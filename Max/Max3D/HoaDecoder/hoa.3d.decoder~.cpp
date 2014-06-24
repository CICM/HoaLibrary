/*
 // Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

/**
 @file      hoa.3d.decoder~.cpp
 @name      hoa.3d.decoder~
 @realname  hoa.3d.decoder~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A 3d ambisonic decoder.
 
 @description
 <o>hoa.3d.decoder~</o> decodes an ambisonics soundfield for several loudspeakers configuration or for headphones. First argument is the ambisonic order of decomposition, the second one is the number of channels.
 
 @discussion
 <o>hoa.3d.decoder~</o> decodes an ambisonics soundfield for several loudspeakers configuration or for headphones. First argument is the ambisonic order of decomposition, the second one is the number of channels.
 
 @category ambisonics, hoa objects, audio, MSP
 
 @seealso hoa.2d.decoder~, hoa.3d.encoder~, hoa.3d.map~, hoa.3d.optim~, hoa.3d.scope~, hoa.3d.wider~, hoa.dac~
 */

#include "../Hoa3D.max.h"

typedef struct _hoa_decoder 
{
	t_pxobject				f_ob;
	double*					f_ins;
    double*					f_outs;
	Hoa3D::DecoderMulti*    f_decoder;
	
	double					f_angles_of_channels[MAX_CHANNELS * 2];
	long					f_number_of_angles;
    double					f_offset[2];
    t_symbol*				f_pinna;
	t_symbol*				f_mode;
} t_hoa_decoder;

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_free(t_hoa_decoder *x);
void hoa_decoder_assist(t_hoa_decoder *x, void *b, long m, long a, char *s);

void hoa_decoder_dsp64(t_hoa_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
//void hoa_decoder_perform64(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_decoder_perform64_zero(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_decoder_perform64_standard(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_decoder_perform64_binaural(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_hoa_err hoa_getinfos(t_hoa_decoder* x, t_hoa_boxinfos* boxinfos);

t_max_err mode_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err offset_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err pinna_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);

