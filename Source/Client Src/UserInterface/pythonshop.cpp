//arat

BOOL CPythonShop::GetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData ** c_ppItemData)

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
void CPythonShop::SetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData & c_rShopItemData)
{
	BYTE tabIdx = dwIndex / OFFLINE_SHOP_HOST_ITEM_MAX_NUM;
	DWORD dwSlotPos = dwIndex % OFFLINE_SHOP_HOST_ITEM_MAX_NUM;

	SetOfflineShopItemData(tabIdx, dwSlotPos, c_rShopItemData);
}

void CPythonShop::SetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData & c_rShopItemData)
{
	if (tabIdx >= SHOP_TAB_COUNT_MAX || dwSlotPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d. dwSlotPos(%d) must be less than %d", tabIdx, SHOP_TAB_COUNT_MAX, dwSlotPos, OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
		return;
	}

	m_aOfflineShoptabs[tabIdx].items[dwSlotPos] = c_rShopItemData;
}

BOOL CPythonShop::GetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData ** c_ppItemData)
{
	BYTE tabIdx = dwIndex / OFFLINE_SHOP_HOST_ITEM_MAX_NUM;
	DWORD dwSlotPos = dwIndex % OFFLINE_SHOP_HOST_ITEM_MAX_NUM;

	return GetOfflineShopItemData(tabIdx, dwSlotPos, c_ppItemData);
}

BOOL CPythonShop::GetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData ** c_ppItemData)
{
	if (tabIdx >= SHOP_TAB_COUNT_MAX || dwSlotPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d. dwSlotPos(%d) must be less than %d", tabIdx, SHOP_TAB_COUNT_MAX, dwSlotPos, OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
		return FALSE;
	}

	if (m_aOfflineShoptabs[tabIdx].items[dwSlotPos].vnum)
	{
		*c_ppItemData = &m_aOfflineShoptabs[tabIdx].items[dwSlotPos];
		return TRUE;
	}

	*c_ppItemData = NULL;
	return FALSE;
}
#endif

//arat

void CPythonShop::BuildPrivateShop(const char * c_szName)

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
struct OfflineShopItemStockSortFunc
{
	bool operator() (TOfflineShopItemTable & rkLeft, TOfflineShopItemTable & rkRight)
	{
		return rkLeft.display_pos < rkRight.display_pos;
	}
};

void CPythonShop::ClearOfflineShopStock()
{
	m_OfflineShopItemStock.clear();
}

#ifdef ENABLE_CHEQUE_SYSTEM
void CPythonShop::AddOfflineShopItemStock(TItemPos ItemPos, BYTE dwDisplayPos, long long dwPrice, DWORD dwPriceCheque)
#else
void CPythonShop::AddOfflineShopItemStock(TItemPos ItemPos, BYTE dwDisplayPos, long long dwPrice)
#endif
{
	DelOfflineShopItemStock(ItemPos);

	TOfflineShopItemTable SellingItem;
	SellingItem.vnum = 0;
	SellingItem.count = 0;
	SellingItem.pos = ItemPos;
	SellingItem.price = dwPrice;
#ifdef ENABLE_CHEQUE_SYSTEM
	SellingItem.price_cheque = dwPriceCheque;
#endif
	SellingItem.display_pos = dwDisplayPos;
	m_OfflineShopItemStock.insert(std::make_pair(ItemPos, SellingItem));
}

void CPythonShop::DelOfflineShopItemStock(TItemPos ItemPos)
{
	if (m_OfflineShopItemStock.end() == m_OfflineShopItemStock.find(ItemPos))
		return;

	m_OfflineShopItemStock.erase(ItemPos);
}

long long CPythonShop::GetOfflineShopItemPrice(TItemPos ItemPos)
{
	TOfflineShopItemStock::iterator itor = m_OfflineShopItemStock.find(ItemPos);

	if (m_OfflineShopItemStock.end() == itor)
		return 0;

	TOfflineShopItemTable & rShopItemTable = itor->second;
	return rShopItemTable.price;
}

#ifdef ENABLE_CHEQUE_SYSTEM
int CPythonShop::GetOfflineShopItemPriceCheque(TItemPos ItemPos)
{
	TOfflineShopItemStock::iterator itor = m_OfflineShopItemStock.find(ItemPos);

	if (m_OfflineShopItemStock.end() == itor)
		return 0;

	TOfflineShopItemTable & rShopItemTable = itor->second;
	return rShopItemTable.price_cheque;
}
#endif

