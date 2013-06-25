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

#include "../../Sources64/hoaMapProcessor/AmbisonicMultiMaps.h"

extern "C"
{
#include "../m_pd.h"
}

typedef struct hoa_map
{
    t_object            f_obj;
    AmbisonicsMultiMaps *f_ambisonics_map;
    t_float             f;
    t_float**           f_inputs;
    t_float**           f_outputs;
    t_float**           f_outputs_real;
    bool				f_mode_bool;
} hoa_map;

void *hoa_map_new(t_symbol *s, long argc, t_atom *argv);
void hoa_map_free(hoa_map *x);
void hoa_map_list(hoa_map *x, t_symbol *s, long argc, t_atom *argv);

void hoa_map_dsp(hoa_map *x, t_signal **sp, short *count);
t_int *hoa_map_perform(t_int *w);
t_int *hoa_map_perform_polar(t_int *w);
t_int *hoa_map_perform_cartesian(t_int *w);

t_class *hoa_map_class;

extern "C"
{
void setup_hoa0x2emap_tilde(void)
{
    t_class *c;
    c = class_new(gensym("hoa.map~"), (t_newmethod)hoa_map_new,(t_method)hoa_map_free, sizeof(hoa_map), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)hoa_map_dsp,     gensym("dsp"),		A_CANT, 0);
    class_addlist(c, (t_method)hoa_map_list);
    
    hoa_map_class = c;
    CLASS_MAINSIGNALIN(hoa_map_class, hoa_map, f);
}
}

void *hoa_map_new(t_symbol *s, long argc, t_atom *argv)
{
	hoa_map *x = NULL;
	int	order = 4;
    int numberOfSources = 10;
    
    x = (hoa_map *)pd_new(hoa_map_class);
	if (x)
	{
        x->f_mode_bool = 0;
        order = atom_getint(argv);
        numberOfSources = atom_getint(argv+1);
        if(atom_getsymbol(argv+2) == gensym("cartesian") || atom_getsymbol(argv+2) == gensym("car"))
            x->f_mode_bool = 1;
        
		x->f_ambisonics_map = new AmbisonicsMultiMaps(order, numberOfSources);
        
        for (int i = 0; i < x->f_ambisonics_map->getNumberOfInputs()-1; i++)
            inlet_new(&x->f_obj, &x->f_obj.ob_pd, &s_signal, &s_signal);
        for (int i = 0; i < x->f_ambisonics_map->getNumberOfOutputs(); i++)
			outlet_new(&x->f_obj, &s_signal);
        
        x->f_outputs        = new float*[x->f_ambisonics_map->getNumberOfOutputs()];
        x->f_outputs_real   = new float*[x->f_ambisonics_map->getNumberOfOutputs()];
        x->f_inputs         = new float*[x->f_ambisonics_map->getNumberOfInputs()];
        for(int i = 0; i < x->f_ambisonics_map->getNumberOfOutputs(); i++)
            x->f_outputs[i] = new float[8192];
	}
	return (x);
}

void hoa_map_dsp(hoa_map *x, t_signal **sp, short *count)
{
	x->f_ambisonics_map->setVectorSize(sp[0]->s_n);

    for(int i = 0; i < x->f_ambisonics_map->getNumberOfInputs(); i++)
        x->f_inputs[i] = sp[i]->s_vec;
    for(int i = 0; i < x->f_ambisonics_map->getNumberOfOutputs(); i++)
        x->f_outputs_real[i] = sp[i+x->f_ambisonics_map->getNumberOfInputs()]->s_vec;
    
    if (x->f_ambisonics_map->getNumberOfSources() == 1 && x->f_mode_bool == 0)
        dsp_add(hoa_map_perform_polar, 1, x);
    else if (x->f_ambisonics_map->getNumberOfSources() == 1 && x->f_mode_bool == 1)
        dsp_add(hoa_map_perform_cartesian, 1, x);
    else
        dsp_add(hoa_map_perform, 1, x);
}

t_int *hoa_map_perform(t_int *w)
{
	hoa_map *x	= (hoa_map *)(w[1]);
	
	x->f_ambisonics_map->process(x->f_inputs, x->f_outputs);
    for(int i = 0; i < x->f_ambisonics_map->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_map->getVectorSize());

	return (w + 2);
}

t_int *hoa_map_perform_polar(t_int *w)
{
	hoa_map *x	= (hoa_map *)(w[1]);
	
	x->f_ambisonics_map->processPolar(x->f_inputs[0], x->f_outputs, x->f_inputs[1], x->f_inputs[2]);
    for(int i = 0; i < x->f_ambisonics_map->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_map->getVectorSize());
    
	return (w + 2);
}

t_int *hoa_map_perform_cartesian(t_int *w)
{
	hoa_map *x	= (hoa_map *)(w[1]);
	
	x->f_ambisonics_map->processCartesian(x->f_inputs[0], x->f_outputs, x->f_inputs[1], x->f_inputs[2]);
    for(int i = 0; i < x->f_ambisonics_map->getNumberOfOutputs(); i++)
        Cicm_Vector_Float_Copy(x->f_outputs[i], x->f_outputs_real[i], x->f_ambisonics_map->getVectorSize());
    
	return (w + 2);
}

void hoa_map_list(hoa_map *x, t_symbol *s, long argc, t_atom *argv)
{
    if(atom_getsymbol(argv+1) == gensym("car") || atom_getsymbol(argv+1) == gensym("cartesian"))
        x->f_ambisonics_map->setCoordinatesCartesian(atom_getint(argv), atom_getfloat(argv+2), atom_getfloat(argv+3));
    else if(atom_getsymbol(argv+1) == gensym("pol") || atom_getsymbol(argv+1) == gensym("polar"))
        x->f_ambisonics_map->setCoordinatesPolar(atom_getint(argv), atom_getfloat(argv+2), atom_getfloat(argv+3));
    else if (atom_getsymbol(argv+1) == gensym("mute"))
        x->f_ambisonics_map->setMuted(atom_getint(argv), atom_getint(argv+2));
}

void hoa_map_free(hoa_map *x)
{
	for(int i = 0; i < x->f_ambisonics_map->getNumberOfOutputs(); i++)
    {
        free(x->f_outputs[i]);
    }
    free(x->f_outputs);
    free(x->f_inputs);
    free(x->f_outputs_real);
	delete(x->f_ambisonics_map);
}
