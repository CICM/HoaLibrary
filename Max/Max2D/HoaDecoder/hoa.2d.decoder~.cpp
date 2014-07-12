/*
// Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

/**
 @file      hoa.2d.decoder~.cpp
 @name      hoa.2d.decoder~
 @realname  hoa.2d.decoder~
 @type      object
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A 2d ambisonic decoder.
 
 @description
 <o>hoa.2d.decoder~</o> decodes an ambisonics soundfield for several loudspeakers configuration or for headphones. First argument is the ambisonic order of decomposition.
 
 @discussion
<o>hoa.2d.decoder~</o> decodes an ambisonics soundfield for several loudspeakers configuration or for headphones. First argument is the ambisonic order of decomposition.
 
 @category ambisonics, hoa objects, audio, MSP
 
 @seealso hoa.2d.meter~, hoa.2d.scope~, hoa.dac~, hoa.vector~, hoa.2d.optim~, hoa.2d.map~, hoa.2d.encoder~, hoa.3d.decoder~
 */

#include "../Hoa2D.max.h"

typedef struct _hoa_2d_decoder 
{
	t_pxobject              f_ob;
    
    Hoa2D::DecoderMulti*    f_decoder;
    double*                 f_ins;
    double*                 f_outs;
    t_atom_long             f_send_config;
    void*                   f_attr;
} t_hoa_2d_decoder;

void *hoa_2d_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_2d_decoder_free(t_hoa_2d_decoder *x);
void hoa_2d_decoder_assist(t_hoa_2d_decoder *x, void *b, long m, long a, char *s);

