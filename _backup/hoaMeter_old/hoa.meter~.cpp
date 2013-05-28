/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#include "AmbisonicsMeter.h"

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

#define MAX_SPEAKER 256
#define DEF_SPEAKER 8

typedef struct  _meter
{
	t_pxjbox	j_box;
	
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
	
	float		f_angles_of_loudspeakers[MAX_SPEAKER];
	
	float		f_speakerRealAngle[MAX_SPEAKER];
	float		f_speakerWidth[MAX_SPEAKER];
	double		f_amplitudeOfLoudspeakers[MAX_SPEAKER];
	double		f_energyOfLoudspeakers[MAX_SPEAKER];
	double		f_abscisseOfLoudspeakers[MAX_SPEAKER];
	double		f_ordonneOfLoudspeakers[MAX_SPEAKER];
	double		f_energyVectorX;
	double		f_energyVectorY;
	
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
	t_atom_long         f_energy;
	double              f_metersize;
    t_atom_long         f_speakers_dir_of_rotation;
    t_atom_long         f_fill_direction;
	
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

t_max_err meter_notify(t_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err number_of_loudspeakers_set(t_meter *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_of_loudspeakers_set(t_meter *x, void *attr, long ac, t_atom *av);

void meter_resize_inlet(t_meter *x, long lastNumberOfOutlet);

/* Paint ------------------------------------- */
void meter_paint(t_meter *x, t_object *view);
void draw_background(t_meter *x, t_object *view, t_rect *rect);
void draw_meter(t_meter *x,  t_object *view, t_rect *rect);
void draw_vector(t_meter *x, t_object *view, t_rect *rect);
void draw_angle(t_meter *x,  t_object *view, t_rect *rect);
void draw_skelton(t_meter *x,  t_object *view, t_rect *rect);

int C74_EXPORT main()
{
	t_class *c;
    
	c = class_new("hoa.meter~", (method)meter_new, (method)meter_free, (short)sizeof(t_meter), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);
	
	class_addmethod(c, (method)meter_dsp64,			"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)meter_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)meter_paint,			"paint",		A_CANT,	0);
	class_addmethod(c, (method)meter_notify,		"notify",		A_CANT, 0);
    
	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 225 225");
    
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	
	/* APPEARANCE */
	CLASS_ATTR_LONG				(c, "leds_bg", 0, t_meter, f_leds_bg);
	CLASS_ATTR_CATEGORY			(c, "leds_bg", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "leds_bg", 0, "1");
	CLASS_ATTR_STYLE_LABEL		(c, "leds_bg", 0, "onoff", "Draw Leds Background");
	CLASS_ATTR_DEFAULT			(c, "leds_bg", 0, "1");
	CLASS_ATTR_SAVE				(c, "leds_bg", 1);
	
	CLASS_ATTR_LONG				(c, "energy", 0, t_meter, f_energy);
	CLASS_ATTR_CATEGORY			(c, "energy", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "energy", 0, "2");
	CLASS_ATTR_STYLE_LABEL		(c, "energy", 0, "onoff", "Draw Energy Vector");
	CLASS_ATTR_DEFAULT			(c, "energy", 0, "1");
	CLASS_ATTR_SAVE				(c, "energy", 1);
	
	CLASS_ATTR_DOUBLE			(c, "metersize", 0, t_meter, f_metersize);
	CLASS_ATTR_CATEGORY			(c, "metersize", 0, "Appearance");
	CLASS_ATTR_ORDER			(c, "metersize", 0, "3");
	CLASS_ATTR_LABEL			(c, "metersize", 0, "Meter Circle Size");
	CLASS_ATTR_FILTER_CLIP		(c, "metersize", 0., 1);
	CLASS_ATTR_DEFAULT			(c, "metersize", 0, "0.8");
	CLASS_ATTR_SAVE				(c, "metersize", 1);
    
    CLASS_ATTR_LONG				(c,"fill_dir", 0, t_meter, f_fill_direction);
	CLASS_ATTR_LABEL			(c,"fill_dir", 0, "Meter Fill Direction");
	CLASS_ATTR_CATEGORY			(c,"fill_dir", 0, "Appearance");
	CLASS_ATTR_ENUMINDEX		(c,"fill_dir", 0, "inside outside");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"fill_dir",0, "0");
	
	/* BEHAVIOR */
	CLASS_ATTR_LONG				(c, "ls", 0 , t_meter, f_number_of_loudspeakers);
    CLASS_ATTR_ACCESSORS		(c, "ls", NULL, number_of_loudspeakers_set);
	CLASS_ATTR_CATEGORY			(c, "ls", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "ls", 0, "1");
	CLASS_ATTR_LABEL			(c, "ls", 0, "Number of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "ls", 1);
    CLASS_ATTR_DEFAULT          (c, "ls", 0, "8");
	CLASS_ATTR_ALIAS            (c, "ls", "loudspeakers");
    CLASS_ATTR_ALIAS            (c, "ls", "channels");
    
	CLASS_ATTR_FLOAT_VARSIZE	(c, "ls_angles", 0, t_meter,f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS		(c, "ls_angles", NULL, angles_of_loudspeakers_set);
	CLASS_ATTR_CATEGORY			(c, "ls_angles", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "ls_angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "ls_angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "ls_angles", 1);
	CLASS_ATTR_ALIAS            (c, "ls_angles", "angles");
    
	CLASS_ATTR_DOUBLE			(c, "offset", 0, t_meter, f_offsetOfLoudspeakers);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "offset", 0, "3");
	CLASS_ATTR_LABEL			(c, "offset", 0, "Offset of Loudspeakers");
	CLASS_ATTR_DEFAULT			(c, "offset", 0, "0");
	CLASS_ATTR_SAVE				(c, "offset", 1);
    
    CLASS_ATTR_LONG				(c,"ls_rot_dir", 0, t_meter, f_speakers_dir_of_rotation);
	CLASS_ATTR_LABEL			(c,"ls_rot_dir", 0, "Direction of Loudspeakers Rotation");
	CLASS_ATTR_CATEGORY			(c,"ls_rot_dir", 0, "Behavior");
	CLASS_ATTR_ENUMINDEX		(c,"ls_rot_dir", 0, "clockwise anti-clockwise");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"ls_rot_dir",0, "1");
	
    /* VALUE */
	CLASS_ATTR_LONG				(c, "dbperled", 0, t_meter, f_dbperled);
	CLASS_ATTR_CATEGORY			(c, "dbperled", 0, "Value");
	CLASS_ATTR_ORDER			(c, "dbperled", 0, "4");
	CLASS_ATTR_LABEL			(c, "dbperled", 0, "DeciBels per Led");
	CLASS_ATTR_FILTER_CLIP		(c, "dbperled", 1, 12);
	CLASS_ATTR_DEFAULT			(c, "dbperled", 0, "3");
	CLASS_ATTR_SAVE				(c, "dbperled", 1);
	
	CLASS_ATTR_LONG				(c, "nhotleds", 0, t_meter, f_nhotleds);
	CLASS_ATTR_CATEGORY			(c, "nhotleds", 0, "Value");
	CLASS_ATTR_ORDER			(c, "nhotleds", 0, "5");
	CLASS_ATTR_LABEL			(c, "nhotleds", 0, "Number of Hot Leds");
	CLASS_ATTR_FILTER_CLIP		(c, "nhotleds", 0, 20);
	CLASS_ATTR_DEFAULT			(c, "nhotleds", 0, "3");
	CLASS_ATTR_SAVE				(c, "nhotleds", 1);
	
	CLASS_ATTR_LONG				(c, "ntepidleds", 0, t_meter, f_ntepidleds);
	CLASS_ATTR_CATEGORY			(c, "ntepidleds", 0, "Value");
	CLASS_ATTR_ORDER			(c, "ntepidleds", 0, "6");
	CLASS_ATTR_LABEL			(c, "ntepidleds", 0, "Number of Tepid Leds");
	CLASS_ATTR_FILTER_CLIP		(c, "ntepidleds", 0, 20);
	CLASS_ATTR_DEFAULT			(c, "ntepidleds", 0, "3");
	CLASS_ATTR_SAVE				(c, "ntepidleds", 1);
	
	CLASS_ATTR_LONG				(c, "nwarmleds", 0, t_meter, f_nwarmleds);
	CLASS_ATTR_CATEGORY			(c, "nwarmleds", 0, "Value");
	CLASS_ATTR_ORDER			(c, "nwarmleds", 0, "7");
	CLASS_ATTR_LABEL			(c, "nwarmleds", 0, "Number of Warm Leds");
	CLASS_ATTR_FILTER_CLIP		(c, "nwarmleds", 0, 20);
	CLASS_ATTR_DEFAULT			(c, "nwarmleds", 0, "3");
	CLASS_ATTR_SAVE				(c, "nwarmleds", 1);
	
	CLASS_ATTR_LONG				(c, "numleds", 0, t_meter, f_numleds);
	CLASS_ATTR_CATEGORY			(c, "numleds", 0, "Value");
	CLASS_ATTR_ORDER			(c, "numleds", 0, "8");
	CLASS_ATTR_LABEL			(c, "numleds", 0, "Total Number of Leds");
	CLASS_ATTR_FILTER_CLIP		(c, "numleds", 10, 20);
	CLASS_ATTR_DEFAULT			(c, "numleds", 0, "12");
	CLASS_ATTR_SAVE				(c, "numleds", 1);
	
	CLASS_ATTR_LONG				(c, "interval", 0, t_meter, f_interval);
	CLASS_ATTR_CATEGORY			(c, "interval", 0, "Value");
	CLASS_ATTR_ORDER			(c, "interval", 0, "9");
	CLASS_ATTR_LABEL			(c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN		(c, "interval", 20);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "50");
	CLASS_ATTR_SAVE				(c, "interval", 1);
	
	/* COLORS */
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_meter, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.55 0.55 0.55 1.");
	
	CLASS_ATTR_RGBA				(c, "mbgcolor", 0, t_meter, f_colorMeterBg);
	CLASS_ATTR_CATEGORY			(c, "mbgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "mbgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "mbgcolor", 0, "Meter Background Color");
	CLASS_ATTR_ORDER			(c, "mbgcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "mbgcolor", 0, "0.4 0.4 0.4 1.");
	
	CLASS_ATTR_RGBA				(c, "bordercolor", 0, t_meter, f_colorBorder);
	CLASS_ATTR_CATEGORY			(c, "bordercolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bordercolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bordercolor", 0, "Box Border Color");
	CLASS_ATTR_ORDER			(c, "bordercolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bordercolor", 0, "0.25 0.25 0.25 1");
	
	CLASS_ATTR_RGBA				(c, "mbordercolor", 0, t_meter, f_colorMeterBorder);
	CLASS_ATTR_CATEGORY			(c, "mbordercolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "mbordercolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "mbordercolor", 0, "Meter Border Color");
	CLASS_ATTR_ORDER			(c, "mbordercolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "mbordercolor", 0, "0.25 0.25 0.25 1");
	
	CLASS_ATTR_RGBA				(c, "coldcolor", 0, t_meter, f_colorColdSignal);
	CLASS_ATTR_CATEGORY			(c, "coldcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "coldcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "coldcolor", 0, "Cold Signal Color");
	CLASS_ATTR_ORDER			(c, "coldcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "coldcolor", 0, "0. 0.6 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "tepidcolor", 0, t_meter, f_colorTepidSignal);
	CLASS_ATTR_CATEGORY			(c, "tepidcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "tepidcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "tepidcolor", 0, "Tepid Signal Color");
	CLASS_ATTR_ORDER			(c, "tepidcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "tepidcolor", 0, "0.6 0.73 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "warmcolor", 0, t_meter, f_colorWarmSignal);
	CLASS_ATTR_CATEGORY			(c, "warmcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "warmcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "warmcolor", 0, "Warm Signal Color");
	CLASS_ATTR_ORDER			(c, "warmcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "warmcolor", 0, ".85 .85 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "hotcolor", 0, t_meter, f_colorHotSignal);
	CLASS_ATTR_CATEGORY			(c, "hotcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "hotcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "hotcolor", 0, "Hot Signal Color");
	CLASS_ATTR_ORDER			(c, "hotcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "hotcolor", 0, "1. 0.6 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "overcolor", 0, t_meter, f_colorOverSignal);
	CLASS_ATTR_CATEGORY			(c, "overcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "overcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "overcolor", 0, "Overload Signal Color");
	CLASS_ATTR_ORDER			(c, "overcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "overcolor", 0, "1. 0. 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "energycolor", 0, t_meter, f_colorEnergy);
	CLASS_ATTR_CATEGORY			(c, "energycolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "energycolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "energycolor", 0, "Energy Vector Color");
	CLASS_ATTR_ORDER			(c, "energycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "energycolor", 0, "0. 0. 1. 0.8");
	
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
	
	if(argc && argv)
    {
        if(atom_gettype(argv) == A_LONG)
            x->f_number_of_loudspeakers = atom_getlong(argv);
        else if(atom_gettype(argv) == A_FLOAT)
            x->f_number_of_loudspeakers = atom_getfloat(argv);
    }
    
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
    
	dsp_setupjbox((t_pxjbox *)x, x->f_number_of_loudspeakers);
	
	attr_dictionary_process(x, d);
	
	x->f_clock = clock_new(x,(method)meter_tick);
	x->f_startclock = 0;
	
	jbox_ready((t_jbox *)x);
	
	return (x);
}

t_max_err number_of_loudspeakers_set(t_meter *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        int dspState = sys_getdspobjdspstate((t_object*)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        long numOutlet = x->f_number_of_loudspeakers;
        
        if(atom_gettype(argv) == A_LONG)
            x->f_number_of_loudspeakers = atom_getlong(argv);
        else if(atom_gettype(argv) == A_FLOAT)
            x->f_number_of_loudspeakers = atom_getfloat(argv);
        x->f_number_of_loudspeakers = Tools::clip((long)x->f_number_of_loudspeakers, (long)1, long(MAX_SPEAKER));
        
        if (x->f_number_of_loudspeakers == 1)
        {
            object_attr_addattr_parse((t_object*)x, "ls_angles", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "offset", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "ls_rot_dir", "invisible", USESYM(long), 1, "1");
        }
        else
        {
            object_attr_addattr_parse((t_object*)x, "ls_angles", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "offset", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "ls_rot_dir", "invisible", USESYM(long), 1, "0");
        }
        
        meter_resize_inlet(x, numOutlet);
        
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("start"));
        
        for(int i = 0; i < x->f_number_of_loudspeakers; i++)
        {
            x->f_angles_of_loudspeakers[i] = ((double)i / (double)x->f_number_of_loudspeakers) * 360.;
        }
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
            if(atom_gettype(av+i) == A_FLOAT)
                x->f_angles_of_loudspeakers[i] = atom_getfloat(av + i);
            else if(atom_gettype(av+i) == A_LONG)
                x->f_angles_of_loudspeakers[i] = atom_getlong(av + i);
        }
    }

	Tools::sortVector(x->f_angles_of_loudspeakers, x->f_number_of_loudspeakers);
    
    for(int i = 0; i < x->f_number_of_loudspeakers; i++)
    {
        x->f_energyOfLoudspeakers[i] = -90.;
        x->f_amplitudeOfLoudspeakers[i] = 0.000001;
        x->f_abscisseOfLoudspeakers[i] = cos(Tools::degToRad(x->f_angles_of_loudspeakers[i]));
        x->f_ordonneOfLoudspeakers[i] = sin(Tools::degToRad(x->f_angles_of_loudspeakers[i]));
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
		
		prevPortion = (curAngle - prevAngle);
		nextPortion = (nextAngle - curAngle);
		
		if (nextPortion < 0.) nextPortion += 360.;
		if (prevPortion < 0.) prevPortion += 360.;
		
		x->f_speakerWidth[i] = (prevPortion + nextPortion)*0.5;

		x->f_speakerRealAngle[i] = (curAngle - prevPortion*0.5) + x->f_speakerWidth[i]*0.5;
		x->f_abscisseOfLoudspeakers[i] = cos(Tools::degToRad(x->f_speakerRealAngle[i]));
		x->f_ordonneOfLoudspeakers[i] = sin(Tools::degToRad(x->f_speakerRealAngle[i]));
	}
    
	jbox_invalidate_layer((t_object *)x, NULL, gensym("skelton_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("vector_layer"));
	jbox_redraw((t_jbox *)x);
    return MAX_ERR_NONE;
}

void meter_dsp64(t_meter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, meter_perform64, 0, NULL);
	x->f_startclock = 1;
}

void meter_perform64(t_meter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i, j;
	double max;
	
	for(i = 0; i < x->f_number_of_loudspeakers; i++)
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
}

void meter_tick(t_meter *x)
{
	int i;
	double sum = 0., square = 0.;
	
	x->f_energyVectorX = x->f_energyVectorY = 0.;
	for(i = 0; i < x->f_number_of_loudspeakers; i++)
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
	jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

void meter_free(t_meter *x)
{
	dsp_freejbox((t_pxjbox *)x);
	freeobject((t_object *)x->f_clock);
	jbox_free((t_jbox *)x);
}

void meter_assist(t_meter *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		sprintf(s,"(Signal) Channel %ld", a);
	}
}

t_max_err meter_notify(t_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("bgcolor") || name == gensym("bordercolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
		else if(name == gensym("mbgcolor") || name == gensym("leds_bg") || name == gensym("mbordercolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("skelton_layer"));
		}
		else if(name == gensym("cicolor") || name == gensym("coldcolor") || name == gensym("tepidcolor") || name == gensym("warmcolor") || name == gensym("hotcolor") || name == gensym("overcolor") || name == gensym("numleds"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("skelton_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
		}
		else if(name == gensym("energycolor") || name == gensym("energy"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("vector_layer"));
		}
		else if(name == gensym("offset") || name == gensym("metersize") || name == gensym("ls_rot_dir") || name == gensym("fill_dir"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("skelton_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("meter_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("vector_layer"));
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
	
	x->f_center.x = rect.width * .5;
	x->f_center.y = rect.height * .5;
	
	x->f_rayonMax = rect.width * .5;
	if(rect.width > rect.height)
		x->f_rayonMax = rect.height * .5;
	
	x->f_fontsize = (x->f_rayonMax / 14.) - 1.;
	x->f_rayonCircle = x->f_rayonMax / 32;
	
	x->f_strokeWidth = 2;
	x->f_rayonExt = x->f_rayonMax - (x->f_strokeWidth*0.5) - 2;
	x->f_rayonInt = x->f_rayonExt*(1 - x->f_metersize);
	
	draw_background(x, view, &rect);
	draw_skelton(x, view, &rect);
    draw_meter(x, view, &rect);
	
	if (x->f_energy)
    {
		draw_vector(x, view, &rect);
	}
}

void draw_background(t_meter *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
	
	if (g)
	{
		/* Background */
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_rectangle_rounded(g, 0, 0, rect->width, rect->height, 8, 8);
		jgraphics_fill(g);
		jgraphics_set_line_width(g, 1);
		jgraphics_set_source_jrgba(g, &x->f_colorBorder);
		jgraphics_rectangle_rounded(g, 0.5, 0.5, rect->width-1, rect->height-1, 8, 8);
		jgraphics_stroke(g);
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_skelton(t_meter *x,  t_object *view, t_rect *rect)
{
	int i,j;
	long nLoudSpeak = x->f_number_of_loudspeakers;
	double deg1, deg2, rotateAngle, ledContainerSize, ledStroke, ledMargin, ledOffset;
	t_pt center = x->f_center;
	t_jrgba ledBgColor = {0,0,0,0.05};
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("skelton_layer"), rect->width, rect->height);
	
	deg1 = Tools::degToRad(90);
	ledContainerSize = x->f_rayonExt - x->f_rayonInt - (x->f_strokeWidth*4);
	ledOffset = ledContainerSize / (x->f_numleds+1);
	ledStroke = ledOffset * 0.75;
	ledMargin = ledOffset * 0.25;
	
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
		jgraphics_set_source_jrgba(g, &x->f_colorMeterBorder);
		jgraphics_set_line_width(g, x->f_strokeWidth);
		jgraphics_arc(g, center.x, center.y, x->f_rayonExt,  0., JGRAPHICS_2PI);
		jgraphics_stroke(g);
		jgraphics_arc(g, center.x, center.y, x->f_rayonInt,  0., JGRAPHICS_2PI);
		jgraphics_stroke(g);
		
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		
		// skelton separators and leds bg:
		for(i=0; i<nLoudSpeak; i++)
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
				jgraphics_set_source_jrgba(g, &x->f_colorMeterBorder);
				jgraphics_set_line_width(g, x->f_strokeWidth);
				jgraphics_move_to(g, 0., x->f_rayonInt);
				jgraphics_line_to(g, 0, x->f_rayonExt);
				jgraphics_stroke(g);
			}
			
			if (x->f_leds_bg) {
				// leds Background :
				jgraphics_set_line_width(g, ledStroke);
				jgraphics_set_source_jrgba(g, &ledBgColor);
				for( j=0; j < x->f_numleds; j++ )
				{
					if (x->f_number_of_loudspeakers > 1) {
						if ( x->f_number_of_loudspeakers < 24  && (x->f_speakerWidth[i] > 14.5)) {
                            if (x->f_fill_direction == 0) { // inside
                                jgraphics_arc(g, 0, 0, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2, deg1+(0.008 * (j+1) * x->f_metersize), deg2-(0.008 * (j+1) * x->f_metersize) );
                            } else { // outside
                                jgraphics_arc(g, 0, 0, x->f_rayonInt+(j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2, deg1+(0.008 * (x->f_numleds-(j+1)) * x->f_metersize), deg2-(0.008 * (x->f_numleds-(j+1)) * x->f_metersize) );
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
					else { // mono
                        if (x->f_fill_direction == 0) { // inside
                            jgraphics_arc(g, 0, 0, x->f_rayonExt-(j*ledOffset)-ledMargin*2-x->f_strokeWidth*2,  0, JGRAPHICS_2PI);
                        } else { // outside
                            jgraphics_arc(g, 0, 0, x->f_rayonInt+(j*ledOffset)+ledMargin*2+x->f_strokeWidth*2,  0, JGRAPHICS_2PI);
                        }
					}
					jgraphics_stroke(g);
				}
			}
			
			jgraphics_rotate(g, Tools::degToRad(-rotateAngle));
		}
		
		jbox_end_layer((t_object*)x, view, gensym("skelton_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("skelton_layer"), 0., 0.);
}

void draw_meter(t_meter *x, t_object *view, t_rect *rect)
{
	int i, j, nbLed, tepidLimit, warmLimit, hotLimit, drawOverLed;
	long nLoudSpeak = x->f_number_of_loudspeakers;
	double deg1, deg2, rotateAngle, ledContainerSize, ledStroke, ledMargin, ledOffset, meter_dB, min_dB_to_display;
	t_jrgba ledColor;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("meter_layer"), rect->width, rect->height);
	
	deg1 = Tools::degToRad(90);
	nbLed = x->f_numleds+1;
	ledContainerSize = x->f_rayonExt - x->f_rayonInt - (x->f_strokeWidth*4);
	ledOffset = ledContainerSize / nbLed;
	ledStroke = ledOffset * 0.75;
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
			meter_dB = x->f_energyOfLoudspeakers[i]; // dB (negatif) de -240 à 0;
			if ( meter_dB >= 0. ) drawOverLed = 1;
			else drawOverLed = 0;
			
			if ( meter_dB > min_dB_to_display ) // si on est en dessous pas la peine de dessiner
			{
				deg2 = Tools::degToRad(90+(x->f_speakerWidth[i]));
                rotateAngle = x->f_speakerRealAngle[i] - (x->f_speakerWidth[i]*0.5) + x->f_offsetOfLoudspeakers;
                if (!x->f_speakers_dir_of_rotation) {
                    rotateAngle += x->f_speakerWidth[i];
                    rotateAngle *= -1;
                }
				jgraphics_rotate(g, Tools::degToRad(rotateAngle));
				
				// leds :
				jgraphics_set_line_width(g, ledStroke);
				for(j=0; j<nbLed; j++)
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
							if ( nLoudSpeak < 24 && (x->f_speakerWidth[i] > 14.5)) {
                                if (x->f_fill_direction == 0) { // inside
                                    jgraphics_arc(g, 0, 0, x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2,  deg1+(0.008 * (j+1) * x->f_metersize), deg2-(0.008 * (j+1) * x->f_metersize));
                                } else { // outside
                                    jgraphics_arc(g, 0, 0, x->f_rayonInt + (j*ledOffset) + ledMargin*2 + x->f_strokeWidth*2,  deg1+(0.008 * (nbLed-(j+1)) * x->f_metersize), deg2-(0.008 * (nbLed-(j+1)) * x->f_metersize));
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
					else if ( drawOverLed )
					{
						jgraphics_set_source_jrgba(g, &x->f_colorOverSignal);
						jgraphics_set_line_width(g, ledStroke);
						
						if (nLoudSpeak > 1) {
							if ( nLoudSpeak < 24  && (x->f_speakerWidth[i] > 15)) {
                                if (x->f_fill_direction == 0) { // inside
                                    jgraphics_arc(g, 0, 0, x->f_rayonInt + ledMargin*2 + x->f_strokeWidth,  deg1+(0.005 * j * x->f_metersize), deg2-(0.005 * j * x->f_metersize));
                                } else { // outside
                                    jgraphics_arc(g, 0, 0, x->f_rayonExt - ledMargin*2 - x->f_strokeWidth,  deg1+(0.008 * (nbLed-(j+1)) * x->f_metersize), deg2-(0.008 * (nbLed-(j+1)) * x->f_metersize));
                                }
							}
							else {
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
					else
					{
						break;
					}
					
				}
				jgraphics_rotate(g, Tools::degToRad(-rotateAngle));
			}
		}
		
		jbox_end_layer((t_object*)x, view, gensym("meter_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("meter_layer"), 0., 0.);
}

void draw_vector(t_meter *x, t_object *view, t_rect *rect)
{
	double angle, rayon, value, arrow;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("vector_layer"), rect->width, rect->height);
	
	if (g)
	{
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		
		/* Energy */
		jgraphics_set_source_jrgba(g, &x->f_colorEnergy);
		if (x->f_energyVectorX == 0.)
			value = 0.;
		else
			value = atan2(x->f_energyVectorY, x->f_energyVectorX);
		
		angle = value + (x->f_offsetOfLoudspeakers / 180.) * JGRAPHICS_PI;
		rayon = x->f_rayonInt * 0.85;
		arrow = rayon * 0.15;
        if (!x->f_speakers_dir_of_rotation)
            angle *= -1;
		jgraphics_rotate(g, angle);
		
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
        
		jbox_end_layer((t_object*)x, view, gensym("vector_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("vector_layer"), 0., 0.);
}

void meter_resize_inlet(t_meter *x, long lastNumberOfOutlet)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
    
    t_object *b = NULL;
    object_obex_lookup(x, _sym_pound_B, (t_object **)&b);
    object_method(b, gensym("dynlet_begin"));
    
    dsp_resize((t_pxobject*)x, x->f_number_of_loudspeakers);
    object_method(b, gensym("dynlet_end"));

    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("start"));
}

