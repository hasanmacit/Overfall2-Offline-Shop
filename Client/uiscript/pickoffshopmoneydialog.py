import app
import uiScriptLocale

MAIN_PATH = "d:/ymir work/ui/offshop/"

window = {
	"name" : "PickMoneyDialog",

	"x" : 100,
	"y" : 100,

	"style" : ("movable", "float",),

	"width" : 320,
	"height" : 93,

	"children" :
	(
		{
			"name" : "board",
			"type" : "new_board_with_titlebar",

			"x" : 0,
			"y" : 0,

			"width" : 320,
			"height" : 93,
			"title" : uiScriptLocale.PICK_MONEY_TITLE,

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
				## Money Slot
				{
					"name" : "money_slot",
					"type" : "image",

					"x" : 20,
					"y" : 36,

					"image" : "d:/ymir work/ui/public/parameter_slot_05.sub",

					"children" :
					(
						{
							"name" : "money_value",
							"type" : "editline",

							"x" : 3,
							"y" : 2,

							"width" : 60,
							"height" : 18,

							"input_limit" : 15,

							"text" : "1",
						},
					),
				},
				{
					"name" : "max_value",
					"type" : "text",

					"x" : 20 + 130 + 10,
					"y" : 38,

					"text" : "/ 999999",
				},

				## Button
				{
					"name" : "accept_button",
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
					"name" : "cancel_button",
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