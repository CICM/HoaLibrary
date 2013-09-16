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

#ifndef DEF_HOA_RECOMPOSER_TILDE_PD
#define DEF_HOA_RECOMPOSER_TILDE_PD

#include "../../../PdEnhanced/Sources/pd_enhanced.h"
#include "../../Sources/HoaLibrary.h"

typedef struct _hoa_recomposer
{
    t_jbox              f_ob;
    AmbisonicRecomposer *f_ambi_recomposer;
    long                f_mode;
} t_hoa_recomposer;

void *hoa_recomposer_new(t_symbol *s, long argc, t_atom *argv);
void hoa_recomposer_free(t_hoa_recomposer *x);

void hoa_recomposer_angle(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av);
void hoa_recomposer_wide(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av);

t_eclass *hoa_recomposer_class;

void hoa_recomposer_dsp(t_hoa_recomposer *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_recomposer_perform(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_recomposer_perform_fisheye(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_recomposer_perform_free(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_max_err recomposer_setattr_mode(t_hoa_recomposer *x, t_object *attr, long ac, t_atom *av);

#endif