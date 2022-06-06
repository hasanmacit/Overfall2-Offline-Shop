import app
import player
import net
import chr
import chat
import item
import shop
import wndMgr
import grp
import snd
import systemSetting
import ui
import mouseModule
import uiCommon
import localeInfo
import constInfo
import interfaceModule
import uiPickMoney
import uiToolTip
import uiOfflineShopBuilder
import renderTarget
from _weakref import proxy
import time

PREMIUM_IMAGES = ["d:/ymir work/ui/pattern/visible_mark_03.tga", "d:/ymir work/ui/pattern/visible_mark_01.tga"]

g_isEditingOfflineShop = False
g_iRefreshDelay = 5000
SHOP_SIGN_MAX_LEN = 32

def minmax(x, y, z):
	if y > z:	return z
	elif y < x:	return x
	return y

def Clear():
	global g_isEditingOfflineShop
	g_isEditingOfflineShop = False

def IsEditingOfflineShop():
	global g_isEditingOfflineShop
	if g_isEditingOfflineShop:
		return True
	else:
		return False

if app.WJ_ENABLE_TRADABLE_ICON:
	INVENTORY_PAGE_SIZE = player.INVENTORY_PAGE_SIZE
	# if app.ENABLE_SPECIAL_INVENTORY_SYSTEM:
		# SPECIAL_INVENTORY_PAGE_SIZE = player.SPECIAL_INVENTORY_PAGE_SIZE


class Animation(object):
	def __init__(self, element, mainElement, animateSteps = 20, animateTime = 0.01):
		self.element = element
		self.mainElement = mainElement
		self.animateTime = animateTime
		self.animateSteps = animateSteps

		self.animateEvent = None
		self.animateWidth = 0
		self.animateCurrentWidth = 0
		self.animateHeight = 0
		self.animateCurrentHeight = 0
		self.animateStartTime = 0
		self.animateEndEvent = None

	def Destroy(self):
		self.element = None

	def Enlarge(self, startWidth = 60, startHeight = 60, endEvent = None):
		self.animateWidth = self.mainElement.GetWidth()
		self.animateCurrentWidth = startWidth
		self.animateHeight = self.mainElement.GetHeight()
		self.animateCurrentHeight = startHeight
		self.animateStartTime = 0
		self.animateEndEvent = endEvent

		self.animateEvent = self.EnlargeEvent

		self.element.SetSize(0, 0)
		
		self.element.Show()

	def Shrink(self, endWidth = 60, endHeight = 60):
		self.animateWidth = endWidth
		self.animateCurrentWidth =  self.mainElement.GetWidth()
		self.animateHeight = endHeight
		self.animateCurrentHeight =  self.mainElement.GetHeight()
		self.animateStartTime = 0

		self.animateEvent = self.ShrinkEvent

		self.element.SetSize(self.mainElement.GetWidth(),  self.mainElement.GetHeight())
		self.element.Show()

	def EnlargeEvent(self):
		if self.animateCurrentWidth + self.animateSteps < self.animateWidth and self.animateCurrentHeight + self.animateSteps < self.animateHeight:
			self.animateCurrentWidth += self.animateSteps
			self.animateCurrentHeight += self.animateSteps

			x, y = self.mainElement.GetGlobalPosition()

			self.element.SetPosition(x + (self.animateWidth - self.animateCurrentWidth)/2, y + (self.animateHeight - self.animateCurrentHeight)/2)
			self.element.SetSize(self.animateCurrentWidth, self.animateCurrentHeight)
			
		else:
			self.animateEvent = None
			self.element.Hide()
			if self.animateEndEvent:
				self.animateEndEvent()

	def ShrinkEvent(self):
		if self.animateCurrentWidth - self.animateSteps > self.animateWidth and self.animateCurrentHeight - self.animateSteps > self.animateHeight:
			self.animateCurrentWidth -= self.animateSteps
			self.animateCurrentHeight -= self.animateSteps
			
			x, y = self.mainElement.GetGlobalPosition()

			self.element.SetPosition(x + ( self.mainElement.GetWidth() - self.animateCurrentWidth)/2, y + ( self.mainElement.GetHeight() - self.animateCurrentHeight)/2)
			self.element.SetSize(self.animateCurrentWidth, self.animateCurrentHeight)
		else:
			self.animateEvent = None
			self.element.Hide()

	def OnUpdate(self):
		if self.animateEvent:
			if self.animateStartTime < time.clock():
				self.animateStartTime = time.clock() + self.animateTime
				self.animateEvent()
					
class BoardAnimation(ui.Board):
	def __init__(self, mainBoardElement):
		ui.Board.__init__(self)
		self.mainBoardElement = mainBoardElement
		x, y = self.mainBoardElement.GetGlobalPosition()
		self.SetSize(self.mainBoardElement.GetWidth(), self.mainBoardElement.GetHeight())
		self.SetPosition(x,y)
		self.animation = Animation(self, mainBoardElement, animateSteps = 30, animateTime = 0.01)

	def __del__(self):
		ui.Board.__del__(self)

	def Enlarge(self):
		self.animation.Enlarge(endEvent = self.mainBoardElement.Show)

	def Shrink(self):
		self.mainBoardElement.Hide()
		self.animation.Shrink()

	def Destroy(self):
		self.mainBoardElement = None
		self.board = None

	def OnUpdate(self):
		self.animation.OnUpdate()
