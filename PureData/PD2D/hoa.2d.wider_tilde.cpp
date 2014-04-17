/*
 // Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "Hoa2D.pd.h"

typedef struct _hoa_wider
{
    t_edspobj       f_ob;
    t_float*        f_ins;
    t_float*        f_outs;
    Hoa2D::Wider*   f_wider;
    
} t_hoa_wider;

void *hoa_wider_new(t_symbol *s, long argc, t_atom *argv);
void hoa_wider_free(t_hoa_wider *x);
void hoa_wider_float(t_hoa_wider *x, float f);

void hoa_wider_dsp(t_hoa_wider *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_wider_perform(t_hoa_wider *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_wider_perform_offset(t_hoa_wider *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_eclass *hoa_wider_class;

t_hoa_err hoa_getinfos(t_hoa_wider* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2e2d0x2ewider_tilde(void)
{
    t_eclass* c;
    c = eclass_new("hoa.2d.wider~", (method)hoa_wider_new, (method)hoa_wider_free, (short)sizeof(t_hoa_wider), 0, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_wider_new, gensym("hoa.wider~"), A_GIMME);
    
	eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
	eclass_addmethod(c, (method)hoa_wider_dsp,       "dsp",      A_CANT, 0);
    eclass_addmethod(c, (method)hoa_wider_float,    "float",    A_FLOAT, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_wider_class = c;
}

void *hoa_wider_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_wider *x = NULL;
	int	order = 1;
    x = (t_hoa_wider *)eobj_new(hoa_wider_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(order < 1)
            order = 1;
        
		x->f_wider = new Hoa2D::Wider(order);
		
        eobj_dspsetup(x, x->f_wider->getNumberOfHarmonics() + 1, x->f_wider->getNumberOfHarmonics());
        
		x->f_ins = new t_float[x->f_wider->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new t_float[x->f_wider->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}
    
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_wider* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_wider->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_wider->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_wider_float(t_hoa_wider *x, float f)
{
    x->f_wider->setWideningValue(f);
}

void hoa_wider_dsp(t_hoa_wider *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    if(count[x->f_wider->getNumberOfHarmonics()])
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_wider_perform, 0, NULL);
    else
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_wider_perform_offset, 0, NULL);
}

void hoa_wider_perform(t_hoa_wider *x, t_object *dsp, float **ins, long numins, float **outs, long numouts, long sampleframes, long f,void *up)
{
	for(int i = 0; i < numins - 1; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numins - 1);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_wider->setWideningValue(ins[numins-1][i]);
        x->f_wider->process(x->f_ins + (numins - 1) * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_wider_perform_offset(t_hoa_wider *x, t_object *dsp, float **ins, long numins, float **outs, long numouts, long sampleframes, long f,void *up)
{
	for(int i = 0; i < numins - 1; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numins - 1);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_wider->process(x->f_ins + (numins - 1) * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_wider_free(t_hoa_wider *x)
{
    eobj_dspfree(x);
	delete x->f_wider;
    delete [] x->f_ins;
    delete [] x->f_outs;
}
