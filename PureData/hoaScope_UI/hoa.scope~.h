/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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

#ifndef DEF_HOA_SCOPE_TILDE_PD
#define DEF_HOA_SCOPE_TILDE_PD

#include "../../../PdEnhanced/Sources/pd_enhanced.h"
#include "../../Sources/HoaLibrary.h"


typedef struct  _scope
{
	t_jbox      j_box;
	
	t_clock*	f_clock;
	int			f_startclock;
	long        f_interval;
	long        f_order;
    
    long        f_drawCircle;
    long        f_drawContributions;
    long        f_drawAngles;
    float       f_normalize;
	
	t_jrgba		f_colorBackground;
    t_jrgba     f_bordercolor;
	t_jrgba		f_colorText;
	t_jrgba		f_colorNegatif;
	t_jrgba		f_colorPositif;
	
	t_rect		f_center;
	double		f_rayonGlobal;
	double		f_rayonAngle;
	double		f_rayonCircle;
	double		f_fontsize;
    
    AmbisonicsViewer* f_viewer;
    double*     f_harmonicsValues;
    long        f_sampleCounter;
    double*     f_averageHarmo;
    
} t_scope;

t_eclass *scope_class;

extern "C" void setup_hoa0x2escope_tilde(void);
void *scope_new(t_symbol *s, int argc, t_atom *argv);
void scope_free(t_scope *x);
void scope_assist(t_scope *x, void *b, long m, long a, char *s);
void scope_tick(t_scope *x);

void scope_dsp(t_scope *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void scope_perform(t_scope *x, t_object *d, float **ins, long ni, float **outs, long no, long sf, long f,void *up);

t_max_err scope_notify(t_scope *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
long scope_oksize(t_scope *x, t_rect *newrect);
void scope_getdrawparams(t_scope *x, t_object *patcherview, t_jboxdrawparams *params);
/* Paint *********************************************/
void scope_paint(t_scope *x, t_object *view);
void draw_background(t_scope *x, t_object *view, t_rect *rect);
void draw_angles(t_scope *x,  t_object *view, t_rect *rect);
void draw_contribution(t_scope *x,  t_object *view, t_rect *rect);
void draw_harmonics(t_scope *x,  t_object *view, t_rect *rect);

t_max_err scope_setattr_order(t_scope *x, t_object *attr, long ac, t_atom *av);

#endif