/*
 // Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

/**
 @file      hoa.3d.meter~.cpp
 @name      hoa.3d.meter~
 @realname  hoa.3d.meter~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A spherical harmonic visualizer
 
 @description
 <o>hoa.3d.meter~</o> displays spherical harmonics of an ambisonic sound field
 
 @discussion
 <o>hoa.3d.meter~</o> displays spherical harmonics of an ambisonic sound field
 
 @category ambisonics, hoa objects, audio, GUI, MSP
 
 @seealso hoa.3d.gl.scope~, hoa.2d.scope~, hoa.3d.decoder~, hoa.3d.encoder~, hoa.3d.map~, hoa.3d.optim~, hoa.3d.vector~, hoa.3d.wider~, hoa.dac~
 
 @illustration on @caption the hoa.3d.meter~ GUI object
 @palette yes
 */

#include "../Hoa3D.max.h"

#define MAX_SPEAKER 64

typedef struct  _hoa_meter_3d
{
	t_pxjbox		j_box;
    
    Hoa3D::Meter*   f_meter;
    Hoa3D::Vector*  f_vector;
    double*			f_signals;
    double			f_vector_coords[6];
    int*            f_over_leds;
    
    long            f_ramp;
	int             f_startclock;
	long            f_interval;
    
    t_symbol*       f_vector_type;
    t_symbol*       f_clockwise;
    t_symbol*       f_view;
	
    t_jrgba         f_color_bg;
    t_jrgba         f_color_bd;
	t_jrgba			f_color_off_signal;
	t_jrgba         f_color_cold_signal;
	t_jrgba         f_color_tepid_signal;
	t_jrgba         f_color_warm_signal;
	t_jrgba         f_color_hot_signal;
	t_jrgba         f_color_over_signal;
	
	t_jrgba         f_color_energy_vector;
	t_jrgba         f_color_velocity_vector;
	
    double          f_radius;
    double          f_center;
	double          f_radius_center;
    
	t_clock*        f_clock;
    void*           f_attrs;
    
} t_hoa_meter_3d;

t_class *hoa_meter_3d_class;

void *hoa_meter_3d_new(t_symbol *s, int argc, t_atom *argv);
void hoa_meter_3d_free(t_hoa_meter_3d *x);
void hoa_meter_3d_assist(t_hoa_meter_3d *x, void *b, long m, long a, char *s);

void hoa_meter_3d_dsp64(t_hoa_meter_3d *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_meter_3d_perform64(t_hoa_meter_3d *x, t_object *d, double **ins, long ni, double **outs, long no, long sf, long f,void *up);
void hoa_meter_3d_tick(t_hoa_meter_3d *x);

t_max_err hoa_meter_3d_notify(t_hoa_meter_3d *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err channels_get(t_hoa_meter_3d *x, t_object *attr, long *argc, t_atom **argv);
t_max_err channels_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_get(t_hoa_meter_3d *x, t_object *attr, long *argc, t_atom **argv);
t_max_err angles_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv);
t_max_err offset_get(t_hoa_meter_3d *x, t_object *attr, long *argc, t_atom **argv);
t_max_err offset_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv);
t_max_err vectors_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv);
t_max_err rotation_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv);
t_max_err view_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv);

void hoa_meter_3d_getdrawparams(t_hoa_meter_3d *x, t_object *patcherview, t_jboxdrawparams *params);
long hoa_meter_3d_oksize(t_hoa_meter_3d *x, t_rect *newrect);

void hoa_meter_3d_paint(t_hoa_meter_3d *x, t_object *view);
void draw_background(t_hoa_meter_3d *x, t_object *view, t_rect *rect);
void draw_leds(t_hoa_meter_3d *x,  t_object *view, t_rect *rect);
void draw_vectors(t_hoa_meter_3d *x, t_object *view, t_rect *rect);

t_hoa_err hoa_getinfos(t_hoa_meter_3d* x, t_hoa_boxinfos* boxinfos);

