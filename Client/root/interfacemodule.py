#importlara ekle

if app.ENABLE_OFFLINE_SHOP_SYSTEM:
	import uiOfflineShop
	import uiOfflineShopBuilder

if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
	import uiPrivateShopSearch

if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
	import uiNewPrivateShopSearch

#arat

self.privateShopAdvertisementBoardDict = {}

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.offlineShopAdvertisementBoardDict = {}

#arat

		event.SetInterfaceWindow(self)

#üstüne ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.wndOfflineShopManager = None
			self.wndOpenOfflineShop = None

#arat

self.wndChatLog = wndChatLog

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			wndOfflineShopManager = uiOfflineShop.OfflineShopManagerWindow()
			self.wndOfflineShopManager = wndOfflineShopManager

			wndOpenOfflineShop = uiOfflineShop.OpenOfflineShop()
			self.wndOpenOfflineShop = wndOpenOfflineShop

#arat

self.dlgShop.Hide()

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.dlgOfflineShop = uiOfflineShop.OfflineShopDialog()
			self.dlgOfflineShop.LoadDialog()
			self.dlgOfflineShop.Hide()

#arat

self.privateShopBuilder.Hide()

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.offlineShopBuilder = uiOfflineShopBuilder.OfflineShopBuilder()
			if app.WJ_ENABLE_TRADABLE_ICON:
				self.offlineShopBuilder.BindInterface(self)
				self.wndOfflineShopManager.BindInterface(self)
				self.wndOpenOfflineShop.BindInterface(self)
			self.offlineShopBuilder.Hide()

#arat

self.privateShopBuilder.SetItemToolTip(self.tooltipItem)

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.dlgOfflineShop.SetItemToolTip(self.tooltipItem)
			self.offlineShopBuilder.SetItemToolTip(self.tooltipItem)
			self.wndOfflineShopManager.SetItemToolTip(self.tooltipItem)
			if app.WJ_ENABLE_TRADABLE_ICON:
				self.offlineShopBuilder.SetInven(self.wndInventory)
				self.wndOfflineShopManager.SetInven(self.wndInventory)

#arat

		if self.wndItemSelect:
			self.wndItemSelect.Destroy()

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if self.dlgOfflineShop:
				self.dlgOfflineShop.Hide()
				self.dlgOfflineShop.Destroy()

			if self.offlineShopBuilder:
				self.offlineShopBuilder.Hide()
				self.offlineShopBuilder.Destroy()

			if self.wndOfflineShopManager:
				self.wndOfflineShopManager.Hide()
				self.wndOfflineShopManager.Destroy()

			if self.wndOpenOfflineShop:
				self.wndOpenOfflineShop.Hide()
				self.wndOpenOfflineShop.Destroy()

		if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			if self.wndPrivateShopSearch:
				self.wndPrivateShopSearch.Hide()
				self.wndPrivateShopSearch.Destroy()
			
		if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			if self.wndNewPrivateShopSearch:
				self.wndNewPrivateShopSearch.Hide()
				self.wndNewPrivateShopSearch.Destroy()

#arat

del self.wndItemSelect

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if self.dlgOfflineShop:
				del self.dlgOfflineShop

			if self.wndOfflineShopManager:
				del self.wndOfflineShopManager

			if self.wndOpenOfflineShop:
				del self.wndOpenOfflineShop

		if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			del self.wndPrivateShopSearch
		
		if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			del self.wndNewPrivateShopSearch

#arat

self.privateShopAdvertisementBoardDict = {}

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.offlineShopAdvertisementBoardDict = {}

#arat

	def RefreshShopDialog(self):
		self.dlgShop.Refresh()

