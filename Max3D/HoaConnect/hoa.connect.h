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

#define CONNECT_MAX_TAB 100

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

typedef struct  _connect
{
	t_object	f_ob;
	
	t_object	*f_patcher;
	t_object	*f_patcherview;
	
	t_object	*f_object[CONNECT_MAX_TAB];
	int			f_index[CONNECT_MAX_TAB];
	int			f_mode[CONNECT_MAX_TAB];
	int			f_order[CONNECT_MAX_TAB];
	int			f_inlet[CONNECT_MAX_TAB];
	int			f_outlet[CONNECT_MAX_TAB];
	int			f_connected[CONNECT_MAX_TAB];
	
	t_jrgba		f_colorPositiv;
	t_jrgba		f_colorNegativ;
	t_jrgba		f_colorPlane;
	
	int			f_nbSelected;
	int			f_inc;
	int			f_harmonics;
	int			f_output;
	
	t_rect		f_jr;
} t_connect;

void *connect_class;

void *connect_new(t_symbol *s, long argc, t_atom *argv);

void connect_free(t_connect *x);
void connect_bang(t_connect *x);
void connect_assist(t_connect *x, void *b, long m, long a, char *s);
void connect_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet);
void connect_attach(t_connect *x);
void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void connect_list(t_connect *x, t_symbol *s, long argc, t_atom *argv);

t_max_err connect_setattr_poscolor(t_connect *x, void *attr, long argc, t_atom *argv);
t_max_err connect_setattr_negcolor(t_connect *x, void *attr, long argc, t_atom *argv);
t_max_err connect_setattr_planecolor(t_connect *x, void *attr, long argc, t_atom *argv);

int validName(t_object *box);

void color_patchline(t_connect *x);
int validConditionColor(t_object *obj);

#endif
