
/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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

#include "AmbisonicFreeverb.h"

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
	AmbisonicFreeverb	*f_freeverb;
	long                f_freeze;
	float               f_size;
	float               f_damp;
    float               f_dry;
	float               f_wet;
}
t_freeverb ;

void *freeverb_new(t_symbol *s, long argc, t_atom *argv);
void freeverb_free(t_freeverb *x);
void freeverb_assist(t_freeverb *x, void *b, long m, long a, char *s);

t_max_err size_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err damp_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err dry_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err wet_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);
t_max_err freeze_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv);

void freeverb_dsp(t_freeverb *x, t_signal **sp, short *count);
t_int *freeverb_perform(t_int *w);

void freeverb_dsp64(t_freeverb *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void freeverb_perform64(t_freeverb *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *freeverb_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("hoa.freeverb~", (method)freeverb_new, (method)freeverb_free, (long)sizeof(t_freeverb ), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)freeverb_dsp,		"dsp",			A_CANT, 0);
	class_addmethod(c, (method)freeverb_dsp64,		"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)freeverb_assist,		"assist",		A_CANT, 0);
    
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
		
		dsp_setup((t_pxobject *)x, x->f_freeverb->getNumberOfInputs());
		for (int i = 0; i < x->f_freeverb->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		attr_args_process(x, argc, argv);
	}
	return (x);
}

void freeverb_dsp(t_freeverb *x, t_signal **sp, short *count)
{
	x->f_freeverb->setVectorSize(sp[0]->s_n);
    x->f_freeverb->setSamplingRate(sp[0]->s_sr);
	dsp_add(freeverb_perform, 3, x, sp[0]->s_vec, sp[1]->s_vec);
}

t_int *freeverb_perform(t_int *w)
{
	t_freeverb*	x	= (t_freeverb *)(w[1]);
	float**		ins	= (float **)(w+2);
	float**		outs= (float **)(w+3);

	x->f_freeverb->process(ins, outs);

	return (w + 4);
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
    long harmonicIndex = 0;
	if (a == 0)
		harmonicIndex = 0;
	else
	{
		harmonicIndex = (a - 1) / 2 + 1;
		if (a % 2 == 1)
			harmonicIndex = - harmonicIndex;
	}
	sprintf(s,"(Signal) Harmonic %ld", harmonicIndex);
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

t_max_err freeze_set(t_freeverb *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_freeverb->setmode(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_freeverb->setmode(atom_getfloat(argv));

	x->f_freeze = x->f_freeverb->getmode();
	return 0;
}