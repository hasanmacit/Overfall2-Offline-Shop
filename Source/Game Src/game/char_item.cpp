//arat

void CHARACTER::__OpenPrivateShop()

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
void CHARACTER::__OpenOfflineShop()
{
	// if (g_bBlockGameMasterStuff) {
		// if ((IsGM() && !IsAllowedGameMaster()))
		// {
			// ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Game masters cant open shops."));
			// return;
		// }
	// }
	
	if (IsDead())
		return;

	if (GetExchange())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		return;
	}

	if (GetMyShop())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You already have an open shop."));
		return;
	}

	if (GetOfflineShop())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You already have an open shop."));
		return;
	}

	if (IsCubeOpen())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		return;
	}

	if (IsOpenSafebox())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		return;
	}

	if (GetShop())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		return;
	}

	ChatPacket(CHAT_TYPE_COMMAND, "OpenOfflineShop");
}
#endif

//arat

switch (item->GetVnum())
				{
				case 71049:

//içeriğini değiştir

				switch (item->GetVnum())
				{
				case 71049:
#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
					__OpenOfflineShop();
#else
					if (LC_IsYMIR() == true || LC_IsKorea() == true)
					{
						if (IS_BOTARYABLE_ZONE(GetMapIndex()) == true)
						{
							UseSilkBotary();
						}
						else
						{
							ChatPacket(CHAT_TYPE_INFO, LC_TEXT("개인 상점을 열 수 없는 지역입니다"));
						}
					}
					else
					{
						UseSilkBotary();
					}
#endif
					break;

//arat

if (iPulse - GetMyShopTime() < PASSES_PER_SEC(g_nPortalLimitTime))

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
			if (iPulse - GetMyOfflineShopTime() < PASSES_PER_SEC(g_nPortalLimitTime))
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("개인상점 사용후 %d초 이내에는 귀환부,귀환기억부를 사용할 수 없습니다."), g_nPortalLimitTime);
				return false;
			}
#endif

//arat

	if ((item->GetVnum() == 50200) || (item->GetVnum() == 71049))

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if ((item->GetVnum() == 71049 || item->GetVnum() == 50200) && HasOfflineShop())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You already have an open shop."));
		return false;
	}
#endif

//arat

	if (GetMyShop())	return false;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if (GetOfflineShop()) return false;
#endif

//arat

case 27996:

//altına ekle

#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
			case 60004:
				ChatPacket(CHAT_TYPE_COMMAND, "OpenShopSearch 0");
				break;

			case 60005:
				ChatPacket(CHAT_TYPE_COMMAND, "OpenShopSearch 1");
				break;
#endif