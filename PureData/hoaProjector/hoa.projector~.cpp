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

typedef struct _hoa_projector
{
    t_edspobj           f_ob;
    AmbisonicProjector* f_ambi_projector;
} t_hoa_projector;

void *hoa_projector_new(t_symbol *s, long argc, t_atom *argv);
void hoa_projector_free(t_hoa_projector *x);

void hoa_projector_dsp(t_hoa_projector *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_projector_perform(t_hoa_projector *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_projector_class;

extern "C" void setup_hoa0x2eprojector_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.projector~", (method)hoa_projector_new, (method)hoa_projector_free, (short)sizeof(t_hoa_projector), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
    
	eclass_addmethod(c, (method)hoa_projector_dsp,     "dsp",      A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_post();
    hoa_projector_class = c;
}

void *hoa_projector_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_projector *x = NULL;
	int	order = 4;
    int microphones = 10;
    
    x = (t_hoa_projector *)eobj_new(hoa_projector_class);
    
    order = atom_getint(argv);
    microphones = atom_getint(argv+1);
    x->f_ambi_projector = new AmbisonicProjector(order, microphones, sys_getblksize());
    eobj_dspsetup(x, x->f_ambi_projector->getNumberOfInputs(), x->f_ambi_projector->getNumberOfOutputs());
    
	return (x);
}

void hoa_projector_dsp(t_hoa_projector *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_projector->setVectorSize(maxvectorsize);
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_projector_perform, 0, NULL);
}

void hoa_projector_perform(t_hoa_projector *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
    x->f_ambi_projector->process(ins, outs);
}

void hoa_projector_free(t_hoa_projector *x)
{
	eobj_dspfree(x);
	delete x->f_ambi_projector;
}
