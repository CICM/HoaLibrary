/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

extern "C"
{
#include "../../../PdEnhanced/Sources/cicm_wrapper.h"
}

#include "../../Sources/HoaLibrary.h"

#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

#define CORNERSIZE 8
#define BORDERTHICK 2

typedef struct  _hoamap
{
	t_ebox          j_box;
	t_rect          rect;
    t_clock*        f_clock;
    
	t_outlet*		f_out_sources;
    t_outlet*		f_out_groups;
    t_outlet*		f_out_infos;
    
    SourcesManager*     f_source_manager;
    SourcesPreset*      f_source_preset;
    SourcesTrajectory*  f_source_trajectory;
    
    t_pt        f_cursor_position;
    long        f_index_of_selected_source;
    long        f_index_of_selected_group;
    long        f_index_of_source_to_remove;
    long        f_index_of_group_to_remove;
    long        f_index_of_source_to_color;
    long        f_index_of_group_to_color;
    
    t_rgba		f_color_background;
    t_rgba     f_color_border_box;
    
    double      f_size_source;
	double		f_zoom_factor;
    
    t_rect		f_rect_selection;
	int			f_rect_selection_exist;
    
    long        f_output_mode;
    
} t_hoamap;

t_eclass *hoamap_class;

void *hoamap_new(t_symbol *s, int argc, t_atom *argv);
void hoamap_free(t_hoamap *x);
void hoamap_tick(t_hoamap *x);
void hoamap_getdrawparams(t_hoamap *x, t_object *patcherview, t_edrawparams *params);
void hoamap_oksize(t_hoamap *x, t_rect *newrect);
void hoamap_assist(t_hoamap *x, void *b, long m, long a, char *s);
t_pd_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_pd_err hoamap_zoom(t_hoamap *x, t_object *attr, long argc, t_atom *argv);
void hoamap_popup(t_hoamap *x, t_symbol *s, long itemid);

void hoamap_parameters_sources(t_hoamap *x, short ac, t_atom *av);
void hoamap_parameters_groups(t_hoamap *x, short ac, t_atom *av);
void hoamap_parameters_slots(t_hoamap *x, short ac, t_atom *av);
void hoamap_parameters_trajectory(t_hoamap *x, short ac, t_atom *av);
void hoamap_source_save(t_hoamap *x, t_binbuf *d);
void hoamap_group_save(t_hoamap *x, t_binbuf *d);
void hoamap_slot_save(t_hoamap *x, t_binbuf *d);
void hoamap_trajectory_save(t_hoamap *x, t_binbuf *d);
void hoamap_jsave(t_hoamap *x, t_binbuf *d);

void hoamap_doread(t_hoamap *x, t_symbol *s, long argc, t_atom *argv);
void hoamap_dowrite(t_hoamap *x, t_symbol *s, long argc, t_atom *argv);
void hoamap_tick(t_hoamap *x);