###################################################################################################
## Offline Shop Sales
class SaleWindowObject(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.SetSize(319, 32)
		
		self.__Initialize()
		self.__LoadWindow()
	
	def __Initialize(self):
		self.buyerName = ""
		self.itemVnum = 0
		self.count = 0
		self.price = 0
		self.date = 0
		
		self.wndBaseImage = None
		self.txtItemName = None
		self.txtTime = None
		self.txtPrice = None
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def DestroyObject(self):
		self.ClearDictionary()
		self.Close()
	
	def __LoadWindow(self):
		self.wndBaseImage = ui.MakeImageBox(self, "d:/ymir work/ui/offshop/sales_window/history_image.tga", 0, 0)
		self.wndBaseImage.Show()

		self.txtItemName = ui.MakeTextLine(self.wndBaseImage)
		self.txtItemName.SetPosition(7, 0)
		self.txtItemName.SetWindowHorizontalAlignLeft()
		self.txtItemName.SetHorizontalAlignLeft()
		self.txtItemName.SetWindowVerticalAlignCenter()

		self.txtTime = ui.MakeTextLine(self.wndBaseImage)
		self.txtTime.SetPosition(132, 0)
		self.txtTime.SetWindowHorizontalAlignLeft()
		self.txtTime.SetHorizontalAlignLeft()
		self.txtTime.SetWindowVerticalAlignCenter()

		self.txtPrice = ui.MakeTextLine(self.wndBaseImage)
		self.txtPrice.SetPosition(7, 0)
		self.txtPrice.SetWindowHorizontalAlignRight()
		self.txtPrice.SetHorizontalAlignRight()
		self.txtPrice.SetWindowVerticalAlignCenter()
	
	def SetInformation(self, buyerName, itemVnum, count, price, date):
		self.buyerName = buyerName
		self.itemVnum = itemVnum
		self.count = count
		self.price = price
		self.date = date
		
		self.RefreshInformation()
	
	def RefreshInformation(self):
		if self.itemVnum == 0:
			return
		
		item.SelectItem(self.itemVnum)
		self.txtItemName.SetText(item.GetItemName())
		if self.__ChangeColor() is True:
			self.txtItemName.SetPackedFontColor(grp.GenerateColor(1.0, 0.7843, 0.0, 1.0))
		else:
			self.txtItemName.SetPackedFontColor(grp.GenerateColor(0.9490, 0.9058, 0.7568, 1.0))
		
		self.txtTime.SetText(str(self.FormatSecToDate(self.date)))
		self.txtPrice.SetText("{} |Eoutras_imagens/money|e".format(localeInfo.NumberToDecimalString(self.price)))
		self.txtPrice.SetPackedFontColor(self.__GetYangTextColor())
	
	def FormatSecToDate(self, time):
		import datetime
		return (
			datetime.datetime.fromtimestamp(
				int(time)
			).strftime("%d %b. %H:%M")
		)
	
	def __ChangeColor(self):
		if self.itemVnum == 0:
			return False
		
		item.SelectItem(self.itemVnum)
		if item.GetItemType() == item.ITEM_TYPE_WEAPON or item.GetItemType() == item.ITEM_TYPE_ARMOR:
			return True
		
		return False
	
	def __GetYangTextColor(self):
		if self.price < 500000000:
			return grp.GenerateColor(0.7, 0.7, 0.7, 1.0)
		elif self.price < 1000000000:
			return grp.GenerateColor( (255.0/255.0), (153.0/255.0), (51.0/255.0), 1.0)
		elif self.price < 10000000000:
			return grp.GenerateColor( (153.0/255.0), (76.0/255.0), (0.0/255.0), 1.0)
		else:
			return grp.GenerateColor( (255.0/255.0), (51.0/255.0), (51.0/255.0), 1.0)
	
	def Close(self):
		self.Hide()
	
	def ShowObject(self):
		self.Show()

###################################################################################################
## Open Offline Shop
class OpenOfflineShop(ui.ScriptWindow):
	RENDER_TARGET_INDEX = 2
	RENDER_TARGET_INDEX_BOARD = 3

	d_Models = {
		0 : {"npc_vnum" : 30000, "type_name" : localeInfo.OFFLINE_SHOP_CREATE_SHOP_STYLE1, "need_premium" : False},
		1 : {"npc_vnum" : 30002, "type_name" : localeInfo.OFFLINE_SHOP_CREATE_SHOP_STYLE2, "need_premium" : True},
		2 : {"npc_vnum" : 30003, "type_name" : localeInfo.OFFLINE_SHOP_CREATE_SHOP_STYLE3, "need_premium" : True},
		3 : {"npc_vnum" : 30004, "type_name" : localeInfo.OFFLINE_SHOP_CREATE_SHOP_STYLE4, "need_premium" : True},
		4 : {"npc_vnum" : 30005, "type_name" : localeInfo.OFFLINE_SHOP_CREATE_SHOP_STYLE5, "need_premium" : True},
		5 : {"npc_vnum" : 30006, "type_name" : localeInfo.OFFLINE_SHOP_CREATE_SHOP_STYLE6, "need_premium" : True},
		6 : {"npc_vnum" : 30007, "type_name" : localeInfo.OFFLINE_SHOP_CREATE_SHOP_STYLE7, "need_premium" : True},
		7 : {"npc_vnum" : 30008, "type_name" : localeInfo.OFFLINE_SHOP_CREATE_SHOP_STYLE8, "need_premium" : True},
	}
	modelsCount = len(d_Models)

	d_BoardModels = {
		0 : {"image_board" : "", "type_name" : localeInfo.OFFLINE_SHOP_CREATE_BOARD_SHOP_STYLE1, "need_premium" : False},
		1 : {"image_board" : "fire", "type_name" : localeInfo.OFFLINE_SHOP_CREATE_BOARD_SHOP_STYLE2, "need_premium" : True},
		2 : {"image_board" : "ice", "type_name" : localeInfo.OFFLINE_SHOP_CREATE_BOARD_SHOP_STYLE3, "need_premium" : True},
		3 : {"image_board" : "paper", "type_name" : localeInfo.OFFLINE_SHOP_CREATE_BOARD_SHOP_STYLE4, "need_premium" : True},
		4 : {"image_board" : "ribon", "type_name" : localeInfo.OFFLINE_SHOP_CREATE_BOARD_SHOP_STYLE5, "need_premium" : True},
		5 : {"image_board" : "wing", "type_name" : localeInfo.OFFLINE_SHOP_CREATE_BOARD_SHOP_STYLE6, "need_premium" : True},
	}
	modelsBoardCount = len(d_BoardModels)
	
	premium_cfg = {
		"shop_time" : {0 : 3, 1 : 7},
		"shop_price" : {0 : 5000000, 1 : 5000000}
	}
	
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__Initialize()
		self.__LoadWindow()
	
	def __Initialize(self):
		self.interface = None
		
		self.v_pagesWindow = { page : {"page" : None, "button" : None} for page in xrange(2)}
		
		self.shop_type_text = None
		self.ModelPreview = None
		self.BoardPreview = None
		
		self.shop_type_block_state = None
		
		self.prev_style_btn = None
		self.next_style_btn = None
		
		self.overfall2_premium = None
		
		self.shop_time_create_value = None
		self.shop_cost_create_value = None
		
		self.shop_board_type_text = None
		self.shop_board_type_block_state = None
		
		self.create_shop_button = None
		self.exit_shop_create_button = None
		
		self.shop_name_el = None
		
		self.create_shop_time_type = 0
		self.actual_shop_type = 0
		self.actual_board_type = 0
		
		self.actual_choose_type = 0
		self.boardAnimation = None
		self.board_type_image = None
	
	def BindInterface(self, interface):
		self.interface = proxy(interface)
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/OfflineShopCreateDialog.py")
		except:
			import exception
			exception.Abort("OpenOfflineShop.LoadWindow.LoadObject")
		
		try:
			GetObject = self.GetChild
			
			self.v_pagesWindow[0]["page"] = GetObject("base_image")
			self.v_pagesWindow[0]["button"] = GetObject("page_model_button")

			self.v_pagesWindow[1]["page"] = GetObject("base_board_image")
			self.v_pagesWindow[1]["button"] = GetObject("page_board_button")
			
			self.shop_type_text = GetObject("shop_type_text")
			self.shop_type_block_state = GetObject("shop_type_block_state")
			
			self.shop_board_type_text = GetObject("shop_board_type_text")
			self.shop_board_type_block_state = GetObject("shop_board_type_block_state")
			
			self.shop_name_el = GetObject("shop_name_el")
			self.shop_name_el.SetPlaceHolder(localeInfo.OFFLINE_SHOP_CREATE_SHOP_PLACEHOLDER, (4, 0))
			self.shop_name_el.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))
			self.shop_name_el.SetMax(SHOP_SIGN_MAX_LEN)
			self.shop_name_el.SetMaxSizeMode()
			self.shop_name_el.SetFocus()
			
			self.prev_style_btn = GetObject("prev_style_btn")
			self.next_style_btn = GetObject("next_style_btn")

			self.prev_board_style_btn = GetObject("prev_board_style_btn")
			self.next_board_style_btn = GetObject("next_board_style_btn")
			
			self.create_shop_button = GetObject("create_shop_button")
			self.exit_shop_create_button = GetObject("exit_shop_create_button")
			
			self.overfall2_premium = GetObject("overfall2_premium")
			
			self.shop_time_create_value = GetObject("shop_time_create_value")
			self.shop_time_create_value.SetPosition(5 + GetObject("shop_time_create_base").GetTextSize()[0], 0)
			self.shop_cost_create_value = GetObject("shop_cost_create_value")
			self.shop_cost_create_value.SetPosition(5 + GetObject("shop_cost_create_base").GetTextSize()[0], 0)

			self.ModelPreview = ui.RenderTarget()
			self.ModelPreview.SetParent(self.v_pagesWindow[0]["page"])
			self.ModelPreview.SetWindowHorizontalAlignCenter()
			self.ModelPreview.SetSize(190, 210)
			self.ModelPreview.SetPosition(0, 65)
			self.ModelPreview.SetRenderTarget(self.RENDER_TARGET_INDEX)
			self.ModelPreview.Show()

			self.BoardPreview = ui.RenderTarget()
			self.BoardPreview.SetParent(self.v_pagesWindow[1]["page"])
			self.BoardPreview.SetWindowHorizontalAlignCenter()
			self.BoardPreview.SetSize(190, 210)
			self.BoardPreview.SetPosition(0, 65)
			self.BoardPreview.SetRenderTarget(self.RENDER_TARGET_INDEX_BOARD)
			self.BoardPreview.Show()

			self.boardAnimation = BoardAnimation(self)

		except:
			import exception
			exception.Abort("OpenOfflineShop.LoadWindow.BindObject")

		self.create_shop_button.SetEvent(ui.__mem_func__(self.OpenShop))
		self.exit_shop_create_button.SetEvent(ui.__mem_func__(self.Close))
		renderTarget.SetBackground(self.RENDER_TARGET_INDEX, "d:/ymir work/ui/game/myshop_deco/model_view_bg.sub")
		renderTarget.SetBackground(self.RENDER_TARGET_INDEX_BOARD, "d:/ymir work/ui/game/myshop_deco/model_view_bg.sub")
		self.prev_style_btn.SetEvent(ui.__mem_func__(self.PrevStyle))
		self.next_style_btn.SetEvent(ui.__mem_func__(self.NextStyle))
		self.prev_board_style_btn.SetEvent(ui.__mem_func__(self.PrevBoardStyle))
		self.next_board_style_btn.SetEvent(ui.__mem_func__(self.NextBoardStyle))
		
		self.v_pagesWindow[0]["button"].SetEvent(ui.__mem_func__(self.ReloadActualChooseType), 0)
		self.v_pagesWindow[1]["button"].SetEvent(ui.__mem_func__(self.ReloadActualChooseType), 1)
		
		self.ReloadActualChooseType(self.actual_choose_type)
	
	def __GetPlayerPremium(self):
		return chr.IsOverfallPremium()
	
	def __HaveShopStyleAcess(self):
		type_premium = self.d_Models[self.actual_shop_type]["need_premium"]
		
		if type_premium is False:
			return True
		else:
			if type_premium == self.__GetPlayerPremium():
				return True
		
		return False
	
	def __HaveBoardStyleAcess(self):
		type_premium = self.d_BoardModels[self.actual_board_type]["need_premium"]
		
		if type_premium is False:
			return True
		else:
			if type_premium == self.__GetPlayerPremium():
				return True
		
		return False
	
	def ReloadConfigurations(self):
		isPremium = int(self.__GetPlayerPremium())
		shop_time, shop_price = self.premium_cfg["shop_time"][isPremium], self.premium_cfg["shop_price"][isPremium]
		self.create_shop_time_type = isPremium
		
		self.shop_time_create_value.SetText("{} Gün |Eoutras_imagens/clock_ore|e".format(shop_time))
		self.shop_cost_create_value.SetText("{} |Eoutras_imagens/money|e".format(localeInfo.NumberToDecimalString(shop_price)))
		
		if self.shop_name_el:
			self.shop_name_el.SetFocus()
			self.shop_name_el.SetText("")
			self.shop_name_el.UpdatePlaceHolder()
		
		self.actual_shop_type = 0
		self.actual_board_type = 0
		self.actual_choose_type = 0
		
		self.ReloadActualChooseType(self.actual_choose_type)
		
	def ReloadModelPreview(self):
		npc_vnum, type_name = self.d_Models[self.actual_shop_type]["npc_vnum"], self.d_Models[self.actual_shop_type]["type_name"]
		
		canUseStyle = self.__HaveShopStyleAcess()
		blockStyleColor = grp.GenerateColor((255.0/255.0), (153.0/255.0), (51.0/255.0), 1.0)
		desblockStyleColor = grp.GenerateColor((255.0/255.0), (204.0/255.0), (153.0/255.0), 1.0)
		
		self.shop_type_block_state.SetText(localeInfo.OFFLINE_SHOP_STYLE_DESBLOCK_STATE if canUseStyle is True else localeInfo.OFFLINE_SHOP_STYLE_BLOCK_STATE)
		self.shop_type_block_state.SetPackedFontColor(desblockStyleColor if canUseStyle is True else blockStyleColor)
		self.shop_type_text.SetText(str(type_name))

		renderTarget.SetVisibility(self.RENDER_TARGET_INDEX, True)
		renderTarget.SelectModel(self.RENDER_TARGET_INDEX, npc_vnum)
		renderTarget.ChangeEffect(self.RENDER_TARGET_INDEX)
		renderTarget.SetVisibility(self.RENDER_TARGET_INDEX_BOARD, True)
		renderTarget.SelectModel(self.RENDER_TARGET_INDEX_BOARD, npc_vnum)
		renderTarget.ChangeEffect(self.RENDER_TARGET_INDEX_BOARD)

	def PrevStyle(self):
		if self.actual_shop_type <= 0:
			self.actual_shop_type = self.modelsCount
		
		self.actual_shop_type -= 1
		self.ReloadModelPreview()
	
	def NextStyle(self):
		if self.actual_shop_type >= (self.modelsCount - 1):
			self.actual_shop_type = -1
		
		self.actual_shop_type += 1
		self.ReloadModelPreview()
	
	def ReloadBorderPreview(self):
		paper_name, type_name = self.d_BoardModels[self.actual_board_type]["image_board"], self.d_BoardModels[self.actual_board_type]["type_name"]

		canUseBoard = self.__HaveBoardStyleAcess()
		blockStyleColor = grp.GenerateColor((255.0/255.0), (153.0/255.0), (51.0/255.0), 1.0)
		desblockStyleColor = grp.GenerateColor((255.0/255.0), (204.0/255.0), (153.0/255.0), 1.0)

		self.shop_board_type_block_state.SetText(localeInfo.OFFLINE_SHOP_STYLE_DESBLOCK_STATE if canUseBoard is True else localeInfo.OFFLINE_SHOP_STYLE_BLOCK_STATE)
		self.shop_board_type_block_state.SetPackedFontColor(desblockStyleColor if canUseBoard is True else blockStyleColor)
		self.shop_board_type_text.SetText(str(type_name))
		
		if self.board_type_image:
			self.board_type_image.Hide()
			self.board_type_image = None
		
		if len(paper_name) > 0:
			size = 50
			self.board_type_image = ui.ShopDecoration()
			self.board_type_image.MakeBoard(paper_name)
			self.board_type_image.SetParent(self.BoardPreview)
			self.board_type_image.SetWindowHorizontalAlignCenter()
			self.board_type_image.SetSize(size)
			self.board_type_image.SetPosition(0, 15)
			self.board_type_image.Show()
		else:
			self.board_type_image = ui.ThinBoard()
			self.board_type_image.SetParent(self.BoardPreview)
			self.board_type_image.SetWindowHorizontalAlignCenter()
			self.board_type_image.SetSize(100, 20)
			self.board_type_image.SetPosition(0, 30)
			self.board_type_image.Show()
	
	def PrevBoardStyle(self):
		if self.actual_board_type <= 0:
			self.actual_board_type = self.modelsBoardCount
		
		self.actual_board_type -= 1
		self.ReloadBorderPreview()
	
	def NextBoardStyle(self):
		if self.actual_board_type >= (self.modelsBoardCount - 1):
			self.actual_board_type = -1
		
		self.actual_board_type += 1
		self.ReloadBorderPreview()
	
	def OnUpdate(self):
		isPremium = int(self.__GetPlayerPremium())
		
		if self.overfall2_premium:
			self.overfall2_premium.LoadImage(PREMIUM_IMAGES[isPremium])

		shop_time, shop_price = self.premium_cfg["shop_time"][isPremium], self.premium_cfg["shop_price"][isPremium]
		self.create_shop_time_type = isPremium
		self.shop_time_create_value.SetText("{} Gün |Eoutras_imagens/clock_ore|e".format(shop_time))

		canUseStyle = self.__HaveShopStyleAcess()
		canUseBoard = self.__HaveBoardStyleAcess()
		blockStyleColor = grp.GenerateColor((255.0/255.0), (153.0/255.0), (51.0/255.0), 1.0)
		desblockStyleColor = grp.GenerateColor((255.0/255.0), (204.0/255.0), (153.0/255.0), 1.0)
		
		self.shop_type_block_state.SetText(localeInfo.OFFLINE_SHOP_STYLE_DESBLOCK_STATE if canUseStyle is True else localeInfo.OFFLINE_SHOP_STYLE_BLOCK_STATE)
		self.shop_type_block_state.SetPackedFontColor(desblockStyleColor if canUseStyle is True else blockStyleColor)
		
		self.shop_board_type_block_state.SetText(localeInfo.OFFLINE_SHOP_STYLE_DESBLOCK_STATE if canUseBoard is True else localeInfo.OFFLINE_SHOP_STYLE_BLOCK_STATE)
		self.shop_board_type_block_state.SetPackedFontColor(desblockStyleColor if canUseBoard is True else blockStyleColor)
		
	def OpenShop(self):
		if len(self.shop_name_el.GetText()) <= 0:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_CREATE_DONT_HAVE_NAME)
			return
		
		if len(self.shop_name_el.GetText()) < 3:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_CREATE_SMALL_SHOP_NAME)
			return
		
		if not self.d_Models.has_key(self.actual_shop_type):
			return
		
		if not self.d_BoardModels.has_key(self.actual_board_type):
			return
		
		if self.create_shop_time_type > 1 or self.create_shop_time_type < 0:
			return
		
		isPremium = int(self.__GetPlayerPremium())
		if player.GetElk() < self.premium_cfg["shop_price"][isPremium]:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_OPEN_NO_MONEY % int(self.premium_cfg["shop_time"][isPremium]))
			return
		
		if self.__HaveShopStyleAcess() is False:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_DONT_HAVE_SHOP_STYLE)
			return
		
		if self.__HaveBoardStyleAcess() is False:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_DONT_HAVE_BOARD_SHOP_STYLE)
			return
		
		shop_name = self.shop_name_el.GetText()
		if self.interface:
			self.interface.OpenOfflineShopBuilder(shop_name, self.actual_shop_type, self.actual_board_type)
	
	def ReloadActualChooseType(self, chooseType):
		for index in xrange(len(self.v_pagesWindow)):
			page = self.v_pagesWindow[index]["page"]
			button = self.v_pagesWindow[index]["button"]
			if index == chooseType:
				button.Down()
				page.Show()
			else:
				button.SetUp()
				page.Hide()

		self.actual_choose_type = chooseType
	
	def Open(self):
		self.SetCenterPosition()
		self.SetTop()
		self.Show()
		
		self.ReloadConfigurations()
		self.ReloadModelPreview()
		self.ReloadBorderPreview()
		self.boardAnimation.Enlarge()
	
	def Close(self):
		if self.interface:
			self.interface.CloseOfflineShopCreateDialog()

		self.boardAnimation.Shrink()

	def OnPressEscapeKey(self):
		self.Close()
		return True
	
	def OnPressExitKey(self):
		self.Close()
		return True

