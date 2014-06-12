/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa2D.pd.h"

#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

typedef struct  _hoa_map
{
	t_ebox          j_box;
	t_rect          rect;
    
	t_outlet*		f_out_sources;
    t_outlet*		f_out_groups;
    t_outlet*		f_out_infos;
    
    SourcesManager*     f_source_manager;
    
    t_pt        f_cursor_position;
    long        f_index_of_selected_source;
    long        f_index_of_selected_group;
    long        f_index_of_source_to_remove;
    long        f_index_of_group_to_remove;
    long        f_index_of_source_to_color;
    long        f_index_of_group_to_color;
    
    t_rgba      f_color_bg;
    t_rgba      f_color_bd;
    
    double      f_size_source;
	double		f_zoom_factor;
    
    t_rect		f_rect_selection;
	int			f_rect_selection_exist;
    
    t_symbol*   f_output_mode;
    long        f_read;
    long        f_write;
    _hoa_map*   f_friend;
} t_hoa_map;

t_eclass *hoa_map_class;

void *hoa_map_new(t_symbol *s, int argc, t_atom *argv);
void hoa_map_free(t_hoa_map *x);
void hoa_map_getdrawparams(t_hoa_map *x, t_object *patcherview, t_edrawparams *params);
void hoa_map_oksize(t_hoa_map *x, t_rect *newrect);
void hoa_map_assist(t_hoa_map *x, void *b, long m, long a, char *s);
t_pd_err hoa_map_notify(t_hoa_map *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_pd_err hoa_map_zoom(t_hoa_map *x, t_object *attr, long argc, t_atom *argv);
void hoa_map_popup(t_hoa_map *x, t_symbol *s, long itemid);

void hoa_map_preset(t_hoa_map *x, t_binbuf *b);
void hoa_map_sources_preset(t_hoa_map *x, t_symbol *s, short ac, t_atom *av);
void hoa_map_interpolate(t_hoa_map *x, short ac, t_atom *av, short ac2, t_atom* av2, t_atom theta);

void hoa_map_source(t_hoa_map *x, t_symbol *s, short ac, t_atom *av);
void hoa_map_group(t_hoa_map *x, t_symbol *s, short ac, t_atom *av);
void hoa_map_slot(t_hoa_map *x, t_symbol *s, short ac, t_atom *av);
void hoa_map_trajectory(t_hoa_map *x, t_symbol *s, short ac, t_atom *av);
void hoa_map_bang(t_hoa_map *x);
void hoa_map_infos(t_hoa_map *x);
void hoa_map_clear_all(t_hoa_map *x);

/* Paint Methods */
void hoa_map_paint(t_hoa_map *x, t_object *view);
void draw_background(t_hoa_map *x, t_object *view, t_rect *rect);
void draw_sources(t_hoa_map *x,  t_object *view, t_rect *rect);
void draw_groups(t_hoa_map *x,  t_object *view, t_rect *rect);
void draw_rect_selection(t_hoa_map *x,  t_object *view, t_rect *rect);

void hoa_map_mousedown(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_map_mousedrag(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_map_mouseup(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_map_mousemove(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_map_mousewheel(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc);
long hoa_map_key(t_hoa_map *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);

t_hoa_err hoa_getinfos(t_hoa_map* x, t_hoa_boxinfos* boxinfos);
/*
void hoa_map_bind(t_hoa_map* x, t_symbol* name)
{
    char scrptname[MAXPDSTRING];
    sprintf(scrptname, "%s_hoamap_xx1", name->s_name);
    if(gensym(scrptname)->s_thing)
    {
        x->f_friend = (t_hoa_map *)gensym(scrptname)->s_thing;
        x->f_friend->f_friend = x;
        sprintf(scrptname, "%s_hoamap_xx2", name->s_name);
        t_symbol *newsym = gensym(scrptname);
        newsym->s_thing = (t_class **)x;
    }
    else
    {
        gensym(scrptname)->s_thing = (t_class **)x;
    }
}
*/
#define  contrast_white 0.06
#define  contrast_black 0.14

void hoa_map_deprecated(t_hoa_map* x, t_symbol *s, long ac, t_atom* av);

t_symbol *hoa_sym_sources_preset;

extern "C" void setup_hoa0x2e2d0x2emap(void)
{
	t_eclass *c;
    
	c = eclass_new("hoa.2d.map", (method)hoa_map_new, (method)hoa_map_free, sizeof(t_hoa_map), 0L, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_map_new, gensym("hoa.map"), A_GIMME, 0);
    
    eclass_init(c, 0);
    
    eclass_addmethod(c, (method) hoa_map_assist,          "assist",             A_CANT,    0);
	eclass_addmethod(c, (method) hoa_map_paint,           "paint",              A_CANT,    0);
	eclass_addmethod(c, (method) hoa_map_getdrawparams,   "getdrawparams",      A_CANT,    0);
    eclass_addmethod(c, (method) hoa_map_oksize,          "oksize",             A_CANT,    0);
	eclass_addmethod(c, (method) hoa_map_notify,          "notify",             A_CANT,    0);
    eclass_addmethod(c, (method) hoa_map_bang,            "bang",               A_CANT,    0);
    eclass_addmethod(c, (method) hoa_map_infos,           "getinfo",            A_CANT,    0);
    
    eclass_addmethod(c, (method) hoa_map_source,           "source",            A_GIMME,   0);
    eclass_addmethod(c, (method) hoa_map_group,            "group",             A_GIMME,   0);
    eclass_addmethod(c, (method) hoa_map_clear_all,        "clear",             A_CANT ,   0);
    
    eclass_addmethod(c, (method) hoa_map_mousedown,        "mousedown",         A_CANT,     0);
    eclass_addmethod(c, (method) hoa_map_mousedrag,        "mousedrag",         A_CANT,     0);
    eclass_addmethod(c, (method) hoa_map_mouseup,          "mouseup",           A_CANT,     0);
    eclass_addmethod(c, (method) hoa_map_mousemove,        "mousemove",         A_CANT,     0);
    eclass_addmethod(c, (method) hoa_map_mousewheel,       "mousewheel",        A_CANT,     0);
    eclass_addmethod(c, (method) hoa_map_key,              "key",               A_CANT,     0);
	eclass_addmethod(c, (method) hoa_map_popup,            "popup",             A_CANT,     0);
    
    eclass_addmethod(c, (method) hoa_map_preset,           "preset",            A_CANT,     0);
    eclass_addmethod(c, (method) hoa_map_interpolate,      "interpolate",       A_CANT,     0);
    eclass_addmethod(c, (method) hoa_map_sources_preset,   "sources_preset",    A_GIMME,    0);
    
    eclass_addmethod(c, (method) hoa_map_deprecated,        "bgcolor2",         A_GIMME,    0);
    eclass_addmethod(c, (method) hoa_map_deprecated,        "bordercolor",      A_GIMME,    0);
    eclass_addmethod(c, (method) hoa_map_deprecated,        "selcolor",         A_GIMME,    0);
    eclass_addmethod(c, (method) hoa_map_deprecated,        "slot",             A_GIMME,   0);
    eclass_addmethod(c, (method) hoa_map_deprecated,        "trajectory",       A_GIMME,   0);
    
	CLASS_ATTR_DEFAULT              (c, "size", 0, "225 225");
    
    CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_hoa_map, f_color_bg);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.76 0.76 0.76 1.");
	
    CLASS_ATTR_RGBA					(c, "bdcolor", 0, t_hoa_map, f_color_bd);
	CLASS_ATTR_CATEGORY				(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bdcolor", 0, "0.7 0.7 0.7 1.");
	
	CLASS_ATTR_SYMBOL               (c, "outputmode", 0, t_hoa_map, f_output_mode);
	CLASS_ATTR_LABEL                (c, "outputmode", 0, "Output Mode");
	CLASS_ATTR_CATEGORY             (c, "outputmode", 0, "Behavior");
	CLASS_ATTR_DEFAULT              (c, "outputmode", 0, "polar");
    CLASS_ATTR_SAVE                 (c, "outputmode", 1);
    CLASS_ATTR_ORDER                (c, "outputmode", 0, "1");
    CLASS_ATTR_STYLE                (c, "outputmode", 1, "menu");
    CLASS_ATTR_ITEMS                (c, "outputmode", 1, "polar cartesian");
    
	CLASS_ATTR_DOUBLE               (c, "zoom", 0, t_hoa_map, f_zoom_factor);
    CLASS_ATTR_ACCESSORS            (c, "zoom", NULL, hoa_map_zoom);
	CLASS_ATTR_LABEL                (c, "zoom", 0, "Zoom");
	CLASS_ATTR_CATEGORY             (c, "zoom", 0, "Behavior");
	CLASS_ATTR_DEFAULT              (c, "zoom", 0, "0.35");
    CLASS_ATTR_ORDER                (c, "zoom", 0, "2");
    CLASS_ATTR_SAVE                 (c, "zoom", 0);
    CLASS_ATTR_PAINT                (c, "zoom", 0);
    CLASS_ATTR_STYLE                (c, "zoom", 0, "number");
    
    eclass_register(CLASS_BOX, c);
	hoa_map_class = c;
    
    hoa_sym_sources_preset = gensym("sources_preset");
}

void hoa_map_deprecated(t_hoa_map* x, t_symbol *s, long ac, t_atom* av)
{
    t_atom* argv;
    long argc;

    for(int i = 0; i < ac; i++)
    {
        if(atom_gettype(av+i) == A_SYM)
        {
            if(atom_getsym(av+i) == gensym("trajectory_parameters"))
                atom_setsym(av+i, hoa_sym_trajectory_parameters);
            else if(atom_getsym(av+i) == gensym("slots_parameters"))
                atom_setsym(av+i, hoa_sym_slots_parameters);
            else if(atom_getsym(av+i) == gensym("sources_parameters"))
                atom_setsym(av+i, hoa_sym_sources_parameters);
            else if(atom_getsym(av+i) == gensym("groups_parameters"))
                atom_setsym(av+i, hoa_sym_groups_parameters);
            else if(atom_getsym(av+i) == gensym("s_nosymbol"))
                atom_setsym(av+i, gensym("(null)"));
        }
    }
    
    if(s && s == gensym("bordercolor") && ac && av)
    {
        object_attr_setvalueof((t_object *)x, gensym("bdcolor"), ac, av);
        object_error(x, "%s attribute @bordercolor is deprecated, please use @bdcolor.", eobj_getclassname(x)->s_name);
    }
    if(s && s == gensym("bgcolor2"))
        object_error(x, "%s attribute @bgcolor2 is deprecated.", eobj_getclassname(x)->s_name);
    if(s && s == gensym("selcolor"))
        object_error(x, "%s attribute @selcolor is deprecated.", eobj_getclassname(x)->s_name);
    
    atoms_get_attribute(ac, av, gensym("@bordercolor"), &argc, &argv);
    if(argc && argv)
    {
        object_attr_setvalueof((t_object *)x, gensym("bdcolor"), argc, argv);
        object_error(x, "%s attribute @bordercolor is deprecated, please use @bdcolor.", eobj_getclassname(x)->s_name);
        argc = 0;free(argv);argv = NULL;
    }
    atoms_get_attribute(ac, av, gensym("@bgcolor2"), &argc, &argv);
    if(argc && argv)
    {
        object_error(x, "%s attribute @bgcolor2 is deprecated.", eobj_getclassname(x)->s_name);
        argc = 0;free(argv);argv = NULL;
    }
    atoms_get_attribute(ac, av, gensym("@selcolor"), &argc, &argv);
    if(argc && argv)
    {
        object_error(x, "%s attribute @selcolor is deprecated.", eobj_getclassname(x)->s_name);
        argc = 0;free(argv);argv = NULL;
    }
    
    if(atoms_has_attribute(ac, av, hoa_sym_trajectory_parameters))
        object_error(x, "%s trajectory is deprecated, please use the preset object.", eobj_getclassname(x)->s_name);
    if(atoms_has_attribute(ac, av, hoa_sym_slots_parameters))
        object_error(x, "%s slots is deprecated, please use the preset object.", eobj_getclassname(x)->s_name);
    if(atoms_has_attribute(ac, av, hoa_sym_sources_parameters))
        object_error(x, "%s sources are no more saved within the canvas, please use the preset object.", eobj_getclassname(x)->s_name);
    if(atoms_has_attribute(ac, av, hoa_sym_groups_parameters))
        object_error(x, "%s groups are no more saved within the canvas, please use the preset object.", eobj_getclassname(x)->s_name);
}

void *hoa_map_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_map *x =  NULL;
	t_binbuf *d;
	long flags;
    
	if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;
    
    x = (t_hoa_map *)eobj_new(hoa_map_class);
    if (x)
    {
        flags = 0
        | EBOX_GROWLINK
        ;
        
        ebox_new((t_ebox *)x, flags);
        x->f_source_manager     = new SourcesManager(1. / (double)MIN_ZOOM - 5.);
        
        x->f_rect_selection_exist = 0;
        x->f_index_of_selected_source = -1;
        x->f_index_of_selected_group = -1;
        x->f_read   = 0;
        x->f_write  = 0;
        x->f_out_sources    = listout(x);
        x->f_out_groups     = listout(x);
        x->f_out_infos      = listout(x);
        
        hoa_map_deprecated(x, NULL, argc, argv);
        ebox_attrprocess_viabinbuf(x, d);
        
        ebox_ready((t_ebox *)x);
    }
    
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_map* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs    = 0;
	boxinfos->autoconnect_outputs   = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_map_free(t_hoa_map *x)
{
    ebox_free((t_ebox *)x);
    delete x->f_source_manager;
}

void hoa_map_assist(t_hoa_map *x, void *b, long m, long a, char *s)
{
	;
}

void hoa_map_getdrawparams(t_hoa_map *x, t_object *patcherview, t_edrawparams *params)
{
    params->d_boxfillcolor = x->f_color_bg;
    params->d_bordercolor = x->f_color_bd;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

void hoa_map_oksize(t_hoa_map *x, t_rect *newrect)
{
    newrect->width = pd_clip_min(newrect->width, 20.);
    newrect->height = pd_clip_min(newrect->height, 20.);
}

/**********************************************************/
/*          Intialisation par l'utilisateur               */
/**********************************************************/

void hoa_map_clear_all(t_hoa_map *x)
{
    x->f_source_manager->clearAll();
  
    ebox_notify((t_ebox *)x, NULL, hoa_sym_modified, NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    ebox_redraw((t_ebox *)x);
    hoa_map_bang(x);
}

void hoa_map_source(t_hoa_map *x, t_symbol *s, short ac, t_atom *av)
{
    int index;
    if(ac && av && atom_gettype(av)==A_LONG && atom_getlong(av) >= 1 && atom_gettype(av+1) == A_SYM)
    {
        index = atom_getlong(av) -1;
        if(atom_getsym(av+1) == hoa_sym_polar || atom_getsym(av+1) == hoa_sym_pol)
            x->f_source_manager->sourceSetPolar(index, atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == hoa_sym_radius)
            x->f_source_manager->sourceSetRadius(index, atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_angle)
            x->f_source_manager->sourceSetAzimuth(index, atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_cartesian || atom_getsym(av+1) == hoa_sym_car)
            x->f_source_manager->sourceSetCartesian(index, atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == hoa_sym_abscissa)
            x->f_source_manager->sourceSetAbscissa(index, atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_ordinate)
            x->f_source_manager->sourceSetOrdinate(index, atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_remove)
        {
            x->f_source_manager->sourceRemove(index);
            t_atom av[3];
            atom_setlong(av, index+1);
            atom_setsym(av+1, hoa_sym_mute);
            atom_setlong(av+2, 1);
            outlet_list(x->f_out_sources, &s_list, 3, av);
        }
        else if(atom_getsym(av+1) == hoa_sym_mute)
            x->f_source_manager->sourceSetMute(index, atom_getlong(av+2));
        else if(atom_getsym(av+1) == hoa_sym_description)
        {
            char description[250];
            char number[250];
            if(atom_gettype(av+1) == A_SYM)
            {
                strcpy(description, atom_getsym(av+2)->s_name);
                strcat(description, " ");
                if(atom_getsym(av+2) == hoa_sym_remove)
                {
                    x->f_source_manager->sourceSetDescription(index, "");
                    ebox_notify((t_ebox *)x, NULL, hoa_sym_modified, NULL, NULL);
                    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
                    ebox_redraw((t_ebox *)x);
                    return;
                }
            }
            for(int i = 3; i < ac; i++)
            {
                if(atom_gettype(av+i) == A_SYM)
                {
                    strcat(description, atom_getsym(av+i)->s_name);
                    strcat(description, " ");
                }
                else if(atom_gettype(av+i) == A_LONG)
                {
                    sprintf(number, "%ld ", (long)atom_getlong(av+i));
                    strcat(description, number);
                }
                else if(atom_gettype(av+i) == A_FLOAT)
                {
                    sprintf(number, "%f ", atom_getfloat(av+i));
                    strcat(description, number);
                }
            }
            x->f_source_manager->sourceSetDescription(index, description);
        }
        else if(atom_getsym(av+1) == gensym("color"))
        {
            x->f_source_manager->sourceSetColor(index, atom_getfloat(av+2), atom_getfloat(av+3), atom_getfloat(av+4), atom_getfloat(av+5));
        }
        
    }
    ebox_notify((t_ebox *)x, NULL, hoa_sym_modified, NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    ebox_redraw((t_ebox *)x);
    hoa_map_bang(x);
}

void hoa_map_group(t_hoa_map *x, t_symbol *s, short ac, t_atom *av)
{
    int index;
    if(ac && av && atom_gettype(av) == A_LONG && atom_getlong(av) >= 1 && atom_gettype(av+1) == A_SYM)
    {
        index = atom_getlong(av) -1;
        if(atom_getsym(av+1) == hoa_sym_set)
        {
            x->f_source_manager->groupRemove(index);
            for(int i = 2; i < ac; i++)
            {
                x->f_source_manager->groupSetSource(index, atom_getlong(av+i)-1);
            }
        }        
        else if(atom_getsym(av+1) == hoa_sym_polar || atom_getsym(av+1) == hoa_sym_pol)
            x->f_source_manager->groupSetPolar(index, atom_getfloat(av+2), atom_getfloat(av+3) + HOA_PI2);
        else if(atom_getsym(av+1) == hoa_sym_radius)
            x->f_source_manager->groupSetRadius(index, atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_angle)
            x->f_source_manager->groupSetAzimuth(index, atom_getfloat(av+2) + HOA_PI2);
        else if(atom_getsym(av+1) == hoa_sym_cartesian || atom_getsym(av+1) == hoa_sym_car)
            x->f_source_manager->groupSetCartesian(index, atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == hoa_sym_abscissa)
            x->f_source_manager->groupSetAbscissa(index, atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_ordinate)
            x->f_source_manager->groupSetOrdinate(index, atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_relpolar || atom_getsym(av+1) == hoa_sym_relativepolar)
            x->f_source_manager->groupSetRelativePolar(index, atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == hoa_sym_relradius || atom_getsym(av+1) == hoa_sym_relativeradius)
            x->f_source_manager->groupSetRelativeRadius(index, atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_relangle || atom_getsym(av+1) == hoa_sym_relativeangle)
            x->f_source_manager->groupSetRelativeAzimuth(index, atom_getfloat(av+2) + HOA_PI2);
        else if(atom_getsym(av+1) == hoa_sym_mute)
            x->f_source_manager->groupSetMute(index, atom_getlong(av+2));
        else if(atom_getsym(av+1) == hoa_sym_remove)
        {
            x->f_source_manager->groupRemove(index);
            t_atom av[3];
            atom_setlong(av, index + 1);
            atom_setsym(av+1, hoa_sym_mute);
            atom_setlong(av+2, 1);
            outlet_list(x->f_out_groups, 0L, 3, av);
        }
        else if(atom_getsym(av+1) == hoa_sym_description)
        {
            char description[250];
            char number[250];
            if(atom_gettype(av+1) == A_SYM)
            {
                strcpy(description, atom_getsym(av+2)->s_name);
                strcat(description, " ");
                if(atom_getsym(av+2) == hoa_sym_remove)
                {
                    x->f_source_manager->groupSetDescription(index, "");
                    ebox_notify((t_ebox *)x, NULL, hoa_sym_modified, NULL, NULL);
                    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
                    ebox_redraw((t_ebox *)x);
                    return;
                }
            }
            for(int i = 3; i < ac; i++)
            {
                if(atom_gettype(av+i) == A_SYM)
                {
                    strcat(description, atom_getsym(av+i)->s_name);
                    strcat(description, " ");
                }
                else if(atom_gettype(av+i) == A_LONG)
                {
                    sprintf(number, "%ld ", (long)atom_getlong(av+i));
                    strcat(description, number);
                }
                else if(atom_gettype(av+i) == A_FLOAT)
                {
                    sprintf(number, "%f ", atom_getfloat(av+i));
                    strcat(description, number);
                }
            }
            x->f_source_manager->groupSetDescription(index, description);
        }
        else if(atom_getsym(av+1) == gensym("color"))
        {
            x->f_source_manager->groupSetColor(index, atom_getfloat(av+2), atom_getfloat(av+3), atom_getfloat(av+4), atom_getfloat(av+5));
        }
    }
    
    ebox_notify((t_ebox *)x, NULL, hoa_sym_modified, NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    ebox_redraw((t_ebox *)x);
    hoa_map_bang(x);    
}

t_pd_err hoa_map_zoom(t_hoa_map *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_zoom_factor = atom_getfloat(argv);
        x->f_zoom_factor = clip_minmax(x->f_zoom_factor, MIN_ZOOM, MAX_ZOOM);
    }
    
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    return 0;
}

t_pd_err hoa_map_notify(t_hoa_map *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if (msg == gensym("attr_modified"))
    {
        if(s == gensym("bgcolor"))
        {
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
        }
        else if(s == gensym("fontname") || s == gensym("fontface") || s == gensym("fontsize"))
        {
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
        }
        else if(s == gensym("zoom"))
        {
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
            ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
        }
        ebox_redraw((t_ebox *)x);
    }
    
    
	return ebox_notify((t_ebox *)x, s, msg, sender, data);
}

/**********************************************************/
/*                          Sortie                        */
/**********************************************************/

void hoa_map_bang(t_hoa_map *x)
{
    t_atom av[4];
    atom_setsym(av+1, hoa_sym_mute);
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(av, i+1);
            atom_setlong(av+2, x->f_source_manager->sourceGetMute(i));
            outlet_list(x->f_out_sources, &s_list, 3, av);
        }
    }
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(av, i+1);
            atom_setfloat(av+2, x->f_source_manager->groupGetMute(i));
            outlet_list(x->f_out_groups, &s_list, 4, av);
        }
    }
    if(x->f_output_mode == hoa_sym_polar)
    {
        atom_setsym(av+1, hoa_sym_polar);
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av, i+1);
                atom_setfloat(av+2, x->f_source_manager->sourceGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->sourceGetAzimuth(i));
                outlet_list(x->f_out_sources, &s_list, 4, av);
            }
        }
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                atom_setlong(av, i+1);
                atom_setfloat(av+2, x->f_source_manager->groupGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->groupGetAzimuth(i));
                outlet_list(x->f_out_groups, &s_list, 4, av);
            }
        }
        
    }
    else
    {
        atom_setsym(av+1, hoa_sym_cartesian);
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av, i+1);
                atom_setfloat(av+2,x->f_source_manager->sourceGetAbscissa(i));
                atom_setfloat(av+3,x->f_source_manager->sourceGetOrdinate(i));
                outlet_list(x->f_out_sources, &s_list, 4, av);
            }
        }
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                atom_setlong(av, i+1);
                atom_setfloat(av+2, x->f_source_manager->groupGetAbscissa(i));
                atom_setfloat(av+3, x->f_source_manager->groupGetOrdinate(i));
                outlet_list(x->f_out_groups, &s_list, 4, av);
            }
        }
    }
}

