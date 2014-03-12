{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 311.0, 66.0, 862.0, 595.0 ],
		"bglocked" : 0,
		"defrect" : [ 311.0, 66.0, 862.0, 595.0 ],
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
					"text" : "ambidec~ 1",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 10.0, 179.0, 79.0, 20.0 ],
					"id" : "obj-1",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambidec~ 0",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 8,
					"fontname" : "Arial",
					"patching_rect" : [ 10.0, 146.0, 125.0, 20.0 ],
					"id" : "obj-2",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambidec~ 2",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 10.0, 212.0, 79.0, 20.0 ],
					"id" : "obj-3",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambidec~ 3",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 6,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 248.0, 94.0, 20.0 ],
					"id" : "obj-4",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambidec~ 4",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 8,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 281.0, 125.0, 20.0 ],
					"id" : "obj-5",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambidec~ 5",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 8,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 314.0, 125.0, 20.0 ],
					"id" : "obj-6",
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambidec~ 6",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 347.0, 79.0, 20.0 ],
					"id" : "obj-7",
					"outlettype" : [ "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ambidec~ 7",
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 382.0, 79.0, 20.0 ],
					"id" : "obj-8",
					"outlettype" : [ "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Based on the b_dec VST plugin by Dave Malham. \nPorted to MAX/MSP by Matthew Paradis",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 74.0, 341.0, 34.0 ],
					"id" : "obj-9"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "For more information see http://www.dmalham.freeserve.co.uk/vst_ambisonics.html",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 10.0, 420.0, 318.0, 34.0 ],
					"id" : "obj-10"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Cube with height",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 127.0, 108.0, 20.0 ],
					"id" : "obj-11"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Square - horizontal",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 162.0, 126.0, 20.0 ],
					"id" : "obj-12"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Rectangle",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 195.0, 66.0, 20.0 ],
					"id" : "obj-13"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Hexagon with speakers at stereo locations",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 8.0, 230.0, 252.0, 20.0 ],
					"id" : "obj-14"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Octagon with speakers at stereo locations",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 7.0, 265.0, 248.0, 20.0 ],
					"id" : "obj-15"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Octagon with speakers at compass points",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 7.0, 297.0, 245.0, 20.0 ],
					"id" : "obj-16"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Decode to stereo",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 9.0, 331.0, 103.0, 20.0 ],
					"id" : "obj-17"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Decode to mono",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 8.0, 365.0, 97.0, 20.0 ],
					"id" : "obj-18"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Input 1 = W, Input 2 = X, Input 3 = Y, Input 4 = Z.",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 130.0, 308.0, 20.0 ],
					"id" : "obj-19"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Outputs",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 160.0, 55.0, 20.0 ],
					"id" : "obj-20"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ambidec~ 0 1 = LFD, 2 = RFD, 3 = RBD, 4= LBD, 5 = LFU, 6 = RFU, 7 = RBU, 8 = LBU.",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 190.0, 267.0, 34.0 ],
					"id" : "obj-21"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ambidec~ 1 1 = LF, 2 = RF, 3 = RB, 4 = LB.",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 230.0, 270.0, 20.0 ],
					"id" : "obj-22"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ambidec~ 2 1 = LF, 2 = RF, 3 = RB, 4 = LB.",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 260.0, 270.0, 20.0 ],
					"id" : "obj-23"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ambidec~ 3 1 = LF, 2 = L, 3 = LB, 4 = RB, 5 = R, 6 = RF.",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 290.0, 349.0, 20.0 ],
					"id" : "obj-24"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ambidec~ 4, 1 = LF1, 2 = LF2, 3 = LB1, 4 = LB2, 5 = RB1, 6 = RB2, 7 = RF1, 8 = RF2.",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 320.0, 429.0, 20.0 ],
					"id" : "obj-25"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ambidec~ 5 1 = F, 2 = LF, 3 = L, 4 = LB, 5 = B, 6 = RB, 7 = R, 8 = RF.",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 350.0, 409.0, 34.0 ],
					"id" : "obj-26"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ambidec~ 6 1 = LF, 2 = RF.",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 390.0, 171.0, 20.0 ],
					"id" : "obj-27"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ambidec~ 7 1 = F, 2 = F.",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 420.0, 155.0, 20.0 ],
					"id" : "obj-28"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "key",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 450.0, 29.0, 20.0 ],
					"id" : "obj-29"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "r = right",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 465.0, 63.0, 20.0 ],
					"id" : "obj-30"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "l = left",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 481.0, 52.0, 20.0 ],
					"id" : "obj-31"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "b = back or rear speakers",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 511.0, 162.0, 20.0 ],
					"id" : "obj-32"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "f = front speakers",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 496.0, 117.0, 20.0 ],
					"id" : "obj-33"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "u = upper speakers in with height decodes",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 526.0, 255.0, 20.0 ],
					"id" : "obj-34"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "d = lower speakers in with height decodes",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 380.0, 540.0, 253.0, 20.0 ],
					"id" : "obj-35"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_title",
					"text" : "ambidec~",
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
					"text" : "Ambisonic decoder",
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
