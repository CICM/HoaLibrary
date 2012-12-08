{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 0,
			"revision" : 8
		}
,
		"rect" : [ 39.0, 61.0, 875.0, 639.0 ],
		"bgcolor" : [ 0.93, 0.93, 0.92, 1.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 0,
		"toolbarvisible" : 0,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"title" : "hoa.library overview",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-72",
					"linecolor" : [ 0.989051, 0.989051, 0.989051, 0.39 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 72.78125, 13.75, 5.0, 48.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-73",
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 71.78125, 12.75, 5.0, 48.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-60",
					"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.78125, 5.75, 868.21875, 8.775246 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-61",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3.78125, 4.75, 868.21875, 8.775246 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-58",
					"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.78125, 69.75, 868.21875, 8.775246 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-59",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 3.78125, 68.75, 868.21875, 8.775246 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 7.263873,
					"hidden" : 1,
					"id" : "obj-55",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -184.4375, 102.875, 55.0, 15.0 ],
					"text" : "loadmess 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.425629,
					"frgb" : 0.0,
					"hidden" : 1,
					"id" : "obj-54",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 14.5, 63.75, 33.28125, 17.0 ],
					"text" : "grow"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-52",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 3,
					"outlettype" : [ "bang", "bang", "" ],
					"patching_rect" : [ -184.4375, 148.257935, 46.0, 20.0 ],
					"text" : "sel 0 1"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-51",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 4.78125, 65.525246, 13.0, 13.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"frgb" : 0.0,
					"id" : "obj-19",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 426.5, 18.75, 437.0, 19.0 ],
					"text" : "Julien Colafrancesco, Pierre Guillot & Eliott Paris © 2012 CICM / Universite Paris 8",
					"textcolor" : [ 0.317518, 0.317518, 0.317518, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-28",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 426.5, 17.75, 437.0, 21.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-13",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -269.9375, 41.75, 177.0, 17.0 ],
					"text" : "window flags grow, window exec"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"hidden" : 1,
					"id" : "obj-6",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -253.4375, 64.75, 190.0, 17.0 ],
					"text" : "window flags nogrow, window exec"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-42",
					"maxclass" : "newobj",
					"numinlets" : 4,
					"numoutlets" : 0,
					"patching_rect" : [ -156.0, 247.257935, 143.0, 20.0 ],
					"text" : "bgcolor 0.93 0.93 0.92 1."
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-49",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 213.5, 18.75, 73.0, 20.0 ],
					"text" : "version 1.1",
					"textcolor" : [ 0.9404, 0.940544, 0.940332, 1.0 ],
					"varname" : "autohelp_top_title[3]"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-48",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 214.5, 19.75, 73.0, 20.0 ],
					"text" : "version 1.1",
					"textcolor" : [ 0.424631, 0.424696, 0.4246, 0.21 ],
					"varname" : "autohelp_top_title[2]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-35",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 213.5, 18.75, 74.0, 21.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.776471, 0.776471, 0.776471, 0.0 ],
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-33",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 651.0, 279.0, 206.0, 40.0 ],
					"text" : "This library is released under the terms of the GNU licence.",
					"textcolor" : [ 0.30292, 0.30292, 0.30292, 0.81 ],
					"varname" : "autohelp_top_description[2]"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-34",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 651.0, 279.0, 206.0, 40.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-18",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 33.6875, 522.5, 817.3125, 23.0 ],
					"textcolor" : [ 0.192668, 0.192697, 0.192653, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
					"bordercolor" : [ 0.999903, 1.0, 0.99983, 1.0 ],
					"id" : "obj-21",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 23.0625, 521.5, 6.0, 80.0 ],
					"rounded" : 5
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-17",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 18.0625, 514.5, 838.9375, 93.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"arrows" : 1,
					"border" : 2.0,
					"id" : "obj-16",
					"justification" : 1,
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 657.0, 216.5, 22.0, 10.0 ]
				}

			}
