{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 68.0, 69.0, 593.0, 258.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 68.0, 69.0, 593.0, 258.0 ],
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
					"patching_rect" : [ 48.0, 177.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-27",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print thru-makenote",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 48.0, 212.0, 111.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-16",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print thru-sustain",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 425.0, 146.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-24",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
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
					"patching_rect" : [ 425.0, 115.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-25",
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
					"patching_rect" : [ 538.0, 37.0, 20.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-23",
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "notein",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 3,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 425.0, 36.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-22",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sustain",
					"fontsize" : 11.595187,
					"numinlets" : 3,
					"background" : 0,
					"color" : [ 0.141176, 0.768627, 0.0, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 425.0, 79.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-21",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print thru-flush",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 244.0, 180.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-20",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
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
					"patching_rect" : [ 244.0, 153.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-19",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 1,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "bang" ],
					"bgcolor" : [ 0.91328, 0.91328, 0.91328, 0.75 ],
					"hidden" : 0,
					"fgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"patching_rect" : [ 199.0, 62.0, 31.0, 31.0 ],
					"outlinecolor" : [ 0.71328, 0.71328, 0.71328, 1.0 ],
					"presentation" : 0,
					"id" : "obj-17",
					"blinkcolor" : [ 1.0, 0.890196, 0.090196, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "flush",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"background" : 0,
					"color" : [ 0.141176, 0.768627, 0.0, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 244.0, 126.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-15",
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
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 325.0, 98.0, 50.0, 20.0 ],
					"htextcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-14",
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"cantchange" : 0,
					"triscale" : 1.0,
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
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 244.0, 98.0, 50.0, 20.0 ],
					"htextcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-13",
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"cantchange" : 0,
					"triscale" : 1.0,
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
					"color" : [ 0.141176, 0.768627, 0.0, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 244.0, 66.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-12",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "notein",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 3,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 244.0, 35.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-11",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "noteout",
					"fontsize" : 11.595187,
					"numinlets" : 3,
					"background" : 0,
					"color" : [ 0.05098, 0.027451, 0.478431, 1.0 ],
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 439.0, 215.0, 49.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-10",
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
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 129.0, 148.0, 40.0, 20.0 ],
					"htextcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-9",
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"cantchange" : 0,
					"triscale" : 1.0,
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
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 48.0, 148.0, 40.0, 20.0 ],
					"htextcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-8",
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"cantchange" : 0,
					"triscale" : 1.0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "makenote 127 50",
					"fontsize" : 11.595187,
					"numinlets" : 3,
					"background" : 0,
					"color" : [ 0.141176, 0.768627, 0.0, 1.0 ],
					"numoutlets" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "int", "int" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 48.0, 117.0, 100.0, 20.0 ],
					"presentation" : 0,
					"id" : "obj-7",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "note",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 43.0, 31.0, 31.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"id" : "obj-6",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "vel",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 85.0, 31.0, 31.0, 20.0 ],
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
					"maxclass" : "comment",
					"text" : "dur",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"background" : 0,
					"numoutlets" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 126.0, 31.0, 31.0, 20.0 ],
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
					"maxclass" : "slider",
					"numinlets" : 1,
					"knobcolor" : [ 0.2, 0.2, 0.2, 1.0 ],
					"background" : 0,
					"size" : 100.0,
					"numoutlets" : 1,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"floatoutput" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"mult" : 10.0,
					"min" : 20.0,
					"hidden" : 0,
					"patching_rect" : [ 129.0, 56.0, 18.0, 55.0 ],
					"relative" : 0,
					"presentation" : 0,
					"id" : "obj-3",
					"orientation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "slider",
					"numinlets" : 1,
					"knobcolor" : [ 0.2, 0.2, 0.2, 1.0 ],
					"background" : 0,
					"size" : 128.0,
					"numoutlets" : 1,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"floatoutput" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"mult" : 1.0,
					"min" : 0.0,
					"hidden" : 0,
					"patching_rect" : [ 89.0, 56.0, 18.0, 55.0 ],
					"relative" : 0,
					"presentation" : 0,
					"id" : "obj-2",
					"orientation" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "slider",
					"numinlets" : 1,
					"knobcolor" : [ 0.2, 0.2, 0.2, 1.0 ],
					"background" : 0,
					"size" : 128.0,
					"numoutlets" : 1,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"outlettype" : [ "" ],
					"floatoutput" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"mult" : 1.0,
					"min" : 0.0,
					"hidden" : 0,
					"patching_rect" : [ 48.0, 56.0, 18.0, 55.0 ],
					"relative" : 0,
					"presentation" : 0,
					"id" : "obj-1",
					"orientation" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-7", 1 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-7", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-7", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 1 ],
					"destination" : [ "obj-12", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 1 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-15", 1 ],
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
					"midpoints" : [ 208.5, 122.0, 253.5, 122.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 1 ],
					"destination" : [ "obj-19", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 1 ],
					"destination" : [ "obj-21", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-21", 2 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 1 ],
					"destination" : [ "obj-25", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-27", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 57.5, 202.0, 231.0, 202.0, 231.0, 210.0, 448.5, 210.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
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
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 253.5, 174.0, 231.0, 174.0, 231.0, 210.0, 448.5, 210.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 434.5, 138.0, 411.0, 138.0, 411.0, 201.0, 448.5, 201.0 ]
				}

			}
 ]
	}

}
