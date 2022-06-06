/*
	* Filename : offline_shop.cpp
	* Version : 0.1
	* Description : --
*/

#include "stdafx.h"
#include "../../libgame/include/grid.h"
#include "constants.h"
#include "utils.h"
#include "config.h"
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
#include "offline_shop.h"
#include "p2p.h"
#include "offlineshop_manager.h"
#include "desc_client.h"
#include "target.h"

COfflineShop::COfflineShop() : 
	m_pkOfflineShopNPC(NULL), 
	m_pkOfflineShopBorderStyle(0), 
	m_dwDisplayedCount(0),
	m_llMapIndex(0), 
	m_iTime(0), 
	llGold(0)
#ifdef __CHEQUE_SYSTEM__
	,dwCheque(0)
#endif
{
	m_pGrid = M2_NEW CGrid(10, 8);
	v_alreadySeeShop.clear();
}

COfflineShop::~COfflineShop()
{
	TPacketGCShop pack;
	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_END;
	pack.size = sizeof(TPacketGCShop);

	Broadcast(&pack, sizeof(pack));

#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
	for (auto &idx : m_map_guest)
	{
		LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(idx);
		if (ch) ch->SetOfflineShop(NULL);
	}
#else
	for (GuestMapType::iterator it = m_map_guest.begin(); it != m_map_guest.end(); ++it)
	{
		LPCHARACTER ch = it->first;
		if (ch)
			ch->SetOfflineShop(NULL);
	}
#endif

	M2_DELETE(m_pGrid);
}

void COfflineShop::SetOfflineShopNPC(LPCHARACTER npc)
{
	m_pkOfflineShopNPC = npc;
}

