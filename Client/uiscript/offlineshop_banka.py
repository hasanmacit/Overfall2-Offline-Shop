import app
import uiScriptLocale

window = {
	"name" : "OfflineShopBankWindow",
	
	"style" : ("movable", "float", ),
	
	"x" : 0,
	"y" : 0,
	
	"width" : 300,
	"height" : 130,
	
	"children" :
	(
		{
			"name" : "Board",
			"type" : "board_with_titlebar",
			
			"style" : ("attach", ),
			
			"x" : 0,
			"y" : 0,
			
			"width" : 300,
			"height" : 130,
			
			"title" : "Çevrimdýþý Dükkan Kasasý",
			
			"children" :
			(
				{ 
					"name" : "icon",
					"type" : "expanded_image",
					
					"x" : 13,
					"y" : 38,
					
					"image" : uiScriptLocale.LOCALE_OFFLINESHOP_PATH + "/moneybag.tga",
				},
				
				{
					"name" : "CurrentMoneySlot",
					"type" : "button",
					
					"x" : 37-10,
					"y" : 46+18+6+10,
					
					"width" : 210,
					"height" : 18,
					"horizontal_align":"center",
					"vertical_align":"bottom",

					"default_image" : "d:/ymir work/ui/public/parameter_slot_05.sub",
					"over_image" : "d:/ymir work/ui/public/parameter_slot_05.sub",
					"down_image" : "d:/ymir work/ui/public/parameter_slot_05.sub",
					
					"children" :
					(
						{
							"name" : "CurrentMoneyLine",
							"type" : "text",
							
							"x" : 3,
							"y" : 3,
							
							"width" : 210,
							"height" : 16,
							
							"input_limit" : 12,
							"text" : "bekleyiniz...",
						},	
					),
				},
				{
					"name" : "cancel_button",
					"type" : "button",
					
					"x" : 35+150+5,
					"y" : 85+4,
					
					"text" : "Kapat",
					
					"default_image" : "d:/ymir work/ui/public/large_button_01.sub",
					"over_image" : "d:/ymir work/ui/public/large_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/large_button_03.sub",					
				},
			),
		},
	),
}