#include "../../common/CommonDefines.h"
#include "../../common/item_length.h"
#include "../../common/length.h"

#include "item.h"
#include "item_manager.h"

#if defined(__NEW_PRIVATE_SHOP_SEARCH_SYSTEM__)
namespace NSS_CFG
{
	//Número de categorias existentes
	enum categorysTypes
	{
		NSS_GERAL_CATEGORY,
		
		NSS_WEAPONS_CATEGORY,
		NSS_ARMOR_CATEGORY,
		NSS_COSTUME_CATEGORY,
		NSS_RINGS_CATEGORY,
		NSS_DRAGON_ALCHEMY_CATEGORY,
		NSS_CATEGORY_MOUNT,
		NSS_CATEGORY_PETS,
		NSS_CATEGORY_NEEDED_ITENS,
		NSS_CATEGORY_SKILL_BOOK,
		NSS_CATEGORY_GIFTBOX,
		NSS_CATEGORY_MINING,
		NSS_CATEGORY_REFINE,
		
		NSS_MAX_NUM,
	};
	
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//Opcoes que cada categoria contém
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	enum subcategory_WEAPONS
	{
		WEAPON_CATEGORY_GENERAL,
		WEAPON_CATEGORY_SWORD,
		WEAPON_CATEGORY_2_SWORD,
		WEAPON_CATEGORY_SURA_SWORD,
		WEAPON_CATEGORY_DAGGER,
		WEAPON_CATEGORY_BOW,
		WEAPON_CATEGORY_BELL,
		WEAPON_CATEGORY_FAN,
		WEAPON_CATEGORY_ARROW,
		
		WEAPON_CATEGORY_MAX_NUM,
	};

	enum subcategory_ARMOR
	{
		ARMOR_CATEGORY_GENERAL,
		ARMOR_CATEGORY_ARMOR,
		ARMOR_CATEGORY_HELMET,
		ARMOR_CATEGORY_SHIELD,
		ARMOR_CATEGORY_NECKLACE,
		ARMOR_CATEGORY_BRACELET,
		ARMOR_CATEGORY_EAR_RINGS,
		ARMOR_CATEGORY_SHOES,
		ARMOR_CATEGORY_BELTS,
		ARMOR_CATEGORY_PENDANT,
		
		ARMOR_CATEGORY_MAX_NUM,
	};

	enum subcategory_COSTUME
	{
		COSTUME_CATEGORY_GENERAL,
		
		COSTUME_CATEGORY_HAIR_STYLE,
		COSTUME_CATEGORY_COSTUMES,
		COSTUME_CATEGORY_WEAPON_SKINS,
		COSTUME_CATEGORY_ACCE,
		
		COSTUME_CATEGORY_MAX_NUM,
	};

	enum subcategory_RINGS
	{
		RINGS_CATEGORY_GENERAL,
		
		RINGS_CATEGORY_NORMAL,
		RINGS_CATEGORY_SPECIAL,
		
		RINGS_CATEGORY_MAX_NUM,
	};

	enum subcategory_DRAGON_ALCHEMY
	{
		DRAGON_ALCHEMY_CATEGORY_GENERAL,
		
		DRAGON_ALCHEMY_CATEGORY_DIAMOND,
		DRAGON_ALCHEMY_CATEGORY_ONIX,
		DRAGON_ALCHEMY_CATEGORY_GRANADA,
		DRAGON_ALCHEMY_CATEGORY_SAFIRA,
		DRAGON_ALCHEMY_CATEGORY_JADE,
		DRAGON_ALCHEMY_CATEGORY_RUBI,
		
		DRAGON_ALCHEMY_CATEGORY_MAX_NUM,
	};

	enum subcategory_MOUNT
	{
		CATEGORY_MOUNT_CATEGORY_GENERAL,
		
		CATEGORY_MOUNT_NORM,
		CATEGORY_MOUNT_SPECIAL,
		CATEGORY_MOUNT_SKINS,
		
		CATEGORY_MOUNT_CATEGORY_MAX_NUM,
	};

	enum subcategory_PETS
	{
		CATEGORY_PETS_CATEGORY_GENERAL,
		
		CATEGORY_PETS_NORM,
		CATEGORY_PETS_SPECIAL,
		CATEGORY_PETS_SKIN,
		CATEGORY_PETS_EVOLVE_PETS,
		
		CATEGORY_PETS_CATEGORY_MAX_NUM,
	};

	enum subcategory_NEEDED_ITENS
	{
		CATEGORY_NEEDED_ITENS_CATEGORY_GENERAL,
		
