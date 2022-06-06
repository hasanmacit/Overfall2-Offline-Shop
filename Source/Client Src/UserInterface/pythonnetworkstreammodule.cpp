//arat

void initnet()

//üstüne ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
PyObject* netSendOfflineShopEndPacket(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendOfflineShopEndPacket();
	return Py_BuildNone();
}

PyObject* netSendOfflineShopBuyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iCount;
	if (!PyTuple_GetInteger(poArgs, 0, &iCount))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendOfflineShopBuyPacket(iCount);
	return Py_BuildNone();
}

PyObject * netSendRefreshOfflineShop(PyObject * poSelf, PyObject * poArgs)
{
	int iDelay;
	if (!PyTuple_GetInteger(poArgs, 0, &iDelay))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRefreshOfflineShop(iDelay);
	return Py_BuildNone();
}

PyObject * netSendAddOfflineShopItem(PyObject * poSelf, PyObject * poArgs)
{
	int bDisplayPos;
	if (!PyTuple_GetInteger(poArgs, 0, &bDisplayPos))
		return Py_BuildException();

	int bPos;
	if (!PyTuple_GetInteger(poArgs, 1, &bPos))
		return Py_BuildException();

	long long iPrice;
	if (!PyTuple_GetLongLong(poArgs, 2, &iPrice))
		return Py_BuildException();

#ifdef ENABLE_CHEQUE_SYSTEM
	int	iPriceCheque;
	if (!PyTuple_GetInteger(poArgs, 3, &iPriceCheque))
		return Py_BuildException();

	BYTE bWindowType;
	if (!PyTuple_GetInteger(poArgs, 4, &bWindowType))
		return Py_BuildException();
#else
	BYTE bWindowType;
	if (!PyTuple_GetInteger(poArgs, 3, &bWindowType))
		return Py_BuildException();
#endif

	if (iPrice > 125000000000000)
		iPrice = 125000000000000;
	else if (iPrice <= 0)
		iPrice = 1;
	
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
#ifdef ENABLE_CHEQUE_SYSTEM
	rkNetStream.SendAddOfflineShopItem(TItemPos(bWindowType, bDisplayPos), bPos, iPrice, iPriceCheque);
#else
	rkNetStream.SendAddOfflineShopItem(TItemPos(bWindowType, bDisplayPos), bPos, iPrice);
#endif
	return Py_BuildNone();
}

PyObject * netSendRemoveOfflineShopItem(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bPos;
	if (!PyTuple_GetInteger(poArgs, 0, &bPos))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRemoveOfflineShopItem(bPos);
	return Py_BuildNone();
}

PyObject * netSendDestroyOfflineShop(PyObject * poSelf, PyObject * poArgs)
{
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendDestroyOfflineShop();
	return Py_BuildNone();
}

PyObject * netSendRefreshOfflineShopMoney(PyObject * poSelf, PyObject * poArgs)
{
	int iDelay;
	if (!PyTuple_GetInteger(poArgs, 0, &iDelay))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRefreshOfflineShopMoney(iDelay);
	return Py_BuildNone();
}

PyObject * netSendRefreshUnsoldItems(PyObject * poSelf, PyObject * poArgs)
{
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRefreshUnsoldItems();
	return Py_BuildNone();
}

