/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa2D.pd.h"

typedef struct _hoa_space
{
    t_ebox      j_box;
    void*		f_out;
    long        f_number_of_channels;
    double      f_minmax[2];
    
    long		f_mode;
    double*     f_channel_values;
	double*     f_channel_refs;
    double*     f_channel_radius;
    double      f_value_ref;
    double      f_angle_ref;
    
	t_rgba      f_color_bg;
    t_rgba      f_color_bd;
	t_rgba		f_color_sp;
	t_rgba		f_color_pt;
    
	double		f_center;
    double      f_radius;
    
} t_hoa_space;

t_eclass *hoa_space_class;

void *hoa_space_new(t_symbol *s, int argc, t_atom *argv);
void hoa_space_free(t_hoa_space *x);
void hoa_space_assist(t_hoa_space *x, void *b, long m, long a, char *s);
void hoa_space_preset(t_hoa_space *x, t_binbuf *b);
void hoa_space_list(t_hoa_space *x, t_symbol *s, long ac, t_atom *av);
void hoa_space_output(t_hoa_space *x);

t_pd_err hoa_space_notify(t_hoa_space *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void hoa_space_getdrawparams(t_hoa_space *x, t_object *patcherview, t_edrawparams *params);
void hoa_space_oksize(t_hoa_space *x, t_rect *newrect);

void hoa_space_mouse_move(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_down(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_drag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);

void hoa_space_paint(t_hoa_space *x, t_object *view);
void draw_background(t_hoa_space *x, t_object *view, t_rect *rect);
void draw_space(t_hoa_space *x,  t_object *view, t_rect *rect);
void draw_points(t_hoa_space *x, t_object *view, t_rect *rect);

t_hoa_err hoa_getinfos(t_hoa_space* x, t_hoa_boxinfos* boxinfos);
t_pd_err channels_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv);
t_pd_err minmax_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv);

#define  contrast_white 0.06
#define  contrast_black 0.14

void hoa_space_deprecated(t_hoa_space* x, t_symbol *s, long ac, t_atom* av);

extern "C" void setup_hoa0x2e2d0x2espace(void)
{
    t_eclass* c;
    c = eclass_new("hoa.2d.space", (method)hoa_space_new, (method)hoa_space_free, sizeof(t_hoa_space), 0L, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_space_new, gensym("hoa.space"), A_GIMME, 0);
    
    eclass_init(c, 0);
    hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)hoa_space_assist,          "assist",         A_CANT,	0);
	eclass_addmethod(c, (method)hoa_space_paint,           "paint",          A_CANT,	0);
	eclass_addmethod(c, (method)hoa_space_notify,          "notify",         A_CANT, 0);
    eclass_addmethod(c, (method)hoa_space_output,          "bang",           A_CANT, 0);
    eclass_addmethod(c, (method)hoa_space_oksize,          "oksize",         A_CANT, 0);
	eclass_addmethod(c, (method)hoa_space_getdrawparams,   "getdrawparams",  A_CANT, 0);
	eclass_addmethod(c, (method)hoa_space_mouse_down,      "mousedown",      A_CANT, 0);
    eclass_addmethod(c, (method)hoa_space_mouse_move,      "mousemove",      A_CANT, 0);
	eclass_addmethod(c, (method)hoa_space_mouse_drag,      "mousedrag",      A_CANT, 0);
    eclass_addmethod(c, (method)hoa_space_preset,          "preset",         A_CANT, 0);
    eclass_addmethod(c, (method)hoa_space_list,            "list",           A_GIMME, 0);
    
    eclass_addmethod(c, (method)hoa_space_deprecated,      "bordercolor",    A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_space_deprecated,      "circolor",       A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_space_deprecated,      "miccolor",       A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_space_deprecated,      "harmocolor",     A_GIMME, 0);
    
    CLASS_ATTR_INVISIBLE            (c, "fontname", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontweight", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontslant", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontsize", 1);
    CLASS_ATTR_DEFAULT              (c, "size", 0, "225 225");
    
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
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "spcolor", 0, "0.27 0.43 0.54 0.25");
	
	CLASS_ATTR_RGBA					(c, "ptcolor", 0, t_hoa_space, f_color_pt);
	CLASS_ATTR_CATEGORY				(c, "ptcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "ptcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "ptcolor", 0, "Virtuals Microphones Color");
    CLASS_ATTR_ORDER                (c, "ptcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "ptcolor", 0, "0. 0. 0. 1.");
    
    eclass_register(CLASS_BOX, c);
    hoa_space_class = c;
}

