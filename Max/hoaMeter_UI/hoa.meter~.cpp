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

#include "../../Sources/HoaLibrary.h"

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
#include "z_dsp.h"
}

#define MAX_SPEAKER 64
#define DEF_SPEAKER 8
#define OVERLED_DRAWTIME 1000

typedef struct  _meter
{
	t_pxjbox	j_box;
    t_rect      f_rect;
	
	void*		f_clock;
	int			f_startclock;
	t_atom_long	f_interval;
    
    t_atom_long f_number_of_loudspeakers;
	double      f_offsetOfLoudspeakers;
	
	t_atom_long			f_dbperled;
	t_atom_long			f_nhotleds;
	t_atom_long			f_ntepidleds;
	t_atom_long			f_nwarmleds;
	t_atom_long			f_numleds;
	
	double		f_angles_of_loudspeakers[MAX_SPEAKER];
	double		f_speakerRealAngle[MAX_SPEAKER];
	double		f_speakerWidth[MAX_SPEAKER];
    long		f_drawOverLedleftTime[MAX_SPEAKER];
	
	t_jrgba		f_colorBackground;
	t_jrgba		f_colorMeterBg;
	t_jrgba		f_colorBorder;
	t_jrgba		f_colorMeterBorder;
	t_jrgba		f_colorColdSignal;
	t_jrgba		f_colorTepidSignal;
	t_jrgba		f_colorWarmSignal;
	t_jrgba		f_colorHotSignal;
	t_jrgba		f_colorOverSignal;
	
	t_jrgba		f_colorEnergy;
	t_jrgba		f_colorVelocity;
	
	t_pt		f_center;
	double		f_rayonMax;
	double		f_rayonCircle;
	double		f_fontsize;
	
	double		f_strokeWidth;
	double		f_rayonExt;
	double		f_rayonInt;
    
	t_atom_long         f_leds_bg;
    t_atom_long         f_drawvector;
    t_atom_long         f_drawmborder;
	double              f_metersize;
    t_atom_long         f_speakers_dir_of_rotation;
    t_atom_long         f_fill_direction;
    
    void*               f_vector_outlet;
    void*               f_peaks_outlet;
	
    AmbisonicsMeter*     f_meter;
} t_meter;

t_class *meter_class;

