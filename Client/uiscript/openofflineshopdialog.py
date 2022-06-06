import app
import uiScriptLocale

BOARD_WIDTH = 180
BOARD_HEIGHT = 118

BOARD_TITLE_WIDTH_GAP = 7.5
BOARD_TITLE_HEIGHT_GAP = 28
ROOT = "d:/ymir work/ui/"

FONT_COLOR1 = 0xFFD4D4D4
FONT_COLOR2 = 0xFFDDCEC3

window = {
	"name" : "OpenOfflineShopDialog",
	"style" : ("movable", "float",),

	"x" : SCREEN_WIDTH / 2 - BOARD_WIDTH / 2,
	"y" : SCREEN_HEIGHT / 2 - BOARD_HEIGHT / 2,

	"width" : BOARD_WIDTH,
	"height" : BOARD_HEIGHT,

	"children" :
	(
		{
			"name" : "board",
			"type" : "board",
			"style" : ("attach",),

			"x" : 0,
			"y" : 0,

			"width" : BOARD_WIDTH,
			"height" : BOARD_HEIGHT,

			"children" :
			(
				## Title
				{
					"name" : "title_bar",
					"type" : "titlebar",
					"style" : ("attach",),

					"x" : 8,
					"y" : 8,

					"width" : BOARD_WIDTH - 14,
					"color" : "gray",

					"children" :
					(
						{
							"name" : "TitleName",
							"type":"text",

							"x" : 84,
							"y" : 4,

							"text" : uiScriptLocale.OFFLINE_SHOP_OPEN_TITLE,

							"text_horizontal_align" : "center"
						},
					),
				},
				{
					"name" : "required_item_window",
					"type" : "expanded_image",
					"style" : ("attach",),

					"x" : BOARD_TITLE_WIDTH_GAP + 2.5,
					"y" : BOARD_TITLE_HEIGHT_GAP + 5,

					"width" : 32,
					"height" : 32,

					"image" : ROOT + "minigame/fish_event/" + "fish_special_slot.sub",

					"children" :
					(
						## Special Item Slot
						{
							"name" : "required_item_slot",
							"type" : "slot",

							"x" : 7,
							"y" : 7,
							"width" : 32,
							"height" : 32,

							"image" : "d:/ymir work/ui/public/Slot_Base.sub",
							"slot" : (
								{ "index" : 0, "x" : 0, "y" : 0, "width" : 32, "height" : 32 },
							),
						},
					),
				},

				## money
				{
					"name" : "money_icon",
					"type" : "image",

					"x" : BOARD_TITLE_WIDTH_GAP + (67 - 18),
					"y" : BOARD_TITLE_HEIGHT_GAP + 30,

					"vertical_align" : "top",

					"image" : ROOT + "game/windows/" + "money_icon.sub",
				},
				{
					"name" : "money_text_window",
					"type" : "button",

					"x" : BOARD_TITLE_WIDTH_GAP + 67,
					"y" : BOARD_TITLE_HEIGHT_GAP + 30,

					"vertical_align" : "top",

					"default_image" : ROOT + "public/" + "gold_slot.sub",
					"over_image" : ROOT + "public/" + "gold_slot.sub",
					"down_image" : ROOT + "public/" + "gold_slot.sub",

					"children" :
					(
						{
							"name" : "money_text",
							"type" : "text",

							"x" : 3,
							"y" : 2.5,

							"horizontal_align" : "right",
							"text_horizontal_align" : "right",

							"text" : "999.999.999",
						},
					),
				},
				##-
				{
					"name" : "ok_button",
					"type" : "button",

					"x" : -38,
					"y" : 34,

					"width" : 610,
					"height" : 21,

					"vertical_align" : "bottom",
					"horizontal_align" : "center",

					"default_image" : ROOT + "public/" + "AcceptButton00.sub",
					"over_image" : ROOT + "public/" + "AcceptButton01.sub",
					"down_image" : ROOT + "public/" + "AcceptButton02.sub",
				},
				{
					"name" : "cancel_button",
					"type" : "button",

					"x" : 38,
					"y" : 34,

					"width" : 610,
					"height" : 21,

					"vertical_align" : "bottom",
					"horizontal_align" : "center",

					"default_image" : ROOT + "public/" + "CancleButton00.sub",
					"over_image" : ROOT + "public/" + "CancleButton01.sub",
					"down_image" : ROOT + "public/" + "CancleButton02.sub",
				},
				{
					"name" : "tooltip_button",
					"type" : "button",

					"x" : BOARD_TITLE_WIDTH_GAP + 1.3,
					"y" : BOARD_TITLE_HEIGHT_GAP + 5,

					"default_image" : ROOT + "pattern/" + "q_mark_01.tga",
					"over_image" : ROOT + "pattern/" + "q_mark_02.tga",
					"down_image" : ROOT + "pattern/" + "q_mark_01.tga",
				},
				## time
				{
					"name" : "time_icon",
					"type" : "image",

					"x" : BOARD_TITLE_WIDTH_GAP + (67 - 18),
					"y" : BOARD_TITLE_HEIGHT_GAP + (28 - 20),

					"vertical_align" : "top",

					"image" : ROOT + "game/premiumshop/" + "close_time_icon.sub",
				},
				{
					"name" : "time_select_text_window",
					"type" : "button",

					"x" : BOARD_TITLE_WIDTH_GAP + 67,
					"y" : BOARD_TITLE_HEIGHT_GAP + (28 - 20),

					"vertical_align" : "top",

					"default_image" : ROOT + "public/" + "gold_slot.sub",
					"over_image" : ROOT + "public/" + "gold_slot.sub",
					"down_image" : ROOT + "public/" + "gold_slot.sub",

					"children" :
					(
						{
							"name" : "time_select_text",
							"type" : "text",

							"x" : 3,
							"y" : 2.5,

							"horizontal_align" : "left",
							"text_horizontal_align" : "left",

							"text" : uiScriptLocale.OFFLINE_SHOP_OPEN_TIME_1,
							"color" : FONT_COLOR1
						},
						{
							"name" : "time_select_button",
							"type" : "button",

							"x" : 18,
							"y" : 2.5,

							"horizontal_align" : "right",
							"text_horizontal_align" : "right",

							"default_image" : ROOT + "game/party_match/" + "arrow_default.sub",
							"over_image" : ROOT + "game/party_match/" + "arrow_over.sub",
							"down_image" : ROOT + "game/party_match/" + "arrow_down.sub",
						},
					),
				},
				{
					"name" : "time_select_window",
					"type" : "window",

					"x" : BOARD_TITLE_WIDTH_GAP + 67,
					"y" : BOARD_TITLE_HEIGHT_GAP + (28 - 20) + 17,

					"width" : 0,
					"height" : 0,
				},
				{
					"name" : "mouse_over_image",
					"type" : "expanded_image",
					"style" : ("not_pick",),

					"x" : 0,
					"y" : 0,
					"image" : ROOT + "game/party_match/" + "button_over.sub",
				},
			),
		},
	),
}