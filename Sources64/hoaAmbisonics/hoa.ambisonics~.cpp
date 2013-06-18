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

#include "Ambisonics.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}


typedef struct _HoaAmbisonics 
{
	t_pxobject	f_ob;			
	Ambisonics*	f_Ambisonics;

	int			f_ninput;
	int			f_noutput;

} t_HoaAmbisonics;

void *HoaAmbisonics_new(t_symbol *s, long argc, t_atom *argv);
void HoaAmbisonics_free(t_HoaAmbisonics *x);
void HoaAmbisonics_assist(t_HoaAmbisonics *x, void *b, long m, long a, char *s);

void HoaAmbisonics_dsp(t_HoaAmbisonics *x, t_signal **sp, short *count);
t_int *HoaAmbisonics_perform(t_int *w);

void HoaAmbisonics_dsp64(t_HoaAmbisonics *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaAmbisonics_perform64(t_HoaAmbisonics *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* HoaAmbisonics_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.ambisonics~", (method)HoaAmbisonics_new, (method)dsp_free, (long)sizeof(t_HoaAmbisonics), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaAmbisonics_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaAmbisonics_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaAmbisonics_assist,		"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaAmbisonics_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaAmbisonics_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaAmbisonics *x = NULL;
	int order = 4;
	
    x = (t_HoaAmbisonics *)object_alloc(HoaAmbisonics_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
			
		x->f_Ambisonics	= new Ambisonics(order, sys_getblksize(), sys_getsr());
		
		dsp_setup((t_pxobject *)x, x->f_Ambisonics->getNumberOfInputs());
		for (int i = 0; i < x->f_Ambisonics->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaAmbisonics_dsp64(t_HoaAmbisonics *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_Ambisonics->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaAmbisonics_perform64, 0, NULL);
}

void HoaAmbisonics_perform64(t_HoaAmbisonics *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_Ambisonics->process(ins, outs);
}

void HoaAmbisonics_dsp(t_HoaAmbisonics *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_Ambisonics->setVectorSize(sp[0]->s_n);
	x->f_ninput = x->f_Ambisonics->getNumberOfInputs();
	x->f_noutput = x->f_Ambisonics->getNumberOfOutputs();
	pointer_count = x->f_Ambisonics->getNumberOfInputs() + x->f_Ambisonics->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaAmbisonics_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaAmbisonics_perform(t_int *w)
{
	t_HoaAmbisonics *x			= (t_HoaAmbisonics *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninput;
	
	x->f_Ambisonics->process(ins, outs);
	
	return (w + x->f_ninput + x->f_noutput + 3);
}

void HoaAmbisonics_assist(t_HoaAmbisonics *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) Harmonic %ld", x->f_Ambisonics->getHarmonicIndex(a));
}


void HoaAmbisonics_free(t_HoaAmbisonics *x)
{
	dsp_free((t_pxobject *)x);
	delete(x->f_Ambisonics);
}

