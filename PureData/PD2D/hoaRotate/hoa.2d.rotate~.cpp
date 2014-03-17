/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.pd.h"

typedef struct _hoa_rotate
{
    t_edspobj       f_ob;
    t_float*        f_ins;
    t_float*        f_outs;
    Hoa2D::Rotate*  f_rotate;
} t_hoa_rotate;

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv);
void hoa_rotate_free(t_hoa_rotate *x);

void hoa_rotate_dsp(t_hoa_rotate *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_rotate_perform(t_hoa_rotate *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

t_eclass *hoa_rotate_class;

t_hoa_err hoa_getinfos(t_hoa_rotate* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2e2d0x2erotate_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.2d.rotate~",(method)hoa_rotate_new,(method)hoa_rotate_free, (short)sizeof(t_hoa_rotate), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
	eclass_addmethod(c, (method)hoa_rotate_dsp, "dsp", A_CANT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_rotate_class = c;
}

void *hoa_rotate_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_rotate *x = NULL;
	int	order = 4;
    
    x = (t_hoa_rotate *)eobj_new(hoa_rotate_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if (order < 1)
			order = 1;
		
		x->f_rotate = new Hoa2D::Rotate(order);
		
		eobj_dspsetup(x, x->f_rotate->getNumberOfHarmonics() + 1, x->f_rotate->getNumberOfHarmonics());
        
		x->f_ins = new t_float[x->f_rotate->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new t_float[x->f_rotate->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}
    
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_rotate* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_rotate->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_rotate->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_rotate_dsp(t_hoa_rotate *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_rotate_perform, 0, NULL);
}

void hoa_rotate_perform(t_hoa_rotate *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_rotate->setYaw(ins[numouts][i]);
        x->f_rotate->process(x->f_ins + numouts * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_rotate_free(t_hoa_rotate *x)
{
	eobj_dspfree(x);
	delete x->f_rotate;
    delete [] x->f_ins;
	delete [] x->f_outs;
}