void COfflineShop::CreateTable(DWORD dwOwnerID)
{
	MYSQL_ROW row;
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT * FROM %soffline_shop_item WHERE owner_id = %u", get_table_postfix(), dwOwnerID));

	m_itemVector.resize(OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
	memset(&m_itemVector[0], 0, sizeof(OFFLINE_SHOP_ITEM) * m_itemVector.size());

	if (pMsg->Get()->uiNumRows != 0)
	{
		while (NULL != (row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
		{
			const TItemTable * item_table;

			DWORD vnum = 0;
			str_to_number(vnum, row[4]);
			BYTE pos = 0;
			str_to_number(pos, row[2]);

			item_table = ITEM_MANAGER::instance().GetTable(vnum);

			if (!item_table)
			{
				sys_err("OfflineShop: no item table by item vnum #%d", vnum);
				continue;
			}

			OFFLINE_SHOP_ITEM & item = m_itemVector[pos];

			str_to_number(item.id, row[0]);									// 0
			str_to_number(item.owner_id, row[1]);							// 1
			str_to_number(item.pos, row[2]);								// 2
			str_to_number(item.count, row[3]);								// 3
			str_to_number(item.vnum, row[4]);								// 4
			str_to_number(item.alSockets[0], row[5]);						// 5
			str_to_number(item.alSockets[1], row[6]);						// 6
			str_to_number(item.alSockets[2], row[7]);						// 7
#ifdef __ITEM_SOCKET5__
			str_to_number(item.alSockets[3], row[8]);						// 8
			str_to_number(item.alSockets[4], row[9]);						// 9
			str_to_number(item.alSockets[5], row[10]);						// 10
#endif
			str_to_number(item.aAttr[0].bType, row[11]);					// 11 ~ 8
			str_to_number(item.aAttr[0].sValue, row[12]);					// 12 ~ 9
			str_to_number(item.aAttr[1].bType, row[13]);					// 13 ~ 10
			str_to_number(item.aAttr[1].sValue, row[14]);					// 14 ~ 11
			str_to_number(item.aAttr[2].bType, row[15]);					// 15 ~ 12
			str_to_number(item.aAttr[2].sValue, row[16]);					// 16 ~ 13
			str_to_number(item.aAttr[3].bType, row[17]);					// 17 ~ 14
			str_to_number(item.aAttr[3].sValue, row[18]);					// 18 ~ 15
			str_to_number(item.aAttr[4].bType, row[19]);					// 19 ~ 16
			str_to_number(item.aAttr[4].sValue, row[20]);					// 20 ~ 17
			str_to_number(item.aAttr[5].bType, row[21]);					// 21 ~ 18
			str_to_number(item.aAttr[5].sValue, row[22]);					// 22 ~ 19
			str_to_number(item.aAttr[6].bType, row[23]);					// 23 ~ 20
			str_to_number(item.aAttr[6].sValue, row[24]);					// 24 ~ 21
			str_to_number(item.aAttr[7].bType, row[25]);					// 25 ~ 22
			str_to_number(item.aAttr[7].sValue, row[26]);					// 26 ~ 23
			str_to_number(item.aAttr[8].bType, row[27]);					// 27 ~ 24
			str_to_number(item.aAttr[8].sValue, row[28]);					// 28 ~ 25
			str_to_number(item.aAttr[9].bType, row[29]);					// 29 ~ 26
			str_to_number(item.aAttr[9].sValue, row[30]);					// 30 ~ 27
			str_to_number(item.aAttr[10].bType, row[31]);					// 31 ~ 28
			str_to_number(item.aAttr[10].sValue, row[32]);					// 32 ~ 29
			str_to_number(item.aAttr[11].bType, row[33]);					// 33 ~ 30
			str_to_number(item.aAttr[11].sValue, row[34]);					// 34 ~ 31
			str_to_number(item.aAttr[12].bType, row[35]);					// 35 ~ 32
			str_to_number(item.aAttr[12].sValue, row[36]);					// 36 ~ 33
			str_to_number(item.aAttr[13].bType, row[37]);					// 37 ~ 34
			str_to_number(item.aAttr[13].sValue, row[38]);					// 38 ~ 35
			str_to_number(item.aAttr[14].bType, row[39]);					// 39 ~ 36
			str_to_number(item.aAttr[14].sValue, row[40]);					// 40 ~ 37
			str_to_number(item.price, row[41]);								// 41 ~ 38
#ifdef __CHEQUE_SYSTEM__
			str_to_number(item.price_cheque, row[42]);						// 42 ~ 39
#endif
			str_to_number(item.status, row[43]);								// 43 ~ 40
			strlcpy(item.szBuyerName, row[44], sizeof(item.szBuyerName));	// 44 ~ 41
#ifdef __BL_TRANSMUTATION__
			str_to_number(item.dwTransmutationVnum, row[45]);						// 45 ~ 42
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
			strlcpy(item.szName, row[46], sizeof(item.szName));				// 46 ~ 43
			str_to_number(item.refine_level, row[47]);						// 47 ~ 44

			DWORD vid = GetOfflineShopNPC()->GetVID();
			item.shop_id = vid;
#endif
		}
	}
}

void COfflineShop::SetOfflineShopBankValues(DWORD dwOwnerPID)
{
#ifdef __CHEQUE_SYSTEM__
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT shop_gold,shop_cheque FROM player.player WHERE id = %u", dwOwnerPID));
#else
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT shop_gold FROM player.player WHERE id = %u", dwOwnerPID));
#endif
	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	if (pMsg->Get()->uiNumRows == 0)
	{
		SetOfflineShopGold(0);
#ifdef __CHEQUE_SYSTEM__
		SetOfflineShopCheque(0);
#endif
	}
	else
	{
		long long llGold = 0;
#ifdef __CHEQUE_SYSTEM__
		DWORD dwCheque = 0;
#endif
		str_to_number(llGold, row[0]);
#ifdef __CHEQUE_SYSTEM__
		str_to_number(dwCheque, row[1]);
#endif
		SetOfflineShopGold(llGold);
#ifdef __CHEQUE_SYSTEM__
		SetOfflineShopCheque(dwCheque);
#endif
	}
}

#ifdef __EXTENDED_ITEM_COUNT__
void COfflineShop::SetOfflineShopItems(DWORD dwOwnerPID, TOfflineShopItemTable * pTable, short bItemCount)
#else
void COfflineShop::SetOfflineShopItems(DWORD dwOwnerPID, TOfflineShopItemTable * pTable, BYTE bItemCount)
#endif
{
	if (bItemCount > OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
		return;

	m_pGrid->Clear();

	m_itemVector.resize(OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
	memset(&m_itemVector[0], 0, sizeof(OFFLINE_SHOP_ITEM) * m_itemVector.size());

	for (int i = 0; i < bItemCount; ++i)
	{
		const TItemTable * item_table;

		LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwOwnerPID);
		LPITEM pkItem = ch->GetItem(pTable->pos);

		if (!pkItem)
			continue;

		if (!pkItem->GetVnum())
			continue;

		item_table = ITEM_MANAGER::instance().GetTable(pkItem->GetVnum());

		if (!item_table)
		{
			sys_err("OfflineShop: no item table by item vnum #%d", pkItem->GetVnum());
			continue;
		}

		OFFLINE_SHOP_ITEM & item = m_itemVector[pTable->display_pos];

		item.id = pkItem->GetID();
		item.owner_id = ch->GetPlayerID();
		item.pos = pTable->display_pos;
		item.count = pkItem->GetCount();
		item.price = pTable->price;
#ifdef __CHEQUE_SYSTEM__
		item.price_cheque = pTable->price_cheque;
#endif
		item.vnum = pkItem->GetVnum();
		item.status = 0;
		for (int i=0; i < ITEM_SOCKET_MAX_NUM; ++i)
			item.alSockets[i] = pkItem->GetSocket(i);
		for (int i=0; i < ITEM_ATTRIBUTE_MAX_NUM; ++i)
		{
			item.aAttr[i].bType = pkItem->GetAttributeType(i);
			item.aAttr[i].sValue = pkItem->GetAttributeValue(i);
		}

#ifdef __BL_TRANSMUTATION__
		item.dwTransmutationVnum = pkItem->GetTransmutationVnum();
#endif

#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		strlcpy(item.szName, pkItem->GetName(), sizeof(item.szName));
		item.refine_level = pkItem->GetRefineLevel();
		item.shop_id = GetOfflineShopNPC()->GetVID();

		char szItemName[ITEM_NAME_MAX_LEN * 2 + 1];
		const std::string strItemName = pkItem->GetName();
		DBManager::instance().EscapeString(szItemName, sizeof(szItemName), strItemName.c_str(), strItemName.length());
#endif

		DBManager::instance().Query("INSERT INTO %soffline_shop_item ("
			"id, owner_id, pos, count"
#ifdef __CHEQUE_SYSTEM__
			", price, price_cheque"
#else
			", price"
#endif
			", vnum"
#ifdef __ITEM_SOCKET5__
			", socket0, socket1, socket2, socket3, socket4, socket5"
#else
			", socket0, socket1, socket2"
#endif
			", attrtype0, attrvalue0"
			", attrtype1, attrvalue1"
			", attrtype2, attrvalue2"
			", attrtype3, attrvalue3"
			", attrtype4, attrvalue4"
			", attrtype5, attrvalue5"
			", attrtype6, attrvalue6"
			", applytype0, applyvalue0"
			", applytype1, applyvalue1"
			", applytype2, applyvalue2"
			", applytype3, applyvalue3"
			", applytype4, applyvalue4"
			", applytype5, applyvalue5"
			", applytype6, applyvalue6"
			", applytype7, applyvalue7"
#ifdef __BL_TRANSMUTATION__
			", transmutation"
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
			", item_name, refine_level, shop_id"
#endif
			") VALUES ("
			"%u, %u, %d, %u" // id, owner_id, pos, count
#ifdef __CHEQUE_SYSTEM__
			", %lld, %d" // price, price_cheque
#else
			", %lld" // price
#endif
			", %u" // vnum
#ifdef __ITEM_SOCKET5__
			", %ld, %ld, %ld, %ld, %ld, %ld" // socket0, socket1, socket2, socket3, socket4, socket5
#else
			", %ld, %ld, %ld" // socket0, socket1, socket2
#endif
			", %d, %d" // attrtype0, attrvalue0
			", %d, %d" // attrtype1, attrvalue1
			", %d, %d" // attrtype2, attrvalue2
			", %d, %d" // attrtype3, attrvalue3
			", %d, %d" // attrtype4, attrvalue4
			", %d, %d" // attrtype5, attrvalue5
			", %d, %d" // attrtype6, attrvalue6
			", %d, %d" // applytype0, applyvalue0
			", %d, %d" // applytype1, applyvalue1
			", %d, %d" // applytype2, applyvalue2
			", %d, %d" // applytype3, applyvalue3
			", %d, %d" // applytype4, applyvalue4
			", %d, %d" // applytype5, applyvalue5
			", %d, %d" // applytype6, applyvalue6
			", %d, %d" // applytype7, applyvalue7
#ifdef __BL_TRANSMUTATION__
			", %u" // dwTransmutationVnum
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
			", '%s', %d, %d" // item_name, refine_level, shop_id
#endif
			")", get_table_postfix(),
			pkItem->GetID(), ch->GetPlayerID(), pTable->display_pos, pkItem->GetCount()
#ifdef __CHEQUE_SYSTEM__
			, pTable->price, pTable->price_cheque
#else
			, pTable->price
#endif
			, pkItem->GetVnum()
#ifdef __ITEM_SOCKET5__
			, pkItem->GetSocket(0)
			, pkItem->GetSocket(1)
			, pkItem->GetSocket(2)
			, pkItem->GetSocket(3)
			, pkItem->GetSocket(4)
			, pkItem->GetSocket(5)
#else
			, pkItem->GetSocket(0)
			, pkItem->GetSocket(1)
			, pkItem->GetSocket(2)
#endif
			, pkItem->GetAttributeType(0), pkItem->GetAttributeValue(0)
			, pkItem->GetAttributeType(1), pkItem->GetAttributeValue(1)
			, pkItem->GetAttributeType(2), pkItem->GetAttributeValue(2)
			, pkItem->GetAttributeType(3), pkItem->GetAttributeValue(3)
			, pkItem->GetAttributeType(4), pkItem->GetAttributeValue(4)
			, pkItem->GetAttributeType(5), pkItem->GetAttributeValue(5)
			, pkItem->GetAttributeType(6), pkItem->GetAttributeValue(6)
			, pkItem->GetAttributeType(7), pkItem->GetAttributeValue(7)
			, pkItem->GetAttributeType(8), pkItem->GetAttributeValue(8)
			, pkItem->GetAttributeType(9), pkItem->GetAttributeValue(9)
			, pkItem->GetAttributeType(10), pkItem->GetAttributeValue(10)
			, pkItem->GetAttributeType(11), pkItem->GetAttributeValue(11)
			, pkItem->GetAttributeType(12), pkItem->GetAttributeValue(12)
			, pkItem->GetAttributeType(13), pkItem->GetAttributeValue(13)
			, pkItem->GetAttributeType(14), pkItem->GetAttributeValue(14)
#ifdef __BL_TRANSMUTATION__
			, pkItem->GetTransmutationVnum()
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
			, szItemName
			, pkItem->GetRefineLevel()
			, (DWORD)GetOfflineShopNPC()->GetVID()
#endif
		);

		ITEM_MANAGER::instance().RemoveItem(pkItem);

		char name[36];
		snprintf(name, sizeof(name), "%-20s(#%-5d) (x %d)", item_table->szName, (int)item.vnum, item.count);

		sys_log(0, "OFFLINE_SHOP_ITEM: %-36s PRICE %-5lld", name, item.price);
		++pTable;
	}
}

#ifdef __CHEQUE_SYSTEM__
void COfflineShop::AddItem(LPCHARACTER ch, LPITEM pkItem, BYTE bPos, long long iPrice, int iPriceCheque)
#else
void COfflineShop::AddItem(LPCHARACTER ch, LPITEM pkItem, BYTE bPos, long long iPrice)
#endif
{
	OFFLINE_SHOP_ITEM & item = m_itemVector[bPos];

	item.id = pkItem->GetID();
	item.owner_id = ch->GetPlayerID();
	item.pos = bPos;
	item.count = pkItem->GetCount();
	item.price = iPrice;
#ifdef __CHEQUE_SYSTEM__
	item.price_cheque = iPriceCheque;
#endif
	item.vnum = pkItem->GetVnum();
	item.status = 0;
	thecore_memcpy(item.alSockets, pkItem->GetSockets(), sizeof(item.alSockets));
	thecore_memcpy(item.aAttr, pkItem->GetAttributes(), sizeof(item.aAttr));
#ifdef __BL_TRANSMUTATION__
	item.dwTransmutationVnum = pkItem->GetTransmutationVnum();
#endif

#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	strlcpy(item.szName, pkItem->GetName(), sizeof(item.szName));
	item.refine_level = pkItem->GetRefineLevel();
	item.shop_id = GetOfflineShopNPC()->GetVID();

	char szItemName[ITEM_NAME_MAX_LEN * 2 + 1];
	const std::string strItemName = pkItem->GetName();
	DBManager::instance().EscapeString(szItemName, sizeof(szItemName), strItemName.c_str(), strItemName.length());
#endif

	DBManager::instance().Query("INSERT INTO %soffline_shop_item ("
		"id, owner_id, pos, count"
#ifdef __CHEQUE_SYSTEM__
		", price, price_cheque"
#else
		", price"
#endif
		", vnum"
#ifdef __ITEM_SOCKET5__
		", socket0, socket1, socket2, socket3, socket4, socket5"
#else
		", socket0, socket1, socket2"
#endif
		", attrtype0, attrvalue0"
		", attrtype1, attrvalue1"
		", attrtype2, attrvalue2"
		", attrtype3, attrvalue3"
		", attrtype4, attrvalue4"
		", attrtype5, attrvalue5"
		", attrtype6, attrvalue6"
		", applytype0, applyvalue0"
		", applytype1, applyvalue1"
		", applytype2, applyvalue2"
		", applytype3, applyvalue3"
		", applytype4, applyvalue4"
		", applytype5, applyvalue5"
		", applytype6, applyvalue6"
		", applytype7, applyvalue7"
#ifdef __BL_TRANSMUTATION__
		", transmutation"
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		", item_name, refine_level, shop_id"
#endif
		") VALUES ("
		"%u, %u, %d, %u" // id, owner_id, pos, count
#ifdef __CHEQUE_SYSTEM__
		", %lld, %d" // price, price_cheque
#else
		", %lld" // price
#endif
		", %u" // vnum
#ifdef __ITEM_SOCKET5__
		", %ld, %ld, %ld, %ld, %ld, %ld" // socket0, socket1, socket2, socket3, socket4, socket5
#else
		", %ld, %ld, %ld" // socket0, socket1, socket2
#endif
		", %d, %d" // attrtype0, attrvalue0
		", %d, %d" // attrtype1, attrvalue1
		", %d, %d" // attrtype2, attrvalue2
		", %d, %d" // attrtype3, attrvalue3
		", %d, %d" // attrtype4, attrvalue4
		", %d, %d" // attrtype5, attrvalue5
		", %d, %d" // attrtype6, attrvalue6
		", %d, %d" // applytype0, applyvalue0
		", %d, %d" // applytype1, applyvalue1
		", %d, %d" // applytype2, applyvalue2
		", %d, %d" // applytype3, applyvalue3
		", %d, %d" // applytype4, applyvalue4
		", %d, %d" // applytype5, applyvalue5
		", %d, %d" // applytype6, applyvalue6
		", %d, %d" // applytype7, applyvalue7
#ifdef __BL_TRANSMUTATION__
		", %u" // dwTransmutationVnum
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		", '%s', %d, %d" // item_name, refine_level, shop_id
#endif
		")", get_table_postfix(),
		pkItem->GetID(), ch->GetPlayerID(), bPos, pkItem->GetCount()
#ifdef __CHEQUE_SYSTEM__
		, iPrice, iPriceCheque
#else
		, iPrice
#endif
		, pkItem->GetVnum()
#ifdef __ITEM_SOCKET5__
		, pkItem->GetSocket(0)
		, pkItem->GetSocket(1)
		, pkItem->GetSocket(2)
		, pkItem->GetSocket(3)
		, pkItem->GetSocket(4)
		, pkItem->GetSocket(5)
#else
		, pkItem->GetSocket(0)
		, pkItem->GetSocket(1)
		, pkItem->GetSocket(2)
#endif
		, pkItem->GetAttributeType(0), pkItem->GetAttributeValue(0)
		, pkItem->GetAttributeType(1), pkItem->GetAttributeValue(1)
		, pkItem->GetAttributeType(2), pkItem->GetAttributeValue(2)
		, pkItem->GetAttributeType(3), pkItem->GetAttributeValue(3)
		, pkItem->GetAttributeType(4), pkItem->GetAttributeValue(4)
		, pkItem->GetAttributeType(5), pkItem->GetAttributeValue(5)
		, pkItem->GetAttributeType(6), pkItem->GetAttributeValue(6)
		, pkItem->GetAttributeType(7), pkItem->GetAttributeValue(7)
		, pkItem->GetAttributeType(8), pkItem->GetAttributeValue(8)
		, pkItem->GetAttributeType(9), pkItem->GetAttributeValue(9)
		, pkItem->GetAttributeType(10), pkItem->GetAttributeValue(10)
		, pkItem->GetAttributeType(11), pkItem->GetAttributeValue(11)
		, pkItem->GetAttributeType(12), pkItem->GetAttributeValue(12)
		, pkItem->GetAttributeType(13), pkItem->GetAttributeValue(13)
		, pkItem->GetAttributeType(14), pkItem->GetAttributeValue(14)
#ifdef __BL_TRANSMUTATION__
		, pkItem->GetTransmutationVnum()
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		, szItemName
		, pkItem->GetRefineLevel()
		, (DWORD)GetOfflineShopNPC()->GetVID()
#endif
	);

	pkItem->RemoveFromCharacter();
	ITEM_MANAGER::instance().FlushDelayedSave(pkItem);

	Refresh(ch);
}

void COfflineShop::RemoveItem(LPCHARACTER ch, BYTE bPos)
{
	OFFLINE_SHOP_ITEM & item = m_itemVector[bPos];
	TPlayerItem item2;

	if (item.status == 2)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> This item has been sold."));
		return;
	}

	item2.id = item.id;
	item2.vnum = item.vnum;
	item2.count = item.count;
	item2.alSockets[0] = item.alSockets[0];
	item2.alSockets[1] = item.alSockets[1];
	item2.alSockets[2] = item.alSockets[2];
#ifdef __ITEM_SOCKET5__
	item2.alSockets[3] = item.alSockets[3];
	item2.alSockets[4] = item.alSockets[4];
	item2.alSockets[5] = item.alSockets[5];
#endif
	for (int j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; j++)
	{
		item2.aAttr[j].bType = item.aAttr[j].bType;
		item2.aAttr[j].sValue = item.aAttr[j].sValue;
	}
#ifdef __BL_TRANSMUTATION__
	item2.dwTransmutationVnum = item.dwTransmutationVnum;
#endif

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

	int iEmptyPos = 0;
	if (pItem->IsDragonSoul())
		iEmptyPos = ch->GetEmptyDragonSoulInventory(pItem);
#ifdef __SPECIAL_INVENTORY_SYSTEM__
	else if (pItem->IsSkillBook())
		iEmptyPos = ch->GetEmptySkillBookInventory(pItem->GetSize());
	else if (pItem->IsUpgradeItem())
		iEmptyPos = ch->GetEmptyUpgradeItemsInventory(pItem->GetSize());
	else if (pItem->IsStone())
		iEmptyPos = ch->GetEmptyStoneInventory(pItem->GetSize());
	else if (pItem->IsGiftBox())
		iEmptyPos = ch->GetEmptyGiftBoxInventory(pItem->GetSize());
	else if (pItem->IsChanger())
		iEmptyPos = ch->GetEmptyChangersInventory(pItem->GetSize());
#endif
	else
		iEmptyPos = ch->GetEmptyInventory(pItem->GetSize());

	if (iEmptyPos < 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("¼ÒÁöÇ°¿¡ ºó °ø°£ÀÌ ¾ø½À´Ï´Ù."));
		return;
	}
	
	if (pItem->IsDragonSoul())
		pItem->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
#ifdef __SPECIAL_INVENTORY_SYSTEM__
	else if (pItem->IsSkillBook())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsUpgradeItem())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsStone())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsGiftBox())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsChanger())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
