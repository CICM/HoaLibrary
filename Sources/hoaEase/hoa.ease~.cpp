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

#include "AmbisonicPolyEase.h"

extern "C"
{
	#include "ext.h"
	#include "ext_obex.h"
	#include "z_dsp.h"
}


typedef struct _HoaTool 
{
	t_pxobject				f_ob;			
	AmbisonicPolyEase*		f_AmbisonicPolyEase;

	int						f_ninput;
	int						f_noutput;

} t_HoaTool;

void *HoaTool_new(t_symbol *s, long argc, t_atom *argv);
void HoaTool_free(t_HoaTool *x);
void HoaTool_assist(t_HoaTool *x, void *b, long m, long a, char *s);
void HoaTool_pol(t_HoaTool *x, t_symbol *s, long argc, t_atom *argv);
void HoaTool_car(t_HoaTool *x, t_symbol *s, long argc, t_atom *argv);

void HoaTool_dsp(t_HoaTool *x, t_signal **sp, short *count);
t_int *HoaTool_perform(t_int *w);

void HoaTool_dsp64(t_HoaTool *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaTool_perform64(t_HoaTool *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaTool_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.ease~", (method)HoaTool_new, (method)dsp_free, (long)sizeof(t_HoaTool), 0L, A_GIMME, 0);
	
	//class_addmethod(c, (method)HoaTool_dsp,         "dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaTool_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaTool_assist,		"assist",	A_CANT, 0);
    class_addmethod(c, (method)HoaTool_pol,         "pol",      A_GIMME, 0);
	class_addmethod(c, (method)HoaTool_car,         "car",      A_GIMME, 0);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaTool_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaTool_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaTool *x = NULL;
	int order = 4;
    int numberOfSources = 1;
    
    x = (t_HoaTool *)object_alloc((t_class*)HoaTool_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			numberOfSources = atom_getlong(argv+1);
        
		x->f_AmbisonicPolyEase	= new AmbisonicPolyEase(order, numberOfSources, sys_getblksize());
        dsp_setup((t_pxobject *)x, x->f_AmbisonicPolyEase->getNumberOfInputs());
        
		for (int i = 0; i < x->f_AmbisonicPolyEase->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaTool_dsp64(t_HoaTool *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicPolyEase->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaTool_perform64, 0, NULL);
}

void HoaTool_perform64(t_HoaTool *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicPolyEase->process(ins, outs);
}

void HoaTool_dsp(t_HoaTool *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_AmbisonicPolyEase->setVectorSize(sp[0]->s_n);
	x->f_ninput = x->f_AmbisonicPolyEase->getNumberOfInputs();
	x->f_noutput = x->f_AmbisonicPolyEase->getNumberOfOutputs();
	pointer_count = x->f_AmbisonicPolyEase->getNumberOfInputs() + x->f_AmbisonicPolyEase->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaTool_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaTool_perform(t_int *w)
{
	t_HoaTool *x			= (t_HoaTool *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninput;
	
	x->f_AmbisonicPolyEase->process(ins, outs);
	
	return (w + x->f_ninput + x->f_noutput + 3);
}

void HoaTool_assist(t_HoaTool *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
    {
        sprintf(s,"(Signal) Source %ld", a);
    }
    else
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
}

void HoaTool_pol(t_HoaTool *x, t_symbol *s, long argc, t_atom *argv)
{
	x->f_AmbisonicPolyEase->setPolarCoordinates(atom_getlong(argv), atom_getfloat(argv+1), atom_getfloat(argv+2));
}

void HoaTool_car(t_HoaTool *x, t_symbol *s, long argc, t_atom *argv)
{
	x->f_AmbisonicPolyEase->setCartesianCoordinates(atom_getlong(argv), atom_getfloat(argv+1), atom_getfloat(argv+2));
}

void HoaTool_free(t_HoaTool *x)
{
	dsp_free((t_pxobject *)x);
	delete(x->f_AmbisonicPolyEase);
}

