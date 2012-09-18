{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 56.0, 44.0, 1415.0, 726.0 ],
		"bglocked" : 0,
		"defrect" : [ 56.0, 44.0, 1415.0, 726.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 992.0, 30.0, 50.0, 20.0 ],
					"minimum" : 0.0,
					"numoutlets" : 2,
					"maximum" : 1.0,
					"fontsize" : 11.595187,
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-6"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s dry",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 992.0, 75.0, 36.0, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-7"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "0.102411",
					"linecount" : 2,
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 240.0, 283.0, 50.0, 32.0 ],
					"numoutlets" : 1,
					"fontsize" : 12.0,
					"outlettype" : [ "" ],
					"id" : "obj-5"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 435.0, 270.0, 50.0, 20.0 ],
					"numoutlets" : 2,
					"fontsize" : 12.0,
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-76"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"patching_rect" : [ 465.0, 690.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"id" : "obj-72"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.name1~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 1110.0, 405.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-62"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.all no",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 1110.0, 450.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-63"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.*~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 1110.0, 480.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-64"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p ballMapping0",
					"fontname" : "Arial",
					"numinlets" : 0,
					"patching_rect" : [ 1170.0, 225.0, 183.0, 20.0 ],
					"numoutlets" : 3,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "signal" ],
					"id" : "obj-65",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 508.0, 150.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 508.0, 150.0, 640.0, 480.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 330.0, 55.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 105.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 105.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 345.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line~",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 375.0, 36.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "signal", "bang" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 225.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!/ 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 300.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "float" ],
									"id" : "obj-65"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 135.0, 225.0, 39.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-64"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r ball4",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 45.0, 105.0, 43.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-63"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 270.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-62"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 225.0, 73.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-61"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0. 0.",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 135.0, 76.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-60"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-59"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 165.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-53"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 105.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-68",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-69",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-68", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-69", 0 ],
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
, 							{
								"patchline" : 								{
									"source" : [ "obj-53", 0 ],
									"destination" : [ "obj-61", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-59", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-61", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 0 ],
									"destination" : [ "obj-53", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-62", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 1 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-62", 0 ],
									"destination" : [ "obj-65", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-63", 0 ],
									"destination" : [ "obj-60", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-64", 0 ],
									"destination" : [ "obj-62", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p dopplershift",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 1110.0, 300.0, 161.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-66",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"bglocked" : 0,
						"defrect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 285.0, 105.0, 37.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.0,
									"outlettype" : [ "" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "onepole~",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 226.0, 58.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 112.0, 201.0, 33.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapout~ 0.",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 263.0, 65.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapin~ 2000",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 226.0, 73.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "tapconnect" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "zl nth 3",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 121.0, 48.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 112.0, 92.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-8",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 152.0, 32.5, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 0.3438",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 176.0, 54.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 287.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-11",
									"comment" : "signal out"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 32.0, 58.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-12",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "doppler shift",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 23.0, 22.0, 73.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 59.0, 59.0, 52.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "aed coordinate input",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 139.0, 92.0, 114.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "speed of sound in dry air at 20 °C: 343.8 m/s",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 175.0, 176.0, 242.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-16"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 251.0, 41.5, 251.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-9", 0 ],
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
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p absorption",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 1110.0, 270.0, 79.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-67",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"bglocked" : 0,
						"defrect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 119.0, 55.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t 1 1",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 215.0, 38.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 63.0, 68.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-4",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 193.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "bang" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "filtercoeff~ lowpass",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 238.0, 111.0, 19.0 ],
									"numoutlets" : 5,
									"fontsize" : 10.0,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal" ],
									"id" : "obj-6"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "biquad~",
									"fontname" : "Verdana",
									"numinlets" : 6,
									"patching_rect" : [ 40.0, 267.0, 134.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 17000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 140.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 18000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 161.0, 59.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 40.0, 292.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-10",
									"comment" : "filtered signal"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 40.0, 36.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-11",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "high-frequency absorption by air as function of distance",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 15.0, 6.0, 293.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-12"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 67.0, 39.0, 53.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 1 ],
									"destination" : [ "obj-6", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-6", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 4 ],
									"destination" : [ "obj-7", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 3 ],
									"destination" : [ "obj-7", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 2 ],
									"destination" : [ "obj-7", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 1 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-7", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"numinlets" : 0,
					"embed" : 1,
					"patching_rect" : [ 1110.0, 120.0, 218.0, 87.0 ],
					"numoutlets" : 1,
					"border" : 1,
					"outlettype" : [ "signal" ],
					"id" : "obj-68",
					"name" : "poiu.maxpat",
					"args" : [  ],
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 1110.0, 120.0, 218.0, 87.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"defrect" : [ 1110.0, 120.0, 218.0, 87.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 1,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "meter~",
									"presentation_rect" : [ 199.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 90.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "float" ],
									"id" : "obj-39"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 128",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 315.0, 85.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-38"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "gain~",
									"presentation_rect" : [ 184.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 2,
									"bgcolor" : [ 0.85098, 0.85098, 0.85098, 1.0 ],
									"patching_rect" : [ 75.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"stripecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"outlettype" : [ "signal", "int" ],
									"knobcolor" : [ 0.482353, 0.482353, 0.482353, 1.0 ],
									"id" : "obj-27"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p attrArgs",
									"presentation_rect" : [ 645.0, 240.0, 379.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 510.0, 300.0, 73.0, 20.0 ],
									"numoutlets" : 5,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "", "", "", "" ],
									"id" : "obj-24",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 154.370789, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-37"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend noise",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 130.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 155.0, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend wave",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 130.0, 88.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 155.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend loop",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 130.0, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route module vol loop file wave freq noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 360.0, 20.0 ],
													"numoutlets" : 9,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "", "", "", "", "" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"presentation_rect" : [ 585.0, 120.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-5",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 585.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-6",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 627.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 92.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-8",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 665.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 130.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-12",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 765.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 230.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-16",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 870.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 335.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-23",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-37", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 2 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 3 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 4 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 5 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 6 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 7 ],
													"destination" : [ "obj-37", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 1 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"presentation_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-20"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "patcherargs @module 0 @vol -20 @loop 0 @file 2 @wave 0 @freq 440 @noise 0 @filter 0",
									"linecount" : 9,
									"presentation_linecount" : 9,
									"presentation_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "fourth",
									"presentation_rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 645.0, 385.000031, 110.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-3",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 25.0, 55.0, 98.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl slice 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 225.0, 215.0, 58.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "filtergraph~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"dbdisplay" : 0,
													"numinlets" : 8,
													"fgcolor" : [ 0.941176, 0.941176, 0.941176, 0.0 ],
													"domain" : [ 0.0, 22050.0 ],
													"bgcolor" : [ 0.941176, 0.941176, 0.941176, 0.4 ],
													"patching_rect" : [ 225.0, 245.0, 140.0, 45.0 ],
													"numoutlets" : 7,
													"presentation" : 1,
													"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
													"id" : "obj-4",
													"range" : [ 0.0, 16.0 ],
													"nfilters" : 1,
													"setfilter" : [ 0, 9, 1, 0, 0, 23.787561, 1.49664, 0.707107, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 80.0, 350.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"logfreq" : 1,
													"id" : "obj-14",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 160.0, 78.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 4.0, 1.666667, 96.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 125.0, 105.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Noise:", "white", ",", "Noise:", "pink" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-10",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 2 1 1.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 270.0, 86.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pink~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 145.0, 210.0, 40.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "biquad~",
													"fontname" : "Arial",
													"numinlets" : 6,
													"patching_rect" : [ 30.0, 315.0, 86.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 102.0, 2.0, 72.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 225.0, 185.0, 120.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Filter:", "allpass", ",", "Filter:", "lowpass", ",", "Filter:", "highpass", ",", "Filter:", "bandpass", ",", "Filter:", "bandstop", ",", "Filter:", "peaknotch", ",", "Filter:", "lowshelf", ",", "Filter:", "highshelf", ",", "Filter:", "resonant", ",", "Filter:", "display" ],
													"fontsize" : 11.595187,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-47",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 60.0, 210.0, 47.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 360.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 25.0, 15.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 1 ],
													"destination" : [ "obj-47", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-47", 1 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 1 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-9", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"presentation_rect" : [ 4.0, 2.0, 179.0, 20.0 ],
									"rounded" : 0,
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 128.736938, 179.0, 20.0 ],
									"numoutlets" : 3,
									"presentation" : 1,
									"items" : [ "Source:", "Sound", "File", ",", "Source:", "Oscillator", ",", "Source:", "ADC", "(input)", ",", "Source:", "Noise" ],
									"fontsize" : 12.0,
									"outlettype" : [ "int", "", "" ],
									"id" : "obj-6",
									"types" : [  ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : ";\rmax refresh",
									"linecount" : 2,
									"presentation_linecount" : 2,
									"presentation_rect" : [ 70.0, 230.0, 74.0, 32.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 60.0, 80.500031, 32.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p manageDisplay",
									"presentation_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 50.0, 94.0, 652.0, 443.0 ],
										"bglocked" : 0,
										"defrect" : [ 50.0, 94.0, 652.0, 443.0 ],
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
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1][1][1][1]",
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 3",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox fourth hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 151.0, 96.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox first hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 151.0, 89.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox second hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 151.0, 105.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 2",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox third hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 151.0, 90.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 257.0, 30.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 257.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-32", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1][1][1][1]",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "clear, $1 0 1",
									"presentation_rect" : [ 192.454483, 163.77652, 78.0, 18.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 75.0, 240.0, 78.0, 18.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "thispatcher",
									"presentation_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "", "" ],
									"id" : "obj-30",
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"presentation_rect" : [ 80.0, 460.629211, 25.0, 25.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 450.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-17",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "matrix~ 4 1 1. @ramp 200",
									"presentation_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 4,
									"patching_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "signal", "list" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "third",
									"presentation_rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 520.0, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-26",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"hidden" : 1,
													"patching_rect" : [ 40.0, 61.0, 74.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Input Channel:",
													"presentation_rect" : [ 5.0, 3.0, 89.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 89.0, 95.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 388.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-9",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 8.0, 25.0, 163.0, 35.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 59.0, 219.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-4",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "adc~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 153.0, 35.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "signal" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 3.0, 7.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "set $1 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 128.0, 54.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "number",
													"presentation_rect" : [ 95.0, 3.0, 48.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 98.0, 48.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "int", "bang" ],
													"id" : "obj-2"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "second",
									"presentation_rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 394.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-21",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "tab",
													"presentation_rect" : [ 50.0, 5.0, 116.0, 16.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 35.0, 280.0, 116.0, 16.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"tabs" : [ "sin", "tri", "rect", "noise" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route wave freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 54.833344, 110.0, 96.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-17"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 440",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 195.0, 110.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 1000",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 484.947357, 48.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 453.947357, 37.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "bang", "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 500",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 275.241211, 397.947357, 87.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "ms",
													"presentation_rect" : [ 152.907867, 43.0, 27.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 568.241211, 120.947357, 27.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Hz",
													"presentation_rect" : [ 92.0, 22.0, 26.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 215.241211, 66.947357, 26.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-30"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 109.0, 43.0, 45.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 274.333344, 425.947357, 45.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-26",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Speed:",
													"presentation_rect" : [ 62.907867, 43.0, 50.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 125.947357, 50.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-25"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 46.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 227.241211, 412.947357, 17.0, 17.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-24"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Pulse:",
													"presentation_rect" : [ 2.0, 43.0, 45.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 82.947357, 45.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-22"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 51.241211, 250.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-21"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 268.241211, 89.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-19"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 46.0, 22.0, 47.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 67.947357, 47.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Freq:",
													"presentation_rect" : [ 2.0, 22.0, 39.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 25.947357, 39.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Wave:",
													"presentation_rect" : [ 2.0, 1.0, 46.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 91.241211, 25.947357, 46.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 5 0.2 10 0 100",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 226.241211, 484.947357, 100.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "metro 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 227.241211, 453.947357, 66.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "bang" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line~ 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.333344, 519.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 571.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.333344, 319.0, 103.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 216.333313, 330.0, 46.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "rect~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 195.0, 290.0, 61.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "tri~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 173.666687, 260.0, 51.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "cycle~ 440",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 224.0, 68.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 4 1 1.",
													"fontname" : "Arial",
													"numinlets" : 4,
													"patching_rect" : [ 152.333344, 378.0, 83.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 152.333344, 615.947388, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 64.241211, 13.947357, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-7", 2 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-7", 3 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 1 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-19", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 1,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-7", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "first",
									"presentation_rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
									"numinlets" : 1,
									"embed" : 1,
									"patching_rect" : [ 269.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-22",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 10.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 20.0, 62.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 157.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 205.0, 50.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p folderOrSoundFile",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 181.0, 100.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-27",
													"patcher" : 													{
														"fileversion" : 1,
														"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
														"boxes" : [ 															{
																"box" : 																{
																	"maxclass" : "comment",
																	"text" : "fill the menu if it's a folder",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 108.0, 323.0, 150.0, 20.0 ],
																	"numoutlets" : 0,
																	"fontsize" : 12.0,
																	"id" : "obj-2"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "t s 1",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 100.0, 32.5, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "int" ],
																	"id" : "obj-20"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 211.0, 166.0, 32.5, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 10.0,
																	"outlettype" : [ "int" ],
																	"id" : "obj-19"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "gate 2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 205.0, 38.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "" ],
																	"id" : "obj-18"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "message",
																	"text" : "prefix $1, insert 0 Browse..., insert 1 <separator>",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 69.0, 238.0, 270.0, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 12.0,
																	"outlettype" : [ "" ],
																	"id" : "obj-7"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "sel fold",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 140.0, 42.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "bang", "" ],
																	"id" : "obj-4"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 300.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 69.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-23",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 442.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 211.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-24",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 281.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 50.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-25",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 300.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 69.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-26",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 0 ],
																	"destination" : [ "obj-25", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 1 ],
																	"destination" : [ "obj-7", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-19", 0 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 1 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 0 ],
																	"destination" : [ "obj-4", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-23", 0 ],
																	"destination" : [ "obj-18", 1 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-24", 0 ],
																	"destination" : [ "obj-20", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-4", 0 ],
																	"destination" : [ "obj-19", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-7", 0 ],
																	"destination" : [ "obj-26", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
														"globalpatchername" : "",
														"fontname" : "Arial",
														"default_fontface" : 0,
														"fontface" : 0,
														"fontsize" : 12.0,
														"default_fontname" : "Arial",
														"default_fontsize" : 12.0
													}

												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route loop file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 45.0, 72.0, 18.0 ],
													"numoutlets" : 3,
													"fontsize" : 10.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 350.0, 55.0, 82.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "regexp .*(Browse...) @substitute open",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 125.0, 256.0, 121.0, 34.0 ],
													"numoutlets" : 5,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "dropfile",
													"presentation_rect" : [ -5.0, 0.0, 174.683014, 62.542229 ],
													"ignoreclick" : 1,
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 111.0, 100.0, 35.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"border" : 0.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "prefix ./examples/sounds/, insert 0 Browse..., insert 1 <separator>, $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 148.0, 181.0, 391.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "loop $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 205.0, 76.0, 51.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sfplay~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 20.0, 375.0, 47.0, 19.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.0,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-11",
													"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "or Drag a Sound file Here.",
													"presentation_rect" : [ 12.0, 24.0, 161.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 474.0, 91.0, 154.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "File:",
													"presentation_rect" : [ 1.0, 4.0, 34.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 470.0, 61.0, 34.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 201.5, 333.0, 78.0, 19.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.0,
													"outlettype" : [ "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 31.0, 4.0, 142.64183, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"prefix" : "Macintosh HD:/Applications/Max5/examples/sounds/",
													"patching_rect" : [ 148.0, 212.0, 100.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "anton.aif", ",", "cello-f2.aif", ",", "cherokee.aif", ",", "drumLoop.aif", ",", "jongly.aif", ",", "rainstick.aif", ",", "sho0630.aif", ",", "vibes-a1.aif" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-5",
													"types" : [  ],
													"autopopulate" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "playbar",
													"presentation_rect" : [ 5.620921, 45.0, 154.179749, 15.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 19.0, 76.0, 176.0, 23.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"outlettype" : [ "", "int" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 20.0, 415.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 15.0, 5.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"presentation_rect" : [ 5.0, 44.0, 169.683014, 17.683012 ],
													"rounded" : 0,
													"numinlets" : 1,
													"bgcolor" : [ 0.5, 0.5, 0.5, 1.0 ],
													"patching_rect" : [ 433.0, 224.0, 128.0, 128.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-17"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 1 ],
													"destination" : [ "obj-27", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-27", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 3 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 1 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 1 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 1 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-8", 0 ],
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
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t f b b",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 420.0, 225.0, 46.0, 18.0 ],
									"numoutlets" : 3,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "bang", "bang" ],
									"id" : "obj-56"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-25"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-57"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "poltocar",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 255.0, 49.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-19"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "65",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 225.0, 32.5, 16.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-18"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 195.0, 48.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf clear",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 570.0, 180.0, 70.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf frameoval 5 5 135 135 255",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 555.0, 210.0, 183.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-28"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 374.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-32"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-33"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 270.0, 304.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-34"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pack 0 0 0 0 255",
									"fontname" : "Arial",
									"numinlets" : 5,
									"patching_rect" : [ 270.0, 345.0, 96.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-35"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend paintoval",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 270.0, 375.0, 103.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-36"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 285.0, 135.0, 48.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-37"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 70 70",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 60.0, 45.0, 95.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-31"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-30", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 3 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 2 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 4 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-15", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-39", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-37", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-35", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-35", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-35", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-35", 0 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 1 ],
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 0 ],
									"destination" : [ "obj-57", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 2 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-19", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 1 ],
									"destination" : [ "obj-28", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-57", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-35", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 1 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 1110.0, 330.0, 243.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 11.595187,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-69"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.name1~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 840.0, 405.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-17"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.all no",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 840.0, 450.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-18"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.*~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 840.0, 480.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-19"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p ballMapping0",
					"fontname" : "Arial",
					"numinlets" : 0,
					"patching_rect" : [ 900.0, 225.0, 183.0, 20.0 ],
					"numoutlets" : 3,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "signal" ],
					"id" : "obj-20",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 508.0, 152.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 508.0, 152.0, 640.0, 480.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 330.0, 55.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 105.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 105.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 345.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line~",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 375.0, 36.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "signal", "bang" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 225.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!/ 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 300.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "float" ],
									"id" : "obj-65"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 135.0, 225.0, 39.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-64"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r ball3",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 45.0, 105.0, 43.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-63"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 270.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-62"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 225.0, 73.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-61"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0. 0.",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 135.0, 76.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-60"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-59"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 165.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-53"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 105.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-68",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-69",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-68", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-69", 0 ],
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
, 							{
								"patchline" : 								{
									"source" : [ "obj-53", 0 ],
									"destination" : [ "obj-61", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-59", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-61", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 0 ],
									"destination" : [ "obj-53", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-62", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 1 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-62", 0 ],
									"destination" : [ "obj-65", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-63", 0 ],
									"destination" : [ "obj-60", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-64", 0 ],
									"destination" : [ "obj-62", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p dopplershift",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 840.0, 300.0, 161.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-22",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"bglocked" : 0,
						"defrect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 285.0, 105.0, 37.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.0,
									"outlettype" : [ "" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "onepole~",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 226.0, 58.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 112.0, 201.0, 33.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapout~ 0.",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 263.0, 65.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapin~ 2000",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 226.0, 73.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "tapconnect" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "zl nth 3",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 121.0, 48.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 112.0, 92.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-8",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 152.0, 32.5, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 0.3438",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 176.0, 54.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 287.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-11",
									"comment" : "signal out"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 32.0, 58.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-12",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "doppler shift",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 23.0, 22.0, 73.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 59.0, 59.0, 52.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "aed coordinate input",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 139.0, 92.0, 114.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "speed of sound in dry air at 20 °C: 343.8 m/s",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 175.0, 176.0, 242.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-16"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 251.0, 41.5, 251.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-9", 0 ],
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
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p absorption",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 840.0, 270.0, 79.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-23",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"bglocked" : 0,
						"defrect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 119.0, 55.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t 1 1",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 215.0, 38.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 63.0, 68.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-4",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 193.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "bang" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "filtercoeff~ lowpass",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 238.0, 111.0, 19.0 ],
									"numoutlets" : 5,
									"fontsize" : 10.0,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal" ],
									"id" : "obj-6"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "biquad~",
									"fontname" : "Verdana",
									"numinlets" : 6,
									"patching_rect" : [ 40.0, 267.0, 134.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 17000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 140.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 18000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 161.0, 59.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 40.0, 292.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-10",
									"comment" : "filtered signal"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 40.0, 36.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-11",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "high-frequency absorption by air as function of distance",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 15.0, 6.0, 293.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-12"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 67.0, 39.0, 53.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 1 ],
									"destination" : [ "obj-6", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-6", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 4 ],
									"destination" : [ "obj-7", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 3 ],
									"destination" : [ "obj-7", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 2 ],
									"destination" : [ "obj-7", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 1 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-7", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"numinlets" : 0,
					"embed" : 1,
					"patching_rect" : [ 840.0, 120.0, 218.0, 87.0 ],
					"numoutlets" : 1,
					"border" : 1,
					"outlettype" : [ "signal" ],
					"id" : "obj-24",
					"name" : "poiu.maxpat",
					"args" : [  ],
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 840.0, 120.0, 218.0, 87.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"defrect" : [ 840.0, 120.0, 218.0, 87.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 1,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "meter~",
									"presentation_rect" : [ 199.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 90.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "float" ],
									"id" : "obj-39"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 128",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 315.0, 85.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-38"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "gain~",
									"presentation_rect" : [ 184.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 2,
									"bgcolor" : [ 0.85098, 0.85098, 0.85098, 1.0 ],
									"patching_rect" : [ 75.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"stripecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"outlettype" : [ "signal", "int" ],
									"knobcolor" : [ 0.482353, 0.482353, 0.482353, 1.0 ],
									"id" : "obj-27"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p attrArgs",
									"presentation_rect" : [ 645.0, 240.0, 379.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 510.0, 300.0, 73.0, 20.0 ],
									"numoutlets" : 5,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "", "", "", "" ],
									"id" : "obj-24",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 154.370789, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-37"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend noise",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 130.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 155.0, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend wave",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 130.0, 88.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 155.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend loop",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 130.0, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route module vol loop file wave freq noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 360.0, 20.0 ],
													"numoutlets" : 9,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "", "", "", "", "" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"presentation_rect" : [ 585.0, 120.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-5",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 585.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-6",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 627.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 92.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-8",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 665.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 130.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-12",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 765.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 230.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-16",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 870.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 335.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-23",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-37", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 2 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 3 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 4 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 5 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 6 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 7 ],
													"destination" : [ "obj-37", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 1 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"presentation_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-20"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "patcherargs @module 0 @vol -20 @loop 0 @file 2 @wave 0 @freq 440 @noise 0 @filter 0",
									"linecount" : 9,
									"presentation_linecount" : 9,
									"presentation_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "fourth",
									"presentation_rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 645.0, 385.000031, 110.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-3",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 25.0, 55.0, 98.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl slice 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 225.0, 215.0, 58.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "filtergraph~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"dbdisplay" : 0,
													"numinlets" : 8,
													"fgcolor" : [ 0.941176, 0.941176, 0.941176, 0.0 ],
													"domain" : [ 0.0, 22050.0 ],
													"bgcolor" : [ 0.941176, 0.941176, 0.941176, 0.4 ],
													"patching_rect" : [ 225.0, 245.0, 140.0, 45.0 ],
													"numoutlets" : 7,
													"presentation" : 1,
													"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
													"id" : "obj-4",
													"range" : [ 0.0, 16.0 ],
													"nfilters" : 1,
													"setfilter" : [ 0, 9, 1, 0, 0, 23.787561, 1.49664, 0.707107, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 80.0, 350.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"logfreq" : 1,
													"id" : "obj-14",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 160.0, 78.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 4.0, 1.666667, 96.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 125.0, 105.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Noise:", "white", ",", "Noise:", "pink" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-10",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 2 1 1.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 270.0, 86.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pink~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 145.0, 210.0, 40.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "biquad~",
													"fontname" : "Arial",
													"numinlets" : 6,
													"patching_rect" : [ 30.0, 315.0, 86.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 102.0, 2.0, 72.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 225.0, 185.0, 120.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Filter:", "allpass", ",", "Filter:", "lowpass", ",", "Filter:", "highpass", ",", "Filter:", "bandpass", ",", "Filter:", "bandstop", ",", "Filter:", "peaknotch", ",", "Filter:", "lowshelf", ",", "Filter:", "highshelf", ",", "Filter:", "resonant", ",", "Filter:", "display" ],
													"fontsize" : 11.595187,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-47",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 60.0, 210.0, 47.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 360.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 25.0, 15.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 1 ],
													"destination" : [ "obj-47", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-47", 1 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 1 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-9", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"presentation_rect" : [ 4.0, 2.0, 179.0, 20.0 ],
									"rounded" : 0,
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 128.736938, 179.0, 20.0 ],
									"numoutlets" : 3,
									"presentation" : 1,
									"items" : [ "Source:", "Sound", "File", ",", "Source:", "Oscillator", ",", "Source:", "ADC", "(input)", ",", "Source:", "Noise" ],
									"fontsize" : 12.0,
									"outlettype" : [ "int", "", "" ],
									"id" : "obj-6",
									"types" : [  ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : ";\rmax refresh",
									"linecount" : 2,
									"presentation_linecount" : 2,
									"presentation_rect" : [ 70.0, 230.0, 74.0, 32.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 60.0, 80.500031, 32.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p manageDisplay",
									"presentation_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 50.0, 94.0, 652.0, 443.0 ],
										"bglocked" : 0,
										"defrect" : [ 50.0, 94.0, 652.0, 443.0 ],
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
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1][1][1]",
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 3",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox fourth hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 151.0, 96.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox first hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 151.0, 89.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox second hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 151.0, 105.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 2",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox third hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 151.0, 90.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 257.0, 30.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 257.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-32", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1][1][1]",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "clear, $1 0 1",
									"presentation_rect" : [ 192.454483, 163.77652, 78.0, 18.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 75.0, 240.0, 78.0, 18.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "thispatcher",
									"presentation_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "", "" ],
									"id" : "obj-30",
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"presentation_rect" : [ 80.0, 460.629211, 25.0, 25.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 450.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-17",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "matrix~ 4 1 1. @ramp 200",
									"presentation_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 4,
									"patching_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "signal", "list" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "third",
									"presentation_rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 520.0, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-26",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"hidden" : 1,
													"patching_rect" : [ 40.0, 61.0, 74.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Input Channel:",
													"presentation_rect" : [ 5.0, 3.0, 89.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 89.0, 95.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 388.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-9",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 8.0, 25.0, 163.0, 35.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 59.0, 219.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-4",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "adc~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 153.0, 35.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "signal" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 3.0, 7.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "set $1 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 128.0, 54.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "number",
													"presentation_rect" : [ 95.0, 3.0, 48.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 98.0, 48.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "int", "bang" ],
													"id" : "obj-2"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "second",
									"presentation_rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 394.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-21",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "tab",
													"presentation_rect" : [ 50.0, 5.0, 116.0, 16.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 35.0, 280.0, 116.0, 16.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"tabs" : [ "sin", "tri", "rect", "noise" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route wave freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 54.833344, 110.0, 96.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-17"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 440",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 195.0, 110.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 1000",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 484.947357, 48.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 453.947357, 37.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "bang", "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 500",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 275.241211, 397.947357, 87.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "ms",
													"presentation_rect" : [ 152.907867, 43.0, 27.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 568.241211, 120.947357, 27.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Hz",
													"presentation_rect" : [ 92.0, 22.0, 26.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 215.241211, 66.947357, 26.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-30"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 109.0, 43.0, 45.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 274.333344, 425.947357, 45.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-26",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Speed:",
													"presentation_rect" : [ 62.907867, 43.0, 50.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 125.947357, 50.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-25"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 46.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 227.241211, 412.947357, 17.0, 17.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-24"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Pulse:",
													"presentation_rect" : [ 2.0, 43.0, 45.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 82.947357, 45.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-22"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 51.241211, 250.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-21"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 268.241211, 89.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-19"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 46.0, 22.0, 47.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 67.947357, 47.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Freq:",
													"presentation_rect" : [ 2.0, 22.0, 39.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 25.947357, 39.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Wave:",
													"presentation_rect" : [ 2.0, 1.0, 46.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 91.241211, 25.947357, 46.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 5 0.2 10 0 100",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 226.241211, 484.947357, 100.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "metro 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 227.241211, 453.947357, 66.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "bang" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line~ 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.333344, 519.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 571.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.333344, 319.0, 103.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 216.333313, 330.0, 46.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "rect~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 195.0, 290.0, 61.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "tri~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 173.666687, 260.0, 51.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "cycle~ 440",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 224.0, 68.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 4 1 1.",
													"fontname" : "Arial",
													"numinlets" : 4,
													"patching_rect" : [ 152.333344, 378.0, 83.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 152.333344, 615.947388, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 64.241211, 13.947357, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-7", 2 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-7", 3 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 1 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-19", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 1,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-7", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "first",
									"presentation_rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
									"numinlets" : 1,
									"embed" : 1,
									"patching_rect" : [ 269.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-22",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 10.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 20.0, 62.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 157.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 205.0, 50.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p folderOrSoundFile",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 181.0, 100.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-27",
													"patcher" : 													{
														"fileversion" : 1,
														"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
														"boxes" : [ 															{
																"box" : 																{
																	"maxclass" : "comment",
																	"text" : "fill the menu if it's a folder",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 108.0, 323.0, 150.0, 20.0 ],
																	"numoutlets" : 0,
																	"fontsize" : 12.0,
																	"id" : "obj-2"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "t s 1",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 100.0, 32.5, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "int" ],
																	"id" : "obj-20"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 211.0, 166.0, 32.5, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 10.0,
																	"outlettype" : [ "int" ],
																	"id" : "obj-19"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "gate 2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 205.0, 38.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "" ],
																	"id" : "obj-18"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "message",
																	"text" : "prefix $1, insert 0 Browse..., insert 1 <separator>",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 69.0, 238.0, 270.0, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 12.0,
																	"outlettype" : [ "" ],
																	"id" : "obj-7"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "sel fold",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 140.0, 42.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "bang", "" ],
																	"id" : "obj-4"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 300.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 69.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-23",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 442.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 211.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-24",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 281.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 50.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-25",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 300.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 69.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-26",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 0 ],
																	"destination" : [ "obj-25", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 1 ],
																	"destination" : [ "obj-7", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-19", 0 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 1 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 0 ],
																	"destination" : [ "obj-4", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-23", 0 ],
																	"destination" : [ "obj-18", 1 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-24", 0 ],
																	"destination" : [ "obj-20", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-4", 0 ],
																	"destination" : [ "obj-19", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-7", 0 ],
																	"destination" : [ "obj-26", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
														"globalpatchername" : "",
														"fontname" : "Arial",
														"default_fontface" : 0,
														"fontface" : 0,
														"fontsize" : 12.0,
														"default_fontname" : "Arial",
														"default_fontsize" : 12.0
													}

												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route loop file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 45.0, 72.0, 18.0 ],
													"numoutlets" : 3,
													"fontsize" : 10.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 350.0, 55.0, 82.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "regexp .*(Browse...) @substitute open",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 125.0, 256.0, 121.0, 34.0 ],
													"numoutlets" : 5,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "dropfile",
													"presentation_rect" : [ -5.0, 0.0, 174.683014, 62.542229 ],
													"ignoreclick" : 1,
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 111.0, 100.0, 35.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"border" : 0.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "prefix ./examples/sounds/, insert 0 Browse..., insert 1 <separator>, $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 148.0, 181.0, 391.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "loop $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 205.0, 76.0, 51.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sfplay~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 20.0, 375.0, 47.0, 19.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.0,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-11",
													"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "or Drag a Sound file Here.",
													"presentation_rect" : [ 12.0, 24.0, 161.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 474.0, 91.0, 154.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "File:",
													"presentation_rect" : [ 1.0, 4.0, 34.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 470.0, 61.0, 34.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 201.5, 333.0, 78.0, 19.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.0,
													"outlettype" : [ "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 31.0, 4.0, 142.64183, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"prefix" : "Macintosh HD:/Applications/Max5/examples/sounds/",
													"patching_rect" : [ 148.0, 212.0, 100.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "anton.aif", ",", "cello-f2.aif", ",", "cherokee.aif", ",", "drumLoop.aif", ",", "jongly.aif", ",", "rainstick.aif", ",", "sho0630.aif", ",", "vibes-a1.aif" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-5",
													"types" : [  ],
													"autopopulate" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "playbar",
													"presentation_rect" : [ 5.620921, 45.0, 154.179749, 15.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 19.0, 76.0, 176.0, 23.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"outlettype" : [ "", "int" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 20.0, 415.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 15.0, 5.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"presentation_rect" : [ 5.0, 44.0, 169.683014, 17.683012 ],
													"rounded" : 0,
													"numinlets" : 1,
													"bgcolor" : [ 0.5, 0.5, 0.5, 1.0 ],
													"patching_rect" : [ 433.0, 224.0, 128.0, 128.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-17"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 1 ],
													"destination" : [ "obj-27", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-27", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 3 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 1 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 1 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 1 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-8", 0 ],
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
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t f b b",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 420.0, 225.0, 46.0, 18.0 ],
									"numoutlets" : 3,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "bang", "bang" ],
									"id" : "obj-56"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-25"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-57"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "poltocar",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 255.0, 49.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-19"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "65",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 225.0, 32.5, 16.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-18"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 195.0, 48.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf clear",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 570.0, 180.0, 70.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf frameoval 5 5 135 135 255",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 555.0, 210.0, 183.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-28"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 374.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-32"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-33"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 270.0, 304.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-34"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pack 0 0 0 0 255",
									"fontname" : "Arial",
									"numinlets" : 5,
									"patching_rect" : [ 270.0, 345.0, 96.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-35"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend paintoval",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 270.0, 375.0, 103.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-36"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 285.0, 135.0, 48.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-37"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 70 70",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 60.0, 45.0, 95.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-31"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-30", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 3 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 2 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 4 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-15", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-39", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-37", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-35", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-35", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-35", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-35", 0 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 1 ],
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 0 ],
									"destination" : [ "obj-57", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 2 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-19", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 1 ],
									"destination" : [ "obj-28", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-57", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-35", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 1 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 840.0, 330.0, 243.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 11.595187,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-27"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.name1~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 570.0, 405.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-32"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.all no",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 570.0, 450.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-33"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.*~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 570.0, 480.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-34"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p ballMapping0",
					"fontname" : "Arial",
					"numinlets" : 0,
					"patching_rect" : [ 630.0, 225.0, 183.0, 20.0 ],
					"numoutlets" : 3,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "signal" ],
					"id" : "obj-37",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 508.0, 150.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 508.0, 150.0, 640.0, 480.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 330.0, 55.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 105.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 105.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 345.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line~",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 375.0, 36.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "signal", "bang" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 225.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!/ 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 300.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "float" ],
									"id" : "obj-65"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 135.0, 225.0, 39.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-64"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r ball2",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 45.0, 105.0, 43.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-63"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 270.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-62"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 225.0, 73.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-61"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0. 0.",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 135.0, 76.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-60"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-59"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 165.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-53"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 105.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-68",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-69",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-68", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-69", 0 ],
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
, 							{
								"patchline" : 								{
									"source" : [ "obj-53", 0 ],
									"destination" : [ "obj-61", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-59", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-61", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 0 ],
									"destination" : [ "obj-53", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-62", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 1 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-62", 0 ],
									"destination" : [ "obj-65", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-63", 0 ],
									"destination" : [ "obj-60", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-64", 0 ],
									"destination" : [ "obj-62", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p dopplershift",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 570.0, 300.0, 161.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-38",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"bglocked" : 0,
						"defrect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 285.0, 105.0, 37.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.0,
									"outlettype" : [ "" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "onepole~",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 226.0, 58.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 112.0, 201.0, 33.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapout~ 0.",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 263.0, 65.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapin~ 2000",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 226.0, 73.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "tapconnect" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "zl nth 3",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 121.0, 48.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 112.0, 92.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-8",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 152.0, 32.5, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 0.3438",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 176.0, 54.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 287.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-11",
									"comment" : "signal out"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 32.0, 58.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-12",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "doppler shift",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 23.0, 22.0, 73.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 59.0, 59.0, 52.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "aed coordinate input",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 139.0, 92.0, 114.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "speed of sound in dry air at 20 °C: 343.8 m/s",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 175.0, 176.0, 242.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-16"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 251.0, 41.5, 251.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-9", 0 ],
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
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p absorption",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 570.0, 270.0, 79.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-39",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"bglocked" : 0,
						"defrect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 119.0, 55.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t 1 1",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 215.0, 38.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 63.0, 68.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-4",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 193.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "bang" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "filtercoeff~ lowpass",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 238.0, 111.0, 19.0 ],
									"numoutlets" : 5,
									"fontsize" : 10.0,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal" ],
									"id" : "obj-6"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "biquad~",
									"fontname" : "Verdana",
									"numinlets" : 6,
									"patching_rect" : [ 40.0, 267.0, 134.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 17000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 140.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 18000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 161.0, 59.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 40.0, 292.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-10",
									"comment" : "filtered signal"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 40.0, 36.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-11",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "high-frequency absorption by air as function of distance",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 15.0, 6.0, 293.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-12"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 67.0, 39.0, 53.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 1 ],
									"destination" : [ "obj-6", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-6", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 4 ],
									"destination" : [ "obj-7", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 3 ],
									"destination" : [ "obj-7", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 2 ],
									"destination" : [ "obj-7", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 1 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-7", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"numinlets" : 0,
					"embed" : 1,
					"patching_rect" : [ 570.0, 120.0, 218.0, 87.0 ],
					"numoutlets" : 1,
					"border" : 1,
					"outlettype" : [ "signal" ],
					"id" : "obj-40",
					"name" : "poiu.maxpat",
					"args" : [  ],
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 570.0, 120.0, 218.0, 87.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"defrect" : [ 570.0, 120.0, 218.0, 87.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 1,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "meter~",
									"presentation_rect" : [ 199.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 90.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "float" ],
									"id" : "obj-39"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 128",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 315.0, 85.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-38"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "gain~",
									"presentation_rect" : [ 184.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 2,
									"bgcolor" : [ 0.85098, 0.85098, 0.85098, 1.0 ],
									"patching_rect" : [ 75.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"stripecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"outlettype" : [ "signal", "int" ],
									"knobcolor" : [ 0.482353, 0.482353, 0.482353, 1.0 ],
									"id" : "obj-27"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p attrArgs",
									"presentation_rect" : [ 645.0, 240.0, 379.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 510.0, 300.0, 73.0, 20.0 ],
									"numoutlets" : 5,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "", "", "", "" ],
									"id" : "obj-24",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 154.370789, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-37"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend noise",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 130.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 155.0, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend wave",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 130.0, 88.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 155.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend loop",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 130.0, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route module vol loop file wave freq noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 360.0, 20.0 ],
													"numoutlets" : 9,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "", "", "", "", "" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"presentation_rect" : [ 585.0, 120.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-5",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 585.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-6",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 627.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 92.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-8",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 665.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 130.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-12",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 765.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 230.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-16",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 870.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 335.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-23",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-37", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 2 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 3 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 4 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 5 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 6 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 7 ],
													"destination" : [ "obj-37", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 1 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"presentation_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-20"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "patcherargs @module 0 @vol -20 @loop 0 @file 2 @wave 0 @freq 440 @noise 0 @filter 0",
									"linecount" : 9,
									"presentation_linecount" : 9,
									"presentation_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "fourth",
									"presentation_rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 645.0, 385.000031, 110.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-3",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 25.0, 55.0, 98.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl slice 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 225.0, 215.0, 58.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "filtergraph~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"dbdisplay" : 0,
													"numinlets" : 8,
													"fgcolor" : [ 0.941176, 0.941176, 0.941176, 0.0 ],
													"domain" : [ 0.0, 22050.0 ],
													"bgcolor" : [ 0.941176, 0.941176, 0.941176, 0.4 ],
													"patching_rect" : [ 225.0, 245.0, 140.0, 45.0 ],
													"numoutlets" : 7,
													"presentation" : 1,
													"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
													"id" : "obj-4",
													"range" : [ 0.0, 16.0 ],
													"nfilters" : 1,
													"setfilter" : [ 0, 9, 1, 0, 0, 23.787561, 1.49664, 0.707107, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 80.0, 350.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"logfreq" : 1,
													"id" : "obj-14",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 160.0, 78.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 4.0, 1.666667, 96.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 125.0, 105.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Noise:", "white", ",", "Noise:", "pink" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-10",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 2 1 1.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 270.0, 86.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pink~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 145.0, 210.0, 40.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "biquad~",
													"fontname" : "Arial",
													"numinlets" : 6,
													"patching_rect" : [ 30.0, 315.0, 86.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 102.0, 2.0, 72.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 225.0, 185.0, 120.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Filter:", "allpass", ",", "Filter:", "lowpass", ",", "Filter:", "highpass", ",", "Filter:", "bandpass", ",", "Filter:", "bandstop", ",", "Filter:", "peaknotch", ",", "Filter:", "lowshelf", ",", "Filter:", "highshelf", ",", "Filter:", "resonant", ",", "Filter:", "display" ],
													"fontsize" : 11.595187,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-47",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 60.0, 210.0, 47.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 360.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 25.0, 15.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 1 ],
													"destination" : [ "obj-47", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-47", 1 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 1 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-9", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"presentation_rect" : [ 4.0, 2.0, 179.0, 20.0 ],
									"rounded" : 0,
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 128.736938, 179.0, 20.0 ],
									"numoutlets" : 3,
									"presentation" : 1,
									"items" : [ "Source:", "Sound", "File", ",", "Source:", "Oscillator", ",", "Source:", "ADC", "(input)", ",", "Source:", "Noise" ],
									"fontsize" : 12.0,
									"outlettype" : [ "int", "", "" ],
									"id" : "obj-6",
									"types" : [  ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : ";\rmax refresh",
									"linecount" : 2,
									"presentation_linecount" : 2,
									"presentation_rect" : [ 70.0, 230.0, 74.0, 32.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 60.0, 80.500031, 32.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p manageDisplay",
									"presentation_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 50.0, 94.0, 652.0, 443.0 ],
										"bglocked" : 0,
										"defrect" : [ 50.0, 94.0, 652.0, 443.0 ],
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
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1][2]",
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 3",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox fourth hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 151.0, 96.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox first hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 151.0, 89.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox second hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 151.0, 105.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 2",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox third hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 151.0, 90.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 257.0, 30.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 257.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-32", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1][2]",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "clear, $1 0 1",
									"presentation_rect" : [ 192.454483, 163.77652, 78.0, 18.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 75.0, 240.0, 78.0, 18.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "thispatcher",
									"presentation_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "", "" ],
									"id" : "obj-30",
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"presentation_rect" : [ 80.0, 460.629211, 25.0, 25.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 450.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-17",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "matrix~ 4 1 1. @ramp 200",
									"presentation_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 4,
									"patching_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "signal", "list" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "third",
									"presentation_rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 520.0, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-26",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"hidden" : 1,
													"patching_rect" : [ 40.0, 61.0, 74.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Input Channel:",
													"presentation_rect" : [ 5.0, 3.0, 89.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 89.0, 95.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 388.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-9",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 8.0, 25.0, 163.0, 35.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 59.0, 219.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-4",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "adc~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 153.0, 35.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "signal" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 3.0, 7.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "set $1 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 128.0, 54.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "number",
													"presentation_rect" : [ 95.0, 3.0, 48.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 98.0, 48.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "int", "bang" ],
													"id" : "obj-2"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "second",
									"presentation_rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 394.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-21",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "tab",
													"presentation_rect" : [ 50.0, 5.0, 116.0, 16.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 35.0, 280.0, 116.0, 16.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"tabs" : [ "sin", "tri", "rect", "noise" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route wave freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 54.833344, 110.0, 96.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-17"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 440",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 195.0, 110.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 1000",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 484.947357, 48.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 453.947357, 37.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "bang", "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 500",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 275.241211, 397.947357, 87.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "ms",
													"presentation_rect" : [ 152.907867, 43.0, 27.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 568.241211, 120.947357, 27.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Hz",
													"presentation_rect" : [ 92.0, 22.0, 26.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 215.241211, 66.947357, 26.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-30"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 109.0, 43.0, 45.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 274.333344, 425.947357, 45.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-26",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Speed:",
													"presentation_rect" : [ 62.907867, 43.0, 50.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 125.947357, 50.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-25"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 46.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 227.241211, 412.947357, 17.0, 17.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-24"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Pulse:",
													"presentation_rect" : [ 2.0, 43.0, 45.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 82.947357, 45.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-22"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 51.241211, 250.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-21"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 268.241211, 89.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-19"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 46.0, 22.0, 47.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 67.947357, 47.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Freq:",
													"presentation_rect" : [ 2.0, 22.0, 39.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 25.947357, 39.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Wave:",
													"presentation_rect" : [ 2.0, 1.0, 46.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 91.241211, 25.947357, 46.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 5 0.2 10 0 100",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 226.241211, 484.947357, 100.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "metro 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 227.241211, 453.947357, 66.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "bang" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line~ 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.333344, 519.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 571.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.333344, 319.0, 103.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 216.333313, 330.0, 46.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "rect~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 195.0, 290.0, 61.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "tri~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 173.666687, 260.0, 51.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "cycle~ 440",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 224.0, 68.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 4 1 1.",
													"fontname" : "Arial",
													"numinlets" : 4,
													"patching_rect" : [ 152.333344, 378.0, 83.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 152.333344, 615.947388, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 64.241211, 13.947357, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-7", 2 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-7", 3 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 1 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-19", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 1,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-7", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "first",
									"presentation_rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
									"numinlets" : 1,
									"embed" : 1,
									"patching_rect" : [ 269.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-22",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 10.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 20.0, 62.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 157.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 205.0, 50.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p folderOrSoundFile",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 181.0, 100.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-27",
													"patcher" : 													{
														"fileversion" : 1,
														"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
														"boxes" : [ 															{
																"box" : 																{
																	"maxclass" : "comment",
																	"text" : "fill the menu if it's a folder",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 108.0, 323.0, 150.0, 20.0 ],
																	"numoutlets" : 0,
																	"fontsize" : 12.0,
																	"id" : "obj-2"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "t s 1",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 100.0, 32.5, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "int" ],
																	"id" : "obj-20"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 211.0, 166.0, 32.5, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 10.0,
																	"outlettype" : [ "int" ],
																	"id" : "obj-19"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "gate 2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 205.0, 38.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "" ],
																	"id" : "obj-18"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "message",
																	"text" : "prefix $1, insert 0 Browse..., insert 1 <separator>",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 69.0, 238.0, 270.0, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 12.0,
																	"outlettype" : [ "" ],
																	"id" : "obj-7"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "sel fold",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 140.0, 42.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "bang", "" ],
																	"id" : "obj-4"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 300.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 69.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-23",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 442.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 211.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-24",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 281.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 50.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-25",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 300.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 69.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-26",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 0 ],
																	"destination" : [ "obj-25", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 1 ],
																	"destination" : [ "obj-7", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-19", 0 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 1 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 0 ],
																	"destination" : [ "obj-4", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-23", 0 ],
																	"destination" : [ "obj-18", 1 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-24", 0 ],
																	"destination" : [ "obj-20", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-4", 0 ],
																	"destination" : [ "obj-19", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-7", 0 ],
																	"destination" : [ "obj-26", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
														"globalpatchername" : "",
														"fontname" : "Arial",
														"default_fontface" : 0,
														"fontface" : 0,
														"fontsize" : 12.0,
														"default_fontname" : "Arial",
														"default_fontsize" : 12.0
													}

												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route loop file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 45.0, 72.0, 18.0 ],
													"numoutlets" : 3,
													"fontsize" : 10.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 350.0, 55.0, 82.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "regexp .*(Browse...) @substitute open",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 125.0, 256.0, 121.0, 34.0 ],
													"numoutlets" : 5,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "dropfile",
													"presentation_rect" : [ -5.0, 0.0, 174.683014, 62.542229 ],
													"ignoreclick" : 1,
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 111.0, 100.0, 35.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"border" : 0.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "prefix ./examples/sounds/, insert 0 Browse..., insert 1 <separator>, $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 148.0, 181.0, 391.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "loop $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 205.0, 76.0, 51.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sfplay~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 20.0, 375.0, 47.0, 19.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.0,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-11",
													"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "or Drag a Sound file Here.",
													"presentation_rect" : [ 12.0, 24.0, 161.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 474.0, 91.0, 154.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "File:",
													"presentation_rect" : [ 1.0, 4.0, 34.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 470.0, 61.0, 34.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 201.5, 333.0, 78.0, 19.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.0,
													"outlettype" : [ "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 31.0, 4.0, 142.64183, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"prefix" : "Macintosh HD:/Applications/Max5/examples/sounds/",
													"patching_rect" : [ 148.0, 212.0, 100.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "anton.aif", ",", "cello-f2.aif", ",", "cherokee.aif", ",", "drumLoop.aif", ",", "jongly.aif", ",", "rainstick.aif", ",", "sho0630.aif", ",", "vibes-a1.aif" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-5",
													"types" : [  ],
													"autopopulate" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "playbar",
													"presentation_rect" : [ 5.620921, 45.0, 154.179749, 15.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 19.0, 76.0, 176.0, 23.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"outlettype" : [ "", "int" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 20.0, 415.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 15.0, 5.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"presentation_rect" : [ 5.0, 44.0, 169.683014, 17.683012 ],
													"rounded" : 0,
													"numinlets" : 1,
													"bgcolor" : [ 0.5, 0.5, 0.5, 1.0 ],
													"patching_rect" : [ 433.0, 224.0, 128.0, 128.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-17"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 1 ],
													"destination" : [ "obj-27", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-27", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 3 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 1 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 1 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 1 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-8", 0 ],
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
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t f b b",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 420.0, 225.0, 46.0, 18.0 ],
									"numoutlets" : 3,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "bang", "bang" ],
									"id" : "obj-56"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-25"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-57"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "poltocar",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 255.0, 49.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-19"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "65",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 225.0, 32.5, 16.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-18"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 195.0, 48.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf clear",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 570.0, 180.0, 70.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf frameoval 5 5 135 135 255",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 555.0, 210.0, 183.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-28"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 374.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-32"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-33"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 270.0, 304.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-34"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pack 0 0 0 0 255",
									"fontname" : "Arial",
									"numinlets" : 5,
									"patching_rect" : [ 270.0, 345.0, 96.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-35"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend paintoval",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 270.0, 375.0, 103.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-36"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 285.0, 135.0, 48.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-37"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 70 70",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 60.0, 45.0, 95.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-31"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-30", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 3 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 2 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 4 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-15", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-39", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-37", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-35", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-35", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-35", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-35", 0 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 1 ],
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 0 ],
									"destination" : [ "obj-57", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 2 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-19", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 1 ],
									"destination" : [ "obj-28", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-57", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-35", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 1 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 570.0, 330.0, 243.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 11.595187,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-41"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.dac~ 1:16",
					"fontname" : "Arial",
					"numinlets" : 16,
					"patching_rect" : [ 896.0, 700.0, 241.5, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-28"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.name1~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 315.0, 405.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-9"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.all no",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 315.0, 450.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-10"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.*~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 315.0, 480.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-11"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p ballMapping0",
					"fontname" : "Arial",
					"numinlets" : 0,
					"patching_rect" : [ 375.0, 225.0, 183.0, 20.0 ],
					"numoutlets" : 3,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "signal" ],
					"id" : "obj-12",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 508.0, 150.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 508.0, 150.0, 640.0, 480.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 330.0, 55.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 105.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 105.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 345.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line~",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 375.0, 36.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "signal", "bang" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 225.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!/ 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 300.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "float" ],
									"id" : "obj-65"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 135.0, 225.0, 39.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-64"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r ball1",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 45.0, 105.0, 43.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-63"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 270.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-62"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 225.0, 73.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-61"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0. 0.",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 135.0, 76.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-60"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-59"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 165.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-53"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 105.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-68",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-69",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-68", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-69", 0 ],
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
, 							{
								"patchline" : 								{
									"source" : [ "obj-53", 0 ],
									"destination" : [ "obj-61", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-59", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-61", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 0 ],
									"destination" : [ "obj-53", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-62", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 1 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-62", 0 ],
									"destination" : [ "obj-65", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-63", 0 ],
									"destination" : [ "obj-60", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-64", 0 ],
									"destination" : [ "obj-62", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p dopplershift",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 315.0, 300.0, 161.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-13",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"bglocked" : 0,
						"defrect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 285.0, 105.0, 37.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.0,
									"outlettype" : [ "" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "onepole~",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 226.0, 58.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 112.0, 201.0, 33.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapout~ 0.",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 263.0, 65.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapin~ 2000",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 226.0, 73.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "tapconnect" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "zl nth 3",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 121.0, 48.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 112.0, 92.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-8",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 152.0, 32.5, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 0.3438",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 176.0, 54.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 287.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-11",
									"comment" : "signal out"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 32.0, 58.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-12",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "doppler shift",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 23.0, 22.0, 73.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 59.0, 59.0, 52.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "aed coordinate input",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 139.0, 92.0, 114.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "speed of sound in dry air at 20 °C: 343.8 m/s",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 175.0, 176.0, 242.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-16"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 251.0, 41.5, 251.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-9", 0 ],
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
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p absorption",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 315.0, 270.0, 79.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-14",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"bglocked" : 0,
						"defrect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 119.0, 55.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t 1 1",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 215.0, 38.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 63.0, 68.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-4",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 193.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "bang" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "filtercoeff~ lowpass",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 238.0, 111.0, 19.0 ],
									"numoutlets" : 5,
									"fontsize" : 10.0,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal" ],
									"id" : "obj-6"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "biquad~",
									"fontname" : "Verdana",
									"numinlets" : 6,
									"patching_rect" : [ 40.0, 267.0, 134.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 17000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 140.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 18000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 161.0, 59.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 40.0, 292.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-10",
									"comment" : "filtered signal"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 40.0, 36.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-11",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "high-frequency absorption by air as function of distance",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 15.0, 6.0, 293.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-12"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 67.0, 39.0, 53.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 1 ],
									"destination" : [ "obj-6", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-6", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 4 ],
									"destination" : [ "obj-7", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 3 ],
									"destination" : [ "obj-7", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 2 ],
									"destination" : [ "obj-7", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 1 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-7", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"numinlets" : 0,
					"embed" : 1,
					"patching_rect" : [ 315.0, 120.0, 218.0, 87.0 ],
					"numoutlets" : 1,
					"border" : 1,
					"outlettype" : [ "signal" ],
					"id" : "obj-15",
					"name" : "poiu.maxpat",
					"args" : [  ],
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 315.0, 120.0, 218.0, 87.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"defrect" : [ 315.0, 120.0, 218.0, 87.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 1,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "meter~",
									"presentation_rect" : [ 199.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 90.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "float" ],
									"id" : "obj-39"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 128",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 315.0, 85.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-38"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "gain~",
									"presentation_rect" : [ 184.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 2,
									"bgcolor" : [ 0.85098, 0.85098, 0.85098, 1.0 ],
									"patching_rect" : [ 75.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"stripecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"outlettype" : [ "signal", "int" ],
									"knobcolor" : [ 0.482353, 0.482353, 0.482353, 1.0 ],
									"id" : "obj-27"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p attrArgs",
									"presentation_rect" : [ 645.0, 240.0, 379.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 510.0, 300.0, 73.0, 20.0 ],
									"numoutlets" : 5,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "", "", "", "" ],
									"id" : "obj-24",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 154.370789, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-37"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend noise",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 130.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 155.0, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend wave",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 130.0, 88.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 155.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend loop",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 130.0, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route module vol loop file wave freq noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 360.0, 20.0 ],
													"numoutlets" : 9,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "", "", "", "", "" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"presentation_rect" : [ 585.0, 120.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-5",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 585.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-6",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 627.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 92.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-8",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 665.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 130.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-12",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 765.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 230.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-16",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 870.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 335.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-23",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-37", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 2 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 3 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 4 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 5 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 6 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 7 ],
													"destination" : [ "obj-37", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 1 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"presentation_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-20"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "patcherargs @module 0 @vol -20 @loop 0 @file 2 @wave 0 @freq 440 @noise 0 @filter 0",
									"linecount" : 9,
									"presentation_linecount" : 9,
									"presentation_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "fourth",
									"presentation_rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 645.0, 385.000031, 110.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-3",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 25.0, 55.0, 98.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl slice 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 225.0, 215.0, 58.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "filtergraph~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"dbdisplay" : 0,
													"numinlets" : 8,
													"fgcolor" : [ 0.941176, 0.941176, 0.941176, 0.0 ],
													"domain" : [ 0.0, 22050.0 ],
													"bgcolor" : [ 0.941176, 0.941176, 0.941176, 0.4 ],
													"patching_rect" : [ 225.0, 245.0, 140.0, 45.0 ],
													"numoutlets" : 7,
													"presentation" : 1,
													"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
													"id" : "obj-4",
													"range" : [ 0.0, 16.0 ],
													"nfilters" : 1,
													"setfilter" : [ 0, 9, 1, 0, 0, 23.787561, 1.49664, 0.707107, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 80.0, 350.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"logfreq" : 1,
													"id" : "obj-14",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 160.0, 78.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 4.0, 1.666667, 96.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 125.0, 105.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Noise:", "white", ",", "Noise:", "pink" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-10",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 2 1 1.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 270.0, 86.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pink~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 145.0, 210.0, 40.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "biquad~",
													"fontname" : "Arial",
													"numinlets" : 6,
													"patching_rect" : [ 30.0, 315.0, 86.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 102.0, 2.0, 72.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 225.0, 185.0, 120.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Filter:", "allpass", ",", "Filter:", "lowpass", ",", "Filter:", "highpass", ",", "Filter:", "bandpass", ",", "Filter:", "bandstop", ",", "Filter:", "peaknotch", ",", "Filter:", "lowshelf", ",", "Filter:", "highshelf", ",", "Filter:", "resonant", ",", "Filter:", "display" ],
													"fontsize" : 11.595187,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-47",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 60.0, 210.0, 47.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 360.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 25.0, 15.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 1 ],
													"destination" : [ "obj-47", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-47", 1 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 1 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-9", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"presentation_rect" : [ 4.0, 2.0, 179.0, 20.0 ],
									"rounded" : 0,
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 128.736938, 179.0, 20.0 ],
									"numoutlets" : 3,
									"presentation" : 1,
									"items" : [ "Source:", "Sound", "File", ",", "Source:", "Oscillator", ",", "Source:", "ADC", "(input)", ",", "Source:", "Noise" ],
									"fontsize" : 12.0,
									"outlettype" : [ "int", "", "" ],
									"id" : "obj-6",
									"types" : [  ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : ";\rmax refresh",
									"linecount" : 2,
									"presentation_linecount" : 2,
									"presentation_rect" : [ 70.0, 230.0, 74.0, 32.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 60.0, 80.500031, 32.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p manageDisplay",
									"presentation_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 50.0, 94.0, 652.0, 443.0 ],
										"bglocked" : 0,
										"defrect" : [ 50.0, 94.0, 652.0, 443.0 ],
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
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1][1]",
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 3",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox fourth hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 151.0, 96.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox first hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 151.0, 89.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox second hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 151.0, 105.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 2",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox third hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 151.0, 90.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 257.0, 30.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 257.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-32", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1][1]",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "clear, $1 0 1",
									"presentation_rect" : [ 192.454483, 163.77652, 78.0, 18.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 75.0, 240.0, 78.0, 18.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "thispatcher",
									"presentation_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "", "" ],
									"id" : "obj-30",
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"presentation_rect" : [ 80.0, 460.629211, 25.0, 25.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 450.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-17",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "matrix~ 4 1 1. @ramp 200",
									"presentation_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 4,
									"patching_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "signal", "list" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "third",
									"presentation_rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 520.0, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-26",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"hidden" : 1,
													"patching_rect" : [ 40.0, 61.0, 74.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Input Channel:",
													"presentation_rect" : [ 5.0, 3.0, 89.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 89.0, 95.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 388.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-9",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 8.0, 25.0, 163.0, 35.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 59.0, 219.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-4",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "adc~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 153.0, 35.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "signal" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 3.0, 7.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "set $1 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 128.0, 54.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "number",
													"presentation_rect" : [ 95.0, 3.0, 48.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 98.0, 48.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "int", "bang" ],
													"id" : "obj-2"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "second",
									"presentation_rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 394.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-21",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "tab",
													"presentation_rect" : [ 50.0, 5.0, 116.0, 16.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 35.0, 280.0, 116.0, 16.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"tabs" : [ "sin", "tri", "rect", "noise" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route wave freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 54.833344, 110.0, 96.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-17"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 440",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 195.0, 110.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 1000",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 484.947357, 48.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 453.947357, 37.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "bang", "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 500",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 275.241211, 397.947357, 87.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "ms",
													"presentation_rect" : [ 152.907867, 43.0, 27.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 568.241211, 120.947357, 27.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Hz",
													"presentation_rect" : [ 92.0, 22.0, 26.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 215.241211, 66.947357, 26.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-30"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 109.0, 43.0, 45.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 274.333344, 425.947357, 45.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-26",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Speed:",
													"presentation_rect" : [ 62.907867, 43.0, 50.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 125.947357, 50.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-25"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 46.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 227.241211, 412.947357, 17.0, 17.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-24"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Pulse:",
													"presentation_rect" : [ 2.0, 43.0, 45.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 82.947357, 45.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-22"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 51.241211, 250.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-21"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 268.241211, 89.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-19"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 46.0, 22.0, 47.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 67.947357, 47.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Freq:",
													"presentation_rect" : [ 2.0, 22.0, 39.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 25.947357, 39.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Wave:",
													"presentation_rect" : [ 2.0, 1.0, 46.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 91.241211, 25.947357, 46.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 5 0.2 10 0 100",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 226.241211, 484.947357, 100.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "metro 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 227.241211, 453.947357, 66.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "bang" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line~ 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.333344, 519.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 571.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.333344, 319.0, 103.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 216.333313, 330.0, 46.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "rect~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 195.0, 290.0, 61.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "tri~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 173.666687, 260.0, 51.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "cycle~ 440",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 224.0, 68.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 4 1 1.",
													"fontname" : "Arial",
													"numinlets" : 4,
													"patching_rect" : [ 152.333344, 378.0, 83.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 152.333344, 615.947388, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 64.241211, 13.947357, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-7", 2 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-7", 3 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 1 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-19", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 1,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-7", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "first",
									"presentation_rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
									"numinlets" : 1,
									"embed" : 1,
									"patching_rect" : [ 269.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-22",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 10.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 20.0, 62.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 157.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 205.0, 50.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p folderOrSoundFile",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 181.0, 100.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-27",
													"patcher" : 													{
														"fileversion" : 1,
														"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
														"boxes" : [ 															{
																"box" : 																{
																	"maxclass" : "comment",
																	"text" : "fill the menu if it's a folder",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 108.0, 323.0, 150.0, 20.0 ],
																	"numoutlets" : 0,
																	"fontsize" : 12.0,
																	"id" : "obj-2"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "t s 1",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 100.0, 32.5, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "int" ],
																	"id" : "obj-20"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 211.0, 166.0, 32.5, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 10.0,
																	"outlettype" : [ "int" ],
																	"id" : "obj-19"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "gate 2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 205.0, 38.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "" ],
																	"id" : "obj-18"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "message",
																	"text" : "prefix $1, insert 0 Browse..., insert 1 <separator>",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 69.0, 238.0, 270.0, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 12.0,
																	"outlettype" : [ "" ],
																	"id" : "obj-7"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "sel fold",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 140.0, 42.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "bang", "" ],
																	"id" : "obj-4"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 300.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 69.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-23",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 442.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 211.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-24",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 281.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 50.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-25",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 300.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 69.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-26",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 0 ],
																	"destination" : [ "obj-25", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 1 ],
																	"destination" : [ "obj-7", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-19", 0 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 1 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 0 ],
																	"destination" : [ "obj-4", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-23", 0 ],
																	"destination" : [ "obj-18", 1 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-24", 0 ],
																	"destination" : [ "obj-20", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-4", 0 ],
																	"destination" : [ "obj-19", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-7", 0 ],
																	"destination" : [ "obj-26", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
														"globalpatchername" : "",
														"fontname" : "Arial",
														"default_fontface" : 0,
														"fontface" : 0,
														"fontsize" : 12.0,
														"default_fontname" : "Arial",
														"default_fontsize" : 12.0
													}

												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route loop file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 45.0, 72.0, 18.0 ],
													"numoutlets" : 3,
													"fontsize" : 10.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 350.0, 55.0, 82.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "regexp .*(Browse...) @substitute open",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 125.0, 256.0, 121.0, 34.0 ],
													"numoutlets" : 5,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "dropfile",
													"presentation_rect" : [ -5.0, 0.0, 174.683014, 62.542229 ],
													"ignoreclick" : 1,
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 111.0, 100.0, 35.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"border" : 0.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "prefix ./examples/sounds/, insert 0 Browse..., insert 1 <separator>, $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 148.0, 181.0, 391.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "loop $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 205.0, 76.0, 51.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sfplay~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 20.0, 375.0, 47.0, 19.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.0,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-11",
													"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "or Drag a Sound file Here.",
													"presentation_rect" : [ 12.0, 24.0, 161.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 474.0, 91.0, 154.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "File:",
													"presentation_rect" : [ 1.0, 4.0, 34.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 470.0, 61.0, 34.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 201.5, 333.0, 78.0, 19.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.0,
													"outlettype" : [ "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 31.0, 4.0, 142.64183, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"prefix" : "Macintosh HD:/Applications/Max5/examples/sounds/",
													"patching_rect" : [ 148.0, 212.0, 100.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "anton.aif", ",", "cello-f2.aif", ",", "cherokee.aif", ",", "drumLoop.aif", ",", "jongly.aif", ",", "rainstick.aif", ",", "sho0630.aif", ",", "vibes-a1.aif" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-5",
													"types" : [  ],
													"autopopulate" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "playbar",
													"presentation_rect" : [ 5.620921, 45.0, 154.179749, 15.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 19.0, 76.0, 176.0, 23.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"outlettype" : [ "", "int" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 20.0, 415.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 15.0, 5.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"presentation_rect" : [ 5.0, 44.0, 169.683014, 17.683012 ],
													"rounded" : 0,
													"numinlets" : 1,
													"bgcolor" : [ 0.5, 0.5, 0.5, 1.0 ],
													"patching_rect" : [ 433.0, 224.0, 128.0, 128.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-17"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 1 ],
													"destination" : [ "obj-27", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-27", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 3 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 1 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 1 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 1 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-8", 0 ],
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
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t f b b",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 420.0, 225.0, 46.0, 18.0 ],
									"numoutlets" : 3,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "bang", "bang" ],
									"id" : "obj-56"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-25"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-57"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "poltocar",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 255.0, 49.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-19"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "65",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 225.0, 32.5, 16.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-18"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 195.0, 48.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf clear",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 570.0, 180.0, 70.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf frameoval 5 5 135 135 255",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 555.0, 210.0, 183.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-28"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 374.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-32"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-33"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 270.0, 304.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-34"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pack 0 0 0 0 255",
									"fontname" : "Arial",
									"numinlets" : 5,
									"patching_rect" : [ 270.0, 345.0, 96.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-35"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend paintoval",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 270.0, 375.0, 103.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-36"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 285.0, 135.0, 48.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-37"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 70 70",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 60.0, 45.0, 95.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-31"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-30", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 3 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 2 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 4 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-15", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-39", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-37", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-35", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-35", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-35", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-35", 0 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 1 ],
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 0 ],
									"destination" : [ "obj-57", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 2 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-19", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 1 ],
									"destination" : [ "obj-28", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-57", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-35", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 1 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 315.0, 330.0, 243.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 11.595187,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-16"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.name1~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 45.0, 405.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-8"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.all no",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 45.0, 450.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-3"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.*~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 45.0, 480.0, 246.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-1"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 735.0, 30.0, 50.0, 20.0 ],
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-29"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 930.0, 30.0, 50.0, 20.0 ],
					"minimum" : 0.0,
					"numoutlets" : 2,
					"maximum" : 1.0,
					"fontsize" : 11.595187,
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-205"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s wet",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 930.0, 75.0, 38.0, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-206"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 870.0, 30.0, 50.0, 20.0 ],
					"minimum" : 0.0,
					"numoutlets" : 2,
					"maximum" : 1.0,
					"fontsize" : 11.595187,
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-204"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s diff",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 870.0, 75.0, 35.0, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-203"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 810.0, 30.0, 50.0, 20.0 ],
					"minimum" : 0,
					"numoutlets" : 2,
					"maximum" : 44100,
					"fontsize" : 11.595187,
					"outlettype" : [ "int", "bang" ],
					"id" : "obj-201"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s freq",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 810.0, 75.0, 39.0, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-199"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s decay",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 735.0, 75.0, 50.0, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-194"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s size",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 645.0, 75.0, 40.0, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-193"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 645.0, 30.0, 50.0, 20.0 ],
					"minimum" : 0,
					"numoutlets" : 2,
					"maximum" : 200,
					"fontsize" : 11.595187,
					"outlettype" : [ "int", "bang" ],
					"id" : "obj-192"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p key32",
					"fontname" : "Arial",
					"numinlets" : 0,
					"patching_rect" : [ 450.0, 30.0, 51.0, 20.0 ],
					"numoutlets" : 1,
					"fontsize" : 11.595187,
					"outlettype" : [ "bang" ],
					"id" : "obj-46",
					"patcher" : 					{
						"fileversion" : 1,
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "button",
									"numinlets" : 1,
									"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sel 32",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "bang", "" ],
									"id" : "obj-23"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "key",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
									"numoutlets" : 4,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "int", "int", "int" ],
									"id" : "obj-17"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-45",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-45", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [ 59.5, 151.0, 59.5, 151.0 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.connect 7 16",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 450.0, 60.0, 99.0, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-2"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p reverb",
					"fontname" : "Arial",
					"numinlets" : 0,
					"patching_rect" : [ 248.0, 588.0, 244.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"id" : "obj-92",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 55.0, 69.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 55.0, 69.0, 640.0, 480.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r wet",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 71.0, 211.0, 37.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r dry",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 421.0, 258.0, 34.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 330.0, 270.0, 72.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 58.0, 240.0, 72.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r diff",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 380.0, 205.0, 34.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-74"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r freq",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 320.0, 100.0, 39.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-73"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r decay",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 230.0, 100.0, 50.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-72"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 140.0, 100.0, 39.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-71"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 230.0, 130.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "bang" ],
									"id" : "obj-29"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 50.0, 265.0, 50.0, 20.0 ],
									"minimum" : 0.0,
									"numoutlets" : 2,
									"maximum" : 1.0,
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "bang" ],
									"id" : "obj-207"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend wet",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 50.0, 295.0, 74.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-208"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend dry",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 320.0, 295.0, 72.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-206"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 320.0, 205.0, 50.0, 20.0 ],
									"minimum" : 0.0,
									"numoutlets" : 2,
									"maximum" : 1.0,
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "bang" ],
									"id" : "obj-204"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend diffusion",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 320.0, 235.0, 99.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-203"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 320.0, 145.0, 50.0, 20.0 ],
									"minimum" : 0,
									"numoutlets" : 2,
									"maximum" : 44100,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "bang" ],
									"id" : "obj-201"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend frequency",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 320.0, 175.0, 107.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-199"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend decay",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 230.0, 175.0, 87.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-194"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend size",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 140.0, 175.0, 77.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-193"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 140.0, 130.0, 50.0, 20.0 ],
									"minimum" : 0,
									"numoutlets" : 2,
									"maximum" : 200,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "bang" ],
									"id" : "obj-192"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 7 hoa.all no",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 140.0, 385.0, 208.0, 20.0 ],
									"numoutlets" : 15,
									"fontsize" : 11.595187,
									"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
									"id" : "obj-22"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 140.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-77",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 153.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-78",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 167.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-79",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 180.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-80",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 194.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-81",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 207.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-82",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 221.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-83",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 234.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-84",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 248.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-85",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 261.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-86",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 275.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-87",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 288.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-88",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 302.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-89",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 315.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-90",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 329.0, 465.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-91",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-207", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-206", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-206", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-207", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-192", 0 ],
									"destination" : [ "obj-193", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-193", 0 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-194", 0 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-199", 0 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-201", 0 ],
									"destination" : [ "obj-199", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-203", 0 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-204", 0 ],
									"destination" : [ "obj-203", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-206", 0 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-207", 0 ],
									"destination" : [ "obj-208", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-208", 0 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-77", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 1 ],
									"destination" : [ "obj-78", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 2 ],
									"destination" : [ "obj-79", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 3 ],
									"destination" : [ "obj-80", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 4 ],
									"destination" : [ "obj-81", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 5 ],
									"destination" : [ "obj-82", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 6 ],
									"destination" : [ "obj-83", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 7 ],
									"destination" : [ "obj-84", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 8 ],
									"destination" : [ "obj-85", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 9 ],
									"destination" : [ "obj-86", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 10 ],
									"destination" : [ "obj-87", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 11 ],
									"destination" : [ "obj-88", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 12 ],
									"destination" : [ "obj-89", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 13 ],
									"destination" : [ "obj-90", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 14 ],
									"destination" : [ "obj-91", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 0 ],
									"destination" : [ "obj-194", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-71", 0 ],
									"destination" : [ "obj-192", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-72", 0 ],
									"destination" : [ "obj-29", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-73", 0 ],
									"destination" : [ "obj-201", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 0 ],
									"destination" : [ "obj-204", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p ballMapping0",
					"fontname" : "Arial",
					"numinlets" : 0,
					"patching_rect" : [ 105.0, 225.0, 183.0, 20.0 ],
					"numoutlets" : 3,
					"fontsize" : 12.0,
					"outlettype" : [ "", "", "signal" ],
					"id" : "obj-70",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 384.0, 188.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 384.0, 188.0, 640.0, 480.0 ],
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
						"visible" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 4.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 46.0, 194.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 330.0, 55.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 105.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 105.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 345.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line~",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 375.0, 36.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "signal", "bang" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1 20",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 360.0, 41.0, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line 0.",
									"fontname" : "Arial",
									"numinlets" : 3,
									"patching_rect" : [ 45.0, 390.0, 46.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 225.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!/ 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 300.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "float" ],
									"id" : "obj-65"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 135.0, 225.0, 39.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-64"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r ball0",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 45.0, 105.0, 43.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-63"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 254.0, 32.5, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-62"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 225.0, 73.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-61"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0. 0.",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 135.0, 76.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-60"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 90.0, 195.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-59"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.5",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 168.0, 35.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "float" ],
									"id" : "obj-53"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 105.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-68",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 420.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-69",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-62", 0 ],
									"destination" : [ "obj-65", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-15", 0 ],
									"destination" : [ "obj-61", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-53", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 1 ],
									"destination" : [ "obj-59", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-62", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-68", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-69", 0 ],
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
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-61", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 0 ],
									"destination" : [ "obj-53", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 1 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-61", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-63", 0 ],
									"destination" : [ "obj-60", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-64", 0 ],
									"destination" : [ "obj-62", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p receiveIpadBallPositions",
					"fontname" : "Arial",
					"numinlets" : 0,
					"patching_rect" : [ 60.0, 45.0, 151.0, 20.0 ],
					"numoutlets" : 0,
					"fontsize" : 12.0,
					"id" : "obj-48",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 546.0, 117.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 546.0, 117.0, 640.0, 480.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/MultiBall/angle -0.324891 -0.786902 -0.786902 -0.786902 -0.786902",
									"linecount" : 13,
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 300.0, 81.0, 50.0, 184.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p ds",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 255.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-36",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 120.0, 135.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 50.0, 130.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pak 0. 0.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 160.0, 57.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-38"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-23",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 120.0, 45.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-24",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-25",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-38", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-25", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-38", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p ds",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 225.0, 255.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-34",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 120.0, 135.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 50.0, 130.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pak 0. 0.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 160.0, 57.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-38"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-23",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 120.0, 45.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-24",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-25",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-38", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-25", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-38", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p ds",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 165.0, 255.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-35",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 120.0, 135.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 50.0, 130.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pak 0. 0.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 160.0, 57.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-38"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-23",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 120.0, 45.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-24",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-25",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-38", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-25", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-38", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p ds",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 105.0, 255.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-32",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 120.0, 135.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 50.0, 130.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pak 0. 0.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 160.0, 57.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-38"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-23",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 120.0, 45.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-24",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-25",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-38", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-25", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-38", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p ds",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 45.0, 255.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-26",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 120.0, 135.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "append 50",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 67.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line 0.",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 50.0, 130.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pak 0. 0.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 160.0, 57.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-38"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-23",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 120.0, 45.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"id" : "obj-24",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-25",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-38", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-25", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-38", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s ball3",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 225.0, 300.0, 45.0, 20.0 ],
									"numoutlets" : 0,
									"fontsize" : 12.0,
									"id" : "obj-46"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s ball4",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 285.0, 300.0, 45.0, 20.0 ],
									"numoutlets" : 0,
									"fontsize" : 12.0,
									"id" : "obj-42"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s ball2",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 165.0, 300.0, 45.0, 20.0 ],
									"numoutlets" : 0,
									"fontsize" : 12.0,
									"id" : "obj-44"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s ball1",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 105.0, 300.0, 45.0, 20.0 ],
									"numoutlets" : 0,
									"fontsize" : 12.0,
									"id" : "obj-40"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s ball0",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 300.0, 45.0, 20.0 ],
									"numoutlets" : 0,
									"fontsize" : 12.0,
									"id" : "obj-39"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0. 0. 0. 0. 0.",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 225.0, 150.0, 139.0, 20.0 ],
									"numoutlets" : 5,
									"fontsize" : 12.0,
									"outlettype" : [ "float", "float", "float", "float", "float" ],
									"id" : "obj-17"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route /MultiBall/y",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 225.0, 120.0, 99.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-6"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0. 0. 0. 0. 0.",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 150.0, 139.0, 20.0 ],
									"numoutlets" : 5,
									"fontsize" : 12.0,
									"outlettype" : [ "float", "float", "float", "float", "float" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route /MultiBall/x",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 120.0, 99.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "udpreceive 7500",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 45.0, 60.0, 99.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-1"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [ 54.5, 105.0, 234.5, 105.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-26", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 1 ],
									"destination" : [ "obj-32", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 3 ],
									"destination" : [ "obj-34", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 2 ],
									"destination" : [ "obj-35", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 4 ],
									"destination" : [ "obj-36", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-39", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-40", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-46", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-35", 0 ],
									"destination" : [ "obj-44", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 0 ],
									"destination" : [ "obj-42", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-26", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 1 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 3 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 2 ],
									"destination" : [ "obj-35", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 4 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-3", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p dopplershift",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 45.0, 300.0, 161.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-21",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"bglocked" : 0,
						"defrect" : [ 681.0, 142.0, 425.0, 365.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r size",
									"fontname" : "Arial",
									"numinlets" : 0,
									"patching_rect" : [ 285.0, 105.0, 37.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.0,
									"outlettype" : [ "" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "onepole~",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 226.0, 58.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 112.0, 201.0, 33.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapout~ 0.",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 263.0, 65.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tapin~ 2000",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 226.0, 73.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "tapconnect" ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "zl nth 3",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 121.0, 48.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 112.0, 92.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-8",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 1.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 152.0, 32.5, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 0.3438",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 112.0, 176.0, 54.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 32.0, 287.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-11",
									"comment" : "signal out"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 32.0, 58.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-12",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "doppler shift",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 23.0, 22.0, 73.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 59.0, 59.0, 52.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "aed coordinate input",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 139.0, 92.0, 114.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "speed of sound in dry air at 20 °C: 343.8 m/s",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 175.0, 176.0, 242.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-16"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 251.0, 41.5, 251.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-9", 0 ],
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
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p absorption",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"patching_rect" : [ 45.0, 270.0, 79.0, 19.0 ],
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "signal" ],
					"id" : "obj-25",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"bglocked" : 0,
						"defrect" : [ 630.0, 440.0, 316.0, 331.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 11.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "clip 0. 1.",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 119.0, 55.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t 1 1",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 215.0, 38.0, 19.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 63.0, 68.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-4",
									"comment" : "aed coordinate triplet"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 109.0, 193.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "bang" ],
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "filtercoeff~ lowpass",
									"fontname" : "Verdana",
									"numinlets" : 3,
									"patching_rect" : [ 63.0, 238.0, 111.0, 19.0 ],
									"numoutlets" : 5,
									"fontsize" : 10.0,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal" ],
									"id" : "obj-6"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "biquad~",
									"fontname" : "Verdana",
									"numinlets" : 6,
									"patching_rect" : [ 40.0, 267.0, 134.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "signal" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 17000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 140.0, 57.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "!- 18000.",
									"fontname" : "Verdana",
									"numinlets" : 2,
									"patching_rect" : [ 63.0, 161.0, 59.0, 19.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 40.0, 292.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-10",
									"comment" : "filtered signal"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"patching_rect" : [ 40.0, 36.0, 25.0, 25.0 ],
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-11",
									"comment" : "signal in"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "high-frequency absorption by air as function of distance",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 15.0, 6.0, 293.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-12"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "signal in",
									"fontname" : "Verdana",
									"numinlets" : 1,
									"patching_rect" : [ 67.0, 39.0, 53.0, 19.0 ],
									"numoutlets" : 0,
									"fontsize" : 10.0,
									"id" : "obj-13"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 1 ],
									"destination" : [ "obj-6", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-6", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 4 ],
									"destination" : [ "obj-7", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 3 ],
									"destination" : [ "obj-7", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 2 ],
									"destination" : [ "obj-7", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 1 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-7", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontname" : "Arial",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 11.0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.reverberation~ post",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 538.0, 666.0, 243.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 11.595187,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-190"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.decoder~ 7 16",
					"fontname" : "Arial",
					"numinlets" : 15,
					"patching_rect" : [ 896.0, 670.0, 242.0, 20.0 ],
					"numoutlets" : 16,
					"fontsize" : 11.595187,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-26"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"numinlets" : 0,
					"embed" : 1,
					"patching_rect" : [ 46.0, 123.0, 218.0, 87.0 ],
					"numoutlets" : 1,
					"border" : 1,
					"outlettype" : [ "signal" ],
					"id" : "obj-30",
					"name" : "poiu.maxpat",
					"args" : [  ],
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 46.0, 123.0, 218.0, 87.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"defrect" : [ 46.0, 123.0, 218.0, 87.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 1,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "meter~",
									"presentation_rect" : [ 199.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 90.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "float" ],
									"id" : "obj-39"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 128",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 315.0, 85.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-38"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "gain~",
									"presentation_rect" : [ 184.0, 2.0, 12.0, 80.0 ],
									"numinlets" : 2,
									"bgcolor" : [ 0.85098, 0.85098, 0.85098, 1.0 ],
									"patching_rect" : [ 75.0, 360.0, 12.0, 80.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"stripecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"outlettype" : [ "signal", "int" ],
									"knobcolor" : [ 0.482353, 0.482353, 0.482353, 1.0 ],
									"id" : "obj-27"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p attrArgs",
									"presentation_rect" : [ 645.0, 240.0, 379.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 510.0, 300.0, 73.0, 20.0 ],
									"numoutlets" : 5,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "", "", "", "" ],
									"id" : "obj-24",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 154.370789, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-37"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend noise",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 340.0, 130.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 155.0, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend wave",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 235.0, 130.0, 88.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 155.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend loop",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 135.0, 130.0, 83.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route module vol loop file wave freq noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 100.0, 360.0, 20.0 ],
													"numoutlets" : 9,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "", "", "", "", "" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"presentation_rect" : [ 585.0, 120.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-5",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 585.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-6",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 627.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 92.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-8",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 665.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 130.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-12",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 765.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 230.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-16",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 870.0, 315.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 335.0, 235.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-23",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-37", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 2 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 3 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 4 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 5 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 6 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 7 ],
													"destination" : [ "obj-37", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 1 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"presentation_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-20"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "patcherargs @module 0 @vol -20 @loop 0 @file 2 @wave 0 @freq 440 @noise 0 @filter 0",
									"linecount" : 9,
									"presentation_linecount" : 9,
									"presentation_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "", "" ],
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "fourth",
									"presentation_rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 645.0, 385.000031, 110.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-3",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 175.0, 66.741623 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route noise filter",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 25.0, 55.0, 98.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl slice 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 225.0, 215.0, 58.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "filtergraph~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"dbdisplay" : 0,
													"numinlets" : 8,
													"fgcolor" : [ 0.941176, 0.941176, 0.941176, 0.0 ],
													"domain" : [ 0.0, 22050.0 ],
													"bgcolor" : [ 0.941176, 0.941176, 0.941176, 0.4 ],
													"patching_rect" : [ 225.0, 245.0, 140.0, 45.0 ],
													"numoutlets" : 7,
													"presentation" : 1,
													"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
													"id" : "obj-4",
													"range" : [ 0.0, 16.0 ],
													"nfilters" : 1,
													"setfilter" : [ 0, 9, 1, 0, 0, 23.787561, 1.49664, 0.707107, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 80.0, 350.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"logfreq" : 1,
													"id" : "obj-14",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 160.0, 78.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 4.0, 1.666667, 96.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 125.0, 105.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Noise:", "white", ",", "Noise:", "pink" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-10",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 2 1 1.",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 270.0, 86.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pink~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 145.0, 210.0, 40.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "biquad~",
													"fontname" : "Arial",
													"numinlets" : 6,
													"patching_rect" : [ 30.0, 315.0, 86.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 102.0, 2.0, 72.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 225.0, 185.0, 120.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "Filter:", "allpass", ",", "Filter:", "lowpass", ",", "Filter:", "highpass", ",", "Filter:", "bandpass", ",", "Filter:", "bandstop", ",", "Filter:", "peaknotch", ",", "Filter:", "lowshelf", ",", "Filter:", "highshelf", ",", "Filter:", "resonant", ",", "Filter:", "display" ],
													"fontsize" : 11.595187,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-47",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 60.0, 210.0, 47.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "signal" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 360.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 25.0, 15.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 1 ],
													"destination" : [ "obj-47", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-47", 1 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 1 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-9", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"presentation_rect" : [ 4.0, 2.0, 179.0, 20.0 ],
									"rounded" : 0,
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 128.736938, 179.0, 20.0 ],
									"numoutlets" : 3,
									"presentation" : 1,
									"items" : [ "Source:", "Sound", "File", ",", "Source:", "Oscillator", ",", "Source:", "ADC", "(input)", ",", "Source:", "Noise" ],
									"fontsize" : 12.0,
									"outlettype" : [ "int", "", "" ],
									"id" : "obj-6",
									"types" : [  ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : ";\rmax refresh",
									"linecount" : 2,
									"presentation_linecount" : 2,
									"presentation_rect" : [ 70.0, 230.0, 74.0, 32.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 60.0, 80.500031, 32.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p manageDisplay",
									"presentation_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-11",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 50.0, 94.0, 652.0, 443.0 ],
										"bglocked" : 0,
										"defrect" : [ 50.0, 94.0, 652.0, 443.0 ],
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
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1]",
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 3",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox fourth hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 151.0, 96.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox first hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 151.0, 89.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox second hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 151.0, 105.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-29"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 2",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 177.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.0, 100.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "int" ],
													"id" : "obj-33"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox third hidden $1",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 313.0, 151.0, 90.0, 31.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 257.0, 30.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 257.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-32", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1][1]",
										"fontname" : "Arial",
										"default_fontface" : 0,
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "clear, $1 0 1",
									"presentation_rect" : [ 192.454483, 163.77652, 78.0, 18.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 75.0, 240.0, 78.0, 18.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "thispatcher",
									"presentation_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "", "" ],
									"id" : "obj-30",
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"presentation_rect" : [ 80.0, 460.629211, 25.0, 25.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 75.0, 450.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-17",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "matrix~ 4 1 1. @ramp 200",
									"presentation_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"fontname" : "Arial",
									"numinlets" : 4,
									"patching_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "signal", "list" ],
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "third",
									"presentation_rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 520.0, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-26",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 179.481781, 66.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"hidden" : 1,
													"patching_rect" : [ 40.0, 61.0, 74.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Input Channel:",
													"presentation_rect" : [ 5.0, 3.0, 89.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 89.0, 95.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 388.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-9",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 8.0, 25.0, 163.0, 35.0 ],
													"rounded" : 1,
													"numinlets" : 2,
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ],
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"patching_rect" : [ 59.0, 219.0, 137.0, 45.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-4",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "adc~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 153.0, 35.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "signal" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 3.0, 7.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "set $1 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 128.0, 54.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "number",
													"presentation_rect" : [ 95.0, 3.0, 48.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 98.0, 48.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "int", "bang" ],
													"id" : "obj-2"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "second",
									"presentation_rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
									"numinlets" : 1,
									"hidden" : 1,
									"embed" : 1,
									"patching_rect" : [ 394.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-21",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.481781, 65.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "tab",
													"presentation_rect" : [ 50.0, 5.0, 116.0, 16.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 35.0, 280.0, 116.0, 16.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"tabs" : [ "sin", "tri", "rect", "noise" ],
													"id" : "obj-28"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route wave freq",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 54.833344, 110.0, 96.0, 20.0 ],
													"numoutlets" : 3,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-17"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 440",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 195.0, 110.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 1000",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 484.947357, 48.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-36"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 0",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.241211, 453.947357, 37.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 12.0,
													"outlettype" : [ "bang", "" ],
													"id" : "obj-34"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 500",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 275.241211, 397.947357, 87.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-32"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "ms",
													"presentation_rect" : [ 152.907867, 43.0, 27.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 568.241211, 120.947357, 27.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Hz",
													"presentation_rect" : [ 92.0, 22.0, 26.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 215.241211, 66.947357, 26.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-30"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 109.0, 43.0, 45.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 274.333344, 425.947357, 45.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-26",
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Speed:",
													"presentation_rect" : [ 62.907867, 43.0, 50.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 125.947357, 50.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-25"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 46.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 227.241211, 412.947357, 17.0, 17.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-24"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Pulse:",
													"presentation_rect" : [ 2.0, 43.0, 45.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 400.241211, 82.947357, 45.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-22"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 51.241211, 250.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-21"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 268.241211, 89.947357, 81.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-19"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 46.0, 22.0, 47.0, 18.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 67.947357, 47.0, 18.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "float", "bang" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Freq:",
													"presentation_rect" : [ 2.0, 22.0, 39.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 155.241211, 25.947357, 39.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Wave:",
													"presentation_rect" : [ 2.0, 1.0, 46.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 91.241211, 25.947357, 46.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 5 0.2 10 0 100",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 226.241211, 484.947357, 100.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "metro 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 227.241211, 453.947357, 66.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "bang" ],
													"id" : "obj-5"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line~ 1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 167.333344, 519.0, 46.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 571.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1 500",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 51.333344, 319.0, 103.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 216.333313, 330.0, 46.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-11"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "rect~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 195.0, 290.0, 61.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "tri~ 440",
													"fontname" : "Arial",
													"numinlets" : 3,
													"patching_rect" : [ 173.666687, 260.0, 51.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "cycle~ 440",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 152.333344, 224.0, 68.0, 20.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 4 1 1.",
													"fontname" : "Arial",
													"numinlets" : 4,
													"patching_rect" : [ 152.333344, 378.0, 83.0, 20.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.595187,
													"outlettype" : [ "signal", "list" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 152.333344, 615.947388, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"hidden" : 1,
													"patching_rect" : [ 64.241211, 13.947357, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-7", 2 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-7", 3 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 1 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-19", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 1,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-5", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-36", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-7", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "first",
									"presentation_rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
									"numinlets" : 1,
									"embed" : 1,
									"patching_rect" : [ 269.714111, 385.000031, 106.0, 61.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"outlettype" : [ "signal" ],
									"id" : "obj-22",
									"args" : [  ],
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 4.0, 22.0, 178.754517, 65.090912 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 1,
										"default_fontsize" : 10.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 5.0, 5.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 20.0, 62.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 10.0,
													"outlettype" : [ "" ],
													"id" : "obj-18"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 157.0, 44.0, 17.0, 17.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 205.0, 50.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"presentation" : 1,
													"outlettype" : [ "int" ],
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p folderOrSoundFile",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 39.0, 181.0, 100.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-27",
													"patcher" : 													{
														"fileversion" : 1,
														"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"defrect" : [ 25.0, 69.0, 640.0, 480.0 ],
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
														"boxes" : [ 															{
																"box" : 																{
																	"maxclass" : "comment",
																	"text" : "fill the menu if it's a folder",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 108.0, 323.0, 150.0, 20.0 ],
																	"numoutlets" : 0,
																	"fontsize" : 12.0,
																	"id" : "obj-2"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "t s 1",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 100.0, 32.5, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "int" ],
																	"id" : "obj-20"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 211.0, 166.0, 32.5, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 10.0,
																	"outlettype" : [ "int" ],
																	"id" : "obj-19"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "gate 2",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 50.0, 205.0, 38.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "", "" ],
																	"id" : "obj-18"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "message",
																	"text" : "prefix $1, insert 0 Browse..., insert 1 <separator>",
																	"fontname" : "Arial",
																	"numinlets" : 2,
																	"patching_rect" : [ 69.0, 238.0, 270.0, 18.0 ],
																	"numoutlets" : 1,
																	"fontsize" : 12.0,
																	"outlettype" : [ "" ],
																	"id" : "obj-7"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "sel fold",
																	"fontname" : "Arial",
																	"numinlets" : 1,
																	"patching_rect" : [ 211.0, 140.0, 42.0, 18.0 ],
																	"numoutlets" : 2,
																	"fontsize" : 10.0,
																	"outlettype" : [ "bang", "" ],
																	"id" : "obj-4"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 300.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 69.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-23",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 442.0, 170.0, 25.0, 25.0 ],
																	"numinlets" : 0,
																	"patching_rect" : [ 211.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"presentation" : 1,
																	"outlettype" : [ "" ],
																	"id" : "obj-24",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 281.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 50.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-25",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 300.0, 446.0, 25.0, 25.0 ],
																	"numinlets" : 1,
																	"patching_rect" : [ 69.0, 316.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"presentation" : 1,
																	"id" : "obj-26",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 0 ],
																	"destination" : [ "obj-25", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-18", 1 ],
																	"destination" : [ "obj-7", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-19", 0 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 1 ],
																	"destination" : [ "obj-18", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-20", 0 ],
																	"destination" : [ "obj-4", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-23", 0 ],
																	"destination" : [ "obj-18", 1 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-24", 0 ],
																	"destination" : [ "obj-20", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-4", 0 ],
																	"destination" : [ "obj-19", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-7", 0 ],
																	"destination" : [ "obj-26", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
														"globalpatchername" : "",
														"fontname" : "Arial",
														"default_fontface" : 0,
														"fontface" : 0,
														"fontsize" : 12.0,
														"default_fontname" : "Arial",
														"default_fontsize" : 12.0
													}

												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route loop file",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 45.0, 72.0, 18.0 ],
													"numoutlets" : 3,
													"fontsize" : 10.0,
													"outlettype" : [ "", "", "" ],
													"id" : "obj-16"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 2",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 350.0, 55.0, 82.0, 18.0 ],
													"numoutlets" : 2,
													"fontsize" : 10.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-15"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "regexp .*(Browse...) @substitute open",
													"linecount" : 2,
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 125.0, 256.0, 121.0, 34.0 ],
													"numoutlets" : 5,
													"fontsize" : 12.0,
													"outlettype" : [ "", "", "", "", "" ],
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "dropfile",
													"presentation_rect" : [ -5.0, 0.0, 174.683014, 62.542229 ],
													"ignoreclick" : 1,
													"numinlets" : 1,
													"patching_rect" : [ 39.0, 111.0, 100.0, 35.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"border" : 0.0,
													"outlettype" : [ "", "" ],
													"id" : "obj-12",
													"types" : [  ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "prefix ./examples/sounds/, insert 0 Browse..., insert 1 <separator>, $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 148.0, 181.0, 391.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "loop $1",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 205.0, 76.0, 51.0, 18.0 ],
													"numoutlets" : 1,
													"fontsize" : 12.0,
													"outlettype" : [ "" ],
													"id" : "obj-8"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sfplay~",
													"fontname" : "Arial",
													"numinlets" : 2,
													"patching_rect" : [ 20.0, 375.0, 47.0, 19.0 ],
													"numoutlets" : 2,
													"fontsize" : 11.0,
													"outlettype" : [ "signal", "bang" ],
													"id" : "obj-11",
													"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "or Drag a Sound file Here.",
													"presentation_rect" : [ 12.0, 24.0, 161.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 474.0, 91.0, 154.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "File:",
													"presentation_rect" : [ 1.0, 4.0, 34.0, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 470.0, 61.0, 34.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"fontsize" : 12.0,
													"id" : "obj-9"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"fontname" : "Arial",
													"numinlets" : 1,
													"patching_rect" : [ 201.5, 333.0, 78.0, 19.0 ],
													"numoutlets" : 1,
													"fontsize" : 11.0,
													"outlettype" : [ "" ],
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 31.0, 4.0, 142.64183, 20.0 ],
													"fontname" : "Arial",
													"numinlets" : 1,
													"prefix" : "Macintosh HD:/Applications/Max5/examples/sounds/",
													"patching_rect" : [ 148.0, 212.0, 100.0, 20.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"items" : [ "anton.aif", ",", "cello-f2.aif", ",", "cherokee.aif", ",", "drumLoop.aif", ",", "jongly.aif", ",", "rainstick.aif", ",", "sho0630.aif", ",", "vibes-a1.aif" ],
													"fontsize" : 12.0,
													"outlettype" : [ "int", "", "" ],
													"id" : "obj-5",
													"types" : [  ],
													"autopopulate" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "playbar",
													"presentation_rect" : [ 5.620921, 45.0, 154.179749, 15.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 19.0, 76.0, 176.0, 23.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"outlettype" : [ "", "int" ],
													"id" : "obj-2"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 20.0, 415.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"patching_rect" : [ 15.0, 5.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"id" : "obj-3",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"presentation_rect" : [ 5.0, 44.0, 169.683014, 17.683012 ],
													"rounded" : 0,
													"numinlets" : 1,
													"bgcolor" : [ 0.5, 0.5, 0.5, 1.0 ],
													"patching_rect" : [ 433.0, 224.0, 128.0, 128.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-17"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 1 ],
													"destination" : [ "obj-27", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-27", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 3 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 1 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 1 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 1 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-8", 0 ],
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
, 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t f b b",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 420.0, 225.0, 46.0, 18.0 ],
									"numoutlets" : 3,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "bang", "bang" ],
									"id" : "obj-56"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-25"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 165.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "float" ],
									"id" : "obj-57"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "poltocar",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 255.0, 49.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-19"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "65",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 225.0, 32.5, 16.0 ],
									"numoutlets" : 1,
									"fontsize" : 10.0,
									"outlettype" : [ "" ],
									"id" : "obj-18"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 285.0, 195.0, 48.0, 18.0 ],
									"numoutlets" : 2,
									"fontsize" : 10.0,
									"outlettype" : [ "float", "float" ],
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf clear",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 570.0, 180.0, 70.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf frameoval 5 5 135 135 255",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 555.0, 210.0, 183.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-28"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 435.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-58"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 374.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-32"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 315.0, 300.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-33"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontname" : "Arial",
									"numinlets" : 2,
									"patching_rect" : [ 270.0, 304.0, 33.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "int" ],
									"id" : "obj-34"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pack 0 0 0 0 255",
									"fontname" : "Arial",
									"numinlets" : 5,
									"patching_rect" : [ 270.0, 345.0, 96.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-35"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend paintoval",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 270.0, 375.0, 103.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"id" : "obj-36"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 285.0, 135.0, 48.0, 20.0 ],
									"numoutlets" : 2,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "int" ],
									"id" : "obj-37"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 70 70",
									"fontname" : "Arial",
									"numinlets" : 1,
									"patching_rect" : [ 60.0, 45.0, 95.0, 20.0 ],
									"numoutlets" : 1,
									"fontsize" : 12.0,
									"outlettype" : [ "" ],
									"id" : "obj-31"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-30", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 3 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 2 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 4 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-15", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-39", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-37", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-35", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-35", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-35", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-35", 0 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 1 ],
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 0 ],
									"destination" : [ "obj-57", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 2 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-19", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-56", 1 ],
									"destination" : [ "obj-28", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-57", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-35", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 1 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 45.0, 330.0, 243.0, 20.0 ],
					"numoutlets" : 15,
					"fontsize" : 11.595187,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"id" : "obj-35"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 0 ],
					"destination" : [ "obj-5", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 14 ],
					"destination" : [ "obj-26", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 13 ],
					"destination" : [ "obj-26", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 12 ],
					"destination" : [ "obj-26", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 11 ],
					"destination" : [ "obj-26", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 10 ],
					"destination" : [ "obj-26", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 9 ],
					"destination" : [ "obj-26", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 8 ],
					"destination" : [ "obj-26", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 7 ],
					"destination" : [ "obj-26", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 6 ],
					"destination" : [ "obj-26", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 5 ],
					"destination" : [ "obj-26", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 4 ],
					"destination" : [ "obj-26", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 3 ],
					"destination" : [ "obj-26", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 2 ],
					"destination" : [ "obj-26", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 1 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 14 ],
					"destination" : [ "obj-11", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 13 ],
					"destination" : [ "obj-11", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 12 ],
					"destination" : [ "obj-11", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 11 ],
					"destination" : [ "obj-11", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 10 ],
					"destination" : [ "obj-11", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 9 ],
					"destination" : [ "obj-11", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 8 ],
					"destination" : [ "obj-11", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 7 ],
					"destination" : [ "obj-11", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 6 ],
					"destination" : [ "obj-11", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 5 ],
					"destination" : [ "obj-11", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 4 ],
					"destination" : [ "obj-11", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 3 ],
					"destination" : [ "obj-11", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 2 ],
					"destination" : [ "obj-11", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 1 ],
					"destination" : [ "obj-11", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 14 ],
					"destination" : [ "obj-26", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 13 ],
					"destination" : [ "obj-26", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 12 ],
					"destination" : [ "obj-26", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 11 ],
					"destination" : [ "obj-26", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 10 ],
					"destination" : [ "obj-26", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 9 ],
					"destination" : [ "obj-26", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 8 ],
					"destination" : [ "obj-26", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 7 ],
					"destination" : [ "obj-26", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 6 ],
					"destination" : [ "obj-26", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 5 ],
					"destination" : [ "obj-26", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 4 ],
					"destination" : [ "obj-26", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 3 ],
					"destination" : [ "obj-26", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 2 ],
					"destination" : [ "obj-26", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 1 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 384.5, 255.0, 300.0, 255.0, 300.0, 450.0, 324.5, 450.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 1 ],
					"destination" : [ "obj-13", 1 ],
					"hidden" : 0,
					"midpoints" : [ 466.5, 285.0, 466.5, 285.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 1 ],
					"destination" : [ "obj-14", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 2 ],
					"destination" : [ "obj-16", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-76", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 14 ],
					"destination" : [ "obj-190", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 13 ],
					"destination" : [ "obj-190", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 12 ],
					"destination" : [ "obj-190", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 11 ],
					"destination" : [ "obj-190", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 10 ],
					"destination" : [ "obj-190", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 9 ],
					"destination" : [ "obj-190", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 8 ],
					"destination" : [ "obj-190", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 7 ],
					"destination" : [ "obj-190", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 6 ],
					"destination" : [ "obj-190", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 5 ],
					"destination" : [ "obj-190", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 4 ],
					"destination" : [ "obj-190", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 3 ],
					"destination" : [ "obj-190", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 2 ],
					"destination" : [ "obj-190", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 1 ],
					"destination" : [ "obj-190", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-190", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 14 ],
					"destination" : [ "obj-9", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 13 ],
					"destination" : [ "obj-9", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 12 ],
					"destination" : [ "obj-9", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 11 ],
					"destination" : [ "obj-9", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 10 ],
					"destination" : [ "obj-9", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 9 ],
					"destination" : [ "obj-9", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 8 ],
					"destination" : [ "obj-9", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 7 ],
					"destination" : [ "obj-9", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 6 ],
					"destination" : [ "obj-9", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 5 ],
					"destination" : [ "obj-9", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 4 ],
					"destination" : [ "obj-9", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 3 ],
					"destination" : [ "obj-9", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 2 ],
					"destination" : [ "obj-9", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 1 ],
					"destination" : [ "obj-9", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 14 ],
					"destination" : [ "obj-19", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 13 ],
					"destination" : [ "obj-19", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 12 ],
					"destination" : [ "obj-19", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 11 ],
					"destination" : [ "obj-19", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 10 ],
					"destination" : [ "obj-19", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 9 ],
					"destination" : [ "obj-19", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 8 ],
					"destination" : [ "obj-19", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 7 ],
					"destination" : [ "obj-19", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 6 ],
					"destination" : [ "obj-19", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 5 ],
					"destination" : [ "obj-19", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 4 ],
					"destination" : [ "obj-19", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 3 ],
					"destination" : [ "obj-19", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 2 ],
					"destination" : [ "obj-19", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 1 ],
					"destination" : [ "obj-19", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 14 ],
					"destination" : [ "obj-19", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 13 ],
					"destination" : [ "obj-19", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 12 ],
					"destination" : [ "obj-19", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 11 ],
					"destination" : [ "obj-19", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 10 ],
					"destination" : [ "obj-19", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 9 ],
					"destination" : [ "obj-19", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 8 ],
					"destination" : [ "obj-19", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 7 ],
					"destination" : [ "obj-19", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 6 ],
					"destination" : [ "obj-19", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 5 ],
					"destination" : [ "obj-19", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 4 ],
					"destination" : [ "obj-19", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 3 ],
					"destination" : [ "obj-19", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 2 ],
					"destination" : [ "obj-19", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 1 ],
					"destination" : [ "obj-19", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 14 ],
					"destination" : [ "obj-26", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 13 ],
					"destination" : [ "obj-26", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 12 ],
					"destination" : [ "obj-26", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 11 ],
					"destination" : [ "obj-26", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 10 ],
					"destination" : [ "obj-26", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 9 ],
					"destination" : [ "obj-26", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 8 ],
					"destination" : [ "obj-26", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 7 ],
					"destination" : [ "obj-26", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 6 ],
					"destination" : [ "obj-26", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 5 ],
					"destination" : [ "obj-26", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 4 ],
					"destination" : [ "obj-26", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 3 ],
					"destination" : [ "obj-26", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 2 ],
					"destination" : [ "obj-26", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 1 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 14 ],
					"destination" : [ "obj-26", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 13 ],
					"destination" : [ "obj-26", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 12 ],
					"destination" : [ "obj-26", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 11 ],
					"destination" : [ "obj-26", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 10 ],
					"destination" : [ "obj-26", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 9 ],
					"destination" : [ "obj-26", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 8 ],
					"destination" : [ "obj-26", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 7 ],
					"destination" : [ "obj-26", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 6 ],
					"destination" : [ "obj-26", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 5 ],
					"destination" : [ "obj-26", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 4 ],
					"destination" : [ "obj-26", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 3 ],
					"destination" : [ "obj-26", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 2 ],
					"destination" : [ "obj-26", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 1 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-190", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-192", 0 ],
					"destination" : [ "obj-193", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [ 909.5, 255.0, 825.0, 255.0, 825.0, 450.0, 849.5, 450.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 1 ],
					"destination" : [ "obj-22", 1 ],
					"hidden" : 0,
					"midpoints" : [ 991.5, 285.0, 991.5, 285.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 1 ],
					"destination" : [ "obj-23", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 2 ],
					"destination" : [ "obj-27", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-201", 0 ],
					"destination" : [ "obj-199", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-204", 0 ],
					"destination" : [ "obj-203", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-205", 0 ],
					"destination" : [ "obj-206", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 15 ],
					"destination" : [ "obj-28", 15 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 14 ],
					"destination" : [ "obj-28", 14 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 13 ],
					"destination" : [ "obj-28", 13 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 12 ],
					"destination" : [ "obj-28", 12 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 11 ],
					"destination" : [ "obj-28", 11 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 10 ],
					"destination" : [ "obj-28", 10 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 9 ],
					"destination" : [ "obj-28", 9 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 8 ],
					"destination" : [ "obj-28", 8 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 7 ],
					"destination" : [ "obj-28", 7 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 6 ],
					"destination" : [ "obj-28", 6 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 5 ],
					"destination" : [ "obj-28", 5 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 4 ],
					"destination" : [ "obj-28", 4 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 3 ],
					"destination" : [ "obj-28", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 2 ],
					"destination" : [ "obj-28", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 1 ],
					"destination" : [ "obj-28", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 14 ],
					"destination" : [ "obj-17", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 13 ],
					"destination" : [ "obj-17", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 12 ],
					"destination" : [ "obj-17", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 11 ],
					"destination" : [ "obj-17", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 10 ],
					"destination" : [ "obj-17", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 9 ],
					"destination" : [ "obj-17", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 8 ],
					"destination" : [ "obj-17", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 7 ],
					"destination" : [ "obj-17", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 6 ],
					"destination" : [ "obj-17", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 5 ],
					"destination" : [ "obj-17", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 4 ],
					"destination" : [ "obj-17", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 3 ],
					"destination" : [ "obj-17", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 2 ],
					"destination" : [ "obj-17", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 1 ],
					"destination" : [ "obj-17", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 14 ],
					"destination" : [ "obj-190", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 13 ],
					"destination" : [ "obj-190", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 12 ],
					"destination" : [ "obj-190", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 11 ],
					"destination" : [ "obj-190", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 10 ],
					"destination" : [ "obj-190", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 9 ],
					"destination" : [ "obj-190", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 8 ],
					"destination" : [ "obj-190", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 7 ],
					"destination" : [ "obj-190", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 6 ],
					"destination" : [ "obj-190", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 5 ],
					"destination" : [ "obj-190", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 4 ],
					"destination" : [ "obj-190", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 3 ],
					"destination" : [ "obj-190", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 2 ],
					"destination" : [ "obj-190", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 1 ],
					"destination" : [ "obj-190", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-190", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-194", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 14 ],
					"destination" : [ "obj-1", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 13 ],
					"destination" : [ "obj-1", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 12 ],
					"destination" : [ "obj-1", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 11 ],
					"destination" : [ "obj-1", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 10 ],
					"destination" : [ "obj-1", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 9 ],
					"destination" : [ "obj-1", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 8 ],
					"destination" : [ "obj-1", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 7 ],
					"destination" : [ "obj-1", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 6 ],
					"destination" : [ "obj-1", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 5 ],
					"destination" : [ "obj-1", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 4 ],
					"destination" : [ "obj-1", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 3 ],
					"destination" : [ "obj-1", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 2 ],
					"destination" : [ "obj-1", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 1 ],
					"destination" : [ "obj-1", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
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
					"source" : [ "obj-32", 14 ],
					"destination" : [ "obj-34", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 13 ],
					"destination" : [ "obj-34", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 12 ],
					"destination" : [ "obj-34", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 11 ],
					"destination" : [ "obj-34", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 10 ],
					"destination" : [ "obj-34", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 9 ],
					"destination" : [ "obj-34", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 8 ],
					"destination" : [ "obj-34", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 7 ],
					"destination" : [ "obj-34", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 6 ],
					"destination" : [ "obj-34", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 5 ],
					"destination" : [ "obj-34", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 4 ],
					"destination" : [ "obj-34", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 3 ],
					"destination" : [ "obj-34", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 2 ],
					"destination" : [ "obj-34", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 1 ],
					"destination" : [ "obj-34", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 14 ],
					"destination" : [ "obj-34", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 13 ],
					"destination" : [ "obj-34", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 12 ],
					"destination" : [ "obj-34", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 11 ],
					"destination" : [ "obj-34", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 10 ],
					"destination" : [ "obj-34", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 9 ],
					"destination" : [ "obj-34", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 8 ],
					"destination" : [ "obj-34", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 7 ],
					"destination" : [ "obj-34", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 6 ],
					"destination" : [ "obj-34", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 5 ],
					"destination" : [ "obj-34", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 4 ],
					"destination" : [ "obj-34", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 3 ],
					"destination" : [ "obj-34", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 2 ],
					"destination" : [ "obj-34", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 1 ],
					"destination" : [ "obj-34", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 14 ],
					"destination" : [ "obj-26", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 13 ],
					"destination" : [ "obj-26", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 12 ],
					"destination" : [ "obj-26", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 11 ],
					"destination" : [ "obj-26", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 10 ],
					"destination" : [ "obj-26", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 9 ],
					"destination" : [ "obj-26", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 8 ],
					"destination" : [ "obj-26", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 7 ],
					"destination" : [ "obj-26", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 6 ],
					"destination" : [ "obj-26", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 5 ],
					"destination" : [ "obj-26", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 4 ],
					"destination" : [ "obj-26", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 3 ],
					"destination" : [ "obj-26", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 2 ],
					"destination" : [ "obj-26", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 1 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 14 ],
					"destination" : [ "obj-190", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 13 ],
					"destination" : [ "obj-190", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 12 ],
					"destination" : [ "obj-190", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 11 ],
					"destination" : [ "obj-190", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 10 ],
					"destination" : [ "obj-190", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 9 ],
					"destination" : [ "obj-190", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 8 ],
					"destination" : [ "obj-190", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 7 ],
					"destination" : [ "obj-190", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 6 ],
					"destination" : [ "obj-190", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 5 ],
					"destination" : [ "obj-190", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 4 ],
					"destination" : [ "obj-190", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 3 ],
					"destination" : [ "obj-190", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 2 ],
					"destination" : [ "obj-190", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 1 ],
					"destination" : [ "obj-190", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-190", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 14 ],
					"destination" : [ "obj-8", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 13 ],
					"destination" : [ "obj-8", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 12 ],
					"destination" : [ "obj-8", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 11 ],
					"destination" : [ "obj-8", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 10 ],
					"destination" : [ "obj-8", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 9 ],
					"destination" : [ "obj-8", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 8 ],
					"destination" : [ "obj-8", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 7 ],
					"destination" : [ "obj-8", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 6 ],
					"destination" : [ "obj-8", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 5 ],
					"destination" : [ "obj-8", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 4 ],
					"destination" : [ "obj-8", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 3 ],
					"destination" : [ "obj-8", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 2 ],
					"destination" : [ "obj-8", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 1 ],
					"destination" : [ "obj-8", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"midpoints" : [ 639.5, 255.0, 555.0, 255.0, 555.0, 450.0, 579.5, 450.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 1 ],
					"destination" : [ "obj-38", 1 ],
					"hidden" : 0,
					"midpoints" : [ 721.5, 285.0, 721.5, 285.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 1 ],
					"destination" : [ "obj-39", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 2 ],
					"destination" : [ "obj-41", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-38", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 14 ],
					"destination" : [ "obj-190", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 13 ],
					"destination" : [ "obj-190", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 12 ],
					"destination" : [ "obj-190", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 11 ],
					"destination" : [ "obj-190", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 10 ],
					"destination" : [ "obj-190", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 9 ],
					"destination" : [ "obj-190", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 8 ],
					"destination" : [ "obj-190", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 7 ],
					"destination" : [ "obj-190", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 6 ],
					"destination" : [ "obj-190", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 5 ],
					"destination" : [ "obj-190", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 4 ],
					"destination" : [ "obj-190", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 3 ],
					"destination" : [ "obj-190", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 2 ],
					"destination" : [ "obj-190", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 1 ],
					"destination" : [ "obj-190", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-190", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 14 ],
					"destination" : [ "obj-32", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 13 ],
					"destination" : [ "obj-32", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 12 ],
					"destination" : [ "obj-32", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 11 ],
					"destination" : [ "obj-32", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 10 ],
					"destination" : [ "obj-32", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 9 ],
					"destination" : [ "obj-32", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 8 ],
					"destination" : [ "obj-32", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 7 ],
					"destination" : [ "obj-32", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 6 ],
					"destination" : [ "obj-32", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 5 ],
					"destination" : [ "obj-32", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 4 ],
					"destination" : [ "obj-32", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 3 ],
					"destination" : [ "obj-32", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 2 ],
					"destination" : [ "obj-32", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 1 ],
					"destination" : [ "obj-32", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [ 459.5, 51.0, 459.5, 51.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 0 ],
					"destination" : [ "obj-63", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 14 ],
					"destination" : [ "obj-64", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 13 ],
					"destination" : [ "obj-64", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 12 ],
					"destination" : [ "obj-64", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 11 ],
					"destination" : [ "obj-64", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 10 ],
					"destination" : [ "obj-64", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 9 ],
					"destination" : [ "obj-64", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 8 ],
					"destination" : [ "obj-64", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 7 ],
					"destination" : [ "obj-64", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 6 ],
					"destination" : [ "obj-64", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 5 ],
					"destination" : [ "obj-64", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 4 ],
					"destination" : [ "obj-64", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 3 ],
					"destination" : [ "obj-64", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 2 ],
					"destination" : [ "obj-64", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 1 ],
					"destination" : [ "obj-64", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 0 ],
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 14 ],
					"destination" : [ "obj-64", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 13 ],
					"destination" : [ "obj-64", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 12 ],
					"destination" : [ "obj-64", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 11 ],
					"destination" : [ "obj-64", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 10 ],
					"destination" : [ "obj-64", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 9 ],
					"destination" : [ "obj-64", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 8 ],
					"destination" : [ "obj-64", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 7 ],
					"destination" : [ "obj-64", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 6 ],
					"destination" : [ "obj-64", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 5 ],
					"destination" : [ "obj-64", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 4 ],
					"destination" : [ "obj-64", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 3 ],
					"destination" : [ "obj-64", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 2 ],
					"destination" : [ "obj-64", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 1 ],
					"destination" : [ "obj-64", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 0 ],
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 14 ],
					"destination" : [ "obj-26", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 13 ],
					"destination" : [ "obj-26", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 12 ],
					"destination" : [ "obj-26", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 11 ],
					"destination" : [ "obj-26", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 10 ],
					"destination" : [ "obj-26", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 9 ],
					"destination" : [ "obj-26", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 8 ],
					"destination" : [ "obj-26", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 7 ],
					"destination" : [ "obj-26", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 6 ],
					"destination" : [ "obj-26", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 5 ],
					"destination" : [ "obj-26", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 4 ],
					"destination" : [ "obj-26", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 3 ],
					"destination" : [ "obj-26", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 2 ],
					"destination" : [ "obj-26", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 1 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-65", 0 ],
					"destination" : [ "obj-63", 0 ],
					"hidden" : 0,
					"midpoints" : [ 1179.5, 255.0, 1095.0, 255.0, 1095.0, 450.0, 1119.5, 450.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-65", 1 ],
					"destination" : [ "obj-66", 1 ],
					"hidden" : 0,
					"midpoints" : [ 1261.5, 285.0, 1261.5, 285.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-65", 1 ],
					"destination" : [ "obj-67", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-65", 2 ],
					"destination" : [ "obj-69", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-66", 0 ],
					"destination" : [ "obj-69", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-67", 0 ],
					"destination" : [ "obj-66", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-68", 0 ],
					"destination" : [ "obj-67", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 14 ],
					"destination" : [ "obj-190", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 13 ],
					"destination" : [ "obj-190", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 12 ],
					"destination" : [ "obj-190", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 11 ],
					"destination" : [ "obj-190", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 10 ],
					"destination" : [ "obj-190", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 9 ],
					"destination" : [ "obj-190", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 8 ],
					"destination" : [ "obj-190", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 7 ],
					"destination" : [ "obj-190", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 6 ],
					"destination" : [ "obj-190", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 5 ],
					"destination" : [ "obj-190", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 4 ],
					"destination" : [ "obj-190", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 3 ],
					"destination" : [ "obj-190", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 2 ],
					"destination" : [ "obj-190", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 1 ],
					"destination" : [ "obj-190", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 0 ],
					"destination" : [ "obj-190", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 14 ],
					"destination" : [ "obj-62", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 13 ],
					"destination" : [ "obj-62", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 12 ],
					"destination" : [ "obj-62", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 11 ],
					"destination" : [ "obj-62", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 10 ],
					"destination" : [ "obj-62", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 9 ],
					"destination" : [ "obj-62", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 8 ],
					"destination" : [ "obj-62", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 7 ],
					"destination" : [ "obj-62", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 6 ],
					"destination" : [ "obj-62", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 5 ],
					"destination" : [ "obj-62", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 4 ],
					"destination" : [ "obj-62", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 3 ],
					"destination" : [ "obj-62", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 2 ],
					"destination" : [ "obj-62", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 1 ],
					"destination" : [ "obj-62", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 0 ],
					"destination" : [ "obj-62", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 1 ],
					"destination" : [ "obj-21", 1 ],
					"hidden" : 0,
					"midpoints" : [ 196.5, 285.0, 196.5, 285.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 1 ],
					"destination" : [ "obj-25", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [ 114.5, 255.0, 30.0, 255.0, 30.0, 450.0, 54.5, 450.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 2 ],
					"destination" : [ "obj-35", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-72", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 14 ],
					"destination" : [ "obj-1", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 13 ],
					"destination" : [ "obj-1", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 12 ],
					"destination" : [ "obj-1", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 11 ],
					"destination" : [ "obj-1", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 10 ],
					"destination" : [ "obj-1", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 9 ],
					"destination" : [ "obj-1", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 8 ],
					"destination" : [ "obj-1", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 7 ],
					"destination" : [ "obj-1", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 6 ],
					"destination" : [ "obj-1", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 5 ],
					"destination" : [ "obj-1", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 4 ],
					"destination" : [ "obj-1", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 3 ],
					"destination" : [ "obj-1", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 2 ],
					"destination" : [ "obj-1", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 1 ],
					"destination" : [ "obj-1", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 14 ],
					"destination" : [ "obj-11", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 13 ],
					"destination" : [ "obj-11", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 12 ],
					"destination" : [ "obj-11", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 11 ],
					"destination" : [ "obj-11", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 10 ],
					"destination" : [ "obj-11", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 9 ],
					"destination" : [ "obj-11", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 8 ],
					"destination" : [ "obj-11", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 7 ],
					"destination" : [ "obj-11", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 6 ],
					"destination" : [ "obj-11", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 5 ],
					"destination" : [ "obj-11", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 4 ],
					"destination" : [ "obj-11", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 3 ],
					"destination" : [ "obj-11", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 2 ],
					"destination" : [ "obj-11", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 1 ],
					"destination" : [ "obj-11", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 14 ],
					"destination" : [ "obj-190", 14 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 13 ],
					"destination" : [ "obj-190", 13 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 12 ],
					"destination" : [ "obj-190", 12 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 11 ],
					"destination" : [ "obj-190", 11 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 10 ],
					"destination" : [ "obj-190", 10 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 9 ],
					"destination" : [ "obj-190", 9 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 8 ],
					"destination" : [ "obj-190", 8 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 7 ],
					"destination" : [ "obj-190", 7 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 6 ],
					"destination" : [ "obj-190", 6 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 5 ],
					"destination" : [ "obj-190", 5 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 4 ],
					"destination" : [ "obj-190", 4 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 3 ],
					"destination" : [ "obj-190", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 2 ],
					"destination" : [ "obj-190", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 1 ],
					"destination" : [ "obj-190", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 0 ],
					"destination" : [ "obj-190", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
