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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

#define CORNERSIZE 8
#define BORDERTHICK 2

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "ext_path.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "ext_parameter.h"
}

#include "../CicmLibrary/CicmTools.h"
#include "BoidsManager.h"

#define DEF_REFRESH_TIME 20

typedef struct  _hoaboids
{
	t_jbox          j_box;
	t_rect          rect;
	t_jfont*        jfont;
    void*           f_clock;
    
    t_atom_long f_output_mode;
	void*		f_out_sources;
    void*		f_out_groups;
    void*		f_out_infos;
    
    BoidsManager*  f_boids_manager;
    
    t_pt        f_cursor_position;
    
    t_jrgba		f_colorBackground;
    t_jrgba		f_colorBackgroundInside;
    t_jrgba     f_colorBorder;
    t_jrgba     f_colorSelection;
    t_jrgba     f_colorBirds;
    t_jrgba     f_colorAttractor;
    
    // param :
    long   f_numberOfBirds;
    double f_separation;
    double f_alignment;
    double f_coherence;
    double f_inertia;
    double f_friction;
    double f_septhresh;
    double f_maxvel;
    double f_gravity;
    double f_noise;
    double f_gravpoint[2];
    
    double f_refreshInterval;
    
    double      f_size_source;
	double		f_zoom_factor;

} t_hoaboids;

t_class *hoaboids_class;

