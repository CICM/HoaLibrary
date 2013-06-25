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

#include "../../Sources64/hoaEncoder/AmbisonicsEncoder.h"

extern "C"
{
#include "../m_pd.h"
}

typedef struct hoa_encoder
{
    t_object            f_obj;
    AmbisonicsEncoder	*f_ambisonics_encoder;
    t_float             f;
    t_float**           f_inputs;
    t_float**           f_outputs;
    t_float**           f_outputs_real;
} hoa_encoder;

void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_encoder_free(hoa_encoder *x);

void hoa_encoder_dsp(hoa_encoder *x, t_signal **sp, short *count);
t_int *hoa_encoder_perform(t_int *w);

t_class *hoa_encoder_class;

extern "C"
{
void setup_hoa0x2eencoder_tilde(void)
{
    t_class* c;
    c = class_new(gensym("hoa.encoder~"), (t_newmethod)hoa_encoder_new,(t_method)hoa_encoder_free, sizeof(hoa_encoder), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)hoa_encoder_dsp,		gensym("dsp"),		A_CANT, 0);
    
    hoa_encoder_class = c;
    CLASS_MAINSIGNALIN(hoa_encoder_class, hoa_encoder, f);
}
}

void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv)
{
	hoa_encoder *x = NULL;
	int	order = 4;

    x = (hoa_encoder *)pd_new(hoa_encoder_class);
	if (x)
	{
        order = atom_getint(argv);
        
		x->f_ambisonics_encoder = new AmbisonicsEncoder(order);
        
        for (int i = 0; i < x->f_ambisonics_encoder->getNumberOfInputs()-1; i++)
            inlet_new(&x->f_obj, &x->f_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->f_ambisonics_encoder->getNumberOfOutputs(); i++)
			outlet_new(&x->f_obj, &s_signal);
        
        x->f_outputs        = new float*[x->f_ambisonics_encoder->getNumberOfOutputs()];
        x->f_outputs_real   = new float*[x->f_ambisonics_encoder->getNumberOfOutputs()];
        x->f_inputs         = new float*[x->f_ambisonics_encoder->getNumberOfInputs()];
        for(int i = 0; i < x->f_ambisonics_encoder->getNumberOfOutputs(); i++)
            x->f_outputs[i] = new float[8192];
	}
	return (x);
}

void hoa_encoder_dsp(hoa_encoder *x, t_signal **sp, short *count)
{
	x->f_ambisonics_encoder->setVectorSize(sp[0]->s_n);

    for(int i = 0; i < x->f_ambisonics_encoder->getNumberOfInputs(); i++)
        x->f_inputs[i] = sp[i]->s_vec;
    for(int i = 0; i < x->f_ambisonics_encoder->getNumberOfOutputs(); i++)
        x->f_outputs_real[i] = sp[i+x->f_ambisonics_encoder->getNumberOfInputs()]->s_vec;

    dsp_add(hoa_encoder_perform, 1, x);
}

t_int *hoa_encoder_perform(t_int *w)
{
	hoa_encoder *x	= (hoa_encoder *)(w[1]);
	
	x->f_ambisonics_encoder->process(x->f_inputs[0], x->f_outputs, x->f_inputs[1]);
    for(int i = 0; i < x->f_ambisonics_encoder->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_encoder->getVectorSize());
    
	return (w + 2);
}

void hoa_encoder_free(hoa_encoder *x)
{
	for(int i = 0; i < x->f_ambisonics_encoder->getNumberOfOutputs(); i++)
    {
        free(x->f_outputs[i]);
    }
    free(x->f_outputs);
    free(x->f_inputs);
    free(x->f_outputs_real);
	delete(x->f_ambisonics_encoder);
}
