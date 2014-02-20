/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "hoa.max.h"

void hoa_credit()
{
    static t_object hoa_cred;
    if(gensym("hoa.credit")->s_thing == NULL)
    {
        post("hoa.library (version 2.0) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
        post("Copyright (C) 2012 - 2014, CICM | Universite Paris 8");
        gensym("hoa.credit")->s_thing = &hoa_cred;
    }
}

void hoa_print_credit()
{
    if(gensym("hoa_print_credits")->s_thing == NULL)
    {
		t_atom* sym = new t_atom;
		atom_setsym(sym, gensym("HoaLibrary"));
		t_object* print = (t_object*)object_new_typed(CLASS_BOX, gensym("print"), 1, sym);
		atom_setsym(sym, gensym("(v2.0) by Julien Colafrancesco, Pierre Guillot & Eliott Paris"));
		object_method_typed(print, gensym("list"), 1, sym, NULL);
		freeobject(print);
		atom_setsym(sym, gensym(" "));
		print = (t_object*)object_new_typed(CLASS_BOX, gensym("print"), 1, sym);
		atom_setsym(sym, gensym("Copyright \u00a9 2012 - 2014, CICM | Universite Paris 8"));
		object_method_typed(print, gensym("list"), 1, sym, NULL);
		gensym("hoa_print_credits")->s_thing = print;
		freeobject(print);
		delete sym;
    }
}



