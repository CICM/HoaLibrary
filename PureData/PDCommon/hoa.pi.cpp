/*
 // Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "HoaCommon.pd.h"

typedef struct _hoa_pi
{	
	t_eobj p_ob;
	double p_value;
    t_outlet *p_outlet;
} t_hoa_pi;

void pi_bang(t_hoa_pi *x);
void pi_float(t_hoa_pi *x, float n);
void *pi_new(t_symbol *s, int argc, t_atom *argv);

t_eclass *pi_class;

t_hoa_err hoa_getinfos(t_hoa_pi* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2epi(void)
{
    t_eclass* c;
    c = eclass_new("hoa.pi", (method)pi_new,(method)NULL, sizeof(t_hoa_pi), 0L, A_GIMME, 0);
    
    hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)pi_bang,     "bang",      A_CANT, 0);
    eclass_addmethod(c, (method)pi_float,    "float",      A_FLOAT, 0);

    eclass_register(CLASS_OBJ, c);
    pi_class = c;
}

void *pi_new(t_symbol *s, int argc, t_atom *argv)
{
    t_hoa_pi *x = (t_hoa_pi *)eobj_new(pi_class);
	x->p_value = 1.;
    x->p_value = atom_getfloat(argv);
    x->p_outlet = floatout(x);

	return(x);
}

t_hoa_err hoa_getinfos(t_hoa_pi* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_STANDARD;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void pi_bang(t_hoa_pi *x) 
{
    outlet_float(x->p_outlet, (float)HOA_PI * x->p_value);
}

void pi_float(t_hoa_pi *x, float n)
{
	x->p_value = n;
	pi_bang(x);
}


