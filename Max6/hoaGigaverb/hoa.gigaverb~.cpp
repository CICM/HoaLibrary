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

extern "C" 
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
	#include "buffer.h"
	#include "ext_globalsymbol.h"
}

#include "../../Sources/HoaLibrary.h"

typedef struct _gigaverb
{
	t_pxobject          f_ob;	
	AmbisonicsGigaverb	*f_gigaverb;
	float			f_size;
	float			f_damp;
	float			f_time;
	float			f_bandwidth;
	float			f_earlygain;
	float			f_tailgain;
    float           f_wet;
    float           f_dry;
} t_gigaverb ;

void *gigaverb_new(t_symbol *s, long argc, t_atom *argv);
void gigaverb_free(t_gigaverb *x);
void gigaverb_assist(t_gigaverb *x, void *b, long m, long a, char *s);

t_max_err size_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err damp_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err reverb_time_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err imput_bandwidth_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err early_gain_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err tail_gain_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err dry_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err wet_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv);

void gigaverb_dsp(t_gigaverb *x, t_signal **sp, short *count);
t_int *gigaverb_perform(t_int *w);

void gigaverb_dsp64(t_gigaverb *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void gigaverb_perform64(t_gigaverb *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *gigaverb_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("hoa.gigaverb~", (method)gigaverb_new, (method)gigaverb_free, (long)sizeof(t_gigaverb ), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)gigaverb_dsp,		"dsp",			A_CANT, 0);
	class_addmethod(c, (method)gigaverb_dsp64,		"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)gigaverb_assist,		"assist",		A_CANT, 0);
    
    CLASS_ATTR_FLOAT			(c, "size", 0, t_gigaverb, f_size);
	CLASS_ATTR_CATEGORY			(c, "size", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "size", 0, "Room size");
	CLASS_ATTR_ORDER			(c, "size", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "size", NULL, size_set);
	CLASS_ATTR_DEFAULT			(c, "size", 0, "50.");
	CLASS_ATTR_SAVE				(c, "size", 1);
    
	CLASS_ATTR_FLOAT			(c, "damp", 0, t_gigaverb, f_damp);
	CLASS_ATTR_CATEGORY			(c, "damp", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "damp", 0, "Damping value");
	CLASS_ATTR_ORDER			(c, "damp", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "damp", NULL, damp_set);
	CLASS_ATTR_DEFAULT			(c, "damp", 0, "0.5");
	CLASS_ATTR_FILTER_MIN		(c, "damp", 0);
	CLASS_ATTR_SAVE				(c, "damp", 1);
	
	CLASS_ATTR_FLOAT			(c, "time", 0, t_gigaverb, f_time);
	CLASS_ATTR_CATEGORY			(c, "time", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "time", 0, "Reverberation time");
	CLASS_ATTR_ORDER			(c, "time", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "time", NULL, reverb_time_set);
	CLASS_ATTR_DEFAULT			(c, "time", 0, "7.");
	CLASS_ATTR_FILTER_MIN		(c, "time", 0);
	CLASS_ATTR_SAVE				(c, "time", 1);
    
	CLASS_ATTR_FLOAT			(c, "bandwidth", 0, t_gigaverb, f_bandwidth);
	CLASS_ATTR_CATEGORY			(c, "bandwidth", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "bandwidth", 0, "Input bandwidth");
	CLASS_ATTR_ORDER			(c, "bandwidth", 0, "4");
	CLASS_ATTR_ACCESSORS		(c, "bandwidth", NULL, imput_bandwidth_set);
	CLASS_ATTR_DEFAULT			(c, "bandwidth", 0, "0.5");
	CLASS_ATTR_FILTER_MIN		(c, "bandwidth", 0);
	CLASS_ATTR_SAVE				(c, "bandwidth", 1);
    
	CLASS_ATTR_FLOAT			(c, "egain", 0, t_gigaverb, f_earlygain);
	CLASS_ATTR_CATEGORY			(c, "egain", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "egain", 0, "Early gain");
	CLASS_ATTR_ORDER			(c, "egain", 0, "5");
	CLASS_ATTR_ACCESSORS		(c, "egain", NULL, early_gain_set);
	CLASS_ATTR_DEFAULT			(c, "egain", 0, "1.");
	CLASS_ATTR_FILTER_MIN		(c, "egain", 0);
	CLASS_ATTR_SAVE				(c, "egain", 1);
    
	CLASS_ATTR_FLOAT			(c, "tgain", 0, t_gigaverb, f_tailgain);
	CLASS_ATTR_CATEGORY			(c, "tgain", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "tgain", 0, "Tail gain");
	CLASS_ATTR_ORDER			(c, "tgain", 0, "6");
	CLASS_ATTR_ACCESSORS		(c, "tgain", NULL, tail_gain_set);
	CLASS_ATTR_DEFAULT			(c, "tgain", 0, "1.");
	CLASS_ATTR_FILTER_MIN		(c, "tgain", 0);
	CLASS_ATTR_SAVE				(c, "tgain", 1);
    
    CLASS_ATTR_FLOAT			(c, "dry", 0, t_gigaverb, f_dry);
	CLASS_ATTR_CATEGORY			(c, "dry", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "dry", 0, "Dry value");
	CLASS_ATTR_ORDER			(c, "dry", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "dry", NULL, dry_set);
	CLASS_ATTR_DEFAULT			(c, "dry", 0, "0.");
	CLASS_ATTR_FILTER_MIN		(c, "dry", 0);
	CLASS_ATTR_SAVE				(c, "dry", 1);
    
    CLASS_ATTR_FLOAT			(c, "wet", 0, t_gigaverb, f_wet);
	CLASS_ATTR_CATEGORY			(c, "wet", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "wet", 0, "Wet value");
	CLASS_ATTR_ORDER			(c, "wet", 0, "4");
	CLASS_ATTR_ACCESSORS		(c, "wet", NULL, wet_set);
	CLASS_ATTR_DEFAULT			(c, "wet", 0, "1.");
	CLASS_ATTR_FILTER_MIN		(c, "wet", 0);
	CLASS_ATTR_SAVE				(c, "wet", 1);
    
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	gigaverb_class = c;
    
    class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	
	return 0;
}

void *gigaverb_new(t_symbol *s, long argc, t_atom *argv)
{
	t_gigaverb *x = NULL;
	int anOrder = 4;
    x = ((t_gigaverb *)object_alloc(gigaverb_class));
	if (x)
	{	
		if(atom_gettype(argv) == A_LONG)
			anOrder = atom_getlong(argv);

		x->f_gigaverb = new AmbisonicsGigaverb(anOrder, sys_getmaxblksize(), sys_getsr());
		x->f_gigaverb->setRoomSize(50.);
        x->f_gigaverb->setDamping(0.5);
        x->f_gigaverb->setDryValue(0.);
        x->f_gigaverb->setWetValue(1.);
        x->f_gigaverb->setTailLevel(1);
        x->f_gigaverb->setReverberationTime(7.);
        x->f_gigaverb->setInputBandwidth(0.5);
        x->f_gigaverb->setEarlyLevel(1.);
        
		object_method(x, gensym("size"), NULL, NULL);
        object_method(x, gensym("damp"), NULL, NULL);
        object_method(x, gensym("time"), NULL, NULL);
        object_method(x, gensym("bandwidth"), NULL, NULL);
        object_method(x, gensym("egain"), NULL, NULL);
        object_method(x, gensym("tgain"), NULL, NULL);
        object_method(x, gensym("dry"), NULL, NULL);
        object_method(x, gensym("wet"), NULL, NULL);
        object_method(x, gensym("fspread"), NULL, NULL);
        object_method(x, gensym("lspread"), NULL, NULL);
        
		dsp_setup((t_pxobject *)x, x->f_gigaverb->getNumberOfInputs());
		for (int i = 0; i < x->f_gigaverb->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		attr_args_process(x, argc, argv);
	}
	return (x);
}

void gigaverb_dsp(t_gigaverb *x, t_signal **sp, short *count)
{
	x->f_gigaverb->setVectorSize(sp[0]->s_n);
    x->f_gigaverb->setSamplingRate(sp[0]->s_sr);
	dsp_add(gigaverb_perform, 3, x, sp[0]->s_vec, sp[1]->s_vec);
}

t_int *gigaverb_perform(t_int *w)
{
	t_gigaverb*	x	= (t_gigaverb *)(w[1]);
	float**		ins	= (float **)(w+2);
	float**		outs= (float **)(w+3);

	x->f_gigaverb->process(ins, outs);

	return (w + 4);
}

void gigaverb_dsp64(t_gigaverb *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_gigaverb->setVectorSize(maxvectorsize);
    x->f_gigaverb->setSamplingRate(samplerate);
	object_method(dsp64, gensym("dsp_add64"), x, gigaverb_perform64, 0, NULL);
}

void gigaverb_perform64(t_gigaverb *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_gigaverb->process(ins, outs);
}

void gigaverb_assist(t_gigaverb *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_gigaverb->getHarmonicsName(a).c_str());
}

void gigaverb_free(t_gigaverb *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_gigaverb;
}

t_max_err size_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_gigaverb->setRoomSize(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_gigaverb->setRoomSize(atom_getfloat(argv));
    
	x->f_size = x->f_gigaverb->getRoomSize();
	return 0;
}

t_max_err damp_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_gigaverb->setDamping(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_gigaverb->setDamping(atom_getfloat(argv));
    
	x->f_damp = x->f_gigaverb->getDamping();
	return 0;
}

t_max_err reverb_time_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_gigaverb->setReverberationTime(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_gigaverb->setReverberationTime(atom_getfloat(argv));
    
	x->f_time = x->f_gigaverb->getReverberationTime();
	return 0;
}

t_max_err imput_bandwidth_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_gigaverb->setInputBandwidth(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_gigaverb->setInputBandwidth(atom_getfloat(argv));
    
	x->f_bandwidth= x->f_gigaverb->getInputBandwidth();
	return 0;
}

t_max_err early_gain_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_gigaverb->setEarlyLevel(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_gigaverb->setEarlyLevel(atom_getfloat(argv));
    
	x->f_earlygain = x->f_gigaverb->getEarlyLevel();
	return 0;
}

t_max_err tail_gain_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_gigaverb->setTailLevel(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_gigaverb->setTailLevel(atom_getfloat(argv));
    
	x->f_tailgain= x->f_gigaverb->getTailLevel();
	return 0;
}

t_max_err dry_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_gigaverb->setDryValue(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_gigaverb->setDryValue(atom_getfloat(argv));
    
	x->f_dry = x->f_gigaverb->getDryValue();
	return 0;
}

t_max_err wet_set(t_gigaverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_gigaverb->setWetValue(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_gigaverb->setWetValue(atom_getfloat(argv));
    
	x->f_wet = x->f_gigaverb->getWetValue();
	return 0;
}