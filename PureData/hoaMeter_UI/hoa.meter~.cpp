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


extern "C"
{
#include "../../../PdEnhanced/Sources/cicm_wrapper.h"
}

#include "../../Sources/HoaLibrary.h"

#define MAX_SPEAKER 64

typedef struct  _hoa_meter
{
	t_edspbox   j_box;
    
	int			f_startclock;
	long        f_interval;
    
    t_symbol*   f_vector_type;
    long        f_vector;
    
    long        f_number_of_loudspeakers;
	float       f_offset_of_loudspeakers;
    t_symbol*   f_clockwise_type;
	long        f_clockwise;
	
	float		f_angles_of_loudspeakers[MAX_SPEAKER];
    long		f_over_leds_preserved[MAX_SPEAKER];
	
	t_rgba		f_color_background;
	t_rgba		f_color_border_box;
	t_rgba		f_color_cold_signal;
	t_rgba		f_color_tepid_signal;
	t_rgba		f_color_warm_signal;
	t_rgba		f_color_hot_signal;
	t_rgba		f_color_over_signal;
	
	t_rgba		f_color_energy_vector;
	t_rgba		f_color_velocity_vector;
	
	float		f_radius_global;
	float		f_radius_circle;
    
    
    AmbisonicsMeter*     f_meter;
    
	t_clock*	f_clock;
    t_outlet*   f_outlet_vector;
    t_outlet*   f_outlet_peaks;
    
} t_hoa_meter;

t_eclass *hoa_meter_class;

void *hoa_meter_new(t_symbol *s, int argc, t_atom *argv);
void hoa_meter_free(t_hoa_meter *x);
void hoa_meter_assist(t_hoa_meter *x, void *b, long m, long a, char *s);

void hoa_meter_dsp(t_hoa_meter *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_meter_perform(t_hoa_meter *x, t_object *d, float **ins, long ni, float **outs, long no, long sf, long f,void *up);
void hoa_meter_tick(t_hoa_meter *x);
void hoa_meter_output(t_hoa_meter *x);

t_pd_err hoa_meter_notify(t_hoa_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_pd_err number_of_loudspeakers_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);
t_pd_err angles_of_loudspeakers_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);
t_pd_err vectors_type_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);
t_pd_err rotation_type_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv);

/* Paint ------------------------------------- */
void hoa_meter_getdrawparams(t_hoa_meter *x, t_object *patcherview, t_edrawparams *params);
void hoa_meter_oksize(t_hoa_meter *x, t_rect *newrect);

void hoa_meter_paint(t_hoa_meter *x, t_object *view);
void draw_background(t_hoa_meter *x, t_object *view, t_rect *rect);
void draw_leds(t_hoa_meter *x,  t_object *view, t_rect *rect);
void draw_vectors(t_hoa_meter *x, t_object *view, t_rect *rect);

