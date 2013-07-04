{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 5.0, 44.0, 776.0, 540.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 5.0, 44.0, 776.0, 540.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 10.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 1,
		"metadata" : [  ],
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "swatch",
					"background" : 0,
					"outlettype" : [ "", "float" ],
					"compatibility" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"patching_rect" : [ 369.0, 15.0, 120.0, 120.0 ],
					"presentation" : 0,
					"numinlets" : 3,
					"id" : "obj-1",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "plane mapping",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 430.0, 492.0, 88.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-2",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "bang" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 719.0, 22.0, 56.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-3",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "setname scale, set 1., setname rscale, set 1., setname gscale, set 1., setname bscale, set 1., setname prate, 1000",
					"linecount" : 5,
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 719.0, 43.0, 133.0, 71.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-4",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pvar",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 719.0, 130.0, 31.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-5",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "patcher explain_scalebias",
					"fontsize" : 11.595187,
					"background" : 0,
					"color" : [ 1.0, 0.360784, 0.682353, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 492.0, 321.0, 142.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 0,
					"id" : "obj-6",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 339.0, 61.0, 575.0, 379.0 ],
						"bglocked" : 0,
						"defrect" : [ 339.0, 61.0, 575.0, 379.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 10.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"metadata" : [  ],
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "8",
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 56.0, 294.0, 32.5, 18.0 ],
									"numinlets" : 2,
									"id" : "obj-1",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"fontsize" : 11.595187,
									"outlettype" : [ "bang" ],
									"fontname" : "Arial",
									"patching_rect" : [ 56.0, 273.0, 58.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-2",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Click on presets",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 96.0, 213.0, 93.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-3",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Demonstrate jit.scalebias",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 18.0, 174.0, 140.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-4",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "preset",
									"fontsize" : 11.595187,
									"outlettype" : [ "preset", "int", "preset", "int" ],
									"patching_rect" : [ 10.0, 210.0, 86.0, 19.0 ],
									"margin" : 4,
									"numinlets" : 1,
									"id" : "obj-5",
									"bubblesize" : 8,
									"numoutlets" : 4,
									"spacing" : 2,
									"preset_data" : [ 										{
											"number" : 1,
											"data" : [ 5, "obj-28", "flonum", "float", 0.5, 5, "obj-27", "flonum", "float", 0.0, 5, "obj-24", "number", "int", 255, 5, "obj-22", "flonum", "float", 1.0, 5, "obj-18", "number", "int", 127, 5, "obj-12", "flonum", "float", 0.498039, 5, "obj-8", "umenu", "int", 1 ]
										}
, 										{
											"number" : 2,
											"data" : [ 5, "obj-28", "flonum", "float", 2.0, 5, "obj-27", "flonum", "float", 0.0, 5, "obj-24", "number", "int", 100, 5, "obj-22", "flonum", "float", 0.392157, 5, "obj-18", "number", "int", 200, 5, "obj-12", "flonum", "float", 0.784314, 5, "obj-8", "umenu", "int", 2 ]
										}
, 										{
											"number" : 3,
											"data" : [ 5, "obj-28", "flonum", "float", 1.0, 5, "obj-27", "flonum", "float", -0.2, 5, "obj-24", "number", "int", 100, 5, "obj-22", "flonum", "float", 0.392157, 5, "obj-18", "number", "int", 49, 5, "obj-12", "flonum", "float", 0.192157, 5, "obj-8", "umenu", "int", 3 ]
										}
, 										{
											"number" : 4,
											"data" : [ 5, "obj-28", "flonum", "float", 2.0, 5, "obj-27", "flonum", "float", 0.2, 5, "obj-24", "number", "int", 100, 5, "obj-22", "flonum", "float", 0.392157, 5, "obj-18", "number", "int", 251, 5, "obj-12", "flonum", "float", 0.984314, 5, "obj-8", "umenu", "int", 4 ]
										}
, 										{
											"number" : 5,
											"data" : [ 5, "obj-28", "flonum", "float", 4.0, 5, "obj-27", "flonum", "float", 0.0, 5, "obj-24", "number", "int", 100, 5, "obj-22", "flonum", "float", 0.392157, 5, "obj-18", "number", "int", 255, 5, "obj-12", "flonum", "float", 1.0, 5, "obj-8", "umenu", "int", 5 ]
										}
, 										{
											"number" : 6,
											"data" : [ 5, "obj-28", "flonum", "float", 1.0, 5, "obj-27", "flonum", "float", -0.5, 5, "obj-24", "number", "int", 100, 5, "obj-22", "flonum", "float", 0.392157, 5, "obj-18", "number", "int", 0, 5, "obj-12", "flonum", "float", 0.0, 5, "obj-8", "umenu", "int", 6 ]
										}
, 										{
											"number" : 7,
											"data" : [ 5, "obj-28", "flonum", "float", 3.0, 5, "obj-27", "flonum", "float", -0.5, 5, "obj-24", "number", "int", 100, 5, "obj-22", "flonum", "float", 0.392157, 5, "obj-18", "number", "int", 172, 5, "obj-12", "flonum", "float", 0.67451, 5, "obj-8", "umenu", "int", 7 ]
										}
, 										{
											"number" : 8,
											"data" : [ 5, "obj-28", "flonum", "float", 1.0, 5, "obj-27", "flonum", "float", 0.0, 5, "obj-24", "number", "int", 100, 5, "obj-22", "flonum", "float", 0.392157, 5, "obj-18", "number", "int", 100, 5, "obj-12", "flonum", "float", 0.392157, 5, "obj-8", "umenu", "int", 8 ]
										}
 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Output will never exceed the 0-255 range of char data",
									"linecount" : 2,
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 312.0, 219.0, 158.0, 33.0 ],
									"numinlets" : 1,
									"id" : "obj-6",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "jit.pwindow",
									"outlettype" : [ "", "" ],
									"depthbuffer" : 0,
									"onscreen" : 0,
									"patching_rect" : [ 400.0, 131.0, 30.0, 30.0 ],
									"numinlets" : 1,
									"id" : "obj-7",
									"doublebuffer" : 0,
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "umenu",
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "", "" ],
									"items" : [ ",", "Halve", "the", "value", ",", "Double", "the", "value", ",", "Subtract", 0.2, "from", "it", ",", "Double", "it", "and", "add", 0.2, "to", "it", ",", "Expected", 400, "is", "limited", "to", 255, ",", "Expected", -27, "is", "limited", "to", 0, ",", "Calculated", "correctly", "internally", ",", "Unchanged", "level" ],
									"menumode" : 2,
									"fontname" : "Arial",
									"types" : [  ],
									"patching_rect" : [ 5.0, 229.0, 176.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-8",
									"numoutlets" : 3
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "For scaling and offsetting color values in a 4-plane char matrix",
									"linecount" : 3,
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 295.0, 163.0, 143.0, 46.0 ],
									"numinlets" : 1,
									"id" : "obj-9",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Resultant char value as an int 0-255",
									"linecount" : 2,
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 316.0, 269.0, 135.0, 33.0 ],
									"numinlets" : 1,
									"id" : "obj-10",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "This is its equivalent decimal value 0.-1.",
									"linecount" : 2,
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 317.0, 311.0, 118.0, 33.0 ],
									"numinlets" : 1,
									"id" : "obj-11",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "bang" ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"fontname" : "Arial",
									"triscale" : 0.9,
									"patching_rect" : [ 273.0, 322.0, 45.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-12",
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 255.",
									"fontsize" : 11.595187,
									"outlettype" : [ "float" ],
									"fontname" : "Arial",
									"patching_rect" : [ 273.0, 295.0, 40.0, 20.0 ],
									"numinlets" : 2,
									"id" : "obj-13",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "A 1-cell 4-plane char matrix",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 236.0, 135.0, 152.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-14",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Set the green value of the cell",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 253.0, 69.0, 164.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-15",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Add to values",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 132.0, 87.0, 81.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-16",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Multiply values",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 47.0, 87.0, 87.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-17",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"maximum" : 255,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "bang" ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"fontname" : "Arial",
									"triscale" : 0.9,
									"patching_rect" : [ 273.0, 269.0, 39.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-18",
									"minimum" : 0,
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0 0 0 0",
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "int", "int", "int" ],
									"fontname" : "Arial",
									"patching_rect" : [ 219.0, 238.0, 87.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-19",
									"numoutlets" : 4
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "jit.iter",
									"fontsize" : 11.595187,
									"outlettype" : [ "", "", "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 219.0, 211.0, 46.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-20",
									"numoutlets" : 3
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "This is its equivalent decimal value 0.-1.",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 4.0, 59.0, 216.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-21",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "bang" ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"fontname" : "Arial",
									"triscale" : 0.9,
									"patching_rect" : [ 6.0, 106.0, 45.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-22",
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 255.",
									"fontsize" : 11.595187,
									"outlettype" : [ "float" ],
									"fontname" : "Arial",
									"patching_rect" : [ 6.0, 85.0, 40.0, 20.0 ],
									"numinlets" : 2,
									"id" : "obj-23",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"maximum" : 255,
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "bang" ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"fontname" : "Arial",
									"triscale" : 0.9,
									"patching_rect" : [ 243.0, 48.0, 37.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-24",
									"minimum" : 0,
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "setcell 0 0 plane 2 val $1",
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 243.0, 89.0, 138.0, 18.0 ],
									"numinlets" : 2,
									"id" : "obj-25",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "jit.pwindow",
									"outlettype" : [ "", "" ],
									"depthbuffer" : 0,
									"onscreen" : 0,
									"patching_rect" : [ 235.0, 275.0, 30.0, 30.0 ],
									"numinlets" : 1,
									"id" : "obj-26",
									"doublebuffer" : 436769776,
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "bang" ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"fontname" : "Arial",
									"triscale" : 0.9,
									"patching_rect" : [ 133.0, 113.0, 54.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-27",
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"fontsize" : 11.595187,
									"outlettype" : [ "float", "bang" ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"fontname" : "Arial",
									"triscale" : 0.9,
									"patching_rect" : [ 74.0, 113.0, 54.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-28",
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "bias $1",
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 133.0, 136.0, 48.0, 18.0 ],
									"numinlets" : 2,
									"id" : "obj-29",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "scale $1",
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 74.0, 136.0, 54.0, 18.0 ],
									"numinlets" : 2,
									"id" : "obj-30",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "jit.scalebias",
									"fontsize" : 11.595187,
									"outlettype" : [ "jit_matrix", "" ],
									"color" : [ 1.0, 0.890196, 0.090196, 1.0 ],
									"fontname" : "Arial",
									"patching_rect" : [ 219.0, 169.0, 70.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-31",
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "jit.matrix 4 char 1 1",
									"fontsize" : 11.595187,
									"outlettype" : [ "jit_matrix", "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 219.0, 113.0, 108.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-32",
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 219.0, 89.0, 20.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-33",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Express char value as an int 0-255",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 224.0, 25.0, 189.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-34",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bgcolor" : [ 1.0, 0.498039, 0.498039, 1.0 ],
									"patching_rect" : [ 221.0, 24.0, 87.0, 49.0 ],
									"numinlets" : 1,
									"id" : "obj-35",
									"rounded" : 0,
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Explanation of jit.scalebias",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 37.0, 25.0, 147.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-36",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bgcolor" : [ 0.498039, 0.498039, 1.0, 1.0 ],
									"patching_rect" : [ 2.0, 189.0, 185.0, 65.0 ],
									"numinlets" : 1,
									"id" : "obj-37",
									"rounded" : 0,
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bgcolor" : [ 1.0, 1.0, 0.498039, 1.0 ],
									"patching_rect" : [ 6.0, 53.0, 211.0, 110.0 ],
									"numinlets" : 1,
									"id" : "obj-38",
									"rounded" : 0,
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bgcolor" : [ 1.0, 1.0, 0.498039, 1.0 ],
									"patching_rect" : [ 233.0, 257.0, 227.0, 97.0 ],
									"numinlets" : 1,
									"id" : "obj-39",
									"rounded" : 0,
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "panel",
									"bgcolor" : [ 0.498039, 1.0, 0.498039, 1.0 ],
									"patching_rect" : [ 214.0, 162.0, 230.0, 48.0 ],
									"numinlets" : 1,
									"id" : "obj-40",
									"rounded" : 0,
									"numoutlets" : 0
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [ 65.5, 313.0, 6.0, 313.0, 6.0, 206.0, 19.5, 206.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-23", 0 ],
									"hidden" : 0,
									"midpoints" : [ 252.5, 81.0, 15.5, 81.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-23", 0 ],
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-28", 0 ],
									"destination" : [ "obj-30", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-29", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-24", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [ 252.5, 85.0, 228.5, 85.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-25", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [ 252.5, 109.0, 228.5, 109.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-31", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-30", 0 ],
									"destination" : [ "obj-31", 0 ],
									"hidden" : 0,
									"midpoints" : [ 83.5, 159.0, 228.5, 159.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-29", 0 ],
									"destination" : [ "obj-31", 0 ],
									"hidden" : 0,
									"midpoints" : [ 142.5, 155.0, 228.5, 155.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-20", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-19", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-31", 0 ],
									"destination" : [ "obj-26", 0 ],
									"hidden" : 0,
									"midpoints" : [ 228.5, 189.0, 204.0, 189.0, 204.0, 270.0, 244.5, 270.0 ]
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
									"source" : [ "obj-19", 2 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [ 228.5, 158.0, 391.0, 158.0, 391.0, 108.0, 409.5, 108.0 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"fontsize" : 10.0,
						"globalpatchername" : "",
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 10.0,
						"fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 0. 0. 0.",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "float", "float", "float" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 369.0, 159.0, 85.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-7",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 3,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "vexpr $i1/255.",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 369.0, 138.0, 81.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-8",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read chilis.jpg",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 188.0, 42.0, 79.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-9",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Same for all color planes",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 410.0, 440.0, 136.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-10",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "planemap 0 1 1 1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 410.0, 461.0, 98.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-11",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"varname" : "prate",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "int", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"format" : 0,
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 670.0, 374.0, 43.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-12",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : 50,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 550.0, 374.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-13",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "patcher rotatecolorplanes",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 550.0, 399.0, 139.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-14",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 40.0, 55.0, 207.0, 248.0 ],
						"bglocked" : 0,
						"defrect" : [ 40.0, 55.0, 207.0, 248.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 10.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"metadata" : [  ],
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "rotation lookup for planemapping",
									"linecount" : 2,
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 56.0, 190.0, 107.0, 33.0 ],
									"numinlets" : 1,
									"id" : "obj-1",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"patching_rect" : [ 28.0, 189.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"id" : "obj-2",
									"numoutlets" : 0,
									"comment" : "(int) color plane rotation"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "rate",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 60.0, 41.0, 30.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-3",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "metro",
									"fontsize" : 11.595187,
									"outlettype" : [ "bang" ],
									"fontname" : "Arial",
									"patching_rect" : [ 28.0, 98.0, 40.0, 20.0 ],
									"numinlets" : 2,
									"id" : "obj-4",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "1",
									"fontsize" : 11.595187,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 68.0, 125.0, 32.5, 18.0 ],
									"numinlets" : 2,
									"id" : "obj-5",
									"numoutlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sel 0",
									"fontsize" : 11.595187,
									"outlettype" : [ "bang", "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 68.0, 98.0, 35.0, 20.0 ],
									"numinlets" : 2,
									"id" : "obj-6",
									"numoutlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "counter 1 6",
									"fontsize" : 11.595187,
									"outlettype" : [ "int", "", "", "int" ],
									"fontname" : "Arial",
									"patching_rect" : [ 28.0, 153.0, 73.0, 20.0 ],
									"numinlets" : 5,
									"id" : "obj-7",
									"numoutlets" : 4
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"outlettype" : [ "int" ],
									"patching_rect" : [ 62.0, 64.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"id" : "obj-8",
									"numoutlets" : 1,
									"comment" : "(int/float) planemapping rate"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"outlettype" : [ "int" ],
									"patching_rect" : [ 28.0, 64.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"id" : "obj-9",
									"numoutlets" : 1,
									"comment" : "(1/0) planemapping on/off"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "automated change of planemapping",
									"linecount" : 2,
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 21.0, 9.0, 123.0, 33.0 ],
									"numinlets" : 1,
									"id" : "obj-10",
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "on/off",
									"fontsize" : 11.595187,
									"fontname" : "Arial",
									"patching_rect" : [ 21.0, 41.0, 40.0, 20.0 ],
									"numinlets" : 1,
									"id" : "obj-11",
									"numoutlets" : 0
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [ 77.5, 148.0, 122.0, 148.0, 122.0, 182.0, 37.5, 182.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-4", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [ 37.5, 94.0, 77.5, 94.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"fontsize" : 10.0,
						"globalpatchername" : "",
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 10.0,
						"fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : 6,
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "int", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"format" : 0,
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 550.0, 420.0, 52.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-15",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend planemap",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 550.0, 469.0, 105.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-16",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "coll",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "", "", "", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 550.0, 443.0, 42.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-17",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 4,
					"fontface" : 0,
					"save" : [ "#N", "coll", ";", "#T", "flags", 1, 0, ";", "#T", 0, 0, 0, 0, 0, ";", "#T", 1, 0, 1, 2, 3, ";", "#T", 2, 0, 1, 3, 2, ";", "#T", 3, 0, 2, 1, 3, ";", "#T", 4, 0, 2, 3, 1, ";", "#T", 5, 0, 3, 1, 2, ";", "#T", 6, 0, 3, 2, 1, ";" ],
					"saved_object_attributes" : 					{
						"embed" : 1
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "send matrixattribute",
					"fontsize" : 11.595187,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 550.0, 494.0, 110.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-18",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.scalebias",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "jit_matrix", "" ],
					"color" : [ 1.0, 0.890196, 0.090196, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 30.0, 244.0, 68.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-19",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "float", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 551.0, 193.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-20",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numdecimalplaces" : 0,
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "bbias $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 551.0, 219.0, 52.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-21",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"varname" : "bscale",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "float", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 486.0, 193.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-22",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numdecimalplaces" : 0,
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "bscale $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 486.0, 219.0, 58.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-23",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "float", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 421.0, 193.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-24",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numdecimalplaces" : 0,
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "gbias $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 421.0, 219.0, 52.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-25",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"varname" : "gscale",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "float", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 356.0, 193.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-26",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numdecimalplaces" : 0,
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "gscale $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 356.0, 219.0, 58.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-27",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "float", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 291.0, 193.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-28",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numdecimalplaces" : 0,
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rbias $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 291.0, 219.0, 50.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-29",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"varname" : "rscale",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "float", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 226.0, 193.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-30",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numdecimalplaces" : 0,
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rscale $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 226.0, 219.0, 56.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-31",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "float", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 96.0, 193.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-32",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numdecimalplaces" : 0,
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "bias $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 96.0, 219.0, 46.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-33",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"varname" : "scale",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"outputonclick" : 0,
					"background" : 0,
					"outlettype" : [ "float", "bang" ],
					"mouseup" : 0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"triscale" : 0.9,
					"patching_rect" : [ 40.0, 193.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-34",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numdecimalplaces" : 0,
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "scale $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 40.0, 219.0, 52.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-35",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read wheel.mov",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 197.0, 61.0, 90.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-36",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read colorswatch.png",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 179.0, 23.0, 117.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-37",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Swap red and blue planes",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 410.0, 397.0, 143.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-38",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "planemap 0 1 2 3",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 410.0, 376.0, 98.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-39",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "receive matrixattribute",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 40.0, 137.0, 123.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 0,
					"id" : "obj-40",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 95.0, 72.0, 30.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-41",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "start",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 130.0, 72.0, 31.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-42",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "planemap 0 3 2 1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 410.0, 419.0, 98.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-43",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 206.0, 80.0, 32.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-44",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 30.0, 24.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-45",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "metro 50",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "bang" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 30.0, 47.0, 54.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-46",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"background" : 0,
					"outlettype" : [ "bang" ],
					"blinkcolor" : [ 1.0, 0.890196, 0.090196, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"outlinecolor" : [ 0.71328, 0.71328, 0.71328, 1.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.91328, 0.91328, 0.91328, 0.75 ],
					"hidden" : 0,
					"fgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"patching_rect" : [ 30.0, 72.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-47",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.qt.movie 320 240",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "jit_matrix", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 30.0, 104.0, 109.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-48",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.pwindow",
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fsaa" : 0,
					"dstrect" : [ 0, 0, 320, 240 ],
					"background" : 0,
					"outlettype" : [ "", "" ],
					"usesrcrect" : 0,
					"depthbuffer" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"colormode" : "argb",
					"ignoreclick" : 0,
					"onscreen" : 0,
					"interp" : 0,
					"idlemouse" : 0,
					"usedstrect" : 0,
					"hidden" : 0,
					"patching_rect" : [ 30.0, 271.0, 320.0, 240.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-49",
					"border" : 0.0,
					"planemap" : [ 0, 1, 2, 3 ],
					"doublebuffer" : 0,
					"shared" : 0,
					"srcrect" : [ 0, 0, 320, 240 ],
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.matrix 4 char 320 240",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "jit_matrix", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 30.0, 164.0, 132.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-50",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Normal plane mapping",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 410.0, 356.0, 125.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-51",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Double-click for the detailed explanation of jit.scalebias.",
					"linecount" : 2,
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 496.0, 287.0, 158.0, 33.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-55",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Modifying color levels with multiplication and addition",
					"linecount" : 2,
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 523.0, 72.0, 160.0, 33.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-57",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 1,
					"shadow" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 0.498039, 1.0, 0.498039, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 402.0, 352.0, 329.0, 170.0 ],
					"mode" : 0,
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-52",
					"border" : 0,
					"rounded" : 0,
					"angle" : 0.0,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 1,
					"shadow" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 0.498039, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 28.0, 21.0, 286.0, 111.0 ],
					"mode" : 0,
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-53",
					"border" : 0,
					"rounded" : 0,
					"angle" : 0.0,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 1,
					"shadow" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 0.498039, 0.498039, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 26.0, 187.0, 587.0, 81.0 ],
					"mode" : 0,
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-54",
					"border" : 0,
					"rounded" : 0,
					"angle" : 0.0,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 1,
					"shadow" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 0.498039, 1.0, 1.0, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 488.0, 286.0, 167.0, 62.0 ],
					"mode" : 0,
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-56",
					"border" : 0,
					"rounded" : 0,
					"angle" : 0.0,
					"numoutlets" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-46", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-47", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 197.5, 100.0, 39.5, 100.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 206.5, 100.0, 39.5, 100.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 188.5, 100.0, 39.5, 100.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-42", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 139.5, 96.0, 39.5, 96.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 104.5, 96.0, 39.5, 96.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-44", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 215.5, 100.0, 39.5, 100.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-47", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-48", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 49.5, 160.0, 39.5, 160.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 560.5, 249.0, 99.0, 249.0, 99.0, 240.0, 39.5, 240.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 495.5, 249.0, 99.0, 249.0, 99.0, 240.0, 39.5, 240.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 49.5, 237.0, 39.5, 237.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 105.5, 237.0, 39.5, 237.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 235.5, 249.0, 99.0, 249.0, 99.0, 240.0, 39.5, 240.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 300.5, 249.0, 99.0, 249.0, 99.0, 240.0, 39.5, 240.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 365.5, 249.0, 99.0, 249.0, 99.0, 240.0, 39.5, 240.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 430.5, 249.0, 99.0, 249.0, 99.0, 240.0, 39.5, 240.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-49", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 378.5, 188.0, 235.5, 188.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-31", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 1 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 411.5, 192.0, 365.5, 192.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 2 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 444.5, 188.0, 495.5, 188.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 419.5, 396.0, 396.0, 396.0, 396.0, 522.0, 537.0, 522.0, 537.0, 501.0, 555.0, 501.0, 555.0, 489.0, 559.5, 489.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 419.5, 438.0, 396.0, 438.0, 396.0, 522.0, 537.0, 522.0, 537.0, 501.0, 555.0, 501.0, 555.0, 489.0, 559.5, 489.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 419.5, 480.0, 408.0, 480.0, 408.0, 522.0, 537.0, 522.0, 537.0, 501.0, 555.0, 501.0, 555.0, 489.0, 559.5, 489.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-14", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 1,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 1,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
 ]
	}

}
