import app
import player
import net
import chr
import background
import chat
import item
import newPrivateShopSearch
import shop
import ui
import grp
import uiCommon
import localeInfo
import constInfo
import filterCfg
import uiScriptLocale
import autoComplete
import math
import exception
import uiToolTip
from _weakref import proxy

MAIN_PATH = "d:/ymir work/ui/search_shop/"
PREMIUM_IMAGES = ["d:/ymir work/ui/pattern/visible_mark_03.tga", "d:/ymir work/ui/pattern/visible_mark_01.tga"]

#############################
SHOP_EFFECT_TIME = 60
MAX_SERVER_LEVEL = 105
MAX_DM = 65
MAX_DH = 30
#############################

already_change_normal_cur = False

def minmax(x, y, z):
	if y > z:	return z
	elif y < x:	return x
	return y

def write(arg):
	chat.AppendChat(chat.CHAT_TYPE_INFO, arg)

def DeletePrivateShopEffect():
	background.DeletePrivateShopPos()
	constInfo.CREATE_PRIVATE_SHOP_EFFECT = (False, app.GetTime())

def CreatePrivateShopEffect(chrVid):
	background.CreatePrivateShopPos(chrVid)
	constInfo.CREATE_PRIVATE_SHOP_EFFECT = (True, app.GetTime() + SHOP_EFFECT_TIME)

class NewPrivateShopFilterListBox(ui.ScriptWindow):
	def __init__(self, parent):
		ui.ScriptWindow.__init__(self)
		self.SetParent(parent)
		self.SetSize(173, 0)
		
		self.__Initialize()
	
	def __Initialize(self):
		self.horizontalLine_top = None
		self.horizontalLine_left = None
		self.horizontalLine_right = None
		self.horizontalLine_bottom = None
		
		self.actual_but_select = 0
		self.max_itens = 0
		self.scrollbar = None
		self.click_event = None
		self.click_args = None
		self.buttons_list = []
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def __LoadScrollBar(self, size):
		self.scrollbar = ui.MakeNewScrollBar(self, 4, -12, size)
		self.scrollbar.SetWindowHorizontalAlignRight()
		self.scrollbar.SetScrollEvent(ui.__mem_func__(self.__OnScroll))
	
	def __LoadMainBox(self):
		self.horizontalLine_top = ui.Line()
		self.horizontalLine_top.SetParent(self)
		self.horizontalLine_top.SetPosition(0, 0)
		self.horizontalLine_top.SetColor(0xFF403c38)
		self.horizontalLine_top.SetSize(173, 0)
		self.horizontalLine_top.Show()
		
		self.horizontalLine_left = ui.Line()
		self.horizontalLine_left.SetParent(self)
		self.horizontalLine_left.SetPosition(0, 0)
		self.horizontalLine_left.SetColor(0xFF403c38)
		self.horizontalLine_left.SetSize(0, 0)
		self.horizontalLine_left.Show()
		
		self.horizontalLine_right = ui.Line()
		self.horizontalLine_right.SetParent(self)
		self.horizontalLine_right.SetPosition(0, 0)
		self.horizontalLine_right.SetWindowHorizontalAlignRight()
		self.horizontalLine_right.SetColor(0xFF403c38)
		self.horizontalLine_right.SetSize(0, 0)
		self.horizontalLine_right.Show()
		
		self.horizontalLine_bottom = ui.Line()
		self.horizontalLine_bottom.SetParent(self)
		self.horizontalLine_bottom.SetPosition(0, 0)
		self.horizontalLine_bottom.SetColor(0xFF403c38)
		self.horizontalLine_bottom.SetSize(173, 0)
		self.horizontalLine_bottom.Show()
	
	def ClearList(self):
		for button in self.buttons_list:
			button.Hide()
		
		self.SetSize(173, 0)
		
		self.horizontalLine_top = None
		self.horizontalLine_left = None
		self.horizontalLine_right = None
		self.horizontalLine_bottom = None
		self.buttons_list = []
	
	def AddItem(self, buttonName, buttonIndex):
		index = len(self.buttons_list)
		tmpButton = ui.MakeRadioButton(self, 0, 24*index, "", MAIN_PATH + "filter_window/", "filter_drop_down_norm.tga", "filter_drop_down_hover.tga", "filter_drop_down_down.tga")
		tmpButton.SetText(str(buttonName))
		tmpButton.SetEvent(ui.__mem_func__(self.ClickOnElement), buttonName, index, buttonIndex)
		tmpButton.Hide()
		
		self.buttons_list.append(tmpButton)
	
	def SetMax(self, max):
		self.max_itens = max
	
	def CloseList(self):
		self.Hide()
	
	def SetClickEvent(self, event, *args):
		self.click_event = event
		self.click_args = args
	
	def __RefreshButtonsPosition(self):
		for button in self.buttons_list:
			button.SetUp()
		
		self.buttons_list[self.actual_but_select].Down()
	
	def ForceButton(self, index):
		self.actual_but_select = index
		self.__RefreshButtonsPosition()
	
	def ClickOnElement(self, name, index, buttonIndex):
		if self.click_event:
			self.click_event(self.click_args, name, buttonIndex)
		self.actual_but_select = index
		self.__RefreshButtonsPosition()
	
	def OpenList(self):
		self.__LoadMainBox()
		
		list_len = len(self.buttons_list)
		if list_len != 0:
			height = 24*self.max_itens
			self.SetSize(173, height)
			self.horizontalLine_left.SetSize(0, height)
			self.horizontalLine_right.SetSize(0, height)
			self.horizontalLine_bottom.SetPosition(0, height)
			
			if list_len > self.max_itens:
				if not self.scrollbar:
					self.__LoadScrollBar(height + 34)
				
				self.scrollbar.SetPos(0.0)
				self.__ReloadScrollBarSize()
				self.__ReloadObjectsPosition()
				self.scrollbar.Show()
			else:
				for button in self.buttons_list:
					button.Show()
				
				if self.scrollbar:
					self.scrollbar.Hide()
		
		self.__RefreshButtonsPosition()
		self.Show()
	
	def __ReloadScrollBarSize(self):
		list_len = len(self.buttons_list)
		if list_len < self.max_itens:
			return
		
		step = (1.0/(float(list_len)))
		step_scroll = (1.0/(float(list_len) - float(self.max_itens)))
		
		new_size = minmax(0.0, 1.0 - (step * (float(list_len) - self.max_itens)), 0.99)
		self.scrollbar.SetMiddleBarSize(new_size)
		self.scrollbar.SetScrollStep(step_scroll)

	def OnRunMouseWheel(self, nLen):
		if nLen > 0:
			self.scrollbar.OnUp()
		else:
			self.scrollbar.OnDown()
	
	def __OnScroll(self):
		if not self.scrollbar.IsShow():
			return
		self.__ReloadObjectsPosition()
	
	def __ReloadObjectsPosition(self):
		scrollPos = self.scrollbar.GetPos()
		dic_len = len(self.buttons_list)
		step = (1.0/(float(dic_len) -float(self.max_itens-1)))
		start_index = 0.0
		while (scrollPos > (start_index * step)):
			start_index += 1.0
		
		start_index = minmax(0, (int(start_index) -1), dic_len-self.max_itens)
		
		for button in self.buttons_list:
			button.Hide()
		
		but_index = 0
		for index in xrange(start_index, start_index+self.max_itens):
			button = self.buttons_list[index]
			button.SetPosition(0, 24*but_index)
			but_index += 1
			button.Show()

