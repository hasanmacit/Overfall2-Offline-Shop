//arat

LPCHARACTER CHARACTER_MANAGER::SpawnMob

//değiştir

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
LPCHARACTER CHARACTER_MANAGER::SpawnMob(DWORD dwVnum, long lMapIndex, long x, long y, long z, bool bSpawnMotion, int iRot, bool bShow, bool isOfflineShopNPC, DWORD real_owner)
#else
LPCHARACTER CHARACTER_MANAGER::SpawnMob(DWORD dwVnum, long lMapIndex, long x, long y, long z, bool bSpawnMotion, int iRot, bool bShow)
#endif

//arat

ch->SetRotation(iRot);

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if (isOfflineShopNPC)
	{
		ch->SetOfflineShopNPC(isOfflineShopNPC);
		ch->SetOfflineShopRealOwner(real_owner);
	}
#endif