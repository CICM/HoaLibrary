/*
 // Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "Hoa2D.pd.h"

#define MAX_SPEAKER 64

typedef struct  _hoa_meter
{
	t_edspbox   j_box;
    
    Hoa2D::Meter*   f_meter;
    Hoa2D::Vector*  f_vector;
    
    t_float*        f_signals;
    t_float         f_vector_coords[4];
    long            f_ramp;
	int             f_startclock;
	long            f_interval;
    
    t_symbol*       f_vector_type;
    t_symbol*       f_clockwise;
    int*            f_over_leds;
	
    t_rgba          f_color_bg;
    t_rgba          f_color_bd;
	t_rgba		f_color_cold_signal;
	t_rgba		f_color_tepid_signal;
	t_rgba		f_color_warm_signal;
	t_rgba		f_color_hot_signal;
	t_rgba		f_color_over_signal;
	
	t_rgba		f_color_energy_vector;
	t_rgba		f_color_velocity_vector;
	
    double      f_radius;
    double      f_center;
	double		f_radius_center;
    
	t_clock*	f_clock;
    void*       f_attrs;
    
} t_hoa_meter;

t_eclass *hoa_meter_class;

void *hoa_meter_new(t_symbol *s, int argc, t_atom *argv);
void hoa_meter_free(t_hoa_meter *x);
void hoa_meter_assist(t_hoa_meter *x, void *b, long m, long a, char *s);

void hoa_meter_dsp(t_hoa_meter *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_meter_perform(t_hoa_meter *x, t_object *d, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_meter_tick(t_hoa_meter *x);

t_pd_err hoa_meter_notify(t_hoa_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_pd_err channels_get(t_hoa_meter *x, void *attr, long *argc, t_atom **argv);
t_pd_err channels_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);
t_pd_err angles_get(t_hoa_meter *x, void *attr, long *argc, t_atom **argv);
t_pd_err angles_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);
t_pd_err offset_get(t_hoa_meter *x, void *attr, long *argc, t_atom **argv);
t_pd_err offset_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);
t_pd_err vectors_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);
t_pd_err rotation_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);

/* Paint ------------------------------------- */
void hoa_meter_getdrawparams(t_hoa_meter *x, t_object *patcherview, t_edrawparams *params);
void hoa_meter_oksize(t_hoa_meter *x, t_rect *newrect);

void hoa_meter_paint(t_hoa_meter *x, t_object *view);
void draw_background(t_hoa_meter *x, t_object *view, t_rect *rect);
void draw_leds(t_hoa_meter *x,  t_object *view, t_rect *rect);
void draw_vectors(t_hoa_meter *x, t_object *view, t_rect *rect);

t_hoa_err hoa_getinfos(t_hoa_meter* x, t_hoa_boxinfos* boxinfos);

t_symbol* hoa_sym_none = gensym("none");
t_symbol* hoa_sym_energy = gensym("energy");
t_symbol* hoa_sym_velocity = gensym("velocity");
t_symbol* hoa_sym_both = gensym("both");
t_symbol* hoa_sym_clockwise = gensym("clockwise");
t_symbol* hoa_sym_anticlock = gensym("anti-clockwise");
t_symbol* hoa_sym_vector_layer = gensym("vectors_layer");
t_symbol* hoa_sym_leds_layer = gensym("leds_layers");

void hoa_meter_deprecated(t_hoa_meter* x, t_symbol *s, long ac, t_atom* av);

#define  contrast_white 0.06
#define  contrast_black 0.14

