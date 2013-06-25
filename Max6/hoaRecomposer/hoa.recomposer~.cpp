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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicsRecomposer.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}

typedef struct _HoaRecomposer 
{
	t_pxobject					f_ob;			
	AmbisonicsRecomposer*       f_ambiRecomposer;

	long						f_inputNumber;
	long						f_outputNumber;
    t_atom_long                 f_mode;
    //t_symbol*                   f_mode;
    double                      f_ramp_time;
    short                       f_fisheyeSignal;
} t_HoaRecomposer;

void *HoaRecomposer_new(t_symbol *s, long argc, t_atom *argv);
void HoaRecomposer_free(t_HoaRecomposer *x);
void HoaRecomposer_assist(t_HoaRecomposer *x, void *b, long m, long a, char *s);
void HoaRecomposer_angle(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av);
void HoaRecomposer_wide(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av);
t_max_err HoaRecomposer_set_attr_mode(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv);
t_max_err HoaRecomposer_ramp(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv);
void HoaRecomposer_float(t_HoaRecomposer *x, double d);

t_max_err HoaRecomposer_notify(t_HoaRecomposer *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void HoaRecomposer_dsp(t_HoaRecomposer *x, t_signal **sp, short *count);
t_int *HoaRecomposer_perform(t_int *w);

void HoaRecomposer_dsp64(t_HoaRecomposer *x,t_object *dsp64,short *count, double samplerate, long maxvectorsize, long flags);
void HoaRecomposer_perform64(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaRecomposer_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.recomposer~", (method)HoaRecomposer_new, (method)HoaRecomposer_free, (long)sizeof(t_HoaRecomposer), 0L, A_GIMME, 0);
	;
	class_addmethod(c, (method)HoaRecomposer_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_angle,         "angle",    A_GIMME,0);
    class_addmethod(c, (method)HoaRecomposer_wide,          "wide",     A_GIMME,0);
    class_addmethod(c, (method)HoaRecomposer_float,         "float",    A_FLOAT,0);
    
    CLASS_ATTR_LONG             (c,"mode", 0, t_HoaRecomposer, f_mode);
	CLASS_ATTR_LABEL			(c,"mode", 0, "Mode");
    CLASS_ATTR_ENUMINDEX3       (c,"mode", 0, "fixe", "fisheye", "free");
	CLASS_ATTR_CATEGORY			(c,"mode", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"mode", NULL, HoaRecomposer_set_attr_mode);
    CLASS_ATTR_ORDER			(c,"mode", 0,  "1");
    
    CLASS_ATTR_DOUBLE			(c,"ramp", 0, t_HoaRecomposer, f_ramp_time);
	CLASS_ATTR_LABEL			(c,"ramp", 0, "Ramp Time (ms)");
	CLASS_ATTR_CATEGORY			(c,"ramp", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"ramp", NULL, HoaRecomposer_ramp);
    CLASS_ATTR_ORDER			(c,"ramp", 0,  "2");
    
    CLASS_ATTR_SAVE             (c,"mode", 1);
    CLASS_ATTR_SAVE             (c,"ramp", 1);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaRecomposer_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaRecomposer_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaRecomposer *x = NULL;
    t_dictionary *d;
	int order = 4, inputs = 10;
    x = (t_HoaRecomposer *)object_alloc((t_class*)HoaRecomposer_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			inputs	= atom_getlong(argv+1);
        
        /* Base Attributes */
        x->f_ramp_time = 20;
        x->f_mode = 0;
        
		x->f_ambiRecomposer	= new AmbisonicsRecomposer(order, inputs);
        
		dsp_setup((t_pxobject *)x, x->f_ambiRecomposer->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiRecomposer->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");

		x->f_ob.z_misc = Z_NO_INPLACE;
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        object_attr_setdisabled((t_object *)x, gensym("ramp"), (x->f_mode == 0) ? 1 : 0);
	}
	return (x);
}

void HoaRecomposer_angle(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if (x->f_mode != 1) // fisheye mode => angle setted by fisheye factor only
    {
        if(ac == 2 && atom_gettype(av) == A_LONG && atom_gettype(av+1) == A_FLOAT)
            x->f_ambiRecomposer->setMicrophoneAngle(atom_getlong(av), atom_getfloat(av+1));
        else if(atom_gettype(av) == A_FLOAT)
        {
            for(int i = 0; i < ac; i++)
            {
                if(i < x->f_ambiRecomposer->getNumberOfOutputs() && atom_gettype(av+i) == A_FLOAT)
                    x->f_ambiRecomposer->setMicrophoneAngle(i, atom_getfloat(av+i));
            }
        }
    }
}

void HoaRecomposer_wide(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2 && atom_gettype(av) == A_LONG && atom_gettype(av+1) == A_FLOAT)
        x->f_ambiRecomposer->setMicrophoneWide(atom_getlong(av), atom_getfloat(av+1));
    else if(atom_gettype(av) == A_FLOAT)
    {
        for(int i = 0; i < ac; i++)
        {
            if(i < x->f_ambiRecomposer->getNumberOfOutputs() && atom_gettype(av+i) == A_FLOAT)
                x->f_ambiRecomposer->setMicrophoneWide(i, atom_getfloat(av+i));
        }
    }
}

void HoaRecomposer_float(t_HoaRecomposer *x, double d)
{
    if (x->f_mode == 1)
        x->f_ambiRecomposer->setFishEyeFactor(d);
}

t_max_err HoaRecomposer_set_attr_mode(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        int dspState = sys_getdspobjdspstate((t_object*)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        long last_numberOfInputs = (x->f_mode == 1) ? x->f_ambiRecomposer->getNumberOfInputs()+1 : x->f_ambiRecomposer->getNumberOfInputs();
        int value = Tools::clip(long(atom_getfloat(argv)), long(0), long(2));
        x->f_ambiRecomposer->setMode(value);
        x->f_mode = x->f_ambiRecomposer->getMode();
        x->f_inputNumber = (x->f_mode == 1) ? x->f_ambiRecomposer->getNumberOfInputs()+1 : x->f_ambiRecomposer->getNumberOfInputs();
        if (last_numberOfInputs != x->f_inputNumber)
        {
            t_object *b = NULL;
            object_obex_lookup(x, _sym_pound_B, (t_object **)&b);
            object_method(b, gensym("dynlet_begin"));
            dsp_resize((t_pxobject*)x, x->f_inputNumber);
            object_method(b, gensym("dynlet_end"));
        }
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("start"));
        
        object_attr_setdisabled((t_object *)x, gensym("ramp"), (x->f_mode == 0) ? 1 : 0);
    }
    return MAX_ERR_NONE;
}

