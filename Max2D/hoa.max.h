/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_MAX
#define DEF_HOA_MAX

#include "../Sources/Hoa2D/Hoa2D.h"

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
}

void hoa_credit()
{
    static t_object hoa_cred;
    if(gensym("hoa.credit")->s_thing == NULL)
    {
        post("hoa.library (version 2.0) by Julien Colafrancesco, Pierre Guillot & Eliott Paris");
        post("Copyright (C) 2012 - 2013, CICM | Universite Paris 8");
        gensym("hoa.credit")->s_thing = &hoa_cred;
    }
}

#endif



