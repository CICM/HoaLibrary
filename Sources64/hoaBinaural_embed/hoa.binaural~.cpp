/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#include "AmbisonicBinaural.hpp"
extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

typedef struct _HoaBinaural 
{
	t_pxobject			f_ob;			
	AmbisonicBinaural	*f_ambiBinaural;
	int ninput;
	int sum;
    t_symbol* pinnasizeAttr;
} t_HoaBinaural;


void *HoaBinaural_new(t_symbol *s, long argc, t_atom *argv);
void HoaBinaural_free(t_HoaBinaural *x);
void HoaBinaural_assist(t_HoaBinaural *x, void *b, long m, long a, char *s);
void HoaBinaural_optim(t_HoaBinaural *x, t_symbol *s, long argc, t_atom *argv);
t_max_err HoaBinaural_set_pinnasize(t_HoaBinaural *x, t_object *attr, long argc, t_atom *argv);

void HoaBinaural_dsp(t_HoaBinaural *x, t_signal **sp, short *count);
t_int *HoaBinaural_perform(t_int *w);

void HoaBinaural_dsp64(t_HoaBinaural *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaBinaural_perform64(t_HoaBinaural *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void *HoaBinaural_class;
    

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.binaural~", (method)HoaBinaural_new, (method)HoaBinaural_free, (long)sizeof(t_HoaBinaural), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaBinaural_dsp,			"dsp",		A_CANT,		0);
	class_addmethod(c, (method)HoaBinaural_dsp64,		"dsp64",	A_CANT,		0);
	class_addmethod(c, (method)HoaBinaural_assist,		"assist",	A_CANT,		0);
    
    CLASS_ATTR_SYM              (c,"pinnasize", 0, t_HoaBinaural, pinnasizeAttr);
    CLASS_ATTR_ACCESSORS		(c,"pinnasize", NULL, HoaBinaural_set_pinnasize);
	CLASS_ATTR_LABEL			(c,"pinnasize", 0,   "Pinna Size");
	CLASS_ATTR_CATEGORY			(c,"pinnasize", 0,   "Behavior");
    CLASS_ATTR_ENUM             (c,"pinnasize", 0, "small large");
	CLASS_ATTR_DEFAULT          (c,"pinnasize", 0,  "small");
    CLASS_ATTR_ORDER			(c,"pinnasize", 0,   "1");
    CLASS_ATTR_SAVE             (c,"pinnasize", 1);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaBinaural_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaBinaural_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaBinaural *x = NULL;
	int order = 3;
    std::string pinnaSize = "small";
    std::string filePath = "HrtfDatabase/";
    std::string absoluteHrtfFilePath = "";
    
    x = (t_HoaBinaural *)object_alloc((t_class *)HoaBinaural_class);
	if (x)
	{
        
		if(atom_gettype(argv) == A_LONG)
			order = atom_getlong(argv);
        
		if(atom_gettype(argv+1) == A_SYM)
			pinnaSize = atom_getsym(argv+1)->s_name;
        
        if (pinnaSize == "small")
        {
            pinnaSize = "Small";
        }
        else
        {
            pinnaSize = "Large";
        }
        
#ifdef __APPLE__
        // OSX only : access to the hoa.binaural~ bundle
        CFBundleRef hoaBinaural_bundle = CFBundleGetBundleWithIdentifier(CFSTR("com.cycling74.hoa-binaural-"));
        CFURLRef hoaBinaural_ref = CFBundleCopyBundleURL(hoaBinaural_bundle);
        UInt8 bundle_path[512];
        Boolean res = CFURLGetFileSystemRepresentation(hoaBinaural_ref, true, bundle_path, 512);
        assert(res);
        // Built the complete resource path
        absoluteHrtfFilePath = std::string((const char*)bundle_path) + std::string("/Contents/Resources/") + std::string(filePath);
#endif
        
#ifdef WIN32
        HMODULE handle = LoadLibrary("hoa.binaural~.mxe");
        if (handle) {
            // Get hoa.binaural~.mxe path
            char name[512];
            GetModuleFileName(handle, name, 512);
            string str_name = string(name);
            str_name = str_name.substr(0, str_name.find_last_of("\\"));
            // Built the complete resource path
            absoluteHrtfFilePath = string(str_name) + string("/Contents/Resources/") + string(filePath);
            FreeLibrary(handle);
        } else {
            post("Error : cannot locate hoa.binaural~.mxe...");
            absoluteHrtfFilePath = "";
        }
#endif
		
		x->f_ambiBinaural = new AmbisonicBinaural(order, sys_getsr(), sys_getblksize(), absoluteHrtfFilePath, pinnaSize);
        
        //post("filePath : %s", filePath.c_str());
        //post("absoluteFilePath : %s", absoluteFilePath.c_str());
		
		if(x->f_ambiBinaural->getisHrtfLoaded() == FALSE)
		{
            post("error : HRTF Database not loaded");
            //post("error HrtfPath : %s", x->f_ambiBinaural->getHrtfPath().c_str());
			return NULL;
		}
		
		dsp_setup((t_pxobject *)x, x->f_ambiBinaural->getParameters("numberOfInputs"));
		for (int i = 0; i < x->f_ambiBinaural->getParameters("numberOfOutputs"); i++) 
			outlet_new(x, "signal");
        
        x->pinnasizeAttr = gensym("small");
        attr_args_process(x, argc, argv);
	}
	return (x);
}

t_max_err HoaBinaural_set_pinnasize(t_HoaBinaural *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv && atom_gettype(argv) == A_SYM)
    {
        if (atom_getsym(argv) == gensym("large") || atom_getsym(argv) == gensym(" large"))
        {
            if(x->pinnasizeAttr != gensym("large"))
                x->f_ambiBinaural->setPinnaSize("Large");
             x->pinnasizeAttr = gensym("large");
        }
        else
        {
            if(x->pinnasizeAttr != gensym("small"))
                x->f_ambiBinaural->setPinnaSize("Small");
            x->pinnasizeAttr = gensym("small");
        }
    }
    return MAX_ERR_NONE;
}