void *hoa_decoder_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.3d.decoder~", (method)hoa_decoder_new, (method)hoa_decoder_free, (long)sizeof(t_hoa_decoder), 0L, A_GIMME, 0);
	
	hoa_initclass(c, (method)hoa_getinfos);
	
	// @method signal @digest Array of spherical harmonic signals to decode for a set of loudspeakers
	// @description Array of spherical harmonic signals to decode for a set of loudspeakers
	class_addmethod(c, (method)hoa_decoder_dsp64,             "dsp64",      A_CANT, 0);
	class_addmethod(c, (method)hoa_decoder_assist,            "assist",     A_CANT, 0);
	
	CLASS_ATTR_SYM              (c, "mode", 0, t_hoa_decoder, f_mode);
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c, "mode", 0, "ambisonic binaural");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, mode_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    CLASS_ATTR_SAVE             (c, "mode", 1);
    // @description There is two decoding <m>mode</m> :
    // <ul>
    // <li><b>Ambisonics</b> : for a standard or irregular loudspeakers repartition over a sphere.</li>
    // <li><b>Binaural</b> : for headphones.</li>
    // </ul>
	
	CLASS_ATTR_DOUBLE_VARSIZE	(c, "angles", ATTR_SET_DEFER_LOW, t_hoa_decoder, f_angles_of_channels, f_number_of_angles, MAX_CHANNELS*2);
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles of Channels");
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_set);
	CLASS_ATTR_ORDER			(c, "angles", 0, "2");
	// @description Set the angles of each channels in degrees. The angles of channels are only settable in <b>irregular</b> <m>mode</m>. Each angles are in degrees, wrapped between 0. and 360. You must specify 2 values per channel corresponding to the azimuth value followed by the elevation value.
    
    CLASS_ATTR_DOUBLE_ARRAY     (c, "offset", 0, t_hoa_decoder, f_offset, 2);
    CLASS_ATTR_LABEL            (c, "offset", 0, "Offset of Channels");
	CLASS_ATTR_ACCESSORS		(c, "offset", NULL, offset_set);
    CLASS_ATTR_DEFAULT          (c, "offset", 0, "0 0");
    CLASS_ATTR_ORDER            (c, "offset", 0, "3");
    // @description Set the offsets of channels with a list of 2 float values corresponding to the azimuth and elevation offset, in degrees between 0. and 360.
	
	CLASS_ATTR_SYM              (c, "pinna", 0, t_hoa_decoder, f_pinna);
    CLASS_ATTR_LABEL            (c, "pinna", 0, "Pinna Size");
    CLASS_ATTR_ENUM             (c, "pinna", 0, "small large");
	CLASS_ATTR_ACCESSORS		(c, "pinna", NULL, pinna_set);
    CLASS_ATTR_ORDER            (c, "pinna", 0, "4");
    // @description The pinna size to use for the binaural restitution. The <m>pinna</m> message followed by the <b>symbol</b> <b>small</b> or <b>large</b> set the pinna size of the HRTF responses for the binaural restitution. Choose the one that suits you best.
    
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	hoa_decoder_class = c;
	return 0;
}

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
	// @arg 0 @name ambisonic-order @optional 0 @type int @digest The ambisonic order of decomposition
	// @description First argument is the ambisonic order of decomposition.
	
	// @arg 1 @name number-of-channels @optional 0 @type int @digest The number of channels
	// @description Second argument is the number of channels
	
	t_hoa_decoder *x = NULL;
	int order = 1;
    int number_of_channels = 4;
    
    x = (t_hoa_decoder *)object_alloc((t_class*)hoa_decoder_class);
	if(x)
	{
		x->f_mode = hoa_sym_ambisonic;
		x->f_pinna = gensym("large");
		
		if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
			order	= clip_min(atom_getfloat(argv), 1);
        if(atom_gettype(argv+1) == A_LONG || atom_gettype(argv+1) == A_FLOAT)
			number_of_channels	= clip_min(atom_getfloat(argv+1), 1);
		
        x->f_decoder = new Hoa3D::DecoderMulti(order, number_of_channels);
		x->f_number_of_angles = x->f_decoder->getNumberOfChannels() * 2;
        
		dsp_setup((t_pxobject *)x, x->f_decoder->getNumberOfHarmonics());
		for (int i = 0; i < x->f_decoder->getNumberOfChannels(); i++)
			outlet_new(x, "signal");
		
		x->f_ins    =  new double[x->f_decoder->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs   =  new double[x->f_decoder->getNumberOfChannels() * SYS_MAXBLKSIZE];
		
		for(int i = 0; i < x->f_decoder->getNumberOfChannels() * 2; i+= 2)
        {
			x->f_angles_of_channels[i] = x->f_decoder->getChannelAzimuth(i/2) / HOA_2PI * 360;
			x->f_angles_of_channels[i+1] = x->f_decoder->getChannelElevation(i/2) / HOA_2PI * 360;
        }
		
		attr_args_process(x, argc, argv);
	}
    
	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_decoder* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_3D;
	boxinfos->autoconnect_inputs = x->f_decoder->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_decoder->getNumberOfChannels();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_decoder_dsp64(t_hoa_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_decoder->setSampleRate(samplerate);
    x->f_decoder->setVectorSize(maxvectorsize);
    
    if(x->f_decoder->getDecodingMode() == Hoa3D::DecoderMulti::Standard)
        object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_decoder_perform64_standard, 0, NULL);
    else if(x->f_decoder->getDecodingMode() == Hoa3D::DecoderMulti::Binaural && x->f_decoder->getBinauralState())
        object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_decoder_perform64_binaural, 0, NULL);
    else
        object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_decoder_perform64_zero, 0, NULL);
}

void hoa_decoder_perform64_zero(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < sampleframes; i++)
        outs[0][i] = outs[1][i] = 0.;
}