void hoamap_source(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_group(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_slot(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_trajectory(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_bang(t_hoamap *x);
void hoamap_infos(t_hoamap *x);
void hoamap_clear_all(t_hoamap *x);

/* Paint Methods */
void hoamap_paint(t_hoamap *x, t_object *view);
void draw_background(t_hoamap *x, t_object *view, t_rect *rect);
void draw_sources(t_hoamap *x,  t_object *view, t_rect *rect);
void draw_groups(t_hoamap *x,  t_object *view, t_rect *rect);
void draw_rect_selection(t_hoamap *x,  t_object *view, t_rect *rect);

void hoamap_mousedown(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousedrag(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseup(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousewheel(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc);
long hoamap_key(t_hoamap *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);

extern "C" void setup_hoa0x2emap(void)
{
	t_eclass *c;
    
	c = eclass_new("hoa.map", (method)hoamap_new, (method)hoamap_free, sizeof(t_hoamap), 0L, A_GIMME, 0);
    
    eclass_init(c, 0);
    
    eclass_addmethod(c, (method) hoamap_assist,          "assist",           A_CANT,     0);
	eclass_addmethod(c, (method) hoamap_paint,           "paint",            A_CANT,     0);
	eclass_addmethod(c, (method) hoamap_getdrawparams,   "getdrawparams",    A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_oksize,          "oksize",           A_CANT,     0);
	eclass_addmethod(c, (method) hoamap_notify,          "notify",           A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_bang,            "bang",             A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_infos,           "getinfo",          A_CANT,     0);
    
    eclass_addmethod(c, (method) hoamap_source,           "source",           A_GIMME,    0);
    eclass_addmethod(c, (method) hoamap_group,            "group",            A_GIMME,    0);
    eclass_addmethod(c, (method) hoamap_slot,             "slot",             A_GIMME,    0);
    eclass_addmethod(c, (method) hoamap_trajectory,       "trajectory",       A_GIMME,    0);
    eclass_addmethod(c, (method) hoamap_clear_all,        "clear",            A_CANT ,    0);
    
    eclass_addmethod(c, (method) hoamap_mousedown,        "mousedown",       A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_mousedrag,        "mousedrag",       A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_mouseup,          "mouseup",         A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_mouseenter,       "mouseenter",      A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_mousemove,        "mousemove",       A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_mouseleave,       "mouseleave",      A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_mousewheel,		 "mousewheel",      A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_key,              "key",             A_CANT,     0);
	eclass_addmethod(c, (method) hoamap_popup,            "popup",           A_CANT,     0);
    eclass_addmethod(c, (method) hoamap_jsave,            "jsave",           A_CANT,     0);
    
	CLASS_ATTR_DEFAULT              (c, "size", 0, "225 225");
    
    CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_hoamap, f_color_background);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.7 0.7 0.7 1.");
	
    CLASS_ATTR_RGBA					(c, "bdcolor", 0, t_hoamap, f_color_border_box);
	CLASS_ATTR_CATEGORY				(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bdcolor", 0, "Border Box Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bdcolor", 0, "0.5 0.5 0.5 1.");
	
	CLASS_ATTR_LONG                 (c,"outputmode", 0, t_hoamap, f_output_mode);
	CLASS_ATTR_LABEL                (c,"outputmode", 0, "Output Mode");
	CLASS_ATTR_CATEGORY             (c,"outputmode", 0, "Behavior");
	CLASS_ATTR_DEFAULT              (c,"outputmode", 0,  "0");
    CLASS_ATTR_SAVE                 (c,"outputmode", 1);
    CLASS_ATTR_ORDER                (c,"outputmode", 0, "1");
    
	CLASS_ATTR_DOUBLE               (c,"zoom", 0, t_hoamap, f_zoom_factor);
    CLASS_ATTR_ACCESSORS            (c,"zoom", NULL, hoamap_zoom);
	CLASS_ATTR_LABEL                (c,"zoom", 0,   "Zoom");
	CLASS_ATTR_CATEGORY             (c,"zoom", 0,   "Behavior");
	CLASS_ATTR_DEFAULT              (c,"zoom", 0,   "0.35");
    CLASS_ATTR_ORDER                (c,"zoom", 0,   "2");
    CLASS_ATTR_SAVE                 (c,"zoom", 0);
    CLASS_ATTR_PAINT                (c,"zoom", 0);
    
    eclass_register(CLASS_BOX, c);
    hoa_post();
	hoamap_class = c;
}

void *hoamap_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoamap *x =  NULL;
	t_binbuf *d;
	long flags;
	
	if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;
    
    x = (t_hoamap *)eobj_new(hoamap_class);
    if (x)
    {
        flags = 0
        | EBOX_GROWLINK
        ;
        
        ebox_new((t_ebox *)x, flags);
        x->f_source_manager     = new SourcesManager(1. / (double)MIN_ZOOM - 5.);
        x->f_source_preset      = new SourcesPreset();
        x->f_source_trajectory  = new SourcesTrajectory();
        
        x->f_rect_selection_exist = 0;
        x->f_index_of_selected_source = -1;
        x->f_index_of_selected_group = -1;
        
        x->f_out_sources    = listout(x);
        x->f_out_groups     = listout(x);
        x->f_out_infos      = listout(x);
       
        x->f_clock = clock_new(x,(t_method)hoamap_tick);
    
         ebox_attrprocess_viabinbuf(x, d);
         t_atom *av = NULL;
         long ac = 0;
         
         binbuf_get_attribute(d, gensym("trajectory_parameters"), &ac, &av);
         hoamap_parameters_trajectory(x, ac, av);
         if (av && ac)
         {
             ac = 0;
             free(av);
             av = NULL;
         }
         binbuf_get_attribute(d, gensym("slots_parameters"), &ac, &av);
         hoamap_parameters_slots(x, ac, av);
         if (av && ac)
         {
             ac = 0;
             free(av);
             av = NULL;
         }
         
         binbuf_get_attribute(d, gensym("sources_parameters"), &ac, &av);
         hoamap_parameters_sources(x, ac, av);
         if (av && ac)
         {
             ac = 0;
             free(av);
             av = NULL;
         }
         binbuf_get_attribute(d, gensym("groups_parameters"), &ac, &av);
         hoamap_parameters_groups(x, ac, av);
         if (av && ac)
         {
             ac = 0;
             free(av);
             av = NULL;
         }
        ebox_ready((t_ebox *)x);
    }
    
	return (x);
}

void hoamap_free(t_hoamap *x)
{
    ebox_free((t_ebox *)x);
    clock_free(x->f_clock);
    delete x->f_source_manager;
    delete x->f_source_preset;
    delete x->f_source_trajectory;
}

void hoamap_assist(t_hoamap *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(Anything) Behavior and appearance");
	else
    {
        if(a == 0)
            sprintf(s,"(List) Sources coordinates");
        if(a == 1)
            sprintf(s,"(List) Groups coordinates");
        if(a == 2)
            sprintf(s,"(List) Infos");
    }
}

void hoamap_doread(t_hoamap *x, t_symbol *s, long argc, t_atom *argv)
{
    int mode = 0;
    t_binbuf *d = binbuf_new();

    if (s == gensym(""))
    {
        object_error(x, "hoa.map read failed, read method needs a filename and a path.");
        return;
    }
    
    if(binbuf_read(d, s->s_name, "", 0))
    {
        object_error(x, "%s: read failed", atom_getsym(argv)->s_name);
    }
    else
    {
        t_atom *av = NULL;
        long ac = 0;
        
        binbuf_get_attribute(d, gensym("slots_parameters"), &ac, &av);
        hoamap_parameters_slots(x, ac, av);
        if (av && ac)
        {
            mode++;
            ac = 0;
            free(av);
            av = NULL;
        }
        
        binbuf_get_attribute(d, gensym("trajectory_parameters"), &ac, &av);
        hoamap_parameters_trajectory(x, ac, av);
        if (av && ac)
        {
            mode += 2;
            ac = 0;
            free(av);
            av = NULL;
        }
        
        if(!mode)
            post("hoa.map : nothing to read from %s.", s->s_name);
        else if (mode == 1)
            post("hoa.map : read slots from %s.", s->s_name);
        else if (mode == 2)
            post("hoa.map : read trajectories from %s.", s->s_name);
        else
            post("hoa.map : read slots and trajectories from %s.", s->s_name);
        
        if (d)
        {
            binbuf_free(d);
        }
    }
}

void hoamap_dowrite(t_hoamap *x, t_symbol *s, long argc, t_atom *argv)
{
    int mode = 0;
    t_binbuf *d = binbuf_new();
    if(atom_getsym(argv+1) == gensym("slot"))
    {
        hoamap_slot_save(x, d);
    }
    else if(atom_getsym(argv+1) == gensym("trajectory"))
    {
        mode = 1;
        hoamap_trajectory_save(x, d);
    }
    else
    {
        mode = 2;
        hoamap_slot_save(x, d);
        hoamap_trajectory_save(x, d);
    }
    
    if (atom_gettype(argv) != A_SYM || atom_getsym(argv)==gensym(""))
    {
        object_error(x, "hoa.map write failed, write method needs a filename and a path.");
        return;
    }
    if(binbuf_write(d, atom_getsym(argv)->s_name, "", 0))
    {
        object_error(x, "%s: write failed", atom_getsym(argv)->s_name);
    }
    else
    {
        if(!mode)
            post("hoa.map : write success slots in %s.", atom_getsym(argv)->s_name);
        else if (mode == 1)
            post("hoa.map : write success trajectories in %s.", atom_getsym(argv)->s_name);
        else
            post("hoa.map : write success slots and trajectories in %s.", atom_getsym(argv)->s_name);
    }
    if (d)
    {
        binbuf_free(d);
    }
}

void hoamap_getdrawparams(t_hoamap *x, t_object *patcherview, t_edrawparams *params)
{
    params->d_boxfillcolor = x->f_color_background;
    params->d_bordercolor = x->f_color_border_box;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

void hoamap_oksize(t_hoamap *x, t_rect *newrect)
{
    newrect->width = pd_clip_min(newrect->width, 30.);
    newrect->height = pd_clip_min(newrect->height, 30.);
}

void hoamap_tick(t_hoamap *x)
{
    if(x->f_index_of_selected_source != -1)
        x->f_source_trajectory->recordSourceInTrajectory(x->f_source_manager, x->f_index_of_selected_source);
    else if(x->f_index_of_selected_group != -1)
        x->f_source_trajectory->recordGroupInTrajectory(x->f_source_manager, x->f_index_of_selected_group);
    clock_delay(x->f_clock, 100);
}

/**********************************************************/
/*          Intialisation par l'utilisateur               */
/**********************************************************/

void hoamap_clear_all(t_hoamap *x)
{
    x->f_source_manager->clearAll();
  
    ebox_notify((t_ebox *)x, NULL, gensym("modified"), NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    ebox_redraw((t_ebox *)x);
    hoamap_bang(x);
}

void hoamap_source(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && atom_gettype(av)==A_LONG && atom_getlong(av)>=0 && atom_gettype(av+1) == A_SYM)
    {
        if(atom_getsym(av+1) == gensym("polar") || atom_getsym(av+1) == gensym("pol"))
            x->f_source_manager->sourceSetPolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("radius"))
            x->f_source_manager->sourceSetRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("angle"))
            x->f_source_manager->sourceSetAngle(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("cartesian") || atom_getsym(av+1) == gensym("car"))
            x->f_source_manager->sourceSetCartesian(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("abscissa"))
            x->f_source_manager->sourceSetAbscissa(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("ordinate"))
            x->f_source_manager->sourceSetOrdinate(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("remove"))
        {
            x->f_source_manager->sourceRemove(atom_getlong(av));
            t_atom av[3];
            atom_setlong(av, atom_getlong(av));
            atom_setsym(av+1, gensym("mute"));
            atom_setlong(av+2, 1);
            outlet_list(x->f_out_sources, 0L, 3, av);
        }
        else if(atom_getsym(av+1) == gensym("mute"))
            x->f_source_manager->sourceSetMute(atom_getlong(av), atom_getlong(av+2));
        else if(atom_getsym(av+1) == gensym("description"))
        {
            char description[250];
            char number[250];
            if(atom_gettype(av+1) == A_SYM)
            {
                strcpy(description, atom_getsym(av+2)->s_name);
                strcat(description, " ");
                if(atom_getsym(av+2) == gensym("remove"))
                {
                    x->f_source_manager->sourceSetDescription(atom_getlong(av), "");
                    ebox_notify((t_ebox *)x, NULL, gensym("modified"), NULL, NULL);
                    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
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
            x->f_source_manager->sourceSetDescription(atom_getlong(av), description);
        }
        else if(atom_getsym(av+1) == gensym("color"))
        {
            x->f_source_manager->sourceSetColor(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3), atom_getfloat(av+4), atom_getfloat(av+5));
        }
        
    }
    ebox_notify((t_ebox *)x, NULL, gensym("modified"), NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    ebox_redraw((t_ebox *)x);
    hoamap_bang(x);
}

void hoamap_group(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && atom_gettype(av) == A_LONG && atom_getlong(av) >= 0 && atom_gettype(av+1) == A_SYM)
    {
        if(atom_getsym(av+1) == gensym("set"))
        {
            x->f_source_manager->groupRemove(atom_getlong(av));
            for(int i = 2; i < ac; i++)
            {
                x->f_source_manager->groupSetSource(atom_getlong(av), atom_getlong(av+i));
            }
        }        
        else if(atom_getsym(av+1) == gensym("polar") || atom_getsym(av+1) == gensym("pol"))
            x->f_source_manager->groupSetPolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3) + CICM_PI2);
        else if(atom_getsym(av+1) == gensym("radius"))
            x->f_source_manager->groupSetRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("angle"))
            x->f_source_manager->groupSetAngle(atom_getlong(av), atom_getfloat(av+2) + CICM_PI2);
        else if(atom_getsym(av+1) == gensym("cartesian") || atom_getsym(av+1) == gensym("car"))
            x->f_source_manager->groupSetCartesian(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("abscissa"))
            x->f_source_manager->groupSetAbscissa(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("ordinate"))
            x->f_source_manager->groupSetOrdinate(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("relpolar") || atom_getsym(av+1) == gensym("relativepolar"))
            x->f_source_manager->groupSetRelativePolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("relradius") || atom_getsym(av+1) == gensym("relativeradius"))
            x->f_source_manager->groupSetRelativeRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("relangle") || atom_getsym(av+1) == gensym("relativeangle"))
            x->f_source_manager->groupSetRelativeAngle(atom_getlong(av), atom_getfloat(av+2) + CICM_PI2);
        else if(atom_getsym(av+1) == gensym("mute"))
            x->f_source_manager->groupSetMute(atom_getlong(av), atom_getlong(av+2));
        else if(atom_getsym(av+1) == gensym("remove"))
        {
            x->f_source_manager->groupRemove(atom_getlong(av));
            t_atom av[3];
            atom_setlong(av, atom_getlong(av));
            atom_setsym(av+1, gensym("mute"));
            atom_setlong(av+2, 1);
            outlet_list(x->f_out_groups, 0L, 3, av);
        }
        else if(atom_getsym(av+1) == gensym("description"))
        {
            char description[250];
            char number[250];
            if(atom_gettype(av+1) == A_SYM)
            {
                strcpy(description, atom_getsym(av+2)->s_name);
                strcat(description, " ");
                if(atom_getsym(av+2) == gensym("remove"))
                {
                    x->f_source_manager->groupSetDescription(atom_getlong(av), "");
                    ebox_notify((t_ebox *)x, NULL, gensym("modified"), NULL, NULL);
                    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
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
            x->f_source_manager->groupSetDescription(atom_getlong(av), description);
        }
        else if(atom_getsym(av+1) == gensym("color"))
        {
            x->f_source_manager->groupSetColor(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3), atom_getfloat(av+4), atom_getfloat(av+5));
        }
    }
    
    ebox_notify((t_ebox *)x, NULL, gensym("modified"), NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    ebox_redraw((t_ebox *)x);
    hoamap_bang(x);    
}

void hoamap_slot(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av)
    {
        if(atom_gettype(av) == A_SYM)
        {
            t_symbol *sym = atom_getsym(av);
			
            if(sym == gensym("store"))
                x->f_source_preset->storeSouceManagerAtSlot(x->f_source_manager, atom_getlong(av+1));
            else if(sym == gensym("storeagain"))
                x->f_source_preset->storeSouceManagerAtLastUsedSlot(x->f_source_manager);
            else if(sym == gensym("storeempty"))
                x->f_source_preset->storeSouceManagerAtFirstEmptySlot(x->f_source_manager);
            else if(sym == gensym("storeend"))
                x->f_source_preset->storeSouceManagerAtNewEndSlot(x->f_source_manager);
            else if(sym == gensym("storenext"))
                x->f_source_preset->storeSouceManagerAtNextSlot(x->f_source_manager);
            else if(sym == gensym("insert"))
                x->f_source_preset->insertSlot(x->f_source_manager, atom_getlong(av+1));
            else if(sym == gensym("remove"))
                x->f_source_preset->removeSlot(atom_getlong(av+1));
            else if(sym == gensym("delete"))
                x->f_source_preset->deleteSlot(atom_getlong(av+1));
            else if(sym == gensym("copy"))
                x->f_source_preset->copySlot(atom_getlong(av+1), atom_getlong(av+2));
            else if(sym == gensym("renumber"))
                x->f_source_preset->renumber();
            else if(sym == gensym("clear"))
                x->f_source_preset->clear();
            else if(sym == gensym("recall"))
			{
                x->f_source_preset->recallFractionalSlot(x->f_source_manager, atom_getlong(av+1), atom_getlong(av+2), (double)atom_getfloat(av+3));
			}
			else if(sym == gensym("read"))
            {
                t_symbol *sym = ( ac >= 1 && atom_gettype(av+1) == A_SYM) ? atom_getsym(av+1) : gensym("");
                hoamap_doread(x, sym, 0, NULL);
            }
            else if(sym == gensym("write"))
            {
                t_atom parameter[2];
                atom_setsym(parameter, ( ac >= 1 && atom_gettype(av+1) == A_SYM) ? atom_getsym(av+1) : gensym(""));
                atom_setsym(parameter+1, gensym("slot"));
                hoamap_dowrite(x, NULL, 2, parameter);
            }
            else if(sym == gensym("storesource"))
                x->f_source_preset->storeSourceAtSlot(x->f_source_manager, atom_getlong(av+1),atom_getlong(av+2));
            else if(sym == gensym("storegroup"))
                x->f_source_preset->storeGroupAtSlot(x->f_source_manager, atom_getlong(av+1), atom_getlong(av+2));
        }
        else if(atom_gettype(av) == A_FLOAT)
		{
            x->f_source_preset->recallFractionalSlot(x->f_source_manager, (double)atom_getfloat(av));
		}
    }
    
    ebox_notify((t_ebox*)x, NULL, gensym("modified"), NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    ebox_redraw((t_ebox *)x);
    hoamap_bang(x);
}

void hoamap_trajectory(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av)
    {
        if(atom_gettype(av) == A_SYM)
        {
            t_symbol *sym = atom_getsym(av);
            if(sym == gensym("record"))
                x->f_source_trajectory->setRecording(atom_getlong(av+1));
            else if(sym == gensym("limit"))
                x->f_source_trajectory->setLimited(atom_getlong(av+1));
            else if(sym == gensym("erase"))
                x->f_source_trajectory->erase();
            else if(sym == gensym("erasepart"))
                x->f_source_trajectory->erase(atom_getfloat(av+1), atom_getfloat(av+2));
            else if(sym == gensym("read"))
            {
                t_symbol *sym = ( ac >= 1 && atom_gettype(av+1) == A_SYM) ? atom_getsym(av+1) : gensym("");
                hoamap_doread(x, sym, 0, NULL);
            }
            else if(sym == gensym("write"))
            {
                t_atom parameter[2];
                atom_setsym(parameter, ( ac >= 1 && atom_gettype(av+1) == A_SYM) ? atom_getsym(av+1) : gensym(""));
                atom_setsym(parameter+1, gensym("trajectory"));
                hoamap_dowrite(x, NULL, 2, parameter);
            }
        }
        else if(atom_gettype(av) == A_FLOAT)
            x->f_source_trajectory->playTrajectory(x->f_source_manager, (double)atom_getfloat(av));
    }
    
    
    ebox_notify((t_ebox*)x, NULL, gensym("modified"), NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    ebox_redraw((t_ebox *)x);
    hoamap_bang(x);
}

/**********************************************************/
/*                  Preset et Pattr                       */
/**********************************************************/

void hoamap_jsave(t_hoamap *x, t_binbuf *d)
{
    hoamap_source_save(x, d);
    hoamap_group_save(x, d);
    hoamap_slot_save(x, d);
    hoamap_trajectory_save(x, d);
}

void hoamap_source_save(t_hoamap *x, t_binbuf *d)
{
    t_atom *av;
    long ac = x->f_source_manager->getNumberOfSources()*10;
    av = new t_atom[ac];
    if(av && ac)
    {
        for(long i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setsym(av+j, gensym("source"));
                atom_setlong(av+j+1, i);
                atom_setfloat(av+j+2, x->f_source_manager->sourceGetAbscissa(i));
                atom_setfloat(av+j+3, x->f_source_manager->sourceGetOrdinate(i));
                atom_setlong(av+j+4, x->f_source_manager->groupGetMute(i));
                atom_setfloat(av+j+5, x->f_source_manager->sourceGetColor(i).red);
                atom_setfloat(av+j+6, x->f_source_manager->sourceGetColor(i).green);
                atom_setfloat(av+j+7, x->f_source_manager->sourceGetColor(i).blue);
                atom_setfloat(av+j+8, x->f_source_manager->sourceGetColor(i).alpha);
                if(x->f_source_manager->sourceGetDescription(i).c_str())
                    atom_setsym(av+j+9, gensym(x->f_source_manager->sourceGetDescription(i).c_str()));
                else
                    atom_setsym(av+j+9, gensym("(null)"));
                
                j += 10;
            }
        }
        binbuf_append_attribute(d, gensym("sources_parameters"), ac, av);
        free(av);
    }
}

void hoamap_group_save(t_hoamap *x, t_binbuf *d)
{
    t_atom *av;
    long ac = 0;
    for(long i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            ac += x->f_source_manager->groupGetNumberOfSources(i) + 9;
        }
    }
    av = new t_atom[ac];
    if(av && ac)
    {
        for(long i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                long numberOfsource = x->f_source_manager->groupGetNumberOfSources(i);
                atom_setsym(av+j, gensym("group"));
                atom_setlong(av+j+1, i);
                atom_setlong(av+j+2, numberOfsource);
                for (long k = 0; k < numberOfsource; k++)
                {
                    atom_setlong(av+j+k+3, x->f_source_manager->groupGetSourceIndex(i, k));
                }
                atom_setlong(av+j+numberOfsource+3, x->f_source_manager->groupGetMute(i));
                atom_setfloat(av+j+numberOfsource+4, x->f_source_manager->groupGetColor(i).red);
                atom_setfloat(av+j+numberOfsource+5, x->f_source_manager->groupGetColor(i).green);
                atom_setfloat(av+j+numberOfsource+6, x->f_source_manager->groupGetColor(i).blue);
                atom_setfloat(av+j+numberOfsource+7, x->f_source_manager->groupGetColor(i).alpha);
                if(x->f_source_manager->groupGetDescription(i).c_str())
                    atom_setsym(av+j+numberOfsource+8, gensym(x->f_source_manager->groupGetDescription(i).c_str()));
                else
                    atom_setsym(av+j+numberOfsource+8, gensym("(null)"));
                
                
                j += x->f_source_manager->groupGetNumberOfSources(i) + 9;
            }
        }
        binbuf_append_attribute(d, gensym("groups_parameters"), ac, av);
        free(av);
    }
}

