//en alta ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
void CPythonBackground::CreateSpecialShopPosEffect(DWORD dwID, float fx, float fy, float fz, const char * c_szFileName)
{
	CMapOutdoor& rkMap = GetMapOutdoorRef();
	rkMap.SpecialShopPosEffect_Create(dwID, fx, fy, fz, c_szFileName);
}

void CPythonBackground::DeleteSpecialShopPosEffect()
{
	CMapOutdoor& rkMap = GetMapOutdoorRef();
	rkMap.SpecialShopPosEffect_Delete();
}
#endif