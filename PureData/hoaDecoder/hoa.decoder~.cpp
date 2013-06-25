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

#include "../../Sources64/hoaMultiDecoder/AmbisonicsMultiDecoder.h"

extern "C"
{
#include "../m_pd.h"
}

typedef struct hoa_decoder
{
    t_object                f_obj;
    AmbisonicsMultiDecoder	*f_ambisonics_decoder;
    t_float                 f;
    t_float**               f_inputs;
    t_float**               f_outputs;
    t_float**               f_outputs_real;
} hoa_decoder;

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_free(hoa_decoder *x);

void hoa_decoder_dsp(hoa_decoder *x, t_signal **sp, short *count);
t_int *hoa_decoder_perform(t_int *w);

t_class *hoa_decoder_class;

extern "C"
{
void setup_hoa0x2edecoder_tilde(void)
{
    t_class* c;
    c = class_new(gensym("hoa.decoder~"), (t_newmethod)hoa_decoder_new,(t_method)hoa_decoder_free, sizeof(hoa_decoder), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)hoa_decoder_dsp,		gensym("dsp"),		A_CANT, 0);
    
    hoa_decoder_class = c;
    CLASS_MAINSIGNALIN(hoa_decoder_class, hoa_decoder, f);
    post("hoa.library (version 1.0) by Julien Colafrancesco, Pierre Guillot & Eliott Paris with the participation of Manuel Deneu");
	post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
}
}

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
	hoa_decoder *x = NULL;
	int	order = 4;
    float numberOfLoudspeakers = 10;
    int mode = Hoa_Ambisonics;
    int pinnaesize = Hoa_Small;
    float offset = 0.f;
    int decmode= Hoa_Amplitude_Panning;
    
    char hrtfPath[256];
    x = (hoa_decoder *)pd_new(hoa_decoder_class);
	if (x)
	{
        order = atom_getint(argv);
        numberOfLoudspeakers = atom_getfloat(argv+1);
        if(atom_getsymbol(argv+2) == gensym("binaural"))
            mode = Hoa_Binaural;
        else if(atom_getsymbol(argv+2) == gensym("irregular"))
            mode = Hoa_Restitution;
        
        if (mode == Hoa_Ambisonics)
            offset = atom_getfloat(argv+3);
        else if (mode == Hoa_Binaural && atom_getsymbol(argv+3) == gensym("large"))
            pinnaesize = Hoa_Large;
        else if (mode == Hoa_Restitution && atom_getsymbol(argv+3) == gensym("projection"))
            decmode = Hoa_Microphone_Simulation;
        
        
        sprintf(hrtfPath, "%s/HrtfDatabase/", canvas_getcurrentdir()->s_name);
        
		x->f_ambisonics_decoder = new AmbisonicsMultiDecoder(order, hrtfPath, pinnaesize, 64, 44100, mode, numberOfLoudspeakers, numberOfLoudspeakers, offset);
        x->f_ambisonics_decoder->setRestitutionMode(decmode);
        
        for (int i = 0; i < x->f_ambisonics_decoder->getNumberOfInputs()-1; i++)
            inlet_new(&x->f_obj, &x->f_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->f_ambisonics_decoder->getNumberOfOutputs(); i++)
			outlet_new(&x->f_obj, &s_signal);
        
        x->f_outputs        = new float*[x->f_ambisonics_decoder->getNumberOfOutputs()];
        x->f_outputs_real   = new float*[x->f_ambisonics_decoder->getNumberOfOutputs()];
        x->f_inputs         = new float*[x->f_ambisonics_decoder->getNumberOfInputs()];
        for(int i = 0; i < x->f_ambisonics_decoder->getNumberOfOutputs(); i++)
            x->f_outputs[i] = new float[8192];
	}
	return (x);
}

void hoa_decoder_dsp(hoa_decoder *x, t_signal **sp, short *count)
{
	x->f_ambisonics_decoder->setVectorSize((long)sp[0]->s_n);
    x->f_ambisonics_decoder->setSamplingRate((long)sp[0]->s_sr);
    
    for(int i = 0; i < x->f_ambisonics_decoder->getNumberOfInputs(); i++)
        x->f_inputs[i] = sp[i]->s_vec;
    for(int i = 0; i < x->f_ambisonics_decoder->getNumberOfOutputs(); i++)
        x->f_outputs_real[i] = sp[i+x->f_ambisonics_decoder->getNumberOfInputs()]->s_vec;

    dsp_add(hoa_decoder_perform, 1, x);
}

t_int *hoa_decoder_perform(t_int *w)
{
	hoa_decoder *x	= (hoa_decoder *)(w[1]);
	
	x->f_ambisonics_decoder->process(x->f_inputs, x->f_outputs);
    
    for(int i = 0; i < x->f_ambisonics_decoder->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_decoder->getVectorSize());
    
	return (w + 2);
}

void hoa_decoder_free(hoa_decoder *x)
{
	for(int i = 0; i < x->f_ambisonics_decoder->getNumberOfOutputs(); i++)
    {
        free(x->f_outputs[i]);
    }
    free(x->f_outputs);
    free(x->f_inputs);
    free(x->f_outputs_real);
	delete(x->f_ambisonics_decoder);
}
