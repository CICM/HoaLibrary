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

#define MAX_SPEAKER 256

#include "../../Sources/HoaLibrary.h"

extern "C"
{
#include "ext.h"							
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "z_dsp.h"
}

typedef struct _HoaVector
{
	t_pxobject				f_ob;
	AmbisonicsVector        *f_ambiVector;
    
    t_symbol*               f_output_mode; 
    t_atom_long             f_number_of_loudspeakers;
    double                  f_offset_of_loudspeakers;
    double                  f_angles_of_loudspeakers[MAX_SPEAKER];
    
} t_HoaVector;

void *HoaVector_new(t_symbol *s, long argc, t_atom *argv);
void HoaVector_free(t_HoaVector* x);
void HoaVector_assist(t_HoaVector* x, void *b, long m, long a, char *s);

t_max_err mode_set(t_HoaVector *x, t_object *attr, long ac, t_atom *av);
t_max_err loudspeakers_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv);

void HoaVector_resize_inlet(t_HoaVector *x, long lastNumberOfOutlet);
void HoaVector_dsp(t_HoaVector* x, t_signal **sp, short *count);
t_int *HoaVector_perform(t_int *w);

void HoaVector_dsp64(t_HoaVector* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaVector_perform64(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *HoaVector_class;

int C74_EXPORT main(void)
{	
    common_symbols_init();
	t_class *c;
	
	c = class_new("hoa.vector~", (method)HoaVector_new, (method)HoaVector_free, (long)sizeof(t_HoaVector), 0L, A_GIMME, 0);

	class_addmethod(c, (method)HoaVector_dsp64,     "dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaVector_assist,    "assist",	A_CANT, 0);
    
    CLASS_ATTR_SYM					(c, "output", 0, t_HoaVector, f_output_mode);
	CLASS_ATTR_CATEGORY				(c, "output", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "output", 0, "1");
    CLASS_ATTR_ENUM                 (c, "output", 0, "polar \" cartesian");
    CLASS_ATTR_ACCESSORS            (c, "output", NULL, mode_set);
	CLASS_ATTR_LABEL                (c, "output", 0, "Coordinates type");
	CLASS_ATTR_DEFAULT				(c, "output", 0, "1");
	CLASS_ATTR_SAVE					(c, "output", 1);
    
    /* Ambisonics Mode */
    CLASS_ATTR_LONG                 (c, "loudspeakers", 0, t_HoaVector, f_number_of_loudspeakers);
	CLASS_ATTR_CATEGORY             (c, "loudspeakers", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_ACCESSORS            (c, "loudspeakers", NULL, loudspeakers_set);
    CLASS_ATTR_ORDER                (c, "loudspeakers", 0, "2");
    CLASS_ATTR_SAVE                 (c, "loudspeakers", 1);
    CLASS_ATTR_ALIAS                (c, "loudspeakers", "ls");
    
    CLASS_ATTR_DOUBLE_VARSIZE       (c, "angles", 0, t_HoaVector, f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_CATEGORY             (c, "angles", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_ACCESSORS            (c, "angles", NULL, angles_set);
    CLASS_ATTR_ORDER                (c, "angles", 0, "4");
	CLASS_ATTR_SAVE                 (c, "angles", 1);
    CLASS_ATTR_ALIAS                (c, "angles", "ls_angles");
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaVector_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaVector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaVector* x = (t_HoaVector*)object_alloc(HoaVector_class);
    t_dictionary *d;

	if (x)
	{
        x->f_output_mode = gensym("polar");
        x->f_number_of_loudspeakers = 4;
        x->f_offset_of_loudspeakers = 0.;
        if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
            x->f_number_of_loudspeakers = atom_getfloat(argv);
        
		x->f_ambiVector = new AmbisonicsVector(x->f_number_of_loudspeakers, Hoa_Polar, sys_getblksize());
		x->f_number_of_loudspeakers = x->f_ambiVector->getNumberOfLoudspeakers();
        for(int i = 0; i < x->f_number_of_loudspeakers; i++)
            x->f_angles_of_loudspeakers[i] = x->f_ambiVector->getLoudspeakerAngle(i);
    
		dsp_setup((t_pxobject *)x, x->f_ambiVector->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiVector->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
        
        attr_args_process(x, argc, argv);
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
	}
	return (x);
}

void HoaVector_dsp64(t_HoaVector* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiVector->setVectorSize(maxvectorsize);
    object_method(dsp64, gensym("dsp_add64"), x, HoaVector_perform64, 0, NULL);
}

void HoaVector_perform64(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiVector->process(ins, outs);
}

void HoaVector_assist(t_HoaVector* x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_ambiVector->getLoudspeakerName(a).c_str());
    else
        sprintf(s,"(Signal) %s", x->f_ambiVector->getVectorName(a).c_str());
}

void HoaVector_free(t_HoaVector* x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiVector;
}

t_max_err mode_set(t_HoaVector *x, t_object *attr, long ac, t_atom *av)
{
    if(ac && av)
    {
        if(atom_gettype(av) == A_SYM)
        {
            if(atom_getsym(av) == gensym("cartesian") || atom_getsym(av) == gensym(" cartesian"))
                x->f_ambiVector->setMode(Hoa_Cartesian);
            else
                x->f_ambiVector->setMode(Hoa_Polar);
        }
        if(atom_gettype(av) == A_FLOAT || atom_gettype(av) == A_LONG)
           x->f_ambiVector->setMode(atom_getfloat(av));
    }
    
    if(x->f_ambiVector->getMode() == Hoa_Polar)
        x->f_output_mode = gensym("polar");
    else
        x->f_output_mode = gensym("cartesian");
    return MAX_ERR_NONE;
}

t_max_err loudspeakers_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
        
    long numOutlet = x->f_ambiVector->getNumberOfOutputs();
        
    if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
        x->f_ambiVector->setNumberOfLoudspeakers(atom_getfloat(argv));
        
    HoaVector_resize_inlet(x, numOutlet);
    x->f_number_of_loudspeakers = x->f_ambiVector->getNumberOfLoudspeakers();
    
    return NULL;
}

t_max_err angles_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        for(int i = 0; i < argc; i++)
        {
            if(atom_gettype(argv+i) == A_LONG || atom_gettype(argv+i) == A_FLOAT)
                x->f_ambiVector->setLoudspeakerAngle(i, atom_getfloat(argv+i));
        }
    }
    
    for(int i = 0; i < x->f_number_of_loudspeakers; i++)
    {
        x->f_angles_of_loudspeakers[i] = x->f_ambiVector->getLoudspeakerAngle(i);
    }
    
    return NULL;
}

/*******************************************************************/
void HoaVector_resize_inlet(t_HoaVector *x, long lastNumberOfOutlet)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
    
    t_object *b = NULL;
    object_obex_lookup(x, _sym_pound_B, (t_object **)&b);
    object_method(b, gensym("dynlet_begin"));
    
    dsp_resize((t_pxobject*)x, x->f_ambiVector->getNumberOfInputs());
    object_method(b, gensym("dynlet_end"));
}



