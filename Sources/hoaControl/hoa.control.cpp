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
#include "AmbisonicEncode.hpp"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "jpatcher_api.h"
	#include "jgraphics.h"
	#include "jpatcher_syms.h"
	#include "ext_dictionary.h"
	#include "ext_globalsymbol.h"
}

typedef struct  _control 
{
	t_jbox		j_box;
	void*		f_deltaOut;
	void*		f_angleOut;

	int			f_order;
	
	t_jrgba		f_colorBackground;
	t_jrgba		f_colorText;
	t_jrgba		f_colorCircle;
	t_jrgba		f_colorNegatif;
	t_jrgba		f_colorPositif;
	
	t_rect		f_center;
	double		f_rayonGlobal;
	double		f_rayonAngle;
	double		f_rayonCircle;
	double		f_fontsize;

} t_control;

t_class *control_class;

void *control_new(t_symbol *s, int argc, t_atom *argv);
void control_free(t_control *x);
void control_assist(t_control *x, void *b, long m, long a, char *s);

t_max_err control_notify(t_control *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

/* Paint *********************************************/
void control_paint(t_control *x, t_object *view);
void draw_background(t_control *x, t_object *view, t_rect *rect);
void draw_angle(t_control *x,  t_object *view, t_rect *rect);
void draw_contribution(t_control *x,  t_object *view, t_rect *rect);
void draw_harmonics(t_control *x,  t_object *view, t_rect *rect);

int main()
{
	t_class *c;

	c = class_new("hoa.control", (method)control_new, (method)control_free, (short)sizeof(t_control), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);

	class_addmethod(c, (method)control_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)control_paint,		"paint",		A_CANT,	0);
	class_addmethod(c, (method)control_notify,		"notify",		A_CANT, 0);

	/*
	class_addmethod(c, (method)uisimp_mousedown,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mousedrag,	"mousedrag",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mouseup,		"mouseup",	A_CANT, 0);
	*/
	CLASS_ATTR_DEFAULT				(c, "patching_rect", 0, "0 0 225 225");
	CLASS_ATTR_INVISIBLE			(c, "color", 0);
	CLASS_ATTR_INVISIBLE			(c, "textcolor", 0);

	CLASS_ATTR_LONG					(c, "order", ATTR_SET_OPAQUE_USER, t_control, f_order);
	CLASS_ATTR_CATEGORY				(c, "order", 0, "Value");
	CLASS_ATTR_ORDER				(c, "order", 0, "1");
	CLASS_ATTR_LABEL				(c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_FILTER_MIN			(c, "order", 1);
	CLASS_ATTR_DEFAULT				(c, "order", 0, "3");
	CLASS_ATTR_SAVE					(c, "order", 1);
	
	CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_control, f_colorBackground);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER				(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "1. 1. 1. 1.");
	
	CLASS_ATTR_RGBA					(c, "txcolor", 0, t_control, f_colorText);
	CLASS_ATTR_CATEGORY				(c, "txcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "txcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "txcolor", 0, "Text Color");
	CLASS_ATTR_ORDER				(c, "txcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "txcolor", 0, "0. 0. 0. 1.");

	CLASS_ATTR_RGBA					(c, "cicolor", 0, t_control, f_colorCircle);
	CLASS_ATTR_CATEGORY				(c, "cicolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "cicolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "cicolor", 0, "Circle Color");
	CLASS_ATTR_ORDER				(c, "cicolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "cicolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_RGBA					(c, "phcolor", 0, t_control, f_colorPositif);
	CLASS_ATTR_CATEGORY				(c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "phcolor", 0, "Positifs Harmonics");
	CLASS_ATTR_ORDER				(c, "phcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "phcolor", 0, "1. 0. 0. 1.");
	
	CLASS_ATTR_RGBA					(c, "nhcolor", 0, t_control, f_colorNegatif);
	CLASS_ATTR_CATEGORY				(c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "nhcolor", 0, "Negatifs Harmonics");
	CLASS_ATTR_ORDER				(c, "nhcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "nhcolor", 0, "0. 0. 1. 1.");
	
	class_register(CLASS_BOX, c);
	control_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *control_new(t_symbol *s, int argc, t_atom *argv)
{
	t_control *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_control *)object_alloc(control_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.b_firstin = (t_object *)x;
	x->f_deltaOut = floatout((t_object *)x);
	x->f_angleOut = floatout((t_object *)x);
	attr_dictionary_process(x, d);

	jbox_ready((t_jbox *)x);
	
	return (x);
}			

void control_tick(t_control *x)
{
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_redraw((t_jbox *)x);
}

void control_free(t_control *x)
{
	jbox_free((t_jbox *)x);
}

void control_assist(t_control *x, void *b, long m, long a, char *s)
{
	long harmonicIndex = 0;
	if (m == ASSIST_INLET) 
	{
		if (a == 0)
			harmonicIndex = 0;
		else 
		{
			harmonicIndex = (a - 1) / 2 + 1;
			if (a % 2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex); 	
	}

}

t_max_err control_notify(t_control *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
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
			jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
		}
		else if(name == gensym("phcolor") || name == gensym("nhcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("harminics_layer"));
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void control_paint(t_control *x, t_object *view)
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
	//draw_contribution(x, view, &rect);
	//draw_harmonics(x, view, &rect);
	
}

void draw_background(t_control *x,  t_object *view, t_rect *rect)
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

void draw_angle(t_control *x,  t_object *view, t_rect *rect)
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

void draw_contribution(t_control *x,  t_object *view, t_rect *rect)
{
	int i, j;
	double x1, y1, biggestcontrib;

	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[64];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("contrib_layer"), rect->width, rect->height);
	
	if (g) 
	{		
		x1 = x->f_center.x + x->f_fontsize * .25;
		y1 = x->f_center.y - 2 * x->f_fontsize;
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->f_fontsize * 0.75);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorText);
		
		for(i = 1; i < 5; i++)
		{
			sprintf(text,"%.2f", (float)(i * biggestcontrib));
			jtextlayout_set(jtl, text, jf, x1, y1 - i * x->f_rayonCircle, x->f_fontsize * 3, 20, JGRAPHICS_TEXT_JUSTIFICATION_LEFT, JGRAPHICS_TEXTLAYOUT_NOWRAP);
			jtextlayout_draw(jtl, g);
			
		}	
		jbox_end_layer((t_object*)x, view, gensym("contrib_layer"));
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
	}
	jbox_paint_layer((t_object *)x, view, gensym("contrib_layer"), 0., 0.);
}

void draw_harmonics(t_control *x,  t_object *view, t_rect *rect)
{
	int i;
	double rayon, angle, normalization, factor;
	double x1, y1, x2, y2;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);
	
	if (g) 
	{
		jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
}