class PrivateShopFilterWindow(ui.ScriptWindow):
	def __init__(self, mainwnd):
		ui.ScriptWindow.__init__(self)
		self.wndPrivateShop = mainwnd
		
		self.__Initialize()
		self.__InitializeValues()
		self.__LoadWindow()
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def __Initialize(self):
		self.reload_event = None
		self.close_event = None
		
		self.min_level_el = None
		self.clean_min_level_el = None
		
		self.max_level_el = None
		self.clean_max_level_el = None
		
		self.dh_min_el = None
		self.clean_dh_min_el = None
		
		self.dh_max_el = None
		self.clean_dh_max_el = None
		
		self.dm_min_el = None
		self.clean_dm_min_el = None
		
		self.dm_max_el = None
		self.clean_dm_max_el = None
		
		self.item_level_textline = None
		self.expand_item_level_textline = None
		
		self.acce_abs_textline = None
		self.expand_acce_abs_textline = None
		
		self.alchemy_textline = None
		self.expand_alchemy_textline = None
		
		self.item_bonus_textline = None
		self.expand_item_bonus_textline = None
		
		self.block_filter = None
		
		self.actual_listbox = -1
		self.v_filter_list_box = []
		
		self.gener_buttons = []
		self.manage_buttons = []
		
		self.error_popup_dialog = uiCommon.PopupDialog()
	
	def __InitializeValues(self):
		self.item_level_value = -1
		self.acce_abs_value = -1
		self.ds_clarity_value = -1
		self.bonus_choose = -1
		self.gender = -1
	
	def __GetPlayerGender(self):
		return chr.RaceToSex(player.GetRace())

	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/newprivateshopsearchfilter.py")
			
			self.min_level_el = self.GetChild("min_level_el")
			self.min_level_el.SetPlaceHolder(localeInfo.NEW_PRIVATESHOP_FILTER_PLACEHOLDER_1)
			self.min_level_el.SetUpdateEvent(ui.__mem_func__(self.UpdateVarTextline), "min_level")
			self.min_level_el.SetPlaceHolderColor(0xff2f2f2f)
			self.min_level_el.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))
			self.min_level_el.SetFocus()
			
			self.max_level_el = self.GetChild("max_level_el")
			self.max_level_el.SetPlaceHolder(localeInfo.NEW_PRIVATESHOP_FILTER_PLACEHOLDER_2)
			self.max_level_el.SetUpdateEvent(ui.__mem_func__(self.UpdateVarTextline), "max_level")
			self.max_level_el.SetPlaceHolderColor(0xff2f2f2f)
			self.max_level_el.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))

			self.dh_min_el = self.GetChild("dh_min_el")
			self.dh_min_el.SetPlaceHolder(localeInfo.NEW_PRIVATESHOP_FILTER_PLACEHOLDER_3)
			self.dh_min_el.SetUpdateEvent(ui.__mem_func__(self.UpdateVarTextline), "dh_min")
			self.dh_min_el.SetPlaceHolderColor(0xff2f2f2f)
			self.dh_min_el.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))

			self.dh_max_el = self.GetChild("dh_max_el")
			self.dh_max_el.SetPlaceHolder(localeInfo.NEW_PRIVATESHOP_FILTER_PLACEHOLDER_4)
			self.dh_max_el.SetUpdateEvent(ui.__mem_func__(self.UpdateVarTextline), "dh_max")
			self.dh_max_el.SetPlaceHolderColor(0xff2f2f2f)
			self.dh_max_el.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))

			self.dm_min_el = self.GetChild("dm_min_el")
			self.dm_min_el.SetPlaceHolder(localeInfo.NEW_PRIVATESHOP_FILTER_PLACEHOLDER_5)
			self.dm_min_el.SetUpdateEvent(ui.__mem_func__(self.UpdateVarTextline), "dm_min")
			self.dm_min_el.SetPlaceHolderColor(0xff2f2f2f)
			self.dm_min_el.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))

			self.dm_max_el = self.GetChild("dm_max_el")
			self.dm_max_el.SetPlaceHolder(localeInfo.NEW_PRIVATESHOP_FILTER_PLACEHOLDER_6)
			self.dm_max_el.SetUpdateEvent(ui.__mem_func__(self.UpdateVarTextline), "dm_max")
			self.dm_max_el.SetPlaceHolderColor(0xff2f2f2f)
			self.dm_max_el.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))
			
			self.item_level_textline = self.GetChild("item_level_textline")
			self.item_level_textline.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_ITEM_LEVEL)
			
			self.expand_item_level_textline = self.GetChild("expand_item_level_textline")
			item_level_drop_down = NewPrivateShopFilterListBox(self)
			(item_level_down_pos_x, item_level_down_pos_y) = self.expand_item_level_textline.GetLocalPosition()
			item_level_drop_down.SetPosition(15, item_level_down_pos_y + 25 + 63)
			item_level_drop_down.SetClickEvent(ui.__mem_func__(self.OnClickInListBox), 0)
			item_level_drop_down.ClearList()
			item_level_drop_down.CloseList()
			self.v_filter_list_box.append(item_level_drop_down)
			
			self.acce_abs_textline = self.GetChild("acce_abs_textline")
			self.acce_abs_textline.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_ACCE_ABS)
			
			self.expand_acce_abs_textline = self.GetChild("expand_acce_abs_textline")
			acce_abs_drop_down = NewPrivateShopFilterListBox(self)
			(acce_abs_down_pos_x, acce_abs_down_pos_y) = self.expand_acce_abs_textline.GetLocalPosition()
			acce_abs_drop_down.SetPosition(15, acce_abs_down_pos_y + 25 + 152)
			acce_abs_drop_down.SetClickEvent(ui.__mem_func__(self.OnClickInListBox), 1)
			acce_abs_drop_down.ClearList()
			acce_abs_drop_down.CloseList()
			self.v_filter_list_box.append(acce_abs_drop_down)
			
			self.alchemy_textline = self.GetChild("alchemy_textline")
			self.alchemy_textline.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_ALCHEMY)
			
			self.expand_alchemy_textline = self.GetChild("expand_alchemy_textline")
			alchemy_drop_down = NewPrivateShopFilterListBox(self)
			(alchemy_down_pos_x, alchemy_down_pos_y) = self.expand_alchemy_textline.GetLocalPosition()
			alchemy_drop_down.SetPosition(15, alchemy_down_pos_y + 25 + 183)
			alchemy_drop_down.SetClickEvent(ui.__mem_func__(self.OnClickInListBox), 2)
			alchemy_drop_down.ClearList()
			alchemy_drop_down.CloseList()
			self.v_filter_list_box.append(alchemy_drop_down)
			
			self.item_bonus_textline = self.GetChild("item_bonus_textline")
			self.item_bonus_textline.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_BONUS)
			
			self.expand_item_bonus_textline = self.GetChild("expand_item_bonus_textline")
			item_bonus_down = NewPrivateShopFilterListBox(self)
			(item_bonus_down_pos_x, item_bonus_down_pos_y) = self.expand_item_bonus_textline.GetLocalPosition()
			item_bonus_down.SetPosition(15, item_bonus_down_pos_y  + 25 + 213)
			item_bonus_down.SetClickEvent(ui.__mem_func__(self.OnClickInListBox), 3)
			item_bonus_down.ClearList()
			item_bonus_down.CloseList()
			self.v_filter_list_box.append(item_bonus_down)
			
			self.gener_buttons.append(self.GetChild("f_rbutton"))
			self.gener_buttons.append(self.GetChild("m_rbutton"))
			
			self.manage_buttons.append(self.GetChild("clear_button"))
			self.manage_buttons.append(self.GetChild("apply_button"))
			
			self.clean_min_level_el = self.GetChild("clean_min_level_el")
			self.clean_min_level_el.SetEvent(ui.__mem_func__(self.CleanVarTextline), "min_level")
			self.clean_min_level_el.Hide()
			
			self.clean_max_level_el = self.GetChild("clean_max_level_el")
			self.clean_max_level_el.SetEvent(ui.__mem_func__(self.CleanVarTextline), "max_level")
			self.clean_max_level_el.Hide()
			
			self.clean_dh_min_el = self.GetChild("clean_dh_min_el")
			self.clean_dh_min_el.SetEvent(ui.__mem_func__(self.CleanVarTextline), "dh_min")
			self.clean_dh_min_el.Hide()
			
			self.clean_dh_max_el = self.GetChild("clean_dh_max_el")
			self.clean_dh_max_el.SetEvent(ui.__mem_func__(self.CleanVarTextline), "dh_max")
			self.clean_dh_max_el.Hide()
			
			self.clean_dm_min_el = self.GetChild("clean_dm_min_el")
			self.clean_dm_min_el.SetEvent(ui.__mem_func__(self.CleanVarTextline), "dm_min")
			self.clean_dm_min_el.Hide()
			
			self.clean_dm_max_el = self.GetChild("clean_dm_max_el")
			self.clean_dm_max_el.SetEvent(ui.__mem_func__(self.CleanVarTextline), "dm_max")
			self.clean_dm_max_el.Hide()
			
			self.block_filter = self.GetChild("block_filter")
			self.block_filter.Hide()
			
		except:	exception.Abort("PrivateShopFilterWindow.__LoadWindow.UIScript/newprivateshopsearchfilter.py")
		
		try:
			self.GetChild("TitleBar").SetCloseEvent(ui.__mem_func__(self.Close))
			
			self.min_level_el.SetTabEvent(ui.__mem_func__(self.max_level_el.SetFocus))
			self.max_level_el.SetTabEvent(ui.__mem_func__(self.dh_min_el.SetFocus))
			self.dh_min_el.SetTabEvent(ui.__mem_func__(self.dh_max_el.SetFocus))
			self.dh_max_el.SetTabEvent(ui.__mem_func__(self.dm_min_el.SetFocus))
			self.dm_min_el.SetTabEvent(ui.__mem_func__(self.dm_max_el.SetFocus))
			self.dm_max_el.SetTabEvent(ui.__mem_func__(self.min_level_el.SetFocus))
			
			self.expand_item_level_textline.SetEvent(ui.__mem_func__(self.ToggleListBox), 0)
			self.expand_acce_abs_textline.SetEvent(ui.__mem_func__(self.ToggleListBox), 1)
			self.expand_alchemy_textline.SetEvent(ui.__mem_func__(self.ToggleListBox), 2)
			self.expand_item_bonus_textline.SetEvent(ui.__mem_func__(self.ToggleListBox), 3)
			self.__LoadListBox()
			
			self.gener_buttons[0].SetEvent(ui.__mem_func__(self.ChooseGender), 0)
			self.gener_buttons[1].SetEvent(ui.__mem_func__(self.ChooseGender), 1)
			self.ChooseGender(-1)
			
			self.manage_buttons[0].SetEvent(ui.__mem_func__(self.__ResetAllPage))
			self.manage_buttons[1].SetEvent(ui.__mem_func__(self.__ApplyFilterOptions))

		except:	exception.Abort("PrivateShopFilterWindow.__LoadWindow.Error_loading_events")
	
	def CleanVarTextline(self, arg):
		arg_list = ["min_level", "max_level", "dh_min", "dh_max", "dm_min", "dm_max"]
		if not arg in arg_list:
			return
		
		if arg == "min_level":
			self.min_level_el.SetText("")
			self.clean_min_level_el.Hide()
		elif arg == "max_level":
			self.max_level_el.SetText("")
			self.clean_max_level_el.Hide()
		elif arg == "dh_min":
			self.dh_min_el.SetText("")
			self.clean_dh_min_el.Hide()
		elif arg == "dh_max":
			self.dh_max_el.SetText("")
			self.clean_dh_max_el.Hide()
		elif arg == "dm_min":
			self.dm_min_el.SetText("")
			self.clean_dm_min_el.Hide()
		elif arg == "dm_max":
			self.dm_max_el.SetText("")
			self.clean_dm_max_el.Hide()
		
		self.__UpdatePlaceHolders()
	
	def UpdateVarTextline(self, arg):
		arg_list = ["min_level", "max_level", "dh_min", "dh_max", "dm_min", "dm_max"]
		if not arg in arg_list:
			return

		if arg == "min_level":
			if len(self.min_level_el.GetText()) != 0:
				self.clean_min_level_el.Show()
			else:
				self.clean_min_level_el.Hide()
			
		elif arg == "max_level":
			if len(self.max_level_el.GetText()) != 0:
				self.clean_max_level_el.Show()
			else:
				self.clean_max_level_el.Hide()
		
		elif arg == "dh_min":
			if len(self.dh_min_el.GetText()) != 0:
				self.clean_dh_min_el.Show()
			else:
				self.clean_dh_min_el.Hide()
		
		elif arg == "dh_max":
			if len(self.dh_max_el.GetText()) != 0:
				self.clean_dh_max_el.Show()
			else:
				self.clean_dh_max_el.Hide()
		
		elif arg == "dm_min":
			if len(self.dm_min_el.GetText()) != 0:
				self.clean_dm_min_el.Show()
			else:
				self.clean_dm_min_el.Hide()
		
		elif arg == "dm_max":
			if len(self.dm_max_el.GetText()) != 0:
				self.clean_dm_max_el.Show()
			else:
				self.clean_dm_max_el.Hide()
	
	def ChooseGender(self, gender):
		if self.ErrorPopUpIsOpened() is False:
			self.gener_buttons[not gender].Down()
			self.gener_buttons[gender].SetUp()
			return
		
		if gender == -1:
			self.gener_buttons[0].SetUp()
			self.gener_buttons[1].SetUp()
			self.gender = -1
			return
		
		self.gener_buttons[gender].Down()
		self.gener_buttons[not gender].SetUp()
		self.gender = gender
	
	def OnClickInListBox(self, list_index, name, index):
		list_index = list_index[0]
		
		text_index = [
			(self.item_level_textline, localeInfo.NEW_PRIVATESHOP_FILTER_ITEM_LEVEL),
			(self.acce_abs_textline, localeInfo.NEW_PRIVATESHOP_FILTER_ACCE_ABS),
			(self.alchemy_textline, localeInfo.NEW_PRIVATESHOP_FILTER_ALCHEMY),
			(self.item_bonus_textline, localeInfo.NEW_PRIVATESHOP_FILTER_BONUS)
		]
		
		text_obj, base_text = text_index[list_index]
		text_obj.SetText(base_text) if index == -1 else text_obj.SetText(name)
		
		if list_index == 0:
			self.item_level_value  = index
		elif list_index == 1:
			self.acce_abs_value  = index
		elif list_index == 2:
			self.ds_clarity_value  = index
		elif list_index == 3:
			self.bonus_choose  = index
		
		list = self.v_filter_list_box[list_index]
		list.CloseList()
		self.actual_listbox = -1
	
	def ForceResetFilter(self):
		self.__ResetAllPage()

	def __ResetAllPage(self):
		if not self.error_popup_dialog:
			write("error 0xff")
			return
		
		if self.error_popup_dialog.IsShow():
			write(localeInfo.NEW_PRIVATESHOP_FILTER_CLOSE_FIRST_ADVISE)
			return
		
		self.min_level_el.SetText("")
		self.max_level_el.SetText("")
		self.dh_min_el.SetText("")
		self.dh_max_el.SetText("")
		self.dm_min_el.SetText("")
		self.dm_max_el.SetText("")
		self.ChooseGender(-1)
		self.item_level_textline.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_ITEM_LEVEL)
		self.acce_abs_textline.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_ACCE_ABS)
		self.alchemy_textline.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_ALCHEMY)
		self.item_bonus_textline.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_BONUS)

		self.clean_min_level_el.Hide()
		self.clean_max_level_el.Hide()
		self.clean_dh_min_el.Hide()
		self.clean_dh_max_el.Hide()
		self.clean_dm_min_el.Hide()
		self.clean_dm_max_el.Hide()
		
		self.__InitializeValues()
		self.__UpdatePlaceHolders()
		
		for list in self.v_filter_list_box:
			list.ForceButton(0)
			list.CloseList()
		self.actual_listbox = -1
		self.min_level_el.SetFocus()
		
		if self.reload_event:
			self.reload_event(self.GetFilterOptions())
		
		write(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_RELOADED)
	
	def ErrorPopUpIsOpened(self):
		if not self.error_popup_dialog:
			write("error 0xff")
			return False
		
		if self.error_popup_dialog.IsShow():
			write(localeInfo.NEW_PRIVATESHOP_FILTER_CLOSE_FIRST_ADVISE)
			return False
		
		return True
	
	def OnUpdate(self):
		if self.error_popup_dialog and self.error_popup_dialog.IsShow():
			self.block_filter.Show()
		else:
			if self.block_filter.IsShow():
				self.block_filter.Hide()
	
	def OnTop(self):
		if self.error_popup_dialog and self.error_popup_dialog.IsShow():
			self.error_popup_dialog.SetTop()
	
	def CheckEditLinesValues(self):
		if self.ErrorPopUpIsOpened() is False:
			return
		
		if len(self.min_level_el.GetText()) != 0:
			min_level = int(self.min_level_el.GetText())
			if len(self.max_level_el.GetText()):
				max_level = int(self.max_level_el.GetText())
				if min_level > max_level:
					self.error_popup_dialog.Open()
					self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF1)
					return False
				elif min_level > MAX_SERVER_LEVEL:
					self.error_popup_dialog.Open()
					self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF2 % MAX_SERVER_LEVEL)
					return False
			elif min_level > MAX_SERVER_LEVEL:
				self.error_popup_dialog.Open()
				self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF3 % MAX_SERVER_LEVEL)
				return False
		
		if len(self.max_level_el.GetText()) != 0:
			max_level = int(self.max_level_el.GetText())
			if max_level > MAX_SERVER_LEVEL:
				self.error_popup_dialog.Open()
				self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF4 % MAX_SERVER_LEVEL)
				return False

		if len(self.dh_min_el.GetText()) != 0:
			min_dh = int(self.dh_min_el.GetText())
			if len(self.dh_max_el.GetText()):
				dh_max = int(self.dh_max_el.GetText())
				if min_dh > dh_max:
					self.error_popup_dialog.Open()
					self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF5)
					return False
				elif min_dh > MAX_DH:
					self.error_popup_dialog.Open()
					self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF6 % MAX_DH)
					return False
			elif min_dh > MAX_DH:
				self.error_popup_dialog.Open()
				self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF7 % MAX_DH)
				return False

		if len(self.dh_max_el.GetText()) != 0:
			dh_max = int(self.dh_max_el.GetText())
			if dh_max > MAX_DH:
				self.error_popup_dialog.Open()
				self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF8 % MAX_DH)
				return False

		if len(self.dm_min_el.GetText()) != 0:
			min_dm = int(self.dm_min_el.GetText())
			if len(self.dm_max_el.GetText()):
				dm_max = int(self.dm_max_el.GetText())
				if min_dm > dm_max:
					self.error_popup_dialog.Open()
					self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF9)
					return False
				elif min_dm > MAX_DM:
					self.error_popup_dialog.Open()
					self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF10 % MAX_DM)
					return False
			elif min_dm > MAX_DM:
				self.error_popup_dialog.Open()
				self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF11 % MAX_DM)
				return False

		if len(self.dm_max_el.GetText()) != 0:
			dm_max = int(self.dm_max_el.GetText())
			if dm_max > MAX_DM:
				self.error_popup_dialog.Open()
				self.error_popup_dialog.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_VERF12 % MAX_DM)
				return False
		
		return True
	
	def __ApplyFilterOptions(self):
		if self.CheckEditLinesValues() is False:
			return
		
		for list in self.v_filter_list_box:
			list.CloseList()
		self.actual_listbox = -1
		self.min_level_el.SetFocus()
		
		if self.reload_event:
			self.reload_event(self.GetFilterOptions())
		
		self.Close()
		
		write(localeInfo.NEW_PRIVATESHOP_FILTER_FILTER_APPLY)
	
	def GetFilterOptions(self):
		return (
				int(self.min_level_el.GetText()) if len(self.min_level_el.GetText()) != 0 else -1,\
				int(self.max_level_el.GetText()) if len(self.max_level_el.GetText()) != 0 else -1,\
				int(self.dh_min_el.GetText()) if len(self.dh_min_el.GetText()) != 0 else -1,\
				int(self.dh_max_el.GetText()) if len(self.dh_max_el.GetText()) != 0 else -1,\
				int(self.dm_min_el.GetText()) if len(self.dm_min_el.GetText()) != 0 else -1,\
				int(self.dm_max_el.GetText()) if len(self.dm_max_el.GetText()) != 0 else -1,\
				self.item_level_value,\
				self.acce_abs_value,\
				self.ds_clarity_value,\
				self.bonus_choose,\
				self.gender,\
			)
	
	def __LoadListBox(self):
		base_text = "Limpar Opção"
		
		bonus_list = []
		for item_sep in uiToolTip.ItemToolTip.AFFECT_DICT.items():
			(key, text) = item_sep[0], item_sep[1](0)
			bonus_list.append((key, text.replace("0", "?")))
		
		listBox_itens = {
			0 : ([("+{}".format(x), x) for x in xrange(10)], 6),
			1 : ([("{}%".format(x + 1), x+1) for x in xrange(10, 25)], 6),
			2 : ([("Crua", 0), ("Talhada", 1), ("Rara", 2), ("Antiga", 3), ("Lendária", 4), ("Mítica", 5)], 5),
			3 : ([("{}".format(y), x) for x, y in bonus_list], 4),
		}
		
		for box_key in listBox_itens.keys():
			list_box = self.v_filter_list_box[box_key]
			list_box.AddItem(base_text, -1)
			
			itens, listMax = listBox_itens[box_key]
			list_box.SetMax(listMax + 1)
			for item_name, item_key in itens:
				list_box.AddItem(item_name, item_key)
	
	def ToggleListBox(self, index):
		if self.ErrorPopUpIsOpened() is False:
			return
		
		listBoxChoose = self.v_filter_list_box[index]
		
		if self.actual_listbox == index:
			if listBoxChoose.IsShow():
				listBoxChoose.CloseList()
			self.actual_listbox = -1
		else:
			for listbox in self.v_filter_list_box:
				listbox.CloseList()
			
			self.v_filter_list_box[index].OpenList()
			self.actual_listbox = index
	
	def __UpdatePlaceHolders(self):
		if self.min_level_el:
			self.min_level_el.UpdatePlaceHolder()
		if self.max_level_el:
			self.max_level_el.UpdatePlaceHolder()
		if self.dh_min_el:
			self.dh_min_el.UpdatePlaceHolder()
		if self.dh_max_el:
			self.dh_max_el.UpdatePlaceHolder()
		if self.dm_min_el:
			self.dm_min_el.UpdatePlaceHolder()
		if self.dm_max_el:
			self.dm_max_el.UpdatePlaceHolder()
	
	def Open(self):
		self.SetCenterPosition()
		self.Show()
		self.SetTop()
		
		self.__UpdatePlaceHolders()
	
	def Close(self, runEvent = True):
		if self.error_popup_dialog:
			self.error_popup_dialog.Close()
		
		self.Hide()
		
		if runEvent is True:
			if self.close_event:
				self.close_event()
		
	def SetCloseEvent(self, event):
		self.close_event = event
	
	def SetReloadVarEvent(self, event):
		self.reload_event = event
	
	def OnRunMouseWheel(self, nLen):
		for listbox in self.v_filter_list_box:
			if listbox.IsShow():
				listbox.OnRunMouseWheel(nLen)
	
	def OnPressEscapeKey(self):
		self.Close()
		return True