void hoamap_slot_save(t_hoamap *x, t_binbuf *d)
{
    t_atom *av;
    long ac = 0;
    
    SourcesManager* temporySourceManager = NULL;
    temporySourceManager = new SourcesManager();
    if(temporySourceManager)
    {
        ac = 0;
        for(long i = 0; i <= x->f_source_preset->getMaximumIndexOfSlot(); i++)
        {
            if(x->f_source_preset->getSlotExistence(i))
            {
                ac += 2;
                x->f_source_preset->recallSlot(temporySourceManager, i);
                ac += temporySourceManager->getNumberOfSources()*10;
                for(long j = 0; j <= temporySourceManager->getMaximumIndexOfGroup(); j++)
                {
                    if(temporySourceManager->groupGetExistence(j))
                    {
                        ac += temporySourceManager->groupGetNumberOfSources(j) + 9;
                    }
                }
            }
        }
        av = new t_atom[ac];
        if(av && ac)
        {
            for(long j = 0, i = 0; j <= x->f_source_preset->getMaximumIndexOfSlot(); j++)
            {
                if(x->f_source_preset->getSlotExistence(j))
                {
                    atom_setsym(av+i, gensym("slot"));
                    atom_setlong(av+i+1, j);
                    x->f_source_preset->recallSlot(temporySourceManager, j);
                    i += 2;
                    for(long k = 0; k <= temporySourceManager->getMaximumIndexOfSource(); k++)
                    {
                        if(temporySourceManager->sourceGetExistence(k))
                        {
                            atom_setsym(av+i, gensym("source"));
                            atom_setlong(av+i+1, k);
                            atom_setfloat(av+i+2, temporySourceManager->sourceGetAbscissa(k));
                            atom_setfloat(av+i+3, temporySourceManager->sourceGetOrdinate(k));
                            atom_setlong(av+i+4, temporySourceManager->groupGetMute(k));
                            atom_setfloat(av+i+5, temporySourceManager->sourceGetColor(k).red);
                            atom_setfloat(av+i+6, temporySourceManager->sourceGetColor(k).green);
                            atom_setfloat(av+i+7, temporySourceManager->sourceGetColor(k).blue);
                            atom_setfloat(av+i+8, temporySourceManager->sourceGetColor(k).alpha);
                            if(x->f_source_manager->sourceGetDescription(i).c_str())
                                atom_setsym(av+i+9, gensym(x->f_source_manager->sourceGetDescription(i).c_str()));
                            else
                                atom_setsym(av+i+9, gensym("(null)"));
                            
                            i += 10;
                        }
                    }
                    for(long k = 0; k <= temporySourceManager->getMaximumIndexOfGroup(); k++)
                    {
                        if(temporySourceManager->groupGetExistence(k))
                        {
                            long numberOfsource = temporySourceManager->groupGetNumberOfSources(k);
                            atom_setsym(av+i, gensym("group"));
                            atom_setlong(av+i+1, k);
                            atom_setlong(av+i+2, numberOfsource);
                            for (long l = 0; l < numberOfsource; l++)
                            {
                                atom_setlong(av+i+l+3, temporySourceManager->groupGetSourceIndex(k, l));
                            }
                            atom_setlong(av+i+numberOfsource+3, temporySourceManager->groupGetMute(k));
                            atom_setfloat(av+i+numberOfsource+4, temporySourceManager->groupGetColor(k).red);
                            atom_setfloat(av+i+numberOfsource+5, temporySourceManager->groupGetColor(k).green);
                            atom_setfloat(av+i+numberOfsource+6, temporySourceManager->groupGetColor(k).blue);
                            atom_setfloat(av+i+numberOfsource+7, temporySourceManager->groupGetColor(k).alpha);
                            if(x->f_source_manager->groupGetDescription(i).c_str())
                                atom_setsym(av+i+numberOfsource+8, gensym(x->f_source_manager->groupGetDescription(i).c_str()));
                            else
                                atom_setsym(av+i+numberOfsource+8, gensym("(null)"));
                            
                            i += numberOfsource + 9;
                        }
                    }
                }
            }
            
            binbuf_append_attribute(d, gensym("slots_parameters"), ac, av);
            free(av);
        }
        delete temporySourceManager;
    }
}

