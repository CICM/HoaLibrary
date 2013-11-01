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
	#include "buffer.h"
	#include "ext_globalsymbol.h"
}


typedef struct _freeverb
{
	t_pxobject          f_ob;	
	AmbisonicFreeverb*  f_freeverb;
	long                f_freeze;
	float               f_size;
	float               f_damp;
    float               f_dry;
	float               f_wet;
    float               f_first_spread;
    float               f_late_spread;
} t_freeverb ;

void *freeverb_new(t_symbol *s, long argc, t_atom *argv);
void freeverb_free(t_freeverb *x);
void freeverb_assist(t_freeverb *x, void *b, long m, long a, char *s);
void freeverb_spread(t_freeverb *x, t_symbol *sym, long argc, t_atom *argv);

t_max_err size_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err damp_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err dry_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err wet_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err first_spread_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err late_spread_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err freeze_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);

void freeverb_dsp64(t_freeverb *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void freeverb_perform64(t_freeverb *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *freeverb_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.freeverb~", (method)freeverb_new, (method)freeverb_free, (long)sizeof(t_freeverb ), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)freeverb_dsp64,		"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)freeverb_assist,		"assist",		A_CANT, 0);
    class_addmethod(c, (method)freeverb_spread,		"spread",		A_GIMME, 0);
    
	CLASS_ATTR_FLOAT			(c, "size", 0, t_freeverb, f_size);
	CLASS_ATTR_CATEGORY			(c, "size", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "size", 0, "Room size");
	CLASS_ATTR_ORDER			(c, "size", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "size", NULL, size_set);
	CLASS_ATTR_DEFAULT			(c, "size", 0, "0.5");
	CLASS_ATTR_FILTER_MIN		(c, "size", 0);
	CLASS_ATTR_SAVE				(c, "size", 1);

	CLASS_ATTR_FLOAT			(c, "damp", 0, t_freeverb, f_damp);
	CLASS_ATTR_CATEGORY			(c, "damp", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "damp", 0, "Damping value");
	CLASS_ATTR_ORDER			(c, "damp", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "damp", NULL, damp_set);
	CLASS_ATTR_DEFAULT			(c, "damp", 0, "0.5");
	CLASS_ATTR_FILTER_MIN		(c, "damp", 0);
	CLASS_ATTR_SAVE				(c, "damp", 1);
    
    CLASS_ATTR_FLOAT			(c, "dry", 0, t_freeverb, f_dry);
	CLASS_ATTR_CATEGORY			(c, "dry", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "dry", 0, "Dry value");
	CLASS_ATTR_ORDER			(c, "dry", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "dry", NULL, dry_set);
	CLASS_ATTR_DEFAULT			(c, "dry", 0, "0.");
	CLASS_ATTR_FILTER_MIN		(c, "dry", 0);
	CLASS_ATTR_SAVE				(c, "dry", 1);
    
    CLASS_ATTR_FLOAT			(c, "wet", 0, t_freeverb, f_wet);
	CLASS_ATTR_CATEGORY			(c, "wet", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "wet", 0, "Wet value");
	CLASS_ATTR_ORDER			(c, "wet", 0, "4");
	CLASS_ATTR_ACCESSORS		(c, "wet", NULL, wet_set);
	CLASS_ATTR_DEFAULT			(c, "wet", 0, "1.");
	CLASS_ATTR_FILTER_MIN		(c, "wet", 0);
	CLASS_ATTR_SAVE				(c, "wet", 1);

    CLASS_ATTR_FLOAT			(c, "fspread", 0, t_freeverb, f_first_spread);
	CLASS_ATTR_CATEGORY			(c, "fspread", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "fspread", 0, "First spread");
	CLASS_ATTR_ORDER			(c, "fspread", 0, "5");
	CLASS_ATTR_ACCESSORS		(c, "fspread", NULL, first_spread_set);
	CLASS_ATTR_DEFAULT			(c, "fspread", 0, "0.2");
	CLASS_ATTR_SAVE				(c, "fspread", 1);
    
    CLASS_ATTR_FLOAT			(c, "lspread", 0, t_freeverb, f_late_spread);
	CLASS_ATTR_CATEGORY			(c, "lspread", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "lspread", 0, "Late spread");
	CLASS_ATTR_ORDER			(c, "lspread", 0, "6");
	CLASS_ATTR_ACCESSORS		(c, "lspread", NULL, late_spread_set);
	CLASS_ATTR_DEFAULT			(c, "lspread", 0, "0.2");
	CLASS_ATTR_SAVE				(c, "lspread", 1);
    
	CLASS_ATTR_LONG				(c, "freeze", 0, t_freeverb, f_freeze);
	CLASS_ATTR_CATEGORY			(c, "freeze", 0, "Behaviors");
	CLASS_ATTR_STYLE_LABEL		(c, "freeze", 0, "onoff", "Freeze");
	CLASS_ATTR_ACCESSORS		(c, "freeze", NULL, freeze_set);
	CLASS_ATTR_DEFAULT			(c, "freeze", 0, "0");
	CLASS_ATTR_SAVE				(c, "freeze", 1);

	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	freeverb_class = c;
    
    class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	
	return 0;
}

