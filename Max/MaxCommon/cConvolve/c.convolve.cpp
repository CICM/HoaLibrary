/*
 // Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "HoaCommon.max.h"

#include <algorithm>
#include <cstring>
#include <numeric>
#include <vector>

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "FFTConvolver.h"
#include "Utilities.h"

using namespace fftconvolver;

typedef struct _convolve
{
	t_pxobject      f_ob;
    FFTConvolver*   f_convolver;
    char            f_normalize;
    
    t_buffer_ref*	f_buffer_ref;
	t_symbol*		f_buffer_name;
	long			f_channel_offset;
    
    char            f_buffer_need_update;
    char            f_buffer_is_valid;
    
    float           *f_sig_ins;
    float           *f_sig_outs;
} t_convolve;

t_class *convolve_class;

void *convolve_new(t_symbol *s, int argc, t_atom *argv);
void convolve_free(t_convolve *x);
t_max_err convolve_notify(t_convolve *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void convolve_dsp64(t_convolve *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void convolve_set(t_convolve *x, t_symbol *s, long ac, t_atom *av);
void convolve_fill_inner_buffer(t_convolve *x);
void convolve_dblclick(t_convolve *x);

t_max_err convolve_setattr_buffername(t_convolve *x, t_symbol *s, long ac, t_atom* av);
t_max_err convolve_setattr_channel(t_convolve *x, t_symbol *s, long ac, t_atom* av);
t_max_err convolve_setattr_normalize(t_convolve *x, t_symbol *s, long ac, t_atom* av);

int C74_EXPORT main()
{
	t_class *c;
    
	c = class_new("c.convolve~", (method)convolve_new, (method)convolve_free, (short)sizeof(t_convolve), 0L, A_GIMME, 0);
    
    class_dspinit(c);
	
    class_addmethod(c, (method) convolve_dsp64,     "dsp64",            A_CANT,  0);
    class_addmethod(c, (method) convolve_set,       "set",              A_GIMME, 0);
    class_addmethod(c, (method) convolve_notify,	"notify",			A_CANT,  0);
    class_addmethod(c, (method) convolve_dblclick,  "dblclick",         A_CANT,  0);
    
    CLASS_ATTR_SYM                  (c, "buffer", 0, t_convolve, f_buffer_name);
	CLASS_ATTR_CATEGORY             (c, "buffer", 0, "Behavior");
	CLASS_ATTR_ACCESSORS            (c, "buffer", NULL, convolve_setattr_buffername);
	CLASS_ATTR_LABEL                (c, "buffer", 0, "Buffer~ Object Name");
	CLASS_ATTR_SAVE                 (c, "buffer", 1);
    CLASS_ATTR_ORDER                (c, "buffer",  0, "1");
	
    CLASS_ATTR_LONG                 (c, "channel", 0, t_convolve, f_channel_offset);
    CLASS_ATTR_CATEGORY             (c, "channel", 0, "Behavior");
	CLASS_ATTR_ACCESSORS            (c, "channel", NULL, convolve_setattr_channel);
    CLASS_ATTR_LABEL                (c, "channel", 0, "Channel");
    CLASS_ATTR_SAVE                 (c, "channel", 1);
    CLASS_ATTR_ORDER                (c, "channel",  0, "2");
    
    CLASS_ATTR_LONG                 (c, "normalize",  0, t_convolve, f_normalize);
	CLASS_ATTR_CATEGORY             (c, "normalize",  0, "Behavior");
    CLASS_ATTR_STYLE_LABEL          (c, "normalize",  0, "onoff", "Normalize buffer content");
    CLASS_ATTR_ACCESSORS            (c, "normalize", NULL, convolve_setattr_normalize);
	CLASS_ATTR_SAVE                 (c, "normalize",  1);
    CLASS_ATTR_ORDER                (c, "normalize",  0, "3");
    // @description If the <b>normalize</b> attribute is checked, <o>c.convolve</o> object will normalize the <o>buffer~</o> content.
    
    class_register(CLASS_BOX, c);
	convolve_class = c;
}

void *convolve_new(t_symbol *s, int ac, t_atom *av)
{
	t_convolve *x =  NULL;

    x = (t_convolve *)object_alloc(convolve_class);
    if (x)
	{
        x->f_buffer_need_update = 1;
        x->f_buffer_name = hoa_sym_nothing;
        x->f_channel_offset = 1;
        x->f_normalize = 0;
        
        x->f_convolver = new FFTConvolver();
        
        x->f_sig_ins = (float *)malloc(SYS_MAXBLKSIZE * sizeof(float));
        x->f_sig_outs = (float *)malloc(SYS_MAXBLKSIZE * sizeof(float));
        
		dsp_setup((t_pxobject *)x, 1);
        outlet_new(x, "signal");
        
        x->f_ob.z_misc = Z_NO_INPLACE;
        
        attr_args_process(x, ac, av);
	}
    
	return (x);
}

void index_assist(t_convolve *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_OUTLET)
		sprintf(s,"(signal) Output");
	else
    {
		switch (a)
        {
			case 0:	sprintf(s,"(signal) Input, messages");	break;
			default: sprintf(s,"Undocumented");	break;
		}
	}
}

t_max_err convolve_setattr_buffername(t_convolve *x, t_symbol *s, long ac, t_atom* av)
{
	if (ac && av && atom_gettype(av) == A_SYM)
	{
		t_symbol* lastname = x->f_buffer_name;
		x->f_buffer_name = atom_getsym(av);
        
		if (lastname != x->f_buffer_name)
		{
			if (!x->f_buffer_ref)
				x->f_buffer_ref = buffer_ref_new((t_object*)x, x->f_buffer_name);
			else
				buffer_ref_set(x->f_buffer_ref, x->f_buffer_name);
		}
        
        x->f_buffer_need_update = 1;
	}
	
	return MAX_ERR_NONE;
}

t_max_err convolve_setattr_channel(t_convolve *x, t_symbol *s, long ac, t_atom* av)
{
	if (ac && av && atom_gettype(av) == A_LONG)
	{
		x->f_channel_offset = clip_minmax(atom_getlong(av), 1, 4);
        x->f_buffer_need_update = 1;
	}
	
	return MAX_ERR_NONE;
}

t_max_err convolve_setattr_normalize(t_convolve *x, t_symbol *s, long ac, t_atom* av)
{
    if (ac && av && atom_gettype(av) == A_LONG)
	{
		x->f_normalize = atom_getlong(av);
        if(x->f_normalize < 1)
            x->f_normalize = 0;
        else
            x->f_normalize = 1;
        x->f_buffer_need_update = 1;
	}
    
    return MAX_ERR_NONE;
}

t_max_err convolve_notify(t_convolve *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("normalize"))
		{
            ;
		}
	}
	else if (msg == gensym("buffer_modified"))
	{
        ;
	}
	
	return buffer_ref_notify(x->f_buffer_ref, s, msg, sender, data);
}


void convolve_fill_inner_buffer(t_convolve *x)
{
    t_buffer_obj *buffer = NULL;
    float* temp;
    float *buffer_samples;
    long frames, nc, chan, frames_per_channel;
    float buffer_sr;
    float sr = sys_getsr();
    
    buffer = buffer_ref_getobject(x->f_buffer_ref);
    if (!buffer)
        return;
    
    buffer_samples = buffer_locksamples(buffer);
	if (!buffer_samples)
		return;
    
    frames = buffer_getframecount(buffer);
	nc = buffer_getchannelcount(buffer);
    buffer_sr = buffer_getsamplerate(buffer);
    
    
    frames_per_channel = frames / nc;
    
    chan = (long) clip_minmax(x->f_channel_offset-1, 0, nc);
    
    temp = (float *) malloc( frames_per_channel * sizeof(float));
    
    for (int i = 0; i < frames_per_channel; i++)
        temp[i] = buffer_samples[i*nc+(chan)];
    
    if(x->f_normalize)
    {
        float max = 0;
        for(int i = 0; i < frames_per_channel; i++)
        {
            if(fabs(temp[i]) > max)
                max = fabs(temp[i]);
        }
        if(max != 0)
        {
            max = 1.f / max;
            for(int i = 0; i < frames_per_channel; i++)
            {
                temp[i] *= max;
            }
        }
    }
    
    x->f_convolver->init(1024, temp, frames_per_channel);
    free(temp);
    
    buffer_unlocksamples(buffer);
}

void convolve_set(t_convolve *x, t_symbol *s, long ac, t_atom *av)
{
    if (ac && av && atom_gettype(av) == A_SYM)
	{
        object_method(x, gensym("buffer"), 1, av);
        if (ac > 1 && atom_gettype(av+1) == A_LONG)
        {
            object_method(x, gensym("channel"), 1, av+1);
        }
	}
}

void convolve_free(t_convolve *x)
{
	dsp_free(&x->f_ob);
    object_free(x->f_buffer_ref);
    free(x->f_sig_ins);
    free(x->f_sig_outs);
}

void convolve_perform64(t_convolve *x, t_object *d, double **ins, long ni, double **outs, long no, long sampleframes, long f,void *up)
{
    if (x->f_buffer_need_update)
    {
        convolve_fill_inner_buffer(x);
        x->f_buffer_need_update = 0;
    }
        
    for (int i = 0; i < sampleframes; i++)
        x->f_sig_ins[i] = ins[0][i];
    
    x->f_convolver->process(x->f_sig_ins, x->f_sig_outs, sampleframes);
    
    for (int i = 0; i < sampleframes; i++)
        outs[0][i] = x->f_sig_outs[i];
}

void convolve_perform64_zero(t_convolve *x, t_object *d, double **ins, long ni, double **outs, long no, long sampleframes, long f,void *up)
{
    for (int i = 0; i < sampleframes; i++)
        outs[0][i] = 0.f;
}

void convolve_dsp64(t_convolve *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp, gensym("dsp_add64"), x, (method)convolve_perform64, 0, NULL);
}

void convolve_dblclick(t_convolve *x)
{
    if (buffer_ref_exists(x->f_buffer_ref))
        buffer_view(buffer_ref_getobject(x->f_buffer_ref));
}
