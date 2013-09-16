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

#ifndef DEF_HOA_GRAIN_TILDE_PD
#define DEF_HOA_GRAIN_TILDE_PD

#include "../../../PdEnhanced/Sources/pd_enhanced.h"
#include "../../Sources/HoaLibrary.h"

typedef struct _hoa_grain
{
    t_jbox              f_ob;
    AmbisonicsGrain*    f_ambi_grain;
    
    int                 f_number_of_samples;
    t_float*            f_buffer;
    t_symbol*           f_buffer_name;
    
} t_hoa_grain;

void *hoa_grain_new(t_symbol *s, long argc, t_atom *argv);
void hoa_grain_free(t_hoa_grain *x);

void hoa_grain_size(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_delay(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_feed(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_rare(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_diff(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_comp(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_buffer_set(t_hoa_grain *x, t_symbol *s);

void hoa_grain_dsp(t_hoa_grain *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_grain_perform_post(t_hoa_grain *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_grain_perform_no(t_hoa_grain *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_grain_class;

#endif