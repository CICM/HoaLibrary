{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 1,
			"revision" : 5,
			"architecture" : "x64"
		}
,
		"rect" : [ 286.0, 145.0, 1154.0, 680.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"id" : "obj-53",
					"maxclass" : "hoa.meter3D~",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 281.0, 266.0, 133.0, 133.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 152.0, 211.0, 147.0, 147.0 ],
					"spherecolor" : [ 0.0, 0.9, 0.9, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "cam",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-63",
					"lock" : 1,
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 500.0, 157.0, 150.0, 19.0 ],
					"text_width" : 35.0
				}

			}
, 			{
				"box" : 				{
					"attr" : "spherecolor",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-64",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 500.0, 91.0, 150.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "vectors",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-65",
					"lock" : 1,
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 500.0, 122.0, 82.0, 19.0 ],
					"text_width" : 56.0
				}

			}
, 			{
				"box" : 				{
					"attr" : "bgcolor",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-66",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 500.0, 58.0, 150.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "spherecolor",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-68",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 281.0, 91.0, 150.0, 19.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-66", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-68", 0 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "hoa.meter3D~.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
