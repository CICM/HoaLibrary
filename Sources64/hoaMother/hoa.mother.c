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

typedef struct _hoaMum 
{	
	t_object p_ob;
    long numberOfInlet;
} t_hoaMum;

void hoaMum_bang(t_hoaMum *x);
void hoaMum_connect(t_hoaMum *x);
void hoaMum_int(t_hoaMum *x, long n);
void hoaMum_float(t_hoaMum *x, double n) ;
void hoaMum_assist(t_hoaMum *x, void *b, long m, long a, char *s);
void *hoaMum_new(t_symbol *s, int argc, t_atom *argv);

void hoaMum_get_hoaLib_version(t_hoaMum *x);
void hoaMum_get_hoaObj_version(t_hoaMum *x);

void hoaMum_set_inletnum(t_hoaMum *x, long numberOfInlets);
void hoaMum_hoaQuery_inletnum(t_hoaMum *x);

void hoaMum_init(t_symbol *s, int argc, t_atom *argv);

t_class *hoaMum_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.mother", (method)hoaMum_new, (method)NULL, sizeof(t_hoaMum), 0L, A_GIMME, 0);
	
    //class_addmethod(c, (method)hoaMum_bang,		"bang",		0);
    //class_addmethod(c, (method)hoaMum_int,		"int",		A_LONG, 0);
	//class_addmethod(c, (method)hoaMum_float,	"float",	A_FLOAT, 0);
    //class_addmethod(c, (method)hoaMum_assist,	"assist",	A_CANT, 0);
    class_addmethod(c, (method)hoaMum_get_hoaLib_version,	"getlibversion",	0, 0);
    class_addmethod(c, (method)hoaMum_get_hoaObj_version,	"getobjversion",	0, 0);
    class_addmethod(c, (method)hoaMum_connect,	"connect",	0, 0);
    class_addmethod(c, (method)hoaMum_init,     "init",     A_GIMME, 0);
    class_addmethod(c, (method)hoaMum_set_inletnum,		"set_inletnum",		A_LONG, 0);
    class_addmethod(c, (method)hoaMum_hoaQuery_inletnum,     "query_inletnum",     0, 0);
	//class_addmethod(c, (method)hoaMum_bang,		"dblclick",	A_CANT, 0);
	
	class_register(CLASS_BOX, c);
	hoaMum_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *hoaMum_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoaMum *x = (t_hoaMum *)object_alloc(hoaMum_class);
	return(x);
}



void hoaMum_init(t_symbol *s, int argc, t_atom *argv)
{
    
}

void hoaMum_set_inletnum(t_hoaMum *x, long numberOfInlets)
{
    x->numberOfInlet = numberOfInlets;
}

void hoaMum_hoaQuery_inletnum(t_hoaMum *x)
{
    object_post((t_object *)x, "has %ld inlets", x->numberOfInlet);
}

void hoaMum_connect(t_hoaMum *x)
{
    object_post((t_object *)x, "connect method call");
}

void hoaMum_get_hoaLib_version(t_hoaMum *x)
{
    object_post((t_object *)x, "HoaLibrary 1.3");
}

void hoaMum_get_hoaObj_version(t_hoaMum *x)
{
    object_post((t_object *)x, "object version 1.1.4");
}

void hoaMum_init(t_symbol *s, int argc, t_atom *argv);

void hoaMum_assist(t_hoaMum *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_OUTLET)
		sprintf(s,"hoaMum");
	else
		sprintf(s,"hoaMum");
}

void hoaMum_bang(t_hoaMum *x) 
{
	//outlet_float(x->p_outlet, hoaMum * x->p_value);
}


void hoaMum_int(t_hoaMum *x, long n)
{
	;
}


void hoaMum_float(t_hoaMum *x, double n) 
{
	;
}


