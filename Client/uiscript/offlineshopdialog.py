import app
import uiScriptLocale

MAIN_PATH = "d:/ymir work/ui/offshop/"
BOARD_WIDTH = 350
BOARD_HEIGHT = 358

window = {
	"name" : "OfflineShopDialog",

	"x" : SCREEN_WIDTH - 400,
	"y" : 10,

	"style" : ("movable", "float",),

	"width" : BOARD_WIDTH,
	"height" : BOARD_HEIGHT,

	"children" :
	(
		{
			"name" : "board",
			"type" : "new_board",
			"style" : ("attach",),

			"x" : 0,
			"y" : 0,

			"width" : BOARD_WIDTH,
			"height" : BOARD_HEIGHT,

			"children" :
			(
				{
					"name" : "dragon_background",
					"type" : "expanded_image",
					"style" : ("ltr",),
					"x" : BOARD_WIDTH - 345,
					"y" : 0,
					"image" : MAIN_PATH + "create_shop/create_shop_dragon_bg.tga"
				},
				## Title
				{
					"name" : "TitleBar",
					"type" : "titlebar",
					"style" : ("attach",),

					"x" : 8,
					"y" : 8,

					"width" : 350 - (184 - 169),
					"color" : "gray",

					"children" :
					(
						{ "name":"TitleName", "type":"text", "x":0, "y":4, "text":uiScriptLocale.SHOP_TITLE, "horizontal_align":"center", "text_horizontal_align":"center" },
					),
				},
				## Name
				{
					"name" : "NameSlot",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 215,
					"y" : 35,
					
					"horizontal_align" : "right",
					
					"image" : MAIN_PATH + "shop_name_slotbar.tga",
					"children" :
					(
						{
							"name" : "shop_name_text",
							"type" : "text",
							
							"x" : -117,
							"y" : 2,
							
							"text" : uiScriptLocale.OFFLINE_SHOP_CREATE_BASE_TEXT,
						},
						{
							"name" : "NameLine",
							"type" : "text",
							"x" : 6,
							"y" : 3,
							"width" : 160,
							"height" : 20,
							"input_limit" : 20,
							"text" : "",
						},
					),
				},
				## Item Slot
				{
					"name" : "ItemSlot",
					"type" : "grid_table",

					"x" : 15,
					"y" : 34+26,

					"start_index" : 0,
					"x_count" : 10,
					"y_count" : 8,
					"x_step" : 32,
					"y_step" : 32,

					"image" : "d:/ymir work/ui/public/Slot_Base.sub",
				},

				## View Count
				{
					"name": "ViewCount",
					"type": "button",

					"x": 0,
					"y" : 295 + 26,

					"text": "",
					
					"horizontal_align" : "center",
					
					"default_image": "d:/ymir work/ui/public/parameter_slot_04.sub",
					"over_image": "d:/ymir work/ui/public/parameter_slot_04.sub",
					"down_image": "d:/ymir work/ui/public/parameter_slot_04.sub",
				},
			),
		},
	),
}