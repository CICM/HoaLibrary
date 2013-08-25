/**
 HoaLibrary : A High Order Ambisonics Library
 Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 All rights reserved.
 
 Website  : http://www.mshparisnord.fr/hoalibrary/
 Contacts : cicm.mshparisnord@gmail.com

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIALL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "../MaxConverter.h"

#define DEF_SPEAKER 8
#define MAX_FREQ_BANDS 5
#define OVERLED_DRAWTIME 1000

typedef struct  _spectrum
{
	t_pxjbox	j_box;
    t_rect      f_rect;
	t_atom_long f_drawmborder;
	void*		f_clock;
	int			f_startclock;
	t_atom_long	f_interval;
    
    t_atom_long f_number_of_loudspeakers;	
	double		f_angles_of_loudspeakers[MAX_SPEAKER];
    t_atom_long f_number_of_bands;
    
	t_jrgba		f_color_background;
	t_jrgba		f_color_circle_background;
	t_jrgba		f_color_border;
	t_jrgba		f_color_bands[5];
    
    double      f_circleExtRadius;
	
	t_pt		f_center;
    
    void*       f_vector_outlet;
    void*       f_amplitude_outlet;
	
    AmbisonicSpectrum* f_spectrum;
} t_spectrum;

t_class *spectrum_class;

/* Common ------------------------------------- */
void *spectrum_new(t_symbol *s, int argc, t_atom *argv);
void spectrum_free(t_spectrum *x);
void spectrum_assist(t_spectrum *x, void *b, long m, long a, char *s);
/* DSP ------------------------------------- */
void spectrum_dsp64(t_spectrum *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void spectrum_perform64(t_spectrum *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void spectrum_tick(t_spectrum *x);
void spectrum_output(t_spectrum *x);

t_max_err spectrum_notify(t_spectrum *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err number_of_loudspeakers_set(t_spectrum *x, t_object *attr, long argc, t_atom *argv);
t_max_err angles_of_loudspeakers_set(t_spectrum *x, void *attr, long ac, t_atom *av);
t_max_err set_attr_nbands(t_spectrum *x, void *attr, long ac, t_atom *av);

/* Paint ------------------------------------- */
void spectrum_getdrawparams(t_spectrum *x, t_object *patcherview, t_jboxdrawparams *params);
void spectrum_paint(t_spectrum *x, t_object *view);

void draw_background(t_spectrum *x, t_object *view, t_rect *rect);
void draw_spectrum(t_spectrum *x,  t_object *view, t_rect *rect);
void draw_background(t_spectrum *x,  t_object *view, t_rect *rect);

int C74_EXPORT main()
{
	t_class *c;
    
	c = class_new("hoa.spectrum~", (method)spectrum_new, (method)spectrum_free, (short)sizeof(t_spectrum), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);
	
	class_addmethod(c, (method) spectrum_dsp64,         "dsp64",		  A_CANT, 0);
	class_addmethod(c, (method) spectrum_assist,		"assist",		  A_CANT, 0);
	class_addmethod(c, (method) spectrum_paint,         "paint",		  A_CANT, 0);
	class_addmethod(c, (method) spectrum_notify,        "notify",		  A_CANT, 0);
    class_addmethod(c, (method) spectrum_getdrawparams, "getdrawparams",  A_CANT, 0);
    
	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 225 225");
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	
	/* BEHAVIOR */
    CLASS_STICKY_CATEGORY       (c, 0, "Behavior");
    
	CLASS_ATTR_LONG				(c, "loudspeakers", 0 , t_spectrum, f_number_of_loudspeakers);
    CLASS_ATTR_ACCESSORS		(c, "loudspeakers", NULL, number_of_loudspeakers_set);
	CLASS_ATTR_ORDER			(c, "loudspeakers", 0, "1");
	CLASS_ATTR_LABEL			(c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "loudspeakers", 1);
    CLASS_ATTR_DEFAULT          (c, "loudspeakers", 0, "8");
    
	CLASS_ATTR_DOUBLE_VARSIZE	(c, "angles", 0, t_spectrum,f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
	CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_of_loudspeakers_set);
	CLASS_ATTR_ORDER			(c, "angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "angles", 1);
    
    CLASS_ATTR_LONG				(c, "nbands", 0, t_spectrum, f_number_of_bands);
    CLASS_ATTR_ACCESSORS		(c, "nbands", NULL, set_attr_nbands);
    CLASS_ATTR_ORDER			(c, "nbands", 0, "3");
	CLASS_ATTR_LABEL			(c, "nbands", 0, "Number of Frequency Bands");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "nbands", 0, "3");
    
    CLASS_ATTR_LONG				(c, "interval", 0, t_spectrum, f_interval);
	CLASS_ATTR_ORDER			(c, "interval", 0, "4");
	CLASS_ATTR_LABEL			(c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN		(c, "interval", 20);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "50");
	CLASS_ATTR_SAVE				(c, "interval", 1);
    
    CLASS_STICKY_CATEGORY_CLEAR (c);
	
	/* COLORS */
    CLASS_STICKY_CATEGORY       (c, 0, "Color");
    CLASS_STICKY_ATTR           (c, "style", 0, "rgba");
    
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_spectrum, f_color_background);
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"bgcolor", 0, "0.55 0.55 0.55 1.");
	
	CLASS_ATTR_RGBA				(c, "cbgcolor", 0, t_spectrum, f_color_circle_background);
	CLASS_ATTR_LABEL			(c, "cbgcolor", 0, "Circle Background Color");
	CLASS_ATTR_ORDER			(c, "cbgcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"cbgcolor", 0, "0.4 0.4 0.4 1.");
	
	CLASS_ATTR_RGBA				(c, "bordercolor", 0, t_spectrum, f_color_border);
	CLASS_ATTR_LABEL			(c, "bordercolor", 0, "Box Border Color");
	CLASS_ATTR_ORDER			(c, "bordercolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"bordercolor", 0, "0.25 0.25 0.25 1");
	
	CLASS_ATTR_RGBA				(c, "bandcolor1", 0, t_spectrum, f_color_bands[0]);
	CLASS_ATTR_LABEL			(c, "bandcolor1", 0, "Band 1 Color");
	CLASS_ATTR_ORDER			(c, "bandcolor1", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"bandcolor1", 0, "0.9 0. 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "bandcolor2", 0, t_spectrum, f_color_bands[1]);
	CLASS_ATTR_LABEL			(c, "bandcolor2", 0, "Band 2 Color");
	CLASS_ATTR_ORDER			(c, "bandcolor2", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bandcolor2", 0, "0.6 0.73 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "bandcolor3", 0, t_spectrum, f_color_bands[2]);
	CLASS_ATTR_LABEL			(c, "bandcolor3", 0, "Band 3 Color");
	CLASS_ATTR_ORDER			(c, "bandcolor3", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bandcolor3", 0, ".85 .85 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "bandcolor4", 0, t_spectrum, f_color_bands[3]);
	CLASS_ATTR_LABEL			(c, "bandcolor4", 0, "Band 4 Color");
	CLASS_ATTR_ORDER			(c, "bandcolor4", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bandcolor4", 0, "1. 0.6 0. 0.8");
	
	CLASS_ATTR_RGBA				(c, "bandcolor5", 0, t_spectrum, f_color_bands[4]);
	CLASS_ATTR_LABEL			(c, "bandcolor5", 0, "Band 5 Color");
	CLASS_ATTR_ORDER			(c, "bandcolor5", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bandcolor5", 0, "1. 0. 0. 0.8");
	
    CLASS_STICKY_ATTR_CLEAR(c, "style");
    CLASS_STICKY_CATEGORY_CLEAR(c);
	
	class_register(CLASS_BOX, c);
	spectrum_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *spectrum_new(t_symbol *s, int argc, t_atom *argv)
{
	t_spectrum *x =  NULL;
	t_dictionary *d;
	long flags;
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
    
	x = (t_spectrum *)object_alloc(spectrum_class);
	flags = 0
    | JBOX_DRAWFIRSTIN
    | JBOX_DRAWINLAST
    | JBOX_TRANSPARENT
    | JBOX_DRAWBACKGROUND
    | JBOX_GROWY
    ;
    
    x->f_number_of_loudspeakers = 8;
    x->f_number_of_bands        = 3;
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
    
	dsp_setupjbox((t_pxjbox *)x, x->f_number_of_loudspeakers);
    x->f_amplitude_outlet = listout(x);
    x->f_vector_outlet = listout(x);
    
    x->f_spectrum = new AmbisonicSpectrum(x->f_number_of_loudspeakers, x->f_number_of_bands, sys_getmaxblksize(), sys_getsr());
    
    dictionary_getlong(d, gensym("loudspeakers"), &x->f_number_of_loudspeakers);
    
    x->f_spectrum->setNumberOfLoudspeakers(x->f_number_of_loudspeakers);
    x->f_number_of_loudspeakers = x->f_spectrum->getNumberOfInputs();

	attr_dictionary_process(x, d);
	
	x->f_clock = clock_new(x,(method)spectrum_tick);
	x->f_startclock = 0;
	
	jbox_ready((t_jbox *)x);
	
	return (x);
}

void spectrum_getdrawparams(t_spectrum *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = 1.;
	params->d_cornersize = 8;
    params->d_bordercolor = x->f_color_border;
    params->d_boxfillcolor = x->f_color_background;
}

t_max_err number_of_loudspeakers_set(t_spectrum *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc && argv)
    {
        t_atom* state = CicmMax::dsp_stop((t_object *)x);
        
        if(atom_gettype(argv) == A_LONG || atom_gettype(argv) == A_FLOAT)
            x->f_number_of_loudspeakers = Tools::clip(atom_getfloat(argv), 1, MAX_SPEAKER);
                
        if (x->f_number_of_loudspeakers == 1)
            object_attr_setdisabled((t_object*)x, gensym("angles"), 1);
        else
            object_attr_setdisabled((t_object*)x, gensym("angles"), 0);
        
        x->f_spectrum->setNumberOfLoudspeakers(x->f_number_of_loudspeakers);
        
        CicmMax::resize_inlet((t_object *)x, x->f_spectrum->getNumberOfInputs());
        CicmMax::dsp_start(state);
        
        object_attr_touch((t_object *)x, gensym("angles"));
    }
    return NULL;
}

t_max_err angles_of_loudspeakers_set(t_spectrum *x, void *attr, long ac, t_atom *av)
{
    if (ac && av)
    {
        for(int i = 0; i < ac && i < x->f_number_of_loudspeakers; i++)
        {
            if(atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG)
                x->f_spectrum->setLoudspeakerAngle(i, atom_getfloat(av+i));
        }
        
    }
    
    for (int i = 0; i < x->f_spectrum->getNumberOfInputs(); i++)
    {
        x->f_angles_of_loudspeakers[i] = x->f_spectrum->getLoudspeakerAngle(i);
    }
    
	jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("spectrum_layer"));
	jbox_redraw((t_jbox *)x);
    return MAX_ERR_NONE;
}

t_max_err set_attr_nbands(t_spectrum *x, void *attr, long ac, t_atom *av)
{
    if (ac && av)
    {
        if(atom_gettype(av) == A_FLOAT || atom_gettype(av) == A_LONG)
            x->f_spectrum->setNumberOfBands(atom_getlong(av));
        
        x->f_number_of_bands = x->f_spectrum->getNumberOfBands();
    
        jbox_invalidate_layer((t_object *)x, NULL, gensym("spectrum_layer"));
        jbox_redraw((t_jbox *)x);
    }
    
    return MAX_ERR_NONE;
}

void spectrum_dsp64(t_spectrum *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_spectrum->setVectorSize(maxvectorsize);
    x->f_spectrum->setSamplingRate(samplerate);
	object_method(dsp64, gensym("dsp_add64"), x, spectrum_perform64, 0, NULL);
	x->f_startclock = 1;
}

void spectrum_perform64(t_spectrum *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	x->f_spectrum->process(ins);
    
	if (x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void spectrum_tick(t_spectrum *x)
{
    x->f_spectrum->tick();
    spectrum_output(x);
    
	jbox_invalidate_layer((t_object *)x, NULL, gensym("spectrum_layer"));
	jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, x->f_interval);
}

void spectrum_output(t_spectrum *x)
{
    t_atom	amplitude[x->f_spectrum->getNumberOfBands()];
    t_atom	vectors[x->f_spectrum->getNumberOfBands()*2];
    
    for (int i = 0; i < x->f_spectrum->getNumberOfBands(); i++)
    {
        atom_setfloat(amplitude+i, x->f_spectrum->getAmplitude(i));
        atom_setfloat(vectors+i*2,   x->f_spectrum->getLogAbscissa(i));
        atom_setfloat(vectors+i*2+1, x->f_spectrum->getLogOrdinate(i));
    }
    
    outlet_list(x->f_amplitude_outlet, NULL, x->f_spectrum->getNumberOfBands(), amplitude);
    outlet_list(x->f_vector_outlet, NULL, x->f_spectrum->getNumberOfBands()*2, vectors);
}

void spectrum_free(t_spectrum *x)
{
	dsp_freejbox((t_pxjbox *)x);
	freeobject((t_object *)x->f_clock);
	jbox_free((t_jbox *)x);
    delete x->f_spectrum;
}

void spectrum_assist(t_spectrum *x, void *b, long m, long a, char *s)
{
	if(m == ASSIST_INLET)
        sprintf(s,"(Signal) %s", x->f_spectrum->getLoudspeakerName(a).c_str());
    else
    {
        if(a == 0)
            sprintf(s,"(list) Energy Vectors Coordinates");
        else
            sprintf(s,"(list) Amplitudes Values");
    }
}

t_max_err spectrum_notify(t_spectrum *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		if(name == gensym("cbgcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
		else if(name == gensym("bandcolor1") || name == gensym("bandcolor2") || name == gensym("bandcolor3") || name == gensym("bandcolor4") || name == gensym("bandcolor5") || name == gensym("nbands"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("spectrum_layer"));
		}
        jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void spectrum_paint(t_spectrum *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
    
    x->f_rect = rect;
	x->f_center.x = rect.width * .5;
	x->f_center.y = rect.height * .5;
    x->f_circleExtRadius = Tools::cicm_min(rect.width, rect.height)*0.5 - 3;
	
	draw_background(x, view, &rect);
    draw_spectrum(x, view, &rect);
}

void draw_background(t_spectrum *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
    t_jmatrix transform;
    t_jrgba black, white;
    int nInnerCircles = 4;
    double contrastBlack = 0.08;
    double contrastWhite = 0.08;
    black = white = x->f_color_circle_background;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
    
    double dashes[2] = {6, 4};
	
	if (g)
	{
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
        jgraphics_set_matrix(g, &transform);
        
        jgraphics_set_source_jrgba(g, &x->f_color_circle_background);
        jgraphics_arc(g, 0, 0, x->f_circleExtRadius,  0., JGRAPHICS_2PI);
        jgraphics_fill(g);
        
        jgraphics_set_line_width(g, 3.);
        jgraphics_set_source_jrgba(g, &black);
        jgraphics_arc(g, 0, 0, x->f_circleExtRadius-1,  0., JGRAPHICS_2PI);
        jgraphics_stroke(g);
        
        jgraphics_set_line_width(g, 2.);
        jgraphics_set_source_jrgba(g, &white);
        jgraphics_arc(g, 0, 0, x->f_circleExtRadius-1,  0., JGRAPHICS_2PI);
        jgraphics_stroke(g);
        
        dashes[0] = (x->f_circleExtRadius/nInnerCircles)*0.25 ;
        dashes[1] = (x->f_circleExtRadius/nInnerCircles)*0.5 ;
        jgraphics_set_dash(g, dashes, 2, 0);
        
        jgraphics_set_line_width(g, 1.);
        for (int i = nInnerCircles-1; i > 0; i--)
        {
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_arc(g, 0.5, -0.5, (x->f_circleExtRadius/nInnerCircles) * double(i),  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
            
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_arc(g, -0.5, 0.5, (x->f_circleExtRadius/nInnerCircles) * double(i),  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
        }
        
        dashes[0] = (x->f_circleExtRadius/nInnerCircles)*0.5 ;
        dashes[1] = (x->f_circleExtRadius/nInnerCircles)*0.5 ;
        
        jgraphics_set_dash(g, dashes, 2, 0);
        jgraphics_set_line_width(g, 1.);
        
        // top
        jgraphics_set_source_jrgba(g, &white);
        jgraphics_move_to(g, 0.5, long( (x->f_circleExtRadius/nInnerCircles)*0.25 ));
        jgraphics_line_to(g, 0.5, x->f_circleExtRadius - 4);
        jgraphics_stroke(g);
        
        jgraphics_set_source_jrgba(g, &black);
        jgraphics_set_line_width(g, 1.);
        jgraphics_move_to(g, -0.5, long( (x->f_circleExtRadius/nInnerCircles)*0.25 ));
        jgraphics_line_to(g, -0.5, x->f_circleExtRadius - 4);
        jgraphics_stroke(g);
        
        // bottom
        jgraphics_set_source_jrgba(g, &white);
        jgraphics_move_to(g, 0.5, - long( (x->f_circleExtRadius/nInnerCircles)*0.25 ));
        jgraphics_line_to(g, 0.5, - x->f_circleExtRadius + 4);
        jgraphics_stroke(g);
        
        jgraphics_set_source_jrgba(g, &black);
        jgraphics_set_line_width(g, 1.);
        jgraphics_move_to(g, -0.5, - long( (x->f_circleExtRadius/nInnerCircles)*0.25 ));
        jgraphics_line_to(g, -0.5, - x->f_circleExtRadius + 4);
        jgraphics_stroke(g);
        
        jgraphics_rotate(g, -CICM_PI2);
        
        // top
        jgraphics_set_source_jrgba(g, &white);
        jgraphics_move_to(g, 0.5, long( (x->f_circleExtRadius/nInnerCircles)*0.25 ));
        jgraphics_line_to(g, 0.5, x->f_circleExtRadius - 4);
        jgraphics_stroke(g);
        
        jgraphics_set_source_jrgba(g, &black);
        jgraphics_set_line_width(g, 1.);
        jgraphics_move_to(g, -0.5, long( (x->f_circleExtRadius/nInnerCircles)*0.25 ));
        jgraphics_line_to(g, -0.5, x->f_circleExtRadius - 4);
        jgraphics_stroke(g);
        
        // bottom
        jgraphics_set_source_jrgba(g, &white);
        jgraphics_move_to(g, 0.5, - long( (x->f_circleExtRadius/nInnerCircles)*0.25 ));
        jgraphics_line_to(g, 0.5, - x->f_circleExtRadius + 4);
        jgraphics_stroke(g);
        
        jgraphics_set_source_jrgba(g, &black);
        jgraphics_set_line_width(g, 1.);
        jgraphics_move_to(g, -0.5, - long( (x->f_circleExtRadius/nInnerCircles)*0.25 ));
        jgraphics_line_to(g, -0.5, - x->f_circleExtRadius + 4);
        jgraphics_stroke(g);
        
        /*
        jgraphics_set_source_jrgba(g, &white);
        jgraphics_arc(g, x->f_center.x, x->f_center.y, x->f_circleExtRadius,  0., JGRAPHICS_2PI);
        jgraphics_fill(g);
        
        jgraphics_set_source_jrgba(g, &black);
        jgraphics_arc(g, x->f_center.x, x->f_center.y, x->f_circleExtRadius,  0., JGRAPHICS_2PI);
        jgraphics_stroke(g);
         
        */
        
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_spectrum(t_spectrum *x, t_object *view, t_rect *rect)
{
    t_jpattern *pattern;
    t_jmatrix transform;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("spectrum_layer"), rect->width, rect->height);
    t_pt coord;
    
    //t_jrgba white = {1., 1., 1., 0.15};
    //t_jrgba black = {0., 0., 0., 0.3};
    t_jrgba zeroColor = {0., 0., 0., 0.};
    /*
    t_jrgba black, white;
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
    black = white = x->f_color_circle_background;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
    */
    
	if (g)
	{
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
        jgraphics_set_matrix(g, &transform);
        
        /*
        coord.x = x->f_circleExtRadius * 0.25;
        coord.y = x->f_circleExtRadius * -0.25;
        
        jgraphics_translate(g, coord.x, coord.y);
        
        pattern = jgraphics_pattern_create_radial(0, 0, 0, x->f_circleExtRadius, x->f_circleExtRadius, 0);
        
        jgraphics_pattern_add_color_stop_rgba(pattern, 0., black.red, black.green, black.blue, black.alpha);
        
        jgraphics_pattern_add_color_stop_rgba(pattern, 1.,
                                              zeroColor.red, zeroColor.green, zeroColor.blue, zeroColor.alpha);
        
        jgraphics_set_source(g, pattern);
        jgraphics_translate(g, -coord.x, -coord.y);
        jgraphics_arc(g, 0, 0, x->f_circleExtRadius-1, 0, CICM_2PI);
        jgraphics_fill(g);
        */
        
        jgraphics_set_line_width(g, 1);
        for(int i = 0; i < x->f_spectrum->getNumberOfBands(); i++)
        {
            coord.x = x->f_spectrum->getLogAbscissa(i) * x->f_circleExtRadius * 1.2;
            coord.y = x->f_spectrum->getLogOrdinate(i) * x->f_circleExtRadius * 1.2;
            
            jgraphics_translate(g, coord.x, coord.y);
            
            pattern = jgraphics_pattern_create_radial(0, 0, 0, x->f_circleExtRadius, x->f_circleExtRadius, 0);
            
            jgraphics_pattern_add_color_stop_rgba(pattern, 0.,
                                                  x->f_color_bands[i].red,
                                                  x->f_color_bands[i].green,
                                                  x->f_color_bands[i].blue,
                                                  x->f_color_bands[i].alpha);
            
            
            jgraphics_pattern_add_color_stop_rgba(pattern, 0.7 * x->f_spectrum->getLogAmplitude(i),
                                                  zeroColor.red, zeroColor.green, zeroColor.blue, zeroColor.alpha);
            
            
            jgraphics_pattern_add_color_stop_rgba(pattern, 1.,
                                                  zeroColor.red, zeroColor.green, zeroColor.blue, zeroColor.alpha);
            
            jgraphics_set_source(g, pattern);
            jgraphics_translate(g, -coord.x, -coord.y);
            jgraphics_arc(g, 0, 0, x->f_circleExtRadius-3, 0, CICM_2PI);
            jgraphics_fill(g);
            
        }
        
        /*
        coord.x = x->f_circleExtRadius * -0.5;
        coord.y = x->f_circleExtRadius * 0.5;
        
        jgraphics_translate(g, coord.x, coord.y);
        
        pattern = jgraphics_pattern_create_radial(0, 0, 0, x->f_circleExtRadius, x->f_circleExtRadius, 0);
        
        jgraphics_pattern_add_color_stop_rgba(pattern, 0., white.red, white.green, white.blue, white.alpha);
        
        jgraphics_pattern_add_color_stop_rgba(pattern, 1.,
                                              zeroColor.red, zeroColor.green, zeroColor.blue, zeroColor.alpha);
        
        jgraphics_set_source(g, pattern);
        jgraphics_translate(g, -coord.x, -coord.y);
        jgraphics_arc(g, 0, 0, x->f_circleExtRadius-1, 0, CICM_2PI);
        jgraphics_fill(g);
        */
        
        jgraphics_pattern_destroy(pattern);
		jbox_end_layer((t_object*)x, view, gensym("spectrum_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("spectrum_layer"), 0., 0.);
}

