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

#define C74_X64

#include "ext.h"
#include "ext_obex.h"



typedef struct _hoaChild 
{	
	t_object p_ob;
} t_hoaChild;

void hoaChild_bang(t_hoaChild *x);
void hoaChild_connect(t_hoaChild *x);
void hoaChild_int(t_hoaChild *x, long n);
void hoaChild_float(t_hoaChild *x, double n) ;
void hoaChild_assist(t_hoaChild *x, void *b, long m, long a, char *s);
void *hoaChild_new(t_symbol *s, int argc, t_atom *argv);

t_class *hoaChild_class;

int C74_EXPORT main(void)
{
	t_class *c;
	
	c = class_new("hoa.child", (method)hoaChild_new, (method)NULL, sizeof(t_hoaChild), 0L, A_GIMME, 0);
	
    class_addmethod(c, (method)hoaChild_bang,		"bang",		0);	
    class_addmethod(c, (method)hoaChild_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)hoaChild_float,	"float",	A_FLOAT, 0);
    class_addmethod(c, (method)hoaChild_assist,	"assist",	A_CANT, 0);
    //class_addmethod(c, (method)hoaChild_connect,	"connect",	0, 0);
	//class_addmethod(c, (method)hoaChild_bang,		"dblclick",	A_CANT, 0);
	
	class_register(CLASS_BOX, c);
	hoaChild_class = c;
    
    class_subclass(class_findbyname(CLASS_BOX, gensym("hoa.mother")), c);
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *hoaChild_new(t_symbol *s, int argc, t_atom *argv)
{
	//t_hoaChild *x = (t_hoaChild *)object_alloc(hoaChild_class);
    t_hoaChild *x = (t_hoaChild *)class_super_construct(hoaChild_class, argc, argv);
    //object_super_method((t_object *)x, gensym("set_inletnum"), 9);

    //object_super_method((t_object *)x, gensym("set_inletnum"), 9);
	return(x);
}


void hoaChild_connect(t_hoaChild *x)
{
    object_post((t_object *)x, "connect method call (child)");
}


void hoaChild_assist(t_hoaChild *x, void *b, long m, long a, char *s)
{
	if (m != ASSIST_OUTLET)
		sprintf(s,"hoaChild");
	else
		sprintf(s,"hoaChild");
}

void hoaChild_bang(t_hoaChild *x) 
{
	//outlet_float(x->p_outlet, hoaChild * x->p_value);
}


void hoaChild_int(t_hoaChild *x, long n)
{
	;
}


void hoaChild_float(t_hoaChild *x, double n) 
{
	;
}


