//arat

case HEADER_GC_DRAGON_SOUL_REFINE:

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
			case HEADER_GC_OFFLINE_SHOP:
				ret = RecvOfflineShopPacket();
				break;

			case HEADER_GC_OFFLINE_SHOP_SIGN:
				ret = RecvOfflineShopSignPacket();
				break;
			
			case HEADER_GC_OFFLINE_SHOP_OPEN_PANEL:
				ret = RecvOfflineShopOpenPanelPacket();
				break;
			
			case HEADER_GC_OFFLINE_SHOP_START_P2P:
				ret = RecvOfflineShopStartP2PPacket();
				break;
			
			case HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN:
				ret = RecvOfflineShopChangeSignPacket();
				break;
			
			case HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN_P2P:
				ret = RecvOfflineShopChangeSignPacketP2P();
				break;
			
			case HEADER_GC_OFFLINE_ADVISE_PLAYER_BUY:
				ret = RecvOfflineShopPlayerBuyItem();
				break;
#endif

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
			case HEADER_GC_SHOPSEARCH_SET:
				ret = RecvShopSearchSet();
				break;
#endif

#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
			case HEADER_GC_NEW_SHOPSEARCH_SET:
				ret = RecvNewShopSearchSet();
				break;
#endif

//arat

bool CPythonNetworkStream::RecvTimePacket()

