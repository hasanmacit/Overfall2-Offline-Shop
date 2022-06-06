//arat

initMessenger();

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	initprivateShopSearch();
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
	initnewprivateShopSearch();
#endif