void hoamap_trajectory_save(t_hoamap *x, t_binbuf *d)
{
    t_atom *av;
    long ac = 0;

    SourcesManager* temporySourceManager = NULL;
    temporySourceManager = new SourcesManager();
    if(temporySourceManager)
    {
        ac = 0;
        for(long i = 0; i <= x->f_source_trajectory->getMaximumIndexOfSlot(); i++)
        {
            if(x->f_source_trajectory->getSlotExistence(i))
            {
                ac += 2;
                x->f_source_trajectory->recallSlot(temporySourceManager, i);
                ac += temporySourceManager->getNumberOfSources()*10;
                for(long j = 0; j <= temporySourceManager->getMaximumIndexOfGroup(); j++)
                {
                    if(temporySourceManager->groupGetExistence(j))
                    {
                        ac += temporySourceManager->groupGetNumberOfSources(j) + 9;
                    }
                }
            }
        }
        av = new t_atom[ac];
        if(av && ac)
        {
            for(long j = 0, i = 0; j <= x->f_source_trajectory->getMaximumIndexOfSlot(); j++)
            {
                if(x->f_source_trajectory->getSlotExistence(j))
                {
                    atom_setsym(av+i, gensym("slot"));
                    atom_setlong(av+i+1, j);
                    x->f_source_trajectory->recallSlot(temporySourceManager, j);
                    i += 2;
                    for(long k = 0; k <= temporySourceManager->getMaximumIndexOfSource(); k++)
                    {
                        if(temporySourceManager->sourceGetExistence(k))
                        {
                            atom_setsym(av+i, gensym("source"));
                            atom_setlong(av+i+1, k);
                            atom_setfloat(av+i+2, temporySourceManager->sourceGetAbscissa(k));
                            atom_setfloat(av+i+3, temporySourceManager->sourceGetOrdinate(k));
                            atom_setlong(av+i+4, temporySourceManager->groupGetMute(k));
                            atom_setfloat(av+i+5, temporySourceManager->sourceGetColor(k).red);
                            atom_setfloat(av+i+6, temporySourceManager->sourceGetColor(k).green);
                            atom_setfloat(av+i+7, temporySourceManager->sourceGetColor(k).blue);
                            atom_setfloat(av+i+8, temporySourceManager->sourceGetColor(k).alpha);
                            if(x->f_source_manager->sourceGetDescription(i).c_str())
                                atom_setsym(av+i+9, gensym(x->f_source_manager->sourceGetDescription(i).c_str()));
                            else
                                atom_setsym(av+i+9, gensym("(null)"));
                            
                            i += 10;
                        }
                    }
                    for(long k = 0; k <= temporySourceManager->getMaximumIndexOfGroup(); k++)
                    {
                        if(temporySourceManager->groupGetExistence(k))
                        {
                            long numberOfsource = temporySourceManager->groupGetNumberOfSources(k);
                            atom_setsym(av+i, gensym("group"));
                            atom_setlong(av+i+1, k);
                            atom_setlong(av+i+2, numberOfsource);
                            for (long l = 0; l < numberOfsource; l++)
                            {
                                atom_setlong(av+i+l+3, temporySourceManager->groupGetSourceIndex(k, l));
                            }
                            atom_setlong(av+i+numberOfsource+3, temporySourceManager->groupGetMute(k));
                            atom_setfloat(av+i+numberOfsource+4, temporySourceManager->groupGetColor(k).red);
                            atom_setfloat(av+i+numberOfsource+5, temporySourceManager->groupGetColor(k).green);
                            atom_setfloat(av+i+numberOfsource+6, temporySourceManager->groupGetColor(k).blue);
                            atom_setfloat(av+i+numberOfsource+7, temporySourceManager->groupGetColor(k).alpha);
                            if(x->f_source_manager->groupGetDescription(i).c_str())
                                atom_setsym(av+i+numberOfsource+8, gensym(x->f_source_manager->groupGetDescription(i).c_str()));
                            else
                                atom_setsym(av+i+numberOfsource+8, gensym("(null)"));
                            
                            i += numberOfsource + 9;
                        }
                    }
                }
            }
            
            binbuf_append_attribute(d, gensym("trajectory_parameters"), ac, av);
            free(av);
        }
        delete temporySourceManager;
    }
}

