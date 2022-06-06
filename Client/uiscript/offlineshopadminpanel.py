import app
import uiScriptLocale

window = {
	"name" : "OfflineShopAdminPanelWindow",
	
	"style" : ("movable", "float",),
	
	"x" : 0,
	"y" : 0,
	
	"width" : 250,
	"height" : 204,
	
	"children":
	(
		{
			"name" : "Board",
			"type" : "board_with_titlebar",
			
			"style" : ("attach", ),
			
			"x" : 0,
			"y" : 0,
			
			"width" : 250,
			"height" : 204,
			
			"title" : "Çevrimdýþý Pazar Yönetim Paneli",
			
			"children" :
			(
				# Get back
				{
					"name" : "GetBackButton",
					"type" : "button",
					
					"x" : 79,
					"y" : 100,
					
					"text" : "Satýlmayanlar",
					
					"default_image" : "d:/ymir work/ui/public/large_button_01.sub",
					"over_image" : "d:/ymir work/ui/public/large_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/large_button_03.sub",					
				},
				{
					"name" : "Pazara_Git",
					"type" : "button",
					
					"x" : 79,
					"y" : 100,
					
					"text" : "Pazara Git",
					
					"default_image" : "d:/ymir work/ui/public/large_button_01.sub",
					"over_image" : "d:/ymir work/ui/public/large_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/large_button_03.sub",
				},
				{
					"name" : "CloseOfflineShopButton",
					"type" : "button",
					
					"x" : 79,
					"y" : 125,
					
					"text" : "Dükkaný Kapat",
					
					"default_image" : "d:/ymir work/ui/public/large_button_01.sub",
					"over_image" : "d:/ymir work/ui/public/large_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/large_button_03.sub",
				},
												
				{
					"name" : "MyBankButton",
					"type" : "button",
					
					"x" : 79,
					"y" : 150,
					
					"text" : "Bankam",
					
					"default_image" : "d:/ymir work/ui/public/large_button_01.sub",
					"over_image" : "d:/ymir work/ui/public/large_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/large_button_03.sub",										
				},
				
				# User Name
				{
					"name" : "UserName",
					"type" : "text",
					
					"x" : 26,
					"y" : 37,
					
					"text" : "Merhaba",
				},
			),
		},
	),
}