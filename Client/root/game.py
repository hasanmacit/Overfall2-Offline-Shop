#importlara ekle

if app.ENABLE_OFFLINE_SHOP_SYSTEM:
	import uiOfflineShop
	import uiOfflineShopBuilder

#arat

uiPrivateShopBuilder.Clear()

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			uiOfflineShopBuilder.Clear()

#arat

def __PressJKey(self):

#değiştir

	def __PressJKey(self):
		if app.IsPressed(app.DIK_LCONTROL) or app.IsPressed(app.DIK_RCONTROL):
			if player.IsMountingHorse():
				net.SendChatPacket("/unmount")
			else:
				#net.SendChatPacket("/user_horse_ride")
				if app.ENABLE_OFFLINE_SHOP_SYSTEM:
					if not uiPrivateShopBuilder.IsBuildingPrivateShop() and not uiOfflineShopBuilder.IsBuildingOfflineShop():
						for i in xrange(player.INVENTORY_PAGE_SIZE):
							if player.GetItemIndex(i) in (71114, 71116, 71118, 71120):
								net.SendItemUsePacket(i)
								break
				else:
					if not uiPrivateShopBuilder.IsBuildingPrivateShop():
						for i in xrange(player.INVENTORY_PAGE_SIZE):
							if player.GetItemIndex(i) in (71114, 71116, 71118, 71120):
								net.SendItemUsePacket(i)
								break

#arat

def SetShopSellingPrice(self, Price):

#altına ekle

	if app.ENABLE_OFFLINE_SHOP_SYSTEM:
		def StartOfflineShop(self, vid):
			self.interface.OpenOfflineShopDialog(vid)

		def EndOfflineShop(self):
			self.interface.CloseOfflineShopDialog()

		def RefreshOfflineShop(self):
			self.interface.RefreshOfflineShopDialog()

		def RefreshOfflineShopManager(self):
			self.interface.RefreshOfflineShopDialogManager()

		def CloseOfflineShopManager(self):
			self.interface.CloseOfflineShopDialogManager()

		def RefreshShopSellingPrice(self, vid, pos, Price):
			if self.interface:
				self.interface.ReloadOfflineShopItemPrice(vid, pos, Price)

#arat

def __DropMoney(self, attachedType, attachedMoney):

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if uiOfflineShopBuilder.IsBuildingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.DROP_ITEM_FAILURE_PRIVATE_SHOP)
				return

			if uiOfflineShop.IsEditingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.DROP_ITEM_FAILURE_PRIVATE_SHOP)
				return

#arat

def __DropItem(self, attachedType, attachedItemIndex, attachedItemSlotPos, attachedItemCount):

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if uiOfflineShopBuilder.IsBuildingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.DROP_ITEM_FAILURE_PRIVATE_SHOP)
				return

			if uiOfflineShop.IsEditingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.DROP_ITEM_FAILURE_PRIVATE_SHOP)
				return

#arat

def __SendDropItemPacket(self, itemVNum, itemCount, itemInvenType = player.INVENTORY):

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if uiOfflineShopBuilder.IsBuildingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.DROP_ITEM_FAILURE_PRIVATE_SHOP)
				return

			if uiOfflineShop.IsEditingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.DROP_ITEM_FAILURE_PRIVATE_SHOP)
				return

#arat

		self.serverCommander=stringCommander.Analyzer()
		for serverCommandItem in serverCommandList.items():
			self.serverCommander.SAFE_RegisterCallBack(
				serverCommandItem[0], serverCommandItem[1]
			)

#üstüne ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			serverCommandList.update({
				"BINARY_CloseOfflineShop" : self.BINARY_CloseOfflineShop,
				"OpenOfflineShop" : self.__OfflineShop_Open,
				"OpenOfflineShopSalesWindow" : self.__OpenOfflineShopSalesWindow,
				"ClearOfflineShopSales" : self.__ClearOfflineShopSalesWindow,
			})

#arat

	def BINARY_PrivateShop_Disappear(self, vid):
		self.interface.DisappearPrivateShop(vid)