#altına ekle

	if app.ENABLE_OFFLINE_SHOP_SYSTEM:
		def GetOpenShopDialog(self, vid):
			if not self.dlgOfflineShop:
				return False
			
			return self.dlgOfflineShop.HaveShopVidOpen(vid)
		
		def ReloadOfflineShopItemPrice(self, vid, pos, Price):
			if not self.dlgOfflineShop:
				return
			
			if not self.GetOpenShopDialog(vid):
				return
			
			self.dlgOfflineShop.ReloadOfflineShopItemPrice(vid, pos, Price)
		
		def OpenOfflineShopDialog(self, vid):
			if self.wndOfflineShopManager.IsShow():
				self.wndOfflineShopManager.Close()

			self.wndInventory.Show()
			self.wndInventory.SetTop()
			self.dlgOfflineShop.Open(vid)
			self.dlgOfflineShop.SetTop()
			event.SetInterfaceWindow(self)

		def CloseOfflineShopDialog(self):
			self.dlgOfflineShop.Close()

		def RefreshOfflineShopDialog(self):
			self.dlgOfflineShop.Refresh()

		def RefreshOfflineShopDialogManager(self):
			self.wndOfflineShopManager.Refresh()

		def CloseOfflineShopDialogManager(self):
			self.wndOfflineShopManager.Close()
		
		def BINARY_CloseOfflineShop(self):
			if self.wndOfflineShopManager:
				shop.ClearOfflineShopStock()
				self.wndOfflineShopManager.Close()
		
		def BINARY_ChangeOfflineShopName(self, shopName):
			if self.wndOfflineShopManager:
				self.wndOfflineShopManager.ChangeOfflineShopName(shopName)

#arat

		if self.wndExpandedTaskBar:
			self.wndExpandedTaskBar.Hide()

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if self.wndOfflineShopManager:
				self.wndOfflineShopManager.Hide()

			if self.wndOpenOfflineShop:
				self.wndOpenOfflineShop.Hide()

#arat

def ToggleChatLogWindow(self):

#altına ekle

	if app.ENABLE_OFFLINE_SHOP_SYSTEM:
		def ToggleOfflineShopAdminPanelWindow(self, isOpen, mapIndex, shopChannel, time, isPremium, displayedCount, shopName):
			if self.wndOpenOfflineShop.IsShow() == True:
				return

			if self.dlgOfflineShop.IsShow():
				self.dlgOfflineShop.Close()

			if not self.offlineShopBuilder.IsShow():
				if self.wndOfflineShopManager.IsShow() == True:
					self.wndOfflineShopManager.Close()
				else:
					if self.offlineShopBuilder.IsBuilding() == False:
						self.wndOfflineShopManager.Open(isOpen, mapIndex, shopChannel, time, isPremium, displayedCount, shopName)

#arat

		if app.ENABLE_DRAGON_SOUL_SYSTEM:
			hideWindows += self.wndDragonSoul,\
						self.wndDragonSoulRefine,

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if self.wndOfflineShopManager:
				hideWindows += self.wndOfflineShopManager,

			if self.wndOpenOfflineShop:
				hideWindows += self.wndOpenOfflineShop,

#arat

def DisappearPrivateShop(self, vid):

#altına ekle

	if app.ENABLE_OFFLINE_SHOP_SYSTEM:
		#####################################################################################
		### Offline Shop ###

		def OpenOfflineShopSalesWindow(self):
			if self.wndOfflineShopManager.IsShow():
				self.wndOfflineShopManager.RefreshSalesWindow()

		def OpenOfflineShopCreateDialog(self):
			constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)
			self.wndOfflineShopManager.Close()
			self.wndOpenOfflineShop.Open()

		def CloseOfflineShopCreateDialog(self):
			constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)
			self.wndOpenOfflineShop.Hide()

		def OpenOfflineShopBuilder(self, shopName, npcVnum, borderStyle):
			self.offlineShopBuilder.Open(shopName, npcVnum, borderStyle) # arg2.style
			self.CloseOfflineShopCreateDialog()
			return True

		def AppearOfflineShop(self, vid, text, borderStyle):
			real_bord_style = borderStyle
			if borderStyle < 0 or borderStyle > 5:
				real_bord_style = 0
			
			base = ["", "fire", "ice", "paper", "ribon", "wing"]
			
			board = uiOfflineShopBuilder.OfflineShopAdvertisementBoard(base[borderStyle])
			board.Open(vid, text)

			self.offlineShopAdvertisementBoardDict[vid] = board
		
		def ChangeOfflineShopSign(self, vid, text):
			if self.offlineShopAdvertisementBoardDict.has_key(vid):
				uiOfflineShopBuilder.UpdateADTextBoard(vid, text)
				return

		def DisappearOfflineShop(self, vid, borderStyle):
			if not self.offlineShopAdvertisementBoardDict.has_key(vid):
				return

			del self.offlineShopAdvertisementBoardDict[vid]
			uiOfflineShopBuilder.DeleteADBoard(vid)

