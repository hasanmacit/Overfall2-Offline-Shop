import app
import uiScriptLocale

GRID_GAP = 26
BUTTONS = 2
BUTTON_GAP = 30
BOTTOM_GAP = 23

BOARD_WIDTH = 350
BOARD_HEIGHT = 461

CATEGORY_BUTTONS_STEP = 82

MAIN_PATH = "d:/ymir work/ui/offshop/"

ORANGE_COLOR = 0xffcd7707

window = {
	"name" : "OfflineShopManagerDialog",

	"x" : SCREEN_WIDTH - 400,
	"y" : 10,

	"style" : ("movable", "float",),

	"width" : BOARD_WIDTH,
	"height" : BOARD_HEIGHT,

	"children" :
	[
		{
			"name" : "board",
			"type" : "new_board",
			"style" : ("attach",),

			"x" : 0,
			"y" : 0,

			"width" : BOARD_WIDTH,
			"height" : BOARD_HEIGHT,

			"children" :
			[
				{
					"name" : "dragon_background",
					"type" : "expanded_image",
					"style" : ("ltr",),
					"x" : BOARD_WIDTH - 345,
					"y" : 0,
					"image" : MAIN_PATH + "off_shop_dragon_bg.tga"
				},
				## Title
				{
					"name" : "TitleBar",
					"type" : "titlebar",
					"style" : ("attach",),

					"x" : 8,
					"y" : 7,

					"width" : (BOARD_WIDTH - 15),
					"color" : "gray",

					"children" :
					[
						{
							"name" : "TitleName",
							"type":"text",

							"x" : 0,
							"y" : 3,

							"text" : uiScriptLocale.MY_OFFLINE_SHOP,

							"horizontal_align" : "center",
							"text_horizontal_align" : "center",
						},
					],
				},
				{
					"name" : "common_header",
					"type" : "window",
					"style" : ("attach",),
					
					"x" : 15,
					"y" : 38,
					
					"width" : BOARD_WIDTH - 30,
					"height" : 33,
					
					"children" :
					[
						{
							"name" : "shop_cat_button",
							"type" : "radio_button",
							
							"x" : CATEGORY_BUTTONS_STEP*0,
							"y" : 0,
							
							"default_image" : MAIN_PATH + "buttons/shop_norm.tga",
							"over_image" : MAIN_PATH + "buttons/shop_hover.tga",
							"down_image" : MAIN_PATH + "buttons/shop_down.tga",
							"disable_image" : MAIN_PATH + "buttons/shop_down.tga",
						},

						{
							"name" : "history_cat_button",
							"type" : "radio_button",
							
							"x" : CATEGORY_BUTTONS_STEP*1,
							"y" : 0,
							
							"default_image" : MAIN_PATH + "buttons/history_norm.tga",
							"over_image" : MAIN_PATH + "buttons/history_hover.tga",
							"down_image" : MAIN_PATH + "buttons/history_down.tga",
							"disable_image" : MAIN_PATH + "buttons/history_down.tga",
						},

						{
							"name" : "info_cat_button",
							"type" : "radio_button",
							
							"x" : CATEGORY_BUTTONS_STEP*2,
							"y" : 0,
							
							"default_image" : MAIN_PATH + "buttons/info_norm.tga",
							"over_image" : MAIN_PATH + "buttons/info_hover.tga",
							"down_image" : MAIN_PATH + "buttons/info_down.tga",
							"disable_image" : MAIN_PATH + "buttons/info_down.tga",
						},

						{
							"name" : "search_shop_cat_button",
							"type" : "button",
							
							"x" : CATEGORY_BUTTONS_STEP*3,
							"y" : 0,
							
							"default_image" : MAIN_PATH + "buttons/search_norm.tga",
							"over_image" : MAIN_PATH + "buttons/search_hover.tga",
							"down_image" : MAIN_PATH + "buttons/search_down.tga",
							"disable_image" : MAIN_PATH + "buttons/search_down.tga",
						},
					],
				},
				{
					"name" : "shop_category_window",
					"type" : "window",
					"style" : ("attach",),
					
					"x" : 15,
					"y" : 78,
					
					"width" : BOARD_WIDTH - 30,
					"height" : 410,
					
					"children" :
					[
						{
							"name" : "ItemSlot_inv_image",
							"type" : "expanded_image",
							"style" : ("ltr",),
							
							"x" : 2,
							"y" : 5,
							
							"image" : MAIN_PATH + "background_item_slot.tga",
						},
						## Shop Location Slot
						{
							"name" : "shop_name_bar",
							"type" : "expanded_image",
							"style" : ("ltr",),

							"x" : 0,
							"y" : 4,
							
							"image" : MAIN_PATH + "shop_name_slotbar.tga",

							"children" :
							[
								{
									"name" : "ShopName",
									"type" : "text",

									"x" : 5,
									"y" : 2.5,

									"text" : "",
								},
							],
						},
						{
							"name" : "change_name_button",
							"type" : "button",
							
							"x" : 200 + 5,
							"y" : 4,
							
							"tooltip_text" : uiScriptLocale.OFFLINE_SHOP_CHANGE_SHOP_NAME,
							
							"default_image" : MAIN_PATH + "buttons/change_name_norm.tga",
							"over_image" : MAIN_PATH + "buttons/change_name_hover.tga",
							"down_image" : MAIN_PATH + "buttons/change_name_down.tga",
							"disable_image" : MAIN_PATH + "buttons/change_name_down.tga",
						},

						{
							"name" : "teleport_button",
							"type" : "button",
							
							"x" : CATEGORY_BUTTONS_STEP*3,
							"y" : 4,
							
							"text" : "TP",
							
							"tooltip_text" : uiScriptLocale.OFFLINE_SHOP_TELEPORT_TOOLTIP,
							
							"text_x" : 0,
							"text_y" : -1,
							
							"default_image" : MAIN_PATH + "buttons/button_norm.tga",
							"over_image" : MAIN_PATH + "buttons/button_hover.tga",
							"down_image" : MAIN_PATH + "buttons/button_down.tga",
							"disable_image" : MAIN_PATH + "buttons/button_down.tga",
						},
						{
							"name" : "OpenShopButton",
							"type" : "button",
							
							"x" : CATEGORY_BUTTONS_STEP*3 + 39,
							"y" : 4,
							
							"text" : uiScriptLocale.OFFLINE_SHOP_OPEN_SHOP_TEXT,
							
							"tooltip_text" : uiScriptLocale.OFFLINE_SHOP_OPEN_SHOP_TOOLTIP,

							"text_x" : 0,
							"text_y" : -1,
							
							"default_image" : MAIN_PATH + "buttons/button_norm.tga",
							"over_image" : MAIN_PATH + "buttons/button_hover.tga",
							"down_image" : MAIN_PATH + "buttons/button_down.tga",
							"disable_image" : MAIN_PATH + "buttons/button_down.tga",
						},
						{
							"name" : "DestroyShopButton",
							"type" : "button",
							
							"x" : CATEGORY_BUTTONS_STEP*3 + 39,
							"y" : 4,
							
							"text" : "X",

							"text_x" : 0,
							"text_y" : -1,
							
							"tooltip_text" : uiScriptLocale.OFFLINE_SHOP_CLOSE_SHOP_TOOLTIP,
							
							"default_image" : MAIN_PATH + "buttons/button_norm.tga",
							"over_image" : MAIN_PATH + "buttons/button_hover.tga",
							"down_image" : MAIN_PATH + "buttons/button_down.tga",
							"disable_image" : MAIN_PATH + "buttons/button_down.tga",
						},
						## Item Slot
						{
							"name" : "ItemSlot",
							"type" : "grid_table",

							"x" : -1,
							"y" : 30,

							"start_index" : 0,
							"x_count" : 10,
							"y_count" : 8,
							"x_step" : 32,
							"y_step" : 32,

							"image" : "d:/ymir work/ui/public/Slot_Base.sub",
						},
						{
							"name" : "ItemSlot_inv_image",
							"type" : "expanded_image",
							"style" : ("ltr",),
							
							"x" : -6,
							"y" : 30,
							
							"image" : MAIN_PATH + "item_slot_inv_image.tga",
						},
						{
							"name" : "line_left",
							"type" : "line",
							"x" : 0,
							"y" : 4,

							"width" : 0,
							"height" : 320,

							"color" : 0xff4a413e,
						},
						{
							"name" : "line_top",
							"type" : "line",
							"x" : 0,
							"y" : 4,

							"width" : BOARD_WIDTH - 32,
							"height" : 0,

							"color" : 0xff4a413e,
						},
						{
							"name" : "line_right",
							"type" : "line",
							"x" : 2,
							"y" : 4,

							"width" : 0,
							"height" : 320,
							
							"horizontal_align" : "right",

							"color" : 0xff4a413e,
						},
					],
				},
				{
					"name" : "history_category_window",
					"type" : "window",
					"style" : ("attach",),
					
					"x" : 15,
					"y" : 78,
					
					"width" : BOARD_WIDTH - 30,
					"height" : 410,
					
					"children" :
					[
						{
							"name" : "history_header",
							"type" : "expanded_image",
							"style" : ("ltr",),
							
							"x" : 0,
							"y" : 5,
							
							"image" : MAIN_PATH + "sales_window/header_image.tga",
							"children" :
							[
								{
									"name" : "history_selled_itens",
									"type" : "text",
									
									"x" : 7,
									"y" : -1,
									
									"vertical_align" : "center",
									"text_vertical_align" : "center",
									
									"text" : uiScriptLocale.OFFLINE_SHOP_HISTORY_ITEM_NAME,
								},
								{
									"name" : "history_time_itens",
									"type" : "text",
									
									"x" : 140,
									"y" : -1,
									
									"vertical_align" : "center",
									"text_vertical_align" : "center",
									
									"text" : uiScriptLocale.OFFLINE_SHOP_HISTORY_DATETIME,
								},
								{
									"name" : "history_price_itens",
									"type" : "text",
									
									"x" : 7,
									"y" : -1,
									
									"vertical_align" : "center",
									"horizontal_align" : "right",
									"text_horizontal_align" : "right",
									"text_vertical_align" : "center",
									
									"text" : uiScriptLocale.OFFLINE_SHOP_HISTORY_PRICE,
								},
							],
						},
						{
							"name" : "history_base_image",
							"type" : "expanded_image",
							"style" : ("ltr",),

							"x" : 0,
							"y" : 36,
							
							"image" : MAIN_PATH + "sales_window/offshop_rec_base_history.tga",
							"children" :
							[
								{
									"name" : "loading_history_window",
									"type" : "ani_image",
									"style" : ("ltr",),
									
									"widht" : 50,
									"height" : 50,
									
									"x" : -25,
									"y" : -25,
									
									"horizontal_align" : "center",
									"vertical_align" : "center",
									
									"delay" : 2,

									"images" :
									[
										"d:/ymir work/ui/search_shop/loading_gif/0.tga",
										"d:/ymir work/ui/search_shop/loading_gif/1.tga",
										"d:/ymir work/ui/search_shop/loading_gif/2.tga",
										"d:/ymir work/ui/search_shop/loading_gif/3.tga",
										"d:/ymir work/ui/search_shop/loading_gif/4.tga",
										"d:/ymir work/ui/search_shop/loading_gif/5.tga",
										"d:/ymir work/ui/search_shop/loading_gif/6.tga",
										"d:/ymir work/ui/search_shop/loading_gif/7.tga",
										"d:/ymir work/ui/search_shop/loading_gif/8.tga",
										"d:/ymir work/ui/search_shop/loading_gif/9.tga",
										"d:/ymir work/ui/search_shop/loading_gif/10.tga",
										"d:/ymir work/ui/search_shop/loading_gif/11.tga",
										"d:/ymir work/ui/search_shop/loading_gif/12.tga",
										"d:/ymir work/ui/search_shop/loading_gif/13.tga",
										"d:/ymir work/ui/search_shop/loading_gif/14.tga",
										"d:/ymir work/ui/search_shop/loading_gif/15.tga",
										"d:/ymir work/ui/search_shop/loading_gif/16.tga",
										"d:/ymir work/ui/search_shop/loading_gif/17.tga",
										"d:/ymir work/ui/search_shop/loading_gif/18.tga",
										"d:/ymir work/ui/search_shop/loading_gif/19.tga",
										"d:/ymir work/ui/search_shop/loading_gif/20.tga",
										"d:/ymir work/ui/search_shop/loading_gif/21.tga",
										"d:/ymir work/ui/search_shop/loading_gif/22.tga",
										"d:/ymir work/ui/search_shop/loading_gif/23.tga",
										"d:/ymir work/ui/search_shop/loading_gif/24.tga",
										"d:/ymir work/ui/search_shop/loading_gif/25.tga",
										"d:/ymir work/ui/search_shop/loading_gif/26.tga",
										"d:/ymir work/ui/search_shop/loading_gif/27.tga",
										"d:/ymir work/ui/search_shop/loading_gif/28.tga",
										"d:/ymir work/ui/search_shop/loading_gif/29.tga",
										"d:/ymir work/ui/search_shop/loading_gif/30.tga",
										"d:/ymir work/ui/search_shop/loading_gif/31.tga",
										"d:/ymir work/ui/search_shop/loading_gif/32.tga",
									],
								},
								{
									"name" : "history_no_found_itens",
									"type" : "text",
									
									"x" : 0,
									"y" : 0,
									
									"horizontal_align" : "center",
									"vertical_align" : "center",
									"text_horizontal_align" : "center",
									"text_vertical_align" : "center",
									
									"text" : uiScriptLocale.OFFLINE_SHOP_HISTORY_NO_VALUES,
								},
							],
						},
						{
							"name" : "history_scrollbar",
							"type" : "new_scrollbar",

							"x" : 5,
							"y" : 35-11,
							"size" : 256+32,
							
							"horizontal_align" : "right",
						},
					],
				},
				{
					"name" : "info_category_window",
					"type" : "window",
					"style" : ("attach",),
					
					"x" : 15,
					"y" : 78,
					
					"width" : BOARD_WIDTH - 30,
					"height" : 410,
					
					"children" :
					[
						{
							"name" : "info_base_text_image",
							"type" : "expanded_image",
							"style" : ("ltr",),

							"x" : 0,
							"y" : 5,
							
							"image" : MAIN_PATH + "offshop_rec_base.tga",
							"children" :
							[
								{
									"name" : "info_base_window",
									"type" : "expanded_image",
									"style" : ("ltr",),
									
									"x" : 0,
									"y" : 0,
									
									"image" : MAIN_PATH + "info_shop_base.tga",
									"children" :
									[
										{
											"name" : "shop_location_value",
											"type" : "text",
											
											"x" : -99,
											"y" : -45,
											
											
											"vertical_align" : "center",
											"horizontal_align" : "center",
											"text_horizontal_align" : "center",
											"text_vertical_align_align" : "center",
											
											"text" : "",
										},
										{
											"name" : "shop_channel_value",
											"type" : "text",
											
											"x" : 0,
											"y" : -45,
											
											
											"vertical_align" : "center",
											"horizontal_align" : "center",
											"text_horizontal_align" : "center",
											"text_vertical_align_align" : "center",
											
											"text" : "",
										},
										{
											"name" : "shop_max_time_value",
											"type" : "text",
											
											"x" : 99,
											"y" : -45,
											
											
											"vertical_align" : "center",
											"horizontal_align" : "center",
											"text_horizontal_align" : "center",
											"text_vertical_align_align" : "center",
											
											"text" : "",
										},
										{
											"name" : "shop_visual_value",
											"type" : "text",
											
											"x" : -99,
											"y" : 83,
											
											
											"vertical_align" : "center",
											"horizontal_align" : "center",
											"text_horizontal_align" : "center",
											"text_vertical_align_align" : "center",
											
											"text" : "",
										},
										{
											"name" : "shop_yang_value",
											"type" : "text",
											
											"x" : 0,
											"y" : 83,
											
											
											"vertical_align" : "center",
											"horizontal_align" : "center",
											"text_horizontal_align" : "center",
											"text_vertical_align_align" : "center",
											
											"text" : "",
										},
										{
											"name" : "shop_quant_value",
											"type" : "text",
											
											"x" : 99,
											"y" : 83,
											
											
											"vertical_align" : "center",
											"horizontal_align" : "center",
											"text_horizontal_align" : "center",
											"text_vertical_align_align" : "center",
											
											"text" : "",
										},
									],
								},
								{
									"name" : "no_info_avaible_msg",
									"type" : "text",
									
									"x" : 0,
									"y" : 0,
									
									"horizontal_align" : "center",
									"vertical_align" : "center",
									"text_horizontal_align" : "center",
									"text_vertical_align" : "center",
									
									"text" : uiScriptLocale.OFFLINE_SHOP_HAS_CLOSED_MSG,
								},
							],
						},
					],
				},
				{
					"name" : "common_footer",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 15,
					"y" : 92,
					
					"vertical_align" : "bottom",
					
					"image" : MAIN_PATH + "footer_base.tga",
					
					"children" :
					[
						{
							"name" : "clock_remove_down",
							"type" : "expanded_image",
							"style" : ("ltr",),
							"x" : 33,
							"y" : 23,
							
							"image" : MAIN_PATH + "footer/clock_remove.tga"
						},
						{
							"name" : "clock_base",
							"type" : "expanded_image",
							"style" : ("ltr",),
							"x" : 29,
							"y" : 9,
							
							"image" : MAIN_PATH + "footer/clock_up.tga"
						},
						{
							"name" : "premium_logo",
							"type" : "expanded_image",
							"style" : ("ltr",),
							
							"x" : 142,
							"y" : 7,
							
							"image" : "d:/ymir work/ui/overfall2_mini_logo.tga",
							"children" :
							[
								{
									"name" : "overfall2_premium_text",
									"type" : "text",
									
									"x" : 23,
									"y" : 0,
									
									"text" : uiScriptLocale.NEWPRIVATE_SHOP_SEARCH_PREMIUM,
								},
								{
									"name"  : "overfall2_premium",
									"type"  : "expanded_image",
									"style" : ("ltr",),
									
									"x" : 118,
									"y" : 0,
									
									"image" : "d:/ymir work/ui/pattern/visible_mark_01.tga",
								},
							],
						},
						## Print
						{
							"name" : "Money",
							"type" : "text",

							"x" : 233,
							"y" : 34,

							"text_horizontal_align" : "right",

							"text" : "0",
						},
						{
							"name" : "money_button",
							"type" : "button",

							"x" : 240,
							"y" : 30,
							
							"text" : uiScriptLocale.OFFLINE_SHOP_REMOVE_YANG,

							"text_x" : 0,
							"text_y" : -1,
							
							"default_image" : MAIN_PATH + "buttons/remove_yang_norm.tga",
							"over_image" : MAIN_PATH + "buttons/remove_yang_hover.tga",
							"down_image" : MAIN_PATH + "buttons/remove_yang_down.tga",
						},
						{
							"name" : "text_time_base",
							"type" : "text",
							
							"x" : 111,
							"y" : 54,
							
							"text" : uiScriptLocale.OFFLINE_SHOP_LEFT_TIME_BASE_TEXT,
							"children" :
							[
								{
									"name" : "left_shop_time_text",
									"type" : "text",
									
									"x" : 0,
									"y" : 0,
									
									"text" : "",
								},
							],
						},
					],
				},
			],
		},
	],
}