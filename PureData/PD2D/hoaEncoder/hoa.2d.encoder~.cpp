/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.pd.h"

typedef struct _hoa_encoder
{
    t_edspobj   f_ob;
    Encoder*    f_encoder;
} t_hoa_encoder;

void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_encoder_free(t_hoa_encoder *x);

void hoa_encoder_dsp(t_hoa_encoder *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_encoder_perform(t_hoa_encoder *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_encoder_class;

t_hoa_err hoa_getinfos(t_hoa_encoder* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2e2d0x2eencoder_tilde(void)
{
    t_eclass *c;
    c = eclass_new("hoa.2d.encoder~", (method)hoa_encoder_new,(method)hoa_encoder_free, sizeof(t_hoa_encoder), 0L, A_GIMME, 0);

    eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)hoa_encoder_dsp,     "dsp",		A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_encoder_class = c;
}

void *hoa_encoder_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_encoder *x = NULL;
	int	order = 1;
    
    x = (t_hoa_encoder *)eobj_new(hoa_encoder_class);
	if (x)
	{
        if(atom_gettype(argv) == A_LONG)
            order = atom_getlong(argv);
        if(order < 1)
            order = 1;
        
		x->f_encoder = new Encoder(order);
        eobj_dspsetup(x, 2, x->f_encoder->getNumberOfHarmonics());
        
        x->f_ob.d_misc = E_NO_INPLACE_REVERSED;
	}
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_encoder* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = x->f_encoder->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_encoder_dsp(t_hoa_encoder *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_encoder_perform, 0, NULL);
}

void hoa_encoder_perform(t_hoa_encoder *x, t_object *dsp, float **ins, long nins, float **outs, long nouts, long sampleframes, long f,void *up)
{
    for(int i = 0; i < sampleframes; i++)
    {
        x->f_encoder->setAzimuth(ins[1][i]);
        //x->f_encoder->process(ins[0][i], outs[0] + numouts * i);
    }
}

void hoa_encoder_free(t_hoa_encoder *x)
{
	eobj_dspfree(x);
	delete x->f_encoder;
}
