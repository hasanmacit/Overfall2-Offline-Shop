#include "stdafx.h"
#include "../../libgame/include/grid.h"
#include "constants.h"
#include "utils.h"
#include "config.h"
#include "offline_shop.h"
#include "desc.h"
#include "desc_manager.h"
#include "char.h"
#include "char_manager.h"
#include "item.h"
#include "item_manager.h"
#include "buffer_manager.h"
#include "packet.h"
#include "log.h"
#include "db.h"
#include "questmanager.h"
#include "monarch.h"
#include "mob_manager.h"
#include "locale_service.h"
#include "desc_client.h"
#include "group_text_parse_tree.h"
#include <boost/algorithm/string/predicate.hpp>
#include <cctype>
#include "offlineshop_manager.h"
#include "p2p.h"
#include "entity.h"
#include "sectree_manager.h"
#include "target.h"
#include "affect.h"

COfflineShopManager::COfflineShopManager()
{
}

COfflineShopManager::~COfflineShopManager()
{
}

struct FFindOfflineShop
{
	const char * szName;

	DWORD dwVID, dwRealOwner;
	FFindOfflineShop(const char * c_szName) : szName(c_szName), dwVID(0), dwRealOwner(0) {};

	void operator()(LPENTITY ent)
	{
		if (!ent)
			return;

		if (ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER ch = (LPCHARACTER)ent;
			if (ch && (ch->IsOfflineShopNPC() && !strcmp(szName, ch->GetName())))
			{
				dwVID = ch->GetVID();
				dwRealOwner = ch->GetOfflineShopRealOwner();
				M2_DESTROY_CHARACTER(ch);
			}
		}
	}
};

bool COfflineShopManager::StartShopping(LPCHARACTER pkChr, LPCHARACTER pkChrShopKeeper)
{
	if (!pkChr || !pkChrShopKeeper)
		return false;
	
	if (pkChr->GetOfflineShopOwner() == pkChrShopKeeper)
		return false;

	if (pkChrShopKeeper->IsPC())
		return false;

	sys_log(0, "OFFLINE_SHOP: START: %s", pkChr->GetName());

	return true;
}

LPOFFLINESHOP COfflineShopManager::CreateOfflineShop(LPCHARACTER npc, DWORD dwOwnerPID, TOfflineShopItemTable * pTable, short bItemCount, long lMapIndex, int iTime, const char * szSign, BYTE bBoardStyle)
{
	if (FindOfflineShop(npc->GetVID()))
		return NULL;

	LPOFFLINESHOP pkOfflineShop = M2_NEW COfflineShop;
	pkOfflineShop->SetOfflineShopNPC(npc);
	pkOfflineShop->SetOfflineShopBorderStyle(bBoardStyle);

	if (pTable)
	{
		pkOfflineShop->SetOfflineShopItems(dwOwnerPID, pTable, bItemCount);
		pkOfflineShop->SetOfflineShopBankValues(dwOwnerPID);
		pkOfflineShop->SetOfflineShopMapIndex(lMapIndex);
		pkOfflineShop->SetOfflineShopTime(iTime);
	}
	else
	{
		pkOfflineShop->CreateTable(dwOwnerPID);
		pkOfflineShop->SetOfflineShopBankValues(dwOwnerPID);
		pkOfflineShop->SetOfflineShopMapIndex(lMapIndex);
		pkOfflineShop->SetOfflineShopTime(iTime);
		pkOfflineShop->SetShopSign(szSign);
	}

	m_map_pkOfflineShopByNPC.insert(TShopMap::value_type(npc->GetVID(), pkOfflineShop));
	m_Map_pkOfflineShopByNPC2.insert(TOfflineShopMap::value_type(dwOwnerPID, npc->GetVID()));

	return pkOfflineShop;
}

LPOFFLINESHOP COfflineShopManager::FindOfflineShop(DWORD dwVID)
{
	TShopMap::iterator it = m_map_pkOfflineShopByNPC.find(dwVID);

	if (it == m_map_pkOfflineShopByNPC.end())
		return NULL;

	return it->second;
}

