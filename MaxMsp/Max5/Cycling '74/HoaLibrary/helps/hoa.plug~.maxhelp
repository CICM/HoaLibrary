{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 26.0, 51.0, 1037.0, 679.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 26.0, 51.0, 1037.0, 679.0 ],
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
					"text" : "p operators",
					"numinlets" : 0,
					"patching_rect" : [ 692.0, 381.0, 71.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-1",
					"fontname" : "Arial",
					"textcolor" : [ 0.209184, 0.209184, 0.209184, 1.0 ],
					"color" : [ 0.734694, 0.734694, 0.734694, 1.0 ],
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 1037.0, 653.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 1037.0, 653.0 ],
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
									"maxclass" : "tab",
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"border" : 1,
									"numinlets" : 1,
									"button" : 1,
									"patching_rect" : [ 10.0, 135.0, 944.0, 359.0 ],
									"spacing_x" : 20.0,
									"margin" : 0,
									"numoutlets" : 3,
									"id" : "obj-25",
									"fontname" : "Arial",
									"rounded" : 6.0,
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"spacing_y" : 5.0,
									"tabs" : [ "hoa.abs~", "hoa.all", "hoa.amp~", "hoa.div~", "hoa.equals~", "hoa.greaterthan~", "hoa.greaterthaneq~", "hoa.highpass~", "hoa.lessthan~", "hoa.lessthaneq~", "hoa.minus~", "hoa.modulo~", "hoa.name1~", "hoa.name2~", "hoa.notequals~", "hoa.nothing~", "hoa.onepole~", "hoa.plus~", "hoa.plusequals~", "hoa.rdiv~", "hoa.receive", "hoa.receive~", "hoa.rminus~", "hoa.send", "hoa.send~", "hoa.snapshot~", "hoa.times~" ],
									"outlettype" : [ "int", "", "" ],
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend help",
									"numinlets" : 1,
									"patching_rect" : [ 472.5, 508.0, 92.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-5",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "pcontrol",
									"numinlets" : 1,
									"patching_rect" : [ 472.5, 544.0, 60.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-4",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
									"linecount" : 2,
									"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 559.0, 19.5, 257.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-36",
									"fontname" : "Arial",
									"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"patching_rect" : [ 559.0, 19.5, 257.0, 32.0 ],
									"numoutlets" : 0,
									"id" : "obj-37",
									"rounded" : 6,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 7.5, 483.0, 56.0 ],
									"numoutlets" : 0,
									"id" : "obj-30",
									"name" : "hoa.helpheader.maxpat",
									"args" : [ "@obj-name", "hoa.plug~", "@obj-desc", "A", "partcher", "that", "duplicates", "patcher", "for", "hoa", "process." ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 424.0, 24.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-31",
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "hoa library embed various operators and utility patches in order to make compatible some vanilla's objects with the ambisonics domain or to simply do parallel processings on signals, thanks to the hoa.plug~ object.",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 12.0, 75.5, 612.0, 34.0 ],
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 10.0, 73.5, 614.0, 35.0 ],
									"numoutlets" : 0,
									"id" : "obj-35",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.connect 7 16",
									"numinlets" : 1,
									"patching_rect" : [ 675.0, 90.0, 99.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-15",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"numinlets" : 0,
									"patching_rect" : [ 675.0, 60.0, 51.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-22",
									"fontname" : "Arial",
									"outlettype" : [ "bang" ],
									"fontsize" : 11.595187,
									"hidden" : 1,
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
													"maxclass" : "button",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 32",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-23",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "key",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
													"numoutlets" : 4,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "int", "int", "int", "int" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-21",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-21", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0
									}

								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 1 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p arguments",
					"numinlets" : 0,
					"patching_rect" : [ 677.0, 351.0, 77.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-28",
					"fontname" : "Arial",
					"textcolor" : [ 0.209184, 0.209184, 0.209184, 1.0 ],
					"color" : [ 0.734694, 0.734694, 0.734694, 1.0 ],
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 1037.0, 653.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 1037.0, 653.0 ],
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
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 32.5, 234.5, 87.0, 206.0 ],
									"numoutlets" : 1,
									"id" : "obj-11",
									"name" : "delay.maxpat",
									"outlettype" : [ "" ],
									"args" : [  ],
									"embed" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 33.0, 261.0, 87.0, 206.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 33.0, 261.0, 87.0, 206.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Open",
													"numinlets" : 1,
													"patching_rect" : [ 60.0, 210.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-2",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 4.0, 54.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend target",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 60.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-1",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 0.",
													"numinlets" : 1,
													"patching_rect" : [ 450.0, 165.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-34",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 5000",
													"numinlets" : 1,
													"patching_rect" : [ 435.0, 90.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-32",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 100",
													"numinlets" : 1,
													"patching_rect" : [ 420.0, 15.0, 85.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-31",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend rarefaction",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 270.0, 111.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-27",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend feedback",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 210.0, 103.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-25",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend delay",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 150.0, 84.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-20",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend size",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 75.0, 77.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-15",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 152.0, 82.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-22",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 390.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-14",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 5000",
													"numinlets" : 1,
													"patching_rect" : [ 630.0, 180.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-4",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 4375",
													"numinlets" : 1,
													"patching_rect" : [ 630.0, 135.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-3",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "tab",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 198.0, 37.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"id" : "obj-37",
													"fontname" : "Arial",
													"background" : 1,
													"tabs" : [ "0", "-1", "-2", "-3", "-4", "-5", "-6", "-7", "all", "1", "2", "3", "4", "5", "6", "7" ],
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 11.595187,
													"presentation_rect" : [ 15.0, 30.0, 54.0, 163.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-37", 1 ],
													"destination" : [ "obj-22", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-25", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-22", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-20", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-15", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-14", 0 ],
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
									"text" : "hoa.plug~ 7 hoa.decorrelation~ post @maxsize 44100 @delay 2000 @factor 0.5",
									"linecount" : 3,
									"numinlets" : 15,
									"patching_rect" : [ 154.320007, 387.0, 220.065018, 46.0 ],
									"numoutlets" : 15,
									"id" : "obj-9",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 728.0, 162.0, 87.0, 206.0 ],
									"numoutlets" : 1,
									"id" : "obj-18",
									"name" : "delay.maxpat",
									"outlettype" : [ "" ],
									"args" : [  ],
									"embed" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 728.0, 188.0, 87.0, 206.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 728.0, 188.0, 87.0, 206.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Open",
													"numinlets" : 1,
													"patching_rect" : [ 60.0, 210.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-2",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 4.0, 54.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend target",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 60.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-1",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 0.",
													"numinlets" : 1,
													"patching_rect" : [ 450.0, 165.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-34",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 5000",
													"numinlets" : 1,
													"patching_rect" : [ 435.0, 90.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-32",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 100",
													"numinlets" : 1,
													"patching_rect" : [ 420.0, 15.0, 85.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-31",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend rarefaction",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 270.0, 111.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-27",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend feedback",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 210.0, 103.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-25",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend delay",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 150.0, 84.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-20",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend size",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 75.0, 77.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-15",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 152.0, 82.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-22",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 390.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-14",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 5000",
													"numinlets" : 1,
													"patching_rect" : [ 630.0, 180.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-4",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 4375",
													"numinlets" : 1,
													"patching_rect" : [ 630.0, 135.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-3",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "tab",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 198.0, 37.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"id" : "obj-37",
													"fontname" : "Arial",
													"background" : 1,
													"tabs" : [ "0", "-1", "-2", "-3", "-4", "-5", "-6", "-7", "all", "1", "2", "3", "4", "5", "6", "7" ],
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 11.595187,
													"presentation_rect" : [ 15.0, 30.0, 54.0, 163.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-37", 1 ],
													"destination" : [ "obj-22", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-25", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-22", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-20", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-15", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-14", 0 ],
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
									"text" : "hoa.plug~ 7 hoa.receive~ post @name encode",
									"linecount" : 2,
									"numinlets" : 15,
									"patching_rect" : [ 411.5, 432.0, 240.821411, 33.0 ],
									"numoutlets" : 15,
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 7 hoa.send~ post @name encode",
									"linecount" : 2,
									"numinlets" : 15,
									"patching_rect" : [ 411.5, 387.0, 233.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-13",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0.",
									"numinlets" : 1,
									"patching_rect" : [ 625.5, 276.0, 86.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-1",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p sinBuffer",
									"numinlets" : 0,
									"patching_rect" : [ 768.0, 130.0, 66.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-2",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 620.0, 172.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 620.0, 172.0, 640.0, 480.0 ],
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
													"text" : "t b b",
													"numinlets" : 1,
													"patching_rect" : [ 45.0, 75.0, 34.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-2",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "bang" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadbang",
													"numinlets" : 1,
													"patching_rect" : [ 45.0, 30.0, 60.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-1",
													"fontname" : "Arial",
													"outlettype" : [ "bang" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "/ 1500.",
													"numinlets" : 2,
													"patching_rect" : [ 195.0, 135.0, 46.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-29",
													"fontname" : "Arial",
													"outlettype" : [ "float" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "uzi 1500",
													"numinlets" : 2,
													"patching_rect" : [ 105.0, 105.0, 64.0, 20.0 ],
													"numoutlets" : 3,
													"id" : "obj-28",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "bang", "int" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "expr sin(3.14159265 * $f1)",
													"numinlets" : 1,
													"patching_rect" : [ 195.0, 180.0, 147.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "sizeinsamps 1500",
													"numinlets" : 2,
													"patching_rect" : [ 45.0, 150.0, 103.0, 18.0 ],
													"numoutlets" : 1,
													"id" : "obj-16",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "peek~ livegrain",
													"numinlets" : 3,
													"patching_rect" : [ 150.0, 225.0, 108.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"fontname" : "Arial",
													"outlettype" : [ "float" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "buffer~ livegrain",
													"numinlets" : 1,
													"patching_rect" : [ 150.0, 255.0, 93.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-6",
													"fontname" : "Arial",
													"outlettype" : [ "float", "bang" ],
													"fontsize" : 11.595187
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 2 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 2 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 1 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-10", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "azimuth :",
									"numinlets" : 1,
									"patching_rect" : [ 566.75, 308.5, 58.75, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-32",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 566.75, 308.5, 58.75, 19.0 ],
									"numoutlets" : 0,
									"id" : "obj-33",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 625.5, 308.5, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-24",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 411.5, 187.0, 218.0, 87.0 ],
									"numoutlets" : 1,
									"id" : "obj-4",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ],
									"args" : [ "@module", 0, "@file", 7, "@loop", 1 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Open the different voices to see the how you can receive the arguments with the @args attribute.",
									"linecount" : 3,
									"numinlets" : 1,
									"patching_rect" : [ 662.0, 380.5, 219.0, 46.0 ],
									"numoutlets" : 0,
									"id" : "obj-5",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7",
									"numinlets" : 2,
									"patching_rect" : [ 411.5, 344.0, 233.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 662.0, 380.5, 219.0, 45.0 ],
									"numoutlets" : 0,
									"id" : "obj-7",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 153.5, 187.0, 218.0, 87.0 ],
									"numoutlets" : 1,
									"id" : "obj-3",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ],
									"args" : [ "@module", 0, "@file", 7, "@loop", 1 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
									"linecount" : 2,
									"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 559.0, 19.5, 257.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-36",
									"fontname" : "Arial",
									"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"patching_rect" : [ 559.0, 19.5, 257.0, 32.0 ],
									"numoutlets" : 0,
									"id" : "obj-37",
									"rounded" : 6,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 7.5, 483.0, 56.0 ],
									"numoutlets" : 0,
									"id" : "obj-30",
									"name" : "hoa.helpheader.maxpat",
									"args" : [ "@obj-name", "hoa.plug~", "@obj-desc", "A", "partcher", "that", "duplicates", "patcher", "for", "hoa", "process." ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 424.0, 24.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-31",
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "hoa.plug~ sends different kind of arguments to the subpatcher that you can receive with patcherargs object. First arguments that you receive in the left outlet are the harmomic number and the global order. This is useful to adapt process on spherical harmonics. Other arguments attributes work like classical patcher's arguments and attributes",
									"linecount" : 3,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 73.5, 615.0, 48.0 ],
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 10.0, 73.5, 615.0, 47.0 ],
									"numoutlets" : 0,
									"id" : "obj-35",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"numinlets" : 2,
									"patching_rect" : [ 433.678589, 562.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "startwindow",
									"numinlets" : 2,
									"patching_rect" : [ 403.678589, 532.0, 72.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"numinlets" : 15,
									"patching_rect" : [ 152.88501, 507.0, 221.5, 20.0 ],
									"numoutlets" : 16,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Open the different voices to see the how you can receive the harmonic number and the global order in the subpatchers.",
									"linecount" : 3,
									"numinlets" : 1,
									"patching_rect" : [ 555.0, 518.0, 219.0, 46.0 ],
									"numoutlets" : 0,
									"id" : "obj-10",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7",
									"numinlets" : 2,
									"patching_rect" : [ 154.320007, 328.0, 220.065018, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-16",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.connect 7 16",
									"numinlets" : 1,
									"patching_rect" : [ 675.0, 90.0, 99.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-15",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"numinlets" : 0,
									"patching_rect" : [ 675.0, 60.0, 51.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-22",
									"fontname" : "Arial",
									"outlettype" : [ "bang" ],
									"fontsize" : 11.595187,
									"hidden" : 1,
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
													"maxclass" : "button",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 32",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-23",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "key",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
													"numoutlets" : 4,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "int", "int", "int", "int" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-21",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-21", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"numinlets" : 16,
									"patching_rect" : [ 152.88501, 608.0, 221.5, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-12",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 555.0, 518.0, 219.0, 45.0 ],
									"numoutlets" : 0,
									"id" : "obj-41",
									"rounded" : 15,
									"shadow" : -1
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 1 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 2 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 3 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 4 ],
									"destination" : [ "obj-8", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 5 ],
									"destination" : [ "obj-8", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 6 ],
									"destination" : [ "obj-8", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 7 ],
									"destination" : [ "obj-8", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 8 ],
									"destination" : [ "obj-8", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 9 ],
									"destination" : [ "obj-8", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 10 ],
									"destination" : [ "obj-8", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 11 ],
									"destination" : [ "obj-8", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 12 ],
									"destination" : [ "obj-8", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 13 ],
									"destination" : [ "obj-8", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 14 ],
									"destination" : [ "obj-8", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
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
									"source" : [ "obj-8", 1 ],
									"destination" : [ "obj-12", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 2 ],
									"destination" : [ "obj-12", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 3 ],
									"destination" : [ "obj-12", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 4 ],
									"destination" : [ "obj-12", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 5 ],
									"destination" : [ "obj-12", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 6 ],
									"destination" : [ "obj-12", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 7 ],
									"destination" : [ "obj-12", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 8 ],
									"destination" : [ "obj-12", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 9 ],
									"destination" : [ "obj-12", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 10 ],
									"destination" : [ "obj-12", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 11 ],
									"destination" : [ "obj-12", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 12 ],
									"destination" : [ "obj-12", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 13 ],
									"destination" : [ "obj-12", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 14 ],
									"destination" : [ "obj-12", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 15 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 1 ],
									"destination" : [ "obj-13", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 2 ],
									"destination" : [ "obj-13", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 3 ],
									"destination" : [ "obj-13", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 4 ],
									"destination" : [ "obj-13", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 5 ],
									"destination" : [ "obj-13", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 6 ],
									"destination" : [ "obj-13", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 7 ],
									"destination" : [ "obj-13", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 8 ],
									"destination" : [ "obj-13", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 9 ],
									"destination" : [ "obj-13", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 10 ],
									"destination" : [ "obj-13", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 11 ],
									"destination" : [ "obj-13", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 12 ],
									"destination" : [ "obj-13", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 13 ],
									"destination" : [ "obj-13", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 14 ],
									"destination" : [ "obj-13", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-6", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 413.178589, 595.0, 364.88501, 595.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-13", 14 ],
									"hidden" : 0,
									"midpoints" : [ 737.5, 374.0, 635.0, 374.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 443.178589, 595.0, 364.88501, 595.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 1 ],
									"destination" : [ "obj-9", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 2 ],
									"destination" : [ "obj-9", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 3 ],
									"destination" : [ "obj-9", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 4 ],
									"destination" : [ "obj-9", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 5 ],
									"destination" : [ "obj-9", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 6 ],
									"destination" : [ "obj-9", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 7 ],
									"destination" : [ "obj-9", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 8 ],
									"destination" : [ "obj-9", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 9 ],
									"destination" : [ "obj-9", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 10 ],
									"destination" : [ "obj-9", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 11 ],
									"destination" : [ "obj-9", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 12 ],
									"destination" : [ "obj-9", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 13 ],
									"destination" : [ "obj-9", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 14 ],
									"destination" : [ "obj-9", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 1 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 2 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 3 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 4 ],
									"destination" : [ "obj-8", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 5 ],
									"destination" : [ "obj-8", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 6 ],
									"destination" : [ "obj-8", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 7 ],
									"destination" : [ "obj-8", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 8 ],
									"destination" : [ "obj-8", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 9 ],
									"destination" : [ "obj-8", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 10 ],
									"destination" : [ "obj-8", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 11 ],
									"destination" : [ "obj-8", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 12 ],
									"destination" : [ "obj-8", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 13 ],
									"destination" : [ "obj-8", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 14 ],
									"destination" : [ "obj-8", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [ 42.0, 450.0, 141.0, 450.0, 141.0, 384.0, 163.820007, 384.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p mode-out",
					"numinlets" : 0,
					"patching_rect" : [ 675.0, 322.0, 71.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-9",
					"fontname" : "Arial",
					"textcolor" : [ 0.209184, 0.209184, 0.209184, 1.0 ],
					"color" : [ 0.734694, 0.734694, 0.734694, 1.0 ],
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 26.0, 77.0, 1037.0, 653.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 26.0, 77.0, 1037.0, 653.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 1000",
									"numinlets" : 1,
									"patching_rect" : [ 492.75, 269.0, 89.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-18",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "First argument is the number of loudspeakers or virtual microphones",
									"linecount" : 3,
									"numinlets" : 1,
									"patching_rect" : [ 468.0, 400.0, 176.0, 46.0 ],
									"numoutlets" : 0,
									"id" : "obj-39",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 468.0, 400.0, 176.0, 45.0 ],
									"numoutlets" : 0,
									"id" : "obj-28",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 662.5, 313.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 603.5, 313.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-16",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 543.0, 313.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-13",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 484.0, 313.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-10",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 16 hoa.amp~ out 0.3",
									"numinlets" : 16,
									"patching_rect" : [ 167.25, 540.0, 221.5, 20.0 ],
									"numoutlets" : 16,
									"id" : "obj-1",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 24 hoa.delay~ out",
									"numinlets" : 24,
									"patching_rect" : [ 106.5, 400.0, 329.5, 20.0 ],
									"numoutlets" : 24,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.recomposer~ 7 24",
									"numinlets" : 25,
									"patching_rect" : [ 106.5, 441.0, 343.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.projector~ 7 24",
									"numinlets" : 15,
									"patching_rect" : [ 106.5, 330.0, 329.5, 20.0 ],
									"numoutlets" : 24,
									"id" : "obj-5",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7",
									"numinlets" : 2,
									"patching_rect" : [ 160.75, 279.0, 221.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-4",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 160.75, 145.0, 218.0, 87.0 ],
									"numoutlets" : 1,
									"id" : "obj-2",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ],
									"args" : [ "@module", 0, "@file", 7, "@loop", 1 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
									"linecount" : 2,
									"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 559.0, 19.5, 257.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-36",
									"fontname" : "Arial",
									"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"patching_rect" : [ 559.0, 19.5, 257.0, 32.0 ],
									"numoutlets" : 0,
									"id" : "obj-37",
									"rounded" : 6,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 7.5, 483.0, 56.0 ],
									"numoutlets" : 0,
									"id" : "obj-30",
									"name" : "hoa.helpheader.maxpat",
									"args" : [ "@obj-name", "hoa.plug~", "@obj-desc", "A", "partcher", "that", "duplicates", "patcher", "for", "hoa", "process." ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 424.0, 24.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-31",
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "The \"out\" mode works libe the \"post\" mode but in the plane wave domain or after the hoa.decoder~ object. It's useful to apply process on a set of virtual microphones or loudspeakers.",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 73.5, 619.0, 34.0 ],
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 10.0, 73.5, 619.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-35",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"numinlets" : 2,
									"patching_rect" : [ 492.75, 499.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "startwindow",
									"numinlets" : 2,
									"patching_rect" : [ 422.25, 499.0, 72.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"numinlets" : 15,
									"patching_rect" : [ 167.25, 514.0, 221.5, 20.0 ],
									"numoutlets" : 16,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.connect 7 16",
									"numinlets" : 1,
									"patching_rect" : [ 675.0, 90.0, 99.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-15",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"numinlets" : 0,
									"patching_rect" : [ 675.0, 60.0, 51.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-22",
									"fontname" : "Arial",
									"outlettype" : [ "bang" ],
									"fontsize" : 11.595187,
									"hidden" : 1,
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
													"maxclass" : "button",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 32",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-23",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "key",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
													"numoutlets" : 4,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "int", "int", "int", "int" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-21",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-21", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"numinlets" : 16,
									"patching_rect" : [ 167.25, 574.0, 221.5, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-12",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 1 ],
									"destination" : [ "obj-1", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 2 ],
									"destination" : [ "obj-1", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 3 ],
									"destination" : [ "obj-1", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 4 ],
									"destination" : [ "obj-1", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 5 ],
									"destination" : [ "obj-1", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 6 ],
									"destination" : [ "obj-1", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 7 ],
									"destination" : [ "obj-1", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 8 ],
									"destination" : [ "obj-1", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 9 ],
									"destination" : [ "obj-1", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 10 ],
									"destination" : [ "obj-1", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 11 ],
									"destination" : [ "obj-1", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 12 ],
									"destination" : [ "obj-1", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 13 ],
									"destination" : [ "obj-1", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 14 ],
									"destination" : [ "obj-1", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 15 ],
									"destination" : [ "obj-1", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 1 ],
									"destination" : [ "obj-6", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 2 ],
									"destination" : [ "obj-6", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 3 ],
									"destination" : [ "obj-6", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 4 ],
									"destination" : [ "obj-6", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 5 ],
									"destination" : [ "obj-6", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 6 ],
									"destination" : [ "obj-6", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 7 ],
									"destination" : [ "obj-6", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 8 ],
									"destination" : [ "obj-6", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 9 ],
									"destination" : [ "obj-6", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 10 ],
									"destination" : [ "obj-6", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 11 ],
									"destination" : [ "obj-6", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 12 ],
									"destination" : [ "obj-6", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 13 ],
									"destination" : [ "obj-6", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 14 ],
									"destination" : [ "obj-6", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 15 ],
									"destination" : [ "obj-6", 15 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 16 ],
									"destination" : [ "obj-6", 16 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 17 ],
									"destination" : [ "obj-6", 17 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 18 ],
									"destination" : [ "obj-6", 18 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 19 ],
									"destination" : [ "obj-6", 19 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 20 ],
									"destination" : [ "obj-6", 20 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 21 ],
									"destination" : [ "obj-6", 21 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 22 ],
									"destination" : [ "obj-6", 22 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 23 ],
									"destination" : [ "obj-6", 23 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 1 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 2 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 3 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 4 ],
									"destination" : [ "obj-8", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 5 ],
									"destination" : [ "obj-8", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 6 ],
									"destination" : [ "obj-8", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 7 ],
									"destination" : [ "obj-8", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 8 ],
									"destination" : [ "obj-8", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 9 ],
									"destination" : [ "obj-8", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 10 ],
									"destination" : [ "obj-8", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 11 ],
									"destination" : [ "obj-8", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 12 ],
									"destination" : [ "obj-8", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 13 ],
									"destination" : [ "obj-8", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 14 ],
									"destination" : [ "obj-8", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 1 ],
									"destination" : [ "obj-7", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 2 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 3 ],
									"destination" : [ "obj-7", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 4 ],
									"destination" : [ "obj-7", 4 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 5 ],
									"destination" : [ "obj-7", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 6 ],
									"destination" : [ "obj-7", 6 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 7 ],
									"destination" : [ "obj-7", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 8 ],
									"destination" : [ "obj-7", 8 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 9 ],
									"destination" : [ "obj-7", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 10 ],
									"destination" : [ "obj-7", 10 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 11 ],
									"destination" : [ "obj-7", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 12 ],
									"destination" : [ "obj-7", 12 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 13 ],
									"destination" : [ "obj-7", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 14 ],
									"destination" : [ "obj-7", 14 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 15 ],
									"destination" : [ "obj-7", 15 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 16 ],
									"destination" : [ "obj-7", 16 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 17 ],
									"destination" : [ "obj-7", 17 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 18 ],
									"destination" : [ "obj-7", 18 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 19 ],
									"destination" : [ "obj-7", 19 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 20 ],
									"destination" : [ "obj-7", 20 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 21 ],
									"destination" : [ "obj-7", 21 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 22 ],
									"destination" : [ "obj-7", 22 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 23 ],
									"destination" : [ "obj-7", 23 ],
									"hidden" : 0,
									"color" : [ 1.0, 1.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-5", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 2 ],
									"destination" : [ "obj-5", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 3 ],
									"destination" : [ "obj-5", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 4 ],
									"destination" : [ "obj-5", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 5 ],
									"destination" : [ "obj-5", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 6 ],
									"destination" : [ "obj-5", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 7 ],
									"destination" : [ "obj-5", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 8 ],
									"destination" : [ "obj-5", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 9 ],
									"destination" : [ "obj-5", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 10 ],
									"destination" : [ "obj-5", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 11 ],
									"destination" : [ "obj-5", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 12 ],
									"destination" : [ "obj-5", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 13 ],
									"destination" : [ "obj-5", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 14 ],
									"destination" : [ "obj-5", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 431.75, 570.0, 379.25, 570.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 502.25, 570.0, 379.25, 570.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"midpoints" : [ 613.0, 387.0, 143.0, 387.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-7", 3 ],
									"hidden" : 0,
									"midpoints" : [ 672.0, 387.0, 156.5, 387.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-7", 1 ],
									"hidden" : 0,
									"midpoints" : [ 552.5, 387.0, 129.5, 387.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [ 493.5, 387.0, 116.0, 387.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 1 ],
									"destination" : [ "obj-12", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 2 ],
									"destination" : [ "obj-12", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 3 ],
									"destination" : [ "obj-12", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 4 ],
									"destination" : [ "obj-12", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 5 ],
									"destination" : [ "obj-12", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 6 ],
									"destination" : [ "obj-12", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 7 ],
									"destination" : [ "obj-12", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 8 ],
									"destination" : [ "obj-12", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 9 ],
									"destination" : [ "obj-12", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 10 ],
									"destination" : [ "obj-12", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 11 ],
									"destination" : [ "obj-12", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 12 ],
									"destination" : [ "obj-12", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 13 ],
									"destination" : [ "obj-12", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 14 ],
									"destination" : [ "obj-12", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 15 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 11.595187,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 11.595187
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p mode-pre",
					"numinlets" : 0,
					"patching_rect" : [ 674.0, 294.0, 72.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-5",
					"fontname" : "Arial",
					"textcolor" : [ 0.209184, 0.209184, 0.209184, 1.0 ],
					"color" : [ 0.734694, 0.734694, 0.734694, 1.0 ],
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 1037.0, 653.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 1037.0, 653.0 ],
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
									"text" : "Use the target message to select voice(s) to receive future messages and the open message to open patcher instance(s) in new window.",
									"linecount" : 5,
									"numinlets" : 1,
									"patching_rect" : [ 617.25, 348.0, 172.0, 73.0 ],
									"numoutlets" : 0,
									"id" : "obj-39",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "order mixer value :",
									"linecount" : 2,
									"numinlets" : 1,
									"patching_rect" : [ 204.25, 226.0, 70.75, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-32",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 204.25, 226.0, 70.75, 32.0 ],
									"numoutlets" : 0,
									"id" : "obj-33",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 332.25, 186.0, 218.0, 87.0 ],
									"numoutlets" : 1,
									"id" : "obj-3",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ],
									"args" : [ "@module", 0, "@file", 9, "@loop", 1 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
									"linecount" : 2,
									"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 559.0, 19.5, 257.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-36",
									"fontname" : "Arial",
									"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"patching_rect" : [ 559.0, 19.5, 257.0, 32.0 ],
									"numoutlets" : 0,
									"id" : "obj-37",
									"rounded" : 6,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 7.5, 483.0, 56.0 ],
									"numoutlets" : 0,
									"id" : "obj-30",
									"name" : "hoa.helpheader.maxpat",
									"args" : [ "@obj-name", "hoa.plug~", "@obj-desc", "A", "partcher", "that", "duplicates", "patcher", "for", "hoa", "process." ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 424.0, 24.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-31",
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "The \"pre\" mode works with the \"split\" mode of the hoa.encoder~. It works like \"no\" mode but it vectorizes process before the encoder. It is useful when you want to create a process on  the order dependant's signals.",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 73.5, 596.0, 34.0 ],
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 10.0, 73.5, 596.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-35",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 572.0, 169.0, 156.0, 173.0 ],
									"numoutlets" : 1,
									"id" : "obj-11",
									"name" : "blablabli.maxpat",
									"outlettype" : [ "" ],
									"args" : [  ],
									"embed" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 572.0, 195.0, 156.0, 173.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 572.0, 195.0, 156.0, 173.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Open",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 150.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-11",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 6.0, 90.0, 47.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Target",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 180.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-9",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 6.0, 0.0, 54.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 255.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-4",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend mute",
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 225.0, 85.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-3",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 120.0, 85.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-2",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend target",
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 45.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-1",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "tab",
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 75.0, 198.0, 37.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"id" : "obj-37",
													"fontname" : "Arial",
													"background" : 1,
													"tabs" : [ "all", "1", "2", "3", "4", "-5", "6", "7" ],
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 11.595187,
													"presentation_rect" : [ 6.0, 120.0, 131.0, 37.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "tab",
													"numinlets" : 1,
													"patching_rect" : [ 0.0, 0.0, 198.0, 37.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"id" : "obj-36",
													"fontname" : "Arial",
													"background" : 1,
													"tabs" : [ "all", "1", "2", "3", "4", "-5", "6", "7" ],
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 11.595187,
													"presentation_rect" : [ 6.0, 30.0, 132.0, 37.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-37", 1 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [ 99.0, 114.0, 9.5, 114.0 ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 1 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [ 99.0, 39.0, 9.5, 39.0 ]
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
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-4", 0 ],
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
									"text" : "stop",
									"numinlets" : 2,
									"patching_rect" : [ 617.25, 472.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "startwindow",
									"numinlets" : 2,
									"patching_rect" : [ 587.25, 442.0, 72.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"numinlets" : 15,
									"patching_rect" : [ 332.25, 457.0, 221.5, 20.0 ],
									"numoutlets" : 16,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 534.75, 374.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-24",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 7.",
									"numinlets" : 1,
									"patching_rect" : [ 204.25, 226.0, 73.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-23",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 204.25, 265.0, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-18",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7 split",
									"numinlets" : 9,
									"patching_rect" : [ 332.25, 404.0, 221.5, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-45",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 7 hoa.pwider~ pre",
									"numinlets" : 1,
									"patching_rect" : [ 332.25, 374.0, 196.1875, 20.0 ],
									"numoutlets" : 8,
									"id" : "obj-4",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.connect 7 16",
									"numinlets" : 1,
									"patching_rect" : [ 675.0, 90.0, 99.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-15",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"numinlets" : 0,
									"patching_rect" : [ 675.0, 60.0, 51.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-22",
									"fontname" : "Arial",
									"outlettype" : [ "bang" ],
									"fontsize" : 11.595187,
									"hidden" : 1,
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
													"maxclass" : "button",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 32",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-23",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "key",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
													"numoutlets" : 4,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "int", "int", "int", "int" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-21",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-21", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"numinlets" : 16,
									"patching_rect" : [ 332.25, 517.0, 221.5, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-12",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 617.25, 348.0, 172.0, 71.0 ],
									"numoutlets" : 0,
									"id" : "obj-28",
									"rounded" : 15,
									"shadow" : -1
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
									"source" : [ "obj-8", 1 ],
									"destination" : [ "obj-12", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 2 ],
									"destination" : [ "obj-12", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 3 ],
									"destination" : [ "obj-12", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 4 ],
									"destination" : [ "obj-12", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 5 ],
									"destination" : [ "obj-12", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 6 ],
									"destination" : [ "obj-12", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 7 ],
									"destination" : [ "obj-12", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 8 ],
									"destination" : [ "obj-12", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 9 ],
									"destination" : [ "obj-12", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 10 ],
									"destination" : [ "obj-12", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 11 ],
									"destination" : [ "obj-12", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 12 ],
									"destination" : [ "obj-12", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 13 ],
									"destination" : [ "obj-12", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 14 ],
									"destination" : [ "obj-12", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 15 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 1 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 2 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 3 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 4 ],
									"destination" : [ "obj-8", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 5 ],
									"destination" : [ "obj-8", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 6 ],
									"destination" : [ "obj-8", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 7 ],
									"destination" : [ "obj-8", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 8 ],
									"destination" : [ "obj-8", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 9 ],
									"destination" : [ "obj-8", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 10 ],
									"destination" : [ "obj-8", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 11 ],
									"destination" : [ "obj-8", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 12 ],
									"destination" : [ "obj-8", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 13 ],
									"destination" : [ "obj-8", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 14 ],
									"destination" : [ "obj-8", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-45", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-45", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 2 ],
									"destination" : [ "obj-45", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 3 ],
									"destination" : [ "obj-45", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 4 ],
									"destination" : [ "obj-45", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 5 ],
									"destination" : [ "obj-45", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 6 ],
									"destination" : [ "obj-45", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 7 ],
									"destination" : [ "obj-45", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-45", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 596.75, 502.0, 544.25, 502.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [ 213.75, 360.0, 341.75, 360.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 626.75, 502.0, 544.25, 502.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [ 581.5, 360.0, 341.75, 360.0 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p mode-post",
					"numinlets" : 0,
					"patching_rect" : [ 673.0, 267.0, 77.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-3",
					"fontname" : "Arial",
					"textcolor" : [ 0.209184, 0.209184, 0.209184, 1.0 ],
					"color" : [ 0.734694, 0.734694, 0.734694, 1.0 ],
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 1037.0, 653.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 1037.0, 653.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Even if the messages are independant, the  sended messages are changed depending to the harmonic's number.",
									"linecount" : 5,
									"numinlets" : 1,
									"patching_rect" : [ 570.714294, 288.5, 152.0, 73.0 ],
									"numoutlets" : 0,
									"id" : "obj-26",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 570.714294, 288.5, 152.0, 71.0 ],
									"numoutlets" : 0,
									"id" : "obj-27",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Use the open message to open patcher instance(s) in new window.",
									"linecount" : 2,
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 419.5, 235.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-39",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 10.0, 419.5, 235.0, 32.0 ],
									"numoutlets" : 0,
									"id" : "obj-40",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 10.0, 129.5, 249.0, 238.0 ],
									"numoutlets" : 15,
									"presentation" : 1,
									"id" : "obj-42",
									"name" : "hoa.mixerControl.maxpat",
									"outlettype" : [ "", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int" ],
									"args" : [  ],
									"embed" : 1,
									"presentation_rect" : [ 1.0, 129.5, 249.0, 238.0 ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 10.0, 156.0, 249.0, 238.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 10.0, 156.0, 249.0, 238.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 128",
													"numinlets" : 1,
													"patching_rect" : [ 510.0, 90.0, 85.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-21",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 115",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 84.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 0.",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 90.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-3",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess set 128",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, -30.0, 105.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-2",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 0.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-59",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 15.0, 150.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 660.0, 165.0, 21.0, 138.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-51",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 225.0, 150.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 660.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-52",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 615.0, 165.0, 21.0, 138.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-54",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 225.0, 15.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 615.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-55",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 570.0, 165.0, 21.0, 138.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-57",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 195.0, 150.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 570.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-58",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 525.0, 165.0, 21.0, 138.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-22",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 195.0, 15.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 525.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-23",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 480.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-25",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 165.0, 150.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 480.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-26",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"interp" : 0.0,
													"numinlets" : 2,
													"patching_rect" : [ 435.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-28",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 165.0, 15.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 435.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-29",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"interp" : 115.0,
													"numinlets" : 2,
													"patching_rect" : [ 390.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-31",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 135.0, 150.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 390.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-32",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 345.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-34",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 135.0, 15.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 345.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-35",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"interp" : 0.0,
													"numinlets" : 2,
													"patching_rect" : [ 300.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-38",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 105.0, 150.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 300.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-40",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 255.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-16",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 105.0, 15.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 255.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-17",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"interp" : 0.0,
													"numinlets" : 2,
													"patching_rect" : [ 210.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-19",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 75.0, 150.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-20",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 165.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-8",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 75.0, 15.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 165.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-9",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"interp" : 115.0,
													"numinlets" : 2,
													"patching_rect" : [ 120.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-12",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 45.0, 150.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-13",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 75.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-5",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 45.0, 15.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 75.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-6",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "gain~",
													"numinlets" : 2,
													"patching_rect" : [ 30.0, 165.0, 20.0, 140.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-1",
													"outlettype" : [ "signal", "int" ],
													"presentation_rect" : [ 15.0, 15.0, 14.0, 77.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 30.0, 315.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-14",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"numinlets" : 1,
													"patching_rect" : [ 285.0, 75.0, 94.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-11",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187,
													"hidden" : 1
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "tab",
													"numinlets" : 1,
													"patching_rect" : [ 270.0, 30.0, 198.0, 37.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"id" : "obj-37",
													"fontname" : "Arial",
													"background" : 1,
													"tabs" : [ "0", "-1", "-2", "-3", "-4", "-5", "-6", "-7", "all", "1", "2", "3", "4", "5", "6", "7" ],
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 11.595187,
													"presentation_rect" : [ 10.0, 105.0, 235.0, 37.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-8", 1 ],
													"destination" : [ "obj-9", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-57", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-54", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-51", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-38", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-25", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-22", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-19", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 1 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-57", 1 ],
													"destination" : [ "obj-58", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-54", 1 ],
													"destination" : [ "obj-55", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-51", 1 ],
													"destination" : [ "obj-52", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 1 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-38", 1 ],
													"destination" : [ "obj-40", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-37", 1 ],
													"destination" : [ "obj-11", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 1 ],
													"destination" : [ "obj-35", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 1 ],
													"destination" : [ "obj-32", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-8", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-54", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-38", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-22", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-19", 0 ],
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
													"source" : [ "obj-28", 1 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-25", 1 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-22", 1 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-57", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-51", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-25", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-59", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-19", 1 ],
													"destination" : [ "obj-20", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 1 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 1 ],
													"destination" : [ "obj-13", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-11", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 1 ],
													"destination" : [ "obj-14", 0 ],
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
									"text" : "hoa.plug~ 7 hoa.mixer~ post",
									"numinlets" : 15,
									"patching_rect" : [ 266.0, 419.5, 221.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-14",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Note that you can use the hoa.all patch in \"no\" mode to easily send the same message to all the instances of a hoa.plug~ in \"post\" mode.",
									"linecount" : 8,
									"numinlets" : 1,
									"patching_rect" : [ 838.5, 101.5, 129.0, 113.0 ],
									"numoutlets" : 0,
									"id" : "obj-25",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 838.5, 101.5, 129.0, 110.0 ],
									"numoutlets" : 0,
									"id" : "obj-28",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.pi 0.5",
									"numinlets" : 1,
									"patching_rect" : [ 740.571411, 256.0, 72.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-13",
									"fontname" : "Arial",
									"outlettype" : [ "float" ],
									"fontsize" : 14.0,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 740.571411, 288.5, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-16",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7",
									"numinlets" : 2,
									"patching_rect" : [ 533.428589, 363.5, 226.571442, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-18",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 7 hoa.all no",
									"numinlets" : 1,
									"patching_rect" : [ 788.5, 229.0, 208.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-33",
									"fontname" : "Arial",
									"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 788.5, 189.5, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-10",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"minimum" : -1.0,
									"maximum" : 1.0,
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 7 hoa.mirror~ post",
									"numinlets" : 15,
									"patching_rect" : [ 533.0, 419.5, 227.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-11",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0.",
									"numinlets" : 1,
									"patching_rect" : [ 468.0, 256.0, 86.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-7",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 468.0, 288.5, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-24",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.encoder~ 7",
									"numinlets" : 2,
									"patching_rect" : [ 266.0, 318.0, 221.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-4",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 533.0, 161.0, 218.0, 87.0 ],
									"numoutlets" : 1,
									"id" : "obj-9",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ],
									"args" : [ "@module", 0, "@file", 9, "@loop", 1 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 266.0, 161.0, 218.0, 87.0 ],
									"numoutlets" : 1,
									"id" : "obj-2",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ],
									"args" : [ "@module", 0, "@file", 7, "@loop", 1 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
									"linecount" : 2,
									"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 559.0, 19.5, 257.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-36",
									"fontname" : "Arial",
									"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"patching_rect" : [ 559.0, 19.5, 257.0, 32.0 ],
									"numoutlets" : 0,
									"id" : "obj-37",
									"rounded" : 6,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 7.5, 483.0, 56.0 ],
									"numoutlets" : 0,
									"id" : "obj-30",
									"name" : "hoa.helpheader.maxpat",
									"args" : [ "@obj-name", "hoa.plug~", "@obj-desc", "A", "partcher", "that", "duplicates", "patcher", "for", "hoa", "process." ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 424.0, 24.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-31",
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "The \"post\" mode means that hoa.plug~ keeps in parallel all the process, each signal is independant. Each inlet correspond to one subpatcher. It is a useful tool to perform process in the spherical harmonic's domain without duplicate the patches.",
									"linecount" : 3,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 73.5, 618.0, 48.0 ],
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 10.0, 73.5, 618.0, 47.0 ],
									"numoutlets" : 0,
									"id" : "obj-35",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"numinlets" : 2,
									"patching_rect" : [ 668.0, 514.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "startwindow",
									"numinlets" : 2,
									"patching_rect" : [ 638.0, 484.0, 72.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"numinlets" : 15,
									"patching_rect" : [ 383.0, 499.0, 221.5, 20.0 ],
									"numoutlets" : 16,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.connect 7 16",
									"numinlets" : 1,
									"patching_rect" : [ 675.0, 90.0, 99.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-15",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"numinlets" : 0,
									"patching_rect" : [ 675.0, 60.0, 51.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-22",
									"fontname" : "Arial",
									"outlettype" : [ "bang" ],
									"fontsize" : 11.595187,
									"hidden" : 1,
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
													"maxclass" : "button",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 32",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-23",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "key",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
													"numoutlets" : 4,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "int", "int", "int", "int" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-21",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-21", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"numinlets" : 16,
									"patching_rect" : [ 383.0, 559.0, 221.5, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-12",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-8", 1 ],
									"destination" : [ "obj-12", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 2 ],
									"destination" : [ "obj-12", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 3 ],
									"destination" : [ "obj-12", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 4 ],
									"destination" : [ "obj-12", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 5 ],
									"destination" : [ "obj-12", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 6 ],
									"destination" : [ "obj-12", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 7 ],
									"destination" : [ "obj-12", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 8 ],
									"destination" : [ "obj-12", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 9 ],
									"destination" : [ "obj-12", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 10 ],
									"destination" : [ "obj-12", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 11 ],
									"destination" : [ "obj-12", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 12 ],
									"destination" : [ "obj-12", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 13 ],
									"destination" : [ "obj-12", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 14 ],
									"destination" : [ "obj-12", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 15 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [ 19.5, 405.0, 275.5, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 1 ],
									"destination" : [ "obj-14", 1 ],
									"hidden" : 0,
									"midpoints" : [ 35.92857, 405.0, 289.928558, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 2 ],
									"destination" : [ "obj-14", 2 ],
									"hidden" : 0,
									"midpoints" : [ 52.357143, 405.0, 304.357147, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 3 ],
									"destination" : [ "obj-14", 3 ],
									"hidden" : 0,
									"midpoints" : [ 68.785713, 405.0, 318.785706, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 4 ],
									"destination" : [ "obj-14", 4 ],
									"hidden" : 0,
									"midpoints" : [ 85.214287, 405.0, 333.214294, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 5 ],
									"destination" : [ "obj-14", 5 ],
									"hidden" : 0,
									"midpoints" : [ 101.64286, 405.0, 347.642853, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 6 ],
									"destination" : [ "obj-14", 6 ],
									"hidden" : 0,
									"midpoints" : [ 118.071426, 405.0, 362.071442, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 7 ],
									"destination" : [ "obj-14", 7 ],
									"hidden" : 0,
									"midpoints" : [ 134.5, 405.0, 376.5, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 8 ],
									"destination" : [ "obj-14", 8 ],
									"hidden" : 0,
									"midpoints" : [ 150.928574, 405.0, 390.928558, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 9 ],
									"destination" : [ "obj-14", 9 ],
									"hidden" : 0,
									"midpoints" : [ 167.357147, 405.0, 405.357147, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 10 ],
									"destination" : [ "obj-14", 10 ],
									"hidden" : 0,
									"midpoints" : [ 183.785721, 405.0, 419.785706, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 11 ],
									"destination" : [ "obj-14", 11 ],
									"hidden" : 0,
									"midpoints" : [ 200.214279, 405.0, 434.214294, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 12 ],
									"destination" : [ "obj-14", 12 ],
									"hidden" : 0,
									"midpoints" : [ 216.642853, 405.0, 448.642853, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 13 ],
									"destination" : [ "obj-14", 13 ],
									"hidden" : 0,
									"midpoints" : [ 233.071426, 405.0, 463.071442, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 14 ],
									"destination" : [ "obj-14", 14 ],
									"hidden" : 0,
									"midpoints" : [ 249.5, 405.0, 477.5, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 275.5, 339.0, 275.5, 339.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-14", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 289.928558, 339.0, 289.928558, 339.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 2 ],
									"destination" : [ "obj-14", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 3 ],
									"destination" : [ "obj-14", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 4 ],
									"destination" : [ "obj-14", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 5 ],
									"destination" : [ "obj-14", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 6 ],
									"destination" : [ "obj-14", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 7 ],
									"destination" : [ "obj-14", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 8 ],
									"destination" : [ "obj-14", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 9 ],
									"destination" : [ "obj-14", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 10 ],
									"destination" : [ "obj-14", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 11 ],
									"destination" : [ "obj-14", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 12 ],
									"destination" : [ "obj-14", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 13 ],
									"destination" : [ "obj-14", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 14 ],
									"destination" : [ "obj-14", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 798.0, 249.0, 799.0, 249.0, 799.0, 405.0, 542.5, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 1 ],
									"destination" : [ "obj-11", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 811.5, 249.0, 812.0, 249.0, 812.0, 405.0, 557.357117, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 2 ],
									"destination" : [ "obj-11", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 825.0, 405.0, 572.214294, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 3 ],
									"destination" : [ "obj-11", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 838.5, 405.0, 587.071411, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 4 ],
									"destination" : [ "obj-11", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 852.0, 405.0, 601.928589, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 5 ],
									"destination" : [ "obj-11", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 865.5, 405.0, 616.785706, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 6 ],
									"destination" : [ "obj-11", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 879.0, 405.0, 631.642883, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 7 ],
									"destination" : [ "obj-11", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 892.5, 405.0, 646.5, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 8 ],
									"destination" : [ "obj-11", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 906.0, 405.0, 661.357117, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 9 ],
									"destination" : [ "obj-11", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 919.5, 405.0, 676.214294, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 10 ],
									"destination" : [ "obj-11", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 933.0, 405.0, 691.071411, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 11 ],
									"destination" : [ "obj-11", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 946.5, 405.0, 705.928589, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 12 ],
									"destination" : [ "obj-11", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 960.0, 405.0, 720.785706, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 13 ],
									"destination" : [ "obj-11", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [ 973.5, 405.0, 735.642883, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 14 ],
									"destination" : [ "obj-11", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [ 987.0, 405.0, 750.5, 405.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-4", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 647.5, 544.0, 595.0, 544.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 1 ],
									"destination" : [ "obj-11", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 2 ],
									"destination" : [ "obj-11", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 3 ],
									"destination" : [ "obj-11", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 4 ],
									"destination" : [ "obj-11", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 5 ],
									"destination" : [ "obj-11", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 6 ],
									"destination" : [ "obj-11", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 7 ],
									"destination" : [ "obj-11", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 8 ],
									"destination" : [ "obj-11", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 9 ],
									"destination" : [ "obj-11", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 10 ],
									"destination" : [ "obj-11", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 11 ],
									"destination" : [ "obj-11", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 12 ],
									"destination" : [ "obj-11", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 13 ],
									"destination" : [ "obj-11", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 14 ],
									"destination" : [ "obj-11", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 677.5, 544.0, 595.0, 544.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-18", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 1 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 2 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 3 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 4 ],
									"destination" : [ "obj-8", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 5 ],
									"destination" : [ "obj-8", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 6 ],
									"destination" : [ "obj-8", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 7 ],
									"destination" : [ "obj-8", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 8 ],
									"destination" : [ "obj-8", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 9 ],
									"destination" : [ "obj-8", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 10 ],
									"destination" : [ "obj-8", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 11 ],
									"destination" : [ "obj-8", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 12 ],
									"destination" : [ "obj-8", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 13 ],
									"destination" : [ "obj-8", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 14 ],
									"destination" : [ "obj-8", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 1 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 2 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 3 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 4 ],
									"destination" : [ "obj-8", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 5 ],
									"destination" : [ "obj-8", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 6 ],
									"destination" : [ "obj-8", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 7 ],
									"destination" : [ "obj-8", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 8 ],
									"destination" : [ "obj-8", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 9 ],
									"destination" : [ "obj-8", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 10 ],
									"destination" : [ "obj-8", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 11 ],
									"destination" : [ "obj-8", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 12 ],
									"destination" : [ "obj-8", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 13 ],
									"destination" : [ "obj-8", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 14 ],
									"destination" : [ "obj-8", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 11.595187,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 11.595187
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p mode-no",
					"numinlets" : 0,
					"patching_rect" : [ 671.0, 239.0, 68.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-2",
					"fontname" : "Arial",
					"textcolor" : [ 0.209184, 0.209184, 0.209184, 1.0 ],
					"color" : [ 0.734694, 0.734694, 0.734694, 1.0 ],
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 5,
							"minor" : 1,
							"revision" : 9
						}
,
						"rect" : [ 0.0, 26.0, 1037.0, 653.0 ],
						"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 26.0, 1037.0, 653.0 ],
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
									"maxclass" : "newobj",
									"text" : "hoa.pi",
									"numinlets" : 1,
									"patching_rect" : [ 743.0, 302.0, 42.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-11",
									"fontname" : "Arial",
									"outlettype" : [ "float" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadmess 0.",
									"numinlets" : 1,
									"patching_rect" : [ 743.0, 229.0, 86.0, 23.0 ],
									"numoutlets" : 1,
									"id" : "obj-1",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 14.0,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p sinBuffer",
									"numinlets" : 0,
									"patching_rect" : [ 768.0, 130.0, 66.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-2",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 620.0, 172.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 620.0, 172.0, 640.0, 480.0 ],
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
													"text" : "t b b",
													"numinlets" : 1,
													"patching_rect" : [ 45.0, 75.0, 34.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-2",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "bang" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadbang",
													"numinlets" : 1,
													"patching_rect" : [ 45.0, 30.0, 60.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-1",
													"fontname" : "Arial",
													"outlettype" : [ "bang" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "/ 1500.",
													"numinlets" : 2,
													"patching_rect" : [ 195.0, 135.0, 46.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-29",
													"fontname" : "Arial",
													"outlettype" : [ "float" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "uzi 1500",
													"numinlets" : 2,
													"patching_rect" : [ 105.0, 105.0, 64.0, 20.0 ],
													"numoutlets" : 3,
													"id" : "obj-28",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "bang", "int" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "expr sin(3.14159265 * $f1)",
													"numinlets" : 1,
													"patching_rect" : [ 195.0, 180.0, 147.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "sizeinsamps 1500",
													"numinlets" : 2,
													"patching_rect" : [ 45.0, 150.0, 103.0, 18.0 ],
													"numoutlets" : 1,
													"id" : "obj-16",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "peek~ livegrain",
													"numinlets" : 3,
													"patching_rect" : [ 150.0, 225.0, 108.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"fontname" : "Arial",
													"outlettype" : [ "float" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "buffer~ livegrain",
													"numinlets" : 1,
													"patching_rect" : [ 150.0, 255.0, 93.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-6",
													"fontname" : "Arial",
													"outlettype" : [ "float", "bang" ],
													"fontsize" : 11.595187
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-29", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 2 ],
													"destination" : [ "obj-29", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-28", 2 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-28", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 1 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-10", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-6", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Use the target message to select voice(s) to receive future messages and the open message to open patcher instance(s) in new window.",
									"linecount" : 3,
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 117.0, 262.0, 46.0 ],
									"numoutlets" : 0,
									"id" : "obj-39",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 10.0, 117.0, 262.0, 45.0 ],
									"numoutlets" : 0,
									"id" : "obj-40",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 10.0, 177.0, 235.0, 303.0 ],
									"numoutlets" : 1,
									"id" : "obj-42",
									"name" : "delay.maxpat",
									"outlettype" : [ "" ],
									"args" : [  ],
									"embed" : 1,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 5,
											"minor" : 1,
											"revision" : 9
										}
,
										"rect" : [ 10.0, 203.0, 235.0, 303.0 ],
										"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
										"bglocked" : 0,
										"defrect" : [ 10.0, 203.0, 235.0, 303.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Open",
													"numinlets" : 1,
													"patching_rect" : [ 60.0, 210.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-2",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 4.0, 54.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Target",
													"numinlets" : 1,
													"patching_rect" : [ 45.0, 195.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-9",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 223.0, 54.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend target",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 60.0, 89.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-1",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 0.",
													"numinlets" : 1,
													"patching_rect" : [ 450.0, 165.0, 75.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-34",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 5000",
													"numinlets" : 1,
													"patching_rect" : [ 435.0, 90.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-32",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 100",
													"numinlets" : 1,
													"patching_rect" : [ 420.0, 15.0, 85.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-31",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Feedback :",
													"numinlets" : 1,
													"patching_rect" : [ 270.0, 135.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-29",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 165.0, 91.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Rarefaction :",
													"numinlets" : 1,
													"patching_rect" : [ 285.0, 75.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-16",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 195.0, 108.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Delay (ms) :",
													"numinlets" : 1,
													"patching_rect" : [ 270.0, 60.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-13",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 135.0, 108.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Grain Size (ms) :",
													"numinlets" : 1,
													"patching_rect" : [ 255.0, 45.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-12",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 105.0, 108.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "comment",
													"text" : "Parameters :",
													"numinlets" : 1,
													"patching_rect" : [ 255.0, 15.0, 150.0, 20.0 ],
													"numoutlets" : 0,
													"presentation" : 1,
													"id" : "obj-10",
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"presentation_rect" : [ 15.0, 75.0, 150.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 240.0, 50.0, 20.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-26",
													"fontname" : "Arial",
													"outlettype" : [ "float", "bang" ],
													"minimum" : 0.0,
													"maximum" : 0.99,
													"fontsize" : 11.595187,
													"presentation_rect" : [ 120.0, 195.0, 50.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend rarefaction",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 270.0, 111.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-27",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 180.0, 50.0, 20.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-24",
													"fontname" : "Arial",
													"outlettype" : [ "float", "bang" ],
													"minimum" : 0.0,
													"maximum" : 0.99,
													"fontsize" : 11.595187,
													"presentation_rect" : [ 120.0, 165.0, 50.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend feedback",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 210.0, 103.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-25",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 120.0, 50.0, 20.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-18",
													"fontname" : "Arial",
													"outlettype" : [ "float", "bang" ],
													"minimum" : 0.0,
													"fontsize" : 11.595187,
													"presentation_rect" : [ 120.0, 135.0, 50.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend delay",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 150.0, 84.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-20",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 45.0, 50.0, 20.0 ],
													"numoutlets" : 2,
													"presentation" : 1,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "float", "bang" ],
													"minimum" : 0.0,
													"fontsize" : 11.595187,
													"presentation_rect" : [ 120.0, 105.0, 50.0, 20.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend size",
													"numinlets" : 1,
													"patching_rect" : [ 405.0, 75.0, 77.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-15",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "prepend open",
													"numinlets" : 1,
													"patching_rect" : [ 210.0, 152.0, 82.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-22",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 390.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-14",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 5000",
													"numinlets" : 1,
													"patching_rect" : [ 630.0, 180.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-4",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "loadmess 4375",
													"numinlets" : 1,
													"patching_rect" : [ 630.0, 135.0, 92.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-3",
													"fontname" : "Arial",
													"outlettype" : [ "" ],
													"fontsize" : 12.0
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "tab",
													"numinlets" : 1,
													"patching_rect" : [ 120.0, 105.0, 198.0, 37.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"id" : "obj-37",
													"fontname" : "Arial",
													"background" : 1,
													"tabs" : [ "0", "-1", "-2", "-3", "-4", "-5", "-6", "-7", "all", "1", "2", "3", "4", "5", "6", "7" ],
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 11.595187,
													"presentation_rect" : [ 15.0, 30.0, 198.0, 37.0 ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "tab",
													"numinlets" : 1,
													"patching_rect" : [ 15.0, 15.0, 198.0, 37.0 ],
													"numoutlets" : 3,
													"presentation" : 1,
													"id" : "obj-36",
													"fontname" : "Arial",
													"background" : 1,
													"tabs" : [ "0", "-1", "-2", "-3", "-4", "-5", "-6", "-7", "all", "1", "2", "3", "4", "5", "6", "7" ],
													"outlettype" : [ "int", "", "" ],
													"fontsize" : 11.595187,
													"presentation_rect" : [ 15.0, 252.0, 211.0, 37.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-37", 1 ],
													"destination" : [ "obj-22", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-36", 1 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [ 114.0, 54.0, 24.5, 54.0 ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-24", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-18", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-27", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-27", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-25", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-25", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-22", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-20", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-20", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-15", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-15", 0 ],
													"destination" : [ "obj-14", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-14", 0 ],
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
									"maxclass" : "comment",
									"text" : "azimuth :",
									"numinlets" : 1,
									"patching_rect" : [ 684.25, 261.5, 58.75, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-32",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 684.25, 261.5, 58.75, 19.0 ],
									"numoutlets" : 0,
									"id" : "obj-33",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numinlets" : 1,
									"patching_rect" : [ 743.0, 261.5, 50.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-24",
									"fontname" : "Arial",
									"outlettype" : [ "float", "bang" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Note that if the subpatch got several inlets the hoa.plug~ have as many inputs.",
									"linecount" : 4,
									"numinlets" : 1,
									"patching_rect" : [ 768.0, 183.5, 125.75, 60.0 ],
									"numoutlets" : 0,
									"id" : "obj-25",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 768.0, 183.5, 124.0, 58.0 ],
									"numoutlets" : 0,
									"id" : "obj-28",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 531.5, 142.0, 218.0, 87.0 ],
									"numoutlets" : 1,
									"id" : "obj-4",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ],
									"args" : [ "@module", 0, "@file", 9, "@loop", 1 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Here you can see how to encode a sound onto a direction like the hoa.encoder~ object do.",
									"linecount" : 3,
									"numinlets" : 1,
									"patching_rect" : [ 546.75, 289.0, 196.0, 46.0 ],
									"numoutlets" : 0,
									"id" : "obj-5",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 7 hoa.pencoder~ no",
									"numinlets" : 2,
									"patching_rect" : [ 531.5, 345.0, 230.5, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 546.75, 289.0, 196.0, 45.0 ],
									"numoutlets" : 0,
									"id" : "obj-7",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"border" : 1,
									"numinlets" : 0,
									"patching_rect" : [ 273.5, 142.0, 218.0, 87.0 ],
									"numoutlets" : 1,
									"id" : "obj-3",
									"name" : "hoa.helpaudio.maxpat",
									"outlettype" : [ "signal" ],
									"args" : [ "@module", 0, "@file", 7, "@loop", 1 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
									"linecount" : 2,
									"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 559.0, 19.5, 257.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-36",
									"fontname" : "Arial",
									"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
									"patching_rect" : [ 559.0, 19.5, 257.0, 32.0 ],
									"numoutlets" : 0,
									"id" : "obj-37",
									"rounded" : 6,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "bpatcher",
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 7.5, 483.0, 56.0 ],
									"numoutlets" : 0,
									"id" : "obj-30",
									"name" : "hoa.helpheader.maxpat",
									"args" : [ "@obj-name", "hoa.plug~", "@obj-desc", "A", "partcher", "that", "duplicates", "patcher", "for", "hoa", "process." ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "bgcolor 0.93 0.93 0.92 1.",
									"linecount" : 2,
									"numinlets" : 4,
									"patching_rect" : [ 424.0, 24.0, 52.0, 23.0 ],
									"numoutlets" : 0,
									"id" : "obj-31",
									"fontname" : "Arial",
									"fontsize" : 7.180877,
									"hidden" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"varname" : "autohelp_top_description[1]",
									"text" : "The \"no\" mode means that hoa.plug~ splits the inputs to all the subpatchs. It could be seen like a tool to facilitate the creation of new kind of encoders. It's really useful to create diffused soundfields.",
									"linecount" : 2,
									"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"numinlets" : 1,
									"patching_rect" : [ 10.0, 73.5, 623.0, 34.0 ],
									"numoutlets" : 0,
									"id" : "obj-34",
									"fontname" : "Arial",
									"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 10.0, 73.5, 623.0, 33.0 ],
									"numoutlets" : 0,
									"id" : "obj-35",
									"rounded" : 15,
									"shadow" : -1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"numinlets" : 2,
									"patching_rect" : [ 655.5, 486.0, 32.5, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "startwindow",
									"numinlets" : 2,
									"patching_rect" : [ 625.5, 456.0, 72.0, 18.0 ],
									"numoutlets" : 1,
									"id" : "obj-20",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.decoder~ 7 16",
									"numinlets" : 15,
									"patching_rect" : [ 370.5, 471.0, 221.5, 20.0 ],
									"numoutlets" : 16,
									"id" : "obj-8",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Here is an exemple to generate a diffused soundfield with the granulation. If You look at the subpatch you can see that sended datas are changed depending to the harmonic's number.",
									"linecount" : 5,
									"numinlets" : 1,
									"patching_rect" : [ 289.5, 261.5, 219.0, 73.0 ],
									"numoutlets" : 0,
									"id" : "obj-10",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.plug~ 7 hoa.grain~ no",
									"numinlets" : 1,
									"patching_rect" : [ 273.5, 345.0, 208.0, 20.0 ],
									"numoutlets" : 15,
									"id" : "obj-16",
									"fontname" : "Arial",
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.connect 7 16",
									"numinlets" : 1,
									"patching_rect" : [ 675.0, 90.0, 99.0, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-15",
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"saved_object_attributes" : 									{
										"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p key32",
									"numinlets" : 0,
									"patching_rect" : [ 675.0, 60.0, 51.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-22",
									"fontname" : "Arial",
									"outlettype" : [ "bang" ],
									"fontsize" : 11.595187,
									"hidden" : 1,
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
													"maxclass" : "button",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
													"numoutlets" : 1,
													"id" : "obj-10",
													"outlettype" : [ "bang" ]
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "sel 32",
													"numinlets" : 2,
													"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
													"numoutlets" : 2,
													"id" : "obj-23",
													"fontname" : "Arial",
													"outlettype" : [ "bang", "" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "key",
													"numinlets" : 0,
													"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
													"numoutlets" : 4,
													"id" : "obj-17",
													"fontname" : "Arial",
													"outlettype" : [ "int", "int", "int", "int" ],
													"fontsize" : 11.595187
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
													"numoutlets" : 0,
													"id" : "obj-21",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-23", 0 ],
													"destination" : [ "obj-10", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-23", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-10", 0 ],
													"destination" : [ "obj-21", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0,
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "hoa.dac~ 1:16",
									"numinlets" : 16,
									"patching_rect" : [ 370.5, 531.0, 221.5, 20.0 ],
									"numoutlets" : 0,
									"id" : "obj-12",
									"fontname" : "Arial",
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
									"numinlets" : 1,
									"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
									"patching_rect" : [ 289.5, 261.5, 219.0, 71.0 ],
									"numoutlets" : 0,
									"id" : "obj-41",
									"rounded" : 15,
									"shadow" : -1
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
									"source" : [ "obj-8", 1 ],
									"destination" : [ "obj-12", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 2 ],
									"destination" : [ "obj-12", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 3 ],
									"destination" : [ "obj-12", 3 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 4 ],
									"destination" : [ "obj-12", 4 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 5 ],
									"destination" : [ "obj-12", 5 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 6 ],
									"destination" : [ "obj-12", 6 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 7 ],
									"destination" : [ "obj-12", 7 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 8 ],
									"destination" : [ "obj-12", 8 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 9 ],
									"destination" : [ "obj-12", 9 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 10 ],
									"destination" : [ "obj-12", 10 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 11 ],
									"destination" : [ "obj-12", 11 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 12 ],
									"destination" : [ "obj-12", 12 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 13 ],
									"destination" : [ "obj-12", 13 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 14 ],
									"destination" : [ "obj-12", 14 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 15 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 1 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 2 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 3 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 4 ],
									"destination" : [ "obj-8", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 5 ],
									"destination" : [ "obj-8", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 6 ],
									"destination" : [ "obj-8", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 7 ],
									"destination" : [ "obj-8", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 8 ],
									"destination" : [ "obj-8", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 9 ],
									"destination" : [ "obj-8", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 10 ],
									"destination" : [ "obj-8", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 11 ],
									"destination" : [ "obj-8", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 12 ],
									"destination" : [ "obj-8", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 13 ],
									"destination" : [ "obj-8", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 14 ],
									"destination" : [ "obj-8", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-42", 0 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 0,
									"midpoints" : [ 19.5, 507.0, 253.0, 507.0, 253.0, 342.0, 283.0, 342.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-22", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 635.0, 516.0, 582.5, 516.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-12", 15 ],
									"hidden" : 0,
									"midpoints" : [ 665.0, 516.0, 582.5, 516.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 1 ],
									"destination" : [ "obj-8", 1 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 2 ],
									"destination" : [ "obj-8", 2 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 3 ],
									"destination" : [ "obj-8", 3 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 4 ],
									"destination" : [ "obj-8", 4 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 5 ],
									"destination" : [ "obj-8", 5 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 6 ],
									"destination" : [ "obj-8", 6 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 7 ],
									"destination" : [ "obj-8", 7 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 8 ],
									"destination" : [ "obj-8", 8 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 9 ],
									"destination" : [ "obj-8", 9 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 10 ],
									"destination" : [ "obj-8", 10 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 11 ],
									"destination" : [ "obj-8", 11 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 12 ],
									"destination" : [ "obj-8", 12 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 13 ],
									"destination" : [ "obj-8", 13 ],
									"hidden" : 0,
									"color" : [ 1.0, 0.0, 0.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 14 ],
									"destination" : [ "obj-8", 14 ],
									"hidden" : 0,
									"color" : [ 0.0, 0.0, 1.0, 1.0 ],
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-6", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-24", 0 ],
									"hidden" : 1,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 14.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 14.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Look at the inlet and outlet notifications.",
					"linecount" : 3,
					"numinlets" : 1,
					"patching_rect" : [ 553.0, 201.5, 97.0, 46.0 ],
					"numoutlets" : 0,
					"id" : "obj-4",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 553.0, 201.5, 97.0, 45.0 ],
					"numoutlets" : 0,
					"id" : "obj-6",
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"border" : 1,
					"numinlets" : 0,
					"patching_rect" : [ 166.0, 138.5, 218.0, 87.0 ],
					"numoutlets" : 1,
					"id" : "obj-7",
					"name" : "hoa.helpaudio.maxpat",
					"outlettype" : [ "signal" ],
					"args" : [ "@module", 0, "@file", 7, "@loop", 1 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "hoalibrary | Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
					"linecount" : 2,
					"frgb" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 553.0, 17.0, 257.0, 33.0 ],
					"numoutlets" : 0,
					"id" : "obj-36",
					"fontname" : "Arial",
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"patching_rect" : [ 553.0, 17.0, 257.0, 32.0 ],
					"numoutlets" : 0,
					"id" : "obj-37",
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "bpatcher",
					"numinlets" : 1,
					"patching_rect" : [ 4.0, 5.0, 483.0, 56.0 ],
					"numoutlets" : 0,
					"id" : "obj-30",
					"name" : "hoa.helpheader.maxpat",
					"args" : [ "@obj-name", "hoa.plug~", "@obj-desc", "A", "partcher", "that", "duplicates", "patcher", "for", "hoa", "process." ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "bgcolor 0.93 0.93 0.92 1.",
					"linecount" : 2,
					"numinlets" : 4,
					"patching_rect" : [ 418.0, 21.5, 52.0, 23.0 ],
					"numoutlets" : 0,
					"id" : "obj-31",
					"fontname" : "Arial",
					"fontsize" : 7.180877,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[1]",
					"text" : "hoa.plug~ helps the modularization of patches for ambisonic process. Number of inlets and outlets depends on number of inlets and outlets objects within its subpatch window, ambisonic order and 1st argument.\nSecond argument is the name of the patcher to load and 3rd argument is the mode pre, no or post encoding.",
					"linecount" : 3,
					"frgb" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 4.0, 71.0, 626.0, 48.0 ],
					"numoutlets" : 0,
					"id" : "obj-34",
					"fontname" : "Arial",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 1.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 4.0, 71.0, 626.0, 47.0 ],
					"numoutlets" : 0,
					"id" : "obj-35",
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Double click opens the last patcher.",
					"linecount" : 3,
					"numinlets" : 1,
					"patching_rect" : [ 166.0, 449.5, 84.0, 46.0 ],
					"numoutlets" : 0,
					"id" : "obj-25",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"numinlets" : 2,
					"patching_rect" : [ 541.0, 569.5, 32.5, 18.0 ],
					"numoutlets" : 1,
					"id" : "obj-17",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "startwindow",
					"numinlets" : 2,
					"patching_rect" : [ 511.0, 539.5, 72.0, 18.0 ],
					"numoutlets" : 1,
					"id" : "obj-20",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Post-mode for processing on harmonics signals.",
					"linecount" : 2,
					"numinlets" : 1,
					"patching_rect" : [ 481.0, 464.5, 217.0, 33.0 ],
					"numoutlets" : 0,
					"id" : "obj-14",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.delay~ post",
					"numinlets" : 15,
					"patching_rect" : [ 256.0, 464.5, 221.0, 20.0 ],
					"numoutlets" : 15,
					"id" : "obj-8",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.decoder~ 7 16",
					"numinlets" : 15,
					"patching_rect" : [ 256.0, 554.5, 221.5, 20.0 ],
					"numoutlets" : 16,
					"id" : "obj-10",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"patching_rect" : [ 580.0, 314.5, 50.0, 20.0 ],
					"numoutlets" : 2,
					"id" : "obj-24",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 7.",
					"numinlets" : 1,
					"patching_rect" : [ 391.0, 214.5, 73.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-23",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"fontsize" : 11.595187,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Order mixer value",
					"numinlets" : 1,
					"patching_rect" : [ 391.0, 225.5, 105.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-21",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"patching_rect" : [ 391.0, 244.5, 50.0, 20.0 ],
					"numoutlets" : 2,
					"id" : "obj-18",
					"fontname" : "Arial",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "No-mode for no encoding processing, useful to create diffuse soundfields",
					"linecount" : 2,
					"numinlets" : 1,
					"patching_rect" : [ 181.0, 310.5, 208.0, 33.0 ],
					"numoutlets" : 0,
					"id" : "obj-11",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Pre-mode for processing on order's signals.",
					"linecount" : 2,
					"numinlets" : 1,
					"patching_rect" : [ 408.1875, 280.5, 150.0, 33.0 ],
					"numoutlets" : 0,
					"id" : "obj-12",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7 split",
					"numinlets" : 9,
					"patching_rect" : [ 391.0, 344.5, 208.0, 20.0 ],
					"numoutlets" : 15,
					"id" : "obj-45",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.grain~ no",
					"numinlets" : 1,
					"patching_rect" : [ 166.0, 344.5, 208.0, 20.0 ],
					"numoutlets" : 15,
					"id" : "obj-16",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.plug~ 7 hoa.pwider~ pre",
					"numinlets" : 1,
					"patching_rect" : [ 391.0, 314.5, 184.375, 20.0 ],
					"numoutlets" : 8,
					"id" : "obj-15",
					"fontname" : "Arial",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.connect 7 16",
					"numinlets" : 1,
					"patching_rect" : [ 669.0, 87.5, 99.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-19",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"saved_object_attributes" : 					{
						"poscolor" : [ 1.0, 0.0, 0.0, 1.0 ]
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p key32",
					"numinlets" : 0,
					"patching_rect" : [ 669.0, 57.5, 51.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-22",
					"fontname" : "Arial",
					"outlettype" : [ "bang" ],
					"fontsize" : 11.595187,
					"hidden" : 1,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "button",
									"numinlets" : 1,
									"patching_rect" : [ 50.0, 160.0, 20.0, 20.0 ],
									"numoutlets" : 1,
									"id" : "obj-10",
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sel 32",
									"numinlets" : 2,
									"patching_rect" : [ 50.0, 130.0, 41.0, 20.0 ],
									"numoutlets" : 2,
									"id" : "obj-23",
									"fontname" : "Arial",
									"outlettype" : [ "bang", "" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "key",
									"numinlets" : 0,
									"patching_rect" : [ 50.0, 100.0, 59.5, 20.0 ],
									"numoutlets" : 4,
									"id" : "obj-17",
									"fontname" : "Arial",
									"outlettype" : [ "int", "int", "int", "int" ],
									"fontsize" : 11.595187
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"patching_rect" : [ 50.0, 240.0, 25.0, 25.0 ],
									"numoutlets" : 0,
									"id" : "obj-21",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-17", 0 ],
									"destination" : [ "obj-23", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0,
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "hoa.dac~ 1:16",
					"numinlets" : 16,
					"patching_rect" : [ 256.0, 614.5, 221.5, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-26",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 481.0, 464.5, 216.0, 32.0 ],
					"numoutlets" : 0,
					"id" : "obj-39",
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 166.0, 449.5, 84.0, 45.0 ],
					"numoutlets" : 0,
					"id" : "obj-40",
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 408.1875, 280.5, 150.0, 32.0 ],
					"numoutlets" : 0,
					"id" : "obj-42",
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"numinlets" : 1,
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"patching_rect" : [ 181.0, 310.5, 208.0, 32.0 ],
					"numoutlets" : 0,
					"id" : "obj-41",
					"rounded" : 15,
					"shadow" : -1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-8", 14 ],
					"destination" : [ "obj-10", 14 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 13 ],
					"destination" : [ "obj-10", 13 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 12 ],
					"destination" : [ "obj-10", 12 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 11 ],
					"destination" : [ "obj-10", 11 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 10 ],
					"destination" : [ "obj-10", 10 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 9 ],
					"destination" : [ "obj-10", 9 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 8 ],
					"destination" : [ "obj-10", 8 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 7 ],
					"destination" : [ "obj-10", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 6 ],
					"destination" : [ "obj-10", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 5 ],
					"destination" : [ "obj-10", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 4 ],
					"destination" : [ "obj-10", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 3 ],
					"destination" : [ "obj-10", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 2 ],
					"destination" : [ "obj-10", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 1 ],
					"destination" : [ "obj-10", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 14 ],
					"destination" : [ "obj-8", 14 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 13 ],
					"destination" : [ "obj-8", 13 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 12 ],
					"destination" : [ "obj-8", 12 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 11 ],
					"destination" : [ "obj-8", 11 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 10 ],
					"destination" : [ "obj-8", 10 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 9 ],
					"destination" : [ "obj-8", 9 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 8 ],
					"destination" : [ "obj-8", 8 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 7 ],
					"destination" : [ "obj-8", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 6 ],
					"destination" : [ "obj-8", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 5 ],
					"destination" : [ "obj-8", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 4 ],
					"destination" : [ "obj-8", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 3 ],
					"destination" : [ "obj-8", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 2 ],
					"destination" : [ "obj-8", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 1 ],
					"destination" : [ "obj-8", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-26", 15 ],
					"hidden" : 0,
					"midpoints" : [ 550.5, 599.5, 468.0, 599.5 ]
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
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-26", 15 ],
					"hidden" : 0,
					"midpoints" : [ 520.5, 599.5, 468.0, 599.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-45", 8 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 175.5, 296.5, 400.5, 296.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 7 ],
					"destination" : [ "obj-45", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 6 ],
					"destination" : [ "obj-45", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 5 ],
					"destination" : [ "obj-45", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 4 ],
					"destination" : [ "obj-45", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 3 ],
					"destination" : [ "obj-45", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 2 ],
					"destination" : [ "obj-45", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 1 ],
					"destination" : [ "obj-45", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 14 ],
					"destination" : [ "obj-8", 14 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 13 ],
					"destination" : [ "obj-8", 13 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 12 ],
					"destination" : [ "obj-8", 12 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 11 ],
					"destination" : [ "obj-8", 11 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 10 ],
					"destination" : [ "obj-8", 10 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 9 ],
					"destination" : [ "obj-8", 9 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 8 ],
					"destination" : [ "obj-8", 8 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 7 ],
					"destination" : [ "obj-8", 7 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 6 ],
					"destination" : [ "obj-8", 6 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 5 ],
					"destination" : [ "obj-8", 5 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 4 ],
					"destination" : [ "obj-8", 4 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 3 ],
					"destination" : [ "obj-8", 3 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 2 ],
					"destination" : [ "obj-8", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 1 ],
					"destination" : [ "obj-8", 1 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 15 ],
					"destination" : [ "obj-26", 15 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 14 ],
					"destination" : [ "obj-26", 14 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 13 ],
					"destination" : [ "obj-26", 13 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 12 ],
					"destination" : [ "obj-26", 12 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 11 ],
					"destination" : [ "obj-26", 11 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 10 ],
					"destination" : [ "obj-26", 10 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 9 ],
					"destination" : [ "obj-26", 9 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 8 ],
					"destination" : [ "obj-26", 8 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 7 ],
					"destination" : [ "obj-26", 7 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 6 ],
					"destination" : [ "obj-26", 6 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 5 ],
					"destination" : [ "obj-26", 5 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 4 ],
					"destination" : [ "obj-26", 4 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 3 ],
					"destination" : [ "obj-26", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 2 ],
					"destination" : [ "obj-26", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 1 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
