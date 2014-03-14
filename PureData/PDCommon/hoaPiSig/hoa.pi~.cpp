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


#include "../hoaLibrary/hoa.library_pd.h"

#define CICM_PI  (3.141592653589793238462643383279502884)

typedef struct _pi 
{	
	t_jbox p_ob;
	double p_value;	
} t_pi;

void pi_float(t_pi *x, float n);
void *pi_new(t_symbol *s, int argc, t_atom *argv);
void pi_dsp(t_pi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void pi_perform(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_eclass *pi_class;

extern "C" void hoa0x2epi_setup(void)
{
    t_eclass* c;
    c = class_new("hoa.pi~", (method)pi_new,(method)NULL, sizeof(t_pi), 0L, A_GIMME, 0);
    class_addmethod(c, (method)pi_float,     "float",      A_FLOAT, 0);

    pi_class = c;
}

void *pi_new(t_symbol *s, int argc, t_atom *argv)
{
    t_pi *x = (t_pi *)object_alloc(pi_class);
	x->p_value = 1.;
    x->p_value = atom_getfloat(argv);

    dsp_setupjbox((t_jbox *)x, 2, 1);
    
    x->p_ob.z_misc = Z_NO_INPLACE;
	
	return(x);
}


void pi_dsp(t_pi *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp, gensym("dsp_add"), x, (method)pi_perform, 0, NULL);
}

void pi_perform(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	//x->f_ambi_encoder->process(ins[0], outs, ins[1]);
}

void pi_float(t_pi *x, double n)
{
	x->p_value = n;
}

