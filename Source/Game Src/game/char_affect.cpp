//arat

bool CHARACTER::UpdateAffect()
{

//altına ekle

#if defined(__ENABLE_PREMIUM_MEMBERS__)
	CheckOverfallPremium();
#endif