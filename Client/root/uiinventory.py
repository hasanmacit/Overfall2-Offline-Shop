#importlara ekle

if app.ENABLE_OFFLINE_SHOP_SYSTEM:
	import uiOfflineShop
	import uiOfflineShopBuilder
import uiToolTip

#arat

self.costumeButton = self.GetChild2("CostumeButton")

#altına ekle

			if app.ENABLE_OFFLINE_SHOP_SYSTEM:
				self.OPSButton = self.GetChild2("OPSButton")
				self.OPSButton.ShowToolTip = lambda arg=1: self.OverInButton(arg)
				self.OPSButton.HideToolTip = lambda arg=1: self.OverOutButton()

			self.toolTip = uiToolTip.ToolTip()
			self.toolTip.ClearToolTip()

#arat

		if self.DSSButton:
			self.DSSButton.SetEvent(ui.__mem_func__(self.ClickDSSButton))

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if self.OPSButton:
				self.OPSButton.SetEvent(ui.__mem_func__(self.ClickOPSButton))

#arat

self.DSSButton = None

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.OPSButton = None

#arat

	def ClickDSSButton(self):
		print "click_dss_button"
		self.interface.ToggleDragonSoulWindow()

#altına ekle

	if app.ENABLE_OFFLINE_SHOP_SYSTEM:
		# OPSButton
		def ClickOPSButton(self):
			if constInfo.GET_ITEM_QUESTION_DIALOG_STATUS() == 1:
				return

			net.SendChatPacket("/open_offlineshop")

#arat

def __SendUseItemToItemPacket(self, srcSlotPos, dstSlotPos):

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if uiOfflineShopBuilder.IsBuildingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.USE_ITEM_FAILURE_PRIVATE_SHOP)
				return

			if uiOfflineShop.IsEditingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.USE_ITEM_FAILURE_PRIVATE_SHOP)
				return

#arat

def __SendUseItemPacket(self, slotPos):

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if uiOfflineShopBuilder.IsBuildingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.USE_ITEM_FAILURE_PRIVATE_SHOP)
				return

			if uiOfflineShop.IsEditingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.USE_ITEM_FAILURE_PRIVATE_SHOP)
				return

#arat

def __SendMoveItemPacket(self, srcSlotPos, dstSlotPos, srcItemCount):

#altına ekle

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			if uiOfflineShopBuilder.IsBuildingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.MOVE_ITEM_FAILURE_PRIVATE_SHOP)
				return

			if uiOfflineShop.IsEditingOfflineShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.MOVE_ITEM_FAILURE_PRIVATE_SHOP)
				return

#arat

def __InventoryLocalSlotPosToGlobalSlotPos(self, local):

#altına ekle

	def GetInventoryPageIndex(self):
		return self.inventoryPageIndex

	if app.WJ_ENABLE_TRADABLE_ICON:
		def RefreshMarkSlots(self, localIndex=None):
			if not self.interface:
				return

			onTopWnd = self.interface.GetOnTopWindow()
			if localIndex:
				if app.ENABLE_SPECIAL_INVENTORY:
					if self.inventoryTypeIndex == player.INVENTORY_TYPE_INVENTORY:
						slotNumber = self.__InventoryLocalSlotPosToGlobalSlotPos(localIndex)
					else:
						slotNumber = self.__SpecialInventoryLocalSlotPosToGlobalSlotPos(localIndex)
				else:
					slotNumber = self.__InventoryLocalSlotPosToGlobalSlotPos(localIndex)
					
				if onTopWnd == player.ON_TOP_WND_NONE:
					self.wndItem.SetUsableSlotOnTopWnd(localIndex)

				elif onTopWnd == player.ON_TOP_WND_SHOP:
					if player.IsAntiFlagBySlot(slotNumber, item.ANTIFLAG_SELL):
						self.wndItem.SetUnusableSlotOnTopWnd(localIndex)
					else:
						self.wndItem.SetUsableSlotOnTopWnd(localIndex)

				elif onTopWnd == player.ON_TOP_WND_EXCHANGE:
					if player.IsAntiFlagBySlot(slotNumber, item.ANTIFLAG_GIVE):
						self.wndItem.SetUnusableSlotOnTopWnd(localIndex)
					else:
						self.wndItem.SetUsableSlotOnTopWnd(localIndex)

				elif onTopWnd == player.ON_TOP_WND_PRIVATE_SHOP:
					if player.IsAntiFlagBySlot(slotNumber, item.ITEM_ANTIFLAG_MYSHOP):
						self.wndItem.SetUnusableSlotOnTopWnd(localIndex)
					else:
						self.wndItem.SetUsableSlotOnTopWnd(localIndex)

				elif onTopWnd == player.ON_TOP_WND_SAFEBOX:
					if player.IsAntiFlagBySlot(slotNumber, item.ANTIFLAG_SAFEBOX):
						self.wndItem.SetUnusableSlotOnTopWnd(localIndex)
					else:
						self.wndItem.SetUsableSlotOnTopWnd(localIndex)

				return

			for i in xrange(player.INVENTORY_PAGE_SIZE):
				if app.ENABLE_SPECIAL_INVENTORY:
					if self.inventoryTypeIndex == player.INVENTORY_TYPE_INVENTORY:
						slotNumber = self.__InventoryLocalSlotPosToGlobalSlotPos(i)
					else:
						slotNumber = self.__SpecialInventoryLocalSlotPosToGlobalSlotPos(i)
				else:
					slotNumber = self.__InventoryLocalSlotPosToGlobalSlotPos(i)	
						
				if onTopWnd == player.ON_TOP_WND_NONE:
					self.wndItem.SetUsableSlotOnTopWnd(i)

				elif onTopWnd == player.ON_TOP_WND_SHOP:
					if player.IsAntiFlagBySlot(slotNumber, item.ANTIFLAG_SELL):
						self.wndItem.SetUnusableSlotOnTopWnd(i)
					else:
						self.wndItem.SetUsableSlotOnTopWnd(i)

				elif onTopWnd == player.ON_TOP_WND_EXCHANGE:
					if player.IsAntiFlagBySlot(slotNumber, item.ANTIFLAG_GIVE):
						self.wndItem.SetUnusableSlotOnTopWnd(i)
					else:
						self.wndItem.SetUsableSlotOnTopWnd(i)

				elif onTopWnd == player.ON_TOP_WND_PRIVATE_SHOP:
					if player.IsAntiFlagBySlot(slotNumber, item.ITEM_ANTIFLAG_MYSHOP):
						self.wndItem.SetUnusableSlotOnTopWnd(i)
					else:
						self.wndItem.SetUsableSlotOnTopWnd(i)

				elif onTopWnd == player.ON_TOP_WND_SAFEBOX:
					if player.IsAntiFlagBySlot(slotNumber, item.ANTIFLAG_SAFEBOX):
						self.wndItem.SetUnusableSlotOnTopWnd(i)
					else:
						self.wndItem.SetUsableSlotOnTopWnd(i)

	def OverInButton(self, stat):
		if not self.toolTip:
			return

		if stat == 0:
			self.toolTip.ClearToolTip()
			self.toolTip.AlignHorizonalCenter()
			self.toolTip.AutoAppendNewTextLine(uiScriptLocale.OFFLINESHOP_BUTTON_TOOLTIP)
			self.toolTip.Show()

	def OverOutButton(self):
		if not self.toolTip:
			return
		
		self.toolTip.Hide()