class PrivateShopFilterButton(ui.ScriptWindow):
	SPECIAL_CATEGORY_DOWN_COLOR = grp.GenerateColor((255.0/255.0), (168.0/255.0), 0.0, 1.0)
	CATEGORY_DOWN_COLOR = 0xFFFEE3AE
	CATEGORY_UP_COLOR = grp.GenerateColor(1.0, 1.0, 1.0, 1.0)
	
	def __init__(self, parent):
		def __init_window__():
			self.SetParent(parent)
			self.SetSize(185, 34)
		
		ui.ScriptWindow.__init__(self)
		__init_window__()
		self.__Initialize()
		self.__LoadWindow()
	
	def __Initialize(self):
		self.index_cat = 0
		self.category_key = "None"
		
		self.click_event = None
		self.base_pos = (0, 0)
		
		self.is_open = 0
		self.can_show_image = True
		
		self.base_button_im = None
		self.category_text = None
		self.category_icon = None
		self.base_button_inv = None
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def __LoadWindow(self):
		self.base_button_im = ui.MakeExpandedImageBox(self, MAIN_PATH + "left_side/category_button.tga", 0, 0)
		self.category_icon = ui.MakeExpandedImageBox(self.base_button_im, MAIN_PATH + "left_side/cat_icon/mineiros.tga", 10, 9)
		self.category_text = ui.MakeTextLine(self.base_button_im)
		self.category_text.SetWindowHorizontalAlignLeft()
		self.category_text.SetHorizontalAlignLeft()
		self.category_text.SetPosition(33, -2)
		
		self.base_button_inv = ui.MakeExpandedImageBox(self, MAIN_PATH + "left_side/category_button_inv.tga", 0, 0)
		self.base_button_inv.SAFE_SetStringEvent("MOUSE_CLICK", self.OnButtonClick)
	
	def OnButtonClick(self):
		if self.index_cat != 0:
			self.is_open = 0 if self.is_open == 1 else 1
		
		if self.click_event:
			self.click_event(self.index_cat)
	
	def ForceCloseCategory(self):
		self.is_open = 0
		self.ResetTextColor()
	
	def SetSpecialUpButton(self):
		self.category_text.SetPackedFontColor(self.SPECIAL_CATEGORY_DOWN_COLOR)
	
	def SetUpButton(self):
		self.category_text.SetPackedFontColor(self.CATEGORY_DOWN_COLOR)
	
	def ResetTextColor(self):
		self.category_text.SetPackedFontColor(self.CATEGORY_UP_COLOR)
	
	def SetCategoryIndexAndKey(self, index, category_key):
		self.index_cat = index
		self.category_key = category_key
	
	def SetButtonBasePosition(self, pos):
		self.base_pos = pos
	
	def SetClickEvent(self, event):
		self.click_event = event
	
	def SetCategoryText(self, text):
		if not self.category_text:	return
		self.category_text.SetText(str(text))
	
	def SetCategoryIcon(self, image, pos):
		if image == "None":
			self.can_show_image = False
			self.category_icon.Hide()
			return
		
		self.category_icon.LoadImage(MAIN_PATH + "left_side/cat_icon/{}.tga".format(image))
		self.category_icon.SetPosition(*pos)
	
	def GetButtonBasePosition(self):
		return self.base_pos
	
	def GetButtonHeight(self):
		return self.GetHeight()
	
	def IsOpen(self):
		return self.is_open
	
	def SetHeightPercentageBottom(self, percentage):
		self.category_text.Hide() if percentage >= 75 else self.category_text.Show()
		
		if self.can_show_image is True:
			self.category_icon.Hide() if percentage >= 95 else self.category_icon.Show()
		
		self.base_button_im.SetRenderingRect(0.0, 0.0, 0.0, -(float(percentage) / 100.0))
		self.base_button_inv.SetRenderingRect(0.0, 0.0, 0.0, -(float(percentage) / 100.0))
	
	def SetHeightPercentageTop(self, percentage):
		self.category_text.Hide() if percentage >= 75 else self.category_text.Show()
		
		if self.can_show_image is True:
			self.category_icon.Hide() if percentage >= 95 else self.category_icon.Show()
		
		self.base_button_im.SetRenderingRect(0.0, -(float(percentage) / 100.0), 0.0, 0.0)
		self.base_button_inv.SetRenderingRect(0.0, -(float(percentage) / 100.0), 0.0, 0.0)

class PrivateShopListBoxButton(ui.ScriptWindow):
	def __init__(self, parent):
		ui.ScriptWindow.__init__(self)
		self.__Initialize()
		
		self.SetParent(parent)
		self.Show()
	
	def __Initialize(self):
		self.is_down = False
		self.v_button_images = []
		
		self.eventFunc = None
		self.eventArgs = None
		
		self.button = None
		self.textline = None
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def CreateButton(self, list_images):
		self.v_button_images = list_images
		self.button = ui.MakeExpandedImageBox(self, self.v_button_images[0], 0, 0)
		self.button.SAFE_SetStringEvent("MOUSE_OVER_IN", self.OnHover)
		self.button.SAFE_SetStringEvent("MOUSE_OVER_OUT", self.OnOut)
		self.button.SAFE_SetStringEvent("MOUSE_CLICK", self.OnButtonClick)
		
		self.textline = ui.MakeTextLine(self.button)
		self.textline.SetWindowHorizontalAlignLeft()
		self.textline.SetHorizontalAlignLeft()
		self.textline.SetPosition(15, -1)
		
		self.SetSize(self.button.GetWidth(), self.button.GetHeight())
	
	def SetButtonEvent(self, func, *args):
		self.eventFunc = func
		self.eventArgs = args
	
	def SetButtonText(self, text):
		self.textline.SetText(str(text))
	
	def SetUpButton(self):
		self.is_down = False
		self.button.LoadImage(self.v_button_images[0])
	
	def SetDownButton(self):
		self.is_down = True
		self.button.LoadImage(self.v_button_images[2])
	
	def OnHover(self):
		if self.is_down is True:
			return
		
		self.button.LoadImage(self.v_button_images[1])
	
	def OnOut(self):
		if self.is_down is True:
			return
		
		self.button.LoadImage(self.v_button_images[0])
	
	def OnButtonClick(self):
		if self.is_down is True:
			return
		
		self.button.LoadImage(self.v_button_images[2])
		self.is_down = True
		apply(self.eventFunc, self.eventArgs)
	
	def SetHeightPercentageBottom(self, percentage):
		self.textline.Hide() if percentage >= 75 else self.textline.Show()
		self.button.SetRenderingRect(0.0, 0.0, 0.0, -(float(percentage) / 100.0))
	
	def SetHeightPercentageTop(self, percentage):
		self.textline.Hide() if percentage >= 75 else self.textline.Show()
		self.button.SetRenderingRect(0.0, -(float(percentage) / 100.0), 0.0, 0.0)
	
