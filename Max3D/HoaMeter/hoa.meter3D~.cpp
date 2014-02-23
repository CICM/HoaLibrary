/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../../hoa.max.h"
#include "../../Sources/HoaOpenGL/OpenGLTools.h"
#include "../../MaxJuceBox/jucebox_wrapper.h"

typedef struct _hoa_meter
{
	t_jucebox	j_box;

    Hoa3D::Meter*   f_meter;
    long            f_number_of_loudspeakers;
    double*         f_signals;
    
    void*           f_clock;
	int             f_startclock;
    long            f_interval;
    
    t_jrgba         f_color_bg;
	t_jrgba         f_color_bd;
    t_jrgba         f_color_cold;
	t_jrgba         f_color_tepid;
	t_jrgba         f_color_warm;
	t_jrgba         f_color_hot;
	t_jrgba         f_color_over;

	double          f_camera[2];
    double          f_camera_ref[2];
    t_pt            f_mouse;
} t_hoa_meter;

t_class *hoa_meter_class;

void *hoa_meter_new(t_symbol *s, long argc, t_atom *argv);
void hoa_meter_free(t_hoa_meter *x);
void hoa_meter_assist(t_hoa_meter *x, void *b, long m, long a, char *s);
void hoa_meter_paint(t_hoa_meter *x, double w, double h);
void hoa_meter_tick(t_hoa_meter *x);

void hoa_meter_getdrawparams(t_hoa_meter *x, t_object *patcherview, t_jboxdrawparams *params);
t_max_err hoa_meter_notify(t_hoa_meter *x, t_symbol *s, t_symbol *m, void *sender, void *data);

