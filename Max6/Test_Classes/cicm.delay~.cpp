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

typedef struct _CicmDelay 
{
	t_pxobject				f_ob;			
	FilterDelay*            f_delay;

} t_CicmDelay;

void *CicmDelay_new(t_symbol *s, long argc, t_atom *argv);
void CicmDelay_free(t_CicmDelay *x);
void CicmDelay_assist(t_CicmDelay *x, void *b, long m, long a, char *s);
void CicmDelay_float(t_CicmDelay *x, double f);
void CicmDelay_int(t_CicmDelay *x, long n);

void CicmDelay_dsp(t_CicmDelay *x, t_signal **sp, short *count);
t_int *CicmDelay_perform(t_int *w);
t_int *CicmDelay_perform_offset(t_int *w);

void CicmDelay_dsp64(t_CicmDelay *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void CicmDelay_perform64(t_CicmDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void CicmDelay_perform64_offset(t_CicmDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void *CicmDelay_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("cicm.delay~", (method)CicmDelay_new, (method)dsp_free, (long)sizeof(t_CicmDelay), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)CicmDelay_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)CicmDelay_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)CicmDelay_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)CicmDelay_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)CicmDelay_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	CicmDelay_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *CicmDelay_new(t_symbol *s, long argc, t_atom *argv)
{
	t_CicmDelay *x = NULL;
	long delayMax = sys_getsr();
	x = (t_CicmDelay *)object_alloc((t_class*)CicmDelay_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			delayMax	= atom_getlong(argv);
			
		x->f_delay	= new FilterDelay(delayMax, sys_getmaxblksize(), sys_getsr());
		
		dsp_setup((t_pxobject *)x, 1);
        outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void CicmDelay_float(t_CicmDelay *x, double f)
{
	;
}

void CicmDelay_int(t_CicmDelay *x, long n)
{
	;
}

void CicmDelay_dsp64(t_CicmDelay *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_delay->setVectorSize(maxvectorsize);
	if(count[x->f_delay->getNumberOfInputs() - 1])
		object_method(dsp64, gensym("dsp_add64"), x, CicmDelay_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, CicmDelay_perform64_offset, 0, NULL);
}

void CicmDelay_perform64(t_CicmDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_delay->process(ins, outs, ins[numins - 1]);
}

void CicmDelay_perform64_offset(t_CicmDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{    
	x->f_delay->process(ins, outs);
}

void CicmDelay_assist(t_CicmDelay *x, void *b, long m, long a, char *s)
{
	if( a == x->f_delay->getNumberOfInputs() - 1)
		sprintf(s,"(Signal or delay) Widen value");
	else
		sprintf(s,"(Signal) %s", x->f_delay->getHarmonicsName(a).c_str());
}

void CicmDelay_free(t_CicmDelay *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_delay;
}

