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

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"

void *play_class;

void *play_new(t_symbol *s, int argc, t_atom *argv);

int main(void)
{
	t_class *c;

	c = class_new("hoa.play~", (method)play_new, (method)NULL, (short)sizeof(0), 0L, A_GIMME, 0);
	
	class_register(CLASS_BOX, c);
	play_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
}

void *play_new(t_symbol *s, int argc, t_atom *argv)
{
	t_object *x;
	t_atom arguments[1];
	int order = 4;
	if(atom_gettype(argv) == A_LONG)
		order = atom_getlong(argv);
	else if(atom_gettype(argv) == A_FLOAT)
		order = atom_getfloat(argv);

	if(order < 1)
		order = 1;
	
	atom_setlong(arguments, order * 2 + 1);
	x = (t_object *)object_new_typed(CLASS_BOX, gensym("sfplay~"), 1, arguments);
	
	return x;
}	