, 			{
				"box" : 				{
					"border" : 2.0,
					"id" : "obj-15",
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 679.0, 202.5, 12.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-12",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 662.0, 165.257935, 154.5, 33.0 ],
					"text" : "Click in the tab to open the appropriate help file.",
					"textcolor" : [ 0.260204, 0.260204, 0.260204, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -94.0, 137.257935, 72.0, 20.0 ],
					"text" : "loadmess 0"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 797.0625, 43.75, 65.0, 20.0 ],
					"text" : "contact us",
					"textcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"handoff" : "",
					"hilite" : 0,
					"id" : "obj-10",
					"maxclass" : "ubutton",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "", "int" ],
					"patching_rect" : [ 797.0625, 43.75, 65.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 619.529907, 138.725479, 92.470032, 20.274523 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-11",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 812.395813, 68.75, 318.0, 26.0 ],
					"text" : ";\rmax launchbrowser http://www.mshparisnord.fr/hoalibrary/en/contacts/"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ -269.9375, 91.25, 69.0, 20.0 ],
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
					"text" : "thispatcher"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.776471, 0.776471, 0.776471, 0.0 ],
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-82",
					"linecount" : 8,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 651.0, 356.5, 206.0, 142.0 ],
					"text" : "NB : to see references and tutorials pages you must before deactivate the option \"Use New Documentation Rendering\" in the global max preferences window. This is a current limitation of Max in this current version (6.0.8).",
					"textcolor" : [ 0.74902, 0.203922, 0.235294, 0.81 ],
					"varname" : "autohelp_top_description[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-80",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 692.0625, 43.75, 96.0, 20.0 ],
					"text" : "visit our website",
					"textcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"autofit" : 1,
					"data" : [ 56067, "", "IBkSG0fBZn....PCIgDQRA..BPA..HfDHX.....kiXE9....DLmPIQEBHf.B7g.YHB..f.PRDEDU3wI681EiijkcemmykckAqdmYG1pzBaMXzNLs8zv.FREyUXsl1uzLmdkWf4isybzrZLDrQQBrHYD1OTYJ6GrGMFYlviGaqGlLqmhfD1avROXgUP6Vrg9.16ZLIKr.tGCsRIKO1vX6AvIaLi1AvvsGJoAckLql2y9.uQVAu7FAifLHYDLt+.ZzUFYPxHICFw+647+bNHnQilMBrssKC.TV7i9+2.h3aJs6kPDqrrNVHhF..zSZy8Ihdee+bWu+QwhE6Uud8AKqiGMZzr7AW2G.ZznIbbccKc80W6cy+p...iwtOQTIXIKLXUiegHDQ8..9iA.5C.zuPgBCN3fCjEonQilTBZAEZzjBvK5BHhUHhJ4EQADwpq0CrTHDQ8AgHChn2mwX83b9.KKqtq0CLMZx4nETnQyJDeoknJh3mFFKhn557XZSBOwFDQOEDhNzBMznY0fVPgFMKIrssqBiEObeDwJqRgCJ7vfr+E.uU1G1yCh3CPDq464sGQzQy502KRKRayuONVoopgHpOhXONm+Lwe28rrr5upd80nIOfVPgFMI.sZ0pxnQip.iEOTcYcyRuUfiHNfy4OSr4t..vxviA111mvXri88520zzb2j70PxiHkE+2mv68vkkPLOQWhnYzUaLTMZVLdk08AfFMYM7cCvphUcWgHpDiwV3maeQVvKhB8A.5uIeyNweWcm09IDsUBDFSU7d+bGoCDwRv3OCqB.b7M2bC333zG.nKQzSKTnPOsIP0nI5nETnQyLv00szM2bSUNm+lHhUu4laprnhGTkq+MYQCIA9t4dW4eWR4MEDwx..0PDqQDANNNCPD6RD8TFi0UKvPilfQKnPiFITIf...lWQDDQcIh5gH99DQ8zlDL4Q3Gh9fjXCaa6xLFqBmyqHJ01JBQCQBQTL1CQbOs.CMZBGsfBMZfwgSmy4UA.d6at4lp.LeBH7DO..7LcHyW+3SnQGus4OkUwUjgBAF8AQJRJVrXGcDlzjmQaJSM4R7hBAQzaCiuAQoY9fjvqxAHhd5lZjGVElxLMfuHY7lKRE4HDS9XczKzjGQGgBM4FrssKiHtGh3adyM2rG..fXz0TK78PWupBPW1gaNnJRFhx9sJh3aFUAFBChVwK5EDQcXL1SaznQmY9f0nIiiVPglMZ7DQ..7f3VM.ZAD4aDQbpq2OGWAFHhkQDOD.3PGGmA..cPDeGs3BMapnETnYiiEQDA.PGOC20nQCcHq0bK9EXHYb28lkGLDoTqF.PslMaB..c3b96n8cglMIzdnPyFAyqHBhHcXoCg7hGJVT7mNM.f8h5iSz2QzQtPyFAZAEZxrHbq+dHhOLlhHzFmKhnETLezrYy8hqge8DWvXrGoOuTSVDsfBMYNZ1r4d..O.hwJAAQHlAsWHhEZAEKNhN74ChRpQ7PD4rGC.zVe9plrBZAEZxDH5DhODQrVLJwScdpWPzBJRVlSwEcIhdrkkU6k5AmFMKHZAEZR0XaaWSLwKqFk826huZQDICZAEKO7ItHRhj0oDQSZGsfBMoNhazH77DAQTGc3gSVzBJVMDWOWniZglzHZAEZRMHtn5CiRzHHhFPD0tPgBOVuZskGZAEqV7Yz3HEUNuuG..7HsXZMqazBJzrVw00szvgCqAiiHQ4H7P5..7XcI1sZPKnX8gHRcdo7qbDdHc3b9i1DaA7ZxFnETnYsfnt8OFhPHd0Nde8gVPQ5f3TYSDQ8HhdjNcHZV0nETnYkhsscUFi8PHZk7oNZDqYzBJRWDmnV3IDuXwhmqMnrlUAZAEZVIDU+QnyIb5BsfhzK5uSoIsgVPglkJhx973HtZpS0goMcgVPQ5mXl9v1hum0e0bzoIOgVPglkBwPHQWwE35tRNvzDKzBJxNHpPjCiX5PzBKzj3nETnIQIFBIzWPKCfVPQ1D82C0rNPO9x0jHDkKfIxk6i.c0ZnQyREQpCaaaaWU78xpp1OQyiqliiiVXglEFsfBMKDwQHg1s4ZzrZQjJwtZgEZVEnETnYtP3v7yzBIznI8ijvhGfHVS09oEVnYQPKnPSrvakN..UQTsEbzUrgFMoS7Ir3TQDKpoZ+DaeOaaa8BBzDYzlxTyLw00szKdwKJy47yBql20QjXyCsoL2rw11tLiwNCBoQyIlxomZZZd9p6HSSVDcDJzDJ1110FNb3YHhkBIhDZgDZzjAQjRi8CyiEhdawYNNNODQ7HcmqUSPnETnQIsZ0pBmycQDqDz9nERnQylAQw7lB+R8DGGmtLF6H8T9UiLZAEZlhlMatmH8FkCZez0utFMad3IrHLSWiHVkH5RGGm1FFFGoWLgFOzBJzbKhV3qKDtgK6QDsuVHgFMatHRqQGQYgelpV5MhXsgCGtmiiSOc2tUC..vV2G.ZV+355VRX9tql0fFB.XfVLgFM4CrrrZaXXrMmyOU0uW3sppLF6BGGGWWW2PmkHZ1rQKnHmSylM2a3vgW52I+gAhX0lMaFkQOtFMZ1.nd85CrrrNgy4aC.DngLEQr3Rsnh7KZAE4TrssK633bA.vSBxqDbN+TDwcDkM1sPDc1J3PTiFMoHrrr52nQi84b9tDQJMjIhX4gCGdkiiygq5iOMqezBJxgXaaeBh3kAkdChntbNeaKKqSN3fC5Il+F2BhXYaa6SVEGqZznIcgkkUWDw9A86EoA4LGGmKa0pUfUIllMOzBJxQzpUqJNNNWxXriUYxJhn9..6aZZtqeeRTrXwykiRAh3C0g1Til7G111UgPZDVdfHVgH5Raa6SzWqHefVPQN.goKOiH5xf5qDbN+TCCicT0zZpWu9.hni7uMDwRCGNTm5CMZxYHpDrIfH5nfRCBiwNd3vgWJDhnYCFsfhMbrssqJLcoxbZRD0EQbGKKqSBqdxsrrZKeACDwZ111kS3CYMZzjRwww4PYOWQD01zz7bSSycDBKl55HHhkYL1E111moiVwlKZAEan3EUBFicgJSWJ5xkGYZZtaT63cxQo..0qVQiFMadHDBLQ0fQDMvvv31qKXZZdNQzNDQcU8bvXrC0QqXyEsfhMPlUTI..5XXXrcbG1OhFWyDoDAQrp9hCZzr4i2L8QZymJGYSKKq9hAH295nUjuPKnXCCQCpJvnR..reiFM1edaWtbNWGkBMZxYHlwG07uMhndgsnjFMZzwvvHvdWgWzJzUBxlCZAEaH3uBNBXW5XXXr8hNo.srr5y47ItHBhXYccmqQylKHhSY.aUo.Ul50qOnQiF6CgDsBuJAIYNR0rNQKnXC.GGmCCpBNRhnRHSwhEOUwEGNVG9RMZ17PXDyIt1BQT63L6NhPzJN1ww4RsIuy1nETjgw00sjiiyEpV8ffDIpDxHDlLQu8GQrz0WesNJEZzrAQTLhYTIBQqnBh3k1110l6CXMqUzBJxnHLdoxg4EQz.NmWOIiJgLB2b22+1XL1w5UXnQylCQ0HlwgvhVAhXIFi41rYymni3Y1CsfhLH9JGTUc6xtDQ6XYY0dYebfHN0pTXLltYWoQyF.yiQLiJdQqHn9VA.vdZCal8PKnHCgXfdEX4fx47Skaa1KSZznQGE0a9d5xHUilrOyqQLiC95aES0Kb7Lro1v2YGzBJxHzrYy8DCzKUFuruW2tbUebwXLUkQpNJEZzjgIILhYTQz2J1gy4mp52iHdlNEHYCzBJx.XaaeFLdLiqJEGsMLL1Ipc6xjFwzHss+sgHVQarJMZxljjFwLNXYYchXznqSARFEbce.nIXbccKMb3vmDjwKIhNZU3UhYg337J+BdHh5aXXryxxTnZBFgwXKK9Q++a.Q7MU7PJqpQnEEDgpV9y39DQuu2OvXrdbNe...TrXwd5yIR23333pv6DGkDdmHJD108...NmWOMbcOMSiVPQJkVsZUgy4AY7xdLFq95JpDpPzgNmXUMbN+z0QZX1jwmXgxvXg.eZw+tTPSR1zHhUg1S7ueJ.uT3wxHr5ZhF111UYL1E92lvHl6rFNVl5ZJ9NlZaXXbjVbZ5BsfhTH1110XLlx1YcZ8KRhUUbo+U5JhhxNqJShtofqqaoqu95JvKEM7lPFSvPRfvvu8IhdeFi0CQreZRD8lHNNNS4SKNmu65RjmnRSBJcu8Hh1We8kzCZAEoLTEtQOR6g5SkPHwnMt955XJsSqVspPDUly4UDBGl6zOjWPjlkdhzpzUmFkjAgQLmvP0ogu+JVrxEA0IfYLVjmXxZVtnETjRXFeooOiw1OK7kFQm6rp+ssNWgSZBaa6xLFqBmyeSQWAr5x90zepEDLg+F...DwApJaOwu6A9E3JVU3Q...iwJw47oNekwX2mHxaEkqjHqHpzodbN+Y..c0muEOBvGTCLLL1NsHVSz+cBpj4S0K1JufVPQJfY3WhtFFFKsNdYRS.4fsqXbFmqP74ZUDw2jHpRRG4Aud.hrGDJTnvfjR7obdrWjOK8kJG.QrBQTokoGPDhe5B.3IxneR97uIgpHilF8.ksscMDQUcuyTQzTx6nETrlIrufv47ysrrVpkp0xf.Ray9I8LEIsgj.hpp9LMtH6ifUsoESRAEQ70qLLNsOdBNRrz.IZU7cEBvzBLDDvh.5aZZt855XJLDeO6IpNmHqs.rMMdk08APdFU4rzirbH7HhNUQYmcFDvjFLqh3leUYL1aSDUUbCP...79+QEYeA..zOOdCOwey8gwuGLAsZ0pxnQip.uznpUhinMwMfp4ctoiiSOhntLF6oa5hcCi.5Hlo1U5evAGzy00cGUkVJhX0gCGdQqVsRUUAWdAcDJVSDj4K2TLYzlZYjJZq3uMhX04MD8dhG..dFQTuzb99W0QnHt3yWJUlGQFRzgH5oDQcxKh4Bnhx5HlJnod1zuNZVCsfhULyv7k8LLL1cSHbcYASdEEbccKcyM2TkH5sA.1adtYkXfs8THCVQBocAEpvKxQ9DXDaged9unPgBOdS8lRA8czrVodGVY1mkizaVDsfhUH111kE0TsJwDox9KwhfpunmE7Ehv7f6wXr2F.Xu3938KfHMG8gnPVTPgLdhBEUWSrirDQTehnNaZhKTU0DY0nHFV+pHq92TVDsfhUDgUIGYgaxNuDPixY6z3JfZ1r4d..O.hoHBwpYeGXCP.gLaBBJjwSvnHBFUiigO2TDWH5+IW5eaoYiXFEDWi0MnEroq.jkOZSYtBv11tpvUxpDSrQGRNhniPDmvA4Hht..ohaJIVYimHhHkNCQucnCQzSKVrXmMonJkGP74Uaw+ca04..7fYE8BDwxHhGRDcniiSe.fGkE8bAmyOS13voYiXFEDl0bWUoTFQrVylMKs0VaUW+80kG5HTrjIn76IxU49aZqnUEoslckHG60DMsoxQ4w3sxz7VEArIFghvXdS2kHMWONKr3frtQLiBgXVyMFepkFQGghkHgIlHO4.Yhn5HhW4eahnTrRCupnme7fn1gJ8Gd6FMZjK9rJui+nWHkZjPMjqvaFUcbbNC.nCiwdTZ762BiXJ2dsG308S2TvzzrtiiCHKp.QrxvgCuv00UKpXIfNBEKIBZR4kWGnMAX.rkd5dDQi3gHh0hREZroji7jh7VDJBCwBDhbjKDeW+QoozhsIYDynfdQcqVzBJVBnC21zrpKizlMatGQzCiRzH74IhGmGRAUbPKnXZ7E4hHEsKQD.ZC.7n04BI1DMhYTPKpX0gVPQBSHSKzN4cCAopyfljqNRHZoFLNhDkivCoCmyemrPduWWnETDNygeb5v47GsNDtl17xzpjfJqTsnhjEsfhDjPhLgtjkD333bk7EdWzxHMNo0PjRiGC.zNuk1o4AsfhniWECEvBJl.uzgrpDylGLh4rHnR2WKpH4PKnHgPKlHZH50COQZyy0E1DMJriixEvgwyQjGmmpPij.sfh3SbhTlXfk8HCCi1KqnWtozQLSBBSTAQzQ5nUtXnETrfH9x5TCoF.zhIBhEMzqhoi3CgYXNtzRtqyxnETrXDUu7HNW8QEKV77jVXQdyHlyhvZ.Va58EnkMZAEK.gMWNzmXFLAXNrYdiJQHkONBWbtOQzooI20mUQKnHYvKZZvLJ+zjVXQd0HlyB80tWNvV2G.YUzmPN+bvAGzSD4faAQrpsscMU6usscUGGmKXL1TQ1vODQcA.12zzbaKKqkVHj0nItXYY02zzrtggw1bN+TQkEMEHhkXL1wCGN7Jaa6Sbccm2ImJ.v3Nho71x5cDyjf50qOvvvXWwj+cBXLlaPWKRS3niPwbfVLwhiXEaWJkW29FFF63IDHFQjnstjOWNniPwxCQiV63v7YwhDwBsQLmM5qkmrniPwbf9DvEGKKq9DQOx+1PDKe80WensscYGGG2HDQh1bNeaSSy5ZwDZxZXYY01zzbaNmWWXNyoPNhEQ84100sjbIZC..bNeipiXtnniTQxhVPQLQTMGZwDI.EKV7b4KjhH9PFicUXUtgjPh9AseZzjEPRXQWU6imvBGGmqhxM4t95qOV1qFBiX1OQNn2fXVhJDUlllHfVPQLHnRCUKlX9nd85CHhN0+1lgg0zBIzrwhPXwt..6GRDKJyXLWGGmKsssqpZeZ0pUE4p5fHpewhEOOwOn2PHLQEDQtsZ0JzoPqlwnETDQzhIVenERnIOQiFM5DgTgTgwXW333bgnwtcKpLhIh3QZSJGNAIp.QrDmyuPKpX1nMkYDPKlH4IJFtjHpKiwNR2A6VenMk45mnXdSNmedwhEO8latoJH033zelEOBxnl5Np4rQGghYfss8YZwDIGtttkhhgKA..DwT4HfVilUIVVVsMLL1IrxMkwXGNb3vqHhzkI5BhNREyOZAEgfnrqNTd6bN+bsXh3iiiyghV.bsnr+pt3nFM4QpWu9.KKqSD8wBkdg.Qrjh4ji1HlyAyPTwSVz9CxlJZAEAPHi711VVV5RuJFzpUqJh1s8YpLcIQz.Nmep7EJQDKGmRkSilMcDBKNhy4aGTEg3gHZFsWIGXafTud8ALFqtbTgPDKOb3vKzhJlFsfBEzrYy8BRLgd1bDcbccKYaaeBQzkgjdiNhgTzIEKVbpP5hH9P8Wb0nYRDcdyYUQHkPDuHnpAQyr4fCNnGiw1Uw0kpnEULMZAERH588ZwDKH111UGNb3k9MzmeHh5y47caznw9dgjUTFoSD8GDwRWe80JeNznIuSiFM5fHFXDSEkY5EMa1TGl94jYHpPmVVenET3iPFss8LLLzo4HBHhJwYBSWVV926kdCw71nq7u2xxps7JtXL1gxkFmFMZF+8sH50n8FNb3U5lzz7gX9CMUKKGQrliiyTK.MuhVPg.WW2RhQZqJwD6pqg6YiunRLkQVAXb4q4kdivddT4JcDQ8WZ0nQhqu95CUHbuipzfHt11SzQqX9vxxpKmyUcsoZNNNJulWdCsfBH75NVKlX1DknR.imBn6FEGmaYY0U1vYhoQZ0j4HVilrO111kkSoHQT+s1Zq5hxLMnNioNZEyIhHnNUzpQDOSO2OzBJ...X3vgmETSLQKlHbZ0pUkYDUh1FFFa2nQiNw44MfnTnyWoFMBTE0NuNhoupAY2vhVgiiiqNZEwCSSyyIhZKucDwyx68nhbufBaa6ST0WDzcDsYiuJ3nr7uyyzklll0mGQYVVV8UTFoUzqBPilwUhlbkSQD0UV3tkkU2vhVAhXsgCGF3bAQiZLMMqKKpvqwWkm86UtVPgnWSLUEDv475ZwDAiX7hGVEbz1vvXmEcjhGPYjdldEUZxyDjQLCpiXFgnUTlwXWn64KwCCCiiT03qPDysdTI2JnPLQ9lJjghNKW60vgTl.wJitT0Hb2mWIlqnRHinLRej+sIJiTsAnzjaQkQLiRGwbVQqPLdzuLOuB63futoYe+aGQrxM2bStzD44RAE111k4b9ExaWzELOYMbHk5waFb..7j.Fw3clGuRLKrrrNQQYjdr9hdZxiDjQLi5nIWJZESI5GQrBh3kZCaFMDcSy8U7d4d1114NOek6DT355VBQbpaJRD0S23pTiv3kWnxqIDQCHhNpQiF6urLvppF2ChntYWoI2QXFwLNOOhnUrM.vTK.vyvl4waHNObvAGzCQbp6cH5eN0VCGRqMxcBJBnhN5aXXnGuuJnYyl6IZ1WpRwQOFisqooYjVcz7RiFM5nnLRqoMRll7DQ0HlQk50qOnQiF6SDcjpnUvXrCcbbtLu5Gf3PiFM5npGUvXL27TkejqDT333bn7prEkG5Ra00YYDqPQYJN3b94FFFqrJggwX5nTnI2RPFwT02KhKlllmKZszS8cYQ6k9Js38YinGUzVd6bNO2LyOxMBJrssqppOFPDcjthNlDgeItPUukvy3kVVVwNLqKBhVeaa+aSzrqpspNFznYcQ.Fw77j5ZWGbvA8DFLrs7uCQrDiwtP2MHmMhxIcpJ+X3vgS4YuMQxEBJrssKiH9D4sqqniowqQUoZ5fRD0iHZmj13kQEhHUkQ5w4E0+ZxmDfQLGTrXwSSxWm50qOvzzrNmymZjcCv3R1V2HrlMBgYSMHwxCdRIWHnPkILA.5nqniIw11tlvuDkk+chdKQjZc1KKrrr5qnLRKqKiTMaxvXLkQVcYEgPKKq1hTfzW92IZDV4lP3OOHp7io7jWdvjla7BJbbbbUXBydas0V5J5vG111mvXroFNZ.LtQekT8VhEkhEKdth599g5KvoYSDg2ElnDNIh5trirpHEH6.pqBjJCGN7p7jYCiKGbvA8BXPhsQ2dt2nETXaaWK.SXlJt4XZ.u9KgptdIQz.DwcRSoERzrqlHTuhbTtwGNQM4OTUlnIgQLiBdUABmymJ0JHhkHhtbSeE2KBpLoon8buwl1nMVAEsZ0ph1DlgiuorZM4emXrsucZ78JwWTkM9TsMYk+ZxeHlyPk8usjzHlQEKKqSBxWELFyU2xtCl.LoYkM0E.sQJnv00sDmymJ78bN+7zzpsWm3y7kp5uDsS6iscUiPXNmuQ9kTM4ODFI+g921xvHlQkv7UgnkcmKa0zQAhno5jlh9nSs0zgzRiMRAEAz7p5YYYsRBUXZmVsZUIHyWx47SSK9kHLDCdrIxuKhXUcKCVyl.LF6LEcy2UZoZKimuJBneUTywwQaVSEXYY0WUmzbSzOEabBJDcStZ92ln8Pu+Z5PJUgsscMwHGW9hUC3bd8rTkuv47oDHpp4+nQSVh0kQLiB9FHVScrfHVUWAHpQzIMmniBuI5mhMJAE111kIhT0q6quNK2wzBhw09Tu+HLp5togKXEGrrr5KaXLDwx5FvilrLqSiXFE70uJlpk6K7GvkaZq7NIvxxR03NeixOEaTBJT0uI3b94qqFwTZBaa6yBPLQOFisxZg1IMhxHUNLv5lcklLIoEiXFEDSsTUgxuLmyuPKpXZBxOEaJopciQPg3KhZeSn.QYgppMZ2aUNONVFHxo7TkQ50WesdNenISQZyHlQAQTMUcSxRZQESSP9ofHx011t7Z3PJQYiPPgsscUUslVFik6adUhF6UME+pNo8J4HpXZZNUytRzU5JudNhznI9jFMhYTnQiFcDU.hRQEahUyvhPP9oPUptxZj4ET355FzGDmlkW4cRPPhIHhZ2nQiMpIrJQjpQG7FStI0rYSZ1HlQgCN3fdAIpPzqJpslNzRkTrXwSU3mhpYc+ek4ETb80Werhxerioo4TFFJOQXhILMM23hbikkUWhntRadO8XWVSVfztQLiBhxJcaUkUpVTwjHl2GabkRZlVPQylM2S1a.DQCxyyoCuQOtJwDbN+7MQwDdnJJEp5VpZzjlHKYDyYguxJUKpXFbvAGzKfFzWlM0GYVAEtttkTUhnDQaTgxON3qUZWU92I5wDYpU7DWDSiz192lXrAWa8bDoQS3jEMh4rPKpH5H7+UW+aSbMqSVOGQKFYVAE2byMA0Zs6tlNjV6HDSLU3xDhIZuFNjV4XXXbjh73dltLR0jFIqZDyYgVTQzgHZp4jBiwNNKl5iLofBQM6Jafo9YYU8KJpFS6.juDS.vsSizG4eahxHMSa1IMadDfQL6so78UsnhngnoKN08txho9.W2G.wEQX8uRQzI1MuFchfLfYdSLgebbbtxedoEse8cxqcLUelSsr3+.FicehH+eOph72qhJhaZLP5m+iE+XWw+ued88eUHeNJ.alWGyWpXy8K3ILZ1r4S.IAlbN+zrz3PHyInHf2zOeS2e.AgVLgZDQw5I921lZEt.v3KZe80WWADBFPDeS.FWJZqyiKUH5YH8A.5SD89..cKTnvfrnIDmWrssOQQuyYi97yfDU..rutaFG7hkQD2Iq7ciLkfBQCr5B+aiHpuggwNY8bNNOnESDNhpcop+ssIrBPaa6xLFqBmyqHDNL2QVHsgHxF87DZTrXwdaZe2V0MNHhFXXXr8l1eq9IHQEdyRnrxMMWlDvBg5YZZtyZ5PJVjYDTHNY7x7PHBiBhYywT9BPKl3kDf.ztlll6ttNlhK9h7P0MMwCQEehLdZgBE5k0uwipEBPDcTdn24nEULaBXgPYhTejYDTn5Fn40TcDzTCMqbR2pDUW7NMK5x00szM2bSUNm+lHhUCHDwKDdkoFh3.Nm+LusiHNPQ266A9e+iHRYsyC.T02+9S363tTR+2.Qz.DwtDQOkwXcyR2DJ.QtYlUflDnEUDNhRI9R4HXkE7.VlPPQqVspPDco+skWS0QHif7M17utHDvWN6aZZt8573xOsZ0pBmyqB.71IgmGHh55SrPeu+adtXjbt9WjH73yXnUA..QDWJqnS2FKDdxnKh36r0Va0MMeMAGGmKkuQZdLJqgHpn2lxLFZQvww4P4lxWVH5pYBAEp9RHjCMxipU2.fVLwrPkA3V2QyoYyl6IhBwdy6MTk8a.rDphhjTPwLdcpBSZnzEI0NcHhdJQTmzzJ5B3lD41u6pRrO.ZQEdnJ0GPJ+9dodAEp9RH.PmFMZr+Z4.ZMgXUrWn3Ke41KHEURKlfqYyl6QD81..6E2aVRD0GQruV097...H.jDQAQkm3Fk8VUqncUInHfWaOym9lHhUlmn2HDc830s3hzx4foMB45Zo9UiurIfHympOm4UV2G.gg3KgSMVxCHGtar3K7fpTxmqduXdnd85CrssOx+.XBQrzvgCOC.XoJFSbAyGBiK04RHFMM7dgwmH5o..cSSqzdUg3u49..2thLQjLphH9lQQfgHxlUPDOywwoGQziJVrXmU8EjGNb3TcDS.fSSq2XXUwAGbPuVsZsqrnBwj2zMOuXoCN3fd111m5WPunI8cL.Pp759o1HTDRN1xEtg1CctFSNTk5rkQMdKBk6d..OLloynSZyngqyHTDEl2TGQD0FQ7cVEgOVaDyYSHdCKWc8dYBp5FSq8lhTaDJt95qOjwXScSz71IWhYVxTtgNOODzlWHhNBQbhKry47y..RjaPJpg7G.RMdsPNdF..zIKXlvzJBAAc..NxmPtGLqJKQT4J0bbb5SD8X.f1Kqn.oZh2l2hx5rvxxpsssMHKp.Q7Laa6Ao0pxZYiH5p0WlW2JIIUFgBQtSuRd64M0ppJUVcoUsXDPmVctcYuXED0fHFMB+hHRylqxizdDJBh3HtvChn1DQONI8mh1HlwC807TS.W2J0U96oRAEpdyyGc3b9Qa54TNnP.BobW9l1QkX04oLRE2v5XHhFrbUFh8jjrpfB+DWwEhdswiVzKVqMh47Q.M9qb86aA0aJRaumj5l1ntttkHhpFxtrGh3k111mroNRpa0pUkfxmXV6FRoMrrr5y47IhxEhXYGGmHMMRsssq5333xXrqPDqElXBhndbNu9Vas0qYZZVW+Y25AKKq9lllmaZZtCh3NbN+b4wEsePDqvXLWGGmqVjqynMh47gggwQJZvZkFNb3TkLedAKKq9YgonbpKBEA0RoUgnT51ntIaPCHFcXRSNlmUNZaaWEQ73YUYAB+szF.3QaBQQaSHBEAgsscMQm.sZX6m3yzGUrXwyipX.sQLWLzWGTMALgZ2NsbslTkoLEgiVN+Y8Ih5nRjg3M1m333zkHpdZ4M0EgfJOzj7KQD.k..7G52xbwHsNtvdYmXD...7kip5TK0qWefiiyo..2la6fJGqXHjnOQzoqiRRTy7gHkFs8WZuph3DhXIDwiGNb3CsssijvhrkQLed4BEdkxhenDmOw0F.FC9zDQkm5g4CDwdb9siqduGWOPLR6GM5U5A.F4uWTud8AATNo0rsseZZy6.qJPDOBjFdXLF6L.fTQeYJUEghvlNjhuzeVXWXmy4mWrXwLaHECH2gwtEiSiEKTh+x4qvaJ9+UXiESrzgO9BIdgs7o...SzMGQeBPVmDlZ+XHjnKQzoapsN4M4HTHiXPrcnHpEkCZ+lUDKReFwbrfAhnJDgkPjDi1dV0U+wBe.QiEZPD9LDoAHh8BRvQPdIKsV1jqBRySQ4TifhnNYHEgo73f9BuWiuJqofU0Wblk6lowQUnBer.h6C.TlMYjGRsvGK1nO.vyVWBMBnUl6k9rPK8SQEAb5lPTwBi7jfB+Lqqy.vsUryo9q7r0sQLKT3EUIhpfHdehnxqGQCyKiEaH5Hru+XgF2oaPU9QZyPhqJB38iTw2KSMBJBXn4nL2PdqjPd9L3GhntLF6nrfJ1fZ+rxkEDAPUQTGdSHAi1fTzDhKI4wQewwwyX.zcUj9j.5W9ARdQHgG4UAEdDQgE25kq.ltsKk4FyctyvJiFAUPj8lDAUhZ4wNKHh2c5sgOMrGiWTO7skDaJyRDu6a8V+Gp9o9Te.7Y9L+P3d26GK1dt6bwpHhmEz6qogxHMUHnHfUmOyPDJJkF2vtg.QTaCCiiRqJYCpSXx47yMsrdJer3gpySjG39lzj..uujeG5gh7alTH4MiJ7w+7mFDC8I1b3SC9XQEOcYIvPU+xWE4MgDdj2ET3QDEVzSQSnKAmrsOuLiwpB.91HBUAfESg72FAf9bN79Hx6iHqO..LZzc5lLGipfJUnvGUA..7k1k6C.TBQnRb+63d26GCelOyODd8W+GB+E9K7Gc5u5u5eiSVFG0oEhx84.HcLEkSEBJjykcbCmkXnKcVXoAAjBMYZA+8biO9G7AP4d8fx85A+Tu26E4mCozGzCFm9fTYjYD96nruzzTINBM3.zgM1SFcVzTjHT76NiaRjKER3gVPwjDEgE9YQyscgBuXOX7hJ1Cfn8Z5IbfH7odhFVtBFVTFK3PjplO83+OqZjezD0CQnKiwe7KdgQp75dyChEadlbDuBi0cyebsKnPkAll2PDZaaeBh3CCp2.HZXMGkFLuB.iu3z+M+Q+Qtu969tP4d8fO9G7Ay7w3kV.wMU6kEpphYgWjMDoy49v3HxLyUsHDR0kAviii.JWW2R2byMtvL7IQd13WdnETnFQeK43Y0GRheYhRkXra1KNQgfHdWhvmxXPuQi9nd.b29w60LchuT5behfpQKEJ7A.fc..dmQitSlrcB3ybvgcurADQORdeV2dKYsJnXYXfIQomdFDxMKV2q5jFeyyGbycuashO+4gdACg.htBADcSKUHwxFggSq5KkOkCa+EuO0YVhKhxMBt84bIk66rDZAEAST8xUTJocFaXswhHXgJxc7y4sBH5lti7PRCUpPgOp5q+5++8vO7CKV8G7Ct2L1+rm3BQDvT0PztE+owWkcAVmW2ZsJnP9hU.jbFKYVgy1Sg2p5MdwMH2iCvCivMGSrv5uofHUIU4.71rWVNrJgONBNOF.nsmOQlUdH85bhxhaIh1IultC.zBJhBpLhoeB5ZMEJ7hp..O..ZuviDA0GFW8QOMqbiwkIdSfyqu1n7yd1mFdu26mBd1y9zvye9Vg7nF+d3nQeziRiQvIJoeEBXrSrnVFHIYsInHfnSj3lJYVqHUzPhpurRCBAPMwMACbkG27puJ7A+Y+y16m5+3+wSwWV1hZB.QJRpxA3sA.1KrzivAny68y+y+rmVudXgOrsggwQWe806MOlCdSFsfhvIpl5Efwo.46889ybzYm8EpfH9vv7Dw3VOM83BEntaR9BHoP066+fev8feqeq+669du2mr7reuk+HNeqNwoYasLHJ8WoY0qaRSQoXsInXYFcBYhh4VhZnIiBzXSGVC.3AAEMhad0WE5e+6C8qTAt592O2uR3EAZbjeBUbwe58tG7u6sdK3+223Mfad0Wc7iSgmZRyMMl0AZAEgipyWDCBtZ9212668SAu669Yfuy24yD3ykmHBNeTmz3pnSaDPCDqmggwtGbvubYNm8.HTyrxG..1dcD0BugK3LtmTegPh1y54StsKrtht5ZQPwpJ5DxDkteHmyOMN8re+H5SDOfMVLgR5WoB7duwa.8qLg+hzSPzD.QjK1aVQD58di2.92VsZ6+m+G8OZpHOD0FrVdAsfhfIft3XmFMZruWJ1927u40q9s+1+kffy2+3apsoUgBqJBXA.maYYcaaNOJoVhHdGDwGsr8jRbLbYbhvP.W2ZkGc00hfhUYzIB30OTiuD2gNlPHwwAkaeN.8Y.7ne8eses295OwmXh8IuGR8jFuJ33i+Aevdu969tvq+u9ecfUOCerYWOUtRYBHm34RQeZAEpIHCkOdUglCXra1CQ1wAs536e+2G9re1uGb+6+94xyqRJBZHhoNphdUPC6gAUwHuLcHFsS5i0nX3xEY7QDf3pU5fCakO9xcccKMN+guDhntqxN7kkkUaCCiskGi0d3anicQqVsBrTkH.pMBfKA.tPkXB9X+PraA.1tUyl8UHlnuggQJcfAk8nUqVUFNb3k..68mdu6A+AewuH7a7M+lv+mVVvO70e8o1ewmYWLBfKHee9QDcJIMdqIhlZXOoI+x0We8T9x5G8i9Xs+a927+kZEJ7hqPrfqrXh6d2afO2m6eO7O3ev+aPiF+qf6e+2GfwWmwcdGQ54cpWu9.DwoVPFhnh2SwAbtQaN+N6vXi1A.pshGWEDK3VnvKtZbk2r3zrYy8bbbthwXtgHlni3l+ycSXjH5T4sgHFXEHsLXkKnPDtmIdSU0aDKapWu9.KKqiPD2gHpqp8AQrJQzk111m4+jSgPhq..bk6fkb.FvA3b.fsK.v9H.ccccKQDM0.tgHpdZsCdl0vww4PhnKU4R5qt+8686724uyN..ayAnMWpCgJKrvxxpOQzi7uOHhksssOY48WflrBsZ0ph+Yovye9Vvu6u6+cvW+q+KUiwvimNr5TehFU+u6e2NG8U9JemaaczdfHVa3vggt3EMASiFM5PzjhCPDKKldvJ4Euvn2nQ2o9nQEdMNmNcbpml3Yn7hJrv11tpiiyE..OIjpMrKmy2sQiF6unQRvxxpq78xPDqsJEqtRETDRzI5tJON7yAGbPOQHb2mHpup8gwXGNb3vqd1m6yc3H.t.FKjnr+8gCPeN.mxFKj3H+k64M2byTJSE44qaR+2SdCWW2RMa17IxlyxCNmepoo4NGbvA8P.5W.f5rwBKNMLgE6+O9ebO4nTfH9P8JI0v47aOW6a+s+KAe8u9WE9c+c2AjERLdlXP6OZzc1lyMZ+0+5+xmKV.yTdk.QrBmyunYylyrOTnYZLLLNR952LF6Paa6pg+HwADcmSFMZqWinQ0EkWp+eerEVXaaW1wwwkwXANmfDGq6aZZlnF9V0hyu95qOT09tLXkJnHfnS73U4wPPznQiNFFF6v47o9.4de+uO7+z25aU5m8a+sOSN0FhFpT8BiERbh77wPbAhItHAQT+hEKtxiJylFhTbbAnv.lDQCD4Q8D4eGBvfB.bRXBK9y79u+S9Bme9D9u.QrzvgC0o9HGiHO3U+NemOC72+u+WE9s9s9rS0+CDBI1ky2ZW49FwAGbPOCCicUktUw0Fehsss9brXR850GPDEwTenFN2n8nQ2Y6vDVvX2bgvjmSgqqaIgmitJnp2P3yliLMM2dY3cl.hRwJagPqLSYttpri4AOGZa77mW8uxu4uI75u66N097mdu6AiJT3nW6+z+o.6a5wyvPZhCh42hxbRRD00vvX+nlNIBfRb.NDF2zwl54669VuE7G7E+h2VtoqZiNsNQaJyWhqqaom8r6c0+x+k6T58duepo98Dw6hHdZTqTfj7bXMiQ0n8VtpOhJL1vZAYrVh3c37QG4UtoQoC7tHUPXbPUEerp5KEqLAEALyNV6ia0fXD.m.JtAyMu5qB+AewuH7ceq2ZlCcr.Fkwy0I2ZdIppRHOVju3DlvBoO2yM2TUKnvCpzq8Z+It+I+I+WoJZX8PDNZdJ4PwhWdhppNfHpGiwpm2mmLwAutnormEVjEwElvhRk9wm+09Z+er2G6i8ho9cdrNF0Cp5KEqhtm4pLkGxdmneZTLAAP0Q.bEabYfd6MUt4UeU3O3K8kf+4+C+GBe225s..FGhRDwybbbtRNWchddQsIdt0o5XgQjaxoDSDVJNhJRoBYBQha8geH7F+l+lvu323a.+j+feP0YmaVMaJvX2bXgBu3JYwD28tWOfnQ0476ry71+Brrr5aXXrqroBA3k9pPetVzIrTeLuOmiSExqriJyaNXvG6v+I+S9xk+deOUQrZrgKMMMSjFlXbPgoxKMbXxT0JgwJQPgHuik8us0QkcDFD.kFAfKLtDPK6+2wAn8+1c2c2+e9Beg1dg81OHhkYL1EMa17I111kEaSWUGIHtttkDptqI+6Dc7xcRpzHIDVbDLVXwDOm266+8gewuw2.dKWWWJBSDUMYWtycFVgwt4BDYm42vk28t2.eguvkPiF+eseRzuBpWu9.SSy5DQSE4RDwRLF6Baa6ZK5qSdAw0AlveBKdUZM17l0qewte1O62aheyG7AeL3ry97Pyl+O.O+4aszLbYbvxxpshhL3gp12jjURJOTM7RLMMesUwqcTPz5lckCysXHScj+FejHxCmERiQY..POUsiWcCrZ9Pzu6cCHrv2N48VVu9hFWlxJ6gAP8MgQHePjWS4Ahu3jwk.5jb+6+9fnzO6znQi8S5WWw0WdhpbwqSWZzI7FOV7iVfnCWdrm+LFO2P94AYuzb26dC7ge3qbDmuUfdqaUQ.y3ikpMCV5QnP7Ejx92lb3XVWHhJwS..dhewDBW+eTA.1Q9lEVVVcMMM2gH5H4xJDfaSCR0IdcFm+J8EBlCDhItPkXBQIgtzi5CBP2ecW2c9C+q9WUtZPJCiKyzyzQqXyfwQk3EWJKl3d26GCGczuGznw+J3d26GCbNeo78YKKqtLFaWUkVJiwNzwwYtCcedBQpOl3yHw0li86e111mLb3vq7a1yO0m5CfCO72C9JekuCb26dys66ye9V.hryXrat.fmWdQ9aXQQDkhoJ88k4q4RWPgbm5hHZPwhEW6p2DQk3J4Y9fXzguCJkCcYLMMO2vvXaU49TAyUqTMuiOwDpVsV8U4zzqd85C98+xe4S+M9leyo55lL.NjCvkT.sdcMYCP7Emv4EtTV75W3KbI709ZOA9LeleH.vsF+s+x53vqzRU0v8PDqo6rlQCwMT65eaHhUiZu9v11tlnCWFX0ar6t+6Z+W6u1+26PDWJEKrpEJT3xBEdwZsuhnvKEUVldxYoJnP3f4p92FQT604MW84UBUQkXeQ2sreTdt7x8YXcaS...Q7Laa6SzWDH5XaaWSz4Kk6aICPD2YcXnWSSyy+S9I9I5+a+29uM7t+R+Rfe+z3OZEq5iKMKJOurpnR7o9Te.709ZcfuvW3O71UgJLV8ReAQhqsDjYMqMb3vKzWOY1vXrohjzrZi9dc3RQqxtrp8gHpKh3Nlll0+m9O8+wdb9V6C.s+jl1jUB.7IL1MOA.Zs7YUwhEOWNJELFaoEkhkpfh.5i3qszcP.TgCvkxSCTQTI1FkLxSTwqaapJEHdvXriGNb3kZyUMaBXJNBDQCXL1tqyxnCQ7H.F2aJ9e+q+0UFshQiiVgtMJmAnPgWrWgBSGUBNmN8u2eumz8S8olbvxgHtT8qiLlll0CnIXUQKpX1bvAGzS98ufLnossc4lMa9jY0gKEUtwTWGZzn6zYbiwZpnUrWgBezk24NCW4WSPbtp7801yq3ARZVZBJDmnKGtmNqqFBDMt+Bboei0IEUhE5hD111mDVSMAfaqFD2YMzwxyDhXhdFFFautqIewbCnK.iatYADshJ7wyEjZqoCSMyDpTgBuvE.7IS1xro9L1ncbb9eUkwp6tNlLnVVVGw4bUkBoVTQDnXwhSMr+PDen2MUEc3xyXL1UfhttK.2VV50MMM2N7J2.GnNZEXYNuvkL1Mqr1fsGqxgF1RSPwvgCqonCQtxiNgOiWNYS0Z7nqdm4MpD9IfYTxf3Nzwx6LCwD6lV7ghbXT+tu0aA+1+J+J.GfaE6HRmlqH8ZZRU77xL1GcA.xkfL0dznWYmVs9m2WUXwU0eCVUXYY0VKpX9HHCZxXryTY3R+HDRbpggw1wIMq9hVQ2IecYmspSAhXQ7SEkhkw4LKyTdHeC1dq5ZxUjhiKTX7xSK.vtQ0qDyhgCGN0LtWzu1izPGSz1Vy0jUDS.v3vnJma6O3m9mFZYa+H4FhESLh60UAR5.0o3fOPLDupC.NPLygJ6+wsrMhYTPKpX9QkAMA.1KLCWJ5vk6XYYcx7c8Gb.mu0tiaHV915ZHEHxKlGQrz0WechaXzkhfhlMat25tTQEUwwE9Gu3hTbragwsU6DAgwSqMwq8XwSsAXxgNVHkY5YNNNWlW6HdYIwDdHltgxgQ83ecW2SA.12+.GSjBjqz9pX8x3vMOYJNHh5MZznc7FhW111kk6DqqJiXFE7DUn3bOsnhYPTalhhNb41IUGtjn6bB.ztSmBD7h4cznGWDCMr9921xHsGKqHT7.++fnTQWY4dT3WB4p3nmv3kcSxWKFioJznSDds50qOvxx5Dhncf.RwBhXEFicQdqjvxhhI.31vnJq5u70We8g3XS9tqhTfbo1WEqCF6Whwc7xI1daN+U10a.OAf5Nb6p1HlyBKKq1hdUgVTQDQrvuPuAJQTOOCWlzQiZzn6zc5TfvJgXAWDewII4qUHL00qR5Ewl3BJDFcYhPorJKUTQNqk8KQaQSpJQOFDeXH+2Z2fRsikkU+FMZrOmy2MnzfHJIrqVr1Da1.wTwKyIlvCQIY02+17L6ENV.6tb.ZK8vb0kV5pDpjJ+RPzn5do3vaahHqVcx8a8XDyYwAGbPOFiMUGKUKpXRDsreWwHEuZP6mvvkIV66WMiSAB.zjoEkgGO1fvKWLLLT0nqdPP6+7vxHBE0Trskd5NDlubpRBE.ndA.VJloRkh2nXbKQ21b6vRCBiwNV0PGaSgVsZUAQ7IxaOqHl.faiRgT9QwRdmWHlIH04.Lw9HJsT8r.YIyctyvJEJ7QS4WBFazNxyfCWW2RoMiXNKDkDYPdpHWKZUT4FmHZ+10V2GO9Yzn6bDQij9bCqwXu3xkoYMUUBoHh0RRwmItfBYEOhUr2Ooecl30X7XmVkeI1AmdEhIBhVJd0INNHpcb9a0xx5jv51lpF5XaBDTGvLKIlvi.5Fe07WVvBO6H6qhZhRKUKpXIvctyvJbNdg+QNsmeIdwKLlpziSqFwbVDhQMqkWaS21110FNb3kyvvkS4+oUyQ2X3bi1L1nc76qhwo89iVpsraFiM0h6SxoPZhJnH.yX93j70PFQkbbkjXhdrwUwwRqmEfHpZ0LwdBp50sMEoAIni28PDubSnaa555Vhy4SM7ixhhI7P0m6bNehyO74qBYyZpEUjvvXCqMVLgeyWx6J6WBOR6FwbVDlnh7PpS8PzgKubVc3RNmusJ+Ospq1tW7BidiFMZG+W2GQrRgBEVZU.hnB0juOSh04LS5HTLkYLWlsHYekEpr4KWphIDiicoNq2hsZlnLzw751lQsWzm1PLA.uPgny9YUwD.bqCpa6eaplY.BeUrijYM0U.RBBiMrFhEbkZVUsGm6ZT44WYAiXNKBRTAiwNdSu671pUqJhVksxgHH.Sa3RU9eB.33U+B1taeN+UjVLIqDmiWrrDUnRLURkZ8DSPQPlwLod9kI.wDsEhIVpWHXYNvy7F5XpZ2thW6x..Owww4hrVZPt4lalZDjKZm16mkt3sJTEkBU4jGGOxympBPDQpPKpXA3khI7Cc9XyWplrjQLmEhzu0Vd6LFycSry7ZaaW1wwwULyeppZeDsJ6oLbYP9e55qudMzSfvAiidl+O6VdhJJVrXmkk4Lwj3IA..bbbNTNM.bNe6kQNHCRLwxx7k9IfYL+oKiIeovqAmMC2IedwhES8SyTQqschurlFlMGII111mHG57fN2P36my7ahXN.CV1QWyOsZ0pxnQiJwXrRbN+1KbgH9l91sx9inj3BQ9O95SD89hG2.uUZUrXwdqxyIUIlfnQ0kMeoeDQL6REdmXobcqUENNNtJ5MNaLeWy00sjvyKOLLORPD8nYccYGGmqjO+1vvX6000SEsC9ZubK7A.f6OZzc5ljuNxmijT+cmjBJj+fomoo4NI0y+sOuqQwD.rdNATjhkiCIufCHhNZcLANiBA0qIDif71qgCokBhaPck+KxMqyOFAf6xVTgv.wUHh9zhHDUNnykRZDSkwAbN+YLFqGmy6kz2rddDS.P7D.l0vwwYpAdVV1mRdHtV3TclX+DmEYsJWfXTYZQEQ6743fnj8uv+1RhqGmHBJZ0pUEhnK8uskwMKV2hIVmm74oJW9Bf9gHpKiwNJMsJjPpniiLMMyDldKNDv4HmaYYM0XT1ijTTg386p..2G.nRP4TdchWTNHhdJiw5s0Va0cduI2BHlnrXXP4+3puggwNY4a35gO+JI+4emFMZr+Z4fZAPHJNPyVJnCmyOJtBVUsHQSSyWadNNSJJT3EmA.NQDcYL0Unz7hh+t6JFWDyMIhfBUgydqs150RxuXFfXhSSx1n8rvwwYhwZ65H7XhN9laXoAgHpsggwZ2TYAERYhn1lllo156eQQ0pCmUXzmWQEBezTkwXuMQT0YMwaSqPD0ST9suSTatPyqXB.l96xB1OK5chfHHw7q6UfGGhRZeIh5RDc571TpBXQ.q8nmN8427ALFsaRIpHfHzsPo6KQDT3337ijByahdCizfXh.BQzZ6KlMa1bOhnyBKMH..mtNiBfpKZurREVZBUmqDE0+QUTgv6C6gH91IUDHDdeXfu+8eL.i8SgjH599KEbFicehtsY7jHoRQbtaGhnmVrXwNpDFuHhIDUeyDMUsjX0YoQT82pfTs3IuVkcXMkJw4hmlD23Wwp06aZZt8h97tnrLEUDPT5VnHGuvBJB3D1D6j00cZN7HMDcBUXaaexLLmTOg+J5tpOtTTa+oh2yVEnRLEmy2cVeNnPTQeF.63XaWB.nFh3Cl2aZKVImmXgtEJTXvrROl7miQ4FuhzyUA.nL.PYgnixKf3mNbN+c7twwhHlHnnlgHtSZJUgIIpLLuv2U6j1LeZDSsajLbYbHsFkB.TaTyjRTgbzTWzE78JK5ADQzaiH5+mGXZZlThIJkFDSnpqXB.nbkSqZrrrNw11ts3BFS0eJPDqfHdgiiSagZ99K6iIwJzm5BBLFKSaHr3.QTcDwIT+K52AgtpmB.TeDLtSZBi++k+i+I+Iup30WW5lW8UiyqeWhndLF6oKCiPFFhOi6p524YPTDw2jHpRDEGsGiw1yww4ru628+1NNNnT4oGcCqItY0DulBOtrQJl.fwkhdylMeSv20GDK.4I..olnE533b3vgCOlwXJWbD.iiJbwhEOOouNRwhE6Lb3vIL6on8.zNIeclGFM5N0KT3EvKEUvJw47K.f1NndqRTgH5Q96CKHhUZ0pUk4UbcRzGJjuI1FkXB.TWitySWwbYQTG5Xdcayk4whqqao.lQGoJyhtrwxxpubuDQz.YpMqGaKa6S+A+E+Kd6EJ9D+m+OW5K8s9Vg9XDMtmy4b9tMZz.EMvmiZznQmzzpPEMvsyaznw9h4Yy1hFxzT0FuL+Q+Q+jkd7iqVaxNfYzESDPGwbPwhESMeWdYwVasUhFgnH...B.IQTPTUc4NjHhXEaa609L+nYyl6IR4PfUuAQTaQ98OYYrnjfldvokYoz3doxj8ohwso6Ea1enZJfOZzn4tmTrPo7PU5NRpPGJFzW2FJl0kXh.xyTp1TghVHaX8w99DQ0WFoAI.eSjpe+ZYQbKiTwp2OFQr5Ve3GBeou02Bt22+6e6u+8di2.5Vql+GRGNm+N..Ks4ky7jxiEAg+Pd.h3Dsw+m+7sfu42be3C9fO1s66m6y8uG9E+Ee2ADQOJJqZsYylOAjV.TZIr1qBBwjlyLUbKC7e9dP6yhZ3x3P.eeMU4sF4zeLdgD2Yghxj72KVD+irPQnfH5sk949IjXBWEyli.K6tkLS0myUMfURS30sMCpSkhhgNVR2sME94np+sIJEu00mcqUBXUOS0M9DqPyq0AWE..t4UeU329W4WA9fe5e5a2uW+ceWX2+Y+y5y475as0VuViFM12xxJVCjtzNGbvA8rrrNxzzbaDwc3b94+3e7c5e1Ye9IDS7Y+reO3q7U9N9aI8WYaaeVPmOKVooTpRnt4EwD.b6bbXpuKhH9jUYKm1qCW5+7cYDQZceQj15tJNtDeess+sgHVMM0QhGM5UNZ5Y+whM5yEKJ4VPDKOucV0EJBExU2wrp29n.Avg..2FFNeyliUdt2yBJVmEQYU.IQdIU0KR.Xy1raQEYGjCv3xyBFWUDmElYE+3evG.+heiuAr0G9g92b8k0TzUlUcDJTg7pxd8W+GBGd3uWf6upxlV0mA40yMU0IMgUP+oHpFtDViUmV1HhzTIF6ilnGiPD+HNeq458LWW2R2byM+H+aaduW9bGgBQOveBUsEJTXglrnz3UP3WLw.13KdtVLx20We8T+MhHlpiNgLhbVuKmyqGTNpShgNFmymRkbdy2DAAhnpUEdYXCyHAc9iesWa2s9vObG9jeGvMuL2OXraNTNDu+0+q28zf7JD.i8KjHhEm355VRD4rx92GNmedd8bSCCiiT792dKyososs8ICGN7pvDSv47SMLL1dcVp6VVV8UDkhZoqo7LNnPAd8IG84ryJT3Ey00uEBumvKEHhy0y0bKnHoS2gn7Pm3lRL.1eUMWCTAN8P.qeZt1sCCKKq1QcniE2vcItf8DOFwJYWaWXHMQiFM5HZZS2RXMfJOCnIRoQWTQJ+xCi87BEdwdHx7YZP9.N+i1+W8W8uwIBCcNkQC8vepPPDmHsk4EiXFD0qWe.iwTEMhiS5v6aaaWyww4JFiElmtVpFtLt3uOq3wvgCqsFNTBjwkLJJ8YH4NuCSrjJsGKhGJjyG4beiVQEc3xl7Bj0w.J8rUAhTET1+1RSU1w7P850GXYYcDh3Nx2fyCDwpDQWZaaeVTTkqpDQEFOLy0deWVHdereX6CQz.Nme5Vas0qYZZVW1WDH.s4.b64edSnzkxAbpfmWF.ZxEXvncA3t889YKKq1lll6HptotpdVPDKopsumFtw05jCN3fdbNeposIpXTtOOXaaWU3Kn.aW1DQcEiT7oNeechkkUWEBUmxKcqaFM5NcIZjuTwvJMZDycdp7ijpZOlKAEIc5NDScwIpniUUNhCB4REUrplLYzIj4fCNnmHO36GTniYL1ghvFWKrmK4FliXa0y6Wv1Caa6phFoTMU+dOgDFFFybEZE.3DtuPSx.nxHeoHbyApDi8JOQt7PCpQ93KsdAJr3kOOT+MkuGunXYYchhRIs5hj5Caa6xMa17IyxvkBgDqkpKIJnpDRWjTBurXbIS+xTzL1jleTrulP.o8nZbedlKAEJR2wL63dA9bAvgRcFvdqixC0Oh19ZMoMmJZjUIIMZzniggwNxqTwCQXicEUCRU4eupTc.iM2Ut+B1tttk74j8xgrqChigXY.Tm6KMfL.NjTzPyxxTnvGIYTUpcT50DR9Epup8AQr7vgCuJMdyg0ALFS00ZONtdFP3UkyDFZT46sBwy0MMM2NsJjvihEKppunL28mgkIiFcGoT+g0F68n3ghzdTIto.adS4QUoedttAhvXYxlvLMTAE0j2PZuTQmWDoA4DNmucXoAQTlotdWnInlDzVasUJxMzqGDQk3pvlCAdfHVVtLRCc+EFU1uIM4iMoY446nMcwXikMoILGM5UhkaysrrZqJO3d30kHa1r4JsbISiDTpOt4lahbpO7Y3RkmGKEEt1K3g7JAUkPJ.vdooRH0Ob9GsurIMiqeJTE4t3ZNyXKnnUqVS0tbQDeG06cv34aBoCl8WWUzgeTjtita5NB2xxpuuvF2W0934ddwrAPYUcroEEm3fuUoMUyCBfWtBM42eQDeXbtwlrIME9oP0.fJigruIFaBy31dgEQXLJ47dugCGdYZoaHttPUpOfw27rZXOtnZ3RwLCIUX3xXhpEQVaUePDMtaeYSZFW+THDQ0UZyusp8MHhsfhQiFMkhk4ID2J7MwoqSSX5Q.lwbgJG1rDhvFuMmyOUUYlJLt0TiS37VSBRlVsZUY3vgWDzpz3b94dqPS1buHhkFNbXrx6ovjls89YgeJNYdN1SKH6aB.v59MgYzedXS0Bm4b94pDJ60j2V1sj9zNpR8AhnqJgtQ0vkHh6j1LbYbPTBoc8uMUiggzBiFcmtb9Ku1hvOEAVltAfbZOpFmE6DaAEHhxJVhsXBBf8T3ahSh6yyxfMYyXFGDqZYmf51lxPDkaS0gsscMQKMdpPL5Y.MKKqaidiPTQW+6GhXs3VlVL.NRxOEGSSmNxLAH9BI+3PsGM5Nw96cgzQLOR3WHkkxLiwN1ww4h7ZJPDo9Xh2ajSGmnCWdQTMb4lPTckWLYZZ9dnBhtiTzlvCiS+oPU0Zd80WG4GerDTHBk3DWzS1HGyB4TcH7MQpnDCEC1pZRadiyLlQEQZPpKRCRfWbPDIiZqtirzCBiW5FPJNZaXXriJCnopDj4bdbiRw.ljAlE9oHScSw6bmgUXL+87Epeb8MgGpREGiwNBfWV1zAkVODwpCGN7p4ssCm0oXwhSEURDwG1pUqJhyyuZFBIxDFtLNnxblo4nT.vz9oXbZDiVpODQkou+sgH9lQ80NtQnnphs0MNOAx8aBF.GgynF8WUnRI1lpYLiChzfLqpA4XGGmbi64EUwgxxAUbAn8MMMCr7YEWzcpxzJtu+g.zSp+TTlCPbCy4Zkw458kvX7X6aB.tspiJ6eap5HlVVVcMLL1ATDcUDwRh9vRs395m0QjC8IDx489QDJ64c1DS4opxoD.Xuzcjrta+I+bjUhwh979PQTJVNQnPVoBQTu3jeLQpNt8fiCPm0c+lvOJR2QhLry1TXVJU82sMSqtgNIP3WhKCHEG8Hh1IJ9Jhy4SsJbhnXWC4h9SQWueVTJoUi6yy5.4Tcv4zoA0uIBCUFwLrNhY850GznQi8UMrr...Fi4lFFs2qZTkNtfPDAtTSGtbYg7hJEC3uT8Bm3bi1Dwu8ZPHx1Kpo9fwXO0+OiHVJpQsKtQnXpbSF0GX.o5H0j2cwEjpJs4bezI7PXV0p92VPyFDQYld6rTXkb.thv11tpvuDkk+chgHzNQUjskkUeEkrW44owBEPojlpeuWNUGiEicmSlmmKUFwLJUcjoo44hNGaeEOmG5uToyCH7GPn+8J5vkaGVD31jPLkV66eaLFKVU+v5.N+N0mmTenZwPbNuZTdMirfBQ4hJevDY+SHppC+o5XsMzuTgp5scQZm3aZHOWS...hnchxPGaSI7w1110BpjPE4ON1BjKVr34Jd+K1MVHDf9roS8wb2wCWELZzjcY0wC7n3S.FwrWTCA+AGbPOCCCksidQoRuwaVSICWpb0nDQ870gK6uhODWqnnR+Rs8jhWBNXbkR4AqTLp5C468EIATQVPgJEJQ07MD.Ukppit3b1LrVhLUumHu8klfv11tlhnSz1xxpeTF5XdcayrrY2DhIT06MFfHN24ONn7Ve80WGaePf.bthp9HU9dNicygHxp58yyapN.PsQLCJUFAQ850GXZZtqppZBQrxlpnBgPhPMboOJsIY3xXRa4MLuSjyUIiFcmNDw69xsfGVnvKpNqGGQjbZOl4iAf3kxi4tbQSyo5..0UuRdp2SLKTL0UGXXXb6Er84d9P61lwYniklHDwD8Hh1YQ8YiHu088uMFic37rBHEU8QJzG.TIDgIppChdEkBRmEpLhoPra2444yzzrtJwHaZhJ7MV2CzvkxHJYxHsuaZHp9A4ummpq1CO37QSj5Chl80DXLVW4sEECiGYAEJVg5SCXWmfQ.bByWaAlMtAV0OputqBTozLO16ITgH5Dk8uMhnGoJ2odcaSHBCcrEY.DsJILwDFFFIVneU0GOlmI+nnpOt8lyL.pRorR5c7vKxeCrBpOOU0gnLumxHl9E6NOXZZdNmOc5W7DUj9C0c3XaaWSzprCrCWx47yEKPPtjIyTUPTBibOoH1y5h0C2sOmi25GPDwJyZVeH7MxDe1y47YV9nQRPgpF4gJELxHLE1segmCPOz2E6RQHqzL216IjQUzIJVrXneF5eniEV21zwwIU21iCRLA.PGCCicSxyQDiL4t92FhX0448GF.mx8IZmON0GohUVONbq9mUG7NiFcmtyyy0vgCmxHl..mlDetXYY0VzuJjugZEDwL4L.QzgKuJn9lhfNbNeaKKqiDqJepotYdMJEp7TWVHsG.LtgWAvKWj23HDNSCZNUYsOqWmnFghIdhh5zEUgQLWnUNrLHIZVWapDmnSHi2PGiHRY89CfmR4IG5XoEBIxDsaznw9KCAmADkhXmxBQCuJUZPShHeBT4C37Qy00DDUcTMom6dlllI1BVrrr5xXLkhJxRo+PzXp7LbYYU6inxM1sQiF66OpahuC22+9lWiRQVNsGBjMnYnWaQgOJpLqy4ijfB49O.hX2Y8XH.pHYDyNogY0gL5zcDLySzIjwxxpeiFM1OJCcrzx7THLwDySkbDUDkQ5Du+JBqZs39bIl0Gc8soGttmHoL1vZSZDS7Qyyr5..0BshqQLiBGbvA8xphJ7LbonwTUU093qCWtaP9NQwrmI2FkBPQZORymC3mQitSW+8lhwQJ74kC4gzUdC2byMUC60HpBJl3IIJ9mP1LXownSHPmtCErHQmPEQYni40sMWmoAoYyl6sNDS3Q.s+34xHqJlHoq0UVhHKQLhoXZ2Jah541HlyhYIpXY7ZtHDECW50gKEsJ61g87oxzv40nTrny5h0MxQDjwJDnOsT0FtmkOJlofh4w+DhxD81GGOEZDS.Br5NhjYS2zIIhNgJrrrNwvvX6fF5XdS+wlMa9jUsgmZ0pUEhn0lXB.tsLRU0Y9hcJKDFzrs2Oy.n15JJEiMAFd6qMQ7SmWiXBRBiRBiXNKBSTgiiSrMO6xhnZ3RuNbYLdp0do.Tm1irPSt5kb29SNQRYUmQYj10+ODTOJwinDghIdwhh+I7uRHQYhlFMhI.JZOw5lYUfiv84N5DxHp4+YMzw1CQ7xUU21z00sjnCXJ2sE6sruYkLpxaMiwNdNKizIBWs+R3d0wjkI53FjjQ644YZYZDyYwAGbPODQU9bo15tMc2rYy8higKi66WFFFsUM3vl6C3LLDQxdrKyDgB..XbjA8WFoTXQa5Y9+gYYLyYJnfwX2W5IraX6ubzI..dTZpiX5GYkkwc1jroxxJ5Dx3MzwHhNJrzfLb3vKWlCcLWW2RCGNLHwDIZ0bDUPDU0KDlmlcUeogGV0U8b9.wO5P+kIJhyW5OWEFwbVznQiNpJoTQeColhGxREQkabA.vShqgKiCAD4rJo4pzZYQgBElZQmYqghHNXxxHM3nTnJaDg8Y9LETPDMwCly4OKfcc7uexlXU+B.bxrdMVWH+2lBkm4NTMSSHhZuLuopoo44ypaaBKwgNlXUuxo9Zv5RLA.iuwkhxHs1bVFomKMmOVg4+lJwXzsqjkHd24sLQWUFwbVHJozoF5XHhmsp5Fr95vkWDlgKgwS81.MbYbPUahmwX4tnTnZ1dPDkgR6QziRgp9QADxBRBUPg3lKxgOqafGjimlnk88jqbR+kFPrZmI9aSkxy7FArJ3k9PRyqaaJFTScUsO9F5XIV21TXvuZ92FQz.Fis1DS363P0MslmnTL.78Y3pLJESGcBbttlvp1HlyBQZoZ6eaHhk3b9RsGU3Y3RQqxtlp8gHZ.QzQlllaGkodaTInQ4c1n4Nk3zU5mqtFNFV.vADAQ0KExdF49AreyLBES8BD1Wf4S1Dq5mlFM4JPNcGQp2ZrIinyCVy+17lYGqpigCN3fdlll6JF5XJec851lKZHlEC7Nkq5MMbtfnYW01+1DM6pZw84Z8DkhjI5DqKiXNKDso6INOAQr7vgCexx30yww4POCWFz9v47SMLL1dYkFHUhbAeW2Ou.h36H8ykyZypHNeqy82rqBJJExEpfbj88yrDTLgRjPLP2TdmHMGcB.TZtjbezIFNbXM4sstloIhgN1NpBsL.25uh4dniILg4TW3my4mNuC5qkADQpJiz4YZjpJJEkSliR0vXunVRDch0oQLmEFFFpp7ipIYqk2yvkHhpde..XrveggKOYY99hXwExcPwZYkdwPRwVasUW4sE0Q7cZBN+k8UiPhRQW++.hXofhJUnBJTDhwtArqSUYGo4nSnKWz.QdtHzacNcA851lQYniE2ts4M2biqhJYoaLKktkNA09immxHcUGkB+UAv7FchzfQLCCgYE2Wd6IgeJhigKMMMquBijnbycpTVpWLjDH9buq+sI2.HyBDEuTTrXwoBj.iwTdt8rDTTUZSJMjonqX5eeW54beAophs0cEeLjpHnREc8bzLIQYni40sMixJCEoLXhK.JBg9T2XHMfvLb88uMDwGNmQo31UWtL6KEL1vZ966DHhy04RoEiXFFhTSM0wz75mBaa6xMa17IqRCWFGDFFtu+skGKgTEKBMCJpZ5J9Pt6YJDOMgnBNmGOAEpbSdgBETlxCIuSjl66D..SqjTWtn.fHNQGCUTpnopz.0nQiNypaaNqgNlH5TptI0RY9bjDH9Bsb6OtzvgCicuOPQeon1Bd3EzqjuavP8GM5Nw9bozlQLCCSSyyUrh0xWe80QNJPBCWdFiwtBB3lShNbY8j1vkyApJgzxqoik0BpLweVrLZkiRQgBuhpyYk8JjxnwDnfBUcDKUFUi.nDaxKJ0Ns12I7QU++PXoxIOfJyXBo3VPdbF5XxWjCQbpF+iv2DcWZGvI.h1er7WpqE2vpK5KEs8soGlzShzBEdQU+W+XbWwLdjVMhYXXXXruhxp7vnbSFaa6SDFtTYD17ZU1hNbY6j4Hd9wvPYiIKWEkh3VRkoWvA.f9tVJVSwjHUN6DwKBEDQeZoetqp8SdJFxR4o6PrB0x92Fiwx09mPU9OYLVp9ywnNzw751l.b67Iop+8QDcpSV1GuIAADV84IJEO12+tDj7gp0Wzt3ClmthoJiXljcq0kA0qWeP.cRy.82isscMQGtLvVkMQTahncV1FtLNnpDRCpLV2jQtQOlE8QA..LZzGMgn+wFp9knXwLJMlYjiPQHU3wsW7PLQQ6GzyYJgpxaPkicySnHcG8SCkMYTvaniMqtsomK4k+8LFakLiNRBDQQQ9h3UiaXVQ.5x8EBSdhtxRpz3U3b6qV639LDfQL6mED9IRCg7mQSYhVOCWJZU1kU8bQD0EQbmUrgKiCSYNyrUGibwQ1GEyp0Tmd4t8Ih206mj8DipH3pxXlgInnpzllxPlJZjUo5U0BfZ+SjVT8uNPUmwDx.eNJiW21LrgNlpTcjUDN4AmyU0Rti874fMYIjVgBHDlw94UZkMiF8Qw9bo.73RlQ32VasUcEo93Xaa6xQ0vkhJ2X2z74mByYNwemYsNF4hRbaM0oYlz3zX4BEdgrw0mowLUJnHf7x1WdC7IiNQeLaToDQtTXyCfHN0JJxpCHMogNV2v12k07IYYikkUe4dyAhX4312CP.ZKUBoIRTJjJUzN.b29w4wKRKk70e5j183heBI0GWDUCWlg96cpNm4Z4nXMgJeTLqIxYZkwFmdhFc0DQtFQruzOOU5cTJnfHpr71jOAm.nLy2IOYgnSHLe3DeXm28OALQ9t2Lp3EQZP751lJi9jnJIVpCcrkEploB..wtYWASZNy8VTyYNto3fk89YDwX0TzDe+bhnSHtIap0HlAQ.yhkxp12zlgKiCxdsJOl1CHhU.QV.oFc0d9Mmoh43UY4GuRAExgxH.+SHeRSpeUsWe80Sobjy4o1PJtrQUC9BjxKZVFQkQD3Mi7OzwxRsMWQJ5lpLRiSIJBvRwblSXFy3VpnWe80SYLQhnGkUE3FklkWZzvkwgMgAk0hRbZM0ocH5iZ6+mkRgYW++NUBjeEUOoJFY48k2GN.Oj8x+cmBoeyXBvzkKZ+r5EqRBTkti.JGrLKQYXZ40sMsssOuXwhohV57rvzz7bGGmG5+K0hRTLx2.FAn2H.5wDoA7C+3e7GX+q8q0GDeOAQ7SCSah4JNNNW36hn8A.5+u3eQk9+N+Nzd.fdO6siyeOsZ0pBQzDosIqXDSYDlJcpIXqeHh5RDkVMaYrfHpChn+O61C.Hy34kDftfuRb1qBHxle1d29DcSmwQm...vG.uruR0Wdusssq5O6EQJkGxg5PzYLuceX.jIF62xghBQL2FcBASktirvMSiJhFiTYoMOUW9yijZnispPkQEYLVjJiTWW2RMa1bu+CUqd6m2u5e5eZ0OwO5GcAiwNVTFi0je+Sz7vp5sOLFykwXW7S7S77q7O2N97e9+PkcU2fPU4ulkLhI.2NRwuPX3xvDSLvvvX+r4MbllBEJjqq1i3zZpyFP2d+7wmGOtyYFv4qk8+CJETnvmAS5tyIMiYpdtcHwD+coHmP4FT4mDXCJcGA0Xj1ZqspG0gNVZ2s1hV9bWoMuWXcITGGmCcbbt7lat4GA.7je+29smXeK2a9zX+rm8x1Vym5S8AvW7K1y0ww4G4333Nqatnp+f.YHiX555VxwwwULRwqNq8WjdpXYh1zL48zdDmVScV.NeqNRcNSeFsdpq2T1+OLkfBU4RVQJO7eAhTu2I.3V+BHa5rtqiikz.pZlUY0p6PEWe80GpHe7GUud8AQcni40sMSySRQUqhW1Xi1110Dkp3Uxgh+lW8Ug9Ud4W4e828ci8wvye9VSHn3y9Y+ddGGdcf0m333bkss8YxMCmrrQLEsJ6SFNb3UA0Tm7LbYRLKVR4zU5mqtFNFVmrwXLyo6blSb+99SrmR+cNkfBUU3g+ZgNqltCUgfRUnpxKvXrIVAwlP0c3G4FyhHe7s8uMugN1r51lQcnisNPLMRa6eaHhUDQh3PQWXzEBwvk9ETbuu+2G9j2bC7I+jeR3S9I+jvO2O2O2T+2q+5u9s+d.lL5D..v8u+6O0qAhXYFicHiwtxwww0agKYUiXZaaWa3vgWNqNbonxMNQ0rXYSJJEHhuizOWNKYz4DfH0ZpyP36ySr7ctyvJ...Qj7WtK6+GlxTlbNuBi8RcFxWnkCvC7YFyAExHQnP0eWaR9EHtPDUEQz+O2c8czjrHBgt7MoBbdRHBs91111mfH9P4Gq3mOyww4gBiz0cYbbOuXXXbzvgC2y+wsplCkJ93e7ONX7K8KAP612tsu3G8Q.9k9RXvOpI4K+kGQ.P...7m+O+OFt289wgt+Hh0Hhp0rYyNvzS80TsQLEFtLvtaI.pMbokkUaGGmi8+3Dcn1SVZGrqPZznQmlMaNw13bdUPZk6apPD0y+0Sy1FybbOonPgaF34KpO5iX6Ai+rrKLoATK6+wMUDJDN61O8k94LW5N.PaHS+zpUqJJVUUlHRSQA4J6PUzITg2PGKrtsIiwtnYylOIMMYEE4vMx8Al6cu6Auwa7FvW8q9U+K+K+K+Ki+U97edD1y2WqeZ7ZMKuy6P29u+a825+ZnQiF3uvuvuvO90e8WG1ZqsB6gpJsaoRiX1pUqJ9LbYYU6CQTWuNbopajnHJEkyJF.NhHe+fbiOJhZqoNawKS6Ahi+rrPgBSsHb+QhRkoLK6+G7WishlY0s+9rR5NDT1+OjmMj4nQijWU3fz1ptmWZ1r4dJtfejuYqHMHdcayfDctm+gN15FWW2Rxk5sLas0VvOyOyOC7U+pe0+xekuxWA+Y+Y+YwRkJ86e6N7l9za2oCL5+x+kein7Z2oCm7+yu8aOdUZ+49y8+O689Giibcclnm6kyzjRVZEslDAqX4mpVvdDdHO6gclD+hLxpgM1UwXihi5FFuciCBhHgWLMq+Z5Ndwhc8twSOK75+X2WROZWraQ16BPpfr1w4kjtUFKCX6D2bTLr8lMZaNxXQfF6ntzZEYC4L1TYjkZ1s3879CdK125V2hrHY8aVe.CltJVj7Rxpt028b9NemG5tWd4kIUqVkTtb4goGYT.Qrcb67PtPVahHt+XrJ6pbhDsc60h6KJlh6yKk0bRAom9ZwzAGQyOAKLS...Q1veOsp1CUVAe+98Gt3TUDJr8k.gPDYjHuhh1S2PMbAW3WZR6tc3ORhGPQzZZGQCEeGHhxZmn6z3sFb21bIuzzwhxRjqQiFqzqWOWsy469tuanb4xPkJUdGenOzGxNIBQrh8mN85W+W0Ku++I+ImvmPSC.MMhiTk7vO7CS9HejOB4we7G+qc1ydVWesHDR43hHXsDbIgP1ebBtjaU1s7xqKhnbIVpE2qlHuBU80h4oxGUNp2iijebGCp1iS.kRKCfShSff.bUkxC4bOO7KIF.WP3u2kHzK.hyPkCYBICi3JPf7JG7hi9kDfpFcFhXqYQqLdooiAb21LrSChggwV..6nRTfKrvBv4O+4geseseMxC+vOLgPHu4ndsHKtHADDmI7LdK3iW+5mPn3W4WYzxt3AdfG3u+xKuLY0UWcS2hXAWDr6GkB5iK3xQ1RwYL1UsDb4j7Zqx1zIRc62jJTU9nLFKAWsCSFb3WSJJvgjEHcE6.o.PrRgkozAdOV+gMBEpVW8MrA..f.PRDEDUtHVLmIR8tiDyMgTYxLIUwxLqP0pgTsxhDJT0fql4dLiUSGiPHKMlxL8.CCiMC5UXy88f8nTpxpD3rm8rPkJUdG+r+r+rdVXk...Tt7I+c61i8vMMQzz7jsuvE71a28ce22U9HejOB4wdrG6Mt669tc73DBQiwX6E15Kf2RwOf2Rwc62vcYL1h555aLMDU4OGaq7iPHUhCQkwmPawMRpMJqoAx90TJ4ytfIWMHRDxoBV7yoMBEh4BwBV4LAcVWwIFAYhHJG0k1QzPINfxhafH1MN2hjmDnHzz65mDGu3EuXmw0zwnT5k60q29A0MCMLLz50qmxVe8ce22M73O9i+0Vd4kGaDIThmPPCcll.t+9n6GrcwXB..qrBchHv7POzCc2erO1G6c79e+ueGOlfAiE3kV4jH3x0VasY1gKkanV..Pud8pLKulwELOqiBUsnhjdoylKm38JoEGz..gWW5vTqgBYFUhguhIbiHdqJ2DRHPgIiXFEii3.Rq5mfKFSYBwAhyepqq2Je97KxXrqp5w4UCRS+toiwqNm8UsxGMMM3i8w9XuiG3Adf+9S6qOY4ksSHXLQoPLcGdM5DNdOIj27C8g9PjG6wdr2PUEgPHjspWudyo5EeLvOEb4j.dpAjIw6KsO9nF4xkywhSRKZDYbP0ByR5o833iy2Qz0LYLn7nhDiMBExqjGreiWwaD0dlGogKzD2Pg4bLOAYRiIlTWMFH2WRLWas0BrnnwcayMFmaaxa5XaMqgzd6s2tDiw1SUn3ejG4QfO7G9COcQkPFho8XLkOpePnvBOzC8P28pqt5G7Lm4LNdLBgTwOIUXI3RtygVQ0wLMBtbRfbY9lVLBJNYI4n2UNJFKQARSVvsEP7j62SH3EXLlxnyBfDgBEcYTQ8STV3uST2DJqBOF.U9OwHJMxDC32rVtTXCkTxY41l..qNtlN1zF9d2HSrvBK.O1i8XuwG3C7Als6lKBOpihNcXXWgoUtfOH8thEK9+3i9Q+nuCMMMGOleQpnd85qaI3R2NFFickoQvkSBJTnfiyO62uepPblxQ8LoWsCSHjEbqruNkDgP4iRKqxgoshB0HiPgkpUUneh19y3L3w3DZ57D52uuJwo1NBFJ9JT0WRj6.hAMVas010poi4VYlxCe+9SRHfa1rYQFi4PjfKrvBvi+3O9lOzC8PNU03r.QlAc6B3AGnTGExAunb4IS+DtABg7le3O7Glnp7RIDRkoUaJMZzXk50qa0KSb0pr4Btbyf1EccQblohRrTQ0Nj3WktWghH9pEEiC+D10QA.+S+m9q65umxkMplpCJIqehQIzz4PXakBognS.fx9RhYT7arUSGCQbIvEQKSHjRSRSGiK.SaW.aQl39tu6yU6DeZgW0QwMtg+ktCUX4kWVIoBJkN1tWpH3UtwdvfxqUS0wH3vkUC4p+xgmTjFR6A3rROzRQUwxHgjuMAPxumd3PGEHhkbyKJjEkolzA0l++h2HJocSnxha3VXomGfBw7kz9szMDIo6vMnqqat1ZqspWZ5XixsMqWudyvjLwPHl1ian1PY8S8S3FbiTAhXywciWKAWxqbixpNF9uMq5mBtbRfJM9jFR6gpPh6hW.k5fhRpLUPjBQa2q3BfKAUPkSYpBkE96jtkUaF0CfnBJlXMo+aoRm3KrS2gaf61lKNpzfX41lxoAg2fypH+bdrG6w9ZAJYB..aFbkhHT7C+g8eAQ+m3bAXFxWd4kIxlfEgPJxXLk5ovqBtDQbiZ0psXPJbWOB4zdTNhFG9F38VFSocWNBFJQALk2QZnJWPjHYC21gkVQFRnP0G5BEJzg2+NDqyz198fMHQVIiN.pbwwzPJOjchunJcGiB555aNN21Troiwc7SGcKzxkKCyRYg5YHxPniyuJegWfXy3HdzGE+VA4v4W9W9W9cHW8GDBoD2oPGBCCiM8pfKqUqlxR9MrAiwja62khSMdtY.lhaLuHLyzpgIRoh22mn8i9Q2k7DCZ.LlHTvENjlztiUSVOoXNtjQ0j2QZPPlJDxV6nXbLNX41ldooiQHDGUzwYO6YgG9ge3fI2Bxnj8Eff6smMgYJJHSMM.t26M2GHHGNDB4MezG8Q2T1mJnT55FFFkMLLpvc3RWsJ6vTvkSBTUsGPJX07xhSLo6GCSBRiQmoe+SYaNqCN3mTYJrFRnfRop8rdmBxL1bwnGg7GbynXPDCPYwMRCZIguRdMw8QHjXcGv0KMcL4OSm4LmAJWt76HrFijkVxNwEw7a..7xu7I7KdvGLb33be228ckOzG5C4X+TJcOtUYqo54gH1lPHKEABtzSfmd.47tm36+EoTan1qvLpG.9OHcA3j6Y7c9NuKMoCnD.BDJjMfCAy5IIKHSUhhwLJFGQMTTOzlQw3vmQY4crvBKzNzGESArZ5Xt41lh3QezGcSewzplDLBgYJlEjfRPlpvC+vOLQkGUnBbGtb4Z0psbbKEXxPgwnUNBFF9JRi1PsWgbkdjVR2i3hP+A+.6Uqt08Y8hnL0D96DkH9RI4hzufl3FoAGxTdkbHhchSgydbvxsMGUSG67m+7PfKBSUPLsGR5nPrjQCRAYpB+h+h+huCUVzsE3NbYUtCW1N7FYSOnTpb+uPKoO2kJRbpJg+zHT3CGohO2hBy7se6Sqo5XDITbOtb.h9zcrlouBnIuijxjLA.rs5.E0KcRDtEUsDE31UbU48e228cCm+7mOzR0gM7fBAzRHkGllnM8T3w.F3afPHu44O+4creKqxl6vksB2Q0rAWhpV4vcT3+HMpkfoDoBBEDByz5uu4MueGO91aucI5IGriFCVGz4MjMgLjHQZyxsa1rYQ4yYkWoWRBDBwQkIb9yedHzS0gEDiPgcBERGl+3PlSB9.efO.QtsmSHjhEJT3pIoHTYAU5n.jLgtDJLk1V4hVSaHspeDBgZJt8st0cY6w62uewQkxiWGjHTPRdQnnr3FoAgHNMvk5f1LjGF9JTYTNLFKoc9I.f5dQxO0O0OU3UUGpfTnGrpzC4J7Hpvi9nO5WSdeGd3gSUuRIN.4nqkFtIjBwll3+L4ELplmURF86e51ha+C+gNc8+QpgB4J7veFVQJLi5APbAwQEuOgnr3FHhcSpelN7vCWWNBRKszRNtgYXBxhKZmLCuSf0sa3WgGpvC7.OveeEFd0kRvV7rs7tmFL3JXvhREQR82lYFI3yKkvIjkjiPAkRsEgBMwGTQN1M84QVFBOTVbizPjZTT0JIxnS...DBwlcKe228cGNFX03fXZO3U5gXAeD1BxTFx1xMgPJppQwkPfo7NR5UEQZMz+iCpzoWZw5wEsf6acK6QnfwX1zPgl8mH1AF3Y2VvLHFfAITTtNlQw3HFBynd.3CPSbijZUqznQiUju1SknCiDTbzKppXwnKBE.LnLRUnkhDYuvP0MgR5lAUZMz+y4X3uouxqbuNdPu1KO..fDmCSJWtNyqtjohUym3ghPBaFACiYFHh15TpKrvBvYO6YilJ6PFJ5oGhMErnNBE.nLJEkSpkborlCj8FnDHLk2QROpKy6.QxvXT9Vukyx2dbDJDKYzL1lIWnItQRc07VvkaXXFxCC+B1BQullVzUYGxXrQnHjFGi.u22668CJuOE1wdRA1liMouP.UZZZdwKJlGJY127MmPBET6hnIwli5Lj5fl7NRh9KhggQYYwX9fO3C9FQ03wAtGgp7qSGnSGlsZFMNPnnXwh+OjabX..OgpiMtCED80hhwQF7EXF0Cff.hMIrW4UNiziQOGE.WCCkYPNvBCHGVbYQBMGgzloVoE0C.eBkE2XgEV.dnG5gbVKVQEDS4Q2tVE5gvCG9dPgJnJsGQyHY1fhqKS7oGPg+ZTNJFGYH3Ah3fp7PUXnpoqqIsqD+MimWEITZyTq.movoczLLlMHac3xkAYF7FdWuq20lx6yEuWIVCE91PLHFPyLlKmyMsBJ098PcT5nd8EJA1kQyP5EoBG2Sdkz2+86zNaiTH4bU23o631CEo39tu66JJ5uGkifghuijp.SyfCjJly53iyaizqr4VMIU4QFxPr.prI9nZrLsP0JnUsR6nDxlaUWySVSQTZpUpfbzcRhc3QWzAjVHOL7UHmFmjtPS8Jj0Cy7hGbLJBEZg0fHCAGRq5iQBxNxWR.Zx6HR5pnoDHKLSDw4hIvi6PtyaBY2WIUCWITvD9gmAmnryLjrfJ8wjTsnZAjFxsrl3FY5mX1v8du2qspiQ1rvRJ.QTN0xZQw3HCYvcbRIw9c+t1M2pTaJOTER4BEJj3BMdFbBEcYzD2uqxgjWgF.hePtLOhQ3ttq65+W48kPMQI4yk0hhAQFxfaPziMdq2JusGK0RnPERhs13LLdjDqdGYWbUgWJDOP4xm7223j60cgKDuzPgpzEMuXhRYHCwAPHjxyUDJxPFhQPKpG.ocPozLBEYHCgHxHTjgLDAPNG+uq206JRaW4oAHGkmTPuvHCYHQARiFMPUOv4+BeA37W6Z...78N6Ygq8I9Dg5.KCYXdBO9i+3esXQKKWBX4xnUiA6eC8SA+aHeJ...9TeJJb4KGObJSKbsqcM7Ue0WMpGFYHCoZb0q9KA27lC7LmG+w2Gd7G++4vGKKBEYHCYHCYHCYXlQFghLjgLjgLjgLLyHiPQFxPFxPFxPFlYbJFisLgPJQHjsDef+OtwMZA.TA..J9puZGFisQDL9lZn5yDiwVNpFOQERieOPoz8D2FQbijl8aK+YHCyN50qmssQDagH9zQzvYp.gP1RzmURheFDAgPdRBgTwZaDwNHhIp6kLMHM+49u4u4d1BboS3dJcc81FFF.gXWeUm4+8+6W15uy+FuQWW7Y9XKT8YJo8YvOPZ76gFMZXaaDwNIsOS0qW2TrRO99e+u+uPzMZRG3V25V11lPHOSsZ0ZGMiloC0qW2lmpfH9xIsysEgggQYo4eRb2KYZPZ9yMk9w6RbQN1Yo7HCYHZfYTO.R6HIZ3YYHCIYLWQnnYylYFcSFhkPd00wFvKYT...N2IQ475WWY0lGY30dsW6xx6KWtbYDJxPFBIfH1N0RnPU3kN7vCyL5lT.TnWhxQw3XVfb6M9niNJpFJdGEiu7wO5ni9GJuuKdwKlnzUCGxyQYFEChLjA2fXpZui6vttkbkPAU3DYZBbB6L3NLLLzh5wvLhzvJOME2HyPllMHqAEwFXTRBDBQl0lYTLNxPFbGDMq+587d9g1djQEgByfXnjgvEtHDHsPdXjAmvTdGpBaeF7FTjxHyHXXjAIH2UcgreWR0H0lxiLjdgbJOHDxEhpwxzBUD899e+u+lg+HwcfGbfMgRTT6jEO+xub7RCExQ3QNkRIAXXXTVwtMC4gguB4tpKh3K61wllf7bRIsxZeZgmITf.DeSfZFl2vqG0C.+.HhsE296889dQzHwEXZZayy8jkb6ghT7Zu1qcYEZPocDLT7cnqqaF0igL3KHULm0oOcOaZ74NtC6W2QAPsZnqaXXJsqzffF0h5APT.DQa+9JZbNITXJsch7yi7pVxzQwzAUQ1IIVy+xWWJecaBEYKDMEAFiZ62yG3ArmpQJ.tpFZs.aTERPdEfPJ3yzTBa+9JGFxDHLE2PgP1RJ3YD23niNBdoW5ktcTMXbfNBm1Trnih7vzDiE483l27l11Vw08IBn35xDeXxkIIQozD+moLnFDBo6HS4AytZ5SjqBLCoRXJuCWx+brF555skWE5K+xu7cEUiGG30EhRaoRPoR1aW4llQOehtc69yoPPlOipiMtC47tSHjzPDJrg4HyFSKpG.AAXrSp3yybl2P5wX2XbZnXHaRVVnqRxvTbCEJuNQAWxqrVHOL7Krq3Flll.h3cFUCFan6nm6eLObnfuy2467WHuODwcUcrI.XaNVFicinZf3GHETd5SMD8pANZG9ihfEm4LNCl5jTkGOn+MTBGHyvmPHItOC9AjUVcJHkGpTMsVTLNlUPHDGo83l27l+3nZ7XCho7nbY...N24NIHE2HFb6NUo6HoJjwTX5Azj2QRTaKY3DPH3vEiJKHS.DHTHaDL7StEK8JMeezEvPACesnXbDCgVTO.lUPHDSosSbkNJ..r1Zqsq70dO+y+7QznQBJBAgnNJ51MZS4wK9huHd6aaeURI0Ny41ausiTJKeNdRCTJMwuvkL3.C+M8AdfeniGTLBElhOfhUwp4iCpLDtns3FJBGWhCJHKlX03i7MAu8suM7Juxq7mGUimgPLBEm6bh+G.PzGgBEQmnagBERjo6ne+9NN+MgZc3CAiwjqZkD8mGuBU54pPgBohO6DxIyy5v1sozNiLkGTgaDQSGDJzh5APbAof7a1VbCBgTLo9YpPgBWUVbl6u+9QZ6LW1TqrBMQwhmjxinzbqdkW4U9yUXlUOU0pUiAJ6XpfMcMkTqTEIbORamT+sYlQB97RIbRTmjscaFiMxp73d.oS.vj2p.aKtQZXk4SCRi1usJF+TJMoc9I...Gd3gEAoq0d0W8Ui1RHUx4pHKuLA..tvEb8PBU7bO2yohvUqvdb3WfPHkE2NMrZdE9pQh+yjWPZMUO4xcbYwsu26cDhxTgcFWh3rNn07ugWFBSj1L2ppUq1UV6ALFKQoihlMaVzvvXSBgruJxteyu42L5JgTIOnPwexOLVnGlhW3EdAUZmnURULl.n75wXfjWmYnIscpvsHGGRqo5AQll31xkMZtb4rEgBk+XyrW5nIsaBYJuijneE3SHsYtU.3LBTkilgwjCCCiJ8506.JkdY2Llqae6aC+k+k+kQSdEdYgBCpTIg+T1KJBqAz.fHdmtHZ0ULLL1LbGM9CbYNo1g7vv2w7PoS5QjJR2AhTMq+9rm0YaB3hW7hiVCEbXJ72IJ+KHIuhk..lhajTqJBQH2.nHDRolMaFqIJYXXTtd85GPozldwgOe9m+4iltPpXDJJYecDQYoi9k+xe4erh91APHjhTJ8x0qW+fD3hFdBwMPD6lzm6RUUqnpEOjFgrO+jVLnLBAGdOiScpiMUcLCITHWyyBq1SbJijVDJT4G9ZQw3Hpght7mVTLN7YzVdGGczQkC+gw3AmHwdTJcO2zxChXaFicU48+bO2ysYna1UsaexeeN6qiPjew0ud3E.kW7EeQzbLgDgPHZTJcu50quWRQjtJhrVhrRUDAhnl79R5UshWgbzeS5FTlEDm25m7mzQJG6Bf.gB2rDUpPnxSnU5QlNPFf1hajFDnptttorNJPDeBWN7HAFFFZ0qWuImHQYUGChnIiwpVqVsk0002PVg+25V2BZ2tcnY1UNpvCMMaa9fOX3WoGu1q8ZW9q+0+5N1ua4mlPHkoT5AFFFaFmiZUylMKpP7hItVutLRq5HviPKpG.9Ovh.Pzr1589d+9lRGPG.FiSYxY3aO26vId4cRDyqtkIjd0SRaosKGAiAGvRvkTJ8.BgTQ0wfH1EQbiZ0psnttdKg8WUNxZ27l2DdwW7ECm6d2w9b+VU3gEjqzie3Or+KDjCGDw674dtmaS4TcvXrqVqVskXLliuur.kRubud81uQiFqDjiwoEGd3gpFWsC6wgeCEg82LhFJgNRiZGIWt21FAwEW7Gnjf3PBEtUZgD.LSxMILEr80hhwQTCU4jMoWoG.3z5pIDhlp72Flnd85qaI3R2NFFick74yuXsZ0bjhCdjW1Pd+sa2NbzSw0EtjojyuJ+.e.7aIt8y8bj2ePNb9BeguvOVtAfgH1oPgBWA..z00akOe9EUktH.FNA+N0qWeun9bCYPoTY8SzIoqeB...Qz12yokv9ONjTRy1jBwlBF.n467c9FxWGYBf26kGsG9BCPRWLeZQ8.HpfByxIQIxVUXgEVns7952u+SF9iD.ZznwJ0qW+.BgrkaBtDQrEiwVTWWeyQY1M555sPDaIu+m8Ye1MCbREiPPl..v8du49.hYAIHEl4d6sGpv.q5Rozphe+UsZ0t555aPHjkbyTnHDRYDw8MLL1JtjFDDwxRa2NZFI9G3owQSZ2sC+QRj.M4cjF5eIh8vCUouxRidTocZJcbk4+eRVXlsE2HMncfoEJNQHo8aoCvuohMQrQHjPM71VBtD.XmwH3xkqUqVUutBzZ0pUU92riN5nfmTgnfLuf50ObgKbRVPBJgYt2d6gx1qM..PHjptIvuKdwK1oVsZKC.rph4y...fRoq2qWuCLLLp3mi2IEMZzXEYhm4xkKQ1KRDwgGdnp4ULC6wQT.E5gIkTgG1Rk70AIhSVUxhbDJLU8hIaA2XBZU9pJUo3VXOCQXasjogTd...LFKRR6gWEbI.vpbAW1dReOxmO+xx2XLHIUf6smc1AJhPA.1KczffPgajIXLV00VaswVEDqs1Z6lOe9kXL1UT837xLsIuZPJO6i3IGxBHFQzLkTIDkE2HMTFrdEJ72mD+umm9z8JIZ41DBoi7BmrV3iMBEx0KqkvZHwTgu4En5Bz986GKB2YXib4x436hzfvLU0PnBxzdLoBtzK2.zMTsZ0tTJcU4U5XQpv2ahXh5mnXQfrzRDUGlbfK7KGyDQ7N+ReoujRxDb2vrkWes3oAYSFis3nRCBuLSaFloAgmVfJh6CQLwWtn.nTPlsingRnCE96iYTLN7Szuu8HY+e8+5umqjjrQnPV3LhrsjbLyDkNJFQpblqvEu3E6j1rfa.B2zdXXXr4rH3xoAW7hWrCkRW1ERE+BuvK7B9WHBD0OQ4xtdXkJQIh1v808gBcra2t+b+Q+Q+Q+XUdMAhXqZ0pUcZdc000MqUq1xLFyQzdr.gPpzqWuCpWu95Sy6wjBUU2QZHcG.3TWHyKBxjCajRU3+OINPHzg2uGQVaUozxJ5qiLBEf8br2V3uKOqCxPFlhaLGW5n.HEBtzfiYBf5zd3mkJnggQEtCW5pUY6UAWNMvMRE..v23a7MfuzW5Kg9h4Wsq.uLWzOwIOr+k1iW5kdoauyN67WHWMG.LajIDgttd6Z0psHiwthpuGIDRQBgrUX31lDBwVDzRKo6vvvPSw0GsihwRT.4EnIaXjISfCmGEQx0GUyOSVTlx2ronvA9LB+chRGEYkN5IP96B4USjTAupHjuIwLm1CAGtr4nDbIgPVZRDb4z.dDlVRkJqMMMgO2m6y8imkTf3P+DiHBE.XmPwy7LSGgBDw67q+0+53W4q7UtKUVpMOsQyLYBQnqquI+6wVpdbK21rQiF6DDkAH+ltkk18S42uOQDJKuizPUN3EnR2VIc+2PV+DTJzdTlVlMBEiR.iJzQQrznXTA4HujjZhTA.ZKtAgPJlVDophaPrxzdCACCCsFMZriGb3xkqUq1xg0pK000M4B0rs7ic6aea3Ye1m8WXu81a5hVwyHDjGMMW0OgEjCfQ61SlNJdoW5kt8m6y849wequ02xwigH1k6dn9RZijAOMHU4oAwse6VgPH662McLBg3HcYoE8SHGwy4IGxLMZ2386KN2Gqa+9mtM.v8HcXCu+pMBEiS.iLg7TmjzQgpSpSqFPx3fpUKvXrxg+HIPfpU4UYRdA3BtbKJkd.3BoYga1sXTr5qpUq1kqI.k2r8l27lPqVs9wSbmJUrbQGSzI.XfNJD8iBuFkhW60dsKesqcM7q7U9J2kbaHGfAD0nT5xSh.LmVvSCxRHha3VZPrZ5X9QJz3B+T90Y2TTUPTVbizfuZ3UjRsa7gUhDhCVL5nrJdGFa0nDsGcP8mZ82IlHT3lKfFxCiXCjuHOsniBtCS1VbeDB4RdU89BBtTov73DItR974WLLtY23ftt9Fv.+VvwMBO5nifm+4ed3y9Y+r3K9hu3XiXAdvAnMAYNF8SbxgcRPL9S9SFMghW60dsKu2d6g6ryNaJaVUBX274yuTXuxtZ0pc074yu3nRCBvcayYYwH850qhrFCXLVpHcG7T4nItOJkl36KIdEoO6FGKRHzxB6v52RM2dFpbJSaWHKUWs1BKGlfHUjUoGmfzpNJ...DQaJkmPHEcoeILDdUvkHhKEDBtbVvZqs1tHhq51ie6aeanc61PqVs9we8u9WG61s6OmxCTL5D..rm3I988x6+uxuxIDJLMAvzDcvp3EewWDu10tFtyN6ropxAEfgKjY00VasUipue4Q9o53bayYroicIwMPDMSKZLPUkUoxIaSqHsY23T5Q198jw5uK.itWknhPgo3Fhqdk2WOF93Lgvgj.fo3FxrImyPawMHDRwzfeT.vPwYZJtOU4rFfgBtb+3ffKmE31mOQbzQGAequ02B97e9O+ewe3e3eH9BuvKXmbgn9IJWFxcu26GyKu2qrB0lNKrR6wK8Ruzs2au8vlMahsa2FFQDIFh3xMerbaSuzzwlD21zvvnhBCARowakDgB8SzNNQ9NnghnyjnS4g8xEE6.vcXpRuchZuTUJOjqaVMosEiRQRJBExqJOUHDwoA555sULQYRhb3Hg7jzDBQSbhetCWtGWvkJOO.QrSXK3xoA7aRUVbeHhN7aDQbqacK3a7M9Fvm+y+4+K9re1OK90+heQzV4h9DS1oBOwSbBmh+S+m96fFMZfekuxW4tt4MuInpxMTAdjjB9Fe1D.uzzwrbaSuHrYYhebGjrkOMbiCv18CRCsgcuBUKHiwXw14M7FNobQIjAKBcbBO8TJdUZC.L7DeGrt.3oA.Vm+2EQ.VgHkJj3HjYKRHDslMaVbdhAsH3tWmvILomJeoPgB61qWOaMnKBgb4lMaZs+Jt8bQDMQDuRRXh9lMaVrWudaItOtCctZgBE51qWuJ..WZT8ulae6aC89xeYa66KbpSAW6ZWCA.f6+9uekOm23MdC...d0W8Ugu4275..OJ...+0+02EbqacWvYNya353lm9nmlPH1hLDkRW2vv3ohSQBhO+vFFFFOEe7VV9XDZ5XWsPgBWQ0bJtDchTg1I.XPeIQde4xkK1eeA+Bp5gGwoyimTjK2wq.ffsQPYOc+9CDdJkdRbHjiFriHTLtdeAAfNIwzdnhM0hE8V...H.jDQAQknKMwl4BnvHnJkVp7kpUq1UdxZBgnczQG8iFkUYyEb4RIAxD..vgGdnCMefH9T555lb8.bUtQNUcTpsWSPLl2587dfWcgEfW8UeU3Ue0WEd9m+4c7uadyaN7wA.fycN6A07F2vouww+98pLFaQd5iZiH5veIHDRyI7qgPAVtsI3glNlJ21TUzIJTnPfTRrQAXLlb5N5FmirW..4Tnmz+rKbecz73iy2A.klBoo3FNHTn5j.Eg4Hwk1CdE.HSVpbTLVhIns7NB6tzYPhBEJbUu1o+PDawqbiXkfKGE1d6sKIWMJbA9so7wpqq2hqIfE4kG4vqwW3MeSaDJt4i7HS7X4NtiirQp3a9MeeVimt7plX0Z0p8N0002PbUabREsEesHDR43rddDa5XiwsM225ygaQmHobtlWfh4NlahNAGtVJkISfh+dJ9aolsiR5yopTd.HhcDCgCu9ZG9hlTS6ALf0XYqMlmElotttY850s86LWTUohUMc3gGVhanYtpDeDw1HhwVwVNJvXrsHD69NkpU7KB9myqB.b0lMaV7niNp7O2y7LWBDtlvzktK53v4N2KOLxDuxqbF3O+O+rq9686s7XmS.QrJgPNPbeDBYK.fklpARH.NQfMMLLZwGqNHhSHjRDBYu50q2R9wSaQmX6s2tj7hNIDxy3xgm5.+ZIaW3jjEjIk1qhc2wbP5N.PYpwMs8bU8BJW+rNpuVmo8Hv5ri9IxDloCH2LhVIL63hAAjDbolpiQTvkIQxDpDhILvbjZ60WipUq1cs0Va2+Oa2Vz35Z+5uy24xLF6J7Uf6nhY3Qcns0wvXrpLFa4e3O7NVD.1vUb+49b+BdxHK3QNrk393oeqhW+rDUPWW2bs0Va0w0zwTkVpzTzIT0YemkNraRCpRcdxVPlDAyrB6XktCWRIto3FJiPAiwtAkRGxpVkxNoCbkvs3+8JH.EIBVvYLEsAIAmZXXnkDuohe.Dwc4qvZH3d1PqnYDM8fapNWdTBtT.cRp09+HDh4FS5qEue7HZbcOM+6k1V6yvvXSo7+2gqk.GHWti2ENwYRWA.vSio74yuQud8VQRDsa0rYycSB23k+c1h7uqtjadYB.tmVpjLxR2gC2A0L4dOk2RiPnB+dZyWezjOZ44QUFgBEUDgpUxKeRSkQMLiCnPgBpXMVNrGGwEvWcn7u0IhnMYAtUYuIgP12ijI.BgTINmm9QgQIDyI80hIXxRrAKFXVuQfvjODsAJEe7vEQzV7vCOzg3FiyPWWeyQ41l.LrK3FHMcrn.au81kjiDnrfuS6P1+MHDRhM5DDxopHtskYVwQYwGSUT47TJO.vYc1xM4pguYLIGfKNB9DWx+XO2piBNjcVxxIkI6LLLpvsJaWc3RtGB3vIIkiLSR.tIDyYHe7UD96cm0HLNnwAcxjLHhdlbJuCfZJtOJkd4jx4hVvxsMYL1nLrpgMcrjdJFUktiBEJLWEgBE9.ShUPlT5IxW.Q1t.bGlm7XNrVbGDmTRnvkx8QSwSVtklW1KC5HFxqHubDMNhEPUWNLtWsGbGt7.tCW51Dx6xXrE0002faO0sDePdd52LvGr9HXLlCRPDBYioIs.H.UnBBVk5TOMSEXrSdcFD5z2RyqOWBg3HEIdwEPianYylEGWj9rZ5X850ae+noiEUPNpfHhsRBooxufJCMKo1Tv3dOgl01DBw1bBdwZwURnf+jaKsKGqjm.PKIwYF6iRgL6QBgTJouJgYApR6ADSEY61aucIOH3x1LFa40VasUESCP974czMIoT5kSJst8FMZrhhUB0dZE+lnPpY.zgnnLhmFf3a2Rba4PnNJvI9YabjDSOEOsTZh6ysax3WMcrn.7yIsM247T0c.f5N0bRUeV1inHZ1u+osM2hWrV7QQnvK5n..gU1vEmolKGWbAsk2wQGcT4veXDefh7WWJNciVdkazDQbe2hnDhnIukhurpKn4qZxQXnYLVrzHkDQylMKhH5H5DiqLQcCH.knhkOs5199Th6vDfShFDkhSzhLT0aKRRQovvvnrpzRkOe9k8XSGaqjxBbPDeBos6NOUcG.nt+kDQCkYD1EioXjFAv6VKtqDJ..rENC2lHmJUQ.w8nTvWQto39jc4s4MnJmmLFKx+czKBtzxgKqUq1Xao30pU6pJVAbrO0GGd3gqqP3aWYZURd.HFSYHLYDs3f5Z2afa1UsD2GWWOd90Hp.OUG6HueDwpUqVsqTSGyT0qgkaaF2+7x+rVQbeiRLpoUH2olSp5mHWtSI0EbOkMcY4UqE2UBE4xkyA6CUqZkKNyVB6pBNByDJlf1haLuqiBtXUaIs6H0SJpWu95dQvkVNboWecQDczAI4h+q7rMhCFXXXnQoTYaadpEhIBfF0tXLa42k6c+9mtsXDNID5DEgADQGtPYRHJEGczQNzzCiwtpbDy3McrkbS3lb8U34lNVT.dehwFxkKmunCmjB3U3h7bSsihwxrArH.XEgsaA.QdNAOYs3tRnPkvL62uuxSto1S6QQF2EMiqPkNJRZ4uzuAhnb0dTj6IEgJZznwJ0qW+.BgrkaDIPDaYI3xIU.XbV0pBqdy3XnlU0aKlVgXBfyHH5uo6v16jvqKQKWtiK60mIOJhN5EKw4HIw6eGxNhoYgBETRZnZ0pc0002jaG5sUcLVMcr50qGGO2TZEsXm4rd2AzueeGNfZRT+DDxautjyXpZNA4HTnLRLiJkGNxGjb9hFte.ZyryLKVJpOK3RYMUNrGGwIvC0ro39HDRnk1CdkarG.vNiSvk7lKk4z9dUqVsqBRg4m27vhU5ovuEhIOxgUr1lMH5DlyxXzMvX4aIUBoSTDF38hESw8QHjKECuwp0JUUpwkwQ7yKMcLBgTwslNVT.CCixo4NmpWgB+mncDMTlIHpyIDYssbFSKvSukmrV7wQnP9I4Z32nBq5iWBoUF0qcTBU9QgajklyfCwYFzoBvRvk7J2P46Eeh1UcSvkSCVXgEbj5C.fUhKqB1uEhI..v.XcoREMPuIfTIjVdRhRA+ZTaqtmPHNbIznFMa1rHiwbnaBtFWZ60Wm0Vasc4cFVO2zwhJPoT4nSzcdy6I32jsr39Rh5mPtucPHDGQTaRrV7QRn.bJLSWITviRg4v2PAKtNNBEgYLwVK39ExmOeK48ETNmokfKoT5AiRvkHhaTqVsE8a0iyugkCCuhRoWNN3K.9sPL4QmPTLlsIAbKVdfvtNo+dLoQoPWWukBh+UhS5JnWudNhnFhX6o0ds4F70RfKBkkPHknT5d0qWuYTjlV96oCq1ddx6I.PckApxSeh6PTeSHxZOvb5bfxha3lfLAX7DJb7hOJ1wIonT.BlxE.CVAPbZhpn.pDmI2G.z7y2GQAW51wvXrqjOe9E4omHP.OMONLSIDwlQ44B9sPLAPYzIFkSN5SfzkwHCiBxjFkB..P0uOpL3qn.0qWuohUo1Me97NHpNIXBZ5X6GAQTyQZPUUpuocnnjYSb8uiAQmfnYsMgPTFwxII0NijPAWbTxLOK61wqvnqhsQofeyDae1TYiryafRopNophe7ZOgBtbyvXUOtnmhhLFamnJe89sPLcI5Dsm9Q3D7dO6QonM372mxQcX+qWu95phrFkRW1uNuUWWucsZ0VDQzgorAvItsY850OHL99vkREscR6Fo9DJKsc6HXLLSvd0W4zHqDvXcHSKLtHT3fMx3zZfhnTDKDRjJn3yV4nYjDevEu3E6nPLtyjX3BSAWNMfqmB4Pqq0qWu8BaRE9sPLAHphNgEl8nTvXLUVxcjIfVd6i2QTRXLV0fnRGpUq1UGUSGiPHZ7zfDntsIOMb1tdXdL5DpZHZIMGBkPNdSwnS..nTaVSZowNVBEJXiLxPAyiRwvKpX.b43puTH2U7xJezAPNzWSamezvvPqQiF6D1BtbRgkdJT38Ak50qmCA2ETHHDhI24ZijnSLbLL6QovT1yFHDhVTT0C7FzlCxLHhsFmwpMKPnoisrGbay.ooiIW0W7v7qbrjlgb4hBv.Q0FEikoCXQ4J6vEsSLwVK9XIT.NMApwp0.J.aH72wVeoPkxji6MFqv.7dpfo39ljnTvEb4VTJ8.vEwtxc3xpAgfKmFnqqaRozkUPpnb850CkUC62BwDfAD5khNgiU6G7vYTJlD2yDfgkQpbX+ubXFAos2d6RLFaOEOzt0pUapI8MIfmFDK21TYpUBhlNFOpLy8Qm...HDxSHsqHe9qIAx9NgpJ6P.1LzpwYs3ikPgJ1HpXsHBE9Rwkhi83CWZm4xmrLWBUkrmWL5JCCiM4BtTIIRKqxl6vks7ogqu.d5dTEd8JAMohfPHl7d1QEqs49NQjX9PHd5ME8khI08LU0KV3mSFJ5zxhLghap1YgEVHTHSHBtaatHiwTd9gXSGyODXrrSkxiNQqY80MoACCCM4pcTNR2wa7VZTJwKU1gEJKtw3JMVuDgBOavURuvhZonXLVflxNDY43n44D1fWxdlh6aT1erggQEdKE2UqxFQrEh3RgkfKmFnqq2hwXNtAQPSpvuEhI..v.vV5SBWsS3DHJl1Bh1f735cv6EKlh6iRoqGzoobTjIxmOuuIByIEb21biw0zwPD2eVZ5X7nSnItu43nS3XQUIIO3HWtScY6a6bATVfSdRSbetYnUCebuLHjYkH2PTTAdTJZI7FUAigtQopZGNJrb53HTDkBG1erkfKoTZyQI3RBgrTTH3xoAgMohfPHlH.qH1QQY.bkfxUL8JXr717UhA4wEmnaxoROITJMvJizQPlvLJISHBqlNFLB21bVZ5XJhNQ24wnSvgsJADQrSb3b.ufAhgVrJcvVxthoDJKuiEVXg1i58vSDJfoPGE7W7qvDZ7PxqXJN.dowZ6KUJklk1Cv0nTbItFI7jfK4UtwxIMe9m+Yuk798aREAjPLKJdsFCftT.BL+7XR.gHpgCZwb4d6IZNAd4d2VZ2qDDkM4HHSzkRoqF2tQxZqs1tdsoi40uubI5Dyc1rM.pS2AHEg63LPT79urt86epQpmJ4LQ3ExSdhPwzniB.FzIRAA68kBPoXZYjJeRQj1oMiSvE6OdOuJ3xjrJvqUqV0QPpXe+3bDWDh4UmQgXtNUPyRT.1vu6nnSKFjuVwuSIUlzxHkRopz4hutXECCiJifLQrkfrWa5XVts4nNGl66D19dcV00SRFpR2QRwcLoziVWjLz.QR6nihJCaedGmfLAv6QnXpzQA..jCfMkM6p3VYjlk1C2gKQoPYzohyBtbZAuT8bLAJujRmIepvEgX10sNToW.WHlCeM4kIZqo80KHP+9u8UDKiT.fIJhObwy1Rbe7R9thOL7.CCiJ7T3knHSHBqlN13bayQ0zwby2IhaQlIDgizcjDRgK.ukFgHpgQzbfHocGt3+DiU7odlPghWLOeCWpfoYvEnYrpqNpJsGgYm1LAf1i6.PDawIRDaEb4zBcc8MbQSEk50q2ASqJ5Uk6eDQ+VHlQPYhNNbGlHByj.MymOuC2ijPHSsvCs.uQ0oxmI5jOe9ESBjIDgkaa5glNlM21jGcBU9NQqfeTG+PRNcGTZtsDKSTvESrRDSp+SL78x6CJpiWLulGNt.MGFE.J.qfwulwkb0dL2axUbAWtuaMuK.F5vkKVqVsw1plSxXDB0rHiw1aRWcL+ZGGgTbVlvFGjpixVay.3pQUYhNNvXKbU6Bzjb4Se5ddlXFuju8ECXCfA2.sd856o5b8ntZN7CX0zwFmaa1nQicLLLz50qmC6wedsxN3nh7NT0LEiaHWtiWgPnByyfsFSYhB.nT+Di84.vDPnfGlQ4Kn7r3Eo.TURflMiSo9PUZOlWM4JdKEeOtfKccRdDwNbGtzLDGdQF32rWkiZVjRoMMLL7bd7UUlnpzFfWABfFydpNLi5xDcbHWN6Dz522YjAFE32jzTbeDB4RS5BA1d6sK0qWOkhKFQrcRmLgE3oAwxsMcin4JDBwwhH3g2uUfOHiof3rqKm.5vpXQ.PgqoFuPLEf7897jWaLIo7..EMoGu9DICTZdrM0G7zdzVZ2yUo8fuJsl7VJd4wc77n3L1iKMg0VascU4nl.Lnz7pWu9X0UgggwlpDh4rDNcF.MkbDypwEgX5FN937cXrSV0KgPJMoo9PkngGkeoHCAwW5f3LhXqZ0pkJHSHBdZPVZTMcL48oxv2lWfpd2QRvLqnziaZOUGjpdPHlfJGVUUFJT9dNAiOG9QwjlV.B.6FmS8AhnbZOzlGZo47x.cyd85cfao2fK3RUhSL1PJLrvEu3E6vaVSNH.PHjx758urpmKOWrx4ldVEhopTczdZe8BSLnOebRTFlzTevEMbaw8QHjJiinq.4YGhubv3B2HrrS6nBiqoiYANoCyPYPECAiwTc8Zrt5NjS0AhrcGQ2D0FXLlb5NL85hclHBEt7kX4I40vkTenMIuFAEJTnvtxL1kOYJsACCiJ850a+w4vkbAWtgLoBUlc07.pVsZ274yurKkUZQJktmJ2IjRopxM8rzZxKA18bhXepNrCRWJksp3dFj5Cua3Upxs+nhRAOEGJ0FDm37x71ZepGVMcrw31lECxlNVbF7OuxK5Mlmti2RSNUGL1o8L4XEo5usWetSDgBU89hI0Dnhyo9feRhLooTomTvEb4AiygKkEbYgBEbnV7oIu0oAXMYragCl6Ng6asZY+VHlnhqcRBo5PFpR8QtbusmSaA2rqZItOBgTVkPYMLL1DQbeUmyiH1gaM7smfgep.bMxMxUgZ0zw7qxyMIfCO7vUTr.fXc0cPo4lpTc.fZ61lLAsl8IUCE.h3TW9nVfm5iVBChx8AXyI80IHfhzd3olhURAau81kDDbolpigSjXYUBtjSpz1MP44sNVPJLJPsZ0tJeEdlxOlk54MLL1xuEhIuShVRX6DSpNjAhmdS62PirdtbG64q6PDUQzcHoDABzJIpvXrqVqVsklWDXrL3sk8wVgL7yma5WMcr3NjEiIFyaY6DxwaRHzxmrGrkWS0wfmuyBQXb1ssHlXBE4xkywfaZZStT.1PzvqnCL7pxS5qieC9pcLE2WZvSJ3UtQS9pyJq5X3VkcUNQh1t8Z4RdqK6msK4jF35pv0xxiRoJcDyoUHl7d0wva.v.nStXomS3cLnpODM7Jr4fv2NdvEUsbYjpYXXrEWqDJIPyIgrpttdh96tYELFSk2arQP1zwh6fuZ8xh6KNGchb4NtrXmDE.zbBppCKHSfp8jjdmIlPAOzXlRuoSbuufm5Ca4NkAvNwjRIUdhoRIU13VBtTUofYAKGtjaU1s7xqqpUViHNRq7MsCqTf.JJsTYLKBwDAnjXpNXJtVJIhiONuT6imVjRO0Nd84WnPgqJ+8NmHWEWdJ6lOe9EmklvVZ.74Gjmea2Z0pcUu1zwbysMS3P0BIaE1CBuArH.nsqUFnMIukpC.FZlYxmGLQUyxDSnfi1RaOUqLka5NCm.gqmBOOARPAUFVRRTblbAWNxVJNiwtpkCWNIu1W7hWribSHhPHEO5nilaS8gE3MooEAm5wYH3oR6xSJALKcSHUhnaD0cRT+BLV9Vh85iA5o3XOcNkpzwoBVQkXs0VK10fuBa3VUGwXrgeOJ1zwFiaateZoLx42bshzt2MtlRLJ83cD0MAhrMFSmD0ATkZ+IsWkLUDJjEoAgPJNsmHQ.3pRkRZ49QbWIkOwTKocmXDmojfKcaLuKiwVTWWepqv.9JBMk18Jyyo9vBUqVs6Zqs1pt04GAvVKk1ypmmAvVR5lnUbqWcLqne+SsgjdJpPo8pLtmmggQYEFPjLxhJg.HDxNJli3JpzNkkaaBtPTlPHk7RSGKI.UhwDhoVsctbGukntIPjsKisvDWkRxEXwzzqRlJBEqs1ZNJuRXBbMSEChpLAKBlBv5nBqNMLgJwY1q23mTKJAmHgmDb4Zqs1pyJaaNwKGkiz7dpODw3tAGuj7trWHVv8ahJVay0MQJzqDHck0SAgjqoa9Sgz48kc6U057948nRXAUo5.Qr8nJYVcccSNQ4w1zwRxkStp9XRbjD5.h1jgoaBQryjThnVPU4wpn.LF+3YReBBP10Lm5UkZUJoL6k6VSTXkXgMTINSHl5blVBtbTSn5UAWNoPWWusBuoHK0GfZGwbDSBaiXgbY3xM.NQ+lHUnaB2vfv0RrMwHiQ1SzeJZznwJdgHQFbBdUc3nS2pZABpfWZ5XTJ8xxMcrj.3Q5R9dOOkxCNBwoOcuRDRNa9Mw.h3dW2DVPU5NTU.FiCSMgBEo8XlbURB.cj6LhL.1KJM8JE15qVbJb9VBtjaU1UTcL7II1XRDb4jBt2TXJs6URoB0xSvsbSyyEsq8RAqIhoT5A0qWuoggQYYQXB..T.VNsnaB2P+9mdWQ+oXfHMe689ze5O650qW+..fclH6+eNtzlEQylMKpppN.Eo5XbPWWeyQ41lxMcrIezF9fRopttsUDMbbAuk1.B1hfTcR0MgETjtCO6Nl1dcll2b.Tm1i986Ot7WNRP.nESvk+rDoYTU4GpbNSDwXQTJpWu95VBtzsigwXWIe97KFzt9W0pU6RoTUqV9xI0piYVwnbDSqdo.iwp5VDK.XPniKb3g6czcdm6SseMP03ZWD0uw.+ofMbkRDBoze7e7+2a4VJ8F7bvVLFaQUt557LIWKv6jnSTpNFErptIuzzwh6tsImzSL2YLQd0OchHLYL7JSheSHBWR2wT8ZMKo7..eLsGVHG.aJY5UkX.r2HdJAFTINSBgTNJuIIOLuGPHDG2vxBVSnpqquYXcgfaU8Aiwl6zSgWcDScc8V7vFqjXwBu4aBejemeGXg27MGtuuy4Oe2sazHFM4VvACCCMCCiM+2+u+2qzC7.2Z39uwMdP32828Qcb7Vm2WqVsp555lpb0U.fItxZRSvvvnhhNIZ274yOyoOyKMcLK21LNEoWQnxx1UYs6QInz2VpY1gsP7zaNsudtjtioR.pyDgBUo8vOxWF2zqDEoYo9Qm8b6H2YQQIjZI7LXPXd0TcLBNbY0nn7l3p.us39HDRod85EoUsSXCUgVeTSJYQr.FTu+ss1+G4242ANy286N73LKUB9pW7hEA.1od85+HdJQpjltA41aucICCiMqWu99TJ8.Jkd465tNVaiM9hvcbGGM739ley2G7U+p+zC8PEQhDVGCmLsCRtGd3gykQof20LcbsHgPp5mK7vpoiopYBxe+zfAmCuWbJMHtrR81woREMWtiaJRl.QryTXdU1fektC..fLKCD..nd85+HwUJya4uyrxy40a+dxkHWTnp850q2TlUOOB.lA86MOW7WdDlyCfHZRHjMhCpPlOd2WN5ILFqZPogi3D3ZZQVraSz0Dau81kVtQi8duO+yO76va8ddOv09M+Mgity6T4yAQrMua.21OEcq7mGdnwW1ud8a1rYQdI5cA.fxiJUFuxqbFXqs9kf25sVX39NyY5twq8Z+DiLT87H5Y60Mrt9MtflMaVrWudNZS6LF6pAoKgt81aWhwXaMlpu4pEJT3JQcZETcsKiw7UQrOKXferbx8AFTQGmZ4oQDlVnYylEO5ni9Qh6aVNm3TS6.Q.6B1KwyU.e3l9D.5h.rJCfg4OlBPk9..gMoBJk9THhUrM9FDZr.abvmn8xixe84gU7JwoNintttYiFMpBRFTFkRat81a2YZY9lD.eRaUB5Zht37iewKdIQMS75+D+Dcu1u4uYQ2HS.vfTwwmz9xMZzvFAiBEJzIpmr1Bau81k52ueIKBDGczQZTp2BT569c+218Iex16Vu9uXEq8cqaUbKJsW2AFhkZfHVkPrKfMJktEjhqRFY3htI5DzVNN+58k4oZ4xpHLx8ikJFFFaDUK5vkqc6DiHSrkHYhAUzAVkwldxD.LHcGJt9apqnkYNBE7bgI6tkq5WqVlqv88THJsV9wquWQ850sUZZ7aTrXPLQMubCuzHLkJfwXWoPgBWMtbiBYXXXrkLYHDQy74yuTbcLOqPUjr3UXimI70efKXN70fWdnK8eY6sK1ue+mjPHqLpUw6F3jO6fHdcBgX00fMG2pzm1HTXXXTlRoEYLVIBg7f..N5KBS.1kwXOSgBE1cf.f6Uwd4xA.h8qNJRExW+BP7Z0mAIpWu95xo5fW8WgZyPiuHo0GkPxQDaSozMB6Edn56n3RTUcd9NqKkhKOsUzgHpWu99xoPoVsZKMsudyLgB9fRNjh6t1Zq4ar+iCjJ3SPZaUNLF6JSpkUOl2CWYwaADwVHhSb4cEEP9jU.7+PlGWfpyOlzKNcgLwxxUzAeU9SM4BYXQ1fuoIh3Ka8XDB4BRDoMUX5aWf+mp5E.SKrQhP9AmTREau81kPD229wOaSdlDfpyK4v2Vz2jBdZQaNJBlHhsxmO+T6huSJjuGFhnIWWSQJBRxDFFFZTJ8.w8MoK.RF9BgBUqFcgEV3c5mmLv6DoxWXDpjJBpnTvMRkKOlKvhDl6yB3gQ7.EkOounyl3DTQdZRVArWISHC9jyqPHjKfHVdTQ0JNCDwN7ywutWuQ2jRpvEsPEKVEZP.t9E1SgdlBTcS3UznQiUPDcsDfCqT5ZXXTgRo1NOJNbdgpyuA.WcZKOTY3hlQlIsE4KDJTw9OH9AgaG2xJnOzHUnJ8NyRTJ3LD2BFQyUiuhvpI0Pyp5bC.hGWv5WvkPJ6YRSSKYBUfeSjxbBFk7iHXDDfqwiNTJ85KrvBSTKRVDSBoBUDbSqogyMQXFGiP33RwKmr4FA0bfwwnSLMo0aRQPjYAegPA.9etXbCpHUDlU+ghS9l3nT3UAWxuHp0LMfiAP0J.3HxB6peAWtIkmOmvOIS3136vCOrDLnBJdPXfyyVJrhjA2eML4BD0LWtb9tvbmjIecYUY9ZpKiCPklQPD6jOe9kiijm73hq78z8pZtoYMr+yJHji2jRs6GF9MYBWRg+LuHO+jPgiUoQHjkBhPzGkjJbI7XddBIOvFuKhXDhZ7J...B.IQTPT4SEmEb4z.WDrXWJktbRJMNxXVDhYPSlXbvxyXHDRIDGziLnT54r9aNzjIPCRiOt.Oec9yuCiw5BdPvm9I7JoBNAv8k+LE1BTLHQR9ZMd5eaNpzffH9T9EAP+XAh9IjKMzAiI+kLA.NOGwu9b6aDJ765Ycb.AnLCfcDEpYXQpXZNILsI3xoAMZzXGvowwjHlnSElVgXx8XkcnCzED.P3SlvqHn8gB+DpIUv1PtUN6xpRSE55QUDX.H4UQKbKR+xiXgWybpfm0EG52vIYBVWDwM7axDptWsec9+rZ81CA+lo1Be8nLioYED.ZSAXYwNTJ2mJ1On68GxtdH288TVJTbGtbeJkNJV2sIDxRQkCWFVXgEVnprW+mjsmaUtNHh3HIPKXXaks1WbkLQRCLV9VH121jhDBcqASTeBz00aovQWqjz5JlxfeCRUjIRbZvxxsMka8AVvpoiMstsYylMKpP2SlEJTHBR0AVjROZOYxDTJtreSl..0VsMkR8ktopuQnfC4xIqnggQEe983jW+AcnTYREkB5tTppIjnT55hmXyao3VsVYkkR2.mNisbsZ0RjqPeRQ0pU6lOe9kk84et8buWRhTAOEexBdq0nl3lW9y6K49qcxHS3ePEoB.HUnzi1Qr0mqxJzU0GGRJvMcJwiRbqHXHMyPpoi0V0wPHjxTJ8fIsoic3gGtthpOKBbqSr3fdyAs7I6y+JMTUf3rKHO0VssL7UBE7NPpo39HDxL0ARGGDHUL7KDNoh8QgIt8a31DRMa1rX850axao3kc44ZxXrp0pUaoj1JGlUv6LoIZRE7wnr8ZORGwjmht8nBDcyHSDLfwx2hR6uD.rgmiQHzUnz2dOKRE555skW8KgPJGWaZUiBtQlfSvMxKOzYE7lN1x7lnmxa3OIMcLdzIbbS0vl30oOcuR4xc7ARM5KyfjLAuetHeeQeI5D.3+Qn.TX5MkC5F.iKjJJxiTQkf38jOgTaaiCBoBWw+JeOQdiLJe97KkTW0fefKdwK1YTjJhpwkWA2FikI935paP.VGjLlMF.6xISjZDdabBGeb9NTJtrcREjR4xc7Am9z8JAf5EEfHlnZjct0vu..1MMnIDQnqq2xqMcrQ0QncK5D95fcLfR6UgwH6I1BxwAM5qkBJxD.ntwVlOu+kVEemPAn1SHB7tyIgmGZoVedQ.fl8AHPljvknT3lHhZkOe9PskhGmwEu3E6nRuADBoT850ipNK6XAWE5UD2GWHlNljCAnHuK4Z2ReGHd3UyHSDr33iy2oe+Suncc6PKxXj8nzdUz00MYLlrdnzLLL1LjGpSEby3pPD6rvBKjpHSXgpUq1UWWeCBgrznRCBh39FFFaIGwSd4oJGcwPM5DDxwaNP7vhjIX6NqM5qwAW5lps7y6G46DJ3hJzg3LCiPYS.naN.pxjZYwT.Vu+fnU36iA2BAmvi21p0JmQjvNz00awXLGS7QHjJwUREdUHlH.Z7TbTQ5gpFEcL24WP5xXmZYDYByIQKRH4ZlK2waUnPgqpHRYWJtm5sQQlHt50D9It3EuXGd0FspbZ1s.uoicfnN9ToSFDwP55wAhuT1iI..uJisvpAIYB..nWudUTb9xS61wOMHHhPA.JDmoJkkFTHG.aBCHVHJVyxL.NvOzUw1aucIAAW5p6tYI3xzbkaLqXbjJhSSr6UgXh.rhBwW1EFjhiVgxfMCBfzkwVXUFSNhhj0+3e7e8891e662VNjGUUaEGv7NYBQr1Zqsa974WRNRSVfPHEoTZy50quG+52JhONhX6vPGaCzKwauur3KQre098OcXoyEU5Fose9FDHDJbQblg5EnD.ZwSAxvwAOEH62e.giIF7J2nIh39dnyI9zyaBtbZwnHUDWDpoWEhIO8Zx9iRGJ.KQ.ncnLXyfRf3o2D.bUYcUb0q9O5R23FOnsiUtpshKnQiFqjQlvN3oAYSFis3nRChpnKRoz.+l4T5QqyX41G.h1I6cf3KChxBUEZzngiFIXPnajfJBE.HobTdtIKGfueN.WrlKwjRACEfKOIo.oYylE4Nb49Sf2Zb43vMBSJXDjJhEU+w3DhIBfV+AQkXcwCfwI1RDH1lgnC86e5coTbYYcUznw+P3O7O7m21wRHjXUZ23gtemLxDpgtttIuZPV1szfHBDwVAa45iEozi1gPnR9cAqcPK9RGiDDkiNQ2BEJrqaG+zh.iPQ974aImaRJkF3hyTFbcUrpBcUXkBjQlJFCCiJ8506.Jk5pqswXrqpPbWw5vlFGQbkTgKBwzzRHlH.q6RJNplaPyqatdh93FN937cFH.N6kM5W8q9SCelOyJvq7JmA.XXEpUNBFhNvHJMzLxDRfWloKxXrqLFMtEX+9lK2wkGTRnTa2egwvqvXKDnhuTF7NRbYw842hwzBAFgBUNmI.vJQUXD45pXIEo.Ym9.ribzJ3Nb4AbGtzsajsKucutgtt9lxrhoT55ip7kxfSLFRE6GEee5hPLqxqhic..1RQJNxzKQrFjt86e5pCLAqSRAxq7JmA9LelUfm8Y+YFbTwfnTTud80yHSL4fOm7RtEsBK21rQiF63e2WBKlK2waAf8RBcv4X3xCR6V3BWjafu48DhHHS4QryM5FQJPVwJZERBtTS0qCuxMVds0VaUQAWpRsvLFKQUW6wALBREZLFaj0XteCdOXQ98a2Z55EY.b.UJBWL.tZlYUkbv.SvRNEH.7rO6Rvm4yrB72727SnEjt863.uINohPaFYBOfb4xUbT8OINVgPH6OqkK7fnR716C.wVZOQjsa+9mdw98Oc6Y40eZ.2DupHs6cCpBEHPITnqqapPjLqDk4C2JEHfyp.oH.vNO1+4+y6m+sdqxpdtBNboxFsCeexkLaYditICS.30E9pJJouhLFauvXRdU98+ceqaA++7u9ecIvovK6B.rZN.1HKEGIKLHEHmdI4p.wJZEOyy7y4vOCBZzrYyhMZzXGUZ1BQrcFYBuAUKnSUZP3UCxkqWu9AStaoJFUBhlv6dWdyoKvKIT2vgGdni68vXr.I5D.DvDJ.v0FoUjeCVdUfrDSR48Zc5.+Z+q9WAu++r+rg6yxgKqUq1hiy.TXL1FJNgMSflSAVas010EG0zpTvBzyiN7vCsoaly+E9BvG8S+og24O3GnIdbbWubQhyT7kgDD3UAxx.XOD4ekuRohe7O9u9d4xcb4vXbXXXnwcLVG2Xi2UHyHS3AvKSzxR6d2w0zw.taa5kzfPo8pjK2wGnHpDs62u+Rxc51vFJrX7NAY0GF3DJ3VTssvIJ+gLpPi50W4+R85k9F+i+GCGcm24v8uva9lvi7G7G.eje6ea3c++5+0tVNboWdM4QkwQcsezQGE44hMIBAa51T9wHDxVAkAXs81aWhRoqC..+T27lvG8S+ogyesqAK7lu4viQHpDYtdYJA86e5186epk9fevuio39Gj1KxdC5boXfs3.tUZuupFJXZoEqGFvsx7lwXaX0zwFmaaN5lN1aoQoGsmriWJDUhkA3NL8wORSL3oqUthfBrnS.PHPn..meHB5tP53PiFMVod85GPHjsHDRwu0+f+Avm8e6+Vvrj8qgu+adS3w+O7eXkeipU2ZRbYStXfjyg9JwEEimzvEu3E6jOe9kT7cpkAXsueGAHFis0ceqaA+hFFvu7u8uMblu6209iOHBWYQkHUBR2JUt9FexO4tvC7.2R9wpLP89Guoe+tZXXTg6wMNNWlmp0LxDdDGczQNDSOh3SIpc.K21zKMcrSte0fzajK2oOvtIUEehJgEj0qXXXw3gBgBd691TbeQg3L4UtwdvfZ4VS7wN5NuS3KqqC+4+p+psYRdF.EfJL.NnO.a5UhEtzmJhUN+XRBVs9bPwMv4U.xA9kXM+Ct7kq7y9rOa4O1m7SBZcrygg2.5VNqbPS2Xs0Va22869us8m7StK73O99vcbGGI7nzhTJ4x4xc7A4xcru3.v7NTrpJ4nK.vpyyMSvIEbMPX62Edn92T0w6klNFkRa9g+vO+9pRuAuBNVMNDUBKviNglztCznS.PHQn..kZoHzTOskCWxqbixtL9LA.V8Q+8+8WlqshqHKZSJ.Wl2VzG63VWWus7InDBQKyaJldTsZ0tqs1Zqp5BeBgTDQb+YUWE8AXyO5UtxVm+ZWy194mKrQtLGubtAVtn3i+3+OgO4mbG3bm6kkNBhF.jcnzilZ8UvmaRog4gHZRozkWas0xhBlGQylMKppiwpZAdhvpoioxsM+ley2G7a8a8OA9S+SOWI6o2...vqxqfiX0uQJhNQW+rqh5FBMBEEJTXWEhqKPu4pkCWRozQ1RwQD2nVsZKZcgKuRP1zkRLUCFzASOXbDKJTnfCiUgaoukmgOVy8feguxvTRHjsZznwNSZjfP.pzePYfdYpTTn9w+896YI5xXQnLyP3.dGwsE..bly7FvZq8mBarwWzQZPFD5axdSJwBtcH6ldI5jOe9kBVmbL8AtPp0D2GiwtpWEhnkaaB.r5e0e08282525eB76969nvst0cY63N6Y+dv+r+Y+IWcPe3HZpfC2fK1r8SEFB4MzHTTsZ0tJzRQfEkh50qutkCW51wvXrqjOe9EU05oA..B.l7RLcY4pAwKDKpVsZWBgnxOExR8wLBcc8VtIVS.fU7pIXYQj..nI+2zg36c1yB+w+K9WXdW+c+cYhtbNE4ym2VUa89deeO3e4+xcLOyY5tgb0fLIDKLLL1BTXi1.LT7kKkUIGSFLLLJaIjZKfHZVnPgIpmUjK2wqnqW8R+G+O9KUTlHwC7.2B1XiuHr95eQ3gdnev50qWe+31BDcwlsCkECEZDJ...WZUv9ZTJLLLpHJ3RUGChXKtCWtoWtnk.P6b.rLLvBuMEeLYhExZrfG0CYuoHK0G9.DDqYa4GiPHZHhJMqFtCWt4nHR7E9DeB3ZehOA7ZO3ClIDt4X31BgtxU9+qX+9mh6cELo4znkciXA2371W9Fe.LrJDxDe4T.tmwnRCJU8JwLgR.cGYAWdG2wgc+M9MdN3S9I2Edeuuu2v8SHjRTJcu3RmQl2l.JKtuvJ5D.DxDJBxnTXI3RtUYqo5Xrb3xZ0pUcZbJLB.6lCfEgAlhksmuEwBUh2bgEVvQ34yR8g+.dIfsrasuXtY0rmgggFuAdsE6jTanIdr29LmA9x55v09DeB3UO6YAXfix0N3+Tjg3L3KDxTbeDB4RFF0Kh3o2re+Su3nIVb79TZuJ0qWecdmBUYJNnT5xYhub5.upNzD2m2R0AVjROZ8AUtStl1MlJ...MQre023Mtq24G7C9ht1zw3cF4ClU21bVgJsSDVQm.fPlPA.9eTJLLLzZznwNiSvkbhDJc3xIED.ZMBhEEoCp+4eTe.Zh.TNK0GAO3suXGlfE..7t+1e6x+xO0SsOLfHw5xZj3sdGuCy1Up.etOymYXoCaUy5gynOCwYvWHjCC56j4sHcGMwBRIBIWyO0m5Wcqu3W77NBiNhXq74yubldIlN3RUcLlTc7VZ4xcbSdC7ZK2HRL32zAhYbbMcLQ21LJVrXTGcB..fDVuQhfKTRajHXLV0IgcdylMKd3gGdYUgNzBVBtLnY8iCJqzmjBPYUONuYQ8T+t+6928jGdO2i7wr6Zqs1pA43adBMa1rXud81I+a8Vke3uw2.9+5O6OCt6aI6k.C.Cf1T.tRcCimP97HFicEuZlYoYHesJhXatn0l6P850crnEBgnP3jXQB4sWmRwK4rp.Ffe9e9uMbty8xv6+8evDMuWFrC906GHmdaFiobwiTZuJ.PdR4TZbBPSDYWwhDwXde2xMw9ywtLFaifpuYHC4yO4U1whodBEpNIf2NnWzKOeCCiMIDxkFgFI5hH9TEJT3pg4Wl3fVh9kjaXTh3lOxi.lkJYyDslTxTYvcfCZzaO439M3utToV+RFFU2d6sKgHtusWiI3bwzNxHTbB3h9aOw8412G7VFcy+6+2Oa4m8Y+YbTk.BuBlLF7zH91shKdXPRBpH4wS0wvnKd5S2qDiQuD.3JtQvCQVaBg7TSZ4exiJvVpRi0fW2v4dQ7nzri39hhEEEIDJ.X5hRA2rNbTVPh.QrEh3UBKVgJGC.nw.3R..UjCutEN5NuS3EejGAt4i7Hve6C7.cQDWJJGyIYvIQ7D..q312229LmAt4G5CA27QdD31m4LCddCDyYQ4ICba0MyiHiPgcznQic.mjUWUzqHTsfmu8299gu5W8mFtwMdPWesG3Dr3SyX82Mibw3gp6gbRWX8WsHgbpJTJ7jNSmgEXcAfrKkxdpiON+LktIt+2b4QrHWSBgrQP4oH7BQPS38KziNA.QHghIIJEbVfW1MMRvetsoT5Fws7PNtzg.vfa1829te2cV7EdgqjYkydCdgDA.CZbWuzRKY9UqUyqFdUVJnDPFgB6vvvPiRoGHtOq4s7vpU6709ZO7U9u8e6WnznuQWF4hwAUQV7Udky.+w+w+r69W8W8t0b62fA.MQDeJF6zs7SOjvioguMh3TUT.tACCiJxtrZTkx1HiPA.iOJE7Kd2BFQ3qQDM4+.0NPGryHDhZwJxUWfH3NxXaJ.OC.PahjnOmWAN36rxL.dhQkNC..fKT1mlBPKqu+1d6sKwXrlidhF.3kSro+LpS9HiPgS31JiG04Vplfmaa2OA.iLO77WanM.vyzu+oaOsi6zB3KFc+COLu1Mu48C23FOH7s+12+HRqD.9YzHFG3y0r0nV.LiwtZgBEtheDAg3RzI.HhIT3RTJ5hHtDOhDUb64FVBtLH.WqEOILlUWCvvdGQaJ.WGFPvXtvraDHPbA.fxihDF.CIQrKEfmlL36LkvCglrMOkYsm1wdZBYDJbB2DBnJ3sHmhEoziVA.xSPHzwzaPXcQDZC.b8b4v1A8MGiaHWtiK+y7y7RW9Mdi6r7Mu486gmA1BFPDKzi7KOE8ixOjl46gwaQ61rZ7nTP4QJgB.TGtlQgnRvkAALLLp7PuvKz79u4MAsNcbsZDDA+Fmso.bCX.AiTwDJ3fTBUhAv4.OPf..uShPFpDvjBDpJzNthLBEpQ850aNtE7..bE2bgW2wjPt..NAiNHRtNkBs62+TchaVA8zi2RKWtSUhwfRDBdA2qLCQLHRD..OS+9mpcT+cAOMHqOJGadZSWuaKHOphNA.w.BE.3LjMtAd8ZuQRmHgHDmX5Le2uKncia.Zc53ncYOJvihQG.fWlNvhvMiqoJgG4AM1.BDOH.PIJ.i0hrs.yd5flJxTpTFtaHNHx2nDYDJriFMZrBh3ViSX39y7TXwb4d6xv.sBUdTZtP54YhH1AQxMnTnCkxLi6QxHWtiKiHSCQp1.xCPI2pHCm.MgAZO65wslzkErp5mwnCvI57FWR81FSNIV+CQNgB9Wz6Lp7OFDBYIt.NKSGtmWgW+02823e9+7mVHj+d9ltVfSznKLHcI.8js6FTQ1.GLNKB.TjM3uuGfuuY3yfukxGUQmf69cEiakgbb.YDJF.uHLb.Fn2gZ0psTPLFN8o6UpeeRY.fKPHPYueC2SFa.fcIDRGFCdcJcv7A86+1lAsvO4kt4f4EXPIJEtGDwRCHlQzljWq63NNBN6Y+dv4N2KC268d6q7a+a+Da56C3.BiiPpWirE+9l6OsVuPPgHmPA..vaeuNtYy.V13Fo87YyEwydJLmkgBTkak2k42j9BippQlTH23ylPLUDEbYbzEFPf357HszwO0LhkXtTXQuKBv.Ga0C514o..ZkFI2pBy6DJ7JQBQDVkcrcBFjRS5MlUCzTxdo6hH4Fd4YRH3EruMQyOFSHhcdjG46T5rm86Auu222CNyYdCq8mXOWzCdozHu2mpTtEG7ynXAgBUFFC.I6SXlT3lVRT6DeC.OZ.kXCRivE..z7h1ChCfq+ASX.4gNv.xClA46oKUUjMAL4EEZCv7SpPlWIT3QOuoKhXKEc3x.KJEiFXwb4d6RLFTlPvyA.YLkOY7CbClxDQ7FDBoS+9mtsggwVJ9NNR0Jfe.OVEiNlmwEy3KVbcYrfPA.tmW64ISFxutvgKvQeIkCyBDh7QG.fW2JkKjYKhHSEby+.xmOux1D8DDh6VHhOcZ8bz4IBE7HXUA.3RdfHwvTfo5513vpEsfU5FXLnrUpF.f3vP2BKfHq8f+mLHUrTnsaocYZVnURC74ZFUSsrKh3SYsvGWbGzXw8IiMDJZ1rYwiO9Xs4caPVU5e76U7HnyA.Ng3wTCAsY.PLUPntPXc0w4bcS.wh1bhEslsQZ7ByCDJLLLzfAjHpLpRA0MszDGUa+j.wVrNiYOUpTJ7fHhZd40gPHlLF7xmr8.8ZL30g0cREFppUhOXLFeHq4mvKtsIh3SqnhQhMlwWrgPgEbgs+bSiZxsZbGQrUsZ0bzwRyv3gKBwbhtw3DPrHUoyhzLgB94EOILFiRyKhx0KoSKCdGyqyC5wlNlMDmLiuXGghjNae+.twLOpKInjHFkPLmlKBmDQ5kFhZQZiPgPzHVYbkp9jVcOpJ+83zj8IE3VkuEcZSI7w3rwcKD2HsRi5AfLpVsZWDwMD2GgPJ1qWusb64j1vEu3E6vXLGrvIDxVFFFUhfgThEGd3gqqXR9oVLk555sqUq1xLFaQDwVi5XIDRYJk1rd85+n50q2zvvn7z7dlgYCMa1rnggQk50quOkROfRoNNmPDHhlLFqZ974WTWWeSutPFBgrgh84pgFkA03niNxgE4yWTYhkH6jB97LKwXrp7RI0MzJrFSdAwtHTXAUZIHtH7jvBtIRSJktbZQPRAIlTgXNMvxI7HDxS5QyYyDQb2b4x8zIgeCSpQnf+6xJTJ8IfwjRCKfH1lPHO0rzQHiyBlKI.UkC479bdtEk03X5eNUTO.bCHhaPHDakRJ2yxmKB4E..nqquQiFMz.gIDIDRQFismggQV6NeLfPHpTGtu5zp7WqMA.1jWpgO4nRGBgPzHDx5HhqWudcSDwcoT50Cp1Z77D3l8yJDB4BGczQqPoiO.rVk9I.vS4GWOQozMjSWIOJEsm0W6zN3W+TQd+HhwttHcXhiN5nxJHSzMe97NhHVTiXaDJ.vUy6HVkynfFiJeh4yme44EckLovODh4zBdd5q30nV.vfIHHDRaFi8L..siKjEi6QnfmFomfPHkmvxfbWFi8LAg9VhqlNTbFtUdny65FaDZ.KVd9TrlPwn5FowkIbCCLBEOmQpPA7agXNKfa0tOA.vJdo6TZAqTiPozquvBKzNp9MNtQnfa7XkIDxE.OlJCKLv5ogmFQb2f77.2rEY+LUaoI3lSAGGCoeXCWpdnqpqqG6hNA.w3Td.vfvIWud8q..LTPlDBoHO0Gwh5tMLP0pU6t81aur7EcDBozQGcTSXN56Bu.d28SSbeyhPLmEvSkwt..UmDxEVoFA.X8iN5Hnd85lvfvleCJk1ddHDvbcPTB.nLgPt.gPJiHBDh2WGjEwLvmRogWftttoggwSIJHSBgnc3gGtNLH8XYfC2HS..r67NYBd09I27uLKTnvUhpwz3PrNBEVXZMknzFFQ4jN2yj2BggPL8CLsQtPD7xRsCgPdYDwNEJTnie+YLrhPA+2sRLFqDkRO2IMNpIGgUjHFETEkr4sxeebXDQlHKxqfq83pX888RDDJbw6xmKu3bD4ZLiTAjLIet81aWpe+9qPHjmXVsCYdIl0geS0WG3hAbZqx.+jPAWaIC+Gm3vL2uID0eRgBE1MtLmfpqUytNc.xzF1nQ850WmGI9gHpS2nWPhfPA.IubIEjvMREyqeeXgnTHl9EZ1rYwiN5nx7nW3Pc2yJ3cRRS9eaQ5.HDRW911.WXoUDd9cj8IF..fRoEYLVIgm2CB7FU2jzoN8J3Qm454xka23b5eTsJyzTenXZvHHSLWWdnVvEM3jHzNXhgPwHDZ2bYMdqxiJ.H9p92fFwIgX5mvhfAiwt.gPJED2bNtCDQSBgzAQ75HhcRRWuqpSJmzH45mHiLw3gpnrlTp1kDCgB.b8hyXW9wCKnp7z.X9jTw7TDr3oHoD.v4RajLrHOvXra..zNHzERXiFMZrC3rhTh0ogKHPFYhwCWR0QhwxwSTDJ.v0lGVp7FGdAYjJbUHlyUZrQPeBkA.tG9j1Z9cJS7KvckxtbhCl..lIoHOLIvMgBOO0EkciLA.yuQYVFpR0A.IqTjk3HT3lmLLOeR47NoBWr634hO6dABkeI.vv1S88HM49LS9fqAit.LPSFbxB.vIL.vzKNzjNTEAsjRXrmULFxDYWmxgKyiknLxwDGgB.bU7cyso9.f4WREY4nNXQbyXqRpXdsKJmQlvaHompCKD651ndABlEzPvMNl41N6WsZ0ppp6WRozlo4NTpp90AkRmKS+UFhufSZvlgDQHjho44rxHS3MvSWoiyCnTZhq7hSjDJ..fEVXAGs0UJktNO5EykXdiTgggwlJppiqlTx2XFluPsZ0tJurcGBJktN+FJoJjQlv6fPHMUjB+qjDmGKwRnnZ0pcQDcX4zHhMa1r4T47foALJRE0qW2wp4SpfKfoKItODwtwYaoMCY.QzwpNUEksjLxHS3cvWTTYw8wKM5MilQz++s2YWVssZRW3pdoWQ9tlYPaFAsYDbLifPFAAeCV5p.i.fQ.jqjruwjQ.jQ.9LBvmQPbOC36NLqUdquKbIhP9U1x+qe1Oq0Y0IFCn1wRdqp10tVOJsBJHZpAurV6GL0Dy7g59sn1RVhJXlOqpHpvXL25Hxd2nqlb.XSSPPvPQjgIeLl415VSszSXXXSHlHezue+VNLp6KkwVcDSoVPAQD0nQiaRWFQhnSihhlIzmpSTkEUnW78Cs1RDYHtXEnLPFUo3VWO2xD862ukN1iPLwBXvfAGZsVWWGtT1piXJ8BJ5zoyKFiw0117p986uV6HfxNKPTwSk0VCAiXBJyDDDLN84kLysJy9bZNK5qWHh9BDS7QlLYxsNB3qgk8wHtzKnfHhNbYadTB..ZHWRDEDU+7yGYs1YbPs0Zq09ofn4Jpn8jISJchJfQLAUA777tLsoxYlusrc9HQS2sPYIlvXLmT2RDzEQud8NM8H9qiPrqaLtTQkPPAQDEDDbsidS1ZxjIk9RItt3662IsfKhd+0mmJKUxAFwDTUPMU92S9X5XjVpZUa7hJLKwDPn+GILLroHxLUXkYtSUv+WUFAEDMs2jNT8eVcdTRiIHH3Zq05p2ssrVaoPTALhInJgdSPiS9XLyeqrLFo5ZPXlObTDYDDS3Fl4GbLhn2UUphSkRPQPPvXl4Y9PSQjAkkSR2lDDDbu0ZcI55PQjmKx8vEFwDTEgY9xT+8CYlKzgc0fACNLJJZfqscrHxHOOOHlvAgggt7MwnpTEVqTBJHZZJZ5ZTRYlenL1exMMAAA2aLlSRKpfn2C.qq2CGVKDXDSPUjtc69niV0dVQcLRSjwDmk9qIhLzyy6DTwvYoWudmlV.V7HhVkd8pxInfn2GkzOnPF9o3Ob94mOREULN8WyXLWEEEUnLyJLhInJiHhK+MU3pRQ+98ao6ijYZOpHx8999PLgCxx2DhHWV0tFVkTPgNJoN8SQQtr96RN+7yG444cbZgWDM80oISl7TQnMQvHlfpNZXWcexGSC6py1OGQyRVSxAQSiIZee+RaXLsMYvfAG5x2DhH2WEaWakTPAQS+.SQjYJINy7skACHtKnSmNu344cRFiUZKl4m22uVAiXBpCHhbiia.pPTkhXyW5ZRNz.q558zgVgmLxahQdddUx10VYETPz6lPbF+TXsV3mBkNc57xbFqzCEQddek5nvHlf5BZXWkdLRatO8zjZ9xmxv7kuXLlSv4hYSXX3YtxahpluIRRkVPAQDEDDboC+TzbxjIOruNlJhDOVotLqIy7s6CeU3xHlt52L.TEnQiFyrMRYl+193leT+R7b5EWEQueG1GU05++lDcOcTK7MQRp7BJHhHsr9oKmX6vvPXRyDjXBPFm9qE6qhcUKPbYDSsuiC2E+9AfcMZXWMSh+tqMSdXX3YhHOm97OhldNHlji4itmNdJ8ias16p5UzoVHnHqUctwXtnHY7oh.ILq4vzes3PvZa+ZVVFwrp12Q.Hlfff6cTQ0y1EB4SjuDNWdfhHW566WYKW+lBcrZS62jgAAAU9qeUKDTPz6NoFlzLGn9p3jz9Ogno2wjwXFrMaABy7UNbS9M3BYf5.ttNk0Z2pUoPawQV4KwKVq8jx9hqZWPTTz.GlvbbUXOcjGpMBJHhHee+6bLdVGZs1R2RxZWfpn9KY3qhsRKPBCCa6vHSivEy.0Ez158gnXVaQa6swuunnnKzVb3JeIF444cDZ03hIJJ5hLLg4WpK2LTsRPAQuuk+RWRwCKiadycAZR9kUdUzxZsOsImBDl4YtSLW2wF.TkwZstplpyVQrpLXvfC60q2CtNmSOFty22+35xGFtNnaPTmW6pJaByzT6DTjH6ERaRSjjlYPPPvXee+iypEHLy21qWu0dTbUE9oKWHLhIn1QPPvXGi7dyMk38vvv1SlL4WTpwxlno2UMQzWpC87eSP+98a4JILqClvLM0NAED8dRZ5RTwYE0cYQQf40BDhnSmLYxuV0M6pJF4CA4CLhInNitBARet1Uqiv8ACFbnFTUNS8RQjghHGWU19kaahmnCGuV9XcTPVsTPAQYmjlFi4JL4GYShVfLL8WSOo5gUoZEZhxAiXB.J568mYLRe80WWoDzTqJwytBpJhdOBsOIHHX7p7yutQhEkV5I5Xzm9zmpkQQdsUPAQumjlyDTR5V2r8d3PpTf1BjSb8ZmxRUsBXDS.vMpQxGm7wzwcuYd+YjppDy78IhL1ZsmfHzd43s2dy0Dc7hHRswDlooVKnfnoIDYF6xhGv3jNeBBBtlY93LBBqbWsBXDS.HaDQl4tcMFSt760hpJgFTUGCeJsbDEEMflcs.DGG4i2OGU6ep8BJHhHee+Ntl7CLNoKl3fvxkgMUla0JfQLAf4ilgNCS8vmNupnlipR7BQzWPPUs73Z7PIp9MQGt.BJTzI+.iS5JPmNcdIHH3Rq0lUrceHQzCQQQeXknCiXB.4Ciw3LT9b8b60q2oSlL4WYUUBhnG877NBFub4QW3Wy75tt0UueObHUn.BJThim6LFmTHpHGDDDLbdUqfYtMy7ywSRCLhI.jOTSjeexGiYtURCjGFF1LJJ5IhnGxXBNdgH5Kc61s11i+0gd85cZFK7q6gXhov66CfhF862uUViAT2tcqEwm5l.0nkCbUtUhlZDLGK+qQ999Gu8O5.4kvvvqMFy6UQRDYnuu+I6yio5J5TE7qjWaRMA3wDQmk7embvie5SeBs2XEIqOWPD4dee+Z4Dc3BTghTn2IfKgCmpFwAjCRTsBmSBRF80Es5..x.sJpeO4ioAK2yYIlHdBNPUIVcliXhQPLwGABJbPPPvPq0NyaTXlOChJxOp2JhmDjgy64JhLpQiF0ZCMA.KBcpzFm7wb0dChllqDXBNVOlmXBOOOTotT.AEYflQEPTwFfyO+7QZtUzIiT1L1qJOiPEC.xF0KWim2yQDYHy7wAAAWipRr5jUJXFKl.u1NKPPwbHqfuREUrwVHV0ETiKkoyxYlapqF8mQvhA.+AcLPuV8PQaWOGcMi2w22+j593KttLmTv7Eiw.unjAPPwBXNAe0s3toWNbkHltfYtkwXdRGyz1a+iL.n3RXX3YZ3TcUVs2PYDl1f0mDhIlIELMFCDqMGffhbfF7U2m9w0H59rc+QT4jLle6abkcE5yusJrXvxD0v.PUfvvvyhhh9kwXxbZoRByb6Uc47AlBDSrd.AE4DHpX8vUhXRS2HeWGOMHyweEmYLleAgEf5.4QHgHxHWdRRDIWQxMXVfXh0GHnXI.hJVMxJQLsV6kD8moAwyy6HWu9FCDV.pxjSgDiUeRbbPPv8NFizlwAGGH+.wDaFffhkDHpX440Wecld+Jh78zKQmNc57huueGq0BgEfZC4THwK55E+nj9jnQiF24Hce+FR127SVhIHB6mikEHnXE.hJxO862uU5cJfHx34spj00idmEkeEwBK50q2Cv7lfxFKiPBOOuibcNiF1UeHP3zcPDZ8QNXdhIv94X4AQu8ZPTTz.WSs.di3eHJJ5ozi4l0ZOYYBaGc5PtJqwkKFc96+NV5QaNPzauYYvfAG95qudAy72l2DanQp82aznwc4YDEihhdN8GJZs1ipyqR6EADSr44esuO.Jy3662IJJhRKpPqTQy4cW30AzMyW6TO7iKax8oO+gKRXg93sihhFKhbSiFMdDyKNnHPXXXSl4qlLYxoFiYiIjHw22kLyOk7wXlGPDAweN.hI1NfJTrAHqJUTmWbLyaQFst20jJr3qKJSKzee2SDMieM.4CTgh0id85cpHx2xQ00VIgDo9c8.QzGFazksZf0Az3z9AWsYBhIVOfGJ1.jkmJpywzcdMh4pPPPvvbZdyCMFyEpANeBynOXWPbpVFEE8KZ5pDucVOWQjwhHWF6Qh0ohZwSMURzpT.TRraNZl7wEQdQiq762KGXUDPEJ1ffJULk9862RD44jOlHxXee+i1F+9zI83rE0W53iCQjePDcOpZwhAUnH+nUi3y4IMXEQFoBrueSdLDFFdqCSPeouu+caxeOkQlyh9BiF5FBHnXCybDULzyyqVrBg2DFwbUPM71opOKZtnmuHxPQje.uVjMPPw7IgX1ulm2yQD8n0Z+915bgrZ0nmm2Q042iqh8F.wDaWffhs.yQTQkeK0EFFdlwXRWl0G61s6W1kGGZ6M9JkpmxtPmi+GEQ9A527GABJlkDBW+lKS8klcsWdzTo8CiMp0ZuotZR7LtlDDSrE.BJ1R35jZhlJpvXLcphuIdaZDyUE8NH+Fy7YKpcHD8dKQd7fCN3GUw+MZYABJlRrHBiw7YJGhTIZ60Vi7PTTzuRWwj53XjNmqCO1XLeAmiuYAiM5VBee+6BCCeIsxXl4VVq8o986W4TF+5qudU5QhaSYDyUE828kDQWpiw5WmmI4XlaxLegHxE53mBwE0TRJh3s2d6TiYwdXOtZWFi46c61cu8dFl4KIhdH4iYLlaIh1oUJbeRctRw6KPEJ1xLuxswL2opDBS6ZiXtNrB8898JWXLl+tp7uY4g5VEJVkJQn7n0Z+YQZJA1WdYZeiVozagXhcOnBEaYBBBtue+9iR6tX8O+PXXXkXtmsV6sL+Q8ohHExIaQqZw0DQWGmoEDQmNuVhDW4BhnKhhhdgYdn0Z+ILzY4m986252+92mxL+42d6sV4oRDDM8CmHh9gHxiEwVIXLlKSKxWK++w6oCosNKXubbumm2k370sGnBE6HxZjkHp7OVoEEiXttrLi8WRzdkOjH5mUs69qJVgBsBUsYl+KZABISSYyiMtJ6eUM7llWfUU1uFaYAHnXGx7TOSD83m9zm5T1TOWDMh45xZT1ahn2GG0+lHZXYWfQUPPwfACN7s2dqs0Z+Kl414YxLRRYSDQRx37ywdddGW1tVy7Pqz3CYbCaHGN1Q.AE6XzSvcldd5c59kxzGD6JHcpZinVbkKnk7tYiIo.iFMZLpLcg7xnfhTUfn0xJffn2OW7mGbvAOV1DQjlz+aHQUqyQyxmZDUcqFSQEHnXOwbbfboY1nyxHlUs69IIZ+1+5pbmtwn8deDQz+HhLpHWEihtfhvvvlFiok0ZakP.wRK5S4QQj+tn5IhUE8lXdNYq.J6UQLlpv0QqR.AE6QxZFoIpbnr1kKxIh9RcYJHhuSXiw7YQj1qwGjQhHiXlGas1+gHZHQz3hvE6KRBJBCCaSD0jHp4FP7v6deoNL4NttK9xruBVf4KqrY8SQGHnXOSVQBKQE6S3y3BTEp6dcWiZJr1Ly+05JvHF0rmiEQ9eFiYj0ZeYWVQicsfBUjVSl4VhHGpBGZl2w6cdHhLlHZnHxeWGmNGW2..y7wksO3cAlur1rhCJhfwFcOS2tcere+9iccBhtsRaUzlaZ8tCtJ8iWTGSzcE5ElGQDcGQyHvn0p7ghwe.P7H4ZLFpWudDQuK1fT+YPwBNHZ5FYcs9+LaATyt1hnoA7lJX3+P+opCMS97SOFxKKIq.g0ZGUDp3y9DQjabjKE2RDUZtIfvvvyzQTuTcCX0EPEJJHrfR3Un5GXU2jWaKR2u+4kXmaJzjaL46aFKh7+b7TG556WC+qyR7yajHxkDQjwXNzZsy79UspBwb3p50jkAQjwLyihaYTQTPUQfL7bPonMktL.dLkgVDWG.BJJXjkIiHpXL9S5GJ9qjOVU2HlaSTis1LgoB2Hk2uJSroVUgQktImYeRVm+VDSz1XJS2rUcGHnn.x7FCJZOmWE0ciXtqvgAD2I2oeQgDUV4c+ivLOFevw5SYpBiKHeIPLZWv.BJJnr.iGsWbwrtRv+vBGptaDycMwlVj9iXiXOHP6hVnroHYqXh8.BoscAsqX6RVgQmmm2QEoOb1kvmXfeIJl.AEEXVPHX8BQzM6pVf3ZV1IpdtRjK5jPzAQ+Q7AQDQFi4+Jhj9t8V41rDaLzTj1mFu+bfXghAtpBp0ZuKHH3x80wTLK55dhHWB+RTLABJJALOk5zNpEHkoxjB1bTjxgBvlknnnmS2Fs88MHrfVbL1XLeAs8p3R9Vqdf8JAAAWas1SzpRjlSmLYxy862eq0ec0HWePLgHx3FMZf7wG.JoDOsNIgYNKuas0QmhCmKPQhnG877JcYlQcCHnnjPPPvPQjiUGt+AXlaJh7bXX30aie2ttHCyLVCv.PIF8ZJCS9XLysUCAuyne+9shhhdNqQBUD4xtc6hvppD.DTThHHHXruu+wVq8FWeciwbUTTzSZOz2HzqWuSS2KSQjgXpN.fxOtBitcYUJhhhtvZsYMRniYlOdeOp7f7CDTTBYds.QWZUOGEE4Ts+xvfACNTDYlcMRcOQLAfpBAAAisV6G9.al4lgggmsM+8NXvfC0QPOyTuDs3n7ADTTRIHHXnmm2QDQyTo.l4CYlusWudOLXvfUdeR75qudgio53FLUG.P0gFMZbS5aNgY9104ZGyid85cpN1psS+0DQdwZsc7882aYsCX0ABJJwzoSmW51s6WDQtbNF17WZ9QrT.iXB.0C5zoyKhHeO4iwLe3qu95ZWkyjLXvfC60q2CDQYFTU5JU+9M4uWvtCHnnBfuu+cFi4jLLr4gDQOrrUq.FwD.pODDDbstMVeGiwb0lxOVwUkfHx4M2Xs1a788OFU+rbCDTTQ37yOez7LrIsDUq.FwD.pevLOyXjZLlY7P0xPdpJAy7wHOapF.AEULBBBtlY93z2sAQerZEYcmGvHl.P8jtc69nijO8zUcLRyQUItyyyCK1qJDPPQEjyO+7QdddGm181I3zrlDjLLh4cnTj.P0Giw3JrqxJkdcRXXXynnnmnrqJwXq0dRPP.ZgZECHnnhRmNcdIHH3Rc7RGm9qGOIHQQQOEmxlYXDyWZznQVsQA..UHN+7yGIhbexGSC6pyxy2eXX30LyOm0hpSqJwwXmtTM4esuO..aWzSbOJq8ABybaMkMuKivkA2EA.TiPD4FZZULeu5BLyWMXvfGy5ZA5N33VWWCQ+YNVDoCDRTsAUnnlPBuU3rekFi4BWFwDivE.TuHHHXriwHsoqwHUCnpA5N3voXBcBNNBhIp9.AE0HhmDj4jaEe.W8SE..UeZznwcoaUJy72RZl6nnnKz.p5LW+LDQFhI3ndADTTCw22+NQjiIGorYR98u+8W2VokG..Jtngc0G7Nk56pqBCCaqq97rhM6WDQtz22GSvQMCHnnlRPPv33T1LqmiwXtXxjI+Zamq+..n3QPPv8N1FomMu1an6fiivB8pdBDTTyQOw+KtlDDhldWIFiYPTTzu10q0X..reIcUJlyyaj0ZOA6fi5MPPAf51s6iZtULyRBJFl4lFi4oM85QG..EWxpRDwjn8FXTPAXrQASQuqhqIhtVGArAoC3Jhde8n+qnnn6EQvlGE.pfDFFdFy7UttFPLZ6MvXkCdGHn.LCIytBl4u4x3ULymwLeVXX3MMZz3NbQE.n7idyDWkUvTEi0ZuASuAHMnkGfLIHH3ZOOuilSDdSFi4J03lWiIBA.JmnStwSpgKaOmm5iVq8HHl.3Bdee..JGnwx8sTFK5GhduepeGUrn5P5DVUDYnuu+I6yiIvli7TQB0WU2344cONuFLOPKO.4B0qDeYdW.JdN0mLYx2BCCgvB.nfRdERfaP.rL.AEfkB0eECWfwMgvB.n.Rd8HALbIXU.BJ.qDILtYltAGBK.fhAKiPBL8VfUE3gBvFgbNlYunqF4uiKXUN.dnnbSud8NUD4aPHAXW.DT.1njGgEDgKfUV.BJJmfyCA6CPKO.aTz0c98K5BZw4XQTTzP8BZC2gGl.PkiACFb3qu95EYkcLIABI.aCffBvVgkPXQal41QQQiEQtoQiFOBeV..4m9862xZse6s2d6LiY9QKDDR.1lfVd.1IrDlBC9rn.AZ4QwEUr9Wy44TemH5dbNEXaBpPAXmPpwM8qLym454oSFxEDQWzqWuGIh9Q2tcebGdnB.EVzEyWrPhly64JhLVD4GX5p.6JffBvNkDBKtgH5apWJxpeumRDcp1NjeP3Nr.0T50q2oDQeklSR0FiHxHQjuqscD.1YfVd.1qLXvfCmLYxYzTwEMyw2xiVq8m3hk6FPKO1erLUifn28GwOfAmA6KffBPgg7Ny7D8GuVbvAG7iyO+7Q6fCuZIPPwtEcRMNMOdifH3OBPwBHn.T3PuyrE0Nj2QDYLQz2EQdDWTcyBDTraPES+4r7VTZDQFpUi39s6QF.jeffBPgl75j8Xh6eLF+zMCPPw1i3w8jH5zbJbFS.EnPCDT.JEjnpEmlSuVPj52BHtX0ABJ1rzue+V+92+9qqx6iQ0H.EcffBPoiks7vJOJh72nsHKGPPw5SXXXahnOuLhHhG4SBdi.Th.BJ.kVVVCrEiHxHhneXLlgvPmyGHnX4YvfAG91au0VD4yTNamAQSaoAQziFi4638kfxHHGJ.kVz1XbOMMhuaxLeJQzWYlaMuuO8q2RDgzLt3Qiw72H.s.qJwu+iY9ud6s2NkHhXdw2uVrHBl4e566i2+AJ0fJT.pbrLhKRiHxPhnehpWLETgB2DWEBq09WKoeH9fHBHhETk.BJ.UZVSwEuPp2KHhFVG6kMDT7GTuPzlY9uVlVrQDDQ.pG.AEfZC5jhz1XLelxQDFmFMuKFVmDXTmETrNBHH5ciUh1oApM.AEfZIoLNW6koj0wHh7By7Pc5QFUEi735hfhvvvlFiok1Bi1Ka0rhAsLCTmAlxDTKQMz4i5+EGxPsooi2W677yPcu+oZOzod85EGrVCIh9mCN3fQ3CUJdnSGTKZZ0p9uhHsimDCiwrT+rhqZEy7O+zm9zPj2If5LPPA.PDoev+Hhn6HZZVWrJ2sJybq3muHRrHigDQiIh9GQjQMZzXD9fmcCIp7PKl4+hHp4au8VyjBGxyzXDSppRgLMA.R.DT..NP648iDMii9W5xgmrhGLyzau8FEEEMlHZr5GiwDQigPiUGMAJOjl19p+CQTyjuturUdHljBHLFyvtc6hJNA.Y.DT..KfzsGgnOZXOhnV4M7hhQ8rwG9Pu2d6s2qnAy7KVq8eHUrAQz359cCqulSDQsIh92pvtCYlaIhrxhFRhF5YiDQ96CN3fQP.A.jeffB.XEPMf4v3+tdGxsHh9uZaOZup+ri+dMFyGlDEUrwXhnwIDbPFiYj0ZeIwwUoBc5aZRzzVFIhbH8GACz57Z47PDYLy7H80wgnBQ.v5AlxC.XKQZQFzJTIi0A06FDQDkT.RBFq+WlnwZ9YI9YNRD4xb7qucp+9+NUqhZtJSVypBDO..aeffB.XGRh6F2Yu9AqGwUvIo2TJiUsA.Ji.AE.PAf3QYLtj+p2L1Zk6uLSrnAZpvg+mwXFwLOFinK.reABJ.fR.oLjHo4mvgjZJw80w0lFMhpGo+4QDQ+eDLlJ.TJ.BJ.fJBIM2n9+F+mSJ.4c1lU+HQUDR9XwBDhYX7e.sk..J+7+Ck8L1.J8S2m.....jTQNQjqBAlf" ],
					"embed" : 1,
					"id" : "obj-47",
					"maxclass" : "fpic",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 18.9375, 14.75, 45.0, 45.0 ],
					"pic" : "hoa-icon.png"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"linecolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 33.0625, 623.0, 782.0, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-38",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.66 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 32.0625, 622.0, 782.0, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.754705,
					"frgb" : 0.0,
					"id" : "obj-66",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 88.5, 41.75, 185.0, 21.0 ],
					"text" : "A high order ambisonics library",
					"textcolor" : [ 0.999903, 1.0, 0.99983, 1.0 ],
					"varname" : "autohelp_top_digest[1]"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 20.871338,
					"frgb" : 0.0,
					"id" : "obj-57",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 87.5, 12.75, 117.0, 30.0 ],
					"text" : "hoa.library",
					"textcolor" : [ 0.999903, 1.0, 0.99983, 1.0 ],
					"varname" : "autohelp_top_title[1]"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 3,
					"fontname" : "Arial",
					"fontsize" : 20.871338,
					"frgb" : 0.0,
					"id" : "obj-2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 89.5, 14.75, 117.0, 30.0 ],
					"text" : "hoa.library",
					"textcolor" : [ 0.0, 0.0, 0.0, 0.5 ],
					"varname" : "autohelp_top_title"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.754705,
					"frgb" : 0.0,
					"id" : "obj-3",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 89.5, 42.75, 185.0, 21.0 ],
					"text" : "A high order ambisonics library",
					"textcolor" : [ 0.0, 0.0, 0.0, 0.5 ],
					"varname" : "autohelp_top_digest"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 0,
							"revision" : 8
						}
