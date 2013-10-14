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

typedef struct _hoa_freeverb
{
    t_jbox            f_ob;
    AmbisonicFreeverb*  f_ambi_freeverb;
    
} t_hoa_freeverb;

void *hoa_freeverb_new(t_symbol *s, long argc, t_atom *argv);
void hoa_freeverb_free(t_hoa_freeverb *x);

void hoa_freeverb_size(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_damp(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_dry(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_wet(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_spread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_fspread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_lspread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);
void hoa_freeverb_freeze(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv);

void hoa_freeverb_dsp(t_hoa_freeverb *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_freeverb_perform(t_hoa_freeverb *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_freeverb_class;

extern "C" void setup_hoa0x2efreeverb_tilde(void)
{
    t_eclass *c;
    c = class_new("hoa.freeverb~", (method)hoa_freeverb_new,(method)hoa_freeverb_free, sizeof(t_hoa_freeverb), 0L, A_GIMME, 0);
    
    class_dspinit(c);
    
    class_addmethod(c, (method)hoa_freeverb_dsp,     "dsp",		A_CANT, 0);
    class_addmethod(c, (method)hoa_freeverb_size,    "size",	A_GIMME, 0);
    class_addmethod(c, (method)hoa_freeverb_damp,    "damp",	A_GIMME, 0);
    class_addmethod(c, (method)hoa_freeverb_dry,     "dry",		A_GIMME, 0);
    class_addmethod(c, (method)hoa_freeverb_wet,     "wet",		A_GIMME, 0);
    class_addmethod(c, (method)hoa_freeverb_fspread, "fspread",	A_GIMME, 0);
    class_addmethod(c, (method)hoa_freeverb_lspread, "lspread",	A_GIMME, 0);
    class_addmethod(c, (method)hoa_freeverb_spread,  "spread",	A_GIMME, 0);
    class_addmethod(c, (method)hoa_freeverb_freeze,  "freeze",	A_GIMME, 0);
    
    class_register(CLASS_BOX, c);
    hoa_freeverb_class = c;
}

void *hoa_freeverb_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_freeverb *x = NULL;
	int	order = 4;
    
    x = (t_hoa_freeverb *)object_alloc(hoa_freeverb_class);
	if (x)
	{
        order = atom_getint(argv);
        
		x->f_ambi_freeverb = new AmbisonicFreeverb(order, sys_getblksize(), sys_getsr());
        dsp_setupjbox((t_jbox *)x, x->f_ambi_freeverb->getNumberOfInputs(), x->f_ambi_freeverb->getNumberOfOutputs());
        
        x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void hoa_freeverb_dsp(t_hoa_freeverb *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_freeverb->setVectorSize(maxvectorsize);
    x->f_ambi_freeverb->setSamplingRate(samplerate);

    object_method(dsp, gensym("dsp_add"), x, (method)hoa_freeverb_perform, 0, NULL);
}

void hoa_freeverb_perform(t_hoa_freeverb *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
    x->f_ambi_freeverb->process(ins, outs);
}

void hoa_freeverb_size(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_freeverb->setroomsize(atom_getfloat(argv));
}

void hoa_freeverb_damp(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_freeverb->setdamp(atom_getfloat(argv));
}

void hoa_freeverb_dry(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_freeverb->setDryValue(atom_getfloat(argv));
}

void hoa_freeverb_wet(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_freeverb->setWetValue(atom_getfloat(argv));
}

void hoa_freeverb_spread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_freeverb->setSpread(atom_getfloat(argv));
}

void hoa_freeverb_fspread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_freeverb->setDirectionalSpread(atom_getfloat(argv));
}

void hoa_freeverb_lspread(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_freeverb->setDiffuseSpread(atom_getfloat(argv));
}

void hoa_freeverb_freeze(t_hoa_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    x->f_ambi_freeverb->setmode(atom_getfloat(argv));
}

void hoa_freeverb_free(t_hoa_freeverb *x)
{
	dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_freeverb);
}
