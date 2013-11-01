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

typedef struct _HoaOptim 
{
	t_pxobject				f_ob;			
	AmbisonicOptim*		f_AmbisonicsOptim;
    t_symbol*               f_optim_mode;
    
} t_HoaOptim;

void *HoaOptim_new(t_symbol *s, long argc, t_atom *argv);
void HoaOptim_free(t_HoaOptim *x);
void HoaOptim_assist(t_HoaOptim *x, void *b, long m, long a, char *s);
t_max_err HoaOptim_optim(t_HoaOptim *x, t_object *attr, long argc, t_atom *argv);

void HoaOptim_dsp64(t_HoaOptim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaOptim_perform64(t_HoaOptim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *HoaOptim_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.optim~", (method)HoaOptim_new, (method)dsp_free, (long)sizeof(t_HoaOptim), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaOptim_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaOptim_assist,		"assist",	A_CANT, 0);
    
    CLASS_ATTR_SYM				(c, "optim", 0, t_HoaOptim, f_optim_mode);
	CLASS_ATTR_CATEGORY			(c, "optim", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "optim", 0, "Optimization");
    CLASS_ATTR_ENUM             (c, "optim", 0, "basic maxRe inPhase");
	CLASS_ATTR_ORDER			(c, "optim", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "optim", NULL, HoaOptim_optim);
	CLASS_ATTR_SAVE				(c, "optim", 1);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaOptim_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaOptim_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaOptim *x = NULL;
    t_dictionary *d = NULL;
	int order = 4;
    
    x = (t_HoaOptim *)object_alloc(HoaOptim_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
        
        x->f_optim_mode = gensym("inPhase");
		x->f_AmbisonicsOptim	= new AmbisonicOptim(order, Hoa_InPhase_Optim, sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsOptim->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsOptim->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
        
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        attr_args_process(x, argc, argv);
	}
	return (x);
}

void HoaOptim_dsp64(t_HoaOptim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicsOptim->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, HoaOptim_perform64, 0, NULL);
}

void HoaOptim_perform64(t_HoaOptim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicsOptim->process(ins, outs);
}

void HoaOptim_assist(t_HoaOptim *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_AmbisonicsOptim->getHarmonicsName(a).c_str());
}

t_max_err HoaOptim_optim(t_HoaOptim *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == gensym("maxRe"))
            x->f_AmbisonicsOptim->setOptimMode(Hoa_MaxRe_Optim);
        else if(atom_getsym(argv) == gensym("inPhase"))
            x->f_AmbisonicsOptim->setOptimMode(Hoa_InPhase_Optim);
        else
            x->f_AmbisonicsOptim->setOptimMode(Hoa_Basic_Optim);
	}
    else if(atom_gettype(argv) == A_LONG)
        x->f_AmbisonicsOptim->setOptimMode(atom_getlong(argv));
    
    if(x->f_AmbisonicsOptim->getOptimMode() == Hoa_MaxRe_Optim)
        x->f_optim_mode = gensym("maxRe");
    else if(x->f_AmbisonicsOptim->getOptimMode() == Hoa_InPhase_Optim)
        x->f_optim_mode = gensym("inPhase");
    else
        x->f_optim_mode = gensym("basic");
    return NULL;
}

void HoaOptim_free(t_HoaOptim *x)
{
	dsp_free((t_pxobject *)x);
	delete(x->f_AmbisonicsOptim);
}

