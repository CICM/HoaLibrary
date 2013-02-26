{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 0,
			"revision" : 8
		}
,
		"rect" : [ 36.0, 128.0, 875.0, 639.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 0,
		"toolbarvisible" : 0,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"title" : "|-- hoa.library overview --|",
		"boxes" : [ 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 208.78125, 20.75, 73.0, 20.0 ],
					"text" : "version 1.1",
					"textcolor" : [ 0.9404, 0.940544, 0.940332, 1.0 ],
					"varname" : "autohelp_top_title[4]"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-27",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 209.78125, 21.75, 73.0, 20.0 ],
					"text" : "version 1.1",
					"textcolor" : [ 0.424631, 0.424696, 0.4246, 0.21 ],
					"varname" : "autohelp_top_title[5]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-29",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 208.78125, 20.75, 74.0, 21.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"args" : [ "@width", 300 ],
					"id" : "obj-8",
					"maxclass" : "bpatcher",
					"name" : "hoa.helpheader.maxpat",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.78125, 10.75, 303.0, 53.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-60",
					"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.78125, 5.75, 868.21875, 8.775246 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-61",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3.78125, 4.75, 868.21875, 8.775246 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-58",
					"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.78125, 69.75, 868.21875, 8.775246 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-59",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3.78125, 68.75, 868.21875, 8.775246 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 7.263873,
					"hidden" : 1,
					"id" : "obj-55",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -184.4375, 102.875, 55.0, 15.0 ],
					"text" : "loadmess 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.425629,
					"frgb" : 0.0,
					"hidden" : 1,
					"id" : "obj-54",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 14.5, 63.75, 33.28125, 17.0 ],
					"text" : "grow"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-52",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 3,
					"outlettype" : [ "bang", "bang", "" ],
					"patching_rect" : [ -184.4375, 148.257935, 46.0, 20.0 ],
					"text" : "sel 0 1"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-51",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 4.78125, 65.525246, 13.0, 13.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"frgb" : 0.0,
					"id" : "obj-19",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 407.5625, 15.75, 454.5, 19.0 ],
					"text" : "Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012-13 CICM / Universite Paris 8",
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-28",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 407.5625, 15.75, 454.5, 19.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-13",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -269.9375, 41.75, 177.0, 17.0 ],
					"text" : "window flags grow, window exec"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-6",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -253.4375, 64.75, 190.0, 17.0 ],
					"text" : "window flags nogrow, window exec"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-42",
					"maxclass" : "newobj",
					"numinlets" : 4,
					"numoutlets" : 0,
					"patching_rect" : [ -156.0, 247.257935, 143.0, 20.0 ],
					"text" : "bgcolor 0.93 0.93 0.92 1."
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.776471, 0.776471, 0.776471, 0.0 ],
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-33",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 651.0, 279.0, 206.0, 40.0 ],
					"text" : "This library is released under the terms of the GNU licence.",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 0.81 ],
					"varname" : "autohelp_top_description[2]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-34",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 651.0, 279.0, 206.0, 40.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-18",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 33.6875, 522.5, 817.3125, 23.0 ],
					"textcolor" : [ 0.192668, 0.192697, 0.192653, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
					"bordercolor" : [ 0.999903, 1.0, 0.99983, 1.0 ],
					"id" : "obj-21",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 23.0625, 521.5, 6.0, 80.0 ],
					"rounded" : 5
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-17",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 18.0625, 514.5, 838.9375, 93.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"arrows" : 1,
					"border" : 2.0,
					"id" : "obj-16",
					"justification" : 1,
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 657.0, 216.5, 22.0, 10.0 ]
				}

			}
