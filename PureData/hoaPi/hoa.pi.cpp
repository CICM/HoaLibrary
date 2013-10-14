/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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


