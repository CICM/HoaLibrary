{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 269.0, 44.0, 807.0, 705.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 269.0, 44.0, 807.0, 705.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 14.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "hoa.map",
					"numinlets" : 1,
					"patching_rect" : [ 15.0, 165.0, 447.0, 447.0 ],
					"numoutlets" : 2,
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"id" : "obj-1",
					"fontname" : "Arial",
					"textcolor" : [  ],
					"outlettype" : [ "list", "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
					"linecount" : 2,
					"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 514.0, 11.0, 257.0, 33.0 ],
					"numoutlets" : 0,
					"id" : "obj-15",
					"fontname" : "Arial",
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"shadow" : -1,
					"numinlets" : 1,
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"patching_rect" : [ 514.0, 11.0, 257.0, 32.0 ],
					"numoutlets" : 0,
					"id" : "obj-17",
					"rounded" : 6,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"args" : [ "@obj-name", "hoa.map", "@obj-desc", "A", "2D", "spatialization", "graphic", "user", "interface", "tool" ],
					"numinlets" : 1,
					"patching_rect" : [ 5.5, 4.5, 483.0, 56.0 ],
					"numoutlets" : 0,
					"id" : "obj-19",
					"name" : "hoa.helpheader.maxpat"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[1]",
					"text" : "hoa.map allow you to spatialize several point sources.\nYou can control sources with a list of value in the first inlet, zoom in/out, add or remove loudspeakers, modify the distance between listener and loudspeaker... ",
					"linecount" : 3,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 5.5, 69.5, 483.0, 48.0 ],
					"numoutlets" : 0,
					"id" : "obj-42",
					"fontname" : "Arial",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"shadow" : -1,
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 5.5, 69.5, 483.0, 47.0 ],
					"numoutlets" : 0,
					"id" : "obj-44",
					"rounded" : 15,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p ex.multi",
					"numinlets" : 0,
					"patching_rect" : [ 596.5, 628.5, 70.0, 23.0 ],
					"numoutlets" : 0,
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"id" : "obj-13",
					"fontname" : "Arial",
					"fontsize" : 14.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 269.0, 70.0, 807.0, 679.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 269.0, 70.0, 807.0, 679.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 1,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "switch off presentation mode to see how it works",
									"linecount" : 2,
									"frgb" : [ 0.255102, 0.255102, 0.255102, 1.0 ],
									"presentation_rect" : [ 143.0, 646.560364, 320.0, 23.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 575.0, 558.0, 178.0, 39.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-68",
									"fontname" : "Arial",
									"textcolor" : [ 0.255102, 0.255102, 0.255102, 1.0 ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"presentation_rect" : [ 143.0, 646.560364, 320.0, 22.0 ],
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 679.0, 455.0, 70.0, 84.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-67",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 176.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 501.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-62",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 175.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 500.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-63",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 335.0, 214.0, 6.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 547.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-57",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 334.0, 214.0, 6.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 546.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-58",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 244.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 486.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-60",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 243.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 485.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-61",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 629.0, 214.0, 6.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 547.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-53",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 628.0, 214.0, 6.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 546.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-54",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 583.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 486.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-55",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 582.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 485.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-56",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 534.0, 214.0, 6.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 532.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-49",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 533.0, 214.0, 6.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 531.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-50",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 488.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 471.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-51",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 487.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 470.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-52",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 440.0, 214.0, 6.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 517.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-41",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 439.0, 214.0, 6.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 516.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-42",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 585.0, 394.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 456.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-39",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 584.0, 393.0, 214.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 455.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-40",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 13.5, 55.0, 782.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 439.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-37",
									"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "live.line",
									"presentation_rect" : [ 12.5, 54.0, 782.0, 5.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 649.0, 438.0, 5.0, 5.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-38",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "turn dac~ on",
									"frgb" : [ 0.326531, 0.326531, 0.326531, 1.0 ],
									"presentation_rect" : [ 638.5, 109.956909, 112.0, 23.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 425.5, 606.793091, 112.0, 23.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-21",
									"fontname" : "Arial",
									"textcolor" : [ 0.326531, 0.326531, 0.326531, 1.0 ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"presentation_rect" : [ 586.0, 87.956909, 44.0, 44.0 ],
									"numinlets" : 2,
									"patching_rect" : [ 373.0, 584.793091, 44.0, 44.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-22",
									"local" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"presentation_rect" : [ 580.0, 77.206909, 181.0, 63.75 ],
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 367.0, 574.043091, 181.0, 63.75 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-26",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 660.0, 602.5, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-4",
									"fontname" : "Arial",
									"hidden" : 1,
									"fontsize" : 7.180877
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Exemple : multiple source spatialization with distance compensation.",
									"presentation_rect" : [ 13.5, 15.0, 435.0, 23.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 116.75, 16.746368, 437.0, 23.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-10",
									"fontname" : "Arial",
									"underline" : 1,
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "<= look inside to see how it works.",
									"numinlets" : 1,
									"patching_rect" : [ 367.0, 519.746338, 224.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-19",
									"fontname" : "Arial",
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "speakers to head distance in meters",
									"linecount" : 2,
									"presentation_linecount" : 3,
									"frgb" : [ 0.255102, 0.255102, 0.255102, 1.0 ],
									"presentation_rect" : [ 637.0, 264.706909, 114.0, 55.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 625.0, 35.5, 178.0, 39.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-13",
									"fontname" : "Arial",
									"textcolor" : [ 0.255102, 0.255102, 0.255102, 1.0 ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.optim~ 7 inPhase",
									"numinlets" : 15,
									"patching_rect" : [ 14.5, 554.0, 345.0, 23.0 ],
									"numoutlets" : 15,
									"id" : "obj-9",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1.5",
									"numinlets" : 1,
									"patching_rect" : [ 575.0, 10.0, 94.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"presentation_rect" : [ 587.0, 264.706909, 50.0, 23.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 575.0, 40.5, 50.0, 23.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "speaker_distance $1",
									"numinlets" : 2,
									"patching_rect" : [ 592.0, 74.0, 138.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-1",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s hoa.map.multi.speaker_distance",
									"numinlets" : 1,
									"patching_rect" : [ 575.0, 109.706909, 223.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-18",
									"fontname" : "Arial",
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "- Move source(s) by dragging it.\n\n- Select sources by dragging the scene.\n\n- Move only the source's angle with ctrl + drag.\n\n- Move only the source's distance with shift + drag.\n\n- cmd + a : select all sources actually in the scene.\n\n- cmd + click : toggle source selection.",
									"linecount" : 11,
									"presentation_linecount" : 17,
									"frgb" : [ 0.255102, 0.255102, 0.255102, 1.0 ],
									"presentation_rect" : [ 587.0, 350.706909, 195.0, 281.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 448.75, 201.353455, 330.0, 184.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-11",
									"fontname" : "Arial",
									"textcolor" : [ 0.255102, 0.255102, 0.255102, 1.0 ],
									"fontsize" : 14.036457
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "re-populate the spat with new sound distribution",
									"presentation_linecount" : 2,
									"frgb" : [ 0.255102, 0.255102, 0.255102, 1.0 ],
									"presentation_rect" : [ 607.0, 187.0, 175.0, 39.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 448.75, 136.706909, 321.0, 23.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-3",
									"fontname" : "Arial",
									"textcolor" : [ 0.255102, 0.255102, 0.255102, 1.0 ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"numinlets" : 16,
									"patching_rect" : [ 14.5, 615.793091, 345.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-14",
									"fontname" : "Arial",
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"numinlets" : 15,
									"patching_rect" : [ 14.5, 587.5, 345.0, 23.0 ],
									"numoutlets" : 16,
									"id" : "obj-2",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "poly~ hoa.mappoly~ 4",
									"numinlets" : 1,
									"patching_rect" : [ 14.899416, 519.746338, 339.408173, 23.0 ],
									"numoutlets" : 15,
									"id" : "obj-65",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p populateMap",
									"numinlets" : 1,
									"patching_rect" : [ 448.75, 74.0, 103.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-64",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 50.0, 94.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 50.0, 94.0, 640.0, 480.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 14.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadbang",
													"numinlets" : 1,
													"patching_rect" : [ 77.25, 100.0, 68.0, 23.0 ],
													"numoutlets" : 1,
													"id" : "obj-57",
													"fontname" : "Arial",
													"outlettype" : [ "bang" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "regexp .+/(.+)",
													"numinlets" : 1,
													"patching_rect" : [ 155.25, 323.5, 95.0, 23.0 ],
													"numoutlets" : 5,
													"id" : "obj-56",
													"fontname" : "Arial",
													"outlettype" : [ "", "", "", "", "" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "t b i i",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 257.706909, 143.5, 23.0 ],
													"numoutlets" : 3,
													"id" : "obj-44",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "int", "int" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pack text 0 symbol",
													"numinlets" : 3,
													"patching_rect" : [ 50.25, 353.5, 143.0, 23.0 ],
													"numoutlets" : 1,
													"id" : "obj-43",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "- 1",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 225.706909, 32.5, 23.0 ],
													"numoutlets" : 1,
													"id" : "obj-36",
													"fontname" : "Arial",
													"outlettype" : [ "int" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p rand",
													"numinlets" : 1,
													"patching_rect" : [ 431.916687, 291.706909, 50.0, 23.0 ],
													"numoutlets" : 1,
													"id" : "obj-31",
													"fontname" : "Arial",
													"outlettype" : [ "float" ],
													"fontsize" : 14.0,
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
															"major" : 5,
															"minor" : 1,
															"revision" : 9
														}
,
														"rect" : [ 0.0, 0.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"defrect" : [ 0.0, 0.0, 640.0, 480.0 ],
														"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
														"openinpresentation" : 0,
														"default_fontsize" : 14.0,
														"default_fontface" : 0,
														"default_fontname" : "Arial",
														"gridonopen" : 0,
														"gridsize" : [ 15.0, 15.0 ],
														"gridsnaponopen" : 0,
														"toolbarvisible" : 1,
														"boxanimatetime" : 200,
														"imprint" : 0,
														"enablehscroll" : 1,
														"enablevscroll" : 1,
														"devicewidth" : 0.0,
														"boxes" : [ 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "- 1.",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 162.0, 32.5, 23.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-24",
																	"fontname" : "Arial",
																	"outlettype" : [ "float" ],
																	"fontsize" : 14.0
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "* 0.002",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 132.0, 55.0, 23.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-23",
																	"fontname" : "Arial",
																	"outlettype" : [ "float" ],
																	"fontsize" : 14.0
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "random 1000",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 100.0, 93.0, 23.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-18",
																	"fontname" : "Arial",
																	"outlettype" : [ "int" ],
																	"fontsize" : 14.0
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"numinlets" : 0,
																	"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-25",
																	"outlettype" : [ "bang" ],
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"numinlets" : 1,
																	"patching_rect" : [ 50.0, 244.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"id" : "obj-26",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 0 ],
																	"destination" : [ "obj-23", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-23", 0 ],
																	"destination" : [ "obj-24", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-24", 0 ],
																	"destination" : [ "obj-26", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-25", 0 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
														"default_fontface" : 0,
														"default_fontname" : "Arial",
														"fontname" : "Arial",
														"default_fontsize" : 14.0,
														"globalpatchername" : "",
														"fontface" : 0,
														"fontsize" : 14.0
													}

												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "t i b b b",
													"numinlets" : 1,
													"patching_rect" : [ 244.916687, 190.706909, 206.0, 23.0 ],
													"numoutlets" : 4,
													"id" : "obj-30",
													"fontname" : "Arial",
													"outlettype" : [ "int", "bang", "bang", "bang" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p rand",
													"numinlets" : 1,
													"patching_rect" : [ 369.583374, 257.706909, 50.0, 23.0 ],
													"numoutlets" : 1,
													"id" : "obj-29",
													"fontname" : "Arial",
													"outlettype" : [ "float" ],
													"fontsize" : 14.0,
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
															"major" : 5,
															"minor" : 1,
															"revision" : 9
														}
,
														"rect" : [ 75.0, 119.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"defrect" : [ 75.0, 119.0, 640.0, 480.0 ],
														"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
														"openinpresentation" : 0,
														"default_fontsize" : 14.0,
														"default_fontface" : 0,
														"default_fontname" : "Arial",
														"gridonopen" : 0,
														"gridsize" : [ 15.0, 15.0 ],
														"gridsnaponopen" : 0,
														"toolbarvisible" : 1,
														"boxanimatetime" : 200,
														"imprint" : 0,
														"enablehscroll" : 1,
														"enablevscroll" : 1,
														"devicewidth" : 0.0,
														"boxes" : [ 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "- 1.",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 162.0, 32.5, 23.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-24",
																	"fontname" : "Arial",
																	"outlettype" : [ "float" ],
																	"fontsize" : 14.0
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "* 0.002",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 132.0, 55.0, 23.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-23",
																	"fontname" : "Arial",
																	"outlettype" : [ "float" ],
																	"fontsize" : 14.0
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "random 1000",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 100.0, 93.0, 23.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-18",
																	"fontname" : "Arial",
																	"outlettype" : [ "int" ],
																	"fontsize" : 14.0
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"numinlets" : 0,
																	"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-25",
																	"outlettype" : [ "bang" ],
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"numinlets" : 1,
																	"patching_rect" : [ 50.0, 244.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"id" : "obj-26",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 0 ],
																	"destination" : [ "obj-23", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-23", 0 ],
																	"destination" : [ "obj-24", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-24", 0 ],
																	"destination" : [ "obj-26", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-25", 0 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
														"default_fontface" : 0,
														"default_fontname" : "Arial",
														"fontname" : "Arial",
														"default_fontsize" : 14.0,
														"globalpatchername" : "",
														"fontface" : 0,
														"fontsize" : 14.0
													}

												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "t b clear",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 127.0, 459.0, 23.0 ],
													"numoutlets" : 2,
													"id" : "obj-9",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "clear" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "button",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-6",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "uzi 4",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 156.0, 213.916687, 23.0 ],
													"numoutlets" : 3,
													"id" : "obj-4",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "bang", "int" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pack add 0. 0.",
													"numinlets" : 3,
													"patching_rect" : [ 307.25, 353.5, 143.666687, 23.0 ],
													"numoutlets" : 1,
													"id" : "obj-3",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 14.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"items" : [ "cello-f2.aif", ",", "drumLoop.aif", ",", "rainstick.aif", ",", "vibes-a1.aif" ],
													"numinlets" : 1,
													"types" : [  ],
													"patching_rect" : [ 133.75, 291.706909, 62.0, 20.0 ],
													"numoutlets" : 3,
													"id" : "obj-37",
													"fontname" : "Arial",
													"prefix" : "Macintosh HD:/Applications/Max6/examples/sounds/",
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"id" : "obj-62",
													"outlettype" : [ "bang" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.25, 432.5, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-63",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-3", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-63", 0 ],
													"hidden" : 0,
													"midpoints" : [ 316.75, 395.603455, 59.75, 395.603455 ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-30", 2 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-30", 1 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-30", 3 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-30", 0 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [ 254.416687, 218.706909, 59.5, 218.706909 ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-3", 2 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-44", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-37", 1 ],
													"destination" : [ "obj-56", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 2 ],
													"destination" : [ "obj-30", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-43", 0 ],
													"destination" : [ "obj-63", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-44", 2 ],
													"destination" : [ "obj-37", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-44", 1 ],
													"destination" : [ "obj-43", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-44", 0 ],
													"destination" : [ "obj-43", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-56", 1 ],
													"destination" : [ "obj-43", 2 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-57", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-62", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 1 ],
													"destination" : [ "obj-63", 0 ],
													"hidden" : 0,
													"midpoints" : [ 499.5, 416.75, 59.75, 416.75 ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 14.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 14.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"presentation_rect" : [ 587.0, 187.0, 20.0, 20.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 448.75, 44.5, 20.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"id" : "obj-59",
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s tomap.multi",
									"numinlets" : 1,
									"patching_rect" : [ 448.75, 109.706909, 94.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-17",
									"fontname" : "Arial",
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r tomap.multi",
									"numinlets" : 0,
									"patching_rect" : [ 14.5, 16.746368, 91.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-16",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s hoa.map.multi",
									"numinlets" : 1,
									"patching_rect" : [ 35.5, 489.746368, 109.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-27",
									"fontname" : "Arial",
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.map",
									"speaker_number" : 16,
									"presentation_rect" : [ 6.5, 77.206909, 559.0, 559.0 ],
									"zoom" : 0.35,
									"numinlets" : 1,
									"bgcolor" : [ 0.87451, 0.882353, 0.901961, 0.501961 ],
									"patching_rect" : [ 14.5, 45.0, 421.25, 421.25 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-71",
									"fontname" : "Arial",
									"textcolor" : [  ],
									"outlettype" : [ "list", "" ],
									"display_cartvectors" : 0,
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.scope~",
									"presentation_rect" : [ 6.5, 77.206909, 559.0, 559.0 ],
									"shadow" : 0,
									"numinlets" : 15,
									"cicolor" : [ 0.0, 0.0, 0.0, 0.0 ],
									"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
									"patching_rect" : [ 14.5, 45.0, 421.25, 421.25 ],
									"numoutlets" : 0,
									"cishadcolor" : [ 0.0, 0.0, 0.0, 0.0 ],
									"presentation" : 1,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-12",
									"fontname" : "Calibri",
									"textcolor" : [  ],
									"interval" : 80,
									"txcolor" : [ 0.0, 0.0, 0.0, 0.0 ],
									"order" : 7,
									"fontface" : 1,
									"fontsize" : 20.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"presentation_rect" : [ 13.5, 13.0, 435.0, 30.0 ],
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 664.0, 440.0, 70.0, 84.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-15",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"presentation_rect" : [ 580.0, 169.206909, 221.0, 467.0 ],
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 679.0, 455.0, 70.0, 84.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-20",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [ 601.5, 101.353455, 458.25, 101.353455 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-71", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 15 ],
									"destination" : [ "obj-14", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 14 ],
									"destination" : [ "obj-14", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 13 ],
									"destination" : [ "obj-14", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 12 ],
									"destination" : [ "obj-14", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 11 ],
									"destination" : [ "obj-14", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 10 ],
									"destination" : [ "obj-14", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 9 ],
									"destination" : [ "obj-14", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 8 ],
									"destination" : [ "obj-14", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 7 ],
									"destination" : [ "obj-14", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 6 ],
									"destination" : [ "obj-14", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 5 ],
									"destination" : [ "obj-14", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 4 ],
									"destination" : [ "obj-14", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 3 ],
									"destination" : [ "obj-14", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 2 ],
									"destination" : [ "obj-14", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 1 ],
									"destination" : [ "obj-14", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-64", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-64", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 14 ],
									"destination" : [ "obj-9", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 13 ],
									"destination" : [ "obj-9", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 12 ],
									"destination" : [ "obj-9", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 11 ],
									"destination" : [ "obj-9", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 10 ],
									"destination" : [ "obj-9", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 9 ],
									"destination" : [ "obj-9", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 8 ],
									"destination" : [ "obj-9", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 7 ],
									"destination" : [ "obj-9", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 6 ],
									"destination" : [ "obj-9", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 5 ],
									"destination" : [ "obj-9", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 4 ],
									"destination" : [ "obj-9", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 3 ],
									"destination" : [ "obj-9", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 2 ],
									"destination" : [ "obj-9", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 1 ],
									"destination" : [ "obj-9", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-71", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 14 ],
									"destination" : [ "obj-12", 14 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 13 ],
									"destination" : [ "obj-12", 13 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 12 ],
									"destination" : [ "obj-12", 12 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 11 ],
									"destination" : [ "obj-12", 11 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 10 ],
									"destination" : [ "obj-12", 10 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 9 ],
									"destination" : [ "obj-12", 9 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 8 ],
									"destination" : [ "obj-12", 8 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 7 ],
									"destination" : [ "obj-12", 7 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 6 ],
									"destination" : [ "obj-12", 6 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 5 ],
									"destination" : [ "obj-12", 5 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 4 ],
									"destination" : [ "obj-12", 4 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 3 ],
									"destination" : [ "obj-12", 3 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 2 ],
									"destination" : [ "obj-12", 2 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 1 ],
									"destination" : [ "obj-12", 1 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 14 ],
									"destination" : [ "obj-2", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 13 ],
									"destination" : [ "obj-2", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 12 ],
									"destination" : [ "obj-2", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 11 ],
									"destination" : [ "obj-2", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 10 ],
									"destination" : [ "obj-2", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 9 ],
									"destination" : [ "obj-2", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 8 ],
									"destination" : [ "obj-2", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 7 ],
									"destination" : [ "obj-2", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 6 ],
									"destination" : [ "obj-2", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 5 ],
									"destination" : [ "obj-2", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 4 ],
									"destination" : [ "obj-2", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 3 ],
									"destination" : [ "obj-2", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 2 ],
									"destination" : [ "obj-2", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 1 ],
									"destination" : [ "obj-2", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "|---\n|\n|\n|---\n|\n|\n|---\n|\n|\n|---\n|\n|\n|---",
					"linecount" : 13,
					"numinlets" : 1,
					"patching_rect" : [ 569.5, 476.5, 27.0, 180.0 ],
					"numoutlets" : 0,
					"id" : "obj-9",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "| dblclick to see more",
					"numinlets" : 1,
					"patching_rect" : [ 569.5, 457.5, 119.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-11",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "number of sources in the scene",
					"numinlets" : 1,
					"patching_rect" : [ 358.5, 654.677979, 177.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-40",
					"fontname" : "Arial",
					"fontsize" : 11.943355
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "cartesian/polar coordinates (default cart)",
					"numinlets" : 1,
					"patching_rect" : [ 5.5, 654.375, 214.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-38",
					"fontname" : "Arial",
					"fontsize" : 11.39628
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p appearance",
					"numinlets" : 0,
					"patching_rect" : [ 596.5, 553.0, 96.0, 23.0 ],
					"numoutlets" : 0,
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"id" : "obj-14",
					"fontname" : "Arial",
					"fontsize" : 14.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 152.0, 112.0, 566.0, 479.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 152.0, 112.0, 566.0, 479.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1",
									"numinlets" : 1,
									"patching_rect" : [ 4.0, 8.0, 82.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"hidden" : 1,
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.map",
									"numinlets" : 1,
									"patching_rect" : [ 146.0, 148.0, 317.0, 317.0 ],
									"numoutlets" : 2,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-18",
									"fontname" : "Arial",
									"textcolor" : [  ],
									"outlettype" : [ "list", "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numinlets" : 1,
									"patching_rect" : [ 4.0, 262.0, 20.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-5",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "display_speakers $1",
									"numinlets" : 2,
									"patching_rect" : [ 4.0, 288.0, 116.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numinlets" : 1,
									"patching_rect" : [ 4.0, 209.0, 20.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-2",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "display_head $1",
									"numinlets" : 2,
									"patching_rect" : [ 4.0, 235.0, 95.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-4",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 15.0, 432.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-13",
									"fontname" : "Arial",
									"hidden" : 1,
									"fontsize" : 7.180877
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numinlets" : 1,
									"patching_rect" : [ 4.0, 148.0, 20.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-26",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "display_angle $1",
									"numinlets" : 2,
									"patching_rect" : [ 4.0, 174.0, 98.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numinlets" : 1,
									"patching_rect" : [ 4.0, 87.034912, 20.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-19",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "display_grid $1",
									"numinlets" : 2,
									"patching_rect" : [ 4.0, 113.0, 89.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-21",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numinlets" : 1,
									"patching_rect" : [ 4.0, 26.0, 20.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-11",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "display_cartvectors $1",
									"numinlets" : 2,
									"patching_rect" : [ 4.0, 53.0, 126.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-12",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"maximum" : 1.0,
									"numinlets" : 1,
									"minimum" : 0.0,
									"patching_rect" : [ 281.0, 53.0, 43.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-32",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"maximum" : 1.0,
									"numinlets" : 1,
									"minimum" : 0.0,
									"patching_rect" : [ 236.0, 53.0, 43.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-33",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"maximum" : 1.0,
									"numinlets" : 1,
									"minimum" : 0.0,
									"patching_rect" : [ 191.0, 53.0, 43.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-31",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Alpha",
									"numinlets" : 1,
									"patching_rect" : [ 283.0, 35.0, 45.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-30",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"maximum" : 1.0,
									"numinlets" : 1,
									"minimum" : 0.0,
									"patching_rect" : [ 146.0, 53.0, 43.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-29",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Destination",
									"numinlets" : 1,
									"patching_rect" : [ 345.0, 35.0, 68.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-3",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Blue",
									"numinlets" : 1,
									"patching_rect" : [ 239.0, 35.0, 33.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-8",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Green",
									"numinlets" : 1,
									"patching_rect" : [ 194.0, 35.0, 42.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-9",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pak 0. 0. 0. 1.",
									"numinlets" : 4,
									"patching_rect" : [ 146.0, 81.0, 154.0, 20.0 ],
									"numoutlets" : 1,
									"color" : [ 0.73, 0.82, 0.63, 1.0 ],
									"id" : "obj-10",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend set",
									"numinlets" : 1,
									"patching_rect" : [ 381.0, 79.0, 72.0, 20.0 ],
									"numoutlets" : 1,
									"color" : [ 0.73, 0.82, 0.63, 1.0 ],
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend bgcolor",
									"numinlets" : 1,
									"patching_rect" : [ 146.0, 113.0, 94.0, 20.0 ],
									"numoutlets" : 1,
									"color" : [ 0.73, 0.82, 0.63, 1.0 ],
									"id" : "obj-15",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"items" : [ "bgcolor", ",", "gridcolor", ",", "headcolor", ",", "lscolor" ],
									"numinlets" : 1,
									"types" : [  ],
									"patching_rect" : [ 326.0, 53.0, 129.0, 20.0 ],
									"labelclick" : 1,
									"numoutlets" : 3,
									"id" : "obj-16",
									"fontname" : "Arial",
									"outlettype" : [ "int", "", "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Red",
									"numinlets" : 1,
									"patching_rect" : [ 148.0, 35.0, 30.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-17",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"color" : [ 0.501961, 0.501961, 0.501961, 0.901961 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [ 13.5, 81.0, 132.0, 81.0, 132.0, 144.0, 155.5, 144.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"color" : [ 0.501961, 0.501961, 0.501961, 0.901961 ],
									"midpoints" : [ 390.5, 109.0, 155.5, 109.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-15", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 1 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"color" : [ 0.501961, 0.501961, 0.501961, 0.901961 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-26", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [ 13.5, 141.0, 155.5, 141.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"color" : [ 0.501961, 0.501961, 0.501961, 0.901961 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-10", 1 ],
									"hidden" : 0,
									"color" : [ 0.501961, 0.501961, 0.501961, 0.901961 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-10", 3 ],
									"hidden" : 0,
									"color" : [ 0.501961, 0.501961, 0.501961, 0.901961 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-10", 2 ],
									"hidden" : 0,
									"color" : [ 0.501961, 0.501961, 0.501961, 0.901961 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [ 13.5, 252.0, 132.0, 252.0, 132.0, 144.0, 155.5, 144.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [ 13.5, 315.0, 132.0, 315.0, 132.0, 144.0, 155.5, 144.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [ 13.5, 192.0, 132.0, 192.0, 132.0, 144.0, 155.5, 144.0 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p key/mouse actions",
					"numinlets" : 0,
					"patching_rect" : [ 596.5, 476.5, 138.0, 23.0 ],
					"numoutlets" : 0,
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"id" : "obj-12",
					"fontname" : "Arial",
					"fontsize" : 14.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 121.0, 144.0, 489.0, 161.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 121.0, 144.0, 489.0, 161.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 392.0, 126.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-13",
									"fontname" : "Arial",
									"hidden" : 1,
									"fontsize" : 7.180877
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "- click : add a source in the scene if there isn't already one.\n- drag : move a source if you click on it before, or all selected sources if the source you move is a part of a selection, make a rect selection otherwise.\n- ctrl + drag : move only the angle of a source | the selected sources.\n- shift + drag : move only the distance of a source | the selected sources.\n- cmd + a : select all sources actually in the scene.\n- cmd + click : toggle source selection if you click on it.\n- alt + mousewheel : zoom.",
									"linecount" : 8,
									"numinlets" : 1,
									"patching_rect" : [ 5.0, 25.0, 480.0, 136.0 ],
									"numoutlets" : 0,
									"id" : "obj-11",
									"fontname" : "Arial",
									"fontsize" : 14.036457
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "key/mouse actions :",
									"numinlets" : 1,
									"patching_rect" : [ 5.0, 6.0, 133.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-2",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
 ],
						"lines" : [  ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "4",
					"numinlets" : 2,
					"patching_rect" : [ 355.0, 623.5, 107.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-3",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "move sources by cartesian or polar coodinates",
					"numinlets" : 1,
					"patching_rect" : [ 539.5, 247.0, 250.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-6",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p map&meter",
					"numinlets" : 0,
					"patching_rect" : [ 596.5, 591.5, 95.0, 23.0 ],
					"numoutlets" : 0,
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"id" : "obj-73",
					"fontname" : "Arial",
					"fontsize" : 14.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 44.0, 807.0, 679.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 44.0, 807.0, 679.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 1,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "click on hoa.map to add a source to the scene",
									"presentation_linecount" : 2,
									"frgb" : [ 0.326531, 0.326531, 0.326531, 1.0 ],
									"presentation_rect" : [ 581.0, 287.5, 163.0, 39.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 323.5, 382.5, 313.0, 23.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-3",
									"fontname" : "Arial",
									"textcolor" : [ 0.326531, 0.326531, 0.326531, 1.0 ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"presentation_rect" : [ 571.5, 276.0, 178.0, 76.0 ],
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 323.5, 382.5, 313.0, 23.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-2",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "turn dac~ on",
									"frgb" : [ 0.326531, 0.326531, 0.326531, 1.0 ],
									"presentation_rect" : [ 624.0, 569.5, 112.0, 23.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 382.0, 548.5, 112.0, 23.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-8",
									"fontname" : "Arial",
									"textcolor" : [ 0.326531, 0.326531, 0.326531, 1.0 ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"presentation_rect" : [ 571.5, 547.5, 44.0, 44.0 ],
									"numinlets" : 2,
									"patching_rect" : [ 329.5, 526.5, 44.0, 44.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-1",
									"local" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"presentation_rect" : [ 565.5, 536.75, 181.0, 63.75 ],
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 323.5, 515.75, 181.0, 63.75 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-26",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 309.0, 630.793091, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-13",
									"fontname" : "Arial",
									"hidden" : 1,
									"fontsize" : 7.180877
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Exemple : hoa.map~ hover hoa.meter~",
									"presentation_rect" : [ 13.5, 15.0, 253.0, 23.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 31.0, 21.0, 255.0, 23.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-10",
									"fontname" : "Arial",
									"underline" : 1,
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s output-map",
									"numinlets" : 1,
									"patching_rect" : [ 31.0, 612.206909, 77.0, 20.0 ],
									"numoutlets" : 0,
									"color" : [ 0.0, 0.70239, 0.839216, 1.0 ],
									"id" : "obj-72",
									"fontname" : "Arial",
									"fontsize" : 11.39568
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.map",
									"speaker_number" : 16,
									"speaker_distance" : 1.92,
									"presentation_rect" : [ 13.5, 64.5, 536.0, 536.0 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.87451, 0.882353, 0.901961, 0.0 ],
									"patching_rect" : [ 31.0, 305.5, 274.0, 274.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-71",
									"fontname" : "Arial",
									"textcolor" : [  ],
									"outlettype" : [ "list", "" ],
									"display_cartvectors" : 0,
									"display_grid" : 0,
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p data",
									"numinlets" : 1,
									"patching_rect" : [ 286.0, 193.5, 43.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-38",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ],
									"fontsize" : 11.595187,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 703.0, 201.0, 233.0, 327.0 ],
										"bglocked" : 0,
										"defrect" : [ 703.0, 201.0, 233.0, 327.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 14.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 10",
													"numinlets" : 1,
													"patching_rect" : [ 115.0, 110.714294, 78.0, 23.0 ],
													"numoutlets" : 1,
													"id" : "obj-18",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 14.244328
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 10",
													"numinlets" : 1,
													"patching_rect" : [ 25.0, 110.714294, 78.0, 23.0 ],
													"numoutlets" : 1,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 14.244328
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line~ 0.",
													"numinlets" : 2,
													"patching_rect" : [ 91.0, 160.0, 48.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-13",
													"fontname" : "Arial",
													"outlettype" : [ "signal", "bang" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line~ 0.",
													"numinlets" : 2,
													"patching_rect" : [ 25.0, 160.0, 48.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-12",
													"fontname" : "Arial",
													"outlettype" : [ "signal", "bang" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "hoa.pi 0.5",
													"numinlets" : 1,
													"patching_rect" : [ 131.0, 197.0, 63.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-7",
													"fontname" : "Arial",
													"outlettype" : [ "float" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "-~ 0.",
													"numinlets" : 2,
													"patching_rect" : [ 91.0, 237.0, 59.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-8",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "cartopol~",
													"numinlets" : 2,
													"patching_rect" : [ 25.0, 197.0, 85.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-10",
													"fontname" : "Arial",
													"outlettype" : [ "signal", "signal" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route 0",
													"numinlets" : 1,
													"patching_rect" : [ 25.0, 51.0, 47.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-1",
													"fontname" : "Arial",
													"outlettype" : [ "", "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "unpack 0. 0.",
													"numinlets" : 1,
													"patching_rect" : [ 25.0, 78.0, 109.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-2",
													"fontname" : "Arial",
													"outlettype" : [ "float", "float" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 25.0, 12.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"id" : "obj-5",
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 91.0, 271.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-11",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 1 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-10", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 1 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-8", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 14.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 14.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r output-map",
									"numinlets" : 0,
									"patching_rect" : [ 286.0, 166.253632, 75.0, 20.0 ],
									"numoutlets" : 1,
									"color" : [ 0.0, 0.70239, 0.839216, 1.0 ],
									"id" : "obj-39",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.39568
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"presentation_rect" : [ 13.5, 64.5, 536.0, 536.0 ],
									"numinlets" : 16,
									"energycolor" : [ 0.0, 0.0, 1.0, 0.0 ],
									"patching_rect" : [ 31.0, 305.5, 274.0, 274.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"ls" : 16,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-53",
									"ls_angles" : [ 0.0, 22.0, 45.0, 67.0, 90.0, 112.0, 135.0, 157.0, 180.0, 202.0, 225.0, 247.0, 270.0, 292.0, 315.0, 337.5 ],
									"metersize" : 0.69
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"args" : [ "@module", 3, "@noise", 1, "@vol", 80 ],
									"presentation_rect" : [ 565.5, 64.5, 218.0, 87.0 ],
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 31.0, 125.5, 218.0, 87.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"id" : "obj-40",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"numinlets" : 15,
									"patching_rect" : [ 31.0, 270.5, 274.0, 20.0 ],
									"numoutlets" : 16,
									"id" : "obj-41",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"numinlets" : 16,
									"patching_rect" : [ 31.0, 586.206909, 274.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-12",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7",
									"numinlets" : 2,
									"patching_rect" : [ 31.0, 232.5, 274.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-47",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"presentation_rect" : [ 13.5, 13.0, 253.0, 28.0 ],
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 31.0, 21.0, 255.0, 22.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-9",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-47", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-39", 0 ],
									"destination" : [ "obj-38", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 15 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 14 ],
									"destination" : [ "obj-12", 14 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 13 ],
									"destination" : [ "obj-12", 13 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 12 ],
									"destination" : [ "obj-12", 12 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 11 ],
									"destination" : [ "obj-12", 11 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 10 ],
									"destination" : [ "obj-12", 10 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 9 ],
									"destination" : [ "obj-12", 9 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 8 ],
									"destination" : [ "obj-12", 8 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 7 ],
									"destination" : [ "obj-12", 7 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 6 ],
									"destination" : [ "obj-12", 6 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 5 ],
									"destination" : [ "obj-12", 5 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 4 ],
									"destination" : [ "obj-12", 4 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 3 ],
									"destination" : [ "obj-12", 3 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 2 ],
									"destination" : [ "obj-12", 2 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 1 ],
									"destination" : [ "obj-12", 1 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 15 ],
									"destination" : [ "obj-53", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 14 ],
									"destination" : [ "obj-53", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 13 ],
									"destination" : [ "obj-53", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 12 ],
									"destination" : [ "obj-53", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 11 ],
									"destination" : [ "obj-53", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 10 ],
									"destination" : [ "obj-53", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 9 ],
									"destination" : [ "obj-53", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 8 ],
									"destination" : [ "obj-53", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 7 ],
									"destination" : [ "obj-53", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 6 ],
									"destination" : [ "obj-53", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 5 ],
									"destination" : [ "obj-53", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 4 ],
									"destination" : [ "obj-53", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 3 ],
									"destination" : [ "obj-53", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 2 ],
									"destination" : [ "obj-53", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 1 ],
									"destination" : [ "obj-53", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-41", 0 ],
									"destination" : [ "obj-53", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 14 ],
									"destination" : [ "obj-41", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 13 ],
									"destination" : [ "obj-41", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 12 ],
									"destination" : [ "obj-41", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 11 ],
									"destination" : [ "obj-41", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 10 ],
									"destination" : [ "obj-41", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 9 ],
									"destination" : [ "obj-41", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 8 ],
									"destination" : [ "obj-41", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 7 ],
									"destination" : [ "obj-41", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 6 ],
									"destination" : [ "obj-41", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 5 ],
									"destination" : [ "obj-41", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 4 ],
									"destination" : [ "obj-41", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 3 ],
									"destination" : [ "obj-41", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 2 ],
									"destination" : [ "obj-41", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 1 ],
									"destination" : [ "obj-41", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-47", 0 ],
									"destination" : [ "obj-41", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-71", 0 ],
									"destination" : [ "obj-72", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-40", 0 ],
									"destination" : [ "obj-47", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p add4point",
					"numinlets" : 1,
					"patching_rect" : [ 483.5, 168.5, 84.0, 23.0 ],
					"numoutlets" : 1,
					"id" : "obj-70",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 535.0, 113.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 535.0, 113.0, 640.0, 480.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"numinlets" : 1,
									"patching_rect" : [ 50.0, 65.0, 68.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-1",
									"fontname" : "Arial",
									"outlettype" : [ "bang" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "add 0.5 -0.5",
									"numinlets" : 2,
									"patching_rect" : [ 128.833313, 196.0, 85.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-15",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "add -0.5 -0.5",
									"numinlets" : 2,
									"patching_rect" : [ 107.333313, 161.5, 91.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "add -0.5 0.5",
									"numinlets" : 2,
									"patching_rect" : [ 80.75, 128.0, 85.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-13",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "add 0.5 0.5",
									"numinlets" : 2,
									"patching_rect" : [ 50.0, 100.0, 81.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-11",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 50.0, 32.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"id" : "obj-68",
									"outlettype" : [ "bang" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 86.729126, 276.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-69",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-15", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-68", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 483.5, 141.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-67",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s map",
					"numinlets" : 1,
					"patching_rect" : [ 483.5, 207.5, 49.0, 23.0 ],
					"numoutlets" : 0,
					"color" : [ 0.0, 0.70239, 0.839216, 1.0 ],
					"id" : "obj-63",
					"fontname" : "Arial",
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "hoa.reverberation~",
					"numinlets" : 2,
					"patching_rect" : [ 589.666687, 404.637512, 128.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-62",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p see_also",
					"numinlets" : 1,
					"patching_rect" : [ 589.666687, 435.637512, 69.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-101",
					"fontname" : "Arial",
					"hidden" : 1,
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 50.0, 94.0, 264.0, 148.0 ],
						"bglocked" : 0,
						"defrect" : [ 50.0, 94.0, 264.0, 148.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"varname" : "phelp",
									"text" : "prepend help",
									"numinlets" : 1,
									"patching_rect" : [ 99.0, 63.5, 83.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-2",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pcontrol",
									"numinlets" : 1,
									"patching_rect" : [ 99.0, 90.5, 56.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-3",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 99.0, 36.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"id" : "obj-4",
									"outlettype" : [ "" ],
									"comment" : "From umenu label out"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "add/remove sources",
					"numinlets" : 1,
					"patching_rect" : [ 514.25, 141.0, 116.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-36",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p options/msg",
					"numinlets" : 0,
					"patching_rect" : [ 596.5, 512.5, 106.0, 24.0 ],
					"numoutlets" : 0,
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"id" : "obj-43",
					"fontname" : "Arial",
					"fontsize" : 15.347269,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 94.0, 76.0, 449.0, 492.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 94.0, 76.0, 449.0, 492.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 291.25, 441.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-6",
									"fontname" : "Arial",
									"hidden" : 1,
									"fontsize" : 7.180877
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[5]",
									"text" : "speaker_offset : (int/float) change loudspeakers offset (in degree -180 | 180).",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 183.25, 246.5, 235.5, 34.0 ],
									"numoutlets" : 0,
									"id" : "obj-12",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"numinlets" : 1,
									"patching_rect" : [ 122.25, 253.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-13",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "speaker_offset $1",
									"numinlets" : 2,
									"patching_rect" : [ 122.25, 285.0, 102.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[4]",
									"text" : "bang : output all visible sources values",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 134.25, 207.0, 216.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-11",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numinlets" : 1,
									"patching_rect" : [ 102.25, 207.0, 20.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-8",
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[6]",
									"text" : "add some text to your source",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 156.25, 337.5, 165.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-9",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "text 1",
									"numinlets" : 2,
									"patching_rect" : [ 274.25, 389.5, 45.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-55",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "text 0",
									"numinlets" : 2,
									"patching_rect" : [ 274.25, 361.5, 45.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-1",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "text 0 violon",
									"numinlets" : 2,
									"patching_rect" : [ 156.25, 364.5, 85.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-4",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "text 1 piano",
									"numinlets" : 2,
									"patching_rect" : [ 156.25, 392.5, 83.0, 21.0 ],
									"numoutlets" : 1,
									"id" : "obj-5",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[3]",
									"text" : "distance : distance between loudspeaker and listener (in meters)",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 144.25, 136.5, 267.0, 34.0 ],
									"numoutlets" : 0,
									"id" : "obj-24",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[2]",
									"text" : "speaker_number : (int) number of loudspeakers.",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 102.25, 70.0, 267.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-7",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "zoom : (0.1=>1.).",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 67.25, 12.0, 102.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-2",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"numinlets" : 1,
									"patching_rect" : [ 36.75, 70.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-53",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "speaker_number $1",
									"numinlets" : 2,
									"patching_rect" : [ 36.75, 102.0, 114.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-48",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s map",
									"numinlets" : 1,
									"patching_rect" : [ 8.0, 451.465088, 49.0, 23.0 ],
									"numoutlets" : 0,
									"color" : [ 0.0, 0.70239, 0.839216, 1.0 ],
									"id" : "obj-33",
									"fontname" : "Arial",
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 8.0, 12.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-25",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "zoom $1",
									"numinlets" : 2,
									"patching_rect" : [ 8.0, 41.0, 55.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-3",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 67.25, 136.5, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-39",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "distance $1",
									"numinlets" : 2,
									"patching_rect" : [ 67.25, 166.5, 70.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 67.25, 12.0, 102.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-44",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 102.25, 70.0, 267.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-18",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 144.25, 136.5, 267.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-19",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 134.25, 207.0, 216.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-21",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 183.25, 246.5, 235.5, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-22",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"shadow" : -1,
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 156.25, 337.5, 165.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-23",
									"rounded" : 15,
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 283.75, 384.0, 252.0, 384.0, 252.0, 438.0, 17.5, 438.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 131.75, 438.0, 17.5, 438.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 76.75, 438.0, 17.5, 438.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 17.5, 60.0, 17.5, 60.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-39", 0 ],
									"destination" : [ "obj-20", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 165.75, 387.0, 17.5, 387.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-48", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 46.25, 438.0, 17.5, 438.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 165.75, 438.0, 17.5, 438.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-53", 0 ],
									"destination" : [ "obj-48", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-55", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 283.75, 426.0, 17.5, 426.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 111.75, 240.0, 17.5, 240.0 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numinlets" : 1,
					"minimum" : 0,
					"patching_rect" : [ 596.083313, 274.0, 50.0, 23.0 ],
					"numoutlets" : 2,
					"id" : "obj-37",
					"fontname" : "Arial",
					"outlettype" : [ "int", "bang" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "set $1",
					"numinlets" : 2,
					"patching_rect" : [ 596.083313, 274.0, 49.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-35",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "pol 0 0.73 17.59",
					"numinlets" : 2,
					"patching_rect" : [ 596.083313, 334.0, 124.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-33",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "set pol",
					"numinlets" : 2,
					"patching_rect" : [ 483.5, 274.0, 52.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-31",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "set car",
					"numinlets" : 2,
					"patching_rect" : [ 539.5, 274.0, 53.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-30",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"patching_rect" : [ 710.0, 274.0, 50.0, 23.0 ],
					"numoutlets" : 2,
					"id" : "obj-28",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"patching_rect" : [ 653.166687, 274.0, 50.0, 23.0 ],
					"numoutlets" : 2,
					"id" : "obj-27",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pak car 0 0. 0.",
					"numinlets" : 4,
					"patching_rect" : [ 539.25, 302.0, 189.5, 23.0 ],
					"numoutlets" : 1,
					"id" : "obj-25",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s map",
					"numinlets" : 1,
					"patching_rect" : [ 539.25, 334.0, 49.0, 23.0 ],
					"numoutlets" : 0,
					"color" : [ 0.0, 0.70239, 0.839216, 1.0 ],
					"id" : "obj-24",
					"fontname" : "Arial",
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r map",
					"numinlets" : 0,
					"patching_rect" : [ 15.0, 130.5, 46.0, 23.0 ],
					"numoutlets" : 1,
					"color" : [ 0.0, 0.70239, 0.839216, 1.0 ],
					"id" : "obj-23",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "add 0 0",
					"numinlets" : 2,
					"patching_rect" : [ 578.5, 168.5, 57.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-10",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "3 0.5 0.5",
					"numinlets" : 2,
					"patching_rect" : [ 5.5, 623.5, 155.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-5",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "remove",
					"numinlets" : 2,
					"patching_rect" : [ 650.166687, 168.5, 56.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-16",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"numinlets" : 2,
					"patching_rect" : [ 720.0, 168.5, 50.0, 21.0 ],
					"numoutlets" : 1,
					"id" : "obj-18",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "see also =>",
					"numinlets" : 1,
					"patching_rect" : [ 514.25, 404.637512, 70.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-7",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "bgcolor 0.93 0.93 0.92 1.",
					"linecount" : 2,
					"numinlets" : 4,
					"patching_rect" : [ 413.5, 21.0, 52.0, 23.0 ],
					"numoutlets" : 0,
					"id" : "obj-45",
					"fontname" : "Arial",
					"hidden" : 1,
					"fontsize" : 7.180877
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"shadow" : -1,
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 514.25, 141.0, 116.0, 19.0 ],
					"numoutlets" : 0,
					"id" : "obj-46",
					"rounded" : 15,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"shadow" : -1,
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 539.5, 247.0, 250.0, 19.0 ],
					"numoutlets" : 0,
					"id" : "obj-47",
					"rounded" : 15,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"shadow" : -1,
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 507.083374, 387.0, 224.0, 54.637512 ],
					"numoutlets" : 0,
					"id" : "obj-48",
					"rounded" : 15,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-1", 1 ],
					"destination" : [ "obj-3", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-5", 1 ],
					"hidden" : 0,
					"midpoints" : [ 24.5, 618.0, 151.0, 618.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-63", 0 ],
					"hidden" : 0,
					"midpoints" : [ 588.0, 197.5, 493.0, 197.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-63", 0 ],
					"hidden" : 0,
					"midpoints" : [ 659.666687, 197.5, 493.0, 197.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-63", 0 ],
					"hidden" : 0,
					"midpoints" : [ 729.5, 197.5, 493.0, 197.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-33", 1 ],
					"hidden" : 0,
					"midpoints" : [ 548.75, 328.5, 710.583313, 328.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-25", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-25", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [ 493.0, 297.0, 548.75, 297.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-25", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 0 ],
					"destination" : [ "obj-101", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-67", 0 ],
					"destination" : [ "obj-70", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 0 ],
					"destination" : [ "obj-63", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
