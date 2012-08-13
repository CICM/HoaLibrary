{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 145.0, 47.0, 861.0, 690.0 ],
		"bglocked" : 0,
		"defrect" : [ 145.0, 47.0, 861.0, 690.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 108.0, 317.0, 208.0, 20.0 ],
					"numoutlets" : 15,
					"id" : "obj-29"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.rotate~ 7",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontsize" : 11.595187,
					"numinlets" : 16,
					"fontname" : "Arial",
					"patching_rect" : [ 112.0, 348.0, 221.5, 20.0 ],
					"numoutlets" : 15,
					"id" : "obj-1"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 276.0, 50.0, 20.0 ],
					"numoutlets" : 2,
					"id" : "obj-38"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sig~",
					"outlettype" : [ "signal" ],
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 378.0, 306.0, 32.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-39"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 365.0, 234.0, 50.0, 20.0 ],
					"numoutlets" : 2,
					"id" : "obj-35"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sig~",
					"outlettype" : [ "signal" ],
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 363.0, 264.0, 32.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-32"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"patching_rect" : [ 573.0, 415.0, 45.0, 45.0 ],
					"numoutlets" : 0,
					"id" : "obj-31"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"outlettype" : [ "bang" ],
					"numinlets" : 1,
					"patching_rect" : [ 508.0, 203.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-27"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.connect 7 16",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 507.0, 250.0, 99.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-25"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "scheme 0. 22.5 45. 67.5 90. 112.5 135. 157.5 180. 202.5 225. 247.5 270. 292.5 315.",
					"outlettype" : [ "" ],
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 20.0, 535.0, 444.0, 18.0 ],
					"numoutlets" : 1,
					"id" : "obj-24"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 288.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-23"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 273.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-21"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 258.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-20"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 243.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-19"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 228.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-18"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 213.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-17"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 198.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-16"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 183.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-15"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 168.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-14"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 153.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-13"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 138.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-11"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 123.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-10"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 108.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-8"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 93.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-7"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"outlettype" : [ "float" ],
					"numinlets" : 1,
					"patching_rect" : [ 78.0, 425.0, 12.0, 78.0 ],
					"numoutlets" : 1,
					"id" : "obj-6"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"varname" : "decode",
					"text" : "hoa.decoder~ 7 16",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontsize" : 12.0,
					"numinlets" : 15,
					"fontname" : "Arial",
					"patching_rect" : [ 76.0, 379.0, 221.5, 20.0 ],
					"numoutlets" : 16,
					"id" : "obj-12"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"name" : "AudioInput",
					"outlettype" : [ "signal" ],
					"embed" : 1,
					"args" : [  ],
					"numinlets" : 0,
					"patching_rect" : [ 70.0, 97.0, 345.0, 122.0 ],
					"numoutlets" : 1,
					"id" : "obj-74",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 70.0, 97.0, 345.0, 122.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"defrect" : [ 70.0, 97.0, 345.0, 122.0 ],
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
									"maxclass" : "bpatcher",
									"varname" : "noiso",
									"name" : "Noise",
									"outlettype" : [ "signal" ],
									"embed" : 1,
									"args" : [  ],
									"presentation_rect" : [ 105.0, 0.0, 240.0, 120.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 270.0, 0.0, 240.0, 120.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"id" : "obj-6",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 105.0, 0.0, 240.0, 120.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 105.0, 0.0, 240.0, 120.0 ],
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
													"maxclass" : "inlet",
													"outlettype" : [ "" ],
													"numinlets" : 0,
													"patching_rect" : [ 330.0, 90.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"id" : "obj-19",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 75.0, 195.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p noisy",
													"outlettype" : [ "signal" ],
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 75.0, 135.0, 47.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-24",
													"patcher" : 													{
														"fileversion" : 1,
														"rect" : [ 29.0, 67.0, 640.0, 480.0 ],
														"bglocked" : 0,
														"defrect" : [ 29.0, 67.0, 640.0, 480.0 ],
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
																	"maxclass" : "newobj",
																	"text" : "noise~",
																	"outlettype" : [ "signal" ],
																	"fontsize" : 11.595187,
																	"numinlets" : 1,
																	"fontname" : "Arial",
																	"patching_rect" : [ 50.0, 100.0, 43.0, 20.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-68"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "biquad~",
																	"outlettype" : [ "signal" ],
																	"fontsize" : 11.595187,
																	"numinlets" : 6,
																	"fontname" : "Arial",
																	"patching_rect" : [ 215.0, 130.0, 79.0, 20.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-69"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"outlettype" : [ "list" ],
																	"numinlets" : 0,
																	"patching_rect" : [ 227.0, 40.0, 25.0, 25.0 ],
																	"numoutlets" : 1,
																	"id" : "obj-16",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"numinlets" : 1,
																	"patching_rect" : [ 215.0, 210.0, 25.0, 25.0 ],
																	"numoutlets" : 0,
																	"id" : "obj-20",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-16", 0 ],
																	"destination" : [ "obj-69", 1 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-68", 0 ],
																	"destination" : [ "obj-69", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
, 															{
																"patchline" : 																{
																	"source" : [ "obj-69", 0 ],
																	"destination" : [ "obj-20", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
														"fontface" : 0,
														"globalpatchername" : "",
														"fontsize" : 12.0,
														"default_fontface" : 0,
														"default_fontname" : "Arial",
														"fontname" : "Arial",
														"default_fontsize" : 12.0
													}

												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 11.595187,
													"items" : [ "display", ",", "lowpass", ",", "highpass", ",", "bandpass", ",", "bandstop", ",", "peaknotch", ",", "lowshelf", ",", "highshelf", ",", "resonant", ",", "allpass" ],
													"numinlets" : 1,
													"types" : [  ],
													"fontname" : "Arial",
													"patching_rect" : [ 12.0, 7.5, 88.0, 20.0 ],
													"numoutlets" : 3,
													"id" : "obj-47"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "filtergraph~",
													"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
													"domain" : [ 0.0, 22050.0 ],
													"fontsize" : 8.998901,
													"autoout" : 1,
													"markercolor" : [ 0.509804, 0.509804, 0.509804, 1.0 ],
													"bwidthcolor" : [ 0.462745, 0.47451, 0.65098, 1.0 ],
													"hbwidthcolor" : [ 0.823529, 0.290196, 0.211765, 1.0 ],
													"bgcolor" : [ 0.913725, 0.913725, 1.0, 1.0 ],
													"numinlets" : 8,
													"hcurvecolor" : [ 1.0, 0.086275, 0.086275, 1.0 ],
													"patching_rect" : [ 12.0, 27.5, 198.0, 77.5 ],
													"fgcolor" : [ 0.756863, 0.756863, 1.0, 1.0 ],
													"numoutlets" : 7,
													"id" : "obj-81",
													"logfreq" : 0,
													"nfilters" : 1,
													"setfilter" : [ 0, 1, 0, 0, 0, 9020.454102, 1.0, 0.5, 0.0001, 22050.0, 0.0001, 16.0, 0.5, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"border" : 2,
													"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 0.0, 240.0, 120.0 ],
													"numoutlets" : 0,
													"id" : "obj-31"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Play with noise",
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 105.0, 15.0, 138.0, 20.0 ],
													"numoutlets" : 0,
													"id" : "obj-41"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-47", 1 ],
													"destination" : [ "obj-81", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-81", 0 ],
													"destination" : [ "obj-24", 0 ],
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
									"varname" : "Soundofile",
									"name" : "SoundFile",
									"outlettype" : [ "signal" ],
									"embed" : 1,
									"args" : [  ],
									"presentation_rect" : [ 105.0, 0.0, 240.0, 120.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 195.0, 0.0, 240.0, 120.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"id" : "obj-4",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 105.0, 0.0, 240.0, 120.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 105.0, 0.0, 240.0, 120.0 ],
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
													"maxclass" : "inlet",
													"outlettype" : [ "" ],
													"numinlets" : 0,
													"patching_rect" : [ 345.0, 105.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"id" : "obj-19",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 45.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sfplay~ 2",
													"outlettype" : [ "signal", "signal", "bang" ],
													"fontsize" : 12.0,
													"numinlets" : 2,
													"fontname" : "Arial",
													"patching_rect" : [ 16.0, 90.0, 59.0, 20.0 ],
													"numoutlets" : 3,
													"id" : "obj-6",
													"save" : [ "#N", "sfplay~", "", 2, 120960, 0, "", ";" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "playbar",
													"outlettype" : [ "", "int" ],
													"numinlets" : 1,
													"patching_rect" : [ 16.0, 54.5, 180.0, 15.0 ],
													"numoutlets" : 2,
													"id" : "obj-3"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "open",
													"outlettype" : [ "" ],
													"fontsize" : 12.0,
													"numinlets" : 2,
													"fontname" : "Arial",
													"patching_rect" : [ 16.0, 14.0, 37.0, 18.0 ],
													"numoutlets" : 1,
													"id" : "obj-10"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"border" : 2,
													"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 0.0, 240.0, 120.0 ],
													"numoutlets" : 0,
													"id" : "obj-36"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 1 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-1", 0 ],
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
									"varname" : "cyclophaso",
									"name" : "cyclephasor",
									"outlettype" : [ "signal" ],
									"embed" : 1,
									"args" : [  ],
									"presentation_rect" : [ 105.0, 0.0, 240.0, 120.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 585.0, 0.0, 240.0, 120.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"id" : "obj-7",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 105.0, 0.0, 240.0, 120.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 105.0, 0.0, 240.0, 120.0 ],
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
													"maxclass" : "inlet",
													"outlettype" : [ "" ],
													"numinlets" : 0,
													"patching_rect" : [ 315.0, 75.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"id" : "obj-19",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 75.0, 195.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-15",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 128",
													"outlettype" : [ "" ],
													"hidden" : 1,
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 15.0, 0.0, 83.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-14"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"outlettype" : [ "signal", "int" ],
													"numinlets" : 2,
													"patching_rect" : [ 135.0, 90.0, 89.0, 17.0 ],
													"numoutlets" : 2,
													"id" : "obj-13"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"outlettype" : [ "signal", "int" ],
													"numinlets" : 2,
													"patching_rect" : [ 15.0, 90.0, 89.0, 17.0 ],
													"numoutlets" : 2,
													"id" : "obj-12"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"outlettype" : [ "float", "bang" ],
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 135.0, 30.0, 58.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "phasor~ 440",
													"outlettype" : [ "signal" ],
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"fontname" : "Arial",
													"patching_rect" : [ 135.0, 60.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-6"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 440",
													"outlettype" : [ "" ],
													"hidden" : 1,
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 90.0, 0.0, 83.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-84"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Set frequency",
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 75.0, 0.0, 83.0, 20.0 ],
													"numoutlets" : 0,
													"id" : "obj-80"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"outlettype" : [ "float", "bang" ],
													"fontsize" : 11.595187,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 15.0, 30.0, 58.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-75"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "cycle~ 440",
													"outlettype" : [ "signal" ],
													"fontsize" : 11.595187,
													"numinlets" : 2,
													"fontname" : "Arial",
													"patching_rect" : [ 15.0, 60.0, 66.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-70"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"border" : 2,
													"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 0.0, 240.0, 120.0 ],
													"numoutlets" : 0,
													"id" : "obj-74"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-15", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-15", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-6", 0 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-70", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-75", 0 ],
													"destination" : [ "obj-70", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-84", 0 ],
													"destination" : [ "obj-7", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-84", 0 ],
													"destination" : [ "obj-75", 0 ],
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
									"varname" : "dacodac",
									"name" : "Dacodac",
									"outlettype" : [ "signal" ],
									"embed" : 1,
									"args" : [  ],
									"presentation_rect" : [ 105.0, 0.0, 240.0, 120.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 570.0, 145.0, 240.0, 120.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"id" : "obj-8",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 105.0, 0.0, 240.0, 120.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 105.0, 0.0, 240.0, 120.0 ],
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
													"maxclass" : "inlet",
													"outlettype" : [ "" ],
													"numinlets" : 0,
													"patching_rect" : [ 300.0, 60.0, 25.0, 25.0 ],
													"numoutlets" : 1,
													"id" : "obj-19",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "tab",
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 12.0,
													"border" : 1,
													"numinlets" : 1,
													"fontname" : "Arial",
													"tabs" : [ "one", "two", "three", "four" ],
													"patching_rect" : [ 20.0, 30.0, 200.0, 20.0 ],
													"numoutlets" : 3,
													"id" : "obj-7"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Select channel",
													"fontsize" : 12.0,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 75.0, 0.0, 90.0, 20.0 ],
													"numoutlets" : 0,
													"id" : "obj-4"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 96.5, 150.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "adc~ 1",
													"outlettype" : [ "signal" ],
													"fontsize" : 12.0,
													"numinlets" : 1,
													"fontname" : "Arial",
													"patching_rect" : [ 96.5, 75.0, 47.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-1"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"border" : 2,
													"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 0.0, 240.0, 120.0 ],
													"numoutlets" : 0,
													"id" : "obj-74"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "set $1",
													"outlettype" : [ "" ],
													"fontsize" : 12.0,
													"numinlets" : 2,
													"fontname" : "Arial",
													"patching_rect" : [ 20.0, 90.0, 43.0, 18.0 ],
													"numoutlets" : 1,
													"id" : "obj-17"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+ 1",
													"outlettype" : [ "int" ],
													"fontsize" : 12.0,
													"numinlets" : 2,
													"fontname" : "Arial",
													"patching_rect" : [ 20.0, 50.0, 32.5, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-12"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-12", 0 ],
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
									"maxclass" : "message",
									"text" : "script bringtofront cyclophaso",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187,
									"numinlets" : 2,
									"fontname" : "Arial",
									"patching_rect" : [ 426.0, 328.5, 161.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-20"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "script bringtofront Soundofile",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187,
									"numinlets" : 2,
									"fontname" : "Arial",
									"patching_rect" : [ 270.0, 340.0, 158.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-19"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "script bringtofront dacodac",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187,
									"numinlets" : 2,
									"fontname" : "Arial",
									"patching_rect" : [ 330.0, 285.0, 147.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-18"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "script bringtofront noiso",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187,
									"numinlets" : 2,
									"fontname" : "Arial",
									"patching_rect" : [ 180.0, 297.0, 131.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-17"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sel 1 2 3 4",
									"outlettype" : [ "bang", "bang", "bang", "bang", "" ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"fontname" : "Arial",
									"patching_rect" : [ 180.0, 255.0, 73.0, 20.0 ],
									"numoutlets" : 5,
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "thispatcher",
									"outlettype" : [ "", "" ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"fontname" : "Arial",
									"patching_rect" : [ 195.0, 390.0, 69.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-9",
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "gain~",
									"outlettype" : [ "signal", "int" ],
									"presentation_rect" : [ 7.5, 77.0, 88.0, 18.0 ],
									"numinlets" : 2,
									"patching_rect" : [ 7.5, 77.0, 88.0, 18.0 ],
									"numoutlets" : 2,
									"presentation" : 1,
									"id" : "obj-78"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 30.0, 240.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-2",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 2",
									"outlettype" : [ "" ],
									"hidden" : 1,
									"fontsize" : 11.595187,
									"presentation_rect" : [ 7.5, 0.0, 70.0, 20.0 ],
									"numinlets" : 1,
									"fontname" : "Arial",
									"patching_rect" : [ 7.5, 0.0, 70.0, 20.0 ],
									"numoutlets" : 1,
									"presentation" : 1,
									"id" : "obj-100"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Select source",
									"fontsize" : 11.595187,
									"presentation_rect" : [ 7.5, 15.0, 88.0, 20.0 ],
									"numinlets" : 1,
									"fontname" : "Arial",
									"patching_rect" : [ 7.5, 15.0, 88.0, 20.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-42"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"outlettype" : [ "int", "", "" ],
									"fontsize" : 11.595187,
									"presentation_rect" : [ 7.5, 44.0, 88.0, 20.0 ],
									"items" : [ "None", ",", "Audio", "file", ",", "Noise", ",", "Cycle~", ",", "Adc~" ],
									"numinlets" : 1,
									"types" : [  ],
									"fontname" : "Arial",
									"patching_rect" : [ 7.5, 44.0, 88.0, 20.0 ],
									"numoutlets" : 3,
									"presentation" : 1,
									"id" : "obj-37"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "selector~ 4",
									"outlettype" : [ "signal" ],
									"fontsize" : 11.595187,
									"numinlets" : 5,
									"fontname" : "Arial",
									"patching_rect" : [ 150.0, 195.0, 73.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-29"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"border" : 2,
									"presentation_rect" : [ 0.0, 0.0, 316.0, 120.0 ],
									"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 0.0, 0.0, 120.0, 120.0 ],
									"numoutlets" : 0,
									"presentation" : 1,
									"id" : "obj-38"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-10", 1 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 3 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 2 ],
									"destination" : [ "obj-20", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-100", 0 ],
									"destination" : [ "obj-37", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 0 ],
									"destination" : [ "obj-78", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 0 ],
									"destination" : [ "obj-29", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-29", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-29", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-29", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-29", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-78", 0 ],
									"destination" : [ "obj-2", 0 ],
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
					"maxclass" : "comment",
					"text" : "huygens~ by Julien Colafrancesco & Pierre Guillot\n© 2012 CICM / Universite Paris 8",
					"linecount" : 2,
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 497.75, 6.0, 288.0, 33.0 ],
					"numoutlets" : 0,
					"id" : "obj-59"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r huygens",
					"outlettype" : [ "" ],
					"fontsize" : 11.595187,
					"numinlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 15.0, 300.0, 61.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-4"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_title",
					"text" : "huygens~",
					"fontface" : 3,
					"fontsize" : 20.871338,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 7.0, 6.0, 485.0, 30.0 ],
					"numoutlets" : 0,
					"id" : "obj-2",
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_digest",
					"text" : "A Wave Field Synthesis external.",
					"fontsize" : 12.754705,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 7.0, 35.0, 503.0, 21.0 ],
					"numoutlets" : 0,
					"id" : "obj-3",
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description",
					"text" : "huygens~ is a sound spatializer that uses wave filed synthesis algorithm for a linear or a circular array of loudness speakers.",
					"linecount" : 2,
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 7.0, 56.0, 491.0, 33.0 ],
					"numoutlets" : 0,
					"id" : "obj-5"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"varname" : "autohelp_top_panel",
					"grad2" : [ 0.85, 0.85, 0.85, 1.0 ],
					"mode" : 1,
					"numinlets" : 1,
					"background" : 1,
					"grad1" : [ 0.27, 0.35, 0.47, 1.0 ],
					"patching_rect" : [ 2.0, 4.0, 495.0, 52.0 ],
					"numoutlets" : 0,
					"id" : "obj-9"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-1", 15 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-29", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 14 ],
					"destination" : [ "obj-12", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 13 ],
					"destination" : [ "obj-12", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 12 ],
					"destination" : [ "obj-12", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 11 ],
					"destination" : [ "obj-12", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 10 ],
					"destination" : [ "obj-12", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 9 ],
					"destination" : [ "obj-12", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 8 ],
					"destination" : [ "obj-12", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 7 ],
					"destination" : [ "obj-12", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 6 ],
					"destination" : [ "obj-12", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 5 ],
					"destination" : [ "obj-12", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 4 ],
					"destination" : [ "obj-12", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 3 ],
					"destination" : [ "obj-12", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 2 ],
					"destination" : [ "obj-12", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 1 ],
					"destination" : [ "obj-12", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 14 ],
					"destination" : [ "obj-1", 14 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 13 ],
					"destination" : [ "obj-1", 13 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 12 ],
					"destination" : [ "obj-1", 12 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 11 ],
					"destination" : [ "obj-1", 11 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 10 ],
					"destination" : [ "obj-1", 10 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 9 ],
					"destination" : [ "obj-1", 9 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 8 ],
					"destination" : [ "obj-1", 8 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 7 ],
					"destination" : [ "obj-1", 7 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 6 ],
					"destination" : [ "obj-1", 6 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 5 ],
					"destination" : [ "obj-1", 5 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 4 ],
					"destination" : [ "obj-1", 4 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 3 ],
					"destination" : [ "obj-1", 3 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 2 ],
					"destination" : [ "obj-1", 2 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 1 ],
					"destination" : [ "obj-1", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-38", 0 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 14 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 13 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 12 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 11 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 10 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 9 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 8 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 7 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 6 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 5 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 4 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 3 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 2 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 1 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [ 24.5, 350.0, 85.5, 350.0 ]
				}

			}
 ]
	}

}
