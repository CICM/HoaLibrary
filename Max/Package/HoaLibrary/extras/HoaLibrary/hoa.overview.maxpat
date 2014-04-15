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
		"rect" : [ 209.0, 129.0, 701.0, 645.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 0,
		"toolbarvisible" : 0,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"title" : "|-- HoaLibrary overview --|",
		"boxes" : [ 			{
				"box" : 				{
					"autofit" : 1,
					"id" : "hoa.2d.scope~",
					"instance_attributes" : 					{
						"palette_caption" : "hoa.2d.scope~",
						"palette_category" : [ "HoaLib", "Interface", "Recent" ],
						"palette_action" : "hoa.2d.scope~"
					}
,
					"maxclass" : "fpic",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 602.875, 22.898775, 58.625, 30.70245 ],
					"pic" : "GPLv3_Logo.svg"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-15",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 691.729187, 82.875, 294.0, 25.0 ],
					"text" : ";\rmax launchbrowser http://creativecommons.org/licenses/by-nc-sa/3.0/"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.78125, 72.75, 675.84375, 8.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3.78125, 71.75, 675.84375, 8.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 208.78125, 20.75, 73.0, 20.0 ],
					"text" : "version 2.0",
					"textcolor" : [ 0.9404, 0.940544, 0.940332, 1.0 ],
					"varname" : "autohelp_top_title[4]"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-27",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 209.78125, 21.75, 73.0, 20.0 ],
					"text" : "version 2.0",
					"textcolor" : [ 0.424631, 0.424696, 0.4246, 0.21 ],
					"varname" : "autohelp_top_title[5]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-29",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 208.78125, 20.75, 74.0, 21.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"args" : [ "@obj-name", "HoaLibrary", "@width", 290, "@obj-desc", "High Order Ambisonics Library " ],
					"id" : "obj-8",
					"maxclass" : "bpatcher",
					"name" : "hoa.helpheader.maxpat",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.78125, 10.75, 292.0, 55.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-60",
					"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.78125, 5.75, 675.84375, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-61",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3.78125, 4.75, 675.84375, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 7.263873,
					"hidden" : 1,
					"id" : "obj-55",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -61.9375, 30.75, 55.0, 15.0 ],
					"text" : "loadmess 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.425629,
					"frgb" : 0.0,
					"hidden" : 1,
					"id" : "obj-54",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 14.5, 63.75, 33.28125, 17.0 ],
					"text" : "grow"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-52",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 3,
					"outlettype" : [ "bang", "bang", "" ],
					"patching_rect" : [ -269.9375, 10.75, 46.0, 20.0 ],
					"text" : "sel 0 1"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-51",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 4.78125, 65.525246, 13.0, 13.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"frgb" : 0.0,
					"id" : "obj-19",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 312.5625, 10.75, 262.0, 32.0 ],
					"text" : "Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 - 2013 CICM / Universite Paris 8",
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-28",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 312.5625, 10.75, 259.5, 32.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-13",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -269.9375, 45.75, 177.0, 17.0 ],
					"text" : "window flags grow, window exec"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-6",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -253.4375, 68.75, 190.0, 17.0 ],
					"text" : "window flags nogrow, window exec"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-42",
					"maxclass" : "newobj",
					"numinlets" : 4,
					"numoutlets" : 0,
					"patching_rect" : [ -149.9375, 611.75, 143.0, 20.0 ],
					"text" : "bgcolor 0.93 0.93 0.92 1."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-18",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 31.6875, 552.5, 604.375, 23.0 ],
					"textcolor" : [ 0.192668, 0.192697, 0.192653, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
					"bordercolor" : [ 0.999903, 1.0, 0.99983, 1.0 ],
					"id" : "obj-21",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 19.0625, 548.5, 6.0, 80.0 ],
					"rounded" : 0
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"border" : 1,
					"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
					"id" : "obj-17",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 16.0625, 544.5, 664.6875, 87.25 ],
					"rounded" : 0
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 418.0625, 45.75, 65.0, 20.0 ],
					"text" : "contact us",
					"textcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"handoff" : "",
					"hilite" : 0,
					"id" : "obj-10",
					"maxclass" : "ubutton",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "", "int" ],
					"patching_rect" : [ 418.0625, 45.75, 65.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 619.529907, 138.725479, 92.470032, 20.274523 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-11",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 691.729187, 44.75, 318.0, 25.0 ],
					"text" : ";\rmax launchbrowser http://www.mshparisnord.fr/hoalibrary/en/contacts/"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ -269.9375, 95.25, 69.0, 20.0 ],
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
					"text" : "thispatcher"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-80",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 313.0625, 45.75, 96.0, 20.0 ],
					"text" : "visit our website",
					"textcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
					"fadeunselect" : 1,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"htabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
					"htextcolor" : [ 1.0, 1.0, 1.0, 0.95 ],
					"id" : "obj-20",
					"margin" : 0,
					"maxclass" : "tab",
					"multiline" : 0,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 13.9375, 88.5, 654.875, 35.0 ],
					"rounded" : 0.0,
					"spacing_x" : 1.0,
					"spacing_y" : 0.0,
					"tabs" : [ "Externals-all", "Externals-1", "Externals-2", "Externals-GUI", "Externals-Utility", "Plug-process", "Plug-Operators" ]
				}

			}
