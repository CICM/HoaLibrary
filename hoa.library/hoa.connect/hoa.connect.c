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
	init();
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
	t_object *pak;

	if (x = (t_connect *)object_alloc((t_class *)connect_class)) 
	{	
		x->f_count = 0;
		x->f_gate = 0;
		x->f_harmonics = 4;
		t_atom msg[4];
		t_atom rv;
		object_obex_lookup(x, gensym("#P"), &x->f_patcher);
		object_obex_lookup(x, gensym("#B"), &x->f_me);
		x->f_harmonics = n * 2 + 1;

		defer_low(x, (method)connect_attach, NULL, 0, NULL);
		
		x->f_newpatch = (t_object *)object_new_typed(CLASS_NOBOX, gensym("jpatcher"), 0, NULL);
		
		x->f_mouseState =  newobject_sprintf(x->f_newpatch, "@maxclass newobj @text mousestate @patching_rect 0 0 100 20");
		pak = newobject_sprintf(x->f_newpatch, "@maxclass newobj @text \"pak 0 0\" @patching_rect 0 50 100 20");
		x->f_out = newobject_sprintf(x->f_newpatch, "@maxclass newobj @text zorglub @patching_rect 0 100 100 20");
		
		//object_method(x->f_newpatch, gensym("vis"));
		atom_setobj(msg, x->f_mouseState);
		atom_setlong(msg + 1, 1);
		atom_setobj(msg + 2, pak);
		atom_setlong(msg + 3, 0);
		object_method_typed(x->f_newpatch , gensym("connect"), 4, msg, &rv);
		
		atom_setobj(msg, x->f_mouseState);
		atom_setlong(msg + 1, 2);
		atom_setobj(msg + 2, pak);
		atom_setlong(msg + 3, 1);
		object_method_typed(x->f_newpatch , gensym("connect"), 4, msg, &rv);
		
		atom_setobj(msg, pak);
		atom_setlong(msg + 1, 0);
		atom_setobj(msg + 2, x->f_out);
		atom_setlong(msg + 3, 0);
		object_method_typed(x->f_newpatch , gensym("connect"), 4, msg, &rv);
		
		connect_getinput(x);
		x->f_inc = 0;
		
		x->f_jr.x = 0;
		x->f_jr.y = 0;
		x->f_jr.width = 0;
		x->f_jr.height = 0;
	}
	
	return x;
}	

void connect_free(t_connect *x)
{
	if(x->f_patcherview)
		object_detach_byptr(x, x->f_patcherview);
}

void connect_getinput(t_connect *x)
{
	t_object *box, *obj;

	int i = 0;
	for (box = jpatcher_get_firstobject(x->f_newpatch); box; box = jbox_get_nextobject(box)) 
	{		
		obj = jbox_get_object(box);
		if(object_classname(obj) == gensym("mousestate"))
		{
			x->f_mouseState = obj;
			object_method(x->f_mouseState, gensym("mode"), 0);
			i++;
		}

	}
}

void connect_bang(t_connect *x)
{
	t_object *box, *obj;
	t_rect jr;
	int i, j;

	t_atom *av = NULL;
	long ac = 0;
	
	int patchX = 0, patchY = 0;
	
	object_attr_getvalueof(x->f_patcherview, gensym("rect"), &ac, &av);
	if (ac && av) 
	{
		patchX = atom_getfloat(av);
		post(" patcher %i", patchX);
		patchY = atom_getfloat(av+1);
		post(" patcher %i", patchY);
		freebytes(av, sizeof(t_atom) * ac);
	}
	
	x->f_inc = 0;
	for (box = jpatcher_get_firstobject(x->f_patcher); box; box = jbox_get_nextobject(box)) 
	{		
		obj = jbox_get_object(box);
		if(object_classname(obj) == gensym("hoa.decoder~") || object_classname(obj) == gensym("hoa.encoder~") || object_classname(obj) == gensym("hoa.rotate~") || object_classname(obj) == gensym("dac~"))
		{
			jbox_get_patching_rect(box, &jr);
			if(jr.x + jr.width + patchX > x->f_jr.x && jr.y + jr.height + patchY > x->f_jr.y && jr.x + patchX < x->f_jr.width && jr.y + patchY<  x->f_jr.height)
			{
			   x->f_object[x->f_inc++] = box;
			}
		}
	}
	
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
	
	for(i = 1; i < x->f_inc; i++)
	{
		for(j = 0; j < x->f_harmonics; j++)
		{
			connect_connect(x, x->f_object[i -1], j, x->f_object[i], j);
		}
	}
}

void connect_connect(t_connect *x, t_object *send, int outlet, t_object *receive, int inlet)
{
	//t_object *line;
	t_atom msg[4];
	t_atom rv;
	t_jrgba rouge, bleu;
	
	bleu.red = rouge.blue = 0;
	bleu.green = rouge.green = 0;
	bleu.blue = rouge.red = 1;
	bleu.alpha = rouge.alpha =1;
	
	atom_setobj(msg, send);
	atom_setlong(msg + 1, outlet);
	atom_setobj(msg + 2, receive);
	atom_setlong(msg + 3, inlet);
	object_method_typed(x->f_patcher , gensym("connect"), 4, msg, &rv);
	
	//jpatchline_set_color(line, &bleu);

}

void connect_attach(t_connect *x)
{	
	x->f_patcherview = object_attr_getobj(x->f_patcher, gensym("firstview"));
	object_attach_byptr_register(x, x->f_patcherview, CLASS_NOBOX);
}

void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{	
	//post("%s", msg->s_name);
	if (msg == gensym("startdrag"))
	{
		object_method(x->f_mouseState, gensym("bang"));
		x->f_jr.x = xPos;
		x->f_jr.y = yPos;
	}
	else if (msg == gensym("enddrag"))
	{
		object_method(x->f_mouseState, gensym("bang"));
		x->f_jr.width = xPos;
		//post("z %i", xPos);
		x->f_jr.height = yPos;
		//post("f %i", xPos);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init(void)
{
	t_class *c;
	
	c = class_new("zorglub", (method)in_new, (method)NULL, (short)sizeof(t_in), 0L, NULL, 0);
	class_addmethod(c, (method)in_list,				"list",			A_GIMME, 0);

	class_register(CLASS_BOX, c);
	in_class = c;
}

void *in_new()
{
	t_in *x = (t_in *)object_alloc((t_class *)in_class);	
	return x;
}			

void in_list(t_in *x, t_symbol *s, long argc, t_atom *argv)
{
	xPos = atom_getlong(argv);
	yPos = atom_getlong(argv+1);
}


