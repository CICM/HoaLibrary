/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicsMultiDecoder.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "ext_path.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "ext_parameter.h"
#include "z_dsp.h"
}


typedef struct _HoaDecode 
{
	t_pxobject				f_ob;			
	AmbisonicsMultiDecoder  *f_AmbisonicsDecoder;

	int						f_ninput;
	int						f_noutput;
    
    t_atom                  f_configuration[256];
    long                    f_config_size;
} t_HoaDecode;

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv);
void HoaDecode_free(t_HoaDecode *x);
void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s);
void HoaDecode_resize_outlet(t_HoaDecode *x, long lastNumberOfOutlet);
void HoaDecode_reconnect_outlet(t_HoaDecode *x);

void configuration_shortcut(t_HoaDecode *x, t_symbol *attr, long argc, t_atom *argv);
t_max_err configuration_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaDecode_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.decoder~", (method)HoaDecode_new, (method)HoaDecode_free, (long)sizeof(t_HoaDecode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaDecode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_assist,	"assist",	A_CANT, 0);
    class_addmethod(c, (method)configuration_shortcut,	"ambisonics",	A_GIMME, 0);
    class_addmethod(c, (method)configuration_shortcut,	"binaural",     A_GIMME, 0);
    class_addmethod(c, (method)configuration_shortcut,	"irregular",	A_GIMME, 0);
    
    CLASS_ATTR_ATOM_VARSIZE     (c, "configuration", 0, t_HoaDecode, f_configuration, f_config_size, 256);
	CLASS_ATTR_CATEGORY			(c, "configuration", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "configuration", 0, "Configuation");
	CLASS_ATTR_ACCESSORS		(c, "configuration", NULL, configuration_set);
    CLASS_ATTR_ORDER            (c, "configuration", 0, "2");
    CLASS_ATTR_SAVE             (c, "configuration", 1);
    CLASS_ATTR_ALIAS            (c, "configuration", "config");

    class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaDecode_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaDecode *x = NULL;
    
	int order = 4;
    x = (t_HoaDecode *)object_alloc((t_class*)HoaDecode_class);
	if(x)
	{
		if(atom_gettype(argv) == A_LONG)
			order	= atom_getlong(argv);
		
#ifdef __APPLE__
        // OSX only : access to the hoa.binaural~ bundle
        CFBundleRef hoaBinaural_bundle = CFBundleGetBundleWithIdentifier(CFSTR("com.cicm.hoa-decoder-"));
        CFURLRef hoaBinaural_ref = CFBundleCopyBundleURL(hoaBinaural_bundle);
        UInt8 bundle_path[512];
        Boolean res = CFURLGetFileSystemRepresentation(hoaBinaural_ref, true, bundle_path, 512);
        assert(res);
        // Built the complete resource path
        std::string absoluteHrtfFilePath = std::string((const char*)bundle_path) + std::string("/Contents/Resources/") + std::string("HrtfDatabase/");
#endif
        
        /* Base Attributes */
		x->f_AmbisonicsDecoder	= new AmbisonicsMultiDecoder(order, absoluteHrtfFilePath, Hoa_Small, sys_getblksize(), sys_getsr(), Hoa_Ambisonics, order * 2 + 2, 5.1);
        
		x->f_config_size = 4;
        atom_setsym(x->f_configuration, gensym("ambisonics"));
        atom_setlong(x->f_configuration+1, order * 2 + 2);
        atom_setsym(x->f_configuration+2, gensym("offset"));
        atom_setfloat(x->f_configuration+3, 0.f);

        /* DSP Setup */
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsDecoder->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsDecoder->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
        attr_args_process(x, argc, argv);
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_AmbisonicsDecoder->setVectorSize(maxvectorsize);
    x->f_AmbisonicsDecoder->setSamplingRate(samplerate);
	object_method(dsp64, gensym("dsp_add64"), x, HoaDecode_perform64, 0, NULL);
}

void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_AmbisonicsDecoder->process(ins, outs);
}

void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(Signal) %s",x->f_AmbisonicsDecoder->getHarmonicsName(a).c_str());
	else
        sprintf(s,"(Signal) %s",x->f_AmbisonicsDecoder->getLoudspeakerName(a).c_str());
}

void HoaDecode_free(t_HoaDecode *x)
{
	dsp_free((t_pxobject *)x);
	delete x->f_AmbisonicsDecoder;
}