class PrivateShopFilterCategoryList(ui.ScriptWindow):
	def __init__(self, parent):
		ui.ScriptWindow.__init__(self)
		self.SetParent(parent)
		
		self.__Initialize()
		self.__LoadBox()
	
	def __Initialize(self):
		self.base_size = (0, 0)
		self.index_cat = 0
		
		self.click_event = None
		
		self.horizontalLine_top = None
		self.horizontalLine_left = None
		self.horizontalLine_right = None
		self.horizontalLine_bottom = None
		
		self.button_elements = []
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def __LoadBox(self):
		self.horizontalLine_top = ui.Line()
		self.horizontalLine_top.SetParent(self)
		self.horizontalLine_top.SetPosition(0, 0)
		self.horizontalLine_top.SetColor(0xFFFFFFFF)
		self.horizontalLine_top.SetSize(182, 0)
		self.horizontalLine_top.Show()
		
		self.horizontalLine_left = ui.Line()
		self.horizontalLine_left.SetParent(self)
		self.horizontalLine_left.SetPosition(0, 0)
		self.horizontalLine_left.SetColor(0xFFFFFFFF)
		self.horizontalLine_left.SetSize(0, 0)
		self.horizontalLine_left.Show()
		
		self.horizontalLine_right = ui.Line()
		self.horizontalLine_right.SetParent(self)
		self.horizontalLine_right.SetPosition(4, 0)
		self.horizontalLine_right.SetWindowHorizontalAlignRight()
		self.horizontalLine_right.SetColor(0xFFFFFFFF)
		self.horizontalLine_right.SetSize(0, 0)
		self.horizontalLine_right.Show()
		
		self.horizontalLine_bottom = ui.Line()
		self.horizontalLine_bottom.SetParent(self)
		self.horizontalLine_bottom.SetPosition(0, 2)
		self.horizontalLine_bottom.SetWindowVerticalAlignBottom()
		self.horizontalLine_bottom.SetColor(0xFFFFFFFF)
		self.horizontalLine_bottom.SetSize(182, 0)
		self.horizontalLine_bottom.Show()
	
	def SetListElements(self, v_Elements):
		index = 0
		for button_name in v_Elements:
			tmpButton = PrivateShopListBoxButton(self)
			images = [MAIN_PATH + "left_side/sub_cat_up.tga",
						MAIN_PATH + "left_side/sub_cat_hover.tga",
						MAIN_PATH + "left_side/sub_cat_hover.tga"]
			tmpButton.CreateButton(images)
			tmpButton.SetButtonEvent(ui.__mem_func__(self.ClickOnElement), index)
			tmpButton.SetButtonText(button_name)
			tmpButton.SetPosition(0, 30*index)
			self.button_elements.append(tmpButton)
			index += 1
		self.ReloadListInfo()
	
	def ReloadListInfo(self):
		widht = 185
		height = len(self.button_elements) * 30
		
		self.base_size = (widht ,height)
		self.SetSize(*self.base_size)
		self.horizontalLine_left.SetSize(0, height)
		self.horizontalLine_right.SetSize(0, height)
	
	def ClickOnElement(self, index):
		for button_index in xrange(len(self.button_elements)):
			button = self.button_elements[button_index]
			if button_index != index:	button.SetUpButton()
		
		if self.click_event:
			self.click_event(index, self.index_cat)
	
	def SetUpAllList(self):
		for button in self.button_elements:
			button.SetUpButton()
	
	def SetClickEvent(self, event):
		self.click_event = event
	
	def SetCategoryIndex(self, index):
		self.index_cat = index
	
	def GetListHeight(self):
		return self.GetHeight()
	
	def SetHeightPercentageBottom(self, percentage):
		size_hided = (self.GetListHeight() * percentage) / 100
		(x_base, y_base) = self.base_size
		new_height = y_base - size_hided
		
		self.horizontalLine_left.SetPosition(0, 0)
		self.horizontalLine_left.SetSize(0, new_height)
		self.horizontalLine_right.SetPosition(4, 0)
		self.horizontalLine_right.SetSize(0, new_height)
		
		if percentage == 0:
			self.horizontalLine_top.Show()
			self.horizontalLine_bottom.Show()
		else:
			if percentage == 100:
				self.horizontalLine_top.Hide()
			self.horizontalLine_bottom.Hide()
		
		button_number = float(percentage) * float(len(self.button_elements)) / 100.0
		loop_times = int(math.ceil(button_number))
		
		for button in self.button_elements:
			button.SetHeightPercentageBottom(0)
		
		cut_start = len(self.button_elements) - 1
		for index in xrange(loop_times):
			button = self.button_elements[cut_start - index]
			if button_number >= 1.0:
				button.SetHeightPercentageBottom(100)
				button_number -= 1.0
			else:
				button.SetHeightPercentageBottom(int(button_number*100.0))
				button_number = 0.0

	def SetHeightPercentageTop(self, percentage):
		size_hided = (self.GetListHeight() * percentage) / 100
		(x_base, y_base) = self.base_size
		new_height = y_base - size_hided
		
		self.horizontalLine_left.SetPosition(0, size_hided)
		self.horizontalLine_left.SetSize(0, new_height)
		self.horizontalLine_right.SetPosition(4, size_hided)
		self.horizontalLine_right.SetSize(0, new_height)
		
		if percentage == 0:
			self.horizontalLine_top.Show()
			self.horizontalLine_bottom.Show()
		else:
			if percentage >= 100:
				self.horizontalLine_bottom.Hide()
			self.horizontalLine_top.Hide()
		
		button_number = float(percentage) * float(len(self.button_elements)) / 100.0
		loop_times = int(math.ceil(button_number))
		
		for button in self.button_elements:
			button.SetHeightPercentageTop(0)
		
		for index in xrange(loop_times):
			button = self.button_elements[index]
			if button_number >= 1.0:
				button.SetHeightPercentageTop(100)
				button_number -= 1.0
			else:
				button.SetHeightPercentageTop(int(button_number*100.0))
				button_number = 0.0

