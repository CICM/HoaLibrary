/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

/**
 @file      hoa.2d.optim~.cpp
 @name      hoa.2d.optim~
 @realname  hoa.2d.optim~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A 2d ambisonic signal optimization external.
 
 @description
 <o>hoa.2d.optim~</o> weights the circular harmonics signals depending on the ambisonic optimization. It can be <b>basic</b> for no optimization, <b>maxRe</b> or <b>inPhase</b>.
 
 @discussion
 <o>hoa.2d.optim~</o> weights the circular harmonics signals depending on the ambisonic optimization. It can be <b>basic</b> for no optimization, <b>maxRe</b> or <b>inPhase</b>.
 
 @category ambisonics, hoa objects, audio, msp
 
 @seealso hoa.2d.decoder~, hoa.2d.map~, hoa.2d.scope~, hoa.2d.meter~, hoa.2d.wider~
 */

#include "Hoa2D.max.h"

typedef struct _hoa_optim 
{
	t_pxobject              f_ob;
    double*                 f_ins;
    double*                 f_outs;
    Hoa2D::Optim*           f_optim;
    
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
    
#ifdef HOA_PACKED_LIB
int hoa_2d_optim_main(void)
#else
int C74_EXPORT main(void)
#endif
{	

	t_class *c;
	
	c = class_new("hoa.2d.optim~", (method)hoa_optim_new, (method)hoa_optim_free, (long)sizeof(t_hoa_optim), 0L, A_GIMME, 0);
	class_setname((char *)"hoa.2d.optim~", (char *)"hoa.2d.optim~");
    
    hoa_initclass(c, (method)hoa_getinfos);
	
	// @method signal @digest Array of circular harmonic signals to be optimized.
	// @description Array of circular harmonic signals to be optimized.
	class_addmethod(c, (method)hoa_optim_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_optim_assist,    "assist",	A_CANT, 0);
	
	// @method basic @digest Set the optimization mode to <b>basic</b>, does not apply any optimization.
	// @description Set the optimization mode to <b>basic</b>. This is particulary suitable when the listener is ideally placed at the center of the loudspeaker arrangement, or for diffused soundfields.
	class_addmethod(c, (method)hoa_optim_basic,     "basic",	A_NOTHING, 0);
	
	// @method maxRe @digest Set the optimization mode to <b>maxRe</b>.
	// @description Set the optimization mode to <b>maxRe</b>. This is particulary suitable when the audience is confined at the center of the restitution area.
    class_addmethod(c, (method)hoa_optim_maxre,     "maxRe",	A_NOTHING, 0);
	
	// @method maxRe @digest Set the optimization mode to <b>maxRe</b>.
	// @description Set the optimization mode to <b>maxRe</b>. This is particulary suitable when the audience covers all of the restitution area.
    class_addmethod(c, (method)hoa_optim_inphase,   "inPhase",	A_NOTHING, 0);
    
	class_dspinit(c);
	class_register(CLASS_BOX, c);
    class_alias(c, gensym("hoa.optim~"));
	hoa_optim_class = c;
    
	return 0;
}

void *hoa_optim_new(t_symbol *s, long argc, t_atom *argv)
{
	// @arg 0 @name ambisonic-order @optional 0 @type int @digest The ambisonic order of decomposition
	// @description First argument is the ambisonic order of decomposition.
	
	// @arg 1 @name optimization-mode @optional 1 @type symbol @digest The optimization mode.
	// @description The optimization mode can be <b>basic</b> for no optimization (default), <b>maxRe</b> or <b>inPhase</b>.
	
	t_hoa_optim *x = NULL;
	int	order = 1;
    x = (t_hoa_optim *)object_alloc(hoa_optim_class);
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
        
		dsp_setup((t_pxobject *)x, x->f_optim->getNumberOfHarmonics());
		for (int i = 0; i < x->f_optim->getNumberOfHarmonics(); i++)
			outlet_new(x, "signal");
        
        x->f_ins = new double[x->f_optim->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new double[x->f_optim->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
	}

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

void hoa_optim_dsp64(t_hoa_optim *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, hoa_optim_perform64, 0, NULL);
}

void hoa_optim_perform64(t_hoa_optim *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_optim->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_optim_assist(t_hoa_optim *x, void *b, long m, long a, char *s)
{
	sprintf(s,"(Signal) %s", x->f_optim->getHarmonicName(a).c_str());
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
	dsp_free((t_pxobject *)x);
	delete x->f_optim;
    delete [] x->f_ins;
    delete [] x->f_outs;
}

