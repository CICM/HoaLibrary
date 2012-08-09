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
	
	post("hoa.plug~ by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");
	
}

void *plug_new(t_symbol *s, int argc, t_atom *argv)
{
	int order, mode, harmonics;
	t_symbol *patchname;

	t_object *x;
	
	x = (t_object *)object_new(CLASS_NOBOX, gensym("jpatcher"), 0, NULL);
	//method_object_setmethod(object_getmethod_object(x, gensym("dblclick")), (method)plug_dblclick);
	
	order = 1;
	if(atom_gettype(argv) == A_LONG)
		order = atom_getlong(argv);
	if(order < 1)
		order = 1;
	harmonics = 2 * order +1;
	patchname = gensym("p");
	if(atom_gettype(argv+1) == A_SYM)
		patchname = atom_getsym(argv+1);
	
	mode = 0;
	if(atom_gettype(argv+2) == A_SYM)
	{
		if(atom_getsym(argv+2) == gensym("pre"))
			mode = 0;
		else if(atom_getsym(argv+2) == gensym("post"))
			mode = 1;
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
	//class_addmethod(c, (method)plug_script_load,				"load",			A_SYM, 0);
	
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
		
		object_obex_lookup(x, gensym("#P"), &x->f_hoaPatcher);
		object_obex_lookup(x, gensym("#B"), (t_object **)&x->f_myBox);
		
		x->f_order = atom_getlong(argv);
		x->f_index = atom_getlong(argv+1);
		x->f_mode = atom_getlong(argv+2);
		x->f_patchName = atom_getsym(argv+3);
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
			if (atom_getlong(argv) == plug_harmonic(x->f_index, x->f_order))
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
			if (atom_getlong(argv) == plug_harmonic(x->f_index, x->f_order))
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
			if (atom_getlong(argv) == x->f_order)
				x->f_gate = 1;
		}
	}
}