void COfflineShopManager::DestroyOfflineShop(LPCHARACTER ch, DWORD dwVID, bool pcMode)
{
	if (pcMode)
	{
		if (!ch)
			return;

		quest::PC * pPC = quest::CQuestManager::Instance().GetPC(ch->GetPlayerID());

		if (pPC->IsRunning())
			return;

		// if (ch->HaveAnotherPagesOpen())
		// {
			// ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
			// return;
		// }

		if (ch->GetMapIndex() >= 10000 || g_bChannel == 99)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant do this on this map."));
			return;
		}

		DWORD dwOwnerPID = ch->GetPlayerID();
		BYTE shopChannel = ch->GetOfflineShopChannel();
		bool canGetOfflineShop = CanGetOfflineShop(dwOwnerPID);
		
		if (g_bChannel != shopChannel || !canGetOfflineShop)
		{
			TPacketGGOfflineShopClose p;
			p.bHeader = HEADER_GG_OFFLINE_SHOP_CLOSE_SHOP;
			p.dwOwnerPID = ch->GetPlayerID();
			P2P_MANAGER::instance().Send(&p, sizeof(TPacketGGOfflineShopClose));
			return;
		}

		LPCHARACTER npc;
		npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));

		if (!npc)
			return;

		LPOFFLINESHOP pkOfflineShop;
		pkOfflineShop = FindOfflineShop(FindMyOfflineShop(ch->GetPlayerID()));

		if (!pkOfflineShop)
			return;
		
		// if (pkOfflineShop->GetLeftItemCount() != 0)
		// {
			// ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Remove all your itens and yang before close shop."));
			// return;
		// }
		
		dwOwnerPID = npc->GetOfflineShopRealOwner();
		
		pkOfflineShop->Destroy(npc);
		m_map_pkOfflineShopByNPC.erase(npc->GetVID());
		m_Map_pkOfflineShopByNPC2.erase(dwOwnerPID);
		M2_DELETE(pkOfflineShop);
		
		// DBManager::instance().DirectQuery("DELETE FROM %soffline_shop_sales WHERE item_owner = %u", get_table_postfix(), dwOwnerPID);

		if (ch && ch->GetDesc()) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "BINARY_CloseOfflineShop");
		}
	}
	else
	{
		LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(dwVID);
		LPOFFLINESHOP pkOfflineShop = FindOfflineShop(dwVID);

		if (!npc)
		{
			sys_err("COfflineShopManager::DestroyOfflineShop CRITICAL ERROR! NPC NOT FOUND! VID: %d", dwVID);
			return;
		}

		if (!pkOfflineShop)
		{
			sys_err("COfflineShopManager::DestroyOfflineShop CRITICAL ERROR! pkOfflineShop NOT FOUND! VID: %d", dwVID);
			return;
		}
		
		DWORD dwOwnerPID = npc->GetOfflineShopRealOwner();
		
		pkOfflineShop->Destroy(npc);
		m_map_pkOfflineShopByNPC.erase(npc->GetVID());
		m_Map_pkOfflineShopByNPC2.erase(dwOwnerPID);
		M2_DELETE(pkOfflineShop);
		
		// DBManager::instance().DirectQuery("DELETE FROM %soffline_shop_sales WHERE item_owner = %u", get_table_postfix(), dwOwnerPID);
		
		LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwOwnerPID);
		if (!ch)
		{
			CCI* pcci = P2P_MANAGER::instance().FindByPID(dwOwnerPID);
			if (pcci && pcci->pkDesc) {
				pcci->pkDesc->SetRelay(pcci->szName);
				pcci->pkDesc->ChatPacket(CHAT_TYPE_COMMAND, "BINARY_CloseOfflineShop");
				pcci->pkDesc->SetRelay("");
			}
		}
		else {
			if (ch && ch->GetDesc()) {
				ch->ChatPacket(CHAT_TYPE_COMMAND, "BINARY_CloseOfflineShop");
			}
		}
	}
}

#ifdef __CHEQUE_SYSTEM__
void COfflineShopManager::AddItem(LPCHARACTER ch, BYTE bDisplayPos, TItemPos bPos, long long iPrice, int iPriceCheque)
#else
void COfflineShopManager::AddItem(LPCHARACTER ch, BYTE bDisplayPos, TItemPos bPos, long long iPrice)
#endif
{
	if (!ch)
		return;

	if (thecore_pulse() - ch->GetMyOfflineShopTime() < PASSES_PER_SEC(2))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Please wait."));
		return;
	}

	if (ch->GetMapIndex() >= 10000 || g_bChannel == 99)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant do this on this map."));
		return;
	}

	ch->SetMyOfflineShopTime();

	quest::PC * pPC = quest::CQuestManager::Instance().GetPC(ch->GetPlayerID());

	if (pPC->IsRunning())
		return;

	// if (ch->HaveAnotherPagesOpen())
	// {
		// ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		// return;
	// }

	if (bDisplayPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		sys_err("Overflow offline shop slot count [%s]", ch->GetName());
		return;
	}

	LPITEM pkItem = ch->GetItem(bPos);
	if (!pkItem)
		return;

	const TItemTable * itemTable = pkItem->GetProto();
	if (IS_SET(itemTable->dwAntiFlags, ITEM_ANTIFLAG_GIVE | ITEM_ANTIFLAG_MYSHOP))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Cannot sell anti give and anti shop items."));
		return;
	}

	if (pkItem->isLocked())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cannot sell locked items."));
		return;
	}

#ifdef __SOUL_BIND_SYSTEM__
	if (pkItem->IsSealed())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cannot sell soulbound items."));
		return;
	}
#endif

	if (pkItem->IsEquipped())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cannot sell equipped items."));
		return;
	}

	{
		BYTE bChannel = ch->GetOfflineShopChannel();
		if (bChannel == 0)
			return;
		
		bool canGetOfflineShop = CanGetOfflineShop(ch->GetPlayerID());
		if (g_bChannel != bChannel || !canGetOfflineShop)
		{
			TPacketGGAddOfflineShopItem p;
			p.bHeader = HEADER_GG_OFFLINE_SHOP_ADD_ITEM;
			
			p.itemAdd.id = pkItem->GetID();
			p.itemAdd.owner_id = ch->GetPlayerID();
			p.itemAdd.pos = bDisplayPos;
			p.itemAdd.count = pkItem->GetCount();
			p.itemAdd.price = iPrice;
			p.itemAdd.vnum = pkItem->GetVnum();
			memcpy(p.itemAdd.alSockets, pkItem->GetSockets(), sizeof(p.itemAdd.alSockets));
			memcpy(p.itemAdd.aAttr, pkItem->GetAttributes(), sizeof(p.itemAdd.aAttr));
			p.itemAdd.status = 0;
			#ifdef __BL_TRANSMUTATION__
			p.itemAdd.dwTransmutationVnum = pkItem->GetTransmutationVnum();
			#endif
			#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
			strlcpy(p.itemAdd.szName, pkItem->GetName(), sizeof(p.itemAdd.szName));
			p.itemAdd.refine_level = pkItem->GetRefineLevel();
			#endif
			
			p.itemPos = bPos;
			p.dwOwnerPID = ch->GetPlayerID();
			p.pos = bDisplayPos;
			p.price = iPrice;
			P2P_MANAGER::instance().Send(&p, sizeof(TPacketGGAddOfflineShopItem));
			
			pkItem->RemoveFromCharacter();
			ITEM_MANAGER::instance().FlushDelayedSave(pkItem);
			LogManager::instance().ItemLog(ch, pkItem, "ADD ITEM OFFLINE SHOP", "");
			return;
		}
	}

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));
	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = FindOfflineShop(npc->GetVID());
	if (!pkOfflineShop)
		return;

