//definelere ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
#include "PythonPrivateShopSearch.h"
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
#include "PythonNewPrivateShopSearch.h"
#include "AbstractApplication.h"
#endif

//arat

bool CPythonNetworkStream::SendItemUsePacket(TItemPos pos)

//üstüne ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
bool CPythonNetworkStream::SendOfflineShopEndPacket()
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGOfflineShop packet_shop;
	packet_shop.header = HEADER_CG_OFFLINE_SHOP;
	packet_shop.subheader = SHOP_SUBHEADER_CG_END;

	if (!Send(sizeof(packet_shop), &packet_shop))
	{
		Tracef("SendOfflineShopEndPacket Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopBuyPacket(BYTE bPos)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_BUY;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendOfflineShopBuyPacket Error\n");
		return false;
	}

	BYTE bCount = 1;
	if (!Send(sizeof(BYTE), &bCount))
	{
		Tracef("SendOfflineShopBuyPacket Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bPos))
	{
		Tracef("SendOfflineShopBuyPacket Error\n");
		return false;
	}

	return SendSequence();
}

#ifdef ENABLE_CHEQUE_SYSTEM
bool CPythonNetworkStream::SendAddOfflineShopItem(TItemPos bDisplayPos, BYTE bPos, long long iPrice, int iPriceCheque)
#else
bool CPythonNetworkStream::SendAddOfflineShopItem(TItemPos bDisplayPos, BYTE bPos, long long iPrice)
#endif
{
	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_ADD_ITEM;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendAddOfflineShopItem Error\n");
		return false;
	}

	TOfflineShopItemTable2 pTable;

	pTable.bDisplayPos = bDisplayPos;
	pTable.bPos = bPos;
	pTable.dwPrice = iPrice;
#ifdef ENABLE_CHEQUE_SYSTEM
	pTable.dwPriceCheque = iPriceCheque;
#endif

	if (!Send(sizeof(TOfflineShopItemTable2), &pTable))
	{
		Tracef("SendAddOfflineShopItem Error\n");
		return false;
	}

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "wndOfflineShopManager", Py_BuildValue("()"));

	return SendSequence();
}

bool CPythonNetworkStream::SendRemoveOfflineShopItem(BYTE bPos)
{
	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_REMOVE_ITEM;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendRemoveOfflineShopItem Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bPos))
	{
		Tracef("SendRemoveOfflineShopItem Packet Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendDestroyOfflineShop()
{
	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_DESTROY_OFFLINE_SHOP;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendDestroyOfflineShop Packet Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendRefreshOfflineShop(int iDelay)
{
	if (iDelay > 0)
	{
		static DWORD s_LastTime = timeGetTime() - (iDelay + 1);
		if (timeGetTime() - s_LastTime < iDelay)
			return true;

		s_LastTime = timeGetTime();
	}

	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_REFRESH;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendRefreshOfflineShop Error\n");
		return false;
	}

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "wndOfflineShopManager", Py_BuildValue("()"));

	return SendSequence();
}

bool CPythonNetworkStream::SendRefreshUnsoldItems()
{
	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_REFRESH_UNSOLD_ITEMS;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendRefreshUnsoldItems Error\n");
		return false;
	}

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "wndOfflineShopManager", Py_BuildValue("()"));

	return SendSequence();
}

bool CPythonNetworkStream::SendRefreshOfflineShopMoney(int iDelay)
{
	if (iDelay > 0)
	{
		static DWORD s_LastTime = timeGetTime() - (iDelay + 1);
		if (timeGetTime() - s_LastTime < iDelay)
			return true;

		s_LastTime = timeGetTime();
	}

	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_REFRESH_MONEY;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendRefreshOfflineShopMoney Packet Error\n");
		return false;
	}

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "wndOfflineShopManager", Py_BuildValue("()"));

	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopWithdrawMoney(long long llMoney)
{
	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_WITHDRAW_MONEY;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendOfflineShopWithdrawMoney Packet Error\n");
		return false;
	}

	if (!Send(sizeof(llMoney), &llMoney))
	{
		Tracef("SendOfflineShopWithdrawMoney Packet Error \n");
		return false;
	}

	return SendSequence();
}