void *freeverb_new(t_symbol *s, long argc, t_atom *argv)
{
	t_freeverb *x = NULL;
	int anOrder = 4;
    x = ((t_freeverb *)object_alloc(freeverb_class));
	if (x)
	{	
		if(atom_gettype(argv) == A_LONG)
			anOrder = atom_getlong(argv);

		x->f_freeverb = new AmbisonicFreeverb(anOrder);
        x->f_freeverb->setroomsize(0.75);
        x->f_freeverb->setdamp(0.5);
        x->f_freeverb->setDryValue(0.);
        x->f_freeverb->setWetValue(1.);
        x->f_freeverb->setSpread(0.2);
        x->f_freeverb->setmode(0);
        
        
		object_method(x, gensym("size"), NULL, NULL);
        object_method(x, gensym("damp"), NULL, NULL);
        object_method(x, gensym("dry"), NULL, NULL);
        object_method(x, gensym("wet"), NULL, NULL);
        object_method(x, gensym("fspread"), NULL, NULL);
        object_method(x, gensym("lspread"), NULL, NULL);
        object_method(x, gensym("freeze"), NULL, NULL);
        
        x->f_first_spread = x->f_late_spread = 0.2;
        
		dsp_setup((t_pxobject *)x, x->f_freeverb->getNumberOfInputs());
		for (int i = 0; i < x->f_freeverb->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		attr_args_process(x, argc, argv);
	}
	return (x);
}

void freeverb_dsp64(t_freeverb *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_freeverb->setVectorSize(maxvectorsize);
    x->f_freeverb->setSamplingRate(samplerate);
	object_method(dsp64, gensym("dsp_add64"), x, freeverb_perform64, 0, NULL);
}

void freeverb_perform64(t_freeverb *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_freeverb->process(ins, outs);
}

void freeverb_assist(t_freeverb *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_freeverb->getHarmonicsName(a).c_str());
}

void freeverb_free(t_freeverb *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_freeverb;
}

t_max_err size_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_freeverb->setroomsize(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_freeverb->setroomsize(atom_getfloat(argv));

	x->f_size = x->f_freeverb->getroomsize();
	return 0;
}


t_max_err damp_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_freeverb->setdamp(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_freeverb->setdamp(atom_getfloat(argv));

	x->f_damp = x->f_freeverb->getdamp();
	return 0;
}

t_max_err dry_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_freeverb->setDryValue(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_freeverb->setDryValue(atom_getfloat(argv));
    
	x->f_dry = x->f_freeverb->getDryValue();
	return 0;
}


t_max_err wet_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_freeverb->setWetValue(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_freeverb->setWetValue(atom_getfloat(argv));
    
	x->f_wet = x->f_freeverb->getWetValue();
	return 0;
}

t_max_err first_spread_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_freeverb->setDirectionalSpread(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_freeverb->setDirectionalSpread(atom_getfloat(argv));
        
	x->f_first_spread = x->f_freeverb->getDirectionalSpread();
	return 0;
}

void freeverb_spread(t_freeverb *x, t_symbol *sym, long argc, t_atom *argv)
{
    object_method(x, gensym("fspread"), argc, argv);
    object_method(x, gensym("lspread"), argc, argv);
}

t_max_err late_spread_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_freeverb->setDiffuseSpread(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_freeverb->setDiffuseSpread(atom_getfloat(argv));
    
	x->f_late_spread = x->f_freeverb->getDiffuseSpread();
	return 0;
}

t_max_err freeze_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_freeverb->setmode(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_freeverb->setmode(atom_getfloat(argv));

	x->f_freeze = x->f_freeverb->getmode();
	return 0;
}