{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 100.0, 100.0, 822.0, 646.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 100.0, 100.0, 822.0, 646.0 ],
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
					"varname" : "autohelp_top_description[3]",
					"text" : "Refresh Interval\n(ms) :",
					"linecount" : 2,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 480.0, 171.0, 97.0, 34.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-47",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 480.0, 171.0, 95.0, 33.0 ],
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"numinlets" : 1,
					"rounded" : 15,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-48"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[2]",
					"text" : "Offset of loudspeakers (-180°  180°) : ",
					"linecount" : 2,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 345.0, 171.0, 132.0, 34.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-44",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 345.0, 171.0, 132.0, 33.0 ],
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"numinlets" : 1,
					"rounded" : 15,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-45"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
					"linecount" : 2,
					"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"fontsize" : 11.595187,
					"patching_rect" : [ 501.0, 17.5, 257.0, 33.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-43",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 501.0, 17.5, 257.0, 32.0 ],
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"numinlets" : 1,
					"rounded" : 6,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-6"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"name" : "hoa.helpheader.maxpat",
					"args" : [ "@obj-name", "hoa.meter~", "@obj-desc", "A", "circular", "version", "of", "the", "meter~", "with", "audio", "descriptor." ],
					"patching_rect" : [ 4.0, 5.5, 483.0, 56.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-8"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "bgcolor 0.93 0.93 0.92 1.",
					"linecount" : 2,
					"fontsize" : 7.180877,
					"patching_rect" : [ 423.0, 22.0, 52.0, 23.0 ],
					"numinlets" : 4,
					"numoutlets" : 0,
					"id" : "obj-29",
					"fontname" : "Arial",
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[1]",
					"text" : "hoa.meter~ displays the peak levels for a circurlar array of loudspeakers. It computes and displays the energy vector. The number of loudspeakers is defined at the object creation with the attribute @ls\nex : [hoa.meter~ @ls 8]",
					"linecount" : 3,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0,
					"patching_rect" : [ 4.0, 73.0, 564.0, 48.0 ],
					"numinlets" : 1,
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-40",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"patching_rect" : [ 4.0, 73.0, 558.0, 47.0 ],
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"numinlets" : 1,
					"rounded" : 15,
					"numoutlets" : 0,
					"shadow" : -1,
					"id" : "obj-41"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p angles",
					"fontsize" : 14.84361,
					"patching_rect" : [ 622.0, 423.5, 67.0, 24.0 ],
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"numinlets" : 0,
					"numoutlets" : 0,
					"id" : "obj-3",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 822.0, 620.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 822.0, 620.0 ],
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
									"text" : "turn dac~ on",
									"fontsize" : 14.0,
									"patching_rect" : [ 545.5, 563.0, 112.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"patching_rect" : [ 493.0, 541.0, 44.0, 44.0 ],
									"numinlets" : 2,
									"numoutlets" : 0,
									"id" : "obj-33",
									"local" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 487.0, 530.25, 181.0, 63.75 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-26"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "ls_angles message sets the loudspeakers angles.\nEach angle can be set within -360° and 360° range.\nThe list will be sorted in ascending order between the equivalent 0 to 360° range.",
									"linecount" : 4,
									"frgb" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 487.0, 359.0, 328.0, 71.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-41",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 487.0, 359.0, 328.0, 69.0 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-24"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"fontsize" : 7.180877,
									"patching_rect" : [ 606.0, 22.0, 52.0, 23.0 ],
									"numinlets" : 4,
									"numoutlets" : 0,
									"id" : "obj-22",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "=",
									"fontsize" : 14.0,
									"patching_rect" : [ 655.0, 245.0, 20.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-23",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "-30 0 30 -110 110",
									"fontsize" : 14.0,
									"patching_rect" : [ 682.0, 245.0, 119.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-15",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : -360.0,
									"maximum" : 360.0,
									"fontsize" : 14.0,
									"patching_rect" : [ 703.0, 140.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-21",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : -360.0,
									"maximum" : 360.0,
									"fontsize" : 14.0,
									"patching_rect" : [ 649.0, 140.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : -360.0,
									"maximum" : 360.0,
									"fontsize" : 14.0,
									"patching_rect" : [ 595.0, 140.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-19",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : -360.0,
									"maximum" : 360.0,
									"fontsize" : 14.0,
									"patching_rect" : [ 541.0, 140.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-18",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : -360.0,
									"maximum" : 360.0,
									"fontsize" : 14.0,
									"patching_rect" : [ 487.0, 140.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pak 0. 72. 144. 216. 288.",
									"fontsize" : 14.0,
									"patching_rect" : [ 487.0, 168.0, 235.0, 23.0 ],
									"numinlets" : 5,
									"numoutlets" : 1,
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.optim~ 2 inPhase",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 98.0, 426.0, 23.0 ],
									"numinlets" : 5,
									"numoutlets" : 5,
									"id" : "obj-11",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "0 30 110 250 330",
									"fontsize" : 14.0,
									"patching_rect" : [ 529.0, 245.0, 118.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-9",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend ls_angles",
									"fontsize" : 14.0,
									"patching_rect" : [ 487.0, 278.0, 125.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "0. 72. 144. 216. 288.",
									"fontsize" : 14.0,
									"patching_rect" : [ 508.0, 214.0, 139.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-4",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"numleds" : 10,
									"ls_angles" : [ 0.0, 30.0, 110.0, 250.0, 330.0 ],
									"patching_rect" : [ 31.0, 168.0, 426.0, 426.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 5,
									"numoutlets" : 0,
									"id" : "obj-1",
									"ls" : 5
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 10.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-13",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p rotate",
									"fontsize" : 14.0,
									"patching_rect" : [ 438.0, 39.0, 58.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-12",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "hoa.pi 2",
													"fontsize" : 11.595187,
													"patching_rect" : [ 65.0, 125.0, 52.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-14",
													"fontname" : "Arial",
													"outlettype" : [ "float" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~",
													"fontsize" : 11.595187,
													"patching_rect" : [ 50.0, 150.0, 33.5, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-15",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "phasor~ 0.2",
													"fontsize" : 11.595187,
													"patching_rect" : [ 50.0, 100.0, 72.0, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-18",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"id" : "obj-9",
													"outlettype" : [ "float" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 50.0, 229.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-11",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-15", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-15", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-15", 1 ],
													"hidden" : 0,
													"midpoints" : [ 74.5, 146.0, 74.0, 146.0 ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
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
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 14.0,
									"patching_rect" : [ 438.0, 10.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~ 5",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 39.0, 48.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"fontsize" : 11.595187,
									"patching_rect" : [ 552.0, 22.0, 51.0, 20.0 ],
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
									"text" : "hoa.connect 15 32",
									"fontsize" : 11.595187,
									"patching_rect" : [ 552.0, 52.0, 106.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-10",
									"fontname" : "Arial",
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 2 5",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 127.0, 426.0, 23.0 ],
									"numinlets" : 5,
									"numoutlets" : 5,
									"id" : "obj-3",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 2",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 69.0, 426.0, 23.0 ],
									"numinlets" : 2,
									"numoutlets" : 5,
									"id" : "obj-2",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal" ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [ 538.5, 271.0, 496.5, 271.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-1", 4 ],
									"hidden" : 0,
									"midpoints" : [ 496.5, 309.0, 472.0, 309.0, 472.0, 158.0, 447.5, 158.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-46", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 1,
									"midpoints" : [ 561.5, 43.0, 561.5, 43.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [ 517.5, 256.5, 496.5, 256.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 1 ],
									"destination" : [ "obj-1", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 2 ],
									"destination" : [ "obj-1", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 3 ],
									"destination" : [ "obj-1", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 4 ],
									"destination" : [ "obj-1", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-14", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-14", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 1 ],
									"destination" : [ "obj-11", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 2 ],
									"destination" : [ "obj-11", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 3 ],
									"destination" : [ "obj-11", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 4 ],
									"destination" : [ "obj-11", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-14", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-14", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-15", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [ 691.5, 271.0, 496.5, 271.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-2", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 1 ],
									"destination" : [ "obj-3", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 2 ],
									"destination" : [ "obj-3", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 3 ],
									"destination" : [ "obj-3", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 4 ],
									"destination" : [ "obj-3", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
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
					"text" : "p color",
					"fontsize" : 14.84361,
					"patching_rect" : [ 622.0, 498.5, 55.0, 24.0 ],
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"numinlets" : 0,
					"numoutlets" : 0,
					"id" : "obj-39",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 100.0, 126.0, 822.0, 620.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 100.0, 126.0, 822.0, 620.0 ],
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
									"text" : "turn dac~ on",
									"fontsize" : 14.0,
									"patching_rect" : [ 612.5, 488.0, 112.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-8",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"patching_rect" : [ 560.0, 466.0, 44.0, 44.0 ],
									"numinlets" : 2,
									"numoutlets" : 0,
									"id" : "obj-13",
									"local" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 554.0, 455.25, 181.0, 63.75 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-26"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Custom colors :",
									"fontsize" : 14.0,
									"patching_rect" : [ 25.0, 15.0, 147.0, 23.0 ],
									"numinlets" : 1,
									"underline" : 1,
									"numoutlets" : 0,
									"id" : "obj-6",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 18.0, 11.0, 160.25, 30.0 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"fontsize" : 7.180877,
									"patching_rect" : [ 18.0, 556.0, 52.0, 23.0 ],
									"numinlets" : 4,
									"numoutlets" : 0,
									"id" : "obj-2",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~ 1",
									"fontsize" : 14.0,
									"patching_rect" : [ 18.0, 26.0, 48.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-17",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Colors",
									"fontsize" : 14.0,
									"patching_rect" : [ 554.0, 72.0, 51.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-14",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend",
									"fontsize" : 14.0,
									"patching_rect" : [ 554.0, 238.0, 62.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-11",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"fontsize" : 14.0,
									"types" : [  ],
									"patching_rect" : [ 575.0, 176.0, 146.0, 23.0 ],
									"items" : [ "bgcolor", ",", "mbgcolor", ",", "bordercolor", ",", "mbordercolor", ",", "coldcolor", ",", "tepidcolor", ",", "warmcolor", ",", "hotcolor", ",", "overcolor", ",", "energycolor" ],
									"numinlets" : 1,
									"numoutlets" : 3,
									"id" : "obj-10",
									"fontname" : "Arial",
									"outlettype" : [ "int", "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "swatch",
									"patching_rect" : [ 554.0, 94.0, 167.0, 73.0 ],
									"numinlets" : 3,
									"numoutlets" : 2,
									"id" : "obj-9",
									"outlettype" : [ "", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend set",
									"fontsize" : 14.0,
									"patching_rect" : [ 638.5, 206.0, 84.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-4",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"ls_angles" : [ 0.0, 45.0, 90.0, 135.0, 180.0, 225.0, 270.0, 315.0 ],
									"mbgcolor" : [ 0.0, 0.0, 0.0, 0.0 ],
									"bordercolor" : [ 0.25098, 0.25098, 0.25098, 0.46 ],
									"patching_rect" : [ 18.0, 58.0, 461.0, 461.0 ],
									"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 8,
									"numoutlets" : 0,
									"mbordercolor" : [ 0.0, 0.0, 0.0, 0.0 ],
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0",
									"fontsize" : 11.595187,
									"patching_rect" : [ 575.0, 148.0, 70.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-12",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "" ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 1 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 2 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 3 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 4 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 5 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 6 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 7 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-1", 7 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 1 ],
									"destination" : [ "obj-4", 0 ],
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
					"text" : "p value",
					"fontsize" : 14.84361,
					"patching_rect" : [ 622.0, 463.5, 58.0, 24.0 ],
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"numinlets" : 0,
					"numoutlets" : 0,
					"id" : "obj-38",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 822.0, 620.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 822.0, 620.0 ],
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
									"text" : "hoa.meter~ and the native msp meter~ object share the same behavior and messages.",
									"linecount" : 2,
									"fontsize" : 14.0,
									"patching_rect" : [ 171.75, 28.0, 295.0, 39.0 ],
									"numinlets" : 1,
									"underline" : 1,
									"numoutlets" : 0,
									"id" : "obj-11",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "turn dac~ on",
									"fontsize" : 14.0,
									"patching_rect" : [ 79.500031, 477.875, 112.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-4",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"patching_rect" : [ 27.000031, 455.875, 44.0, 44.0 ],
									"numinlets" : 2,
									"numoutlets" : 0,
									"id" : "obj-5",
									"local" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 21.000031, 445.125, 181.0, 63.75 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-26"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"fontsize" : 7.180877,
									"patching_rect" : [ 520.0, 28.0, 52.0, 23.0 ],
									"numinlets" : 4,
									"numoutlets" : 0,
									"id" : "obj-2",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"minimum" : 20,
									"fontsize" : 14.0,
									"patching_rect" : [ 416.0, 392.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-9",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "interval $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 416.0, 421.0, 74.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"minimum" : 1,
									"maximum" : 12,
									"fontsize" : 14.0,
									"patching_rect" : [ 406.0, 332.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-38",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "dbperled $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 406.0, 360.0, 82.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-23",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"minimum" : 0,
									"maximum" : 20,
									"fontsize" : 14.0,
									"patching_rect" : [ 382.0, 215.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-36",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "nwarmleds $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 382.0, 245.0, 98.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-37",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"minimum" : 0,
									"maximum" : 20,
									"fontsize" : 14.0,
									"patching_rect" : [ 394.0, 273.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-34",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "ntepidleds $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 394.0, 303.0, 94.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-35",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r metval",
									"fontsize" : 14.0,
									"patching_rect" : [ 75.000031, 59.0, 60.0, 23.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-33",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s metval",
									"fontsize" : 14.0,
									"patching_rect" : [ 354.0, 466.0, 63.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-32",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"minimum" : 0,
									"maximum" : 20,
									"fontsize" : 14.0,
									"patching_rect" : [ 370.0, 155.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-31",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "nhotleds $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 370.0, 185.0, 82.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-29",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"minimum" : 10,
									"maximum" : 20,
									"fontsize" : 14.0,
									"patching_rect" : [ 354.0, 89.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-30",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "numleds $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 354.0, 127.0, 82.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-28",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "meter~",
									"interval" : 20,
									"patching_rect" : [ 171.75, 271.0, 16.5, 136.0 ],
									"bgcolor" : [ 0.333324, 0.333375, 0.333299, 1.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-19",
									"outlettype" : [ "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : 0.0,
									"maximum" : 1.0,
									"fontsize" : 14.0,
									"patching_rect" : [ 21.000031, 28.0, 114.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~ 1",
									"fontsize" : 14.0,
									"patching_rect" : [ 21.000031, 59.0, 48.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"interval" : 20,
									"ls_angles" : [ 0.0 ],
									"mbgcolor" : [ 0.403061, 0.403061, 0.403061, 1.0 ],
									"bordercolor" : [ 0.254902, 0.254902, 0.254902, 0.24 ],
									"patching_rect" : [ 21.000031, 89.0, 318.0, 318.0 ],
									"bgcolor" : [ 0.505882, 0.505882, 0.505882, 0.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"energy" : 0,
									"id" : "obj-1",
									"ls" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 166.75, 26.0, 299.25, 42.0 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-12"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-23", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-37", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-36", 0 ],
									"destination" : [ "obj-37", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-35", 0 ],
									"destination" : [ "obj-32", 0 ],
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
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-29", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-30", 0 ],
									"destination" : [ "obj-28", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-32", 0 ],
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
					"text" : "p multichannel",
					"fontsize" : 14.84361,
					"patching_rect" : [ 622.0, 348.5, 106.0, 24.0 ],
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"numinlets" : 0,
					"numoutlets" : 0,
					"id" : "obj-33",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 822.0, 620.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 822.0, 620.0 ],
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
									"text" : "@offset -45°",
									"frgb" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 636.0, 20.0, 88.0, 23.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-7",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 636.0, 17.625, 88.0, 26.375 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"fontsize" : 7.180877,
									"patching_rect" : [ 670.0, 587.0, 52.0, 23.0 ],
									"numinlets" : 4,
									"numoutlets" : 0,
									"id" : "obj-3",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "@offset -90°",
									"frgb" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 397.0, 20.0, 88.0, 23.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-42",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Mono",
									"frgb" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 163.0, 20.0, 46.0, 23.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-41",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "receive~ hoa.meter~",
									"fontsize" : 14.0,
									"patching_rect" : [ 497.0, 20.0, 139.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-39",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"interval" : 150,
									"ls_angles" : [ 0.0, 90.0, 180.0, 270.0 ],
									"mbgcolor" : [ 0.407843, 0.407843, 0.407843, 1.0 ],
									"bordercolor" : [ 0.254902, 0.254902, 0.254902, 1.0 ],
									"patching_rect" : [ 497.0, 50.0, 225.0, 225.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 4,
									"offset" : -45.0,
									"numoutlets" : 0,
									"id" : "obj-38",
									"ls" : 4
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "turn on the dac~",
									"fontsize" : 14.0,
									"patching_rect" : [ 67.5, 581.0, 112.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"patching_rect" : [ 15.0, 559.0, 44.0, 44.0 ],
									"numinlets" : 2,
									"numoutlets" : 0,
									"id" : "obj-33",
									"local" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "receive~ hoa.meter~",
									"fontsize" : 14.0,
									"patching_rect" : [ 497.0, 283.0, 139.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-28",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"prototypename" : "bigOctoBlack",
									"interval" : 150,
									"ls_angles" : [ 0.0, 22.0, 45.0, 67.0, 90.0, 112.0, 135.0, 157.0, 180.0, 202.0, 225.0, 247.0, 270.0, 292.0, 315.0, 337.5 ],
									"mbgcolor" : [ 0.407843, 0.407843, 0.407843, 1.0 ],
									"bordercolor" : [ 0.254902, 0.254902, 0.254902, 1.0 ],
									"patching_rect" : [ 497.0, 313.0, 225.0, 225.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 16,
									"numoutlets" : 0,
									"id" : "obj-27",
									"ls" : 16
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "receive~ hoa.meter~",
									"fontsize" : 14.0,
									"patching_rect" : [ 15.0, 20.0, 139.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-24",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"prototypename" : "bigQuadriBlack",
									"interval" : 150,
									"ls_angles" : [ 0.0 ],
									"metersize" : 1.0,
									"mbgcolor" : [ 0.407843, 0.407843, 0.407843, 1.0 ],
									"bordercolor" : [ 0.254902, 0.254902, 0.254902, 1.0 ],
									"patching_rect" : [ 15.0, 50.0, 225.0, 225.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"energy" : 0,
									"id" : "obj-25",
									"ls" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "receive~ hoa.meter~",
									"fontsize" : 14.0,
									"patching_rect" : [ 15.0, 283.0, 139.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-22",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"ls_angles" : [ 0.0, 72.0, 144.0, 216.0, 288.0 ],
									"patching_rect" : [ 15.0, 313.0, 225.0, 225.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 5,
									"numoutlets" : 0,
									"id" : "obj-23",
									"ls" : 5
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "receive~ hoa.meter~",
									"fontsize" : 14.0,
									"patching_rect" : [ 256.0, 283.0, 139.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "receive~ hoa.meter~",
									"fontsize" : 14.0,
									"patching_rect" : [ 256.0, 20.0, 139.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-19",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "send~ hoa.meter~",
									"fontsize" : 14.0,
									"patching_rect" : [ 341.0, 587.0, 124.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-18",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "-~ 1",
									"fontsize" : 14.0,
									"patching_rect" : [ 295.0, 587.0, 35.0, 23.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-14",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "*~ 2.1",
									"fontsize" : 14.0,
									"patching_rect" : [ 248.0, 587.0, 47.0, 23.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-13",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "phasor~ 0.15",
									"fontsize" : 14.0,
									"patching_rect" : [ 248.0, 559.0, 93.0, 23.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-11",
									"fontname" : "Arial",
									"hidden" : 1,
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"prototypename" : "bigOctoBlack",
									"interval" : 150,
									"ls_angles" : [ 0.0, 180.0 ],
									"mbgcolor" : [ 0.407843, 0.407843, 0.407843, 1.0 ],
									"bordercolor" : [ 0.254902, 0.254902, 0.254902, 1.0 ],
									"patching_rect" : [ 256.0, 50.0, 225.0, 225.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 2,
									"offset" : -90.0,
									"numoutlets" : 0,
									"id" : "obj-2",
									"ls" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"interval" : 150,
									"ls_angles" : [ 0.0, 45.0, 90.0, 135.0, 180.0, 225.0, 270.0, 315.0 ],
									"patching_rect" : [ 256.0, 313.0, 225.0, 225.0 ],
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 8,
									"numoutlets" : 0,
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 9.0, 548.25, 181.0, 63.75 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 160.0, 15.625, 51.0, 28.375 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 397.0, 17.625, 88.0, 26.375 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-5"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-39", 0 ],
									"destination" : [ "obj-38", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-23", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 1,
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
					"text" : "p custom",
					"fontsize" : 14.84361,
					"patching_rect" : [ 622.0, 386.5, 71.0, 24.0 ],
					"color" : [ 0.267659, 0.594304, 0.839216, 1.0 ],
					"numinlets" : 0,
					"numoutlets" : 0,
					"id" : "obj-30",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 822.0, 620.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 822.0, 620.0 ],
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
									"text" : "hoa.meter~ border color alpha.",
									"frgb" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 553.0, 369.0, 210.0, 23.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-20",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 553.0, 368.625, 210.0, 22.375 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-22"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Draw energy vector.",
									"frgb" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 553.0, 307.0, 210.0, 23.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-16",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 553.0, 306.625, 210.0, 22.375 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-18"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Draw leds background.",
									"frgb" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 553.0, 229.0, 210.0, 23.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-7",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 553.0, 228.625, 210.0, 22.375 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-11"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Change size of the interior circle",
									"frgb" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"fontsize" : 14.0,
									"patching_rect" : [ 553.0, 158.0, 210.0, 23.0 ],
									"numinlets" : 1,
									"textcolor" : [ 0.229592, 0.229592, 0.229592, 1.0 ],
									"numoutlets" : 0,
									"id" : "obj-41",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 553.0, 157.625, 210.0, 22.375 ],
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
									"text" : "turn on the dac~",
									"fontsize" : 14.0,
									"patching_rect" : [ 551.5, 551.0, 112.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"patching_rect" : [ 499.0, 529.0, 44.0, 44.0 ],
									"numinlets" : 2,
									"numoutlets" : 0,
									"id" : "obj-33",
									"local" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"patching_rect" : [ 493.0, 518.25, 181.0, 63.75 ],
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"numinlets" : 1,
									"rounded" : 15,
									"numoutlets" : 0,
									"shadow" : -1,
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"fontsize" : 7.180877,
									"patching_rect" : [ 606.0, 20.0, 52.0, 23.0 ],
									"numinlets" : 4,
									"numoutlets" : 0,
									"id" : "obj-4",
									"fontname" : "Arial",
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : 0.0,
									"maximum" : 1.0,
									"fontsize" : 14.0,
									"patching_rect" : [ 493.0, 369.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-26",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "mbordercolor 0.25 0.25 0.25 $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 493.0, 400.0, 206.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-25",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"patching_rect" : [ 493.0, 307.0, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-23",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"patching_rect" : [ 493.0, 229.0, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-21",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"minimum" : 0.0,
									"maximum" : 1.0,
									"fontsize" : 14.0,
									"patching_rect" : [ 493.0, 158.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-19",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "metersize $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 493.0, 188.0, 90.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "energy $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 493.0, 336.0, 72.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-15",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "leds_bg $1",
									"fontsize" : 14.0,
									"patching_rect" : [ 493.0, 257.0, 78.0, 21.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 23.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-13",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p rotate",
									"fontsize" : 14.0,
									"patching_rect" : [ 436.0, 52.0, 58.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-12",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "hoa.pi 2",
													"fontsize" : 11.595187,
													"patching_rect" : [ 65.0, 125.0, 52.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-14",
													"fontname" : "Arial",
													"outlettype" : [ "float" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~",
													"fontsize" : 11.595187,
													"patching_rect" : [ 50.0, 150.0, 33.5, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-15",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "phasor~ 0.2",
													"fontsize" : 11.595187,
													"patching_rect" : [ 50.0, 100.0, 72.0, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-18",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"id" : "obj-9",
													"outlettype" : [ "float" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 50.0, 229.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-11",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-15", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-15", 0 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-15", 1 ],
													"hidden" : 0,
													"midpoints" : [ 74.5, 146.0, 74.0, 146.0 ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
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
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 14.0,
									"patching_rect" : [ 436.0, 23.0, 50.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sig~ 1.1",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 52.0, 60.0, 23.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"fontsize" : 11.595187,
									"patching_rect" : [ 552.0, 22.0, 51.0, 20.0 ],
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
									"text" : "hoa.connect 15 32",
									"fontsize" : 11.595187,
									"patching_rect" : [ 552.0, 52.0, 106.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-10",
									"fontname" : "Arial",
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 15 32",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 119.0, 424.0, 23.0 ],
									"numinlets" : 31,
									"numoutlets" : 32,
									"id" : "obj-3",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 15",
									"fontsize" : 14.0,
									"patching_rect" : [ 31.0, 82.0, 424.0, 23.0 ],
									"numinlets" : 2,
									"numoutlets" : 31,
									"id" : "obj-2",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "hoa.meter~",
									"interval" : 120,
									"numleds" : 15,
									"ls_angles" : [ 0.0, 11.0, 22.0, 33.0, 45.0, 56.0, 67.0, 78.0, 90.0, 101.0, 112.0, 123.0, 135.0, 146.0, 157.0, 168.0, 180.0, 191.0, 202.0, 213.0, 225.0, 236.0, 247.0, 258.0, 270.0, 281.0, 292.0, 303.0, 315.0, 326.0, 337.0, 348.75 ],
									"metersize" : 0.52,
									"patching_rect" : [ 31.0, 158.0, 424.0, 424.0 ],
									"dbperled" : 2,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"numinlets" : 32,
									"numoutlets" : 0,
									"energy" : 0,
									"mbordercolor" : [ 0.25, 0.25, 0.25, 0.0 ],
									"id" : "obj-1",
									"ls" : 32
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-46", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 1,
									"midpoints" : [ 561.5, 43.0, 561.5, 43.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 1 ],
									"destination" : [ "obj-1", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 2 ],
									"destination" : [ "obj-1", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 3 ],
									"destination" : [ "obj-1", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 4 ],
									"destination" : [ "obj-1", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 5 ],
									"destination" : [ "obj-1", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 6 ],
									"destination" : [ "obj-1", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 7 ],
									"destination" : [ "obj-1", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 8 ],
									"destination" : [ "obj-1", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 9 ],
									"destination" : [ "obj-1", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 10 ],
									"destination" : [ "obj-1", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 11 ],
									"destination" : [ "obj-1", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 12 ],
									"destination" : [ "obj-1", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 13 ],
									"destination" : [ "obj-1", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 14 ],
									"destination" : [ "obj-1", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 15 ],
									"destination" : [ "obj-1", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 16 ],
									"destination" : [ "obj-1", 16 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 17 ],
									"destination" : [ "obj-1", 17 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 18 ],
									"destination" : [ "obj-1", 18 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 19 ],
									"destination" : [ "obj-1", 19 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 20 ],
									"destination" : [ "obj-1", 20 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 21 ],
									"destination" : [ "obj-1", 21 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 22 ],
									"destination" : [ "obj-1", 22 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 23 ],
									"destination" : [ "obj-1", 23 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 24 ],
									"destination" : [ "obj-1", 24 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 25 ],
									"destination" : [ "obj-1", 25 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 26 ],
									"destination" : [ "obj-1", 26 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 27 ],
									"destination" : [ "obj-1", 27 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 28 ],
									"destination" : [ "obj-1", 28 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 29 ],
									"destination" : [ "obj-1", 29 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 30 ],
									"destination" : [ "obj-1", 30 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 31 ],
									"destination" : [ "obj-1", 31 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-1", 31 ],
									"hidden" : 0,
									"midpoints" : [ 502.5, 429.0, 474.0, 429.0, 474.0, 148.0, 445.5, 148.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 1 ],
									"destination" : [ "obj-3", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 2 ],
									"destination" : [ "obj-3", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 3 ],
									"destination" : [ "obj-3", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 4 ],
									"destination" : [ "obj-3", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 5 ],
									"destination" : [ "obj-3", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 6 ],
									"destination" : [ "obj-3", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 7 ],
									"destination" : [ "obj-3", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 8 ],
									"destination" : [ "obj-3", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 9 ],
									"destination" : [ "obj-3", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 10 ],
									"destination" : [ "obj-3", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 11 ],
									"destination" : [ "obj-3", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 12 ],
									"destination" : [ "obj-3", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 13 ],
									"destination" : [ "obj-3", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 14 ],
									"destination" : [ "obj-3", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 15 ],
									"destination" : [ "obj-3", 15 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 16 ],
									"destination" : [ "obj-3", 16 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 17 ],
									"destination" : [ "obj-3", 17 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 18 ],
									"destination" : [ "obj-3", 18 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 19 ],
									"destination" : [ "obj-3", 19 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 20 ],
									"destination" : [ "obj-3", 20 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 21 ],
									"destination" : [ "obj-3", 21 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 22 ],
									"destination" : [ "obj-3", 22 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 23 ],
									"destination" : [ "obj-3", 23 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 24 ],
									"destination" : [ "obj-3", 24 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 25 ],
									"destination" : [ "obj-3", 25 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 26 ],
									"destination" : [ "obj-3", 26 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 27 ],
									"destination" : [ "obj-3", 27 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 28 ],
									"destination" : [ "obj-3", 28 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 29 ],
									"destination" : [ "obj-3", 29 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 30 ],
									"destination" : [ "obj-3", 30 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-1", 31 ],
									"hidden" : 0,
									"midpoints" : [ 502.5, 217.0, 474.0, 217.0, 474.0, 148.0, 445.5, 148.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-15", 0 ],
									"destination" : [ "obj-1", 31 ],
									"hidden" : 0,
									"midpoints" : [ 502.5, 365.0, 474.0, 365.0, 474.0, 148.0, 445.5, 148.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-1", 31 ],
									"hidden" : 0,
									"midpoints" : [ 502.5, 286.0, 474.0, 286.0, 474.0, 148.0, 445.5, 148.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-2", 1 ],
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
					"maxclass" : "number",
					"minimum" : 20,
					"fontsize" : 11.595187,
					"patching_rect" : [ 480.0, 211.0, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-36",
					"fontname" : "Arial",
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 50",
					"fontsize" : 11.595187,
					"patching_rect" : [ 480.0, 181.0, 76.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-12",
					"fontname" : "Arial",
					"hidden" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend interval",
					"fontsize" : 11.595187,
					"patching_rect" : [ 480.0, 241.0, 94.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-28",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0",
					"fontsize" : 11.595187,
					"patching_rect" : [ 345.0, 181.0, 70.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-35",
					"fontname" : "Arial",
					"hidden" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"minimum" : -180.0,
					"maximum" : 180.0,
					"fontsize" : 11.595187,
					"patching_rect" : [ 345.0, 211.0, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-23",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend offset",
					"fontsize" : 11.595187,
					"patching_rect" : [ 345.0, 241.0, 84.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-21",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"name" : "poiu.maxpat",
					"border" : 1,
					"args" : [ "@module", 3 ],
					"patching_rect" : [ 30.0, 136.0, 218.0, 87.0 ],
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-2",
					"outlettype" : [ "signal" ],
					"embed" : 1,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 30.0, 136.0, 218.0, 87.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"defrect" : [ 30.0, 136.0, 218.0, 87.0 ],
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
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "meter~",
									"presentation_rect" : [ 199.0, 2.0, 12.0, 80.0 ],
									"patching_rect" : [ 90.0, 360.0, 12.0, 80.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-39",
									"outlettype" : [ "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 128",
									"fontsize" : 12.0,
									"patching_rect" : [ 75.0, 315.0, 85.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-38",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "gain~",
									"stripecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"presentation_rect" : [ 184.0, 2.0, 12.0, 80.0 ],
									"knobcolor" : [ 0.482353, 0.482353, 0.482353, 1.0 ],
									"patching_rect" : [ 75.0, 360.0, 12.0, 80.0 ],
									"presentation" : 1,
									"bgcolor" : [ 0.85098, 0.85098, 0.85098, 1.0 ],
									"numinlets" : 2,
									"numoutlets" : 2,
									"id" : "obj-27",
									"outlettype" : [ "signal", "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p attrArgs",
									"presentation_rect" : [ 645.0, 240.0, 379.0, 20.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 510.0, 300.0, 73.0, 20.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 5,
									"id" : "obj-24",
									"fontname" : "Arial",
									"outlettype" : [ "", "", "", "", "" ],
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
										"gridsize" : [ 5.0, 5.0 ],
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
													"text" : "prepend filter",
													"fontsize" : 12.0,
													"patching_rect" : [ 340.0, 154.370789, 83.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-37",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend noise",
													"fontsize" : 12.0,
													"patching_rect" : [ 340.0, 130.0, 89.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-36",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend freq",
													"fontsize" : 12.0,
													"patching_rect" : [ 235.0, 155.0, 81.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-34",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend wave",
													"fontsize" : 12.0,
													"patching_rect" : [ 235.0, 130.0, 88.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-33",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend file",
													"fontsize" : 12.0,
													"patching_rect" : [ 135.0, 155.0, 75.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-31",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend loop",
													"fontsize" : 12.0,
													"patching_rect" : [ 135.0, 130.0, 83.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-29",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route module vol loop file wave freq noise filter",
													"fontsize" : 12.0,
													"patching_rect" : [ 50.0, 100.0, 360.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 9,
													"id" : "obj-9",
													"fontname" : "Arial",
													"outlettype" : [ "", "", "", "", "", "", "", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"presentation_rect" : [ 585.0, 120.0, 25.0, 25.0 ],
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
													"presentation" : 1,
													"numinlets" : 0,
													"numoutlets" : 1,
													"id" : "obj-5",
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 585.0, 315.0, 25.0, 25.0 ],
													"patching_rect" : [ 50.0, 235.0, 25.0, 25.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-6",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 627.0, 315.0, 25.0, 25.0 ],
													"patching_rect" : [ 92.0, 235.0, 25.0, 25.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-8",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 665.0, 315.0, 25.0, 25.0 ],
													"patching_rect" : [ 130.0, 235.0, 25.0, 25.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-12",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 765.0, 315.0, 25.0, 25.0 ],
													"patching_rect" : [ 230.0, 235.0, 25.0, 25.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-16",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"presentation_rect" : [ 870.0, 315.0, 25.0, 25.0 ],
													"patching_rect" : [ 335.0, 235.0, 25.0, 25.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-23",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-9", 1 ],
													"destination" : [ "obj-8", 0 ],
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
													"source" : [ "obj-9", 7 ],
													"destination" : [ "obj-37", 0 ],
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
													"source" : [ "obj-9", 5 ],
													"destination" : [ "obj-34", 0 ],
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
													"source" : [ "obj-9", 3 ],
													"destination" : [ "obj-31", 0 ],
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
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-9", 0 ],
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
													"source" : [ "obj-36", 0 ],
													"destination" : [ "obj-23", 0 ],
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
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-16", 0 ],
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
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-12", 0 ],
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
									"maxclass" : "button",
									"presentation_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"patching_rect" : [ 400.0, 114.814606, 20.0, 20.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-20",
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "patcherargs @module 0 @vol -20 @loop 0 @file 2 @wave 0 @freq 440 @noise 0 @filter 0",
									"linecount" : 9,
									"presentation_linecount" : 9,
									"presentation_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 400.0, 140.000031, 77.0, 131.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "fourth",
									"presentation_rect" : [ 4.0, 22.0, 175.0, 66.741623 ],
									"args" : [  ],
									"patching_rect" : [ 645.0, 385.000031, 110.0, 61.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-3",
									"outlettype" : [ "signal" ],
									"embed" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
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
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route noise filter",
													"fontsize" : 12.0,
													"patching_rect" : [ 25.0, 55.0, 98.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 3,
													"id" : "obj-11",
													"fontname" : "Arial",
													"outlettype" : [ "", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl slice 1",
													"fontsize" : 12.0,
													"patching_rect" : [ 225.0, 215.0, 58.0, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 2,
													"id" : "obj-6",
													"fontname" : "Arial",
													"outlettype" : [ "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "filtergraph~",
													"dbdisplay" : 0,
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"domain" : [ 0.0, 22050.0 ],
													"patching_rect" : [ 225.0, 245.0, 140.0, 45.0 ],
													"presentation" : 1,
													"bgcolor" : [ 0.941176, 0.941176, 0.941176, 0.4 ],
													"numinlets" : 8,
													"range" : [ 0.0, 16.0 ],
													"numoutlets" : 7,
													"id" : "obj-4",
													"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
													"fgcolor" : [ 0.941176, 0.941176, 0.941176, 0.0 ],
													"nfilters" : 1,
													"setfilter" : [ 0, 9, 1, 0, 0, 23.787561, 1.49664, 0.707107, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 5.0, 25.0, 169.0, 36.0 ],
													"logfreq" : 1,
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"patching_rect" : [ 80.0, 350.0, 137.0, 45.0 ],
													"presentation" : 1,
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"numinlets" : 2,
													"rounded" : 1,
													"numoutlets" : 1,
													"id" : "obj-14",
													"outlettype" : [ "" ],
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1",
													"fontsize" : 12.0,
													"patching_rect" : [ 30.0, 160.0, 78.0, 18.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-13",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 4.0, 1.666667, 96.0, 20.0 ],
													"fontsize" : 12.0,
													"types" : [  ],
													"patching_rect" : [ 30.0, 125.0, 105.0, 20.0 ],
													"presentation" : 1,
													"items" : [ "Noise:", "white", ",", "Noise:", "pink" ],
													"numinlets" : 1,
													"numoutlets" : 3,
													"id" : "obj-10",
													"fontname" : "Arial",
													"outlettype" : [ "int", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 2 1 1.",
													"fontsize" : 12.0,
													"patching_rect" : [ 30.0, 270.0, 86.0, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 2,
													"id" : "obj-9",
													"fontname" : "Arial",
													"outlettype" : [ "signal", "list" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pink~",
													"fontsize" : 12.0,
													"patching_rect" : [ 145.0, 210.0, 40.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-8",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "biquad~",
													"fontsize" : 12.0,
													"patching_rect" : [ 30.0, 315.0, 86.5, 20.0 ],
													"numinlets" : 6,
													"numoutlets" : 1,
													"id" : "obj-5",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 102.0, 2.0, 72.0, 20.0 ],
													"fontsize" : 11.595187,
													"types" : [  ],
													"patching_rect" : [ 225.0, 185.0, 120.0, 20.0 ],
													"presentation" : 1,
													"items" : [ "Filter:", "allpass", ",", "Filter:", "lowpass", ",", "Filter:", "highpass", ",", "Filter:", "bandpass", ",", "Filter:", "bandstop", ",", "Filter:", "peaknotch", ",", "Filter:", "lowshelf", ",", "Filter:", "highshelf", ",", "Filter:", "resonant", ",", "Filter:", "display" ],
													"numinlets" : 1,
													"numoutlets" : 3,
													"id" : "obj-47",
													"fontname" : "Arial",
													"outlettype" : [ "int", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontsize" : 12.0,
													"patching_rect" : [ 60.0, 210.0, 47.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-3",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 30.0, 360.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"patching_rect" : [ 25.0, 15.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"id" : "obj-1",
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-5", 0 ],
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
													"source" : [ "obj-6", 1 ],
													"destination" : [ "obj-4", 0 ],
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
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-14", 0 ],
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
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-5", 1 ],
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
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-9", 0 ],
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
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-10", 0 ],
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
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-11", 0 ],
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
									"fontsize" : 12.0,
									"types" : [  ],
									"patching_rect" : [ 75.0, 128.736938, 179.0, 20.0 ],
									"presentation" : 1,
									"items" : [ "Source:", "Sound", "File", ",", "Source:", "Oscillator", ",", "Source:", "ADC", "(input)", ",", "Source:", "Noise" ],
									"numinlets" : 1,
									"rounded" : 0,
									"numoutlets" : 3,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "int", "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : ";\rmax refresh",
									"linecount" : 2,
									"presentation_linecount" : 2,
									"presentation_rect" : [ 70.0, 230.0, 74.0, 32.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 435.0, 60.0, 80.500031, 32.0 ],
									"presentation" : 1,
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-10",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p manageDisplay",
									"presentation_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 75.0, 162.000031, 106.0, 20.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-11",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
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
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1]",
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 3",
													"fontsize" : 11.595187,
													"patching_rect" : [ 435.0, 100.0, 32.5, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-3",
													"fontname" : "Arial",
													"outlettype" : [ "int" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox fourth hidden $1",
													"linecount" : 2,
													"fontsize" : 11.595187,
													"patching_rect" : [ 435.0, 151.0, 96.0, 31.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-4",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox first hidden $1",
													"linecount" : 2,
													"fontsize" : 11.595187,
													"patching_rect" : [ 51.0, 151.0, 89.0, 31.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-28",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox second hidden $1",
													"linecount" : 2,
													"fontsize" : 11.595187,
													"patching_rect" : [ 177.0, 151.0, 105.0, 31.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-29",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 2",
													"fontsize" : 11.595187,
													"patching_rect" : [ 313.0, 100.0, 32.5, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-31",
													"fontname" : "Arial",
													"outlettype" : [ "int" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 1",
													"fontsize" : 11.595187,
													"patching_rect" : [ 177.0, 100.0, 32.5, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-32",
													"fontname" : "Arial",
													"outlettype" : [ "int" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!= 0",
													"fontsize" : 11.595187,
													"patching_rect" : [ 51.0, 100.0, 32.5, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-33",
													"fontname" : "Arial",
													"outlettype" : [ "int" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "script sendbox third hidden $1",
													"linecount" : 2,
													"fontsize" : 11.595187,
													"patching_rect" : [ 313.0, 151.0, 90.0, 31.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-34",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"patching_rect" : [ 257.0, 30.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"id" : "obj-1",
													"outlettype" : [ "int" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 257.0, 240.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-2",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 0 ],
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
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-28", 0 ],
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
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-34", 0 ],
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
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-2", 0 ],
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
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-33", 0 ],
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
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "[1][1][1][3][1][1][3][2][1][1][1][1][1][2][3][3][1][1][1][1]",
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
									"maxclass" : "message",
									"text" : "clear, $1 0 1",
									"presentation_rect" : [ 192.454483, 163.77652, 78.0, 18.0 ],
									"fontsize" : 12.0,
									"patching_rect" : [ 75.0, 240.0, 78.0, 18.0 ],
									"presentation" : 1,
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-13",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "thispatcher",
									"presentation_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"fontsize" : 11.595187,
									"patching_rect" : [ 75.0, 195.000031, 69.0, 20.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-30",
									"fontname" : "Arial",
									"outlettype" : [ "", "" ],
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"presentation_rect" : [ 80.0, 460.629211, 25.0, 25.0 ],
									"patching_rect" : [ 75.0, 450.0, 25.0, 25.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-17",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "matrix~ 4 1 1. @ramp 200",
									"presentation_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"fontsize" : 11.595187,
									"patching_rect" : [ 270.0, 465.0, 394.0, 20.0 ],
									"presentation" : 1,
									"numinlets" : 4,
									"numoutlets" : 2,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "list" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"varname" : "third",
									"presentation_rect" : [ 4.0, 22.0, 179.481781, 66.0 ],
									"args" : [  ],
									"patching_rect" : [ 520.0, 385.000031, 106.0, 61.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-26",
									"hidden" : 1,
									"outlettype" : [ "signal" ],
									"embed" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
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
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontsize" : 12.0,
													"patching_rect" : [ 40.0, 61.0, 74.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-8",
													"fontname" : "Arial",
													"hidden" : 1,
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Input Channel:",
													"presentation_rect" : [ 5.0, 3.0, 89.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 89.0, 95.0, 150.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-6",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 39.0, 388.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-9",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "spectroscope~",
													"presentation_rect" : [ 8.0, 25.0, 163.0, 35.0 ],
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"markercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"patching_rect" : [ 59.0, 219.0, 137.0, 45.0 ],
													"presentation" : 1,
													"bgcolor" : [ 0.576471, 0.576471, 0.576471, 0.458824 ],
													"numinlets" : 2,
													"rounded" : 1,
													"numoutlets" : 1,
													"id" : "obj-4",
													"outlettype" : [ "" ],
													"fgcolor" : [ 0.513726, 0.784314, 0.901961, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "adc~",
													"fontsize" : 11.595187,
													"patching_rect" : [ 39.0, 153.0, 35.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 2,
													"id" : "obj-18",
													"fontname" : "Arial",
													"outlettype" : [ "signal", "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"patching_rect" : [ 3.0, 7.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"id" : "obj-3",
													"hidden" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "set $1 1",
													"fontsize" : 12.0,
													"patching_rect" : [ 39.0, 128.0, 54.0, 18.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-1",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "number",
													"presentation_rect" : [ 95.0, 3.0, 48.0, 18.0 ],
													"fontsize" : 10.0,
													"patching_rect" : [ 39.0, 98.0, 48.0, 18.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 2,
													"id" : "obj-2",
													"fontname" : "Arial",
													"outlettype" : [ "int", "bang" ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
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
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
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
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-18", 0 ],
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
									"args" : [  ],
									"patching_rect" : [ 394.714111, 385.000031, 106.0, 61.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-21",
									"hidden" : 1,
									"outlettype" : [ "signal" ],
									"embed" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
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
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "tab",
													"presentation_rect" : [ 50.0, 5.0, 116.0, 16.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 35.0, 280.0, 116.0, 16.0 ],
													"tabs" : [ "sin", "tri", "rect", "noise" ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 3,
													"id" : "obj-28",
													"fontname" : "Arial",
													"outlettype" : [ "int", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route wave freq",
													"fontsize" : 12.0,
													"patching_rect" : [ 54.833344, 110.0, 96.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 3,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 440",
													"fontsize" : 12.0,
													"patching_rect" : [ 405.0, 195.0, 110.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 2,
													"id" : "obj-12",
													"fontname" : "Arial",
													"outlettype" : [ "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 1000",
													"fontsize" : 12.0,
													"patching_rect" : [ 167.241211, 484.947357, 48.0, 18.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-36",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 0",
													"fontsize" : 12.0,
													"patching_rect" : [ 167.241211, 453.947357, 37.0, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 2,
													"id" : "obj-34",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 500",
													"fontsize" : 12.0,
													"patching_rect" : [ 275.241211, 397.947357, 87.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-32",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "ms",
													"presentation_rect" : [ 152.907867, 43.0, 27.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 568.241211, 120.947357, 27.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-31",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Hz",
													"presentation_rect" : [ 92.0, 22.0, 26.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 215.241211, 66.947357, 26.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-30",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 109.0, 43.0, 45.0, 18.0 ],
													"bordercolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
													"fontsize" : 10.0,
													"patching_rect" : [ 274.333344, 425.947357, 45.0, 18.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 2,
													"id" : "obj-26",
													"fontname" : "Arial",
													"outlettype" : [ "float", "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Speed:",
													"presentation_rect" : [ 62.907867, 43.0, 50.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 400.241211, 125.947357, 50.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-25",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 46.0, 44.0, 17.0, 17.0 ],
													"patching_rect" : [ 227.241211, 412.947357, 17.0, 17.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-24",
													"outlettype" : [ "int" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Pulse:",
													"presentation_rect" : [ 2.0, 43.0, 45.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 400.241211, 82.947357, 45.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-22",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #1",
													"fontsize" : 12.0,
													"patching_rect" : [ 51.241211, 250.947357, 81.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-21",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess #2",
													"fontsize" : 12.0,
													"patching_rect" : [ 268.241211, 89.947357, 81.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-19",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"presentation_rect" : [ 46.0, 22.0, 47.0, 18.0 ],
													"fontsize" : 10.0,
													"patching_rect" : [ 155.241211, 67.947357, 47.0, 18.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 2,
													"id" : "obj-18",
													"fontname" : "Arial",
													"outlettype" : [ "float", "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Freq:",
													"presentation_rect" : [ 2.0, 22.0, 39.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 155.241211, 25.947357, 39.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-16",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Wave:",
													"presentation_rect" : [ 2.0, 1.0, 46.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 91.241211, 25.947357, 46.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-15",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "1 5 0.2 10 0 100",
													"fontsize" : 12.0,
													"patching_rect" : [ 226.241211, 484.947357, 100.0, 18.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-14",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "metro 500",
													"fontsize" : 12.0,
													"patching_rect" : [ 227.241211, 453.947357, 66.0, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-5",
													"fontname" : "Arial",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "line~ 1",
													"fontsize" : 11.595187,
													"patching_rect" : [ 167.333344, 519.0, 46.0, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 2,
													"id" : "obj-4",
													"fontname" : "Arial",
													"outlettype" : [ "signal", "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "*~",
													"fontsize" : 11.595187,
													"patching_rect" : [ 152.333344, 571.0, 32.5, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-2",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, $1 0 1 500",
													"fontsize" : 12.0,
													"patching_rect" : [ 51.333344, 319.0, 103.0, 18.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-13",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "noise~",
													"fontsize" : 11.595187,
													"patching_rect" : [ 216.333313, 330.0, 46.0, 20.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-11",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "rect~ 440",
													"fontsize" : 11.595187,
													"patching_rect" : [ 195.0, 290.0, 61.0, 20.0 ],
													"numinlets" : 3,
													"numoutlets" : 1,
													"id" : "obj-10",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "tri~ 440",
													"fontsize" : 11.595187,
													"patching_rect" : [ 173.666687, 260.0, 51.0, 20.0 ],
													"numinlets" : 3,
													"numoutlets" : 1,
													"id" : "obj-9",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "cycle~ 440",
													"fontsize" : 11.595187,
													"patching_rect" : [ 152.333344, 224.0, 68.0, 20.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-8",
													"fontname" : "Arial",
													"outlettype" : [ "signal" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "matrix~ 4 1 1.",
													"fontsize" : 11.595187,
													"patching_rect" : [ 152.333344, 378.0, 83.0, 20.0 ],
													"numinlets" : 4,
													"numoutlets" : 2,
													"id" : "obj-7",
													"fontname" : "Arial",
													"outlettype" : [ "signal", "list" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 152.333344, 615.947388, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"patching_rect" : [ 64.241211, 13.947357, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"id" : "obj-3",
													"hidden" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-9", 0 ],
													"destination" : [ "obj-7", 1 ],
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
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-2", 0 ],
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
													"source" : [ "obj-4", 0 ],
													"destination" : [ "obj-2", 1 ],
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
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-36", 0 ],
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
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-17", 0 ],
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
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-5", 1 ],
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
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-34", 0 ],
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
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-1", 0 ],
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
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-9", 0 ],
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
													"destination" : [ "obj-10", 0 ],
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
													"source" : [ "obj-17", 1 ],
													"destination" : [ "obj-18", 0 ],
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
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-7", 0 ],
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
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-7", 2 ],
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
									"args" : [  ],
									"patching_rect" : [ 269.714111, 385.000031, 106.0, 61.0 ],
									"presentation" : 1,
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-22",
									"hidden" : 1,
									"outlettype" : [ "signal" ],
									"embed" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
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
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 1",
													"fontsize" : 10.0,
													"patching_rect" : [ 210.0, 20.0, 62.0, 18.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-18",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "toggle",
													"presentation_rect" : [ 157.0, 44.0, 17.0, 17.0 ],
													"patching_rect" : [ 205.0, 50.0, 20.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-7",
													"outlettype" : [ "int" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "p folderOrSoundFile",
													"fontsize" : 10.0,
													"patching_rect" : [ 39.0, 181.0, 100.0, 18.0 ],
													"numinlets" : 2,
													"numoutlets" : 2,
													"id" : "obj-27",
													"fontname" : "Arial",
													"outlettype" : [ "", "" ],
													"patcher" : 													{
														"fileversion" : 1,
														"appversion" : 														{
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
														"boxes" : [ 															{
																"box" : 																{
																	"maxclass" : "comment",
																	"text" : "fill the menu if it's a folder",
																	"fontsize" : 12.0,
																	"patching_rect" : [ 108.0, 323.0, 150.0, 20.0 ],
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"id" : "obj-2",
																	"fontname" : "Arial"
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "t s 1",
																	"fontsize" : 10.0,
																	"patching_rect" : [ 211.0, 100.0, 32.5, 18.0 ],
																	"numinlets" : 1,
																	"numoutlets" : 2,
																	"id" : "obj-20",
																	"fontname" : "Arial",
																	"outlettype" : [ "", "int" ]
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "2",
																	"fontsize" : 10.0,
																	"patching_rect" : [ 211.0, 166.0, 32.5, 18.0 ],
																	"numinlets" : 2,
																	"numoutlets" : 1,
																	"id" : "obj-19",
																	"fontname" : "Arial",
																	"outlettype" : [ "int" ]
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "gate 2",
																	"fontsize" : 10.0,
																	"patching_rect" : [ 50.0, 205.0, 38.0, 18.0 ],
																	"numinlets" : 2,
																	"numoutlets" : 2,
																	"id" : "obj-18",
																	"fontname" : "Arial",
																	"outlettype" : [ "", "" ]
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "message",
																	"text" : "prefix $1, insert 0 Browse..., insert 1 <separator>",
																	"fontsize" : 12.0,
																	"patching_rect" : [ 69.0, 238.0, 270.0, 18.0 ],
																	"numinlets" : 2,
																	"numoutlets" : 1,
																	"id" : "obj-7",
																	"fontname" : "Arial",
																	"outlettype" : [ "" ]
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "newobj",
																	"text" : "sel fold",
																	"fontsize" : 10.0,
																	"patching_rect" : [ 211.0, 140.0, 42.0, 18.0 ],
																	"numinlets" : 1,
																	"numoutlets" : 2,
																	"id" : "obj-4",
																	"fontname" : "Arial",
																	"outlettype" : [ "bang", "" ]
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 300.0, 170.0, 25.0, 25.0 ],
																	"patching_rect" : [ 69.0, 40.0, 25.0, 25.0 ],
																	"presentation" : 1,
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"id" : "obj-23",
																	"outlettype" : [ "" ],
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "inlet",
																	"presentation_rect" : [ 442.0, 170.0, 25.0, 25.0 ],
																	"patching_rect" : [ 211.0, 40.0, 25.0, 25.0 ],
																	"presentation" : 1,
																	"numinlets" : 0,
																	"numoutlets" : 1,
																	"id" : "obj-24",
																	"outlettype" : [ "" ],
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 281.0, 446.0, 25.0, 25.0 ],
																	"patching_rect" : [ 50.0, 316.0, 25.0, 25.0 ],
																	"presentation" : 1,
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"id" : "obj-25",
																	"comment" : ""
																}

															}
, 															{
																"box" : 																{
																	"maxclass" : "outlet",
																	"presentation_rect" : [ 300.0, 446.0, 25.0, 25.0 ],
																	"patching_rect" : [ 69.0, 316.0, 25.0, 25.0 ],
																	"presentation" : 1,
																	"numinlets" : 1,
																	"numoutlets" : 0,
																	"id" : "obj-26",
																	"comment" : ""
																}

															}
 ],
														"lines" : [ 															{
																"patchline" : 																{
																	"source" : [ "obj-7", 0 ],
																	"destination" : [ "obj-26", 0 ],
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
																	"source" : [ "obj-24", 0 ],
																	"destination" : [ "obj-20", 0 ],
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
																	"source" : [ "obj-20", 0 ],
																	"destination" : [ "obj-4", 0 ],
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
																	"source" : [ "obj-19", 0 ],
																	"destination" : [ "obj-18", 0 ],
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
																	"source" : [ "obj-18", 0 ],
																	"destination" : [ "obj-25", 0 ],
																	"hidden" : 0,
																	"midpoints" : [  ]
																}

															}
 ]
													}
,
													"saved_object_attributes" : 													{
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
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "route loop file",
													"fontsize" : 10.0,
													"patching_rect" : [ 15.0, 45.0, 72.0, 18.0 ],
													"numinlets" : 1,
													"numoutlets" : 3,
													"id" : "obj-16",
													"fontname" : "Arial",
													"outlettype" : [ "", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "patcherargs 0 2",
													"fontsize" : 10.0,
													"patching_rect" : [ 350.0, 55.0, 82.0, 18.0 ],
													"numinlets" : 1,
													"numoutlets" : 2,
													"id" : "obj-15",
													"fontname" : "Arial",
													"outlettype" : [ "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "regexp .*(Browse...) @substitute open",
													"linecount" : 2,
													"fontsize" : 12.0,
													"patching_rect" : [ 125.0, 256.0, 121.0, 34.0 ],
													"numinlets" : 1,
													"numoutlets" : 5,
													"id" : "obj-13",
													"fontname" : "Arial",
													"outlettype" : [ "", "", "", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "dropfile",
													"presentation_rect" : [ -5.0, 0.0, 174.683014, 62.542229 ],
													"border" : 0.0,
													"types" : [  ],
													"patching_rect" : [ 39.0, 111.0, 100.0, 35.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"ignoreclick" : 1,
													"numoutlets" : 2,
													"id" : "obj-12",
													"outlettype" : [ "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "prefix ./examples/sounds/, insert 0 Browse..., insert 1 <separator>, $1",
													"fontsize" : 12.0,
													"patching_rect" : [ 148.0, 181.0, 391.0, 18.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-14",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "loop $1",
													"fontsize" : 12.0,
													"patching_rect" : [ 205.0, 76.0, 51.0, 18.0 ],
													"numinlets" : 2,
													"numoutlets" : 1,
													"id" : "obj-8",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sfplay~",
													"fontsize" : 11.0,
													"patching_rect" : [ 20.0, 375.0, 47.0, 19.0 ],
													"numinlets" : 2,
													"numoutlets" : 2,
													"id" : "obj-11",
													"fontname" : "Arial",
													"outlettype" : [ "signal", "bang" ],
													"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "or Drag a Sound file Here.",
													"presentation_rect" : [ 12.0, 24.0, 161.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 474.0, 91.0, 154.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-10",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "File:",
													"presentation_rect" : [ 1.0, 4.0, 34.0, 20.0 ],
													"fontsize" : 12.0,
													"patching_rect" : [ 470.0, 61.0, 34.0, 20.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-9",
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"fontsize" : 11.0,
													"patching_rect" : [ 201.5, 333.0, 78.0, 19.0 ],
													"numinlets" : 1,
													"numoutlets" : 1,
													"id" : "obj-6",
													"fontname" : "Arial",
													"outlettype" : [ "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "umenu",
													"presentation_rect" : [ 31.0, 4.0, 142.64183, 20.0 ],
													"fontsize" : 12.0,
													"types" : [  ],
													"patching_rect" : [ 148.0, 212.0, 100.0, 20.0 ],
													"presentation" : 1,
													"items" : [ "Browse...", ",", "<separator>", ",", "anton.aif", ",", "cello-f2.aif", ",", "cherokee.aif", ",", "drumLoop.aif", ",", "jongly.aif", ",", "rainstick.aif", ",", "sho0630.aif", ",", "vibes-a1.aif" ],
													"numinlets" : 1,
													"autopopulate" : 1,
													"numoutlets" : 3,
													"prefix" : "Macintosh HD:/Applications/Max5/examples/sounds/",
													"id" : "obj-5",
													"fontname" : "Arial",
													"outlettype" : [ "int", "", "" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "playbar",
													"presentation_rect" : [ 5.620921, 45.0, 154.179749, 15.0 ],
													"patching_rect" : [ 19.0, 76.0, 176.0, 23.0 ],
													"presentation" : 1,
													"numinlets" : 1,
													"numoutlets" : 2,
													"id" : "obj-2",
													"outlettype" : [ "", "int" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"patching_rect" : [ 20.0, 415.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"id" : "obj-1",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"patching_rect" : [ 15.0, 5.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"id" : "obj-3",
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "panel",
													"presentation_rect" : [ 5.0, 44.0, 169.683014, 17.683012 ],
													"patching_rect" : [ 433.0, 224.0, 128.0, 128.0 ],
													"presentation" : 1,
													"bgcolor" : [ 0.5, 0.5, 0.5, 1.0 ],
													"numinlets" : 1,
													"rounded" : 0,
													"numoutlets" : 0,
													"id" : "obj-17"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-8", 0 ],
													"destination" : [ "obj-2", 0 ],
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
													"source" : [ "obj-7", 0 ],
													"destination" : [ "obj-8", 0 ],
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
													"source" : [ "obj-5", 1 ],
													"destination" : [ "obj-13", 0 ],
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
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-6", 0 ],
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
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-11", 0 ],
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
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-8", 0 ],
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
													"source" : [ "obj-14", 0 ],
													"destination" : [ "obj-5", 0 ],
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
													"source" : [ "obj-13", 0 ],
													"destination" : [ "obj-11", 0 ],
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
													"source" : [ "obj-12", 1 ],
													"destination" : [ "obj-27", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
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
									"maxclass" : "newobj",
									"text" : "t f b b",
									"fontsize" : 10.0,
									"patching_rect" : [ 420.0, 225.0, 46.0, 18.0 ],
									"numinlets" : 1,
									"numoutlets" : 3,
									"id" : "obj-56",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontsize" : 10.0,
									"patching_rect" : [ 315.0, 165.0, 32.5, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-25",
									"fontname" : "Arial",
									"outlettype" : [ "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 70.",
									"fontsize" : 10.0,
									"patching_rect" : [ 285.0, 165.0, 32.5, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-57",
									"fontname" : "Arial",
									"outlettype" : [ "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "poltocar",
									"fontsize" : 10.0,
									"patching_rect" : [ 285.0, 255.0, 49.0, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 2,
									"id" : "obj-19",
									"fontname" : "Arial",
									"outlettype" : [ "float", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "65",
									"fontsize" : 10.0,
									"patching_rect" : [ 285.0, 225.0, 32.5, 16.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-18",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cartopol",
									"fontsize" : 10.0,
									"patching_rect" : [ 285.0, 195.0, 48.0, 18.0 ],
									"numinlets" : 2,
									"numoutlets" : 2,
									"id" : "obj-15",
									"fontname" : "Arial",
									"outlettype" : [ "float", "float" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf clear",
									"fontsize" : 11.595187,
									"patching_rect" : [ 570.0, 180.0, 70.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sprintf frameoval 5 5 135 135 255",
									"fontsize" : 11.595187,
									"patching_rect" : [ 555.0, 210.0, 183.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-28",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontsize" : 11.595187,
									"patching_rect" : [ 435.0, 300.0, 33.0, 20.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-58",
									"fontname" : "Arial",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 73",
									"fontsize" : 11.595187,
									"patching_rect" : [ 374.0, 300.0, 33.0, 20.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-32",
									"fontname" : "Arial",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontsize" : 11.595187,
									"patching_rect" : [ 315.0, 300.0, 33.0, 20.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-33",
									"fontname" : "Arial",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 67",
									"fontsize" : 11.595187,
									"patching_rect" : [ 270.0, 304.0, 33.0, 20.0 ],
									"numinlets" : 2,
									"numoutlets" : 1,
									"id" : "obj-34",
									"fontname" : "Arial",
									"outlettype" : [ "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pack 0 0 0 0 255",
									"fontsize" : 11.595187,
									"patching_rect" : [ 270.0, 345.0, 96.0, 20.0 ],
									"numinlets" : 5,
									"numoutlets" : 1,
									"id" : "obj-35",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend paintoval",
									"fontsize" : 11.595187,
									"patching_rect" : [ 270.0, 375.0, 103.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-36",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack",
									"fontsize" : 11.595187,
									"patching_rect" : [ 285.0, 135.0, 48.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-37",
									"fontname" : "Arial",
									"outlettype" : [ "int", "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 70 70",
									"fontsize" : 12.0,
									"patching_rect" : [ 60.0, 45.0, 95.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-31",
									"fontname" : "Arial",
									"outlettype" : [ "" ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-27", 0 ],
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
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-13", 0 ],
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
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-35", 3 ],
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
									"source" : [ "obj-56", 1 ],
									"destination" : [ "obj-28", 0 ],
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
									"source" : [ "obj-56", 0 ],
									"destination" : [ "obj-18", 0 ],
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
									"source" : [ "obj-38", 0 ],
									"destination" : [ "obj-27", 0 ],
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
									"source" : [ "obj-37", 1 ],
									"destination" : [ "obj-25", 0 ],
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
									"source" : [ "obj-34", 0 ],
									"destination" : [ "obj-35", 0 ],
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
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-35", 2 ],
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
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-8", 3 ],
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
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-17", 0 ],
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
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-15", 1 ],
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
									"source" : [ "obj-24", 4 ],
									"destination" : [ "obj-3", 0 ],
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
									"source" : [ "obj-24", 3 ],
									"destination" : [ "obj-21", 0 ],
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
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-8", 1 ],
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
									"source" : [ "obj-19", 1 ],
									"destination" : [ "obj-58", 0 ],
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
									"destination" : [ "obj-33", 0 ],
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
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-19", 0 ],
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
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-30", 0 ],
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
					"maxclass" : "hoa.meter~",
					"ls_angles" : [ 0.0, 22.0, 45.0, 67.0, 90.0, 112.0, 135.0, 157.0, 180.0, 202.0, 225.0, 247.0, 270.0, 292.0, 315.0, 337.5 ],
					"tepidcolor" : [ 0.6, 0.729412, 0.0, 1.0 ],
					"patching_rect" : [ 30.0, 346.0, 244.0, 244.0 ],
					"energycolor" : [ 0.0, 0.054688, 0.875, 1.0 ],
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"numinlets" : 16,
					"numoutlets" : 0,
					"id" : "obj-4",
					"ls" : 16
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"fontsize" : 11.595187,
					"patching_rect" : [ 30.0, 256.0, 243.5, 20.0 ],
					"numinlets" : 2,
					"numoutlets" : 15,
					"id" : "obj-20",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.pi 2",
					"fontsize" : 11.595187,
					"patching_rect" : [ 270.0, 201.0, 52.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-14",
					"fontname" : "Arial",
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "*~",
					"fontsize" : 11.595187,
					"patching_rect" : [ 255.0, 226.0, 33.5, 20.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-15",
					"fontname" : "Arial",
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0.1",
					"fontsize" : 11.595187,
					"patching_rect" : [ 255.0, 125.0, 79.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-16",
					"fontname" : "Arial",
					"hidden" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 11.595187,
					"patching_rect" : [ 255.0, 145.0, 50.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-17",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "phasor~ 0.1",
					"fontsize" : 11.595187,
					"patching_rect" : [ 255.0, 171.0, 72.0, 20.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-18",
					"fontname" : "Arial",
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.dac~ 1:16",
					"fontsize" : 11.595187,
					"patching_rect" : [ 30.0, 591.0, 243.5, 20.0 ],
					"numinlets" : 16,
					"numoutlets" : 0,
					"id" : "obj-69",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.decoder~ 7 16",
					"fontsize" : 11.595187,
					"patching_rect" : [ 30.0, 306.0, 243.5, 20.0 ],
					"numinlets" : 15,
					"numoutlets" : 16,
					"id" : "obj-74",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"fontsize" : 11.595187,
					"patching_rect" : [ 444.5, 511.0, 34.5, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-9",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "startwindow",
					"fontsize" : 11.595187,
					"patching_rect" : [ 405.0, 481.0, 74.0, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-11",
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p key32",
					"fontsize" : 11.595187,
					"patching_rect" : [ 642.0, 79.0, 51.0, 20.0 ],
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
					"patching_rect" : [ 642.0, 101.0, 99.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-10",
					"fontname" : "Arial",
					"hidden" : 1,
					"saved_object_attributes" : 					{
						"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "|---\n|\n|\n|---\n|\n|\n|---\n|\n|\n|---\n|\n|\n|---",
					"linecount" : 13,
					"fontsize" : 11.595187,
					"patching_rect" : [ 598.5, 348.5, 27.0, 180.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-5",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "| dblclick to see more",
					"fontsize" : 11.595187,
					"patching_rect" : [ 598.5, 329.5, 119.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-37",
					"fontname" : "Arial"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-69", 15 ],
					"hidden" : 0,
					"midpoints" : [ 454.0, 586.0, 264.0, 586.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 0 ],
					"destination" : [ "obj-69", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 1 ],
					"destination" : [ "obj-69", 1 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 2 ],
					"destination" : [ "obj-69", 2 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 3 ],
					"destination" : [ "obj-69", 3 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 4 ],
					"destination" : [ "obj-69", 4 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 5 ],
					"destination" : [ "obj-69", 5 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 6 ],
					"destination" : [ "obj-69", 6 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 7 ],
					"destination" : [ "obj-69", 7 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 8 ],
					"destination" : [ "obj-69", 8 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 9 ],
					"destination" : [ "obj-69", 9 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 10 ],
					"destination" : [ "obj-69", 10 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 11 ],
					"destination" : [ "obj-69", 11 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 12 ],
					"destination" : [ "obj-69", 12 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 13 ],
					"destination" : [ "obj-69", 13 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 14 ],
					"destination" : [ "obj-69", 14 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 15 ],
					"destination" : [ "obj-69", 15 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 1 ],
					"destination" : [ "obj-4", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 2 ],
					"destination" : [ "obj-4", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 3 ],
					"destination" : [ "obj-4", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 4 ],
					"destination" : [ "obj-4", 4 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 5 ],
					"destination" : [ "obj-4", 5 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 6 ],
					"destination" : [ "obj-4", 6 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 7 ],
					"destination" : [ "obj-4", 7 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 8 ],
					"destination" : [ "obj-4", 8 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 9 ],
					"destination" : [ "obj-4", 9 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 10 ],
					"destination" : [ "obj-4", 10 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 11 ],
					"destination" : [ "obj-4", 11 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 12 ],
					"destination" : [ "obj-4", 12 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 13 ],
					"destination" : [ "obj-4", 13 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 14 ],
					"destination" : [ "obj-4", 14 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 15 ],
					"destination" : [ "obj-4", 15 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"midpoints" : [ 651.5, 100.0, 651.5, 100.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-4", 15 ],
					"hidden" : 0,
					"midpoints" : [ 489.5, 343.0, 264.5, 343.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-4", 15 ],
					"hidden" : 0,
					"midpoints" : [ 354.5, 343.0, 264.5, 343.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-74", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 1 ],
					"destination" : [ "obj-74", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 2 ],
					"destination" : [ "obj-74", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 3 ],
					"destination" : [ "obj-74", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 4 ],
					"destination" : [ "obj-74", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 5 ],
					"destination" : [ "obj-74", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 6 ],
					"destination" : [ "obj-74", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 7 ],
					"destination" : [ "obj-74", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 8 ],
					"destination" : [ "obj-74", 8 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 9 ],
					"destination" : [ "obj-74", 9 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 10 ],
					"destination" : [ "obj-74", 10 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 11 ],
					"destination" : [ "obj-74", 11 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 12 ],
					"destination" : [ "obj-74", 12 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 13 ],
					"destination" : [ "obj-74", 13 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 14 ],
					"destination" : [ "obj-74", 14 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-20", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-15", 1 ],
					"hidden" : 0,
					"midpoints" : [ 279.5, 222.0, 279.0, 222.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-36", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-69", 15 ],
					"hidden" : 0,
					"midpoints" : [ 414.5, 586.0, 264.0, 586.0 ]
				}

			}
 ]
	}

}
