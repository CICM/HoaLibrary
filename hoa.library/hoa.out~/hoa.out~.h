
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
#include "z_dsp.h"

typedef struct  _out
{
	t_pxobject	f_ob;
	t_sample	*f_vector;
} t_out;

void *out_class;

void *out_new(t_symbol *s, int argc, t_atom *argv);
void out_free(t_out *x);
void out_assist(t_out *x, void *b, long m, long a, char *s);

void out_dsp64(t_out *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void out_perform64(t_out *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void out_dsp(t_out *x, t_signal **sp, short *count);
t_int *out_perform(t_int *w);
