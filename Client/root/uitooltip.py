#importlara ekle

if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
	import newPrivateShopSearch
if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
	import privateShopSearch

#arat

	def __init__(self, *args, **kwargs):
		ToolTip.__init__(self, *args, **kwargs)
		self.itemVnum = 0
		self.isShopItem = False

#altına ekle

		if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			self.isPrivateSearchItem = False
		
		if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			self.isnewPrivateSearchItem = (False, -1)

		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.isOfflineShopItem = (False, -1)

#arat

	def ClearToolTip(self):
		self.isShopItem = False

#altına ekle

		if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			self.isPrivateSearchItem = False
		if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			self.isnewPrivateSearchItem = (False, -1)
		if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			self.isOfflineShopItem = (False, -1)

#arat

def SetInventoryItem(self, slotIndex, window_type = player.INVENTORY):

#içinde arat

self.AppendSellingPrice(0)

#değiştir

			if not (item.GetItemType() == item.ITEM_TYPE_WEAPON and item.GetItemSubType() == item.WEAPON_ARROW):
				if app.ENABLE_OFFLINE_SHOP_SYSTEM and (not shop.IsPrivateShop() or not shop.IsOfflineShop()):
					self.AppendSellingPrice(player.GetISellItemPrice(window_type, slotIndex))
				else:
					if not shop.IsPrivateShop():
						item.SelectItem(itemVnum)
						self.AppendSellingPrice(player.GetISellItemPrice(window_type, slotIndex))
			else:
				self.AppendSellingPrice(0)

#arat

def SetPrivateShopBuilderItem(self, invenType, invenPos, privateShopSlotIndex):

