/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../hoaLibrary/hoa.library_pd.h"


typedef struct  _scope
{
	t_jbox      j_box;
	
	t_clock*	f_clock;
	int			f_startclock;
	long        f_interval;
	long        f_order;
    
    long        f_drawCircle;
    long        f_drawContributions;
    long        f_drawAngles;
    float       f_normalize;
	
	t_jrgba		f_color_background;
    t_jrgba     f_color_border_box;
	t_jrgba		f_colorText;
	t_jrgba		f_colorNegatif;
	t_jrgba		f_colorPositif;
	
	t_rect		f_center;
	double		f_rayonGlobal;
	double		f_rayonAngle;
	double		f_rayonCircle;
	double		f_fontsize;
    
    AmbisonicViewer* f_viewer;
    double*     f_harmonicsValues;
    long        f_sampleCounter;
    double*     f_averageHarmo;
    
} t_scope;

t_eclass *scope_class;

void *scope_new(t_symbol *s, int argc, t_atom *argv);
void scope_free(t_scope *x);
void scope_assist(t_scope *x, void *b, long m, long a, char *s);
void scope_tick(t_scope *x);

void scope_dsp(t_scope *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void scope_perform(t_scope *x, t_object *d, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_max_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
long scope_oksize(t_scope *x, t_rect *newrect);
void scope_getdrawparams(t_scope *x, t_object *patcherview, t_jboxdrawparams *params);
/* Paint *********************************************/
void scope_paint(t_scope *x, t_object *view);
void draw_background(t_scope *x, t_object *view, t_rect *rect);
void draw_angles(t_scope *x,  t_object *view, t_rect *rect);
void draw_contribution(t_scope *x,  t_object *view, t_rect *rect);
void draw_harmonics(t_scope *x,  t_object *view, t_rect *rect);

t_max_err scope_setattr_order(t_scope *x, t_object *attr, long ac, t_atom *av);

extern "C" void setup_hoa0x2escope_tilde(void)
{
	t_eclass *c;

	c = class_new("hoa.scope~", (method)scope_new, (method)scope_free, (short)sizeof(t_scope), 0L, A_GIMME, 0);

	class_dspinitjbox(c);
    
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);

	class_addmethod(c, (method)scope_dsp,			"dsp",          A_CANT, 0);
	class_addmethod(c, (method)scope_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)scope_paint,			"paint",		A_CANT,	0);
	class_addmethod(c, (method)scope_notify,		"notify",		A_CANT, 0);
	class_addmethod(c, (method)scope_getdrawparams, "getdrawparams", A_CANT, 0);
	class_addmethod(c, (method)scope_oksize,		"oksize",		A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "size", 0, "225 225");

    CLASS_ATTR_LONG             (c, "order", 0, t_scope, f_order);
    CLASS_ATTR_ACCESSORS        (c, "order", (method)NULL,(method)scope_setattr_order);
	CLASS_ATTR_CATEGORY			(c, "order", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "order", 0, "1");
	CLASS_ATTR_LABEL			(c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_FILTER_MIN		(c, "order", 1);
	CLASS_ATTR_DEFAULT			(c, "order", 0, "3");
	CLASS_ATTR_SAVE				(c, "order", 1);
    
    CLASS_ATTR_FLOAT            (c, "gain", 0, t_scope, f_normalize);
	CLASS_ATTR_CATEGORY			(c, "gain", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "gain", 0, "2");
	CLASS_ATTR_LABEL			(c, "gain", 0, "Gain factor");
	CLASS_ATTR_FILTER_MIN		(c, "gain", 1.);
	CLASS_ATTR_DEFAULT			(c, "gain", 0, "1.");
	CLASS_ATTR_SAVE				(c, "gain", 1);

	CLASS_ATTR_LONG             (c, "interval", 0, t_scope, f_interval);
	CLASS_ATTR_CATEGORY			(c, "interval", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "interval", 0, "3");
	CLASS_ATTR_LABEL			(c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN		(c, "interval", 20);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "100");
	CLASS_ATTR_SAVE				(c, "interval", 1);
    
    CLASS_ATTR_LONG             (c, "drawcircle", 0, t_scope, f_drawCircle);
	CLASS_ATTR_CATEGORY			(c, "drawcircle", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "drawcircle", 0, "1");
	CLASS_ATTR_STYLE            (c, "drawcircle", 0, "onoff");
    CLASS_ATTR_LABEL			(c, "drawcircle", 0, "Draw Circle");
	CLASS_ATTR_DEFAULT			(c, "drawcircle", 0, "1");
	CLASS_ATTR_SAVE				(c, "drawcircle", 1);
    
    CLASS_ATTR_LONG             (c, "drawangles", 0, t_scope, f_drawAngles);
	CLASS_ATTR_CATEGORY			(c, "drawangles", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "drawangles", 0, "2");
    CLASS_ATTR_STYLE            (c, "drawangles", 0, "onoff");
    CLASS_ATTR_LABEL			(c, "drawangles", 0, "Draw Angles");
	CLASS_ATTR_DEFAULT			(c, "drawangles", 0, "1");
	CLASS_ATTR_SAVE				(c, "drawangles", 1);
    
    CLASS_ATTR_LONG             (c, "drawcontrib", 0, t_scope, f_drawContributions);
	CLASS_ATTR_CATEGORY			(c, "drawcontrib", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "drawcontrib", 0, "3");
    CLASS_ATTR_STYLE            (c, "drawcontrib", 0, "onoff");
    CLASS_ATTR_LABEL			(c, "drawcontrib", 0, "Draw Contributions");
	CLASS_ATTR_DEFAULT			(c, "drawcontrib", 0, "1");
	CLASS_ATTR_SAVE				(c, "drawcontrib", 1);
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
	CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_scope, f_color_background);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.7 0.7 0.7 1.");
	
    CLASS_ATTR_RGBA					(c, "bordercolor", 0, t_scope, f_color_border_box);
	CLASS_ATTR_CATEGORY				(c, "bordercolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bordercolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bordercolor", 0, "Border Box Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bordercolor", 0, "0.5 0.5 0.5 1.");
	
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
	
    class_register(CLASS_NOBOX, c);
	scope_class = c;
	
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
    
    x->f_order = 1;
    x->f_sampleCounter = 0;
    x->f_normalize = 1.;
	x->j_box.b_firstin = (t_object *)x;

	dsp_setupjbox((t_jbox *)x, x->f_order * 2 + 1, 0);
    
	x->f_clock              = clock_new(x, (t_method)scope_tick);
	x->f_startclock         = 0;
    
	x->f_viewer             = new AmbisonicViewer(x->f_order);
	x->f_harmonicsValues    = new double[x->f_order * 2 + 1];
    x->f_averageHarmo       = new double[x->f_order * 2 + 1];
    for (int i = 0; i < x->f_order * 2 + 1; i++)
    {
        x->f_harmonicsValues[i] = 0.;
        x->f_averageHarmo[i]    = 0.;
    }

    attr_dictionary_process(x, d);
	jbox_ready((t_jbox *)x);
	
	return (x);
}

