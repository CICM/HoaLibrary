/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.max.h"

typedef struct _hoa_projector 
{
	t_pxobject              f_ob;
	double*                 f_ins;
    double*                 f_outs;
    Hoa2D::Projector*       f_projector;
    
} t_hoa_projector;

void *hoa_projector_new(t_symbol *s, long argc, t_atom *argv);
void hoa_projector_free(t_hoa_projector *x);
void hoa_projector_assist(t_hoa_projector *x, void *b, long m, long a, char *s);

void hoa_projector_dsp64(t_hoa_projector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_projector_perform64(t_hoa_projector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_hoa_err hoa_getinfos(t_hoa_projector* x, t_hoa_boxinfos* boxinfos);

t_class *hoa_projector_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.2d.projector~", (method)hoa_projector_new, (method)hoa_projector_free, (long)sizeof(t_hoa_projector), 0L, A_GIMME, 0);
    class_alias(c, gensym("hoa.projector~"));
	
    hoa_initclass(c, (method)hoa_getinfos);
	class_addmethod(c, (method)hoa_projector_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_projector_assist,    "assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_projector_class = c;
    
	return 0;
}

void *hoa_projector_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_projector *x = NULL;
	int	order = 1;
    int numberOfLoudspeakers = 4;
    x = (t_hoa_projector *)object_alloc(hoa_projector_class);
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
		
		dsp_setup((t_pxobject *)x, x->f_projector->getNumberOfHarmonics());
		for (int i = 0; i < x->f_projector->getNumberOfChannels(); i++)
			outlet_new(x, "signal");
        
		x->f_ins = new double[x->f_projector->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new double[x->f_projector->getNumberOfChannels() * SYS_MAXBLKSIZE];
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

void hoa_projector_dsp64(t_hoa_projector *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, hoa_projector_perform64, 0, NULL);
}

void hoa_projector_perform64(t_hoa_projector *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_projector->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_projector_assist(t_hoa_projector *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_projector->getHarmonicsName(a).c_str());
    else
        sprintf(s,"(Signal) %s", x->f_projector->getChannelName(a).c_str());
}


void hoa_projector_free(t_hoa_projector *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_projector;
    delete [] x->f_ins;
	delete [] x->f_outs;
}

