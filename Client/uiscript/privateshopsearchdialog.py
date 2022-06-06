import app
import item
import uiScriptLocale
import localeInfo

LOCALE_PATH = "d:/ymir work/ui/privatesearch/"
MAIN_PATH = "d:/ymir work/ui/search_shop/"
GOLD_COLOR	= 0xFFFEE3AE

BOARD_WIDTH = 794
BOARD_HEIGHT = 545

window = {
	"name" : "PrivateShopSearchDialog",

	"x" : 0,
	"y" : 0,

	"style" : ("movable", "float",),

	"width" : BOARD_WIDTH,
	"height" : BOARD_HEIGHT,

	"children" :
	(
		{
			"name" : "board",
			"type" : "board_with_titlebar",

			"x" : 0,
			"y" : 0,

			"width" : BOARD_WIDTH,
			"height" : BOARD_HEIGHT,
			
			"title" : uiScriptLocale.PRIVATESHOPSEARCH_SEARCH_BAR,
		
			"children" :
			(
				## ItemName
				{
					"name" : "ItemNameImg",
					"type" : "image",
					"x" : 10,
					"y" : 275+20,
					"image" : LOCALE_PATH+"private_leftNameImg.sub",
					"children" :
					(
						{ "name" : "ItemNameText", "type" : "text", "text_horizontal_align":"center", "x" : 60, "y" : 5, "text" : uiScriptLocale.PRIVATESHOPSEARCH_ITEMNAME, "color":GOLD_COLOR },
					),
				},
				## ItemNameEditLine
				{
					"name" : "ItemNameSlot",
					"type" : "image",
					"x" : 12,
					"y" : 295+20,
					"image" : LOCALE_PATH+"private_leftSlotImg.sub",
					"children" :
					(
						{
							"name" : "ItemNameValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 136,
							"height" : 15,
							"input_limit" : 20,
							"text" : "",
						},
					),
				},
				## LevelText
				{
					"name" : "LevelImg",
					"type" : "image",
					"x" : 10,
					"y" : 135,
					"image" : LOCALE_PATH+"private_leftNameImg.sub",
					"children" :
					(
						{ "name" : "LevelText", "type" : "text", "text_horizontal_align":"center", "x" : 60, "y" : 5, "text" : uiScriptLocale.PRIVATESHOPSEARCH_LEVEL, "color":GOLD_COLOR },
					),
				},
				## LevelText2
				{ "name" : "LevelText2", "type" : "text", "x" : 65, "y" : 158, "text" : "~", "fontsize":"LARGE",},
				## minLevelEditLine
				{
					"name" : "minLevelSlot",
					"type" : "image",
					"x" : 12,
					"y" : 155,
					"image" : LOCALE_PATH+"private_leftSlotHalfImg.sub",

					"children" :
					(
						{
							"name" : "minLevelValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 36,
							"height" : 15,
							"input_limit" : 3,
							"only_number" : 1,
							"text" : "1",
						},
					),
				},
				## maxLevelEditLine
				{
				
					"name" : "maxLevelSlot",
					"type" : "image",
					"x" : 90,
					"y" : 155,
					"image" : LOCALE_PATH+"private_leftSlotHalfImg.sub",

					"children" :
					(
						{
							"name" : "maxLevelValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 36,
							"height" : 15,
							"input_limit" : 3,
							"only_number" : 1,
							"text" : "120",
						},
					),
				},
				## refineText
				{
					"name" : "refineImg",
					"type" : "image",
					"x" : 10,
					"y" : 175,
					"image" : LOCALE_PATH+"private_leftNameImg.sub",
					"children" :
					(
						{ "name" : "refineText", "type" : "text", "text_horizontal_align":"center", "x" : 60, "y" : 5, "text" : uiScriptLocale.PRIVATESHOPSEARCH_REFINE, "color":GOLD_COLOR },
					),
				},
				## refineText2
				{ "name" : "refineText2", "type" : "text", "x" : 65, "y" : 198, "text" : "~", "fontsize":"LARGE"},
				## minrefineEditLine
				{
					"name" : "minrefineSlot",
					"type" : "image",
					"x" : 12,
					"y" : 195,
					"image" : LOCALE_PATH+"private_leftSlotHalfImg.sub",
					"children" :
					(
						{
							"name" : "minrefineValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 36,
							"height" : 15,
							"input_limit" : 3,
							"only_number" : 1,
							"text" : "0",
						},
					),
				},
				## maxrefineEditLine
				{
					"name" : "maxrefineSlot",
					"type" : "image",
					"x" : 90,
					"y" : 195,
					"image" : LOCALE_PATH+"private_leftSlotHalfImg.sub",

					"children" :
					(
						{
							"name" : "maxrefineValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 36,
							"height" : 15,
							"input_limit" : 3,
							"only_number" : 1,
							"text" : "9",
						},
					),
				},
				## GoldText
				{
					"name" : "GoldImg",
					"type" : "image",
					"x" : 10,
					"y" : 215,
					"image" : LOCALE_PATH+"private_leftNameImg.sub",
					"children" :
					(
						{ "name" : "GoldText", "type" : "text", "text_horizontal_align":"center", "x" : 60, "y" : 5, "text" : uiScriptLocale.PRIVATESHOPSEARCH_PRICE, "color":GOLD_COLOR },
					),
				},
				## GoldminEditLine
				{
					"name":"Money_Icon",
					"type":"image",

					"x":12,
					"y":267,

					"image":"d:/ymir work/ui/game/windows/money_icon.sub",
				},
				{
					"name" : "GoldminSlot",
					"type" : "image",
					"x" : 33,
					"y" : 235+20,
					"image" : LOCALE_PATH+"private_goldSlot.sub",

					"children" :
					(
						{
							"name" : "GoldminValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 94,
							"height" : 15,
							"input_limit" : 10,
							"only_number" : 1,
							"text" : "0",
						},
					),
				},
				## GoldmaxEditLine
				{
					"name" : "GoldmaxSlot",
					"type" : "image",
					"x" : 33,
					"y" : 255+20,
					"image" : LOCALE_PATH+"private_goldSlot.sub",

					"children" :
					(
						{
							"name" : "GoldmaxValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 94,
							"height" : 15,
							"input_limit" : 10,
							"only_number" : 1,
							"text" : "1999999999",
						},
					),
				},
				{ "name" : "chequeText", "type" : "text", "x" : 75, "y" : 238, "text" : "~", "fontsize":"LARGE"},
				## ChequeminSlot
				{
					"name":"Cheque_Icon",
					"type":"image",

					"x":12,
					"y":238,

					"image":"d:/ymir work/ui/game/windows/cheque_icon.sub",
				},
				{
					"name" : "ChequeminSlot",
					"type" : "image",
					"x" : 33,
					"y" : 235,
					"image" : LOCALE_PATH+"private_leftSlotHalfImg.sub",

					"children" :
					(
						{
							"name" : "ChequeminValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 115,
							"height" : 15,
							"input_limit" : 3,
							"only_number" : 0,
							"text" : "0",
						},
					),
				},
				## ChequemaxSlot
				{
					"name" : "ChequemaxSlot",
					"type" : "image",
					"x" : 90,
					"y" : 235,
					"image" : LOCALE_PATH+"private_leftSlotHalfImg.sub",

					"children" :
					(
						{
							"name" : "ChequemaxValue",
							"type" : "editline",
							"x" : 2,
							"y" : 3,
							"width" : 135,
							"height" : 15,
							"input_limit" : 3,
							"only_number" : 0,
							"text" : "99",
						},
					),
				},
				## Name
				{
					"name" : "name_warrior",
					"type" : "image",

					"x" : 10,
					"y" : 35,

					"image" : LOCALE_PATH+"private_leftNameImg.sub",
					"children" :
					(
						{ "name" : "ItemNameText", "type" : "text", "text_horizontal_align":"center", "x" : 60, "y" : 5, "text" : uiScriptLocale.PRIVATESHOPSEARCH_JOB, "color":GOLD_COLOR },
					),
				},
		
				## ItemTypeName
				{
					"name" : "ItemTypeImg",
					"type" : "image",
					"x" : 10,
					"y" : 75,
					"image" : LOCALE_PATH+"private_leftNameImg.sub",
					"children" :
					(
						{ "name" : "ItemTypeName", "type" : "text", "text_horizontal_align":"center", "x" : 60, "y" : 5, "text" : uiScriptLocale.PRIVATESHOPSEARCH_ITEMTYPE, "color":GOLD_COLOR },
					),
				},
				## FindButton
				{
					"name" : "SearchButton",
					"type" : "button",

					"x" : 10,
					"y" : 338,

					"text" : uiScriptLocale.PRIVATESHOPSEARCH_SEARCH,

					"default_image" : LOCALE_PATH + "private_findbuttonImg01.sub",
					"over_image" : LOCALE_PATH + "private_findbuttonImg02.sub",
					"down_image" : LOCALE_PATH + "private_findbuttonImg03.sub",
				},
				## BuyButton
				{
					"name" : "BuyButton",
					"type" : "button",

					"x" : BOARD_WIDTH - 137,
					"y" : 338,

					"text" : uiScriptLocale.PRIVATESHOPSEARCH_BUY,

					"default_image" : "d:/ymir work/ui/privatesearch/private_findbuttonImg01.sub",
					"over_image" : "d:/ymir work/ui/privatesearch/private_findbuttonImg02.sub",
					"down_image" : "d:/ymir work/ui/privatesearch/private_findbuttonImg03.sub",
				},
				
				##Background Image
				{
					"name" : "search_bg",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 140,
					"y" : 65,
					
					"image" : MAIN_PATH + "search_bg.tga",
				},
				
				## tab_menu_01
				{
					"name" : "ItemTypeImg",
					"type" : "expanded_image",
					"x" : 136,
					"y" : 39,
					"width" : 10,
					"image" : "d:/ymir work/ui/tab_menu_01.tga",
					"x_scale" : 1.22, 
					"y_scale" : 1.0,
					"children" :
					(
						## Text
						{ "name" : "ResultNameText1", "type" : "text", "x" : 67, "y" : 4,  "text" : uiScriptLocale.PRIVATESHOPSEARCH_ITEMNAME, },
						{ "name" : "ResultNameText2", "type" : "text", "x" : 207, "y" : 4, "text" : uiScriptLocale.PRIVATESHOPSEARCH_SELLER, },
						{ "name" : "ResultNameText3", "type" : "text", "x" : 303, "y" : 4, "text" : uiScriptLocale.PRIVATESHOPSEARCH_COUNT, },
						{ "name" : "ResultNameText4", "type" : "text", "x" : 454, "y" : 4, "text" : localeInfo.CHEQUE_SYSTEM_UNIT_YANG, },
						{ "name" : "ResultNameText5", "type" : "text", "x" : 375, "y" : 4, "text" : localeInfo.CHEQUE_SYSTEM_UNIT_WON, },
					),
				},
				{
					"name" : "first_prev_button", "type" : "button",
					"x" : 230+20, "y" : 315,

					"default_image" : LOCALE_PATH + "private_first_prev_btn_01.sub",
					"over_image" 	: LOCALE_PATH + "private_first_prev_btn_02.sub",
					"down_image" 	: LOCALE_PATH + "private_first_prev_btn_01.sub",
				},
				{
					"name" : "prev_button", "type" : "button",
					"x" : 260+20, "y" : 315,

					"default_image" : LOCALE_PATH + "private_prev_btn_01.sub",
					"over_image" 	: LOCALE_PATH + "private_prev_btn_02.sub",
					"down_image" 	: LOCALE_PATH + "private_prev_btn_01.sub",
				},
				{
					"name" : "page1_button", "type" : "button",
					"x" : 275+30, "y" : 313,

					"text" : "10000",

					"default_image" : LOCALE_PATH + "private_pagenumber_00.sub",
					"over_image" 	: LOCALE_PATH + "private_pagenumber_01.sub",
					"down_image" 	: LOCALE_PATH + "private_pagenumber_02.sub",
				},
				{
					"name" : "page2_button", "type" : "button",
					"x" : 310+30, "y" : 313,

					"text" : "2000",

					"default_image" : LOCALE_PATH + "private_pagenumber_00.sub",
					"over_image" 	: LOCALE_PATH + "private_pagenumber_01.sub",
					"down_image" 	: LOCALE_PATH + "private_pagenumber_02.sub",
				},
				{
					"name" : "page3_button", "type" : "button",
					"x" : 345+30, "y" : 313,
					
					"text" : "300",

					"default_image" : LOCALE_PATH + "private_pagenumber_00.sub",
					"over_image" 	: LOCALE_PATH + "private_pagenumber_01.sub",
					"down_image" 	: LOCALE_PATH + "private_pagenumber_02.sub",
				},
				{
					"name" : "page4_button", "type" : "button",
					"x" : 380+30, "y" : 313,

					"text" : "4",

					"default_image" : LOCALE_PATH + "private_pagenumber_00.sub",
					"over_image" 	: LOCALE_PATH + "private_pagenumber_01.sub",
					"down_image" 	: LOCALE_PATH + "private_pagenumber_02.sub",
				},
				{
					"name" : "page5_button", "type" : "button",
					"x" : 415+30, "y" : 313,

					"text" : "50000",

					"default_image" : LOCALE_PATH + "private_pagenumber_00.sub",
					"over_image" 	: LOCALE_PATH + "private_pagenumber_01.sub",
					"down_image" 	: LOCALE_PATH + "private_pagenumber_02.sub",
				},
				{
					"name" : "next_button", "type" : "button",
					"x" : 453+40, "y" : 315,

					"default_image" : LOCALE_PATH + "private_next_btn_01.sub",
					"over_image" 	: LOCALE_PATH + "private_next_btn_02.sub",
					"down_image" 	: LOCALE_PATH + "private_next_btn_01.sub",
				},
				{
					"name" : "last_next_button", "type" : "button",
					"x" : 483+40, "y" : 315,

					"default_image" : LOCALE_PATH + "private_last_next_btn_01.sub",
					"over_image" 	: LOCALE_PATH + "private_last_next_btn_02.sub",
					"down_image" 	: LOCALE_PATH + "private_last_next_btn_01.sub",
				},
			),
		},
	),
}
