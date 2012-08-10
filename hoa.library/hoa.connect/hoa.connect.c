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
	c = class_new("hoa.connect", (method)connect_new, (method)connect_free, (short)sizeof(t_connect), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)connect_notify,				"notify",		A_CANT, 0);
	class_addmethod(c, (method)connect_bang,				"bang",			A_CANT,	0);
	
	class_register(CLASS_BOX, c);
	connect_class = c;
	
	post("hoa.connect by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");

	
}

void *connect_new(t_symbol *s, long argc, t_atom *argv)
{
	t_connect *x = NULL;
	t_object *tog, *met, *pak, *mou, *out;

	if (x = (t_connect *)object_alloc((t_class *)connect_class)) 
	{	
		x->f_harmonics = 4;
		x->f_output = 4;
		if(atom_gettype(argv) == A_LONG)
			x->f_harmonics	= atom_getlong(argv) * 2 +1;
		if(atom_gettype(argv+1) == A_LONG)
			x->f_output	= atom_getlong(argv+1);
		else 
			x->f_output = x->f_harmonics;

		
		object_obex_lookup(x, gensym("#P"), &x->f_patcher);
		defer_low(x, (method)connect_attach, NULL, 0, NULL);
		
		x->f_newpatch = (t_object *)object_new_typed(CLASS_NOBOX, gensym("jpatcher"), 0, NULL);
		
		tog = newobject_sprintf(x->f_newpatch, "@maxclass toggle @patching_rect 0 0 20 20");
		met = newobject_sprintf(x->f_newpatch, "@maxclass newobj @text \"metro 20\" @patching_rect 0 50 100 20");
		mou =  newobject_sprintf(x->f_newpatch, "@maxclass newobj @text mousestate @patching_rect 0 100 100 20");
		pak = newobject_sprintf(x->f_newpatch, "@maxclass newobj @text \"pak 0 0\" @patching_rect 0 150 100 20");
		out = newobject_sprintf(x->f_newpatch, "@maxclass newobj @text zorglub @patching_rect 0 200 100 20");
		
		connect_connect(x->f_newpatch , tog, 0, met, 0);
		connect_connect(x->f_newpatch , met, 0, mou, 0);
		connect_connect(x->f_newpatch , mou, 1, pak, 0);
		connect_connect(x->f_newpatch , mou, 2, pak, 1);
		connect_connect(x->f_newpatch , pak, 0, out, 0);
	
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
	for (box = jpatcher_get_firstobject(x->f_newpatch); box; box = jbox_get_nextobject(box)) 
	{		
		obj = jbox_get_object(box);
		if(object_classname(obj) == gensym("mousestate"))
			object_method(obj, gensym("mode"), 0);
		if(object_classname(obj) == gensym("toggle"))
			object_method(obj, gensym("int"), 1);
	}
}

void connect_bang(t_connect *x)
{
	t_object *box, *obj, *jb, *o, *var;
	
	t_rect jr;
	int i, j, k, go;

	t_atom *av = NULL;
	long ac = 0;
	
	int patchX = 0, patchY = 0;
	
	object_attr_getvalueof(x->f_patcherview, gensym("rect"), &ac, &av);
	if (ac && av) 
	{
		patchX = atom_getfloat(av);
		//post(" patcher %i", patchX);
		patchY = atom_getfloat(av+1);
		//post(" patcher %i", patchY);
		freebytes(av, sizeof(t_atom) * ac);
	}
	go = 0;
	x->f_inc = 0;
	for (box = jpatcher_get_firstobject(x->f_patcher); box; box = jbox_get_nextobject(box)) 
	{		
		obj = jbox_get_object(box);
		if(object_classname(obj) == gensym("hoa.decoder~") || object_classname(obj) == gensym("hoa.encoder~") || object_classname(obj) == gensym("hoa.rotate~") || object_classname(obj) == gensym("dac~"))
		{
			jbox_get_patching_rect(box, &jr);
			if(jr.x + jr.width + patchX > x->f_jr.x && jr.y + jr.height + patchY > x->f_jr.y && jr.x + patchX < x->f_jr.width && jr.y + patchY<  x->f_jr.height)
			{
				x->f_index[x->f_inc] = jr.y;
				x->f_object[x->f_inc++] = box;
			}
		}
		else if (object_classname(obj) == gensym("jpatcher"))
		{
			jb = jpatcher_get_firstobject(obj);
			while(jb) 
			{
				o = jbox_get_object(jb);
				jbox_get_patching_rect(box, &jr);
				if(object_classname(o) == gensym("hoa.plug_script"))
				{
					if(jr.x + jr.width + patchX > x->f_jr.x && jr.y + jr.height + patchY > x->f_jr.y && jr.x + patchX < x->f_jr.width && jr.y + patchY<  x->f_jr.height)
					{
						go = 1;
					}
				}
				jb = jbox_get_nextobject(jb);
			}
			if(go)
			{
				x->f_index[x->f_inc] = jr.x;
				x->f_object[x->f_inc++] = box;
				go = 0;
			}
		}
	}
	// Trier de haut en bas //
	for(i = 0; i < x->f_inc; i++)
	{
		for(j = 0; j < x->f_inc - 1; j++)
		{
			if (x->f_index[j] > x->f_index[j+1]) 
			{
				k = x->f_index[j];
				x->f_index[j] = x->f_index[j+1];
				x->f_index[j+1] = k;
				
				var = x->f_object[j];
				x->f_object[j] = x->f_object[j+1];
				x->f_object[j+1] = var;
			}
		}
	}
	for(i = 1; i < x->f_inc; i++)
	{
		k = x->f_harmonics;
		if(object_classname(jbox_get_object(x->f_object[i -1])) == gensym("hoa.decoder~"))
		{
			k++;
		}
		for(j = 0; j < k; j++)
		{
			connect_connect(x->f_patcher, x->f_object[i -1], j, x->f_object[i], j);
		}
	}
}

void connect_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet)
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
	object_method_typed(x , gensym("connect"), 4, msg, &rv);
	
	//jpatchline_set_color(line, &bleu);

}

void connect_attach(t_connect *x)
{	
	x->f_patcherview = object_attr_getobj(x->f_patcher, gensym("firstview"));
	object_attach_byptr_register(x, x->f_patcherview, CLASS_NOBOX);
}

void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{	
	if (msg == gensym("startdrag"))
	{
		x->f_jr.x = xPos;
		x->f_jr.y = yPos;
	}
	else if (msg == gensym("enddrag"))
	{
		if(xPos < x->f_jr.x)
		{
			x->f_jr.width = x->f_jr.x;
			x->f_jr.x = xPos;
		}
		else
			x->f_jr.width = xPos;

		if(yPos < x->f_jr.y)
		{
			x->f_jr.height = x->f_jr.y;
			x->f_jr.y = yPos;
		}
		else
			x->f_jr.height = yPos;
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