#ifdef __CHEQUE_SYSTEM__
	pkOfflineShop->AddItem(ch, pkItem, bDisplayPos, iPrice, iPriceCheque);
#else
	pkOfflineShop->AddItem(ch, pkItem, bDisplayPos, iPrice);
#endif
	pkOfflineShop->BroadcastUpdateItem(bDisplayPos, ch->GetPlayerID());
	LogManager::instance().ItemLog(ch, pkItem, "ADD ITEM OFFLINE SHOP", "");
}

void COfflineShopManager::RemoveItem(LPCHARACTER ch, BYTE bPos)
{
	if (!ch)
		return;

	if (thecore_pulse() - ch->GetMyOfflineShopTime() < PASSES_PER_SEC(2))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Please wait."));
		return;
	}

	if (ch->GetMapIndex() >= 10000 || g_bChannel == 99)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant do this on this map."));
		return;
	}

	ch->SetMyOfflineShopTime();

	quest::PC * pPC = quest::CQuestManager::Instance().GetPC(ch->GetPlayerID());

	if (pPC->IsRunning())
		return;

	// if (ch->HaveAnotherPagesOpen())
	// {
		// ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		// return;
	// }

	if (bPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		sys_log(0, "OfflineShopManager::RemoveItem - Overflow slot! [%s]", ch->GetName());
		return;
	}

	{
		BYTE bChannel = ch->GetOfflineShopChannel();
		if (bChannel == 0)
			return;
		
		bool canGetOfflineShop = CanGetOfflineShop(ch->GetPlayerID());
		if (g_bChannel != bChannel || !canGetOfflineShop)
		{
			TPacketGGRemoveOfflineShopItem p;
			p.bHeader = HEADER_GG_OFFLINE_SHOP_REMOVE_ITEM;
			p.bSubHeader = OFFLINE_SHOP_SEND_REMOVE_ITEM;
			p.dwOwnerPID = ch->GetPlayerID();
			p.bPos = bPos;
			P2P_MANAGER::instance().Send(&p, sizeof(TPacketGGRemoveOfflineShopItem));
			return;
		}
	}

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));

	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();

	if (!pkOfflineShop)
		return;

	pkOfflineShop->RemoveItem(ch, bPos);
	if (pkOfflineShop->GetLeftItemCount() <= 0)
		npc->DestroyOfflineShop();
}

void COfflineShopManager::Refresh(LPCHARACTER ch)
{
	if (!ch)
		return;

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));
	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return;

	pkOfflineShop->Refresh(ch);
}

void COfflineShopManager::RefreshMoney(LPCHARACTER ch)
{
	if (!ch)
		return;

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));

	LPOFFLINESHOP pkOfflineShop = npc ? npc->GetOfflineShop() : NULL;
	if (!pkOfflineShop)
	{
#ifdef __CHEQUE_SYSTEM__
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT shop_gold, shop_cheque FROM player.player WHERE id = %u", ch->GetPlayerID()));
#else
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT shop_gold FROM player.player WHERE id = %u", ch->GetPlayerID()));
#endif
		TPacketGCShop p;
		TPacketGCOfflineShopMoney p2;

		p.header = HEADER_GC_OFFLINE_SHOP;
		p.subheader = SHOP_SUBHEADER_GC_REFRESH_MONEY;

		if (pMsg->Get()->uiNumRows == 0)
		{
			p2.llMoney = 0;
#ifdef __CHEQUE_SYSTEM__
			p2.dwCheque = 0;
#endif
			p.size = sizeof(p) + sizeof(p2);
			if (ch && ch->GetDesc()) {
				ch->GetDesc()->BufferedPacket(&p, sizeof(TPacketGCShop));
				ch->GetDesc()->Packet(&p2, sizeof(TPacketGCOfflineShopMoney));
			}
		}
		else
		{
			MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
			str_to_number(p2.llMoney, row[0]);
#ifdef __CHEQUE_SYSTEM__
			str_to_number(p2.dwCheque, row[1]);
#endif
			p.size = sizeof(p) + sizeof(p2);
			if (ch && ch->GetDesc()) {
				ch->GetDesc()->BufferedPacket(&p, sizeof(TPacketGCShop));
				ch->GetDesc()->Packet(&p2, sizeof(TPacketGCOfflineShopMoney));
			}
		}
	}
	else
	{
		TPacketGCShop p;
		TPacketGCOfflineShopMoney p2;

		p.header = HEADER_GC_OFFLINE_SHOP;
		p.subheader = SHOP_SUBHEADER_GC_REFRESH_MONEY;

		p2.llMoney = pkOfflineShop->GetOfflineShopGold();
#ifdef __CHEQUE_SYSTEM__
		p2.dwCheque = pkOfflineShop->GetOfflineShopCheque();
#endif
		p.size = sizeof(p) + sizeof(p2);
		if (ch && ch->GetDesc()) {
			ch->GetDesc()->BufferedPacket(&p, sizeof(TPacketGCShop));
			ch->GetDesc()->Packet(&p2, sizeof(TPacketGCOfflineShopMoney));
		}
	}
}

