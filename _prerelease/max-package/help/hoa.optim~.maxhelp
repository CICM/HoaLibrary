{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 1,
			"revision" : 3,
			"architecture" : "x64"
		}
,
		"rect" : [ 100.0, 100.0, 626.0, 696.0 ],
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
					"id" : "obj-35",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 3,
							"architecture" : "x64"
						}
,
						"rect" : [ 100.0, 126.0, 626.0, 670.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
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
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-22",
									"linecount" : 5,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 340.0, 465.0, 152.0, 74.0 ],
									"text" : "But it's not always true... for example, diffuse sound field don't need optimzation. You should trust your ears !"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"id" : "obj-24",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 340.0, 465.0, 150.0, 74.0 ],
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-17",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 340.0, 274.0, 150.0, 33.0 ],
									"text" : "Optimization \"basic\" has no effect."
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"id" : "obj-18",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 340.0, 274.0, 150.0, 47.0 ],
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-5",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 340.0, 404.0, 150.0, 47.0 ],
									"text" : "\"inPhase\" is used when auditory covers all the circle."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-3",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 340.0, 338.0, 150.0, 47.0 ],
									"text" : "\"maxRe\" is used when auditory is confined to the center of the circle."
								}

							}
, 							{
								"box" : 								{
									"attr" : "optim",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-10",
									"lock" : 1,
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 319.5, 230.0, 170.5, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"args" : [ "@size", 0 ],
									"id" : "obj-2",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpcredit.maxpat",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 632.0, 548.0, 23.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"id" : "obj-47",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 340.0, 404.0, 150.0, 47.0 ],
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"args" : [ "@obj-name", "hoa.optim~", "@obj-desc", "An", "ambisonic", "optimization", "external." ],
									"id" : "obj-20",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpheader.maxpat",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 8.0, 483.0, 56.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1,
									"id" : "obj-21",
									"linecount" : 2,
									"maxclass" : "newobj",
									"numinlets" : 4,
									"numoutlets" : 0,
									"patching_rect" : [ 421.0, 24.5, 52.0, 23.0 ],
									"text" : "bgcolor 0.93 0.93 0.92 1."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-25",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 78.0, 487.0, 33.0 ],
									"text" : "hoa.optim~ weights the circular harmonics signals depending to the ambisonic optimization. It can be \"basic\" for no optimization, \"maxRe\" or \"inPhase\".",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"varname" : "autohelp_top_description[1]"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"id" : "obj-27",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 78.0, 483.0, 34.0 ],
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 15,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 24.0, 230.0, 242.0, 19.0 ],
									"text" : "hoa.encoder~ 7"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-16",
									"maxclass" : "newobj",
									"numinlets" : 15,
									"numoutlets" : 15,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 24.0, 274.0, 242.0, 19.0 ],
									"saved_object_attributes" : 									{
										"optim" : "maxRe"
									}
,
									"text" : "hoa.optim~ 7"
								}

							}
, 							{
								"box" : 								{
									"angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ],
									"channels" : 16,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"id" : "obj-19",
									"loudspeakers" : 16,
									"ls" : 16,
									"ls_angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ],
									"maxclass" : "hoa.meter~",
									"numinlets" : 16,
									"numoutlets" : 2,
									"outlettype" : [ "list", "list" ],
									"patching_rect" : [ 24.0, 342.0, 242.0, 242.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 319.5, 167.0, 55.0, 19.0 ],
									"text" : "hoa.pi 2."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-7",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 247.0, 197.0, 91.5, 19.0 ],
									"text" : "*~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-15",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 247.0, 141.0, 50.0, 19.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-11",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 357.0, 567.0, 32.5, 17.0 ],
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 277.25, 567.0, 72.0, 17.0 ],
									"text" : "startwindow"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-6",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 247.0, 122.0, 79.0, 19.0 ],
									"text" : "loadmess 0.5"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 16,
									"numoutlets" : 0,
									"patching_rect" : [ 24.0, 604.0, 242.0, 19.0 ],
									"text" : "hoa.dac~ 1:16"
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
											"revision" : 3,
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
										"boxes" : [ 											{
												"box" : 												{
													"id" : "obj-10",
													"maxclass" : "button",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ]
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
													"patching_rect" : [ 50.0, 130.0, 41.0, 19.0 ],
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
													"patching_rect" : [ 50.0, 100.0, 59.5, 19.0 ],
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
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
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
													"midpoints" : [ 59.5, 121.0, 59.5, 121.0 ],
													"source" : [ "obj-17", 0 ]
												}

											}
, 											{
												"patchline" : 												{
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
									"patching_rect" : [ 413.0, 118.0, 51.0, 19.0 ],
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
									"text" : "p key32"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-31",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 413.0, 148.0, 99.0, 19.0 ],
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}
,
									"text" : "hoa.connect 7 16"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"id" : "obj-29",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 247.0, 167.0, 72.0, 19.0 ],
									"text" : "phasor~ 0.5"
								}

							}
, 							{
								"box" : 								{
									"args" : [ "@module", 0, "@file", 3 ],
									"border" : 1,
									"id" : "obj-30",
									"maxclass" : "bpatcher",
									"name" : "hoa.helpaudio.maxpat",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 24.0, 129.0, 218.0, 87.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 15,
									"numoutlets" : 16,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 24.0, 311.0, 242.0, 20.0 ],
									"saved_object_attributes" : 									{
										"angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ],
										"autoconnect" : 1,
										"loudspeakers" : 16,
										"ls" : 16,
										"ls_angles" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ],
										"mode" : "ambisonic",
										"pinnaesize" : "small",
										"restitution" : "panning",
										"yls" : 16,
										"zls" : [ 0.0, 22.5, 45.0, 67.5, 90.0, 112.5, 135.0, 157.5, 180.0, 202.5, 225.0, 247.5, 270.0, 292.5, 315.0, 337.5 ]
									}
,
									"text" : "hoa.decoder~ 7"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"id" : "obj-9",
									"maxclass" : "panel",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 340.0, 338.0, 150.0, 47.0 ],
									"rounded" : 15,
									"shadow" : -1
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-16", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 329.0, 261.0, 256.5, 261.0 ],
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 366.5, 592.5, 256.5, 592.5 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-12", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-12", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-12", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-12", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-12", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-12", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-12", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-12", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-12", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-12", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-12", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-12", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-12", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-12", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-12", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-16", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-16", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-16", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-16", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-16", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-16", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-16", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-16", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-16", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-16", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-16", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-16", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-16", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"destination" : [ "obj-16", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"destination" : [ "obj-16", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"midpoints" : [ 422.5, 139.0, 422.5, 139.0 ],
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 286.75, 592.5, 256.5, 592.5 ],
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 12.0, 7.0, 51.0, 20.0 ],
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
					"id" : "obj-36",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 3,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 26.0, 626.0, 670.0 ],
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
					"patching_rect" : [ 63.0, 7.0, 50.0, 20.0 ],
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
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_prerelease/max-package/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.helpheader.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_prerelease/max-package/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.helpcredit.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/_prerelease/max-package/misc/others",
				"patcherrelativepath" : "../misc/others",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.decoder~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.connect.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "hoa.pi.mxo",
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
, 			{
				"name" : "hoa.encoder~.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
