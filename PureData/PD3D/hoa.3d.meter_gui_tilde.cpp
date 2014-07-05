/*
 // Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "Hoa3D.pd.h"

#define MAX_SPEAKER 64

typedef struct  _hoa_meter_3d
{
	t_edspbox   j_box;
    
    Hoa3D::Meter*   f_meter;
    Hoa3D::Vector*  f_vector;
    t_float*        f_signals;
    t_float         f_vector_coords[6];
    int*            f_over_leds;
    
    long            f_ramp;
	int             f_startclock;
	long            f_interval;
    
    t_symbol*       f_vector_type;
    t_symbol*       f_clockwise;
    t_symbol*       f_view;
	
    t_rgba          f_color_bg;
    t_rgba          f_color_bd;
	t_rgba          f_color_cold_signal;
	t_rgba          f_color_tepid_signal;
	t_rgba          f_color_warm_signal;
	t_rgba          f_color_hot_signal;
	t_rgba          f_color_over_signal;
	
	t_rgba          f_color_energy_vector;
	t_rgba          f_color_velocity_vector;
	
    double          f_radius;
    double          f_center;
    
	t_clock*        f_clock;
    void*           f_attrs;
    
} t_hoa_meter_3d;

t_eclass *hoa_meter_3d_class;

void *hoa_meter_3d_new(t_symbol *s, int argc, t_atom *argv);
void hoa_meter_3d_free(t_hoa_meter_3d *x);
void hoa_meter_3d_assist(t_hoa_meter_3d *x, void *b, long m, long a, char *s);

void hoa_meter_3d_dsp(t_hoa_meter_3d *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_meter_3d_perform(t_hoa_meter_3d *x, t_object *d, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_meter_3d_tick(t_hoa_meter_3d *x);

t_pd_err hoa_meter_3d_notify(t_hoa_meter_3d *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_pd_err channels_get(t_hoa_meter_3d *x, void *attr, long *argc, t_atom **argv);
t_pd_err channels_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv);
t_pd_err angles_get(t_hoa_meter_3d *x, void *attr, long *argc, t_atom **argv);
t_pd_err angles_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv);
t_pd_err offset_get(t_hoa_meter_3d *x, void *attr, long *argc, t_atom **argv);
t_pd_err offset_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv);
t_pd_err vectors_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv);
t_pd_err rotation_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv);
t_pd_err view_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv);

void hoa_meter_3d_getdrawparams(t_hoa_meter_3d *x, t_object *patcherview, t_edrawparams *params);
void hoa_meter_3d_oksize(t_hoa_meter_3d *x, t_rect *newrect);

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
t_symbol* hoa_sym_3d_toponbottom = gensym("top/bottom");
t_symbol* hoa_sym_3d_topnextbottom = gensym("top-bottom");

#define  contrast_white 0.06
#define  contrast_black 0.14

extern "C" void setup_hoa0x2e3d0x2emeter_tilde(void)
{
	t_eclass *c;
    
	c = eclass_new("hoa.3d.meter~", (method)hoa_meter_3d_new, (method)hoa_meter_3d_free, (short)sizeof(t_hoa_meter_3d), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
	eclass_init(c, 0);
	hoa_initclass(c, (method)hoa_getinfos);
	eclass_addmethod(c, (method) hoa_meter_3d_dsp,             "dsp",           A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_3d_assist,          "assist",		A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_3d_paint,           "paint",         A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_3d_notify,          "notify",        A_CANT, 0);
    eclass_addmethod(c, (method) hoa_meter_3d_getdrawparams,   "getdrawparams", A_CANT, 0);
    eclass_addmethod(c, (method) hoa_meter_3d_oksize,          "oksize",        A_CANT, 0);
    
	CLASS_ATTR_INVISIBLE            (c, "fontname", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontweight", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontslant", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontsize", 1);
    CLASS_ATTR_INVISIBLE            (c, "send", 1);
	CLASS_ATTR_DEFAULT              (c, "size", 0, "225. 225.");
	
    CLASS_ATTR_LONG                 (c, "channels", 0 , t_hoa_meter_3d, f_attrs);
    CLASS_ATTR_ACCESSORS            (c, "channels", channels_get, channels_set);
	CLASS_ATTR_ORDER                (c, "channels", 0, "1");
	CLASS_ATTR_LABEL                (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_SAVE                 (c, "channels", 1);
    CLASS_ATTR_DEFAULT              (c, "channels", 0, "8");
    CLASS_ATTR_STYLE                (c, "channels", 1, "number");
    
    CLASS_ATTR_FLOAT_VARSIZE        (c, "angles", 0, t_hoa_meter_3d, f_attrs, f_attrs, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS            (c, "angles", angles_get, angles_set);
	CLASS_ATTR_ORDER                (c, "angles", 0, "2");
	CLASS_ATTR_LABEL                (c, "angles", 0, "Angles of Channels");
	CLASS_ATTR_SAVE                 (c, "angles", 1);
    CLASS_ATTR_DEFAULT              (c, "angles", 0, "0 45 90 45 180 45 270 45 0 -45 90 -45 180 -45 270 -45");
    
    CLASS_ATTR_DOUBLE_ARRAY         (c, "offset", 0, t_hoa_meter_3d, f_attrs, 3);
    CLASS_ATTR_ACCESSORS            (c, "offset", offset_get, offset_set);
	CLASS_ATTR_ORDER                (c, "offset", 0, "3");
	CLASS_ATTR_LABEL                (c, "offset", 0, "Offset of Channels");
	CLASS_ATTR_DEFAULT              (c, "offset", 0, "0 0 0");
	CLASS_ATTR_SAVE                 (c, "offset", 1);
    CLASS_ATTR_STYLE                (c, "offset", 1, "number");
    
    CLASS_ATTR_SYMBOL               (c, "rotation", 0, t_hoa_meter_3d, f_clockwise);
    CLASS_ATTR_ACCESSORS            (c, "rotation", NULL, rotation_set);
    CLASS_ATTR_ORDER                (c, "rotation", 0, "4");
	CLASS_ATTR_LABEL                (c, "rotation", 0, "Rotation of Channels");
    CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "rotation", 0, "anti-clockwise");
    CLASS_ATTR_STYLE                (c, "rotation", 1, "menu");
    CLASS_ATTR_ITEMS                (c, "rotation", 1, "anti-clockwise clockwise");
    
    CLASS_ATTR_SYMBOL               (c, "view", 0 , t_hoa_meter_3d, f_view);
    CLASS_ATTR_ACCESSORS            (c, "view", NULL, view_set);
	CLASS_ATTR_ORDER                (c, "view", 0, "5");
	CLASS_ATTR_LABEL                (c, "view", 0, "Number of Channels");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "view", 0, "top");
    CLASS_ATTR_STYLE                (c, "view", 1, "menu");
    CLASS_ATTR_ITEMS                (c, "view", 1, "top bottom top-bottom top/bottom");
    
	CLASS_ATTR_SYMBOL               (c, "vectors", 0, t_hoa_meter_3d, f_vector_type);
    CLASS_ATTR_ACCESSORS            (c, "vectors", NULL, vectors_set);
	CLASS_ATTR_ORDER                (c, "vectors", 0, "2");
    CLASS_ATTR_LABEL                (c, "vectors", 0, "Vectors");
	CLASS_ATTR_DEFAULT              (c, "vectors", 0, "Energy");
	CLASS_ATTR_SAVE                 (c, "vectors", 1);
    CLASS_ATTR_STYLE                (c, "vectors", 1, "menu");
    CLASS_ATTR_ITEMS                (c, "vectors", 1, "none energy velocity both");
    
    CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_meter_3d, f_interval);
	CLASS_ATTR_ORDER                (c, "interval", 0, "5");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval (in ms)");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "50");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
	CLASS_ATTR_STYLE                (c, "interval", 1, "number");
    
    CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_hoa_meter_3d, f_color_bg);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.76 0.76 0.76 1.");
	CLASS_ATTR_STYLE                (c, "bgcolor", 1, "color");
    
    CLASS_ATTR_RGBA					(c, "bdcolor", 0, t_hoa_meter_3d, f_color_bd);
	CLASS_ATTR_CATEGORY				(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bdcolor", 0, "0.7 0.7 0.7 1.");
	CLASS_ATTR_STYLE                (c, "bdcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "coldcolor", 0, t_hoa_meter_3d, f_color_cold_signal);
	CLASS_ATTR_LABEL                (c, "coldcolor", 0, "Cold Signal Color");
	CLASS_ATTR_ORDER                (c, "coldcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "coldcolor", 0, "0. 0.6 0. 0.8");
	CLASS_ATTR_STYLE                (c, "coldcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "tepidcolor", 0, t_hoa_meter_3d, f_color_tepid_signal);
	CLASS_ATTR_LABEL                (c, "tepidcolor", 0, "Tepid Signal Color");
	CLASS_ATTR_ORDER                (c, "tepidcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "tepidcolor", 0, "0.6 0.73 0. 0.8");
	CLASS_ATTR_STYLE                (c, "tepidcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "warmcolor", 0, t_hoa_meter_3d, f_color_warm_signal);
	CLASS_ATTR_LABEL                (c, "warmcolor", 0, "Warm Signal Color");
	CLASS_ATTR_ORDER                (c, "warmcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "warmcolor", 0, ".85 .85 0. 0.8");
	CLASS_ATTR_STYLE                (c, "warmcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "hotcolor", 0, t_hoa_meter_3d, f_color_hot_signal);
	CLASS_ATTR_LABEL                (c, "hotcolor", 0, "Hot Signal Color");
	CLASS_ATTR_ORDER                (c, "hotcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "hotcolor", 0, "1. 0.6 0. 0.8");
	CLASS_ATTR_STYLE                (c, "hotcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "overcolor", 0, t_hoa_meter_3d, f_color_over_signal);
	CLASS_ATTR_LABEL                (c, "overcolor", 0, "Overload Signal Color");
	CLASS_ATTR_ORDER                (c, "overcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "overcolor", 0, "1. 0. 0. 0.8");
	CLASS_ATTR_STYLE                (c, "overcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "energycolor", 0, t_hoa_meter_3d, f_color_energy_vector);
	CLASS_ATTR_LABEL                (c, "energycolor", 0, "Energy Vector Color");
	CLASS_ATTR_ORDER                (c, "energycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "energycolor", 0, "0. 0. 1. 0.8");
    CLASS_ATTR_STYLE                (c, "energycolor", 1, "color");
    
    CLASS_ATTR_RGBA                 (c, "velocitycolor", 0, t_hoa_meter_3d, f_color_velocity_vector);
	CLASS_ATTR_LABEL                (c, "velocitycolor", 0, "Velocity Vector Color");
	CLASS_ATTR_ORDER                (c, "velocitycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "velocitycolor", 0, "1. 0. 0. 0.8");
    CLASS_ATTR_STYLE                (c, "velocitycolor", 1, "color");
	
    eclass_register(CLASS_BOX, c);
	hoa_meter_3d_class = c;
}

void *hoa_meter_3d_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_meter_3d *x =  NULL;
	t_binbuf *d;
	long flags;
	t_atom *av;
    long    ac;
    
	if (!(d = binbuf_via_atoms(argc, argv)))
		return NULL;
    
	x = (t_hoa_meter_3d *)eobj_new(hoa_meter_3d_class);
    
    x->f_ramp = 0;
    x->f_signals = new t_float[MAX_SPEAKER * SYS_MAXBLKSIZE];
    x->f_over_leds = new int[MAX_CHANNELS];
    for(int i = 0; i < MAX_CHANNELS; i++)
        x->f_over_leds[i] = 0;
    x->f_clock = clock_new(x,(t_method)hoa_meter_3d_tick);
	x->f_startclock = 0;
    binbuf_get_attribute(d, gensym("@channels"), &ac, &av);
    if(ac && av)
    {
        x->f_meter  = new Hoa3D::Meter(atom_getlong(av), 181, 360);
        x->f_vector = new Hoa3D::Vector(atom_getlong(av));
        free(av);
    }
    else
    {
        x->f_meter  = new Hoa3D::Meter(8, 181, 360);
        x->f_vector = new Hoa3D::Vector(8);
    }
    
    eobj_dspsetup((t_ebox *)x, x->f_meter->getNumberOfChannels(), 0);
    
    flags = 0
    | EBOX_GROWINDI
    | EBOX_IGNORELOCKCLICK
    ;
	ebox_new((t_ebox *)x, flags);

    
    binbuf_get_attribute(d, gensym("@size"), &ac, &av);
    if(ac && av)
    {
        x->j_box.b_rect.width = atom_getfloat(av);
        x->j_box.b_rect.height = atom_getfloat(av+1);
        x->j_box.b_rect_last = x->j_box.b_rect;
        free(av);
    }
    
	ebox_attrprocess_viabinbuf(x, d);
    
	ebox_ready((t_ebox *)x);
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

void hoa_meter_3d_getdrawparams(t_hoa_meter_3d *x, t_object *patcherview, t_edrawparams *params)
{
    params->d_boxfillcolor = x->f_color_bg;
    params->d_bordercolor = x->f_color_bd;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

void hoa_meter_3d_oksize(t_hoa_meter_3d *x, t_rect *newrect)
{
    newrect->width = pd_clip_min(newrect->width, 20.);
    newrect->height = pd_clip_min(newrect->height, 20.);
    double delta1 = newrect->width - x->j_box.b_rect_last.width;
    double delta2 = newrect->height - x->j_box.b_rect_last.height;
    
    if(x->f_view == gensym("top-bottom"))
    {
        if(fabs(delta1) < fabs(delta2))
            newrect->width = newrect->height * 2;
        else
            newrect->height = newrect->width * 0.5;
    }
    else if(x->f_view == gensym("top/bottom"))
    {
        if(fabs(delta1) < fabs(delta2))
            newrect->width = newrect->height * 0.5;
        else
            newrect->height = newrect->width * 2;
    }
    else
    {
        if(fabs(delta1) < fabs(delta2))
            newrect->width = newrect->height;
        else
            newrect->height = newrect->width;
    }
    x->j_box.b_rect_last = *newrect;
}

t_pd_err channels_get(t_hoa_meter_3d *x, void *attr, long *argc, t_atom **argv)
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

t_pd_err channels_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_FLOAT)
        {
            long d = pd_clip_minmax(atom_getfloat(argv), 4, MAX_SPEAKER);
            if(d != x->f_meter->getNumberOfChannels())
            {
                int dspState = canvas_suspend_dsp();
                delete x->f_meter;
                delete x->f_vector;
                x->f_meter = new Meter(d, 181, 360);
                x->f_vector = new Vector(d);
                eobj_resize_inputs((t_ebox *)x, x->f_meter->getNumberOfChannels());
                canvas_resume_dsp(dspState);
            }
        }
    }
    return NULL;
}

t_pd_err angles_get(t_hoa_meter_3d *x, void *attr, long *argc, t_atom **argv)
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
    return 0;
}

t_pd_err angles_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv)
{
    double azimuths[MAX_SPEAKER];
	double elevations[MAX_SPEAKER];
    if(argc > MAX_SPEAKER)
        argc = MAX_SPEAKER;
	
    if(argc && argv)
    {
		for(int i = 0, j = 0; i < x->f_meter->getNumberOfChannels(); i++, j+=2)
        {
            if(j < argc-1 && atom_gettype(argv+j) == A_FLOAT && atom_gettype(argv+j+1) == A_FLOAT)
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
	
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_background_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_leds_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_vector_layer);
    
	ebox_redraw((t_ebox *)x);
    return 0;
}

t_pd_err offset_get(t_hoa_meter_3d *x, void *attr, long *argc, t_atom **argv)
{
    argc[0] = 3;
    argv[0] = (t_atom *)malloc(3 * sizeof(t_atom));
    if(argv[0] && argc[0])
    {
       // atom_setfloat(argv[0], x->f_meter->getChannelsOffset() / HOA_2PI * 360.);
		argc[0] = 3;
        argv[0] = argv[2] = argv[2] = 0;
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return 0;
}

t_pd_err offset_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_FLOAT)
    {
     
       // x->f_meter->setChannelsOffset(atom_getfloat(argv) / 360 * HOA_2PI);
    }
    
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_background_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_leds_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_vector_layer);
    
	ebox_redraw((t_ebox *)x);
    return 0;
}

t_pd_err vectors_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv)
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
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_vector_layer);
    }
    return 0;
}

t_pd_err rotation_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv)
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

t_pd_err view_set(t_hoa_meter_3d *x, void *attr, long argc, t_atom *argv)
{
    t_symbol* view = x->f_view;
    if(argc && argv)
    {
        
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == hoa_sym_3d_bottom)
                view = hoa_sym_3d_bottom;
            else if(atom_getsym(argv) == hoa_sym_3d_topnextbottom)
                view = hoa_sym_3d_topnextbottom;
            else if(atom_getsym(argv) == hoa_sym_3d_toponbottom)
                view = hoa_sym_3d_toponbottom;
            else
                view = hoa_sym_3d_top;
        }
        else if(atom_gettype(argv) == A_FLOAT)
        {
            if(atom_getlong(argv) == 1)
                view = hoa_sym_3d_bottom;
            else if(atom_getlong(argv) == 2)
                view = hoa_sym_3d_topnextbottom;
            else if(atom_getlong(argv) == 3)
                view = hoa_sym_3d_toponbottom;
            else
                view = hoa_sym_3d_top;
        }
        if(view != x->f_view)
        {
            x->f_view = view;
            x->j_box.b_rect_last = x->j_box.b_rect;
            object_attr_setvalueof((t_object *)x, gensym("size"), 0, NULL);
        }
    }
    return 0;
}

void hoa_meter_3d_dsp(t_hoa_meter_3d *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_meter->setVectorSize(maxvectorsize);
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_meter_3d_perform, 0, NULL);
	x->f_startclock = 1;
}

void hoa_meter_3d_perform(t_hoa_meter_3d *x, t_object *dsp, float **ins, long numins, float **outs, long no, long sampleframes, long f,void *up)
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
    
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_leds_layer);
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_vector_layer);
  	ebox_redraw((t_ebox *)x);
    
	if (sys_getdspstate())
		clock_delay(x->f_clock, x->f_interval);
}

void hoa_meter_3d_free(t_hoa_meter_3d *x)
{
	ebox_free((t_ebox *)x);
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

t_pd_err hoa_meter_3d_notify(t_hoa_meter_3d *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("attr_modified"))
	{
		ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_background_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_leds_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_3d_vector_layer);
		ebox_redraw((t_ebox *)x);
	}
	return 0;
}

void hoa_meter_3d_paint(t_hoa_meter_3d *x, t_object *view)
{
	t_rect rect;
	ebox_get_rect_for_view((t_ebox *)x, &rect);
	
    if(x->f_view == hoa_sym_3d_topnextbottom)
        x->f_center = rect.width * .25;
    else
        x->f_center = rect.width * .5;
	x->f_radius = x->f_center * 0.95;
	
	draw_background(x, view, &rect);
    draw_leds(x, view, &rect);
    draw_vectors(x, view, &rect);
}

void draw_background(t_hoa_meter_3d *x,  t_object *view, t_rect *rect)
{
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_3d_background_layer, rect->width, rect->height);
    t_rgba black, white;
    black = rgba_addContrast(x->f_color_bg, -contrast_black);
    white = rgba_addContrast(x->f_color_bg, contrast_white);
    
	if (g)
	{
        if(x->f_view == hoa_sym_3d_topnextbottom)
        {
            egraphics_set_color_rgba(g, &white);
            egraphics_set_line_width(g, 3.);
            egraphics_arc(g, x->f_center, x->f_center, x->f_radius,  0., HOA_2PI);
            egraphics_stroke(g);
            egraphics_set_color_rgba(g, &black);
            egraphics_set_line_width(g, 1.);
            egraphics_stroke(g);
            
            egraphics_set_color_rgba(g, &white);
            egraphics_set_line_width(g, 3.);
            egraphics_line_fast(g, x->f_center * 2, 0, x->f_center * 2, x->f_center * 2);
            egraphics_set_color_rgba(g, &black);
            egraphics_set_line_width(g, 1.);
            egraphics_line_fast(g, x->f_center * 2, 0, x->f_center * 2, x->f_center * 2);
            
            egraphics_set_color_rgba(g, &white);
            egraphics_set_line_width(g, 3.);
            egraphics_arc(g, x->f_center * 3, x->f_center, x->f_radius,  0., HOA_2PI);
            egraphics_stroke(g);
            egraphics_set_color_rgba(g, &black);
            egraphics_set_line_width(g, 1.);
            egraphics_stroke(g);
        }
        else if(x->f_view == hoa_sym_3d_toponbottom)
        {
            egraphics_set_color_rgba(g, &white);
            egraphics_set_line_width(g, 3.);
            egraphics_arc(g, x->f_center, x->f_center, x->f_radius,  0., HOA_2PI);
            egraphics_stroke(g);
            egraphics_set_color_rgba(g, &black);
            egraphics_set_line_width(g, 1.);
            egraphics_stroke(g);
            
            egraphics_set_color_rgba(g, &white);
            egraphics_set_line_width(g, 3.);
            egraphics_line_fast(g, 0, x->f_center * 2, x->f_center * 2, x->f_center * 2);
            egraphics_set_color_rgba(g, &black);
            egraphics_set_line_width(g, 1.);
            egraphics_line_fast(g, 0, x->f_center * 2, x->f_center * 2, x->f_center * 2);
            
            egraphics_set_color_rgba(g, &white);
            egraphics_set_line_width(g, 3.);
            egraphics_arc(g, x->f_center, x->f_center * 3, x->f_radius,  0., HOA_2PI);
            egraphics_stroke(g);
            egraphics_set_color_rgba(g, &black);
            egraphics_set_line_width(g, 1.);
            egraphics_stroke(g);
        }
        else
        {
            egraphics_set_color_rgba(g, &white);
            egraphics_set_line_width(g, 3.);
            egraphics_arc(g, x->f_center, x->f_center, x->f_radius,  0., HOA_2PI);
            egraphics_stroke(g);
            egraphics_set_color_rgba(g, &black);
            egraphics_set_line_width(g, 1.);
            egraphics_stroke(g);
		}
        ebox_end_layer((t_ebox*)x, hoa_sym_3d_background_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_3d_background_layer, 0., 0.);
}

void draw_leds(t_hoa_meter_3d *x, t_object *view, t_rect *rect)
{
    t_matrix transform;
    t_rgba black = rgba_addContrast(x->f_color_bg, -contrast_black);
    t_rgba white = rgba_addContrast(x->f_color_bg, contrast_white);
	t_elayer *g = ebox_start_layer((t_ebox *)x,  hoa_sym_3d_leds_layer, rect->width, rect->height);
    t_rgba mcolor;
    bool viewd = 1;
    if(x->f_view == hoa_sym_3d_bottom)
        viewd = 0;
	if (g)
	{
		egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
        egraphics_set_matrix(g, &transform);
        
		for(int i = 0; i < x->f_meter->getNumberOfChannels(); i++)
		{
            if(x->f_over_leds[i])
                 mcolor = x->f_color_over_signal;
            else if(x->f_meter->getChannelEnergy(i) < -25.5)
                mcolor = x->f_color_cold_signal;
            else if(x->f_meter->getChannelEnergy(i) >= -25.5 && x->f_meter->getChannelEnergy(i) < -16.5)
                mcolor = x->f_color_tepid_signal;
            else if(x->f_meter->getChannelEnergy(i) >= -16.5 && x->f_meter->getChannelEnergy(i) < -7.5)
                mcolor = x->f_color_warm_signal;
            else
                mcolor = x->f_color_hot_signal;
            
            egraphics_set_color_rgba(g, &mcolor);
            int npt = x->f_meter->getChannelNumberOfPoints(i, viewd);
            int factor = pd_clip_min(sqrt((rect->width * 100)) / (double)(npt * 0.1) - 1, 1);
			if(npt)
			{
				float azi = x->f_meter->getChannelPointAzimuth(i, 0, viewd);
                if(x->f_clockwise == hoa_sym_3d_clockwise)
                    azi =-azi;
				float ele = x->f_meter->getChannelPointElevation(i, 0, viewd);
				float abs = abscissa(x->f_radius, azi, ele);
				float ord = ordinate(x->f_radius, azi, ele);
                
				egraphics_move_to(g, abs, ord);
				for(int j = factor; j < npt; j += factor)
				{
					azi = x->f_meter->getChannelPointAzimuth(i, j, viewd);
                    if(x->f_clockwise == hoa_sym_3d_clockwise)
                        azi =-azi;
                    
					ele = x->f_meter->getChannelPointElevation(i, j, viewd);
					abs =  abscissa(x->f_radius, azi, ele);
					ord = ordinate(x->f_radius, azi, ele);
					egraphics_line_to(g, abs, ord);

				}
                egraphics_set_line_splinestep(g, 1000.);
				egraphics_close_path(g);
				egraphics_fill_preserve(g);
				
				egraphics_set_color_rgba(g, &white);
				egraphics_set_line_width(g, 3);
				egraphics_stroke(g);
                
                egraphics_set_color_rgba(g, &black);
				egraphics_set_line_width(g, 1);
				egraphics_stroke(g);
			}

		}
        
        if(x->f_view == hoa_sym_3d_toponbottom || x->f_view == hoa_sym_3d_topnextbottom)
        {
            viewd = 0;
            if(x->f_view == hoa_sym_3d_toponbottom)
                egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center * 3);
            else
                egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center * 3, x->f_center);
            
            egraphics_set_matrix(g, &transform);
            
            for(int i = 0; i < x->f_meter->getNumberOfChannels(); i++)
            {
                if(x->f_over_leds[i])
                    mcolor = x->f_color_over_signal;
                else if(x->f_meter->getChannelEnergy(i) < -25.5)
                    mcolor = x->f_color_cold_signal;
                else if(x->f_meter->getChannelEnergy(i) >= -25.5 && x->f_meter->getChannelEnergy(i) < -16.5)
                    mcolor = x->f_color_tepid_signal;
                else if(x->f_meter->getChannelEnergy(i) >= -16.5 && x->f_meter->getChannelEnergy(i) < -7.5)
                    mcolor = x->f_color_warm_signal;
                else
                    mcolor = x->f_color_hot_signal;
                
                egraphics_set_color_rgba(g, &mcolor);
                int npt = x->f_meter->getChannelNumberOfPoints(i, viewd);
                int factor = pd_clip_min(sqrt((rect->width * 100)) / (double)(npt * 0.1) - 1, 1);
                if(npt)
                {
                    float azi = x->f_meter->getChannelPointAzimuth(i, 0, viewd);
                    if(x->f_clockwise == hoa_sym_3d_clockwise)
                        azi =-azi;
                    float ele = x->f_meter->getChannelPointElevation(i, 0, viewd);
                    float abs = abscissa(x->f_radius, azi, ele);
                    float ord = ordinate(x->f_radius, azi, ele);
                    
                    egraphics_move_to(g, abs, ord);
                    for(int j = factor; j < npt; j += factor)
                    {
                        azi = x->f_meter->getChannelPointAzimuth(i, j, viewd);
                        if(x->f_clockwise == hoa_sym_3d_clockwise)
                            azi =-azi;
                        
                        ele = x->f_meter->getChannelPointElevation(i, j, viewd);
                        abs =  abscissa(x->f_radius, azi, ele);
                        ord = ordinate(x->f_radius, azi, ele);
                        egraphics_line_to(g, abs, ord);
                        
                    }
                    egraphics_set_line_splinestep(g, 1000.);
                    egraphics_close_path(g);
                    egraphics_fill_preserve(g);
                    
                    egraphics_set_color_rgba(g, &white);
                    egraphics_set_line_width(g, 3);
                    egraphics_stroke(g);
                    
                    egraphics_set_color_rgba(g, &black);
                    egraphics_set_line_width(g, 1);
                    egraphics_stroke(g);
                }
                
            }
        }
		ebox_end_layer((t_ebox*)x,  hoa_sym_3d_leds_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_3d_leds_layer, 0., 0.);
}

void draw_vectors(t_hoa_meter_3d *x, t_object *view, t_rect *rect)
{
	double x1, y1, size;
	t_matrix transform;
	t_elayer *g = ebox_start_layer((t_ebox *)x,  hoa_sym_3d_vector_layer, rect->width, rect->height);
	t_rgba color;
    double distance;
	if (g)
	{
        egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
        egraphics_set_matrix(g, &transform);
		size = x->f_center / 32.;
        
        if(x->f_vector_type == hoa_sym_3d_both || x->f_vector_type == hoa_sym_3d_energy)
        {
            double rad = radius(x->f_vector_coords[3], x->f_vector_coords[4], x->f_vector_coords[5]);
            distance = (fabs(rad) * 0.5 + 0.5);
            color = rgba_addContrast(x->f_color_energy_vector, -(1. - distance));
            egraphics_set_color_rgba(g, &color);
            if(x->f_clockwise == hoa_sym_3d_anticlock)
            {
                x1 = x->f_vector_coords[3] * x->f_radius;
                y1 = x->f_vector_coords[4] * x->f_radius;
            }
            else
            {
                double ang = -azimuth(x->f_vector_coords[3], x->f_vector_coords[4], x->f_vector_coords[5]);
                x1 = abscissa(rad * x->f_radius, ang);
                y1 = ordinate(rad * x->f_radius, ang);
            }
            
            if((x->f_vector_coords[5] >= 0 && (x->f_view == hoa_sym_3d_top || x->f_view == hoa_sym_3d_toponbottom || x->f_view == hoa_sym_3d_topnextbottom)) ||  (x->f_vector_coords[5] <= 0 && x->f_view == hoa_sym_3d_bottom))
            {
                egraphics_arc(g, x1, y1, size * distance, 0., HOA_2PI);
                egraphics_fill(g);
            }
            else if(x->f_vector_coords[5] <= 0 && x->f_view == hoa_sym_3d_toponbottom)
            {
                egraphics_arc(g, x1, y1 - x->f_center * 2, size * distance, 0., HOA_2PI);
                egraphics_fill(g);
            }
            else if(x->f_vector_coords[5] <= 0 && x->f_view == hoa_sym_3d_topnextbottom)
            {
                egraphics_arc(g, x1 + x->f_center * 2, y1, size * distance, 0., HOA_2PI);
                egraphics_fill(g);
            }
		}
        if(x->f_vector_type == hoa_sym_3d_both || x->f_vector_type == hoa_sym_3d_velocity)
        {
            double rad = radius(x->f_vector_coords[0], x->f_vector_coords[1], x->f_vector_coords[2]);
            distance = (fabs(rad) * 0.5 + 0.5);
            color = rgba_addContrast(x->f_color_velocity_vector, -(1. - distance));
            egraphics_set_color_rgba(g, &color);
            if(x->f_clockwise == hoa_sym_3d_anticlock)
            {
                x1 = x->f_vector_coords[0] * x->f_radius;
                y1 = x->f_vector_coords[1] * x->f_radius;
            }
            else
            {
                double ang = -azimuth(x->f_vector_coords[0], x->f_vector_coords[1], x->f_vector_coords[2]);
                x1 = abscissa(rad * x->f_radius, ang);
                y1 = ordinate(rad * x->f_radius, ang);
            }
            
            if((x->f_vector_coords[2] >= 0 && (x->f_view == hoa_sym_3d_top || x->f_view == hoa_sym_3d_toponbottom || x->f_view == hoa_sym_3d_topnextbottom)) ||  (x->f_vector_coords[2] <= 0 && x->f_view == hoa_sym_3d_bottom))
            {
                egraphics_arc(g, x1, y1, size * distance, 0., HOA_2PI);
                egraphics_fill(g);
            }
            else if(x->f_vector_coords[2] <= 0 && x->f_view == hoa_sym_3d_toponbottom)
            {
                egraphics_arc(g, x1, y1 - x->f_center * 2, size * distance, 0., HOA_2PI);
                egraphics_fill(g);
            }
            else if(x->f_vector_coords[2] <= 0 && x->f_view == hoa_sym_3d_topnextbottom)
            {
                egraphics_arc(g, x1 + x->f_center * 2, y1, size * distance, 0., HOA_2PI);
                egraphics_fill(g);
            }
		}
        
		ebox_end_layer((t_ebox*)x,  hoa_sym_3d_vector_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_3d_vector_layer, 0., 0.);
}

