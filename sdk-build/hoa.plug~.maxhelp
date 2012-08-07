{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 48.0, 92.0, 1047.0, 673.0 ],
		"bglocked" : 0,
		"defrect" : [ 48.0, 92.0, 1047.0, 673.0 ],
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
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "" ],
					"patching_rect" : [ 525.0, 586.0, 62.0, 20.0 ],
					"text" : "hoa.plug~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 473.0, 344.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 490.0, 421.0, 47.0, 20.0 ],
					"text" : "iterator"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
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
									"comment" : "",
									"id" : "obj-1",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 378.0, 209.0, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 424.0, 446.0, 18.0, 20.0 ],
					"saved_object_attributes" : 					{
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0,
						"globalpatchername" : ""
					}
,
					"text" : "p",
					"varname" : "qsqs"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-4",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 224.0, 223.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-12",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 0,
					"patching_rect" : [ 60.0, 495.0, 235.0, 20.0 ],
					"text" : "dac~ 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 60.0, 210.0, 45.0, 20.0 ],
					"text" : "noise~"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 15,
					"numoutlets" : 16,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" ],
					"patching_rect" : [ 60.0, 420.0, 235.0, 20.0 ],
					"text" : "hoa.decoder~ 7 16"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 60.0, 270.0, 235.0, 20.0 ],
					"text" : "hoa.plug~ 7 volume~ pre"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 15,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"patching_rect" : [ 60.0, 345.0, 235.0, 20.0 ],
					"text" : "hoa.plug~ 7 volume~ post"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "ezadc~",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 375.0, 285.0, 45.0, 45.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-59",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 497.75, 6.0, 293.0, 33.0 ],
					"text" : "hoa.plug~ by Julien Colafrancesco & Pierre Guillot\n© 2012 CICM / Universite Paris 8"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 20.871338,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"id" : "obj-2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.0, 6.0, 485.0, 30.0 ],
					"text" : "hoa.plug~",
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ],
					"varname" : "autohelp_top_title"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.754705,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"id" : "obj-3",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.0, 35.0, 503.0, 21.0 ],
					"text" : "Embed a stream of patcher for hoa processing.",
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ],
					"varname" : "autohelp_top_digest"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-5",
					"linecount" : 8,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.0, 56.0, 595.0, 113.0 ],
					"text" : "hoa.plug~ facilitates the modularization of patches for ambisonic processing. Take a patch contained within a single patcher window, place it within a patcher object, add inlet s and outlet s, and you can instantiate it as an object (or many copies of that object) capable of its own messaging, embedded within a larger patch.\n\nThe number of inlets is determined by the number of inlet objects contained within its subpatch window and the third argument. The messaging which the patcher object can handle depends upon the patch you embed within it.\n\nDouble-clicking on a patcher object with the mouse opens the first instance of the patcher in a new window.",
					"varname" : "autohelp_top_description"
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"grad1" : [ 0.27, 0.35, 0.47, 1.0 ],
					"grad2" : [ 0.85, 0.85, 0.85, 1.0 ],
					"id" : "obj-9",
					"maxclass" : "panel",
					"mode" : 1,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2.0, 4.0, 495.0, 52.0 ],
					"varname" : "autohelp_top_panel"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 14 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 13 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 12 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 11 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 10 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 9 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 8 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 7 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 6 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 5 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 4 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 3 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 2 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 1 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 14 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 13 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 12 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 11 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 10 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 9 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 8 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 7 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 6 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 5 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 4 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 3 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 2 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [ 233.5, 255.0, 69.5, 255.0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 15 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 14 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 13 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 12 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 11 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 10 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 9 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 8 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 7 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 6 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 5 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 4 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 3 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 2 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 1 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-8", 0 ]
				}

			}
 ]
	}

}
