/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_MAX_COMMONSYMS
#define DEF_HOA_MAX_COMMONSYMS

extern "C"
{
#include <ext.h>
}

static t_symbol* hoa_sym_cartesian	= gensym("cartesian");
static t_symbol* hoa_sym_car		= gensym("car");
static t_symbol* hoa_sym_polar		= gensym("polar");
static t_symbol* hoa_sym_pol		= gensym("pol");
static t_symbol* hoa_sym_mute		= gensym("mute");

#endif
