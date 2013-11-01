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

void pi_bang(t_pi *x);
void pi_float(t_pi *x, float n);
void *pi_new(t_symbol *s, int argc, t_atom *argv);

t_eclass *pi_class;

extern "C" void setup_hoa0x2epi(void)
{
    t_eclass* c;
    c = class_new("hoa.pi", (method)pi_new,(method)NULL, sizeof(t_pi), 0L, A_GIMME, 0);
    class_addmethod(c, (method)pi_bang,     "bang",      A_CANT, 0);
    class_addmethod(c, (method)pi_float,     "float",      A_FLOAT, 0);

    pi_class = c;
}

void *pi_new(t_symbol *s, int argc, t_atom *argv)
{
    t_pi *x = (t_pi *)object_alloc(pi_class);
	x->p_value = 1.;
    x->p_value = atom_getfloat(argv);

    outlet_new(&x->p_ob.e_obj, &s_float);
	
	return(x);
}


void pi_bang(t_pi *x) 
{
    outlet_float(x->p_ob.e_obj.ob_outlet, CICM_PI * x->p_value);
}

void pi_float(t_pi *x, float n)
{
	x->p_value = n;
	pi_bang(x);
}


