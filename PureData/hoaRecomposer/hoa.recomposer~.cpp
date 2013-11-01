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

#include "../hoaLibrary/hoa.library_pd.h"

typedef struct _hoa_recomposer
{
    t_jbox              f_ob;
    AmbisonicRecomposer *f_ambi_recomposer;
} t_hoa_recomposer;

void *hoa_recomposer_new(t_symbol *s, long argc, t_atom *argv);
void hoa_recomposer_free(t_hoa_recomposer *x);

void hoa_recomposer_angle(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av);
void hoa_recomposer_wide(t_hoa_recomposer *x, t_symbol *s, short ac, t_atom *av);

t_eclass *hoa_recomposer_class;

void hoa_recomposer_dsp(t_hoa_recomposer *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_recomposer_perform(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_recomposer_perform_fisheye(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_recomposer_perform_free(t_hoa_recomposer *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

extern "C" void setup_hoa0x2erecomposer_tilde(void)
{
    t_eclass* c;
    
    c = class_new("hoa.recomposer~", (method)hoa_recomposer_new, (method)hoa_recomposer_free, (short)sizeof(t_hoa_recomposer), 0L, A_GIMME, 0);
    
	class_dspinit(c);
    
	class_addmethod(c, (method)hoa_recomposer_dsp,     "dsp",      A_CANT, 0);
    class_addmethod(c, (method)hoa_recomposer_angle,   "angle",    A_GIMME,0);
    class_addmethod(c, (method)hoa_recomposer_wide,    "wide",      A_GIMME,0);
    
    class_register(CLASS_BOX, c);
    hoa_recomposer_class = c;
}

void *hoa_recomposer_new(t_symbol *s, long argc, t_atom *argv)
{
    t_hoa_recomposer *x = NULL;
    t_dictionary *d;
	int	order = 4;
    int microphones = 10;
    int mode = Hoa_Fixe;
    x = (t_hoa_recomposer *)object_alloc(hoa_recomposer_class);
    
    order = atom_getint(argv);
    microphones = atom_getint(argv+1);
    if (atom_gettype(argv+2) == A_SYM)
    {
        if(atom_getsym(argv+2) == gensym("fixe"))
            mode = Hoa_Fixe;
        else if(atom_getsym(argv+2) == gensym("fisheye"))
            mode = Hoa_Fisheye;
        else if(atom_getsym(argv+2) == gensym("free"))
            mode = Hoa_Free;
    }
    if (atom_gettype(argv+2) == A_LONG)
    {
        mode = Tools::clip(long(atom_getlong(argv+2)), 0, 2);
    }
    x->f_ambi_recomposer = new AmbisonicRecomposer(order, microphones, mode, sys_getblksize(), sys_getsr());
    
    dsp_setupjbox((t_jbox *)x, x->f_ambi_recomposer->getNumberOfInputs(), x->f_ambi_recomposer->getNumberOfOutputs());
    
	x->f_ob.z_misc = Z_NO_INPLACE;
    
    d = object_dictionaryarg(argc,argv);
    attr_dictionary_process(x, d);
	
   	return (x);
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
