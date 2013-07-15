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

#include "../../Sources/HoaLibrary.h"


#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

#define CORNERSIZE 8
#define BORDERTHICK 2

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
    #include "ext_common.h"
	#include "jpatcher_api.h"
	#include "jgraphics.h"
	#include "jpatcher_syms.h"
	#include "ext_dictionary.h"
	#include "ext_globalsymbol.h"
    #include "commonsyms.h"
    #include "ext_parameter.h"
}

typedef struct  _galaxy
{
	t_jbox		j_box;
    PlanetarySystem*     f_galaxy;
    
	void*		f_out;
	void*		f_outInfos;
    
	long		f_mode;
	long		f_order;
	int			f_shadow;

    t_jrgba		f_colorBackground;
    t_jrgba		f_colorBackgroundInside;
    t_jrgba     f_colorBorder;
    t_jrgba     f_colorSelection;
    
	double		f_zoom_factor;

	t_rect		f_center;
	double		f_rayonGlobal;
	double		f_rayonCircle;

    t_rect		f_ellipse_start;

} t_galaxy;

t_class *galaxy_class;

void *galaxy_new(t_symbol *s, int argc, t_atom *argv);
void galaxy_free(t_galaxy *x);
void galaxy_assist(t_galaxy *x, void *b, long m, long a, char *s);
void galaxy_preset(t_galaxy *x);
t_max_err galaxy_zoom(t_galaxy *x, t_object *attr, long argc, t_atom *argv);

