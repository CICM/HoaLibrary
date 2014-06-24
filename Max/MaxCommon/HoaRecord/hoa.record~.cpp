/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

/**
 @file      hoa.record~.cpp
 @name      hoa.record~
 @realname  hoa.record~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 an ambisonic <o>sfrecord~</o> object
 
 @description
 <o>hoa.record~</o> is a wrapped <o>sfrecord~</o> object
 
 @discussion
 <o>hoa.record~</o> is a wrapped <o>sfrecord~</o> object
 
 @category ambisonics, hoa objects, audio, msp
 
 @seealso hoa.play~, sfplay~, sfrecord~
 */

#include "../../hoa.max.h"

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
    // @arg 0 @ambisonic-order @optional 0 @type int @digest The ambisonic order
    // @description The ambisonic order, must be at least equal to 1
    
	t_object *x;
	t_atom arguments[2];
	int order = 1;
	if(atom_gettype(argv) == A_LONG)
		order = atom_getlong(argv);
	else if(atom_gettype(argv) == A_FLOAT)
		order = atom_getfloat(argv);

	if(order < 1)
		order = 1;
    
    int is2D = 1;
    
    if (s == gensym("hoa.3d.record~"))
        is2D = 0;
    
    int number_of_channels = is2D ? (order * 2 + 1) : ( (order+1)*(order+1) );
	
	atom_setlong(arguments, number_of_channels);
    
	switch (number_of_channels)
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


