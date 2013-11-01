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

typedef struct _HoaConvolve 
{
	t_pxobject			f_ob;			
	AmbisonicConvolver*	f_ambiConvolve;

	t_symbol*			f_name;
	t_buffer*			f_buffer;
	long				f_channel;
	long				f_numberOfHarmonics;
	
	double              f_wet;
    double              f_dry;

} t_HoaConvolve;

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv);
void HoaConvolve_free(t_HoaConvolve *x);
void HoaConvolve_assist(t_HoaConvolve *x, void *b, long m, long a, char *s);
void HoaConvolve_clear(t_HoaConvolve *x);

void buffer_setup(t_HoaConvolve *x);
void HoaConvolve_dblclick(t_HoaConvolve *x);
t_max_err buffer_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err dry_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err wet_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err HoaConvolve_notify(t_HoaConvolve *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void HoaConvolve_dsp(t_HoaConvolve *x, t_signal **sp, short *count);
t_int *HoaConvolve_perform(t_int *w);
t_int *HoaConvolve_performOffset(t_int *w);

void HoaConvolve_dsp64(t_HoaConvolve *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaConvolve_perform64(t_HoaConvolve *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaConvolve_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.convolve~", (method)HoaConvolve_new, (method)HoaConvolve_free, (long)sizeof(t_HoaConvolve), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaConvolve_dsp,			"dsp",		A_CANT,     0);
	class_addmethod(c, (method)HoaConvolve_dsp64,		"dsp64",	A_CANT,     0);
	class_addmethod(c, (method)HoaConvolve_assist,		"assist",	A_CANT,     0);
    class_addmethod(c, (method)HoaConvolve_notify,		"notify",	A_CANT,     0);
	class_addmethod(c, (method)HoaConvolve_dblclick,    "dblclick", A_CANT,     0);
    class_addmethod(c, (method)HoaConvolve_clear,       "clear",                0);
    
	CLASS_ATTR_SYM              (c, "buffer",   0, t_HoaConvolve, f_name);
	CLASS_ATTR_CATEGORY			(c, "buffer",   0, "Behavior");
	CLASS_ATTR_LABEL			(c, "buffer",   0, "buffer~ Object Name");
	CLASS_ATTR_ORDER			(c, "buffer",   0, "1");
	CLASS_ATTR_ACCESSORS		(c, "buffer",   NULL, buffer_set);
	CLASS_ATTR_DEFAULT			(c, "buffer",   0, "");
	CLASS_ATTR_SAVE				(c, "buffer",   1);

	CLASS_ATTR_LONG             (c, "channel",  0, t_HoaConvolve, f_channel);
	CLASS_ATTR_CATEGORY			(c, "channel",  0, "Behavior");
	CLASS_ATTR_LABEL			(c, "channel",  0, "buffer~ Object Channel");
	CLASS_ATTR_ORDER			(c, "channel",  0, "2");
	CLASS_ATTR_ACCESSORS		(c, "channel",  NULL, channel_set);
	CLASS_ATTR_DEFAULT			(c, "channel",  0, "1");
	CLASS_ATTR_SAVE				(c, "channel",  1);
    
    CLASS_ATTR_DOUBLE			(c, "dry",      0, t_HoaConvolve, f_dry);
	CLASS_ATTR_CATEGORY			(c, "dry",      0, "Parameters");
	CLASS_ATTR_LABEL			(c, "dry",      0, "Dry value");
	CLASS_ATTR_ORDER			(c, "dry",      0, "1");
	CLASS_ATTR_ACCESSORS		(c, "dry",      NULL, dry_set);
	CLASS_ATTR_DEFAULT			(c, "dry",      0, "0.");
	CLASS_ATTR_SAVE				(c, "dry",      1);
    
    CLASS_ATTR_DOUBLE			(c, "wet",      0, t_HoaConvolve, f_wet);
	CLASS_ATTR_CATEGORY			(c, "wet",      0, "Parameters");
	CLASS_ATTR_LABEL			(c, "wet",      0, "Wet value");
	CLASS_ATTR_ORDER			(c, "wet",      0, "2");
	CLASS_ATTR_ACCESSORS		(c, "wet",      NULL, wet_set);
	CLASS_ATTR_DEFAULT			(c, "wet",      0, "1.");
	CLASS_ATTR_SAVE				(c, "wet",      1);
    

	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaConvolve_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaConvolve *x = NULL;

	long order = 4;
    x = (t_HoaConvolve *)object_alloc((t_class*)HoaConvolve_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
        if(order < 1)
            order = 1;

		x->f_ambiConvolve	= new AmbisonicConvolver(order, sys_getsr(), sys_getblksize());
		x->f_numberOfHarmonics = x->f_ambiConvolve->getNumberOfHarmonics();
       
        x->f_buffer = NULL;
         
		dsp_setup((t_pxobject *)x, x->f_ambiConvolve->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiConvolve->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		attr_args_process(x, argc, argv);
		buffer_setup(x);
	}
	return (x);
}

void HoaConvolve_clear(t_HoaConvolve *x)
{
    x->f_ambiConvolve->clear();
}

void HoaConvolve_dsp64(t_HoaConvolve *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiConvolve->setVectorSize(maxvectorsize);
    if(x->f_ambiConvolve->getSamplingRate() != samplerate)
        x->f_ambiConvolve->setSamplingRate(samplerate);
	object_method(dsp64, gensym("dsp_add64"), x, HoaConvolve_perform64, 0, NULL);
}

void HoaConvolve_perform64(t_HoaConvolve *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiConvolve->process(ins, outs);
}

void HoaConvolve_dsp(t_HoaConvolve *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
	x->f_ambiConvolve->setVectorSize(sp[0]->s_n);
    if(x->f_ambiConvolve->getSamplingRate() != sp[0]->s_sr)
        x->f_ambiConvolve->setSamplingRate(sp[0]->s_sr);
    
	pointer_count = x->f_ambiConvolve->getNumberOfInputs() + x->f_ambiConvolve->getNumberOfOutputs() + 2;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;

	dsp_addv(HoaConvolve_perform, pointer_count, (void **)sigvec);
	free(sigvec);
}

t_int *HoaConvolve_perform(t_int *w)
{
	t_HoaConvolve *x		= (t_HoaConvolve *)(w[1]);
	t_float		**ins		= (t_float **)w+3;
	t_float		**outs		= (t_float **)w+3+x->f_ambiConvolve->getNumberOfOutputs();
	
	x->f_ambiConvolve->process(ins, outs);
	
	return (w + x->f_ambiConvolve->getNumberOfInputs() + x->f_ambiConvolve->getNumberOfOutputs() + 3);
}

void HoaConvolve_assist(t_HoaConvolve *x, void *b, long m, long a, char *s)
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

void HoaConvolve_free(t_HoaConvolve *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiConvolve;
}

t_max_err HoaConvolve_notify(t_HoaConvolve *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if(msg == gensym("globalsymbol_binding"))
	{
		x->f_buffer = (t_buffer*)x->f_name->s_thing;
	}
	else if (msg == gensym("globalsymbol_unbinding"))
	{
		x->f_buffer = NULL;
	}
	else if (msg == gensym("buffer_modified"))
	{
		buffer_setup(x);
	}
	return object_notify(x, s, data);
}

void HoaConvolve_dblclick(t_HoaConvolve *x)
{
	t_buffer *b;
	
	if ((b = (t_buffer *)(x->f_name->s_thing)) && ob_sym(b) == gensym("buffer~"))
		mess0((t_object *)b,gensym("dblclick"));
}

t_max_err buffer_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	t_buffer *b;
	t_symbol *name;
	t_atom channel[1];
    
	if(argc && argv && atom_gettype(argv) == A_SYM)
	{
		name = atom_getsym(argv);
		if(x->f_name != name)
		{
			if ((b = (t_buffer *)(name->s_thing)) && ob_sym(b) == gensym("buffer~"))
			{
				if(x->f_name && x->f_buffer != NULL)
				{
					globalsymbol_dereference((t_object*)x, x->f_name->s_name, "buffer~");
				}
				x->f_name = name;
				x->f_buffer = (t_buffer*)globalsymbol_reference((t_object*)x, x->f_name->s_name, "buffer~");
				
			}
			else
			{
				x->f_buffer = NULL;
				x->f_name= gensym("none");
			}
		}
        
        atom_setlong(channel, x->f_channel);
        channel_set(x, attr, 2, channel);
	}
	return MAX_ERR_NONE;
}

    
t_max_err channel_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(argc && argv && atom_gettype(argv) == A_LONG )
	{
		if(x->f_buffer != NULL)
		{
            if(atom_getlong(argv) >= 1)
                x->f_channel = atom_getlong(argv);
			else
			{
				if(atom_getlong(argv) <= x->f_buffer->b_nchans && atom_getlong(argv) >= 1)
					x->f_channel = atom_getlong(argv);
				else if(atom_getlong(argv) < 1)
					x->f_channel = 1;
				else
					x->f_channel = x->f_buffer->b_nchans;
			}
		}
		buffer_setup(x);
	}
	return MAX_ERR_NONE;
}

void buffer_setup(t_HoaConvolve *x)
{
		int vectorSize = 0;
        if(x->f_buffer != NULL)
        {
            if(vectorSize < x->f_buffer->b_frames)
				vectorSize = x->f_buffer->b_frames;
            float* datas = new float[vectorSize];
            
            ATOMIC_INCREMENT(&x->f_buffer->b_inuse);
            if (!x->f_buffer->b_valid)
            {
                ATOMIC_DECREMENT(&x->f_buffer->b_inuse);
            }
            else
            {
                for(long i = 0; i < x->f_buffer->b_frames; i++)
                {
                    datas[i] = x->f_buffer->b_samples[i * x->f_buffer->b_nchans + (x->f_channel - 1)];
                }
                ATOMIC_DECREMENT(&x->f_buffer->b_inuse);
            }
            x->f_ambiConvolve->setImpulseResponse(datas, x->f_buffer->b_frames);
            free(datas);
        }
}

t_max_err dry_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_ambiConvolve->setDryValue(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_ambiConvolve->setDryValue(atom_getfloat(argv));
    
	x->f_dry = x->f_ambiConvolve->getDryValue();
	return 0;
}


t_max_err wet_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_ambiConvolve->setWetValue(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_ambiConvolve->setWetValue(atom_getfloat(argv));

	x->f_wet = x->f_ambiConvolve->getWetValue();
	return 0;
}
