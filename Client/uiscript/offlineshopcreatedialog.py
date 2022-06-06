import app
import uiScriptLocale

MAIN_PATH = "d:/ymir work/ui/offshop/"
BOARD_WIDTH = 350
BOARD_HEIGHT = 442

window = {
	"name" : "OfflineShopCreateDialog",

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
					"image" : MAIN_PATH + "create_shop/off_shop_dragon_bg.tga"
				},
				{
					"name" : "TitleBar",
					"type" : "titlebar_without_button",
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
							"y" : 4,
							
							"horizontal_align" : "center",

							"text" : uiScriptLocale.OFFLINE_SHOP_CREATE_SHOP,

							"text_horizontal_align" : "center"
						},
					],
				},
				{
					"name" : "shop_name_bar",
					"type" : "expanded_image",
					"style" : ("ltr",),

					"x" : 215,
					"y" : 40,
					
					"horizontal_align" : "right",
					
					"image" : MAIN_PATH + "shop_name_slotbar.tga",
					"children" :
					[
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
							"name" : "shop_name_el",
							"type" : "editline",
							"x" : 35,
							"y" : 3,

							"input_limit" : 32,

							"width" : 150,
							"height" : 20,
						},
					],
				},
				{
					"name" : "base_image",
					"type" : "expanded_image",
					"style" : ("ltr",),

					"x" : 0,
					"y" : 65,
					
					"horizontal_align" : "center",
					
					"image" : MAIN_PATH + "create_shop/bg_rect.tga",
					"children" :
					[
						{
							"name" : "shop_type_window",
							"type" : "window",
							"style" : ("attach",),
							
							"x" : 0,
							"y" : 10,
							
							"width" : 319,
							"height" : 15,
							
							"children" :
							[
								{
									"name" : "prev_style_btn",
									"type" : "button",
									
									"x" : -95,
									"y" : 5,
									
									"horizontal_align" : "center",
									
									"default_image" : MAIN_PATH + "create_shop/prev_but_norm.tga",
									"over_image" : MAIN_PATH + "create_shop/prev_but_hover.tga",
									"down_image" : MAIN_PATH +  "create_shop/prev_but_down.tga",
								},
								{
									"name" : "base_shop_type_image",
									"type" : "expanded_image",
									"style" : ("ltr",),

									"x" : 0,
									"y" : 0,
									
									"horizontal_align" : "center",
									
									"image" : "d:/ymir work/ui/public/select_btn_03.sub",
									"children" :
									[
										{
											"name" : "shop_type_text",
											"type" : "text",
											
											"x" : 0,
											"y" : 0,
											
											"horizontal_align" : "center",
											"vertical_align" : "center",
											"text_horizontal_align" : "center",
											"text_vertical_align" : "center",
											
											"text" : "",
										},
									],
								},
								{
									"name" : "next_style_btn",
									"type" : "button",
									
									"x" : 95,
									"y" : 5,
									
									"horizontal_align" : "center",

									"default_image" : MAIN_PATH + "create_shop/next_but_norm.tga",
									"over_image" : MAIN_PATH + "create_shop/next_but_hover.tga",
									"down_image" : MAIN_PATH +  "create_shop/next_but_down.tga",
								},
							],
						},
						{
							"name" : "base_shop_type_image",
							"type" : "expanded_image",
							"style" : ("ltr",),

							"x" : 0,
							"y" : 42,
							
							"horizontal_align" : "center",
							
							"image" : MAIN_PATH + "create_shop/model_preview_header.tga",
							"children" :
							[
								{
									"name" : "shop_type_block_state",
									"type" : "text",
									
									"x" : 0,
									"y" : 0,
									
									"horizontal_align" : "center",
									"vertical_align" : "center",
									"text_horizontal_align" : "center",
									"text_vertical_align" : "center",
									
									"text" : "",
								},
							],
						},
					],
				},

				{
					"name" : "base_board_image",
					"type" : "expanded_image",
					"style" : ("ltr",),

					"x" : 0,
					"y" : 65,
					
					"horizontal_align" : "center",
					
					"image" : MAIN_PATH + "create_shop/bg_rect.tga",
					"children" :
					[
						{
							"name" : "shop_board_type_window",
							"type" : "window",
							"style" : ("attach",),
							
							"x" : 0,
							"y" : 10,
							
							"width" : 319,
							"height" : 15,
							
							"children" :
							[
								{
									"name" : "prev_board_style_btn",
									"type" : "button",
									
									"x" : -95,
									"y" : 5,
									
									"horizontal_align" : "center",
									
									"default_image" : MAIN_PATH + "create_shop/prev_but_norm.tga",
									"over_image" : MAIN_PATH + "create_shop/prev_but_hover.tga",
									"down_image" : MAIN_PATH +  "create_shop/prev_but_down.tga",
								},
								{
									"name" : "base_board_shop_type_image",
									"type" : "expanded_image",
									"style" : ("ltr",),

									"x" : 0,
									"y" : 0,
									
									"horizontal_align" : "center",
									
									"image" : "d:/ymir work/ui/public/select_btn_03.sub",
									"children" :
									[
										{
											"name" : "shop_board_type_text",
											"type" : "text",
											
											"x" : 0,
											"y" : 0,
											
											"horizontal_align" : "center",
											"vertical_align" : "center",
											"text_horizontal_align" : "center",
											"text_vertical_align" : "center",
											
											"text" : "",
										},
									],
								},
								{
									"name" : "next_board_style_btn",
									"type" : "button",
									
									"x" : 95,
									"y" : 5,
									
									"horizontal_align" : "center",

									"default_image" : MAIN_PATH + "create_shop/next_but_norm.tga",
									"over_image" : MAIN_PATH + "create_shop/next_but_hover.tga",
									"down_image" : MAIN_PATH +  "create_shop/next_but_down.tga",
								},
							],
						},
						{
							"name" : "base_shop_board_type_image",
							"type" : "expanded_image",
							"style" : ("ltr",),

							"x" : 0,
							"y" : 42,
							
							"horizontal_align" : "center",
							
							"image" : MAIN_PATH + "create_shop/model_preview_header.tga",
							"children" :
							[
								{
									"name" : "shop_board_type_block_state",
									"type" : "text",
									
									"x" : 0,
									"y" : 0,
									
									"horizontal_align" : "center",
									"vertical_align" : "center",
									"text_horizontal_align" : "center",
									"text_vertical_align" : "center",
									
									"text" : "",
								},
							],
						},
					],
				},


				{
					"name" : "common_footer",
					"type" : "window",
					"style" : ("attach",),
					
					"x" : 16,
					"y" : 350,
					
					"width" : BOARD_WIDTH - 30,
					"height" : 51,
					
					"children" :
					[
						{
							"name" : "footer_base_image",
							"type" : "expanded_image",
							"style" : ("ltr",),
							
							"x" : 0,
							"y" : 0,
							
							"image" : MAIN_PATH + "create_shop/footer_create_shop.tga",
						},
						{
							"name" : "shop_time_create_base",
							"type" : "text",
							
							"x" : 5,
							"y" : 30,
							
							"text" : uiScriptLocale.OFFLINE_SHOP_CREATE_SHOP_TIME,
							"children" :
							[
								{
									"name" : "shop_time_create_value",
									"type" : "text",
									
									"x" : 0,
									"y" : 0,
									
									"text" : "",
								},
							],
						},
						{
							"name" : "shop_cost_create_base",
							"type" : "text",
							
							"x" : 5,
							"y" : 50,
							
							"text" : uiScriptLocale.OFFLINE_SHOP_CREATE_SHOP_PRICE,
							"children" :
							[
								{
									"name" : "shop_cost_create_value",
									"type" : "text",
									
									"x" : 0,
									"y" : 0,
									
									"text" : "",
								},
							],
						},
						{
							"name" : "premium_logo",
							"type" : "expanded_image",
							"style" : ("ltr",),
							
							"x" : 38,
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
					],
				},
				{
					"name" : "create_shop_button",
					"type" : "button",

					"x" : 236,
					"y" : 361,
					
					"text" : uiScriptLocale.OFFLINE_SHOP_CREATE_SHOP_BUTTON,

					"text_x" : 0,
					"text_y" : -1,
					
					"default_image" : MAIN_PATH + "create_shop/button_norm.tga",
					"over_image" : MAIN_PATH + "create_shop/button_hover.tga",
					"down_image" : MAIN_PATH + "create_shop/button_down.tga",
				},
				{
					"name" : "exit_shop_create_button",
					"type" : "button",
					
					"x" : 236,
					"y" : 392,
					
					"text" : uiScriptLocale.OFFLINE_SHOP_EXIT_CREATE_SHOP_BUTTON,

					"text_x" : 0,
					"text_y" : -1,
					
					"default_image" : MAIN_PATH + "create_shop/button_norm.tga",
					"over_image" : MAIN_PATH + "create_shop/button_hover.tga",
					"down_image" : MAIN_PATH + "create_shop/button_down.tga",
				},
				{
					"name" : "page_model_button",
					"type" : "radio_button",
					
					"x" : 270 - 21 - 26,
					"y" : 213+107,
					
					"default_image" : MAIN_PATH + "buttons_pagination/but_pag_1_norm.tga",
					"over_image" : MAIN_PATH + "buttons_pagination/but_pag_1_hover.tga",
					"down_image" : MAIN_PATH + "buttons_pagination/but_pag_1_down.tga",
				},
				{
					"name" : "page_board_button",
					"type" : "radio_button",
					
					"x" : 270 - 21,
					"y" : 213+107,
					
					"default_image" : MAIN_PATH + "buttons_pagination/but_pag_2_norm.tga",
					"over_image" : MAIN_PATH + "buttons_pagination/but_pag_2_hover.tga",
					"down_image" : MAIN_PATH + "buttons_pagination/but_pag_2_down.tga",
				},
			],
		},
	],
}
