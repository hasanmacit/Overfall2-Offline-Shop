//definelere ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
#include "offline_shop.h"
#include "offlineshop_manager.h"
#endif
#if defined(__PRIVATE_SHOP_SEARCH_SYSTEM__) || defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
#include "entity.h"
#include <unordered_map>
bool CompareItemVnumAcPriceAC(COfflineShop::OFFLINE_SHOP_ITEM i, COfflineShop::OFFLINE_SHOP_ITEM j)
{
	return (i.vnum < j.vnum) && (i.price < j.price);
}
#endif

//arat

void CInputMain::OnClick(LPCHARACTER ch, const char* data)

//üstüne ekle

#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
void CInputMain::ShopSearch(LPCHARACTER ch, const char* data, bool bName)
{
	TPacketCGShopSearch* pinfo = (TPacketCGShopSearch*)data;

	if (!ch)
		return;

	if (!data)
		return;

	// if (ch->HaveAnotherPagesOpen())
	// {
		// ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("CANT_DO_THIS_BECAUSE_OTHER_WINDOW_OPEN"));
		// return;
	// }

#ifdef __PRIVATE_SHOP_SEARCH_NEED_ITEM__
	if (!ch->FindSpecifyItem(60004) && !ch->FindSpecifyItem(60005))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("PRIVATE_SHOP_SEARCH_NEED_ITEM"));
		return;
	}
#endif

	int32_t Race = pinfo->Race;
	int32_t Cat = pinfo->ItemCat;
	int32_t SubCat = pinfo->SubCat;
	int32_t MinLevel = pinfo->MinLevel;
	int32_t MaxLevel = pinfo->MaxLevel;
	int32_t MinRefine = pinfo->MinRefine;
	int32_t MaxRefine = pinfo->MaxRefine;
	uint64_t MinGold = pinfo->MinGold;
	uint64_t MaxGold = pinfo->MaxGold;
#ifdef __CHEQUE_SYSTEM__
	uint64_t MinCheque = pinfo->MinCheque;
	uint64_t MaxCheque = pinfo->MaxCheque;
#endif
	std::string itemName = "";

	//Checks
	if (Race < JOB_WARRIOR || Race >
#ifdef ENABLE_WOLFMAN_CHARACTER
		JOB_WOLFMAN
#else
		JOB_SHAMAN
#endif
		)
		return;

	// if (Cat < ITEM_NONE || Cat > ITEM_SOUL) // @ enum EItemTypes common/item_length.h
		// return;

	if (SubCat < USE_POTION || SubCat > USE_RESET_COSTUME_ATTR)
		return;

	if (MinLevel < 0 || MinLevel > PLAYER_MAX_LEVEL_CONST)
		return;

	if (MaxLevel < 0 || MaxLevel > PLAYER_MAX_LEVEL_CONST)
		return;

	if (MinRefine < 0 || MinRefine > 15)
		return;

	if (MaxRefine < 0 || MaxRefine > 15)
		return;

	if (MinGold < 0 || MinGold > GOLD_MAX)
		return;

	if (MaxGold < 0 || MaxGold > GOLD_MAX)
		return;

#ifdef __CHEQUE_SYSTEM__
	if (MinCheque < 0 || MinCheque > CHEQUE_MAX)
		return;

	if (MaxCheque < 0 || MaxCheque > CHEQUE_MAX)
		return;
#endif

	if (MinLevel > MaxLevel)
		return;

	if (MinRefine > MaxRefine)
		return;

	if (MinGold > MaxGold)
		return;

#ifdef __CHEQUE_SYSTEM__
	if (MinCheque > MaxCheque)
		return;
#endif

	if (bName)
	{
		itemName = pinfo->ItemName;
		std::replace(itemName.begin(), itemName.end(), '_', ' ');
	}

	quest::PC* pPC = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());

	if (!pPC)
		return;

	DWORD dwShopSearchSecCycle = 2; // 1 sec
	DWORD dwNowSec = get_global_time();
	DWORD dwLastShopSearchAttrSec = pPC->GetFlag("ShopSearch.LastShopSearchSecAttr");

	if (dwLastShopSearchAttrSec + dwShopSearchSecCycle > dwNowSec)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("PRIVATE_SHOP_SEARCH_NEED_WAIT_%d_LEFT_(%d)"),
			dwShopSearchSecCycle, dwShopSearchSecCycle - (dwNowSec - dwLastShopSearchAttrSec));
		return;
	}

	pPC->SetFlag("ShopSearch.LastShopSearchSecAttr", dwNowSec);

	// if (bName) // todo: add cheque
	// {
// #ifdef __CHEQUE_SYSTEM__
		// sys_log(0, "SHOP_SEARCH: CharName: %s Search: Race: %d Cat: %d SubCat: %d MinLevel: %d MaxLevel: %d MinRefine: %d MaxRefine: %d MinGold: %llu MaxGold: %llu MinCheque: %d MaxCheque: %d itemName: %s", ch->GetName(), Race, Cat, SubCat, MinLevel, MaxLevel, MinRefine, MaxRefine, MinGold, MaxGold, MinCheque, MaxCheque, itemName.c_str());
// #else
		// sys_log(0, "SHOP_SEARCH: CharName: %s Search: Race: %d Cat: %d SubCat: %d MinLevel: %d MaxLevel: %d MinRefine: %d MaxRefine: %d MinGold: %llu MaxGold: %llu itemName: %s", ch->GetName(), Race, Cat, SubCat, MinLevel, MaxLevel, MinRefine, MaxRefine, MinGold, MaxGold, itemName.c_str());
