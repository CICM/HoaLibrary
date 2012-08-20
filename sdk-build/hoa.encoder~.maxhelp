{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 86.0, 113.0, 1388.0, 694.0 ],
		"bglocked" : 0,
		"defrect" : [ 86.0, 113.0, 1388.0, 694.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 11.595187,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"boxes" : [ 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "sig~",
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"fontname" : "Arial",
					"patching_rect" : [ 282.0, 300.0, 32.0, 20.0 ],
					"id" : "obj-64",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-64",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 282.0, 300.0, 32.0, 20.0 ],
					"text" : "sig~"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "message",
					"text" : "open",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 660.0, 135.0, 36.0, 18.0 ],
					"id" : "obj-63",
					"fontsize" : 11.595187,
					"numinlets" : 2
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-63",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 660.0, 135.0, 36.0, 18.0 ],
					"text" : "open"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-22",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 312.0, 255.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-8",
					"maxclass" : "number~",
					"mode" : 2,
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"patching_rect" : [ 135.0, 450.0, 56.0, 20.0 ],
					"sig" : 0.0
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-36",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 600.0, 300.0, 127.0, 46.0 ],
					"text" : "Arg2 : Shape of the loudspeakers array (default 0 - Linear)"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 450.0, 513.0, 70.0, 20.0 ],
					"text" : "loadmess 2"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 450.0, 240.0, 70.0, 20.0 ],
					"text" : "loadmess 0"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-49",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 600.0, 450.0, 142.0, 33.0 ],
					"text" : "Arg5 : Delay interpolation (default 2 - Lagrange)"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-44",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 600.0, 390.0, 126.0, 60.0 ],
					"text" : "Arg4 : Distance between the speaker array and the listener in meter (default 1.5)"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-43",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 600.0, 345.0, 127.0, 46.0 ],
					"text" : "Arg3 : Distance between speakers in meter (default 0.2)"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-42",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 600.0, 270.0, 125.0, 33.0 ],
					"text" : "Arg1 : Number of speakers (default 16)"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2,
					"id" : "obj-24",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 585.0, 255.0, 159.25, 264.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-26",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 765.0, 150.0, 47.0, 20.0 ],
					"text" : "Zoom :"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-19",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.01,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 829.0, 150.0, 50.0, 20.0 ]
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "flonum",
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"fontname" : "Arial",
					"patching_rect" : [ 312.0, 255.0, 50.0, 20.0 ],
					"id" : "obj-22",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"id" : "obj-7",
					"increment" : 0.05,
					"maxclass" : "incdec",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 810.0, 150.0, 20.0, 20.0 ]
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "number~",
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"mode" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 75.0, 435.0, 56.0, 20.0 ],
					"sig" : 0.0,
					"id" : "obj-8",
					"fontsize" : 11.595187,
					"numinlets" : 2
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-52",
					"items" : [ "Linear", ",", "Circular" ],
					"maxclass" : "umenu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"patching_rect" : [ 450.0, 270.0, 100.0, 20.0 ],
					"types" : [  ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-51",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 450.0, 421.0, 79.0, 20.0 ],
					"text" : "loadmess 1.5"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"text" : "Arg2 : Shape of the loudspeakers array (default 0 - Linear)",
					"linecount" : 3,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 600.0, 300.0, 127.0, 46.0 ],
					"id" : "obj-36",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-47",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 450.0, 330.0, 79.0, 20.0 ],
					"text" : "loadmess 0.2"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "loadmess 2",
					"numoutlets" : 1,
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 513.0, 70.0, 20.0 ],
					"id" : "obj-13",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-27",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 450.0, 300.0, 58.0, 18.0 ],
					"text" : "shape $1"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "loadmess 0",
					"numoutlets" : 1,
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 240.0, 70.0, 20.0 ],
					"id" : "obj-6",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 450.0, 330.0, 63.0, 20.0 ],
					"text" : "s huygens"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"text" : "Arg5 : Delay interpolation (default 2 - Lagrange)",
					"linecount" : 2,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 600.0, 450.0, 142.0, 33.0 ],
					"id" : "obj-49",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-17",
					"items" : [ "Linear", ",", "Quadratic", ",", "Lagrange" ],
					"maxclass" : "umenu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"patching_rect" : [ 450.0, 540.0, 100.0, 20.0 ],
					"types" : [  ]
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"text" : "Arg4 : Distance between the speaker array and the listener in meter (default 1.5)",
					"linecount" : 4,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 600.0, 390.0, 126.0, 60.0 ],
					"id" : "obj-44",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1155.0, 585.0, 47.0, 20.0 ],
					"text" : "s yPos"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"text" : "Arg3 : Distance between speakers in meter (default 0.2)",
					"linecount" : 3,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 600.0, 345.0, 127.0, 46.0 ],
					"id" : "obj-43",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 780.0, 585.0, 47.0, 20.0 ],
					"text" : "s xPos"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"text" : "Arg1 : Number of speakers (default 16)",
					"linecount" : 2,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 600.0, 270.0, 125.0, 33.0 ],
					"id" : "obj-42",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 20.0,
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 890.0, 149.0, 138.0, 29.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 674.0, 124.0, 245.0, 29.0 ],
					"text" : "User Interface"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "panel",
					"numoutlets" : 0,
					"border" : 2,
					"patching_rect" : [ 585.0, 255.0, 159.25, 264.0 ],
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-24",
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Zoom :",
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 765.0, 150.0, 47.0, 20.0 ],
					"id" : "obj-26",
					"fontsize" : 11.595187,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"fontname" : "Arial",
					"patching_rect" : [ 829.0, 150.0, 50.0, 20.0 ],
					"id" : "obj-19",
					"minimum" : 0.01,
					"fontsize" : 11.595187,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "incdec",
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 810.0, 150.0, 20.0, 20.0 ],
					"id" : "obj-7",
					"numinlets" : 1,
					"increment" : 0.05
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"fontname" : "Arial",
					"items" : [ "Linear", ",", "Circular" ],
					"patching_rect" : [ 450.0, 270.0, 100.0, 20.0 ],
					"types" : [  ],
					"id" : "obj-52",
					"fontsize" : 11.595187,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 1.5",
					"numoutlets" : 1,
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 421.0, 79.0, 20.0 ],
					"id" : "obj-51",
					"fontsize" : 11.595187,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0.2",
					"numoutlets" : 1,
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 330.0, 79.0, 20.0 ],
					"id" : "obj-47",
					"fontsize" : 11.595187,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "shape $1",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 300.0, 58.0, 18.0 ],
					"id" : "obj-27",
					"fontsize" : 11.595187,
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s huygens",
					"numoutlets" : 0,
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 330.0, 63.0, 20.0 ],
					"id" : "obj-28",
					"fontsize" : 11.595187,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"fontname" : "Arial",
					"items" : [ "Linear", ",", "Quadratic", ",", "Lagrange" ],
					"patching_rect" : [ 450.0, 540.0, 100.0, 20.0 ],
					"types" : [  ],
					"id" : "obj-17",
					"fontsize" : 11.595187,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s yPos",
					"numoutlets" : 0,
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 1155.0, 585.0, 47.0, 20.0 ],
					"id" : "obj-41",
					"fontsize" : 12.0,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s xPos",
					"numoutlets" : 0,
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 780.0, 585.0, 47.0, 20.0 ],
					"id" : "obj-14",
					"fontsize" : 12.0,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "User Interface",
					"presentation_rect" : [ 674.0, 124.0, 245.0, 29.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 890.0, 149.0, 138.0, 29.0 ],
					"presentation" : 1,
					"id" : "obj-23",
					"fontsize" : 20.0,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jsui",
					"presentation_rect" : [ 103.999969, 126.0, 510.0, 510.0 ],
					"numoutlets" : 1,
					"jsarguments" : [  ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 780.0, 180.0, 394.0, 394.0 ],
					"presentation" : 1,
					"filename" : "wfsUserInter.js",
					"id" : "obj-68",
