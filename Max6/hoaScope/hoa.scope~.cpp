/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "z_dsp.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
}

#include "../CicmLibrary/CicmTools.h"
#include "../hoaAmbisonics/AmbisonicsViewer.h"

typedef struct  _scope 
{
	t_pxjbox	j_box;
	
	void*		f_clock;
	int			f_startclock;
	t_atom_long	f_interval;
	t_atom_long	f_order;
    t_atom_long	f_process_mode;
    t_atom_long f_bufsize;
    t_atom_long f_drawCircle;
    t_atom_long f_drawContributions;
    t_atom_long f_drawAngles;
	
	t_jrgba		f_colorBackground;
    t_jrgba     f_bordercolor;
	t_jrgba		f_colorText;
	t_jrgba		f_colorNegatif;
	t_jrgba		f_colorPositif;
	
	t_rect		f_center;
	double		f_rayonGlobal;
	double		f_rayonAngle;
	double		f_rayonCircle;
	double		f_fontsize;
    
    AmbisonicsViewer* f_viewer;
    double*     f_harmonicsValues;
    long        f_sampleCounter;
    double*     f_averageHarmo;
	
} t_scope;

t_class *scope_class;

void *scope_new(t_symbol *s, int argc, t_atom *argv);
void scope_free(t_scope *x);
void scope_assist(t_scope *x, void *b, long m, long a, char *s);
void scope_tick(t_scope *x);

void scope_dsp(t_scope *x, t_signal **sp, short *count);
t_int *scope_perform(t_int *w);

