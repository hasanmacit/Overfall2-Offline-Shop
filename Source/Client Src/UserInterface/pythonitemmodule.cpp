//en alta ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	PyModule_AddIntConstant(poModule, "DRAGON_STONE_DRAGON_DIAMOND", 0);
	PyModule_AddIntConstant(poModule, "DRAGON_STONE_DRAGON_RUBY", 1);
	PyModule_AddIntConstant(poModule, "DRAGON_STONE_DRAGON_JADE", 2);
	PyModule_AddIntConstant(poModule, "DRAGON_STONE_DRAGON_SAPPHIRE", 3);
	PyModule_AddIntConstant(poModule, "DRAGON_STONE_DRAGON_GARNET", 4);
	PyModule_AddIntConstant(poModule, "DRAGON_STONE_DRAGON_ONYX", 5);
#endif