extern "C" void setup_hoa0x2e2d0x2emeter_tilde(void)
{
	t_eclass *c;
    
	c = eclass_new("hoa.2d.meter~", (method)hoa_meter_new, (method)hoa_meter_free, (short)sizeof(t_hoa_meter), 0L, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_meter_new, gensym("hoa.meter~"), A_GIMME, 0);
    
	eclass_dspinit(c);
	eclass_init(c, 0);
	hoa_initclass(c, (method)hoa_getinfos);
	eclass_addmethod(c, (method) hoa_meter_dsp,             "dsp",           A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_assist,          "assist",		 A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_paint,           "paint",		 A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_notify,          "notify",        A_CANT, 0);
    eclass_addmethod(c, (method) hoa_meter_getdrawparams,   "getdrawparams", A_CANT, 0);
    eclass_addmethod(c, (method) hoa_meter_oksize,          "oksize",        A_CANT, 0);
    
    eclass_addmethod(c, (method)hoa_meter_deprecated,   "loudspeakers",	A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_meter_deprecated,   "bordercolor",	A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_meter_deprecated,   "mbgcolor",     A_GIMME, 0);
    
	CLASS_ATTR_INVISIBLE            (c, "fontname", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontweight", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontslant", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontsize", 1);
    CLASS_ATTR_INVISIBLE            (c, "send", 1);
	CLASS_ATTR_DEFAULT              (c, "size", 0, "225. 225.");
	
    CLASS_ATTR_LONG                 (c, "channels", 0 , t_hoa_meter, f_attrs);
    CLASS_ATTR_ACCESSORS            (c, "channels", channels_get, channels_set);
	CLASS_ATTR_ORDER                (c, "channels", 0, "1");
	CLASS_ATTR_LABEL                (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_SAVE                 (c, "channels", 1);
    CLASS_ATTR_DEFAULT              (c, "channels", 0, "8");
    CLASS_ATTR_STYLE                (c, "channels", 1, "number");
    
    CLASS_ATTR_FLOAT_VARSIZE        (c, "angles", 0, t_hoa_meter, f_attrs, f_attrs, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS            (c, "angles", angles_get, angles_set);
	CLASS_ATTR_ORDER                (c, "angles", 0, "2");
	CLASS_ATTR_LABEL                (c, "angles", 0, "Angles of Channels");
	CLASS_ATTR_SAVE                 (c, "angles", 1);
    CLASS_ATTR_DEFAULT              (c, "angles", 0, "0 45 90 135 180 225 270 315");
    
    CLASS_ATTR_FLOAT                (c, "offset", 0, t_hoa_meter, f_attrs);
    CLASS_ATTR_ACCESSORS            (c, "offset", offset_get, offset_set);
	CLASS_ATTR_ORDER                (c, "offset", 0, "3");
	CLASS_ATTR_LABEL                (c, "offset", 0, "Offset of Channels");
	CLASS_ATTR_DEFAULT              (c, "offset", 0, "0");
	CLASS_ATTR_SAVE                 (c, "offset", 1);
    CLASS_ATTR_STYLE                (c, "offset", 1, "number");
    
    CLASS_ATTR_SYMBOL               (c, "rotation", 0, t_hoa_meter, f_clockwise);
    CLASS_ATTR_ACCESSORS            (c, "rotation", NULL, rotation_set);
    CLASS_ATTR_ORDER                (c, "rotation", 0, "4");
	CLASS_ATTR_LABEL                (c, "rotation", 0, "Rotation of Channels");
    CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "rotation", 0, "0");
    CLASS_ATTR_STYLE                (c, "rotation", 1, "menu");
    CLASS_ATTR_ITEMS                (c, "rotation", 1, "anti-clockwise clockwise");
    
	CLASS_ATTR_SYMBOL               (c, "vectors", 0, t_hoa_meter, f_vector_type);
    CLASS_ATTR_ACCESSORS            (c, "vectors", NULL, vectors_set);
	CLASS_ATTR_ORDER                (c, "vectors", 0, "2");
    CLASS_ATTR_LABEL                (c, "vectors", 0, "Vectors");
	CLASS_ATTR_DEFAULT              (c, "vectors", 0, "Energy");
	CLASS_ATTR_SAVE                 (c, "vectors", 1);
    CLASS_ATTR_STYLE                (c, "vectors", 1, "menu");
    CLASS_ATTR_ITEMS                (c, "vectors", 1, "none energy velocity both");
    
    CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_meter, f_interval);
	CLASS_ATTR_ORDER                (c, "interval", 0, "5");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval (in ms)");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "50");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
	CLASS_ATTR_STYLE                (c, "interval", 1, "number");
    
    CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_hoa_meter, f_color_bg);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.76 0.76 0.76 1.");
	CLASS_ATTR_STYLE                (c, "bgcolor", 1, "color");
    
    CLASS_ATTR_RGBA					(c, "bdcolor", 0, t_hoa_meter, f_color_bd);
	CLASS_ATTR_CATEGORY				(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bdcolor", 0, "0.7 0.7 0.7 1.");
	CLASS_ATTR_STYLE                (c, "bdcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "coldcolor", 0, t_hoa_meter, f_color_cold_signal);
	CLASS_ATTR_LABEL                (c, "coldcolor", 0, "Cold Signal Color");
	CLASS_ATTR_ORDER                (c, "coldcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "coldcolor", 0, "0. 0.6 0. 0.8");
	CLASS_ATTR_STYLE                (c, "coldcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "tepidcolor", 0, t_hoa_meter, f_color_tepid_signal);
	CLASS_ATTR_LABEL                (c, "tepidcolor", 0, "Tepid Signal Color");
	CLASS_ATTR_ORDER                (c, "tepidcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "tepidcolor", 0, "0.6 0.73 0. 0.8");
	CLASS_ATTR_STYLE                (c, "tepidcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "warmcolor", 0, t_hoa_meter, f_color_warm_signal);
	CLASS_ATTR_LABEL                (c, "warmcolor", 0, "Warm Signal Color");
	CLASS_ATTR_ORDER                (c, "warmcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "warmcolor", 0, ".85 .85 0. 0.8");
	CLASS_ATTR_STYLE                (c, "warmcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "hotcolor", 0, t_hoa_meter, f_color_hot_signal);
	CLASS_ATTR_LABEL                (c, "hotcolor", 0, "Hot Signal Color");
	CLASS_ATTR_ORDER                (c, "hotcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "hotcolor", 0, "1. 0.6 0. 0.8");
	CLASS_ATTR_STYLE                (c, "hotcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "overcolor", 0, t_hoa_meter, f_color_over_signal);
	CLASS_ATTR_LABEL                (c, "overcolor", 0, "Overload Signal Color");
	CLASS_ATTR_ORDER                (c, "overcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "overcolor", 0, "1. 0. 0. 0.8");
	CLASS_ATTR_STYLE                (c, "overcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "energycolor", 0, t_hoa_meter, f_color_energy_vector);
	CLASS_ATTR_LABEL                (c, "energycolor", 0, "Energy Vector Color");
	CLASS_ATTR_ORDER                (c, "energycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "energycolor", 0, "0. 0. 1. 0.8");
    CLASS_ATTR_STYLE                (c, "energycolor", 1, "color");
    
    CLASS_ATTR_RGBA                 (c, "velocitycolor", 0, t_hoa_meter, f_color_velocity_vector);
	CLASS_ATTR_LABEL                (c, "velocitycolor", 0, "Velocity Vector Color");
	CLASS_ATTR_ORDER                (c, "velocitycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "velocitycolor", 0, "1. 0. 0. 0.8");
    CLASS_ATTR_STYLE                (c, "velocitycolor", 1, "color");
	
    eclass_register(CLASS_BOX, c);
	hoa_meter_class = c;
}

void hoa_meter_deprecated(t_hoa_meter* x, t_symbol *s, long ac, t_atom* av)
{
    t_atom* argv;
    long argc;
    if(s && s == gensym("loudspeakers") && ac && av)
    {
        object_error(x, "%s attribute @loudspeakers is deprecated, please use @channels.", eobj_getclassname(x)->s_name);
        channels_set(x, NULL, ac, av);
    }
    if(s && s == gensym("bordercolor") && ac && av)
    {
        object_attr_setvalueof((t_object *)x, gensym("bdcolor"), ac, av);
        object_error(x, "%s attribute @bordercolor is deprecated, please use @bdcolor.", eobj_getclassname(x)->s_name);
    }
    
    atoms_get_attribute(ac, av, gensym("@loudspeakers"), &argc, &argv);
    if(argc && argv)
    {
        object_error(x, "%s attribute @loudspeakers is deprecated, please use @channels.", eobj_getclassname(x)->s_name);
        channels_set(x, NULL, argc, argv);
        argc = 0;free(argv);argv = NULL;
    }
    atoms_get_attribute(ac, av, gensym("@bordercolor"), &argc, &argv);
    if(argc && argv)
    {
        object_attr_setvalueof((t_object *)x, gensym("bdcolor"), argc, argv);
        object_error(x, "%s attribute @bordercolor is deprecated, please use @bdcolor.", eobj_getclassname(x)->s_name);
        argc = 0;free(argv);argv = NULL;
    }

    if((s && s == gensym("mbgcolor")) || atoms_has_attribute(ac, av, gensym("@mbgcolor")))
    {
        object_error(x, "%s attribute @mbgcolor is deprecated.", eobj_getclassname(x)->s_name);
        argc = 0;free(argv);argv = NULL;
    }
}

void *hoa_meter_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_meter *x =  NULL;
	t_binbuf *d;
	long flags;
	
	if (!(d = binbuf_via_atoms(argc, argv)))
		return NULL;
    
	x = (t_hoa_meter *)eobj_new(hoa_meter_class);
    
    x->f_ramp = 0;
    x->f_meter  = new Hoa2D::Meter(4);
    x->f_vector = new Hoa2D::Vector(4);
    x->f_signals = new t_float[MAX_SPEAKER * SYS_MAXBLKSIZE];
    x->f_over_leds = new int[MAX_CHANNELS];
    
    x->f_clock = clock_new(x,(t_method)hoa_meter_tick);
	x->f_startclock = 0;
    eobj_dspsetup((t_ebox *)x, x->f_meter->getNumberOfChannels(), 0);
    
    flags = 0
    | EBOX_GROWLINK
    | EBOX_IGNORELOCKCLICK
    ;
	ebox_new((t_ebox *)x, flags);
    
    hoa_meter_deprecated(x, s, argc, argv);
	ebox_attrprocess_viabinbuf(x, d);
    
	ebox_ready((t_ebox *)x);
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_meter* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs    = x->f_meter->getNumberOfChannels();
	boxinfos->autoconnect_outputs   = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_PLANEWAVES;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_meter_getdrawparams(t_hoa_meter *x, t_object *patcherview, t_edrawparams *params)
{
    params->d_boxfillcolor = x->f_color_bg;
    params->d_bordercolor = x->f_color_bd;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

void hoa_meter_oksize(t_hoa_meter *x, t_rect *newrect)
{
    newrect->width = pd_clip_min(newrect->width, 20.);
    newrect->height = pd_clip_min(newrect->height, 20.);
}

t_pd_err channels_get(t_hoa_meter *x, void *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)malloc(sizeof(t_atom));
    if(argv[0] && argc[0])
    {
        atom_setfloat(argv[0], x->f_meter->getNumberOfChannels());
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return 0;
}

t_pd_err channels_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv)
{
    t_atom* av;
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_FLOAT)
        {
            long d = pd_clip_minmax(atom_getfloat(argv), 1, MAX_SPEAKER);
            if(d != x->f_meter->getNumberOfChannels())
            {
                int dspState = canvas_suspend_dsp();
                delete x->f_meter;
                x->f_meter = new Meter(d);
                delete x->f_vector;
                x->f_vector = new Vector(d);
                
                av = new t_atom[x->f_meter->getNumberOfChannels()];
                for(int i = 0; i < x->f_meter->getNumberOfChannels(); i++)
                {
                    atom_setfloat(av+i, x->f_meter->getChannelAzimuth(i) / HOA_2PI * 360.);
                    x->f_over_leds[i] = 0;
                }
                angles_set(x, NULL, x->f_meter->getNumberOfChannels(), av);
                
                eobj_resize_inputs((t_ebox *)x, x->f_meter->getNumberOfChannels());
                
                canvas_resume_dsp(dspState);
            }
        }
    }
    return NULL;
}

t_pd_err angles_get(t_hoa_meter *x, void *attr, long *argc, t_atom **argv)
{
    argc[0] = x->f_meter->getNumberOfChannels();
    argv[0] = (t_atom *)malloc(sizeof(t_atom) * x->f_meter->getNumberOfChannels());
    if(argv[0] && argc[0])
    {
        for(int i = 0; i < x->f_meter->getNumberOfChannels(); i++)
            atom_setfloat(argv[0]+i, x->f_meter->getChannelAzimuth(i) / HOA_2PI * 360.);
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return 0;
}

t_pd_err angles_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv)
{
    double angles[MAX_SPEAKER];
    if(argc > MAX_SPEAKER)
        argc = MAX_SPEAKER;
    if(argc && argv)
    {
        for(int i = 0; i < argc; i++)
        {
            if(atom_gettype(argv+i) == A_FLOAT)
            {
                angles[i] = atom_getfloat(argv+i) / 360. * HOA_2PI;
            }
        }
        x->f_meter->setChannelsAzimuth(angles);
        x->f_vector->setChannelsAzimuth(angles);
    }

	ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_leds_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_vector_layer);
    
	ebox_redraw((t_ebox *)x);
    return 0;
}

t_pd_err offset_get(t_hoa_meter *x, void *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)malloc(sizeof(t_atom));
    if(argv[0] && argc[0])
    {
        atom_setfloat(argv[0], x->f_meter->getChannelsOffset() / HOA_2PI * 360.);
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return 0;
}

t_pd_err offset_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_vector->setChannelsOffset(atom_getfloat(argv) / 360 * HOA_2PI);
        x->f_meter->setChannelsOffset(atom_getfloat(argv) / 360 * HOA_2PI);
    }
    
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_leds_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_vector_layer);
    
	ebox_redraw((t_ebox *)x);
    return 0;
}

t_pd_err vectors_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == hoa_sym_energy)
                x->f_vector_type = hoa_sym_energy;
            else if(atom_getsym(argv) == hoa_sym_velocity)
                x->f_vector_type = hoa_sym_velocity;
            else if(atom_getsym(argv) == hoa_sym_both)
                x->f_vector_type = hoa_sym_both;
            else
                x->f_vector_type = hoa_sym_none;
        }
        else if(atom_gettype(argv) == A_FLOAT)
        {
            if(atom_getlong(argv) == 1)
                x->f_vector_type = hoa_sym_energy;
            else if(atom_getlong(argv) == 2)
                x->f_vector_type = hoa_sym_velocity;
            else if(atom_getlong(argv) == 3)
                x->f_vector_type = hoa_sym_both;
            else
                x->f_vector_type = hoa_sym_none;
        }
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_vector_layer);
    }
    return 0;
}

t_pd_err rotation_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == hoa_sym_clockwise)
                x->f_clockwise = hoa_sym_clockwise;
            else
                x->f_clockwise = hoa_sym_anticlock;
        }
        else if(atom_gettype(argv) == A_FLOAT)
        {
            if(atom_getlong(argv) == 1)
                x->f_clockwise = hoa_sym_clockwise;
            else
                x->f_clockwise = hoa_sym_anticlock;
        }
    }
    return 0;
}