//üstüne ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
/////////////////////////////////////////////////////////////////////////
// MyOfflineShop
bool CPythonNetworkStream::SendBuildOfflineShopPacket(const char* c_szName, const std::vector<TOfflineShopItemTable>& c_rSellingItemStock, BYTE bNpcType, BYTE bBoardStyle)
{
	TPacketCGMyOfflineShop packet;
	packet.bHeader = HEADER_CG_MY_OFFLINE_SHOP;
	strncpy(packet.szSign, c_szName, SHOP_SIGN_MAX_LEN);
	packet.bCount = (short)c_rSellingItemStock.size();
	packet.bNpcType = bNpcType;
	packet.bBoardStyle = bBoardStyle;
	if (!Send(sizeof(packet), &packet))
		return false;

	for (std::vector<TOfflineShopItemTable>::const_iterator itor = c_rSellingItemStock.begin(); itor < c_rSellingItemStock.end(); ++itor)
	{
		const TOfflineShopItemTable& c_rItem = *itor;
		if (!Send(sizeof(c_rItem), &c_rItem))
			return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::RecvOfflineShopSignPacket()
{
	TPacketGCShopSign p;
	if (!Recv(sizeof(TPacketGCShopSign), &p))
		return false;

	CInstanceBase* pInstance = CPythonCharacterManager::instance().GetInstancePtr(p.dwVID);
	if (pInstance)
	{
		if (pInstance->IsShop())
		{
			if (0 == strlen(p.szSign))
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Disappear", Py_BuildValue("(i)", p.dwVID));
			else
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Appear", Py_BuildValue("(isi)", p.dwVID, p.szSign, p.bBorderStyle));
		}
		else
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Disappear", Py_BuildValue("(i)", p.dwVID));
	}
	return true;
}

bool CPythonNetworkStream::RecvOfflineShopOpenPanelPacket()
{
	TPacketGCOpenOffShopPanel p;
	if (!Recv(sizeof(TPacketGCOpenOffShopPanel), &p))
		return false;
	
	BYTE hasOfflineShop = p.hasOfflineShop;
	UINT lMapIndex = (UINT)p.lMapIndex;
	BYTE shopChannel = p.shopChannel;
	int iTime = p.iTime;
	BYTE isPremium = p.isPremium;
	DWORD displayedCount = p.displayedCount;
	const char * shopName = p.shopName;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Open", Py_BuildValue("(iiiiiis)", hasOfflineShop, lMapIndex, shopChannel, iTime, isPremium, displayedCount, shopName));
	return true;
}

bool CPythonNetworkStream::RecvOfflineShopStartP2PPacket()
{
	TPacketGCOfflineShopStartP2P pShopStartPacket;
	if (!Recv(sizeof(TPacketGCOfflineShopStartP2P), &pShopStartPacket))
		return false;
	
	CPythonShop::Instance().Clear();
	for (BYTE iItemIndex = 0; iItemIndex < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++iItemIndex)
	{
		CPythonShop::Instance().SetOfflineShopItemData(iItemIndex, pShopStartPacket.items[iItemIndex]);
	}
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShopManager", Py_BuildValue("()"));
	return true;
}

bool CPythonNetworkStream::RecvOfflineShopChangeSignPacket()
{
	TPacketGCShopSign p;
	if (!Recv(sizeof(TPacketGCShopSign), &p))
		return false;

	CInstanceBase* pInstance = CPythonCharacterManager::instance().GetInstancePtr(p.dwVID);
	if (pInstance)
	{
		if (pInstance->IsShop())
		{
			if (0 == strlen(p.szSign))
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Disappear", Py_BuildValue("(i)", p.dwVID));
			else
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_ChangeSign", Py_BuildValue("(is)", p.dwVID, p.szSign));
		}
		else
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Disappear", Py_BuildValue("(i)", p.dwVID));
	}
	
	return true;
}

bool CPythonNetworkStream::RecvOfflineShopChangeSignPacketP2P()
{
	TPacketGCShopSign p;
	if (!Recv(sizeof(TPacketGCShopSign), &p))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_ChangeOfflineShopName", Py_BuildValue("(s)", p.szSign));
	
	return true;
}

bool CPythonNetworkStream::RecvOfflineShopPlayerBuyItem()
{
	TPacketGCOfflineShopAdviseOwnerSell p;
	if (!Recv(sizeof(TPacketGCOfflineShopAdviseOwnerSell), &p))
		return false;

	PyObject *args = PyTuple_New(3);
	PyTuple_SetItem(args, 0, Py_BuildValue("i", p.itemSelled));
	PyTuple_SetItem(args, 1, Py_BuildValue("s", p.buyerName));
	PyTuple_SetItem(args, 2, PyLong_FromLongLong(p.itemPrice));
	
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShopAdviseBuyItem", args);
	
	return true;
}

bool CPythonNetworkStream::RecvOfflineShopPacket()
{
	std::vector<int> vecBuffer;
	vecBuffer.clear();

	TPacketGCShop  packet_shop;
	if (!Recv(sizeof(packet_shop), &packet_shop))
		return false;

	int iSize = packet_shop.size - sizeof(packet_shop);

	if (iSize > 0)
	{
		vecBuffer.resize(iSize);
		if (!Recv(iSize, &vecBuffer[0]))
			return false;
	}

	switch (packet_shop.subheader)
	{
	case SHOP_SUBHEADER_GC_START:
	{
		CPythonShop::Instance().Clear();

		DWORD dwVID = *(DWORD*)&vecBuffer[0];

		TPacketGCOfflineShopStart* pShopStartPacket = (TPacketGCOfflineShopStart*)&vecBuffer[1];
		for (BYTE iItemIndex = 0; iItemIndex < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++iItemIndex)
		{
			CPythonShop::Instance().SetOfflineShopItemData(iItemIndex, pShopStartPacket->items[iItemIndex]);
		}

		CPythonShop::Instance().SetShopDisplayedCount(pShopStartPacket->m_dwDisplayedCount);

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "StartOfflineShop", Py_BuildValue("(i)", dwVID));
	}
	break;

	case SHOP_SUBHEADER_GC_UPDATE_ITEM2:
	{
		CPythonShop::Instance().Clear();
		TPacketGCOfflineShopStart* pShopStartPacket = (TPacketGCOfflineShopStart*)&vecBuffer[1];
		for (BYTE iItemIndex = 0; iItemIndex < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++iItemIndex)
		{
			CPythonShop::Instance().SetOfflineShopItemData(iItemIndex, pShopStartPacket->items[iItemIndex]);
		}
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShopManager", Py_BuildValue("()"));
	}
	break;

	case SHOP_SUBHEADER_GC_END:
		CPythonShop::instance().Clear();
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "EndOfflineShop", Py_BuildValue("()"));
		break;

	case SHOP_SUBHEADER_GC_UPDATE_PRICE:
	{	
		TPacketGCShopUpdatePrice* pShopUpdateItemPricePacket = (TPacketGCShopUpdatePrice*)&vecBuffer[0];
		PyObject *args = PyTuple_New(3);
		PyTuple_SetItem(args, 0, Py_BuildValue("i", pShopUpdateItemPricePacket->dwShopVid));
		PyTuple_SetItem(args, 1, Py_BuildValue("i", pShopUpdateItemPricePacket->bPos));
		PyTuple_SetItem(args, 2, PyLong_FromLongLong(pShopUpdateItemPricePacket->iPrice));
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshShopSellingPrice", args);
	}
	break;

	case SHOP_SUBHEADER_GC_UPDATE_ITEM:
	{
		TPacketGCOfflineShopUpdateItem* pShopUpdateItemPacket = (TPacketGCOfflineShopUpdateItem*)&vecBuffer[0];
		CPythonShop::Instance().SetOfflineShopItemData(pShopUpdateItemPacket->pos, pShopUpdateItemPacket->item);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShop", Py_BuildValue("()"));
	}
	break;

	case SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "NOT_ENOUGH_MONEY"));
		break;

	case SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY_EX:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "NOT_ENOUGH_MONEY_EX"));
		break;

	case SHOP_SUBHEADER_GC_SOLDOUT:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "SOLDOUT"));
		break;

	case SHOP_SUBHEADER_GC_INVENTORY_FULL:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "INVENTORY_FULL"));
		break;

	case SHOP_SUBHEADER_GC_INVALID_POS:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "INVALID_POS"));
		break;

	case SHOP_SUBHEADER_GC_YOU_DONT_HAVE_DS:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "YOU_DONT_HAVE_DS"));
		break;

	case SHOP_SUBHEADER_GC_REFRESH_MONEY:
	{
		TPacketGCOfflineShopMoney* pOfflineShopMoney = (TPacketGCOfflineShopMoney*)&vecBuffer[0];
		CPythonPlayer::Instance().SetCurrentOfflineShopMoney(pOfflineShopMoney->llMoney);
#ifdef ENABLE_CHEQUE_SYSTEM
		CPythonPlayer::Instance().SetCurrentOfflineShopCheque(pOfflineShopMoney->dwCheque);
#endif
		break;
	}

	case SHOP_SUBHEADER_GC_CHECK_RESULT:
	{
		BYTE bHasOfflineShop;
		if (!Recv(sizeof(BYTE), &bHasOfflineShop))
			return false;

		CPythonPlayer::instance().SetHasOfflineShop(bHasOfflineShop == 1 ? true : false);
		if (bHasOfflineShop != 0)
		{
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShopManager", Py_BuildValue("()"));
		}
		else
		{
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "CloseOfflineShopManager", Py_BuildValue("()"));
		}

		break;
	}

#ifdef ENABLE_CHEQUE_SYSTEM
	case SHOP_SUBHEADER_GC_NOT_ENOUGH_CHEQUE:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "NOT_ENOUGH_MONEY"));
		break;
#endif

	default:
		TraceError("CPythonNetworkStream::RecvOfflineShopPacket: Unknown subheader %d\n", packet_shop.subheader);
		break;
	}

	return true;
}
#endif

//arat

void CPythonNetworkStream::__RefreshEquipmentWindow()

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
void CPythonNetworkStream::__RefreshShopSearchWindow()
{
	m_isRefreshShopSearchWnd = true;
}
#endif

#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
void CPythonNetworkStream::__RefreshNewShopSearchWindow()
{
	m_isRefreshNewShopSearchWnd = true;
}
#endif

//arat

if (m_isRefreshGuildWndGradePage)

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	if (m_isRefreshShopSearchWnd)
	{
		m_isRefreshShopSearchWnd = false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshShopSearch", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}
#endif

#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
	if (m_isRefreshNewShopSearchWnd)
	{
		m_isRefreshNewShopSearchWnd = false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshNewShopSearch", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}
#endif