		CATEGORY_NEEDED_ITENS_ORV_DD,
		CATEGORY_NEEDED_ITENS_CHANGERS,
		CATEGORY_NEEDED_ITENS_MELHORAMENTO,
		CATEGORY_NEEDED_ITENS_SHOP_ITENS,
		CATEGORY_NEEDED_ITENS_STONES,
		
		CATEGORY_NEEDED_ITENS_CATEGORY_MAX_NUM,
	};

	enum subcategory_SKILL_BOOK
	{
		CATEGORY_SKILL_BOOK_CATEGORY_GENERAL,
		
		CATEGORY_SKILL_BOOK_CLASS,
		CATEGORY_SKILL_BOOK_PASSIVE,
		CATEGORY_SKILL_BOOK_MISSION,
		
		CATEGORY_SKILL_BOOK_CATEGORY_MAX_NUM,
	};

	enum subcategory_GIFTBOX
	{
		CATEGORY_GIFTBOX_CATEGORY_GENERAL,
		
		CATEGORY_GIFTBOX_NORM,
		CATEGORY_GIFTBOX_SPECIAL,
		
		CATEGORY_GIFTBOX_CATEGORY_MAX_NUM,
	};

	enum subcategory_MINING
	{
		CATEGORY_MINING_CATEGORY_GENERAL,
		
		CATEGORY_MINING_ORES,
		CATEGORY_MINING_GEMS,
		
		CATEGORY_MINING_CATEGORY_MAX_NUM,
	};

	enum subcategory_REFINE
	{
		CATEGORY_REFINE_CATEGORY_GENERAL,
		
		CATEGORY_REFINE_NORM,
		CATEGORY_REFINE_SPECIAL,
		
		CATEGORY_REFINE_CATEGORY_MAX_NUM,
	};

	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//////////////////////////////////////////////

	//Usado para verificar a veracidade dos valores enviados
	struct NSS_CATEGORYS
	{
		int category_id;
		int subcategory_numb;
	};
	
	NSS_CATEGORYS nss_category_cfg[NSS_MAX_NUM] =
	{
		{NSS_GERAL_CATEGORY, 1},
		{NSS_WEAPONS_CATEGORY, WEAPON_CATEGORY_MAX_NUM},
		{NSS_ARMOR_CATEGORY, ARMOR_CATEGORY_MAX_NUM},
		{NSS_COSTUME_CATEGORY, COSTUME_CATEGORY_MAX_NUM},
		{NSS_RINGS_CATEGORY, RINGS_CATEGORY_MAX_NUM},
		{NSS_DRAGON_ALCHEMY_CATEGORY, DRAGON_ALCHEMY_CATEGORY_MAX_NUM,},
		{NSS_CATEGORY_MOUNT, CATEGORY_MOUNT_CATEGORY_MAX_NUM},
		{NSS_CATEGORY_PETS, CATEGORY_PETS_CATEGORY_MAX_NUM},
		{NSS_CATEGORY_NEEDED_ITENS, CATEGORY_NEEDED_ITENS_CATEGORY_MAX_NUM},
		{NSS_CATEGORY_SKILL_BOOK, CATEGORY_SKILL_BOOK_CATEGORY_MAX_NUM},
		{NSS_CATEGORY_GIFTBOX, CATEGORY_GIFTBOX_CATEGORY_MAX_NUM},
		{NSS_CATEGORY_MINING, CATEGORY_MINING_CATEGORY_MAX_NUM},
		{NSS_CATEGORY_REFINE, CATEGORY_REFINE_CATEGORY_MAX_NUM},
	};
	
	//Usado para mostrar os mapas permitidos na procura para membros não premium:
	struct allowedMaps
	{
		DWORD first_empire_map;
		DWORD second_empire_map;
	};
	
	std::map<DWORD, allowedMaps > allowed_norm_search_shop_maps = {
			{	1	,	{1, 3}	}, //Vermelhos
			{	2	,	{21, 23}	}, //Amarelos
			{	3	,	{41, 43}	}, //Azuis
	};
	
	const BYTE allowedMapCount = 6;
	const DWORD premium_maps[allowedMapCount] = {1,3,21,23,41,43};
	
	std::vector<DWORD> allowed_premium_search_shop_maps = {1,3,21,23,41,43};
	
