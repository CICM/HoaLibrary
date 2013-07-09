/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//#include "AmbisonicMultiMaps.h"
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

void HoaMap_dsp(t_HoaMap *x, t_signal **sp, short *count);
t_int *HoaMap_perform(t_int *w);


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
	
	class_addmethod(c, (method)HoaMap_dsp,         "dsp",		A_CANT,  0);
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

void HoaMap_dsp(t_HoaMap *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_maps->setVectorSize(sp[0]->s_n);
	x->f_ninput = x->f_maps->getNumberOfInputs();
	x->f_noutput = x->f_maps->getNumberOfOutputs();
	pointer_count = x->f_maps->getNumberOfInputs() + x->f_maps->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaMap_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}

t_int *HoaMap_perform(t_int *w)
{
	t_HoaMap *x			= (t_HoaMap *)(w[1]);	
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->f_ninput;
	
	x->f_maps->process(ins, outs);
	
	return (w + x->f_ninput + x->f_noutput + 3);
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




