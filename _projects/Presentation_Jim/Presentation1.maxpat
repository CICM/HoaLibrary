{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 1,
			"revision" : 2,
			"architecture" : "x86"
		}
,
		"rect" : [ 0.0, 44.0, 1440.0, 806.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-33",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1370.599976, 274.0, 72.0, 17.0 ],
					"text" : "1, 15 30000"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-43",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 1370.599976, 312.0, 46.0, 19.0 ],
					"text" : "line 0."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-40",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 772.5, 693.0, 33.0, 18.0 ],
					"text" : "stop"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-38",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 671.0, 693.0, 74.0, 18.0 ],
					"text" : "startwindow"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 0,
					"patching_rect" : [ 356.75, 739.0, 221.5, 20.0 ],
					"text" : "hoa.dac~ 1:16"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-21",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1282.0, 341.5, 88.0, 17.0 ],
					"text" : "storagewindow"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-23",
					"maxclass" : "flonum",
					"minimum" : 1.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 1370.599976, 341.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-27",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"patching_rect" : [ 1185.0, 356.0, 59.5, 19.0 ],
					"restore" : 					{
						"SpaceJim" : [ 0.999762, 1.0, 1.0, 0.347704, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.312381, 0.983585, 0.994141 ]
					}
,
					"text" : "autopattr",
					"varname" : "u239001704"
				}

			}
, 			{
				"box" : 				{
					"autorestore" : "SpaceJim.json",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-81",
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1356.0, 381.5, 110.0, 32.0 ],
					"saved_object_attributes" : 					{
						"client_rect" : [ 4, 44, 358, 172 ],
						"parameter_enable" : 0,
						"storage_rect" : [ 766, 44, 1220, 302 ]
					}
,
					"text" : "pattrstorage jim @savemode 2",
					"varname" : "jim"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "preset",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "preset", "int", "preset", "int" ],
					"patching_rect" : [ 1185.0, 381.5, 152.800003, 30.0 ],
					"pattrstorage" : "jim"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-26",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 51.600006, 421.0, 67.0, 18.0 ],
					"text" : "resetangle"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-22",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 46.25, 18.0, 34.0, 17.0 ],
					"text" : "read"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-20",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1.25, 18.0, 35.0, 17.0 ],
					"text" : "write"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-16",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 106.0, 18.0, 40.0, 17.0 ],
					"text" : "erase"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 15,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 357.27774, 202.0, 220.767059, 20.0 ],
					"saved_object_attributes" : 					{
						"optim" : "inPhase"
					}
,
					"text" : "hoa.optim~ 7 inPhase"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-104",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 596.0, 190.0, 37.0, 18.0 ],
					"text" : "clear"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-102",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 718.0, 42.0, 60.0, 20.0 ],
					"text" : "loadbang"
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
					"patching_rect" : [ 1039.3125, 42.0, 60.0, 20.0 ],
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
					"patching_rect" : [ 559.0448, 98.0, 93.0, 20.0 ],
					"text" : "hoa.soundgrain"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-96",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 772.5, 190.0, 78.0, 18.0 ],
					"text" : "buffer hoaIr1"
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
					"patching_rect" : [ 457.950958, 98.0, 89.0, 20.0 ],
					"text" : "hoa.soundcoat"
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
					"patching_rect" : [ 356.857117, 63.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-89",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 356.857117, 98.0, 94.0, 20.0 ],
					"text" : "hoa.soundclack"
				}

			}
, 			{
				"box" : 				{
					"angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ],
					"channels" : 16,
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"id" : "obj-87",
					"loudspeakers" : 16,
					"ls" : 16,
					"ls_angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ],
					"maxclass" : "hoa.meter~",
					"numinlets" : 16,
					"numoutlets" : 2,
					"outlettype" : [ "list", "list" ],
					"patching_rect" : [ 647.625, 409.0, 248.5, 248.5 ]
				}

			}
, 			{
				"box" : 				{
					"channels" : 16,
					"id" : "obj-54",
					"maxclass" : "hoa.gain~",
					"numinlets" : 17,
					"numoutlets" : 17,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 356.75, 631.0, 235.0, 18.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.352446, 0.352446, 0.352446, 1.0 ],
					"bordercolor" : [ 0.196168, 0.196168, 0.196168, 1.0 ],
					"circlecolor" : [ 0.196078, 0.196078, 0.196078, 1.0 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"fisheyecolor" : [ 0.687659, 0.179729, 0.179729, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 14.0,
					"id" : "obj-86",
					"maxclass" : "hoa.recomposer",
					"miccolor" : [ 0.062419, 0.329952, 0.487508, 1.0 ],
					"nmics" : 16,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "list" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 51.600006, 458.0, 225.0, 225.0 ],
					"rectselectcolor" : [ 0.386326, 0.519675, 0.8, 1.0 ],
					"selmiccolor" : [ 0.114856, 0.605484, 0.893993, 1.0 ]
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
					"patching_rect" : [ 1039.3125, 75.0, 116.0, 17.0 ],
					"text" : "fill 1, apply hamming"
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
					"patching_rect" : [ 1322.5, 170.5, 73.0, 19.0 ],
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
					"patching_rect" : [ 1191.5, 170.5, 79.0, 19.0 ],
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
					"patching_rect" : [ 1310.0, 36.5, 92.0, 19.0 ],
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
					"patching_rect" : [ 1191.5, 36.5, 86.0, 19.0 ],
					"text" : "loadmess 400."
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
					"patching_rect" : [ 1310.0, 170.5, 104.0, 20.0 ],
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
					"patching_rect" : [ 1310.0, 170.5, 104.0, 20.0 ],
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
					"patching_rect" : [ 1322.5, 200.5, 50.0, 19.0 ]
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
					"patching_rect" : [ 1322.5, 231.5, 81.0, 17.0 ],
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
					"patching_rect" : [ 1179.0, 170.5, 104.0, 20.0 ],
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
					"patching_rect" : [ 1179.0, 170.5, 104.0, 20.0 ],
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
					"patching_rect" : [ 1191.5, 200.5, 50.0, 19.0 ]
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
					"patching_rect" : [ 1191.5, 231.5, 74.0, 17.0 ],
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
					"patching_rect" : [ 1297.5, 36.5, 104.0, 20.0 ],
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
					"patching_rect" : [ 1297.5, 36.5, 104.0, 20.0 ],
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
					"patching_rect" : [ 1310.0, 66.5, 50.0, 19.0 ]
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
					"patching_rect" : [ 1310.0, 97.5, 54.0, 17.0 ],
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
					"patching_rect" : [ 1179.0, 36.5, 105.0, 20.0 ],
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
					"patching_rect" : [ 1179.0, 36.5, 104.0, 20.0 ],
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
					"patching_rect" : [ 1191.5, 66.5, 50.0, 19.0 ]
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
					"patching_rect" : [ 1191.5, 97.5, 47.0, 17.0 ],
					"text" : "size $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-78",
					"maxclass" : "meter~",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 945.5, 99.5, 80.0, 13.0 ]
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
							"revision" : 2,
							"architecture" : "x86"
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
									"patching_rect" : [ 77.5, 163.5, 32.5, 19.0 ],
									"text" : "*~ 1"
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
					"patching_rect" : [ 934.0, 36.5, 69.0, 19.0 ],
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
					"id" : "obj-80",
					"maxclass" : "gain~",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 934.0, 66.5, 91.5, 16.0 ]
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
					"patching_rect" : [ 1039.3125, 101.5, 121.0, 19.0 ],
					"text" : "buffer~ granular 1000"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-83",
					"linecount" : 3,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 934.0, 187.5, 220.791656, 45.0 ],
					"text" : "hoa.plug~ 7 hoa.granular~ no @name granular @size 400 @delay 3000 @feedback 0.9 @rarefaction 0."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 934.0, 366.0, 221.5, 20.0 ],
					"saved_object_attributes" : 					{
						"mode" : 0,
						"ramp" : 20.0
					}
,
					"text" : "hoa.recomposer~ 7 16"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 15,
					"numoutlets" : 16,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 934.0, 270.0, 221.5, 20.0 ],
					"text" : "hoa.projector~ 7 16"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-49",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 16,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 934.0, 312.0, 221.5, 20.0 ],
					"text" : "hoa.space~ 16"
				}

			}
, 			{
				"box" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-18",
					"maxclass" : "hoa.scope~",
					"numinlets" : 15,
					"numoutlets" : 0,
					"order" : 7,
					"patching_rect" : [ 934.25, 432.5, 221.25, 221.25 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-53",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 356.5448, 514.5, 221.5, 20.0 ],
					"saved_object_attributes" : 					{
						"mode" : 2,
						"ramp" : 20.0
					}
,
					"text" : "hoa.recomposer~ 7 16"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-52",
					"maxclass" : "newobj",
					"numinlets" : 15,
					"numoutlets" : 16,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 356.5448, 434.5, 221.5, 20.0 ],
					"text" : "hoa.projector~ 7 16"
				}

			}
