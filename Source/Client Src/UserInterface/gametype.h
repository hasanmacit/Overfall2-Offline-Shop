//arat

ON_TOP_WND_PET_FEED,

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	ON_TOP_WND_OFFLINE_SHOP,			// 5
	ON_TOP_WND_OFFLINE_SHOP_MANAGER,	// 6
#endif

//arat

	SLOT_TYPE_DRAGON_SOUL_INVENTORY,

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	SLOT_TYPE_OFFLINE_SHOP,
#endif

//arat

} TShopItemData;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
typedef struct packet_offline_shop_item
{
	DWORD		vnum;
	long long		price;
#ifdef ENABLE_CHEQUE_SYSTEM
	DWORD		price_cheque;
#endif
#ifdef ENABLE_EXTENDED_ITEM_COUNT
	short		count;
#else
	BYTE		count;
#endif
	BYTE		display_pos;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
	BYTE		status;
	char		szBuyerName[72];
#ifdef __BL_TRANSMUTATION__
	DWORD		dwTransmutationVnum;
#endif
} TOfflineShopItemData;
#endif