#altına ekle

	if app.ENABLE_OFFLINE_SHOP_SYSTEM:
		def BINARY_OfflineShopAdviseBuyItem(self, itemId, buyerName, itemPrice):
			if self.interface and itemId > 0:
				item.SelectItem(itemId)
				itemPrice -= (3 * itemPrice) / 100
				tip_msg = localeInfo.OFFLINE_SHOP_ADVISE_PLAYER_TIP.format(item.GetItemName(), localeInfo.NumberToMoneyString(itemPrice))
				self.interface.LoadAppLeftTip(tip_msg, "SHOP")
		def __OfflineShop_Open(self):
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_OPEN_WITH_BUTTON)
		
		def BINARY_CloseOfflineShop(self):
			if self.interface:
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_FORCE_CLOSE)
				self.interface.BINARY_CloseOfflineShop()
		
		def BINARY_ChangeOfflineShopName(self, shopName):
			if self.interface:
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_CHANGE_SHOP_NAME)
				self.interface.BINARY_ChangeOfflineShopName(shopName)

		def __OpenOfflineShopSalesWindow(self):
			self.interface.OpenOfflineShopSalesWindow()

		def __ClearOfflineShopSalesWindow(self):
			constInfo.OFFLINE_SHOP_SALES = []

		def BINARY_OfflineShop_Appear(self, vid, text, borderStyle):
			if (chr.GetInstanceType(vid) == chr.INSTANCE_TYPE_NPC):
				self.interface.AppearOfflineShop(vid, text, borderStyle)
		
		def BINARY_OfflineShop_ChangeSign(self, vid, text):
			if (chr.GetInstanceType(vid) == chr.INSTANCE_TYPE_NPC):
				self.interface.ChangeOfflineShopSign(vid, text)

		def BINARY_OfflineShop_Disappear(self, vid):
			if (chr.GetInstanceType(vid) == chr.INSTANCE_TYPE_NPC):
				self.interface.DisappearOfflineShop(vid)

		def BINARY_OfflineShop_Count(self, count):
			pass

		def BINARY_OfflineShop_Open(self, isOpen, mapIndex, shopChannel, time, isPremium, displayedCount, shopName):
			if self.interface:
				self.interface.ToggleOfflineShopAdminPanelWindow(isOpen, mapIndex, shopChannel, time, isPremium, displayedCount, shopName)

		def BINARY_OfflineShop_Sales(self, buyerName, itemVnum, itemCount, itemPrice, itemDate):
			constInfo.OFFLINE_SHOP_SALES.append([buyerName, itemVnum, itemCount, itemPrice, itemDate],)

#arat

		if self.enableXMasBoom:
			self.__XMasBoom_Update()

#altına ekle

		if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			privateShopEffect, privateShopEffectStartTime = constInfo.CREATE_PRIVATE_SHOP_EFFECT
			if privateShopEffect is True:
				if privateShopEffectStartTime - app.GetTime() < 0:
					background.DeletePrivateShopPos()
			else:
				background.DeletePrivateShopPos()

#en alta ekle

	if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
		def OpenPrivateShopSearch(self, type):
			if self.interface:
				self.interface.OpenPrivateShopSearch(type)

		def RefreshShopSearch(self):
			self.interface.RefreshShopSearch()

		def BuyShopSearch(self):
			self.interface.RefreshShopSearch()
	
	if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
		def OpenNewPrivateShopSearch(self):
			if self.interface:
				self.interface.OpenNewPrivateShopSearch()
			
		def RefreshNewShopSearch(self):
			if self.interface:
				self.interface.RefreshNewShopSearch()

		def BINARY_NewPrivateShopSearch_Error(self, error):
			if self.interface:
				self.interface.NewPrivateShopSearch_Error(error)
	
		def BINARY_NewShopSearchBuy(self, shopId):
			if self.interface:
				self.interface.NewShopSearchBuy(shopId)
	
		def BINARY_NewShopSearchRemoved(self, shopId):
			if self.interface:
				self.interface.NewShopSearchRemoved(shopId)
		
		def BINARY_NewShopSearchPriceChanged(self, shopId, newPrice):
			if self.interface:
				self.interface.NewShopSearchPriceChanged(shopId, newPrice)

		def OnNewShopError(self, type):
			try:
				self.PopupMessage(localeInfo.SHOP_ERROR_DICT[type])
			except KeyError:
				self.PopupMessage(localeInfo.SHOP_ERROR_UNKNOWN % (type))