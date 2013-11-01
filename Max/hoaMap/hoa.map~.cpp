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

typedef struct _HoaMap 
{
	t_pxobject				f_ob;
	AmbisonicsMultiMaps*	f_maps;

	int						f_ninput;
	int						f_noutput;
    t_symbol*               f_mode;
    bool					f_mode_bool;
    float                   f_ramp;
} t_HoaMap;

void *HoaMap_new(t_symbol *s, long argc, t_atom *argv);
void HoaMap_free(t_HoaMap *x);
void HoaMap_assist(t_HoaMap *x, void *b, long m, long a, char *s);
void HoaMap_list(t_HoaMap *x, t_symbol *s, long argc, t_atom *argv);
void HoaMap_float(t_HoaMap *x, double f);
void HoaMap_int(t_HoaMap *x, long n);
t_max_err HoaMap_mode(t_HoaMap *x, t_object *attr, long argc, t_atom *argv);
t_max_err HoaMap_ramp(t_HoaMap *x, t_object *attr, long argc, t_atom *argv);


void HoaMap_dsp64(t_HoaMap *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaMap_perform64(t_HoaMap *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaMap_perform64_polar(t_HoaMap *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaMap_perform64_radius(t_HoaMap *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaMap_perform64_azimuth(t_HoaMap *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaMap_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.map~", (method)HoaMap_new, (method)dsp_free, (long)sizeof(t_HoaMap), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaMap_dsp64,       "dsp64",     A_CANT,  0);
	class_addmethod(c, (method)HoaMap_assist,      "assist",	A_CANT,  0);
    class_addmethod(c, (method)HoaMap_list,        "list",      A_GIMME, 0);
    class_addmethod(c, (method)HoaMap_float,       "float",     A_FLOAT);
    class_addmethod(c, (method)HoaMap_int,         "int",       A_LONG);
    
    CLASS_ATTR_SYM              (c, "mode", 0, t_HoaMap, f_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "mode", 0, "Coordinates Types");
    CLASS_ATTR_ENUM             (c, "mode", 0, "polar cartesian");
	CLASS_ATTR_ORDER			(c, "mode", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, HoaMap_mode);
	CLASS_ATTR_SAVE				(c, "mode", 1);
    
    CLASS_ATTR_FLOAT            (c, "ramp", 0, t_HoaMap, f_ramp);
	CLASS_ATTR_CATEGORY			(c, "ramp", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "ramp", 0, "Ramp Time");
	CLASS_ATTR_ORDER			(c, "ramp", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "ramp", NULL, HoaMap_ramp);
	CLASS_ATTR_SAVE				(c, "ramp", 1);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaMap_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaMap_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaMap *x = NULL;
	int order = 4;
    int numberOfSources = 1;
    
    x = (t_HoaMap *)object_alloc((t_class*)HoaMap_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			numberOfSources = atom_getlong(argv+1);
        
		x->f_maps	= new AmbisonicsMultiMaps(order, numberOfSources, 4410, sys_getblksize(), sys_getsr());
        dsp_setup((t_pxobject *)x, x->f_maps->getNumberOfInputs());
        
		for (int i = 0; i < x->f_maps->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
        t_atom av;
        atom_setlong(&av, 1);
        object_method(x, gensym("mode"), 1, &av);
        atom_setlong(&av, 100.);
        object_method(x, gensym("ramp"), 1, &av);
        
        if(atom_gettype(argv+1) == A_SYM)
            object_method(x, gensym("mode"), 1, argv+1);
        
        attr_args_process(x, argc, argv);
        
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaMap_float(t_HoaMap *x, double f)
{
    if(x->f_mode_bool == 0 && x->f_maps->getNumberOfSources() == 1)
    {
        if (proxy_getinlet((t_object *)x) == 1)
            x->f_maps->setCoordinatesRadius(0, f);
        else if(proxy_getinlet((t_object *)x) == 2)
            x->f_maps->setCoordinatesAzimuth(0, f);
    }
    else if (x->f_mode_bool == 1 && x->f_maps->getNumberOfSources() == 1)
    {
        if (proxy_getinlet((t_object *)x) == 1)
            x->f_maps->setCoordinatesAbscissa(0, f);
        else if(proxy_getinlet((t_object *)x) == 2)
            x->f_maps->setCoordinatesOrdinate(0, f);
    }
}

void HoaMap_int(t_HoaMap *x, long n)
{
    if(x->f_mode_bool == 0 && x->f_maps->getNumberOfSources() == 1)
    {
        if (proxy_getinlet((t_object *)x) == 1)
            x->f_maps->setCoordinatesRadius(0, n);
        else if(proxy_getinlet((t_object *)x) == 2)
            x->f_maps->setCoordinatesAzimuth(0, n);
    }
    else if (x->f_mode_bool == 1 && x->f_maps->getNumberOfSources() == 1)
    {
        if (proxy_getinlet((t_object *)x) == 1)
            x->f_maps->setCoordinatesAbscissa(0, n);
        else if(proxy_getinlet((t_object *)x) == 2)
            x->f_maps->setCoordinatesOrdinate(0, n);
    }
}

void HoaMap_dsp64(t_HoaMap *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_maps->setVectorSize(maxvectorsize);
    if (x->f_maps->getNumberOfSources() == 1)
    {
        if(count[1] && count[2])
            object_method(dsp64, gensym("dsp_add64"), x, HoaMap_perform64_polar, 0, NULL);
        else if(count[1] && !count[2])
            object_method(dsp64, gensym("dsp_add64"), x, HoaMap_perform64_radius, 0, NULL);
        else if(!count[1] && count[2])
            object_method(dsp64, gensym("dsp_add64"), x, HoaMap_perform64_azimuth, 0, NULL);
        else
            object_method(dsp64, gensym("dsp_add64"), x, HoaMap_perform64, 0, NULL);
    }
    else
        object_method(dsp64, gensym("dsp_add64"), x, HoaMap_perform64, 0, NULL);
}

void HoaMap_perform64(t_HoaMap *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_maps->process(ins, outs);
}

void HoaMap_perform64_polar(t_HoaMap *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    if(x->f_mode_bool)
        x->f_maps->processCartesian(ins[0], outs, ins[1], ins[2]);
    else
        x->f_maps->processPolar(ins[0], outs, ins[1], ins[2]);
}

void HoaMap_perform64_radius(t_HoaMap *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    if(x->f_mode_bool)
        x->f_maps->processAbscissa(ins[0], outs, ins[1]);
    else
        x->f_maps->processRadius(ins[0], outs, ins[1]);
}

void HoaMap_perform64_azimuth(t_HoaMap *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    if(x->f_mode_bool)
        x->f_maps->processOrdinate(ins[0], outs, ins[2]);
    else
        x->f_maps->processAzimuth(ins[0], outs, ins[2]);
}

void HoaMap_assist(t_HoaMap *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
    {
        if(a == 0)
            sprintf(s,"(Signal and List) %s", x->f_maps->getSourceName(a).c_str());
        else
            sprintf(s,"(Signal) %s", x->f_maps->getSourceName(a).c_str());
    }
    else
        sprintf(s,"(Signal) %s", x->f_maps->getHarmonicsName(a).c_str());
}

void HoaMap_list(t_HoaMap *x, t_symbol *s, long argc, t_atom *argv)
{
    if(atom_getsym(argv+1) == gensym("car") || atom_getsym(argv+1) == gensym("cartesian"))
        x->f_maps->setCoordinatesCartesian(atom_getlong(argv), atom_getfloat(argv+2), atom_getfloat(argv+3));
    else if(atom_getsym(argv+1) == gensym("pol") || atom_getsym(argv+1) == gensym("polar"))
        x->f_maps->setCoordinatesPolar(atom_getlong(argv), atom_getfloat(argv+2), atom_getfloat(argv+3));
    else if (atom_getsym(argv+1) == gensym("mute"))
        x->f_maps->setMuted(atom_getlong(argv), atom_getlong(argv+2));
}

void HoaMap_free(t_HoaMap *x)
{
	dsp_free((t_pxobject *)x);
	delete(x->f_maps);
}

t_max_err HoaMap_mode(t_HoaMap *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == gensym(" cartesian") || atom_getsym(argv) == gensym("cartesian") || atom_getsym(argv) == gensym(" car") || atom_getsym(argv) == gensym("car"))
            x->f_mode_bool = 1;
        else
            x->f_mode_bool = 0;
	}
    else if(atom_gettype(argv) == A_LONG)
        x->f_mode_bool = Tools::clip(atom_getlong(argv), (t_atom_long)0, (t_atom_long)1);
    if(x->f_mode_bool)
         x->f_mode = gensym("cartesian");
    else
        x->f_mode = gensym("polar");
    return NULL;
}

t_max_err HoaMap_ramp(t_HoaMap *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG)
        x->f_maps->setRamp(atom_getlong(argv) * sys_getsr() / 1000.);
    else if(atom_gettype(argv) == A_FLOAT)
        x->f_maps->setRamp(atom_getfloat(argv) * sys_getsr() / 1000.);
    
    x->f_ramp = x->f_maps->getRamp() / sys_getsr() * 1000.;

    return NULL;
}