<<<<<<< HEAD
					"numinlets" : 1
=======
					"numinlets" : 1,
					"presentation" : 1
=======
					"filename" : "wfsUserInter.js",
					"id" : "obj-68",
					"jsarguments" : [  ],
					"maxclass" : "jsui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 780.0, 180.0, 394.0, 394.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 103.999969, 126.0, 510.0, 510.0 ]
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "flonum",
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 450.0, 50.0, 20.0 ],
					"id" : "obj-39",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-39",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 450.0, 450.0, 50.0, 20.0 ]
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "flonum",
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 360.0, 50.0, 20.0 ],
					"id" : "obj-37",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-37",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 450.0, 360.0, 50.0, 20.0 ]
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "message",
					"text" : "delta $1",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 390.0, 52.0, 18.0 ],
					"id" : "obj-30",
					"fontsize" : 11.595187,
					"numinlets" : 2
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-30",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 450.0, 390.0, 52.0, 18.0 ],
					"text" : "delta $1"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "s huygens",
					"numoutlets" : 0,
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 420.0, 63.0, 20.0 ],
					"id" : "obj-31",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 450.0, 420.0, 63.0, 20.0 ],
					"text" : "s huygens"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "message",
					"text" : "distance $1",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 480.0, 70.0, 18.0 ],
					"id" : "obj-20",
					"fontsize" : 11.595187,
					"numinlets" : 2
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-20",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 450.0, 480.0, 70.0, 18.0 ],
					"text" : "distance $1"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "s huygens",
					"numoutlets" : 0,
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 510.0, 63.0, 20.0 ],
					"id" : "obj-21",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-21",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 450.0, 510.0, 63.0, 20.0 ],
					"text" : "s huygens"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "message",
					"text" : "interpolation $1",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 570.0, 90.0, 18.0 ],
					"id" : "obj-15",
					"fontsize" : 11.595187,
					"numinlets" : 2
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-15",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 450.0, 570.0, 90.0, 18.0 ],
					"text" : "interpolation $1"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "s huygens",
					"numoutlets" : 0,
					"hidden" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 450.0, 600.0, 63.0, 20.0 ],
					"id" : "obj-11",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 450.0, 600.0, 63.0, 20.0 ],
					"text" : "s huygens"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "panel",
					"numoutlets" : 0,
					"border" : 2,
					"patching_rect" : [ 435.0, 255.0, 136.25, 380.0 ],
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-10",
					"numinlets" : 1
