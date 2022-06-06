//arat

LPCHARACTER		SpawnMob

//değiştir

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
		LPCHARACTER		SpawnMob(DWORD dwVnum, long lMapIndex, long x, long y, long z, bool bSpawnMotion = false, int iRot = -1, bool bShow = true, bool isOfflineShopNPC = false, DWORD real_owner = 0);
#else
		LPCHARACTER		SpawnMob(DWORD dwVnum, long lMapIndex, long x, long y, long z, bool bSpawnMotion = false, int iRot = -1, bool bShow = true);
#endif