void COfflineShopManager::RefreshUnsoldItems(LPCHARACTER ch)
{
	if (!ch || (ch && !ch->GetDesc()))
		return;
	
	TPacketGCShop pack;
	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_UPDATE_ITEM2;

	TPacketGCOfflineShopStart pack2;
	memset(&pack2, 0, sizeof(pack2));
	pack2.owner_vid = 0;

	char szQuery[1024];
	snprintf(szQuery, sizeof(szQuery), "SELECT pos, count, vnum, "
		"price, "
		"transmutation, "
		"socket0, socket1, socket2, socket3, socket4, socket5, "
		"attrtype0, attrvalue0, "
		"attrtype1, attrvalue1, "
		"attrtype2, attrvalue2, "
		"attrtype3, attrvalue3, "
		"attrtype4, attrvalue4, "
		"attrtype5, attrvalue5, "
		"attrtype6, attrvalue6, "
		"applytype0, applyvalue0, "
		"applytype1, applyvalue1, "
		"applytype2, applyvalue2, "
		"applytype3, applyvalue3, "
		"applytype4, applyvalue4, "
		"applytype5, applyvalue5, "
		"applytype6, applyvalue6, "
		"applytype7, applyvalue7 "
		"FROM %soffline_shop_item WHERE owner_id = %u and status = 1", get_table_postfix(), ch->GetPlayerID());
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));
	
	if (!pMsg || (pMsg && !pMsg->Get()))
		return;
	
	MYSQL_ROW row;
	while (NULL != (row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
	{
		BYTE bPos = 0;
		str_to_number(bPos, row[0]);
		str_to_number(pack2.items[bPos].count, row[1]);
		str_to_number(pack2.items[bPos].vnum, row[2]);
		str_to_number(pack2.items[bPos].price, row[3]);
		str_to_number(pack2.items[bPos].dwTransmutationVnum, row[4]);

		DWORD alSockets[ITEM_SOCKET_MAX_NUM];
		for (int i = 0, n = 5; i < ITEM_SOCKET_MAX_NUM; ++i, n++)
			str_to_number(alSockets[i], row[n]);

		TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_MAX_NUM];
		for (int i = 0, iStartType = 11, iStartValue = 12; i < ITEM_ATTRIBUTE_MAX_NUM; ++i, iStartType += 2, iStartValue += 2)
		{
			str_to_number(aAttr[i].bType, row[iStartType]);
			str_to_number(aAttr[i].sValue, row[iStartValue]);
		}

		thecore_memcpy(pack2.items[bPos].alSockets, alSockets, sizeof(pack2.items[bPos].alSockets));
		thecore_memcpy(pack2.items[bPos].aAttr, aAttr, sizeof(pack2.items[bPos].aAttr));
	}

	pack.size = sizeof(pack) + sizeof(pack2);
	if (ch && ch->GetDesc()) {
		ch->GetDesc()->BufferedPacket(&pack, sizeof(TPacketGCShop));
		ch->GetDesc()->Packet(&pack2, sizeof(TPacketGCOfflineShopStart));
	}
}

void COfflineShopManager::TakeItem(LPCHARACTER ch, BYTE bPos)
{
	if (!ch)
		return;

	if (bPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
		return;

	if (ch->GetOfflineShop() || ch->GetOfflineShopOwner())
		return;

	if (ch->GetMapIndex() >= 10000 || g_bChannel == 99)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant do this on this map."));
		return;
	}

	char szQuery[1024];
	snprintf(szQuery, sizeof(szQuery), "SELECT id, pos, count, vnum, "
#ifdef __ITEM_SOCKET5__
		"socket0, socket1, socket2, socket3, socket4, socket5, "
#else
		"socket0, socket1, socket2, "
#endif
#ifdef __BL_TRANSMUTATION__
		"transmutation, "
#endif
		"attrtype0, attrvalue0, "
		"attrtype1, attrvalue1, "
		"attrtype2, attrvalue2, "
		"attrtype3, attrvalue3, "
		"attrtype4, attrvalue4, "
		"attrtype5, attrvalue5, "
		"attrtype6, attrvalue6, "
		"applytype0, applyvalue0, "
		"applytype1, applyvalue1, "
		"applytype2, applyvalue2, "
		"applytype3, applyvalue3, "
		"applytype4, applyvalue4, "
		"applytype5, applyvalue5, "
		"applytype6, applyvalue6, "
		"applytype7, applyvalue7 "
		"FROM %soffline_shop_item WHERE owner_id = %u and pos = %d and status = 1", get_table_postfix(), ch->GetPlayerID(), bPos);
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));

	if (pMsg->Get()->uiNumRows == 0)
	{
		sys_log(0, "OfflineShopManager::TakeItem - This slot is empty! [%s]", ch->GetName());
		return;
	}

	TPlayerItem item;
	int rows;
	if (!(rows = mysql_num_rows(pMsg->Get()->pSQLResult)))
		return;

	for (int i = 0; i < rows; ++i)
	{
		MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
		int cur = 0;

		str_to_number(item.id, row[cur++]);
		str_to_number(item.pos, row[cur++]);
		str_to_number(item.count, row[cur++]);
		str_to_number(item.vnum, row[cur++]);
		str_to_number(item.alSockets[0], row[cur++]);
		str_to_number(item.alSockets[1], row[cur++]);
		str_to_number(item.alSockets[2], row[cur++]);
#ifdef __ITEM_SOCKET5__
		str_to_number(item.alSockets[3], row[cur++]);
		str_to_number(item.alSockets[4], row[cur++]);
		str_to_number(item.alSockets[5], row[cur++]);
#endif
#ifdef __BL_TRANSMUTATION__
		str_to_number(item.dwTransmutationVnum, row[cur++]);
#endif

		for (int j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; j++)
		{
			str_to_number(item.aAttr[j].bType, row[cur++]);
			str_to_number(item.aAttr[j].sValue, row[cur++]);
		}
	}

	LPITEM pItem = ITEM_MANAGER::instance().CreateItem(item.vnum, item.count);
	if (!pItem)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Error."));
		return;
	}

	pItem->SetID(item.id);
	pItem->SetAttributes(item.aAttr);
	pItem->SetSockets(item.alSockets);
