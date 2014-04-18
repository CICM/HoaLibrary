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
		"rect" : [ 622.0, 54.0, 742.0, 706.0 ],
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
					"id" : "obj-25",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 6,
							"architecture" : "x64"
						}
,
						"rect" : [ 622.0, 80.0, 742.0, 680.0 ],
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
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 1,
											"revision" : 6,
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
									"patching_rect" : [ 422.0, 117.0, 69.0, 19.0 ],
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
									"id" : "obj-17",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 422.0, 147.0, 74.0, 19.0 ],
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
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"frgb" : 0.0,
									"id" : "obj-37",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 456.0, 432.25, 45.0, 32.0 ],
									"text" : "Gains \n(0 - 1)"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"frgb" : 0.0,
									"id" : "obj-36",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 429.0, 239.5, 78.0, 32.0 ],
									"text" : "Delays in ms\n(0 - 5000)"
								}

							}
, 							{
								"box" : 								{
									"channels" : 16,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-29",
									"maxclass" : "hoa.2d.space",
									"minmax" : [ 0.0, 5000.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "list" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 514.0, 239.5, 175.5, 175.5 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "hoa.2d.space",
											"parameter_shortname" : "hoa.2d.space",
											"parameter_type" : 3,
											"parameter_initial_enable" : 1,
											"parameter_initial" : [ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ],
											"parameter_invisible" : 1
										}

									}
,
									"spcolor" : [ 1.0, 0.012904, 0.0, 0.25 ],
									"varname" : "hoa.2d.space"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.74902, 0.74902, 0.74902, 1.0 ],
									"channels" : 16,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-21",
									"maxclass" : "hoa.2d.space",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "list" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 514.0, 432.25, 175.5, 175.5 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "hoa.2d.space[1]",
											"parameter_shortname" : "hoa.2d.space[1]",
											"parameter_type" : 3,
											"parameter_initial_enable" : 1,
											"parameter_initial" : [ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 ],
											"parameter_invisible" : 1
										}

									}
,
									"varname" : "hoa.2d.space[1]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-15",
									"maxclass" : "newobj",
									"numinlets" : 17,
									"numoutlets" : 16,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 9.166687, 396.0, 328.333313, 19.0 ],
									"text" : "hoa.2d.process~ 16 hoa.amp~ planewaves 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 17,
									"numoutlets" : 16,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 9.166687, 339.0, 308.999969, 19.0 ],
									"text" : "hoa.process~ 16 hoa.fx.delay~ planewaves"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 514.0, 13.0, 58.0, 19.0 ],
									"text" : "loadbang"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-11",
									"maxclass" : "hoa.2d.map",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "list", "list", "list" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 514.0, 45.25, 175.5, 175.5 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "hoa.2d.map",
											"parameter_shortname" : "hoa.2d.map",
											"parameter_type" : 3,
											"parameter_initial_enable" : 1,
											"parameter_initial" : [ "_source_preset_data_", "source", 0, 1, -1.131461, 1.400081, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1, 1.636142, 0.846561, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 3, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 4, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 5, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 6, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 7, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 8, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 9, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 10, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 11, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 12, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 13, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 14, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 15, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 16, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 17, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 18, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 19, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 20, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 21, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 22, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 23, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 24, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 25, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 26, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 27, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 28, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 29, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 30, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 31, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 32, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 33, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 34, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 35, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 36, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 37, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 38, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 39, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 40, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 41, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 42, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 43, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 44, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 45, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 46, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 47, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 48, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 49, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 50, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 51, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 52, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 53, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 54, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 55, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 56, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 57, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 58, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 59, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 60, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 61, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 62, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "source", 63, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 1.0, "", "_group_preset_data_", "group", 0, 1, "0 1", 0.2, 0.2, 0.2, 1.0, "", "group", 1, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 2, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 3, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 4, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 5, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 6, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 7, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 8, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 9, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 10, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 11, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 12, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 13, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 14, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 15, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 16, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 17, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 18, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 19, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 20, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 21, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 22, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 23, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 24, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 25, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 26, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 27, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 28, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 29, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 30, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 31, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 32, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 33, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 34, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 35, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 36, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 37, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 38, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 39, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 40, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 41, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 42, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 43, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 44, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 45, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 46, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 47, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 48, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 49, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 50, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 51, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 52, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 53, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 54, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 55, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 56, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 57, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 58, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 59, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 60, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 61, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 62, 0, "", 0.0, 0.0, 0.0, 0.0, "", "group", 63, 0, "", 0.0, 0.0, 0.0, 0.0, "" ],
											"parameter_invisible" : 1
										}

									}
,
									"varname" : "hoa.2d.map"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 279.833313, 117.0, 93.0, 20.0 ],
									"text" : "hoa.soundgrain"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-8",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 9.166687, 117.0, 89.0, 20.0 ],
									"text" : "hoa.soundcoat"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-7",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 15,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 9.166687, 161.0, 289.666626, 19.0 ],
									"saved_object_attributes" : 									{
										"ramp" : 100.0
									}
