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
#include "hoa.structure.h"

#define CONNECT_MAX_TAB 100

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
void connect_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet);
void connect_attach(t_connect *x);
void connect_notify(t_connect *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void connect_list(t_connect *x, t_symbol *s, long argc, t_atom *argv);

int validName(t_object *box);

void color_patchline(t_connect *x);
int validConditionColor(t_object *obj);

#endif