,
						"rect" : [ 497.0, 168.0, 292.0, 315.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 173.0, 58.0, 64.0, 20.0 ],
									"text" : "hoa.spat"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-3",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 191.0, 89.0, 80.0, 20.0 ],
									"text" : "hoa.control"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 157.5, 174.333344, 84.0, 22.0 ],
									"text" : "prepend set"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-19",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 125.0, 143.0, 32.5, 18.0 ],
									"text" : "set"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-15",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 50.0, 100.0, 97.0, 20.0 ],
									"text" : "route blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 27.0, 240.5, 74.0, 20.0 ],
									"text" : "prepend set"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 27.0, 215.5, 79.0, 20.0 ],
									"text" : "route symbol"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 26,
										"data" : [ 											{
												"key" : "hoa.encoder~",
												"value" : [ "hoa.encoder~ creates the spherical harmonics of a signal depending of an given order and the position on a circle." ]
											}
, 											{
												"key" : "hoa.decoder~",
												"value" : [ "hoa.decoder~ decodes an ambisonic soundfield for a given number of loudspeakers. First argument is the order of the ambisonic soundfield, second argument is the number of loudspeakers, it must be equal or superior to the number of harmonics (2 * order + 1)." ]
											}
, 											{
												"key" : "hoa.rotate~",
												"value" : [ "hoa.rotate~ allows you to rotate the ambisonic soundfield." ]
											}
, 											{
												"key" : "hoa.plug~",
												"value" : [ "hoa.plug~ facilitates the modularization of patches for ambisonic processing. The number of inlets and outlets is dependant on the number of inlets and outlets objects within its subpatch window, the ambisonic order andf the 1st argument.\nThe 2nd argument is the name of the patcher to load and the 3rd argument is the mode pre, no or post decoding." ]
											}
, 											{
												"key" : "hoa.connect",
												"value" : [ "hoa.connect helps to connect the hoa externals together. You must drag-select the objects then bang the hoa.connect to connect the objects together. 1st argument is the ambisonic order and the 2nd is the number of decoder outputs and dac inlets." ]
											}
, 											{
												"key" : "hoa.dac~",
												"value" : [ "hoa.dac~ makes easier the setting of the channels. It works like a dac~ object but you can use the matlab syntax :  to set the loudspeakers routing." ]
											}
, 											{
												"key" : "hoa.binaural~",
												"value" : [ "hoa.binaural~ virtualizes ambisonic soundfield for two headspeakers. It uses hrtf to perform FIR filtering on the incoming signal. Hrtf are extracted from the sipic hrtf database. hoa.binaural~ works up to the order 35 and at 44100 Hz only." ]
											}
, 											{
												"key" : "hoa.pi",
												"value" : [ "hoa.pi is for peoples that never remember more than 4 decimals or want to initialize a good Pi number. " ]
											}
, 											{
												"key" : "hoa.scope~",
												"value" : [ "hoa.scope~ displays the harmonics of an ambisonic soundfield on a circle. The number of harmonics is defined at the object creation with the attribute @order and create order * 2 + 1 inputs (ex : hoa.scope~ @order 7)." ]
											}
, 											{
												"key" : "hoa.projector~",
												"value" : [ "hoa.projector~ discretizes the ambisonic soundfield into an array of virtual loudspeakers and gives a access to a new sound domain." ]
											}
, 											{
												"key" : "hoa.recomposer~",
												"value" : [ "hoa.recomposer~ recomposes a plane wave decomposition into circular harmonics and allows you to perform a fish eye operation." ]
											}
, 											{
												"key" : "hoa.meter~",
												"value" : [ "hoa.meter~ displays the peak levels for a circurlar array of loudspeakers. It computes and displays the energy vector. The number of loudspeakers is defined at the object creation with the attribute @ls and the offset of the loudspeakers is defined with the attribute @offset (ex : hoa.meter~ @ld 16 @offset 0.5)." ]
											}
, 											{
												"key" : "hoa.record~",
												"value" : [ "hoa.record~ creates an sfrecord~ object with the best arguments to record of an ambisonic soundfield. The limit defined in Max is 15 inputs then the maximum order can be 7." ]
											}
, 											{
												"key" : "hoa.play~",
												"value" : [ "hoa.play~ creates an sfplay~ object with the best arguments to play of an ambisonic soundfield." ]
											}
, 											{
												"key" : "hoa.optim~",
												"value" : [ "hoa.optim~ applies an optimization to the cylindrical harmonics. It can be basic for no optimization, maxRe or inPhase." ]
											}
, 											{
												"key" : "hoa.spat",
												"value" : [ "hoa.spat is a 2D spatialization user interface tool, allow you to spatialize several point sources. You can control sources with a list of value in the first inlet, zoom in/out, add or remove loudspeakers, modify the distance between listener and loudspeaker..." ]
											}
, 											{
												"key" : "hoa.control",
												"value" : [ "hoa.control displays the representation of the harmonics of an encoded ponctual sound for a given order, optimization, azimuth value and wide value. It can be used to understand of the encoding behavior, the optimization and fractionnal order effect (wider) or as a controller for the super", "encoder set." ]
											}
, 											{
												"key" : "hoa.stereo~",
												"value" : [ "hoa.stereo~ decodes an ambisonic soundfield for stereophonic system." ]
											}
, 											{
												"key" : "hoa.convolve~",
												"value" : [ "hoa.convolve~ uses FIR and FFT filtering to apply reveberation on harmonics dependant signals. The zero latency convolution is optimized with the Gardner algorithm and uses the circular harmonics behavior to reduce the number of FFT convolution." ]
											}
, 											{
												"key" : "hoa.irconverter~",
												"value" : [ "hoa.irconverter~ create the circular harmonic dependant signals of a discrete circular impulse response for ambisonics processing. It facilitates the convertion for the use of hoa.convolve~ and allows you to changes the incidence angles of the discrete impulse response." ]
											}
, 											{
												"key" : "hoa.wider~",
												"value" : [ "hoa.wider~ can be used to make more wide the diffusion of a localised sound. The order depending signals are weighted and appear in a logarithmic way to have linear changes." ]
											}
, 											{
												"key" : "hoa.delay~",
												"value" : [ "hoa.delay~ allows you to delay the differents harmonics." ]
											}
, 											{
												"key" : "hoa.grain~",
												"value" : [ "hoa.grain~ synthesizes a diffused sound field. It uses delay lines and amplitude modulation to create streams of grains. The parameters are scaled depending to the orders to generate a granular sound field." ]
											}
, 											{
												"key" : "hoa.mirror~",
												"value" : [ "hoa.mirror~ applies a weight on the negatives harmonics to add the mirror image of a soundfield to itself. " ]
											}
, 											{
												"key" : "hoa.mixer~",
												"value" : [ "hoa.mixer~ helps to understand ambisonics and the behavior of the circular harmonics." ]
											}
, 											{
												"key" : "hoa.reverberation~",
												"value" : [ "hoa.reverberation~ use a algorithm based on feedback network delay and doppler effect to simulate a room reveberation." ]
											}
 ]
									}
