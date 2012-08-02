
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
#include "jpatcher_api.h"
#include "ext_wind.h"
#include "z_dsp.h"
#include "ext_symobject.h"
#include "ext_database.h"
#include "jgraphics.h"
#include "indexmap.h"
#include "jdataview.h"

typedef struct  _in
{
	t_pxobject	f_ob;
	t_sample	*f_vector;
} t_in;

typedef struct  _plug
{
	t_pxobject	f_ob;
	
	int			f_order;
	int			f_harmonics;
	
	t_object	*f_mypatcher;
	
	t_object	**f_patchers;
	t_object	**f_ins;
	t_object	**f_instilde;
	t_object	**f_outstilde;
	
	t_sample	*f_vectorIn;
	t_sample	*f_vectorOut;
} t_plug;

void *plug_class;

void *plug_new(t_symbol *s, int argc, t_atom *argv);

void plug_free(t_plug *x);
void plug_assist(t_plug *x, void *b, long m, long a, char *s);
void plug_dblclick(t_plug *x);
t_max_err plug_notify(t_plug *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void plug_dsp64(t_plug *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void plug_perform64(t_plug *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void plug_dsp(t_plug *x, t_signal **sp, short *count);
t_int *plug_perform(t_int *w);

void post_containers(t_plug *x);
void plug_patchers(t_plug *x, t_symbol *s);
void plug_read(t_plug *x, t_symbol *s, t_dictionary *d);
void plug_getinput(t_plug *x, t_object *patcher, int index);


void plug_bang(t_plug *x);
void plug_int(t_plug *x, long n);
void plug_float(t_plug *x, double f);
void plug_list(t_plug *x, t_symbol *s, long argc, t_atom *argv);
void plug_anything(t_plug *x, t_symbol *s, long argc, t_atom *argv);
void plug_assist(t_plug *x, void *b, long m, long a, char *s);