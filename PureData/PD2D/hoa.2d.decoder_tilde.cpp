/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa2D.pd.h"

typedef struct _hoa_decoder
{
    t_edspobj               f_ob;
    Hoa2D::DecoderMulti*    f_decoder;
    t_float*                f_ins;
    t_float*                f_outs;
    
    double                  f_angles_of_channels[MAX_CHANNELS];
    double                  f_offset;
    long                    f_pinna;
    long                    f_number_of_channels;
} t_hoa_decoder;

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_free(t_hoa_decoder *x);

void hoa_decoder_dsp(t_hoa_decoder *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_decoder_perform64(t_hoa_decoder *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

t_pd_err angles_set(t_hoa_decoder *x, void *attr, long argc, t_atom *argv);
t_pd_err offset_set(t_hoa_decoder *x, void *attr, long argc, t_atom *argv);
t_pd_err pinna_set(t_hoa_decoder *x, void *attr, long argc, t_atom *argv);

t_eclass *hoa_decoder_class;
t_eclass *hoa_binaural_alias;

t_hoa_err hoa_getinfos(t_hoa_decoder* x, t_hoa_boxinfos* boxinfos);
void hoa_decoder_deprecated(t_hoa_decoder* x, t_symbol *s, long ac, t_atom* av);

extern "C" void setup_hoa0x2e2d0x2edecoder_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.2d.decoder~", (method)hoa_decoder_new, (method)hoa_decoder_free, (short)sizeof(t_hoa_decoder), 0L, A_GIMME, 0);
    class_addcreator((t_newmethod)hoa_decoder_new, gensym("hoa.decoder~"), A_GIMME, 0);
    
	eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)hoa_decoder_dsp,           "dsp",          A_CANT,  0);
    eclass_addmethod(c, (method)hoa_decoder_deprecated,    "pinnae",       A_GIMME, 0);
    eclass_addmethod(c, (method)hoa_decoder_deprecated,    "restitution",  A_GIMME, 0);
    
    CLASS_ATTR_DOUBLE_VARSIZE	(c, "angles",0, t_hoa_decoder, f_angles_of_channels, f_number_of_channels, MAX_CHANNELS);
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_set);
	CLASS_ATTR_ORDER			(c, "angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles of Loudspeakers");
    
    CLASS_ATTR_DOUBLE           (c, "offset", 0, t_hoa_decoder, f_offset);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "offset", 0, "Offset of Channels");
	CLASS_ATTR_ACCESSORS		(c, "offset", NULL, offset_set);
    CLASS_ATTR_DEFAULT          (c, "offset", 0, "0");
    CLASS_ATTR_ORDER            (c, "offset", 0, "3");
    CLASS_ATTR_SAVE             (c, "offset", 0);
    
    CLASS_ATTR_LONG				(c, "pinna", 0 , t_hoa_decoder, f_pinna);
    CLASS_ATTR_ACCESSORS		(c, "pinna", NULL, pinna_set);
	CLASS_ATTR_LABEL			(c, "pinna", 0, "Pinna Size");
    
    eclass_register(CLASS_OBJ, c);
    hoa_decoder_class = c;
}

