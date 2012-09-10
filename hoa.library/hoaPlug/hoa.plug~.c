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
	t_class *plug;
	t_class *patcher;

	plug = class_new("hoa.plug~", (method)plug_new, (method)NULL, (short)sizeof(t_plug), 0L, A_GIMME, 0);
	
	class_register(CLASS_BOX, plug);
	plug_class = plug;
	
	plug_script_init();
	
	patcher = class_findbyname(CLASS_NOBOX, gensym("jpatcher"));
	dblclickpatcher = class_method(patcher, gensym("dblclick"));
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
}

void *plug_new(t_symbol *s, int argc, t_atom *argv)
{
	int order, mode, harmonics;
	t_symbol *patchname;

	t_object *x;
	
	x = (t_object *)object_new(CLASS_NOBOX, gensym("jpatcher"), 0, NULL);
	jpatcher_set_title(x, gensym("hoa.plug~"));
	method_object_setmethod(object_getmethod_object(x, gensym("dblclick")), (method)plug_dblclick);
	
	order = 1;
	if(atom_gettype(argv) == A_LONG)
		order = atom_getlong(argv);
	if(order < 1)
		order = 1;
	harmonics = 2 * order +1;
	patchname = gensym("hoa.nothing~");
	if(atom_gettype(argv+1) == A_SYM)
		patchname = atom_getsym(argv+1);
	
	mode = 0;
	if(atom_gettype(argv+2) == A_SYM)
	{
		if(atom_getsym(argv+2) == gensym("no"))
			mode = 0;
		else if(atom_getsym(argv+2) == gensym("post"))
			mode = 1;
		else if(atom_getsym(argv+2) == gensym("pre"))
			mode = 2;
		else 
			mode = 0;
	}
	plug_router(x, order, patchname, mode);
	return x;
	
}	

void plug_dblclick(t_object *x)
{	
	t_object *box, *obj;
	if(jpatcher_get_title(x) == gensym("hoa.plug~"))
	{
		for (box = jpatcher_get_firstobject(x); box; box = jbox_get_nextobject(box)) 
		{		
			obj = jbox_get_object(box);
		
			if(object_classname(obj) == gensym("jpatcher"))
			{
				object_method(obj, gensym("vis"));
				return;
			}
		}
	}
	else 
	{
		method_object_setmethod(object_getmethod_object(x, gensym("dblclick")), (method)dblclickpatcher);
		object_method(x, gensym("vis"));
		method_object_setmethod(object_getmethod_object(x, gensym("dblclick")), (method)plug_dblclick);
	}
}

//////////////////////////////////////


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
	
	class_addmethod(c, (method)plug_script_open,				"open",			A_GIMME, 0);
	class_addmethod(c, (method)plug_script_mute,				"mute",			A_GIMME, 0);
	class_addmethod(c, (method)plug_script_target,				"target",		A_GIMME, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	plug_script_class = c;
	
}

void *plug_script_new(t_symbol *s, int argc, t_atom *argv)
{
	t_plug_script *x = NULL;
	
	if (x = (t_plug_script *)object_alloc((t_class *)plug_script_class)) 
	{
		x->f_outcontr = outlet_new((t_object *)x, NULL);
		x->f_outany = outlet_new((t_object *)x, NULL);
		x->f_outsignal = outlet_new((t_pxobject *)x, "signal");
		
		x->f_gate = 1;
		dsp_setup((t_pxobject *)x, 1);
		x->f_order = 1;
		x->f_index = 0;
		x->f_mode = 0;
		x->f_connected = 0;
		if(atom_gettype(argv) == A_LONG)
			x->f_index = atom_getlong(argv);
		if(atom_gettype(argv+1) == A_LONG)
			x->f_order = atom_getlong(argv+1);
		if(atom_gettype(argv+2) == A_LONG)
			x->f_mode = atom_getlong(argv+2);
		if(atom_gettype(argv+3) == A_LONG)
			x->f_inlet = atom_getlong(argv+1);
		if(atom_gettype(argv+4) == A_LONG)
			x->f_outlet = atom_getlong(argv+2);
		
	}
	
	return x;
}	


void plug_script_bang(t_plug_script *x)
{
	if(x->f_gate)
		outlet_bang(x->f_outany);
}

void plug_script_int(t_plug_script *x, long n)
{
	if(x->f_gate)
		outlet_int(x->f_outany, n);
}

void plug_script_float(t_plug_script *x, double f)
{
	if(x->f_gate)
		outlet_float(x->f_outany, f);
}

