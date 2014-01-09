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

typedef struct _hoa_optim
{
    t_edspobj         f_ob;
    AmbisonicOptim*   f_ambi_optim;
    long              f_mode;
} t_hoa_optim;

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv);
void hoa_optim_free(t_hoa_optim *x);

void hoa_optim_dsp(t_hoa_optim *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_optim_perform(t_hoa_optim *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
t_pd_err optim_setattr_mode(t_hoa_optim *x, t_object *attr, long ac, t_atom *av);

t_eclass *hoa_optim_class;

extern "C" void setup_hoa0x2eoptim_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.optim~", (method)hoa_optim_new, (method)hoa_optim_free, (short)sizeof(t_hoa_optim), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
    
	eclass_addmethod(c, (method)hoa_optim_dsp,     "dsp",      A_CANT, 0);
    
    CLASS_ATTR_LONG             (c, "mode", 0, t_hoa_optim, f_mode);
    CLASS_ATTR_ACCESSORS        (c, "mode", (method)NULL,(method)optim_setattr_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "mode", 0, "1");
	CLASS_ATTR_LABEL			(c, "mode", 0, "Optim mode");
	CLASS_ATTR_FILTER_CLIP      (c, "mode", 0, 2);
	CLASS_ATTR_DEFAULT			(c, "mode", 0, "0");
    
    eclass_register(CLASS_BOX, c);
    erouter_add_libary(gensym("hoa"), "hoa.library by Julien Colafrancesco, Pierre Guillot & Eliott Paris", "© 2012 - 2014  CICM | Paris 8 University", "Version 1.1");
    hoa_optim_class = c;
}

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_optim *x = NULL;
    t_binbuf *d;
	int	order = 4;
    
    if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;
    
    x = (t_hoa_optim *)eobj_new(hoa_optim_class);
    
    order = atom_getint(argv);
    x->f_mode = Hoa_InPhase_Optim;
    x->f_ambi_optim = new AmbisonicOptim(order, x->f_mode, sys_getblksize());
    eobj_dspsetup(x, x->f_ambi_optim->getNumberOfInputs(), x->f_ambi_optim->getNumberOfOutputs());
    x->f_mode = x->f_ambi_optim->getOptimMode();
    
	x->f_ob.d_misc = E_NO_INPLACE;
    ebox_attrprocess_viabinbuf(x, d);
    
   	return (x);
}

t_pd_err optim_setattr_mode(t_hoa_optim *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av)
    {
        if (atom_gettype(av) == A_SYM)
        {
            if(atom_getsym(av) == gensym("basic"))
                atom_setlong(av, Hoa_Basic_Optim);
            else if(atom_getsym(av) == gensym("maxRe"))
                atom_setlong(av, Hoa_MaxRe_Optim);
            else if(atom_getsym(av) == gensym("inPhase"))
                atom_setlong(av, Hoa_InPhase_Optim);
        }
        if (atom_gettype(av) == A_LONG)
        {
            long d = Tools::clip(long(atom_getlong(av)), 0, 2);
            x->f_ambi_optim->setOptimMode(d);
             x->f_mode = x->f_ambi_optim->getOptimMode();
        }
	}
	return 0;
}

void hoa_optim_dsp(t_hoa_optim *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_optim->setVectorSize(maxvectorsize);
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_optim_perform, 0, NULL);
}

void hoa_optim_perform(t_hoa_optim *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_optim->process(ins, outs);
}

void hoa_optim_free(t_hoa_optim *x)
{
	eobj_dspfree(x);
	delete(x->f_ambi_optim);
}
