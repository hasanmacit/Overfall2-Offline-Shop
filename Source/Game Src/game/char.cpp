//definelere ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#include "offline_shop.h"
#include "offlineshop_manager.h"
#endif

//arat

	m_pkPartyRequestEvent = NULL;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	m_pkOfflineShop = NULL;
	m_pkChrOfflineShopOwner = NULL;
	m_pkOfflineShopUpdateEvent = NULL;
#endif

//arat

m_iSyncHackCount = 0;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	m_iMyOfflineShopTime = 0;
#endif

//arat

show_all_info:

//altına ekle

#if defined(__OFFLINE_PRIVATE_SHOP_SYSTEM__)
			addPacket.dwMyShopVID = (IsPC() ? COfflineShopManager::Instance().GetOfflineShopVID(GetPlayerID()) : 0);
#endif

//arat

	if (GetMyShop())
	{
		TPacketGCShopSign p;

		p.bHeader = HEADER_GC_SHOP_SIGN;
		p.dwVID = GetVID();
		strlcpy(p.szSign, m_stShopSign.c_str(), sizeof(p.szSign));

		d->Packet(&p, sizeof(TPacketGCShopSign));
	}

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if (IsOfflineShopNPC() && (GetRaceNum() == 30000 || (GetRaceNum() >= 30002 && GetRaceNum() <= 30008)))
	{
		if (entity->IsType(ENTITY_CHARACTER))
		{
			LPOFFLINESHOP shop = GetOfflineShop();

			if (shop)
			{
				TPacketGCShopSign p;
				p.bHeader = HEADER_GC_OFFLINE_SHOP_SIGN;
				p.dwVID = GetVID();
				p.bBorderStyle = shop->GetBorderStyle();
				strlcpy(p.szSign, shop->GetShopSign(), sizeof(p.szSign));
				d->Packet(&p, sizeof(TPacketGCShopSign));
			}
		}
	}
#endif

//arat

pack.dwMountVnum = GetMountVnum();

//altına ekle

#if defined(__OFFLINE_PRIVATE_SHOP_SYSTEM__)
	pack.dwMyShopVID = (IsPC() ? COfflineShopManager::Instance().GetOfflineShopVID(GetPlayerID()) : 0);
#endif

//arat

	if (GetShop())
	{
		GetShop()->RemoveGuest(this);
		SetShop(NULL);
	}

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if (GetOfflineShop())
	{
		GetOfflineShop()->RemoveGuest(this);
		SetOfflineShop(NULL);
	}
#endif

//arat

#ifdef __PET_SYSTEM__
	if (m_petSystem)
	{
		m_petSystem->Destroy();
		delete m_petSystem;
	}

	m_petSystem = M2_NEW CPetSystem(this);
#endif

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	SetOfflineShopVID(COfflineShopManager::instance().FindMyOfflineShop(GetPlayerID()));
#endif
#if defined(__ENABLE_PREMIUM_MEMBERS__)
	LoadOverfallPremium();
#endif

//arat