// #endif
	// }
	// else
	// {
// #ifdef __CHEQUE_SYSTEM__
		// sys_log(0, "SHOP_SEARCH: CharName: %s Search: Race: %d Cat: %d SubCat: %d MinLevel: %d MaxLevel: %d MinRefine: %d MaxRefine: %d MinGold: %llu MaxGold: %llu MinCheque: %d MaxCheque: %d", ch->GetName(), Race, Cat, SubCat, MinLevel, MaxLevel, MinRefine, MaxRefine, MinGold, MaxGold, MinCheque, MaxCheque);
// #else
		// sys_log(0, "SHOP_SEARCH: CharName: %s Search: Race: %d Cat: %d SubCat: %d MinLevel: %d MaxLevel: %d MinRefine: %d MaxRefine: %d MinGold: %llu MaxGold: %llu", ch->GetName(), Race, Cat, SubCat, MinLevel, MaxLevel, MinRefine, MaxRefine, MinGold, MaxGold);
// #endif
		// sys_log(0, "SHOP_SEARCH: CharName: %s Search: Race: %d Cat: %d SubCat: %d MinLevel: %d MaxLevel: %d MinRefine: %d MaxRefine: %d MinGold: %llu MaxGold: %llu", ch->GetName(), Race, Cat, SubCat, MinLevel, MaxLevel, MinRefine, MaxRefine, MinGold, MaxGold);
	// }

	CEntity::ENTITY_MAP viewmap = ch->GetViewMap();
	CEntity::ENTITY_MAP::iterator it = viewmap.begin();
	std::vector<COfflineShop::OFFLINE_SHOP_ITEM> sendItems;

	while (it != viewmap.end())
	{
		if (it->first->GetType() != ENTITY_CHARACTER)
		{
			++it;
			continue;
		}

		LPCHARACTER tch = static_cast<LPCHARACTER>((it++)->first);

		if (!tch)
			continue;

		if (!tch->IsOfflineShopNPC() || tch == ch)
			continue;

		if (!tch->GetOfflineShop())
			continue;

		std::vector<COfflineShop::OFFLINE_SHOP_ITEM> shop_items = tch->GetOfflineShop()->GetItemVector();
		std::vector<COfflineShop::OFFLINE_SHOP_ITEM>::iterator item;

		for (item = shop_items.begin(); item != shop_items.end(); ++item)
		{
			bool bLimit = false;

			if (bName)
			{
				if (item->status != 0 || item->vnum == 0)
					continue;

				TItemTable* itemTable = ITEM_MANAGER::instance().GetTable(item->vnum);

				if (!itemTable)
					continue;

				if (itemName.length() > 2)
				{
					for (int i = 0; i < ITEM_LIMIT_MAX_NUM; ++i)
					{
						long lLimit = itemTable->aLimits[i].lValue;
						switch (itemTable->aLimits[i].bType)
						{
						case LIMIT_LEVEL:
							if (!(lLimit >= MinLevel && lLimit <= MaxLevel))
								bLimit = true;
							break;
						case LIMIT_REAL_TIME:
							if (lLimit == 0)
								bLimit = true;
							break;
						}
					}

					if (bLimit)
						continue;

					if (!(item->price >= MinGold && item->price <= MaxGold))
						continue;

#ifdef __CHEQUE_SYSTEM__
					if (!(item->price_cheque >= MinCheque && item->price_cheque <= MaxCheque))
						continue;
#endif

					bool pushback = false;

					std::string foundName = item->szName;
					if (foundName.find(itemName) != std::string::npos)
						pushback = true;

					if (pushback)
						sendItems.push_back(*item);
				}
			}
			else
			{
				if (item->status != 0 || item->vnum == 0)
					continue;

				TItemTable* itemTable = ITEM_MANAGER::instance().GetTable(item->vnum);

				if (!itemTable)
					continue;

				if (itemTable->bType == Cat && itemTable->bSubType == SubCat)
				{
					if (itemTable->bType == ITEM_WEAPON || itemTable->bType == ITEM_ARMOR)
					{
						if (!(item->refine_level >= MinRefine && item->refine_level <= MaxRefine))
							continue;
					}

					for (int i = 0; i < ITEM_LIMIT_MAX_NUM; ++i)
					{
						long lLimit = itemTable->aLimits[i].lValue;
						switch (itemTable->aLimits[i].bType)
						{
						case LIMIT_LEVEL:
							if (!(lLimit >= MinLevel && lLimit <= MaxLevel))
								bLimit = true;
							break;
						case LIMIT_REAL_TIME:
							if (lLimit == 0)
								bLimit = true;
							break;
						}
					}

					if (bLimit)
						continue;

					if (!(item->price >= MinGold && item->price <= MaxGold))
						continue;

#ifdef __CHEQUE_SYSTEM__
					if (!(item->price_cheque >= MinCheque && item->price_cheque <= MaxCheque))
						continue;
#endif

					bool cont = false;
					switch (Race)
					{
					case JOB_WARRIOR:
						if (IS_SET(itemTable->dwAntiFlags, ITEM_ANTIFLAG_WARRIOR))
							cont = true;
						break;

					case JOB_ASSASSIN:
						if (IS_SET(itemTable->dwAntiFlags, ITEM_ANTIFLAG_ASSASSIN))
							cont = true;
						break;

					case JOB_SURA:
						if (IS_SET(itemTable->dwAntiFlags, ITEM_ANTIFLAG_SURA))
							cont = true;
						break;

					case JOB_SHAMAN:
						if (IS_SET(itemTable->dwAntiFlags, ITEM_ANTIFLAG_SHAMAN))
							cont = true;
						break;

#ifdef ENABLE_WOLFMAN_CHARACTER
					case JOB_WOLFMAN:
						if (IS_SET(itemTable->dwAntiFlags, ITEM_ANTIFLAG_WOLFMAN))
							cont = true;
						break;
#endif
					}

					if (cont)
						continue;

					sendItems.push_back(*item);
				}
				else
					continue;
			}
		}
	}

	std::stable_sort(sendItems.begin(), sendItems.end(), CompareItemVnumAcPriceAC);
	std::vector<COfflineShop::OFFLINE_SHOP_ITEM>::iterator item;

	for (item = sendItems.begin(); item != sendItems.end(); ++item)
	{
		if (item->status != 0 || item->vnum == 0)
			continue;

		TItemTable* itemTable = ITEM_MANAGER::instance().GetTable(item->vnum);

		if (itemTable)
		{
			LPDESC d = ch->GetDesc();

			if (!d)
				return;

			TPacketGCShopSearchItemSet pack;
			pack.header = HEADER_GC_SHOPSEARCH_SET;

			pack.count = item->count;
			pack.vnum = item->vnum;
			pack.flags = itemTable->dwFlags;
			pack.anti_flags = itemTable->dwAntiFlags;
			pack.price = item->price;
#ifdef __CHEQUE_SYSTEM__
			pack.price_cheque = item->price_cheque;
#endif
			pack.vid = item->shop_id;
#ifdef __BL_TRANSMUTATION__
			pack.dwTransmutationVnum = item->dwTransmutationVnum;
#endif
			pack.Cell = item->pos;

			thecore_memcpy(pack.alSockets, item->alSockets, sizeof(pack.alSockets));
			thecore_memcpy(pack.aAttr, item->aAttr, sizeof(pack.aAttr));

			d->LargePacket(&pack, sizeof(TPacketGCShopSearchItemSet));
		}
	}
}
#endif

