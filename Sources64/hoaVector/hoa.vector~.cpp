/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#define MAX_SPEAKER 256

#include "AmbisonicsVector.h"

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
	t_pxobject					f_ob;
	Ambisonicsvector            *f_ambiVector;

	long						f_inputNumber;
	long						f_outputNumber;
    
    t_symbol*               f_output_mode; 
    t_symbol*               f_mode;
    t_atom_long             f_number_of_ambisonics_loudspeakers;
    double                  f_offset_of_ambisonics_loudspeakers;
    
    t_atom_long             f_number_of_loudspeakers;
    double                  f_configuration_of_loudspeakers;
    double                  f_angles_of_loudspeakers[MAX_SPEAKER];
    
} t_HoaVector;

void *HoaVector_new(t_symbol *s, long argc, t_atom *argv);
void HoaVector_free(t_HoaVector* x);
void HoaVector_assist(t_HoaVector* x, void *b, long m, long a, char *s);
t_max_err mode_set(t_HoaVector *x, t_object *attr, long ac, t_atom *av);
t_max_err configuration_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv);

t_max_err config_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv);

void HoaVector_resize_inlet(t_HoaVector *x, long lastNumberOfOutlet);
void HoaVector_dsp(t_HoaVector* x, t_signal **sp, short *count);
t_int *HoaVector_perform(t_int *w);

