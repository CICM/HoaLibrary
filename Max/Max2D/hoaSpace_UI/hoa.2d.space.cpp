/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.max.h"

typedef struct  _hoa_space
{
	t_jbox		j_box;
	void*		f_out;
    long        f_number_of_channels;
    double      f_minmax[2];
    
    long		f_mode;
    double*     f_channel_values;
	double*     f_channel_refs;
    
	t_jrgba     f_color_bg;
    t_jrgba     f_color_bd;
	t_jrgba		f_color_sp;
	t_jrgba		f_color_pt;

    t_pt        f_mouse_ref;
	double		f_center;
    double      f_radius;
} t_hoa_space;

void *hoa_space_new(t_symbol *s, int argc, t_atom *argv);
void hoa_space_free(t_hoa_space *x);
void hoa_space_assist(t_hoa_space *x, void *b, long m, long a, char *s);
void hoa_space_preset(t_hoa_space *x);
void hoa_space_list(t_hoa_space *x, t_symbol *s, long ac, t_atom *av);
void hoa_space_output(t_hoa_space *x);

t_max_err hoa_space_notify(t_hoa_space *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void hoa_space_getdrawparams(t_hoa_space *x, t_object *patcherview, t_jboxdrawparams *params);

void hoa_space_mouse_move(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_down(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_drag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);

void hoa_space_paint(t_hoa_space *x, t_object *view);
void draw_background(t_hoa_space *x, t_object *view, t_rect *rect);
void draw_space(t_hoa_space *x,  t_object *view, t_rect *rect);
void draw_points(t_hoa_space *x, t_object *view, t_rect *rect);

t_max_err hoa_space_setvalueof(t_hoa_space *x, long ac, t_atom *av);
t_max_err hoa_space_getvalueof(t_hoa_space *x, long *ac, t_atom **av);
t_hoa_err hoa_getinfos(t_hoa_space* x, t_hoa_boxinfos* boxinfos);
t_max_err channels_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv);
t_max_err minmax_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv);

t_class *hoa_space_class;

