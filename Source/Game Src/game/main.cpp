//definelere ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#include "offlineshop_manager.h"
#endif

//arat

CShopManager	shop_manager;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	COfflineShopManager offlineshop_manager;
#endif