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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "MaxConvolve.h"

typedef struct _hoa_convolve 
{
	t_pxobject			f_ob;			
	AmbisonicConvolver*	f_ambi_convolver;
    MaxConvolve*        f_ambi_max;
    
	t_symbol*			f_name;
	t_buffer*			f_buffer;
	long				f_channel;
	float               f_wet;
    float               f_dry;

} t_hoa_convolve;

void *hoa_convolve_new(t_symbol *s, long argc, t_atom *argv);
void hoa_convolve_free(t_hoa_convolve *x);

void hoa_convolve_clear(t_hoa_convolve *x);
void buffer_setup(t_hoa_convolve *x);
void hoa_convolve_dblclick(t_hoa_convolve *x);

t_max_err buffer_set(t_hoa_convolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_set(t_hoa_convolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err dry_set(t_hoa_convolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err wet_set(t_hoa_convolve *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoa_convolve_notify(t_hoa_convolve *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void hoa_convolve_dsp64(t_hoa_convolve *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_convolve_perform64(t_hoa_convolve *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *hoa_convolve_class;

int C74_EXPORT main(void)
{	

	t_class *c = class_new("hoa.convolve~", (method)hoa_convolve_new, (method)hoa_convolve_free, (long)sizeof(t_hoa_convolve), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_convolve_dsp64,		"dsp64",	A_CANT,     0);
    class_addmethod(c, (method)hoa_convolve_notify,		"notify",	A_CANT,     0);
	class_addmethod(c, (method)hoa_convolve_dblclick,   "dblclick", A_CANT,     0);
    class_addmethod(c, (method)hoa_convolve_clear,      "clear",                0);
    
	CLASS_ATTR_SYM              (c, "buffer",   0, t_hoa_convolve, f_name);
	CLASS_ATTR_CATEGORY			(c, "buffer",   0, "Behavior");
	CLASS_ATTR_LABEL			(c, "buffer",   0, "buffer~ Object Name");
	CLASS_ATTR_ORDER			(c, "buffer",   0, "1");
	CLASS_ATTR_ACCESSORS		(c, "buffer",   NULL, buffer_set);
	CLASS_ATTR_DEFAULT			(c, "buffer",   0, "");
	CLASS_ATTR_SAVE				(c, "buffer",   1);

	CLASS_ATTR_LONG             (c, "channel",  0, t_hoa_convolve, f_channel);
	CLASS_ATTR_CATEGORY			(c, "channel",  0, "Behavior");
	CLASS_ATTR_LABEL			(c, "channel",  0, "buffer~ Object Channel");
	CLASS_ATTR_ORDER			(c, "channel",  0, "2");
	CLASS_ATTR_ACCESSORS		(c, "channel",  NULL, channel_set);
	CLASS_ATTR_DEFAULT			(c, "channel",  0, "1");
	CLASS_ATTR_SAVE				(c, "channel",  1);
    
    CLASS_ATTR_FLOAT			(c, "dry",      0, t_hoa_convolve, f_dry);
	CLASS_ATTR_CATEGORY			(c, "dry",      0, "Parameters");
	CLASS_ATTR_LABEL			(c, "dry",      0, "Dry value");
	CLASS_ATTR_ORDER			(c, "dry",      0, "1");
	CLASS_ATTR_ACCESSORS		(c, "dry",      NULL, dry_set);
	CLASS_ATTR_DEFAULT			(c, "dry",      0, "0.");
	CLASS_ATTR_SAVE				(c, "dry",      1);
    
    CLASS_ATTR_FLOAT			(c, "wet",      0, t_hoa_convolve, f_wet);
	CLASS_ATTR_CATEGORY			(c, "wet",      0, "Parameters");
	CLASS_ATTR_LABEL			(c, "wet",      0, "Wet value");
	CLASS_ATTR_ORDER			(c, "wet",      0, "2");
	CLASS_ATTR_ACCESSORS		(c, "wet",      NULL, wet_set);
	CLASS_ATTR_DEFAULT			(c, "wet",      0, "1.");
	CLASS_ATTR_SAVE				(c, "wet",      1);
    
    class_hoainit(c);
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	hoa_convolve_class = c;
	
	return 0;
}

void *hoa_convolve_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_convolve *x = (t_hoa_convolve *)object_alloc(hoa_convolve_class);
	if (x)
	{
        x->f_buffer = NULL;
        x->f_ambi_max       = new MaxConvolve((t_hoa_object *)x, argc, argv);
		x->f_ambi_convolver	= new AmbisonicConvolver(x->f_ambi_max->getOrder(), sys_getsr(), sys_getblksize());
       
		dsp_setup((t_pxobject *)x, x->f_ambi_convolver->getNumberOfInputs());
		for (int i = 0; i < x->f_ambi_convolver->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
		x->f_ob.z_misc = Z_NO_INPLACE;
		buffer_setup(x);
	}
	return (x);
}

void hoa_convolve_clear(t_hoa_convolve *x)
{
    x->f_ambi_convolver->clear();
}

void hoa_convolve_dsp64(t_hoa_convolve *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_convolver->setVectorSize(maxvectorsize);
    x->f_ambi_convolver->setSamplingRate(samplerate);
	object_method(dsp64, gensym("dsp_add64"), x, hoa_convolve_perform64, 0, NULL);
}

void hoa_convolve_perform64(t_hoa_convolve *x,t_object *d,double **ins, long ni, double **outs, long no, long sf, long f, void *up)
{
	x->f_ambi_convolver->process(ins, outs);
}

void hoa_convolve_free(t_hoa_convolve *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambi_convolver;
    delete x->f_ambi_max;
}

t_max_err hoa_convolve_notify(t_hoa_convolve *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
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

void hoa_convolve_dblclick(t_hoa_convolve *x)
{
	t_buffer *b;
	
	if ((b = (t_buffer *)(x->f_name->s_thing)) && ob_sym(b) == gensym("buffer~"))
		mess0((t_object *)b,gensym("dblclick"));
}

t_max_err buffer_set(t_hoa_convolve *x, t_object *attr, long argc, t_atom *argv)
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

    
t_max_err channel_set(t_hoa_convolve *x, t_object *attr, long argc, t_atom *argv)
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

void buffer_setup(t_hoa_convolve *x)
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
        x->f_ambi_convolver->setImpulseResponse(datas, x->f_buffer->b_frames);
        free(datas);
    }
}

t_max_err dry_set(t_hoa_convolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_ambi_convolver->setDryValue(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_ambi_convolver->setDryValue(atom_getfloat(argv));
    
	x->f_dry = x->f_ambi_convolver->getDryValue();
	return 0;
}


t_max_err wet_set(t_hoa_convolve *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
		x->f_ambi_convolver->setWetValue(atom_getlong(argv));
	else if(atom_gettype(argv) == A_FLOAT)
		x->f_ambi_convolver->setWetValue(atom_getfloat(argv));

	x->f_wet = x->f_ambi_convolver->getWetValue();
	return 0;
}