#ifdef ENABLE_CHEQUE_SYSTEM
bool CPythonNetworkStream::SendOfflineShopWithdrawCheque(DWORD dwCheque)
{
	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_WITHDRAW_CHEQUE;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendOfflineShopWithdrawCheque Packet Error\n");
		return false;
	}

	if (!Send(sizeof(dwCheque), &dwCheque))
	{
		Tracef("SendOfflineShopWithdrawCheque Packet Error \n");
		return false;
	}

	return SendSequence();
}
#endif

bool CPythonNetworkStream::SendOfflineShopTakeItem(BYTE bDisplayPos)
{
	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_TAKE_ITEM;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendOfflineShopTakeItem Packet error\n");
		return false;
	}

	if (!Send(sizeof(bDisplayPos), &bDisplayPos))
	{
		Tracef("SendOfflineShopTakeItem Packet error\n");
		return false;
	}
	
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopChangeItemPrice(BYTE bDisplayPos, long long llPrice)
{
	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHANGE_ITEM_PRICE;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendOfflineShopChangeItemPrice Packet error\n");
		return false;
	}

	if (!Send(sizeof(bDisplayPos), &bDisplayPos))
	{
		Tracef("SendOfflineShopChangeItemPrice Packet error\n");
		return false;
	}

	if (!Send(sizeof(llPrice), &llPrice))
	{
		Tracef("SendOfflineShopChangeItemPrice Packet error\n");
		return false;
	}
	
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopCheck(int iDelay)
{
	if (iDelay > 0)
	{
		static DWORD s_LastTime = timeGetTime() - (iDelay + 1);
		if (timeGetTime() - s_LastTime < iDelay)
			return true;

		s_LastTime = timeGetTime();
	}

	TPacketCGOfflineShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHECK;

	if (!Send(sizeof(TPacketCGOfflineShop), &PacketShop))
	{
		Tracef("SendOfflineShopCheck Packet error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendChangeOfflineShopName(const char * szShopName)
{
	TPacketCGChangeOfflineShopName PacketShop;
	PacketShop.bHeader = HEADER_CG_OFFLINE_SHOP_CHANGE_SHOP_NAME;
	strncpy(PacketShop.szSign, szShopName, SHOP_SIGN_MAX_LEN);
	
	if (!Send(sizeof(TPacketCGChangeOfflineShopName), &PacketShop))
	{
		Tracef("SendChangeOfflineShopName Packet error\n");
		return false;
	}

	return SendSequence();
}
#endif

//en alta ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
#ifdef ENABLE_CHEQUE_SYSTEM
bool CPythonNetworkStream::SendPrivateShopSearchInfo(int32_t Race, int32_t ItemCat, int32_t SubCat, int32_t MinLevel, int32_t MaxLevel, int32_t MinRefine, int32_t MaxRefine, uint64_t MinGold, uint64_t MaxGold, uint64_t MinCheque, uint64_t MaxCheque)
#else
bool CPythonNetworkStream::SendPrivateShopSearchInfo(int32_t Race, int32_t ItemCat, int32_t SubCat, int32_t MinLevel, int32_t MaxLevel, int32_t MinRefine, int32_t MaxRefine, uint64_t MinGold, uint64_t MaxGold)
#endif
{
	if (!__CanActMainInstance())
	{
		return true;
	}

	TPacketCGShopSearch ShopSearchPacket;
	ShopSearchPacket.header = HEADER_CG_SHOP_SEARCH;
	ShopSearchPacket.Race = Race;
	ShopSearchPacket.ItemCat = ItemCat;
	ShopSearchPacket.SubCat = SubCat;
	ShopSearchPacket.MinLevel = MinLevel;
	ShopSearchPacket.MaxLevel = MaxLevel;
	ShopSearchPacket.MinRefine = MinRefine;
	ShopSearchPacket.MaxRefine = MaxRefine;
	ShopSearchPacket.MinGold = MinGold;
	ShopSearchPacket.MaxGold = MaxGold;
#ifdef ENABLE_CHEQUE_SYSTEM
	ShopSearchPacket.MinCheque = MinCheque;
	ShopSearchPacket.MaxCheque = MaxCheque;
#endif

	if (!Send(sizeof(ShopSearchPacket), &ShopSearchPacket))
	{
		Tracen("SendPrivateShopSearchInfo Error");
		return false;
	}

	return true;
}

#ifdef ENABLE_CHEQUE_SYSTEM
bool CPythonNetworkStream::SendPrivateShopSearchInfoSub(int32_t Race, int32_t ItemCat, int32_t SubCat, int32_t MinLevel, int32_t MaxLevel, int32_t MinRefine, int32_t MaxRefine, uint64_t MinGold, uint64_t MaxGold, char* ItemName, uint64_t MinCheque, uint64_t MaxCheque)
#else
bool CPythonNetworkStream::SendPrivateShopSearchInfoSub(int32_t Race, int32_t ItemCat, int32_t SubCat, int32_t MinLevel, int32_t MaxLevel, int32_t MinRefine, int32_t MaxRefine, uint64_t MinGold, uint64_t MaxGold, char* ItemName)
#endif
{
	if (!__CanActMainInstance())
	{
		return true;
	}

	TPacketCGShopSearch ShopSearchPacket;
	ShopSearchPacket.header = HEADER_CG_SHOP_SEARCH_SUB;
	ShopSearchPacket.Race = Race;
	ShopSearchPacket.ItemCat = ItemCat;
	ShopSearchPacket.SubCat = SubCat;
	ShopSearchPacket.MinLevel = MinLevel;
	ShopSearchPacket.MaxLevel = MaxLevel;
	ShopSearchPacket.MinRefine = MinRefine;
	ShopSearchPacket.MaxRefine = MaxRefine;
	ShopSearchPacket.MinGold = MinGold;
	ShopSearchPacket.MaxGold = MaxGold;
	strncpy_s(ShopSearchPacket.ItemName, ItemName, sizeof(ShopSearchPacket.ItemName) - 1);
#ifdef ENABLE_CHEQUE_SYSTEM
	ShopSearchPacket.MinCheque = MinCheque;
	ShopSearchPacket.MaxCheque = MaxCheque;
#endif

	if (!Send(sizeof(ShopSearchPacket), &ShopSearchPacket))
	{
		Tracen("SendPrivateShopSearchInfoSub Error");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendPrivateShopSerchBuyItem(int32_t shopVid, BYTE shopItemPos, int shopPos, DWORD item_id, long long llPrice)
{
	if (!__CanActMainInstance())
	{
		return true;
	}

	TPacketCGShopSearchBuy PacketShopSearchBuy;
	PacketShopSearchBuy.header = HEADER_CG_SHOP_SEARCH_BUY;
	PacketShopSearchBuy.shopVid = shopVid;
	PacketShopSearchBuy.shopItemPos = shopItemPos;
	PacketShopSearchBuy.shopPos = shopPos;
	PacketShopSearchBuy.item_id = item_id;
	PacketShopSearchBuy.item_price = llPrice;

	if (!Send(sizeof(TPacketCGShopSearchBuy), &PacketShopSearchBuy))
	{
		Tracef("SendPrivateShopSerchBuyItem Error\n");
		return false;
	}

	Tracef("SendPrivateShopSerchBuyItem: ShopVid: %d  Pos %d shopPos %d", shopVid, shopItemPos, shopPos);

	return SendSequence();
}

bool CPythonNetworkStream::RecvShopSearchSet()
{
	TPacketGCShopSearchItemSet packet_item_set;

	if (!Recv(sizeof(TPacketGCShopSearchItemSet), &packet_item_set))
	{
		return false;
	}

	CPythonPrivateShopSearch::TSearchItemData searchItem;
	searchItem.vnum = packet_item_set.vnum;
	searchItem.count = packet_item_set.count;
	searchItem.flags = packet_item_set.flags;
	searchItem.anti_flags = packet_item_set.anti_flags;

	for (int i = 0; i < ITEM_SOCKET_SLOT_MAX_NUM; ++i)
	{
		searchItem.alSockets[i] = packet_item_set.alSockets[i];
	}
	for (int j = 0; j < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++j)
	{
		searchItem.aAttr[j] = packet_item_set.aAttr[j];
	}

#ifdef __BL_TRANSMUTATION__
	searchItem.dwTransmutationVnum = packet_item_set.dwTransmutationVnum;
#endif

	searchItem.vid = packet_item_set.vid;
	searchItem.price = packet_item_set.price;
#ifdef ENABLE_CHEQUE_SYSTEM
	searchItem.price_cheque = packet_item_set.price_cheque;
#endif
	searchItem.Cell = packet_item_set.Cell;

#ifdef ENABLE_CHEQUE_SYSTEM
	CPythonPrivateShopSearch::Instance().AddItemData(packet_item_set.vid, packet_item_set.price, packet_item_set.price_cheque, searchItem);
#else
	CPythonPrivateShopSearch::Instance().AddItemData(packet_item_set.vid, packet_item_set.price, searchItem);
#endif

	__RefreshShopSearchWindow();
	return SendSequence();
}
#endif

#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
bool CPythonNetworkStream::SendNewPrivateShopSearchInfo(int32_t ItemCat, int32_t SubCat, char* ItemName, int minLevelValue, int maxLevelValue, int minDHValue, int maxDHValue, int minDMValue, int maxDMValue, int itemRefineLevel, int acceAbsPerc, int dsClarityValue, int bonusChoose, int itemGender, int have_name)
{
	if (!__CanActMainInstance())
	{
		return true;
	}

	TPacketCGNewShopSearch NewShopSearchPacket;
	NewShopSearchPacket.bHeader = HEADER_CG_NEW_SHOP_SEARCH;
	NewShopSearchPacket.ItemCat = ItemCat;
	NewShopSearchPacket.SubCat = SubCat;
	strncpy_s(NewShopSearchPacket.ItemName, ItemName, sizeof(NewShopSearchPacket.ItemName) - 1);
	NewShopSearchPacket.minLevelValue = minLevelValue;
	NewShopSearchPacket.maxLevelValue = maxLevelValue;
	NewShopSearchPacket.minDHValue = minDHValue;
	NewShopSearchPacket.maxDHValue = maxDHValue;
	NewShopSearchPacket.minDMValue = minDMValue;
	NewShopSearchPacket.maxDMValue = maxDMValue;
	NewShopSearchPacket.itemRefineLevel = itemRefineLevel;
	NewShopSearchPacket.acceAbsPerc = acceAbsPerc;
	NewShopSearchPacket.dsClarityValue = dsClarityValue;
	NewShopSearchPacket.bonusChoose = bonusChoose;
	NewShopSearchPacket.itemGender = itemGender;
	NewShopSearchPacket.have_name = have_name;
	
	if (!Send(sizeof(NewShopSearchPacket), &NewShopSearchPacket))
	{
		Tracen("SendNewPrivateShopSearchInfo Error");
		return false;
	}

	return true;
}

bool CPythonNetworkStream::RecvNewShopSearchSet()
{
	TPacketGCShopSearchItemSet packet_item_set;

	if (!Recv(sizeof(TPacketGCShopSearchItemSet), &packet_item_set))
	{
		return false;
	}

	CPythonNewPrivateShopSearch::TSearchItemData searchItem;
	searchItem.vnum = packet_item_set.vnum;
	searchItem.count = packet_item_set.count;
	searchItem.flags = packet_item_set.flags;
	searchItem.anti_flags = packet_item_set.anti_flags;

	for (int i = 0; i < ITEM_SOCKET_SLOT_MAX_NUM; ++i)
	{
		searchItem.alSockets[i] = packet_item_set.alSockets[i];
	}
	for (int j = 0; j < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++j)
	{
		searchItem.aAttr[j] = packet_item_set.aAttr[j];
	}

#ifdef __BL_TRANSMUTATION__
	searchItem.dwTransmutationVnum = packet_item_set.dwTransmutationVnum;
#endif

	IAbstractApplication& rApp = IAbstractApplication::GetSingleton();
	float fcurTime = rApp.GetGlobalTime();
	
	searchItem.vid = packet_item_set.vid;
	searchItem.price = packet_item_set.price;
	searchItem.Cell = packet_item_set.Cell;
	searchItem.shop_time = packet_item_set.shop_time + (int)fcurTime;

	searchItem.ch_map_index = packet_item_set.ch_map_index;
	searchItem.off_shop_map_index = packet_item_set.off_shop_map_index;
	searchItem.item_state = 0;
	searchItem.item_id = packet_item_set.item_id;
	searchItem.sellerName = packet_item_set.sellerName;


	CPythonNewPrivateShopSearch::Instance().AddItemData(searchItem);

	return SendSequence();
}

#endif