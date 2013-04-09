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

#include "AmbisonicSpace.h"

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

typedef struct _HoaSpace
{
	t_pxobject					f_ob;
    t_object                    *f_patcher;
    t_object                    *f_patcherview;
    t_object                    *f_ui;
	AmbisonicSpace				*f_ambiSpace;

	long						f_inputNumber;
	long						f_outputNumber;

} t_HoaSpace;

void *HoaSpace_new(t_symbol *s, long argc, t_atom *argv);
void HoaSpace_free(t_HoaSpace* x);
void HoaSpace_assist(t_HoaSpace* x, void *b, long m, long a, char *s);
void HoaSpace_list(t_HoaSpace *x, t_symbol *s, short ac, t_atom *av);
void HoaSpace_bang(t_HoaSpace *x);
void HoaSpace_dblclick(t_HoaSpace *x);
t_max_err HoaSpace_notify(t_HoaSpace *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void HoaSpace_dsp(t_HoaSpace* x, t_signal **sp, short *count);
t_int *HoaSpace_perform(t_int *w);

void HoaSpace_dsp64(t_HoaSpace* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaSpace_perform64(t_HoaSpace* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaSpace_class;

int main(void)
{	
    common_symbols_init();
	t_class *c;
	
	c = class_new("hoa.space~", (method)HoaSpace_new, (method)HoaSpace_free, (long)sizeof(t_HoaSpace), 0L, A_GIMME, 0);
	
    class_addmethod(c, (method)HoaSpace_bang,		"bang",             0);
	class_addmethod(c, (method)HoaSpace_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaSpace_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaSpace_assist,     "assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaSpace_list,       "coeffs",   A_GIMME,0);
    class_addmethod(c, (method)HoaSpace_list,       "list",   A_GIMME,0);
    class_addmethod(c, (method)HoaSpace_dblclick,	"dblclick",	A_CANT, 0);
	class_addmethod(c, (method)HoaSpace_notify,		"notify",	A_CANT, 0);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaSpace_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaSpace_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaSpace* x = NULL;
	int	anNumberOfMicrophones = 8;
    
    x = (t_HoaSpace*)object_alloc((t_class*)HoaSpace_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			anNumberOfMicrophones = atom_getlong(argv);
		
		x->f_ambiSpace = new AmbisonicSpace(anNumberOfMicrophones, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiSpace->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiSpace->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaSpace_list(t_HoaSpace *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2 && atom_gettype(av) == A_LONG && atom_gettype(av+1) == A_FLOAT)
        x->f_ambiSpace->setCoefficient(atom_getlong(av), atom_getfloat(av+1));
    else if(atom_gettype(av) == A_FLOAT)
    {
        for(int i = 0; i < ac; i++)
        {
            if(i < x->f_ambiSpace->getNumberOfMicrophones() && atom_gettype(av+i) == A_FLOAT)
                x->f_ambiSpace->setCoefficient(i, atom_getfloat(av+i));
        }
    }
    if(x->f_patcher)
    {
        t_atom* values;
        long nValues = x->f_ambiSpace->getNumberOfMicrophones();
        values = new t_atom[nValues];
        for(int i = 0; i < nValues; i++)
            atom_setfloat(values+i, x->f_ambiSpace->getCoefficient(i));
        
        object_setvalueof(x->f_ui, nValues, values);
        free(values);
    }
}

void HoaSpace_dsp64(t_HoaSpace* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiSpace->setVectorSize(maxvectorsize);
    object_method(dsp64, gensym("dsp_add64"), x, HoaSpace_perform64, 0, NULL);
}

void HoaSpace_perform64(t_HoaSpace* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiSpace->process(ins, outs);
}

								  
								  
void HoaSpace_dsp(t_HoaSpace* x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_outputNumber = x->f_ambiSpace->getNumberOfOutputs();
	x->f_inputNumber = x->f_ambiSpace->getNumberOfInputs();
	x->f_ambiSpace->setVectorSize(sp[0]->s_n);
	pointer_count = x->f_inputNumber + x->f_outputNumber + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaSpace_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaSpace_perform(t_int *w)
{
	t_HoaSpace* x			= (t_HoaSpace*)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiSpace->process(ins, outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}


void HoaSpace_dblclick(t_HoaSpace *x)
{
	if (x->f_patcher)
		object_method(x->f_patcher, gensym("vis"));
	else
    {
		t_dictionary *d = dictionary_new();
		char parsebuf[256];
		t_atom a;
		long ac = 0;
		t_atom *av = NULL;
        
		sprintf(parsebuf,"@defrect 0 0 300 300 @openrect 0 0 300 300 @title hoa.space @enablehscroll 0 @enablevscroll 0 @presentation 0 @toolbarid \"\"");
		atom_setparse(&ac,&av,parsebuf);
		attr_args_dictionary(d,ac,av);
		atom_setobj(&a,d);
		sysmem_freeptr(av);
		x->f_patcher = (t_object *)object_new_typed(CLASS_NOBOX,gensym("jpatcher"),1, &a);
		freeobject((t_object *)d);
        
        object_method(x->f_patcher,gensym("noedit"), 1);
		object_method(x->f_patcher,gensym("vis"));
                                            
		x->f_ui = newobject_sprintf(x->f_patcher, "@maxclass hoa.space @patching_rect 0 0 300 300 @nmics %ld", x->f_ambiSpace->getNumberOfMicrophones());
        
		object_attach_byptr_register(x, x->f_ui, CLASS_BOX);
		object_attach_byptr_register(x, x->f_patcher, CLASS_NOBOX);
        x->f_patcherview = object_attr_getobj(x->f_patcher, gensym("firstview"));
        object_attach_byptr_register(x, x->f_patcherview, CLASS_NOBOX);
            
        HoaSpace_list(x, NULL, 0, NULL);
	}
}

void HoaSpace_bang(t_HoaSpace *x)
{
	defer(x, (method)HoaSpace_dblclick, 0, 0, 0);
}

void HoaSpace_assist(t_HoaSpace* x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) Microphones %ld", a);
}

t_max_err HoaSpace_notify(t_HoaSpace *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    t_atom *av = NULL;
    long    ac = 0;
	if (msg == gensym("free"))
    {
		if (sender == x->f_patcher)
        {
			x->f_patcher = NULL;
            x->f_patcherview = NULL;
        }
	}
	else if (msg == _sym_modified)
    {
		if (sender == x->f_ui)
        {
            object_getvalueof(x->f_ui, &ac, &av);
            if (ac && av)
            {
                for(int i = 0; i < ac; i++)
                    x->f_ambiSpace->setCoefficient(i, atom_getfloat(av+i));
                sysmem_freeptr(av);
            }
		}
	}
    else if (msg == gensym("attr_modified"))
    {
        if (sender == x->f_patcherview)
        {
            t_symbol* attrname = (t_symbol *)object_method(data, gensym("getname"));
            if (attrname == gensym("rect"))
            {
                object_attr_getvalueof(sender, attrname, &ac, &av);
                if (ac && av)
                {
                    long size;
                    if(atom_getlong(av+2) < atom_getlong(av+3))
                        size = atom_getlong(av+2);
                    else
                        size = atom_getlong(av+3);

                    t_atom  rv[4];
                    long    rc = 4;
                    atom_setlong(rv, 0.);
                    atom_setlong(rv+1, 0.);
                    atom_setlong(rv+2, size);
                    atom_setlong(rv+3, size);
                    if(atom_getlong(av+2) != size || atom_getlong(av+3) != size)
                    {
                        atom_setlong(av+2, size);
                        atom_setlong(av+3, size);
                        //object_attr_setvalueof(x->f_patcher, gensym("rect"), ac, av);
                        object_attr_setvalueof(x->f_ui, gensym("patching_rect"), rc, rv);
                    }
                
                    freebytes(av, sizeof(t_atom) * ac);
                }
            }
        }
    }
	return 0;
}

void HoaSpace_free(t_HoaSpace* x)
{
	dsp_free((t_pxobject *)x);
    if (x->f_patcher)
		object_free(x->f_patcher);
	free(x->f_ambiSpace);
}



