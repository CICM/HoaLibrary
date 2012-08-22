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

typedef struct _HoaConvolve 
{
	t_pxobject					f_ob;			
	AmbisonicEncode				*f_ambiEncoder;
	
	int							f_n;
	int							f_sr;
	
	long						f_inputNumber;
	long						f_outputNumber;
	long						f_order;
	long						f_harmonics;
	std::vector<double>			f_computedOuput;
	
	double						*f_inputSig;
} t_HoaConvolve;


void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv);
void HoaConvolve_free(t_HoaConvolve *x);
void HoaConvolve_assist(t_HoaConvolve *x, void *b, long m, long a, char *s);

void HoaConvolve_float(t_HoaConvolve *x, double f);
void HoaConvolve_int(t_HoaConvolve *x, long n);

void HoaConvolve_dsp(t_HoaConvolve *x, t_signal **sp, short *count);
t_int *HoaConvolve_perform(t_int *w);

void HoaConvolve_dsp64(t_HoaConvolve *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);

void *HoaConvolve_class;
    

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.convolve~", (method)HoaConvolve_new, (method)HoaConvolve_free, (long)sizeof(t_HoaConvolve), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaConvolve_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaConvolve_int,			"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaConvolve_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaConvolve_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaConvolve_assist,		"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaConvolve_class = c;
	
	post("hoa.encoder~ by Julien Colafrancesco & Pierre Guillot",0);
	post("Copyright (C) 2012, CICM / Universite Paris 8");
	
	return 0;
}

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaConvolve *x = NULL;
	
	if (x = (t_HoaConvolve *)object_alloc((t_class*)HoaConvolve_class)) 
	{
		x->f_mode = 0;
		x->f_order = 1;
		if(argv[0].a_type == A_LONG)
			x->f_order = atom_getlong(argv);
		if(x->f_order < 1) x->f_order = 1;
		x->f_harmonics = 2 * x->f_order + 1;
			
		x->f_inputNumber = x->f_harmonics * 2;
		x->f_outputNumber = x->f_harmonics;
		
		x->f_ambiEncoder = new AmbisonicEncode(x->f_order);
		
		if (x->f_mode)
			dsp_setup((t_pxobject *)x, x->f_inputNumber);
		else
			dsp_setup((t_pxobject *)x, 2);	
		for (int i = 0; i < x->f_outputNumber; i++) 
			outlet_new(x, "signal");
		
	}
	return (x);
}

void HoaConvolve_float(t_HoaConvolve *x, double f)
{
	//x->f_ambiEncoder->computeCoefs(f);
}

void HoaConvolve_int(t_HoaConvolve *x, long n)
{
	//x->f_ambiEncoder->computeCoefs(n);
}

void HoaConvolve_dsp64(t_HoaConvolve *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_n	= maxvectorsize;
	x->f_sr	= samplerate;
	x->f_inputSig = (double *)getbytes(x->f_inputNumber * sizeof(double));
	object_method(dsp64, gensym("dsp_add64"), x, HoaConvolve_perform64, 0, NULL);
}

void HoaConvolve_perform64(t_HoaConvolve *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for (int i = 0; i < sampleframes; i++) 
	{
		for (int j = 0; j < x->f_harmonics; j++)
		{
			x->f_inputSig[j] = ins[j][i];
			x->f_inputSig[j+x->f_harmonics] = ins[j+x->f_harmonics][i];
		}
		x->f_computedOuput = x->f_ambiEncoder->process(x->f_inputSig, x->f_inputSig+x->f_harmonics);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			outs[j][i] = x->f_computedOuput[j];
	}
}

void HoaConvolve_dsp(t_HoaConvolve *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_n	= (int)sp[0]->s_n;
	x->f_sr	= (int)sp[0]->s_sr;
		x->f_inputSig = (double *)getbytes(x->f_inputNumber * sizeof(double));
		pointer_count = x->f_outputNumber + 2 + x->f_inputNumber;
		
		sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
		for(i = 0; i < pointer_count; i++)
			sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
		
		sigvec[0] = (t_int *)x;
		sigvec[1] = (t_int *)sp[0]->s_n;
		for(i = 2; i < pointer_count; i++)
			sigvec[i] = (t_int *)sp[i - 2]->s_vec;
		if(count[1])
			dsp_addv(HoaConvolve_performVec, pointer_count, (void **)sigvec);
		else
			dsp_addv(HoaConvolve_performOffsetVec, pointer_count, (void **)sigvec);
		
		free(sigvec);

}

t_int *HoaConvolve_perform(t_int *w)
{
	t_HoaConvolve *x			= (t_HoaConvolve *)(w[1]);
	int			n			= (int)(w[2]);
	t_float		**signals	= (t_float **)w+3;
	
	for (int i = 0; i < n; i++) 
	{		
		for (int j = 0; j < x->f_harmonics; j++)
		{
			x->f_inputSig[j] = signals[j][i];signals
			x->f_inputSig[j+x->f_harmonics] = ins[j+x->f_harmonics][i];
		}
		
		x->f_computedOuput = x->f_ambiEncoder->process(x->f_inputSig, x->f_inputSig+x->f_harmonics);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			signals[j+x->f_inputNumber][i] = x->f_computedOuput[j];
	}
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}


void HoaConvolve_assist(t_HoaConvolve *x, void *b, long m, long a, char *s)
{
	
	if (m == ASSIST_INLET) 
	{
		if(a == 0)
			sprintf(s,"(Signal) Input signal");
		else 
			sprintf(s,"(Signal or float) Azimuth");
	} 
	else 
	{
		long harmonicIndex = 0;
		if (a == 0)
			harmonicIndex = 0;
		else {
			harmonicIndex = (int)floor((a-1)/2) + 1;
			if (a%2 == 1) 
				harmonicIndex = - harmonicIndex;
		}

		sprintf(s,"(Signal) Spherical harmonic %i dependant signal", harmonicIndex); 			
	}
}


void HoaConvolve_free(t_HoaConvolve *x) 
{
	dsp_free((t_pxobject *)x);
}