t_symbol* hoa_sym_3d_none = gensym("none");
t_symbol* hoa_sym_3d_energy = gensym("energy");
t_symbol* hoa_sym_3d_velocity = gensym("velocity");
t_symbol* hoa_sym_3d_both = gensym("both");
t_symbol* hoa_sym_3d_clockwise = gensym("clockwise");
t_symbol* hoa_sym_3d_anticlock = gensym("anti-clockwise");
t_symbol* hoa_sym_3d_vector_layer = gensym("vectors_layer");
t_symbol* hoa_sym_3d_leds_layer = gensym("leds_layers");
t_symbol* hoa_sym_3d_background_layer = gensym("background_layers");
t_symbol* hoa_sym_3d_top = gensym("top");
t_symbol* hoa_sym_3d_bottom = gensym("bottom");

int C74_EXPORT main()
{
	t_class *c;
	c = class_new("hoa.3d.meter~", (method)hoa_meter_3d_new, (method)hoa_meter_3d_free, (short)sizeof(t_hoa_meter_3d), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method) hoa_meter_3d_dsp64,           "dsp64",			A_CANT, 0);
	class_addmethod(c, (method) hoa_meter_3d_assist,          "assist",			A_CANT, 0);
	class_addmethod(c, (method) hoa_meter_3d_paint,           "paint",			A_CANT, 0);
	class_addmethod(c, (method) hoa_meter_3d_notify,          "notify",			A_CANT, 0);
    class_addmethod(c, (method) hoa_meter_3d_getdrawparams,   "getdrawparams",	A_CANT, 0);
    class_addmethod(c, (method) hoa_meter_3d_oksize,          "oksize",			A_CANT, 0);
	
	CLASS_ATTR_INVISIBLE            (c, "color", 0);
	CLASS_ATTR_DEFAULT              (c, "patching_rect", 0, "0 0 225 225");
	
    CLASS_ATTR_LONG                 (c, "channels", ATTR_SET_DEFER_LOW, t_hoa_meter_3d, f_attrs);
    CLASS_ATTR_ACCESSORS            (c, "channels", channels_get, channels_set);
	CLASS_ATTR_ORDER                (c, "channels", 0, "1");
	CLASS_ATTR_LABEL                (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_SAVE                 (c, "channels", 1);
    CLASS_ATTR_DEFAULT              (c, "channels", 0, "8");
	
    CLASS_ATTR_FLOAT_VARSIZE        (c, "angles", ATTR_SET_DEFER_LOW, t_hoa_meter_3d, f_attrs, f_attrs, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS            (c, "angles", angles_get, angles_set);
	CLASS_ATTR_ORDER                (c, "angles", 0, "2");
	CLASS_ATTR_LABEL                (c, "angles", 0, "Angles of Channels");
	CLASS_ATTR_SAVE                 (c, "angles", 1);
    CLASS_ATTR_DEFAULT              (c, "angles", 0, "0 45 90 45 180 45 270 45 0 -45 90 -45 180 -45 270 -45");
    
    CLASS_ATTR_FLOAT_ARRAY			(c, "offset", ATTR_SET_DEFER_LOW, t_hoa_meter_3d, f_attrs, 3);
    CLASS_ATTR_ACCESSORS            (c, "offset", offset_get, offset_set);
	CLASS_ATTR_ORDER                (c, "offset", 0, "3");
	CLASS_ATTR_LABEL                (c, "offset", 0, "Offset of Channels");
	CLASS_ATTR_DEFAULT              (c, "offset", 0, "0. 0. 0.");
	CLASS_ATTR_SAVE                 (c, "offset", 1);
	
    CLASS_ATTR_SYM					(c, "rotation", 0, t_hoa_meter_3d, f_clockwise);
    CLASS_ATTR_ACCESSORS            (c, "rotation", NULL, rotation_set);
    CLASS_ATTR_ORDER                (c, "rotation", 0, "4");
	CLASS_ATTR_LABEL                (c, "rotation", 0, "Rotation of Channels");
    CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "rotation", 0, "anti-clockwise");
    CLASS_ATTR_ENUM					(c, "rotation", 0, "anti-clockwise clockwise");
    
    CLASS_ATTR_SYM					(c, "view", 0 , t_hoa_meter_3d, f_view);
    CLASS_ATTR_ACCESSORS            (c, "view", NULL, view_set);
	CLASS_ATTR_ORDER                (c, "view", 0, "5");
	CLASS_ATTR_LABEL                (c, "view", 0, "View");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "view", 0, "top");
    CLASS_ATTR_ENUM					(c, "view", 0, "top bottom");
    
	CLASS_ATTR_SYM					(c, "vectors", 0, t_hoa_meter_3d, f_vector_type);
    CLASS_ATTR_ACCESSORS            (c, "vectors", NULL, vectors_set);
	CLASS_ATTR_ORDER                (c, "vectors", 0, "2");
    CLASS_ATTR_LABEL                (c, "vectors", 0, "Vectors");
	CLASS_ATTR_DEFAULT              (c, "vectors", 0, "Energy");
	CLASS_ATTR_SAVE                 (c, "vectors", 1);
    CLASS_ATTR_ENUM					(c, "vectors", 0, "none energy velocity both");
    
    CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_meter_3d, f_interval);
	CLASS_ATTR_ORDER                (c, "interval", 0, "5");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval (in ms)");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "50");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
    
	CLASS_STICKY_CATEGORY(c, 0, "Color");
    CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_hoa_meter_3d, f_color_bg);
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.76 0.76 0.76 1.");
	CLASS_ATTR_STYLE                (c, "bgcolor", 1, "rgba");
    
    CLASS_ATTR_RGBA					(c, "bdcolor", 0, t_hoa_meter_3d, f_color_bd);
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bdcolor", 0, "0.7 0.7 0.7 1.");
	CLASS_ATTR_STYLE                (c, "bdcolor", 1, "rgba");
    
	CLASS_ATTR_RGBA                 (c, "offcolor", 0, t_hoa_meter_3d, f_color_off_signal);
	CLASS_ATTR_LABEL                (c, "offcolor", 0, "Off Signal Color");
	CLASS_ATTR_ORDER                (c, "offcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "offcolor", 0, "0. 0. 0. 0.2");
	CLASS_ATTR_STYLE                (c, "offcolor", 1, "rgba");
	
	CLASS_ATTR_RGBA                 (c, "coldcolor", 0, t_hoa_meter_3d, f_color_cold_signal);
	CLASS_ATTR_LABEL                (c, "coldcolor", 0, "Cold Signal Color");
	CLASS_ATTR_ORDER                (c, "coldcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "coldcolor", 0, "0. 0.6 0. 0.8");
	CLASS_ATTR_STYLE                (c, "coldcolor", 1, "rgba");
    
	CLASS_ATTR_RGBA                 (c, "tepidcolor", 0, t_hoa_meter_3d, f_color_tepid_signal);
	CLASS_ATTR_LABEL                (c, "tepidcolor", 0, "Tepid Signal Color");
	CLASS_ATTR_ORDER                (c, "tepidcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "tepidcolor", 0, "0.6 0.73 0. 0.8");
	CLASS_ATTR_STYLE                (c, "tepidcolor", 1, "rgba");
    
	CLASS_ATTR_RGBA                 (c, "warmcolor", 0, t_hoa_meter_3d, f_color_warm_signal);
	CLASS_ATTR_LABEL                (c, "warmcolor", 0, "Warm Signal Color");
	CLASS_ATTR_ORDER                (c, "warmcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "warmcolor", 0, ".85 .85 0. 0.8");
	CLASS_ATTR_STYLE                (c, "warmcolor", 1, "rgba");
    
	CLASS_ATTR_RGBA                 (c, "hotcolor", 0, t_hoa_meter_3d, f_color_hot_signal);
	CLASS_ATTR_LABEL                (c, "hotcolor", 0, "Hot Signal Color");
	CLASS_ATTR_ORDER                (c, "hotcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "hotcolor", 0, "1. 0.6 0. 0.8");
	CLASS_ATTR_STYLE                (c, "hotcolor", 1, "rgba");
    
	CLASS_ATTR_RGBA                 (c, "overcolor", 0, t_hoa_meter_3d, f_color_over_signal);
	CLASS_ATTR_LABEL                (c, "overcolor", 0, "Overload Signal Color");
	CLASS_ATTR_ORDER                (c, "overcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "overcolor", 0, "1. 0. 0. 0.8");
	CLASS_ATTR_STYLE                (c, "overcolor", 1, "rgba");
    
	CLASS_ATTR_RGBA                 (c, "energycolor", 0, t_hoa_meter_3d, f_color_energy_vector);
	CLASS_ATTR_LABEL                (c, "energycolor", 0, "Energy Vector Color");
	CLASS_ATTR_ORDER                (c, "energycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "energycolor", 0, "0. 0. 1. 0.8");
    CLASS_ATTR_STYLE                (c, "energycolor", 1, "rgba");
    
    CLASS_ATTR_RGBA                 (c, "velocitycolor", 0, t_hoa_meter_3d, f_color_velocity_vector);
	CLASS_ATTR_LABEL                (c, "velocitycolor", 0, "Velocity Vector Color");
	CLASS_ATTR_ORDER                (c, "velocitycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "velocitycolor", 0, "1. 0. 0. 0.8");
    CLASS_ATTR_STYLE                (c, "velocitycolor", 1, "rgba");
	CLASS_STICKY_CATEGORY_CLEAR(c);
	
    class_register(CLASS_BOX, c);
	hoa_meter_3d_class = c;
}

void *hoa_meter_3d_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_meter_3d *x =  NULL;
	t_dictionary *d;
	long flags;
	
	if(!(d = object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_hoa_meter_3d *)object_alloc(hoa_meter_3d_class);
	flags = 0
	| JBOX_DRAWFIRSTIN
	| JBOX_DRAWINLAST
	| JBOX_DRAWBACKGROUND
	| JBOX_TRANSPARENT
	| JBOX_GROWY
	;
	
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
    
    x->f_ramp = 0;
    x->f_meter  = new Hoa3D::Meter(8);
    x->f_vector = new Hoa3D::Vector(8);
    
    x->f_signals = new double[MAX_SPEAKER * SYS_MAXBLKSIZE];
    x->f_over_leds = new int[MAX_CHANNELS];
    for(int i = 0; i < MAX_CHANNELS; i++)
        x->f_over_leds[i] = 0;
	
    x->f_clock = (t_clock*)clock_new(x,(method)hoa_meter_3d_tick);
	x->f_startclock = 0;
	
    dsp_setupjbox((t_pxjbox *)x, x->f_meter->getNumberOfChannels());

	attr_dictionary_process(x, d);
    
	jbox_ready((t_jbox *)x);
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_meter_3d* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs    = x->f_meter->getNumberOfChannels();
	boxinfos->autoconnect_outputs   = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_PLANEWAVES;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_meter_3d_getdrawparams(t_hoa_meter_3d *x, t_object *patcherview, t_jboxdrawparams *params)
{
    params->d_boxfillcolor = x->f_color_bg;
    params->d_bordercolor = x->f_color_bd;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

long hoa_meter_3d_oksize(t_hoa_meter_3d *x, t_rect *newrect)
{
    newrect->width = clip_min(newrect->width, 20.);
    newrect->height = clip_min(newrect->height, 20.);
	return 0;
}

t_max_err channels_get(t_hoa_meter_3d *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)malloc(sizeof(t_atom));
    if(argv[0] && argc[0])
    {
        atom_setlong(argv[0], x->f_meter->getNumberOfChannels());
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return MAX_ERR_NONE;
}

t_max_err channels_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_isNumber(argv))
        {
			t_object *b = NULL;
            long d = clip_minmax(atom_getlong(argv), 1, MAX_SPEAKER);
            if(d != x->f_meter->getNumberOfChannels())
            {
				object_obex_lookup(x, gensym("#B"), (t_object **)&b);
                int dspState = sys_getdspobjdspstate((t_object*)x);

				if (b)
				{
					if(dspState)
						object_method(gensym("dsp")->s_thing, hoa_sym_stop);
					
					delete x->f_meter;
					delete x->f_vector;
					x->f_meter = new Meter(d);
					x->f_vector = new Vector(d);
					
					object_method(b, hoa_sym_dynlet_begin);
					dsp_resize((t_pxobject*)x, x->f_meter->getNumberOfChannels());
					object_method(b, hoa_sym_dynlet_end);
					
					if(dspState)
						object_method(gensym("dsp")->s_thing, hoa_sym_start);
				}
            }
        }
    }
    return MAX_ERR_NONE;
}

t_max_err angles_get(t_hoa_meter_3d *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = x->f_meter->getNumberOfChannels() * 2;
    argv[0] = (t_atom *)malloc(sizeof(t_atom) * x->f_meter->getNumberOfChannels() * 2);
    if(argv[0] && argc[0])
    {
        for(int i = 0, j = 0; i < x->f_meter->getNumberOfChannels() * 2; i+=2, j++)
		{
            atom_setfloat(argv[0]+i, x->f_meter->getChannelAzimuth(j) / HOA_2PI * 360.);
			atom_setfloat(argv[0]+i+1, x->f_meter->getChannelElevation(j) / HOA_2PI * 360.);
		}
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return MAX_ERR_NONE;
}

t_max_err angles_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv)
{
    double azimuths[MAX_SPEAKER];
	double elevations[MAX_SPEAKER];
    if(argc > MAX_SPEAKER)
        argc = MAX_SPEAKER;
	
    if(argc && argv)
    {
		for(int i = 0, j = 0; i < x->f_meter->getNumberOfChannels(); i++, j+=2)
        {
            if(j < argc-1 && atom_isNumber(argv+j) && atom_isNumber(argv+j+1))
            {
                azimuths[i] = atom_getfloat(argv+j) / 360. * HOA_2PI;
				elevations[i] = atom_getfloat(argv+j+1) / 360. * HOA_2PI;
            }
			else
			{
				azimuths[i] = x->f_meter->getChannelAzimuth(i);
				elevations[i] = x->f_meter->getChannelElevation(i);
			}
        }
		x->f_meter->setChannelsPosition(azimuths, elevations);
        x->f_vector->setChannelsPosition(azimuths, elevations);
    }
	
	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_background_layer);
	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_leds_layer);
	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_vector_layer);
    
	jbox_redraw((t_jbox *)x);
    return MAX_ERR_NONE;
}

t_max_err offset_get(t_hoa_meter_3d *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = 3;
    argv[0] = (t_atom *)malloc(3 * sizeof(t_atom));
    if(argv[0] && argc[0])
    {
		// atom_setfloat(argv[0], x->f_meter->getChannelsOffset() / HOA_2PI * 360.);
		atom_setfloat(argv[0]  , 0);
		atom_setfloat(argv[0]+1, 0);
		atom_setfloat(argv[0]+2, 0);
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return MAX_ERR_NONE;
}

t_max_err offset_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv)
{
	double offsets[3];
	
	if(argc && argv && atom_isNumber(argv))
		offsets[0] = atom_getfloat(argv);
	if(argc > 1 && argv+1 && atom_isNumber(argv+1))
		offsets[1] = atom_getfloat(argv+1);
	if(argc > 2 && argv+2 && atom_isNumber(argv+2))
		offsets[2] = atom_getfloat(argv+2);
	
	// x->f_meter->setChannelsOffset(atom_getfloat(argv) / 360 * HOA_2PI);
	
	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_background_layer);
	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_leds_layer);
	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_vector_layer);
    
	jbox_redraw((t_jbox *)x);
    return 0;
}

