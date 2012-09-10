/*
 * Copyright (C) 2012 Pierre Guillot & Julien Colafransceco, Universite Paris 8
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

int main(void)
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


