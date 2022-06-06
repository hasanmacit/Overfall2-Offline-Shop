//arat

void		Refine(LPCHARACTER ch, const char* c_pData);

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
		int			OfflineShop(LPCHARACTER ch, const char* data, size_t uiBytes);
		int			MyOfflineShop(LPCHARACTER ch, const char* c_pData, size_t uiBytes);
		void		SendChangeOfflineShopName(LPCHARACTER ch, const char* c_pData);
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		void 		ShopSearch(LPCHARACTER ch, const char* data, bool bName);
		void		ShopSearchBuy(LPCHARACTER ch, const char* data);
#endif
#if defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
		void 		NewShopSearch(LPCHARACTER ch, const char* data);
#endif

//arat

	protected:
		CPacketInfoGG 	m_packetInfoGG;

// üstüne ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
		void		RemoveOfflineShop(LPDESC d, const char* c_pData);
		void		ChangeOfflineShopTime(LPDESC d, const char* c_pData);
		void		OfflineShopBuy(LPDESC d, const char* c_pData);
		void		LoadOfflineShopPanelData(LPDESC d, const char* c_pData);
		void		AddOfflineShopItemData(LPDESC d, const char* c_pData);
		void		RemoveOfflineShopItemData(LPDESC d, const char* c_pData);
		void		CloseOfflineShopData(LPDESC d, const char* c_pData);
		void		ChangeOfflineShopName(LPDESC d, const char* c_pData);
		void		AdviseOfflineShopSellOwner(LPDESC d, const char* c_pData);
		void		ChangeOfflineShopItemPrice(LPDESC d, const char* c_pData);
#endif

//arat

	void		RespondChannelStatus(LPDESC desc, const char* pcData);

//altına ekle

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
public:
	void		ChangeChannel(LPDESC desc, const char* pcData);
#endif