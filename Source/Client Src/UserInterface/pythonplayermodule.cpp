//arat

void initPlayer()

//üstüne ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
PyObject* playerGetCurrentOfflineShopMoney(PyObject* poSelf, PyObject* poArgs)
{
	return PyLong_FromLongLong(CPythonPlayer::instance().GetCurrentOfflineShopMoney());
}

#ifdef ENABLE_CHEQUE_SYSTEM
PyObject* playerGetCurrentOfflineShopCheque(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonPlayer::instance().GetCurrentOfflineShopCheque());
}
#endif

PyObject* playerHasOfflineShop(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonPlayer::instance().HasOfflineShop());
}
#endif

//arat

{ "SendDragonSoulRefine",		playerSendDragonSoulRefine,			METH_VARARGS },

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		{ "GetCurrentOfflineShopMoney",		playerGetCurrentOfflineShopMoney,	METH_VARARGS },
	#ifdef ENABLE_CHEQUE_SYSTEM
		{ "GetCurrentOfflineShopCheque",	playerGetCurrentOfflineShopCheque,	METH_VARARGS },
	#endif
		{ "HasOfflineShop",					playerHasOfflineShop,				METH_VARARGS },
#endif

//arat

PyModule_AddIntConstant(poModule, "ON_TOP_WND_PET_FEED", ON_TOP_WND_PET_FEED);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "ON_TOP_WND_OFFLINE_SHOP", ON_TOP_WND_OFFLINE_SHOP);
	PyModule_AddIntConstant(poModule, "ON_TOP_WND_OFFLINE_SHOP_MANAGER", ON_TOP_WND_OFFLINE_SHOP_MANAGER);
#endif

//arat

PyModule_AddIntConstant(poModule, "SLOT_TYPE_DRAGON_SOUL_INVENTORY",	SLOT_TYPE_DRAGON_SOUL_INVENTORY);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "SLOT_TYPE_OFFLINE_SHOP", SLOT_TYPE_OFFLINE_SHOP);
#endif