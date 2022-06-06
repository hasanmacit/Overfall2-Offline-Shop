//arat

HEADER_CG_MYSHOP

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	HEADER_CG_OFFLINE_SHOP						= 57,
	HEADER_CG_MY_OFFLINE_SHOP					= 58,
	HEADER_CG_OFFLINE_SHOP_CHANGE_SHOP_NAME		= 62,
#endif
#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	HEADER_CG_SHOP_SEARCH						= 220,
	HEADER_CG_SHOP_SEARCH_SUB					= 221,
	HEADER_CG_SHOP_SEARCH_BUY					= 222,
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
	HEADER_CG_NEW_SHOP_SEARCH					= 223,
#endif

//arat

HEADER_GC_QUEST_CONFIRM

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	HEADER_GC_OFFLINE_SHOP						= 47,
	HEADER_GC_OFFLINE_SHOP_SIGN					= 48,
	HEADER_GC_OFFLINE_SHOP_OPEN_PANEL			= 49,
	HEADER_GC_OFFLINE_SHOP_START_P2P			= 50,
	HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN			= 51,
	HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN_P2P		= 52,
	HEADER_GC_OFFLINE_ADVISE_PLAYER_BUY			= 53,
#endif
#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	HEADER_GC_SHOPSEARCH_SET					= 156,
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
	HEADER_GC_NEW_SHOPSEARCH_SET				= 157,
#endif

//arat

SHOP_HOST_ITEM_MAX_NUM = 40,

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	OFFLINE_SHOP_HOST_ITEM_MAX_NUM = 80,
#endif

//arat

SHOP_SUBHEADER_CG_SELL2

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	SHOP_SUBHEADER_CG_ADD_ITEM,
	SHOP_SUBHEADER_CG_REMOVE_ITEM,
	SHOP_SUBHEADER_CG_DESTROY_OFFLINE_SHOP,
	SHOP_SUBHEADER_CG_REFRESH,
	SHOP_SUBHEADER_CG_REFRESH_MONEY,
	SHOP_SUBHEADER_CG_WITHDRAW_MONEY,
	#ifdef ENABLE_CHEQUE_SYSTEM
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

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
typedef struct command_offline_shop
{
	BYTE		header;
	BYTE		subheader;
} TPacketCGOfflineShop;

typedef struct SPacketCGChangeOfflineShopName
{
	BYTE		bHeader;
	char		szSign[SHOP_SIGN_MAX_LEN + 1];
} TPacketCGChangeOfflineShopName;
#endif

//arat

} TShopItemTable;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
typedef struct SOfflineShopItemTable
{
	DWORD		vnum;
#ifdef ENABLE_EXTENDED_ITEM_COUNT
	short		count;
#else
	BYTE		count;
#endif

	TItemPos	pos;
	long long		price;
#ifdef ENABLE_CHEQUE_SYSTEM
	DWORD		price_cheque;
#endif
	BYTE		display_pos;
} TOfflineShopItemTable;

typedef struct SOfflineShopItemTable2
{
	TItemPos	bDisplayPos;
	BYTE		bPos;
	long long		dwPrice;
#ifdef ENABLE_CHEQUE_SYSTEM
	DWORD		dwPriceCheque;
#endif
} TOfflineShopItemTable2;
#endif

//arat

} TPacketCGMyShop;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
typedef struct TPacketCGMyOfflineShop
{
	BYTE	bHeader;
	char	szSign[SHOP_SIGN_MAX_LEN + 1];
#ifdef ENABLE_EXTENDED_ITEM_COUNT
	short	bCount;
#else
	BYTE	bCount;
#endif
	BYTE	bNpcType;
	BYTE	bBoardStyle;
} TPacketCGMyOfflineShop;
#endif

//arat

} TPacketGCCharacterAdditionalInfo;

//üstüne ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
	DWORD	dwMyShopVID;
#endif

//arat

} TPacketGCCharacterUpdate;

