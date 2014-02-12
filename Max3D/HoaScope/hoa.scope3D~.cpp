/*
// Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../hoa.max.h"

typedef struct _hoa_scope 
{
	t_pxobject              f_ob;
    double*                 f_signals;
    Hoa3D::Scope*           f_scope;
    int                     f_index;
} t_hoa_scope;

void *hoa_scope_new(t_symbol *s, long argc, t_atom *argv);
void hoa_scope_free(t_hoa_scope *x);
void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s);

void hoa_scope_bang(t_hoa_scope *x);

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *hoa_scope_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.scope3D~", (method)hoa_scope_new, (method)hoa_scope_free, (long)sizeof(t_hoa_scope), 0L, A_GIMME, 0);
	
    class_addmethod(c, (method)hoa_scope_bang,		"bang",     A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_assist,    "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_scope_class = c;
    hoa_credit();
    
	return 0;
}

void *hoa_scope_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_scope *x = NULL;
	int	order = 1;
    x = (t_hoa_scope *)object_alloc(hoa_scope_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_scope = new Hoa3D::Scope(order, 20, 50);
		
		dsp_setup((t_pxobject *)x, x->f_scope->getNumberOfHarmonics());
        x->f_signals =  new double[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_index = 0;
	}

	return (x);
}

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_index = 0;
    object_method(dsp64, gensym("dsp_add64"), x, hoa_scope_perform64, 0, NULL);
}

void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
    x->f_index = 0;
    while(--sampleframes)
    {
        x->f_index++;
    }
}

void hoa_scope_bang(t_hoa_scope *x)
{
    x->f_scope->process(x->f_signals + x->f_index * x->f_scope->getNumberOfHarmonics());
    for(int i = 0; i < x->f_scope->getNumberOfRows(); i++)
    {
        for(int j = 0; j < x->f_scope->getNumberOfColumns(); j++)
            post("scope : %i %i %f", i, j, (float)x->f_scope->getValue(i, j));
    }
}

void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_scope->getHarmonicsName(a).c_str());
}

void hoa_scope_free(t_hoa_scope *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_scope;
    delete [] x->f_signals;
}

