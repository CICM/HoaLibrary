/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Eliott Paris, Universite Paris 8
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

#include "GrainPlug.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "../hoaHeader.h"
}

int postons = 0;

typedef struct _HoaGranulate 
{
	t_pxobject			f_ob;
	GrainPlug			*f_ambiGranulate;
	
	long				f_inputNumber;
	long				f_outputNumber;
} t_HoaGranulate;


void *HoaGranulate_new(t_symbol *s, long argc, t_atom *argv);
void HoaGranulate_free(t_HoaGranulate *x);
void HoaGranulate_assist(t_HoaGranulate *x, void *b, long m, long a, char *s);

void HoaGranulate_float(t_HoaGranulate *x, double f);
void HoaGranulate_int(t_HoaGranulate *x, long n);

void HoaGranulate_dsp(t_HoaGranulate *x, t_signal **sp, short *count);
t_int *HoaGranulate_perform(t_int *w);
t_int *HoaGranulate_performOffset(t_int *w);
t_int *HoaGranulate_performVec(t_int *w);
t_int *HoaGranulate_performOffsetVec(t_int *w);

void HoaGranulate_dsp64(t_HoaGranulate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaGranulate_perform64(t_HoaGranulate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaGranulate_perform64Offset(t_HoaGranulate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaGranulate_perform64vec(t_HoaGranulate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaGranulate_perform64Offsetvec(t_HoaGranulate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *HoaGranulate_class;
    

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.granulate~", (method)HoaGranulate_new, (method)HoaGranulate_free, (long)sizeof(t_HoaGranulate), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaGranulate_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaGranulate_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaGranulate_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaGranulate_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaGranulate_assist,     "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	HoaGranulate_class = c;

	if(class_findbyname(CLASS_NOBOX, gensym("hoa.loader")) == NULL)
	{
		if(postons == 0)
		{
			hoa_postcredits();
			postons = 1;
		}
	}
	return 0;
}

void *HoaGranulate_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaGranulate *x = NULL;
	int	order = 4;
	std::string mode = "basic";
    x = (t_HoaGranulate *)object_alloc(HoaGranulate_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		if(atom_gettype(argv + 1) == A_SYM)
			mode = atom_getsym(argv + 1)->s_name;
		
		x->f_ambiGranulate = new GrainPlug(order);
        x->f_ambiGranulate->setVectorSize(sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiGranulate->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiGranulate->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaGranulate_float(t_HoaGranulate *x, double f)
{
}

void HoaGranulate_int(t_HoaGranulate *x, long n)
{
}

void HoaGranulate_dsp64(t_HoaGranulate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiGranulate->setVectorSize(maxvectorsize);
	x->f_inputNumber = x->f_ambiGranulate->getNumberOfInputs();
    object_method(dsp64, gensym("dsp_add64"), x, HoaGranulate_perform64vec, 0, NULL);
}

void HoaGranulate_perform64(t_HoaGranulate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	//x->f_ambiGranulate->process(ins[0], outs, ins[1]);
}


void HoaGranulate_dsp(t_HoaGranulate *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ambiGranulate->setVectorSize(sp[0]->s_n);
	x->f_inputNumber = x->f_ambiGranulate->getNumberOfInputs();
	x->f_outputNumber = x->f_ambiGranulate->getNumberOfOutputs();
    pointer_count = x->f_outputNumber + 2 + x->f_inputNumber;
    
    sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
    for(i = 0; i < pointer_count; i++)
        sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
    
    sigvec[0] = (t_int *)x;
    sigvec[1] = (t_int *)sp[0]->s_n;
    for(i = 2; i < pointer_count; i++)
        sigvec[i] = (t_int *)sp[i - 2]->s_vec;
    dsp_addv(HoaGranulate_perform, pointer_count, (void **)sigvec);
    
    free(sigvec);
}

t_int *HoaGranulate_perform(t_int *w)
{
	t_HoaGranulate *x			= (t_HoaGranulate *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	//x->f_ambiGranulate->process(ins[0], outs, ins[1]);

	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaGranulate_assist(t_HoaGranulate *x, void *b, long m, long a, char *s)
{
	
	if (m == ASSIST_INLET) 
	{
		if(a == 0)
            sprintf(s,"(Signal) Input");
        else
            sprintf(s,"(Signal or float) Azimuth");
	} 
	else 
	{
		long harmonicIndex = 0;
		if (a == 0)
			harmonicIndex = 0;
		else 
		{
			harmonicIndex = (a - 1) / 2 + 1;
			if (a % 2 == 1) 
				harmonicIndex = - harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %ld", harmonicIndex); 			
	}
}


void HoaGranulate_free(t_HoaGranulate *x) 
{
	dsp_free((t_pxobject *)x);
	delete(x->f_ambiGranulate);
}

