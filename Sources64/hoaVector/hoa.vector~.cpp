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

#include "AmbisonicVector.h"

extern "C"
{
#include "ext.h"							
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "z_dsp.h"
}

typedef struct _HoaVectore
{
	t_pxobject					f_ob;
	Ambisonicvector				*f_ambiVector;

	long						f_inputNumber;
	long						f_outputNumber;
    long                        f_mode;
} t_HoaVectore;

void *HoaVector_new(t_symbol *s, long argc, t_atom *argv);
void HoaVector_free(t_HoaVectore* x);
void HoaVector_assist(t_HoaVectore* x, void *b, long m, long a, char *s);
t_max_err mode_set(t_HoaVectore *x, t_object *attr, long ac, t_atom *av);

void HoaVector_dsp(t_HoaVectore* x, t_signal **sp, short *count);
t_int *HoaVector_perform(t_int *w);

void HoaVector_dsp64(t_HoaVectore* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaVector_perform64(t_HoaVectore* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaVector_class;

int C74_EXPORT main(void)
{	
    common_symbols_init();
	t_class *c;
	
	c = class_new("hoa.vector~", (method)HoaVector_new, (method)HoaVector_free, (long)sizeof(t_HoaVectore), 0L, A_GIMME, 0);

	class_addmethod(c, (method)HoaVector_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaVector_dsp64,     "dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaVector_assist,    "assist",	A_CANT, 0);
    
    CLASS_ATTR_LONG					(c, "mode", 0, t_HoaVectore, f_mode);
	CLASS_ATTR_CATEGORY				(c, "mode", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "mode", 0, "1");
    CLASS_ATTR_ENUMINDEX            (c, "mode", 0, "Polar \" Cartesian");
    CLASS_ATTR_ACCESSORS            (c, "mode", NULL, mode_set);
	CLASS_ATTR_LABEL                (c, "mode", 0, "Coordinates type");
	CLASS_ATTR_DEFAULT				(c, "mode", 0, "1");
	CLASS_ATTR_SAVE					(c, "mode", 1);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaVector_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaVector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaVectore* x = NULL;
	int	anNumberOfMicrophones = 8;
    t_symbol* mode = gensym("polar");
    x = (t_HoaVectore*)object_alloc((t_class*)HoaVector_class);
	if (x)
	{
		if(argc > 0 && atom_gettype(argv) == A_LONG)
			anNumberOfMicrophones = atom_getlong(argv);
		if(argc > 1 && atom_gettype(argv+1) == A_SYM)
            mode = atom_getsym(argv+1);
		x->f_ambiVector = new Ambisonicvector(anNumberOfMicrophones, mode->s_name, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiVector->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiVector->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaVector_dsp64(t_HoaVectore* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiVector->setVectorSize(maxvectorsize);
    object_method(dsp64, gensym("dsp_add64"), x, HoaVector_perform64, 0, NULL);
}

void HoaVector_perform64(t_HoaVectore* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiVector->process(ins, outs);
}

								  
								  
void HoaVector_dsp(t_HoaVectore* x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_outputNumber = x->f_ambiVector->getNumberOfOutputs();
	x->f_inputNumber = x->f_ambiVector->getNumberOfInputs();
	x->f_ambiVector->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_inputNumber + x->f_outputNumber + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaVector_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaVector_perform(t_int *w)
{
	t_HoaVectore* x			= (t_HoaVectore*)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiVector->process(ins, outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaVector_assist(t_HoaVectore* x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
        sprintf(s,"(Signal) Loudspeakers %ld", a);
    else
    {
        if(!x->f_mode)
        {
            if(a == 0)
                sprintf(s,"(Signal) Velocity Vector Radius");
            else if(a == 1)
                sprintf(s,"(Signal) Velocity Vector Angle");
            else if(a == 2)
                sprintf(s,"(Signal) Energy Vector Radius");
            else if(a == 3)
                sprintf(s,"(Signal) Energy Vector Angle");
        }
        else
        {
            if(a == 0)
                sprintf(s,"(Signal) Velocity Vector Abscissa");
            else if(a == 1)
                sprintf(s,"(Signal) Velocity Vector Ordinate");
            else if(a == 2)
                sprintf(s,"(Signal) Energy Vector Abscissa");
            else if(a == 3)
                sprintf(s,"(Signal) Energy Vector Ordinate");
        }
    }
}

void HoaVector_free(t_HoaVectore* x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_ambiVector);
}

t_max_err mode_set(t_HoaVectore *x, t_object *attr, long ac, t_atom *av)
{
    if(ac && av && atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("cartesian"))
        x->f_ambiVector->setMode("cartesian");
    else if(ac && av && atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("Cartesian"))
        x->f_ambiVector->setMode("cartesian");
    else if(ac && av && atom_gettype(av) == A_LONG && atom_getlong(av) == 1)
        x->f_ambiVector->setMode("cartesian");
    else
        x->f_ambiVector->setMode("polar");
    
    if(x->f_ambiVector->getMode() == "polar")
        x->f_mode = 0;
    else
        x->f_mode = 1;
    return MAX_ERR_NONE;
}