, 			{
				"box" : 				{
					"coeffs" : [ 0.999762, 1.0, 1.0, 0.347704, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.312381, 0.983585, 0.994141 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"id" : "obj-51",
					"maxclass" : "hoa.space",
					"nmics" : 16,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "list" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 1191.5, 432.5, 248.5, 248.5 ],
					"varname" : "SpaceJim"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-42",
					"maxclass" : "number",
					"maximum" : 44100,
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 639.625, 242.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-17",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 708.125, 242.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-44",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 708.125, 282.5, 85.0, 19.0 ],
					"text" : "prepend factor"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-45",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 15,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"patching_rect" : [ 639.625, 315.0, 208.0, 19.0 ],
					"text" : "hoa.plug~ 7 hoa.all no"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-47",
					"linecount" : 3,
					"maxclass" : "newobj",
					"numinlets" : 15,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 356.75, 381.5, 221.2948, 45.0 ],
					"text" : "hoa.plug~ 7 hoa.decorrelation~ post @maxsize 44100 @delay 1000 @factor 0."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-46",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 2,
							"architecture" : "x86"
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
									"patching_rect" : [ 50.0, 130.0, 41.0, 19.0 ],
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
									"patching_rect" : [ 50.0, 100.0, 59.5, 19.0 ],
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
					"patching_rect" : [ 830.0, 42.0, 51.0, 19.0 ],
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
					"hidden" : 1,
					"id" : "obj-37",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 830.0, 80.0, 99.0, 19.0 ],
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
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-58",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 658.625, 136.5, 73.0, 19.0 ],
					"text" : "loadmess 1."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-55",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 722.125, 136.5, 73.0, 19.0 ],
					"text" : "loadmess 0."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-29",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 722.125, 160.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-31",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 658.625, 160.5, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-7",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 722.125, 196.5, 43.0, 17.0 ],
					"text" : "dry $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-32",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 658.625, 196.5, 45.0, 17.0 ],
					"text" : "wet $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-34",
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 15,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 356.928558, 308.5, 221.116241, 32.0 ],
					"saved_object_attributes" : 					{
						"buffer" : "hoaIr1",
						"wet" : 0.44
					}
,
					"text" : "hoa.convolve~ 7 @buffer hoaIr1 @channel 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-39",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 718.0, 73.5, 74.0, 17.0 ],
					"text" : "normalize 1."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-35",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 658.625, 73.5, 49.0, 17.0 ],
					"text" : "replace"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-36",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 658.625, 111.5, 147.0, 19.0 ],
					"text" : "buffer~ hoaIr1 Chapel.wav"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-19",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 253.0, 18.0, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 116.0, 52.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-13",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 116.0, 77.0, 47.0, 17.0 ],
					"text" : "limit $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-11",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 175.0, 18.0, 65.0, 17.0 ],
					"text" : "0, 1 30000"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 175.0, 52.0, 46.0, 19.0 ],
					"text" : "line 0."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-5",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 175.0, 77.0, 50.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 40.0, 52.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-4",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 40.0, 77.0, 59.0, 17.0 ],
					"text" : "record $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 40.0, 116.5, 104.0, 19.0 ],
					"text" : "prepend trajectory"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 15,
					"numoutlets" : 16,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 356.75, 560.5, 221.5, 20.0 ],
					"saved_object_attributes" : 					{
						"angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0 ],
						"config" : 5.1,
						"loudspeakers" : 16,
						"ls" : 16,
						"ls_angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0 ],
						"mode" : "ambisonics",
						"offset" : 0.0,
						"pinnaesize" : "small",
						"restitution" : "panning"
					}
,
					"text" : "hoa.decoder~ 7 @mode ambisonics"
				}

			}
