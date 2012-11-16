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

#include "ambisonicStereo.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}

typedef struct _HoaStereo
{
	t_pxobject					f_ob;			
	ambisonicStereo			*f_ambisonicStereo;

	int							f_ninputs;
	int							f_noutputs;
} t_HoaStereo;

void *HoaStereo_new(t_symbol *s, long argc, t_atom *argv);
void HoaStereo_free(t_HoaStereo *x);
void HoaStereo_assist(t_HoaStereo *x, void *b, long m, long a, char *s);

void HoaStereo_dsp(t_HoaStereo *x, t_signal **sp, short *count);
t_int *HoaStereo_perform(t_int *w);

void HoaStereo_dsp64(t_HoaStereo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaStereo_perform64(t_HoaStereo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaStereo_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaStereo *x = NULL;
	int order = 4;
	double anAngle = 30.;
	if (x = (t_HoaStereo *)object_alloc((t_class*)HoaStereo_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			anAngle	= atom_getlong(argv+1);
		else if(atom_gettype(argv+1) == A_FLOAT)
			anAngle	= atom_getfloat(argv+1);

		x->f_ambisonicStereo	= new ambisonicStereo(order, anAngle, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambisonicStereo->getParameters("numberOfInputs"));
		for (int i = 0; i < x->f_ambisonicStereo->getParameters("numberOfOutputs"); i++) 
			outlet_new(x, "signal");
		
	
	}
	return (x);
}

void HoaStereo_dsp64(t_HoaStereo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambisonicStereo->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaStereo_perform64, 0, NULL);
}

void HoaStereo_perform64(t_HoaStereo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambisonicStereo->process(ins, outs);
}

void HoaStereo_dsp(t_HoaStereo *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ninputs = x->f_ambisonicStereo->getParameters("numberOfInputs");
	x->f_noutputs = x->f_ambisonicStereo->getParameters("numberOfOutputs");
	x->f_ambisonicStereo->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_ambisonicStereo->getParameters("numberOfInputs") + x->f_ambisonicStereo->getParameters("numberOfOutputs") + 2;
	
	sigvec  = (t_int **)malloc(pointer_count * sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)malloc(sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaStereo_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaStereo_perform(t_int *w)
{
	t_HoaStereo *x		= (t_HoaStereo *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninputs;

	x->f_ambisonicStereo->process(ins, outs);
	
	return (w + x->f_noutputs + x->f_ninputs + 3);
}

void HoaStereo_assist(t_HoaStereo *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		long harmonicIndex = 0;
		if (a != 0)
		{
			harmonicIndex = (a - 1) / 2 + 1;
			if (a % 2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex);
	}
	else 
	{
		if (a == 0)
			sprintf(s,"(Signal) Left channel", a);
		if (a == 1)
			sprintf(s,"(Signal) Right channel", a);
	}
}

void HoaStereo_free(t_HoaStereo *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_ambisonicStereo);
}

