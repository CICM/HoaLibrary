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

typedef struct hoa_space
{
    t_object            f_obj;
    AmbisonicSpace      *f_ambisonics_space;
    t_float             f;
    t_float**           f_inputs;
    t_float**           f_outputs;
    t_float**           f_outputs_real;
} hoa_space;

void *hoa_space_new(t_symbol *s, long argc, t_atom *argv);
void hoa_space_free(hoa_space *x);
void hoa_space_list(hoa_space *x, t_symbol *s, short ac, t_atom *av);

void hoa_space_dsp(hoa_space *x, t_signal **sp, short *count);
t_int *hoa_space_perform(t_int *w);

t_class *hoa_space_class;

extern "C"
{
void setup_hoa0x2espace_tilde(void)
{
    t_class* c;
    c = class_new(gensym("hoa.space~"), (t_newmethod)hoa_space_new,(t_method)hoa_space_free, sizeof(hoa_space), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)hoa_space_dsp,		gensym("dsp"),		A_CANT, 0);
    class_addlist(c, hoa_space_list);
    
    hoa_space_class = c;
    CLASS_MAINSIGNALIN(hoa_space_class, hoa_space, f);
}
}

void *hoa_space_new(t_symbol *s, long argc, t_atom *argv)
{
	hoa_space *x = NULL;
	int	microphones = 10;

    x = (hoa_space *)pd_new(hoa_space_class);
	if (x)
	{
        microphones = atom_getint(argv);
        
		x->f_ambisonics_space = new AmbisonicSpace(microphones);
        
        for (int i = 0; i < x->f_ambisonics_space->getNumberOfInputs()-1; i++)
            inlet_new(&x->f_obj, &x->f_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->f_ambisonics_space->getNumberOfOutputs(); i++)
			outlet_new(&x->f_obj, &s_signal);
        
        x->f_outputs        = new float*[x->f_ambisonics_space->getNumberOfOutputs()];
        x->f_outputs_real   = new float*[x->f_ambisonics_space->getNumberOfOutputs()];
        x->f_inputs         = new float*[x->f_ambisonics_space->getNumberOfInputs()];
        for(int i = 0; i < x->f_ambisonics_space->getNumberOfOutputs(); i++)
            x->f_outputs[i] = new float[8192];
	}
	return (x);
}

void hoa_space_dsp(hoa_space *x, t_signal **sp, short *count)
{
	x->f_ambisonics_space->setVectorSize(sp[0]->s_n);

    for(int i = 0; i < x->f_ambisonics_space->getNumberOfInputs(); i++)
        x->f_inputs[i] = sp[i]->s_vec;
    for(int i = 0; i < x->f_ambisonics_space->getNumberOfOutputs(); i++)
        x->f_outputs_real[i] = sp[i+x->f_ambisonics_space->getNumberOfInputs()]->s_vec;

    dsp_add(hoa_space_perform, 1, x);
}

t_int *hoa_space_perform(t_int *w)
{
	hoa_space *x	= (hoa_space *)(w[1]);
	
	x->f_ambisonics_space->process(x->f_inputs, x->f_outputs);
    for(int i = 0; i < x->f_ambisonics_space->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_space->getVectorSize());
    
	return (w + 2);
}

void hoa_space_list(hoa_space *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2)
        x->f_ambisonics_space->setCoefficient(atom_getint(av), atom_getfloat(av+1));
    else
    {
        for(int i = 0; i < ac; i++)
        {
            x->f_ambisonics_space->setCoefficient(i, atom_getfloat(av+i));
        }
    }
}

void hoa_space_free(hoa_space *x)
{
	for(int i = 0; i < x->f_ambisonics_space->getNumberOfOutputs(); i++)
    {
        free(x->f_outputs[i]);
    }
    free(x->f_outputs);
    free(x->f_inputs);
    free(x->f_outputs_real);
	delete(x->f_ambisonics_space);
}