#arat

def __MakeCubeWindow(self):

#altına ekle

	if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
		def __MakePrivateShopSearchWindow(self):
			self.wndPrivateShopSearch = uiPrivateShopSearch.PrivateShopSeachWindow()
			# self.wndPrivateShopSearch.LoadWindow()
			self.wndPrivateShopSearch.Hide()
	
	if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
		def __MakeNewPrivateShopSearchWindow(self):
			self.wndNewPrivateShopSearch = uiNewPrivateShopSearch.PrivateShopSearchWindow()
			self.wndNewPrivateShopSearch.SetInterface(self)
			self.wndNewPrivateShopSearch.Hide()

#arat

self.__MakeCubeResultWindow()

#altına ekle

		if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			self.__MakePrivateShopSearchWindow()
		if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			self.__MakeNewPrivateShopSearchWindow()

#arat

self.wndInventory.SetItemToolTip(self.tooltipItem)

#altına ekle

		if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			self.wndPrivateShopSearch.SetItemToolTip(self.tooltipItem)
		if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			self.wndNewPrivateShopSearch.SetItemToolTip(self.tooltipItem)

#arat

def RefreshInventory(self):

#altına ekle

	if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
		def SearchNewPrivateShopSearchItem(self, itemName):
			if self.dlgOfflineShop:
				self.dlgOfflineShop.Close()
			
			if self.wndNewPrivateShopSearch:
				self.wndNewPrivateShopSearch.SearchNewPrivateShopSearchItem(itemName)
		
		def OpenNewPrivateShopSearch(self):
			if self.wndNewPrivateShopSearch:
				self.wndNewPrivateShopSearch.Open()
		
		def RefreshNewShopSearch(self):
			if self.wndNewPrivateShopSearch:
				self.wndNewPrivateShopSearch.RefreshList()
		
		def NewPrivateShopSearch_Error(self, error):
			if self.wndNewPrivateShopSearch:
				self.wndNewPrivateShopSearch.ShopSearch_Error(error)
		
		def NewShopSearchBuy(self, shopId):
			if self.wndNewPrivateShopSearch:
				self.wndNewPrivateShopSearch.NewShopSearchBuy(shopId)
		
		def NewShopSearchRemoved(self, shopId):
			if self.wndNewPrivateShopSearch:
				self.wndNewPrivateShopSearch.NewShopSearchRemoved(shopId)
		
		def NewShopSearchPriceChanged(self, shopId, newPrice):
			if self.wndNewPrivateShopSearch:
				self.wndNewPrivateShopSearch.NewShopSearchPriceChanged(shopId, newPrice)
	
	if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
		def OpenPrivateShopSearch(self, type):
			self.wndPrivateShopSearch.Open(type)
		
		def RefreshShopSearch(self):
			self.wndPrivateShopSearch.RefreshList()

#arat

def EmptyFunction(self):

#altına ekle

	if app.WJ_ENABLE_TRADABLE_ICON:
		def SetOnTopWindow(self, onTopWnd):
			self.onTopWindow = onTopWnd

		def GetOnTopWindow(self):
			return self.onTopWindow

		def RefreshMarkInventoryBag(self):
			self.wndInventory.RefreshMarkSlots()