#class ImageBox(Window): sonuna ekle

	if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
		def LeftRightReverse(self):
			wndMgr.LeftRightReverseImageBox(self.hWnd)

#class Button(Window): sonuna ekle

	if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
		def SetAlpha(self, alpha):
			wndMgr.SetButtonDiffuseColor(self.hWnd, 1.0, 1.0, 1.0, alpha)

		def GetText(self):
			if self.ButtonText:
				return self.ButtonText.GetText()
			else:
				return ""

		def IsDisable(self):
			return wndMgr.IsDisable(self.hWnd)

#class ListBox(Window): içinde def _LocateItem(self): bul

#içinde arat 

				if localeInfo.IsARABIC():
					w, h = textLine.GetTextSize()
					textLine.SetPosition(w + 10, yPos + 3)
				else:
					textLine.SetPosition(0, yPos + 3)

#değiştir

			if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
				textLine.SetPosition(0, yPos + 3)
			else:
				if localeInfo.IsARABIC():
					w, h = textLine.GetTextSize()
					textLine.SetPosition(w + 10, yPos + 3)
				else:
					textLine.SetPosition(0, yPos + 3)

#aynı classta tekrar arat

def SelectItem(self, line):

#içinde arat

			if line == self.selectedLine:
				return

#değiştir

		if not app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
			if line == self.selectedLine:
				return

#class ComboBox(Window): bul ve üstüne ekle

if app.ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM:
	class ComboBoxImage(Window):
		class ListBoxWithBoard(ListBox):
			def __init__(self, layer):
				ListBox.__init__(self, layer)

			def OnRender(self):
				xRender, yRender = self.GetGlobalPosition()
				yRender -= self.TEMPORARY_PLACE
				widthRender = self.width
				heightRender = self.height + self.TEMPORARY_PLACE*2
				grp.SetColor(BACKGROUND_COLOR)
				grp.RenderBar(xRender, yRender, widthRender, heightRender)
				grp.SetColor(DARK_COLOR)
				grp.RenderLine(xRender, yRender, widthRender, 0)
				grp.RenderLine(xRender, yRender, 0, heightRender)
				ListBox.OnRender(self)

		def __init__(self, parent, name, x ,y):
			Window.__init__(self)
			self.isSelected = False
			self.isOver = False
			self.isListOpened = False
			self.event = lambda *arg: None
			self.enable = True
			self.imagebox = None

			## imagebox
			image = ImageBox()
			image.SetParent(parent)
			image.LoadImage(name)
			image.SetPosition(x, y)
			image.Show()
			self.imagebox = image

			## BaseSetting
			self.x = x + 1
			self.y = y + 1
			self.width = self.imagebox.GetWidth() - 3
			self.height = self.imagebox.GetHeight() - 3
			self.SetParent(parent)

			## TextLine
			self.textLine = MakeTextLine(self)
			self.textLine.SetText(localeInfo.UI_ITEM)

			## ListBox
			self.listBox = self.ListBoxWithBoard("TOP_MOST")
			self.listBox.SetPickAlways()
			self.listBox.SetParent(self)
			self.listBox.SetEvent(__mem_func__(self.OnSelectItem))
			self.listBox.Hide()

			Window.SetPosition(self, self.x, self.y)
			Window.SetSize(self, self.width, self.height)
			self.textLine.UpdateRect()
			self.__ArrangeListBox()

		def __del__(self):
			Window.__del__(self)

		def Destroy(self):
			self.textLine = None
			self.listBox = None
			self.imagebox = None

		def SetPosition(self, x, y):
			Window.SetPosition(self, x, y)
			self.imagebox.SetPosition(x, y)
			self.x = x
			self.y = y
			self.__ArrangeListBox()

		def SetSize(self, width, height):
			Window.SetSize(self, width, height)
			self.width = width
			self.height = height
			self.textLine.UpdateRect()
			self.__ArrangeListBox()

		def __ArrangeListBox(self):
			self.listBox.SetPosition(0, self.height + 5)
			self.listBox.SetWidth(self.width)

		def Enable(self):
			self.enable = True

		def Disable(self):
			self.enable = False
			self.textLine.SetText("")
			self.CloseListBox()

		def SetEvent(self, event):
			self.event = event

		def ClearItem(self):
			self.CloseListBox()
			self.listBox.ClearItem()

		def InsertItem(self, index, name):
			self.listBox.InsertItem(index, name)
			self.listBox.ArrangeItem()

		def SetCurrentItem(self, text):
			self.textLine.SetText(text)

		def SelectItem(self, key):
			self.listBox.SelectItem(key)

		def OnSelectItem(self, index, name):
			self.CloseListBox()
			self.event(index)

		def CloseListBox(self):
			self.isListOpened = False
			self.listBox.Hide()

		def OnMouseLeftButtonDown(self):
			if not self.enable:
				return

			self.isSelected = True

		def OnMouseLeftButtonUp(self):
			if not self.enable:
				return

			self.isSelected = False

			if self.isListOpened:
				self.CloseListBox()
			else:
				if self.listBox.GetItemCount() > 0:
					self.isListOpened = True
					self.listBox.Show()
					self.__ArrangeListBox()

		def OnUpdate(self):
			if not self.enable:
				return

			if self.IsIn():
				self.isOver = True
			else:
				self.isOver = False

		def OnRender(self):
			self.x, self.y = self.GetGlobalPosition()
			xRender = self.x
			yRender = self.y
			widthRender = self.width
			heightRender = self.height
			if self.isOver:
				grp.SetColor(HALF_WHITE_COLOR)
				grp.RenderBar(xRender + 2, yRender + 3, self.width - 3, heightRender - 5)
				if self.isSelected:
					grp.SetColor(WHITE_COLOR)
					grp.RenderBar(xRender + 2, yRender + 3, self.width - 3, heightRender - 5)

