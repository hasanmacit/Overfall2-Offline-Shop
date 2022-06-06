//arat

BOOL GetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData ** c_ppItemData);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		void SetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData & c_rShopItemData);
		BOOL GetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData ** c_ppItemData);

		void SetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData & c_rShopItemData);
		BOOL GetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData ** c_ppItemData);
#endif

//arat

const char* GetTabName(BYTE tabIdx);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		void SetShopDisplayedCount(DWORD dwDisplayedCount);
		DWORD GetShopDisplayedCount();
#endif

//arat

void Open

//değiştir

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		void Open(BOOL isPrivateShop, BOOL isMainPrivateShop, BOOL isOfflineShop);
#else
		void Open(BOOL isPrivateShop, BOOL isMainPrivateShop);
#endif

//arat

BOOL IsMainPlayerPrivateShop();

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		BOOL IsOfflineShop();
#endif

//arat

void BuildPrivateShop(const char * c_szName);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		void ClearOfflineShopStock();
	#ifdef ENABLE_CHEQUE_SYSTEM
		void AddOfflineShopItemStock(TItemPos ItemPos, BYTE byDisplayPos, long long dwPrice, DWORD dwPriceCheque);
	#else
		void AddOfflineShopItemStock(TItemPos ItemPos, BYTE byDisplayPos, long long dwPrice);
	#endif
		void DelOfflineShopItemStock(TItemPos ItemPos);
		long long GetOfflineShopItemPrice(TItemPos ItemPos);
	#ifdef ENABLE_CHEQUE_SYSTEM
		int GetOfflineShopItemPriceCheque(TItemPos ItemPos);
	#endif
		BYTE GetOfflineShopItemStatus(TItemPos ItemPos);
		void BuildOfflineShop(const char * c_szName, BYTE bNpcType, BYTE bBoardStyle);
#endif

//arat

BOOL				m_isMainPlayerPrivateShop;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		BOOL				m_isOfflineShop;
#endif

//arat

		struct ShopTab
		{
			ShopTab()
			{
				coinType = SHOP_COIN_TYPE_GOLD;
			}
			BYTE				coinType;
			std::string			name;
			TShopItemData		items[SHOP_HOST_ITEM_MAX_NUM];
		};

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		struct OfflineShopTab
		{
			OfflineShopTab()
			{
				coinType = SHOP_COIN_TYPE_GOLD;
			}
			BYTE				coinType;
			std::string			name;
			TOfflineShopItemData items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
		};

		DWORD				m_dwDisplayedCount;
#endif

//arat

ShopTab m_aShoptabs[SHOP_TAB_COUNT_MAX];

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		OfflineShopTab m_aOfflineShoptabs[SHOP_TAB_COUNT_MAX];
#endif

//arat

		typedef std::map<TItemPos, TShopItemTable> TPrivateShopItemStock;
		TPrivateShopItemStock	m_PrivateShopItemStock;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		typedef std::map<TItemPos, TOfflineShopItemTable> TOfflineShopItemStock;
		TOfflineShopItemStock	m_OfflineShopItemStock;
#endif