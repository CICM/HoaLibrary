{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 46.0, 51.0, 575.0, 518.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 46.0, 51.0, 575.0, 518.0 ],
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
					"text" : "jit.unpack",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "jit_matrix", "jit_matrix", "jit_matrix", "jit_matrix", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 64.0, 107.0, 73.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-1",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 5,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "voc -1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 226.0, 573.0, 42.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-2",
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
					"patching_rect" : [ 64.0, 523.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-3",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "metro 2",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "bang" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 64.0, 543.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-4",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"depth" : 0,
					"fontsize" : 11.595187,
					"arrowbgcolor" : [ 0.86, 0.86, 0.86, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int", "", "" ],
					"framecolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"align" : 0,
					"arrowframe" : 1,
					"arrow" : 1,
					"autopopulate" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"discolor" : [ 0.43, 0.43, 0.43, 1.0 ],
					"items" : [ "Minimum", "Quality", ",", "Low", "Quality", ",", "Normal", "Quality", ",", "High", "Quality", ",", "Maximum", "Quality", ",", "Lossless", "Quality" ],
					"ignoreclick" : 0,
					"menumode" : 0,
					"togcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"arrowlink" : 1,
					"labelclick" : 0,
					"hidden" : 0,
					"fontname" : "Arial",
					"types" : [  ],
					"hltcolor" : [ 0.92, 0.92, 0.92, 1.0 ],
					"patching_rect" : [ 303.0, 266.0, 108.0, 20.0 ],
					"prefix_mode" : 0,
					"textcolor2" : [ 0.15, 0.15, 0.15, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"prefix" : "",
					"id" : "obj-5",
					"showdotfiles" : 0,
					"rounded" : 8,
					"bgcolor2" : [ 1.0, 1.0, 1.0, 1.0 ],
					"underline" : 0,
					"textcolor" : [ 0.15, 0.15, 0.15, 1.0 ],
					"numoutlets" : 3,
					"fontface" : 0,
					"pattrmode" : 0,
					"arrowcolor" : [ 0.22, 0.22, 0.22, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "codecquality $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 303.0, 286.0, 91.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-6",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "getvocmodes",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 148.0, 573.0, 79.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-7",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "getvoclist",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 76.0, 573.0, 59.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-8",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "vocmode $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 379.0, 731.0, 74.0, 18.0 ],
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
					"patching_rect" : [ 475.0, 659.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-10",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 475.0, 682.0, 36.0, 18.0 ],
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
					"maxclass" : "newobj",
					"text" : "iter",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 379.0, 659.0, 27.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-12",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"depth" : 0,
					"fontsize" : 11.595187,
					"arrowbgcolor" : [ 0.86, 0.86, 0.86, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int", "", "" ],
					"framecolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"align" : 0,
					"arrowframe" : 1,
					"arrow" : 1,
					"autopopulate" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"discolor" : [ 0.43, 0.43, 0.43, 1.0 ],
					"items" : [  ],
					"ignoreclick" : 0,
					"menumode" : 0,
					"togcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"arrowlink" : 1,
					"labelclick" : 0,
					"hidden" : 0,
					"fontname" : "Arial",
					"types" : [  ],
					"hltcolor" : [ 0.92, 0.92, 0.92, 1.0 ],
					"patching_rect" : [ 379.0, 708.0, 134.0, 20.0 ],
					"prefix_mode" : 0,
					"textcolor2" : [ 0.15, 0.15, 0.15, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"prefix" : "",
					"id" : "obj-13",
					"showdotfiles" : 0,
					"rounded" : 8,
					"bgcolor2" : [ 1.0, 1.0, 1.0, 1.0 ],
					"underline" : 0,
					"textcolor" : [ 0.15, 0.15, 0.15, 1.0 ],
					"numoutlets" : 3,
					"fontface" : 0,
					"pattrmode" : 0,
					"arrowcolor" : [ 0.22, 0.22, 0.22, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend append",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 379.0, 682.0, 95.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-14",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "voc $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 238.0, 731.0, 45.0, 18.0 ],
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
					"patching_rect" : [ 334.0, 659.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-16",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 334.0, 682.0, 36.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-17",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "iter",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 238.0, 659.0, 27.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-18",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"depth" : 0,
					"fontsize" : 11.595187,
					"arrowbgcolor" : [ 0.86, 0.86, 0.86, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int", "", "" ],
					"framecolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"align" : 0,
					"arrowframe" : 1,
					"arrow" : 1,
					"autopopulate" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"discolor" : [ 0.43, 0.43, 0.43, 1.0 ],
					"items" : [  ],
					"ignoreclick" : 0,
					"menumode" : 0,
					"togcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"arrowlink" : 1,
					"labelclick" : 0,
					"hidden" : 0,
					"fontname" : "Arial",
					"types" : [  ],
					"hltcolor" : [ 0.92, 0.92, 0.92, 1.0 ],
					"patching_rect" : [ 238.0, 708.0, 134.0, 20.0 ],
					"prefix_mode" : 0,
					"textcolor2" : [ 0.15, 0.15, 0.15, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"prefix" : "",
					"id" : "obj-19",
					"showdotfiles" : 0,
					"rounded" : 8,
					"bgcolor2" : [ 1.0, 1.0, 1.0, 1.0 ],
					"underline" : 0,
					"textcolor" : [ 0.15, 0.15, 0.15, 1.0 ],
					"numoutlets" : 3,
					"fontface" : 0,
					"pattrmode" : 0,
					"arrowcolor" : [ 0.22, 0.22, 0.22, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend append",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 238.0, 682.0, 95.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-20",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route voclist vocmodes",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "", "", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 238.0, 632.0, 128.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-21",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 3,
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
					"patching_rect" : [ 120.0, 543.0, 34.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-22",
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
					"patching_rect" : [ 64.0, 600.0, 111.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-23",
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
					"patching_rect" : [ 63.0, 631.0, 160.0, 120.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-24",
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
					"maxclass" : "message",
					"text" : "getvocmodes",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 226.0, 286.0, 79.0, 18.0 ],
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
					"maxclass" : "message",
					"text" : "getvoclist",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 154.0, 286.0, 59.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-26",
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "vocmode $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 379.0, 442.0, 74.0, 18.0 ],
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
					"patching_rect" : [ 475.0, 370.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-28",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 475.0, 393.0, 36.0, 18.0 ],
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
					"maxclass" : "newobj",
					"text" : "iter",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 379.0, 370.0, 27.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-30",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"depth" : 0,
					"fontsize" : 11.595187,
					"arrowbgcolor" : [ 0.86, 0.86, 0.86, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int", "", "" ],
					"framecolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"align" : 0,
					"arrowframe" : 1,
					"arrow" : 1,
					"autopopulate" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"discolor" : [ 0.43, 0.43, 0.43, 1.0 ],
					"items" : [  ],
					"ignoreclick" : 0,
					"menumode" : 0,
					"togcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"arrowlink" : 1,
					"labelclick" : 0,
					"hidden" : 0,
					"fontname" : "Arial",
					"types" : [  ],
					"hltcolor" : [ 0.92, 0.92, 0.92, 1.0 ],
					"patching_rect" : [ 379.0, 419.0, 134.0, 20.0 ],
					"prefix_mode" : 0,
					"textcolor2" : [ 0.15, 0.15, 0.15, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"prefix" : "",
					"id" : "obj-31",
					"showdotfiles" : 0,
					"rounded" : 8,
					"bgcolor2" : [ 1.0, 1.0, 1.0, 1.0 ],
					"underline" : 0,
					"textcolor" : [ 0.15, 0.15, 0.15, 1.0 ],
					"numoutlets" : 3,
					"fontface" : 0,
					"pattrmode" : 0,
					"arrowcolor" : [ 0.22, 0.22, 0.22, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend append",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 379.0, 393.0, 95.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-32",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "voc $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 238.0, 442.0, 45.0, 18.0 ],
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
					"patching_rect" : [ 334.0, 370.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-34",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 334.0, 393.0, 36.0, 18.0 ],
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
					"maxclass" : "newobj",
					"text" : "iter",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 238.0, 370.0, 27.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-36",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"depth" : 0,
					"fontsize" : 11.595187,
					"arrowbgcolor" : [ 0.86, 0.86, 0.86, 1.0 ],
					"background" : 0,
					"outlettype" : [ "int", "", "" ],
					"framecolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"align" : 0,
					"arrowframe" : 1,
					"arrow" : 1,
					"autopopulate" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"discolor" : [ 0.43, 0.43, 0.43, 1.0 ],
					"items" : [  ],
					"ignoreclick" : 0,
					"menumode" : 0,
					"togcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"arrowlink" : 1,
					"labelclick" : 0,
					"hidden" : 0,
					"fontname" : "Arial",
					"types" : [  ],
					"hltcolor" : [ 0.92, 0.92, 0.92, 1.0 ],
					"patching_rect" : [ 238.0, 419.0, 134.0, 20.0 ],
					"prefix_mode" : 0,
					"textcolor2" : [ 0.15, 0.15, 0.15, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"prefix" : "",
					"id" : "obj-37",
					"showdotfiles" : 0,
					"rounded" : 8,
					"bgcolor2" : [ 1.0, 1.0, 1.0, 1.0 ],
					"underline" : 0,
					"textcolor" : [ 0.15, 0.15, 0.15, 1.0 ],
					"numoutlets" : 3,
					"fontface" : 0,
					"pattrmode" : 0,
					"arrowcolor" : [ 0.22, 0.22, 0.22, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend append",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 238.0, 393.0, 95.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-38",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route voclist vocmodes",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "", "", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 238.0, 343.0, 128.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-39",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 3,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "close",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 113.0, 286.0, 38.0, 18.0 ],
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
					"maxclass" : "message",
					"text" : "open",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 78.0, 286.0, 36.0, 18.0 ],
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
					"maxclass" : "newobj",
					"text" : "jit.qt.videoout",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "jit_matrix", "" ],
					"color" : [ 1.0, 0.890196, 0.090196, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 64.0, 311.0, 79.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-42",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "$1 1000",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 316.0, 151.0, 52.0, 18.0 ],
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
					"maxclass" : "newobj",
					"text" : "line 30.",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "", "", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 316.0, 171.0, 48.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 3,
					"id" : "obj-44",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 3,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "theta $1",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 316.0, 193.0, 52.0, 18.0 ],
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
					"maxclass" : "newobj",
					"text" : "* 0.01",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "float" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 316.0, 129.0, 41.0, 20.0 ],
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
					"maxclass" : "newobj",
					"text" : "random 628",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "int" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 316.0, 107.0, 72.0, 20.0 ],
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
					"maxclass" : "newobj",
					"text" : "speedlim 1000",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 316.0, 85.0, 86.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-48",
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
					"patching_rect" : [ 64.0, 26.0, 20.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-49",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "metro 2",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "bang" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 64.0, 46.0, 50.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-50",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 1,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op - @in2_name grendel",
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "jit_matrix", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 64.0, 149.0, 178.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-51",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read dozer.mov",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"background" : 0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 118.0, 47.0, 91.0, 18.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"id" : "obj-52",
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
					"onscreen" : 0,
					"interp" : 4,
					"idlemouse" : 0,
					"usedstrect" : 0,
					"hidden" : 0,
					"patching_rect" : [ 63.0, 342.0, 160.0, 120.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-53",
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
					"text" : "jit.rota @anchor_x 160 @anchor_y 120 @zoom_x 1.01 @zoom_y 1.01 @theta 0.03 @boundmode 4 @out_name grendel",
					"linecount" : 2,
					"fontsize" : 11.595187,
					"background" : 0,
					"outlettype" : [ "jit_matrix", "" ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 86.0, 226.0, 445.0, 33.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-54",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
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
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 64.0, 73.0, 111.0, 20.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-55",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "1.",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 29.0, 22.0, 20.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-56",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontface" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "2.",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 31.0, 518.0, 20.0, 20.0 ],
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
					"maxclass" : "comment",
					"text" : "scroll down for example 2...",
					"fontsize" : 11.595187,
					"background" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"ignoreclick" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"hidden" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 44.0, 491.0, 152.0, 20.0 ],
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-58",
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
					"bgcolor" : [ 1.0, 1.0, 0.752941, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 44.0, 518.0, 490.0, 257.0 ],
					"mode" : 0,
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-59",
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
					"bgcolor" : [ 0.752941, 0.752941, 1.0, 1.0 ],
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"hidden" : 0,
					"patching_rect" : [ 44.0, 22.0, 490.0, 463.0 ],
					"mode" : 0,
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"id" : "obj-60",
					"border" : 0,
					"rounded" : 0,
					"angle" : 0.0,
					"numoutlets" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-49", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-55", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 73.5, 69.0, 73.5, 69.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-52", 0 ],
					"destination" : [ "obj-55", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 127.5, 68.0, 73.5, 68.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-55", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 1 ],
					"destination" : [ "obj-51", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 87.0, 137.0, 73.5, 137.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-51", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 235.5, 306.0, 73.5, 306.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 163.5, 306.0, 73.5, 306.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 388.5, 479.0, 48.0, 479.0, 48.0, 306.0, 73.5, 306.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 247.5, 476.0, 52.0, 476.0, 52.0, 306.0, 73.5, 306.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 122.5, 306.0, 73.5, 306.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 87.5, 306.0, 73.5, 306.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 312.5, 306.0, 73.5, 306.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-42", 0 ],
					"destination" : [ "obj-53", 0 ],
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
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 235.5, 595.0, 73.5, 595.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 157.5, 595.0, 73.5, 595.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 85.5, 595.0, 73.5, 595.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 388.5, 768.0, 48.0, 768.0, 48.0, 595.0, 73.5, 595.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 247.5, 765.0, 52.0, 765.0, 52.0, 595.0, 73.5, 595.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 129.5, 564.0, 73.5, 564.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-54", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 325.5, 217.0, 95.5, 217.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-51", 0 ],
					"destination" : [ "obj-54", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 73.5, 178.0, 95.5, 178.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-42", 1 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 133.5, 336.0, 247.5, 336.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-36", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 343.5, 414.0, 247.5, 414.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-38", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 1 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 165.5, 625.0, 247.5, 625.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 343.5, 703.0, 247.5, 703.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 73.5, 68.0, 325.5, 68.0 ]
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
					"destination" : [ "obj-46", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-43", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-44", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 247.5, 366.0, 343.5, 366.0 ]
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
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 247.5, 655.0, 343.5, 655.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 1 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 302.0, 363.0, 388.5, 363.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
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
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-31", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 484.5, 414.0, 388.5, 414.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 1 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 302.0, 652.0, 388.5, 652.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 484.5, 703.0, 388.5, 703.0 ]
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
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 1 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 302.0, 366.0, 484.5, 366.0 ]
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
					"source" : [ "obj-21", 1 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 302.0, 655.0, 484.5, 655.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
 ]
	}

}
