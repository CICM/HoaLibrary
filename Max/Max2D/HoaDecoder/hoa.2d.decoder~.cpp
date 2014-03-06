/*
// Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.max.h"

typedef struct _hoa_decoder 
{
	t_pxobject              f_ob;
	double*                 f_ins;
    double*                 f_outs;
    
    Hoa2D::DecoderRegular*      f_decoder_regular;
    Hoa2D::DecoderIrregular*    f_decoder_irregular;
    Hoa2D::DecoderBinaural*     f_decoder_binaural;
    
    t_symbol*               f_mode;
    t_atom_long             f_number_of_channels;
    t_atom_long             f_send_config;
    double*                 f_angles_of_channels;
    
} t_hoa_decoder;

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_free(t_hoa_decoder *x);
void hoa_decoder_assist(t_hoa_decoder *x, void *b, long m, long a, char *s);

void hoa_decoder_dsp64(t_hoa_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_decoder_perform64(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_hoa_err hoa_getinfos(t_hoa_decoder* x, t_hoa_boxinfos* boxinfos);

t_max_err mode_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);

t_class *hoa_decoder_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.2d.decoder~", (method)hoa_decoder_new, (method)hoa_decoder_free, (long)sizeof(t_hoa_decoder), 0L, A_GIMME, 0);
    class_alias(c, gensym("hoa.decoder~"));
	
    hoa_initclass(c, (method)hoa_getinfos);
	class_addmethod(c, (method)hoa_decoder_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_decoder_assist,		"assist",	A_CANT, 0);
    
    CLASS_ATTR_SYM              (c, "mode", 0, t_hoa_decoder, f_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c, "mode", 0, "ambisonic binaural irregular");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, mode_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    CLASS_ATTR_SAVE             (c, "mode", 1);
    
    CLASS_ATTR_LONG             (c, "autoconnect", 0, t_hoa_decoder, f_send_config);
	CLASS_ATTR_CATEGORY			(c, "autoconnect", 0, "Behavior");
	CLASS_ATTR_STYLE_LABEL      (c, "autoconnect", 0, "onoff", "Auto connection");
    CLASS_ATTR_ORDER            (c, "autoconnect", 0, "2");
    CLASS_ATTR_SAVE             (c, "autoconnect", 1);
    
    CLASS_ATTR_LONG             (c, "channels", 0, t_hoa_decoder, f_number_of_channels);
	CLASS_ATTR_CATEGORY			(c, "channels", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_ACCESSORS		(c, "channels", NULL, channel_set);
    CLASS_ATTR_ORDER            (c, "channels", 0, "1");
    CLASS_ATTR_SAVE             (c, "channels", 1);
    
    CLASS_ATTR_DOUBLE_VARSIZE   (c, "angles", 0, t_hoa_decoder, f_angles_of_channels, f_number_of_channels, MAX_CHANNELS);
	CLASS_ATTR_CATEGORY			(c, "angles", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "angles", 0, "Angles of Channels");
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_set);
    CLASS_ATTR_ORDER            (c, "angles", 0, "2");
	CLASS_ATTR_SAVE             (c, "angles", 1);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_decoder_class = c;
    
	return 0;
}

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_decoder *x = NULL;
	int	order = 1;
    int numberOfLoudspeakers = 10;
    x = (t_hoa_decoder *)object_alloc(hoa_decoder_class);
	if (x)
	{		
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(order < 1)
            order = 1;
        if(atom_gettype(argv+1) == A_LONG)
			numberOfLoudspeakers = atom_getlong(argv+1);
        if(numberOfLoudspeakers < 1)
            numberOfLoudspeakers = 1;
		
		x->f_decoder_regular = new Hoa2D::DecoderRegular(order, numberOfLoudspeakers);
		
		dsp_setup((t_pxobject *)x, x->f_decoder_regular->getNumberOfHarmonics());
		for (int i = 0; i < x->f_decoder_regular->getNumberOfChannels(); i++)
			outlet_new(x, "signal");
        
		x->f_ins = new double[x->f_decoder_regular->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs = new double[x->f_decoder_regular->getNumberOfChannels() * SYS_MAXBLKSIZE];
        x->f_angles_of_channels = new double[MAX_CHANNELS];
	}

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_decoder* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_decoder_regular->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_decoder_regular->getNumberOfChannels();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_PLANEWAVES;
	return HOA_ERR_NONE;
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
        x->f_decoder_regular->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_decoder_assist(t_hoa_decoder *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_decoder_regular->getHarmonicsName(a).c_str());
    else
        sprintf(s,"(Signal) %s", x->f_decoder_regular->getChannelName(a).c_str());
}


void hoa_decoder_free(t_hoa_decoder *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_decoder_regular;
    delete [] x->f_ins;
	delete [] x->f_outs;
    delete [] x->f_angles_of_channels;
}

t_max_err mode_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    return 0;
}

t_max_err channel_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    return 0;
}

t_max_err angles_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    return 0;
}