, 			{
				"box" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"groups_parameters" : [ "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "" ],
					"id" : "obj-2",
					"maxclass" : "hoa.map",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "list", "list", "list" ],
					"patching_rect" : [ 34.0, 139.25, 248.25, 248.25 ],
					"sources_parameters" : [ "source", 0, 0.171571, -2.754424, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.033378, -2.797678, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.095514, -1.131924, 0, 0.2, 0.2, 0.2, 1.0, "" ],
					"trajectory_parameters" : [ "slot", 0, "source", 0, 0.341039, 2.356114, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 1, 0, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 1, "source", 0, 0.341039, 2.356114, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 1, 0, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 2, "source", 0, 0.341039, 2.356114, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.753669, -1.341652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.861001, -0.718433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 3, "source", 0, 0.257943, 2.356114, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.670573, -1.341652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.944097, -0.718433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 4, "source", 0, -0.157536, 2.480758, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.255094, -1.217008, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.359577, -0.593789, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 5, "source", 0, -0.323728, 2.605402, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.088902, -1.092365, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.525769, -0.469146, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 6, "source", 0, -0.614563, 2.771594, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.798067, -0.926173, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.816604, -0.302954, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 7, "source", 0, -1.237782, 3.353265, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.174848, -0.344502, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.439823, 0.278717, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 8, "source", 0, -1.27933, 3.436361, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.1333, -0.261406, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.481371, 0.361813, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 9, "source", 0, -1.445522, 3.685649, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.032892, -0.012118, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.647563, 0.611101, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 10, "source", 0, -1.528618, 3.934936, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.115988, 0.237169, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.730659, 0.860389, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 11, "source", 0, -1.528618, 4.05958, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.115988, 0.361813, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.730659, 0.985032, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 12, "source", 0, -1.528618, 4.05958, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.115988, 0.361813, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.730659, 0.985032, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 13, "source", 0, -1.071591, 4.558156, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.341039, 0.860389, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.273632, 1.483608, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 14, "source", 0, -1.071591, 4.558156, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.341039, 0.860389, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.273632, 1.483608, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 15, "source", 0, -0.406824, 4.848991, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.005806, 1.151224, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.608865, 1.774443, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 16, "source", 0, -0.032892, 4.973635, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.379738, 1.275868, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.234933, 1.899087, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 17, "source", 0, 0.216396, 5.015182, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.629025, 1.317416, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.985645, 1.940635, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 18, "source", 0, 1.171998, 5.015182, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.584628, 1.317416, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.030043, 1.940635, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 19, "source", 0, 1.171998, 5.015182, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.584628, 1.317416, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.030043, 1.940635, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 20, "source", 0, 2.044505, 4.308867, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.457135, 0.611101, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.157536, 1.23432, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 21, "source", 0, 2.169149, 4.184224, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.581779, 0.486457, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.032892, 1.109676, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 22, "source", 0, 2.33534, 3.768744, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.747971, 0.070978, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.1333, 0.694197, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 23, "source", 0, 2.33534, 3.602553, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.747971, -0.095214, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.1333, 0.528005, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 24, "source", 0, 2.33534, 3.394813, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.747971, -0.302954, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.1333, 0.320265, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 25, "source", 0, 2.376889, 2.231471, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.789518, -1.466296, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.174848, -0.843077, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 26, "source", 0, 2.376889, 2.106827, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.789518, -1.59094, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.174848, -0.967721, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 27, "source", 0, 2.293792, 1.649799, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.706423, -2.047967, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.091752, -1.424748, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 28, "source", 0, 1.629025, 0.154074, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.041656, -3.543693, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.573015, -2.920474, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 29, "source", 0, 1.379738, -0.095214, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.792368, -3.792981, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.822303, -3.169762, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 30, "source", 0, 0.839615, -0.676885, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.252245, -4.374652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.362426, -3.751433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 31, "source", 0, 0.673423, -0.801529, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.086053, -4.499296, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.528618, -3.876077, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 32, "source", 0, 0.548779, -0.801529, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.961409, -4.499296, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.653262, -3.876077, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 33, "source", 0, 0.174848, -0.801529, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.587478, -4.499296, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.027193, -3.876077, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 34, "source", 0, -0.032892, -0.718433, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.379738, -4.4162, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.234933, -3.792981, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 35, "source", 0, -0.032892, -0.676885, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.379738, -4.374652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.234933, -3.751433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 36, "source", 0, -0.032892, -0.676885, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.379738, -4.374652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.234933, -3.751433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 37, "source", 0, -0.032892, -0.676885, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.379738, -4.374652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.234933, -3.751433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 38, "source", 0, -0.115988, -0.676885, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.296642, -4.374652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.318029, -3.751433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 39, "source", 0, -0.240632, -0.676885, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.171998, -4.374652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.442673, -3.751433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 40, "source", 0, -0.323728, -0.635337, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.088902, -4.333104, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.525769, -3.709885, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 41, "source", 0, -0.614563, -0.427598, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.798067, -4.125364, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.816604, -3.502145, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 42, "source", 0, -0.656111, -0.38605, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.756519, -4.083817, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.858152, -3.460597, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 43, "source", 0, -0.863851, -0.136762, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.548779, -3.834529, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.065892, -3.21131, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 44, "source", 0, -0.905399, -0.053666, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.507231, -3.751433, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.10744, -3.128214, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 45, "source", 0, -0.946947, 0.112526, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.465683, -3.585241, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.148988, -2.962022, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 46, "source", 0, -0.946947, 0.154074, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.465683, -3.543693, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.148988, -2.920474, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 47, "source", 0, -0.946947, 0.361813, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.465683, -3.335953, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.148988, -2.712734, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 48, "source", 0, -0.946947, 0.486457, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.465683, -3.21131, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.148988, -2.58809, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 49, "source", 0, -0.822303, 0.611101, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.590327, -3.086666, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.024344, -2.463447, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 50, "source", 0, -0.739207, 0.611101, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.673423, -3.086666, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.941248, -2.463447, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 51, "source", 0, -0.573015, 0.694197, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.839615, -3.00357, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.775056, -2.380351, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 52, "source", 0, -0.406824, 0.735745, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.005806, -2.962022, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.608865, -2.338803, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 53, "source", 0, -0.323728, 0.818841, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.088902, -2.878926, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.525769, -2.255707, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 54, "source", 0, -0.28218, 0.818841, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.13045, -2.878926, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.484221, -2.255707, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 55, "source", 0, -0.115988, 0.901937, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.296642, -2.79583, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.318029, -2.172611, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 56, "source", 0, -0.07444, 0.901937, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.33819, -2.79583, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.276481, -2.172611, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 57, "source", 0, 0.008656, 0.901937, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.421286, -2.79583, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.193385, -2.172611, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 58, "source", 0, 0.299491, 0.943484, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.712121, -2.754282, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.90255, -2.131063, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 59, "source", 0, 1.088902, 0.985032, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.501532, -2.712734, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.113139, -2.089515, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 60, "source", 0, 1.296642, 1.02658, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.709272, -2.671186, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.905399, -2.047967, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 61, "source", 0, 1.712121, 1.151224, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.124751, -2.546543, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.489919, -1.923323, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 62, "source", 0, 2.044505, 1.400512, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.457135, -2.297255, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.157536, -1.674036, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 63, "source", 0, 2.252245, 1.691347, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.664875, -2.006419, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.050204, -1.3832, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 64, "source", 0, 2.33534, 2.148375, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.747971, -1.549392, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.1333, -0.926173, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 65, "source", 0, 2.376889, 2.356114, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.789518, -1.341652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.174848, -0.718433, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 66, "source", 0, 2.376889, 2.563854, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.789518, -1.133913, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.174848, -0.510693, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 67, "source", 0, 2.210697, 2.896238, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.623327, -0.801529, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.008656, -0.17831, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 68, "source", 0, 1.961409, 3.062429, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.374039, -0.635337, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.240632, -0.012118, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 69, "source", 0, 1.670573, 3.127637, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 3.083204, -0.57013, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.531467, 0.106755, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 70, "source", 0, 1.379738, 3.335376, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.792368, -0.36239, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.822303, 0.314495, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 71, "source", 0, 1.047354, 3.543116, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.459984, -0.154651, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.154687, 0.522235, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 72, "source", 0, 0.839615, 3.584664, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.252245, -0.113103, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.362426, 0.563782, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 73, "source", 0, 0.839615, 3.584664, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.252245, -0.113103, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.362426, 0.563782, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 74, "source", 0, 0.179584, 3.615916, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.922199, 0.061722, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.739007, 0.407534, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 75, "source", 0, -0.043176, 3.620115, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.914762, 0.179842, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.760782, 0.299793, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 76, "source", 0, -0.810995, 3.528369, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.832892, 0.582378, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.784285, -0.080983, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 77, "source", 0, -0.810995, 3.528369, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.832892, 0.582378, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.784285, -0.080983, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 78, "source", 0, -1.738337, 3.175733, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.60598, 1.058059, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.695304, -0.562295, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 79, "source", 0, -2.517269, 2.60201, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.26845, 1.445577, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.485872, -0.991168, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 80, "source", 0, -2.703917, 2.407474, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.157361, 1.535961, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.407995, -1.098991, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 81, "source", 0, -3.007909, 2.01484, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.936302, 1.67988, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.244372, -1.281316, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 82, "source", 0, -3.43325, 1.148865, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.459376, 1.867521, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.861772, -1.564474, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 83, "source", 0, -3.597584, -0.405575, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.370734, 1.887118, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.121914, -1.781956, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 84, "source", 0, -2.824668, -2.264586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.321452, 1.397291, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.848805, -1.571547, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 85, "source", 0, -2.493354, -2.624935, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.497869, 1.206254, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.053049, -1.442677, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 86, "source", 0, -2.493354, -2.624935, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.497869, 1.206254, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.053049, -1.442677, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 87, "source", 0, -0.833299, -3.523168, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.901442, 0.288403, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.636074, -0.716585, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 88, "source", 0, 0.528529, -3.581586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.873317, -0.435137, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.785086, -0.060822, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 89, "source", 0, 0.790211, -3.533082, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.836289, -0.571579, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.784731, 0.070478, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 90, "source", 0, 2.671194, -2.443731, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.177976, -1.520208, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.422693, 1.079897, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 91, "source", 0, 3.100998, -1.868397, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.854733, -1.722815, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.181546, 1.33947, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 92, "source", 0, 3.460639, -1.06352, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.413003, -1.87832, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.822778, 1.585328, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 93, "source", 0, 3.536737, -0.773685, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.256253, -1.906041, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.688855, 1.647941, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 94, "source", 0, 3.61188, -0.247836, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.025411, -1.923022, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.440301, 1.731001, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 95, "source", 0, 3.482353, 0.990108, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.675212, -1.800763, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.171989, 1.777822, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 96, "source", 0, 3.482353, 0.990108, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.675212, -1.800763, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.171989, 1.777822, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 97, "source", 0, 2.689661, 2.423391, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.399675, -1.318927, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.93784, 1.520094, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 98, "source", 0, 2.689661, 2.423391, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.399675, -1.318927, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.93784, 1.520094, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 99, "source", 0, 2.288404, 2.805407, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.58453, -1.089919, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.158797, 1.359199, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 100, "source", 0, 1.762414, 3.162435, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.750746, -0.795957, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.378677, 1.135553, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 101, "source", 0, 0.919714, 3.501603, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.893772, -0.33509, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.617951, 0.756614, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 102, "source", 0, 0.607726, 3.569001, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.915926, -0.166988, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.678304, 0.611168, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 103, "source", 0, 0.283137, 3.609284, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.923178, 0.00661, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.726614, 0.457204, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 104, "source", 0, -0.638336, 3.563653, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.859061, 0.492496, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.786112, 0.005941, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 105, "source", 0, -0.75713, 3.540318, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.841555, 0.554378, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.785312, -0.053781, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 106, "source", 0, -1.221178, 3.408199, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.751483, 0.794335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.762306, -0.290705, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 107, "source", 0, -1.790627, 3.146547, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.588259, 1.084477, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.685771, -0.590259, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 108, "source", 0, -2.192779, 2.880767, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.430106, 1.285867, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.592412, -0.808984, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 109, "source", 0, -2.917252, 2.144001, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.008616, 1.637483, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.299025, -1.225873, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 110, "source", 0, -3.044934, 1.958437, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.904834, 1.697037, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.220278, -1.304283, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 111, "source", 0, -3.604316, 0.340596, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.024027, 1.92304, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.484651, -1.719112, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 112, "source", 0, -3.620333, -0.016987, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.165986, 1.916013, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.312523, -1.758568, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 113, "source", 0, -3.234082, -1.627211, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.001754, 1.64169, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.503192, -1.713776, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 114, "source", 0, -3.146459, -1.79078, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.084554, 1.588207, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.590341, -1.685743, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 115, "source", 0, -2.752065, -2.352283, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.364735, 1.355049, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.8978, -1.544081, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 116, "source", 0, -1.973966, -3.03489, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.692392, 0.913492, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.298032, -1.226925, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 117, "source", 0, -0.118223, -3.618442, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.920876, -0.094319, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.74567, -0.377977, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 118, "source", 0, 0.247707, -3.611889, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.901538, -0.287773, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.774912, -0.199799, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 119, "source", 0, 0.841988, -3.521101, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.827701, -0.598472, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.783504, 0.096668, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 120, "source", 0, 1.793204, -3.145078, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.58737, -1.085778, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.685287, 0.59164, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 121, "source", 0, 2.507957, -2.610986, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.273606, -1.441037, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.489404, 0.985853, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 122, "source", 0, 2.565414, -2.554554, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.241237, -1.46901, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.467106, 1.018739, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 123, "source", 0, 2.670628, -2.444349, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.178327, -1.519935, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.422942, 1.079567, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 124, "source", 0, 2.866236, -2.211739, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.046692, -1.613411, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.32738, 1.195112, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 125, "source", 0, 2.95572, -2.09065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.978702, -1.655536, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.276541, 1.24927, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 126, "source", 0, 2.95572, -2.09065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.978702, -1.655536, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.276541, 1.24927, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 127, "source", 0, 2.95572, -2.09065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.978702, -1.655536, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.276541, 1.24927, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 128, "source", 0, 2.95572, -2.09065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.978702, -1.655536, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.276541, 1.24927, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 129, "source", 0, 2.95572, -2.09065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.978702, -1.655536, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.276541, 1.24927, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 130, "source", 0, 3.029349, -2.115271, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.905073, -1.680157, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.35017, 1.224649, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 131, "source", 0, 3.029349, -2.115271, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.905073, -1.680157, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.35017, 1.224649, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 132, "source", 0, 3.029349, -2.115271, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.905073, -1.680157, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.35017, 1.224649, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 133, "source", 0, 3.056903, -2.134511, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.921011, -1.709744, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.375062, 1.247227, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 134, "source", 0, 3.363494, -2.34859, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.09835, -2.038953, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.652036, 1.498451, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 135, "source", 0, 3.525092, -2.461428, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.191823, -2.212473, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.798023, 1.630867, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 136, "source", 0, 3.643418, -2.54405, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.260265, -2.339528, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.904919, 1.727825, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 137, "source", 0, 3.784826, -2.64279, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.342059, -2.491369, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.032667, 1.843696, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 138, "source", 0, 3.969609, -2.771816, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.448942, -2.689783, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.199599, 1.995109, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 139, "source", 0, 4.33683, -3.028231, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.661352, -3.084096, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.531346, 2.296015, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 140, "source", 0, 4.933801, -3.445071, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.006654, -3.725108, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.070648, 2.78518, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 141, "source", 0, 5.214346, -3.640965, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.168928, -4.02635, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.324093, 3.015063, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 142, "source", 0, 5.694532, -3.976259, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.446679, -4.541961, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.757892, 3.408533, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 143, "source", 0, 5.803429, -4.052297, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.509668, -4.658892, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.856269, 3.497765, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 144, "source", 0, 5.893254, -4.115018, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.561625, -4.755344, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.937417, 3.571368, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 145, "source", 0, 5.989546, -4.182255, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.617323, -4.858739, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.024407, 3.650271, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 146, "source", 0, 6.089481, -4.252036, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.675128, -4.966047, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.114688, 3.732159, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 147, "source", 0, 6.089481, -4.252036, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.675128, -4.966047, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.114688, 3.732159, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 148, "source", 0, 6.174289, -4.311254, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.724183, -5.057112, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.191304, 3.801652, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 149, "source", 0, 6.174289, -4.311254, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.724183, -5.057112, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.191304, 3.801652, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 150, "source", 0, 6.174289, -4.311254, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.724183, -5.057112, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.191304, 3.801652, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 151, "source", 0, 6.167552, -4.306549, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.720285, -5.049877, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 4.185217, 3.796131, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 152, "source", 0, 5.264714, -3.676135, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.198062, -4.080434, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.369595, 3.056335, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 153, "source", 0, 5.10941, -3.567692, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.108231, -3.913672, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.229294, 2.929077, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 154, "source", 0, 4.606579, -3.216586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.817381, -3.373745, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.775037, 2.517051, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 155, "source", 0, 4.606579, -3.216586, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.817381, -3.373745, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.775037, 2.517051, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 156, "source", 0, 4.258911, -2.973823, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.616281, -3.000428, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.460954, 2.232167, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 157, "source", 0, 3.566627, -2.49043, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.215847, -2.257072, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.835546, 1.664901, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 158, "source", 0, 3.27623, -2.287657, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.047874, -1.945251, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.573201, 1.426946, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 159, "source", 0, 3.129079, -2.184908, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.962759, -1.787244, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.440266, 1.306369, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 160, "source", 0, 2.871183, -2.00483, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.813586, -1.510322, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.207283, 1.095046, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 161, "source", 0, 2.751979, -1.921595, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.744635, -1.382324, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.099594, 0.997368, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 162, "source", 0, 2.751979, -1.921595, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.744635, -1.382324, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.099594, 0.997368, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 163, "source", 0, 2.587123, -1.806482, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.649278, -1.205306, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.950663, 0.862283, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 164, "source", 0, 2.37671, -1.659559, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.52757, -0.97937, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.760576, 0.689868, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 165, "source", 0, 2.053922, -1.43417, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.340862, -0.632768, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.46897, 0.425372, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 166, "source", 0, 1.934198, -1.350571, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.27161, -0.504211, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.360812, 0.327268, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 167, "source", 0, 1.934198, -1.350571, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.27161, -0.504211, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.360812, 0.327268, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 168, "source", 0, 1.730107, -1.208063, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.15356, -0.285065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.176437, 0.160034, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 169, "source", 0, 1.665118, -1.162684, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.115968, -0.215281, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.117726, 0.106781, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 170, "source", 0, 1.597653, -1.115576, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.076944, -0.142838, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.056777, 0.051499, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 171, "source", 0, 1.597653, -1.115576, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.076944, -0.142838, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.056777, 0.051499, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 172, "source", 0, 1.597653, -1.115576, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.076944, -0.142838, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.056777, 0.051499, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 173, "source", 0, 1.605321, -1.12093, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.08138, -0.151072, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.063704, 0.057782, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 174, "source", 0, 1.682056, -1.174511, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.125765, -0.233468, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.133027, 0.12066, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 175, "source", 0, 1.682056, -1.174511, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.125765, -0.233468, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.133027, 0.12066, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 176, "source", 0, 1.797561, -1.255163, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.192576, -0.357494, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.237374, 0.215306, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 177, "source", 0, 2.062743, -1.440329, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.345964, -0.64224, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.476939, 0.4326, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 178, "source", 0, 2.386538, -1.666422, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.533255, -0.989923, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.769455, 0.697922, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 179, "source", 0, 2.6863, -1.875734, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.706645, -1.3118, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.04026, 0.94355, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 180, "source", 0, 2.877647, -2.009343, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.817324, -1.517263, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.213122, 1.100342, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 181, "source", 0, 3.004596, -2.097986, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.890755, -1.653577, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.327808, 1.204366, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 182, "source", 0, 3.251556, -2.270429, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.033603, -1.918757, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.550911, 1.406728, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 183, "source", 0, 3.441135, -2.402804, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.14326, -2.122322, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.722176, 1.562071, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 184, "source", 0, 3.619532, -2.527371, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.246449, -2.313879, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.88334, 1.708252, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 185, "source", 0, 3.690677, -2.577049, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.287601, -2.390273, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.947612, 1.766549, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 186, "source", 0, 3.784069, -2.642261, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.341621, -2.490556, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.031983, 1.843076, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 187, "source", 0, 3.872815, -2.683704, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.378188, -2.580469, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.096647, 1.915422, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 188, "source", 0, 4.077438, -2.683582, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.392392, -2.764055, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.172658, 2.082269, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 189, "source", 0, 4.426668, -2.547098, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.313621, -3.049953, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.197398, 2.374473, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 190, "source", 0, 4.876528, -2.369933, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.201892, -3.431149, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.223707, 2.767208, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 191, "source", 0, 5.066073, -2.06179, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.986211, -3.548724, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.064089, 2.946595, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 192, "source", 0, 5.2714, -1.860358, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.844278, -3.708816, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.987033, 3.142614, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 193, "source", 0, 5.42415, -1.268663, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.43166, -3.759494, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.623116, 3.323426, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 194, "source", 0, 5.43861, -0.96602, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.2254, -3.730588, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.423227, 3.363046, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 195, "source", 0, 5.421474, 0.366835, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.66379, -3.586617, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.556901, 3.51813, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 196, "source", 0, 5.200766, 1.082037, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.111004, -3.34617, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.066822, 3.439549, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 197, "source", 0, 4.490261, 2.425573, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.902254, -2.717541, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.864219, 3.113875, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 198, "source", 0, 4.028587, 2.839482, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.094154, -2.342853, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.160481, 2.827921, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 199, "source", 0, 2.053748, 3.769209, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.32407, -0.937591, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.814208, 1.602299, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 200, "source", 0, 1.279812, 3.935814, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.305922, -0.464897, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.945429, 1.163343, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 201, "source", 0, 1.058514, 3.909572, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.238914, -0.336013, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.923134, 1.023215, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 202, "source", 0, 0.104819, 3.809342, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.016616, 0.177787, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.87758, 0.483551, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 203, "source", 0, -0.113774, 3.542175, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.738557, 0.258406, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.641199, 0.319796, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 204, "source", 0, -0.866192, 2.812096, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.058347, 0.465341, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.067592, -0.079414, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 205, "source", 0, -1.276605, 2.367379, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.740393, 0.517468, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.788087, -0.218108, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 206, "source", 0, -1.281764, 2.118423, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.545012, 0.422613, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.573491, -0.189779, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 207, "source", 0, -1.290784, 1.739309, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.276741, 0.259826, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.269183, -0.118242, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 208, "source", 0, -1.284813, 1.179212, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 209, "source", 0, -1.404765, -0.096217, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 210, "source", 0, -1.227258, -0.353047, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.0, 0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 211, "source", 0, -0.86732, -0.92859, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.012117, 0.008944, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.008441, -0.012473, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 212, "source", 0, -0.503984, -1.177121, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.023862, 0.007097, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.020129, -0.014648, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 213, "source", 0, -0.135619, -1.287638, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.039179, -0.000412, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.037074, -0.012677, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 214, "source", 0, 1.169059, -1.328202, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.344035, -0.381661, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.451618, 0.245084, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 215, "source", 0, 1.710082, -1.361447, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.491725, -0.789684, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.726923, 0.580498, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 216, "source", 0, 2.316878, -1.018873, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.375531, -1.218896, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.760516, 1.023889, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 217, "source", 0, 2.879907, -0.733094, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.228969, -1.700827, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.783059, 1.527108, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 218, "source", 0, 3.011516, 1.338505, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.037762, -1.756315, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.392655, 2.001852, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 219, "source", 0, 3.07178, 1.566872, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.214717, -1.825536, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.536397, 2.126123, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 220, "source", 0, 3.079378, 1.67178, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.293182, -1.839211, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.60581, 2.165181, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 221, "source", 0, 2.630248, 2.31959, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.673704, -1.505785, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.075741, 1.97774, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 222, "source", 0, 1.852024, 3.14876, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.192756, -0.969343, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.743975, 1.645101, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 223, "source", 0, 1.569228, 3.385967, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.351769, -0.775541, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.958515, 1.515421, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 224, "source", 0, 0.922908, 3.74324, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.579052, -0.327448, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.322218, 1.168774, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 225, "source", 0, 0.346083, 4.045015, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.802945, 0.084375, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.670631, 0.855189, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 226, "source", 0, -1.307112, 4.160255, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.835478, 1.265796, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.095286, -0.247753, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 227, "source", 0, -2.104076, 4.298512, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.970904, 1.906969, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.436779, -0.807061, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 228, "source", 0, -3.237434, 3.838129, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.579559, 2.743284, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.346733, -1.726008, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 229, "source", 0, -3.707773, 3.74786, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.510893, 3.13482, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.412569, -2.11803, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 230, "source", 0, -4.130379, 2.852995, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.768398, 3.323107, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.775368, -2.543149, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 231, "source", 0, -4.214013, 2.334719, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.355849, 3.293833, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.376672, -2.653128, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 232, "source", 0, -4.407705, 0.314574, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.139758, 3.160249, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.922132, -3.025951, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 233, "source", 0, -4.126168, -0.622398, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.764499, 2.815313, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.218123, -2.909101, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 234, "source", 0, -3.96786, -1.019853, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.019557, 2.65202, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.07679, -2.840213, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 235, "source", 0, -3.830846, -1.243035, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.153518, 2.520472, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.246952, -2.760869, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 236, "source", 0, -3.414708, -1.757267, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.439598, 2.146754, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.641284, -2.503947, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 237, "source", 0, -2.366456, -2.354801, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.629454, 1.297383, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.103523, -1.766511, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 238, "source", 0, -0.800025, -2.496629, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.340298, 0.264249, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.175451, -0.696089, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 239, "source", 0, 0.005136, -2.492386, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.228284, -0.144996, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.206326, -0.272916, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 240, "source", 0, 0.760192, -2.22533, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.989451, -0.471414, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.09002, 0.114464, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 241, "source", 0, 1.655273, -1.603924, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.63853, -0.832661, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.879656, 0.572058, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 242, "source", 0, 1.940816, -1.242204, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.459841, -0.942539, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.747838, 0.735236, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 243, "source", 0, 2.436613, -0.350646, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.033144, -1.20568, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.43332, 1.125609, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 244, "source", 0, 2.638222, 0.264111, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.307307, -1.405757, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.124319, 1.433574, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 245, "source", 0, 2.673523, 0.465942, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.426427, -1.439536, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.020618, 1.501226, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 246, "source", 0, 2.493269, 1.499385, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.036221, -1.343814, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.590074, 1.591038, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 247, "source", 0, 2.59573, 1.966531, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.413823, -1.476277, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.911255, 1.829727, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 248, "source", 0, 2.542796, 2.106953, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.509853, -1.444893, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.012273, 1.828299, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 249, "source", 0, 2.542796, 2.106953, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.509853, -1.444893, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.012273, 1.828299, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 250, "source", 0, 2.465336, 2.337154, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.675616, -1.401752, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.183367, 1.836366, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 251, "source", 0, 2.409233, 2.488336, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.786869, -1.369144, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.299285, 1.838291, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 252, "source", 0, 2.409233, 2.488336, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.786869, -1.369144, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.299285, 1.838291, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 253, "source", 0, 2.409233, 2.488336, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.786869, -1.369144, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.299285, 1.838291, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 254, "source", 0, 2.409233, 2.488336, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.786869, -1.369144, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.299285, 1.838291, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 255, "source", 0, 2.435584, 2.556787, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.81322, -1.300693, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.272933, 1.906743, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 256, "source", 0, 2.394037, 2.639883, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.771672, -1.217597, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.314481, 1.989839, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 257, "source", 0, 2.310941, 2.764527, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.688576, -1.092953, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.397577, 2.114482, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 258, "source", 0, 1.853913, 2.930719, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.231549, -0.926762, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.854605, 2.280674, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 259, "source", 0, 1.438434, 2.930719, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.81607, -0.926762, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.270084, 2.280674, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 260, "source", 0, 1.022954, 2.930719, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.40059, -0.926762, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.685563, 2.280674, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 261, "source", 0, 0.233544, 2.598335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.388821, -1.259145, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.474974, 1.948291, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 262, "source", 0, 0.233544, 2.598335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.388821, -1.259145, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.474974, 1.948291, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 263, "source", 0, -0.389676, 2.058212, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.01204, -1.799268, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.098193, 1.408167, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 264, "source", 0, -0.431224, 1.975116, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.053588, -1.882364, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.139741, 1.325072, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 265, "source", 0, -0.638963, 1.393445, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.261327, -2.464036, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.347481, 0.7434, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 266, "source", 0, -0.680511, 1.185705, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.302875, -2.671775, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.389029, 0.535661, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 267, "source", 0, -0.680511, 0.936418, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.302875, -2.921063, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.389029, 0.286373, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 268, "source", 0, -0.680511, 0.604034, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.302875, -3.253446, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.389029, -0.046011, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 269, "source", 0, -0.680511, 0.520938, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.302875, -3.336542, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.389029, -0.129106, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 270, "source", 0, -0.555867, 0.105459, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.178231, -3.752022, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.264385, -0.544586, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 271, "source", 0, -0.555867, 0.063911, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.178231, -3.79357, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.264385, -0.586134, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 272, "source", 0, -0.555867, 0.022363, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.178231, -3.835118, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.264385, -0.627682, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 273, "source", 0, -0.514319, -0.185377, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.136684, -4.042857, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.222837, -0.835421, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 274, "source", 0, -0.514319, -0.185377, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.136684, -4.042857, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.222837, -0.835421, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 275, "source", 0, -0.472771, -0.310021, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.095136, -4.167501, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.181289, -0.960065, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 276, "source", 0, -0.30658, -0.434664, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.928944, -4.292145, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -4.015098, -1.084709, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 277, "source", 0, -0.265032, -0.434664, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.887396, -4.292145, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.97355, -1.084709, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 278, "source", 0, -0.223484, -0.559308, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.845848, -4.416789, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.932002, -1.209353, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 279, "source", 0, -0.223484, -0.559308, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.845848, -4.416789, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.932002, -1.209353, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 280, "source", 0, -0.166879, -0.537318, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.740986, -4.401975, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.849685, -1.25332, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 281, "source", 0, -0.151529, -0.512596, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.676301, -4.383933, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.805537, -1.296894, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 282, "source", 0, -0.110358, -0.441644, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.48042, -4.329921, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.673007, -1.428884, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 283, "source", 0, -0.07952, -0.408324, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.250156, -4.310009, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.55716, -1.603629, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 284, "source", 0, -0.041379, -0.317817, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.020674, -4.221717, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -3.364954, -1.779322, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 285, "source", 0, 0.009045, -0.090275, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.926521, -3.882986, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.698974, -2.346915, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 286, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.344828, -3.560003, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.256019, -2.53059, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 287, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.579066, -3.339791, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.978181, -2.614998, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 288, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.963301, -2.598576, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.216115, -2.568135, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 289, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.086167, -2.342529, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.963058, -2.545366, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 290, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.700613, -0.728635, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.515093, -2.325479, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 291, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.66914, -0.606784, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.592371, -2.245068, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 292, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.63933, -0.540704, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.628537, -2.190412, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 293, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.572609, -0.406415, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.698662, -2.074694, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 294, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.09023, -0.063063, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.730967, -1.508023, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 295, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.843287, 0.108129, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.735915, -1.227406, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 296, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.199349, 0.592713, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.745226, -0.54369, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 297, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.09759, 0.636349, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.721268, -0.456102, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 298, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.730427, 0.939541, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.762307, -0.138179, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 299, "source", 0, 0.0, -0.0, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.504531, 1.028378, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.729901, 0.018545, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 300, "source", 0, 0.012445, 0.036377, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.229721, 1.161421, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.737312, 0.217005, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 301, "source", 0, -0.014248, 0.065424, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.414363, 1.139428, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.537763, 0.588362, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 302, "source", 0, -0.079343, 0.117122, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.85802, 0.959178, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.306635, 0.815885, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 303, "source", 0, -0.163598, 0.156406, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.109621, 0.806599, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.140145, 0.946148, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 304, "source", 0, -0.300259, 0.187065, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.367218, 0.615166, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.063594, 1.082032, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 305, "source", 0, -0.328948, 0.175294, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.423417, 0.528072, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.138879, 1.094097, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 306, "source", 0, -0.340409, 0.111219, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.478914, 0.271293, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.32169, 1.03962, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 307, "source", 0, -0.428995, -0.070461, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.510961, -0.462693, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.818131, 0.82922, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 308, "source", 0, -0.557707, -0.370796, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.36334, -1.198433, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.306049, 0.503824, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 309, "source", 0, -0.596336, -0.669113, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.142032, -1.692498, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.616218, 0.181903, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 310, "source", 0, -0.594337, -0.931569, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.945368, -2.042298, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.833039, -0.088024, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 311, "source", 0, -0.590312, -1.009483, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.890313, -2.13683, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.892408, -0.164544, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 312, "source", 0, -0.54712, -1.111644, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.756862, -2.261156, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.94444, -0.310817, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 313, "source", 0, -0.415517, -1.351165, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.417763, -2.524758, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.036583, -0.66932, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 314, "source", 0, -0.277729, -1.555652, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.115271, -2.723286, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.091105, -0.982426, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 315, "source", 0, -0.232365, -1.641625, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.017512, -2.803409, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.123455, -1.092739, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 316, "source", 0, -0.049281, -1.864041, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.324266, -2.992651, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -2.156953, -1.442459, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 317, "source", 0, 0.300382, -1.803884, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.035459, -2.77444, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.701818, -1.893693, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 318, "source", 0, 0.49641, -1.745244, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.332908, -2.628465, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.470991, -2.060598, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 319, "source", 0, 0.739594, -1.699301, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.692636, -2.459814, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.202022, -2.272228, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 320, "source", 0, 0.810027, -1.687175, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.793625, -2.409999, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.124853, -2.331712, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 321, "source", 0, 0.999664, -1.442219, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.067917, -2.015205, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.709225, -2.368186, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 322, "source", 0, 1.142417, -1.057992, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.2862, -1.416985, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.166657, -2.26826, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 323, "source", 0, 1.153985, -0.510856, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.334524, -0.533232, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.503005, -1.914328, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 324, "source", 0, 1.098803, 0.071936, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.160109, 0.569024, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.224932, -1.344001, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 325, "source", 0, 1.086575, 0.286958, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 2.031444, 0.982295, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.477985, -1.097877, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 326, "source", 0, 1.036117, 0.59354, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.76083, 1.520896, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.777246, -0.703415, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 327, "source", 0, 1.031559, 0.730392, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.655393, 1.733023, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.903563, -0.549404, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 328, "source", 0, 0.941566, 0.839527, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.449711, 1.90531, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.950629, -0.332667, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 329, "source", 0, 0.738444, 1.061208, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.979573, 2.218886, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.005809, 0.132114, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 330, "source", 0, 0.394457, 1.330682, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.241558, 2.508958, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.950699, 0.791663, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 331, "source", 0, 0.288498, 1.387972, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.032488, 2.550075, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.904636, 0.964544, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 332, "source", 0, -0.028402, 1.462133, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.545077, 2.537162, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.676745, 1.392724, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 333, "source", 0, -0.883804, 1.527656, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.90336, 2.184704, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.903618, 2.311877, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 334, "source", 0, -1.133058, 1.488988, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.242053, 1.998876, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.631872, 2.510066, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 335, "source", 0, -1.328435, 1.47663, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.490462, 1.877519, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.442659, 2.667067, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 336, "source", 0, -1.599123, 0.95943, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.817618, 1.022771, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.343204, 2.559255, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 337, "source", 0, -1.600169, 0.842795, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.816204, 0.848292, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.474388, 2.480904, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 338, "source", 0, -1.571843, 0.767956, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.783506, 0.747225, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.536493, 2.40767, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 339, "source", 0, -1.543135, 0.693942, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.749989, 0.645062, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.59865, 2.333733, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 340, "source", 0, -1.5149, 0.681245, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.719849, 0.637992, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.590957, 2.303746, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 341, "source", 0, -1.5149, 0.681245, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.719849, 0.637992, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.590957, 2.303746, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 342, "source", 0, -1.531895, 0.486316, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.736843, 0.443062, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.607952, 2.108816, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 343, "source", 0, -1.573443, 0.278576, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.778391, 0.235322, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.6495, 1.901076, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 344, "source", 0, -1.573443, 0.029288, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.778391, -0.013966, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.6495, 1.651788, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 345, "source", 0, -1.573443, -0.261547, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.778391, -0.304801, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.6495, 1.360953, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 346, "source", 0, -1.448799, -0.884767, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.653747, -0.92802, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.524856, 0.737734, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 347, "source", 0, -1.241059, -1.42489, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.446007, -1.468143, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.317116, 0.197611, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 348, "source", 0, -0.991772, -1.674177, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.19672, -1.717431, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.067828, -0.051677, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 349, "source", 0, -0.991772, -1.674177, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.19672, -1.717431, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.067828, -0.051677, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 350, "source", 0, -0.285457, -2.131205, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.490405, -2.174459, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.638487, -0.508704, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 351, "source", 0, -0.285457, -2.131205, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.490405, -2.174459, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.638487, -0.508704, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 352, "source", 0, 0.628598, -1.798821, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.57635, -1.842075, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.552541, -0.176321, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 353, "source", 0, 0.753242, -1.591082, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.451706, -1.634335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.677185, 0.031419, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 354, "source", 0, 1.085625, -1.300246, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.119323, -1.3435, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.009569, 0.322254, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 355, "source", 0, 1.168721, -1.134054, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.036227, -1.177308, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.092664, 0.488446, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 356, "source", 0, 1.168721, -0.926314, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.036227, -0.969568, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.092664, 0.696186, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 357, "source", 0, 1.168721, -0.718575, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.036227, -0.761828, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.092664, 0.903926, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 358, "source", 0, 1.127173, -0.386191, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.077775, -0.429445, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.051117, 1.236309, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 359, "source", 0, 1.085625, -0.344643, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.119323, -0.387897, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.009569, 1.277857, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 360, "source", 0, 1.044078, -0.303095, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, -0.346349, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.319405, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 361, "source", 0, 1.044078, -0.303095, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, -0.346349, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.319405, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 362, "source", 0, 1.044078, -0.303095, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, -0.346349, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.319405, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 363, "source", 0, 1.044078, -0.303095, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, -0.346349, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.319405, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 364, "source", 0, 1.044078, -0.303095, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, -0.346349, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.319405, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 365, "source", 0, 1.044078, -0.219999, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, -0.263253, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.402501, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 366, "source", 0, 1.044078, -0.219999, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, -0.263253, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.402501, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 367, "source", 0, 1.044078, 0.070836, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, 0.027582, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.693336, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 368, "source", 0, 1.044078, 0.153932, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, 0.110678, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.776432, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 369, "source", 0, 1.044078, 0.361672, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, 0.318418, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 1.984172, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 370, "source", 0, 0.836338, 1.026439, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.36861, 0.983185, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.760281, 2.648939, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 371, "source", 0, 0.836338, 1.109535, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.36861, 1.066281, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.760281, 2.732035, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 372, "source", 0, 0.79479, 2.065137, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.410158, 2.021883, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.718733, 3.687638, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 373, "source", 0, 0.960982, 2.314425, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.243967, 2.271171, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.884925, 3.936925, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 374, "source", 0, 1.376461, 2.397521, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.171513, 2.354267, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.300404, 4.020021, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 375, "source", 0, 1.501105, 2.397521, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.296157, 2.354267, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.425048, 4.020021, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 376, "source", 0, 2.20742, 1.317274, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.002472, 1.274021, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.131363, 2.939775, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 377, "source", 0, 2.290516, 0.777151, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.085567, 0.733897, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.214459, 2.399652, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 378, "source", 0, 2.165872, -0.386191, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.960924, -0.429445, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 3.089815, 1.236309, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 379, "source", 0, 1.625749, -1.549534, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.4208, -1.592787, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.549692, 0.072967, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 380, "source", 0, 0.37931, -2.172753, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.825638, -2.216007, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.303254, -0.550252, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 381, "source", 0, 0.046927, -2.172753, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.158021, -2.216007, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.97087, -0.550252, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 382, "source", 0, -1.490347, -1.507986, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.695295, -1.551239, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.566404, 0.114515, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 383, "source", 0, -1.739635, -0.926314, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.944583, -0.969568, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.815691, 0.696186, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 384, "source", 0, -1.656539, 0.029288, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -2.861487, -0.013966, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.732595, 1.651788, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 385, "source", 0, -0.4101, 0.984891, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.615049, 0.941637, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.513843, 2.607391, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 386, "source", 0, 1.044078, 1.109535, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.160871, 1.066281, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.968021, 2.732035, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 387, "source", 0, 1.210269, 0.943343, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.005321, 0.900089, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.134212, 2.565843, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 388, "source", 0, 1.708845, 0.486316, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.503896, 0.443062, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.632788, 2.108816, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 389, "source", 0, 1.79194, 0.444768, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.586992, 0.401514, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.715884, 2.067268, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 390, "source", 0, 1.79194, -0.178452, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.586992, -0.221705, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.715884, 1.444049, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 391, "source", 0, 1.79194, -0.635479, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.586992, -0.678733, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.715884, 0.987021, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 392, "source", 0, 1.542653, -1.632629, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.337705, -1.675883, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.466596, -0.010129, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 393, "source", 0, 1.293365, -2.380492, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.088417, -2.423746, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 2.217308, -0.757992, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 394, "source", 0, 0.919434, -2.962163, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.285515, -3.005417, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.843377, -1.339663, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 395, "source", 0, 0.919434, -2.962163, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.285515, -3.005417, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.843377, -1.339663, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 396, "source", 0, 0.58705, -3.128355, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.617898, -3.171609, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.510993, -1.505855, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 397, "source", 0, 0.420858, -3.169903, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.78409, -3.213157, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.344802, -1.547403, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 398, "source", 0, 0.337763, -3.086807, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.867186, -3.130061, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.261706, -1.464307, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 399, "source", 0, 0.337763, -3.045259, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.867186, -3.088513, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.261706, -1.422759, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 400, "source", 0, 0.254667, -2.962163, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.950282, -3.005417, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.17861, -1.339663, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 401, "source", 0, 0.171571, -2.795972, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.033378, -2.839226, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.095514, -1.173471, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 402, "source", 0, 0.171571, -2.795972, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.033378, -2.839226, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.095514, -1.173471, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 403, "source", 0, 0.171571, -2.754424, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.033378, -2.797678, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.095514, -1.131924, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 404, "source", 0, 0.171571, -2.754424, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.033378, -2.797678, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.095514, -1.131924, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 405, "source", 0, 0.171571, -2.754424, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.033378, -2.797678, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.095514, -1.131924, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 3, 0, 1, 2, 0, 0.2, 0.2, 0.2, 1.0, "" ],
					"zoom" : 0.193906
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 356.857117, 136.5, 221.187683, 20.0 ],
					"saved_object_attributes" : 					{
						"mode" : "cartesian",
						"ramp" : 100.0
					}