#if defined(__PRIVATE_SHOP_SEARCH_SYSTEM__) || defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
void CInputMain::ShopSearchBuy(LPCHARACTER ch, const char* data)
{
	TPacketCGShopSearchBuy* pinfo = (TPacketCGShopSearchBuy*)data;

	int32_t shopVid = pinfo->shopVid;
	int32_t shopItemPos = pinfo->shopItemPos;
	int shopPos = pinfo->shopPos;
	DWORD item_id = pinfo->item_id;
	long long item_price = pinfo->item_price;

	if (!ch)
		return;

	#if defined(__ENABLE_PREMIUM_MEMBERS__)
	if (!ch->IsOverfallPremium())
		return;
	#endif

#if defined(__PRIVATE_SHOP_SEARCH_NEED_ITEM__) && !defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
	if (0 == quest::CQuestManager::instance().GetEventFlag("enable_shop_search"))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("PRIVATE_SHOP_SEARCH_SYSTEM_DISABLED"));
		return;
	}

	if (!ch->FindSpecifyItem(60005))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("PRIVATE_SHOP_SEARCH_NEED_ITEM"));
		return;
	}
#endif
	
	LPCHARACTER pkChrShop = CHARACTER_MANAGER::instance().Find(shopVid);

	if (!pkChrShop) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopBuyError %d", SHOP_SUBHEADER_GC_REMOVED_FROM_SHOP);
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearchRemoved %d", shopPos);
		return;
	}

	LPOFFLINESHOP pkShop = pkChrShop->GetOfflineShop();

	if (!pkShop) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopBuyError %d", SHOP_SUBHEADER_GC_REMOVED_FROM_SHOP);
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearchRemoved %d", shopPos);
		return;
	}

#if defined(__PRIVATE_SHOP_SEARCH_NEED_ITEM__) && !defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
	if (DISTANCE_APPROX(ch->GetX() - pkChrShop->GetX(), ch->GetY() - pkChrShop->GetY()) > VIEW_RANGE)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("상점과의 거리가 너무 멀어 물건을 살 수 없습니다."));
		return;
	}

	if (ch->GetMapIndex() != pkChrShop->GetMapIndex())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("YOU_CANNOT_BUY_THIS_BECAUSE_NOT_IN_SAME_MAP"));
		return;
	}
#endif

	ch->SetOfflineShopOwner(pkChrShop);
	pkShop->SetGuestMap(ch);
	int32_t returnHeader = pkShop->Buy(ch, shopItemPos, item_id, item_price);

	if (SHOP_SUBHEADER_GC_OK == returnHeader)
	{
#if defined(__PRIVATE_SHOP_SEARCH_NEED_ITEM__) && !defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
			ch->ChatPacket(CHAT_TYPE_COMMAND, "ShopSearchBuy");
#elseif defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearchBuy %d", shopPos);
#endif
			ch->SetOfflineShop(NULL);
			ch->SetOfflineShopOwner(NULL);
			pkShop->RemoveGuestMap(ch);
	}
	else
	{
#if defined(__PRIVATE_SHOP_SEARCH_NEED_ITEM__) && !defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
			ch->ChatPacket(CHAT_TYPE_COMMAND, "ShopSearchError %d", returnHeader);
#elseif defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopBuyError %d", returnHeader);
		if (returnHeader == SHOP_SUBHEADER_GC_SOLD_OUT)
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearchBuy %d", shopPos);
		else if (returnHeader == SHOP_SUBHEADER_GC_REMOVED_FROM_SHOP)
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearchRemoved %d", shopPos);
		else if (returnHeader == SHOP_SUBHEADER_GC_PRICE_CHANGED) {
			long long newPrice = pkShop->GetOfflineShopItemPrice(shopItemPos);
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearchPriceChanged %d %lld", shopPos, newPrice);
		}
#endif
		ch->SetOfflineShop(NULL);
		ch->SetOfflineShopOwner(NULL);
		pkShop->RemoveGuestMap(ch);
	}
}
#endif