, 			{
				"box" : 				{
					"border" : 2.0,
					"id" : "obj-15",
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 679.0, 202.5, 12.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-12",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 662.0, 165.257935, 154.5, 33.0 ],
					"text" : "Click in the tab to open the appropriate help file.",
					"textcolor" : [ 0.260204, 0.260204, 0.260204, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -94.0, 137.257935, 72.0, 20.0 ],
					"text" : "loadmess 0"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 797.0625, 43.75, 65.0, 20.0 ],
					"text" : "contact us",
					"textcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"handoff" : "",
					"hilite" : 0,
					"id" : "obj-10",
					"maxclass" : "ubutton",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "", "int" ],
					"patching_rect" : [ 797.0625, 43.75, 65.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 619.529907, 138.725479, 92.470032, 20.274523 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-11",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 812.395813, 68.75, 318.0, 26.0 ],
					"text" : ";\rmax launchbrowser http://www.mshparisnord.fr/hoalibrary/en/contacts/"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ -269.9375, 91.25, 69.0, 20.0 ],
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
					"text" : "thispatcher"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.776471, 0.776471, 0.776471, 0.0 ],
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-82",
					"linecount" : 7,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 651.0, 356.5, 213.0, 125.0 ],
					"text" : "NB : to see references pages you must before deactivate the option \"Use New Documentation Rendering\" in the global max preferences window. This is a current limitation of Max version (6.0.8).",
					"textcolor" : [ 0.74902, 0.203922, 0.235294, 0.81 ],
					"varname" : "autohelp_top_description[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-80",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 692.0625, 43.75, 96.0, 20.0 ],
					"text" : "visit our website",
					"textcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 33.0625, 623.0, 782.0, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-38",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 32.0625, 622.0, 782.0, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 0,
							"revision" : 8
						}
