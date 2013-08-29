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

#include "MaxWider.h"

typedef struct _hoa_wider 
{
	t_pxobject			f_ob;
	AmbisonicWider*		f_ambi_wider;
    MaxWider*           f_ambi_max;
    
} t_hoa_wider;

void *hoa_wider_new(t_symbol *s, long argc, t_atom *argv);
void hoa_wider_free(t_hoa_wider *x);
void hoa_wider_float(t_hoa_wider *x, double f);
void hoa_wider_int(t_hoa_wider *x, long n);

void hoa_wider_dsp64(t_hoa_wider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_wider_perform64(t_hoa_wider *x, t_object *d, double **ins, long ni, double **outs, long no, long sf, long f,void *up);
void hoa_wider_perform64_o(t_hoa_wider *x, t_object *d, double **ins, long ni, double **outs, long no, long sf, long f,void *up);

t_class* hoa_wider_class;

int C74_EXPORT main(void)
{	
	t_class *c = class_new("hoa.wider~", (method)hoa_wider_new, (method)hoa_wider_free, (long)sizeof(t_hoa_wider), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_wider_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_wider_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)hoa_wider_dsp64,		"dsp64",	A_CANT, 0);
	
    class_hoainit(c);
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	hoa_wider_class = c;

	return 0;
}

void *hoa_wider_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_wider *x = (t_hoa_wider *)object_alloc(hoa_wider_class);
	if (x)
	{
        x->f_ambi_max   = new MaxWider((t_hoa_object *)x, argc, argv);
		x->f_ambi_wider	= new AmbisonicWider(atom_getfloat(argv),  sys_getblksize());
        
		dsp_setup((t_pxobject *)x, x->f_ambi_wider->getNumberOfInputs());
		for (int i = 0; i < x->f_ambi_wider->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void hoa_wider_float(t_hoa_wider *x, double f)
{
	x->f_ambi_wider->setWidenValue(f);
}

void hoa_wider_int(t_hoa_wider *x, long n)
{
	x->f_ambi_wider->setWidenValue(n);
}

void hoa_wider_dsp64(t_hoa_wider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_wider->setVectorSize(maxvectorsize);
	if(count[x->f_ambi_wider->getNumberOfInputs() - 1])
		object_method(dsp64, gensym("dsp_add64"), x, hoa_wider_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, hoa_wider_perform64_o, 0, NULL);
}

void hoa_wider_perform64(t_hoa_wider *x, t_object *d, double **ins, long ni, double **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_wider->process(ins, outs, ins[ni - 1]);
}

void hoa_wider_perform64_o(t_hoa_wider *x, t_object *d, double **ins, long ni, double **outs, long no, long sf, long f,void *up)
{    
	x->f_ambi_wider->process(ins, outs);
}

void hoa_wider_free(t_hoa_wider *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambi_wider;
    delete x->f_ambi_max;
}

