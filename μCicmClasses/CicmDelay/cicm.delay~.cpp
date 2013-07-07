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
	CicmDecorrelation*      f_delay;
    double                  f_ramp_time;
    
} t_CicmDelay;

void *CicmDelay_new(t_symbol *s, long argc, t_atom *argv);
void CicmDelay_free(t_CicmDelay *x);
void CicmDelay_assist(t_CicmDelay *x, void *b, long m, long a, char *s);
void CicmDelay_float(t_CicmDelay *x, double f);
void CicmDelay_int(t_CicmDelay *x, long n);

t_max_err ramp_set(t_CicmDelay *x, t_object *attr, long argc, t_atom *argv);

void CicmDelay_dsp64(t_CicmDelay *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void CicmDelay_perform64(t_CicmDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* CicmDelay_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("cicm.delay~", (method)CicmDelay_new, (method)dsp_free, (long)sizeof(t_CicmDelay), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)CicmDelay_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)CicmDelay_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)CicmDelay_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)CicmDelay_assist,	"assist",	A_CANT, 0);
    
    CLASS_ATTR_DOUBLE			(c, "ramp", 0, t_CicmDelay, f_ramp_time);
	CLASS_ATTR_CATEGORY			(c, "ramp", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "ramp", 0, "Ramp time (ms)");
	CLASS_ATTR_ORDER			(c, "ramp", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "ramp", NULL, ramp_set);
	CLASS_ATTR_SAVE				(c, "ramp", 1);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	CicmDelay_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("cicm.grain~"));
	return 0;
}

void *CicmDelay_new(t_symbol *s, long argc, t_atom *argv)
{
	t_CicmDelay *x = NULL;
    t_dictionary *d = NULL;
    
	double delayMax = sys_getsr() * 5;
    double initialDelay = 0;
	x = (t_CicmDelay *)object_alloc(CicmDelay_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
			delayMax	= atom_getfloat(argv);
        if(atom_gettype(argv+1) == A_LONG || atom_gettype(argv+1) == A_FLOAT)
			initialDelay	= atom_getfloat(argv+1);
			
		x->f_delay	= new CicmDecorrelation(delayMax, sys_getmaxblksize(), sys_getsr());
		x->f_delay->setDelayTimeInMs(initialDelay);
        post("delay ms %f", x->f_delay->getDelayTimeInMs());
        x->f_ramp_time = x->f_delay->getRampInMs();
        post("%f", x->f_delay->getRampInMs());
		dsp_setup((t_pxobject *)x, 1);
        outlet_new(x, "signal");
		
        x->f_ob.z_misc = Z_NO_INPLACE;
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        attr_args_process(x, argc, argv);
        
	}
	return (x);
}

void CicmDelay_float(t_CicmDelay *x, double f)
{
    post("delay ms %f", x->f_delay->getDelayTimeInMs());
	x->f_delay->setDelayTimeInMs(f);
    post("delay ms %f", x->f_delay->getDelayTimeInMs());
}

void CicmDelay_int(t_CicmDelay *x, long n)
{
    post("delay sample %ld", x->f_delay->getDelayTimeInSample());
	x->f_delay->setDelayTimeInSample(n);
    post("delay sample %ld", x->f_delay->getDelayTimeInSample());
}

void CicmDelay_dsp64(t_CicmDelay *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_delay->setVectorSize(maxvectorsize);
    x->f_delay->setSamplingRate(samplerate);
    
    object_method(dsp64, gensym("dsp_add64"), x, CicmDelay_perform64, 0, NULL);
}

void CicmDelay_perform64(t_CicmDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_delay->process(ins[0], outs[0]);
}


void CicmDelay_assist(t_CicmDelay *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET)
		sprintf(s,"(Signal or message) Clean Signal");
	else
		sprintf(s,"(Signal) Delayed Signal");
}

void CicmDelay_free(t_CicmDelay *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_delay;
}

t_max_err ramp_set(t_CicmDelay *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_delay->setRampInMs(atom_getfloat(argv));
    post("%f", atom_getfloat(argv));
    post("%f", x->f_delay->getRampInMs());
	x->f_ramp_time = x->f_delay->getRampInMs();
	return MAX_ERR_NONE;
}





