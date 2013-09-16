/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef DEF_HOA_MAP_PD
#define DEF_HOA_MAP_PD

#include "../../../PdEnhanced/Sources/pd_enhanced.h"
#include "../../Sources/HoaLibrary.h"

#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

#define CORNERSIZE 8
#define BORDERTHICK 2

typedef struct  _hoamap
{
	t_jbox          j_box;
	t_rect          rect;
	t_jfont*        jfont;
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
    
    t_jrgba		f_colorBackground;
    t_jrgba		f_colorBackgroundInside;
    t_jrgba     f_colorBorder;
    t_jrgba     f_colorSelection;
    
    int         f_cartConstrain;
    
    double      f_size_source;
	double		f_zoom_factor;
    
    t_rect		f_rect_selection;
	int			f_rect_selection_exist;
    
    long    f_output_mode;
    
} t_hoamap;

t_eclass *hoamap_class;

extern "C" void setup_hoa0x2map(void);
void *hoamap_new(t_symbol *s, int argc, t_atom *argv);
void hoamap_free(t_hoamap *x);
void hoamap_tick(t_hoamap *x);
void hoamap_getdrawparams(t_hoamap *x, t_object *patcherview, t_jboxdrawparams *params);
void hoamap_assist(t_hoamap *x, void *b, long m, long a, char *s);
t_max_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err hoamap_zoom(t_hoamap *x, t_object *attr, long argc, t_atom *argv);
void hoamap_popup(t_hoamap *x, t_symbol *s, long itemid, t_pt pt);

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


#endif