class PrivateShopResultButton(ui.ScriptWindow):
	def __init__(self, parent):
		ui.ScriptWindow.__init__(self)
		self.SetParent(parent)
		
		self.__Initialize()
		self.Show()
	
	def __Initialize(self):
		self.base_size = (0,0)
		self.simulate_page_size = (0,0)
		self.simulate_page_y = 0
		self.base_pos = (0,0)
		
		self.itemVnum = 0
		self.itemName = ""
		self.sellerName = ""
		self.count = 0
		self.price = 0
		self.shopTime = 0
		self.player_map_index = 0
		self.off_shop_map_index = 0
		self.item_id = 0
		self.shopPos = 0
		self.page = 0
		self.result_per_page = 0

		# if app.ENABLE_CHANGE_LOOK_SYSTEM:
		# self.icon_image_change_look = None
		# self.message_button = None
		# self.money_image = None
		# self.shop_time_txt = None
		# self.item_price_txt = None
		# self.item_quantity = None
		# self.item_name_txt = None
		# self.slot_base_image = None
		# self.icon_image = None
		# self.horizontalLine_bottom = None
		
		self.message_button_tooltip = None
		self.toolTipItem = None
		self.interface = None
		self.wndPrivateShopSearch = None
		
		self.ismyownItem = False
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def SetMainPage(self, wndMain):
		self.wndPrivateShopSearch = wndMain
	
	def SetInterface(self, interface):
		self.interface = interface
	
	def SetItemToolTip(self, tooltip):
		self.toolTipItem = tooltip
	
	def GetRealSlot(self):
		return (self.result_per_page * self.page) + self.shopPos
	
	def CreateButton(self, itemSize):
		window_height = 32* itemSize + 40
		self.SetSize(568, window_height)
		self.base_size = (568, window_height)
		self.simulate_page_size = (568, window_height)
		
		self.horizontalLine_bottom = ui.Line()
		self.horizontalLine_bottom.SetParent(self)
		self.horizontalLine_bottom.SetPosition(0, 0)
		self.horizontalLine_bottom.SetWindowVerticalAlignBottom()
		self.horizontalLine_bottom.SetColor(0xFF564b47)
		self.horizontalLine_bottom.SetSize(568, 0)
		self.horizontalLine_bottom.Show()
		
		self.slot_base_image = ui.MakeExpandedImageBox(self, MAIN_PATH + "right_side/{}_slot.tga".format(itemSize), 25, 0)
		self.slot_base_image.SAFE_SetStringEvent("MOUSE_CLICK", self.OnMouseLeftButtonDown)
		self.slot_base_image.SAFE_SetStringEvent("MOUSE_RCLICK", self.OnMouseRightButtonDown)
		self.slot_base_image.SetWindowVerticalAlignCenter()
		
		self.icon_image = ui.MakeExpandedImageBox(self.slot_base_image, MAIN_PATH + "right_side/{}_slot.tga".format(itemSize), 0, 0)
		self.icon_image.SAFE_SetStringEvent("MOUSE_OVER_IN", self.OnHover)
		self.icon_image.SAFE_SetStringEvent("MOUSE_OVER_OUT", self.OnOut)
		self.icon_image.SAFE_SetStringEvent("MOUSE_CLICK", self.OnMouseLeftButtonDown)
		self.icon_image.SAFE_SetStringEvent("MOUSE_RCLICK", self.OnMouseRightButtonDown)
		self.icon_image.SetWindowHorizontalAlignCenter()
		self.icon_image.SetWindowVerticalAlignCenter()

		# if app.ENABLE_CHANGE_LOOK_SYSTEM:
		# self.icon_image_change_look = ui.MakeExpandedImageBox(self.slot_base_image, "icon/item/ingame_convert_mark.tga", 4, 2)
		# self.icon_image_change_look.SAFE_SetStringEvent("MOUSE_OVER_IN", self.OnHover)
		# self.icon_image_change_look.SAFE_SetStringEvent("MOUSE_OVER_OUT", self.OnOut)
		# self.icon_image_change_look.SAFE_SetStringEvent("MOUSE_CLICK", self.OnMouseLeftButtonDown)
		# self.icon_image_change_look.SAFE_SetStringEvent("MOUSE_RCLICK", self.OnMouseRightButtonDown)
		
		self.item_quantity = ui.MakeTextLine(self)
		self.item_quantity.SetPosition(25+32+13, 0)
		self.item_quantity.SetWindowHorizontalAlignLeft()
		self.item_quantity.SetHorizontalAlignLeft()
		self.item_quantity.SetWindowVerticalAlignCenter()
		
		self.item_name_txt = ui.MakeTextLine(self)
		self.item_name_txt.SetPosition(105, 0)
		self.item_name_txt.SetWindowHorizontalAlignLeft()
		self.item_name_txt.SetWindowVerticalAlignCenter()
		self.item_name_txt.SetHorizontalAlignLeft()
		
		self.shop_time_txt = ui.MakeTextLine(self)
		self.shop_time_txt.SetPosition(320, 0)
		self.shop_time_txt.SetWindowHorizontalAlignLeft()
		self.shop_time_txt.SetWindowVerticalAlignCenter()

		self.item_price_txt = ui.MakeTextLine(self)
		self.item_price_txt.SetPosition(490, 0)
		self.item_price_txt.SetWindowHorizontalAlignLeft()
		self.item_price_txt.SetHorizontalAlignRight()
		self.item_price_txt.SetWindowVerticalAlignCenter()
		
		self.money_image = ui.MakeExpandedImageBox(self, MAIN_PATH + "right_side/money.tga".format(itemSize), 490 + 5, 2)
		self.money_image.SAFE_SetStringEvent("MOUSE_CLICK", self.OnMouseLeftButtonDown)
		self.money_image.SAFE_SetStringEvent("MOUSE_RCLICK", self.OnMouseRightButtonDown)
		self.money_image.SetWindowVerticalAlignCenter()
		
		self.message_button_tooltip = uiToolTip.ToolTip()
		self.__LoadMessageButtonTooltip()
		
		self.message_button = ui.MakeButton(self, 490 + 7 + 28, 1, "", MAIN_PATH + "right_side/", "message_norm.tga", "message_hover.tga", "message_press.tga")
		self.message_button.SetEvent(ui.__mem_func__(self.SendMensage))
		self.message_button.SetWindowVerticalAlignCenter()
		
	def OnRender(self):
		x, y = self.GetGlobalPosition()
		(widht, height) = self.simulate_page_size
		y_add = self.simulate_page_y
		
		item_state = newPrivateShopSearch.GetItemState(self.GetRealSlot())
		
		if self.ismyownItem is True:
			grp.SetColor(grp.GenerateColor((153.0/255.0), (204.0/255.0), (255.0/255.0), 0.1))
			grp.RenderBar(x, y + y_add, widht, height)
		elif item_state != 0:
			grp.SetColor(grp.GenerateColor((51.0/255.0), (102.0/255.0), (0.0/255.0), 0.1))
			if item_state != 1:
				grp.SetColor(grp.GenerateColor((255.0/255.0), (128.0/255.0), (0.0/255.0), 0.1))
			grp.RenderBar(x, y + y_add, widht, height)
		elif self.shopTime - app.GetTime() <= 0:
			grp.SetColor(grp.GenerateColor((102.0/255.0), (0.0/255.0), (0.0/255.0), 0.1))
			grp.RenderBar(x, y + y_add, widht, height)
		elif self.IsIn() or self.message_button.IsIn() or self.money_image.IsIn() or self.icon_image.IsIn() or self.slot_base_image.IsIn():
			# (app.ENABLE_CHANGE_LOOK_SYSTEM and self.icon_image_change_look.IsIn()):
			grp.SetColor(grp.GenerateColor((86.0/255.0), (75.0/255.0), (71.0/255.0), 0.3))
			grp.RenderBar(x, y + y_add, widht, height)
	
	def SetItemInfo(self, itemVnum, itemName, sellerName, count, price, shop_time, player_map_index, off_shop_map_index, item_id, shopPos, page):
		self.itemVnum = itemVnum
		self.itemName = itemName
		self.sellerName = sellerName
		self.count = count
		self.price = price
		self.shopTime = shop_time
		self.player_map_index = player_map_index
		self.off_shop_map_index = off_shop_map_index
		self.shopPos = shopPos
		self.page = page
		self.item_id = item_id
		self.ismyownItem = True if sellerName == player.GetName() else False
		
		self.__LoadMessageButtonTooltip()
	
	def __GetPlayerPremium(self):
		return chr.IsOverfallPremium()
	
	def OnMouseLeftButtonDown(self):
		new_time = self.shopTime - app.GetTime()
		if new_time <= 0:
			return

		item_state = newPrivateShopSearch.GetItemState(self.GetRealSlot())
		if item_state != 0:
			return
		
		if self.ismyownItem is True:
			return
		
		DeletePrivateShopEffect()
		
		if self.player_map_index == self.off_shop_map_index:
			write(localeInfo.NEWPRIVATE_SHOP_SEARCH_SELECT_SHOP)
			write(localeInfo.NEWPRIVATE_SHOP_SEARCH_SELECT_SHOP_ADVISE % SHOP_EFFECT_TIME)
			
			chrVID = newPrivateShopSearch.GetSearchItemShopVID(self.GetRealSlot())
			CreatePrivateShopEffect(chrVID)
		else:
			write(localeInfo.NEWPRIVATE_SHOP_SEARCH_CANT_SELECT_SHOP)
	
	def OnMouseRightButtonDown(self):
		new_time = self.shopTime - app.GetTime()
		if new_time <= 0:
			return

		item_state = newPrivateShopSearch.GetItemState(self.GetRealSlot())
		if item_state != 0:
			return

		if self.ismyownItem is True:
			return
		
		if self.__GetPlayerPremium():
			if self.wndPrivateShopSearch:
				self.wndPrivateShopSearch.BuyItemFromSystem(self.GetRealSlot(), self.itemName, self.price, self.item_id)
		else:
			write(localeInfo.NEWPRIVATE_SHOP_SEARCH_CANT_BUY_ITEM)
	
	def SetPageCut(self, page_cut_result):
		self.result_per_page = page_cut_result
	
	def __GetYangTextColor(self):
		if self.price < 500000000:
			return grp.GenerateColor(1.0, 0.7843, 0.0, 1.0)
		elif self.price < 1000000000:
			return grp.GenerateColor( (255.0/255.0), (153.0/255.0), (51.0/255.0), 1.0)
		elif self.price < 10000000000:
			return grp.GenerateColor( (153.0/255.0), (76.0/255.0), (0.0/255.0), 1.0)
		else:
			return grp.GenerateColor( (255.0/255.0), (51.0/255.0), (51.0/255.0), 1.0)
	
	def ReloadButtonInfo(self):
		def __IsAttr(attrSlot):
			if not attrSlot:
				return False

			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				type = attrSlot[i][0]
				if 0 != type:
					return True

			return False
		
		item.SelectItem(self.itemVnum)
		self.icon_image.LoadImage(item.GetIconImageFileName())
		
		self.item_quantity.SetText("{}x".format(self.count))
		self.shop_time_txt.SetText("{}".format(localeInfo.PrivateShopSecondToDHMS(self.shopTime - app.GetTime())))
		self.item_price_txt.SetText("{}".format(localeInfo.NumberToDecimalString(self.price)))
		self.item_price_txt.SetPackedFontColor(self.__GetYangTextColor())

		attrSlot = []
		for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
			attrSlot.append(newPrivateShopSearch.GetSearchItemAttribute(self.GetRealSlot(), i))
		
		self.item_name_txt.SetText("{}".format(self.itemName))
		if __IsAttr(attrSlot):
			self.item_name_txt.SetPackedFontColor(grp.GenerateColor(1.0, 0.7843, 0.0, 1.0))
		else:
			self.item_name_txt.SetPackedFontColor(grp.GenerateColor(0.9490, 0.9058, 0.7568, 1.0))

		# if app.ENABLE_CHANGE_LOOK_SYSTEM:
		# changelookvnum = newPrivateShopSearch.GetSearchItemTransmutation(self.GetRealSlot())
		# if changelookvnum != 0:
			# self.icon_image_change_look.Show()
		# else:
			# self.icon_image_change_look.Hide()
	
	def OnClose(self):
		if self.message_button_tooltip:
			self.message_button_tooltip.HideToolTip()
		
		self.OnOut()
		self.Hide()

	def __LoadMessageButtonTooltip(self):
		if not self.message_button_tooltip:
			return
		
		self.message_button_tooltip.ClearToolTip()
		self.message_button_tooltip.AutoAppendTextLine(localeInfo.NEW_PRIVATESHOP_SEARCH_PLAYER_SELL)
		self.message_button_tooltip.AutoAppendTextLine("|cffE58A17{}".format(str(self.sellerName)))
		self.message_button_tooltip.AlignHorizonalCenter()
	
	def OnUpdate(self):
		if self.message_button_tooltip and self.message_button:
			if self.message_button.IsIn():
				self.message_button_tooltip.ShowToolTip()
			else:
				self.message_button_tooltip.HideToolTip()
		
		new_time = self.shopTime - app.GetTime()
		item_state = newPrivateShopSearch.GetItemState(self.GetRealSlot())
		
		self.price = newPrivateShopSearch.GetSearchItemPrice(self.GetRealSlot())
		self.item_price_txt.SetText("{}".format(localeInfo.NumberToDecimalString(self.price)))
		
		if item_state != 0:
			if item_state == 1:
				self.shop_time_txt.SetText(localeInfo.NEWPRIVATE_SHOP_ITEM_BUYED_TEXT)
			else:
				self.shop_time_txt.SetText(localeInfo.NEWPRIVATE_SHOP_ITEM_REMOVED_TEXT)
		else:
			if new_time <= 0:
				self.shop_time_txt.SetText(localeInfo.NEW_PRIVATESHOP_SEARCH_CLOSED_SHOP)
			else:
				self.shop_time_txt.SetText("{}".format(localeInfo.PrivateShopSecondToDHMS(new_time)))
	
	def SendMensage(self):
		if self.ismyownItem:
			return
		
		if self.interface:
			self.interface.OpenWhisperDialog(self.sellerName)
	
	def OnHover(self):
		if self.toolTipItem:
			self.toolTipItem.SetNewPrivateSearchItem(self.GetRealSlot())
	
	def OnOut(self):
		if self.toolTipItem:
			self.toolTipItem.Hide()
	
	def SetBasePosition(self, x, y):
		self.base_pos = (x, y)
	
	def GetButtonBasePosition(self):
		return self.base_pos
	
	def GetButtonHeight(self):
		return self.base_size[1]

	def SetHeightPercentageBottom(self, percentage):
		self.simulate_page_y = 0
		
		if percentage > 0:
			self.horizontalLine_bottom.Hide()
			
			(base_width, base_height) = self.base_size
			real_height = (base_height * (100-percentage))/100
			self.simulate_page_size = (base_width, real_height)
			
			slot_image_end = base_height/2 + self.slot_base_image.GetHeight()/2
			if slot_image_end > real_height:
				hided_slot = slot_image_end - real_height
				hided_slot_pct = minmax(0, hided_slot * 100 / self.slot_base_image.GetHeight(), 100)
				self.slot_base_image.SetRenderingRect(0.0, 0.0, 0.0, -(float(hided_slot_pct) / 100.0))
				self.icon_image.SetRenderingRect(0.0, 0.0, 0.0, -(float(hided_slot_pct) / 100.0))
			else:
				self.slot_base_image.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
				self.icon_image.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			
			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# change_look_end = base_height/2 - self.slot_base_image.GetHeight()/2 + self.icon_image_change_look.GetHeight()
			# if change_look_end > real_height:
				# hided_change_look = change_look_end - real_height
				# hided_change_look_pct = minmax(0, hided_change_look * 100 / self.icon_image_change_look.GetHeight(), 100)
				# self.icon_image_change_look.SetRenderingRect(0.0, 0.0, 0.0, -(float(hided_change_look_pct) / 100.0))
			# else:
				# self.icon_image_change_look.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			
			money_image_end = base_height/2 - self.money_image.GetHeight()/2
			if money_image_end > real_height:
				self.money_image.Hide()
			else:
				self.money_image.Show()
			
			message_button_end = base_height/2 - self.message_button.GetHeight()/2
			if message_button_end > real_height:
				self.message_button.Hide()
			else:
				self.message_button.Show()
			
			if base_height/2 > real_height:
				self.item_quantity.Hide()
				self.item_name_txt.Hide()
				self.shop_time_txt.Hide()
				self.item_price_txt.Hide()
			else:
				self.item_quantity.Show()
				self.item_name_txt.Show()
				self.shop_time_txt.Show()
				self.item_price_txt.Show()
		else:
			self.horizontalLine_bottom.Show()
			(base_width, base_height) = self.base_size
			self.simulate_page_size = (base_width, base_height)
			self.slot_base_image.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			self.icon_image.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# self.icon_image_change_look.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			self.money_image.Show()
			self.message_button.Show()
			self.item_quantity.Show()
			self.item_name_txt.Show()
			self.shop_time_txt.Show()
			self.item_price_txt.Show()
		
	def SetHeightPercentageTop(self, percentage):
		if percentage == 100:
			self.horizontalLine_bottom.Hide()
		else:
			self.horizontalLine_bottom.Show()
		
		if percentage >= 0:
			(base_width, base_height) = self.base_size
			real_height = (base_height * (100-percentage))/100
			self.simulate_page_size = (base_width, real_height)
			self.simulate_page_y = minmax(0, base_height - real_height, base_height - real_height)
			page_position = (self.GetLocalPosition()[1] - 2)
			slot_image_start = page_position + base_height/2 - self.slot_base_image.GetHeight()/2
			if slot_image_start < 0:
				hided_slot_pct = minmax(0, abs(slot_image_start) * 100 / self.slot_base_image.GetHeight(), 100)
				self.slot_base_image.SetRenderingRect(0.0, -(float(hided_slot_pct) / 100.0), 0.0, 0.0)
				self.icon_image.SetRenderingRect(0.0, -(float(hided_slot_pct) / 100.0), 0.0, 0.0)
			else:
				self.slot_base_image.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
				self.icon_image.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			
			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# change_look_start = page_position + base_height/2 - self.slot_base_image.GetHeight()/2
			# if change_look_start < 0:
				# hided_change_look_pct = minmax(0, abs(change_look_start) * 100 / self.icon_image_change_look.GetHeight(), 100)
				# self.icon_image_change_look.SetRenderingRect(0.0, -(float(hided_change_look_pct) / 100.0), 0.0, 0.0)
			# else:
				# self.icon_image_change_look.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			
			money_image_start = page_position + base_height/2 + self.money_image.GetHeight()/2
			if money_image_start < 0:
				self.money_image.Hide()
			else:
				self.money_image.Show()
			
			message_button_start = page_position + base_height/2 +  self.message_button.GetHeight()/2
			if message_button_start < 0:
				self.message_button.Hide()
			else:
				self.message_button.Show()
			
			if base_height/2 > real_height + 4:
				self.item_quantity.Hide()
				self.item_name_txt.Hide()
				self.shop_time_txt.Hide()
				self.item_price_txt.Hide()
			else:
				self.item_quantity.Show()
				self.item_name_txt.Show()
				self.shop_time_txt.Show()
				self.item_price_txt.Show()
		else:
			self.simulate_page_y = 0
			(base_width, base_height) = self.base_size
			self.simulate_page_size = (base_width, base_height)
			self.slot_base_image.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			self.icon_image.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
			# self.icon_image_change_look.SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			self.money_image.Show()
			self.message_button.Show()
			self.item_quantity.Show()
			self.item_name_txt.Show()
			self.shop_time_txt.Show()
			self.item_price_txt.Show()

