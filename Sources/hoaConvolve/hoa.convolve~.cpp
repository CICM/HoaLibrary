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

#include "AmbisonicConvolve.h"
#define MAX_SIZE 256
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
	AmbisonicConvolve*	f_ambiConvolve;

	t_symbol*			f_name[MAX_SIZE];
	t_buffer*			f_buffer[MAX_SIZE];
	long				f_channel[MAX_SIZE];
	long				f_limit[MAX_SIZE];
	long				f_numberOfHarmonics;
	
} t_HoaConvolve;

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv);
void HoaConvolve_free(t_HoaConvolve *x);
void HoaConvolve_assist(t_HoaConvolve *x, void *b, long m, long a, char *s);
void HoaConvolve_int(t_HoaConvolve *x, long n);
void HoaConvolve_float(t_HoaConvolve *x, double f);

void buffer_setup(t_HoaConvolve *x);
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
	
	CLASS_ATTR_SYM_VARSIZE		(c, "buffers", 0, t_HoaConvolve, f_name, f_numberOfHarmonics, MAX_SIZE);
	CLASS_ATTR_CATEGORY			(c, "buffers", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "buffers", 0, "buffer~ Objects Names");
	CLASS_ATTR_ORDER			(c, "buffers", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "buffers", NULL, buffer_set);
	CLASS_ATTR_DEFAULT			(c, "buffers", 0, "");
	CLASS_ATTR_SAVE				(c, "buffers", 1);

	CLASS_ATTR_LONG_VARSIZE		(c, "channels", 0, t_HoaConvolve, f_channel, f_numberOfHarmonics, MAX_SIZE);
	CLASS_ATTR_CATEGORY			(c, "channels", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "channels", 0, "buffer~ Objects Channels");
	CLASS_ATTR_ORDER			(c, "channels", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "channels", NULL, channel_set);
	CLASS_ATTR_DEFAULT			(c, "channels", 0, "0");
	CLASS_ATTR_SAVE				(c, "channels", 1);
	
	CLASS_ATTR_LONG_VARSIZE		(c, "limits", 0, t_HoaConvolve, f_limit, f_numberOfHarmonics, MAX_SIZE);
	CLASS_ATTR_CATEGORY			(c, "limits", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "limits", 0, "buffer~ Objects Size Used");
	CLASS_ATTR_ORDER			(c, "limits", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "limits", NULL, limit_set);
	CLASS_ATTR_DEFAULT			(c, "limits", 0, "0");
	CLASS_ATTR_SAVE				(c, "limits", 1);

	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaConvolve_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaConvolve_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaConvolve *x = NULL;

	long order = 4;
	if (x = (t_HoaConvolve *)object_alloc((t_class*)HoaConvolve_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);

		x->f_ambiConvolve	= new AmbisonicConvolve(order);
		x->f_numberOfHarmonics = x->f_ambiConvolve->getNumberOfHarmonics();

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

void HoaConvolve_float(t_HoaConvolve *x, double f)
{
	x->f_ambiConvolve->setGain(f);
}

void HoaConvolve_int(t_HoaConvolve *x, long n)
{
	x->f_ambiConvolve->setGain(n);
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
	t_atom channel[2];
	if(atom_gettype(argv) == A_SYM)
	{
		if(atom_getsym(argv) == gensym("all"))
		{
			for(int i = 0; i < x->f_ambiConvolve->getNumberOfHarmonics(); i++)
			{
				char bufferName[256];
				name = atom_getsym(argv+1);
				sprintf(bufferName, "%s.%i",  name->s_name, i+1);
				name = gensym(bufferName);
				if(x->f_name[i] != name)
				{

					if ((b = (t_buffer *)(name->s_thing)) && ob_sym(b) == gensym("buffer~")) 
					{
						if(x->f_name && x->f_buffer[i] != NULL)
						{
							globalsymbol_dereference((t_object*)x, x->f_name[i]->s_name, "buffer~");
						}
						x->f_name[i] = name;
						x->f_buffer[i] = (t_buffer*)globalsymbol_reference((t_object*)x, x->f_name[i]->s_name, "buffer~");
						atom_setlong(channel, i);
						atom_setlong(channel, x->f_channel[i]);
						channel_set(x, attr, 2, channel);
					}
					else
					{
						x->f_buffer[i] = NULL;
						x->f_name[i] = gensym("none");
					}
				}
			}
		}
		else if(argc > 0)
		{
			if(argc > x->f_numberOfHarmonics)
			argc = x->f_numberOfHarmonics;

			for(int i = 0; i < argc; i++)
			{
				name = atom_getsym(argv+i);
				if(x->f_name[i] != name)
				{

					if ((b = (t_buffer *)(name->s_thing)) && ob_sym(b) == gensym("buffer~")) 
					{
						if(x->f_name && x->f_buffer[i] != NULL)
						{
							globalsymbol_dereference((t_object*)x, x->f_name[i]->s_name, "buffer~");
						}
						x->f_name[i] = name;
						x->f_buffer[i] = (t_buffer*)globalsymbol_reference((t_object*)x, x->f_name[i]->s_name, "buffer~");
						atom_setlong(channel, i);
						atom_setlong(channel, x->f_channel[i]);
						channel_set(x, attr, 2, channel);
					}
					else
					{
						x->f_buffer[i] = NULL;
						x->f_name[i] = gensym("none");
					}
				}
			}
		}
	}
	return 0;
}

t_max_err channel_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	
	if(argc == 2 && atom_gettype(argv) == A_SYM && atom_gettype(argv+1) == A_LONG)
	{
		for(int i = 0; i < x->f_numberOfHarmonics; i++)
		{
			if(x->f_buffer[i] == NULL)
			{
				if(atom_getlong(argv+1) >= 1)
					x->f_channel[i] = atom_getlong(argv+1);
			}
			else
			{
				if(atom_getlong(argv+1) > 1 && x->f_channel[i] <= x->f_buffer[i]->b_nchans)
					x->f_channel[i] = atom_getlong(argv+1);
				else if(atom_getlong(argv+1) <= 1)
					x->f_channel[i] = 1;
				else
					x->f_channel[i] = x->f_buffer[i]->b_nchans;
			}
		}
		buffer_setup(x);
	}
	else if(argc > 0)
	{
		if(argc > x->f_numberOfHarmonics)
			argc = x->f_numberOfHarmonics;
		for(int i = 0; i < argc; i++)
		{
			if(x->f_buffer[i] == NULL)
			{
				if(atom_getlong(argv) >= 1)
					x->f_channel[i] = atom_getlong(argv+i);
			}
			else
			{
				if(atom_getlong(argv+i) > 1 && x->f_channel[i] <= x->f_buffer[i]->b_nchans)
					x->f_channel[i] = atom_getlong(argv+i);
				else if(atom_getlong(argv+i) <= 1)
					x->f_channel[i] = 1;
				else
					x->f_channel[i] = x->f_buffer[i]->b_nchans;
				buffer_setup(x);
			}
		}
	}
	return 0;
}