=======
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2,
					"id" : "obj-10",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 435.0, 255.0, 136.25, 380.0 ]
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "hoa.encoder~ 7",
					"numoutlets" : 15,
					"fontsize" : 12.0,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
					"fontname" : "Arial",
					"patching_rect" : [ 75.0, 379.0, 227.0, 20.0 ],
					"id" : "obj-12",
					"numinlets" : 2
=======
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-12",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 15,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
<<<<<<< HEAD
					"fontname" : "Arial",
					"patching_rect" : [ 75.0, 379.0, 208.0, 20.0 ],
					"id" : "obj-12",
					"fontsize" : 12.0,
					"numinlets" : 2
=======
					"patching_rect" : [ 75.0, 379.0, 227.0, 20.0 ],
					"text" : "hoa.encoder~ 7"
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "ezdac~",
					"numoutlets" : 0,
					"patching_rect" : [ 490.0, 167.0, 45.0, 45.0 ],
					"id" : "obj-32",
<<<<<<< HEAD
					"local" : 1,
					"numinlets" : 2
=======
=======
					"id" : "obj-32",
					"local" : 1,
					"maxclass" : "ezdac~",
>>>>>>> Rien
					"numinlets" : 2,
					"local" : 1
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"text" : "Audio On/Off : spacebar",
=======
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-33",
					"maxclass" : "comment",
					"numinlets" : 1,
>>>>>>> Rien
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 448.375, 127.5, 150.0, 20.0 ],
<<<<<<< HEAD
					"id" : "obj-33",
					"fontsize" : 12.0,
					"numinlets" : 1
