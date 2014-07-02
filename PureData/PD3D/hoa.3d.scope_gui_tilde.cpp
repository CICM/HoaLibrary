/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa3D.pd.h"

typedef struct  _hoa_scope_3D
{
	t_edspbox   j_box;
    Hoa3D::Scope*   f_scope;
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
   
} t_hoa_scope_3D;

t_eclass *hoa_scope_3D_class;

void *hoa_scope_3D_new(t_symbol *s, int argc, t_atom *argv);
void hoa_scope_3D_free(t_hoa_scope_3D *x);
void hoa_scope_3D_assist(t_hoa_scope_3D *x, void *b, long m, long a, char *s);
void hoa_scope_3D_tick(t_hoa_scope_3D *x);

void hoa_scope_3D_dsp(t_hoa_scope_3D *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_scope_3D_perform(t_hoa_scope_3D *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

t_pd_err hoa_scope_3D_notify(t_hoa_scope_3D *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
long hoa_scope_3D_oksize(t_hoa_scope_3D *x, t_rect *newrect);
void hoa_scope_3D_getdrawparams(t_hoa_scope_3D *x, t_object *patcherview, t_edrawparams *params);

void hoa_scope_3D_paint(t_hoa_scope_3D *x, t_object *view);
void draw_harmonics(t_hoa_scope_3D *x,  t_object *view, t_rect *rect);

t_pd_err    set_order(t_hoa_scope_3D *x, t_object *attr, long ac, t_atom *av);
t_hoa_err hoa_getinfos(t_hoa_scope_3D* x, t_hoa_boxinfos* boxinfos);

#define  contrast_white 0.06
#define  contrast_black 0.14

extern "C" void setup_hoa0x2e3d0x2escope_tilde(void)
{
	t_eclass *c;

	c = eclass_new("hoa.3d.scope~", (method)hoa_scope_3D_new, (method)hoa_scope_3D_free, (short)sizeof(t_hoa_scope_3D), 0L, A_GIMME, 0);
    
    eclass_dspinit(c);
    eclass_init(c, 0);
	hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)hoa_scope_3D_dsp,			"dsp",          A_CANT, 0);
	eclass_addmethod(c, (method)hoa_scope_3D_assist,		"assist",		A_CANT,	0);
	eclass_addmethod(c, (method)hoa_scope_3D_paint,         "paint",		A_CANT,	0);
	eclass_addmethod(c, (method)hoa_scope_3D_notify,		"notify",		A_CANT, 0);
	eclass_addmethod(c, (method)hoa_scope_3D_getdrawparams,"getdrawparams", A_CANT, 0);
	eclass_addmethod(c, (method)hoa_scope_3D_oksize,		"oksize",		A_CANT, 0);

    CLASS_ATTR_INVISIBLE            (c, "fontname", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontweight", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontslant", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontsize", 1);
    CLASS_ATTR_INVISIBLE            (c, "send", 1);
	CLASS_ATTR_DEFAULT              (c, "size", 0, "225. 225.");

    CLASS_ATTR_LONG                 (c, "order", 0, t_hoa_scope_3D, f_order);
    CLASS_ATTR_ACCESSORS            (c, "order", NULL, set_order);
	CLASS_ATTR_CATEGORY             (c, "order", 0, "Ambisonic");
	CLASS_ATTR_ORDER                (c, "order", 0, "1");
	CLASS_ATTR_LABEL                (c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_FILTER_MIN           (c, "order", 1);
	CLASS_ATTR_DEFAULT              (c, "order", 0, "1");
	CLASS_ATTR_SAVE                 (c, "order", 1);
    
    CLASS_ATTR_FLOAT                (c, "gain", 0, t_hoa_scope_3D, f_gain);
	CLASS_ATTR_CATEGORY             (c, "gain", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "gain", 0, "1");
	CLASS_ATTR_LABEL                (c, "gain", 0, "Gain");
	CLASS_ATTR_FILTER_MIN           (c, "gain", 1.);
	CLASS_ATTR_DEFAULT              (c, "gain", 0, "1.");
	CLASS_ATTR_SAVE                 (c, "gain", 1);
    
	CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_scope_3D, f_interval);
	CLASS_ATTR_CATEGORY             (c, "interval", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "interval", 0, "2");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "100");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
	
	CLASS_ATTR_RGBA                 (c, "bgcolor", 0, t_hoa_scope_3D, f_color_bg);
	CLASS_ATTR_CATEGORY             (c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER                (c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bgcolor", 0, "0.76 0.76 0.76 1.");
    
    CLASS_ATTR_RGBA                 (c, "bdcolor", 0, t_hoa_scope_3D, f_color_bd);
	CLASS_ATTR_CATEGORY             (c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER                (c, "bdcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bdcolor", 0, "0.7 0.7 0.7 1.");
	
	CLASS_ATTR_RGBA                 (c, "phcolor", 0, t_hoa_scope_3D, f_color_ph);
	CLASS_ATTR_CATEGORY             (c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "phcolor", 0, "Positive Harmonics Color");
	CLASS_ATTR_ORDER                (c, "phcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "phcolor", 0, "1. 0. 0. 1.");
	
	CLASS_ATTR_RGBA                 (c, "nhcolor", 0, t_hoa_scope_3D, f_color_nh);
	CLASS_ATTR_CATEGORY             (c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "nhcolor", 0, "Negative Harmonics Color");
	CLASS_ATTR_ORDER                (c, "nhcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "nhcolor", 0, "0. 0. 1. 1.");
    
    eclass_register(CLASS_BOX, c);
    hoa_scope_3D_class = c;
}

void *hoa_scope_3D_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_scope_3D *x =  NULL;
	t_binbuf *d;
	long flags;
	
	if (!(d = binbuf_via_atoms(argc, argv)))
		return NULL;

	x = (t_hoa_scope_3D *)eobj_new(hoa_scope_3D_class);
    
    x->f_order      = 1;
	x->f_startclock = 0;
	x->f_scope      = new Hoa3D::Scope(x->f_order, NUMBEROFCIRCLEPOINTS_UI2 * 0.5, NUMBEROFCIRCLEPOINTS_UI2);
    x->f_order      = x->f_scope->getDecompositionOrder();
    x->f_signals    = new t_float[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
    x->f_index      = 0;
    
    eobj_dspsetup(x, x->f_scope->getNumberOfHarmonics(), 0);
    
	flags = 0
    | EBOX_IGNORELOCKCLICK
    | EBOX_GROWLINK
    ;
	ebox_new((t_ebox *)x, flags);
    
    x->f_clock = clock_new(x,(t_method)hoa_scope_3D_tick);
	x->f_startclock = 0;
    
    ebox_attrprocess_viabinbuf(x, d);
	ebox_ready((t_ebox *)x);
	
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_scope_3D* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs    = x->f_scope->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs   = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_scope_3D_dsp(t_hoa_scope_3D *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_index = 0;
    object_method(dsp64, gensym("dsp_add"), x, (method)hoa_scope_3D_perform, 0, NULL);
    x->f_startclock = 1;
}

void hoa_scope_3D_perform(t_hoa_scope_3D *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
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

void hoa_scope_3D_tick(t_hoa_scope_3D *x)
{
    x->f_scope->process(x->f_signals + x->f_index * x->f_scope->getNumberOfHarmonics());
    
	ebox_invalidate_layer((t_ebox *)x, hoa_sym_harmonics_layer);
	ebox_redraw((t_ebox *)x);
	if(sys_getdspstate())
		clock_delay(x->f_clock, x->f_interval);
}

void hoa_scope_3D_free(t_hoa_scope_3D *x)
{
	ebox_free((t_ebox *)x);
    clock_free(x->f_clock);
    
    delete x->f_scope;
    delete [] x->f_signals;
}

void hoa_scope_3D_assist(t_hoa_scope_3D *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_scope->getHarmonicName(a).c_str());
}

t_pd_err hoa_scope_3D_notify(t_hoa_scope_3D *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == hoa_sym_attr_modified)
	{
		name = s;
		if(name == gensym("phcolor") || name == gensym("nhcolor") || name == hoa_sym_bgcolor || name == gensym("order"))
		{
			ebox_invalidate_layer((t_ebox *)x, hoa_sym_harmonics_layer);
		}
		ebox_redraw((t_ebox *)x);
	}
	return 0;
}

void hoa_scope_3D_getdrawparams(t_hoa_scope_3D *x, t_object *patcherview, t_edrawparams *params)
{
	params->d_boxfillcolor = x->f_color_bg;
    params->d_bordercolor = x->f_color_bd;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

long hoa_scope_3D_oksize(t_hoa_scope_3D *x, t_rect *newrect)
{
	if (newrect->width < 20)
		newrect->width = newrect->height = 20;
	return 0;
}

t_pd_err set_order(t_hoa_scope_3D *x, t_object *attr, long ac, t_atom *av)
{
    long order;
	if (ac && av && atom_gettype(av) == A_LONG)
    {
        order = atom_getlong(av);
        if(order != x->f_scope->getDecompositionOrder() && order > 0)
        {
            int dspState = canvas_suspend_dsp();
            
            delete x->f_scope;
            delete [] x->f_signals;
            x->f_scope      = new Hoa3D::Scope(order, 100, 199);
            x->f_order      = x->f_scope->getDecompositionOrder();
            x->f_signals    = new t_float[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
            
            eobj_resize_inputs((t_ebox *)x, x->f_scope->getNumberOfHarmonics());
            canvas_update_dsp();
            canvas_resume_dsp(dspState);
        }
	}
    
	return 0;
}

void hoa_scope_3D_paint(t_hoa_scope_3D *x, t_object *view)
{
	t_rect rect;
	ebox_get_rect_for_view((t_ebox *)x, &rect);
	
	x->f_center = rect.width * .5;
	x->f_radius = x->f_center * 0.95;

    draw_harmonics(x, view, &rect);
}

void draw_harmonics(t_hoa_scope_3D *x, t_object *view, t_rect *rect)
{
    char pathLength;
	t_pt beginCoord;
    t_matrix transform;
    long precIndex = 0;
    t_rgba color_pos;
    t_rgba color_neg;
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_harmonics_layer, rect->width, rect->height);
    
    
	double y1, y2, rotateAngle;
    t_rgba black, white;
    
    black = white = x->f_color_bg;
    black.red = clip_min(black.red - contrast_black, 0.);
    black.green = clip_min(black.green - contrast_black, 0.);
    black.blue = clip_min(black.blue - contrast_black, 0.);
    
    white.red = clip_max(white.red + contrast_white, 1.);
    white.green = clip_max(white.green + contrast_white, 1.);
    white.blue = clip_max(white.blue + contrast_white, 1.);
    
	if (g)
	{
        egraphics_rotate(g, HOA_PI);
        egraphics_set_line_width(g, 1);
        egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
        egraphics_set_matrix(g, &transform);
        
        for(int j = 0; j < x->f_scope->getNumberOfRows() * 0.5; j++)
        {
            // positive harmonics
            pathLength = 0;
            double constrast = (j - x->f_scope->getNumberOfRows() * 0.5) / (double)x->f_scope->getNumberOfRows();
            color_pos = rgba_addContrast(x->f_color_ph, constrast);
            color_neg = rgba_addContrast(x->f_color_nh, constrast);
            
            egraphics_set_color_rgba(g, &color_pos);
            for(int i = 0; i < x->f_scope->getNumberOfColumns(); i++)
            {
                precIndex = i-1;
                if(precIndex < 0)
                    precIndex += x->f_scope->getNumberOfColumns();
                
                if(i == x->f_scope->getNumberOfColumns()-1)
                {
                    egraphics_line_to(g, beginCoord.x, beginCoord.y );
                }
                else if(x->f_scope->getValue(j, i) >= 0)
                {
                    if (pathLength == 0)
                    {
                        beginCoord.x = abscissa(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        beginCoord.y = ordinate(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        egraphics_move_to(g, beginCoord.x, beginCoord.y );
                        pathLength++;
                    }
                    else
                    {
                        egraphics_line_to(g, abscissa(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)), ordinate(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)));
                    }
                }
            }
            if(pathLength)
                egraphics_stroke(g);
            
            pathLength = 0;
            // negative harmonics
            egraphics_set_color_rgba(g, &color_neg);
            for(int i = 0; i < x->f_scope->getNumberOfColumns(); i++)
            {
                precIndex = i-1;
                if(precIndex < 0)
                    precIndex += x->f_scope->getNumberOfColumns();
                
                if (i == x->f_scope->getNumberOfColumns()-1)
                {
                    egraphics_line_to(g, beginCoord.x, beginCoord.y );
                }
                else if(x->f_scope->getValue(j, i) < 0)
                {
                    if (!pathLength)
                    {
                        beginCoord.x = abscissa(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        beginCoord.y = ordinate(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        egraphics_move_to(g, beginCoord.x, beginCoord.y );
                        pathLength++;
                    }
                    else
                    {
                        egraphics_line_to(g, abscissa(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)), ordinate(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)));
                    }
                }
            }
            if(pathLength)
                egraphics_stroke(g);
        }
        
        for(int i = 0; i < (x->f_order * 2 + 2) ; i++)
		{
            rotateAngle = ((double)i / (x->f_order * 2 + 2) * HOA_2PI ) - (0.5 / (x->f_order * 2 + 2) * HOA_2PI);
			egraphics_rotate(g, rotateAngle);
			
			y1 = x->f_radius / 5.;
			y2 = x->f_radius;
            
            egraphics_move_to(g, 0, y1);
			egraphics_line_to(g, 0, y2);
            egraphics_set_line_width(g, 3);
            egraphics_set_color_rgba(g, &white);
            egraphics_stroke(g);
            
            egraphics_set_color_rgba(g, &black);
			egraphics_set_line_width(g, 1);
			egraphics_stroke(g);
			
			egraphics_rotate(g, -rotateAngle);
		}
        
        for(int i = 5; i > 0; i--)
		{
            egraphics_set_line_width(g, 3);
            egraphics_set_color_rgba(g, &white);
            egraphics_arc(g, 0, 0, (double)i / 5.* x->f_radius,  0., HOA_2PI);
            egraphics_stroke(g);
            egraphics_set_line_width(g, 1);
            egraphics_set_color_rgba(g, &black);
            egraphics_stroke(g);
		}
        
        for(int j = x->f_scope->getNumberOfRows() * 0.5; j < x->f_scope->getNumberOfRows(); j++)
        {
            // positive harmonics
            pathLength = 0;
            double constrast = (j - x->f_scope->getNumberOfRows() * 0.5) / (double)x->f_scope->getNumberOfRows();
            color_pos = rgba_addContrast(x->f_color_ph, constrast);
            color_neg = rgba_addContrast(x->f_color_nh, constrast);
            
            egraphics_set_color_rgba(g, &color_pos);
            for(int i = 0; i < x->f_scope->getNumberOfColumns(); i++)
            {
                precIndex = i-1;
                if(precIndex < 0)
                    precIndex += x->f_scope->getNumberOfColumns();
                
                if(i == x->f_scope->getNumberOfColumns()-1)
                {
                    egraphics_line_to(g, beginCoord.x, beginCoord.y );
                }
                else if(x->f_scope->getValue(j, i) >= 0)
                {
                    if (pathLength == 0)
                    {
                        beginCoord.x = abscissa(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        beginCoord.y = ordinate(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        egraphics_move_to(g, beginCoord.x, beginCoord.y );
                        pathLength++;
                    }
                    else
                    {
                        egraphics_line_to(g, abscissa(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)), ordinate(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)));
                    }
                }
            }
            if(pathLength)
                egraphics_stroke(g);
            
            pathLength = 0;
            // negative harmonics
            egraphics_set_color_rgba(g, &color_neg);
            for(int i = 0; i < x->f_scope->getNumberOfColumns(); i++)
            {
                precIndex = i-1;
                if(precIndex < 0)
                    precIndex += x->f_scope->getNumberOfColumns();
                
                if (i == x->f_scope->getNumberOfColumns()-1)
                {
                    egraphics_line_to(g, beginCoord.x, beginCoord.y );
                }
                else if(x->f_scope->getValue(j, i) < 0)
                {
                    if (!pathLength)
                    {
                        beginCoord.x = abscissa(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        beginCoord.y = ordinate(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        egraphics_move_to(g, beginCoord.x, beginCoord.y );
                        pathLength++;
                    }
                    else
                    {
                        egraphics_line_to(g, abscissa(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)), ordinate(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)));
                    }
                }
            }
            if(pathLength)
                egraphics_stroke(g);
        }

                 
		ebox_end_layer((t_ebox *)x, hoa_sym_harmonics_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_harmonics_layer, 0., 0.);
}