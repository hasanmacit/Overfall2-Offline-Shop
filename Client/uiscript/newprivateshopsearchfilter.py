import app
import item
import uiScriptLocale
import localeInfo

MAIN_PATH = "d:/ymir work/ui/search_shop/"

BOARD_WIDTH = 205
BOARD_HEIGHT = 304

window = {
	"name" : "PrivateShopFilterWindow",

	"x" : 0,
	"y" : 0,

	"style" : ("movable", "float", "alpha_sensitive", ),

	"width" : BOARD_WIDTH,
	"height" : BOARD_HEIGHT+60,

	"children" :
	[
		{
			"name" : "board",
			"type" : "new_board",

			"x" : 0,
			"y" : 0,

			"width" : BOARD_WIDTH,
			"height" : BOARD_HEIGHT,
			"children" : 
			[
				{
					"name" : "filter_bg",
					"type" : "expanded_image",
					"style" : ("attach",),
					
					"x" : 0,
					"y" : 0,
					
					"image" : MAIN_PATH + "filter_window/filter_bg.tga",
					"children" :
					[
						{
							"name" : "min_level_el",
							"type" : "editline",
							
							"x" : 25,
							"y" : 42 - 3,
							
							"width" : 74,
							"height" : 24,
							
							"only_number" : 1,
							"input_limit" : 3,
						},
						{
							"name" : "clean_min_level_el",
							"type" : "button",
							
							"x" : 25 + 74 - 24,
							"y" : 42 - 5, 
							
							"default_image" : MAIN_PATH + "search_editline/clean_1.tga",
							"over_image" : MAIN_PATH + "search_editline/clean_2.tga",
							"down_image" : MAIN_PATH + "search_editline/clean_3.tga",
						},
						
						{
							"name" : "max_level_el",
							"type" : "editline",
							
							"x" : 25 + 93,
							"y" : 42 - 3,
							
							"width" : 74,
							"height" : 24,
							
							"only_number" : 1,
							"input_limit" : 3,
						},
						{
							"name" : "clean_max_level_el",
							"type" : "button",
							
							"x" : 25 + 93 + 74 - 24,
							"y" : 42 - 5, 
							
							"default_image" : MAIN_PATH + "search_editline/clean_1.tga",
							"over_image" : MAIN_PATH + "search_editline/clean_2.tga",
							"down_image" : MAIN_PATH + "search_editline/clean_3.tga",
						},
						
						#nivel do item
						{
							"name" : "item_level_label" ,
							"type" : "window",
							"style" : ("attach", ),
							
							"x" : 15,
							"y" : 63,
							
							"width" : 175,
							"height" : 34,
							
							"children" : 
							[
								{
									"name" : "item_level_textline",
									"type" : "text",
									
									"x" : 0,
									"y" : 6,
									
									"horizontal_align":"center",
									"text_horizontal_align":"center",
									
									"text" : "",
								},
								{
									"name" : "expand_item_level_textline",
									"type" : "button",
									
									"x" : 23,
									"y" : 6,
									
									"horizontal_align" : "right",
									
									"default_image" : MAIN_PATH + "filter_window/expand_filter_button_norm.tga",
									"over_image" : MAIN_PATH + "filter_window/expand_filter_button_hover.tga",
									"down_image" : MAIN_PATH + "filter_window/expand_filter_button_down.tga",
								},
							],
						},
						
						#DH min e DH max
						{
							"name" : "dm_min_el",
							"type" : "editline",
							
							"x" : 25,
							"y" : 42 + 60 - 3,
							
							"width" : 74,
							"height" : 24,
							
							"only_number" : 1,
							"input_limit" : 2,
						},
						{
							"name" : "clean_dm_min_el",
							"type" : "button",
							
							"x" : 25 + 74 - 24,
							"y" : 42 - 5 + 60, 
							
							"default_image" : MAIN_PATH + "search_editline/clean_1.tga",
							"over_image" : MAIN_PATH + "search_editline/clean_2.tga",
							"down_image" : MAIN_PATH + "search_editline/clean_3.tga",
						},
						
						{
							"name" : "dm_max_el",
							"type" : "editline",
							
							"x" : 25 + 93,
							"y" : 42 + 60 - 3,
							
							"width" : 74,
							"height" : 24,
							
							"only_number" : 1,
							"input_limit" : 2,
						},
						{
							"name" : "clean_dm_max_el",
							"type" : "button",
							
							"x" : 25 + 93 + 74 - 24,
							"y" : 42 - 5 + 60, 
							
							"default_image" : MAIN_PATH + "search_editline/clean_1.tga",
							"over_image" : MAIN_PATH + "search_editline/clean_2.tga",
							"down_image" : MAIN_PATH + "search_editline/clean_3.tga",
						},

						{
							"name" : "dh_min_el",
							"type" : "editline",
							
							"x" : 25,
							"y" : 42 + 60 + 30 - 3,
							
							"width" : 74,
							"height" : 24,
							
							"only_number" : 1,
							"input_limit" : 2,
						},
						{
							"name" : "clean_dh_min_el",
							"type" : "button",
							
							"x" : 25 + 74 - 24,
							"y" : 42 - 5 + 60 + 30 - 1, 
							
							"default_image" : MAIN_PATH + "search_editline/clean_1.tga",
							"over_image" : MAIN_PATH + "search_editline/clean_2.tga",
							"down_image" : MAIN_PATH + "search_editline/clean_3.tga",
						},
						
						{
							"name" : "dh_max_el",
							"type" : "editline",
							
							"x" : 25 + 93,
							"y" : 42 + 60 + 30 - 3,
							
							"width" : 74,
							"height" : 24,
							
							"only_number" : 1,
							"input_limit" : 2,
						},
						{
							"name" : "clean_dh_max_el",
							"type" : "button",
							
							"x" : 25 + 93+ 74 - 24,
							"y" : 42 - 5 + 60 + 30 - 1, 
							
							"default_image" : MAIN_PATH + "search_editline/clean_1.tga",
							"over_image" : MAIN_PATH + "search_editline/clean_2.tga",
							"down_image" : MAIN_PATH + "search_editline/clean_3.tga",
						},
						
						#abs acce
						{
							"name" : "acce_label" ,
							"type" : "window",
							"style" : ("attach", ),
							
							"x" : 15,
							"y" : 152,
							
							"width" : 175,
							"height" : 34,
							
							"children" : 
							[
								{
									"name" : "acce_abs_textline",
									"type" : "text",
									
									"x" : 0,
									"y" : 6,
									
									"horizontal_align":"center",
									"text_horizontal_align":"center",
									
									"text" : "",
								},
								{
									"name" : "expand_acce_abs_textline",
									"type" : "button",
									
									"x" : 23,
									"y" : 6,
									
									"horizontal_align" : "right",
									
									"default_image" : MAIN_PATH + "filter_window/expand_filter_button_norm.tga",
									"over_image" : MAIN_PATH + "filter_window/expand_filter_button_hover.tga",
									"down_image" : MAIN_PATH + "filter_window/expand_filter_button_down.tga",
								},
							],
						},

						#alchemy clarity
						{
							"name" : "alchemy_label" ,
							"type" : "window",
							"style" : ("attach", ),
							
							"x" : 15,
							"y" : 183,
							
							"width" : 175,
							"height" : 34,
							
							"children" : 
							[
								{
									"name" : "alchemy_textline",
									"type" : "text",
									
									"x" : 0,
									"y" : 6,
									
									"horizontal_align":"center",
									"text_horizontal_align":"center",
									
									"text" : "",
								},
								{
									"name" : "expand_alchemy_textline",
									"type" : "button",
									
									"x" : 23,
									"y" : 6,
									
									"horizontal_align" : "right",
									
									"default_image" : MAIN_PATH + "filter_window/expand_filter_button_norm.tga",
									"over_image" : MAIN_PATH + "filter_window/expand_filter_button_hover.tga",
									"down_image" : MAIN_PATH + "filter_window/expand_filter_button_down.tga",
								},
							],
						},

						#item bonus
						{
							"name" : "item_bonus_label" ,
							"type" : "window",
							"style" : ("attach", ),
							
							"x" : 15,
							"y" : 213,
							
							"width" : 175,
							"height" : 34,
							
							"children" : 
							[
								{
									"name" : "item_bonus_textline",
									"type" : "text",
									
									"x" : 0,
									"y" : 6,
									
									"horizontal_align":"center",
									"text_horizontal_align":"center",
									
									"text" : "",
								},
								{
									"name" : "expand_item_bonus_textline",
									"type" : "button",
									
									"x" : 23,
									"y" : 6,
									
									"horizontal_align" : "right",
									
									"default_image" : MAIN_PATH + "filter_window/expand_filter_button_norm.tga",
									"over_image" : MAIN_PATH + "filter_window/expand_filter_button_hover.tga",
									"down_image" : MAIN_PATH + "filter_window/expand_filter_button_down.tga",
								},
							],
						},
					],
				},
				
				#Manage buttons
				{
					"name" : "f_rbutton",
					"type" : "radio_button",
					
					"x" : 16,
					"y" : 244,
					
					"tooltip_text" : uiScriptLocale.NEW_PRIVATESHOPSEARCH_WOMEN_NAME,
					
					"default_image" : MAIN_PATH + "filter_window/f_norm.tga",
					"over_image" : MAIN_PATH + "filter_window/f_hover.tga",
					"down_image" : MAIN_PATH + "filter_window/f_down.tga",
				},
				{
					"name" : "m_rbutton",
					"type" : "radio_button",
					
					"x" : 81 + 16,
					"y" : 244,
					
					"tooltip_text" : uiScriptLocale.NEW_PRIVATESHOPSEARCH_MALE_NAME,
					
					"horizontal_align" : "right",
					
					"default_image" : MAIN_PATH + "filter_window/m_norm.tga",
					"over_image" : MAIN_PATH + "filter_window/m_hover.tga",
					"down_image" : MAIN_PATH + "filter_window/m_down.tga",
				},
				
				{
					"name" : "clear_button",
					"type" : "button",
					
					"x" : 16,
					"y" : 271,
					
					"tooltip_text" : uiScriptLocale.NEW_PRIVATESHOPSEARCH_RESET_BUTTON_TT,
					
					"default_image" : MAIN_PATH + "filter_window/clear_norm.tga",
					"over_image" : MAIN_PATH + "filter_window/clear_hover.tga",
					"down_image" : MAIN_PATH + "filter_window/clear_down.tga",
				},
				{
					"name" : "apply_button",
					"type" : "button",
					
					"x" : 81 + 16,
					"y" : 271,
					
					"horizontal_align" : "right",
					
					"tooltip_text" : uiScriptLocale.NEW_PRIVATESHOPSEARCH_APPLY_BUTTON_TT,
					
					"default_image" : MAIN_PATH + "filter_window/apply_norm.tga",
					"over_image" : MAIN_PATH + "filter_window/apply_hover.tga",
					"down_image" : MAIN_PATH + "filter_window/apply_down.tga",
				},
				{
					"name" : "TitleBar",
					"type" : "titlebar",

					"x" : 6,
					"y" : 7,

					"width" : BOARD_WIDTH - 13,
					"color" : "yellow",

					"children" :
					(
						{ "name":"TitleName", "type":"text", "x":0, "y":4, "text" : uiScriptLocale.NEW_PRIVATESHOPSEARCH_SEARCH_FILTER, "horizontal_align":"center", "text_horizontal_align":"center" },
					),
				},
				{
					"name" : "block_filter",
					"type" : "expanded_image",
					"style" : ("attach",),
					
					"x" : 0,
					"y" : 0,
					
					"image" : MAIN_PATH + "filter_window/block_filter.tga",
				},
			],
		},
	],
}