#ifdef __BL_TRANSMUTATION__
	pItem->SetTransmutationVnum(item.dwTransmutationVnum);
#endif

	int iEmptyPos = 0;
	if (pItem->IsDragonSoul())
		iEmptyPos = ch->GetEmptyDragonSoulInventory(pItem);
#ifdef WJ_SPLIT_INVENTORY_SYSTEM
	else if (pItem->IsSkillBook())
		iEmptyPos = ch->GetEmptySkillBookInventory(pItem->GetSize());
	else if (pItem->IsUpgradeItem())
		iEmptyPos = ch->GetEmptyUpgradeItemsInventory(pItem->GetSize());
	else if (pItem->IsStone())
		iEmptyPos = ch->GetEmptyStoneInventory(pItem->GetSize());
	else if (pItem->IsGiftBox())
		iEmptyPos = ch->GetEmptyGiftBoxInventory(pItem->GetSize());
#endif
	else
		iEmptyPos = ch->GetEmptyInventory(pItem->GetSize());

	if (iEmptyPos < 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("소지품에 빈 공간이 없습니다."));
		return;
	}

	if (pItem->IsDragonSoul())
		pItem->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
#ifdef WJ_SPLIT_INVENTORY_SYSTEM
	else if (pItem->IsSkillBook())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsUpgradeItem())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsStone())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsGiftBox())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
#endif
	else
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));

	DBManager::instance().DirectQuery("DELETE FROM %soffline_shop_item WHERE owner_id = %u and pos = %d", get_table_postfix(), ch->GetPlayerID(), bPos);
	LogManager::instance().ItemLog(ch, pItem, "TAKE OFFLINE SHOP ITEM", "");
}

DWORD COfflineShopManager::FindMyOfflineShop(DWORD dwPID)
{
	TOfflineShopMap::iterator it = m_Map_pkOfflineShopByNPC2.find(dwPID);
	if (m_Map_pkOfflineShopByNPC2.end() == it)
		return 0;

	return it->second;
}

void COfflineShopManager::ChangeOfflineShopTime(LPCHARACTER ch, int bTime)
{
	if (!ch)
		return;

	DWORD dwOfflineShopVID = FindMyOfflineShop(ch->GetPlayerID());
	if (!dwOfflineShopVID)
		return;

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));
	if (npc)
	{
		int iTime = bTime*60;
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("UPDATE %soffline_shop_npc SET time = time + %d WHERE owner_id = %u", get_table_postfix(), iTime, ch->GetPlayerID()));
		std::unique_ptr<SQLMsg> pMsg2(DBManager::instance().DirectQuery("UPDATE player.player SET offlineshop_time = offlineshop_time + %d WHERE owner_id = %u", iTime, ch->GetPlayerID()));
		npc->StopOfflineShopUpdateEvent();
		npc->SetOfflineShopTimer(iTime);
		npc->StartOfflineShopUpdateEvent();
		LogManager::instance().CharLog(ch, 0, "OFFLINE SHOP", "CHANGE TIME");
	}
	else
	{
		TPacketGGChangeOfflineShopTime p;
		p.bHeader = HEADER_GG_CHANGE_OFFLINE_SHOP_TIME;
		// p.bTime = bTime;
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT mapIndex FROM %soffline_shop_npc WHERE owner_id = %u", get_table_postfix(), ch->GetPlayerID()));
		if (pMsg->Get()->uiNumRows == 0)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Shop not found."));
			return;
		}

		MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
		str_to_number(p.lMapIndex, row[0]);
		p.dwOwnerPID = ch->GetPlayerID();
		P2P_MANAGER::instance().Send(&p, sizeof(TPacketGGChangeOfflineShopTime));
	}
}

void COfflineShopManager::StopShopping(LPCHARACTER ch)
{
	if (!ch || (ch && !ch->GetDesc()))
		return;
	
	LPOFFLINESHOP pkOfflineShop;
	if (!(pkOfflineShop = ch->GetOfflineShop()))
		return;

	pkOfflineShop->RemoveGuest(ch);
	sys_log(0, "OFFLINE_SHOP: END: %s", ch->GetName());

	TPacketGCShop pack;
	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_UPDATE_ITEM2;

	TPacketGCOfflineShopStart pack2;
	memset(&pack2, 0, sizeof(pack2));
	pack2.owner_vid = 0;

	for (BYTE i = 0; i < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++i)
		pack2.items[i].vnum = 0;

	pack.size = sizeof(pack) + sizeof(pack2);
	if (ch && ch->GetDesc()) {
		ch->GetDesc()->BufferedPacket(&pack, sizeof(TPacketGCShop));
		ch->GetDesc()->Packet(&pack2, sizeof(TPacketGCOfflineShopStart));
	}
}

void COfflineShopManager::Buy(LPCHARACTER ch, BYTE pos)
{
	if (!ch || (ch && !ch->GetDesc()))
		return;
	
	if (!ch->GetOfflineShop() || !ch->GetOfflineShopOwner())
		return;

	if (DISTANCE_APPROX(ch->GetX() - ch->GetOfflineShopOwner()->GetX(), ch->GetY() - ch->GetOfflineShopOwner()->GetY()) > 1500)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You are to fare away."));
		return;
	}

	LPOFFLINESHOP pkOfflineShop = ch->GetOfflineShop();
	if (!pkOfflineShop)
		return;

	int ret = pkOfflineShop->Buy(ch, pos);

	if (SHOP_SUBHEADER_GC_OK != ret)
	{
		TPacketGCShop pack;
		pack.header = HEADER_GC_OFFLINE_SHOP;
		pack.subheader = ret;
		pack.size = sizeof(TPacketGCShop);
		
		if (ch && ch->GetDesc())
			ch->GetDesc()->Packet(&pack, sizeof(pack));
	}
}

