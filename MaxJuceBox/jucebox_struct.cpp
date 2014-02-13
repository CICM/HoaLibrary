/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "jucebox_struct.h"

t_max_err eclass_addmethod(t_jbclass* c, method m, const char* name, e_max_atomtypes type, long anything)
{
	class_addmethod((t_class*) c, m, name, type, anything);
	return MAX_ERR_NONE;
}