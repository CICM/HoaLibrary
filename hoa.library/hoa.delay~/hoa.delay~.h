
/*
* Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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
* guillotpierre6@gmail.com
*/
#define WINSIZE	16384

#include "hoa.delay.ui.h"
#include "z_dsp.h"
#include "../pg.delay/pg.delay.h"

typedef struct  _delayObj
{
	t_pxobject	f_ob;

	double		f_sr;
	t_delay		f_delay;
	int			f_order;
	int			f_harmonics;
	
	t_object	*f_patcher;
	t_object	*f_ui;
	t_jrgba		f_oncolor;
	t_jrgba		f_offcolor;

} t_delayObj;

void *delayObj_class;

void delayObj_classinit(void);
void *delayObj_new(t_symbol *s, int argc, t_atom *argv);
void delayObj_free(t_delayObj *x);
void delayObj_assist(t_delayObj *x, void *b, long m, long a, char *s);
void delayObj_dblclick(t_delayObj *x);
t_max_err delayObj_notify(t_delayObj *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void delayObj_dsp64(t_delayObj *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void delayObj_perform64(t_delayObj *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void delayObj_dsp(t_delayObj *x, t_signal **sp, short *count);
t_int *delayObj_perform(t_int *w);
