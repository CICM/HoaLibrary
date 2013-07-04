{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 0,
			"revision" : 4
		}
,
		"rect" : [ 431.0, 89.0, 534.0, 198.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 10.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 1,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"boxes" : [ 			{
				"box" : 				{
					"background" : 0,
					"bgcolor" : [ 0.73, 0.73, 0.73, 1.0 ],
					"bgcolor2" : [ 0.92, 0.92, 0.92, 1.0 ],
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"htextcolor" : [ 0.01, 0.01, 0.01, 1.0 ],
					"id" : "obj-1",
					"ignoreclick" : 0,
					"maxclass" : "jit.fpsgui",
					"mode" : 1,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 157.0, 110.0, 60.0, 35.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"textcolor" : [ 0.12, 0.12, 0.12, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 0,
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"gradient" : 0,
					"hidden" : 0,
					"id" : "obj-2",
					"ignoreclick" : 0,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 26.0, 58.0, 63.0, 18.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"text" : "size $1 $2",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 0,
					"border" : 0.0,
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"colormode" : "argb",
					"dstrect" : [ 0, 0, 320, 240 ],
					"hidden" : 0,
					"id" : "obj-3",
					"idlemouse" : 0,
					"ignoreclick" : 0,
					"interp" : 0,
					"maxclass" : "jit.pwindow",
					"numinlets" : 1,
					"numoutlets" : 2,
					"onscreen" : 1,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 17.0, 87.0, 60.0, 40.0 ],
					"pickray" : 0,
					"planemap" : [ 0, 1, 2, 3 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"srcrect" : [ 0, 0, 320, 240 ],
					"usedstrect" : 0,
					"usesrcrect" : 0
				}

			}
, 			{
				"box" : 				{
					"background" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"hidden" : 0,
					"id" : "obj-4",
					"ignoreclick" : 0,
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 201.0, 60.0, 20.0, 20.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"id" : "obj-5",
					"ignoreclick" : 0,
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 201.0, 39.0, 94.0, 20.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"text" : "route connected",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"id" : "obj-6",
					"ignoreclick" : 0,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 324.0, 37.0, 58.0, 20.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"text" : "loadbang",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"align" : 0,
					"arrow" : 1,
					"arrowbgcolor" : [ 0.86, 0.86, 0.86, 1.0 ],
					"arrowcolor" : [ 0.22, 0.22, 0.22, 1.0 ],
					"arrowframe" : 1,
					"arrowlink" : 1,
					"autopopulate" : 0,
					"background" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"bgcolor2" : [ 1.0, 1.0, 1.0, 1.0 ],
					"depth" : 0,
					"discolor" : [ 0.43, 0.43, 0.43, 1.0 ],
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"framecolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"hidden" : 0,
					"hltcolor" : [ 0.92, 0.92, 0.92, 1.0 ],
					"id" : "obj-7",
					"ignoreclick" : 0,
					"items" : [ "192.168.0.101", ",", "fe80:0:0:0:20d:93ff:feb1:a2f2" ],
					"labelclick" : 0,
					"maxclass" : "umenu",
					"menumode" : 0,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 324.0, 111.0, 100.0, 20.0 ],
					"pattrmode" : 0,
					"prefix" : "",
					"prefix_mode" : 0,
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"rounded" : 8,
					"showdotfiles" : 0,
					"textcolor" : [ 0.15, 0.15, 0.15, 1.0 ],
					"textcolor2" : [ 0.15, 0.15, 0.15, 1.0 ],
					"togcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
					"truncate" : 1,
					"underline" : 0
				}

			}
, 			{
				"box" : 				{
					"align" : 0,
					"arrow" : 1,
					"arrowbgcolor" : [ 0.86, 0.86, 0.86, 1.0 ],
					"arrowcolor" : [ 0.22, 0.22, 0.22, 1.0 ],
					"arrowframe" : 1,
					"arrowlink" : 1,
					"autopopulate" : 0,
					"background" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"bgcolor2" : [ 1.0, 1.0, 1.0, 1.0 ],
					"depth" : 0,
					"discolor" : [ 0.43, 0.43, 0.43, 1.0 ],
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"framecolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"hidden" : 0,
					"hltcolor" : [ 0.92, 0.92, 0.92, 1.0 ],
					"id" : "obj-8",
					"ignoreclick" : 0,
					"items" : [ "utun0", ",", "en1", ",", "lo0" ],
					"labelclick" : 0,
					"maxclass" : "umenu",
					"menumode" : 0,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 397.0, 88.0, 100.0, 20.0 ],
					"pattrmode" : 0,
					"prefix" : "",
					"prefix_mode" : 0,
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"rounded" : 8,
					"showdotfiles" : 0,
					"textcolor" : [ 0.15, 0.15, 0.15, 1.0 ],
					"textcolor2" : [ 0.15, 0.15, 0.15, 1.0 ],
					"togcolor" : [ 0.55, 0.55, 0.55, 1.0 ],
					"truncate" : 1,
					"underline" : 0
				}

			}
, 			{
				"box" : 				{
					"background" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"id" : "obj-9",
					"ignoreclick" : 0,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 324.0, 62.0, 75.0, 20.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"text" : "mxj net.local",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"color" : [ 1.0, 0.890196, 0.090196, 1.0 ],
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 0,
					"id" : "obj-10",
					"ignoreclick" : 0,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "jit_matrix", "", "" ],
					"patching_rect" : [ 17.0, 17.0, 127.0, 20.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"text" : "jit.net.recv @port 7476",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"angle" : 0.0,
					"arrow_orientation" : 0,
					"background" : 1,
					"bgcolor" : [ 0.0, 0.713726, 0.294118, 1.0 ],
					"border" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"drag_window" : 0,
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"hidden" : 0,
					"horizontal_direction" : 0,
					"id" : "obj-11",
					"ignoreclick" : 1,
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 321.0, 33.0, 187.0, 98.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"rounded" : 0,
					"shadow" : 0,
					"shape" : 0,
					"vertical_direction" : 0
				}

			}
, 			{
				"box" : 				{
					"angle" : 0.0,
					"arrow_orientation" : 0,
					"background" : 1,
					"bgcolor" : [ 0.835294, 0.741176, 0.003922, 1.0 ],
					"border" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"drag_window" : 0,
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"hidden" : 0,
					"horizontal_direction" : 0,
					"id" : "obj-12",
					"ignoreclick" : 1,
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 10.0, 9.0, 297.0, 139.0 ],
					"presentation" : 0,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"rounded" : 0,
					"shadow" : 0,
					"shape" : 0,
					"vertical_direction" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 26.5, 80.0, 166.5, 80.0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 80.5, 46.0, 35.5, 46.0 ],
					"source" : [ "obj-10", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 35.5, 80.0, 26.5, 80.0 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 447.0, 108.0, 501.0, 108.0, 501.0, 58.0, 333.5, 58.0 ],
					"source" : [ "obj-8", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-9", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-8", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-9", 1 ]
				}

			}
 ],
		"dependency_cache" : [  ]
	}

}
