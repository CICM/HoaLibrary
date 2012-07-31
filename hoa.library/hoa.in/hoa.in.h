
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

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"

typedef struct  _in
{
	t_object	f_ob;
	void		*f_outlet;
} t_in;

void *in_class;

void *in_new(t_symbol *s, int argc, t_atom *argv);
void in_free(t_in *x);
void in_assist(t_in *x, void *b, long m, long a, char *s);

void in_bang(t_in *x);
void in_int(t_in *x, long n);
void in_float(t_in *x, double f);
void in_list(t_in *x, t_symbol *s, long argc, t_atom *argv);
void in_anything(t_in *x, t_symbol *s, long argc, t_atom *argv);