void HoaVector_dsp64(t_HoaVector* x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaVector_perform64(t_HoaVector* x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaVector_class;

int C74_EXPORT main(void)
{	
    common_symbols_init();
	t_class *c;
	
	c = class_new("hoa.vector~", (method)HoaVector_new, (method)HoaVector_free, (long)sizeof(t_HoaVector), 0L, A_GIMME, 0);

	class_addmethod(c, (method)HoaVector_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaVector_dsp64,     "dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaVector_assist,    "assist",	A_CANT, 0);
    
    CLASS_ATTR_SYM					(c, "output", 0, t_HoaVector, f_output_mode);
	CLASS_ATTR_CATEGORY				(c, "output", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "output", 0, "1");
    CLASS_ATTR_ENUMINDEX            (c, "output", 0, "Polar \" Cartesian");
    CLASS_ATTR_ACCESSORS            (c, "output", NULL, mode_set);
	CLASS_ATTR_LABEL                (c, "output", 0, "Coordinates type");
	CLASS_ATTR_DEFAULT				(c, "output", 0, "1");
	CLASS_ATTR_SAVE					(c, "output", 1);
    
    /* Attribut Global */
    CLASS_ATTR_SYM              (c, "mode", 0, t_HoaVector, f_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c, "mode", 0, "ambisonics \" \"binaural \" \"irregular");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, configuration_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    CLASS_ATTR_SAVE             (c, "mode", 1);
    
    /* Ambisonics Mode */
    CLASS_ATTR_LONG             (c, "loudspeakers", 0, t_HoaDecode, f_number_of_ambisonics_loudspeakers);
	CLASS_ATTR_CATEGORY			(c, "loudspeakers", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_ACCESSORS		(c, "loudspeakers", NULL, loudspeakers_set);
    CLASS_ATTR_ORDER            (c, "loudspeakers", 0, "2");
    CLASS_ATTR_SAVE             (c, "loudspeakers", 1);
    CLASS_ATTR_ALIAS            (c, "loudspeakers", "ls");
    
    CLASS_ATTR_DOUBLE           (c, "offset", 0, t_HoaDecode, f_offset_of_ambisonics_loudspeakers);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "offset", 0, "Offset of Loudspeakers");
	CLASS_ATTR_ACCESSORS		(c, "offset", NULL, offset_set);
    CLASS_ATTR_ORDER            (c, "offset", 0, "3");
	CLASS_ATTR_SAVE             (c, "offset", 1);
    
    /* Binaural */
    CLASS_ATTR_SYM              (c, "pinnaesize", 0, t_HoaDecode, f_pinna_size);
	CLASS_ATTR_CATEGORY			(c, "pinnaesize", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "pinnaesize", 0, "Pinnae Size");
    CLASS_ATTR_ENUM             (c, "pinnaesize", 0, "small large");
	CLASS_ATTR_ACCESSORS		(c, "pinnaesize", NULL, pinnaesize_set);
    CLASS_ATTR_ORDER            (c, "pinnaesize", 0, "4");
    CLASS_ATTR_SAVE             (c, "pinnaesize", 1);
    
    CLASS_ATTR_DOUBLE               (c, "config", 0, t_HoaVector, f_configuration_of_loudspeakers);
	CLASS_ATTR_CATEGORY             (c, "config", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "config", 0, "Configuration");
	CLASS_ATTR_ACCESSORS            (c, "config", NULL, config_set);
    CLASS_ATTR_ORDER                (c, "config", 0, "2");
	CLASS_ATTR_SAVE                 (c, "config", 1);
    
    CLASS_ATTR_DOUBLE_VARSIZE       (c, "angles", 0, t_HoaVector, f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_CATEGORY             (c, "angles", 0, "Behavior");
    CLASS_ATTR_LABEL                (c, "angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_ACCESSORS            (c, "angles", NULL, angles_set);
    CLASS_ATTR_ORDER                (c, "angles", 0, "3");
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
	t_HoaVector* x = NULL;
    x = (t_HoaVector*)object_alloc((t_class*)HoaVector_class);
	if (x)
	{
		x->f_ambiVector = new Ambisonicsvector();
		
		dsp_setup((t_pxobject *)x, x->f_ambiVector->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiVector->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
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
    if(ac && av && atom_gettype(av) == A_SYM)
    {
        if(atom_getsym(av) == gensym("cartesian") || atom_getsym(av) == gensym(" cartesian"))
            x->f_ambiVector->setMode(Hoa_Cartesian);
        else
            x->f_ambiVector->setMode(Hoa_Polar);
    }
    
    if(x->f_ambiVector->getMode() == Hoa_Polar)
        x->f_output_mode = gensym("cartesian");
    else
        x->f_output_mode = gensym("polar");
    return MAX_ERR_NONE;
}

t_max_err configuration_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
    
    long numOutlet = x->f_ambiVector->getNumberOfOutputs();
	if(atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == gensym("binaural") || atom_getsym(argv) == gensym(" binaural"))
        {
            x->f_ambiVector->setConfiguration(2., 0);
            x->f_mode = gensym("binaural");
            object_attr_addattr_parse((t_object*)x, "config", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "angles", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "offset", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "loudspeakers", "invisible", USESYM(long), 1, "1");
        }
        else if(atom_getsym(argv) == gensym("irregular") || atom_getsym(argv) == gensym(" irregular"))
        {
            x->f_ambiVector->setConfiguration(x->f_configuration_of_loudspeakers);
            x->f_mode = gensym("irregular");
            object_attr_addattr_parse((t_object*)x, "config", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "angles", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "offset", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "loudspeakers", "invisible", USESYM(long), 1, "1");
        }
        else
        {
            x->f_ambiVector->setConfiguration(x->f_configuration_of_loudspeakers, 0);
            x->f_mode = gensym("ambisonics");
            object_attr_addattr_parse((t_object*)x, "config", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "angles", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "offset", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "pinnaesize", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "loudspeakers", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "restitution", "invisible", USESYM(long), 1, "1");
        }
	}
    
    HoaVector_resize_inlet(x, numOutlet);
    
    return NULL;
}

t_max_err loudspeakers_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Ambisonics)
    {
        int dspState = sys_getdspobjdspstate((t_object*)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        long numOutlet = x->f_AmbisonicsDecoder->getNumberOfOutputs();
        
        if(atom_gettype(argv) == A_LONG)
            x->f_AmbisonicsDecoder->setNumberOfLoudspeakers(atom_getlong(argv));
        else if(atom_gettype(argv) == A_FLOAT)
            x->f_AmbisonicsDecoder->setNumberOfLoudspeakers(atom_getfloat(argv));
        
        HoaDecode_resize_outlet(x, numOutlet);
    }
    x->f_number_of_ambisonics_loudspeakers = x->f_AmbisonicsDecoder->getNumberOfLoudspeakers();
    return NULL;
}

t_max_err offset_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Ambisonics)
    {
        if(atom_gettype(argv) == A_FLOAT)
            x->f_AmbisonicsDecoder->setOffset(atom_getfloat(argv));
        else if(atom_gettype(argv) == A_LONG)
            x->f_AmbisonicsDecoder->setOffset(atom_getlong(argv));
    }
    x->f_offset_of_ambisonics_loudspeakers = x->f_AmbisonicsDecoder->getOffset();
    
    return NULL;
}

t_max_err config_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution)
    {
        long standard = 1;
        int dspState = sys_getdspobjdspstate((t_object*)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        long numOutlet = x->f_AmbisonicsDecoder->getNumberOfOutputs();
        if(argc == 2 && atom_gettype(argv+1) == A_LONG && atom_getlong(argv+1) == 0)
            standard = 0;
        if(atom_gettype(argv) == A_FLOAT)
            x->f_AmbisonicsDecoder->setConfiguration(atom_getfloat(argv), standard);
        else if(atom_gettype(argv) == A_LONG)
            x->f_AmbisonicsDecoder->setConfiguration(atom_getlong(argv), standard);
        
        HoaDecode_resize_outlet(x, numOutlet);
    }
    x->f_configuration_of_irregular_loudspeakers = x->f_AmbisonicsDecoder->getConfiguration();
    x->f_number_of_irregular_loudspeakers = x->f_configuration_of_irregular_loudspeakers;
    for(int i = 0; i < x->f_number_of_irregular_loudspeakers; i++)
    {
        x->f_angles_of_irregular_loudspeakers[i] = x->f_AmbisonicsDecoder->getLoudspeakerAngle(i);
    }
    object_attr_touch((t_object*)x, gensym("angles"));
    return NULL;
}

t_max_err angles_set(t_HoaVector *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution)
    {
        if(argc && argv)
        {
            for(int i = 0; i < argc; i++)
            {
                if(atom_gettype(argv+i) == A_FLOAT)
                    x->f_AmbisonicsDecoder->setLoudspeakerAngle(i, atom_getfloat(argv+i));
                else if(atom_gettype(argv+i) == A_LONG)
                    x->f_AmbisonicsDecoder->setLoudspeakerAngle(i, atom_getlong(argv+i));
            }
        }
    }
    
    for(int i = 0; i < x->f_number_of_irregular_loudspeakers; i++)
    {
        x->f_angles_of_irregular_loudspeakers[i] = x->f_AmbisonicsDecoder->getLoudspeakerAngle(i);
    }
    HoaDecode_send_angles(x);
    
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



