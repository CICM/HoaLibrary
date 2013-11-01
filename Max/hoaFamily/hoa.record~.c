/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"

void *record_class;

void *record_new(t_symbol *s, int argc, t_atom *argv);

int C74_EXPORT main(void)
{
	t_class *c;

	c = class_new("hoa.record~", (method)record_new, (method)NULL, (short)sizeof(0), 0L, A_GIMME, 0);
	
	class_register(CLASS_BOX, c);
	record_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
}

void *record_new(t_symbol *s, int argc, t_atom *argv)
{
	t_object *x;
	t_atom arguments[2];
	int order = 4;
	if(atom_gettype(argv) == A_LONG)
		order = atom_getlong(argv);
	else if(atom_gettype(argv) == A_FLOAT)
		order = atom_getfloat(argv);

	if(order < 1)
		order = 1;
	
	atom_setlong(arguments, order * 2 + 1);
	switch (order * 2 + 1) 
	{
		case 9:
			atom_setlong(arguments+1, 181440);
			break;
		case 10:
			atom_setlong(arguments+1, 20160);
			break;
		case 11:
			atom_setlong(arguments+1, 221760);
			break;
		case 12:
			atom_setlong(arguments+1, 60480);
			break;
		case 13:
			atom_setlong(arguments+1, 262080);
			break;
		case 14:
			atom_setlong(arguments+1, 20160);
			break;
		case 15:
			atom_setlong(arguments+1, 60480);
			break;
		case 16:
			atom_setlong(arguments+1, 40320);
			break;
		default:
			atom_setlong(arguments+1, 20160);
			break;
	}
	x = (t_object *)object_new_typed(CLASS_BOX, gensym("sfrecord~"), 2, arguments);
	
	return x;
}	


