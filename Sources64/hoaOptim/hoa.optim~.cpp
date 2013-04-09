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

#include "AmbisonicOptim.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}


typedef struct _HoaOptim 
{
	t_pxobject				f_ob;			
	AmbisonicOptim*			f_AmbisonicOptim;

	int						f_ninput;
	int						f_noutput;

} t_HoaOptim;

void *HoaOptim_new(t_symbol *s, long argc, t_atom *argv);
void HoaOptim_free(t_HoaOptim *x);
void HoaOptim_assist(t_HoaOptim *x, void *b, long m, long a, char *s);
void HoaOptim_optim(t_HoaOptim *x, t_symbol *s, long argc, t_atom *argv);

void HoaOptim_dsp(t_HoaOptim *x, t_signal **sp, short *count);
t_int *HoaOptim_perform(t_int *w);

void HoaOptim_dsp64(t_HoaOptim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaOptim_perform64(t_HoaOptim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaOptim_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.optim~", (method)HoaOptim_new, (method)dsp_free, (long)sizeof(t_HoaOptim), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaOptim_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaOptim_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaOptim_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaOptim_optim,		"optim",	A_GIMME, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaOptim_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaOptim_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaOptim *x = NULL;
	int order = 4;
	std::string decodingId = "basic";
	
	if (x = (t_HoaOptim *)object_alloc((t_class*)HoaOptim_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_SYM)
			decodingId = atom_getsym(argv+1)->s_name;
			
		x->f_AmbisonicOptim	= new AmbisonicOptim(order, decodingId, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicOptim->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicOptim->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaOptim_dsp64(t_HoaOptim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicOptim->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaOptim_perform64, 0, NULL);
}

void HoaOptim_perform64(t_HoaOptim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicOptim->process(ins, outs);
}

void HoaOptim_dsp(t_HoaOptim *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_AmbisonicOptim->setVectorSize(sp[0]->s_n);
	x->f_ninput = x->f_AmbisonicOptim->getNumberOfInputs();
	x->f_noutput = x->f_AmbisonicOptim->getNumberOfOutputs();
	pointer_count = x->f_AmbisonicOptim->getNumberOfInputs() + x->f_AmbisonicOptim->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaOptim_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaOptim_perform(t_int *w)
{
	t_HoaOptim *x			= (t_HoaOptim *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninput;
	
	x->f_AmbisonicOptim->process(ins, outs);
	
	return (w + x->f_ninput + x->f_noutput + 3);
}

void HoaOptim_assist(t_HoaOptim *x, void *b, long m, long a, char *s)
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

void HoaOptim_optim(t_HoaOptim *x, t_symbol *s, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_SYM)
	{
		std::string decodingId = atom_getsym(argv)->s_name;
		x->f_AmbisonicOptim->setOptimMode(decodingId);
	}
}

void HoaOptim_free(t_HoaOptim *x)
{
	dsp_free((t_pxobject *)x);
	delete(x->f_AmbisonicOptim);
}

