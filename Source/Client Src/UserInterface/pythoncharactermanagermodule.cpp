//arat

PyModule_AddIntConstant(poModule, "NAMECOLOR_EXTRA", CInstanceBase::NAMECOLOR_EXTRA);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "NAMECOLOR_OFFLINESHOP", CInstanceBase::NAMECOLOR_OFFLINESHOP);
#endif