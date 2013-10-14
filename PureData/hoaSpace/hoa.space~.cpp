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

extern "C"
{
#include "../../../PdEnhanced/Sources/pd_enhanced.h"
}
#include "../../Sources/HoaLibrary.h"


typedef struct _hoa_space
{
    t_jbox              f_ob;
    AmbisonicSpace      *f_ambi_space;
} t_hoa_space;

void *hoa_space_new(t_symbol *s, long argc, t_atom *argv);
void hoa_space_free(t_hoa_space *x);
void hoa_space_list(t_hoa_space *x, t_symbol *s, short ac, t_atom *av);

void hoa_space_dsp(t_hoa_space *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_space_perform(t_hoa_space *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_space_class;

extern "C" void setup_hoa0x2espace_tilde(void)
{
    t_eclass* c;
    c = class_new("hoa.space~", (method)hoa_space_new, (method)hoa_space_free, (short)sizeof(t_hoa_space), 0L, A_GIMME, 0);
    
    class_dspinit(c);
    class_addmethod(c, (method)hoa_space_dsp,   "dsp",      A_CANT, 0);
    class_addmethod(c, (method)hoa_space_list,  "coeffs",   A_GIMME,0);
    class_addmethod(c, (method)hoa_space_list,  "list",     A_GIMME,0);
    
	class_register(CLASS_BOX, c);
    hoa_space_class = c;
}

void *hoa_space_new(t_symbol *s, long argc, t_atom *argv)
{  
    t_hoa_space *x = NULL;
	int	number_of_channels = 4;
    
    x = (t_hoa_space *)object_alloc(hoa_space_class);
    
    number_of_channels = atom_getint(argv);
    x->f_ambi_space = new AmbisonicSpace(number_of_channels, sys_getblksize());
    dsp_setupjbox((t_jbox *)x, x->f_ambi_space->getNumberOfInputs(), x->f_ambi_space->getNumberOfOutputs());
    
	x->f_ob.z_misc = Z_NO_INPLACE;
    
	return (x);
}

void hoa_space_dsp(t_hoa_space *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_space->setVectorSize(maxvectorsize);
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_space_perform, 0, NULL);
}

void hoa_space_perform(t_hoa_space *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_space->process(ins, outs);
}

void hoa_space_list(t_hoa_space *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2)
    {
        x->f_ambi_space->setCoefficient(atom_getint(av), atom_getfloat(av+1));
    }
    else
    {
        for(int i = 0; i < ac; i++)
        {
            x->f_ambi_space->setCoefficient(i, atom_getfloat(av+i));
        }
    }
}

void hoa_space_free(t_hoa_space *x)
{
	dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_space);
}
