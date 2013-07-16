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

#include "../../Sources/HoaBoids/BoidsManager.h"

#define DEF_REFRESH_TIME 20

typedef struct  _hoaboids
{
	t_jbox          j_box;
	t_rect          rect;
    void*           f_clock;
    
    t_atom_long f_output_mode;
	void*		f_out_sources;
    void*		f_out_infos;
    
    BoidsManager*  f_boids_manager;
    
    t_pt        f_cursor_position;
    
    t_jrgba		f_colorBackground;
    t_jrgba		f_colorBackgroundInside;
    t_jrgba     f_colorBorder;
    t_jrgba     f_colorSelection;
    t_jrgba     f_colorBoids;
    t_jrgba     f_colorAttractor;
    t_jrgba     f_colorFlyrect;
    
    // param :
    long   f_numberOfBoids;
    long   f_neighbors;
	double f_minspeed;
	double f_maxspeed;
	double f_center;
	double f_attract;
	double f_match;
	double f_avoid;
	double f_wall; //f_repel;
	double f_edgedist;
	double f_speed;
	double f_inertia;
	double f_accel;
	double f_prefdist;
	double f_flyrect[4];
	double f_attractpt[2];
    
    double f_refreshInterval;
    
    double      f_size_source;
	double		f_zoom_factor;
    
    // interaction :
    int cmdKeyPressed;

} t_hoaboids;

t_class *hoaboids_class;

