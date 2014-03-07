/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaCommon.max.h"

void *record_class;

void *record_new(t_symbol *s, int argc, t_atom *argv);

int C74_EXPORT main(void)
{
	t_class *c;

	c = class_new("hoa.record~", (method)record_new, (method)NULL, (short)sizeof(0), 0L, A_GIMME, 0);
	hoa_initclass(c, NULL);
	class_register(CLASS_BOX, c);
	record_class = c;
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