if ((GetExchange() || IsOpenSafebox() || GetShopOwner()) || IsCubeOpen()

//altına ya da yanına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
						|| GetOfflineShopOwner()
#endif

//arat

if ((GetExchange() || IsOpenSafebox() || GetShopOwner()) || IsCubeOpen()

//altına ya da yanına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
						|| GetOfflineShopOwner()
#endif

//arat

if ((GetExchange() || IsOpenSafebox() || IsCubeOpen()

//altına ya da yanına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
						|| GetOfflineShopOwner()
#endif

//arat

if (g_bChinaIntoxicationCheck)

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if (IsOfflineShopNPC())
	{
		if (pkChrCauser->GetOfflineShopVID() == this->GetVID())
		{
			::interpret_command(pkChrCauser, "open_offlineshop", strlen("open_offlineshop"));
			return;
		}
		else
		{
			pkChrCauser->SetOfflineShopOwner(this);
			if (GetOfflineShop()) { GetOfflineShop()->AddGuest(pkChrCauser, this); }
			return;
		}
	}
#endif

//arat

if (iPulse - GetMyShopTime() < PASSES_PER_SEC(limittime))

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if (iPulse - GetMyOfflineShopTime() < PASSES_PER_SEC(limittime))
	{
		if (bSendMsg)
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("거래 후 %d초 이내에는 다른지역으로 이동 할 수 없습니다."), limittime);
		return true;
	}
#endif

//arat

	if ((iPulse - GetMyShopTime()) < limit_time)
		return false;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if ((iPulse - GetMyOfflineShopTime()) < limit_time)
		return false;
#endif

//en alta ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
void CHARACTER::SetOfflineShop(LPOFFLINESHOP pkOfflineShop)
{
	m_pkOfflineShop = pkOfflineShop;
	if (m_pkOfflineShop)
		SET_BIT(m_pointsInstant.instant_flag, INSTANT_FLAG_OFFLINE_SHOP);
	else
	{
		REMOVE_BIT(m_pointsInstant.instant_flag, INSTANT_FLAG_OFFLINE_SHOP);
		SetOfflineShopOwner(NULL);
	}
}

#ifdef __EXTENDED_ITEM_COUNT__
void CHARACTER::OpenMyOfflineShop(const char* c_pszSign, TOfflineShopItemTable * pTable, short bItemCount, BYTE bNpcType, BYTE bBoardStyle)
#else
void CHARACTER::OpenMyOfflineShop(const char* c_pszSign, TOfflineShopItemTable * pTable, BYTE bItemCount, BYTE bNpcType, BYTE bBoardStyle)
#endif
{
	if (thecore_pulse() - GetMyOfflineShopTime() < PASSES_PER_SEC(10))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Please wait."));
		return;
	}

	SetMyOfflineShopTime();

	quest::PC* pPC = quest::CQuestManager::instance().GetPC(GetPlayerID());

	if (pPC && pPC->IsRunning())
		return;

	if (bItemCount == 0)
		return;

	if (GetShop() || GetOfflineShop())
		return;

	{
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT COUNT(*) FROM offline_shop_item%s WHERE owner_id = %u and status = 1", get_table_postfix(), GetPlayerID()));
		MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);

		BYTE bResult = 0;
		str_to_number(bResult, row[0]);

		if (bResult)
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Remove your unsold items first before opening a new shop."));
			return;
		}
	}

	if (g_bChannel != 1)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You can only open shops in channel 1."));
		return;
	}
	
	if (HasOfflineShop() == true)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You already have an open shop."));
		return;
	}

	if (COfflineShopManager::instance().GetShopCountChannel() >= OFFLINE_SHOP_MAX_COUNT)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> The server can not handle more open shops."));
		return;
	}

	if (GetMapIndex() != 1 && GetMapIndex() != 21 && GetMapIndex() != 41)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You can only open shops in your village."));
		return;
	}

	#if defined(__ENABLE_PREMIUM_MEMBERS__)
	if (!IsOverfallPremium()) {
		if (GetEmpire() == 1)
		{
			if (GetMapIndex() == 21 || GetMapIndex() == 41)
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You can only open shops in your kingdom."));
				return;
			}
		}
		else if (GetEmpire() == 2)
		{
			if (GetMapIndex() == 1 || GetMapIndex() == 41)
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You can only open shops in your kingdom."));
				return;
			}
		}
		else if (GetEmpire() == 3)
		{
			if (GetMapIndex() == 1 || GetMapIndex() == 21)
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You can only open shops in your kingdom."));
				return;
			}
		}
	}
	#endif

	if (GetLevel() < OFFLINE_SHOP_NEED_LEVEL)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cannot open shop below level %d."), OFFLINE_SHOP_NEED_LEVEL);
		return;
	}

	char szSign[SHOP_SIGN_MAX_LEN + 1];
	strlcpy(szSign, c_pszSign, sizeof(szSign));

	if (strlen(c_pszSign) == 0)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Your shop needs a title."));
		return;
	}

	if (strstr(szSign, "%") || strstr(szSign, "'"))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Invalid shop title name."));
		return;
	}

	m_stOfflineShopSign = szSign;

	if (CBanwordManager::instance().CheckString(m_stOfflineShopSign.c_str(), m_stOfflineShopSign.length()))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Invalid shop title name."));
		return;
	}

	if (IsCubeOpen())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		return;
	}

	// if (g_bBlockGameMasterStuff) {
		// if ((IsGM() && !IsAllowedGameMaster()))
		// {
			// ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Game masters cant open shops."));
			// return;
		// }
	// }

	std::map<DWORD, DWORD> itemkind;
	std::set<TItemPos> cont;

