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

#include "../../Sources/HoaLibrary.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "buffer.h"
#include "ext_globalsymbol.h"
}

typedef struct _HoaGrain
{
	t_pxobject			f_ob;			
	AmbisonicsGrain*	f_AmbiGrain;
    
    double      f_grain_size;
    double      f_delay_time;
    double      f_feedback;
    double      f_rarefaction;
    
    t_symbol*   f_name;
	t_buffer*	f_buffer;
    long		f_channel;    
} t_HoaGrain;

void *HoaGrain_new(t_symbol *s, long argc, t_atom *argv);
void HoaGrain_free(t_HoaGrain *x);
void HoaGrain_assist(t_HoaGrain *x, void *b, long m, long a, char *s);
void HoaGrain_float(t_HoaGrain *x, double f);
void HoaGrain_int(t_HoaGrain *x, long n);

t_max_err size_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv);
t_max_err delay_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv);
t_max_err feedback_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv);
t_max_err rarefaction_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv);

void buffer_setup(t_HoaGrain *x);
void HoaGrain_dblclick(t_HoaGrain *x);
t_max_err buffer_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv);
t_max_err HoaGrain_notify(t_HoaGrain *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void HoaGrain_dsp64(t_HoaGrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaGrain_perform64_no(t_HoaGrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void HoaGrain_perform64_post(t_HoaGrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class* HoaGrain_class;

int main(void)
{	
	t_class *c;
	
	c = class_new("hoa.grain~", (method)HoaGrain_new, (method)dsp_free, (long)sizeof(t_HoaGrain), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaGrain_float,		"float",	A_FLOAT,    0);
	class_addmethod(c, (method)HoaGrain_int,		"int",		A_LONG,     0);
	class_addmethod(c, (method)HoaGrain_dsp64,		"dsp64",	A_CANT,     0);
	class_addmethod(c, (method)HoaGrain_assist,		"assist",	A_CANT,     0);
    class_addmethod(c, (method)HoaGrain_notify,     "notify",	A_CANT,     0);
	class_addmethod(c, (method)HoaGrain_dblclick,   "dblclick", A_CANT,     0);
    
    
    CLASS_ATTR_DOUBLE			(c, "size", 0, t_HoaGrain, f_grain_size);
	CLASS_ATTR_CATEGORY			(c, "size", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "size", 0, "Grain size (ms)");
	CLASS_ATTR_ORDER			(c, "size", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "size", NULL, size_set);
	CLASS_ATTR_SAVE				(c, "size", 1);
    
	CLASS_ATTR_DOUBLE			(c, "delay", 0, t_HoaGrain, f_delay_time);
	CLASS_ATTR_CATEGORY			(c, "delay", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "delay", 0, "Delay time (ms)");
	CLASS_ATTR_ORDER			(c, "delay", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "delay", NULL, delay_set);
	CLASS_ATTR_SAVE				(c, "delay", 1);
    
    CLASS_ATTR_DOUBLE			(c, "feedback", 0, t_HoaGrain, f_feedback);
	CLASS_ATTR_CATEGORY			(c, "feedback", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "feedback", 0, "Feedback");
	CLASS_ATTR_ORDER			(c, "feedback", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "feedback", NULL, feedback_set);
	CLASS_ATTR_SAVE				(c, "feedback", 1);
    
    CLASS_ATTR_DOUBLE			(c, "rarefaction", 0, t_HoaGrain, f_rarefaction);
	CLASS_ATTR_CATEGORY			(c, "rarefaction", 0, "Parameters");
	CLASS_ATTR_LABEL			(c, "rarefaction", 0, "Rarefaction");
	CLASS_ATTR_ORDER			(c, "rarefaction", 0, "4");
	CLASS_ATTR_ACCESSORS		(c, "rarefaction", NULL, rarefaction_set);
	CLASS_ATTR_SAVE				(c, "rarefaction", 1);
    
    CLASS_ATTR_SYM              (c, "buffer",   0, t_HoaGrain, f_name);
	CLASS_ATTR_CATEGORY			(c, "buffer",   0, "Behavior");
	CLASS_ATTR_LABEL			(c, "buffer",   0, "buffer~ Object Name");
	CLASS_ATTR_ORDER			(c, "buffer",   0, "1");
	CLASS_ATTR_ACCESSORS		(c, "buffer",   NULL, buffer_set);
	CLASS_ATTR_DEFAULT			(c, "buffer",   0, "");
	CLASS_ATTR_SAVE				(c, "buffer",   1);
    
	CLASS_ATTR_LONG             (c, "channel",  0, t_HoaGrain, f_channel);
	CLASS_ATTR_CATEGORY			(c, "channel",  0, "Behavior");
	CLASS_ATTR_LABEL			(c, "channel",  0, "buffer~ Object Channel");
	CLASS_ATTR_ORDER			(c, "channel",  0, "2");
	CLASS_ATTR_ACCESSORS		(c, "channel",  NULL, channel_set);
	CLASS_ATTR_DEFAULT			(c, "channel",  0, "1");
	CLASS_ATTR_SAVE				(c, "channel",  1);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaGrain_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaGrain_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaGrain *x = NULL;
    t_dictionary *d = NULL;
    
	int order = 4;
    bool mode = 1;
    double maxdelay = 5000.;
	x = (t_HoaGrain *)object_alloc(HoaGrain_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
        if(atom_gettype(argv+1) == A_SYM && atom_getsym(argv+1) == gensym("no"))
            mode = 0;
        if(atom_gettype(argv+2) == A_LONG || atom_gettype(argv+2) == A_FLOAT)
            maxdelay = atom_getfloat(argv+2);
			
		x->f_AmbiGrain	= new AmbisonicsGrain(order, mode, maxdelay, sys_getblksize(), sys_getsr());
		
		dsp_setup((t_pxobject *)x, x->f_AmbiGrain->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbiGrain->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
        
		x->f_grain_size = x->f_AmbiGrain->getGrainSize();
        x->f_delay_time = x->f_AmbiGrain->getDelayTime();
        x->f_feedback = x->f_AmbiGrain->getFeedback();
        x->f_rarefaction = x->f_AmbiGrain->getRarefaction();
        
        x->f_ob.z_misc = Z_NO_INPLACE;
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        attr_args_process(x, argc, argv);
	}
	return (x);
}

void HoaGrain_float(t_HoaGrain *x, double f)
{
	;
}

void HoaGrain_int(t_HoaGrain *x, long n)
{
	;
}

void HoaGrain_dsp64(t_HoaGrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbiGrain->setVectorSize(maxvectorsize);
    x->f_AmbiGrain->setSamplingRate(samplerate);
    if(x->f_AmbiGrain->getMode() == Hoa_No_Encoding)
        object_method(dsp64, gensym("dsp_add64"), x, HoaGrain_perform64_no, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, HoaGrain_perform64_post, 0, NULL);
        
}

void HoaGrain_perform64_no(t_HoaGrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbiGrain->process(ins[0], outs);
}

void HoaGrain_perform64_post(t_HoaGrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbiGrain->process(ins, outs);
}

void HoaGrain_assist(t_HoaGrain *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET && a == 0)
		sprintf(s,"(Signal, float or int) %s", x->f_AmbiGrain->getHarmonicsName(a).c_str());
	else
		sprintf(s,"(Signal) %s", x->f_AmbiGrain->getHarmonicsName(a).c_str());
}

void HoaGrain_free(t_HoaGrain *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_AmbiGrain;
}

t_max_err size_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiGrain->setGrainSize(atom_getfloat(argv));
    
	x->f_grain_size = x->f_AmbiGrain->getGrainSize();
	return MAX_ERR_NONE;
}

t_max_err delay_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiGrain->setDelayTime(atom_getfloat(argv));
    
	x->f_delay_time = x->f_AmbiGrain->getDelayTime();
	return MAX_ERR_NONE;
}

t_max_err feedback_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiGrain->setFeedback(atom_getfloat(argv));
    
	x->f_feedback = x->f_AmbiGrain->getFeedback();
	return MAX_ERR_NONE;
}

t_max_err rarefaction_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
		x->f_AmbiGrain->setRarefaction(atom_getfloat(argv));
    
	x->f_rarefaction = x->f_AmbiGrain->getRarefaction();
	return MAX_ERR_NONE;
}

t_max_err HoaGrain_notify(t_HoaGrain *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if(msg == gensym("globalsymbol_binding"))
	{
		x->f_buffer = (t_buffer *)x->f_name->s_thing;
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

void HoaGrain_dblclick(t_HoaGrain *x)
{
	t_buffer *b;
	
	if ((b = (t_buffer *)(x->f_name->s_thing)) && ob_sym(b) == gensym("buffer~"))
		mess0((t_object *)b,gensym("dblclick"));
}

t_max_err buffer_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv)
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


t_max_err channel_set(t_HoaGrain *x, t_object *attr, long argc, t_atom *argv)
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

void buffer_setup(t_HoaGrain *x)
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
        x->f_AmbiGrain->writeWidowFunction(datas, x->f_buffer->b_frames);
        free(datas);
    }
}







