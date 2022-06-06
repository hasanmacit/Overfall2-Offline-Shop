//definelere ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#include "offlineshop_manager.h"
#endif

//en alta ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
ACMD(do_teleport_to_offshop)
{
	if (!ch)
		return;

	#if defined(__ENABLE_PREMIUM_MEMBERS__)
	if (!ch->IsOverfallPremium()) {
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant do this because you arent a premium member."));
		return;
	}
	#endif
	
	ch->TeleportToMyOfflineShop();
}
#endif

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
ACMD(do_change_channel)
{
	if (!ch)
		return;

	if (ch->m_pkTimedEvent)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("취소 되었습니다."));
		event_cancel(&ch->m_pkTimedEvent);
		return;
	}

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Usage: channel <new channel>"));
		return;
	}

	short channel;
	str_to_number(channel, arg1);

	if (channel < 0 || channel > 4)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Please enter a valid channel."));
		return;
	}

	if (channel == g_bChannel)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You are already on channel %d."), g_bChannel);
		return;
	}

	if (g_bChannel == 99)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("The map you are at is cross-channel, changing won't have any effect."));
		return;
	}

	if (ch->GetDungeon())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You cannot change channel while in a dungeon."));
		return;
	}

	if (CWarMapManager::instance().IsWarMap(ch->GetMapIndex()))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You cannot change channel in war map."));
		return;
	}

	if (ch->IsHack())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You cannot change channel this state."));
		return;
	}

	TPacketChangeChannel p;
	p.iChannel = channel;
	p.lMapIndex = ch->GetMapIndex();

	db_clientdesc->DBPacket(HEADER_GD_FIND_CHANNEL, ch->GetDesc()->GetHandle(), &p, sizeof(p));
}
#endif