class ShopDecoration(Window):
	CORNER_WIDTH = 48
	CORNER_HEIGHT = 32
	LINE_WIDTH = 16
	LINE_HEIGHT = 16

	NORMAL_CORNER_WIDTH = 16
	NORMAL_CORNER_HEIGHT = 16
	NORMAL_LINE_WIDTH = 16
	NORMAL_LINE_HEIGHT = 16
	NORMAL_BOARD_COLOR = grp.GenerateColor(0.0, 0.0, 0.0, 0.51)

	LT = 0
	LB = 1
	RT = 2
	RB = 3
	L = 0
	R = 1
	T = 2
	B = 3

	def __init__(self, layer = "UI"):
		Window.__init__(self, layer)
		self.border_style = ""
	
	def IsNormalBoard(self):
		return len(self.border_style) == 0
	
	def MakeBoard(self, base):
		self.border_style = base
		
		if self.IsNormalBoard():
			CornerFileNames = [ "d:/ymir work/ui/pattern/ThinBoard_Corner_"+dir+".tga" for dir in ["LeftTop","LeftBottom","RightTop","RightBottom"] ]
			LineFileNames = [ "d:/ymir work/ui/pattern/ThinBoard_Line_"+dir+".tga" for dir in ["Left","Right","Top","Bottom"] ]
		
			self.Corners = []
			for fileName in CornerFileNames:
				Corner = ExpandedImageBox()
				Corner.AddFlag("attach")
				Corner.AddFlag("not_pick")
				Corner.LoadImage(fileName)
				Corner.SetParent(self)
				Corner.SetPosition(0, 0)
				Corner.Show()
				self.Corners.append(Corner)

			self.Lines = []
			for fileName in LineFileNames:
				Line = ExpandedImageBox()
				Line.AddFlag("attach")
				Line.AddFlag("not_pick")
				Line.LoadImage(fileName)
				Line.SetParent(self)
				Line.SetPosition(0, 0)
				Line.Show()
				self.Lines.append(Line)

			Base = Bar()
			Base.SetParent(self)
			Base.AddFlag("attach")
			Base.AddFlag("not_pick")
			Base.SetPosition(self.NORMAL_CORNER_WIDTH, self.NORMAL_CORNER_HEIGHT)
			Base.SetColor(self.NORMAL_BOARD_COLOR)
			Base.Show()
			self.Base = Base

			self.Lines[self.L].SetPosition(0, self.NORMAL_CORNER_HEIGHT)
			self.Lines[self.T].SetPosition(self.NORMAL_CORNER_WIDTH, 0)
		else:
			path = "d:/ymir work/ui/pattern/myshop/%s/p_%s_" % (base, base)
			CornerFileNames = [ path+dir+".tga" for dir in ("Left_Top", "Left_Bottom", "Right_Top", "Right_Bottom", ) ]
			LineFileNames = [ path+dir+".tga" for dir in ("Left", "Right", "Top", "Bottom", ) ]

			self.Corners = []
			for fileName in CornerFileNames:
				Corner = ExpandedImageBox()
				Corner.AddFlag("not_pick")
				Corner.LoadImage(fileName)
				Corner.SetParent(self)
				Corner.SetPosition(0, 0)
				Corner.Show()
				self.Corners.append(Corner)

			self.Lines = []
			for fileName in LineFileNames:
				Line = ExpandedImageBox()
				Line.AddFlag("not_pick")
				Line.LoadImage(fileName)
				Line.SetParent(self)
				Line.SetPosition(0, 0)
				Line.Show()
				self.Lines.append(Line)

			self.Lines[self.L].SetPosition(0, self.CORNER_HEIGHT)
			self.Lines[self.T].SetPosition(self.CORNER_WIDTH, 0)
	
	def __del__(self):
		Window.__del__(self)

	def SetSize(self, textWidth):
		height = 20
		if self.IsNormalBoard():
			width = textWidth + 35
			# width = max(self.NORMAL_CORNER_WIDTH*2, width)
			height = max(self.NORMAL_CORNER_HEIGHT*2, height)
			Window.SetSize(self, width, height)

			self.Corners[self.LB].SetPosition(0, height - self.NORMAL_CORNER_HEIGHT)
			self.Corners[self.RT].SetPosition(width - self.NORMAL_CORNER_WIDTH, 0)
			self.Corners[self.RB].SetPosition(width - self.NORMAL_CORNER_WIDTH, height - self.NORMAL_CORNER_HEIGHT)
			self.Lines[self.R].SetPosition(width - self.NORMAL_CORNER_WIDTH, self.NORMAL_CORNER_HEIGHT)
			self.Lines[self.B].SetPosition(self.NORMAL_CORNER_HEIGHT, height - self.NORMAL_CORNER_HEIGHT)

			verticalShowingPercentage = float((height - self.NORMAL_CORNER_HEIGHT*2) - self.NORMAL_LINE_HEIGHT) / self.NORMAL_LINE_HEIGHT
			horizontalShowingPercentage = float((width - self.NORMAL_CORNER_WIDTH*2) - self.NORMAL_LINE_WIDTH) / self.NORMAL_LINE_WIDTH
			self.Lines[self.L].SetRenderingRect(0, 0, 0, verticalShowingPercentage)
			self.Lines[self.R].SetRenderingRect(0, 0, 0, verticalShowingPercentage)
			self.Lines[self.T].SetRenderingRect(0, 0, horizontalShowingPercentage, 0)
			self.Lines[self.B].SetRenderingRect(0, 0, horizontalShowingPercentage, 0)
			self.Base.SetSize(width - self.NORMAL_CORNER_WIDTH*2, height - self.NORMAL_CORNER_HEIGHT*2)
		else:
			width = textWidth + 100
			# width = max(self.CORNER_WIDTH*2, width)
			height = max(self.CORNER_HEIGHT*2, height)
			Window.SetSize(self, width, height)

			self.Corners[self.LB].SetPosition(0, height - self.CORNER_HEIGHT)
			self.Corners[self.RT].SetPosition(width - self.CORNER_WIDTH, 0)
			self.Corners[self.RB].SetPosition(width - self.CORNER_WIDTH, height - self.CORNER_HEIGHT)
			self.Lines[self.R].SetPosition(width - self.CORNER_WIDTH, self.CORNER_HEIGHT)
			self.Lines[self.B].SetPosition(self.CORNER_WIDTH, height - self.CORNER_HEIGHT)

			verticalShowingPercentage = float((height - self.CORNER_HEIGHT*2) - self.LINE_HEIGHT) / self.LINE_HEIGHT
			horizontalShowingPercentage = float((width - self.CORNER_WIDTH*2) - self.LINE_WIDTH) / self.LINE_WIDTH
			self.Lines[self.L].SetRenderingRect(0, 0, 0, verticalShowingPercentage)
			self.Lines[self.R].SetRenderingRect(0, 0, 0, verticalShowingPercentage)
			self.Lines[self.T].SetRenderingRect(0, 0, horizontalShowingPercentage, 0)
			self.Lines[self.B].SetRenderingRect(0, 0, horizontalShowingPercentage, 0)

