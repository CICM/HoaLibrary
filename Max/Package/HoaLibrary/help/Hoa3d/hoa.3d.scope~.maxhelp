{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 1,
			"revision" : 7,
			"architecture" : "x64"
		}
,
		"rect" : [ 64.0, 44.0, 911.0, 783.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 11.595187,
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
		"showrootpatcherontab" : 0,
		"showontab" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"color" : [ 0.734694, 0.734694, 0.734694, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 7,
							"architecture" : "x64"
						}
,
						"rect" : [ 64.0, 70.0, 911.0, 757.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 11.595187,
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
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-45",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 41.0, 517.0, 128.0, 19.0 ],
									"text" : "loadmess camera 0. 0."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-38",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 334.0, 129.0, 70.0, 19.0 ],
									"text" : "loadmess 1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-37",
									"maxclass" : "number~",
									"mode" : 1,
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "float" ],
									"patching_rect" : [ 666.785706, 161.0, 56.0, 19.0 ],
									"presentation_rect" : [ 666.0, 158.0, 0.0, 0.0 ],
									"sig" : 0.0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-36",
									"maxclass" : "number~",
									"mode" : 1,
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "float" ],
									"patching_rect" : [ 334.0, 161.0, 56.0, 19.0 ],
									"presentation_rect" : [ 373.392853, 171.0, 0.0, 0.0 ],
									"sig" : 0.92
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-34",
									"maxclass" : "number~",
									"mode" : 1,
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "float" ],
									"patching_rect" : [ 500.392853, 161.0, 56.0, 19.0 ],
									"sig" : 1.51
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-33",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 768.0, 204.0, 70.0, 19.0 ],
									"text" : "loadmess 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-27",
									"items" : [ "basic", ",", "maxRe", ",", "inPhase" ],
									"maxclass" : "umenu",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 768.0, 234.5, 100.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.853045, 0.853045, 0.853045, 1.0 ],
									"border" : 1.0,
									"bordercolor" : [ 0.378792, 0.378792, 0.378792, 0.5 ],
									"id" : "obj-12",
									"local" : 1,
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"offgradcolor1" : [ 0.945098, 0.952941, 0.952941, 1.0 ],
									"offgradcolor2" : [ 0.945098, 0.952941, 0.952941, 1.0 ],
									"ongradcolor1" : [ 0.929412, 0.313725, 0.345098, 0.71 ],
									"ongradcolor2" : [ 0.929412, 0.313725, 0.345098, 0.709804 ],
									"patching_rect" : [ 760.75, 687.71875, 45.0, 45.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 6.25, 67.5, 483.0, 20.0 ],
									"text" : "hoa.3d.scope~ displays spherical harmonics of an ambisonic sound field",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"varname" : "autohelp_top_description[3]"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"border" : 1,
									"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
									"id" : "obj-19",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 6.25, 67.5, 483.0, 20.0 ],
									"rounded" : 0
								}

							}
, 							{
								"box" : 								{
									"args" : [ "@obj-name", "hoa.3d.scope~", "@obj-desc", "A spherical harmonic visualizer" ],
									"id" : "obj-56",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpheader.maxpat",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 6.25, 6.0, 483.0, 56.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1,
									"id" : "obj-57",
									"linecount" : 2,
									"maxclass" : "newobj",
									"numinlets" : 4,
									"numoutlets" : 0,
									"patching_rect" : [ 418.25, 22.5, 52.0, 23.0 ],
									"text" : "bgcolor 0.93 0.93 0.92 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-46",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 1,
											"revision" : 7,
											"architecture" : "x64"
										}
,
										"rect" : [ 413.0, 101.0, 204.0, 214.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-5",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 2,
													"outlettype" : [ "int", "int" ],
													"patching_rect" : [ 85.0, 78.0, 49.0, 20.0 ],
													"text" : "unpack"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-4",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 85.0, 9.0, 60.0, 20.0 ],
													"text" : "loadbang"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-3",
													"maxclass" : "number",
													"numinlets" : 1,
													"numoutlets" : 2,
													"outlettype" : [ "int", "bang" ],
													"parameter_enable" : 0,
													"patching_rect" : [ 145.0, 119.0, 50.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-1",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"patching_rect" : [ 85.0, 41.0, 74.0, 20.0 ],
													"text" : "patcherargs"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-10",
													"maxclass" : "button",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 16.5, 149.0, 20.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"id" : "obj-23",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 2,
													"outlettype" : [ "bang", "" ],
													"patching_rect" : [ 16.5, 119.0, 117.5, 19.0 ],
													"text" : "sel 32"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"id" : "obj-17",
													"maxclass" : "newobj",
													"numinlets" : 0,
													"numoutlets" : 4,
													"outlettype" : [ "int", "int", "int", "int" ],
													"patching_rect" : [ 16.5, 78.0, 59.5, 19.0 ],
													"text" : "key"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-45",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 16.5, 178.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-5", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-45", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-10", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-23", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-17", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-10", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 26.0, 140.0, 26.0, 140.0 ],
													"source" : [ "obj-23", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-4", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-23", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-5", 1 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-3", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-5", 1 ]
												}

											}
 ]
									}
