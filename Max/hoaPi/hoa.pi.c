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

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

typedef struct _pi 
{	
	t_object    f_ob;
	double      f_value;	
	void*       f_outlet;
    t_atom_long f_loadbang;
    
} t_pi;

void pi_bang(t_pi *x);
void pi_int(t_pi *x, long n);
void pi_float(t_pi *x, double n) ;
void pi_assist(t_pi *x, void *b, long m, long a, char *s);
void *pi_new(t_symbol *s, int argc, t_atom *argv);

t_class *pi_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.pi", (method)pi_new, (method)NULL, sizeof(t_pi), 0L, A_GIMME, 0);
	
    class_addmethod(c, (method)pi_bang,		"bang",		0);	
    class_addmethod(c, (method)pi_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)pi_float,	"float",	A_FLOAT, 0);
    class_addmethod(c, (method)pi_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)pi_bang,		"dblclick",	A_CANT, 0);
    
    CLASS_ATTR_LONG             (c, "loadout",  0, t_pi, f_loadbang);
	CLASS_ATTR_CATEGORY			(c, "loadout",  0, "Behavior");
    CLASS_ATTR_STYLE_LABEL      (c, "loadout",  0, "onoff", "Load output");
	CLASS_ATTR_ORDER			(c, "loadout",  0, "1");
	CLASS_ATTR_DEFAULT			(c, "loadout",  0, "0");
	CLASS_ATTR_SAVE				(c, "loadout",  1);
	
	class_register(CLASS_BOX, c);
	pi_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *pi_new(t_symbol *s, int argc, t_atom *argv)
{
	t_pi *x = NULL;
    t_dictionary *d = NULL;
    t_dictionary* attr = NULL;
    
    x = (t_pi *)object_alloc(pi_class);
    if (x)
	{
        x->f_value = 1.;
        x->f_loadbang = 0;
        if (atom_gettype(argv) == A_LONG)
            x->f_value = atom_getlong(argv);
        else if (atom_gettype(argv) == A_FLOAT)
            x->f_value = atom_getfloat(argv);
        
        x->f_outlet = floatout(x);
        
        d = (t_dictionary *)gensym("#D")->s_thing;
        if (d) attr_dictionary_process(x, d);
        
        
        dictionary_getdictionary(d, gensym("saved_object_attributes"), (t_object **)&attr);
        if(attr)
            dictionary_getlong(attr, gensym("loadout"), &x->f_loadbang);
        
        attr_args_process(x, argc, argv);
        if(x->f_loadbang)
        {
            defer_low(x, (method)pi_bang, NULL, 0, NULL);
        }
        
    }
	
	return(x);
}

void pi_assist(t_pi *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_OUTLET)
		sprintf(s,"(Int, Float or Bang) Compute");
	else
		sprintf(s,"(Float) PI * %.f", x->f_value);
}

void pi_bang(t_pi *x) 
{
	outlet_float(x->f_outlet, PI * x->f_value);
}


void pi_int(t_pi *x, long n)
{
	x->f_value = n;
	pi_bang(x);
}


void pi_float(t_pi *x, double n) 
{
	x->f_value = n;
	pi_bang(x);
}