void hoa_meter_dsp64(t_hoa_meter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_meter_perform64(t_hoa_meter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_meter_mousedown(t_hoa_meter *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_meter_mousedrag(t_hoa_meter *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err hoa_meter_attr_set_loudspeakers(t_hoa_meter *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoa_meter_attr_set_camera(t_hoa_meter *x, t_object *attr, long argc, t_atom *argv);
t_hoa_err hoa_getinfos(t_hoa_meter* x, t_hoa_boxinfos* boxinfos);

int C74_EXPORT main(void)
{
	t_class *c;
    
	c = class_new("hoa.meter3D~", (method)hoa_meter_new, (method)hoa_meter_free, sizeof(t_hoa_meter), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	
    class_dspinitjbox(c);
    jucebox_initclass(c, (method)hoa_meter_paint,  JBOX_COLOR | JBOX_FIXWIDTH);
    hoa_initclass(c, (method)hoa_getinfos);
    
	class_addmethod(c, (method)hoa_meter_dsp64,				"dsp64",            A_CANT, 0);
	class_addmethod(c, (method)hoa_meter_mousedown,			"mousedown",        A_CANT, 0);
    class_addmethod(c, (method)hoa_meter_mousedrag,			"mousedrag",        A_CANT, 0);
	class_addmethod(c, (method)hoa_meter_assist,			"assist",           A_CANT, 0);
	class_addmethod(c, (method)hoa_meter_getdrawparams,		"getdrawparams",    A_CANT, 0);
	class_addmethod(c, (method)hoa_meter_notify,			"notify",           A_CANT, 0);
	
    CLASS_ATTR_DEFAULT              (c, "patching_rect", 0, "0 0 200 200");
    CLASS_ATTR_INVISIBLE            (c, "color", 0);
    
    CLASS_ATTR_LONG                 (c, "loudspeakers", 0, t_hoa_meter, f_number_of_loudspeakers);
    CLASS_ATTR_ACCESSORS            (c, "loudspeakers", NULL,  hoa_meter_attr_set_loudspeakers);
	CLASS_ATTR_CATEGORY             (c, "loudspeakers", 0, "Planewaves");
	CLASS_ATTR_ORDER                (c, "loudspeakers", 0, "1");
	CLASS_ATTR_LABEL                (c, "loudspeakers", 0, "Number Of Loudspeakers");
	CLASS_ATTR_FILTER_MIN           (c, "loudspeakers", 1);
	CLASS_ATTR_DEFAULT              (c, "loudspeakers", 0, "8");
	CLASS_ATTR_SAVE                 (c, "loudspeakers", 1);
    CLASS_ATTR_PAINT                (c, "loudspeakers", 1);
    
    CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_meter, f_interval);
	CLASS_ATTR_CATEGORY             (c, "interval", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "interval", 0, "1");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "100");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
    
    CLASS_ATTR_RGBA                 (c, "bgcolor", 0, t_hoa_meter, f_color_bg);
	CLASS_ATTR_CATEGORY             (c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER                (c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bgcolor", 0, "0.9 0.9 0.9 1.");
	
	CLASS_ATTR_RGBA                 (c, "bdcolor", 0, t_hoa_meter, f_color_bd);
	CLASS_ATTR_CATEGORY             (c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER                (c, "bdcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bdcolor", 0, "0.1 0.1 0.1 1.");
	
    CLASS_ATTR_RGBA                 (c, "coldcolor", 0, t_hoa_meter, f_color_cold);
    CLASS_ATTR_CATEGORY             (c, "coldcolor", 0, "Color");
	CLASS_ATTR_LABEL                (c, "coldcolor", 0, "Cold Signal Color");
	CLASS_ATTR_ORDER                (c, "coldcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "coldcolor", 0, "0. 0.6 0. 0.8");
	
	CLASS_ATTR_RGBA                 (c, "tepidcolor", 0, t_hoa_meter, f_color_tepid);
    CLASS_ATTR_CATEGORY             (c, "tepidcolor", 0, "Color");
	CLASS_ATTR_LABEL                (c, "tepidcolor", 0, "Tepid Signal Color");
	CLASS_ATTR_ORDER                (c, "tepidcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "tepidcolor", 0, "0.6 0.73 0. 0.8");
	
	CLASS_ATTR_RGBA                 (c, "warmcolor", 0, t_hoa_meter, f_color_warm);
    CLASS_ATTR_CATEGORY             (c, "warmcolor", 0, "Color");
	CLASS_ATTR_LABEL                (c, "warmcolor", 0, "Warm Signal Color");
	CLASS_ATTR_ORDER                (c, "warmcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "warmcolor", 0, ".85 .85 0. 0.8");
	
	CLASS_ATTR_RGBA                 (c, "hotcolor", 0, t_hoa_meter, f_color_hot);
    CLASS_ATTR_CATEGORY             (c, "hotcolor", 0, "Color");
	CLASS_ATTR_LABEL                (c, "hotcolor", 0, "Hot Signal Color");
	CLASS_ATTR_ORDER                (c, "hotcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "hotcolor", 0, "1. 0.6 0. 0.8");
	
	CLASS_ATTR_RGBA                 (c, "overcolor", 0, t_hoa_meter, f_color_over);
    CLASS_ATTR_CATEGORY             (c, "overcolor", 0, "Color");
	CLASS_ATTR_LABEL                (c, "overcolor", 0, "Overload Signal Color");
	CLASS_ATTR_ORDER                (c, "overcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "overcolor", 0, "1. 0. 0. 0.8");
	
	CLASS_ATTR_DOUBLE_ARRAY         (c, "camera", 0, t_hoa_meter, f_camera, 2);
	CLASS_ATTR_CATEGORY             (c, "camera", 0, "Rendering Context");
    CLASS_ATTR_ORDER                (c, "camera", 0, "1");
	CLASS_ATTR_LABEL                (c, "camera", 0, "Camera");
	CLASS_ATTR_DEFAULT_SAVE         (c, "camera", 0, "0. 0.");
	CLASS_ATTR_ACCESSORS            (c, "camera", NULL, hoa_meter_attr_set_camera);
    CLASS_ATTR_PAINT                (c, "camera", 1);
    
	class_register(CLASS_BOX, c);
	hoa_meter_class = c;
    
	return 0;
}

void *hoa_meter_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_meter *x    = NULL;
 	t_dictionary *d = NULL;
	long flags;
    
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
    
	x = (t_hoa_meter *)object_alloc(hoa_meter_class);
	flags = 0
    | JBOX_DRAWFIRSTIN
    | JBOX_NODRAWBOX
    | JBOX_DRAWINLAST
    | JBOX_TRANSPARENT
    | JBOX_GROWY
    | JBOX_DRAWBACKGROUND
    ;
    
	jbox_new((t_jbox *)x, flags, argc, argv);
    x->j_box.j_box.z_box.b_firstin = (t_object *)x;
    
    dictionary_getlong(d, gensym("loudspeakers"), (t_atom_long *)&x->f_number_of_loudspeakers);
    x->f_meter      = new Hoa3D::Meter(x->f_number_of_loudspeakers, 100, 199);
    x->f_number_of_loudspeakers      = x->f_meter->getNumberOfLoudspeakers();
    x->f_signals    = new double[x->f_meter->getNumberOfLoudspeakers() * SYS_MAXBLKSIZE];
    x->f_clock      = clock_new((void *)x, (method)hoa_meter_tick);
    x->f_startclock = 0;
    
    dsp_setupjbox((t_pxjbox *)x, x->f_meter->getNumberOfLoudspeakers());
	jucebox_new((t_jucebox *) x);
    
	attr_dictionary_process(x,d);
	jbox_ready((t_jbox *)x);
	return x;
}

t_max_err hoa_meter_attr_set_loudspeakers(t_hoa_meter *x, t_object *attr, long ac, t_atom *av)
{
    long d;
    t_object *b = NULL;
	if (ac && av)
    {
        if(atom_gettype(av) == A_LONG)
        {
            d = Hoa3D::clip_min(long(atom_getlong(av)), long(1));
            if (d != x->f_number_of_loudspeakers)
            {
                int dspState = sys_getdspobjdspstate((t_object*)x);
                if(dspState)
                    object_method(gensym("dsp")->s_thing, gensym("stop"));
                
                delete x->f_meter;
                delete [] x->f_signals;
                x->f_meter      = new Hoa3D::Meter(x->f_number_of_loudspeakers, 100, 199);
                x->f_number_of_loudspeakers      = x->f_meter->getNumberOfLoudspeakers();
                x->f_signals    = new double[x->f_meter->getNumberOfLoudspeakers() * SYS_MAXBLKSIZE];
                
                object_obex_lookup(x, gensym("#B"), (t_object **)&b);
                object_method(b, gensym("dynlet_begin"));
                dsp_resize((t_pxobject*)x, x->f_meter->getNumberOfLoudspeakers());
                object_method(b, gensym("dynlet_end"));
                
                if(dspState)
                    object_method(gensym("dsp")->s_thing, gensym("start"));
            }
        }
	}
    
	return MAX_ERR_NONE;
}

void hoa_meter_dsp64(t_hoa_meter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_meter->setVectorSize(maxvectorsize);
    object_method(dsp64, gensym("dsp_add64"), x, hoa_meter_perform64, 0, NULL);
    x->f_startclock = 1;
}

void hoa_meter_perform64(t_hoa_meter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_meter->process(x->f_signals + numouts * i);
    }
    if(x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void hoa_meter_tick(t_hoa_meter *x)
{
    jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

t_max_err hoa_meter_attr_set_camera(t_hoa_meter *x, t_object *attr, long argc, t_atom *argv)
{
	if(argc && argv)
    {
		for(int i = 0; i < 2 && i < argc; i++)
		{
            if(atom_gettype(argv+i) == A_FLOAT)
                x->f_camera[i] = Hoa3D::wrap(atom_getfloat(argv+i), -CICM_PI, CICM_PI);
		}
    }
    return MAX_ERR_NONE;
}

void hoa_meter_getdrawparams(t_hoa_meter *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_bordercolor = x->f_color_bd;
    params->d_boxfillcolor = x->f_color_bg;
	params->d_borderthickness = 1;
	params->d_cornersize = 4;
}

t_max_err hoa_meter_notify(t_hoa_meter *x, t_symbol *s, t_symbol *m, void *sender, void *data)
{
	return jbox_notify((t_jbox *)x, s, m, sender, data);
}

t_hoa_err hoa_getinfos(t_hoa_meter* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = x->f_meter->getNumberOfLoudspeakers();
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_PLANEWAVES;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_meter_assist(t_hoa_meter *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_meter->getLoudspeakerName(a).c_str());
}

void hoa_meter_paint(t_hoa_meter *x, double w, double h)
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
    glLoadIdentity();
    glRotated(180., 0., 1., 0.);
    glRotated(-x->f_camera[0] / CICM_2PI * 360., 0., 1., 0.);
    glRotated(x->f_camera[1] / CICM_2PI * 360., 1., 0., 0.);
	glPointSize(1.0f);
    
    
}

void hoa_meter_mousedown(t_hoa_meter *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_rect rect;
    jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
    x->f_mouse = pt;
    x->f_camera_ref[0] = x->f_camera[0];
    x->f_camera_ref[1] = x->f_camera[1];
}

void hoa_meter_mousedrag(t_hoa_meter *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_atom av[2];
    t_rect rect;
    jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
    atom_setfloat(av, x->f_camera_ref[0] + (pt.x - x->f_mouse.x) / (rect.width * 0.5) * CICM_PI2);
    atom_setfloat(av+1, x->f_camera_ref[1] + (pt.y - x->f_mouse.y) / (-rect.height * 0.5) * CICM_PI2);
    object_method(x, gensym("camera"), 2, av);
}

void hoa_meter_free(t_hoa_meter *x)
{
    clock_free((t_object *)x->f_clock);
    dsp_freejbox((t_pxjbox *)x);
    jucebox_free((t_jucebox*)x);
	delete x->f_meter;
    delete [] x->f_signals;
}