,
									"color" : [ 0.590533, 0.704632, 0.839216, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 16.680918,
									"id" : "obj-21",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 27.0, 174.333344, 120.0, 25.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll description"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-26",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-28",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 157.5, 276.5, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-29",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 27.0, 276.5, 25.0, 25.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-15", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ -67.875, 514.5, 79.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 14.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 14.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p description"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-25",
					"linecolor" : [ 1.0, 1.0, 1.0, 0.5 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 36.5, 202.257935, 579.0, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"linecolor" : [ 0.0, 0.0, 0.0, 0.3 ],
					"maxclass" : "live.line",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 35.5, 201.257935, 579.0, 5.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ -83.9375, 203.257935, 77.0, 20.0 ],
					"text" : "prepend nav"
				}

			}
, 			{
				"box" : 				{
					"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
					"fadeunselect" : 1,
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"htabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
					"htextcolor" : [ 1.0, 1.0, 1.0, 0.95 ],
					"id" : "obj-20",
					"margin" : 0,
					"maxclass" : "tab",
					"multiline" : 0,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 25.5, 165.257935, 605.125, 30.242065 ],
					"rounded" : 0.0,
					"spacing_x" : 1.0,
					"spacing_y" : 0.0,
					"tabs" : [ "All", "Basics", "GUI", "Special", "Utility", "Effects", "Operators" ]
				}

			}
