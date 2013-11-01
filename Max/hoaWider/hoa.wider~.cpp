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

typedef struct _HoaWider 
{
	t_pxobject			f_ob;
	AmbisonicWider*		f_AmbisonicsWider;

} t_HoaWider;

void *HoaWider_new(t_symbol *s, long argc, t_atom *argv);
void HoaWider_free(t_HoaWider *x);
void HoaWider_assist(t_HoaWider *x, void *b, long m, long a, char *s);
void HoaWider_float(t_HoaWider *x, double f);
void HoaWider_int(t_HoaWider *x, long n);

void HoaWider_dsp64(t_HoaWider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaWider_perform64(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaWider_perform64_offset(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void *HoaWider_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.wider~", (method)HoaWider_new, (method)dsp_free, (long)sizeof(t_HoaWider), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaWider_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaWider_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaWider_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaWider_assist,		"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaWider_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaWider_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaWider *x = NULL;
	int order = 4;
	x = (t_HoaWider *)object_alloc((t_class*)HoaWider_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
			
		x->f_AmbisonicsWider	= new AmbisonicWider(order,  sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsWider->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsWider->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaWider_float(t_HoaWider *x, double f)
{
	x->f_AmbisonicsWider->setWidenValue(f);
}

void HoaWider_int(t_HoaWider *x, long n)
{
	x->f_AmbisonicsWider->setWidenValue(n);
}

void HoaWider_dsp64(t_HoaWider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicsWider->setVectorSize(maxvectorsize);
	if(count[x->f_AmbisonicsWider->getNumberOfInputs() - 1])
		object_method(dsp64, gensym("dsp_add64"), x, HoaWider_perform64, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, HoaWider_perform64_offset, 0, NULL);
}

void HoaWider_perform64(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicsWider->process(ins, outs, ins[numins - 1]);
}

void HoaWider_perform64_offset(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{    
	x->f_AmbisonicsWider->process(ins, outs);
}

void HoaWider_assist(t_HoaWider *x, void *b, long m, long a, char *s)
{
	if( a == x->f_AmbisonicsWider->getNumberOfInputs() - 1)
		sprintf(s,"(Signal or float) Widen value");
	else
		sprintf(s,"(Signal) %s", x->f_AmbisonicsWider->getHarmonicsName(a).c_str());
}

void HoaWider_free(t_HoaWider *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_AmbisonicsWider;
}

