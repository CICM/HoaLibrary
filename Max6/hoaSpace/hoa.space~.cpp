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

#include "../MaxConverter.h"

typedef struct _HoaSpace
{
	t_pxobject					f_ob;
	AmbisonicSpace				*f_ambiSpace;
    long                        f_number_of_loudspeakers;
    double                      f_ramp_time;
} t_HoaSpace;

void *HoaSpace_new(t_symbol *s, long argc, t_atom *argv);
void HoaSpace_free(t_HoaSpace* x);
void HoaSpace_assist(t_HoaSpace* x, void *b, long m, long a, char *s);
void HoaSpace_list(t_HoaSpace *x, t_symbol *s, short ac, t_atom *av);

t_max_err loudspeakers_set(t_HoaSpace *x, t_object *attr, long argc, t_atom *argv);
t_max_err ramp_set(t_HoaSpace *x, t_object *attr, long argc, t_atom *argv);

void HoaSpace_dsp64(t_HoaSpace* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaSpace_perform64(t_HoaSpace* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaSpace_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.space~", (method)HoaSpace_new, (method)HoaSpace_free, (long)sizeof(t_HoaSpace), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaSpace_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaSpace_assist,     "assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaSpace_list,       "coeffs",   A_GIMME,0);
    class_addmethod(c, (method)HoaSpace_list,       "list",     A_GIMME,0);
    
    CLASS_ATTR_LONG                 (c, "loudspeakers", 0, t_HoaSpace, f_number_of_loudspeakers);
	CLASS_ATTR_CATEGORY             (c, "loudspeakers", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_ACCESSORS            (c, "loudspeakers", NULL, loudspeakers_set);
    CLASS_ATTR_ORDER                (c, "loudspeakers", 0, "1");
    CLASS_ATTR_SAVE                 (c, "loudspeakers", 1);
    
    CLASS_ATTR_DOUBLE               (c, "ramp", 0, t_HoaSpace, f_ramp_time);
	CLASS_ATTR_CATEGORY             (c, "ramp", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "ramp", 0, "Ramp Time in Milliseconds");
	CLASS_ATTR_ACCESSORS            (c, "ramp", NULL, ramp_set);
    CLASS_ATTR_ORDER                (c, "ramp", 0, "2");
    CLASS_ATTR_SAVE                 (c, "ramp", 1);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaSpace_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaSpace_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaSpace* x = NULL;
	int	anNumberOfMicrophones = 8;
    t_dictionary *d;
    
    x = (t_HoaSpace*)object_alloc((t_class*)HoaSpace_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			anNumberOfMicrophones = atom_getlong(argv);
		
		x->f_ambiSpace = new AmbisonicSpace(anNumberOfMicrophones, sys_getblksize(), sys_getsr());
		x->f_ramp_time = x->f_ambiSpace->getRampInMs();
        
		dsp_setup((t_pxobject *)x, x->f_ambiSpace->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiSpace->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
        
        attr_args_process(x, argc, argv);
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
	}
	return (x);
}

void HoaSpace_list(t_HoaSpace *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av)
    {
        if(ac == 2 && atom_gettype(av) == A_LONG && atom_gettype(av+1) == A_FLOAT)
        {
            x->f_ambiSpace->setCoefficient(atom_getlong(av), atom_getfloat(av+1));
        }
        else if(atom_gettype(av) == A_FLOAT)
        {
            for(int i = 0; i < ac; i++)
            {
                if(i < x->f_ambiSpace->getNumberOfLoudspeakers() && atom_gettype(av+i) == A_FLOAT)
                    x->f_ambiSpace->setCoefficient(i, atom_getfloat(av+i));
            }
        }
    }
}

void HoaSpace_dsp64(t_HoaSpace* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiSpace->setVectorSize(maxvectorsize);
    x->f_ambiSpace->setSamplingRate(samplerate);
    
    object_method(dsp64, gensym("dsp_add64"), x, HoaSpace_perform64, 0, NULL);
}

void HoaSpace_perform64(t_HoaSpace* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiSpace->process(ins, outs);
}

void HoaSpace_assist(t_HoaSpace* x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_ambiSpace->getLoudspeakerName(a).c_str());
}

t_max_err loudspeakers_set(t_HoaSpace *x, t_object *attr, long argc, t_atom *argv)
{
    t_atom* state = CicmMax::dsp_stop((t_object *)x);
    
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
        x->f_ambiSpace->setNumberOfLoudspeakers(atom_getfloat(argv));
    x->f_number_of_loudspeakers = x->f_ambiSpace->getNumberOfLoudspeakers();
    
    CicmMax::resize_inlet((t_object *)x, x->f_ambiSpace->getNumberOfInputs());
    CicmMax::resize_outlet((t_object *)x, x->f_ambiSpace->getNumberOfOutputs());
    CicmMax::dsp_start(state);
    
    return MAX_ERR_NONE;
}

t_max_err ramp_set(t_HoaSpace *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
        x->f_ambiSpace->setRampInMs(atom_getfloat(argv));
    
    x->f_ramp_time = x->f_ambiSpace->getRampInMs();
    
    return MAX_ERR_NONE;
}

void HoaSpace_free(t_HoaSpace* x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_ambiSpace);
}



