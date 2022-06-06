//arat

void CPythonPlayer::SetPlayTime(DWORD dwPlayTime)

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
void CPythonPlayer::SetCurrentOfflineShopMoney(long long llMoney)
{
	m_llCurrentOfflineShopMoney = llMoney;
}

long long CPythonPlayer::GetCurrentOfflineShopMoney()
{
	return m_llCurrentOfflineShopMoney;
}

#ifdef ENABLE_CHEQUE_SYSTEM
void CPythonPlayer::SetCurrentOfflineShopCheque(DWORD dwCheque)
{
	m_dwCurrentOfflineShopCheque = dwCheque;
}

DWORD CPythonPlayer::GetCurrentOfflineShopCheque()
{
	return m_dwCurrentOfflineShopCheque;
}
#endif
#endif