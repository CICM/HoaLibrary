/*
// Copyright (c) 2012-2013 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.max.h"

typedef struct _hoa_decoder 
{
	t_pxobject              f_ob;
    
    Hoa2D::DecoderMulti*    f_decoder;
    double*                 f_ins;
    double*                 f_outs;
    t_atom_long             f_send_config;
    void*                   f_attr;
} t_hoa_decoder;

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_free(t_hoa_decoder *x);
void hoa_decoder_assist(t_hoa_decoder *x, void *b, long m, long a, char *s);

void hoa_decoder_dsp64(t_hoa_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_decoder_perform64_regular(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_decoder_perform64_irregular(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoa_decoder_perform64_binaural(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void send_configuration(t_hoa_decoder *x);

t_hoa_err hoa_getinfos(t_hoa_decoder* x, t_hoa_boxinfos* boxinfos);

t_max_err mode_get(t_hoa_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err mode_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_get(t_hoa_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err channel_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_get(t_hoa_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err angles_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);
t_max_err offset_get(t_hoa_decoder *x, t_object *attr, long *argc, t_atom **argv);
t_max_err offset_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv);

t_class *hoa_decoder_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.2d.decoder~", (method)hoa_decoder_new, (method)hoa_decoder_free, (long)sizeof(t_hoa_decoder), 0L, A_GIMME, 0);
    class_alias(c, gensym("hoa.decoder~"));
	
    hoa_initclass(c, (method)hoa_getinfos);
	class_addmethod(c, (method)hoa_decoder_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)hoa_decoder_assist,		"assist",	A_CANT, 0);
    
    CLASS_ATTR_LONG             (c, "autoconnect", 0, t_hoa_decoder, f_send_config);
	CLASS_ATTR_CATEGORY			(c, "autoconnect", 0, "Behavior");
	CLASS_ATTR_STYLE_LABEL      (c, "autoconnect", 0, "onoff", "Auto connection");
    CLASS_ATTR_ORDER            (c, "autoconnect", 0, "1");
    CLASS_ATTR_SAVE             (c, "autoconnect", 1);
    
    CLASS_ATTR_SYM              (c, "mode", ATTR_SET_DEFER_LOW, t_hoa_decoder, f_attr);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c, "mode", 0, "ambisonic binaural irregular");
	CLASS_ATTR_ACCESSORS		(c, "mode", mode_get, mode_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    CLASS_ATTR_SAVE             (c, "mode", 1);
    
    CLASS_ATTR_LONG             (c, "channels", ATTR_SET_DEFER_LOW, t_hoa_decoder, f_attr);
	CLASS_ATTR_CATEGORY			(c, "channels", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_ACCESSORS		(c, "channels", channel_get, channel_set);
    CLASS_ATTR_DEFAULT          (c, "channels", 0, "4");
    CLASS_ATTR_ORDER            (c, "channels", 0, "2");
    CLASS_ATTR_SAVE             (c, "channels", 0);
    
    CLASS_ATTR_DOUBLE           (c, "offset", ATTR_SET_DEFER_LOW, t_hoa_decoder, f_attr);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "offset", 0, "Offset of Channels");
	CLASS_ATTR_ACCESSORS		(c, "offset", offset_get, offset_set);
    CLASS_ATTR_DEFAULT          (c, "offset", 0, "0");
    CLASS_ATTR_ORDER            (c, "offset", 0, "3");
    CLASS_ATTR_SAVE             (c, "offset", 0);
    
    CLASS_ATTR_DOUBLE_VARSIZE   (c, "angles", ATTR_SET_DEFER_LOW, t_hoa_decoder, f_attr, f_attr, MAX_CHANNELS);
	CLASS_ATTR_CATEGORY			(c, "angles", 0, "Planewaves");
    CLASS_ATTR_LABEL            (c, "angles", 0, "Angles of Channels");
	CLASS_ATTR_ACCESSORS		(c, "angles", angles_get, angles_set);
    CLASS_ATTR_ORDER            (c, "angles", 0, "4");
	CLASS_ATTR_SAVE             (c, "angles", 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);	
	hoa_decoder_class = c;
    
	return 0;
}

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_decoder *x = NULL;
    t_dictionary *d = NULL;
    t_dictionary *attr = NULL;
    t_atom_long channels;
    t_symbol*   mode;
	int	order = 1;
    x = (t_hoa_decoder *)object_alloc(hoa_decoder_class);
	if (x)
	{
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
		if(order < 1)
            order = 1;
    
        x->f_decoder    = new Hoa2D::DecoderMulti(order);
        x->f_decoder->setSampleRate(sys_getsr());
        x->f_decoder->setVectorSize(sys_getblksize());
        
        d = (t_dictionary *)gensym("#D")->s_thing;
        if(d && dictionary_getdictionary(d, gensym("saved_object_attributes"), (t_object **)&attr) == MAX_ERR_NONE)
        {
            if(dictionary_getsym(attr, gensym("mode"), &mode) == MAX_ERR_NONE)
            {
                if(mode == gensym("irregular"))
                    x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Irregular);
                else if(mode == gensym("binaural"))
                    x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Binaural);
                else
                    x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Regular);
            }
            if(dictionary_getlong(attr, gensym("channels"), &channels) == MAX_ERR_NONE)
                x->f_decoder->setNumberOfChannels(channels);
            dictionary_getlong(attr, gensym("autoconnect"), &x->f_send_config);
        }
       
		dsp_setup((t_pxobject *)x, x->f_decoder->getNumberOfHarmonics());
        for(int i = 0; i < x->f_decoder->getNumberOfChannels(); i++)
            outlet_new(x, "signal");
        
        x->f_ob.z_misc = Z_NO_INPLACE;
        x->f_ins = new double[x->f_decoder->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
        x->f_outs= new double[MAX_CHANNELS * SYS_MAXBLKSIZE];
        
        if(d)
            attr_dictionary_process(x, d);
        defer_low(x, (method)send_configuration, NULL, 0, NULL);
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

void hoa_decoder_dsp64(t_hoa_decoder *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_decoder->setSampleRate(samplerate);
    x->f_decoder->setVectorSize(maxvectorsize);
    
    if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Regular)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_decoder_perform64_regular, 0, NULL);
    else if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Irregular)
        object_method(dsp64, gensym("dsp_add64"), x, hoa_decoder_perform64_irregular, 0, NULL);
    else if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Binaural && x->f_decoder->getBinauralState())
        object_method(dsp64, gensym("dsp_add64"), x, hoa_decoder_perform64_regular, 0, NULL);
}

void hoa_decoder_perform64_regular(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
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

void hoa_decoder_perform64_irregular(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
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

void hoa_decoder_perform64_binaural(t_hoa_decoder *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_decoder->processBinaural(ins, outs);
}

void hoa_decoder_assist(t_hoa_decoder *x, void *b, long m, long a, char *s)
{
    if(m == ASSIST_INLET)
        sprintf(s,"(signal) %s", x->f_decoder->getHarmonicsName(a).c_str());
    else
        sprintf(s,"(signal) %s", x->f_decoder->getChannelName(a).c_str());
}


void hoa_decoder_free(t_hoa_decoder *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_decoder;
    delete [] x->f_ins;
    delete [] x->f_outs;
}

t_max_err mode_get(t_hoa_decoder *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)sysmem_newptr(argc[0] * sizeof(t_atom));
    if(argv[0])
    {
        if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Regular)
            atom_setsym(argv[0], gensym("ambisonic"));
        else if(x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Irregular)
            atom_setsym(argv[0], gensym("irregular"));
        else
            atom_setsym(argv[0], gensym("binaural"));
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    
    return MAX_ERR_NONE;
}

t_max_err mode_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == gensym("ambisonic") && x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Regular)
        {
            object_method(gensym("dsp")->s_thing, gensym("stop"));
            x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Regular);
            object_attr_setdisabled((t_object *)x, gensym("angles"), 1);
            object_attr_setdisabled((t_object *)x, gensym("channels"), 0);
            object_attr_setdisabled((t_object *)x, gensym("offset"), 0);
            object_attr_setfloat(x, gensym("offset"), (float)x->f_decoder->getChannelsOffset() / HOA_2PI * 360.f);
		}
        else if(atom_getsym(argv) == gensym("irregular") && x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Irregular)
        {
            object_method(gensym("dsp")->s_thing, gensym("stop"));
            x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Irregular);
            object_attr_setdisabled((t_object *)x, gensym("angles"), 0);
            object_attr_setdisabled((t_object *)x, gensym("channels"), 0);
            object_attr_setdisabled((t_object *)x, gensym("offset"), 0);
        }
        else if(atom_getsym(argv) == gensym("binaural") && x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Binaural)
        {
            object_method(gensym("dsp")->s_thing, gensym("stop"));
            x->f_decoder->setDecodingMode(Hoa2D::DecoderMulti::Binaural);
            object_attr_setdisabled((t_object *)x, gensym("angles"), 1);
            object_attr_setdisabled((t_object *)x, gensym("channels"), 1);
            object_attr_setdisabled((t_object *)x, gensym("offset"), 1);
            
        }
        object_attr_setlong(x, gensym("channels"), x->f_decoder->getNumberOfChannels());
    }
    send_configuration(x);
    return MAX_ERR_NONE;
}

t_max_err offset_get(t_hoa_decoder *x, t_object *attr, long *argc, t_atom **argv)
{
    argc[0] = 1;
    argv[0] = (t_atom *)sysmem_newptr(argc[0] * sizeof(t_atom));
    
    if(argv[0])
    {
        atom_setfloat(argv[0], x->f_decoder->getChannelsOffset() / HOA_2PI * 360.f);
    }
    else
    {
        argc[0] = 0;
        argv[0] = NULL;
    }
    return MAX_ERR_NONE;
}

t_max_err offset_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG))
    {
        double offset = atom_getfloat(argv) / 360.f * HOA_2PI;
        if(offset != x->f_decoder->getChannelsOffset())
        {
            object_method(gensym("dsp")->s_thing, gensym("stop"));
            x->f_decoder->setChannelsOffset(offset);
        }
    }
    send_configuration(x);
    return MAX_ERR_NONE;
}

t_max_err channel_get(t_hoa_decoder *x, t_object *attr, long *argc, t_atom **argv)
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

t_max_err channel_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    t_object *b = NULL;
    if(argc && argv && atom_gettype(argv) == A_LONG && atom_getlong(argv) != outlet_count((t_object *)x))
    {
        if(x->f_decoder->getDecodingMode() != Hoa2D::DecoderMulti::Regular || atom_getlong(argv) >= x->f_decoder->getNumberOfHarmonics())
        {
            object_method(gensym("dsp")->s_thing, gensym("stop"));
            
            object_obex_lookup(x, gensym("#B"), (t_object **)&b);
            object_method(b, gensym("dynlet_begin"));
            
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
            
            object_method(b, gensym("dynlet_end"));
            object_attr_touch((t_object *)x, gensym("angles"));
        }
    }
    send_configuration(x);
    return 0;
}

t_max_err angles_get(t_hoa_decoder *x, t_object *attr, long *argc, t_atom **argv)
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

t_max_err angles_set(t_hoa_decoder *x, t_object *attr, long argc, t_atom *argv)
{
    double *angles;
    if(argc && argv && x->f_decoder->getDecodingMode() == Hoa2D::DecoderMulti::Irregular)
    {
        angles = new double[x->f_decoder->getNumberOfChannels()];
        if(angles)
        {
            object_method(gensym("dsp")->s_thing, gensym("stop"));
            for(int i = 0; i < argc && i < x->f_decoder->getNumberOfChannels(); i++)
            {
                if(atom_gettype(argv+i) == A_FLOAT || atom_gettype(argv+i) == A_LONG)
                    angles[i] = atom_getfloat(argv+i) / 360. * HOA_2PI;
                else
                    angles[i] = x->f_decoder->getChannelAzimuth(i);
            }
            
            x->f_decoder->setChannelsAzimtuh(angles);
            free(angles);
        }
    }
    send_configuration(x);
    return 0;
}

void send_configuration(t_hoa_decoder *x)
{
	t_object *patcher;
	t_object *decoder;
    t_object *object;
    t_object *line;
	t_max_err err;
    
    if(!x->f_send_config)
        return;
    
	err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
	if (err != MAX_ERR_NONE)
		return;
	
	err = object_obex_lookup(x, gensym("#B"), (t_object **)&decoder);
	if (err != MAX_ERR_NONE)
		return;
	
    t_atom nchannels;
    t_atom offset;
    t_atom *argv = new t_atom[x->f_decoder->getNumberOfChannels()];
    if(argv)
    {
        atom_setlong(&nchannels, x->f_decoder->getNumberOfChannels());
        atom_setfloat(&offset, x->f_decoder->getChannelsOffset() / HOA_2PI * 360.);
        for(int i = 0; i < x->f_decoder->getNumberOfChannels(); i++)
            atom_setfloat(argv+i, x->f_decoder->getChannelAzimuth(i) / HOA_2PI * 360.);
        
        for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line))
        {
            if (jpatchline_get_box1(line) == decoder)
            {
                object = jpatchline_get_box2(line);
                t_symbol* classname = object_classname(jbox_get_object(object));
                if(classname == gensym("hoa.2d.meter~") || classname == gensym("hoa.meter~") ||  classname == gensym("hoa.2d.vector~"))
                {
                    object_method_typed(jbox_get_object(object), gensym("channels"), 1, &nchannels, NULL);
                    object_method_typed(jbox_get_object(object), gensym("angles"), x->f_decoder->getNumberOfChannels(), argv, NULL);
                    object_method_typed(jbox_get_object(object), gensym("offset"), 1, &offset, NULL);
                }
                else if(classname == gensym("hoa.gain~"))
                    object_method_typed(jbox_get_object(object), gensym("channels"), 1, &nchannels, NULL);
            }
        }
        
        free(argv);
    }
}