=======
					"text" : "Audio On/Off : spacebar"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "p audioPanic 32",
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 464.0, 147.5, 97.0, 20.0 ],
					"id" : "obj-34",
					"fontsize" : 12.0,
					"numinlets" : 1,
=======
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
>>>>>>> Rien
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 363.0, 100.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 363.0, 100.0, 640.0, 480.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"boxes" : [ 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "button",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 120.0, 270.0, 20.0, 20.0 ],
									"id" : "obj-32",
									"numinlets" : 1
=======
									"id" : "obj-32",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 120.0, 270.0, 20.0, 20.0 ]
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "newobj",
									"text" : "togedge",
									"numoutlets" : 2,
									"outlettype" : [ "bang", "bang" ],
									"fontname" : "Arial",
									"patching_rect" : [ 120.0, 240.0, 54.0, 20.0 ],
									"id" : "obj-26",
									"fontsize" : 12.0,
									"numinlets" : 1
=======
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-26",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "bang", "bang" ],
									"patching_rect" : [ 120.0, 240.0, 54.0, 20.0 ],
									"text" : "togedge"
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "newobj",
									"text" : "!=",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"fontname" : "Arial",
									"patching_rect" : [ 120.0, 210.0, 33.5, 20.0 ],
									"id" : "obj-25",
									"fontsize" : 12.0,
									"numinlets" : 2
=======
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-25",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 120.0, 210.0, 33.5, 20.0 ],
									"text" : "!="
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "newobj",
									"text" : "dac~",
=======
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-22",
									"maxclass" : "newobj",
									"numinlets" : 2,
>>>>>>> Rien
									"numoutlets" : 0,
									"fontname" : "Arial",
									"patching_rect" : [ 45.0, 315.0, 37.0, 20.0 ],
<<<<<<< HEAD
									"id" : "obj-22",
									"fontsize" : 12.0,
									"numinlets" : 2
=======
									"text" : "dac~"
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "newobj",
									"text" : "dspstate~",
									"numoutlets" : 4,
									"outlettype" : [ "int", "float", "int", "int" ],
									"fontname" : "Arial",
									"patching_rect" : [ 120.0, 150.0, 63.0, 20.0 ],
									"id" : "obj-3",
									"fontsize" : 12.0,
									"numinlets" : 1
=======
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "int", "float", "int", "int" ],
									"patching_rect" : [ 120.0, 150.0, 63.0, 20.0 ],
									"text" : "dspstate~"
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 120.0, 60.0, 25.0, 25.0 ],
									"id" : "obj-2",
									"numinlets" : 0,
									"comment" : "ASCII Code of key pressed"
=======
									"comment" : "ASCII Code of key pressed",
									"id" : "obj-2",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 120.0, 60.0, 25.0, 25.0 ]
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "newobj",
									"text" : "zl slice 1",
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 150.0, 90.0, 57.0, 20.0 ],
									"id" : "obj-1",
									"fontsize" : 12.0,
									"numinlets" : 2
=======
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 150.0, 90.0, 57.0, 20.0 ],
									"text" : "zl slice 1"
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "newobj",
									"text" : "patcherargs",
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 150.0, 60.0, 74.0, 20.0 ],
									"id" : "obj-8",
									"fontsize" : 12.0,
									"numinlets" : 1
=======
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-8",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 150.0, 60.0, 74.0, 20.0 ],
									"text" : "patcherargs"
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "newobj",
									"text" : "sel 32",
									"numoutlets" : 2,
									"outlettype" : [ "bang", "" ],
									"fontname" : "Arial",
									"patching_rect" : [ 45.0, 120.0, 43.0, 20.0 ],
									"id" : "obj-29",
									"fontsize" : 12.0,
									"numinlets" : 2