t_max_err vectors_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == hoa_sym_3d_energy)
                x->f_vector_type = hoa_sym_3d_energy;
            else if(atom_getsym(argv) == hoa_sym_3d_velocity)
                x->f_vector_type = hoa_sym_3d_velocity;
            else if(atom_getsym(argv) == hoa_sym_3d_both)
                x->f_vector_type = hoa_sym_3d_both;
            else
                x->f_vector_type = hoa_sym_3d_none;
        }
        else if(atom_gettype(argv) == A_FLOAT)
        {
            if(atom_getlong(argv) == 1)
                x->f_vector_type = hoa_sym_3d_energy;
            else if(atom_getlong(argv) == 2)
                x->f_vector_type = hoa_sym_3d_velocity;
            else if(atom_getlong(argv) == 3)
                x->f_vector_type = hoa_sym_3d_both;
            else
                x->f_vector_type = hoa_sym_3d_none;
        }
        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_vector_layer);
    }
    return 0;
}

t_max_err rotation_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == hoa_sym_3d_clockwise)
                x->f_clockwise = hoa_sym_3d_clockwise;
            else
                x->f_clockwise = hoa_sym_3d_anticlock;
        }
        else if(atom_gettype(argv) == A_FLOAT)
        {
            if(atom_getlong(argv) == 1)
                x->f_clockwise = hoa_sym_3d_clockwise;
            else
                x->f_clockwise = hoa_sym_3d_anticlock;
        }
    }
    return 0;
}