void hoa_2d_decoder_dsp64(t_hoa_2d_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_2d_decoder_perform64(t_hoa_2d_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void send_configuration(t_hoa_2d_decoder *x);
void reconnect_outlets(t_hoa_2d_decoder *x);

t_hoa_err hoa_getinfos(t_hoa_2d_decoder* x, t_hoa_boxinfos* boxinfos);

t_max_err mode_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err mode_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err channel_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err angles_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err offset_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err offset_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err pinna_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err pinna_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv);

t_class *hoa_2d_decoder_class;

#ifdef HOA_PACKED_LIB
int hoa_2d_decoder_main(void)
#else
int C74_EXPORT main(void)
#endif
{
	t_class *c;
	
	c = class_new("hoa.2d.decoder~", (method)hoa_2d_decoder_new, (method)hoa_2d_decoder_free, (long)sizeof(t_hoa_2d_decoder), 0L, A_GIMME, 0);
    class_setname((char *)"hoa.2d.decoder~", (char *)"hoa.2d.decoder~");
	
    hoa_initclass(c, (method)hoa_getinfos);
    
    // @method signal @digest Array of circular harmonic signals to decode for an array of loudspeakers
	// @description Array of circular harmonic signals to decode for an array of loudspeakers
	class_addmethod(c, (method)hoa_2d_decoder_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_2d_decoder_assist,		"assist",	A_CANT, 0);
    
    CLASS_ATTR_LONG             (c, "autoconnect", 0, t_hoa_2d_decoder, f_send_config);
	CLASS_ATTR_CATEGORY			(c, "autoconnect", 0, "Behavior");
	CLASS_ATTR_STYLE_LABEL      (c, "autoconnect", 0, "onoff", "Auto connection");
    CLASS_ATTR_ORDER            (c, "autoconnect", 0, "1");
    CLASS_ATTR_SAVE             (c, "autoconnect", 1);
    // @description If the <m>autoconnect</m> attribute is checked, connected objects like the <o>hoa.2d.meter~</o>, <o>hoa.2d.vector~</o>, <o>hoa.dac~</o> or <o>hoa.gain~</o> will be notified of changes and adapt their behavior accordingly.
    
    CLASS_ATTR_SYM              (c, "mode", ATTR_SET_DEFER_LOW, t_hoa_2d_decoder, f_attr);
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c, "mode", 0, "ambisonic binaural irregular");
	CLASS_ATTR_ACCESSORS		(c, "mode", mode_get, mode_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    CLASS_ATTR_SAVE             (c, "mode", 1);
    // @description There is three decoding <m>mode</m> :
    // <ul>
    // <li><b>Ambisonics</b> : for a regular loudspeakers repartition over a circular array.</li>
    // <li><b>Binaural</b> : for headphones.</li>
    // <li><b>Irregular</b> : for an irregular loudspeakers repartition over a circular array.</li>
    // </ul>
    
    CLASS_ATTR_LONG             (c, "channels", ATTR_SET_DEFER_LOW, t_hoa_2d_decoder, f_attr);
    CLASS_ATTR_LABEL            (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_ACCESSORS		(c, "channels", channel_get, channel_set);
    CLASS_ATTR_DEFAULT          (c, "channels", 0, "4");
    CLASS_ATTR_ORDER            (c, "channels", 0, "2");
    CLASS_ATTR_SAVE             (c, "channels", 0);
    // @description The number of Channels. In <b>ambisonic</b> <m>mode</m>, the number of channels must be equal or higher to the number of harmonics : (order *2 + 1), (default : order * 2 + 2).
    
    CLASS_ATTR_DOUBLE           (c, "offset", ATTR_SET_DEFER_LOW, t_hoa_2d_decoder, f_attr);
    CLASS_ATTR_LABEL            (c, "offset", 0, "Offsets of Channels");
	CLASS_ATTR_ACCESSORS		(c, "offset", offset_get, offset_set);
    CLASS_ATTR_DEFAULT          (c, "offset", 0, "0");
    CLASS_ATTR_ORDER            (c, "offset", 0, "3");
    CLASS_ATTR_SAVE             (c, "offset", 0);
    // @description The offset of channels, in degrees between 0. and 360.
    
    CLASS_ATTR_DOUBLE_VARSIZE   (c, "angles", ATTR_SET_DEFER_LOW, t_hoa_2d_decoder, f_attr, f_attr, MAX_CHANNELS);
    CLASS_ATTR_LABEL            (c, "angles", 0, "Angles of Channels");
	CLASS_ATTR_ACCESSORS		(c, "angles", angles_get, angles_set);
    CLASS_ATTR_ORDER            (c, "angles", 0, "4");
	CLASS_ATTR_SAVE             (c, "angles", 0);
    // @description Angles of each channels. The angles of channels are only settable in <b>irregular</b> <m>mode</m>. Each angle are in degrees and is wrapped between 0. and 360. So you can also set an angle with a negative value. ex : angles for a 5.1 loudspeakers restitution system can be setted either by the "angles 0 30 110 250 330" or by "angles 0 30 110 -110 -30".
    
    CLASS_ATTR_SYM              (c, "pinna", ATTR_SET_DEFER_LOW, t_hoa_2d_decoder, f_attr);
    CLASS_ATTR_LABEL            (c, "pinna", 0, "Pinna Size");
    CLASS_ATTR_ENUM             (c, "pinna", 0, "small large");
	CLASS_ATTR_ACCESSORS		(c, "pinna", pinna_get, pinna_set);
    CLASS_ATTR_ORDER            (c, "pinna", 0, "5");
    CLASS_ATTR_SAVE             (c, "pinna", 1);
    // @description The pinna size to use for the binaural restitution. The <m>pinna</m> message followed by the <b>symbol</b> <b>small</b> or <b>large</b> set the pinna size of the HRTF responses for the binaural restitution. Choose the one that suits you best.
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
    class_alias(c, gensym("hoa.decoder~"));
	hoa_2d_decoder_class = c;
    
	return 0;
}

void *hoa_2d_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
    // @arg 0 @name ambisonic-order @optional 0 @type int @digest The ambisonic order of decomposition
	// @description First argument is the ambisonic order of decomposition.
    
	t_hoa_2d_decoder *x = NULL;
    t_dictionary *d = NULL;
    t_dictionary *attr = NULL;
    t_atom_long channels;
    t_symbol*   mode;
	int	order = 1;
    
    x = (t_hoa_2d_decoder *)object_alloc(hoa_2d_decoder_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(order < 1)
            order = 1;
        
        x->f_send_config = 1;
    
        x->f_decoder    = new Hoa2D::DecoderMulti(order);
        
        d = (t_dictionary *)gensym("#D")->s_thing;
        if(d && dictionary_getdictionary(d, gensym("saved_object_attributes"), (t_object **)&attr) == MAX_ERR_NONE)
        {
            if(dictionary_getsym(attr, gensym("mode"), &mode) == MAX_ERR_NONE)
            {
                if(mode == hoa_sym_irregular)
                    x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Irregular);
                else if(mode == hoa_sym_binaural)
                    x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Binaural);
                else
                    x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Regular);
            }
            if(dictionary_getlong(attr, hoa_sym_channels, &channels) == MAX_ERR_NONE)
                x->f_decoder->setNumberOfChannels(channels);
            if(dictionary_getsym(attr, gensym("pinna"), &mode) == MAX_ERR_NONE)
            {
                if(mode == gensym("large"))
                    x->f_decoder->setPinnaSize(DecoderBinaural::Large);
                else if(mode == gensym("small"))
                    x->f_decoder->setPinnaSize(DecoderBinaural::Small);
            }
            dictionary_getlong(attr, gensym("autoconnect"), &x->f_send_config);
        }
       
        x->f_decoder->setSampleRate(sys_getsr());
        //x->f_decoder->setVectorSize(sys_getblksize());
		dsp_setup((t_pxobject *)x, x->f_decoder->getNumberOfHarmonics());
        for(int i = 0; i < x->f_decoder->getNumberOfChannels(); i++)
            outlet_new(x, "signal");
        
        x->f_ob.z_misc = Z_NO_INPLACE;
        x->f_ins = new double[x->f_decoder->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs= new double[MAX_CHANNELS * SYS_MAXBLKSIZE];
        
        if(d)
            attr_dictionary_process(x, d);
        
        attr_args_process(x, argc, argv);
        
        defer_low(x, (method)send_configuration, NULL, 0, NULL);
	}

	return (x);
}

