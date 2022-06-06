//definelere ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#include "offlineshop_manager.h"
#endif

//arat

	if (ch->GetShop())
		strlcat(buf, ", Shop", sizeof(buf));

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if (ch->GetOfflineShop())
		strlcat(buf, ", Offline Shop", sizeof(buf));
#endif

//arat

ACMD(do_user)

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
struct FFindOfflineShop
{
	const char* szName;
	bool bResult;

	FFindOfflineShop(const char* c_szName) : szName(c_szName), bResult(false) {};

	void operator()(LPENTITY ent)
	{
		if (!ent)
			return;

		if (ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER ch = (LPCHARACTER)ent;
			if (ch->IsOfflineShopNPC() && !strcmp(szName, ch->GetName()))
			{
				bResult = true;
				ch->DestroyOfflineShop();
			}
		}
	}
};
#endif

//en alta ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
struct FFindOfflineShop2
{
	const char* szName;

	DWORD dwVID, dwRealOwner;
	bool bIsDestroyed;
	FFindOfflineShop2(const char* c_szName) : szName(c_szName), dwVID(0), dwRealOwner(0), bIsDestroyed(false) {};

	void operator()(LPENTITY ent)
	{
		if (!ent)
			return;

		if (ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER ch = (LPCHARACTER)ent;
			if (ch->IsOfflineShopNPC() && !strcmp(szName, ch->GetName()))
			{
				dwVID = ch->GetVID();
				dwRealOwner = ch->GetOfflineShopRealOwner();
				bIsDestroyed = true;
				M2_DESTROY_CHARACTER(ch);
			}
		}
	}
};

ACMD(do_kick_offline_shop)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "kick_offline_shop <owner of offline shop>");
		return;
	}

	LPSECTREE_MAP pMap = SECTREE_MANAGER::Instance().GetMap(ch->GetMapIndex());
	if (pMap)
	{
		char szName[CHARACTER_NAME_MAX_LEN + 1];
		snprintf(szName, sizeof(szName), "%s", arg1);
		FFindOfflineShop2 offlineShop(szName);
		pMap->for_each(offlineShop);

		if (offlineShop.bIsDestroyed)
		{
			DBManager::instance().Query("UPDATE %soffline_shop_item SET status = 1 WHERE owner_id = %u and status = 0", get_table_postfix(), offlineShop.dwRealOwner);
			DBManager::instance().Query("DELETE FROM %soffline_shop_npc WHERE owner_id = %u", get_table_postfix(), offlineShop.dwRealOwner);
			DBManager::instance().Query("DELETE FROM %soffline_shop_item WHERE owner_id = %u and status = 2", get_table_postfix(), offlineShop.dwRealOwner);

			ch->ChatPacket(CHAT_TYPE_INFO, "<Offline Shop> %s shop was deleted.", szName);
		}
		else
			ch->ChatPacket(CHAT_TYPE_INFO, "<Offline Shop> Cannot destroy %s shop.", szName);
	}
}

ACMD(do_open_offline_shop)
{
	if (!ch)
		return;
	
	ch->OpenOfflineShopPanel();
}

ACMD(do_offline_shop_sales)
{
	char szQuery[1024];

	snprintf(szQuery, sizeof(szQuery), "SELECT buyer_name, item_vnum, item_count, item_price, item_cheque, datetime "
		"FROM %soffline_shop_sales WHERE item_owner = %u ORDER BY datetime DESC LIMIT 100;", get_table_postfix(), ch->GetPlayerID());
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));

	ch->ChatPacket(CHAT_TYPE_COMMAND, "ClearOfflineShopSales");
	if (pMsg->Get()->uiNumRows > 0)
	{
		for (int i = 0; i < pMsg->Get()->uiNumRows; ++i)
		{
			MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);

			const char* szBuyerName = row[0]; // buyer name

			DWORD dwItemVnum = 0;
			str_to_number(dwItemVnum, row[1]); // item vnum

			BYTE bItemCount = 0;
			str_to_number(bItemCount, row[2]); // item count

			long long llItemPrice = 0;
			str_to_number(llItemPrice, row[3]); // item price

			int iItemCheque = 0;
			str_to_number(iItemCheque, row[4]); // item cheque

			DWORD dwItemDate = 0;
			str_to_number(dwItemDate, row[5]); // item date

			ch->ChatPacket(CHAT_TYPE_COMMAND, "OfflineShopSales %s %u %d %lld %d %u", szBuyerName, dwItemVnum, bItemCount, llItemPrice, iItemCheque, dwItemDate);
		}
	}
	ch->ChatPacket(CHAT_TYPE_COMMAND, "OpenOfflineShopSalesWindow");
}
#endif