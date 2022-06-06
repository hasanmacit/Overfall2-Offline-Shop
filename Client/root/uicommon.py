#importlara ekle

import constInfo

#arat Class InputDialog ve üstüne ekle

class NewMoneyInputDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		
		self.FEE = 3 #3% de taxa de venda
		self.moneyHeaderText = localeInfo.OFFLINE_SHOP_MONEY_INPUT_DIALOG_SELLPRICE
		self.moneyHeaderFeeText = localeInfo.OFFLINE_SHOP_MONEY_INPUT_DIALOG_FEE % self.FEE
		self.__CreateDialog()
		self.SetMaxLength(15)

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __CreateDialog(self):
		pyScrLoader = ui.PythonScriptLoader()
		pyScrLoader.LoadScriptFile(self, "uiscript/moneyinputdialognew.py")

		getObject = self.GetChild
		self.board = self.GetChild("board")
		self.acceptButton = getObject("AcceptButton")
		self.cancelButton = getObject("CancelButton")
		self.inputValue = getObject("InputValue")
		self.inputValue.OnIMEUpdate = ui.__mem_func__(self.__OnValueUpdate)
		self.moneyText = getObject("MoneyValue")
		self.moneyTextFee = getObject("MoneyFeeValue")

	def Open(self):
		self.inputValue.SetText("")
		self.inputValue.SetFocus()
		self.__OnValueUpdate()
		self.SetCenterPosition()
		self.SetTop()
		self.Show()

	def Close(self):
		if app.ENABLE_CHEQUE_SYSTEM:
			self.inputChequeValue = None

		self.ClearDictionary()
		self.board = None
		self.acceptButton = None
		self.cancelButton = None
		self.inputValue = None
		self.Hide()

	def SetTitle(self, name):
		self.board.SetTitleName(name)

	def SetFocus(self):
		self.inputValue.SetFocus()

	def SetMaxLength(self, length):
		length = min(15, length)
		self.inputValue.SetMax(length)

	def SetAcceptEvent(self, event):
		self.acceptButton.SetEvent(event)
		self.inputValue.OnIMEReturn = event

	def SetCancelEvent(self, event):
		self.board.SetCloseEvent(event)
		self.cancelButton.SetEvent(event)
		self.inputValue.OnPressEscapeKey = event

	def SetValue(self, value):
		value=str(value)
		self.inputValue.SetText(value)
		self.__OnValueUpdate()
		ime.SetCursorPosition(len(value)+1)

	def GetText(self):
		return self.inputValue.GetText()
	
	def GetRealMoney(self):
		text = self.inputValue.GetText()
		value_converted = constInfo.ConvertMoneyText(text)
		moneyValue = min(value_converted, 125000000000000)
		return moneyValue
	
	def __calc_money_fee__(self, moneyMax):
		moneyMax -= ((self.FEE * moneyMax) / 100)
		return moneyMax

	def __OnValueUpdate(self):
		ui.EditLine.OnIMEUpdate(self.inputValue)
		moneyValue = self.GetRealMoney()
		moneyWithFee = self.__calc_money_fee__(moneyValue)
		
		self.moneyText.SetText(self.moneyHeaderText + " " + localeInfo.NumberToMoneyStringWithIcon(moneyValue))
		self.moneyTextFee.SetText(self.moneyHeaderFeeText + " " + localeInfo.NumberToMoneyStringWithIcon(moneyWithFee))

class InputDialogOfflineShop(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)

		self.__CreateDialog()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __CreateDialog(self):
		pyScrLoader = ui.PythonScriptLoader()
		pyScrLoader.LoadScriptFile(self, "uiscript/inputdialogofflineshop.py")

		getObject = self.GetChild
		self.board = getObject("Board")
		self.acceptButton = getObject("AcceptButton")
		self.cancelButton = getObject("CancelButton")
		self.inputSlot = getObject("InputSlot")
		self.inputValue = getObject("InputValue")

	def Open(self):
		self.inputValue.SetFocus()
		self.SetCenterPosition()
		self.SetTop()
		self.Show()

	def Close(self):
		self.ClearDictionary()
		self.board = None
		self.acceptButton = None
		self.cancelButton = None
		self.inputSlot = None
		self.inputValue = None
		self.Hide()

	def SetTitle(self, name):
		self.board.SetTitleName(name)

	def SetNumberMode(self):
		self.inputValue.SetNumberMode()

	#MT-679 °³ÀÎ »óÁ¡ Å¸ÀÌÆ²ÀÇ CodePage ÀÌ½´
	def SetUseCodePage(self, bUse = True):
		self.inputValue.SetUseCodePage(bUse)

	def SetSecretMode(self):
		self.inputValue.SetSecret()

	def SetFocus(self):
		self.inputValue.SetFocus()

	def SetMaxLength(self, length):
		self.inputValue.SetMax(length)
	
	def SetMaxSizeMode(self):
		self.inputValue.SetMaxSizeMode()

	def SetSlotWidth(self, width):
		self.inputSlot.SetSize(width, self.inputSlot.GetHeight())
		self.inputValue.SetSize(width, self.inputValue.GetHeight())
		if self.IsRTL():
			self.inputValue.SetPosition(self.inputValue.GetWidth(), 0)

	def SetAcceptEvent(self, event):
		self.acceptButton.SetEvent(event)
		self.inputValue.OnIMEReturn = event

	def SetCancelEvent(self, event):
		self.board.SetCloseEvent(event)
		self.cancelButton.SetEvent(event)
		self.inputValue.SetEscapeEvent(event)

	def GetText(self):
		return self.inputValue.GetText()