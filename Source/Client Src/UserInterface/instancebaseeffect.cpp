//arat

	else if (IsPoly())
	{
		return NAMECOLOR_MOB;
	}

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	else if (IsShop())
	{
		return NAMECOLOR_OFFLINESHOP;
	}
#endif