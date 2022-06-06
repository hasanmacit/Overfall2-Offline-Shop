import app
import player
import net
import chr
import background
import chat
import item
import privateShopSearch
import shop
import ui
import grp
import uiCommon
import localeInfo
from _weakref import proxy

GOLD_MAX = 10000000000

class PrivateShopSeachWindow(ui.ScriptWindow):
	MAX_LINE_COUNT = 10
	MAX_CHAR_LEVEL = 120
	CLICK_LIMIT_TIME = 3
	PAGE_BUTTON_MAX_SIZE = 9
	PAGE_BUTTON_NUMBER_SIZE = 5
	PAGE1_MAX_SIZE = 50
	
	SPECIAL_TITLE_COLOR = 0xff4E3D30

	if app.ENABLE_WOLFMAN_CHARACTER:
		JOB_MAX_COUNT = 5
		JOB_NAME_DIC = {
			0 : localeInfo.JOB_WARRIOR,
			1 : localeInfo.JOB_ASSASSIN,
			2 : localeInfo.JOB_SURA,
			3 : localeInfo.JOB_SHAMAN,
			4 : localeInfo.JOB_WOLFMAN,
		}
	else:
		JOB_MAX_COUNT = 4
		JOB_NAME_DIC = {
			0 : localeInfo.JOB_WARRIOR,
			1 : localeInfo.JOB_ASSASSIN,
			2 : localeInfo.JOB_SURA,
			3 : localeInfo.JOB_SHAMAN,
		}

	### SubTypes
	WEAPON_SUBTYPE_DIC = {
		0 : {
			item.WEAPON_SWORD : localeInfo.CATEGORY_WEAPON_WEAPON_SWORD,
			item.WEAPON_TWO_HANDED : localeInfo.CATEGORY_WEAPON_WEAPON_TWO_HANDED,
		},
		1 : {
			item.WEAPON_SWORD : localeInfo.CATEGORY_WEAPON_WEAPON_SWORD,
			item.WEAPON_DAGGER : localeInfo.CATEGORY_WEAPON_WEAPON_DAGGER,
			item.WEAPON_BOW : localeInfo.CATEGORY_WEAPON_WEAPON_BOW,
			item.WEAPON_ARROW : localeInfo.CATEGORY_WEAPON_WEAPON_ARROW,
			# item.WEAPON_QUIVER : localeInfo.CATEGORY_WEAPON_WEAPON_QUIVER,
		},
		2 : {
			item.WEAPON_SWORD : localeInfo.CATEGORY_WEAPON_WEAPON_SWORD,
		},
		3 : {
			item.WEAPON_BELL : localeInfo.CATEGORY_WEAPON_WEAPON_BELL,
			item.WEAPON_FAN : localeInfo.CATEGORY_WEAPON_WEAPON_FAN,
		},
	}

	ARMOR_SUBTYPE_DIC = {
		item.ARMOR_BODY : localeInfo.CATEGORY_ARMOR_ARMOR_BODY,
		item.ARMOR_HEAD : localeInfo.CATEGORY_ARMOR_ARMOR_HEAD,
		item.ARMOR_SHIELD : localeInfo.CATEGORY_ARMOR_ARMOR_SHIELD,
		item.ARMOR_WRIST : localeInfo.CATEGORY_JEWELRY_ARMOR_WRIST,
		item.ARMOR_FOOTS : localeInfo.CATEGORY_JEWELRY_ARMOR_FOOTS,
		item.ARMOR_NECK : localeInfo.CATEGORY_JEWELRY_ARMOR_NECK,
		item.ARMOR_EAR : localeInfo.CATEGORY_JEWELRY_ARMOR_EAR,
	}
	# if app.ENABLE_PENDANT:
		# ARMOR_SUBTYPE_DIC[item.ARMOR_PENDANT] = localeInfo.CATEGORY_JEWELRY_ARMOR_PENDANT

	USE_SUBTYPE_DIC = {
		item.USE_POTION			: localeInfo.PRIVATESHOPSEARCH_POTION,
		item.USE_TUNING			: localeInfo.PRIVATESHOPSEARCH_TUNING,
		item.USE_ABILITY_UP		: localeInfo.PRIVATESHOPSEARCH_ABLITY_POTION,
		item.USE_POTION_NODELAY	: localeInfo.PRIVATESHOPSEARCH_NODELAY_POTION,
		item.USE_CLEAR			: localeInfo.PRIVATESHOPSEARCH_CLEAR_POTION,
		item.USE_DETACHMENT		: localeInfo.PRIVATESHOPSEARCH_DETACHMENT,
	}

	MATERIAL_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_MATERIAL,
	}

	METIN_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_METIN,
	}

	FISH_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_FISH,
	}

	BELT_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_BELT,
	}

	RESOURCE_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_RESOURCE,
	}

	ROD_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_ROD,
	}

	UNIQUE_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_UNIQUE,
	}

	SKILLBOOK_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_SKILLBOOK,
	}

	QUEST_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_QUEST,
	}

	TREASUREBOX_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_TREASUREBOX,
	}

	PICK_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_PICK,
	}

	BLEND_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_BLEND,
	}

	COSTUME_SUBTYPE_DIC = {
		item.COSTUME_TYPE_BODY : localeInfo.CATEGORY_COSTUMES_COSTUME_BODY,
		item.COSTUME_TYPE_HAIR : localeInfo.CATEGORY_COSTUMES_COSTUME_HAIR,
		item.COSTUME_TYPE_MOUNT : localeInfo.CATEGORY_COSTUMES_ETC,
		item.COSTUME_TYPE_ACCE : localeInfo.CATEGORY_COSTUMES_SASH,
		item.COSTUME_TYPE_WEAPON : localeInfo.CATEGORY_COSTUMES_COSTUME_WEAPON,
	}

	DS_SUBTYPE_DIC = {
		item.DRAGON_STONE_DRAGON_DIAMOND : localeInfo.CATEGORY_DRAGON_STONE_DRAGON_DIAMOND,
		item.DRAGON_STONE_DRAGON_RUBY : localeInfo.CATEGORY_DRAGON_STONE_DRAGON_RUBY,
		item.DRAGON_STONE_DRAGON_JADE : localeInfo.CATEGORY_DRAGON_STONE_DRAGON_JADE,
		item.DRAGON_STONE_DRAGON_SAPPHIRE : localeInfo.CATEGORY_DRAGON_STONE_DRAGON_SAPPHIRE,
		item.DRAGON_STONE_DRAGON_GARNET : localeInfo.CATEGORY_DRAGON_STONE_DRAGON_GARNET,
		item.DRAGON_STONE_DRAGON_ONYX : localeInfo.CATEGORY_DRAGON_STONE_DRAGON_ONYX,
	}

	SPECIAL_SUBTYPE_DIC = {
		0 : localeInfo.PRIVATESHOPSEARCH_SPECIAL,
	}

	## Types
	ITEM_TYPE_DIC = {
		item.ITEM_TYPE_WEAPON		: localeInfo.PRIVATESHOPSEARCH_WEAPON,
		item.ITEM_TYPE_ARMOR		: localeInfo.PRIVATESHOPSEARCH_ARMOR,
		item.ITEM_TYPE_USE			: localeInfo.PRIVATESHOPSEARCH_USEITEM,
		item.ITEM_TYPE_MATERIAL		: localeInfo.PRIVATESHOPSEARCH_MATERIAL,
		item.ITEM_TYPE_METIN		: localeInfo.PRIVATESHOPSEARCH_METIN,
		item.ITEM_TYPE_FISH			: localeInfo.PRIVATESHOPSEARCH_FISH,
		item.ITEM_TYPE_BELT			: localeInfo.PRIVATESHOPSEARCH_BELT,
		item.ITEM_TYPE_RESOURCE		: localeInfo.PRIVATESHOPSEARCH_RESOURCE,
		item.ITEM_TYPE_ROD			: localeInfo.PRIVATESHOPSEARCH_ROD,
		item.ITEM_TYPE_UNIQUE		: localeInfo.PRIVATESHOPSEARCH_UNIQUE,
		item.ITEM_TYPE_SKILLBOOK	: localeInfo.PRIVATESHOPSEARCH_SKILLBOOK,
		item.ITEM_TYPE_QUEST		: localeInfo.PRIVATESHOPSEARCH_QUEST,
		item.ITEM_TYPE_TREASURE_BOX	: localeInfo.PRIVATESHOPSEARCH_TREASUREBOX,
		item.ITEM_TYPE_PICK			: localeInfo.PRIVATESHOPSEARCH_PICK,
		item.ITEM_TYPE_BLEND		: localeInfo.PRIVATESHOPSEARCH_BLEND,
		item.ITEM_TYPE_COSTUME		: localeInfo.PRIVATESHOPSEARCH_COSTUME,
		item.ITEM_TYPE_DS			: localeInfo.PRIVATESHOPSEARCH_DS,
		item.ITEM_TYPE_SPECIAL		: localeInfo.PRIVATESHOPSEARCH_SPECIAL,
	}

	ITEM_SUBTYPE_DICS = {
		item.ITEM_TYPE_WEAPON		: WEAPON_SUBTYPE_DIC,
		item.ITEM_TYPE_ARMOR		: ARMOR_SUBTYPE_DIC,
		item.ITEM_TYPE_USE			: USE_SUBTYPE_DIC,
		item.ITEM_TYPE_MATERIAL		: MATERIAL_SUBTYPE_DIC,
		item.ITEM_TYPE_METIN		: METIN_SUBTYPE_DIC,
		item.ITEM_TYPE_FISH			: FISH_SUBTYPE_DIC,
		item.ITEM_TYPE_BELT			: BELT_SUBTYPE_DIC,
		item.ITEM_TYPE_RESOURCE		: RESOURCE_SUBTYPE_DIC,
		item.ITEM_TYPE_ROD			: ROD_SUBTYPE_DIC,
		item.ITEM_TYPE_UNIQUE		: UNIQUE_SUBTYPE_DIC,
		item.ITEM_TYPE_SKILLBOOK	: SKILLBOOK_SUBTYPE_DIC,
		item.ITEM_TYPE_QUEST		: QUEST_SUBTYPE_DIC,
		item.ITEM_TYPE_TREASURE_BOX	: TREASUREBOX_SUBTYPE_DIC,
		item.ITEM_TYPE_PICK			: PICK_SUBTYPE_DIC,
		item.ITEM_TYPE_BLEND		: BLEND_SUBTYPE_DIC,
		item.ITEM_TYPE_COSTUME		: COSTUME_SUBTYPE_DIC,
		item.ITEM_TYPE_DS			: DS_SUBTYPE_DIC,
		item.ITEM_TYPE_SPECIAL		: SPECIAL_SUBTYPE_DIC,
	}

	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.isLoaded = 0

		self.saveJobSelectNumber = 0
		self.saveItemTypeSelectNumber = item.ITEM_TYPE_WEAPON
		self.saveItemSubTypeSelectNumber = 0
		self.minLevelValue = 0
		self.maxLevelValue = 0
		self.minRefineValue = 0
		self.maxRefineValue = 0
		self.minGoldValue = 0
		self.maxGoldValue = 0
		self.itemNameValue = None
		self.searchButton = None
		self.buyButton = None

		self.searchClickTime = 0.0
		self.buyClickTime = 0.0

		self.listSlotCount = 0
		self.selectItemRealIndex = -1
		self.selectItemIndex = -1

		self.serchItemSlotList = {}
		self.itemSlotButtonList = {}
		self.pageButtonList = {}

		self.nowPageNumber = 1
		self.plusPageNumber = 1
		self.pageCount = 0
		self.bigPageCount = 1

		self.isCashItem = 0
		self.popup = None

	def __del__(self):
		ui.ScriptWindow.__del__(self)

		self.itemNameValue = None
		self.buyButton = None
		self.searchButton = None

		self.serchItemSlotList = {}
		self.itemSlotButtonList = {}
		self.pageButtonList = {}

		self.popup = None

	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/PrivateShopSearchDialog.py")
		except:
			import exception
			exception.Abort("PrivateShopSeachWindow.__LoadWindow.UIScript/PrivateShopSearchDialog.py")

		try:
			self.GetChild("board").SetCloseEvent(ui.__mem_func__(self.Close))
			self.searchButton = self.GetChild("SearchButton")
			self.searchButton.SetEvent(ui.__mem_func__(self.Search))
			self.buyButton = self.GetChild("BuyButton")
			self.buyButton.SetEvent(ui.__mem_func__(self.Buy))

			self.itemNameValue = self.GetChild("ItemNameValue")
			self.itemNameValue.SetEscapeEvent(ui.__mem_func__(self.Close))

			self.minLevelValue = self.GetChild("minLevelValue")
			self.minLevelValue.SetEscapeEvent(ui.__mem_func__(self.Close))

			self.maxLevelValue = self.GetChild("maxLevelValue")
			self.maxLevelValue.SetEscapeEvent(ui.__mem_func__(self.Close))

			self.minRefineValue = self.GetChild("minrefineValue")
			self.minRefineValue.SetEscapeEvent(ui.__mem_func__(self.Close))

			self.maxRefineValue = self.GetChild("maxrefineValue")
			self.maxRefineValue.SetEscapeEvent(ui.__mem_func__(self.Close))

			self.minGoldValue = self.GetChild("GoldminValue")
			self.minGoldValue.SetEscapeEvent(ui.__mem_func__(self.Close))

			self.maxGoldValue = self.GetChild("GoldmaxValue")
			self.maxGoldValue.SetEscapeEvent(ui.__mem_func__(self.Close))

			self.prevButton = self.GetChild("prev_button")
			self.prevButton.SetEvent(ui.__mem_func__(self.PrevButton))

			self.nextButton = self.GetChild("next_button")
			self.nextButton.SetEvent(ui.__mem_func__(self.NextButton))

			self.firstPrevButton = self.GetChild("first_prev_button")
			self.firstPrevButton.SetEvent(ui.__mem_func__(self.FirstPrevButton))

			self.lastNextButton = self.GetChild("last_next_button")
			self.lastNextButton.SetEvent(ui.__mem_func__(self.LastNextButton))

			if localeInfo.IsARABIC():
				self.prevButton.LeftRightReverse()
				self.nextButton.LeftRightReverse()
				self.firstPrevButton.LeftRightReverse()
				self.lastNextButton.LeftRightReverse()

			self.page1Button = self.GetChild("page1_button")
			self.page1Button.SetEvent(ui.__mem_func__(self.PageButton), 1)

			self.page2Button = self.GetChild("page2_button")
			self.page2Button.SetEvent(ui.__mem_func__(self.PageButton), 2)

			self.page3Button = self.GetChild("page3_button")
			self.page3Button.SetEvent(ui.__mem_func__(self.PageButton), 3)

			self.page4Button = self.GetChild("page4_button")
			self.page4Button.SetEvent(ui.__mem_func__(self.PageButton), 4)

			self.page5Button = self.GetChild("page5_button")
			self.page5Button.SetEvent(ui.__mem_func__(self.PageButton), 5)

			TempPageSlotButton = []
			TempPageSlotButton.append(self.page1Button)
			TempPageSlotButton.append(self.page2Button)
			TempPageSlotButton.append(self.page3Button)
			TempPageSlotButton.append(self.page4Button)
			TempPageSlotButton.append(self.page5Button)
			TempPageSlotButton.append(self.prevButton)
			TempPageSlotButton.append(self.nextButton)
			TempPageSlotButton.append(self.firstPrevButton)
			TempPageSlotButton.append(self.lastNextButton)
			self.pageButtonList[0] = TempPageSlotButton

			self.HidePageButton()
		except:
			import exception
			exception.Abort("PrivateShopSeachWindow.__LoadWindow.PrivateShopSearchDialog")

	def Open(self, isCash):
		if self.isLoaded == 0:
			self.isLoaded = 1
			self.__LoadWindow()
			self.SetCenterPosition()
			self.SetTop()
			self.__MakeResultSlot()
			self.isCashItem = 1
			if not isCash:
				self.isCashItem = 0
				self.buyButton.Disable()
				self.buyButton.Down()
			ui.ScriptWindow.Show(self)

	def Destroy(self):
		self.Hide()
		self.ClearDictionary()

	def OnPressEscapeKey(self):
		self.Close()
		return True

	def __MakeResultSlot(self):
		yPos = 0
		for i in range(0, self.MAX_LINE_COUNT):
			yPos = 63 + i * 25
			
			## Item Name
			itemSlotImage = ui.MakeImageBox(self, "d:/ymir work/ui/public/parameter_slot_04.sub", 150 + 30, yPos)
			itemSlotImage.SetAlpha(0)
			itemNameSlot = ui.MakeTextLine(itemSlotImage)
			self.Children.append(itemSlotImage)
			self.Children.append(itemNameSlot)

			## Seller
			sellerNameImage = ui.MakeImageBox(self, "d:/ymir work/ui/public/parameter_slot_04.sub", 140 + 125 + 38, yPos)
			sellerNameImage.SetAlpha(0)
			sellerNameSlot = ui.MakeTextLine(sellerNameImage)
			self.Children.append(sellerNameImage)
			self.Children.append(sellerNameSlot)

			## Quantity
			countSlotImage = ui.MakeImageBox(self, "d:/ymir work/ui/public/Parameter_Slot_01.sub", 140 + 125 + 120 + 40, yPos)
			countSlotImage.SetAlpha(0)
			countSlot = ui.MakeTextLine(countSlotImage)
			self.Children.append(countSlotImage)
			self.Children.append(countSlot)

			## Price
			priceSlotImage = ui.MakeImageBox(self, "d:/ymir work/ui/public/Parameter_Slot_03.sub", 140 + 125 + 85 + 90 + 40, yPos)
			priceSlotImage.SetAlpha(0)
			priceSlot = ui.MakeTextLine(priceSlotImage)
			self.Children.append(priceSlotImage)
			self.Children.append(priceSlot)
			
			aNameSlotList = []
			aNameSlotList.append(itemNameSlot)
			aNameSlotList.append(sellerNameSlot)
			aNameSlotList.append(countSlot)
			aNameSlotList.append(priceSlot)

			self.serchItemSlotList[i] = aNameSlotList

			## Item list button
			itemSlotButtonImage = ui.MakeButton(self, 138, yPos, "", "d:/ymir work/ui/", "tab_01.tga", "tab_02.tga", "tab_02.tga")
			itemSlotButtonImage.ShowToolTip = lambda slotIndex = i : self.OverInToolTip(slotIndex)
			itemSlotButtonImage.HideToolTip = lambda slotIndex = i : self.OverOutToolTip(slotIndex)
			itemSlotButtonImage.Hide()
			itemSlotButtonImage.SetEvent(ui.__mem_func__(self.__SelectItem), i)
			self.Children.append(itemSlotButtonImage)

			if localeInfo.IsARABIC():
				itemSlotButtonImage.LeftRightReverse()
				itemSlotButtonImage.SetPosition(self.GetWidth() - 138 - itemSlotButtonImage.GetWidth(), yPos)

			tempItemSlotButtonImage = []
			tempItemSlotButtonImage.append(itemSlotButtonImage)
			self.itemSlotButtonList[i] = tempItemSlotButtonImage

		## Item Type (Sub Type)
		self.itemSubTypeSelectSlot = ui.ComboBoxImage(self, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 115)
		self.itemSubTypeSelectSlot.SetEvent(lambda subTypeNumber, argSelf = proxy(self): argSelf.OnChangeItemSubTypeSlot(subTypeNumber))
		for i in self.WEAPON_SUBTYPE_DIC[0]:
			self.itemSubTypeSelectSlot.InsertItem(i, self.WEAPON_SUBTYPE_DIC[0][i])
		self.itemSubTypeSelectSlot.SetCurrentItem(self.WEAPON_SUBTYPE_DIC[0][0])
		self.itemSubTypeSelectSlot.Show()
		self.Children.append(self.itemSubTypeSelectSlot)

		if localeInfo.IsARABIC():
			self.itemSubTypeSelectSlot.SetPosition(self.GetWidth() - 12 - self.itemSubTypeSelectSlot.GetWidth() - 3, 115)

		## Item type (type)
		self.itemTypeSelectSlot = ui.ComboBoxImage(self, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 95)
		self.itemTypeSelectSlot.SetEvent(lambda typeNumber, argSelf = proxy(self): argSelf.OnChangeItemTypeSlot(typeNumber))

		for i, itemTypeDic in self.ITEM_TYPE_DIC.items():
			self.itemTypeSelectSlot.InsertItem(i, self.ITEM_TYPE_DIC[i])

		self.itemTypeSelectSlot.SetCurrentItem(self.ITEM_TYPE_DIC[1]) # fix
		self.itemTypeSelectSlot.Show()
		self.Children.append(self.itemTypeSelectSlot)

		if localeInfo.IsARABIC():
			self.itemTypeSelectSlot.SetPosition(self.GetWidth() - 12 - self.itemTypeSelectSlot.GetWidth() - 3, 95)

		## Equipment search target
		self.jobSelectSlot = ui.ComboBoxImage(self, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 55)
		self.jobSelectSlot.SetEvent(lambda jobNumber, argSelf = proxy(self): argSelf.OnChangeJobSlot(jobNumber))

		for i in range(0, self.JOB_MAX_COUNT):
			self.jobSelectSlot.InsertItem(i, self.JOB_NAME_DIC[i])
		self.jobSelectSlot.SetCurrentItem(self.JOB_NAME_DIC[0])
		self.jobSelectSlot.Show()
		self.Children.append(self.jobSelectSlot)

		if localeInfo.IsARABIC():
			self.jobSelectSlot.SetPosition(self.GetWidth() - 12 - self.jobSelectSlot.GetWidth() - 3, 55)

	def Close(self):
		self.Hide()
		self.isLoaded = 0

		background.DeletePrivateShopPos()

		self.saveJobSelectNumber = 0
		self.saveItemTypeSelectNumber = item.ITEM_TYPE_WEAPON
		self.saveItemSubTypeSelectNumber = 0

		self.itemNameValue.KillFocus()

		self.selectItemRealIndex = -1
		self.selectItemIndex = -1

		if self.popup:
			self.popup.Close()
			self.popup = None

	def GetPageSlot(self, slotIndex):
		maxCount = privateShopSearch.GetItemCount()
		page = self.plusPageNumber
		slot = slotIndex

		if page > 1:
			slot = (((page - 1) * self.MAX_LINE_COUNT) + slotIndex)
			if slot < maxCount:
				return slot
			else:
				return -1

		return slot

	def GetRealPageSlot(self, slotIndex):
		maxCount = privateShopSearch.GetItemCount()
		page = self.plusPageNumber
		slot = slotIndex

		if page > 1:
			slot = (((page - 1) * self.MAX_LINE_COUNT) + slotIndex)
			if slot < maxCount:
				return slot
			else:
				return -1

		return slot

	def GetPrivateShopSearchResult(self, slot):
		slotIndex = self.GetPageSlot(slot)
		itemVnum = 0
		if slotIndex != -1:
			itemVnum = privateShopSearch.GetSearchItemVnum(slotIndex)
		itemName = ""
		sellerName = ""
		count = 0
		price = 0
		
		if itemVnum != 0:
			item.SelectItem(itemVnum)
			itemName = item.GetItemName()

			sellerVID = privateShopSearch.GetSearchItemShopVID(slotIndex)
			sellerName = chr.GetNameByVID(sellerVID)

			count = privateShopSearch.GetSearchItemCount(slotIndex)
			price = privateShopSearch.GetSearchItemPrice(slotIndex)

		return itemName, sellerName, count, price

	def RefreshList(self):
		maxCount = privateShopSearch.GetItemCount()
		page = self.nowPageNumber

		for line, nameSlotList in self.serchItemSlotList.items():
			if line < maxCount:
				itemName, sellerName, count, price = self.GetPrivateShopSearchResult(line)
				if "" == itemName:
					nameSlotList[0].SetText("")
					nameSlotList[1].SetText("")
					nameSlotList[2].SetText("")
					nameSlotList[3].SetText("")
					self.itemSlotButtonList[line][0].Hide()
				else:
					nameSlotList[0].SetText(itemName)
					nameSlotList[1].SetText(sellerName)
					nameSlotList[2].SetText(str(count))
					nameSlotList[3].SetText(self.NumberToMoneyString(price))
					self.itemSlotButtonList[line][0].Show()

		self.ShowPageButton(maxCount, page)

		if self.bigPageCount == 1:
			self.prevButton.Disable()
			self.prevButton.Down()
			# self.prevButton.Hide()
		else:
			self.prevButton.Enable()
			#self.prevButton.Show()

		if self.bigPageCount - 1 <= 1:
			self.firstPrevButton.Disable()
			self.firstPrevButton.Down()
			# self.firstPrevButton.Hide()
		else:
			self.firstPrevButton.Enable()
			#self.firstPrevButton.Show()

		if maxCount <= self.bigPageCount * self.PAGE1_MAX_SIZE:
			self.nextButton.Disable()
			self.nextButton.Down()
			# self.nextButton.Hide()
		else:
			self.nextButton.Enable()
			# self.nextButton.Show()

		if maxCount <= (self.bigPageCount + 1) * self.PAGE1_MAX_SIZE:
			self.lastNextButton.Disable()
			self.lastNextButton.Down()
			# self.lastNextButton.Hide()
		else:
			self.lastNextButton.Enable()
			# self.lastNextButton.Show()

	def NumberToMoneyString(self, n):
		if n <= 0 :
			return "0"

		return "%s %s" % ('.'.join([ i-3<0 and str(n)[:i] or str(n)[i-3:i] for i in range(len(str(n))%3, len(str(n))+1, 3) if i ]), "")

	def PageButton(self, number):
		if number == self.nowPageNumber:
			return

		if self.bigPageCount > 1:
			if number == self.nowPageNumber - (self.bigPageCount - 1) * 5:
				return

		self.ClearPageButtonColor()
		self.pageButtonList[0][number - 1].SetTextColor(self.SPECIAL_TITLE_COLOR)
		self.pageButtonList[0][number - 1].Down()
		self.pageButtonList[0][number - 1].Disable()
		self.nowPageNumber = int(self.pageButtonList[0][number - 1].GetText())
		self.plusPageNumber = int(self.pageButtonList[0][number - 1].GetText())

		self.RefreshList()
		self.ClearEffectEtc()

	def FirstPrevButton(self):
		if self.bigPageCount - 1 <= 1:
			return

		self.ClearPageButtonColor()
		self.bigPageCount = 1
		for line, pageButton in self.pageButtonList.items():
			for i in xrange(5):
				pageButton[i].SetText(str(i + 1))

		self.nowPageNumber = int(self.pageButtonList[0][0].GetText())
		self.plusPageNumber = 1
		self.pageButtonList[0][0].SetTextColor(self.SPECIAL_TITLE_COLOR)
		self.pageButtonList[0][0].Down()
		self.pageButtonList[0][0].Disable()

		self.RefreshList()
		self.ClearEffectEtc()

	def LastNextButton(self):
		maxSize = privateShopSearch.GetItemCount()
		self.pageCount = maxSize / 10
		self.HidePageButton()
		self.ClearPageButtonColor()

		if self.pageCount % 5 == 0:
			self.bigPageCount = (self.pageCount / 5)
		else:
			self.bigPageCount = (self.pageCount / 5) + 1

		pageNumber = 5 * (self.pageCount / 5)
		if pageNumber == self.pageCount:
			pageNumber -= 5
		for line, pageButton in self.pageButtonList.items():
			for i in xrange(5):
				pageButton[i].SetText(str(i + pageNumber + 1))

		self.nowPageNumber = self.pageCount
		self.plusPageNumber = pageNumber

		self.RefreshList()
		self.ClearEffectEtc()

	def PrevButton(self):
		if self.bigPageCount == 1:
			return

		self.ClearPageButtonColor()
		self.bigPageCount -= 1

		for line, pageButton in self.pageButtonList.items():
			for i in xrange(5):
				pageNumber = int(pageButton[i].GetText()) - 5
				pageButton[i].SetText(str(pageNumber))

		self.nowPageNumber = int(self.pageButtonList[0][0].GetText())
		self.plusPageNumber -= 1
		self.pageButtonList[0][0].SetTextColor(self.SPECIAL_TITLE_COLOR)
		self.pageButtonList[0][0].Down()
		self.pageButtonList[0][0].Disable()

		self.RefreshList()
		self.ClearEffectEtc()

	def NextButton(self):
		maxItemCount = privateShopSearch.GetItemCount()
		if maxItemCount < self.bigPageCount * self.PAGE1_MAX_SIZE:
			return

		for line, pageButton in self.pageButtonList.items():
			for i in xrange(5):
				pageNumber = int(pageButton[i].GetText()) + 5
				pageButton[i].SetText(str(pageNumber))

		self.nowPageNumber = int(self.pageButtonList[0][0].GetText())
		self.plusPageNumber += 1
		self.bigPageCount += 1
		self.HidePageButton()
		self.ClearPageButtonColor()
		self.pageButtonList[0][0].SetTextColor(self.SPECIAL_TITLE_COLOR)
		self.pageButtonList[0][0].Down()
		self.pageButtonList[0][0].Disable()

		self.RefreshList()
		self.ClearEffectEtc()

	def ClearPageButtonColor(self):
		for line, pageButton in self.pageButtonList.items():
			for i in range(0,self.PAGE_BUTTON_NUMBER_SIZE):
				pageButton[i].SetTextColor(0xffffffff)
				pageButton[i].SetUp()
				pageButton[i].Enable()

	def HidePageButton(self):
		for line, pageButton in self.pageButtonList.items():
			for i in range(0, self.PAGE_BUTTON_MAX_SIZE):
				pageButton[i].Hide()

	def ShowPageButton(self, maxSize, page):
		if self.bigPageCount > 1:
			maxSize = maxSize - ((self.bigPageCount - 1) * self.PAGE1_MAX_SIZE)
			page = page - (self.bigPageCount - 1) * 5

		self.pageCount = maxSize / 10

		if not maxSize % 10 == 0:
			self.pageCount = self.pageCount + 1

		if self.pageCount > 5:
			self.pageCount = 5

		for line, pageButton in self.pageButtonList.items():
			for i in xrange(self.pageCount):
				pageButton[i].Show()

		self.pageButtonList[0][5].Show()
		self.pageButtonList[0][6].Show()
		self.pageButtonList[0][7].Show()
		self.pageButtonList[0][8].Show()

		self.ClearPageButtonColor()
		self.pageButtonList[0][page-1].SetTextColor(self.SPECIAL_TITLE_COLOR)
		self.pageButtonList[0][page-1].Down()
		self.pageButtonList[0][page-1].Disable()
		self.nowPageNumber = page

	def OnUpdate(self):
		if (app.GetTime() - self.searchClickTime) > self.CLICK_LIMIT_TIME and self.searchButton.IsDisable() == 0:
			self.searchButton.Enable()

		if (app.GetTime() - self.buyClickTime) > self.CLICK_LIMIT_TIME and self.buyButton.IsDisable() == 0 and self.isCashItem == 1:
			self.buyButton.Enable()

	def Search(self):
		privateSearchItemCount_6004 = player.GetItemCountByVnum(60004)
		privateSearchItemCount_6005 = player.GetItemCountByVnum(60005)

		if privateSearchItemCount_6004 <= 0 and privateSearchItemCount_6005 <= 0:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.PRIVATESHOPSEARCH_NEED_ITEM_FIND)
			self.Close()
			return

		privateShopSearch.ClearSearchItems()

		self.searchClickTime = app.GetTime()
		self.searchButton.Disable()
		self.searchButton.SetUp()

		job = self.saveJobSelectNumber
		type = self.saveItemTypeSelectNumber
		subType = self.saveItemSubTypeSelectNumber

		if len(self.minRefineValue.GetText()) <= 0:
			self.minRefineValue.SetText("0")
		if len(self.maxRefineValue.GetText()) <= 0:
			self.maxRefineValue.SetText("15")

		if len(self.minLevelValue.GetText()) <= 0:
			self.minLevelValue.SetText("1")
		if len(self.maxLevelValue.GetText()) <= 0:
			self.maxLevelValue.SetText("120")

		if len(self.minGoldValue.GetText()) <= 0:
			self.minGoldValue.SetText("1")
		if len(self.maxGoldValue.GetText()) <= 0:
			self.maxGoldValue.SetText("900000000")

		minRefine = int(self.minRefineValue.GetText())
		maxRefine = int(self.maxRefineValue.GetText())
		minLevel = int(self.minLevelValue.GetText())
		if minLevel == 1:
			minLevel = 0

		maxLevel = int(self.maxLevelValue.GetText())
		minGold = int(self.minGoldValue.GetText())
		maxGold = int(self.maxGoldValue.GetText())
		itemName = self.itemNameValue.GetText()
		itemName = itemName.replace(" ", "_")

		if minGold > GOLD_MAX - 1:
			minGold = GOLD_MAX - 1
			self.minGoldValue.SetText(str(GOLD_MAX - 1))

		if maxGold > GOLD_MAX - 1:
			maxGold = GOLD_MAX - 1
			self.maxGoldValue.SetText(str(GOLD_MAX - 1))

		if (len(itemName)):
			net.SendPrivateShopSearchInfoSub(job, type, subType, minLevel, maxLevel, minRefine, maxRefine, minGold, maxGold, itemName)
		else:
			net.SendPrivateShopSearchInfo(job, type, subType, minLevel, maxLevel, minRefine, maxRefine, minGold, maxGold)

		for line, nameSlotList in self.serchItemSlotList.items():
			nameSlotList[0].SetText("")
			nameSlotList[1].SetText("")
			nameSlotList[2].SetText("")
			nameSlotList[3].SetText("")

			self.itemSlotButtonList[line][0].Hide()

		self.ClearEffectEtc()
		self.HidePageButton()
		self.bigPageCount = 1
		for line, pageButton in self.pageButtonList.items():
			for i in xrange(5):
				pageNumber = int(pageButton[i].GetText()) - 5
				pageButton[i].SetText(str(i + 1))

	def Buy(self):
		privateSearchItemCount_60005 = player.GetItemCountByVnum(60005)
		if privateSearchItemCount_60005 <= 0:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.PRIVATESHOPSEARCH_NEED_ITEM_BUY)
			self.Close()
			return

		if self.selectItemRealIndex == -1:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.PRIVATESHOPSEARCH_SELECTITEM)
			return

		self.buyClickTime = app.GetTime()
		self.buyButton.Disable()
		self.buyButton.SetUp()

		popup = uiCommon.QuestionDialog()
		popup.SetText(localeInfo.PRIVATESHOPSEARCH_BUYTIME)
		popup.SetAcceptEvent(self.OnBuyAcceptEvent)
		popup.SetCancelEvent(self.OnBuyCloseEvent)
		popup.Open()
		self.popup = popup

	def OnBuyAcceptEvent(self):
		if self.selectItemRealIndex == -1:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.PRIVATESHOPSEARCH_SELECTITEM)
			return

		chrVID = privateShopSearch.GetSearchItemShopVID(self.GetPageSlot(self.selectItemRealIndex))
		shopItemPos = privateShopSearch.GetSearchItemPos(self.GetPageSlot(self.selectItemRealIndex))
		# net.SendPrivateShopSerchBuyItem(chrVID, shopItemPos)
		self.ClearEffectEtc()
		self.Search()
		self.popup.Close()
		self.popup = None

	def OnBuyCloseEvent(self):
		self.popup.Close()
		self.popup = None
		self.ClearEffectEtc()

	def __SelectItem(self, arg):
		self.selectItemRealIndex = arg
		self.selectItemIndex = arg
		self.__SelectItemSlotButtonList(arg)

		chrVID = privateShopSearch.GetSearchItemShopVID(self.GetPageSlot(self.selectItemRealIndex))
		background.DeletePrivateShopPos(chrVID)
		background.CreatePrivateShopPos(chrVID)

	def __ClearItemSlotButtonList(self):
		for line, itemSlotButtonList in self.itemSlotButtonList.items():
			itemSlotButtonList[0].SetUp()

	def __SelectItemSlotButtonList(self, index):
		for line, itemSlotButtonList in self.itemSlotButtonList.items():
			if index != line:
				itemSlotButtonList[0].SetUp()
			else:
				itemSlotButtonList[0].Down()

	def SetItemToolTip(self, tooltip):
		self.toolTipItem = tooltip

	def __ShowToolTip(self, slotIndex):
		if self.toolTipItem:
			self.toolTipItem.SetPrivateSearchItem(self.GetRealPageSlot(slotIndex))

	def OverInToolTip(self, slotIndex):
		self.__ShowToolTip(slotIndex)

	def OverOutToolTip(self, slotIndex):
		if self.toolTipItem:
			self.toolTipItem.HideToolTip()

		if self.selectItemIndex == slotIndex:
			self.itemSlotButtonList[slotIndex][0].Down()

	def OnChangeItemSubTypeSlot(self, subTypeNumber):
		if self.saveItemTypeSelectNumber == item.ITEM_TYPE_WEAPON:
			self.itemSubTypeSelectSlot.SetCurrentItem(self.WEAPON_SUBTYPE_DIC[self.saveJobSelectNumber][subTypeNumber])
		else:
			self.itemSubTypeSelectSlot.SetCurrentItem(self.ITEM_SUBTYPE_DICS[self.saveItemTypeSelectNumber][subTypeNumber])
		self.saveItemSubTypeSelectNumber = subTypeNumber

	def OnChangeItemTypeSlot(self, typeNumber):
		self.itemTypeSelectSlot.SetCurrentItem(self.ITEM_TYPE_DIC[typeNumber])
		if typeNumber != self.saveItemTypeSelectNumber:
			self.itemSubTypeSelectSlot.ClearItem()
			if typeNumber == item.ITEM_TYPE_WEAPON:
				subType = 0
				saveFirst = 0
				for i in self.WEAPON_SUBTYPE_DIC[self.saveJobSelectNumber]:
					self.itemSubTypeSelectSlot.InsertItem(i, self.WEAPON_SUBTYPE_DIC[self.saveJobSelectNumber][i])
					if subType == 0:
						if saveFirst == 0:
							subType = i
							saveFirst = 1
				self.itemSubTypeSelectSlot.SetCurrentItem(self.WEAPON_SUBTYPE_DIC[self.saveJobSelectNumber][subType])
				self.saveItemSubTypeSelectNumber = subType
			else:
				subType = 0
				saveFirst = 0
				for i in self.ITEM_SUBTYPE_DICS[typeNumber]:
					self.itemSubTypeSelectSlot.InsertItem(i,self.ITEM_SUBTYPE_DICS[typeNumber][i])
					if subType == 0:
						if saveFirst == 0:
							subType = i
							saveFirst = 1
				self.itemSubTypeSelectSlot.SetCurrentItem(self.ITEM_SUBTYPE_DICS[typeNumber][subType])
				self.saveItemSubTypeSelectNumber = subType
			self.saveItemTypeSelectNumber = typeNumber

	def OnChangeJobSlot(self, jobNumber):
		self.jobSelectSlot.SetCurrentItem(self.JOB_NAME_DIC[jobNumber])
		if jobNumber != self.saveJobSelectNumber:
			if self.saveItemTypeSelectNumber == item.ITEM_TYPE_WEAPON:
				self.itemSubTypeSelectSlot.ClearItem()
				subType = 0
				saveFirst = 0
				for i in self.WEAPON_SUBTYPE_DIC[jobNumber]:
					self.itemSubTypeSelectSlot.InsertItem(i, self.WEAPON_SUBTYPE_DIC[jobNumber][i])
					if subType == 0:
						if saveFirst == 0:
							subType = i
							saveFirst = 1
				self.itemSubTypeSelectSlot.SetCurrentItem(self.WEAPON_SUBTYPE_DIC[jobNumber][subType])
				self.saveItemSubTypeSelectNumber = subType
			self.saveJobSelectNumber = jobNumber

	def ClearEffectEtc(self):
		background.DeletePrivateShopPos()
		self.__ClearItemSlotButtonList()
		self.selectItemRealIndex = -1
		self.selectItemIndex = -1

	def OnTop(self):
		self.itemNameValue.SetFocus()