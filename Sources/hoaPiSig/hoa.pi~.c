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
	t_pxobject p_ob;
	double p_value;	
	void *p_outlet;
} t_pi;

void pi_bang(t_pi *x);
void pi_int(t_pi *x, long n);
void pi_float(t_pi *x, double n) ;
void pi_assist(t_pi *x, void *b, long m, long a, char *s);
void *pi_new(t_symbol *s, int argc, t_atom *argv);

void pi_dsp(t_pi *x, t_signal **sp, short *count);
t_int *pi_perform(t_int *w);
t_int *pi_performFloat(t_int *w);

void pi_dsp64(t_pi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void pi_perform64(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void pi_perform64Float(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *pi_class;

int main(void)
{
	t_class *c;
	
	c = class_new("hoa.pi~", (method)pi_new, (method)dsp_free, sizeof(t_pi), 0L, A_GIMME, 0);
	
    class_addmethod(c, (method)pi_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)pi_float,	"float",	A_FLOAT, 0);
    class_addmethod(c, (method)pi_assist,	"assist",	A_CANT, 0);
    class_addmethod(c, (method)pi_dsp,      "dsp",	A_CANT, 0);
	class_addmethod(c, (method)pi_dsp64,	"dsp64",A_CANT, 0);
	
    class_dspinit(c);
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
    
    dsp_setup((t_pxobject *)x, 1);
    x->p_outlet = outlet_new(x, "signal");
	return(x);
}


void pi_dsp64(t_pi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	if(count[0])
		object_method(dsp64, gensym("dsp_add64"), x, pi_perform64, 0, NULL);
    else
		object_method(dsp64, gensym("dsp_add64"), x, pi_perform64Float, 0, NULL);
}

void pi_perform64(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int i;
    for(i = 0; i < sampleframes; i++)
        outs[0][i] = PI * ins[0][i];
}

void pi_perform64Float(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int i;
    for(i = 0; i < sampleframes; i++)
        outs[0][i] = PI * x->p_value;
}

void pi_dsp(t_pi *x, t_signal **sp, short *count)
{	
	if(count[0])
		dsp_add(pi_perform, 3, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
	else
		dsp_add(pi_performFloat, 3, x, sp[1]->s_vec, sp[0]->s_n);	
}

t_int *pi_perform(t_int *w)
{
	t_float *in = (t_float *)(w[1]);
	t_float *out = (t_float *)(w[2]);
	int n = (int)w[3];
	
	while (n--)
		*out++ = *in++ * PI;
    
	return w + 4;
}

t_int *pi_performFloat(t_int *w)
{
	t_pi *x = (t_pi *)(w[1]);
	t_float *out = (t_float *)(w[2]);
	int n = (int)w[3];
	
	while (n--)
		*out++ = x->p_value * PI;
    
	return w + 4;
}

void pi_assist(t_pi *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_OUTLET)
		sprintf(s,"(Signal/Float) Multiply by PI");
	else
		sprintf(s,"(Signal) PI * Factor");
}

void pi_int(t_pi *x, long n)
{
	x->p_value = n;
}


void pi_float(t_pi *x, double n) 
{
	x->p_value = n;
}