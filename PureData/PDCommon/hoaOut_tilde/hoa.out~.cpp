/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../HoaCommon.pd.h"

typedef struct _hoa_out_tilde
{
    t_edspobj   f_obj;
    t_sample*   f_signal;
    int         f_extra;
} t_hoa_out_tilde;

t_eclass *hoa_out_tilde_class;

void *hoa_out_tilde_new(t_symbol *s, long argc, t_atom *argv);
void hoa_out_tilde_free(t_hoa_out_tilde *x);

void hoa_out_tilde_dsp(t_hoa_out_tilde *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_out_tilde_perform(t_hoa_out_tilde *x, t_object *dsp, float **inps, long ni, float **outs, long no, long sf, long f,void *up);

t_hoa_err hoa_getinfos(t_hoa_out_tilde* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2eout_tilde(void)
{
    t_eclass* c;
    c = eclass_new("hoa.out~", (method)hoa_out_tilde_new, (method)hoa_out_tilde_free, (short)sizeof(t_hoa_out_tilde), 0, A_GIMME, 0);
    
    hoa_initclass(c, (method)hoa_getinfos);
    eclass_dspinit(c);
    eclass_addmethod(c, (method)hoa_out_tilde_dsp, "dsp", A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_out_tilde_class = c;
    
}

void *hoa_out_tilde_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_out_tilde *x = NULL;
    
    x = (t_hoa_out_tilde *)eobj_new(hoa_out_tilde_class);
	if(x)
	{
        eobj_dspsetup(x, 0, 0);
        x->f_extra = 0;
        x->f_signal = NULL;
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

void hoa_out_tilde_free(t_hoa_out_tilde *x)
{
    eobj_dspfree(x);
}

t_hoa_err hoa_getinfos(t_hoa_out_tilde* x, t_hoa_boxinfos* boxinfos)
{
    boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_out_tilde_dsp(t_hoa_out_tilde *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(x->f_signal)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_out_tilde_perform, 0, NULL);
    
}

void hoa_out_tilde_perform(t_hoa_out_tilde *x, t_object *dsp, float **inps, long ni, float **outs, long no, long sf, long f,void *up)
{
    cblas_saxpy(sf, 1.f, inps[0], 1, x->f_signal, 1);
}





