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

#include "ambisonicProjector.h"


typedef struct _HoaProjector
{
	t_pxobject					f_ob;			
	ambisonicProjector			*f_ambisonicProjector;

	int							f_ninputs;
	int							f_noutputs;
} t_HoaProjector;

void *HoaProjector_new(t_symbol *s, long argc, t_atom *argv);
void HoaProjector_free(t_HoaProjector *x);
void HoaProjector_assist(t_HoaProjector *x, void *b, long m, long a, char *s);
void HoaProjector_optim(t_HoaProjector *x, t_symbol *s, long argc, t_atom *argv);

void HoaProjector_dsp(t_HoaProjector *x, t_signal **sp, short *count);
t_int *HoaProjector_perform(t_int *w);

void HoaProjector_dsp64(t_HoaProjector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaProjector_perform64(t_HoaProjector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaProjector_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.projector~", (method)HoaProjector_new, (method)dsp_free, (long)sizeof(t_HoaProjector), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaProjector_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaProjector_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaProjector_assist,			"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaProjector_optim,			"optim",	A_GIMME, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaProjector_class = c;
	
	return 0;
}

void *HoaProjector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaProjector *x = NULL;
	int order = 4, outputs = 9;
	if (x = (t_HoaProjector *)object_alloc((t_class*)HoaProjector_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			outputs	= atom_getlong(argv+1);
		
		x->f_ambisonicProjector	= new ambisonicProjector(order, outputs, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambisonicProjector->getParameters("numberOfInputs"));
		for (int i = 0; i < x->f_ambisonicProjector->getParameters("numberOfOutputs"); i++) 
			outlet_new(x, "signal");
		
	
	}
	return (x);
}

void HoaProjector_dsp64(t_HoaProjector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambisonicProjector->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaProjector_perform64, 0, NULL);
}

void HoaProjector_perform64(t_HoaProjector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambisonicProjector->process(ins, outs);
}

void HoaProjector_dsp(t_HoaProjector *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ninputs = x->f_ambisonicProjector->getParameters("numberOfInputs");
	x->f_noutputs = x->f_ambisonicProjector->getParameters("numberOfOutputs");
	x->f_ambisonicProjector->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_ambisonicProjector->getParameters("numberOfInputs") + x->f_ambisonicProjector->getParameters("numberOfOutputs") + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaProjector_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaProjector_perform(t_int *w)
{
	t_HoaProjector *x		= (t_HoaProjector *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninputs;

	x->f_ambisonicProjector->process(ins, outs);
	
	return (w + x->f_noutputs + x->f_ninputs + 3);
}

void HoaProjector_assist(t_HoaProjector *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		long harmonicIndex = 0;
		if (a != 0)
		{
			harmonicIndex = floor((a - 1) / 2) + 1;
			if (a % 2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex);
	}
	else 
		sprintf(s,"(Signal) Virtual Microphone %ld", a);			
}


void HoaProjector_optim(t_HoaProjector *x, t_symbol *s, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_SYM)
	{
		std::string decodingId = atom_getsym(argv)->s_name;
		x->f_ambisonicProjector->setOptimMode(decodingId);
	}
}

void HoaProjector_free(t_HoaProjector *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_ambisonicProjector);
}

