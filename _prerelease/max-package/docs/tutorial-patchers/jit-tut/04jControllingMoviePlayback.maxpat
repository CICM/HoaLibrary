{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 7.0, 44.0, 790.0, 580.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 7.0, 44.0, 790.0, 580.0 ],
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
					"text" : "gettime",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 8.0, 135.0, 49.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-1",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sel 1",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "bang", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 290.0, 289.0, 35.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-2",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Gets the timing, rate, and volume information of the movie clip when it loads",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 262.0, 201.0, 400.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-3",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Stop and start the movie at its current time position",
					"linecount" : 3,
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 247.0, 38.0, 110.0, 46.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-4",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Reset the looppoints",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 479.0, 65.0, 116.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-5",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Change the movie's playback rate and volume",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 369.0, 35.0, 248.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-6",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Set the looppoints for the movie",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 581.0, 410.0, 174.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-7",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pack",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 572.0, 471.0, 35.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-8",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "looppoints, getlooppoints",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 478.0, 91.0, 139.0, 18.0 ],
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
					"maxclass" : "message",
					"text" : "looppoints $1 $2",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 572.0, 495.0, 96.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-10",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "size $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 502.0, 360.0, 47.0, 18.0 ],
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
					"maxclass" : "rslider",
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"listmode" : 0,
					"background" : 0,
					"outlettype" : [ "", "int" ],
					"size" : 2836,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"mult" : 1,
					"min" : 0,
					"hidden" : 0,
					"fgcolor" : [ 0.65, 0.65, 0.65, 1.0 ],
					"patching_rect" : [ 572.0, 432.0, 155.0, 28.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-12",
					"numoutlets" : 2,
					"orientation" : 0,
					"drawline" : 1
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
					"patching_rect" : [ 367.0, 65.0, 48.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-13",
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
					"patching_rect" : [ 418.0, 65.0, 52.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-14",
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
					"text" : "vol $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 418.0, 91.0, 41.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-15",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rate $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 367.0, 91.0, 47.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-16",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Change when the movie is stopped to 'scrub' the movie playback",
					"linecount" : 2,
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 361.0, 410.0, 193.0, 33.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-17",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Movie timescale and fps.",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 502.0, 269.0, 138.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-18",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "set $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 300.0, 385.0, 42.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-19",
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
					"patching_rect" : [ 444.0, 268.0, 54.0, 20.0 ],
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
					"maxclass" : "number",
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
					"patching_rect" : [ 387.0, 268.0, 54.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-21",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Current time",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 224.0, 325.0, 74.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-22",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Current frame",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 219.0, 408.0, 82.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-23",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
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
					"patching_rect" : [ 300.0, 408.0, 55.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-24",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "int" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 300.0, 360.0, 32.5, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-25",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
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
					"patching_rect" : [ 300.0, 324.0, 52.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-26",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Total frames",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 343.0, 385.0, 75.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-27",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Total time",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 351.0, 325.0, 61.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-28",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Timescale/Fps=time values/frame",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 511.0, 302.0, 184.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-29",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
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
					"patching_rect" : [ 422.0, 385.0, 61.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-30",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "int" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 422.0, 360.0, 32.5, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-31",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
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
					"patching_rect" : [ 422.0, 325.0, 52.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-32",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
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
					"patching_rect" : [ 477.0, 325.0, 52.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-33",
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/ 1.",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "float" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 477.0, 302.0, 32.5, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-34",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack s 0",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "", "int" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 242.0, 266.0, 67.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-35",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route read time duration timescale fps rate vol looppoints",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "", "", "", "", "", "", "", "", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 242.0, 240.0, 474.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-36",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 9,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "getfps, gettimescale, getduration, getrate, getvol",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 242.0, 178.0, 258.0, 18.0 ],
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
					"maxclass" : "message",
					"text" : "frame $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 300.0, 430.0, 56.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-38",
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
					"patching_rect" : [ 312.0, 91.0, 33.0, 18.0 ],
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
					"patching_rect" : [ 279.0, 91.0, 32.5, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-40",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
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
					"onscreen" : 1,
					"interp" : 0,
					"idlemouse" : 0,
					"usedstrect" : 0,
					"hidden" : 0,
					"patching_rect" : [ 54.0, 235.0, 160.0, 120.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-41",
					"border" : 0.0,
					"planemap" : [ 0, 1, 2, 3 ],
					"doublebuffer" : 1,
					"shared" : 0,
					"srcrect" : [ 0, 0, 320, 240 ],
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Open",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 24.0, 29.0, 39.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-42",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Play",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 76.0, 86.0, 33.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-43",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "time 0",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 185.0, 61.0, 42.0, 18.0 ],
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
					"maxclass" : "message",
					"text" : "1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 152.0, 61.0, 32.5, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-45",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
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
					"patching_rect" : [ 152.0, 29.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-46",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "metro 40",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "bang" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 55.0, 110.0, 56.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-47",
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
					"patching_rect" : [ 55.0, 85.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-48",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read crashtest.mov",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 22.0, 53.0, 109.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-49",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.qt.movie 320 240",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "jit_matrix", "" ],
					"color" : [ 1.0, 0.890196, 0.090196, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 55.0, 209.0, 111.0, 20.0 ],
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
					"text" : "Restart",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 167.0, 29.0, 48.0, 20.0 ],
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
					"maxclass" : "panel",
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 1,
					"shadow" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 0.498039, 1.0, 1.0, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 49.0, 202.0, 174.0, 166.0 ],
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
					"bgcolor" : [ 1.0, 0.498039, 1.0, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 18.0, 28.0, 124.0, 49.0 ],
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
					"bgcolor" : [ 0.498039, 0.498039, 1.0, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 245.0, 35.0, 400.0, 80.0 ],
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
					"bgcolor" : [ 0.498039, 1.0, 0.498039, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 217.0, 405.0, 551.0, 61.0 ],
					"mode" : 0,
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-55",
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
					"patching_rect" : [ 2.0, 77.0, 128.0, 74.0 ],
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
					"source" : [ "obj-47", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 161.5, 81.0, 64.5, 81.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-48", 0 ],
					"destination" : [ "obj-47", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-47", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 251.5, 198.0, 64.5, 198.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-44", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 194.5, 158.0, 64.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 288.5, 158.0, 64.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 321.5, 158.0, 64.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-38", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 309.5, 457.0, 22.0, 457.0, 22.0, 195.0, 64.5, 195.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 427.5, 158.0, 64.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 376.5, 158.0, 64.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 487.5, 158.0, 64.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 581.5, 522.0, 771.0, 522.0, 771.0, 158.0, 64.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-49", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 31.5, 124.0, 5.0, 124.0, 5.0, 158.0, 64.5, 158.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 161.5, 57.0, 194.5, 57.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 299.5, 311.0, 234.0, 311.0, 234.0, 174.0, 251.5, 174.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 1 ],
					"destination" : [ "obj-36", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 156.5, 233.0, 251.5, 233.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 1 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 308.375, 262.0, 343.0, 262.0, 343.0, 318.0, 309.5, 318.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 1 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 0 ],
					"destination" : [ "obj-25", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 486.5, 354.0, 323.0, 354.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 5 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 535.875, 264.0, 726.0, 264.0, 726.0, 56.0, 376.5, 56.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 3 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 422.125, 261.0, 396.5, 261.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 2 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 365.25, 279.0, 352.0, 279.0, 352.0, 312.0, 431.5, 312.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-31", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 0 ],
					"destination" : [ "obj-31", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 486.5, 354.0, 445.0, 354.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 6 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 592.75, 264.0, 726.0, 264.0, 726.0, 56.0, 427.5, 56.0 ]
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
					"source" : [ "obj-36", 4 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 479.0, 261.0, 453.5, 261.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 396.5, 292.0, 486.5, 292.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-34", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 453.5, 286.0, 500.0, 286.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 431.5, 347.0, 511.5, 347.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 511.5, 391.0, 581.5, 391.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 7 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 649.625, 293.0, 581.5, 293.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-8", 0 ],
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
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 1 ],
					"destination" : [ "obj-8", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 717.5, 464.0, 597.5, 464.0 ]
				}

			}
 ]
	}

}
