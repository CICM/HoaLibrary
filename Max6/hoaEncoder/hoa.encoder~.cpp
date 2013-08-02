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
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
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

int postons = 0;

typedef struct _HoaEncode 
{
	t_pxobject					f_ob;			
	AmbisonicEncoder			*f_ambiEncoder;
} t_HoaEncode;


void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv);
void HoaEncode_free(t_HoaEncode *x);
void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s);

void HoaEncode_float(t_HoaEncode *x, double f);
void HoaEncode_int(t_HoaEncode *x, long n);

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
	class_addmethod(c, (method)HoaEncode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaEncode_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	HoaEncode_class = c;
    
    if (!postons)
    {
        post("hoa.library (version 1.3) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
        post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
        postons = 1;
    }

	return 0;
}

void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaEncode *x = NULL;
	int	order = 4;
	int mode = Hoa_Basic;
    x = (t_HoaEncode *)object_alloc(HoaEncode_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		if(atom_gettype(argv + 1) == A_SYM && atom_getsym(argv + 1) == gensym("split"))
			mode = Hoa_Split;
		
		x->f_ambiEncoder = new AmbisonicEncoder(order, mode, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiEncoder->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiEncoder->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}

	return (x);
}

void HoaEncode_float(t_HoaEncode *x, double f)
{
	x->f_ambiEncoder->setAngle(f);
}

void HoaEncode_int(t_HoaEncode *x, long n)
{
	x->f_ambiEncoder->setAngle(n);
}

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiEncoder->setVectorSize(maxvectorsize);
	x->f_ambiEncoder->setSamplingRate(samplerate);
    
	if(x->f_ambiEncoder->getMode() == Hoa_Split)
	{
		if(count[x->f_ambiEncoder->getNumberOfInputs() - 1])
			object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64vec, 0, NULL);
		else
			object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64Offsetvec, 0, NULL);
	}
	else 
	{
		if(count[x->f_ambiEncoder->getNumberOfInputs() - 1])
			object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64, 0, NULL);
		else
			object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64Offset, 0, NULL);
	}

}

void HoaEncode_perform64vec(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->processSplit(ins, outs, ins[x->f_ambiEncoder->getNumberOfInputs()-1]);
}

void HoaEncode_perform64Offsetvec(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->processSplit(ins, outs);
}

void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins[0], outs, ins[1]);
}

void HoaEncode_perform64Offset(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins[0], outs);
}

void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s)
{
	
	if (m == ASSIST_INLET) 
	{
		if(x->f_ambiEncoder->getMode() == Hoa_Split)
		{
			if(a < x->f_ambiEncoder->getOrder() + 1)
			{
				sprintf(s,"(Signal) Order %ld", a);
			}
			else 
				sprintf(s,"(Signal or float) Angle");
		}
		else
		{
			if(a == 0)
				sprintf(s,"(Signal) Input");
			else
				sprintf(s,"(Signal or float) Angle");
		}
	} 
	else 
	{
		sprintf(s,"(Signal) %s", x->f_ambiEncoder->getHarmonicsName(a).c_str());
	}
}


void HoaEncode_free(t_HoaEncode *x) 
{
	dsp_free((t_pxobject *)x);
	delete(x->f_ambiEncoder);
}