,
						"rect" : [ 497.0, 168.0, 292.0, 315.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
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
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 191.0, 174.333344, 84.0, 22.0 ],
									"text" : "prepend set"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-19",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 157.5, 142.0, 32.5, 18.0 ],
									"text" : "set"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-15",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 113.0, 96.0, 97.0, 20.0 ],
									"text" : "route blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 27.0, 231.5, 74.0, 20.0 ],
									"text" : "prepend set"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 27.0, 206.5, 79.0, 20.0 ],
									"text" : "route symbol"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 28,
										"data" : [ 											{
												"key" : "hoa.encoder~",
												"value" : [ "hoa.encoder~ creates the spherical harmonics of a signal depending of an given order and the position on a circle." ]
											}
, 											{
												"key" : "hoa.decoder~",
												"value" : [ "hoa.decoder~ decodes an ambisonic soundfield for a given number of loudspeakers." ]
											}
, 											{
												"key" : "hoa.rotate~",
												"value" : [ "hoa.rotate~ allows you to rotate the ambisonic soundfield." ]
											}
, 											{
												"key" : "hoa.plug~",
												"value" : [ "hoa.plug~ facilitates the modularization of patches for ambisonic processing." ]
											}
, 											{
												"key" : "hoa.connect",
												"value" : [ "hoa.connect helps to connect the hoa externals together. You must drag-select the objects then bang the hoa.connect to connect the objects together. 1st argument is the ambisonic order and the 2nd is the number of decoder outputs and dac inlets." ]
											}
, 											{
												"key" : "hoa.dac~",
												"value" : [ "hoa.dac~ makes easier the setting of the channels. It works like a dac~ object but you can use the matlab syntax :  to set the loudspeakers routing." ]
											}
, 											{
												"key" : "hoa.binaural~",
												"value" : [ "hoa.binaural~ virtualizes ambisonic soundfield for two headspeakers. It uses hrtf to perform FIR filtering on the incoming signal. Hrtf are extracted from the sipic hrtf database. hoa.binaural~ works up to the order 35 and at 44100 Hz only." ]
											}
, 											{
												"key" : "hoa.pi",
												"value" : [ "hoa.pi is for peoples that never remember more than 4 decimals or want to initialize a good Pi number. " ]
											}
, 											{
												"key" : "hoa.scope~",
												"value" : [ "hoa.scope~ displays the harmonics of an ambisonic soundfield on a circle. The number of harmonics is defined at the object creation with the attribute @order and create order * 2 + 1 inputs (ex : hoa.scope~ @order 7)." ]
											}
, 											{
												"key" : "hoa.projector~",
												"value" : [ "hoa.projector~ discretizes the ambisonic soundfield into an array of virtual loudspeakers and gives a access to a new sound domain." ]
											}
, 											{
												"key" : "hoa.recomposer~",
												"value" : [ "hoa.recomposer~ recomposes a plane wave decomposition into circular harmonics and allows you to perform a fish eye operation." ]
											}
, 											{
												"key" : "hoa.meter~",
												"value" : [ "hoa.meter~ displays the peak levels for a circurlar array of loudspeakers. It computes and displays the energy vector. The number of loudspeakers is defined at the object creation with the attribute @ls and the offset of the loudspeakers is defined with the attribute @offset (ex : hoa.meter~ @ld 16 @offset 0.5)." ]
											}
, 											{
												"key" : "hoa.record~",
												"value" : [ "hoa.record~ creates an sfrecord~ object with the best arguments to record of an ambisonic soundfield. The limit defined in Max is 15 inputs then the maximum order can be 7." ]
											}
, 											{
												"key" : "hoa.play~",
												"value" : [ "hoa.play~ creates an sfplay~ object with the best arguments to play of an ambisonic soundfield." ]
											}
, 											{
												"key" : "hoa.optim~",
												"value" : [ "hoa.optim~ applies an optimization to the cylindrical harmonics." ]
											}
, 											{
												"key" : "hoa.map",
												"value" : [ "hoa.map is a 2D spatialization user interface tool. It allows you to spatialize several point sources." ]
											}
, 											{
												"key" : "hoa.control",
												"value" : [ "hoa.control displays the representation of the harmonics of an encoded sound for a given order. optimization. azimuth value and wide value. It can be used to understand of the encoding behavior. But also the optimization and fractionnal order effect (wider) or as a controller for the 'super encoder' set." ]
											}
, 											{
												"key" : "hoa.stereo~",
												"value" : [ "hoa.stereo~ decodes an ambisonic soundfield for stereophonic system." ]
											}
, 											{
												"key" : "hoa.convolve~",
												"value" : [ "hoa.convolve~ uses FIR and FFT filtering to apply reveberation on harmonics dependant signals. The zero latency convolution is optimized with the Gardner algorithm and uses the circular harmonics behavior to reduce the number of FFT convolution." ]
											}
, 											{
												"key" : "hoa.irconverter~",
												"value" : [ "hoa.irconverter~ create the circular harmonic dependant signals of a discrete circular impulse response for ambisonics processing. It facilitates the convertion for the use of hoa.convolve~ and allows you to changes the incidence angles of the discrete impulse response." ]
											}
, 											{
												"key" : "hoa.wider~",
												"value" : [ "hoa.wider~ can be used to wide the diffusion of a localised sound. The order depending signals are weighted and appear in a logarithmic way to have linear changes." ]
											}
, 											{
												"key" : "hoa.delay~",
												"value" : [ "hoa.delay~ allows you to delay the differents harmonics." ]
											}
, 											{
												"key" : "hoa.decorrelation~",
												"value" : [ "hoa.decorrelation~ allows you to delay the differents harmonics depending to the harmonic number to decorrelate the harmonics and generate a diffuse soundfield." ]
											}
, 											{
												"key" : "hoa.grain~",
												"value" : [ "hoa.grain~ synthesizes a diffused sound field. It uses delay lines and amplitude modulation to create streams of grains. The parameters are scaled depending to the orders to generate a granular sound field." ]
											}
, 											{
												"key" : "hoa.mirror~",
												"value" : [ "hoa.mirror~ applies a weight on the negatives harmonics to add the mirror image of a soundfield to itself." ]
											}
, 											{
												"key" : "hoa.mixer~",
												"value" : [ "hoa.mixer~ helps to understand ambisonics and the behavior of the circular harmonics." ]
											}
, 											{
												"key" : "hoa.reverberation~",
												"value" : [ "hoa.reverberation~ use a algorithm based on feedback network delay and doppler effect to simulate a room reveberation." ]
											}
, 											{
												"key" : "hoa.halo~",
												"value" : [ "hoa.halo~ highlights a part of the soundfield. It puts all the soundfield in the dark exept where you're directing the 'sound-flashlight'. The spread value controls the diffusion of the 'sound-flashlight'." ]
											}
 ]
									}