#ifdef __EXTENDED_ITEM_COUNT__
	for (short i = 0; i < bItemCount; ++i)
#else
	for (BYTE i = 0; i < bItemCount; ++i)
#endif
	{
		if (cont.find((pTable + i)->pos) != cont.end())
		{
			sys_err("MY_OFFLINE_SHOP: duplicate shop item detected! (name: %s)", GetName());
			return;
		}

		// ANTI_GIVE, ANTI_MYSHOP check
		LPITEM pkItem = GetItem((pTable + i)->pos);

		if (pkItem)
		{
			const TItemTable* item_table = pkItem->GetProto();
			if (item_table && (IS_SET(item_table->dwAntiFlags, ITEM_ANTIFLAG_GIVE | ITEM_ANTIFLAG_MYSHOP)))
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Cannot sell anti give and anti shop items."));
				return;
			}

			if (pkItem->IsEquipped() == true)
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cannot sell equipped items."));
				return;
			}

			if (true == pkItem->isLocked())
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cannot sell locked items."));
				return;
			}

#ifdef __SOUL_BIND_SYSTEM__
			if (pkItem->IsSealed())
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cannot sell soulbound items."));
				return;
			}
#endif
		}
	}
	
	int open_cost = 5000000;
	int open_time = 0;
	#if defined(__ENABLE_PREMIUM_MEMBERS__)
	if (IsOverfallPremium())
		open_time = (7 * 60 * 60 * 24);
	else
		open_time = (3 * 60 * 60 * 24);
	#else
	open_time = (7 * 60 * 60 * 24);
	#endif

	int npc_vnum = 0;
	switch (bNpcType)
	{
	case 0:
		npc_vnum = 30000;
		break;
	case 1:
		npc_vnum = 30002;
		break;
	case 2:
		npc_vnum = 30003;
		break;
	case 3:
		npc_vnum = 30004;
		break;
	case 4:
		npc_vnum = 30005;
		break;
	case 5:
		npc_vnum = 30006;
		break;
	case 6:
		npc_vnum = 30007;
		break;
	case 7:
		npc_vnum = 30008;
		break;
	default:
		npc_vnum = 30000;
		break;
	}
	
	if (bBoardStyle < 0 || bBoardStyle > 5)
		bBoardStyle = 0;
	
	#if defined(__ENABLE_PREMIUM_MEMBERS__)
	if (!IsOverfallPremium() && npc_vnum != 30000)
		npc_vnum = 30000;
	#endif

	if (GetGold() < open_cost)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You do not have enought gold to open a shop."));
		return;
	}

#if defined(__WJ_SHOW_MOB_INFO__)
	LPCHARACTER npc = CHARACTER_MANAGER::instance().SpawnMob(npc_vnum, GetMapIndex(), GetX(), GetY(), GetZ(), false, -1, false, false, true, GetPlayerID());
#else
	LPCHARACTER npc = CHARACTER_MANAGER::instance().SpawnMob(npc_vnum, GetMapIndex(), GetX(), GetY(), GetZ(), false, -1, false, true, GetPlayerID());
