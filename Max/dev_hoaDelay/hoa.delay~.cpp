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

typedef struct _HoaDelay
{
	t_pxobject			f_ob;			
	AmbisonicsDelay*	f_AmbiDelay;
    
    double              f_ramp_time;
    double              f_delay;
    double              f_diffuse_factor;
    long                f_encoding_compensation;
    
} t_HoaDelay;

void *HoaDelay_new(t_symbol *s, long argc, t_atom *argv);
void HoaDelay_free(t_HoaDelay *x);
void HoaDelay_assist(t_HoaDelay *x, void *b, long m, long a, char *s);
void HoaDelay_float(t_HoaDelay *x, double f);
void HoaDelay_int(t_HoaDelay *x, long n);

t_max_err ramp_set(t_HoaDelay *x, t_object *attr, long argc, t_atom *argv);
t_max_err delay_set(t_HoaDelay *x, t_object *attr, long argc, t_atom *argv);
t_max_err diff_set(t_HoaDelay *x, t_object *attr, long argc, t_atom *argv);
t_max_err comp_set(t_HoaDelay *x, t_object *attr, long argc, t_atom *argv);

void HoaDelay_dsp64(t_HoaDelay *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaDelay_perform64_no(t_HoaDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaDelay_perform64_post(t_HoaDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* HoaDelay_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("hoa.delay~", (method)HoaDelay_new, (method)dsp_free, (long)sizeof(t_HoaDelay), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaDelay_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaDelay_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaDelay_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaDelay_assist,		"assist",	A_CANT, 0);
    
    CLASS_ATTR_DOUBLE			(c, "ramp", 0, t_HoaDelay, f_ramp_time);
	CLASS_ATTR_CATEGORY			(c, "ramp", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "ramp", 0, "Ramp time (ms)");
	CLASS_ATTR_ORDER			(c, "ramp", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "ramp", NULL, ramp_set);
	CLASS_ATTR_SAVE				(c, "ramp", 1);
    
    CLASS_ATTR_LONG             (c, "compensation", 0, t_HoaDelay, f_encoding_compensation);
	CLASS_ATTR_CATEGORY			(c, "compensation", 0, "Behavior");
    CLASS_ATTR_STYLE_LABEL      (c, "compensation", 0, "onoff", "Encoding compensation")
	CLASS_ATTR_ORDER			(c, "compensation", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "compensation", NULL, comp_set);
	CLASS_ATTR_SAVE				(c, "compensation", 1);
    
    CLASS_ATTR_DOUBLE			(c, "delay", 0, t_HoaDelay, f_delay);
	CLASS_ATTR_CATEGORY			(c, "delay", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "delay", 0, "Delay time (ms)");
	CLASS_ATTR_ORDER			(c, "delay", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "delay", NULL, delay_set);
	CLASS_ATTR_SAVE				(c, "delay", 1);
    
    CLASS_ATTR_DOUBLE			(c, "diffusion", 0, t_HoaDelay, f_diffuse_factor);
	CLASS_ATTR_CATEGORY			(c, "diffusion", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "diffusion", 0, "Diffusion factor");
	CLASS_ATTR_ORDER			(c, "diffusion", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "diffusion", NULL, diff_set);
	CLASS_ATTR_SAVE				(c, "diffusion", 1);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaDelay_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaDelay_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaDelay *x = NULL;
    t_dictionary *d = NULL;
    
	int order = 4;
    bool mode = 1;
    double maxdelay = 5000.;
	x = (t_HoaDelay *)object_alloc(HoaDelay_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
        if(atom_gettype(argv+1) == A_SYM && atom_getsym(argv+1) == gensym("no"))
            mode = 0;
        if(atom_gettype(argv+2) == A_LONG || atom_gettype(argv+2) == A_FLOAT)
            maxdelay = atom_getfloat(argv+2);
			
		x->f_AmbiDelay	= new AmbisonicsDelay(order, mode, maxdelay, sys_getblksize(), sys_getsr());
		
		dsp_setup((t_pxobject *)x, x->f_AmbiDelay->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbiDelay->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
        
		x->f_ramp_time = x->f_AmbiDelay->getRampInMs();
        x->f_diffuse_factor = x->f_AmbiDelay->getDiffuseFactor();
        x->f_encoding_compensation = x->f_AmbiDelay->getEncodingCompensation();
        x->f_delay = x->f_AmbiDelay->getDelayTimeInMs();
        
        if(x->f_AmbiDelay->getMode() == Hoa_No_Encoding)
        {
            object_attr_setdisabled((t_object*)x, gensym("diffusion"), 1);
            object_attr_setdisabled((t_object*)x, gensym("compensation"), 1);
        }
        
        x->f_ob.z_misc = Z_NO_INPLACE;
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        attr_args_process(x, argc, argv);
	}
	return (x);
}

void HoaDelay_float(t_HoaDelay *x, double f)
{
    t_atom av[1];
    atom_setfloat(av, f);
	object_method(x, gensym("delay"), 1, av);
}

void HoaDelay_int(t_HoaDelay *x, long n)
{
	t_atom av[1];
    atom_setlong(av, n);
	object_method(x, gensym("delay"), 1, av);
}

void HoaDelay_dsp64(t_HoaDelay *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbiDelay->setVectorSize(maxvectorsize);
    x->f_AmbiDelay->setSamplingRate(samplerate);
    if(x->f_AmbiDelay->getMode() == Hoa_No_Encoding)
        object_method(dsp64, gensym("dsp_add64"), x, HoaDelay_perform64_no, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, HoaDelay_perform64_post, 0, NULL);
        
}

void HoaDelay_perform64_no(t_HoaDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbiDelay->process(ins[0], outs);
}

void HoaDelay_perform64_post(t_HoaDelay *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbiDelay->process(ins, outs);
}

void HoaDelay_assist(t_HoaDelay *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET && a == 0)
		sprintf(s,"(Signal, float or int) %s and delay", x->f_AmbiDelay->getHarmonicsName(a).c_str());
	else
		sprintf(s,"(Signal) %s", x->f_AmbiDelay->getHarmonicsName(a).c_str());
}

void HoaDelay_free(t_HoaDelay *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_AmbiDelay;
}

t_max_err ramp_set(t_HoaDelay *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiDelay->setRampInMs(atom_getfloat(argv));

	x->f_ramp_time = x->f_AmbiDelay->getRampInMs();
	return MAX_ERR_NONE;
}

t_max_err diff_set(t_HoaDelay *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiDelay->setDiffuseFactor(atom_getfloat(argv));
 
	x->f_diffuse_factor = x->f_AmbiDelay->getDiffuseFactor();
	return MAX_ERR_NONE;
}


t_max_err comp_set(t_HoaDelay *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiDelay->setEncodingCompensation(atom_getfloat(argv));
    
	x->f_encoding_compensation = x->f_AmbiDelay->getEncodingCompensation();
	return MAX_ERR_NONE;
}

t_max_err delay_set(t_HoaDelay *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG)
		x->f_AmbiDelay->setDelayTimeInSample(atom_getlong(argv));
    else if(atom_gettype(argv) == A_FLOAT)
        x->f_AmbiDelay->setDelayTimeInMs(atom_getfloat(argv));
    
	x->f_delay = x->f_AmbiDelay->getDelayTimeInMs();
	return MAX_ERR_NONE;
}






