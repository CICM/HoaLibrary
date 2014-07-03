/*
 // Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

/**
 @file      hoa.3d.scope~.cpp
 @name      hoa.3d.scope~
 @realname  hoa.3d.scope~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A spherical harmonic visualizer
 
 @description
 <o>hoa.3d.scope~</o> displays spherical harmonics of an ambisonic sound field
 
 @discussion
 <o>hoa.3d.gl.scope~</o> displays spherical harmonics of an ambisonic sound field
 
 @category ambisonics, hoa objects, audio, GUI, MSP
 
 @seealso hoa.3d.gl.scope~, hoa.2d.scope~, hoa.3d.decoder~, hoa.3d.encoder~, hoa.3d.map~, hoa.3d.optim~, hoa.3d.vector~, hoa.3d.wider~, hoa.dac~
 
 @illustration on @caption the hoa.3d.scope~ GUI object
 @palette yes
 */

#include "../Hoa3D.max.h"

typedef struct  _hoa_scope 
{
	t_pxjbox        j_box;
    Hoa3D::Scope*   f_scope;
    int             f_index;
	void*           f_clock;
	int             f_startclock;
	t_atom_long     f_interval;
	t_atom_long     f_order;
    float           f_gain;
	
	t_jrgba         f_color_bg;
    t_jrgba         f_color_bd;
	t_jrgba         f_color_nh;
	t_jrgba         f_color_ph;
	
	double          f_center;
	double          f_radius;
    double*         f_signals;
    
} t_hoa_scope;