#endif

	if (!npc)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Cannot open shop."));
		sys_err("SpawnMob: Unkown NPC! (name: %s)", GetName());
		return;
	}

	DBManager::Instance().DirectQuery("UPDATE player%s SET offlineshop_time=%d WHERE id=%u", get_table_postfix(), (time(0) + (open_time)), GetPlayerID());
	npc->SetOfflineShopTimer(open_time);
	npc->StartOfflineShopUpdateEvent();

	char szInsertQuery[512];
	snprintf(szInsertQuery, sizeof(szInsertQuery), "INSERT INTO offline_shop_npc%s (owner_id, sign, name, time, x, y, z, mapIndex, channel, level, align, guild, npc_vnum, border_style) VALUES(%u, '%s', '%s', %d, %ld, %ld, %ld, %ld, %d, %d, %d, '%s', %d, %d)", get_table_postfix(), GetPlayerID(), szSign, GetName(), open_time, GetX(), GetY(), GetZ(), GetMapIndex(), g_bChannel, GetLevel(), GetAlignment(), GetGuild() ? GetGuild()->GetName() : "NONAME", npc_vnum, bBoardStyle);
	DBManager::Instance().DirectQuery(szInsertQuery);

	LPOFFLINESHOP pkOfflineShop = COfflineShopManager::instance().CreateOfflineShop(npc, GetPlayerID(), pTable, bItemCount, GetMapIndex(), open_time, szSign, bBoardStyle);
	if (!pkOfflineShop)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Cannot open shop."));
		sys_err("CreateOfflineShop: Unable to create offline shop! (name: %s)", GetName());
		return;
	}

	npc->SetOfflineShop(pkOfflineShop);
	npc->SetOfflineShopChannel(g_bChannel);

	char szName[CHARACTER_NAME_MAX_LEN + 1];
	snprintf(szName, sizeof(szName), "%s", GetName());
	npc->SetName(szName);

	pkOfflineShop->SetShopSign(szSign);

	SetOfflineShopVID(npc->GetVID());
	npc->Show(GetMapIndex(), GetX(), GetY(), GetZ(), true);

	if (m_pkExchange)
		m_pkExchange->Cancel();

	CloseSafebox();

	TPacketGCShopSign p;
	p.bHeader = HEADER_GC_OFFLINE_SHOP_SIGN;
	p.dwVID = npc->GetVID();
	p.bBorderStyle = bBoardStyle;
	strlcpy(p.szSign, c_pszSign, sizeof(p.szSign));

	PacketAround(&p, sizeof(TPacketGCShopSign));

	ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You have opened a private offline shop for %d hours."), (open_time / 60 / 60 / 24));

	PointChange(POINT_GOLD, -open_cost);

	npc->ViewReencode();
	
	UpdatePacket();
}

