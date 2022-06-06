//arat

#define INSTANT_FLAG_NO_REWARD			(1 << 4)

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#define INSTANT_FLAG_OFFLINE_SHOP		(1 << 5)
#endif

//arat

} CHARACTER_POINT_INSTANT;

//üstüne ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	DWORD			real_owner;
	bool			isOfflineShop;
	int				leftTime;
	BYTE			bSaveTime;
	BYTE			bChannel;
	DWORD			dwVID;
#endif

//arat

class CShop;
typedef class CShop* LPSHOP;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
class COfflineShop;
typedef class COfflineShop* LPOFFLINESHOP;
#endif

//arat

	int				ChangeEmpire(BYTE empire);

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	bool			CanChangeEmpireOfflineShopCheck();
#endif

//arat

	LPCHARACTER		m_pkChrShopOwner;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
public:
	void SetOfflineShop(LPOFFLINESHOP pkOfflineShop);
	LPOFFLINESHOP GetOfflineShop() const { return m_pkOfflineShop; }

	void SetOfflineShopOwner(LPCHARACTER ch) { m_pkChrOfflineShopOwner = ch; }
	LPCHARACTER GetOfflineShopOwner() const { return m_pkChrOfflineShopOwner; }

	void SetOfflineShopRealOwner(DWORD dwVID) { m_pointsInstant.real_owner = dwVID; }
	DWORD GetOfflineShopRealOwner() const { return m_pointsInstant.real_owner; }

	void SetOfflineShopNPC(bool flag) { m_pointsInstant.isOfflineShop = flag; }
	bool IsOfflineShopNPC() const { return m_pointsInstant.isOfflineShop; }

#ifdef __EXTENDED_ITEM_COUNT__
	void OpenMyOfflineShop(const char* c_pszSign, TOfflineShopItemTable* pTable, short bItemCount, BYTE bStyle, BYTE bBoardStyle);
#else
	void OpenMyOfflineShop(const char* c_pszSign, TOfflineShopItemTable* pTable, BYTE bItemCount, BYTE bStyle, BYTE bBoardStyle);
#endif

	void SetOfflineShopTimer(int iTime) { m_pointsInstant.leftTime = iTime; }
	int GetOfflineShopTimer() { return m_pointsInstant.leftTime; }
	void SetOfflineShopSaveTime(BYTE bSaveTime) { m_pointsInstant.bSaveTime = bSaveTime; }
	BYTE GetOfflineShopSaveTime() { return m_pointsInstant.bSaveTime; }

	void SetOfflineShopSign(const char* c_pszSign);

	void DestroyOfflineShop();

	void StartOfflineShopUpdateEvent();
	void StopOfflineShopUpdateEvent();

	void SetOfflineShopChannel(BYTE bChannel) { m_pointsInstant.bChannel = bChannel; }

	void SetOfflineShopVID(DWORD dwVID) { m_pointsInstant.dwVID = dwVID; }
	DWORD GetOfflineShopVID() { return m_pointsInstant.dwVID; }

	bool HasOfflineShop();
	
	/*
		Overfall2 Work
	*/
	void	OfflineShopPanelPacket(BYTE hasOfflineShop, const char * shopName = "", long lMapIndex = 0, BYTE shopChannel = 0, int iTime = 0, DWORD displayedCount = 0);
	void	OpenOfflineShopPanel();
	BYTE	GetOfflineShopChannel();
	void	TeleportToMyOfflineShop();
	void	ChangeShopSign(DWORD shopVid, const char * newShopName);

protected:
	
	LPOFFLINESHOP m_pkOfflineShop;
	LPCHARACTER m_pkChrOfflineShopOwner;
	std::string m_stOfflineShopSign;
#endif

//arat

LPEVENT				m_pkPetSystemUpdateEvent;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	LPEVENT				m_pkOfflineShopUpdateEvent;
#endif

//arat

	void	SetMyShopTime() { m_iMyShopTime = thecore_pulse(); }

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	int m_iMyOfflineShopTime;
	int GetMyOfflineShopTime() const { return m_iMyOfflineShopTime; }
	void SetMyOfflineShopTime() { m_iMyOfflineShopTime = thecore_pulse(); }
#endif

//arat

private:
	void	__OpenPrivateShop();

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	void	__OpenOfflineShop();
#endif

//arat

};
ESex GET_SEX(LPCHARACTER ch);

//üstüne ekle

#if defined(__ENABLE_PREMIUM_MEMBERS__)
public:
	bool	ActivatePremium(int seconds);
	void	LoadOverfallPremium();
	void	CheckOverfallPremium();
	bool	IsOverfallPremium() const;
	int		GetOverfallPremiumTime() const { return iOverfallPremiumTime; }
	void	SetOverfallPremiumTime(int time) { iOverfallPremiumTime = time; }
private:
	int		iOverfallPremiumTime;
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
public:
	CEntity::ENTITY_MAP GetViewMap() const { return m_map_view; }
#endif
#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
public:
	bool			SwitchChannel(long newAddr, WORD newPort);
	bool			StartChannelSwitch(long newAddr, WORD newPort);
#endif