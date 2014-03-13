{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 311.0, 66.0, 699.0, 469.0 ],
		"bglocked" : 0,
		"defrect" : [ 311.0, 66.0, 699.0, 469.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 10.0, 10.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambiproc~ 0",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 23.0, 150.0, 86.0, 20.0 ],
					"id" : "obj-1",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambiproc~ 1",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 23.0, 189.0, 86.0, 20.0 ],
					"id" : "obj-2",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambiproc~ 2",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 23.0, 230.0, 86.0, 20.0 ],
					"id" : "obj-3",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambiproc~ 3",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 23.0, 272.0, 86.0, 20.0 ],
					"id" : "obj-4",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambiproc~ 4",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 23.0, 313.0, 86.0, 20.0 ],
					"id" : "obj-5",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambiproc~ 5",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 23.0, 352.0, 86.0, 20.0 ],
					"id" : "obj-6",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Based on the b_proc VST plugin by Dave Malham. Ported to MAX/MSP by Matthew Paradis",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 22.0, 85.0, 372.0, 34.0 ],
					"id" : "obj-7"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Rotate-Tilt-Tumble",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 148.0, 127.0, 20.0 ],
					"id" : "obj-10"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Rotate-Tumble-Tilt",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 186.0, 127.0, 20.0 ],
					"id" : "obj-11"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Tilt-Rotate-Tumble",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 230.0, 127.0, 20.0 ],
					"id" : "obj-12"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Tilt-Tumble-Rotate",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 268.0, 127.0, 20.0 ],
					"id" : "obj-13"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Tumble-Rotate-Tilt",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 310.0, 127.0, 20.0 ],
					"id" : "obj-14"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Parameters",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 240.0, 147.0, 80.0, 20.0 ],
					"id" : "obj-16"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "rotate = rotate, \ntilt = tilt, \ntumble = tumble.",
					"linecount" : 3,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 240.0, 170.0, 267.0, 48.0 ],
					"id" : "obj-17"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "For more informataion see: http://www.york.ac.uk/inst/mustech/3d_audio/vst/bproc_help.html",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 21.0, 396.0, 353.0, 34.0 ],
					"id" : "obj-18"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Tumble-Tilt-Rotate",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 350.0, 127.0, 20.0 ],
					"id" : "obj-20"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "All parameters are scaled between 0.0-1.0",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 239.0, 228.0, 263.0, 20.0 ],
					"id" : "obj-21"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_title",
					"text" : "ambiproc~",
					"fontface" : 3,
					"fontsize" : 20.871338,
					"numinlets" : 1,
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"frgb" : [ 1.0, 1.0, 1.0, 1.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 15.0, 13.0, 566.0, 30.0 ],
					"id" : "obj-110"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_digest",
					"text" : "Ambisonic B-format processor",
					"fontsize" : 12.754705,
					"numinlets" : 1,
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"frgb" : [ 1.0, 1.0, 1.0, 1.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 15.0, 45.0, 566.0, 21.0 ],
					"id" : "obj-111"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"varname" : "autohelp_top_panel",
					"background" : 1,
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.756863, 0.564706, 0.105882, 1.0 ],
					"mode" : 1,
					"grad1" : [ 0.117647, 0.203922, 0.435294, 1.0 ],
					"patching_rect" : [ 10.0, 10.0, 570.0, 60.0 ],
					"id" : "obj-114",
					"grad2" : [ 0.352941, 0.439216, 0.713726, 1.0 ]
				}

			}
 ],
		"lines" : [  ]
	}

}
