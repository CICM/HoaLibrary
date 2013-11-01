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

#include "../../Sources/HoaLibrary.h"

extern "C"
{
#include "ext.h"							
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "z_dsp.h"
}

typedef struct _HoaSpace
{
	t_pxobject					f_ob;
    t_object                    *f_patcher;
    t_object                    *f_patcherview;
    t_object                    *f_ui;
	AmbisonicSpace				*f_ambiSpace;

	long						f_inputNumber;
	long						f_outputNumber;

} t_HoaSpace;

void *HoaSpace_new(t_symbol *s, long argc, t_atom *argv);
void HoaSpace_free(t_HoaSpace* x);
void HoaSpace_assist(t_HoaSpace* x, void *b, long m, long a, char *s);
void HoaSpace_list(t_HoaSpace *x, t_symbol *s, short ac, t_atom *av);

void HoaSpace_dsp64(t_HoaSpace* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaSpace_perform64(t_HoaSpace* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaSpace_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.space~", (method)HoaSpace_new, (method)HoaSpace_free, (long)sizeof(t_HoaSpace), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaSpace_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaSpace_assist,     "assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaSpace_list,       "coeffs",   A_GIMME,0);
    class_addmethod(c, (method)HoaSpace_list,       "list",     A_GIMME,0);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaSpace_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaSpace_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaSpace* x = NULL;
	int	anNumberOfMicrophones = 8;
    
    x = (t_HoaSpace*)object_alloc((t_class*)HoaSpace_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			anNumberOfMicrophones = atom_getlong(argv);
		
		x->f_ambiSpace = new AmbisonicSpace(anNumberOfMicrophones, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiSpace->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiSpace->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaSpace_list(t_HoaSpace *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2 && atom_gettype(av) == A_LONG && atom_gettype(av+1) == A_FLOAT)
        x->f_ambiSpace->setCoefficient(atom_getlong(av), atom_getfloat(av+1));
    else if(atom_gettype(av) == A_FLOAT)
    {
        for(int i = 0; i < ac; i++)
        {
            if(i < x->f_ambiSpace->getNumberOfLoudspeakers() && atom_gettype(av+i) == A_FLOAT)
                x->f_ambiSpace->setCoefficient(i, atom_getfloat(av+i));
        }
    }
    if(x->f_patcher)
    {
        t_atom* values;
        long nValues = x->f_ambiSpace->getNumberOfLoudspeakers();
        values = new t_atom[nValues];
        for(int i = 0; i < nValues; i++)
            atom_setfloat(values+i, x->f_ambiSpace->getCoefficient(i));
        
        object_setvalueof(x->f_ui, nValues, values);
        free(values);
    }
}

void HoaSpace_dsp64(t_HoaSpace* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiSpace->setVectorSize(maxvectorsize);
    object_method(dsp64, gensym("dsp_add64"), x, HoaSpace_perform64, 0, NULL);
}

void HoaSpace_perform64(t_HoaSpace* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiSpace->process(ins, outs);
}

void HoaSpace_assist(t_HoaSpace* x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_ambiSpace->getLoudspeakerName(a).c_str());
}

void HoaSpace_free(t_HoaSpace* x)
{
	dsp_free((t_pxobject *)x);
    if (x->f_patcher)
		object_free(x->f_patcher);
	free(x->f_ambiSpace);
}