t_max_err HoaRecomposer_ramp(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_ambiRecomposer->setRamp(atom_getfloat(argv) * sys_getsr()  / 1000.);
        x->f_ramp_time = Tools::clip_min((float)atom_getfloat(argv), 0.f);
    }
    return MAX_ERR_NONE;
}

void HoaRecomposer_dsp64(t_HoaRecomposer *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiRecomposer->setVectorSize(maxvectorsize);
	x->f_inputNumber = (x->f_mode == 1) ? x->f_ambiRecomposer->getNumberOfInputs()+1 : x->f_ambiRecomposer->getNumberOfInputs();
	x->f_fisheyeSignal = (x->f_mode == 1) ? count[x->f_ambiRecomposer->getNumberOfInputs()] : 0;
    object_method(dsp64, gensym("dsp_add64"), x, HoaRecomposer_perform64, 0, NULL);
}

void HoaRecomposer_perform64(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    if (x->f_mode == 1 && x->f_fisheyeSignal)
        x->f_ambiRecomposer->process(ins, outs, ins[x->f_ambiRecomposer->getNumberOfInputs()]);
    else
        x->f_ambiRecomposer->process(ins, outs);
}

void HoaRecomposer_dsp(t_HoaRecomposer *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ambiRecomposer->setVectorSize(sp[0]->s_n);
	x->f_inputNumber = (x->f_mode == 1) ? x->f_ambiRecomposer->getNumberOfInputs()+1 : x->f_ambiRecomposer->getNumberOfInputs();
	x->f_outputNumber = x->f_ambiRecomposer->getNumberOfOutputs();
	pointer_count = x->f_inputNumber + x->f_outputNumber + 2;
    x->f_fisheyeSignal = (x->f_mode == 1) ? count[x->f_ambiRecomposer->getNumberOfInputs()] : 0;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
    dsp_addv(HoaRecomposer_perform, pointer_count, (void **)sigvec);
	free(sigvec);
}

t_int *HoaRecomposer_perform(t_int *w)
{
	t_HoaRecomposer *x		= (t_HoaRecomposer *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
    if (x->f_mode == 1 && x->f_fisheyeSignal)
        x->f_ambiRecomposer->process(ins, outs, ins[x->f_ambiRecomposer->getNumberOfInputs()]);
    else
        x->f_ambiRecomposer->process(ins, outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaRecomposer_assist(t_HoaRecomposer *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_INLET)
	{
        if ((x->f_mode == 1) && a == x->f_ambiRecomposer->getNumberOfInputs())
            sprintf(s,"(Signal/float) Fisheye factor (0-1)");
        else
            sprintf(s,"(Signal) Harmonic %ld", x->f_ambiRecomposer->getHarmonicIndex(a));
	}
	else 
	{
        sprintf(s,"(Signal) Virtual Microphone %ld", a);
	}
}

void HoaRecomposer_free(t_HoaRecomposer *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiRecomposer;
}