class NewBoard(Window):
	CORNER_WIDTH = 32
	CORNER_HEIGHT = 32
	LINE_WIDTH = 128
	LINE_HEIGHT = 128
	LT = 0
	LB = 1
	RT = 2
	RB = 3
	L = 0
	R = 1
	T = 2
	B = 3

	def __init__(self):
		Window.__init__(self)

		self.MakeBoard("d:/ymir work/ui/pattern/new_board/Board_Corner_", "d:/ymir work/ui/pattern/new_board/Board_Line_")
		self.MakeBase()

	def MakeBoard(self, cornerPath, linePath):

		CornerFileNames = [ cornerPath+dir+".tga" for dir in ("LeftTop", "LeftBottom", "RightTop", "RightBottom", ) ]
		LineFileNames = [ linePath+dir+".tga" for dir in ("Left", "Right", "Top", "Bottom", ) ]
		
		self.Corners = []
		for fileName in CornerFileNames:
			Corner = ExpandedImageBox()
			Corner.AddFlag("not_pick")
			Corner.LoadImage(fileName)
			Corner.SetParent(self)
			Corner.SetPosition(0, 0)
			Corner.Show()
			self.Corners.append(Corner)

		self.Lines = []
		for fileName in LineFileNames:
			Line = ExpandedImageBox()
			Line.AddFlag("not_pick")
			Line.LoadImage(fileName)
			Line.SetParent(self)
			Line.SetPosition(0, 0)
			Line.Show()
			self.Lines.append(Line)

		self.Lines[self.L].SetPosition(0, self.CORNER_HEIGHT)
		self.Lines[self.T].SetPosition(self.CORNER_WIDTH, 0)

	def MakeBase(self):
		self.Base = ExpandedImageBox()
		self.Base.AddFlag("not_pick")
		self.Base.LoadImage("d:/ymir work/ui/pattern/new_board/Board_Base.tga")
		self.Base.SetParent(self)
		self.Base.SetPosition(self.CORNER_WIDTH, self.CORNER_HEIGHT)
		self.Base.Show()

	def __del__(self):
		Window.__del__(self)

	def SetSize(self, width, height):
		width = max(self.CORNER_WIDTH*2, width)
		height = max(self.CORNER_HEIGHT*2, height)
		Window.SetSize(self, width, height)

		self.Corners[self.LB].SetPosition(0, height - self.CORNER_HEIGHT)
		self.Corners[self.RT].SetPosition(width - self.CORNER_WIDTH, 0)
		self.Corners[self.RB].SetPosition(width - self.CORNER_WIDTH, height - self.CORNER_HEIGHT)
		self.Lines[self.R].SetPosition(width - self.CORNER_WIDTH, self.CORNER_HEIGHT)
		self.Lines[self.B].SetPosition(self.CORNER_HEIGHT, height - self.CORNER_HEIGHT)

		verticalShowingPercentage = float((height - self.CORNER_HEIGHT*2) - self.LINE_HEIGHT) / self.LINE_HEIGHT
		horizontalShowingPercentage = float((width - self.CORNER_WIDTH*2) - self.LINE_WIDTH) / self.LINE_WIDTH
		self.Lines[self.L].SetRenderingRect(0, 0, 0, verticalShowingPercentage)
		self.Lines[self.R].SetRenderingRect(0, 0, 0, verticalShowingPercentage)
		self.Lines[self.T].SetRenderingRect(0, 0, horizontalShowingPercentage, 0)
		self.Lines[self.B].SetRenderingRect(0, 0, horizontalShowingPercentage, 0)

		if self.Base:
			self.Base.SetRenderingRect(0, 0, horizontalShowingPercentage, verticalShowingPercentage)

