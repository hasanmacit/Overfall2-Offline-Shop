//arat

HEADER_CG_MYSHOP

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	HEADER_CG_OFFLINE_SHOP = 57,
	HEADER_CG_MY_OFFLINE_SHOP = 58,
	HEADER_CG_OFFLINE_SHOP_CHANGE_SHOP_NAME = 62,
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	HEADER_CG_SHOP_SEARCH = 220,
	HEADER_CG_SHOP_SEARCH_SUB = 221,
	HEADER_CG_SHOP_SEARCH_BUY = 222,
#endif
#if defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
	HEADER_CG_NEW_SHOP_SEARCH = 223,
#endif

//arat

HEADER_GC_QUEST_CONFIRM

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	HEADER_GC_OFFLINE_SHOP = 47,
	HEADER_GC_OFFLINE_SHOP_SIGN = 48,
	HEADER_GC_OFFLINE_SHOP_OPEN_PANEL = 49,
	HEADER_GC_OFFLINE_SHOP_START_P2P = 50,
	HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN = 51,
	HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN_P2P = 52,
	HEADER_GC_OFFLINE_ADVISE_PLAYER_BUY = 53,
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	HEADER_GC_SHOPSEARCH_SET = 156,
#endif
#if defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
	HEADER_GC_NEW_SHOPSEARCH_SET = 157,
#endif

//arat

HEADER_GG_PCBANG_UPDATE

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	HEADER_GG_REMOVE_OFFLINE_SHOP = 32,
	HEADER_GG_OFFLINE_SHOP_BUY = 33,
	HEADER_GG_CHANGE_OFFLINE_SHOP_TIME = 34,
	HEADER_GG_OFFLINE_SHOP_OPEN_PANEL = 35,
	HEADER_GG_OFFLINE_SHOP_ADD_ITEM = 36,
	HEADER_GG_OFFLINE_SHOP_REMOVE_ITEM = 37,
	HEADER_GG_OFFLINE_SHOP_CLOSE_SHOP = 38,
	HEADER_GG_OFFLINE_SHOP_CHANGE_NAME = 39,
	HEADER_GG_OFFLINE_SHOP_ADVISE_PLAYER = 40,
	HEADER_GG_OFFLINE_SHOP_CHANGE_ITEM_PRICE = 41,
#endif

