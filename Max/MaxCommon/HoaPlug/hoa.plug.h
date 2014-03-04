/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DEF_HOA_PLUG
#define DEF_HOA_PLUG

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
	void		*f_outany;
	void		*f_outcontr;
	void		*f_outsignal;

	int			f_gate;
	int			f_index;
	int			f_mode;
	int			f_order;
	int			f_inlet;
	int			f_outlet;
	int			f_connected;
} t_plug_script;

typedef struct  _plug
{
	t_object	f_ob;
	
} t_plug;

void *plug_class;
void *patcher_class;
void *plug_script_class;
method dblclickpatcher;

void *plug_new(t_symbol *s, int argc, t_atom *argv);
void plug_router(t_object *x, int order, t_symbol *s, int mode, t_atom *argv, int argc);
void plug_dblclick(t_object *x);

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
void plug_script_open(t_plug_script *x, t_symbol *s, long argc, t_atom *argv);
void plug_script_mute(t_plug_script *x, t_symbol *s, long argc, t_atom *argv);
void plug_script_target(t_plug_script *x, t_symbol *s, long argc, t_atom *argv);
void plug_script_load(t_plug_script *x, t_symbol *s);

int plug_harmonic(int index, int order);
void plug_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet);
t_object *plug_patch(t_object *patcher, t_symbol *s, int index, int order, int mode, int noutlet, t_atom *argv, int argc);
t_object *plug_script(t_object *patcher, int index, int order, int ninlet, int noutlet, int mode);
t_object *plug_outlet(t_object *patcher, int index, int order, int noutlet, int mode);
t_object* plug_inlet(t_object *patcher, int index, int order, int ninlet, int mode);
t_object *plug_pcontr(t_object *patcher, int index, int order, int ninlet);


#endif
