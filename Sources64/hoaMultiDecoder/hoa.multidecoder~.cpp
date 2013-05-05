/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
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
    
    t_symbol*               f_mode;
    
    t_atom_long             f_number_of_loudspeakers;
    t_object*               f_offset_attr;
    double                  f_offset;
    t_symbol*               f_pinna_size;
    t_atom_long             f_n_ls;
    double                  f_configuration;
    double                  f_angle_of_ls[256];
} t_HoaDecode;

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv);
void HoaDecode_free(t_HoaDecode *x);
void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s);
void HoaDecode_resize_outlet(t_HoaDecode *x, long lastNumberOfOutlet);
void HoaDecode_reconnect_outlet(t_HoaDecode *x);

t_max_err mode_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err loudspeakers_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err offset_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err pinnasize_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err config_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaDecode_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.decoder~", (method)HoaDecode_new, (method)HoaDecode_free, (long)sizeof(t_HoaDecode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaDecode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_assist,	"assist",	A_CANT, 0);
    
    /* Attribut Global */
    CLASS_ATTR_SYM              (c, "mode", 0, t_HoaDecode, f_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c, "mode", 0, "ambisonics \" \"binaural \" \"irregular");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, mode_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    CLASS_ATTR_SAVE             (c, "mode", 1);
    
    /* Ambisonics Mode */
    CLASS_ATTR_LONG             (c, "loudspeakers", 0, t_HoaDecode, f_number_of_loudspeakers);
	CLASS_ATTR_CATEGORY			(c, "loudspeakers", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_ACCESSORS		(c, "loudspeakers", NULL, loudspeakers_set);
    CLASS_ATTR_ORDER            (c, "loudspeakers", 0, "2");
    CLASS_ATTR_SAVE             (c, "loudspeakers", 1);
    CLASS_ATTR_ATTR_PARSE       (c, "loudspeakers","invisible",USESYM(long),0,"0");
    CLASS_ATTR_ALIAS            (c, "loudspeakers", "ls");
    
    CLASS_ATTR_DOUBLE           (c, "offset", 0, t_HoaDecode, f_offset);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "offset", 0, "Loudspeakers Offset");
	CLASS_ATTR_ACCESSORS		(c, "offset", NULL, offset_set);
    CLASS_ATTR_ORDER            (c, "offset", 0, "3");
	CLASS_ATTR_SAVE             (c, "offset", 1);
    CLASS_ATTR_ATTR_PARSE       (c, "offset","invisible",USESYM(long),0,"0");
    
    /* Binaural */
    CLASS_ATTR_SYM              (c, "pinnasize", 0, t_HoaDecode, f_pinna_size);
	CLASS_ATTR_CATEGORY			(c, "pinnasize", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "pinnasize", 0, "Pinna Size");
    CLASS_ATTR_ENUM             (c, "pinnasize", 0, "small large");
	CLASS_ATTR_ACCESSORS		(c, "pinnasize", NULL, pinnasize_set);
    CLASS_ATTR_ORDER            (c, "pinnasize", 0, "4");
    CLASS_ATTR_SAVE             (c, "pinnasize", 1);
    CLASS_ATTR_ATTR_PARSE       (c, "pinnasize","invisible",USESYM(long),0,"0");
    
    /* Irregular */
    CLASS_ATTR_DOUBLE           (c, "config", 0, t_HoaDecode, f_configuration);
	CLASS_ATTR_CATEGORY			(c, "config", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "config", 0, "Loudspeakers Configuration");
	CLASS_ATTR_ACCESSORS		(c, "config", NULL, config_set);
    CLASS_ATTR_ORDER            (c, "config", 0, "5");
	CLASS_ATTR_SAVE             (c, "config", 1);
    CLASS_ATTR_ATTR_PARSE       (c, "config","invisible",USESYM(long),0,"0");
    
    CLASS_ATTR_DOUBLE_VARSIZE   (c, "angles", 0, t_HoaDecode, f_angle_of_ls, f_n_ls, 256);
	CLASS_ATTR_CATEGORY			(c, "angles", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "angles", 0, "Loudspeakers Angles");
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_set);
    CLASS_ATTR_ORDER            (c, "angles", 0, "6");
	CLASS_ATTR_SAVE             (c, "angles", 1);
    CLASS_ATTR_ATTR_PARSE       (c, "angles","invisible",USESYM(long),0,"0");
    
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
        
		x->f_mode = gensym("ambisonics");
        x->f_number_of_loudspeakers =  order * 2 + 2;
        x->f_configuration = 5.1;
        x->f_offset = 0.;
        x->f_n_ls = 5;
        x->f_pinna_size = gensym("small");
        
        for(int i = 0; i < x->f_n_ls; i++)
            x->f_angle_of_ls[i] = x->f_AmbisonicsDecoder->getLoudspeakerAngle(i);
        
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