void hoa_map_infos(t_hoa_map *x)
{
    t_atom avNumber[3];
    t_atom* avIndex;
    t_atom* avSource;
    t_atom avMute[4];
    
    /* Sources */
    long numberOfSource = 0;
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        
        if(x->f_source_manager->sourceGetExistence(i))
        {
            numberOfSource++;
        }
    }
    atom_setsym(avNumber, hoa_sym_source);
    atom_setsym(avNumber+1, hoa_sym_number);
    atom_setlong(avNumber+2, numberOfSource);
    outlet_list(x->f_out_infos, &s_list, 3, avNumber);
    
    avIndex = new t_atom[numberOfSource+2];
    atom_setsym(avIndex, hoa_sym_source);
    atom_setsym(avIndex+1, hoa_sym_index);
    for(int i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(avIndex+j+2, i);
            j++;
        }
    }
    outlet_list(x->f_out_infos, 0L, numberOfSource+2, avIndex);
    free(avIndex);
    
    atom_setsym(avMute, hoa_sym_source);
    atom_setsym(avMute+1, hoa_sym_mute);
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(avMute+2, i);
            atom_setlong(avMute+3, x->f_source_manager->sourceGetMute(i));
            outlet_list(x->f_out_infos, &s_list, 4, avMute);
        }
    }
    
    /* Groups */
    long numberOfGroups = 0;
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            numberOfGroups++;
        }
    }
    atom_setsym(avNumber, hoa_sym_group);
    atom_setsym(avNumber+1, hoa_sym_number);
    atom_setlong(avNumber+2, numberOfGroups);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);
    
    avIndex = new t_atom[numberOfGroups+2];
    atom_setsym(avIndex, hoa_sym_group);
    atom_setsym(avIndex+1, hoa_sym_index);
    for(int i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(avIndex+j+2, i);
            j++;
            avSource = new t_atom[x->f_source_manager->groupGetNumberOfSources(i)+3];
            atom_setsym(avSource, hoa_sym_group);
            atom_setsym(avSource+1, hoa_sym_source);
            atom_setlong(avSource+2, i);
            for(int k = 0; k < x->f_source_manager->groupGetNumberOfSources(i); k++)
            {
                atom_setlong(avSource+3+k,x->f_source_manager->groupGetSourceIndex(i, k));
            }
            outlet_list(x->f_out_infos, &s_list, x->f_source_manager->groupGetNumberOfSources(i)+3, avSource);
            free(avSource);
        }
    }
    outlet_list(x->f_out_infos, &s_list, numberOfGroups+2, avIndex);
    free(avIndex);
    
    atom_setsym(avMute, hoa_sym_group);
    atom_setsym(avMute+1, hoa_sym_mute);
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(avMute+2, i);
            atom_setlong(avMute+3, x->f_source_manager->groupGetMute(i));
            outlet_list(x->f_out_infos, &s_list, 4, avMute);
        }
    }
}