void HoaBinaural_dsp64(t_HoaBinaural *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_ambiBinaural->setVectorSizeAndSamplingRate(maxvectorsize, samplerate);
    //post("HrtfPath : %s", x->f_ambiBinaural->getHrtfPath().c_str());
	object_method(dsp64, gensym("dsp_add64"), x, HoaBinaural_perform64, 0, NULL);
}

void HoaBinaural_perform64(t_HoaBinaural *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_ambiBinaural->process(ins, outs);
}

void HoaBinaural_dsp(t_HoaBinaural *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;
	
    x->f_ambiBinaural->setVectorSizeAndSamplingRate(sp[0]->s_n, sp[0]->s_sr);
	
	pointer_count = x->f_ambiBinaural->getParameters("numberOfOutputs") + x->f_ambiBinaural->getParameters("numberOfInputs") + 2;
	x->ninput = x->f_ambiBinaural->getParameters("numberOfInputs");
	x->sum = pointer_count + 1;
	sigvec  = (t_int **)malloc(pointer_count * sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)malloc(sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
	
	dsp_addv(HoaBinaural_perform, pointer_count, (void **)sigvec);

	free(sigvec);
	
}

t_int *HoaBinaural_perform(t_int *w)
{
	t_HoaBinaural *x	= (t_HoaBinaural *)(w[1]);
	t_float		**ins	= (t_float **)w+3;
	t_float		**outs	= (t_float **)w+3+x->ninput;
	
	x->f_ambiBinaural->process(ins, outs);

	return (w + x->sum);
}

void HoaBinaural_optim(t_HoaBinaural *x, t_symbol *s, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_SYM)
	{
		std::string optimMode = atom_getsym(argv)->s_name;
		x->f_ambiBinaural->setOptimMode(optimMode);
	}
}

void HoaBinaural_assist(t_HoaBinaural *x, void *b, long m, long a, char *s)
{
	int harmonicIndex = 0;
	if (m == ASSIST_INLET) 
	{
		if (a == 0)
			harmonicIndex = 0;
		else 
		{
			harmonicIndex = ((a - 1) / 2) + 1;
			if (a % 2 == 1) 
				harmonicIndex = -harmonicIndex;
		}
		sprintf(s,"(Signal) Harmonic %i", harmonicIndex);
	} 
	else 
	{
		if (a == 0)
			sprintf(s,"(Signal) Left headphone");
		else
			sprintf(s,"(Signal) Right headphone");
	}
}


void HoaBinaural_free(t_HoaBinaural *x) 
{
	dsp_free((t_pxobject *)x);
	delete x->f_ambiBinaural;
}

