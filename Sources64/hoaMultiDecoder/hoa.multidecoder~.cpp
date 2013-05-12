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

#define MAX_SPEAKER 256

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
    
    t_atom_long             f_number_of_ambisonics_loudspeakers;
    double                  f_offset_of_ambisonics_loudspeakers;
    
    t_symbol*               f_pinna_size;
    
    t_atom_long             f_number_of_irregular_loudspeakers;
    double                  f_configuration_of_irregular_loudspeakers;
    double                  f_angles_of_irregular_loudspeakers[MAX_SPEAKER];
    t_symbol*               f_resitution_mode;
} t_HoaDecode;

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv);
void HoaDecode_free(t_HoaDecode *x);
void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s);
void HoaDecode_resize_outlet(t_HoaDecode *x, long lastNumberOfOutlet);
void HoaDecode_reconnect_outlet(t_HoaDecode *x);
void HoaDecode_disconnect_outlet(t_HoaDecode *x);
void HoaDecode_send_configuration(t_HoaDecode *x);
void HoaDecode_send_angles(t_HoaDecode *x);

t_max_err HoaDecode_notify(t_HoaDecode *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

t_max_err configuration_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err loudspeakers_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err offset_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err pinnaesize_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err config_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err restitution_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaDecode_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.decoder~", (method)HoaDecode_new, (method)HoaDecode_free, (long)sizeof(t_HoaDecode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaDecode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_assist,	"assist",	A_CANT, 0);
    class_addmethod(c, (method)HoaDecode_notify,    "notify",   A_CANT, 0);
    
    /* Attribut Global */
    CLASS_ATTR_SYM              (c, "mode", 0, t_HoaDecode, f_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c, "mode", 0, "ambisonics \" \"binaural \" \"irregular");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, configuration_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    CLASS_ATTR_SAVE             (c, "mode", 1);

    /* Ambisonics Mode */
    CLASS_ATTR_LONG             (c, "loudspeakers", 0, t_HoaDecode, f_number_of_ambisonics_loudspeakers);
	CLASS_ATTR_CATEGORY			(c, "loudspeakers", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_ACCESSORS		(c, "loudspeakers", NULL, loudspeakers_set);
    CLASS_ATTR_ORDER            (c, "loudspeakers", 0, "2");
    CLASS_ATTR_SAVE             (c, "loudspeakers", 1);
    CLASS_ATTR_ALIAS            (c, "loudspeakers", "ls");
    
    CLASS_ATTR_DOUBLE           (c, "offset", 0, t_HoaDecode, f_offset_of_ambisonics_loudspeakers);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "offset", 0, "Offset of Loudspeakers");
	CLASS_ATTR_ACCESSORS		(c, "offset", NULL, offset_set);
    CLASS_ATTR_ORDER            (c, "offset", 0, "3");
	CLASS_ATTR_SAVE             (c, "offset", 1);
    
    /* Binaural */
    CLASS_ATTR_SYM              (c, "pinnaesize", 0, t_HoaDecode, f_pinna_size);
	CLASS_ATTR_CATEGORY			(c, "pinnaesize", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "pinnaesize", 0, "Pinnae Size");
    CLASS_ATTR_ENUM             (c, "pinnaesize", 0, "small large");
	CLASS_ATTR_ACCESSORS		(c, "pinnaesize", NULL, pinnaesize_set);
    CLASS_ATTR_ORDER            (c, "pinnaesize", 0, "4");
    CLASS_ATTR_SAVE             (c, "pinnaesize", 1);
    
    /* Irregular */
    CLASS_ATTR_DOUBLE           (c, "config", 0, t_HoaDecode, f_configuration_of_irregular_loudspeakers);
	CLASS_ATTR_CATEGORY			(c, "config", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "config", 0, "Configuration");
	CLASS_ATTR_ACCESSORS		(c, "config", NULL, config_set);
    CLASS_ATTR_ORDER            (c, "config", 0, "5");
	CLASS_ATTR_SAVE             (c, "config", 1);
    
    CLASS_ATTR_DOUBLE_VARSIZE   (c, "angles", 0, t_HoaDecode, f_angles_of_irregular_loudspeakers, f_number_of_irregular_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_CATEGORY			(c, "angles", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_set);
    CLASS_ATTR_ORDER            (c, "angles", 0, "6");
	CLASS_ATTR_SAVE             (c, "angles", 1);
    CLASS_ATTR_ALIAS            (c, "angles", "ls_angles");
    
    CLASS_ATTR_SYM              (c, "restitution", 0, t_HoaDecode, f_resitution_mode);
	CLASS_ATTR_CATEGORY			(c, "restitution", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "restitution", 0, "Restituion Mode");
    CLASS_ATTR_ENUM             (c, "restitution", 0, "panning projection");
	CLASS_ATTR_ACCESSORS		(c, "restitution", NULL, restitution_set);
    CLASS_ATTR_ORDER            (c, "restitution", 0, "7");
    CLASS_ATTR_SAVE             (c, "restitution", 1);
    
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
		x->f_AmbisonicsDecoder	= new AmbisonicsMultiDecoder(order, absoluteHrtfFilePath, Hoa_Small, sys_getblksize(), sys_getsr(), Hoa_Ambisonics, order * 2 + 2, 5.1);
        
        /* Base Attributes */
		x->f_mode = gensym("ambisonics");
        x->f_number_of_ambisonics_loudspeakers =  order * 2 + 2;
        x->f_configuration_of_irregular_loudspeakers = 5.1;
        x->f_offset_of_ambisonics_loudspeakers = 0.;
        x->f_number_of_irregular_loudspeakers = 5;
        x->f_pinna_size = gensym("small");
        x->f_resitution_mode = gensym("panning");
        
        for(int i = 0; i < x->f_number_of_irregular_loudspeakers; i++)
            x->f_angles_of_irregular_loudspeakers[i] = x->f_AmbisonicsDecoder->getLoudspeakerAngle(i);
        
        /* DSP Setup */
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsDecoder->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsDecoder->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
        attr_args_process(x, argc, argv);
		x->f_ob.z_misc = Z_NO_INPLACE;
        
        object_attach_byptr_register(x, x, CLASS_BOX);
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

t_max_err HoaDecode_notify(t_HoaDecode *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	;
	return 0;
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

t_max_err configuration_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
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
            object_attr_addattr_parse((t_object*)x, "config", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "angles", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "offset", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "pinnaesize", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "loudspeakers", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "restitution", "invisible", USESYM(long), 1, "1");
            
        }
        else if(atom_getsym(argv) == gensym("irregular") || atom_getsym(argv) == gensym(" irregular"))
        {
            x->f_AmbisonicsDecoder->setMode(Hoa_Restitution);
            x->f_mode = gensym("irregular");
            object_attr_addattr_parse((t_object*)x, "config", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "angles", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "offset", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "pinnaesize", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "loudspeakers", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "restitution", "invisible", USESYM(long), 1, "0");
        }
        else
        {
            x->f_AmbisonicsDecoder->setMode(Hoa_Ambisonics);
            x->f_mode = gensym("ambisonics");
            object_attr_addattr_parse((t_object*)x, "config", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "angles", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "offset", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "pinnaesize", "invisible", USESYM(long), 1, "1");
            object_attr_addattr_parse((t_object*)x, "loudspeakers", "invisible", USESYM(long), 1, "0");
            object_attr_addattr_parse((t_object*)x, "restitution", "invisible", USESYM(long), 1, "1");
        }
	}

    HoaDecode_resize_outlet(x, numOutlet);
    
    return NULL;
}

