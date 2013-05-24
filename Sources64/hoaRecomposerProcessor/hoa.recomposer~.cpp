/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#include "AmbisonicsRecomposer.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "ext_path.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "ext_parameter.h"
#include "z_dsp.h"
}


typedef struct _HoaRecomposer 
{
	t_pxobject					f_ob;
    AmbisonicsRecomposer*       f_ambiRecomposer;
    
	long						f_inputNumber;
	long						f_outputNumber;
    t_atom_long                 f_play;
    double                      f_ramp_time;
} t_HoaRecomposer;

void *HoaRecomposer_new(t_symbol *s, long argc, t_atom *argv);
void HoaRecomposer_free(t_HoaRecomposer *x);
void HoaRecomposer_assist(t_HoaRecomposer *x, void *b, long m, long a, char *s);
void HoaRecomposer_angle(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av);
void HoaRecomposer_wide(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av);
t_max_err HoaRecomposer_play(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv);
t_max_err HoaRecomposer_ramp(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv);

void HoaRecomposer_dsp(t_HoaRecomposer *x, t_signal **sp, short *count);
t_int *HoaRecomposer_perform(t_int *w);

void HoaRecomposer_dsp64(t_HoaRecomposer *x,t_object *dsp64,short *count, double samplerate, long maxvectorsize, long flags);
void HoaRecomposer_perform64(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaRecomposer_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.recomposer~", (method)HoaRecomposer_new, (method)HoaRecomposer_free, (long)sizeof(t_HoaRecomposer), 0L, A_GIMME, 0);
	;
    
	class_addmethod(c, (method)HoaRecomposer_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposer_angle,         "angle",    A_GIMME,0);
    class_addmethod(c, (method)HoaRecomposer_wide,          "wide",    A_GIMME,0);
    
    CLASS_ATTR_LONG             (c,"play", 0, t_HoaRecomposer, f_play);
	CLASS_ATTR_LABEL			(c,"play", 0, "Playable");
    CLASS_ATTR_STYLE            (c,"play", 0, "onoff");
	CLASS_ATTR_CATEGORY			(c,"play", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"play", NULL, HoaRecomposer_play);
	CLASS_ATTR_DEFAULT          (c,"play", 0,  "1");
    CLASS_ATTR_ORDER			(c,"play", 0,  "1");
    CLASS_ATTR_SAVE             (c,"play", 1);
    
    CLASS_ATTR_DOUBLE			(c,"ramp", 0, t_HoaRecomposer, f_ramp_time);
	CLASS_ATTR_LABEL			(c,"ramp", 0, "Ramp Time (ms)");
	CLASS_ATTR_CATEGORY			(c,"ramp", 0, "Behavior");
    CLASS_ATTR_ACCESSORS		(c,"ramp", NULL, HoaRecomposer_ramp);
	CLASS_ATTR_DEFAULT          (c,"ramp", 0,  "100.");
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

	int order = 4, inputs = 10;
    x = (t_HoaRecomposer *)object_alloc((t_class*)HoaRecomposer_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			inputs	= atom_getlong(argv+1);

		x->f_ambiRecomposer	= new AmbisonicsRecomposer(order, inputs);
        
		dsp_setup((t_pxobject *)x, x->f_ambiRecomposer->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiRecomposer->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");

		x->f_ob.z_misc = Z_NO_INPLACE;
        
        t_atom av[1];
        atom_setlong(av, 1);
        object_method_typed(x, gensym("play"), 1, av, NULL);
        atom_setfloat(av, 100.);
        object_method_typed(x, gensym("ramp"), 1, av, NULL);
        
        attr_args_process(x, argc, argv);
	}
	return (x);
}

void HoaRecomposer_angle(t_HoaRecomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2 && atom_gettype(av) == A_LONG && atom_gettype(av+1) == A_FLOAT)
        x->f_ambiRecomposer->setMicrophoneAngle(atom_getlong(av), atom_getfloat(av+1));
    else if(atom_gettype(av) == A_FLOAT)
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
    else if(atom_gettype(av) == A_FLOAT)
    {
        for(int i = 0; i < ac; i++)
        {
            if(i < x->f_ambiRecomposer->getNumberOfOutputs() && atom_gettype(av+i) == A_FLOAT)
                x->f_ambiRecomposer->setMicrophoneWide(i, atom_getfloat(av+i));
        }
    }
}

t_max_err HoaRecomposer_play(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_FLOAT)
    {
        int value = 1 - Tools::clip((long)atom_getfloat(argv), (long)0, (long)1);
        x->f_ambiRecomposer->setFixed(value);
    }
    if(argc && argv && atom_gettype(argv) == A_LONG)
    {
        int value = 1 - Tools::clip((long)atom_getlong(argv), (long)0, (long)1);
        x->f_ambiRecomposer->setFixed(value);
        
    }
    x->f_play = 1 - x->f_ambiRecomposer->getFixed();
    return MAX_ERR_NONE;
}

t_max_err HoaRecomposer_ramp(t_HoaRecomposer *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_FLOAT)
    {
        x->f_ambiRecomposer->setRamp(atom_getfloat(argv) * sys_getsr()  / 1000.);
    }
    if(argc && argv && atom_gettype(argv) == A_LONG)
    {
        x->f_ambiRecomposer->setRamp(atom_getlong(argv) * sys_getsr()  / 1000.);
    }
    x->f_ramp_time = Tools::clip_min((float)atom_getfloat(argv), 0.f);
    return MAX_ERR_NONE;
}

void HoaRecomposer_dsp64(t_HoaRecomposer *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiRecomposer->setVectorSize(maxvectorsize);
	x->f_inputNumber = x->f_ambiRecomposer->getNumberOfInputs();
	
    object_method(dsp64, gensym("dsp_add64"), x, HoaRecomposer_perform64, 0, NULL);
}

void HoaRecomposer_perform64(t_HoaRecomposer *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiRecomposer->process(ins, outs);
}

void HoaRecomposer_dsp(t_HoaRecomposer *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ambiRecomposer->setVectorSize(sp[0]->s_n);
	x->f_inputNumber = x->f_ambiRecomposer->getNumberOfInputs();
	x->f_outputNumber = x->f_ambiRecomposer->getNumberOfOutputs();
	pointer_count = x->f_inputNumber + x->f_outputNumber + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
    dsp_addv(HoaRecomposer_perform, pointer_count, (void **)sigvec);
	free(sigvec);
}

t_int *HoaRecomposer_perform(t_int *w)
{
	t_HoaRecomposer *x		= (t_HoaRecomposer *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_inputNumber;
	
	x->f_ambiRecomposer->process(ins, outs);
	
	return (w + x->f_outputNumber + x->f_inputNumber + 3);
}

void HoaRecomposer_assist(t_HoaRecomposer *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_INLET)
	{
        sprintf(s,"(Signal) Harmonic %ld", x->f_ambiRecomposer->getHarmonicIndex(a));
	}
	else 
	{
        sprintf(s,"(Signal) Virtual Microphone %ld", a);
	}
}

void HoaRecomposer_free(t_HoaRecomposer *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiRecomposer;
}

