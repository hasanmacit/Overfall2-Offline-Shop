import app
import uiScriptLocale

MAIN_PATH = "d:/ymir work/ui/offshop/"
BOARD_WIDTH = 350
BOARD_HEIGHT = 358

window = {
	"name" : "OfflineShopBuilder",

	"x" : 0,
	"y" : 0,

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
						{ "name":"TitleName", "type":"text", "x":0, "y":4, "text":uiScriptLocale.PRIVATE_SHOP_TITLE, "horizontal_align":"center", "text_horizontal_align":"center" },
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
							"name" : "icon_write",
							"type" : "expanded_image",
							"style" : ("ltr",),
							
							"x" : 3,
							"y" : 0,
							
							"image" : "icon/tip_images/msg_icon.tga",
						},
						{
							"name" : "NameLine",
							"type" : "text",
							"x" : 35,
							"y" : 3,
							"width" : 160,
							"height" : 20,
							"input_limit" : 32,
							"text" : "",
						},
					),
				},

				## Item Slot
				{
					"name" : "ItemSlot",
					"type" : "grid_table",

					"x" : 15,
					"y" : 34 + 26,

					"start_index" : 0,
					"x_count" : 10,
					"y_count" : 8,
					"x_step" : 32,
					"y_step" : 32,

					"image" : "d:/ymir work/ui/public/Slot_Base.sub",
				},

				## Ok
				{
					"name" : "OkButton",
					"type" : "button",

					"x" : (BOARD_WIDTH/2) - 94 - 5,
					"y" : 295 + 26,

					"width" : 61,
					"height" : 21,

					"text" : uiScriptLocale.OFFLINE_SHOP_CREATE_SHOP_BUTTON,

					"default_image" : MAIN_PATH + "create_shop/button_norm.tga",
					"over_image" : MAIN_PATH + "create_shop/button_hover.tga",
					"down_image" : MAIN_PATH + "create_shop/button_down.tga",
				},

				## Close
				{
					"name" : "CloseButton",
					"type" : "button",

					"x" : (BOARD_WIDTH/2) + 5,
					"y" : 295 + 26,

					"width" : 61,
					"height" : 21,

					"text" : uiScriptLocale.OFFLINE_SHOP_EXIT_CREATE_SHOP_BUTTON,

					"default_image" : MAIN_PATH + "create_shop/button_norm.tga",
					"over_image" : MAIN_PATH + "create_shop/button_hover.tga",
					"down_image" : MAIN_PATH + "create_shop/button_down.tga",
				},
			),
		},
	),
}