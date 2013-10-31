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

#include "../hoaLibrary/hoa.library_pd.h"

typedef struct _hoa_delay
{
    t_jbox              f_ob;
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
    c = class_new("hoa.delay~", (method)hoa_delay_new,(method)hoa_delay_free, sizeof(t_hoa_delay), 0L, A_GIMME, 0);
    
    class_dspinit(c);
    class_addmethod(c, (method)hoa_delay_dsp,           "dsp",          A_CANT, 0);
    class_addmethod(c, (method)hoa_delay_ramp,          "ramp",         A_GIMME, 0);
    class_addmethod(c, (method)hoa_delay_comp,          "comp",         A_GIMME, 0);
    class_addmethod(c, (method)hoa_delay_time_ms,       "ms",           A_GIMME, 0);
    class_addmethod(c, (method)hoa_delay_time_sample,   "sample",       A_GIMME, 0);
    class_addmethod(c, (method)hoa_delay_diff,          "diff",         A_GIMME, 0);
    
    class_register(CLASS_BOX, c);
    hoa_delay_class = c;
}

void *hoa_delay_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_delay *x = NULL;
    int order = 4;
    bool mode = 1;
    double maxdelay = 5000.;
    
    x = (t_hoa_delay *)object_alloc(hoa_delay_class);
	order = atom_getint(argv);
    if(atom_getsym(argv+1) == gensym("no"))
        mode = 0;
    
    x->f_ambi_delay = new AmbisonicsDelay(order, mode, maxdelay, (int)sys_getblksize(), (int)sys_getsr());
    dsp_setupjbox((t_jbox *)x, x->f_ambi_delay->getNumberOfInputs(), x->f_ambi_delay->getNumberOfOutputs());
    
    x->f_ob.z_misc = Z_NO_INPLACE;
    
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
	dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_delay);
}
