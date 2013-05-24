/*
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

#include "AmbisonicsDiffuser.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}


typedef struct _HoaDiffuser 
{
	t_pxobject				f_ob;			
	AmbisonicsDiffuser*		f_AmbisonicsDiffuser;

	int						f_ninput;
	int						f_noutput;
} t_HoaDiffuser;

void *HoaDiffuser_new(t_symbol *s, long argc, t_atom *argv);
void HoaDiffuser_free(t_HoaDiffuser *x);
void HoaDiffuser_assist(t_HoaDiffuser *x, void *b, long m, long a, char *s);
void HoaDiffuser_float(t_HoaDiffuser *x, double f);
void HoaDiffuser_int(t_HoaDiffuser *x, long n);

void HoaDiffuser_dsp(t_HoaDiffuser *x, t_signal **sp, short *count);
t_int *HoaDiffuser_perform(t_int *w);

void HoaDiffuser_dsp64(t_HoaDiffuser *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaDiffuser_perform64(t_HoaDiffuser *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaDiffuser_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.diffuser~", (method)HoaDiffuser_new, (method)dsp_free, (long)sizeof(t_HoaDiffuser), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaDiffuser_dsp,         "dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaDiffuser_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaDiffuser_assist,		"assist",	A_CANT, 0);
    class_addmethod(c, (method)HoaDiffuser_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaDiffuser_int,         "int",		A_LONG, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaDiffuser_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaDiffuser_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaDiffuser *x = NULL;
	int order = 4;
    
	x = (t_HoaDiffuser *)object_alloc((t_class*)HoaDiffuser_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
			
		x->f_AmbisonicsDiffuser	= new AmbisonicsDiffuser(order, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsDiffuser->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsDiffuser->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaDiffuser_float(t_HoaDiffuser *x, double f)
{
	x->f_AmbisonicsDiffuser->setDiffuseFactor(f);
}

void HoaDiffuser_int(t_HoaDiffuser *x, long n)
{
	x->f_AmbisonicsDiffuser->setDiffuseFactor(n);
}

void HoaDiffuser_dsp64(t_HoaDiffuser *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicsDiffuser->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaDiffuser_perform64, 0, NULL);
}

void HoaDiffuser_perform64(t_HoaDiffuser *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicsDiffuser->process(ins, outs);
}

void HoaDiffuser_dsp(t_HoaDiffuser *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_AmbisonicsDiffuser->setVectorSize(sp[0]->s_n);
	x->f_ninput = x->f_AmbisonicsDiffuser->getNumberOfInputs();
	x->f_noutput = x->f_AmbisonicsDiffuser->getNumberOfOutputs();
	pointer_count = x->f_AmbisonicsDiffuser->getNumberOfInputs() + x->f_AmbisonicsDiffuser->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaDiffuser_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaDiffuser_perform(t_int *w)
{
	t_HoaDiffuser *x			= (t_HoaDiffuser *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninput;
	
	x->f_AmbisonicsDiffuser->process(ins, outs);
	
	return (w + x->f_ninput + x->f_noutput + 3);
}

void HoaDiffuser_assist(t_HoaDiffuser *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) Harmonic %ld", x->f_AmbisonicsDiffuser->getHarmonicIndex(a));
}

void HoaDiffuser_free(t_HoaDiffuser *x)
{
	dsp_free((t_pxobject *)x);
	delete(x->f_AmbisonicsDiffuser);
}