,
									"color" : [ 0.590533, 0.704632, 0.839216, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 16.680918,
									"id" : "obj-21",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 27.0, 174.333344, 120.0, 25.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll description"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-26",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-28",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 157.5, 276.5, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-29",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 27.0, 276.5, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 200.5, 235.916672, 167.0, 235.916672 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 200.5, 130.666672, 36.5, 130.666672 ],
									"source" : [ "obj-15", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 167.0, 263.75, 36.5, 263.75 ],
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ -67.875, 514.5, 79.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 14.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 14.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p description"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-25",
					"linecolor" : [ 1.0, 1.0, 1.0, 0.5 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 36.5, 202.257935, 579.0, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 35.5, 201.257935, 579.0, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -83.9375, 203.257935, 77.0, 20.0 ],
					"text" : "prepend nav"
				}

			}
, 			{
				"box" : 				{
					"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
					"fadeunselect" : 1,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"htabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
					"htextcolor" : [ 1.0, 1.0, 1.0, 0.95 ],
					"id" : "obj-20",
					"margin" : 0,
					"maxclass" : "tab",
					"multiline" : 0,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 25.5, 165.257935, 605.125, 30.242065 ],
					"rounded" : 0.0,
					"spacing_x" : 1.0,
					"spacing_y" : 0.0,
					"tabs" : [ "All", "Basics", "GUI", "Advanced", "Utility", "Effects", "Operators" ]
				}

			}
, 			{
				"box" : 				{
					"clickthrough" : 1,
					"embed" : 1,
					"id" : "obj-22",
					"maxclass" : "bpatcher",
					"numinlets" : 1,
					"numoutlets" : 1,
					"offset" : [ -1313.0, 0.0 ],
					"outlettype" : [ "blank" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 0,
							"revision" : 8
						}
,
						"rect" : [ 62.0, 339.0, 605.0, 288.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
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
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-21",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 4334.0, 264.0, 248.0, 20.0 ],
									"text" : "Operators and tools shortcuts for hoa.plug~",
									"textcolor" : [ 0.375912, 0.375912, 0.375912, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-20",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 3994.0, 0.0, 617.0, 282.0 ],
									"rounded" : 6.0,
									"spacing_x" : 20.0,
									"spacing_y" : 5.0,
									"tabs" : [ "hoa.abs~", "hoa.all", "hoa.amp~", "hoa.div~", "hoa.equals~", "hoa.greaterthan~", "hoa.greaterthaneq~", "hoa.highpass~", "hoa.lessthan~", "hoa.lessthaneq~", "hoa.minus~", "hoa.modulo~", "hoa.name1~", "hoa.name2~", "hoa.notequals~", "hoa.nothing~", "hoa.onepole~", "hoa.plus~", "hoa.plusequals~", "hoa.rdiv~", "hoa.receive", "hoa.receive~", "hoa.rminus~", "hoa.send", "hoa.send~", "hoa.snapshot~", "hoa.times~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-47",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 3881.0, 324.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-48",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 3881.0, 295.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-45",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 3217.0, 338.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-46",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 3217.0, 309.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-42",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 2556.0, 338.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-44",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 2556.0, 309.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-38",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 1894.0, 343.5, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-40",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 1894.0, 307.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-34",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 1241.0, 343.5, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-36",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 1241.0, 307.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 520.0, 372.5, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 520.0, 336.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-43",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 679.0, 336.0, 70.0, 20.0 ],
									"text" : "renumber"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-41",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 355.0, 487.0, 177.0, 20.0 ],
									"text" : "hoa.control"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 6,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.delay~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.grain~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.mirror~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.mixer~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.reverberation~" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.decorrelation~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-39",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 3942.0, 325.0, 128.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-effects"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 6,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.plug~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.connect" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.dac~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.pi" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.record~" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.play~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-37",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 3278.0, 338.0, 119.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-utility"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 6,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.projector~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.recomposer~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.binaural~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.stereo~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.convolve~" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.irconverter~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-35",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 2617.0, 338.0, 130.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-special"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 4,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.scope~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.meter~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.map" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.control" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-33",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 1955.0, 343.5, 105.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-gui"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 5,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.encoder~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.decoder~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.rotate~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.optim~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.wider~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 1302.0, 343.5, 126.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-basics"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-32",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 320.5, 422.0, 91.0, 22.0 ],
									"text" : "route symbol"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 22,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.encoder~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.decoder~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.rotate~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.plug~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.connect" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.dac~" ]
											}
, 											{
												"key" : 6,
												"value" : [ "hoa.binaural~" ]
											}
, 											{
												"key" : 7,
												"value" : [ "hoa.pi" ]
											}
, 											{
												"key" : 8,
												"value" : [ "hoa.scope~" ]
											}
, 											{
												"key" : 9,
												"value" : [ "hoa.projector~" ]
											}
, 											{
												"key" : 10,
												"value" : [ "hoa.recomposer~" ]
											}
, 											{
												"key" : 11,
												"value" : [ "hoa.meter~" ]
											}
, 											{
												"key" : 12,
												"value" : [ "hoa.record~" ]
											}
, 											{
												"key" : 13,
												"value" : [ "hoa.play~" ]
											}
, 											{
												"key" : 14,
												"value" : [ "hoa.optim~" ]
											}
, 											{
												"key" : 15,
												"value" : [ "hoa.spat" ]
											}
, 											{
												"key" : 16,
												"value" : [ "hoa.control" ]
											}
, 											{
												"key" : 17,
												"value" : [ "hoa.stereo~" ]
											}
, 											{
												"key" : 18,
												"value" : [ "hoa.convolve~" ]
											}
, 											{
												"key" : 19,
												"value" : [ "hoa.irconverter~" ]
											}
, 											{
												"key" : 20,
												"value" : [ "hoa.wider~" ]
											}
, 											{
												"key" : 21,
												"value" : [ "hoa.halo~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 581.0, 372.5, 101.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-all"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.32331, 0.623465, 0.84, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hidden" : 1,
									"id" : "obj-73",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 0,
											"revision" : 8
										}
,
										"rect" : [ 50.0, 94.0, 337.0, 182.0 ],
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
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 105.0, 60.0, 83.0, 20.0 ],
													"text" : "prepend help",
													"varname" : "phelp"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-3",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 105.0, 90.5, 56.0, 20.0 ],
													"text" : "pcontrol"
												}

											}