#ifdef __NEW_PRIVATE_SHOP_SEARCH_SYSTEM__

#include "newPrivateShopSearch.h"
struct FFindNewOffShop
{
	std::vector<LPCHARACTER> v_player_list;

	void operator()(LPENTITY pEnt)
	{
		if (pEnt->IsType(ENTITY_CHARACTER) == true)
		{
			LPCHARACTER pChar = (LPCHARACTER)pEnt;
			if (pChar && pChar->IsOfflineShopNPC() && pChar->GetOfflineShop())
				v_player_list.push_back(pChar);
		}
	}
};

void CInputMain::NewShopSearch(LPCHARACTER ch, const char* data)
{
	TPacketCGNewShopSearch* pinfo = (TPacketCGNewShopSearch*)data;

	if (!ch)
		return;
	
	if (!data) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}

	if (ch->IsOpenSafebox() || ch->GetShop() || ch->IsCubeOpen() ||
		ch->IsDead() || ch->GetExchange() || ch->GetMyShop()
#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
		|| ch->GetOfflineShop()
#endif
		)
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_HAVE_PAGE_OPENED);
		return;
	}

	quest::PC* pPC = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());

	if (!pPC)
		return;

	DWORD dwShopSearchSecCycle = 2; // 1 sec
	DWORD dwNowSec = get_global_time();
	DWORD dwLastShopSearchAttrSec = pPC->GetFlag("NewShopSearch.LastShopSearchSecAttr");

	if (dwLastShopSearchAttrSec + dwShopSearchSecCycle > dwNowSec)
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_PLEASE_WAIT);
		return;
	}

	pPC->SetFlag("NewShopSearch.LastShopSearchSecAttr", dwNowSec);

	using namespace NSS_CFG;
	
	int32_t category = pinfo->ItemCat;
	int32_t sub_category = pinfo->SubCat;

	int minLevelValue = pinfo->minLevelValue;
	int maxLevelValue = pinfo->maxLevelValue;
	int minDHValue = pinfo->minDHValue;
	int maxDHValue = pinfo->maxDHValue;
	int minDMValue = pinfo->minDMValue;
	int maxDMValue = pinfo->maxDMValue;
	int itemRefineLevel = pinfo->itemRefineLevel;
	int acceAbsPerc = pinfo->acceAbsPerc;
	int dsClarityValue = pinfo->dsClarityValue;
	int bonusChoose = pinfo->bonusChoose;
	int itemGender = pinfo->itemGender;
	int bName = pinfo->have_name;
	std::string itemName = "";
	
	if (bName)
	{
		itemName = pinfo->ItemName;
		std::replace(itemName.begin(), itemName.end(), '_', ' ');
	}

	if (category >= NSS_MAX_NUM || category < NSS_GERAL_CATEGORY) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}
	
	if (nss_category_cfg[category].subcategory_numb <= sub_category || 0 > sub_category) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}

	if (bonusChoose != -1 && bonusChoose < 0) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}
	if (dsClarityValue != -1 && (dsClarityValue < 0 || dsClarityValue > 4)) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}

	if (acceAbsPerc != -1 && (acceAbsPerc < 11 || acceAbsPerc > 25)) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}

	if (minDHValue != -1)
	{
		if (minDHValue < 0) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}

		if (minDHValue > 30) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}
		
		if (maxDHValue != -1)
		{
			if (minDHValue > maxDHValue) {
				ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
				return;
			}
		}
	}

	if (maxDHValue != -1)
	{
		if (maxDHValue < 0) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}

		if (maxDHValue > 30) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		};
	}
	
	if (minDMValue != -1)
	{
		if (minDMValue < 0) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}

		if (minDMValue > 65) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}
		
		if (maxDMValue != -1)
		{
			if (minDMValue > maxDMValue) {
				ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
				return;
			}
		}
	}

	if (maxDMValue != -1)
	{
		if (maxDMValue < 0) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}

		if (maxDMValue > 65) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}
	}

	if (minLevelValue != -1)
	{
		if (minLevelValue < 0) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}

		if (minLevelValue > PLAYER_MAX_LEVEL_CONST) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}
		
		if (maxLevelValue != -1)
		{
			if (minLevelValue > maxLevelValue) {
				ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
				return;
			}
		}
	}

	if (maxLevelValue != -1)
	{
		if (maxLevelValue < 0) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}

		if (maxLevelValue > PLAYER_MAX_LEVEL_CONST) {
			ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
			return;
		}
	}
	
	if (itemRefineLevel != -1 && (itemRefineLevel < 0 || itemRefineLevel > 9)) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}

	if (itemGender != -1 && (itemGender != 0 && itemGender != 1)) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}
	
	#if defined(__ENABLE_PREMIUM_MEMBERS__)
	bool isPremium = ch->IsOverfallPremium();
	#else
	bool isPremium = false;
	#endif
	
	std::vector<COfflineShop::OFFLINE_SHOP_ITEM> sendItems;

	auto find_map = allowed_norm_search_shop_maps.find(ch->GetEmpire());
	if (find_map == allowed_norm_search_shop_maps.end()) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_OTHER_ERROR);
		return;
	}
	
	bool found_player_map = false;
	DWORD player_map_index = ch->GetMapIndex();
	for (int i = 0; i != 6; ++i)
	{
		if (premium_maps[i] == player_map_index) {
			found_player_map = true;
			break;
		}
	}
	
	if (!found_player_map) {
		ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearch_Error %d", NPSS_NEED_TO_BE_IN_EMPIRE);
		return;
	}
	
	for (int i = 0; i != 6; ++i)
	{
		if (i != 0 && !isPremium)
			break;
		
		DWORD search_map = isPremium ? premium_maps[i] : player_map_index;
		LPSECTREE_MAP pMap = SECTREE_MANAGER::instance().GetMap(search_map);
		if (!pMap)
			break;
		
		FFindNewOffShop find_function;
		pMap->for_each(find_function);
		
		if (find_function.v_player_list.size() > 0)
		{
			for (auto &player : find_function.v_player_list) {
				LPCHARACTER tch = player;
				if (!tch || (tch && (tch == ch)))
					continue;
				
				std::vector<COfflineShop::OFFLINE_SHOP_ITEM> shop_items = tch->GetOfflineShop()->GetItemVector();
				std::vector<COfflineShop::OFFLINE_SHOP_ITEM>::iterator item;

				for (item = shop_items.begin(); item != shop_items.end(); ++item)
				{
					bool bLimit = false;
					
					if (item->status != 0 || item->vnum == 0)
						continue;

					TItemTable* itemTable = ITEM_MANAGER::instance().GetTable(item->vnum);

					if (!itemTable)
						continue;
					
					if (!CheckItemFilter(itemTable, category, sub_category))
						continue;

					if (bName)
					{
						std::string foundName = item->szName;
						if (!(foundName.find(itemName) != std::string::npos))
							continue;
					}
					
					//Verifica o range de niveis do item
					for (int i = 0; i < ITEM_LIMIT_MAX_NUM; ++i)
					{
						long lLimit = itemTable->aLimits[i].lValue;
						switch (itemTable->aLimits[i].bType)
						{
							case LIMIT_LEVEL:
								{
									if (minLevelValue != -1)
										if (minLevelValue >= lLimit)
											bLimit = true;
									
									if (maxLevelValue != -1)
										if (maxLevelValue <= lLimit)
											bLimit = true;
								}
								break;
							
							case LIMIT_REAL_TIME:
								if (lLimit == 0)
									bLimit = true;
								break;
							
							default:
								if (minLevelValue != -1 || maxLevelValue != -1)
									bLimit = true;
								break;
						}
					}

					if (bLimit)
						continue;
					
					if (itemRefineLevel != -1) {
						if (itemTable->bType == ITEM_WEAPON || itemTable->bType == ITEM_ARMOR)
						{
							if (item->refine_level < itemRefineLevel)
								continue;
						}
						else
							continue;
					}
					
					if (maxDHValue != -1 || minDHValue != -1)
					{
						if (itemTable->bType == ITEM_WEAPON)
						{
							bool found_attr = false;
							short bonus_value = 0;
							#ifdef ENABLE_SWITCHBOT
							for (int i = 0; i < MAX_NORM_ATTR_NUM; ++i)
							#else
							for (int i = 0; i < ITEM_MANAGER::MAX_NORM_ATTR_NUM; ++i)
							#endif
							{
								if (item->aAttr[i].bType == APPLY_SKILL_DAMAGE_BONUS) {
									found_attr = true;
									bonus_value = item->aAttr[i].sValue;
									break;
								}
							}
							
							if (!found_attr)
								continue;
							
							if (minDHValue != -1)
							{
								if (minDHValue > bonus_value)
									continue;
							}
							
							if (maxDHValue != -1)
							{
								if (maxDHValue < bonus_value)
									continue;
							}
						}
						else
							continue;
					}

					if (maxDMValue != -1 || minDMValue != -1)
					{
						if (itemTable->bType == ITEM_WEAPON)
						{
							bool found_attr = false;
							short bonus_value = 0;
							#ifdef ENABLE_SWITCHBOT
							for (int i = 0; i < MAX_NORM_ATTR_NUM; ++i)
							#else
							for (int i = 0; i < ITEM_MANAGER::MAX_NORM_ATTR_NUM; ++i)
							#endif
							{
								if (item->aAttr[i].bType == APPLY_NORMAL_HIT_DAMAGE_BONUS) {
									found_attr = true;
									bonus_value = item->aAttr[i].sValue;
									break;
								}
							}
							
							if (!found_attr)
								continue;
							
							if (minDMValue != -1)
							{
								if (minDMValue > bonus_value)
									continue;
							}
							
							if (maxDMValue != -1)
							{
								if (maxDMValue < bonus_value)
									continue;
							}
						}
						else
							continue;
					}
					
					if (acceAbsPerc != -1) {
						if (itemTable->bType == ITEM_COSTUME && itemTable->bSubType == COSTUME_ACCE)
						{
							if (item->alSockets[ACCE_ABSORPTION_SOCKET] < acceAbsPerc)
								continue;
						}
						else
							continue;
					}
					
					if (dsClarityValue != -1)
					{
						if (itemTable->bType == ITEM_DS)
						{
							BYTE grade_idx = (item->vnum / 1000) % 10;
							if (grade_idx < dsClarityValue)
								continue;
						}
						else
							continue;
					}

					if (bonusChoose != -1)
					{
						bool found_attr = false;
						
						#ifdef ENABLE_SWITCHBOT
						for (int i = 0; i < MAX_NORM_ATTR_NUM; ++i)
						#else
						for (int i = 0; i < ITEM_MANAGER::MAX_NORM_ATTR_NUM; ++i)
						#endif
						{
							if (item->aAttr[i].bType == bonusChoose) {
								found_attr = true;
								break;
							}
						}
						
						if (!found_attr)
							continue;
					}
					
					if (itemGender != -1)
					{
						if (itemGender == 1) //SEX_FEMALE
						{
							if (!IS_SET(itemTable->dwAntiFlags, ITEM_ANTIFLAG_FEMALE)) {
								continue;
							}
							
						}
						else if (itemGender == 0) //SEX_MALE
						{
							if (!IS_SET(itemTable->dwAntiFlags, ITEM_ANTIFLAG_MALE)) {
								continue;
							}
						}
					}
					//
					
					sendItems.push_back(*item);
				}
			}
		}
	}

	std::vector<COfflineShop::OFFLINE_SHOP_ITEM>::iterator item;

	for (item = sendItems.begin(); item != sendItems.end(); ++item)
	{
		if (item->status != 0 || item->vnum == 0)
			continue;

		TItemTable* itemTable = ITEM_MANAGER::instance().GetTable(item->vnum);

		if (itemTable)
		{
			LPDESC d = ch->GetDesc();

			if (!d)
				return;
			

			TPacketGCShopSearchItemSet pack;
			pack.header = HEADER_GC_NEW_SHOPSEARCH_SET;

			pack.count = item->count;
			pack.vnum = item->vnum;
			pack.flags = itemTable->dwFlags;
			pack.anti_flags = itemTable->dwAntiFlags;
			pack.price = item->price;
			pack.vid = item->shop_id;
			pack.item_id = item->id;
#ifdef __BL_TRANSMUTATION__
			pack.dwTransmutationVnum = item->dwTransmutationVnum;
#endif
			pack.shop_time = 0;
			pack.off_shop_map_index = 0;
			
			pack.ch_map_index = ch->GetMapIndex();
			
			std::string sellerName = "None";
			
			
			LPCHARACTER pkChrShop = CHARACTER_MANAGER::instance().Find(item->shop_id);
			if (pkChrShop) {
				LPOFFLINESHOP pkShop = pkChrShop->GetOfflineShop();
				sellerName = pkChrShop->GetName();
				if (pkShop) {
					pack.shop_time = pkShop->GetOfflineShopTime();
					pack.off_shop_map_index = pkShop->GetOfflineShopMapIndex();
				}
			}
			strlcpy(pack.sellerName, sellerName.c_str(), sizeof(pack.sellerName));
			
			pack.Cell = item->pos;

			thecore_memcpy(pack.alSockets, item->alSockets, sizeof(pack.alSockets));
			thecore_memcpy(pack.aAttr, item->aAttr, sizeof(pack.aAttr));

			d->LargePacket(&pack, sizeof(TPacketGCShopSearchItemSet));
		}
	}

	ch->ChatPacket(CHAT_TYPE_COMMAND, "NewShopSearchFinish");
}
#endif

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
int CInputMain::OfflineShop(LPCHARACTER ch, const char* data, size_t uiBytes)
{
	TPacketCGOfflineShop* p = (TPacketCGOfflineShop*)data;

	if (uiBytes < sizeof(TPacketCGOfflineShop))
		return -1;

	if (test_server)
		sys_log(0, "CInputMain::OfflineShop ==> SubHeader %d", p->subheader);

	const char* c_pData = data + sizeof(TPacketCGOfflineShop);
	uiBytes -= sizeof(TPacketCGOfflineShop);

	switch (p->subheader)
	{
	case SHOP_SUBHEADER_CG_END:
	{
		sys_log(1, "INPUT: %s OFFLINE_SHOP: END", ch->GetName());
		COfflineShopManager::instance().StopShopping(ch);
		return 0;
	}

	case SHOP_SUBHEADER_CG_BUY:
	{
		if (uiBytes < sizeof(BYTE) + sizeof(BYTE))
			return -1;

		BYTE bPos = *(c_pData + 1);
		sys_log(1, "INPUT: %s OFFLINE_SHOP: BUY %d", ch->GetName(), bPos);
		COfflineShopManager::instance().Buy(ch, bPos);
		return (sizeof(BYTE) + sizeof(BYTE));
	}

	case SHOP_SUBHEADER_CG_DESTROY_OFFLINE_SHOP:
	{
		sys_log(1, "INPUT: %s OFFLINE_SHOP_DESTROY", ch->GetName());
		COfflineShopManager::instance().DestroyOfflineShop(ch, ch->GetOfflineShopVID(), true);
		return 0;
	}

	case SHOP_SUBHEADER_CG_ADD_ITEM:
	{
		if (uiBytes < sizeof(TOfflineShopItemTable2))
			return -1;

		#if defined(__ENABLE_PREMIUM_MEMBERS__)
		if (!ch->IsOverfallPremium()) {
			if (ch->GetMapIndex() != COfflineShopManager::instance().GetMapIndex(ch->GetPlayerID()))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You need to be one premium member to do this on this map."));
				return (sizeof(TOfflineShopItemTable2));
			}
			
			if (ch->GetOfflineShopChannel() != g_bChannel)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You need to be one premium member to do this on this channel."));
				return (sizeof(TOfflineShopItemTable2));
			}
		}
		#endif

		TOfflineShopItemTable2* pTable = (TOfflineShopItemTable2*)(c_pData);
		
		if (pTable->dwPrice <= 0)
			pTable->dwPrice = 1;
		
#ifdef __CHEQUE_SYSTEM__
		COfflineShopManager::instance().AddItem(ch, pTable->bDisplayPos, pTable->bPos, pTable->dwPrice, pTable->dwPriceCheque);
#else
		COfflineShopManager::instance().AddItem(ch, pTable->bDisplayPos, pTable->bPos, pTable->dwPrice);
#endif
		return (sizeof(TOfflineShopItemTable2));
	}

	case SHOP_SUBHEADER_CG_REMOVE_ITEM:
	{
		if (uiBytes < sizeof(BYTE))
			return -1;

		#if defined(__ENABLE_PREMIUM_MEMBERS__)
		if (!ch->IsOverfallPremium()) {
			if (ch->GetMapIndex() != COfflineShopManager::instance().GetMapIndex(ch->GetPlayerID()))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You need to be one premium member to do this on this map."));
				return (sizeof(BYTE));
			}
			
			if (ch->GetOfflineShopChannel() != g_bChannel)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You need to be one premium member to do this on this channel."));
				return (sizeof(BYTE));
			}
		}
		#endif

		BYTE bPos = *c_pData;
		sys_log(0, "INPUT: %s REMOVE_ITEM : %d", ch->GetName(), bPos);
		COfflineShopManager::instance().RemoveItem(ch, bPos);
		return (sizeof(BYTE));
	}

	case SHOP_SUBHEADER_CG_REFRESH:
	{
		sys_log(0, "INPUT: %s OFFLINE_SHOP_REFRESH_ITEM", ch->GetName());
		COfflineShopManager::instance().Refresh(ch);
		return 0;
	}

	case SHOP_SUBHEADER_CG_REFRESH_MONEY:
	{
		sys_log(0, "INPUT: %s OFFLINE_SHOP_REFRESH_MONEY", ch->GetName());
		COfflineShopManager::instance().RefreshMoney(ch);
		return 0;
	}

	case SHOP_SUBHEADER_CG_WITHDRAW_MONEY:
	{
		if (uiBytes < sizeof(long long))
			return -1;

		#if defined(__ENABLE_PREMIUM_MEMBERS__)
		BYTE shop_channel = ch->GetOfflineShopChannel();
		if (!ch->IsOverfallPremium() && shop_channel != 0) {
			if (ch->GetMapIndex() != COfflineShopManager::instance().GetMapIndex(ch->GetPlayerID()))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You need to be one premium member to do this on this map."));
				return (sizeof(long long));
			}
			
			if (ch->GetOfflineShopChannel() != g_bChannel)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You need to be one premium member to do this on this channel."));
				return (sizeof(long long));
			}
		}
		#endif
		
		const long long gold = *reinterpret_cast<const long long*>(c_pData);
		sys_log(0, "INPUT: %s(%d) OFFLINE_SHOP_WITHDRAW_MONEY", ch->GetName(), gold);
		COfflineShopManager::instance().WithdrawMoney(ch, gold);
		return (sizeof(long long));
	}

