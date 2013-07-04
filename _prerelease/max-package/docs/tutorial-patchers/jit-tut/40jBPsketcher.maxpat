{
	"patcher" : 	{
		"rect" : [ 242.0, 51.0, 756.0, 501.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 242.0, 51.0, 756.0, 501.0 ],
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
		"imprint" : 0,
		"metadata" : [  ],
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "thecomment[7]",
					"text" : "draw a square and scale it",
					"id" : "obj-1",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 137.0, 1438.0, 146.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "thecomment[6]",
					"text" : "draw a square and translate it",
					"id" : "obj-2",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 137.0, 1238.0, 163.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "thecomment[5]",
					"text" : "draw a square and rotate it, drawing unit vectors for each axis",
					"id" : "obj-3",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 137.0, 1018.0, 327.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "thecomment[4]",
					"text" : "draw a square and rotate it",
					"id" : "obj-4",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 137.0, 847.0, 148.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "thecomment[3]",
					"text" : "draw a square, filled or outlined",
					"id" : "obj-5",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 123.0, 627.0, 172.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "thecomment[2]",
					"text" : "draw a filled triangle with separately colored vertices",
					"id" : "obj-6",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 74.0, 499.0, 279.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "thecomment[1]",
					"text" : "draw a filled triangle",
					"id" : "obj-7",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 74.0, 299.0, 114.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "thecomment",
					"text" : "draw an outlined triangle",
					"id" : "obj-8",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 74.0, 99.0, 137.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glbegin triangles, glcolor 1 0 0 1, glvertex -0.5 -0.5, glcolor 0 1 0 1, glvertex 0 0.5, glcolor 0 0 1 1, glvertex 0.5 -0.5, glend",
					"linecount" : 2,
					"outlettype" : [ "" ],
					"id" : "obj-9",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 446.0, 385.0, 31.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "offset 0 $1",
					"outlettype" : [ "" ],
					"id" : "obj-10",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 931.0, 145.0, 65.0, 18.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* -200",
					"outlettype" : [ "int" ],
					"id" : "obj-11",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 931.0, 118.0, 41.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "inlet",
					"outlettype" : [ "" ],
					"id" : "obj-12",
					"numinlets" : 0,
					"patching_rect" : [ 931.0, 92.0, 25.0, 25.0 ],
					"numoutlets" : 1,
					"comment" : ""
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "thispatcher",
					"outlettype" : [ "", "" ],
					"id" : "obj-13",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 931.0, 180.0, 67.0, 20.0 ],
					"numoutlets" : 2,
					"fontname" : "Arial",
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-14",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 77.0, 1438.0, 36.0, 20.0 ],
					"numoutlets" : 2,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-15",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 24.0, 1438.0, 36.0, 20.0 ],
					"numoutlets" : 2,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pak 0. 0.",
					"outlettype" : [ "" ],
					"id" : "obj-16",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 1459.0, 55.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glmatrixmode modelview, glpushmatrix, glscale $1 $2, glbegin tri_strip, glcolor 1 0 0 1, glvertex -0.5 -0.5, glcolor 0 1 0 1, glvertex -0.5 0.5, glcolor 0 0 1 1, glvertex 0.5 -0.5, glcolor 1 1 1 1, glvertex 0.5 0.5, glend, glpopmatrix",
					"linecount" : 4,
					"outlettype" : [ "" ],
					"id" : "obj-17",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 1485.0, 327.0, 58.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-18",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 77.0, 1238.0, 36.0, 20.0 ],
					"numoutlets" : 2,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-19",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 24.0, 1238.0, 36.0, 20.0 ],
					"numoutlets" : 2,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pak 0. 0.",
					"outlettype" : [ "" ],
					"id" : "obj-20",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 1259.0, 55.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glmatrixmode modelview, glpushmatrix, gltranslate $1 $2, glbegin tri_strip, glcolor 1 0 0 1, glvertex -0.5 -0.5, glcolor 0 1 0 1, glvertex -0.5 0.5, glcolor 0 0 1 1, glvertex 0.5 -0.5, glcolor 1 1 1 1, glvertex 0.5 0.5, glend, glpopmatrix",
					"linecount" : 5,
					"outlettype" : [ "" ],
					"id" : "obj-21",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 1285.0, 276.0, 71.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-22",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 100.0, 1018.0, 36.0, 20.0 ],
					"numoutlets" : 2,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-23",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 62.0, 1018.0, 36.0, 20.0 ],
					"numoutlets" : 2,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-24",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 24.0, 1018.0, 36.0, 20.0 ],
					"numoutlets" : 2,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pak 0. 0. 0.",
					"outlettype" : [ "" ],
					"id" : "obj-25",
					"fontsize" : 10.0,
					"numinlets" : 3,
					"patching_rect" : [ 24.0, 1038.0, 68.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glmatrixmode modelview, glpushmatrix, glrotate $1 1 0 0, glrotate $2 0 1 0, glrotate $3 0 0 1, glbegin tri_strip, glcolor 1 0 0 1, glvertex -0.5 -0.5, glcolor 0 1 0 1, glvertex -0.5 0.5, glcolor 0 0 1 1, glvertex 0.5 -0.5, glcolor 1 1 1 1, glvertex 0.5 0.5, glend, glcolor 1 0 0 1, glbegin lines, glvertex 0 0 0, glvertex 1 0 0, glend, glcolor 0 1 0 1, glbegin lines, glvertex 0 0 0, glvertex 0 1 0, glend, glcolor 0 0 1 1, glbegin lines, glvertex 0 0 0, glvertex 0 0 1, glend, glpopmatrix",
					"linecount" : 8,
					"outlettype" : [ "" ],
					"id" : "obj-26",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 1059.0, 351.0, 111.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"id" : "obj-27",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 24.0, 847.0, 36.0, 20.0 ],
					"numoutlets" : 2,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glmatrixmode modelview, glpushmatrix, glrotate $1 0 0 1, glbegin tri_strip, glcolor 1 0 0 1, glvertex -0.5 -0.5, glcolor 0 1 0 1, glvertex -0.5 0.5, glcolor 0 0 1 1, glvertex 0.5 -0.5, glcolor 1 1 1 1, glvertex 0.5 0.5, glend, glpopmatrix",
					"linecount" : 7,
					"outlettype" : [ "" ],
					"id" : "obj-28",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 874.0, 193.0, 98.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "glbegin tri_strip, glcolor 1 0 0 1, glvertex -0.5 -0.5, glcolor 0 1 0 1, glvertex -0.5 0.5, glcolor 0 0 1 1, glvertex 0.5 -0.5, glcolor 1 1 1 1, glvertex 0.5 0.5, glend",
					"linecount" : 5,
					"outlettype" : [ "" ],
					"id" : "obj-29",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 674.0, 183.0, 71.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b i",
					"outlettype" : [ "bang", "int" ],
					"id" : "obj-30",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 24.0, 648.0, 32.5, 20.0 ],
					"numoutlets" : 2,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glpolygonmode front_and_back fill",
					"outlettype" : [ "" ],
					"id" : "obj-31",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 256.0, 698.0, 219.0, 18.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sel 0 1",
					"outlettype" : [ "bang", "bang", "" ],
					"id" : "obj-32",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 256.0, 674.0, 46.0, 20.0 ],
					"numoutlets" : 3,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glpolygonmode front_and_back line",
					"outlettype" : [ "" ],
					"id" : "obj-33",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 276.0, 719.0, 226.0, 18.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"outlettype" : [ "int", "", "" ],
					"id" : "obj-34",
					"fontsize" : 10.0,
					"items" : [ "fill", ",", "outline" ],
					"numinlets" : 1,
					"patching_rect" : [ 24.0, 627.0, 81.0, 20.0 ],
					"numoutlets" : 3,
					"fontname" : "Arial",
					"types" : [  ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glcolor 0 1 0 1, glbegin triangles, glvertex -0.5 -0.5, glvertex 0 0.5, glvertex 0.5 -0.5, glend",
					"outlettype" : [ "" ],
					"id" : "obj-35",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 246.0, 501.0, 18.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset, glcolor 0 1 0 1, glbegin line_loop, glvertex -0.5 -0.5, glvertex 0 0.5, glvertex 0.5 -0.5, glend",
					"outlettype" : [ "" ],
					"id" : "obj-36",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"patching_rect" : [ 24.0, 46.0, 503.0, 18.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "outlet",
					"id" : "obj-37",
					"numinlets" : 1,
					"patching_rect" : [ 743.0, 1572.0, 25.0, 25.0 ],
					"numoutlets" : 0,
					"comment" : ""
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-38",
					"bgcolor" : [ 0.25098, 1.0, 0.498039, 1.0 ],
					"rounded" : 0,
					"background" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 0.0, 1394.0, 600.0, 200.0 ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-39",
					"bgcolor" : [ 1.0, 0.498039, 0.25098, 1.0 ],
					"rounded" : 0,
					"background" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 0.0, 1195.0, 600.0, 200.0 ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-40",
					"bgcolor" : [ 0.498039, 1.0, 1.0, 1.0 ],
					"rounded" : 0,
					"background" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 0.0, 996.0, 600.0, 200.0 ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-41",
					"bgcolor" : [ 1.0, 0.498039, 1.0, 1.0 ],
					"rounded" : 0,
					"background" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 0.0, 797.0, 600.0, 200.0 ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-42",
					"bgcolor" : [ 1.0, 1.0, 0.498039, 1.0 ],
					"rounded" : 0,
					"background" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 0.0, 598.0, 600.0, 200.0 ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-43",
					"bgcolor" : [ 0.498039, 0.498039, 1.0, 1.0 ],
					"rounded" : 0,
					"background" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 0.0, 399.0, 600.0, 200.0 ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-44",
					"bgcolor" : [ 0.498039, 1.0, 0.498039, 1.0 ],
					"rounded" : 0,
					"background" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 0.0, 200.0, 600.0, 200.0 ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-45",
					"bgcolor" : [ 1.0, 0.498039, 0.498039, 1.0 ],
					"rounded" : 0,
					"background" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 0.0, 1.0, 600.0, 200.0 ],
					"numoutlets" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 33.5, 1557.0, 752.5, 1557.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 33.5, 1357.0, 752.5, 1357.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 33.5, 1175.0, 752.5, 1175.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 33.5, 982.0, 752.5, 982.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 33.5, 772.0, 752.5, 772.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 265.5, 757.0, 752.5, 757.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-33", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 285.5, 767.0, 752.5, 767.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 33.5, 117.0, 752.5, 117.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 33.5, 317.0, 752.5, 317.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 33.5, 517.0, 752.5, 517.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 1 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-31", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 1 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"midpoints" : [ 47.0, 670.0, 265.5, 670.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-25", 2 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-16", 1 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-20", 1 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-25", 1 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0
				}

			}
 ]
	}

}