t_max_err view_set(t_hoa_meter_3d *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == hoa_sym_3d_bottom)
                x->f_view = hoa_sym_3d_bottom;
            else
                x->f_view = hoa_sym_3d_top;
        }
        else if(atom_gettype(argv) == A_FLOAT)
        {
            if(atom_getlong(argv) == 1)
                x->f_view = hoa_sym_3d_bottom;
            else
                x->f_view = hoa_sym_3d_top;
        }
    }
    return 0;
}

void hoa_meter_3d_dsp64(t_hoa_meter_3d *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_meter->setVectorSize(maxvectorsize);
    object_method(dsp, gensym("dsp_add64"), x, (method)hoa_meter_3d_perform64, 0, NULL);
	x->f_startclock = 1;
}

void hoa_meter_3d_perform64(t_hoa_meter_3d *x, t_object *dsp, double **ins, long numins, double **outs, long no, long sampleframes, long f,void *up)
{
	for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
    for(x->f_ramp = 0; x->f_ramp < sampleframes; x->f_ramp++)
    {
        x->f_meter->process(x->f_signals + numins * x->f_ramp);
    }
    if(x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
	
}

void hoa_meter_3d_tick(t_hoa_meter_3d *x)
{
    double peak;
    
    if(x->f_vector_type == hoa_sym_3d_both)
        x->f_vector->process(x->f_signals, x->f_vector_coords);
    else if(x->f_vector_type == hoa_sym_3d_velocity)
        x->f_vector->processVelocity(x->f_signals, x->f_vector_coords);
    else if(x->f_vector_type == hoa_sym_3d_energy)
        x->f_vector->processEnergy(x->f_signals, x->f_vector_coords + 3);
    
    for (int i = 0; i < x->f_meter->getNumberOfChannels(); i++)
    {
        peak = x->f_meter->getChannelEnergy(i);
        if(peak >= 0.)
            x->f_over_leds[i] = 1000;
        else
            x->f_over_leds[i] -= x->f_interval;
        
        if(x->f_over_leds[i] < 0)
            x->f_over_leds[i] = 0;
    }
    
	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_leds_layer);
	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_vector_layer);
  	jbox_redraw((t_jbox *)x);
    
	if (sys_getdspstate())
		clock_delay(x->f_clock, x->f_interval);
}

