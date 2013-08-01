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

typedef struct hoa_freeverb
{
    t_object            f_obj;
    AmbisonicsFreeverb *f_ambisonics_freeverb;
    t_float             f;
    t_float**           f_inputs;
    t_float**           f_outputs;
    t_float**           f_outputs_real;
   
} hoa_freeverb;

void *hoa_freeverb_new(t_symbol *s, long argc, t_atom *argv);
void hoa_freeverb_free(hoa_freeverb *x);

void hoa_freeverb_size(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_damp(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_dry(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_wet(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_spread(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_fspread(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_lspread(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_freeze(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);

void hoa_freeverb_dsp(hoa_freeverb *x, t_signal **sp, short *count);
t_int *hoa_freeverb_perform(t_int *w);

t_class *hoa_freeverb_class;

extern "C"
{
void setup_hoa0x2efreeverb_tilde(void)
{
    t_class *c;
    c = class_new(gensym("hoa.freeverb~"), (t_newmethod)hoa_freeverb_new,(t_method)hoa_freeverb_free, sizeof(hoa_freeverb), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)hoa_freeverb_dsp,     gensym("dsp"),		A_CANT, 0);
    class_addmethod(c, (t_method)hoa_freeverb_size,    gensym("size"),		A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_freeverb_damp,    gensym("damp"),		A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_freeverb_dry,     gensym("dry"),		A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_freeverb_wet,     gensym("wet"),		A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_freeverb_fspread, gensym("fspread"),	A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_freeverb_lspread, gensym("lspread"),	A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_freeverb_spread,  gensym("spread"),	A_GIMME, 0);
    class_addmethod(c, (t_method)hoa_freeverb_freeze,  gensym("freeze"),	A_GIMME, 0);
    
    hoa_freeverb_class = c;
    CLASS_MAINSIGNALIN(hoa_freeverb_class, hoa_freeverb, f);
}
}

void *hoa_freeverb_new(t_symbol *s, long argc, t_atom *argv)
{
	hoa_freeverb *x = NULL;
	int	order = 4;
    
    x = (hoa_freeverb *)pd_new(hoa_freeverb_class);
	if (x)
	{
        order = atom_getint(argv);
        
		x->f_ambisonics_freeverb = new AmbisonicsFreeverb(order);
        
        for (int i = 0; i < x->f_ambisonics_freeverb->getNumberOfInputs()-1; i++)
            inlet_new(&x->f_obj, &x->f_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->f_ambisonics_freeverb->getNumberOfOutputs(); i++)
			outlet_new(&x->f_obj, &s_signal);
        
        x->f_outputs        = new float*[x->f_ambisonics_freeverb->getNumberOfOutputs()];
        x->f_outputs_real   = new float*[x->f_ambisonics_freeverb->getNumberOfOutputs()];
        x->f_inputs         = new float*[x->f_ambisonics_freeverb->getNumberOfInputs()];
        for(int i = 0; i < x->f_ambisonics_freeverb->getNumberOfOutputs(); i++)
            x->f_outputs[i] = new float[8192];
	}
	return (x);
}

void hoa_freeverb_dsp(hoa_freeverb *x, t_signal **sp, short *count)
{
	x->f_ambisonics_freeverb->setVectorSize(sp[0]->s_n);

    x->f_ambisonics_freeverb->setVectorSize(sp[0]->s_n);
    
    for(int i = 0; i < x->f_ambisonics_freeverb->getNumberOfInputs(); i++)
        x->f_inputs[i] = sp[i]->s_vec;
    for(int i = 0; i < x->f_ambisonics_freeverb->getNumberOfOutputs(); i++)
        x->f_outputs_real[i] = sp[i+x->f_ambisonics_freeverb->getNumberOfInputs()]->s_vec;
    
    dsp_add(hoa_freeverb_perform, 1, x);
}

t_int *hoa_freeverb_perform(t_int *w)
{
	hoa_freeverb *x	= (hoa_freeverb *)(w[1]);
	
	x->f_ambisonics_freeverb->process(x->f_inputs, x->f_outputs);
    for(int i = 0; i < x->f_ambisonics_freeverb->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_freeverb->getVectorSize());

	return (w + 2);
}

void hoa_freeverb_size(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_freeverb->setroomsize(atom_getfloat(argv));
}

void hoa_freeverb_damp(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_freeverb->setdamp(atom_getfloat(argv));
}

void hoa_freeverb_dry(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_freeverb->setDryValue(atom_getfloat(argv));
}

void hoa_freeverb_wet(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_freeverb->setWetValue(atom_getfloat(argv));
}

void hoa_freeverb_spread(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_freeverb->setSpread(atom_getfloat(argv));
}

void hoa_freeverb_fspread(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_freeverb->setDirectionalSpread(atom_getfloat(argv));
}

void hoa_freeverb_lspread(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_freeverb->setDiffuseSpread(atom_getfloat(argv));
}

void hoa_freeverb_freeze(hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambisonics_freeverb->setmode(atom_getfloat(argv));
}

void hoa_freeverb_free(hoa_freeverb *x)
{
	for(int i = 0; i < x->f_ambisonics_freeverb->getNumberOfOutputs(); i++)
    {
        free(x->f_outputs[i]);
    }
    free(x->f_outputs);
    free(x->f_inputs);
    free(x->f_outputs_real);
	delete(x->f_ambisonics_freeverb);
}
