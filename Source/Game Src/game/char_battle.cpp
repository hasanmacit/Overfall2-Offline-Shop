//definelere ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#include "offlineshop_manager.h"
#endif

//arat

	CShopManager::instance().StopShopping(this);

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	COfflineShopManager::Instance().StopShopping(this);
#endif