	//Usado para verificar se o item se enquadra no filtro atual
	bool CheckItemFilter(TItemTable *item, int32_t category, int32_t subcategory)
	{
		if (!item)
			return false;
		
		switch (category)
		{
			case NSS_GERAL_CATEGORY: //categoria geral dá sempre true
				return true;

			case NSS_WEAPONS_CATEGORY:
				{
					switch (subcategory)
						{
							case WEAPON_CATEGORY_GENERAL:
								{
									if (item->bType == ITEM_WEAPON)
										return true;
									return false;
								}
							case WEAPON_CATEGORY_SWORD:
								{
									if (item->bType == ITEM_WEAPON && item->bSubType == WEAPON_SWORD)
										return true;
									return false;
								}
							
							case WEAPON_CATEGORY_2_SWORD:
								{
									if (item->bType == ITEM_WEAPON && item->bSubType == WEAPON_TWO_HANDED)
										return true;
									return false;
								}
							
							case WEAPON_CATEGORY_SURA_SWORD:
								{
									if (item->bType == ITEM_WEAPON &&
										item->bSubType == WEAPON_SWORD && (
										!IS_SET(item->dwAntiFlags, ITEM_ANTIFLAG_WARRIOR) &&
										!IS_SET(item->dwAntiFlags, ITEM_ANTIFLAG_ASSASSIN) &&
										!IS_SET(item->dwAntiFlags, ITEM_ANTIFLAG_SHAMAN) &&
										IS_SET(item->dwAntiFlags, ITEM_ANTIFLAG_SURA))
									)
										return true;
									return false;
								}
							
							case WEAPON_CATEGORY_DAGGER:
								{
									if (item->bType == ITEM_WEAPON && item->bSubType == WEAPON_DAGGER)
										return true;
									return false;
								}
							
							case WEAPON_CATEGORY_BOW:
								{
									if (item->bType == ITEM_WEAPON && item->bSubType == WEAPON_BOW)
										return true;
									return false;
								}
							
							case WEAPON_CATEGORY_BELL:
								{
									if (item->bType == ITEM_WEAPON && item->bSubType == WEAPON_BELL)
										return true;
									return false;
								}
							
							case WEAPON_CATEGORY_FAN:
								{
									if (item->bType == ITEM_WEAPON && item->bSubType == WEAPON_FAN)
										return true;
									return false;
								}
							
							case WEAPON_CATEGORY_ARROW:
								{
									if (item->bType == ITEM_WEAPON && (item->bSubType == WEAPON_ARROW))
										return true;
									return false;
								}
							
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_ARMOR_CATEGORY:
				{
					switch (subcategory)
						{
							case ARMOR_CATEGORY_GENERAL:
								{
									if (item->bType == ITEM_ARMOR)
										return true;
									return false;
								}
							
							case ARMOR_CATEGORY_ARMOR:
								{
									if (item->bType == ITEM_ARMOR && item->bSubType == ARMOR_BODY)
										return true;
									return false;
								}
							
							case ARMOR_CATEGORY_HELMET:
								{
									if (item->bType == ITEM_ARMOR && item->bSubType == ARMOR_HEAD)
										return true;
									return false;
								}
							
							case ARMOR_CATEGORY_SHIELD:
								{
									if (item->bType == ITEM_ARMOR && item->bSubType == ARMOR_SHIELD)
										return true;
									return false;
								}
							
							case ARMOR_CATEGORY_NECKLACE:
								{
									if (item->bType == ITEM_ARMOR && item->bSubType == ARMOR_NECK)
										return true;
									return false;
								}
							
							case ARMOR_CATEGORY_BRACELET:
								{
									if (item->bType == ITEM_ARMOR && item->bSubType == ARMOR_WRIST)
										return true;
									return false;
								}
							
							case ARMOR_CATEGORY_EAR_RINGS:
								{
									if (item->bType == ITEM_ARMOR && item->bSubType == ARMOR_EAR)
										return true;
									return false;
								}
							
							case ARMOR_CATEGORY_SHOES:
								{
									if (item->bType == ITEM_ARMOR && item->bSubType == ARMOR_FOOTS)
										return true;
									return false;
								}
							
							case ARMOR_CATEGORY_BELTS:
								{
									if (item->bType == ITEM_BELT)
										return true;
									return false;
								}
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_COSTUME_CATEGORY:
				{
					switch (subcategory)
						{
							case COSTUME_CATEGORY_GENERAL:
								{
									if (item->bType == ITEM_COSTUME && (
										item->bSubType == COSTUME_HAIR ||
										item->bSubType == COSTUME_BODY ||
										item->bSubType == COSTUME_WEAPON ||
										item->bSubType == COSTUME_ACCE))
										return true;
									return false;
								}
							
							case COSTUME_CATEGORY_HAIR_STYLE:
								{
									if (item->bType == ITEM_COSTUME && item->bSubType == COSTUME_HAIR)
										return true;
									return false;
								}
							
							case COSTUME_CATEGORY_COSTUMES:
								{
									if (item->bType == ITEM_COSTUME && item->bSubType == COSTUME_BODY)
										return true;
									return false;
								}
							
							case COSTUME_CATEGORY_WEAPON_SKINS:
								{
									#if defined(__WEAPON_COSTUME_SYSTEM__)
									if (item->bType == ITEM_COSTUME && item->bSubType == COSTUME_WEAPON)
										return true;
									return false;
									#else
									return false;
									#endif
								}
							
							case COSTUME_CATEGORY_ACCE:
								{
									if (item->bType == ITEM_COSTUME && item->bSubType == COSTUME_ACCE)
										return true;
									return false;
								}
							
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_RINGS_CATEGORY:
				{
					switch (subcategory)
						{
							case RINGS_CATEGORY_GENERAL:
								{
									if (item->bType == ITEM_RING)
										return true;
									return false;
								}
							
							case RINGS_CATEGORY_NORMAL:
								{
									if (item->bType != ITEM_RING)
										return false;
									return true;
								}
							
							/*não temos aneis especiais ainda*/
							case RINGS_CATEGORY_SPECIAL:
								{
									return false;
								}
							
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_DRAGON_ALCHEMY_CATEGORY:
				{
					switch (subcategory)
						{
							case DRAGON_ALCHEMY_CATEGORY_GENERAL:
								{
									if (item->bType == ITEM_DS)
										return true;
									return false;
								}
							
							case DRAGON_ALCHEMY_CATEGORY_DIAMOND:
								{
									if (item->bType == ITEM_DS && item->bSubType == DS_SLOT1)
										return true;
									return false;
								}
							
							case DRAGON_ALCHEMY_CATEGORY_ONIX:
								{
									if (item->bType == ITEM_DS && item->bSubType == DS_SLOT6)
										return true;
									return false;
								}
							
							case DRAGON_ALCHEMY_CATEGORY_GRANADA:
								{
									if (item->bType == ITEM_DS && item->bSubType == DS_SLOT5)
										return true;
									return false;
								}
							
							case DRAGON_ALCHEMY_CATEGORY_SAFIRA:
								{
									if (item->bType == ITEM_DS && item->bSubType == DS_SLOT4)
										return true;
									return false;
								}
							
							case DRAGON_ALCHEMY_CATEGORY_JADE:
								{
									if (item->bType == ITEM_DS && item->bSubType == DS_SLOT3)
										return true;
									return false;
								}
							
							case DRAGON_ALCHEMY_CATEGORY_RUBI:
								{
									if (item->bType == ITEM_DS && item->bSubType == DS_SLOT2)
										return true;
									return false;
								}
							
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_CATEGORY_MOUNT:
				{
					switch (subcategory)
						{
							case CATEGORY_MOUNT_CATEGORY_GENERAL:
								{
									if (item->bType == ITEM_COSTUME && item->bSubType == COSTUME_MOUNT)
										return true;
									
									// if (item->bType == ITEM_COSTUME && item->bSubType == ITEM_MOUNT_SKIN)
										// return true;
									
									return false;
								}
							
							case CATEGORY_MOUNT_NORM:
								{
									if (!(item->bType == ITEM_COSTUME && item->bSubType == COSTUME_MOUNT))
										return false;
									
									return true;
								}
							
							/*não temos mounts especiais para já*/
							case CATEGORY_MOUNT_SPECIAL:
								{
									return false;
								}
							
							// case CATEGORY_MOUNT_SKINS:
								// {
									// if (item->bType == ITEM_COSTUME && item->bSubType == ITEM_MOUNT_SKIN)
										// return true;
									// return false;
								// }
							
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_CATEGORY_PETS:
				{
					switch (subcategory)
						{
							case CATEGORY_PETS_CATEGORY_GENERAL:
								{
									// if (item->bType == ITEM_NORMAL_PET)
										// return true;
									
									// if (item->bType == ITEM_COSTUME && item->bSubType == ITEM_PET_SKIN)
										// return true;
									
									std::vector<DWORD> growth_pet_stuff = {55001, 55002, 55003, 55004, 55005, 55010, 55011, 55012, 55013, 55014, 55015, 55016, 55017, 55018, 55019, 55401, 55402, 55403, 55404, 55405, 55406, 55407, 55408, 55409, 55410, 55701, 55702, 55703, 55704, 55705, 55706, 55707, 55708, 55709, 55710, 55711};
									if (std::find(growth_pet_stuff.begin(), growth_pet_stuff.end(), item->dwVnumRange) != growth_pet_stuff.end())
										return true;
									
									return false;
								}
							
							// case CATEGORY_PETS_NORM:
								// {
									// if (!(item->bType == ITEM_NORMAL_PET))
										// return false;
									// return true;
								// }
							
							/*não temos pets especiais para já*/
							case CATEGORY_PETS_SPECIAL:
								{
									return false;
								}
							
							// case CATEGORY_PETS_SKIN:
								// {
									// if (item->bType == ITEM_COSTUME && item->bSubType == ITEM_PET_SKIN)
										// return true;
									// return false;
								// }
							
							case CATEGORY_PETS_EVOLVE_PETS:
								{
									std::vector<DWORD> growth_pet_stuff = {55001, 55002, 55003, 55004, 55005, 55010, 55011, 55012, 55013, 55014, 55015, 55016, 55017, 55018, 55019, 55401, 55402, 55403, 55404, 55405, 55406, 55407, 55408, 55409, 55410, 55701, 55702, 55703, 55704, 55705, 55706, 55707, 55708, 55709, 55710, 55711};
									if (std::find(growth_pet_stuff.begin(), growth_pet_stuff.end(), item->dwVnumRange) == growth_pet_stuff.end())
										return false;
									return true;
								}
							
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_CATEGORY_NEEDED_ITENS:
				{
					switch (subcategory)
						{
							case CATEGORY_NEEDED_ITENS_CATEGORY_GENERAL:
								{
									if (item->bType == ITEM_BLEND)
										return true;
									
									if (item->bType == ITEM_USE && (item->bSubType == USE_CHANGE_ATTRIBUTE || item->bSubType == USE_ADD_ATTRIBUTE || item->bSubType == USE_ADD_ATTRIBUTE2 ||
										item->bSubType == USE_CHANGE_COSTUME_ATTR || item->bSubType == USE_RESET_COSTUME_ATTR)) {
											return true;
									}
									
									std::vector<DWORD> itens = {25040, 70036, 39014, 71032, 70039, 25041, 39008, 39030, 70102, 71107, 91100, 91101, 90022, 90023};
									if (std::find(itens.begin(), itens.end(), item->dwVnumRange) != itens.end())
										return true;

									std::vector<DWORD> item_shop = {91103, 91102, 90031, 90021, 90000, 88023, 88022, 88021, 88020, 86506, 86506, 86505, 86505, 86122, 86122, 86109, 86100, 86100, 80017, 80016, 80016, 80015, 80015, 80014, 80008, 80008, 72325, 71135, 71128, 71128, 71128, 71128, 71128, 71128, 71127, 71127, 71127, 71127, 71127, 71127, 71126, 71126, 71126, 71126, 71126, 71126, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71055, 71055, 71035, 53013, 53013, 53012, 53012, 53011, 53011, 53010, 53010, 53010, 53010, 45359, 45359, 45359, 45359, 45358, 45358, 45358, 45358, 45357, 45357, 45357, 45356, 45356, 45356, 45293, 45293, 45293, 45293, 45292, 45292, 45292, 45292, 45291, 45291, 45291, 45291, 45290, 45290, 45290, 45290, 41682, 41681, 41681, 41681, 41680, 41680, 41680, 41679, 41679, 41679, 41678, 41678, 41678, 41603, 41603, 41603, 41603, 41602, 41602, 41602, 41602, 41601, 41601, 41601, 41601, 41600, 41600, 41600, 41600, 41600, 41600, 40106, 40106, 40106, 40106, 40105, 40105, 40105, 40105, 40104, 40104, 40104, 40104, 40103, 40103, 40103, 40103, 40103, 40103, 40103, 40103, 40102, 40102, 40102, 40102, 40102, 40102, 40102, 40102, 40101, 40101, 40101, 40101, 40101, 40101, 40101, 40101, 39023, 30033, 30032, 30031, 30030, 30030};
									if (std::find(item_shop.begin(), item_shop.end(), item->dwVnumRange) != item_shop.end())
										return true;
									
									if (item->bType == ITEM_METIN)
										return true;
									
									return false;
								}
							case CATEGORY_NEEDED_ITENS_ORV_DD:
								{
									if (item->bType == ITEM_BLEND)
										return true;
									return false;
								}
							
							case CATEGORY_NEEDED_ITENS_CHANGERS:
								{
									if (item->bType == ITEM_USE && (item->bSubType == USE_CHANGE_ATTRIBUTE || item->bSubType == USE_ADD_ATTRIBUTE || item->bSubType == USE_ADD_ATTRIBUTE2 ||
										item->bSubType == USE_CHANGE_COSTUME_ATTR || item->bSubType == USE_RESET_COSTUME_ATTR)) {
											return true;
									}
									
									return false;
								}
							case CATEGORY_NEEDED_ITENS_MELHORAMENTO:
								{
									std::vector<DWORD> itens = {25040, 70036, 39014, 71032, 70039, 25041, 39008, 39030, 70102, 71107, 91100, 91101, 90022, 90023};
									if (std::find(itens.begin(), itens.end(), item->dwVnumRange) == itens.end())
										return false;
									
									return true;
								}
							
							case CATEGORY_NEEDED_ITENS_SHOP_ITENS:
								{
									std::vector<DWORD> item_shop = {91103, 91102, 90031, 90021, 90000, 88023, 88022, 88021, 88020, 86506, 86506, 86505, 86505, 86122, 86122, 86109, 86100, 86100, 80017, 80016, 80016, 80015, 80015, 80014, 80008, 80008, 72325, 71135, 71128, 71128, 71128, 71128, 71128, 71128, 71127, 71127, 71127, 71127, 71127, 71127, 71126, 71126, 71126, 71126, 71126, 71126, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71125, 71055, 71055, 71035, 53013, 53013, 53012, 53012, 53011, 53011, 53010, 53010, 53010, 53010, 45359, 45359, 45359, 45359, 45358, 45358, 45358, 45358, 45357, 45357, 45357, 45356, 45356, 45356, 45293, 45293, 45293, 45293, 45292, 45292, 45292, 45292, 45291, 45291, 45291, 45291, 45290, 45290, 45290, 45290, 41682, 41681, 41681, 41681, 41680, 41680, 41680, 41679, 41679, 41679, 41678, 41678, 41678, 41603, 41603, 41603, 41603, 41602, 41602, 41602, 41602, 41601, 41601, 41601, 41601, 41600, 41600, 41600, 41600, 41600, 41600, 40106, 40106, 40106, 40106, 40105, 40105, 40105, 40105, 40104, 40104, 40104, 40104, 40103, 40103, 40103, 40103, 40103, 40103, 40103, 40103, 40102, 40102, 40102, 40102, 40102, 40102, 40102, 40102, 40101, 40101, 40101, 40101, 40101, 40101, 40101, 40101, 39023, 30033, 30032, 30031, 30030, 30030};
									
									if (std::find(item_shop.begin(), item_shop.end(), item->dwVnumRange) == item_shop.end())
										return false;
									
									return true;
								}
							case CATEGORY_NEEDED_ITENS_STONES:
								{
									if (item->bType == ITEM_METIN)
										return true;
									return false;
								}
							
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_CATEGORY_SKILL_BOOK:
				{
					switch (subcategory)
						{
							case CATEGORY_SKILL_BOOK_CATEGORY_GENERAL:
								{
									std::vector<DWORD> stuff_book_related = {90022, 90023, 39030, 71094, 76034, 71001, 72310, 76026, 39008, 70102, 91100, 91101};
									if (std::find(stuff_book_related.begin(), stuff_book_related.end(), item->dwVnumRange) != stuff_book_related.end())
										return true;
									
									if (item->bType == ITEM_SKILLBOOK || item->bType == ITEM_SKILLFORGET)
										return true;
									
									// if (item->bType == ITEM_SKILLBOOK_P)
										// return true;
									
									std::vector<DWORD> book_missions = {50307, 50308, 50309};
									if (std::find(book_missions.begin(), book_missions.end(), item->dwVnumRange) != book_missions.end())
										return true;
									
									return false;
								}
							
							case CATEGORY_SKILL_BOOK_CLASS:
								{
									if (item->bType == ITEM_SKILLBOOK || item->bType == ITEM_SKILLFORGET)
										return true;
									return false;
								}
							// case CATEGORY_SKILL_BOOK_PASSIVE:
								// {
									// if (item->bType == ITEM_SKILLBOOK_P)
										// return true;
									// return false;
								// }
							case CATEGORY_SKILL_BOOK_MISSION:
								{
									std::vector<DWORD> book_missions = {50307, 50308, 50309};
									if (std::find(book_missions.begin(), book_missions.end(), item->dwVnumRange) != book_missions.end())
										return true;
									
									return false;
								}
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_CATEGORY_GIFTBOX:
				{
					switch (subcategory)
						{
							case CATEGORY_GIFTBOX_CATEGORY_GENERAL:
								{
									std::vector<DWORD> not_allowed_giftbox = {50187, 50188, 50189, 50190, 50191, 50192, 50193, 50194, 50195, 50196};
									if (std::find(not_allowed_giftbox.begin(), not_allowed_giftbox.end(), item->dwVnumRange) != not_allowed_giftbox.end())
										return false;
									
									if (item->bType == ITEM_GIFTBOX)
										return true;
									
									return false;
								}
							
							case CATEGORY_GIFTBOX_NORM:
								{
									std::vector<DWORD> not_allowed_giftbox = {50187, 50188, 50189, 50190, 50191, 50192, 50193, 50194, 50195, 50196};
									if (std::find(not_allowed_giftbox.begin(), not_allowed_giftbox.end(), item->dwVnumRange) != not_allowed_giftbox.end())
										return false;
									
									if (item->bType == ITEM_GIFTBOX)
										return true;
									
									return false;
								}
							
							/*ainda não temos cofres especiais*/
							case CATEGORY_GIFTBOX_SPECIAL:
								{
									return false;
								}
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_CATEGORY_MINING:
				{
					switch (subcategory)
						{
							case CATEGORY_MINING_CATEGORY_GENERAL:
								{
									std::vector<DWORD> ores = {50604, 50605, 50606, 50607, 50608, 50609, 50610, 50611, 50612, 50613, 50614, 50615, 50616, 50617, 50618, 50619};
									if (std::find(ores.begin(), ores.end(), item->dwVnumRange) != ores.end())
										return true;
									
									if (item->bType == ITEM_USE && (item->bSubType == USE_PUT_INTO_ACCESSORY_SOCKET || item->bSubType == USE_ADD_ACCESSORY_SOCKET))
										return true;
									
									if (item->bType == ITEM_PICK)
										return true;
									
									return false;
								}
							
							case CATEGORY_MINING_ORES:
								{
									std::vector<DWORD> ores = {50604, 50605, 50606, 50607, 50608, 50609, 50610, 50611, 50612, 50613, 50614, 50615, 50616, 50617, 50618, 50619};
									if (std::find(ores.begin(), ores.end(), item->dwVnumRange) != ores.end())
										return true;
									
									return false;
								}
							case CATEGORY_MINING_GEMS:
								{
									if (item->bType == ITEM_USE && (item->bSubType == USE_PUT_INTO_ACCESSORY_SOCKET || item->bSubType == USE_ADD_ACCESSORY_SOCKET))
										return true;
									
									return false;
								}
							
							default:
								return false;
						}
					break;
				}
				break;
			
			case NSS_CATEGORY_REFINE:
				{
					switch (subcategory)
						{
							case CATEGORY_REFINE_CATEGORY_GENERAL:
								{
									std::vector<DWORD> normal_refine = {30003, 30004, 30005, 30006, 30007, 30008, 30009, 30010, 30011, 30015, 30016, 30017, 30018, 30019, 30020, 30021, 30022, 30023, 30025, 30027, 30028, 30034, 30035, 30037, 30038, 30039, 30040, 30041, 30042, 30045, 30046, 30047, 30048, 30049, 30050, 30051, 30052, 30053, 30055, 30056, 30057, 30058, 30059, 30060, 30061, 30067, 30069, 30070, 30071, 30072, 30073, 30074, 30075, 30076, 30077, 30078, 30079, 30080, 30081, 30082, 30083, 30084, 30085, 30086, 30087, 30088, 30089, 30090, 30091, 30092, 30192, 30193, 30194, 30195, 30196, 30197, 30198, 30199, 30500, 30501, 30502, 30503, 30504, 30505, 30506, 30507, 30508, 30509, 30510, 30511, 30512, 30513, 30514, 30515, 30516, 30517, 30518, 30519, 30520, 30521, 30522, 30523, 30524, 30525, 30600, 30601, 30602, 30603, 30604, 30605, 30606, 30607, 30608, 30609, 30610, 30611, 30612, 30614, 30615, 30616, 30617, 30618, 30619, 27799, 27992, 27993, 27994, 27987, 33031, 33030, 33029, 30630, 30629, 30628, 30627, 30626, 30625, 30624, 30623, 70097, 70096, 70095, 70094, 70093, 70092, 70091, 70090, 70089, 70088, 70087, 70086, 85000, 70254, 70253, 70252, 70251, 51001, 50160, 50161, 50162, 50163, 50164, 50165, 50166, 50167, 50168, 50169, 50170, 50171, 50172, 50173, 50174, 50175, 50176, 50177, 50178, 50179, 30622, 30621, 30620, 30252, 30251, 30228, 30227, 30226, 30225, 30224, 30223, 30222, 30221, 30220, 30168, 30167, 30166, 30165, 27990, 71123, 71129, 39072, 39077, 39073, 39078, 39074, 39079, 39075, 39080, 39076, 40001, 90033, 90034, 90035, 90036, 90037, 90038, 31006, 31066, 30180, 30542, 30543, 30544, 30545, 30546, 30547, 30548, 30549, 30550, 30551, 30552, 30553, 30554, 30555, 30556, 30557, 30558, 30559, 30560, 30561, 30562, 30563, 30564, 30565, 30566, 30567, 30568, 30569, 30570, 30571, 30572, 30573, 30574, 30575, 30576, 30577, 30578, 30579, 30580, 30581, 30582, 30583, 30584, 30585, 30586, 31062, 31026, 31043, 31057, 30181, 30182, 30183, 31090, 31005, 30184, 30185, 30186, 30187, 30188, 71022, 71023, 31196, 31197, 31198, 31204, 31205, 31206, 31209, 31210, 31211, 30000, 30001, 30002};
									if (std::find(normal_refine.begin(), normal_refine.end(), item->dwVnumRange) != normal_refine.end())
										return true;
									
									std::vector<DWORD> special_refine = {31005, 31006, 71129, 71123, 31090, 30183, 30184, 30185, 30186, 30187, 30188, 30192, 30181, 30182, 31035};
									if (std::find(special_refine.begin(), special_refine.end(), item->dwVnumRange) != special_refine.end())
										return true;
									
									return false;
								}
							
							case CATEGORY_REFINE_NORM:
								{
									std::vector<DWORD> normal_refine = {30003, 30004, 30005, 30006, 30007, 30008, 30009, 30010, 30011, 30015, 30016, 30017, 30018, 30019, 30020, 30021, 30022, 30023, 30025, 30027, 30028, 30034, 30035, 30037, 30038, 30039, 30040, 30041, 30042, 30045, 30046, 30047, 30048, 30049, 30050, 30051, 30052, 30053, 30055, 30056, 30057, 30058, 30059, 30060, 30061, 30067, 30069, 30070, 30071, 30072, 30073, 30074, 30075, 30076, 30077, 30078, 30079, 30080, 30081, 30082, 30083, 30084, 30085, 30086, 30087, 30088, 30089, 30090, 30091, 30092, 30192, 30193, 30194, 30195, 30196, 30197, 30198, 30199, 30500, 30501, 30502, 30503, 30504, 30505, 30506, 30507, 30508, 30509, 30510, 30511, 30512, 30513, 30514, 30515, 30516, 30517, 30518, 30519, 30520, 30521, 30522, 30523, 30524, 30525, 30600, 30601, 30602, 30603, 30604, 30605, 30606, 30607, 30608, 30609, 30610, 30611, 30612, 30614, 30615, 30616, 30617, 30618, 30619, 27799, 27992, 27993, 27994, 27987, 33031, 33030, 33029, 30630, 30629, 30628, 30627, 30626, 30625, 30624, 30623, 70097, 70096, 70095, 70094, 70093, 70092, 70091, 70090, 70089, 70088, 70087, 70086, 85000, 70254, 70253, 70252, 70251, 51001, 50160, 50161, 50162, 50163, 50164, 50165, 50166, 50167, 50168, 50169, 50170, 50171, 50172, 50173, 50174, 50175, 50176, 50177, 50178, 50179, 30622, 30621, 30620, 30252, 30251, 30228, 30227, 30226, 30225, 30224, 30223, 30222, 30221, 30220, 30168, 30167, 30166, 30165, 27990, 71123, 71129, 39072, 39077, 39073, 39078, 39074, 39079, 39075, 39080, 39076, 40001, 90033, 90034, 90035, 90036, 90037, 90038, 31006, 31066, 30180, 30542, 30543, 30544, 30545, 30546, 30547, 30548, 30549, 30550, 30551, 30552, 30553, 30554, 30555, 30556, 30557, 30558, 30559, 30560, 30561, 30562, 30563, 30564, 30565, 30566, 30567, 30568, 30569, 30570, 30571, 30572, 30573, 30574, 30575, 30576, 30577, 30578, 30579, 30580, 30581, 30582, 30583, 30584, 30585, 30586, 31062, 31026, 31043, 31057, 30181, 30182, 30183, 31090, 31005, 30184, 30185, 30186, 30187, 30188, 71022, 71023, 31196, 31197, 31198, 31204, 31205, 31206, 31209, 31210, 31211, 30000, 30001, 30002};
									if (std::find(normal_refine.begin(), normal_refine.end(), item->dwVnumRange) != normal_refine.end())
										return true;
									
									return false;
								}
							
							case CATEGORY_REFINE_SPECIAL:
								{
									std::vector<DWORD> special_refine = {31005, 31006, 71129, 71123, 31090, 30183, 30184, 30185, 30186, 30187, 30188, 30192, 30181, 30182, 31035};
									if (std::find(special_refine.begin(), special_refine.end(), item->dwVnumRange) != special_refine.end())
										return true;
									
									return false;
								}
							
							default:
								return false;
						}
					break;
				}
				break;
			
			default:
				return false;
		}
	}
};


#endif