void hoamap_parameters_sources(t_hoamap *x, short ac, t_atom *av)
{
    if(ac && av)
    {
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == gensym("source")) 
            {
                x->f_source_manager->sourceSetCartesian(atom_getlong(av+i+1), atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                x->f_source_manager->sourceSetMute(atom_getlong(av+i+1), atom_getlong(av+i+4));
                x->f_source_manager->sourceSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                if(atom_getsym(av+i+9) != gensym("(null)") && atom_getsym(av+i+9) != gensym("s_nosymbol") && atom_getsym(av+i+9) != gensym(" "))
                {
                    x->f_source_manager->sourceSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+9)->s_name);
                }
                i += 8;
            }
        }
    }
}

void hoamap_parameters_groups(t_hoamap *x, short ac, t_atom *av)
{
    if(ac && av)
    {
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == gensym("group"))
            {
                long numberOfsource = atom_getlong(av+i+2);
                for (int j = 0; j < numberOfsource; j++)
                {
                    x->f_source_manager->groupSetSource(atom_getlong(av+i+1), atom_getlong(av+i+3+j));
                }
                if(atom_getlong(av+i+3+numberOfsource) == 1)
                    x->f_source_manager->groupSetMute(atom_getlong(av+i+1), 1);
                x->f_source_manager->groupSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+4+numberOfsource), atom_getfloat(av+i+5+numberOfsource), atom_getfloat(av+i+6+numberOfsource), atom_getfloat(av+i+7+numberOfsource));
                if(atom_getsym(av+i+7+numberOfsource) != gensym("(null)") && atom_getsym(av+i+8+numberOfsource) != gensym("s_nosymbol") && atom_getsym(av+i+7+numberOfsource) != gensym(" "))
                {
                    x->f_source_manager->groupSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+7+numberOfsource)->s_name);
                }
                
                i += numberOfsource + 7;
            }
        }
    }
}

