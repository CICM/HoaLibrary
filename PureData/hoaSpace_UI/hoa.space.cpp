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

#include "../hoaLibrary/hoa.library_pd.h"

#define NUMBER_OF_CIRCLES 5
#define MAX_CHANNELS 250

typedef struct _hoa_space
{
    t_jbox                  j_box;
    AmbisonicsViewer*       f_viewer;
    AmbisonicRecomposer*    f_recomposer;
    
    t_outlet*   f_out;
    
    t_jrgba		f_color_background;
	t_jrgba		f_color_border_box;
    t_jrgba		f_color_inner_circle;
    t_jrgba		f_color_points;
    t_jrgba     f_color_harmonics;
    
    t_rect		f_center;
    t_pt        f_mousepos;
    long		f_mode;
    
    long        f_number_of_microphones;
    
    double		f_radius_global;
	double		f_radius_circle;
    double      f_radius_ext_circle;
    
	double      f_harmonicsValues[MAX_CHANNELS];
    double      f_mode_values[MAX_CHANNELS];
    double      f_microphonesValues[MAX_CHANNELS];
    t_atom      f_tempory_values[MAX_CHANNELS];
    
    double      f_reference_angle;
    double      f_rotation_max;
    double      f_retractation;
    
} t_hoa_space;

t_eclass *hoa_space_class;

extern "C" void setup_hoa0x2espace(void);
void *hoa_space_new(t_symbol *s, int argc, t_atom *argv);
void hoa_space_free(t_hoa_space *x);
void hoa_space_assist(t_hoa_space *x, void *b, long m, long a, char *s);
void hoa_space_bang(t_hoa_space *x);;
void hoa_space_getdrawparams(t_hoa_space *x, t_object *patcherview, t_jboxdrawparams *params);
void hoa_space_oksize(t_hoa_space *x, t_rect *newrect);

