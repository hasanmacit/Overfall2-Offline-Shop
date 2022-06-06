//arat

pTextTail->pTextInstance->GetTextSize(&iNameWidth, &iNameHeight);

//altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
		CGraphicImageInstance* pOverfallPremiumInstance = pTextTail->pOverfallPremiumInstance;
#endif

//arat

pLevel->Update();

//altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
				if (pOverfallPremiumInstance)
				{
					int iLevelWidth, iLevelHeight;
					pLevel->GetTextSize(&iLevelWidth, &iLevelHeight);
					pOverfallPremiumInstance->SetPosition(pTextTail->x - (iNameWidth / 2) - iTitleWidth - iLevelWidth - pOverfallPremiumInstance->GetWidth() - 4.0f, pTextTail->y - 11.0f);
				}
#endif

//arat

pLevel->Update();

//altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
				if (pOverfallPremiumInstance)
				{
					pOverfallPremiumInstance->SetPosition(pTextTail->x - (iNameWidth / 2) - iLevelWidth - pOverfallPremiumInstance->GetWidth() - 4.0f, pTextTail->y - 11.0f);
				}
#endif

//arat

		if (pTextTail->pTitleTextInstance)
		{
			pTextTail->pTitleTextInstance->Render();
		}

//altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
		CInstanceBase * pCharacterInstance = CPythonCharacterManager::Instance().GetInstancePtr(pTextTail->dwVirtualID);

		if (pCharacterInstance && pTextTail->bIsPC) {
			BOOL isPremium = pCharacterInstance->IsOverfallPremium();
			
			if (pTextTail->pOverfallPremiumInstance && isPremium)
				pTextTail->pOverfallPremiumInstance->Render();
		}
#endif

//arat

	m_CharacterTextTailMap.insert(TTextTailMap::value_type(dwVirtualID, pTextTail));

//üstüne ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
	CGraphicImageInstance *& prOverfallPremium = pTextTail->pOverfallPremiumInstance;
	if (!prOverfallPremium)
	{
		if(pCharacterInstance->IsPC())
		{
			if (CResourceManager::Instance().IsFileExist("d:/ymir work/overfall2_mini_logo.tga"))
			{
				CGraphicImage * pPremiumImage = (CGraphicImage *)CResourceManager::Instance().GetResourcePointer("d:/ymir work/overfall2_mini_logo.tga");
				if (pPremiumImage)
				{
					prOverfallPremium = CGraphicImageInstance::New();
					prOverfallPremium->SetImagePointer(pPremiumImage);
				}
			}
		}
	}
#endif

//arat

pTextTail->pLevelTextInstance = NULL;

//altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
	pTextTail->pOverfallPremiumInstance = NULL;
#endif