// general methods
void *hoaboids_new(t_symbol *s, int argc, t_atom *argv);
void hoaboids_free(t_hoaboids *x);
void hoaboids_getdrawparams(t_hoaboids *x, t_object *patcherview, t_jboxdrawparams *params);
void hoaboids_assist(t_hoaboids *x, void *b, long m, long a, char *s);
t_max_err hoaboids_notify(t_hoaboids *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

// attr setters :
t_max_err hoaboids_setAttr_gravpoint(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_nbirds(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_zoom(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_separation(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_alignment(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_coherence(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_inertia(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_friction(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_septhresh(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_maxvel(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_gravity(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_agitation(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
void hoaboids_setGravityPoint(t_hoaboids *x, double gx, double gy);

void hoaboids_tick(t_hoaboids *x);

void hoaboids_start(t_hoaboids *x);
void hoaboids_stop(t_hoaboids *x);
void hoaboids_float(t_hoaboids *x, double v);
void hoaboids_int(t_hoaboids *x, long v);

void hoaboids_bang(t_hoaboids *x);
void hoaboids_infos(t_hoaboids *x);

/* Paint Methods */
void hoaboids_paint(t_hoaboids *x, t_object *view);
void draw_background(t_hoaboids *x, t_object *view, t_rect *rect);
void draw_boids(t_hoaboids *x,  t_object *view, t_rect *rect);
void draw_attractor(t_hoaboids *x,  t_object *view, t_rect *rect);

void hoaboids_mousedown(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaboids_mousedrag(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaboids_mouseup(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaboids_mouseenter(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaboids_mousemove(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaboids_mouseleave(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaboids_mousewheel(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc);
long hoaboids_key(t_hoaboids *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);

int C74_EXPORT main()
{
	t_class *c;
    
	c = class_new("hoa.boids", (method)hoaboids_new, (method)hoaboids_free, (short)sizeof(t_hoaboids), 0L, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method) hoaboids_assist,           "assist",		A_CANT,	0);
	class_addmethod(c, (method) hoaboids_paint,            "paint",         A_CANT,	0);
	class_addmethod(c, (method) hoaboids_getdrawparams,    "getdrawparams", A_CANT, 0);
	class_addmethod(c, (method) hoaboids_notify,           "notify",		A_CANT, 0);
    
    class_addmethod(c, (method) hoaboids_start,            "start",         0);
    class_addmethod(c, (method) hoaboids_stop,             "stop",          0);
    class_addmethod(c, (method) hoaboids_int,              "int",			A_LONG, 0);
    class_addmethod(c, (method) hoaboids_float,            "float",			A_FLOAT, 0);
    class_addmethod(c, (method) hoaboids_bang,             "bang",			A_CANT, 0);
    class_addmethod(c, (method) hoaboids_infos,            "getinfo",		0);
    
    class_addmethod(c, (method) hoaboids_mousedown,        "mousedown",     A_CANT, 0);
    class_addmethod(c, (method) hoaboids_mousedrag,        "mousedrag",     A_CANT, 0);
    class_addmethod(c, (method) hoaboids_mouseup,          "mouseup",       A_CANT, 0);
    class_addmethod(c, (method) hoaboids_mouseenter,       "mouseenter",    A_CANT, 0);
    class_addmethod(c, (method) hoaboids_mousemove,        "mousemove",     A_CANT, 0);
    class_addmethod(c, (method) hoaboids_mouseleave,       "mouseleave",    A_CANT, 0);
    class_addmethod(c, (method) hoaboids_mousewheel,       "mousewheel",	A_CANT, 0);
    class_addmethod(c, (method) hoaboids_key,              "key",           A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 300");
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
    
    /* Colors */
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_hoaboids, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Outside Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.9 0.9 0.9 1.");
    
    CLASS_ATTR_RGBA				(c, "bgcolor2", 0, t_hoaboids, f_colorBackgroundInside);
	CLASS_ATTR_CATEGORY			(c, "bgcolor2", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor2", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor2", 0, "Background Inside Color");
	CLASS_ATTR_ORDER			(c, "bgcolor2", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor2", 0, "0.75 0.75 0.75 1.");
    
    CLASS_ATTR_RGBA				(c, "bdcolor", 0, t_hoaboids, f_colorBorder);
	CLASS_ATTR_CATEGORY			(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bdcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bdcolor", 0, "0.5 0.5 0.5 1.");
    
    CLASS_ATTR_RGBA				(c, "birdscolor", 0, t_hoaboids, f_colorBirds);
	CLASS_ATTR_CATEGORY			(c, "birdscolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "birdscolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "birdscolor", 0, "Birds Color");
	CLASS_ATTR_ORDER			(c, "birdscolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "birdscolor", 0, "0.2 0.2 0.2 0.9");
    
    CLASS_ATTR_RGBA				(c, "attractorcolor", 0, t_hoaboids, f_colorAttractor);
	CLASS_ATTR_CATEGORY			(c, "attractorcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "attractorcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "attractorcolor", 0, "Attractor Color");
	CLASS_ATTR_ORDER			(c, "attractorcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "attractorcolor", 0, "0.8 0.5 0.5 0.9");
	
    /* Behavior */
	CLASS_ATTR_LONG				(c,"outputmode", 0, t_hoaboids, f_output_mode);
	CLASS_ATTR_LABEL			(c,"outputmode", 0, "Output Mode");
	CLASS_ATTR_CATEGORY			(c,"outputmode", 0, "Behavior");
	CLASS_ATTR_ENUMINDEX		(c,"outputmode", 0, "Polar Cartesian");
	CLASS_ATTR_DEFAULT          (c,"outputmode", 0,  "0");
    CLASS_ATTR_SAVE             (c,"outputmode", 1);
    CLASS_ATTR_ORDER			(c,"outputmode", 0, "1");
    
	CLASS_ATTR_DOUBLE			(c,"zoom", 0, t_hoaboids, f_zoom_factor);
    CLASS_ATTR_ACCESSORS		(c,"zoom", NULL, hoaboids_setAttr_zoom);
	CLASS_ATTR_LABEL			(c,"zoom", 0,   "Zoom");
	CLASS_ATTR_CATEGORY			(c,"zoom", 0,   "Behavior");
	CLASS_ATTR_DEFAULT          (c,"zoom", 0,   "0.35");
    CLASS_ATTR_ORDER			(c,"zoom", 0,   "2");
    CLASS_ATTR_SAVE             (c,"zoom", 1);
    
    /* hoa.boids */
    CLASS_STICKY_CATEGORY(c, 0, "hoa.boids");
    CLASS_ATTR_DOUBLE_ARRAY     (c,"gravpoint", 0, t_hoaboids, f_gravpoint, 2);
    CLASS_ATTR_ACCESSORS		(c,"gravpoint", NULL, hoaboids_setAttr_gravpoint);
	CLASS_ATTR_LABEL			(c,"gravpoint", 0,   "Gravity Point");
	CLASS_ATTR_DEFAULT          (c,"gravpoint", 0,   "0. 0.");
    CLASS_ATTR_ORDER			(c,"gravpoint", 0,   "1");
    CLASS_ATTR_SAVE             (c,"gravpoint", 1);
    
    CLASS_ATTR_LONG             (c,"nbirds", 0, t_hoaboids, f_numberOfBirds);
    CLASS_ATTR_ACCESSORS		(c,"nbirds", NULL, hoaboids_setAttr_nbirds);
	CLASS_ATTR_LABEL			(c,"nbirds", 0,   "Number of Birds");
	CLASS_ATTR_DEFAULT          (c,"nbirds", 0,   "4");
    CLASS_ATTR_ORDER			(c,"nbirds", 0,   "1");
    CLASS_ATTR_SAVE             (c,"nbirds", 1);
    
    CLASS_ATTR_DOUBLE			(c,"separation", 0, t_hoaboids, f_separation);
    CLASS_ATTR_ACCESSORS		(c,"separation", NULL, hoaboids_setAttr_separation);
	CLASS_ATTR_LABEL			(c,"separation", 0,   "Separation");
	CLASS_ATTR_DEFAULT          (c,"separation", 0,   "0.03");
    CLASS_ATTR_ORDER			(c,"separation", 0,   "1");
    CLASS_ATTR_SAVE             (c,"separation", 1);
    
    CLASS_ATTR_DOUBLE			(c,"alignment", 0, t_hoaboids, f_alignment);
    CLASS_ATTR_ACCESSORS		(c,"alignment", NULL, hoaboids_setAttr_alignment);
	CLASS_ATTR_LABEL			(c,"alignment", 0,   "Alignment");
	CLASS_ATTR_DEFAULT          (c,"alignment", 0,   "0.05");
    CLASS_ATTR_ORDER			(c,"alignment", 0,   "2");
    CLASS_ATTR_SAVE             (c,"alignment", 1);
    
    CLASS_ATTR_DOUBLE			(c,"coherence", 0, t_hoaboids, f_coherence);
    CLASS_ATTR_ACCESSORS		(c,"coherence", NULL, hoaboids_setAttr_coherence);
	CLASS_ATTR_LABEL			(c,"coherence", 0,   "Coherence");
	CLASS_ATTR_DEFAULT          (c,"coherence", 0,   "0.02");
    CLASS_ATTR_ORDER			(c,"coherence", 0,   "3");
    CLASS_ATTR_SAVE             (c,"coherence", 1);
    
    CLASS_ATTR_DOUBLE			(c,"inertia", 0, t_hoaboids, f_inertia);
    CLASS_ATTR_ACCESSORS		(c,"inertia", NULL, hoaboids_setAttr_inertia);
	CLASS_ATTR_LABEL			(c,"inertia", 0,   "Inertia");
	CLASS_ATTR_DEFAULT          (c,"inertia", 0,   "0.5");
    CLASS_ATTR_ORDER			(c,"inertia", 0,   "4");
    CLASS_ATTR_SAVE             (c,"inertia", 1);
    
    CLASS_ATTR_DOUBLE			(c,"friction", 0, t_hoaboids, f_friction);
    CLASS_ATTR_ACCESSORS		(c,"friction", NULL, hoaboids_setAttr_friction);
	CLASS_ATTR_LABEL			(c,"friction", 0,   "Friction");
	CLASS_ATTR_DEFAULT          (c,"friction", 0,   "0.5");
    CLASS_ATTR_ORDER			(c,"friction", 0,   "5");
    CLASS_ATTR_SAVE             (c,"friction", 1);
    
    CLASS_ATTR_DOUBLE			(c,"septhresh", 0, t_hoaboids, f_septhresh);
    CLASS_ATTR_ACCESSORS		(c,"septhresh", NULL, hoaboids_setAttr_septhresh);
	CLASS_ATTR_LABEL			(c,"septhresh", 0,   "SepThresh");
	CLASS_ATTR_DEFAULT          (c,"septhresh", 0,   "0.1");
    CLASS_ATTR_ORDER			(c,"septhresh", 0,   "6");
    CLASS_ATTR_SAVE             (c,"septhresh", 1);
    
    CLASS_ATTR_DOUBLE			(c,"maxvel", 0, t_hoaboids, f_maxvel);
    CLASS_ATTR_ACCESSORS		(c,"maxvel", NULL, hoaboids_setAttr_maxvel);
	CLASS_ATTR_LABEL			(c,"maxvel", 0,   "Max Velocity");
	CLASS_ATTR_DEFAULT          (c,"maxvel", 0,   "0.05");
    CLASS_ATTR_ORDER			(c,"maxvel", 0,   "7");
    CLASS_ATTR_SAVE             (c,"maxvel", 1);
    
    CLASS_ATTR_DOUBLE			(c,"gravity", 0, t_hoaboids, f_gravity);
    CLASS_ATTR_ACCESSORS		(c,"gravity", NULL, hoaboids_setAttr_gravity);
	CLASS_ATTR_LABEL			(c,"gravity", 0,   "Gravity");
	CLASS_ATTR_DEFAULT          (c,"gravity", 0,   "0.03");
    CLASS_ATTR_ORDER			(c,"gravity", 0,   "8");
    CLASS_ATTR_SAVE             (c,"gravity", 1);
    
    CLASS_ATTR_DOUBLE			(c,"agitation", 0, t_hoaboids, f_noise);
    CLASS_ATTR_ACCESSORS		(c,"agitation", NULL, hoaboids_setAttr_agitation);
	CLASS_ATTR_LABEL			(c,"agitation", 0,   "Agitation");
	CLASS_ATTR_DEFAULT          (c,"agitation", 0,   "0.1");
    CLASS_ATTR_ORDER			(c,"agitation", 0,   "9");
    CLASS_ATTR_SAVE             (c,"agitation", 1);
    CLASS_STICKY_CATEGORY_CLEAR(c);
    
	class_register(CLASS_BOX, c);
	hoaboids_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *hoaboids_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoaboids *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_hoaboids *)object_alloc(hoaboids_class);
	flags = 0 
	| JBOX_DRAWFIRSTIN 
	| JBOX_DRAWINLAST
	| JBOX_TRANSPARENT
	| JBOX_DRAWBACKGROUND
	| JBOX_GROWY
	| JBOX_HILITE
	;
	jbox_new(&x->j_box, flags, argc, argv);
	x->f_boids_manager = new BoidsManager();
    
    x->j_box.b_firstin = (t_object*) x;
    
    x->f_out_infos      = listout(x);
    x->f_out_groups     = listout(x);
	x->f_out_sources    = listout(x);
    
    x->f_refreshInterval = DEF_REFRESH_TIME;
	
    x->f_clock = clock_new(x,(method)hoaboids_tick);
    //clock_set(x->f_clock, x->f_refreshInterval);
	x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    
	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);
	return (x);
}

void hoaboids_free(t_hoaboids *x)
{
	jbox_free(&x->j_box);
    jfont_destroy(x->jfont);
    freeobject((t_object *)x->f_clock);
    delete x->f_boids_manager;
}

void hoaboids_assist(t_hoaboids *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(Anything) Behavior and appearance");
	else
    {
        if(a == 0)
            sprintf(s,"(List) Sources coordinates");
        if(a == 1)
            sprintf(s,"(List) Groups coordinates");
        if(a == 2)
            sprintf(s,"(List) Infos");
    }
}

void hoaboids_getdrawparams(t_hoaboids *x, t_object *patcherview, t_jboxdrawparams *params)
{
    params->d_boxfillcolor = x->f_colorBackground;
    params->d_bordercolor =  x->f_colorBorder;
	params->d_borderthickness = 1;
	params->d_cornersize = CORNERSIZE;
}

void hoaboids_tick(t_hoaboids *x)
{
    x->f_boids_manager->update();
    hoaboids_bang(x);
    clock_fdelay(x->f_clock, x->f_refreshInterval);
}

void hoaboids_start(t_hoaboids *x)
{
    hoaboids_tick(x);
}

void hoaboids_stop(t_hoaboids *x)
{
    clock_unset(x->f_clock);
}

void hoaboids_float(t_hoaboids *x, double v)
{
    hoaboids_int(x, long(v));
}

void hoaboids_int(t_hoaboids *x, long v)
{
    (v == 0) ? hoaboids_stop(x) : hoaboids_start(x);
}


t_max_err hoaboids_setAttr_zoom(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
        x->f_zoom_factor = Tools::clip(float(atom_getfloat(argv)), float(MIN_ZOOM), float(MAX_ZOOM));
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("birds_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_gravpoint(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 2 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG) && (atom_gettype(argv+1) == A_FLOAT || atom_gettype(argv+1) == A_LONG))
    {
        double gx, gy;
        gx = Tools::clip(double(atom_getfloat(argv)), double(-10), double(10));
        gy = Tools::clip(double(atom_getfloat(argv+1)), double(-10), double(10));
        hoaboids_setGravityPoint(x, gx, gy);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_nbirds(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_numberOfBirds = Tools::clip(long(atom_getlong(argv)), long(0), long(100));
        x->f_boids_manager->setNumberOfBoids(x->f_numberOfBirds);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_separation(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_separation = Tools::clip(double(atom_getfloat(argv)), double(0), double(10));
        x->f_boids_manager->setSeparation(x->f_separation);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_alignment(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_alignment = Tools::clip(double(atom_getfloat(argv)), double(0), double(1));
        x->f_boids_manager->setAlignment(x->f_alignment);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_coherence(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_coherence = Tools::clip(double(atom_getfloat(argv)), double(0), double(1));
        x->f_boids_manager->setCoherence(x->f_coherence);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_inertia(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_inertia = Tools::clip(double(atom_getfloat(argv)), double(0), double(1));
        x->f_boids_manager->setInertia(x->f_inertia);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_friction(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_friction = Tools::clip(double(atom_getfloat(argv)), double(0), double(1));
        x->f_boids_manager->setFriction(x->f_friction);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_septhresh(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_septhresh = Tools::clip(double(atom_getfloat(argv)), double(0), double(1));
        x->f_boids_manager->setSepThresh(x->f_septhresh);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_maxvel(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_maxvel = Tools::clip(double(atom_getfloat(argv)), double(0), double(1));
        x->f_boids_manager->setMaxVel(x->f_maxvel);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_gravity(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_gravity = Tools::clip(double(atom_getfloat(argv)), double(-1.), double(1.));
        x->f_boids_manager->setGravity(x->f_gravity);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_agitation(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_noise = Tools::clip(double(atom_getfloat(argv)), double(0.), double(1.));
        x->f_boids_manager->setNoise(x->f_noise);
    }
    return MAX_ERR_NONE;
}

void hoaboids_setGravityPoint(t_hoaboids *x, double gx, double gy)
{
    //x->f_gravpoint[0] = gx/x->f_zoom_factor;
    //x->f_gravpoint[1] = gy/x->f_zoom_factor;
    x->f_gravpoint[0] = gx;
    x->f_gravpoint[1] = gy;
    x->f_boids_manager->setGravPoint(x->f_gravpoint[0], x->f_gravpoint[1]);
}


t_max_err hoaboids_notify(t_hoaboids *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
    {
        name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
        if(name == gensym("bgcolor") || name == gensym("bgcolor2") )
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
        }
        else if(name == gensym("fontname") || name == gensym("fontface") || name == gensym("fontsize"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("birds_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
        }
        else if(name == gensym("zoom"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("birds_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
        }
        jbox_redraw((t_jbox *)x);
    }
    
    
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

/**********************************************************/
/*                          Sortie                        */
/**********************************************************/

void hoaboids_bang(t_hoaboids *x)
{
    t_atom av[4];
    double birdCoord[2];
    //x->f_boids_manager->update();
    
    for (int i=0; i < x->f_boids_manager->getNumberOfBoids(); i++)
    {
        x->f_boids_manager->getBirdCoord(i, birdCoord);
        atom_setlong(av, i);
        atom_setsym(av+1, gensym("cartesian"));
        atom_setfloat(av+2, birdCoord[0]);
        atom_setfloat(av+3, birdCoord[1]);
        outlet_list(x->f_out_sources, 0L, 4, av);
    }
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("birds_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoaboids_infos(t_hoaboids *x)
{
    ;
}

/**********************************************************/
/*                          Paint                        */
/**********************************************************/

void hoaboids_paint(t_hoaboids *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	x->rect = rect;
	draw_background(x, view, &rect);
    draw_attractor(x, view, &rect);
    draw_boids(x, view, &rect);
}

void draw_background(t_hoaboids *x,  t_object *view, t_rect *rect)
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

void draw_boids(t_hoaboids *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g;
    t_jmatrix transform;
    double w = rect->width;
    double h = rect->height;
    double birdCoord[2];
		
	if ((g = jbox_start_layer((t_object *)x, view, gensym("birds_layer"), rect->width, rect->height)))
    {
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
		jgraphics_set_matrix(g, &transform);
        
        //jgraphics_set_line_width(g, 1);
        
        jgraphics_set_source_jrgba(g, &x->f_colorBirds);
        
        for (int i=0; i < x->f_boids_manager->getNumberOfBoids(); i++)
        {
            x->f_boids_manager->getBirdCoord(i, birdCoord);
            //post("%i x = %f y = %f", i, birdCoord[0], birdCoord[1]);
            birdCoord[0] *= (w*0.5) * x->f_zoom_factor;
            birdCoord[1] *= (h*0.5) * x->f_zoom_factor;
            jgraphics_arc(g, birdCoord[0], birdCoord[1], 3, 0, CICM_2PI);
            jgraphics_fill(g);
        }
        
		jbox_end_layer((t_object*)x, view, gensym("birds_layer"));
    }
	jbox_paint_layer((t_object *)x, view, gensym("birds_layer"), 0., 0.);
}


void draw_attractor(t_hoaboids *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g = NULL;
    t_jmatrix transform;
    double w = rect->width;
    double h = rect->height;
    
    //double attPosX = x->f_cursor_position.x * ( (w*0.5) * x->f_zoom_factor);
    //double attPosY = x->f_cursor_position.y * ( (h*0.5) * x->f_zoom_factor);
    
    double attPosX = x->f_gravpoint[0] * ( (w*0.5) * x->f_zoom_factor);
    double attPosY = x->f_gravpoint[1] * ( (h*0.5) * x->f_zoom_factor);
		
	if ((g = jbox_start_layer((t_object *)x, view, gensym("attractor_layer"), rect->width, rect->height)))
    {
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
		jgraphics_set_matrix(g, &transform);
        
        jgraphics_set_line_width(g, 1);
        
        jgraphics_arc(g, attPosX, attPosY, 5, 0, CICM_2PI);
        //jgraphics_arc(g, x->f_cursor_position.x, x->f_cursor_position.y, 5, 0, CICM_2PI);
        
        jgraphics_set_source_jrgba(g, &x->f_colorAttractor);
        jgraphics_fill(g);
        
		jbox_end_layer((t_object*)x, view, gensym("attractor_layer"));
    }
	jbox_paint_layer((t_object *)x, view, gensym("attractor_layer"), 0., 0.);
}

/**********************************************************/
/*                   Souris et clavier                    */
/**********************************************************/

void hoaboids_mousedown(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
    hoaboids_setGravityPoint(x, cursor.x, cursor.y);
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
    jbox_redraw((t_jbox *)x);
    
    /*
    hoaboids_mousedrag(x, patcherview, pt, modifiers);
    */
    /*
    if(x->f_source_trajectory->getRecording())
        clock_set(x->f_clock, 100);
    */
}


void hoaboids_mousedrag(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
    hoaboids_setGravityPoint(x, cursor.x, cursor.y);
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;

    jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
    jbox_redraw((t_jbox *)x);
    //hoaboids_bang(x);
}

void hoaboids_mouseup(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    /*
    if(x->f_source_trajectory)
        clock_unset(x->f_clock);
    */
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("birds_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoaboids_mousewheel(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	if (modifiers == eAltKey)
    {
		double newZoom = x->f_zoom_factor + y_inc / 100.;
        x->f_zoom_factor = Tools::clip(newZoom, MIN_ZOOM, MAX_ZOOM);
        object_notify(x, _sym_modified, NULL);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("birds_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
        jbox_redraw((t_jbox *)x);
	}
}

void hoaboids_mouseenter(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void hoaboids_mousemove(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    /*
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
    double ditanceSelected = (x->f_size_source / x->rect.width * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    */

    /*
    jbox_invalidate_layer((t_object *)x, NULL, gensym("birds_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
    jbox_redraw((t_jbox *)x);
    */
}

void hoaboids_mouseleave(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

long hoaboids_key(t_hoaboids *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	post("keycode : %ld , modifiers : %ld , textcharacter : %ld ", keycode, modifiers, textcharacter);
    int filter = 0;
	return filter;	// returns 1 if you want to filter it from the key object (otherwise return 0)
}