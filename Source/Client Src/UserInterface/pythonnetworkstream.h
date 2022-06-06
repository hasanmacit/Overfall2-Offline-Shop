//arat

bool SendShopSellPacketNew(BYTE bySlot, BYTE byCount);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		// Offline Shop
		bool SendOfflineShopEndPacket();
		bool SendOfflineShopBuyPacket(BYTE byCount);
	#ifdef ENABLE_CHEQUE_SYSTEM
		bool SendAddOfflineShopItem(TItemPos bDisplayPos, BYTE bPos, long long lPrice, int iPriceCheque);
	#else
		bool SendAddOfflineShopItem(TItemPos bDisplayPos, BYTE bPos, long long lPrice);
	#endif
		bool SendRemoveOfflineShopItem(BYTE bPos);
		bool SendDestroyOfflineShop();
		bool SendRefreshOfflineShop(int iDelay = 0);
		bool SendRefreshOfflineShopMoney(int iDelay = 0);
		bool SendRefreshUnsoldItems();
		bool SendOfflineShopWithdrawMoney(long long llMoney);
	#ifdef ENABLE_CHEQUE_SYSTEM
		bool SendOfflineShopWithdrawCheque(DWORD dwCheque);
	#endif
		bool SendOfflineShopTakeItem(BYTE bDisplayPos);
		bool SendOfflineShopChangeItemPrice(BYTE bDisplayPos, long long llPrice);
		bool SendOfflineShopCheck(int iDelay = 0);
		bool SendChangeOfflineShopName(const char * szShopName);
#endif

//arat

bool SendBuildPrivateShopPacket(const char * c_szName, const std::vector<TShopItemTable> & c_rSellingItemStock);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		// Offline Shop
		bool SendBuildOfflineShopPacket(const char * c_szName, const std::vector<TOfflineShopItemTable> & c_rSellingItemStock, BYTE bNpcType = 0, BYTE bBoardStyle = 0);
#endif

//arat

bool RecvExchangePacket();

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		bool RecvOfflineShopPacket();
		bool RecvOfflineShopSignPacket();
		bool RecvOfflineShopOpenPanelPacket();
		bool RecvOfflineShopStartP2PPacket();
		bool RecvOfflineShopChangeSignPacket();
		bool RecvOfflineShopChangeSignPacketP2P();
		bool RecvOfflineShopPlayerBuyItem();
#endif

//arat

	public:
		void SetOffLinePhase();

//üstüne ekle

#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
	public:
		bool SendNewPrivateShopSearchInfo(int32_t ItemCat, int32_t SubCat, char* ItemName, int minLevelValue, int maxLevelValue, int minDHValue, int maxDHValue, int minDMValue, int maxDMValue, int itemRefineLevel, int acceAbsPerc, int dsClarityValue, int bonusChoose, int itemGender, int have_name);
		bool RecvNewShopSearchSet();
#endif

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	public:
	#ifdef ENABLE_CHEQUE_SYSTEM
		bool SendPrivateShopSearchInfo(int32_t Race, int32_t ItemCat, int32_t SubCat, int32_t MinLevel, int32_t MaxLevel, int32_t MinRefine, int32_t MaxRefine, uint64_t MinGold, uint64_t MaxGold, uint64_t MinCheque, uint64_t MaxCheque);
		bool SendPrivateShopSearchInfoSub(int32_t Race, int32_t ItemCat, int32_t SubCat, int32_t MinLevel, int32_t MaxLevel, int32_t MinRefine, int32_t MaxRefine, uint64_t MinGold, uint64_t MaxGold, char* ItemName, uint64_t MinCheque, uint64_t MaxCheque);
	#else
		bool SendPrivateShopSearchInfo(int32_t Race, int32_t ItemCat, int32_t SubCat, int32_t MinLevel, int32_t MaxLevel, int32_t MinRefine, int32_t MaxRefine, uint64_t MinGold, uint64_t MaxGold);
		bool SendPrivateShopSearchInfoSub(int32_t Race, int32_t ItemCat, int32_t SubCat, int32_t MinLevel, int32_t MaxLevel, int32_t MinRefine, int32_t MaxRefine, uint64_t MinGold, uint64_t MaxGold, char* ItemName);
	#endif
		bool SendPrivateShopSerchBuyItem(int32_t shopVid, BYTE shopItemPos, int shopPos, DWORD item_id, long long llPrice);
		bool RecvShopSearchSet();
#endif

//arat

void __RefreshMallWindow();

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
		void __RefreshShopSearchWindow();
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
		void __RefreshNewShopSearchWindow();
#endif

//arat

bool m_isRefreshGuildWndGradePage;

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
		bool m_isRefreshShopSearchWnd;
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
		bool m_isRefreshNewShopSearchWnd;
#endif