#altına ekle

	if app.ENABLE_OFFLINE_SHOP_SYSTEM:
		def SetOfflineShopBuilderItem(self, invenType, invenPos, offlineShopSlotIndex):
			itemVnum = player.GetItemIndex(invenType, invenPos)
			if itemVnum == 0:
				return

			item.SelectItem(itemVnum)
			self.ClearToolTip()

			metinSlot = []
			for i in xrange(player.METIN_SOCKET_MAX_NUM):
				metinSlot.append(player.GetItemMetinSocket(invenPos, i))
			attrSlot = []
			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				attrSlot.append(player.GetItemAttribute(invenPos, i))

			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# self.AddItemData(itemVnum, metinSlot, attrSlot, 0, 0, invenType, invenPos)
			# else:
			self.AddItemData(itemVnum, metinSlot, attrSlot)
			
			# if app.ENABLE_CHEQUE_SYSTEM:
				# self.AppendSellingPrice(long(shop.GetOfflineShopItemPriceReal(invenType, invenPos)), shop.GetOfflineShopItemPriceChequeReal(invenType, invenPos), True)
			# else:
			self.AppendSellingPrice(long(shop.GetOfflineShopItemPriceReal(invenType, invenPos)))

		def SetOfflineShopItem(self, slotIndex):
			itemVnum = shop.GetOfflineShopItemID(slotIndex)
			if 0 == itemVnum:
				return

			price = shop.GetOfflineShopItemPrice(slotIndex)
			self.ClearToolTip()
			self.isOfflineShopItem = (True, slotIndex)

			metinSlot = []
			for i in xrange(player.METIN_SOCKET_MAX_NUM):
				metinSlot.append(shop.GetOfflineShopItemMetinSocket(slotIndex, i))
			attrSlot = []
			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				attrSlot.append(shop.GetOfflineShopItemAttribute(slotIndex, i))

			self.AddItemData(itemVnum, metinSlot, attrSlot)

			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# self.AppendChangeLookInfoOfflineShopWindow(slotIndex)

			# if app.ENABLE_CHEQUE_SYSTEM:
				# cheque = shop.GetOfflineShopItemPriceCheque(slotIndex)
				# self.AppendPrice(price, cheque)
			# else:
			self.AppendPrice(price)

			if shop.GetOfflineShopItemStatus(slotIndex) == 2:
				self.AppendTextLine(localeInfo.TOOLTIP_OFFLINE_SHOP_ITEM_SOLD, self.DISABLE_COLOR)
				self.AppendTextLine(localeInfo.TOOLTIP_OFFLINE_SHOP_ITEM_BUYER % (shop.GetOfflineShopItemBuyerName(slotIndex)), self.DISABLE_COLOR)

	# if app.ENABLE_CHANGE_LOOK_SYSTEM:
		# def AppendChangeLookInfoItemVnum(self, changelookvnum):
			# if not changelookvnum == 0:
				# self.AppendSpace(5)
				# self.AppendTextLine("[ " + localeInfo.CHANGE_LOOK_TITLE + " ]", self.CHANGELOOK_TITLE_COLOR)
				# itemName = item.GetItemNameByVnum(changelookvnum)

				# if item.GetItemType() == item.ITEM_TYPE_COSTUME:
					# if item.GetItemSubType() == item.COSTUME_TYPE_BODY:
						# malefemale = ""
						# if item.IsAntiFlag(item.ITEM_ANTIFLAG_MALE):
							# malefemale = localeInfo.FOR_FEMALE

						# if item.IsAntiFlag(item.ITEM_ANTIFLAG_FEMALE):
							# malefemale = localeInfo.FOR_MALE
						# itemName += " ( " + malefemale + " )"

				# textLine = self.AppendTextLine(itemName, self.CHANGELOOK_ITEMNAME_COLOR, True)
				# textLine.SetFeather()

		# if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			# def AppendChangeLookInfoPrivateShopWIndow(self, slotIndex):
				# changelookvnum = privateShopSearch.GetSearchItemTransmutation(slotIndex)
				# if not changelookvnum == 0:
					# self.AppendSpace(5)
					# self.AppendTextLine("[ " + localeInfo.CHANGE_LOOK_TITLE + " ]", self.CHANGELOOK_TITLE_COLOR)
					# itemName = item.GetItemNameByVnum(changelookvnum)

					# if item.GetItemType() == item.ITEM_TYPE_COSTUME:
						# if item.GetItemSubType() == item.COSTUME_TYPE_BODY:
							# malefemale = ""
							# if item.IsAntiFlag(item.ITEM_ANTIFLAG_MALE):
								# malefemale = localeInfo.FOR_FEMALE

							# if item.IsAntiFlag(item.ITEM_ANTIFLAG_FEMALE):
								# malefemale = localeInfo.FOR_MALE
							# itemName += " ( " + malefemale + " )"

					# textLine = self.AppendTextLine(itemName, self.CHANGELOOK_ITEMNAME_COLOR, True)
					# textLine.SetFeather()
		
		# if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			# def AppendChangeLookInfoNewPrivateShopWIndow(self, slotIndex):
				# changelookvnum = newPrivateShopSearch.GetSearchItemTransmutation(slotIndex)
				# if not changelookvnum == 0:
					# self.AppendSpace(5)
					# self.AppendTextLine("[ " + localeInfo.CHANGE_LOOK_TITLE + " ]", self.CHANGELOOK_TITLE_COLOR)
					# itemName = item.GetItemNameByVnum(changelookvnum)

					# if item.GetItemType() == item.ITEM_TYPE_COSTUME:
						# if item.GetItemSubType() == item.COSTUME_TYPE_BODY:
							# malefemale = ""
							# if item.IsAntiFlag(item.ITEM_ANTIFLAG_MALE):
								# malefemale = localeInfo.FOR_FEMALE

							# if item.IsAntiFlag(item.ITEM_ANTIFLAG_FEMALE):
								# malefemale = localeInfo.FOR_MALE
							# itemName += " ( " + malefemale + " )"

					# textLine = self.AppendTextLine(itemName, self.CHANGELOOK_ITEMNAME_COLOR, True)
					# textLine.SetFeather()

		# def AppendChangeLookInfoShopWindow(self, slotIndex):
			# changelookvnum = shop.GetItemTransmutation(slotIndex)
			# if not changelookvnum == 0:
				# self.AppendSpace(5)
				# self.AppendTextLine("[ " + localeInfo.CHANGE_LOOK_TITLE + " ]", self.CHANGELOOK_TITLE_COLOR)
				# itemName = item.GetItemNameByVnum(changelookvnum)

				# if item.GetItemType() == item.ITEM_TYPE_COSTUME:
					# if item.GetItemSubType() == item.COSTUME_TYPE_BODY:
						# malefemale = ""
						# if item.IsAntiFlag(item.ITEM_ANTIFLAG_MALE):
							# malefemale = localeInfo.FOR_FEMALE

						# if item.IsAntiFlag(item.ITEM_ANTIFLAG_FEMALE):
							# malefemale = localeInfo.FOR_MALE
						# itemName += " ( " + malefemale + " )"

				# textLine = self.AppendTextLine(itemName, self.CHANGELOOK_ITEMNAME_COLOR, True)
				# textLine.SetFeather()

		# if app.ENABLE_OFFLINE_SHOP_SYSTEM:
			# def AppendChangeLookInfoOfflineShopWindow(self, slotIndex):
				# changelookvnum = shop.GetOfflineShopItemTransmutation(slotIndex)
				# if not changelookvnum == 0:
					# self.AppendSpace(5)
					# self.AppendTextLine("[ " + localeInfo.CHANGE_LOOK_TITLE + " ]", self.CHANGELOOK_TITLE_COLOR)
					# itemName = item.GetItemNameByVnum(changelookvnum)

					# if item.GetItemType() == item.ITEM_TYPE_COSTUME:
						# if item.GetItemSubType() == item.COSTUME_TYPE_BODY:
							# malefemale = ""
							# if item.IsAntiFlag(item.ITEM_ANTIFLAG_MALE):
								# malefemale = localeInfo.FOR_FEMALE

							# if item.IsAntiFlag(item.ITEM_ANTIFLAG_FEMALE):
								# malefemale = localeInfo.FOR_MALE
							# itemName += " ( " + malefemale + " )"

					# textLine = self.AppendTextLine(itemName, self.CHANGELOOK_ITEMNAME_COLOR, True)
					# textLine.SetFeather()

