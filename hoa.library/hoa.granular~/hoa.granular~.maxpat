{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 0,
			"revision" : 5
		}
,
		"rect" : [ 248.0, 172.0, 1107.0, 239.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6.0, 150.0, 78.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 150.0, 60.0, 20.0 ],
					"text" : "Bypass :"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-8",
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 56.0, -60.0, 25.0, 25.0 ],
					"varname" : "granulInlet"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 15.0, 480.0, 32.5, 20.0 ],
					"text" : "+ 2"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-7",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6.0, 120.0, 78.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 120.0, 90.0, 20.0 ],
					"text" : "Rarefaction :"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-6",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6.0, 90.0, 78.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 90.0, 75.0, 20.0 ],
					"text" : "Feedback :"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6.0, 60.0, 78.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 60.0, 75.0, 20.0 ],
					"text" : "Delay Time :"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6.0, 30.0, 78.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 30.0, 75.0, 20.0 ],
					"text" : "Grain Size :"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 0,
							"revision" : 5
						}
,
						"rect" : [ 855.0, 85.0, 724.0, 608.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 10.0,
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
									"addpoints" : [ 0.0, 0.0, 2, 261.446808, 0.0, 2, 566.468079, 0.226667, 0, 1176.51062, 0.546667, 0, 2091.574463, 0.813333, 2, 2919.489258, 0.973333, 0, 3921.702148, 1.0, 0, 4967.489258, 0.973333, 0, 6013.276367, 0.84, 2, 7102.638184, 0.533333, 2, 7712.680664, 0.213333, 2, 8017.702148, 0.0, 2, 8192.0, 0.0, 2 ],
									"domain" : 8192.0,
									"id" : "obj-3",
									"maxclass" : "function",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "float", "", "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 115.0, 252.0, 200.0, 100.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 10.0,
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 21.0, 34.0, 52.0, 18.0 ],
									"text" : "loadbang"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 10.0,
									"id" : "obj-25",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 51.0, 413.0, 78.0, 18.0 ],
									"text" : "peek~ livegrain"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-22",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 21.0, 61.0, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 10.0,
									"id" : "obj-24",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 3,
									"outlettype" : [ "bang", "bang", "int" ],
									"patching_rect" : [ 21.0, 84.0, 48.0, 18.0 ],
									"text" : "uzi 8192"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 10.0,
									"id" : "obj-20",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 52.0, 447.0, 137.0, 18.0 ],
									"text" : "buffer~ livegrain 185.759644"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-24", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-25", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-24", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-24", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-25", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
 ],
						"dependency_cache" : [  ]
					}
,
					"patching_rect" : [ 210.0, 420.0, 53.0, 20.0 ],
					"saved_object_attributes" : 					{
						"fontname" : "Arial",
						"tags" : "",
						"fontface" : 0,
						"default_fontface" : 0,
						"fontsize" : 10.0,
						"globalpatchername" : "",
						"digest" : "",
						"default_fontname" : "Arial",
						"default_fontsize" : 10.0,
						"description" : ""
					}
,
					"text" : "p ligrain"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 15.0, 450.0, 32.5, 20.0 ],
					"text" : "* 2"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 0,
							"revision" : 5
						}
,
						"rect" : [ 548.0, 168.0, 640.0, 480.0 ],
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
									"id" : "obj-8",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 150.0, 255.0, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-6",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 3,
									"outlettype" : [ "bang", "bang", "int" ],
									"patching_rect" : [ 195.0, 300.0, 46.0, 20.0 ],
									"text" : "uzi 51"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 2,
									"outlettype" : [ "int", "int" ],
									"patching_rect" : [ 92.0, 300.0, 59.0, 20.0 ],
									"text" : "split 1 51"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-18",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "bang", "int" ],
									"patching_rect" : [ 65.0, 105.0, 32.5, 20.0 ],
									"text" : "t b i"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 0,
											"revision" : 5
										}
,
										"rect" : [ 581.0, 161.0, 471.0, 145.0 ],
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
													"id" : "obj-1",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 240.0, 90.0, 164.0, 20.0 ],
													"text" : "sprintf script delete outlet%ld"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-65",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 15.0, 75.0, 165.0, 20.0 ],
													"text" : "sprintf script delete granul%d"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-71",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 15.0, 30.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-72",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 15.0, 120.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-72", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-72", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-65", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-71", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-65", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-71", 0 ]
												}

											}
 ],
										"dependency_cache" : [  ]
									}
,
									"patching_rect" : [ 390.0, 375.0, 67.0, 20.0 ],
									"saved_object_attributes" : 									{
										"fontname" : "Arial",
										"tags" : "",
										"fontface" : 0,
										"default_fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"digest" : "",
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"description" : ""
									}