###################################################################################################
## Offline Shop Manager
class OfflineShopManagerWindow(ui.ScriptWindow):
	class TextToolTip(ui.Window):
		def __init__(self):
			ui.Window.__init__(self, "TOP_MOST")
			self.SetWindowName("GiftBox")
			textLine = ui.TextLine()
			textLine.SetParent(self)
			textLine.SetHorizontalAlignCenter()
			textLine.SetOutline()
			textLine.Show()
			self.textLine = textLine

		def __del__(self):
			ui.Window.__del__(self)

		def SetText(self, text):
			self.textLine.SetText(text)

		def OnRender(self):
			(mouseX, mouseY) = wndMgr.GetMousePosition()
			self.textLine.SetPosition(mouseX, mouseY - 15)
	
	TIME_COLOR = grp.GenerateColor((224.0/255.0), (126.0/255.0), 0.0 ,1.0)
	
	def __init__(self):
		ui.ScriptWindow.__init__(self)

		self.tooltipItem = None
		self.priceInputBoard = None
		self.boardAnimation = None
		self.inputDialog = None
		self.questionDialog = None
		self.changePriceInput = None
		self.openDialog = None
		self.title = ""
		self.interface = None
		self.shopTime = None

		if app.WJ_ENABLE_TRADABLE_ICON:
			self.inven = None
			# if app.ENABLE_SPECIAL_INVENTORY_SYSTEM:
				# self.invenSpecial = None
		
		self.__Initialize()
		self.__LoadWindow()
		self.boardAnimation = BoardAnimation(self)

	def __Initialize(self):
		self.isOpen = 0
		self.actual_category_page = 0
		self.category_buttons = { cat_number : {"cat_main_window" : None, "cat_button_object" : None} for cat_number in xrange(3)}
		
		self.sales_info_obj = []
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)

		if app.WJ_ENABLE_TRADABLE_ICON:
			self.inven = None
			# if app.ENABLE_SPECIAL_INVENTORY_SYSTEM:
				# self.invenSpecial = None
	
	def Destroy(self):
		self.ClearDictionary()
		self.Close()
		
		self.itemSlotWindow = None
		self.titleBar = None
		self.priceInputBoard = None
		self.boardAnimation = None
		self.inputDialog = None
		self.questionDialog = None
		self.changePriceInput = None
		self.openDialog = None

		self.dlgPickMoney.Destroy()
		self.dlgPickMoney = 0

		self.wndMoney = None
		self.btnMoney = None
		
		self.isOpen = 0
	
	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/OfflineShopManagerDialog.py")
		except:
			import exception
			exception.Abort("OfflineShopManagerWindow.LoadWindow.LoadObject")

		try:
			GetObject = self.GetChild
			self.titleBar = GetObject("TitleBar")
			
			#Common header
			self.category_buttons[0]["cat_main_window"] = GetObject("shop_category_window")
			self.category_buttons[0]["cat_button_object"] = GetObject("shop_cat_button")
			self.category_buttons[1]["cat_main_window"] = GetObject("history_category_window")
			self.category_buttons[1]["cat_button_object"] = GetObject("history_cat_button")
			self.category_buttons[2]["cat_main_window"] = GetObject("info_category_window")
			self.category_buttons[2]["cat_button_object"] = GetObject("info_cat_button")
			self.btnPrivateShopSearch = GetObject("search_shop_cat_button")
			
			#Main Shop Elements
			self.wndShopName = GetObject("ShopName")
			self.btnChangeName = GetObject("change_name_button")
			self.btnShopTeleport = GetObject("teleport_button")
			self.btnOpen = GetObject("OpenShopButton")
			self.btnDestroy = GetObject("DestroyShopButton")
			
			self.itemSlotWindow = GetObject("ItemSlot")
			
			#History Elements
			self.history_bg = GetObject("history_base_image")
			self.history_scrollbar = GetObject("history_scrollbar")
			self.history_scrollbar.Hide()
			self.loading_history_window = GetObject("loading_history_window")
			self.loading_history_window.Hide()
			self.history_no_found_itens = GetObject("history_no_found_itens")
			self.history_no_found_itens.Hide()
			
			#Info Elements
			self.no_info_avaible_msg = GetObject("no_info_avaible_msg")
			self.no_info_avaible_msg.Show()
			
			self.info_base_window = GetObject("info_base_window")
			self.info_base_window.Hide()
			
			self.shop_location_value = GetObject("shop_location_value")
			self.shop_channel_value = GetObject("shop_channel_value")
			self.shop_max_time_value = GetObject("shop_max_time_value")
			self.shop_quant_value = GetObject("shop_quant_value")
			self.shop_yang_value = GetObject("shop_yang_value")
			self.shop_visual_value = GetObject("shop_visual_value")
			
			#Common footer
			self.btnMoney = GetObject("money_button")
			self.wndMoney =  GetObject("Money")
			self.overfall2_premium = self.GetChild("overfall2_premium")
			
			self.left_shop_time_text = GetObject("left_shop_time_text")
			shop_time_text_width = GetObject("text_time_base").GetTextSize()[0]
			self.left_shop_time_text.SetPosition(shop_time_text_width + 5, 0)
			
			self.clock_remove_down = GetObject("clock_remove_down")
			self.clock_remove_down.SetCoolTime(0, 0)

			self.boardAnimation = BoardAnimation(self)

		except:
			import exception
			exception.Abort("OfflineShopManagerWindow.LoadWindow.BindObject")

		self.titleBar.SetCloseEvent(ui.__mem_func__(self.Close))
		
		#Common header
		for categoryKey in self.category_buttons.keys():
			self.category_buttons[categoryKey]["cat_button_object"].SetEvent(ui.__mem_func__(self.ChangeOfflineShopCategory), categoryKey)
		self.btnPrivateShopSearch.SetEvent(ui.__mem_func__(self.OpenSearchShop))
		
		#Main Shop Elements
		self.btnOpen.SetEvent(ui.__mem_func__(self.OpenShop))
		self.btnDestroy.SetEvent(ui.__mem_func__(self.DestroyShop))
		self.btnShopTeleport.SetEvent(ui.__mem_func__(self.TeleportToShop))
		self.btnChangeName.SetEvent(ui.__mem_func__(self.ChangeShopName))
		
		self.itemSlotWindow.SAFE_SetButtonEvent("LEFT", "EMPTY", self.SelectEmptySlot)
		self.itemSlotWindow.SAFE_SetButtonEvent("RIGHT", "EXIST", self.UnselectItemSlot)
		self.itemSlotWindow.SetOverInItemEvent(ui.__mem_func__(self.OverInItem))
		self.itemSlotWindow.SetOverOutItemEvent(ui.__mem_func__(self.OverOutItem))

		#History Elements
		self.history_scrollbar.SetScrollEvent(ui.__mem_func__(self.__OnHistoryScroll))
		
		#Common footer
		self.btnMoney.SetEvent(ui.__mem_func__(self.OpenPickMoneyDialog))
		
		#Others
		self.dlgPickMoney = uiPickMoney.PickExpandedMoneyDialog()
		self.dlgPickMoney.LoadDialog()
		self.dlgPickMoney.Hide()
		
		#Run imporant constructor things
		self.ChangeOfflineShopCategory(self.actual_category_page)
	
	def __ManageOfflineShopStateButtons(self, isOpened):
		if isOpened is True and self.isOpen:
			self.btnOpen.Hide()
			self.btnDestroy.Show()
			
			self.btnChangeName.Enable()
			self.btnShopTeleport.Enable()

			self.no_info_avaible_msg.Hide()
			self.info_base_window.Show()
			
			self.clock_remove_down.Show()
		else:
			self.btnOpen.Show()
			self.btnDestroy.Hide()
			
			self.btnChangeName.Disable()
			self.btnShopTeleport.Disable()
			
			self.info_base_window.Hide()
			self.no_info_avaible_msg.Show()
			
			self.clock_remove_down.Hide()
			self.clock_remove_down.SetCoolTime(0, 0)
	
	def RefreshInitInfo(self, mapIndex, shopChannel, time, displayedCount, shopName):
		self.shop_location_value.SetText(constInfo.MapNameByIndex(mapIndex))
		self.shop_channel_value.SetText("Kanal {}".format(str(shopChannel)))
		self.shopTime = int(time) + app.GetGlobalTimeStamp()
		self.shop_visual_value.SetText("{} Görüntülenme".format(str(displayedCount)))
		self.wndShopName.SetText(shopName)
		self.wndMoney.SetText(localeInfo.NumberToDecimalString(player.GetCurrentOfflineShopMoney()))
		
		shop_max_time = (7 if self.__GetPlayerPremium() else 3) * (60 * 60 * 24)
		shop_actual_time = float(time)
		
		if shop_actual_time >= shop_max_time:
			self.clock_remove_down.SetCoolTime(0, 0)
		else:
			perc_passed = 1.0 - (float(shop_actual_time) / float(shop_max_time))
			self.clock_remove_down.SetCoolTime(float(shop_max_time), perc_passed)
			self.clock_remove_down.SetStartCoolTime(float(app.GetTime()))
	
	def RefreshBaseInfo(self):
		shop_time = 7 if self.__GetPlayerPremium() else 3
		self.shop_max_time_value.SetText("{} Gün".format(shop_time))
		
		shop_count, shop_price = self.GetItensInShopInfo()
		self.shop_quant_value.SetText("{} Eþya(lar)".format(str(shop_count)))
		
		shop_text = localeInfo.NumberToDecimalString(shop_price)
		if len(shop_text) > 15:
			index_finish = len(shop_text) - 16
			real_shop_text = shop_text[:index_finish] + "kkkk"
			
			self.shop_yang_value.SetText("{}".format(real_shop_text))
		else:
			self.shop_yang_value.SetText("{}".format(shop_text))
		
		self.wndMoney.SetText(localeInfo.NumberToDecimalString(player.GetCurrentOfflineShopMoney()))
	
	def Open(self, isOpen, mapIndex, shopChannel, time, isPremium, displayedCount, shopName):
		global g_isEditingOfflineShop
		self.isOpen = isOpen
		if self.isOpen:
			g_isEditingOfflineShop = True
			self.__ManageOfflineShopStateButtons(True)
		else:
			g_isEditingOfflineShop = False
			self.__ManageOfflineShopStateButtons(False)
		
		self.RefreshInitInfo(mapIndex, shopChannel, time, displayedCount, shopName)
		
		if app.WJ_ENABLE_TRADABLE_ICON:
			self.ItemListIdx = []

		self.SetCenterPosition()
		self.SetTop()
		self.Show()
		self.boardAnimation.Enlarge()
		self.RefreshShop()

	def OpenShop(self):
		if self.interface:
			self.interface.OpenOfflineShopCreateDialog()

	def Close(self):
		global g_isEditingOfflineShop
		g_isEditingOfflineShop = False

		if self.priceInputBoard:
			self.priceInputBoard.Close()

		if self.questionDialog:
			self.OnCloseQuestionDialog()
		
		if self.changePriceInput:
			self.OnCloseChangePriceInput()
		
		if self.inputDialog:
			self.inputDialog.Close()

		self.boardAnimation.Shrink()
		self.title = ""
		self.priceInputBoard = None
		self.inputDialog = None
		self.Hide()

		if self.dlgPickMoney:
			self.dlgPickMoney.Close()

		if app.WJ_ENABLE_TRADABLE_ICON:
			if self.interface:
				self.interface.SetOnTopWindow(player.ON_TOP_WND_NONE)
				self.interface.RefreshMarkInventoryBag()

			self.ItemListIdx = None

	def OnPressEscapeKey(self):
		self.Close()
		return True

	def OnPressExitKey(self):
		self.Close()
		return True
	
	def OpenSearchShop(self):
		if app.ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM:
			if self.interface:
				self.interface.OpenNewPrivateShopSearch()
	
	def ChangeOfflineShopCategory(self, category):
		self.actual_category_page = category
		for categoryKey in self.category_buttons.keys():
			catWindow = self.category_buttons[categoryKey]["cat_main_window"]
			catButton = self.category_buttons[categoryKey]["cat_button_object"]
			
			if categoryKey != category:
				catWindow.Hide()
				catButton.SetUp()
			else:
				catWindow.Show()
				catButton.Down()
		
		self.__LoadExtraCatEvent()
	
	def __LoadExtraCatEvent(self):
		self.__ClearLastSalesObjects()
		
		if self.actual_category_page == 1:
			self.history_no_found_itens.Hide()
			self.loading_history_window.Show()
			net.SendChatPacket("/offlineshop_sales")
	
	################Sales Window
	def __ClearLastSalesObjects(self):
		if not len(self.sales_info_obj):
			return
		
		for obj in self.sales_info_obj:
			obj.DestroyObject()
		
		self.sales_info_obj = []
	
	def RefreshSalesWindow(self):
		self.loading_history_window.Hide()
		saleList = constInfo.OFFLINE_SHOP_SALES
		saleCount = len(saleList)
		
		if saleCount == 0:
			self.history_no_found_itens.Show()
		
		for line in xrange(saleCount):
			buyerName, itemVnum, count, price, date = saleList[line]
			price -= ((3*price)/100) #Aplica a taxa dos 3%
			
			tmpObj = SaleWindowObject()
			tmpObj.SetParent(self.history_bg)
			tmpObj.SetPosition(0, 32*line)
			tmpObj.SetInformation(buyerName, itemVnum, count, price, date)
			tmpObj.ShowObject()
			
			self.sales_info_obj.append(tmpObj)
		
		self.RefreshHistoryScrollBar()
		self.__OnHistoryScroll()
	
	def RefreshHistoryScrollBar(self):
		saleCount = len(self.sales_info_obj)
		if saleCount <= 8:
			self.history_scrollbar.Hide()
		else:
			self.history_scrollbar.Show()
			out_perc = minmax(0.0, float(saleCount - 8) / float(saleCount), 0.99)
			new_mid_bar_size = 1.0 - out_perc
			self.history_scrollbar.SetMiddleBarSize(new_mid_bar_size)
	
	def __OnHistoryScroll(self):
		saleCount = len(self.sales_info_obj)
		pos = int(self.history_scrollbar.GetPos() * (saleCount - 8))
		new_index = 0
		
		for line in xrange(saleCount):
			obj = self.sales_info_obj[line]
			if line < pos or line >= (pos + 8):
				obj.Close()
			else:
				obj.SetPosition(0, 32*new_index)
				obj.ShowObject()
				new_index += 1
	
	def OnRunMouseWheel(self, nLen):
		if self.actual_category_page == 1:
			if nLen > 0:
				self.history_scrollbar.OnUp()
			else:
				self.history_scrollbar.OnDown()
	################
	
	def ChangeOfflineShopName(self, shopName):
		if len(self.wndShopName.GetText()) != 0:
			self.wndShopName.SetText(shopName)
	
	def ChangeShopName(self):
		inputDialog = uiCommon.InputDialogOfflineShop()
		inputDialog.SetTitle(localeInfo.PRIVATE_SHOP_INPUT_NEW_NAME_DIALOG_TITLE)
		inputDialog.SetMaxLength(SHOP_SIGN_MAX_LEN)
		inputDialog.SetMaxSizeMode()
		inputDialog.SetAcceptEvent(ui.__mem_func__(self.AcceptChangeShopName))
		inputDialog.SetCancelEvent(ui.__mem_func__(self.CloseChangeShopName))
		inputDialog.Open()
		self.inputDialog = inputDialog
	
	def AcceptChangeShopName(self):
		if not self.inputDialog:
			return

		shop_name = self.inputDialog.GetText()
		
		if len(shop_name) <= 0:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_CREATE_DONT_HAVE_NAME)
			return
		
		if len(shop_name) < 3:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_CREATE_SMALL_SHOP_NAME)
			return
		
		net.SendChangeOfflineShopName(shop_name)
		self.CloseChangeShopName()
		return True
	
	def CloseChangeShopName(self):
		if not self.inputDialog:
			return
		
		self.inputDialog.Close()
		self.inputDialog = 0
	
	def TeleportToShop(self):
		net.SendChatPacket("/teleport_to_offshop")
	
	def DestroyShop(self):
		questionDialog = uiCommon.QuestionDialog()
		questionDialog.SetText(localeInfo.OFFLINE_SHOP_CLOSE_QUESTION)
		questionDialog.SetAcceptEvent(lambda arg = True: self.AnswerDestroyShop(arg))
		questionDialog.SetCancelEvent(lambda arg = False: self.AnswerDestroyShop(arg))
		questionDialog.Open()
		self.questionDialog = questionDialog

		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)

	def AnswerDestroyShop(self, flag):
		if flag:
			net.SendDestroyOfflineShop()

		if self.questionDialog:
			self.questionDialog.Close()
			self.questionDialog = None

		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)

	def RefreshShop(self):
		if IsEditingOfflineShop():
			net.SendRefreshOfflineShop()
			net.SendOfflineShopCheck()
		else:
			net.SendRefreshUnsoldItems()

		self.Refresh()

	def RefreshStatus(self):
		getItemStatus = shop.GetOfflineShopItemStatus

		self.RefreshMoney()
		if IsEditingOfflineShop():
			global g_iRefreshDelay
			net.SendRefreshOfflineShop(g_iRefreshDelay)
			net.SendOfflineShopCheck(g_iRefreshDelay)

		for i in xrange(shop.OFFLINE_SHOP_SLOT_COUNT):
			if getItemStatus(i) == 2:
				self.itemSlotWindow.SetCantMouseEventSlot(i)
			else:
				self.itemSlotWindow.SetCanMouseEventSlot(i)
	
	def GetItensInShopInfo(self):
		getItemID = shop.GetOfflineShopItemID
		iCount = 0
		totalPrice = 0
		
		for i in xrange(shop.OFFLINE_SHOP_SLOT_COUNT):
			idx = i

			if (getItemID(idx) > 0):
				iCount = iCount + 1
			
			totalPrice += (shop.GetOfflineShopItemPrice(idx) - ((3*shop.GetOfflineShopItemPrice(idx)) / 100))
		
		return iCount, totalPrice
	
	def Refresh(self):
		getItemID = shop.GetOfflineShopItemID
		getItemCount = shop.GetOfflineShopItemCount
		getItemStatus = shop.GetOfflineShopItemStatus
		setItemID = self.itemSlotWindow.SetItemSlot

		if IsEditingOfflineShop():
			global g_iRefreshDelay
			net.SendOfflineShopCheck(g_iRefreshDelay)

		iCount = 0
		for i in xrange(shop.OFFLINE_SHOP_SLOT_COUNT):
			idx = i

			if (getItemID(idx) <= 0):
				iCount = iCount + 1

			itemCount = getItemCount(idx)
			if itemCount <= 1:
				itemCount = 0
			setItemID(i, getItemID(idx), itemCount)

			# if app.BL_TRANSMUTATION_SYSTEM:
				# changelookvnum = shop.GetOfflineShopItemTransmutation(idx)
				# if not changelookvnum == 0:
					# self.itemSlotWindow.SetSlotCoverImage(i,"icon/item/ingame_convert_Mark.tga")
				# else:
			self.itemSlotWindow.EnableSlotCoverImage(i,False)

			if iCount == shop.OFFLINE_SHOP_SLOT_COUNT:
				self.__ManageOfflineShopStateButtons(False)

				for i in xrange(shop.OFFLINE_SHOP_SLOT_COUNT):
					self.itemSlotWindow.SetCoverButton(i, "d:/ymir work/ui/game/belt_inventory/slot_disabled.tga",\
						"d:/ymir work/ui/game/belt_inventory/slot_disabled.tga",\
						"d:/ymir work/ui/game/belt_inventory/slot_disabled.tga",\
						"d:/ymir work/ui/game/belt_inventory/slot_disabled.tga", False, False)
					self.itemSlotWindow.SetAlwaysRenderCoverButton(i)
				return
			else:
				self.__ManageOfflineShopStateButtons(True)

		wndMgr.RefreshSlot(self.itemSlotWindow.GetWindowHandle())

	def RefreshMoney(self):
		global g_iRefreshDelay
		net.SendRefreshOfflineShopMoney(g_iRefreshDelay)

		money = player.GetCurrentOfflineShopMoney()
		self.wndMoney.SetText(localeInfo.NumberToDecimalString(money))

	def SetItemData(self, pos, itemID, itemCount, itemPrice):
		shop.SetOfflineShopItemData(pos, itemID, itemCount, itemPrice)

	def AcceptInputPrice(self):
		if not self.priceInputBoard:
			return True
		
		price = long(self.priceInputBoard.GetRealMoney())
		
		if not price:
			return

		attachedInvenType = self.priceInputBoard.sourceWindowType
		sourceSlotPos = self.priceInputBoard.sourceSlotPos
		targetSlotPos = self.priceInputBoard.targetSlotPos

		constInfo.SetOfflineShopItemPrice(self.priceInputBoard.itemVNum, price, self.priceInputBoard.itemCount)
		net.SendAddOfflineShopItem(sourceSlotPos, targetSlotPos, price, attachedInvenType)

		snd.PlaySound("sound/ui/drop.wav")

		#####

		self.CancelInputPrice()

	def CancelInputPrice(self):
		if app.WJ_ENABLE_TRADABLE_ICON:
			pos = self.priceInputBoard.sourceSlotPos
			for i in xrange(len(self.ItemListIdx)):
				if self.ItemListIdx[i] == pos:
					del self.ItemListIdx[i]
					break

			# if app.ENABLE_SPECIAL_INVENTORY_SYSTEM:
				# if self.inven or self.invenSpecial:
					# page = self.inven.GetInventoryPageIndex() # range 0 ~ 1
					# special_page = self.invenSpecial.GetInventoryPageIndex()

					# if (page * INVENTORY_PAGE_SIZE) <= pos < ((page + 1) * INVENTORY_PAGE_SIZE): # range 0 ~ 44, 45 ~ 89
						# idx = pos - (page * INVENTORY_PAGE_SIZE)
						# self.inven.wndItem.SetCanMouseEventSlot(idx)

					# if self.invenSpecial.GetInventoryType() == 0:
						# if (item.SKILL_BOOK_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= pos < (item.SKILL_BOOK_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# idx = pos - (item.SKILL_BOOK_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCanMouseEventSlot(idx)

					# if self.invenSpecial.GetInventoryType() == 1:
						# if (item.UPGRADE_ITEMS_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= pos < (item.UPGRADE_ITEMS_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# idx = pos - (item.UPGRADE_ITEMS_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCanMouseEventSlot(idx)

					# if self.invenSpecial.GetInventoryType() == 2:
						# if (item.STONE_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= pos < (item.STONE_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# idx = pos - (item.STONE_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCanMouseEventSlot(idx)

					# if self.invenSpecial.GetInventoryType() == 3:
						# if (item.GIFT_BOX_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= pos < (item.GIFT_BOX_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# idx = pos - (item.GIFT_BOX_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCanMouseEventSlot(idx)
					
					# if self.invenSpecial.GetInventoryType() == 4:
						# if (item.CHANGERS_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= pos < (item.CHANGERS_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# idx = pos - (item.CHANGERS_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCanMouseEventSlot(idx)
			# else:
			if self.inven:
				page = self.inven.GetInventoryPageIndex() # range 0 ~ 1

				if (page * INVENTORY_PAGE_SIZE) <= pos < ((page + 1) * INVENTORY_PAGE_SIZE): # range 0 ~ 44, 45 ~ 89
					idx = pos - (page * INVENTORY_PAGE_SIZE)
					self.inven.wndItem.SetCanMouseEventSlot(idx)

		self.RefreshShop()

		self.priceInputBoard = None
		return True

	def OpenPickMoneyDialog(self):
		if not mouseModule.mouseController.isAttached():
			curMoney = player.GetCurrentOfflineShopMoney()

			if curMoney <= 0:
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_DONT_HAVE_MONEY_TO_WITHDRAW)
				return

			self.dlgPickMoney.SetTitleName(localeInfo.PICK_MONEY_TITLE)
			self.dlgPickMoney.SetAcceptEvent(ui.__mem_func__(self.OnPickMoney))
			self.dlgPickMoney.Open(curMoney)
			self.dlgPickMoney.SetMax(15)

	def OnPickMoney(self, money):
		if money > 0:
			net.SendOfflineShopWithdrawMoney(money)
			self.RefreshMoney()
		self.RefreshShop()

	def OnCloseQuestionDialog(self):
		if not self.questionDialog:
			return

		self.questionDialog.Close()
		self.questionDialog = None
		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)
	
	def OnCloseChangePriceInput(self):
		if not self.changePriceInput:
			return

		self.changePriceInput.Close()
		self.changePriceInput = None
		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)

	def SelectEmptySlot(self, selectedSlotPos):
		if not IsEditingOfflineShop():
			return

		if self.priceInputBoard:
			return

		isAttached = mouseModule.mouseController.isAttached()
		if isAttached:
			attachedSlotType = mouseModule.mouseController.GetAttachedType()
			attachedSlotPos = mouseModule.mouseController.GetAttachedSlotNumber()
			mouseModule.mouseController.DeattachObject()

			if player.SLOT_TYPE_INVENTORY != attachedSlotType and player.SLOT_TYPE_DRAGON_SOUL_INVENTORY != attachedSlotType:
				# (player.SLOT_TYPE_SKILL_BOOK_INVENTORY != attachedSlotType and\
				# player.SLOT_TYPE_UPGRADE_ITEMS_INVENTORY != attachedSlotType and\
				# player.SLOT_TYPE_STONE_INVENTORY != attachedSlotType and\
				# player.SLOT_TYPE_GIFT_BOX_INVENTORY != attachedSlotType and\
				# player.SLOT_TYPE_CHANGERS_INVENTORY != attachedSlotType and app.ENABLE_SPECIAL_INVENTORY_SYSTEM):

				return

			attachedInvenType = player.SlotTypeToInvenType(attachedSlotType)

			itemVNum = player.GetItemIndex(attachedInvenType, attachedSlotPos)
			itemCount = player.GetItemCount(attachedInvenType, attachedSlotPos)
			item.SelectItem(itemVNum)

			# if app.ENABLE_SOUL_BIND_SYSTEM:
				# if player.GetItemSealDate(attachedInvenType, attachedSlotPos) == -1 or player.GetItemSealDate(attachedInvenType, attachedSlotPos) > 0: #ºÀÀÎ¾ÆÀÌÅÛ °É·¯³¿.
					# return True

			if item.IsAntiFlag(item.ANTIFLAG_GIVE) or item.IsAntiFlag(item.ANTIFLAG_MYSHOP):
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.PRIVATE_SHOP_CANNOT_SELL_ITEM)
				return

			priceInputBoard = uiCommon.NewMoneyInputDialog()
			priceInputBoard.SetTitle(localeInfo.PRIVATE_SHOP_INPUT_PRICE_DIALOG_TITLE)
			priceInputBoard.SetAcceptEvent(ui.__mem_func__(self.AcceptInputPrice))
			priceInputBoard.SetCancelEvent(ui.__mem_func__(self.CancelInputPrice))
			priceInputBoard.Open()

			itemPrice = constInfo.GetOfflineShopItemPrice(itemVNum, itemCount)
			if itemPrice > 0:
				priceInputBoard.SetValue(itemPrice)

			self.priceInputBoard = priceInputBoard
			self.priceInputBoard.itemVNum = itemVNum
			self.priceInputBoard.itemCount = itemCount
			self.priceInputBoard.sourceWindowType = attachedInvenType
			self.priceInputBoard.sourceSlotPos = attachedSlotPos
			self.priceInputBoard.targetSlotPos = selectedSlotPos

			if app.WJ_ENABLE_TRADABLE_ICON:
				self.ItemListIdx.append(attachedSlotPos)
				self.priceInputBoard.Socket = self.GetItemDataSocketValue(attachedInvenType, attachedSlotPos)

	def UnselectItemSlot(self, selectedSlotPos):
		if constInfo.GET_ITEM_QUESTION_DIALOG_STATUS() == 1:
			return
		
		if (app.IsPressed(app.DIK_LCONTROL) or app.IsPressed(app.DIK_RCONTROL)) and\
			shop.GetOfflineShopItemStatus(selectedSlotPos) == 0 and g_isEditingOfflineShop:
			self.ChangeItemPrice(selectedSlotPos)
		else:
			self.AskRemoveItem(selectedSlotPos)

	def DropToInventory(self):
		attachedSlotPos = mouseModule.mouseController.GetAttachedSlotNumber()
		self.AskBuyItem(attachedSlotPos)
	
	def ChangeItemPrice(self, selectedSlotPos):
		itemVNum = shop.GetOfflineShopItemID(selectedSlotPos)
		itemCount = shop.GetOfflineShopItemCount(selectedSlotPos)
		actualItemPrice = shop.GetOfflineShopItemPrice(selectedSlotPos)
		
		changePriceInput = uiCommon.NewMoneyInputDialog()
		changePriceInput.SetTitle(localeInfo.PRIVATE_SHOP_INPUT_CHANGE_PRICE_DIALOG_TITLE)
		changePriceInput.SetAcceptEvent(lambda arg = True : self.AnswerChangePrice(arg))
		changePriceInput.SetCancelEvent(lambda arg = False : self.AnswerChangePrice(arg))
		changePriceInput.Open()

		if actualItemPrice > 0:
			changePriceInput.SetValue(actualItemPrice)

		self.changePriceInput = changePriceInput
		self.changePriceInput.pos = selectedSlotPos
		self.changePriceInput.itemVNum = itemVNum
		self.changePriceInput.itemCount = itemCount

		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)
	
	def AnswerChangePrice(self, flag):
		if not self.changePriceInput:
			return True
		
		if flag:
			pos = self.changePriceInput.pos
			itemVNum = self.changePriceInput.itemVNum
			itemCount = self.changePriceInput.itemCount
			price = long(self.changePriceInput.GetRealMoney())
			
			if not price:
				return True
			
			constInfo.SetOfflineShopItemPrice(itemVNum, price, itemCount)
			if IsEditingOfflineShop():
				net.SendOfflineShopChangeItemPrice(pos, price)
				net.SendOfflineShopCheck()
		
		self.changePriceInput.Close()
		self.changePriceInput = None

		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)
		
		return True
	
	def AskRemoveItem(self, selectedSlotPos):
		itemIndex = shop.GetOfflineShopItemID(selectedSlotPos)

		item.SelectItem(itemIndex)
		itemName = item.GetItemName()

		questionDialog = uiCommon.QuestionDialog()
		questionDialog.SetText(localeInfo.OFFLINE_SHOP_REMOVE_ITEM_QUESTION % itemName)
		questionDialog.SetAcceptEvent(lambda arg = True : self.AnswerRemoveItem(arg))
		questionDialog.SetCancelEvent(lambda arg = False : self.AnswerRemoveItem(arg))
		questionDialog.Open()
		questionDialog.pos = selectedSlotPos
		self.questionDialog = questionDialog

		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)

	def AnswerRemoveItem(self, flag):
		if not self.questionDialog:
			return
		
		if flag:
			pos = self.questionDialog.pos
			if IsEditingOfflineShop():
				net.SendRemoveOfflineShopItem(pos)
				net.SendOfflineShopCheck()
			else:
				net.SendOfflineShopTakeItem(pos)

		self.questionDialog.Close()
		self.questionDialog = None

		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)

		self.RefreshShop()

	def SetItemToolTip(self, tooltipItem):
		self.tooltipItem = tooltipItem

	def OverInItem(self, slotIndex):
		global g_isEditingOfflineShop
		if mouseModule.mouseController.isAttached():
			return

		if None != self.tooltipItem:
			self.tooltipItem.SetOfflineShopItem(slotIndex)
			
			if shop.GetOfflineShopItemStatus(slotIndex) < 2: 
				self.tooltipItem.AppendTextLine("|Ekey/key_rclick|e - Eþyayý Kaldýr")
			if shop.GetOfflineShopItemStatus(slotIndex) == 0 and g_isEditingOfflineShop:
				self.tooltipItem.AppendTextLine("|Ekey/key_ctrl|e + |Ekey/key_rclick|e - Fiyatý Düzenle")

	def OverOutItem(self):
		if None != self.tooltipItem:
			self.tooltipItem.HideToolTip()

	def __GetPlayerPremium(self):
		return chr.IsOverfallPremium()
	
	def __RefreshTimeGauge(self):
		if IsEditingOfflineShop():
			leftSec = max(0, self.shopTime - app.GetGlobalTimeStamp())
			self.left_shop_time_text.SetText("|cffd3820b{}|cFFFFFFFF / {} Gün".format(localeInfo.PrivateShopSecondToDHMS(leftSec), 7 if self.__GetPlayerPremium() else 3))
			if not self.clock_remove_down.IsShow():
				self.clock_remove_down.Show()

			shop_max_time = (7 if self.__GetPlayerPremium() else 3) * (60 * 60 * 24)
			shop_actual_time = float(leftSec)
			
			if not self.clock_remove_down.IsInCoolTime():
				self.clock_remove_down.SetStartCoolTime(float(app.GetTime()))
			
			if shop_actual_time >= shop_max_time:
				if self.clock_remove_down.IsInCoolTime():
					self.clock_remove_down.SetCoolTime(0, 0)
			else:
				perc_passed = 1.0 - (float(shop_actual_time) / float(shop_max_time))
				self.clock_remove_down.SetCoolTime(float(shop_max_time), perc_passed)
		else:
			self.left_shop_time_text.SetText("|cffd3820bKapalý maðaza")
			self.clock_remove_down.SetCoolTime(0, 0)
			self.clock_remove_down.Hide()
			
	def OnUpdate(self):
		self.__RefreshTimeGauge()
		self.RefreshStatus()

		if self.overfall2_premium:
			self.overfall2_premium.LoadImage(PREMIUM_IMAGES[self.__GetPlayerPremium()])
		
		self.RefreshBaseInfo()

		if app.WJ_ENABLE_TRADABLE_ICON:
			# if app.ENABLE_SPECIAL_INVENTORY_SYSTEM:
				# if not self.inven or not self.invenSpecial:
					# return
			# else:
			if not self.inven:
				return

			page = self.inven.GetInventoryPageIndex() # range 0 ~ 1
			# if app.ENABLE_SPECIAL_INVENTORY_SYSTEM:
				# special_page = self.invenSpecial.GetInventoryPageIndex()

			for i in self.ItemListIdx:
				if (page * INVENTORY_PAGE_SIZE) <= i < ((page + 1) * INVENTORY_PAGE_SIZE): # range 0 ~ 44, 45 ~ 89
					lock_idx = i - (page * INVENTORY_PAGE_SIZE) 
					self.inven.wndItem.SetCantMouseEventSlot(lock_idx)

				# if app.ENABLE_SPECIAL_INVENTORY_SYSTEM:
					# if self.invenSpecial.GetInventoryType() == 0:
						# if (item.SKILL_BOOK_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= i < (item.SKILL_BOOK_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# lock_idx = i - (item.SKILL_BOOK_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCantMouseEventSlot(lock_idx)

					# if self.invenSpecial.GetInventoryType() == 1:
						# if (item.UPGRADE_ITEMS_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= i < (item.UPGRADE_ITEMS_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# lock_idx = i - (item.UPGRADE_ITEMS_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCantMouseEventSlot(lock_idx)

					# if self.invenSpecial.GetInventoryType() == 2:
						# if (item.STONE_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= i < (item.STONE_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# lock_idx = i - (item.STONE_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCantMouseEventSlot(lock_idx)

					# if self.invenSpecial.GetInventoryType() == 3:
						# if (item.GIFT_BOX_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= i < (item.GIFT_BOX_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# lock_idx = i - (item.GIFT_BOX_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCantMouseEventSlot(lock_idx)
					
					# if self.invenSpecial.GetInventoryType() == 4:
						# if (item.CHANGERS_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE)) <= i < (item.CHANGERS_INVENTORY_SLOT_START + (((special_page + 1) * SPECIAL_INVENTORY_PAGE_SIZE))):
							# lock_idx = i - (item.CHANGERS_INVENTORY_SLOT_START + (special_page * SPECIAL_INVENTORY_PAGE_SIZE))
							# self.invenSpecial.wndItem.SetCantMouseEventSlot(lock_idx)

	if app.WJ_ENABLE_TRADABLE_ICON:
		def CantTradableItem(self, slotIndex):
			itemIndex = player.GetItemIndex(slotIndex)

			if itemIndex:
				if app.ENABLE_SOUL_BIND_SYSTEM:
					if player.GetItemSealDate(player.INVENTORY, slotIndex) == -1 or player.GetItemSealDate(player.INVENTORY, slotIndex) > 0: #ºÀÀÎ¾ÆÀÌÅÛ °É·¯³¿.
						return True

				if itemIndex == 50200:
					return True

				if player.IsAntiFlagBySlot(slotIndex, item.ANTIFLAG_GIVE) or player.IsAntiFlagBySlot(slotIndex, item.ANTIFLAG_MYSHOP):
					return True

			return False

		def BindInterface(self, interface):
			self.interface = proxy(interface)

		def OnTop(self):
			if not self.interface:
				return

			self.interface.SetOnTopWindow(player.ON_TOP_WND_OFFLINE_SHOP)
			self.interface.RefreshMarkInventoryBag()

		def SetInven(self, inven):
			self.inven = inven

		# if app.ENABLE_SPECIAL_INVENTORY_SYSTEM:
			# def SetSpecialInven(self, invenSpecial):
				# self.invenSpecial = invenSpecial

		def GetItemDataSocketValue(self, winType, SlotPos):
			for i in xrange(item.LIMIT_MAX_NUM):

				(limitType, limitValue) = item.GetLimit(i)
				if limitType == item.LIMIT_REAL_TIME or limitType == item.LIMIT_REAL_TIME_START_FIRST_USE or limitType == item.LIMIT_TIMER_BASED_ON_WEAR:
					return 0

			return player.GetItemMetinSocket(winType, SlotPos, 0)

