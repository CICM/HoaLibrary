{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 22.0, 125.0, 551.0, 300.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 22.0, 125.0, 551.0, 300.0 ],
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
					"maxclass" : "message",
					"text" : "0",
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
					"patching_rect" : [ 228.0, 103.0, 32.5, 18.0 ],
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"presentation" : 0,
					"id" : "obj-1",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"gradient" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "stripnote",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 55.0, 68.0, 55.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-2",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "map velocity to amplitude exponentially",
					"linecount" : 3,
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 24.0, 110.0, 90.0, 46.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-3",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "(signal) sample",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 250.0, 257.0, 89.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-4",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "key #, velocity",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 83.0, 7.0, 83.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-5",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "outlet",
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"patching_rect" : [ 224.0, 256.0, 25.0, 25.0 ],
					"presentation" : 0,
					"id" : "obj-6",
					"comment" : "(signal) sample"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "*~",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "signal" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 224.0, 231.0, 72.5, 20.0 ],
					"presentation" : 0,
					"id" : "obj-7",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "line~",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "signal", "bang" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 115.0, 194.0, 35.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-8",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "$1 20",
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
					"patching_rect" : [ 115.0, 169.0, 40.0, 18.0 ],
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"presentation" : 0,
					"id" : "obj-9",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"gradient" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* 1.",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "float" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 115.0, 135.0, 32.5, 20.0 ],
					"presentation" : 0,
					"id" : "obj-10",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/ 127.",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "float" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 115.0, 110.0, 40.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-11",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "loop $1",
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
					"patching_rect" : [ 469.0, 64.0, 49.0, 18.0 ],
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"presentation" : 0,
					"id" : "obj-12",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"gradient" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "inlet",
					"numinlets" : 0,
					"background" : 0,
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"hidden" : 0,
					"patching_rect" : [ 55.0, 7.0, 25.0, 25.0 ],
					"presentation" : 0,
					"id" : "obj-13",
					"comment" : "key #, velocity"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 0 s 0 0 0",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 5,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "", "int", "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 197.0, 35.0, 343.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-14",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sig~",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "signal" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 162.0, 188.0, 32.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-15",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "groove~ sample1",
					"fontsize" : 11.595187,
					"numinlets" : 3,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "signal", "signal" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 278.0, 137.0, 181.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-16",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/ 1.",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "float" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 162.0, 161.0, 53.5, 20.0 ],
					"presentation" : 0,
					"id" : "obj-17",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "mtof",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 162.0, 127.0, 33.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-18",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "mtof",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 197.0, 127.0, 33.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-19",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend set",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 278.0, 64.0, 72.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-20",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 55.0, 35.0, 79.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-21",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "inlet",
					"numinlets" : 0,
					"background" : 0,
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"hidden" : 0,
					"patching_rect" : [ 197.0, 7.0, 25.0, 25.0 ],
					"presentation" : 0,
					"id" : "obj-22",
					"comment" : "base key, sample, loop start, loop end, looping"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "base key, sample, loop start, loop end, looping",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 225.0, 7.0, 250.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-23",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-14", 4 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 530.5, 57.0, 478.5, 57.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 3 ],
					"destination" : [ "obj-16", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 2 ],
					"destination" : [ "obj-16", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-7", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 171.5, 215.0, 236.0, 215.0, 236.0, 128.0, 287.5, 128.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 237.5, 128.0, 287.5, 128.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 478.5, 91.0, 287.5, 91.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 1 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 64.5, 94.0, 213.0, 94.0, 213.0, 100.0, 237.5, 100.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-6", 0 ],
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
					"midpoints" : [ 124.5, 223.0, 233.5, 223.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-17", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-15", 0 ],
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
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 64.5, 94.0, 171.5, 94.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-10", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 124.5, 131.0, 138.0, 131.0 ]
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
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 1 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 1 ],
					"destination" : [ "obj-2", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 124.5, 61.0, 100.5, 61.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-2", 0 ],
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
					"midpoints" : [  ]
				}

			}
 ]
	}

}
