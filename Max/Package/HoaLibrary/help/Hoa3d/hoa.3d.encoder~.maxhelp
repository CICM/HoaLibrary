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
		"rect" : [ 100.0, 100.0, 837.0, 718.0 ],
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
						"rect" : [ 100.0, 126.0, 837.0, 692.0 ],
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
									"border" : 0,
									"filename" : "helpargs.js",
									"id" : "obj-17",
									"ignoreclick" : 1,
									"jsarguments" : [ "hoa.3d.encoder~", 20 ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 354.0, 326.0, 151.0, 39.5 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-12",
									"maxclass" : "number~",
									"mode" : 2,
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "float" ],
									"patching_rect" : [ 121.625, 321.5, 56.0, 19.0 ],
									"sig" : 0.0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-8",
									"maxclass" : "number~",
									"mode" : 2,
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "float" ],
									"patching_rect" : [ 262.25, 321.5, 56.0, 19.0 ],
									"sig" : 0.0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 318.25, 293.0, 49.0, 19.0 ],
									"text" : "hoa.pi~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-3",
									"maxclass" : "number~",
									"mode" : 1,
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "float" ],
									"patching_rect" : [ 318.25, 263.0, 56.0, 19.0 ],
									"sig" : 0.0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-47",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 177.625, 228.0, 117.0, 20.0 ],
									"text" : "Azimuth (0 -  2*π) ",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"varname" : "autohelp_top_description[4]"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"border" : 1,
									"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
									"id" : "obj-48",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 177.625, 228.0, 117.0, 20.0 ],
									"rounded" : 0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-44",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 318.25, 228.0, 131.0, 20.0 ],
									"text" : "Elevation (-π/2 -  π/2) ",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"varname" : "autohelp_top_description[2]"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"border" : 1,
									"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
									"id" : "obj-45",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 318.25, 228.0, 131.0, 20.0 ],
									"rounded" : 0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-36",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 177.625, 293.0, 49.0, 19.0 ],
									"text" : "hoa.pi~"
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
									"patching_rect" : [ 177.625, 263.0, 56.0, 19.0 ],
									"sig" : 0.0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-31",
									"maxclass" : "newobj",
									"numinlets" : 20,
									"numoutlets" : 0,
									"patching_rect" : [ 37.0, 655.0, 300.25, 19.0 ],
									"text" : "hoa.dac~ 1:20"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-30",
									"maxclass" : "hoa.3d.scope~",
									"numinlets" : 16,
									"numoutlets" : 0,
									"order" : 3,
									"patching_rect" : [ 375.75, 421.0, 249.0, 249.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-29",
									"maxclass" : "newobj",
									"numinlets" : 16,
									"numoutlets" : 20,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 37.0, 562.0, 300.25, 19.0 ],
									"text" : "hoa.3d.decoder~ 3 20"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.853045, 0.853045, 0.853045, 1.0 ],
									"border" : 1.0,
									"bordercolor" : [ 0.378792, 0.378792, 0.378792, 0.5 ],
									"id" : "obj-6",
									"local" : 1,
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"offgradcolor1" : [ 0.945098, 0.952941, 0.952941, 1.0 ],
									"offgradcolor2" : [ 0.945098, 0.952941, 0.952941, 1.0 ],
									"ongradcolor1" : [ 0.929412, 0.313725, 0.345098, 0.71 ],
									"ongradcolor2" : [ 0.929412, 0.313725, 0.345098, 0.709804 ],
									"patching_rect" : [ 639.0, 625.0, 45.0, 45.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-4",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 405.25, 279.0, 213.0, 33.0 ],
									"text" : "Azimuth and elevation can be set with signal or float values.",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"varname" : "autohelp_top_description[1]"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"border" : 1,
									"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
									"id" : "obj-5",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 405.25, 279.0, 212.0, 33.0 ],
									"rounded" : 0
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-18",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 6.25, 67.5, 483.0, 33.0 ],
									"text" : "hoa.3d.encoder~ creates the spherical harmonics of a signal depending of a given order \n(arg 1), an azimuth and an elevation value given in radians.",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"varname" : "autohelp_top_description[3]"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"border" : 1,
									"bordercolor" : [ 0.75, 0.75, 0.75, 1.0 ],
									"id" : "obj-7",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 6.25, 67.5, 483.0, 33.0 ],
									"rounded" : 0
								}

							}
