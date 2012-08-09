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

#ifndef DEF_HOA.PLUG_SCRIPT
#define DEF_HOA.PLUG_SCRIPT

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

typedef struct  _plug_script
{
	t_pxobject	f_ob;
	void		*f_outlet;
} t_plug_script;

void *plug_script_class;
void plug_script_init();
void *plug_script_new(t_symbol *s, int argc, t_atom *argv);
void plug_script_free(t_plug_script *x);
void plug_script_assist(t_plug_script *x, void *b, long m, long a, char *s);

void plug_script_dsp64(t_plug_script *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void plug_script_perform64(t_plug_script *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void plug_script_dsp(t_plug_script *x, t_signal **sp, short *count);
t_int *plug_script_perform(t_int *w);

void plug_script_bang(t_plug_script *x);
void plug_script_int(t_plug_script *x, long n);
void plug_script_float(t_plug_script *x, double f);
void plug_script_list(t_plug_script *x, t_symbol *s, long argc, t_atom *argv);
void plug_script_anything(t_plug_script *x, t_symbol *s, long argc, t_atom *argv);

#endif
