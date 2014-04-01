/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.pd.h"

typedef struct _hoa_optim
{
    t_edspobj         f_ob;
    t_float*          f_ins;
    t_float*          f_outs;
    Hoa2D::Optim*     f_optim;
} t_hoa_optim;

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv);
void hoa_optim_free(t_hoa_optim *x);

void hoa_optim_dsp(t_hoa_optim *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_optim_perform(t_hoa_optim *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_optim_basic(t_hoa_optim *x);
void hoa_optim_maxre(t_hoa_optim *x);
void hoa_optim_inphase(t_hoa_optim *x);

t_eclass *hoa_optim_class;

t_hoa_err hoa_getinfos(t_hoa_optim* x, t_hoa_boxinfos* boxinfos);

extern "C" void setup_hoa0x2e2d0x2eoptim_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.2d.optim~", (method)hoa_optim_new, (method)hoa_optim_free, (short)sizeof(t_hoa_optim), 0L, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_optim_new, gensym("hoa.optim~"), A_GIMME);
    
	eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
	eclass_addmethod(c, (method)hoa_optim_dsp,      "dsp",      A_CANT, 0);
    eclass_addmethod(c, (method)hoa_optim_basic,    "basic",	A_NULL, 0);
    eclass_addmethod(c, (method)hoa_optim_maxre,    "maxRe",	A_NULL, 0);
    eclass_addmethod(c, (method)hoa_optim_inphase,  "inPhase",	A_NULL, 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_optim_class = c;
}

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_optim *x = NULL;
    t_binbuf *d;
	int	order = 4;
    
    if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;
    
    x = (t_hoa_optim *)eobj_new(hoa_optim_class);
    if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
        if(order < 1)
            order = 1;
        
        x->f_optim = new Hoa2D::Optim(order, Hoa2D::Optim::InPhase);
		
        if(argc > 1 && atom_gettype(argv+1) == A_SYM)
        {
            if(atom_getsym(argv+1) == gensym("maxRe"))
                x->f_optim->setMode(Hoa2D::Optim::MaxRe);
            else if(atom_getsym(argv+1) == gensym("basic"))
                x->f_optim->setMode(Hoa2D::Optim::Basic);
        }
        
		eobj_dspsetup(x, x->f_optim->getNumberOfHarmonics(), x->f_optim->getNumberOfHarmonics());
        
        x->f_ins = new t_float[x->f_optim->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new t_float[x->f_optim->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}
    
    ebox_attrprocess_viabinbuf(x, d);
    
   	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_optim* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_optim->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_optim->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_optim_dsp(t_hoa_optim *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_optim_perform, 0, NULL);
}

void hoa_optim_perform(t_hoa_optim *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < numins; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_optim->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_optim_assist(t_hoa_optim *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_optim->getHarmonicsName(a).c_str());
}

void hoa_optim_basic(t_hoa_optim *x)
{
    if(x->f_optim->getMode() != Hoa2D::Optim::Basic)
        x->f_optim->setMode(Hoa2D::Optim::Basic);
}

void hoa_optim_maxre(t_hoa_optim *x)
{
    if(x->f_optim->getMode() != Hoa2D::Optim::MaxRe)
        x->f_optim->setMode(Hoa2D::Optim::MaxRe);
}

void hoa_optim_inphase(t_hoa_optim *x)
{
    if(x->f_optim->getMode() != Hoa2D::Optim::InPhase)
        x->f_optim->setMode(Hoa2D::Optim::InPhase);
}

void hoa_optim_free(t_hoa_optim *x)
{
	eobj_dspfree(x);
	delete x->f_optim;
    delete [] x->f_ins;
    delete [] x->f_outs;
}

