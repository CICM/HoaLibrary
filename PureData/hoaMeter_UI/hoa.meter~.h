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

#ifndef DEF_HOA_METER_TILDE_PD
#define DEF_HOA_METER_TILDE_PD

#include "../../../PdEnhanced/Sources/pd_enhanced.h"
#include "../../Sources/HoaLibrary.h"

#define MAX_SPEAKER 64
#define DEF_SPEAKER 8
#define OVERLED_DRAWTIME 1000

typedef struct  _meter
{
	t_jbox      j_box;
    t_rect      f_rect;
	
	t_clock*	f_clock;
	int			f_startclock;
	long        f_interval;
    
    long        f_number_of_loudspeakers;
	double      f_offset_of_loudspeakers;
	
	long		f_dbperled;
	long		f_nhotleds;
	long		f_ntepidleds;
	long		f_nwarmleds;
	long		f_number_of_leds;
	
	double		f_angles_of_loudspeakers[MAX_SPEAKER];
	double		f_angles_to_draw[MAX_SPEAKER];
	double		f_width_of_loudspeakers[MAX_SPEAKER];
    long		f_drawOverLedleftTime[MAX_SPEAKER];
	
	t_jrgba		f_colorBackground;
	t_jrgba		f_colorMeterBg;
	t_jrgba		f_colorBorder;
	t_jrgba		f_colorMeterBorder;
	t_jrgba		f_colorColdSignal;
	t_jrgba		f_colorTepidSignal;
	t_jrgba		f_colorWarmSignal;
	t_jrgba		f_colorHotSignal;
	t_jrgba		f_colorOverSignal;
	
	t_jrgba		f_colorEnergy;
	t_jrgba		f_colorVelocity;
	
	t_pt		f_center;
	double		f_rayonMax;
	double		f_rayonCircle;
	double		f_fontsize;
	
	double		f_strokeWidth;
	double		f_rayonExt;
	double		f_rayonInt;
    
	long         f_leds_bg;
    long         f_drawvector;
    long         f_drawmborder;
	double       f_metersize;
    long         f_speakers_dir_of_rotation;
    long         f_fill_direction;
    
    void*               f_vector_outlet;
    void*               f_peaks_outlet;
	
    AmbisonicsMeter*     f_meter;
} t_meter;

t_eclass *meter_class;

extern "C" void setup_hoa0x2emeter_tilde(void);
void *meter_new(t_symbol *s, int argc, t_atom *argv);
void meter_free(t_meter *x);
void meter_assist(t_meter *x, void *b, long m, long a, char *s);

void meter_dsp(t_meter *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void meter_perform(t_meter *x, t_object *d, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void meter_tick(t_meter *x);
void meter_output(t_meter *x);

t_max_err meter_notify(t_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err number_of_loudspeakers_set(t_meter *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_of_loudspeakers_set(t_meter *x, void *attr, long ac, t_atom *av);

/* Paint ------------------------------------- */
void meter_getdrawparams(t_meter *x, t_object *patcherview, t_jboxdrawparams *params);
void meter_paint(t_meter *x, t_object *view);
void draw_background(t_meter *x, t_object *view, t_rect *rect);
void draw_meter(t_meter *x,  t_object *view, t_rect *rect);
void draw_vector_energy(t_meter *x, t_object *view, t_rect *rect);
void draw_vector_velocity(t_meter *x, t_object *view, t_rect *rect);
void draw_angle(t_meter *x,  t_object *view, t_rect *rect);
void draw_skelton(t_meter *x,  t_object *view, t_rect *rect);
void draw_separator(t_meter *x,  t_object *view, t_rect *rect);


#endif