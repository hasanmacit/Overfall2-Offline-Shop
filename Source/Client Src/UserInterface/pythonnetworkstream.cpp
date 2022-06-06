//arat

Set(HEADER_GC_DRAGON_SOUL_REFINE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
			Set(HEADER_GC_OFFLINE_SHOP, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShop), DYNAMIC_SIZE_PACKET));
			Set(HEADER_GC_OFFLINE_SHOP_SIGN, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShopSign), STATIC_SIZE_PACKET));
			Set(HEADER_GC_OFFLINE_SHOP_OPEN_PANEL, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCOpenOffShopPanel), STATIC_SIZE_PACKET));
			Set(HEADER_GC_OFFLINE_SHOP_START_P2P, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCOfflineShopStartP2P), STATIC_SIZE_PACKET));
			Set(HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShopSign), STATIC_SIZE_PACKET));
			Set(HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN_P2P, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShopSign), STATIC_SIZE_PACKET));
			Set(HEADER_GC_OFFLINE_ADVISE_PLAYER_BUY, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCOfflineShopAdviseOwnerSell), STATIC_SIZE_PACKET));
#endif
#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
			Set(HEADER_GC_SHOPSEARCH_SET, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShopSearchItemSet), STATIC_SIZE_PACKET));
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
			Set(HEADER_GC_NEW_SHOPSEARCH_SET, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShopSearchItemSet), STATIC_SIZE_PACKET));
#endif