void hoa_meter_dsp(t_hoa_meter *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_meter->setVectorSize(maxvectorsize);
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_meter_perform, 0, NULL);
	x->f_startclock = 1;
}

void hoa_meter_perform(t_hoa_meter *x, t_object *dsp, float **ins, long numins, float **outs, long no, long sampleframes, long f,void *up)
{
	for(int i = 0; i < numins; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
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

void hoa_meter_tick(t_hoa_meter *x)
{
    if(x->f_vector_type == hoa_sym_both)
        x->f_vector->process(x->f_signals, x->f_vector_coords);
    else if(x->f_vector_type == hoa_sym_velocity)
        x->f_vector->processVelocity(x->f_signals, x->f_vector_coords);
    else if(x->f_vector_type == hoa_sym_energy)
         x->f_vector->processEnergy(x->f_signals, x->f_vector_coords + 2);
    
    double peak;
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
    
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_leds_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_vector_layer);
  	ebox_redraw((t_ebox *)x);
    
	if (sys_getdspstate())
		clock_delay(x->f_clock, x->f_interval);
}

void hoa_meter_free(t_hoa_meter *x)
{
	ebox_free((t_ebox *)x);
    clock_free(x->f_clock);
    delete x->f_meter;
    delete x->f_vector;
    delete [] x->f_signals;
    delete [] x->f_over_leds;
}

void hoa_meter_assist(t_hoa_meter *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_meter->getChannelName(a).c_str());
}

