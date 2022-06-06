//arat

m_WarpPositionVector.clear();

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	m_OffShopPositionVector.clear();
#endif

//arat

else if (pkInstEach->IsWarp())

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
		else if (pkInstEach->IsShop())
		{
			aMarkPosition.m_fX = ( m_fWidth - (float)m_WhiteMark.GetWidth() ) / 2.0f + fDistanceFromCenterX + m_fScreenX;
			aMarkPosition.m_fY = ( m_fHeight - (float)m_WhiteMark.GetHeight() ) / 2.0f + fDistanceFromCenterY + m_fScreenY;

			m_OffShopPositionVector.push_back(aMarkPosition);
		}
#endif

//arat

	// NPC
	STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_NPC));
	aIterator = m_NPCPositionVector.begin();
	while (aIterator != m_NPCPositionVector.end())
	{
		TMarkPosition & rPosition = *aIterator;
		m_WhiteMark.SetPosition(rPosition.m_fX, rPosition.m_fY);
		m_WhiteMark.Render();
		++aIterator;
	}

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	// NPC - OfflineShop
	STATEMANAGER.SetRenderState(D3DRS_TEXTUREFACTOR, CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_OFFLINESHOP));
	aIterator = m_OffShopPositionVector.begin();
	while (aIterator != m_OffShopPositionVector.end())
	{
		TMarkPosition & rPosition = *aIterator;
		m_WhiteMark.SetPosition(rPosition.m_fX, rPosition.m_fY);
		m_WhiteMark.Render();
		++aIterator;
	}
#endif