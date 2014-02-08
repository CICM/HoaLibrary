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

typedef struct _hoa_encoder 
{
	t_pxobject      f_ob;
    double*         f_signals;
    Hoa2D::Encoder* f_encoder;
} t_hoa_encoder;


void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_encoder_free(t_hoa_encoder *x);
void hoa_encoder_assist(t_hoa_encoder *x, void *b, long m, long a, char *s);

void hoa_encoder_float(t_hoa_encoder *x, double f);
void hoa_encoder_int(t_hoa_encoder *x, long n);

void hoa_encoder_dsp64(t_hoa_encoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_encoder_perform64(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_encoder_perform64_azimuth(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *hoa_encoder_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.encoder~", (method)hoa_encoder_new, (method)hoa_encoder_free, (long)sizeof(t_hoa_encoder), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_encoder_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_encoder_int,         "int",		A_LONG, 0);
	class_addmethod(c, (method)hoa_encoder_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_encoder_assist,      "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_encoder_class = c;

	return 0;
}

void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_encoder *x = NULL;
	int	order = 4;
    x = (t_hoa_encoder *)object_alloc(hoa_encoder_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_encoder = new Hoa2D::Encoder(order);
		
		dsp_setup((t_pxobject *)x, x->f_encoder->getNumberOfInputs());
		for (int i = 0; i < x->f_encoder->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
        x->f_signals =  new double[x->f_encoder->getNumberOfOutputs() * SYS_MAXBLKSIZE];
	}

	return (x);
}

void hoa_encoder_float(t_hoa_encoder *x, double f)
{
	x->f_encoder->setAzimuth(f);
}

void hoa_encoder_int(t_hoa_encoder *x, long n)
{
	x->f_encoder->setAzimuth(n);
}

void hoa_encoder_dsp64(t_hoa_encoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(count[x->f_encoder->getNumberOfInputs() - 1])
        object_method(dsp64, gensym("dsp_add64"), x, hoa_encoder_perform64_azimuth, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, hoa_encoder_perform64, 0, NULL);
}

void hoa_encoder_perform64_azimuth(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_encoder->setAzimuth(ins[1][i]);
        x->f_encoder->process(ins[0][i], x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_encoder_perform64(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_encoder->process(ins[0][i], x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_encoder_assist(t_hoa_encoder *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET)
	{
        if(a == 0)
            sprintf(s,"(Signal) Input");
        else
            sprintf(s,"(Signal or float) Azymuth");
	} 
	else 
	{
		sprintf(s,"(Signal) %s", x->f_encoder->getHarmonicsName(a).c_str());
	}
}


void hoa_encoder_free(t_hoa_encoder *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_encoder;
    delete [] x->f_signals;
}