PyObject * netSendOfflineShopTakeItem(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bDisplayPos;
	if (!PyTuple_GetInteger(poArgs, 0, &bDisplayPos))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopTakeItem(bDisplayPos);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopChangeItemPrice(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bDisplayPos;
	if (!PyTuple_GetInteger(poArgs, 0, &bDisplayPos))
		return Py_BuildException();
	
	long long llPrice;
	if (!PyTuple_GetLongLong(poArgs, 1, &llPrice))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopChangeItemPrice(bDisplayPos, llPrice);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopWithdrawMoney(PyObject * poSelf, PyObject * poArgs)
{
	long long llMoney;
	if (!PyTuple_GetLongLong(poArgs, 0, &llMoney))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawMoney(llMoney);
	return Py_BuildNone();
}

#ifdef ENABLE_CHEQUE_SYSTEM
PyObject * netSendOfflineShopWithdrawCheque(PyObject * poSelf, PyObject * poArgs)
{
	int iCheque;
	if (!PyTuple_GetInteger(poArgs, 0, &iCheque))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawCheque(iCheque);
	return Py_BuildNone();
}
#endif

PyObject * netSendOfflineShopCheck(PyObject * poSelf, PyObject * poArgs)
{
	int iDelay;
	if (!PyTuple_GetInteger(poArgs, 0, &iDelay))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopCheck(iDelay);
	return Py_BuildNone();
}

PyObject* netSendChangeOfflineShopName(PyObject* poSelf, PyObject* poArgs)
{
	char* szShopName;
	if (!PyTuple_GetString(poArgs, 0, &szShopName))
		return Py_BuildException();
	
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendChangeOfflineShopName(szShopName);
	return Py_BuildNone();
}

#endif

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
PyObject* netSendPrivateShopSearchInfo(PyObject* poSelf, PyObject* poArgs)
{
	int iJob;
	if (!PyTuple_GetInteger(poArgs, 0, &iJob))
		return Py_BuildException();

	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();

	int iSubType;
	if (!PyTuple_GetInteger(poArgs, 2, &iSubType))
		return Py_BuildException();

	int iMinLevel;
	if (!PyTuple_GetInteger(poArgs, 3, &iMinLevel))
		return Py_BuildException();

	int iMaxLevel;
	if (!PyTuple_GetInteger(poArgs, 4, &iMaxLevel))
		return Py_BuildException();

	int iMinRefine;
	if (!PyTuple_GetInteger(poArgs, 5, &iMinRefine))
		return Py_BuildException();

	int iMaxRefine;
	if (!PyTuple_GetInteger(poArgs, 6, &iMaxRefine))
		return Py_BuildException();

	int iMinPrice;
	if (!PyTuple_GetInteger(poArgs, 7, &iMinPrice))
		return Py_BuildException();

	int iMaxPrice;
	if (!PyTuple_GetInteger(poArgs, 8, &iMaxPrice))
		return Py_BuildException();

#ifdef ENABLE_CHEQUE_SYSTEM
	int iMinCheque;
	if (!PyTuple_GetInteger(poArgs, 9, &iMinCheque))
		return Py_BuildException();

	int iMaxCheque;
	if (!PyTuple_GetInteger(poArgs, 10, &iMaxCheque))
		return Py_BuildException();
#endif

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
#ifdef ENABLE_CHEQUE_SYSTEM
	rkNetStream.SendPrivateShopSearchInfo(iJob, iType, iSubType, iMinLevel, iMaxLevel, iMinRefine, iMaxRefine, iMinPrice, iMaxPrice, iMinCheque, iMaxCheque);
#else
	rkNetStream.SendPrivateShopSearchInfo(iJob, iType, iSubType, iMinLevel, iMaxLevel, iMinRefine, iMaxRefine, iMinPrice, iMaxPrice);
#endif

	return Py_BuildNone();
}

PyObject* netSendPrivateShopSearchInfoSub(PyObject* poSelf, PyObject* poArgs)
{
	int iJob;
	if (!PyTuple_GetInteger(poArgs, 0, &iJob))
		return Py_BuildException();

	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();

	int iSubType;
	if (!PyTuple_GetInteger(poArgs, 2, &iSubType))
		return Py_BuildException();

	int iMinLevel;
	if (!PyTuple_GetInteger(poArgs, 3, &iMinLevel))
		return Py_BuildException();

	int iMaxLevel;
	if (!PyTuple_GetInteger(poArgs, 4, &iMaxLevel))
		return Py_BuildException();

	int iMinRefine;
	if (!PyTuple_GetInteger(poArgs, 5, &iMinRefine))
		return Py_BuildException();

	int iMaxRefine;
	if (!PyTuple_GetInteger(poArgs, 6, &iMaxRefine))
		return Py_BuildException();

	int iMinPrice;
	if (!PyTuple_GetInteger(poArgs, 7, &iMinPrice))
		return Py_BuildException();

	int iMaxPrice;
	if (!PyTuple_GetInteger(poArgs, 8, &iMaxPrice))
		return Py_BuildException();

	char * pcItemName;
	if (!PyTuple_GetString(poArgs, 9, &pcItemName))
		return Py_BuildException();

#ifdef ENABLE_CHEQUE_SYSTEM
	int iMinCheque;
	if (!PyTuple_GetInteger(poArgs, 10, &iMinCheque))
		return Py_BuildException();

	int iMaxCheque;
	if (!PyTuple_GetInteger(poArgs, 11, &iMaxCheque))
		return Py_BuildException();
#endif

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
#ifdef ENABLE_CHEQUE_SYSTEM
	rkNetStream.SendPrivateShopSearchInfoSub(iJob, iType, iSubType, iMinLevel, iMaxLevel, iMinRefine, iMaxRefine, iMinPrice, iMaxPrice, pcItemName, iMinCheque, iMaxCheque);
#else
	rkNetStream.SendPrivateShopSearchInfoSub(iJob, iType, iSubType, iMinLevel, iMaxLevel, iMinRefine, iMaxRefine, iMinPrice, iMaxPrice, pcItemName);
#endif

	return Py_BuildNone();
}

PyObject* netSendPrivateShopSerchBuyItem(PyObject* poSelf, PyObject* poArgs)
{
	int iShopVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iShopVID))
		return Py_BuildException();

	int iItemPos;
	if (!PyTuple_GetInteger(poArgs, 1, &iItemPos))
		return Py_BuildException();

	int shopPos;
	if (!PyTuple_GetInteger(poArgs, 2, &shopPos))
		return Py_BuildException();

	int item_id;
	if (!PyTuple_GetInteger(poArgs, 3, &item_id))
		return Py_BuildException();

	long long llPrice;
	if (!PyTuple_GetLongLong(poArgs, 4, &llPrice))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendPrivateShopSerchBuyItem(iShopVID, iItemPos, shopPos, (DWORD)item_id, llPrice);
	return Py_BuildNone();
}
#endif

