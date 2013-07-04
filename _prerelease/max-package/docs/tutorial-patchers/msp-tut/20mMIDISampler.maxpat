{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 14.0, 46.0, 547.0, 339.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 14.0, 46.0, 547.0, 339.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "if velocity ≠ 0, send key #",
					"fontface" : 0,
					"id" : "obj-1",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 0,
					"background" : 0,
					"patching_rect" : [ 274.0, 10.0, 140.0, 20.0 ],
					"underline" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Play Sequence",
					"fontface" : 0,
					"id" : "obj-2",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 0,
					"background" : 0,
					"patching_rect" : [ 25.0, 25.0, 89.0, 20.0 ],
					"underline" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-3",
					"hidden" : 0,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numoutlets" : 1,
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 3.0, 25.0, 20.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p sequence",
					"fontface" : 0,
					"id" : "obj-4",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 3.0, 53.0, 70.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 128.0, 67.0, 276.0, 230.0 ],
						"bglocked" : 0,
						"defrect" : [ 128.0, 67.0, 276.0, 230.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "(1/0) on/off",
									"id" : "obj-1",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 0,
									"patching_rect" : [ 62.0, 9.0, 67.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-2",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 34.0, 174.0, 25.0, 25.0 ],
									"comment" : "key #, velocity"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "midiparse",
									"id" : "obj-3",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 7,
									"outlettype" : [ "", "", "", "int", "int", "int", "int" ],
									"patching_rect" : [ 34.0, 148.0, 100.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "midiflush",
									"id" : "obj-4",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 34.0, 122.0, 56.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "seq sampleseq.midi",
									"id" : "obj-5",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 2,
									"outlettype" : [ "int", "bang" ],
									"patching_rect" : [ 34.0, 96.0, 113.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"id" : "obj-6",
									"fontsize" : 11.595187,
									"numinlets" : 2,
									"fontname" : "Arial",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 34.0, 68.0, 32.5, 18.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "start",
									"id" : "obj-7",
									"fontsize" : 11.595187,
									"numinlets" : 2,
									"fontname" : "Arial",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 69.0, 68.0, 33.0, 18.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sel 0 1",
									"id" : "obj-8",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 3,
									"outlettype" : [ "bang", "bang", "" ],
									"patching_rect" : [ 34.0, 38.0, 46.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-9",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 34.0, 9.0, 25.0, 25.0 ],
									"comment" : "(1/0) on/off"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "key #, velocity",
									"id" : "obj-10",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 0,
									"patching_rect" : [ 62.0, 174.0, 83.0, 20.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-8", 0 ],
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
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [ 78.5, 87.0, 43.5, 87.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [ 43.5, 60.0, 21.0, 60.0, 21.0, 117.0, 43.5, 117.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 1 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [ 137.5, 120.0, 162.0, 120.0, 162.0, 63.0, 78.5, 63.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 1 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"fontface" : 0,
						"fontsize" : 10.0,
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 10.0,
						"fontname" : "Arial",
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Audio On/Off",
					"fontface" : 0,
					"id" : "obj-5",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 0,
					"background" : 0,
					"patching_rect" : [ 42.0, 249.0, 78.0, 20.0 ],
					"underline" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-6",
					"hidden" : 0,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numoutlets" : 1,
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 86.0, 280.0, 20.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Output Level",
					"fontface" : 0,
					"id" : "obj-7",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 0,
					"background" : 0,
					"patching_rect" : [ 296.0, 249.0, 76.0, 20.0 ],
					"underline" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "$1 50",
					"fontface" : 0,
					"id" : "obj-8",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"gradient" : 0,
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 231.0, 274.0, 40.0, 18.0 ],
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numdecimalplaces" : 0,
					"fontface" : 0,
					"maximum" : 1.0,
					"id" : "obj-9",
					"fontsize" : 11.595187,
					"triangle" : 1,
					"hidden" : 0,
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"cantchange" : 0,
					"triscale" : 0.9,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 2,
					"background" : 0,
					"mouseup" : 0,
					"outputonclick" : 0,
					"minimum" : 0.0,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 231.0, 249.0, 59.0, 20.0 ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"tricolor" : [ 0.75, 0.75, 0.75, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0,
					"htricolor" : [ 0.87, 0.82, 0.24, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "line~",
					"fontface" : 0,
					"id" : "obj-10",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 179.0, 249.0, 35.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "*~",
					"fontface" : 0,
					"id" : "obj-11",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 121.0, 280.0, 32.5, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "*~ 0.25",
					"fontface" : 0,
					"id" : "obj-12",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 121.0, 249.0, 48.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "samplervoice~",
					"fontface" : 0,
					"id" : "obj-13",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 161.0, 189.0, 86.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "samplervoice~",
					"fontface" : 0,
					"id" : "obj-14",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 181.0, 213.0, 86.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "samplervoice~",
					"fontface" : 0,
					"id" : "obj-15",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 141.0, 165.0, 86.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "samplervoice~",
					"fontface" : 0,
					"id" : "obj-16",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 121.0, 141.0, 86.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "keyboard sample assignments",
					"linecount" : 3,
					"fontface" : 0,
					"id" : "obj-17",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 0,
					"background" : 0,
					"patching_rect" : [ 372.0, 68.0, 76.0, 46.0 ],
					"underline" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "0 1, 41 2, 48 3, 53 4, 68 5, 96 6",
					"linecount" : 2,
					"fontface" : 0,
					"id" : "obj-18",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"gradient" : 0,
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 358.0, 33.0, 91.0, 31.0 ],
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "if $i3 then $i2",
					"fontface" : 0,
					"id" : "obj-19",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 3,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 268.0, 33.0, 80.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "funbuff",
					"fontface" : 0,
					"id" : "obj-20",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 3,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "int", "int", "bang" ],
					"patching_rect" : [ 268.0, 61.0, 46.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0,
					"save" : [ "#N", "funbuff", 0, ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "gate 4",
					"fontface" : 0,
					"id" : "obj-21",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 4,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "", "", "", "" ],
					"patching_rect" : [ 227.0, 117.0, 59.5, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p samplebuffers",
					"fontface" : 0,
					"id" : "obj-22",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 0,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 287.0, 293.0, 93.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 248.0, 185.0, 211.0, 217.0 ],
						"bglocked" : 0,
						"defrect" : [ 248.0, 185.0, 211.0, 217.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "buffer~ sample6 ahkey.aiff",
									"id" : "obj-1",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 20.0, 138.0, 147.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "buffer~ sample5 epno.aiff",
									"id" : "obj-2",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 20.0, 117.0, 142.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "buffer~ sample4 bass.aiff",
									"id" : "obj-3",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 20.0, 96.0, 140.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "buffer~ sample1 bd+hh.aiff",
									"id" : "obj-4",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 20.0, 33.0, 149.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "buffer~ sample3 cym.aiff",
									"id" : "obj-5",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 20.0, 75.0, 137.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "buffer~ sample2 snare.aiff",
									"id" : "obj-6",
									"fontsize" : 11.595187,
									"numinlets" : 1,
									"fontname" : "Arial",
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 20.0, 54.0, 145.0, 20.0 ]
								}

							}
 ],
						"lines" : [  ]
					}
,
					"saved_object_attributes" : 					{
						"fontface" : 0,
						"fontsize" : 10.0,
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 10.0,
						"fontname" : "Arial",
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "coll",
					"fontface" : 0,
					"id" : "obj-23",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 4,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "", "", "", "" ],
					"patching_rect" : [ 268.0, 86.0, 59.5, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0,
					"coll_data" : 					{
						"count" : 6,
						"data" : [ 							{
								"key" : 1,
								"value" : [ 24, "sample1", 0, 0, 0 ]
							}
, 							{
								"key" : 2,
								"value" : [ 33, "sample2", 0, 0, 0 ]
							}
, 							{
								"key" : 3,
								"value" : [ 50, "sample3", 0.136054, 373.106537, 1 ]
							}
, 							{
								"key" : 4,
								"value" : [ 67, "sample4", 60.204079, 70.476189, 1 ]
							}
, 							{
								"key" : 5,
								"value" : [ 84, "sample5", 0, 0, 0 ]
							}
, 							{
								"key" : 6,
								"value" : [ 108, "sample6", 0, 0, 0 ]
							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"embed" : 1
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route 1 2 3 4",
					"fontface" : 0,
					"id" : "obj-24",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 5,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "", "", "", "", "" ],
					"patching_rect" : [ 121.0, 117.0, 98.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "dac~",
					"fontface" : 0,
					"id" : "obj-25",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 0,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 121.0, 309.0, 36.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pack 0 0 0",
					"fontface" : 0,
					"id" : "obj-26",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 3,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 121.0, 82.0, 64.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "poly 4 1",
					"fontface" : 0,
					"id" : "obj-27",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 3,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "int", "int", "int" ],
					"patching_rect" : [ 121.0, 53.0, 64.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "notein a",
					"fontface" : 0,
					"id" : "obj-28",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"numinlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"fontname" : "Arial",
					"numoutlets" : 3,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"outlettype" : [ "int", "int", "int" ],
					"patching_rect" : [ 121.0, 25.0, 52.0, 20.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"presentation" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 170.5, 210.0, 130.5, 210.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 2 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 2 ],
					"destination" : [ "obj-13", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 190.5, 234.0, 130.5, 234.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 3 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 3 ],
					"destination" : [ "obj-14", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 150.5, 186.0, 130.5, 186.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 1 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 1 ],
					"destination" : [ "obj-15", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-16", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 12.5, 74.0, 117.0, 74.0, 117.0, 49.0, 130.5, 49.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 95.5, 300.0, 130.5, 300.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-25", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 130.5, 300.0, 147.5, 300.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 1 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 1 ],
					"destination" : [ "obj-27", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 147.0, 49.0, 175.5, 49.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 2 ],
					"destination" : [ "obj-26", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 240.5, 293.0, 220.0, 293.0, 220.0, 246.0, 188.5, 246.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-11", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 130.5, 74.0, 236.5, 74.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 130.5, 108.0, 252.0, 108.0, 252.0, 28.0, 277.5, 28.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 367.5, 79.0, 327.0, 79.0, 327.0, 57.0, 277.5, 57.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-21", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
 ]
	}

}
