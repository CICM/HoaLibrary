/*
 // Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

/**
 @file      hoa.3d.encoder~.cpp
 @name      hoa.3d.encoder~
 @realname  hoa.3d.encoder~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A 3d ambisonic encoder.
 
 @description
 <o>hoa.3d.encoder~</o> encodes a signal into the spherical harmonics domain depending on a given order of decomposition, an azimuth and an elevation value given in radians
 
 @discussion
 <o>hoa.3d.encoder~</o> encodes a signal into the spherical harmonics domain depending on a given order of decomposition, an azimuth and an elevation value given in radians
 
 @category ambisonics, hoa objects, audio, MSP
 
 @seealso hoa.2d.encoder~, hoa.3d.decoder~, hoa.3d.map~, hoa.3d.optim~, hoa.3d.scope~, hoa.3d.wider~, hoa.pi, hoa.pi~
 */

#include "Hoa3D.max.h"

typedef struct _hoa_3d_encoder 
{
	t_pxobject              f_ob;
    double*                 f_signals;
    Hoa3D::Encoder*         f_encoder;
    
} t_hoa_3d_encoder;

void *hoa_3d_encoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_3d_encoder_free(t_hoa_3d_encoder *x);
void hoa_3d_encoder_assist(t_hoa_3d_encoder *x, void *b, long m, long a, char *s);

void hoa_3d_encoder_float(t_hoa_3d_encoder *x, double f);
void hoa_3d_encoder_int(t_hoa_3d_encoder *x, long n);

void hoa_3d_encoder_dsp64(t_hoa_3d_encoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_3d_encoder_perform64(t_hoa_3d_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_encoder_perform64_azimuth(t_hoa_3d_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_encoder_perform64_elevation(t_hoa_3d_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_3d_encoder_perform64_azimuth_elevation(t_hoa_3d_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_hoa_err hoa_getinfos(t_hoa_3d_encoder* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_3d_encoder_class;

#ifdef HOA_PACKED_LIB
int hoa_3d_encoder_main(void)
#else
int C74_EXPORT main(void)
#endif
{
	t_class *c;
	
	c = class_new("hoa.3d.encoder~", (method)hoa_3d_encoder_new, (method)hoa_3d_encoder_free, (long)sizeof(t_hoa_3d_encoder), 0L, A_GIMME, 0);
	class_setname((char *)"hoa.3d.encoder~", (char *)"hoa.3d.encoder~");
    
	hoa_initclass(c, (method)hoa_getinfos);
	
	// @method int @digest Set the azimuth or the elevation of the encoding in radians (between 0 and 2π)
	// In the second inlet : The <m>float</m> method sets the azimuth of the encoding.
	// In the third inlet : The <m>float</m> method the elevation of the encoding.
	// @marg 0 @name azimuth/elevation @optional 0 @type float
	class_addmethod(c, (method)hoa_3d_encoder_float,		"float",	A_FLOAT, 0);
	
	// @method int @digest Set the azimuth or the elevation of the encoding in radians (between 0 and 2π)
	// In the second inlet : The <m>int</m> method sets the azimuth of the encoding.
	// In the third inlet : The <m>int</m> method the elevation of the encoding.
	// @marg 0 @name azimuth/elevation @optional 0 @type int
	class_addmethod(c, (method)hoa_3d_encoder_int,         "int",		A_LONG, 0);
	
	// @method signal @digest Signal to encode or azimuth / elevation of the encoding in radians.
	// @description In the left inlet, the signal to encode.
	// In the second inlet : set the azimuth of the encoding in radians
	// In the third inlet : set the elevation of the encoding in radians
	class_addmethod(c, (method)hoa_3d_encoder_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_3d_encoder_assist,      "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	hoa_3d_encoder_class = c;
	
	return 0;
}

void *hoa_3d_encoder_new(t_symbol *s, long argc, t_atom *argv)
{
	// @arg 0 @name ambisonic-order @optional 0 @type int @digest The ambisonic order of decomposition
	// @description First argument is the ambisonic order of decomposition.
	
	t_hoa_3d_encoder *x = NULL;
	int	order = 1;
    x = (t_hoa_3d_encoder *)object_alloc(hoa_3d_encoder_class);
	if (x)
	{
		if(argc && atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(order < 1)
            order = 1;
        
		x->f_encoder = new Hoa3D::Encoder(order);
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		
		dsp_setup((t_pxobject *)x, 3);
		for (int i = 0; i < x->f_encoder->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
        
        x->f_signals =  new double[x->f_encoder->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_3d_encoder* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = x->f_encoder->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_3d_encoder_float(t_hoa_3d_encoder *x, double f)
{
    if(proxy_getinlet((t_object *)x) == 1)
    {
        x->f_encoder->setAzimuth(f);
    }
	else if(proxy_getinlet((t_object *)x) == 2)
    {
        x->f_encoder->setElevation(f);
    }
}

void hoa_3d_encoder_int(t_hoa_3d_encoder *x, long n)
{
	if(proxy_getinlet((t_object *)x) == 1)
    {
        x->f_encoder->setAzimuth(n);
    }
	else if(proxy_getinlet((t_object *)x) == 2)
    {
        x->f_encoder->setElevation(n);
    }
}

void hoa_3d_encoder_dsp64(t_hoa_3d_encoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int azimuth = count[1];
	int elevation = count[2];
    if(azimuth && elevation)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_3d_encoder_perform64_azimuth_elevation, 0, NULL);
    else if(azimuth && !elevation)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_3d_encoder_perform64_azimuth, 0, NULL);
    else if(!azimuth && elevation)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_3d_encoder_perform64_elevation, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, hoa_3d_encoder_perform64, 0, NULL);
}

void hoa_3d_encoder_perform64_azimuth_elevation(t_hoa_3d_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_encoder->setAzimuth(ins[1][i]);
        x->f_encoder->setElevation(ins[2][i]);
        x->f_encoder->process(ins[0][i], x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_3d_encoder_perform64_azimuth(t_hoa_3d_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
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

void hoa_3d_encoder_perform64_elevation(t_hoa_3d_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_encoder->setElevation(ins[2][i]);
        x->f_encoder->process(ins[0][i], x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_3d_encoder_perform64(t_hoa_3d_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
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

void hoa_3d_encoder_assist(t_hoa_3d_encoder *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET)
	{
        if(a == 0)
            sprintf(s,"(signal) Input");
        else if(a == 1)
            sprintf(s,"(signal or float) Azimuth");
        else if(a == 2)
            sprintf(s,"(signal or float) Elevation");
	}
	else 
	{
		sprintf(s,"(signal) %s", x->f_encoder->getHarmonicName(a).c_str());
	}
}


void hoa_3d_encoder_free(t_hoa_3d_encoder *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_encoder;
    delete [] x->f_signals;
}