int C74_EXPORT main()
{
	t_class *c;
    
	c = class_new("hoa.2d.space", (method)hoa_space_new, (method)hoa_space_free, (short)sizeof(t_hoa_space), 0L, A_GIMME, 0);
    class_alias(c, gensym("hoa.space"));
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);

    hoa_initclass(c, (method)hoa_getinfos);
	class_addmethod(c, (method)hoa_space_assist,          "assist",         A_CANT,	0);
	class_addmethod(c, (method)hoa_space_paint,           "paint",          A_CANT,	0);
	class_addmethod(c, (method)hoa_space_notify,          "notify",         A_CANT, 0);
    class_addmethod(c, (method)hoa_space_output,          "bang",           A_CANT, 0);
	class_addmethod(c, (method)hoa_space_getdrawparams,   "getdrawparams",  A_CANT, 0);
	class_addmethod(c, (method)hoa_space_mouse_down,      "mousedown",      A_CANT, 0);
    class_addmethod(c, (method)hoa_space_mouse_move,      "mousemove",      A_CANT, 0);
	class_addmethod(c, (method)hoa_space_mouse_drag,      "mousedrag",      A_CANT, 0);
    class_addmethod(c, (method)hoa_space_mouse_down,      "mouseup",        A_CANT, 0);
    class_addmethod(c, (method)hoa_space_preset,          "preset",         0);
    class_addmethod(c, (method)hoa_space_getvalueof,      "getvalueof",     A_CANT, 0);
	class_addmethod(c, (method)hoa_space_setvalueof,      "setvalueof",     A_CANT, 0);
    class_addmethod(c, (method)hoa_space_list,            "list",           A_GIMME, 0);
    
	CLASS_ATTR_INVISIBLE            (c, "color", 0);
	CLASS_ATTR_INVISIBLE            (c, "textcolor", 0);
	CLASS_ATTR_DEFAULT              (c, "patching_rect", 0, "0 0 225 225");
    
    CLASS_ATTR_LONG                 (c, "channels", 0, t_hoa_space, f_number_of_channels);
	CLASS_ATTR_CATEGORY             (c, "channels", 0, "Planewaves");
    CLASS_ATTR_LABEL                (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_ACCESSORS            (c, "channels", NULL, channels_set);
    CLASS_ATTR_ORDER                (c, "channels", 0, "1");
    CLASS_ATTR_DEFAULT              (c, "channels", 0, "4");
    CLASS_ATTR_SAVE                 (c, "channels", 1);
    
    CLASS_ATTR_DOUBLE_ARRAY         (c, "minmax",   0, t_hoa_space, f_minmax, 2);
	CLASS_ATTR_CATEGORY             (c, "minmax",   0, "Behavior");
    CLASS_ATTR_LABEL                (c, "minmax",   0, "Minimum and Maximum");
	CLASS_ATTR_ACCESSORS            (c, "minmax", NULL, minmax_set);
    CLASS_ATTR_ORDER                (c, "minmax",   0, "1");
    CLASS_ATTR_DEFAULT              (c, "minmax",   0, "0. 1.");
    CLASS_ATTR_SAVE                 (c, "minmax",   1);
    
	CLASS_ATTR_RGBA                 (c, "bgcolor", 0, t_hoa_space, f_color_bg);
	CLASS_ATTR_CATEGORY             (c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER                (c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bgcolor", 0, "0.76 0.76 0.76 1.");
    
    CLASS_ATTR_RGBA                 (c, "bdcolor", 0, t_hoa_space, f_color_bd);
	CLASS_ATTR_CATEGORY             (c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL                (c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER                (c, "bdcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "bdcolor", 0, "0.7 0.7 0.7 1.");
	
	CLASS_ATTR_RGBA					(c, "spcolor", 0, t_hoa_space, f_color_sp);
	CLASS_ATTR_CATEGORY				(c, "spcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "spcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "spcolor", 0, "Space Color");
    CLASS_ATTR_ORDER                (c, "spcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "spcolor", 0, "0. 0. 1. 0.25");
	
	CLASS_ATTR_RGBA					(c, "ptcolor", 0, t_hoa_space, f_color_pt);
	CLASS_ATTR_CATEGORY				(c, "ptcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "ptcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "ptcolor", 0, "Virtuals Microphones Color");
    CLASS_ATTR_ORDER                (c, "ptcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "ptcolor", 0, "0. 0. 0. 1.");
	
	class_register(CLASS_BOX, c);
	hoa_space_class = c;
	
	return 0;
}

void *hoa_space_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_space *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_hoa_space *)object_alloc(hoa_space_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			| JBOX_DRAWBACKGROUND
			;
    
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.b_firstin = (t_object *)x;
    
    x->f_channel_values = new double[MAX_CHANNELS];
    x->f_channel_refs   = new double[MAX_CHANNELS];
    x->f_out        = listout(x);

	attr_dictionary_process(x, d);
	jbox_ready((t_jbox *)x);

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_space* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs    = 0;
	boxinfos->autoconnect_outputs   = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}


void hoa_space_list(t_hoa_space *x, t_symbol *s, long ac, t_atom *av)
{
    if(ac && av)
    {
        for(int i = 0; i < x->f_number_of_channels && i < ac; i++)
        {
            if(atom_gettype(av+i) == A_FLOAT)
                x->f_channel_values[i] = Hoa2D::clip_minmax(atom_getfloat(av+i), x->f_minmax[0], x->f_minmax[1]);
        }
        
        jbox_invalidate_layer((t_object *)x, NULL, gensym("space_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("points_layer"));
        jbox_redraw((t_jbox *)x);

    }
}


void hoa_space_free(t_hoa_space *x)
{
	jbox_free((t_jbox *)x);
    delete [] x->f_channel_values;
    delete [] x->f_channel_refs;
}

void hoa_space_assist(t_hoa_space *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		sprintf(s,"(Anything) Behavior and appearance");
	}
	else
	{
        sprintf(s,"(List) Channels coefficients");
	}
}

t_max_err hoa_space_notify(t_hoa_space *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("bgcolor") || name == gensym("bdcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
		else if(name == gensym("spcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("space_layer"));
		}
		else if(name == gensym("ptcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("points_layer"));
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void hoa_space_getdrawparams(t_hoa_space *x, t_object *patcherview, t_jboxdrawparams *params)
{
    params->d_boxfillcolor = x->f_color_bg;
    params->d_bordercolor = x->f_color_bd;
	params->d_borderthickness = 1;
	params->d_cornersize = 6;
}

void hoa_space_preset(t_hoa_space *x)
{
    void* z;
    if(!(z = gensym("_preset")->s_thing))
        return;
    
    for(int i = 0; i < x->f_number_of_channels; i++)
        binbuf_vinsert(z, gensym("osslf")->s_name, x, object_classname(x), gensym("list"), i, (float)x->f_channel_values[i]);
}

t_max_err hoa_space_setvalueof(t_hoa_space *x, long ac, t_atom *av)
{
	if(ac && av)
    {
        for(int i = 0; i < x->f_number_of_channels && i < ac; i++)
        {
            if(atom_gettype(av+i) == A_FLOAT)
                x->f_channel_values[i] = Hoa2D::clip_minmax(atom_getfloat(av+i), x->f_minmax[0], x->f_minmax[1]);
        }
        
        jbox_invalidate_layer((t_object *)x, NULL, gensym("space_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("points_layer"));
        jbox_redraw((t_jbox *)x);
        
    }
	return MAX_ERR_NONE;
}

t_max_err hoa_space_getvalueof(t_hoa_space *x, long *ac, t_atom **av)
{
    int limit = 0;
	if(ac && av)
    {
		if(*ac && *av)
        {
            limit = *ac;
            if(limit > x->f_number_of_channels)
                limit = x->f_number_of_channels;
		}
        else
        {
			*av = (t_atom *)getbytes(x->f_number_of_channels * sizeof(t_atom));
            limit = *ac = x->f_number_of_channels;
        }
        for(int i = 0; i < limit; i++)
            atom_setfloat(*av+i, x->f_channel_values[i]);
    }
	return MAX_ERR_NONE;
}

void hoa_space_paint(t_hoa_space *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	
	x->f_center = rect.width * .5;
	x->f_radius = x->f_center * 0.95;
	
	draw_background(x, view, &rect);
	draw_space(x, view, &rect);
	draw_points(x, view, &rect);
}

void draw_background(t_hoa_space *x,  t_object *view, t_rect *rect)
{
    int i;
	double y1, y2, rotateAngle;
    t_jmatrix transform;
    t_jrgba black, white;
    
    double contrastBlack = 0.14;
    double contrastWhite = 0.06;
    
    black = white = x->f_color_bg;
    black.red = Hoa2D::clip_min(black.red -= contrastBlack, 0.);
    black.green = Hoa2D::clip_min(black.green -= contrastBlack, 0.);
    black.blue = Hoa2D::clip_min(black.blue -= contrastBlack, 0.);
    
    white.red = Hoa2D::clip_max(white.red += contrastWhite, 1.);
    white.green = Hoa2D::clip_max(white.green += contrastWhite, 1.);
    white.blue = Hoa2D::clip_max(white.blue += contrastWhite, 1.);
    
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
    
	if (g)
	{
		/* Axes */
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		jgraphics_set_matrix(g, &transform);
        
        for(i = 0; i < x->f_number_of_channels ; i++)
		{
            rotateAngle = ((double)i / (x->f_number_of_channels) * CICM_2PI ) - (0.5 / (x->f_number_of_channels) * CICM_2PI);
			jgraphics_rotate(g, rotateAngle);
			
			y1 = x->f_radius / 5.;
			y2 = x->f_radius;
            
            /* Inner shadow */
            if(rotateAngle > CICM_PI2 && rotateAngle < CICM_PI + CICM_PI2)
            {
                jgraphics_move_to(g, -1, long(y1));
                jgraphics_line_to(g, -1, long(y2));
            }
            else
            {
                jgraphics_move_to(g, 1, long(y1));
                jgraphics_line_to(g, 1, long(y2));
            }
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_stroke(g);
            
			jgraphics_move_to(g, 0, y1);
			jgraphics_line_to(g, 0, y2);
            jgraphics_set_source_jrgba(g, &black);
			jgraphics_set_line_width(g, 1);
			jgraphics_stroke(g);
			
			jgraphics_rotate(g, -rotateAngle);
		}
        
        jgraphics_matrix_init(&transform, 1, 0, 0, 1, x->f_center, x->f_center);
		jgraphics_set_matrix(g, &transform);
        
        /* Circles */
        for(i = 5; i > 0; i--)
		{
            //inner shadow
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_arc(g, 1, 1, (double)i / 5. * x->f_radius,  0., CICM_2PI);
            jgraphics_stroke(g);
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_arc(g, 0, 0, (double)i / 5.* x->f_radius,  0., CICM_2PI);
            jgraphics_stroke(g);
		}
        
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_space(t_hoa_space *x,  t_object *view, t_rect *rect)
{
    int i;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("space_layer"), rect->width, rect->height);

	if (g)
	{
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		jgraphics_set_matrix(g, &transform);
		jgraphics_set_line_width(g, 2);
        jgraphics_set_source_jrgba(g, &x->f_color_sp);
		
		jbox_end_layer((t_object*)x, view, gensym("space_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("space_layer"), 0., 0.);
}

void draw_points(t_hoa_space *x,  t_object *view, t_rect *rect)
{
    int i;
    double angle, radius, abscissa, ordinate;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("points_layer"), rect->width, rect->height);

	if (g) 
	{
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		jgraphics_set_matrix(g, &transform);
		jgraphics_set_source_jrgba(g, &x->f_color_pt);
        
        for(i = 0; i < x->f_number_of_channels; i++)
		{
            radius = (x->f_channel_values[i] / (x->f_minmax[1] - x->f_minmax[0]) - x->f_minmax[0]) * x->f_radius * 4. / 5. + x->f_radius / 5.;
            angle  = (double)(i + 1.) / (double)x->f_number_of_channels * CICM_2PI;
            abscissa = Hoa2D::abscissa(radius, angle + CICM_PI - CICM_2PI / (double)x->f_number_of_channels);
            ordinate = Hoa2D::ordinate(radius, angle + CICM_PI - CICM_2PI / (double)x->f_number_of_channels);
            jgraphics_arc(g, abscissa, ordinate, 3., 0., CICM_2PI);
            jgraphics_fill(g);
        }
        
        jbox_end_layer((t_object*)x, view, gensym("points_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("points_layer"), 0., 0.);
}

/**********************************************************/
/*                      Souris                            */
/**********************************************************/

void hoa_space_mouse_move(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if(modifiers == 132 || modifiers == 5) // ctrl : rotation
        jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_RESIZE_FOURWAY);
    else if(modifiers == 2) // shift : gain
        jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_RESIZE_UPDOWN);
    else
        jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_ARROW);
    
    jbox_redraw((t_jbox *)x);
}

void hoa_space_mouse_down(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->f_mouse_ref = pt;
    if(modifiers == 148 || modifiers == 21) // ctrl : rotation
    {
        x->f_mode = 1;
        memcpy(x->f_channel_refs, x->f_channel_values, x->f_number_of_channels * sizeof(double));
    }
    else if(modifiers == 18) // shift : gain
    {
        x->f_mode = 2;
        memcpy(x->f_channel_refs, x->f_channel_values, x->f_number_of_channels * sizeof(double));
    }
    else
    {
        x->f_mode = 0;
        hoa_space_mouse_drag(x, patcherview, pt, modifiers);
    }
}

void hoa_space_mouse_drag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    int index;
    t_pt mouse;
    mouse.x = pt.x - x->f_center;
    mouse.y = x->f_center * 2. - pt.y - x->f_center;
    double angle, radius, value;
    if(x->f_mode == 1)
    {
        ;
    }
    else if(x->f_mode == 2)
    {
        ;
    }
    else
    {
        angle   = Hoa2D::wrap_twopi(Hoa2D::angle(mouse.x, mouse.y) - CICM_PI + (CICM_PI / (double)x->f_number_of_channels));
        radius  = Hoa2D::radius(mouse.x, mouse.y);
        index   = angle / CICM_2PI * x->f_number_of_channels;
        value   = (radius - (x->f_radius / 5.)) / (x->f_radius * 4. / 5.);
        value  += x->f_minmax[0];
        value  *= (x->f_minmax[1] - x->f_minmax[0]);
        value   = Hoa2D::clip_minmax(value, x->f_minmax[0], x->f_minmax[1]);
        x->f_channel_values[index] = value;
    }
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("space_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("points_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoa_space_output(t_hoa_space *x)
{
    t_atom argv[MAX_CHANNELS];
    for(int i = 0; i < x->f_number_of_channels; i++)
        atom_setfloat(argv+i, x->f_channel_values[i]);
    
    outlet_list(x->f_out, 0L, x->f_number_of_channels, argv);
}

t_max_err channels_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv)
{
    long numberOfChannels;
    if (argc && argv && atom_gettype(argv) == A_LONG)
    {
        numberOfChannels = atom_getlong(argv);
        if(numberOfChannels != x->f_number_of_channels && numberOfChannels > 2 && numberOfChannels <= MAX_CHANNELS)
        {
            x->f_number_of_channels  = numberOfChannels;
            for(int i = 0; i < x->f_number_of_channels; i++)
                x->f_channel_values[i] = 0.;
            
            jbox_invalidate_layer((t_object*)x, NULL, gensym("background_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("space_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("points_layer"));
            jbox_redraw((t_jbox *)x);
        }
    }
	return 0;
}

t_max_err minmax_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv)
{
    double min, max;
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_FLOAT)
            min = atom_getfloat(argv);
        else
            min = x->f_minmax[0];
        if(argc > 1 && atom_gettype(argv+1) == A_FLOAT)
            max = atom_getfloat(argv+1);
        else
            max = x->f_minmax[1];
        
        if(min > max)
        {
            x->f_minmax[1] = min;
            x->f_minmax[0] = max;
        }
        else
        {
            x->f_minmax[0] = min;
            x->f_minmax[1] = max;
        }
        for(int i = 0; i < x->f_number_of_channels; i++)
            x->f_channel_values[i] = Hoa2D::clip_minmax(x->f_channel_values[i], x->f_minmax[0], x->f_minmax[1]);
        
        jbox_invalidate_layer((t_object *)x, NULL, gensym("space_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("points_layer"));
        jbox_redraw((t_jbox *)x);
    }
	return 0;
}