void hoa_meter_3d_free(t_hoa_meter_3d *x)
{
	jbox_free((t_jbox *)x);
    clock_free(x->f_clock);
    delete x->f_meter;
    delete x->f_vector;
    delete [] x->f_signals;
    delete [] x->f_over_leds;
}

void hoa_meter_3d_assist(t_hoa_meter_3d *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_meter->getChannelName(a).c_str());
}

t_max_err hoa_meter_3d_notify(t_hoa_meter_3d *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("attr_modified"))
	{
		jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_background_layer);
        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_leds_layer);
        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_3d_vector_layer);
		jbox_redraw((t_jbox *)x);
	}
	return 0;
}

void hoa_meter_3d_paint(t_hoa_meter_3d *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	
    x->f_center = rect.width * .5;
	x->f_radius = x->f_center * 0.95;
	x->f_radius_center = x->f_radius / 5.;
	
	draw_background(x, view, &rect);
    draw_leds(x, view, &rect);
    draw_vectors(x, view, &rect);
}

t_jrgba rgba_addContrast(t_jrgba color, float contrast)
{
    t_jrgba new_color = color;
    new_color.red = clip_minmax(new_color.red += contrast, 0., 1.);
    new_color.green = clip_minmax(new_color.green += contrast, 0., 1.);
    new_color.blue = clip_minmax(new_color.blue += contrast, 0., 1.);
    return new_color;
}

