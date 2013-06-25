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

#include "../../Sources64/hoarotate/AmbisonicsRotate.h"

extern "C"
{
#include "../m_pd.h"
}

typedef struct hoa_rotate
{
    t_object            f_obj;
    AmbisonicsRotate	*f_ambisonics_rotate;
    t_float             f;
    t_float**           f_inputs;
    t_float**           f_outputs;
    t_float**           f_outputs_real;
} hoa_rotate;

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv);
void hoa_rotate_free(hoa_rotate *x);

void hoa_rotate_dsp(hoa_rotate *x, t_signal **sp, short *count);
t_int *hoa_rotate_perform(t_int *w);

t_class *hoa_rotate_class;

extern "C"
{
void setup_hoa0x2erotate_tilde(void)
{
    t_class* c;
    c = class_new(gensym("hoa.rotate~"), (t_newmethod)hoa_rotate_new,(t_method)hoa_rotate_free, sizeof(hoa_rotate), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)hoa_rotate_dsp,		gensym("dsp"),		A_CANT, 0);
    hoa_rotate_class = c;
    CLASS_MAINSIGNALIN(hoa_rotate_class, hoa_rotate, f);
}
}

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv)
{
	hoa_rotate *x = NULL;
	int	order = 4;

    x = (hoa_rotate *)pd_new(hoa_rotate_class);
	if (x)
	{
        order = atom_getint(argv);
        
		x->f_ambisonics_rotate = new AmbisonicsRotate(order);
        
        for (int i = 0; i < x->f_ambisonics_rotate->getNumberOfInputs()-1; i++)
            inlet_new(&x->f_obj, &x->f_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->f_ambisonics_rotate->getNumberOfOutputs(); i++)
			outlet_new(&x->f_obj, &s_signal);
        
        x->f_outputs        = new float*[x->f_ambisonics_rotate->getNumberOfOutputs()];
        x->f_outputs_real   = new float*[x->f_ambisonics_rotate->getNumberOfOutputs()];
        x->f_inputs         = new float*[x->f_ambisonics_rotate->getNumberOfInputs()];
        for(int i = 0; i < x->f_ambisonics_rotate->getNumberOfOutputs(); i++)
            x->f_outputs[i] = new float[8192];
	}
	return (x);
}

void hoa_rotate_dsp(hoa_rotate *x, t_signal **sp, short *count)
{
	x->f_ambisonics_rotate->setVectorSize(sp[0]->s_n);

    for(int i = 0; i < x->f_ambisonics_rotate->getNumberOfInputs(); i++)
        x->f_inputs[i] = sp[i]->s_vec;
    for(int i = 0; i < x->f_ambisonics_rotate->getNumberOfOutputs(); i++)
        x->f_outputs_real[i] = sp[i+x->f_ambisonics_rotate->getNumberOfInputs()]->s_vec;

    dsp_add(hoa_rotate_perform, 1, x);
}

t_int *hoa_rotate_perform(t_int *w)
{
	hoa_rotate *x	= (hoa_rotate *)(w[1]);
	
	x->f_ambisonics_rotate->process(x->f_inputs, x->f_outputs, x->f_inputs[x->f_ambisonics_rotate->getNumberOfInputs()-1]);
    for(int i = 0; i < x->f_ambisonics_rotate->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_rotate->getVectorSize());
    
	return (w + 2);
}

void hoa_rotate_free(hoa_rotate *x)
{
	for(int i = 0; i < x->f_ambisonics_rotate->getNumberOfOutputs(); i++)
    {
        free(x->f_outputs[i]);
    }
    free(x->f_outputs);
    free(x->f_inputs);
    free(x->f_outputs_real);
	delete(x->f_ambisonics_rotate);
}
