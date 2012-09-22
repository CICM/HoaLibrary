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

#define MAXIMUM_SIZE 3600

typedef struct  _meter 
{
	t_pxjbox	j_box;
	
	void*		f_clock;
	int			f_startclock;
	int			f_interval;
	
	int			f_numberOfLoudspeakers;
	double		f_offsetOfLoudspeakers;
	
	double*		f_amplitudeOfLoudspeakers;
	double*		f_energyOfLoudspeakers;
	double*		f_abscisseOfLoudspeakers;
	double*		f_ordonneOfLoudspeakers;
	double		f_energyVectorX;
	double		f_energyVectorY;
	
	t_jrgba		f_colorBackground;
	t_jrgba		f_colorText;
	t_jrgba		f_colorCircle;
	t_jrgba		f_colorColdSignal;
	t_jrgba		f_colorTepidSignal;
	t_jrgba		f_colorWarmSignal;
	t_jrgba		f_colorHotSignal;
	t_jrgba		f_colorOverSignal;
	
	t_jrgba		f_colorEnergy;
	t_jrgba		f_colorVelocity;
	
	t_rect		f_center;
	double		f_rayonGlobal;
	double		f_rayonCircle;
	double		f_fontsize;
	
} t_meter;

t_class *meter_class;

void *meter_new(t_symbol *s, int argc, t_atom *argv);
void meter_free(t_meter *x);
void meter_assist(t_meter *x, void *b, long m, long a, char *s);
void meter_tick(t_meter *x);

void meter_dsp(t_meter *x, t_signal **sp, short *count);
t_int *meter_perform(t_int *w);