t_hoa_err hoa_getinfos(t_hoa_2d_decoder* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = x->f_decoder->getNumberOfHarmonics();
	boxinfos->autoconnect_outputs = x->f_decoder->getNumberOfChannels();
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_AMBISONICS;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoa_2d_decoder_dsp64(t_hoa_2d_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_decoder->setSampleRate(samplerate);
    object_method(dsp64, gensym("dsp_add64"), x, (method)hoa_2d_decoder_perform64, 0, NULL);
    /*
    if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Regular)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_2d_decoder_perform64_regular, 0, NULL);
    else if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Irregular)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_2d_decoder_perform64_irregular, 0, NULL);
    else if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Binaural && x->f_decoder->getBinauralState())
        object_method(dsp64, gensym("dsp_add64"), x, hoa_2d_decoder_perform64_binaural, 0, NULL);
    */
}

void hoa_2d_decoder_perform64(t_hoa_2d_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
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

/*
void hoa_2d_decoder_perform64_regular(t_hoa_2d_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_decoder->processRegular(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
    
}

void hoa_2d_decoder_perform64_irregular(t_hoa_2d_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_ins+i, numins);
    }
	for(int i = 0; i < sampleframes; i++)
    {
        x->f_decoder->processIrregular(x->f_ins + numins * i, x->f_outs + numouts * i);
    }
    for(int i = 0; i < numouts; i++)
    {
        cblas_dcopy(sampleframes, x->f_outs+i, numouts, outs[i], 1);
    }
}

void hoa_2d_decoder_perform64_binaural(t_hoa_2d_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_decoder->processBinaural(ins, outs);
}
*/

void hoa_2d_decoder_assist(t_hoa_2d_decoder *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
        sprintf(s,"(signal) %s", x->f_decoder->getHarmonicName(a).c_str());
    else
        sprintf(s,"(signal) %s", x->f_decoder->getChannelName(a).c_str());
}


void hoa_2d_decoder_free(t_hoa_2d_decoder *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_decoder;
    delete [] x->f_ins;
    delete [] x->f_outs;
}

t_max_err mode_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)sysmem_newptr(argc[0] * sizeof(t_atom));
    if(argv[0])
    {
        if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Regular)
            atom_setsym(argv[0], hoa_sym_ambisonic);
        else if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Irregular)
            atom_setsym(argv[0], hoa_sym_irregular);
        else
            atom_setsym(argv[0], hoa_sym_binaural);
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    
    return MAX_ERR_NONE;
}