/**********************************************************/
/*                          Paint                         */
/**********************************************************/

void hoa_map_paint(t_hoa_map *x, t_object *view)
{
    t_rect rect;
    ebox_get_rect_for_view((t_ebox *)x, &rect);
	x->rect = rect;
    
    x->f_source_manager->groupClean();
	draw_background(x, view, &rect);
    draw_rect_selection(x, view, &rect);
    draw_sources(x, view, &rect);
    draw_groups(x, view, &rect);
}

void draw_background(t_hoa_map *x,  t_object *view, t_rect *rect)
{
    t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_background_layer, rect->width, rect->height);

    t_rgba black = rgba_addContrast(x->f_color_bg, -0.14);
	if (g)
    {
        egraphics_set_color_rgba(g, &x->f_color_bg);
        egraphics_arc(g, rect->width / 2., rect->width / 2., (rect->width / 2.) * (1. / MIN_ZOOM * x->f_zoom_factor) - 1.,  0., EPD_2PI);
        egraphics_fill(g);
        
        /* Circles */
        double radius  = x->f_zoom_factor * rect->width / 10.;
        for(int i = 5; i > 0; i--)
        {
            
            egraphics_set_line_width(g, 2);
            egraphics_set_color_rgba(g, &x->f_color_bg);
            egraphics_arc(g, rect->width / 2 - 0.5, rect->width / 2 - 0.5, (double)i * radius - 1.,  0., EPD_2PI);
            egraphics_stroke(g);
            
            egraphics_set_line_width(g, 1);
            egraphics_set_color_rgba(g, &black);
            egraphics_arc(g, rect->width / 2, rect->width / 2, (double)i * radius - 1.,  0., EPD_2PI);
            egraphics_stroke(g);
            
        }
        
        double ecart = x->f_zoom_factor * rect->width / 2.;
        if(ecart < 10 && ecart >= 5)
            ecart *= 2;
        else if(ecart < 5 && ecart > 2.5)
            ecart *= 4;
        else if(ecart < 2.5)
            ecart *= 8;
        
        ecart = (int)ecart;
		for(double i = 0; i < rect->width / 2.; i += ecart)
        {
            egraphics_set_line_width(g, 2);
            egraphics_set_color_rgba(g, &x->f_color_bg);
            egraphics_move_to(g, 0. - 0.5, rect->width / 2. - i - 0.5);
            egraphics_line_to(g, rect->width - 0.5, rect->width / 2. - i - 0.5);
            egraphics_stroke(g);
            egraphics_move_to(g, 0. - 0.5, rect->width / 2. + i - 0.5);
            egraphics_line_to(g, rect->width - 0.5, rect->width / 2. + i - 0.5);
            egraphics_stroke(g);
            egraphics_move_to(g, rect->width / 2. - i - 0.5, 0. - 0.5);
            egraphics_line_to(g, rect->width / 2. - i - 0.5, rect->width - 0.5);
            egraphics_stroke(g);
            egraphics_move_to(g, rect->width / 2. + i - 0.5, 0. - 0.5);
            egraphics_line_to(g, rect->width / 2. + i - 0.5, rect->width - 0.5);
            egraphics_stroke(g);
            
            egraphics_set_line_width(g, 1);
            egraphics_set_color_rgba(g, &black);
            egraphics_move_to(g, 0., rect->width / 2. - i);
            egraphics_line_to(g, rect->width, rect->width / 2. - i);
            egraphics_stroke(g);
            egraphics_move_to(g, 0., rect->width / 2. + i);
            egraphics_line_to(g, rect->width, rect->width / 2. + i);
            egraphics_stroke(g);
            egraphics_move_to(g, rect->width / 2. - i, 0.);
            egraphics_line_to(g, rect->width / 2. - i, rect->width);
            egraphics_stroke(g);
            egraphics_move_to(g, rect->width / 2. + i, 0.);
            egraphics_line_to(g, rect->width / 2. + i, rect->width);
            egraphics_stroke(g);
        }
        
		ebox_end_layer((t_ebox *)x, hoa_sym_background_layer);
	}
	ebox_paint_layer((t_ebox *)x, hoa_sym_background_layer, 0., 0.);
}

