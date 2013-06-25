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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicsBinaural.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

typedef struct _HoaBinaural 
{
	t_pxobject			f_ob;			
	AmbisonicsBinaural* f_ambiBinaural;
    t_symbol*           f_pinna_size;
    
} t_HoaBinaural;


void *HoaBinaural_new(t_symbol *s, long argc, t_atom *argv);
void HoaBinaural_free(t_HoaBinaural *x);
void HoaBinaural_assist(t_HoaBinaural *x, void *b, long m, long a, char *s);
t_max_err HoaBinaural_set_pinnasize(t_HoaBinaural *x, t_object *attr, long argc, t_atom *argv);

void HoaBinaural_dsp(t_HoaBinaural *x, t_signal **sp, short *count);
t_int *HoaBinaural_perform(t_int *w);

void HoaBinaural_dsp64(t_HoaBinaural *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void HoaBinaural_perform64(t_HoaBinaural *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *HoaBinaural_class;
    

int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("hoa.binaural~", (method)HoaBinaural_new, (method)HoaBinaural_free, (long)sizeof(t_HoaBinaural), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaBinaural_dsp,			"dsp",		A_CANT,		0);
	class_addmethod(c, (method)HoaBinaural_dsp64,		"dsp64",	A_CANT,		0);
	class_addmethod(c, (method)HoaBinaural_assist,		"assist",	A_CANT,		0);
    
    CLASS_ATTR_SYM              (c,"pinnasize", 0,      t_HoaBinaural, f_pinna_size);
    CLASS_ATTR_ACCESSORS		(c,"pinnasize", NULL,   HoaBinaural_set_pinnasize);
	CLASS_ATTR_LABEL			(c,"pinnasize", 0,      "Pinna Size");
	CLASS_ATTR_CATEGORY			(c,"pinnasize", 0,      "Behavior");
    CLASS_ATTR_ENUM             (c,"pinnasize", 0,      "small large");
	CLASS_ATTR_DEFAULT          (c,"pinnasize", 0,      "small");
    CLASS_ATTR_ORDER			(c,"pinnasize", 0,      "1");
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
    
    x = (t_HoaBinaural *)object_alloc(HoaBinaural_class);
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
		x->f_ambiBinaural = new AmbisonicsBinaural(order, absoluteHrtfFilePath, pinnaSize, sys_getsr(), sys_getblksize());
		
		dsp_setup((t_pxobject *)x, x->f_ambiBinaural->getNumberOfInputs());
		for (int i = 0; i < x->f_ambiBinaural->getNumberOfOutputs(); i++)
			outlet_new(x, "signal");
    
        x->f_ob.z_misc = Z_NO_INPLACE;
        attr_args_process(x, argc, argv);
	}
	return (x);
}

void HoaBinaural_dsp64(t_HoaBinaural *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_ambiBinaural->setVectorSize(maxvectorsize);
    x->f_ambiBinaural->setSamplingRate(samplerate);
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
	
    x->f_ambiBinaural->setVectorSize(sp[0]->s_n);
	x->f_ambiBinaural->setSamplingRate(sp[0]->s_sr);
	pointer_count = x->f_ambiBinaural->getNumberOfOutputs() + x->f_ambiBinaural->getNumberOfInputs() + 2;
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
	t_float		**outs	= (t_float **)w+3+x->f_ambiBinaural->getNumberOfInputs();
	
	x->f_ambiBinaural->process(ins, outs);

	return (w + x->f_ambiBinaural->getNumberOfOutputs() + x->f_ambiBinaural->getNumberOfInputs() + 3);
}

void HoaBinaural_assist(t_HoaBinaural *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"(Signal) Harmonic %ld", x->f_ambiBinaural->getHarmonicIndex(a));
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


t_max_err HoaBinaural_set_pinnasize(t_HoaBinaural *x, t_object *attr, long argc, t_atom *argv)
{

    if(argc && argv && atom_gettype(argv) == A_SYM)
    {
        if (atom_getsym(argv) == gensym("large") || atom_getsym(argv) == gensym(" large"))
            x->f_ambiBinaural->setPinnaSize("Large");
        else
            x->f_ambiBinaural->setPinnaSize("Small");
    }
    if(x->f_ambiBinaural->getPinnaSize() == "Small")
        x->f_pinna_size = gensym("small");
    else
        x->f_pinna_size = gensym("large");
    
    return MAX_ERR_NONE;
}

