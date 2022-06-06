//arat

} TPlayerTable;

//üstüne ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	long long llOfflineShopMoney;
#endif

//arat

} TShopTable;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
typedef struct SOfflineShopItemTable
{
	DWORD		vnum;
#ifdef __EXTENDED_ITEM_COUNT__
	short		count;
#else
	BYTE		count;
#endif

	TItemPos	pos;
	long long		price;
#ifdef __CHEQUE_SYSTEM__
	DWORD		price_cheque;
#endif
	BYTE		display_pos;
} TOfflineShopItemTable;

typedef struct SSOfflineShopItemTable
{
	TItemPos	bPos;
	BYTE		bDisplayPos;
	long long		dwPrice;
#ifdef __CHEQUE_SYSTEM__
	DWORD		dwPriceCheque;
#endif
} TOfflineShopItemTable2;

typedef struct SOfflineShopItem
{
	DWORD	id;
	DWORD	owner_id;
	BYTE	pos;
#ifdef __EXTENDED_ITEM_COUNT__
	short	count;
#else
	BYTE	count;
#endif
	long long	price;
#ifdef __CHEQUE_SYSTEM__
	DWORD	price_cheque;
#endif
	DWORD	vnum;
	long	alSockets[ITEM_SOCKET_MAX_NUM];
	TPlayerItemAttribute	aAttr[ITEM_ATTRIBUTE_MAX_NUM];
	BYTE	status;
	char	szBuyerName[CHARACTER_NAME_MAX_LEN + 1];
#ifdef __BL_TRANSMUTATION__
	DWORD	dwTransmutationVnum;
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	char	szName[ITEM_NAME_MAX_LEN + 1];
	BYTE	refine_level;
	DWORD	shop_id;
#endif
	SOfflineShopItem()
	{
		id = 0;
		owner_id = 0;
		pos = 0;
		count = 0;
		price = 0;
#ifdef __CHEQUE_SYSTEM__
		price_cheque = 0;
#endif
		vnum = 0;
		alSockets[0] = 0;
		alSockets[1] = 0;
		alSockets[2] = 0;
		alSockets[3] = 0;
		alSockets[4] = 0;
		alSockets[5] = 0;
		aAttr[0].bType = 0;
		aAttr[0].sValue = 0;
		aAttr[1].bType = 0;
		aAttr[1].sValue = 0;
		aAttr[2].bType = 0;
		aAttr[2].sValue = 0;
		aAttr[3].bType = 0;
		aAttr[3].sValue = 0;
		aAttr[4].bType = 0;
		aAttr[4].sValue = 0;
		aAttr[5].bType = 0;
		aAttr[5].sValue = 0;
		aAttr[6].bType = 0;
		aAttr[6].sValue = 0;
		aAttr[7].bType = 0;
		aAttr[7].sValue = 0;
		aAttr[8].bType = 0;
		aAttr[8].sValue = 0;
		aAttr[9].bType = 0;
		aAttr[9].sValue = 0;
		aAttr[10].bType = 0;
		aAttr[10].sValue = 0;
		aAttr[11].bType = 0;
		aAttr[11].sValue = 0;
		aAttr[12].bType = 0;
		aAttr[12].sValue = 0;
		aAttr[13].bType = 0;
		aAttr[13].sValue = 0;
		aAttr[14].bType = 0;
		aAttr[14].sValue = 0;
		status = 0;
		szBuyerName[CHARACTER_NAME_MAX_LEN + 1] = 0;
#ifdef __BL_TRANSMUTATION__
		dwTransmutationVnum = 0;
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
		szName[ITEM_NAME_MAX_LEN + 1] = 0;
		refine_level = 0;
		shop_id = 0;
#endif
	}
} TOfflineShopItem;

#endif

//en alta ekle

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
typedef struct SPacketChangeChannel
{
	int iChannel;
	
	long lMapIndex;
	long x;
	long y;
	
	SPacketChangeChannel() : lMapIndex(-1), x(-1), y(-1) {};
} TPacketChangeChannel;

typedef struct SPacketReturnChannel
{
	long lAddr;
	WORD wPort;
	
	long lMapIndex;
	long x;
	long y;
	
	SPacketReturnChannel() : lMapIndex(-1), x(-1), y(-1) {};
} TPacketReturnChannel;
#endif