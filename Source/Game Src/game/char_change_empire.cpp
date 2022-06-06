//arat

	if (GetEmpire() == empire)
		return 1;

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	if (!CanChangeEmpireOfflineShopCheck())
		return 4;
#endif

//arat

int CHARACTER::GetChangeEmpireCount() const

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
bool CHARACTER::CanChangeEmpireOfflineShopCheck()
{
	DWORD dwPID = GetPlayerID();

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery),
		"SELECT "
		"a.pid1, "
		"a.pid2, "
		"a.pid3, "
		"a.pid4, "
#ifdef __PLAYER_PER_ACCOUNT5__
		"a.pid5, "
#endif
		"b.owner_id "
		"FROM player_index%s a "
		"INNER JOIN offline_shop_npc%s b "
		"ON "
		"a.pid1 = b.owner_id OR "
		"a.pid2 = b.owner_id OR "
		"a.pid3 = b.owner_id OR "
#ifdef __PLAYER_PER_ACCOUNT5__
		"a.pid4 = b.owner_id OR "
		"a.pid5 = b.owner_id "
#else
		"a.pid4 = b.owner_id "
#endif
		"WHERE "
		"a.pid1 = %u OR "
		"a.pid2 = %u OR "
		"a.pid3 = %u OR "
#ifdef __PLAYER_PER_ACCOUNT5__
		"a.pid4 = %u OR "
		"a.pid5 = %u",
#else
		"a.pid4 = %u",
#endif
		get_table_postfix(),	// a
		get_table_postfix(),	// b
		dwPID,	// 1
		dwPID,	// 2
		dwPID,	// 3
		dwPID	// 4
#ifdef __PLAYER_PER_ACCOUNT5__
		, dwPID	// 5
#endif
	);

	SQLMsg* pMsg = DBManager::instance().DirectQuery(szQuery);
	if (pMsg != NULL)
	{
		if (pMsg->Get()->uiNumRows == 0)
		{
			M2_DELETE(pMsg);
			return true;
		}

		M2_DELETE(pMsg);
		return false;
	}

	return false;
}
#endif