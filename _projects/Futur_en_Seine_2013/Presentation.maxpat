{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 1,
			"revision" : 6,
			"architecture" : "x64"
		}
,
		"rect" : [ 0.0, 44.0, 1440.0, 806.0 ],
		"bgcolor" : [ 0.298039, 0.298039, 0.298039, 1.0 ],
		"bglocked" : 0,
		"openinpresentation" : 1,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"boxes" : [ 			{
				"box" : 				{
					"border" : 1,
					"fadetime" : 2000.0,
					"fadeunselect" : 1,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"htabcolor" : [ 0.422854, 0.476426, 0.6, 1.0 ],
					"id" : "obj-93",
					"maxclass" : "tab",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 729.0, 566.875, 57.5, 61.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1254.0, 50.875, 138.5, 271.0 ],
					"rounded" : 8.0,
					"spacing_y" : 12.0,
					"tabs" : [ "All", "Map", "FishEye", "Space" ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 311.0, 353.0, 127.0, 20.0 ],
					"text" : "hoa.encoder~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-108",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 516.0, 91.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-55",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 936.0, 513.5, 37.0, 18.0 ],
					"text" : "set 3"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-50",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 826.0, 513.5, 37.0, 18.0 ],
					"text" : "set 2"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-48",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 749.5, 515.0, 37.0, 18.0 ],
					"text" : "set 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-19",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 646.5896, 508.0, 37.0, 18.0 ],
					"text" : "set 0"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-97",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 5,
					"outlettype" : [ "bang", "bang", "bang", "bang", "" ],
					"patching_rect" : [ 729.0, 637.0, 110.0, 20.0 ],
					"text" : "sel 0 1 2 3"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.913725, 0.913725, 0.913725, 0.0 ],
					"id" : "obj-92",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"outlinecolor" : [ 0.497921, 0.497921, 0.497921, 1.0 ],
					"patching_rect" : [ 1443.0, 146.0, 20.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 441.25, 57.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"channels" : 16,
					"defvaldb" : 8.0,
					"id" : "obj-53",
					"inputmode" : 1,
					"loudspeakers" : 16,
					"maxclass" : "hoa.gain~",
					"numinlets" : 17,
					"numoutlets" : 17,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 832.796387, 695.5, 172.125793, 24.5 ]
				}

			}
, 			{
				"box" : 				{
					"defvaldb" : 8.0,
					"id" : "obj-20",
					"inputmode" : 1,
					"maxclass" : "hoa.gain~",
					"numinlets" : 9,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 998.819092, 695.5, 172.125793, 24.5 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-25",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 6,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 0.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "bang", "" ],
									"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
									"text" : "sel 32"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-17",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 4,
									"outlettype" : [ "int", "int", "int", "int" ],
									"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
									"text" : "key"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-45",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-45", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 59.5, 121.0, 59.5, 121.0 ],
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 59.5, 151.0, 59.5, 151.0 ],
									"source" : [ "obj-23", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 1236.0, 456.0, 51.0, 19.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 12.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p key32"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1236.0, 486.0, 99.0, 19.0 ],
					"saved_object_attributes" : 					{
						"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
					}
,
					"text" : "hoa.connect 7 16"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-11",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1444.0, 180.0, 37.0, 18.0 ],
					"text" : "reset"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-47",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 985.875, 158.0, 173.0, 20.0 ],
					"text" : "buffer~ SoundBic SoundBic.aif"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-35",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 189.375, 394.0, 43.0, 20.0 ],
					"text" : "sig~ 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-37",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 189.0, 306.0, 72.0, 20.0 ],
					"text" : "loadmess 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-45",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 189.375, 350.5, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-46",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 189.375, 445.0, 157.0, 20.0 ],
					"text" : "groove~ SoundBic @loop 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-32",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 999.375, 279.0, 43.0, 20.0 ],
					"text" : "sig~ 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 1004.0, 129.0, 195.0, 20.0 ],
					"text" : "buffer~ SoundConv SoundConv.aif"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 999.0, 191.0, 72.0, 20.0 ],
					"text" : "loadmess 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 999.375, 235.5, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 999.375, 330.0, 168.0, 20.0 ],
					"text" : "groove~ SoundConv @loop 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-100",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 263.375, 739.5, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-23",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "" ],
					"patching_rect" : [ 257.375, 681.5, 41.0, 19.0 ],
					"text" : "sel 32"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-17",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 4,
					"outlettype" : [ "int", "int", "int", "int" ],
					"patching_rect" : [ 257.375, 651.5, 59.5, 19.0 ],
					"text" : "key"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-96",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "" ],
					"patching_rect" : [ 176.338318, 722.0, 36.0, 20.0 ],
					"text" : "sel 9"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-10",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 176.338318, 792.5, 76.0, 17.0 ],
					"text" : "fullscreen $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-88",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 176.338318, 768.5, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-87",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 148.338318, 836.0, 69.0, 20.0 ],
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
					"text" : "thispatcher"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontname" : "Arial",
					"fontsize" : 18.0,
					"frgb" : 0.0,
					"id" : "obj-81",
					"linecount" : 15,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1321.5, 535.0, 226.0, 308.0 ],
					"presentation" : 1,
					"presentation_linecount" : 13,
					"presentation_rect" : [ 833.349976, 494.875, 382.5, 268.0 ],
					"text" : "HOA LIBRARY\n\nCICM - MSH Paris Nord - LABEX Arts H2H\n\n\nAnne Sèdes\nAlain Bonardi\nJulien Colafrancesco\nEliott Paris\nPierre Guillot\nManuel Deneu\n\nhttp://www.mshparisnord.fr/hoalibrary/",
					"textcolor" : [ 0.150202, 0.150202, 0.150202, 1.0 ],
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-78",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"patching_rect" : [ 896.0, 513.5, 34.0, 20.0 ],
					"text" : "t 0 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-77",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"patching_rect" : [ 791.5, 513.5, 34.0, 20.0 ],
					"text" : "t 0 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-76",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"patching_rect" : [ 709.5, 513.5, 34.0, 20.0 ],
					"text" : "t 0 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-52",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 628.0, 535.0, 32.5, 18.0 ],
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-42",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 5,
					"outlettype" : [ "", "", "", "", "" ],
					"patching_rect" : [ 628.0, 480.0, 345.0, 20.0 ],
					"text" : "route /All/x /MapButton/x /RecomposerButton/x /SpaceButton/x"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-40",
					"inputmode" : 1,
					"maxclass" : "hoa.gain~",
					"numinlets" : 9,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 998.819092, 551.0, 172.125793, 24.5 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-39",
					"inputmode" : 1,
					"maxclass" : "hoa.gain~",
					"numinlets" : 9,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 404.0, 626.0, 155.111862, 23.75 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-36",
					"inputmode" : 1,
					"maxclass" : "hoa.gain~",
					"numinlets" : 9,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 27.350006, 618.0, 155.111862, 23.75 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-33",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 6,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 0.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-96",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 50.0, 243.0, 191.0, 20.0 ],
									"text" : "route /Container/GrainFeedback/x"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-93",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 296.0, 253.75, 200.0, 20.0 ],
									"text" : "route /Container/GrainRarefaction/x"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-87",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 307.0, 129.0, 125.0, 20.0 ],
									"text" : "scale 0. 1. 200. 5000."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-88",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 307.0, 100.0, 169.0, 20.0 ],
									"text" : "route /Container/GrainDelay/x"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-81",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 127.0, 129.0, 119.0, 20.0 ],
									"text" : "scale 0. 1. 20. 1000."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-55",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 127.0, 100.0, 162.0, 20.0 ],
									"text" : "route /Container/GrainSize/x"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-15",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 190.0, 40.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-20",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 50.0, 333.75, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-23",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 127.0, 333.75, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-25",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 296.0, 333.75, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-31",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 307.0, 333.75, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-55", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-88", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-93", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-96", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-81", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-55", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-81", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-87", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-87", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-88", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-25", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-93", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-20", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-96", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 707.5, 99.0, 70.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 12.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p knobmap"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-16",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1227.375, 369.5, 47.0, 18.0 ],
					"text" : "$1 100"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-12",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 1139.875, 464.0, 36.0, 20.0 ],
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-114",
					"maxclass" : "newobj",
					"numinlets" : 10,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 999.375, 519.0, 154.0, 20.0 ],
					"saved_object_attributes" : 					{
						"mode" : "free",
						"ramp" : 100.0
					}
,
					"text" : "hoa.recomposer~ 4 10"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-115",
					"maxclass" : "newobj",
					"numinlets" : 9,
					"numoutlets" : 10,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 999.375, 476.0, 140.5, 20.0 ],
					"text" : "hoa.projector~ 4 10"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-112",
					"linecount" : 4,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 999.375, 386.5, 144.0, 58.0 ],
					"text" : "hoa.plug~ 4 hoa.decorrelation~ no @maxsize 44100 @delay 2000 @factor 1."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-44",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 646.5896, 739.5, 85.0, 20.0 ],
					"text" : "route /Fader/x"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-27",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 1227.375, 86.5, 32.5, 20.0 ],
					"text" : "!- 1."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-26",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 1227.375, 117.0, 32.5, 20.0 ],
					"text" : "+ 1."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-22",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 1227.375, 55.5, 97.0, 20.0 ],
					"text" : "route /FishEye/x"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-21",
					"maxclass" : "preset",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "preset", "int", "preset", "int" ],
					"patching_rect" : [ 1384.5, 213.5, 100.0, 40.0 ],
					"pattrstorage" : "fensrecomp"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-58",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 1227.375, 146.5, 80.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"autorestore" : "fensrecomp.json",
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1227.375, 174.5, 141.0, 20.0 ],
					"saved_object_attributes" : 					{
						"client_rect" : [ 916, 44, 1270, 172 ],
						"parameter_enable" : 0,
						"storage_rect" : [ 766, 44, 1220, 302 ]
					}
,
					"text" : "pattrstorage fensrecomp",
					"varname" : "fensrecomp"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"patching_rect" : [ 1350.625, 117.0, 59.5, 20.0 ],
					"restore" : 					{
						"recomp" : [ 1.0, 0.0, 1.0, 0.707107, 0.707107, 1.0, 0.0, 1.0, 1.0, -0.707107, 0.707107, 1.0, -1.0, 0.0, 1.0, -0.707107, -0.707107, 1.0, -0.0, -1.0, 1.0, 0.707107, -0.707107, 1.0 ]
					}
,
					"text" : "autopattr",
					"varname" : "u571001200"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-91",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 6,
							"architecture" : "x64"
						}
,
						"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 480.5, 304.0, 32.5, 20.0 ],
									"text" : "- 4."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 408.5, 284.0, 32.5, 20.0 ],
									"text" : "- 4."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 467.375, 261.5, 32.5, 20.0 ],
									"text" : "* 8."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 408.5, 250.5, 32.5, 20.0 ],
									"text" : "* 8."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 328.25, 330.0, 126.0, 20.0 ],
									"text" : "pak source 2 car 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-76",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 341.375, 286.0, 32.5, 20.0 ],
									"text" : "- 4."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-77",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 269.375, 266.0, 32.5, 20.0 ],
									"text" : "- 4."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-81",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 328.25, 243.5, 32.5, 20.0 ],
									"text" : "* 8."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-84",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 269.375, 232.5, 32.5, 20.0 ],
									"text" : "* 8."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-87",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 189.125, 312.0, 126.0, 20.0 ],
									"text" : "pak source 1 car 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-58",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 202.25, 259.0, 32.5, 20.0 ],
									"text" : "- 4."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-55",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 130.25, 239.0, 32.5, 20.0 ],
									"text" : "- 4."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-47",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 189.125, 216.5, 32.5, 20.0 ],
									"text" : "* 8."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-45",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 130.25, 205.5, 32.5, 20.0 ],
									"text" : "* 8."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-44",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 286.0, 126.0, 20.0 ],
									"text" : "pak source 0 car 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-42",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "float", "float", "float" ],
									"patching_rect" : [ 230.625, 174.5, 89.0, 20.0 ],
									"text" : "unpack 0. 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-40",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "float", "float", "float" ],
									"patching_rect" : [ 116.625, 174.5, 89.0, 20.0 ],
									"text" : "unpack 0. 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-39",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 220.625, 100.0, 77.0, 20.0 ],
									"text" : "route /Map/y"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-32",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 130.25, 100.0, 77.0, 20.0 ],
									"text" : "route /Map/x"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-88",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 170.4375, 40.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-89",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 114.5625, 392.0, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-40", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-45", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-40", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-84", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-40", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-42", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-42", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-81", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-42", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-89", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-55", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-45", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-58", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-89", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-55", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-58", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-87", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-76", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-87", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-77", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-76", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-81", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-77", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-84", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-89", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-87", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-88", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-88", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 27.278564, 99.0, 64.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 12.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p mapTraj"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-29",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 6,
							"architecture" : "x64"
						}
