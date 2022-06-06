//definelere ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#include "offlineshop_manager.h"
#include "sectree_manager.h"
#endif

//arat

void CInputP2P::IamAwake(LPDESC d, const char * c_pData)

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
struct FFindOfflineShop
{
	const char* szName;

	FFindOfflineShop(const char* c_szName) : szName(c_szName) {};

	void operator()(LPENTITY ent)
	{
		if (!ent)
			return;

		if (ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER ch = (LPCHARACTER)ent;
			if (ch->IsOfflineShopNPC() && !strcmp(szName, ch->GetName()))
				ch->DestroyOfflineShop();
		}
	}
};

struct FChangeOfflineShopTime
{
	int iTime;
	DWORD dwOwnerPID;

	FChangeOfflineShopTime(int time, DWORD dwOwner) : iTime(time), dwOwnerPID(dwOwner) {};

	void operator()(LPENTITY ent)
	{
		if (!ent)
			return;

		if (ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER ch = (LPCHARACTER)ent;
			if (ch->IsOfflineShopNPC() && ch->GetOfflineShopRealOwner() == dwOwnerPID)
			{
				DBManager::instance().DirectQuery("UPDATE %soffline_shop_npc SET time = time + %d WHERE owner_id = %u", get_table_postfix(), iTime, dwOwnerPID);
				ch->StopOfflineShopUpdateEvent();
				ch->SetOfflineShopTimer(iTime);
				ch->StartOfflineShopUpdateEvent();
			}
		}
	}
};

void CInputP2P::RemoveOfflineShop(LPDESC d, const char* c_pData)
{
	TPacketGGRemoveOfflineShop* p = (TPacketGGRemoveOfflineShop*)c_pData;
	LPSECTREE_MAP pMap = SECTREE_MANAGER::instance().GetMap(p->lMapIndex);

	if (pMap)
	{
		FFindOfflineShop offlineshop(p->szNpcName);
		pMap->for_each(offlineshop);
	}
}

void CInputP2P::ChangeOfflineShopTime(LPDESC d, const char* c_pData)
{
	TPacketGGChangeOfflineShopTime* p = (TPacketGGChangeOfflineShopTime*)c_pData;

	int iTime = p->bTime * 60;

	LPSECTREE_MAP pMap = SECTREE_MANAGER::instance().GetMap(p->lMapIndex);
	FChangeOfflineShopTime offlineShopTime(iTime, p->dwOwnerPID);
	if (pMap)
		pMap->for_each(offlineShopTime);
}

void CInputP2P::OfflineShopBuy(LPDESC d, const char* c_pData)
{
	TPacketGGOfflineShopBuy* p = (TPacketGGOfflineShopBuy*)c_pData;
}

void CInputP2P::LoadOfflineShopPanelData(LPDESC d, const char* c_pData)
{
	TPacketGGOpenOffShopPanel* p = (TPacketGGOpenOffShopPanel*)c_pData;
	DWORD dwOwnerPID = p->dwOwnerPID;
	BYTE shopChannel = p->shopChannel;
	
	switch(p->bSubHeader)
	{
		case OFFLINE_SHOP_PANEL_SEARCH_SHOP:
			{
				DWORD offShopVID = COfflineShopManager::instance().FindMyOfflineShop(dwOwnerPID);
				if (!offShopVID)
					return;
				
				COfflineShopManager::instance().RefreshP2P(dwOwnerPID);
				
				long shop_map_index = COfflineShopManager::instance().GetMapIndex(dwOwnerPID);
				int shop_left_time = COfflineShopManager::instance().GetLeftTime(dwOwnerPID);
				const char* shopName = COfflineShopManager::instance().GetOfflineShopSign(dwOwnerPID);
				DWORD displayedCount = COfflineShopManager::instance().GetDisplayedCount(dwOwnerPID);

				TPacketGGOpenOffShopPanel sendShopData;
				sendShopData.bHeader = HEADER_GG_OFFLINE_SHOP_OPEN_PANEL;
				sendShopData.bSubHeader = OFFLINE_SHOP_PANEL_SEND_DATA;
				sendShopData.lMapIndex = shop_map_index;
				sendShopData.iTime = shop_left_time;
				sendShopData.shopChannel = shopChannel;
				sendShopData.dwOwnerPID = dwOwnerPID;
				sendShopData.displayedCount = displayedCount;
				strlcpy(sendShopData.shopName, shopName, sizeof(sendShopData.shopName));
				
				P2P_MANAGER::instance().Send(&sendShopData, sizeof(TPacketGGOpenOffShopPanel));
			}
			break;
		case OFFLINE_SHOP_PANEL_SEND_DATA:
			{
				LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwOwnerPID);
				if (!ch)
					return;
				
				bool hasShop = ch->HasOfflineShop();
				if (!hasShop) {
					sys_log(0, "OFFLINE_SHOP_PANEL_SEND_DATA - Player %s searching data without offline shop!", ch->GetName());
					return;
				}
				
				long shop_map_index = p->lMapIndex;
				int shop_left_time = p->iTime;
				const char * shop_name = p->shopName;
				DWORD displayedCount = p->displayedCount;
				ch->OfflineShopPanelPacket(static_cast<BYTE>(hasShop), shop_name, shop_map_index, shopChannel, shop_left_time, displayedCount);
			}
			break;
		default:
			return;
	}
}