class AutoCompleteSearchEditLine(ui.ScriptWindow):
	def __init__(self, parent):
		ui.ScriptWindow.__init__(self)
		self.SetParent(parent)
		self.SetSize(185, 0)
		
		self.__Initialize()
	
	def __Initialize(self):
		self.horizontalLine_top = None
		self.horizontalLine_left = None
		self.horizontalLine_right = None
		self.horizontalLine_bottom = None
		
		self.click_event = None
		self.buttons_list = []
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def __LoadMainBox(self):
		self.horizontalLine_top = ui.Line()
		self.horizontalLine_top.SetParent(self)
		self.horizontalLine_top.SetPosition(0, 0)
		self.horizontalLine_top.SetColor(0xFF403c38)
		self.horizontalLine_top.SetSize(185, 0)
		self.horizontalLine_top.Show()
		
		self.horizontalLine_left = ui.Line()
		self.horizontalLine_left.SetParent(self)
		self.horizontalLine_left.SetPosition(0, 0)
		self.horizontalLine_left.SetColor(0xFF403c38)
		self.horizontalLine_left.SetSize(0, 0)
		self.horizontalLine_left.Show()
		
		self.horizontalLine_right = ui.Line()
		self.horizontalLine_right.SetParent(self)
		self.horizontalLine_right.SetPosition(0, 0)
		self.horizontalLine_right.SetWindowHorizontalAlignRight()
		self.horizontalLine_right.SetColor(0xFF403c38)
		self.horizontalLine_right.SetSize(0, 0)
		self.horizontalLine_right.Show()
		
		self.horizontalLine_bottom = ui.Line()
		self.horizontalLine_bottom.SetParent(self)
		self.horizontalLine_bottom.SetPosition(0, 0)
		self.horizontalLine_bottom.SetColor(0xFF403c38)
		self.horizontalLine_bottom.SetSize(185, 0)
		self.horizontalLine_bottom.Show()
	
	def ClearList(self):
		for button in self.buttons_list:
			button.Hide()
		
		self.SetSize(185, 0)
		
		self.horizontalLine_top = None
		self.horizontalLine_left = None
		self.horizontalLine_right = None
		self.horizontalLine_bottom = None
		self.buttons_list = []
	
	def AddItem(self, buttonName):
		index = len(self.buttons_list)
		tmpButton = ui.MakeButton(self, 0, 23*index, "", MAIN_PATH + "search_editline/", "dropdown_list.tga", "dropdown_list_hover.tga", "dropdown_list_down.tga")
		tmpButton.SetText(str(buttonName))
		tmpButton.SetEvent(ui.__mem_func__(self.ClickOnElement), buttonName)
		self.buttons_list.append(tmpButton)
	
	def CloseList(self):
		self.ClearList()
		self.Hide()
	
	def SetClickEvent(self, event):
		self.click_event = event
	
	def ClickOnElement(self, name):
		if self.click_event:
			self.click_event(name)
	
	def OpenList(self):
		self.__LoadMainBox()
		
		if len(self.buttons_list) != 0:
			height = self.buttons_list[-1].GetLocalPosition()[1] + self.buttons_list[-1].GetHeight()
			self.SetSize(185, height)
			self.horizontalLine_left.SetSize(0, height)
			self.horizontalLine_right.SetSize(0, height)
			self.horizontalLine_bottom.SetPosition(0, height)
		
		self.Show()