,
						"rect" : [ 284.0, 129.0, 823.0, 454.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-36",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 38.0, 404.0, 50.0, 31.0 ],
									"text" : "0.2"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-34",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 177.9552, 126.0, 117.0, 20.0 ],
									"text" : "vexpr ($f1 - 0.5) * 2."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-33",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 135.0, 117.0, 20.0 ],
									"text" : "vexpr ($f1 - 0.5) * 2."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-29",
									"linecount" : 8,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 535.0, 498.0, 50.0, 273.0 ],
									"text" : "0. 1. 1. 0.030684 0.859054 1. 1. 1. 1. 0.261638"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-20",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 879.7948, 289.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-21",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ 879.7948, 242.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-24",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 734.9552, 289.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-26",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ 734.9552, 242.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 634.7948, 276.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ 634.7948, 229.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 489.9552, 276.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-15",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ 489.9552, 229.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-16",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 337.7948, 276.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-17",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ 337.7948, 229.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-18",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 192.9552, 276.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-19",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ 192.9552, 229.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 289.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-6",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ 50.0, 242.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-7",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ -94.8396, 289.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-8",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ -94.8396, 242.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ -247.0, 289.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ -247.0, 242.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 10,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 327.2948, 435.0, 163.0, 20.0 ],
									"text" : "pak 0. 0. 0. 0. 0. 0. 0. 0. 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-22",
									"maxclass" : "newobj",
									"numinlets" : 5,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ -391.8396, 289.0, 100.0, 20.0 ],
									"text" : "zmap 0.2 1. 0. 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "float", "float" ],
									"patching_rect" : [ -391.8396, 242.0, 60.0, 20.0 ],
									"text" : "cartopol ."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-10",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 10,
									"outlettype" : [ "float", "float", "float", "float", "float", "float", "float", "float", "float", "float" ],
									"patching_rect" : [ -4.666667, 173.0, 183.0, 20.0 ],
									"text" : "unpack 0. 0. 0. 0. 0. 0. 0. 0. 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 10,
									"outlettype" : [ "float", "float", "float", "float", "float", "float", "float", "float", "float", "float" ],
									"patching_rect" : [ 247.9552, 155.0, 183.0, 20.0 ],
									"text" : "unpack 0. 0. 0. 0. 0. 0. 0. 0. 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 57.2948, 100.0, 88.0, 20.0 ],
									"text" : "route /Space/x"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 155.2948, 100.0, 88.0, 20.0 ],
									"text" : "route /Space/y"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-25",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 101.2948, 40.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-27",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 355.2948, 520.0, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-13", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-16", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-20", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-27", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-24", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-33", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-13", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-34", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 404.0, 99.0, 78.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 12.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p mapSpace"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 404.0, 48.5, 99.0, 20.0 ],
					"text" : "udpreceive 7500"
				}

			}
, 			{
				"box" : 				{
					"angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ],
					"channels" : 16,
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"drawvector" : 0,
					"id" : "obj-7",
					"loudspeakers" : 16,
					"maxclass" : "hoa.meter~",
					"numinlets" : 16,
					"numoutlets" : 2,
					"outlettype" : [ "list", "list" ],
					"patching_rect" : [ 838.5, 739.5, 154.0, 154.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 38.25, 440.875, 382.5, 382.5 ],
					"yls" : 16,
					"zls" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 9,
					"numoutlets" : 16,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 840.781433, 637.0, 154.0, 20.0 ],
					"saved_object_attributes" : 					{
						"angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ],
						"autoconnect" : 1,
						"channels" : 16,
						"loudspeakers" : 16,
						"mode" : "ambisonic",
						"pinnaesize" : "small",
						"restitution" : "panning",
						"ychannels" : 16,
						"zchannels" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ]
					}
,
					"text" : "hoa.decoder~ 4"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-43",
					"local" : 1,
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 263.375, 792.5, 44.0, 44.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1254.0, 375.375, 58.0, 58.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-99",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 46.338333, 815.0, 60.0, 20.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-98",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 27.278564, 438.0, 93.0, 20.0 ],
					"text" : "hoa.soundgrain"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-90",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 87.808449, 456.0, 89.0, 20.0 ],
					"text" : "hoa.soundcoat"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-54",
					"inputmode" : 1,
					"maxclass" : "hoa.gain~",
					"numinlets" : 9,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 404.0, 797.0, 261.5896, 17.75 ],
					"presentation" : 1,
					"presentation_rect" : [ 1254.0, 459.0, 58.0, 364.375 ],
					"range" : [ -70.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.74902, 0.74902, 0.74902, 1.0 ],
					"bordercolor" : [ 0.504182, 0.504182, 0.504182, 1.0 ],
					"circlecolor" : [ 0.8, 0.8, 0.8, 1.0 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"fisheyecolor" : [ 0.687659, 0.179729, 0.179729, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 14.0,
					"harmonicscolor" : [ 0.501961, 0.501961, 0.501961, 0.5 ],
					"id" : "obj-86",
					"maxclass" : "hoa.recomposer",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "list" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 1384.5, 266.0, 225.0, 225.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 435.25, 50.875, 382.5, 382.5 ],
					"rectselectcolor" : [ 0.386326, 0.519675, 0.8, 1.0 ],
					"selmiccolor" : [ 0.288867, 0.335101, 0.549868, 1.0 ],
					"varname" : "recomp"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-85",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 46.338333, 848.0, 116.0, 17.0 ],
					"text" : "fill 1, apply hamming"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-61",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 826.0, 308.5, 104.0, 20.0 ],
					"text" : "Rarefaction :",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"varname" : "autohelp_top_description[6]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-62",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 826.0, 308.5, 104.0, 20.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-63",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 838.5, 338.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-64",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 838.5, 369.5, 81.0, 17.0 ],
					"text" : "rarefaction $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-65",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 695.0, 308.5, 104.0, 20.0 ],
					"text" : "Feedback :",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"varname" : "autohelp_top_description[5]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-66",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 695.0, 308.5, 104.0, 20.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-67",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 707.5, 338.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-68",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 707.5, 369.5, 74.0, 17.0 ],
					"text" : "feedback $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-69",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 813.5, 174.5, 104.0, 20.0 ],
					"text" : "Delay :",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"varname" : "autohelp_top_description[4]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-70",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 813.5, 174.5, 104.0, 20.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-24",
					"maxclass" : "flonum",
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 826.0, 204.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-71",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 826.0, 235.5, 54.0, 17.0 ],
					"text" : "delay $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-72",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 695.0, 174.5, 105.0, 20.0 ],
					"text" : "Grain size in ms :\n",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"varname" : "autohelp_top_description[3]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-73",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 695.0, 174.5, 104.0, 20.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-74",
					"maxclass" : "flonum",
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 707.5, 204.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-75",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 707.5, 235.5, 47.0, 17.0 ],
					"text" : "size $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-79",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 6,
							"architecture" : "x64"
						}
,
						"rect" : [ 581.0, 122.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 168.25, 108.0, 89.0, 20.0 ],
									"text" : "hoa.soundcoat"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 79.25, 123.0, 89.0, 20.0 ],
									"text" : "hoa.soundcoat"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 120.25, 44.0, 89.0, 20.0 ],
									"text" : "hoa.soundcoat"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-90",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 49.25, 98.0, 89.0, 20.0 ],
									"text" : "hoa.soundcoat"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 77.5, 163.5, 41.0, 19.0 ],
									"text" : "*~ 0.5"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-28",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 77.5, 207.0, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-90", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 422.0, 394.0, 69.0, 19.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 12.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p synthesis"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-82",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 46.338333, 874.5, 121.0, 19.0 ],
					"text" : "buffer~ granular 1000"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-83",
					"linecount" : 5,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 404.0, 431.0, 144.0, 71.0 ],
					"text" : "hoa.plug~ 4 hoa.granular~ no @name granular @size 400 @delay 3000 @feedback 0.9 @rarefaction 0."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 10,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 404.0, 593.5, 140.5, 20.0 ],
					"saved_object_attributes" : 					{
						"mode" : "fixe",
						"ramp" : 20.0
					}
,
					"text" : "hoa.recomposer~ 4 10"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 9,
					"numoutlets" : 10,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 404.0, 513.5, 140.5, 20.0 ],
					"text" : "hoa.projector~ 4 10"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-49",
					"maxclass" : "newobj",
					"numinlets" : 10,
					"numoutlets" : 10,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 404.0, 555.5, 140.5, 20.0 ],
					"text" : "hoa.space~ 10"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.701961, 0.701961, 0.701961, 1.0 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-18",
					"maxclass" : "hoa.scope~",
					"numinlets" : 9,
					"numoutlets" : 0,
					"order" : 4,
					"patching_rect" : [ 999.930908, 739.5, 154.0, 154.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 435.25, 440.875, 382.5, 382.5 ],
					"txcolor" : [ 0.302419, 0.302419, 0.302419, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.74902, 0.74902, 0.74902, 1.0 ],
					"coeffs" : [ 0.074334, 0.882527, 0.031965, 0.299515, 0.120785, 0.065838, 0.0, 0.0 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"id" : "obj-51",
					"maxclass" : "hoa.space",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "list", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 404.0, 139.5, 248.5, 248.5 ],
					"presentation" : 1,
					"presentation_rect" : [ 833.349976, 50.875, 382.5, 382.5 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-38",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 404.0, 861.0, 140.2948, 20.0 ],
					"text" : "hoa.dac~ 1:2"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 9,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 27.350006, 551.0, 139.988327, 19.0 ],
					"saved_object_attributes" : 					{
						"damp" : 0.0,
						"dry" : 0.89,
						"size" : 0.7,
						"wet" : 0.33
					}
,
					"text" : "hoa.freeverb~ 4"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 9,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 404.0, 739.5, 141.0, 33.0 ],
					"saved_object_attributes" : 					{
						"angles" : [ 90.0, 270.0 ],
						"autoconnect" : 1,
						"channels" : 2,
						"loudspeakers" : 2,
						"mode" : "binaural",
						"pinnaesize" : "small",
						"restitution" : "panning",
						"ychannels" : 2,
						"zchannels" : [ 90.0, 270.0 ]
					}
