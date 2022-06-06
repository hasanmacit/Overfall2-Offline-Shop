import app
import item
import uiScriptLocale
import localeInfo

LOCALE_PATH = "d:/ymir work/ui/privatesearch/"
GOLD_COLOR = 0xFFFEE3AE

BOARD_WIDTH = 570
BOARD_HEIGHT = 350
LEFT_X_GAP = 13
RIGHT_X_GAP = 539
CENTER_X_GAP = 29
BOARD_EXPAND = 5

window = {
	"name" : "SalesDialog",

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

			"title" : uiScriptLocale.OFFLINE_SHOP_SALES,

			"children" :
			(
				## LeftTop
				{
					"name" : "LeftTop",
					"type" : "image",
					"x" : LEFT_X_GAP,
					"y" : 36,
					"image" : LOCALE_PATH+"private_mainboxlefttop.sub",
				},
				## RightTop
				{
					"name" : "RightTop",
					"type" : "image",
					"x" : RIGHT_X_GAP,
					"y" : 36,
					"image" : LOCALE_PATH+"private_mainboxrighttop.sub",
				},
				## LeftBottom
				{
					"name" : "LeftBottom",
					"type" : "image",
					"x" : LEFT_X_GAP,
					"y" : 320,
					"image" : LOCALE_PATH+"private_mainboxleftbottom.sub",
				},
				## RightBottom
				{
					"name" : "RightBottom",
					"type" : "image",
					"x" : RIGHT_X_GAP,
					"y" : 320,
					"image" : LOCALE_PATH+"private_mainboxrightbottom.sub",
				},
				## leftcenterImg
				{
					"name" : "leftcenterImg",
					"type" : "expanded_image",
					"x" : LEFT_X_GAP,
					"y" : 52,
					"image" : LOCALE_PATH+"private_leftcenterImg.tga",
					"rect" : (0.0, 0.0, 0, 15),
				},
				## rightcenterImg
				{
					"name" : "rightcenterImg",
					"type" : "expanded_image",
					"x" : RIGHT_X_GAP - 1,
					"y" : 52,
					"image" : LOCALE_PATH+"private_rightcenterImg.tga",
					"rect" : (0.0, 0.0, 0, 15),
				},
				## topcenterImg
				{
					"name" : "topcenterImg",
					"type" : "expanded_image",
					"x" : CENTER_X_GAP,
					"y" : 36,
					"image" : LOCALE_PATH+"private_topcenterImg.tga",
					"rect" : (0.0, 0.0, 24 + BOARD_EXPAND, 0),
				},
				## bottomcenterImg
				{
					"name" : "bottomcenterImg",
					"type" : "expanded_image",
					"x" : CENTER_X_GAP,
					"y" : 320,
					"image" : LOCALE_PATH+"private_bottomcenterImg.tga",
					"rect" : (0.0, 0.0, 24 + BOARD_EXPAND, 0),
				},
				## centerImg
				{
					"name" : "centerImg",
					"type" : "expanded_image",
					"x" : CENTER_X_GAP,
					"y" : 52,
					"image" : LOCALE_PATH+"private_centerImg.tga",
					"rect" : (0.0, 0.0, 24 + BOARD_EXPAND, 15),
				},
				## tab_menu_01
				{
					"name" : "ItemTypeImg",
					"type" : "expanded_image",
					"x" : LEFT_X_GAP + 3,
					"y" : 39,
					"width" : 10,
					"image" : "d:/ymir work/ui/tab_menu_01.tga",
					"x_scale" : 1.22,
					"y_scale" : 1.0,
					"children" :
					(
						## Text
						{ "name" : "ResultNameText1", "type" : "text", "x" : 67 - 30, "y" : 4,  "text" : uiScriptLocale.OFFLINE_SHOP_SALES_BUYER, },
						{ "name" : "ResultNameText2", "type" : "text", "x" : 207 - 15, "y" : 4, "text" : uiScriptLocale.OFFLINE_SHOP_SALES_ITEM, },
						{ "name" : "ResultNameText3", "type" : "text", "x" : 303, "y" : 4, "text" : uiScriptLocale.OFFLINE_SHOP_SALES_ITEM_COUNT, },
						{ "name" : "ResultNameText4", "type" : "text", "x" : 377 - 10, "y" : 4, "text" : uiScriptLocale.OFFLINE_SHOP_SALES_YANG, },
						{ "name" : "ResultNameText4", "type" : "text", "x" : 377+55, "y" : 4, "text" : uiScriptLocale.OFFLINE_SHOP_SALES_CHEQUE, },
						{ "name" : "ResultNameText4", "type" : "text", "x" : 377+55+50, "y" : 4, "text" : uiScriptLocale.OFFLINE_SHOP_SALES_DATE, },
					),
				},
				{
					"name" : "scrollbar",
					"type" : "scrollbar",
					"x" : BOARD_WIDTH - 12.5,
					"y" : 36,
					"size" : 100,
				},
			),
		},
	),
}