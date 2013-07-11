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

typedef struct _HoaRingMod
{
	t_pxobject			f_ob;			
	AmbisonicsRingModulation*	f_AmbiRingMod;
    
    double              f_frequency;
    double              f_diffuse_factor;
    long                f_encoding_compensation;
    
} t_HoaRingMod;

void *HoaRingMod_new(t_symbol *s, long argc, t_atom *argv);
void HoaRingMod_free(t_HoaRingMod *x);
void HoaRingMod_assist(t_HoaRingMod *x, void *b, long m, long a, char *s);
void HoaRingMod_float(t_HoaRingMod *x, double f);
void HoaRingMod_int(t_HoaRingMod *x, long n);

t_max_err freq_set(t_HoaRingMod *x, t_object *attr, long argc, t_atom *argv);
t_max_err diff_set(t_HoaRingMod *x, t_object *attr, long argc, t_atom *argv);
t_max_err comp_set(t_HoaRingMod *x, t_object *attr, long argc, t_atom *argv);

void HoaRingMod_dsp64(t_HoaRingMod *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaRingMod_perform64_no(t_HoaRingMod *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaRingMod_perform64_post(t_HoaRingMod *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* HoaRingMod_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("hoa.ringmod~", (method)HoaRingMod_new, (method)dsp_free, (long)sizeof(t_HoaRingMod), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaRingMod_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaRingMod_int,          "int",		A_LONG, 0);
	class_addmethod(c, (method)HoaRingMod_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaRingMod_assist,		"assist",	A_CANT, 0);
    
    CLASS_ATTR_LONG             (c, "compensation", 0, t_HoaRingMod, f_encoding_compensation);
	CLASS_ATTR_CATEGORY			(c, "compensation", 0, "Behavior");
    CLASS_ATTR_STYLE_LABEL      (c, "compensation", 0, "onoff", "Encoding compensation")
	CLASS_ATTR_ORDER			(c, "compensation", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "compensation", NULL, comp_set);
	CLASS_ATTR_SAVE				(c, "compensation", 1);
    
    CLASS_ATTR_DOUBLE			(c, "frequency", 0, t_HoaRingMod, f_frequency);
	CLASS_ATTR_CATEGORY			(c, "frequency", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "frequency", 0, "Frequency (Hz)");
	CLASS_ATTR_ORDER			(c, "frequency", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "frequency", NULL, freq_set);
	CLASS_ATTR_SAVE				(c, "frequency", 1);
    
    CLASS_ATTR_DOUBLE			(c, "diffusion", 0, t_HoaRingMod, f_diffuse_factor);
	CLASS_ATTR_CATEGORY			(c, "diffusion", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "diffusion", 0, "Diffusion factor");
	CLASS_ATTR_ORDER			(c, "diffusion", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "diffusion", NULL, diff_set);
	CLASS_ATTR_SAVE				(c, "diffusion", 1);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaRingMod_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaRingMod_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaRingMod *x = NULL;
    t_dictionary *d = NULL;
    
	int order = 4;
    bool mode = 1;
	x = (t_HoaRingMod *)object_alloc(HoaRingMod_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
        if(atom_gettype(argv+1) == A_SYM && atom_getsym(argv+1) == gensym("no"))
            mode = 0;
			
		x->f_AmbiRingMod	= new AmbisonicsRingModulation(order, mode, sys_getblksize(), sys_getsr());
		
		dsp_setup((t_pxobject *)x, x->f_AmbiRingMod->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbiRingMod->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
        
        x->f_diffuse_factor = x->f_AmbiRingMod->getDiffuseFactor();
        x->f_encoding_compensation = x->f_AmbiRingMod->getEncodingCompensation();
        x->f_frequency = x->f_AmbiRingMod->getFrequency();
        
        if(x->f_AmbiRingMod->getMode() == Hoa_No_Encoding)
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

void HoaRingMod_float(t_HoaRingMod *x, double f)
{
    t_atom av[1];
    atom_setfloat(av, f);
	object_method(x, gensym("frequency"), 1, av);
}

void HoaRingMod_int(t_HoaRingMod *x, long n)
{
	t_atom av[1];
    atom_setlong(av, n);
	object_method(x, gensym("frequency"), 1, av);
}

void HoaRingMod_dsp64(t_HoaRingMod *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbiRingMod->setVectorSize(maxvectorsize);
    x->f_AmbiRingMod->setSamplingRate(samplerate);
    if(x->f_AmbiRingMod->getMode() == Hoa_No_Encoding)
        object_method(dsp64, gensym("dsp_add64"), x, HoaRingMod_perform64_no, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, HoaRingMod_perform64_post, 0, NULL);
        
}

void HoaRingMod_perform64_no(t_HoaRingMod *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbiRingMod->process(ins[0], outs);
}

void HoaRingMod_perform64_post(t_HoaRingMod *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbiRingMod->process(ins, outs);
}

void HoaRingMod_assist(t_HoaRingMod *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET && a == 0)
		sprintf(s,"(Signal, float or int) %s and frequency", x->f_AmbiRingMod->getHarmonicsName(a).c_str());
	else
		sprintf(s,"(Signal) %s", x->f_AmbiRingMod->getHarmonicsName(a).c_str());
}

void HoaRingMod_free(t_HoaRingMod *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_AmbiRingMod;
}

t_max_err diff_set(t_HoaRingMod *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiRingMod->setDiffuseFactor(atom_getfloat(argv));
 
	x->f_diffuse_factor = x->f_AmbiRingMod->getDiffuseFactor();
	return MAX_ERR_NONE;
}

t_max_err comp_set(t_HoaRingMod *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiRingMod->setEncodingCompensation(atom_getfloat(argv));
    
	x->f_encoding_compensation = x->f_AmbiRingMod->getEncodingCompensation();
	return MAX_ERR_NONE;
}

t_max_err freq_set(t_HoaRingMod *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiRingMod->setFrequency(atom_getfloat(argv));
    
	x->f_frequency = x->f_AmbiRingMod->getFrequency();
	return MAX_ERR_NONE;
}






