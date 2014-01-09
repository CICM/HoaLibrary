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

typedef struct _hoa_space_t
{
    t_edspobj           f_ob;
    AmbisonicSpace      *f_ambi_space;
} t_hoa_space_t;

void *hoa_space_t_new(t_symbol *s, long argc, t_atom *argv);
void hoa_space_t_free(t_hoa_space_t *x);
void hoa_space_t_list(t_hoa_space_t *x, t_symbol *s, short ac, t_atom *av);

void hoa_space_t_dsp(t_hoa_space_t *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_space_t_perform(t_hoa_space_t *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_space_t_class;

extern "C" void setup_hoa0x2espace_tilde(void)
{
    t_eclass* c;
    c = eclass_new("hoa.space~", (method)hoa_space_t_new, (method)hoa_space_t_free, (short)sizeof(t_hoa_space_t), 0L, A_GIMME, 0);
    
    eclass_dspinit(c);
    eclass_addmethod(c, (method)hoa_space_t_dsp,   "dsp",      A_CANT, 0);
    eclass_addmethod(c, (method)hoa_space_t_list,  "coeffs",   A_GIMME,0);
    eclass_addmethod(c, (method)hoa_space_t_list,  "list",     A_GIMME,0);
    
	eclass_register(CLASS_BOX, c);
    erouter_add_libary(gensym("hoa"), "hoa.library by Julien Colafrancesco, Pierre Guillot & Eliott Paris", "© 2012 - 2014  CICM | Paris 8 University", "Version 1.1");
    hoa_space_t_class = c;
}

void *hoa_space_t_new(t_symbol *s, long argc, t_atom *argv)
{  
    t_hoa_space_t *x = NULL;
	int	number_of_channels = 4;
    
    x = (t_hoa_space_t *)eobj_new(hoa_space_t_class);
    
    number_of_channels = atom_getint(argv);
    x->f_ambi_space = new AmbisonicSpace(number_of_channels, sys_getblksize());
    eobj_dspsetup(x, x->f_ambi_space->getNumberOfInputs(), x->f_ambi_space->getNumberOfOutputs());
    
	x->f_ob.d_misc = E_NO_INPLACE;
    
	return (x);
}

void hoa_space_t_dsp(t_hoa_space_t *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_space->setVectorSize(maxvectorsize);
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_space_t_perform, 0, NULL);
}

void hoa_space_t_perform(t_hoa_space_t *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_space->process(ins, outs);
}

void hoa_space_t_list(t_hoa_space_t *x, t_symbol *s, short ac, t_atom *av)
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

void hoa_space_t_free(t_hoa_space_t *x)
{
	eobj_dspfree(x);
	delete(x->f_ambi_space);
}
