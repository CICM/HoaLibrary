{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 64.0, 103.0, 858.0, 460.0 ],
		"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
		"bglocked" : 0,
		"defrect" : [ 64.0, 103.0, 858.0, 460.0 ],
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
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "This is a very simple phase vocoder.  It is not the best quality possible but it gives an easy example of the technique.",
					"linecount" : 3,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 347.0, 387.0, 283.0, 46.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-41",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "record some frames of spectral data",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 199.0, 200.0, 197.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-40",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "wrap values between -π and π",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 173.0, 134.0, 172.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-39",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "notice that we are recording amplitude and \"phase difference\" which can be used to reconstruct a correct phase value when we play back the spectral frames at a different speed....",
					"linecount" : 4,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 52.0, 223.0, 288.0, 60.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-36",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "20000 ms. = 882000 samples at 44.1kHz = 1722 frames of spectrum data at a FFT size of 1024 points (512 sigvs. for this subpatch).",
					"linecount" : 4,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 42.0, 375.0, 215.0, 60.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-35",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "<===",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 72.0, 166.0, 32.0, 18.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-34",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "this example shows how to use the sync inlet of the fftin~ instead of count~",
					"linecount" : 3,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 588.0, 151.0, 183.0, 46.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-32",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "phasewrap~",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 97.0, 134.0, 74.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-1",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sig~",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 477.0, 125.0, 32.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-2",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r recstart",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 0,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 6.0, 163.0, 56.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-3",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "in 2",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 477.0, 31.0, 29.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-4",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"saved_object_attributes" : 					{
						"attr_comment" : ""
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ifft window to patcher.",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 352.0, 331.0, 123.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-5",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "amp/phase to x/y.",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 373.0, 301.0, 102.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-6",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "index~ this 1",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 477.0, 241.0, 76.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-7",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"bgcolor2" : [ 0.867, 0.867, 0.867, 1.0 ],
					"bgcolor" : [ 0.867, 0.867, 0.867, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 41.0, 320.0, 36.0, 18.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-8",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"gradient" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "*~ 512",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 477.0, 159.0, 44.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-9",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "+~",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 477.0, 202.0, 62.5, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-10",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "index~ this 2",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 563.0, 241.0, 76.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-11",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "record~ this 2",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 4,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 56.0, 201.0, 142.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-12",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "buffer~ this 20000 2",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 41.0, 347.0, 130.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 2,
					"presentation" : 0,
					"id" : "obj-13",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "float", "bang" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "frameaccum~ 1",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 563.0, 264.0, 91.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-14",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "framedelta~",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 97.0, 94.0, 72.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 1,
					"presentation" : 0,
					"id" : "obj-15",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "poltocar~",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 477.0, 301.0, 59.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 2,
					"presentation" : 0,
					"id" : "obj-16",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal", "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "cartopol~",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 56.0, 65.0, 60.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 2,
					"presentation" : 0,
					"id" : "obj-17",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal", "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Spectral frame size (sigvs).",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 671.0, 88.0, 150.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-18",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"htricolor" : [ 0.87, 0.82, 0.24, 1.0 ],
					"bordercolor" : [ 0.5, 0.5, 0.5, 1.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"tricolor" : [ 0.75, 0.75, 0.75, 1.0 ],
					"hbgcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 608.0, 89.0, 60.0, 20.0 ],
					"mouseup" : 0,
					"numoutlets" : 2,
					"format" : 0,
					"triscale" : 0.9,
					"presentation" : 0,
					"id" : "obj-19",
					"fontname" : "Arial",
					"htextcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"minimum" : "<none>",
					"outlettype" : [ "int", "bang" ],
					"ignoreclick" : 0,
					"outputonclick" : 0,
					"triangle" : 1,
					"maximum" : "<none>",
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187,
					"cantchange" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "fftinfo~",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 594.0, 60.0, 59.5, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 4,
					"presentation" : 0,
					"id" : "obj-20",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "int", "int", "int", "int" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "fftin~ 1",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 56.0, 36.0, 101.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 3,
					"presentation" : 0,
					"id" : "obj-21",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"outlettype" : [ "signal", "signal", "signal" ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "fftout~ 1",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"bgcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"background" : 0,
					"patching_rect" : [ 477.0, 331.0, 59.0, 20.0 ],
					"color" : [ 0.8, 0.84, 0.71, 1.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-22",
					"fontname" : "Arial",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 0,
					"hidden" : 0,
					"fontface" : 0,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "record something (sent from parent patch).",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 108.0, 166.0, 230.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-23",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "convert (real, imag) to (amplitude, phase).",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 121.0, 65.0, 226.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-24",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "compute phase deviation between successive FFT frames.",
					"linecount" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 172.0, 94.0, 202.0, 33.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-25",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "accumulate the \"phase difference\" values to reconstruct a \"correct\" phase value for the bins - this is called \"running phase\".  The non-zero argument to frameaccum~ tells it to perform high-resolution phase wrapping on the accumulated signal to preserve fidelity.",
					"linecount" : 6,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 573.0, 288.0, 245.0, 86.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-26",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "play back frames at any rate",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 508.0, 30.0, 156.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-27",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "fft window in from patcher.",
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 56.0, 15.0, 146.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-28",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "buffer which will hold our  spectral data.",
					"linecount" : 2,
					"presentation_rect" : [ 0.0, 0.0, 0.0, 0.0 ],
					"numinlets" : 1,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"background" : 0,
					"patching_rect" : [ 83.0, 309.0, 123.0, 33.0 ],
					"numoutlets" : 0,
					"presentation" : 0,
					"id" : "obj-30",
					"fontname" : "Arial",
					"underline" : 0,
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"ignoreclick" : 1,
					"hidden" : 0,
					"fontface" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-16", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 572.5, 285.0, 526.5, 285.0 ]
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
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-9", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 1 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 486.5, 80.0, 486.5, 80.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 1 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 106.5, 88.0, 106.5, 88.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-12", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 1 ],
					"destination" : [ "obj-17", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 106.5, 62.0, 106.5, 62.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 1 ],
					"destination" : [ "obj-22", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 486.5, 230.0, 572.5, 230.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 2 ],
					"destination" : [ "obj-10", 1 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [ 147.5, 64.5, 530.0, 64.5 ]
				}

			}
 ]
	}

}