void draw_sources(t_hoa_map *x,  t_object *view, t_rect *rect)
{
	int i;
	double font_size;
	t_etext *jtl;
	t_rgba sourceColor;
	char description[250];
	double descriptionPositionX;
    double descriptionPositionY;
	double sourcePositionX;
    double sourcePositionY;
    
    double w = rect->width;
    double h = rect->height;
    t_pt ctr = {w*0.5, h*0.5};
	
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_sources_layer, rect->width, rect->height);
	t_rgba color_sel = rgba_addContrast(x->f_color_bg, -0.14);
    
    x->f_size_source = ebox_getfontsize((t_ebox *)x) / 1.5;
    font_size = ebox_getfontsize((t_ebox *)x);
    
    char text[] = "s";
	if (g)
    {
        jtl = etext_layout_create();
        egraphics_set_line_width(g, 1.);
        
		for(i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                sourcePositionX = (x->f_source_manager->sourceGetAbscissa(i) * x->f_zoom_factor + 1.) * ctr.x;
                sourcePositionY = (-x->f_source_manager->sourceGetOrdinate(i) * x->f_zoom_factor + 1.) * ctr.y;
			
                sourceColor.red = x->f_source_manager->sourceGetColor(i)[0];
                sourceColor.green = x->f_source_manager->sourceGetColor(i)[1];
                sourceColor.blue = x->f_source_manager->sourceGetColor(i)[2];
                sourceColor.alpha = x->f_source_manager->sourceGetColor(i)[3];

                if(x->f_source_manager->sourceGetDescription(i).c_str()[0])
                    sprintf(description,"%i : %s", i+1, x->f_source_manager->sourceGetDescription(i).c_str());
                else
                    sprintf(description,"%i", i+1);
                    
                descriptionPositionX = sourcePositionX - 2. * x->f_size_source;
                descriptionPositionY = sourcePositionY - x->f_size_source - font_size - 1.;

                etext_layout_settextcolor(jtl, &sourceColor);
                etext_layout_set(jtl, description, &x->j_box.b_font, descriptionPositionX, descriptionPositionY, font_size * 10., font_size * 2., ETEXT_LEFT, ETEXT_JCENTER, ETEXT_NOWRAP);
                etext_layout_draw(jtl, g);
			
                if (x->f_index_of_selected_source == i)
                {
                    egraphics_set_color_rgba(g, &color_sel);
                    egraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.5,  0., EPD_2PI);
                    egraphics_fill(g);
                    int groupIndex;
                    double groupPositionX, groupPositionY;
                  
                    for(int index = 0; index < x->f_source_manager->sourceGetNumberOfGroups(i); index++)
                    {
                        egraphics_move_to(g, sourcePositionX, sourcePositionY);
                        groupIndex = x->f_source_manager->sourceGetGroupIndex(i, index);
                        groupPositionX = (x->f_source_manager->groupGetAbscissa(groupIndex) * x->f_zoom_factor + 1.) * ctr.x;
                        groupPositionY = (-x->f_source_manager->groupGetOrdinate(groupIndex) * x->f_zoom_factor + 1.) * ctr.y;
                       
                        egraphics_line_to(g, groupPositionX, groupPositionY);
                        egraphics_stroke(g);
                    }
                }
                              
                if(!x->f_source_manager->sourceGetMute(i))
                {
                    etext_layout_set(jtl, text, &x->j_box.b_font, sourcePositionX, sourcePositionY, font_size * 10., font_size * 2., ETEXT_CENTER, ETEXT_JCENTER, ETEXT_NOWRAP);
                    etext_layout_draw(jtl, g);
                    egraphics_set_color_rgba(g, &sourceColor); 
                    egraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., EPD_2PI);
                    egraphics_stroke(g);
                }
                else
                {
                    egraphics_set_color_rgba(g, &sourceColor);
                    etext_layout_set(jtl, text, &x->j_box.b_font, sourcePositionX, sourcePositionY, font_size * 10., font_size * 2., ETEXT_CENTER, ETEXT_JCENTER, ETEXT_NOWRAP);
                    etext_layout_draw(jtl, g);
                    t_rgba red = {1., 0., 0., 1.};
                    egraphics_set_color_rgba(g, &red); 
                    egraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., EPD_2PI);
                    egraphics_stroke(g);
                    egraphics_move_to(g, sourcePositionX + abscissa(x->f_size_source * 1., HOA_PI2 / 2.), sourcePositionY + ordinate(x->f_size_source * 1., HOA_PI2 / 2.));
                    egraphics_line_to(g, sourcePositionX + abscissa(x->f_size_source * 1., HOA_PI2 * 5. / 2.), sourcePositionY + ordinate(x->f_size_source * 1., HOA_PI * 5. / 4.));
                    egraphics_stroke(g);
                }
                
            }
        }
		etext_layout_destroy(jtl);

		ebox_end_layer((t_ebox *)x, hoa_sym_sources_layer);
    }
	ebox_paint_layer((t_ebox *)x, hoa_sym_sources_layer, 0., 0.);
}


