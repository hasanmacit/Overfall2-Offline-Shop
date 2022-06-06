//arat

void	SetPlayTime(DWORD dwPlayTime);

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		void	SetCurrentOfflineShopMoney(long long llMoney);
		long long	GetCurrentOfflineShopMoney();
	#ifdef ENABLE_CHEQUE_SYSTEM
		void	SetCurrentOfflineShopCheque(DWORD dwCheque);
		DWORD	GetCurrentOfflineShopCheque();
	#endif
		bool	HasOfflineShop() { return m_bHasOfflineShop; }
		void	SetHasOfflineShop(bool bStatus) { m_bHasOfflineShop = bStatus; }
#endif

//arat

DWORD					m_dwPlayTime;

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		long long				m_llCurrentOfflineShopMoney;
	#ifdef ENABLE_CHEQUE_SYSTEM
		DWORD					m_dwCurrentOfflineShopCheque;
	#endif
		bool					m_bHasOfflineShop;
#endif