void draw_background(t_hoa_meter_3d *x,  t_object *view, t_rect *rect)
{
    t_jrgba black, white;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, hoa_sym_3d_background_layer, rect->width, rect->height);
    
    black = rgba_addContrast(x->f_color_bg, -0.14);
    white = rgba_addContrast(x->f_color_bg, 0.06);
    
	if (g)
	{
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, rect->width * .5, rect->width * .5);
        jgraphics_set_matrix(g, &transform);
		jgraphics_set_line_width(g, 1.);
		
        jgraphics_set_source_jrgba(g, &white);
        jgraphics_arc(g, 1, 1, x->f_radius,  0., HOA_2PI);
        jgraphics_stroke(g);
        
        jgraphics_set_source_jrgba(g, &black);
        jgraphics_arc(g, 0.f, 0.f, x->f_radius,  0., HOA_2PI);
        jgraphics_stroke(g);
        
		jbox_end_layer((t_object*)x, view, hoa_sym_3d_background_layer);
	}
	jbox_paint_layer((t_object *)x, view, hoa_sym_3d_background_layer, 0., 0.);
}

void draw_leds(t_hoa_meter_3d *x, t_object *view, t_rect *rect)
{
    t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, hoa_sym_3d_leds_layer, rect->width, rect->height);
    t_jrgba mcolor;
    bool viewd = 1;
    if(x->f_view == hoa_sym_3d_bottom)
        viewd = 0;
	if (g)
	{
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, rect->width * .5, rect->width * .5);
        jgraphics_set_matrix(g, &transform);
        
		for(int i = 0; i < x->f_meter->getNumberOfChannels(); i++)
		{
            if(x->f_over_leds[i])
				mcolor = x->f_color_over_signal;
			else if (x->f_meter->getChannelEnergy(i) < -50)
				mcolor = x->f_color_off_signal;
            else if(x->f_meter->getChannelEnergy(i) < -25.5)
                mcolor = x->f_color_cold_signal;
            else if(x->f_meter->getChannelEnergy(i) >= -25.5 && x->f_meter->getChannelEnergy(i) < -16.5)
                mcolor = x->f_color_tepid_signal;
            else if(x->f_meter->getChannelEnergy(i) >= -16.5 && x->f_meter->getChannelEnergy(i) < -7.5)
                mcolor = x->f_color_warm_signal;
            else
                mcolor = x->f_color_hot_signal;
            
            jgraphics_set_source_jrgba(g, &mcolor);
            int npt = x->f_meter->getChannelNumberOfPoints(i, viewd);
            int factor = clip_min(rect->width / (double)(npt * 0.1) - 1, 1);
			
			if(npt)
			{
				float azi = x->f_meter->getChannelPointAzimuth(i, 0, viewd);
                if(x->f_clockwise == hoa_sym_3d_clockwise)
                    azi = -azi;
				float ele = x->f_meter->getChannelPointElevation(i, 0, viewd);
				float abs = abscissa(x->f_radius, azi, ele);
				float ord = ordinate(x->f_radius, azi, ele);
				jgraphics_move_to(g, abs, ord);
				
				for(int j = factor; j < npt; j += factor)
				{
					azi = x->f_meter->getChannelPointAzimuth(i, j, viewd);
                    if(x->f_clockwise == hoa_sym_3d_clockwise)
                        azi =-azi;
                    
					ele = x->f_meter->getChannelPointElevation(i, j, viewd);
					abs = abscissa(x->f_radius, azi, ele);
					ord = ordinate(x->f_radius, azi, ele);
					jgraphics_line_to(g, abs, ord);
				}
				
				for(int j = factor; j < npt; j += factor)
				{
					azi = x->f_meter->getChannelPointAzimuth(i, j, viewd);
                    if(x->f_clockwise == hoa_sym_3d_clockwise)
                        azi =-azi;
                    
					ele = x->f_meter->getChannelPointElevation(i, j, viewd);
					abs = abscissa(x->f_radius, azi, ele);
					ord = ordinate(x->f_radius, azi, ele);
					jgraphics_line_to(g, abs, ord);
				}
				
				jgraphics_close_path(g);
				jgraphics_fill_preserve(g);
				
				jgraphics_set_source_jrgba(g, &x->f_color_bd);
				jgraphics_set_line_width(g, 1);
				jgraphics_stroke(g);
			}
			
		}
		jbox_end_layer((t_object*)x, view, hoa_sym_3d_leds_layer);
	}
	jbox_paint_layer((t_object *)x, view, hoa_sym_3d_leds_layer, 0., 0.);
}