EVENTFUNC(offline_shop_update_event)
{
	char_event_info* pInfo = dynamic_cast<char_event_info*>(event->info);

	if (pInfo == NULL)
	{
		sys_err("offline_shop_update_event> <Factor> Null pointer");
		return 0;
	}

	LPCHARACTER npc = pInfo->ch;

	if (npc == NULL)
		return 0;

	int remain_time = npc->GetOfflineShopTimer() - processing_time / passes_per_sec;
	if (remain_time <= 0)
	{
		sys_log(0, "OFFLINE SHOP EXPIRED : expired %s", npc->GetName());
		LPCHARACTER pChar = CHARACTER_MANAGER::instance().Find(npc->GetOfflineShopRealOwner());

		DBManager::instance().DirectQuery("DELETE FROM offline_shop_npc%s WHERE owner_id = %u", get_table_postfix(), npc->GetOfflineShopRealOwner());
		DBManager::instance().DirectQuery("UPDATE offline_shop_item%s SET status = 1 WHERE owner_id = %u and status = 0", get_table_postfix(), npc->GetOfflineShopRealOwner());
		DBManager::instance().DirectQuery("DELETE FROM offline_shop_item%s WHERE owner_id = %u and status = 2", get_table_postfix(), npc->GetOfflineShopRealOwner());

		if (pChar)
		{
			pChar->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Your shop time is over."));
			COfflineShopManager::Instance().DestroyOfflineShop(pChar, npc->GetVID());
		}
		else
			COfflineShopManager::Instance().DestroyOfflineShop(NULL, npc->GetVID());

		if (pChar)
		{
			pChar->SetOfflineShop(NULL);
			pChar->SetOfflineShopOwner(NULL);
		}

		M2_DESTROY_CHARACTER(npc);
		return 0;
	}

	if (npc->GetOfflineShopSaveTime() >= OFFLINE_SHOP_SAVE_TIME)
	{
		DBManager::instance().DirectQuery("UPDATE offline_shop_npc%s SET time = %d WHERE owner_id = %u", get_table_postfix(), npc->GetOfflineShopTimer(), npc->GetOfflineShopRealOwner());
		npc->SetOfflineShopTimer(1);
	}

	npc->SetOfflineShopTimer(remain_time);
	npc->SetOfflineShopSaveTime(npc->GetOfflineShopSaveTime() + 1);

	LPOFFLINESHOP pkOfflineShop = npc->GetOfflineShop();
	if (pkOfflineShop)
		pkOfflineShop->SetOfflineShopTime(remain_time);

	return PASSES_PER_SEC(MIN(60, remain_time));
}

void CHARACTER::StartOfflineShopUpdateEvent()
{
	if (m_pkOfflineShopUpdateEvent)
		return;

	if (IsPC() || IsMonster())
		return;

	char_event_info* pInfo = AllocEventInfo<char_event_info>();
	pInfo->ch = this;
	m_pkOfflineShopUpdateEvent = event_create(offline_shop_update_event, pInfo, PASSES_PER_SEC(60));
}

void CHARACTER::StopOfflineShopUpdateEvent()
{
	m_pointsInstant.bSaveTime = 0;
	m_pointsInstant.leftTime = 0;
	event_cancel(&m_pkOfflineShopUpdateEvent);
}

void CHARACTER::SetOfflineShopSign(const char* c_szSign)
{
	char szSign[SHOP_SIGN_MAX_LEN + 1];
	strlcpy(szSign, c_szSign, sizeof(szSign));
	m_stOfflineShopSign = szSign;
}

void CHARACTER::DestroyOfflineShop()
{
	COfflineShopManager::instance().DestroyOfflineShop(NULL, GetVID(), false);
}

bool CHARACTER::HasOfflineShop()
{
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT owner_id FROM offline_shop_npc%s WHERE owner_id = %u", get_table_postfix(), GetPlayerID()));
	if (pMsg->Get()->uiNumRows == 0)
		return false;

	return true;
}

BYTE CHARACTER::GetOfflineShopChannel()
{
	if (!HasOfflineShop())
		return 0;
	
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT channel FROM offline_shop_npc%s WHERE owner_id = %u", get_table_postfix(), GetPlayerID()));
	if (!pMsg || (pMsg && pMsg->Get()->uiNumRows == 0))
		return 0;

	BYTE channel = 0;
	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	str_to_number(channel, row[0]);

	return channel;
}

void CHARACTER::OfflineShopPanelPacket(BYTE hasOfflineShop, const char * shopName, long lMapIndex, BYTE shopChannel, int iTime, DWORD displayedCount)
{
	if (!GetDesc())
		return;
	
	TPacketGCOpenOffShopPanel packet;
	packet.bHeader = HEADER_GC_OFFLINE_SHOP_OPEN_PANEL;
	packet.hasOfflineShop = hasOfflineShop;
	packet.lMapIndex = (lMapIndex == -1 ? 0 : lMapIndex);
	packet.shopChannel = shopChannel;
	packet.iTime = (iTime == -1 ? 0 : iTime);
	packet.isPremium = static_cast<BYTE>(IsOverfallPremium());
	packet.displayedCount = displayedCount;
	strlcpy(packet.shopName, shopName, sizeof(packet.shopName));

	GetDesc()->Packet(&packet, sizeof(packet));
}