#ifdef __CHEQUE_SYSTEM__
	case SHOP_SUBHEADER_CG_WITHDRAW_CHEQUE:
	{
		if (uiBytes < sizeof(DWORD))
			return -1;

		const DWORD cheque = *reinterpret_cast<const DWORD*>(c_pData);
		sys_log(0, "INPUT: %s(%d) SHOP_SUBHEADER_CG_WITHDRAW_CHEQUE", ch->GetName(), cheque);
		COfflineShopManager::instance().WithdrawCheque(ch, cheque);
		return (sizeof(DWORD));
	}
#endif

	case SHOP_SUBHEADER_CG_REFRESH_UNSOLD_ITEMS:
	{
		sys_log(0, "INPUT: %s OFFLINE_SHOP_REFRESH_UNSOLD_ITEMS", ch->GetName());
		COfflineShopManager::instance().RefreshUnsoldItems(ch);
		return 0;
	}

	case SHOP_SUBHEADER_CG_TAKE_ITEM:
	{
		if (uiBytes < sizeof(BYTE))
			return -1;

		BYTE bPos = *c_pData;
		sys_log(0, "INPUT: %s OFFLINE_SHOP_TAKE_ITEM", ch->GetName());
		COfflineShopManager::instance().TakeItem(ch, bPos);
		return (sizeof(BYTE));
	}

	case SHOP_SUBHEADER_CG_CHANGE_ITEM_PRICE:
	{
		if (uiBytes < sizeof(BYTE) + sizeof(long long))
			return -1;

		#if defined(__ENABLE_PREMIUM_MEMBERS__)
		if (!ch->IsOverfallPremium()) {
			if (ch->GetMapIndex() != COfflineShopManager::instance().GetMapIndex(ch->GetPlayerID()))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You need to be one premium member to do this on this map."));
				return (sizeof(BYTE) + sizeof(long long));
			}
			
			if (ch->GetOfflineShopChannel() != g_bChannel)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Offline Shop> You need to be one premium member to do this on this channel."));
				return (sizeof(BYTE) + sizeof(long long));
			}
		}
		#endif
		
		const BYTE bPos = *reinterpret_cast<const BYTE*>(c_pData);
		const long long llPrice = *reinterpret_cast<const long long*>(c_pData + 1);
		
		sys_log(0, "INPUT: %s OFFLINE_SHOP_CHANGE_ITEM_PRICE", ch->GetName());
		COfflineShopManager::instance().ChangeOfflineShopItemPrice(ch, bPos, llPrice);
		
		return (sizeof(BYTE) + sizeof(long long));
	}

	case SHOP_SUBHEADER_CG_CHECK:
	{
		COfflineShopManager::instance().HasOfflineShop(ch);
		return 0;
	}

	default:
	{
		sys_err("CInputMain::OfflineShop : Unknown subheader %d : %s", p->subheader, ch->GetName());
		break;
	}
	}

	return 0;
}

