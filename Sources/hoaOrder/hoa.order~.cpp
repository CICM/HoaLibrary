/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "AmbisonicOrder.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

typedef struct _HoaOrder 
{
	t_pxobject					f_ob;			
	AmbisonicOrder				*f_ambiOrder;

	long						f_inputNumber;
	long						f_outputNumber;

} t_HoaOrder;

void *HoaOrder_new(t_symbol *s, long argc, t_atom *argv);
void HoaOrder_free(t_HoaOrder *x);
void HoaOrder_assist(t_HoaOrder *x, void *b, long m, long a, char *s);
void HoaOrder_float(t_HoaOrder *x, double f);
void HoaOrder_int(t_HoaOrder *x, long n);

void HoaOrder_dsp(t_HoaOrder *x, t_signal **sp, short *count);
t_int *HoaOrder_perform(t_int *w);

void HoaOrder_dsp64(t_HoaOrder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaOrder_perform64(t_HoaOrder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaOrder_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.order~", (method)HoaOrder_new, (method)HoaOrder_free, (long)sizeof(t_HoaOrder), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaOrder_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaOrder_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaOrder_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaOrder_dsp64,		"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)HoaOrder_assist,     "assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaOrder_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaOrder_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaOrder *x = NULL;
	int	orderIn = 4;
    int orderOut = 4;
    x = (t_HoaOrder *)object_alloc((t_class*)HoaOrder_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			orderIn = atom_getlong(argv);
        if(atom_gettype(argv+1) == A_LONG)
			orderOut = atom_getlong(argv+1);
		
		x->f_ambiOrder = new AmbisonicOrder(orderIn, orderOut, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiOrder->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiOrder->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaOrder_float(t_HoaOrder *x, double f)
{
	//x->f_ambiOrder->setAzimuth(f);
}

void HoaOrder_int(t_HoaOrder *x, long n)
{
	//x->f_ambiOrder->setAzimuth(n);
}

void HoaOrder_dsp64(t_HoaOrder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiOrder->setVectorSize(maxvectorsize);

	object_method(dsp64, gensym("dsp_add64"), x, HoaOrder_perform64, 0, NULL);
}

void HoaOrder_perform64(t_HoaOrder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiOrder->process(ins, outs);
}
								  							  
void HoaOrder_dsp(t_HoaOrder *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_outputNumber = x->f_ambiOrder->getNumberOfOutputs();
	x->f_inputNumber = x->f_ambiOrder->getNumberOfInputs();
	x->f_ambiOrder->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_inputNumber + x->f_outputNumber + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
    dsp_addv(HoaOrder_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaOrder_perform(t_int *w)
{
	t_HoaOrder *x			= (t_HoaOrder *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiOrder->process(ins, outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaOrder_assist(t_HoaOrder *x, void *b, long m, long a, char *s)
{

    long harmonicIndex = 0;
	if (a == 0)
		harmonicIndex = 0;
	else {
		harmonicIndex = (int)floor((float)((int)(a - 1) / 2)) + 1;
		if (a%2 == 1)
			harmonicIndex = - harmonicIndex;
	}
    sprintf(s,"(Signal) Harmonic %ld", harmonicIndex); 
}


void HoaOrder_free(t_HoaOrder *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_ambiOrder);
}

