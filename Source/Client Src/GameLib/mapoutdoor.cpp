//arat

void CMapOutdoor::SpecialEffect_Destroy()

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
void CMapOutdoor::SpecialShopPosEffect_Create(DWORD dwID, float x, float y, float z, const char* c_szEffName)
{
	CEffectManager& rkEffMgr = CEffectManager::Instance();

	TSpecialEffectMap::iterator itor = m_kMap_dwID_iEffectID.find(dwID);
	if (m_kMap_dwID_iEffectID.end() != itor)
	{
		DWORD dwEffectID = itor->second;

		if (dwEffectID == m_iLastShopPos)
			return;

		if (rkEffMgr.SelectEffectInstance(dwEffectID))
		{
			D3DXMATRIX mat;
			D3DXMatrixIdentity(&mat);
			mat._41 = x;
			mat._42 = y;
			mat._43 = z;
			rkEffMgr.SetEffectInstanceGlobalMatrix(mat);
			return;
		}
	}

	rkEffMgr.RegisterEffect(c_szEffName);
	DWORD dwEffectID = rkEffMgr.CreateEffect(c_szEffName,
		D3DXVECTOR3(x, y, z),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_iLastShopPos = dwEffectID;
	m_kMap_dwID_iEffectID.insert(std::make_pair(dwID, dwEffectID));
}

void CMapOutdoor::SpecialShopPosEffect_Delete()
{
	if (m_iLastShopPos != 0)
	{
		CEffectManager& rkEffMgr = CEffectManager::Instance();
		rkEffMgr.DestroyEffectInstance(m_iLastShopPos);
		m_iLastShopPos = 0;
	}
}
#endif