t_max_err hoa_space_channels_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoa_space_notify(t_hoa_space *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err hoa_space_coefficients_set(t_hoa_space *x, t_object *attr, long ac, t_atom *av);

void hoa_space_paint(t_hoa_space *x, t_object *view);
void hoa_space_draw_background(t_hoa_space *x, t_object *view, t_rect *rect);
void hoa_space_draw_microphones(t_hoa_space *x, t_object *view, t_rect *rect);
void hoa_space_draw_harmonics(t_hoa_space *x, t_object *view, t_rect *rect);

void hoa_space_mouse_move(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_down(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_drag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_enddrag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);

void hoa_space_draw_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_rotate_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_retract_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);

void hoa_space_compute(t_hoa_space *x);
void hoa_space_output(t_hoa_space *x);

extern "C" void setup_hoa0x2espace(void)
{
    t_eclass* c;
    c = class_new("hoa.space", (method)hoa_space_new, (method)hoa_space_free, sizeof(t_hoa_space), 0L, A_GIMME, 0);

    jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);
    
    class_addmethod(c, (method)hoa_space_assist,        "assist",           A_CANT, 0);
    class_addmethod(c, (method)hoa_space_paint,         "paint",            A_CANT, 0);
    class_addmethod(c, (method)hoa_space_notify,        "notify",           A_CANT, 0);
    class_addmethod(c, (method)hoa_space_bang,          "bang",             A_CANT, 0);
    class_addmethod(c, (method)hoa_space_getdrawparams, "getdrawparams",    A_CANT, 0);
    class_addmethod(c, (method)hoa_space_oksize,        "oksize",           A_CANT, 0);
    class_addmethod(c, (method)hoa_space_mouse_down,    "mousedown",        A_CANT, 0);
    class_addmethod(c, (method)hoa_space_mouse_move,    "mousemove",        A_CANT, 0);
    class_addmethod(c, (method)hoa_space_mouse_drag,    "mousedrag",        A_CANT, 0);
    class_addmethod(c, (method)hoa_space_mouse_enddrag, "mouseup",          A_CANT, 0);
    class_addmethod(c, (method)hoa_space_coefficients_set,"list",           A_GIMME,0);
    
    CLASS_ATTR_DEFAULT		(c, "patching_rect", 0, "0 0 225 225");
	CLASS_ATTR_INVISIBLE	(c, "color", 0);
	CLASS_ATTR_INVISIBLE	(c, "textcolor", 0);
    
    CLASS_ATTR_LONG             (c, "channels", 0, t_hoa_space, f_number_of_microphones);
	CLASS_ATTR_CATEGORY         (c, "channels", 0, "Behavior");
	CLASS_ATTR_ORDER            (c, "channels", 0, "1");
	CLASS_ATTR_LABEL            (c, "channels", 0, "Number of channels");
	CLASS_ATTR_ACCESSORS        (c, "channels", NULL, hoa_space_channels_set);
    CLASS_ATTR_DEFAULT          (c, "channels", 0, "8");
	CLASS_ATTR_SAVE             (c, "channels", 0);
    CLASS_ATTR_PAINT            (c, "channels", 0);
    
    CLASS_ATTR_DOUBLE_VARSIZE      (c, "coeffs", 0, t_hoa_space, f_microphonesValues, f_number_of_microphones, MAX_CHANNELS);
	CLASS_ATTR_CATEGORY             (c, "coeffs", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "coeffs", 0, "2");
	CLASS_ATTR_LABEL                (c, "coeffs", 0, "Virtuals microphones coefficients");
    CLASS_ATTR_ACCESSORS			(c, "coeffs", NULL, hoa_space_coefficients_set);
	CLASS_ATTR_DEFAULT              (c, "coeffs", 0, "0.");
	CLASS_ATTR_SAVE                 (c, "coeffs", 0);
    CLASS_ATTR_PAINT                (c, "coeffs", 0);
    
	CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_hoa_space, f_color_background);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.7 0.7 0.7 1.");
	
    CLASS_ATTR_RGBA					(c, "bordercolor", 0, t_hoa_space, f_color_border_box);
	CLASS_ATTR_CATEGORY				(c, "bordercolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bordercolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bordercolor", 0, "Border Box Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bordercolor", 0, "0.5 0.5 0.5 1.");
    
	CLASS_ATTR_RGBA					(c, "harmocolor", 0, t_hoa_space, f_color_harmonics);
	CLASS_ATTR_CATEGORY				(c, "harmocolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "harmocolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "harmocolor", 0, "Harmonics color");
    CLASS_ATTR_DEFAULT              (c, "harmocolor", 0, "0. 0.4 0.6 1.");
	CLASS_ATTR_SAVE                 (c, "harmocolor", 0);
    
	CLASS_ATTR_RGBA					(c, "miccolor", 0, t_hoa_space, f_color_points);
	CLASS_ATTR_CATEGORY				(c, "miccolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "miccolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "miccolor", 0, "Virtuals microphones color");
	CLASS_ATTR_DEFAULT              (c, "miccolor", 0, "0. 0. 0. 1.");
	CLASS_ATTR_SAVE                 (c, "miccolor", 0);
    
	CLASS_ATTR_RGBA					(c, "circolor", 0, t_hoa_space, f_color_inner_circle);
	CLASS_ATTR_CATEGORY				(c, "circolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "circolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "circolor", 0, "Circle Inner Color");
	CLASS_ATTR_DEFAULT              (c, "circolor", 0, "0.7 0.7 0.7 1.");
	CLASS_ATTR_SAVE                 (c, "circolor", 0);
    
	CLASS_ATTR_ORDER				(c, "bgcolor", 0, "1");
	CLASS_ATTR_ORDER				(c, "bordercolor", 0, "2");
	CLASS_ATTR_ORDER				(c, "cicolor", 0, "3");
	CLASS_ATTR_ORDER				(c, "circolor", 0, "4");
	CLASS_ATTR_ORDER				(c, "cishadcolor", 0, "5");
	CLASS_ATTR_ORDER				(c, "harmocolor", 0, "6");
	CLASS_ATTR_ORDER				(c, "miccolor", 0, "7");
    
    class_register(CLASS_NOBOX, c);
    hoa_space_class = c;
}

void *hoa_space_new(t_symbol *s, int argc, t_atom *argv)
{
    t_hoa_space *x = NULL;
    t_dictionary *d;
	long flags;
    
    x = (t_hoa_space *)object_alloc(hoa_space_class);
    if (x)
    {
        if (!(d = object_dictionaryarg(argc,argv)))
            return NULL;
        
        flags = 0
            | JBOX_DRAWFIRSTIN
            | JBOX_DRAWINLAST
            | JBOX_TRANSPARENT
            | JBOX_GROWY
            | JBOX_DRAWBACKGROUND
        ;
        
        jbox_new((t_jbox *)x, 1, argc, argv);
        
        x->j_box.b_firstin = (t_object *)x;
        x->f_viewer                 = new AmbisonicsViewer(1);
        x->f_recomposer             = new AmbisonicRecomposer(1, 4);
        x->f_out                    = listout(x);
        x->f_number_of_microphones  = 4;
        
        attr_dictionary_process(x, d);
        jbox_ready((t_jbox *)x);
    }
    return (x);
}