#endif
	else
		pItem->AddToCharacter(ch, TItemPos(INVENTORY,iEmptyPos));
	
	ITEM_MANAGER::instance().FlushDelayedSave(pItem);

	DBManager::instance().DirectQuery("DELETE FROM %soffline_shop_item WHERE owner_id = %u and pos = %d", get_table_postfix(), ch->GetPlayerID(), bPos);
	memset(&item, 0, sizeof(item));

	LogManager::instance().ItemLog(ch, pItem, "DELETE OFFLINE SHOP ITEM", "");
	BroadcastUpdateItem(bPos, ch->GetPlayerID(), true);
}

bool COfflineShop::AddGuest(LPCHARACTER ch, LPCHARACTER npc)
{
	if (!ch || (ch && !ch->GetDesc()))
		return false;
	
	// if (ch && (ch->HaveAnotherPagesOpen()))
	// {
		// ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		// return false;
	// }

	ch->SetOfflineShop(this);
	#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
	DWORD dwPID = ch->GetPlayerID();
	m_map_guest.emplace_back(dwPID);
	#else
	m_map_guest.insert(GuestMapType::value_type(ch, false));
	#endif

	TPacketGCShop pack;
	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_START;

	TPacketGCOfflineShopStart pack2;
	memset(&pack2, 0, sizeof(pack2));
	pack2.owner_vid = npc->GetVID();
	
	DWORD seePlayerID = ch->GetPlayerID();
	if (!AlreadySeeShop(seePlayerID)) {
		++m_dwDisplayedCount;
		SetAlreadySeeShop(seePlayerID);
	}

	pack2.m_dwDisplayedCount = m_dwDisplayedCount;

	if (GetLeftItemCount() == 0)
	{
		DBManager::instance().DirectQuery("DELETE FROM player.offline_shop_npc WHERE owner_id = %u", npc->GetOfflineShopRealOwner());
		DBManager::instance().DirectQuery("UPDATE %soffline_shop_item SET status = 1 WHERE owner_id = %u and status = 0", get_table_postfix(), npc->GetOfflineShopRealOwner());
		DBManager::instance().DirectQuery("DELETE FROM %soffline_shop_item WHERE owner_id = %u and status = 2", get_table_postfix(), npc->GetOfflineShopRealOwner());
		ch->SetOfflineShop(NULL);
		ch->SetOfflineShopOwner(NULL);
		M2_DESTROY_CHARACTER(npc);
		return false;
	}

	for (DWORD i = 0; i < m_itemVector.size() && i < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++i)
	{
		const OFFLINE_SHOP_ITEM & item = m_itemVector[i];
		if (item.vnum == 0)
			continue;

		pack2.items[item.pos].count = item.count;
		pack2.items[item.pos].vnum = item.vnum;
		pack2.items[item.pos].price = item.price;
#ifdef __CHEQUE_SYSTEM__
		pack2.items[item.pos].price_cheque = item.price_cheque;
#endif
		pack2.items[item.pos].status = item.status;
		strlcpy(pack2.items[item.pos].szBuyerName, item.szBuyerName, sizeof(pack2.items[item.pos].szBuyerName));

		DWORD alSockets[ITEM_SOCKET_MAX_NUM];
		for (int i = 0; i < ITEM_SOCKET_MAX_NUM; ++i)
			alSockets[i] = item.alSockets[i];
		TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_MAX_NUM];

		for (int i = 0; i < ITEM_ATTRIBUTE_MAX_NUM; ++i)
		{
			aAttr[i].bType = item.aAttr[i].bType;
			aAttr[i].sValue = item.aAttr[i].sValue;
		}

#ifdef __BL_TRANSMUTATION__
		pack2.items[item.pos].dwTransmutationVnum = item.dwTransmutationVnum;
#endif

		thecore_memcpy(pack2.items[item.pos].alSockets, alSockets, sizeof(pack2.items[item.pos].alSockets));
		thecore_memcpy(pack2.items[item.pos].aAttr, aAttr, sizeof(pack2.items[item.pos].aAttr));
	}

	pack.size = sizeof(pack) + sizeof(pack2);
	if (ch && ch->GetDesc()) {
		ch->GetDesc()->BufferedPacket(&pack, sizeof(TPacketGCShop));
		ch->GetDesc()->Packet(&pack2, sizeof(TPacketGCOfflineShopStart));
	}
	
	return true;
}