, 							{
								"box" : 								{
									"args" : [ "@size", 1 ],
									"id" : "obj-25",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpcredit.maxpat",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 498.5, 16.5, 331.0, 35.0 ]
								}

							}
, 							{
								"box" : 								{
									"args" : [ "@obj-name", "hoa.3d.encoder~", "@obj-desc", "A 3D ambisonic encoder" ],
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
									"args" : [ "@module", 0, "@file", 9, "@vol", 100, "@loop", 1 ],
									"border" : 1,
									"id" : "obj-55",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpaudio.maxpat",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 37.0, 115.0, 218.0, 87.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
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
									"patching_rect" : [ 685.0, 74.5, 69.0, 19.0 ],
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
									"id" : "obj-10",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 685.0, 104.5, 74.0, 19.0 ],
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
									"id" : "obj-34",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 16,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 37.0, 346.5, 300.25, 19.0 ],
									"text" : "hoa.3d.encoder~ 3"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-34", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 19 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 19 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 18 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 18 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 17 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 17 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 16 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 16 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-29", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-29", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-29", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-29", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-29", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-29", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-29", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-29", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-29", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-29", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-29", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-29", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-29", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-29", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-29", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-30", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 327.75, 392.75, 615.25, 392.75 ],
									"source" : [ "obj-34", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-30", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 309.0, 392.75, 599.916667, 392.75 ],
									"source" : [ "obj-34", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-30", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 290.25, 392.75, 584.583333, 392.75 ],
									"source" : [ "obj-34", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-30", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 271.5, 392.75, 569.25, 392.75 ],
									"source" : [ "obj-34", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-30", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 252.75, 392.75, 553.916667, 392.75 ],
									"source" : [ "obj-34", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-30", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 234.0, 392.75, 538.583333, 392.75 ],
									"source" : [ "obj-34", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-30", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 215.25, 392.75, 523.25, 392.75 ],
									"source" : [ "obj-34", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-30", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 196.5, 392.75, 507.916667, 392.75 ],
									"source" : [ "obj-34", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-30", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 177.75, 392.75, 492.583333, 392.75 ],
									"source" : [ "obj-34", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-30", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 159.0, 392.75, 477.25, 392.75 ],
									"source" : [ "obj-34", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-30", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 140.25, 392.75, 461.916667, 392.75 ],
									"source" : [ "obj-34", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-30", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 121.5, 392.75, 446.583333, 392.75 ],
									"source" : [ "obj-34", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-30", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 102.75, 392.75, 431.25, 392.75 ],
									"source" : [ "obj-34", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-30", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 84.0, 392.75, 415.916667, 392.75 ],
									"source" : [ "obj-34", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-30", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 65.25, 392.75, 400.583333, 392.75 ],
									"source" : [ "obj-34", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.2, 0.2, 0.2, 1.0 ],
									"destination" : [ "obj-30", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 46.5, 392.75, 385.25, 392.75 ],
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-34", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-37", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 694.5, 95.5, 694.5, 95.5 ],
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-34", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-55", 0 ]
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
						"rect" : [ 0.0, 26.0, 837.0, 692.0 ],
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
				"name" : "hoa.helpaudio.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../../misc/others",
				"type" : "JSON",
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
				"name" : "hoa.helpcredit.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/Max/Package/HoaLibrary/misc/others",
				"patcherrelativepath" : "../../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "helpargs.js",
				"bootpath" : "/Applications/Max 6.1/Cycling '74/help-resources",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max 6.1/Cycling '74/help-resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.3d.encoder~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.connect.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.3d.decoder~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.3d.scope~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.pi~.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