t_max_err scope_setattr_order(t_scope *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av)
    {
        if (atom_gettype(av) == A_LONG)
        {
            long d = Tools::clip_min(long(atom_getlong(av)), long(1));
            if (d != x->f_order)
            {
                int dspState = canvas_suspend_dsp();
                
                free(x->f_harmonicsValues);
                free(x->f_averageHarmo);
                delete x->f_viewer;
                x->f_viewer = new AmbisonicViewer(d);
                x->f_order = x->f_viewer->getOrder();
                x->f_harmonicsValues    = new double[x->f_order * 2 + 1];
                x->f_averageHarmo       = new double[x->f_order * 2 + 1];
                jbox_resize_inputs((t_jbox *)x, x->f_order * 2 + 1);
                
                canvas_resume_dsp(dspState);
            }
        }
	}
	return 0;
}

void scope_dsp(t_scope *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp, gensym("dsp_add"), x, (method)scope_perform, 0, NULL);
	x->f_startclock = 1;
}

void scope_perform(t_scope *x, t_object *d, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
    for(int i = 0; i < (x->f_order * 2 + 1); i++)
    {
        float maximum = ins[i][0];
        for(int j = 0; j < sf; j++)
        {
            if (fabs(ins[i][j]) >= fabs(maximum))
            {
                maximum = ins[i][0];
            }
            x->f_harmonicsValues[i] = ins[i][0] * x->f_normalize;
        }
    }
    
	if (x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void scope_tick(t_scope *x)
{
    x->f_viewer->processContribAndRep(x->f_harmonicsValues);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_redraw((t_jbox *)x);
    if (sys_getdspstate())
		clock_delay(x->f_clock, x->f_interval);
}

void scope_free(t_scope *x)
{
	dsp_freejbox((t_jbox *)x);
    clock_free(x->f_clock);
    
    free(x->f_harmonicsValues);
    free(x->f_averageHarmo);
    delete x->f_viewer;
}

void scope_assist(t_scope *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_viewer->getHarmonicsName(a).c_str());
}

t_max_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("attr_modified"))
	{
		if( s == gensym("bgcolor") || s == gensym("drawcircle") )
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
        else if(s == gensym("drawangles"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
		}
		else if(s == gensym("txcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
		}
		else if(s == gensym("phcolor") || s == gensym("nhcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
		}
        else if(s == gensym("order"))
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
    params->d_boxfillcolor = x->f_color_background;
    params->d_bordercolor = x->f_color_border_box;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

long scope_oksize(t_scope *x, t_rect *newrect)
{
	newrect->width = pd_clip_min(newrect->width, 30.);
    newrect->height = pd_clip_min(newrect->height, 30.);
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
	
	x->f_fontsize = (x->f_rayonGlobal / 14.) - 2.;
	x->f_rayonAngle = 5. / 6. * x->f_rayonGlobal + x->f_fontsize * 1.5;
	x->f_rayonCircle = x->f_rayonGlobal / 6;
	
	if (x->f_drawCircle) 
		draw_background(x, view, &rect);
    if (x->f_drawAngles) 
		draw_angles(x, view, &rect);
    if (x->f_drawContributions)
		draw_contribution(x, view, &rect);
    draw_harmonics(x, view, &rect);
}

void draw_background(t_scope *x,  t_object *view, t_rect *rect)
{
    t_jmatrix transform;
    t_jrgba black, white;
    
    double contrastBlack = 0.14;
    double contrastWhite = 0.06;
    
    black = white = x->f_color_background;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
    
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);

	if (g) 
	{
		/* Circles */
		for(int i = 5; i > 0; i--)
		{
            //inner shadow
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_arc(g, long(x->f_center.x)+0.5, long(x->f_center.y)+0.5, (double)i * x->f_rayonCircle,  0., CICM_2PI);
            jgraphics_stroke(g);
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_arc(g, long(x->f_center.x)-0.5, long(x->f_center.y)-0.5, (double)i * x->f_rayonCircle,  0., CICM_2PI);
            jgraphics_stroke(g);
		}
        
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		double coso, sino, angle, x1, y1, x2, y2, rad1, rad2;
        rad1 = 1. / 6. * x->f_rayonGlobal;
        rad2 = 5. / 6. * x->f_rayonGlobal;
		for(int i = 0; i < (x->f_order * 2 + 2); i++)
		{
            jgraphics_set_source_jrgba(g, &white);
            angle = ( (double)i/(x->f_order * 2 + 2) * CICM_2PI ) - ( 0.5/(x->f_order * 2 + 2) * CICM_2PI );
            coso = cos(angle);
            sino = sin(angle);
            x1 = rad1 * coso;
            y1 = rad1 * sino;
            x2 = rad2 * coso;
            y2 = rad2 * sino;
            
            if(Tools::isInsideDeg(angle / CICM_2PI * 360., 45, 225))
            {
                jgraphics_move_to(g, x1 - 0.5, y1 - 0.5);
                jgraphics_line_to(g, x2 - 0.5, y2 - 0.5);
            }
            else
            {
                jgraphics_move_to(g, x1 + 0.5, y1 + 0.5);
                jgraphics_line_to(g, x2 + 0.5, y2 + 0.5);
            }
            jgraphics_stroke(g);
            
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_move_to(g, x1, y1);
            jgraphics_line_to(g, x2, y2);
            jgraphics_stroke(g);
			
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
		jf = jfont_create(jbox_get_fontname((t_jbox *)x), gensym("regular"), gensym("normal"), x->f_fontsize);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorText);
		for(i = 0; i < (x->f_order*2+2); i++)
		{
			x1 = (x->f_rayonAngle - x->f_fontsize / 2.) * cos((double)-i * CICM_2PI / (x->f_order*2+2) - CICM_PI / 2.) + x->f_center.x;
			y1 = (x->f_rayonAngle - x->f_fontsize / 2.) * sin((double)-i * CICM_2PI / (x->f_order*2+2) - CICM_PI / 2.) + x->f_center.y;
		
            sprintf(text,"%i°", (int)( (360*i) / (x->f_order*2+2) ) );
			jtextlayout_set(jtl, text, jf, x1, y1, x->f_fontsize * 3., 20, ETEXT_CENTER, ETEXT_NOWRAP);
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
		jf = jfont_create(jbox_get_fontname((t_jbox *)x), gensym("regular"), gensym("normal"), x->f_fontsize * 0.75);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorText);
        
        biggestcontrib = (x->f_viewer->getBiggestContribution() + 0.5 * x->f_harmonicsValues[0]) / ((double)(x->f_order + 1) * 4.);
		
		for(int i = 1; i < 5; i++)
		{
			sprintf(text,"%.2f", (float)(i * biggestcontrib));
			jtextlayout_set(jtl, text, jf, x1, y1 - i * x->f_rayonCircle, x->f_fontsize * 4, x->f_fontsize, ETEXT_UP, ETEXT_NOWRAP);
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
    t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);
    
	if (g)
	{
        t_jrgba grey  = {0.5, 0.5, 0.5, 1.};
		double factor = (x->f_rayonGlobal * 5. / 6.);
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
        
		if(x->f_viewer->getBiggestContribution() > 0.)
		{
            jgraphics_set_line_width(g, 1.);
            double shadow = 1.;
            double x1;
            double y1;
            
            x1 = x->f_viewer->getAbscisseValue(0) * factor + shadow;
            y1 = x->f_viewer->getOrdinateValue(0) * factor + shadow;
            jgraphics_move_to(g, x1, y1);
            for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i += 2)
			{
                x1 = x->f_viewer->getAbscisseValue(i) * factor + shadow;
                y1 = x->f_viewer->getOrdinateValue(i) * factor  + shadow;
                jgraphics_line_to(g, x1, y1);
            }
            x1 = x->f_viewer->getAbscisseValue(0) * factor + shadow;
            y1 = x->f_viewer->getOrdinateValue(0) * factor + shadow;
            jgraphics_line_to(g, x1, y1);
            //jgraphics_smooth_line(g);
            jgraphics_set_source_jrgba(g, &grey);
            jgraphics_stroke(g);
            
            jgraphics_set_line_width(g, 1.);
            int color = x->f_viewer->getColor(0);
            x1 = x->f_viewer->getAbscisseValue(0) * factor;
            y1 = x->f_viewer->getOrdinateValue(0) * factor;
            jgraphics_move_to(g, x1, y1);
            
			for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i += 2)
			{
                if(x->f_viewer->getColor(i) == color)
                {
                    x1 = x->f_viewer->getAbscisseValue(i) * factor;
                    y1 = x->f_viewer->getOrdinateValue(i) * factor;
                    jgraphics_line_to(g, x1, y1);
                }
                else
                {
                    if(color == 1)
                        jgraphics_set_source_jrgba(g, &x->f_colorPositif);
                    else
                        jgraphics_set_source_jrgba(g, &x->f_colorNegatif);
                    
                    jgraphics_line_to(g, x1, y1);
                    //jgraphics_smooth_line(g);
                    jgraphics_stroke(g);
                    
                    
                    color = x->f_viewer->getColor(i);
                    x1 = x->f_viewer->getAbscisseValue(i) * factor;
                    y1 = x->f_viewer->getOrdinateValue(i) * factor;
                    jgraphics_move_to(g, x1, y1);
                }
            }
            
            x1 = x->f_viewer->getAbscisseValue(0) * factor;
            y1 = x->f_viewer->getOrdinateValue(0) * factor;
            jgraphics_line_to(g, x1, y1);
            if(color == 1)
                jgraphics_set_source_jrgba(g, &x->f_colorPositif);
            else
                jgraphics_set_source_jrgba(g, &x->f_colorNegatif);
            
            //jgraphics_smooth_line(g);
            jgraphics_stroke(g);
		}
		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
    
}