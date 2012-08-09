/*
 * Copyright (C) 2012 Pierre Guillot & Julien Colafransceco, Universite Paris 8
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

#include "hoa.plug_script.h"

void plug_script_init()
{
	t_class *c;
	
	c = class_new("hoa.plug_script", (method)plug_script_new, (method)plug_script_free, (short)sizeof(t_plug_script), 0L, A_GIMME, 0);
	
	
	class_addmethod(c, (method)plug_script_anything,			"anything",		A_GIMME, 0);
	class_addmethod(c, (method)plug_script_list,				"list",			A_GIMME, 0);
	class_addmethod(c, (method)plug_script_int,					"int",			A_LONG, 0);
	class_addmethod(c, (method)plug_script_float,				"float",		A_FLOAT, 0);
	class_addmethod(c, (method)plug_script_bang,				"bang",			A_CANT,	0);
	class_addmethod(c, (method)plug_script_dsp64,				"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)plug_script_dsp,					"dsp",			A_CANT,	0);
	
	//class_addmethod(c, (method)plug_script_open,				"open",			A_GIMME, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	plug_script_class = c;
	
	post("hoa.plug_script by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");
	
}

void *plug_script_new(t_symbol *s, int argc, t_atom *argv)
{
	t_plug_script *x = NULL;
	
	if (x = (t_plug_script *)object_alloc((t_class *)plug_script_class)) 
	{
		x->f_outlet = outlet_new((t_object *)x, NULL);
		x->f_outlet = intout((t_object *)x);
		x->f_outlet = outlet_new((t_object *)x, NULL);
		outlet_new((t_pxobject *)x, "signal");
		dsp_setup((t_pxobject *)x, 1);
		attr_args_process(x, argc, argv);
	}
	
	return x;
}	


void plug_script_bang(t_plug_script *x)
{
	outlet_bang(x->f_outlet);
}

void plug_script_int(t_plug_script *x, long n)
{
	outlet_int(x->f_outlet, n);
}

void plug_script_float(t_plug_script *x, double f)
{
	outlet_float(x->f_outlet, f);
}

void plug_script_list(t_plug_script *x, t_symbol *s, long argc, t_atom *argv)
{
	outlet_list(x->f_outlet, s, argc, argv);
}

void plug_script_anything(t_plug_script *x, t_symbol *s, long argc, t_atom *argv)
{
	outlet_anything(x->f_outlet, s, argc, argv);
}

void plug_script_dsp(t_plug_script *x, t_signal **sp, short *count)
{
	dsp_add(plug_script_perform, 3, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

t_int *plug_script_perform(t_int *w)
{
	t_sample *in = (t_sample *)(w[1]);
	t_sample *out = (t_sample *)(w[2]);
    int sampleframes = (int)(w[3]);
	int i;
	
	for(i = 0; i < sampleframes; i++)
	{ 
		out[i] = in[i];
	}
	
	return w + 4;
}

void plug_script_dsp64(t_plug_script *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, plug_script_perform64, 0, NULL);
}

void plug_script_perform64(t_plug_script *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i;
	for(i = 0; i < sampleframes; i++)
	{ 
		outs[0][i] = ins[0][i];	
	}
}

void plug_script_free(t_plug_script *x)
{
	dsp_free((t_pxobject *)x);
}