void plug_script_list(t_plug_script *x, t_symbol *s, long argc, t_atom *argv)
{
	if(x->f_gate)
		outlet_list(x->f_outany, s, argc, argv);
}

void plug_script_anything(t_plug_script *x, t_symbol *s, long argc, t_atom *argv)
{
	if(x->f_gate)
		outlet_anything(x->f_outany, s, argc, argv);
}

void plug_script_open(t_plug_script *x, t_symbol *s, long argc, t_atom *argv)
{
	int pass = 0;
	if(argc >= 1)
	{
		if (atom_gettype(argv) == A_SYM) 
		{
			if (atom_getsym(argv) == gensym("all"))
			{
				pass = 1;
			}
		}
		else if (atom_gettype(argv) == A_LONG) 
		{
			if (atom_getlong(argv) == x->f_index)
			{
				pass = 1;
			}
		}
		
		if (pass)
		{
			outlet_anything(x->f_outcontr, gensym("open"), 0, NULL); 
		}
	}
	
}

void plug_script_mute(t_plug_script *x, t_symbol *s, long argc, t_atom *argv)
{
	int pass, value;
	t_atom newat[1];
	if(argc >= 2)
	{
		pass = 0;
		if (atom_gettype(argv) == A_SYM) 
		{
			if (atom_getsym(argv) == gensym("all"))
				pass = 1;
		}
		else if (atom_gettype(argv) == A_LONG) 
		{
			if (atom_getlong(argv) == x->f_index)
				pass = 1;
		}
		
		if (pass == 1 && atom_gettype(argv+1) == A_LONG) 
		{
			value = atom_getlong(argv+1);
			if (value >= 1) 
				value = 0;
			else
				value = 1;

			atom_setlong(newat, value);
			outlet_anything(x->f_outcontr, gensym("enable"), 1, newat);
		}
	}
}

void plug_script_target(t_plug_script *x, t_symbol *s, long argc, t_atom *argv)
{
	x->f_gate = 0;
	if(argc >= 1)
	{
		if (atom_gettype(argv) == A_SYM) 
		{
			if (atom_getsym(argv) == gensym("all"))
				x->f_gate = 1;
		}
		else if (atom_gettype(argv) == A_LONG) 
		{
			if (atom_getlong(argv) == x->f_index)
				x->f_gate = 1;
		}
	}
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

//////////////////////////////////////////////////////////////
int plug_harmonic(int index, int order)
{
	float harm;
	harm = ((((float)index + 1.) / 2.));
	if (harm - (int)harm < 0.01) 
	{
		harm = -1 * (int)harm;
		return harm;
	}
	else
	{
		return (int)harm;
	}
}
	
void plug_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet)
{
	t_atom argv[4];
	t_atom rv;
	atom_setobj(argv, send);
	atom_setlong(argv + 1, outlet);
	atom_setobj(argv + 2, receive);
	atom_setlong(argv + 3, inlet);
	object_method_typed(x, gensym("connect"), 4, argv, &rv);
}