/* Common ------------------------------------- */
void *meter_new(t_symbol *s, int argc, t_atom *argv);
void meter_free(t_meter *x);
void meter_assist(t_meter *x, void *b, long m, long a, char *s);
/* DSP ------------------------------------- */
void meter_dsp64(t_meter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void meter_perform64(t_meter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void meter_tick(t_meter *x);
void meter_output(t_meter *x);

t_max_err meter_notify(t_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err number_of_loudspeakers_set(t_meter *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_of_loudspeakers_set(t_meter *x, void *attr, long ac, t_atom *av);

void meter_resize_inlet(t_meter *x, long lastNumberOfOutlet);

/* Paint ------------------------------------- */
void meter_getdrawparams(t_meter *x, t_object *patcherview, t_jboxdrawparams *params);
void meter_paint(t_meter *x, t_object *view);
void draw_background(t_meter *x, t_object *view, t_rect *rect);
void draw_meter(t_meter *x,  t_object *view, t_rect *rect);
void draw_vector_energy(t_meter *x, t_object *view, t_rect *rect);
void draw_vector_velocity(t_meter *x, t_object *view, t_rect *rect);
void draw_angle(t_meter *x,  t_object *view, t_rect *rect);
void draw_skelton(t_meter *x,  t_object *view, t_rect *rect);
void draw_separator(t_meter *x,  t_object *view, t_rect *rect);

int C74_EXPORT main()
{
	t_class *c;
    
	c = class_new("hoa.meter~", (method)meter_new, (method)meter_free, (short)sizeof(t_meter), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);
	
	class_addmethod(c, (method) meter_dsp64,		 "dsp64",		  A_CANT, 0);
	class_addmethod(c, (method) meter_assist,		 "assist",		  A_CANT, 0);
	class_addmethod(c, (method) meter_paint,		 "paint",		  A_CANT, 0);
	class_addmethod(c, (method) meter_notify,        "notify",		  A_CANT, 0);
    class_addmethod(c, (method) meter_getdrawparams, "getdrawparams", A_CANT, 0);
    
	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 225 225");
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	
	/* APPEARANCE */
    CLASS_STICKY_CATEGORY       (c, 0, "Appearance");
    
	CLASS_ATTR_LONG				(c, "leds_bg", 0, t_meter, f_leds_bg);
	CLASS_ATTR_ORDER			(c, "leds_bg", 0, "1");
	CLASS_ATTR_STYLE_LABEL		(c, "leds_bg", 0, "onoff", "Draw Leds Background");
	CLASS_ATTR_DEFAULT			(c, "leds_bg", 0, "1");
	CLASS_ATTR_SAVE				(c, "leds_bg", 1);
	
	CLASS_ATTR_LONG				(c, "drawvector", 0, t_meter, f_drawvector);
	CLASS_ATTR_ORDER			(c, "drawvector", 0, "2");
    CLASS_ATTR_LABEL            (c, "drawvector", 0, "Draw Vectors");
    CLASS_ATTR_ENUMINDEX4       (c, "drawvector", 0, "none", "energy", "velocity", "both")
	CLASS_ATTR_DEFAULT			(c, "drawvector", 0, "1");
	CLASS_ATTR_SAVE				(c, "drawvector", 1);
    
    CLASS_ATTR_LONG				(c, "drawmborder", 0, t_meter, f_drawmborder);
	CLASS_ATTR_ORDER			(c, "drawmborder", 0, "3");
    CLASS_ATTR_LABEL            (c, "drawmborder", 0, "Draw Meter Borders");
    CLASS_ATTR_ENUMINDEX4       (c, "drawmborder", 0, "none", "Circles", "Axes", "both")
	CLASS_ATTR_DEFAULT			(c, "drawmborder", 0, "3");
	CLASS_ATTR_SAVE				(c, "drawmborder", 1);
	
	CLASS_ATTR_DOUBLE			(c, "metersize", 0, t_meter, f_metersize);
	CLASS_ATTR_ORDER			(c, "metersize", 0, "4");
	CLASS_ATTR_LABEL			(c, "metersize", 0, "Meter Circle Size");
	CLASS_ATTR_FILTER_CLIP		(c, "metersize", 0., 1);
	CLASS_ATTR_DEFAULT			(c, "metersize", 0, "0.8");
	CLASS_ATTR_SAVE				(c, "metersize", 1);
    
    CLASS_ATTR_LONG				(c, "orientation", 0, t_meter, f_fill_direction);
	CLASS_ATTR_LABEL			(c, "orientation", 0, "Meter Fill Orientation");
    CLASS_ATTR_ORDER			(c, "orientation", 0, "5");
	CLASS_ATTR_ENUMINDEX		(c, "orientation", 0, "inside outside");
    CLASS_ATTR_ALIAS            (c, "orientation", "fill_dir");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"orientation",0, "0");
    
    CLASS_STICKY_CATEGORY_CLEAR (c);
	
	/* BEHAVIOR */
    CLASS_STICKY_CATEGORY       (c, 0, "Behavior");
    
	CLASS_ATTR_LONG				(c, "channels", 0 , t_meter, f_number_of_loudspeakers);
    CLASS_ATTR_ACCESSORS		(c, "channels", NULL, number_of_loudspeakers_set);
	CLASS_ATTR_ORDER			(c, "channels", 0, "1");
	CLASS_ATTR_LABEL			(c, "channels", 0, "Number of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "channels", 1);
    CLASS_ATTR_DEFAULT          (c, "channels", 0, "8");
    CLASS_ATTR_ALIAS            (c, "channels", "loudspeakers");
    
	CLASS_ATTR_DOUBLE_VARSIZE	(c, "angles", 0, t_meter,f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_of_loudspeakers_set);
	CLASS_ATTR_ORDER			(c, "angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "angles", 1);
    
	CLASS_ATTR_DOUBLE			(c, "offset", 0, t_meter, f_offsetOfLoudspeakers);
	CLASS_ATTR_ORDER			(c, "offset", 0, "3");
	CLASS_ATTR_LABEL			(c, "offset", 0, "Offset of Loudspeakers");
	CLASS_ATTR_DEFAULT			(c, "offset", 0, "0");
	CLASS_ATTR_SAVE				(c, "offset", 1);
    
    CLASS_ATTR_LONG				(c, "rotation", 0, t_meter, f_speakers_dir_of_rotation);
    CLASS_ATTR_ORDER			(c, "rotation", 0, "4");
	CLASS_ATTR_LABEL			(c, "rotation", 0, "Rotation of Loudspeakers");
	CLASS_ATTR_ENUMINDEX		(c, "rotation", 0, "clockwise anti-clockwise");
    CLASS_ATTR_ALIAS            (c, "rotation", "ls_rot_dir");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"rotation",0, "1");
    
    CLASS_ATTR_LONG				(c, "interval", 0, t_meter, f_interval);
	CLASS_ATTR_ORDER			(c, "interval", 0, "5");
	CLASS_ATTR_LABEL			(c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN		(c, "interval", 20);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "50");
	CLASS_ATTR_SAVE				(c, "interval", 1);
    
    CLASS_STICKY_CATEGORY_CLEAR (c);
	
    /* VALUE */
    CLASS_STICKY_CATEGORY(c, 0, "Value");
	CLASS_ATTR_LONG				(c, "dbperled", 0, t_meter, f_dbperled);
	CLASS_ATTR_ORDER			(c, "dbperled", 0, "4");
	CLASS_ATTR_LABEL			(c, "dbperled", 0, "DeciBels per Led");
	CLASS_ATTR_FILTER_CLIP		(c, "dbperled", 1, 12);
	CLASS_ATTR_DEFAULT			(c, "dbperled", 0, "3");
	CLASS_ATTR_SAVE				(c, "dbperled", 1);
	
	CLASS_ATTR_LONG				(c, "nhotleds", 0, t_meter, f_nhotleds);
	CLASS_ATTR_ORDER			(c, "nhotleds", 0, "5");
	CLASS_ATTR_LABEL			(c, "nhotleds", 0, "Number of Hot Leds");
	CLASS_ATTR_FILTER_CLIP		(c, "nhotleds", 0, 20);
	CLASS_ATTR_DEFAULT			(c, "nhotleds", 0, "3");
	CLASS_ATTR_SAVE				(c, "nhotleds", 1);
	
	CLASS_ATTR_LONG				(c, "ntepidleds", 0, t_meter, f_ntepidleds);
	CLASS_ATTR_ORDER			(c, "ntepidleds", 0, "6");
	CLASS_ATTR_LABEL			(c, "ntepidleds", 0, "Number of Tepid Leds");
	CLASS_ATTR_FILTER_CLIP		(c, "ntepidleds", 0, 20);
	CLASS_ATTR_DEFAULT			(c, "ntepidleds", 0, "3");
	CLASS_ATTR_SAVE				(c, "ntepidleds", 1);
	
	CLASS_ATTR_LONG				(c, "nwarmleds", 0, t_meter, f_nwarmleds);
	CLASS_ATTR_ORDER			(c, "nwarmleds", 0, "7");
	CLASS_ATTR_LABEL			(c, "nwarmleds", 0, "Number of Warm Leds");
	CLASS_ATTR_FILTER_CLIP		(c, "nwarmleds", 0, 20);
	CLASS_ATTR_DEFAULT			(c, "nwarmleds", 0, "3");
	CLASS_ATTR_SAVE				(c, "nwarmleds", 1);
	
	CLASS_ATTR_LONG				(c, "numleds", 0, t_meter, f_numleds);
	CLASS_ATTR_ORDER			(c, "numleds", 0, "8");
	CLASS_ATTR_LABEL			(c, "numleds", 0, "Total Number of Leds");
	CLASS_ATTR_FILTER_CLIP		(c, "numleds", 10, 20);
	CLASS_ATTR_DEFAULT			(c, "numleds", 0, "12");
	CLASS_ATTR_SAVE				(c, "numleds", 1);
	
    CLASS_STICKY_CATEGORY_CLEAR (c);
	
	/* COLORS */
    CLASS_STICKY_CATEGORY(c, 0, "Color");
    CLASS_STICKY_ATTR(c, "style", 0, "rgba");
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_meter, f_colorBackground);
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.55 0.55 0.55 1.");
	
	CLASS_ATTR_RGBA				(c, "mbgcolor", 0, t_meter, f_colorMeterBg);
	CLASS_ATTR_LABEL			(c, "mbgcolor", 0, "Meter Background Color");
	CLASS_ATTR_ORDER			(c, "mbgcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "mbgcolor", 0, "0.4 0.4 0.4 1.");
	
	CLASS_ATTR_RGBA				(c, "bordercolor", 0, t_meter, f_colorBorder);
	CLASS_ATTR_LABEL			(c, "bordercolor", 0, "Box Border Color");
	CLASS_ATTR_ORDER			(c, "bordercolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bordercolor", 0, "0.25 0.25 0.25 1");
	
	CLASS_ATTR_RGBA				(c, "coldcolor", 0, t_meter, f_colorColdSignal);
	CLASS_ATTR_LABEL			(c, "coldcolor", 0, "Cold Signal Color");
	CLASS_ATTR_ORDER			(c, "coldcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "coldcolor", 0, "0. 0.6 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "tepidcolor", 0, t_meter, f_colorTepidSignal);
	CLASS_ATTR_LABEL			(c, "tepidcolor", 0, "Tepid Signal Color");
	CLASS_ATTR_ORDER			(c, "tepidcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "tepidcolor", 0, "0.6 0.73 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "warmcolor", 0, t_meter, f_colorWarmSignal);
	CLASS_ATTR_LABEL			(c, "warmcolor", 0, "Warm Signal Color");
	CLASS_ATTR_ORDER			(c, "warmcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "warmcolor", 0, ".85 .85 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "hotcolor", 0, t_meter, f_colorHotSignal);
	CLASS_ATTR_LABEL			(c, "hotcolor", 0, "Hot Signal Color");
	CLASS_ATTR_ORDER			(c, "hotcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "hotcolor", 0, "1. 0.6 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "overcolor", 0, t_meter, f_colorOverSignal);
	CLASS_ATTR_LABEL			(c, "overcolor", 0, "Overload Signal Color");
	CLASS_ATTR_ORDER			(c, "overcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "overcolor", 0, "1. 0. 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "energycolor", 0, t_meter, f_colorEnergy);
	CLASS_ATTR_LABEL			(c, "energycolor", 0, "Energy Vector Color");
	CLASS_ATTR_ORDER			(c, "energycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "energycolor", 0, "0. 0. 1. 0.8");
    
    CLASS_ATTR_RGBA				(c, "velocitycolor", 0, t_meter, f_colorVelocity);
	CLASS_ATTR_LABEL			(c, "velocitycolor", 0, "Velocity Vector Color");
	CLASS_ATTR_ORDER			(c, "velocitycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "velocitycolor", 0, "1. 0. 0. 0.8");
    CLASS_STICKY_ATTR_CLEAR(c, "style");
    CLASS_STICKY_CATEGORY_CLEAR(c);
	
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
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
    
	x = (t_meter *)object_alloc(meter_class);
	flags = 0
    | JBOX_DRAWFIRSTIN
    | JBOX_DRAWINLAST
    | JBOX_TRANSPARENT
    | JBOX_DRAWBACKGROUND
    | JBOX_GROWY
    ;
    
    x->f_number_of_loudspeakers = 8;
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
    
	dsp_setupjbox((t_pxjbox *)x, x->f_number_of_loudspeakers);
    x->f_peaks_outlet = listout(x);
    x->f_vector_outlet = listout(x);
    
    x->f_meter = new AmbisonicsMeter(x->f_number_of_loudspeakers);
    
    dictionary_getlong(d, gensym("channels"), &x->f_number_of_loudspeakers);
    
    x->f_meter->setNumberOfLoudspeakers(x->f_number_of_loudspeakers);
    x->f_number_of_loudspeakers = x->f_meter->getNumberOfInputs();

	attr_dictionary_process(x, d);
	
	x->f_clock = clock_new(x,(method)meter_tick);
	x->f_startclock = 0;
	
	jbox_ready((t_jbox *)x);
	
	return (x);
}

void meter_getdrawparams(t_meter *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = x->f_strokeWidth;
	params->d_cornersize = 8;
    params->d_bordercolor = x->f_colorBorder;
    params->d_boxfillcolor = x->f_colorBackground;
}

t_max_err number_of_loudspeakers_set(t_meter *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        int dspState = sys_getdspobjdspstate((t_object*)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
            x->f_number_of_loudspeakers = Tools::clip(long(atom_getfloat(argv)), long(1), long(MAX_SPEAKER));
                
        if (x->f_number_of_loudspeakers == 1)
        {
            object_attr_setdisabled((t_object*)x, gensym("ls_angles"), 1);
            object_attr_setdisabled((t_object*)x, gensym("offset"), 1);
            object_attr_setdisabled((t_object*)x, gensym("ls_rot_dir"), 1);
        }
        else
        {
            object_attr_setdisabled((t_object*)x, gensym("ls_angles"), 0);
            object_attr_setdisabled((t_object*)x, gensym("offset"), 0);
            object_attr_setdisabled((t_object*)x, gensym("ls_rot_dir"), 0);
        }
        
        x->f_meter->setNumberOfLoudspeakers(x->f_number_of_loudspeakers);
        meter_resize_inlet(x, x->f_number_of_loudspeakers);
        
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("start"));
        
        long    argc = x->f_number_of_loudspeakers;
        t_atom* argv = new t_atom[argc];
        for(int i = 0; i < argc; i++)
            atom_setfloat(argv+i, ((double)i / (double)x->f_number_of_loudspeakers) * 360.);
        
        object_method(x, gensym("angles"), argc, argv);
        object_attr_touch((t_object *)x, gensym("angles"));
    }
    return NULL;
}

t_max_err angles_of_loudspeakers_set(t_meter *x, void *attr, long ac, t_atom *av)
{
    if (ac && av)
    {
        for(int i = 0; i < ac && i < x->f_number_of_loudspeakers; i++)
        {
            if(atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG)
                x->f_meter->setLoudspeakerAngleDegrees(i, atom_getfloat(av+i));
        }
        
    }
    
    for (int i=0; i < x->f_meter->getNumberOfInputs(); i++)
    {
        x->f_angles_of_loudspeakers[i] = x->f_meter->getLoudspeakerAngle(i);
    }
    
	double curAngle, prevAngle, nextAngle, prevPortion, nextPortion;

	for(int i = 0; i < x->f_number_of_loudspeakers; i++)
	{
		curAngle = x->f_angles_of_loudspeakers[i];
		if (i != 0)
            prevAngle = x->f_angles_of_loudspeakers[i-1];
		else
            prevAngle = x->f_angles_of_loudspeakers[x->f_number_of_loudspeakers-1];
		if (i != x->f_number_of_loudspeakers-1)
            nextAngle = x->f_angles_of_loudspeakers[i+1];
		else
            nextAngle = x->f_angles_of_loudspeakers[0];
		
		prevPortion = Tools::degreeWrap(curAngle - prevAngle);
		nextPortion = Tools::degreeWrap(nextAngle - curAngle);
		
		x->f_speakerWidth[i] = (prevPortion + nextPortion)*0.5;
		x->f_speakerRealAngle[i] = (curAngle - prevPortion*0.5) + x->f_speakerWidth[i]*0.5;
	}
    
	jbox_invalidate_layer((t_object *)x, NULL, gensym("skelton_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("separator_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("energy_vector_layer"));
	jbox_redraw((t_jbox *)x);
    return MAX_ERR_NONE;
}

void meter_dsp64(t_meter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_meter->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, meter_perform64, 0, NULL);
	x->f_startclock = 1;
}

void meter_perform64(t_meter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_meter->process(ins);
    
	if (x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void meter_tick(t_meter *x)
{
    x->f_meter->processEnergy();
    x->f_meter->processVectors();
    meter_output(x);
    
    double peak;
    for (int i=0; i<x->f_meter->getNumberOfInputs(); i++)
    {
        peak = x->f_meter->getLoudspeakerEnergy(i); // dB (negatif) de -240 à 0;
        if ( peak >= 0. ) x->f_drawOverLedleftTime[i] = OVERLED_DRAWTIME;
        else x->f_drawOverLedleftTime[i] -= x->f_interval;
        if (x->f_drawOverLedleftTime[i] < 0) x->f_drawOverLedleftTime[i] = 0;
    }
    
	jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("energy_vector_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("velocity_vector_layer"));
	jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

void meter_output(t_meter *x)
{
    long nbChannels = x->f_meter->getNumberOfInputs();
    t_atom*	av_peaks = new t_atom[nbChannels];
    t_atom	av_vectors[4];
    
    for (int i=0; i<nbChannels; i++)
        atom_setfloat(av_peaks+i, fabs(x->f_meter->getLoudspeakerPeaks(i)));
    outlet_list(x->f_peaks_outlet, NULL, nbChannels, av_peaks);
    
    atom_setfloat(av_vectors,   x->f_meter->getEnergyVectorAbscissa());
    atom_setfloat(av_vectors+1, x->f_meter->getEnergyVectorOrdinate());
    atom_setfloat(av_vectors+2, x->f_meter->getVelocityVectorAbscissa());
    atom_setfloat(av_vectors+3, x->f_meter->getVelocityVectorOrdinate());
    outlet_list(x->f_vector_outlet, NULL, 4, av_vectors);
	free(av_peaks);
}

void meter_free(t_meter *x)
{
	dsp_freejbox((t_pxjbox *)x);
	freeobject((t_object *)x->f_clock);
	jbox_free((t_jbox *)x);
    delete x->f_meter;
}

void meter_assist(t_meter *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_meter->getChannelName(a).c_str());
    else
    {
        if (a == 0)
            sprintf(s,"(list) Vectors Values For Each Metering Interval : Energy(x/y) and Velocity(x/y)");
        else if (a == 1)
            sprintf(s,"(list) Peak Values For Each Metering Interval");
    }
}

t_max_err meter_notify(t_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		if(name == gensym("mbgcolor") || name == gensym("leds_bg") || name == gensym("drawmborder"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("skelton_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("separator_layer"));
		}
		else if(name == gensym("cicolor") || name == gensym("coldcolor") || name == gensym("tepidcolor") || name == gensym("warmcolor") || name == gensym("hotcolor") || name == gensym("overcolor") || name == gensym("numleds"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("skelton_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("separator_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
		}
        else if(name == gensym("drawvector"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("energy_vector_layer"));
		}
		else if(name == gensym("energycolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("energy_vector_layer"));
		}
        else if(name == gensym("velocitycolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("velocity_vector_layer"));
		}
		else if(name == gensym("offset") || name == gensym("metersize") || name == gensym("ls_rot_dir") || name == gensym("fill_dir"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("skelton_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("separator_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("energy_vector_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("velocity_vector_layer"));
		}
		else if(name == gensym("dbperled") || name == gensym("nhotleds") || name == gensym("ntepidleds") || name == gensym("nwarmleds"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void meter_paint(t_meter *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
    x->f_rect = rect;
	
	x->f_center.x = rect.width * .5;
	x->f_center.y = rect.height * .5;
	
	x->f_rayonMax = rect.width * .5;
	if(rect.width > rect.height)
		x->f_rayonMax = rect.height * .5;
	
	x->f_fontsize = (x->f_rayonMax / 14.) - 1.;
	x->f_rayonCircle = x->f_rayonMax / 32;
	
    x->f_strokeWidth = 1;
	x->f_rayonExt = x->f_rayonMax - (x->f_strokeWidth*0.5) - 2;
	x->f_rayonInt = x->f_rayonExt*(1 - x->f_metersize);
	
	draw_skelton(x, view, &rect);
    draw_meter(x, view, &rect);
    if (x->f_drawmborder == 2 || x->f_drawmborder == 3)
        draw_separator(x, view, &rect);
    if (x->f_drawvector == 2 || x->f_drawvector == 3)
		draw_vector_velocity(x, view, &rect);
	if (x->f_drawvector == 1 || x->f_drawvector == 3)
		draw_vector_energy(x, view, &rect);
}

void draw_skelton(t_meter *x,  t_object *view, t_rect *rect)
{
	int i,j;
	double deg1, deg2, rotateAngle, ledContainerSize, ledStroke, ledMargin, ledOffset;
	t_pt center = x->f_center;
	t_jrgba ledBgColor = {0,0,0,0.05};
    t_jrgba black, white;
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("skelton_layer"), rect->width, rect->height);
	
	deg1 = Tools::degToRad(90);
	ledContainerSize = x->f_rayonExt - x->f_rayonInt - (x->f_strokeWidth*4);
	ledOffset = ledContainerSize / (x->f_numleds+1);
	ledStroke = ledOffset * 0.75;
	ledMargin = ledOffset * 0.25;
    
    black = white = x->f_colorMeterBg;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
	
	if (g)
	{
		// Background :
		jgraphics_set_source_jrgba(g, &x->f_colorMeterBg);
		jgraphics_set_line_width(g, (x->f_rayonExt - x->f_rayonInt) - x->f_strokeWidth*0.5);
		jgraphics_arc(g, center.x, center.y, x->f_rayonExt*0.5+(x->f_rayonInt*0.5), 0., JGRAPHICS_2PI);
		jgraphics_stroke(g);
		jgraphics_arc_negative(g, center.x, center.y, x->f_rayonExt*0.5+(x->f_rayonInt*0.5), JGRAPHICS_PI, -JGRAPHICS_2PI); // due to a stroke bug !
		jgraphics_stroke(g);
		
        // skelton circles :
        if (x->f_drawmborder == 1 || x->f_drawmborder == 3)
        {
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_set_line_width(g, x->f_strokeWidth);
            jgraphics_arc(g, center.x+1, center.y+1, x->f_rayonExt,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
            jgraphics_arc(g, center.x+1, center.y+1, x->f_rayonInt,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
            
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_set_line_width(g, x->f_strokeWidth);
            jgraphics_arc(g, center.x, center.y, x->f_rayonExt,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
            jgraphics_arc(g, center.x, center.y, x->f_rayonInt,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
        }
        
        if (x->f_leds_bg)
        {
            jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
            jgraphics_set_matrix(g, &transform);
            
            white.alpha = 0.5;
            // skelton separators and leds bg:
            for(i=0; i < x->f_number_of_loudspeakers; i++)
            {
                deg2 = Tools::degToRad(90+(x->f_speakerWidth[i]));
                rotateAngle = x->f_speakerRealAngle[i] - (x->f_speakerWidth[i]*0.5) + x->f_offsetOfLoudspeakers;
                if (!x->f_speakers_dir_of_rotation) {
                    rotateAngle += x->f_speakerWidth[i];
                    rotateAngle *= -1;
                }
                jgraphics_rotate(g, Tools::degToRad(rotateAngle));
                
                // leds Background :
                jgraphics_set_line_width(g, ledStroke);
                jgraphics_set_source_jrgba(g, &white);
                for( j=0; j < x->f_numleds; j++ )
                {
                    jgraphics_set_line_cap(g, (x->f_number_of_loudspeakers < 24 && (x->f_speakerWidth[i] > 14.5)) ? JGRAPHICS_LINE_CAP_ROUND : JGRAPHICS_LINE_CAP_BUTT);
                    if ( Tools::isInsideDeg(rotateAngle, -45, 135) )
                    {
                        if (x->f_number_of_loudspeakers > 1) {
                            if ( x->f_number_of_loudspeakers < 24  && (x->f_speakerWidth[i] > 14.5)) {
                                
                                double tmpdeg1 = 0, tmpdeg2 = 0, tmprad = 0;
                                
                                if (x->f_fill_direction == 0) { // inside
                                    tmpdeg1 = deg1+(0.008 * (j+4) * x->f_metersize);
                                    tmpdeg2 = deg2-(0.008 * (j+4) * x->f_metersize);
                                    tmprad = x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2;
                                } else { // outside
                                    tmpdeg1 = deg1+(0.008 * (x->f_numleds+3-(j)) * x->f_metersize);
                                    tmpdeg2 = deg2-(0.008 * (x->f_numleds+3-(j)) * x->f_metersize);
                                    tmprad = x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2;
                                }
                                if (tmpdeg1 < tmpdeg2)  jgraphics_arc(g, 0, 1, tmprad,  tmpdeg1, tmpdeg2);
                                else
                                {
                                    jgraphics_arc(g, 0, 1, tmprad, tmpdeg2, tmpdeg1);
                                    //jgraphics_arc_negative(g, 0, 0, tmprad, tmpdeg1, tmpdeg2);
                                }
                                
                                /*
                                if (x->f_fill_direction == 0) { // inside
                                    jgraphics_arc(g, 0, 1, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2, deg1+(0.008 * (j+4) * x->f_metersize), deg2-(0.008 * (j+4) * x->f_metersize) );
                                } else { // outside
                                    jgraphics_arc(g, 0, 1, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2, deg1+(0.008 * (x->f_numleds+3-(j)) * x->f_metersize), deg2-(0.008 * (x->f_numleds+3-(j)) * x->f_metersize) );
                                }
                                */
                            }
                            else {
                                if (x->f_fill_direction == 0) { // inside
                                    jgraphics_arc_negative(g, 0, 1, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2, deg2, deg1);
                                } else { // outside
                                    jgraphics_arc_negative(g, 0, 1, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2, deg2, deg1);
                                }
                            }
                        }
                        else { // mono
                            if (x->f_fill_direction == 0) { // inside
                                jgraphics_arc(g, 0, -1, x->f_rayonExt-(j*ledOffset)-ledMargin*2-x->f_strokeWidth*2-1,  0, JGRAPHICS_2PI);
                            } else { // outside
                                jgraphics_arc(g, 0, -1, x->f_rayonInt+(j*ledOffset)+ledMargin*2+x->f_strokeWidth*2-1,  0, JGRAPHICS_2PI);
                            }
                        }
                    }
                    else
                    {
                        if (x->f_number_of_loudspeakers > 1) {
                            if ( x->f_number_of_loudspeakers < 24  && (x->f_speakerWidth[i] > 14.5))
                            {
                                double tmpdeg1 = 0, tmpdeg2 = 0, tmprad = 0;
                                
                                if (x->f_fill_direction == 0) { // inside
                                    tmpdeg1 = deg1+(0.008 * (j+4) * x->f_metersize);
                                    tmpdeg2 = deg2-(0.008 * (j+4) * x->f_metersize);
                                    tmprad = x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2;
                                } else { // outside
                                    tmpdeg1 = deg1+(0.008 * (x->f_numleds+3-(j)) * x->f_metersize);
                                    tmpdeg2 = deg2-(0.008 * (x->f_numleds+3-(j)) * x->f_metersize);
                                    tmprad = x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2;
                                }
                                if (tmpdeg1 < tmpdeg2)  jgraphics_arc(g, 0, -1, tmprad,  tmpdeg1, tmpdeg2);
                                else
                                {
                                    jgraphics_arc(g, 0, -1, tmprad, tmpdeg2, tmpdeg1);
                                    //jgraphics_arc_negative(g, 0, 0, tmprad, tmpdeg1, tmpdeg2);
                                }
                                
                                /*
                                if (x->f_fill_direction == 0) { // inside
                                    jgraphics_arc(g, 0, -1, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2, deg1+(0.008 * (j+4) * x->f_metersize), deg2-(0.008 * (j+4) * x->f_metersize) );
                                } else { // outside
                                    jgraphics_arc(g, 0, -1, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2, deg1+(0.008 * (x->f_numleds+3-(j)) * x->f_metersize), deg2-(0.008 * (x->f_numleds+3-(j)) * x->f_metersize) );
                                }
                                */
                            }
                            else {
                                if (x->f_fill_direction == 0) { // inside
                                    jgraphics_arc_negative(g, 0, -1, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2, deg2, deg1);
                                } else { // outside
                                    jgraphics_arc_negative(g, 0, -1, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2, deg2, deg1);
                                }
                            }
                        }
                        else { // mono
                            if (x->f_fill_direction == 0) { // inside
                                jgraphics_arc(g, 0, -1, x->f_rayonExt-(j*ledOffset)-ledMargin*2-x->f_strokeWidth*2-1,  0, JGRAPHICS_2PI);
                            } else { // outside
                                jgraphics_arc(g, 0, -1, x->f_rayonInt+(j*ledOffset)+ledMargin*2+x->f_strokeWidth*2-1,  0, JGRAPHICS_2PI);
                            }
                        }
                    }
                    
                    jgraphics_stroke(g);
                }
                
                // black
                jgraphics_set_source_jrgba(g, &ledBgColor);
                for( j=0; j < x->f_numleds; j++ )
                {
                    jgraphics_set_line_cap(g, (x->f_number_of_loudspeakers < 24 && (x->f_speakerWidth[i] > 14.5)) ? JGRAPHICS_LINE_CAP_ROUND : JGRAPHICS_LINE_CAP_BUTT);
                    if (x->f_number_of_loudspeakers > 1) {
                        if ( x->f_number_of_loudspeakers < 24  && (x->f_speakerWidth[i] > 14.5)) {
                            double tmpdeg1 = 0, tmpdeg2 = 0, tmprad = 0;
                            
                            if (x->f_fill_direction == 0) { // inside
                                tmpdeg1 = deg1+(0.008 * (j+4) * x->f_metersize);
                                tmpdeg2 = deg2-(0.008 * (j+4) * x->f_metersize);
                                tmprad = x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2;
                            } else { // outside
                                tmpdeg1 = deg1+(0.008 * (x->f_numleds+3-(j)) * x->f_metersize);
                                tmpdeg2 = deg2-(0.008 * (x->f_numleds+3-(j)) * x->f_metersize);
                                tmprad = x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2;
                            }
                            if (tmpdeg1 < tmpdeg2)  jgraphics_arc(g, 0, 0, tmprad,  tmpdeg1, tmpdeg2);
                            else
                            {
                                jgraphics_arc(g, 0, 0, tmprad, tmpdeg2, tmpdeg1);
                                //jgraphics_arc_negative(g, 0, 0, tmprad, tmpdeg1, tmpdeg2);
                            }
                            /*
                            if (x->f_fill_direction == 0) { // inside
                                jgraphics_arc(g, 0, 0, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2, deg1+(0.008 * (j+4) * x->f_metersize), deg2-(0.008 * (j+4) * x->f_metersize) );
                            } else { // outside
                                jgraphics_arc(g, 0, 0, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2, deg1+(0.008 * (x->f_numleds+3-(j)) * x->f_metersize), deg2-(0.008 * (x->f_numleds+3-(j)) * x->f_metersize) );
                            }
                            */
                        }
                        else {
                            if (x->f_fill_direction == 0) { // inside
                                jgraphics_arc_negative(g, 0, 0, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2, deg2, deg1);
                            } else { // outside
                                jgraphics_arc_negative(g, 0, 0, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2, deg2, deg1);
                            }
                        }
                    }
                    else { // mono
                        if (x->f_fill_direction == 0) { // inside
                            jgraphics_arc(g, 0, 0, x->f_rayonExt-(j*ledOffset)-ledMargin*2-x->f_strokeWidth*2,  0, JGRAPHICS_2PI);
                        } else { // outside
                            jgraphics_arc(g, 0, 0, x->f_rayonInt+(j*ledOffset)+ledMargin*2+x->f_strokeWidth*2,  0, JGRAPHICS_2PI);
                        }
                    }
                    jgraphics_stroke(g);
                }
                jgraphics_rotate(g, Tools::degToRad(-rotateAngle));
            }
        }
		jbox_end_layer((t_object*)x, view, gensym("skelton_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("skelton_layer"), 0., 0.);
}


void draw_separator(t_meter *x,  t_object *view, t_rect *rect)
{
	double deg2, rotateAngle;
    t_jrgba black, white;
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("separator_layer"), rect->width, rect->height);
    
    black = white = x->f_colorMeterBg;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
	
	if (g)
	{
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		
		// skelton separators and leds bg:
		for(int i=0; i < x->f_number_of_loudspeakers; i++)
		{
			deg2 = Tools::degToRad(90+(x->f_speakerWidth[i]));
			rotateAngle = x->f_speakerRealAngle[i] - (x->f_speakerWidth[i]*0.5) + x->f_offsetOfLoudspeakers;
            if (!x->f_speakers_dir_of_rotation) {
                rotateAngle += x->f_speakerWidth[i];
                rotateAngle *= -1;
            }
			jgraphics_rotate(g, Tools::degToRad(rotateAngle));

            // separator
			if (x->f_number_of_loudspeakers > 1) {
                jgraphics_set_line_width(g, x->f_strokeWidth);
                
                jgraphics_set_source_jrgba(g, &white);
                
                if ( Tools::isInsideDeg(rotateAngle, 45, 225) )
                {
                    jgraphics_move_to(g, -0.5, x->f_rayonInt-0.5);
                    jgraphics_line_to(g, -0.5, x->f_rayonExt-0.5);
                }
                else
                {
                    jgraphics_move_to(g, 0.5, x->f_rayonInt+0.5);
                    jgraphics_line_to(g, 0.5, x->f_rayonExt+0.5);
                }
                jgraphics_stroke(g);
                
                jgraphics_set_source_jrgba(g, &black);
				jgraphics_move_to(g, 0., x->f_rayonInt);
				jgraphics_line_to(g, 0, x->f_rayonExt);
				jgraphics_stroke(g);
			}
			
			jgraphics_rotate(g, Tools::degToRad(-rotateAngle));
		}
		
		jbox_end_layer((t_object*)x, view, gensym("separator_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("separator_layer"), 0., 0.);
}

void draw_meter(t_meter *x, t_object *view, t_rect *rect)
{
	int i, j, nbLed, tepidLimit, warmLimit, hotLimit;
	long nLoudSpeak = x->f_number_of_loudspeakers;
	double deg1, deg2, rotateAngle, ledContainerSize, ledStroke, ledMargin, ledOffset, meter_dB, min_dB_to_display;
	t_jrgba ledColor;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("meter_layer"), rect->width, rect->height);
	
	deg1 = Tools::degToRad(90);
	nbLed = x->f_numleds+1;
	ledContainerSize = x->f_rayonExt - x->f_rayonInt - (x->f_strokeWidth*4);
	ledOffset = ledContainerSize / nbLed;
    ledStroke = ledOffset * 0.50;
	ledMargin = ledOffset * 0.25;
	hotLimit = x->f_numleds - x->f_nhotleds;
	warmLimit = hotLimit - x->f_nwarmleds;
	tepidLimit = warmLimit - x->f_ntepidleds;
	min_dB_to_display = -1 * ( (x->f_numleds * x->f_dbperled) - (x->f_dbperled * 0.5) );
	
	if (g)
	{
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		
		for(i=0; i<nLoudSpeak; i++)
		{
            meter_dB = x->f_meter->getLoudspeakerEnergy(i); // dB (negatif) de -240 à 0;
			
            deg2 = Tools::degToRad(90+(x->f_speakerWidth[i]));
            rotateAngle = x->f_speakerRealAngle[i] - (x->f_speakerWidth[i]*0.5) + x->f_offsetOfLoudspeakers;
            if (!x->f_speakers_dir_of_rotation) {
                rotateAngle += x->f_speakerWidth[i];
                rotateAngle *= -1;
            }
            jgraphics_rotate(g, Tools::degToRad(rotateAngle));
            
            jgraphics_set_line_cap(g, (nLoudSpeak < 24 && (x->f_speakerWidth[i] > 14.5)) ? JGRAPHICS_LINE_CAP_ROUND : JGRAPHICS_LINE_CAP_BUTT);
            
			if ( meter_dB > min_dB_to_display ) // si on est en dessous pas la peine de dessiner
			{
				// leds :
				jgraphics_set_line_width(g, ledStroke);
				for(j=0; j<nbLed-1; j++)
				{
					if ( ( j < nbLed-1 ) && ( meter_dB > min_dB_to_display + (x->f_dbperled * j) ) )
					{
						if ( j < tepidLimit ) ledColor = x->f_colorColdSignal;
						else if ( j < warmLimit ) ledColor = x->f_colorTepidSignal;
						else if ( j < hotLimit ) ledColor = x->f_colorWarmSignal;
						else ledColor = x->f_colorHotSignal;
						
						jgraphics_set_source_jrgba(g, &ledColor);
						jgraphics_set_line_width(g, ledStroke);
						
						if (nLoudSpeak > 1) {
							if ( nLoudSpeak < 24 && (x->f_speakerWidth[i] > 14.5 ))
                            {
                                double tmpdeg1 = 0, tmpdeg2 = 0, tmprad = 0;
                                
                                if (x->f_fill_direction == 0) { // inside
                                    tmpdeg1 = deg1+(0.01 * (j+4) * x->f_metersize);
                                    tmpdeg2 = deg2-(0.01 * (j+4) * x->f_metersize);
                                    tmprad = x->f_rayonExt - (j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2;
                                } else { // outside
                                    tmpdeg1 = deg1+(0.01 * (nbLed+3-(j)) * x->f_metersize);
                                    tmpdeg2 = deg2-(0.01 * (nbLed+3-(j)) * x->f_metersize);
                                    tmprad = x->f_rayonInt + (j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2;
                                }
                                if (tmpdeg1 < tmpdeg2)  jgraphics_arc(g, 0, 0, tmprad,  tmpdeg1, tmpdeg2);
                                else
                                {
                                    jgraphics_arc(g, 0, 0, tmprad, tmpdeg2, tmpdeg1);
                                    //jgraphics_arc(g, 0, tmprad, x->f_strokeWidth*2, 0, CICM_2PI);
                                    //jgraphics_fill(g);
                                    //jgraphics_arc_negative(g, 0, 0, tmprad, tmpdeg1, tmpdeg2);
                                }
							}
							else {
                                if (x->f_fill_direction == 0) { // inside
                                    jgraphics_arc_negative(g, 0, 0, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2, deg2, deg1);
                                } else { // outside
                                    jgraphics_arc_negative(g, 0, 0, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2, deg2, deg1);
                                }
							}
						}
						else {
                            if (x->f_fill_direction == 0) { // inside
                                jgraphics_arc(g, 0, 0, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2,  0, JGRAPHICS_2PI);
                            } else { // outside
                                jgraphics_arc(g, 0, 0, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2,  0, JGRAPHICS_2PI);
                            }
						}
						jgraphics_stroke(g);
					}
					else
					{
						break;
					}
				}
			}
            
            if ( x->f_drawOverLedleftTime[i] > 0 )
            {
                jgraphics_set_source_jrgba(g, &x->f_colorOverSignal);
                jgraphics_set_line_width(g, ledStroke);
                
                if (nLoudSpeak > 1) {
                    
                    if ( nLoudSpeak < 24 && (x->f_speakerWidth[i] > 14.5 ))
                    {
                        double tmpdeg1 = 0, tmpdeg2 = 0, tmprad = 0;
                        
                        if (x->f_fill_direction == 0) { // inside
                            tmpdeg1 = deg1+(0.01 * (nbLed+1) * x->f_metersize);
                            tmpdeg2 = deg2-(0.01 * (nbLed+1) * x->f_metersize);
                            tmprad = x->f_rayonInt + ledMargin*2 + x->f_strokeWidth;
                        } else { // outside
                            tmpdeg1 = deg1+(0.008 * 3 * x->f_metersize);
                            tmpdeg2 = deg2-(0.008 * 3 * x->f_metersize);
                            tmprad = x->f_rayonExt - ledMargin*2 - x->f_strokeWidth;
                        }
                        
                        if (tmpdeg1 < tmpdeg2)  jgraphics_arc(g, 0, 0, tmprad,  tmpdeg1, tmpdeg2);
                        else jgraphics_arc_negative(g, 0, 0, tmprad,  tmpdeg1, tmpdeg2);
                    }
                    
                    else
                    {
                        if (x->f_fill_direction == 0) { // inside
                            jgraphics_arc_negative(g, 0, 0, x->f_rayonInt + ledMargin*2 + x->f_strokeWidth, deg2, deg1);
                        } else { // outside
                            jgraphics_arc_negative(g, 0, 0, x->f_rayonExt - ledMargin*2 - x->f_strokeWidth, deg2, deg1);
                        }
                    }
                }
                else {
                    if (x->f_fill_direction == 0) { // inside
                        jgraphics_arc(g, 0, 0, x->f_rayonInt + ledMargin*2,  0, JGRAPHICS_2PI);
                    } else { // outside
                        jgraphics_arc(g, 0, 0, x->f_rayonExt - ledMargin*2,  0, JGRAPHICS_2PI);
                    }
                }
                jgraphics_stroke(g);
            }
            
            jgraphics_rotate(g, Tools::degToRad(-rotateAngle));
		}
		
		jbox_end_layer((t_object*)x, view, gensym("meter_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("meter_layer"), 0., 0.);
}

void draw_vector_energy(t_meter *x, t_object *view, t_rect *rect)
{
	double angle, rayon, arrow;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("energy_vector_layer"), rect->width, rect->height);
	
	if (g)
	{
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		
		/* Energy */
		jgraphics_set_source_jrgba(g, &x->f_colorEnergy);
        
        rayon = x->f_rayonInt * 0.85;
		arrow = rayon * 0.15;
        angle = x->f_meter->getEnergyVectorAngle() + (x->f_offsetOfLoudspeakers / 180.) * JGRAPHICS_PI;
		jgraphics_rotate(g, x->f_speakers_dir_of_rotation ? angle : -angle);
		
		// arrow
		jgraphics_move_to(g, 0, 0);
		jgraphics_line_to(g, 0, rayon);
		jgraphics_rel_line_to(g, -arrow, -arrow);
		jgraphics_move_to(g, 0, rayon);
		jgraphics_rel_line_to(g, arrow, -arrow);
		jgraphics_stroke(g);
		
		/* Center */
		jgraphics_arc(g, 0, 0, 2, 0., JGRAPHICS_2PI);
		jgraphics_fill(g);
        
		jbox_end_layer((t_object*)x, view, gensym("energy_vector_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("energy_vector_layer"), 0., 0.);
}

void draw_vector_velocity(t_meter *x, t_object *view, t_rect *rect)
{
	double angle, rayon, arrow;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("velocity_vector_layer"), rect->width, rect->height);
	
	if (g)
	{
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		
		/* Velocity */
		jgraphics_set_source_jrgba(g, &x->f_colorVelocity);
        
        rayon = x->f_rayonInt * 0.85;
		arrow = rayon * 0.15;
        angle = x->f_meter->getVelocityVectorAngle() + (x->f_offsetOfLoudspeakers / 180.) * JGRAPHICS_PI;
		jgraphics_rotate(g, x->f_speakers_dir_of_rotation ? angle : -angle);
		
		// arrow
		jgraphics_move_to(g, 0, 0);
		jgraphics_line_to(g, 0, rayon);
		jgraphics_rel_line_to(g, -arrow, -arrow);
		jgraphics_move_to(g, 0, rayon);
		jgraphics_rel_line_to(g, arrow, -arrow);
		jgraphics_stroke(g);
		
		/* Center */
		jgraphics_arc(g, 0, 0, 2, 0., JGRAPHICS_2PI);
		jgraphics_fill(g);
        
		jbox_end_layer((t_object*)x, view, gensym("velocity_vector_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("velocity_vector_layer"), 0., 0.);
}

void meter_resize_inlet(t_meter *x, long lastNumberOfOutlet)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
    
    t_object *b = NULL;
	object_obex_lookup(x, gensym("#B"), (t_object **)&b);
    object_method(b, gensym("dynlet_begin"));
    
    dsp_resize((t_pxobject*)x, x->f_number_of_loudspeakers);
    object_method(b, gensym("dynlet_end"));

    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("start"));
}

