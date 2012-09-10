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

#define MAXIMUM_SIZE 3600

typedef struct  _descriptor 
{
	t_jbox		j_box;
	
	t_jrgba		f_colorBackground;
	t_jrgba		f_colorText;
	t_jrgba		f_colorCircle;
	t_jrgba		f_colorNegatif;
	t_jrgba		f_colorPositif;
	
	int			f_order;
	double		f_biggestContrib;
	double		*f_harmonics;
	double		*f_contributions;
	double		**f_harmonicsBasis;
	double		*f_harmonicsValues;
	double		*f_angularSteps;
	double		*f_xCircleVector;
	double		*f_yCircleVector;
	
} t_descriptor;

t_class *descriptor_class;

void *descriptor_new(t_symbol *s, int argc, t_atom *argv);
void descriptor_free(t_descriptor *x);
void descriptor_assist(t_descriptor *x, void *b, long m, long a, char *s);
void descriptor_vector(t_descriptor *x);
void descriptor_basis(t_descriptor *x);
void descriptor_list(t_descriptor *x, t_symbol *s, short ac, t_atom *av);

t_max_err descriptor_notify(t_descriptor *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

/* Paint *********************************************/
void descriptor_paint(t_descriptor *x, t_object *view);
void draw_background(t_descriptor *x, t_object *view, t_rect *rect);
void draw_angle(t_descriptor *x,  t_object *view, t_rect *rect);
void draw_contribution(t_descriptor *x,  t_object *view, t_rect *rect);
void draw_harmonics(t_descriptor *x,  t_object *view, t_rect *rect);

int main()
{
	t_class *c;

	c = class_new("hoa.scope", (method)descriptor_new, (method)descriptor_free, (short)sizeof(t_descriptor), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);

	class_addmethod(c, (method)descriptor_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)descriptor_paint,		"paint",		A_CANT,	0);
	class_addmethod(c, (method)descriptor_notify,		"notify",		A_CANT, 0);
	class_addmethod(c, (method)descriptor_list,			"list",			A_GIMME, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 225 225");

	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_descriptor, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "txcolor", 0, t_descriptor, f_colorText);
	CLASS_ATTR_CATEGORY			(c, "txcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "txcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "txcolor", 0, "Text Color");
	CLASS_ATTR_ORDER			(c, "txcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "txcolor", 0, "1. 1. 1. 1.");

	CLASS_ATTR_RGBA				(c, "cicolor", 0, t_descriptor, f_colorCircle);
	CLASS_ATTR_CATEGORY			(c, "cicolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "cicolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "cicolor", 0, "Circle Color");
	CLASS_ATTR_ORDER			(c, "cicolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "cicolor", 0, "1. 1. 1. 1.");
	
	CLASS_ATTR_RGBA				(c, "phcolor", 0, t_descriptor, f_colorPositif);
	CLASS_ATTR_CATEGORY			(c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "phcolor", 0, "Positifs Harmonics");
	CLASS_ATTR_ORDER			(c, "phcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "phcolor", 0, "1. 0. 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "nhcolor", 0, t_descriptor, f_colorNegatif);
	CLASS_ATTR_CATEGORY			(c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "nhcolor", 0, "Negatifs Harmonics");
	CLASS_ATTR_ORDER			(c, "nhcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "nhcolor", 0, "0. 0. 1. 1.");
	
	class_register(CLASS_BOX, c);
	descriptor_class = c;
	
	return 0;
}

void *descriptor_new(t_symbol *s, int argc, t_atom *argv)
{
	t_descriptor *x =  NULL; 
	int i;
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_descriptor *)object_alloc(descriptor_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWBOTH
			;
	jbox_new(&x->j_box, flags, argc, argv); 

	x->f_order = 1;
	x->f_harmonicsValues = (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	x->f_harmonics = (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	x->f_contributions = (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	x->f_angularSteps = (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	x->f_xCircleVector = (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	x->f_yCircleVector = (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	x->f_harmonicsBasis = (double **)getbytes(MAXIMUM_SIZE * sizeof(double *));
	
	for (i = 0; i < MAXIMUM_SIZE; i++)
	{ 
		x->f_harmonics[i] = 0.;
		x->f_contributions[i] = 0.;
		x->f_harmonicsBasis[i] = (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	}
	descriptor_vector(x);
	descriptor_basis(x);
	
	x->j_box.b_firstin = (t_object*) x;
	
	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);
	
		return (x);
}			

void descriptor_free(t_descriptor *x)
{
	int i;
	jbox_free(&x->j_box);
	freebytes(x->f_harmonicsValues, MAXIMUM_SIZE * sizeof(double));
	freebytes(x->f_harmonics, MAXIMUM_SIZE * sizeof(double));
	freebytes(x->f_contributions, MAXIMUM_SIZE * sizeof(double));
	freebytes(x->f_angularSteps, MAXIMUM_SIZE * sizeof(double));
	freebytes(x->f_xCircleVector, MAXIMUM_SIZE * sizeof(double));
	freebytes(x->f_yCircleVector, MAXIMUM_SIZE * sizeof(double));
	for(i = 0; i < MAXIMUM_SIZE; i++)
		freebytes(x->f_harmonicsBasis[i], MAXIMUM_SIZE * sizeof(double));
	
	freebytes(x->f_harmonicsBasis, MAXIMUM_SIZE * sizeof(double *));
}

void descriptor_assist(t_descriptor *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"(List) Harmonics values");
	}
}

void descriptor_vector(t_descriptor *x)
{
	int i;
	for (i = 0; i < MAXIMUM_SIZE; i++)
	{
		x->f_angularSteps[i] = (2. * JGRAPHICS_PI / MAXIMUM_SIZE) * (double)i;
		x->f_xCircleVector[i] = cos(x->f_angularSteps[i]);
		x->f_yCircleVector[i] = sin(x->f_angularSteps[i]);
	}
}

void descriptor_basis(t_descriptor *x)
{
	int i, j;
	for (j = 0; j < x->f_order * 2 + 1; j++)
	{
		for(i = 0; i < MAXIMUM_SIZE; i++)
		{
			if(j < x->f_order)
				x->f_harmonicsBasis[j][i] = sin(fabs(j) * x->f_angularSteps[i]);
			else if (j == x->f_order)
				x->f_harmonicsBasis[j][i] = cos(fabs(j)* x->f_angularSteps[i]) / 2.;
			else 
				x->f_harmonicsBasis[j+x->f_order][i] = cos(fabs(j)* x->f_angularSteps[i]);
		}
	}
}

void descriptor_list(t_descriptor *x, t_symbol *s, short ac, t_atom *av)
{
	int i, index;

	if(ac > MAXIMUM_SIZE)
		ac = MAXIMUM_SIZE;
	if((ac - 1) / 2 != x->f_order)
	{
		x->f_order = (ac - 1) / 2;
		descriptor_basis(x);
	}
	
	for (i = 0; i < ac; i++)
	{ 
		if(i %2 == 1)
			index = x->f_order - i;
		else
			index = x->f_order + i;
		
		if(atom_gettype(av+i) == A_FLOAT)
			x->f_harmonicsValues[index] = atom_getfloat(av+i);
		else if(atom_gettype(av+i) == A_LONG)
			x->f_harmonicsValues[index] = atom_getlong(av+i);
		else
			x->f_harmonicsValues[index] = 0.;
	}
	jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_redraw((t_jbox *)x);
}

t_max_err descriptor_notify(t_descriptor *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
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

void descriptor_paint(t_descriptor *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	draw_background(x, view, &rect);
	draw_angle(x, view, &rect);
	draw_contribution(x, view, &rect);
	draw_harmonics(x, view, &rect);
	
}

void draw_background(t_descriptor *x,  t_object *view, t_rect *rect)
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

void draw_angle(t_descriptor *x,  t_object *view, t_rect *rect)
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

void draw_contribution(t_descriptor *x,  t_object *view, t_rect *rect)
{
	int i, j;
	double size, fontsize, contrib;
	double x1, y1;
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("contrib_layer"), rect->width, rect->height);
	size = rect->width * .5;
	if(rect->width > rect->height)
		size = rect->height * .5;
	fontsize = (size / 14.) - 0.5;
	
	if (g) 
	{
		x->f_biggestContrib = 0.;
		for (i = 0; i < MAXIMUM_SIZE; i++)
		{    
			contrib = 0.;		
			for(j = -x->f_order; j<= x->f_order; j++)
				contrib += x->f_harmonicsBasis[j+x->f_order][i] * x->f_harmonicsValues[j+x->f_order];
			
			if (fabs(contrib) > x->f_biggestContrib )
				x->f_biggestContrib = fabs(contrib);
			
			x->f_contributions[i] = contrib;
		}
		
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize * 0.75);
		jtl = jtextlayout_create();
		size = (rect->width * .5) / 6.;
		if(rect->width > rect->height)
			size = (rect->height * .5) / 6.;
		jtextlayout_settextcolor(jtl, &x->f_colorText);
		x1 = rect->width * .5 + fontsize * .25;
		y1 = rect->height * .5 - 2 * fontsize;
		for(i = 1; i < 5; i++)
		{
			sprintf(text,"%.2f",((double)(i + 1) * x->f_biggestContrib) / 5.);
			jtextlayout_set(jtl, text, jf, x1, y1 - i * size, fontsize * 1.5, 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
			jtextlayout_draw(jtl, g);
			
		}	
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("contrib_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("contrib_layer"), 0., 0.);
}

void draw_harmonics(t_descriptor *x,  t_object *view, t_rect *rect)
{
	int i;
	double size, normalization, zero;
	double x1, y1, x2, y2;

	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);
	
	if (g) 
	{

		size = (rect->width * 5.) / 12.;
		zero = rect->width / 2.;
		if(rect->width > rect->height)
		{
			size = (rect->height * 5.) / 12.;
			zero = rect->height / 2.;
		}
		
		x1 = zero;
		y1 = zero;
		normalization = size / x->f_biggestContrib;
		for(i = 0; i < MAXIMUM_SIZE; i++)
		{
			x2 =  x->f_xCircleVector[i] * fabs(x->f_contributions[i]) * normalization + zero;
            y2 =  x->f_yCircleVector[i] * fabs(x->f_contributions[i]) * normalization + zero;
			
            if (x->f_contributions[i] < 0.)
            {
				if(i > 1 && x->f_contributions[i-1] >= 0.)
				{
					x2 = zero;
					y2 = zero;
				}
					
				jgraphics_set_source_jrgba(g, &x->f_colorPositif);
            }
            else
            {
				if(i > 1 && x->f_contributions[i-1] < 0.)
				{
					x1 = zero;
					y1 = zero;
				}
				jgraphics_set_source_jrgba(g, &x->f_colorNegatif);
            }			
			jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
			x1 = x2;
			y1 = y2;
		}	

		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
}