class NewBoardWithTitleBar(NewBoard):
	def __init__(self, withButton = False):
		NewBoard.__init__(self)

		self.withButton = withButton
		titleBar = TitleBar()
		if self.withButton is True:
			titleBar = TitleBarWithoutButton()
		titleBar.SetParent(self)
		titleBar.MakeTitleBar(0, "red")
		titleBar.SetPosition(8, 7)
		titleBar.Show()

		titleName = TextLine()
		titleName.SetParent(titleBar)
		titleName.SetPosition(0, 4)
		titleName.SetWindowHorizontalAlignCenter()
		titleName.SetHorizontalAlignCenter()
		titleName.Show()

		self.titleBar = titleBar
		self.titleName = titleName

		if self.withButton is False:
			self.SetCloseEvent(self.Hide)

	def __del__(self):
		NewBoard.__del__(self)
		self.titleBar = None
		self.titleName = None

	def SetSize(self, width, height):
		self.titleBar.SetWidth(width - 15)
		#self.pickRestrictWindow.SetSize(width, height - 30)
		NewBoard.SetSize(self, width, height)
		self.titleName.UpdateRect()

	def SetTitleColor(self, color):
		self.titleName.SetPackedFontColor(color)

	def SetTitleName(self, name):
		self.titleName.SetText(name)

	def SetCloseEvent(self, event):
		if self.withButton is False:
			self.titleBar.SetCloseEvent(event)