#arat

def SetInventoryItem(self, slotIndex, window_type = player.INVENTORY):

#altına ekle

	if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
		def SetPrivateSearchItem(self, slotIndex):
			itemVnum = privateShopSearch.GetSearchItemVnum(slotIndex)

			if 0 == itemVnum:
				return

			self.ClearToolTip()
			self.isPrivateSearchItem = True

			metinSlot = []
			for i in xrange(player.METIN_SOCKET_MAX_NUM):
				metinSlot.append(privateShopSearch.GetSearchItemMetinSocket(slotIndex, i))
			attrSlot = []
			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				attrSlot.append(privateShopSearch.GetSearchItemAttribute(slotIndex, i))

			self.AddItemData(itemVnum, metinSlot, attrSlot)

			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# self.AppendChangeLookInfoPrivateShopWIndow(slotIndex)

	if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
		def SetNewPrivateSearchItem(self, slotIndex):
			itemVnum = newPrivateShopSearch.GetSearchItemVnum(slotIndex)

			if 0 == itemVnum:
				return

			self.ClearToolTip()
			self.isnewPrivateSearchItem = (True, slotIndex)

			metinSlot = []
			for i in xrange(player.METIN_SOCKET_MAX_NUM):
				metinSlot.append(newPrivateShopSearch.GetSearchItemMetinSocket(slotIndex, i))
			attrSlot = []
			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				attrSlot.append(newPrivateShopSearch.GetSearchItemAttribute(slotIndex, i))

			self.AddItemData(itemVnum, metinSlot, attrSlot)

			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# self.AppendChangeLookInfoNewPrivateShopWIndow(slotIndex)

#arat

		if self.__IsHair(itemVnum):
			self.__AppendHairIcon(itemVnum)

#altına ekle

		if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			if self.isPrivateSearchItem:
				if not self.__IsHair(itemVnum):
					self.__AppendPrivateSearchItemIcon(itemVnum)

#arat

	def __IsNewHair3(self, itemVnum):
		return ((74012 < itemVnum and itemVnum < 74022) or
			(74262 < itemVnum and itemVnum < 74272) or
			(74512 < itemVnum and itemVnum < 74599) or
			(74762 < itemVnum and itemVnum < 74799) or
			(45000 < itemVnum and itemVnum < 47000))

#altına ekle

	if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
		def __AppendPrivateSearchItemIcon(self, itemVnum):
			itemImage = ui.ImageBox()
			itemImage.SetParent(self)
			itemImage.Show()
			item.SelectItem(itemVnum)
			itemImage.LoadImage(item.GetIconImageFileName())
			itemImage.SetPosition((self.toolTipWidth / 2) - 16, self.toolTipHeight)
			self.toolTipHeight += itemImage.GetHeight()
			self.childrenList.append(itemImage)
			self.ResizeToolTip()

#arat

itemImage.SetPosition(itemImage.GetWidth()/2, self.toolTipHeight)

#değiştir

		if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			if self.isPrivateSearchItem:
				itemImage.SetPosition((self.toolTipWidth / 2) - 48, self.toolTipHeight)
			else:
				itemImage.SetPosition((self.toolTipWidth / 2) - 48, self.toolTipHeight)
		else:
			itemImage.SetPosition(itemImage.GetWidth() / 2, self.toolTipHeight)