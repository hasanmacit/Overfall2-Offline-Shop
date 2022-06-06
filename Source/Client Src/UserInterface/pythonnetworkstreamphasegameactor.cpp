//arat

kNetActorData.m_dwHair=0;/*chrAddPacket.awPart[CHR_EQUIPPART_HAIR]*/;

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
	kNetActorData.m_dwMyShopVID = 0;
#endif

//arat

kNetActorData.m_dwHair		= chrInfoPacket.awPart[CHR_EQUIPPART_HAIR];

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
		kNetActorData.m_dwMyShopVID = chrInfoPacket.dwMyShopVID;
#endif

//arat

kNetUpdateActorData.m_dwMountVnum=chrUpdatePacket.dwMountVnum;

//altına ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
	kNetUpdateActorData.m_dwMyShopVID = chrUpdatePacket.dwMyShopVID;
#endif