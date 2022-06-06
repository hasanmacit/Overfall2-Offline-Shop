import app
import uiScriptLocale
import localeInfo

MAIN_PATH = "d:/ymir work/ui/offshop/"

window = {
	"name" : "NewInputDialog",

	"x" : 0,
	"y" : 0,

	"style" : ("movable", "float",),

	"width" : 230,
	"height" : 143,
	"children" :
	(
		{
			"name" : "board",
			"type" : "new_board_with_titlebar",

			"x" : 0,
			"y" : 0,

			"width" : 230,
			"height" : 143,

			"title" : "",

			"children" :
			(
				{
					"name" : "base_image",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 10,
					"y" : 32,
					
					"image" : MAIN_PATH + "input_money_bg.tga",
				},
				## Input Slot
				{
					"name" : "InputSlot",
					"type" : "slotbar",

					"x" : 0,
					"y" : 34+7,
					"width" : 90,
					"height" : 18,
					"horizontal_align" : "center",

					"children" :
					(
						{
							"name" : "InputValue",
							"type" : "editline",

							"x" : 3,
							"y" : 3,

							"width" : 90,
							"height" : 18,

							"input_limit" : 12,
						},
					),
				},

				## Input Slot
				{
					"name" : "MoneyValue",
					"type" : "text",

					"x" : 0,
					"y" : 59+7,
					"text" : "999999999",
					"text_horizontal_align" : "center",
					"horizontal_align" : "center",
				},
				{
					"name" : "MoneyFeeValue",
					"type" : "text",

					"x" : 0,
					"y" : 79+7,
					"text" : "999999999",
					"text_horizontal_align" : "center",
					"horizontal_align" : "center",
				},

				## Button
				{
					"name" : "AcceptButton",
					"type" : "button",

					"x" : - 72 + 30,
					"y" : 98+7,
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
					"y" : 98+7,
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