void COfflineShopManager::WithdrawMoney(LPCHARACTER ch, long long dwRequiredMoney)
{
	if (!ch)
		return;

	unsigned long long llRequiredMoney = dwRequiredMoney;

	if (llRequiredMoney < 0)
		return;

	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT shop_gold FROM %splayer WHERE id = %u", get_table_postfix(), ch->GetPlayerID()));
	if (pMsg->Get()->uiNumRows == 0)
		return;

	long long llCurrentMoney = 0;
	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	str_to_number(llCurrentMoney, row[0]);

	if (llRequiredMoney > llCurrentMoney)
		llRequiredMoney = llCurrentMoney;

	// bool isOverFlow = ch->GetGold() + llRequiredMoney >= g_MaxGold ? true : false;
	// if (isOverFlow)
	// {
		// ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You carry to much gold."));
		// return;
	// }

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));
	LPOFFLINESHOP pkOfflineShop = npc ? npc->GetOfflineShop() : NULL;
	if (pkOfflineShop)
		pkOfflineShop->SetOfflineShopGold(pkOfflineShop->GetOfflineShopGold()-llRequiredMoney);

	ch->PointChange(POINT_GOLD, llRequiredMoney, false);
	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You have withdrawn %lld Gold from your Private Shop."), llRequiredMoney);

	DBManager::instance().DirectQuery("UPDATE %splayer SET shop_gold = shop_gold - %lld WHERE id = %u", get_table_postfix(), llRequiredMoney, ch->GetPlayerID());
	LogManager::instance().CharLog(ch, 0, "OFFLINE_SHOP", "WITHDRAW_GOLD");
	RefreshMoney(ch);
}

#ifdef __CHEQUE_SYSTEM__
void COfflineShopManager::WithdrawCheque(LPCHARACTER ch, DWORD dwRequiredCheque)
{
	if (!ch)
		return;

	if (dwRequiredCheque < 0)
		return;

	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT shop_cheque FROM %splayer WHERE id = %u", get_table_postfix(), ch->GetPlayerID()));
	if (pMsg->Get()->uiNumRows == 0)
		return;

	DWORD dwCurrentCheque = 0;
	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	str_to_number(dwCurrentCheque, row[0]);

	if (dwRequiredCheque > dwCurrentCheque)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You don't have enough Won."));
		return;
	}

	bool isOverFlow = ch->GetCheque() + dwRequiredCheque >= CHEQUE_MAX ? true : false;
	if (isOverFlow)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You carry to much won."));
		return;
	}

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));
	LPOFFLINESHOP pkOfflineShop = npc ? npc->GetOfflineShop() : NULL;
	if (pkOfflineShop)
		pkOfflineShop->SetOfflineShopCheque(pkOfflineShop->GetOfflineShopCheque()-dwRequiredCheque);

	ch->PointChange(POINT_CHEQUE, dwRequiredCheque, false);
	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You have withdrawn %d Won from your Private Shop."), dwRequiredCheque);

	DBManager::instance().DirectQuery("UPDATE %splayer SET shop_cheque = shop_cheque - %d WHERE id = %u", get_table_postfix(), dwRequiredCheque, ch->GetPlayerID());
	LogManager::instance().CharLog(ch, 0, "OFFLINE_SHOP", "WITHDRAW_CHEQUE");
}
#endif

BYTE COfflineShopManager::LeftItemCount(LPCHARACTER ch)
{
	if (!ch)
		return -1;

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));
	if (!npc)
		return -1;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return -1;

	BYTE ret = pkOfflineShop->GetLeftItemCount();
	return ret;
}

bool COfflineShopManager::HasOfflineShop(LPCHARACTER ch)
{
	if (!ch)
		return false;
	
	BYTE bHasOfflineShop = 0;

	TPacketGCShop p;
	p.header = HEADER_GC_OFFLINE_SHOP;
	p.subheader = SHOP_SUBHEADER_GC_CHECK_RESULT;
	p.size = sizeof(p);

	if (ch->GetOfflineShopVID())
	{
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT owner_id FROM %soffline_shop_npc WHERE owner_id = %u", get_table_postfix(), ch->GetPlayerID()));
		if (pMsg->Get()->uiNumRows == 0)
		{
			bHasOfflineShop = 0;
			if (ch && ch->GetDesc())
			{
				ch->GetDesc()->BufferedPacket(&p, sizeof(TPacketGCShop));
				ch->GetDesc()->Packet(&bHasOfflineShop, sizeof(BYTE));
			}
			return false;
		}
		else
		{
			bHasOfflineShop = 1;
			if (ch && ch->GetDesc())
			{
				ch->GetDesc()->BufferedPacket(&p, sizeof(TPacketGCShop));
				ch->GetDesc()->Packet(&bHasOfflineShop, sizeof(BYTE));
			}
			return true;
		}
	}

	return false;
}

LPOFFLINESHOP COfflineShopManager::FindShop(DWORD dwVID)
{
	TShopMap::iterator it = m_map_pkOfflineShopByNPC.find(dwVID);

	if (it == m_map_pkOfflineShopByNPC.end())
		return NULL;

	return it->second;
}

