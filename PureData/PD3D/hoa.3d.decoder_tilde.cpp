/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Hoa3D.pd.h"

typedef struct _hoa_decoder_3D
{
    t_edspobj               f_ob;
    Hoa3D::Decoder*         f_decoder;
    t_float*                f_ins;
    t_float*                f_outs;
    
    double                  f_angles_of_channels[MAX_CHANNELS * 2];
    double                  f_offset[2];
    long                    f_pinna;
    long                    f_number_of_angles;
} t_hoa_decoder_3D;

void *hoa_decoder_3D_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_3D_free(t_hoa_decoder_3D *x);

void hoa_decoder_3D_dsp(t_hoa_decoder_3D *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_decoder_3D_perform64(t_hoa_decoder_3D *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam);

t_pd_err angles_set(t_hoa_decoder_3D *x, void *attr, long argc, t_atom *argv);
t_pd_err offset_set(t_hoa_decoder_3D *x, void *attr, long argc, t_atom *argv);

t_eclass *hoa_decoder_3D_class;

t_hoa_err hoa_getinfos(t_hoa_decoder_3D* x, t_hoa_boxinfos* boxinfos);


extern "C" void setup_hoa0x2e3d0x2edecoder_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.3d.decoder~", (method)hoa_decoder_3D_new, (method)hoa_decoder_3D_free, (short)sizeof(t_hoa_decoder_3D), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
    hoa_initclass(c, (method)hoa_getinfos);
    eclass_addmethod(c, (method)hoa_decoder_3D_dsp,           "dsp",          A_CANT,  0);
    
    CLASS_ATTR_DOUBLE_VARSIZE	(c, "angles",0, t_hoa_decoder_3D, f_angles_of_channels, f_number_of_angles, MAX_CHANNELS*2);
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_set);
	CLASS_ATTR_ORDER			(c, "angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles of Loudspeakers");
    
    CLASS_ATTR_DOUBLE_ARRAY     (c, "offset", 0, t_hoa_decoder_3D, f_offset, 2);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "offset", 0, "Offset of Channels");
	CLASS_ATTR_ACCESSORS		(c, "offset", NULL, offset_set);
    CLASS_ATTR_DEFAULT          (c, "offset", 0, "0 0");
    CLASS_ATTR_ORDER            (c, "offset", 0, "3");
    CLASS_ATTR_SAVE             (c, "offset", 0);
    
    eclass_register(CLASS_OBJ, c);
    hoa_decoder_3D_class = c;
}

void *hoa_decoder_3D_new(t_symbol *s, long argc, t_atom *argv)
{
    
    t_hoa_decoder_3D *x = NULL;
    t_binbuf *d;
	int	order = 1;
    int number_of_channels = 4;
   
    if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;

    x = (t_hoa_decoder_3D *)eobj_new(hoa_decoder_3D_class);
    if (x)
	{
        if(argc && argv && atom_gettype(argv) == A_LONG)
            order = atom_getlong(argv);
        if(order < 1)
            order = 1;
        
        if(argc >= 1 && atom_gettype(argv+1) == A_LONG)
        {
            number_of_channels = atom_getint(argv+1);
            if(number_of_channels < 1)
                number_of_channels = 1;
        }
        
        x->f_decoder    = new Hoa3D::Decoder(order, number_of_channels);
        x->f_number_of_angles = x->f_decoder->getNumberOfChannels() * 2;
    
        eobj_dspsetup(x, x->f_decoder->getNumberOfHarmonics(), x->f_decoder->getNumberOfChannels());
        x->f_ins = new t_float[x->f_decoder->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs= new t_float[MAX_CHANNELS * SYS_MAXBLKSIZE];
        
        ebox_attrprocess_viabinbuf(x, d);
	}
    
    return (x);
}

t_hoa_err hoa_getinfos(t_hoa_decoder_3D* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_decoder->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_decoder->getNumberOfChannels();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_PLANEWAVES;
	return HOA_ERR_NONE;
}

void hoa_decoder_3D_dsp(t_hoa_decoder_3D *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_decoder_3D_perform64, 0, NULL);
}

void hoa_decoder_3D_perform64(t_hoa_decoder_3D *x, t_object *dsp64, float **ins, long numins, float **outs, long numouts, long sampleframes, long flags, void *userparam)
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

t_pd_err angles_set(t_hoa_decoder_3D *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        int dspState = canvas_suspend_dsp();
        for(int i = 1, j = 0; i < x->f_decoder->getNumberOfChannels() * 2 && i < argc; i+= 2, j++)
        {
            if(atom_gettype(argv+i-1) == A_FLOAT && atom_gettype(argv+i) == A_FLOAT)
                x->f_decoder->setChannelPosition(j, atom_getfloat(argv+i-1) / 360. * HOA_2PI, atom_getfloat(argv+i) / 360. * HOA_2PI);
        }
        canvas_resume_dsp(dspState);
    }
    return 0;
}

t_pd_err offset_set(t_hoa_decoder_3D *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        double azimuth, elevation;
        if(atom_gettype(argv) == A_FLOAT)
           azimuth = wrap_twopi(atom_getfloat(argv) / 360. * HOA_2PI);
        else
            azimuth = x->f_decoder->getChannelsAzimuthOffset();
        
        if(argc > 1 && atom_gettype(argv+1) == A_FLOAT)
            elevation = wrap_twopi(atom_getfloat(argv+1) / 360. * HOA_2PI);
        else
            elevation = x->f_decoder->getChannelsElevationOffset();
        
        x->f_decoder->setChannelsOffset(azimuth, elevation);
    }
    return 0;
}

void hoa_decoder_3D_free(t_hoa_decoder_3D *x)
{
    eobj_dspfree(x);
	delete x->f_decoder;
    delete [] x->f_ins;
    delete [] x->f_outs;
}

