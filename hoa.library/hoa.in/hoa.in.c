
/*
* Copyright (C) 2012 Pierre Guillot & Julien Colafransceco, Universite Paris 8
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

#include "hoa.in.h"

int main(void)
{
	t_class *c;

	c = class_new("hoa.in", (method)in_new, (method)in_free, (short)sizeof(t_in), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)in_anything,			"anything",		A_GIMME, 0);
	class_addmethod(c, (method)in_list,				"list",			A_GIMME, 0);
	class_addmethod(c, (method)in_int,				"int",			A_LONG, 0);
	class_addmethod(c, (method)in_float,			"float",		A_FLOAT, 0);
	class_addmethod(c, (method)in_bang,				"bang",			A_CANT,	0);
	
	class_addmethod(c, (method)in_assist,			"assist",		A_CANT,	0);

	class_register(CLASS_BOX, c);
	in_class = c;

	post("hoa.in~ by Pierre Guillot & Julien Colafransceco",0);
	post("Copyright (C) 2012, Universite Paris 8");

}

void *in_new(t_symbol *s, int argc, t_atom *argv)
{
	t_in *x = NULL;
	
	if (x = (t_in *)object_alloc((t_class *)in_class)) 
	{
		x->f_outlet = outlet_new((t_object *)x, NULL);
		attr_args_process(x, argc, argv);
	}
	
	return x;
}			


void in_free(t_in *x)
{
	;
}

void in_bang(t_in *x)
{
	outlet_bang(x->f_outlet);
}

void in_int(t_in *x, long n)
{
	outlet_int(x->f_outlet, n);
}

void in_float(t_in *x, double f)
{
	outlet_float(x->f_outlet, f);
}

void in_list(t_in *x, t_symbol *s, long argc, t_atom *argv)
{
	outlet_list(x->f_outlet, s, argc, argv);
}

void in_anything(t_in *x, t_symbol *s, long argc, t_atom *argv)
{
	outlet_anything(x->f_outlet, s, argc, argv);
}

void in_assist(t_in *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"(Anything) Input");
	}
	else 
	{
		sprintf(s,"(Anything) Output");
	}
}