,
									"text" : "p deleteAll"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-73",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 0,
											"revision" : 5
										}
,
										"rect" : [ 535.0, 193.0, 640.0, 480.0 ],
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
													"id" : "obj-6",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 30.0, 285.0, 260.0, 20.0 ],
													"text" : "sprintf script sendbox granul%ld presentation 1"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-5",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 43.5, 255.0, 197.0, 20.0 ],
													"text" : "sprintf script size granul%ld 75 150"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-69",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 302.0, 135.0, 32.5, 20.0 ],
													"text" : "* 75"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-65",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 57.0, 210.0, 547.0, 20.0 ],
													"text" : "sprintf script newdefault granul%ld %ld 0 bpatcher @name hoa.grain @patching_position @args %ld"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-56",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 4,
													"outlettype" : [ "int", "int", "int", "int" ],
													"patching_rect" : [ 30.0, 75.0, 59.5, 20.0 ],
													"text" : "t i i i i"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-71",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 30.0, 15.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-72",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 57.0, 330.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-72", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-5", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-5", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-56", 1 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-56", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-65", 2 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 80.0, 195.0, 594.5, 195.0 ],
													"source" : [ "obj-56", 3 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-65", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-56", 2 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-69", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 80.0, 120.0, 311.5, 120.0 ],
													"source" : [ "obj-56", 3 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-72", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-6", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-72", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-65", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-65", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-69", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-56", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-71", 0 ]
												}

											}
 ],
										"dependency_cache" : [  ]
									}
,
									"patching_rect" : [ 195.0, 375.0, 79.0, 20.0 ],
									"saved_object_attributes" : 									{
										"fontname" : "Arial",
										"tags" : "",
										"fontface" : 0,
										"default_fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"digest" : "",
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"description" : ""
									}
,
									"text" : "p scriptGrain"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-155",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "int", "int" ],
									"patching_rect" : [ 92.0, 345.0, 46.0, 20.0 ],
									"text" : "t i i i"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-134",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 0,
											"revision" : 5
										}
,
										"rect" : [ 540.0, 79.0, 640.0, 480.0 ],
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
													"id" : "obj-2",
													"linecount" : 4,
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 210.0, 120.0, 105.0, 62.0 ],
													"text" : "sprintf script connect granul%ld 0 outlet%ld 0"
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
													"outlettype" : [ "int", "int" ],
													"patching_rect" : [ 110.0, 75.0, 32.5, 20.0 ],
													"text" : "t i i"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-65",
													"linecount" : 4,
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 110.0, 120.0, 85.0, 62.0 ],
													"text" : "sprintf script connect granulInlet 0 granul%d 0"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-71",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 110.0, 40.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-72",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 110.0, 225.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 133.0, 105.0, 305.5, 105.0 ],
													"source" : [ "obj-1", 1 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 119.5, 105.0, 219.5, 105.0 ],
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-65", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-72", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-2", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-72", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-65", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-71", 0 ]
												}

											}
 ],
										"dependency_cache" : [  ]
									}
,
									"patching_rect" : [ 92.0, 375.0, 94.0, 20.0 ],
									"saved_object_attributes" : 									{
										"fontname" : "Arial",
										"tags" : "",
										"fontface" : 0,
										"default_fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"digest" : "",
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"description" : ""
									}
,
									"text" : "p scriptConnect"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-122",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 0,
											"revision" : 5
										}
,
										"rect" : [ 722.0, 155.0, 640.0, 480.0 ],
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
													"id" : "obj-1",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 305.0, 240.0, 38.0, 20.0 ],
													"text" : "- 140"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-69",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 305.0, 205.0, 39.0, 20.0 ],
													"text" : "* 140"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-66",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 50.0, 295.0, 51.0, 20.0 ],
													"text" : "append"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-65",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 50.0, 250.0, 220.0, 20.0 ],
													"text" : "prepend script newobject newobj @text"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-64",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 300.0, 270.0, 333.0, 20.0 ],
													"text" : "sprintf set @patching_position %ld 330 @varname outlet%ld"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-63",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 50.0, 220.0, 74.0, 20.0 ],
													"text" : "tosymbol \" \""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-59",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 49.0, 190.0, 76.0, 20.0 ],
													"text" : "sprintf outlet"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-56",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 3,
													"outlettype" : [ "bang", "int", "int" ],
													"patching_rect" : [ 110.0, 100.0, 46.0, 20.0 ],
													"text" : "t b i i"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-71",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 110.0, 40.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-72",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 50.0, 375.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-64", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-59", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-56", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-64", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-56", 2 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-69", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-56", 1 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-63", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-59", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-65", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-63", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-66", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-64", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-66", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-65", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-72", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-66", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-69", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-56", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-71", 0 ]
												}

											}
 ],
										"dependency_cache" : [  ]
									}
