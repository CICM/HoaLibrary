/*
 *
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

#include "AmbisonicSixDotOne.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}

typedef struct _HoaSevenDotOne
{
	t_pxobject					f_ob;			
	AmbisonicSixDotOne		*f_AmbisonicSixDotOne;

	int							f_ninputs;
	int							f_noutputs;
} t_HoaSevenDotOne;

void *HoaSevenDotOne_new(t_symbol *s, long argc, t_atom *argv);
void HoaSevenDotOne_free(t_HoaSevenDotOne *x);
void HoaSevenDotOne_assist(t_HoaSevenDotOne *x, void *b, long m, long a, char *s);
void HoaSevenDotOne_infos(t_HoaSevenDotOne *x);

void HoaSevenDotOne_dsp(t_HoaSevenDotOne *x, t_signal **sp, short *count);
t_int *HoaSevenDotOne_perform(t_int *w);

void HoaSevenDotOne_dsp64(t_HoaSevenDotOne *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaSevenDotOne_perform64(t_HoaSevenDotOne *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaSevenDotOne_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.sixDotOne~", (method)HoaSevenDotOne_new, (method)dsp_free, (long)sizeof(t_HoaSevenDotOne), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaSevenDotOne_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaSevenDotOne_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaSevenDotOne_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaSevenDotOne_infos,		"infos",	A_GIMME, 0);

	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaSevenDotOne_class = c;
	class_alias(c, gensym("hoa.6.1~"));
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaSevenDotOne_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaSevenDotOne *x = NULL;
	int order = 4;
	double anAngle1 = 30.;
	double anAngle2 = 110.;
	if (x = (t_HoaSevenDotOne *)object_alloc((t_class*)HoaSevenDotOne_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			anAngle1	= atom_getlong(argv+1);
		else if(atom_gettype(argv+1) == A_FLOAT)
			anAngle1	= atom_getfloat(argv+1);
		if(atom_gettype(argv+2) == A_LONG)
			anAngle2	= atom_getlong(argv+2);
		else if(atom_gettype(argv+2) == A_FLOAT)
			anAngle2	= atom_getfloat(argv+2);

		x->f_AmbisonicSixDotOne	= new AmbisonicSixDotOne(order, anAngle1, anAngle2, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicSixDotOne->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicSixDotOne->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
	
	}
	return (x);
}

void HoaSevenDotOne_dsp64(t_HoaSevenDotOne *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicSixDotOne->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaSevenDotOne_perform64, 0, NULL);
}

void HoaSevenDotOne_perform64(t_HoaSevenDotOne *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicSixDotOne->process(ins, outs);
}

void HoaSevenDotOne_dsp(t_HoaSevenDotOne *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ninputs = x->f_AmbisonicSixDotOne->getNumberOfInputs();
	x->f_noutputs = x->f_AmbisonicSixDotOne->getNumberOfOutputs();
	x->f_AmbisonicSixDotOne->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_AmbisonicSixDotOne->getNumberOfInputs() + x->f_AmbisonicSixDotOne->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)malloc(pointer_count * sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)malloc(sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaSevenDotOne_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaSevenDotOne_perform(t_int *w)
{
	t_HoaSevenDotOne *x	= (t_HoaSevenDotOne *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninputs;

	x->f_AmbisonicSixDotOne->process(ins, outs);
	
	return (w + x->f_noutputs + x->f_ninputs + 3);
}

void HoaSevenDotOne_assist(t_HoaSevenDotOne *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		long harmonicIndex = 0;
		if (a != 0)
		{
			harmonicIndex = (a - 1) / 2 + 1;
			if (a % 2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex);
	}
	else
	{
		if (a == 0)
			sprintf(s,"(Signal) Center channel");
		else if (a == 1)
			sprintf(s,"(Signal) Front left channel");
		else if (a == 2)
			sprintf(s,"(Signal) Surround left channel");
		else if (a == 3)
			sprintf(s,"(Signal) Back surround channel");
		else if (a == 4)
			sprintf(s,"(Signal) Surround right channel");
		else if (a == 5)
			sprintf(s,"(Signal) Front right channel");
		else
			sprintf(s,"(Signal) Low Frequency Effects channel");
	}
}

void HoaSevenDotOne_free(t_HoaSevenDotOne *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_AmbisonicSixDotOne);
}


void HoaSevenDotOne_infos(t_HoaSevenDotOne *x)
{
	post("hoa.5.1~ informations :");
	post("Fractional order center channel : %.1f", (float)x->f_AmbisonicSixDotOne->getFractionalOrderCenter());
	post("Fractional order front channels : %.1f", (float)x->f_AmbisonicSixDotOne->getFractionalOrderFront());
	post("Fractional order surround channels : %.1f", (float)x->f_AmbisonicSixDotOne->getFractionalOrderSurround());
	post("Fractional order back surround channel : %.1f", (float)x->f_AmbisonicSixDotOne->getFractionalOrderBackSurround());
}