void CInputMain::SendChangeOfflineShopName(LPCHARACTER pkChar, const char* c_pData)
{
	TPacketCGChangeOfflineShopName* sPacket = (TPacketCGChangeOfflineShopName*)c_pData;
	
	if (!c_pData)
		return;
	
	if (!pkChar)
		return;
	
	DWORD dwOwnerPID = pkChar->GetPlayerID();
	BYTE shopChannel = pkChar->GetOfflineShopChannel();
	bool canGetOfflineShop = COfflineShopManager::instance().CanGetOfflineShop(dwOwnerPID);
	const char* newShopName = sPacket->szSign;
	
	if (shopChannel == 0)
		return;
	
	if (g_bChannel != shopChannel || !canGetOfflineShop)
	{
		TPacketGGOfflineShopChangeName p;
		p.bHeader = HEADER_GG_OFFLINE_SHOP_CHANGE_NAME;
		p.dwOwnerPID = dwOwnerPID;
		strlcpy(p.szSign, newShopName, sizeof(p.szSign));
		P2P_MANAGER::instance().Send(&p, sizeof(TPacketGGOfflineShopChangeName));
	}
	else
		COfflineShopManager::instance().ChangeOfflineShopName(dwOwnerPID, newShopName);
}
#endif

//arat

void CInputMain::Refine(LPCHARACTER ch, const char* c_pData)

