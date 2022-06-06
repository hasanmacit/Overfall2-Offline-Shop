import app
import item
import uiScriptLocale
import localeInfo

MAIN_PATH = "d:/ymir work/ui/search_shop/"

BOARD_WIDTH = 810
BOARD_HEIGHT = 555

TOP_LINE = 66 #Linha onde comeca o background da pesquisa, etc

window = {
	"name" : "PrivateShopSearchDialog",

	"x" : 0,
	"y" : 0,

	"style" : ("movable", "float", "remove_limit", ),

	"width" : BOARD_WIDTH,
	"height" : BOARD_HEIGHT,

	"children" :
	[
		{
			"name" : "board",
			"type" : "new_board_with_titlebar",

			"x" : 0,
			"y" : 0,

			"width" : BOARD_WIDTH,
			"height" : BOARD_HEIGHT,
			
			"title" : uiScriptLocale.PRIVATESHOPSEARCH_SEARCH_BAR,
		
			"children" :
			[
				########### Left side window
				{
					"name" : "buttons_filter_bg",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 18,
					"y" : TOP_LINE,
					
					"image" : MAIN_PATH + "buttons_filter_bg.tga",
				},
				{
					"name" : "bg_inv",
					"type" : "expanded_image",
					"style" : ("attach",),
					
					"x" : 18,
					"y" : 545 - 29,
					
					"image" : MAIN_PATH + "bg_inv.tga",
				},
				{
					"name" : "bg_inv1",
					"type" : "expanded_image",
					"style" : ("attach",),
					
					"x" : 18,
					"y" : 43,
					
					"image" : MAIN_PATH + "bg_inv.tga",
				},
				
				{	#Search bar content
					"name" : "search_bar_base",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 18,
					"y" : 35,
					
					"image" : MAIN_PATH + "left_side/search_bar.tga",
					"children" :
					[
						{
							"name" : "search_button",
							"type" : "button",
							
							"x" : 5,
							"y" : 3, 
							
							"default_image" : MAIN_PATH + "search_editline/normal.tga",
							"over_image" : MAIN_PATH + "search_editline/hover.tga",
							"down_image" : MAIN_PATH + "search_editline/press.tga",
							"children" :
							[
								{
									"name" : "sbutton_separtor",
									"type" : "expanded_image",
									"style" : ("ltr",),
									
									"x" : 20,
									"y" : -3,
									
									"image" : MAIN_PATH + "search_editline/separator.tga",
								},
							],
						},
						{
							"name" : "search_item_editline",
							"type" : "editline",
							
							"x" : 35,
							"y" : 5,

							"width" : 177,
							"height" : 25,

							"input_limit" : 16,
						},
						{
							"name" : "clean_editline_button",
							"type" : "button",
							
							"x" : 24,
							"y" : 3, 
							
							"horizontal_align" : "right",
							
							"default_image" : MAIN_PATH + "search_editline/clean_1.tga",
							"over_image" : MAIN_PATH + "search_editline/clean_2.tga",
							"down_image" : MAIN_PATH + "search_editline/clean_3.tga",
						},
					],
				},
				{
					"name" : "premium_image_box",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 20,
					"y" : BOARD_HEIGHT - 32,
					
					"image" : MAIN_PATH + "footer/premium_box.tga",
					"children" :
					[
						{
							"name" : "premium_logo",
							"type" : "expanded_image",
							"style" : ("ltr",),
							
							"x" : 3,
							"y" : 2,
							
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
				
				#############
				
				############ Right side window
				{
					"name" : "search_bg",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 203 + 5 + 9,
					"y" : TOP_LINE+1,
					
					"image" : MAIN_PATH + "search_bg.tga",
					"children" :
					[
						{
							"name" : "dragon_bg",
							"type" : "expanded_image",
							"style" : ("alpha_sensitive",),
							
							"x" : 12,
							"y" : 0,

							"image" : MAIN_PATH + "right_side/dragon_bg.tga",
						},
						{
							"name" : "help_window",
							"type" : "expanded_image",
							"style" : ("alpha_sensitive",),
							
							"x" : 0,
							"y" : 0,

							"image" : MAIN_PATH + "right_side/main_help.tga",
						},
						{
							"name" : "error_mensage",
							"type" : "text",
							
							"x" : 0,
							"y" : 0,
							
							"horizontal_align" : "center",
							"vertical_align" : "center",
							"text_horizontal_align" : "center",
							
							"text" : uiScriptLocale.NEWPRIVATE_SHOP_SEARCH_ERROR1
						},
						
						#Loading stuff
						{
							"name" : "loading_window",
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
								MAIN_PATH + "loading_gif/0.tga",
								MAIN_PATH + "loading_gif/1.tga",
								MAIN_PATH + "loading_gif/2.tga",
								MAIN_PATH + "loading_gif/3.tga",
								MAIN_PATH + "loading_gif/4.tga",
								MAIN_PATH + "loading_gif/5.tga",
								MAIN_PATH + "loading_gif/6.tga",
								MAIN_PATH + "loading_gif/7.tga",
								MAIN_PATH + "loading_gif/8.tga",
								MAIN_PATH + "loading_gif/9.tga",
								MAIN_PATH + "loading_gif/10.tga",
								MAIN_PATH + "loading_gif/11.tga",
								MAIN_PATH + "loading_gif/12.tga",
								MAIN_PATH + "loading_gif/13.tga",
								MAIN_PATH + "loading_gif/14.tga",
								MAIN_PATH + "loading_gif/15.tga",
								MAIN_PATH + "loading_gif/16.tga",
								MAIN_PATH + "loading_gif/17.tga",
								MAIN_PATH + "loading_gif/18.tga",
								MAIN_PATH + "loading_gif/19.tga",
								MAIN_PATH + "loading_gif/20.tga",
								MAIN_PATH + "loading_gif/21.tga",
								MAIN_PATH + "loading_gif/22.tga",
								MAIN_PATH + "loading_gif/23.tga",
								MAIN_PATH + "loading_gif/24.tga",
								MAIN_PATH + "loading_gif/25.tga",
								MAIN_PATH + "loading_gif/26.tga",
								MAIN_PATH + "loading_gif/27.tga",
								MAIN_PATH + "loading_gif/28.tga",
								MAIN_PATH + "loading_gif/29.tga",
								MAIN_PATH + "loading_gif/30.tga",
								MAIN_PATH + "loading_gif/31.tga",
								MAIN_PATH + "loading_gif/32.tga",
							],
						},
					],
				},
				{
					"name" : "bg_inv2",
					"type" : "expanded_image",
					"style" : ("alpha_sensitive",),
					
					"x" : 203 + 5 + 9,
					"y" : 29,

					"image" : MAIN_PATH + "right_side/bar.tga",
				},
				{
					"name" : "header_search_bg",
					"type" : "expanded_image",
					"style" : ("ltr",),
					
					"x" : 203 + 5 + 8 + 28,
					"y" : 31 + 5,
					
					"image" : MAIN_PATH + "bg_header.tga",
					"children" :
					[
						{
							"name" : "item_text_base",
							"type" : "text",
							
							"x" : 5,
							"y" : 3,
							
							"text" : uiScriptLocale.MEW_PRIVATESHOPSEARCH_HEADER_1,
						},
						{
							"name" : "quantity_text_base",
							"type" : "text",
							
							"x" : 40,
							"y" : 3,
							
							"text" : uiScriptLocale.MEW_PRIVATESHOPSEARCH_HEADER_2,
						},
						{
							"name" : "item_name_text_base",
							"type" : "text",
							
							"x" : 120,
							"y" : 3,
							
							"text_horizontal_align" : "center",
							
							"text" : uiScriptLocale.MEW_PRIVATESHOPSEARCH_HEADER_3,
						},
						{
							"name" : "shop_time_text_base",
							"type" : "text",
							
							"x" : 290,
							"y" : 3,
							
							"text_horizontal_align" : "center",
							
							"text" : uiScriptLocale.MEW_PRIVATESHOPSEARCH_HEADER_4,
						},
						{
							"name" : "item_price_text_base",
							"type" : "text",
							
							"x" : 470,
							"y" : 3,
							
							"text_horizontal_align" : "center",
							
							"text" : uiScriptLocale.MEW_PRIVATESHOPSEARCH_HEADER_5,
						},
					],
				},
				{
					"name" : "filter_button", "type" : "button",
					"x" : 203 + 5 + 9, "y" : 31 + 5,

					"default_image" : MAIN_PATH + "right_side/filter_norm.tga",
					"over_image" 	: MAIN_PATH + "right_side/filter_hover.tga",
					"down_image" 	: MAIN_PATH + "right_side/filter_down.tga",
				},
				
				#############
				
				############ Window Scrollbars
				{
					"name" : "left_side_scrollbar",
					"type" : "new_scrollbar",

					"x" : 203 + 5,
					"y" : TOP_LINE-11,
					"size" : 481,
				},
				{
					"name" : "right_side_scrollbar",
					"type" : "new_scrollbar",

					"x" : 810-22,
					"y" : TOP_LINE-11,
					"size" : 481,
				},
				
				########### Footer
				{
					"name" : "result_per_page1",
					"type" : "radio_button",
					
					"x" : 203 + 5 + 9 + 1,
					"y" : BOARD_HEIGHT - 32,
					
					"text" : "50", 
					
					"default_image" : MAIN_PATH + "footer/footer_box_norm.tga",
					"over_image" : MAIN_PATH + "footer/footer_box_norm.tga",
					"down_image" : MAIN_PATH + "footer/footer_box_down.tga",
				},

				{
					"name" : "result_per_page2",
					"type" : "radio_button",
					
					"x" : 203 + 5 + 9 + 40 + 1,
					"y" : BOARD_HEIGHT - 32,
					
					"text" : "100", 
					
					"default_image" : MAIN_PATH + "footer/footer_box_norm.tga",
					"over_image" : MAIN_PATH + "footer/footer_box_norm.tga",
					"down_image" : MAIN_PATH + "footer/footer_box_down.tga",
				},

				{
					"name" : "result_per_page3",
					"type" : "radio_button",
					
					"x" : 203 + 5 + 9 + 80+ 1,
					"y" : BOARD_HEIGHT - 32,
					
					"text" : "200", 
					
					"default_image" : MAIN_PATH + "footer/footer_box_norm.tga",
					"over_image" : MAIN_PATH + "footer/footer_box_norm.tga",
					"down_image" : MAIN_PATH + "footer/footer_box_down.tga",
				},
				{
					"name" : "result_per_page_text",
					"type" : "text",
					
					"x" : 203 + 5 + 9 + 80 + 43 + 1,
					"y" : BOARD_HEIGHT - 32 + 3,
					
					"text" : uiScriptLocale.NEWPRIVATE_SHOP_SEARCH_RESULT_PP,
				},
				
				{
					"name" : "buttons_and_arrows",
					"type" : "window",
					"style" : ("attach",),
					
					"x" : 510,
					"y" : BOARD_HEIGHT - 32,
					
					"width" : 283,
					"height" : 30,
					"children" :
					[
						{
							"name" : "first_prev_button", "type" : "button",
							"x" : 0, "y" : 5,

							"default_image" : "d:/ymir work/ui/privatesearch/private_first_prev_btn_01.sub",
							"over_image" 	: "d:/ymir work/ui/privatesearch/private_first_prev_btn_02.sub",
							"down_image" 	: "d:/ymir work/ui/privatesearch/private_first_prev_btn_01.sub",
						},
						{
							"name" : "prev_button", "type" : "button",
							"x" : 30, "y" : 5,

							"default_image" : "d:/ymir work/ui/privatesearch/private_prev_btn_01.sub",
							"over_image" 	: "d:/ymir work/ui/privatesearch/private_prev_btn_02.sub",
							"down_image" 	: "d:/ymir work/ui/privatesearch/private_prev_btn_01.sub",
						},
						{
							"name" : "1_result_page",
							"type" : "radio_button",
							
							"x" : 48+2,
							"y" : 0,
							
							"text" : "1", 
							
							"default_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"over_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"down_image" : MAIN_PATH + "footer/footer_box_down.tga",
						},
						{
							"name" : "2_result_page",
							"type" : "radio_button",
							
							"x" : 81+2,
							"y" : 0,
							
							"text" : "2", 
							
							"default_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"over_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"down_image" : MAIN_PATH + "footer/footer_box_down.tga",
						},
						{
							"name" : "3_result_page",
							"type" : "radio_button",
							
							"x" : 2+81+33*1,
							"y" : 0,
							
							"text" : "3", 
							
							"default_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"over_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"down_image" : MAIN_PATH + "footer/footer_box_down.tga",
						},
						{
							"name" : "4_result_page",
							"type" : "radio_button",
							
							"x" : 2+81+33*2,
							"y" : 0,
							
							"text" : "4", 
							
							"default_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"over_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"down_image" : MAIN_PATH + "footer/footer_box_down.tga",
						},
						{
							"name" : "5_result_page",
							"type" : "radio_button",
							
							"x" : 2+81+33*3,
							"y" : 0,
							
							"text" : "5", 
							
							"default_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"over_image" : MAIN_PATH + "footer/footer_box_norm.tga",
							"down_image" : MAIN_PATH + "footer/footer_box_down.tga",
						},
						{
							"name" : "next_button", "type" : "button",
							"x" : 273 - 50, "y" : 5,

							"default_image" : "d:/ymir work/ui/privatesearch/private_next_btn_01.sub",
							"over_image" 	: "d:/ymir work/ui/privatesearch/private_next_btn_02.sub",
							"down_image" 	: "d:/ymir work/ui/privatesearch/private_next_btn_01.sub",
						},
						{
							"name" : "last_next_button", "type" : "button",
							"x" : 273 - 20, "y" : 5,

							"default_image" : "d:/ymir work/ui/privatesearch/private_last_next_btn_01.sub",
							"over_image" 	: "d:/ymir work/ui/privatesearch/private_last_next_btn_02.sub",
							"down_image" 	: "d:/ymir work/ui/privatesearch/private_last_next_btn_01.sub",
						},
					],
				},
				#############
			],
		},
		{
			"name" : "block_page",
			"type" : "expanded_image",
			"style" : ("ltr",),
			
			"x" : 0,
			"y" : 0,
			
			"image" : MAIN_PATH + "block_page.tga",
		},
	],
}
