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

#include <AmbisonicCentralize.h>

typedef struct _HoaCentralize 
{
	t_pxobject					f_ob;			
	AmbisonicCentralize			*f_ambiCentralizer;
	
	int							f_n;
	int							f_sr;
	
	long						f_inputNumber;
	long						f_outputNumber;
	long						f_order;
	long						f_harmonics;
	std::vector<double>			f_computedOuput;
	
	double						*f_inputSig;
} t_HoaCentralize;


void *HoaCentralize_new(t_symbol *s, long argc, t_atom *argv);
void HoaCentralize_free(t_HoaCentralize *x);
void HoaCentralize_assist(t_HoaCentralize *x, void *b, long m, long a, char *s);

void HoaCentralize_float(t_HoaCentralize *x, double f);
void HoaCentralize_int(t_HoaCentralize *x, long n);

void HoaCentralize_dsp(t_HoaCentralize *x, t_signal **sp, short *count);
t_int *HoaCentralize_perform(t_int *w);
t_int *HoaCentralize_performOffset(t_int *w);

void HoaCentralize_dsp64(t_HoaCentralize *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaCentralize_perform64(t_HoaCentralize *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaCentralize_perform64Offset(t_HoaCentralize *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaCentralize_class;
    

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.centralizer~", (method)HoaCentralize_new, (method)HoaCentralize_free, (long)sizeof(t_HoaCentralize), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaCentralize_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaCentralize_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaCentralize_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaCentralize_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaCentralize_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaCentralize_class = c;
	
	post("hoa.centralizer~ by Julien Colafrancesco & Pierre Guillot",0);
	post("Copyright (C) 2012, CICM / Universite Paris 8");
	
	return 0;
}

void *HoaCentralize_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaCentralize *x = NULL;
	
	if (x = (t_HoaCentralize *)object_alloc((t_class*)HoaCentralize_class)) 
	{
		x->f_order = 1;
		if(argv[0].a_type == A_LONG)
			x->f_order = atom_getlong(argv);
		if(x->f_order < 1) x->f_order = 1;
		x->f_harmonics = 2 * x->f_order + 1;
		
			
		x->f_inputNumber = x->f_harmonics + 2;
		x->f_outputNumber = x->f_harmonics;
		
		x->f_ambiCentralizer = new AmbisonicCentralize(x->f_order);
		
		dsp_setup((t_pxobject *)x, x->f_inputNumber);
		for (int i = 0; i < x->f_outputNumber; i++) 
			outlet_new(x, "signal");
		//x->f_ob.z_misc != Z_NO_INPLACE;
		
	}
	return (x);
}

void HoaCentralize_float(t_HoaCentralize *x, double f)
{
	x->f_ambiCentralizer->computeCoefs(f);
}

void HoaCentralize_int(t_HoaCentralize *x, long n)
{
	x->f_ambiCentralizer->computeCoefs(n);
}

void HoaCentralize_dsp64(t_HoaCentralize *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_n	= maxvectorsize;
	x->f_sr	= samplerate;
	
	if(count[x->f_inputNumber - 1])
		object_method(dsp64, gensym("dsp_add64"), x, HoaCentralize_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, HoaCentralize_perform64Offset, 0, NULL);

}

void HoaCentralize_perform64(t_HoaCentralize *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for (int i = 0; i < sampleframes; i++) 
	{
		//x->f_computedOuput = x->f_ambiCentralizer->process(ins[0][i], ins[0][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			outs[j][i] = x->f_computedOuput[j];
	}
}

void HoaCentralize_perform64Offset(t_HoaCentralize *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for (int i = 0; i < sampleframes; i++) 
	{
		//x->f_computedOuput = x->f_ambiCentralizer->process(ins[0][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			outs[j][i] = x->f_computedOuput[j];
	}
}


void HoaCentralize_dsp(t_HoaCentralize *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_n	= (int)sp[0]->s_n;
	x->f_sr	= (int)sp[0]->s_sr;

	for(i = 0; i < x->f_inputNumber; i++)
		post("adress %i %p", i, (void *)sp[i]->s_vec);
	
	
	pointer_count = x->f_outputNumber + x->f_inputNumber + 2;
	x->f_inputSig = (double *)getbytes(x->f_harmonics * sizeof(double));
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaCentralize_perform, pointer_count, (void **)sigvec);

	free(sigvec);
	
}

t_int *HoaCentralize_perform(t_int *w)
{
	t_HoaCentralize *x			= (t_HoaCentralize *)(w[1]);
	int			n			= (int)(w[2]);
	t_float		**signals	= (t_float **)w+3;
	
	for (int i = 0; i < n; i++) 
	{	
		for (int j = 0; j < x->f_harmonics; j++)
			x->f_inputSig[j] = signals[j][i];
			
		x->f_computedOuput = x->f_ambiCentralizer->process(x->f_inputSig, signals[x->f_harmonics][i], signals[x->f_harmonics + 1][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			signals[j+x->f_inputNumber][i] = x->f_computedOuput[j];
	}
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

t_int *HoaCentralize_performOffset(t_int *w)
{
	t_HoaCentralize *x			= (t_HoaCentralize *)(w[1]);
	int			n			= (int)(w[2]);
	t_float		**signals	= (t_float **)w+3;
	
	for (int i = 0; i < n; i++) 
	{		
			//x->f_computedOuput = x->f_ambiCentralizer->process(signals[0][i]);
		
		for (int j = 0; j < x->f_outputNumber; j++) 
			signals[j+2][i] = x->f_computedOuput[j];
	}
	
	return (w + x->f_outputNumber + 5);
}

void HoaCentralize_assist(t_HoaCentralize *x, void *b, long m, long a, char *s)
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


void HoaCentralize_free(t_HoaCentralize *x) 
{
	dsp_free((t_pxobject *)x);
}