t_max_err galaxy_notify(t_galaxy *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void galaxy_getdrawparams(t_galaxy *x, t_object *patcherview, t_jboxdrawparams *params);
t_max_err number_of_microphones_set(t_galaxy *x, t_object *attr, long argc, t_atom *argv);
t_max_err coefficients_set(t_galaxy *x, t_object *attr, long ac, t_atom *av);

t_max_err galaxy_setvalueof(t_galaxy *x, long ac, t_atom *av);
t_max_err galaxy_getvalueof(t_galaxy *x, long *ac, t_atom **av);

/* Interaction ***************************************/
void galaxy_mouse_down(t_galaxy *x, t_object *patcherview, t_pt pt, long modifiers);
void galaxy_mouse_drag(t_galaxy *x, t_object *patcherview, t_pt pt, long modifiers);
void galaxy_mouse_enddrag(t_galaxy *x, t_object *patcherview, t_pt pt, long modifiers);
void galaxy_mouse_wheel(t_galaxy *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc);

/* Paint *********************************************/
void galaxy_paint(t_galaxy *x, t_object *view);
void draw_background(t_galaxy *x, t_object *view, t_rect *rect);
void draw_ellipse(t_galaxy *x,  t_object *view, t_rect *rect);

int C74_EXPORT main()
{
	t_class *c;
    common_symbols_init();
    
	c = class_new("hoa.galaxy", (method)galaxy_new, (method)galaxy_free, (short)sizeof(t_galaxy), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);

	class_addmethod(c, (method)galaxy_assist,          "assist",         A_CANT,	0);
	class_addmethod(c, (method)galaxy_paint,           "paint",          A_CANT,	0);
	class_addmethod(c, (method)galaxy_notify,          "notify",         A_CANT, 0);
	class_addmethod(c, (method)galaxy_getdrawparams,   "getdrawparams",  A_CANT, 0);
	class_addmethod(c, (method)galaxy_mouse_down,      "mousedown",      A_CANT, 0);
	class_addmethod(c, (method)galaxy_mouse_drag,      "mousedrag",      A_CANT, 0);
    class_addmethod(c, (method)galaxy_mouse_enddrag,   "mouseup",        A_CANT, 0);
    class_addmethod(c, (method)galaxy_mouse_wheel,     "mousewheel",     A_CANT, 0);
    
	CLASS_ATTR_DEFAULT				(c, "patching_rect", 0, "0 0 225 225");
	CLASS_ATTR_INVISIBLE			(c, "color", 0);
	CLASS_ATTR_INVISIBLE			(c, "textcolor", 0);

    /* Colors */
	CLASS_ATTR_RGBA                 (c, "bgcolor", 0, t_galaxy, f_colorBackground);
	CLASS_ATTR_CATEGORY             (c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bgcolor", 0, "Background Outside Color");
	CLASS_ATTR_ORDER                (c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bgcolor", 0, "0.9 0.9 0.9 1.");
    
    CLASS_ATTR_RGBA                 (c, "bgcolor2", 0, t_galaxy, f_colorBackgroundInside);
	CLASS_ATTR_CATEGORY             (c, "bgcolor2", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bgcolor2", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bgcolor2", 0, "Background Inside Color");
	CLASS_ATTR_ORDER                (c, "bgcolor2", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bgcolor2", 0, "0.75 0.75 0.75 1.");
    
    CLASS_ATTR_RGBA                 (c, "bdcolor", 0, t_galaxy, f_colorBorder);
	CLASS_ATTR_CATEGORY             (c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER                (c, "bdcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bdcolor", 0, "0.5 0.5 0.5 1.");
    
    CLASS_ATTR_RGBA                 (c, "selcolor", 0, t_galaxy, f_colorSelection);
	CLASS_ATTR_CATEGORY             (c, "selcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "selcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "selcolor", 0, "Selection Color");
	CLASS_ATTR_ORDER                (c, "selcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "selcolor", 0, "0.36 0.37 0.7 0.5");
    
    CLASS_ATTR_DOUBLE               (c,"zoom", 0,   t_galaxy, f_zoom_factor);
    CLASS_ATTR_ACCESSORS            (c,"zoom", NULL, galaxy_zoom);
	CLASS_ATTR_LABEL                (c,"zoom", 0,   "Zoom");
	CLASS_ATTR_CATEGORY             (c,"zoom", 0,   "Behavior");
	CLASS_ATTR_DEFAULT              (c,"zoom", 0,   "0.35");
    CLASS_ATTR_ORDER                (c,"zoom", 0,   "2");
    CLASS_ATTR_SAVE                 (c,"zoom", 1);
	
	
	class_register(CLASS_BOX, c);
	galaxy_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *galaxy_new(t_symbol *s, int argc, t_atom *argv)
{
	t_galaxy *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_galaxy *)object_alloc(galaxy_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;
    
    x->f_galaxy = new PlanetarySystem();
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.b_firstin = (t_object *)x;
    
    x->f_outInfos   = outlet_new(x, NULL);
    x->f_out        = listout(x);

	attr_dictionary_process(x, d);
	jbox_ready((t_jbox *)x);

	return (x);
}			

void galaxy_free(t_galaxy *x)
{
	jbox_free((t_jbox *)x);
    delete x->f_galaxy;

}

void galaxy_assist(t_galaxy *x, void *b, long m, long a, char *s)
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
			sprintf(s,"(int) Nuber of Virtual microphones");
	}
}

t_max_err galaxy_notify(t_galaxy *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("bgcolor") || name == gensym("borderboxcolor") || name == gensym("cicolor") || name == gensym("cicolorin") )
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
		else if(name == gensym("harmocolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
		}
		else if(name == gensym("miccolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("microphones_points_layer"));
		}
		else if(name == gensym("shadow"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
			if (x->f_shadow) object_attr_setdisabled((t_object *)x, gensym("cishadcolor"), 0);
			else object_attr_setdisabled((t_object *)x, gensym("cishadcolor"), 1);
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void galaxy_getdrawparams(t_galaxy *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = 2;
	params->d_cornersize = 12;
}

/**********************************************************/
/*                      Preset et Pattrs                  */
/**********************************************************/



/**********************************************************/
/*                      Dessin                            */
/**********************************************************/

t_max_err galaxy_zoom(t_galaxy *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
        x->f_zoom_factor = Tools::clip(float(atom_getfloat(argv)), float(MIN_ZOOM), float(MAX_ZOOM));
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("ellipse_layer"));
  
    return MAX_ERR_NONE;
}

void galaxy_paint(t_galaxy *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	
	x->f_center.x = rect.width * .5;
	x->f_center.y = rect.height * .5;
	
	x->f_rayonGlobal = rect.width * .5;
	if(rect.width > rect.height)
		x->f_rayonGlobal = rect.height * .5;
	
	x->f_rayonCircle = x->f_rayonGlobal / 6;
	
	draw_background(x, view, &rect);
    draw_ellipse(x, view, &rect);
}

void draw_background(t_galaxy *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g, *g2, *g3;
    t_jsurface *s1, *s2;
    t_jrgba black, white;
    double w = rect->width;
    
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
    black = white = x->f_colorBackgroundInside;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
    
	g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), w, rect->height);
	
	if (g)
    {
        s1 = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, int(w), int(w));
        g2 = jgraphics_create(s1);
        
        s2 = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, int(w), int(w));
        g3 = jgraphics_create(s2);
        
        jgraphics_set_source_jrgba(g3, &x->f_colorBackgroundInside);
        jgraphics_set_line_width(g3, 1);
        jgraphics_arc(g3, w / 2., w / 2., (w / 2.) * (1./MIN_ZOOM * x->f_zoom_factor),  0., JGRAPHICS_2PI);
        jgraphics_fill(g3);
        
        double ecart = x->f_zoom_factor * w / 2.;
        if(ecart < 10 && ecart >= 5) ecart *= 4;
        else if(ecart < 5 && ecart > 2.5) ecart *= 8;
        else if(ecart < 2.5) ecart *= 16;
        ecart = int(ecart);
        
		for(double i = 0; i < w / 2.; i += ecart)
        {
            jgraphics_set_line_width(g3, 1);
            jgraphics_set_source_jrgba(g3, &white);
            jgraphics_move_to(g3, 0., w / 2. - i);
            jgraphics_line_to(g3, w, w / 2. - i);
            jgraphics_move_to(g3, 0., w / 2. + i);
            jgraphics_line_to(g3, w, w / 2. + i);
            jgraphics_move_to(g3, w / 2. - i, 0.);
            jgraphics_line_to(g3, w / 2. - i, w);
            jgraphics_move_to(g3, w / 2. + i, 0.);
            jgraphics_line_to(g3, w / 2. + i, w);
            jgraphics_set_line_width(g3, 1);
            jgraphics_scale(g3, 0.25, 0.25); // tricks to draw a 0.25 line width
            jgraphics_stroke(g3);
            jgraphics_scale(g3, 4, 4);
            
            jgraphics_set_line_width(g3, 1);
            jgraphics_set_source_jrgba(g3, &black);
            jgraphics_move_to(g3, 0. - 0.5, w / 2. - i - 0.5);
            jgraphics_line_to(g3, w - 0.5, w / 2. - i - 0.5);
            jgraphics_move_to(g3, 0. - 0.5, w / 2. + i - 0.5);
            jgraphics_line_to(g3, w - 0.5, w / 2. + i - 0.5);
            jgraphics_move_to(g3, w / 2. - i - 0.5, 0. - 0.5);
            jgraphics_line_to(g3, w / 2. - i - 0.5, w - 0.5);
            jgraphics_move_to(g3, w / 2. + i - 0.5, 0. - 0.5);
            jgraphics_line_to(g3, w / 2. + i - 0.5, w - 0.5);
            jgraphics_set_line_width(g3, 2);
            jgraphics_scale(g3, 0.25, 0.25);
            jgraphics_stroke(g3);
            jgraphics_scale(g3, 4, 4);
        }
        
        /* Circles */
        double radius = x->f_zoom_factor * w / 10.;
        for(int i = 5; i > 0; i--)
        {
            jgraphics_set_line_width(g3, 1);
            jgraphics_set_source_jrgba(g3, &white);
            jgraphics_arc(g3, w / 2, w / 2, (double)i * radius - 1,  0., JGRAPHICS_2PI);
            jgraphics_scale(g3, 0.5, 0.5); // tricks to draw a 0.5 line width
            jgraphics_stroke(g3);
            jgraphics_scale(g3, 2, 2);
            
            jgraphics_set_line_width(g3, 2);
            jgraphics_set_source_jrgba(g3, &black);
            jgraphics_arc(g3, w / 2 - 0.5, w / 2 - 0.5, (double)i * radius - 1,  0., JGRAPHICS_2PI);
            jgraphics_scale(g3, 0.5, 0.5);
            jgraphics_stroke(g3);
            jgraphics_scale(g3, 2, 2);
        }
        
        /* clip jgraphics_3 to circle */
        jgraphics_destroy(g3);
        jgraphics_set_source_surface(g2, s2, 0, 0);
        jgraphics_surface_destroy(s2);
        jgraphics_arc(g2, w / 2., w / 2., (w / 2.) * (1./MIN_ZOOM * x->f_zoom_factor) - (BORDERTHICK*2),  0., CICM_2PI);
        jgraphics_fill(g2);
        
        /* clip jgraphics_2 to rounded rect */
        jgraphics_destroy(g2);
        jgraphics_set_source_surface(g, s1, 0, 0);
        jgraphics_surface_destroy(s1);
        jgraphics_rectangle_rounded(g, 0, 0, w, rect->height, CORNERSIZE, CORNERSIZE);
        jgraphics_fill(g);
        
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_ellipse(t_galaxy *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g;
    t_jrgba black;
    double w = rect->width;
    

    black.red = 0.;
    black.green = 0.;
    black.blue = 0.;
    black.alpha = 1.;
    
	g = jbox_start_layer((t_object *)x, view, gensym("ellipse_layer"), w, rect->height);
	
	if (g)
    {
        jgraphics_set_line_width(g, 1);
        jgraphics_set_source_jrgba(g, &black);
        jgraphics_ellipse(g, x->f_ellipse_start.x, x->f_ellipse_start.y, x->f_ellipse_start.width, x->f_ellipse_start.height);
        jgraphics_stroke(g);
        
		jbox_end_layer((t_object*)x, view, gensym("ellipse_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("ellipse_layer"), 0., 0.);
}

/**********************************************************/
/*                      Souris                            */
/**********************************************************/

void galaxy_mouse_down(t_galaxy *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->f_ellipse_start.width    = 0.;
    x->f_ellipse_start.height   = 0.;
    x->f_ellipse_start.x = pt.x;
    x->f_ellipse_start.y = pt.y;
   
    jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("ellipse_layer"));
    jbox_redraw((t_jbox *)x);
}

void galaxy_mouse_drag(t_galaxy *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->f_ellipse_start.width    = pt.x - x->f_ellipse_start.x;
    x->f_ellipse_start.height   = pt.y - x->f_ellipse_start.y;
    jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("ellipse_layer"));
    jbox_redraw((t_jbox *)x);
}

void galaxy_mouse_enddrag(t_galaxy *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void galaxy_mouse_wheel(t_galaxy *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	if (modifiers == eAltKey)
    {
        x->f_zoom_factor = Tools::clip(x->f_zoom_factor + y_inc / 100., MIN_ZOOM, MAX_ZOOM);
        object_notify(x, _sym_modified, NULL);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("ellipse_layer"));
        jbox_redraw((t_jbox *)x);
	}
}