void COfflineShop::SetGuestMap(LPCHARACTER ch)
{
	if (!ch)
		return;
	
	#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
	DWORD dwPID = ch->GetPlayerID();
	auto it = std::find(m_map_guest.begin(), m_map_guest.end(), dwPID);
	if (it != m_map_guest.end())
		return;
	
	m_map_guest.emplace_back(dwPID);
	#else
	GuestMapType::iterator it = m_map_guest.find(ch);
	if (it != m_map_guest.end())
		return;
	m_map_guest.insert(GuestMapType::value_type(ch, false));
	#endif
}

void COfflineShop::RemoveGuestMap(LPCHARACTER ch)
{
	if (!ch)
		return;
	
	if (ch->GetOfflineShop() != this)
		return;
	
	#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
	DWORD dwPID = ch->GetPlayerID();
	auto it = std::find(m_map_guest.begin(), m_map_guest.end(), dwPID);
	if (it != m_map_guest.end())
		m_map_guest.erase(it);
	#else
	m_map_guest.erase(ch);
	#endif
}

void COfflineShop::RemoveGuest(LPCHARACTER ch)
{
	if (!ch || (ch && !ch->GetDesc()))
		return;
	
	if (ch->GetOfflineShop() != this)
		return;

	#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
	DWORD dwPID = ch->GetPlayerID();
	auto it = std::find(m_map_guest.begin(), m_map_guest.end(), dwPID);
	if (it != m_map_guest.end())
		m_map_guest.erase(it);
	#else
	m_map_guest.erase(ch);
	#endif
	ch->SetOfflineShop(NULL);

	TPacketGCShop pack;
	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_END;
	pack.size = sizeof(TPacketGCShop);
	
	if (ch->GetDesc())
		ch->GetDesc()->Packet(&pack, sizeof(pack));
}