void configuration_shortcut(t_HoaDecode *x, t_symbol *attr, long argc, t_atom *argv)
{
    t_atom *av;
    long ac = argc +1;
    av = new t_atom[ac];
    atom_setsym(av, attr);
    for(int i = 0; i < argc; i++)
        av[i+1] = argv[i];
    configuration_set(x, NULL, ac, av);
    object_attr_addattr_parse((t_object*)x, "configuration", "invisible", USESYM(long), 1, "1");
    object_attr_touch((t_object*)x, gensym("configuration"));
}

t_max_err configuration_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    
    long numOutlet = x->f_AmbisonicsDecoder->getNumberOfOutputs();
    if(argc && argv)
    {
        for(int i = 0; i < argc; i++)
        {
            if(atom_gettype(argv+i) == A_SYM)
            {
                /* AMBISONICS */
                if(atom_getsym(argv+i) == gensym("ambisonics") || atom_getsym(argv+i) == gensym(" ambisonics"))
                {
                    if(x->f_AmbisonicsDecoder->getMode() != Hoa_Ambisonics)
                    {
                        if(dspState)
                            object_method(gensym("dsp")->s_thing, gensym("stop"));
                        x->f_AmbisonicsDecoder->setMode(Hoa_Ambisonics);
                    }
                    if(atom_gettype(argv+i+1) == A_LONG)
                    {
                        if(atom_getlong(argv+i+1) != x->f_AmbisonicsDecoder->getNumberOfLoudspeakers())
                        {
                            if(dspState)
                                object_method(gensym("dsp")->s_thing, gensym("stop"));
                            x->f_AmbisonicsDecoder->setNumberOfLoudspeakers(atom_getlong(argv+i+1));
                        }
                    }
                }
                else if(atom_getsym(argv+i) == gensym("offset") || atom_getsym(argv+i) == gensym(" offset"))
                {
                    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Ambisonics)
                    {
                        if(atom_gettype(argv+i+1) == A_FLOAT)
                            x->f_AmbisonicsDecoder->setOffset(atom_getfloat(argv+i+1));
                        else if(atom_gettype(argv+i+1) == A_LONG)
                            x->f_AmbisonicsDecoder->setOffset(atom_getlong(argv+i+1));
                    }
                }
                /* BINAURAL */
                else if(atom_getsym(argv+i) == gensym("binaural") || atom_getsym(argv+i) == gensym(" binaural"))
                {
                    if(x->f_AmbisonicsDecoder->getMode() != Hoa_Binaural)
                    {
                        if(dspState)
                            object_method(gensym("dsp")->s_thing, gensym("stop"));
                        x->f_AmbisonicsDecoder->setMode(Hoa_Binaural);
                    }
                    if(atom_gettype(argv+i+1) == A_SYM)
                    {
                        if(atom_gettype(argv) == A_SYM && (atom_getsym(argv) == gensym("large") || atom_getsym(argv) == gensym(" large")))
                            x->f_AmbisonicsDecoder->setPinnaSize(Hoa_Large);
                        else
                            x->f_AmbisonicsDecoder->setPinnaSize(Hoa_Small);
                    }                    
                }
                /* IRREGULAR */
                else if(atom_getsym(argv+i) == gensym("irregular") || atom_getsym(argv+i) == gensym(" irregular"))
                {
                    if(x->f_AmbisonicsDecoder->getMode() != Hoa_Restitution)
                    {
                        if(dspState)
                            object_method(gensym("dsp")->s_thing, gensym("stop"));
                        x->f_AmbisonicsDecoder->setMode(Hoa_Restitution);
                    }
                    if(atom_gettype(argv+i+1) == A_LONG)
                    {
                        if(atom_getlong(argv+i+1) != x->f_AmbisonicsDecoder->getConfiguration())
                        {
                            if(dspState)
                                object_method(gensym("dsp")->s_thing, gensym("stop"));
                            x->f_AmbisonicsDecoder->setConfiguration(atom_getlong(argv+i+1));
                        }
                    }
                    else if(atom_gettype(argv+i+1) == A_FLOAT)
                    {
                        if(atom_getfloat(argv+i+1) != x->f_AmbisonicsDecoder->getConfiguration())
                        {
                            if(dspState)
                                object_method(gensym("dsp")->s_thing, gensym("stop"));
                            x->f_AmbisonicsDecoder->setConfiguration(atom_getfloat(argv+i+1));
                        }
                    }
                }
                else if(atom_getsym(argv+i) == gensym("angles") || atom_getsym(argv+i) == gensym(" angles"))
                {
                    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution)
                    {
                        for(int j = 0; j < argc; j++)
                        {
                            if(atom_gettype(argv+i+j+1) == A_FLOAT)
                                x->f_AmbisonicsDecoder->setLoudspeakerAngle(j, atom_getfloat(argv+i+j+1));
                            else if(atom_gettype(argv+i+j+1) == A_LONG)
                                x->f_AmbisonicsDecoder->setLoudspeakerAngle(j, atom_getlong(argv+i+j+1));
                        }
                    }
                }
                
            }
        }
    }
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Ambisonics)
    {
        x->f_config_size = 4;
        atom_setsym(x->f_configuration, gensym("ambisonics"));
        atom_setlong(x->f_configuration+1, x->f_AmbisonicsDecoder->getNumberOfLoudspeakers());
        atom_setsym(x->f_configuration+2, gensym("offset"));
        atom_setfloat(x->f_configuration+3, x->f_AmbisonicsDecoder->getOffset());
    }
    else if(x->f_AmbisonicsDecoder->getMode() == Hoa_Binaural)
    {
        x->f_config_size = 2;
        atom_setsym(x->f_configuration, gensym("binaural"));
        if(x->f_AmbisonicsDecoder->getPinnaSize() == Hoa_Large)
            atom_setsym(x->f_configuration+1, gensym("large"));
        else
            atom_setsym(x->f_configuration+1, gensym("small"));
    }
    else if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution)
    {
        long nHps = x->f_AmbisonicsDecoder->getConfiguration();
        long lfe = 0;
        if(x->f_AmbisonicsDecoder->getConfiguration() - nHps != 0.)
            lfe = 1;
        x->f_config_size = 3 + nHps + lfe;
        atom_setsym(x->f_configuration, gensym("irregular"));
        atom_setfloat(x->f_configuration+1, x->f_AmbisonicsDecoder->getConfiguration());
        atom_setsym(x->f_configuration+2, gensym("angles"));
        for(int i = 0; i < nHps; i++)
        {
            atom_setfloat(x->f_configuration+3+i, x->f_AmbisonicsDecoder->getLoudspeakerAngle(i));
        }
        if(lfe)
            atom_setsym(x->f_configuration+3+nHps, gensym("Lfe"));
    }

    HoaDecode_resize_outlet(x, numOutlet);
    
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("start"));
    
    return NULL;
}