###################################################################################################
## Offline Shop
class OfflineShopDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.tooltipItem = 0
		self.xShopStart = 0
		self.yShopStart = 0
		self.questionDialog = None
		self.popup = None
		self.itemBuyQuestionDialog = None
		self.boardAnimation = None

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __GetRealIndex(self, i):
		return i # shop.OFFLINE_SHOP_SLOT_COUNT + i

	def Refresh(self):
		getItemID = shop.GetOfflineShopItemID
		getItemVnum = shop.GetOfflineShopItemVnum
		getItemStatus = shop.GetOfflineShopItemStatus
		getItemCount = shop.GetOfflineShopItemCount
		setItemID = self.itemSlotWindow.SetItemSlot

		for i in xrange(shop.OFFLINE_SHOP_SLOT_COUNT):
			idx = self.__GetRealIndex(i)
			itemCount = getItemCount(idx)
			if itemCount <= 1:
				itemCount = 0
			setItemID(i, getItemID(idx), itemCount)

			item.SelectItem(getItemVnum(idx))
			(itemWidth, itemHeight) = item.GetItemSize()

			# if app.BL_TRANSMUTATION_SYSTEM:
				# changelookvnum = shop.GetOfflineShopItemTransmutation(idx)
				# if not changelookvnum == 0:
					# self.itemSlotWindow.SetSlotCoverImage(i,"icon/item/ingame_convert_Mark.tga")
				# else:
			self.itemSlotWindow.EnableSlotCoverImage(i,False)

			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# itemTransmutedVnum = shop.GetOfflineShopItemTransmutation(idx)
			# if itemTransmutedVnum:
				# self.itemSlotWindow.DisableCoverButton(i)
			# else:
				# self.itemSlotWindow.EnableCoverButton(i)

			if getItemStatus(idx) == 2:
				self.itemSlotWindow.SetCantMouseEventSlot(i)
			else:
				self.itemSlotWindow.SetCanMouseEventSlot(i)

		self.viewCount.SetText(localeInfo.OFFLINE_SHOP_VIEWS % shop.GetDisplayedCount())
		wndMgr.RefreshSlot(self.itemSlotWindow.GetWindowHandle())

	def LoadDialog(self):
		try:
			PythonScriptLoader = ui.PythonScriptLoader()
			PythonScriptLoader.LoadScriptFile(self, "UIScript/offlineshopdialog.py")
		except:
			import exception
			exception.Abort("OfflineShopDialog.LoadDialog.LoadObject")

		try:
			GetObject = self.GetChild
			self.itemSlotWindow = GetObject("ItemSlot")
			self.titleBar = GetObject("TitleBar")
			self.titleName = GetObject("TitleName")
			self.NameLine = GetObject("NameLine")
			self.viewCount = GetObject("ViewCount")

			self.boardAnimation = BoardAnimation(self)

		except:
			import exception
			exception.Abort("OfflineShopDialog.LoadDialog.BindObject")

		self.itemSlotWindow.SetSlotStyle(wndMgr.SLOT_STYLE_NONE)
		self.itemSlotWindow.SAFE_SetButtonEvent("LEFT", "EMPTY", self.SelectEmptySlot)
		self.itemSlotWindow.SAFE_SetButtonEvent("LEFT", "EXIST", self.SelectItemSlot)
		self.itemSlotWindow.SAFE_SetButtonEvent("RIGHT", "EXIST", self.UnselectItemSlot)

		self.itemSlotWindow.SetOverInItemEvent(ui.__mem_func__(self.OverInItem))
		self.itemSlotWindow.SetOverOutItemEvent(ui.__mem_func__(self.OverOutItem))

		self.titleBar.SetCloseEvent(ui.__mem_func__(self.Close))

		self.Refresh()

	def Destroy(self):
		self.Close()
		self.ClearDictionary()

		self.tooltipItem = 0
		self.itemSlotWindow = 0
		self.titleBar = 0
		self.questionDialog = None
		self.popup = None

	def Open(self, vid):
		isPrivateShop = False
		isMainPlayerPrivateShop = False
		isOfflineShop = True

		if chr.IsNPC(vid):
			isPrivateShop = False
		else:
			isPrivateShop = True

		if player.IsMainCharacterIndex(vid):
			isMainPlayerPrivateShop = True
		else:
			isMainPlayerPrivateShop = False

		shop.Open(isPrivateShop, isMainPlayerPrivateShop, isOfflineShop)

		self.Refresh()
		self.SetTop()

		self.Show()
		self.boardAnimation.Enlarge()
		self.titleName.SetText(chr.GetNameByVID(vid))
		shopName = uiOfflineShopBuilder.GetADBoardName(vid)
		self.NameLine.SetText(shopName if len(shopName) != 0 else self.titleName.GetText())

		(self.xShopStart, self.yShopStart, z) = player.GetMainCharacterPosition()
	
	def HaveShopVidOpen(self, vid):
		if chr.GetNameByVID(vid) == self.titleName.GetText():
			return True
		return False
	
	def ReloadOfflineShopItemPrice(self, vid, pos, Price):
		if not self.itemBuyQuestionDialog:
			return
		
		if self.itemBuyQuestionDialog.pos != pos:
			return
		
		self.itemBuyQuestionDialog.Close()
		self.itemBuyQuestionDialog = None
		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.OFFLINE_SHOP_PRICE_CHANGED_RELOAD)
	
	def Close(self):
		if self.itemBuyQuestionDialog:
			self.itemBuyQuestionDialog.Close()
			self.itemBuyQuestionDialog = None
			constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)

		if self.questionDialog:
			self.OnCloseQuestionDialog()
		self.boardAnimation.Shrink()
		shop.Close()
		net.SendOfflineShopEndPacket()
		self.CancelShopping()
		self.tooltipItem.HideToolTip()
		self.Hide()

	def OnPressEscapeKey(self):
		self.Close()
		return True

	def OnPressExitKey(self):
		self.Close()
		return True

	def OnBuy(self):
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.SHOP_BUY_INFO)
		app.SetCursor(app.BUY)

	def CancelShopping(self):
		app.SetCursor(app.NORMAL)

	def __OnClosePopupDialog(self):
		self.pop = None
		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)

	def OnCloseQuestionDialog(self):
		if not self.questionDialog:
			return

		self.questionDialog.Close()
		self.questionDialog = None
		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)

	def SelectEmptySlot(self, selectedSlotPos):
		isAttached = mouseModule.mouseController.isAttached()
		if isAttached:
			if shop.IsOfflineShop():
				mouseModule.mouseController.DeattachObject()
				return

	def UnselectItemSlot(self, selectedSlotPos):
		if constInfo.GET_ITEM_QUESTION_DIALOG_STATUS() == 1:
			return

		if shop.IsOfflineShop():
			if shop.GetOfflineShopItemStatus(selectedSlotPos) == 0:
				self.AskBuyItem(selectedSlotPos)

	def SelectItemSlot(self, selectedSlotPos):
		if constInfo.GET_ITEM_QUESTION_DIALOG_STATUS() == 1:
			return

		isAttached = mouseModule.mouseController.isAttached()
		if not isAttached:
			if True == shop.IsMainPlayerPrivateShop():
				return

			curCursorNum = app.GetCursor()
			if app.BUY == curCursorNum:
				self.AskBuyItem(selectedSlotPos)
			else:
				selectedItemID = shop.GetOfflineShopItemID(selectedSlotPos)
				itemCount = shop.GetOfflineShopItemCount(selectedSlotPos)

				type = player.SLOT_TYPE_SHOP
				if shop.IsOfflineShop():
					type = player.SLOT_TYPE_OFFLINE_SHOP

				mouseModule.mouseController.AttachObject(self, type, selectedSlotPos, selectedItemID, itemCount)
				mouseModule.mouseController.SetCallBack("INVENTORY", ui.__mem_func__(self.DropToInventory))
				snd.PlaySound("sound/ui/pick.wav")

	def DropToInventory(self):
		attachedSlotPos = mouseModule.mouseController.GetAttachedSlotNumber()
		self.AskBuyItem(attachedSlotPos)

	def AskBuyItem(self, slotPos):
		slotPos = self.__GetRealIndex(slotPos)

		itemIndex = shop.GetOfflineShopItemID(slotPos)
		itemPrice = shop.GetOfflineShopItemPrice(slotPos)
		itemCount = shop.GetOfflineShopItemCount(slotPos)

		item.SelectItem(itemIndex)
		itemName = item.GetItemName()

		itemBuyQuestionDialog = uiCommon.QuestionDialog()
		itemBuyQuestionDialog.SetText(localeInfo.DO_YOU_BUY_ITEM(itemName, itemCount, localeInfo.NumberToMoneyString(itemPrice)))

		itemBuyQuestionDialog.SetAcceptEvent(lambda arg=True: self.AnswerBuyItem(arg))
		itemBuyQuestionDialog.SetCancelEvent(lambda arg=False: self.AnswerBuyItem(arg))
		itemBuyQuestionDialog.Open()
		itemBuyQuestionDialog.pos = slotPos
		self.itemBuyQuestionDialog = itemBuyQuestionDialog

		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)

	def AnswerBuyItem(self, flag):
		if flag:
			pos = self.itemBuyQuestionDialog.pos
			net.SendOfflineShopBuyPacket(pos)

		self.itemBuyQuestionDialog.Close()
		self.itemBuyQuestionDialog = None

		constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)

	def SetItemToolTip(self, tooltipItem):
		self.tooltipItem = tooltipItem

	def OverInItem(self, slotIndex):
		slotIndex = self.__GetRealIndex(slotIndex)
		if mouseModule.mouseController.isAttached():
			return

		if 0 != self.tooltipItem:
			self.tooltipItem.SetOfflineShopItem(slotIndex)

	def OverOutItem(self):
		if 0 != self.tooltipItem:
			self.tooltipItem.HideToolTip()

	def OnUpdate(self):
		USE_SHOP_LIMIT_RANGE = 1500

		(x, y, z) = player.GetMainCharacterPosition()
		if abs(x - self.xShopStart) > USE_SHOP_LIMIT_RANGE or abs(y - self.yShopStart) > USE_SHOP_LIMIT_RANGE:
			self.Close()

		self.Refresh()