/* Ambisonics */
t_max_err loudspeakers_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Ambisonics)
    {
        int dspState = sys_getdspobjdspstate((t_object*)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        long numOutlet = x->f_AmbisonicsDecoder->getNumberOfOutputs();
        
        if(atom_gettype(argv) == A_LONG)
            x->f_AmbisonicsDecoder->setNumberOfLoudspeakers(atom_getlong(argv));
        else if(atom_gettype(argv) == A_FLOAT)
            x->f_AmbisonicsDecoder->setNumberOfLoudspeakers(atom_getfloat(argv));
        
        HoaDecode_resize_outlet(x, numOutlet);
    }
    x->f_number_of_ambisonics_loudspeakers = x->f_AmbisonicsDecoder->getNumberOfLoudspeakers();
    return NULL;
}

t_max_err offset_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Ambisonics)
    {
        if(atom_gettype(argv) == A_FLOAT)
            x->f_AmbisonicsDecoder->setOffset(atom_getfloat(argv));
        else if(atom_gettype(argv) == A_LONG)
            x->f_AmbisonicsDecoder->setOffset(atom_getlong(argv));
    }        
    x->f_offset_of_ambisonics_loudspeakers = x->f_AmbisonicsDecoder->getOffset();
    
    return NULL;
}

/* Binaural */
t_max_err pinnaesize_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Binaural)
    {
        if(atom_gettype(argv) == A_SYM && (atom_getsym(argv) == gensym("large") || atom_getsym(argv) == gensym(" large")))
            x->f_AmbisonicsDecoder->setPinnaeSize(Hoa_Large);
        else
            x->f_AmbisonicsDecoder->setPinnaeSize(Hoa_Small);
    }

    if(x->f_AmbisonicsDecoder->getPinnaeSize() == Hoa_Large)
        x->f_pinna_size = gensym("large");
    else
        x->f_pinna_size = gensym("small");
    return NULL;
}

/* Irregular */

t_max_err restitution_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution && atom_gettype(argv) == A_SYM)
    {
        if(atom_getsym(argv) == gensym("projection") || atom_getsym(argv) == gensym(" projection"))
            x->f_AmbisonicsDecoder->setRestitutionMode(Hoa_Microphone_Simulation);
        else
            x->f_AmbisonicsDecoder->setRestitutionMode(Hoa_Amplitude_Panning);
    }
    if(x->f_AmbisonicsDecoder->getRestitutionMode() == Hoa_Microphone_Simulation)
        x->f_resitution_mode = gensym("projection");
    else
        x->f_resitution_mode = gensym("panning");
    return NULL;
}

