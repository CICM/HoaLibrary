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

extern "C"
{
#include "../../../PdEnhanced/Sources/cicm_wrapper.h"
}

#include "../../Sources/HoaLibrary.h"


typedef struct  _scope
{
	t_edspbox   j_box;
    AmbisonicViewer* f_viewer;
    double*     f_harmonics_values;
    
	t_clock*	f_clock;
	int			f_startclock;
	long        f_interval;
	long        f_order;
    float       f_normalize;
	
	t_rgba		f_color_background;
    t_rgba      f_color_border_box;
	t_rgba		f_color_negatif;
	t_rgba		f_color_positif;
	
	float		f_center;
	float		f_radius_global;
	float		f_radius_circle;
   
} t_scope;

t_eclass *scope_class;

void *scope_new(t_symbol *s, int argc, t_atom *argv);
void scope_free(t_scope *x);
void scope_assist(t_scope *x, void *b, long m, long a, char *s);
void scope_tick(t_scope *x);

void scope_dsp(t_scope *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void scope_perform(t_scope *x, t_object *d, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_pd_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
long scope_oksize(t_scope *x, t_rect *newrect);
void scope_getdrawparams(t_scope *x, t_object *patcherview, t_edrawparams *params);

void scope_paint(t_scope *x, t_object *view);
void draw_background(t_scope *x, t_object *view, t_rect *rect);
void draw_harmonics(t_scope *x,  t_object *view, t_rect *rect);

t_pd_err scope_setattr_order(t_scope *x, t_object *attr, long ac, t_atom *av);

extern "C" void setup_hoa0x2escope_tilde(void)
{
	t_eclass *c;

	c = eclass_new("hoa.scope~", (method)scope_new, (method)scope_free, (short)sizeof(t_scope), 0L, A_GIMME, 0);

    eclass_dspinit(c);
    eclass_init(c, 0);
	
	eclass_addmethod(c, (method)scope_dsp,              "dsp",          A_CANT, 0);
	eclass_addmethod(c, (method)scope_assist,           "assist",		A_CANT,	0);
	eclass_addmethod(c, (method)scope_paint,			"paint",		A_CANT,	0);
	eclass_addmethod(c, (method)scope_notify,           "notify",		A_CANT, 0);
	eclass_addmethod(c, (method)scope_getdrawparams,    "getdrawparams",A_CANT, 0);
	eclass_addmethod(c, (method)scope_oksize,           "oksize",		A_CANT, 0);

    CLASS_ATTR_INVISIBLE            (c, "fontname", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontweight", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontslant", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontsize", 1);
    CLASS_ATTR_INVISIBLE            (c, "send", 1);
	CLASS_ATTR_DEFAULT              (c, "size", 0, "225. 225.");

    CLASS_ATTR_LONG                 (c, "order", 0, t_scope, f_order);
    CLASS_ATTR_ACCESSORS            (c, "order", NULL, scope_setattr_order);
	CLASS_ATTR_CATEGORY             (c, "order", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "order", 0, "1");
	CLASS_ATTR_LABEL                (c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_FILTER_MIN           (c, "order", 1);
	CLASS_ATTR_DEFAULT              (c, "order", 0, "3");
	CLASS_ATTR_SAVE                 (c, "order", 1);
    CLASS_ATTR_STYLE                (c, "order", 1, "number");
    
    CLASS_ATTR_FLOAT                (c, "gain", 0, t_scope, f_normalize);
	CLASS_ATTR_CATEGORY             (c, "gain", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "gain", 0, "2");
	CLASS_ATTR_LABEL                (c, "gain", 0, "Gain factor");
	CLASS_ATTR_FILTER_MIN           (c, "gain", 1.);
	CLASS_ATTR_DEFAULT              (c, "gain", 0, "1.");
	CLASS_ATTR_SAVE                 (c, "gain", 1);
    CLASS_ATTR_STYLE                (c, "gain", 1, "number");
    
	CLASS_ATTR_LONG                 (c, "interval", 0, t_scope, f_interval);
	CLASS_ATTR_CATEGORY             (c, "interval", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "interval", 0, "3");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval (in ms)");
	CLASS_ATTR_FILTER_CLIP          (c, "interval", 20, 1000);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "20");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
	CLASS_ATTR_STYLE                (c, "interval", 1, "number");
    
	CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_scope, f_color_background);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.7 0.7 0.7 1.");
	CLASS_ATTR_STYLE                (c, "bgcolor", 1, "color");
    
    CLASS_ATTR_RGBA					(c, "bdcolor", 0, t_scope, f_color_border_box);
	CLASS_ATTR_CATEGORY				(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bdcolor", 0, "0.5 0.5 0.5 1.");
	CLASS_ATTR_STYLE                (c, "bdcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "phcolor", 0, t_scope, f_color_positif);
	CLASS_ATTR_CATEGORY             (c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "phcolor", 0, "Positifs Harmonics Color");
	CLASS_ATTR_ORDER                (c, "phcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "phcolor", 0, "1. 0. 0. 1.");
	CLASS_ATTR_STYLE                (c, "phcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "nhcolor", 0, t_scope, f_color_negatif);
	CLASS_ATTR_CATEGORY             (c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "nhcolor", 0, "Negatifs Harmonics Color");
	CLASS_ATTR_ORDER                (c, "nhcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "nhcolor", 0, "0. 0. 1. 1.");
	CLASS_ATTR_STYLE                (c, "nhcolor", 1, "color");
    
    eclass_register(CLASS_BOX, c);
    hoa_post();
	scope_class = c;
	
}

void *scope_new(t_symbol *s, int argc, t_atom *argv)
{
	t_scope *x =  NULL; 
	t_binbuf *d;
	long flags;
	
	if (!(d = binbuf_via_atoms(argc, argv)))
		return NULL;

	x = (t_scope *)eobj_new(scope_class);
    x->f_order = 1;
    x->f_normalize = 1.;
	x->f_startclock         = 0;
	x->f_viewer             = new AmbisonicViewer(1);
    x->f_clock              = clock_new(x, (t_method)scope_tick);
    x->f_harmonics_values   = new double[3];
    for(int i = 0; i < 3; i++)
        x->f_harmonics_values[i] = 0.;
    eobj_dspsetup(x, x->f_order * 2 + 1, 0);
    
	flags = 0 
			| EBOX_IGNORELOCKCLICK
			| EBOX_GROWLINK
			;
	ebox_new((t_ebox *)x, flags);
    
    
    ebox_attrprocess_viabinbuf(x, d);
	ebox_ready((t_ebox *)x);
	
	return (x);
}

t_pd_err scope_setattr_order(t_scope *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av)
    {
        if (atom_gettype(av) == A_LONG)
        {
            long d = Tools::clip_min(long(atom_getlong(av)), long(1));
            if (d != x->f_order)
            {
                int dspState = canvas_suspend_dsp();
            
                free(x->f_harmonics_values);
                delete x->f_viewer;
                x->f_viewer = new AmbisonicViewer(d);
                x->f_order = x->f_viewer->getOrder();
                x->f_harmonics_values    = new double[x->f_order * 2 + 1];
                eobj_resize_inputs((t_ebox *)x, x->f_order * 2 + 1);
                canvas_update_dsp();
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
            x->f_harmonics_values[i] = ins[i][0] * x->f_normalize;
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
    x->f_viewer->processContribAndRep(x->f_harmonics_values);
	ebox_invalidate_layer((t_ebox *)x, gensym("harmonics_layer"));
	ebox_redraw((t_ebox *)x);
    if (sys_getdspstate())
		clock_delay(x->f_clock, x->f_interval);
}

void scope_free(t_scope *x)
{
    ebox_free((t_ebox *)x);
    clock_free(x->f_clock);
    free(x->f_harmonics_values);
    delete x->f_viewer;
}

void scope_assist(t_scope *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_viewer->getHarmonicsName(a).c_str());
}

t_pd_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("attr_modified"))
	{
		if( s == gensym("bgcolor") || s == gensym("drawcircle") || s == gensym("order"))
		{
			ebox_invalidate_layer((t_ebox *)x, gensym("background_layer"));
            ebox_invalidate_layer((t_ebox *)x, gensym("harmonics_layer"));
		}
		else if(s == gensym("phcolor") || s == gensym("nhcolor"))
		{
			ebox_invalidate_layer((t_ebox *)x, gensym("harmonics_layer"));
		}
		ebox_redraw((t_ebox *)x);
	}
	return 0;
}

void scope_getdrawparams(t_scope *x, t_object *patcherview, t_edrawparams *params)
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
	ebox_get_rect_for_view((t_ebox *)x, &rect);
	
	x->f_center = rect.width * .5;
	x->f_center = rect.height * .5;
	
	x->f_radius_global = rect.width * .49;
	if(rect.width > rect.height)
		x->f_radius_global = rect.height * .5;
	
	x->f_radius_circle = x->f_radius_global / 5;
	
    draw_background(x, view, &rect);
    draw_harmonics(x, view, &rect);
}

void draw_background(t_scope *x,  t_object *view, t_rect *rect)
{
    t_matrix transform;
    t_rgba black, white;
    
    black = rgba_addContrast(x->f_color_background, -0.14);
    white = rgba_addContrast(x->f_color_background, 0.06);
    
	t_elayer *g = ebox_start_layer((t_ebox *)x, gensym("background_layer"), rect->width, rect->height);

	if (g) 
	{
		for(int i = 5; i > 0; i--)
		{
            egraphics_set_line_width(g, 1);
            egraphics_set_color_rgba(g, &white);
            egraphics_arc(g, long(x->f_center)+0.5, long(x->f_center)+0.5, (double)i * x->f_radius_circle,  0., CICM_2PI);
            egraphics_stroke(g);
            egraphics_set_line_width(g, 1);
            egraphics_set_color_rgba(g, &black);
            egraphics_arc(g, long(x->f_center)-0.5, long(x->f_center)-0.5, (double)i * x->f_radius_circle,  0., CICM_2PI);
            egraphics_stroke(g);
		}
        
        egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		egraphics_set_matrix(g, &transform);
		double coso, sino, angle, x1, y1, x2, y2;

		for(int i = 0; i < (x->f_order * 2 + 2); i++)
		{
            egraphics_set_color_rgba(g, &white);
            angle = ((double)i / (x->f_order * 2 + 2) * CICM_2PI ) - (0.5 / (x->f_order * 2 + 2) * CICM_2PI);
            coso = cos(angle);
            sino = sin(angle);
            x1 = x->f_radius_circle * coso;
            y1 = x->f_radius_circle * sino;
            x2 = x->f_radius_global * coso;
            y2 = x->f_radius_global * sino;
            
            if(Tools::isInsideDeg(angle / CICM_2PI * 360., 45, 225))
            {
                egraphics_move_to(g, x1 - 0.5, y1 - 0.5);
                egraphics_line_to(g, x2 - 0.5, y2 - 0.5);
            }
            else
            {
                egraphics_move_to(g, x1 + 0.5, y1 + 0.5);
                egraphics_line_to(g, x2 + 0.5, y2 + 0.5);
            }
            egraphics_stroke(g);
            
            egraphics_set_color_rgba(g, &black);
            egraphics_move_to(g, x1, y1);
            egraphics_line_to(g, x2, y2);
            egraphics_stroke(g);
			
		}
		
		ebox_end_layer((t_ebox *)x, gensym("background_layer"));
	}
	ebox_paint_layer((t_ebox *)x, gensym("background_layer"), 0., 0.);
}

void draw_harmonics(t_scope *x,  t_object *view, t_rect *rect)
{
    t_matrix transform;
	t_elayer *g = ebox_start_layer((t_ebox *)x, gensym("harmonics_layer"), rect->width, rect->height);
    
	if (g)
	{
        t_rgba grey  = {0.5, 0.5, 0.5, 1.};
		egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		egraphics_set_matrix(g, &transform);
        
		if(x->f_viewer->getBiggestContribution() > 0.)
		{
            egraphics_set_line_width(g, 1.);
            double shadow = 1.;
            double x1;
            double y1;
            
            x1 = x->f_viewer->getAbscisseValue(0) * x->f_radius_global + shadow;
            y1 = x->f_viewer->getOrdinateValue(0) * x->f_radius_global + shadow;
            egraphics_move_to(g, x1, y1);
            for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i += 2)
			{
                x1 = x->f_viewer->getAbscisseValue(i) * x->f_radius_global + shadow;
                y1 = x->f_viewer->getOrdinateValue(i) * x->f_radius_global  + shadow;
                egraphics_line_to(g, x1, y1);
            }
            x1 = x->f_viewer->getAbscisseValue(0) * x->f_radius_global + shadow;
            y1 = x->f_viewer->getOrdinateValue(0) * x->f_radius_global + shadow;
            egraphics_line_to(g, x1, y1);
            egraphics_set_color_rgba(g, &grey);
            egraphics_stroke(g);
            
            egraphics_set_line_width(g, 1.);
            int color = x->f_viewer->getColor(0);
            x1 = x->f_viewer->getAbscisseValue(0) * x->f_radius_global;
            y1 = x->f_viewer->getOrdinateValue(0) * x->f_radius_global;
            egraphics_move_to(g, x1, y1);
            
			for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i += 2)
			{
                if(x->f_viewer->getColor(i) == color)
                {
                    x1 = x->f_viewer->getAbscisseValue(i) * x->f_radius_global;
                    y1 = x->f_viewer->getOrdinateValue(i) * x->f_radius_global;
                    egraphics_line_to(g, x1, y1);
                }
                else
                {
                    if(color == 1)
                        egraphics_set_color_rgba(g, &x->f_color_positif);
                    else
                        egraphics_set_color_rgba(g, &x->f_color_negatif);
                    
                    egraphics_line_to(g, x1, y1);
                    egraphics_stroke(g);
                    
                    color = x->f_viewer->getColor(i);
                    x1 = x->f_viewer->getAbscisseValue(i) * x->f_radius_global;
                    y1 = x->f_viewer->getOrdinateValue(i) * x->f_radius_global;
                    egraphics_move_to(g, x1, y1);
                }
            }
            
            x1 = x->f_viewer->getAbscisseValue(0) * x->f_radius_global;
            y1 = x->f_viewer->getOrdinateValue(0) * x->f_radius_global;
            egraphics_line_to(g, x1, y1);
            if(color == 1)
                egraphics_set_color_rgba(g, &x->f_color_positif);
            else
                egraphics_set_color_rgba(g, &x->f_color_negatif);
            egraphics_stroke(g);
		}
		ebox_end_layer((t_ebox*)x, gensym("harmonics_layer"));
	}
	ebox_paint_layer((t_ebox *)x, gensym("harmonics_layer"), 0., 0.);
    
}