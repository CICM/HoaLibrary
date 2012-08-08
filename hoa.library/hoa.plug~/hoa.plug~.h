
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

#include "hoa.plug_script.h"

typedef struct  _plug
{
	t_object	f_ob;
	
} t_plug;

void *plug_class;
void *patcher_class;
method dblclickpatcher;

void *plug_new(t_symbol *s, int argc, t_atom *argv);
void plug_connect(t_object *x, t_object *send, int outlet, t_object *receive, int inlet);
void plug_router(t_object *x, t_object *inlet, t_object *patch, int index);

void plug_dblclick(t_object *x);
void plug_load(t_object *x);