=======
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-29",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "bang", "" ],
									"patching_rect" : [ 45.0, 120.0, 43.0, 20.0 ],
									"text" : "sel 32"
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "newobj",
									"text" : "key",
									"numoutlets" : 4,
									"outlettype" : [ "int", "int", "int", "int" ],
									"fontname" : "Arial",
									"patching_rect" : [ 45.0, 60.0, 59.5, 20.0 ],
									"id" : "obj-28",
									"fontsize" : 12.0,
									"numinlets" : 0
=======
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-28",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 4,
									"outlettype" : [ "int", "int", "int", "int" ],
									"patching_rect" : [ 45.0, 60.0, 59.5, 20.0 ],
									"text" : "key"
>>>>>>> Rien
								}

							}
, 							{
								"box" : 								{
<<<<<<< HEAD
									"maxclass" : "toggle",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 45.0, 165.0, 20.0, 20.0 ],
									"id" : "obj-4",
									"numinlets" : 1
=======
									"id" : "obj-4",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 45.0, 165.0, 20.0, 20.0 ]
>>>>>>> Rien
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-1", 1 ],
									"destination" : [ "obj-29", 1 ],
									"hidden" : 0,
									"midpoints" : [ 197.5, 119.0, 78.5, 119.0 ]
=======
									"destination" : [ "obj-29", 1 ],
									"hidden" : 0,
									"midpoints" : [ 197.5, 119.0, 78.5, 119.0 ],
									"source" : [ "obj-1", 1 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-29", 1 ],
									"hidden" : 0,
									"midpoints" : [ 129.5, 105.0, 78.5, 105.0 ]
=======
									"destination" : [ "obj-29", 1 ],
									"hidden" : 0,
									"midpoints" : [ 129.5, 105.0, 78.5, 105.0 ],
									"source" : [ "obj-2", 0 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-25", 0 ],
=======
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
									"destination" : [ "obj-26", 0 ],
									"hidden" : 0,
									"midpoints" : [  ],
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
=======
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ],
									"source" : [ "obj-26", 0 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-28", 0 ],
=======
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
									"destination" : [ "obj-29", 0 ],
									"hidden" : 0,
									"midpoints" : [  ],
									"source" : [ "obj-28", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ],
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-3", 0 ],
=======
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
									"destination" : [ "obj-25", 0 ],
									"hidden" : 0,
									"midpoints" : [  ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [ 129.5, 291.0, 75.0, 291.0, 75.0, 162.0, 54.5, 162.0 ]
=======
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [ 129.5, 291.0, 75.0, 291.0, 75.0, 162.0, 54.5, 162.0 ],
									"source" : [ "obj-32", 0 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-4", 0 ],
=======
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
									"destination" : [ "obj-22", 0 ],
									"hidden" : 0,
									"midpoints" : [  ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-25", 1 ],
									"hidden" : 0,
									"midpoints" : [ 54.5, 195.0, 144.0, 195.0 ]
=======
									"destination" : [ "obj-25", 1 ],
									"hidden" : 0,
									"midpoints" : [ 54.5, 195.0, 144.0, 195.0 ],
									"source" : [ "obj-4", 0 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
								}

							}
, 							{
								"patchline" : 								{
<<<<<<< HEAD
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
=======
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ],
									"source" : [ "obj-8", 0 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
								}

							}
 ]
					}
,
					"patching_rect" : [ 464.0, 147.5, 97.0, 20.0 ],
					"saved_object_attributes" : 					{
<<<<<<< HEAD
=======
<<<<<<< HEAD
						"default_fontsize" : 12.0,
=======
						"fontname" : "Arial",
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
						"globalpatchername" : "",
						"default_fontface" : 0,
<<<<<<< HEAD
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0
=======
<<<<<<< HEAD
						"fontname" : "Arial",
						"default_fontname" : "Arial"
=======
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					}
,
					"text" : "p audioPanic 32"
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "panel",
=======
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2,
					"id" : "obj-35",
					"maxclass" : "panel",
					"numinlets" : 1,
>>>>>>> Rien
					"numoutlets" : 0,
					"border" : 2,
					"patching_rect" : [ 435.0, 120.0, 177.25, 122.0 ],
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-35",
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"text" : "hoa.encoder~ by Julien Colafrancesco & Pierre Guillot\n© 2012 CICM / Universite Paris 8",
					"linecount" : 2,
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-59",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
>>>>>>> Rien
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 497.75, 6.0, 293.0, 33.0 ],
<<<<<<< HEAD
					"id" : "obj-59",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"text" : "hoa.encoder~ by Julien Colafrancesco & Pierre Guillot\n© 2012 CICM / Universite Paris 8"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"varname" : "autohelp_top_title",
					"text" : "hoa.encoder~",
					"numoutlets" : 0,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"fontname" : "Arial",
					"patching_rect" : [ 7.0, 6.0, 485.0, 30.0 ],
					"fontface" : 3,
					"id" : "obj-2",
<<<<<<< HEAD
					"fontsize" : 20.871338,
					"numinlets" : 1,
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ]
=======
					"numinlets" : 1