// general methods
void *hoaboids_new(t_symbol *s, int argc, t_atom *argv);
void hoaboids_free(t_hoaboids *x);
void hoaboids_getdrawparams(t_hoaboids *x, t_object *patcherview, t_jboxdrawparams *params);
void hoaboids_assist(t_hoaboids *x, void *b, long m, long a, char *s);
t_max_err hoaboids_notify(t_hoaboids *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

// preset - pattr
void hoaboids_preset(t_hoaboids *x);
t_max_err hoaboids_setvalueof(t_hoaboids *x, long ac, t_atom *av);
t_max_err hoaboids_getvalueof(t_hoaboids *x, long *ac, t_atom **av);

// attr setters :
t_max_err hoaboids_setAttr_attractpoint(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_nBoids(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_zoom(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_flyrect(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_neighbors(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_mode(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_minspeed(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_maxspeed(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_center(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_attract(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_match(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_avoid(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_wall(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_edgedist(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_speed(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_inertia(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_accel(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaboids_setAttr_prefdist(t_hoaboids *x, t_object *attr, long argc, t_atom *argv);

void hoaboids_setGravityPoint(t_hoaboids *x, double gx, double gy);

void boid_set_pos(t_hoaboids *x, t_symbol *s, long argc, t_atom *argv);
void boid_set_dir(t_hoaboids *x, t_symbol *s, long argc, t_atom *argv);
void boid_set_speed(t_hoaboids *x, t_symbol *s, long argc, t_atom *argv);
void boid_set_speedinv(t_hoaboids *x, t_symbol *s, long argc, t_atom *argv);

void hoaboids_tick(t_hoaboids *x);

void hoaboids_reset(t_hoaboids *x);
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
void draw_flyrect(t_hoaboids *x,  t_object *view, t_rect *rect);

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
    
    class_addmethod(c, (method) hoaboids_preset,           "preset",                  0);
    class_addmethod(c, (method) hoaboids_getvalueof,       "getvalueof",    A_CANT,   0);
	class_addmethod(c, (method) hoaboids_setvalueof,       "setvalueof",    A_CANT,   0);
    
    class_addmethod(c, (method) hoaboids_reset,            "reset",		A_NOTHING, 0);
    class_addmethod(c, (method) boid_set_pos,              "set_pos",		A_GIMME, 0);
    class_addmethod(c, (method) boid_set_dir,              "set_dir",		A_GIMME, 0);
    class_addmethod(c, (method) boid_set_speed,            "set_speed",		A_GIMME, 0);
    class_addmethod(c, (method) boid_set_speedinv,         "set_speedinv",	A_GIMME, 0);
    
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
    
    CLASS_ATTR_RGBA				(c, "boidscolor", 0, t_hoaboids, f_colorBoids);
	CLASS_ATTR_CATEGORY			(c, "boidscolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "boidscolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "boidscolor", 0, "Boids Color");
	CLASS_ATTR_ORDER			(c, "boidscolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "boidscolor", 0, "0.2 0.2 0.2 0.9");
    
    CLASS_ATTR_RGBA				(c, "attractorcolor", 0, t_hoaboids, f_colorAttractor);
	CLASS_ATTR_CATEGORY			(c, "attractorcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "attractorcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "attractorcolor", 0, "Attractor Color");
	CLASS_ATTR_ORDER			(c, "attractorcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "attractorcolor", 0, "0.8 0.5 0.5 0.9");
    
    CLASS_ATTR_RGBA				(c, "flyrectcolor", 0, t_hoaboids, f_colorFlyrect);
	CLASS_ATTR_CATEGORY			(c, "flyrectcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "flyrectcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "flyrectcolor", 0, "Fly Rectangle Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "flyrectcolor", 0, "0.25 0.25 0.25 0.9");
	
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
    CLASS_ATTR_DOUBLE_ARRAY     (c,"attractpoint", 0, t_hoaboids, f_attractpt, 2);
    CLASS_ATTR_ACCESSORS		(c,"attractpoint", NULL, hoaboids_setAttr_attractpoint);
	CLASS_ATTR_LABEL			(c,"attractpoint", 0,   "Attraction Point");
	CLASS_ATTR_DEFAULT          (c,"attractpoint", 0,   "0. 0.");
    CLASS_ATTR_SAVE             (c,"attractpoint", 1);
    
    CLASS_ATTR_LONG             (c,"nboids", 0, t_hoaboids, f_numberOfBoids);
    CLASS_ATTR_ACCESSORS		(c,"nboids", NULL, hoaboids_setAttr_nBoids);
	CLASS_ATTR_LABEL			(c,"nboids", 0,   "Number of Boids");
	CLASS_ATTR_DEFAULT          (c,"nboids", 0,   "4");
    CLASS_ATTR_SAVE             (c,"nboids", 1);
    
    CLASS_ATTR_DOUBLE_ARRAY     (c,"flyrect", 0, t_hoaboids, f_flyrect, 4);
    CLASS_ATTR_ACCESSORS		(c,"flyrect", NULL, hoaboids_setAttr_flyrect);
	CLASS_ATTR_LABEL			(c,"flyrect", 0,   "Flying Rectangle");
	CLASS_ATTR_DEFAULT          (c,"flyrect", 0,   "-5. 5. 5. -5");
    CLASS_ATTR_SAVE             (c,"flyrect", 1);
    
    CLASS_ATTR_LONG             (c,"neigbhors", 0, t_hoaboids, f_neighbors);
    CLASS_ATTR_ACCESSORS		(c,"neigbhors", NULL, hoaboids_setAttr_neighbors);
	CLASS_ATTR_LABEL			(c,"neigbhors", 0,   "Number Of Neighbors");
	CLASS_ATTR_DEFAULT          (c,"neigbhors", 0,   "4");
    CLASS_ATTR_SAVE             (c,"neigbhors", 1);
    
    CLASS_ATTR_DOUBLE			(c,"minspeed", 0, t_hoaboids, f_minspeed);
    CLASS_ATTR_ACCESSORS		(c,"minspeed", NULL, hoaboids_setAttr_minspeed);
	CLASS_ATTR_LABEL			(c,"minspeed", 0,   "Minimum Speed");
	CLASS_ATTR_DEFAULT_SAVE     (c,"minspeed", 0,   "0.15");
    
    CLASS_ATTR_DOUBLE			(c,"maxspeed", 0, t_hoaboids, f_maxspeed);
    CLASS_ATTR_ACCESSORS		(c,"maxspeed", NULL, hoaboids_setAttr_maxspeed);
	CLASS_ATTR_LABEL			(c,"maxspeed", 0,   "Maximum Speed");
	CLASS_ATTR_DEFAULT_SAVE     (c,"maxspeed", 0,   "0.25");
    
    CLASS_ATTR_DOUBLE			(c,"center", 0, t_hoaboids, f_center);
    CLASS_ATTR_ACCESSORS		(c,"center", NULL, hoaboids_setAttr_center);
	CLASS_ATTR_LABEL			(c,"center", 0,   "Flock Centering");
	CLASS_ATTR_DEFAULT_SAVE     (c,"center", 0,   "0.25");
    
    CLASS_ATTR_DOUBLE			(c,"attract", 0, t_hoaboids, f_attract);
    CLASS_ATTR_ACCESSORS		(c,"attract", NULL, hoaboids_setAttr_attract);
	CLASS_ATTR_LABEL			(c,"attract", 0,   "Attraction Point Seeking");
	CLASS_ATTR_DEFAULT_SAVE     (c,"attract", 0,   "0.3");
    
    CLASS_ATTR_DOUBLE			(c,"match", 0, t_hoaboids, f_match);
    CLASS_ATTR_ACCESSORS		(c,"match", NULL, hoaboids_setAttr_match);
	CLASS_ATTR_LABEL			(c,"match", 0,   "Neighbors Velocity Matching");
	CLASS_ATTR_DEFAULT_SAVE     (c,"match", 0,   "0.1");
    
    CLASS_ATTR_DOUBLE			(c,"avoid", 0, t_hoaboids, f_avoid);
    CLASS_ATTR_ACCESSORS		(c,"avoid", NULL, hoaboids_setAttr_avoid);
	CLASS_ATTR_LABEL			(c,"avoid", 0,   "Neighbors Avoidance");
	CLASS_ATTR_DEFAULT_SAVE     (c,"avoid", 0,   "0.1");
    
    /*
    CLASS_ATTR_DOUBLE			(c,"wall", 0, t_hoaboids, f_wall);
    CLASS_ATTR_ACCESSORS		(c,"wall", NULL, hoaboids_setAttr_wall);
	CLASS_ATTR_LABEL			(c,"wall", 0,   "Wall Avoidance");
	CLASS_ATTR_DEFAULT_SAVE     (c,"wall", 0,   "0.5");
    
    CLASS_ATTR_DOUBLE			(c,"edgedist", 0, t_hoaboids, f_edgedist);
    CLASS_ATTR_ACCESSORS		(c,"edgedist", NULL, hoaboids_setAttr_edgedist);
	CLASS_ATTR_LABEL			(c,"edgedist", 0,   "Vision Distance to Avoid Wall Edges");
	CLASS_ATTR_DEFAULT_SAVE     (c,"edgedist", 0,   "0.5");
    */
     
    CLASS_ATTR_DOUBLE			(c,"speed", 0, t_hoaboids, f_speed);
    CLASS_ATTR_ACCESSORS		(c,"speed", NULL, hoaboids_setAttr_speed);
	CLASS_ATTR_LABEL			(c,"speed", 0,   "Animation Speed");
	CLASS_ATTR_DEFAULT_SAVE     (c,"speed", 0,   "0.1");
    
    CLASS_ATTR_DOUBLE			(c,"inertia", 0, t_hoaboids, f_inertia);
    CLASS_ATTR_ACCESSORS		(c,"inertia", NULL, hoaboids_setAttr_inertia);
	CLASS_ATTR_LABEL			(c,"inertia", 0,   "Willingness to Change Speed & Direction");
	CLASS_ATTR_DEFAULT_SAVE     (c,"inertia", 0,   "0.2");
    
    CLASS_ATTR_DOUBLE			(c,"accel", 0, t_hoaboids, f_accel);
    CLASS_ATTR_ACCESSORS		(c,"accel", NULL, hoaboids_setAttr_accel);
	CLASS_ATTR_LABEL			(c,"accel", 0,   "Neighbor Avoidance Accelerate or Decelerate Rate");
	CLASS_ATTR_DEFAULT_SAVE     (c,"accel", 0,   "0.1");
    
    CLASS_ATTR_DOUBLE			(c,"prefdist", 0, t_hoaboids, f_prefdist);
    CLASS_ATTR_ACCESSORS		(c,"prefdist", NULL, hoaboids_setAttr_prefdist);
	CLASS_ATTR_LABEL			(c,"prefdist", 0,   "Preferred Distance from Neighbors");
	CLASS_ATTR_DEFAULT_SAVE     (c,"prefdist", 0,   "0.25");
    
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
	x->f_out_sources    = listout(x);
    
    x->f_refreshInterval = DEF_REFRESH_TIME;
	
    x->f_clock = clock_new(x,(method)hoaboids_tick);
    
	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);
	return (x);
}

void hoaboids_free(t_hoaboids *x)
{
	jbox_free(&x->j_box);
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
    params->d_boxfillcolor = x->f_colorBackgroundInside;
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

void hoaboids_reset(t_hoaboids *x)
{
    x->f_boids_manager->resetBoids();
    jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
    jbox_redraw((t_jbox *)x);
}


// --------------------- //


void hoaboids_preset(t_hoaboids *x)
{
    void* z;
    if(!(z = gensym("_preset")->s_thing))
        return;
    
    binbuf_vinsert(z, gensym("ossl")->s_name, x, object_classname(x), gensym("nboids"), x->f_numberOfBoids);
    binbuf_vinsert(z, gensym("ossff")->s_name, x, object_classname(x), gensym("attractpoint"), x->f_attractpt[0], x->f_attractpt[1]);
    binbuf_vinsert(z, gensym("ossffff")->s_name, x, object_classname(x), gensym("flyrect"),
                   x->f_flyrect[0], x->f_flyrect[1],
                   x->f_flyrect[2], x->f_flyrect[3]);
    binbuf_vinsert(z, gensym("ossl")->s_name, x, object_classname(x), gensym("neigbhors"), x->f_neighbors);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("minspeed"), x->f_minspeed);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("maxspeed"), x->f_maxspeed);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("center"), x->f_center);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("attract"), x->f_attract);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("match"), x->f_match);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("avoid"), x->f_avoid);
    //binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("wall"), x->f_wall);
    //binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("edgedist"), x->f_edgedist);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("speed"), x->f_speed);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("inertia"), x->f_inertia);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("accel"), x->f_accel);
    binbuf_vinsert(z, gensym("ossf")->s_name, x, object_classname(x), gensym("prefdist"), x->f_prefdist);
}

t_max_err hoaboids_setvalueof(t_hoaboids *x, long ac, t_atom *av)
{
    /*
    if (ac && av) {
        
        long index, i;
        for (i = index = 0; (index < x->f_numberOfMic) && (i <= ac); index++, i+=3)
        {
            x->f_mics->setAngleCartesianCoordinate(index, atom_getfloat(av+i), atom_getfloat(av+i+1));
            x->f_mics->setWiderValue(index, atom_getfloat(av+i+2));
        }
        
        jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
        jbox_redraw((t_jbox *)x);
        
        HoaRecomposerUI_output(x);
	}
	return MAX_ERR_NONE;
    */
}

// get a list of mic value : (x, y, wider)*numberOfMicrophone
t_max_err hoaboids_getvalueof(t_hoaboids *x, long *ac, t_atom **av)
{
    /*
    if (ac && av)
    {
        if (*ac && *av)
        {
            long index, i;
            for (i = index = 0; index < x->f_numberOfMic; index++, i+=3)
            {
                atom_setfloat(*av+i, x->f_mics->getAbscissa(index) );
                atom_setfloat(*av+i+1, x->f_mics->getOrdinate(index) );
                atom_setfloat(*av+i+2, x->f_mics->getWiderValue(index) );
            }
		}
        else
        {
            *ac = (x->f_numberOfMic*3);
			*av = (t_atom *)getbytes( (x->f_numberOfMic*3) * sizeof(t_atom));
            long index, i;
            for (i = index = 0; index < x->f_numberOfMic; index++, i+=3)
            {
                atom_setfloat(*av+i, x->f_mics->getAbscissa(index) );
                atom_setfloat(*av+i+1, x->f_mics->getOrdinate(index) );
                atom_setfloat(*av+i+2, x->f_mics->getWiderValue(index) );
            }
        }
    }
	return MAX_ERR_NONE;
    */
}

// --------------------- //

t_max_err hoaboids_setAttr_zoom(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
        x->f_zoom_factor = Tools::clip(float(atom_getfloat(argv)), float(MIN_ZOOM), float(MAX_ZOOM));
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("flyrect_layer"));
    jbox_redraw((t_jbox *)x);
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_attractpoint(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
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

t_max_err hoaboids_setAttr_nBoids(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_numberOfBoids = Tools::clip(long(atom_getlong(argv)), long(0), long(100));
        x->f_boids_manager->setNumberOfBoids(x->f_numberOfBoids);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
        jbox_redraw((t_jbox *)x);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_flyrect(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        for (int i = 0; i < argc; i++) {
            if (atom_gettype(argv+i) == A_FLOAT || atom_gettype(argv+i) == A_LONG)
                x->f_flyrect[i] = atom_getfloat(argv+i);
                //x->f_flyrect[i] = Tools::clip(double(atom_getfloat(argv+i)), double(-10), double(10));
        }
        x->f_boids_manager->setFlyRect(x->f_flyrect[0], x->f_flyrect[1], x->f_flyrect[2], x->f_flyrect[3]);
        
        jbox_invalidate_layer((t_object *)x, NULL, gensym("flyrect_layer"));
        jbox_redraw((t_jbox *)x);
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_neighbors(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT))
    {
        x->f_boids_manager->setNumberOfNeighbors(atom_getlong(argv));
        x->f_neighbors = x->f_boids_manager->getNumberOfNeighbors();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_minspeed(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setMinSpeed(atom_getfloat(argv));
        x->f_minspeed = x->f_boids_manager->getMinSpeed();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_maxspeed(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setMaxSpeed(atom_getfloat(argv));
        x->f_maxspeed = x->f_boids_manager->getMaxSpeed();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_center(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setCenterWeight(atom_getfloat(argv));
        x->f_center = x->f_boids_manager->getCenterWeight();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_attract(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setAttractWeight(atom_getfloat(argv));
        x->f_attract = x->f_boids_manager->getAttractWeight();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_match(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setMatchWeight(atom_getfloat(argv));
        x->f_match = x->f_boids_manager->getMatchWeight();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_avoid(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setAvoidWeight(atom_getfloat(argv));
        x->f_avoid = x->f_boids_manager->getAvoidWeight();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_wall(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setWallsWeight(atom_getfloat(argv));
        x->f_wall = x->f_boids_manager->getWallsWeight();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_edgedist(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setEdgeDistance(atom_getfloat(argv));
        x->f_edgedist = x->f_boids_manager->getEdgeDistance();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_speed(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setSpeedupFactor(atom_getfloat(argv));
        x->f_speed = x->f_boids_manager->getSpeedupFactor();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_inertia(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setInertiaFactor(atom_getfloat(argv));
        x->f_inertia = x->f_boids_manager->getInertiaFactor();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_accel(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setAccelFactor(atom_getfloat(argv));
        x->f_accel = x->f_boids_manager->getAccelFactor();
    }
    return MAX_ERR_NONE;
}

t_max_err hoaboids_setAttr_prefdist(t_hoaboids *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_boids_manager->setPrefDistance(atom_getfloat(argv));
        x->f_prefdist = x->f_boids_manager->getPrefDistance();
    }
    return MAX_ERR_NONE;
}

void hoaboids_setGravityPoint(t_hoaboids *x, double gx, double gy)
{
    x->f_attractpt[0] = gx;
    x->f_attractpt[1] = gy;
    x->f_boids_manager->setAttractPt(x->f_attractpt[0], x->f_attractpt[1]);
    
    object_attr_touch((t_object*)x, gensym("attractpoint"));
}

void boid_set_pos(t_hoaboids *x, t_symbol *s, long argc, t_atom *argv)
{
	//receives index posx posy
	
	if( argc >= 3 && argv )
    {
        for (int i=0; i < argc; i++)
            if ( !(atom_gettype(argv+i) == A_LONG) || (atom_gettype(argv+i) == A_FLOAT) )
                return;
        
        x->f_boids_manager->boid_set_pos(atom_getlong(argv), atom_getfloat(argv+1), atom_getfloat(argv+2));
	}
}

void boid_set_dir(t_hoaboids *x, t_symbol *s, long argc, t_atom *argv)
{
	//receives index dirx diry
	
	if( argc >= 3 && argv )
    {
        for (int i=0; i < argc; i++)
            if ( !(atom_gettype(argv+i) == A_LONG) || (atom_gettype(argv+i) == A_FLOAT) )
                return;
        
        x->f_boids_manager->boid_set_dir(atom_getlong(argv), atom_getfloat(argv+1), atom_getfloat(argv+2));
	}
}

void boid_set_speed(t_hoaboids *x, t_symbol *s, long argc, t_atom *argv)
{
	//receives index speed
    if( argc >= 2 && argv )
    {
        for (int i=0; i < argc; i++)
            if ( !(atom_gettype(argv+i) == A_LONG) || (atom_gettype(argv+i) == A_FLOAT) )
                return;
        
        x->f_boids_manager->boid_set_speed(atom_getlong(argv), atom_getfloat(argv+1));
	}
}

void boid_set_speedinv(t_hoaboids *x, t_symbol *s, long argc, t_atom *argv)
{
	//receives index
    if( argc && argv )
    {
        if ( !(atom_gettype(argv) == A_LONG) || (atom_gettype(argv) == A_FLOAT) )
            return;
        x->f_boids_manager->boid_set_speedinv(atom_getlong(argv));
	}
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
            jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
        }
        else if(name == gensym("zoom"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
        }
        else if (name == gensym("nboids") || name == gensym("boidscolor"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
        }
        else if(name == gensym("attractorcolor"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
        }
        else if(name == gensym("flyrectcolor"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("flyrect_layer"));
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
    double coords[2];
    
    // output Flock barycenter :
    coords[0] = x->f_boids_manager->getCenterPt_abscissa();
    coords[1] = x->f_boids_manager->getCenterPt_ordinate();
    atom_setsym(av, gensym("barycenter"));
    atom_setsym(av+1, gensym("car"));
    atom_setfloat(av+2, coords[0]);
    atom_setfloat(av+3, coords[1]);
    outlet_list(x->f_out_infos, 0L, 4, av);
    
    // output boid (cartesians) Coordinates :
    for (int i=0; i < x->f_boids_manager->getNumberOfBoids(); i++)
    {
        if(x->f_boids_manager->getBoidPosCoord(i, coords))
        {
            atom_setlong(av, i);
            atom_setsym(av+1, gensym("car"));
            atom_setfloat(av+2, coords[0]);
            atom_setfloat(av+3, coords[1]);
            outlet_list(x->f_out_sources, 0L, 4, av);
        }
    }
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
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
    draw_flyrect(x, view, &rect);
    draw_attractor(x, view, &rect);
    draw_boids(x, view, &rect);
}

void draw_background(t_hoaboids *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g;
    t_jrgba black, white;
    double w = rect->width;
    double h = rect->height;
    t_pt ctr = {w*0.5, h*0.5};
    double maxctr = Tools::max(w, h)*0.5;
    
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
    black = white = x->f_colorBackgroundInside;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
    
	g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), w, h);
	
	if (g)
    {
        /*
        jgraphics_set_source_jrgba(g, &x->f_colorBackgroundInside);
        jgraphics_set_line_width(g, 1);
        jgraphics_arc(g, ctr.x, ctr.y, maxctr * (1./MIN_ZOOM * x->f_zoom_factor),  0., JGRAPHICS_2PI);
        jgraphics_fill(g);
        */
        
        double ecart = x->f_zoom_factor * maxctr;
        if(ecart < 10 && ecart >= 5) ecart *= 4;
        else if(ecart < 5 && ecart > 2.5) ecart *= 8;
        else if(ecart < 2.5) ecart *= 16;
        ecart = int(ecart);
        
		for(double i = 0; i < maxctr; i += ecart)
        {
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_move_to(g, 0., long(ctr.y - i) + 0.5);
            jgraphics_line_to(g, w,  long(ctr.y - i) + 0.5);
            jgraphics_move_to(g, 0., long(ctr.y + i) + 0.5);
            jgraphics_line_to(g, w,  long(ctr.y + i) + 0.5);
            jgraphics_move_to(g, long(ctr.x - i) + 0.5, 0.);
            jgraphics_line_to(g, long(ctr.x - i) + 0.5, w);
            jgraphics_move_to(g, long(ctr.x + i) + 0.5, 0.);
            jgraphics_line_to(g, long(ctr.x + i) + 0.5, w);
            jgraphics_set_line_width(g, 1);
            jgraphics_scale(g, 0.5, 0.5); // tricks to draw a 0.5 line width
            jgraphics_stroke(g);
            jgraphics_scale(g, 2, 2);
            
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_move_to(g, 0. - 0.5, long(ctr.y - i) - 0.5);
            jgraphics_line_to(g, w - 0.5, long(ctr.y - i) - 0.5);
            jgraphics_move_to(g, 0. - 0.5, long(ctr.y + i) - 0.5);
            jgraphics_line_to(g, w - 0.5, long(ctr.y + i) - 0.5);
            jgraphics_move_to(g, long(ctr.x - i) - 0.5, 0. - 0.5);
            jgraphics_line_to(g, long(ctr.x - i) - 0.5, w - 0.5);
            jgraphics_move_to(g, long(ctr.x + i) - 0.5, 0. - 0.5);
            jgraphics_line_to(g, long(ctr.x + i) - 0.5, w - 0.5);
            jgraphics_set_line_width(g, 2);
            jgraphics_scale(g, 0.25, 0.25);
            jgraphics_stroke(g);
            jgraphics_scale(g, 4, 4);
        }
        
        // Circles //
        double radius = x->f_zoom_factor * (maxctr*2) / 10.;
        for(int i = 5; i > 0; i--)
        {
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_arc(g, long(ctr.x)+0.5, long(ctr.y)+0.5, (double)i * radius - 1,  0., JGRAPHICS_2PI);
            jgraphics_scale(g, 0.5, 0.5); // tricks to draw a 0.5 line width
            jgraphics_stroke(g);
            jgraphics_scale(g, 2, 2);
            
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_arc(g, long(ctr.x) - 0.5, long(ctr.y) - 0.5, (double)i * radius - 1,  0., JGRAPHICS_2PI);
            jgraphics_scale(g, 0.5, 0.5);
            jgraphics_stroke(g);
            jgraphics_scale(g, 2, 2);
        }
        
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_flyrect(t_hoaboids *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g;
    t_jmatrix transform;
    double w = rect->width;
    double cornerSize = 3;
    double dashes[2] = {5, 5};
    t_pt topLeft, bottomRight;
    topLeft.x = x->f_flyrect[0] * (w*0.5) * x->f_zoom_factor;
    topLeft.y = x->f_flyrect[1] * (w*0.5) * x->f_zoom_factor;
    bottomRight.x = x->f_flyrect[2] * (w*0.5) * x->f_zoom_factor;
    bottomRight.y = x->f_flyrect[3] * (w*0.5) * x->f_zoom_factor;
    
	g = jbox_start_layer((t_object *)x, view, gensym("flyrect_layer"), w, rect->height);
	
	if (g)
    {
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
		jgraphics_set_matrix(g, &transform);
        
        jgraphics_set_source_jrgba(g, &x->f_colorFlyrect);
        
        jgraphics_arc(g, topLeft.x, topLeft.y, cornerSize, 0, CICM_2PI);
        jgraphics_fill(g);
        
        jgraphics_arc(g, bottomRight.x, bottomRight.y, cornerSize, 0, CICM_2PI);
        jgraphics_fill(g);
        
        jgraphics_set_line_width(g, 1);
        jgraphics_set_dash(g, dashes, 2, 0);
        
        //top
        jgraphics_move_to(g, topLeft.x + cornerSize*1.5, long(topLeft.y)+0.5);
        jgraphics_line_to(g, bottomRight.x, long(topLeft.y)+0.5);
        jgraphics_stroke(g);
        
        //right
        jgraphics_move_to(g, long(bottomRight.x)+0.5, topLeft.y);
        jgraphics_line_to(g, long(bottomRight.x)+0.5, bottomRight.y + cornerSize*1.5);
        jgraphics_stroke(g);
        
        //bottom
        jgraphics_move_to(g, topLeft.x, long(bottomRight.y)+0.5);
        jgraphics_line_to(g, bottomRight.x - cornerSize*1.5, long(bottomRight.y)+0.5);
        jgraphics_stroke(g);
        
        //left
        jgraphics_move_to(g, long(topLeft.x)+0.5, topLeft.y - cornerSize*1.5);
        jgraphics_line_to(g, long(topLeft.x)+0.5, bottomRight.y);
        jgraphics_stroke(g);
        
		jbox_end_layer((t_object*)x, view, gensym("flyrect_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("flyrect_layer"), 0., 0.);
}

void draw_boids(t_hoaboids *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g;
    t_jmatrix transform;
    double w = rect->width;
    double h = rect->height;
    double BoidPos[2];
    double BoidDir[2];
    //t_pt flockCenter;
    double BoidAngle;
    double BoidSize = 10;
    
    t_jrgba black, white;
    
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
    black = white = x->f_colorBoids;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
		
	if ((g = jbox_start_layer((t_object *)x, view, gensym("boids_layer"), rect->width, rect->height)))
    {
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
		jgraphics_set_matrix(g, &transform);
        
        jgraphics_set_source_jrgba(g, &x->f_colorBoids);
        
        for (int i=0; i < x->f_boids_manager->getNumberOfBoids(); i++)
        {
            if(x->f_boids_manager->getBoidPosCoord(i, BoidPos))
            {
                BoidPos[0] *= (w*0.5) * x->f_zoom_factor;
                BoidPos[1] *= (h*0.5) * x->f_zoom_factor;
                
                x->f_boids_manager->getBoidDirCoord(i, BoidDir);
                BoidAngle = Tools::angle(BoidDir[0], BoidDir[1])-CICM_PI2;
                
                jgraphics_translate(g, BoidPos[0], BoidPos[1]);
                jgraphics_rotate(g, BoidAngle);
                
                jgraphics_set_source_jrgba(g, Tools::isInsideDeg(Tools::radToDeg(BoidAngle), 45, -135) ? &x->f_colorBoids : &white);
                jgraphics_move_to(g, 0, -BoidSize*0.2);
                jgraphics_line_to(g, 0, BoidSize*0.5);
                jgraphics_line_to(g, -BoidSize*0.4, -BoidSize*0.4);
                jgraphics_line_to(g, 0, -BoidSize*0.2);
                jgraphics_fill(g);
                
                jgraphics_set_source_jrgba(g, !Tools::isInsideDeg(Tools::radToDeg(BoidAngle), 45, -135) ? &x->f_colorBoids : &white);
                jgraphics_move_to(g, 0, -BoidSize*0.2);
                jgraphics_line_to(g, 0, BoidSize*0.5);
                jgraphics_line_to(g, BoidSize*0.4, -BoidSize*0.4);
                jgraphics_line_to(g, 0, -BoidSize*0.2);
                jgraphics_fill(g);
                
                jgraphics_set_source_jrgba(g, &black);
                jgraphics_move_to(g, 0, -BoidSize*0.2);
                jgraphics_line_to(g, 0, BoidSize*0.5);
                jgraphics_fill(g);
                
                jgraphics_rotate(g, -BoidAngle);
                jgraphics_translate(g, -BoidPos[0], -BoidPos[1]);
            }
            
            /*
            flockCenter.x = x->f_boids_manager->getCenterPt_abscissa() * (w*0.5) * x->f_zoom_factor;
            flockCenter.y = x->f_boids_manager->getCenterPt_ordinate() * (w*0.5) * x->f_zoom_factor;
            jgraphics_set_source_jrgba(g, &x->f_colorFlyrect);
            jgraphics_arc(g, flockCenter.x, flockCenter.y, 5, 0, CICM_2PI);
            jgraphics_fill(g);
            */
        }
        
		jbox_end_layer((t_object*)x, view, gensym("boids_layer"));
    }
	jbox_paint_layer((t_object *)x, view, gensym("boids_layer"), 0., 0.);
}


void draw_attractor(t_hoaboids *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g = NULL;
    t_jmatrix transform;
    double w = rect->width;
    double h = rect->height;
    double attSize = 5;
    
    double attPosX = x->f_attractpt[0] * ( (w*0.5) * x->f_zoom_factor);
    double attPosY = x->f_attractpt[1] * ( (h*0.5) * x->f_zoom_factor);
		
	if ((g = jbox_start_layer((t_object *)x, view, gensym("attractor_layer"), rect->width, rect->height)))
    {
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
		jgraphics_set_matrix(g, &transform);
        
        jgraphics_set_source_jrgba(g, &x->f_colorAttractor);
        
        jgraphics_set_line_width(g, 1);
        jgraphics_move_to(g, attPosX - attSize*0.5, attPosY - attSize*0.5);
        jgraphics_line_to(g, attPosX + attSize*0.5, attPosY + attSize*0.5);
        jgraphics_stroke(g);
        
        jgraphics_move_to(g, attPosX - attSize*0.5, attPosY + attSize*0.5);
        jgraphics_line_to(g, attPosX + attSize*0.5, attPosY - attSize*0.5);
        jgraphics_stroke(g);
        
        //jgraphics_set_line_width(g, 2);
        jgraphics_arc(g, attPosX, attPosY, attSize, 0, CICM_2PI);
        jgraphics_stroke(g);
        
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
}

void hoaboids_mouseup(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    /*
    jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
    jbox_redraw((t_jbox *)x);
    */
}

void hoaboids_mousewheel(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	if (modifiers == eAltKey)
    {
		double newZoom = x->f_zoom_factor + y_inc / 100.;
        x->f_zoom_factor = Tools::clip(newZoom, MIN_ZOOM, MAX_ZOOM);
        object_attr_touch((t_object*)x, gensym("zoom"));
        object_notify(x, _sym_modified, NULL);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("attractor_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("flyrect_layer"));
        jbox_redraw((t_jbox *)x);
	}
}

void hoaboids_mouseenter(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void hoaboids_mousemove(t_hoaboids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->cmdKeyPressed = 0;
    /*
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
    double ditanceSelected = (x->f_size_source / x->rect.width * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    */

    /*
    jbox_invalidate_layer((t_object *)x, NULL, gensym("boids_layer"));
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
	//post("keycode : %ld , modifiers : %ld , textcharacter : %ld ", keycode, modifiers, textcharacter);
    int filter = 0;
	return filter;	// returns 1 if you want to filter it from the key object (otherwise return 0)
}