, 			{
				"box" : 				{
					"clickthrough" : 1,
					"embed" : 1,
					"id" : "obj-22",
					"maxclass" : "bpatcher",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "blank" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 6,
							"architecture" : "x64"
						}
,
						"rect" : [ 225.0, 300.0, 665.0, 366.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-13",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 145.0, 74.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "int", "" ],
									"patching_rect" : [ 7.0, 30.0, 33.0, 20.0 ],
									"text" : "t 0 s"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 425.5, 617.0, 83.0, 20.0 ],
									"text" : "prepend help",
									"varname" : "phelp"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-8",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 425.5, 647.5, 56.0, 20.0 ],
									"text" : "pcontrol"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-61",
									"linecolor" : [ 1.0, 1.0, 1.0, 0.5 ],
									"maxclass" : "live.line",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 145.0, 58.0, 616.0, 5.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 25.4375, 47.257935, 616.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-62",
									"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
									"maxclass" : "live.line",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 144.0, 57.0, 616.0, 5.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 24.4375, 46.257935, 616.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 16.0, 180.0, 138.0, 20.0 ],
									"text" : "t s s"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 16.0, 617.0, 105.0, 20.0 ],
									"text" : "join 2 @triggers 1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 16.0, 645.0, 273.0, 20.0 ],
									"text" : "prepend get_objectref_from_category_and_index"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-31",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 16.0, 675.5, 104.0, 20.0 ],
									"saved_object_attributes" : 									{
										"filename" : "hoa.overviewer",
										"parameter_enable" : 0
									}
,
									"text" : "js hoa.overviewer"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-43",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 135.0, 244.0, 104.0, 20.0 ],
									"saved_object_attributes" : 									{
										"filename" : "hoa.overviewer",
										"parameter_enable" : 0
									}
,
									"text" : "js hoa.overviewer"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-50",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 135.0, 217.0, 105.0, 20.0 ],
									"text" : "prepend objectlist"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-53",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 21.0, 86.0, 81.0, 20.0 ],
									"text" : "prepend tabs"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-55",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 7.0, 4.0, 107.0, 20.0 ],
									"text" : "loadmess getkeys"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-56",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 21.0, 58.0, 104.0, 20.0 ],
									"saved_object_attributes" : 									{
										"filename" : "hoa.overviewer",
										"parameter_enable" : 0
									}
,
									"text" : "js hoa.overviewer"
								}

							}
, 							{
								"box" : 								{
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fadeunselect" : 1,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"htabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"htextcolor" : [ 1.0, 1.0, 1.0, 0.95 ],
									"id" : "obj-57",
									"margin" : 0,
									"maxclass" : "tab",
									"multiline" : 0,
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 21.0, 115.0, 654.875, 35.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 3.0, 4.0, 657.875, 35.0 ],
									"rounded" : 0.0,
									"spacing_x" : 1.0,
									"spacing_y" : 0.0,
									"tabs" : [ "all", "2d", "3d", "GUI" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-58",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 135.0, 277.0, 81.0, 20.0 ],
									"text" : "prepend tabs"
								}

							}
