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

typedef struct _CicmGrain 
{
	t_pxobject	f_ob;
	CicmQsgs*   f_grain;
    double      f_grain_time;
    
} t_CicmGrain;

void *CicmGrain_new(t_symbol *s, long argc, t_atom *argv);
void CicmGrain_free(t_CicmGrain *x);
void CicmGrain_assist(t_CicmGrain *x, void *b, long m, long a, char *s);
void CicmGrain_float(t_CicmGrain *x, double f);
void CicmGrain_int(t_CicmGrain *x, long n);

void CicmGrain_dsp64(t_CicmGrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void CicmGrain_perform64(t_CicmGrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void CicmGrain_perform64_offset(t_CicmGrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void *CicmGrain_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("cicm.grain~", (method)CicmGrain_new, (method)dsp_free, (long)sizeof(t_CicmGrain), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)CicmGrain_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)CicmGrain_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)CicmGrain_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)CicmGrain_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	CicmGrain_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *CicmGrain_new(t_symbol *s, long argc, t_atom *argv)
{
	t_CicmGrain *x = NULL;
	long delayMax = sys_getsr();
	x = (t_CicmGrain *)object_alloc((t_class*)CicmGrain_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			delayMax	= atom_getlong(argv);
			
		x->f_grain	= new CicmQsgs(sys_getmaxblksize(), sys_getsr());
		x->f_grain->setRarefaction(1.);
        
		dsp_setup((t_pxobject *)x, 2);
        outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void CicmGrain_float(t_CicmGrain *x, double f)
{
	;
}

void CicmGrain_int(t_CicmGrain *x, long n)
{
	;
}

void CicmGrain_dsp64(t_CicmGrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_grain->setVectorSize(maxvectorsize);
    x->f_grain->setSamplingRate(samplerate);
    
    object_method(dsp64, gensym("dsp_add64"), x, CicmGrain_perform64, 0, NULL);
}

void CicmGrain_perform64(t_CicmGrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for (int i = 0; i < sampleframes; i++)
    {
        outs[0][i] = x->f_grain->process(ins[0][i]);
    }
}

void CicmGrain_assist(t_CicmGrain *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET)
		sprintf(s,"(Signal or delay) Widen value");
	else
		sprintf(s,"(Signal) aa");
}

void CicmGrain_free(t_CicmGrain *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_grain;
}

