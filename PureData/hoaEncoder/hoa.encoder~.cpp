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

typedef struct _hoa_encoder
{
    t_edspobj         f_ob;
    AmbisonicEncoder* f_ambi_encoder;
} t_hoa_encoder;

void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_encoder_free(t_hoa_encoder *x);

void hoa_encoder_dsp(t_hoa_encoder *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_encoder_perform(t_hoa_encoder *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_encoder_class;

extern "C" void setup_hoa0x2eencoder_tilde(void)
{
    t_eclass *c;
    c = eclass_new("hoa.encoder~", (method)hoa_encoder_new,(method)hoa_encoder_free, sizeof(t_hoa_encoder), 0L, A_GIMME, 0);
    
    eclass_dspinit(c);
    
    eclass_addmethod(c, (method)hoa_encoder_dsp,     "dsp",		A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_post();
    hoa_encoder_class = c;
}

void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_encoder *x = NULL;
	int	order = 4;
    
    x = (t_hoa_encoder *)eobj_new(hoa_encoder_class);
	if (x)
	{
        order = atom_getint(argv);
        
		x->f_ambi_encoder = new AmbisonicEncoder(order, sys_getblksize());
        eobj_dspsetup(x, x->f_ambi_encoder->getNumberOfInputs(), x->f_ambi_encoder->getNumberOfOutputs());
        
        x->f_ob.d_misc = E_NO_INPLACE;
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
	eobj_dspfree(x);
	delete(x->f_ambi_encoder);
}
