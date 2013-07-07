/**
 * CicmLibrary : A Set Of Useful Tools For Signal Processing
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

#include "../../Sources/CicmLibrary/CicmLibrary.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}

typedef struct _CicmRingMod 
{
	t_pxobject				f_ob;			
	CicmRingModulation*     f_ring_mod;
    
} t_CicmRingMod;

void *CicmRingMod_new(t_symbol *s, long argc, t_atom *argv);
void CicmRingMod_free(t_CicmRingMod *x);
void CicmRingMod_assist(t_CicmRingMod *x, void *b, long m, long a, char *s);
void CicmRingMod_float(t_CicmRingMod *x, double f);
void CicmRingMod_int(t_CicmRingMod *x, long n);

t_max_err ramp_set(t_CicmRingMod *x, t_object *attr, long argc, t_atom *argv);

void CicmRingMod_dsp64(t_CicmRingMod *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void CicmRingMod_perform64(t_CicmRingMod *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* CicmRingMod_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("cicm.ringmod~", (method)CicmRingMod_new, (method)dsp_free, (long)sizeof(t_CicmRingMod), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)CicmRingMod_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)CicmRingMod_int,         "int",		A_LONG, 0);
	class_addmethod(c, (method)CicmRingMod_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)CicmRingMod_assist,      "assist",	A_CANT, 0);

	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	CicmRingMod_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("cicm.grain~"));
	return 0;
}

void *CicmRingMod_new(t_symbol *s, long argc, t_atom *argv)
{
	t_CicmRingMod *x = NULL;
    t_dictionary *d = NULL;
    
	double frequency = 1.;
    double amplitude = 1.;
	x = (t_CicmRingMod *)object_alloc(CicmRingMod_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
			frequency	= atom_getfloat(argv);
        if(atom_gettype(argv+1) == A_LONG || atom_gettype(argv+1) == A_FLOAT)
			amplitude	= atom_getfloat(argv+1);
			
		x->f_ring_mod	= new CicmRingModulation(sys_getmaxblksize(), sys_getsr());
		x->f_ring_mod->setFrequency(frequency);
 
		dsp_setup((t_pxobject *)x, 1);
        outlet_new(x, "signal");
		
        x->f_ob.z_misc = Z_NO_INPLACE;
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        attr_args_process(x, argc, argv);
        
	}
	return (x);
}

void CicmRingMod_float(t_CicmRingMod *x, double f)
{
	x->f_ring_mod->setFrequency(f);
}

void CicmRingMod_int(t_CicmRingMod *x, long n)
{
	x->f_ring_mod->setFrequency(n);
}

void CicmRingMod_dsp64(t_CicmRingMod *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ring_mod->setVectorSize(maxvectorsize);
    x->f_ring_mod->setSamplingRate(samplerate);
    
    object_method(dsp64, gensym("dsp_add64"), x, CicmRingMod_perform64, 0, NULL);
}

void CicmRingMod_perform64(t_CicmRingMod *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_ring_mod->process(ins[0], outs[0]);
}


void CicmRingMod_assist(t_CicmRingMod *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET)
		sprintf(s,"(Signal or message) Clean Signal");
	else
		sprintf(s,"(Signal) Modulated Signal");
}

void CicmRingMod_free(t_CicmRingMod *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ring_mod;
}





