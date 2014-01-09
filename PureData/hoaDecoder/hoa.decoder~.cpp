/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

extern "C"
{
#include "../../../PdEnhanced/Sources/cicm_wrapper.h"
}

#include "../../Sources/HoaLibrary.h"

#define MAX_SPEAKER 256

typedef struct _hoa_decoder
{
    t_edspobj               f_ob;
    AmbisonicsMultiDecoder* f_ambi_decoder;
    double                  f_angles_of_loudspeakers[MAX_SPEAKER];
    long                    f_restitution_mode;
    long                    f_pinnae;
    long                    f_number_of_loudspeakers;
} t_hoa_decoder;

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv);
void hoa_decoder_free(t_hoa_decoder *x);

void hoa_decoder_dsp(t_hoa_decoder *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_decoder_perform(t_hoa_decoder *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_pd_err decoder_setattr_angles(t_hoa_decoder *x, void *attr, long ac, t_atom *av);
t_pd_err decoder_setattr_pinnae(t_hoa_decoder *x, void *attr, long ac, t_atom *av);
t_pd_err decoder_setattr_restitution(t_hoa_decoder *x, void *attr, long ac, t_atom *av);

t_eclass *hoa_decoder_class;

extern "C" void setup_hoa0x2edecoder_tilde(void)
{
    t_eclass* c;
    
    c = eclass_new("hoa.decoder~", (method)hoa_decoder_new, (method)hoa_decoder_free, (short)sizeof(t_hoa_decoder), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
    eclass_addmethod(c, (method)hoa_decoder_dsp,           "dsp",          A_CANT,  0);
    
    CLASS_ATTR_DOUBLE_VARSIZE	(c, "angles",0,t_hoa_decoder,f_angles_of_loudspeakers,f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, decoder_setattr_angles);
	CLASS_ATTR_ORDER			(c, "angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles of Loudspeakers");
    
    CLASS_ATTR_LONG				(c, "pinnae", 0 , t_hoa_decoder, f_pinnae);
    CLASS_ATTR_ACCESSORS		(c, "pinnae", NULL, decoder_setattr_pinnae);
	CLASS_ATTR_LABEL			(c, "pinnae", 0, "Pinnae Size");
    
    CLASS_ATTR_LONG             (c, "restitution", 0, t_hoa_decoder, f_restitution_mode);
	CLASS_ATTR_CATEGORY			(c, "restitution", 0, "Behavior");
    CLASS_ATTR_LABEL            (c, "restitution", 0, "Restitution Mode");
	CLASS_ATTR_ACCESSORS		(c, "restitution", NULL, decoder_setattr_restitution);
    CLASS_ATTR_ORDER            (c, "restitution", 0, "6");
    
    eclass_register(CLASS_BOX, c);
    erouter_add_libary(gensym("hoa"), "hoa.library by Julien Colafrancesco, Pierre Guillot & Eliott Paris", "© 2012 - 2014  CICM | Paris 8 University", "Version 1.1");
    hoa_decoder_class = c;
}

void *hoa_decoder_new(t_symbol *s, long argc, t_atom *argv)
{
    
    t_hoa_decoder *x = NULL;
    t_binbuf *d;
	int	order = 4;
    int mode = Hoa_Dec_Ambisonic;
    int number_of_loudspeakers = 10;
    char hrtfPath[256];
   
    if (!(d = binbuf_via_atoms(argc,argv)))
		return NULL;
    
    x = (t_hoa_decoder *)eobj_new(hoa_decoder_class);
    
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
    
    sprintf(hrtfPath, "%s/HrtfDatabase/", canvas_getcurrentdir()->s_name);
    x->f_ambi_decoder = new AmbisonicsMultiDecoder(order, number_of_loudspeakers, mode, Hoa_Small, hrtfPath, sys_getblksize(), sys_getsr());

    eobj_dspsetup(x, x->f_ambi_decoder->getNumberOfInputs(), x->f_ambi_decoder->getNumberOfOutputs());
    
	x->f_ob.d_misc = E_NO_INPLACE;
    
    ebox_attrprocess_viabinbuf(x, d);
    
    return (x);
}

t_pd_err decoder_setattr_angles(t_hoa_decoder *x, void *attr, long ac, t_atom *av)
{
    double* angles = new double[(int)pd_clip_min(ac, 1)];
    if (ac && av)
    {
        for(int i = 0; i < ac && i < x->f_ambi_decoder->getNumberOfLoudspeakers(); i++)
        {
            if(atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG)
                angles[i] = atom_getfloat(av+i);
            else
                angles[i] = 0.;
                
        }
        x->f_ambi_decoder->setLoudspeakersAngles(angles, ac);
    }
    for(int i = 0; i < x->f_ambi_decoder->getNumberOfLoudspeakers(); i++)
    {
        x->f_angles_of_loudspeakers[i] = x->f_ambi_decoder->getLoudspeakerAngle(i);
    }
    
    
    free(angles);
    return 0;
}

t_pd_err decoder_setattr_pinnae(t_hoa_decoder *x, void *attr, long ac, t_atom *av)
{
    long d = 0;
    if(atom_gettype(av) == A_LONG)
    {
        d = Tools::clip(long(atom_getlong(av)), 0, 1);
    }
    if(atom_gettype(av) == A_SYM)
    {
        if(atom_getsym(av) == gensym("large"))
           d = 1;
        else
           d = 0;
    }
    if(d != x->f_ambi_decoder->getPinnaeSize())
    {
        int dspState = canvas_suspend_dsp();
        x->f_ambi_decoder->setPinnaeSize(d);
        canvas_resume_dsp(dspState);
    }
    
    return 0;
}

t_pd_err decoder_setattr_restitution(t_hoa_decoder *x, void *attr, long ac, t_atom *av)
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
    eobj_dspfree(x);
	delete(x->f_ambi_decoder);
}
