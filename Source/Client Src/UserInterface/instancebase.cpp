//arat

BOOL CInstanceBase::IsGameMaster()

//altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
BOOL CInstanceBase::IsOverfallPremium()
{
	if (m_kAffectFlagContainer.IsSet(AFF_OVERFALL_PREMIUM))
		return 1;
	return 0;
}
#endif

//(DOSYALARINIZDA YOKSA ÜSTTEKİNİN HEMEN ALTINA EKLEYİN)

BOOL CInstanceBase::IsShop()
{
	if (GetRace() == 30000 || (GetRace() >= 30002 && GetRace() <= 30008))
		return true;
	return false;
}