t_pd_err hoa_meter_notify(t_hoa_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("attr_modified"))
	{
		ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_leds_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_vector_layer);
		ebox_redraw((t_ebox *)x);
	}
	return 0;
}

void hoa_meter_paint(t_hoa_meter *x, t_object *view)
{
	t_rect rect;
	ebox_get_rect_for_view((t_ebox *)x, &rect);
	
    x->f_center = rect.width * .5;
	x->f_radius = x->f_center * 0.95;
	x->f_radius_center = x->f_radius / 5.;
	
	draw_background(x, view, &rect);
    draw_leds(x, view, &rect);
    draw_vectors(x, view, &rect);
}

void draw_background(t_hoa_meter *x,  t_object *view, t_rect *rect)
{
	int i;
    float coso, sino, angle, x1, y1, x2, y2;
    t_rgba black, white;
	t_matrix transform;
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_background_layer, rect->width, rect->height);
    
    black = rgba_addContrast(x->f_color_bg, -contrast_black);
    white = rgba_addContrast(x->f_color_bg, contrast_white);
    
	if (g)
	{
        egraphics_matrix_init(&transform, 1, 0, 0, -1, rect->width * .5, rect->width * .5);
        egraphics_set_matrix(g, &transform);
       
        egraphics_rotate(g, -HOA_PI2);
        
		egraphics_set_line_width(g, 1.);

		egraphics_set_color_rgba(g, &x->f_color_bg);
		egraphics_arc(g, 0.f, 0.f, x->f_radius, 0., HOA_2PI);
		egraphics_fill(g);

		egraphics_set_color_rgba(g, &x->f_color_bg);
		egraphics_arc(g, 0.f, 0.f, x->f_radius_center, 0., HOA_2PI);
		egraphics_fill(g);
		
        egraphics_set_color_rgba(g, &white);
        egraphics_set_line_width(g, 1.f);
        egraphics_arc(g, 1, 1, x->f_radius,  0., HOA_2PI);
        egraphics_stroke(g);
        egraphics_arc(g, 1, 1, x->f_radius_center,  0., HOA_2PI);
        egraphics_stroke(g);
        
        egraphics_set_color_rgba(g, &black);
        egraphics_set_line_width(g, 1.f);
        egraphics_arc(g, 0.f, 0.f, x->f_radius,  0., HOA_2PI);
        egraphics_stroke(g);
        egraphics_arc(g, 0.f, 0.f, x->f_radius_center,  0., HOA_2PI);
        egraphics_stroke(g);
        
        if(x->f_meter->getNumberOfChannels() != 1)
        {
            for(i = 0; i < x->f_meter->getNumberOfChannels(); i++)
            {
                angle = x->f_meter->getChannelAzimuthMapped(i) - x->f_meter->getChannelWidth(i) * 0.5f;
                if(x->f_clockwise == hoa_sym_clockwise)
                    angle = -angle;
                egraphics_set_line_width(g, 1.f);
               
                coso = cosf(angle);
                sino = sinf(angle);
                x1 = x->f_radius_center * coso;
                y1 = x->f_radius_center * sino;
                x2 = x->f_radius * coso;
                y2 = x->f_radius * sino;
                if(isInsideRad(angle, HOA_PI4, HOA_PI + HOA_PI4))
                {
                    egraphics_move_to(g, x1 - 0.5, y1 - 0.5);
                    egraphics_line_to(g, x2 - 0.5, y2 - 0.5);
                }
                else
                {
                    egraphics_move_to(g, x1 + 0.5, y1 + 0.5);
                    egraphics_line_to(g, x2 + 0.5, y2 + 0.5);
                }
                
                egraphics_set_color_rgba(g, &white);
                egraphics_stroke(g);
                
                
				egraphics_move_to(g, x1, y1);
				egraphics_line_to(g, x2, y2);
                
                egraphics_set_color_rgba(g, &black);
				egraphics_stroke(g);
			}
        }
		ebox_end_layer((t_ebox*)x, hoa_sym_background_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_background_layer, 0., 0.);
}

