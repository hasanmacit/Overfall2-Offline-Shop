#importun altına ekle

NEW_PATH = "d:/ymir work/ui/"

#arat

						{
							"name" : "Character_Name_Slot",
							"type" : "image",
							"x" : 153,
							"y" :27+7,
							"image" : LARGE_VALUE_FILE,

							"children" :
							(

#altına ekle

								{
									"name" : "overfall2_premium",
									"type" : "expanded_image",
									"style" : ("ltr",),
									
									"x" : 2,
									"y" : 2,
									
									"image" : NEW_PATH + "overfall2_mini_logo.tga",
								},

#son hali böyle olacak

						{
							"name" : "Character_Name_Slot",
							"type" : "image",
							"x" : 153,
							"y" :27+7,
							"image" : LARGE_VALUE_FILE,

							"children" :
							(
								{
									"name" : "overfall2_premium",
									"type" : "expanded_image",
									"style" : ("ltr",),
									
									"x" : 2,
									"y" : 2,
									
									"image" : NEW_PATH + "overfall2_mini_logo.tga",
								},
								{
									"name" : "Character_Name",
									"type":"text",
									"text":"캐릭터 이름",
									"x":0,
									"y":0,
									"r":1.0,
									"g":1.0,
									"b":1.0,
									"a":1.0,
									"all_align" : "center",
								},
							),
						},