,
									"text" : "hoa.2d.map~ 7 2"
								}

							}
, 							{
								"box" : 								{
									"args" : [ "@size", 0 ],
									"id" : "obj-25",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpcredit.maxpat",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 8.5, 633.0, 548.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"local" : 1,
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"patching_rect" : [ 18.5, 564.0, 45.0, 45.0 ]
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"id" : "obj-5",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpout_7.maxpat",
									"numinlets" : 15,
									"numoutlets" : 0,
									"patching_rect" : [ 8.5, 484.0, 329.0, 132.0 ]
								}

							}
, 							{
								"box" : 								{
									"args" : [ "@obj-name", "hoa.2d.projector~", "@obj-desc", "An", "ambisonics", "projection", "external" ],
									"id" : "obj-16",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpheader.maxpat",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 8.0, 6.0, 483.0, 56.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1,
									"id" : "obj-18",
									"linecount" : 2,
									"maxclass" : "newobj",
									"numinlets" : 4,
									"numoutlets" : 0,
									"patching_rect" : [ 422.0, 22.5, 52.0, 23.0 ],
									"text" : "bgcolor 0.93 0.93 0.92 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-20",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 8.0, 69.0, 483.0, 33.0 ],
									"text" : "hoa.2d.projector~ discretizes the ambisonic soundfield into an array of channels \nand gives an access to a new sound domain.",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"varname" : "autohelp_top_description[1]"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"border" : 1,
									"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
									"id" : "obj-31",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 8.0, 69.0, 483.0, 33.0 ],
									"rounded" : 0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 16,
									"numoutlets" : 15,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 8.5, 431.0, 329.0, 19.0 ],
									"saved_object_attributes" : 									{
										"ramp" : 20.0
									}
,
									"text" : "hoa.2d.recomposer~ 7 16"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 15,
									"numoutlets" : 16,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 9.166687, 230.0, 289.666626, 19.0 ],
									"text" : "hoa.2d.projector~ 7 16"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"border" : 1,
									"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
									"id" : "obj-6",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 429.0, 239.5, 78.0, 32.0 ],
									"rounded" : 0
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"border" : 1,
									"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
									"id" : "obj-3",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 456.0, 432.25, 45.0, 32.0 ],
									"rounded" : 0
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-14", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 523.5, 235.0, 348.0, 235.0, 348.0, 153.0, 289.333313, 153.0 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"midpoints" : [ 431.5, 138.0, 431.5, 138.0 ],
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-15", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 16 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 523.5, 616.75, 366.75, 616.75, 366.75, 386.0, 328.0, 386.0 ],
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 16 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 523.5, 421.0, 383.0, 421.0, 383.0, 324.0, 308.666656, 324.0 ],
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-5", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-5", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-5", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-5", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-5", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-5", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-5", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-5", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-5", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-5", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-5", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-5", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-5", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-5", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-1", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-1", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-1", 0 ],
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
									"destination" : [ "obj-7", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 20.5, 19.0, 51.0, 20.0 ],
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
					"id" : "obj-26",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 6,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 26.0, 742.0, 680.0 ],
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
					"patching_rect" : [ 71.5, 19.0, 50.0, 20.0 ],
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
		"parameters" : 		{
			"obj-25::obj-11" : [ "hoa.2d.map", "hoa.2d.map", 0 ],
			"obj-25::obj-29" : [ "hoa.2d.space", "hoa.2d.space", 0 ],
			"obj-25::obj-21" : [ "hoa.2d.space[1]", "hoa.2d.space[1]", 0 ]
		}
,
		"dependency_cache" : [ 			{
				"name" : "hoa.helpheader.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.2d.scope~.svg",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/object-palettes",
				"patcherrelativepath" : "../misc/object-palettes",
				"type" : "svg ",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.helpout_7.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others/hoa.helpout",
				"patcherrelativepath" : "../misc/others/hoa.helpout",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.helpcredit.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.soundcoat.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "littlefilter~.maxpat",
				"bootpath" : "/Applications/Max 6.1/patches/docs/tutorial-patchers/msp-tut",
				"patcherrelativepath" : "../../../../../../../../../../../Applications/Max 6.1/patches/docs/tutorial-patchers/msp-tut",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.soundgrain.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.fx.delay~.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/patchers/effects",
				"patcherrelativepath" : "../patchers/effects",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.help.process.infos.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/patchers/helputility",
				"patcherrelativepath" : "../patchers/helputility",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.args.map.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.mode.sel.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.amp~.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/patchers/operators",
				"patcherrelativepath" : "../patchers/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.list.sel.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.2d.projector~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.2d.recomposer~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.2d.scope~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.gain~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.2d.meter~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.2d.decoder~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.2d.map~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.2d.map.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.process~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.in.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.in~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.out~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.thisprocess~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.2d.space.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.connect.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