t_max_err mode_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == hoa_sym_ambisonic && x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Regular)
        {
            //short dspstate = dsp_setloadupdate(true);
            object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Regular);
            object_attr_setdisabled((t_object *)x, hoa_sym_angles, 1);
            object_attr_setdisabled((t_object *)x, hoa_sym_channels, 0);
            object_attr_setdisabled((t_object *)x, hoa_sym_offset, 0);
            object_attr_setdisabled((t_object *)x, hoa_sym_pinna, 1);
            object_attr_setfloat(x, hoa_sym_offset, (float)x->f_decoder->getChannelsOffset() / HOA_2PI * 360.f);
		}
        else if(atom_getsym(argv) == hoa_sym_irregular && x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Irregular)
        {
            //short dspstate = dsp_setloadupdate(true);
            object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Irregular);
            object_attr_setdisabled((t_object *)x, hoa_sym_angles, 0);
            object_attr_setdisabled((t_object *)x, hoa_sym_channels, 0);
            object_attr_setdisabled((t_object *)x, hoa_sym_offset, 0);
            object_attr_setdisabled((t_object *)x, hoa_sym_pinna, 1);
        }
        else if(atom_getsym(argv) == hoa_sym_binaural && x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Binaural)
        {
            //short dspstate = dsp_setloadupdate(true);
            //object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Binaural);
            object_attr_setdisabled((t_object *)x, hoa_sym_angles, 1);
            object_attr_setdisabled((t_object *)x, hoa_sym_channels, 1);
            object_attr_setdisabled((t_object *)x, hoa_sym_offset, 1);
            object_attr_setdisabled((t_object *)x, hoa_sym_pinna, 0);
        }
        object_attr_setlong(x, hoa_sym_channels, x->f_decoder->getNumberOfChannels());
        send_configuration(x);
    }
    return MAX_ERR_NONE;
}

t_max_err offset_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)sysmem_newptr(argc[0] * sizeof(t_atom));
    
    if(argv[0])
    {
        atom_setfloat(argv[0], wrap(x->f_decoder->getChannelsOffset() / HOA_2PI * 360.f, -180, 180));
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return MAX_ERR_NONE;
}

t_max_err offset_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_isNumber(argv))
    {
        double offset = wrap_twopi(wrap(atom_getfloat(argv), -180, 180) / 360. * HOA_2PI);
        if(offset != x->f_decoder->getChannelsOffset())
        {
            object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setChannelsOffset(offset);
            send_configuration(x);
        }
    }
    return MAX_ERR_NONE;
}

t_max_err channel_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)sysmem_newptr(argc[0] * sizeof(t_atom));
    if(argv[0])
    {
        atom_setlong(argv[0], x->f_decoder->getNumberOfChannels());
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    
    return MAX_ERR_NONE;
}

t_max_err channel_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    t_object *b = NULL;
    if(argc && argv && atom_gettype(argv) == A_LONG && atom_getlong(argv) != outlet_count((t_object *)x))
    {
        if(x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Regular || atom_getlong(argv) >= x->f_decoder->getNumberOfHarmonics())
        {
            object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            
            object_obex_lookup(x, hoa_sym_pound_B, (t_object **)&b);
            object_method(b, hoa_sym_dynlet_begin);
            
            x->f_decoder->setNumberOfChannels(atom_getlong(argv));
            
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
            object_attr_touch((t_object *)x, hoa_sym_angles);
            send_configuration(x);
        }
    }
    return 0;
}

t_max_err angles_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = x->f_decoder->getNumberOfChannels();
    argv[0] = (t_atom *)sysmem_newptr(argc[0] * sizeof(t_atom));
    if(argv[0])
    {
        for(int i = 0; i < x->f_decoder->getNumberOfChannels(); i++)
        {
            atom_setfloat(argv[0]+i, x->f_decoder->getChannelAzimuth(i) / HOA_2PI * 360.);
        }
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    
    return MAX_ERR_NONE;
}