=======
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 20.871338,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"id" : "obj-2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.0, 6.0, 485.0, 30.0 ],
					"text" : "hoa.encoder~",
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ],
					"varname" : "autohelp_top_title"
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"varname" : "autohelp_top_digest",
					"text" : "A high order ambisonic encoder.",
					"numoutlets" : 0,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"fontname" : "Arial",
					"patching_rect" : [ 7.0, 35.0, 503.0, 21.0 ],
					"id" : "obj-3",
<<<<<<< HEAD
					"fontsize" : 12.754705,
					"numinlets" : 1,
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ]
=======
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 12.754705,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"id" : "obj-3",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.0, 35.0, 503.0, 21.0 ],
					"text" : "A high order ambisonic encoder.",
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ],
					"varname" : "autohelp_top_digest"
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "comment",
					"varname" : "autohelp_top_description",
					"text" : "hoa.encoder~ is a sound spatializer that uses ambisonic algorithm.",
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-5",
					"maxclass" : "comment",
					"numinlets" : 1,
>>>>>>> Rien
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 7.0, 56.0, 510.0, 20.0 ],
<<<<<<< HEAD
					"id" : "obj-5",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"text" : "hoa.encoder~ is a sound spatializer that uses ambisonic algorithm.",
					"varname" : "autohelp_top_description"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "r huygens",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 795.0, 225.0, 61.0, 20.0 ],
					"id" : "obj-46",
					"fontsize" : 11.595187,
					"numinlets" : 0
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-46",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 795.0, 225.0, 61.0, 20.0 ],
					"text" : "r huygens"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "newobj",
					"text" : "route delta shape distance",
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"fontname" : "Arial",
					"patching_rect" : [ 855.0, 195.0, 147.0, 20.0 ],
					"id" : "obj-45",
					"fontsize" : 11.595187,
					"numinlets" : 1
=======
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-45",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"patching_rect" : [ 855.0, 195.0, 147.0, 20.0 ],
					"text" : "route delta shape distance"
>>>>>>> Rien
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "panel",
=======
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2,
					"id" : "obj-1",
					"maxclass" : "panel",
					"numinlets" : 1,
>>>>>>> Rien
					"numoutlets" : 0,
					"border" : 2,
					"patching_rect" : [ 750.0, 135.0, 453.25, 481.0 ],
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-1",
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
<<<<<<< HEAD
					"maxclass" : "panel",
					"varname" : "autohelp_top_panel",
					"numoutlets" : 0,
					"mode" : 1,
					"patching_rect" : [ 2.0, 4.0, 495.0, 52.0 ],
					"grad1" : [ 0.27, 0.35, 0.47, 1.0 ],
					"grad2" : [ 0.85, 0.85, 0.85, 1.0 ],
					"background" : 1,
					"id" : "obj-9",
					"numinlets" : 1
=======
					"background" : 1,
					"grad1" : [ 0.27, 0.35, 0.47, 1.0 ],
					"grad2" : [ 0.85, 0.85, 0.85, 1.0 ],
					"id" : "obj-9",
					"maxclass" : "panel",
					"mode" : 1,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2.0, 4.0, 495.0, 52.0 ],
					"varname" : "autohelp_top_panel"
