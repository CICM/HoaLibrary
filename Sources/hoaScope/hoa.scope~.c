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
#include "z_dsp.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"

#define MAXIMUM_SIZE 360

typedef struct  _scope 
{
	t_pxjbox	j_box;
	
	void*		f_clock;
	int			f_startclock;
	int			f_interval;
	
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
	
	double		f_biggestContrib;
	double		*f_harmonics;
	double		*f_contributions;
	double		**f_harmonicsBasis;
	double		*f_harmonicsValues;
	double		*f_xCircleVector;
	double		*f_yCircleVector;
	
} t_scope;

t_class *scope_class;

void *scope_new(t_symbol *s, int argc, t_atom *argv);
void scope_free(t_scope *x);
void scope_assist(t_scope *x, void *b, long m, long a, char *s);
void scope_vector(t_scope *x);
void scope_basis(t_scope *x);
void scope_tick(t_scope *x);

void scope_dsp(t_scope *x, t_signal **sp, short *count);
t_int *scope_perform(t_int *w);

void scope_dsp64(t_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void scope_perform64(t_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

/* Paint *********************************************/
void scope_paint(t_scope *x, t_object *view);
void draw_background(t_scope *x, t_object *view, t_rect *rect);
void draw_angle(t_scope *x,  t_object *view, t_rect *rect);
void draw_contribution(t_scope *x,  t_object *view, t_rect *rect);
void draw_harmonics(t_scope *x,  t_object *view, t_rect *rect);

int main()
{
	t_class *c;

	c = class_new("hoa.scope~", (method)scope_new, (method)scope_free, (short)sizeof(t_scope), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);

	class_addmethod(c, (method)scope_dsp,			"dsp",			A_CANT, 0);
	class_addmethod(c, (method)scope_dsp64,			"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)scope_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)scope_paint,			"paint",		A_CANT,	0);
	class_addmethod(c, (method)scope_notify,		"notify",		A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 225 225");

	CLASS_ATTR_LONG				(c, "order", ATTR_SET_OPAQUE_USER, t_scope, f_order);
	CLASS_ATTR_CATEGORY			(c, "order", 0, "Value");
	CLASS_ATTR_ORDER			(c, "order", 0, "1");
	CLASS_ATTR_LABEL			(c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_FILTER_MIN		(c, "order", 1);
	CLASS_ATTR_DEFAULT			(c, "order", 0, "3");
	CLASS_ATTR_SAVE				(c, "order", 1);
	
	CLASS_ATTR_LONG				(c, "interval", 0, t_scope, f_interval);
	CLASS_ATTR_CATEGORY			(c, "interval", 0, "Value");
	CLASS_ATTR_ORDER			(c, "interval", 0, "3");
	CLASS_ATTR_LABEL			(c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN		(c, "interval", 20);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "100");
	CLASS_ATTR_SAVE				(c, "interval", 1);
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_scope, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "1. 1. 1. 1.");
	
	CLASS_ATTR_RGBA				(c, "txcolor", 0, t_scope, f_colorText);
	CLASS_ATTR_CATEGORY			(c, "txcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "txcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "txcolor", 0, "Text Color");
	CLASS_ATTR_ORDER			(c, "txcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "txcolor", 0, "0. 0. 0. 1.");

	CLASS_ATTR_RGBA				(c, "cicolor", 0, t_scope, f_colorCircle);
	CLASS_ATTR_CATEGORY			(c, "cicolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "cicolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "cicolor", 0, "Circle Color");
	CLASS_ATTR_ORDER			(c, "cicolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "cicolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "phcolor", 0, t_scope, f_colorPositif);
	CLASS_ATTR_CATEGORY			(c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "phcolor", 0, "Positifs Harmonics");
	CLASS_ATTR_ORDER			(c, "phcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "phcolor", 0, "1. 0. 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "nhcolor", 0, t_scope, f_colorNegatif);
	CLASS_ATTR_CATEGORY			(c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "nhcolor", 0, "Negatifs Harmonics");
	CLASS_ATTR_ORDER			(c, "nhcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "nhcolor", 0, "0. 0. 1. 1.");
	
	class_register(CLASS_BOX, c);
	scope_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *scope_new(t_symbol *s, int argc, t_atom *argv)
{
	t_scope *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_scope *)object_alloc(scope_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;
	jbox_new((t_jbox *)x, flags, argc, argv);
	attr_dictionary_process(x, d);
	
	x->j_box.z_box.b_firstin = (t_object *)x;
	dsp_setupjbox((t_pxjbox *)x, x->f_order * 2 + 1);
	
	x->f_clock = clock_new(x,(method)scope_tick);
	x->f_startclock = 0;
	
	x->f_harmonicsValues	= (double *)getbytes((x->f_order * 2 + 1) * sizeof(double));
	x->f_harmonics			= (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	x->f_contributions		= (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	
	scope_vector(x);
	scope_basis(x);
	
	jbox_ready((t_jbox *)x);
	
	return (x);
}			


void scope_dsp64(t_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, scope_perform64, 0, NULL);
	x->f_startclock = 1;
}

void scope_perform64(t_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i, j;
	for(i = 0; i < (x->f_order * 2 + 1); i++)
	{
		for(j = 0; j < sampleframes; j++)
		{
			x->f_harmonicsValues[i] = ins[i][j];
		}
	}
	if (x->f_startclock) 
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void scope_dsp(t_scope *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	pointer_count = (x->f_order * 2 + 1) + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(scope_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
	x->f_startclock = 1;
}

t_int *scope_perform(t_int *w)
{
	t_scope *x			= (t_scope *)(w[1]);
	t_int	sampleframes= (t_int)(w[2]);
	t_float	**ins		= (t_float **)w+3;
	int i, j;
	
	for(i = 0; i < (x->f_order * 2 + 1); i++)
	{
		for(j = 0; j < sampleframes; j++)
		{
			x->f_harmonicsValues[i] = ins[i][j];
		}
	}
	
	if (x->f_startclock) 
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
	return (w + (x->f_order * 2 + 1) + 3);
}

void scope_tick(t_scope *x)
{
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

void scope_free(t_scope *x)
{
	int i;
	dsp_freejbox((t_pxjbox *)x);
	freeobject((t_object *)x->f_clock);
	jbox_free((t_jbox *)x);
	
	freebytes(x->f_harmonicsValues, (x->f_order * 2 + 1) * sizeof(double));
	freebytes(x->f_harmonics, MAXIMUM_SIZE * sizeof(double));
	freebytes(x->f_contributions, MAXIMUM_SIZE * sizeof(double));
	freebytes(x->f_xCircleVector, MAXIMUM_SIZE * sizeof(double));
	freebytes(x->f_yCircleVector, MAXIMUM_SIZE * sizeof(double));
	for(i = 0; i < (x->f_order * 2 + 1); i++)
		freebytes(x->f_harmonicsBasis[i], MAXIMUM_SIZE * sizeof(double));
	
	freebytes(x->f_harmonicsBasis, (x->f_order * 2 + 1) * sizeof(double *));
}

void scope_assist(t_scope *x, void *b, long m, long a, char *s)
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

void scope_vector(t_scope *x)
{
	int i;
	double angularStep;
	
	x->f_xCircleVector		= (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	x->f_yCircleVector		= (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
	for (i = 0; i < MAXIMUM_SIZE; i++)
	{
		angularStep = (JGRAPHICS_2PI / MAXIMUM_SIZE) * (double)i;
		x->f_xCircleVector[i] = cos(JGRAPHICS_2PI - angularStep - JGRAPHICS_PI / 2.);
		x->f_yCircleVector[i] = sin(JGRAPHICS_2PI - angularStep - JGRAPHICS_PI / 2.);
	}
}

void scope_basis(t_scope *x)
{
	int i, j;
	double angularStep;
	
	x->f_harmonicsBasis		= (double **)getbytes((x->f_order * 2 + 1) * sizeof(double *));
	x->f_harmonicsBasis[0]	= (double *)getbytes(MAXIMUM_SIZE * sizeof(double));

	for(i = 0; i < MAXIMUM_SIZE; i++)
		x->f_harmonicsBasis[0][i] = 0.5;
		
	for (j = 1; j <= x->f_order ; j++)
	{
		x->f_harmonicsBasis[j*2]	= (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
		x->f_harmonicsBasis[j*2-1]	= (double *)getbytes(MAXIMUM_SIZE * sizeof(double));
		for(i = 0; i < MAXIMUM_SIZE; i++)
		{
			angularStep = (JGRAPHICS_2PI / MAXIMUM_SIZE) * (double)i;
			x->f_harmonicsBasis[j*2][i] = cos((double)j * angularStep);
			x->f_harmonicsBasis[j*2-1][i] = sin((double)j * angularStep);
		}
	}
}

t_max_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
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

void scope_paint(t_scope *x, t_object *view)
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
	draw_contribution(x, view, &rect);
	draw_harmonics(x, view, &rect);
	
}

void draw_background(t_scope *x,  t_object *view, t_rect *rect)
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
			jgraphics_stroke(g);
			/*
			jgraphics_set_source_jrgba(g, &x->f_colorBackground);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (double)i * x->f_rayonCircle - 1.,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
			*/
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
		//jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		//jgraphics_arc(g, x->f_center.x, x->f_center.y, x->f_rayonCircle - 1.,  0., JGRAPHICS_2PI);
		//jgraphics_fill(g);
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_angle(t_scope *x,  t_object *view, t_rect *rect)
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

void draw_contribution(t_scope *x,  t_object *view, t_rect *rect)
{
	int i, j;
	double x1, y1, biggestcontrib;

	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[64];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("contrib_layer"), rect->width, rect->height);
	
	if (g) 
	{	
		x->f_biggestContrib = 0.;
		biggestcontrib = 0.;
		for (i = 0; i < MAXIMUM_SIZE; i++)
		{    
			x->f_contributions[i] = 0.;		
			for(j = 0; j < (x->f_order * 2 + 1); j++)
			{
				x->f_contributions[i] += x->f_harmonicsBasis[j][i] * x->f_harmonicsValues[j];
			}
			
			if (fabs(x->f_contributions[i]) > x->f_biggestContrib)
			{
				x->f_biggestContrib = fabs(x->f_contributions[i]);
				biggestcontrib = (x->f_biggestContrib + 0.5 * x->f_harmonicsValues[0]) / ((double)(x->f_order + 1) * 4.);
			}
		}
	
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

void draw_harmonics(t_scope *x,  t_object *view, t_rect *rect)
{
	int i;
	double rayon, angle, normalization, factor;
	double x1, y1, x2, y2;
	double energyX, energyY, velocityX, velocityY;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);

	
	if (g) 
	{
		rayon = x->f_rayonCircle * 5.;
		if(x->f_biggestContrib > 1.)
			normalization = rayon / x->f_biggestContrib;
		else
			normalization = rayon;
		
		energyX = x->f_xCircleVector[0] * x->f_contributions[0] * x->f_contributions[0];
		energyY = x->f_yCircleVector[0] * x->f_contributions[0] * x->f_contributions[0];
		
		velocityX = x->f_xCircleVector[0] * x->f_contributions[0];
		velocityY = x->f_yCircleVector[0] * x->f_contributions[0];

		x1 =  x->f_xCircleVector[0] * fabs(x->f_contributions[0]) * normalization + x->f_center.x;
		y1 =  x->f_yCircleVector[0] * fabs(x->f_contributions[0]) * normalization + x->f_center.y;
				
		for(i = 1; i < MAXIMUM_SIZE; i++)
		{
			energyX += x->f_xCircleVector[i] * x->f_contributions[i] * x->f_contributions[i];
			energyY += x->f_yCircleVector[i] * x->f_contributions[i] * x->f_contributions[i];
			
			velocityX += x->f_xCircleVector[i] * x->f_contributions[i];
			velocityY += x->f_yCircleVector[i] * x->f_contributions[i];
			
			x2 =  x->f_xCircleVector[i] * fabs(x->f_contributions[i]) * normalization + x->f_center.x;
			y2 =  x->f_yCircleVector[i] * fabs(x->f_contributions[i]) * normalization + x->f_center.y;
			
            if (x->f_contributions[i] < 0.)
            {
				
				if(i > 1 && x->f_contributions[i-1] >= 0.)
				{
					x2 = x->f_center.x;
					y2 = x->f_center.y;
				}
				jgraphics_set_source_jrgba(g, &x->f_colorPositif);
            }
            else
            {
				if(i > 1 && x->f_contributions[i-1] < 0.)
				{
					x1 = x->f_center.x;
					y1 = x->f_center.y;
				}
				jgraphics_set_source_jrgba(g, &x->f_colorNegatif);
            }
			
			if(i == MAXIMUM_SIZE - 1)
			{
				x2 =  x->f_xCircleVector[0] * fabs(x->f_contributions[0]) * normalization + x->f_center.x;
				y2 =  x->f_yCircleVector[0] * fabs(x->f_contributions[0]) * normalization + x->f_center.y;
			}
			
			jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
			x1 = x2;
			y1 = y2;
			
		}
		
		/* Energy */
		//jgraphics_set_source_rgba(g, 0.08, .43, 0.41, 1.);
//		
//		factor = (x->f_rayonCircle * 5.) / sqrt(energyX * energyX + energyY * energyY);
//		energyX *= factor;
//		energyY *= factor;
//		x1 =  energyX + x->f_center.x;
//		y1 =  energyY + x->f_center.y;
//		jgraphics_line_draw_fast(g, x->f_center.x, x->f_center.y, x1, y1, 1.);
//		angle = atan2(energyY, energyX);
//		rayon = sqrt(energyX * energyX + energyY * energyY);
//		
//		rayon -= x->f_rayonCircle / 4.;
//		angle -= JGRAPHICS_PI / 100.;
//		jgraphics_line_draw_fast(g, x1, y1, rayon * cos(angle)+ x->f_center.x, rayon * sin(angle)+ x->f_center.y, 1.);
//		angle += JGRAPHICS_PI / 50.;
//		jgraphics_line_draw_fast(g, x1, y1, rayon * cos(angle)+ x->f_center.x, rayon * sin(angle)+ x->f_center.y, 1.);
//		
		/* Velocity */
		//jgraphics_set_source_rgba(g, 0.32, .18, 0.45, 1.);
//
//		factor = (x->f_rayonCircle * 5.) / sqrt(velocityX * velocityX + velocityY * velocityY);
//		velocityX *= factor;
//		velocityY *= factor;
//		x1 =  velocityX + x->f_center.x;
//		y1 =  velocityY + x->f_center.y;
//		jgraphics_line_draw_fast(g, x->f_center.x, x->f_center.y, x1, y1, 1.);
//		angle = atan2(velocityY, velocityX);
//		rayon = sqrt(velocityX * velocityX + velocityY * velocityY);
//		
//		rayon -= x->f_rayonCircle / 4.;
//		angle -= JGRAPHICS_PI / 100.;
//		jgraphics_line_draw_fast(g, x1, y1, rayon * cos(angle)+ x->f_center.x, rayon * sin(angle)+ x->f_center.y, 1.);
//		angle += JGRAPHICS_PI / 50.;
//		jgraphics_line_draw_fast(g, x1, y1, rayon * cos(angle)+ x->f_center.x, rayon * sin(angle)+ x->f_center.y, 1.);
		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
}