void meter_dsp64(t_meter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void meter_perform64(t_meter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err meter_notify(t_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

/* Paint *********************************************/
void meter_paint(t_meter *x, t_object *view);
void draw_background(t_meter *x, t_object *view, t_rect *rect);
void draw_meter(t_meter *x,  t_object *view, t_rect *rect);
void draw_vector(t_meter *x, t_object *view, t_rect *rect);
void draw_angle(t_meter *x,  t_object *view, t_rect *rect);

int main()
{
	t_class *c;

	c = class_new("hoa.meter~", (method)meter_new, (method)meter_free, (short)sizeof(t_meter), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method)meter_dsp,			"dsp",			A_CANT, 0);
	class_addmethod(c, (method)meter_dsp64,			"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)meter_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)meter_paint,			"paint",		A_CANT,	0);
	class_addmethod(c, (method)meter_notify,		"notify",		A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 225 225");

	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
	CLASS_ATTR_LONG				(c, "ls", ATTR_SET_OPAQUE_USER, t_meter, f_numberOfLoudspeakers);
	CLASS_ATTR_CATEGORY			(c, "ls", 0, "Value");
	CLASS_ATTR_ORDER			(c, "ls", 0, "1");
	CLASS_ATTR_LABEL			(c, "ls", 0, "Number of Loudspeakers");
	CLASS_ATTR_FILTER_MIN		(c, "ls", 3);
	CLASS_ATTR_DEFAULT			(c, "ls", 0, "8");
	CLASS_ATTR_SAVE				(c, "ls", 1);
	//CLASS_ATTR_INVISIBLE		(c, "ls", 1);
	
	CLASS_ATTR_DOUBLE			(c, "offset", 0, t_meter, f_offsetOfLoudspeakers);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Value");
	CLASS_ATTR_ORDER			(c, "offset", 0, "2");
	CLASS_ATTR_LABEL			(c, "offset", 0, "Offset of Loudspeakers");
	CLASS_ATTR_FILTER_CLIP		(c, "offset", -1., 1.);
	CLASS_ATTR_DEFAULT			(c, "offset", 0, "0");
	CLASS_ATTR_SAVE				(c, "offset", 1);
	
	CLASS_ATTR_LONG				(c, "interval", 0, t_meter, f_interval);
	CLASS_ATTR_CATEGORY			(c, "interval", 0, "Value");
	CLASS_ATTR_ORDER			(c, "interval", 0, "3");
	CLASS_ATTR_LABEL			(c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN		(c, "interval", 20);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "100");
	CLASS_ATTR_SAVE				(c, "interval", 1);
								
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_meter, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "1. 1. 1. 1.");
	
	CLASS_ATTR_RGBA				(c, "txcolor", 0, t_meter, f_colorText);
	CLASS_ATTR_CATEGORY			(c, "txcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "txcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "txcolor", 0, "Text Color");
	CLASS_ATTR_ORDER			(c, "txcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "txcolor", 0, "1. 1. 1. 1.");

	CLASS_ATTR_RGBA				(c, "cicolor", 0, t_meter, f_colorCircle);
	CLASS_ATTR_CATEGORY			(c, "cicolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "cicolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "cicolor", 0, "Circle Color");
	CLASS_ATTR_ORDER			(c, "cicolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "cicolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "coldcolor", 0, t_meter, f_colorColdSignal);
	CLASS_ATTR_CATEGORY			(c, "coldcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "coldcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "coldcolor", 0, "Cold Signal Color");
	CLASS_ATTR_ORDER			(c, "coldcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "coldcolor", 0, "0. 0.6 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "tepidcolor", 0, t_meter, f_colorTepidSignal);
	CLASS_ATTR_CATEGORY			(c, "tepidcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "tepidcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "tepidcolor", 0, "Tepid Signal Color");
	CLASS_ATTR_ORDER			(c, "tepidcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "tepidcolor", 0, "0.6 0.73 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "warmcolor", 0, t_meter, f_colorWarmSignal);
	CLASS_ATTR_CATEGORY			(c, "warmcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "warmcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "warmcolor", 0, "Warm Signal Color");
	CLASS_ATTR_ORDER			(c, "warmcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "warmcolor", 0, ".85 .85 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "hotcolor", 0, t_meter, f_colorHotSignal);
	CLASS_ATTR_CATEGORY			(c, "hotcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "hotcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "hotcolor", 0, "Hot Signal Color");
	CLASS_ATTR_ORDER			(c, "hotcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "hotcolor", 0, "1. 0.6 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "overcolor", 0, t_meter, f_colorOverSignal);
	CLASS_ATTR_CATEGORY			(c, "overcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "overcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "overcolor", 0, "Overload Signal Color");
	CLASS_ATTR_ORDER			(c, "overcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "overcolor", 0, "1. 0. 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "energycolor", 0, t_meter, f_colorEnergy);
	CLASS_ATTR_CATEGORY			(c, "energycolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "energycolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "energycolor", 0, "Energy Vector Color");
	CLASS_ATTR_ORDER			(c, "energycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "energycolor", 0, "0. 0. 1. 1.");
	
	//CLASS_ATTR_RGBA				(c, "velocitycolor", 0, t_meter, f_colorEnergy);
//	CLASS_ATTR_CATEGORY			(c, "velocitycolor", 0, "Color");
//	CLASS_ATTR_STYLE			(c, "velocitycolor", 0, "rgba");
//	CLASS_ATTR_LABEL			(c, "velocitycolor", 0, "Energy Vector Color");
//	CLASS_ATTR_ORDER			(c, "velocitycolor", 0, "10");
//	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "energycolor", 0, ".74 .18 .76 1.");
	
	class_register(CLASS_BOX, c);
	meter_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *meter_new(t_symbol *s, int argc, t_atom *argv)
{
	t_meter *x =  NULL; 
	t_dictionary *d;
	long flags;
	int i;
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_meter *)object_alloc(meter_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;
	
	attr_dictionary_process(x, d);
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
	dsp_setupjbox((t_pxjbox *)x, x->f_numberOfLoudspeakers);
	x->f_energyOfLoudspeakers = (double *)getbytes(x->f_numberOfLoudspeakers * sizeof(double));
	x->f_amplitudeOfLoudspeakers = (double *)getbytes(x->f_numberOfLoudspeakers * sizeof(double));
	x->f_abscisseOfLoudspeakers = (double *)getbytes(x->f_numberOfLoudspeakers * sizeof(double));
	x->f_ordonneOfLoudspeakers = (double *)getbytes(x->f_numberOfLoudspeakers * sizeof(double));
	for(i = 0; i < x->f_numberOfLoudspeakers; i++)
	{
		x->f_energyOfLoudspeakers[i] = 0.00001;
		x->f_amplitudeOfLoudspeakers[i] = 0.000001;
		x->f_abscisseOfLoudspeakers[i] = cos(((double)(x->f_numberOfLoudspeakers - i) / (double)x->f_numberOfLoudspeakers) * JGRAPHICS_2PI);
		x->f_ordonneOfLoudspeakers[i] = sin(((double)(x->f_numberOfLoudspeakers - i) / (double)x->f_numberOfLoudspeakers) * JGRAPHICS_2PI);
	}
	x->f_clock = clock_new(x,(method)meter_tick);
	x->f_startclock = 0;
	
	jbox_ready((t_jbox *)x);
	
	return (x);
}			

void meter_dsp64(t_meter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, meter_perform64, 0, NULL);
}

void meter_perform64(t_meter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i;
	while (sampleframes--) 
	{
		for(i = 0; i < x->f_numberOfLoudspeakers; i++)
		{
			if(abs(ins[i][sampleframes]) > abs(x->f_amplitudeOfLoudspeakers[sampleframes]))
				x->f_amplitudeOfLoudspeakers[sampleframes] = ins[i][sampleframes];
		}
	}
	if (x->f_startclock) 
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}	
}

void meter_dsp(t_meter *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	pointer_count = x->f_numberOfLoudspeakers + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(meter_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
	x->f_startclock = 1;
}

t_int *meter_perform(t_int *w)
{
	t_meter *x			= (t_meter *)(w[1]);
	t_int	sampleframes= (t_int)(w[2]);
	t_float	**ins		= (t_float **)w+3;
	int i, j;
	double max;
	
	for(i = 0; i < x->f_numberOfLoudspeakers; i++)
	{
		max = x->f_amplitudeOfLoudspeakers[i];
		for(j = 0; j < sampleframes; j++)
		{
			if(fabs(ins[i][j]) > fabs(max))
				max = ins[i][j];
		}
		x->f_amplitudeOfLoudspeakers[i] = max;
	}
	
	if (x->f_startclock) 
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
	return (w + x->f_numberOfLoudspeakers + 3);
}

void meter_tick(t_meter *x)
{
	int i;
	double sum = 0., square = 0.;
	x->f_energyVectorX = 0.;
	x->f_energyVectorY = 0.;
	for(i = 0; i < x->f_numberOfLoudspeakers; i++)
	{
		x->f_energyOfLoudspeakers[i] = 20. * log10(fabs(x->f_amplitudeOfLoudspeakers[i]));
		square = x->f_amplitudeOfLoudspeakers[i] * x->f_amplitudeOfLoudspeakers[i];
		
		x->f_energyVectorX += square * x->f_abscisseOfLoudspeakers[i];
		x->f_energyVectorY += square * x->f_ordonneOfLoudspeakers[i];
		sum += square;
		
		x->f_amplitudeOfLoudspeakers[i] = 0.000000000001;
		
	}
	if (sum == 0.) 
	{
		x->f_energyVectorX = 0.;
		x->f_energyVectorY = 0.;
	}
	else
	{
		x->f_energyVectorX /= sum;
		x->f_energyVectorY /= sum;
	}
	jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("vector_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
	jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

void meter_free(t_meter *x)
{
	dsp_freejbox((t_pxjbox *)x);
	freeobject((t_object *)x->f_clock);
	jbox_free((t_jbox *)x);
	freebytes(x->f_energyOfLoudspeakers, x->f_numberOfLoudspeakers * sizeof(double));
	freebytes(x->f_amplitudeOfLoudspeakers, x->f_numberOfLoudspeakers * sizeof(double));
	freebytes(x->f_abscisseOfLoudspeakers, x->f_numberOfLoudspeakers * sizeof(double));
	freebytes(x->f_ordonneOfLoudspeakers, x->f_numberOfLoudspeakers * sizeof(double));
}

void meter_assist(t_meter *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"Loudspeakers %ld", a);
	}
}


t_max_err meter_notify(t_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("bgcolor") || name == gensym("cicolor") || name == gensym("coldcolor") || name == gensym("tepidcolor") || name == gensym("warmcolor") || name == gensym("hotcolor") || name == gensym("overcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
		else if(name == gensym("txcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
		}
		else if(name == gensym("energycolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("vector_layer"));
		}
		else if(name == gensym("offset"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("vector_layer"));
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void meter_paint(t_meter *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	
	x->f_center.x = rect.width * .5;
	x->f_center.y = rect.height * .5;
	
	x->f_rayonGlobal = rect.width * .5;
	if(rect.width > rect.height)
		x->f_rayonGlobal = rect.height * .5;
	
	x->f_fontsize = (x->f_rayonGlobal / 14.) - 1.;
	x->f_rayonCircle = x->f_rayonGlobal / 32;
	
	draw_background(x, view, &rect);
	draw_meter(x, view, &rect);
	draw_vector(x, view, &rect);
	//draw_angle(x, view, &rect);
}

void draw_background(t_meter *x,  t_object *view, t_rect *rect)
{
	int i;
	double x1, y1;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);

	if (g) 
	{
		/* Background */
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_rectangle_fill_fast(g, 0., 0., rect->width, rect->height);
		
		/* Exterior circle */
		jgraphics_set_source_jrgba(g, &x->f_colorCircle);
		jgraphics_arc(g, x->f_center.x, x->f_center.y, 30. * x->f_rayonCircle + 1.,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		
		/* Cold circle */
		for(i = 3; i > 0; i--)
		{
			jgraphics_set_source_jrgba(g, &x->f_colorColdSignal);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (27. + i) * x->f_rayonCircle,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
			jgraphics_set_source_jrgba(g, &x->f_colorBackground);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (26. + i) * x->f_rayonCircle + 1.,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
		}
		
		/* Tepid circle */
		for(i = 3; i > 0; i--)
		{
			jgraphics_set_source_jrgba(g, &x->f_colorTepidSignal);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (24. + i) * x->f_rayonCircle,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
			jgraphics_set_source_jrgba(g, &x->f_colorBackground);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (23. + i) * x->f_rayonCircle + 1.,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
		}
		
		/* Warm circle */
		for(i = 3; i > 0; i--)
		{
			jgraphics_set_source_jrgba(g, &x->f_colorWarmSignal);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (21. + i) * x->f_rayonCircle,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
			jgraphics_set_source_jrgba(g, &x->f_colorBackground);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (20. + i) * x->f_rayonCircle + 1.,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
		}
		
		/* Hot circle */
		for(i = 3; i > 0; i--)
		{
			jgraphics_set_source_jrgba(g, &x->f_colorHotSignal);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (18. + i) * x->f_rayonCircle,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
			jgraphics_set_source_jrgba(g, &x->f_colorBackground);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, (17. + i) * x->f_rayonCircle + 1.,  0., JGRAPHICS_2PI);
			jgraphics_fill(g);
		}

		/* Over Circle */
		jgraphics_set_source_jrgba(g, &x->f_colorOverSignal);
		jgraphics_arc(g, x->f_center.x, x->f_center.y, (17.5 + i) * x->f_rayonCircle,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_arc(g, x->f_center.x, x->f_center.y, (16. + i) * x->f_rayonCircle + 1.,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		
		/* Axes */
		jgraphics_set_source_jrgba(g, &x->f_colorCircle);
		for(i = 0; i < x->f_numberOfLoudspeakers; i++)
		{
			x1 = (30. * x->f_rayonCircle + 1.) * cos((double)i * JGRAPHICS_2PI / x->f_numberOfLoudspeakers - 0.5 * JGRAPHICS_2PI / x->f_numberOfLoudspeakers + x->f_offsetOfLoudspeakers * JGRAPHICS_2PI) + x->f_center.x;
			y1 = (30. * x->f_rayonCircle + 1.) * sin((double)i * JGRAPHICS_2PI / x->f_numberOfLoudspeakers - 0.5 * JGRAPHICS_2PI / x->f_numberOfLoudspeakers + x->f_offsetOfLoudspeakers * JGRAPHICS_2PI) + x->f_center.y;
			jgraphics_line_draw_fast(g, x1, y1, x->f_center.x, x->f_center.y, 3.);
		}
		
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_meter(t_meter *x, t_object *view, t_rect *rect)
{
	int i, index;
	double angle1, angle2, radius, radianMax, x1, y1, offset;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("meter_layer"), rect->width, rect->height);
	
	if (g) 
	{
		angle2 = JGRAPHICS_2PI / x->f_numberOfLoudspeakers;
		radianMax = 30. * x->f_rayonCircle;
		/* Meters */
		offset = x->f_offsetOfLoudspeakers * JGRAPHICS_2PI - 0.5 * JGRAPHICS_2PI / x->f_numberOfLoudspeakers - 0.5 * JGRAPHICS_PI;
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		for(i = 0; i < x->f_numberOfLoudspeakers; i++)
		{
			angle1 = (x->f_numberOfLoudspeakers - i) * JGRAPHICS_2PI / x->f_numberOfLoudspeakers + offset;
			index = x->f_energyOfLoudspeakers[i] / -3.;
			if(index < 0) 
				index = 0;
			if(index > 14)
				index = 14;

			radius = (index + 16) * x->f_rayonCircle / 2.;
			jgraphics_set_line_width(g, (index + 16) * x->f_rayonCircle);
			jgraphics_arc(g, x->f_center.x, x->f_center.y, radius, angle1, angle1 + angle2);
			jgraphics_stroke(g);
		}
		
		/* Axes */
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		for(i = 0; i < x->f_numberOfLoudspeakers; i++)
		{
			x1 = (30. * x->f_rayonCircle + 2.) * cos((double)i * JGRAPHICS_2PI / x->f_numberOfLoudspeakers - 0.5 * JGRAPHICS_2PI / x->f_numberOfLoudspeakers + x->f_offsetOfLoudspeakers * JGRAPHICS_2PI) + x->f_center.x;
			y1 = (30. * x->f_rayonCircle + 2.) * sin((double)i * JGRAPHICS_2PI / x->f_numberOfLoudspeakers - 0.5 * JGRAPHICS_2PI / x->f_numberOfLoudspeakers + x->f_offsetOfLoudspeakers * JGRAPHICS_2PI) + x->f_center.y;
			jgraphics_line_draw_fast(g, x1, y1, x->f_center.x, x->f_center.y, 1.);
		}
		
		jbox_end_layer((t_object*)x, view, gensym("meter_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("meter_layer"), 0., 0.);
}

void draw_vector(t_meter *x, t_object *view, t_rect *rect)
{
	double x1, y1, energyX, energyY, angle, rayon, value;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("vector_layer"), rect->width, rect->height);
	
	if (g) 
	{
		/* Energy */
		jgraphics_set_source_jrgba(g, &x->f_colorEnergy);
		if (x->f_energyVectorX == 0.) 
			value = 0.;
		else
			value = atan2(x->f_energyVectorY, x->f_energyVectorX);
		
		angle = value + x->f_offsetOfLoudspeakers * JGRAPHICS_2PI + 1.5 * JGRAPHICS_PI;
		rayon = (15 * x->f_rayonCircle);
		
		energyX = rayon * cos(angle);
		energyY = rayon * sin(angle);
		x1 = energyX + x->f_center.x;
		y1 = energyY + x->f_center.y;
		jgraphics_line_draw_fast(g, x1, y1, x->f_center.x, x->f_center.y, 1.);
		
		
		rayon -= x->f_rayonCircle;
		angle -= JGRAPHICS_PI / 60;
		jgraphics_line_draw_fast(g, x1, y1, rayon * cos(angle)+ x->f_center.x, rayon * sin(angle)+ x->f_center.y, 1.);
		angle += JGRAPHICS_PI / 30;
		jgraphics_line_draw_fast(g, x1, y1, rayon * cos(angle)+ x->f_center.x, rayon * sin(angle)+ x->f_center.y, 1.);
		
		/* Center */
		jgraphics_arc(g, x->f_center.x, x->f_center.y, 3, 0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		
		jbox_end_layer((t_object*)x, view, gensym("vector_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("vector_layer"), 0., 0.);
}

void draw_angle(t_meter *x,  t_object *view, t_rect *rect)
{
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("angle_layer"), rect->width, rect->height);
	
	if (g) 
	{
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->f_fontsize);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorText); 
						
		sprintf(text,"Energy : %d°", (int)(atan2(x->f_energyVectorY, x->f_energyVectorX) / JGRAPHICS_2PI * 360));
		jtextlayout_set(jtl, text, jf, x->f_fontsize, rect->height - x->f_fontsize, x->f_fontsize * 3., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
		jtextlayout_draw(jtl, g);
			
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("angle_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("angle_layer"), 0., 0.);
}



