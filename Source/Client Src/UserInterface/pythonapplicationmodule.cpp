//en alta ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_OFFLINE_SHOP_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_OFFLINE_SHOP_SYSTEM", 0);
#endif

#if defined(ENABLE_PREMIUM_MEMBERS)
	PyModule_AddIntConstant(poModule, "ENABLE_PREMIUM_MEMBERS", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_PREMIUM_MEMBERS", 0);
#endif

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM", 0);
#endif

#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
	PyModule_AddIntConstant(poModule, "ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM", 0);
#endif