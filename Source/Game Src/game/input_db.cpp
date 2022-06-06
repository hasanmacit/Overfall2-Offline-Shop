//definelere ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#include "offlineshop_manager.h"
#endif

//arat

	{
		db_clientdesc->DBPacket(HEADER_GD_BLOCK_COUNTRY_IP, 0, NULL, 0);
		dev_log(LOG_DEB0, "<sent HEADER_GD_BLOCK_COUNTRY_IP>");
	}

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	MYSQL_ROW row;
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT * FROM %soffline_shop_npc", get_table_postfix()));

	if (pMsg->Get()->uiNumRows != 0)
	{
		while (NULL != (row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
		{
			char szName[CHARACTER_NAME_MAX_LEN + 1];
			char szSign[SHOP_SIGN_MAX_LEN + 1];
			DWORD dwOwnerID = 0;
			long lMapIndex = 0, x = 0, y = 0, z = 0;
			int iTime = 0;
			BYTE bChannel = 0;
			int level = 0;
			int align = 0;
			char szGuild[CHARACTER_NAME_MAX_LEN + 1];
			int npc_vnum = 0;
			BYTE border_type = 0;

			str_to_number(dwOwnerID, row[0]);
			snprintf(szSign, sizeof(szSign), "%s", row[1]);
			snprintf(szName, sizeof(szName), "%s", row[2]);
			str_to_number(iTime, row[3]);
			str_to_number(x, row[4]);
			str_to_number(y, row[5]);
			str_to_number(z, row[6]);
			str_to_number(lMapIndex, row[7]);
			str_to_number(bChannel, row[8]);
			str_to_number(level, row[9]);
			str_to_number(align, row[10]);
			snprintf(szGuild, sizeof(szGuild), "%s", row[11]);
			str_to_number(npc_vnum, row[12]);
			str_to_number(border_type, row[13]);

			if (g_bChannel == bChannel)
			{
				LPCHARACTER npc;
#if defined(__WJ_SHOW_MOB_INFO__)
				npc = CHARACTER_MANAGER::instance().SpawnMob(npc_vnum, lMapIndex, x, y, z, false, -1, false, false, true, dwOwnerID);
#else
				npc = CHARACTER_MANAGER::instance().SpawnMob(npc_vnum, lMapIndex, x, y, z, false, -1, false, true, dwOwnerID);
#endif

				if (npc)
				{
					npc->SetName(szName);
					npc->SetOfflineShopSign(szSign);

					// npc->SetLevel(level);
					// npc->UpdateAlignment(align);
					// CGuild* pGuild = CGuildManager::instance().FindGuildByName(szGuild);
					// if (pGuild != NULL)
						// npc->SetGuild(pGuild);

					// bug fixed - 6.20.2015
					if (iTime != 0)
					{
						DBManager::Instance().DirectQuery("UPDATE %splayer SET offlineshop_time=%d WHERE id=%u", get_table_postfix(), (time(0) + iTime), dwOwnerID);
						npc->SetOfflineShopTimer(iTime);
						npc->StartOfflineShopUpdateEvent();
					}
					// end of bug fixed - 6.20.2015

					LPOFFLINESHOP pkOfflineShop = COfflineShopManager::instance().CreateOfflineShop(npc, dwOwnerID, NULL, 0, lMapIndex, iTime, szSign, border_type);
					npc->SetOfflineShop(pkOfflineShop);
					npc->SetOfflineShopChannel(bChannel);

					npc->Show(lMapIndex, x, y, z, true);
				}
			}
		}
	}
#endif

//arat

	case HEADER_DG_RESPOND_CHANNELSTATUS:
		RespondChannelStatus(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;

//altına ekle

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	case HEADER_DG_CHANNEL_RESULT:
		ChangeChannel(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
#endif

//arat

void CInputDB::ReloadAdmin(const char * c_pData )

//altına ekle

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
void CInputDB::ChangeChannel(LPDESC d, const char* pcData)
{
	if (!d || !d->GetCharacter())
	{
		sys_err("Change channel request with empty or invalid description handle!");
		return;
	}

	TPacketReturnChannel* p = (TPacketReturnChannel*)pcData;
	if (!p->lAddr || !p->wPort)
	{
		std::string pName = d->GetCharacter()->GetName();
		d->GetCharacter()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("CANNOT_CHANGE_CHANNEL"));
		sys_err("Can't switch channel for player %s!", pName.c_str());
		return;
	}

	// Execute
	d->GetCharacter()->StartChannelSwitch(p->lAddr, p->wPort);
}
#endif