void COfflineShop::RemoveAllGuest()
{
	TPacketGCShop pack;
	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_END;
	pack.size = sizeof(TPacketGCShop);

	Broadcast(&pack, sizeof(pack));

#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
	for (auto &idx : m_map_guest) {
		LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(idx);
		if (ch) {
			ch->SetOfflineShop(NULL);
			ch->SetOfflineShopOwner(NULL);
		}
	}
#else
	for (GuestMapType::iterator it = m_map_guest.begin(); it != m_map_guest.end(); ++it)
	{
		LPCHARACTER ch = it->first;
		if (ch) {
			ch->SetOfflineShop(NULL);
			ch->SetOfflineShopOwner(NULL);
		}
	}
#endif
}

void COfflineShop::Destroy(LPCHARACTER npc)
{
	DBManager::instance().DirectQuery("DELETE FROM %soffline_shop_item WHERE owner_id = %u and status = 2", get_table_postfix(), npc->GetOfflineShopRealOwner());
	DBManager::instance().DirectQuery("DELETE FROM %soffline_shop_npc WHERE owner_id = %u", get_table_postfix(), npc->GetOfflineShopRealOwner());
	DBManager::instance().DirectQuery("UPDATE %soffline_shop_item SET status = 1 WHERE owner_id = %u and status = 0", get_table_postfix(), npc->GetOfflineShopRealOwner());
	RemoveAllGuest();
	if (npc)
		M2_DESTROY_CHARACTER(npc);
}

int COfflineShop::Buy(LPCHARACTER ch, BYTE bPos, DWORD item_id, long long llPriceCheck)
{
	if (!ch || (ch && !ch->GetDesc()))
		return SHOP_SUBHEADER_GC_INVALID_POS;
	
	if (ch->GetOfflineShopOwner()->GetOfflineShopRealOwner() == ch->GetPlayerID())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You can not buy items from your own shop."));
		return SHOP_SUBHEADER_GC_BUY_FROM_OWNSHOP;
	}

	if (bPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		sys_log(0, "OfflineShop::Buy : invalid position %d : %s", bPos, ch->GetName());
		return SHOP_SUBHEADER_GC_INVALID_POS;
	}

	sys_log(0, "OfflineShop::Buy : name %s pos %d", ch->GetName(), bPos);

#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
	auto it = std::find(m_map_guest.begin(), m_map_guest.end(), ch->GetPlayerID());
#else
	GuestMapType::iterator it = m_map_guest.find(ch);
#endif
	if (it == m_map_guest.end())
		return SHOP_SUBHEADER_GC_END;

	OFFLINE_SHOP_ITEM& r_item = m_itemVector[bPos];
	
	DWORD dwID = r_item.id;
	long long dwPrice = r_item.price;
#ifdef __CHEQUE_SYSTEM__
	DWORD dwPriceCheque = r_item.price_cheque;
#endif
	DWORD dwItemVnum = r_item.vnum;
#ifdef __EXTENDED_ITEM_COUNT__
	short bCount = r_item.count;
#else
	BYTE bCount = r_item.count;
#endif
	DWORD alSockets[ITEM_SOCKET_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_MAX_NUM];
#ifdef __BL_TRANSMUTATION__
	DWORD dwTransmutation = r_item.dwTransmutationVnum;
#endif

	for (int i = 0; i < ITEM_SOCKET_MAX_NUM; ++i)
		alSockets[i] = r_item.alSockets[i];

	for (int i = 0; i < ITEM_ATTRIBUTE_MAX_NUM; ++i)
	{
		aAttr[i].bType = r_item.aAttr[i].bType;
		aAttr[i].sValue = r_item.aAttr[i].sValue;
	}

	if (r_item.status != 0)
		return SHOP_SUBHEADER_GC_SOLD_OUT;

	unsigned long long llPrice = dwPrice;
	if (llPrice > 0)
	{
		if (ch->GetGold() < llPrice)
		{
			sys_log(1, "Shop::Buy : Not enough money : %s has %lld, price %lld", ch->GetName(), ch->GetGold(), llPrice);
			return SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY;
		}
	}

	// if (g_bBlockGameMasterStuff)
		// if ((ch->IsGM() && !ch->IsAllowedGameMaster()))
			// return SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY;

#ifdef __CHEQUE_SYSTEM__
	if (dwPriceCheque > 0)
	{
		if (ch->GetCheque() < static_cast<DWORD>(dwPriceCheque))
		{
			sys_log(1, "Shop::Buy : Not enough cheque : %s has %d, cheque %d", ch->GetName(), ch->GetCheque(), dwPriceCheque);
			return SHOP_SUBHEADER_GC_NOT_ENOUGH_CHEQUE;
		}
	}
#endif
	
	if (item_id != 0 && (item_id != dwID))
		return SHOP_SUBHEADER_GC_REMOVED_FROM_SHOP;

	if (llPriceCheck != 0 && (llPriceCheck != llPrice))
		return SHOP_SUBHEADER_GC_PRICE_CHANGED;
	
	LPITEM pItem = ITEM_MANAGER::Instance().CreateItem(dwItemVnum, bCount);
	if (!pItem)
		return SHOP_SUBHEADER_GC_SOLD_OUT;
	
	if (pItem->IsDragonSoul() && (ch && !ch->DragonSoul_IsQualified()))
		return SHOP_SUBHEADER_GC_YOU_DONT_HAVE_DS;
	
	pItem->SetAttributes(aAttr);
	for (BYTE i = 0; i < ITEM_SOCKET_MAX_NUM; ++i)
		pItem->SetSocket(i, alSockets[i]);
#ifdef __BL_TRANSMUTATION__
	pItem->SetTransmutationVnum(dwTransmutation);
#endif

	int iEmptyPos = 0;
	if (pItem->IsDragonSoul())
		iEmptyPos = ch->GetEmptyDragonSoulInventory(pItem);
#ifdef __SPECIAL_INVENTORY_SYSTEM__
	else if (pItem->IsSkillBook())
		iEmptyPos = ch->GetEmptySkillBookInventory(pItem->GetSize());
	else if (pItem->IsUpgradeItem())
		iEmptyPos = ch->GetEmptyUpgradeItemsInventory(pItem->GetSize());
	else if (pItem->IsStone())
		iEmptyPos = ch->GetEmptyStoneInventory(pItem->GetSize());
	else if (pItem->IsGiftBox())
		iEmptyPos = ch->GetEmptyGiftBoxInventory(pItem->GetSize());
	else if (pItem->IsChanger())
		iEmptyPos = ch->GetEmptyChangersInventory(pItem->GetSize());
#endif
	else
		iEmptyPos = ch->GetEmptyInventory(pItem->GetSize());

	if (iEmptyPos < 0)
		return SHOP_SUBHEADER_GC_INVENTORY_FULL;

	if (pItem->IsDragonSoul())
		pItem->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