void plug_router(t_object *x, int order, t_symbol *s, int mode)
{
	int i, j, ninlet = 0, noutlet = 0;
	t_object *firstPatch, *jb, *o;
	t_object  **inlets, **scripts, **pcontr, **patchs, **outlets, *router[4];
	char name[512];

	firstPatch = newobject_sprintf(x, "@maxclass newobj @text %s @patching_rect 0 0 20 20",	s->s_name);
	
	jb = jpatcher_get_firstobject(firstPatch);
	while(jb) 
	{
		o = jbox_get_object(jb);
		if(object_classname(o)->s_name == gensym("inlet")->s_name) ninlet++;
		else if (object_classname(o)->s_name == gensym("outlet")->s_name) noutlet++;
		jb = jbox_get_nextobject(jb);
	}
	object_free(firstPatch);
	
	if(mode == 1)
	{
		router[0] = newobject_sprintf(x, "@maxclass newobj @text \"route open mute target\" @patching_rect 0 50 20 20");
		router[1] = newobject_sprintf(x, "@maxclass newobj @text \"prepend open\" @patching_rect 0 100 20 20");
		router[2] = newobject_sprintf(x, "@maxclass newobj @text \"prepend mute\" @patching_rect 0 150 20 20");
		router[3] = newobject_sprintf(x, "@maxclass newobj @text \"prepend target\" @patching_rect 0 200 20 20");
		plug_connect(x, router[0], 0, router[1], 0);
		plug_connect(x, router[0], 1, router[2], 0);
		plug_connect(x, router[0], 2, router[3], 0);
		
		inlets = (t_object **)getbytes((order * 2 + 1) * ninlet * sizeof(t_object *));
		scripts = (t_object **)getbytes((order * 2 + 1) * ninlet * sizeof(t_object *));
		for(i = 0; i < (order * 2 + 1) * ninlet; i++)
		{
			inlets[i] = plug_inlet(x, i, order, ninlet, mode);
			scripts[i] = plug_script(x, i, order, ninlet, noutlet, mode);
			plug_connect(x, inlets[i], 0, scripts[i], 0);
			plug_connect(x, inlets[i], 0, router[0], 0);
			inlets[i] = plug_pcontr(x, i, order, ninlet);
			plug_connect(x, scripts[i], 2, inlets[i], 0);
			for(j = 1; j < 4; j++)
				plug_connect(x, router[j], 0, scripts[i], 0);
		}
		
		patchs = (t_object **)getbytes((order * 2 + 1) * sizeof(t_object *));
		for(i = 0; i < (order * 2 + 1); i++)
		{
			patchs[i] = plug_patch(x, s, i, order, mode);
			sprintf(name, "%s (%i)", s->s_name,  plug_harmonic(i, order));
			jpatcher_set_title(patchs[i], gensym(name));
			for(j = 0; j < ninlet; j++)
			{
				plug_connect(x, scripts[i * ninlet +j], 0, patchs[i], j);
				plug_connect(x, scripts[i * ninlet +j], 1, patchs[i], j);
				plug_connect(x, inlets[i * ninlet +j], 0, patchs[i], j);
			}
		}
		outlets = (t_object **)getbytes((order * 2 + 1) * noutlet * sizeof(t_object *));
		for(i = 0; i < (order * 2 + 1) * noutlet; i++)
		{
			outlets[i] = plug_outlet(x, i, order, noutlet, mode);
			plug_connect(x, patchs[int(i /noutlet)], i % noutlet, outlets[i], 0);
		}
	}
	else if(mode == 0)
	{
		inlets = (t_object **)getbytes(ninlet * sizeof(t_object *));
		for(i = 0; i < ninlet; i++)
		{
			inlets[i] = plug_inlet(x, i, order, 1, mode);
		}
		
		scripts = (t_object **)getbytes((order * 2 + 1) * ninlet * sizeof(t_object *));
		pcontr = (t_object **)getbytes((order * 2 + 1) * ninlet * sizeof(t_object *));
		for(i = 0; i < (order * 2 + 1) * ninlet; i++)
		{
			scripts[i] = plug_script(x, i, order, ninlet, noutlet, mode);
			pcontr[i] = plug_pcontr(x, i, order, ninlet);
			plug_connect(x, scripts[i], 2, pcontr[i], 0);
			plug_connect(x, inlets[i % ninlet], 0, scripts[i], 0);
		}
		
		patchs = (t_object **)getbytes((order * 2 + 1) * sizeof(t_object *));
		for(i = 0; i < (order * 2 + 1); i++)
		{
			patchs[i] = plug_patch(x, s, i, order, mode);
			sprintf(name, "%s (%i)", s->s_name,  plug_harmonic(i, order));
			jpatcher_set_title(patchs[i], gensym(name));
			for(j = 0; j < ninlet; j++)
			{
				plug_connect(x, scripts[i * ninlet +j], 0, patchs[i], j);
				plug_connect(x, scripts[i * ninlet +j], 1, patchs[i], j);
				plug_connect(x, pcontr[i * ninlet +j], 0, patchs[i], j);
			}
			
		}
		
		outlets = (t_object **)getbytes((order * 2 + 1) * noutlet * sizeof(t_object *));
		for(i = 0; i < (order * 2 + 1) * noutlet; i++)
		{
			outlets[i] = plug_outlet(x, i, order, noutlet, mode);
			plug_connect(x, patchs[int(i /noutlet)], i % noutlet, outlets[i], 0);
		}
			
	}
	else 
	{
		inlets = (t_object **)getbytes(ninlet * sizeof(t_object *));
		for(i = 0; i < ninlet; i++)
		{
			inlets[i] = plug_inlet(x, i, order, 1, mode);
		}
		
		scripts = (t_object **)getbytes((order + 1) * ninlet * sizeof(t_object *));
		pcontr = (t_object **)getbytes((order + 1) * ninlet * sizeof(t_object *));
		for(i = 0; i < (order + 1) * ninlet; i++)
		{
			scripts[i] = plug_script(x, i, order, ninlet, noutlet, mode);
			pcontr[i] = plug_pcontr(x, i, order, ninlet);
			plug_connect(x, scripts[i], 2, pcontr[i], 0);
			plug_connect(x, inlets[i % ninlet], 0, scripts[i], 0);
		}
		
		patchs = (t_object **)getbytes((order + 1) * sizeof(t_object *));
		for(i = 0; i < (order + 1); i++)
		{
			patchs[i] = plug_patch(x, s, i, order, mode);
			sprintf(name, "%s (%i)", s->s_name,  i);
			jpatcher_set_title(patchs[i], gensym(name));
			for(j = 0; j < ninlet; j++)
			{
				plug_connect(x, scripts[i * ninlet +j], 0, patchs[i], j);
				plug_connect(x, scripts[i * ninlet +j], 1, patchs[i], j);
				plug_connect(x, pcontr[i * ninlet +j], 0, patchs[i], j);
			}
			
		}
		
		outlets = (t_object **)getbytes((order + 1) * noutlet * sizeof(t_object *));
		for(i = 0; i < (order + 1) * noutlet; i++)
		{
			outlets[i] = plug_outlet(x, i, order, noutlet, mode);
			plug_connect(x, patchs[int(i /noutlet)], i % noutlet, outlets[i], 0);
		}
		
	}


}