//üstüne ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
int CInputMain::MyOfflineShop(LPCHARACTER ch, const char* c_pData, size_t uiBytes)
{
	TPacketCGMyOfflineShop* p = (TPacketCGMyOfflineShop*)c_pData;
	int iExtraLen = p->bCount * sizeof(TOfflineShopItemTable);

	if (uiBytes < sizeof(TPacketCGMyOfflineShop) + iExtraLen)
		return -1;

	if (ch->IsStun() || ch->IsDead())
		return (iExtraLen);

#ifdef __ACCE_COSTUME_SYSTEM__
	if (ch->GetExchange() || ch->IsOpenSafebox() || ch->GetShopOwner() || ch->IsCubeOpen() || ch->GetOfflineShopOwner() || ch->IsOpenAcce())
#else
	if (ch->GetExchange() || ch->IsOpenSafebox() || ch->GetShopOwner() || ch->IsCubeOpen() || ch->GetOfflineShopOwner())
#endif
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("다른 거래중일경우 개인상점을 열수가 없습니다."));
		return (iExtraLen);
	}

	sys_log(0, "MyOfflineShop count %d", p->bCount);
	ch->OpenMyOfflineShop(p->szSign, (TOfflineShopItemTable*)(c_pData + sizeof(TPacketCGMyOfflineShop)), p->bCount, p->bNpcType, p->bBoardStyle);
	return (iExtraLen);
}
#endif