#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
PyObject* SendNewPrivateShopSearchInfo(PyObject* poSelf, PyObject* poArgs)
{
	int categoryType;
	if (!PyTuple_GetInteger(poArgs, 0, &categoryType))
		return Py_BuildException();

	int categorySubType;
	if (!PyTuple_GetInteger(poArgs, 1, &categorySubType))
		return Py_BuildException();

	char * pcItemName;
	if (!PyTuple_GetString(poArgs, 2, &pcItemName))
		return Py_BuildException();

	int minLevelValue;
	if (!PyTuple_GetInteger(poArgs, 3, &minLevelValue))
		return Py_BuildException();

	int maxLevelValue;
	if (!PyTuple_GetInteger(poArgs, 4, &maxLevelValue))
		return Py_BuildException();

	int minDHValue;
	if (!PyTuple_GetInteger(poArgs, 5, &minDHValue))
		return Py_BuildException();

	int maxDHValue;
	if (!PyTuple_GetInteger(poArgs, 6, &maxDHValue))
		return Py_BuildException();

	int minDMValue;
	if (!PyTuple_GetInteger(poArgs, 7, &minDMValue))
		return Py_BuildException();

	int maxDMValue;
	if (!PyTuple_GetInteger(poArgs, 8, &maxDMValue))
		return Py_BuildException();

	int itemRefineLevel;
	if (!PyTuple_GetInteger(poArgs, 9, &itemRefineLevel))
		return Py_BuildException();

	int acceAbsPerc;
	if (!PyTuple_GetInteger(poArgs, 10, &acceAbsPerc))
		return Py_BuildException();

	int dsClarityValue;
	if (!PyTuple_GetInteger(poArgs, 11, &dsClarityValue))
		return Py_BuildException();

	int bonusChoose;
	if (!PyTuple_GetInteger(poArgs, 12, &bonusChoose))
		return Py_BuildException();

	int itemGender;
	if (!PyTuple_GetInteger(poArgs, 13, &itemGender))
		return Py_BuildException();

	int have_name;
	if (!PyTuple_GetInteger(poArgs, 14, &have_name))
		return Py_BuildException();
	
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendNewPrivateShopSearchInfo(categoryType,
											categorySubType,
											pcItemName,
											minLevelValue,
											maxLevelValue,
											minDHValue,
											maxDHValue,
											minDMValue,
											maxDMValue,
											itemRefineLevel,
											acceAbsPerc,
											dsClarityValue,
											bonusChoose,
											itemGender,
											have_name);

	return Py_BuildNone();
}
#endif

//arat

{ "SendExchangeStartPacket",			netSendExchangeStartPacket,				METH_VARARGS },

//üstüne ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		{ "SendOfflineShopEndPacket",			netSendOfflineShopEndPacket,			METH_VARARGS },
		{ "SendOfflineShopBuyPacket",			netSendOfflineShopBuyPacket,			METH_VARARGS },
		{ "SendAddOfflineShopItem",				netSendAddOfflineShopItem,				METH_VARARGS },
		{ "SendRemoveOfflineShopItem",			netSendRemoveOfflineShopItem,			METH_VARARGS },
		{ "SendDestroyOfflineShop",				netSendDestroyOfflineShop,				METH_VARARGS },
		{ "SendRefreshOfflineShop",				netSendRefreshOfflineShop,				METH_VARARGS },
		{ "SendRefreshOfflineShopMoney",		netSendRefreshOfflineShopMoney,			METH_VARARGS },
		{ "SendRefreshUnsoldItems",				netSendRefreshUnsoldItems,				METH_VARARGS },
		{ "SendOfflineShopWithdrawMoney",		netSendOfflineShopWithdrawMoney,		METH_VARARGS },
	#ifdef ENABLE_CHEQUE_SYSTEM
		{ "SendOfflineShopWithdrawCheque",		netSendOfflineShopWithdrawCheque,		METH_VARARGS },
	#endif
		{ "SendOfflineShopTakeItem",			netSendOfflineShopTakeItem,				METH_VARARGS },
		{ "SendOfflineShopChangeItemPrice",		netSendOfflineShopChangeItemPrice,		METH_VARARGS },
		{ "SendOfflineShopCheck",				netSendOfflineShopCheck,				METH_VARARGS },
		{ "SendChangeOfflineShopName",			netSendChangeOfflineShopName,			METH_VARARGS },
#endif

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
		{ "SendPrivateShopSearchInfo",				netSendPrivateShopSearchInfo,				METH_VARARGS },
		{ "SendPrivateShopSearchInfoSub",			netSendPrivateShopSearchInfoSub,			METH_VARARGS },
		{ "SendPrivateShopSerchBuyItem",			netSendPrivateShopSerchBuyItem,				METH_VARARGS },
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
		{ "SendNewPrivateShopSearchInfo",			SendNewPrivateShopSearchInfo,				METH_VARARGS },
#endif