#include "stdafx.h"
#include "constants.h"
#include "utils.h"
#include "config.h"
#include "char.h"
#include "char_manager.h"
#include "db.h"
#include "packet.h"
#include "desc_client.h"
#include "item.h"
#include "item_manager.h"
#include "locale_service.h"
#include "affect.h"
#ifdef ENABLE_SWITCHBOT
#include "new_switchbot.h"
#endif

void CHARACTER::LoadOverfallPremium()
{
	if (!IsPC() || !GetDesc())
		return;
	
	DWORD accountId = GetDesc()->GetAccountId();
	
	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery), "SELECT UNIX_TIMESTAMP(premium_time) FROM account.premium_acc WHERE accountId='%d'", accountId);
	std::unique_ptr<SQLMsg> pSelectMsg(DBManager::instance().DirectQuery(szQuery));
	
	if (!pSelectMsg)
		return;
	
	SQLResult* pRes = pSelectMsg->Get();
	
	int premium_time = 0;
	if (pRes->uiNumRows > 0)
	{
		MYSQL_ROW row = mysql_fetch_row(pRes->pSQLResult);
		str_to_number(premium_time, row[0]);
	}
	
	SetOverfallPremiumTime(premium_time);
}

void CHARACTER::CheckOverfallPremium()
{
	if (!IsPC())
		return;
	
	auto premium_time = GetOverfallPremiumTime() - get_global_time();
	
	if (premium_time < 0) {
		if (m_afAffectFlag.IsSet(AFF_OVERFALL_PREMIUM) || FindAffect(AFFECT_OVERFALL_PREMIUM)) {
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Deixas-te de ser um membro premium."));
			
			#ifdef ENABLE_SWITCHBOT
			if (CSwitchbotManager::Instance().RemovePremiumAffect(GetPlayerID()))
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("A velocidade do teu bot de rodar foi reposta."));
			#endif
		}
		
		if (m_afAffectFlag.IsSet(AFF_OVERFALL_PREMIUM))
			m_afAffectFlag.Reset(AFF_OVERFALL_PREMIUM);
		
		if (FindAffect(AFFECT_OVERFALL_PREMIUM))
			RemoveAffect(AFFECT_OVERFALL_PREMIUM);
	}
	else
	{
		if (!m_afAffectFlag.IsSet(AFF_OVERFALL_PREMIUM))
			m_afAffectFlag.Set(AFF_OVERFALL_PREMIUM);
		
		if (!FindAffect(AFFECT_OVERFALL_PREMIUM))
			AddAffect(AFFECT_OVERFALL_PREMIUM, POINT_NONE, 0, AFF_OVERFALL_PREMIUM, premium_time, 0, true, false);
	}
}

bool CHARACTER::IsOverfallPremium() const
{
	return (m_afAffectFlag.IsSet(AFF_OVERFALL_PREMIUM) && FindAffect(AFFECT_OVERFALL_PREMIUM));
}

bool CHARACTER::ActivatePremium(int seconds)
{
	if (IsOverfallPremium()) {
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Já és um membro premium."));
		return false;
	}
	
	DWORD accountId = GetDesc()->GetAccountId();
	
	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery), "INSERT INTO account.premium_acc%s (accountId, premium_time) VALUES (%d, TIMESTAMPADD(SECOND,%d,NOW())) ON DUPLICATE KEY UPDATE premium_time = TIMESTAMPADD(SECOND,%d,NOW());", get_table_postfix(), accountId, seconds, seconds);
	std::unique_ptr<SQLMsg> pSelectMsg(DBManager::instance().DirectQuery(szQuery));
	
	LoadOverfallPremium();
	CheckOverfallPremium();
	
	ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Tornaste-te um membro premium."));
	return true;
}
