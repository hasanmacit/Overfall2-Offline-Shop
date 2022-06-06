//arat

short	m_sAlignment;

//üstüne ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
			DWORD	m_dwMyShopVID;
#endif

//arat

NEW_AFFECT_DRAGON_SOUL_DECK2 = 542,

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
			AFFECT_OFFLINE_SHOP = 311,
#endif

//arat

NAMECOLOR_WAYPOINT

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
			NAMECOLOR_OFFLINESHOP,
#endif

//arat

ChangeHair(DWORD eHair);

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
		void					SetOfflineShopVid(DWORD dwShopVID) { m_dwMyShopVID = dwShopVID; }
		DWORD					GetOfflineShopVid() const { return m_dwMyShopVID; }
#endif

//arat

DWORD					m_dwGuildID;

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
		DWORD					m_dwMyShopVID;
#endif

//arat

AFFECT_NUM = 64,

//üstüne ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
			AFF_OVERFALL_PREMIUM,
#endif

//arat

NEW_AFFECT_QUEST_START_IDX

//üstüne ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
			NEW_AFFECT_OVERFALL_PREMIUM = 724,
#endif

//arat

IsGameMaster();

//altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
		BOOL					IsOverfallPremium();
#endif

//(DOSYALARINIZDA YOKSA HEMEN ALTINA EKLEYİN)

		BOOL					IsShop();