class TitleBarWithoutButton(Window):
	BLOCK_WIDTH = 32
	BLOCK_HEIGHT = 23

	def __init__(self):
		Window.__init__(self)
		self.AddFlag("attach")

	def __del__(self):
		Window.__del__(self)

	def MakeTitleBar(self, width, color):

		## 현재 Color는 사용하고 있지 않음

		width = max(64, width)

		imgLeft = ImageBox()
		imgCenter = ExpandedImageBox()
		imgRight = ImageBox()
		imgLeft.AddFlag("not_pick")
		imgCenter.AddFlag("not_pick")
		imgRight.AddFlag("not_pick")
		imgLeft.SetParent(self)
		imgCenter.SetParent(self)
		imgRight.SetParent(self)

		if localeInfo.IsARABIC():
			imgLeft.LoadImage("locale/ae/ui/pattern/titlebar_left.tga")
			imgCenter.LoadImage("locale/ae/ui/pattern/titlebar_center.tga")
			imgRight.LoadImage("locale/ae/ui/pattern/titlebar_right_without_x.tga")
		else:
			imgLeft.LoadImage("d:/ymir work/ui/pattern/titlebar_left.tga")
			imgCenter.LoadImage("d:/ymir work/ui/pattern/titlebar_center.tga")
			imgRight.LoadImage("d:/ymir work/ui/pattern/titlebar_right_without_x.tga")

		imgLeft.Show()
		imgCenter.Show()
		imgRight.Show()

		self.imgLeft = imgLeft
		self.imgCenter = imgCenter
		self.imgRight = imgRight

		self.SetWidth(width)

	def SetWidth(self, width):
		self.imgCenter.SetRenderingRect(0.0, 0.0, float((width - self.BLOCK_WIDTH*2) - self.BLOCK_WIDTH) / self.BLOCK_WIDTH, 0.0)
		self.imgCenter.SetPosition(self.BLOCK_WIDTH, 0)
		self.imgRight.SetPosition(width - self.BLOCK_WIDTH, 0)
			
		self.SetSize(width, self.BLOCK_HEIGHT)