/*******************************************************************/
void HoaDecode_resize_outlet(t_HoaDecode *x, long lastNumberOfOutlet)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
    
    t_object *b = NULL;
    object_obex_lookup(x, _sym_pound_B, (t_object **)&b);
    object_method(b, gensym("dynlet_begin"));
    
    if(lastNumberOfOutlet > x->f_AmbisonicsDecoder->getNumberOfOutputs())
    {
        for(int i = lastNumberOfOutlet; i > x->f_AmbisonicsDecoder->getNumberOfOutputs(); i--)
        {
            outlet_delete(outlet_nth((t_object*)x, i-1));
        }
    }
    else if(lastNumberOfOutlet < x->f_AmbisonicsDecoder->getNumberOfOutputs())
    {
        for(int i = lastNumberOfOutlet; i < x->f_AmbisonicsDecoder->getNumberOfOutputs(); i++)
        {
            outlet_append((t_object*)x, NULL, gensym("signal"));
        }
    }
    object_method(b, gensym("dynlet_end"));
    
    HoaDecode_reconnect_outlet(x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("start"));
}

void HoaDecode_reconnect_outlet(t_HoaDecode *x)
{
	t_object *patcher;
	t_object *decoder;
    t_object *object;
    t_object *line;
	t_max_err err;
    
	err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
	if (err != MAX_ERR_NONE)
		return;
	
	err = object_obex_lookup(x, gensym("#B"), (t_object **)&decoder);
	if (err != MAX_ERR_NONE)
		return;
	
    for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line))
    {
        if (jpatchline_get_box1(line) == decoder)
        {
            object = jpatchline_get_box2(line);
            long i = 0;
            while(jbox_getinlet((t_jbox *)object, i))
            {
                i++;
                if(i < x->f_AmbisonicsDecoder->getNumberOfOutputs())
                {
                    t_atom msg[4];
                    t_atom rv;
                    
                    atom_setobj(msg, decoder);
                    atom_setlong(msg + 1, i);
                    atom_setobj(msg + 2, object);
                    atom_setlong(msg + 3, i);
                    
                    object_method_typed(patcher , gensym("connect"), 4, msg, &rv);
                }
            }
        }
    }
}