void hoa_space_deprecated(t_hoa_space* x, t_symbol *s, long ac, t_atom* av)
{
    t_atom* argv;
    long argc;
    if(s && s == gensym("bordercolor") && ac && av)
    {
        object_attr_setvalueof((t_object *)x, gensym("bdcolor"), ac, av);
        object_error(x, "%s attribute @bordercolor is deprecated, please use @bdcolor.", eobj_getclassname(x)->s_name);
    }
    else if(s && s == gensym("miccolor") && ac && av)
    {
        object_attr_setvalueof((t_object *)x, gensym("ptcolor"), ac, av);
        object_error(x, "%s attribute @miccolor is deprecated, please use @ptcolor.", eobj_getclassname(x)->s_name);
    }
    else if(s && s == gensym("harmocolor") && ac && av)
    {
        object_attr_setvalueof((t_object *)x, gensym("spcolor"), ac, av);
        object_error(x, "%s attribute @harmocolor is deprecated, please use @spcolor.", eobj_getclassname(x)->s_name);
    }

    atoms_get_attribute(ac, av, gensym("@bordercolor"), &argc, &argv);
    if(argc && argv)
    {
        object_attr_setvalueof((t_object *)x, gensym("bdcolor"), argc, argv);
        object_error(x, "%s attribute @bordercolor is deprecated, please use @bdcolor.", eobj_getclassname(x)->s_name);
        argc = 0;free(argv);argv = NULL;
    }
    atoms_get_attribute(ac, av, gensym("@miccolor"), &argc, &argv);
    if(argc && argv)
    {
        object_attr_setvalueof((t_object *)x, gensym("ptcolor"), argc, argv);
        object_error(x, "%s attribute @miccolor is deprecated, please use @ptcolor.", eobj_getclassname(x)->s_name);
        argc = 0;free(argv);argv = NULL;
    }
    atoms_get_attribute(ac, av, gensym("@harmocolor"), &argc, &argv);
    if(argc && argv)
    {
        object_attr_setvalueof((t_object *)x, gensym("spcolor"), ac, av);
        object_error(x, "%s attribute @harmocolor is deprecated, please use @spcolor.", eobj_getclassname(x)->s_name);
        argc = 0;free(argv);argv = NULL;
    }
    
    if((s && s == gensym("circolor")) || atoms_has_attribute(ac, av, gensym("@circolor")))
    {
        object_error(x, "%s attribute @circolor is deprecated.", eobj_getclassname(x)->s_name);
    }
}

void *hoa_space_new(t_symbol *s, int argc, t_atom *argv)
{
    t_hoa_space *x = NULL;
    t_binbuf *d;
	long flags;
    
    if (!(d = binbuf_via_atoms(argc, argv)))
		return NULL;
    
    x = (t_hoa_space *)eobj_new(hoa_space_class);
    
    x->f_channel_values = new double[MAX_CHANNELS];
    x->f_channel_refs   = new double[MAX_CHANNELS];
    x->f_channel_radius = new double[MAX_CHANNELS];
    x->f_out                    = listout(x);

    flags = 0
    | EBOX_GROWLINK
    ;
    ebox_new((t_ebox *)x, flags);
    
    hoa_space_deprecated(x, NULL, argc, argv);
    
    ebox_attrprocess_viabinbuf(x, d);
    ebox_ready((t_ebox *)x);

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
            if(atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG)
            {
                x->f_channel_values[i] = clip_minmax(atom_getfloat(av+i), x->f_minmax[0], x->f_minmax[1]);
            }
        }
        
        hoa_space_output(x);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_space_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_points_layer);
        ebox_redraw((t_ebox *)x);
    }
}

void hoa_space_free(t_hoa_space *x)
{
    ebox_free((t_ebox *)x);
    delete [] x->f_channel_values;
    delete [] x->f_channel_refs;
    delete [] x->f_channel_radius;
}

