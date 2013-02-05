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

#include "AmbisonicHalo.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

typedef struct _HoaHalo 
{
	t_pxobject					f_ob;			
	AmbisonicHalo				*f_ambiHalo;

	long						f_inputNumber;
	long						f_outputNumber;

} t_HoaHalo;

void *HoaHalo_new(t_symbol *s, long argc, t_atom *argv);
void HoaHalo_free(t_HoaHalo *x);
void HoaHalo_assist(t_HoaHalo *x, void *b, long m, long a, char *s);
void HoaHalo_float(t_HoaHalo *x, double f);
void HoaHalo_int(t_HoaHalo *x, long n);

void HoaHalo_dsp(t_HoaHalo *x, t_signal **sp, short *count);
t_int *HoaHalo_perform_azimuth_spread(t_int *w);
t_int *HoaHalo_perform_azimuth(t_int *w);
t_int *HoaHalo_perform_spread(t_int *w);
t_int *HoaHalo_perform(t_int *w);

void HoaHalo_dsp64(t_HoaHalo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaHalo_perform64_azimuth_spread(t_HoaHalo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaHalo_perform64_azimuth(t_HoaHalo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaHalo_perform64_spread(t_HoaHalo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaHalo_perform64(t_HoaHalo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaHalo_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.halo~", (method)HoaHalo_new, (method)HoaHalo_free, (long)sizeof(t_HoaHalo), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaHalo_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaHalo_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaHalo_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaHalo_dsp64,		"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)HoaHalo_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaHalo_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaHalo_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaHalo *x = NULL;
	int	order = 4;
	if (x = (t_HoaHalo *)object_alloc((t_class*)HoaHalo_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_ambiHalo = new AmbisonicHalo(order, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiHalo->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiHalo->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaHalo_float(t_HoaHalo *x, double f)
{
	//x->f_ambiHalo->setAzimuth(f);
}

void HoaHalo_int(t_HoaHalo *x, long n)
{
	//x->f_ambiHalo->setAzimuth(n);
}

void HoaHalo_dsp64(t_HoaHalo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiHalo->setVectorSize(maxvectorsize);

	if(count[x->f_ambiHalo->getNumberOfInputs() - 1] && count[x->f_ambiHalo->getNumberOfInputs() - 2])
		object_method(dsp64, gensym("dsp_add64"), x, HoaHalo_perform64_azimuth_spread, 0, NULL);
	else if(count[x->f_ambiHalo->getNumberOfInputs() - 2])
		object_method(dsp64, gensym("dsp_add64"), x, HoaHalo_perform64_azimuth, 0, NULL);
	else if(count[x->f_ambiHalo->getNumberOfInputs() - 1])
		object_method(dsp64, gensym("dsp_add64"), x, HoaHalo_perform64_spread, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, HoaHalo_perform64, 0, NULL);
}

void HoaHalo_perform64_azimuth_spread(t_HoaHalo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiHalo->process_block_azimuth_spread(ins, outs, ins[numins - 2], ins[numins - 1]);
}

void HoaHalo_perform64_azimuth(t_HoaHalo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiHalo->process_block_azimuth(ins, outs, ins[numins - 2]);
}

void HoaHalo_perform64_spread(t_HoaHalo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiHalo->process_block_spread(ins, outs, ins[numins - 1]);
}

void HoaHalo_perform64(t_HoaHalo *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiHalo->process_block(ins, outs);
}
								  							  
void HoaHalo_dsp(t_HoaHalo *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_outputNumber = x->f_ambiHalo->getNumberOfOutputs();
	x->f_inputNumber = x->f_ambiHalo->getNumberOfInputs();
	x->f_ambiHalo->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_inputNumber + x->f_outputNumber + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	if(count[x->f_ambiHalo->getNumberOfInputs() - 1] && count[x->f_ambiHalo->getNumberOfInputs() - 2])
		dsp_addv(HoaHalo_perform_azimuth_spread, pointer_count, (void **)sigvec);
	else if(count[x->f_inputNumber - 2])
		dsp_addv(HoaHalo_perform_azimuth, pointer_count, (void **)sigvec);
	else if(count[x->f_inputNumber - 1])
		dsp_addv(HoaHalo_perform_spread, pointer_count, (void **)sigvec);
	else
		dsp_addv(HoaHalo_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaHalo_perform_azimuth_spread(t_int *w)
{
	t_HoaHalo *x			= (t_HoaHalo *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;

	x->f_ambiHalo->process_block_azimuth_spread(ins, outs, ins[x->f_inputNumber - 2], ins[x->f_inputNumber - 1]);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

t_int *HoaHalo_perform_spread(t_int *w)
{
	t_HoaHalo *x			= (t_HoaHalo *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiHalo->process_block_spread(ins, outs, ins[x->f_inputNumber - 1]);

	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

t_int *HoaHalo_perform_azimuth(t_int *w)
{
	t_HoaHalo *x			= (t_HoaHalo *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiHalo->process_block_spread(ins, outs, ins[x->f_inputNumber - 2]);

	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

t_int *HoaHalo_perform(t_int *w)
{
	t_HoaHalo *x			= (t_HoaHalo *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiHalo->process_block(ins, outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaHalo_assist(t_HoaHalo *x, void *b, long m, long a, char *s)
{
	long harmonicIndex = 0;
	if(a != x->f_inputNumber-1)
		sprintf(s,"(Signal or float) Azimuth");
	else
	{
		if (a == 0)
			harmonicIndex = 0;
		else {
			harmonicIndex = (int)floor((float)((int)(a - 1) / 2)) + 1;
			if (a%2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex); 
	}	
}


void HoaHalo_free(t_HoaHalo *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_ambiHalo);
}

