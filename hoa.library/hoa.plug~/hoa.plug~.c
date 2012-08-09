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
	class_addmethod(patcher, (method)plug_load, "load");
	
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
	
	t_object *x;
	char	args[512];
	
	order = 1;
	if(atom_gettype(argv) == A_LONG)
		order = atom_getlong(argv);
	if(order < 1)
		order = 1;
	harmonics = 2 * order + 1;
	
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

	x = (t_object *)object_new(CLASS_NOBOX, gensym("jpatcher"), 0, NULL);
	jpatcher_set_title(x, gensym("hoa.plug~"));
	
	//method_object_setmethod(object_getmethod_object(x, gensym("dblclick")), (method)plug_dblclick);

	if (mode == 0)
	{
		inlets = (t_object **)getbytes(1 * sizeof(t_object *));
		patchs = (t_object **)getbytes(harmonics * sizeof(t_object *));
		outlets = (t_object **)getbytes(harmonics * sizeof(t_object *));
		
		inlets[0] = newobject_sprintf(x, "@maxclass inlet @comment Signal @patching_rect 0 0 20 20");
		
		for(i = 0; i < harmonics; i++)
		{
			
			
			patchs[i] = newobject_sprintf(x, "@maxclass newobj @text \"%s %i %i %i\" @patching_rect %i 400 20 20", patchname->s_name, (i - harmonics / 2), i, abs((i - harmonics / 2)),  (i * 50));
			sprintf(args, "%s (%i)", patchname->s_name, (i - harmonics / 2));
			jpatcher_set_title(patchs[i], gensym(args));
			
			plug_router(x, inlets[0], patchs[i], i);
			//plug_connect(x, inlets[0], 0, routes[i], 0);
			/*
			atom_setobj(msg, route[0]);
			atom_setlong(msg + 1, 3);
			atom_setobj(msg + 2, patchs[i]);
			atom_setlong(msg + 3, 0);
			object_method_typed(x, gensym("connect"), 4, msg, &rv);
			*/
			sprintf(args, "Harmonic %i", (i - harmonics / 2));
			outlets[i] = newobject_sprintf(x, "@maxclass outlet @comment \"%s \" @patching_rect %i 500 20 20 ", args, (i * 50));
			plug_connect(x, patchs[0], 0, outlets[0], 0);
		}
	}
	else if (mode == 1)
	{
		inlets = (t_object **)getbytes(harmonics * sizeof(t_object *));
		patchs = (t_object **)getbytes(harmonics * sizeof(t_object *));
		outlets = (t_object **)getbytes(harmonics * sizeof(t_object *));
		/*
		for(i = 0; i < harmonics; i++)
		{
			sprintf(args, "Harmonic %i", (i - harmonics / 2));
			inlets[i] = newobject_sprintf(x, "@maxclass inlet  @comment \"%s \" @patching_rect %i 100 20 20", args, (i * 50));
			atom_setobj(msg, inlets[i]);
			atom_setlong(msg + 1, 0);
			patchs[i] = newobject_sprintf(x, "@maxclass newobj @text \"%s %i\" @patching_rect %i 200 20 20", patchname->s_name, (i - harmonics / 2), (i * 50));
			sprintf(args, "%s (%i)", patchname->s_name, (i - harmonics / 2));
			jpatcher_set_title(patchs[i], gensym(args));
			atom_setobj(msg + 2, patchs[i]);
			atom_setlong(msg + 3, 0);
			object_method_typed(x, gensym("connect"), 4, msg, &rv);
			atom_setobj(msg, patchs[i]);
			atom_setlong(msg + 1, 0);
			sprintf(args, "Harmonic %i", (i - harmonics / 2));
			outlets[i] = newobject_sprintf(x, "@maxclass outlet @comment \"%s \" @patching_rect %i 300 20 20 ", args, (i * 50));
			atom_setobj(msg + 2, outlets[i]);
			atom_setlong(msg + 3, 0);
			object_method_typed(x, gensym("connect"), 4, msg, &rv);
		}*/
	}
		return x;
	
}			

void plug_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet)
{
	t_atom msg[4];
	t_atom rv;
	
	atom_setobj(msg, send);
	atom_setlong(msg + 1, outlet);
	atom_setobj(msg + 2, receive);
	atom_setlong(msg + 3, inlet);
	object_method_typed(x, gensym("connect"), 4, msg, &rv);
}

void plug_router(t_object *x, t_object *inlet, t_object *patch, int index)
{
	t_object *route;
	t_object *routo[2];
	t_object *sel;
	t_object *signal;
	

	route = newobject_sprintf(x, "@maxclass newobj @text \"route mute open target signal\" @patching_rect %i 50 20 20", (index * 50));
	plug_connect(x, inlet, 0, route, 0);
	routo[0] = newobject_sprintf(x, "@maxclass newobj @text \"route %i\" @patching_rect %i 100 20 20", index, (index * 50));
	plug_connect(x, route, 0, routo[0], 0);
	routo[1] = newobject_sprintf(x, "@maxclass newobj @text \"route %i\" @patching_rect %i 100 20 20", index, (index * 50));
	plug_connect(x, route, 1, routo[1], 0);
	sel = newobject_sprintf(x, "@maxclass newobj @text \"sel 0 %i\" @patching_rect %i 100 20 20", index, (index * 50));
	plug_connect(x, route, 2, sel, 0);
	signal = newobject_sprintf(x, "@maxclass message @text signal @patching_rect %i 150 20 20", (index * 50));
	plug_connect(x, route, 3, signal, 0);
	
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

void plug_load(t_object *x)
{	
	t_object *box, *obj;
	if(jpatcher_get_title(x) == gensym("hoa.plug~"))
	{
		for (box = jpatcher_get_firstobject(x); box; box = jbox_get_nextobject(box)) 
		{		
			obj = jbox_get_object(box);
			
			if(object_classname(obj) == gensym("jpatcher"))
			{
				object_free(obj);
				return;
			}
		}
	}
}

