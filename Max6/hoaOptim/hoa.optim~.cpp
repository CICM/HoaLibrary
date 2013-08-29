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

#include "MaxOptim.h"

typedef struct _hoa_optim
{
	t_pxobject          f_ob;			
	AmbisonicOptim*		f_ambi_optim;
    MaxOptim*           f_ambi_max;
    
} t_hoa_optim;

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv);
void hoa_optim_free(t_hoa_optim *x);

void hoa_optim_dsp64(t_hoa_optim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_optim_perform64(t_hoa_optim *x, t_object *d, double **ins, long ni, double **outs, long no, long sf, long f, void *up);

t_class *hoa_optim_class;

int C74_EXPORT main(void)
{	
	t_class *c = class_new("hoa.optim~", (method)hoa_optim_new, (method)hoa_optim_free, (long)sizeof(t_hoa_optim), 0L, A_GIMME, 0);
	class_addmethod(c, (method)hoa_optim_dsp64,     "dsp64",	A_CANT, 0);    
    
    class_hoainit(c);
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	hoa_optim_class = c;
	
	return 0;
}

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_optim *x = (t_hoa_optim *)object_alloc(hoa_optim_class);
	if (x)
	{
        x->f_ambi_max   = new MaxOptim((t_hoa_object *)x, argc, argv);
		x->f_ambi_optim	= new AmbisonicOptim(x->f_ambi_max->getOrder(), x->f_ambi_max->getOptim(), sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambi_optim->getNumberOfInputs());
		for (int i = 0; i < x->f_ambi_optim->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void hoa_optim_dsp64(t_hoa_optim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_optim->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, hoa_optim_perform64, 0, NULL);
}

void hoa_optim_perform64(t_hoa_optim *x, t_object *d, double **ins, long ni, double **outs, long no, long sf, long f, void *up)
{
	x->f_ambi_optim->process(ins, outs);
}

void hoa_optim_free(t_hoa_optim *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambi_optim;
    delete x->f_ambi_max;
}

