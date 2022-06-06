import uiScriptLocale

MAIN_PATH = "d:/ymir work/ui/offshop/"

window = {
	"name" : "InputDialog",

	"x" : 0,
	"y" : 0,

	"style" : ("movable", "float",),

	"width" : 320,
	"height" : 93,

	"children" :
	(
		{
			"name" : "Board",
			"type" : "new_board_with_titlebar",

			"x" : 0,
			"y" : 0,

			"width" : 320,
			"height" : 93,

			"title" : "",

			"children" :
			(
				{
					"name" : "base_image",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 10,
					"y" : 32,
					
					"image" : MAIN_PATH + "pick_money_bg.tga",
				},
				## Input Slot
				{
					"name" : "InputSlot",
					"type" : "expanded_image",
					"style" : ("ltr",),

					"x" : 0,
					"y" : 36,
					"image" : MAIN_PATH + "shop_name_slotbar.tga",
					"horizontal_align" : "center",

					"children" :
					(
						{
							"name" : "InputValue",
							"type" : "editline",

							"x" : 6,
							"y" : 3,

							"width" : 180,
							"height" : 18,

							"input_limit" : 32,
						},
					),
				},

				## Button
				{
					"name" : "AcceptButton",
					"type" : "button",

					"x" : - 72 + 30,
					"y" : 58,
					"horizontal_align" : "center",

					"text" : uiScriptLocale.OK,
					
					"text_x" : 0,
					"text_y" : -1,
					
					"default_image" : MAIN_PATH + "buttons/remove_yang_norm.tga",
					"over_image" : MAIN_PATH + "buttons/remove_yang_hover.tga",
					"down_image" : MAIN_PATH + "buttons/remove_yang_down.tga",
				},
				{
					"name" : "CancelButton",
					"type" : "button",

					"x" : 10 + 30,
					"y" : 58,
					"horizontal_align" : "center",

					"text" : uiScriptLocale.CANCEL,
					
					"text_x" : 0,
					"text_y" : -1,
					
					"default_image" : MAIN_PATH + "buttons/remove_yang_norm.tga",
					"over_image" : MAIN_PATH + "buttons/remove_yang_hover.tga",
					"down_image" : MAIN_PATH + "buttons/remove_yang_down.tga",
				},
			),
		},
	),
}