//arat

} TPacketGGBlockChat;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
typedef struct SPacketGGRemoveOfflineShop
{
	BYTE	bHeader;
	long	lMapIndex;
	char	szNpcName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGGRemoveOfflineShop;

typedef struct SPacketGGOfflineShopBuy
{
	BYTE	bHeader;
	long long	dwMoney;
#ifdef __CHEQUE_SYSTEM__
	DWORD	dwCheque;
#endif
	char	szBuyerName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGGOfflineShopBuy;

typedef struct SPacketGGChangeOfflineShopTime
{
	BYTE	bHeader;
	int		bTime;
	long	lMapIndex;
	DWORD	dwOwnerPID;
} TPacketGGChangeOfflineShopTime;

/*Usado na comunicao P2P, tempo e mapindex tem values default pois nem sempre sao utilizados
*/
enum EOpenOfflineShopPanel
{
	OFFLINE_SHOP_PANEL_SEARCH_SHOP,
	OFFLINE_SHOP_PANEL_SEND_DATA,
};
typedef struct SPacketGGOpenOffShopPanel
{
	BYTE	bHeader;
	BYTE	bSubHeader;
	int		iTime;
	long	lMapIndex;
	DWORD	dwOwnerPID;
	BYTE	shopChannel;
	char	shopName[SHOP_SIGN_MAX_LEN + 1];
	DWORD	displayedCount;
	
	//Inicializa só as variaveis que não são usadas para comunicar entre ch's P2P
	SPacketGGOpenOffShopPanel() : iTime(0), lMapIndex(0), shopChannel(0), displayedCount(0)
	{
		memset(&shopName, 0, sizeof(shopName));
	};
} TPacketGGOpenOffShopPanel;
//

typedef struct SPacketGGAddOfflineShopItem
{
	BYTE	bHeader;
	TOfflineShopItem itemAdd;
	DWORD	dwOwnerPID;
	BYTE	pos;
	long long		price;
	TItemPos itemPos;
} TPacketGGAddOfflineShopItem;

enum OfflineShopRemoveItemSubHeader
{
	OFFLINE_SHOP_SEND_REMOVE_ITEM,
	OFFLINE_SHOP_FORCE_REMOVE_ITEM,
};

typedef struct SPacketGGRemoveOfflineShopItem
{
	BYTE	bHeader;
	BYTE	bSubHeader;
	DWORD	dwOwnerPID;
	BYTE	bPos;
	TPlayerItem	item;
	
	SPacketGGRemoveOfflineShopItem() : dwOwnerPID(0), bPos(0) {
		memset(&item, 0, sizeof(item));
	};
	
} TPacketGGRemoveOfflineShopItem;

typedef struct SPacketGGChangeOfflineShopItemPrice
{
	BYTE		bHeader;
	DWORD		dwOwnerPID;
	BYTE		bPos;
	long long	llPrice;
} TPacketGGChangeOfflineShopItemPrice;

typedef struct SPacketGGOfflineShopClose
{
	BYTE	bHeader;
	DWORD	dwOwnerPID;
} TPacketGGOfflineShopClose;

typedef struct SPacketGGOfflineShopChangeName
{
	BYTE bHeader;
	DWORD dwOwnerPID;
	char szSign[SHOP_SIGN_MAX_LEN + 1];
} TPacketGGOfflineShopChangeName;

typedef struct SPacketGGOfflineShopAdviseOwnerSell
{
	BYTE		bHeader;
	DWORD		dwOwnerPID;
	DWORD		itemSelled;
	long long	itemPrice;
	char		buyerName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGGOfflineShopAdviseOwnerSell;
#endif

//arat

SHOP_SUBHEADER_CG_SELL2

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	SHOP_SUBHEADER_CG_ADD_ITEM,
	SHOP_SUBHEADER_CG_REMOVE_ITEM,
	SHOP_SUBHEADER_CG_DESTROY_OFFLINE_SHOP,
	SHOP_SUBHEADER_CG_REFRESH,
	SHOP_SUBHEADER_CG_REFRESH_MONEY,
	SHOP_SUBHEADER_CG_WITHDRAW_MONEY,
#ifdef __CHEQUE_SYSTEM__
	SHOP_SUBHEADER_CG_WITHDRAW_CHEQUE,
#endif
	SHOP_SUBHEADER_CG_REFRESH_UNSOLD_ITEMS,
	SHOP_SUBHEADER_CG_TAKE_ITEM,
	SHOP_SUBHEADER_CG_CHECK,
	SHOP_SUBHEADER_CG_CHANGE_ITEM_PRICE,
#endif

//arat

} TPacketCGShop;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
typedef struct command_offline_shop
{
	BYTE	header;
	BYTE	subheader;
} TPacketCGOfflineShop;

typedef struct SPacketCGChangeOfflineShopName
{
	BYTE		bHeader;
	char		szSign[SHOP_SIGN_MAX_LEN + 1];
} TPacketCGChangeOfflineShopName;
#endif

//arat

} TPacketGCCharacterAdditionalInfo;

//üstüne ekle

#if defined(__OFFLINE_PRIVATE_SHOP_SYSTEM__)
	DWORD	dwMyShopVID;
#endif

//arat

} TPacketGCCharacterUpdate;

//üstüne ekle

#if defined(__OFFLINE_PRIVATE_SHOP_SYSTEM__)
	DWORD	dwMyShopVID;
#endif

//arat

SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#ifdef __CHEQUE_SYSTEM__
	SHOP_SUBHEADER_GC_NOT_ENOUGH_CHEQUE,
#endif
#ifdef __CHEQUE_SYSTEM__
	SHOP_SUBHEADER_GC_NOT_ENOUGH_CHEQUE_MONEY,
#endif
	SHOP_SUBHEADER_GC_UPDATE_ITEM2,
	SHOP_SUBHEADER_GC_REFRESH_MONEY,
	SHOP_SUBHEADER_GC_CHECK_RESULT,
	SHOP_SUBHEADER_GC_BUY_FROM_OWNSHOP,
	SHOP_SUBHEADER_GC_REMOVED_FROM_SHOP,
	SHOP_SUBHEADER_GC_PRICE_CHANGED,
	SHOP_SUBHEADER_GC_YOU_ALREADY_HAVE_ONE,
	SHOP_SUBHEADER_GC_YOU_DONT_HAVE_DS,
#endif

//arat

} TPacketGCShopStart;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
struct packet_offline_shop_item
{
	DWORD					vnum;
	long long				price;
#ifdef __CHEQUE_SYSTEM__
	DWORD					price_cheque;
#endif
#ifdef __EXTENDED_ITEM_COUNT__
	short					count;
#else
	BYTE					count;
#endif
	BYTE					display_pos;
	long					alSockets[ITEM_SOCKET_MAX_NUM];
	TPlayerItemAttribute	aAttr[ITEM_ATTRIBUTE_MAX_NUM];
	BYTE					status;
	char					szBuyerName[72];
#ifdef __BL_TRANSMUTATION__
	DWORD					dwTransmutationVnum;
#endif
};
#endif

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
typedef struct packet_offline_shop_start
{
	DWORD	owner_vid;
	struct	packet_offline_shop_item items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
	DWORD	m_dwDisplayedCount;
} TPacketGCOfflineShopStart;