,
					"text" : "hoa.map~ 7 3"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-10", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-10", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-10", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-10", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-10", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-10", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-10", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-10", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-10", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-10", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-10", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-10", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-10", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-10", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-34", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-34", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-102", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 605.5, 294.0, 568.5448, 294.0 ],
					"source" : [ "obj-104", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 125.5, 102.0, 49.5, 102.0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 262.5, 39.0, 184.5, 39.0 ],
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 43.5, 387.0, 342.0, 387.0, 342.0, 128.0, 366.357117, 128.0 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-81", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1291.5, 367.0, 1365.5, 367.0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-81", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1380.099976, 371.0, 1365.5, 371.0 ],
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
					"destination" : [ "obj-86", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-18", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-18", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-18", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-18", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-18", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-18", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-18", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-18", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-18", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-18", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-18", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-18", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-18", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-18", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1146.0, 396.0, 588.0, 396.0, 588.0, 552.0, 568.75, 552.0 ],
					"source" : [ "obj-28", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1131.535767, 396.0, 588.0, 396.0, 588.0, 552.0, 554.285706, 552.0 ],
					"source" : [ "obj-28", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1117.071411, 396.0, 588.0, 396.0, 588.0, 552.0, 539.821411, 552.0 ],
					"source" : [ "obj-28", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1102.607178, 396.0, 588.0, 396.0, 588.0, 552.0, 525.357117, 552.0 ],
					"source" : [ "obj-28", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1088.142822, 396.0, 588.0, 396.0, 588.0, 552.0, 510.892853, 552.0 ],
					"source" : [ "obj-28", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1073.678589, 396.0, 588.0, 396.0, 588.0, 552.0, 496.428558, 552.0 ],
					"source" : [ "obj-28", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1059.214233, 396.0, 588.0, 396.0, 588.0, 552.0, 481.964294, 552.0 ],
					"source" : [ "obj-28", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1044.75, 396.0, 588.0, 396.0, 588.0, 552.0, 467.5, 552.0 ],
					"source" : [ "obj-28", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1030.285767, 396.0, 588.0, 396.0, 588.0, 552.0, 453.035706, 552.0 ],
					"source" : [ "obj-28", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1015.821411, 396.0, 588.0, 396.0, 588.0, 552.0, 438.571442, 552.0 ],
					"source" : [ "obj-28", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1001.357117, 396.0, 588.0, 396.0, 588.0, 552.0, 424.107147, 552.0 ],
					"source" : [ "obj-28", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 986.892883, 396.0, 588.0, 396.0, 588.0, 552.0, 409.642853, 552.0 ],
					"source" : [ "obj-28", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 972.428589, 396.0, 588.0, 396.0, 588.0, 552.0, 395.178558, 552.0 ],
					"source" : [ "obj-28", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 957.964294, 396.0, 588.0, 396.0, 588.0, 552.0, 380.714294, 552.0 ],
					"source" : [ "obj-28", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 943.5, 396.0, 588.0, 396.0, 588.0, 552.0, 366.25, 552.0 ],
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 2 ]
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
					"destination" : [ "obj-32", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 668.125, 228.0, 588.0, 228.0, 588.0, 294.0, 568.5448, 294.0 ],
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 680.5, 726.0, 568.75, 726.0 ],
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 727.5, 101.5, 668.125, 101.5 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 49.5, 81.0, 49.5, 81.0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 782.0, 726.0, 568.75, 726.0 ],
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-49", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 10 ]
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
					"destination" : [ "obj-45", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-43", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 717.625, 305.0, 649.125, 305.0 ],
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 838.125, 366.0, 568.5448, 366.0 ],
					"source" : [ "obj-45", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 824.625, 366.0, 554.095154, 366.0 ],
					"source" : [ "obj-45", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 811.125, 366.0, 539.645569, 366.0 ],
					"source" : [ "obj-45", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 797.625, 366.0, 525.195923, 366.0 ],
					"source" : [ "obj-45", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 784.125, 366.0, 510.746277, 366.0 ],
					"source" : [ "obj-45", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 770.625, 366.0, 496.296661, 366.0 ],
					"source" : [ "obj-45", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 757.125, 366.0, 481.847015, 366.0 ],
					"source" : [ "obj-45", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 743.625, 366.0, 467.3974, 366.0 ],
					"source" : [ "obj-45", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 730.125, 366.0, 452.947784, 366.0 ],
					"source" : [ "obj-45", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 716.625, 366.0, 438.498138, 366.0 ],
					"source" : [ "obj-45", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 703.125, 366.0, 424.048523, 366.0 ],
					"source" : [ "obj-45", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 689.625, 366.0, 409.598877, 366.0 ],
					"source" : [ "obj-45", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 676.125, 366.0, 395.149261, 366.0 ],
					"source" : [ "obj-45", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-47", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 662.625, 366.0, 380.699615, 366.0 ],
					"source" : [ "obj-45", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-47", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 649.125, 366.0, 366.25, 366.0 ],
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 839.5, 63.0, 839.5, 63.0 ],
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-52", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-52", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-52", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-52", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-52", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-52", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-52", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-52", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-52", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-52", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-52", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-52", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-52", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-52", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-52", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-28", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 10 ]
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
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 184.5, 102.0, 49.5, 102.0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-49", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1201.0, 681.0, 1167.0, 681.0, 1167.0, 309.0, 1146.0, 309.0 ],
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"destination" : [ "obj-53", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 568.5448, 534.0, 568.75, 534.0 ],
					"source" : [ "obj-53", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 554.080505, 534.0, 554.285706, 534.0 ],
					"source" : [ "obj-53", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 539.616211, 534.0, 539.821411, 534.0 ],
					"source" : [ "obj-53", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 525.151917, 534.0, 525.357117, 534.0 ],
					"source" : [ "obj-53", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 510.687653, 534.0, 510.892853, 534.0 ],
					"source" : [ "obj-53", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 496.223358, 534.0, 496.428558, 534.0 ],
					"source" : [ "obj-53", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 481.759094, 534.0, 481.964294, 534.0 ],
					"source" : [ "obj-53", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 467.2948, 534.0, 467.5, 534.0 ],
					"source" : [ "obj-53", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 452.830505, 561.0, 453.035706, 561.0 ],
					"source" : [ "obj-53", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 438.366241, 534.0, 438.571442, 534.0 ],
					"source" : [ "obj-53", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 423.901947, 534.0, 424.107147, 534.0 ],
					"source" : [ "obj-53", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 409.437653, 534.0, 409.642853, 534.0 ],
					"source" : [ "obj-53", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 394.973358, 534.0, 395.178558, 534.0 ],
					"source" : [ "obj-53", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 380.509094, 534.0, 380.714294, 534.0 ],
					"source" : [ "obj-53", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 366.0448, 534.0, 366.25, 534.0 ],
					"source" : [ "obj-53", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 15 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 568.75, 651.0, 633.0, 651.0, 633.0, 396.0, 886.625, 396.0 ],
					"source" : [ "obj-54", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 555.25, 660.0, 603.0, 660.0, 603.0, 396.0, 871.325012, 396.0 ],
					"source" : [ "obj-54", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 541.75, 660.0, 603.0, 660.0, 603.0, 396.0, 856.025024, 396.0 ],
					"source" : [ "obj-54", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 528.25, 660.0, 603.0, 660.0, 603.0, 396.0, 840.724976, 396.0 ],
					"source" : [ "obj-54", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 514.75, 660.0, 603.0, 660.0, 603.0, 396.0, 825.424988, 396.0 ],
					"source" : [ "obj-54", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 501.25, 660.0, 603.0, 660.0, 603.0, 396.0, 810.125, 396.0 ],
					"source" : [ "obj-54", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 487.75, 660.0, 603.0, 660.0, 603.0, 396.0, 794.825012, 396.0 ],
					"source" : [ "obj-54", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 474.25, 660.0, 603.0, 660.0, 603.0, 396.0, 779.525024, 396.0 ],
					"source" : [ "obj-54", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 460.75, 660.0, 603.0, 660.0, 603.0, 396.0, 764.224976, 396.0 ],
					"source" : [ "obj-54", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 447.25, 660.0, 603.0, 660.0, 603.0, 396.0, 748.924988, 396.0 ],
					"source" : [ "obj-54", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 433.75, 660.0, 603.0, 660.0, 603.0, 396.0, 733.625, 396.0 ],
					"source" : [ "obj-54", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 420.25, 687.0, 603.0, 687.0, 603.0, 396.0, 718.325012, 396.0 ],
					"source" : [ "obj-54", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 406.75, 687.0, 603.0, 687.0, 603.0, 396.0, 703.025024, 396.0 ],
					"source" : [ "obj-54", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 393.25, 687.0, 603.0, 687.0, 603.0, 396.0, 687.724976, 396.0 ],
					"source" : [ "obj-54", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 379.75, 687.0, 603.0, 687.0, 603.0, 396.0, 672.424988, 396.0 ],
					"source" : [ "obj-54", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 366.25, 687.0, 603.0, 687.0, 603.0, 405.0, 657.125, 405.0 ],
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"disabled" : 0,
					"hidden" : 1,
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
					"destination" : [ "obj-31", 0 ],
					"disabled" : 0,
					"hidden" : 1,
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
					"destination" : [ "obj-4", 0 ],
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
					"midpoints" : [ 1332.0, 248.5, 1295.0, 248.5, 1295.0, 155.5, 943.5, 155.5 ],
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
					"midpoints" : [ 1201.0, 248.5, 1166.0, 248.5, 1166.0, 155.5, 943.5, 155.5 ],
					"source" : [ "obj-68", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 731.625, 228.0, 588.0, 228.0, 588.0, 294.0, 568.5448, 294.0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 1319.5, 155.5, 943.5, 155.5 ],
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
					"midpoints" : [ 1201.0, 155.5, 943.5, 155.5 ],
					"source" : [ "obj-75", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-80", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-78", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-80", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-80", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 13 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 12 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"destination" : [ "obj-41", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-41", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-83", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
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
					"destination" : [ "obj-53", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 61.100006, 693.0, 342.0, 693.0, 342.0, 510.0, 366.0448, 510.0 ],
					"source" : [ "obj-86", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-89", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-88", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-89", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-9", 0 ]
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
					"destination" : [ "obj-34", 14 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 782.0, 228.0, 588.0, 228.0, 588.0, 294.0, 568.5448, 294.0 ],
					"source" : [ "obj-96", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 2 ],
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
				"bootpath" : "/Applications/Max 6.1/packages/HoaLibrary-1.2.1/docs",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/packages/HoaLibrary-1.2.1/docs",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.decorrelation~.maxpat",
				"bootpath" : "/Applications/Max 6.1/packages/HoaLibrary-1.2.1/patchers/effects",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/packages/HoaLibrary-1.2.1/patchers/effects",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.all.maxpat",
				"bootpath" : "/Applications/Max 6.1/packages/HoaLibrary-1.2.1/patchers/operators",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/packages/HoaLibrary-1.2.1/patchers/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.granular~.maxpat",
				"bootpath" : "/Applications/Max 6.1/packages/HoaLibrary-1.2.1/patchers/effects",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/packages/HoaLibrary-1.2.1/patchers/effects",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.soundcoat.maxpat",
				"bootpath" : "/Applications/Max 6.1/packages/HoaLibrary-1.2.1/misc/others",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/packages/HoaLibrary-1.2.1/misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "littlefilter~.maxpat",
				"bootpath" : "/Applications/Max 6.1/patches/docs/tutorial-patchers/msp-tut",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/patches/docs/tutorial-patchers/msp-tut",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.soundclack.maxpat",
				"bootpath" : "/Applications/Max 6.1/packages/HoaLibrary-1.2.1/misc/others",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/packages/HoaLibrary-1.2.1/misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "yafr2.maxpat",
				"bootpath" : "/Applications/Max 6.1/examples/effects/reverb/lib",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/examples/effects/reverb/lib",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.soundgrain.maxpat",
				"bootpath" : "/Applications/Max 6.1/packages/HoaLibrary-1.2.1/misc/others",
				"patcherrelativepath" : "../../../../../../Applications/Max 6.1/packages/HoaLibrary-1.2.1/misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "SpaceJim.json",
				"bootpath" : "/Users/Pierre/SourceTree/HoaLibrary/_projects/Presentation_Jim",
				"patcherrelativepath" : ".",
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
				"name" : "hoa.convolve~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.connect.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.plug~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.space.mxo",
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
				"name" : "hoa.scope~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.space~.mxo",
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
				"name" : "hoa.optim~.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
