/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa3D.max.h"

typedef struct _hoa_optim 
{
	t_pxobject              f_ob;
    double*                 f_signals;
    Hoa3D::Optim*           f_optim;
    
} t_hoa_optim;


void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv);
void hoa_optim_free(t_hoa_optim *x);
void hoa_optim_assist(t_hoa_optim *x, void *b, long m, long a, char *s);

void hoa_optim_dsp64(t_hoa_optim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_optim_perform64(t_hoa_optim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_optim_basic(t_hoa_optim *x);
void hoa_optim_maxre(t_hoa_optim *x);
void hoa_optim_inphase(t_hoa_optim *x);

t_hoa_err hoa_getinfos(t_hoa_optim* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_optim_class;

int C74_EXPORT main(void)
{	

	t_class *c;
	
	c = class_new("hoa.3d.optim~", (method)hoa_optim_new, (method)hoa_optim_free, (long)sizeof(t_hoa_optim), 0L, A_GIMME, 0);
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	class_addmethod(c, (method)hoa_optim_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_optim_assist,    "assist",	A_CANT, 0);
    class_addmethod(c, (method)hoa_optim_basic,     "basic",	A_NOTHING, 0);
    class_addmethod(c, (method)hoa_optim_maxre,     "maxRe",	A_NOTHING, 0);
    class_addmethod(c, (method)hoa_optim_inphase,   "inPhase",	A_NOTHING, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	
	hoa_optim_class = c;
    hoa_print_credit();
	return 0;
}

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_optim *x = NULL;
	int	order = 1;
    x = (t_hoa_optim *)object_alloc(hoa_optim_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
        
        x->f_optim = new Hoa3D::Optim(order, Hoa3D::Optim::InPhase);
        
        if(argc > 1 && atom_gettype(argv+1) == A_SYM)
        {
            if(atom_getsym(argv+1) == gensym("maxRe"))
                x->f_optim->setMode(Hoa3D::Optim::MaxRe);
            else if(atom_getsym(argv+1) == gensym("basic"))
                x->f_optim->setMode(Hoa3D::Optim::Basic);
        }
		
		dsp_setup((t_pxobject *)x, x->f_optim->getNumberOfHarmonics());
		for (int i = 0; i < x->f_optim->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
        
        x->f_signals =  new double[x->f_optim->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_optim* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = boxinfos->autoconnect_outputs = x->f_optim->getNumberOfHarmonics();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	return HOA_ERR_NONE;
}

void hoa_optim_dsp64(t_hoa_optim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, hoa_optim_perform64, 0, NULL);
}

void hoa_optim_perform64(t_hoa_optim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numouts);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_optim->process(x->f_signals + numouts * i, x->f_signals + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_signals+i, numouts, outs[i], 1);
    }
}

void hoa_optim_assist(t_hoa_optim *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_optim->getHarmonicName(a).c_str());
}

void hoa_optim_basic(t_hoa_optim *x)
{
    if(x->f_optim->getMode() != Hoa3D::Optim::Basic)
        x->f_optim->setMode(Hoa3D::Optim::Basic);
}

void hoa_optim_maxre(t_hoa_optim *x)
{
    if(x->f_optim->getMode() != Hoa3D::Optim::MaxRe)
        x->f_optim->setMode(Hoa3D::Optim::MaxRe);
}

void hoa_optim_inphase(t_hoa_optim *x)
{
    if(x->f_optim->getMode() != Hoa3D::Optim::InPhase)
        x->f_optim->setMode(Hoa3D::Optim::InPhase);
}

void hoa_optim_free(t_hoa_optim *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_optim;
    delete [] x->f_signals;
}