void hoamap_parameters_slots(t_hoamap *x, short ac, t_atom *av)
{
    SourcesManager* temporySourceManager = NULL;
    temporySourceManager = new SourcesManager();
    if(ac && av && temporySourceManager)
    {
        long slotIndex = -1;
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == gensym("slot"))
            {
                x->f_source_preset->storeSouceManagerAtSlot(temporySourceManager, slotIndex);
                temporySourceManager->setExistence(0);
                temporySourceManager->setExistence(1);
                slotIndex = atom_getlong(av+i+1);
            }
            else if(atom_getsym(av+i) == gensym("source"))
            {
                temporySourceManager->sourceSetCartesian(atom_getlong(av+i+1), atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                temporySourceManager->sourceSetMute(atom_getlong(av+i+1), atom_getlong(av+i+4));
                temporySourceManager->sourceSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                temporySourceManager->sourceSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+9)->s_name);
            }
            if(atom_getsym(av+i) == gensym("group"))
            {
                long numberOfsource = atom_getlong(av+i+2);
                for (int j = 0; j < numberOfsource; j++)
                {
                    temporySourceManager->groupSetSource(atom_getlong(av+i+1), atom_getlong(av+i+3+j));
                }
                if(atom_getlong(av+i+3+numberOfsource) == 1)
                    temporySourceManager->groupSetMute(atom_getlong(av+i+1), 1);
                temporySourceManager->groupSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+4+numberOfsource), atom_getfloat(av+i+5+numberOfsource), atom_getfloat(av+i+6+numberOfsource), atom_getfloat(av+i+7+numberOfsource));
                temporySourceManager->groupSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+8+numberOfsource)->s_name);
            }
        }
        x->f_source_preset->storeSouceManagerAtSlot(temporySourceManager, slotIndex);
        delete temporySourceManager;
    }
}

void hoamap_parameters_trajectory(t_hoamap *x, short ac, t_atom *av)
{
    SourcesManager* temporySourceManager = NULL;
    temporySourceManager = new SourcesManager();
    if(ac && av && temporySourceManager)
    {
        long slotIndex = -1;
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == gensym("slot"))
            {
                x->f_source_trajectory->storeSouceManagerAtSlot(temporySourceManager, slotIndex);
                temporySourceManager->setExistence(0);
                temporySourceManager->setExistence(1);
                slotIndex = atom_getlong(av+i+1);
            }
            else if(atom_getsym(av+i) == gensym("source"))
            {
                temporySourceManager->sourceSetCartesian(atom_getlong(av+i+1), atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                temporySourceManager->sourceSetMute(atom_getlong(av+i+1), atom_getlong(av+i+4));
                temporySourceManager->sourceSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                temporySourceManager->sourceSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+9)->s_name);
            }
            if(atom_getsym(av+i) == gensym("group"))
            {
                long numberOfsource = atom_getlong(av+i+2);
                for (int j = 0; j < numberOfsource; j++)
                {
                    temporySourceManager->groupSetSource(atom_getlong(av+i+1), atom_getlong(av+i+3+j));
                }
                if(atom_getlong(av+i+3+numberOfsource) == 1)
                    temporySourceManager->groupSetMute(atom_getlong(av+i+1), 1);
                temporySourceManager->groupSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+4+numberOfsource), atom_getfloat(av+i+5+numberOfsource), atom_getfloat(av+i+6+numberOfsource), atom_getfloat(av+i+7+numberOfsource));
                temporySourceManager->groupSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+8+numberOfsource)->s_name);
            }
        }
        x->f_source_trajectory->storeSouceManagerAtSlot(temporySourceManager, slotIndex);
        delete temporySourceManager;
    }
}

t_pd_err hoamap_zoom(t_hoamap *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_zoom_factor = atom_getfloat(argv);
        x->f_zoom_factor = Tools::clip(x->f_zoom_factor, MIN_ZOOM, MAX_ZOOM);
    }
    
    ebox_invalidate_layer((t_ebox *)x, gensym("background_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    return 0;
}

t_pd_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if (msg == gensym("attr_modified"))
    {
        if(s == gensym("bgcolor") || s == gensym("bgcolor2") )
        {
            ebox_invalidate_layer((t_ebox *)x, gensym("background_layer"));
        }
        else if(s == gensym("fontname") || s == gensym("fontface") || s == gensym("fontsize"))
        {
            ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
            ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
        }
        else if(s == gensym("zoom"))
        {
            ebox_invalidate_layer((t_ebox *)x, gensym("background_layer"));
            ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
            ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
        }
        ebox_redraw((t_ebox *)x);
    }
    
    
	return ebox_notify((t_ebox *)x, s, msg, sender, data);
}

/**********************************************************/
/*                          Sortie                        */
/**********************************************************/

