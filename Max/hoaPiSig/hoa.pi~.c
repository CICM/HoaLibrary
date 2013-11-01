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

#define CICM_PI  (3.141592653589793238462643383279502884)

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

typedef struct _pi 
{	
	t_pxobject  p_ob;
	double      p_value;
} t_pi;

void pi_bang(t_pi *x);
void pi_int(t_pi *x, long n);
void pi_float(t_pi *x, double n) ;
void pi_assist(t_pi *x, void *b, long m, long a, char *s);
void *pi_new(t_symbol *s, int argc, t_atom *argv);

void pi_dsp64(t_pi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void pi_perform64(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void pi_perform64_phase(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void pi_perform64_offset(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_class *pi_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.pi~", (method)pi_new, (method)dsp_free, sizeof(t_pi), 0L, A_GIMME, 0);
	
    class_addmethod(c, (method)pi_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)pi_float,	"float",	A_FLOAT, 0);
    class_addmethod(c, (method)pi_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)pi_dsp64,	"dsp64",    A_CANT, 0);
	
    class_dspinit(c);
	class_register(CLASS_BOX, c);
	pi_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *pi_new(t_symbol *s, int argc, t_atom *argv)
{
	t_pi *x = (t_pi *)object_alloc(pi_class);
	x->p_value = 1.;
    
	if (atom_gettype(argv) == A_LONG)
		x->p_value = atom_getlong(argv);
	else if (atom_gettype(argv) == A_FLOAT)
		x->p_value = atom_getfloat(argv);
    
    dsp_setup((t_pxobject *)x, 2);
    outlet_new(x, "signal");
    
	return(x);
}


void pi_dsp64(t_pi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	if(count[0])
		object_method(dsp64, gensym("dsp_add64"), x, pi_perform64, 0, NULL);
    else if(count[1])
		object_method(dsp64, gensym("dsp_add64"), x, pi_perform64_phase, 0, NULL);
    else
		object_method(dsp64, gensym("dsp_add64"), x, pi_perform64_offset, 0, NULL);
}

void pi_perform64(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int i;
    for(i = 0; i < sampleframes; i++)
    {
        x->p_value = ins[0][i];
        outs[0][i] = CICM_PI * ins[0][i];
    }
}

void pi_perform64_phase(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int i;
    for(i = 0; i < sampleframes; i++)
        outs[0][i] = CICM_PI * x->p_value * ins[1][i];
}

void pi_perform64_offset(t_pi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int i;
    for(i = 0; i < sampleframes; i++)
        outs[0][i] = CICM_PI * x->p_value;
}

void pi_assist(t_pi *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_OUTLET)
		sprintf(s,"(Signal or Float) Pi Multiplication Result");
	else
    {
        if(a)
            sprintf(s,"(Signal or Float) This * Pi * Multiplier");
        else
            sprintf(s,"(Signal or Float) This * Pi");
    }
}

void pi_int(t_pi *x, long n)
{
	x->p_value = n;
}


void pi_float(t_pi *x, double n) 
{
	x->p_value = n;
}