class NewScrollBar(Window):
	SCROLLBAR_WIDTH = 17
	SCROLLBAR_MIDDLE_HEIGHT = 9
	SCROLLBAR_BUTTON_WIDTH = 17
	SCROLLBAR_BUTTON_HEIGHT = 17
	MIDDLE_BAR_POS = 0
	MIDDLE_BAR_UPPER_PLACE = 3
	MIDDLE_BAR_DOWNER_PLACE = 4
	TEMP_SPACE = MIDDLE_BAR_UPPER_PLACE + MIDDLE_BAR_DOWNER_PLACE

	class MiddleBar(DragButton):
		def __init__(self):
			DragButton.__init__(self)
			self.AddFlag("movable")

		def MakeImage(self):

			middle = ExpandedImageBox()
			middle.SetParent(self)
			middle.LoadImage("d:/ymir work/ui/pattern/new_scroll/scrollbar_middle.tga")
			middle.SetPosition(0, 0)
			middle.AddFlag("not_pick")
			middle.Show()

			self.middle = middle

		def SetSize(self, height):
			height = max(12, height)
			DragButton.SetSize(self, 10, height)

			height -= 4*3
			self.middle.SetRenderingRect(0, 0, 0, float(height)/4.0)

	def __init__(self):
		Window.__init__(self)

		self.pageSize = 1
		self.curPos = 0.0
		self.eventScroll = lambda *arg: None
		self.lockFlag = False
		self.scrollStep = 0.20

		self.eventFuncCall = True

		self.CreateScrollBar()

	def __del__(self):
		Window.__del__(self)

	def CreateScrollBar(self):
		barSlot = ExpandedImageBox()
		barSlot.SetParent(self)
		barSlot.LoadImage("d:/ymir work/ui/pattern/new_scroll/base_scroll.tga")
		barSlot.AddFlag("not_pick")
		barSlot.Show()

		middleBar = self.MiddleBar()
		middleBar.SetParent(self)
		middleBar.SetMoveEvent(__mem_func__(self.OnMove))
		middleBar.Show()
		middleBar.MakeImage()
		middleBar.SetSize(12)
		
		self.middleBar = middleBar
		self.barSlot = barSlot

		self.SCROLLBAR_WIDTH = self.middleBar.GetWidth()
		self.SCROLLBAR_MIDDLE_HEIGHT = self.middleBar.GetHeight()
		self.SCROLLBAR_BUTTON_WIDTH = self.middleBar.GetWidth()
		self.SCROLLBAR_BUTTON_HEIGHT = self.middleBar.GetHeight()

	def Destroy(self):
		self.middleBar = None
		self.eventScroll = lambda *arg: None

		self.eventFuncCall	= True

	def SetEvnetFuncCall(self, callable):
		self.eventFuncCall = callable

	def SetScrollEvent(self, event):
		self.eventScroll = event

	def SetMiddleBarSize(self, pageScale):
		realHeight = self.GetHeight() - self.SCROLLBAR_BUTTON_HEIGHT*2
		self.SCROLLBAR_MIDDLE_HEIGHT = int(pageScale * float(realHeight))
		self.middleBar.SetSize(self.SCROLLBAR_MIDDLE_HEIGHT)
		self.pageSize = (self.GetHeight() - self.SCROLLBAR_BUTTON_HEIGHT*2) - self.SCROLLBAR_MIDDLE_HEIGHT - (self.TEMP_SPACE)

	def SetScrollBarSize(self, height):
		self.pageSize = (height - self.SCROLLBAR_BUTTON_HEIGHT*2) - self.SCROLLBAR_MIDDLE_HEIGHT - (self.TEMP_SPACE)
		self.SetSize(self.SCROLLBAR_WIDTH, height)
		self.middleBar.SetRestrictMovementArea(self.MIDDLE_BAR_POS, self.SCROLLBAR_BUTTON_HEIGHT + self.MIDDLE_BAR_UPPER_PLACE, self.MIDDLE_BAR_POS+2, height - self.SCROLLBAR_BUTTON_HEIGHT*2 - self.TEMP_SPACE)
		self.middleBar.SetPosition(self.MIDDLE_BAR_POS, 0)

		self.UpdateBarSlot()

	def UpdateBarSlot(self):
		self.barSlot.SetPosition(0, self.SCROLLBAR_BUTTON_HEIGHT)
		height =  - self.SCROLLBAR_BUTTON_HEIGHT*2 - 2
		new_height = float(self.GetHeight()) / float(self.barSlot.GetHeight())
		self.barSlot.SetRenderingRect(0.0, 0.0, 0.0, new_height - 2.8)

	def GetPos(self):
		return self.curPos

	def SetPos(self, pos, event_callable = True):
		pos = max(0.0, pos)
		pos = min(1.0, pos)

		newPos = float(self.pageSize) * pos
		self.middleBar.SetPosition(self.MIDDLE_BAR_POS, int(newPos) + self.SCROLLBAR_BUTTON_HEIGHT + self.MIDDLE_BAR_UPPER_PLACE)

		self.OnMove(event_callable)

	def SetScrollStep(self, step):
		self.scrollStep = step

	def GetScrollStep(self):
		return self.scrollStep

	def OnUp(self):
		self.SetPos(self.curPos-self.scrollStep, self.eventFuncCall)

	def OnDown(self):
		self.SetPos(self.curPos+self.scrollStep, self.eventFuncCall)

	def OnMove(self, event_callable = True):
		if self.lockFlag:
			return

		if 0 == self.pageSize:
			return

		(xLocal, yLocal) = self.middleBar.GetLocalPosition()
		self.curPos = float(yLocal - self.SCROLLBAR_BUTTON_HEIGHT - self.MIDDLE_BAR_UPPER_PLACE) / float(self.pageSize)

		if event_callable:
			self.eventScroll()

	def OnMouseLeftButtonDown(self):
		(xMouseLocalPosition, yMouseLocalPosition) = self.GetMouseLocalPosition()
		pickedPos = yMouseLocalPosition - self.SCROLLBAR_BUTTON_HEIGHT - self.SCROLLBAR_MIDDLE_HEIGHT/2
		newPos = float(pickedPos) / float(self.pageSize)
		self.SetPos(newPos)

	def LockScroll(self):
		self.lockFlag = True

	def UnlockScroll(self):
		self.lockFlag = False

	def RunMouseWheel(self, nLen):
		if nLen > 0:
			self.OnUp()
		else:
			self.OnDown()