bool COfflineShopManager::AddGuest(LPCHARACTER ch, DWORD dwVID)
{
	LPOFFLINESHOP pOfflineShop = FindShop(dwVID);
	LPCHARACTER npc = pOfflineShop->IsOfflineShopNPC() ? pOfflineShop->GetOfflineShopNPC() : 0;
	if (!npc)
		return false;
	npc->SetOfflineShopOwner(ch);
	return pOfflineShop->AddGuest(ch, npc);
}

LPCHARACTER COfflineShopManager::GetOfflineShopNPC(DWORD dwVID)
{
	LPOFFLINESHOP pOfflineShop = FindShop(dwVID);
	if (pOfflineShop)
		return pOfflineShop->IsOfflineShopNPC() ? pOfflineShop->GetOfflineShopNPC() : 0;
	else
		return 0;
}

/*
	Overfall Work
*/

long COfflineShopManager::GetMapIndex(DWORD dwPID)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return 0;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return 0;

	return pkOfflineShop->GetOfflineShopMapIndex();
}

bool COfflineShopManager::GetOfflineShopCoords(DWORD dwPID, long * map_index, long * x, long * y)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return false;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return false;
	
	*map_index = pkOfflineShop->GetOfflineShopMapIndex();
	*x = npc->GetX();
	*y = npc->GetY();
	return true;
}

bool COfflineShopManager::GetOfflineShopCoordsP2P(LPCHARACTER ch, long * map_index, long * x, long * y)
{
	if (!ch)
		return false;
	
	if (!ch->HasOfflineShop())
		return false;

	DWORD player_id = ch->GetPlayerID();
	
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT x,y,z,mapIndex FROM offline_shop_npc%s WHERE owner_id = %u", get_table_postfix(), player_id));
	if (!pMsg || (pMsg && pMsg->Get()->uiNumRows == 0))
		return false;

	long shop_x = -1, shop_y = -1, shop_z = -1, shop_MapIndex = -1;
	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	str_to_number(shop_x, row[0]);
	str_to_number(shop_y, row[1]);
	str_to_number(shop_z, row[2]);
	str_to_number(shop_MapIndex, row[3]);
	
	*map_index = shop_MapIndex;
	*x = shop_x;
	*y = shop_y;
	return true;
}

int COfflineShopManager::GetLeftTime(DWORD dwPID)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return 0;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return 0;
	
	return pkOfflineShop->GetOfflineShopTime();
}

const char* COfflineShopManager::GetOfflineShopSign(DWORD dwPID)
{
	const char * cleanSign = "";
	
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return cleanSign;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return cleanSign;
	
	return pkOfflineShop->GetShopSign();
}

DWORD COfflineShopManager::GetDisplayedCount(DWORD dwPID)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return 0;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return 0;
	
	return pkOfflineShop->GetDisplayedCount();
}

void COfflineShopManager::RefreshP2P(DWORD dwPID)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return;
	
	pkOfflineShop->RefreshP2P(dwPID);
}

bool COfflineShopManager::CanGetOfflineShop(DWORD dwPID)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return false;

	LPOFFLINESHOP pkOfflineShop = FindOfflineShop(npc->GetVID());
	if (!pkOfflineShop)
		return false;
	
	return true;
}

void COfflineShopManager::AddItemP2P(DWORD dwPID, TOfflineShopItem pkItem, BYTE bPos, long long iPrice)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = FindOfflineShop(npc->GetVID());
	if (!pkOfflineShop)
		return;

	pkOfflineShop->AddItemP2P(dwPID, pkItem, bPos, iPrice);
	pkOfflineShop->BroadcastUpdateItem(bPos, dwPID);
}

void COfflineShopManager::RemoveItemP2P(DWORD dwPID, BYTE bPos)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return;

	pkOfflineShop->RemoveItemP2P(dwPID, bPos);
	if (pkOfflineShop->GetLeftItemCount() <= 0)
		npc->DestroyOfflineShop();
}

void COfflineShopManager::GiveItemP2P(DWORD dwPID, TPlayerItem item2)
{
	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwPID);
	if (!ch) {
		sys_err("CRITICAL ERROR: GiveItemP2P PID: %d", dwPID);
		return;
	}
	
	LPITEM pItem = ITEM_MANAGER::instance().CreateItem(item2.vnum, item2.count);
	if (!pItem)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Error"));
		return;
	}

	pItem->SetAttributes(item2.aAttr);
	pItem->SetSockets(item2.alSockets);
#ifdef __BL_TRANSMUTATION__
	pItem->SetTransmutationVnum(item2.dwTransmutationVnum);
#endif

	ch->AutoGiveItem(pItem);
	ITEM_MANAGER::instance().FlushDelayedSave(pItem);
	LogManager::instance().ItemLog(ch, pItem, "DELETE OFFLINE SHOP ITEM", "");
}

bool COfflineShopManager::CanCloseOfflineShopP2P(DWORD dwPID)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return false;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return false;
	
	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwPID);
	if (!ch)
	{
		CCI* pcci = P2P_MANAGER::instance().FindByPID(dwPID);
		if (pcci && pcci->pkDesc) {
			if (pcci->lMapIndex >= 10000 || pcci->bChannel == 99) {
				pcci->pkDesc->SetRelay(pcci->szName);
				pcci->pkDesc->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant do this on this map."));
				pcci->pkDesc->SetRelay("");
			}
		}
		else
			return false;
	}
	else {
		if (ch->GetDesc()) {
			if (ch->GetMapIndex() >= 10000 || g_bChannel == 99)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant do this on this map."));
				return false;
			}
		}
	}
	
	return true;
}

