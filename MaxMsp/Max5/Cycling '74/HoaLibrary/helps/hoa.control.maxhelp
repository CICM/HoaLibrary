{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 100.0, 100.0, 899.0, 648.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 100.0, 100.0, 899.0, 648.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 11.595187,
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
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 304.0, 546.5, 84.0, 20.0 ],
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"numinlets" : 1,
					"rounded" : 6,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-57"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 171.0, 546.5, 38.0, 20.0 ],
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"numinlets" : 1,
					"rounded" : 6,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-56"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 82.0, 546.5, 54.0, 20.0 ],
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"numinlets" : 1,
					"rounded" : 6,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-55"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
					"linecount" : 2,
					"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"fontsize" : 11.595187,
					"patching_rect" : [ 549.0, 18.0, 257.0, 33.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-52",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 549.0, 18.0, 257.0, 32.0 ],
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"numinlets" : 1,
					"rounded" : 6,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-53"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"name" : "hoa.helpheader.maxpat",
					"args" : [ "@obj-name", "hoa.control", "@obj-desc", "A", "didactic", "Graphic", "User", "Interface", "and", "an", "ambisonics", "controler" ],
					"patching_rect" : [ 5.5, 6.0, 483.0, 56.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-21"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "bgcolor 0.93 0.93 0.92 1.",
					"linecount" : 2,
					"fontsize" : 7.180877,
					"patching_rect" : [ 419.5, 22.5, 52.0, 23.0 ],
					"numinlets" : 4,
					"numoutlets" : 0,
					"id" : "obj-31",
					"fontname" : "Arial",
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[1]",
					"text" : "hoa.control~ displays the representation of the harmonics of an encoded ponctual sound for a given order, optimization, azimuth value and wide value. Click and drag to move the azimuth of the dirac and hold shift to widen the dirac. The absolute and relative mode are explain in the \"controler\" subpatcher. It can be used to understand the behavior of the encoding, the optimization and fractionnal order effect (wider) or to control the \"super encoder\" set.",
					"linecount" : 4,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 5.5, 69.0, 677.0, 62.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-43",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 5.5, 69.0, 677.0, 60.0 ],
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"numinlets" : 1,
					"rounded" : 15,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-44"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Look at us :",
					"fontsize" : 11.595187,
					"patching_rect" : [ 776.0, 130.0, 76.5, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-23",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[2]",
					"text" : "Super encoder",
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 569.5, 310.5, 89.0, 20.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-15",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 11.595187,
					"patching_rect" : [ 817.0, 368.0, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-40",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend set",
					"fontsize" : 11.595187,
					"patching_rect" : [ 787.5, 271.5, 72.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-36",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "textedit",
					"varname" : "textedit[1]",
					"text" : "optim maxRe",
					"bangmode" : 1,
					"fontsize" : 11.595187,
					"patching_rect" : [ 787.5, 301.0, 94.5, 21.0 ],
					"numinlets" : 1,
					"keymode" : 1,
					"numoutlets" : 4,
					"id" : "obj-37",
					"fontname" : "Arial",
					"outlettype" : [ "", "int", "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 11.595187,
					"patching_rect" : [ 699.0, 278.0, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-35",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r root.optim",
					"fontsize" : 11.595187,
					"patching_rect" : [ 787.5, 242.5, 69.0, 20.0 ],
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-32",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r root.wide",
					"fontsize" : 11.595187,
					"patching_rect" : [ 817.0, 336.5, 65.0, 20.0 ],
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-33",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r root.azimuth",
					"fontsize" : 11.595187,
					"patching_rect" : [ 699.0, 242.5, 81.0, 20.0 ],
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-34",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s root.optim",
					"fontsize" : 11.595187,
					"patching_rect" : [ 390.0, 570.5, 71.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-28",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s root.wide",
					"fontsize" : 11.595187,
					"patching_rect" : [ 210.0, 570.5, 67.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-12",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s root.azimuth",
					"fontsize" : 11.595187,
					"patching_rect" : [ 30.0, 570.5, 83.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-14",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "textedit",
					"varname" : "textedit",
					"text" : "optim basic",
					"bangmode" : 1,
					"fontsize" : 11.595187,
					"patching_rect" : [ 390.0, 546.5, 87.5, 20.0 ],
					"numinlets" : 1,
					"keymode" : 1,
					"numoutlets" : 4,
					"id" : "obj-19",
					"fontname" : "Arial",
					"outlettype" : [ "", "int", "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 11.595187,
					"patching_rect" : [ 210.0, 546.5, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-17",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 11.595187,
					"patching_rect" : [ 30.0, 546.5, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-8",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[5]",
					"text" : "Optimization :",
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 304.0, 546.5, 84.0, 20.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-3",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "hoa.control",
					"patching_rect" : [ 30.0, 150.0, 379.0, 379.0 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"numinlets" : 1,
					"numoutlets" : 3,
					"order" : 7,
					"id" : "obj-4",
					"outlettype" : [ "float", "float", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.optim~ 7 basic",
					"fontsize" : 11.595187,
					"patching_rect" : [ 510.0, 391.0, 208.0, 20.0 ],
					"numinlets" : 15,
					"numoutlets" : 15,
					"id" : "obj-5",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[4]",
					"text" : "Wide",
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 171.0, 546.5, 38.0, 20.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-18",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[3]",
					"text" : "Azimuth",
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 82.0, 546.5, 54.0, 20.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-9",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.wider~ 7",
					"fontsize" : 11.595187,
					"patching_rect" : [ 510.0, 435.0, 221.5, 20.0 ],
					"numinlets" : 16,
					"numoutlets" : 15,
					"id" : "obj-1",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.dac~ 1:16",
					"fontsize" : 11.595187,
					"patching_rect" : [ 510.0, 578.0, 221.5, 20.0 ],
					"numinlets" : 16,
					"numoutlets" : 0,
					"id" : "obj-69",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.decoder~ 7 16",
					"fontsize" : 11.595187,
					"patching_rect" : [ 510.0, 495.0, 221.5, 20.0 ],
					"numinlets" : 15,
					"numoutlets" : 16,
					"id" : "obj-74",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"fontsize" : 11.595187,
					"patching_rect" : [ 834.5, 496.0, 32.5, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-73",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "startwindow",
					"fontsize" : 11.595187,
					"patching_rect" : [ 795.0, 466.0, 72.0, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-71",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"fontsize" : 11.595187,
					"patching_rect" : [ 510.0, 345.0, 208.0, 20.0 ],
					"numinlets" : 2,
					"numoutlets" : 15,
					"id" : "obj-20",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p key32",
					"fontsize" : 11.595187,
					"patching_rect" : [ 763.0, 53.0, 51.0, 20.0 ],
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-46",
					"fontname" : "Arial",
					"hidden" : 1,
					"outlettype" : [ "bang" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
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
									"maxclass" : "button",
									"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-10",
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sel 32",
									"fontsize" : 11.595187,
									"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
									"numinlets" : 2,
									"numoutlets" : 2,
									"id" : "obj-23",
									"fontname" : "Arial",
									"outlettype" : [ "bang", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "key",
									"fontsize" : 11.595187,
									"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
									"numinlets" : 0,
									"numoutlets" : 4,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "int", "int", "int", "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-45",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [ 59.5, 151.0, 59.5, 151.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-23", 0 ],
									"hidden" : 0,
									"midpoints" : [ 59.5, 121.0, 59.5, 121.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-45", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.connect 7 16",
					"fontsize" : 11.595187,
					"patching_rect" : [ 763.0, 75.0, 99.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-10",
					"fontname" : "Arial",
					"hidden" : 1,
					"saved_object_attributes" : 					{
						"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p controler",
					"fontsize" : 11.595187,
					"patching_rect" : [ 776.0, 150.0, 65.0, 20.0 ],
					"color" : [ 0.8, 0.839216, 0.709804, 1.0 ],
					"numinlets" : 0,
					"numoutlets" : 0,
					"id" : "obj-16",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 44.0, 899.0, 622.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 44.0, 899.0, 622.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.595187,
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
									"varname" : "autohelp_top_description[9]",
									"text" : "Change the interaction mode :",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 420.0, 28.5, 105.5, 34.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-66",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 420.0, 28.5, 105.5, 33.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-67"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[8]",
									"text" : "Change the optimization :",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 300.0, 28.5, 80.0, 34.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-64",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 300.0, 28.5, 80.0, 34.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-65"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[7]",
									"text" : "Change the widen value :",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 210.0, 28.5, 80.0, 34.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-49",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 210.0, 28.5, 80.0, 34.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-63"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[6]",
									"text" : "Change the azimuth :",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 105.0, 28.5, 80.0, 34.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-46",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "Change the \norder :",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 15.0, 28.5, 80.0, 34.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-43",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 15.0, 28.5, 80.0, 34.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-44"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"fontsize" : 7.180877,
									"patching_rect" : [ 817.0, 574.0, 52.0, 23.0 ],
									"numinlets" : 4,
									"numoutlets" : 0,
									"id" : "obj-19",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[2]",
									"text" : "Super encoder",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 569.5, 310.5, 89.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-6",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 569.5, 310.5, 89.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 311.5, 554.5, 84.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-57"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 163.25, 554.5, 38.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-56"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 72.0, 554.5, 54.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-55"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s ctrl.optim",
									"fontsize" : 11.595187,
									"patching_rect" : [ 401.5, 578.0, 67.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-50",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s ctrl.wide",
									"fontsize" : 11.595187,
									"patching_rect" : [ 208.25, 578.5, 62.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-51",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s ctrl.azimuth",
									"fontsize" : 11.595187,
									"patching_rect" : [ 15.0, 578.5, 79.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-52",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "textedit",
									"varname" : "textedit[2]",
									"text" : "optim maxRe",
									"bangmode" : 1,
									"fontsize" : 11.595187,
									"patching_rect" : [ 401.5, 554.5, 87.5, 20.0 ],
									"numinlets" : 1,
									"keymode" : 1,
									"numoutlets" : 4,
									"id" : "obj-53",
									"fontname" : "Arial",
									"outlettype" : [ "", "int", "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"patching_rect" : [ 208.25, 554.5, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-54",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"patching_rect" : [ 15.0, 554.5, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-58",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[5]",
									"text" : "Optimization :",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 311.5, 554.5, 84.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-59",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[4]",
									"text" : "Wide",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 163.25, 554.5, 38.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-60",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[3]",
									"text" : "Azimuth",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 72.0, 554.5, 54.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-61",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend set",
									"fontsize" : 11.595187,
									"patching_rect" : [ 402.5, 554.5, 72.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-62",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"patching_rect" : [ 817.0, 368.0, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-40",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend set",
									"fontsize" : 11.595187,
									"patching_rect" : [ 772.5, 271.5, 72.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-36",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "textedit",
									"varname" : "textedit[1]",
									"text" : "optim maxRe",
									"bangmode" : 1,
									"fontsize" : 11.595187,
									"patching_rect" : [ 772.5, 301.0, 94.5, 21.0 ],
									"numinlets" : 1,
									"keymode" : 1,
									"numoutlets" : 4,
									"id" : "obj-37",
									"fontname" : "Arial",
									"outlettype" : [ "", "int", "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"patching_rect" : [ 699.0, 263.0, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-35",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r ctrl.optim",
									"fontsize" : 11.595187,
									"patching_rect" : [ 772.5, 242.5, 65.0, 20.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-21",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r ctrl.wide",
									"fontsize" : 11.595187,
									"patching_rect" : [ 817.0, 336.5, 60.0, 20.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-26",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r ctrl.azimuth",
									"fontsize" : 11.595187,
									"patching_rect" : [ 699.0, 228.0, 77.0, 20.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-27",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.optim~ 7 basic",
									"fontsize" : 11.595187,
									"patching_rect" : [ 510.0, 391.0, 208.0, 20.0 ],
									"numinlets" : 15,
									"numoutlets" : 15,
									"id" : "obj-28",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"name" : "hoa.helpaudio.maxpat",
									"border" : 1,
									"args" : [ "@module", 3, "@noise", 1, "@vol", 0 ],
									"patching_rect" : [ 510.0, 135.0, 218.0, 87.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-30",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.wider~ 7",
									"fontsize" : 11.595187,
									"patching_rect" : [ 510.0, 435.0, 221.5, 20.0 ],
									"numinlets" : 16,
									"numoutlets" : 15,
									"id" : "obj-29",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"fontsize" : 11.595187,
									"patching_rect" : [ 510.0, 578.0, 221.5, 20.0 ],
									"numinlets" : 16,
									"numoutlets" : 0,
									"id" : "obj-69",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"fontsize" : 11.595187,
									"patching_rect" : [ 510.0, 495.0, 221.5, 20.0 ],
									"numinlets" : 15,
									"numoutlets" : 16,
									"id" : "obj-74",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"fontsize" : 11.595187,
									"patching_rect" : [ 834.5, 496.0, 32.5, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-73",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "startwindow",
									"fontsize" : 11.595187,
									"patching_rect" : [ 795.0, 466.0, 72.0, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-71",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7",
									"fontsize" : 11.595187,
									"patching_rect" : [ 510.0, 345.0, 208.0, 20.0 ],
									"numinlets" : 2,
									"numoutlets" : 15,
									"id" : "obj-31",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1",
									"fontsize" : 11.595187,
									"patching_rect" : [ 420.0, 37.0, 70.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-3",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend mode",
									"fontsize" : 11.595187,
									"patching_rect" : [ 420.0, 97.0, 85.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-22",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"fontsize" : 11.595187,
									"types" : [  ],
									"patching_rect" : [ 420.0, 67.0, 100.0, 20.0 ],
									"items" : [ "absolute", ",", "relative" ],
									"numinlets" : 1,
									"numoutlets" : 3,
									"id" : "obj-23",
									"fontname" : "Arial",
									"outlettype" : [ "int", "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1",
									"fontsize" : 11.595187,
									"patching_rect" : [ 300.0, 37.0, 70.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-32",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend optim",
									"fontsize" : 11.595187,
									"patching_rect" : [ 300.0, 97.0, 85.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-33",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"fontsize" : 11.595187,
									"types" : [  ],
									"patching_rect" : [ 300.0, 67.0, 100.0, 20.0 ],
									"items" : [ "basic", ",", "maxRe", ",", "inPhase" ],
									"numinlets" : 1,
									"numoutlets" : 3,
									"id" : "obj-34",
									"fontname" : "Arial",
									"outlettype" : [ "int", "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : 0.0,
									"maximum" : 1.0,
									"fontsize" : 11.595187,
									"patching_rect" : [ 210.0, 67.0, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"patching_rect" : [ 105.0, 67.0, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-18",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0.5",
									"fontsize" : 11.595187,
									"patching_rect" : [ 210.0, 35.0, 79.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-13",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend wide",
									"fontsize" : 11.595187,
									"patching_rect" : [ 210.0, 97.0, 80.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-16",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.pi",
									"fontsize" : 11.595187,
									"patching_rect" : [ 105.0, 35.0, 42.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-9",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend azimuth",
									"fontsize" : 11.595187,
									"patching_rect" : [ 105.0, 97.0, 97.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-12",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 12",
									"fontsize" : 11.595187,
									"patching_rect" : [ 15.0, 35.0, 76.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-8",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"minimum" : 1,
									"fontsize" : 11.595187,
									"patching_rect" : [ 15.0, 67.0, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend order",
									"fontsize" : 11.595187,
									"patching_rect" : [ 15.0, 97.0, 83.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-2",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description",
									"text" : "Controler messages and modes :",
									"linecount" : 3,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 725.0, 33.5, 88.0, 55.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-4",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.control",
									"mode" : 1,
									"patching_rect" : [ 15.0, 141.0, 405.5, 405.5 ],
									"optim" : 1,
									"azimuth" : 3.141593,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 1,
									"wide" : 0.5,
									"numoutlets" : 3,
									"order" : 12,
									"id" : "obj-1",
									"outlettype" : [ "float", "float", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 105.0, 28.5, 80.0, 34.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-39"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 706.5, 14.5, 125.0, 92.0 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-45"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 485.0, 301.0, 264.0, 174.0 ],
									"background" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-17"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-30", 0 ],
									"destination" : [ "obj-31", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 1 ],
									"destination" : [ "obj-69", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 2 ],
									"destination" : [ "obj-69", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 3 ],
									"destination" : [ "obj-69", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 4 ],
									"destination" : [ "obj-69", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 5 ],
									"destination" : [ "obj-69", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 6 ],
									"destination" : [ "obj-69", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 7 ],
									"destination" : [ "obj-69", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 8 ],
									"destination" : [ "obj-69", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 9 ],
									"destination" : [ "obj-69", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 10 ],
									"destination" : [ "obj-69", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 11 ],
									"destination" : [ "obj-69", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 12 ],
									"destination" : [ "obj-69", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 13 ],
									"destination" : [ "obj-69", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 14 ],
									"destination" : [ "obj-69", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 15 ],
									"destination" : [ "obj-69", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-73", 0 ],
									"destination" : [ "obj-69", 15 ],
									"hidden" : 0,
									"midpoints" : [ 844.0, 526.0, 722.0, 526.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-71", 0 ],
									"destination" : [ "obj-69", 15 ],
									"hidden" : 0,
									"midpoints" : [ 804.5, 526.0, 722.0, 526.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-62", 0 ],
									"destination" : [ "obj-53", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-52", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-54", 0 ],
									"destination" : [ "obj-51", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-40", 0 ],
									"destination" : [ "obj-29", 15 ],
									"hidden" : 0,
									"midpoints" : [ 826.5, 421.0, 722.0, 421.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 0 ],
									"destination" : [ "obj-37", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-35", 0 ],
									"destination" : [ "obj-31", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 309.5, 135.0, 24.5, 135.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-28", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 1 ],
									"destination" : [ "obj-28", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 2 ],
									"destination" : [ "obj-28", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 3 ],
									"destination" : [ "obj-28", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 4 ],
									"destination" : [ "obj-28", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 5 ],
									"destination" : [ "obj-28", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 6 ],
									"destination" : [ "obj-28", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 7 ],
									"destination" : [ "obj-28", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 8 ],
									"destination" : [ "obj-28", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 9 ],
									"destination" : [ "obj-28", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 10 ],
									"destination" : [ "obj-28", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 11 ],
									"destination" : [ "obj-28", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 12 ],
									"destination" : [ "obj-28", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 13 ],
									"destination" : [ "obj-28", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 14 ],
									"destination" : [ "obj-28", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-23", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 0 ],
									"destination" : [ "obj-74", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 1 ],
									"destination" : [ "obj-74", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 2 ],
									"destination" : [ "obj-74", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 3 ],
									"destination" : [ "obj-74", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 4 ],
									"destination" : [ "obj-74", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 5 ],
									"destination" : [ "obj-74", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 6 ],
									"destination" : [ "obj-74", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 7 ],
									"destination" : [ "obj-74", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 8 ],
									"destination" : [ "obj-74", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 9 ],
									"destination" : [ "obj-74", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 10 ],
									"destination" : [ "obj-74", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 11 ],
									"destination" : [ "obj-74", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 12 ],
									"destination" : [ "obj-74", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 13 ],
									"destination" : [ "obj-74", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 14 ],
									"destination" : [ "obj-74", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 0 ],
									"destination" : [ "obj-29", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 1 ],
									"destination" : [ "obj-29", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 2 ],
									"destination" : [ "obj-29", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 3 ],
									"destination" : [ "obj-29", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 4 ],
									"destination" : [ "obj-29", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 5 ],
									"destination" : [ "obj-29", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 6 ],
									"destination" : [ "obj-29", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 7 ],
									"destination" : [ "obj-29", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 8 ],
									"destination" : [ "obj-29", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 9 ],
									"destination" : [ "obj-29", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 10 ],
									"destination" : [ "obj-29", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 11 ],
									"destination" : [ "obj-29", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 12 ],
									"destination" : [ "obj-29", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 13 ],
									"destination" : [ "obj-29", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 14 ],
									"destination" : [ "obj-29", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-35", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-40", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 429.5, 135.0, 24.5, 135.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-28", 14 ],
									"hidden" : 0,
									"midpoints" : [ 782.0, 376.0, 708.5, 376.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 24.5, 117.0, 24.5, 117.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 219.5, 135.0, 24.5, 135.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-20", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 114.5, 135.0, 24.5, 135.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 2 ],
									"destination" : [ "obj-62", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 1 ],
									"destination" : [ "obj-54", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 2 ],
									"destination" : [ "obj-50", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 11.595187,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 11.595187
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p color",
					"fontsize" : 11.595187,
					"patching_rect" : [ 776.0, 169.0, 45.0, 20.0 ],
					"color" : [ 0.8, 0.839216, 0.709804, 1.0 ],
					"numinlets" : 0,
					"numoutlets" : 0,
					"id" : "obj-25",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 899.0, 622.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 899.0, 622.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.595187,
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
									"varname" : "autohelp_top_description[7]",
									"text" : "circle inner color :",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 751.0, 160.0, 112.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-2",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 751.0, 160.0, 112.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1. 0. 0. 0.",
									"fontsize" : 11.595187,
									"patching_rect" : [ 751.0, 139.0, 112.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-4",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend cicolorin",
									"fontsize" : 11.595187,
									"patching_rect" : [ 751.0, 219.0, 99.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-5",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "swatch",
									"presentation_rect" : [ 550.0, 231.0, 128.0, 32.0 ],
									"patching_rect" : [ 751.0, 181.0, 128.0, 32.0 ],
									"presentation" : 1,
									"numinlets" : 3,
									"numoutlets" : 2,
									"id" : "obj-6",
									"outlettype" : [ "", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[6]",
									"text" : "Shadow",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 499.0, 143.0, 54.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-56",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 499.0, 143.0, 54.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-57"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[5]",
									"text" : "Background color :",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 15.0, 36.0, 116.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-54",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 15.0, 36.0, 112.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-55"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[4]",
									"text" : "Circle color :",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 150.0, 36.0, 82.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-52",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 150.0, 36.0, 78.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-53"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[3]",
									"text" : "Biggest contribution color :",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 286.0, 36.0, 152.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-50",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 286.0, 36.0, 152.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-51"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[2]",
									"text" : "Positive harmonics color :",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 446.0, 36.0, 146.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-48",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 446.0, 36.0, 146.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-49"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "Negative harmonics color :",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 595.0, 36.0, 151.5, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-43",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 595.0, 36.0, 151.5, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-44"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[9]",
									"text" : "circle shadow color :",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 751.0, 36.0, 137.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-66",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 751.0, 36.0, 137.0, 20.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-67"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description",
									"text" : "Custom colors.",
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 578.0, 295.5, 122.0, 23.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-38",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 570.0, 283.5, 140.0, 43.0 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-45"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"fontsize" : 7.180877,
									"patching_rect" : [ 456.0, 517.0, 52.0, 23.0 ],
									"numinlets" : 4,
									"numoutlets" : 0,
									"id" : "obj-37",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"patching_rect" : [ 472.0, 143.0, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-36",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "shadow $1",
									"fontsize" : 11.595187,
									"patching_rect" : [ 472.0, 172.0, 66.0, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-32",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1. 0. 0. 0.",
									"fontsize" : 11.595187,
									"patching_rect" : [ 751.0, 15.0, 112.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-10",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend cishadcolor",
									"fontsize" : 11.595187,
									"patching_rect" : [ 751.0, 95.0, 115.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-29",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "swatch",
									"presentation_rect" : [ 535.0, 216.0, 128.0, 32.0 ],
									"patching_rect" : [ 751.0, 57.0, 128.0, 32.0 ],
									"presentation" : 1,
									"numinlets" : 3,
									"numoutlets" : 2,
									"id" : "obj-31",
									"outlettype" : [ "", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1. 1. 0.99 1.",
									"fontsize" : 11.595187,
									"patching_rect" : [ 15.0, 15.0, 125.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-30",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0. 0. 0.01 1.",
									"fontsize" : 11.595187,
									"patching_rect" : [ 150.0, 15.0, 125.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-28",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0. 1. 0. 0.",
									"fontsize" : 11.595187,
									"patching_rect" : [ 286.0, 15.0, 112.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-27",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1. 0. 0. 0.",
									"fontsize" : 11.595187,
									"patching_rect" : [ 595.0, 15.0, 112.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-26",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0. 0. 1. 0.",
									"fontsize" : 11.595187,
									"patching_rect" : [ 446.0, 15.0, 112.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-25",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend cocolor",
									"fontsize" : 11.595187,
									"patching_rect" : [ 286.0, 93.0, 94.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-23",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "swatch",
									"presentation_rect" : [ 505.0, 186.0, 128.0, 32.0 ],
									"patching_rect" : [ 286.0, 57.0, 128.0, 32.0 ],
									"presentation" : 1,
									"numinlets" : 3,
									"numoutlets" : 2,
									"id" : "obj-24",
									"outlettype" : [ "", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend nhcolor",
									"fontsize" : 11.595187,
									"patching_rect" : [ 595.0, 95.0, 94.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "swatch",
									"presentation_rect" : [ 520.0, 201.0, 128.0, 32.0 ],
									"patching_rect" : [ 595.0, 57.0, 128.0, 32.0 ],
									"presentation" : 1,
									"numinlets" : 3,
									"numoutlets" : 2,
									"id" : "obj-21",
									"outlettype" : [ "", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend phcolor",
									"fontsize" : 11.595187,
									"patching_rect" : [ 446.0, 95.0, 94.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-15",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "swatch",
									"presentation_rect" : [ 505.0, 186.0, 128.0, 32.0 ],
									"patching_rect" : [ 446.0, 57.0, 128.0, 32.0 ],
									"presentation" : 1,
									"numinlets" : 3,
									"numoutlets" : 2,
									"id" : "obj-16",
									"outlettype" : [ "", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend cicolor",
									"fontsize" : 11.595187,
									"patching_rect" : [ 150.0, 93.0, 90.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "swatch",
									"presentation_rect" : [ 490.0, 171.0, 128.0, 32.0 ],
									"patching_rect" : [ 150.0, 57.0, 128.0, 32.0 ],
									"presentation" : 1,
									"numinlets" : 3,
									"numoutlets" : 2,
									"id" : "obj-18",
									"outlettype" : [ "", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.control",
									"cocolor" : [ 0.0, 1.0, 0.0, 1.0 ],
									"phcolor" : [ 0.0, 0.0, 1.0, 1.0 ],
									"patching_rect" : [ 15.0, 135.0, 405.0, 405.0 ],
									"bgcolor" : [ 1.0, 1.0, 0.99, 1.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"cicolor" : [ 0.0, 0.0, 0.01, 1.0 ],
									"numinlets" : 1,
									"nhcolor" : [ 1.0, 0.0, 0.0, 1.0 ],
									"cishadcolor" : [ 1.0, 0.0, 0.0, 1.0 ],
									"numoutlets" : 3,
									"id" : "obj-1",
									"cicolorin" : [ 1.0, 0.0, 0.0, 1.0 ],
									"outlettype" : [ "float", "float", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend bgcolor",
									"fontsize" : 11.595187,
									"patching_rect" : [ 15.0, 93.0, 94.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-33",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "swatch",
									"presentation_rect" : [ 475.0, 156.0, 128.0, 32.0 ],
									"patching_rect" : [ 15.0, 57.0, 128.0, 32.0 ],
									"presentation" : 1,
									"numinlets" : 3,
									"numoutlets" : 2,
									"id" : "obj-34",
									"outlettype" : [ "", "float" ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 760.5, 247.0, 733.5, 247.0, 733.5, 123.0, 24.5, 123.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 24.5, 123.0, 24.5, 123.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 481.5, 198.0, 446.0, 198.0, 446.0, 123.0, 24.5, 123.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-29", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-30", 0 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 760.5, 123.0, 24.5, 123.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-23", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 295.5, 123.0, 24.5, 123.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-20", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 604.5, 124.0, 24.5, 124.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 159.5, 123.0, 24.5, 123.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-15", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [ 455.5, 124.0, 24.5, 124.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-31", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 11.595187,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 11.595187
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 763.0, 127.0, 101.0, 67.0 ],
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"numinlets" : 1,
					"rounded" : 15,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-49"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 569.5, 310.5, 89.0, 20.0 ],
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"numinlets" : 1,
					"rounded" : 6,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-54"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend set",
					"fontsize" : 11.595187,
					"patching_rect" : [ 390.0, 546.5, 72.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-22",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"name" : "hoa.helpaudio.maxpat",
					"border" : 1,
					"args" : [ "@module", 3, "@noise", 1, "@vol", 80 ],
					"patching_rect" : [ 510.0, 150.0, 218.0, 87.0 ],
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-30",
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 485.0, 301.0, 264.0, 174.0 ],
					"background" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"numinlets" : 1,
					"rounded" : 15,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-50"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 0 ],
					"destination" : [ "obj-69", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 1 ],
					"destination" : [ "obj-69", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 2 ],
					"destination" : [ "obj-69", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 3 ],
					"destination" : [ "obj-69", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 4 ],
					"destination" : [ "obj-69", 4 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 5 ],
					"destination" : [ "obj-69", 5 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 6 ],
					"destination" : [ "obj-69", 6 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 7 ],
					"destination" : [ "obj-69", 7 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 8 ],
					"destination" : [ "obj-69", 8 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 9 ],
					"destination" : [ "obj-69", 9 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 10 ],
					"destination" : [ "obj-69", 10 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 11 ],
					"destination" : [ "obj-69", 11 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 12 ],
					"destination" : [ "obj-69", 12 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 13 ],
					"destination" : [ "obj-69", 13 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 14 ],
					"destination" : [ "obj-69", 14 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 15 ],
					"destination" : [ "obj-69", 15 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-73", 0 ],
					"destination" : [ "obj-69", 15 ],
					"hidden" : 0,
					"midpoints" : [ 844.0, 526.0, 722.0, 526.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-71", 0 ],
					"destination" : [ "obj-69", 15 ],
					"hidden" : 0,
					"midpoints" : [ 804.5, 526.0, 722.0, 526.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 1 ],
					"destination" : [ "obj-1", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 2 ],
					"destination" : [ "obj-1", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 3 ],
					"destination" : [ "obj-1", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 4 ],
					"destination" : [ "obj-1", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 5 ],
					"destination" : [ "obj-1", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 6 ],
					"destination" : [ "obj-1", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 7 ],
					"destination" : [ "obj-1", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 8 ],
					"destination" : [ "obj-1", 8 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 9 ],
					"destination" : [ "obj-1", 9 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 10 ],
					"destination" : [ "obj-1", 10 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 11 ],
					"destination" : [ "obj-1", 11 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 12 ],
					"destination" : [ "obj-1", 12 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 13 ],
					"destination" : [ "obj-1", 13 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 14 ],
					"destination" : [ "obj-1", 14 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"midpoints" : [ 772.5, 66.0, 772.5, 66.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-1", 15 ],
					"hidden" : 0,
					"midpoints" : [ 826.5, 421.0, 722.0, 421.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 2 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 2 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 1 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-20", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 0 ],
					"destination" : [ "obj-40", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-5", 14 ],
					"hidden" : 0,
					"midpoints" : [ 797.0, 376.0, 708.5, 376.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-36", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 1 ],
					"destination" : [ "obj-5", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 2 ],
					"destination" : [ "obj-5", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 3 ],
					"destination" : [ "obj-5", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 4 ],
					"destination" : [ "obj-5", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 5 ],
					"destination" : [ "obj-5", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 6 ],
					"destination" : [ "obj-5", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 7 ],
					"destination" : [ "obj-5", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 8 ],
					"destination" : [ "obj-5", 8 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 9 ],
					"destination" : [ "obj-5", 9 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 10 ],
					"destination" : [ "obj-5", 10 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 11 ],
					"destination" : [ "obj-5", 11 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 12 ],
					"destination" : [ "obj-5", 12 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 13 ],
					"destination" : [ "obj-5", 13 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 14 ],
					"destination" : [ "obj-5", 14 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-74", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 1 ],
					"destination" : [ "obj-74", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 2 ],
					"destination" : [ "obj-74", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 3 ],
					"destination" : [ "obj-74", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 4 ],
					"destination" : [ "obj-74", 4 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 5 ],
					"destination" : [ "obj-74", 5 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 6 ],
					"destination" : [ "obj-74", 6 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 7 ],
					"destination" : [ "obj-74", 7 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 8 ],
					"destination" : [ "obj-74", 8 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 9 ],
					"destination" : [ "obj-74", 9 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 10 ],
					"destination" : [ "obj-74", 10 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 11 ],
					"destination" : [ "obj-74", 11 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 12 ],
					"destination" : [ "obj-74", 12 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 13 ],
					"destination" : [ "obj-74", 13 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 14 ],
					"destination" : [ "obj-74", 14 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
