/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
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

typedef struct _HoaEncode 
{
	t_pxobject              f_ob;
    AmbisonicEncoder3D*     f_ambiEncoder;
} t_HoaEncode;


void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv);
void HoaEncode_free(t_HoaEncode *x);
void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s);

void HoaEncode_float(t_HoaEncode *x, double f);
void HoaEncode_int(t_HoaEncode *x, long n);

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaEncode_perform64_azimuth(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaEncode_perform64_elevation(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaEncode_perform64_azimuth_elevation(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *HoaEncode_class;
    

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.encoder3D~", (method)HoaEncode_new, (method)HoaEncode_free, (long)sizeof(t_HoaEncode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaEncode_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaEncode_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaEncode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaEncode_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	HoaEncode_class = c;
    
    if (!postons)
    {
        post("hoa.library (version 1.4) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
        post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
        postons = 1;
    }

	return 0;
}

void *HoaEncode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaEncode *x = NULL;
	int	order = 4;

    x = (t_HoaEncode *)object_alloc(HoaEncode_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		
		x->f_ambiEncoder = new AmbisonicEncoder3D(order, sys_getblksize(), sys_getsr());
		
		dsp_setup((t_pxobject *)x, x->f_ambiEncoder->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiEncoder->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
        
        x->f_ob.z_misc = Z_NO_INPLACE;
	}

	return (x);
}

void HoaEncode_float(t_HoaEncode *x, double f)
{
    if(proxy_getinlet((t_object *)x) == 1)
    {
        x->f_ambiEncoder->setAzimuth(f);
    }
	else if(proxy_getinlet((t_object *)x) == 2)
    {
        x->f_ambiEncoder->setElevation(f);
    }
}

void HoaEncode_int(t_HoaEncode *x, long n)
{
	if(proxy_getinlet((t_object *)x) == 1)
    {
        x->f_ambiEncoder->setAzimuth(n);
    }
	else if(proxy_getinlet((t_object *)x) == 2)
    {
        x->f_ambiEncoder->setElevation(n);
    }
}

void HoaEncode_dsp64(t_HoaEncode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiEncoder->setVectorSize(maxvectorsize);
	x->f_ambiEncoder->setSamplingRate(samplerate);
    
    if(count[x->f_ambiEncoder->getNumberOfInputs() - 1] && count[x->f_ambiEncoder->getNumberOfInputs() - 2])
        object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64_azimuth_elevation, 0, NULL);
    else if(!count[x->f_ambiEncoder->getNumberOfInputs() - 1] && count[x->f_ambiEncoder->getNumberOfInputs() - 2])
        object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64_azimuth, 0, NULL);
    else if(count[x->f_ambiEncoder->getNumberOfInputs() - 1] && !count[x->f_ambiEncoder->getNumberOfInputs() - 2])
        object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64_elevation, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, HoaEncode_perform64, 0, NULL);
}

void HoaEncode_perform64_azimuth_elevation(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->processAzimtuhElevation(ins[0], outs, ins[1], ins[2]);
}

void HoaEncode_perform64_azimuth(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->processAzimtuh(ins[0], outs, ins[1]);
}

void HoaEncode_perform64_elevation(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->processElevation(ins[0], outs, ins[2]);
}

void HoaEncode_perform64(t_HoaEncode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiEncoder->process(ins[0], outs);
}

void HoaEncode_assist(t_HoaEncode *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET)
	{
        if(a == 0)
            sprintf(s,"(Signal) %s", x->f_ambiEncoder->getInputName(a).c_str());
        else
            sprintf(s,"(Signal or float) %s", x->f_ambiEncoder->getInputName(a).c_str());
	} 
	else 
	{
		sprintf(s,"(Signal) %s", x->f_ambiEncoder->getHarmonicsName(a).c_str());
	}
}


void HoaEncode_free(t_HoaEncode *x) 
{
	dsp_free((t_pxobject *)x);
	delete(x->f_ambiEncoder);
}

