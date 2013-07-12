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

typedef struct hoa_delay
{
    t_object            f_obj;
    AmbisonicsDelay     *f_ambisonics_delay;
    t_float             f;
    t_float**           f_inputs;
    t_float**           f_outputs;
    t_float**           f_outputs_real;
   
} hoa_delay;

void *hoa_delay_new(t_symbol *s, long argc, t_atom *argv);
void hoa_delay_free(hoa_delay *x);

void hoa_delay_ramp(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_delay_time_ms(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_delay_time_sample(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_delay_diff(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_delay_comp(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);

void hoa_delay_dsp(hoa_delay *x, t_signal **sp, short *count);
t_int *hoa_delay_perform_post(t_int *w);
t_int *hoa_delay_perform_no(t_int *w);

t_class *hoa_delay_class;

extern "C"
{
void setup_hoa0x2edelay_tilde(void)
{
    t_class *c;
    c = class_new(gensym("hoa.delay~"), (t_newmethod)hoa_delay_new,(t_method)hoa_delay_free, sizeof(hoa_delay), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)hoa_delay_dsp,     gensym("dsp"),          A_CANT, 0);
    class_addmethod(c, (t_method)hoa_delay_ramp,    gensym("ramp"),         A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_delay_comp,    gensym("comp"),         A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_delay_time_ms,    gensym("ms"),        A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_delay_time_sample,gensym("sample"),    A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_delay_diff,    gensym("diff"),         A_GIMME, 0);
    
    hoa_delay_class = c;
    CLASS_MAINSIGNALIN(hoa_delay_class, hoa_delay, f);
}
}

void *hoa_delay_new(t_symbol *s, long argc, t_atom *argv)
{
	hoa_delay *x = NULL;
    int order = 4;
    bool mode = 1;
    double maxdelay = 5000.;
    
    x = (hoa_delay *)pd_new(hoa_delay_class);
	if (x)
	{
        order = atom_getint(argv);
        if(atom_getsymbol(argv+1) == gensym("no"))
            mode = 0;
        
		x->f_ambisonics_delay = new AmbisonicsDelay(order, mode, maxdelay, (int)sys_getblksize(), (int)sys_getsr());
        
        for (int i = 0; i < x->f_ambisonics_delay->getNumberOfInputs()-1; i++)
            inlet_new(&x->f_obj, &x->f_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->f_ambisonics_delay->getNumberOfOutputs(); i++)
			outlet_new(&x->f_obj, &s_signal);
        
        x->f_outputs        = new float*[x->f_ambisonics_delay->getNumberOfOutputs()];
        x->f_outputs_real   = new float*[x->f_ambisonics_delay->getNumberOfOutputs()];
        x->f_inputs         = new float*[x->f_ambisonics_delay->getNumberOfInputs()];
        for(int i = 0; i < x->f_ambisonics_delay->getNumberOfOutputs(); i++)
            x->f_outputs[i] = new float[8192];
	}
	return (x);
}

void hoa_delay_dsp(hoa_delay *x, t_signal **sp, short *count)
{
	x->f_ambisonics_delay->setVectorSize((int)sp[0]->s_n);
    x->f_ambisonics_delay->setSamplingRate((int)sp[0]->s_sr);
    
    for(int i = 0; i < x->f_ambisonics_delay->getNumberOfInputs(); i++)
        x->f_inputs[i] = sp[i]->s_vec;
    for(int i = 0; i < x->f_ambisonics_delay->getNumberOfOutputs(); i++)
        x->f_outputs_real[i] = sp[i+x->f_ambisonics_delay->getNumberOfInputs()]->s_vec;
    
    if(x->f_ambisonics_delay->getMode() == Hoa_Post_Encoding)
        dsp_add(hoa_delay_perform_post, 1, x);
    else if(x->f_ambisonics_delay->getMode() == Hoa_No_Encoding)
        dsp_add(hoa_delay_perform_no, 1, x);
}

t_int *hoa_delay_perform_post(t_int *w)
{
	hoa_delay *x	= (hoa_delay *)(w[1]);
	
	x->f_ambisonics_delay->process(x->f_inputs, x->f_outputs_real);

    for(int i = 0; i < x->f_ambisonics_delay->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_delay->getVectorSize());

	return (w + 2);
}

t_int *hoa_delay_perform_no(t_int *w)
{
	hoa_delay *x	= (hoa_delay *)(w[1]);
	
	x->f_ambisonics_delay->process(x->f_inputs[0], x->f_outputs_real);

    for(int i = 0; i < x->f_ambisonics_delay->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_delay->getVectorSize());
    
	return (w + 2);
}

void hoa_delay_ramp(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_delay->setRampInMs(atom_getfloat(argv));
}

void hoa_delay_diff(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_delay->setDiffuseFactor(atom_getfloat(argv));
}

void hoa_delay_comp(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_delay->setEncodingCompensation(atom_getint(argv));
}

void hoa_delay_time_ms(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_delay->setDelayTimeInMs(atom_getfloat(argv));
}

void hoa_delay_time_sample(hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_delay->setDelayTimeInSample(atom_getint(argv));
}

void hoa_delay_free(hoa_delay *x)
{
	for(int i = 0; i < x->f_ambisonics_delay->getNumberOfOutputs(); i++)
    {
        free(x->f_outputs[i]);
    }
    free(x->f_outputs);
    free(x->f_inputs);
    free(x->f_outputs_real);
	delete(x->f_ambisonics_delay);
}