#ifdef __SPECIAL_INVENTORY_SYSTEM__
	else if (pItem->IsSkillBook())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsUpgradeItem())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsStone())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsGiftBox())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
	else if (pItem->IsChanger())
		pItem->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
#endif
	else
		pItem->AddToCharacter(ch, TItemPos(INVENTORY,iEmptyPos));

	if (pItem)
		sys_log(0, "OFFLINE_SHOP: BUY: name %s %s(x %u):%u price %lld", ch->GetName(), pItem->GetName(), pItem->GetCount(), pItem->GetID(), llPrice);

	if (llPrice > 0)
	{
		//Aplica a taxa de 3% na compra de um jogador
		long long llPriceWithFee = llPrice - ((OFFLINE_SHOP_BUY_FEE * llPrice) / 100);
		if (llPriceWithFee < 0 || llPriceWithFee >= llPrice)
			llPriceWithFee = llPrice;
		
		DBManager::instance().DirectQuery("UPDATE %splayer SET shop_gold = shop_gold + %lld WHERE id = %u", get_table_postfix(), llPriceWithFee, ch->GetOfflineShopOwner()->GetOfflineShopRealOwner());
		SetOfflineShopGold(GetOfflineShopGold() + llPriceWithFee);
	}

#ifdef __CHEQUE_SYSTEM__
	if (dwPriceCheque > 0)
	{
		DBManager::instance().DirectQuery("UPDATE %splayer SET shop_cheque = shop_cheque + %d WHERE id = %u", get_table_postfix(), dwPriceCheque, ch->GetOfflineShopOwner()->GetOfflineShopRealOwner());
		SetOfflineShopCheque(GetOfflineShopCheque() + dwPriceCheque);
	}
#endif

	DBManager::instance().DirectQuery("UPDATE %soffline_shop_item SET status = 2 WHERE pos = %d and owner_id = %u", get_table_postfix(), bPos, ch->GetOfflineShopOwner()->GetOfflineShopRealOwner());
	DBManager::instance().DirectQuery("UPDATE %soffline_shop_item SET buyer_name='%s' WHERE pos = %d and owner_id = %u", get_table_postfix(), ch->GetName(), bPos, ch->GetOfflineShopOwner()->GetOfflineShopRealOwner());

	r_item.status = 2;
	strlcpy(r_item.szBuyerName, ch->GetName(), sizeof(r_item.szBuyerName));
	ITEM_MANAGER::instance().FlushDelayedSave(pItem);
	BroadcastUpdateItem(bPos, ch->GetOfflineShopOwner()->GetOfflineShopRealOwner(), false);

	if (llPrice > 0)
		ch->PointChange(POINT_GOLD, -llPrice, false);

#ifdef __CHEQUE_SYSTEM__
	if (dwPriceCheque > 0)
		ch->PointChange(POINT_CHEQUE, -dwPriceCheque, false);
#endif

	if (pItem->GetVnum() >= 55701 && pItem->GetVnum() <= 55710)
	{
		DBManager::instance().DirectQuery("UPDATE new_petsystem SET id =%d WHERE id = %d", pItem->GetID(), pItem->GetAttributeValue(14));
	}

	ch->Save();
	LogManager::instance().ItemLog(ch, pItem, "BUY ITEM FROM OFFLINE SHOP", "");

	{ ///* log sales *///
		char szInsertQuery[QUERY_MAX_LEN];
		snprintf(szInsertQuery, sizeof(szInsertQuery), "INSERT INTO %soffline_shop_sales ("
			"buyer_id, "
			"buyer_name, "
			"item_owner, "
			"item_vnum, "
			"item_count, "
			"item_price, "
#ifdef __CHEQUE_SYSTEM__
			"item_cheque, "
#endif
			"datetime) VALUES("
			"%u, "
			"'%s', "
			"%u, "
			"%u, "
			"%d, "
			"%lld, "
#ifdef __CHEQUE_SYSTEM__
			"%d, "
#endif
			"%u)",
			get_table_postfix(),
			ch->GetPlayerID(),
			ch->GetName(),
			ch->GetOfflineShopOwner()->GetOfflineShopRealOwner(),
			dwItemVnum,
			bCount,
			llPrice,
#ifdef __CHEQUE_SYSTEM__
			dwPriceCheque,
#endif
			get_global_time()
		);
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szInsertQuery));
	}

	///Dá Refresh ao dinheiro do dono da loja em real time
	DWORD dwOwnerPID_s = ch->GetOfflineShopOwner()->GetOfflineShopRealOwner();
	LPCHARACTER ownerChar = CHARACTER_MANAGER::instance().FindByPID(dwOwnerPID_s);
	if (!ownerChar)
	{
		CCI* pcci = P2P_MANAGER::instance().FindByPID(dwOwnerPID_s);
		if (pcci)
		{
			TPacketGGOfflineShopAdviseOwnerSell packetReload;
			packetReload.bHeader = HEADER_GG_OFFLINE_SHOP_ADVISE_PLAYER;
			packetReload.dwOwnerPID = dwOwnerPID_s;
			packetReload.itemSelled = dwItemVnum;
			packetReload.itemPrice = llPrice;
			strlcpy(packetReload.buyerName, ch->GetName(), sizeof(packetReload.buyerName));;
			P2P_MANAGER::instance().Send(&packetReload, sizeof(TPacketGGOfflineShopAdviseOwnerSell));
		}
	}
	else
		COfflineShopManager::instance().AdviseItemSell(ownerChar, dwItemVnum, llPrice, ch->GetName());
	//////
	
	if (m_pkOfflineShopNPC && m_pkOfflineShopNPC->IsOfflineShopNPC())
	{
		if (GetLeftItemCount() <= 0)
			m_pkOfflineShopNPC->DestroyOfflineShop();
	}

	return (SHOP_SUBHEADER_GC_OK);
}

void COfflineShop::BroadcastUpdateItem(BYTE bPos, DWORD dwPID, bool bDestroy)
{
	if (bPos >= m_itemVector.size()) //Check vector position
		return;
	
	TPacketGCShop pack;
	TPacketGCOfflineShopUpdateItem pack2;
	
	TEMP_BUFFER buf;
	
	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_UPDATE_ITEM;
	pack.size = sizeof(pack) + sizeof(pack2);
	
	pack2.pos = bPos;

	if (bDestroy)
	{
		pack2.item.vnum = 0;
		pack2.item.count = 0;
		pack2.item.price = 0;
#ifdef __CHEQUE_SYSTEM__
		pack2.item.price_cheque = 0;
#endif
		pack2.item.status = 0;
		memset(pack2.item.alSockets, 0, sizeof(pack2.item.alSockets));
		memset(pack2.item.aAttr, 0, sizeof(pack2.item.aAttr));
#ifdef __BL_TRANSMUTATION__
		pack2.item.dwTransmutationVnum = 0;
#endif
	}
	else
	{
		pack2.item.count = m_itemVector[bPos].count;
		pack2.item.vnum = m_itemVector[bPos].vnum;
		pack2.item.price = m_itemVector[bPos].price;
#ifdef __CHEQUE_SYSTEM__
		pack2.item.price_cheque = m_itemVector[bPos].price_cheque;
#endif
		pack2.item.status = m_itemVector[bPos].status;
		strlcpy(pack2.item.szBuyerName, m_itemVector[bPos].szBuyerName, sizeof(pack2.item.szBuyerName));
		thecore_memcpy(pack2.item.alSockets, m_itemVector[bPos].alSockets, sizeof(pack2.item.alSockets));
		thecore_memcpy(pack2.item.aAttr, m_itemVector[bPos].aAttr, sizeof(pack2.item.aAttr));
#ifdef __BL_TRANSMUTATION__
		pack2.item.dwTransmutationVnum = m_itemVector[bPos].dwTransmutationVnum;
#endif
	}

	buf.write(&pack, sizeof(pack));
	buf.write(&pack2, sizeof(pack2));
	
	Broadcast(buf.read_peek(), buf.size());

	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwPID);
	if (!ch)
	{
		CCI* pcci = P2P_MANAGER::instance().FindByPID(dwPID);
		if (pcci)
			RefreshP2P(dwPID);
	}
	else
		Refresh(ch);
}

