/*
 // Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "../HoaCommon.pd.h"

typedef struct _hoa_converter_tilde
{	
	t_edspobj   p_ob;
	
} t_hoa_converter_tilde;

void hoa_converter_tilde_dsp(t_hoa_converter_tilde *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_converter_tilde_perform(t_hoa_converter_tilde *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);


void *hoa_converter_tilde_new(t_symbol *s, int argc, t_atom *argv);

t_eclass *hoa_converter_tilde_class;

t_hoa_err hoa_getinfos(t_hoa_converter_tilde* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2econverter_tilde(void)
{
    t_eclass* c;
    c = eclass_new("hoa.converter~", (method)hoa_converter_tilde_new, (method)NULL, sizeof(t_hoa_converter_tilde), CLASS_NOINLET, A_GIMME, 0);
    
    eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
   
    eclass_addmethod(c, (method)hoa_converter_tilde_dsp,      "dsp",      A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_converter_tilde_class = c;
}

void *hoa_converter_tilde_new(t_symbol *s, int argc, t_atom *argv)
{
    t_hoa_converter_tilde *x = NULL;
    
    if(argc < 3 || atom_gettype(argv) != A_LONG || atom_gettype(argv+1) != A_SYM || atom_gettype(argv+2) != A_SYM)
    {
        error("hoa.converter~ need 4 arguments.");
        return NULL;
    }
    
    x = (t_hoa_converter_tilde *)eobj_new(hoa_converter_tilde_class);
	
    
    eobj_dspsetup(x, 2, 1);
    
	return(x);
}

t_hoa_err hoa_getinfos(t_hoa_converter_tilde* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_STANDARD;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_converter_tilde_dsp(t_hoa_converter_tilde *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_converter_tilde_perform, 0, NULL);
}

void hoa_converter_tilde_perform(t_hoa_converter_tilde *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    ;
}
