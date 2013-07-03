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

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "z_dsp.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
}

#define MAX_SPEAKER 64
#define DEF_SPEAKER 8

#include "../../Sources/HoaLibrary.h"

typedef struct  _spectrum 
{
	t_pxjbox	j_box;
	AmbisonicsSpectrum* f_spectrum;
    
	void*		f_clock;
	int			f_startclock;
    t_atom_long	f_interval;
    t_atom_long f_number_of_loudspeakers;
	double      f_offset_of_loudspeakers;
    double		f_angles_of_loudspeakers[MAX_SPEAKER];
    double      f_frequency_band[4];
	
} t_spectrum;

t_class *spectrum_class;

void *spectrum_new(t_symbol *s, int argc, t_atom *argv);
void spectrum_free(t_spectrum *x);
void spectrum_assist(t_spectrum *x, void *b, long m, long a, char *s);
void spectrum_tick(t_spectrum *x);


void spectrum_dsp64(t_spectrum *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void spectrum_perform64(t_spectrum *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);


/* Paint *********************************************/
void spectrum_paint(t_spectrum *x, t_object *view);

int C74_EXPORT main()
{
	t_class *c;

	c = class_new("hoa.spectrum~", (method)spectrum_new, (method)spectrum_free, (short)sizeof(t_spectrum), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);

	class_addmethod(c, (method)spectrum_dsp64,			"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)spectrum_assist,         "assist",		A_CANT,	0);
	class_addmethod(c, (method)spectrum_paint,			"paint",		A_CANT,	0);
    
    /* BEHAVIOR */
	CLASS_ATTR_LONG				(c, "loudspeakers", 0 , t_spectrum, f_number_of_loudspeakers);
    CLASS_ATTR_CATEGORY         (c, "loudspeakers", 0, "Behavior");
    //CLASS_ATTR_ACCESSORS		(c, "loudspeakers", NULL, number_of_loudspeakers_set);
	CLASS_ATTR_ORDER			(c, "loudspeakers", 0, "1");
	CLASS_ATTR_LABEL			(c, "loudspeakers", 0, "Number of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "loudspeakers", 1);
    CLASS_ATTR_DEFAULT          (c, "loudspeakers", 0, "8");
    
	CLASS_ATTR_DOUBLE_VARSIZE	(c, "angles", 0, t_spectrum,f_angles_of_loudspeakers, f_number_of_loudspeakers, MAX_SPEAKER);
    CLASS_ATTR_CATEGORY         (c, "angles", 0, "Behavior");
	//CLASS_ATTR_ACCESSORS		(c, "angles", NULL, angles_of_loudspeakers_set);
	CLASS_ATTR_ORDER			(c, "angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "angles", 0, "Angles of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "angles", 1);
	CLASS_ATTR_ALIAS            (c, "angles", "ls_angles");
    
    CLASS_ATTR_DOUBLE_ARRAY     (c, "bands", 0, t_spectrum, f_frequency_band, 4);
    CLASS_ATTR_CATEGORY         (c, "bands", 0, "Behavior");
	//CLASS_ATTR_ACCESSORS		(c, "bands", NULL, angles_of_loudspeakers_set);
	CLASS_ATTR_ORDER			(c, "bands", 0, "3");
	CLASS_ATTR_LABEL			(c, "bands", 0, "Angles of Loudspeakers");
	CLASS_ATTR_SAVE				(c, "bands", 1);
	CLASS_ATTR_ALIAS            (c, "bands", "ls_angles");
    
    CLASS_ATTR_LONG				(c, "interval", 0, t_spectrum, f_interval);
    CLASS_ATTR_CATEGORY         (c, "interval", 0, "Behavior");
	CLASS_ATTR_ORDER			(c, "interval", 0, "4");
	CLASS_ATTR_LABEL			(c, "interval", 0, "Refresh Interval in Milliseconds");
	CLASS_ATTR_FILTER_MIN		(c, "interval", 20);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "50");
	CLASS_ATTR_SAVE				(c, "interval", 1);
    
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
            | JBOX_DRAWBACKGROUND
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;
	jbox_new((t_jbox *)x, flags, argc, argv);

	x->j_box.z_box.b_firstin = (t_object *)x;
	dsp_setupjbox((t_pxjbox *)x, 16);
    x->f_spectrum = new AmbisonicsSpectrum(16, 3, sys_getblksize(), sys_getsr());
	
	x->f_clock = clock_new(x,(method)spectrum_tick);
	x->f_startclock = 0;
    
    attr_dictionary_process(x, d);
	
	jbox_ready((t_jbox *)x);
	
	return (x);
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
    for(int i = 0; i < x->f_spectrum->getNumberOfBands(); i++)
    {
        post("%i amp %f", x->f_spectrum->getAmplitude(i));
        post("%i abs %f", x->f_spectrum->getAbscissa(i));
        post("%i ord %f", x->f_spectrum->getOrdinate(i));
    }
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, 100.);
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
    sprintf(s,"(Signal) %s", x->f_spectrum->getLoudspeakerName(a).c_str());
}

void spectrum_paint(t_spectrum *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
}

