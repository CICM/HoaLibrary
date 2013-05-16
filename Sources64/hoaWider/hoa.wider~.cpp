/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#include "AmbisonicsWider.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}

typedef struct _HoaWider 
{
	t_pxobject				f_ob;			
	AmbisonicsWider*		f_AmbisonicsWider;

} t_HoaWider;

void *HoaWider_new(t_symbol *s, long argc, t_atom *argv);
void HoaWider_free(t_HoaWider *x);
void HoaWider_assist(t_HoaWider *x, void *b, long m, long a, char *s);
void HoaWider_float(t_HoaWider *x, double f);
void HoaWider_int(t_HoaWider *x, long n);

void HoaWider_dsp(t_HoaWider *x, t_signal **sp, short *count);
t_int *HoaWider_perform(t_int *w);

void HoaWider_dsp64(t_HoaWider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaWider_perform64(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaWider_perform64_offset(t_HoaWider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void *HoaWider_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("hoa.wider~", (method)HoaWider_new, (method)dsp_free, (long)sizeof(t_HoaWider), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaWider_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaWider_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaWider_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaWider_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaWider_assist,		"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaWider_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
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
			
		x->f_AmbisonicsWider	= new AmbisonicsWider(order,  sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsWider->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsWider->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaWider_float(t_HoaWider *x, double f)
{
	x->f_AmbisonicsWider->setWidenValueBoth(f);
}

void HoaWider_int(t_HoaWider *x, long n)
{
	x->f_AmbisonicsWider->setWidenValueBoth(n);
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
    /*
    double in[x->f_AmbisonicsWider->getNumberOfHarmonics()];
    for (int i = 0; i < sampleframes; i++)
    {
        for(int j = 0; j < x->f_AmbisonicsWider->getNumberOfHarmonics(); j++)
            in[j] = ins[j][i];
        x->f_AmbisonicsWider->process(in, in);
        for(int j = 0; j < x->f_AmbisonicsWider->getNumberOfHarmonics(); j++)
            outs[j][i] = in[j];
    }
    */
	x->f_AmbisonicsWider->process(ins, outs);
}

void HoaWider_dsp(t_HoaWider *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_AmbisonicsWider->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_AmbisonicsWider->getNumberOfInputs() + x->f_AmbisonicsWider->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaWider_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaWider_perform(t_int *w)
{
	t_HoaWider *x		= (t_HoaWider *)(w[1]);
	long		numins	= x->f_AmbisonicsWider->getNumberOfInputs();
	long		numouts	= x->f_AmbisonicsWider->getNumberOfOutputs();
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+numins;
	
	x->f_AmbisonicsWider->process(ins, outs, ins[numins - 1]);
	
	return (w + numins + numouts + 3);
}

void HoaWider_assist(t_HoaWider *x, void *b, long m, long a, char *s)
{
	long harmonicIndex = 0;
	if (a != 0) 
	{
		harmonicIndex = (a - 1) / 2 + 1;
		if (a % 2 == 1) 
			harmonicIndex = - harmonicIndex;
	}
	if( a == x->f_AmbisonicsWider->getNumberOfInputs() - 1)
		sprintf(s,"(Signal, float or int) Widen value");
	else
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex);
}

void HoaWider_free(t_HoaWider *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_AmbisonicsWider;
}

