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

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"

typedef struct  _trajectory 
{
	t_jbox		j_box;
	
	t_jrgba		f_colorBackground;
	t_jrgba		f_colorText;
	t_jrgba		f_colorCircle;
	t_jrgba		f_colorPointer;

	t_pt		f_mousePointer[100];
	int			f_numberOfSources;
	int			f_actualSource;
	void*		f_outPolar;
	void*		f_outCarte;

} t_trajectory;

t_class *trajectory_class;

void *trajectory_new(t_symbol *s, int argc, t_atom *argv);
void trajectory_free(t_trajectory *x);
void trajectory_assist(t_trajectory *x, void *b, long m, long a, char *s);
void trajectory_list(t_trajectory *x, t_symbol *s, short ac, t_atom *av);
void trajectory_bang(t_trajectory *x);
void trajectory_outone(t_trajectory *x, int i);

void trajectory_mousedown(t_trajectory *x, t_object *patcherview, t_pt pt, long modifiers);
void trajectory_mousedrag(t_trajectory *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err trajectory_notify(t_trajectory *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

/* Paint *********************************************/
void trajectory_paint(t_trajectory *x, t_object *view);
void draw_background(t_trajectory *x, t_object *view, t_rect *rect);
void draw_angle(t_trajectory *x,  t_object *view, t_rect *rect);
void draw_contribution(t_trajectory *x,  t_object *view, t_rect *rect);
void draw_pointer(t_trajectory *x,  t_object *view, t_rect *rect);
void draw_coordinates(t_trajectory *x,  t_object *view, t_rect *rect);

int main()
{
	t_class *c;

	c = class_new("hoa.trajectory", (method)trajectory_new, (method)trajectory_free, (short)sizeof(t_trajectory), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);

	class_addmethod(c, (method)trajectory_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)trajectory_paint,		"paint",		A_CANT,	0);
	class_addmethod(c, (method)trajectory_notify,		"notify",		A_CANT, 0);
	class_addmethod(c, (method)trajectory_mousedown,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)trajectory_mousedrag,	"mousedrag",	A_CANT, 0);

	class_addmethod(c, (method)trajectory_list,			"list",			A_GIMME,0);
	class_addmethod(c, (method)trajectory_bang,			"bang",			A_GIMME,0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 225 225");

	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_trajectory, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "1. 1. 1. 1.");
	
	CLASS_ATTR_RGBA				(c, "txcolor", 0, t_trajectory, f_colorText);
	CLASS_ATTR_CATEGORY			(c, "txcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "txcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "txcolor", 0, "Text Color");
	CLASS_ATTR_ORDER			(c, "txcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "txcolor", 0, "0. 0. 0. 1.");

	CLASS_ATTR_RGBA				(c, "cicolor", 0, t_trajectory, f_colorCircle);
	CLASS_ATTR_CATEGORY			(c, "cicolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "cicolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "cicolor", 0, "Circle Color");
	CLASS_ATTR_ORDER			(c, "cicolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "cicolor", 0, "0. 0. 0. 1.");

	CLASS_ATTR_RGBA				(c, "ptcolor", 0, t_trajectory, f_colorPointer);
	CLASS_ATTR_CATEGORY			(c, "ptcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "ptcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "ptcolor", 0, "Pointer Color");
	CLASS_ATTR_ORDER			(c, "ptcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "ptcolor", 0, "0. 0. 1. 1.");
	
	class_register(CLASS_BOX, c);
	trajectory_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *trajectory_new(t_symbol *s, int argc, t_atom *argv)
{
	t_trajectory *x =  NULL; 
	int i;
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_trajectory *)object_alloc(trajectory_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWBOTH
			;
	jbox_new(&x->j_box, flags, argc, argv); 	
	x->j_box.b_firstin	= (t_object*) x;
	x->f_outPolar		= listout(x);
	x->f_outCarte		= listout(x);
	x->f_numberOfSources = 0;
	for(i = 0; i < 100; i++)
	{
		x->f_mousePointer[i].x = 0.;
		x->f_mousePointer[i].y = 0.;
	}

	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);
	
		return (x);
}			

void trajectory_free(t_trajectory *x)
{
	jbox_free(&x->j_box);
}

void trajectory_assist(t_trajectory *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
		sprintf(s,"Anything");
	else
	{
		if(a)
			sprintf(s,"(List) Polar Coordinates");
		else
			sprintf(s,"(List) Cartesian Coordinates");
	}
}


void trajectory_list(t_trajectory *x, t_symbol *s, short ac, t_atom *av)
{

	jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_redraw((t_jbox *)x);
}

void trajectory_bang(t_trajectory *x)
{
	int i;
	for(i = 0; i < x->f_numberOfSources; i++)
		trajectory_outone(x, i);
}

void trajectory_outone(t_trajectory *x, int i)
{
	t_atom	av[3];
	atom_setlong(av, i);
	atom_setfloat(av+1, (float)x->f_mousePointer[i].x);
	atom_setfloat(av+2, (float)x->f_mousePointer[i].y);
	outlet_list(x->f_outCarte, NULL, 3, av);
}

t_max_err trajectory_notify(t_trajectory *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
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
		else if(name == gensym("ptcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("pointer_layer"));
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void trajectory_paint(t_trajectory *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	draw_background(x, view, &rect);
	draw_angle(x, view, &rect);
	draw_pointer(x, view, &rect);
	draw_coordinates(x, view, &rect);
}

void draw_background(t_trajectory *x,  t_object *view, t_rect *rect)
{
	int i;
	double size;
	double x1, x2, y1, y2;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);

	if (g) 
	{
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_rectangle_fill_fast(g, 0., 0., rect->width, rect->height);

		size = rect->width * .5;
		if(rect->width > rect->height)
			size = rect->height * .5;
		
		for(i = 5; i > 0; i--)
		{
			jgraphics_set_source_jrgba(g, &x->f_colorCircle);
			jgraphics_arc(g, rect->width * .5, rect->height * .5, ((double)i * size / 6.),  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
			jgraphics_set_source_jrgba(g, &x->f_colorBackground);
			jgraphics_arc(g, rect->width * .5, rect->height * .5, ((double)i * size / 6.) - 1.,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
		}
		jgraphics_set_source_jrgba(g, &x->f_colorCircle);
		for(i = 0; i < 6; i++)
		{
			x1 = 5. / 6. * size	 * cos((double)i * JGRAPHICS_PI / 6.) + rect->width * .5;
			x2 = 5. / 6. * size  * cos((double)i * JGRAPHICS_PI / 6. + JGRAPHICS_PI) + rect->width * .5;
			y1 = 5. / 6. * size  * sin((double)i * JGRAPHICS_PI / 6.) + rect->height * .5;
			y2 = 5. / 6. * size  * sin((double)i * JGRAPHICS_PI / 6. + JGRAPHICS_PI) + rect->height * .5;
			jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
		}
		
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_arc(g, rect->width * .5, rect->height * .5, (size / 6.) - 1.,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		
		
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_angle(t_trajectory *x,  t_object *view, t_rect *rect)
{
	int i;
	double size, fontsize;
	double x1, y1;
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("angle_layer"), rect->width, rect->height);
	size = rect->width * .5;
	if(rect->width > rect->height)
		size = rect->height * .5;
	fontsize = (size / 14.) - 1.;
	if (g) 
	{
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize);
		jtl = jtextlayout_create();
		size = rect->width * .5;
		if(rect->width > rect->height)
			size = rect->height * .5;
		jtextlayout_settextcolor(jtl, &x->f_colorText); 
		for(i = 0; i < 12; i++)
		{
			x1 = (5. / 6. * size + fontsize * 1.5) * cos((double)-i * JGRAPHICS_2PI / 12. - JGRAPHICS_PI / 2.) + rect->width * .5;
			y1 = (5. / 6. * size + fontsize * 1.5) * sin((double)-i * JGRAPHICS_2PI / 12. - JGRAPHICS_PI / 2.) + rect->height * .5;
		
			sprintf(text,"%d°", 30 * i);
			jtextlayout_set(jtl, text, jf, x1 - fontsize * 1.5, y1 - 10, fontsize * 3., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
			jtextlayout_draw(jtl, g);
			
		}	
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("angle_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("angle_layer"), 0., 0.);
}

void draw_pointer(t_trajectory *x,  t_object *view, t_rect *rect)
{
	int i;
	double size, fontsize;
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("pointer_layer"), rect->width, rect->height);
	if(rect->width > rect->height)
	{
		size = rect->height / 60.;
		fontsize = (rect->height / 28.) - 1.;
	}
	else
	{
		size = rect->width / 60.;
		fontsize = (rect->width / 28.) - 1.;
	}
	
	if (g) 
	{
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorPointer); 
		for(i = 0; i < x->f_numberOfSources; i++)
		{
			sprintf(text,"%i", i);
			jtextlayout_set(jtl, text, jf, x->f_mousePointer[i].x + size, x->f_mousePointer[i].y + size, fontsize * 3, fontsize, JGRAPHICS_TEXT_JUSTIFICATION_LEFT, JGRAPHICS_TEXTLAYOUT_NOWRAP);
			jtextlayout_draw(jtl, g);

			jgraphics_set_source_jrgba(g, &x->f_colorPointer);
			jgraphics_arc(g, x->f_mousePointer[i].x, x->f_mousePointer[i].y, size,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
		}
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("pointer_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("pointer_layer"), 0., 0.);
}

void draw_coordinates(t_trajectory *x,  t_object *view, t_rect *rect)
{
	int i;
	double size, fontsize, angle = 0.;
	double x1, y1;
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("coordinates_layer"), rect->width, rect->height);
	size = rect->width * .5;
	if(rect->width > rect->height)
		size = rect->height * .5;
	fontsize = (size / 14.) - 1.;
	if (g) 
	{
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize);
		jtl = jtextlayout_create();
		size = rect->width * .5;
		if(rect->width > rect->height)
			size = rect->height * .5;
		jtextlayout_settextcolor(jtl, &x->f_colorText); 
		
		sprintf(text,"x : %f", x->f_mousePointer[x->f_actualSource-1].x / rect->width);
		jtextlayout_set(jtl, text, jf, fontsize, rect->height - 3 * fontsize, fontsize * 5., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
		jtextlayout_draw(jtl, g);
		sprintf(text,"y : %f", x->f_mousePointer[x->f_actualSource-1].y /  rect->height);
		jtextlayout_set(jtl, text, jf, fontsize, rect->height - 2 * fontsize, fontsize * 5., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
		jtextlayout_draw(jtl, g);

		angle = sqrt((x->f_mousePointer[x->f_actualSource-1].x / rect->width) + (rect->width / 2.) * (x->f_mousePointer[x->f_actualSource-1].x / rect->width) + (rect->width / 2.)
			+ (x->f_mousePointer[x->f_actualSource-1].y / rect->height) + (rect->height / 2.) * (x->f_mousePointer[x->f_actualSource-1].y / rect->height) + (rect->height / 2.));
		sprintf(text,"a : %f°", angle);
		jtextlayout_set(jtl, text, jf, rect->width - 6 * fontsize, rect->height - 3 * fontsize, fontsize * 5., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
		jtextlayout_draw(jtl, g);
		sprintf(text,"r : %f", x->f_mousePointer[x->f_actualSource-1].y /  rect->height);
		jtextlayout_set(jtl, text, jf, rect->width - 6 * fontsize, rect->height - 2 * fontsize, fontsize * 5., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
		jtextlayout_draw(jtl, g);
		
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("coordinates_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("coordinates_layer"), 0., 0.);
}

void trajectory_mousedown(t_trajectory *x, t_object *patcherview, t_pt pt, long modifiers)
{
	int i;
	post("%ld", modifiers);
	if(x->f_numberOfSources == 0)
	{
		x->f_numberOfSources = 1;
		x->f_actualSource = 1;
	}
	if(modifiers == 17)// windows 21 mac 18
	{
		x->f_numberOfSources++;
		if(x->f_numberOfSources == 100) x->f_numberOfSources--;
		x->f_actualSource = x->f_numberOfSources;
		x->f_mousePointer[x->f_actualSource-1] = pt;
	}
	if(modifiers == 18)
	{
		x->f_numberOfSources--;
		if(x->f_numberOfSources == -1) x->f_numberOfSources++;
		x->f_actualSource = x->f_numberOfSources;
	}
	else
	{
		for(i = 0; i < x->f_numberOfSources; i++)
		{
			if( sqrt(pow((x->f_mousePointer[i].x - pt.x), 2) + pow((x->f_mousePointer[i].y - pt.y), 2)) < sqrt(pow((x->f_mousePointer[x->f_actualSource-1].x - pt.x), 2) + pow((x->f_mousePointer[x->f_actualSource-1].y - pt.y), 2)))
				x->f_actualSource = i + 1;
		}
		x->f_mousePointer[x->f_actualSource-1] = pt;
	}
	trajectory_outone(x, x->f_actualSource-1);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("pointer_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("coordinates_layer"));
	jbox_redraw((t_jbox *)x);
	
}

void trajectory_mousedrag(t_trajectory *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->f_mousePointer[x->f_actualSource-1] = pt;
	trajectory_outone(x, x->f_actualSource-1);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("pointer_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("coordinates_layer"));
	jbox_redraw((t_jbox *)x);
}