>>>>>>> Rien
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-45", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 14 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-17", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-64", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 13 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-52", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-63", 0 ],
					"destination" : [ "obj-32", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 12 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-52", 0 ],
					"destination" : [ "obj-27", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-68", 0 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ]
=======
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 11 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-51", 0 ],
					"destination" : [ "obj-39", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-7", 0 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ]
=======
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 10 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-47", 0 ],
					"destination" : [ "obj-37", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-19", 0 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ]
=======
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 9 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-28", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-15", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 8 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
=======
<<<<<<< HEAD
					"source" : [ "obj-68", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 1,
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"midpoints" : [  ]
=======
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 7 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-21", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-20", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 6 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-31", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-30", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 5 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-30", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-31", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 4 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-20", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-21", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 3 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-68", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
=======
<<<<<<< HEAD
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-11", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 2 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-15", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-28", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 1 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 0.0 ],
					"midpoints" : [  ]
=======
<<<<<<< HEAD
					"source" : [ "obj-47", 0 ],
					"destination" : [ "obj-37", 0 ],
=======
					"destination" : [ "obj-8", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-12", 0 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 0.0 ],
					"midpoints" : [  ]
=======
<<<<<<< HEAD
					"source" : [ "obj-51", 0 ],
					"destination" : [ "obj-39", 0 ],
=======
					"destination" : [ "obj-17", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-13", 0 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-68", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 0.0 ],
					"midpoints" : [  ]
=======
<<<<<<< HEAD
					"source" : [ "obj-52", 0 ],
					"destination" : [ "obj-27", 0 ],
=======
					"destination" : [ "obj-11", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-15", 0 ]
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-63", 0 ],
					"destination" : [ "obj-32", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-52", 0 ],
=======
					"destination" : [ "obj-15", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-64", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-17", 0 ],
=======
					"color" : [ 0.0, 0.0, 0.0, 0.0 ],
					"destination" : [ "obj-68", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 14 ],
					"destination" : [ "obj-8", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-45", 0 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ]
=======
					"color" : [ 0.0, 0.0, 0.0, 0.0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-19", 0 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 13 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 0 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
=======
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-20", 0 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 12 ],
					"destination" : [ "obj-8", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-64", 0 ],
					"destination" : [ "obj-12", 0 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ]
=======
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-22", 0 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 11 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 1 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-28", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 10 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 2 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
=======
					"destination" : [ "obj-31", 0 ],
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-30", 0 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 9 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 3 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-30", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 8 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 4 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-20", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 7 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 5 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-45", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 6 ],
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-37", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-47", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 5 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 7 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-39", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 4 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 8 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-27", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 3 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 9 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-52", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 2 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 10 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-32", 0 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 1 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 11 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-12", 1 ],
>>>>>>> Rien
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-64", 0 ],
					"destination" : [ "obj-12", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 12 ],
					"destination" : [ "obj-8", 0 ],
=======
					"destination" : [ "obj-12", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-12", 0 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 13 ],
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
=======
					"destination" : [ "obj-14", 0 ],
					"hidden" : 1,
					"midpoints" : [  ],
					"source" : [ "obj-68", 0 ]
>>>>>>> Rien
				}

			}
, 			{
				"patchline" : 				{
<<<<<<< HEAD
					"source" : [ "obj-64", 0 ],
					"destination" : [ "obj-12", 1 ],
=======
<<<<<<< HEAD
					"source" : [ "obj-12", 14 ],
					"destination" : [ "obj-8", 0 ],
=======
					"color" : [ 0.0, 0.0, 0.0, 0.0 ],
					"destination" : [ "obj-19", 0 ],
>>>>>>> Rien
>>>>>>> 771c287f66c253c690133b1f0b9996f831fe7e23
					"hidden" : 0,
					"midpoints" : [  ],
					"source" : [ "obj-7", 0 ]
				}

			}
 ]
	}

}