void *hoa_scope_new(t_symbol *s, int argc, t_atom *argv);
void hoa_scope_free(t_hoa_scope *x);
void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s);
void hoa_scope_tick(t_hoa_scope *x);

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err hoa_scope_notify(t_hoa_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
long hoa_scope_oksize(t_hoa_scope *x, t_rect *newrect);
void hoa_scope_getdrawparams(t_hoa_scope *x, t_object *patcherview, t_jboxdrawparams *params);

void hoa_scope_paint(t_hoa_scope *x, t_object *view);
void draw_background(t_hoa_scope *x,  t_object *view, t_rect *rect);
void draw_harmonics(t_hoa_scope *x,  t_object *view, t_rect *rect);

t_max_err set_order(t_hoa_scope *x, t_object *attr, long ac, t_atom *av);
t_hoa_err hoa_getinfos(t_hoa_scope* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_scope_class;

#define  contrast_white 0.06
#define  contrast_black 0.14

int C74_EXPORT main()
{
	t_class *c;

	c = class_new("hoa.3d.scope~", (method)hoa_scope_new, (method)hoa_scope_free, (short)sizeof(t_hoa_scope), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);
    
    hoa_initclass(c, (method)hoa_getinfos);
	
	// @method signal @digest Array of spherical harmonic signals that represent a sound field
	// @description Array of spherical harmonic signals that represent a sound field
	class_addmethod(c, (method)hoa_scope_dsp64,			"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)hoa_scope_paint,			"paint",		A_CANT,	0);
	class_addmethod(c, (method)hoa_scope_notify,		"notify",		A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_getdrawparams, "getdrawparams", A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_oksize,		"oksize",		A_CANT, 0);

    CLASS_ATTR_INVISIBLE            (c, "color", 0);
	CLASS_ATTR_INVISIBLE            (c, "textcolor", 0);
	CLASS_ATTR_DEFAULT              (c, "patching_rect", 0, "0 0 225 225");

    CLASS_ATTR_LONG                 (c, "order", 0, t_hoa_scope, f_order);
    CLASS_ATTR_ACCESSORS            (c, "order", NULL, set_order);
	CLASS_ATTR_CATEGORY             (c, "order", 0, "Ambisonic");
	CLASS_ATTR_ORDER                (c, "order", 0, "1");
	CLASS_ATTR_LABEL                (c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_FILTER_MIN           (c, "order", 1);
	CLASS_ATTR_DEFAULT              (c, "order", 0, "1");
	CLASS_ATTR_SAVE                 (c, "order", 1);
	// @description The ambisonic order of decomposition. Will adapt the number of input accordingly.
    
    CLASS_ATTR_FLOAT                (c, "gain", 0, t_hoa_scope, f_gain);
	CLASS_ATTR_CATEGORY             (c, "gain", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "gain", 0, "1");
	CLASS_ATTR_LABEL                (c, "gain", 0, "Gain");
	CLASS_ATTR_FILTER_MIN           (c, "gain", 1.);
	CLASS_ATTR_DEFAULT              (c, "gain", 0, "1.");
	CLASS_ATTR_SAVE                 (c, "gain", 1);
	// @description The <b>gain</b> factor can be used to offer a better visualisation of low amplitude sound fields.

	CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_scope, f_interval);
	CLASS_ATTR_CATEGORY             (c, "interval", 0, "Behavior");
	CLASS_ATTR_ORDER                (c, "interval", 0, "2");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "100");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
	// @description The refresh interval time in milliseconds.
	
	CLASS_ATTR_RGBA                 (c, "bgcolor", 0, t_hoa_scope, f_color_bg);
	CLASS_ATTR_CATEGORY             (c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER                (c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bgcolor", 0, "0.76 0.76 0.76 1.");
	// @description Sets the RGBA values for the background color of the <o>hoa.3d.scope~</o> object
    
    CLASS_ATTR_RGBA                 (c, "bdcolor", 0, t_hoa_scope, f_color_bd);
	CLASS_ATTR_CATEGORY             (c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER                (c, "bdcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bdcolor", 0, "0.7 0.7 0.7 1.");
	// @description Sets the RGBA values for the border color of the <o>hoa.3d.scope~</o> object
	
	CLASS_ATTR_RGBA                 (c, "phcolor", 0, t_hoa_scope, f_color_ph);
	CLASS_ATTR_CATEGORY             (c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "phcolor", 0, "Positive Harmonics Color");
	CLASS_ATTR_ORDER                (c, "phcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "phcolor", 0, "1. 0. 0. 1.");
	// @description Sets the RGBA values for the positive harmonics color of the <o>hoa.3d.scope~</o> object
	
	CLASS_ATTR_RGBA                 (c, "nhcolor", 0, t_hoa_scope, f_color_nh);
	CLASS_ATTR_CATEGORY             (c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "nhcolor", 0, "Negative Harmonics Color");
	CLASS_ATTR_ORDER                (c, "nhcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "nhcolor", 0, "0. 0. 1. 1.");
	// @description Sets the RGBA values for the negative harmonics color of the <o>hoa.3d.scope~</o> object
	
	class_register(CLASS_BOX, c);
	hoa_scope_class = c;
	
	return 0;
}

void *hoa_scope_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_scope *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if(!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_hoa_scope *)object_alloc(hoa_scope_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
            | JBOX_DRAWBACKGROUND
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;
    
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
    
    dictionary_getlong(d, gensym("order"), (t_atom_long *)&x->f_order);
    if(x->f_order < 1)
        x->f_order = 1;
    
	x->f_scope      = new Hoa3D::Scope(x->f_order, NUMBEROFCIRCLEPOINTS_UI2, NUMBEROFCIRCLEPOINTS_UI);
    x->f_order      = x->f_scope->getDecompositionOrder();
    x->f_signals    = new double[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
    x->f_index      = 0;
    
    dsp_setupjbox((t_pxjbox *)x, x->f_scope->getNumberOfHarmonics());
    
    x->f_clock = clock_new(x,(method)hoa_scope_tick);
	x->f_startclock = 0;
    
    attr_dictionary_process(x, d);
	jbox_ready((t_jbox *)x);
	
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
    }
    cblas_dscal(numins * sampleframes, x->f_gain, x->f_signals, 1);
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

	jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_harmonics_layer);
	jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

void hoa_scope_free(t_hoa_scope *x)
{
	dsp_freejbox((t_pxjbox *)x);
	freeobject((t_object *)x->f_clock);
	jbox_free((t_jbox *)x);
    
    delete x->f_scope;
    delete [] x->f_signals;
}

void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(signal) %s", x->f_scope->getHarmonicName(a).c_str());
}

t_max_err hoa_scope_notify(t_hoa_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == hoa_sym_attr_modified)
	{
		name = (t_symbol *)object_method((t_object *)data, hoa_sym_getname);
		if( name == hoa_sym_bgcolor || name == gensym("order"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_background_layer);
		}
		else if(name == gensym("phcolor") || name == gensym("nhcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_harmonics_layer);
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void hoa_scope_getdrawparams(t_hoa_scope *x, t_object *patcherview, t_jboxdrawparams *params)
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

void hoa_scope_paint(t_hoa_scope *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	
	x->f_center = rect.width * .5;
	x->f_radius = x->f_center * 0.95;
	
    draw_harmonics(x, view, &rect);
}

t_jrgba rgba_addContrast(t_jrgba color, float contrast)
{
    t_jrgba new_color = color;
    new_color.red = clip_minmax(new_color.red += contrast, 0., 1.);
    new_color.green = clip_minmax(new_color.green += contrast, 0., 1.);
    new_color.blue = clip_minmax(new_color.blue += contrast, 0., 1.);
    return new_color;
}

void draw_harmonics(t_hoa_scope *x, t_object *view, t_rect *rect)
{
    char pathLength;
	t_pt beginCoord;
    t_jmatrix transform;
    long precIndex = 0;
    t_jrgba color_pos;
    t_jrgba color_neg;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, hoa_sym_harmonics_layer, rect->width, rect->height);
    
	double y1, y2, rotateAngle;
    t_jrgba black, white;
    
    black = white = x->f_color_bg;
    black.red = clip_min(black.red - contrast_black, 0.);
    black.green = clip_min(black.green - contrast_black, 0.);
    black.blue = clip_min(black.blue - contrast_black, 0.);
    
    white.red = clip_max(white.red + contrast_white, 1.);
    white.green = clip_max(white.green + contrast_white, 1.);
    white.blue = clip_max(white.blue + contrast_white, 1.);
    
	if (g)
	{
        jgraphics_rotate(g, HOA_PI);
        jgraphics_set_line_width(g, 1);
		jgraphics_new_path(g);
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		jgraphics_set_matrix(g, &transform);
        
        for(int j = 0; j < x->f_scope->getNumberOfRows() * 0.5; j++)
        {
            // positive harmonics
            pathLength = 0;
            double constrast = (j - x->f_scope->getNumberOfRows() * 0.5) / (double)x->f_scope->getNumberOfRows();
            color_pos = rgba_addContrast(x->f_color_ph, constrast);
            color_neg = rgba_addContrast(x->f_color_nh, constrast);
			
			jgraphics_new_path(g);
            
            jgraphics_set_source_jrgba(g, &color_pos);
            for(int i = 0; i < x->f_scope->getNumberOfColumns(); i++)
            {
                precIndex = i-1;
                if(precIndex < 0)
                    precIndex += x->f_scope->getNumberOfColumns();
                
                if(i == x->f_scope->getNumberOfColumns()-1)
                {
                    jgraphics_line_to(g, beginCoord.x, beginCoord.y );
					//post("last %f %f", beginCoord.x, beginCoord.y);
                }
                else if(x->f_scope->getValue(j, i) >= 0)
                {
                    if (!pathLength)
                    {
                        beginCoord.x = abscissa(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        beginCoord.y = ordinate(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        jgraphics_move_to(g, beginCoord.x, beginCoord.y );
						//post("pathlen %f %f", beginCoord.x, beginCoord.y);
                        pathLength++;
                    }
                    else
                    {
                        jgraphics_line_to(g, abscissa(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)), ordinate(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)));
                    }
                }
            }
            if(pathLength)
                jgraphics_fill(g);
            
            // negative harmonics
			pathLength = 0;
			jgraphics_new_path(g);
            jgraphics_set_source_jrgba(g, &color_neg);
            for(int i = 0; i < x->f_scope->getNumberOfColumns(); i++)
            {
                precIndex = i-1;
                if(precIndex < 0)
                    precIndex += x->f_scope->getNumberOfColumns();
                
                if (i == x->f_scope->getNumberOfColumns()-1)
                {
                    jgraphics_line_to(g, beginCoord.x, beginCoord.y );
                }
                else if(x->f_scope->getValue(j, i) < 0)
                {
                    if (!pathLength)
                    {
                        beginCoord.x = abscissa(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        beginCoord.y = ordinate(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        jgraphics_move_to(g, beginCoord.x, beginCoord.y );
                        pathLength++;
                    }
                    else
                    {
                        jgraphics_line_to(g, abscissa(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)), ordinate(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)));
                    }
                }
            }
            if(pathLength)
                jgraphics_fill(g);
        }
        
		// draw background
		pathLength = 0;
		jgraphics_new_path(g);
        for(int i = 0; i < (x->f_order * 2 + 2) ; i++)
		{
            rotateAngle = ((double)i / (x->f_order * 2 + 2) * HOA_2PI ) - (0.5 / (x->f_order * 2 + 2) * HOA_2PI);
			jgraphics_rotate(g, rotateAngle);
			
			y1 = x->f_radius / 5.;
			y2 = x->f_radius;
            
            jgraphics_move_to(g, 0, y1);
			jgraphics_line_to(g, 0, y2);
            jgraphics_set_line_width(g, 3);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_stroke_preserve(g);
            
            jgraphics_set_source_jrgba(g, &black);
			jgraphics_set_line_width(g, 1);
			jgraphics_stroke(g);
			
			jgraphics_rotate(g, -rotateAngle);
		}
        
        for(int i = 5; i > 0; i--)
		{
            jgraphics_set_line_width(g, 3);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_arc(g, 0, 0, (double)i / 5.* x->f_radius,  0., HOA_2PI);
            jgraphics_stroke_preserve(g);
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_stroke(g);
		}
        
        for(int j = x->f_scope->getNumberOfRows() * 0.5; j < x->f_scope->getNumberOfRows(); j++)
        {
            // positive harmonics
			pathLength = 0;
			jgraphics_new_path(g);
            double constrast = (j - x->f_scope->getNumberOfRows() * 0.5) / (double)x->f_scope->getNumberOfRows();
            color_pos = rgba_addContrast(x->f_color_ph, constrast);
            color_neg = rgba_addContrast(x->f_color_nh, constrast);
            
            jgraphics_set_source_jrgba(g, &color_pos);
            for(int i = 0; i < x->f_scope->getNumberOfColumns(); i++)
            {
                precIndex = i-1;
                if(precIndex < 0)
                    precIndex += x->f_scope->getNumberOfColumns();
                
                if(i == x->f_scope->getNumberOfColumns()-1)
                {
                    jgraphics_line_to(g, beginCoord.x, beginCoord.y );
                }
                else if(x->f_scope->getValue(j, i) >= 0)
                {
                    if (!pathLength)
                    {
                        beginCoord.x = abscissa(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        beginCoord.y = ordinate(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        jgraphics_move_to(g, beginCoord.x, beginCoord.y );
                        pathLength++;
                    }
                    else
                    {
                        jgraphics_line_to(g, abscissa(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)), ordinate(x->f_radius *  x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)));
                    }
                }
            }
            if(pathLength)
                jgraphics_fill(g);
            
			// negative harmonics
            pathLength = 0;
			jgraphics_new_path(g);
            jgraphics_set_source_jrgba(g, &color_neg);
            for(int i = 0; i < x->f_scope->getNumberOfColumns(); i++)
            {
                precIndex = i-1;
                if(precIndex < 0)
                    precIndex += x->f_scope->getNumberOfColumns();
                
                if (i == x->f_scope->getNumberOfColumns()-1)
                {
                    jgraphics_line_to(g, beginCoord.x, beginCoord.y );
                }
                else if(x->f_scope->getValue(j, i) < 0)
                {
                    if (!pathLength)
                    {
                        beginCoord.x = abscissa(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        beginCoord.y = ordinate(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j));
                        jgraphics_move_to(g, beginCoord.x, beginCoord.y );
                        pathLength++;
                    }
                    else
                    {
                        jgraphics_line_to(g, abscissa(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)), ordinate(x->f_radius *  -x->f_scope->getValue(j, i), x->f_scope->getAzimuth(i),x->f_scope->getElevation(j)));
                    }
                }
            }
            if(pathLength)
                jgraphics_fill(g);
        }
		
		/*
		jgraphics_new_path(g);
		jgraphics_move_to(g, -x->f_radius, 0);
		jgraphics_line_to(g, x->f_radius, 0);
		jgraphics_set_line_width(g, 1);
		jgraphics_set_source_jrgba(g, &black);
		jgraphics_stroke(g);
		
		jgraphics_move_to(g, 0, x->f_radius);
		jgraphics_line_to(g, 0, -x->f_radius);
		jgraphics_set_line_width(g, 1);
		jgraphics_set_source_jrgba(g, &black);
		jgraphics_stroke(g);
		
		for (int i=1; i<=5; i++)
		{
			jgraphics_new_path(g);
			jgraphics_move_to(g, x->f_radius, x->f_radius);
			jgraphics_ovalarc(g, 0, 0, x->f_radius*((float)i/(float)5), x->f_radius, 0, HOA_2PI);
			jgraphics_set_line_width(g, 1);
			jgraphics_set_source_jrgba(g, &black);
			jgraphics_stroke(g);
			
			jgraphics_rotate(g, HOA_PI2);
			jgraphics_move_to(g, x->f_radius, x->f_radius);
			jgraphics_ovalarc(g, 0, 0, x->f_radius*((float)i/(float)5), x->f_radius, 0, HOA_2PI);
			jgraphics_set_line_width(g, 1);
			jgraphics_set_source_jrgba(g, &black);
			jgraphics_stroke(g);
			jgraphics_rotate(g, -HOA_PI2);
		}
		*/
		
		jbox_end_layer((t_object*)x, view, hoa_sym_harmonics_layer);
	}
	jbox_paint_layer((t_object *)x, view, hoa_sym_harmonics_layer, 0., 0.);
}

t_max_err set_order(t_hoa_scope *x, t_object *attr, long ac, t_atom *av)
{
    long order;
    t_object *b = NULL;
	if (ac && av && atom_gettype(av) == A_LONG)
    {
        order = atom_getlong(av);
        if(order != x->f_scope->getDecompositionOrder() && order > 0)
        {
            int dspState = sys_getdspobjdspstate((t_object*)x);
            if(dspState)
                object_method(gensym("dsp")->s_thing, hoa_sym_start);
            
            delete x->f_scope;
            delete [] x->f_signals;
            x->f_scope      = new Hoa3D::Scope(order, NUMBEROFCIRCLEPOINTS_UI2, NUMBEROFCIRCLEPOINTS_UI);
            x->f_order      = x->f_scope->getDecompositionOrder();
            x->f_signals    = new double[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
            
            object_obex_lookup(x, gensym("#B"), (t_object **)&b);
            object_method(b, hoa_sym_dynlet_begin);
            dsp_resize((t_pxobject*)x, x->f_scope->getNumberOfHarmonics());
            object_method(b, hoa_sym_dynlet_end);
            
            if(dspState)
                object_method(gensym("dsp")->s_thing, hoa_sym_stop);
        }
	}
    
	return MAX_ERR_NONE;
}
