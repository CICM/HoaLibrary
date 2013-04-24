{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 258.0, 71.0, 812.0, 556.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 258.0, 71.0, 812.0, 556.0 ],
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
					"maxclass" : "newobj",
					"text" : "loadmess 0",
					"outlettype" : [ "" ],
					"patching_rect" : [ 27.375, 93.0, 70.0, 20.0 ],
					"id" : "obj-1",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 1,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"outlettype" : [ "int" ],
					"patching_rect" : [ 27.375, 123.0, 20.0, 20.0 ],
					"id" : "obj-2",
					"numinlets" : 1,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "normalize 1.",
					"outlettype" : [ "" ],
					"patching_rect" : [ 375.0, 329.0, 74.0, 18.0 ],
					"id" : "obj-6",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "replace",
					"outlettype" : [ "" ],
					"patching_rect" : [ 315.625, 329.0, 49.0, 18.0 ],
					"id" : "obj-9",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "buffer~ hoaIr3 Cistern.wav",
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 315.625, 367.0, 147.0, 20.0 ],
					"id" : "obj-10",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[2]",
					"text" : "Clear the reverb tail",
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"patching_rect" : [ 636.4375, 99.0, 117.5625, 20.0 ],
					"id" : "obj-95",
					"fontname" : "Arial",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"patching_rect" : [ 636.4375, 99.0, 117.5625, 20.0 ],
					"id" : "obj-96",
					"rounded" : 15,
					"shadow" : -1,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p SambaClick",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "list" ],
					"patching_rect" : [ 27.375, 151.0, 238.0, 20.0 ],
					"id" : "obj-92",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 6,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 540.0, 107.0, 797.0, 594.0 ],
						"bglocked" : 0,
						"defrect" : [ 540.0, 107.0, 797.0, 594.0 ],
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
									"text" : "!- 1",
									"outlettype" : [ "int" ],
									"patching_rect" : [ 66.0, 120.0, 32.5, 20.0 ],
									"id" : "obj-30",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "mute~",
									"outlettype" : [ "" ],
									"patching_rect" : [ 64.0, 178.0, 44.0, 20.0 ],
									"id" : "obj-29",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 50.0, 216.0, 357.20871, 20.0 ],
									"id" : "obj-25",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 6,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
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
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pass~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 299.399994, 487.0, 43.0, 20.0 ],
													"id" : "obj-7",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pass~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 229.083679, 487.0, 43.0, 20.0 ],
													"id" : "obj-6",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pass~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 181.083679, 487.0, 43.0, 20.0 ],
													"id" : "obj-5",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pass~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 50.0, 480.0, 43.0, 20.0 ],
													"id" : "obj-4",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pass~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 97.200005, 480.0, 43.0, 20.0 ],
													"id" : "obj-3",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pass~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 132.0, 487.0, 43.0, 20.0 ],
													"id" : "obj-1",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+~ 0.5",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 364.20871, 266.0, 43.0, 20.0 ],
													"id" : "obj-80",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "button",
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 299.399994, 405.0, 20.0, 20.0 ],
													"id" : "obj-78",
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "click~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 299.399994, 458.0, 40.0, 20.0 ],
													"id" : "obj-79",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : ">~ 0.5",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 336.52121, 327.5, 43.0, 20.0 ],
													"id" : "obj-75",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "edge~",
													"outlettype" : [ "bang", "bang" ],
													"patching_rect" : [ 336.52121, 358.5, 43.0, 20.0 ],
													"id" : "obj-76",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"numoutlets" : 2
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "button",
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 229.083679, 392.0, 20.0, 20.0 ],
													"id" : "obj-73",
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "click~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 229.083679, 445.0, 40.0, 20.0 ],
													"id" : "obj-74",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : ">~ 0.75",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 269.521179, 327.5, 50.0, 20.0 ],
													"id" : "obj-70",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "edge~",
													"outlettype" : [ "bang", "bang" ],
													"patching_rect" : [ 269.521179, 358.5, 43.0, 20.0 ],
													"id" : "obj-72",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"numoutlets" : 2
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "%~ 1",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 364.20871, 293.0, 37.0, 20.0 ],
													"id" : "obj-66",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~ 2",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 364.20871, 230.0, 32.5, 20.0 ],
													"id" : "obj-67",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "%~ 1",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 315.083679, 293.0, 37.0, 20.0 ],
													"id" : "obj-65",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~ 2",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 315.083679, 256.0, 32.5, 20.0 ],
													"id" : "obj-60",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : ">~ 0.5",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 206.083679, 250.0, 43.0, 20.0 ],
													"id" : "obj-59",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "edge~",
													"outlettype" : [ "bang", "bang" ],
													"patching_rect" : [ 206.083679, 281.0, 43.0, 20.0 ],
													"id" : "obj-57",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"numoutlets" : 2
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~ 0.7",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 141.0, 271.0, 41.0, 20.0 ],
													"id" : "obj-56",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~ 0.9",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 97.200005, 265.0, 41.0, 20.0 ],
													"id" : "obj-53",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "%~ 1",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 141.0, 234.0, 37.0, 20.0 ],
													"id" : "obj-50",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+~ 0.75",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 141.0, 204.0, 50.0, 20.0 ],
													"id" : "obj-52",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "%~ 1",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 97.200005, 234.0, 37.0, 20.0 ],
													"id" : "obj-48",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+~ 0.375",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 97.200005, 204.0, 56.0, 20.0 ],
													"id" : "obj-47",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "phasor~ 1",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 50.0, 100.0, 62.0, 20.0 ],
													"id" : "obj-38",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "button",
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 181.083679, 378.0, 20.0, 20.0 ],
													"id" : "obj-35",
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "click~",
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 181.083679, 431.0, 40.0, 20.0 ],
													"id" : "obj-2",
													"fontname" : "Arial",
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"numoutlets" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"outlettype" : [ "" ],
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"id" : "obj-18",
													"numinlets" : 0,
													"numoutlets" : 1,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 50.0, 537.0, 25.0, 25.0 ],
													"id" : "obj-19",
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 97.200005, 537.0, 25.0, 25.0 ],
													"id" : "obj-20",
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 141.0, 537.0, 25.0, 25.0 ],
													"id" : "obj-21",
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 181.083679, 537.0, 25.0, 25.0 ],
													"id" : "obj-22",
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 229.083679, 537.0, 25.0, 25.0 ],
													"id" : "obj-23",
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 299.399994, 537.0, 25.0, 25.0 ],
													"id" : "obj-24",
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-21", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-20", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-35", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-47", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-52", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-60", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 0 ],
													"destination" : [ "obj-67", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-19", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-47", 0 ],
													"destination" : [ "obj-48", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-48", 0 ],
													"destination" : [ "obj-53", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-22", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-50", 0 ],
													"destination" : [ "obj-56", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-52", 0 ],
													"destination" : [ "obj-50", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-53", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-56", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-57", 0 ],
													"destination" : [ "obj-35", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 0 ],
													"destination" : [ "obj-57", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-60", 0 ],
													"destination" : [ "obj-65", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-65", 0 ],
													"destination" : [ "obj-59", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-65", 0 ],
													"destination" : [ "obj-70", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-66", 0 ],
													"destination" : [ "obj-75", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-67", 0 ],
													"destination" : [ "obj-80", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-24", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-70", 0 ],
													"destination" : [ "obj-72", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-72", 0 ],
													"destination" : [ "obj-73", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-73", 0 ],
													"destination" : [ "obj-74", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-74", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-75", 0 ],
													"destination" : [ "obj-76", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-76", 0 ],
													"destination" : [ "obj-78", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-78", 0 ],
													"destination" : [ "obj-79", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-79", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-80", 0 ],
													"destination" : [ "obj-66", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontsize" : 12.0,
										"fontname" : "Arial",
										"globalpatchername" : "",
										"fontface" : 0,
										"default_fontface" : 0,
										"fontsize" : 12.0,
										"default_fontname" : "Arial"
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"outlettype" : [ "int" ],
									"patching_rect" : [ 50.0, 16.0, 25.0, 25.0 ],
									"id" : "obj-6",
									"numinlets" : 0,
									"numoutlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "phasor~ 0.1",
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 263.521179, 19.0, 72.0, 20.0 ],
									"id" : "obj-14",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"numinlets" : 2,
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "*~ 0.5",
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 328.0, 128.0, 42.0, 20.0 ],
									"id" : "obj-13",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+~ 1",
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 319.0, 79.0, 35.0, 20.0 ],
									"id" : "obj-12",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number~",
									"outlettype" : [ "signal", "float" ],
									"mode" : 2,
									"patching_rect" : [ 395.0, 102.0, 56.0, 20.0 ],
									"id" : "obj-11",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"numinlets" : 2,
									"sig" : 0.0,
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "triangle~ 0.5",
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 263.521179, 46.0, 77.0, 20.0 ],
									"id" : "obj-10",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend trajectory",
									"outlettype" : [ "" ],
									"patching_rect" : [ 432.0, 236.0, 107.0, 20.0 ],
									"id" : "obj-7",
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 432.0, 182.0, 50.0, 20.0 ],
									"id" : "obj-5",
									"fontname" : "Arial",
									"minimum" : 0.0,
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"maximum" : 1.0,
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.map",
									"outlettype" : [ "list", "list", "list" ],
									"patching_rect" : [ 426.0, 263.0, 300.0, 300.0 ],
									"id" : "obj-1",
									"fontname" : "Arial",
									"textcolor" : [  ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 3,
									"sources_parameters" : [ "source", 0, 0.644201, -0.803824, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.101782, 0.126365, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.364123, 1.056367, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.64573, 0.944006, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -1.094155, -0.069207, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -0.536566, -0.931165, 0, 0.2, 0.2, 0.2, 1.0, "" ],
									"groups_parameters" : [ "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "" ],
									"trajectory_parameters" : [ "slot", 0, "source", 0, -0.211221, -1.013651, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.802714, -0.773475, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.051992, 0.39335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.318937, 1.104502, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.753516, 0.804121, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -1.065211, -0.179557, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 1, "source", 0, -0.211221, -1.013651, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.802714, -0.773475, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.051992, 0.39335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.318937, 1.104502, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.753516, 0.804121, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -1.065211, -0.179557, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 2, "source", 0, -0.211221, -1.013651, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.802714, -0.773475, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.051992, 0.39335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.318937, 1.104502, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.753516, 0.804121, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -1.065211, -0.179557, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 3, "source", 0, -0.211221, -1.013651, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.802714, -0.773475, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 1.051992, 0.39335, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.318937, 1.104502, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.753516, 0.804121, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -1.065211, -0.179557, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 4, "source", 0, -0.081553, -1.032208, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.893945, -0.66594, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.993912, 0.523021, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.176937, 1.135931, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.84901, 0.702552, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -1.034017, -0.312608, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 5, "source", 0, -0.081553, -1.032208, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.893945, -0.66594, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.993912, 0.523021, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.176937, 1.135931, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.84901, 0.702552, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -1.034017, -0.312608, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 6, "source", 0, 0.34662, -0.975683, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.087843, -0.243332, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.694089, 0.882979, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.301847, 1.109294, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -1.061752, 0.295091, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -0.816542, -0.707231, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 7, "source", 0, 0.476074, -0.919487, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.110827, -0.093147, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.567574, 0.96916, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.449885, 1.057946, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -1.092017, 0.147973, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -0.712788, -0.811695, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 8, "source", 0, 0.588354, -0.852023, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.113699, 0.047845, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.440672, 1.033063, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.579855, 0.99268, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -1.101961, 0.008917, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -0.604604, -0.895193, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 9, "source", 0, 0.756838, -0.706612, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 1.077748, 0.284734, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.20973, 1.10337, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.778593, 0.845836, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -1.078411, -0.226775, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -0.399338, -1.003716, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 10, "source", 0, 0.911002, -0.492117, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.970632, 0.548168, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.076278, 1.120532, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.967277, 0.621306, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.985938, -0.492263, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -0.132375, -1.072097, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 11, "source", 0, 0.999499, -0.27038, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.819277, 0.755909, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.330896, 1.073275, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.083867, 0.383246, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.846981, -0.704996, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.116696, -1.073917, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 12, "source", 0, 1.034815, 0.035515, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.560746, 0.96342, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.631899, 0.928502, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.148645, 0.047548, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.602198, -0.922906, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.42736, -0.992109, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 13, "source", 0, 0.967361, 0.369211, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, 0.217975, 1.093207, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.898878, 0.673372, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -1.101977, -0.327556, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, -0.270326, -1.068326, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.726024, -0.799878, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 14, "source", 0, 0.764716, 0.698078, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.197882, 1.097022, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.083131, 0.29705, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.905231, -0.708662, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 0.140055, -1.093061, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.968674, -0.478108, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 15, "source", 0, 0.346242, 0.975818, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.690847, 0.87484, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -1.095492, -0.247605, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.465245, -1.051281, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 0.637959, -0.898557, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 1.079704, 0.033987, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 16, "source", 0, -0.077688, 1.032506, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.985487, 0.520989, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.901959, -0.669239, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, -0.000664, -1.149628, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 0.946697, -0.564058, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.973855, 0.467465, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 17, "source", 0, -0.329452, 0.981613, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.083408, 0.262377, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.70947, -0.870668, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.282342, -1.114419, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 1.056413, -0.31367, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.828822, 0.692799, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 18, "source", 0, -0.637371, 0.816003, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.108967, -0.113161, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.379248, -1.057158, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.637147, -0.956917, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 1.100583, 0.055808, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.550993, 0.929151, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 19, "source", 0, -0.711865, 0.751899, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.093243, -0.217791, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.277311, -1.088352, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.725001, -0.892199, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 1.090334, 0.159902, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.460419, 0.977205, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 20, "source", 0, -0.862706, 0.572574, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -1.016274, -0.45804, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, -0.025483, -1.122836, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.907054, -0.706328, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 1.026456, 0.400979, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.228895, 1.05571, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 21, "source", 0, -0.927063, 0.461147, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.951613, -0.580556, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.113984, -1.117327, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 0.987659, -0.588367, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 0.968795, 0.525199, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, 0.096182, 1.075948, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "", "slot", 22, "source", 0, -0.999499, 0.27038, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 1, -0.819277, -0.755909, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 2, 0.330896, -1.073275, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 3, 1.083867, -0.383246, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 4, 0.846981, 0.704996, 0, 0.2, 0.2, 0.2, 1.0, "", "source", 5, -0.116696, 1.073917, 0, 0.2, 0.2, 0.2, 1.0, "", "group", 0, 6, 0, 1, 2, 3, 4, 5, 0, 0.2, 0.2, 0.2, 1.0, "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 50.0, 546.613525, 25.0, 25.0 ],
									"id" : "obj-86",
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 97.200005, 546.613525, 25.0, 25.0 ],
									"id" : "obj-87",
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 141.0, 546.613525, 25.0, 25.0 ],
									"id" : "obj-88",
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 272.399994, 546.613525, 25.0, 25.0 ],
									"id" : "obj-89",
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 181.083679, 546.613525, 25.0, 25.0 ],
									"id" : "obj-90",
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 229.083679, 546.613525, 25.0, 25.0 ],
									"id" : "obj-91",
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-89", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 1 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-86", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 1 ],
									"destination" : [ "obj-87", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 2 ],
									"destination" : [ "obj-88", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 5 ],
									"destination" : [ "obj-89", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 3 ],
									"destination" : [ "obj-90", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 4 ],
									"destination" : [ "obj-91", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 0 ],
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-30", 0 ],
									"destination" : [ "obj-29", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-30", 0 ],
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
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontsize" : 12.0,
						"fontname" : "Arial",
						"globalpatchername" : "",
						"fontface" : 0,
						"default_fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"outlettype" : [ "" ],
					"patching_rect" : [ 669.5, 129.0, 36.0, 18.0 ],
					"id" : "obj-8",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 375.0, 178.0, 58.0, 20.0 ],
					"id" : "obj-12",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 1,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 1.",
					"outlettype" : [ "" ],
					"patching_rect" : [ 312.0, 99.0, 73.0, 20.0 ],
					"id" : "obj-58",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 1,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0.",
					"outlettype" : [ "" ],
					"patching_rect" : [ 375.5, 99.0, 73.0, 20.0 ],
					"id" : "obj-55",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 1,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 3 hoa.receive~ post @name convolve",
					"linecount" : 2,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 529.0, 212.0, 225.0, 33.0 ],
					"id" : "obj-54",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 7,
					"numoutlets" : 7,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 3 hoa.send~ post @name convolve",
					"linecount" : 2,
					"patching_rect" : [ 27.375, 324.5, 238.0, 33.0 ],
					"id" : "obj-49",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 7,
					"numoutlets" : 0,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"outlettype" : [ "int", "bang" ],
					"patching_rect" : [ 444.8125, 123.0, 50.0, 20.0 ],
					"id" : "obj-34",
					"fontname" : "Arial",
					"minimum" : 1,
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"maximum" : 2,
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend channel",
					"outlettype" : [ "" ],
					"patching_rect" : [ 444.8125, 159.0, 97.0, 20.0 ],
					"id" : "obj-27",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"outlettype" : [ "int", "", "" ],
					"types" : [  ],
					"patching_rect" : [ 552.875, 129.0, 100.0, 20.0 ],
					"id" : "obj-30",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"items" : [ "hoaIr1", ",", "hoaIr2", ",", "hoaIr3" ],
					"numoutlets" : 3
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend buffer",
					"outlettype" : [ "" ],
					"patching_rect" : [ 552.875, 159.0, 86.0, 20.0 ],
					"id" : "obj-33",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 1",
					"outlettype" : [ "" ],
					"patching_rect" : [ 444.8125, 99.0, 70.0, 20.0 ],
					"id" : "obj-37",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 1,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0",
					"outlettype" : [ "" ],
					"patching_rect" : [ 552.875, 99.0, 70.0, 20.0 ],
					"id" : "obj-43",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 1,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "normalize 1.",
					"outlettype" : [ "" ],
					"patching_rect" : [ 375.0, 267.0, 74.0, 18.0 ],
					"id" : "obj-18",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "replace",
					"outlettype" : [ "" ],
					"patching_rect" : [ 315.625, 267.0, 49.0, 18.0 ],
					"id" : "obj-21",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "buffer~ hoaIr2 SmallRoom.wav",
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 315.625, 305.0, 170.0, 20.0 ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 375.5, 123.0, 50.0, 20.0 ],
					"id" : "obj-14",
					"fontname" : "Arial",
					"minimum" : 0.0,
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"maximum" : 1.0,
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 312.0, 123.0, 50.0, 20.0 ],
					"id" : "obj-13",
					"fontname" : "Arial",
					"minimum" : 0.0,
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"maximum" : 1.0,
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "dry $1",
					"outlettype" : [ "" ],
					"patching_rect" : [ 375.5, 159.0, 43.0, 18.0 ],
					"id" : "obj-7",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "wet $1",
					"outlettype" : [ "" ],
					"patching_rect" : [ 312.0, 159.0, 45.0, 18.0 ],
					"id" : "obj-5",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "hoa.scope~",
					"patching_rect" : [ 529.0, 204.0, 225.0, 225.0 ],
					"id" : "obj-51",
					"fontname" : "Arial",
					"textcolor" : [  ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"fontsize" : 11.595187,
					"numinlets" : 7,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.convolve~ 3 @buffer hoaIr @channel 1",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 27.375, 276.0, 238.0, 20.0 ],
					"id" : "obj-4",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 7,
					"numoutlets" : 7,
					"saved_object_attributes" : 					{
						"channel" : 1,
						"buffer" : "hoaIr1",
						"dry" : 0.0,
						"wet" : 1.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "normalize 1.",
					"outlettype" : [ "" ],
					"patching_rect" : [ 375.0, 204.0, 74.0, 18.0 ],
					"id" : "obj-39",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "replace",
					"outlettype" : [ "" ],
					"patching_rect" : [ 315.625, 204.0, 49.0, 18.0 ],
					"id" : "obj-11",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[13]",
					"text" : "Tip : hoa.convolve~ used with a small order is a efficient tool to reduce the CPU usage. At the first order, it computes only three zero latency convolution and allows to output on an infinity of loudspeakers.",
					"linecount" : 3,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"patching_rect" : [ 347.875, 448.0, 406.125, 48.0 ],
					"id" : "obj-71",
					"fontname" : "Arial",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "buffer~ hoaIr1 Chapel.wav",
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 315.625, 242.0, 147.0, 20.0 ],
					"id" : "obj-15",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
					"linecount" : 2,
					"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"patching_rect" : [ 506.375, 16.0, 257.0, 33.0 ],
					"id" : "obj-28",
					"fontname" : "Arial",
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"patching_rect" : [ 506.375, 16.0, 257.0, 32.0 ],
					"id" : "obj-36",
					"rounded" : 6,
					"shadow" : -1,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"patching_rect" : [ 5.0, 4.0, 483.0, 56.0 ],
					"id" : "obj-17",
					"name" : "hoa.helpheader.maxpat",
					"numinlets" : 1,
					"args" : [ "@obj-name", "hoa.convolve~", "@obj-desc", "An", "ambisonics", "zero", "latency", "convolution", "reverberation" ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[1]",
					"text" : "hoa.convolve~ uses time domain and frequency domain filtering to apply reveberation on harmonics dependant signals. The zero latency convolution is optimized with an algorithm based on the Gardner algorithm.",
					"linecount" : 3,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"patching_rect" : [ 5.0, 65.0, 549.0, 48.0 ],
					"id" : "obj-20",
					"fontname" : "Arial",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"patching_rect" : [ 5.0, 65.0, 547.0, 47.0 ],
					"id" : "obj-25",
					"rounded" : 15,
					"shadow" : -1,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"outlettype" : [ "" ],
					"patching_rect" : [ 301.191345, 419.5, 32.5, 18.0 ],
					"id" : "obj-22",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "startwindow",
					"outlettype" : [ "" ],
					"patching_rect" : [ 275.191345, 393.5, 72.0, 18.0 ],
					"id" : "obj-19",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.dac~ 1:2",
					"patching_rect" : [ 27.375, 476.0, 238.0, 20.0 ],
					"id" : "obj-41",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.binaural~ 3 small",
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 27.375, 419.5, 238.0, 20.0 ],
					"id" : "obj-16",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 7,
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p key32",
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 823.375, 9.0, 51.0, 20.0 ],
					"id" : "obj-46",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 0,
					"numoutlets" : 1,
					"hidden" : 1,
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
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
									"id" : "obj-10",
									"numinlets" : 1,
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sel 32",
									"outlettype" : [ "bang", "" ],
									"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
									"id" : "obj-23",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"numinlets" : 2,
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "key",
									"outlettype" : [ "int", "int", "int", "int" ],
									"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
									"id" : "obj-17",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"numinlets" : 0,
									"numoutlets" : 4
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
									"id" : "obj-45",
									"numinlets" : 1,
									"numoutlets" : 0,
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
						"default_fontsize" : 12.0,
						"fontname" : "Arial",
						"globalpatchername" : "",
						"fontface" : 0,
						"default_fontface" : 0,
						"fontsize" : 12.0,
						"default_fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.connect 3 16",
					"patching_rect" : [ 823.375, 33.0, 99.0, 20.0 ],
					"id" : "obj-31",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 0,
					"hidden" : 1,
					"saved_object_attributes" : 					{
						"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.map~ 3 6",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 27.375, 192.5, 238.0, 20.0 ],
					"id" : "obj-23",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 6,
					"numoutlets" : 7
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "bgcolor 0.93 0.93 0.92 1.",
					"linecount" : 2,
					"patching_rect" : [ 424.8125, 20.5, 52.0, 23.0 ],
					"id" : "obj-26",
					"fontname" : "Arial",
					"fontsize" : 7.180877,
					"numinlets" : 4,
					"numoutlets" : 0,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"patching_rect" : [ 347.875, 448.0, 406.125, 47.0 ],
					"id" : "obj-94",
					"rounded" : 15,
					"shadow" : -1,
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 1 ],
					"destination" : [ "obj-41", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [ 384.5, 297.0, 325.125, 297.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-41", 1 ],
					"hidden" : 0,
					"midpoints" : [ 284.691345, 451.0, 255.875, 451.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-92", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-41", 1 ],
					"hidden" : 0,
					"midpoints" : [ 310.691345, 451.0, 255.875, 451.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 6 ],
					"destination" : [ "obj-4", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 5 ],
					"destination" : [ "obj-4", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 4 ],
					"destination" : [ "obj-4", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 3 ],
					"destination" : [ "obj-4", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 2 ],
					"destination" : [ "obj-4", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 1 ],
					"destination" : [ "obj-4", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-4", 6 ],
					"hidden" : 0,
					"midpoints" : [ 454.3125, 190.0, 276.375, 190.0, 276.375, 262.0, 255.875, 262.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 1 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"midpoints" : [ 602.875, 155.0, 563.125, 155.0, 563.125, 156.0, 562.375, 156.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 0 ],
					"destination" : [ "obj-4", 6 ],
					"hidden" : 0,
					"midpoints" : [ 562.375, 190.0, 276.375, 190.0, 276.375, 262.0, 255.875, 262.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 384.5, 232.0, 325.125, 232.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 6 ],
					"destination" : [ "obj-16", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 5 ],
					"destination" : [ "obj-16", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 4 ],
					"destination" : [ "obj-16", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 3 ],
					"destination" : [ "obj-16", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 2 ],
					"destination" : [ "obj-16", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 1 ],
					"destination" : [ "obj-16", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 6 ],
					"destination" : [ "obj-49", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 5 ],
					"destination" : [ "obj-49", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 4 ],
					"destination" : [ "obj-49", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 3 ],
					"destination" : [ "obj-49", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 2 ],
					"destination" : [ "obj-49", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 1 ],
					"destination" : [ "obj-49", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-49", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-31", 0 ],
					"hidden" : 1,
					"midpoints" : [ 832.875, 30.0, 832.875, 30.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-4", 6 ],
					"hidden" : 0,
					"midpoints" : [ 321.5, 190.0, 276.375, 190.0, 276.375, 262.0, 255.875, 262.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 6 ],
					"destination" : [ "obj-51", 6 ],
					"hidden" : 1,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 5 ],
					"destination" : [ "obj-51", 5 ],
					"hidden" : 1,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 4 ],
					"destination" : [ "obj-51", 4 ],
					"hidden" : 1,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 3 ],
					"destination" : [ "obj-51", 3 ],
					"hidden" : 1,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 2 ],
					"destination" : [ "obj-51", 2 ],
					"hidden" : 1,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 1 ],
					"destination" : [ "obj-51", 1 ],
					"hidden" : 1,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 0 ],
					"destination" : [ "obj-51", 0 ],
					"hidden" : 1,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-55", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-58", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 384.5, 359.0, 325.125, 359.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-4", 6 ],
					"hidden" : 0,
					"midpoints" : [ 385.0, 190.0, 276.375, 190.0, 276.375, 262.0, 255.875, 262.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-4", 6 ],
					"hidden" : 0,
					"midpoints" : [ 679.0, 190.0, 276.375, 190.0, 276.375, 261.0, 255.875, 261.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 5 ],
					"destination" : [ "obj-23", 5 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 4 ],
					"destination" : [ "obj-23", 4 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 3 ],
					"destination" : [ "obj-23", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 2 ],
					"destination" : [ "obj-23", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 1 ],
					"destination" : [ "obj-23", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