t_max_err limit_set(t_HoaConvolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(argc == 2 && atom_gettype(argv) == A_SYM && atom_gettype(argv+1) == A_LONG)
	{
		for(int i = 0; i < x->f_numberOfHarmonics; i++)
		{
			if(atom_getlong(argv+1) > 0)
				x->f_limit[i] = atom_getlong(argv+1);
			else
				x->f_limit[i] = 0;
		}
		buffer_setup(x);
	}
	else if(argc > 0)
	{
		if(argc > x->f_numberOfHarmonics)
			argc = x->f_numberOfHarmonics;
		for(int i = 0; i < argc; i++)
		{
			if(atom_gettype(argv+i) == A_LONG && atom_getlong(argv+i) > 0)
				x->f_limit[i] = atom_getlong(argv+i);
			else
				x->f_limit[i] = 0;
		}
		buffer_setup(x);
	}
	return 0;
}

void buffer_setup(t_HoaConvolve *x)
{
	for(int j = 0; j < x->f_numberOfHarmonics; j++)
	{
		if(x->f_buffer[j] != NULL)
		{
			ATOMIC_INCREMENT(&x->f_buffer[j]->b_inuse);
			if (!x->f_buffer[j]->b_valid) 
			{
				ATOMIC_DECREMENT(&x->f_buffer[j]->b_inuse);
			}
			else
			{
				long size;
				if(x->f_limit[j] == 0)
					size = x->f_buffer[j]->b_frames;
				else if(x->f_limit[j] > x->f_buffer[j]->b_frames)
					size = x->f_buffer[j]->b_frames;
				else			
					size = x->f_limit[j];
				double* datas = new double[x->f_buffer[j]->b_frames];
				for(long i = 0; i < x->f_buffer[j]->b_frames; i++)
				{
					datas[i] = x->f_buffer[j]->b_samples[i * x->f_buffer[j]->b_nchans + (x->f_channel[j] - 1)] * 0.05;
				}
				ATOMIC_DECREMENT(&x->f_buffer[j]->b_inuse);

				x->f_ambiConvolve->setImpulseResponse(j, datas, size);
				free(datas);
			}
		}
	}
}