t_max_err angles_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    double *angles;
    if(argc && argv && x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Irregular)
    {
        angles = new double[x->f_decoder->getNumberOfChannels()];
        if(angles)
        {
            object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            for(int i = 0; i < x->f_decoder->getNumberOfChannels(); i++)
            {
                if(i < argc && (atom_gettype(argv+i) == A_FLOAT || atom_gettype(argv+i) == A_LONG))
                    angles[i] = atom_getfloat(argv+i) / 360. * HOA_2PI;
                else
                    angles[i] = x->f_decoder->getChannelAzimuth(i);
            }
            
            x->f_decoder->setChannelsAzimtuh(angles);
            free(angles);
            send_configuration(x);
        }
    }
    
    return MAX_ERR_NONE;
}

t_max_err pinna_get(t_hoa_2d_decoder *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)sysmem_newptr(argc[0] * sizeof(t_atom));
    if(argv[0])
    {
        if(x->f_decoder->getPinnaSize() == Hoa2D::DecoderBinaural::Small)
            atom_setsym(argv[0], gensym("small"));
        else
            atom_setsym(argv[0], gensym("large"));
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return MAX_ERR_NONE;
}

t_max_err pinna_set(t_hoa_2d_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == gensym("small") && x->f_decoder->getPinnaSize() != Hoa2D::DecoderBinaural::Small)
        {
            if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Binaural)
                object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setPinnaSize(Hoa2D::DecoderBinaural::Small);
		}
        else if(atom_getsym(argv) == gensym("large") && x->f_decoder->getPinnaSize() != Hoa2D::DecoderBinaural::Large)
        {
            if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Binaural)
                object_method(gensym("dsp")->s_thing, hoa_sym_stop);
            x->f_decoder->setPinnaSize(Hoa2D::DecoderBinaural::Large);
        }
    }
    return MAX_ERR_NONE;
}

void send_configuration(t_hoa_2d_decoder *x)
{
	t_object *patcher;
	t_object *decoder;
    t_object *object;
    t_object *line;
    t_object *obj;
	t_max_err err;
    t_atom msg[4];
    t_atom rv;
    
    if(!x->f_send_config)
        return;
    
	err = object_obex_lookup(x, hoa_sym_pound_P, (t_object **)&patcher);
	if (err != MAX_ERR_NONE)
		return;
	
	err = object_obex_lookup(x, hoa_sym_pound_B, (t_object **)&decoder);
	if (err != MAX_ERR_NONE)
		return;
	
    t_atom nchannels;
    t_atom offset;
    t_atom *argv = new t_atom[x->f_decoder->getNumberOfChannels()];
    if(argv)
    {
        atom_setlong(&nchannels, x->f_decoder->getNumberOfChannels());
        atom_setfloat(&offset, wrap(x->f_decoder->getChannelsOffset() / HOA_2PI * 360.f, -180, 180));
        for(int i = 0; i < x->f_decoder->getNumberOfChannels(); i++)
            atom_setfloat(argv+i, x->f_decoder->getChannelAzimuth(i) / HOA_2PI * 360.);
        
        for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line))
        {
            if (jpatchline_get_box1(line) == decoder)
            {
                object = jpatchline_get_box2(line);
                obj = jbox_get_object(object);
                t_symbol* classname = object_classname(obj);
                
                if(classname == hoa_sym_hoa_2d_meter || classname == hoa_sym_hoa_2d_vector || classname == hoa_sym_hoa_gain || classname == hoa_sym_hoa_dac || hoa_sym_dac)
                {
                    if (classname == hoa_sym_hoa_2d_meter || classname == hoa_sym_hoa_2d_vector || classname == hoa_sym_hoa_gain)
                    {
                        object_method_typed(obj, hoa_sym_channels, 1, &nchannels, NULL);
                        object_method_typed(obj, hoa_sym_angles, x->f_decoder->getNumberOfChannels(), argv, NULL);
                        object_method_typed(obj, hoa_sym_offset, 1, &offset, NULL);
                    }
                    
                    // connection
                    for(int i = 0; jbox_getinlet((t_jbox *)object, i) != NULL && i < x->f_decoder->getNumberOfChannels(); i++)
                    {
                        atom_setobj(msg, decoder);
                        atom_setlong(msg + 1, i);
                        atom_setobj(msg + 2, object);
                        atom_setlong(msg + 3, i);
                        object_method_typed(patcher , hoa_sym_connect, 4, msg, &rv);
                    }
                }
            }
        }
        
        free(argv);
    }
}