class PrivateShopSearchWindow(ui.ScriptWindow):
	isFilterWindowOpened = 0
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__Initialize()
		self.__InitializeFilterValues()
		self.__LoadWindow()
	
	def __Initialize(self):
		self.interface = None
		self.tooltipItem = None
		self.editline_list = None
		
		self.buttons_and_arrows = None
		self.filter_button = None
		self.help_window = None
		self.search_bg = None
		self.search_button = None
		self.clean_editline_button = None
		self.search_item_editline = None
		self.buttons_filter_bg = None

		self.first_prev_button = None
		self.prev_button = None
		self.next_button = None
		self.last_next_button = None
		
		self.loading_window = None
		self.error_mensage = None
		
		self.left_side_scrollbar = None
		self.right_side_scrollbar = None
		
		self.last_scroll_pos = 0.0
		self.last_left_middlebar_size = 0.0
		
		self.filter_size = 0
		self.buttons_filter_y_rect = 0
		
		self.v_filterButtons = []
		self.v_filterButtonsList = []
		
		self.result_per_page = []
		self.result_page_numb = []
		self.result_per_page_actual = 0
		
		self.search_type_cat = 0
		self.search_sub_type_cat = 0
		
		self.actual_list_page = 0
		self.true_actual_list_page = 0
		self.result_buttons = {}
		
		self.questionFilterReset = None
		self.questionBuyItem = None
		self.filter_window = None
		
		self.block_page = None
		self.overfall2_premium = None

	def __GetPlayerGender(self):
		return chr.RaceToSex(player.GetRace())
	
	def __InitializeFilterValues(self):
		self.min_level_value = -1
		self.max_level_value = -1
		self.min_dh_value = -1
		self.max_dh_value = -1
		self.min_dm_value = -1
		self.max_dm_value = -1
		
		self.item_level_value = -1
		self.acce_abs_value = -1
		self.ds_clarity_value = -1
		self.bonus_choose = -1
		
		self.gender = -1
	
	def __del__(self):
		ui.ScriptWindow.__del__(self)
	
	def Destroy(self):
		self.__Initialize()
	
	def SetItemToolTip(self, tooltip):
		self.tooltipItem = proxy(tooltip)
	
	def SetInterface(self, interface):
		self.interface = proxy(interface)
	
	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/newprivateshopsearch.py")
		except:	exception.Abort("PrivateShopSeachWindow.__LoadWindow.UIScript/newprivateshopsearch.py")
		
		try:
			self.GetChild("board").SetCloseEvent(ui.__mem_func__(self.Close))
			
			self.search_bg = self.GetChild("search_bg")
			
			self.help_window = self.GetChild("help_window")
			self.help_window.Show()
			
			self.buttons_filter_bg = self.GetChild("buttons_filter_bg")
			
			self.buttons_and_arrows = self.GetChild("buttons_and_arrows")
			self.buttons_and_arrows.Hide()
			
			self.search_button = self.GetChild("search_button")
			self.search_button.SetEvent(ui.__mem_func__(self.SearchItensFunc))

			self.clean_editline_button = self.GetChild("clean_editline_button")
			self.clean_editline_button.SetEvent(ui.__mem_func__(self.CleanSearchEditLineText))
			self.clean_editline_button.Hide()
			
			self.left_side_scrollbar = self.GetChild("left_side_scrollbar")
			self.left_side_scrollbar.SetScrollEvent(ui.__mem_func__(self.__OnScroll))
			
			self.right_side_scrollbar = self.GetChild("right_side_scrollbar")
			self.right_side_scrollbar.SetScrollEvent(ui.__mem_func__(self.__OnScrollList))
			self.right_side_scrollbar.Hide()
			
			self.search_item_editline = self.GetChild("search_item_editline")
			self.search_item_editline.SetPlaceHolder(localeInfo.PRIVATESHOP_SEARCH_ITEM)
			self.search_item_editline.SetPlaceHolderColor(0xff2f2f2f)
			self.search_item_editline.SetUpdateEvent(ui.__mem_func__(self.OnUpdateSearchItemEditLine))
			self.search_item_editline.OnIMEReturn = ui.__mem_func__(self.SearchItensFunc)
			self.search_item_editline.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))
			
			self.loading_window = self.GetChild("loading_window")
			self.loading_window.Hide()
			
			self.error_mensage = self.GetChild("error_mensage")
			self.error_mensage.Hide()
			
			v_result_per_page = [50, 100, 200]
			for i in xrange(3):
				self.result_per_page.append(self.GetChild("result_per_page{}".format(i+1)))
				self.result_per_page[i].SetEvent(ui.__mem_func__(self.ClickInResultPerPageButton), i, v_result_per_page[i])
			self.ClickInResultPerPageButton(0, v_result_per_page[0])
			
			for i in xrange(5):
				self.result_page_numb.append(self.GetChild("{}_result_page".format(i+1)))
				self.result_page_numb[i].SetEvent(ui.__mem_func__(self.ClickInChangePageButton), i)
			
			self.first_prev_button = self.GetChild("first_prev_button")
			self.first_prev_button.SetEvent(ui.__mem_func__(self.ClickInArrowButton), "first_prev")
			
			self.prev_button = self.GetChild("prev_button")
			self.prev_button.SetEvent(ui.__mem_func__(self.ClickInArrowButton), "prev")
			
			self.next_button = self.GetChild("next_button")
			self.next_button.SetEvent(ui.__mem_func__(self.ClickInArrowButton), "next")
			
			self.last_next_button = self.GetChild("last_next_button")
			self.last_next_button.SetEvent(ui.__mem_func__(self.ClickInArrowButton), "last_next")
		
			self.buttons_filter_y_rect = self.GetChild("bg_inv").GetLocalPosition()[1] - self.buttons_filter_bg.GetLocalPosition()[1]
			
			self.editline_list = AutoCompleteSearchEditLine(self)
			editline_list_pos_x, editline_list_pos_y = self.GetChild("search_bar_base").GetLocalPosition()
			self.editline_list.SetPosition(editline_list_pos_x, editline_list_pos_y + 30)
			self.editline_list.SetClickEvent(ui.__mem_func__(self.ClickOnSearchEditLineElement))
			self.editline_list.CloseList()
			
			self.filter_window = PrivateShopFilterWindow(self)
			self.filter_window.SetReloadVarEvent(ui.__mem_func__(self.OnReloadFilterOptions))
			self.filter_window.SetCloseEvent(ui.__mem_func__(self.OnCloseFilter))
			self.filter_window.Hide()
			
			self.filter_button = self.GetChild("filter_button")
			self.filter_button.SetEvent(ui.__mem_func__(self.ToggleFilterWindow))
			
			self.block_page = self.GetChild("block_page")
			self.block_page.Hide()
			
			self.overfall2_premium = self.GetChild("overfall2_premium")
			
			self.__LoadQuestionDialog()
			self.__LoadBuyDialog()
		except:	exception.Abort("PrivateShopSeachWindow.__LoadWindow.Cant_Load_Objects")

		self.__CreateFilterButtons()
		self.__ReloadFilterSize()
		self.__ReloadLeftScrollBar()
		self.__OnScroll()
		self.OnClickCategoryButton(0)
	
	def CanAskForFilterReset(self):
		if self.min_level_value == -1 and\
			self.max_level_value == -1 and\
			self.min_dh_value == -1 and\
			self.max_dh_value == -1 and\
			self.min_dm_value == -1 and\
			self.max_dm_value == -1 and\
			self.item_level_value == -1 and\
			self.acce_abs_value == -1 and\
			self.ds_clarity_value == -1 and\
			self.bonus_choose == -1 and\
			self.gender == -1:
			return False
		
		return True
	
	def AnswerFilterReset(self, arg):
		if not self.questionFilterReset:
			return
		
		self.SearchItensFunc(True)
		self.questionFilterReset.Close()
		
		if arg is True:
			if self.filter_window:
				self.filter_window.ForceResetFilter()
	
	def __LoadQuestionDialog(self):
		questionFilterReset = uiCommon.QuestionDialog()
		questionFilterReset.SetText(localeInfo.NEW_PRIVATESHOP_FILTER_QUESTION_DIALOG)
		questionFilterReset.SetAcceptEvent(lambda arg=True: self.AnswerFilterReset(arg))
		questionFilterReset.SetCancelEvent(lambda arg=False: self.AnswerFilterReset(arg))
		questionFilterReset.Close()
		self.questionFilterReset = questionFilterReset
	
	def __LoadBuyDialog(self):
		questionBuyItem = uiCommon.QuestionDialog2()
		questionBuyItem.SetAcceptEvent(lambda arg=True: self.AnswerBuyItem(arg))
		questionBuyItem.SetCancelEvent(lambda arg=False: self.AnswerBuyItem(arg))
		questionBuyItem.Close()
		self.questionBuyItem = questionBuyItem
	
	def SearchItensFunc(self, forcepass = False):
		if self.editline_list.IsShow():
			self.editline_list.CloseList()

		if self.filter_window.IsShow():
			self.filter_window.Close(True)
		
		if forcepass is False:
			if self.CanAskForFilterReset() is True and\
				(self.questionFilterReset and not self.questionFilterReset.IsShow()):
				self.questionFilterReset.Open()
				return
		
		self.__LoadLoadingPage()
		
		newPrivateShopSearch.ClearSearchItems()
		self.__ClearSearchList()
		
		net.SendNewPrivateShopSearchInfo(self.search_type_cat,\
										self.search_sub_type_cat,\
										self.search_item_editline.GetText(),\
										self.min_level_value,\
										self.max_level_value,\
										self.min_dh_value,\
										self.max_dh_value,\
										self.min_dm_value,\
										self.max_dm_value,\
										self.item_level_value,\
										self.acce_abs_value,\
										self.ds_clarity_value,\
										self.bonus_choose,\
										self.gender,
										(1 if len(self.search_item_editline.GetText()) != 0 else 0))
		return True
	
	def __ReloadLeftScrollBar(self):
		out_perc = minmax(0.0, float(self.filter_size - self.buttons_filter_y_rect) / float(self.filter_size), 0.99)
		new_mid_bar_size = 1.0 - out_perc
		self.left_side_scrollbar.SetMiddleBarSize(new_mid_bar_size)
		if self.last_left_middlebar_size != 0.0:
			new_pos = (new_mid_bar_size * self.left_side_scrollbar.GetPos() / self.last_left_middlebar_size)
			self.left_side_scrollbar.SetPos(new_pos)
			self.__OnScroll()
		self.last_left_middlebar_size = new_mid_bar_size
	
	def __GetLastFilterElementPosition(self):
		last_button = self.v_filterButtons[-1]
		last_list = self.v_filterButtonsList[-1]
		
		if last_button.IsOpen() == 0:
			return last_button.GetLocalPosition()[1] + last_button.GetButtonHeight()
		else:
			return last_list.GetLocalPosition()[1] + last_list.GetListHeight()
		
		return 0
	
	def __OnScroll(self):
		pos = self.left_side_scrollbar.GetPos()
		move_value = self.filter_size - self.buttons_filter_y_rect
		if move_value <= 0:	return
		
		scroll_step_value = float(move_value) * float(pos)
		(x_base, y_base) = self.v_filterButtons[0].GetButtonBasePosition()
		self.v_filterButtons[0].SetPosition(x_base, (y_base - int(scroll_step_value)))
		
		self.ReloadObjectsPosition()
	
	def __ReloadFilterSize(self):
		first_pos = self.v_filterButtons[0].GetLocalPosition()[1]
		last_pos = 0
		
		last_button = self.v_filterButtons[-1]
		last_list = self.v_filterButtonsList[-1]
		
		if last_button.IsOpen() == 0:
			last_pos += last_button.GetLocalPosition()[1] + last_button.GetButtonHeight()
		else:
			last_pos += last_list.GetLocalPosition()[1] + last_list.GetListHeight()
		
		self.filter_size = last_pos - first_pos
	
	def __CreateFilterButtons(self):
		for category_list in filterCfg.CATEGORY_BUTTONS:
			index = 0
			for categorymain_keys in category_list.keys():
				for category_keys in category_list[categorymain_keys].keys():
					tmpObj = PrivateShopFilterButton(self.buttons_filter_bg)
					tmpObj.SetCategoryIndexAndKey(index, category_keys)
					tmpObj.SetClickEvent(self.OnClickCategoryButton)
					tmpObj.SetCategoryText(str(category_keys))
					tmpObj.SetCategoryIcon(*category_list[categorymain_keys][category_keys][0])
					start_pos = (0, 35*index)
					tmpObj.SetButtonBasePosition(start_pos)
					tmpObj.SetPosition(*start_pos)
					tmpObj.ResetTextColor()
					tmpObj.Show()
					self.v_filterButtons.append(tmpObj)
					
					tmpListObj = PrivateShopFilterCategoryList(self.buttons_filter_bg)
					tmpListObj.SetListElements(category_list[categorymain_keys][category_keys][1])
					tmpListObj.SetCategoryIndex(index)
					tmpListObj.SetClickEvent(self.OnClickSubCategoryButton)
					tmpListObj.Hide()
					self.v_filterButtonsList.append(tmpListObj)
				index += 1
	
	def OnClickSubCategoryButton(self, index, category_index):
		self.v_filterButtons[0].ForceCloseCategory() #Reseta a cor do texto da primeira categoria
		
		for list_button_index in xrange(len(self.v_filterButtonsList)): #Reseta todos os botões selecionados das listas
			if list_button_index == category_index:
				continue
			
			list = self.v_filterButtonsList[list_button_index]
			list.SetUpAllList()

		self.search_type_cat = category_index
		self.search_sub_type_cat = index
	
	def OnClickCategoryButton(self, index):
		button = self.v_filterButtons[index]
		list = self.v_filterButtonsList[index]
		
		if index == 0:
			button.SetSpecialUpButton()
			
			for button_index in xrange(len(self.v_filterButtons)):
				if button_index == 0:
					continue
				
				button_manage = self.v_filterButtons[button_index] #objeto do botão
				button_manage.ForceCloseCategory()
			
			for list_button in self.v_filterButtonsList:
				list_button.SetUpAllList()
				list_button.Hide()
			
			self.search_type_cat = 0
			self.search_sub_type_cat = 0
		else:
			if button.IsOpen() == 0:
				button.ResetTextColor()
				list.Hide()
			else:
				button.SetUpButton()
				
				(x, y) = button.GetLocalPosition()
				x += 2
				y += (button.GetButtonHeight() + 2)
				
				list.SetPosition(x, y)
				list.Show()
			
		self.ReloadObjectsPosition()
		self.__ReloadFilterSize()
		self.__ReloadLeftScrollBar()

	def ReloadObjectsPosition(self):
		for button_index in xrange(len(self.v_filterButtons)):
			if button_index == 0:
				continue
			
			before_button = self.v_filterButtons[button_index-1]
			before_list = self.v_filterButtonsList[button_index-1]
			
			button = self.v_filterButtons[button_index]
			list = self.v_filterButtonsList[button_index]
			
			if before_button.IsOpen() == 0:
				(x, y) = before_button.GetLocalPosition()
				y += before_button.GetButtonHeight() + 2
				button.SetPosition(x, y)
				if button.IsOpen() == 1:
					(x, y) = button.GetLocalPosition()
					x += 2
					y += (button.GetButtonHeight() + 2)
					
					list.SetPosition(x, y)
					list.Show()
			else:
				(x, y) = before_list.GetLocalPosition()
				x -= 2
				y += before_list.GetListHeight() + 4
				
				button.SetPosition(x, y)
				if button.IsOpen() == 1:
					(x, y) = button.GetLocalPosition()
					x += 2
					y += (button.GetButtonHeight() + 2)
					
					list.SetPosition(x, y)
					list.Show()
	
	def __GetPlayerPremium(self):
		return chr.IsOverfallPremium()
	
	def OnUpdate(self):
		if not self.questionBuyItem:
			self.block_page.Hide()
			return
		
		if self.questionBuyItem.IsShow():
			self.block_page.Show()
		else:
			self.block_page.Hide()
		
		if self.overfall2_premium:
			self.overfall2_premium.LoadImage(PREMIUM_IMAGES[self.__GetPlayerPremium()])
	
	def OnRender(self):
		#left side
		for index in xrange(len(self.v_filterButtons)):
			button = self.v_filterButtons[index]
			if button.GetLocalPosition()[1] + button.GetButtonHeight() > self.buttons_filter_y_rect:
				percentage = minmax(0, ((button.GetLocalPosition()[1] + button.GetButtonHeight() - self.buttons_filter_y_rect) * 100) / button.GetButtonHeight(), 100)
				button.SetHeightPercentageBottom(percentage)
			elif button.GetLocalPosition()[1] < 0:
				percentage = minmax(0, -button.GetLocalPosition()[1] * 100 / button.GetButtonHeight(), 100)
				button.SetHeightPercentageTop(percentage)
			else:
				button.SetHeightPercentageBottom(0)
				button.SetHeightPercentageTop(0)
		
		for index in xrange(len(self.v_filterButtonsList)):
			list = self.v_filterButtonsList[index]
			if list.GetLocalPosition()[1] + list.GetListHeight() > self.buttons_filter_y_rect:
				percentage = minmax(0, ((list.GetLocalPosition()[1] + list.GetListHeight() - self.buttons_filter_y_rect) * 100) / list.GetListHeight(), 100)
				list.SetHeightPercentageBottom(percentage)
			elif list.GetLocalPosition()[1] < 0:
				percentage = minmax(0, (-list.GetLocalPosition()[1] * 100) / list.GetListHeight(), 100)
				list.SetHeightPercentageTop(percentage)
			else:
				list.SetHeightPercentageBottom(0)
				list.SetHeightPercentageTop(0)
		
		#right side
		if self.result_buttons.has_key(self.actual_list_page):
			for right_index in xrange(len(self.result_buttons[self.actual_list_page])):
				button_r = self.result_buttons[self.actual_list_page][right_index]
				if button_r.GetLocalPosition()[1] + button_r.GetButtonHeight() > self.search_bg.GetHeight()-5:
					percentage = minmax(0, ((button_r.GetLocalPosition()[1] + button_r.GetButtonHeight() - self.search_bg.GetHeight()-5) * 100) / button_r.GetButtonHeight(), 100)
					button_r.SetHeightPercentageBottom(percentage)
				elif button_r.GetLocalPosition()[1] < 0:
					percentage = minmax(0, -button_r.GetLocalPosition()[1] * 100 / button_r.GetButtonHeight(), 100)
					button_r.SetHeightPercentageTop(percentage)
				else:
					button_r.SetHeightPercentageBottom(0)
					button_r.SetHeightPercentageTop(0)
	
	def __ReloadRightScrollBarSize(self):
		first_button = self.result_buttons[self.actual_list_page][0]
		last_button = self.result_buttons[self.actual_list_page][-1]
		filter_size = (last_button.GetLocalPosition()[1] + last_button.GetHeight()) - first_button.GetLocalPosition()[1]
		parent_size = self.search_bg.GetHeight()
		
		out_perc = minmax(0.0, float(filter_size - parent_size) / float(filter_size), 0.99)
		new_mid_bar_size = 1.0 - out_perc
		if parent_size >= filter_size:
			new_mid_bar_size = 0.99
		
		self.right_side_scrollbar.SetScrollStep((1.0/(float(filter_size-parent_size)/30.0)))
		self.right_side_scrollbar.SetMiddleBarSize(new_mid_bar_size)
		self.right_side_scrollbar.Show()
	
	def __OnScrollList(self):
		if len(self.result_buttons[self.actual_list_page]) == 0:
			return
		
		first_button = self.result_buttons[self.actual_list_page][0]
		last_button = self.result_buttons[self.actual_list_page][-1]
		
		pos = self.right_side_scrollbar.GetPos()
		parent_size = self.search_bg.GetHeight()
		filter_size = (last_button.GetLocalPosition()[1] + last_button.GetHeight()) - first_button.GetLocalPosition()[1]
		move_value = filter_size - parent_size
		if move_value <= 0:	return
		
		scroll_step_value = float(move_value) * float(pos)
		for button in self.result_buttons[self.actual_list_page]:
			(x_base, y_base) = button.GetButtonBasePosition()
			button.SetPosition(x_base, (y_base - int(scroll_step_value)))
	
	def GetPrivateShopSearchResult(self, position):
		itemVnum = newPrivateShopSearch.GetSearchItemVnum(position)
		itemName = ""
		sellerName = ""
		count = 0
		price = 0
		itemSize = 1
		shop_time = 0
		player_map_index = 0
		off_shop_map_index = 0
		item_id = 0
		
		if itemVnum != 0:
			item.SelectItem(itemVnum)
			itemName = item.GetItemName()

			sellerVID = newPrivateShopSearch.GetSearchItemShopVID(position)
			sellerName = newPrivateShopSearch.GetSearchItemSellerName(position)

			count = newPrivateShopSearch.GetSearchItemCount(position)
			price = newPrivateShopSearch.GetSearchItemPrice(position)
			shop_time = newPrivateShopSearch.GetSearchItemShopTime(position)
			itemSize = item.GetItemSize()[1]
			
			player_map_index = newPrivateShopSearch.GetPlayerSearchMapIndex(position)
			off_shop_map_index = newPrivateShopSearch.GetOfflineShopMapIndex(position)
			item_id = newPrivateShopSearch.GetSearchItemId(position)

		return itemVnum, itemName, sellerName, count, price, itemSize, shop_time, player_map_index, off_shop_map_index, item_id
	
	def __ClearSearchList(self):
		if len(self.result_buttons) == 0:
			return
		
		for key in self.result_buttons.keys():
			for button in self.result_buttons[key]:
				button.OnClose()
		
		self.result_buttons.clear()
	
	def __ReloadPageElements(self):
		for key in self.result_buttons.keys():
			for button in self.result_buttons[key]:
				if key == self.actual_list_page:
					button.Show()
				else:
					button.OnClose()
		
		if len(self.result_buttons) != 0:
			self.buttons_and_arrows.Show()
		else:
			self.buttons_and_arrows.Hide()
	
	def __LoadLoadingPage(self):
		self.help_window.Hide()
		self.error_mensage.Hide()
		self.right_side_scrollbar.Hide()
		self.buttons_and_arrows.Hide()
		self.loading_window.Show()
	
	def __StopLoading(self):
		self.error_mensage.Hide()
		self.loading_window.Hide()
		self.help_window.Hide()
	
	def __LoadErrorMsg(self, text):
		self.help_window.Hide()
		self.right_side_scrollbar.Hide()
		self.loading_window.Hide()
		self.buttons_and_arrows.Hide()
		
		self.error_mensage.SetText(text)
		self.error_mensage.Show()
	
	def ShopSearch_Error(self, error):
		m_texts = {
			newPrivateShopSearch.NPSS_HAVE_PAGE_OPENED : localeInfo.NEWPRIVATE_SHOP_SEARCH_ERROR2,
			newPrivateShopSearch.NPSS_PLEASE_WAIT : localeInfo.NEWPRIVATE_SHOP_SEARCH_ERROR3,
			newPrivateShopSearch.NPSS_NEED_TO_BE_IN_EMPIRE : localeInfo.NEWPRIVATE_SHOP_SEARCH_ERROR4,
			newPrivateShopSearch.NPSS_NEED_OTHER_ERROR : localeInfo.NEWPRIVATE_SHOP_SEARCH_ERROR5,
		}
		
		self.__ClearSearchList()
		self.__LoadErrorMsg(m_texts[error])
	
	def RefreshList(self):
		self.__ClearSearchList()
		self.__StopLoading()
		
		maxCount = newPrivateShopSearch.GetItemCount()
		if maxCount == 0:
			self.__LoadErrorMsg(uiScriptLocale.NEWPRIVATE_SHOP_SEARCH_ERROR1)
		else:
			page = 0
			line = 0
			for _ in xrange(maxCount):
				if line >= self.result_per_page_actual:
					line = 0
					page += 1
				
				true_line_search = (self.result_per_page_actual * page) + line
				itemVnum, itemName, sellerName, count, price,\
					itemSize, shop_time, player_map_index,\
					off_shop_map_index, item_id = self.GetPrivateShopSearchResult(true_line_search)
				tmpButton = PrivateShopResultButton(self.search_bg)
				tmpButton.SetMainPage(self)
				tmpButton.SetInterface(self.interface)
				tmpButton.SetItemToolTip(self.tooltipItem)
				tmpButton.CreateButton(itemSize)
				
				(x, y) = (2,0)
				if line == 0:
					tmpButton.SetPosition(x,y)
				else:
					height = self.result_buttons[page][line-1].GetLocalPosition()[1] + self.result_buttons[page][line-1].GetHeight()
					(x, y) = (2, height)
					tmpButton.SetPosition(2, height)
				
				tmpButton.SetBasePosition(x, y)
				tmpButton.SetItemInfo(itemVnum, itemName, sellerName, count, price, shop_time, player_map_index, off_shop_map_index, item_id, line, page)
				tmpButton.SetPageCut(self.result_per_page_actual)
				tmpButton.ReloadButtonInfo()
				tmpButton.OnClose()
				
				if not self.result_buttons.has_key(page):
					self.result_buttons[page] = []
				self.result_buttons[page].append(tmpButton)
				
				line += 1
			
			self.total_pages = page + 1
			self.actual_list_page = 0
			self.true_actual_list_page = 0
			index = 1
			for button in self.result_page_numb:
				button.SetText("{}".format(int(index)))
				index += 1
			self.ClickInChangePageButton(self.actual_list_page)
			self.__RefreshMaxPages()
			self.__ReloadRightScrollBarSize()
	
	def __RefreshMaxPages(self):
		for i in xrange(len(self.result_page_numb)):
			button = self.result_page_numb[i]
			if int(self.result_page_numb[i].GetText()) > self.total_pages:
				button.Hide()
			else:
				button.Show()
	
	def ClickInResultPerPageButton(self, index, result_per_page):
		for radio_button in self.result_per_page:
			radio_button.SetUp()
		self.result_per_page[index].Down()
		self.result_per_page_actual = result_per_page
		if len(self.result_buttons) != 0:
			self.RefreshList()
	
	def ClickInChangePageButton(self, index):
		for button in self.result_page_numb:
			button.SetUp()
		self.result_page_numb[index].Down()
		
		true_page_index = int(self.result_page_numb[index].GetText())
		self.actual_list_page = true_page_index - 1
		self.true_actual_list_page = index
		self.__ReloadPageElements()
		self.__RefreshMaxPages()
		self.__ReloadRightScrollBarSize()
		self.right_side_scrollbar.SetPos(0)
		self.__OnScrollList()
	
	def ClickInArrowButton(self, arg):
		if not arg in ["first_prev", "prev", "next", "last_next"]:
			return
		
		calc_list_page = self.actual_list_page +1
		if arg == "next":
			if calc_list_page >= self.total_pages:
				return
			
			if calc_list_page % 5 == 0:
				index = 1
				for button in self.result_page_numb:
					button.SetText("{}".format(int(calc_list_page + index)))
					index += 1
				self.ClickInChangePageButton(0)
			else:
				self.ClickInChangePageButton(self.true_actual_list_page + 1)
		elif arg == "prev":
			first_page_numb = int(self.result_page_numb[0].GetText())
			if first_page_numb == 1 and self.true_actual_list_page == 0:
				return
			
			if self.true_actual_list_page == 0 and\
				first_page_numb != 1:
				start_numb = calc_list_page - 5
				index = 0
				for button in self.result_page_numb:
					button.SetText("{}".format(int(start_numb + index)))
					index += 1
				self.ClickInChangePageButton(4)
			else:
				self.ClickInChangePageButton(self.true_actual_list_page - 1)
		elif arg == "first_prev":
			if self.true_actual_list_page == 0 and calc_list_page == 1:
				return
			
			index = 1
			for button in self.result_page_numb:
				button.SetText("{}".format(int(index)))
				index += 1
			self.ClickInChangePageButton(0)
		elif arg == "last_next":
			if calc_list_page >= self.total_pages:
				return
			
			if self.total_pages <= 5:
				index = 1
				for button in self.result_page_numb:
					button.SetText("{}".format(int(index)))
					index += 1
				self.ClickInChangePageButton(self.total_pages - 1)
			else:
				last_button_index = 0
				
				total_pages = self.total_pages
				numb = 5
				
				last_button_index = total_pages - numb
				while (last_button_index > 0):
					numb += 5
					last_button_index = total_pages - numb
				last_button_index += 5
				
				
				numb_add = 5 - last_button_index
				last_page = total_pages + numb_add
				
				index = 0
				for button in reversed(self.result_page_numb):
					button.SetText("{}".format(last_page - index))
					index += 1
				
				self.ClickInChangePageButton(last_button_index - 1)
	
	def CleanSearchEditLineText(self):
		self.search_item_editline.SetText("")
		self.OnUpdateSearchItemEditLine()
	
	def OnUpdateSearchItemEditLine(self):
		editline_text = self.search_item_editline.GetText()
		self.editline_list.ClearList()
		
		if len(editline_text) == 0:
			self.clean_editline_button.Hide()
			self.editline_list.CloseList()
			return
		
		new_list = [x for x in autoComplete.AUTOCOMPLETE_DIC_NAMES if editline_text in x]
		index = 1
		for item in new_list:
			if index > 10:
				break
			index += 1
			self.editline_list.AddItem(item)
		
		self.clean_editline_button.Show()
		
		if not len(new_list):
			self.editline_list.CloseList()
		else:
			self.editline_list.OpenList()
	
	def ClickOnSearchEditLineElement(self, name):
		self.search_item_editline.SetText(str(name))
		self.search_item_editline.UpdateHolderPosition()
		self.editline_list.CloseList()
	
	def OnRunMouseWheel(self, nLen):
		(xMouseLocalPosition, yMouseLocalPosition) = self.GetMouseLocalPosition()
		if xMouseLocalPosition >= self.search_bg.GetLocalPosition()[0]:
			if nLen > 0:
				self.right_side_scrollbar.OnUp()
			else:
				self.right_side_scrollbar.OnDown()
			self.__OnScrollList()
		else:
			if nLen > 0:
				self.left_side_scrollbar.OnUp()
			else:
				self.left_side_scrollbar.OnDown()
			self.__OnScroll()
	
	def ToggleFilterWindow(self):
		if not self.filter_window:
			return
		
		if self.filter_window.IsShow():
			self.filter_window.Close(True)
		else:
			self.isFilterWindowOpened = 1
			self.filter_window.Open()
	
	def OnTop(self):
		if self.filter_window and self.filter_window.IsShow():
			self.filter_window.SetTop()
		
		if self.questionBuyItem and self.questionBuyItem.IsShow():
			self.questionBuyItem.SetTop()
	
	def Open(self):
		if self.IsShow():
			self.Close()
			return
		
		if self.search_item_editline.IsFocus():
			self.search_item_editline.KillFocus()
		self.search_item_editline.UpdatePlaceHolder()
		
		self.SetCenterPosition()
		self.Show()
		self.SetTop()

		if self.filter_window and self.isFilterWindowOpened == 1:
			self.filter_window.Open()
	
	def Close(self):
		if self.filter_window:
			self.filter_window.Close(False)
		if self.questionFilterReset:
			self.questionFilterReset.Close()
		if self.questionBuyItem:
			self.questionBuyItem.Close()
		self.Hide()
	
	def OnReloadFilterOptions(self, args):
		self.min_level_value = args[0]
		self.max_level_value = args[1]
		self.min_dh_value = args[2]
		self.max_dh_value = args[3]
		self.min_dm_value = args[4]
		self.max_dm_value = args[5]
		self.item_level_value = args[6]
		self.acce_abs_value = args[7]
		self.ds_clarity_value = args[8]
		self.bonus_choose = args[9]
		self.gender = args[10]
	
	def AnswerBuyItem(self, arg):
		if not self.questionBuyItem:
			return
		
		if arg is True:
			self.BuyItemFromSystem(shopPos = self.questionBuyItem.shopPos, itemPrice = self.questionBuyItem.itemPrice, item_id = self.questionBuyItem.item_id, forcePass = True)
		
		self.questionBuyItem.Close()
	
	def BuyItemFromSystem(self, shopPos, itemName = "", itemPrice = 0, item_id = 0, forcePass = False):
		if forcePass is False:
			if not self.questionBuyItem:
				return
			
			if self.questionBuyItem.IsShow():
				return
			
			self.questionBuyItem.SetText1(localeInfo.NEW_PRIVATESHOP_BUY_ITEM_QUESTION_DIALOG1 % itemName)
			self.questionBuyItem.SetText2(localeInfo.NEW_PRIVATESHOP_BUY_ITEM_QUESTION_DIALOG2 % (localeInfo.NumberToDecimalString(itemPrice) + " Yang"))
			self.questionBuyItem.shopPos = shopPos
			self.questionBuyItem.item_id = item_id
			self.questionBuyItem.itemPrice = itemPrice
			self.questionBuyItem.Open()
			return

		item_state = newPrivateShopSearch.GetItemState(shopPos)
		if item_state != 0:
			return
		
		if item_id == 0:
			return
		
		chrVID = newPrivateShopSearch.GetSearchItemShopVID(shopPos)
		shopItemPos = newPrivateShopSearch.GetSearchItemPos(shopPos)
		net.SendPrivateShopSerchBuyItem(chrVID, shopItemPos, shopPos, item_id, itemPrice)
	
	def NewShopSearchBuy(self, shopId):
		newPrivateShopSearch.SetItemState(shopId, 1)
	
	def NewShopSearchRemoved(self, shopId):
		newPrivateShopSearch.SetItemState(shopId, 2)
	
	def NewShopSearchPriceChanged(self, shopId, newPrice):
		newPrivateShopSearch.ReloadItemPrice(shopId, newPrice)
	
	def SearchNewPrivateShopSearchItem(self, itemName):
		if not self.IsShow():
			self.Open()
		
		self.OnClickCategoryButton(0)
		self.search_item_editline.SetText(str(itemName))
		self.SearchItensFunc()
	
	def OnCloseFilter(self):
		self.isFilterWindowOpened = 0
	
	def OnPressEscapeKey(self):
		self.Close()
		return True
