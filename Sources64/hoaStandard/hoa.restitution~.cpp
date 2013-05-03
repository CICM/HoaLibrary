/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#include "AmbisonicsRestitution.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}

typedef struct _HoaStereo
{
	t_pxobject					f_ob;			
	AmbisonicsRestitution			*f_AmbisonicStereo;
} t_HoaStereo;

void *HoaStereo_new(t_symbol *s, long argc, t_atom *argv);
void HoaStereo_free(t_HoaStereo *x);
void HoaStereo_assist(t_HoaStereo *x, void *b, long m, long a, char *s);

void HoaStereo_dsp(t_HoaStereo *x, t_signal **sp, short *count);
t_int *HoaStereo_perform(t_int *w);

void HoaStereo_dsp64(t_HoaStereo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaStereo_perform64(t_HoaStereo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaStereo_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.restitution~", (method)HoaStereo_new, (method)HoaStereo_free, (long)sizeof(t_HoaStereo), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaStereo_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaStereo_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaStereo_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaStereo_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaStereo_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaStereo *x = NULL;
	int order = 4;
	double anAngle = 60.;
    x = (t_HoaStereo *)object_alloc((t_class*)HoaStereo_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		
		if(atom_gettype(argv+1) == A_LONG)
			anAngle	= atom_getlong(argv+1);
		else if(atom_gettype(argv+1) == A_FLOAT)
			anAngle	= atom_getfloat(argv+1);
		
		x->f_AmbisonicStereo	= new AmbisonicsRestitution(order, anAngle, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicStereo->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicStereo->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaStereo_dsp64(t_HoaStereo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicStereo->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaStereo_perform64, 0, NULL);
}

void HoaStereo_perform64(t_HoaStereo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicStereo->process(ins, outs);
}

void HoaStereo_dsp(t_HoaStereo *x, t_signal **sp, short *count)
{
	x->f_AmbisonicStereo->setVectorSize(sp[0]->s_n);
	int pointer_count = x->f_AmbisonicStereo->getNumberOfInputs() + x->f_AmbisonicStereo->getNumberOfOutputs() + 3;
	
	t_int** sigvec  = (t_int **)malloc(pointer_count * sizeof(t_int *));
	for(int i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)malloc(sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)x->f_AmbisonicStereo->getNumberOfInputs();
	sigvec[2] = (t_int *)x->f_AmbisonicStereo->getNumberOfOutputs();
	for(int i = 3; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 3]->s_vec;
	
	dsp_addv(HoaStereo_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaStereo_perform(t_int *w)
{
	t_HoaStereo *x		= (t_HoaStereo *)(w[1]);
	long		numins	= (long)(w[2]);
	long		numouts	= (long)(w[3]);
	t_float		**ins	= (t_float **)w+4;
	t_float		**outs	= (t_float **)w+4+numins;

	x->f_AmbisonicStereo->process(ins, outs);
	
	return (w + numins + numouts + 4);
}

void HoaStereo_assist(t_HoaStereo *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
        sprintf(s,"(Signal) Harmonic %ld", x->f_AmbisonicStereo->getHarmonicIndex(a));
	}
	else 
	{
		if (a == 0)
			sprintf(s,"(Signal) Left channel");
		if (a == 1)
			sprintf(s,"(Signal) Right channel");
	}
}

void HoaStereo_free(t_HoaStereo *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_AmbisonicStereo);
}

