/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../../Sources/Hoa2D/Hoa2D.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

int postons = 0;

typedef struct _hoa_optim 
{
	t_pxobject              f_ob;
    double*                 f_signals;
    Hoa2D::Optim*           f_optim;
    
} t_hoa_optim;


void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv);
void hoa_optim_free(t_hoa_optim *x);
void hoa_optim_assist(t_hoa_optim *x, void *b, long m, long a, char *s);

void hoa_optim_dsp64(t_hoa_optim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_optim_perform64(t_hoa_optim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_optim_perform64_wide(t_hoa_optim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *hoa_optim_class;
    

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.optim~", (method)hoa_optim_new, (method)hoa_optim_free, (long)sizeof(t_hoa_optim), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_optim_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_optim_assist,    "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_optim_class = c;
    
    class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
    
	return 0;
}

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_optim *x = NULL;
	int	order = 4;
    x = (t_hoa_optim *)object_alloc(hoa_optim_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG && atom_getlong(argv+1) == 1)
            x->f_optim = new Hoa2D::Optim(order, Hoa2D::Optim::MaxRe);
        else
            x->f_optim = new Hoa2D::Optim(order, Hoa2D::Optim::inPhase);
		
		dsp_setup((t_pxobject *)x, x->f_optim->getNumberOfInputs());
		for (int i = 0; i < x->f_optim->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
        
        x->f_signals =  new double[x->f_optim->getNumberOfOutputs() * SYS_MAXBLKSIZE];
	}

	return (x);
}

void hoa_optim_dsp64(t_hoa_optim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(count[x->f_optim->getNumberOfInputs() - 1])
        object_method(dsp64, gensym("dsp_add64"), x, hoa_optim_perform64_wide, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, hoa_optim_perform64, 0, NULL);
}

void hoa_optim_perform64_wide(t_hoa_optim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_optim->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_optim_perform64(t_hoa_optim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_optim->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_optim_assist(t_hoa_optim *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_optim->getHarmonicsName(a).c_str());
}


void hoa_optim_free(t_hoa_optim *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_optim;
    delete [] x->f_signals;
}

