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
	#include "z_dsp.h"
}

typedef struct _HoaProjector
{
	t_pxobject					f_ob;			
	AmbisonicProjector			*f_AmbisonicsProjector;

	int							f_ninputs;
	int							f_noutputs;
} t_HoaProjector;

void *HoaProjector_new(t_symbol *s, long argc, t_atom *argv);
void HoaProjector_free(t_HoaProjector *x);
void HoaProjector_assist(t_HoaProjector *x, void *b, long m, long a, char *s);

void HoaProjector_dsp64(t_HoaProjector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaProjector_perform64(t_HoaProjector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaProjector_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.projector~", (method)HoaProjector_new, (method)dsp_free, (long)sizeof(t_HoaProjector), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaProjector_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaProjector_assist,			"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaProjector_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaProjector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaProjector *x = NULL;
	int order = 4, outputs = 9;
    x = (t_HoaProjector *)object_alloc((t_class*)HoaProjector_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			outputs	= atom_getlong(argv+1);
		
		x->f_AmbisonicsProjector	= new AmbisonicProjector(order, outputs, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsProjector->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsProjector->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
	
	}
	return (x);
}

void HoaProjector_dsp64(t_HoaProjector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicsProjector->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaProjector_perform64, 0, NULL);
}

void HoaProjector_perform64(t_HoaProjector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicsProjector->process(ins, outs);
}

void HoaProjector_assist(t_HoaProjector *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		sprintf(s,"(Signal) %s", x->f_AmbisonicsProjector->getInputName(a).c_str());
	}
	else 
		sprintf(s,"(Signal) %s", x->f_AmbisonicsProjector->getLoudspeakerName(a).c_str());
}

void HoaProjector_free(t_HoaProjector *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_AmbisonicsProjector);
}

