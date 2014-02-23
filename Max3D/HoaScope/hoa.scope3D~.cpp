/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../../hoa.max.h"
#include "../../Sources/HoaOpenGL/OpenGLTools.h"
#include "../../MaxJuceBox/jucebox_wrapper.h"

typedef struct _hoa_scope
{
	t_jucebox	j_box;

    Hoa3D::Scope*   f_scope;
    long            f_order;
    double*         f_signals;
    double          f_gain;
    
    int             f_index;
    void*           f_clock;
	int             f_startclock;
    long            f_interval;
    
    long            f_vectors;
    long            f_sphere;
    t_jrgba         f_color_bg;
	t_jrgba         f_color_bd;
    t_jrgba         f_color_ph;
    t_jrgba         f_color_nh;
	t_jrgba         f_color_sp;

	double          f_camera[2];
    double          f_camera_ref[2];
    t_pt            f_mouse;
} t_hoa_scope;

t_class *hoa_scope_class;

void *hoa_scope_new(t_symbol *s, long argc, t_atom *argv);
void hoa_scope_free(t_hoa_scope *x);
void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s);
void hoa_scope_paint(t_hoa_scope *x, double w, double h);
void hoa_scope_tick(t_hoa_scope *x);

void hoa_scope_getdrawparams(t_hoa_scope *x, t_object *patcherview, t_jboxdrawparams *params);
t_max_err hoa_scope_notify(t_hoa_scope *x, t_symbol *s, t_symbol *m, void *sender, void *data);

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_scope_mousedown(t_hoa_scope *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_scope_mousedrag(t_hoa_scope *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err hoa_scope_attr_set_order(t_hoa_scope *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoa_scope_attr_set_camera(t_hoa_scope *x, t_object *attr, long argc, t_atom *argv);
t_hoa_err hoa_getinfos(t_hoa_scope* x, t_hoa_boxinfos* boxinfos);

int C74_EXPORT main(void)
{
	t_class *c;
    
	c = class_new("hoa.scope3D~", (method)hoa_scope_new, (method)hoa_scope_free, sizeof(t_hoa_scope), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	
    class_dspinitjbox(c);
    jucebox_initclass(c, (method)hoa_scope_paint,  JBOX_COLOR | JBOX_FIXWIDTH);
    hoa_initclass(c, (method)hoa_getinfos);
    
	class_addmethod(c, (method)hoa_scope_dsp64,				"dsp64",            A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_mousedown,			"mousedown",        A_CANT, 0);
    class_addmethod(c, (method)hoa_scope_mousedrag,			"mousedrag",        A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_assist,			"assist",           A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_getdrawparams,		"getdrawparams",    A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_notify,			"notify",           A_CANT, 0);
	
    CLASS_ATTR_DEFAULT              (c, "patching_rect", 0, "0 0 200 200");
    CLASS_ATTR_INVISIBLE            (c, "color", 0);
    
    CLASS_ATTR_LONG                 (c, "order", 0, t_hoa_scope, f_order);
    CLASS_ATTR_ACCESSORS            (c, "order", NULL,  hoa_scope_attr_set_order);
	CLASS_ATTR_CATEGORY             (c, "order", 0, "Ambisonic");
	CLASS_ATTR_ORDER                (c, "order", 0, "1");
	CLASS_ATTR_LABEL                (c, "order", 0, "Order");
	CLASS_ATTR_FILTER_MIN           (c, "order", 1);
	CLASS_ATTR_DEFAULT              (c, "order", 0, "1");
	CLASS_ATTR_SAVE                 (c, "order", 1);
    CLASS_ATTR_PAINT                (c, "order", 1);
    
    CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_scope, f_interval);
	CLASS_ATTR_CATEGORY             (c, "interval", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "interval", 0, "1");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "100");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
    
    CLASS_ATTR_DOUBLE               (c, "gain", 0, t_hoa_scope, f_gain);
	CLASS_ATTR_CATEGORY             (c, "gain", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "gain", 0, "2");
	CLASS_ATTR_LABEL                (c, "gain", 0, "Gain factor");
	CLASS_ATTR_FILTER_MIN           (c, "gain", 1.);
	CLASS_ATTR_DEFAULT              (c, "gain", 0, "1.");
	CLASS_ATTR_SAVE                 (c, "gain", 1);
    
    CLASS_ATTR_RGBA                 (c, "bgcolor", 0, t_hoa_scope, f_color_bg);
	CLASS_ATTR_CATEGORY             (c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER                (c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bgcolor", 0, "0.9 0.9 0.9 1.");
	
	CLASS_ATTR_RGBA                 (c, "bdcolor", 0, t_hoa_scope, f_color_bd);
	CLASS_ATTR_CATEGORY             (c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER                (c, "bdcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bdcolor", 0, "0.1 0.1 0.1 1.");
	
    CLASS_ATTR_RGBA                 (c, "phcolor", 0, t_hoa_scope, f_color_ph);
	CLASS_ATTR_CATEGORY             (c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "phcolor", 0, "Positive Harmonics Color");
	CLASS_ATTR_ORDER                (c, "phcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "phcolor", 0, "1. 0. 0. 1.");
	
	CLASS_ATTR_RGBA                 (c, "nhcolor", 0, t_hoa_scope, f_color_nh);
	CLASS_ATTR_CATEGORY             (c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "nhcolor", 0, "Negative Harmonics Color");
	CLASS_ATTR_ORDER                (c, "nhcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "nhcolor", 0, "0. 0. 1. 1.");
    
	CLASS_ATTR_RGBA                 (c, "spcolor", 0, t_hoa_scope, f_color_sp);
	CLASS_ATTR_CATEGORY             (c, "spcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "spcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "spcolor", 0, "Sphere Color");
	CLASS_ATTR_ORDER                (c, "spcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "spcolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_DOUBLE_ARRAY         (c, "camera", 0, t_hoa_scope, f_camera, 2);
	CLASS_ATTR_CATEGORY             (c, "camera", 0, "Rendering Context");
    CLASS_ATTR_ORDER                (c, "camera", 0, "1");
	CLASS_ATTR_LABEL                (c, "camera", 0, "Camera");
	CLASS_ATTR_DEFAULT_SAVE         (c, "camera", 0, "0. 0.");
	CLASS_ATTR_ACCESSORS            (c, "camera", NULL, hoa_scope_attr_set_camera);
    CLASS_ATTR_PAINT                (c, "camera", 1);
    
    CLASS_ATTR_ATOM_LONG            (c, "vectors", 0, t_hoa_scope, f_vectors);
	CLASS_ATTR_CATEGORY             (c, "vectors", 0, "Rendering Context");
	CLASS_ATTR_ORDER                (c, "vectors", 0, "2");
	CLASS_ATTR_STYLE_LABEL          (c, "vectors", 0, "onoff", "Draw Vectors");
	CLASS_ATTR_DEFAULT              (c, "vectors", 0, "1");
	CLASS_ATTR_SAVE                 (c, "vectors", 1);
    CLASS_ATTR_PAINT                (c, "vectors", 1);
    
    CLASS_ATTR_ATOM_LONG            (c, "sphere", 0, t_hoa_scope, f_sphere);
	CLASS_ATTR_CATEGORY             (c, "sphere", 0, "Rendering Context");
	CLASS_ATTR_ORDER                (c, "sphere", 0, "3");
    CLASS_ATTR_STYLE_LABEL          (c, "sphere", 0, "onoff", "Draw Sphere");
	CLASS_ATTR_DEFAULT              (c, "sphere", 0, "1");
	CLASS_ATTR_SAVE                 (c, "sphere", 1);
    CLASS_ATTR_PAINT                (c, "sphere", 1);
    
	class_register(CLASS_BOX, c);
	hoa_scope_class = c;
    
	return 0;
}

void *hoa_scope_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_scope *x    = NULL;
 	t_dictionary *d = NULL;
	long flags;
    
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
    
	x = (t_hoa_scope *)object_alloc(hoa_scope_class);
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
    
    dictionary_getlong(d, gensym("order"), (t_atom_long *)&x->f_order);
    x->f_scope      = new Hoa3D::Scope(x->f_order, 100, 199);
    x->f_order      = x->f_scope->getOrder();
    x->f_signals    = new double[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
    x->f_clock      = clock_new((void *)x, (method)hoa_scope_tick);
    x->f_startclock = 0;
    x->f_index      = 0;
    
    dsp_setupjbox((t_pxjbox *)x, x->f_scope->getNumberOfHarmonics());
	jucebox_new((t_jucebox *) x);
    
	attr_dictionary_process(x,d);
	jbox_ready((t_jbox *)x);
	return x;
}

t_max_err hoa_scope_attr_set_order(t_hoa_scope *x, t_object *attr, long ac, t_atom *av)
{
    long d;
    t_object *b = NULL;
	if (ac && av)
    {
        if(atom_gettype(av) == A_LONG)
        {
            d = Hoa3D::clip_min(long(atom_getlong(av)), long(1));
            if (d != x->f_order)
            {
                int dspState = sys_getdspobjdspstate((t_object*)x);
                if(dspState)
                    object_method(gensym("dsp")->s_thing, gensym("stop"));
                
                delete x->f_scope;
                delete [] x->f_signals;
                x->f_scope      = new Hoa3D::Scope(d, 100, 199);
                x->f_order      = x->f_scope->getOrder();
                x->f_signals    = new double[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
                
                object_obex_lookup(x, gensym("#B"), (t_object **)&b);
                object_method(b, gensym("dynlet_begin"));
                dsp_resize((t_pxobject*)x, x->f_scope->getNumberOfHarmonics());
                object_method(b, gensym("dynlet_end"));
                
                if(dspState)
                    object_method(gensym("dsp")->s_thing, gensym("start"));
            }
        }
	}
    
	return MAX_ERR_NONE;
}

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_index = 0;
    object_method(dsp64, gensym("dsp_add64"), x, hoa_scope_perform64, 0, NULL);
    x->f_startclock = 1;
}

void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
        cblas_dscal(numins, x->f_gain, x->f_signals+i, 1);
    }
    x->f_index = 0;
    while(--sampleframes)
    {
        x->f_index++;
    }
    if(x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void hoa_scope_tick(t_hoa_scope *x)
{
    x->f_scope->process(x->f_signals + x->f_index * x->f_scope->getNumberOfHarmonics());
    jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

t_max_err hoa_scope_attr_set_camera(t_hoa_scope *x, t_object *attr, long argc, t_atom *argv)
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

void hoa_scope_getdrawparams(t_hoa_scope *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_bordercolor = x->f_color_bd;
    params->d_boxfillcolor = x->f_color_bg;
	params->d_borderthickness = 1;
	params->d_cornersize = 4;
}

t_max_err hoa_scope_notify(t_hoa_scope *x, t_symbol *s, t_symbol *m, void *sender, void *data)
{
	return jbox_notify((t_jbox *)x, s, m, sender, data);
}

t_hoa_err hoa_getinfos(t_hoa_scope* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = x->f_scope->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_scope->getHarmonicsName(a).c_str());
}

void hoa_draw_sphere(t_jucebox *x, t_jrgba color)
{
    double one, cos_one, sin_one, two ,cos_two, sin_two;
    
    glColor4d(color.red, color.green, color.blue, color.alpha);
    for(int i = 1; i < 10; i++)
    {
        one  =   0;
        two = (double)i / 10. * CICM_PI;
        cos_two = cos(two);
        sin_two = sin(two);
        glBegin(GL_LINE_LOOP);
        for(int j = 0; j < 50; j++)
        {
            one  =   (double)j / 50. * CICM_2PI;
            cos_one = cos(one);
            sin_one = sin(one);
            glVertex3d(sin_two * cos_one, cos_two, sin_two * sin_one);
        }
        glEnd();
    }
    
    for(int j = 0; j < 20; j++)
    {
        one  =   (double)j / 20. * CICM_2PI;
        two  = 0.;
        cos_one = cos(one);
        sin_one = sin(one);
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < 25; i++)
        {
            two = (double)i / 20. * CICM_PI;
            cos_two = cos(two);
            sin_two = sin(two);
            glVertex3d(sin_two * cos_one, cos_two, sin_two * sin_one);
        }
        glEnd();
    }
    
}

void hoa_scope_paint(t_hoa_scope *x, double w, double h)
{
    int number_of_rows = x->f_scope->getNumberOfRows();
	int number_of_columns = x->f_scope->getNumberOfColumns();

	float value;
    float one, two;
	t_jrgba color_positive = x->f_color_ph;
	t_jrgba color_negative = x->f_color_nh;
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
    glLoadIdentity();
    glRotated(-x->f_camera[0] / CICM_2PI * 360., 0., 1., 0.);
    glRotated(x->f_camera[1] / CICM_2PI * 360., 1., 0., 0.);
	glPointSize(1.0f);
    
    if(x->f_sphere)
        hoa_draw_sphere((t_jucebox *)x, x->f_color_sp);
    
	glBegin(GL_LINE_LOOP);
    
	for(int i = 0; i < number_of_rows; i++)
    {
        one  =   0;
        two = (double)i / (double)(number_of_rows - 1) * CICM_PI;
        value = x->f_scope->getValue(i, 0);
        if(value < 0)
        {
            glColor4d(color_negative.red, color_negative.green, color_negative.blue, color_negative.alpha);
            value= -value;
        }
        else
            glColor4d(color_positive.red, color_positive.green, color_positive.blue, color_positive.alpha);
            
    
        glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
		
        for(int j = 1; j < number_of_columns; j++)
        {
            one  =   (double)j / (double)number_of_columns * CICM_2PI;
            value = x->f_scope->getValue(i, j);
            if(value < 0)
            {
                glColor4d(color_negative.red, color_negative.green, color_negative.blue, color_negative.alpha);
                value= -value;
            }
            else
                glColor4d(color_positive.red, color_positive.green, color_positive.blue, color_positive.alpha);
			
            glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
        }
        
        one  =   0;
        value = x->f_scope->getValue(i, 0);
        if(value < 0)
        {
            glColor4d(color_negative.red, color_negative.green, color_negative.blue, color_negative.alpha);
            value = -value;
        }
        else
           glColor4d(color_positive.red, color_positive.green, color_positive.blue, color_positive.alpha);
        
        glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
    }
	
	for(int j = 0; j < number_of_columns; j++)
    {
        one  =   (double)j / (double)number_of_columns * CICM_2PI;
        two  = 0.;
        value = x->f_scope->getValue(0, j);
        if(value < 0)
        {
            glColor4d(color_negative.red, color_negative.green, color_negative.blue, color_negative.alpha);
            value= -value;
        }
        else
           glColor4d(color_positive.red, color_positive.green, color_positive.blue, color_positive.alpha);
		
		glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
		
        for(int i = 1; i < number_of_rows; i++)
        {
            two = (double)i / (double)(number_of_rows - 1) * CICM_PI;
            value = x->f_scope->getValue(i, j);
            if(value < 0)
            {
                glColor4d(color_negative.red, color_negative.green, color_negative.blue, color_negative.alpha);
                value= -value;
            }
            else
               glColor4d(color_positive.red, color_positive.green, color_positive.blue, color_positive.alpha);
			
            glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
        }
    }
	glEnd();
}

void hoa_scope_mousedown(t_hoa_scope *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_rect rect;
    jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
    x->f_mouse = pt;
    x->f_camera_ref[0] = x->f_camera[0];
    x->f_camera_ref[1] = x->f_camera[1];
}

void hoa_scope_mousedrag(t_hoa_scope *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_atom av[2];
    t_rect rect;
    jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
    atom_setfloat(av, x->f_camera_ref[0] + (pt.x - x->f_mouse.x) / (rect.width * 0.5) * CICM_PI2);
    atom_setfloat(av+1, x->f_camera_ref[1] + (pt.y - x->f_mouse.y) / (-rect.height * 0.5) * CICM_PI2);
    object_method(x, gensym("camera"), 2, av);
}

void hoa_scope_free(t_hoa_scope *x)
{
    clock_free((t_object *)x->f_clock);
    dsp_freejbox((t_pxjbox *)x);
    jucebox_free((t_jucebox*)x);
	delete x->f_scope;
    delete [] x->f_signals;
}

