/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../hoaLibrary/hoa.library_pd.h"

typedef struct _hoa_grain
{
    t_jbox              f_ob;
    AmbisonicsGrain*    f_ambi_grain;
    
    int                 f_number_of_samples;
    t_float*            f_buffer;
    t_symbol*           f_buffer_name;
    
} t_hoa_grain;

void *hoa_grain_new(t_symbol *s, long argc, t_atom *argv);
void hoa_grain_free(t_hoa_grain *x);

void hoa_grain_size(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_delay(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_feed(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_rare(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_diff(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_comp(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_grain_buffer_set(t_hoa_grain *x, t_symbol *s);

void hoa_grain_dsp(t_hoa_grain *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_grain_perform_post(t_hoa_grain *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_grain_perform_no(t_hoa_grain *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_grain_class;

extern "C" void setup_hoa0x2egrain_tilde(void)
{    
    t_eclass* c;
    
    c = class_new("hoa.grain~", (method)hoa_grain_new, (method)hoa_grain_free, (short)sizeof(t_hoa_grain), 0L, A_GIMME, 0);
    
	class_dspinit(c);
    
    class_addmethod(c, (method)hoa_grain_dsp,           "dsp",          A_CANT,  0);
    class_addmethod(c, (method)hoa_grain_size,          "size",         A_GIMME, 0);
    class_addmethod(c, (method)hoa_grain_delay,         "delay",        A_GIMME, 0);
    class_addmethod(c, (method)hoa_grain_feed,          "feedback",     A_GIMME, 0);
    class_addmethod(c, (method)hoa_grain_rare,          "rarefaction",  A_GIMME, 0);
    class_addmethod(c, (method)hoa_grain_buffer_set,    "set",        A_SYMBOL,0);
    
    class_register(CLASS_BOX, c);
    hoa_grain_class = c;
}

void *hoa_grain_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_grain *x = NULL;
    t_dictionary *d;
	int	order = 4;
    bool mode = 1;
    
    x = (t_hoa_grain *)object_alloc(hoa_grain_class);
    
    order = atom_getint(argv);
    if(atom_getsym(argv+1) == gensym("no"))
        mode = 0;
    
    x->f_ambi_grain = new AmbisonicsGrain(order, mode, 5000, sys_getblksize(), sys_getsr());
    dsp_setupjbox((t_jbox *)x, x->f_ambi_grain->getNumberOfInputs(), x->f_ambi_grain->getNumberOfOutputs());
    hoa_grain_buffer_set(x, atom_getsymbol(argv+2));
    x->f_ambi_grain->setGrainSize(20.);
    x->f_ambi_grain->setDelayTime(100.);
    x->f_ambi_grain->setRarefaction(0.);
    x->f_ambi_grain->setFeedback(0.95);
    
	x->f_ob.z_misc = Z_NO_INPLACE;
    
    d = object_dictionaryarg(argc,argv);
    attr_dictionary_process(x, d);
    
    return (x);
}

void hoa_grain_dsp(t_hoa_grain *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_grain->setVectorSize(maxvectorsize);
    x->f_ambi_grain->setSamplingRate(samplerate);
    
    hoa_grain_buffer_set(x, x->f_buffer_name);

    if(x->f_ambi_grain->getMode() == Hoa_Post_Encoding)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_grain_perform_post, 0, NULL);
    else if(x->f_ambi_grain->getMode() == Hoa_No_Encoding)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_grain_perform_no, 0, NULL);
}

void hoa_grain_perform_post(t_hoa_grain *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_grain->process(ins, outs);
}

void hoa_grain_perform_no(t_hoa_grain *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_grain->process(ins[0], outs);
}

void hoa_grain_size(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_grain->setGrainSize(atom_getfloat(argv));
}

void hoa_grain_delay(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_grain->setDelayTime(atom_getfloat(argv));
}

void hoa_grain_rare(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_grain->setRarefaction(atom_getfloat(argv));
}

void hoa_grain_feed(t_hoa_grain *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_grain->setFeedback(atom_getfloat(argv));
}

void hoa_grain_buffer_set(t_hoa_grain *x, t_symbol *s)
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
        x->f_ambi_grain->writeWidowFunction(x->f_buffer, x->f_number_of_samples);
    }
}

void hoa_grain_free(t_hoa_grain *x)
{
	dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_grain);
}
