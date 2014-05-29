/*
 // Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

/**
 @file      hoa.3d.wider~.cpp
 @name      hoa.3d.wider~
 @realname  hoa.3d.wider~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A fractional ambisonic orders simulator for 2d
 
 @description
 <o>hoa.3d.wider~</o> can be used to wide the diffusion of a localised sound. The order depending signals are weighted and appear in a logarithmic way to have linear changes.
 
 @discussion
 <o>hoa.3d.wider~</o> can be used to wide the diffusion of a localised sound. The order depending signals are weighted and appear in a logarithmic way to have linear changes.
 
 @category ambisonics, hoa objects, audio, MSP
 
 @seealso hoa.2d.wider~, hoa.3d.encoder~, hoa.3d.decoder~, hoa.3d.map~, hoa.3d.optim~, hoa.3d.scope~
 */

#include "../Hoa3D.max.h"

typedef struct _hoa_wider 
{
	t_pxobject              f_ob;
    double*                 f_signals;
    Hoa3D::Wider*           f_wider;
    
} t_hoa_wider;

void *hoa_wider_new(t_symbol *s, long argc, t_atom *argv);
void hoa_wider_free(t_hoa_wider *x);
void hoa_wider_assist(t_hoa_wider *x, void *b, long m, long a, char *s);

void hoa_wider_float(t_hoa_wider *x, double f);
void hoa_wider_int(t_hoa_wider *x, long n);

void hoa_wider_dsp64(t_hoa_wider *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_wider_perform64(t_hoa_wider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_wider_perform64_wide(t_hoa_wider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_hoa_err hoa_getinfos(t_hoa_wider* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_wider_class;
    

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.3d.wider~", (method)hoa_wider_new, (method)hoa_wider_free, (long)sizeof(t_hoa_wider), 0L, A_GIMME, 0);
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	// @method float @digest Set the widening value.
	// @description Set the widening value in the last inlet at control rate. The widening value is clipped between 0. and 1.
	class_addmethod(c, (method)hoa_wider_float,		"float",	A_FLOAT, 0);
	
	// @method int @digest Set the widening value.
	// @description Set the widening value in the last inlet at control rate. The widening value is clipped between 0. and 1.
	class_addmethod(c, (method)hoa_wider_int,       "int",		A_LONG, 0);
	
	// @method signal @digest Array of spherical harmonics signals to be processed, widening value.
	// @description Array of spherical harmonics signals to be processed. Set the widening value in the last inlet at signal rate. The widening value is clipped between 0. and 1.
	class_addmethod(c, (method)hoa_wider_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_wider_assist,    "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_wider_class = c;
	return 0;
}

void *hoa_wider_new(t_symbol *s, long argc, t_atom *argv)
{
	// @arg 0 @name ambisonic-order @optional 0 @type int @digest The ambisonic order of decomposition
	// @description First argument is the ambisonic order of decomposition.
	
	t_hoa_wider *x = NULL;
	int	order = 1;
    x = (t_hoa_wider *)object_alloc(hoa_wider_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_wider = new Hoa3D::Wider(order);
		
		dsp_setup((t_pxobject *)x, x->f_wider->getNumberOfHarmonics() + 1);
		for (int i = 0; i < x->f_wider->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
        
        x->f_signals =  new double[x->f_wider->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_wider* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
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
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_wider->setWideningValue(ins[numins-1][i]);
        x->f_wider->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_wider_perform64(t_hoa_wider *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_wider->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_wider_assist(t_hoa_wider *x, void *b, long m, long a, char *s)
{
    if (a == x->f_wider->getNumberOfHarmonics())
	{
        sprintf(s,"(Signal or float) Widening value");
	}
	else 
	{
		sprintf(s,"(Signal) %s", x->f_wider->getHarmonicName(a).c_str());
	}
}

void hoa_wider_free(t_hoa_wider *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_wider;
    delete [] x->f_signals;
}

