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

#include "hoa.ringmod.h"


extern "C" void setup_hoa0x2eringmod_tilde(void)
{
    t_eclass* c;
    
    c = class_new("hoa.ringmod~", (method)hoa_ringmod_new, (method)hoa_ringmod_free, (short)sizeof(t_hoa_ringmod), 0L, A_GIMME, 0);
    
	class_dspinit(c);
    
	class_addmethod(c, (method)hoa_ringmod_dsp,     "dsp",      A_CANT, 0);
    
    CLASS_ATTR_LONG             (c, "compensation", 0, t_hoa_ringmod, f_encoding_compensation);
	CLASS_ATTR_CATEGORY			(c, "compensation", 0, "Behavior");
    CLASS_ATTR_STYLE            (c, "compensation", 0, "onoff");
    CLASS_ATTR_LABEL            (c, "compensation", 0, "Encoding compensation");
	CLASS_ATTR_ORDER			(c, "compensation", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "compensation", NULL, comp_set);
    
    CLASS_ATTR_DOUBLE			(c, "frequency", 0, t_hoa_ringmod, f_frequency);
	CLASS_ATTR_CATEGORY			(c, "frequency", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "frequency", 0, "Frequency (Hz)");
	CLASS_ATTR_ORDER			(c, "frequency", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "frequency", NULL, freq_set);
    
    CLASS_ATTR_DOUBLE			(c, "diffusion", 0, t_hoa_ringmod, f_diffuse_factor);
	CLASS_ATTR_CATEGORY			(c, "diffusion", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "diffusion", 0, "Diffusion factor");
	CLASS_ATTR_ORDER			(c, "diffusion", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "diffusion", NULL, diff_set);
    
    class_register(CLASS_BOX, c);
    hoa_ringmod_class = c;

}

void *hoa_ringmod_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_ringmod *x = NULL;
    t_dictionary *d;
	int	order = 4;
    bool mode = 1;
    
    x = (t_hoa_ringmod *)object_alloc(hoa_ringmod_class);
    
    order = atom_getint(argv);
    if(atom_getsym(argv+1) == gensym("no"))
        mode = 0;
    
    x->f_ambi_ringmod = new AmbisonicsRingModulation(order, mode, sys_getblksize(), sys_getsr());
    dsp_setupjbox((t_jbox *)x, x->f_ambi_ringmod->getNumberOfInputs(), x->f_ambi_ringmod->getNumberOfOutputs());
    
	x->f_ob.z_misc = Z_NO_INPLACE;
    
    d = object_dictionaryarg(argc,argv);
    attr_dictionary_process(x, d);
    
	return (x);
}

void hoa_ringmod_dsp(t_hoa_ringmod *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_ringmod->setVectorSize(maxvectorsize);
    x->f_ambi_ringmod->setSamplingRate(samplerate);
    
    if(x->f_ambi_ringmod->getMode() == Hoa_Post_Encoding)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_ringmod_perform_post, 0, NULL);
    else if(x->f_ambi_ringmod->getMode() == Hoa_No_Encoding)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_ringmod_perform_no, 0, NULL);
}

void hoa_ringmod_perform_post(t_hoa_ringmod *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_ringmod->process(ins, outs);
}

void hoa_ringmod_perform_no(t_hoa_ringmod *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_ringmod->process(ins[0], outs);
}

void hoa_ringmod_free(t_hoa_ringmod *x)
{
	dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_ringmod);
}

t_max_err diff_set(t_hoa_ringmod *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_ambi_ringmod->setDiffuseFactor(atom_getfloat(argv));
    
	x->f_diffuse_factor = x->f_ambi_ringmod->getDiffuseFactor();
	return 0;
}

t_max_err comp_set(t_hoa_ringmod *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_ambi_ringmod->setEncodingCompensation(atom_getfloat(argv));
    
	x->f_encoding_compensation = x->f_ambi_ringmod->getEncodingCompensation();
	return 0;
}

t_max_err freq_set(t_hoa_ringmod *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_ambi_ringmod->setFrequency(atom_getfloat(argv));
    
	x->f_frequency = x->f_ambi_ringmod->getFrequency();
	return 0;
}
