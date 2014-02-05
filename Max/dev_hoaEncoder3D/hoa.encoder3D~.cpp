/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../../Sources/HoaLibrary.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

int postons = 0;

typedef struct _hoa_encoder 
{
	t_pxobject              f_ob;
    Hoa3D::Encoder*         f_encoder;
    double*                 f_signals;
    
} t_hoa_encoder;


void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_encoder_free(t_hoa_encoder *x);
void hoa_encoder_assist(t_hoa_encoder *x, void *b, long m, long a, char *s);

void hoa_encoder_float(t_hoa_encoder *x, double f);
void hoa_encoder_int(t_hoa_encoder *x, long n);

void hoa_encoder_dsp64(t_hoa_encoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_encoder_perform64(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_encoder_perform64_azimuth(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_encoder_perform64_elevation(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_encoder_perform64_azimuth_elevation(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *hoa_encoder_class;
    

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.encoder3D~", (method)hoa_encoder_new, (method)hoa_encoder_free, (long)sizeof(t_hoa_encoder), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_encoder_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)hoa_encoder_int,         "int",		A_LONG, 0);
	class_addmethod(c, (method)hoa_encoder_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_encoder_assist,      "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_encoder_class = c;
    
    if (!postons)
    {
        post("hoa.library (version 1.4) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
        post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
        postons = 1;
    }

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
		
		x->f_encoder = new Hoa3D::Encoder(order);
		
		dsp_setup((t_pxobject *)x, x->f_encoder->getNumberOfInputs());
		for (int i = 0; i < x->f_encoder->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
        x->f_signals =  new double[x->f_encoder->getNumberOfOutputs() * sys_getmaxblksize()];
	}

	return (x);
}

void hoa_encoder_float(t_hoa_encoder *x, double f)
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

void hoa_encoder_int(t_hoa_encoder *x, long n)
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

void hoa_encoder_dsp64(t_hoa_encoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    
    if(count[x->f_encoder->getNumberOfInputs() - 1] && count[x->f_encoder->getNumberOfInputs() - 2])
        object_method(dsp64, gensym("dsp_add64"), x, hoa_encoder_perform64_azimuth_elevation, 0, NULL);
    else if(!count[x->f_encoder->getNumberOfInputs() - 1] && count[x->f_encoder->getNumberOfInputs() - 2])
        object_method(dsp64, gensym("dsp_add64"), x, hoa_encoder_perform64_azimuth, 0, NULL);
    else if(count[x->f_encoder->getNumberOfInputs() - 1] && !count[x->f_encoder->getNumberOfInputs() - 2])
        object_method(dsp64, gensym("dsp_add64"), x, hoa_encoder_perform64_elevation, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, hoa_encoder_perform64, 0, NULL);
}

void hoa_encoder_perform64_azimuth_elevation(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int i = sampleframes;
    while(--i)
    {
        x->f_encoder->setAzimuth(ins[1][sampleframes]);
        x->f_encoder->setElevation(ins[1][sampleframes]);
        x->f_encoder->process(ins[0][sampleframes], x->f_signals + sampleframes * i);
    }
    for(int i = 0; i < numouts; i++)
        cblas_daxpy(sampleframes, 1., x->f_signals+i, numouts, outs[i], 1);
}

void hoa_encoder_perform64_azimuth(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    while(--sampleframes)
    {
        x->f_encoder->setAzimuth(ins[1][sampleframes]);
        x->f_encoder->process(ins[0][sampleframes], x->f_signals);
        for(int i = 0; i < numouts; i++)
            outs[i][sampleframes] = x->f_signals[i];
    }
}

void hoa_encoder_perform64_elevation(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	while(--sampleframes)
    {
        x->f_encoder->setElevation(ins[1][sampleframes]);
        x->f_encoder->process(ins[0][sampleframes], x->f_signals);
        for(int i = 0; i < numouts; i++)
            outs[i][sampleframes] = x->f_signals[i];
    }
}

void hoa_encoder_perform64(t_hoa_encoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	while(--sampleframes)
    {
        x->f_encoder->process(ins[0][sampleframes], x->f_signals);
        for(int i = 0; i < numouts; i++)
            outs[i][sampleframes] = x->f_signals[i];
    }
}

void hoa_encoder_assist(t_hoa_encoder *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET)
	{
        if(a == 0)
        {
            sprintf(s,"(Signal) %s", "");
        }
        else
        {
            sprintf(s,"(Signal or float) %s", "");
        }
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

