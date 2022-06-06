//arat

	Set(HEADER_CG_DRAGON_SOUL_REFINE, sizeof(TPacketCGDragonSoulRefine), "DragonSoulRefine", false);

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	Set(HEADER_CG_OFFLINE_SHOP, sizeof(TPacketCGOfflineShop), "OfflineShop");
	Set(HEADER_CG_MY_OFFLINE_SHOP, sizeof(TPacketCGMyOfflineShop), "MyOfflineShop");
	Set(HEADER_CG_OFFLINE_SHOP_CHANGE_SHOP_NAME, sizeof(TPacketCGChangeOfflineShopName), "SendChangeOfflineShopName");
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	Set(HEADER_CG_SHOP_SEARCH, sizeof(TPacketCGShopSearch), "ShopSearch");
	Set(HEADER_CG_SHOP_SEARCH_SUB, sizeof(TPacketCGShopSearch), "ShopSearchSub");
	Set(HEADER_CG_SHOP_SEARCH_BUY, sizeof(TPacketCGShopSearchBuy), "ShopSearchBuy");
#endif
#if defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
	Set(HEADER_CG_NEW_SHOP_SEARCH, sizeof(TPacketCGNewShopSearch), "NewShopSearch");
#endif

//arat

Set(HEADER_GG_CHECK_AWAKENESS,		sizeof(TPacketGGCheckAwakeness),	"CheckAwakeness",		false);

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	Set(HEADER_GG_REMOVE_OFFLINE_SHOP, sizeof(TPacketGGRemoveOfflineShop), "RemoveOfflineShop");
	Set(HEADER_GG_CHANGE_OFFLINE_SHOP_TIME, sizeof(TPacketGGChangeOfflineShopTime), "ChangeOfflineShopTime");
	Set(HEADER_GG_OFFLINE_SHOP_OPEN_PANEL, sizeof(TPacketGGOpenOffShopPanel), "LoadOfflineShopPanelData");
	Set(HEADER_GG_OFFLINE_SHOP_ADD_ITEM, sizeof(TPacketGGAddOfflineShopItem), "AddOfflineShopItemData");
	Set(HEADER_GG_OFFLINE_SHOP_REMOVE_ITEM, sizeof(TPacketGGRemoveOfflineShopItem), "RemoveOfflineShopItemData");
	Set(HEADER_GG_OFFLINE_SHOP_CLOSE_SHOP, sizeof(TPacketGGOfflineShopClose), "CloseOfflineShopData");
	Set(HEADER_GG_OFFLINE_SHOP_CHANGE_NAME, sizeof(TPacketGGOfflineShopChangeName), "ChangeOfflineShopName");
	Set(HEADER_GG_OFFLINE_SHOP_ADVISE_PLAYER, sizeof(TPacketGGOfflineShopAdviseOwnerSell), "ReloadOfflineShopMoney");
	Set(HEADER_GG_OFFLINE_SHOP_CHANGE_ITEM_PRICE, sizeof(TPacketGGChangeOfflineShopItemPrice), "ChangeOfflineShopItemPrice");
#endif