t_object *plug_inlet(t_object *patcher, int index, int order, int ninlet, int mode)
{
	int harm;
	harm = floor(index / ninlet);
	index %= ninlet;
	if (mode == 1) 
		return newobject_sprintf(patcher, "@maxclass inlet @comment \"Harmonic %i Input %i\" @patching_rect %i 0 20 20 ", plug_harmonic(harm, order), index, harm * 100 + (index * 100) / ninlet);
	else if (mode == 0)
		return newobject_sprintf(patcher, "@maxclass inlet @comment \"Input %i\" @patching_rect %i 0 20 20 ", ninlet, harm * 100 + (index * 100) / ninlet);
	else
		return newobject_sprintf(patcher, "@maxclass inlet @comment \"Input %i\" @patching_rect %i 0 20 20 ", ninlet, harm * 100 + (index * 100) / ninlet);
}

t_object *plug_script(t_object *patcher, int index, int order, int ninlet, int noutlet, int mode)
{
	int harm, last;
	harm = floor(index / ninlet);
	last = index;
	index %= ninlet;
	if (mode == 2)
		return newobject_sprintf(patcher, "@maxclass newobj @text \"hoa.plug_script %i %i %i %i %i\" @patching_rect %i 300 20 20", 
								 last, order, mode, ninlet, noutlet, harm * 100 + (index * 100) / ninlet);
	else
		return newobject_sprintf(patcher, "@maxclass newobj @text \"hoa.plug_script %i %i %i %i %i\" @patching_rect %i 300 20 20", 
								 plug_harmonic(harm, order), order, mode, ninlet, noutlet, harm * 100 + (index * 100) / ninlet);

}

t_object *plug_pcontr(t_object *patcher, int index, int order, int ninlet)
{
	return newobject_sprintf(patcher, "@maxclass newobj @text pcontrol @patching_rect %i 400 20 20 ", 50 + (100 / ninlet) * index);
}

t_object *plug_patch(t_object *patcher, t_symbol *s, int index, int order, int mode)
{
	if (mode == 2)
		return newobject_sprintf(patcher, "@maxclass newobj @text \"%s %i %i\" @patching_rect %i 500 20 20", s->s_name, index, order, index * 100);
	else
		return newobject_sprintf(patcher, "@maxclass newobj @text \"%s %i %i\" @patching_rect %i 500 20 20", s->s_name, plug_harmonic(index, order), order, index * 100);
}
	
t_object *plug_outlet(t_object *patcher, int index, int order, int noutlet, int mode)
{
	int harm, last;
	harm = floor(index / noutlet);
	last = index;
	index %= noutlet;
	if (mode == 2)
		return newobject_sprintf(patcher, "@maxclass outlet @comment \"Order %i Output %i\" @patching_rect %i 600 20 20 ", last, index, harm * 100 + (index * 100) / noutlet);
	else
		return newobject_sprintf(patcher, "@maxclass outlet @comment \"Harmonic %i Output %i\" @patching_rect %i 600 20 20 ", plug_harmonic(harm, order), index, harm * 100 + (index * 100) / noutlet);
}

