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

typedef struct _HoaWider 
{
	t_pxobject			f_ob;			
	AmbisonicWider*		f_AmbisonicWider;

} t_HoaWider;

void *HoaWider_new(t_symbol *s, long argc, t_atom *argv);
void HoaWider_free(t_HoaWider *x);
void HoaWider_assist(t_HoaWider *x, void *b, long m, long a, char *s);
void HoaWider_float(t_HoaWider *x, double f);
void HoaWider_int(t_HoaWider *x, long n);

void HoaWider_dsp64(t_HoaWider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaWider_perform64(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaWider_perform64_offset(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void *HoaWider_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.wider~", (method)HoaWider_new, (method)dsp_free, (long)sizeof(t_HoaWider), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaWider_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaWider_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaWider_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaWider_assist,		"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaWider_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaWider_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaWider *x = NULL;
	int order = 4;
	x = (t_HoaWider *)object_alloc((t_class*)HoaWider_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
			
		x->f_AmbisonicWider	= new AmbisonicWider(order,  sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicWider->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicWider->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaWider_float(t_HoaWider *x, double f)
{
	x->f_AmbisonicWider->setWidenValue(f);
}

void HoaWider_int(t_HoaWider *x, long n)
{
	x->f_AmbisonicWider->setWidenValue(n);
}

void HoaWider_dsp64(t_HoaWider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicWider->setVectorSize(maxvectorsize);
	if(count[x->f_AmbisonicWider->getNumberOfInputs() - 1])
		object_method(dsp64, gensym("dsp_add64"), x, HoaWider_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, HoaWider_perform64_offset, 0, NULL);
}

void HoaWider_perform64(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicWider->process(ins, outs, ins[numins - 1]);
}

void HoaWider_perform64_offset(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{    
	x->f_AmbisonicWider->process(ins, outs);
}

void HoaWider_assist(t_HoaWider *x, void *b, long m, long a, char *s)
{
	if( a == x->f_AmbisonicWider->getNumberOfInputs() - 1)
		sprintf(s,"(Signal or float) Widen value");
	else
		sprintf(s,"(Signal) %s", x->f_AmbisonicWider->getHarmonicsName(a).c_str());
}

void HoaWider_free(t_HoaWider *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_AmbisonicWider;
}