void CPythonShop::BuildOfflineShop(const char * c_szName, BYTE bNpcType, BYTE bBoardStyle)
{
	std::vector<TOfflineShopItemTable> ItemStock;
	ItemStock.reserve(m_OfflineShopItemStock.size());

	TOfflineShopItemStock::iterator itor = m_OfflineShopItemStock.begin();
	for (; itor != m_OfflineShopItemStock.end(); ++itor)
	{
		ItemStock.push_back(itor->second);
	}

	std::sort(ItemStock.begin(), ItemStock.end(), OfflineShopItemStockSortFunc());

	CPythonNetworkStream::Instance().SendBuildOfflineShopPacket(c_szName, ItemStock, bNpcType, bBoardStyle);
}
#endif

//arat

void CPythonShop::Open

//değiştir

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
void CPythonShop::Open(BOOL isPrivateShop, BOOL isMainPrivateShop, BOOL isOfflineShop)
#else
void CPythonShop::Open(BOOL isPrivateShop, BOOL isMainPrivateShop)
#endif
{
	m_isShoping = TRUE;
	m_isPrivateShop = isPrivateShop;
	m_isMainPlayerPrivateShop = isMainPrivateShop;
#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	m_isOfflineShop = isOfflineShop;
#endif
}

//arat

m_isMainPlayerPrivateShop = FALSE;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	m_isOfflineShop = FALSE;
#endif

//arat

BOOL CPythonShop::IsMainPlayerPrivateShop()

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
BOOL CPythonShop::IsOfflineShop()
{
	return m_isOfflineShop;
}

DWORD CPythonShop::GetShopDisplayedCount()
{
	return m_dwDisplayedCount;
}

void CPythonShop::SetShopDisplayedCount(DWORD dwDisplayedCount)
{
	m_dwDisplayedCount = dwDisplayedCount;
}
#endif

//arat

m_isMainPlayerPrivateShop = FALSE;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	m_isOfflineShop = FALSE;
#endif

//arat

PyObject * shopOpen(PyObject * poSelf, PyObject * poArgs)

//değiştir

PyObject * shopOpen(PyObject * poSelf, PyObject * poArgs)
{
	int isPrivateShop = false;
	PyTuple_GetInteger(poArgs, 0, &isPrivateShop);
	int isMainPrivateShop = false;
	PyTuple_GetInteger(poArgs, 1, &isMainPrivateShop);

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	int isOfflineShop = false;
	PyTuple_GetInteger(poArgs, 2, &isOfflineShop);
#endif

	CPythonShop& rkShop=CPythonShop::Instance();
#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	rkShop.Open(isPrivateShop, isMainPrivateShop, isOfflineShop);
#else
	rkShop.Open(isPrivateShop, isMainPrivateShop);
#endif
	return Py_BuildNone();
}

//arat

PyObject * shopBuildPrivateShop(PyObject * poSelf, PyObject * poArgs)

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
PyObject * shopIsOfflineShop(PyObject * poSelf, PyObject * poArgs)
{
	CPythonShop & rkShop = CPythonShop::Instance();
	return Py_BuildValue("i", rkShop.IsOfflineShop());
}

PyObject * shopGetOfflineShopItemID(PyObject * poSelf, PyObject * poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->vnum);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetOfflineShopItemCount(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->count);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetOfflineShopItemVnum(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->vnum);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetOfflineShopItemPrice(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return PyLong_FromLongLong(c_pItemData->price);

	return Py_BuildValue("i", 0);
}

#ifdef ENABLE_CHEQUE_SYSTEM
PyObject * shopGetOfflineShopItemPriceCheque(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->price_cheque);

	return Py_BuildValue("i", 0);
}
#endif

PyObject * shopGetOfflineShopItemMetinSocket(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	int iMetinSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iMetinSocketIndex))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->alSockets[iMetinSocketIndex]);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetOfflineShopItemAttribute(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		const TOfflineShopItemData * c_pItemData;
		if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
			return Py_BuildValue("ii", c_pItemData->aAttr[iAttrSlotIndex].bType, c_pItemData->aAttr[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

#ifdef __BL_TRANSMUTATION__
PyObject * shopGetOfflineShopItemTransmutation(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->dwTransmutationVnum);

	return Py_BuildValue("i", 0);
}
#endif

PyObject * shopClearOfflineShopStock(PyObject * poSelf, PyObject * poArgs)
{
	CPythonShop::Instance().ClearOfflineShopStock();
	return Py_BuildNone();
}

PyObject * shopAddOfflineShopItemStock(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();

	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	int iDisplaySlotIndex;
	if (!PyTuple_GetInteger(poArgs, 2, &iDisplaySlotIndex))
		return Py_BuildException();

	long long iPrice;
	if (!PyTuple_GetLongLong(poArgs, 3, &iPrice))
		return Py_BuildException();

#ifdef ENABLE_CHEQUE_SYSTEM
	int iPriceCheque;
	if (!PyTuple_GetInteger(poArgs, 4, &iPriceCheque))
		return Py_BuildException();
#endif

	if (iPrice > 125000000000000)
		iPrice = 125000000000000;
	else if (iPrice <= 0)
		iPrice = 1;
	
#ifdef ENABLE_CHEQUE_SYSTEM
	CPythonShop::Instance().AddOfflineShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex), iDisplaySlotIndex, iPrice, iPriceCheque);
#else
	CPythonShop::Instance().AddOfflineShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex), iDisplaySlotIndex, iPrice);
