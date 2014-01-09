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

#define DEFDACBLKSIZE 64
extern t_sample *sys_soundout;

typedef struct _hoa_dac
{
    t_object    x_obj;
    t_int       x_n;
    t_int*      x_vec;
    t_float     x_f;
} t_hoa_dac;

void *hoa_dac_new(t_symbol *s, long argc, t_atom *argv);
void hoa_dac_free(t_hoa_dac *x);
void hoa_dac_dsp(t_hoa_dac *x, t_signal **sp);

t_class *hoa_dac_class;

extern "C" void setup_hoa0x2edac_tilde(void)
{
    t_class* c;
    c = class_new(gensym("hoa.dac~"), (t_newmethod)hoa_dac_new, (t_method)hoa_dac_free, (short)sizeof(t_hoa_dac), 0, A_GIMME, 0);
    CLASS_MAINSIGNALIN(c, t_hoa_dac, x_f);
    class_addmethod(c, (t_method)hoa_dac_dsp, gensym("dsp"), A_CANT, 0);
    hoa_dac_class = c;
    erouter_add_libary(gensym("hoa"), "hoa.library by Julien Colafrancesco, Pierre Guillot & Eliott Paris", "© 2012 - 2014  CICM | Paris 8 University", "Version 1.1");
}

void *hoa_dac_new(t_symbol *s, long argc, t_atom *argv)
{
    int i, j;
    int min, max;
    t_atom channels[256];
	t_hoa_dac *x = (t_hoa_dac *)pd_new(hoa_dac_class);
    
    if(!argc)
    {
        x->x_n = 2;
        x->x_vec = (t_int *)malloc(2 * sizeof(*x->x_vec));
        x->x_vec[0] = 1;
        x->x_vec[1] = 2;
    }
    else
    {
        x->x_n = 0;
        for(i = 0; i < argc; i++)
        {
            if(atom_gettype(argv+i) == A_FLOAT)
            {
                atom_setfloat(channels + x->x_n, (int)atom_getfloat(argv+i));
                x->x_n++;
            }
            else if(atom_gettype(argv+i) == A_SYM)
            {
                min = atoi(atom_getsym(argv+i)->s_name);
                if(min > 0 && min <= 256)
                {
                    if (min < 10)
                        max = atoi(atom_getsym(argv+i)->s_name+2);
                    else if (min < 100)
                        max = atoi(atom_getsym(argv+i)->s_name+3);
                    else if (min < 1000)
                        max = atoi(atom_getsym(argv+i)->s_name+4);
                    else
                        max = atoi(atom_getsym(argv+i)->s_name+5);
                    if(max > 0 && max <= 256)
                    {
                        if(max > min)
                        {
                            for(j = min; j <= max; j++)
                            {
                                atom_setlong(channels + x->x_n, j);
                                x->x_n++;
                            }
                        }
                        else
                        {
                            for(j = min; j >= max; j--)
                            {
                                atom_setlong(channels + x->x_n, j);
                                x->x_n++;
                            }
                        }
                    }
                }
            }
        }
        x->x_vec = (t_int *)malloc(x->x_n * sizeof(*x->x_vec));
        for (i = 0; i < x->x_n; i++)
        {
            x->x_vec[i] = atom_getintarg(i, x->x_n, channels);
        }
    }
    
    for (i = 1; i < x->x_n; i++)
        inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->x_f = 0;
    return (x);
}

void hoa_dac_dsp(t_hoa_dac *x, t_signal **sp)
{
    t_int i, *ip;
    t_signal **sp2;
    for (i = x->x_n, ip = x->x_vec, sp2 = sp; i--; ip++, sp2++)
    {
        int ch = *ip - 1;
        if ((*sp2)->s_n != DEFDACBLKSIZE)
            error("hoa.dac~: bad vector size");
        else if (ch >= 0 && ch < sys_get_outchannels())
            dsp_add(plus_perform, 4, sys_soundout + DEFDACBLKSIZE*ch,
                    (*sp2)->s_vec, sys_soundout + DEFDACBLKSIZE*ch, DEFDACBLKSIZE);
    }
}

void hoa_dac_free(t_hoa_dac *x)
{
    freebytes(x->x_vec, x->x_n * sizeof(*x->x_vec));
}
