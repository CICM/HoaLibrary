/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#include "ambisonicConvolve.hpp"

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
	ambisonicConvolve*	f_ambiConvolve;

	t_symbol*			f_name;
	t_buffer**			f_buffer;
	long				f_channel;
	long				f_limit;
} t_HoaConvolve;

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv);
void HoaConvolve_free(t_HoaConvolve *x);
void HoaConvolve_assist(t_HoaConvolve *x, void *b, long m, long a, char *s);
void HoaConvolve_int(t_HoaConvolve *x, long n);
void HoaConvolve_float(t_HoaConvolve *x, double f);

t_max_err buffer_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err limit_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv);

void HoaConvolve_dsp(t_HoaConvolve *x, t_signal **sp, short *count);
t_int *HoaConvolve_perform(t_int *w);
t_int *HoaConvolve_performOffset(t_int *w);

void HoaConvolve_dsp64(t_HoaConvolve *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaConvolve_perform64(t_HoaConvolve *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaConvolve_class;

int main(void)
{	

	t_class *c;
	
	c = class_new("hoa.convolve~", (method)HoaConvolve_new, (method)HoaConvolve_free, (long)sizeof(t_HoaConvolve), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaConvolve_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaConvolve_int,			"int",		A_LONG, 0);
	class_addmethod(c, (method)HoaConvolve_dsp,			"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaConvolve_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaConvolve_assist,		"assist",	A_CANT, 0);
	
	
	CLASS_ATTR_SYM				(c, "buffer", 0, t_HoaConvolve, f_name);
	CLASS_ATTR_CATEGORY			(c, "buffer", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "buffer", 0, "buffer~ Object Name");
	CLASS_ATTR_ORDER			(c, "buffer", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "buffer", NULL, buffer_set);
	CLASS_ATTR_DEFAULT			(c, "buffer", 0, "");
	CLASS_ATTR_SAVE				(c, "buffer", 1);

	CLASS_ATTR_LONG				(c, "channel", 0, t_HoaConvolve, f_channel);
	CLASS_ATTR_CATEGORY			(c, "channel", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "channel", 0, "Channels");
	CLASS_ATTR_ORDER			(c, "channel", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "channel", NULL, channel_set);
	CLASS_ATTR_DEFAULT			(c, "channel", 0, "0");
	CLASS_ATTR_SAVE				(c, "channel", 1);
	
	CLASS_ATTR_LONG				(c, "limit", 0, t_HoaConvolve, f_limit);
	CLASS_ATTR_CATEGORY			(c, "limit", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "limit", 0, "Limit Size");
	CLASS_ATTR_ORDER			(c, "limit", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "limit", NULL, limit_set);
	CLASS_ATTR_DEFAULT			(c, "limit", 0, "0");
	CLASS_ATTR_SAVE				(c, "limit", 1);

	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaConvolve_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaConvolve *x = NULL;

	int order = 4, inputs = 9;
	if (x = (t_HoaConvolve *)object_alloc((t_class*)HoaConvolve_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			inputs	= atom_getlong(argv+1);

		x->f_ambiConvolve	= new ambisonicConvolve(order, inputs);
		
		x->f_buffer = new t_buffer*[x->f_ambiConvolve->getNumberOfHarmonics()];
		for (int i = 0; i <x->f_ambiConvolve->getNumberOfHarmonics(); i++)
			x->f_buffer[i] = NULL;

		dsp_setup((t_pxobject *)x, x->f_ambiConvolve->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiConvolve->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		attr_args_process(x, argc, argv);
	}
	return (x);
}

void HoaConvolve_dsp64(t_HoaConvolve *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambiConvolve->setVectorSize(maxvectorsize);
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


t_max_err buffer_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	t_buffer *b;
	t_symbol *name;
	t_atom channel[1];
	if (atom_gettype(argv) == A_SYM)
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
				atom_setlong(channel, x->f_channel);
				channel_set(x, attr, 1, channel);
			}
			else
			{
				x->f_buffer = NULL;
				x->f_name = gensym("");
			}
		}
	}
	return 0;
}

t_max_err channel_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
	{
		if(x->f_buffer == NULL)
		{
			if(atom_getlong(argv) > 1)
				x->f_channel = atom_getlong(argv);
		}
		else
		{
			if(atom_getlong(argv) > 1 && x->f_channel <= x->f_buffer->b_nchans)
				x->f_channel = atom_getlong(argv);
			else if(atom_getlong(argv) <= 1)
				x->f_channel = 1;
			else
				x->f_channel = x->f_buffer->b_nchans;
			buffer_setup(x);
		}
	}
	return 0;
}

t_max_err limit_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) > 0)
			x->f_limit = atom_getlong(argv);
		else
			x->f_limit = 0;
		buffer_setup(x);
	}
	else if(atom_gettype(argv) == A_FLOAT)
	{
		if(atom_getfloat(argv) > 0.f)
			x->f_limit = atom_getfloat(argv);
		else
			x->f_limit = 0;
		buffer_setup(x);
	}
	return 0;
}


void buffer_setup(t_HoaConvolve *x)
{
	int i;
	double* datas;
	long size;
	if(x->f_buffer != NULL)
	{
		ATOMIC_INCREMENT(&x->f_buffer->b_inuse);
		if (!x->f_buffer->b_valid) 
		{
			ATOMIC_DECREMENT(&x->f_buffer->b_inuse);
		}
		else
		{
			if(x->f_limit == 0)
				size = x->f_buffer->b_frames;
			else if(x->f_limit > x->f_buffer->b_frames)
				size = x->f_buffer->b_frames;
			else			
				size = x->f_limit;
			datas = new double[x->f_buffer->b_frames];
			for(i = 0; i < x->f_buffer->b_frames; i++)
			{
				datas[i] = x->f_buffer->b_samples[i * x->f_buffer->b_nchans + (x->f_channel - 1)] * 0.05;
			}
			ATOMIC_DECREMENT(&x->f_buffer->b_inuse);

			x->f_Zlc->setImpulseResponse(datas, size);
			free(datas);
		}
	}
}