, 			{
				"box" : 				{
					"clickthrough" : 1,
					"embed" : 1,
					"id" : "obj-22",
					"maxclass" : "bpatcher",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "blank" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 0,
							"revision" : 8
						}
,
						"rect" : [ 65.0, 272.0, 605.0, 288.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 14.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-47",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 3881.0, 324.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-48",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 3881.0, 295.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-45",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 3217.0, 338.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-46",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 3217.0, 309.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-42",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 2556.0, 338.0, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-44",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 2556.0, 309.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-38",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 1894.0, 343.5, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-40",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 1894.0, 307.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-34",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 1241.0, 343.5, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-36",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 1241.0, 307.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "blank" ],
									"patching_rect" : [ 520.0, 372.5, 52.0, 22.0 ],
									"text" : "t blank"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 520.0, 336.0, 80.0, 22.0 ],
									"text" : "route -1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-43",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 679.0, 336.0, 70.0, 20.0 ],
									"text" : "renumber"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-41",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 355.0, 487.0, 177.0, 20.0 ],
									"text" : "hoa.projector~"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 5,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.delay~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.grain~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.mirror~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.mixer~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.reverberation~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-39",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 3942.0, 325.0, 128.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-effects"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 6,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.plug~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.connect" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.dac~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.pi" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.record~" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.play~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-37",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 3278.0, 338.0, 119.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-utility"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 6,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.projector~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.recomposer~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.binaural~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.stereo~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.convolve~" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.irconverter~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-35",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 2617.0, 338.0, 130.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-special"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 4,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.scope~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.meter~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.spat" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.control" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-33",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 1955.0, 343.5, 105.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-gui"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 5,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.encoder~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.decoder~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.rotate~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.optim~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.wider~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 1302.0, 343.5, 126.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-basics"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-32",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 320.5, 422.0, 91.0, 22.0 ],
									"text" : "route symbol"
								}

							}