,
									"patching_rect" : [ 516.0, 13.5, 69.0, 19.0 ],
									"saved_object_attributes" : 									{
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
									"text" : "p keysel 32"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-20",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 516.0, 43.5, 74.0, 19.0 ],
									"saved_object_attributes" : 									{
										"nhcolor" : [ 0.0, 0.0, 1.0, 1.0 ],
										"phcolor" : [ 1.0, 0.0, 0.0, 1.0 ],
										"planecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
										"zhcolor" : [ 0.2, 0.2, 0.2, 1.0 ]
									}
,
									"text" : "hoa.connect"
								}

							}
, 							{
								"box" : 								{
									"attr" : "light",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-41",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 439.0, 150.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "nhcolor",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-29",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 278.0, 150.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "style",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-42",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 367.0, 184.0, 19.0 ],
									"text_width" : 49.0
								}

							}
, 							{
								"box" : 								{
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
									"patching_rect" : [ 704.25, 284.0, 50.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-17",
									"maxclass" : "newobj",
									"numinlets" : 50,
									"numoutlets" : 49,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 334.0, 326.0, 358.71875, 19.0 ],
									"text" : "hoa.3d.wider~ 6"
								}

							}
, 							{
								"box" : 								{
									"attr" : "vectors",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-6",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 410.0, 150.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-26",
									"maxclass" : "newobj",
									"numinlets" : 49,
									"numoutlets" : 49,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 334.0, 284.0, 351.785706, 19.0 ],
									"text" : "hoa.3d.optim~ 6 basic"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-1",
									"maxclass" : "hoa.3d.scope~",
									"numinlets" : 49,
									"numoutlets" : 0,
									"order" : 6,
									"patching_rect" : [ 334.0, 374.0, 358.71875, 358.71875 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "sphere",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-4",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 470.0, 150.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "phcolor",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-2",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 249.0, 150.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "order",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-18",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 339.0, 150.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "camera",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-13",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 161.0, 208.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "gain",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-3",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 30.0, 200.0, 204.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-21",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 666.785706, 194.0, 59.0, 19.0 ],
									"text" : "hoa.pi~ 2"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 500.392853, 194.0, 59.0, 19.0 ],
									"text" : "hoa.pi~ 2"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-25",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 49,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 334.0, 240.0, 351.785706, 19.0 ],
									"text" : "hoa.3d.encoder~ 6"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 48 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 48 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 47 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 47 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 46 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 46 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 45 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 45 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 44 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 44 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 43 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 43 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 42 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 42 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 41 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 41 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 40 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 40 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 39 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 39 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 38 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 38 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 37 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 37 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-1", 36 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 36 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 35 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 35 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 34 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 34 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 33 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 33 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 32 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 32 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 31 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 31 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 30 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 30 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 29 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 29 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 28 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 28 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 27 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 27 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 26 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 26 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-1", 25 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 25 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 24 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 24 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 23 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 23 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 22 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 22 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 21 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 21 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 20 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 20 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 19 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 19 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 18 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 18 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 17 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 17 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-1", 16 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 16 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-1", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-1", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-1", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-18", 0 ]
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
									"destination" : [ "obj-25", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-25", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 48 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 48 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 47 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 47 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 46 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 46 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 45 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 45 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 44 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 44 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 43 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 43 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 42 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 42 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 41 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 41 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 40 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 40 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 39 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 39 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 38 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 38 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 37 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 37 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-26", 36 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 36 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 35 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 35 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 34 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 34 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 33 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 33 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 32 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 32 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 31 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 31 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 30 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 30 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 29 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 29 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 28 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 28 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 27 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 27 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 26 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 26 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-26", 25 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 25 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 24 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 24 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 23 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 23 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 22 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 22 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 21 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 21 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 20 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 20 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 19 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 19 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 18 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 18 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 17 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 17 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-26", 16 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 16 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-26", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-26", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-26", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-26", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-26", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 48 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 48 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 47 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 47 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 46 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 46 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 45 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 45 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 44 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 44 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 43 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 43 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 42 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 42 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 41 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 41 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 40 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 40 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 39 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 39 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 38 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 38 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 37 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 37 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-17", 36 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 36 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 35 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 35 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 34 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 34 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 33 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 33 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 32 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 32 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 31 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 31 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 30 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 30 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 29 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 29 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 28 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 28 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 27 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 27 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 26 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 26 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-17", 25 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 25 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 24 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 24 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 23 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 23 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 22 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 22 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 21 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 21 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 20 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 20 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 19 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 19 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 18 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 18 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 17 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 17 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-17", 16 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 16 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-17", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-17", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-17", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-17", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-17", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 818.0, 271.25, 343.5, 271.25 ],
									"source" : [ "obj-27", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 0 ]
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
									"destination" : [ "obj-17", 49 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-31", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-27", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-33", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-25", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-37", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-41", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-42", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-45", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-20", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"midpoints" : [ 525.5, 34.5, 525.5, 34.5 ],
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-6", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 22.0, 27.0, 51.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 11.595187,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 11.595187,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p basic",
					"textcolor" : [ 0.209184, 0.209184, 0.209184, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"color" : [ 0.734694, 0.734694, 0.734694, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-24",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 7,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 26.0, 911.0, 757.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 5.0, 5.0 ],
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
						"showontab" : 1,
						"boxes" : [  ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 73.0, 27.0, 50.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 13.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p ?",
					"textcolor" : [ 0.209184, 0.209184, 0.209184, 1.0 ],
					"varname" : "q_tab"
				}

			}
 ],
		"lines" : [  ],
		"dependency_cache" : [ 			{
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
				"name" : "hoa.3d.encoder~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.pi~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.3d.scope~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.3d.optim~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.3d.wider~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.connect.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