, 											{
												"box" : 												{
													"comment" : "From umenu label out",
													"id" : "obj-4",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 105.0, 15.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-3", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-2", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-4", 0 ]
												}

											}
 ]
									}
,
									"patching_rect" : [ 290.5, 313.5, 69.0, 20.0 ],
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
									"text" : "p see_help"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-31",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "int", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 447.0, 336.0, 50.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-22",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 320.5, 484.5, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 424.0, -110.0, 69.0, 22.0 ],
									"text" : "route nav"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-30",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 949.0, -55.0, 81.0, 17.0 ],
									"text" : "offset -4000 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-29",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 861.5, -55.0, 81.0, 17.0 ],
									"text" : "offset -3300 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-28",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 774.0, -55.0, 84.0, 17.0 ],
									"text" : "offset -2636. 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-27",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 686.5, -55.0, 81.0, 17.0 ],
									"text" : "offset -1975 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-24",
									"maxclass" : "newobj",
									"numinlets" : 8,
									"numoutlets" : 8,
									"outlettype" : [ "bang", "bang", "bang", "bang", "bang", "bang", "bang", "" ],
									"patching_rect" : [ 424.0, -82.0, 631.5, 19.0 ],
									"text" : "sel 0 1 2 3 4 5 6"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 599.0, -55.0, 81.0, 17.0 ],
									"text" : "offset -1313 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-25",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 511.5, -55.0, 75.0, 17.0 ],
									"text" : "offset -660 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-26",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 424.0, -55.0, 58.0, 17.0 ],
									"text" : "offset 0 0"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-2",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 424.0, -141.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.934731,
									"hidden" : 1,
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 424.0, -29.0, 67.0, 20.0 ],
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
									"text" : "thispatcher"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-19",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 3297.0, -26.0, 26.0, 20.0 ],
									"text" : "FX"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-18",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 3300.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.delay~", "hoa.grain~", "hoa.mirror~", "hoa.mixer~", "hoa.reverberation~", "hoa.decorrelation~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1975.25, -26.0, 50.0, 20.0 ],
									"text" : "Special"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-17",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1975.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.projector~", "hoa.recomposer~", "hoa.binaural~", "hoa.stereo~", "hoa.convolve~", "hoa.irconverter~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 2636.0, -26.0, 40.0, 20.0 ],
									"text" : "Utility"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-15",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 2636.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.plug~", "hoa.connect", "hoa.dac~", "hoa.pi", "hoa.record~", "hoa.play~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-11",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1313.0, -26.0, 32.0, 20.0 ],
									"text" : "GUI"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-12",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1313.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.scope~", "hoa.meter~", "hoa.map", "hoa.control" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-8",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 660.0, -20.75, 46.0, 20.0 ],
									"text" : "Basics"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-10",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 660.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.encoder~", "hoa.decoder~", "hoa.rotate~", "hoa.optim~", "hoa.wider~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 11.0, -20.75, 24.0, 20.0 ],
									"text" : "All"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-4",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 0.0, 0.0, 600.0, 280.0 ],
									"rounded" : 6.0,
									"spacing_x" : 20.0,
									"spacing_y" : 5.0,
									"tabs" : [ "hoa.encoder~", "hoa.decoder~", "hoa.rotate~", "hoa.plug~", "hoa.connect", "hoa.dac~", "hoa.binaural~", "hoa.pi", "hoa.scope~", "hoa.projector~", "hoa.recomposer~", "hoa.meter~", "hoa.record~", "hoa.play~", "hoa.optim~", "hoa.map", "hoa.control", "hoa.stereo~", "hoa.convolve~", "hoa.irconverter~", "hoa.wider~", "hoa.halo~" ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-10", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-10", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-12", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-12", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-46", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-15", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-15", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-17", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-17", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-48", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-18", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-18", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-20", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-25", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-27", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-30", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-27", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-28", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-41", 1 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-33", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-35", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-13", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-36", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-34", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-37", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-4", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-4", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-4", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-40", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-40", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-42", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-43", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-35", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-44", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-45", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-37", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-46", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-45", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-48", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-48", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-24", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 25.5, 210.5, 605.125, 288.0 ]
				}

			}