void hoa_space_assist(t_hoa_space *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		sprintf(s,"(anything) Behavior and appearance");
	}
	else
	{
        sprintf(s,"(list) Channels coefficients");
	}
}

t_pd_err hoa_space_notify(t_hoa_space *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == hoa_sym_attr_modified)
	{
		name = s;
		
		if(name == hoa_sym_bgcolor || name == hoa_sym_bdcolor)
		{
			ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
		}
		else if(name == gensym("spcolor"))
		{
			ebox_invalidate_layer((t_ebox *)x, hoa_sym_space_layer);
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_points_layer);
		}
		else if(name == gensym("ptcolor"))
		{
			ebox_invalidate_layer((t_ebox *)x, hoa_sym_points_layer);
		}
		ebox_redraw((t_ebox *)x);
	}
	return 0;
}

void hoa_space_getdrawparams(t_hoa_space *x, t_object *patcherview, t_edrawparams *params)
{
    params->d_boxfillcolor = x->f_color_bg;
    params->d_bordercolor = x->f_color_bd;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

void hoa_space_oksize(t_hoa_space *x, t_rect *newrect)
{
    newrect->width = pd_clip_min(newrect->width, 20.);
    newrect->height = pd_clip_min(newrect->height, 20.);
}

/************************************************************************************/
/***************************** DRAW *************************************************/
/************************************************************************************/

void hoa_space_paint(t_hoa_space *x, t_object *view)
{
    t_rect rect;
	ebox_get_rect_for_view((t_ebox *)x, &rect);
	
	x->f_center = rect.width * .5;
	x->f_radius = x->f_center * 0.95;
	
	draw_background(x, view, &rect);
	draw_space(x, view, &rect);
	draw_points(x, view, &rect);
}

void draw_background(t_hoa_space *x, t_object *view, t_rect *rect)
{
    t_matrix transform;
    t_rgba black = rgba_addContrast(x->f_color_bg, -contrast_black);
    t_rgba white = rgba_addContrast(x->f_color_bg, contrast_white);
    
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_background_layer, rect->width, rect->height);
    
	if (g)
	{
		egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		egraphics_set_matrix(g, &transform);
        
        double angle, x1, x2, y1, y2, cosa, sina;
        for(int i = 0; i < x->f_number_of_channels ; i++)
		{
            angle = ((double)(i - 0.5) / (x->f_number_of_channels) * HOA_2PI);
        
			cosa = cos(angle);
            sina = sin(angle);
            x1 = cosa * x->f_radius * 0.2;
			y1 = sina * x->f_radius * 0.2;
            x2 = cosa * x->f_radius;
			y2 = sina * x->f_radius;
            
            egraphics_move_to(g, x1, y1);
			egraphics_line_to(g, x2, y2);
            egraphics_set_line_width(g, 3);
            egraphics_set_color_rgba(g, &white);
            egraphics_stroke(g);
            
            egraphics_set_color_rgba(g, &black);
			egraphics_set_line_width(g, 1);
			egraphics_stroke(g);

		}
        
        for(int i = 5; i > 0; i--)
		{
            egraphics_arc(g, 0, 0, (double)i * 0.2 * x->f_radius,  0., HOA_2PI);
            egraphics_set_line_width(g, 3);
            egraphics_set_color_rgba(g, &white);
            egraphics_stroke(g);
            
            egraphics_set_line_width(g, 1);
            egraphics_set_color_rgba(g, &black);
            egraphics_stroke(g);
		}
        
		ebox_end_layer((t_ebox *)x, hoa_sym_background_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_background_layer, 0., 0.);
}

double cosine_interpolation(double y1, double y2, float mu)
{
    double mu2;
    mu2 = (1-cos(mu*HOA_PI))/2;
    return(y1*(1-mu2)+y2*mu2);;
}

void draw_space(t_hoa_space *x, t_object *view, t_rect *rect)
{
    int i, index1, index2;
    double angle, radius, abscissa, ordinate, mu, diff, ratio;
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_space_layer, rect->width, rect->height);
    
	if (g)
	{
		t_matrix transform;
		egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		egraphics_set_matrix(g, &transform);
		egraphics_set_line_width(g, 2);
        egraphics_set_color_rgba(g, &x->f_color_sp);
		
        diff = x->f_minmax[1] - x->f_minmax[0];
        ratio = x->f_radius / 5.;
        for(i = 0; i < x->f_number_of_channels; i++)
		{
            x->f_channel_radius[i] = (x->f_channel_values[i] - x->f_minmax[0]) / diff *  4 * ratio + ratio;
        }
        
        abscissa = Hoa::abscissa(x->f_channel_radius[0], 0);
        ordinate = Hoa::ordinate(x->f_channel_radius[0], 0);
        egraphics_move_to(g, abscissa, ordinate);
        for(i = 1; i < NUMBEROFCIRCLEPOINTS_UI2; i++)
		{
            index1 = (double)i / (double)NUMBEROFCIRCLEPOINTS_UI2 * x->f_number_of_channels;
            index2 = index1+1;
            
            mu = (double)index1 / (double)x->f_number_of_channels * (double)NUMBEROFCIRCLEPOINTS_UI2;
            mu = (double)(i - mu) / ((double)NUMBEROFCIRCLEPOINTS_UI2 / (double)x->f_number_of_channels);
            if(index2 >= x->f_number_of_channels)
                index2 = 0;
            
            radius = cosine_interpolation(x->f_channel_radius[index1], x->f_channel_radius[index2], mu);
            angle  = (double)i / (double)NUMBEROFCIRCLEPOINTS_UI2 * HOA_2PI;
            abscissa = Hoa::abscissa(radius, angle);
            ordinate = Hoa::ordinate(radius, angle);
            egraphics_line_to(g, abscissa, ordinate);
        }
        
        egraphics_close_path(g);
        egraphics_fill_preserve(g);
        egraphics_stroke(g);
		ebox_end_layer((t_ebox*)x, hoa_sym_space_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_space_layer, 0., 0.);
}

void draw_points(t_hoa_space *x, t_object *view, t_rect *rect)
{
    int i;
    double angle, radius, abscissa, ordinate;
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_points_layer, rect->width, rect->height);
    
	if (g)
	{
		t_matrix transform;
		egraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center, x->f_center);
		egraphics_set_matrix(g, &transform);
		egraphics_set_color_rgba(g, &x->f_color_pt);
        
        for(i = 0; i < x->f_number_of_channels; i++)
		{
            radius = x->f_channel_radius[i] - 3.5;
            angle  = (double)(i + 1.) / (double)x->f_number_of_channels * HOA_2PI;
            angle -= HOA_2PI / (double)x->f_number_of_channels;
            abscissa = Hoa::abscissa(radius, angle);
            ordinate = Hoa::ordinate(radius, angle);
            egraphics_arc(g, abscissa, ordinate, 3., 0., HOA_2PI);
            egraphics_fill(g);
        }
        
        ebox_end_layer((t_ebox *)x, hoa_sym_points_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_points_layer, 0., 0.);
}