, 							{
								"box" : 								{
									"coll_data" : 									{
										"count" : 21,
										"data" : [ 											{
												"key" : 0,
												"value" : [ "hoa.encoder~" ]
											}
, 											{
												"key" : 1,
												"value" : [ "hoa.decoder~" ]
											}
, 											{
												"key" : 2,
												"value" : [ "hoa.rotate~" ]
											}
, 											{
												"key" : 3,
												"value" : [ "hoa.plug~" ]
											}
, 											{
												"key" : 4,
												"value" : [ "hoa.connect" ]
											}
, 											{
												"key" : 5,
												"value" : [ "hoa.dac~" ]
											}
, 											{
												"key" : 6,
												"value" : [ "hoa.binaural~" ]
											}
, 											{
												"key" : 7,
												"value" : [ "hoa.pi" ]
											}
, 											{
												"key" : 8,
												"value" : [ "hoa.scope~" ]
											}
, 											{
												"key" : 9,
												"value" : [ "hoa.projector~" ]
											}
, 											{
												"key" : 10,
												"value" : [ "hoa.recomposer~" ]
											}
, 											{
												"key" : 11,
												"value" : [ "hoa.meter~" ]
											}
, 											{
												"key" : 12,
												"value" : [ "hoa.record~" ]
											}
, 											{
												"key" : 13,
												"value" : [ "hoa.play~" ]
											}
, 											{
												"key" : 14,
												"value" : [ "hoa.optim~" ]
											}
, 											{
												"key" : 15,
												"value" : [ "hoa.spat" ]
											}
, 											{
												"key" : 16,
												"value" : [ "hoa.control" ]
											}
, 											{
												"key" : 17,
												"value" : [ "hoa.stereo~" ]
											}
, 											{
												"key" : 18,
												"value" : [ "hoa.convolve~" ]
											}
, 											{
												"key" : 19,
												"value" : [ "hoa.irconverter~" ]
											}
, 											{
												"key" : 20,
												"value" : [ "hoa.wider~" ]
											}
 ]
									}
,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 581.0, 372.5, 101.0, 22.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1
									}
,
									"text" : "coll maptab-all"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.32331, 0.623465, 0.84, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hidden" : 1,
									"id" : "obj-73",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 0,
											"revision" : 8
										}