t_max_err mode_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
    
    long numOutlet = x->f_AmbisonicsDecoder->getNumberOfOutputs();
	if(atom_gettype(argv) == A_SYM)
	{
        if(atom_getsym(argv) == gensym("binaural") || atom_getsym(argv) == gensym(" binaural"))
        {
            x->f_AmbisonicsDecoder->setMode(Hoa_Binaural);
            x->f_mode = gensym("binaural");
        }
        else if(atom_getsym(argv) == gensym("irregular") || atom_getsym(argv) == gensym(" irregular"))
        {
            x->f_AmbisonicsDecoder->setMode(Hoa_Restitution);
            x->f_mode = gensym("irregular");
        }
        else
        {
            x->f_AmbisonicsDecoder->setMode(Hoa_Ambisonics);
            x->f_mode = gensym("ambisonics");;
        }
	}

    HoaDecode_resize_outlet(x, numOutlet);
    
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("start"));
    
    return NULL;
}

t_max_err loudspeakers_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
    
    long numOutlet = x->f_AmbisonicsDecoder->getNumberOfOutputs();
    
    if(atom_gettype(argv) == A_LONG)
        x->f_AmbisonicsDecoder->setNumberOfLoudspeakers(atom_getlong(argv));
    else if(atom_gettype(argv) == A_FLOAT)
        x->f_AmbisonicsDecoder->setNumberOfLoudspeakers(atom_getfloat(argv));
    
    x->f_number_of_loudspeakers = x->f_AmbisonicsDecoder->getNumberOfLoudspeakers();
    HoaDecode_resize_outlet(x, numOutlet);
    
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("start"));
    
    return NULL;
}

t_max_err offset_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_FLOAT)
        x->f_AmbisonicsDecoder->setOffset(atom_getfloat(argv));
    else if(atom_gettype(argv) == A_LONG)
        x->f_AmbisonicsDecoder->setOffset(atom_getlong(argv));
        
    x->f_offset = x->f_AmbisonicsDecoder->getOffset();
    return NULL;
}

t_max_err pinnasize_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(atom_gettype(argv) == A_SYM && (atom_getsym(argv) == gensym("large") || atom_getsym(argv) == gensym(" large")))
        x->f_AmbisonicsDecoder->setPinnaSize(Hoa_Large);
    else
        x->f_AmbisonicsDecoder->setPinnaSize(Hoa_Small);

    if(x->f_AmbisonicsDecoder->getPinnaSize() == Hoa_Large)
        x->f_pinna_size = gensym("large");
    else
        x->f_pinna_size = gensym("small");
    return NULL;
}

t_max_err config_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("stop"));
    
    long numOutlet = x->f_AmbisonicsDecoder->getNumberOfOutputs();
    
    if(atom_gettype(argv) == A_FLOAT)
        x->f_AmbisonicsDecoder->setConfiguration(atom_getfloat(argv));
    else if(atom_gettype(argv) == A_LONG)
        x->f_AmbisonicsDecoder->setConfiguration(atom_getlong(argv));
    
    x->f_configuration = x->f_AmbisonicsDecoder->getConfiguration();
    x->f_n_ls = x->f_configuration;
    for(int i = 0; i < x->f_n_ls; i++)
    {
        x->f_angle_of_ls[i] = x->f_AmbisonicsDecoder->getLoudspeakerAngle(i);
    }
    object_attr_touch((t_object*)x, gensym("angles"));
    
    HoaDecode_resize_outlet(x, numOutlet);
    
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("start"));
    return NULL;
}

t_max_err angles_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        for(int i = 0; i < argc; i++)
        {
            if(atom_gettype(argv+i) == A_FLOAT)
                x->f_AmbisonicsDecoder->setLoudspeakerAngle(i, atom_getfloat(argv+i));
            else if(atom_gettype(argv+i) == A_LONG)
                x->f_AmbisonicsDecoder->setLoudspeakerAngle(i, atom_getlong(argv+i));
        }
    }
    
    for(int i = 0; i < x->f_n_ls; i++)
    {
        x->f_angle_of_ls[i] = x->f_AmbisonicsDecoder->getLoudspeakerAngle(i);
    }
    
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
