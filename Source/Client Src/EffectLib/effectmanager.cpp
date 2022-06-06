//arat

BOOL CEffectManager::RegisterEffect(const char * c_szFileName,bool isExistDelete,bool isNeedCache)

//üstüne ekle

void CEffectManager::RenderOne(DWORD id)
{
	STATEMANAGER.SetTexture(0, NULL);
	STATEMANAGER.SetTexture(1, NULL);

	
	const auto& pEffectInstance = m_kEftInstMap.find(id);

	if (pEffectInstance != m_kEftInstMap.end())
	{
		pEffectInstance->second->SetIgnoreFrustum(true);
		pEffectInstance->second->Show();
		pEffectInstance->second->Render();
	}
	else
		TraceError("!RenderOne, not found");
}