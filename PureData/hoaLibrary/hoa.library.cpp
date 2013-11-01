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

#include "hoa.library_pd.h"

typedef struct _hoa
{
	t_object x_obj;
} t_hoa;

static t_eclass* hoa_class;


static void* hoa_new(t_symbol* s)
{
    t_hoa *x = (t_hoa *)object_alloc(hoa_class);
    return (x);
}

extern "C" void hoa_setup(void)
{
    hoa_class = class_new("hoa", (method)hoa_new, (method)NULL, (short)sizeof(t_hoa), 0L, A_GIMME, 0);
    
    post("hoa.library (version 1.0) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
	post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
    
	setup_hoa0x2edecoder_tilde();
    setup_hoa0x2edelay_tilde();
    setup_hoa0x2eencoder_tilde();
    setup_hoa0x2efreeverb_tilde();
    setup_hoa0x2egrain_tilde();
    setup_hoa0x2emap_tilde();
    setup_hoa0x2emeter_tilde();
    setup_hoa0x2eprojector_tilde();
    setup_hoa0x2erecomposer_tilde();
    setup_hoa0x2epi();
    setup_hoa0x2eringmod_tilde();
    setup_hoa0x2espace_tilde();
    setup_hoa0x2ewider_tilde();
    setup_hoa0x2espace();
    setup_hoa0x2emap();
    setup_hoa0x2erotate_tilde();
    setup_hoa0x2escope_tilde();
    setup_hoa0x2eoptim_tilde();
}




