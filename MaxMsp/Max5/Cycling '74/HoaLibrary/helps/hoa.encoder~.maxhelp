{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 93.0, 63.0, 659.0, 709.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 93.0, 63.0, 659.0, 709.0 ],
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
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[2]",
					"text" : "The azimuth position. (0 -  2*pi) can be set with signal or float values",
					"linecount" : 2,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 59.949997, 231.0, 202.0, 34.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-61",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 59.949997, 231.0, 202.0, 33.0 ],
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"numinlets" : 1,
					"rounded" : 15,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-9"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"name" : "hoa.helpheader.maxpat",
					"args" : [ "@obj-name", "hoa.encoder~", "@obj-desc", "An", "ambisonic", "encoder." ],
					"patching_rect" : [ 7.0, 6.0, 483.0, 56.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-56"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "bgcolor 0.93 0.93 0.92 1.",
					"linecount" : 2,
					"fontsize" : 7.180877,
					"patching_rect" : [ 425.0, 22.5, 52.0, 23.0 ],
					"numinlets" : 4,
					"numoutlets" : 0,
					"id" : "obj-57",
					"fontname" : "Arial",
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
					"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"fontsize" : 11.595187,
					"patching_rect" : [ 7.0, 647.5, 497.0, 20.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-58",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 7.0, 647.5, 497.0, 19.0 ],
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"numinlets" : 1,
					"rounded" : 6,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-28"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[1]",
					"text" : "hoa.encoder~ creates the circular harmonics of a signal depending of a given order (arg 1) and a position on a circle (last inlet).",
					"linecount" : 2,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 7.0, 72.0, 463.0, 34.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-60",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 7.0, 72.0, 463.0, 33.0 ],
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"numinlets" : 1,
					"rounded" : 15,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-31"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"name" : "hoa.helpaudio.maxpat",
					"border" : 1,
					"args" : [ "@module", 3, "@noise", 1, "@vol", 80 ],
					"patching_rect" : [ 39.75, 117.0, 218.0, 87.0 ],
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-55",
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "hoa.scope~",
					"fontsize" : 11.595187,
					"patching_rect" : [ 272.5, 330.0, 225.0, 225.0 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"numinlets" : 15,
					"textcolor" : [  ],
					"numoutlets" : 0,
					"order" : 7,
					"id" : "obj-20",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"fontsize" : 11.595187,
					"patching_rect" : [ 368.75, 567.0, 32.5, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-13",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "startwindow",
					"fontsize" : 11.595187,
					"patching_rect" : [ 291.0, 567.0, 72.0, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-7",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.dac~ 1:16",
					"fontsize" : 11.595187,
					"patching_rect" : [ 40.0, 612.0, 221.5, 20.0 ],
					"numinlets" : 16,
					"numoutlets" : 0,
					"id" : "obj-40",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"fontsize" : 11.595187,
					"patching_rect" : [ 39.75, 285.0, 222.199997, 20.0 ],
					"numinlets" : 2,
					"numoutlets" : 15,
					"id" : "obj-34",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.decoder~ 7 16",
					"fontsize" : 12.0,
					"patching_rect" : [ 40.0, 522.0, 221.5, 20.0 ],
					"numinlets" : 15,
					"numoutlets" : 16,
					"id" : "obj-12",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p split-mode",
					"fontsize" : 14.84361,
					"patching_rect" : [ 413.0, 602.0, 91.0, 24.0 ],
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
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
						"rect" : [ 536.0, 60.0, 631.0, 689.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 536.0, 60.0, 631.0, 689.0 ],
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
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[3]",
									"text" : "widen value :",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 272.5, 150.5, 50.0, 34.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-4",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 272.5, 150.5, 44.75, 33.0 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[2]",
									"text" : "hoa.encoder~ works also with float or int for the azimuth position. (0 -  2*pi)",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 299.5, 243.0, 216.0, 34.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-3",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 299.5, 243.0, 216.0, 33.0 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "With split mode, the input are splited by the given order. It could be useful to optimize some process on the order dependant signals.",
									"linecount" : 3,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 9.25, 41.5, 324.0, 48.0 ],
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
									"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
									"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"fontsize" : 11.595187,
									"patching_rect" : [ 7.0, 647.5, 497.0, 20.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-58",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 7.0, 647.5, 497.0, 19.0 ],
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"numinlets" : 1,
									"rounded" : 6,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-28"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"fontsize" : 7.180877,
									"patching_rect" : [ 368.75, 84.0, 52.0, 23.0 ],
									"numinlets" : 4,
									"numoutlets" : 0,
									"id" : "obj-1",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"name" : "hoa.helpaudio.maxpat",
									"border" : 1,
									"args" : [ "@module", 3, "@noise", 1, "@vol", 0 ],
									"patching_rect" : [ 39.75, 113.0, 218.0, 87.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-17",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"fontsize" : 11.595187,
									"patching_rect" : [ 368.75, 25.5, 51.0, 20.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-46",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "bang" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "button",
													"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-10",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
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
, 											{
												"box" : 												{
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
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-45",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [ 59.5, 151.0, 59.5, 151.0 ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [ 59.5, 121.0, 59.5, 121.0 ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-45", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
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
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.connect 7 16",
									"fontsize" : 11.595187,
									"patching_rect" : [ 368.75, 55.5, 99.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-39",
									"fontname" : "Arial",
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.scope~",
									"fontsize" : 11.595187,
									"patching_rect" : [ 272.5, 330.0, 225.0, 225.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 15,
									"textcolor" : [  ],
									"numoutlets" : 0,
									"order" : 7,
									"id" : "obj-20",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1.",
									"fontsize" : 11.595187,
									"patching_rect" : [ 272.5, 160.0, 73.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-16",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : 0.0,
									"maximum" : 1.0,
									"fontsize" : 11.595187,
									"patching_rect" : [ 272.5, 190.0, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"fontsize" : 11.595187,
									"patching_rect" : [ 368.75, 567.0, 32.5, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-13",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "startwindow",
									"fontsize" : 11.595187,
									"patching_rect" : [ 291.0, 567.0, 72.0, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"fontsize" : 11.595187,
									"patching_rect" : [ 40.0, 612.0, 221.5, 20.0 ],
									"numinlets" : 16,
									"numoutlets" : 0,
									"id" : "obj-40",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"patching_rect" : [ 242.5, 250.0, 50.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-38",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 7 hoa.pwider~ pre",
									"fontsize" : 11.595187,
									"patching_rect" : [ 39.75, 237.0, 196.40625, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 8,
									"id" : "obj-36",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7 split",
									"fontsize" : 11.595187,
									"patching_rect" : [ 39.75, 285.0, 221.75, 20.0 ],
									"numinlets" : 9,
									"numoutlets" : 15,
									"id" : "obj-34",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"fontsize" : 12.0,
									"patching_rect" : [ 40.0, 522.0, 221.5, 20.0 ],
									"numinlets" : 15,
									"numoutlets" : 16,
									"id" : "obj-12",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 9.25, 41.5, 324.0, 47.0 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-9"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-40", 15 ],
									"hidden" : 0,
									"midpoints" : [ 300.5, 597.0, 252.0, 597.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [ 282.0, 228.0, 49.25, 228.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-46", 0 ],
									"destination" : [ "obj-39", 0 ],
									"hidden" : 1,
									"midpoints" : [ 378.25, 46.5, 378.25, 46.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-34", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 0 ],
									"destination" : [ "obj-34", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 1 ],
									"destination" : [ "obj-34", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 2 ],
									"destination" : [ "obj-34", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 3 ],
									"destination" : [ "obj-34", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 4 ],
									"destination" : [ "obj-34", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 5 ],
									"destination" : [ "obj-34", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 6 ],
									"destination" : [ "obj-34", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 7 ],
									"destination" : [ "obj-34", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-20", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 49.25, 316.5, 282.0, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 1 ],
									"destination" : [ "obj-20", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 63.732143, 316.5, 296.714294, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 2 ],
									"destination" : [ "obj-20", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 78.214287, 316.5, 311.428558, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 3 ],
									"destination" : [ "obj-20", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 92.696426, 316.5, 326.142853, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 4 ],
									"destination" : [ "obj-20", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 107.178574, 316.5, 340.857147, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 5 ],
									"destination" : [ "obj-20", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 121.660713, 316.5, 355.571442, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 6 ],
									"destination" : [ "obj-20", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 136.142853, 316.5, 370.285706, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 7 ],
									"destination" : [ "obj-20", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 150.625, 316.5, 385.0, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 8 ],
									"destination" : [ "obj-20", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 165.107147, 316.5, 399.714294, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 9 ],
									"destination" : [ "obj-20", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 179.589279, 316.5, 414.428558, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 10 ],
									"destination" : [ "obj-20", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 194.071426, 316.5, 429.142853, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 11 ],
									"destination" : [ "obj-20", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 208.553574, 316.5, 443.857147, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 12 ],
									"destination" : [ "obj-20", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 223.035721, 316.5, 458.571442, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 13 ],
									"destination" : [ "obj-20", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 237.517853, 316.5, 473.285706, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 14 ],
									"destination" : [ "obj-20", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 252.0, 316.5, 488.0, 316.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 1 ],
									"destination" : [ "obj-12", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 2 ],
									"destination" : [ "obj-12", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 3 ],
									"destination" : [ "obj-12", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 4 ],
									"destination" : [ "obj-12", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 5 ],
									"destination" : [ "obj-12", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 6 ],
									"destination" : [ "obj-12", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 7 ],
									"destination" : [ "obj-12", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 8 ],
									"destination" : [ "obj-12", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 9 ],
									"destination" : [ "obj-12", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 10 ],
									"destination" : [ "obj-12", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 11 ],
									"destination" : [ "obj-12", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 12 ],
									"destination" : [ "obj-12", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 13 ],
									"destination" : [ "obj-12", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-34", 14 ],
									"destination" : [ "obj-12", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-36", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-40", 15 ],
									"hidden" : 0,
									"midpoints" : [ 378.25, 597.0, 252.0, 597.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-40", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 1 ],
									"destination" : [ "obj-40", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 2 ],
									"destination" : [ "obj-40", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 3 ],
									"destination" : [ "obj-40", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 4 ],
									"destination" : [ "obj-40", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 5 ],
									"destination" : [ "obj-40", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 6 ],
									"destination" : [ "obj-40", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 7 ],
									"destination" : [ "obj-40", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 8 ],
									"destination" : [ "obj-40", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 9 ],
									"destination" : [ "obj-40", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 10 ],
									"destination" : [ "obj-40", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 11 ],
									"destination" : [ "obj-40", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 12 ],
									"destination" : [ "obj-40", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 13 ],
									"destination" : [ "obj-40", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 14 ],
									"destination" : [ "obj-40", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 15 ],
									"destination" : [ "obj-40", 15 ],
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
						"fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.pi 2.",
					"fontsize" : 11.595187,
					"patching_rect" : [ 401.5, 185.0, 55.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-1",
					"fontname" : "Arial",
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0.1",
					"fontsize" : 11.595187,
					"patching_rect" : [ 327.5, 125.0, 79.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-8",
					"fontname" : "Arial",
					"hidden" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0.",
					"fontsize" : 11.595187,
					"patching_rect" : [ 272.5, 155.0, 73.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-4",
					"fontname" : "Arial",
					"hidden" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p key32",
					"fontsize" : 11.595187,
					"patching_rect" : [ 419.0, 125.0, 51.0, 20.0 ],
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
					"patching_rect" : [ 419.0, 155.0, 99.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-39",
					"fontname" : "Arial",
					"hidden" : 1,
					"saved_object_attributes" : 					{
						"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 11.595187,
					"patching_rect" : [ 272.5, 185.0, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-10",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "+~",
					"fontsize" : 11.595187,
					"patching_rect" : [ 272.5, 245.0, 74.0, 20.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-14",
					"fontname" : "Arial",
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sig~",
					"fontsize" : 11.595187,
					"patching_rect" : [ 272.5, 215.0, 32.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-15",
					"fontname" : "Arial",
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 11.595187,
					"patching_rect" : [ 327.5, 155.0, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-19",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "*~",
					"fontsize" : 11.595187,
					"patching_rect" : [ 327.5, 215.0, 93.0, 20.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-17",
					"fontname" : "Arial",
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "phasor~ 0.1",
					"fontsize" : 11.595187,
					"patching_rect" : [ 327.5, 185.0, 72.0, 20.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-27",
					"fontname" : "Arial",
					"outlettype" : [ "signal" ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-40", 15 ],
					"hidden" : 0,
					"midpoints" : [ 300.5, 597.0, 252.0, 597.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-55", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 1,
					"midpoints" : [ 428.5, 146.0, 428.5, 146.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [ 49.25, 316.5, 282.0, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 1 ],
					"destination" : [ "obj-20", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 63.764286, 316.5, 296.714294, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 2 ],
					"destination" : [ "obj-20", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [ 78.278572, 316.5, 311.428558, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 3 ],
					"destination" : [ "obj-20", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 92.792854, 316.5, 326.142853, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 4 ],
					"destination" : [ "obj-20", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [ 107.307144, 316.5, 340.857147, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 5 ],
					"destination" : [ "obj-20", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 121.821426, 316.5, 355.571442, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 6 ],
					"destination" : [ "obj-20", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [ 136.335709, 316.5, 370.285706, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 7 ],
					"destination" : [ "obj-20", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 150.850006, 316.5, 385.0, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 8 ],
					"destination" : [ "obj-20", 8 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [ 165.364288, 316.5, 399.714294, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 9 ],
					"destination" : [ "obj-20", 9 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 179.878571, 316.5, 414.428558, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 10 ],
					"destination" : [ "obj-20", 10 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [ 194.392853, 316.5, 429.142853, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 11 ],
					"destination" : [ "obj-20", 11 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 208.907135, 316.5, 443.857147, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 12 ],
					"destination" : [ "obj-20", 12 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [ 223.421432, 316.5, 458.571442, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 13 ],
					"destination" : [ "obj-20", 13 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 237.935715, 316.5, 473.285706, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 14 ],
					"destination" : [ "obj-20", 14 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [ 252.449997, 316.5, 488.0, 316.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 1 ],
					"destination" : [ "obj-12", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 2 ],
					"destination" : [ "obj-12", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 3 ],
					"destination" : [ "obj-12", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 4 ],
					"destination" : [ "obj-12", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 5 ],
					"destination" : [ "obj-12", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 6 ],
					"destination" : [ "obj-12", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 7 ],
					"destination" : [ "obj-12", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 8 ],
					"destination" : [ "obj-12", 8 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 9 ],
					"destination" : [ "obj-12", 9 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 10 ],
					"destination" : [ "obj-12", 10 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 11 ],
					"destination" : [ "obj-12", 11 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 12 ],
					"destination" : [ "obj-12", 12 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 13 ],
					"destination" : [ "obj-12", 13 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 14 ],
					"destination" : [ "obj-12", 14 ],
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
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"midpoints" : [ 337.0, 176.0, 337.0, 176.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-14", 1 ],
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
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-34", 1 ],
					"hidden" : 0,
					"midpoints" : [ 282.0, 274.0, 252.449997, 274.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-40", 15 ],
					"hidden" : 0,
					"midpoints" : [ 378.25, 597.0, 252.0, 597.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-40", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 1 ],
					"destination" : [ "obj-40", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 2 ],
					"destination" : [ "obj-40", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 3 ],
					"destination" : [ "obj-40", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 4 ],
					"destination" : [ "obj-40", 4 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 5 ],
					"destination" : [ "obj-40", 5 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 6 ],
					"destination" : [ "obj-40", 6 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 7 ],
					"destination" : [ "obj-40", 7 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 8 ],
					"destination" : [ "obj-40", 8 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 9 ],
					"destination" : [ "obj-40", 9 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 10 ],
					"destination" : [ "obj-40", 10 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 11 ],
					"destination" : [ "obj-40", 11 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 12 ],
					"destination" : [ "obj-40", 12 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 13 ],
					"destination" : [ "obj-40", 13 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 14 ],
					"destination" : [ "obj-40", 14 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 15 ],
					"destination" : [ "obj-40", 15 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-17", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
