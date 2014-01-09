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

extern "C"
{
#include "../../../PdEnhanced/Sources/cicm_wrapper.h"
}

#include "../../Sources/HoaLibrary.h"

typedef struct _hoa_delay
{
    t_edspobj           f_ob;
    AmbisonicsDelay*    f_ambi_delay;
    
} t_hoa_delay;

void *hoa_delay_new(t_symbol *s, long argc, t_atom *argv);
void hoa_delay_free(t_hoa_delay *x);

void hoa_delay_ramp(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_delay_time_ms(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_delay_time_sample(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_delay_diff(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_delay_comp(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv);

void hoa_delay_dsp(t_hoa_delay *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_delay_perform_post(t_hoa_delay *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_delay_perform_no(t_hoa_delay *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_delay_class;

extern "C" void setup_hoa0x2edelay_tilde(void)
{
    t_eclass *c;
    c = eclass_new("hoa.delay~", (method)hoa_delay_new,(method)hoa_delay_free, sizeof(t_hoa_delay), 0L, A_GIMME, 0);
    
    eclass_dspinit(c);
    eclass_addmethod(c, (method)hoa_delay_dsp,           "dsp",          A_CANT, 0);
    eclass_addmethod(c, (method)hoa_delay_ramp,          "ramp",         A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_delay_comp,          "comp",         A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_delay_time_ms,       "ms",           A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_delay_time_sample,   "sample",       A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_delay_diff,          "diff",         A_GIMME, 0);
    
    eclass_register(CLASS_BOX, c);
    erouter_add_libary(gensym("hoa"), "hoa.library by Julien Colafrancesco, Pierre Guillot & Eliott Paris", "© 2012 - 2014  CICM | Paris 8 University", "Version 1.1");
    hoa_delay_class = c;
}

void *hoa_delay_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_delay *x = NULL;
    int order = 4;
    bool mode = 1;
    double maxdelay = 5000.;
    
    x = (t_hoa_delay *)eobj_new(hoa_delay_class);
	order = atom_getint(argv);
    if(atom_getsym(argv+1) == gensym("no"))
        mode = 0;
    
    x->f_ambi_delay = new AmbisonicsDelay(order, mode, maxdelay, (int)sys_getblksize(), (int)sys_getsr());
    eobj_dspsetup(x, x->f_ambi_delay->getNumberOfInputs(), x->f_ambi_delay->getNumberOfOutputs());
    
    x->f_ob.d_misc = E_NO_INPLACE;
    
	return (x);
}

void hoa_delay_dsp(t_hoa_delay *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_delay->setVectorSize(maxvectorsize);
    x->f_ambi_delay->setSamplingRate(samplerate);
    
    if(x->f_ambi_delay->getMode() == Hoa_Post_Encoding)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_delay_perform_post, 0, NULL);
    else if(x->f_ambi_delay->getMode() == Hoa_No_Encoding)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_delay_perform_no, 0, NULL);
}

void hoa_delay_perform_post(t_hoa_delay *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
    x->f_ambi_delay->process(ins, outs);
}

void hoa_delay_perform_no(t_hoa_delay *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
    x->f_ambi_delay->process(ins[0], outs);
}

void hoa_delay_ramp(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_delay->setRampInMs(atom_getfloat(argv));
}

void hoa_delay_diff(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_delay->setDiffuseFactor(atom_getfloat(argv));
}

void hoa_delay_comp(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_delay->setEncodingCompensation(atom_getint(argv));
}

void hoa_delay_time_ms(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_delay->setDelayTimeInMs(atom_getfloat(argv));
}

void hoa_delay_time_sample(t_hoa_delay *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_delay->setDelayTimeInSample(atom_getint(argv));
}

void hoa_delay_free(t_hoa_delay *x)
{
	eobj_dspfree(x);
	delete(x->f_ambi_delay);
}
