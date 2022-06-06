//ekle

#define ENABLE_CHANNEL_SWITCH_SYSTEM
#define WJ_ENABLE_TRADABLE_ICON
#define __OFFLINE_PRIVATE_SHOP_SYSTEM__ // Offline private shop
#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#define __OFFLINE_SHOP_PID_MAP_GUESTS__ //Use pid for save informations about guest players
#endif
#define __ENABLE_PREMIUM_MEMBERS__ //premium members system
#define __PRIVATE_SHOP_SEARCH_SYSTEM__ // Search private shop items
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	#define __PRIVATE_SHOP_SEARCH_NEED_ITEM__ // Require special search item
#endif
#define __NEW_PRIVATE_SHOP_SEARCH_SYSTEM__ // new private shop search