,
										"rect" : [ 50.0, 94.0, 337.0, 182.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"boxes" : [ 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-2",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 105.0, 60.0, 83.0, 20.0 ],
													"text" : "prepend help",
													"varname" : "phelp"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-3",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 105.0, 90.5, 56.0, 20.0 ],
													"text" : "pcontrol"
												}

											}
, 											{
												"box" : 												{
													"comment" : "From umenu label out",
													"id" : "obj-4",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 105.0, 15.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-3", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-2", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-4", 0 ]
												}

											}
 ]
									}
,
									"patching_rect" : [ 290.5, 313.5, 69.0, 20.0 ],
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"description" : "",
										"digest" : "",
										"fontface" : 0,
										"fontname" : "Arial",
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"tags" : ""
									}
,
									"text" : "p see_help"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-31",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "int", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 447.0, 336.0, 50.0, 22.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-22",
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 320.5, 484.5, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-109",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 4331.0, 130.0, 144.0, 33.0 ],
									"text" : "Operators and tools shortcuts for hoa.plug~ :",
									"textcolor" : [ 0.375912, 0.375912, 0.375912, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 424.0, -110.0, 69.0, 22.0 ],
									"text" : "route nav"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-30",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 949.0, -55.0, 81.0, 17.0 ],
									"text" : "offset -4000 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-29",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 861.5, -55.0, 81.0, 17.0 ],
									"text" : "offset -3300 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-28",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 774.0, -55.0, 84.0, 17.0 ],
									"text" : "offset -2636. 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-27",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 686.5, -55.0, 81.0, 17.0 ],
									"text" : "offset -1975 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-24",
									"maxclass" : "newobj",
									"numinlets" : 8,
									"numoutlets" : 8,
									"outlettype" : [ "bang", "bang", "bang", "bang", "bang", "bang", "bang", "" ],
									"patching_rect" : [ 424.0, -82.0, 631.5, 19.0 ],
									"text" : "sel 0 1 2 3 4 5 6"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 599.0, -55.0, 81.0, 17.0 ],
									"text" : "offset -1313 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-25",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 511.5, -55.0, 75.0, 17.0 ],
									"text" : "offset -660 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.595187,
									"hidden" : 1,
									"id" : "obj-26",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 424.0, -55.0, 58.0, 17.0 ],
									"text" : "offset 0 0"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-128",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 4174.0, 220.0, 90.0, 20.0 ],
									"text" : "hoa.snapshot~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-127",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4264.0, 115.0, 46.0, 20.0 ],
									"text" : "hoa.*~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-126",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4264.0, 160.0, 48.0, 20.0 ],
									"text" : "hoa.!-~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-125",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4099.0, 220.0, 48.0, 20.0 ],
									"text" : "hoa.!/~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-124",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4234.0, 190.0, 55.0, 20.0 ],
									"text" : "hoa.+=~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-123",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4234.0, 85.0, 48.0, 20.0 ],
									"text" : "hoa.+~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-122",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4024.0, 205.0, 51.0, 20.0 ],
									"text" : "hoa.!=~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-121",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4189.0, 160.0, 52.0, 20.0 ],
									"text" : "hoa.%~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-120",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4129.0, 160.0, 45.0, 20.0 ],
									"text" : "hoa.-~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-118",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4144.0, 190.0, 55.0, 20.0 ],
									"text" : "hoa.<=~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-119",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4069.0, 175.0, 48.0, 20.0 ],
									"text" : "hoa.<~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-117",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 4024.0, 130.0, 78.0, 20.0 ],
									"text" : "hoa.name2~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-116",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 4174.0, 130.0, 78.0, 20.0 ],
									"text" : "hoa.name1~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-115",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4174.0, 100.0, 55.0, 20.0 ],
									"text" : "hoa.>=~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-114",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4114.0, 115.0, 48.0, 20.0 ],
									"text" : "hoa.>~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-113",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4054.0, 100.0, 55.0, 20.0 ],
									"text" : "hoa.==~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-112",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4189.0, 55.0, 44.0, 20.0 ],
									"text" : "hoa./~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-111",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 4099.0, 70.0, 64.0, 20.0 ],
									"text" : "hoa.amp~"
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.390905, 0.495765, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-110",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 4039.0, 55.0, 46.0, 20.0 ],
									"text" : "hoa.all"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-2",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 424.0, -141.0, 25.0, 25.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 11.934731,
									"hidden" : 1,
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 424.0, -29.0, 67.0, 20.0 ],
									"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
									"text" : "thispatcher"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-19",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 3297.0, -26.0, 26.0, 20.0 ],
									"text" : "FX"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-18",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 3300.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.delay~", "hoa.grain~", "hoa.mirror~", "hoa.mixer~", "hoa.reverberation~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1975.25, -26.0, 50.0, 20.0 ],
									"text" : "Special"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-17",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1975.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.projector~", "hoa.recomposer~", "hoa.binaural~", "hoa.stereo~", "hoa.convolve~", "hoa.irconverter~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 2636.0, -26.0, 40.0, 20.0 ],
									"text" : "Utility"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-15",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 2636.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.plug~", "hoa.connect", "hoa.dac~", "hoa.pi", "hoa.record~", "hoa.play~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-11",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1313.0, -26.0, 32.0, 20.0 ],
									"text" : "GUI"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-12",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1313.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.scope~", "hoa.meter~", "hoa.spat", "hoa.control" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-8",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 660.0, -20.75, 46.0, 20.0 ],
									"text" : "Basics"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-10",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 660.0, 0.0, 600.0, 280.0 ],
									"rounded" : 0.0,
									"spacing_x" : 15.0,
									"spacing_y" : 15.0,
									"tabs" : [ "hoa.encoder~", "hoa.decoder~", "hoa.rotate~", "hoa.optim~", "hoa.wider~" ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"hidden" : 1,
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 11.0, -20.75, 24.0, 20.0 ],
									"text" : "All"
								}

							}