//üstüne ekle

#if defined(ENABLE_OFFLINE_SHOP_SYSTEM)
	DWORD		dwMyShopVID;
#endif

//arat

} TPacketGCShopStart;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
typedef struct packet_offline_shop_start
{
	struct packet_offline_shop_item items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
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

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
typedef struct packet_offline_shop_update_item
{
	BYTE						pos;
	struct packet_offline_shop_item item;
} TPacketGCOfflineShopUpdateItem;

typedef struct packet_offline_shop_money
{
	long long	llMoney;
#ifdef ENABLE_CHEQUE_SYSTEM
	DWORD		dwCheque;
#endif
} TPacketGCOfflineShopMoney;
#endif

//arat

typedef struct packet_shop_update_price
{

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	BYTE	bPos;
	DWORD	dwShopVid;
	long long iPrice;
#endif

//arat

} TPacketGCShopSign;

//üstüne ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	BYTE	bBorderStyle;
	SPacketGCShopSign() : bBorderStyle(0) {};
#endif

//arat

enum EPacketShopSubHeaders

//komple değiştir

enum EPacketShopSubHeaders
{
	SHOP_SUBHEADER_GC_START,
    SHOP_SUBHEADER_GC_END,
	SHOP_SUBHEADER_GC_UPDATE_ITEM,
	SHOP_SUBHEADER_GC_UPDATE_PRICE,
    SHOP_SUBHEADER_GC_OK,
    SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY,
    SHOP_SUBHEADER_GC_SOLDOUT,
    SHOP_SUBHEADER_GC_INVENTORY_FULL,
    SHOP_SUBHEADER_GC_INVALID_POS,
	SHOP_SUBHEADER_GC_SOLD_OUT,
	SHOP_SUBHEADER_GC_START_EX,
	SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY_EX,
#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	SHOP_SUBHEADER_GC_UPDATE_ITEM2,
	SHOP_SUBHEADER_GC_REFRESH_MONEY,
	SHOP_SUBHEADER_GC_CHECK_RESULT,
#endif
	SHOP_SUBHEADER_GC_BUY_FROM_OWNSHOP,
	SHOP_SUBHEADER_GC_REMOVED_FROM_SHOP,
	SHOP_SUBHEADER_GC_PRICE_CHANGED,
	SHOP_SUBHEADER_GC_YOU_ALREADY_HAVE_ONE,
	SHOP_SUBHEADER_GC_YOU_DONT_HAVE_DS,
};

//en alta ekle

#if defined(ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM) || defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
typedef struct packet_priv_shop_item_set
{
	BYTE header;
	DWORD vid;
	BYTE Cell;
	long long price;
#ifdef ENABLE_CHEQUE_SYSTEM
	DWORD price_cheque;
#endif
	DWORD vnum;
	short count;
	DWORD flags;
	DWORD anti_flags;
	long alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
#ifdef __BL_TRANSMUTATION__
	DWORD dwTransmutationVnum;
#endif
	int shop_time;
	long ch_map_index;
	long off_shop_map_index;
	DWORD item_id;
	char sellerName[20];
} TPacketGCShopSearchItemSet;

typedef struct SPacketGCOfflineShopAdviseOwnerSell
{
	BYTE		bHeader;
	DWORD		dwOwnerPID;
	DWORD		itemSelled;
	long long	itemPrice;
	char		buyerName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCOfflineShopAdviseOwnerSell;

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
#ifdef ENABLE_CHEQUE_SYSTEM
	unsigned int MinCheque;
	unsigned int MaxCheque;
#endif
	char ItemName[SHOP_TAB_NAME_MAX + 1];
} TPacketCGShopSearch;

typedef struct command_shop_search_buy
{
	BYTE header;
	int shopVid;
	BYTE shopItemPos;
	int shopPos;
	DWORD item_id;
	long long item_price;
} TPacketCGShopSearchBuy;
#endif

#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
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