void COfflineShopManager::ChangeOfflineShopName(DWORD dwPID, const char *shopName)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (!pkOfflineShop)
		return;

	DBManager::instance().DirectQuery("UPDATE %soffline_shop_npc SET sign = '%s' WHERE owner_id = '%u'", get_table_postfix(), shopName, dwPID);
	pkOfflineShop->SetShopSign(shopName);
	npc->ChangeShopSign(npc->GetVID(), shopName);

	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwPID);
	if (!ch)
	{
		CCI* pcci = P2P_MANAGER::instance().FindByPID(dwPID);
		if (pcci && pcci->pkDesc) {
			TPacketGCShopSign p;
			p.bHeader = HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN_P2P;
			p.dwVID = npc->GetVID();
			strlcpy(p.szSign, shopName, sizeof(p.szSign));
			pcci->pkDesc->SetRelay(pcci->szName);
			pcci->pkDesc->Packet(&p, sizeof(TPacketGCShopSign));
			pcci->pkDesc->SetRelay("");
		}
	}
	else {
		if (ch->GetDesc()) {
			TPacketGCShopSign p;
			p.bHeader = HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN_P2P;
			p.dwVID = npc->GetVID();
			strlcpy(p.szSign, shopName, sizeof(p.szSign));
			ch->GetDesc()->Packet(&p, sizeof(TPacketGCShopSign));
		}
	}
}

bool COfflineShopManager::PlayerIsOnline(DWORD dwPID)
{
	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwPID);
	if (!ch)
	{
		CCI* pcci = P2P_MANAGER::instance().FindByPID(dwPID);
		if (pcci) {
			if (pcci->lMapIndex >= 10000 || pcci->bChannel == 99)
				return false;
			else
				return true;
		}
		else
			return false;
	}
	else {
		if (ch->GetMapIndex() >= 10000 || g_bChannel == 99)
			return false;
		else
			return true;
	}
	
	return false;
}

void COfflineShopManager::AdviseItemSell(LPCHARACTER ch, DWORD itemVnum, long long itemPrice, const char * buyerName)
{
	if (!ch || (ch && !ch->GetDesc()))
		return;
	
	RefreshMoney(ch);
	
	TPacketGGOfflineShopAdviseOwnerSell p;
	p.bHeader = HEADER_GC_OFFLINE_ADVISE_PLAYER_BUY;
	p.dwOwnerPID = ch->GetPlayerID();
	p.itemSelled = itemVnum;
	p.itemPrice = itemPrice;
	strlcpy(p.buyerName, buyerName, sizeof(p.buyerName));;
	ch->GetDesc()->Packet(&p, sizeof(TPacketGGOfflineShopAdviseOwnerSell));
}

DWORD COfflineShopManager::GetOfflineShopVID(DWORD dwPID)
{
	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));
	if (!npc)
		return 0;
	
	return npc->GetVID();
}

void COfflineShopManager::ChangeOfflineShopItemPrice(LPCHARACTER ch, BYTE bPos, long long llPrice)
{
	if (!ch)
		return;

	if (thecore_pulse() - ch->GetMyOfflineShopTime() < PASSES_PER_SEC(2))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Please wait."));
		return;
	}

	if (ch->GetMapIndex() >= 10000 || g_bChannel == 99)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant do this on this map."));
		return;
	}

	ch->SetMyOfflineShopTime();

	quest::PC * pPC = quest::CQuestManager::Instance().GetPC(ch->GetPlayerID());

	if (pPC->IsRunning())
		return;

	// if (ch->HaveAnotherPagesOpen())
	// {
		// ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		// return;
	// }

	if (bPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		sys_log(0, "OfflineShopManager::RemoveItem - Overflow slot! [%s]", ch->GetName());
		return;
	}

	{
		BYTE bChannel = ch->GetOfflineShopChannel();
		if (bChannel == 0)
			return;
		
		bool canGetOfflineShop = CanGetOfflineShop(ch->GetPlayerID());
		if (g_bChannel != bChannel || !canGetOfflineShop)
		{
			TPacketGGChangeOfflineShopItemPrice p;
			p.bHeader = HEADER_GG_OFFLINE_SHOP_CHANGE_ITEM_PRICE;
			p.dwOwnerPID = ch->GetPlayerID();
			p.bPos = bPos;
			p.llPrice = llPrice;
			P2P_MANAGER::instance().Send(&p, sizeof(TPacketGGChangeOfflineShopItemPrice));
			return;
		}
	}

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(ch->GetPlayerID()));

	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();

	if (!pkOfflineShop)
		return;

	if (pkOfflineShop->ChangeItemPrice(ch->GetPlayerID(), bPos, llPrice))
		ch->ChatPacket(CHAT_TYPE_INFO, "[Loja Offline] O pre? do item foi alterado com sucesso.");
}

void COfflineShopManager::ChangeOfflineShopItemPriceP2P(DWORD dwPID, BYTE bPos, long long llPrice)
{
	if (bPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
		return;

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(FindMyOfflineShop(dwPID));

	if (!npc)
		return;

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();

	if (!pkOfflineShop)
		return;

	if (pkOfflineShop->ChangeItemPrice(dwPID, bPos, llPrice)) {
		LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwPID);
		if (!ch)
		{
			CCI* pcci = P2P_MANAGER::instance().FindByPID(dwPID);
			if (pcci && pcci->pkDesc) {
				pcci->pkDesc->SetRelay(pcci->szName);
				pcci->pkDesc->ChatPacket(CHAT_TYPE_INFO, "[Loja Offline] O pre? do item foi alterado com sucesso.");
				pcci->pkDesc->SetRelay("");
			}
		}
		else {
			if (ch->GetDesc()) {
				ch->ChatPacket(CHAT_TYPE_INFO, "[Loja Offline] O pre? do item foi alterado com sucesso.");
			}
		}
	}
}
