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

#include "ambisonicRecomposer.hpp"
extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}



typedef struct _HoaRecomposer 
{
	t_pxobject					f_ob;			
	ambisonicRecomposer			*f_ambiRecomposer;

	long						f_inputNumber;
	long						f_outputNumber;
} t_HoaRecomposer;

void *HoaRecomposer_new(t_symbol *s, long argc, t_atom *argv);
void HoaRecomposer_free(t_HoaRecomposer *x);
void HoaRecomposer_assist(t_HoaRecomposer *x, void *b, long m, long a, char *s);
void HoaRecomposer_int(t_HoaRecomposer *x, long n);
void HoaRecomposer_float(t_HoaRecomposer *x, double f);

void HoaRecomposer_dsp(t_HoaRecomposer *x, t_signal **sp, short *count);
t_int *HoaRecomposer_perform(t_int *w);
t_int *HoaRecomposer_performOffset(t_int *w);

void HoaRecomposer_dsp64(t_HoaRecomposer *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaRecomposer_perform64(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaRecomposer_perform64Offset(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaRecomposer_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.recomposer~", (method)HoaRecomposer_new, (method)HoaRecomposer_free, (long)sizeof(t_HoaRecomposer), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaRecomposer_float,			"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaRecomposer_int,			"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaRecomposer_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_assist,		"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaRecomposer_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaRecomposer_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaRecomposer *x = NULL;

	int order = 4, inputs = 9;
	if (x = (t_HoaRecomposer *)object_alloc((t_class*)HoaRecomposer_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			inputs	= atom_getlong(argv+1);

		x->f_ambiRecomposer	= new ambisonicRecomposer(order, inputs);
		
		dsp_setup((t_pxobject *)x, x->f_ambiRecomposer->getParameters("numberOfInputs") + 1);
		for (int i = 0; i < x->f_ambiRecomposer->getParameters("numberOfOutputs"); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaRecomposer_float(t_HoaRecomposer *x, double f)
{
	x->f_ambiRecomposer->setFishEyeFactor(f);
}

void HoaRecomposer_int(t_HoaRecomposer *x, long n)
{
	x->f_ambiRecomposer->setFishEyeFactor(n);
}

void HoaRecomposer_dsp64(t_HoaRecomposer *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiRecomposer->setVectorSize(maxvectorsize);
	x->f_inputNumber = x->f_ambiRecomposer->getParameters("numberOfInputs") + 1;
	if(count[x->f_inputNumber - 1])
		object_method(dsp64, gensym("dsp_add64"), x, HoaRecomposer_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, HoaRecomposer_perform64Offset, 0, NULL);
}

void HoaRecomposer_perform64(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiRecomposer->process(ins, outs, ins[x->f_inputNumber-1]);
}

void HoaRecomposer_perform64Offset(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiRecomposer->process(ins, outs);
}

void HoaRecomposer_dsp(t_HoaRecomposer *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ambiRecomposer->setVectorSize(sp[0]->s_n);
	x->f_inputNumber = x->f_ambiRecomposer->getParameters("numberOfInputs") + 1;
	x->f_outputNumber = x->f_ambiRecomposer->getParameters("numberOfOutputs");
	pointer_count = x->f_inputNumber + x->f_outputNumber + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	if(count[x->f_inputNumber - 1])
		dsp_addv(HoaRecomposer_perform, pointer_count, (void **)sigvec);
	else
		dsp_addv(HoaRecomposer_performOffset, pointer_count, (void **)sigvec);
	free(sigvec);
}

t_int *HoaRecomposer_perform(t_int *w)
{
	t_HoaRecomposer *x		= (t_HoaRecomposer *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiRecomposer->process(ins, outs, ins[x->f_inputNumber-1]);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

t_int *HoaRecomposer_performOffset(t_int *w)
{
	t_HoaRecomposer *x			= (t_HoaRecomposer *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiRecomposer->process(ins, outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaRecomposer_assist(t_HoaRecomposer *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_INLET)
	{
		long harmonicIndex = 0;
		if (a == 0)
			harmonicIndex = 0;
		else 
		{
			harmonicIndex = (a - 1) / 2 + 1;
			if (a % 2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex);
	}
	else 
	{
		if(a == x->f_ambiRecomposer->getParameters("numberOfInputs"))
			sprintf(s,"(Signal or float) Azimuth");	
		else
			sprintf(s,"(Signal) Virtual Microphone %ld", a);
	}
}

void HoaRecomposer_free(t_HoaRecomposer *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiRecomposer;
}

