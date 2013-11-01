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
	AmbisonicVector        *f_ambiVector;
    
    t_symbol*               f_output_mode; 
    t_atom_long             f_number_of_loudspeakers;
    double                  f_offset_of_loudspeakers;
    double                  f_angles_of_loudspeakers[MAX_SPEAKER];
    
} t_HoaVector;

void *HoaVector_new(t_symbol *s, long argc, t_atom *argv);
void HoaVector_free(t_HoaVector* x);
void HoaVector_assist(t_HoaVector* x, void *b, long m, long a, char *s);

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
	t_class *c;
	
	c = class_new("hoa.vector~", (method)HoaVector_new, (method)HoaVector_free, (long)sizeof(t_HoaVector), 0L, A_GIMME, 0);

	class_addmethod(c, (method)HoaVector_dsp64,     "dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaVector_assist,    "assist",	A_CANT, 0);
    
    CLASS_ATTR_LONG                 (c, "channels", 0, t_HoaVector, f_number_of_loudspeakers);
	CLASS_ATTR_CATEGORY             (c, "channels", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_ACCESSORS            (c, "channels", NULL, loudspeakers_set);
    CLASS_ATTR_ORDER                (c, "channels", 0, "2");
    CLASS_ATTR_SAVE                 (c, "channels", 1);
    CLASS_ATTR_ALIAS                (c, "channels", "loudspeakers");
    
    CLASS_ATTR_DOUBLE_VARSIZE       (c, "angles", 0, t_HoaVector, f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_CATEGORY             (c, "angles", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "angles", 0, "Angles of Channels");
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
        
		x->f_ambiVector = new AmbisonicVector(x->f_number_of_loudspeakers, sys_getblksize());
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
                x->f_ambiVector->setLoudspeakerAngleDegrees(i, atom_getfloat(argv+i));
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
    object_obex_lookup(x, gensym("#B"), (t_object **)&b);
    object_method(b, gensym("dynlet_begin"));
    
    dsp_resize((t_pxobject*)x, x->f_ambiVector->getNumberOfInputs());
    object_method(b, gensym("dynlet_end"));
}