void draw_groups(t_hoa_map *x,  t_object *view, t_rect *rect)
{
	int i;
	double fontSize;
	t_etext *jtl;
	t_rgba sourceColor;    
	char description[250] = {0};
	double descriptionPositionX;
    double descriptionPositionY;
	double sourcePositionX;
    double sourcePositionY;
    
    double w = rect->width;
    double h = rect->height;
    t_pt ctr = {w*0.5, h*0.5};
	
	t_elayer *g = ebox_start_layer((t_ebox *)x, hoa_sym_groups_layer, w, h);
    t_rgba color_sel = rgba_addContrast(x->f_color_bg, -0.14);
    x->f_size_source = ebox_getfontsize((t_ebox *)x) / 1.5;
    fontSize = ebox_getfontsize((t_ebox *)x);
    
    char text[] = "G";
	if (g)
    {
        jtl = etext_layout_create();
        egraphics_set_line_width(g, 2.);
        
		for(i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                sourcePositionX = (x->f_source_manager->groupGetAbscissa(i) * x->f_zoom_factor + 1.) * ctr.x;
                sourcePositionY = (-x->f_source_manager->groupGetOrdinate(i) * x->f_zoom_factor + 1.) * ctr.y;
                
                sourceColor.red = x->f_source_manager->groupGetColor(i)[0];
                sourceColor.green = x->f_source_manager->groupGetColor(i)[1];
                sourceColor.blue = x->f_source_manager->groupGetColor(i)[2];
                sourceColor.alpha = x->f_source_manager->groupGetColor(i)[3];
                
                if(x->f_source_manager->groupGetDescription(i).c_str()[0])
                    sprintf(description,"%i : %s", i+1, x->f_source_manager->groupGetDescription(i).c_str());
                else
                    sprintf(description,"%i", i+1);
    
                descriptionPositionX = sourcePositionX - 2. * x->f_size_source;
                descriptionPositionY = sourcePositionY - x->f_size_source - fontSize - 1.;
                
                etext_layout_settextcolor(jtl, &sourceColor);
                etext_layout_set(jtl, description, &x->j_box.b_font, descriptionPositionX, descriptionPositionY, fontSize * 10., fontSize * 2., ETEXT_LEFT, ETEXT_JLEFT, ETEXT_NOWRAP);
                etext_layout_draw(jtl, g);
                
                if (x->f_index_of_selected_group == i)
                {
                    egraphics_set_color_rgba(g, &color_sel);
                    egraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.5,  0., EPD_2PI);
                    egraphics_fill(g);
                    
                    for(int index = 0; index < x->f_source_manager->groupGetNumberOfSources(i); index++)
                    {
                        egraphics_move_to(g, sourcePositionX, sourcePositionY);
                        int groupIndex = x->f_source_manager->groupGetSourceIndex(i, index);
                        double groupPositionX = (x->f_source_manager->sourceGetAbscissa(groupIndex) * x->f_zoom_factor + 1.) * ctr.x;
                        double groupPositionY = (-x->f_source_manager->sourceGetOrdinate(groupIndex) * x->f_zoom_factor + 1.) * ctr.y;
                        egraphics_line_to(g, groupPositionX, groupPositionY);
                        egraphics_stroke(g);
                    }
                }
                egraphics_set_color_rgba(g, &sourceColor);

                if(!x->f_source_manager->groupGetMute(i))
                {
                    egraphics_set_color_rgba(g, &sourceColor);
                    egraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.,  0., EPD_2PI);
                    egraphics_stroke(g);
                    etext_layout_set(jtl, text, &x->j_box.b_font, sourcePositionX, sourcePositionY, fontSize * 10., fontSize * 2., ETEXT_CENTER, ETEXT_JLEFT, ETEXT_NOWRAP);
                    etext_layout_draw(jtl, g);
                
                }
                
                if(x->f_source_manager->groupGetMute(i))
                {
                    etext_layout_set(jtl, text, &x->j_box.b_font, sourcePositionX, sourcePositionY, fontSize * 10., fontSize * 2., ETEXT_CENTER, ETEXT_JLEFT, ETEXT_NOWRAP);
                    etext_layout_draw(jtl, g);
                    t_rgba red = {1., 0., 0., 1.};
                    egraphics_set_color_rgba(g, &red);
                    egraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., EPD_2PI);
                    egraphics_stroke(g);
                    for(int j = 0; j < 2; j++)
                    {
                        egraphics_move_to(g, sourcePositionX, sourcePositionY);
                        egraphics_line_to(g, sourcePositionX + abscissa(x->f_size_source * 1., HOA_2PI * j / 2. + HOA_PI2 / 2.), sourcePositionY + ordinate(x->f_size_source * 1., HOA_2PI * j / 2. + HOA_PI2 / 2.));
                        egraphics_stroke(g);
                    }
                    
                }
                 
            }
        }
		etext_layout_destroy(jtl);
        
		ebox_end_layer((t_ebox *)x, hoa_sym_groups_layer);
    }
	ebox_paint_layer((t_ebox *)x, hoa_sym_groups_layer, 0., 0.);
}