,
					"text" : "hoa.decoder~ 4 @mode binaural"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"bgcolor2" : [ 0.701961, 0.701961, 0.701961, 1.0 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 30.0,
					"id" : "obj-2",
					"maxclass" : "hoa.map",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "list", "list", "list" ],
					"patching_rect" : [ 27.278564, 132.0, 248.25, 248.25 ],
					"presentation" : 1,
					"presentation_rect" : [ 38.25, 50.875, 382.5, 382.5 ],
					"sources_parameters" : [ "source", 0, -3.162045, -1.433639, 0, 1.0, 1.0, 1.0, 1.0, "", "source", 1, -3.247796, -2.84852, 0, 0.4, 0.4, 1.0, 1.0, "", "source", 2, 2.904794, 1.782, 0, 0.0, 1.0, 1.0, 1.0, "" ],
					"trajectory_parameters" : [ "slot", 0, "source", 0, -1.820705, -1.103227, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 1, 0, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 1, "source", 0, -1.820705, -1.103227, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 1, 0, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 2, "source", 0, -1.820705, -1.103227, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.669988, 2.030483, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.549227, 1.615105, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.194589, -1.68058, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 3, "source", 0, -1.820705, -1.103227, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.669988, 2.030483, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.549227, 1.615105, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.194589, -1.68058, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 4, "source", 0, -1.887753, -0.984107, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.536237, 2.133471, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.649684, 1.512352, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.084274, -1.75378, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 5, "source", 0, -1.952941, -0.847406, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.38067, 2.237292, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.753031, 1.39124, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.956844, -1.826429, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 6, "source", 0, -2.065197, -0.516757, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.996365, 2.432896, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.956877, 1.085956, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.645404, -1.958276, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 7, "source", 0, -2.104183, -0.32325, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.766739, 2.514724, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.04905, 0.900035, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.461248, -2.009638, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 8, "source", 0, -2.125812, -0.114011, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.514819, 2.578117, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.127871, 0.693422, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.260666, -2.045347, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 9, "source", 0, -1.987319, 0.763307, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.581937, 2.563801, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.225616, -0.235164, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.596584, -1.973697, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 10, "source", 0, -1.802259, 1.13311, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.06661, 2.402929, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.138165, -0.660999, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.966898, -1.821126, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 11, "source", 0, -1.633085, 1.36569, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.38076, 2.237236, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.029559, -0.943164, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.203539, -1.674183, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 12, "source", 0, -0.886672, 1.93543, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.208953, 1.42557, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.426359, -1.724578, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.806733, -0.993534, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 13, "source", 0, 0.065918, 2.127846, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.612383, 0.295262, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.511249, -2.178828, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.060054, -0.087008, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 14, "source", 0, 1.37797, 1.622737, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.226757, -1.397596, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.958446, -2.022387, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.665057, 1.216133, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 15, "source", 0, 1.37797, 1.622737, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.226757, -1.397596, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.958446, -2.022387, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.665057, 1.216133, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 16, "source", 0, 1.807274, 1.125094, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.694344, -2.010205, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.529645, -1.633663, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.214761, 1.666058, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 17, "source", 0, 1.897112, 0.965942, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.515689, -2.148118, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.664124, -1.496448, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.06739, 1.764106, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 18, "source", 0, 1.897112, 0.965942, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.515689, -2.148118, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.664124, -1.496448, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.06739, 1.764106, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 19, "source", 0, 2.094505, 0.380953, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.835556, -2.492703, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.023542, -0.956005, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.516301, 1.996203, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 20, "source", 0, 2.128799, 0.017008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.396785, -2.598901, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.157263, -0.595722, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.167178, 2.055102, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 21, "source", 0, 2.111212, -0.273608, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.038476, -2.628734, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.21837, -0.295811, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.114787, 2.058693, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 22, "source", 0, 1.93969, -0.877313, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.729692, -2.525722, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.208225, 0.363884, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.710081, 1.935763, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 23, "source", 0, 1.727797, -1.243702, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.214932, -2.331451, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.092596, 0.793544, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.078997, 1.757031, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 24, "source", 0, 1.262398, -1.714184, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.872175, -1.845721, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.747806, 1.397799, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.566414, 1.340798, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 25, "source", 0, 0.525827, -2.062906, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.428494, -1.007046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.094545, 1.952086, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.955421, 0.654004, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 26, "source", 0, -0.293429, -2.108548, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.62898, -0.013779, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.274958, 2.221051, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.057524, -0.134122, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 27, "source", 0, -0.590934, -2.045208, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.604108, 0.36103, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.044382, 2.237565, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.017407, -0.425981, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 28, "source", 0, -1.030341, -1.862921, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.45892, 0.930288, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.54015, 2.171844, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.872445, -0.863334, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 29, "source", 0, -1.280403, -1.700778, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.304909, 1.264562, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.838157, 2.075129, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.733531, -1.116362, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 30, "source", 0, -1.705651, -1.273904, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.858276, 1.859713, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.386006, 1.757172, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.351307, -1.557357, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 31, "source", 0, -1.910352, -0.939485, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.485691, 2.168973, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.684759, 1.473179, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.042772, -1.778769, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 32, "source", 0, -2.054758, -0.556818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.043485, 2.413061, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.93539, 1.123802, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.683362, -1.945356, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 33, "source", 0, -2.119008, 0.204649, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.124138, 2.626083, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.207549, 0.36796, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.047624, -2.061341, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 34, "source", 0, -1.192502, 1.763523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.944825, 1.769005, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.69023, -1.466898, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.619024, -1.276775, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 35, "source", 0, 0.319089, 2.104818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.628953, -0.018243, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.247885, -2.224235, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.055737, 0.159173, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 36, "source", 0, 1.132864, 1.802414, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.403074, -1.066282, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.660708, -2.138255, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.821258, 0.96665, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 37, "source", 0, 1.432586, 1.574729, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.177727, -1.47283, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.026956, -1.988474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.622552, 1.272289, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 38, "source", 0, 1.56492, 1.443295, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.040457, -1.657788, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.197061, -1.890956, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.504964, 1.409424, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 39, "source", 0, 1.896559, 0.967027, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.516917, -2.147251, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.663268, -1.4974, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.068399, 1.763495, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 40, "source", 0, 2.045951, 0.588353, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.080473, -2.396727, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.917878, -1.153435, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.7132, 1.934616, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 41, "source", 0, 2.128681, -0.028184, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.341529, -2.606738, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.169422, -0.549796, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.123517, 2.058188, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 42, "source", 0, 2.096576, -0.369386, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.081173, -2.627762, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.229532, -0.194567, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.20834, 2.051338, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 43, "source", 0, 2.036565, -0.620064, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.398161, -2.598691, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.236704, 0.076313, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.454731, 2.011122, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 44, "source", 0, 1.468764, -1.541042, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.624105, -2.067367, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.910331, 1.165891, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.384555, 1.527874, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 45, "source", 0, 0.715413, -2.005059, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.324305, -1.228548, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.271358, 1.841825, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.886119, 0.833037, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 46, "source", 0, 0.171234, -2.12197, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.563313, -0.58408, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.750489, 2.10842, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.037584, 0.315668, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 47, "source", 0, -0.28621, -2.10954, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.628917, -0.022779, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.282559, 2.220097, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.057971, -0.127078, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 48, "source", 0, -1.244161, -1.727466, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.331128, 1.215552, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.7941, 2.092385, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.756744, -1.079464, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 49, "source", 0, -1.645417, -1.350807, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.941631, 1.77251, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.30394, 1.818903, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.421326, -1.493729, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 50, "source", 0, -2.00333, -0.72024, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.234142, 2.321339, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.838757, 1.27579, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.837577, -1.884107, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 51, "source", 0, -2.119707, -0.197276, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.61551, 2.555948, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.099046, 0.776321, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.340663, -2.033554, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 52, "source", 0, -1.832144, 1.084124, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.00146, 2.430803, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.155203, -0.603133, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.917465, -1.846524, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 53, "source", 0, -0.969329, 1.895383, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.145407, 1.519523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.499418, -1.661449, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.762197, -1.07054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 54, "source", 0, 0.220043, 2.117465, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.626916, 0.10505, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.351907, -2.210165, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.06094, 0.062603, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 55, "source", 0, 0.892354, 1.932817, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.519978, -0.749289, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.381026, -2.205332, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.930189, 0.725096, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 56, "source", 0, 1.627844, 1.371933, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.964349, -1.7473, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.280353, -1.835583, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.440488, 1.475258, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 57, "source", 0, 1.816821, 1.109611, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.677106, -2.024609, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.543548, -1.620533, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.200481, 1.676376, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 58, "source", 0, 2.036113, 0.621548, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.119307, -2.378839, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.898866, -1.184472, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.744567, 1.922762, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 59, "source", 0, 2.122947, 0.158654, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.568876, -2.56673, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.112831, -0.737979, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.303585, 2.039419, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 60, "source", 0, 2.108729, -0.292127, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.015403, -2.628971, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.220881, -0.276329, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.132851, 2.057606, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 61, "source", 0, 1.934358, -0.889007, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.744927, -2.521271, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.205988, 0.377209, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.721754, 1.931441, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 62, "source", 0, 1.745633, -1.218541, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.18103, -2.348807, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.103872, 0.763146, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.053431, 1.772478, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 63, "source", 0, 1.493585, -1.516997, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.590333, -2.093458, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.929005, 1.134728, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.359572, 1.550148, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 64, "source", 0, 0.974151, -1.89291, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.141532, -1.52498, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.503643, 1.657627, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.759466, 1.075022, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 65, "source", 0, 0.443907, -2.082072, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.466388, -0.910305, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.016559, 1.993809, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.979735, 0.57623, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 66, "source", 0, -0.293429, -2.108548, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.62898, -0.013779, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.274958, 2.221051, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.057524, -0.134122, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 67, "source", 0, -0.700862, -2.010191, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.580726, 0.501573, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.165533, 2.231875, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.991368, -0.534645, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 68, "source", 0, -1.211286, -1.750675, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.353688, 1.171271, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.754407, 2.107021, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.776835, -1.046065, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 69, "source", 0, -1.419322, -1.586695, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.190009, 1.454505, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.010235, 1.997021, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.63317, -1.258629, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 70, "source", 0, -1.747501, -1.21586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.794724, 1.921116, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.444279, 1.709598, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.298204, -1.601893, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 71, "source", 0, -1.89991, -0.960425, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.509441, 2.152513, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.668465, 1.491607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.06226, -1.7672, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 72, "source", 0, -2.038996, -0.612024, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.108176, 2.384045, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.904382, 1.175584, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.735572, -1.926221, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 73, "source", 0, -2.104183, -0.32325, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.766739, 2.514724, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.04905, 0.900035, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.461248, -2.009638, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 74, "source", 0, -2.127126, -0.086092, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.480927, 2.584653, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.136791, 0.665426, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.233791, -2.048593, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 75, "source", 0, -2.124316, 0.139131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.205154, 2.620999, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.195137, 0.435939, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.016039, -2.061828, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 76, "source", 0, -2.11501, 0.242506, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.077161, 2.627883, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.213776, 0.328428, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.084475, -2.060159, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 77, "source", 0, -2.11501, 0.242506, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.077161, 2.627883, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.213776, 0.328428, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.084475, -2.060159, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 78, "source", 0, -2.11501, 0.242506, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.077161, 2.627883, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.213776, 0.328428, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.084475, -2.060159, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 79, "source", 0, -2.100816, 0.344456, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.049954, 2.628541, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.227063, 0.221036, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.183959, -2.053668, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 80, "source", 0, -2.100816, 0.344456, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.049954, 2.628541, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.227063, 0.221036, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.183959, -2.053668, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 81, "source", 0, -2.076292, 0.470198, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.207972, 2.620777, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.236326, 0.086677, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.307155, -2.038884, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 82, "source", 0, -2.076292, 0.470198, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.207972, 2.620777, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.236326, 0.086677, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.307155, -2.038884, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 83, "source", 0, -2.076292, 0.470198, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.207972, 2.620777, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.236326, 0.086677, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.307155, -2.038884, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 84, "source", 0, -2.076292, 0.470198, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.207972, 2.620777, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.236326, 0.086677, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.307155, -2.038884, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 85, "source", 0, -2.076292, 0.470198, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.207972, 2.620777, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.236326, 0.086677, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.307155, -2.038884, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 86, "source", 0, -2.076292, 0.470198, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.207972, 2.620777, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.236326, 0.086677, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.307155, -2.038884, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 87, "source", 0, -2.076292, 0.470198, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.207972, 2.620777, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.236326, 0.086677, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.307155, -2.038884, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 88, "source", 0, -2.071364, 0.585448, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.2129, 2.736027, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.241255, 0.201927, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.302227, -1.923634, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 89, "source", 0, -2.071364, 0.608467, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.2129, 2.759046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.241255, 0.224946, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.302227, -1.900615, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 90, "source", 0, -2.071364, 0.654503, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.2129, 2.805082, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.241255, 0.270982, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.302227, -1.854579, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 91, "source", 0, -2.071364, 0.677522, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.2129, 2.8281, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.241255, 0.294001, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.302227, -1.83156, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 92, "source", 0, -2.094382, 0.746576, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.189882, 2.897155, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.218236, 0.363055, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.325245, -1.762506, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 93, "source", 0, -2.1174, 0.769595, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.166864, 2.920174, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.195218, 0.386074, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.348264, -1.739487, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 94, "source", 0, -2.163437, 0.838649, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.120827, 2.989228, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.149182, 0.455128, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.3943, -1.670433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 95, "source", 0, -2.209474, 0.930723, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.074791, 3.081301, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.103145, 0.547202, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.440337, -1.578359, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 96, "source", 0, -2.301547, 1.045814, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.017283, 3.196393, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.011072, 0.662293, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.53241, -1.463268, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 97, "source", 0, -2.301547, 1.045814, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.017283, 3.196393, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.011072, 0.662293, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.53241, -1.463268, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 98, "source", 0, -2.39362, 1.206942, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.109356, 3.357521, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.918999, 0.823421, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.624483, -1.30214, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 99, "source", 0, -2.416638, 1.252978, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.132374, 3.403557, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.895981, 0.869457, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.647501, -1.256104, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 100, "source", 0, -2.439656, 1.391088, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.155392, 3.541667, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.872962, 1.007567, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.670519, -1.117994, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 101, "source", 0, -2.462675, 1.506179, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.17841, 3.656758, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.849944, 1.122658, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.693538, -1.002903, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 102, "source", 0, -2.462675, 1.736362, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.17841, 3.886941, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.849944, 1.352841, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.693538, -0.77272, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 103, "source", 0, -2.462675, 1.75938, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.17841, 3.909959, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.849944, 1.375859, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.693538, -0.749702, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 104, "source", 0, -2.462675, 1.874472, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.17841, 4.025051, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.849944, 1.490951, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.693538, -0.63461, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 105, "source", 0, -2.462675, 2.058618, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.17841, 4.209197, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.849944, 1.675097, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.693538, -0.450464, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 106, "source", 0, -2.439656, 2.173709, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.155392, 4.324288, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.872962, 1.790188, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.670519, -0.335373, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 107, "source", 0, -2.39362, 2.334837, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.109356, 4.485416, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.918999, 1.951316, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.624483, -0.174245, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 108, "source", 0, -2.278528, 2.449929, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.005736, 4.600507, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.03409, 2.066407, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.509391, -0.059154, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 109, "source", 0, -2.163437, 2.518983, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.120827, 4.669562, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.149182, 2.135462, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.3943, 0.009901, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 110, "source", 0, -1.979291, 2.611056, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.304973, 4.761635, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.333328, 2.227535, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.210154, 0.101974, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 111, "source", 0, -1.841181, 2.680111, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.443083, 4.83069, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.471437, 2.29659, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.072044, 0.171029, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 112, "source", 0, -1.841181, 2.680111, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.443083, 4.83069, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.471437, 2.29659, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.072044, 0.171029, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 113, "source", 0, -1.610999, 2.726148, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.673266, 4.876727, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.70162, 2.342627, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.158138, 0.217066, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 114, "source", 0, -1.403834, 2.726148, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.88043, 4.876727, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.908785, 2.342627, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.365303, 0.217066, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 115, "source", 0, -1.265724, 2.726148, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.01854, 4.876727, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.046894, 2.342627, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.503412, 0.217066, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 116, "source", 0, -1.104597, 2.703129, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.179668, 4.853708, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.208022, 2.319608, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.66454, 0.194047, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 117, "source", 0, -1.035542, 2.588038, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.248722, 4.738617, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.277077, 2.204517, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.733595, 0.078956, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 118, "source", 0, -0.989505, 2.495965, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.294759, 4.646544, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.323113, 2.112444, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.779632, -0.013117, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 119, "source", 0, -0.966487, 2.357855, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.317777, 4.508434, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.346132, 1.974334, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.80265, -0.151227, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 120, "source", 0, -0.943469, 1.89749, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.340796, 4.048069, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.36915, 1.513969, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.825668, -0.611592, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 121, "source", 0, -0.943469, 1.460143, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.340796, 3.610722, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.36915, 1.076622, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.825668, -1.048939, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 122, "source", 0, -0.943469, 1.160905, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.340796, 3.311484, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.36915, 0.777384, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.825668, -1.348177, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 123, "source", 0, -0.943469, 0.746576, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.340796, 2.897155, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.36915, 0.363055, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.825668, -1.762506, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 124, "source", 0, -1.012523, 0.355266, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.271741, 2.505845, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.300095, -0.028255, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.756613, -2.153816, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 125, "source", 0, -1.104597, -0.151136, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.179668, 1.999443, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.208022, -0.534657, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.66454, -2.660218, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 126, "source", 0, -1.173651, -0.358301, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.110613, 1.792278, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.138967, -0.741822, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.595486, -2.867383, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 127, "source", 0, -1.288743, -0.749611, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.995521, 1.400968, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.023876, -1.133132, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.480394, -3.258693, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 128, "source", 0, -1.403834, -1.071867, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.88043, 1.078712, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.908785, -1.455388, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.365303, -3.580949, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 129, "source", 0, -1.495907, -1.232995, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.788357, 0.917584, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.816711, -1.616516, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.27323, -3.742077, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 130, "source", 0, -1.634017, -1.440159, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.650247, 0.71042, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.678602, -1.82368, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.13512, -3.949241, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 131, "source", 0, -1.887218, -1.923543, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.397046, 0.227036, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.425401, -2.307064, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.118081, -4.432625, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 132, "source", 0, -1.887218, -1.923543, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.397046, 0.227036, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.425401, -2.307064, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.118081, -4.432625, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 133, "source", 0, -2.071364, -2.176744, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.2129, -0.026165, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.241255, -2.560265, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.302227, -4.685826, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 134, "source", 0, -2.163437, -2.268817, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.120827, -0.118238, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.149182, -2.652338, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.3943, -4.777899, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 135, "source", 0, -2.416638, -2.383909, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.132374, -0.23333, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.895981, -2.76743, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.647501, -4.892991, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 136, "source", 0, -2.416638, -2.383909, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.132374, -0.23333, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.895981, -2.76743, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.647501, -4.892991, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 137, "source", 0, -2.807949, -2.452963, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.523685, -0.302384, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.50467, -2.836484, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.038812, -4.962045, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 138, "source", 0, -2.969077, -2.337872, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.684812, -0.187293, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.343542, -2.721393, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.19994, -4.846954, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 139, "source", 0, -3.222277, -1.96958, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.938013, 0.180999, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.090341, -2.353101, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.45314, -4.478662, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 140, "source", 0, -3.337369, -1.877507, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.053105, 0.273072, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.97525, -2.261028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.568232, -4.386589, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 141, "source", 0, -3.45246, -1.279032, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.168196, 0.871547, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.860158, -1.662552, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.683323, -3.788114, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 142, "source", 0, -3.429442, -1.002812, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.145178, 1.147767, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.883177, -1.386333, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.660305, -3.511894, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 143, "source", 0, -3.314351, -0.77263, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.030086, 1.377949, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.998268, -1.15615, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.545214, -3.281712, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 144, "source", 0, -3.314351, -0.77263, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.030086, 1.377949, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.998268, -1.15615, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.545214, -3.281712, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 145, "source", 0, -3.038131, -0.450374, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.753867, 1.700205, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.274487, -0.833895, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.268994, -2.959456, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 146, "source", 0, -2.900022, -0.289246, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.615758, 1.861333, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.412597, -0.672767, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.130885, -2.798328, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 147, "source", 0, -2.715876, -0.174154, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.431611, 1.976424, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.596743, -0.557675, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.946739, -2.683237, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 148, "source", 0, -2.577766, -0.082081, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.293502, 2.068498, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.734853, -0.465602, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.808629, -2.591163, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 149, "source", 0, -2.416638, -0.013027, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.132374, 2.137552, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.895981, -0.396548, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.647501, -2.522109, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 150, "source", 0, -2.347583, -0.013027, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.063319, 2.137552, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.965035, -0.396548, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.578446, -2.522109, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 151, "source", 0, -2.232492, 0.03301, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.051772, 2.183589, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.080127, -0.350511, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.463355, -2.476072, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 152, "source", 0, -2.186455, 0.079046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.097809, 2.229625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.126163, -0.304474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.417318, -2.430036, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 153, "source", 0, -2.186455, 0.079046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.097809, 2.229625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.126163, -0.304474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.417318, -2.430036, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 154, "source", 0, -2.163437, 0.079046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.120827, 2.229625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.149182, -0.304474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.3943, -2.430036, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 155, "source", 0, -2.163437, 0.079046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.120827, 2.229625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.149182, -0.304474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.3943, -2.430036, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 156, "source", 0, -2.163437, 0.079046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.120827, 2.229625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.149182, -0.304474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.3943, -2.430036, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 157, "source", 0, -2.25551, 0.079046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.028754, 2.229625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.057108, -0.304474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.486373, -2.430036, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 158, "source", 0, -2.39362, 0.056028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.109356, 2.206607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.918999, -0.327493, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.624483, -2.453054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 159, "source", 0, -2.416638, 0.056028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.132374, 2.206607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.895981, -0.327493, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.647501, -2.453054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 160, "source", 0, -2.531729, 0.056028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.247465, 2.206607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.780889, -0.327493, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.762592, -2.453054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 161, "source", 0, -2.623802, 0.056028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.339538, 2.206607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.688816, -0.327493, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.854666, -2.453054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 162, "source", 0, -2.692857, 0.056028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.408593, 2.206607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.619761, -0.327493, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.92372, -2.453054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 163, "source", 0, -2.692857, 0.056028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.408593, 2.206607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.619761, -0.327493, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.92372, -2.453054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 164, "source", 0, -2.692857, 0.056028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.408593, 2.206607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.619761, -0.327493, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.92372, -2.453054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 165, "source", 0, -2.692857, 0.056028, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.408593, 2.206607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.619761, -0.327493, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.92372, -2.453054, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 166, "source", 0, -2.715373, 0.056497, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.412694, 2.228752, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.641836, -0.331956, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.931657, -2.47413, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 167, "source", 0, -2.715373, 0.056497, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.412694, 2.228752, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.641836, -0.331956, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.931657, -2.47413, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 168, "source", 0, -2.757237, 0.057368, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.420317, 2.269924, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.682878, -0.340254, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.946413, -2.513316, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 169, "source", 0, -2.838336, 0.059055, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.435086, 2.349685, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.762385, -0.356329, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.974998, -2.589229, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 170, "source", 0, -2.930532, 0.060973, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.451877, 2.440359, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.852772, -0.374604, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.007496, -2.675529, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 171, "source", 0, -2.930532, 0.060973, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.451877, 2.440359, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.852772, -0.374604, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.007496, -2.675529, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 172, "source", 0, -3.012338, 0.062675, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.466775, 2.520816, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.932974, -0.39082, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.036331, -2.752104, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 173, "source", 0, -2.989405, 0.062198, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.462598, 2.498261, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.910491, -0.386274, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.028247, -2.730638, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 174, "source", 0, -2.815803, 0.058586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.430983, 2.327524, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.740295, -0.351863, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.967056, -2.568137, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 175, "source", 0, -2.731013, 0.056822, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.415542, 2.244133, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.657168, -0.335056, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.937169, -2.488769, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 176, "source", 0, -2.363345, 0.049172, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.348585, 1.882533, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.296715, -0.262177, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.807574, -2.144614, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 177, "source", 0, -2.231961, 0.046439, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.324658, 1.753317, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.167909, -0.236135, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.761264, -2.021631, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 178, "source", 0, -2.097343, 0.043638, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.300143, 1.620921, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.035932, -0.209451, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.713814, -1.895622, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 179, "source", 0, -1.938425, 0.040331, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.271202, 1.464625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.880132, -0.17795, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.657799, -1.746867, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 180, "source", 0, -1.436881, 0.029896, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.179864, 0.971358, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.388429, -0.078535, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.481015, -1.277396, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 181, "source", 0, -1.277807, 0.026586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.150895, 0.814908, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.232476, -0.047003, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.424945, -1.128494, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 182, "source", 0, -0.964381, 0.020065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.093816, 0.506655, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.314469, -0.835112, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 183, "source", 0, -0.827891, 0.017225, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.06896, 0.372417, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.266359, -0.70735, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 184, "source", 0, -0.827891, 0.017225, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.06896, 0.372417, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.266359, -0.70735, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 185, "source", 0, -0.827891, 0.017225, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.06896, 0.372417, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.266359, -0.70735, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 186, "source", 0, -0.761931, 0.015853, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.056948, 0.307546, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.24311, -0.645609, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 187, "source", 0, -0.740712, 0.015411, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.053083, 0.286676, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.23563, -0.625746, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 188, "source", 0, -0.816071, 0.016979, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.066807, 0.360792, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.073881, -0.014938, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.262193, -0.696286, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 189, "source", 0, -0.816071, 0.016979, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.066807, 0.360792, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.073881, -0.014938, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.262193, -0.696286, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 190, "source", 0, -0.899645, 0.018718, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.082027, 0.442987, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.155815, -0.031504, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.291651, -0.774515, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 191, "source", 0, -1.015593, 0.021131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.103143, 0.557022, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.269488, -0.054487, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.33252, -0.883049, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 192, "source", 0, -1.264134, 0.026302, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.148405, 0.801461, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.513152, -0.103752, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.420126, -1.115696, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 193, "source", 0, -1.727034, 0.035933, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.232705, 1.256722, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.966969, -0.195507, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.583288, -1.548994, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 194, "source", 0, -1.727034, 0.035933, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.232705, 1.256722, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.966969, -0.195507, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.583288, -1.548994, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 195, "source", 0, -2.119258, 0.044094, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.304134, 1.642474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.351498, -0.273254, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.721539, -1.916136, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 196, "source", 0, -2.326691, 0.04841, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.34191, 1.846484, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.554861, -0.314371, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.794655, -2.110304, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 197, "source", 0, -2.548921, 0.053033, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.382381, 2.065047, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.77273, -0.358421, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.872986, -2.318322, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 198, "source", 0, -3.16664, 0.065886, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.494875, 2.672572, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.378329, -0.480864, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.090719, -2.896539, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 199, "source", 0, -3.527483, 0.073394, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.560589, 3.02746, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.732091, -0.55239, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.217908, -3.234306, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 200, "source", 0, -3.527483, 0.073394, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.560589, 3.02746, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.732091, -0.55239, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.217908, -3.234306, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 201, "source", 0, -3.716657, 0.07733, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.59504, 3.213512, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.917553, -0.589888, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.284588, -3.411382, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 202, "source", 0, -3.85593, 0.080227, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.620403, 3.350486, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.054093, -0.617494, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.333679, -3.541749, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 203, "source", 0, -4.04166, 0.084092, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.654227, 3.533152, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.23618, -0.65431, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.399145, -3.715602, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 204, "source", 0, -3.950774, 0.082201, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.637675, 3.443766, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.147077, -0.636294, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.367109, -3.630528, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 205, "source", 0, -3.630344, 0.075534, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.579321, 3.128624, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.832934, -0.572779, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.254165, -3.33059, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 206, "source", 0, -3.003118, 0.062484, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.465095, 2.511748, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.218015, -0.448451, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.033081, -2.743473, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 207, "source", 0, -2.784876, 0.057943, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.425351, 2.297107, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.004055, -0.405191, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.956155, -2.539188, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 208, "source", 0, -2.329207, 0.048462, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.342368, 1.848958, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.557327, -0.314869, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.795541, -2.112659, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 209, "source", 0, -2.115346, 0.044012, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.303421, 1.638626, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.347662, -0.272478, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.72016, -1.912474, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 210, "source", 0, -1.913409, 0.039811, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.266646, 1.440022, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.149688, -0.232451, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.648981, -1.723451, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 211, "source", 0, -1.495048, 0.031106, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.190457, 1.028564, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.739535, -0.149523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.501518, -1.331843, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 212, "source", 0, -1.495048, 0.031106, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.190457, 1.028564, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.739535, -0.149523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.501518, -1.331843, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 213, "source", 0, -1.495048, 0.031106, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.190457, 1.028564, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.739535, -0.149523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.501518, -1.331843, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 214, "source", 0, -1.495048, 0.031106, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.190457, 1.028564, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.739535, -0.149523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.501518, -1.331843, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 215, "source", 0, -1.495048, 0.031106, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.190457, 1.028564, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.739535, -0.149523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.501518, -1.331843, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 216, "source", 0, -1.495048, 0.031106, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.190457, 1.028564, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.739535, -0.149523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.501518, -1.331843, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 217, "source", 0, -1.495048, 0.031106, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.190457, 1.028564, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.739535, -0.149523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.501518, -1.331843, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 218, "source", 0, -1.344173, 0.027967, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.162981, 0.880179, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.591621, -0.119617, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.448338, -1.190617, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 219, "source", 0, -1.344173, 0.027967, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.162981, 0.880179, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.591621, -0.119617, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.448338, -1.190617, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 220, "source", 0, -1.236265, 0.045048, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.055073, 0.89726, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.699529, -0.102537, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.34043, -1.173536, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 221, "source", 0, -1.236265, 0.045048, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.055073, 0.89726, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.699529, -0.102537, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.34043, -1.173536, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 222, "source", 0, -1.236265, 0.045048, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.055073, 0.89726, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.699529, -0.102537, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.34043, -1.173536, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 223, "source", 0, -1.236265, 0.045048, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.055073, 0.89726, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.699529, -0.102537, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.34043, -1.173536, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 224, "source", 0, -1.236265, 0.045048, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.055073, 0.89726, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.699529, -0.102537, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.34043, -1.173536, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 225, "source", 0, -1.236265, 0.045048, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.055073, 0.89726, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.699529, -0.102537, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.34043, -1.173536, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 226, "source", 0, -1.234455, 0.080643, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.029202, 0.898474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.696285, -0.122646, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.374096, -1.163242, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 227, "source", 0, -1.223469, 0.183047, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.045635, 0.89779, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.68367, -0.180139, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.469559, -1.128093, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 228, "source", 0, -1.133991, 0.494414, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.277159, 0.855156, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.613458, -0.35146, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.746339, -0.9675, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 229, "source", 0, -1.089683, 0.585638, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.346274, 0.82958, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.582608, -0.400527, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.823079, -0.903117, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 230, "source", 0, -1.039057, 0.671374, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.411868, 0.799046, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.54851, -0.446084, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.893043, -0.833999, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 231, "source", 0, -0.864106, 0.88527, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.578961, 0.687687, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.435807, -0.556711, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.055891, -0.614959, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 232, "source", 0, -0.74285, 0.989219, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.662734, 0.607365, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.360451, -0.608218, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.126319, -0.473798, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 233, "source", 0, -0.472221, 1.143411, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.793433, 0.422578, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.197107, -0.678972, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.208962, -0.177452, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 234, "source", 0, -0.220694, 1.217241, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.86466, 0.245909, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.049617, -0.705261, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.219211, 0.081269, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 235, "source", 0, 0.533134, 1.116311, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.845114, -0.306415, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.372357, -0.601003, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.941251, 0.779182, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 236, "source", 0, 0.909818, 0.83822, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.670707, -0.598549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.569045, -0.419573, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.584257, 1.073183, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 237, "source", 0, 1.028873, 0.686878, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.569697, -0.69538, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.627262, -0.326184, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.41064, 1.150849, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 238, "source", 0, 1.108406, 0.54938, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.475897, -0.762647, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.663888, -0.24312, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.259789, 1.19398, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 239, "source", 0, 1.197853, 0.30908, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.308455, -0.844372, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.699747, -0.101037, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.008069, 1.22189, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 240, "source", 0, 1.197853, 0.30908, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.308455, -0.844372, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.699747, -0.101037, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.008069, 1.22189, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 241, "source", 0, 1.155802, -0.441025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.237002, -0.867144, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.629171, 0.322487, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.700437, 1.001233, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 242, "source", 0, 0.862828, -0.886516, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.579952, -0.686851, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.435003, 0.557339, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.056777, 0.613435, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 243, "source", 0, 0.543186, -1.111454, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.765291, -0.471634, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.239412, 0.665234, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.195411, 0.253123, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 244, "source", 0, 0.249649, -1.211634, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.858552, -0.266452, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.066416, 0.703877, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.220802, -0.052181, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 245, "source", 0, 0.006882, -1.237067, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.894158, -0.092685, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.073085, 0.703216, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.186791, -0.290873, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 246, "source", 0, -0.488584, -1.136515, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.856568, 0.272764, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.348305, 0.615254, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.971321, -0.741361, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 247, "source", 0, -0.790651, -0.951448, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.744144, 0.50434, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.508393, 0.491315, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.721386, -0.986246, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 248, "source", 0, -1.125854, -0.512674, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.450589, 0.777868, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.671515, 0.221182, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.220429, -1.20187, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 249, "source", 0, -1.199598, -0.302236, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.303629, 0.846119, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.700312, 0.09704, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.001093, -1.221916, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 250, "source", 0, -1.233601, -0.092789, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.154567, 0.885561, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.706594, -0.024065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.207739, -1.204128, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 251, "source", 0, -1.224294, 0.177444, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.041524, 0.897989, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.684487, -0.177007, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.46439, -1.130231, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 252, "source", 0, -1.084787, 0.594658, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.353144, 0.826679, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.579265, -0.405347, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.830543, -0.896257, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 253, "source", 0, -1.001526, 0.726173, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.454159, 0.775789, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.523779, -0.474879, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.936516, -0.784867, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 254, "source", 0, -0.751301, 0.982816, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.657504, 0.613023, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.36565, -0.605107, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.122217, -0.483434, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 255, "source", 0, -0.751301, 0.982816, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.657504, 0.613023, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.36565, -0.605107, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.122217, -0.483434, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 256, "source", 0, 0.088925, 1.233886, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.89865, 0.023172, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.127316, -0.695446, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.160705, 0.381893, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 257, "source", 0, 0.348457, 1.186996, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.88314, -0.167845, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.27184, -0.652654, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.053377, 0.619255, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 258, "source", 0, 0.50366, 1.129915, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.852863, -0.284135, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.356459, -0.610566, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.961372, 0.754217, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 259, "source", 0, 0.648413, 1.053538, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.80789, -0.394236, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.433941, -0.558166, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.853393, 0.874528, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 260, "source", 0, 0.725545, 1.001981, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.776074, -0.453672, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.474551, -0.524076, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.785454, 0.936024, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 261, "source", 0, 0.738345, 0.992586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.770187, -0.463596, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.481238, -0.517942, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.773375, 0.946028, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 262, "source", 0, 0.803732, 0.940423, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.737098, -0.514582, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.515139, -0.484238, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.707679, 0.996127, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 263, "source", 0, 0.874509, 0.874995, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.694799, -0.570406, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.551275, -0.442663, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.627979, 1.0482, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 264, "source", 0, 0.937313, 0.807358, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.650336, -0.620622, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.582745, -0.400329, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.548079, 1.092103, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 265, "source", 0, 0.974687, 0.761818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.620052, -0.65088, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.601143, -0.372131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.495464, 1.116958, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 266, "source", 0, 0.974687, 0.761818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.620052, -0.65088, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.601143, -0.372131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.495464, 1.116958, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 267, "source", 0, 0.974687, 0.761818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.620052, -0.65088, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.601143, -0.372131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.495464, 1.116958, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 268, "source", 0, 0.974687, 0.761818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.620052, -0.65088, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.601143, -0.372131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.495464, 1.116958, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 269, "source", 0, 0.974687, 0.761818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.620052, -0.65088, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.601143, -0.372131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.495464, 1.116958, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 270, "source", 0, 0.974687, 0.761818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.620052, -0.65088, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.601143, -0.372131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.495464, 1.116958, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 271, "source", 0, 0.977196, 0.763779, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.622248, -0.653185, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.60385, -0.373807, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.496755, 1.119869, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 272, "source", 0, 1.072338, 0.838143, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.70554, -0.740618, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.706526, -0.437367, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.545719, 1.230253, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 273, "source", 0, 1.236876, 0.966746, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.849583, -0.891823, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.88409, -0.547286, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.630397, 1.421147, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 274, "source", 0, 1.427273, 1.11556, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.016265, -1.066791, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.089561, -0.674481, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.728383, 1.642045, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 275, "source", 0, 1.656467, 1.294699, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.216912, -1.277414, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.336901, -0.827594, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.846337, 1.907954, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 276, "source", 0, 1.77282, 1.385641, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.318772, -1.384338, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.462466, -0.905324, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.906217, 2.042946, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 277, "source", 0, 1.894344, 1.480625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.42516, -1.496015, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.593611, -0.986508, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.968758, 2.183937, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 278, "source", 0, 2.163328, 1.690863, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.66064, -1.743203, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.883891, -1.166202, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.107188, 2.496011, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 279, "source", 0, 2.295137, 1.793885, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.776031, -1.864331, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.026135, -1.254257, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.175023, 2.648934, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 280, "source", 0, 2.430104, 1.899376, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.894186, -1.988361, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.171788, -1.344422, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.244482, 2.805521, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 281, "source", 0, 2.563529, 2.003661, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.010993, -2.110974, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.315777, -1.433556, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.313148, 2.96032, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 282, "source", 0, 2.563529, 2.003661, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.010993, -2.110974, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.315777, -1.433556, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.313148, 2.96032, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 283, "source", 0, 2.699861, 2.110219, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.130343, -2.236259, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.462902, -1.524633, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.383311, 3.118492, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 284, "source", 0, 2.834658, 2.215577, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.248351, -2.360134, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.608372, -1.614684, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.452683, 3.274883, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 285, "source", 0, 2.834658, 2.215577, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.248351, -2.360134, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.608372, -1.614684, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.452683, 3.274883, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 286, "source", 0, 2.834658, 2.215577, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.248351, -2.360134, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.608372, -1.614684, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.452683, 3.274883, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 287, "source", 0, 2.834658, 2.215577, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.248351, -2.360134, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.608372, -1.614684, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.452683, 3.274883, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 288, "source", 0, 2.834658, 2.215577, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.248351, -2.360134, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.608372, -1.614684, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.452683, 3.274883, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 289, "source", 0, 3.057677, 2.389889, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.443592, -2.565081, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.849048, -1.763672, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.567458, 3.533628, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 290, "source", 0, 3.084681, 2.410995, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.467232, -2.589896, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.878189, -1.781712, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.581355, 3.564957, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 291, "source", 0, 3.003762, 2.347749, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.396392, -2.515535, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.790865, -1.727654, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.539711, 3.471076, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 292, "source", 0, 2.960052, 2.313585, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.358126, -2.475367, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.743694, -1.698454, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.517216, 3.420364, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 293, "source", 0, 2.89522, 2.262912, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.301369, -2.415788, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.673728, -1.655142, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.48385, 3.345145, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 294, "source", 0, 2.561529, 2.002099, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.009242, -2.109137, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.313619, -1.432221, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.31212, 2.958001, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 295, "source", 0, 2.335725, 1.825609, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.811563, -1.90163, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.069937, -1.281372, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.195911, 2.696024, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 296, "source", 0, 2.075186, 1.621971, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.583476, -1.662203, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.788771, -1.107319, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.061827, 2.393749, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 297, "source", 0, 1.828795, 1.429391, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.367775, -1.435777, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.522872, -0.942717, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.935024, 2.107887, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 298, "source", 0, 1.556586, 1.216632, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.129472, -1.185626, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.229113, -0.760869, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.794934, 1.792073, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 299, "source", 0, 1.432259, 1.119458, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.02063, -1.071373, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.094942, -0.677812, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.73095, 1.647829, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 300, "source", 0, 1.233333, 0.963977, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.846482, -0.888567, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.880267, -0.54492, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.628574, 1.417037, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 301, "source", 0, 1.029335, 0.804532, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.667894, -0.7011, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.660118, -0.408639, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.523588, 1.180361, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 302, "source", 0, 1.033372, 0.807686, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.671427, -0.704809, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.664474, -0.411335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.525665, 1.185043, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 303, "source", 0, 1.085243, 0.848229, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.716838, -0.752477, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.720452, -0.445988, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.552361, 1.245224, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 304, "source", 0, 1.215192, 0.949797, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.8306, -0.871896, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.860689, -0.5328, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.619238, 1.39599, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 305, "source", 0, 1.437262, 1.123368, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.02501, -1.075971, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.100341, -0.681154, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.733524, 1.653634, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 306, "source", 0, 1.437262, 1.123368, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.02501, -1.075971, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.100341, -0.681154, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.733524, 1.653634, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 307, "source", 0, 1.55184, 1.212923, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.125317, -1.181265, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.223991, -0.757698, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.792491, 1.786567, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 308, "source", 0, 1.575278, 1.231242, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.145835, -1.202804, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.249284, -0.773356, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.804553, 1.813759, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 309, "source", 0, 1.588867, 1.241863, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.157732, -1.215292, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.263949, -0.782434, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.811547, 1.829525, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 310, "source", 0, 1.588867, 1.241863, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.157732, -1.215292, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.263949, -0.782434, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.811547, 1.829525, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 311, "source", 0, 1.551673, 1.212792, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.125171, -1.181111, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.22381, -0.757586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.792405, 1.786373, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 312, "source", 0, 1.459912, 1.141072, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.044839, -1.096786, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.124785, -0.696286, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.745181, 1.679913, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 313, "source", 0, 1.211426, 0.946854, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.827304, -0.868435, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.856625, -0.530285, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.6173, 1.391621, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 314, "source", 0, 1.211426, 0.946854, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.827304, -0.868435, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.856625, -0.530285, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.6173, 1.391621, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 315, "source", 0, 0.857299, 0.670068, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.517286, -0.543004, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.474461, -0.29371, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.435051, 0.980766, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 316, "source", 0, 0.629248, 0.491822, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.31764, -0.333433, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.228355, -0.141361, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.317687, 0.716183, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 317, "source", 0, 0.452745, 0.353866, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.163121, -0.171231, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.037877, -0.023448, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.22685, 0.511404, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 318, "source", 0, 0.333554, 0.260707, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.058777, -0.061699, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.16551, 0.373121, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 319, "source", 0, 0.332841, 0.260149, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.058152, -0.061043, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.165143, 0.372293, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 320, "source", 0, 0.332841, 0.260149, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.058152, -0.061043, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.165143, 0.372293, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 321, "source", 0, 0.328518, 0.256771, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.054368, -0.057071, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.162918, 0.367278, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 322, "source", 0, 0.303264, 0.237032, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.03226, -0.033864, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.149922, 0.337978, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 323, "source", 0, 0.229196, 0.17914, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.111803, 0.252044, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 324, "source", 0, 0.242585, 0.189605, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.013209, -0.013866, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.016283, -0.01008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.118693, 0.267579, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 325, "source", 0, 0.357612, 0.27951, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.113908, -0.119571, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.140416, -0.086923, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.177891, 0.401032, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 326, "source", 0, 0.425359, 0.332462, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.173217, -0.181829, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.213528, -0.132182, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.212757, 0.479632, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 327, "source", 0, 0.425359, 0.332462, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.173217, -0.181829, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.213528, -0.132182, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.212757, 0.479632, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 328, "source", 0, 0.425359, 0.332462, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.173217, -0.181829, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.213528, -0.132182, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.212757, 0.479632, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 329, "source", 0, 0.733511, 0.573314, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.442986, -0.465011, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.546076, -0.338042, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.371344, 0.837147, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 330, "source", 0, 0.733511, 0.573314, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.442986, -0.465011, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.546076, -0.338042, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.371344, 0.837147, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 331, "source", 0, 1.202727, 0.940055, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.853759, -0.896205, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.052441, -0.651502, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.612823, 1.381528, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 332, "source", 0, 1.38877, 1.085467, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.016629, -1.067173, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.253214, -0.775788, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.708568, 1.597374, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 333, "source", 0, 1.598147, 1.249116, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.199926, -1.259584, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.479168, -0.915663, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.816323, 1.840292, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 334, "source", 0, 2.056843, 1.607634, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.601488, -1.681111, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.974179, -1.222094, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.052387, 2.372467, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 335, "source", 0, 2.299713, 1.797462, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.814107, -1.9043, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.236278, -1.384343, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.177378, 2.654243, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 336, "source", 0, 2.538708, 1.984261, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.023334, -2.123929, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.494195, -1.544004, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.300375, 2.931523, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 337, "source", 0, 3.00645, 2.34985, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.432816, -2.55377, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.998969, -1.856479, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.541095, 3.474195, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 338, "source", 0, 3.235816, 2.529123, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.633613, -2.764549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.246495, -2.009707, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.659136, 3.740303, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 339, "source", 0, 3.235816, 2.529123, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.633613, -2.764549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.246495, -2.009707, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.659136, 3.740303, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 340, "source", 0, 2.768323, 3.033704, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.058074, -2.286227, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.865542, -2.523355, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.260117, 3.410934, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 341, "source", 0, 2.768323, 3.033704, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.058074, -2.286227, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.865542, -2.523355, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.260117, 3.410934, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 342, "source", 0, 2.768323, 3.033704, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.058074, -2.286227, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.865542, -2.523355, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.260117, 3.410934, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 343, "source", 0, 2.768323, 3.033704, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.058074, -2.286227, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.865542, -2.523355, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.260117, 3.410934, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 344, "source", 0, 2.596188, 3.18226, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.179912, -2.113482, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.721502, -2.678074, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.445422, 3.280626, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 345, "source", 0, 2.375561, 3.350176, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.315265, -1.894114, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.534607, -2.855594, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.661197, 3.108155, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 346, "source", 0, 2.039432, 3.564785, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.483343, -1.56364, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.245697, -3.08796, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -2.950108, 2.835395, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 347, "source", 0, 1.757838, 3.711735, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.593767, -1.289763, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.000336, -3.252277, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -3.160411, 2.598924, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 348, "source", 0, 0.449354, 4.082285, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.817929, -0.045465, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.828599, -3.727207, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -3.835853, 1.42437, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 349, "source", 0, 0.449354, 4.082285, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.817929, -0.045465, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.828599, -3.727207, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -3.835853, 1.42437, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 350, "source", 0, -0.661623, 4.053298, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.690332, 0.979846, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.201061, -3.812902, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.077306, 0.343767, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 351, "source", 0, -1.054315, 3.969306, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.576997, 1.335569, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.572477, -3.775039, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.091388, -0.056076, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 352, "source", 0, -1.258736, 3.909291, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.502924, 1.519267, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.767473, -3.740272, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.082975, -0.268171, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 353, "source", 0, -1.664436, 3.754547, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.322945, 1.880607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.158073, -3.63834, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.031842, -0.697744, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 354, "source", 0, -1.76455, 3.708549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.271304, 1.969067, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.255253, -3.605966, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.011675, -0.805645, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 355, "source", 0, -2.288284, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.74757, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.731519, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.535409, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 356, "source", 0, -2.412928, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.622926, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.606875, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.660053, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 357, "source", 0, -2.454476, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.581378, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.565327, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.701601, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 358, "source", 0, -2.496024, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.53983, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.523779, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.743148, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 359, "source", 0, -2.620667, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.415186, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.399136, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.867792, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 360, "source", 0, -2.662215, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.373639, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.357588, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.90934, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 361, "source", 0, -2.745311, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.290543, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.274492, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.992436, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 362, "source", 0, -2.911502, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.124351, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.1083, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -5.158628, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 363, "source", 0, -2.95305, 4.15549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.082803, 2.416008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.066752, -3.159025, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -5.200175, -0.358703, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 364, "source", 0, -3.368529, 4.280134, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.667325, 2.540652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.348726, -3.034381, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -5.615654, -0.23406, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 365, "source", 0, -3.493173, 4.321681, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.542681, 2.582199, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.47337, -2.992833, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -5.740298, -0.192512, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 366, "source", 0, -3.825556, 4.446325, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.210298, 2.706843, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.805753, -2.86819, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.072681, -0.067868, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 367, "source", 0, -4.033295, 4.529421, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.002558, 2.789939, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.013493, -2.785094, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.28042, 0.015228, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 368, "source", 0, -4.157939, 4.570969, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.877915, 2.831487, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.138136, -2.743546, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.405064, 0.056775, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 369, "source", 0, -4.448774, 4.737161, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.587079, 2.997678, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.428972, -2.577354, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.695899, 0.222967, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 370, "source", 0, -4.53187, 4.778708, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.503984, 3.039226, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.512067, -2.535806, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.778995, 0.264515, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 371, "source", 0, -4.573418, 4.820256, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.462436, 3.080774, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.553615, -2.494259, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.820543, 0.306063, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 372, "source", 0, -4.698061, 4.903352, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.337792, 3.16387, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.678259, -2.411163, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.945187, 0.389159, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 373, "source", 0, -4.698061, 4.903352, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.337792, 3.16387, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.678259, -2.411163, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.945187, 0.389159, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 374, "source", 0, -4.698061, 4.861804, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.337792, 3.122322, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.678259, -2.452711, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.945187, 0.347611, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 375, "source", 0, -4.656514, 4.737161, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.37934, 2.997678, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.636711, -2.577354, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.903638, 0.222967, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 376, "source", 0, -4.573418, 4.695612, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.462436, 2.95613, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.553615, -2.618902, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.820543, 0.181419, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 377, "source", 0, -4.116391, 4.36323, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.919463, 2.623747, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.096588, -2.951285, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.363516, -0.150964, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 378, "source", 0, -3.908652, 4.280134, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.127202, 2.540652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.888849, -3.034381, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -6.155777, -0.23406, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 379, "source", 0, -3.659364, 4.113942, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.376489, 2.37446, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.639562, -3.200572, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -5.906489, -0.400251, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 380, "source", 0, -3.16079, 3.864655, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.875064, 2.125173, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.140987, -3.44986, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -5.407915, -0.649539, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 381, "source", 0, -2.869955, 3.656915, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.165899, 1.917433, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.149848, -3.657599, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -5.117079, -0.857278, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 382, "source", 0, -2.662215, 3.57382, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.373639, 1.834337, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.357588, -3.740695, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.90934, -0.940374, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 383, "source", 0, -2.63218, 3.389235, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.468553, 1.850359, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.674658, -3.800073, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.698941, -1.210332, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 384, "source", 0, -2.624509, 3.395179, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.472731, 1.844772, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.666063, -3.801589, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.701666, -1.199702, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 385, "source", 0, -2.908046, 3.155718, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.304091, 2.051523, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.992039, -3.729823, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.580426, -1.601452, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 386, "source", 0, -2.912678, 3.151443, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.301075, 2.054905, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.997516, -3.728362, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.578069, -1.608178, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 387, "source", 0, -3.091563, 2.976159, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.177279, 2.185644, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.213319, -3.66382, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.476456, -1.87251, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 388, "source", 0, -3.326102, 2.711518, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.989938, 2.357484, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.510851, -3.551486, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -4.307089, -2.234711, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 389, "source", 0, -3.73045, 2.121092, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.570508, 2.655389, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.080022, -3.251035, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -3.875843, -2.919382, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 390, "source", 0, -4.022638, 1.494546, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.123736, 2.873117, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.57507, -2.874846, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -3.356765, -3.503866, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 391, "source", 0, -4.290889, -0.05968, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.009848, 3.085042, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.43976, -1.750364, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.864182, -4.47993, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 392, "source", 0, -4.178222, -0.978647, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.652094, 3.015354, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.73514, -0.971829, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.859891, -4.775514, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 393, "source", 0, -3.662372, -2.236587, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.562647, 2.660022, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.851688, 0.245396, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.677173, -4.804829, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 394, "source", 0, -3.635185, -2.280508, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.594552, 2.64102, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.848455, 0.29174, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.734958, -4.79633, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 395, "source", 0, -3.460863, -2.537266, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.781254, 2.518873, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.817307, 0.569112, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.079676, -4.730671, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 396, "source", 0, -3.266011, -2.783606, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.960719, 2.38184, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.765456, 0.846795, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.422797, -4.63903, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 397, "source", 0, -3.266011, -2.783606, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.960719, 2.38184, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.765456, 0.846795, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.422797, -4.63903, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 398, "source", 0, -3.266011, -2.783606, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.960719, 2.38184, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.765456, 0.846795, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.422797, -4.63903, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 399, "source", 0, -3.261585, -2.342744, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.956293, 2.822703, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.769882, 1.287657, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.427222, -4.198168, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 400, "source", 0, -3.261585, -2.467387, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.956293, 2.698059, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.769882, 1.163013, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.427222, -4.322811, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 401, "source", 0, -3.261585, -2.550483, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.956293, 2.614963, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.769882, 1.079918, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.427222, -4.405907, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 402, "source", 0, -3.220037, -2.841318, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.914746, 2.324128, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.81143, 0.789082, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.46877, -4.696742, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 403, "source", 0, -3.178489, -2.924414, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.873198, 2.241032, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.852978, 0.705987, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.510318, -4.779838, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 404, "source", 0, -3.053845, -3.339893, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.748554, 1.825553, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.977621, 0.290508, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.634962, -5.195317, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 405, "source", 0, -3.053845, -3.464537, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.748554, 1.70091, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.977621, 0.165864, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.634962, -5.319961, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 406, "source", 0, -3.012298, -3.672276, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.707006, 1.49317, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.019169, -0.041875, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.67651, -5.5277, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 407, "source", 0, -2.887654, -4.004659, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.582362, 1.160787, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.143813, -0.374258, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.801154, -5.860083, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 408, "source", 0, -2.804558, -4.212399, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.499267, 0.953048, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.226909, -0.581998, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.884249, -6.067822, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 409, "source", 0, -2.721462, -4.37859, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.416171, 0.786856, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.310004, -0.748189, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.967345, -6.234014, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 410, "source", 0, -2.679914, -4.420138, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.374623, 0.745308, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.351552, -0.789737, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.008893, -6.275562, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 411, "source", 0, -2.679914, -4.420138, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.374623, 0.745308, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.351552, -0.789737, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.008893, -6.275562, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 412, "source", 0, -2.679914, -4.37859, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.374623, 0.786856, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.351552, -0.748189, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.008893, -6.234014, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 413, "source", 0, -2.679914, -4.295495, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.374623, 0.869952, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.351552, -0.665094, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.008893, -6.150918, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 414, "source", 0, -2.721462, -4.170851, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.416171, 0.994596, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.310004, -0.54045, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.967345, -6.026275, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 415, "source", 0, -2.846106, -4.046207, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.540815, 1.119239, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.185361, -0.415806, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.842701, -5.901631, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 416, "source", 0, -2.887654, -3.921563, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.582362, 1.243883, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.143813, -0.291163, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.801154, -5.776988, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 417, "source", 0, -2.97075, -3.755372, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.665458, 1.410074, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.060717, -0.124971, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.718058, -5.610796, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 418, "source", 0, -3.095393, -3.506084, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.790102, 1.659362, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.936074, 0.124316, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.593414, -5.361508, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 419, "source", 0, -3.095393, -3.381441, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.790102, 1.784006, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.936074, 0.24896, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.593414, -5.236865, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 420, "source", 0, -3.095393, -3.173701, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.790102, 1.991745, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.936074, 0.456699, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.593414, -5.029125, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 421, "source", 0, -3.095393, -3.090605, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.790102, 2.074841, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.936074, 0.539795, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.593414, -4.94603, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 422, "source", 0, -3.083931, -3.102043, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.79777, 2.0682, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.934048, 0.554362, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.611712, -4.940097, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 423, "source", 0, -3.083931, -3.102043, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.79777, 2.0682, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.934048, 0.554362, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.611712, -4.940097, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 424, "source", 0, -3.071686, -3.114169, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.805905, 2.061101, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.931834, 0.569857, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.631163, -4.933709, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 425, "source", 0, -3.029365, -3.155353, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.833565, 2.036533, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.923782, 0.622885, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.69762, -4.911239, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 426, "source", 0, -2.774912, -3.381297, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.986329, 1.887836, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.863488, 0.926021, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.074265, -4.76441, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 427, "source", 0, -2.716951, -3.428043, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.018178, 1.85375, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.847165, 0.991654, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.155067, -4.72841, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 428, "source", 0, -2.545841, -3.556965, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.106524, 1.752708, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.793994, 1.178838, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.384005, -4.617218, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 429, "source", 0, -2.089552, -3.842795, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.3059, 1.480626, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.620422, 1.63603, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.933207, -4.289344, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 430, "source", 0, -1.506262, -4.106638, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.497322, 1.12819, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.342845, 2.14696, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 3.527883, -3.815262, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 431, "source", 0, -1.506262, -4.106638, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.497322, 1.12819, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.342845, 2.14696, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 3.527883, -3.815262, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 432, "source", 0, 0.201816, -4.369505, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.739363, 0.072914, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.250417, 3.274092, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 4.730205, -2.151125, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 433, "source", 0, 1.048293, -4.246691, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.70118, -0.461579, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.570231, 3.649442, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 5.058393, -1.189468, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 434, "source", 0, 1.807963, -3.983036, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.571042, -0.948247, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.875645, 3.875216, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 5.190659, -0.243398, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 435, "source", 0, 2.204555, -3.777994, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.46099, -1.205386, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.476065, 3.944289, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 5.188431, 0.286977, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 436, "source", 0, 2.765268, -3.389189, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.243593, -1.573442, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.143123, 3.970336, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 5.080678, 1.090364, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 437, "source", 0, 2.924087, -3.253155, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.16583, -1.678872, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.332713, 3.958959, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 5.02276, 1.331938, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 438, "source", 0, 3.075293, -3.110607, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.083649, -1.779841, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.520365, 3.938689, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 4.953833, 1.568987, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 439, "source", 0, 3.789764, -2.184259, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.537386, -2.268452, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.545694, 3.659902, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 4.360805, 2.825873, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 440, "source", 0, 3.875234, -2.02876, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.444119, -2.328937, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.692857, 3.594202, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 4.242607, 3.00041, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 441, "source", 0, 4.216193, -1.164913, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.919896, -2.581321, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.413493, 3.155805, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 3.513551, 3.828464, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 442, "source", 0, 4.29871, -0.808944, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.701237, -2.649093, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.668471, 2.943352, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 3.181749, 4.108363, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 443, "source", 0, 4.372762, -0.110696, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.268327, -2.727165, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.105048, 2.478453, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 2.483386, 4.564534, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 444, "source", 0, 4.336846, 0.570148, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.158716, -2.735734, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.452465, 1.965842, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.74392, 4.894989, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 445, "source", 0, 4.275251, 0.924947, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.383209, -2.713408, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.602468, 1.675195, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.335369, 5.021849, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 446, "source", 0, 4.225442, 1.130904, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.514164, -2.691666, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.679367, 1.498769, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.090604, 5.080626, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 447, "source", 0, 3.993373, 1.785014, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.933437, -2.576456, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.870113, 0.897929, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.273263, 5.189172, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 448, "source", 0, 3.846508, 2.082711, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.126135, -2.498249, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.927063, 0.601854, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.121044, 5.194952, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 449, "source", 0, 3.609113, 2.471357, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.379783, -2.367621, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.968356, 0.190282, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.660525, 5.15421, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 450, "source", 0, 3.426364, 2.719068, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.542882, -2.264717, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.971911, -0.089286, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.021388, 5.094992, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 4, 0, 1, 2, 3, 0, 0.2, 0.2, 0.2, 1.0, "" ],
					"zoom" : 0.243906
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 9,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 27.278564, 518.0, 140.059769, 20.0 ],
					"saved_object_attributes" : 					{
						"mode" : "cartesian",
						"ramp" : 100.0
					}
