/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa2D.max.h"

typedef struct _hoa_wider 
{
	t_pxobject      f_ob;
	double*         f_ins;
    double*         f_outs;
    Hoa2D::Wider*   f_wider;
    
} t_hoa_wider;

void *hoa_wider_new(t_symbol *s, long argc, t_atom *argv);
void hoa_wider_free(t_hoa_wider *x);
void hoa_wider_assist(t_hoa_wider *x, void *b, long m, long a, char *s);

void hoa_wider_float(t_hoa_wider *x, double f);
void hoa_wider_int(t_hoa_wider *x, long n);

void hoa_wider_dsp64(t_hoa_wider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_wider_perform64_wide(t_hoa_wider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_wider_perform64(t_hoa_wider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_hoa_err hoa_getinfos(t_hoa_wider* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_wider_class;

int C74_EXPORT main(void)
{

	t_class *c;
	
	c = class_new("hoa.2d.wider~", (method)hoa_wider_new, (method)hoa_wider_free, (long)sizeof(t_hoa_wider), 0L, A_GIMME, 0);
	class_alias(c, gensym("hoa.wider~"));

    hoa_initclass(c, (method)hoa_getinfos);
	class_addmethod(c, (method)hoa_wider_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_wider_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)hoa_wider_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_wider_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_wider_class = c;
    
	return 0;
}

void *hoa_wider_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_wider *x = NULL;
	int	order = 1;
    x = (t_hoa_wider *)object_alloc(hoa_wider_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(order < 1)
            order = 1;
        
		x->f_wider = new Hoa2D::Wider(order);
		
		dsp_setup((t_pxobject *)x, x->f_wider->getNumberOfHarmonics() + 1);
		for (int i = 0; i < x->f_wider->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
        
		x->f_ins = new double[x->f_wider->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new double[x->f_wider->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_wider* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_wider->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_wider->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_wider_float(t_hoa_wider *x, double f)
{
    x->f_wider->setWideningValue(f);
}

void hoa_wider_int(t_hoa_wider *x, long n)
{
    x->f_wider->setWideningValue(n);
}

void hoa_wider_dsp64(t_hoa_wider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(count[x->f_wider->getNumberOfHarmonics()])
        object_method(dsp64, gensym("dsp_add64"), x, hoa_wider_perform64_wide, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, hoa_wider_perform64, 0, NULL);
}

void hoa_wider_perform64_wide(t_hoa_wider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins - 1; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins - 1);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_wider->setWideningValue(ins[numins-1][i]);
        x->f_wider->process(x->f_ins + (numins - 1) * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_wider_perform64(t_hoa_wider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_wider->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_wider_assist(t_hoa_wider *x, void *b, long m, long a, char *s)
{
	if(a == x->f_wider->getNumberOfHarmonics())
	{
        sprintf(s,"(Signal or float) Widening Value");
	}
	else 
	{
		sprintf(s,"(Signal) %s", x->f_wider->getHarmonicsName(a).c_str());
	}
}


void hoa_wider_free(t_hoa_wider *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_wider;
    delete [] x->f_ins;
    delete [] x->f_outs;
}

