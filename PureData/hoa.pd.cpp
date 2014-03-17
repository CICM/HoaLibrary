/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "hoa.pd.h"

void hoa_print_credit()
{
    erouter_add_libary(gensym("HOA"), "HOA Library by Julien Colafrancesco, Pierre Guillot & Eliott Paris", "© 2012 - 2014  CICM | Paris 8 University", "Version 2.0");
}

int hoa_method_true(void *x)
{
    return 1;
}

t_hoa_err hoa_initclass(t_eclass* c, method hoa_getinfos_method)
{
    
	hoa_print_credit();
	
	eclass_addmethod(c, (method)hoa_method_true, "is_hoa", A_CANT, 0);

	if (hoa_getinfos_method)
		eclass_addmethod(c, (method)hoa_getinfos_method, "hoa_getinfos", A_CANT, 0);
	else
		eclass_addmethod(c, (method)hoa_not_implemented_method, "hoa_getinfos", A_CANT, 0);
	
	return HOA_ERR_NONE;
}

t_hoa_err hoa_not_implemented_method()
{
	return HOA_ERR_NOT_IMPLEMENTED;
}

long object_is_hoa(t_object* z)
{
    rmethod nrmethod = NULL;
    nrmethod = (rmethod)zgetfn((t_pd *)z, _sym_is_hoa);
    if(nrmethod)
    {
        return (long)nrmethod((t_pd *)z);
    }
    else
        return 0;
}

void hoa_boxinfos_init(t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_STANDARD;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
}
