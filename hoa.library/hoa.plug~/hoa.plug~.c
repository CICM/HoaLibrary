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
	
	c = class_new("hoa.plug~", (method)plug_new, (method)NULL, (short)sizeof(t_plug *), 0L, A_GIMME, 0);	

	dblclickpatcher = class_method(class_findbyname(CLASS_NOBOX, gensym("jpatcher")), gensym("dblclick"));
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	plug_class = c;
	
	post("hoa.plug~ by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");

}

void *plug_new(t_symbol *s, int argc, t_atom *argv)
{
	int i, order, mode, harmonics;
	t_symbol *patchname;
	
	t_object **inlets;
	t_object **outlets;
	t_object **patchs;
	
	t_atom msg[4];
	t_atom rv;
	
	t_object *x = (t_object *)object_new(CLASS_NOBOX, gensym("jpatcher"), 0, NULL);
	jpatcher_set_title(x, gensym("hoa.plug~"));
	//object_unregister(x);
	//object_register(CLASS_NOBOX, gensym("hoa.plug~"), x);
	//post("fontname %s", (t_symbol *)jbox_get_varname(x)->s_name);

	//method_object_setmethod(object_getmethod_object(x, gensym("dblclick")), (method)plug_dblclick);
	//method_object_setmethod(object_getmethod_object(x, gensym("assist")), (method)plug_assist);
	

	t_class *patcherClass = class_findbyname(CLASS_NOBOX, gensym("jpatcher"));
	for(i = 0; i < 1; i++)
		post("mess : %s", patcherClass->c_newmess[i].m_sym->s_name);

	order = 1;
	if(atom_gettype(argv) == A_LONG)
		order = atom_getlong(argv);
	if(order < 1)
		order = 1;
	harmonics = 2 * order + 1;
	
	patchname = gensym("patcher");
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

	if (mode == 0)
	{
		inlets = (t_object **)getbytes(1 * sizeof(t_object *));
		patchs = (t_object **)getbytes(harmonics * sizeof(t_object *));
		outlets = (t_object **)getbytes(harmonics * sizeof(t_object *));
		
		inlets[0] = newobject_sprintf(x, "@maxclass newobj @text inlet @comment Signal @patching_rect 0 100 20 20 ");
		
		for(i = 0; i < harmonics; i++)
		{
			atom_setobj(msg, inlets[0]);
			atom_setlong(msg + 1, 0);
			patchs[i] = newobject_sprintf(x, "@maxclass newobj @text %s @patching_rect %i 200 20 20", patchname->s_name, (i * 50));
			atom_setobj(msg + 2, patchs[i]);
			atom_setlong(msg + 3, 0);
			object_method_typed(x, gensym("connect"), 4, msg, &rv);
			atom_setobj(msg, patchs[i]);
			atom_setlong(msg + 1, 0);
			outlets[i] = newobject_sprintf(x, "@maxclass outlet @comment Harmonic %i @patching_rect %i 300 20 20 ",(i - (harmonics / 2)), (i * 50));
			atom_setobj(msg + 2, outlets[i]);
			atom_setlong(msg + 3, 0);
			object_method_typed(x, gensym("connect"), 4, msg, &rv);
		}
	}
	else if (mode == 1)
	{
		inlets = (t_object **)getbytes(harmonics * sizeof(t_object *));
		patchs = (t_object **)getbytes(harmonics * sizeof(t_object *));
		outlets = (t_object **)getbytes(harmonics * sizeof(t_object *));
		
		for(i = 0; i < harmonics; i++)
		{
			inlets[i] = newobject_sprintf(x, "@maxclass newobj @text inlet @patching_rect 0 100 20 20 @comment Anything");
			atom_setobj(msg, inlets[i]);
			atom_setlong(msg + 1, 0);
			patchs[i] = newobject_sprintf(x, "@maxclass newobj @text %s @patching_rect %i 200 20 20", patchname->s_name, (i * 50));
			atom_setobj(msg + 2, patchs[i]);
			atom_setlong(msg + 3, 0);
			object_method_typed(x, gensym("connect"), 4, msg, &rv);
			atom_setobj(msg, patchs[i]);
			atom_setlong(msg + 1, 0);
			outlets[i] = newobject_sprintf(x, "@maxclass newobj @text outlet @patching_rect %i 300 20 20 @comment Harmonic",(i * 50));
			atom_setobj(msg + 2, outlets[i]);
			atom_setlong(msg + 3, 0);
			object_method_typed(x, gensym("connect"), 4, msg, &rv);
		}
	}

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

void plug_assist(t_object *x, void *b, long m, long a, char *s)
{
	
	//t_class *patcherClass = (t_class *)x->o_messlist[-1];
	//post("name : %s", x->o_messlist[0].m_sym->s_name);
	//post("type : %s", x->o_messlist[0].m_type);
	//object_method(x, gensym("classname"), gensym("hoa."));
	//patcherClass->c_sym = gensym("hoa.plug~");
	if(jpatcher_get_title(x) == gensym("hoa.plug~"))
	{
		if (m == ASSIST_INLET) 
		{
			sprintf(s,"Dummy");
		}
		else 
		{
			sprintf(gensym("hoa.plug~ :")->s_name,"(Signal) Output signal");
		}
	}
	//patcherClass->c_sym = gensym("jpatcher");
}

