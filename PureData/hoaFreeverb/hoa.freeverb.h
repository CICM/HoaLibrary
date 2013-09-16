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

#ifndef DEF_HOA_FREEVERB_TILDE_PD
#define DEF_HOA_FREEVERB_TILDE_PD

#include "../../../PdEnhanced/Sources/pd_enhanced.h"
#include "../../Sources/HoaLibrary.h"

typedef struct _hoa_freeverb
{
    t_jbox            f_ob;
    AmbisonicFreeverb*  f_ambi_freeverb;
    
} t_hoa_freeverb;

void *hoa_freeverb_new(t_symbol *s, long argc, t_atom *argv);
void hoa_freeverb_free(t_hoa_freeverb *x);

void hoa_freeverb_size(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_damp(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_dry(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_wet(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_spread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_fspread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_lspread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_freeze(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);

void hoa_freeverb_dsp(t_hoa_freeverb *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_freeverb_perform(t_hoa_freeverb *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_freeverb_class;

#endif