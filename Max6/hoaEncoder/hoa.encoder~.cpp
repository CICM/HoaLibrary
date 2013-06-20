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

#include "../../Sources64/hoaEncoder/AmbisonicsEncoder.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "../hoaHeader.h"
}

int postons = 0;

typedef struct _HoaEncode 
{
	t_pxobject					f_ob;			
	AmbisonicsEncoder			*f_ambiEncoder;
	
	long						f_inputNumber;
	long						f_outputNumber;
} t_HoaEncode;


void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv);
void HoaEncode_free(t_HoaEncode *x);
void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s);

void HoaEncode_float(t_HoaEncode *x, double f);
void HoaEncode_int(t_HoaEncode *x, long n);

void HoaEncode_dsp(t_HoaEncode *x, t_signal **sp, short *count);
t_int *HoaEncode_perform(t_int *w);
t_int *HoaEncode_performOffset(t_int *w);
t_int *HoaEncode_performVec(t_int *w);
t_int *HoaEncode_performOffsetVec(t_int *w);

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaEncode_perform64Offset(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaEncode_perform64vec(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaEncode_perform64Offsetvec(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *HoaEncode_class;
    

int C74_EXPORT main(void)
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

	if(class_findbyname(CLASS_NOBOX, gensym("hoa.loader")) == NULL)
	{
		if(postons == 0)
		{
			hoa_postcredits();
			postons = 1;
		}
	}
	return 0;
}

void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaEncode *x = NULL;
	int	order = 4;
	std::string mode = "basic";
    x = (t_HoaEncode *)object_alloc(HoaEncode_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		if(atom_gettype(argv + 1) == A_SYM)
			mode = atom_getsym(argv + 1)->s_name;
		
		x->f_ambiEncoder = new AmbisonicsEncoder(order, mode, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiEncoder->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiEncoder->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaEncode_float(t_HoaEncode *x, double f)
{
	x->f_ambiEncoder->setAzimuthBoth(f);
}

void HoaEncode_int(t_HoaEncode *x, long n)
{
	x->f_ambiEncoder->setAzimuthBoth(n);
}

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiEncoder->setVectorSize(maxvectorsize);
	x->f_inputNumber = x->f_ambiEncoder->getNumberOfInputs();
	if(x->f_ambiEncoder->getMode() == "split")
	{
		if(count[x->f_inputNumber - 1])
			object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64vec, 0, NULL);
		else
			object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64Offsetvec, 0, NULL);
	}
	else 
	{
		if(count[x->f_inputNumber - 1])
			object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64, 0, NULL);
		else
			object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64Offset, 0, NULL);
	}

}

void HoaEncode_perform64vec(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins, outs, ins[x->f_inputNumber-1]);
}

void HoaEncode_perform64Offsetvec(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins, outs);
}

void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins[0], outs, ins[1]);
}

void HoaEncode_perform64Offset(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins[0], outs);
}


void HoaEncode_dsp(t_HoaEncode *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ambiEncoder->setVectorSize(sp[0]->s_n);
	x->f_inputNumber = x->f_ambiEncoder->getNumberOfInputs();
	x->f_outputNumber = x->f_ambiEncoder->getNumberOfOutputs();
	if(x->f_ambiEncoder->getMode() == "split")
	{
		pointer_count = x->f_outputNumber + 2 + x->f_inputNumber;
		
		sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
		for(i = 0; i < pointer_count; i++)
			sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
		
		sigvec[0] = (t_int *)x;
		sigvec[1] = (t_int *)sp[0]->s_n;
		for(i = 2; i < pointer_count; i++)
			sigvec[i] = (t_int *)sp[i - 2]->s_vec;
		if(count[x->f_inputNumber-1])
			dsp_addv(HoaEncode_performVec, pointer_count, (void **)sigvec);
		else
			dsp_addv(HoaEncode_performOffsetVec, pointer_count, (void **)sigvec);
		
		free(sigvec);
	}
	else
	{
		pointer_count = x->f_outputNumber + 2 + x->f_inputNumber;
		
		sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
		for(i = 0; i < pointer_count; i++)
			sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
		
		sigvec[0] = (t_int *)x;
		sigvec[1] = (t_int *)sp[0]->s_n;
		for(i = 2; i < pointer_count; i++)
			sigvec[i] = (t_int *)sp[i - 2]->s_vec;
		if(count[x->f_inputNumber - 1])
			dsp_addv(HoaEncode_perform, pointer_count, (void **)sigvec);
		else
			dsp_addv(HoaEncode_performOffset, pointer_count, (void **)sigvec);
		
		free(sigvec);
	}
}

t_int *HoaEncode_perform(t_int *w)
{
	t_HoaEncode *x			= (t_HoaEncode *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiEncoder->process(ins[0], outs, ins[1]);

	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

t_int *HoaEncode_performOffset(t_int *w)
{
	t_HoaEncode *x			= (t_HoaEncode *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiEncoder->process(ins[0], outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}


t_int *HoaEncode_performVec(t_int *w)
{
	t_HoaEncode *x			= (t_HoaEncode *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiEncoder->process(ins, outs, ins[x->f_inputNumber-1]);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

t_int *HoaEncode_performOffsetVec(t_int *w)
{
	t_HoaEncode *x			= (t_HoaEncode *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;

	x->f_ambiEncoder->process(ins, outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s)
{
	
	if (m == ASSIST_INLET) 
	{
		if(x->f_ambiEncoder->getMode() == "split")
		{
			if(a < x->f_ambiEncoder->getOrder() + 1)
			{
				sprintf(s,"(Signal) Order %ld", a);
			}
			else 
				sprintf(s,"(Signal or float) Azimuth");
		}
		else
		{
			if(a == 0)
				sprintf(s,"(Signal) Input");
			else
				sprintf(s,"(Signal or float) Azimuth");
		}
	} 
	else 
	{
		sprintf(s,"(Signal) Harmonic %ld", x->f_ambiEncoder->getHarmonicIndex(a));
	}
}


void HoaEncode_free(t_HoaEncode *x) 
{
	dsp_free((t_pxobject *)x);
	delete(x->f_ambiEncoder);
}