void draw_rect_selection(t_hoa_map *x,  t_object *view, t_rect *rect)
{
	t_elayer *g;
    g = ebox_start_layer((t_ebox *)x, gensym("rect_selection_layer"), rect->width, rect->height);
    t_rgba color_sel = rgba_addContrast(x->f_color_bg, -0.14);
	if (g)
    {
		if (x->f_rect_selection_exist)
        {            
			egraphics_set_line_width(g, 1);
			egraphics_set_color_rgba(g, &color_sel);
			egraphics_rectangle(g, x->f_rect_selection.x, x->f_rect_selection.y, x->f_rect_selection.width, x->f_rect_selection.height);
			egraphics_fill(g);
		}
		ebox_end_layer((t_ebox *)x, gensym("rect_selection_layer"));
	}
	ebox_paint_layer((t_ebox *)x, gensym("rect_selection_layer"), 0., 0.);
}

/**********************************************************/
/*                   Souris et clavier                    */
/**********************************************************/

void hoa_map_mousedown(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    double maxwh = x->rect.height;
    double ditanceSelected = (x->f_size_source / maxwh * 2.) / x->f_zoom_factor;

    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    x->f_rect_selection_exist = -1;
    x->f_rect_selection.width = x->f_rect_selection.height = 0.;
        
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && distance(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = distance(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && distance(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = distance(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
                x->f_index_of_selected_group = i;
            }
        }
    }

    if(modifiers == EMOD_CMD)
    {
        t_pt pos = eobj_get_mouse_global_position(x);
        x->f_index_of_source_to_remove = x->f_index_of_selected_source;
        x->f_index_of_group_to_remove = x->f_index_of_selected_group;
        
        
        if(x->f_index_of_selected_group != -1)
        {
            t_epopup* popup = epopupmenu_create((t_eobj *)x, hoa_sym_group);
            epopupmenu_setfont(popup, &x->j_box.b_font);
            x->f_index_of_group_to_color = x->f_index_of_selected_group;
            x->f_index_of_selected_group = -1;
            x->f_index_of_source_to_color = -1;
            epopupmenu_additem(popup, 0, "Group Menu", 0, 1);
            epopupmenu_addseperator(popup);
            epopupmenu_additem(popup, 1, "Remove group", 0, 0);
            epopupmenu_additem(popup, 2, "Remove group and sources", 0, 0);
            epopupmenu_additem(popup, 3, "Mute group", 0, x->f_source_manager->groupGetMute(x->f_index_of_group_to_remove));
            epopupmenu_additem(popup, 4, "Unmute group", 0, 0);
            epopupmenu_popup(popup, pos, 0);
        }
        else if(x->f_index_of_selected_source != -1)
        {
            t_epopup* popup = epopupmenu_create((t_eobj *)x, hoa_sym_source);
            epopupmenu_setfont(popup, &x->j_box.b_font);
            x->f_index_of_source_to_color = x->f_index_of_selected_source;
            x->f_index_of_selected_source = -1;
            x->f_index_of_group_to_color = -1;
            int muted = x->f_source_manager->sourceGetMute(x->f_index_of_source_to_remove);
            epopupmenu_additem(popup, 0, "Source Menu", 0, 1);
            epopupmenu_addseperator(popup);
            epopupmenu_additem(popup, 1, "Remove source", 0, 0);
            if(muted)
                epopupmenu_additem(popup, 2, "Unmute source", 0, 0);
            else
                epopupmenu_additem(popup, 2, "Mute source", 0, 0);
            epopupmenu_popup(popup, pos, 0);
        }
        else
        {
            t_epopup* popup = epopupmenu_create((t_eobj *)x, gensym("nothing"));
            epopupmenu_setfont(popup, &x->j_box.b_font);
            x->f_index_of_group_to_color = -1;
            x->f_index_of_source_to_color = -2;
            epopupmenu_additem(popup, 0, "Menu", 0, 1);
            epopupmenu_addseperator(popup);
            epopupmenu_additem(popup, 1, "Add source", 0, 0);
            epopupmenu_additem(popup, 2, "Clear all", 0, 0);
            epopupmenu_popup(popup, pos, 0);
        }
    }
    
    if(x->f_index_of_selected_source == -1 && x->f_index_of_selected_group == -1)
    {
        x->f_rect_selection.x = pt.x;
        x->f_rect_selection.y = pt.y;
        x->f_rect_selection_exist = 1;
    }
}

void hoa_map_popup(t_hoa_map *x, t_symbol *s, long itemid)
{
    if(s == hoa_sym_group)
    {
        switch (itemid)
        {
            case 1:
            {
                t_atom av[3];
                atom_setlong(av, x->f_index_of_group_to_remove);
                atom_setsym(av+1, hoa_sym_mute);
                atom_setlong(av+2, 1);
                outlet_list(x->f_out_groups, 0L, 3, av);
                x->f_source_manager->groupRemove(x->f_index_of_group_to_remove);
                hoa_map_bang(x);
                break;
            }
            case 2:
            {
                t_atom av[3];
                atom_setlong(av, x->f_index_of_group_to_remove);
                atom_setsym(av+1, hoa_sym_mute);
                atom_setlong(av+2, 1);
                outlet_list(x->f_out_groups, 0L, 3, av);
                x->f_source_manager->groupRemoveWithSources(x->f_index_of_group_to_remove);
                hoa_map_bang(x);
                break;
            }
            case 3: // Mute group
            {
                x->f_source_manager->groupSetMute(x->f_index_of_group_to_remove, 1);
                break;
            }
            case 4: // Unmute group
            {
                x->f_source_manager->groupSetMute(x->f_index_of_group_to_remove, 0);
                break;
            }
            default:
                break;
        }
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
        ebox_redraw((t_ebox *)x);
        hoa_map_bang(x);
    }
    else if(s ==hoa_sym_source)
    {
        switch (itemid)
        {
            case 1:
            {
                t_atom av[3];
                atom_setlong(av, x->f_index_of_source_to_remove);
                atom_setsym(av+1, hoa_sym_mute);
                atom_setlong(av+2, 1);
                outlet_list(x->f_out_sources, 0L, 3, av);
                x->f_source_manager->sourceRemove(x->f_index_of_source_to_remove);
                break;
            }
            case 2:
            {
                if(x->f_source_manager->sourceGetMute(x->f_index_of_source_to_remove))
                    x->f_source_manager->sourceSetMute(x->f_index_of_source_to_remove, 0);
                else
                    x->f_source_manager->sourceSetMute(x->f_index_of_source_to_remove, 1);
                break;
            }
            default:
                break;
        }
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
        ebox_redraw((t_ebox *)x);
        hoa_map_bang(x);
    }
    else if(s ==gensym("nothing"))
    {
        switch (itemid)
        {
            case 1:
            {
                x->f_source_manager->sourceNewCartesian(0., 0.);
                break;
            }
            case 2:
            {
                x->f_source_manager->clearAll();
                break;
            }
        }
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
        ebox_redraw((t_ebox *)x);
        hoa_map_bang(x);
    }
    
}


void hoa_map_mousedrag(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
	
	if (x->f_index_of_selected_source != -1)
    {
        if(modifiers == EMOD_SHIFT)
            x->f_source_manager->sourceSetAzimuth(x->f_index_of_selected_source, azimuth(cursor.x, cursor.y));
        else if(modifiers == EMOD_ALT)
            x->f_source_manager->sourceSetRadius(x->f_index_of_selected_source, radius(cursor.x, cursor.y));
        else
            x->f_source_manager->sourceSetCartesian(x->f_index_of_selected_source, cursor.x, cursor.y);
    }
    else if (x->f_index_of_selected_group != -1)
    {
        if(modifiers == EMOD_SHIFT)
            x->f_source_manager->groupSetRelativeAzimuth(x->f_index_of_selected_group, azimuth(cursor.x, cursor.y));
        else if(modifiers == EMOD_ALT || modifiers == 274)
            x->f_source_manager->groupSetRelativeRadius(x->f_index_of_selected_group, radius(cursor.x, cursor.y));
        else if((modifiers & EMOD_ALT) && (modifiers & EMOD_SHIFT))
            x->f_source_manager->groupSetRelativePolar(x->f_index_of_selected_group, radius(cursor.x, cursor.y), azimuth(cursor.x, cursor.y));
        else
            x->f_source_manager->groupSetCartesian(x->f_index_of_selected_group, cursor.x, cursor.y);            
    }
    else
    {
		x->f_rect_selection.width = pt.x - x->f_rect_selection.x;
		x->f_rect_selection.height = pt.y - x->f_rect_selection.y;
		ebox_invalidate_layer((t_ebox *)x, gensym("rect_selection_layer"));
		ebox_redraw((t_ebox *)x);
    }
    
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    ebox_notify((t_ebox *)x, NULL, hoa_sym_modified, NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    ebox_redraw((t_ebox *)x);
    hoa_map_bang(x);
}

void hoa_map_mouseup(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    if(x->f_rect_selection_exist)
    {
        int indexOfNewGroup = -1;
        for(int i = 0; indexOfNewGroup == -1; i++)
        {
            if (x->f_source_manager->groupGetExistence(i) == 0)
            {
                indexOfNewGroup = i;
            }
        }
    
        double x1 = ((x->f_rect_selection.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
        double x2 = (((x->f_rect_selection.x + x->f_rect_selection.width) / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
        double y1 = ((-x->f_rect_selection.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
        double y2 = (((-x->f_rect_selection.y - x->f_rect_selection.height) / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
        
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i) && indexOfNewGroup >= 0)
            {
                double abscissaOfSource = x->f_source_manager->sourceGetAbscissa(i);
                double ordinateOfSource = x->f_source_manager->sourceGetOrdinate(i);
                                
                if(((abscissaOfSource > x1 && abscissaOfSource < x2) || (abscissaOfSource < x1 && abscissaOfSource > x2)) && ((ordinateOfSource > y1 && ordinateOfSource < y2) || (ordinateOfSource < y1 && ordinateOfSource > y2)))
                {
                    x->f_source_manager->groupSetSource(indexOfNewGroup, i);
                    x->f_index_of_selected_group = indexOfNewGroup;
                }
            }
        }
    }
    
    x->f_rect_selection_exist = x->f_rect_selection.width = x->f_rect_selection.height = 0;
    
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    ebox_invalidate_layer((t_ebox *)x, gensym("rect_selection_layer"));
    ebox_redraw((t_ebox *)x);
}

void hoa_map_mousewheel(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
    if(modifiers == EMOD_ALT)
    {
		double newZoom = x->f_zoom_factor + y_inc / 100.;
        x->f_zoom_factor = clip_minmax(newZoom, MIN_ZOOM, MAX_ZOOM);
        
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_background_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
        ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
        ebox_redraw((t_ebox *)x);
	}
}

void hoa_map_mousemove(t_hoa_map *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    double maxwh = x->rect.width;
    double ditanceSelected = (x->f_size_source / maxwh * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && distance(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = distance(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && distance(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = distance(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
                x->f_index_of_selected_group = i;
                
            }
        }
    }
    if( x->f_index_of_selected_source != -1 ||  x->f_index_of_selected_group != -1)
        ebox_set_cursor((t_ebox *)x, 4);
    else
        ebox_set_cursor((t_ebox *)x, 1);

    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    ebox_redraw((t_ebox *)x);
}

long hoa_map_key(t_hoa_map *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
    int filter = 0;
	if (keycode == 97 && modifiers == 1 && textcharacter == 0)
    {
		int indexOfNewGroup = -1;
        for(int i = 0; indexOfNewGroup == -1; i++)
        {
            if (x->f_source_manager->groupGetExistence(i) == 0)
            {
                indexOfNewGroup = i;
            }
        }
        
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i) && indexOfNewGroup >= 0)
            {
                x->f_source_manager->groupSetSource(indexOfNewGroup, i);
                x->f_index_of_selected_group = indexOfNewGroup;
            }
        }
        filter = 1;
	}
	return filter;
}

t_symbol* format_string(const char *s)
{
    char desc[MAXPDSTRING];
    char str[MAXPDSTRING];
    char *pch;
    
    sprintf(str, "%s", s);
    pch = strtok(str, " ,.-");
    sprintf(desc, "%s", pch);
    pch = strtok(NULL, " ,.-");
    if(pch != NULL)
    {
        sprintf(desc, "%s", pch);
        strcat(desc, "_");
        pch = strtok(NULL, " ,.-");
    }
    while(pch != NULL)
    {
        strcat(desc, pch);
        strcat(desc, "_");
        pch = strtok(NULL, " ,.-");
    }
    
    return gensym(desc);
}

void hoa_map_preset(t_hoa_map *x, t_binbuf *d)
{
    binbuf_addv(d, "s", hoa_sym_sources_preset);
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            binbuf_addv(d, "sfff", hoa_sym_source, (float)i,
                        (float)x->f_source_manager->sourceGetAbscissa(i),
                        (float)x->f_source_manager->sourceGetOrdinate(i));
            
            binbuf_addv(d, "fffff", (float)x->f_source_manager->sourceGetMute(i),
                        (float)x->f_source_manager->sourceGetColor(i)[0],
                        (float)x->f_source_manager->sourceGetColor(i)[1],
                        (float)x->f_source_manager->sourceGetColor(i)[2],
                        (float)x->f_source_manager->sourceGetColor(i)[3]);
            
            if(x->f_source_manager->sourceGetDescription(i).size())
                binbuf_addv(d, "s", format_string(x->f_source_manager->sourceGetDescription(i).c_str()));
            else
                binbuf_addv(d, "s", gensym("(null)"));
        }
    }
    
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            binbuf_addv(d, "sf", hoa_sym_group, (float)i);
            binbuf_addv(d, "f", (float)x->f_source_manager->groupGetNumberOfSources(i));
            for(int j = 0; j < x->f_source_manager->groupGetNumberOfSources(i); j++)
            {
                binbuf_addv(d, "f", (float)x->f_source_manager->groupGetSourceIndex(i, j));
            }
            
            binbuf_addv(d, "ffff",
                        (float)x->f_source_manager->groupGetColor(i)[0],
                        (float)x->f_source_manager->groupGetColor(i)[1],
                        (float)x->f_source_manager->groupGetColor(i)[2],
                        (float)x->f_source_manager->groupGetColor(i)[3]);
            
            if(x->f_source_manager->groupGetDescription(i).size())
                binbuf_addv(d, "s", format_string(x->f_source_manager->groupGetDescription(i).c_str()));
            else
                binbuf_addv(d, "s", gensym("(null)"));
        }
    }
}

void hoa_map_sources_preset(t_hoa_map *x, t_symbol *s, short ac, t_atom *av)
{
    int index;
    int nsources;
    
    if(ac && av)
    {
        x->f_source_manager->clearAll();
        for(long i = 0; i < ac; i++)
        {
            if(ac > i+9)
            {
                if(atom_gettype(av+i) == A_SYM && atom_getsym(av+i) == hoa_sym_source
                   && atom_gettype(av+i+1) == A_FLOAT
                   && atom_gettype(av+i+2) == A_FLOAT
                   && atom_gettype(av+i+3) == A_FLOAT)
                {
                    index = atom_getlong(av+i+1);
                    x->f_source_manager->sourceSetCartesian(index, atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                    
                    if(atom_gettype(av+i+4) == A_FLOAT && atom_getfloat(av+i+4) == 0)
                        x->f_source_manager->sourceSetMute(index, 0);
                    else
                        x->f_source_manager->sourceSetMute(index, 1);
                    
                    if(atom_gettype(av+i+5) == A_FLOAT
                       && atom_gettype(av+i+6) == A_FLOAT
                       && atom_gettype(av+i+7) == A_FLOAT
                       && atom_gettype(av+i+8) == A_FLOAT)
                        x->f_source_manager->sourceSetColor(index, atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                    
                    if(atom_gettype(av+i+9) == A_SYM && atom_getsym(av+i+9) != gensym("(null)"))
                        x->f_source_manager->sourceSetDescription(index, format_string(atom_getsym(av+i+9)->s_name)->s_name);
                    else
                        x->f_source_manager->sourceSetDescription(index, "");
                    
                    i += 9;
                }
                
                if(atom_gettype(av+i) == A_SYM && atom_getsym(av+i) == hoa_sym_group
                   && atom_gettype(av+i+1) == A_FLOAT
                   && atom_gettype(av+i+2) == A_FLOAT)
                {
                    index = atom_getlong(av+i+1);
                    nsources = atom_getlong(av+i+2);
                    for(int j = 0; j < nsources; j++)
                    {
                        if(ac > i+3+j && atom_gettype(av+i+3+j) == A_FLOAT)
                            x->f_source_manager->groupSetSource(index, atom_getlong(av+i+3+j));
                    }
                    
                    if(ac > i+6+nsources && atom_gettype(av+i+3+nsources) == A_FLOAT
                       && atom_gettype(av+i+4+nsources) == A_FLOAT
                       && atom_gettype(av+i+5+nsources) == A_FLOAT
                       && atom_gettype(av+i+6+nsources) == A_FLOAT)
                        x->f_source_manager->groupSetColor(index, atom_getfloat(av+i+3+nsources), atom_getfloat(av+i+4+nsources), atom_getfloat(av+i+5+nsources), atom_getfloat(av+i+6+nsources));
                    
                    if(ac > i+7+nsources && atom_gettype(av+i+7+nsources) == A_SYM && atom_getsym(av+i+7+nsources) != gensym("(null)"))
                        x->f_source_manager->groupSetDescription(index, format_string(atom_getsym(av+i+7+nsources)->s_name)->s_name);
                    else
                        x->f_source_manager->groupSetDescription(index, "");
                    
                    i += (7+nsources);
                }
            }
        }
    }
    
    ebox_notify((t_ebox *)x, NULL, hoa_sym_modified, NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    ebox_redraw((t_ebox *)x);
    hoa_map_bang(x);
}

void hoa_map_interpolate(t_hoa_map *x, short ac, t_atom *av, short ac2, t_atom* av2, t_atom ratio)
{
    int index;
    float exist2;
    int nsources;
    float theta = atom_getfloat(&ratio);
 
    if(ac && av)
    {
        x->f_source_manager->clearAll();
        for(int i = 0; i < ac; i++)
        {
            if(ac > i+9)
            {
                if(atom_gettype(av+i) == A_SYM && atom_getsym(av+i) == hoa_sym_source
                   && atom_gettype(av+i+1) == A_FLOAT
                   && atom_gettype(av+i+2) == A_FLOAT
                   && atom_gettype(av+i+3) == A_FLOAT)
                {
                    index = atom_getlong(av+i+1);
                    exist2 = 0;
                    for(int j = 0; j < ac2; j++)
                    {
                        if(ac2 > j+9)
                        {
                            if(atom_gettype(av2+j) == A_SYM && atom_getsym(av2+j) == hoa_sym_source
                               && atom_gettype(av2+j+1) == A_FLOAT
                               && atom_gettype(av2+j+2) == A_FLOAT
                               && atom_gettype(av2+j+3) == A_FLOAT
                               && index == atom_getlong(av2+j+1))
                            {
                                exist2 = 1;
                                float abscissa = atom_getfloat(av+i+2) * (1.f - theta) + atom_getfloat(av2+j+2) * theta;
                                float ordinate = atom_getfloat(av+i+3) * (1.f - theta) + atom_getfloat(av2+j+3) * theta;
                                x->f_source_manager->sourceSetCartesian(index, abscissa, ordinate);
                                break;
                            }
                        }
                    }
                    if(!exist2)
                    {
                        x->f_source_manager->sourceSetCartesian(index, atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                    }
                    if(atom_gettype(av+i+4) == A_FLOAT && atom_getfloat(av+i+4) == 0)
                        x->f_source_manager->sourceSetMute(index, 0);
                    else
                        x->f_source_manager->sourceSetMute(index, 1);
                    
                    if(atom_gettype(av+i+5) == A_FLOAT
                       && atom_gettype(av+i+6) == A_FLOAT
                       && atom_gettype(av+i+7) == A_FLOAT
                       && atom_gettype(av+i+8) == A_FLOAT)
                        x->f_source_manager->sourceSetColor(index, atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                    
                    if(atom_gettype(av+i+9) == A_SYM && atom_getsym(av+i+9) != gensym("(null)"))
                        x->f_source_manager->sourceSetDescription(index, format_string(atom_getsym(av+i+9)->s_name)->s_name);
                    else
                        x->f_source_manager->sourceSetDescription(index, "");
                    
                    i += 9;
                }
                
                if(atom_gettype(av+i) == A_SYM && atom_getsym(av+i) == hoa_sym_group
                   && atom_gettype(av+i+1) == A_FLOAT
                   && atom_gettype(av+i+2) == A_FLOAT)
                {
                    index = atom_getlong(av+i+1);
                    nsources = atom_getlong(av+i+2);
                   
                    for(int j = 0; j < nsources; j++)
                    {
                        if(ac > i+3+j && atom_gettype(av+i+3+j) == A_FLOAT)
                            x->f_source_manager->groupSetSource(index, atom_getlong(av+i+3+j));
                    }
                    
                    if(ac > i+6+nsources && atom_gettype(av+i+3+nsources) == A_FLOAT
                       && atom_gettype(av+i+4+nsources) == A_FLOAT
                       && atom_gettype(av+i+5+nsources) == A_FLOAT
                       && atom_gettype(av+i+6+nsources) == A_FLOAT)
                        x->f_source_manager->groupSetColor(index, atom_getfloat(av+i+3+nsources), atom_getfloat(av+i+4+nsources), atom_getfloat(av+i+5+nsources), atom_getfloat(av+i+6+nsources));
                    
                    if(ac > i+7+nsources && atom_gettype(av+i+7+nsources) == A_SYM && atom_getsym(av+i+7+nsources) != gensym("(null)"))
                        x->f_source_manager->groupSetDescription(index, format_string(atom_getsym(av+i+7+nsources)->s_name)->s_name);
                    else
                        x->f_source_manager->groupSetDescription(index, "");
                    
                    i += (7+nsources);
                }
            }
        }
    }
    
    ebox_notify((t_ebox *)x, NULL, hoa_sym_modified, NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_sources_layer);
    ebox_invalidate_layer((t_ebox *)x, hoa_sym_groups_layer);
    ebox_redraw((t_ebox *)x);
    hoa_map_bang(x);

}

