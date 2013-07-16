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

typedef struct _HoaRotate 
{
	t_pxobject					f_ob;			
	AmbisonicsRotate			*f_ambiRotate;

} t_HoaRotate;

void *HoaRotate_new(t_symbol *s, long argc, t_atom *argv);
void HoaRotate_free(t_HoaRotate *x);
void HoaRotate_assist(t_HoaRotate *x, void *b, long m, long a, char *s);
void HoaRotate_float(t_HoaRotate *x, double f);
void HoaRotate_int(t_HoaRotate *x, long n);

void HoaRotate_dsp64(t_HoaRotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaRotate_perform64(t_HoaRotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaRotate_perform64Offset(t_HoaRotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* HoaRotate_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.rotate~", (method)HoaRotate_new, (method)HoaRotate_free, (long)sizeof(t_HoaRotate), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaRotate_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaRotate_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaRotate_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaRotate_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaRotate_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaRotate_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaRotate *x = NULL;
	int	order = 4;
    x = (t_HoaRotate *)object_alloc(HoaRotate_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_ambiRotate = new AmbisonicsRotate(order, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiRotate->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiRotate->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaRotate_float(t_HoaRotate *x, double f)
{
	x->f_ambiRotate->setAzimuth(f);
}

void HoaRotate_int(t_HoaRotate *x, long n)
{
	x->f_ambiRotate->setAzimuth(n);
}

void HoaRotate_dsp64(t_HoaRotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiRotate->setVectorSize(maxvectorsize);
	if(count[x->f_ambiRotate->getNumberOfInputs() - 1])
		object_method(dsp64, gensym("dsp_add64"), x, HoaRotate_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, HoaRotate_perform64Offset, 0, NULL);
}

void HoaRotate_perform64(t_HoaRotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiRotate->process(ins, outs, ins[x->f_ambiRotate->getNumberOfInputs() - 1]);
}

void HoaRotate_perform64Offset(t_HoaRotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiRotate->process(ins, outs);
}
								  
void HoaRotate_assist(t_HoaRotate *x, void *b, long m, long a, char *s)
{
	if (a != x->f_ambiRotate->getNumberOfInputs()-1 )
	{
		sprintf(s,"(Signal) %s", x->f_ambiRotate->getHarmonicsName(a).c_str());
	}
	else
		sprintf(s,"(Signal or float) Azimuth"); 	
}


void HoaRotate_free(t_HoaRotate *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_ambiRotate);
}

