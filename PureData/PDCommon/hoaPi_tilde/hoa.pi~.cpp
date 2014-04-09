/*
 // Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "../HoaCommon.pd.h"

typedef struct _hoa_pi_tilde
{	
	t_edspobj   p_ob;
	double      p_value;
    double      p_phase;
} t_hoa_pi_tilde;

void hoa_pi_tilde_float(t_hoa_pi_tilde *x, float n);

void hoa_pi_tilde_dsp(t_hoa_pi_tilde *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_pi_tilde_perform(t_hoa_pi_tilde *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_pi_tilde_perform_phase(t_hoa_pi_tilde *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_pi_tilde_perform_offset(t_hoa_pi_tilde *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

void *hoa_pi_tilde_new(t_symbol *s, int argc, t_atom *argv);

t_eclass *hoa_pi_tilde_class;

t_hoa_err hoa_getinfos(t_hoa_pi_tilde* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2epi_tilde(void)
{
    t_eclass* c;
    c = eclass_new("hoa.pi~", (method)hoa_pi_tilde_new, (method)NULL, sizeof(t_hoa_pi_tilde), CLASS_NOINLET, A_GIMME, 0);
    
    eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
   
    eclass_addmethod(c, (method)hoa_pi_tilde_float,    "float",    A_FLOAT, 0);
    eclass_addmethod(c, (method)hoa_pi_tilde_dsp,      "dsp",      A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_pi_tilde_class = c;
}

void *hoa_pi_tilde_new(t_symbol *s, int argc, t_atom *argv)
{
    t_hoa_pi_tilde *x = (t_hoa_pi_tilde *)eobj_new(hoa_pi_tilde_class);
	x->p_value = 1.;
    x->p_phase = 1;
    x->p_value = atom_getfloat(argv);
    eobj_dspsetup(x, 2, 1);
    
	return(x);
}

t_hoa_err hoa_getinfos(t_hoa_pi_tilde* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_STANDARD;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_pi_tilde_float(t_hoa_pi_tilde *x, float n)
{
    if(eobj_getproxy(x))
    {
        x->p_phase = n;
    }
    else
    {
        x->p_value = n;
        x->p_phase = 1;
    }
}

void hoa_pi_tilde_dsp(t_hoa_pi_tilde *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(count[0])
		object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_pi_tilde_perform, 0, NULL);
    else if(count[1])
		object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_pi_tilde_perform_phase, 0, NULL);
    else
		object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_pi_tilde_perform_offset, 0, NULL);

}

void hoa_pi_tilde_perform(t_hoa_pi_tilde *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->p_value = ins[0][i];
        outs[0][i] = HOA_PI * ins[0][i];
    }
}

void hoa_pi_tilde_perform_phase(t_hoa_pi_tilde *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
        outs[0][i] = HOA_PI * x->p_value * ins[1][i];
}

void hoa_pi_tilde_perform_offset(t_hoa_pi_tilde *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
        outs[0][i] = HOA_PI * x->p_value * x->p_phase;
}