extern "C" void setup_hoa0x2emeter_tilde(void)
{
	t_eclass *c;
    
	c = eclass_new("hoa.meter~", (method)hoa_meter_new, (method)hoa_meter_free, (short)sizeof(t_hoa_meter), 0L, A_GIMME, 0);
    
	eclass_dspinit(c);
	eclass_init(c, 0);
	
	eclass_addmethod(c, (method) hoa_meter_dsp,             "dsp",           A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_assist,          "assist",		 A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_paint,           "paint",		 A_CANT, 0);
	eclass_addmethod(c, (method) hoa_meter_notify,          "notify",        A_CANT, 0);
    eclass_addmethod(c, (method) hoa_meter_getdrawparams,   "getdrawparams", A_CANT, 0);
    eclass_addmethod(c, (method) hoa_meter_oksize,          "oksize",        A_CANT, 0);
    
	CLASS_ATTR_INVISIBLE            (c, "fontname", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontweight", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontslant", 1);
    CLASS_ATTR_INVISIBLE            (c, "fontsize", 1);
    CLASS_ATTR_INVISIBLE            (c, "send", 1);
	CLASS_ATTR_DEFAULT              (c, "size", 0, "225. 225.");
	
    CLASS_ATTR_LONG                 (c, "channels", 0 , t_hoa_meter, f_number_of_loudspeakers);
    CLASS_ATTR_ACCESSORS            (c, "channels", NULL, number_of_loudspeakers_set);
	CLASS_ATTR_ORDER                (c, "channels", 0, "1");
	CLASS_ATTR_LABEL                (c, "channels", 0, "Number of Channels");
	CLASS_ATTR_SAVE                 (c, "channels", 1);
    CLASS_ATTR_DEFAULT              (c, "channels", 0, "8");
    CLASS_ATTR_STYLE                (c, "channels", 1, "number");
    
    CLASS_ATTR_FLOAT_VARSIZE        (c, "angles", 0, t_hoa_meter, f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS            (c, "angles", NULL, angles_of_loudspeakers_set);
	CLASS_ATTR_ORDER                (c, "angles", 0, "2");
	CLASS_ATTR_LABEL                (c, "angles", 0, "Angles of Channels");
	CLASS_ATTR_SAVE                 (c, "angles", 1);
    CLASS_ATTR_DEFAULT              (c, "angles", 0, "0 45 90 135 180 225 270 315");
    
    CLASS_ATTR_FLOAT                (c, "offset", 0, t_hoa_meter, f_offset_of_loudspeakers);
	CLASS_ATTR_ORDER                (c, "offset", 0, "3");
	CLASS_ATTR_LABEL                (c, "offset", 0, "Offset of Channels");
	CLASS_ATTR_DEFAULT              (c, "offset", 0, "0");
	CLASS_ATTR_SAVE                 (c, "offset", 1);
    CLASS_ATTR_STYLE                (c, "offset", 1, "number");
    
    CLASS_ATTR_SYMBOL               (c, "rotation", 0, t_hoa_meter, f_clockwise_type);
    CLASS_ATTR_ACCESSORS            (c, "rotation", NULL, rotation_type_set);
    CLASS_ATTR_ORDER                (c, "rotation", 0, "4");
	CLASS_ATTR_LABEL                (c, "rotation", 0, "Rotation of Channels");
    CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "rotation", 0, "0");
    CLASS_ATTR_STYLE                (c, "rotation", 1, "menu");
    CLASS_ATTR_ITEMS                (c, "rotation", 1, "Anti-Clockwise Clockwise");
    
	CLASS_ATTR_SYMBOL               (c, "vectors", 0, t_hoa_meter, f_vector_type);
    CLASS_ATTR_ACCESSORS            (c, "vectors", NULL, vectors_type_set);
	CLASS_ATTR_ORDER                (c, "vectors", 0, "2");
    CLASS_ATTR_LABEL                (c, "vectors", 0, "Vectors");
	CLASS_ATTR_DEFAULT              (c, "vectors", 0, "Energy");
	CLASS_ATTR_SAVE                 (c, "vectors", 1);
    CLASS_ATTR_STYLE                (c, "vectors", 1, "menu");
    CLASS_ATTR_ITEMS                (c, "vectors", 1, "None Energy Velocity Both");
    
    CLASS_ATTR_LONG                 (c, "interval", 0, t_hoa_meter, f_interval);
	CLASS_ATTR_ORDER                (c, "interval", 0, "5");
	CLASS_ATTR_LABEL                (c, "interval", 0, "Refresh Interval (in ms)");
	CLASS_ATTR_FILTER_MIN           (c, "interval", 20);
	CLASS_ATTR_DEFAULT              (c, "interval", 0, "50");
	CLASS_ATTR_SAVE                 (c, "interval", 1);
	CLASS_ATTR_STYLE                (c, "interval", 1, "number");
    
    CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_hoa_meter, f_color_background);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "0.7 0.7 0.7 1.");
	CLASS_ATTR_STYLE                (c, "bgcolor", 1, "color");
    
    CLASS_ATTR_RGBA					(c, "bdcolor", 0, t_hoa_meter, f_color_border_box);
	CLASS_ATTR_CATEGORY				(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE                (c, "bdcolor", 0, "rgba");
    CLASS_ATTR_LABEL				(c, "bdcolor", 0, "Border Box Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bdcolor", 0, "0.5 0.5 0.5 1.");
	CLASS_ATTR_STYLE                (c, "bdcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "coldcolor", 0, t_hoa_meter, f_color_cold_signal);
	CLASS_ATTR_LABEL                (c, "coldcolor", 0, "Cold Signal Color");
	CLASS_ATTR_ORDER                (c, "coldcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "coldcolor", 0, "0. 0.6 0. 0.8");
	CLASS_ATTR_STYLE                (c, "coldcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "tepidcolor", 0, t_hoa_meter, f_color_tepid_signal);
	CLASS_ATTR_LABEL                (c, "tepidcolor", 0, "Tepid Signal Color");
	CLASS_ATTR_ORDER                (c, "tepidcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "tepidcolor", 0, "0.6 0.73 0. 0.8");
	CLASS_ATTR_STYLE                (c, "tepidcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "warmcolor", 0, t_hoa_meter, f_color_warm_signal);
	CLASS_ATTR_LABEL                (c, "warmcolor", 0, "Warm Signal Color");
	CLASS_ATTR_ORDER                (c, "warmcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "warmcolor", 0, ".85 .85 0. 0.8");
	CLASS_ATTR_STYLE                (c, "warmcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "hotcolor", 0, t_hoa_meter, f_color_hot_signal);
	CLASS_ATTR_LABEL                (c, "hotcolor", 0, "Hot Signal Color");
	CLASS_ATTR_ORDER                (c, "hotcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "hotcolor", 0, "1. 0.6 0. 0.8");
	CLASS_ATTR_STYLE                (c, "hotcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "overcolor", 0, t_hoa_meter, f_color_over_signal);
	CLASS_ATTR_LABEL                (c, "overcolor", 0, "Overload Signal Color");
	CLASS_ATTR_ORDER                (c, "overcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "overcolor", 0, "1. 0. 0. 0.8");
	CLASS_ATTR_STYLE                (c, "overcolor", 1, "color");
    
	CLASS_ATTR_RGBA                 (c, "energycolor", 0, t_hoa_meter, f_color_energy_vector);
	CLASS_ATTR_LABEL                (c, "energycolor", 0, "Energy Vector Color");
	CLASS_ATTR_ORDER                (c, "energycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "energycolor", 0, "0. 0. 1. 0.8");
    CLASS_ATTR_STYLE                (c, "energycolor", 1, "color");
    
    CLASS_ATTR_RGBA                 (c, "velocitycolor", 0, t_hoa_meter, f_color_velocity_vector);
	CLASS_ATTR_LABEL                (c, "velocitycolor", 0, "Velocity Vector Color");
	CLASS_ATTR_ORDER                (c, "velocitycolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT   (c, "velocitycolor", 0, "1. 0. 0. 0.8");
    CLASS_ATTR_STYLE                (c, "velocitycolor", 1, "color");
	
    eclass_register(CLASS_BOX, c);
    hoa_post();
	hoa_meter_class = c;
}

void *hoa_meter_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoa_meter *x =  NULL;
	t_binbuf *d;
	long flags;
	
	if (!(d = binbuf_via_atoms(argc, argv)))
		return NULL;
    
	x = (t_hoa_meter *)eobj_new(hoa_meter_class);
    x->f_meter = new AmbisonicsMeter(8, sys_getblksize(), sys_getsr());
    x->f_number_of_loudspeakers = x->f_meter->getNumberOfInputs();
    x->f_clock = clock_new(x,(t_method)hoa_meter_tick);
	x->f_startclock = 0;
    
	flags = 0
            | EBOX_GROWLINK
            | EBOX_IGNORELOCKCLICK
            ;
	ebox_new((t_ebox *)x, flags);
    eobj_dspsetup((t_ebox *)x, x->f_number_of_loudspeakers, 0);
    
    x->f_outlet_peaks = listout(x);
    x->f_outlet_vector = listout(x);
    
	ebox_attrprocess_viabinbuf(x, d);
	ebox_ready((t_ebox *)x);
    
	return (x);
}

void hoa_meter_getdrawparams(t_hoa_meter *x, t_object *patcherview, t_edrawparams *params)
{
    params->d_boxfillcolor = x->f_color_background;
    params->d_bordercolor = x->f_color_border_box;
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
}

void hoa_meter_oksize(t_hoa_meter *x, t_rect *newrect)
{
    newrect->width = pd_clip_min(newrect->width, 30.);
    newrect->height = pd_clip_min(newrect->height, 30.);
}

t_pd_err number_of_loudspeakers_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv)
{
    t_atom* av;
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_FLOAT)
        {
            long d = pd_clip_minmax(atom_getfloat(argv), 1, MAX_SPEAKER);
            if(d != x->f_meter->getNumberOfLoudspeakers())
            {
                int dspState = canvas_suspend_dsp();
                x->f_meter->setNumberOfLoudspeakers(d);
                
                x->f_number_of_loudspeakers = x->f_meter->getNumberOfLoudspeakers();
                av = new t_atom[x->f_number_of_loudspeakers];
                for(int i = 0; i < x->f_number_of_loudspeakers; i++)
                {
                    atom_setfloat(av+i, x->f_meter->getLoudspeakerAngle(i));
                }
                angles_of_loudspeakers_set(x, NULL, x->f_number_of_loudspeakers, av);
                eobj_resize_inputs((t_ebox *)x, x->f_number_of_loudspeakers);
                
                canvas_resume_dsp(dspState);
            }
        }
    }
    return NULL;
}

t_pd_err angles_of_loudspeakers_set(t_hoa_meter *x, void *attr, long ac, t_atom *av)
{
    double angles[MAX_SPEAKER];
    if(ac > MAX_SPEAKER)
        ac = MAX_SPEAKER;
    if(ac && av)
    {
        for(int i = 0; i < ac; i++)
        {
            if(atom_gettype(av+i) == A_FLOAT)
            {
                angles[i] = atom_getfloat(av+i);
            }
        }
        x->f_meter->setLoudspeakerAnglesDegrees(ac, angles);
    }
    for(int i = 0; i < x->f_meter->getNumberOfLoudspeakers(); i++)
    {
        x->f_angles_of_loudspeakers[i] = x->f_meter->getLoudspeakerAngle(i);
    }
    x->f_number_of_loudspeakers = x->f_meter->getNumberOfLoudspeakers();

	ebox_invalidate_layer((t_ebox *)x, gensym("background_layer"));
	ebox_invalidate_layer((t_ebox *)x, gensym("leds_layers"));
	ebox_invalidate_layer((t_ebox *)x, gensym("vectors_layer"));
    
	ebox_redraw((t_ebox *)x);
    return 0;
}

t_pd_err vectors_type_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == gensym("Energy"))
            {
                x->f_vector = 1;
                x->f_vector_type = gensym("Energy");
            }
            else if(atom_getsym(argv) == gensym("Velocity"))
            {
                x->f_vector = 2;
                x->f_vector_type = gensym("Velocity");
            }
            else if(atom_getsym(argv) == gensym("Both"))
            {
                x->f_vector = 3;
                x->f_vector_type = gensym("Both");
            }
            else
            {
                x->f_vector = 0;
                x->f_vector_type = gensym("None");
            }
        }
        else if(atom_gettype(argv) == A_FLOAT)
        {
            if(atom_getlong(argv) == 1)
            {
                x->f_vector = 1;
                x->f_vector_type = gensym("Energy");
            }
            else if(atom_getlong(argv) == 2)
            {
                x->f_vector = 2;
                x->f_vector_type = gensym("Velocity");
            }
            else if(atom_getlong(argv) == 3)
            {
                x->f_vector = 3;
                x->f_vector_type = gensym("Both");
            }
            else
            {
                x->f_vector = 0;
                x->f_vector_type = gensym("None");
            }
        }
        ebox_invalidate_layer((t_ebox *)x, gensym("vectors_layer"));
    }
    return 0;
}

t_pd_err rotation_type_set(t_hoa_meter *x, void *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        if(atom_gettype(argv) == A_SYM)
        {
            if(atom_getsym(argv) == gensym("Clockwise"))
            {
                x->f_clockwise = 1;
                x->f_clockwise_type = gensym("Clockwise");
            }
            else
            {
                x->f_clockwise = 0;
                x->f_clockwise_type = gensym("Anti-Clockwise");
            }
        }
        else if(atom_gettype(argv) == A_FLOAT)
        {
            if(atom_getlong(argv) == 1)
            {
                x->f_clockwise = 1;
                x->f_clockwise_type = gensym("Clockwise");
            }
            else
            {
                x->f_clockwise = 0;
                x->f_clockwise_type = gensym("Anti-Clockwise");
            }
        }
    }
    return 0;
}

void hoa_meter_dsp(t_hoa_meter *x, t_object *dsp, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_meter->setVectorSize(maxvectorsize);
   
    object_method(dsp, gensym("dsp_add"), x, (method)hoa_meter_perform, 0, NULL);
    
	x->f_startclock = 1;
}

void hoa_meter_perform(t_hoa_meter *x, t_object *dsp, float **ins, long ni, float **outs, long no, long sf, long f,void *up)
{
	x->f_meter->process(ins);
	if (x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void hoa_meter_tick(t_hoa_meter *x)
{
    x->f_meter->processEnergy();
    x->f_meter->processVectors();
    hoa_meter_output(x);
    
    double peak;
    for (int i = 0; i<x->f_number_of_loudspeakers; i++)
    {
        peak = x->f_meter->getLoudspeakerEnergy(i);
        if(peak >= 0.)
            x->f_over_leds_preserved[i] = 1000;
        else
            x->f_over_leds_preserved[i] -= x->f_interval;
        
        if(x->f_over_leds_preserved[i] < 0)
            x->f_over_leds_preserved[i] = 0;
    }
    
	ebox_invalidate_layer((t_ebox *)x, gensym("leds_layers"));
	ebox_invalidate_layer((t_ebox *)x, gensym("vectors_layer"));
  	ebox_redraw((t_ebox *)x);
    
	if (sys_getdspstate())
		clock_delay(x->f_clock, x->f_interval);
}

void hoa_meter_output(t_hoa_meter *x)
{
    long nbChannels = x->f_meter->getNumberOfInputs();
    t_atom*	av_peaks = new t_atom[nbChannels];
    t_atom	av_vectors[4];
    
    for (int i=0; i<nbChannels; i++)
        atom_setfloat(av_peaks+i, fabs(x->f_meter->getLoudspeakerPeaks(i)));
    outlet_list(x->f_outlet_peaks, NULL, nbChannels, av_peaks);
    
    atom_setfloat(av_vectors,   x->f_meter->getEnergyVectorAbscissa());
    atom_setfloat(av_vectors+1, x->f_meter->getEnergyVectorOrdinate());
    atom_setfloat(av_vectors+2, x->f_meter->getVelocityVectorAbscissa());
    atom_setfloat(av_vectors+3, x->f_meter->getVelocityVectorOrdinate());
    outlet_list(x->f_outlet_vector, NULL, 4, av_vectors);
	free(av_peaks);
}

void hoa_meter_free(t_hoa_meter *x)
{
	ebox_free((t_ebox *)x);
    clock_free(x->f_clock);
    delete x->f_meter;
}

void hoa_meter_assist(t_hoa_meter *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_meter->getChannelName(a).c_str());
    else
    {
        if (a == 0)
            sprintf(s,"(list) Vectors Values For Each Metering Interval : Energy(x/y) and Velocity(x/y)");
        else if (a == 1)
            sprintf(s,"(list) Peak Values For Each Metering Interval");
    }
}

t_pd_err hoa_meter_notify(t_hoa_meter *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("attr_modified"))
	{
		ebox_invalidate_layer((t_ebox *)x, gensym("background_layer"));
        ebox_invalidate_layer((t_ebox *)x, gensym("leds_layers"));
        ebox_invalidate_layer((t_ebox *)x, gensym("vectors_layer"));
		ebox_redraw((t_ebox *)x);
	}
	return 0;
}

void hoa_meter_paint(t_hoa_meter *x, t_object *view)
{
	t_rect rect;
    float led_width;
	ebox_get_rect_for_view((t_ebox *)x, &rect);
	
    led_width = 0.49 * rect.width / 18.;
	x->f_radius_global = led_width * 18.;
	x->f_radius_circle = led_width * 4.;
	
	draw_background(x, view, &rect);
    draw_leds(x, view, &rect);
    draw_vectors(x, view, &rect);
}

void draw_background(t_hoa_meter *x,  t_object *view, t_rect *rect)
{
	int i;
    float coso, sino, angle, x1, y1, x2, y2;
    t_rgba black, white;
	t_matrix transform;
	t_elayer *g = ebox_start_layer((t_ebox *)x, gensym("background_layer"), rect->width, rect->height);
    
    black = rgba_addContrast(x->f_color_background, -0.14);
    white = rgba_addContrast(x->f_color_background, 0.06);
    
	if (g)
	{
        egraphics_matrix_init(&transform, 1, 0, 0, -1, rect->width * .5, rect->width * .5);
        egraphics_set_matrix(g, &transform);
        
		egraphics_set_line_width(g, 1.);

		egraphics_set_color_rgba(g, &x->f_color_background);
		egraphics_arc(g, 0.f, 0.f, x->f_radius_global, 0., EPD_2PI);
		egraphics_fill(g);

		egraphics_set_color_rgba(g, &x->f_color_background);
		egraphics_arc(g, 0.f, 0.f, x->f_radius_circle, 0., EPD_2PI);
		egraphics_fill(g);
		
        egraphics_set_color_rgba(g, &white);
        egraphics_set_line_width(g, 1.f);
        egraphics_arc(g, 1, 1, x->f_radius_global,  0., EPD_2PI);
        egraphics_stroke(g);
        egraphics_arc(g, 1, 1, x->f_radius_circle,  0., EPD_2PI);
        egraphics_stroke(g);
        
        egraphics_set_color_rgba(g, &black);
        egraphics_set_line_width(g, 1.f);
        egraphics_arc(g, 0.f, 0.f, x->f_radius_global,  0., EPD_2PI);
        egraphics_stroke(g);
        egraphics_arc(g, 0.f, 0.f, x->f_radius_circle,  0., EPD_2PI);
        egraphics_stroke(g);
        
        if(x->f_number_of_loudspeakers != 1)
        {
            for(i = 0; i < x->f_number_of_loudspeakers; i++)
            {
                angle = x->f_meter->getLoudspeakerAngleMappedRadian(i) - x->f_meter->getLoudspeakerWidthRadian(i) * 0.5f + x->f_offset_of_loudspeakers / 360. * CICM_2PI + CICM_PI2;
                if(x->f_clockwise)
                    angle = -angle + CICM_PI;
                egraphics_set_line_width(g, 1.f);
               
                coso = cosf(angle);
                sino = sinf(angle);
                x1 = x->f_radius_circle * coso;
                y1 = x->f_radius_circle * sino;
                x2 = x->f_radius_global * coso;
                y2 = x->f_radius_global * sino;
                if(Tools::isInsideRad(angle, CICM_PI4, CICM_PI + CICM_PI4))
                {
                    egraphics_move_to(g, x1 - 0.5, y1 - 0.5);
                    egraphics_line_to(g, x2 - 0.5, y2 - 0.5);
                }
                else
                {
                    egraphics_move_to(g, x1 + 0.5, y1 + 0.5);
                    egraphics_line_to(g, x2 + 0.5, y2 + 0.5);
                }
                
                egraphics_set_color_rgba(g, &white);
                egraphics_stroke(g);
                
                
				egraphics_move_to(g, x1, y1);
				egraphics_line_to(g, x2, y2);
                
                egraphics_set_color_rgba(g, &black);
				egraphics_stroke(g);
			}
        }
		ebox_end_layer((t_ebox*)x, gensym("background_layer"));
	}
	ebox_paint_layer((t_ebox *)x, gensym("background_layer"), 0., 0.);
}

void draw_leds(t_hoa_meter *x, t_object *view, t_rect *rect)
{
    int i;
    float j, h, dB;
    float angle_start, angle, angle_end, radius, center_x, center_y;
    float led_width = 0.49 * rect->width / 18.;
    float offset = x->f_offset_of_loudspeakers / 360. * CICM_2PI + CICM_PI2;
    
    t_rgba black = rgba_addContrast(x->f_color_background, -0.14);
	t_elayer *g = ebox_start_layer((t_ebox *)x,  gensym("leds_layers"), rect->width, rect->height);
    
	if (g)
	{
        h = led_width * 17.;
        for(i = 0; i < x->f_meter->getNumberOfLoudspeakers(); i++)
        {
            if(!x->f_clockwise)
                angle   = x->f_meter->getLoudspeakerAngleMappedRadian(i) + offset;
            else
                angle   = -x->f_meter->getLoudspeakerAngleMappedRadian(i) + offset;
            center_x    = pd_abscissa(x->f_radius_global - h, angle);
            center_y    = -pd_ordinate(x->f_radius_global - h, angle);
            
            angle_start = angle - x->f_meter->getLoudspeakerWidthRadian(i) * 0.5f;
            angle_end   = angle + x->f_meter->getLoudspeakerWidthRadian(i) * 0.5f;
            for(j = 11, dB = -34.5; j > -1; j--, dB += 3.)
            {
                radius    = (j + 5.) * led_width;
                
                if(x->f_meter->getLoudspeakerEnergy(i) > dB)
                {
                    if(j > 8)
                        egraphics_set_color_rgba(g, &x->f_color_cold_signal);
                    else if(j > 5)
                        egraphics_set_color_rgba(g, &x->f_color_tepid_signal);
                    else if(j > 2)
                        egraphics_set_color_rgba(g, &x->f_color_warm_signal);
                    else
                        egraphics_set_color_rgba(g, &x->f_color_hot_signal);
                    
                    egraphics_set_line_width(g, led_width - pd_clip_min(360. / rect->width, 2.));
                    egraphics_arc(g, center_x + rect->width * 0.5f, center_y + rect->width * 0.5f, radius, angle_start, angle_end);
                    egraphics_stroke(g);
                }
                else if(j != -1)
                {
                    egraphics_set_color_rgba(g, &black);
                    egraphics_set_line_width(g, led_width - pd_clip_min(360. / rect->width, 2.));
                    egraphics_arc(g, center_x + rect->width * 0.5f, center_y + rect->width * 0.5f, radius,  angle_start, angle_end);
                    egraphics_stroke(g);
                }
            }
            if(x->f_over_leds_preserved[i])
            {
                radius    = (4.) * led_width;
                egraphics_set_color_rgba(g, &x->f_color_over_signal);
                egraphics_set_line_width(g, led_width - pd_clip_min(360. / rect->width, 2.));
                egraphics_arc(g, center_x + rect->width * 0.5f, center_y + rect->width * 0.5f, radius, angle_start, angle_end);
                egraphics_stroke(g);
            }
        }
		ebox_end_layer((t_ebox*)x,  gensym("leds_layers"));
	}
	ebox_paint_layer((t_ebox *)x, gensym("leds_layers"), 0., 0.);
}

void draw_vectors(t_hoa_meter *x, t_object *view, t_rect *rect)
{
	double angle, rayon, x1, y1, size;
	t_matrix transform;
	t_elayer *g = ebox_start_layer((t_ebox *)x,  gensym("vectors_layer"), rect->width, rect->height);
	
	if (g)
	{
		egraphics_matrix_init(&transform, 1, 0, 0, -1, rect->width / 2., rect->width / 2.);
		egraphics_set_matrix(g, &transform);
		size = 1. / 64. * rect->width;
        
		/* Energy */
        if(x->f_vector == 1 || x->f_vector == 3)
        {
            egraphics_set_color_rgba(g, &x->f_color_energy_vector);
            
            rayon = Tools::clip(x->f_meter->getEnergyVectorRadius(), 0., 1.) * x->f_radius_circle * 0.85;
            angle = x->f_meter->getEnergyVectorAngle() + (x->f_offset_of_loudspeakers / 180.) * EPD_PI;
            
            if(!x->f_clockwise)
            {
                x1 = Tools::abscissa(rayon, angle + CICM_PI2);
                y1 = Tools::ordinate(rayon, angle + CICM_PI2);
            }
            else
            {
                x1 = Tools::abscissa(rayon, -angle + CICM_PI2);
                y1 = Tools::ordinate(rayon, -angle + CICM_PI2);
            }
            egraphics_arc(g, x1, y1, size, 0., EPD_2PI);
            egraphics_fill(g);
		}
        if(x->f_vector == 2 || x->f_vector == 3)
        {
            egraphics_set_color_rgba(g, &x->f_color_velocity_vector);
            
            rayon = Tools::clip(x->f_meter->getVelocityVectorRadius(), 0., 1.) * x->f_radius_circle * 0.85;
            angle = x->f_meter->getVelocityVectorAngle() + (x->f_offset_of_loudspeakers / 180.) * EPD_PI;
            
            if(!x->f_clockwise)
            {
                x1 = Tools::abscissa(rayon, angle + CICM_PI2);
                y1 = Tools::ordinate(rayon, angle + CICM_PI2);
            }
            else
            {
                x1 = Tools::abscissa(rayon, -angle + CICM_PI2);
                y1 = Tools::ordinate(rayon, -angle + CICM_PI2);
            }
            egraphics_arc(g, x1, y1, size, 0., EPD_2PI);
            egraphics_fill(g);
		}
		
        
        
		ebox_end_layer((t_ebox*)x,  gensym("vectors_layer"));
	}
	ebox_paint_layer((t_ebox *)x, gensym("vectors_layer"), 0., 0.);
}