, 							{
								"box" : 								{
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-59",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 135.0, 309.0, 600.0, 280.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 3.0, 54.0, 657.875, 300.0 ],
									"rounded" : 0.0,
									"spacing_x" : 20.0,
									"spacing_y" : 3.0,
									"tabcolor" : [ 0.85098, 0.85098, 0.85098, 0.9 ],
									"tabs" : [ "hoa.2d.map", "hoa.2d.meter~", "hoa.2d.recomposer", "hoa.2d.scope~", "hoa.2d.space", "hoa.gain~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-54",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 4021.0, 637.0, 70.0, 20.0 ],
									"text" : "renumber"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-52",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 3201.0, 486.0, 70.0, 20.0 ],
									"text" : "renumber"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-21",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 4369.0, 602.0, 248.0, 20.0 ],
									"text" : "Operators and tools shortcuts for hoa.plug~",
									"textcolor" : [ 0.375912, 0.375912, 0.375912, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-20",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 4029.0, 338.0, 617.0, 282.0 ],
									"rounded" : 6.0,
									"spacing_x" : 20.0,
									"spacing_y" : 5.0,
									"tabs" : [ "hoa.abs~", "hoa.all", "hoa.amp~", "hoa.div~", "hoa.equals~", "hoa.greaterthan~", "hoa.greaterthaneq~", "hoa.highpass~", "hoa.lessthan~", "hoa.lessthaneq~", "hoa.minus~", "hoa.modulo~", "hoa.name1~", "hoa.name2~", "hoa.notequals~", "hoa.nothing~", "hoa.onepole~", "hoa.plus~", "hoa.plusequals~", "hoa.rdiv~", "hoa.receive", "hoa.receive~", "hoa.rminus~", "hoa.send", "hoa.send~", "hoa.snapshot~", "hoa.times~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-47",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 3916.0, 662.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-48",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 3916.0, 633.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-45",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 3252.0, 676.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-46",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 3252.0, 647.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-42",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 3058.0, 510.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-44",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 3058.0, 481.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 7,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.am~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.delay~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.decorrelation~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.grain~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.mirror~" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.mixer~" ]
											}
, 											{
												"key" : 6,
												"value" : [ "hoa.granular~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-39",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 3977.0, 663.0, 128.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-effects"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 7,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.plug~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.connect" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.dac~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.pi" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.pi~" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.record~" ]
											}
, 											{
												"key" : 6,
												"value" : [ "hoa.play~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-37",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 3313.0, 676.0, 119.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-utility"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 7,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.projector~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.recomposer~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.convolve~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.map~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.space~" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.freeverb~" ]
											}
, 											{
												"key" : 6,
												"value" : [ "hoa.vector~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-35",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 3119.0, 510.0, 130.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-special"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-32",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 330.5, 667.5, 91.0, 22.0 ],
									"text" : "route symbol"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-22",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 16.0, 712.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 1815.0, 243.0, 69.0, 22.0 ],
									"text" : "route nav"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-30",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 2340.0, 298.0, 81.0, 17.0 ],
									"text" : "offset -4000 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-29",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 2252.5, 298.0, 81.0, 17.0 ],
									"text" : "offset -3300 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-28",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 2165.0, 298.0, 84.0, 17.0 ],
									"text" : "offset -2636. 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-27",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 2077.5, 298.0, 81.0, 17.0 ],
									"text" : "offset -1975 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-24",
									"maxclass" : "newobj",
									"numinlets" : 8,
									"numoutlets" : 8,
									"outlettype" : [ "bang", "bang", "bang", "bang", "bang", "bang", "bang", "" ],
									"patching_rect" : [ 1815.0, 271.0, 631.5, 19.0 ],
									"text" : "sel 0 1 2 3 4 5 6"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1990.0, 298.0, 81.0, 17.0 ],
									"text" : "offset -1313 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-25",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1902.5, 298.0, 75.0, 17.0 ],
									"text" : "offset -660 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-26",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1815.0, 298.0, 58.0, 17.0 ],
									"text" : "offset 0 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.934731,
									"hidden" : 1,
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 1815.0, 324.0, 67.0, 20.0 ],
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
									"text" : "thispatcher"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-19",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 3332.0, 312.0, 26.0, 20.0 ],
									"text" : "FX"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-18",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 3335.0, 338.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.am~", "hoa.delay~", "hoa.decorrelation~", "hoa.grain~", "hoa.mirror~", "hoa.mixer~", "hoa.granular~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 2680.25, 156.0, 50.0, 20.0 ],
									"text" : "Special"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-17",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 2680.0, 182.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.projector~", "hoa.recomposer~", "hoa.convolve~", "hoa.map~", "hoa.space~", "hoa.freeverb~", "hoa.vector~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1954.0, 349.0, 40.0, 20.0 ],
									"text" : "Utility"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-15",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1954.0, 375.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.plug~", "hoa.connect", "hoa.dac~", "hoa.pi", "hoa.pi~", "hoa.record~", "hoa.play~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 259.0, 252.0, 24.0, 20.0 ],
									"text" : "All"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-56", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-57", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 16.5, 109.0, 30.5, 109.0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-57", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 154.5, 110.0, 30.5, 110.0 ],
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-46", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-15", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-17", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-48", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-18", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-25", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-27", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-30", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-27", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-28", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-31", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-35", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-37", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-50", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-42", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-58", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-43", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-35", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-44", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-45", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-37", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-46", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-45", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-48", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-48", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-43", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-50", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-35", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-52", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-57", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-53", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-54", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-55", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-56", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 348.4375, 161.0, 25.5, 161.0 ],
									"source" : [ "obj-57", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-59", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-58", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-59", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 725.5, 605.0, 111.5, 605.0 ],
									"source" : [ "obj-59", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-24", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 16.0625, 171.257935, 664.5625, 365.25 ]
				}

			}
