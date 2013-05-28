/*
 * Copyright (C) 2012 hoaMumerre Guillot & Julien Colafransceco, Universite Paris 8
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


