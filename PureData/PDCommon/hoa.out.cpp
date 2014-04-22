/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaCommon.pd.h"

typedef struct _hoa_out
{
    t_eobj  f_obj;
    t_outlet *f_outlet;
    int    f_extra;
} t_hoa_out;

t_eclass *hoa_out_class;

void *hoa_out_new(t_symbol *s, long argc, t_atom *argv);
void hoa_out_free(t_hoa_out *x);

void hoa_out_bang(t_hoa_out *x);
void hoa_out_float(t_hoa_out *x, float f);
void hoa_out_symbol(t_hoa_out *x, t_symbol* s);
void hoa_out_list(t_hoa_out *x, t_symbol* s, int argc, t_atom* argv);
void hoa_out_anything(t_hoa_out *x, t_symbol* s, int argc, t_atom* argv);

t_hoa_err hoa_getinfos(t_hoa_out* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2eout(void)
{
    t_eclass* c;
    c = eclass_new("hoa.out", (method)hoa_out_new, (method)hoa_out_free, (short)sizeof(t_hoa_out), CLASS_NOINLET, A_GIMME, 0);
    
    hoa_initclass(c, (method)hoa_getinfos);
    
    eclass_addmethod(c, (method)hoa_out_bang,       "bang",     A_CANT,  0);
    eclass_addmethod(c, (method)hoa_out_float,      "float",    A_FLOAT, 0);
    eclass_addmethod(c, (method)hoa_out_symbol,     "symbol",   A_SYMBOL,0);
    eclass_addmethod(c, (method)hoa_out_list,       "list",     A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_out_anything,   "anything", A_GIMME, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_out_class = c;
    
}

void *hoa_out_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_out *x = NULL;
    
    x = (t_hoa_out *)eobj_new(hoa_out_class);
	if(x)
	{
        inlet_new(&x->f_obj.o_obj, &x->f_obj.o_obj.ob_pd, 0, 0);
        x->f_outlet = NULL;
        x->f_extra = 0;
        if(argc > 1 && argv && atom_gettype(argv) == A_SYM && atom_gettype(argv+1) == A_FLOAT && atom_getsym(argv) == gensym("extra") && atom_getfloat(argv+1) > 0)
        {
            x->f_extra = atom_getfloat(argv+1);
        }
        else if(argc && argv)
        {
            pd_error(x, "wrong argument.");
            eobj_free(x);
            return NULL;
        }
	}
    
	return x;
}

void hoa_out_free(t_hoa_out *x)
{
    eobj_free(x);
}

t_hoa_err hoa_getinfos(t_hoa_out* x, t_hoa_boxinfos* boxinfos)
{
    boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_out_bang(t_hoa_out *x)
{
    if(x->f_outlet)
        outlet_bang(x->f_outlet);
}

void hoa_out_float(t_hoa_out *x, float f)
{
    if(x->f_outlet)
        outlet_float(x->f_outlet, f);
}

void hoa_out_symbol(t_hoa_out *x, t_symbol* s)
{
    if(x->f_outlet)
        outlet_symbol(x->f_outlet, s);
}

void hoa_out_list(t_hoa_out *x, t_symbol* s, int argc, t_atom* argv)
{
    if(x->f_outlet)
        outlet_list(x->f_outlet, s, argc, argv);
}

void hoa_out_anything(t_hoa_out *x, t_symbol* s, int argc, t_atom* argv)
{
    if(x->f_outlet)
        outlet_anything(x->f_outlet, s, argc, argv);
}

