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
#include "../m_pd.h"
}

typedef struct hoa_grain
{
    t_object            f_obj;
    AmbisonicsGrain*    f_ambisonics_grain;
    t_float             f;
    t_float**           f_inputs;
    t_float**           f_outputs;
    t_float**           f_outputs_real;
    
    int                 f_number_of_samples;
    t_float*            f_buffer;
    t_symbol*           f_buffer_name;
   
} hoa_grain;

void *hoa_grain_new(t_symbol *s, long argc, t_atom *argv);
void hoa_grain_free(hoa_grain *x);

void hoa_grain_size(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_delay(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_feed(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_rare(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_diff(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_comp(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_buffer_set(hoa_grain *x, t_symbol *s);

void hoa_grain_dsp(hoa_grain *x, t_signal **sp, short *count);
t_int *hoa_grain_perform_post(t_int *w);
t_int *hoa_grain_perform_no(t_int *w);

t_class *hoa_grain_class;

extern "C"
{
void setup_hoa0x2egrain_tilde(void)
{
    t_class *c;
    c = class_new(gensym("hoa.grain~"), (t_newmethod)hoa_grain_new,(t_method)hoa_grain_free, sizeof(hoa_grain), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)hoa_grain_dsp,     gensym("dsp"),          A_CANT,  0);
    class_addmethod(c, (t_method)hoa_grain_size,    gensym("size"),         A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_grain_delay,   gensym("delay"),        A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_grain_feed,    gensym("feedback"),     A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_grain_rare,    gensym("rarefaction"),  A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_grain_buffer_set,gensym("set"),        A_SYMBOL,0);
    
    hoa_grain_class = c;
    CLASS_MAINSIGNALIN(hoa_grain_class, hoa_grain, f);
}
}

void *hoa_grain_new(t_symbol *s, long argc, t_atom *argv)
{
	hoa_grain *x = NULL;
    int order = 4;
    bool mode = 1;
    
    x = (hoa_grain *)pd_new(hoa_grain_class);
	if (x)
	{
        x->f_buffer_name = NULL;
        x->f_number_of_samples = 0;

        order = atom_getint(argv);
        if(atom_getsymbol(argv+1) == gensym("no"))
            mode = 0;
        x->f_buffer_name = atom_getsymbol(argv+2);
        
		x->f_ambisonics_grain = new AmbisonicsGrain(order, mode, 5000., (long)sys_getblksize(), (long)sys_getsr());
        
        for (int i = 0; i < x->f_ambisonics_grain->getNumberOfInputs()-1; i++)
            inlet_new(&x->f_obj, &x->f_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->f_ambisonics_grain->getNumberOfOutputs(); i++)
			outlet_new(&x->f_obj, &s_signal);
        
        x->f_outputs        = new float*[x->f_ambisonics_grain->getNumberOfOutputs()];
        x->f_outputs_real   = new float*[x->f_ambisonics_grain->getNumberOfOutputs()];
        x->f_inputs         = new float*[x->f_ambisonics_grain->getNumberOfInputs()];
        for(int i = 0; i < x->f_ambisonics_grain->getNumberOfOutputs(); i++)
            x->f_outputs[i] = new float[8192];
	}
	return (x);
}

void hoa_grain_dsp(hoa_grain *x, t_signal **sp, short *count)
{
	x->f_ambisonics_grain->setVectorSize((int)sp[0]->s_n);
    x->f_ambisonics_grain->setSamplingRate((int)44100);
    
    hoa_grain_buffer_set(x, x->f_buffer_name);
    for(int i = 0; i < x->f_ambisonics_grain->getNumberOfInputs(); i++)
        x->f_inputs[i] = sp[i]->s_vec;
    for(int i = 0; i < x->f_ambisonics_grain->getNumberOfOutputs(); i++)
        x->f_outputs_real[i] = sp[i+x->f_ambisonics_grain->getNumberOfInputs()]->s_vec;
    
    if(x->f_ambisonics_grain->getMode() == Hoa_Post_Encoding)
        dsp_add(hoa_grain_perform_post, 1, x);
    else if(x->f_ambisonics_grain->getMode() == Hoa_No_Encoding)
        dsp_add(hoa_grain_perform_no, 1, x);
}

t_int *hoa_grain_perform_post(t_int *w)
{
	hoa_grain *x	= (hoa_grain *)(w[1]);
	
	x->f_ambisonics_grain->process(x->f_inputs, x->f_outputs);

    for(int i = 0; i < x->f_ambisonics_grain->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_grain->getVectorSize());

	return (w + 2);
}

t_int *hoa_grain_perform_no(t_int *w)
{
	hoa_grain *x	= (hoa_grain *)(w[1]);
	
	x->f_ambisonics_grain->process(x->f_inputs[0], x->f_outputs);

    for(int i = 0; i < x->f_ambisonics_grain->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_grain->getVectorSize());
    
	return (w + 2);
}

void hoa_grain_size(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_grain->setGrainSize(atom_getfloat(argv));
    post("size %f", x->f_ambisonics_grain->getGrainSize());
    for(int i = 0; i < x->f_ambisonics_grain->getNumberOfHarmonics(); i++)
    {
        post("%i size %f", i, x->f_ambisonics_grain->getGrainSizeFromIndex(i));
    }
}

void hoa_grain_delay(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_grain->setDelayTime(atom_getfloat(argv));
}

void hoa_grain_rare(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_grain->setRarefaction(atom_getfloat(argv));
}

void hoa_grain_feed(hoa_grain *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_grain->setFeedback(atom_getfloat(argv));
}

void hoa_grain_buffer_set(hoa_grain *x, t_symbol *s)
{
    t_garray *a = NULL;
    x->f_buffer_name = s;
    if (!(a = (t_garray *)pd_findbyclass(x->f_buffer_name, garray_class)))
    {
        x->f_buffer = 0;
        x->f_number_of_samples = 0;
    }
    else if (!garray_getfloatarray(a, &x->f_number_of_samples, &x->f_buffer))
    {
        x->f_buffer = 0;
        x->f_number_of_samples = 0;
    }
    else
    {
        x->f_ambisonics_grain->writeWidowFunction(x->f_buffer, x->f_number_of_samples);
    }
}

void hoa_grain_free(hoa_grain *x)
{
	for(int i = 0; i < x->f_ambisonics_grain->getNumberOfOutputs(); i++)
    {
        free(x->f_outputs[i]);
    }
    free(x->f_outputs);
    free(x->f_inputs);
    free(x->f_outputs_real);
	delete(x->f_ambisonics_grain);
}