void plug_script_load(t_plug_script *x, t_symbol *s)
{
	t_object *jb, *o, *next;
	if(x->f_index == 0)
	{
		jb = jpatcher_get_firstobject(x->f_hoaPatcher);
		while(jb) 
		{
			next = jbox_get_nextobject(jb);
			o = jbox_get_object(jb);
			if (jpatcher_is_patcher(o))
				object_free(jb);
			else if(object_classname(o)->s_name != gensym("hoa.plug_script")->s_name)
				object_free(o);		
			jb = next;
		}
		x->f_patchName = s;
		plug_routons(x->f_hoaPatcher, x->f_order, s, x->f_mode);
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
	
	atom_setobj(argv, send);
	atom_setlong(argv + 1, outlet);
	atom_setobj(argv + 2, receive);
	atom_setlong(argv + 3, inlet);
	defer_low(x, (method)plug_defer, NULL, 4, argv);
}

void plug_defer(t_object *x, t_symbol *s, short argc, t_atom *argv)
{
	t_atom rv;
	object_method_typed(x, gensym("connect"), argc, argv, &rv);
}

void plug_script(t_object *patcher, t_symbol *s, int index, int order, t_object *script, int mode)
{
	script = newobject_sprintf(patcher, "@maxclass newobj @text \"hoa.plug_script %i %i %i %s\" @patching_rect %i 200 20 20 @varname script", 
								  order, plug_harmonic(index, order), mode, s->s_name, (index * 50));
}

void plug_patch(t_object *patcher, t_symbol *s, int *ninlet, int *noutlet, t_object *patch, int index, int order, t_object *script)
{
	t_object *jb;
	t_object *o;
	char	name[512];
	ninlet[0] = 0;
	noutlet[0] = 0;
	
	patch = newobject_sprintf(patcher, "@maxclass newobj @text \"%s %i %i\" @patching_rect %i 400 20 20 @varname patch", s->s_name, plug_harmonic(index, order), order,  index * 50);
	sprintf(name, "%s (%i)", s->s_name,  plug_harmonic(index, order));
	jpatcher_set_title(patch, gensym(name));
	
	jb = jpatcher_get_firstobject(patch);
	while(jb) 
	{
		o = jbox_get_object(jb);
		if(object_classname(o)->s_name == gensym("inlet")->s_name) ninlet[0]++;
		else if (object_classname(o)->s_name == gensym("outlet")->s_name) noutlet[0]++;
		jb = jbox_get_nextobject(jb);
	}	
}

void plug_outlet(t_object *patcher, t_object **outlets, int noutlet, t_object *patch, int index, int order)
{
	int i;
	
	outlets = (t_object **)getbytes(noutlet * sizeof(t_object *));
	for(i = 0; i < noutlet; i++)
	{
		outlets[i] = newobject_sprintf(patcher, "@maxclass outlet @comment \"Harmonic %i\" @patching_rect %i 500 20 20 @varname outlet", plug_harmonic(index, order) , index * 50 + i * 50 / noutlet);
	}
}

void plug_inlet(t_object *patcher, t_object **inlets, int nInlet, int mode, int index, int order, t_object *plug_script)
{
	int i;
	if(mode == 0 && index == order * 2)
	{
		inlets = (t_object **)getbytes(nInlet * sizeof(t_object *));
		for(i = 0; i < nInlet; i++)
			inlets[i] = newobject_sprintf(patcher, "@maxclass inlet @comment \"Global Input %i\" @patching_rect %i 0 20 20 @varname inlet", i, i * 50 / nInlet);
	}
	else if(mode == 1)
	{
		inlets = (t_object **)getbytes(nInlet * sizeof(t_object *));
		for(i = 0; i < nInlet; i++)
		{
			inlets[i] = newobject_sprintf(patcher, "@maxclass inlet @comment \"Patch %i Input %i\" @patching_rect %i 0 20 20 @varname inlet", 
											   index, i, index * 50 + i * 50 / nInlet);
		}
	}
}

void plug_routo(t_object *patcher, t_object **router, int mode, int nInlets, t_object *script, t_object **inlets, int index)
{	
	if (mode == 1 && index == 0) 
	{
		router[0] = newobject_sprintf(patcher, "@maxclass newobj @text \"route open mute target\" @patching_rect 0 50 20 20 @varname route1");
		router[1] = newobject_sprintf(patcher, "@maxclass newobj @text \"prepend open\" @patching_rect 0 75 20 20 @varname route2");
		router[2] = newobject_sprintf(patcher, "@maxclass newobj @text \"prepend mute\" @patching_rect 0 100 20 20 @varname route3");
		router[3] = newobject_sprintf(patcher, "@maxclass newobj @text \"prepend target\" @patching_rect 0 125 20 20 @varname route4");
		 
	}
	
}

void plug_router(t_object *x, int order, t_symbol *s, int mode)
{
	int i, nInlet, nOutlet;
	t_object **patchs, ***inlets, ***outlets, **script, **router;
	t_object *send, *receive;
	script = (t_object **)getbytes((order * 2 + 1) * sizeof(t_object *));
	patchs = (t_object **)getbytes((order * 2 + 1) * sizeof(t_object *));
	outlets = (t_object ***)getbytes((order * 2 + 1) * sizeof(t_object **));
	inlets = (t_object ***)getbytes((order * 2 + 1) * sizeof(t_object **));
	router = (t_object **)getbytes(4 * sizeof(t_object **));
	
	/* script */
	for(i = 0; i < (order * 2 + 1) && i < 100; i++)
	{
		plug_patch(x, s, &nInlet, &nOutlet, patchs[i], i, order, script[i]);
		plug_inlet(x, inlets[i], nInlet, mode, i, order, script[i]);
		plug_routo(x, router, mode, nInlet, script[i], inlets[i], i);
		plug_script(x, s, i, order, script[i], mode);
		plug_outlet(x, outlets[i], nOutlet, patchs[i], i, order);
	}
	
	if(mode == 1)
	{
		send = jbox_get_varname(<#t_object *b#>)
	/*
	jbox_get_varname
	plug_connect(x, script[0], 0, patchs[0], 0);
	 */
}

void plug_routons(t_object *x, int order, t_symbol *s, int mode)
{
	int i, nInlet, nOutlet;
	t_object **patchs, ***inlets, ***outlets, **router;
	
	patchs = (t_object **)getbytes((order * 2 + 1) * sizeof(t_object *));
	outlets = (t_object ***)getbytes((order * 2 + 1) * sizeof(t_object **));
	inlets = (t_object ***)getbytes((order * 2 + 1) * sizeof(t_object **));
	router = (t_object **)getbytes(4 * sizeof(t_object **));
	
	for(i = 0; i < (order * 2 + 1); i++)
	{
		plug_patch(x, s, &nInlet, &nOutlet, patchs[i], i, order, NULL);
		plug_inlet(x, inlets[i], nInlet, mode, i, order, NULL);
		plug_routo(x, router, mode, nInlet, NULL, inlets[i], i);
		plug_outlet(x, outlets[i], nOutlet, patchs[i], i, order);
	}
}