, 			{
				"box" : 				{
					"handoff" : "",
					"hilite" : 0,
					"id" : "obj-63",
					"maxclass" : "ubutton",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "", "int" ],
					"patching_rect" : [ 313.0625, 45.75, 96.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 604.529907, 123.725479, 92.470032, 20.274523 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-65",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 691.729187, 10.75, 261.5, 25.0 ],
					"text" : ";\rmax launchbrowser http://www.mshparisnord.fr/hoalibrary/en/"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-56",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ -51.9375, 10.75, 45.0, 17.0 ],
					"text" : "onecopy"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-5",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 13.9375, 88.5, 666.6875, 74.0 ],
					"text" : "Hoa Library allows musicians and composers to synthesize, transform and render sound fields in a creative and artistic way. This library facilitates the understanding and the appropriation of key concepts of ambisonics. Thanks to original graphical interfaces a lot of new signal processing are allowed like diffuse sound field synthesis, perspective distorsion or spatial filtering...",
					"textcolor" : [ 0.27596, 0.276002, 0.27594, 1.0 ],
					"varname" : "autohelp_top_description"
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"border" : 1,
					"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
					"id" : "obj-77",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 16.0625, 171.257935, 664.5625, 365.25 ],
					"rounded" : 0
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"border" : 1,
					"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
					"id" : "obj-26",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 13.9375, 88.25, 666.6875, 74.25 ],
					"rounded" : 0
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-67",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 313.0625, 45.75, 96.0, 20.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-69",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 418.0625, 45.75, 65.0, 20.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-10", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-52", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-55", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-63", 1 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "hoa.overviewer.js",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/javascript",
				"patcherrelativepath" : "../../javascript",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.helpheader.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.2d.scope~.svg",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/object-palettes",
				"patcherrelativepath" : "../../misc/object-palettes",
				"type" : "svg ",
				"implicit" : 1
			}
, 			{
				"name" : "GPLv3_Logo.svg",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../../misc/others",
				"type" : "svg ",
				"implicit" : 1
			}
 ]
	}

}
