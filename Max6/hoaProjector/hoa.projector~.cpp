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
 
#include "AmbisonicsProjector.h"
extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}

typedef struct _HoaProjector
{
	t_pxobject					f_ob;			
	AmbisonicsProjector			*f_AmbisonicsProjector;

	int							f_ninputs;
	int							f_noutputs;
} t_HoaProjector;

void *HoaProjector_new(t_symbol *s, long argc, t_atom *argv);
void HoaProjector_free(t_HoaProjector *x);
void HoaProjector_assist(t_HoaProjector *x, void *b, long m, long a, char *s);

void HoaProjector_dsp(t_HoaProjector *x, t_signal **sp, short *count);
t_int *HoaProjector_perform(t_int *w);

void HoaProjector_dsp64(t_HoaProjector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaProjector_perform64(t_HoaProjector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaProjector_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.projector~", (method)HoaProjector_new, (method)dsp_free, (long)sizeof(t_HoaProjector), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaProjector_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaProjector_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaProjector_assist,			"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaProjector_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaProjector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaProjector *x = NULL;
	int order = 4, outputs = 9;
    x = (t_HoaProjector *)object_alloc((t_class*)HoaProjector_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			outputs	= atom_getlong(argv+1);
		
		x->f_AmbisonicsProjector	= new AmbisonicsProjector(order, outputs, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsProjector->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsProjector->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
	
	}
	return (x);
}

void HoaProjector_dsp64(t_HoaProjector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicsProjector->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaProjector_perform64, 0, NULL);
}

void HoaProjector_perform64(t_HoaProjector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicsProjector->process(ins, outs);
}

void HoaProjector_dsp(t_HoaProjector *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ninputs = x->f_AmbisonicsProjector->getNumberOfInputs();
	x->f_noutputs = x->f_AmbisonicsProjector->getNumberOfOutputs();
	x->f_AmbisonicsProjector->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_AmbisonicsProjector->getNumberOfInputs() + x->f_AmbisonicsProjector->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)malloc(pointer_count * sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)malloc(sizeof(t_int));
	
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

	x->f_AmbisonicsProjector->process(ins, outs);
	
	return (w + x->f_noutputs + x->f_ninputs + 3);
}

void HoaProjector_assist(t_HoaProjector *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		sprintf(s,"(Signal) Harmonic %ld", x->f_AmbisonicsProjector->getHarmonicIndex(a));
	}
	else 
		sprintf(s,"(Signal) Virtual Microphone %ld", a);			
}

void HoaProjector_free(t_HoaProjector *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_AmbisonicsProjector);
}