void COfflineShop::BroadcastUpdatePrice(DWORD dwPID, BYTE bPos, long long dwPrice)
{
	TPacketGCShop pack;
	TPacketGCShopUpdatePrice pack2;

	TEMP_BUFFER buf;

	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_UPDATE_PRICE;
	pack.size = sizeof(pack) + sizeof(pack2);

	pack2.bPos = bPos;
	pack2.dwShopVid = (DWORD)(GetOfflineShopNPC() ? GetOfflineShopNPC()->GetVID() : 0);
	pack2.iPrice = dwPrice;

	buf.write(&pack, sizeof(pack));
	buf.write(&pack2, sizeof(pack2));

	Broadcast(buf.read_peek(), buf.size());
	BroadcastUpdateItem(bPos, dwPID, false);
}

void COfflineShop::Refresh(LPCHARACTER ch)
{
	if (!ch || (ch && !ch->GetDesc()))
		return;
	
	TPacketGCShop pack;
	pack.header = HEADER_GC_OFFLINE_SHOP;
	pack.subheader = SHOP_SUBHEADER_GC_UPDATE_ITEM2;

	TPacketGCOfflineShopStart pack2;
	memset(&pack2, 0, sizeof(pack2));
	pack2.owner_vid = 0;
	pack2.m_dwDisplayedCount = m_dwDisplayedCount;

	for (DWORD i = 0; i < m_itemVector.size() && i < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++i)
	{
		const OFFLINE_SHOP_ITEM & item = m_itemVector[i];
		if (item.vnum == 0)
			continue;

		pack2.items[item.pos].count = item.count;
		pack2.items[item.pos].vnum = item.vnum;
		pack2.items[item.pos].price = item.price;
		pack2.items[item.pos].status = item.status;
		strlcpy(pack2.items[item.pos].szBuyerName, item.szBuyerName, sizeof(pack2.items[item.pos].szBuyerName));
		thecore_memcpy(pack2.items[item.pos].alSockets, item.alSockets, sizeof(pack2.items[item.pos].alSockets));
		thecore_memcpy(pack2.items[item.pos].aAttr, item.aAttr, sizeof(pack2.items[item.pos].aAttr));
#ifdef __BL_TRANSMUTATION__
		pack2.items[item.pos].dwTransmutationVnum = item.dwTransmutationVnum;
#endif
	}

	pack.size = sizeof(pack) + sizeof(pack2);
	if (ch->GetDesc()) {
		ch->GetDesc()->BufferedPacket(&pack, sizeof(TPacketGCShop));
		ch->GetDesc()->Packet(&pack2, sizeof(TPacketGCOfflineShopStart));
	}
}

bool COfflineShop::RemoveItem(DWORD dwVID, BYTE bPos)
{
	DBManager::instance().Query("DELETE FROM %soffline_shop_item WHERE owner_id = %u and pos = %d", get_table_postfix(), dwVID, bPos);
	return true;
}

BYTE COfflineShop::GetLeftItemCount()
{
	BYTE bCount = 0;
	for (int i = 0; i < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++i)
	{
		const OFFLINE_SHOP_ITEM & item = m_itemVector[i];
		if (item.vnum == 0)
			continue;
		if (item.status == 0)
			bCount++;
	}

	return bCount;
}

void COfflineShop::Broadcast(const void* data, int bytes)
{
	if (!data || !bytes)
		return;
	
	if (test_server)
		sys_log(1, "OfflineShop::Broadcast %p %d", data, bytes);

#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
	for (auto &idx : m_map_guest) {
		LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(idx);
		LPDESC d = nullptr;
		if (!ch || (ch && !(d = ch->GetDesc())))
			continue;
		
		d->Packet(data, bytes);
	}
#else
	GuestMapType::iterator it = m_map_guest.begin();
	while (it != m_map_guest.end())
	{
		LPCHARACTER ch = it->first;
		
		if (!ch || (ch && !ch->GetDesc()))
			continue;
		
		ch->GetDesc()->Packet(data, bytes);
		++it;
	}
#endif
}

/*
	Overfall2 Work
*/

void COfflineShop::RefreshP2P(DWORD dwPID)
{
	TPacketGCOfflineShopStartP2P pack2;
	pack2.header = HEADER_GC_OFFLINE_SHOP_START_P2P;
	pack2.owner_vid = dwPID;
	pack2.m_dwDisplayedCount = m_dwDisplayedCount;

	for (DWORD i = 0; i < m_itemVector.size() && i < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++i)
	{
		const OFFLINE_SHOP_ITEM & item = m_itemVector[i];
		if (item.vnum == 0)
			continue;

		pack2.items[item.pos].count = item.count;
		pack2.items[item.pos].vnum = item.vnum;
		pack2.items[item.pos].price = item.price;
		pack2.items[item.pos].status = item.status;
		strlcpy(pack2.items[item.pos].szBuyerName, item.szBuyerName, sizeof(pack2.items[item.pos].szBuyerName));
		thecore_memcpy(pack2.items[item.pos].alSockets, item.alSockets, sizeof(pack2.items[item.pos].alSockets));
		thecore_memcpy(pack2.items[item.pos].aAttr, item.aAttr, sizeof(pack2.items[item.pos].aAttr));
#ifdef __BL_TRANSMUTATION__
		pack2.items[item.pos].dwTransmutationVnum = item.dwTransmutationVnum;
#endif
	}
	
	CCI* pcci = P2P_MANAGER::instance().FindByPID(dwPID);
	if (!pcci || (pcci && !pcci->pkDesc))
		return;
	
	pcci->pkDesc->SetRelay(pcci->szName);
	pcci->pkDesc->Packet(&pack2, sizeof(pack2));
	pcci->pkDesc->SetRelay("");
}

