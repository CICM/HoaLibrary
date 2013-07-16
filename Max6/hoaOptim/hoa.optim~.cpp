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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
	AmbisonicsOptim*		f_AmbisonicsOptim;
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
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
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
		x->f_AmbisonicsOptim	= new AmbisonicsOptim(order, Hoa_InPhase_Optim, sys_getblksize());
		
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