void hoa_space_free(t_hoa_space *x)
{
    jbox_free((t_jbox *)x);
    delete x->f_viewer;
    delete x->f_recomposer;
}

void hoa_space_assist(t_hoa_space *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		sprintf(s,"(Anything) Behavior and appearance");
	}
	else
	{
		if (a == 0)
			sprintf(s,"(List) Virtual microphones coefficients");
        else if (a == 1)
			sprintf(s,"(int) Number of Virtual microphones");
	}
}

t_max_err hoa_space_notify(t_hoa_space *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("attr_modified"))
	{
        if(s == gensym("miccolor"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("microphones_layer"));
        }
        else if(s == gensym("harmocolor"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("microphones_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
        }
        else if(s == gensym("circolor"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("microphones_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
        }
        jbox_redraw((t_jbox *)x);
	}
	return ebox_notify((t_jbox *)x, s, msg, sender, data);
}

void hoa_space_getdrawparams(t_hoa_space *x, t_object *patcherview, t_jboxdrawparams *params)
{
    params->d_boxfillcolor = x->f_color_background;
    params->d_bordercolor = x->f_color_border_box;
	params->d_borderthickness = 2;
	params->d_cornersize = 2;
}

void hoa_space_oksize(t_hoa_space *x, t_rect *newrect)
{
    newrect->width = pd_clip_min(newrect->width, 15.);
    newrect->height = pd_clip_min(newrect->height, 15.);
    
    if(newrect->height > newrect->width)
        newrect->width = newrect->height;
    else
        newrect->height = newrect->width;
}

void hoa_space_bang(t_hoa_space *x)
{
    hoa_space_compute(x);
}

/************************************************************************************/
/***************************** DRAW *************************************************/
/************************************************************************************/

void hoa_space_paint(t_hoa_space *x, t_object *view)
{
    t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
    
    x->f_center.x = rect.width  * .5;
	x->f_center.y = rect.height * .5;
	
	x->f_radius_global = rect.width * .5;
	if(rect.width > rect.height)
		x->f_radius_global = rect.height * .5;
	

    x->f_radius_ext_circle = x->f_radius_global - 5;
    x->f_radius_circle = x->f_radius_ext_circle / NUMBER_OF_CIRCLES;
    
    hoa_space_draw_background(x, view, &rect);
    hoa_space_draw_harmonics(x, view, &rect);
    hoa_space_draw_microphones(x, view, &rect);
}

void hoa_space_draw_background(t_hoa_space *x, t_object *view, t_rect *rect)
{
    t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
	
    if (g)
	{
        t_jmatrix transform;
        jgraphics_matrix_init(&transform, 1, 0, 0, 1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
        
        t_jrgba black  = jrgba_addContrast(x->f_color_inner_circle, -0.12);
        t_jrgba white  = jrgba_addContrast(x->f_color_inner_circle, 0.08);
        
        jgraphics_set_source_jrgba(g, &x->f_color_inner_circle);
		jgraphics_arc(g, 0., 0., x->f_radius_ext_circle,  0.f, JGRAPHICS_2PI);
		jgraphics_fill(g);
		
		for(int i = NUMBER_OF_CIRCLES; i > 0; i--)
		{
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_arc(g, -0.5, -0.5, (double)i * x->f_radius_circle,  0.f, JGRAPHICS_2PI);
            jgraphics_stroke(g);
            
			jgraphics_set_line_width(g, 1);
			jgraphics_set_source_jrgba(g, &black);
			jgraphics_arc(g, 0, 0, (double)i * x->f_radius_circle,  0.f, JGRAPHICS_2PI);
			jgraphics_stroke(g);
		}
        
		double coso, sino, angle, x1, y1, x2, y2, rad1, rad2, offset;
        offset = CICM_PI / (double)x->f_number_of_microphones;
        rad1 = 1. / (double)NUMBER_OF_CIRCLES * x->f_radius_ext_circle;
        rad2 = x->f_radius_ext_circle;
        
		for(int i = 0; i < x->f_number_of_microphones; i++)
		{
            jgraphics_set_source_jrgba(g, &white);
            angle = i * CICM_2PI / (double)x->f_number_of_microphones + offset + CICM_PI2;
            coso = cosf(angle);
            sino = sinf(angle);
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

void hoa_space_draw_microphones(t_hoa_space *x, t_object *view, t_rect *rect)
{
    t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("microphones_layer"), rect->width, rect->height);
    
	if (g)
	{
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		jgraphics_set_source_jrgba(g, &x->f_color_points);
        jgraphics_set_line_width(g, 1);
        double loudspeaker_angle = CICM_2PI / (double)x->f_number_of_microphones;
        double factor1 = (NUMBER_OF_CIRCLES - 1.) * x->f_radius_circle;
        double factor2 = x->f_radius_circle;
        for(int i = 0; i < x->f_number_of_microphones; i++)
        {
            double angle = loudspeaker_angle * (double)(i) + CICM_PI2;
            jgraphics_arc(g, Tools::abscissa(x->f_microphonesValues[i] * factor1 + factor2, angle), Tools::ordinate(x->f_microphonesValues[i] * factor1 + factor2, angle), 3.,  0., JGRAPHICS_2PI);
            jgraphics_fill(g);
        }
		jbox_end_layer((t_object*)x, view, gensym("microphones_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("microphones_layer"), 0., 0.);
}

void hoa_space_draw_harmonics(t_hoa_space *x, t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);
    
	if (g)
	{
        int pathLength = 0;
        t_pt beginCoord;
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		jgraphics_set_line_width(g, 1.);
        
		if(x->f_viewer->getBiggestContribution() != 0.)
		{
            double max = 0.;
            
            double normalize = 1;
            for(int i = 0 ; i < x->f_number_of_microphones; i++)
            {
                if(x->f_microphonesValues[i] > max)
                    max = x->f_microphonesValues[i];
            }
            normalize = max;
            
            
            if(x->f_mode == 1)
                normalize = x->f_rotation_max;
            
            double factor = x->f_radius_ext_circle * normalize;
            
			jgraphics_set_source_jrgba(g, &x->f_color_harmonics);
			for(int i = 0; i < NUMBEROFCIRCLEPOINTS_UI; i += 5)
			{
				
				if (i == NUMBEROFCIRCLEPOINTS_UI-1)
                {
					jgraphics_line_to(g, beginCoord.x, beginCoord.y );
				}
				else if(x->f_viewer->getColor(i) == 1)
				{
					if (pathLength == 0)
					{
						beginCoord.x = x->f_viewer->getAbscisseValue(i) * factor;
						beginCoord.y = x->f_viewer->getOrdinateValue(i) * factor;
						jgraphics_move_to(g, beginCoord.x, beginCoord.y );
						pathLength++;
					}
                    else
                    {
						jgraphics_line_to(g, x->f_viewer->getAbscisseValue(i) * factor,
										  x->f_viewer->getOrdinateValue(i) * factor);
					}
				}
			}
			if (pathLength)
            {
				jgraphics_close_path(g);
				jgraphics_fill(g);
			}
		}
		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
}

/**********************************************************/
/*                      Souris                            */
/**********************************************************/

void hoa_space_mouse_move(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double mapped_x = (pt.x - x->f_center.x) / x->f_center.x;
    double mapped_y = (pt.y - x->f_center.y) / x->f_center.y * -1.;
    double radius   = Tools::radius(mapped_x, mapped_y);
    double angle    = Tools::angle(mapped_x, mapped_y) - CICM_PI2;
    
    x->f_mousepos.x = radius;
    x->f_mousepos.y = angle;
    
    if(modifiers == EMOD_SHIFT)
    {
        x->f_mode = 2;
        jmouse_setcursor(patcherview, (t_jbox *)x, 2);
    }
    else if(modifiers == EMOD_ALT)
    {
        x->f_mode = 1;
        jmouse_setcursor(patcherview, (t_jbox *)x, 5);
    }
    else
    {
        x->f_mode = 0;
        jmouse_setcursor(patcherview, (t_jbox *)x, 1);
    }
}

void hoa_space_mouse_down(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double mapped_x = (pt.x - x->f_center.x) / x->f_center.x;
    double mapped_y = (pt.y - x->f_center.y) / x->f_center.y * -1.;
    double radius   = Tools::radius(mapped_x, mapped_y);
    double angle    = Tools::angle(mapped_x, mapped_y) - CICM_PI2;
    
    if(modifiers == EMOD_SHIFT)
    {
        x->f_mode = 2;
        x->f_retractation = radius;
        for(int i =0; i < x->f_number_of_microphones; i++)
        {
            x->f_mode_values[i] = x->f_microphonesValues[i];
        }
    }
    else if(modifiers == EMOD_ALT)
    {
        x->f_mode = 1;
        x->f_rotation_max = 0.;
        for(int i = 0 ; i < x->f_number_of_microphones; i++)
        {
            if(x->f_microphonesValues[i] > x->f_rotation_max)
                x->f_rotation_max = x->f_microphonesValues[i];
        }
        x->f_reference_angle = angle;
        for(int i =0; i < x->f_number_of_microphones; i++)
            x->f_mode_values[i] = x->f_microphonesValues[i];
    }
    else
    {
        x->f_mode = 0;
        hoa_space_mouse_drag(x, patcherview, pt, modifiers);
    }
}

void hoa_space_mouse_drag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double mapped_x = (pt.x - x->f_center.x) / x->f_center.x;
    double mapped_y = (pt.y - x->f_center.y) / x->f_center.y * -1.;
    double radius   = Tools::radius(mapped_x, mapped_y);
    double angle    = Tools::angle(mapped_x, mapped_y) - CICM_PI2;
    
    x->f_mousepos.x = radius;
    x->f_mousepos.y = angle;
    
    if(x->f_mode == 0)
    {
        hoa_space_draw_points(x, patcherview, pt, modifiers);
    }
    else if(x->f_mode == 1)
    {
        hoa_space_rotate_points(x, patcherview, pt, modifiers);
    }
    else if(x->f_mode == 2)
    {
        hoa_space_retract_points(x, patcherview, pt, modifiers);
    }
    
    jbox_redraw((t_jbox *)x);
}

void hoa_space_mouse_enddrag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    hoa_space_compute(x);
}

void hoa_space_draw_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double loudspeaker_angle = CICM_2PI / (double)x->f_number_of_microphones;
    double loudspeaker_angle_mid = loudspeaker_angle / 2.;
    
    double mapped_x = (pt.x - x->f_center.x);
    double mapped_y = (pt.y - x->f_center.y);

    double angle    = Tools::radian_wrap(Tools::angle(mapped_x, -mapped_y) - CICM_PI2);
    double radius   = Tools::radius(mapped_x, mapped_y);

    if(radius < x->f_radius_circle)
    {
        if(angle > CICM_2PI - loudspeaker_angle_mid || angle < loudspeaker_angle_mid)
            atom_setfloat(x->f_tempory_values, 0.);
        else
        {
            for(int i = 1; i < x->f_number_of_microphones; i++)
            {
                if(angle > i * loudspeaker_angle - loudspeaker_angle_mid && angle < i * loudspeaker_angle + loudspeaker_angle_mid)
                    atom_setfloat(x->f_tempory_values+i, 0.);
            }
        }
    }
    else
    {
        double center_x = Tools::abscissa(x->f_radius_circle, angle - CICM_PI2 + CICM_PI);
        mapped_x = mapped_x - center_x;
        double center_y = Tools::ordinate(x->f_radius_circle, angle - CICM_PI2 + CICM_PI);
        mapped_y = -mapped_y - center_y;
        double radius  = Tools::radius(mapped_x, mapped_y) / (4. * x->f_radius_circle);
        
        if(angle > CICM_2PI - loudspeaker_angle_mid || angle < loudspeaker_angle_mid)
            atom_setfloat(x->f_tempory_values, radius);
        else
        {
            for(int i = 1; i < x->f_number_of_microphones; i++)
            {
                if(angle > i * loudspeaker_angle - loudspeaker_angle_mid && angle < i * loudspeaker_angle + loudspeaker_angle_mid)
                    atom_setfloat(x->f_tempory_values+i, radius);
            }
        }
    }
    
    hoa_space_coefficients_set(x, NULL, x->f_number_of_microphones, x->f_tempory_values);
    hoa_space_output(x);
}

void hoa_space_rotate_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double loudspeaker_angle = CICM_2PI / (double)x->f_number_of_microphones;
    double mapped_x = (pt.x - x->f_center.x) / x->f_center.x;
    double mapped_y = (pt.y - x->f_center.y) / x->f_center.y * -1.;
    double rotation  = Tools::angle(mapped_x, mapped_y) - CICM_PI2;
    double offset = rotation - x->f_reference_angle;
    
    offset *= -1.;
    while(offset < 0.)
        offset += CICM_2PI;
    int nbDecalage = offset / loudspeaker_angle;
    double decimal = (offset - loudspeaker_angle * nbDecalage) / loudspeaker_angle;
    
    double newcoeff;
    int index1, index2;
    
    for(int i = 0; i < x->f_number_of_microphones; i++)
    {
        index1 = ((i + nbDecalage) + x->f_number_of_microphones) % x->f_number_of_microphones;
        index2 = ((i + 1 + nbDecalage) + x->f_number_of_microphones) % x->f_number_of_microphones;
        newcoeff = x->f_mode_values[index2] * decimal + x->f_mode_values[index1] * (1. - decimal);
        atom_setfloat(x->f_tempory_values+i ,newcoeff);
    }
    
    hoa_space_coefficients_set(x, NULL, x->f_number_of_microphones, x->f_tempory_values);
    hoa_space_output(x);
}

void hoa_space_retract_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double mapped_x = (pt.x - x->f_center.x) / x->f_center.x;
    double mapped_y = (pt.y - x->f_center.y) / x->f_center.y * -1.;
    double radius   = (Tools::radius(mapped_x, mapped_y) - (1. / 6.)) * (31. / 20.);
    double offset = x->f_retractation - radius;
    
    for(int i = 0; i < x->f_number_of_microphones; i++)
        atom_setfloat(x->f_tempory_values+i ,x->f_mode_values[i] - offset);
    
    hoa_space_coefficients_set(x, NULL, x->f_number_of_microphones, x->f_tempory_values);
    hoa_space_output(x);
}

t_max_err hoa_space_coefficients_set(t_hoa_space *x, t_object *attr, long ac, t_atom *av)
{
    
    if (ac && av)
    {
        if(atom_gettype(av) == A_FLOAT)
        {
            if(x->f_mode == 0 || x->f_mode == 2)
            {
                for (int i = 0; i < ac && i < x->f_number_of_microphones; i++)
                {
                    if(atom_gettype(av+i) == A_FLOAT)
                        x->f_microphonesValues[i] = Tools::clip((double)atom_getfloat(av + i), 0., 1.);
                }
                
            }
            else
            {
                for (int i = 0; i < ac && i < x->f_number_of_microphones; i++)
                {
                    x->f_microphonesValues[i] = atom_getfloat(av + i);
                }
            }
        }
    } 
    x->f_recomposer->processFixe(x->f_microphonesValues, x->f_harmonicsValues);
    x->f_viewer->processContribAndRep(x->f_harmonicsValues);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("microphones_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
    return 0;
}

t_max_err hoa_space_channels_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv)
{
    if (argc && argv)
    {
        if(atom_gettype(argv) == A_LONG)
        {
            if(atom_getlong(argv) != x->f_number_of_microphones)
            {
				long order;
                delete x->f_viewer;
                delete x->f_recomposer;
                
                x->f_number_of_microphones  = Tools::clip(long(atom_getlong(argv)), (long)3, (long)MAX_CHANNELS);
				
                if(x->f_number_of_microphones % 2 == 0)
                    order = (x->f_number_of_microphones - 2) / 2;
                else
                    order = (x->f_number_of_microphones - 1) / 2;
                
                x->f_viewer         = new AmbisonicsViewer(order);
                x->f_recomposer		= new AmbisonicRecomposer(order, x->f_number_of_microphones, Hoa_Fixe);
                
                jbox_invalidate_layer((t_object*)x, NULL, gensym("background_layer"));
                jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
                jbox_invalidate_layer((t_object *)x, NULL, gensym("microphones_layer"));
            }
        }
    }
	return 0;
}

void hoa_space_compute(t_hoa_space *x)
{
    x->f_recomposer->processFixe(x->f_microphonesValues, x->f_harmonicsValues);
    x->f_viewer->processContribAndRep(x->f_harmonicsValues);
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("microphones_layer"));
    jbox_redraw((t_jbox *)x);
    hoa_space_output(x);
}

void hoa_space_output(t_hoa_space *x)
{
    for(int i = 0; i < x->f_number_of_microphones; i++)
        atom_setfloat(x->f_tempory_values+i, x->f_microphonesValues[i]);
    
    outlet_list(x->f_out, 0L, x->f_number_of_microphones, x->f_tempory_values);
}







