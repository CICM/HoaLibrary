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

	c = class_new("hoa.connect", (method)connect_new, (method)connect_free, (short)sizeof(t_connect), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)connect_notify,				"notify",		A_CANT, 0);
	class_addmethod(c, (method)connect_bang,				"bang",			A_CANT,	0);
	
	class_register(CLASS_BOX, c);
	connect_class = c;
	
	/*
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_RGBA				(c, "poscolor", 0, t_connect, f_colorPositiv);
	CLASS_ATTR_CATEGORY			(c, "poscolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "poscolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "poscolor", 0, "Positiv Color");
	CLASS_ATTR_ORDER			(c, "poscolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE		(c, "poscolor", 0, "0. 0. 1. 1");
	*/
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
}

void *connect_new(t_symbol *s, long argc, t_atom *argv)
{
	t_connect *x = NULL;

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
		
		//attr_args_process(x, argc, argv);
		
		//object_obex_lookup(x, gensym("#P"), &x->f_patcher); // passé dans la fonction connect_attach
		defer_low(x, (method)connect_attach, NULL, 0, NULL);
	
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

void connect_bang(t_connect *x)
{
	t_object *box;
	
	t_rect jr;
	int i, j;
	t_atom *av = NULL;
	long ac = 0;

	
	int patchX = 0, patchY = 0;
	object_attr_getvalueof(x->f_patcherview, gensym("rect"), &ac, &av);
	if (ac && av) 
	{
		patchX = atom_getfloat(av);
		patchY = atom_getfloat(av+1);
		freebytes(av, sizeof(t_atom) * ac);
	}
 
	x->f_inc = 0;
	for (box = jpatcher_get_firstobject(x->f_patcher); box && x->f_inc < 100; box = jbox_get_nextobject(box)) 
	{	
		jbox_get_patching_rect(box, &jr);
		if(validName(box) && validPos(jr, x->f_jr, patchX, patchY))
		{
			x->f_index[x->f_inc] = jr.y;
			for(i = 0; i < x->f_inc; i++)
			{
				if (x->f_index[x->f_inc] == x->f_index[i]) 
				{
					x->f_index[x->f_inc]++;
				}
			}
			x->f_object[x->f_inc++] = box;
		}
	
	}
	
	ordonnerTableau(x->f_index, x->f_object, x->f_inc);
	for(i = 1; i < x->f_inc; i++)
	{
		if (object_classname(jbox_get_object(x->f_object[i -1])) == gensym("hoa.decoder~"))
		{
			//for(j = 0; j < 30; j++)
//			{
//				if((jbox_get_object(x->f_object[i -1]))->o_inlet[j] != NULL))
//				   k++;
//			}
//			post("inlet %i", k);
			for(j = 0; j < x->f_output; j++)
			{
				connect_connect(x->f_patcher, x->f_object[i -1], j, x->f_object[i], j);
			}
		}
		else if (object_classname(jbox_get_object(x->f_object[i -1])) == gensym("jpatcher"))
		{
			for(j = 0; j < x->f_harmonics; j++)
			{
				connect_connect(x->f_patcher, x->f_object[i -1], j, x->f_object[i], j);
			}
		}
		else
		{
			for(j = 0; j < x->f_harmonics; j++)
			{
				connect_connect(x->f_patcher, x->f_object[i -1], j, x->f_object[i], j);
			}
		}
		
	}
	color_patchline(x);
}

void color_patchline(t_connect *x)
{
	t_object *line, *obj, *patcher;
	t_jrgba rouge, bleu;
	
	bleu.red = rouge.blue = 0;
	bleu.green = rouge.green = 0;
	bleu.blue = rouge.red = 1;
	bleu.alpha = rouge.alpha =1;
	
	//bleu = x->f_colorPositiv;
	
	object_obex_lookup(x, gensym("#P"), &patcher);
	for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line)) 
	{
		obj = jbox_get_object(jpatchline_get_box1(line));
						   
		if (validConditionColor(obj))
		{ 
			if (jpatchline_get_inletnum(line) % 2 == 1) 
				jpatchline_set_color(line, &rouge);
			else
				jpatchline_set_color(line, &bleu);			
		}
	}
}

