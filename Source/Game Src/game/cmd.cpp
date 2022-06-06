//arat

ACMD(do_user_horse_feed);

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
ACMD(do_kick_offline_shop);
ACMD(do_open_offline_shop);
ACMD(do_offline_shop_sales);
ACMD(do_teleport_to_offshop);
#endif
#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
ACMD(do_change_channel);
#endif

//arat

	{ "\n",		NULL,			0,			POS_DEAD,	GM_IMPLEMENTOR	}

//üstüne ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	{ "kick_offlineshop", do_kick_offline_shop, 0, POS_DEAD, GM_IMPLEMENTOR },
	{ "open_offlineshop", do_open_offline_shop, 0, POS_DEAD, GM_PLAYER },
	{ "offlineshop_sales", do_offline_shop_sales, 0, POS_DEAD, GM_PLAYER },
	{ "teleport_to_offshop", do_teleport_to_offshop, 0, POS_DEAD, GM_PLAYER },
#endif
#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	{ "channel",			do_change_channel,			0,			POS_DEAD,	GM_PLAYER		},
#endif