/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../../Sources/Hoa3D/Hoa3D.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

typedef struct _hoa_decoder 
{
	t_pxobject          f_ob;
	double*             f_ins;
    double*             f_outs;
	Hoa3D::Decoder*     f_decoder;
} t_hoa_decoder;

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_free(t_hoa_decoder *x);
void hoa_decoder_assist(t_hoa_decoder *x, void *b, long m, long a, char *s);

void hoa_decoder_dsp64(t_hoa_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_decoder_perform64(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_decoder_setLoudspeakers(t_hoa_decoder *x, t_symbol* s, long argc, t_atom* argv);
void hoa_decoder_infos(t_hoa_decoder *x);

void *hoa_decoder_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.decoder3D~", (method)hoa_decoder_new, (method)hoa_decoder_free, (long)sizeof(t_hoa_decoder), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)hoa_decoder_dsp64,             "dsp64",      A_CANT, 0);
	class_addmethod(c, (method)hoa_decoder_assist,            "assist",     A_CANT, 0);
    class_addmethod(c, (method)hoa_decoder_setLoudspeakers,   "lscoord",    A_GIMME, 0);
    class_addmethod(c, (method)hoa_decoder_infos,             "infos",      A_GIMME, 0);
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	hoa_decoder_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_decoder *x = NULL;
	int order = 1;
    int number_of_loudspeakers = 4;
    
    x = (t_hoa_decoder *)object_alloc((t_class*)hoa_decoder_class);
	if(x)
	{
		if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
			order	= atom_getfloat(argv);
        if(atom_gettype(argv+1) == A_LONG || atom_gettype(argv+1) == A_FLOAT)
			number_of_loudspeakers	= atom_getfloat(argv+1);
		
        x->f_decoder	= new Hoa3D::Decoder(order, number_of_loudspeakers);
        
		dsp_setup((t_pxobject *)x, x->f_decoder->getNumberOfInputs());
		for (int i = 0; i < x->f_decoder->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
		
		x->f_ins    =  new double[x->f_decoder->getNumberOfInputs() * SYS_MAXBLKSIZE];
        x->f_outs   =  new double[x->f_decoder->getNumberOfOutputs() * SYS_MAXBLKSIZE];
	}
    
	return (x);
}

void hoa_decoder_dsp64(t_hoa_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, hoa_decoder_perform64, 0, NULL);
}

void hoa_decoder_perform64(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_decoder->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_decoder_assist(t_hoa_decoder *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(Signal) %s",x->f_decoder->getHarmonicsName(a).c_str());
	else
	{
		sprintf(s,"(Signal) channel %ld", a);
	}
}

void hoa_decoder_free(t_hoa_decoder *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_decoder;
    delete [] x->f_ins;
    delete [] x->f_outs;
}

void hoa_decoder_setLoudspeakers(t_hoa_decoder *x, t_symbol* s, long argc, t_atom* argv)
{
    if(argc > 2 && argv && atom_gettype(argv) == A_LONG && atom_gettype(argv+1) == A_FLOAT && atom_gettype(argv+2) == A_FLOAT)
    {
        x->f_decoder->setLoudspeakerPosition(atom_getlong(argv), atom_getfloat(argv+1), atom_getfloat(argv+2));
    }
}


void hoa_decoder_infos(t_hoa_decoder *x)
{
    object_post((t_object *)x, "Number Of Ls : %ld", x->f_decoder->getNumberOfOutputs());
    for (int i = 0; i < x->f_decoder->getNumberOfOutputs(); i++)
        object_post((t_object *)x, "Ls  %i : %f %f", i, x->f_decoder->getLoudspeakerAzimuth(i), x->f_decoder->getLoudspeakerElevation(i));
}

