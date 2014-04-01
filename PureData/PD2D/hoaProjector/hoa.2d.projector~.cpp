/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.pd.h"

typedef struct _hoa_projector
{
    t_edspobj           f_ob;
    t_float*            f_ins;
    t_float*            f_outs;
    Hoa2D::Projector*   f_projector;
} t_hoa_projector;

void *hoa_projector_new(t_symbol *s, long argc, t_atom *argv);
void hoa_projector_free(t_hoa_projector *x);

void hoa_projector_dsp(t_hoa_projector *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_projector_perform(t_hoa_projector *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

t_eclass *hoa_projector_class;

t_hoa_err hoa_getinfos(t_hoa_projector* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2e2d0x2eprojector_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.2d.projector~", (method)hoa_projector_new, (method)hoa_projector_free, (short)sizeof(t_hoa_projector), 0L, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_projector_new, gensym("hoa.projector~"), A_GIMME);
    
	eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
	eclass_addmethod(c, (method)hoa_projector_dsp,     "dsp",      A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_projector_class = c;
}

void *hoa_projector_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_projector *x = NULL;
    int	order = 1;
    int numberOfLoudspeakers = 4;
    x = (t_hoa_projector *)eobj_new(hoa_projector_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(order < 1)
            order = 1;
        if(atom_gettype(argv+1) == A_LONG)
			numberOfLoudspeakers = atom_getlong(argv+1);
        if(numberOfLoudspeakers < order * 2 + 1)
            numberOfLoudspeakers = order * 2 + 1;
		
		x->f_projector = new Hoa2D::Projector(order, numberOfLoudspeakers);
		
        eobj_dspsetup(x, x->f_projector->getNumberOfHarmonics(), x->f_projector->getNumberOfChannels());
        
		x->f_ins = new t_float[x->f_projector->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new t_float[x->f_projector->getNumberOfChannels() * SYS_MAXBLKSIZE];
	}
    
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_projector* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_projector->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_projector->getNumberOfChannels();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_PLANEWAVES;
	return HOA_ERR_NONE;
}

void hoa_projector_dsp(t_hoa_projector *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_projector_perform, 0, NULL);
}

void hoa_projector_perform(t_hoa_projector *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_projector->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_projector_free(t_hoa_projector *x)
{
	eobj_dspfree(x);
	delete x->f_projector;
    delete [] x->f_ins;
	delete [] x->f_outs;
}