void draw_leds(t_hoa_meter *x, t_object *view, t_rect *rect)
{
    int i;
    float j, h, dB;
    float angle_start, angle, angle_end, radius, center_x, center_y;
    float led_width = 0.49 * rect->width / 18.;
    
    t_rgba black = rgba_addContrast(x->f_color_bg, -0.14);
	t_elayer *g = ebox_start_layer((t_ebox *)x,  hoa_sym_leds_layer, rect->width, rect->height);
    
	if (g)
	{
        h = led_width * 17.;
        for(i = 0; i < x->f_meter->getNumberOfChannels(); i++)
        {
            if(x->f_clockwise != hoa_sym_clockwise)
                angle   = x->f_meter->getChannelAzimuthMapped(i) + HOA_PI2;
            else
                angle   = -x->f_meter->getChannelAzimuthMapped(i) + HOA_PI2;
            
            center_x    = pd_abscissa(x->f_radius - h, angle);
            center_y    = -pd_ordinate(x->f_radius - h, angle);
            
            angle_start = angle - x->f_meter->getChannelWidth(i) * 0.5f;
            angle_end   = angle + x->f_meter->getChannelWidth(i) * 0.5f;
            for(j = 11, dB = -34.5; j > -1; j--, dB += 3.)
            {
                radius    = (j + 5.) * led_width;
                
                if(x->f_meter->getChannelEnergy(i) > dB)
                {
                    if(j > 8)
                        egraphics_set_color_rgba(g, &x->f_color_cold_signal);
                    else if(j > 5)
                        egraphics_set_color_rgba(g, &x->f_color_tepid_signal);
                    else if(j > 2)
                        egraphics_set_color_rgba(g, &x->f_color_warm_signal);
                    else
                        egraphics_set_color_rgba(g, &x->f_color_hot_signal);
                    
                    egraphics_set_line_width(g, led_width - pd_clip_min(360. / rect->width, 2.));
                    egraphics_arc(g, center_x + rect->width * 0.5f, center_y + rect->width * 0.5f, radius, angle_start, angle_end);
                    egraphics_stroke(g);
                }
                else if(j != -1)
                {
                    egraphics_set_color_rgba(g, &black);
                    egraphics_set_line_width(g, led_width - pd_clip_min(360. / rect->width, 2.));
                    egraphics_arc(g, center_x + rect->width * 0.5f, center_y + rect->width * 0.5f, radius,  angle_start, angle_end);
                    egraphics_stroke(g);
                }
            }
            if(x->f_over_leds[i])
            {
                radius    = (4.) * led_width;
                egraphics_set_color_rgba(g, &x->f_color_over_signal);
                egraphics_set_line_width(g, led_width - pd_clip_min(360. / rect->width, 2.));
                egraphics_arc(g, center_x + rect->width * 0.5f, center_y + rect->width * 0.5f, radius, angle_start, angle_end);
                egraphics_stroke(g);
            }
        }
		ebox_end_layer((t_ebox*)x,  hoa_sym_leds_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_leds_layer, 0., 0.);
}

void draw_vectors(t_hoa_meter *x, t_object *view, t_rect *rect)
{
	double x1, y1, size;
	t_matrix transform;
	t_elayer *g = ebox_start_layer((t_ebox *)x,  hoa_sym_vector_layer, rect->width, rect->height);
	
	if(g)
	{
		egraphics_matrix_init(&transform, 1, 0, 0, -1, rect->width / 2., rect->width / 2.);
		egraphics_set_matrix(g, &transform);
		size = 1. / 64. * rect->width;
    
        if(x->f_vector_type == hoa_sym_both || x->f_vector_type == hoa_sym_energy)
        {
            egraphics_set_color_rgba(g, &x->f_color_energy_vector);
            if(x->f_clockwise == hoa_sym_anticlock)
            {
                x1 = x->f_vector_coords[2] * x->f_radius_center * 0.85;
                y1 = x->f_vector_coords[3] * x->f_radius_center * 0.85;
            }
            else
            {
                double rad = radius(x->f_vector_coords[2], x->f_vector_coords[3]) * x->f_radius_center * 0.85;
                double ang = -azimuth(x->f_vector_coords[2], x->f_vector_coords[3]);
                x1 = abscissa(rad, ang);
                y1 = ordinate(rad, ang);
            }
            egraphics_arc(g, x1, y1, size, 0., HOA_2PI);
            egraphics_fill(g);
		}
        if(x->f_vector_type == hoa_sym_both || x->f_vector_type == hoa_sym_velocity)
        {
            egraphics_set_color_rgba(g, &x->f_color_velocity_vector);
            if(x->f_clockwise == hoa_sym_anticlock)
            {
                x1 = x->f_vector_coords[0] * x->f_radius_center * 0.85;
                y1 = x->f_vector_coords[1] * x->f_radius_center * 0.85;
            }
            else
            {
                double rad = radius(x->f_vector_coords[0], x->f_vector_coords[1]) * x->f_radius_center * 0.85;
                double ang = -azimuth(x->f_vector_coords[0], x->f_vector_coords[1]);
                x1 = abscissa(rad, ang);
                y1 = ordinate(rad, ang);
            }
            egraphics_arc(g, x1, y1, size, 0., HOA_2PI);
            egraphics_fill(g);
		}
        
		ebox_end_layer((t_ebox*)x,  hoa_sym_vector_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_vector_layer, 0., 0.);
}