void draw_vectors(t_hoa_meter_3d *x, t_object *view, t_rect *rect)
{
	double x1, y1, size;
	t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, hoa_sym_3d_vector_layer, rect->width, rect->height);
	
	if (g)
	{
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, rect->width / 2., rect->width / 2.);
		jgraphics_set_matrix(g, &transform);
		size = 1. / 64. * rect->width;
        
        if(x->f_vector_type == hoa_sym_3d_both || x->f_vector_type == hoa_sym_3d_energy)
        {
            jgraphics_set_source_jrgba(g, &x->f_color_energy_vector);
            if(x->f_clockwise == hoa_sym_3d_anticlock)
            {
                x1 = x->f_vector_coords[3] * x->f_radius * 0.85;
                y1 = x->f_vector_coords[4] * x->f_radius * 0.85;
            }
            else
            {
                double rad = radius(x->f_vector_coords[3], x->f_vector_coords[4]) * x->f_radius * 0.85;
                double ang = -azimuth(x->f_vector_coords[3], x->f_vector_coords[4]);
                x1 = abscissa(rad, ang);
                y1 = ordinate(rad, ang);
            }
            jgraphics_arc(g, x1, y1, size, 0., HOA_2PI);
            jgraphics_fill(g);
		}
        if(x->f_vector_type == hoa_sym_3d_both || x->f_vector_type == hoa_sym_3d_velocity)
        {
            jgraphics_set_source_jrgba(g, &x->f_color_velocity_vector);
            if(x->f_clockwise == hoa_sym_3d_anticlock)
            {
                x1 = x->f_vector_coords[0] * x->f_radius * 0.85;
                y1 = x->f_vector_coords[1] * x->f_radius * 0.85;
            }
            else
            {
                double rad = radius(x->f_vector_coords[0], x->f_vector_coords[1]) * x->f_radius * 0.85;
                double ang = -azimuth(x->f_vector_coords[0], x->f_vector_coords[1]);
                x1 = abscissa(rad, ang);
                y1 = ordinate(rad, ang);
            }
            jgraphics_arc(g, x1, y1, size, 0., HOA_2PI);
            jgraphics_fill(g);
		}
        jbox_end_layer((t_object*)x, view, hoa_sym_3d_vector_layer);
	}
	jbox_paint_layer((t_object *)x, view, hoa_sym_3d_vector_layer, 0., 0.);
}