, 			{
				"box" : 				{
					"handoff" : "",
					"hilite" : 0,
					"id" : "obj-63",
					"maxclass" : "ubutton",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "", "int" ],
					"patching_rect" : [ 692.0625, 43.75, 96.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 604.529907, 123.725479, 92.470032, 20.274523 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-65",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 717.729187, 68.75, 261.5, 26.0 ],
					"text" : ";\rmax launchbrowser http://www.mshparisnord.fr/hoalibrary/en/"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-56",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ -83.9375, 289.0, 45.0, 17.0 ],
					"text" : "onecopy"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-5",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 13.9375, 81.5, 854.0, 57.0 ],
					"text" : "The hoa.library is a set of externals that encodes a signal in ambisonic spherical harmonics and decodes the ambisonic soundfield for a circle array of loudspeakers. This library allows you to synthesize, transform and modulate sound fields. It has been elaborated to facilitate the use of the sphericals harmonics and the routing in the ambisonics domain.",
					"textcolor" : [ 0.27596, 0.276002, 0.27594, 1.0 ],
					"varname" : "autohelp_top_description"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-77",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 18.0625, 156.257935, 622.0, 342.242065 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-4",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 651.0, 356.5, 206.0, 125.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-14",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 662.0, 165.257935, 154.5, 33.0 ],
					"rounded" : 0,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-26",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 13.9375, 81.25, 849.5625, 58.25 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-67",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 692.0625, 43.75, 96.0, 20.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-69",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 797.0625, 43.75, 65.0, 20.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-10", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-52", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-55", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-63", 1 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "hoa.helpheader.maxpat",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/MaxMsp/Max/Cycling '74/HoaLibrary/others",
				"patcherrelativepath" : "../../../Cycling '74/HoaLibrary/others",
				"type" : "JSON",
				"implicit" : 1
			}
 ]
	}

}