void scope_dsp64(t_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void scope_perform64(t_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
long scope_oksize(t_scope *x, t_rect *newrect);
void scope_getdrawparams(t_scope *x, t_object *patcherview, t_jboxdrawparams *params);
/* Paint *********************************************/
void scope_paint(t_scope *x, t_object *view);
void draw_background(t_scope *x, t_object *view, t_rect *rect);
void draw_angles(t_scope *x,  t_object *view, t_rect *rect);
void draw_contribution(t_scope *x,  t_object *view, t_rect *rect);
void draw_harmonics(t_scope *x,  t_object *view, t_rect *rect);

void scope_resize_inputs(t_scope *x, long newNumberOfInput);
t_max_err scope_setattr_order(t_scope *x, t_object *attr, long ac, t_atom *av);

int C74_EXPORT main()
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
	class_addmethod(c, (method)scope_getdrawparams, "getdrawparams", A_CANT, 0);
	class_addmethod(c, (method)scope_oksize,		"oksize",		A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 225 225");

    CLASS_ATTR_LONG             (c, "order", 0, t_scope, f_order);
    CLASS_ATTR_ACCESSORS        (c, "order", (method)NULL,(method)scope_setattr_order);
	CLASS_ATTR_CATEGORY			(c, "order", 0, "Value");
	CLASS_ATTR_ORDER			(c, "order", 0, "1");
	CLASS_ATTR_LABEL			(c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_FILTER_MIN		(c, "order", 1);
	CLASS_ATTR_DEFAULT			(c, "order", 0, "3");
	CLASS_ATTR_SAVE				(c, "order", 1);
	
    CLASS_ATTR_LONG             (c, "mode", 0, t_scope, f_process_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Value");
    CLASS_ATTR_ENUMINDEX2       (c, "mode", 0, "Peak", "Average");
	CLASS_ATTR_ORDER			(c, "mode", 0, "2");
	CLASS_ATTR_LABEL			(c, "mode", 0, "Process Mode");
	CLASS_ATTR_DEFAULT			(c, "mode", 0, "0");
	CLASS_ATTR_SAVE				(c, "mode", 1);
    
    CLASS_ATTR_LONG             (c, "bufsize", 0, t_scope, f_bufsize);
	CLASS_ATTR_CATEGORY			(c, "bufsize", 0, "Value");
	CLASS_ATTR_ORDER			(c, "bufsize", 0, "3");
    CLASS_ATTR_FILTER_MIN		(c, "bufsize", 1);
	CLASS_ATTR_LABEL			(c, "bufsize", 0, "Buffer Size (in samps)");
	CLASS_ATTR_DEFAULT			(c, "bufsize", 0, "128");
	CLASS_ATTR_SAVE				(c, "bufsize", 1);
    
	CLASS_ATTR_LONG             (c, "interval", 0, t_scope, f_interval);
	CLASS_ATTR_CATEGORY			(c, "interval", 0, "Value");
	CLASS_ATTR_ORDER			(c, "interval", 0, "4");
	CLASS_ATTR_LABEL			(c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN		(c, "interval", 20);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "100");
	CLASS_ATTR_SAVE				(c, "interval", 1);
    
    CLASS_ATTR_ATOM_LONG		(c, "drawcircle", 0, t_scope, f_drawCircle);
	CLASS_ATTR_CATEGORY			(c, "drawcircle", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "drawcircle", 0, "1");
	CLASS_ATTR_STYLE_LABEL		(c, "drawcircle", 0, "onoff", "Draw Circle");
	CLASS_ATTR_DEFAULT			(c, "drawcircle", 0, "1");
	CLASS_ATTR_SAVE				(c, "drawcircle", 1);
    
    CLASS_ATTR_ATOM_LONG		(c, "drawangles", 0, t_scope, f_drawAngles);
	CLASS_ATTR_CATEGORY			(c, "drawangles", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "drawangles", 0, "2");
	CLASS_ATTR_STYLE_LABEL		(c, "drawangles", 0, "onoff", "Draw Angles");
	CLASS_ATTR_DEFAULT			(c, "drawangles", 0, "1");
	CLASS_ATTR_SAVE				(c, "drawangles", 1);
    
    CLASS_ATTR_ATOM_LONG		(c, "drawcontrib", 0, t_scope, f_drawContributions);
	CLASS_ATTR_CATEGORY			(c, "drawcontrib", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "drawcontrib", 0, "3");
	CLASS_ATTR_STYLE_LABEL		(c, "drawcontrib", 0, "onoff", "Draw Contributions");
	CLASS_ATTR_DEFAULT			(c, "drawcontrib", 0, "1");
	CLASS_ATTR_SAVE				(c, "drawcontrib", 1);
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_scope, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.76 0.76 0.76 1.");
    
    CLASS_ATTR_RGBA				(c, "bordercolor", 0, t_scope, f_bordercolor);
	CLASS_ATTR_CATEGORY			(c, "bordercolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bordercolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bordercolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bordercolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bordercolor", 0, "0.7 0.7 0.7 1.");
	
	CLASS_ATTR_RGBA				(c, "txcolor", 0, t_scope, f_colorText);
	CLASS_ATTR_CATEGORY			(c, "txcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "txcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "txcolor", 0, "Text Color");
	CLASS_ATTR_ORDER			(c, "txcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "txcolor", 0, "0. 0. 0. 7.");
	
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
            | JBOX_DRAWBACKGROUND
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;
	jbox_new((t_jbox *)x, flags, argc, argv);
    
    x->f_order = 3;
    x->f_sampleCounter = 0;
    
	x->j_box.z_box.b_firstin = (t_object *)x;
	dsp_setupjbox((t_pxjbox *)x, x->f_order * 2 + 1);
	
	x->f_clock = clock_new(x,(method)scope_tick);
	x->f_startclock = 0;
    
    x->f_viewer = new AmbisonicsViewer(x->f_order);
	x->f_harmonicsValues = new double[x->f_order * 2 + 1];
    x->f_averageHarmo = new double[x->f_order * 2 + 1];
    for (int i = 0; i < x->f_order * 2 + 1; i++)
    {
        x->f_harmonicsValues[i] = 0.;
        x->f_averageHarmo[i] = 0.;
    }
    
    attr_dictionary_process(x, d);
	
	jbox_ready((t_jbox *)x);
	
	return (x);
}

t_max_err scope_setattr_order(t_scope *x, t_object *attr, long ac, t_atom *av)
{
    long d;
	if (ac && av)
    {
        if (atom_gettype(av) == A_LONG)
        {
            d = Tools::clip_min( long(atom_getlong(av)), long(1));
            if (d != x->f_order)
            {
                int dspState = sys_getdspobjdspstate((t_object*)x);
                if(dspState)
                    object_method(gensym("dsp")->s_thing, gensym("stop"));
                
                free(x->f_harmonicsValues);
                free(x->f_averageHarmo);
                delete x->f_viewer;
                x->f_viewer = new AmbisonicsViewer(d);
                x->f_order = x->f_viewer->getOrder();
                x->f_harmonicsValues = new double[x->f_order * 2 + 1];
                x->f_averageHarmo = new double[x->f_order * 2 + 1];
                scope_resize_inputs(x, x->f_order * 2 + 1);
                
                if(dspState)
                    object_method(gensym("dsp")->s_thing, gensym("start"));
            }
        }
	}
	return MAX_ERR_NONE;
}

void scope_resize_inputs(t_scope *x, long newNumberOfInput)
{
    newNumberOfInput = Tools::clip_min(newNumberOfInput, long(1));
    t_object *b = NULL;
    object_obex_lookup(x, _sym_pound_B, (t_object **)&b);
    object_method(b, gensym("dynlet_begin"));
    dsp_resize((t_pxobject*)x, newNumberOfInput);
    object_method(b, gensym("dynlet_end"));
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
        if (x->f_process_mode == 1) // average
        {
            for(j = 0; j < sampleframes; j++)
            {
                x->f_averageHarmo[i] += ins[i][j];
                x->f_sampleCounter++;
                if (x->f_sampleCounter >= x->f_bufsize)
                {
                    x->f_harmonicsValues[i] = x->f_averageHarmo[i] / x->f_bufsize;
                    x->f_averageHarmo[i] = x->f_sampleCounter = 0.;
                }
            }
        }
        else
        {
            x->f_harmonicsValues[i] = ins[i][0]; // first sample only
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
	t_scope *x			 = (t_scope *)(w[1]);
	t_int	sampleframes = (t_int)(w[2]);
	t_float	**ins		 = (t_float **)w+3;
    int i, j;
    for(i = 0; i < (x->f_order * 2 + 1); i++)
    {
        if (x->f_process_mode == 1) // average
        {
            for(j = 0; j < sampleframes; j++)
            {
                x->f_averageHarmo[i] += ins[i][j];
                x->f_sampleCounter++;
                if (x->f_sampleCounter >= x->f_bufsize)
                {
                    x->f_harmonicsValues[i] = x->f_averageHarmo[i] / x->f_bufsize;
                    x->f_averageHarmo[i] = x->f_sampleCounter = 0.;
                }
            }
        }
        else
        {
            x->f_harmonicsValues[i] = ins[i][0]; // first sample only
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
    x->f_viewer->processContribAndRep(x->f_harmonicsValues);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

void scope_free(t_scope *x)
{
	dsp_freejbox((t_pxjbox *)x);
	freeobject((t_object *)x->f_clock);
	jbox_free((t_jbox *)x);
    
    free(x->f_harmonicsValues);
    free(x->f_averageHarmo);
    delete x->f_viewer;
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

t_max_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if( name == gensym("bgcolor") || name == gensym("drawcircle") )
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
			jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
		}
        else if(name == gensym("order"))
		{
            jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void scope_getdrawparams(t_scope *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = 2;
	params->d_cornersize = 6;
    params->d_bordercolor = x->f_bordercolor;
    params->d_boxfillcolor = x->f_colorBackground;
}

long scope_oksize(t_scope *x, t_rect *newrect)
{
	if (newrect->width < 20)
		newrect->width = newrect->height = 20;
	return 0;
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
	
	if (x->f_drawCircle) draw_background(x, view, &rect);
    if (x->f_drawAngles) draw_angles(x, view, &rect);
    if (x->f_drawContributions) draw_contribution(x, view, &rect);
    draw_harmonics(x, view, &rect);
}

void draw_background(t_scope *x,  t_object *view, t_rect *rect)
{
	int i;
	double y1, y2, rotateAngle;
    t_jmatrix transform;
    t_jrgba black, white;
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
    
    black = white = x->f_colorBackground;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
    
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);

	if (g) 
	{
		/* Background */
        /*
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_rectangle_rounded(g, 0., 0., rect->width, rect->height, 6, 6);
		jgraphics_fill(g);
        */
		
		/* Circles */
		for(i = 5; i > 0; i--)
		{
            //inner shadow
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_arc(g, x->f_center.x+0.5, x->f_center.y+0.5, (double)i * x->f_rayonCircle,  0., CICM_2PI);
            jgraphics_stroke(g);
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_arc(g, x->f_center.x, x->f_center.y, (double)i * x->f_rayonCircle,  0., CICM_2PI);
            jgraphics_stroke(g);
		}
		/* Axes */
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
        jgraphics_set_source_jrgba(g, &black);
		//for(i = 0; i < 12; i++)
        for(i = 0; i < (x->f_order * 2 + 2) ; i++)
		{
            rotateAngle = ( (double)i/(x->f_order * 2 + 2) * CICM_2PI ) - ( 0.5/(x->f_order * 2 + 2) * CICM_2PI );
			jgraphics_rotate(g, rotateAngle);
			
			y1 = 1. / 6. * x->f_rayonGlobal;
			y2 = 5. / 6. * x->f_rayonGlobal;
			
			if ( (rotateAngle <= CICM_PI && rotateAngle > 0.) )
            {
                jgraphics_move_to(g, -0.5, y1-0.5);
                jgraphics_line_to(g, -0.5, y2-0.5);
            }
            else
            {
                jgraphics_move_to(g, 0.5, y1+0.5);
                jgraphics_line_to(g, 0.5, y2+0.5);
            }
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_stroke(g);
            
			jgraphics_move_to(g, 0, y1);
			jgraphics_line_to(g, 0, y2);
            jgraphics_set_source_jrgba(g, &black);
			jgraphics_set_line_width(g, 1);
			jgraphics_stroke(g);
			
			jgraphics_rotate(g, -rotateAngle);
		}
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_angles(t_scope *x,  t_object *view, t_rect *rect)
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
		for(i = 0; i < (x->f_order*2+2); i++)
		{
			x1 = x->f_rayonAngle * cos((double)-i * CICM_2PI / (x->f_order*2+2) - CICM_PI / 2.) + x->f_center.x;
			y1 = x->f_rayonAngle * sin((double)-i * CICM_2PI / (x->f_order*2+2) - CICM_PI / 2.) + x->f_center.y;
		
            sprintf(text,"%ld°", long( (360*i) / (x->f_order*2+2) ) );
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
	double x1, y1, biggestcontrib;
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[64];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("contrib_layer"), rect->width, rect->height);
	
	if (g)
	{
		x1 = x->f_center.x;
		y1 = x->f_center.y - 2 * x->f_fontsize;
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->f_fontsize * 0.75);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorText);
        
        biggestcontrib = (x->f_viewer->getBiggestContribution() + 0.5 * x->f_harmonicsValues[0]) / ((double)(x->f_order + 1) * 4.);
		
		for(int i = 1; i < 5; i++)
		{
			sprintf(text,"%.2f", (float)(i * biggestcontrib));
			jtextlayout_set(jtl, text, jf, x1 - x->f_fontsize * 2, y1 - i * x->f_rayonCircle, x->f_fontsize * 4, x->f_fontsize, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
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
	int pathLength = 0;
	t_pt beginCoord;
    t_jpath* posHarmPath = NULL;
    t_jpath* negHarmPath = NULL;
    t_jmatrix transform;
    t_jrgba shadcolor = {0.4, 0.4, 0.4, 0.9};
    double alphaShadow = 1.;
    long posPathLen, negPathLen;
    long precIndex = 0;
    double factor;
    posPathLen = negPathLen = 0;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);
    
    if (alphaShadow > x->f_colorPositif.alpha ) alphaShadow = x->f_colorPositif.alpha;
	if (alphaShadow > x->f_colorNegatif.alpha ) alphaShadow = x->f_colorNegatif.alpha;
	alphaShadow -= 0.5;
	if (alphaShadow < 0.) alphaShadow = 0;
	shadcolor.alpha = alphaShadow;
    
	if (g)
	{
		jgraphics_set_line_join(g, JGRAPHICS_LINE_JOIN_ROUND);
        jgraphics_set_line_cap(g, JGRAPHICS_LINE_CAP_ROUND);
		jgraphics_set_line_width(g, 1);
		if(x->f_viewer->getBiggestContribution() > 0.)
		{
            factor = (x->f_rayonGlobal * 5. / 6.);
            if (x->f_viewer->getBiggestContribution() > 1)
                factor /= x->f_viewer->getBiggestContribution();
            
            Tools::clip(&factor, 0., (x->f_rayonGlobal * 5. / 6.));
			
            // positiv harmonics
			for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
			{
				precIndex = i-1;
                if (precIndex < 0) precIndex += NUMBEROFCIRCLEPOINTS_UI;
                
				if (i == NUMBEROFCIRCLEPOINTS_UI-1) {
					jgraphics_line_to(g, beginCoord.x, beginCoord.y );
				}
				else if(x->f_viewer->getColor(i) == 1 || x->f_viewer->getColor(i) == 0)
				{
					if (pathLength == 0)
					{
						beginCoord.x = x->f_viewer->getAbscisseValue(i) * factor;
						beginCoord.y = x->f_viewer->getOrdinateValue(i) * factor;
						jgraphics_move_to(g, beginCoord.x, beginCoord.y );
						pathLength++;
					}
                    else if(x->f_viewer->getColor(precIndex) != 1)
                    {
                        jgraphics_line_to(g, 0, 0);
                        jgraphics_move_to(g, x->f_viewer->getAbscisseValue(i) * factor, x->f_viewer->getOrdinateValue(i) * factor);
                    }
                    else
                    {
						jgraphics_line_to(g, x->f_viewer->getAbscisseValue(i) * factor, x->f_viewer->getOrdinateValue(i) * factor);
					}
				}
			}
			if (pathLength) {
				//jgraphics_close_path(g);
                posHarmPath = jgraphics_copy_path(g);
			}
            posPathLen = pathLength;
			
			pathLength = 0;
			jgraphics_new_path(g);
			for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i++)
			{
				precIndex = i-1;
                if (precIndex < 0) precIndex += NUMBEROFCIRCLEPOINTS_UI;
                
				if (i == NUMBEROFCIRCLEPOINTS_UI-1) {
					jgraphics_line_to(g, beginCoord.x, beginCoord.y );
				}
				else if(x->f_viewer->getColor(i) == -1 || x->f_viewer->getColor(i) == 0)
				{
					if (!pathLength)
					{
						beginCoord.x = x->f_viewer->getAbscisseValue(i) * factor;
						beginCoord.y = x->f_viewer->getOrdinateValue(i) * factor;
						jgraphics_move_to(g, beginCoord.x, beginCoord.y );
						pathLength++;
					}
                    else if(x->f_viewer->getColor(precIndex) != -1)
                    {
                        jgraphics_line_to(g, 0, 0);
                        jgraphics_move_to(g, x->f_viewer->getAbscisseValue(i) * factor, x->f_viewer->getOrdinateValue(i) * factor);
                    }
                    else
                    {
						jgraphics_line_to(g, x->f_viewer->getAbscisseValue(i) * factor, x->f_viewer->getOrdinateValue(i) * factor);
					}
				}
			}
			if (pathLength) {
				//jgraphics_close_path(g);
                negHarmPath = jgraphics_copy_path(g);
			}
            negPathLen = pathLength;
            
            // draw harmonics :
            if (posPathLen || negPathLen) {
                jgraphics_new_path(g);
                jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
                jgraphics_set_matrix(g, &transform);
                
                // shadows
                if (posPathLen) jgraphics_append_path(g, posHarmPath);
                //if (negPathLen) jgraphics_append_path(g, negHarmPath);
                jgraphics_set_source_jrgba(g, &shadcolor);
                jgraphics_stroke(g);
                
                jgraphics_translate(g, 1, 1);
                // harmocolor
                if (posPathLen) jgraphics_append_path(g, posHarmPath);
                jgraphics_set_source_jrgba(g, &x->f_colorPositif);
                jgraphics_stroke(g);
                
                if (negPathLen) jgraphics_append_path(g, negHarmPath);
                jgraphics_set_source_jrgba(g, &x->f_colorNegatif);
                jgraphics_stroke(g);
            }
		}
		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
}