//arat

case HEADER_CG_ITEM_USE:

//altına ekle

#ifdef __OFFLINE_PRIVATE_SHOP_SYSTEM__
	case HEADER_CG_OFFLINE_SHOP:
		if ((iExtraLen = OfflineShop(ch, c_pData, m_iBufferLeft)) < 0)
			return -1;
		break;

	case HEADER_CG_MY_OFFLINE_SHOP:
		if ((iExtraLen = MyOfflineShop(ch, c_pData, m_iBufferLeft)) < 0)
			return -1;
		break;
	
	case HEADER_CG_OFFLINE_SHOP_CHANGE_SHOP_NAME:
		SendChangeOfflineShopName(ch, c_pData);
		break;
#endif
#ifdef __PRIVATE_SHOP_SEARCH_SYSTEM__
	case HEADER_CG_SHOP_SEARCH:
		if (!ch->IsObserverMode())
			ShopSearch(ch, c_pData, false);
		break;

	case HEADER_CG_SHOP_SEARCH_SUB:
		if (!ch->IsObserverMode())
			ShopSearch(ch, c_pData, true);
		break;

	case HEADER_CG_SHOP_SEARCH_BUY:
		if (!ch->IsObserverMode())
			ShopSearchBuy(ch, c_pData);
		break;
#endif

#if defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
	case HEADER_CG_NEW_SHOP_SEARCH:
		if (!ch->IsObserverMode())
			NewShopSearch(ch, c_pData);
		break;
#endif