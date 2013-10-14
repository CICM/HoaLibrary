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

#define MAX_SPEAKER 256

#include "../hoaLibrary/hoa.library_pd.h"

typedef struct _hoa_decoder
{
    t_jbox                f_ob;
    AmbisonicsMultiDecoder* f_ambi_decoder;
    double		f_angles_of_loudspeakers[MAX_SPEAKER];
    long        f_restitution_mode;
    long        f_pinnae;
} t_hoa_decoder;

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_free(t_hoa_decoder *x);

void hoa_decoder_dsp(t_hoa_decoder *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_decoder_perform(t_hoa_decoder *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_max_err decoder_setattr_angles(t_hoa_decoder *x, void *attr, long ac, t_atom *av);
t_max_err decoder_setattr_pinnae(t_hoa_decoder *x, void *attr, long ac, t_atom *av);
t_max_err decoder_setattr_restitution(t_hoa_decoder *x, void *attr, long ac, t_atom *av);

t_eclass *hoa_decoder_class;

extern "C" void setup_hoa0x2edecoder_tilde(void)
{
    t_eclass* c;
    
    c = class_new("hoa.decoder~", (method)hoa_decoder_new, (method)hoa_decoder_free, (short)sizeof(t_hoa_decoder), 0L, A_GIMME, 0);
    
	class_dspinit(c);
    class_addmethod(c, (method)hoa_decoder_dsp,           "dsp",          A_CANT,  0);
    
    CLASS_ATTR_DOUBLE_VARSIZE	(c, "angles",0,t_hoa_decoder,f_angles_of_loudspeakers,f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, decoder_setattr_angles);
	CLASS_ATTR_ORDER			(c, "angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "angles", 1);
    
    CLASS_ATTR_LONG				(c, "pinnae", 0 , t_hoa_decoder, f_pinnae);
    CLASS_ATTR_ACCESSORS		(c, "pinnae", NULL, decoder_setattr_pinnae);
	CLASS_ATTR_LABEL			(c, "pinnae", 0, "Number of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "pinnae", 1);
    CLASS_ATTR_DEFAULT          (c, "pinnae", 0, "8");
    
    CLASS_ATTR_LONG             (c, "restitution", 0, t_hoa_decoder, f_restitution_mode);
	CLASS_ATTR_CATEGORY			(c, "restitution", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "restitution", 0, "Restitution Mode");
	CLASS_ATTR_ACCESSORS		(c, "restitution", NULL, decoder_setattr_restitution);
    CLASS_ATTR_ORDER            (c, "restitution", 0, "6");
    CLASS_ATTR_SAVE             (c, "restitution", 1);
    
    class_register(CLASS_BOX, c);
    hoa_decoder_class = c;
}

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
    
    t_hoa_decoder *x = NULL;
    t_dictionary *d;
	int	order = 4;
    int mode = Hoa_Dec_Ambisonic;
    int number_of_loudspeakers = 10;
    char hrtfPath[256];
    sprintf(hrtfPath, "%s/HrtfDatabase/", canvas_getcurrentdir()->s_name);
    
    x = (t_hoa_decoder *)object_alloc(hoa_decoder_class);
    
    order = atom_getint(argv);
    if (atom_gettype(argv+1) == A_SYM)
    {
        if(atom_getsym(argv+1) == gensym("ambisonic"))
            mode = Hoa_Dec_Ambisonic;
        else if(atom_getsym(argv+1) == gensym("binaural"))
            mode = Hoa_Dec_Binaural;
        else if(atom_getsym(argv+1) == gensym("irregular"))
            mode = Hoa_Dec_Irregular;
    }
    else if(atom_gettype(argv+1) == A_LONG)
    {
        mode = pd_clip_minmax(atom_getlong(argv+1), 0, 2);
    }
    if(atom_gettype(argv+2) == A_LONG)
        number_of_loudspeakers = atom_getint(argv+2);
    
    x->f_ambi_decoder = new AmbisonicsMultiDecoder(order, number_of_loudspeakers, mode, Hoa_Small, hrtfPath, sys_getblksize(), sys_getsr());
    
    dsp_setupjbox((t_jbox *)x, x->f_ambi_decoder->getNumberOfInputs(), x->f_ambi_decoder->getNumberOfOutputs());
    
	x->f_ob.z_misc = Z_NO_INPLACE;
    
    d = object_dictionaryarg(argc,argv);
    attr_dictionary_process(x, d);
    
    return (x);
}

t_max_err decoder_setattr_angles(t_hoa_decoder *x, void *attr, long ac, t_atom *av)
{
    if (ac && av)
    {
        for(int i = 0; i < ac && i < x->f_ambi_decoder->getNumberOfLoudspeakers(); i++)
        {
            if(atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG)
                x->f_ambi_decoder->setLoudspeakerAngle(i, atom_getfloat(av+i));
        }
    }
    return 0;
}

t_max_err decoder_setattr_pinnae(t_hoa_decoder *x, void *attr, long ac, t_atom *av)
{
    if (atom_gettype(av) == A_LONG)
    {
        long d = Tools::clip(long(atom_getlong(av)), 0, 1);
        if(d != x->f_ambi_decoder->getPinnaeSize())
        {
            int dspState = canvas_suspend_dsp();
            x->f_ambi_decoder->setPinnaeSize(d);            
            canvas_resume_dsp(dspState);
        }
    }
    return 0;
}

t_max_err decoder_setattr_restitution(t_hoa_decoder *x, void *attr, long ac, t_atom *av)
{
    if (atom_gettype(av) == A_LONG)
    {
        long d = Tools::clip(long(atom_getlong(av)), 0, 1);
        if(d != x->f_ambi_decoder->getRestitutionMode())
        {
            int dspState = canvas_suspend_dsp();
            x->f_ambi_decoder->setRestitutionMode(d);
            canvas_resume_dsp(dspState);
        }
    }
    return 0;
}

void hoa_decoder_dsp(t_hoa_decoder *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_decoder->setVectorSize(maxvectorsize);
    x->f_ambi_decoder->setSamplingRate(samplerate);
    
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_decoder_perform, 0, NULL);
}

void hoa_decoder_perform(t_hoa_decoder *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_decoder->process(ins, outs);
}

void hoa_decoder_free(t_hoa_decoder *x)
{
    dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_decoder);
}
