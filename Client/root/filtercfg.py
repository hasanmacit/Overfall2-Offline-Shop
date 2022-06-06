import localeInfo

CATEGORY_BUTTONS = {
	0 : {
		localeInfo.GENERAL_CATEGORY : (("None", (10, 9)) , ["None", "None"]), #Todos os itens
	},
	
	1 : {
		localeInfo.WEAPONS_CATEGORY : (("sword", (10, 9)), #Armas
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.WEAPON_CATEGORY_SWORD,
					localeInfo.WEAPON_CATEGORY_2_SWORD,
					localeInfo.WEAPON_CATEGORY_SURA_SWORD,
					localeInfo.WEAPON_CATEGORY_DAGGER,
					localeInfo.WEAPON_CATEGORY_BOW,
					localeInfo.WEAPON_CATEGORY_BELL,
					localeInfo.WEAPON_CATEGORY_FAN,
					localeInfo.WEAPON_CATEGORY_ARROW,
				]),
		},

	2 : {
		localeInfo.ARMOR_CATEGORY : (("helmet", (10, 9)), #Equipamentos
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.ARMOR_CATEGORY_ARMOR,
					localeInfo.ARMOR_CATEGORY_HELMET,
					localeInfo.ARMOR_CATEGORY_SHIELD,
					localeInfo.ARMOR_CATEGORY_NECKLACE,
					localeInfo.ARMOR_CATEGORY_BRACELET,
					localeInfo.ARMOR_CATEGORY_EAR_RINGS,
					localeInfo.ARMOR_CATEGORY_SHOES,
					localeInfo.ARMOR_CATEGORY_BELTS,
					localeInfo.ARMOR_CATEGORY_PENDANT,
				]),
		},
	
	3 : {
		localeInfo.COSTUME_CATEGORY : (("mask", (10, 12)), #Disfarces
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.COSTUME_CATEGORY_HAIR_STYLE,
					localeInfo.COSTUME_CATEGORY_COSTUMES,
					localeInfo.COSTUME_CATEGORY_WEAPON_SKINS,
					localeInfo.COSTUME_CATEGORY_ACCE,
				]),
		},
	
	4 : {
		localeInfo.RINGS_CATEGORY : (("ring", (10, 7)), #Anéis
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.RINGS_CATEGORY_NORMAL,
					localeInfo.RINGS_CATEGORY_SPECIAL,
				]),
		},
	
	5 : {
		localeInfo.DRAGON_ALCHEMY_CATEGORY : (("alquimia", (10, 9)), #Alquimia
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.DRAGON_ALCHEMY_CATEGORY_DIAMOND,
					localeInfo.DRAGON_ALCHEMY_CATEGORY_ONIX,
					localeInfo.DRAGON_ALCHEMY_CATEGORY_GRANADA,
					localeInfo.DRAGON_ALCHEMY_CATEGORY_SAFIRA,
					localeInfo.DRAGON_ALCHEMY_CATEGORY_JADE,
					localeInfo.DRAGON_ALCHEMY_CATEGORY_RUBI,
				]),
		},
	
	6 : {
		localeInfo.CATEGORY_MOUNT : (("cavalo", (10, 9)), #Montadas
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.CATEGORY_MOUNT_NORM,
					localeInfo.CATEGORY_MOUNT_SPECIAL,
					localeInfo.CATEGORY_MOUNT_SKINS,
				]),
		},
	
	7 : {
		localeInfo.CATEGORY_PETS : (("pet", (10, 9)), #Pets
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.CATEGORY_PETS_NORM,
					localeInfo.CATEGORY_PETS_SPECIAL,
					localeInfo.CATEGORY_PETS_SKIN,
					localeInfo.CATEGORY_PETS_EVOLVE_PETS,
				]),
		},
	
	8 : {
		localeInfo.CATEGORY_NEEDED_ITENS : (("helpfulitens", (10, 9)), #Itens Úteis
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.CATEGORY_NEEDED_ITENS_ORV_DD,
					localeInfo.CATEGORY_NEEDED_ITENS_CHANGERS,
					localeInfo.CATEGORY_NEEDED_ITENS_MELHORAMENTO,
					localeInfo.CATEGORY_NEEDED_ITENS_SHOP_ITENS,
					localeInfo.CATEGORY_NEEDED_ITENS_STONES,
				]),
		},
	
	9 : {
		localeInfo.CATEGORY_SKILL_BOOK : (("books", (10, 9)), #Livros de habilidades
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.CATEGORY_SKILL_BOOK_CLASS,
					localeInfo.CATEGORY_SKILL_BOOK_PASSIVE,
					localeInfo.CATEGORY_SKILL_BOOK_MISSION,
				]),
		},
	
	10 : {
		localeInfo.CATEGORY_GIFTBOX : (("chest", (10, 9)), #Cofres
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.CATEGORY_GIFTBOX_NORM,
					localeInfo.CATEGORY_GIFTBOX_SPECIAL,
				]),
		},
	
	11 : {
		localeInfo.CATEGORY_MINING : (("mineiros", (10, 9)), #Minérios
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.CATEGORY_MINING_ORES,
					localeInfo.CATEGORY_MINING_GEMS,
				]),
		},
	
	12 : {
		localeInfo.CATEGORY_REFINE : (("refines", (10, 9)), #Refines
				[
					localeInfo.CATEGORY_SEARCH_ALL,
					
					localeInfo.CATEGORY_REFINE_NORM,
					localeInfo.CATEGORY_REFINE_SPECIAL,
				]),
		},
},
