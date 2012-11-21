/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
#include "hoa.ctrl.encoder.h"

int main()
{
	t_class *c;

	c = class_new("hoa.ctrl.encoder", (method)controler_encoder_new, (method)controler_encoder_free, (short)sizeof(t_controler_encoder), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);

	class_addmethod(c, (method)controler_encoder_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)controler_encoder_paint,			"paint",		A_CANT,	0);
	class_addmethod(c, (method)controler_encoder_notify,		"notify",		A_CANT, 0);
	class_addmethod(c, (method)controler_encoder_mouse_down,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)controler_encoder_mouse_drag,	"mousedrag",	A_CANT, 0);
	
	CLASS_ATTR_DEFAULT				(c, "patching_rect", 0, "0 0 225 225");
	CLASS_ATTR_INVISIBLE			(c, "color", 0);
	CLASS_ATTR_INVISIBLE			(c, "textcolor", 0);

	CLASS_ATTR_LONG					(c, "order", 0, t_controler_encoder, f_order);
	CLASS_ATTR_CATEGORY				(c, "order", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "order", 0, "1");
	CLASS_ATTR_LABEL				(c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_ACCESSORS			(c, "order", NULL, order_set);
	CLASS_ATTR_FILTER_MIN			(c, "order", 1);
	CLASS_ATTR_DEFAULT				(c, "order", 0, "4");
	CLASS_ATTR_SAVE					(c, "order", 1);

	CLASS_ATTR_LONG					(c, "optim", 0, t_controler_encoder, f_optimMode);
	CLASS_ATTR_CATEGORY				(c, "optim", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "optim", 0, "2");
	CLASS_ATTR_ENUMINDEX			(c, "optim", 0, "basic \" \"maxRe \" \"inPhase");
	CLASS_ATTR_LABEL				(c, "optim", 0, "Ambisonic Optimization");
	CLASS_ATTR_ACCESSORS			(c, "optim", NULL, optim_set);
	CLASS_ATTR_DEFAULT				(c, "optim", 0, "0");
	CLASS_ATTR_SAVE					(c, "optim", 1);
	
	CLASS_ATTR_DOUBLE				(c, "wide", 0, t_controler_encoder, f_wide);
	CLASS_ATTR_CATEGORY				(c, "wide", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "wide", 0, "3");
	CLASS_ATTR_LABEL				(c, "wide", 0, "Wide value");
	CLASS_ATTR_ACCESSORS			(c, "wide", NULL, wide_set);
	CLASS_ATTR_FILTER_CLIP			(c, "wide", 0., 1.);
	CLASS_ATTR_DEFAULT				(c, "wide", 0, "1.");
	CLASS_ATTR_SAVE					(c, "wide", 1);

	CLASS_ATTR_DOUBLE				(c, "azimuth", 0, t_controler_encoder, f_azimuth);
	CLASS_ATTR_CATEGORY				(c, "azimuth", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "azimuth", 0, "4");
	CLASS_ATTR_LABEL				(c, "azimuth", 0, "Azimuth value");
	CLASS_ATTR_ACCESSORS			(c, "azimuth", NULL, azimuth_set);
	CLASS_ATTR_DEFAULT				(c, "azimuth", 0, "0.");
	CLASS_ATTR_SAVE					(c, "azimuth", 1);

	CLASS_ATTR_LONG					(c, "mode", 0, t_controler_encoder, f_mode);
	CLASS_ATTR_CATEGORY				(c, "mode", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "mode", 0, "5");
	CLASS_ATTR_ENUMINDEX			(c, "mode", 0, "Absolute \" \"Relative");
	CLASS_ATTR_LABEL				(c, "mode", 0, "Interaction mode");
	CLASS_ATTR_FILTER_CLIP			(c, "mode", 0, 1);
	CLASS_ATTR_DEFAULT				(c, "mode", 0, "0.");
	CLASS_ATTR_SAVE					(c, "mode", 1);

	CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_controler_encoder, f_colorBackground);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER				(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "1. 1. 1. 1.");
	
	CLASS_ATTR_RGBA					(c, "txcolor", 0, t_controler_encoder, f_colorText);
	CLASS_ATTR_CATEGORY				(c, "txcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "txcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "txcolor", 0, "Text Color");
	CLASS_ATTR_ORDER				(c, "txcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "txcolor", 0, "0. 0. 0. 1.");

	CLASS_ATTR_RGBA					(c, "cicolor", 0, t_controler_encoder, f_colorCircle);
	CLASS_ATTR_CATEGORY				(c, "cicolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "cicolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "cicolor", 0, "Circle Color");
	CLASS_ATTR_ORDER				(c, "cicolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "cicolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_RGBA					(c, "phcolor", 0, t_controler_encoder, f_colorPositif);
	CLASS_ATTR_CATEGORY				(c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "phcolor", 0, "Positifs Harmonics color");
	CLASS_ATTR_ORDER				(c, "phcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "phcolor", 0, "0. 0. 1. 1.");
	
	CLASS_ATTR_RGBA					(c, "nhcolor", 0, t_controler_encoder, f_colorNegatif);
	CLASS_ATTR_CATEGORY				(c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "nhcolor", 0, "Negatifs Harmonics color");
	CLASS_ATTR_ORDER				(c, "nhcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "nhcolor", 0, "1. 0. 0. 1.");
	
	CLASS_ATTR_RGBA					(c, "cocolor", 0, t_controler_encoder, f_colorContrib);
	CLASS_ATTR_CATEGORY				(c, "cocolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "cocolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "cocolor", 0, "Biggest contribution color");
	CLASS_ATTR_ORDER				(c, "cocolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "cocolor", 0, "0. 0. 0. 1.");

	class_register(CLASS_BOX, c);
	controler_encoder_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));

	return 0;
}

void *controler_encoder_new(t_symbol *s, int argc, t_atom *argv)
{
	t_controler_encoder *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_controler_encoder *)object_alloc(controler_encoder_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;

	x->f_encoder			= new AmbisonicEncode(x->f_order);
	x->f_viewer				= new AmbisonicViewer(x->f_order);
	x->f_optim				= new AmbisonicOptim(x->f_order);
	x->f_wider				= new AmbisonicWider(x->f_order);
	x->f_harmonicsValues	= new double[x->f_order * 2 + 1];

	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.b_firstin = (t_object *)x;

	x->f_outInfos	= outlet_new(x, NULL);
	x->f_outWide	= floatout((t_object *)x);
	x->f_outAzimuth = floatout((t_object *)x);

	attr_dictionary_process(x, d);

	x->f_azimuth= 0.;
	x->f_wide = 1.;
	controler_encoder_compute(x);
	jbox_ready((t_jbox *)x);
	
	return (x);
}			

void controler_encoder_free(t_controler_encoder *x)
{
	jbox_free((t_jbox *)x);
	free(x->f_harmonicsValues);
	delete x->f_encoder;
	delete x->f_viewer;
	delete x->f_optim;
	delete x->f_wider;
}

void controler_encoder_assist(t_controler_encoder *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"(Anything) Behavior and color messages"); 
	}
	else
	{
		if (a == 0)
			sprintf(s,"(Float) Azimuth value"); 
		else if(a == 1)
			sprintf(s,"(Float) Wide value");
		else
			sprintf(s,"(Messages) Infos");
	}
}

