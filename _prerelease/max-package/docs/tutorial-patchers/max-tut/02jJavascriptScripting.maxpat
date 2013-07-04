{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 27.0, 48.0, 1024.0, 608.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 27.0, 48.0, 1024.0, 608.0 ],
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
					"maxclass" : "comment",
					"text" : "current step:",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 558.0, 474.0, 75.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-1",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "current value:",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 406.0, 474.0, 81.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-2",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "+ 1",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 635.0, 510.0, 32.5, 20.0 ],
					"presentation" : 0,
					"id" : "obj-3",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "min, select $2 $1",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 717.0, 308.0, 98.0, 18.0 ],
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"presentation" : 0,
					"id" : "obj-4",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"gradient" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "size $1",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 127.0, 297.0, 47.0, 18.0 ],
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"presentation" : 0,
					"id" : "obj-5",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"gradient" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pack 0 0",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 592.0, 546.0, 62.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-6",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "multislider",
					"border_right" : 0,
					"numinlets" : 1,
					"background" : 0,
					"peakcolor" : [ 0.498039, 0.498039, 0.498039, 1.0 ],
					"size" : 1,
					"setstyle" : 1,
					"slidercolor" : [ 0.972549, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"compatibility" : 0,
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"signed" : 0,
					"candicane6" : [ 0.7348, 0.03601, 0.78958, 1.0 ],
					"ignoreclick" : 0,
					"border_top" : 0,
					"outlettype" : [ "", "" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"contdata" : 0,
					"candicane5" : [ 0.58784, 0.82881, 0.43166, 1.0 ],
					"ghostbar" : 0,
					"candicane4" : [ 0.44088, 0.62161, 0.07375, 1.0 ],
					"hidden" : 0,
					"border_left" : 0,
					"patching_rect" : [ 717.0, 365.0, 205.0, 112.0 ],
					"presentation" : 0,
					"id" : "obj-7",
					"candicane3" : [ 0.29392, 0.41441, 0.71583, 1.0 ],
					"candicane2" : [ 0.14696, 0.2072, 0.35792, 1.0 ],
					"setminmax" : [ 0.0, 127.0 ],
					"border_bottom" : 0,
					"settype" : 0,
					"orientation" : 1,
					"drawpeaks" : 0,
					"spacing" : 0,
					"thickness" : 2,
					"candicane8" : [ 0.02872, 0.45042, 0.50541, 1.0 ],
					"candycane" : 1,
					"candicane7" : [ 0.88176, 0.24321, 0.14749, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"mouseup" : 0,
					"numoutlets" : 2,
					"outputonclick" : 0,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"format" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "bang" ],
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 635.0, 474.0, 49.0, 20.0 ],
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation" : 0,
					"id" : "obj-8",
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"cantchange" : 0,
					"triscale" : 0.9,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "reverse the sequence",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 167.0, 345.0, 122.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-9",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "make some sliders",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 105.0, 269.0, 107.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-10",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "<- turn it on",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 75.0, 345.0, 69.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-11",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"mouseup" : 0,
					"numoutlets" : 2,
					"outputonclick" : 0,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"format" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "bang" ],
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 490.0, 474.0, 49.0, 20.0 ],
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation" : 0,
					"id" : "obj-12",
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"cantchange" : 0,
					"triscale" : 0.9,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reverse $1",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 146.0, 379.0, 65.0, 18.0 ],
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"presentation" : 0,
					"id" : "obj-13",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"gradient" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 1,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 146.0, 345.0, 20.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-14",
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "noteout",
					"fontsize" : 11.595187,
					"numinlets" : 3,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 490.0, 546.0, 49.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-15",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "makenote 64 250",
					"fontsize" : 11.595187,
					"numinlets" : 3,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 490.0, 510.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-16",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "metro 250",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "bang" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 54.0, 379.0, 63.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-17",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 1,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 54.0, 345.0, 20.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-18",
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triangle" : 1,
					"maximum" : "<none>",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"mouseup" : 0,
					"numoutlets" : 2,
					"outputonclick" : 0,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"format" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "bang" ],
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 54.0, 268.0, 48.0, 20.0 ],
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"presentation" : 0,
					"id" : "obj-19",
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"cantchange" : 0,
					"triscale" : 0.9,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "sliders $1",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 54.0, 297.0, 60.0, 18.0 ],
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"presentation" : 0,
					"id" : "obj-20",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"gradient" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"varname" : "thejs",
					"text" : "js autosurface.js",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.196078, 1.0, 0.090196, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "", "" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 490.0, 445.0, 94.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-21",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
 ],
		"lines" : [ 			{
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
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 63.5, 294.0, 136.5, 294.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 155.5, 417.0, 499.5, 417.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 63.5, 417.0, 499.5, 417.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 63.5, 331.0, 499.5, 331.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 499.5, 498.0, 601.5, 498.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 1 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 574.5, 467.0, 644.5, 467.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 644.5, 498.0, 644.5, 498.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-6", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 601.5, 575.0, 689.0, 575.0, 689.0, 304.0, 726.5, 304.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 136.5, 326.0, 726.5, 326.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 1 ],
					"destination" : [ "obj-15", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 580.5, 531.0, 514.5, 531.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
 ]
	}

}
