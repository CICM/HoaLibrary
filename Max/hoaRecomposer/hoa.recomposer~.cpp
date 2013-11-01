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

typedef struct _HoaRecomposer
{
	t_pxobject					f_ob;
	AmbisonicRecomposer*       f_ambiRecomposer;
    
	long						f_inputNumber;
	long						f_outputNumber;
    t_symbol*                   f_mode;
    double                      f_ramp_time;
    
} t_HoaRecomposer;

void *HoaRecomposer_new(t_symbol *s, long argc, t_atom *argv);
void HoaRecomposer_free(t_HoaRecomposer *x);
void HoaRecomposer_assist(t_HoaRecomposer *x, void *b, long m, long a, char *s);
void HoaRecomposer_angle(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av);
void HoaRecomposer_wide(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av);
t_max_err HoaRecomposer_set_attr_mode(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv);
t_max_err HoaRecomposer_ramp(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv);
void HoaRecomposer_float(t_HoaRecomposer *x, double d);
t_max_err HoaRecomposer_notify(t_HoaRecomposer *x, t_symbol *s, t_symbol *msg, void *sender, void *data);


void HoaRecomposer_dsp64(t_HoaRecomposer *x,t_object *dsp64,short *count, double samplerate, long maxvectorsize, long flags);
void HoaRecomposer_perform64_free(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaRecomposer_perform64_fisheye(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaRecomposer_perform64_fixe(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaRecomposer_perform64_fisheye_offset(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaRecomposer_class;

int C74_EXPORT main(void)
{
    
	t_class *c;
	
	c = class_new("hoa.recomposer~", (method)HoaRecomposer_new, (method)HoaRecomposer_free, (long)sizeof(t_HoaRecomposer), 0L, A_GIMME, 0);
	;

	class_addmethod(c, (method)HoaRecomposer_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_angle,         "angles",    A_GIMME,0);
    class_addmethod(c, (method)HoaRecomposer_wide,          "directivities",     A_GIMME,0);
    class_addmethod(c, (method)HoaRecomposer_float,         "float",    A_FLOAT,0);
    
    CLASS_ATTR_SYM              (c,"mode", 0, t_HoaRecomposer, f_mode);
	CLASS_ATTR_LABEL			(c,"mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c,"mode", 0, "fixe fisheye free");
	CLASS_ATTR_CATEGORY			(c,"mode", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"mode", NULL, HoaRecomposer_set_attr_mode);
    CLASS_ATTR_ORDER			(c,"mode", 0,  "1");
    CLASS_ATTR_SAVE             (c,"mode", 1);
    
    CLASS_ATTR_DOUBLE			(c,"ramp", 0, t_HoaRecomposer, f_ramp_time);
	CLASS_ATTR_LABEL			(c,"ramp", 0, "Ramp Time in milliseconds");
	CLASS_ATTR_CATEGORY			(c,"ramp", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"ramp", NULL, HoaRecomposer_ramp);
    CLASS_ATTR_ORDER			(c,"ramp", 0,  "2");
    CLASS_ATTR_SAVE             (c,"ramp", 1);
    
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	HoaRecomposer_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaRecomposer_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaRecomposer *x = NULL;
    t_dictionary *d;
	int order = 4, inputs = 10;
    x = (t_HoaRecomposer *)object_alloc((t_class*)HoaRecomposer_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			inputs	= atom_getlong(argv+1);
        
        /* Base Attributes */
        
		x->f_ambiRecomposer	= new AmbisonicRecomposer(order, inputs, Hoa_Fixe, sys_getblksize(), sys_getsr());
        x->f_ambiRecomposer->setRampInMs(20.);
        
        x->f_ramp_time = x->f_ambiRecomposer->getRampInMs();
        x->f_mode = gensym("fixe");
        
		dsp_setup((t_pxobject *)x, x->f_ambiRecomposer->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiRecomposer->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
        
		x->f_ob.z_misc = Z_NO_INPLACE;
        
        attr_args_process(x, argc, argv);
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        object_attr_setdisabled((t_object *)x, gensym("ramp"), (x->f_mode == gensym("fixe")) ? 1 : 0);
	}
	return (x);
}

void HoaRecomposer_angle(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2 && atom_gettype(av) == A_LONG && atom_gettype(av+1) == A_FLOAT)
        x->f_ambiRecomposer->setMicrophoneAngle(atom_getlong(av), atom_getfloat(av+1));
    else
    {
        for(int i = 0; i < ac; i++)
        {
            if(i < x->f_ambiRecomposer->getNumberOfOutputs() && atom_gettype(av+i) == A_FLOAT)
                x->f_ambiRecomposer->setMicrophoneAngle(i, atom_getfloat(av+i));
        }
    }
}

void HoaRecomposer_wide(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2 && atom_gettype(av) == A_LONG && atom_gettype(av+1) == A_FLOAT)
        x->f_ambiRecomposer->setMicrophoneWide(atom_getlong(av), atom_getfloat(av+1));
    else
    {
        for(int i = 0; i < ac; i++)
        {
            if(i < x->f_ambiRecomposer->getNumberOfOutputs() && atom_gettype(av+i) == A_FLOAT)
                x->f_ambiRecomposer->setMicrophoneWide(i, atom_getfloat(av+i));
        }
    }
}

void HoaRecomposer_float(t_HoaRecomposer *x, double f)
{
    if(x->f_ambiRecomposer->getMode() == Hoa_Fisheye)
        x->f_ambiRecomposer->setFishEyeFactor(f);
}

t_max_err HoaRecomposer_set_attr_mode(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv)
{
    long lastNumberOfInputs = x->f_ambiRecomposer->getNumberOfInputs();
    
    if(argc && argv)
    {
        int dspState = sys_getdspobjdspstate((t_object*)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        if(atom_gettype(argv) == A_SYM)
        {
            t_symbol* newModeSym = atom_getsym(argv);
            int newModeInt = (newModeSym == gensym("free")) ? Hoa_Free : (newModeSym == gensym("fisheye")) ? Hoa_Fisheye : 0;
            x->f_ambiRecomposer->setMode(newModeInt);
        }
        else if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
        {
            x->f_ambiRecomposer->setMode(atom_getfloat(argv));
        }
        
        int newModeInt = x->f_ambiRecomposer->getMode();
        x->f_mode = (newModeInt == Hoa_Free) ? gensym("free") : (newModeInt == Hoa_Fisheye) ? gensym("fisheye") : gensym("fixe");
        
        if (lastNumberOfInputs != x->f_ambiRecomposer->getNumberOfInputs())
        {
            t_object *b = NULL;
			object_obex_lookup(x, gensym("#B"), (t_object **)&b);
            object_method(b, gensym("dynlet_begin"));
            dsp_resize((t_pxobject*)x, x->f_ambiRecomposer->getNumberOfInputs());
            object_method(b, gensym("dynlet_end"));
            
        }
        if(x->f_ambiRecomposer->getMode() == Hoa_Fixe)
            object_attr_setdisabled((t_object *)x, gensym("ramp"), 1);
        else
            object_attr_setdisabled((t_object *)x, gensym("ramp"), 0);
    }
    return MAX_ERR_NONE;
}

t_max_err HoaRecomposer_ramp(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        x->f_ambiRecomposer->setRampInMs(atom_getfloat(argv));
        x->f_ramp_time = x->f_ambiRecomposer->getRampInMs();
    }
    return MAX_ERR_NONE;
}

void HoaRecomposer_dsp64(t_HoaRecomposer *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiRecomposer->setVectorSize(maxvectorsize);
    x->f_ambiRecomposer->setSamplingRate(samplerate);
    
    if (x->f_ambiRecomposer->getMode() == Hoa_Free)
        object_method(dsp64, gensym("dsp_add64"), x, HoaRecomposer_perform64_free, 0, NULL);
    else if(x->f_ambiRecomposer->getMode() == Hoa_Fixe)
        object_method(dsp64, gensym("dsp_add64"), x, HoaRecomposer_perform64_fixe, 0, NULL);
    else
    {
        if(count[x->f_ambiRecomposer->getNumberOfInputs()-1])
            object_method(dsp64, gensym("dsp_add64"), x, HoaRecomposer_perform64_fisheye, 0, NULL);
        else
            object_method(dsp64, gensym("dsp_add64"), x, HoaRecomposer_perform64_fisheye_offset, 0, NULL);
    }
}

void HoaRecomposer_perform64_free(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_ambiRecomposer->processFree(ins, outs);
}

void HoaRecomposer_perform64_fixe(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_ambiRecomposer->processFixe(ins, outs);
}

void HoaRecomposer_perform64_fisheye(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_ambiRecomposer->processFisheye(ins, outs, ins[x->f_ambiRecomposer->getNumberOfInputs()-1]);
}

void HoaRecomposer_perform64_fisheye_offset(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_ambiRecomposer->processFisheye(ins, outs);
}

void HoaRecomposer_assist(t_HoaRecomposer *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_ambiRecomposer->getHarmonicsName(a).c_str());
	else
        sprintf(s,"(Signal) %s", x->f_ambiRecomposer->getMicrophonesName(a).c_str());
}

void HoaRecomposer_free(t_HoaRecomposer *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiRecomposer;
}