#arat class SlotWindow ve sonuna ekle

	if app.WJ_ENABLE_TRADABLE_ICON:
		def SetCanMouseEventSlot(self, slotIndex):
			wndMgr.SetCanMouseEventSlot(self.hWnd, slotIndex)

		def SetCantMouseEventSlot(self, slotIndex):
			wndMgr.SetCantMouseEventSlot(self.hWnd, slotIndex)

		def SetUsableSlotOnTopWnd(self, slotIndex):
			wndMgr.SetUsableSlotOnTopWnd(self.hWnd, slotIndex)

		def SetUnusableSlotOnTopWnd(self, slotIndex):
			wndMgr.SetUnusableSlotOnTopWnd(self.hWnd, slotIndex)

	def SetSlotCoverImage(self, slotindex, filename):
		wndMgr.SetSlotCoverImage(self.hWnd, slotindex, filename)

	def EnableSlotCoverImage(self, slotindex, onoff):
		wndMgr.EnableSlotCoverImage(self.hWnd, slotindex, onoff)

#arat class ExpandedImageBox ve sonuna ekle

	def SetCoolTime(self, time, elapsedTime = 0.0):
		wndMgr.SetCoolTimeImageBox(self.hWnd, time, elapsedTime)
	
	def IsInCoolTime(self):
		return wndMgr.IsInCoolTime(self.hWnd)

	def SetStartCoolTime(self, time):
		wndMgr.SetStartCoolTimeImageBox(self.hWnd, time)

#arat class Editline ve sonuna ekle

	def SetUpdateEvent(self, event, *args):
		self.update_event = event
		if len(args) != 0:
			self.update_event_args = args
	
	def OnUpdateEvent(self):
		if self.update_event:
			if self.update_event_args:
				self.update_event(self.update_event_args[0])
			else:
				self.update_event()

	#PlaceHolder funcs
	def UpdatePlaceHolder(self):
		self.placeHolder.Show() if len(self.GetText()) <= 0 and self.CheckPlaceHolder() is True else self.placeHolder.Hide()

	def SetPlaceHolder(self, placeHolderText, placeHolderPos = (0, 0)):
		if not self.placeHolder:
			return
		
		self.placeHolder.SetText(placeHolderText)
		self.placeHolder.SetPosition(*placeHolderPos)
		self.UpdatePlaceHolder()
	
	def SetPlaceHolderColor(self, color):
		if not self.placeHolder:
			return
		
		self.placeHolder.SetPackedFontColor(color)

	def CheckPlaceHolder(self):
		return bool(len(self.placeHolder.GetText())) #return true or false

	def SetMaxSizeMode(self, forceWidht = -1):
		self.max_size = self.GetWidth() if forceWidht == -1 else forceWidht

#arat class Editline ve def__init__ içine ekle

		self.placeHolder = TextLine()
		self.placeHolder.SetParent(self)
		self.placeHolder.SetText("")
		self.placeHolder.Hide()

#arat class Editline ve def__del__ içine ekle

		self.placeHolder = None

		self.max_size = -1

#arat

			elif Type == "board":
				parent.Children[Index] = Board()
				parent.Children[Index].SetParent(parent)
				self.LoadElementBoard(parent.Children[Index], ElementValue, parent)

