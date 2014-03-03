/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa2D.max.h"

void hoa_print_credit()
{
    if(gensym("hoa_print_credits")->s_thing == NULL)
    {
		t_object* print;
		t_atom* sym = (t_atom*) malloc( sizeof(t_atom));
		atom_setsym(sym, gensym("HoaLibrary"));
		print = (t_object*)object_new_typed(CLASS_BOX, gensym("print"), 1, sym);
		atom_setsym(sym, _sym_credit_line1);
		object_method_typed(print, gensym("list"), 1, sym, NULL);
		atom_setsym(sym, gensym(" "));
		print = (t_object*)object_new_typed(CLASS_BOX, gensym("print"), 1, sym);
		atom_setsym(sym, _sym_credit_line2);
		object_method_typed(print, gensym("list"), 1, sym, NULL);
		gensym("hoa_print_credits")->s_thing = print;
		freeobject(print);
		free(sym);
    }
}

t_hoa_err hoa_initclass(t_class* c, method hoa_getinfos_method)
{
	hoa_print_credit();
	
	class_addmethod(c, (method)method_true, "is_hoa", A_CANT, 0);

	if (hoa_getinfos_method)
		class_addmethod(c, (method)hoa_getinfos_method, "hoa_getinfos", A_CANT, 0);
	else
		class_addmethod(c, (method)hoa_not_implemented_method, "hoa_getinfos", A_CANT, 0);
	
	return HOA_ERR_NONE;
}

t_hoa_err hoa_not_implemented_method()
{
	return HOA_ERR_NOT_IMPLEMENTED;
}

long object_is_hoa(t_object* o)
{
	return (long) object_method(o, _sym_is_hoa, 0, NULL);
}

void hoa_boxinfos_init(t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_STANDARD;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
}
