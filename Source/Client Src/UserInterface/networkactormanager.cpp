//arat

	m_stName = src.m_stName;

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
	m_dwMyShopVID = src.m_dwMyShopVID;
#endif

//arat

m_stName="";

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
	m_dwMyShopVID = 0;
#endif

//arat

kCreateData.m_isMain=__IsMainActorVID(dwVID);

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
	kCreateData.m_dwMyShopVID = rkNetActorData.m_dwMyShopVID;
#endif

//arat

pkInstFind->SetStateFlags(c_rkNetUpdateActorData.m_dwStateFlags);

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
		pkInstFind->SetOfflineShopVid(c_rkNetUpdateActorData.m_dwMyShopVID);
#endif

//arat

rkNetActorData.m_byPKMode=c_rkNetUpdateActorData.m_byPKMode;

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
	rkNetActorData.m_dwMyShopVID = c_rkNetUpdateActorData.m_dwMyShopVID;
#endif