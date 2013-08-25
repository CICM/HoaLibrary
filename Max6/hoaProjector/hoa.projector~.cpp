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

typedef struct _HoaProjector
{
	t_pxobject			f_ob;			
	AmbisonicProjector	*f_AmbisonicProjector;
    t_atom_long         f_number_of_loudspeakers;

} t_HoaProjector;

void *HoaProjector_new(t_symbol *s, long argc, t_atom *argv);
void HoaProjector_free(t_HoaProjector *x);
void HoaProjector_assist(t_HoaProjector *x, void *b, long m, long a, char *s);

void HoaProjector_dsp64(t_HoaProjector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaProjector_perform64(t_HoaProjector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err loudspeakers_set(t_HoaProjector *x, t_object *attr, long argc, t_atom *argv);

t_class* HoaProjector_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.projector~", (method)HoaProjector_new, (method)dsp_free, (long)sizeof(t_HoaProjector), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaProjector_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaProjector_assist,			"assist",	A_CANT, 0);
    
    CLASS_ATTR_LONG                 (c, "loudspeakers", 0, t_HoaProjector, f_number_of_loudspeakers);
	CLASS_ATTR_CATEGORY             (c, "loudspeakers", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_ACCESSORS            (c, "loudspeakers", NULL, loudspeakers_set);
    CLASS_ATTR_ORDER                (c, "loudspeakers", 0, "1");
    CLASS_ATTR_SAVE                 (c, "loudspeakers", 1);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaProjector_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaProjector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaProjector *x = NULL;
    t_dictionary *d;
	int order = 4;
    x = (t_HoaProjector *)object_alloc(HoaProjector_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		
		x->f_AmbisonicProjector	= new AmbisonicProjector(order, 10, sys_getblksize());
		x->f_number_of_loudspeakers = x->f_AmbisonicProjector->getNumberOfLoudspeakers();
        
		dsp_setup((t_pxobject *)x, x->f_AmbisonicProjector->Ambisonics::getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicProjector->Planewaves::getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
        x->f_ob.z_misc = Z_NO_INPLACE;
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
	}
	return (x);
}

void HoaProjector_dsp64(t_HoaProjector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicProjector->setVectorSize(maxvectorsize);
    object_method(dsp64, gensym("dsp_add64"), x, HoaProjector_perform64, 0, NULL);
}

void HoaProjector_perform64(t_HoaProjector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicProjector->process(ins, outs);
}

void HoaProjector_assist(t_HoaProjector *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		sprintf(s,"(Signal) %s", x->f_AmbisonicProjector->getHarmonicsName(a).c_str());
	}
	else 
		sprintf(s,"(Signal) %s",  x->f_AmbisonicProjector->getLoudspeakerName(a).c_str());
}

t_max_err loudspeakers_set(t_HoaProjector *x, t_object *attr, long argc, t_atom *argv)
{
    t_atom* state = CicmMax::dsp_stop((t_object *)x);
    
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
        x->f_AmbisonicProjector->setNumberOfLoudspeakers(atom_getfloat(argv));
    x->f_number_of_loudspeakers = x->f_AmbisonicProjector->getNumberOfLoudspeakers();
    
    CicmMax::resize_outlet((t_object *)x, x->f_AmbisonicProjector->getNumberOfLoudspeakers());
    CicmMax::dsp_start(state);
    
    return MAX_ERR_NONE;
}

void HoaProjector_free(t_HoaProjector *x)
{
	dsp_free((t_pxobject *)x);
	free(x->f_AmbisonicProjector);
}

