/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

#include <AmbisonicEncode.h>

typedef struct _HoaEncode 
{
	t_pxobject					ob;			
	AmbisonicEncode*			AmbiEncoder;
	
	int							f_n;
	int							f_sr;
	
	long						f_inputNumber;
	long						f_outputNumber;
	long						f_order;
	long						f_harmonics;
	std::vector<double>			f_computedOuput;

} t_HoaEncode;


void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv);
void HoaEncode_free(t_HoaEncode *x);
void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s);

void HoaEncode_float(t_HoaEncode *x, double f);
void HoaEncode_int(t_HoaEncode *x, long n);

void HoaEncode_dsp(t_HoaEncode *x, t_signal **sp, short *count);
t_int *HoaEncode_perform(t_int *w);
t_int *HoaEncode_performOffset(t_int *w);

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaEncode_perform64Offset(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaEncode_class;
    

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.encoder~", (method)HoaEncode_new, (method)HoaEncode_free, (long)sizeof(t_HoaEncode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaEncode_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaEncode_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaEncode_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaEncode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaEncode_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaEncode_class = c;
	
	post("hoa.encoder~ by Julien Colafrancesco & Pierre Guillot",0);
	post("Copyright (C) 2012, CICM / Universite Paris 8");
	
	return 0;
}

void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaEncode *x = NULL;
	
	if (x = (t_HoaEncode *)object_alloc((t_class*)HoaEncode_class)) 
	{
		x->f_order = 1;
		if(argv[0].a_type == A_LONG)
			x->f_order = atom_getlong(argv);
		if(x->f_order < 1) x->f_order = 1;
		x->f_harmonics = 2 * x->f_order + 1;
		
		x->f_inputNumber = x->f_order + 2;
		x->f_outputNumber = x->f_harmonics;
		
		x->AmbiEncoder = new AmbisonicEncode(x->f_order);
		
		dsp_setup((t_pxobject *)x, 2);	
		for (int i = 0; i < x->f_outputNumber; i++) 
			outlet_new(x, "signal");
		
	}
	return (x);
}

void HoaEncode_float(t_HoaEncode *x, double f)
{
	x->AmbiEncoder->computeCoefs(f);
}

void HoaEncode_int(t_HoaEncode *x, long n)
{
	x->AmbiEncoder->computeCoefs(n);
}

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_n	= maxvectorsize;
	x->f_sr	= samplerate;
	
	
	if(count[x->f_inputNumber - 1])
		object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64Offset, 0, NULL);
}

void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for (int i = 0; i < sampleframes; i++) 
	{
		for (int j = 0; j < x->f_inputNumber - 1; j++)
		
		x->f_computedOuput = x->AmbiEncoder->process(ins[0][i], ins[1][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			outs[j][i] = x->f_computedOuput[j];
	}
}

void HoaEncode_perform64Offset(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for (int i = 0; i < sampleframes; i++) 
	{
		x->f_computedOuput = x->AmbiEncoder->process(ins[0][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			outs[j][i] = x->f_computedOuput[j];
	}
}

void HoaEncode_dsp(t_HoaEncode *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_n	= (int)sp[0]->s_n;
	x->f_sr	= (int)sp[0]->s_sr;
	
	pointer_count = 2 + x->f_outputNumber + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;

	if(count[1])
		dsp_addv(HoaEncode_perform, pointer_count, (void **)sigvec);
	else
		dsp_addv(HoaEncode_performOffset, pointer_count, (void **)sigvec);

	free(sigvec);
}

t_int *HoaEncode_perform(t_int *w)
{
	t_HoaEncode *x			= (t_HoaEncode *)(w[1]);
	int			n			= (int)(w[2]);
	t_float		**signals	= (t_float **)w+3;
	
	for (int i = 0; i < n; i++) 
	{		
		x->f_computedOuput = x->AmbiEncoder->process(signals[0][i], signals[1][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			signals[j+2][i] = x->f_computedOuput[j];
	}
	
	return (w + x->f_outputNumber + 2 + 3);
}

t_int *HoaEncode_performOffset(t_int *w)
{
	t_HoaEncode *x			= (t_HoaEncode *)(w[1]);
	int			n			= (int)(w[2]);
	t_float		**signals	= (t_float **)w+3;
	
	for (int i = 0; i < n; i++) 
	{		
		x->f_computedOuput = x->AmbiEncoder->process(signals[0][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			signals[j+2][i] = x->f_computedOuput[j];
	}
	
	return (w + x->f_outputNumber + 2 + 3);
}

void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		if(a < x->f_inputNumber - 1)
			sprintf(s,"(Signal) Order %i dependant signal", (int)a);
		else 
			sprintf(s,"(Signal or float) Azimuth");
	} 
	else 
	{
		sprintf(s,"(Signal) Spherical harmonic %i dependant signal", (int)(a - (x->f_harmonics - 1) / 2)); 			
	}
}


void HoaEncode_free(t_HoaEncode *x) 
{
	dsp_free((t_pxobject *)x);
}

