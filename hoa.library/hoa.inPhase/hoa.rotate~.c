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

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}


#include "ambisonicRotate.h"
#include <iostream>
#include <vector>
typedef struct _HoaDecode 
{
	t_pxobject					f_ob;			
	ambisonicRotate				*f_ambisonicRotate;
	double						*f_vector;
	int							f_n;
	int							f_sr;
	long						f_order;
	long						f_inputNumber;
	long						f_outputNumber;

} t_HoaDecode;

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv);
void HoaDecode_free(t_HoaDecode *x);
void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s);
void HoaDecode_dsp(t_HoaDecode *x, t_signal **sp, short *count);
t_int *HoaDecode_perform(t_int *w);

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaDecode_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.inPhase~", (method)HoaDecode_new, (method)HoaDecode_free, (long)sizeof(t_HoaDecode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaDecode_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_dsp64,		"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaDecode_class = c;
	
	post("hoa.rotate~ by Julien Colafrancesco & Pierre Guillot",0);
	post("Copyright (C) 2012, CICM / Universite Paris 8");
	
	return 0;
}

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaDecode *x = NULL;
	
	if (x = (t_HoaDecode *)object_alloc((t_class*)HoaDecode_class)) 
	{
		x->f_order = 1;
		x->f_outputNumber = 4;
		if(atom_gettype(argv) == A_LONG)
			x->f_order			= atom_getlong(argv);

		x->f_outputNumber		= x->f_order * 2 + 1;
		x->f_inputNumber		= x->f_order * 2 + 2;
		
		x->f_vector				= (double *)getbytes(sizeof(double) * (x->f_inputNumber-1));
		
		dsp_setup((t_pxobject *)x, x->f_inputNumber);	
		for (int i = 0; i < x->f_outputNumber; i++)
			outlet_new(x, "signal");		
	}
	return (x);
}

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_n	= maxvectorsize;
	x->f_sr	= samplerate;
	x->f_ambisonicRotate	= new ambisonicRotate(x->f_order);
	object_method(dsp64, gensym("dsp_add64"), x, HoaDecode_perform64, 0, NULL);
}

void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double* ComputedOuput;
	
	for (int i = 0; i < sampleframes; i++) 
	{
		for (int j = 0; j < x->f_inputNumber - 2; j++)
			x->f_vector[j] = ins[j][i];
		
		ComputedOuput = x->f_ambisonicRotate->process(x->f_vector, ins[x->f_inputNumber-1][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			outs[j][i] = ComputedOuput[j];
	}
}

void HoaDecode_dsp(t_HoaDecode *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_n	= (int)sp[0]->s_n;
	x->f_sr	= (int)sp[0]->s_sr;
	x->f_ambisonicRotate	= new ambisonicRotate(x->f_order);
	
	pointer_count = x->f_inputNumber + x->f_outputNumber + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaDecode_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaDecode_perform(t_int *w)
{
	t_HoaDecode *x			= (t_HoaDecode *)(w[1]);	
	int			n			= (int)(w[2]);
	t_float		**signals	= (t_float **)w+3;
	
	double* ComputedOuput;
	
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < x->f_inputNumber-1; j++)
			x->f_vector[j] = signals[j][i];
		
		ComputedOuput = x->f_ambisonicRotate->process(x->f_vector, signals[x->f_inputNumber-1][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			signals[j+x->f_inputNumber][i] = ComputedOuput[j];
	}
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s)
{
	long harmonicIndex = 0;
	if (a != x->f_inputNumber-1 || m != ASSIST_INLET)
	{
		if (a == 0)
			harmonicIndex = 0;
		else {
			harmonicIndex = (int)floor((a-1)/2) + 1;
			if (a%2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Spherical harmonic %i dependant signal", (int)harmonicIndex); 
	}
	else
		sprintf(s,"Rotation value (rad)"); 

}


void HoaDecode_free(t_HoaDecode *x)
{
	dsp_free((t_pxobject *)x);
	freebytes(x->f_vector,sizeof(t_float) * (x->f_outputNumber + x->f_inputNumber));
}

