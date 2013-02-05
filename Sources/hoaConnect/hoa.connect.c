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
	
	/*
	CLASS_ATTR_RGBA				(c, "poscolor", 0, t_connect, f_colorPositiv);
	CLASS_ATTR_CATEGORY			(c, "poscolor", 0, "Behavior");
	CLASS_ATTR_STYLE			(c, "poscolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "poscolor", 0, "Positif Color");
	CLASS_ATTR_ORDER			(c, "poscolor", 0, "0");
	CLASS_ATTR_DEFAULT			(c, "poscolor", 0, "0. 0. 1. 1.");
	CLASS_ATTR_SAVE				(c, "poscolor", 1);
	*/
	
	class_register(CLASS_BOX, c);
	connect_class = c;
	
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
		
		//object_obex_lookup(x, gensym("#P"), &x->f_patcher); // passé dans la fonction connect_attach
		defer_low(x, (method)connect_attach, NULL, 0, NULL);
	
		x->f_inc = 0;
		x->f_jr.x = 0;
		x->f_jr.y = 0;
		x->f_jr.width = 0;
		x->f_jr.height = 0;
		
		//attr_args_process(x, argc, argv);
		x->f_condition = 0;
		x->f_tab_index = 0;
		x->f_nbSelected = 0;
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
	int i, j;
 
	x->f_inc = 0;
	
	for (i = 0; i < x->f_nbSelected; i++) 
	{	
		if(validName(x->f_object[i]))
		{
			x->f_object[x->f_inc++] = x->f_object[i];
		}
	
	}
	
	//ordonnerTableau(x->f_index, x->f_object, x->f_inc);
	for(i = 1; i < x->f_inc; i++)
	{
		if (object_classname(jbox_get_object(x->f_object[i -1])) == gensym("hoa.decoder~"))
		{
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
	
	for(i  = 0; i < CONNECT_MAX_TAB; i++)
		x->f_object[i] = 0;
	for(i  = 0; i < CONNECT_MAX_TAB; i++)
		x->f_object[i] = NULL;
	
	x->f_nbSelected = 0;
	
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

void clear_objectab(t_connect *x, t_object *objectab[], long tablen)
{
	int i;
	if (!x->f_objectab_cleaned) 
	{
		for(i=0;i<tablen;i++)
			objectab[i] = NULL;
		x->f_objectab_cleaned = 1;
	}
}

void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{	
	int i, j, k, index, tabcheck, nb_object_allready_selected;
	//int condition;
	if (msg == gensym("attr_modified") && sender == x->f_patcherview) 
	{
		t_symbol *attrname;
		attrname = (t_symbol *)object_method(data, gensym("getname"));
		if (attrname == gensym("unselectedboxes")){
			post("unselected !!!");
		}
			
		if (attrname == gensym("selectedboxes")) {
			t_atom *av = NULL;
			long current_nb_selected = 0;
			
			object_attr_getvalueof(sender, attrname, &current_nb_selected, &av);
			if (current_nb_selected && av) 
			{				
				// on supprime tous les objets du tableau qui ne sont plus dans la selection
				/*
				for( i = 0 ; i < current_nb_selected ; i++ )
				{
					//if (i > x->f_tab_index) break;
					tabcheck = 0;
					for(j = 0; j < x->f_nbSelected; j++)
					{
						if (atom_gettype(av+i) == A_OBJ && x->f_object[j] == (t_object*)atom_getobj(av+i)) 
						{	
							tabcheck = 1;
							break;
						}
					}
					
					if (!tabcheck)
						x->f_object[i] = NULL;
				}
				 */
				if(x->f_nbSelected < 0)
					x->f_nbSelected = 0;
				if(current_nb_selected < x->f_nbSelected)
				{
					for(i = 0 ; i < current_nb_selected ; i++)
					{
						//if (i > x->f_tab_index) break;
						tabcheck = 0;
						for(j = 0; j < x->f_nbSelected; j++)
						{
							if (atom_gettype(av+i) == A_OBJ && x->f_object[j] == (t_object*)atom_getobj(av+i)) 
							{	
								tabcheck = 1;
								break;
							}
						}
						
						if (!tabcheck)
							x->f_object[j] = NULL;
					}
				
					// puis on retrie le tableau
					for(i = 0; i < x->f_nbSelected; i++)
					{
						if (x->f_object[i] == NULL)
						{
							for(k = i; k < x->f_nbSelected; k++)
								x->f_object[k] = x->f_object[k+1];
							
							x->f_nbSelected--;
							break;
						}
					}
				}
				else if(current_nb_selected > x->f_nbSelected)
				{
					for(i = 0 ; i < current_nb_selected ; i++)
					{
						tabcheck = 0;
						for(j = 0; j < x->f_nbSelected; j++)
						{
							if (atom_gettype(av+i) == A_OBJ && x->f_object[j] == (t_object*)atom_getobj(av+i)) 
							{	
								tabcheck = 1;
							}
						}
						
						if (!tabcheck)
							x->f_object[x->f_nbSelected] = (t_object*)atom_getobj(av+i);
					}
					x->f_nbSelected++;
				}

				
				
				for(i = 0; i < x->f_nbSelected; i++)
				{
					post("selected %ld : %s", i, jbox_get_maxclass(x->f_object[i])->s_name);
				}
				
				//nb_object_allready_selected = index;
				tabcheck = 0;
				/*
				for(i=0; i<ac; i++)
				{
					if (atom_gettype(av+i) == A_OBJ)
					{
						// on check si l'objet est déja dans le tableau (dans ce cas on le laisse à sa place)
						/*
						tabcheck = 0;
						for( j = 0 ; j < CONNECT_MAX_TAB ; j++ )
						{
							if ( (t_object*)atom_getobj(av+i) == x->f_object[j] )
							{	
								tabcheck = 1;
								break;
							}
						}
						if (!tabcheck) {
							x->f_object[index] = (t_object*)atom_getobj(av+i);
							index++;
						}
						
						// si il n'y
						// si tab vide on stock
						
						
						//post("selected %ld : %s", i, jbox_get_maxclass((t_object*)atom_getobj(av+i))->s_name);
						
						/*
						if(x->f_condition)
						{
							condition = 1;
							for(j=0; j<ac; j++)
							{
								if((t_object*)atom_getobj(av+ac-1) == x->f_object[j])
									condition = 0;
							}
							if(condition)
								x->f_object[ac-1] = (t_object*)atom_getobj(av+ac-1);
						}							
						else
							x->f_object[i] = (t_object*)atom_getobj(av+i);
						 *
					}
				}*/
			}
			freebytes(av, sizeof(t_atom) * current_nb_selected);
		}			
	}


	if (msg == gensym("startdrag"))
	{
		post("startdrag");
		x->f_condition = 1;
	}
	else if (msg == gensym("enddrag"))
	{
		post("enddrag");
		x->f_condition = 0;
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