,
									"patching_rect" : [ 285.0, 375.0, 81.0, 20.0 ],
									"saved_object_attributes" : 									{
										"fontname" : "Arial",
										"tags" : "",
										"fontface" : 0,
										"default_fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"digest" : "",
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"description" : ""
									}
,
									"text" : "p scriptOutlet"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-53",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 3,
									"outlettype" : [ "bang", "bang", "int" ],
									"patching_rect" : [ 65.0, 270.0, 46.0, 20.0 ],
									"text" : "uzi 51"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-51",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "int", "int" ],
									"patching_rect" : [ 65.0, 75.0, 73.0, 20.0 ],
									"text" : "maximum 0"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-1",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 65.0, 0.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-3",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 92.0, 435.0, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-122", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-134", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-122", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-155", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-134", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-155", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-155", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-18", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-13", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-51", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-53", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-155", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-6", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-73", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-8", 0 ]
								}

							}
 ],
						"dependency_cache" : [  ]
					}
,
					"patching_rect" : [ 15.0, 510.0, 63.0, 20.0 ],
					"saved_object_attributes" : 					{
						"fontname" : "Arial",
						"tags" : "",
						"fontface" : 0,
						"default_fontface" : 0,
						"fontsize" : 12.0,
						"globalpatchername" : "",
						"digest" : "",
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"description" : ""
					}
,
					"text" : "p scriptAll",
					"varname" : "scriptAll"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-55",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 15.0, 390.0, 60.0, 20.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-48",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 15.0, 540.0, 69.0, 20.0 ],
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
					"text" : "thispatcher"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 15.0, 420.0, 74.0, 20.0 ],
					"text" : "patcherargs"
				}

			}
, 			{
				"box" : 				{
					"border" : 2,
					"id" : "obj-45",
					"ignoreclick" : 1,
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6.0, 0.0, 78.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 0.0, 75.0, 180.0 ]
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-13",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 81.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet1"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 1 ],
					"id" : "obj-17",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 81.0, 0.0, 74.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 75.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul1"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-19",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 140.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet2"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 2 ],
					"id" : "obj-21",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 150.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 150.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul2"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-23",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 280.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet3"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 3 ],
					"id" : "obj-25",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 225.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 225.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul3"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-27",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 420.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet4"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 4 ],
					"id" : "obj-29",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 300.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 300.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul4"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-32",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 560.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet5"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 5 ],
					"id" : "obj-34",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 375.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 375.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul5"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-36",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 700.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet6"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 6 ],
					"id" : "obj-38",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 450.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 450.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul6"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-40",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 840.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet7"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 7 ],
					"id" : "obj-42",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 525.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 525.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul7"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-44",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 980.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet8"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 8 ],
					"id" : "obj-47",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 600.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 600.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul8"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-50",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1120.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet9"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 9 ],
					"id" : "obj-52",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 675.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 675.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul9"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-54",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1260.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet10"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 10 ],
					"id" : "obj-57",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 750.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 750.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul10"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-59",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1400.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet11"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 11 ],
					"id" : "obj-61",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 825.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 825.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul11"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-63",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1540.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet12"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 12 ],
					"id" : "obj-65",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 900.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 900.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul12"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-67",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1680.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet13"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 13 ],
					"id" : "obj-69",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 975.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 975.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul13"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-71",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1820.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet14"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 14 ],
					"id" : "obj-73",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1050.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1050.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul14"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-75",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1960.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet15"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 15 ],
					"id" : "obj-77",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1125.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1125.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul15"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-79",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2100.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet16"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 16 ],
					"id" : "obj-81",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1200.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1200.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul16"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-83",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2240.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet17"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 17 ],
					"id" : "obj-85",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1275.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1275.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul17"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-87",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2380.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet18"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 18 ],
					"id" : "obj-89",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1350.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1350.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul18"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-91",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2520.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet19"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 19 ],
					"id" : "obj-93",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1425.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1425.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul19"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-95",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2660.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet20"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 20 ],
					"id" : "obj-97",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1500.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1500.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul20"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-99",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2800.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet21"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 21 ],
					"id" : "obj-101",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1575.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1575.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul21"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-103",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2940.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet22"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 22 ],
					"id" : "obj-105",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1650.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1650.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul22"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-107",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3080.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet23"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 23 ],
					"id" : "obj-109",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1725.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1725.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul23"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-111",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3220.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet24"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 24 ],
					"id" : "obj-113",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1800.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1800.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul24"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-115",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3360.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet25"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 25 ],
					"id" : "obj-117",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1875.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1875.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul25"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-119",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3500.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet26"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 26 ],
					"id" : "obj-121",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 1950.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 1950.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul26"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-123",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3640.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet27"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 27 ],
					"id" : "obj-125",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2025.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2025.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul27"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-127",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3780.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet28"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 28 ],
					"id" : "obj-129",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2100.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2100.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul28"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-131",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3920.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet29"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 29 ],
					"id" : "obj-133",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2175.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2175.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul29"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-135",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4060.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet30"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 30 ],
					"id" : "obj-137",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2250.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2250.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul30"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-139",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4200.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet31"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 31 ],
					"id" : "obj-141",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2325.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2325.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul31"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-143",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4340.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet32"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 32 ],
					"id" : "obj-145",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2400.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2400.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul32"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-147",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4480.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet33"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 33 ],
					"id" : "obj-149",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2475.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2475.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul33"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-151",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4620.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet34"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 34 ],
					"id" : "obj-153",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2550.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2550.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul34"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-155",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4760.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet35"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 35 ],
					"id" : "obj-157",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2625.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2625.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul35"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-159",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4900.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet36"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 36 ],
					"id" : "obj-161",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2700.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2700.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul36"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-163",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 5040.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet37"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 37 ],
					"id" : "obj-165",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2775.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2775.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul37"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-167",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 5180.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet38"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 38 ],
					"id" : "obj-169",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2850.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2850.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul38"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-171",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 5320.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet39"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 39 ],
					"id" : "obj-173",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 2925.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2925.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul39"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-175",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 5460.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet40"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 40 ],
					"id" : "obj-177",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3000.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3000.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul40"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-179",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 5600.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet41"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 41 ],
					"id" : "obj-181",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3075.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3075.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul41"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-183",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 5740.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet42"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 42 ],
					"id" : "obj-185",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3150.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3150.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul42"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-187",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 5880.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet43"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 43 ],
					"id" : "obj-189",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3225.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3225.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul43"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-191",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6020.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet44"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 44 ],
					"id" : "obj-193",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3300.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3300.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul44"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-195",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6160.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet45"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 45 ],
					"id" : "obj-197",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3375.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3375.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul45"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-199",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6300.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet46"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 46 ],
					"id" : "obj-201",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3450.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3450.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul46"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-203",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6440.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet47"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 47 ],
					"id" : "obj-205",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3525.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3525.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul47"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-207",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6580.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet48"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 48 ],
					"id" : "obj-209",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3600.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3600.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul48"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-211",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6720.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet49"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 49 ],
					"id" : "obj-213",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3675.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3675.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul49"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-215",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6860.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet50"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 50 ],
					"id" : "obj-217",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3750.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3750.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul50"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-219",
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7000.0, 330.0, 25.0, 25.0 ],
					"varname" : "outlet51"
				}

			}
