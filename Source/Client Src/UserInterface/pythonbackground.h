//arat

void DeleteSpecialEffect(DWORD dwID);

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	void CreateSpecialShopPosEffect(DWORD dwID, float fx, float fy, float fz, const char * c_szFileName);
	void DeleteSpecialShopPosEffect();
#endif