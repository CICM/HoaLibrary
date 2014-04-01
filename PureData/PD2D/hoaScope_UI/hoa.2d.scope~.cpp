/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.pd.h"

typedef struct  _hoa_scope
{
	t_edspbox   j_box;
    Hoa2D::Scope*   f_scope;
    int             f_index;
	t_clock*        f_clock;
	int             f_startclock;
	long            f_interval;
	long            f_order;
    float           f_gain;
	
	t_rgba          f_color_bg;
    t_rgba          f_color_bd;
	t_rgba          f_color_nh;
	t_rgba          f_color_ph;
	
	double          f_center;
	double          f_radius;
    t_float*        f_signals;
   
} t_hoa_scope;

t_eclass *scope_class;

void *hoa_scope_new(t_symbol *s, int argc, t_atom *argv);
void hoa_scope_free(t_hoa_scope *x);
void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s);
void hoa_scope_tick(t_hoa_scope *x);

void hoa_scope_dsp(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_scope_perform(t_hoa_scope *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

t_pd_err hoa_scope_notify(t_hoa_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
long hoa_scope_oksize(t_hoa_scope *x, t_rect *newrect);
void hoa_scope_getdrawparams(t_hoa_scope *x, t_object *patcherview, t_edrawparams *params);

void hoa_scope_paint(t_hoa_scope *x, t_object *view);
void draw_background(t_hoa_scope *x, t_object *view, t_rect *rect);
void draw_harmonics(t_hoa_scope *x,  t_object *view, t_rect *rect);

t_pd_err    set_order(t_hoa_scope *x, t_object *attr, long ac, t_atom *av);
t_hoa_err hoa_getinfos(t_hoa_scope* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_scope_class;

#define  contrast_white 0.06
#define  contrast_black 0.14

extern "C" void setup_hoa0x2e2d0x2escope_tilde(void)
{
	t_eclass *c;

	c = eclass_new("hoa.2d.scope~", (method)hoa_scope_new, (method)hoa_scope_free, (short)sizeof(t_hoa_scope), 0L, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_scope_new, gensym("hoa.scope~"), A_GIMME);
    
    eclass_dspinit(c);
    eclass_init(c, 0);
	hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)hoa_scope_dsp,			"dsp",          A_CANT, 0);
	eclass_addmethod(c, (method)hoa_scope_assist,		"assist",		A_CANT,	0);
	eclass_addmethod(c, (method)hoa_scope_paint,		"paint",		A_CANT,	0);
	eclass_addmethod(c, (method)hoa_scope_notify,		"notify",		A_CANT, 0);
	eclass_addmethod(c, (method)hoa_scope_getdrawparams,"getdrawparams", A_CANT, 0);
	eclass_addmethod(c, (method)hoa_scope_oksize,		"oksize",		A_CANT, 0);

    CLASS_ATTR_INVISIBLE            (c, "fontname", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontweight", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontslant", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontsize", 1);
    CLASS_ATTR_INVISIBLE            (c, "send", 1);
	CLASS_ATTR_DEFAULT              (c, "size", 0, "225. 225.");

    CLASS_ATTR_LONG                 (c, "order", 0, t_hoa_scope, f_order);
    CLASS_ATTR_ACCESSORS            (c, "order", NULL, set_order);
	CLASS_ATTR_CATEGORY             (c, "order", 0, "Ambisonic");
	CLASS_ATTR_ORDER                (c, "order", 0, "1");
	CLASS_ATTR_LABEL                (c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_FILTER_MIN           (c, "order", 1);
	CLASS_ATTR_DEFAULT              (c, "order", 0, "1");
	CLASS_ATTR_SAVE                 (c, "order", 1);
    
    CLASS_ATTR_FLOAT                (c, "gain", 0, t_hoa_scope, f_gain);
	CLASS_ATTR_CATEGORY             (c, "gain", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "gain", 0, "1");
	CLASS_ATTR_LABEL                (c, "gain", 0, "Gain");
	CLASS_ATTR_FILTER_MIN           (c, "gain", 1.);
	CLASS_ATTR_DEFAULT              (c, "gain", 0, "1.");
	CLASS_ATTR_SAVE                 (c, "gain", 1);
    
	CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_scope, f_interval);
	CLASS_ATTR_CATEGORY             (c, "interval", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "interval", 0, "2");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "100");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
	
	CLASS_ATTR_RGBA                 (c, "bgcolor", 0, t_hoa_scope, f_color_bg);
	CLASS_ATTR_CATEGORY             (c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER                (c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bgcolor", 0, "0.76 0.76 0.76 1.");
    
    CLASS_ATTR_RGBA                 (c, "bdcolor", 0, t_hoa_scope, f_color_bd);
	CLASS_ATTR_CATEGORY             (c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER                (c, "bdcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bdcolor", 0, "0.7 0.7 0.7 1.");
	
	CLASS_ATTR_RGBA                 (c, "phcolor", 0, t_hoa_scope, f_color_ph);
	CLASS_ATTR_CATEGORY             (c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "phcolor", 0, "Positive Harmonics Color");
	CLASS_ATTR_ORDER                (c, "phcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "phcolor", 0, "1. 0. 0. 1.");
	
	CLASS_ATTR_RGBA                 (c, "nhcolor", 0, t_hoa_scope, f_color_nh);
	CLASS_ATTR_CATEGORY             (c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "nhcolor", 0, "Negative Harmonics Color");
	CLASS_ATTR_ORDER                (c, "nhcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "nhcolor", 0, "0. 0. 1. 1.");
    
    eclass_register(CLASS_BOX, c);
    scope_class = c;
}

void *hoa_scope_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_scope *x =  NULL;
	t_binbuf *d;
	long flags;
	
	if (!(d = binbuf_via_atoms(argc, argv)))
		return NULL;

	x = (t_hoa_scope *)eobj_new(scope_class);
    
    x->f_order      = 1;
	x->f_startclock = 0;
	x->f_scope      = new Hoa2D::Scope(x->f_order, NUMBEROFCIRCLEPOINTS_UI2);
    x->f_order      = x->f_scope->getOrder();
    x->f_signals    = new t_float[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
    x->f_index      = 0;
    
    eobj_dspsetup(x, x->f_scope->getNumberOfHarmonics(), 0);
    
	flags = 0
    | EBOX_IGNORELOCKCLICK
    | EBOX_GROWLINK
    ;
	ebox_new((t_ebox *)x, flags);
    
    x->f_clock = clock_new(x,(t_method)hoa_scope_tick);
	x->f_startclock = 0;
    
    ebox_attrprocess_viabinbuf(x, d);
	ebox_ready((t_ebox *)x);
	
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_scope* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs    = x->f_scope->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs   = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_scope_dsp(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_index = 0;
    object_method(dsp64, gensym("dsp_add"), x, (method)hoa_scope_perform, 0, NULL);
    x->f_startclock = 1;
}

void hoa_scope_perform(t_hoa_scope *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
    cblas_sscal(numins * sampleframes, x->f_gain, x->f_signals, 1);
    x->f_index = 0;
    while(--sampleframes)
    {
        x->f_index++;
    }
    if(x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock, 0);
	}
}

void hoa_scope_tick(t_hoa_scope *x)
{
    x->f_scope->process(x->f_signals + x->f_index * x->f_scope->getNumberOfHarmonics());
    
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_harmonics_layer);
	ebox_redraw((t_ebox *)x);
	if(sys_getdspstate())
		clock_delay(x->f_clock, x->f_interval);
}

void hoa_scope_free(t_hoa_scope *x)
{
	ebox_free((t_ebox *)x);
    clock_free(x->f_clock);
    
    delete x->f_scope;
    delete [] x->f_signals;
}

void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_scope->getHarmonicsName(a).c_str());
}

t_pd_err hoa_scope_notify(t_hoa_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == hoa_sym_attr_modified)
	{
		name = s;
		if( name == hoa_sym_bgcolor || name == gensym("order"))
		{
			ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
		}
		else if(name == gensym("phcolor") || name == gensym("nhcolor"))
		{
			ebox_invalidate_layer((t_ebox *)x, hoa_sym_harmonics_layer);
		}
		ebox_redraw((t_ebox *)x);
	}
	return 0;
}

void hoa_scope_getdrawparams(t_hoa_scope *x, t_object *patcherview, t_edrawparams *params)
{
	params->d_boxfillcolor = x->f_color_bg;
    params->d_bordercolor = x->f_color_bd;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

long hoa_scope_oksize(t_hoa_scope *x, t_rect *newrect)
{
	if (newrect->width < 20)
		newrect->width = newrect->height = 20;
	return 0;
}

t_pd_err set_order(t_hoa_scope *x, t_object *attr, long ac, t_atom *av)
{
    long order;
	if (ac && av && atom_gettype(av) == A_LONG)
    {
        order = atom_getlong(av);
        if(order != x->f_scope->getOrder() && order > 0)
        {
            int dspState = canvas_suspend_dsp();
            
            delete x->f_scope;
            delete [] x->f_signals;
            x->f_scope      = new Hoa2D::Scope(order, NUMBEROFCIRCLEPOINTS_UI);
            x->f_order      = x->f_scope->getOrder();
            x->f_signals    = new t_float[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
            
            eobj_resize_inputs((t_ebox *)x, x->f_scope->getNumberOfHarmonics());
            canvas_update_dsp();
            canvas_resume_dsp(dspState);
        }
	}
    
	return 0;
}

void hoa_scope_paint(t_hoa_scope *x, t_object *view)
{
	t_rect rect;
	ebox_get_rect_for_view((t_ebox *)x, &rect);
	
	x->f_center = rect.width * .5;
	x->f_radius = x->f_center * 0.95;
	
    draw_background(x, view, &rect);
    draw_harmonics(x, view, &rect);
}

void draw_background(t_hoa_scope *x, t_object *view, t_rect *rect)
{
    int i;
	double y1, y2, rotateAngle;
    t_matrix transform;
    t_rgba black, white;
    
    black = white = x->f_color_bg;
    black.red = clip_min(black.red - contrast_black, 0.);
    black.green = clip_min(black.green - contrast_black, 0.);
    black.blue = clip_min(black.blue - contrast_black, 0.);
    
    white.red = clip_max(white.red + contrast_white, 1.);
    white.green = clip_max(white.green + contrast_white, 1.);
    white.blue = clip_max(white.blue + contrast_white, 1.);
    
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_background_layer, rect->width, rect->height);
    
	if (g)
	{
		egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		egraphics_set_matrix(g, &transform);
        
        for(i = 0; i < (x->f_order * 2 + 2) ; i++)
		{
            rotateAngle = ((double)i / (x->f_order * 2 + 2) * HOA_2PI ) - (0.5 / (x->f_order * 2 + 2) * HOA_2PI);
			egraphics_rotate(g, rotateAngle);
			
			y1 = x->f_radius / 5.;
			y2 = x->f_radius;
            
            if(rotateAngle > HOA_PI2 && rotateAngle < HOA_PI + HOA_PI2)
            {
                egraphics_move_to(g, -1, long(y1));
                egraphics_line_to(g, -1, long(y2));
            }
            else
            {
                egraphics_move_to(g, 1, long(y1));
                egraphics_line_to(g, 1, long(y2));
            }
            egraphics_set_line_width(g, 2);
            egraphics_set_color_rgba(g, &white);
            egraphics_stroke(g);
            
			egraphics_move_to(g, 0, y1);
			egraphics_line_to(g, 0, y2);
            egraphics_set_color_rgba(g, &black);
			egraphics_set_line_width(g, 1);
			egraphics_stroke(g);
			
			egraphics_rotate(g, -rotateAngle);
		}
        
        egraphics_matrix_init(&transform, 1, 0, 0, 1, x->f_center, x->f_center);
		egraphics_set_matrix(g, &transform);
        
        for(i = 5; i > 0; i--)
		{
            egraphics_set_line_width(g, 2);
            egraphics_set_color_rgba(g, &white);
            egraphics_arc(g, 1, 1, (double)i / 5. * x->f_radius,  0., HOA_2PI);
            egraphics_stroke(g);
            egraphics_set_line_width(g, 1);
            egraphics_set_color_rgba(g, &black);
            egraphics_arc(g, 0, 0, (double)i / 5.* x->f_radius,  0., HOA_2PI);
            egraphics_stroke(g);
		}
        
		ebox_end_layer((t_ebox*)x, hoa_sym_background_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_background_layer, 0., 0.);
}

void draw_harmonics(t_hoa_scope *x, t_object *view, t_rect *rect)
{
    long pathLength = 0;
	t_pt beginCoord;
    t_matrix transform;
    t_rgba shadcolor = {0.4, 0.4, 0.4, 1.};
    long precIndex = 0;
    
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_harmonics_layer, rect->width, rect->height);
    
    if(shadcolor.alpha > x->f_color_nh.alpha)
        shadcolor.alpha = x->f_color_ph.alpha;
    if(shadcolor.alpha > x->f_color_nh.alpha)
        shadcolor.alpha = x->f_color_nh.alpha;
	shadcolor.alpha -= 0.5;
	if(shadcolor.alpha < 0.)
        shadcolor.alpha = 0;
    
	if (g)
	{
        egraphics_rotate(g, HOA_PI);
		egraphics_set_line_width(g, 1);
        egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
        egraphics_set_matrix(g, &transform);
        egraphics_set_color_rgba(g, &x->f_color_ph);
        
        // positiv harmonics
        for(int i = 0; i < x->f_scope->getNumberOfPoints(); i++)
        {
            precIndex = i-1;
            if(precIndex < 0)
                precIndex += x->f_scope->getNumberOfPoints();
            
            if(i == x->f_scope->getNumberOfPoints()-1)
            {
                egraphics_line_to(g, beginCoord.x, beginCoord.y );
            }
            else if(x->f_scope->getValue(i) >= 0)
            {
                if (pathLength == 0)
                {
                    beginCoord.x = x->f_scope->getAbscissa(i) * x->f_radius;
                    beginCoord.y = x->f_scope->getOrdinate(i) * x->f_radius;
                    egraphics_move_to(g, beginCoord.x, beginCoord.y );
                    pathLength++;
                }
                else if(x->f_scope->getValue(i) < 0)
                {
                    egraphics_line_to(g, 0, 0);
                    egraphics_stroke(g);
                    egraphics_move_to(g, x->f_scope->getAbscissa(i) * x->f_radius, x->f_scope->getOrdinate(i) * x->f_radius);
                }
                else
                {
                    egraphics_line_to(g, x->f_scope->getAbscissa(i) * x->f_radius, x->f_scope->getOrdinate(i) * x->f_radius);
                }
            }
        }
        if(pathLength)
            egraphics_stroke(g);
        
        egraphics_set_color_rgba(g, &x->f_color_nh);
        pathLength = 0;
        for(int i = 0; i < x->f_scope->getNumberOfPoints(); i++)
        {
            precIndex = i-1;
            if (precIndex < 0) precIndex += x->f_scope->getNumberOfPoints();
            
            if (i == x->f_scope->getNumberOfPoints()-1)
            {
                egraphics_line_to(g, beginCoord.x, beginCoord.y );
            }
            else if(x->f_scope->getValue(i) < 0)
            {
                if (!pathLength)
                {
                    beginCoord.x = x->f_scope->getAbscissa(i) * x->f_radius;
                    beginCoord.y = x->f_scope->getOrdinate(i) * x->f_radius;
                    egraphics_move_to(g, beginCoord.x, beginCoord.y );
                    pathLength++;
                }
                else if(x->f_scope->getValue(precIndex) >= 0)
                {
                    egraphics_line_to(g, 0, 0);
                    egraphics_stroke(g);
                    egraphics_move_to(g, x->f_scope->getAbscissa(i) * x->f_radius, x->f_scope->getOrdinate(i) * x->f_radius);
                }
                else
                {
                    egraphics_line_to(g, x->f_scope->getAbscissa(i) * x->f_radius, x->f_scope->getOrdinate(i) * x->f_radius);
                }
            }
        }
        if(pathLength)
            egraphics_stroke(g);
        
		ebox_end_layer((t_ebox *)x, hoa_sym_harmonics_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_harmonics_layer, 0., 0.);
}