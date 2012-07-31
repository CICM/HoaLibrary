
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

#include "hoa.plug~.h"

int main(void)
{
	t_class *c;

	c = class_new("hoa.plug~", (method)plug_new, (method)plug_free, (short)sizeof(t_plug), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)plug_dsp64,			"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)plug_dsp,			"dsp",			A_CANT,	0);
	class_addmethod(c, (method)plug_assist,			"assist",		A_CANT,	0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	plug_class = c;

	post("hoa.plug~ by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");

}

void *plug_new(t_symbol *s, int argc, t_atom *argv)
{
	t_plug *x = NULL;
	
	if (x = (t_plug *)object_alloc((t_class *)plug_class)) 
	{
		if(atom_gettype(argv) == A_LONG)
			x->f_order = atom_getlong(argv);
		if(x->f_order < 1)
			x->f_order = 1;
		
		x->f_harmonics = 2 * x->f_order + 1;
		
		outlet_new((t_pxobject *)x, "signal");
		dsp_setup((t_pxobject *)x, 1);
		attr_args_process(x, argc, argv);
	}
	
	return x;
}			

void plug_dsp(t_plug *x, t_signal **sp, short *count)
{
	dsp_add(plug_perform, 3, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

t_plugt *plug_perform(t_plugt *w)
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

void plug_dsp64(t_plug *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, plug_perform64, 0, NULL);
}

void plug_perform64(t_plug *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i;
	for(i = 0; i < sampleframes; i++)
	{ 
		outs[0][i] = ins[0][i];	
	}
}

void plug_free(t_plug *x)
{
	dsp_free((t_pxobject *)x);
}

void plug_assist(t_plug *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"Dummy");
	}
	else 
	{
		sprintf(s,"(Signal) Output signal");
	}
}

void delayObj_dblclick(t_delayObj *x)
{
	if (x->f_patcher) 
		object_method(x->f_patcher, gensym("vis"));
	else 
	{
		t_dictionary *d = dictionary_new();
		char	parsebuf[256];
		t_atom	a;
		long	ac = 0;
		t_atom	*av = NULL;
		long	size;
		t_atom msg[4], rv;
		size = x->f_harmonics * 70;
		
		sprintf(parsebuf,"@defrect 0 0 %ld 200 @title hoa.delay~ @enablehscroll 0 @enablevscroll 0 @presentation 1 @toolbarid \"\"", size);
		atom_setparse(&ac,&av,parsebuf);
		attr_args_dictionary(d,ac,av);
		atom_setobj(&a,d);
		sysmem_freeptr(av); 
		x->f_patcher = (t_object *)object_new_typed(CLASS_NOBOX,gensym("jpatcher"),1, &a);
		freeobject((t_object *)d);
		
		object_method(x->f_patcher,gensym("vis"));
		/*
		 x->f_ui = newobject_sprintf(x->f_patcher, "@maxclass delay_ui @patching_rect 0 0 %ld 200 @oncolor %.2f %.2f %.2f %.2f @offcolor %.2f %.2f %.2f %.2f",
		 size, x->f_oncolor.red, x->f_oncolor.green, x->f_oncolor.blue, x->f_oncolor.alpha, x->f_offcolor.red, x->f_offcolor.green, x->f_offcolor.blue, x->f_offcolor.alpha);
		 
		 */
		x->f_ui = newobject_sprintf(x->f_patcher, "@maxclass flonum @patching_rect 10 10 50 20 @presentation 1");
		
		/*
		 atom_setobj(msg, x->f_ui); 
		 atom_setlong(msg + 1, 0); 
		 atom_setobj(msg + 2, x); 
		 atom_setlong(msg + 3, 0);
		 object_method_typed(x->f_patcher, gensym("connect"), 4, msg, &rv);
		 */
		object_attach_byptr_register(x, x->f_ui, CLASS_BOX);
		object_attach_byptr_register(x, x->f_patcher, CLASS_NOBOX);
	}
}
