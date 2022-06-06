#arat

self.characterNameValue = None

#altına ekle

		if app.ENABLE_PREMIUM_MEMBERS:
			self.overfall2_premium = None

#arat

self.characterNameValue = self.GetChild("Character_Name")

#altına ekle

		if app.ENABLE_PREMIUM_MEMBERS:
			self.overfall2_premium = self.GetChild("overfall2_premium")

#arat

def OnPressEscapeKey(self):

#altına ekle
	if app.ENABLE_PREMIUM_MEMBERS:
		def __GetPlayerPremium(self):
			return chr.IsOverfallPremium()

#arat

	def OnUpdate(self):
		self.__UpdateQuestClock()

#altına ekle
		if app.ENABLE_PREMIUM_MEMBERS:
			if self.overfall2_premium:
				if self.__GetPlayerPremium():
					if not self.overfall2_premium.IsShow():
						self.overfall2_premium.Show()
				else:
					if self.overfall2_premium.IsShow():
						self.overfall2_premium.Hide()