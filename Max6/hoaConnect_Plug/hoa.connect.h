/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