, 			{
				"box" : 				{
					"args" : [ 51 ],
					"id" : "obj-221",
					"maxclass" : "bpatcher",
					"name" : "hoa.grain.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 3825.0, 0.0, 75.0, 181.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 3825.0, 0.0, 75.0, 180.0 ],
					"varname" : "granul51"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-99", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-101", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-103", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-105", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-107", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-109", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-111", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-113", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-115", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-117", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-119", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-121", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-123", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-125", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-127", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-129", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-131", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-133", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-135", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-137", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-139", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-141", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-143", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-145", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-147", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-149", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-151", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-153", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-155", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-157", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-159", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-161", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-163", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-165", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-167", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-169", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-171", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-173", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-175", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-177", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-179", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-181", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-183", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-185", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-187", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-189", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-191", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-193", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-195", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-197", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-199", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-201", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-203", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-205", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-207", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-209", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-211", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-213", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-215", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-217", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-219", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-221", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
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
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-40", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-55", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-57", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-59", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-61", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-65", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-67", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-69", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-71", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-73", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-75", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-77", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-101", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-105", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-113", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-117", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-121", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-125", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-129", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-133", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-137", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-141", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-145", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-149", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-153", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-157", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-161", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-165", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-169", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-173", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-177", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-181", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-185", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-189", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-193", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-197", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-201", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-205", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-209", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-213", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-217", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-221", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-25", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-47", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-57", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-69", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-73", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-77", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-81", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-89", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-93", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-97", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-81", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-85", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-89", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-91", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-93", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-95", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-97", 0 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "hoa.grain.maxpat",
				"bootpath" : "\\Users\\Pierre\\Documents\\GitHub\\CICM-Library\\hoa.library\\hoa.granular~",
				"patcherrelativepath" : "",
				"type" : "JSON",
				"implicit" : 1
			}
 ]
	}

}
