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
	#include "z_dsp.h"
}


typedef struct _HoaDecode 
{
	t_pxobject				f_ob;			
	AmbisonicsMultiDecoder  *f_AmbisonicsDecoder;

	int						f_ninput;
	int						f_noutput;
    
    t_symbol*               f_mode;
    t_symbol*               f_pinna_size;
    double                  f_offset;
    long                    f_number_of_loudspeakers;
    long                    f_lfe;
    
} t_HoaDecode;

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv);
void HoaDecode_free(t_HoaDecode *x);
void HoaDecode_assist(t_HoaDecode *x, void *b, long m, long a, char *s);
void HoaDecode_resize_outlet(t_HoaDecode *x, long lastNumberOfOutlet);
void HoaDecode_reconnect_outlet(t_HoaDecode *x);

void HoaDecode_save(t_HoaDecode *x, t_dictionary *d);

t_max_err mode_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);
t_max_err config_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv);

void HoaDecode_dsp64(t_HoaDecode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaDecode_perform64(t_HoaDecode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaDecode_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.decoder~", (method)HoaDecode_new, (method)HoaDecode_free, (long)sizeof(t_HoaDecode), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaDecode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)HoaDecode_assist,	"assist",	A_CANT, 0);
    class_addmethod(c, (method)HoaDecode_save,      "save",     A_CANT, 0);
    
    CLASS_ATTR_SYM              (c, "mode", 0, t_HoaDecode, f_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "mode", 0, "Mode");
    CLASS_ATTR_ENUM             (c, "mode", 0, "ambisonics \" \"binaural \" \"irregular");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, mode_set);
    CLASS_ATTR_ORDER            (c, "mode", 0, "1");
    
    CLASS_ATTR_LONG             (c, "ls", 0, t_HoaDecode, f_number_of_loudspeakers);
	CLASS_ATTR_CATEGORY			(c, "ls", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "ls", 0, "Number of Loudspeakers");
	CLASS_ATTR_ACCESSORS		(c, "ls", NULL, config_set);
    CLASS_ATTR_ORDER            (c, "ls", 0, "2");
    
    CLASS_ATTR_SYM              (c, "pinnasize", 0, t_HoaDecode, f_pinna_size);
	CLASS_ATTR_CATEGORY			(c, "pinnasize", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "pinnasize", 0, "Pinna Size");
    CLASS_ATTR_ENUM             (c, "pinnasize", 0, "small large");
	CLASS_ATTR_DEFAULT			(c, "pinnasize", 0, "small");
    CLASS_ATTR_ORDER            (c, "pinnasize", 0, "3");
    
    CLASS_ATTR_DOUBLE           (c, "offset", 0, t_HoaDecode, f_offset);
	CLASS_ATTR_CATEGORY			(c, "offset", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "offset", 0, "Loudspeakers Offset");
	CLASS_ATTR_ACCESSORS		(c, "offset", NULL, config_set);
    CLASS_ATTR_ORDER            (c, "offset", 0, "4");
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaDecode_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaDecode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaDecode *x = NULL;
    t_dictionary *d;
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
        
		x->f_AmbisonicsDecoder	= new AmbisonicsMultiDecoder(order, absoluteHrtfFilePath, "small", sys_getblksize(), sys_getsr(), Hoa_Ambisonics, order * 2 + 2);
		x->f_mode = gensym("ambisonics");
        x->f_number_of_loudspeakers =  order * 2 + 2;
        x->f_offset = 0.;
        x->f_pinna_size = gensym("small");
        
		dsp_setup((t_pxobject *)x, x->f_AmbisonicsDecoder->getNumberOfInputs());
		for (int i = 0; i < x->f_AmbisonicsDecoder->getNumberOfOutputs(); i++) 
			outlet_new(x, "signal");
		
        attr_args_process(x, argc, argv);
		x->f_ob.z_misc = Z_NO_INPLACE;
	}
	return (x);
}

void HoaDecode_save(t_HoaDecode *x, t_dictionary *d)
{
    post("saved");
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
	{
		sprintf(s,"(Signal) Harmonic %ld", x->f_AmbisonicsDecoder->getHarmonicIndex(a));
	}
	else
    {
        if(x->f_AmbisonicsDecoder->getMode() == Hoa_Ambisonics)
            sprintf(s,"(Signal) Speaker %ld", a);
        else if(x->f_AmbisonicsDecoder->getMode() == Hoa_Binaural)
        {
            if(a == 0)
                sprintf(s,"(Signal) Left headphone");
            else if(a == 1)
                sprintf(s,"(Signal) Right headphone");
        }
        else if(x->f_AmbisonicsDecoder->getMode() == Hoa_Restitution)
        {
            /* A voir */
            double config = x->f_AmbisonicsDecoder->getConfiguration();
            if(config - (long)config != 0.)
            {
                if(a == x->f_AmbisonicsDecoder->getNumberOfOutputs() - 1)
                      sprintf(s,"(Signal) Lfe channel");
            }
            else if(x->f_AmbisonicsDecoder->getNumberOfOutputs() == 2)
                sprintf(s,"(Signal) Speaker %ld", a);
            
        }
    }
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
            x->f_mode = gensym("ambisonics");
        }
	}
    else if(atom_gettype(argv) == A_LONG)
    {
        if(atom_getlong(argv) == 1)
        {
            x->f_AmbisonicsDecoder->setMode(Hoa_Binaural);
            x->f_mode = gensym("binaural");
        }
        else if(atom_getlong(argv) == 2)
        {
            x->f_AmbisonicsDecoder->setMode(Hoa_Restitution);
            x->f_mode = gensym("irregular");
        }
        else
        {
            x->f_AmbisonicsDecoder->setMode(Hoa_Ambisonics);
            x->f_mode = gensym("ambisonics");
        }
    }

    HoaDecode_resize_outlet(x, numOutlet);
    
    if(dspState)
        object_method(gensym("dsp")->s_thing, gensym("start"));
    
    return NULL;
}

t_max_err config_set(t_HoaDecode *x, t_object *attr, long argc, t_atom *argv)
{
    return NULL;
}

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
	t_object *jpatcher;
	t_object *jbox;
	t_object *mybox;
	t_max_err err;
    
	err = object_obex_lookup(x, gensym("#P"), (t_object **)&jpatcher);
	if (err != MAX_ERR_NONE)
		return;
	
	err = object_obex_lookup(x, gensym("#B"), (t_object **)&mybox);
	if (err != MAX_ERR_NONE)
		return;
	
	jbox = jpatcher_get_firstobject(jpatcher); // get the first BOX in the object list
    
	while(jbox)
    {
        long i = 0;
        while(jbox_getinlet((t_jbox *)jbox, i))
        {
            i++;
        }
        post("%ld", i);
		
		jbox = jbox_get_nextobject(jbox);
	}
}