void CInputP2P::AddOfflineShopItemData(LPDESC d, const char* c_pData)
{
	TPacketGGAddOfflineShopItem* p = (TPacketGGAddOfflineShopItem*)c_pData;
	DWORD dwOwnerPID = p->dwOwnerPID;
	
	DWORD offShopVID = COfflineShopManager::instance().FindMyOfflineShop(dwOwnerPID);
	if (!offShopVID)
		return;
	COfflineShopManager::instance().AddItemP2P(dwOwnerPID, p->itemAdd, p->pos, p->price);
}

void CInputP2P::RemoveOfflineShopItemData(LPDESC d, const char* c_pData)
{
	TPacketGGRemoveOfflineShopItem* p = (TPacketGGRemoveOfflineShopItem*)c_pData;
	DWORD dwOwnerPID = p->dwOwnerPID;
	
	switch (p->bSubHeader)
	{
		case OFFLINE_SHOP_SEND_REMOVE_ITEM:
			{
				DWORD offShopVID = COfflineShopManager::instance().FindMyOfflineShop(dwOwnerPID);
				if (!offShopVID)
					return;
				
				COfflineShopManager::instance().RemoveItemP2P(dwOwnerPID, p->bPos);
			}
			break;
		case OFFLINE_SHOP_FORCE_REMOVE_ITEM:
			{
				LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwOwnerPID);
				if (!ch)
					return;
				
				COfflineShopManager::instance().GiveItemP2P(dwOwnerPID, p->item);
			}
			break;
		default:
			return;
	}
}

void CInputP2P::CloseOfflineShopData(LPDESC d, const char* c_pData)
{
	TPacketGGOfflineShopClose* p = (TPacketGGOfflineShopClose*)c_pData;
	DWORD dwOwnerPID = p->dwOwnerPID;
	
	DWORD offShopVID = COfflineShopManager::instance().FindMyOfflineShop(dwOwnerPID);
	if (!offShopVID)
		return;

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(offShopVID);
	if (!npc)
		return;

	if (!COfflineShopManager::instance().CanCloseOfflineShopP2P(dwOwnerPID))
		return;
	
	COfflineShopManager::instance().DestroyOfflineShop(NULL, npc->GetVID(), false);
}

void CInputP2P::ChangeOfflineShopName(LPDESC d, const char* c_pData)
{
	TPacketGGOfflineShopChangeName* p = (TPacketGGOfflineShopChangeName*)c_pData;
	DWORD dwOwnerPID = p->dwOwnerPID;
	const char * szShopName = p->szSign;
	
	DWORD offShopVID = COfflineShopManager::instance().FindMyOfflineShop(dwOwnerPID);
	if (!offShopVID)
		return;
	
	COfflineShopManager::instance().ChangeOfflineShopName(dwOwnerPID, szShopName);
}

void CInputP2P::AdviseOfflineShopSellOwner(LPDESC d, const char* c_pData)
{
	TPacketGGOfflineShopAdviseOwnerSell* p = (TPacketGGOfflineShopAdviseOwnerSell*)c_pData;
	DWORD dwOwnerPID = p->dwOwnerPID;
	

	LPCHARACTER ch = CHARACTER_MANAGER::instance().FindByPID(dwOwnerPID);
	if (!ch)
		return;
	
	COfflineShopManager::instance().AdviseItemSell(ch, p->itemSelled, p->itemPrice, p->buyerName);
}

void CInputP2P::ChangeOfflineShopItemPrice(LPDESC d, const char* c_pData)
{
	TPacketGGChangeOfflineShopItemPrice* p = (TPacketGGChangeOfflineShopItemPrice*)c_pData;
	DWORD dwOwnerPID = p->dwOwnerPID;
	
	DWORD offShopVID = COfflineShopManager::instance().FindMyOfflineShop(dwOwnerPID);
	if (!offShopVID)
		return;
	
	COfflineShopManager::instance().ChangeOfflineShopItemPriceP2P(dwOwnerPID, p->bPos, p->llPrice);
}
#endif

//arat

case HEADER_GG_CHECK_AWAKENESS:

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
		case HEADER_GG_REMOVE_OFFLINE_SHOP:
			RemoveOfflineShop(d, c_pData);
			break;

		case HEADER_GG_CHANGE_OFFLINE_SHOP_TIME:
			ChangeOfflineShopTime(d, c_pData);
			break;

		case HEADER_GG_OFFLINE_SHOP_OPEN_PANEL:
			LoadOfflineShopPanelData(d, c_pData);
			break;
		
		case HEADER_GG_OFFLINE_SHOP_ADD_ITEM:
			AddOfflineShopItemData(d, c_pData);
			break;
		
		case HEADER_GG_OFFLINE_SHOP_REMOVE_ITEM:
			RemoveOfflineShopItemData(d, c_pData);
			break;
		
		case HEADER_GG_OFFLINE_SHOP_CLOSE_SHOP:
			CloseOfflineShopData(d, c_pData);
			break;
		
		case HEADER_GG_OFFLINE_SHOP_CHANGE_NAME:
			ChangeOfflineShopName(d, c_pData);
			break;
		
		case HEADER_GG_OFFLINE_SHOP_ADVISE_PLAYER:
			AdviseOfflineShopSellOwner(d, c_pData);
			break;
		
		case HEADER_GG_OFFLINE_SHOP_CHANGE_ITEM_PRICE:
			ChangeOfflineShopItemPrice(d, c_pData);
			break;
#endif