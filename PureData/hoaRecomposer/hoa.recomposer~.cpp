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

#include "hoa.recomposer.h"

extern "C" void setup_hoa0x2erecomposer_tilde(void)
{
    t_eclass* c;
    
    c = class_new("hoa.recomposer~", (method)hoa_recomposer_new, (method)hoa_recomposer_free, (short)sizeof(t_hoa_recomposer), 0L, A_GIMME, 0);
    
	class_dspinit(c);
    
	class_addmethod(c, (method)hoa_recomposer_dsp,     "dsp",      A_CANT, 0);
    class_addmethod(c, (method)hoa_recomposer_angle,   "angle",    A_GIMME,0);
    class_addmethod(c, (method)hoa_recomposer_wide,    "wide",      A_GIMME,0);

    CLASS_ATTR_LONG             (c, "mode", 0, t_hoa_recomposer, f_mode);
    CLASS_ATTR_ACCESSORS        (c, "mode", (method)NULL,(method)recomposer_setattr_mode);
	CLASS_ATTR_CATEGORY			(c, "mode", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "mode", 0, "1");
	CLASS_ATTR_LABEL			(c, "mode", 0, "Recomposition mode");
	CLASS_ATTR_FILTER_CLIP      (c, "mode", 0, 2);
	CLASS_ATTR_DEFAULT			(c, "mode", 0, "0");
    
    class_register(CLASS_BOX, c);
    hoa_recomposer_class = c;
}

void *hoa_recomposer_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_recomposer *x = NULL;
    t_dictionary *d;
	int	order = 4;
    int microphones = 10;
    
    x = (t_hoa_recomposer *)object_alloc(hoa_recomposer_class);
    
    order = atom_getint(argv);
    microphones = atom_getint(argv+1);
    x->f_mode = Hoa_Fixe;
    x->f_ambi_recomposer = new AmbisonicRecomposer(order, microphones, x->f_mode, sys_getblksize(), sys_getsr());
    dsp_setupjbox((t_jbox *)x, x->f_ambi_recomposer->getNumberOfInputs(), x->f_ambi_recomposer->getNumberOfOutputs());
    x->f_mode = x->f_ambi_recomposer->getMode();
    
	x->f_ob.z_misc = Z_NO_INPLACE;
    
    d = object_dictionaryarg(argc,argv);
    attr_dictionary_process(x, d);
	
   	return (x);
}

t_max_err recomposer_setattr_mode(t_hoa_recomposer *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av)
    {
        if (atom_gettype(av) == A_SYM)
        {
            if(atom_getsym(av) == gensym("fixe"))
                atom_setlong(av, Hoa_Fixe);
            else if(atom_getsym(av) == gensym("fisheye"))
                atom_setlong(av, Hoa_Fisheye);
            else if(atom_getsym(av) == gensym("free"))
                atom_setlong(av, Hoa_Free);
        }
        if (atom_gettype(av) == A_LONG)
        {
            long d = Tools::clip(long(atom_getlong(av)), 0, 2);
            if (d != x->f_mode)
            {
                
                long order = x->f_ambi_recomposer->getOrder();
                long microphones = x->f_ambi_recomposer->getNumberOfInputs();
                if(x->f_mode == Hoa_Fisheye)
                    microphones--;
                
                int dspState = canvas_suspend_dsp();
                delete x->f_ambi_recomposer;
                x->f_ambi_recomposer = new AmbisonicRecomposer(order, microphones, d, sys_getblksize(), sys_getsr());
                
                x->f_mode = x->f_ambi_recomposer->getMode();
                
                jbox_resize_inputs((t_jbox *)x, x->f_ambi_recomposer->getNumberOfInputs());
                
                canvas_resume_dsp(dspState);
            }
        }
	}
	return 0;
}

void hoa_recomposer_dsp(t_hoa_recomposer *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_ambi_recomposer->setVectorSize(maxvectorsize);

    if(x->f_ambi_recomposer->getMode() == Hoa_Free)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_recomposer_perform_free, 0, NULL);
    else if(x->f_ambi_recomposer->getMode() == Hoa_Fisheye)
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_recomposer_perform_fisheye, 0, NULL);
    else
        object_method(dsp, gensym("dsp_add"), x, (method)hoa_recomposer_perform, 0, NULL);
}

void hoa_recomposer_perform(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_recomposer->processFixe(ins, outs);
}

void hoa_recomposer_perform_fisheye(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_recomposer->processFisheye(ins, outs, ins[x->f_ambi_recomposer->getNumberOfInputs()-1]);
}

void hoa_recomposer_perform_free(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_ambi_recomposer->processFree(ins, outs);
}

void hoa_recomposer_angle(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2)
        x->f_ambi_recomposer->setMicrophoneAngle(atom_getint(av), atom_getfloat(av+1));
    else
    {
        for(int i = 0; i < ac; i++)
            x->f_ambi_recomposer->setMicrophoneAngle(i, atom_getfloat(av+i));
    }
    
}

void hoa_recomposer_wide(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac == 2)
        x->f_ambi_recomposer->setMicrophoneWide(atom_getint(av), atom_getfloat(av+1));
    else
    {
        for(int i = 0; i < ac; i++)
        {
            x->f_ambi_recomposer->setMicrophoneWide(i, atom_getfloat(av+i));
        }
    }
}


void hoa_recomposer_free(t_hoa_recomposer *x)
{
	dsp_freejbox((t_jbox *)x);
	delete(x->f_ambi_recomposer);
}