void connect_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet)
{
	t_atom msg[4];
	t_atom rv;

	atom_setobj(msg, send);
	atom_setlong(msg + 1, outlet);
	atom_setobj(msg + 2, receive);
	atom_setlong(msg + 3, inlet);

	object_method_typed(x , gensym("connect"), 4, msg, &rv);
}

void connect_attach(t_connect *x)
{	
	object_obex_lookup(x, gensym("#P"), &x->f_patcher);
	x->f_patcherview = object_attr_getobj(x->f_patcher, gensym("firstview"));
	object_attach_byptr_register(x, x->f_patcherview, CLASS_NOBOX);
}

void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{	
	int xPos, yPos;
	
	if (msg == gensym("startdrag"))
	{
		jmouse_getposition_global(&xPos, &yPos);
		x->f_jr.x = xPos;
		x->f_jr.y = yPos;
	}
	else if (msg == gensym("enddrag"))
	{
		jmouse_getposition_global(&xPos, &yPos);
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

int validPos(t_rect jr, t_rect f_jr, int patchX, int patchY)
{
	if(jr.x + jr.width + patchX >= f_jr.x && jr.y + jr.height + patchY >= f_jr.y && jr.x + patchX <= f_jr.width && jr.y + patchY <=  f_jr.height)
		return 1;
	else
		return 0;
}

int validName(t_object *box)
{
	int i;
	t_object *jb, *o, *obj;
	char objName[] = "nop.";
	
	obj = jbox_get_object(box);
	
	if(object_classname(obj) == gensym("jpatcher"))
	{
		if(strlen(jpatcher_get_name(obj)->s_name) >= 4)
		{
			for(i = 0; i < 4; i++)
			{
				objName[i] = jpatcher_get_name(obj)->s_name[i];
			}
		}
		else 
		{
			jb = jpatcher_get_firstobject(obj);
			while(jb) 
			{
				o = jbox_get_object(jb);
				if(object_classname(o) == gensym("hoa.plug_script"))
				{
					strcpy(objName, "hoa.");
				}
				jb = jbox_get_nextobject(jb);
			}
		}			
	}
	else if (object_classname(obj) == gensym("dac~") || object_classname(obj) == gensym("sfrecord~") || object_classname(obj) == gensym("sfplay~"))
	{
		strcpy(objName, "hoa.");
	}
	else if (strlen(object_classname(obj)->s_name) >= 4) 
	{
		for(i = 0; i < 4; i++)
		{
			objName[i] = object_classname(obj)->s_name[i];
		}
	}
	
	if(strcmp(objName, "hoa.") == 0)
		return 1;
	else
		return 0;
}

int validConditionColor(t_object *obj)
{
	t_object *jb, *o;
	
	if(object_classname(obj) == gensym("hoa.encoder~") || object_classname(obj) == gensym("hoa.rotate~") || object_classname(obj) == gensym("hoa.recomposer~") || object_classname(obj) == gensym("sfplay~") || object_classname(obj) == gensym("hoa.optim~"))
		return 1;
	else if (object_classname(obj) == gensym("jpatcher"))
	{
		jb = jpatcher_get_firstobject(obj);
		while(jb) 
		{
			o = jbox_get_object(jb);
			if(object_classname(o) == gensym("hoa.plug_script"))
			{
				return 1;
			}
			jb = jbox_get_nextobject(jb);
		}
		
	}		
	
	return 0;
}

void ordonnerTableau(int *positions, t_object **objects, int size) 
{ 
	long i, j, k; 
	t_object *newObject[100];
	int newPosition[100];
	
	for(i = 0; i < size; i++)
	{
		newPosition[i] = positions[i];
	}
	
	for(i = 1; i < size; i++) 
	{ 
		for(j = 0; j < size - 1; j++) 
		{ 
			if(newPosition[j] > newPosition[j+1]) 
			{ 
				k = newPosition[j] - newPosition[j+1]; 
				newPosition[j] -= k; 
				newPosition[j+1] += k; 
			} 
		} 
	}
	
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			if (positions[j] == newPosition[i]) 
			{
				newObject[i] = objects[j];
			}
		}
	}
	for(i = 0; i < size; i++)
	{
		objects[i] = newObject[i];
	}
}



