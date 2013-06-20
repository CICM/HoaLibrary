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

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

typedef struct _pi 
{	
	t_object p_ob;
	double p_value;	
	void *p_outlet;
} t_pi;

void pi_bang(t_pi *x);
void pi_int(t_pi *x, long n);
void pi_float(t_pi *x, double n) ;
void pi_assist(t_pi *x, void *b, long m, long a, char *s);
void *pi_new(t_symbol *s, int argc, t_atom *argv);

t_class *pi_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.pi", (method)pi_new, (method)NULL, sizeof(t_pi), 0L, A_GIMME, 0);
	
    class_addmethod(c, (method)pi_bang,		"bang",		0);	
    class_addmethod(c, (method)pi_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)pi_float,	"float",	A_FLOAT, 0);
    class_addmethod(c, (method)pi_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)pi_bang,		"dblclick",	A_CANT, 0);
	
	class_register(CLASS_BOX, c);
	pi_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *pi_new(t_symbol *s, int argc, t_atom *argv)
{
	t_pi *x = (t_pi *)object_alloc(pi_class);
	x->p_value = 1.;
	if (atom_gettype(argv) == A_LONG)
		x->p_value = atom_getlong(argv);
	else if (atom_gettype(argv) == A_FLOAT)
		x->p_value = atom_getfloat(argv);

	x->p_outlet = floatout(x);
	defer_low(x, (method)pi_bang, NULL, 0, NULL);
	return(x);
}

void pi_assist(t_pi *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_OUTLET)
		sprintf(s,"(Int, Float or Bang) Compute");
	else
		sprintf(s,"(Float) PI * %.f", x->p_value);
}

void pi_bang(t_pi *x) 
{
	outlet_float(x->p_outlet, PI * x->p_value);
}


void pi_int(t_pi *x, long n)
{
	x->p_value = n;
	pi_bang(x);
}


void pi_float(t_pi *x, double n) 
{
	x->p_value = n;
	pi_bang(x);
}