void hoa_decoder_perform64_standard(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_decoder->processStandard(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
    
}

void hoa_decoder_perform64_binaural(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_decoder->processBinaural(ins, outs);
}

void hoa_decoder_assist(t_hoa_decoder *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(signal) %s",x->f_decoder->getHarmonicName(a).c_str());
	else
	{
		sprintf(s,"(signal) Channel %ld", a);
	}
}

void hoa_decoder_resize_outlets(t_hoa_decoder *x)
{
	t_object *b = NULL;
	object_method(gensym("dsp")->s_thing, hoa_sym_stop);
	
	object_obex_lookup(x, hoa_sym_pound_B, (t_object **)&b);
	object_method(b, hoa_sym_dynlet_begin);
	
	if(outlet_count((t_object *)x) > x->f_decoder->getNumberOfChannels())
	{
		for(int i = outlet_count((t_object *)x); i > x->f_decoder->getNumberOfChannels(); i--)
		{
			outlet_delete(outlet_nth((t_object*)x, i-1));
		}
	}
	else if(outlet_count((t_object *)x) < x->f_decoder->getNumberOfChannels())
	{
		for(int i = outlet_count((t_object *)x); i < x->f_decoder->getNumberOfChannels(); i++)
		{
			outlet_append((t_object*)x, NULL, gensym("signal"));
		}
	}
	
	object_method(b, hoa_sym_dynlet_end);
}

t_max_err mode_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
	if(argc && argv && atom_gettype(argv) == A_SYM)
	{
		t_symbol* mode = atom_getsym(argv);
        if(mode == hoa_sym_ambisonic && x->f_decoder->getDecodingMode() != Hoa3D::DecoderMulti::Standard)
        {
			object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setDecodingMode(Hoa3D::DecoderMulti::Standard);
            object_attr_setdisabled((t_object *)x, hoa_sym_angles, 0);
            object_attr_setdisabled((t_object *)x, hoa_sym_offset, 0);
            object_attr_setdisabled((t_object *)x, hoa_sym_pinna, 1);
			float offset[2];
			offset[0] = x->f_decoder->getChannelsAzimuthOffset() / HOA_2PI * 360.f;
			offset[1] = x->f_decoder->getChannelsElevationOffset() / HOA_2PI * 360.f;
			object_attr_setfloat_array(x, hoa_sym_offset, 2, offset);
			x->f_mode = mode;
			hoa_decoder_resize_outlets(x);
		}
        else if(mode == hoa_sym_binaural && x->f_decoder->getDecodingMode() != Hoa3D::DecoderMulti::Binaural)
        {
			x->f_decoder->setDecodingMode(Hoa3D::DecoderMulti::Binaural);
            object_attr_setdisabled((t_object *)x, hoa_sym_angles, 1);
            object_attr_setdisabled((t_object *)x, hoa_sym_offset, 1);
            object_attr_setdisabled((t_object *)x, hoa_sym_pinna, 0);
			x->f_mode = mode;
			hoa_decoder_resize_outlets(x);
        }
    }
    return MAX_ERR_NONE;
}

t_max_err angles_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
		short dspstate = dsp_setloadupdate(false);
        for(int i = 1, j = 0; i < x->f_decoder->getNumberOfChannels() * 2 && i < argc; i+= 2, j++)
        {
            if( (atom_gettype(argv+i-1) == A_FLOAT || atom_gettype(argv+i-1) == A_LONG) &&
			   (atom_gettype(argv+i) == A_FLOAT || atom_gettype(argv+i) == A_LONG) )
			{
                x->f_decoder->setChannelPosition(j, atom_getfloat(argv+i-1) / 360. * HOA_2PI, atom_getfloat(argv+i) / 360. * HOA_2PI);
			}
			
			x->f_angles_of_channels[i-1] = x->f_decoder->getChannelAzimuth(j) / HOA_2PI * 360;
			x->f_angles_of_channels[i] = x->f_decoder->getChannelElevation(j) / HOA_2PI * 360;
        }
		dsp_setloadupdate(dspstate);
    }
    return MAX_ERR_NONE;
}

t_max_err offset_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        double azimuth, elevation;
        if(atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG)
			azimuth = wrap_twopi(atom_getfloat(argv) / 360. * HOA_2PI);
        else
            azimuth = x->f_decoder->getChannelsAzimuthOffset();
        
        if(argc > 1 && (atom_gettype(argv+1) == A_FLOAT || atom_gettype(argv+1) == A_LONG))
            elevation = wrap_twopi(atom_getfloat(argv+1) / 360. * HOA_2PI);
        else
            elevation = x->f_decoder->getChannelsElevationOffset();
        
        x->f_decoder->setChannelsOffset(azimuth, elevation);
		
		x->f_offset[0] = x->f_decoder->getChannelsAzimuthOffset() / HOA_2PI * 360;
		x->f_offset[1] = x->f_decoder->getChannelsElevationOffset() / HOA_2PI * 360;
    }
    return MAX_ERR_NONE;
}

t_max_err pinna_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
	if(argc && argv && atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == gensym("small") && x->f_decoder->getPinnaSize() != Hoa3D::DecoderBinaural::Small)
        {
            if(x->f_decoder->getDecodingMode() == Hoa3D::DecoderMulti::Binaural)
                object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setPinnaSize(Hoa3D::DecoderBinaural::Small);
			x->f_pinna = atom_getsym(argv);
		}
        else if(atom_getsym(argv) == gensym("large") && x->f_decoder->getPinnaSize() != Hoa3D::DecoderBinaural::Large)
        {
            if(x->f_decoder->getDecodingMode() == Hoa3D::DecoderMulti::Binaural)
                object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setPinnaSize(Hoa3D::DecoderBinaural::Large);
			x->f_pinna = atom_getsym(argv);
        }
    }
	return MAX_ERR_NONE;
}

void hoa_decoder_free(t_hoa_decoder *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_decoder;
    delete [] x->f_ins;
    delete [] x->f_outs;
}