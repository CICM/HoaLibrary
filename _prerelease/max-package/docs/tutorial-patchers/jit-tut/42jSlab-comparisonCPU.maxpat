{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 980.0, 110.0, 332.0, 540.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 980.0, 110.0, 332.0, 540.0 ],
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
					"text" : "CPU Performance",
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 23.0, 20.0, 105.0, 20.0 ],
					"underline" : 0,
					"id" : "obj-1",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"ignoreclick" : 1,
					"numoutlets" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.fpsgui",
					"bgcolor" : [ 0.73, 0.73, 0.73, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 51.0, 399.0, 60.0, 35.0 ],
					"id" : "obj-2",
					"fontname" : "Arial",
					"textcolor" : [ 0.12, 0.12, 0.12, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"bgcolor2" : [ 0.92, 0.92, 0.92, 1.0 ],
					"fontface" : 0,
					"fontsize" : 11.595187,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"outlettype" : [ "", "" ],
					"mode" : 0,
					"htextcolor" : [ 0.01, 0.01, 0.01, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op mult",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 359.0, 93.0, 20.0 ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op add",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 331.0, 89.0, 20.0 ],
					"id" : "obj-4",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op add",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 270.0, 89.0, 20.0 ],
					"id" : "obj-5",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op mult",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 300.0, 93.0, 20.0 ],
					"id" : "obj-6",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op mult",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 243.0, 93.0, 20.0 ],
					"id" : "obj-7",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op add",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 215.0, 89.0, 20.0 ],
					"id" : "obj-8",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op add",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 154.0, 89.0, 20.0 ],
					"id" : "obj-9",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.op @op mult",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 184.0, 93.0, 20.0 ],
					"id" : "obj-10",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"checkedcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"patching_rect" : [ 36.0, 51.0, 15.0, 15.0 ],
					"id" : "obj-11",
					"presentation" : 0,
					"numinlets" : 1,
					"ignoreclick" : 0,
					"numoutlets" : 1,
					"hidden" : 0,
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"outlettype" : [ "int" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "qmetro 2",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 70.0, 61.0, 20.0 ],
					"id" : "obj-12",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 2,
					"ignoreclick" : 0,
					"numoutlets" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "bang" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.noise 4 char 640 480",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 102.0, 151.0, 20.0 ],
					"id" : "obj-13",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.window cpu @size 640 480",
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"patching_rect" : [ 36.0, 441.0, 182.0, 20.0 ],
					"id" : "obj-14",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"ignoreclick" : 0,
					"numoutlets" : 2,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"outlettype" : [ "bang", "" ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "4 additions and 4 multiplications at 640x480 on the CPU",
					"linecount" : 3,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 135.0, 168.0, 172.0, 46.0 ],
					"underline" : 0,
					"id" : "obj-15",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation" : 0,
					"numinlets" : 1,
					"ignoreclick" : 1,
					"numoutlets" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bgcolor" : [ 0.764706, 0.819608, 0.854902, 1.0 ],
					"background" : 0,
					"rounded" : 0,
					"patching_rect" : [ 21.0, 40.0, 277.0, 442.0 ],
					"id" : "obj-16",
					"presentation" : 0,
					"numinlets" : 1,
					"ignoreclick" : 1,
					"numoutlets" : 0,
					"shadow" : 0,
					"hidden" : 0,
					"grad1" : [ 0.75, 0.79, 0.93, 1.0 ],
					"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"angle" : 0.0,
					"mode" : 0,
					"border" : 0,
					"grad2" : [ 0.66, 0.66, 0.72, 1.0 ],
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-3", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-6", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-7", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-10", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-4", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-5", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-8", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-9", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-3", 0 ],
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
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-5", 0 ],
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
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-10", 0 ],
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
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 45.5, 96.0, 45.5, 96.0 ]
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
 ]
	}

}