void COfflineShop::AddItemP2P(DWORD dwPID, TOfflineShopItem pkItem, BYTE bPos, long long iPrice)
{
	if (bPos >= m_itemVector.size()) //Check vector position
		return;
	
	OFFLINE_SHOP_ITEM & item = m_itemVector[bPos];
	
	item.id = pkItem.id;
	item.owner_id = pkItem.owner_id;
	item.pos = pkItem.pos;
	item.count = pkItem.count;
	item.price = pkItem.price;
	item.vnum = pkItem.vnum;
	memcpy(item.alSockets, pkItem.alSockets, sizeof(item.alSockets));
	memcpy(item.aAttr, pkItem.aAttr, sizeof(item.aAttr));
	item.status = pkItem.status;
	#ifdef __BL_TRANSMUTATION__
	item.dwTransmutationVnum = pkItem.dwTransmutationVnum;
	#endif
	#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	strlcpy(item.szName, pkItem.szName, sizeof(item.szName));
	item.refine_level = pkItem.refine_level;
	item.shop_id = (DWORD)GetOfflineShopNPC()->GetVID();
	#endif

#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	char szItemName[ITEM_NAME_MAX_LEN * 2 + 1];
	const std::string strItemName = item.szName;
	DBManager::instance().EscapeString(szItemName, sizeof(szItemName), strItemName.c_str(), strItemName.length());
#endif

	DBManager::instance().Query("INSERT INTO %soffline_shop_item ("
		"id, owner_id, pos, count"
#ifdef __CHEQUE_SYSTEM__
		", price, price_cheque"
#else
		", price"
#endif
		", vnum"
#ifdef __ITEM_SOCKET5__
		", socket0, socket1, socket2, socket3, socket4, socket5"
#else
		", socket0, socket1, socket2"
#endif
		", attrtype0, attrvalue0"
		", attrtype1, attrvalue1"
		", attrtype2, attrvalue2"
		", attrtype3, attrvalue3"
		", attrtype4, attrvalue4"
		", attrtype5, attrvalue5"
		", attrtype6, attrvalue6"
		", applytype0, applyvalue0"
		", applytype1, applyvalue1"
		", applytype2, applyvalue2"
		", applytype3, applyvalue3"
		", applytype4, applyvalue4"
		", applytype5, applyvalue5"
		", applytype6, applyvalue6"
		", applytype7, applyvalue7"
#ifdef __BL_TRANSMUTATION__
		", transmutation"
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		", item_name, refine_level, shop_id"
#endif
		") VALUES ("
		"%u, %u, %d, %u" // id, owner_id, pos, count
#ifdef __CHEQUE_SYSTEM__
		", %lld, %d" // price, price_cheque
#else
		", %lld" // price
#endif
		", %u" // vnum
#ifdef __ITEM_SOCKET5__
		", %ld, %ld, %ld, %ld, %ld, %ld" // socket0, socket1, socket2, socket3, socket4, socket5
#else
		", %ld, %ld, %ld" // socket0, socket1, socket2
#endif
		", %d, %d" // attrtype0, attrvalue0
		", %d, %d" // attrtype1, attrvalue1
		", %d, %d" // attrtype2, attrvalue2
		", %d, %d" // attrtype3, attrvalue3
		", %d, %d" // attrtype4, attrvalue4
		", %d, %d" // attrtype5, attrvalue5
		", %d, %d" // attrtype6, attrvalue6
		", %d, %d" // applytype0, applyvalue0
		", %d, %d" // applytype1, applyvalue1
		", %d, %d" // applytype2, applyvalue2
		", %d, %d" // applytype3, applyvalue3
		", %d, %d" // applytype4, applyvalue4
		", %d, %d" // applytype5, applyvalue5
		", %d, %d" // applytype6, applyvalue6
		", %d, %d" // applytype7, applyvalue7
#ifdef __BL_TRANSMUTATION__
		", %u" // dwTransmutationVnum
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		", '%s', %d, %d" // item_name, refine_level, shop_id
#endif
		")", get_table_postfix(),
		item.id, dwPID, bPos, item.count
#ifdef __CHEQUE_SYSTEM__
		, iPrice, iPriceCheque
#else
		, iPrice
#endif
		, item.vnum
#ifdef __ITEM_SOCKET5__
		, item.alSockets[0]
		, item.alSockets[1]
		, item.alSockets[2]
		, item.alSockets[3]
		, item.alSockets[4]
		, item.alSockets[5]
#else
		, item.alSockets[0]
		, item.alSockets[1]
		, item.alSockets[2]
#endif
		, item.aAttr[0].bType, item.aAttr[0].sValue
		, item.aAttr[1].bType, item.aAttr[1].sValue
		, item.aAttr[2].bType, item.aAttr[2].sValue
		, item.aAttr[3].bType, item.aAttr[3].sValue
		, item.aAttr[4].bType, item.aAttr[4].sValue
		, item.aAttr[5].bType, item.aAttr[5].sValue
		, item.aAttr[6].bType, item.aAttr[6].sValue
		, item.aAttr[7].bType, item.aAttr[7].sValue
		, item.aAttr[8].bType, item.aAttr[8].sValue
		, item.aAttr[9].bType, item.aAttr[9].sValue
		, item.aAttr[10].bType, item.aAttr[10].sValue
		, item.aAttr[11].bType, item.aAttr[11].sValue
		, item.aAttr[12].bType, item.aAttr[12].sValue
		, item.aAttr[13].bType, item.aAttr[13].sValue
		, item.aAttr[14].bType, item.aAttr[14].sValue
#ifdef __BL_TRANSMUTATION__
		, item.dwTransmutationVnum
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		, szItemName
		, item.refine_level
		, item.shop_id
#endif
	);

	RefreshP2P(dwPID);
}

void COfflineShop::RemoveItemP2P(DWORD dwPID, BYTE bPos)
{
	OFFLINE_SHOP_ITEM & item = m_itemVector[bPos];
	TPlayerItem item2;

	CCI* pcci = P2P_MANAGER::instance().FindByPID(dwPID);
	if (!pcci || (pcci && !pcci->pkDesc))
		return;
	
	if (item.status == 2)
	{
		pcci->pkDesc->SetRelay(pcci->szName);
		pcci->pkDesc->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> This item has been sold."));
		pcci->pkDesc->SetRelay("");
		return;
	}

	item2.id = item.id;
	item2.vnum = item.vnum;
	item2.count = item.count;
	item2.alSockets[0] = item.alSockets[0];
	item2.alSockets[1] = item.alSockets[1];
	item2.alSockets[2] = item.alSockets[2];
#ifdef __ITEM_SOCKET5__
	item2.alSockets[3] = item.alSockets[3];
	item2.alSockets[4] = item.alSockets[4];
	item2.alSockets[5] = item.alSockets[5];
#endif
	for (int j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; j++)
	{
		item2.aAttr[j].bType = item.aAttr[j].bType;
		item2.aAttr[j].sValue = item.aAttr[j].sValue;
	}
#ifdef __BL_TRANSMUTATION__
	item2.dwTransmutationVnum = item.dwTransmutationVnum;
#endif

	TPacketGGRemoveOfflineShopItem p;
	p.bHeader = HEADER_GG_OFFLINE_SHOP_REMOVE_ITEM;
	p.bSubHeader = OFFLINE_SHOP_FORCE_REMOVE_ITEM;
	p.dwOwnerPID = dwPID;
	p.bPos = bPos;
	p.item = item2;
	P2P_MANAGER::instance().Send(&p, sizeof(TPacketGGRemoveOfflineShopItem));
	
	DBManager::instance().DirectQuery("DELETE FROM %soffline_shop_item WHERE owner_id = %u and pos = %d", get_table_postfix(), dwPID, bPos);
	memset(&item, 0, sizeof(item));

	BroadcastUpdateItem(bPos, dwPID, true);
}


void COfflineShop::SetOfflineShopBorderStyle(BYTE bBorderStyle)
{
	m_pkOfflineShopBorderStyle = bBorderStyle;
}

bool COfflineShop::ChangeItemPrice(DWORD dwPID, BYTE bPos, long long llPrice)
{
	OFFLINE_SHOP_ITEM & item = m_itemVector[bPos];
	TPlayerItem item2;

	if (item.status == 2)
		return false;
	
	item.price = llPrice;
	
	DBManager::instance().DirectQuery("UPDATE %soffline_shop_item SET price = %lld WHERE owner_id = %u and pos = %d", get_table_postfix(), llPrice, dwPID, bPos);
	BroadcastUpdatePrice(dwPID, bPos, llPrice);
	
	return true;
}

long long COfflineShop::GetOfflineShopItemPrice(BYTE bPos)
{
	OFFLINE_SHOP_ITEM & item = m_itemVector[bPos];
	return item.price;
}

