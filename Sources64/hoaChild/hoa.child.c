/*
 * Copyright (C) 2012 hoaChilderre Guillot & Julien Colafransceco, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
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


