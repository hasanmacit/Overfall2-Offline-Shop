enum
{
	OFFLINE_SHOP_MAX_DISTANCE = 1500,
	OFFLINE_SHOP_BUY_FEE = 3,
};

class COfflineShop
{
	public:
		typedef struct offline_shop_item
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
			offline_shop_item()
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
		} OFFLINE_SHOP_ITEM;

		COfflineShop();
		~COfflineShop();

		virtual void	SetOfflineShopNPC(LPCHARACTER npc);
		virtual bool	IsOfflineShopNPC(){ return m_pkOfflineShopNPC ? true : false; }
		LPCHARACTER		GetOfflineShopNPC() { return m_pkOfflineShopNPC; }

		void			CreateTable(DWORD dwOwnerPID);
#ifdef __EXTENDED_ITEM_COUNT__
		void			SetOfflineShopItems(DWORD dwOwnerPID, TOfflineShopItemTable * pTable, short bItemCount);
#else
		void			SetOfflineShopItems(DWORD dwOwnerPID, TOfflineShopItemTable * pTable, BYTE bItemCount);
#endif
#ifdef __CHEQUE_SYSTEM__
		void			AddItem(LPCHARACTER ch, LPITEM pkItem, BYTE bPos, long long iPrice, int iPriceCheque);
#else
		void			AddItem(LPCHARACTER ch, LPITEM pkItem, BYTE bPos, long long iPrice);
#endif
		void			RemoveItem(LPCHARACTER ch, BYTE bPos);

		virtual bool	AddGuest(LPCHARACTER ch, LPCHARACTER npc);

		void			RemoveGuest(LPCHARACTER ch);
		void			RemoveAllGuest();
		void			Destroy(LPCHARACTER npc);

		virtual int		Buy(LPCHARACTER ch, BYTE bPos, DWORD item_id = 0, long long llPriceCheck = 0);

		void			BroadcastUpdateItem(BYTE bPos, DWORD dwPID, bool bDestroy = false);
		void			BroadcastUpdatePrice(DWORD dwPID, BYTE bPos, long long dwPrice);
		void			Refresh(LPCHARACTER ch);

		bool			RemoveItem(DWORD dwVID, BYTE bPos);
		BYTE			GetLeftItemCount();
		void			SetOfflineShopGold(long long val) { llGold = val; }
		long long		GetOfflineShopGold() const { return llGold; }
#ifdef __CHEQUE_SYSTEM__
		void			SetOfflineShopCheque(DWORD val) { dwCheque = val; }
		DWORD			GetOfflineShopCheque() const { return dwCheque; }
#endif
		void			SetOfflineShopMapIndex(long idx) { m_llMapIndex = idx; }
		long			GetOfflineShopMapIndex() const { return m_llMapIndex; }
		void			SetOfflineShopTime(int iTime) { m_iTime = iTime; }
		int				GetOfflineShopTime() const { return m_iTime; }
		void			SetOfflineShopBankValues(DWORD dwOwnerPID);

		std::string shopSign;
		const char *	GetShopSign() { return shopSign.c_str(); };
		void			SetShopSign(const char * c) { shopSign = c; };

		std::vector<OFFLINE_SHOP_ITEM>	GetItemVector() { return m_itemVector; }

		void			SetGuestMap(LPCHARACTER ch);
		void			RemoveGuestMap(LPCHARACTER ch);
		
		/*
			Overfall2 Work
		*/
		virtual void	SetOfflineShopBorderStyle(BYTE bBorderStyle);
		BYTE			GetBorderStyle() const { return m_pkOfflineShopBorderStyle; }
		DWORD			GetDisplayedCount() const { return m_dwDisplayedCount; }
		void			RefreshP2P(DWORD dwPID);
		void			AddItemP2P(DWORD dwPID, TOfflineShopItem pkItem, BYTE bPos, long long iPrice);
		void			RemoveItemP2P(DWORD dwPID, BYTE bPos);
		bool			ChangeItemPrice(DWORD dwPID, BYTE bPos, long long llPrice);
		long long		GetOfflineShopItemPrice(BYTE bPos);
		
		void SetAlreadySeeShop(DWORD dwPID) { v_alreadySeeShop.push_back(dwPID); }
		bool AlreadySeeShop(DWORD dwPID) { return (bool)(std::find(v_alreadySeeShop.begin(), v_alreadySeeShop.end(), dwPID) != v_alreadySeeShop.end()); }

	protected:
		void			Broadcast(const void * data, int bytes);

	private:
		// Grid
		CGrid *				m_pGrid;
		long long			llGold;
#ifdef __CHEQUE_SYSTEM__
		DWORD				dwCheque;
#endif
		long				m_llMapIndex;
		int					m_iTime;

		// Guest Map
		#ifdef __OFFLINE_SHOP_PID_MAP_GUESTS__
		typedef std::vector<DWORD> GuestMapType;
		#else
		typedef std::unordered_map<LPCHARACTER, bool> GuestMapType;
		#endif
		GuestMapType m_map_guest;
		// End Of Guest Map

		std::vector<OFFLINE_SHOP_ITEM>		m_itemVector;
		std::vector<DWORD>					v_alreadySeeShop;

		LPCHARACTER m_pkOfflineShopNPC;
		DWORD	m_dwDisplayedCount;
		BYTE	m_pkOfflineShopBorderStyle;
};

#pragma once