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

#include "hoa.encoder.h"

extern "C" void setup_hoa0x2eencoder_tilde(void)
{
    t_eclass *c;
    c = class_new("hoa.encoder~", (method)hoa_encoder_new,(method)hoa_encoder_free, sizeof(t_hoa_encoder), 0L, A_GIMME, 0);
    
    class_dspinit(c);
    
    class_addmethod(c, (method)hoa_encoder_dsp,     "dsp",		A_CANT, 0);
    
    class_register(CLASS_BOX, c);
    hoa_encoder_class = c;
}

void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_encoder *x = NULL;
	int	order = 4;
    
    x = (t_hoa_encoder *)object_alloc(hoa_encoder_class);
	if (x)
	{
        order = atom_getint(argv);
        
		x->f_ambi_encoder = new AmbisonicEncoder(order, sys_getblksize());
        dsp_setupjbox((t_jbox *)x, x->f_ambi_encoder->getNumberOfInputs(), x->f_ambi_encoder->getNumberOfOutputs());
        
        x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void hoa_encoder_dsp(t_hoa_encoder *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_encoder->setVectorSize(maxvectorsize);
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_encoder_perform, 0, NULL);
}

void hoa_encoder_perform(t_hoa_encoder *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_encoder->process(ins[0], outs, ins[1]);
}

void hoa_encoder_free(t_hoa_encoder *x)
{
	dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_encoder);
}