/**********************************************************/
/*                      Souris                            */
/**********************************************************/

void hoa_space_mouse_move(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if(modifiers == EMOD_ALT) // alt : rotation
        ebox_set_cursor((t_ebox *)x, 11);
    else if(modifiers == EMOD_SHIFT) // shift : gain
        ebox_set_cursor((t_ebox *)x, 10);
    else
        ebox_set_cursor((t_ebox *)x, 1);
}

void hoa_space_mouse_down(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt mouse;
    double rad;
    mouse.x = pt.x - x->f_center;
    mouse.y = x->f_center * 2. - pt.y - x->f_center;
    
    if(modifiers == EMOD_ALT) // alt : rotation
    {
        x->f_mode = 1;
        x->f_angle_ref = wrap_twopi(azimuth(mouse.x, mouse.y) - HOA_PI + (HOA_PI / (double)x->f_number_of_channels));
        memcpy(x->f_channel_refs, x->f_channel_values, x->f_number_of_channels * sizeof(double));
    }
    else if(modifiers == EMOD_SHIFT) // shift : gain
    {
        x->f_mode = 2;
        rad  = radius(mouse.x, mouse.y);
        x->f_value_ref   = (rad - (x->f_radius / 5.)) / (x->f_radius * 4. / 5.);
        x->f_value_ref  *= (x->f_minmax[1] - x->f_minmax[0]);
        x->f_value_ref  += x->f_minmax[0];
        x->f_value_ref   = clip_minmax(x->f_value_ref, x->f_minmax[0], x->f_minmax[1]);
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
    int index, index2;
    t_pt mouse;
    mouse.x = pt.x - x->f_center;
    mouse.y = x->f_center * 2. - pt.y - x->f_center;
    double angle, radius, value, inc, mu;
    
    if(x->f_mode == 1) // alt : rotation
    {
        angle   = wrap_twopi(azimuth(mouse.x, mouse.y) - HOA_PI + (HOA_PI / (double)x->f_number_of_channels));
        inc     = x->f_angle_ref - angle;
        for(int i = 0; i < x->f_number_of_channels; i++)
        {
            angle   = wrap_twopi((double)i / (double)x->f_number_of_channels * HOA_2PI + inc);
            index   = angle / HOA_2PI * x->f_number_of_channels;
            index2  = index+1;
            if(index2 >= x->f_number_of_channels)
                index2 = 0;
            
            mu = (double)index / (double)x->f_number_of_channels * (double)HOA_2PI;
            mu = (double)(angle - mu) / ((double)HOA_2PI / (double)x->f_number_of_channels);
            value = cosine_interpolation(x->f_channel_refs[index], x->f_channel_refs[index2], mu);
            x->f_channel_values[i] = clip_minmax(value, x->f_minmax[0], x->f_minmax[1]);
        }
    }
    else if(x->f_mode == 2) // shift : gain
    {
        radius  = Hoa::radius(mouse.x, mouse.y);
        inc     = (radius - (x->f_radius / 5.)) / (x->f_radius * 4. / 5.);
        inc    *= (x->f_minmax[1] - x->f_minmax[0]);
        inc    += x->f_minmax[0];
        inc     = inc - x->f_value_ref;
        for(int i = 0; i < x->f_number_of_channels; i++)
            x->f_channel_values[i] = clip_minmax(x->f_channel_refs[i] + inc, x->f_minmax[0], x->f_minmax[1]);
    }
    else
    {
        angle   = wrap_twopi(azimuth(mouse.x, mouse.y) + (HOA_PI / (double)x->f_number_of_channels));
        radius  = Hoa::radius(mouse.x, mouse.y);
        index   = angle / HOA_2PI * x->f_number_of_channels;
        value   = (radius - (x->f_radius / 5.)) / (x->f_radius * 4. / 5.);
        value  *= (x->f_minmax[1] - x->f_minmax[0]);
        value  += x->f_minmax[0];
        value   = clip_minmax(value, x->f_minmax[0], x->f_minmax[1]);
        x->f_channel_values[index] = value;
    }
    
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_space_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_points_layer);
    ebox_redraw((t_ebox *)x);
    hoa_space_output(x);
}

