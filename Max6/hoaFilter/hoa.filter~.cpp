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

#include "../../Sources/HoaLibrary.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

typedef struct _HoaFilter 
{
	t_pxobject					f_ob;			
	AmbisonicsFilter			*f_ambiFilter;
	
	long						f_inputNumber;
	long						f_outputNumber;
} t_HoaFilter;


void *HoaFilter_new(t_symbol *s, long argc, t_atom *argv);
void HoaFilter_free(t_HoaFilter *x);
void HoaFilter_assist(t_HoaFilter *x, void *b, long m, long a, char *s);

void HoaFilter_float(t_HoaFilter *x, double f);
void HoaFilter_int(t_HoaFilter *x, long n);

void HoaFilter_dsp(t_HoaFilter *x, t_signal **sp, short *count);
t_int *HoaFilter_perform(t_int *w);

void HoaFilter_dsp64(t_HoaFilter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaFilter_perform64(t_HoaFilter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *HoaFilter_class;
    

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.filter~", (method)HoaFilter_new, (method)HoaFilter_free, (long)sizeof(t_HoaFilter), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaFilter_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaFilter_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaFilter_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaFilter_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaFilter_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	HoaFilter_class = c;
    
	return 0;
}

void *HoaFilter_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaFilter *x = NULL;
	int	order = 4;
	int mode = Hoa_Basic;
    x = (t_HoaFilter *)object_alloc(HoaFilter_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		if(atom_gettype(argv + 1) == A_SYM && atom_getsym(argv + 1) == gensym("split"))
			mode = Hoa_Split;
		
		x->f_ambiFilter = new AmbisonicsFilter(order, sys_getblksize(), sys_getsr());
		
		dsp_setup((t_pxobject *)x, x->f_ambiFilter->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiFilter->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaFilter_float(t_HoaFilter *x, double f)
{
	x->f_ambiFilter->setDiffusion(f);
}

void HoaFilter_int(t_HoaFilter *x, long n)
{
	x->f_ambiFilter->setDiffusion(n);
}

void HoaFilter_dsp64(t_HoaFilter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiFilter->setVectorSize(maxvectorsize);
    x->f_ambiFilter->setSamplingRate(samplerate);
    
    object_method(dsp64, gensym("dsp_add64"), x, HoaFilter_perform64, 0, NULL);
}

void HoaFilter_perform64(t_HoaFilter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiFilter->process(ins, outs);
}


void HoaFilter_dsp(t_HoaFilter *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ambiFilter->setVectorSize(sp[0]->s_n);
	x->f_inputNumber = x->f_ambiFilter->getNumberOfInputs();
	x->f_outputNumber = x->f_ambiFilter->getNumberOfOutputs();
    pointer_count = x->f_outputNumber + 2 + x->f_inputNumber;
		
    sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
    for(i = 0; i < pointer_count; i++)
        sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
		
    sigvec[0] = (t_int *)x;
    sigvec[1] = (t_int *)sp[0]->s_n;
    for(i = 2; i < pointer_count; i++)
        sigvec[i] = (t_int *)sp[i - 2]->s_vec;
    if(count[x->f_inputNumber - 1])
        dsp_addv(HoaFilter_perform, pointer_count, (void **)sigvec);		
    free(sigvec);
}

t_int *HoaFilter_perform(t_int *w)
{
	t_HoaFilter *x			= (t_HoaFilter *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiFilter->process(ins, outs);

	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaFilter_assist(t_HoaFilter *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_ambiFilter->getHarmonicsName(a).c_str());
}


void HoaFilter_free(t_HoaFilter *x) 
{
	dsp_free((t_pxobject *)x);
	delete(x->f_ambiFilter);
}