t_max_err controler_encoder_notify(t_controler_encoder *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("bgcolor") || name == gensym("cicolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
		else if(name == gensym("txcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
		}
		else if(name == gensym("nhcolor") || name == gensym("phcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
		}
		else if(name == gensym("cocolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("biggest_contribution_layer"));
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void controler_encoder_paint(t_controler_encoder *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	
	x->f_center.x = rect.width * .5;
	x->f_center.y = rect.height * .5;
	
	x->f_rayonGlobal = rect.width * .5;
	if(rect.width > rect.height)
		x->f_rayonGlobal = rect.height * .5;
	
	x->f_fontsize = (x->f_rayonGlobal / 14.) - 1.;
	x->f_rayonAngle = 5. / 6. * x->f_rayonGlobal + x->f_fontsize * 1.5;
	x->f_rayonCircle = x->f_rayonGlobal / 6;
	
	draw_background(x, view, &rect);
	draw_angle(x, view, &rect);
	draw_harmonics(x, view, &rect);
	draw_biggest_contribution(x, view, &rect);
}

void draw_background(t_controler_encoder *x,  t_object *view, t_rect *rect)
{
	int i;
	double x1, x2, y1, y2;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);

	if (g) 
	{
		/* Background */
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_rectangle_fill_fast(g, 0., 0., rect->width, rect->height);
		
		/* Circles */
		for(i = 5; i > 0; i--)
		{
			jgraphics_set_source_jrgba(g, &x->f_colorCircle);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (double)i * x->f_rayonCircle,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
			jgraphics_set_source_jrgba(g, &x->f_colorBackground);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (double)i * x->f_rayonCircle - 1.,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
		}
		/* Axes */
		jgraphics_set_source_jrgba(g, &x->f_colorCircle);
		for(i = 0; i < 6; i++)
		{
			x1 = 5. / 6. * x->f_rayonGlobal	 * cos((double)i * JGRAPHICS_PI / 6.) + x->f_center.x;
			x2 = 5. / 6. * x->f_rayonGlobal  * cos((double)i * JGRAPHICS_PI / 6. + JGRAPHICS_PI) + x->f_center.x;
			y1 = 5. / 6. * x->f_rayonGlobal  * sin((double)i * JGRAPHICS_PI / 6.) + x->f_center.y;
			y2 = 5. / 6. * x->f_rayonGlobal  * sin((double)i * JGRAPHICS_PI / 6. + JGRAPHICS_PI) + x->f_center.y;
			jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
		}
		
		/* Center circle */
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_arc(g, x->f_center.x, x->f_center.y, x->f_rayonCircle - 1.,  0., JGRAPHICS_2PI);
		
		jgraphics_fill(g);
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_angle(t_controler_encoder *x,  t_object *view, t_rect *rect)
{
	int i;
	double x1, y1;
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("angle_layer"), rect->width, rect->height);
	
	if (g) 
	{
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->f_fontsize);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorText); 
		for(i = 0; i < 12; i++)
		{
			x1 = x->f_rayonAngle * cos((double)-i * JGRAPHICS_2PI / 12. - JGRAPHICS_PI / 2.) + x->f_center.x;
			y1 = x->f_rayonAngle * sin((double)-i * JGRAPHICS_2PI / 12. - JGRAPHICS_PI / 2.) + x->f_center.y;
		
			sprintf(text,"%d°", 30 * i);
			jtextlayout_set(jtl, text, jf, x1 - x->f_fontsize * 1.5, y1 - 10, x->f_fontsize * 3., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
			jtextlayout_draw(jtl, g);
			
		}	
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("angle_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("angle_layer"), 0., 0.);
}

void draw_harmonics(t_controler_encoder *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);

	if (g) 
	{
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);

		if(x->f_viewer->getBiggestContribution() != 0.)
		{
			double factor = (x->f_rayonGlobal * 5. / 6.) / x->f_viewer->getBiggestContribution();
			jgraphics_set_source_jrgba(g, &x->f_colorPositif);
			jgraphics_move_to(g, x->f_viewer->getAbscisseValue(0) * factor, x->f_viewer->getOrdinateValue(0) * factor );
			for(int i = 1; i < NUMBEROFCIRCLEPOINTS; i++)
			{
				if(x->f_viewer->getColor(i) == 1 && x->f_viewer->getColor(i - 1) == 1)
					jgraphics_line_to(g, x->f_viewer->getAbscisseValue(i) * factor, x->f_viewer->getOrdinateValue(i) * factor);
				else if(x->f_viewer->getColor(i) == 1 && x->f_viewer->getColor(i - 1) == -1)
					jgraphics_move_to(g, x->f_viewer->getAbscisseValue(i) * factor, x->f_viewer->getOrdinateValue(i) * factor);
			}
			jgraphics_stroke(g);

			jgraphics_set_source_jrgba(g, &x->f_colorNegatif);
			jgraphics_move_to(g, x->f_viewer->getAbscisseValue(0) * factor, x->f_viewer->getOrdinateValue(0) * factor );
			for(int i = 1; i < NUMBEROFCIRCLEPOINTS; i++)
			{
				if(x->f_viewer->getColor(i) == -1 && x->f_viewer->getColor(i - 1) == -1)
					jgraphics_line_to(g, x->f_viewer->getAbscisseValue(i) * factor, x->f_viewer->getOrdinateValue(i) * factor);
				else if(x->f_viewer->getColor(i) == -1 && x->f_viewer->getColor(i - 1) == 1)
					jgraphics_move_to(g, x->f_viewer->getAbscisseValue(i) * factor, x->f_viewer->getOrdinateValue(i) * factor);
			}
			jgraphics_stroke(g);
		}
		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
}

void draw_biggest_contribution(t_controler_encoder *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("biggest_contribution_layer"), rect->width, rect->height);

	if (g) 
	{
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);

		if(x->f_viewer->getBiggestContribution() != 0.)
		{
			double factor = (x->f_rayonGlobal * 5. / 6.) / x->f_viewer->getBiggestContribution();
			jgraphics_set_source_jrgba(g, &x->f_colorContrib);
			jgraphics_arc(g, x->f_viewer->getAbscisseValue(x->f_viewer->getBiggestContributionIndex()) * factor, x->f_viewer->getOrdinateValue(x->f_viewer->getBiggestContributionIndex()) * factor, 
				3.,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
		}
		jbox_end_layer((t_object*)x, view, gensym("biggest_contribution_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("biggest_contribution_layer"), 0., 0.);
}

void controler_encoder_mouse_down(t_controler_encoder *x, t_object *patcherview, t_pt pt, long modifiers)
{
	#ifdef WIN_VERSION
		long shift = 18;
	#endif
	#ifdef MAC_VERSION
		long shift = 2;
	#endif
	t_atom argv[1];
	if(modifiers != shift)
	{
		if(x->f_mode == 0)
		{
			double angle = Tools::angle(pt.x - x->f_center.x, pt.y - x->f_center.y) * -1. - JGRAPHICS_PIOVER2;
			atom_setfloat(argv, angle);
			object_method(x, gensym("azimuth"), 1, argv);
		}
		else
		{
			x->f_azimuthOffset = Tools::angle(pt.x - x->f_center.x, pt.y - x->f_center.y) * -1. - JGRAPHICS_PIOVER2;
			double angle = x->f_azimuth;
			atom_setfloat(argv, angle);
			object_method(x, gensym("azimuth"), 1, argv);
		}
	}
	else
	{
		if(x->f_mode == 0)
		{
			double radius = Tools::radius((pt.x - x->f_center.x) / (x->f_rayonGlobal * 5. / 6.), (pt.y - x->f_center.y) / (x->f_rayonGlobal * 5. / 6.));
			atom_setfloat(argv, radius);
			object_method(x, gensym("wide"), 1, argv);
		}
		else
		{
			x->f_wideOffset = Tools::radius(pt.x / x->f_rayonGlobal, (x->f_rayonGlobal * 2. - pt.y) / x->f_rayonGlobal);
			double radius = x->f_wide;
			atom_setfloat(argv, radius);
			object_method(x, gensym("wide"), 1, argv);
		}
	}
}

void controler_encoder_mouse_drag(t_controler_encoder *x, t_object *patcherview, t_pt pt, long modifiers)
{
	#ifdef WIN_VERSION
		long shift = 18;
	#endif
	#ifdef MAC_VERSION
		long shift = 2;
	#endif
	t_atom argv[1];
	if(modifiers != shift)
	{
		if(x->f_mode == 0)
		{
			double angle = Tools::angle(pt.x - x->f_center.x, pt.y - x->f_center.y) * -1. - JGRAPHICS_PIOVER2;
			atom_setfloat(argv, angle);
			object_method(x, gensym("azimuth"), 1, argv);
		}
		else
		{
			double newAngle = Tools::angle(pt.x - x->f_center.x, pt.y - x->f_center.y) * -1. - JGRAPHICS_PIOVER2;
			double offset = newAngle - x->f_azimuthOffset;
			x->f_azimuthOffset = newAngle;
			double angle = x->f_azimuth + offset;
			atom_setfloat(argv, angle);
			object_method(x, gensym("azimuth"), 1, argv);
		}
	}
	else
	{
		if(x->f_mode == 0)
		{
			double radius = Tools::radius((pt.x - x->f_center.x) / (x->f_rayonGlobal * 5. / 6.), (pt.y - x->f_center.y) / (x->f_rayonGlobal * 5. / 6.));
			atom_setfloat(argv, radius);
			object_method(x, gensym("wide"), 1, argv);
		}
		else
		{
			double newRadius = Tools::radius(pt.x / x->f_rayonGlobal, (x->f_rayonGlobal * 2. - pt.y) / x->f_rayonGlobal);
			double offset = newRadius - x->f_wideOffset;
			x->f_wideOffset = newRadius;
			double radius = x->f_wide + offset;
			atom_setfloat(argv, radius);
			object_method(x, gensym("wide"), 1, argv);
		}
	}
}

void controler_encoder_compute(t_controler_encoder *x)
{
	double angle = x->f_azimuth;
	if(angle > JGRAPHICS_2PI)
		angle -= JGRAPHICS_2PI;
	else if(angle < 0.)
		angle += JGRAPHICS_2PI;
	
	x->f_encoder->process(1., x->f_harmonicsValues, angle - JGRAPHICS_PIOVER2);
	x->f_optim->process(x->f_harmonicsValues, x->f_harmonicsValues);
	x->f_wider->process(x->f_harmonicsValues, x->f_harmonicsValues, x->f_wide);
	x->f_viewer->process(x->f_harmonicsValues);
}

t_max_err order_set(t_controler_encoder *x, t_object *attr, long argc, t_atom *argv)
{
	if (atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) != x->f_order && atom_getlong(argv) >= 1)
		{
			delete x->f_encoder;
			delete x->f_viewer;
			delete x->f_optim;
			delete x->f_wider;
			x->f_order = atom_getlong(argv);
			x->f_encoder	= new AmbisonicEncode(x->f_order);
			x->f_optim		= new AmbisonicOptim(x->f_order);
			x->f_wider		= new AmbisonicWider(x->f_order);
			x->f_viewer		= new AmbisonicViewer(x->f_order);
			x->f_harmonicsValues = new double[x->f_order * 2 + 1];

			std::string optimMode = "basic";
			if(x->f_optimMode == 1)
				optimMode = "maxRe";
			else if(x->f_optimMode == 2)
				optimMode = "inPhase";
			x->f_optim->setOptimMode(optimMode);

			controler_encoder_compute(x);

			jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("biggest_contribution_layer"));
			jbox_redraw((t_jbox *)x);
		}
	}
	return 0;
}

t_max_err optim_set(t_controler_encoder *x, t_object *attr, long argc, t_atom *argv)
{
	if (atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) != x->f_optimMode)
		{
			t_atom mode[1];
			std::string optimMode;
			if(atom_getlong(argv) == 1)
			{
				atom_setsym(mode, gensym("maxRe"));
				optimMode = "maxRe";
				x->f_optimMode = 1;
			}
			else if(atom_getlong(argv) == 2)
			{
				atom_setsym(mode, gensym("inPhase"));
				optimMode = "inPhase";
				x->f_optimMode = 2;
			}
			else
			{
				atom_setsym(mode, gensym("basic"));
				optimMode = "basic";
				x->f_optimMode = 0;
			}
		
			x->f_optim->setOptimMode(optimMode);

			controler_encoder_compute(x);
			outlet_anything(x->f_outInfos, gensym("optim"), 1, mode);

			jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("biggest_contribution_layer"));
			jbox_redraw((t_jbox *)x);
		}
	}
	return 0;
}

t_max_err wide_set(t_controler_encoder *x, t_object *attr, long argc, t_atom *argv)
{
	if (atom_gettype(argv) == A_FLOAT)
	{
		x->f_wide = atom_getfloat(argv);
		controler_encoder_compute(x);
		outlet_float(x->f_outWide, x->f_wide);

		jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("biggest_contribution_layer"));
		jbox_redraw((t_jbox *)x);
	}
	return 0;
}

t_max_err azimuth_set(t_controler_encoder *x, t_object *attr, long argc, t_atom *argv)
{
	if (atom_gettype(argv) == A_FLOAT)
	{
		x->f_azimuth = fmod(atom_getfloat(argv) + JGRAPHICS_2PI, JGRAPHICS_2PI);
		controler_encoder_compute(x);
		outlet_float(x->f_outAzimuth, x->f_azimuth);

		jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("biggest_contribution_layer"));
		jbox_redraw((t_jbox *)x);
	}
	return 0;
}
