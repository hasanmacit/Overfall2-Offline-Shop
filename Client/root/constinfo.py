#importlar yoksa ekle

import app
import localeInfo
import re
import math

#importların altına ekle

if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
	CREATE_PRIVATE_SHOP_EFFECT = (False,app.GetTime())

if app.ENABLE_OFFLINE_SHOP_SYSTEM:
	OFFLINE_SHOP_SALES = []
	OFFLINE_SHOP_ITEM_PRICE_DIC = {}

#arat

def GET_FOG_LEVEL_INDEX():

#altına ekle

if app.ENABLE_OFFLINE_SHOP_SYSTEM:
	def MapNameByIndex(idx):

		MAP_INDEX_DICT = {
			0 : localeInfo.MAP_NONE,
			1 : localeInfo.MAP_A1,
			21 : localeInfo.MAP_B1,
			41 : localeInfo.MAP_C1,
			61 : localeInfo.MAP_N_SNOWM_01,
			62 : localeInfo.MAP_N_FLAME_01,
			63 : localeInfo.MAP_N_DESERT_01,
			64 : localeInfo.MAP_N_THREEWAY,
			65 : localeInfo.MAP_MILGYO,
			66 : localeInfo.MAP_DEVILTOWER1,
			72 : localeInfo.MAP_SKIPIA_DUNGEON_01,
			73 : localeInfo.MAP_SKIPIA_DUNGEON_02,
			208 : localeInfo.MAP_SKIPIA_DUNGEON_BOSS,
			216 : localeInfo.MAP_DEVILCATACOMB,
			217 : localeInfo.MAP_SPIDERDUNGEON_03,
			321 : localeInfo.MAP_DAWNMIST_DUNGEON_01,
			322 : localeInfo.MAP_MT_TH_DUNGEON_01,
			351 : localeInfo.MAP_N_FLAME_DUNGEON_01,
			352 : localeInfo.MAP_N_SNOW_DUNGEON_01,
			
			109 : "Maymun Zindanı",
			357 : "Ork Zindanı",
			30 : "Prag mağarası",
			57 : "Ejderha Mağarası",
			13 : "Devil's Catacomb Zindanı",
			56 : "Ganesha Harabeleri",
			364 : "Sfenks'in Mezarı",
			
		}

		if idx in MAP_INDEX_DICT:
			return MAP_INDEX_DICT[idx]
		else:
			return MAP_INDEX_DICT[0]

if app.ENABLE_OFFLINE_SHOP_SYSTEM:
	def SetOfflineShopItemPrice(itemVNum, itemPrice, itemCount):
		# if ExistSavedItemPrice(itemVNum):
			# return
		
		real_item_price = int(math.ceil(itemPrice/itemCount)) #Arrendonda sempre para o valor superior
		OFFLINE_SHOP_ITEM_PRICE_DIC[int(itemVNum)] = real_item_price #preco por unidade

	def GetOfflineShopItemPrice(itemVNum, itemCount):
		try:
			return long(OFFLINE_SHOP_ITEM_PRICE_DIC[itemVNum] * itemCount)
		except KeyError:
			return 0
	
	def ExistSavedItemPrice(itemVNum):
		return OFFLINE_SHOP_ITEM_PRICE_DIC.has_key(int(itemVNum))

#en alta ekle

def ConvertMoneyText(text, powers = dict(k = 10**3, m = 10**6, b = 10**9)):
	match = re.search(r'(\d+)({:s}+)?'.format('+|'.join(powers.keys())), text.lower(), re.I)
	if match:
		moneyValue, suffixName = match.groups()
		moneyValue = int(moneyValue)
		if not suffixName:
			return moneyValue

		return moneyValue * (powers[suffixName[0]] ** len(suffixName))

	return 0