void CHARACTER::OpenOfflineShopPanel()
{
	quest::PC * pPC = quest::CQuestManager::Instance().GetPC(GetPlayerID());

	if (pPC->IsRunning())
		return;

	if (IsOpenSafebox() || GetShop() || IsCubeOpen() || IsDead() || GetExchange() || GetOfflineShop() || GetMyShop())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		return;
	}
	
	if (GetMapIndex() >= 10000 || g_bChannel == 99)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant open your shop in this map."));
		return;
	}
	
	BYTE shopChannel = GetOfflineShopChannel();
	
	if (shopChannel == 0) {
		COfflineShopManager::instance().RefreshUnsoldItems(this);
		OfflineShopPanelPacket(0);
		return;
	}
	
	DWORD dwOwnerPID = GetPlayerID();
	bool canGetOfflineShop = COfflineShopManager::instance().CanGetOfflineShop(dwOwnerPID);
	
	if (g_bChannel != shopChannel || !canGetOfflineShop)
	{
		TPacketGGOpenOffShopPanel searchShopData;
		searchShopData.bHeader = HEADER_GG_OFFLINE_SHOP_OPEN_PANEL;
		searchShopData.bSubHeader = OFFLINE_SHOP_PANEL_SEARCH_SHOP;
		searchShopData.shopChannel = shopChannel;
		searchShopData.dwOwnerPID = dwOwnerPID;
		P2P_MANAGER::instance().Send(&searchShopData, sizeof(TPacketGGOpenOffShopPanel));
	}
	else
	{
		COfflineShopManager::instance().Refresh(this);
		
		long shop_map_index = COfflineShopManager::instance().GetMapIndex(dwOwnerPID);
		int shop_left_time = COfflineShopManager::instance().GetLeftTime(dwOwnerPID);
		const char* shopName = COfflineShopManager::instance().GetOfflineShopSign(dwOwnerPID);
		DWORD displayedCount = COfflineShopManager::instance().GetDisplayedCount(dwOwnerPID);
		OfflineShopPanelPacket(static_cast<BYTE>((bool)shopChannel), shopName, shop_map_index, shopChannel, shop_left_time, displayedCount);
	}
}
/////

void CHARACTER::TeleportToMyOfflineShop()
{
	quest::PC * pPC = quest::CQuestManager::Instance().GetPC(GetPlayerID());

	if (pPC->IsRunning())
		return;

	if (IsOpenSafebox() || GetShop() || IsCubeOpen() || IsDead() || GetExchange() || GetOfflineShop() || GetMyShop())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Close other windows before opening a shop."));
		return;
	}
	
	if (GetMapIndex() >= 10000 || g_bChannel == 99)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You cant open your shop in this map."));
		return;
	}
	
	BYTE shopChannel = GetOfflineShopChannel();
	
	if (shopChannel == 0)
		return;
	
	bool canGetOfflineShop = COfflineShopManager::instance().CanGetOfflineShop(GetPlayerID());
	if (g_bChannel != shopChannel || !canGetOfflineShop)
	{
		if (!CanWarp()) {
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Wait a second before warp to your offline shop."));
			return;
		}
		
		long mapIdx, x, y;
		if (!COfflineShopManager::Instance().GetOfflineShopCoordsP2P(this, &mapIdx, &x, &y))
			return;
		
		if (!GetDesc())
			return;
		
		TPacketChangeChannel p;
		p.iChannel = shopChannel;
		p.lMapIndex = mapIdx;
		p.x = x;
		p.y = y;

		db_clientdesc->DBPacket(HEADER_GD_FIND_CHANNEL, GetDesc()->GetHandle(), &p, sizeof(p));
	}
	else
	{
		if (!CanWarp()) {
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> Wait a second before warp to your offline shop."));
			return;
		}
		
		long mapIdx, x, y;
		if (!COfflineShopManager::Instance().GetOfflineShopCoords(GetPlayerID(), &mapIdx, &x, &y))
			return;
		
		WarpSet(x, y, mapIdx);
	}
}

