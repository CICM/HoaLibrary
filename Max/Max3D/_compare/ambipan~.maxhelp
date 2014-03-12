{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 311.0, 66.0, 601.0, 490.0 ],
		"bglocked" : 0,
		"defrect" : [ 311.0, 66.0, 601.0, 490.0 ],
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
					"maxclass" : "comment",
					"text" : "Based on the b_pan VST plugin by Dave Malham. Ported to MAX/MSP by Matthew Paradis\n\nMRC University of York\n\nInput 1 Left channel and messages Input 2 Right channel Output 1 W Output 2 X Output 3 Y Output 4 Z\n\nAll parameters are scaled between 0.0-1.0\n\nazl = Azimuth Left, \nell = Elevation Left, \nzel = Zeroth Left, \nfil = First Left, \ndisl = Distance Left, \ncenl = Centre Left, \ndfacl = Distance Factor Left, \nvoll = Volume Left, \nazr = Azimuth Right, \nelr = Elevation Right, \nzer = Zeroth Right, \nfir = First Right, \ndisr = Distance Right, \ncenr = Centre Right, \ndfacr = Distance Factor Right, \nvolr = Volume Right\n\nFor more information see http://www.dmalham.freeserve.co.uk/vst_ambisonics.html",
					"linecount" : 29,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 260.0, 80.0, 331.0, 407.0 ],
					"id" : "obj-16"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "L                        R",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 80.0, 130.0, 128.0, 20.0 ],
					"id" : "obj-11"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "w         x        y        z  ",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 80.0, 190.0, 128.0, 20.0 ],
					"id" : "obj-9"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_title",
					"text" : "ambipan~",
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
					"text" : "Ambisonic panner",
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
					"maxclass" : "newobj",
					"text" : "ambipan~",
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 80.0, 160.0, 123.0, 20.0 ],
					"id" : "obj-1",
					"outlettype" : [ "signal", "signal", "signal", "signal" ]
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