#altına ekle

			elif Type == "new_board":
				parent.Children[Index] = NewBoard()
				parent.Children[Index].SetParent(parent)
				self.LoadElementBoard(parent.Children[Index], ElementValue, parent)

			elif Type == "new_board_with_titlebar":
				parent.Children[Index] = NewBoardWithTitleBar()
				parent.Children[Index].SetParent(parent)
				self.LoadElementBoardWithTitleBar(parent.Children[Index], ElementValue, parent)

			elif Type == "new_scrollbar":
				parent.Children[Index] = NewScrollBar()
				parent.Children[Index].SetParent(parent)
				self.LoadElementScrollBar(parent.Children[Index], ElementValue, parent)

#arat

def MakeButton(parent, x, y, tooltipText, path, up, over, down):

#altına ekle

def MakeRadioButton(parent, x, y, buttonText, path, up, over, down, tooltip = ""):
	button = RadioButton()
	button.SetParent(parent)
	button.SetPosition(x, y)
	button.SetUpVisual(path + up)
	button.SetOverVisual(path + over)
	button.SetDownVisual(path + down)
	button.SetText(buttonText)
	button.SetToolTipText(tooltip)
	button.Show()
	return button

def MakeExpandedImageBox(parent, name, x, y):
	image = ExpandedImageBox()
	image.SetParent(parent)
	image.LoadImage(name)
	image.SetPosition(x, y)
	image.Show()
	return image

def MakeNewScrollBar(parent, x, y, height):
	scrollbar = NewScrollBar()
	scrollbar.SetParent(parent)
	scrollbar.SetPosition(x, y)
	scrollbar.SetScrollBarSize(height)
	scrollbar.Show()
	return scrollbar

#class ImageBox içinde bul

			self.eventFunc = {"mouse_click" : None, "mouse_over_in" : None, "mouse_over_out" : None}
			self.eventArgs = {"mouse_click" : None, "mouse_over_in" : None, "mouse_over_out" : None}

#değiştir (yoksa def __init__ içine ekle)

		self.eventFunc = {"mouse_rclick" : None, "mouse_click" : None, "mouse_over_in" : None, "mouse_over_out" : None}
		self.eventArgs = {"mouse_rclick" : None, "mouse_click" : None, "mouse_over_in" : None, "mouse_over_out" : None}

#aynı class içinde def __del__ içine ekle

		self.eventFunc = None
		self.eventArgs = None

#yine aynı classta arat

	def OnMouseOverIn(self):
		try:
			self.eventDict["MOUSE_OVER_IN"]()
		except KeyError:
			pass

	def OnMouseOverOut(self):
		try:
			self.eventDict["MOUSE_OVER_OUT"]()
		except KeyError:
			pass

	def SAFE_SetStringEvent(self, event, func):
		self.eventDict[event]=__mem_func__(func)

#değiştir

	def SetEvent(self, func, *args):
		result = self.eventFunc.has_key(args[0])
		if result:
			self.eventFunc[args[0]] = func
			self.eventArgs[args[0]] = args
		else:
			print "[ERROR] ui.py SetEvent, Can`t Find has_key : %s" % args[0]

	def OnMouseLeftButtonDown(self) :
		if self.eventFunc["mouse_click"] :
			apply(self.eventFunc["mouse_click"], self.eventArgs["mouse_click"])
		else:
			try:
				apply(self.eventDict["MOUSE_CLICK"][0], self.eventDict["MOUSE_CLICK"][1])
			except KeyError:
				pass
	
	def OnMouseRightButtonDown(self) :
		if self.eventFunc["mouse_rclick"] :
			apply(self.eventFunc["mouse_rclick"], self.eventArgs["mouse_rclick"])
		else:
			try:
				apply(self.eventDict["MOUSE_RCLICK"][0], self.eventDict["MOUSE_RCLICK"][1])
			except KeyError:
				pass

	def OnMouseOverIn(self) :
		if self.eventFunc["mouse_over_in"] :
			apply(self.eventFunc["mouse_over_in"], self.eventArgs["mouse_over_in"])
		else:
			try:
				apply(self.eventDict["MOUSE_OVER_IN"][0], self.eventDict["MOUSE_OVER_IN"][1])
			except KeyError:
				pass

	def OnMouseOverOut(self) :
		if self.eventFunc["mouse_over_out"] :
			apply(self.eventFunc["mouse_over_out"], self.eventArgs["mouse_over_out"])
		else :
			try:
				apply(self.eventDict["MOUSE_OVER_OUT"][0], self.eventDict["MOUSE_OVER_OUT"][1])
			except KeyError:
				pass