void CHARACTER::ChangeShopSign(DWORD shopVid, const char * newShopName)
{
	TPacketGCShopSign p;
	p.bHeader = HEADER_GC_OFFLINE_CHANGE_SHOP_SIGN;
	p.dwVID = shopVid;
	strlcpy(p.szSign, newShopName, sizeof(p.szSign));
	PacketAround(&p, sizeof(TPacketGCShopSign));
}
#endif
#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
bool CHARACTER::SwitchChannel(long newAddr, WORD newPort)
{
	if (!IsPC() || !GetDesc() || !CanWarp())
		return false;

	long x = GetX();
	long y = GetY();

	long lAddr = newAddr;
	long lMapIndex = GetMapIndex();
	WORD wPort = newPort;

	// If we currently are in a dungeon.
	if (lMapIndex >= 10000)
	{
		sys_err("Invalid change channel request from dungeon %d!", lMapIndex);
		return false;
	}

	// If we are on CH99.
	if (g_bChannel == 99)
	{
		sys_err("%s attempted to change channel from CH99, ignoring req.", GetName());
		return false;
	}

	Stop();
	Save();

	if (GetSectree())
	{
		GetSectree()->RemoveEntity(this);
		ViewCleanup();
		EncodeRemovePacket(this);
	}

	m_lWarpMapIndex = lMapIndex;
	m_posWarp.x = x;
	m_posWarp.y = y;

	// TODO: This log message should mention channel we are changing to instead of port.
	sys_log(0, "ChangeChannel %s, %ld %ld map %ld to port %d", GetName(), x, y, GetMapIndex(), wPort);

	TPacketGCWarp p;

	p.bHeader = HEADER_GC_WARP;
	p.lX = x;
	p.lY = y;
	p.lAddr = lAddr;
	p.wPort = wPort;

	GetDesc()->Packet(&p, sizeof(p));

	char buf[256];
	// TODO: This log message should mention channel we are changing to instead of port
	snprintf(buf, sizeof(buf), "%s Port%d Map%ld x%ld y%ld", GetName(), wPort, GetMapIndex(), x, y);
	LogManager::instance().CharLog(this, 0, "CHANGE_CH", buf);

	return true;
}

EVENTINFO(switch_channel_info)
{
	DynamicCharacterPtr ch;
	int secs;
	long newAddr;
	WORD newPort;
	switch_channel_info()
		: ch(),
		secs(0),
		newAddr(0),
		newPort(0)
	{
	}
};

EVENTFUNC(switch_channel)
{
	switch_channel_info* info = dynamic_cast<switch_channel_info*>(event->info);
	if (!info)
	{
		sys_err("No switch channel event info!");
		return 0;
	}

	LPCHARACTER	ch = info->ch;
	if (!ch)
	{
		sys_err("No char to work on for the switch.");
		return 0;
	}

	if (!ch->GetDesc())
		return 0;

	if (info->secs > 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Channel switch in %d seconds."), info->secs);
		--info->secs;
		return PASSES_PER_SEC(1);
	}

	ch->SwitchChannel(info->newAddr, info->newPort);
	ch->m_pkTimedEvent = nullptr;
	return 0;
}

bool CHARACTER::StartChannelSwitch(long newAddr, WORD newPort)
{
	if (IsHack(false, true, 10))
		return false;

	switch_channel_info* info = AllocEventInfo<switch_channel_info>();
	info->ch = this;
	info->secs = CanWarp() && !IsPosition(POS_FIGHTING) ? 3 : 10;
	info->newAddr = newAddr;
	info->newPort = newPort;

	m_pkTimedEvent = event_create(switch_channel, info, 1);
	ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Channel switch starting."));
	return true;
}
#endif