#endif
	return Py_BuildNone();
}

PyObject * shopDelOfflineShopItemStock(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();

	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	CPythonShop::Instance().DelOfflineShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildNone();
}

PyObject * shopGetOfflineShopItemPriceReal(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();

	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	long long iValue = CPythonShop::Instance().GetOfflineShopItemPrice(TItemPos(bItemWindowType, wItemSlotIndex));
	return PyLong_FromLongLong(iValue);
}

#ifdef ENABLE_CHEQUE_SYSTEM
PyObject * shopGetOfflineShopItemPriceChequeReal(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();

	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	int iValue = CPythonShop::Instance().GetOfflineShopItemPriceCheque(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildValue("i", iValue);
}
#endif

PyObject * shopGetOfflineShopItemGetStatus(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->status);

	return Py_BuildValue("i", 0);
}

PyObject * shopGetOfflineShopItemGetBuyerName(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("s", c_pItemData->szBuyerName);

	return Py_BuildValue("s", "None");
}

PyObject * shopBuildOfflineShop(PyObject * poSelf, PyObject * poArgs)
{
	char * szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	BYTE bNpcType;
	if (!PyTuple_GetInteger(poArgs, 1, &bNpcType))
		return Py_BuildException();

	BYTE bBoardStyle;
	if (!PyTuple_GetInteger(poArgs, 2, &bBoardStyle))
		return Py_BuildException();

	CPythonShop::Instance().BuildOfflineShop(szName, bNpcType, bBoardStyle);
	return Py_BuildNone();
}

PyObject * shopGetDisplayedCount(PyObject * poSelf, PyObject * poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetShopDisplayedCount());
}
#endif

//arat

{ "BuildPrivateShop",			shopBuildPrivateShop,			METH_VARARGS },

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		// Offline Shop
		{ "IsOfflineShop",						shopIsOfflineShop,						METH_VARARGS },
		{ "GetOfflineShopItemID",				shopGetOfflineShopItemID,				METH_VARARGS },
		{ "GetOfflineShopItemCount",			shopGetOfflineShopItemCount,			METH_VARARGS },
		{ "GetOfflineShopItemVnum",				shopGetOfflineShopItemVnum,				METH_VARARGS },
		{ "GetOfflineShopItemPrice",			shopGetOfflineShopItemPrice,			METH_VARARGS },
	#ifdef ENABLE_CHEQUE_SYSTEM
		{ "GetOfflineShopItemPriceCheque",		shopGetOfflineShopItemPriceCheque,		METH_VARARGS },
	#endif
		{ "GetOfflineShopItemMetinSocket",		shopGetOfflineShopItemMetinSocket,		METH_VARARGS },
		{ "GetOfflineShopItemAttribute",		shopGetOfflineShopItemAttribute,		METH_VARARGS },
	#ifdef __BL_TRANSMUTATION__
		{ "GetOfflineShopItemTransmutation",		shopGetOfflineShopItemTransmutation,	METH_VARARGS},
	#endif

		{ "ClearOfflineShopStock",				shopClearOfflineShopStock,				METH_VARARGS },
		{ "AddOfflineShopItemStock",			shopAddOfflineShopItemStock,			METH_VARARGS },
		{ "DelOfflineShopItemStock",			shopDelOfflineShopItemStock,			METH_VARARGS },
		{ "GetOfflineShopItemPriceReal",		shopGetOfflineShopItemPriceReal,		METH_VARARGS },
	#ifdef ENABLE_CHEQUE_SYSTEM
		{ "GetOfflineShopItemPriceChequeReal",	shopGetOfflineShopItemPriceChequeReal,	METH_VARARGS },
	#endif
		{ "GetOfflineShopItemStatus",			shopGetOfflineShopItemGetStatus,		METH_VARARGS },
		{ "GetOfflineShopItemBuyerName",		shopGetOfflineShopItemGetBuyerName,		METH_VARARGS },
		{ "BuildOfflineShop",					shopBuildOfflineShop,					METH_VARARGS },
		{ "GetDisplayedCount",					shopGetDisplayedCount,					METH_VARARGS },
#endif

//arat

PyModule_AddIntConstant(poModule, "SHOP_SLOT_COUNT", SHOP_HOST_ITEM_MAX_NUM);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "OFFLINE_SHOP_SLOT_COUNT", OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
#endif