t_max_err config_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution)
    {
        long standard = 1;
        int dspState = sys_getdspobjdspstate((t_object*)x);
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        long numOutlet = x->f_AmbisonicsDecoder->getNumberOfOutputs();
        if(argc == 2 && atom_gettype(argv+1) == A_LONG && atom_getlong(argv+1) == 0)
            standard = 0;
        if(atom_gettype(argv) == A_FLOAT)
            x->f_AmbisonicsDecoder->setConfiguration(atom_getfloat(argv), standard);
        else if(atom_gettype(argv) == A_LONG)
            x->f_AmbisonicsDecoder->setConfiguration(atom_getlong(argv), standard);
        
        HoaDecode_resize_outlet(x, numOutlet);
    }
    x->f_configuration_of_irregular_loudspeakers = x->f_AmbisonicsDecoder->getConfiguration();
    x->f_number_of_irregular_loudspeakers = x->f_configuration_of_irregular_loudspeakers;
    for(int i = 0; i < x->f_number_of_irregular_loudspeakers; i++)
    {
        x->f_angles_of_irregular_loudspeakers[i] = x->f_AmbisonicsDecoder->getLoudspeakerAngle(i);
    }
    object_attr_touch((t_object*)x, gensym("angles"));
    return NULL;
}

t_max_err angles_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution)
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
    }
    
    for(int i = 0; i < x->f_number_of_irregular_loudspeakers; i++)
    {
        x->f_angles_of_irregular_loudspeakers[i] = x->f_AmbisonicsDecoder->getLoudspeakerAngle(i);
    }
    HoaDecode_send_angles(x);
    
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
    
    HoaDecode_send_configuration(x);
    HoaDecode_reconnect_outlet(x);
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
            
            for(int i = 0; jbox_getinlet((t_jbox *)object, i) != NULL && i < x->f_AmbisonicsDecoder->getNumberOfOutputs(); i++)
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

void HoaDecode_send_configuration(t_HoaDecode *x)
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
            if(object_classname(jbox_get_object(object)) == gensym("hoa.meter~") || object_classname(jbox_get_object(object)) == gensym("hoa.gain~"))
            {
                long    argc = 1;
                t_atom *argv = new t_atom[1];
                if(x->f_AmbisonicsDecoder->getMode() == Hoa_Ambisonics)
                    atom_setlong(argv, x->f_AmbisonicsDecoder->getNumberOfLoudspeakers());
                else if(x->f_AmbisonicsDecoder->getMode() == Hoa_Binaural)
                    atom_setlong(argv, x->f_AmbisonicsDecoder->getNumberOfOutputs());
                else if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution)
                    atom_setlong(argv, x->f_AmbisonicsDecoder->getConfiguration());
                
                object_method_typed(jbox_get_object(object), gensym("loudspeakers"), argc, argv, NULL);
                
                free(argv);
                
                argc = x->f_AmbisonicsDecoder->getNumberOfOutputs();
                argv = new t_atom[argc];
                
                for(int i = 0; i < argc; i++)
                    atom_setfloat(argv+i, x->f_AmbisonicsDecoder->getLoudspeakerAngle(i));
                
                object_method_typed(jbox_get_object(object), gensym("angles"), argc, argv, NULL);
                free(argv);
            }
            if(object_classname(jbox_get_object(object)) == gensym("hoa.gain~"))
            {
                long argc = 1;
                t_atom argv[1];
                atom_setlong(argv, x->f_AmbisonicsDecoder->getNumberOfOutputs());
                object_method_typed(jbox_get_object(object), gensym("channels"), argc, argv, NULL);
            }
        }
    }
}

void HoaDecode_send_angles(t_HoaDecode *x)
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
            if(object_classname(jbox_get_object(object)) == gensym("hoa.meter~") || object_classname(jbox_get_object(object)) == gensym("hoa.gain~"))
            {                
                long    argc = x->f_AmbisonicsDecoder->getNumberOfOutputs();
                t_atom *argv = new t_atom[argc];
                
                for(int i = 0; i < argc; i++)
                    atom_setfloat(argv+i, x->f_AmbisonicsDecoder->getLoudspeakerAngle(i));
                
                object_method_typed(jbox_get_object(object), gensym("angles"), argc, argv, NULL);
                free(argv);
            }
        }
    }
}

void HoaDecode_disconnect_outlet(t_HoaDecode *x)
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
            if(jpatchline_get_inletnum(line) != 0 && jpatchline_get_outletnum(line) != 0)
            {
                t_atom msg[4];
                t_atom rv;
                    
                atom_setobj(msg, decoder);
                atom_setlong(msg + 1, jpatchline_get_outletnum(line));
                atom_setobj(msg + 2, object);
                atom_setlong(msg + 3, jpatchline_get_inletnum(line));
                    
                object_method_typed(patcher , gensym("disconnect"), 4, msg, &rv);
            }
        }
    }
}