void hoa_space_output(t_hoa_space *x)
{
    t_atom argv[MAX_CHANNELS];
    for(int i = 0; i < x->f_number_of_channels; i++)
        atom_setfloat(argv+i, x->f_channel_values[i]);
    
    outlet_list((t_outlet *)x->f_out, &s_list, x->f_number_of_channels, argv);
    if(ebox_getsender((t_ebox *) x))
        pd_list(ebox_getsender((t_ebox *) x), &s_list, x->f_number_of_channels, argv);
}

t_pd_err channels_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv)
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
            
            ebox_invalidate_layer((t_ebox*)x, hoa_sym_background_layer);
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_space_layer);
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_points_layer);
            ebox_redraw((t_ebox *)x);
        }
    }
	return 0;
}

t_pd_err minmax_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv)
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
            x->f_channel_values[i] = clip_minmax(x->f_channel_values[i], x->f_minmax[0], x->f_minmax[1]);
        
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_space_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_points_layer);
        ebox_redraw((t_ebox *)x);
    }
	return 0;
}


void hoa_space_preset(t_hoa_space *x, t_binbuf *b)
{
    binbuf_addv(b, "s", gensym("list"));
    for(int i = 0; i < x->f_number_of_channels; i++)
    {
        binbuf_addv(b, "f", (float)x->f_channel_values[i]);
    }
}