void hoa_decoder_deprecated(t_hoa_decoder* x, t_symbol *s, long ac, t_atom* av)
{
    t_atom* argv;
    long argc;
    if(s && s == gensym("pinnae"))
    {
        object_error(x, "%s attribute @pinnae is deprecated, please use @pinna.", eobj_getclassname(x)->s_name);
        pinna_set(x, NULL, ac, av);
    }
    if(s && s == gensym("restitution"))
    {
        object_error(x, "%s attribute @restitution is deprecated. The projection restitution is now automatic for a stereo decoding and the panning restitution is used for the other irregular decoding.", eobj_getclassname(x)->s_name);
    }
    atoms_get_attribute(ac, av, gensym("@pinnae"), &argc, &argv);
    if(argc && argv)
    {
        object_error(x, "%s attribute @pinnae is deprecated, please use @pinna.", eobj_getclassname(x)->s_name);
        pinna_set(x, NULL, argc, argv);
        argc = 0;free(argv);argv = NULL;
        
    }
    if(atoms_has_attribute(ac, av, gensym("@restitution")))
    {
        object_error(x, "%s attribute @restitution is deprecated. The projection restitution is now automatic for a stereo decoding and the panning restitution is used for the other irregular decoding.", eobj_getclassname(x)->s_name);
    }
}

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
    
    t_hoa_decoder *x = NULL;
    t_binbuf *d;
	int	order = 1;
    int number_of_channels = 4;
   
    if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;

    x = (t_hoa_decoder *)eobj_new(hoa_decoder_class);
    if (x)
	{
        if(argc && argv && atom_gettype(argv) == A_LONG)
            order = atom_getlong(argv);
        if(order < 1)
            order = 1;
        
        x->f_decoder    = new Hoa2D::DecoderMulti(order);
        if(argc >= 0 && atom_gettype(argv+1) == A_SYM)
        {
            if(atom_getsym(argv+1) == gensym("ambisonic"))
                x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Regular);
            else if(atom_getsym(argv+1) == gensym("binaural"))
                x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Binaural);
            else if(atom_getsym(argv+1) == gensym("irregular"))
                x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Irregular);
        }
        else if(argc >= 0 &&  atom_gettype(argv+1) == A_LONG)
        {
            if(atom_getlong(argv+1) == 0)
                x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Regular);
            else if(atom_getlong(argv+1) == 1)
                x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Binaural);
            else if(atom_getlong(argv+1) == 2)
                x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Irregular);
        }
        if(argc >= 1 && atom_gettype(argv+2) == A_LONG)
        {
            number_of_channels = atom_getint(argv+2);
            if(number_of_channels < 1)
                number_of_channels = 1;
            if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Regular)
            {
                if(number_of_channels < x->f_decoder->getNumberOfHarmonics())
                    x->f_decoder->setNumberOfChannels(x->f_decoder->getNumberOfHarmonics());
                else
                    x->f_decoder->setNumberOfChannels(number_of_channels);
            }
            else if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Irregular)
                x->f_decoder->setNumberOfChannels(number_of_channels);
                
        }
        
        hoa_decoder_deprecated(x, NULL, argc, argv);
        
        x->f_number_of_channels = x->f_decoder->getNumberOfChannels();
    
        eobj_dspsetup(x, x->f_decoder->getNumberOfHarmonics(), x->f_decoder->getNumberOfChannels());
        x->f_ins = new t_float[x->f_decoder->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs= new t_float[MAX_CHANNELS * SYS_MAXBLKSIZE];
        
        ebox_attrprocess_viabinbuf(x, d);
	}
    
    return (x);
}

t_hoa_err hoa_getinfos(t_hoa_decoder* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_decoder->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_decoder->getNumberOfChannels();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_PLANEWAVES;
	return HOA_ERR_NONE;
}

void hoa_decoder_dsp(t_hoa_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_decoder->setSampleRate(samplerate);
    
    object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_decoder_perform64, 0, NULL);
}

void hoa_decoder_perform64(t_hoa_decoder *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_scopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_decoder->process(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_scopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
    
}

t_pd_err angles_set(t_hoa_decoder *x, void *attr, long argc, t_atom *argv)
{
    double *angles;
    if(argc && argv && x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Irregular)
    {
        angles = new double[x->f_decoder->getNumberOfChannels()];
        if(angles)
        {
            int dspState = canvas_suspend_dsp();
            for(int i = 0; i < x->f_decoder->getNumberOfChannels(); i++)
            {
                if(i < argc && (atom_gettype(argv+i) == A_FLOAT || atom_gettype(argv+i) == A_LONG))
                    angles[i] = atom_getfloat(argv+i) / 360. * HOA_2PI;
                else
                    angles[i] = x->f_decoder->getChannelAzimuth(i);
            }
            
            x->f_decoder->setChannelsAzimuth(angles);
            free(angles);
            canvas_resume_dsp(dspState);
        }
    }
    
    return 0;
}

t_pd_err pinna_set(t_hoa_decoder *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == gensym("small") && x->f_decoder->getPinnaSize() != Hoa2D::DecoderBinaural::Small)
        {
            int dspState;
            if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Binaural)
                dspState = canvas_suspend_dsp();
            x->f_decoder->setPinnaSize(Hoa2D::DecoderBinaural::Small);
            if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Binaural)
                canvas_resume_dsp(dspState);
		}
        else if(atom_getsym(argv) == gensym("large") && x->f_decoder->getPinnaSize() != Hoa2D::DecoderBinaural::Large)
        {
            int dspState;
            if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Binaural)
                dspState = canvas_suspend_dsp();
            x->f_decoder->setPinnaSize(Hoa2D::DecoderBinaural::Large);
            if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Binaural)
                canvas_resume_dsp(dspState);
        }
    }
    return 0;
}

t_pd_err offset_set(t_hoa_decoder *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        double offset = wrap_twopi(atom_getfloat(argv) / 360. * HOA_2PI);
        if(offset != x->f_decoder->getChannelsOffset())
        {
            int dspState;
            if(x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Binaural)
                dspState = canvas_suspend_dsp();
            x->f_decoder->setChannelsOffset(offset);
            if(x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Binaural)
                canvas_resume_dsp(dspState);
        }
    }
    return 0;
}

void hoa_decoder_free(t_hoa_decoder *x)
{
    eobj_dspfree(x);
	delete x->f_decoder;
    delete [] x->f_ins;
    delete [] x->f_outs;
}