void hoamap_bang(t_hoamap *x)
{
    t_atom av[4];
    atom_setsym(av+1, gensym("mute"));
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(av, i);
            atom_setlong(av+2, x->f_source_manager->sourceGetMute(i));
            outlet_list(x->f_out_sources, 0L, 3, av);
        }
    }
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(av, i);
            atom_setfloat(av+2, x->f_source_manager->groupGetMute(i));
            outlet_list(x->f_out_groups, 0L, 4, av);
        }
    }
    if(x->f_output_mode == 0)
    {
        atom_setsym(av+1, gensym("polar"));
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2, x->f_source_manager->sourceGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->sourceGetAngle(i));
                outlet_list(x->f_out_sources, 0L, 4, av);
            }
        }
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2, x->f_source_manager->groupGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->groupGetAngle(i));
                outlet_list(x->f_out_groups, 0L, 4, av);
            }
        }
        
    }
    else
    {
        atom_setsym(av+1, gensym("cartesian"));
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2,x->f_source_manager->sourceGetAbscissa(i));
                atom_setfloat(av+3,x->f_source_manager->sourceGetOrdinate(i));
                outlet_list(x->f_out_sources, 0L, 4, av);
            }
        }
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2, x->f_source_manager->groupGetAbscissa(i));
                atom_setfloat(av+3, x->f_source_manager->groupGetOrdinate(i));
                outlet_list(x->f_out_groups, 0L, 4, av);
            }
        }
    }
}

void hoamap_infos(t_hoamap *x)
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
    atom_setsym(avNumber, gensym("source"));
    atom_setsym(avNumber+1, gensym("number"));
    atom_setlong(avNumber+2, numberOfSource);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);
    
    avIndex = new t_atom[numberOfSource+2];
    atom_setsym(avIndex, gensym("source"));
    atom_setsym(avIndex+1, gensym("index"));
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
    
    atom_setsym(avMute, gensym("source"));
    atom_setsym(avMute+1, gensym("mute"));
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(avMute+2, i);
            atom_setlong(avMute+3, x->f_source_manager->sourceGetMute(i));
            outlet_list(x->f_out_infos, 0L, 4, avMute);
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
    atom_setsym(avNumber, gensym("group"));
    atom_setsym(avNumber+1, gensym("number"));
    atom_setlong(avNumber+2, numberOfGroups);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);
    
    avIndex = new t_atom[numberOfGroups+2];
    atom_setsym(avIndex, gensym("group"));
    atom_setsym(avIndex+1, gensym("index"));
    for(int i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(avIndex+j+2, i);
            j++;
            avSource = new t_atom[x->f_source_manager->groupGetNumberOfSources(i)+3];
            atom_setsym(avSource, gensym("group"));
            atom_setsym(avSource+1, gensym("source"));
            atom_setlong(avSource+2, i);
            for(int k = 0; k < x->f_source_manager->groupGetNumberOfSources(i); k++)
            {
                atom_setlong(avSource+3+k,x->f_source_manager->groupGetSourceIndex(i, k));
            }
            outlet_list(x->f_out_infos, 0L, x->f_source_manager->groupGetNumberOfSources(i)+3, avSource);
            free(avSource);
        }
    }
    outlet_list(x->f_out_infos, 0L, numberOfGroups+2, avIndex);
    free(avIndex);
    
    atom_setsym(avMute, gensym("group"));
    atom_setsym(avMute+1, gensym("mute"));
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(avMute+2, i);
            atom_setlong(avMute+3, x->f_source_manager->groupGetMute(i));
            outlet_list(x->f_out_infos, 0L, 4, avMute);
        }
    }

    /* Slots */
    long numberOfSlots = 0;
    for(int i = 0; i <= x->f_source_preset->getMaximumIndexOfSlot(); i++)
    {
        if(x->f_source_preset->getSlotExistence(i))
        {
            numberOfSlots++;
        }
    }
    atom_setsym(avNumber, gensym("slot"));
    atom_setsym(avNumber+1, gensym("number"));
    atom_setlong(avNumber+2, numberOfSlots);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);

    avIndex = new t_atom[numberOfSlots+2];
    atom_setsym(avIndex, gensym("slot"));
    atom_setsym(avIndex+1, gensym("index"));
    for(int i = 0, j = 0; i <= x->f_source_preset->getMaximumIndexOfSlot(); i++)
    {
        if(x->f_source_preset->getSlotExistence(i))
        {
            atom_setlong(avIndex+j+2, i);
            j++;
        }
    }
    outlet_list(x->f_out_infos, 0L, numberOfSlots+2, avIndex);
    free(avIndex);    
}

/**********************************************************/
/*                          Paint                         */
/**********************************************************/

void hoamap_paint(t_hoamap *x, t_object *view)
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

void draw_background(t_hoamap *x,  t_object *view, t_rect *rect)
{
    t_elayer *g = ebox_start_layer((t_ebox *)x, gensym("background_layer"), rect->width, rect->height);

    t_rgba black = rgba_addContrast(x->f_color_background, -0.14);
	if (g)
    {
        egraphics_set_color_rgba(g, &x->f_color_background);
        egraphics_arc(g, rect->width / 2., rect->width / 2., (rect->width / 2.) * (1. / MIN_ZOOM * x->f_zoom_factor) - 1.,  0., EPD_2PI);
        egraphics_fill(g);
        
        /* Circles */
        double radius  = x->f_zoom_factor * rect->width / 10.;
        for(int i = 5; i > 0; i--)
        {
            
            egraphics_set_line_width(g, 2);
            egraphics_set_color_rgba(g, &x->f_color_background);
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
            egraphics_set_color_rgba(g, &x->f_color_background);
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
        
		ebox_end_layer((t_ebox *)x, gensym("background_layer"));
	}
	ebox_paint_layer((t_ebox *)x, gensym("background_layer"), 0., 0.);
}

void draw_sources(t_hoamap *x,  t_object *view, t_rect *rect)
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
	
	t_elayer *g = ebox_start_layer((t_ebox *)x, gensym("sources_layer"), rect->width, rect->height);
	t_rgba color_sel = rgba_addContrast(x->f_color_background, -0.14);
    
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
			
                sourceColor.red = x->f_source_manager->sourceGetColor(i).red;
                sourceColor.green = x->f_source_manager->sourceGetColor(i).green;
                sourceColor.blue = x->f_source_manager->sourceGetColor(i).blue;
                sourceColor.alpha = x->f_source_manager->sourceGetColor(i).alpha;

                if(x->f_source_manager->sourceGetDescription(i).c_str()[0])
                    sprintf(description,"%i : %s", i, x->f_source_manager->sourceGetDescription(i).c_str());
                else
                    sprintf(description,"%i", i);
                    
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
                    egraphics_move_to(g, sourcePositionX + Tools::abscissa(x->f_size_source * 1., CICM_PI2 / 2.), sourcePositionY + Tools::ordinate(x->f_size_source * 1., CICM_PI2 / 2.));
                    egraphics_line_to(g, sourcePositionX + Tools::abscissa(x->f_size_source * 1., CICM_PI2 * 5. / 2.), sourcePositionY + Tools::ordinate(x->f_size_source * 1., CICM_PI * 5. / 4.));
                    egraphics_stroke(g);
                }
                
            }
        }
		etext_layout_destroy(jtl);

		ebox_end_layer((t_ebox *)x, gensym("sources_layer"));
    }
	ebox_paint_layer((t_ebox *)x, gensym("sources_layer"), 0., 0.);
}