,
					"text" : "hoa.map~ 4 3"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-56",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 838.5, 308.5, 73.0, 19.0 ],
					"text" : "loadmess 0."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-57",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 707.5, 308.5, 79.0, 19.0 ],
					"text" : "loadmess 0.9"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-59",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 826.0, 174.5, 92.0, 19.0 ],
					"text" : "loadmess 3000."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-60",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 707.5, 174.5, 86.0, 19.0 ],
					"text" : "loadmess 400."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-84",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1345.0, 593.5, 128.0, 128.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 833.349976, 440.875, 382.5, 382.5 ],
					"shadow" : 2
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-100", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-86", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-115", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-115", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-115", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-115", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-115", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-115", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-115", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-115", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-115", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-112", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-40", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-40", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-40", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-40", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-40", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-40", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-40", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-40", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-40", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-114", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-114", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-115", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1236.875, 441.0, 1146.0, 441.0, 1146.0, 453.0, 1149.375, 453.0 ],
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 266.875, 672.5, 266.875, 672.5 ],
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-96", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-93", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 36.778564, 387.0, 12.0, 387.0, 12.0, 504.0, 36.778564, 504.0 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-86", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-100", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-23", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-71", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1245.5, 477.0, 1245.5, 477.0 ],
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-39", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-39", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-39", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-39", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-39", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-39", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-39", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-39", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-39", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-67", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-74", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-36", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-36", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-36", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-36", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-36", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-36", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-36", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-36", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-36", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-46", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 172.961868, 726.0, 1161.444885, 726.0 ],
					"source" : [ "obj-36", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 155.947885, 726.0, 1142.304161, 726.0 ],
					"source" : [ "obj-36", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 138.933903, 726.0, 1123.163437, 726.0 ],
					"source" : [ "obj-36", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 121.91992, 726.0, 1104.022713, 726.0 ],
					"source" : [ "obj-36", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 104.905937, 726.0, 1084.881989, 726.0 ],
					"source" : [ "obj-36", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 87.891954, 726.0, 1065.741264, 726.0 ],
					"source" : [ "obj-36", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 70.877972, 726.0, 1046.60054, 726.0 ],
					"source" : [ "obj-36", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 53.863989, 726.0, 1027.459816, 726.0 ],
					"source" : [ "obj-36", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 36.850006, 726.0, 1008.319092, 726.0 ],
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 172.961868, 726.0, 535.5, 726.0 ],
					"source" : [ "obj-36", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 155.947885, 726.0, 520.25, 726.0 ],
					"source" : [ "obj-36", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 138.933903, 726.0, 505.0, 726.0 ],
					"source" : [ "obj-36", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 121.91992, 726.0, 489.75, 726.0 ],
					"source" : [ "obj-36", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 104.905937, 726.0, 474.5, 726.0 ],
					"source" : [ "obj-36", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 87.891954, 726.0, 459.25, 726.0 ],
					"source" : [ "obj-36", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 70.877972, 726.0, 444.0, 726.0 ],
					"source" : [ "obj-36", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 53.863989, 726.0, 428.75, 726.0 ],
					"source" : [ "obj-36", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 36.850006, 726.0, 413.5, 726.0 ],
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 172.961868, 681.0, 985.281433, 681.0 ],
					"source" : [ "obj-36", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 155.947885, 681.0, 968.406433, 681.0 ],
					"source" : [ "obj-36", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 138.933903, 681.0, 951.531433, 681.0 ],
					"source" : [ "obj-36", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 121.91992, 681.0, 934.656433, 681.0 ],
					"source" : [ "obj-36", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 104.905937, 681.0, 917.781433, 681.0 ],
					"source" : [ "obj-36", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 87.891954, 681.0, 900.906433, 681.0 ],
					"source" : [ "obj-36", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 70.877972, 681.0, 884.031433, 681.0 ],
					"source" : [ "obj-36", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 53.863989, 681.0, 867.156433, 681.0 ],
					"source" : [ "obj-36", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 36.850006, 681.0, 850.281433, 681.0 ],
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 549.611862, 681.0, 1161.444885, 681.0 ],
					"source" : [ "obj-39", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-20", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 532.597879, 681.0, 1142.304161, 681.0 ],
					"source" : [ "obj-39", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 515.583897, 681.0, 1123.163437, 681.0 ],
					"source" : [ "obj-39", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-20", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 498.569914, 681.0, 1104.022713, 681.0 ],
					"source" : [ "obj-39", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 481.555931, 681.0, 1084.881989, 681.0 ],
					"source" : [ "obj-39", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-20", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 464.541948, 681.0, 1065.741264, 681.0 ],
					"source" : [ "obj-39", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 447.527965, 681.0, 1046.60054, 681.0 ],
					"source" : [ "obj-39", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-20", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 430.513983, 681.0, 1027.459816, 681.0 ],
					"source" : [ "obj-39", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 681.0, 1008.319092, 681.0 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 549.611862, 717.0, 535.5, 717.0 ],
					"source" : [ "obj-39", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 532.597879, 717.0, 520.25, 717.0 ],
					"source" : [ "obj-39", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 515.583897, 717.0, 505.0, 717.0 ],
					"source" : [ "obj-39", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 498.569914, 717.0, 489.75, 717.0 ],
					"source" : [ "obj-39", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 481.555931, 717.0, 474.5, 717.0 ],
					"source" : [ "obj-39", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 464.541948, 717.0, 459.25, 717.0 ],
					"source" : [ "obj-39", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 447.527965, 717.0, 444.0, 717.0 ],
					"source" : [ "obj-39", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 430.513983, 717.0, 428.75, 717.0 ],
					"source" : [ "obj-39", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 717.0, 413.5, 717.0 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 549.611862, 681.0, 985.281433, 681.0 ],
					"source" : [ "obj-39", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 532.597879, 681.0, 968.406433, 681.0 ],
					"source" : [ "obj-39", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 515.583897, 681.0, 951.531433, 681.0 ],
					"source" : [ "obj-39", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 498.569914, 681.0, 934.656433, 681.0 ],
					"source" : [ "obj-39", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 481.555931, 681.0, 917.781433, 681.0 ],
					"source" : [ "obj-39", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 464.541948, 681.0, 900.906433, 681.0 ],
					"source" : [ "obj-39", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 447.527965, 681.0, 884.031433, 681.0 ],
					"source" : [ "obj-39", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 430.513983, 681.0, 867.156433, 681.0 ],
					"source" : [ "obj-39", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 681.0, 850.281433, 681.0 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-112", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-20", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-20", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-20", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-20", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1161.444885, 681.0, 535.5, 681.0 ],
					"source" : [ "obj-40", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1142.304161, 681.0, 520.25, 681.0 ],
					"source" : [ "obj-40", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1123.163437, 681.0, 505.0, 681.0 ],
					"source" : [ "obj-40", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1104.022713, 681.0, 489.75, 681.0 ],
					"source" : [ "obj-40", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1084.881989, 681.0, 474.5, 681.0 ],
					"source" : [ "obj-40", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1065.741264, 681.0, 459.25, 681.0 ],
					"source" : [ "obj-40", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1046.60054, 681.0, 444.0, 681.0 ],
					"source" : [ "obj-40", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1027.459816, 681.0, 428.75, 681.0 ],
					"source" : [ "obj-40", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1008.319092, 681.0, 413.5, 681.0 ],
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1161.444885, 594.0, 985.281433, 594.0 ],
					"source" : [ "obj-40", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1142.304161, 594.0, 968.406433, 594.0 ],
					"source" : [ "obj-40", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1123.163437, 594.0, 951.531433, 594.0 ],
					"source" : [ "obj-40", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1104.022713, 594.0, 934.656433, 594.0 ],
					"source" : [ "obj-40", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1084.881989, 594.0, 917.781433, 594.0 ],
					"source" : [ "obj-40", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1065.741264, 594.0, 900.906433, 594.0 ],
					"source" : [ "obj-40", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1046.60054, 594.0, 884.031433, 594.0 ],
					"source" : [ "obj-40", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-6", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1027.459816, 594.0, 867.156433, 594.0 ],
					"source" : [ "obj-40", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1008.319092, 594.0, 850.281433, 594.0 ],
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-55", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-76", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-77", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-78", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-93", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-48", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-93", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-50", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-49", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 399.0, 413.5, 399.0 ],
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-93", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-55", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-56", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-67", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-57", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-58", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-59", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-74", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-64", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 848.0, 471.0, 558.0, 471.0, 558.0, 417.0, 474.0, 417.0, 474.0, 426.0, 413.5, 426.0 ],
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-68", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-67", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 717.0, 459.0, 558.0, 459.0, 558.0, 417.0, 474.0, 417.0, 474.0, 426.0, 413.5, 426.0 ],
					"source" : [ "obj-68", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 835.5, 366.0, 663.0, 366.0, 663.0, 417.0, 474.0, 417.0, 474.0, 426.0, 413.5, 426.0 ],
					"source" : [ "obj-71", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-75", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-74", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 717.0, 366.0, 663.0, 366.0, 663.0, 417.0, 474.0, 417.0, 474.0, 426.0, 413.5, 426.0 ],
					"source" : [ "obj-75", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-108", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 78.0, 984.0, 78.0, 984.0, 51.0, 1236.875, 51.0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 69.0, 413.5, 69.0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 84.0, 717.0, 84.0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 84.0, 390.0, 84.0, 390.0, 681.0, 656.0896, 681.0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-91", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 413.5, 84.0, 36.778564, 84.0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-82", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-85", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-88", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-90", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-91", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-92", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-97", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-93", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-88", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-96", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-97", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-76", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-97", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-77", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-97", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-78", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-97", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-98", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-99", 0 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "hoa.plug~.maxref.xml",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_prerelease/max-package/docs/refpages/hoa-ref",
				"patcherrelativepath" : "../../_prerelease/max-package/docs/refpages/hoa-ref",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.granular~.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_prerelease/max-package/patchers/effects",
				"patcherrelativepath" : "../../_prerelease/max-package/patchers/effects",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.soundcoat.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_prerelease/max-package/misc/others",
				"patcherrelativepath" : "../../_prerelease/max-package/misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "littlefilter~.maxpat",
				"bootpath" : "/Applications/Max 6.1/patches/docs/tutorial-patchers/msp-tut",
				"patcherrelativepath" : "../../../../../../../../../Applications/Max 6.1/patches/docs/tutorial-patchers/msp-tut",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.soundgrain.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_prerelease/max-package/misc/others",
				"patcherrelativepath" : "../../_prerelease/max-package/misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "fensrecomp.json",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_projects/Futur_en_Seine_2013",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.decorrelation~.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_prerelease/max-package/patchers/effects",
				"patcherrelativepath" : "../../_prerelease/max-package/patchers/effects",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.map~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.map.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.decoder~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.freeverb~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.space.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.scope~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.space~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.projector~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.recomposer~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.plug~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.recomposer.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.gain~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.meter~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.connect.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.encoder~.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
