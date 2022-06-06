//arat

	private:
		typedef std::map<DWORD, int> TSpecialEffectMap;
		TSpecialEffectMap m_kMap_dwID_iEffectID;

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	private:
		int m_iLastShopPos;

	public:
		void SpecialShopPosEffect_Create(DWORD dwID, float x, float y, float z, const char* c_szEffName);
		void SpecialShopPosEffect_Delete();
#endif