typedef struct packet_offline_shop_start_p2p
{
	BYTE	header;
	DWORD	owner_vid;
	struct	packet_offline_shop_item items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
	DWORD	m_dwDisplayedCount;
	
	packet_offline_shop_start_p2p() : owner_vid(0), m_dwDisplayedCount(0)
	{
		memset(&items, 0, sizeof(items));
	};
	
} TPacketGCOfflineShopStartP2P;

/*Usado para abrir o painel do utilizador
*/
typedef struct SPacketGCOpenOffShopPanel
{
	BYTE	bHeader;
	BYTE	hasOfflineShop;
	long	lMapIndex;
	BYTE	shopChannel;
	int		iTime;
	BYTE	isPremium;
	DWORD	displayedCount;
	char	shopName[SHOP_SIGN_MAX_LEN + 1];
} TPacketGCOpenOffShopPanel;
#endif

//arat

} TPacketGCShopUpdateItem;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
typedef struct packet_offline_shop_update_item
{
	BYTE	pos;
	struct	packet_offline_shop_item item;
} TPacketGCOfflineShopUpdateItem;
#endif

//arat

typedef struct packet_shop_update_price
{

//altına ekle (iprice varsa bununla birlikte paket içeriğini değiştirin)

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	BYTE	bPos;
	DWORD	dwShopVid;
	long long iPrice;
#endif

//arat

} TPacketGCShop;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
typedef struct packet_offline_shop_money
{
	long long	llMoney;
#ifdef __CHEQUE_SYSTEM__
	DWORD		dwCheque;
#endif
} TPacketGCOfflineShopMoney;
#endif

//arat

} TPacketCGMyShop;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
typedef struct TPacketCGMyOfflineShop
{
	BYTE	bHeader;
	char	szSign[SHOP_SIGN_MAX_LEN + 1];
#ifdef __EXTENDED_ITEM_COUNT__
	short	bCount;
#else
	BYTE	bCount;
#endif
	BYTE	bNpcType;
	BYTE	bBoardStyle;
} TPacketCGMyOfflineShop;
#endif

//en alta ekle

#if defined(__PRIVATE_SHOP_SEARCH_SYSTEM__) || defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
typedef struct packet_priv_shop_item_set
{
	BYTE header;
	DWORD vid;
	BYTE Cell;
	long long price;
#ifdef __CHEQUE_SYSTEM__
	DWORD price_cheque;
#endif
	DWORD vnum;
	short count;
	DWORD flags;
	DWORD anti_flags;
	long alSockets[ITEM_SOCKET_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_MAX_NUM];
#ifdef __BL_TRANSMUTATION__
	DWORD dwTransmutationVnum;
#endif
	int shop_time;
	long ch_map_index;
	long off_shop_map_index;
	DWORD item_id;
	char sellerName[20];
} TPacketGCShopSearchItemSet;

typedef struct command_shop_search
{
	BYTE header;
	WORD Race;
	int ItemCat;
	int SubCat;
	int MinLevel;
	int MaxLevel;
	int MinRefine;
	int MaxRefine;
	unsigned int MinGold;
	unsigned int MaxGold;
#ifdef __CHEQUE_SYSTEM__
	unsigned int MinCheque;
	unsigned int MaxCheque;
#endif
	char ItemName[SHOP_TAB_NAME_MAX + 1];
} TPacketCGShopSearch;

typedef struct command_shop_search_buy
{
	BYTE header;
	int32_t shopVid;
	BYTE shopItemPos;
	int shopPos;
	DWORD item_id;
	long long item_price;
} TPacketCGShopSearchBuy;
#endif

#if defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
enum NewSearchShopErrors
{
	NPSS_HAVE_PAGE_OPENED,
	NPSS_PLEASE_WAIT,
	NPSS_NEED_TO_BE_IN_EMPIRE,
	NPSS_NEED_OTHER_ERROR,
};

typedef struct SPacketCGNewShopSearch
{
	BYTE bHeader;
	int ItemCat;
	int SubCat;
	char ItemName[SHOP_TAB_NAME_MAX + 1];
	int minLevelValue;
	int maxLevelValue;
	int minDHValue;
	int maxDHValue;
	int minDMValue;
	int maxDMValue;
	int itemRefineLevel;
	int acceAbsPerc;
	int dsClarityValue;
	int bonusChoose;
	int itemGender;
	int have_name;
} TPacketCGNewShopSearch;
#endif

//arat

} TPacketGCShopSign;

//üstüne ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	BYTE	bBorderStyle;
	SPacketGCShopSign() : bBorderStyle(0) {};
#endif