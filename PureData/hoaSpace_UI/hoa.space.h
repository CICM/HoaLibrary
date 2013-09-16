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

#ifndef DEF_HOA_SPACE_PD
#define DEF_HOA_SPACE_PD

#include "../../../PdEnhanced/Sources/pd_enhanced.h"
#include "../../Sources/HoaLibrary.h"


#define NUMBER_OF_CIRCLES 5
#define MAX_CHANNELS 250

typedef struct _hoa_space
{
    t_jbox                  j_box;
    AmbisonicsViewer*       f_viewer;
    AmbisonicRecomposer*    f_recomposer;
    
    void*       f_out;
    
    t_jrgba		f_color_background;
	t_jrgba		f_color_border_box;
    t_jrgba		f_color_inner_circle;
    t_jrgba		f_color_points;
    t_jrgba     f_color_harmonics;
    
    t_rect		f_center;
    t_pt        f_mousepos;
    long		f_mode;
    
    long        f_number_of_microphones;
    
    double		f_radius_global;
	double		f_radius_circle;
    double      f_radius_ext_circle;
    
	double      f_harmonicsValues[MAX_CHANNELS];
    double      f_mode_values[MAX_CHANNELS];
    double      f_microphonesValues[MAX_CHANNELS];
    t_atom      f_tempory_values[MAX_CHANNELS];
    
    double      f_reference_angle;
    double      f_rotation_max;
    double      f_retractation;
    
} t_hoa_space;

t_eclass *hoa_space_class;

extern "C" void setup_hoa0x2espace(void);
void *hoa_space_new(t_symbol *s, int argc, t_atom *argv);
void hoa_space_free(t_hoa_space *x);
void hoa_space_assist(t_hoa_space *x, void *b, long m, long a, char *s);
void hoa_space_bang(t_hoa_space *x);;
void hoa_space_getdrawparams(t_hoa_space *x, t_object *patcherview, t_jboxdrawparams *params);

t_max_err hoa_space_channels_set(t_hoa_space *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoa_space_notify(t_hoa_space *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err hoa_space_coefficients_set(t_hoa_space *x, t_object *attr, long ac, t_atom *av);

void hoa_space_paint(t_hoa_space *x, t_object *view);
void hoa_space_draw_background(t_hoa_space *x, t_object *view, t_rect *rect);
void hoa_space_draw_microphones(t_hoa_space *x, t_object *view, t_rect *rect);
void hoa_space_draw_harmonics(t_hoa_space *x, t_object *view, t_rect *rect);

void hoa_space_mouse_move(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_down(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_drag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_mouse_enddrag(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);

void hoa_space_draw_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_rotate_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);
void hoa_space_retract_points(t_hoa_space *x, t_object *patcherview, t_pt pt, long modifiers);

static void hoa_space_properties(t_gobj *z, t_glist *owner);

void hoa_space_compute(t_hoa_space *x);
void hoa_space_output(t_hoa_space *x);

#endif