void draw_groups(t_hoamap *x,  t_object *view, t_rect *rect)
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
	
	t_elayer *g = ebox_start_layer((t_ebox *)x, gensym("groups_layer"), w, h);
    t_rgba color_sel = rgba_addContrast(x->f_color_background, -0.14);
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
                
                sourceColor.red = x->f_source_manager->groupGetColor(i).red;
                sourceColor.green = x->f_source_manager->groupGetColor(i).green;
                sourceColor.blue = x->f_source_manager->groupGetColor(i).blue;
                sourceColor.alpha = x->f_source_manager->groupGetColor(i).alpha;
                
                if(x->f_source_manager->groupGetDescription(i).c_str()[0])
                    sprintf(description,"%i : %s", i, x->f_source_manager->groupGetDescription(i).c_str());
                else
                    sprintf(description,"%i", i);
    
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
                        egraphics_line_to(g, sourcePositionX + Tools::abscissa(x->f_size_source * 1., CICM_2PI * j / 2. + CICM_PI2 / 2.), sourcePositionY + Tools::ordinate(x->f_size_source * 1., CICM_2PI * j / 2. + CICM_PI2 / 2.));
                        egraphics_stroke(g);
                    }
                    
                }
                 
            }
        }
		etext_layout_destroy(jtl);
        
		ebox_end_layer((t_ebox *)x, gensym("groups_layer"));
    }
	ebox_paint_layer((t_ebox *)x, gensym("groups_layer"), 0., 0.);
}


void draw_rect_selection(t_hoamap *x,  t_object *view, t_rect *rect)
{
	t_elayer *g;
    g = ebox_start_layer((t_ebox *)x, gensym("rect_selection_layer"), rect->width, rect->height);
    t_rgba color_sel = rgba_addContrast(x->f_color_background, -0.14);
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

void hoamap_mousedown(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    double maxwh = Tools::cicm_max(x->rect.width, x->rect.height);
    double ditanceSelected = (x->f_size_source / maxwh * 2.) / x->f_zoom_factor;

    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    x->f_rect_selection_exist = -1;
    x->f_rect_selection.width = x->f_rect_selection.height = 0.;
        
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
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
            t_epopup* popup = epopupmenu_create((t_eobj *)x, gensym("group"));
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
            t_epopup* popup = epopupmenu_create((t_eobj *)x, gensym("source"));
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
    
    if(x->f_source_trajectory->getRecording())
        clock_set(x->f_clock, 20);
}

void hoamap_popup(t_hoamap *x, t_symbol *s, long itemid)
{
    if(s == gensym("group"))
    {
        switch (itemid)
        {
            case 1:
            {
                t_atom av[3];
                atom_setlong(av, x->f_index_of_group_to_remove);
                atom_setsym(av+1, gensym("mute"));
                atom_setlong(av+2, 1);
                outlet_list(x->f_out_groups, 0L, 3, av);
                x->f_source_manager->groupRemove(x->f_index_of_group_to_remove);
                hoamap_bang(x);
                break;
            }
            case 2:
            {
                t_atom av[3];
                atom_setlong(av, x->f_index_of_group_to_remove);
                atom_setsym(av+1, gensym("mute"));
                atom_setlong(av+2, 1);
                outlet_list(x->f_out_groups, 0L, 3, av);
                x->f_source_manager->groupRemoveWithSources(x->f_index_of_group_to_remove);
                hoamap_bang(x);
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
        ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
        ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
        ebox_redraw((t_ebox *)x);
        hoamap_bang(x);
    }
    else if(s ==gensym("source"))
    {
        switch (itemid)
        {
            case 1:
            {
                t_atom av[3];
                atom_setlong(av, x->f_index_of_source_to_remove);
                atom_setsym(av+1, gensym("mute"));
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
        ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
        ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
        ebox_redraw((t_ebox *)x);
        hoamap_bang(x);
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
        ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
        ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
        ebox_redraw((t_ebox *)x);
        hoamap_bang(x);
    }
    
}


void hoamap_mousedrag(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
	
	if (x->f_index_of_selected_source != -1)
    {
        if(modifiers == EMOD_SHIFT)
            x->f_source_manager->sourceSetAngle(x->f_index_of_selected_source, Tools::angle(cursor.x, cursor.y) - CICM_PI2);
        else if(modifiers == EMOD_ALT)
            x->f_source_manager->sourceSetRadius(x->f_index_of_selected_source, Tools::radius(cursor.x, cursor.y));
        else
            x->f_source_manager->sourceSetCartesian(x->f_index_of_selected_source, cursor.x, cursor.y);
    }
    else if (x->f_index_of_selected_group != -1)
    {
        if(modifiers == EMOD_SHIFT)
            x->f_source_manager->groupSetRelativeAngle(x->f_index_of_selected_group, Tools::angle(cursor.x, cursor.y));
        else if(modifiers == EMOD_ALT || modifiers == 274)
            x->f_source_manager->groupSetRelativeRadius(x->f_index_of_selected_group, Tools::radius(cursor.x, cursor.y));
        else if((modifiers & EMOD_ALT) && (modifiers & EMOD_SHIFT))
            x->f_source_manager->groupSetRelativePolar(x->f_index_of_selected_group, Tools::radius(cursor.x, cursor.y), Tools::angle(cursor.x, cursor.y));
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
    
    ebox_notify((t_ebox *)x, NULL, gensym("modified"), NULL, NULL);
    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    ebox_redraw((t_ebox *)x);
    hoamap_bang(x);
}

void hoamap_mouseup(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if(x->f_source_trajectory)
        clock_unset(x->f_clock);
     
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
    
    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("rect_selection_layer"));
    ebox_redraw((t_ebox *)x);
}

void hoamap_mousewheel(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
    if(modifiers == EMOD_ALT)
    {
		double newZoom = x->f_zoom_factor + y_inc / 100.;
        x->f_zoom_factor = Tools::clip(newZoom, MIN_ZOOM, MAX_ZOOM);
        
        ebox_invalidate_layer((t_ebox *)x, gensym("background_layer"));
        ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
        ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
        ebox_redraw((t_ebox *)x);
	}
}

void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    double maxwh = Tools::cicm_max(x->rect.width, x->rect.height);
    double ditanceSelected = (x->f_size_source / maxwh * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
                x->f_index_of_selected_group = i;
                
            }
        }
    }
    if( x->f_index_of_selected_source != -1 ||  x->f_index_of_selected_group != -1)
        ebox_set_cursor((t_ebox *)x, 4);
    else
        ebox_set_cursor((t_ebox *)x, 1);

    ebox_invalidate_layer((t_ebox *)x, gensym("sources_layer"));
    ebox_invalidate_layer((t_ebox *)x, gensym("groups_layer"));
    ebox_redraw((t_ebox *)x);
}

void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

long hoamap_key(t_hoamap *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
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

