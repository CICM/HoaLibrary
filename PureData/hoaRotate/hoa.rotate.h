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

#ifndef DEF_HOA_ROTATE_TILDE_PD
#define DEF_HOA_ROTATE_TILDE_PD

#include "../../../PdEnhanced/Sources/pd_enhanced.h"
#include "../../Sources/HoaLibrary.h"

typedef struct _hoa_rotate
{
    t_jbox           f_ob;
    AmbisonicRotate	*f_ambi_rotate;
} t_hoa_rotate;

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv);
void hoa_rotate_free(t_hoa_rotate *x);

void hoa_rotate_dsp(t_hoa_rotate *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_rotate_perform(t_hoa_rotate *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_rotate_class;

#endif