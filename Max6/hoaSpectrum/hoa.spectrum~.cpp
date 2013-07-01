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

#include "../../Sources/HoaLibrary.h"

typedef struct  _spectrum 
{
	t_pxjbox	j_box;
	
	void*		f_clock;
	int			f_startclock;
    
    AmbisonicsSpectrum* f_spectrum;
	
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
    x->f_spectrum = new AmbisonicsSpectrum(16, 512, sys_getblksize(), sys_getsr());
	
	x->f_clock = clock_new(x,(method)spectrum_tick);
	x->f_startclock = 0;
    
    attr_dictionary_process(x, d);
	
	jbox_ready((t_jbox *)x);
	
	return (x);
}


void spectrum_dsp64(t_spectrum *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_spectrum->setVectorSize(maxvectorsize);
	object_method(dsp64, gensym("dsp_add64"), x, spectrum_perform64, 0, NULL);
	//x->f_startclock = 1;
}

void spectrum_perform64(t_spectrum *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    x->f_spectrum->process(ins);
    /*
	if (x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}*/
}

void spectrum_tick(t_spectrum *x)
{
    /*
    
	jbox_invalidate_layer((t_object *)x, NULL, gensym("contrib_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, 100.);
     */
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
    sprintf(s,"(Signal) %ld", a);
}

void spectrum_paint(t_spectrum *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
}