, 							{
								"box" : 								{
									"border" : 1,
									"button" : 1,
									"clicktabcolor" : [ 0.392157, 0.494118, 0.666667, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hovertabcolor" : [ 0.392157, 0.494118, 0.666667, 0.9 ],
									"hovertextcolor" : [ 1.0, 1.0, 1.0, 0.9 ],
									"id" : "obj-4",
									"margin" : 0,
									"maxclass" : "tab",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 0.0, 0.0, 600.0, 280.0 ],
									"rounded" : 6.0,
									"spacing_x" : 20.0,
									"spacing_y" : 5.0,
									"tabs" : [ "hoa.encoder~", "hoa.decoder~", "hoa.rotate~", "hoa.plug~", "hoa.connect", "hoa.dac~", "hoa.binaural~", "hoa.pi", "hoa.scope~", "hoa.projector~", "hoa.recomposer~", "hoa.meter~", "hoa.record~", "hoa.play~", "hoa.optim~", "hoa.spat", "hoa.control", "hoa.stereo~", "hoa.convolve~", "hoa.irconverter~", "hoa.wider~" ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-10", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-10", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-12", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-12", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-46", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-15", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-15", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-17", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-17", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-48", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-18", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-18", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-25", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-27", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-30", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-24", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-27", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-28", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-41", 1 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-33", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-35", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-13", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-36", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-34", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-37", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-4", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-4", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-73", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-4", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-40", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-40", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-42", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-43", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-35", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-44", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-45", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-37", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-46", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-45", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-48", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-48", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-24", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 25.5, 210.5, 605.125, 288.0 ]
				}

			}
, 			{
				"box" : 				{
					"handoff" : "",
					"hilite" : 0,
					"id" : "obj-63",
					"maxclass" : "ubutton",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "", "int" ],
					"patching_rect" : [ 692.0625, 43.75, 96.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 604.529907, 123.725479, 92.470032, 20.274523 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-65",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 717.729187, 68.75, 261.5, 26.0 ],
					"text" : ";\rmax launchbrowser http://www.mshparisnord.fr/hoalibrary/en/"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.160198,
					"hidden" : 1,
					"id" : "obj-56",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ -83.9375, 289.0, 45.0, 17.0 ],
					"text" : "onecopy"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Goudy Old Style",
					"fontsize" : 15.0,
					"frgb" : 0.0,
					"id" : "obj-5",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 13.9375, 81.5, 854.0, 57.0 ],
					"text" : "The hoa.library is a set of externals that encodes a signal in ambisonic spherical harmonics and decodes the ambisonic soundfield for a circle array of loudspeakers. This library allows you to synthesize, transform and modulate sound fields. It has been elaborated to facilitate the use of the sphericals harmonics and the routing in the ambisonics domain.",
					"textcolor" : [ 0.27596, 0.276002, 0.27594, 1.0 ],
					"varname" : "autohelp_top_description"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-77",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 18.0625, 156.257935, 622.0, 342.242065 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-4",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 651.0, 356.5, 206.0, 142.0 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-14",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 662.0, 165.257935, 154.5, 33.0 ],
					"rounded" : 0,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.94324, 0.954082, 0.954082, 1.0 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-26",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 13.9375, 81.25, 849.5625, 58.25 ],
					"rounded" : 15,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.392157, 0.494118, 0.666667, 0.5 ],
					"bordercolor" : [ 0.999903, 1.0, 0.99983, 1.0 ],
					"id" : "obj-46",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 10.9375, 9.75, 298.5625, 55.0 ],
					"rounded" : 15
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-67",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 692.0625, 43.75, 96.0, 20.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.0, 0.0, 0.0, 0.05 ],
					"bordercolor" : [ 0.235294, 0.235294, 0.235294, 0.2 ],
					"id" : "obj-69",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 797.0625, 43.75, 65.0, 20.0 ],
					"rounded" : 6,
					"shadow" : -1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-10", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-52", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-55", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-63", 1 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "hoa.all.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.amp~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.div~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.equals~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.greaterthan~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.greaterthaneq~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.name1~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.name2~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.lessthan~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.lessthaneq~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.minus~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.modulo~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.notequals~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.plus~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.plusequals~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.rdiv~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.rminus~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.times~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa.snapshot~.maxpat",
				"bootpath" : "/Applications/Max6/Cycling '74/HoaLibrary/operators",
				"patcherrelativepath" : "../../../../../../../../../../../../Applications/Max6/Cycling '74/HoaLibrary/operators",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "hoa-icon.png",
				"bootpath" : "/Users/elioton/Documents/programmation/CICM/sourceTree/HoaLibrary/MaxMsp/Max/patches/extras/hoaExtras",
				"patcherrelativepath" : "",
				"type" : "PNG ",
				"implicit" : 1
			}
 ]
	}

}
