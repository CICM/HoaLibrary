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

#include "hoa.connect.h"

int main(void)
{
	t_class *c;

	c = class_new("hoa.connect", (method)connect_new, (method)connect_free, (short)sizeof(t_connect), 0L, A_LONG, 0);
	
	class_addmethod(c, (method)connect_notify,				"notify",		A_CANT, 0);
	class_addmethod(c, (method)connect_bang,				"bang",			A_CANT,	0);
	
	class_register(CLASS_BOX, c);
	connect_class = c;
	
	post("hoa.plug~ by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");

}

void *connect_new(long n)
{
	t_connect *x = NULL;
	
	if (x = (t_connect *)object_alloc((t_class *)connect_class)) 
	{	
		x->f_count = 0;
		x->f_gate = 0;
		x->f_harmonics = 4;
		object_obex_lookup(x, gensym("#P"), &x->f_patcher);
		x->f_harmonics = n * 2 + 1;
		x->f_object = (t_object **)getbytes(20 * sizeof(t_object *));
		defer_low(x, (method)connect_attach, NULL, 0, NULL);
	}
	
	return x;
}	


void connect_bang(t_connect *x)
{
	int i, j;
	for(i = 1; i < x->f_count; i++)
	{
		for(j = 0; j < x->f_inlet[x->f_count]; j++)
		{
			connect_connect(x, x->f_object[i -1], j, x->f_object[i], j);
		}
	}
	
	post("bang");
	/*
	for(i = 0; i < 10; i++)
		x->f_object[i] = NULL;*/
}

void connect_connect(t_connect *x, t_object *send, int outlet, t_object *receive, int inlet)
{
	t_atom msg[4];
	t_atom rv;
	
	atom_setobj(msg, send);
	atom_setlong(msg + 1, outlet);
	atom_setobj(msg + 2, receive);
	atom_setlong(msg + 3, inlet);
	object_method_typed(x->f_patcher , gensym("connect"), 4, msg, &rv);
}

void connect_free(t_connect *x)
{
	if(x->f_patcherview)
		object_detach_byptr(x, x->f_patcherview);
}

void connect_attach(t_connect *x)
{	
	x->f_patcherview = object_attr_getobj(x->f_patcher, gensym("firstview"));
	object_attach_byptr_register(x, x->f_patcherview, CLASS_NOBOX);
}

void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{	

	int i, go;
	long *argc;
	t_atom **argv;
	t_object *object, *cible, *jb, *o;
	t_symbol *className, *typeName;

	if(msg == gensym("startdrag"))
	{
		x->f_gate = 1;
		x->f_count = 0;
		for(i = 0; i < 10; i++)
			x->f_object[i] = 0;
	}
	else if(msg == gensym("enddrag"))
		x->f_gate = 0;
	if (msg == gensym("attr_modified") && sender == x->f_patcherview && x->f_gate == 1) 
	{
		className = (t_symbol *)object_method(data, gensym("getname"));
		typeName = (t_symbol *)object_method(data, gensym("gettype"));

		if (className == gensym("selectedboxes") || typeName == gensym("object"))
		{
			object_attr_getvalueof(sender, gensym("selectedboxes"), argc, argv);
			if(atom_gettype(argv[0]) == A_OBJ)
			{
				cible = (t_object *)atom_getobj(argv[0]);
				object = jbox_get_object(cible);
				className = object_classname(object);
				go = 1;
				for(i = 0; i < x->f_count; i++)
				{
					if(x->f_object[i] == cible)
					{
						go = 0;
						post("non");
					}
				}
				if(go)
				{
					if(className->s_name == gensym("hoa.rotate~")->s_name)
					   x->f_object[x->f_count] = cible;
					else if (className->s_name == gensym("hoa.decoder~")->s_name)
					{
						x->f_object[x->f_count] = cible;
						post("oui");
					}
					else if (className->s_name == gensym("hoa.encoder~")->s_name)
						x->f_object[x->f_count] = (t_object *)(t_object *)atom_getobj(argv[0]);
					else if (className->s_name == gensym("jpatcher")->s_name)
					{
						jb = jpatcher_get_firstobject(x->f_patcher);
						while(jb) 
						{
							o = jbox_get_object(jb);
							if(object_classname(o)->s_name == gensym("hoa.plug_script")->s_name)
							{
								x->f_object[x->f_count] = cible;
							}
							jb = jbox_get_nextobject(jb);
						}
					}
					x->f_inlet[x->f_count] = x->f_harmonics;
					x->f_count++;
				}
					
			}
						 
		}
		
	}
}

