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
 
#ifdef WIN_VERSION
#define _CRT_SECURE_NO_DEPRECATE
#endif

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "ext_parameter.h"
#include "z_dsp.h"

#ifdef WIN_VERSION
#include <float.h>
#endif
}

#include "../CicmLibrary/CicmDefine.h"
#include "../CicmLibrary/CicmTools.h"
#include "CicmLine.h"

#define MAX_IO 64
#define MIN_IO 1
#define DEF_IO 8

static t_class	*s_hoaGain_class = 0;
static t_symbol *ps_slider, *ps_hslider, *ps_preset;

// mouse tracking stuff

static t_pt s_hoaGain_cum;
static double s_hoaGain_startval;

#define INRANGE(v,lo,hi) ((v)<=(hi)&&(v)>=(lo))

#define	hoaGain_BORDERTHICKNESS			(2.)
#define hoaGain_CORNERSIZE				(6.)

#define hoaGain_DISPLAYINSET			(11)	// amount subtracted from rect for value
#define knobMargin                      (4)		// Knob Margin
#define knobRound                       (8)		// Knob Round

enum inputmode {
DECIBELS = 0,
AMPLITUDE = 1,
MIDI = 2
};

typedef struct _hoaGain
{
	t_pxjbox	j_box;
	double		j_min;			
	double		j_size;			// number of steps
	double		j_val;
	char		j_relative;		// relative mousing (like orig miller slider, but not like h/uslider)
	char		j_orientation;	// 0 = auto, 1 = horiz, 2 = vertical
	t_jrgba		j_brgba;
	t_jrgba		j_frgba2;
    t_jrgba     j_knobcolor;
    t_jrgba     j_intknobcolor;
    
    // gain
    CicmLine*   f_amp;
    char        f_inputMode;
    float       f_range[2];
    double      j_valdB;
    double      j_defaultValuedB;
    
    //inputs/output
    void*       f_inlet_val;
    void*       f_outlet_infos;
    
    // options
    double          f_interp;
    t_atom_long     f_numberOfChannels;
    
} t_hoaGain;

void *hoaGain_new(t_symbol *s, short argc, t_atom *argv);
void hoaGain_free(t_hoaGain *x);
t_max_err hoaGain_notify(t_hoaGain *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void hoaGain_assist(t_hoaGain *x, void *b, long m, long a, char *s);
void hoaGain_preset(t_hoaGain *x);
void *hoaGain_stdargs(t_dictionary *d, t_symbol *s, long argc, t_atom *argv);
void hoaGain_tometer(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv);
void HoaGain_reconnect_outlet(t_hoaGain *x);
/* DSP ------------------------------------- */
void hoaGain_dsp(t_hoaGain *x, t_signal **sp, short *count);
t_int *hoaGain_perform(t_int *w);
void hoaGain_dsp64(t_hoaGain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoaGain_perform64(t_hoaGain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoaGain_tick(t_hoaGain *x);
void hoaGain_output_dB(t_hoaGain *x);
/* Paint ------------------------------------- */
long hoaGain_oksize(t_hoaGain *x, t_rect *newrect);
void hoaGain_paint(t_hoaGain *x, t_object *view);
void draw_cursor(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz);
void draw_background(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz);
void draw_dB_grid(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz);
void hoaGain_getdrawparams(t_hoaGain *x, t_object *patcherview, t_jboxdrawparams *params);
/* Input ------------------------------------- */
void hoaGain_bang(t_hoaGain *x);
void hoaGain_int(t_hoaGain *x, long n);
void hoaGain_float(t_hoaGain *x, double f);
void hoaGain_float_dB(t_hoaGain *x, double dBValue); // for mouse value setting
void hoaGain_set_dB(t_hoaGain *x, double dBValue);
void hoaGain_set(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv);
void hoaGain_setminmax(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv);
void hoaGain_contextValue(t_hoaGain *x, long valueType, double value);
void hoaGain_setInputModeValue(t_hoaGain *x, double value, bool outputTheValue);
double hoaGain_getInputModeValue(t_hoaGain *x);
t_max_err hoaGain_setattr_interp(t_hoaGain *x, t_object *attr, long ac, t_atom *av);
t_max_err hoaGain_setattr_channels(t_hoaGain *x, t_object *attr, long ac, t_atom *av);
void hoaGain_resize_io(t_hoaGain *x, long newNumberOfChannel);
t_max_err hoaGain_setattr_range(t_hoaGain *x, t_object *attr, long ac, t_atom *av);
t_max_err hoaGain_setvalueof(t_hoaGain *x, long ac, t_atom *av);
t_max_err hoaGain_getvalueof(t_hoaGain *x, long *ac, t_atom **av);
/* Utility ------------------------------------- */
void hoaGain_assign(t_hoaGain *x, double f, long notify);
double hoaGain_constrain(t_hoaGain *x, double f);
double hoaGain_constrain_real_value(t_hoaGain *x, double f);
char hoaGain_ishorizontal(t_hoaGain *x, t_rect *r);
double hoaGain_postoval(t_hoaGain *x, t_pt pt, t_rect *r, char ishoriz);
double hoaGain_valtopos(t_hoaGain *x, double val, t_rect *r, char ishoriz);
double hoaGain_dBvaltopos(t_hoaGain *x, double dBval, t_rect *r, char ishoriz);
double hoaGain_dbtoval(t_hoaGain *x, double dBval);
double hoaGain_valtodb(t_hoaGain *x, double val);
/* Mouse ------------------------------------- */
void hoaGain_mousedoubleclick(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaGain_mousedown(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaGain_mousedragdelta(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaGain_mouseup(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers);

void hoaGain_set_gain(t_hoaGain *x);

void hoaGain_drawPopupValue(t_hoaGain *x);

int C74_EXPORT main()
{
	t_class *c; 

	common_symbols_init();

	c = class_new("hoa.gain~", (method)hoaGain_new, (method)hoaGain_free, sizeof(t_hoaGain), (method)NULL, A_GIMME, 0L);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY; // to specify dictionary constructor

    class_dspinitjbox(c);
	jbox_initclass(c, JBOX_FIXWIDTH | JBOX_COLOR );
    
    class_addmethod (c, (method) hoaGain_dsp,                 "dsp",                  A_CANT, 0);
	class_addmethod (c, (method) hoaGain_dsp64,               "dsp64",                A_CANT, 0);
	class_addmethod (c, (method) hoaGain_paint,               "paint",                A_CANT, 0);
	class_addmethod (c, (method) hoaGain_int,                 "int",                  A_LONG, 0);
	class_addmethod (c, (method) hoaGain_float,               "float",                A_FLOAT, 0);
    class_addmethod (c, (method) hoaGain_contextValue,        "contextvalue", A_LONG, A_FLOAT, 0);
	class_addmethod (c, (method) hoaGain_bang,                "bang",                         0);
	class_addmethod (c, (method) hoaGain_set,                 "set",                  A_GIMME, 0);
	class_addmethod (c, (method) hoaGain_getdrawparams,       "getdrawparams",        A_CANT, 0);
    class_addmethod (c, (method) hoaGain_mousedoubleclick,    "mousedoubleclick",     A_CANT, 0);
	class_addmethod (c, (method) hoaGain_mousedown,           "mousedown",            A_CANT, 0);
	class_addmethod (c, (method) hoaGain_mousedragdelta,      "mousedragdelta",       A_CANT, 0);
	class_addmethod (c, (method) hoaGain_mouseup,             "mouseup",              A_CANT, 0);
	class_addmethod (c, (method) hoaGain_getvalueof,          "getvalueof",           A_CANT, 0);
	class_addmethod (c, (method) hoaGain_setvalueof,          "setvalueof",           A_CANT, 0);
	class_addmethod (c, (method) hoaGain_assist,              "assist",               A_CANT, 0);
	class_addmethod (c, (method) hoaGain_preset,              "preset",                       0);
	class_addmethod (c, (method) hoaGain_notify,              "notify",               A_CANT, 0); 
	class_addmethod (c, (method) hoaGain_oksize,              "oksize",               A_CANT, 0);
    class_addmethod (c, (method) hoaGain_tometer,             "anything",             A_GIMME, 0);
    
	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 200. 30.");
	
	CLASS_STICKY_CATEGORY   (c,0,"Value");
    CLASS_ATTR_DOUBLE       (c, "interp", 0, t_hoaGain, f_interp);
	CLASS_ATTR_ACCESSORS    (c, "interp",(method)NULL,(method)hoaGain_setattr_interp);
    CLASS_ATTR_LABEL        (c, "interp", 0, "Ramp Time (ms)");
    CLASS_ATTR_FILTER_MIN   (c, "interp", 0);
	
	CLASS_ATTR_CHAR(c,"relative", 0, t_hoaGain, j_relative);
	CLASS_ATTR_LABEL(c,"relative", 0, "Mousing Mode");
	CLASS_ATTR_ENUMINDEX2(c, "relative", 0, "Absolute", "Relative");
	CLASS_ATTR_BASIC(c, "relative", 0);
    
    CLASS_ATTR_CHAR(c,"inputmode", 0, t_hoaGain, f_inputMode);
	CLASS_ATTR_LABEL(c,"inputmode", 0, "Input Mode");
	CLASS_ATTR_ENUMINDEX3(c, "inputmode", 0, "DeciBels", "Amplitude", "Midi");
    
    CLASS_ATTR_DOUBLE       (c, "defvaldb", 0, t_hoaGain, j_defaultValuedB);
    CLASS_ATTR_LABEL        (c, "defvaldb", 0, "Default Value (dB)");
	CLASS_STICKY_CATEGORY_CLEAR(c);
	
	CLASS_ATTR_CHAR(c,"orientation",0,t_hoaGain,j_orientation);
	CLASS_ATTR_LABEL(c,"orientation",0,"Orientation");
	CLASS_ATTR_ENUMINDEX3(c,"orientation", 0,"Automatic", "Horizontal", "Vertical");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "orientation", 0, "0");
	CLASS_ATTR_CATEGORY(c, "orientation", 0, "Appearance");
	
	CLASS_STICKY_CATEGORY(c, 0, "Color");
	CLASS_ATTR_RGBA_LEGACY(c, "bgcolor", "brgb", 0, t_hoaGain, j_brgba);
	CLASS_ATTR_ALIAS(c,"bgcolor", "brgba");
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c,"bgcolor",0,"0.35 0.35 0.35 1.");
	CLASS_ATTR_STYLE_LABEL(c, "bgcolor", 0, "rgba", "Background Color");
	class_parameter_register_default_color(c, gensym("bgcolor"), ps_control_text_bg);
	CLASS_ATTR_BASIC(c, "bgcolor", 0);
	
	CLASS_ATTR_RGBA_LEGACY(c,"bordercolor", "rgb2",0, t_hoaGain, j_frgba2);
	CLASS_ATTR_ALIAS(c,"bordercolor", "rgba2");
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c,"bordercolor",0,"0.2 0.2 0.2 1.");
	CLASS_ATTR_STYLE_LABEL(c,"bordercolor",0,"rgba","Border Color");
	class_parameter_register_default_color(c, gensym("bordercolor"), ps_control_bg);
    
    CLASS_ATTR_RGBA				(c, "knobcolor", 0, t_hoaGain, j_knobcolor);
    CLASS_ATTR_STYLE_LABEL      (c, "knobcolor", 0, "rgba","Knob Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "knobcolor", 0, "0.16 0.16 0.16 1");
    
    CLASS_ATTR_RGBA				(c, "intknobcolor", 0, t_hoaGain, j_intknobcolor);
    CLASS_ATTR_STYLE_LABEL      (c, "intknobcolor", 0, "rgba","Interior Knob Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "intknobcolor", 0, "0.9 0.9 0.9 1");
	CLASS_STICKY_CATEGORY_CLEAR(c);

	CLASS_ATTR_INVISIBLE(c, "color", 0);
	CLASS_ATTR_ATTR_PARSE(c, "color","save", USESYM(long), 0, "0");

	CLASS_ATTR_DEFAULT_SAVE(c,"relative",0,"0");
    CLASS_ATTR_DEFAULT_SAVE(c,"defvaldb",0,"0");
    CLASS_ATTR_DEFAULT_SAVE(c,"inputmode",0,"0");
    CLASS_ATTR_DEFAULT_SAVE(c,"interp",0,"20");
	CLASS_ATTR_LABEL(c,"min", 0, "Output Minimum");
	CLASS_ATTR_LABEL(c,"mult", 0, "Output Multiplier");
	CLASS_ATTR_STYLE_LABEL(c,"floatoutput",0,"onoff","Float Output");
	
	CLASS_ATTR_ORDER(c, "relative",		0, "2");
	CLASS_ATTR_ORDER(c, "size",			0, "3");
	CLASS_ATTR_ORDER(c, "min",			0, "4");
	CLASS_ATTR_ORDER(c, "mult",			0, "5");
    
    CLASS_ATTR_CATEGORY			(c, "channels", 0, "Custom");
    CLASS_ATTR_LONG				(c, "channels", 0, t_hoaGain, f_numberOfChannels);
    CLASS_ATTR_ACCESSORS        (c, "channels", (method)NULL,(method)hoaGain_setattr_channels);
	CLASS_ATTR_ORDER			(c, "channels", 0, "1");
	CLASS_ATTR_LABEL			(c, "channels", 0, "Number of Channels");
	CLASS_ATTR_FILTER_CLIP		(c, "channels", 1, MAX_IO);
	CLASS_ATTR_DEFAULT			(c, "channels", 0, "8");
	CLASS_ATTR_SAVE				(c, "channels", 1);
    
    CLASS_ATTR_CATEGORY			(c, "range", 0, "Value");
    CLASS_ATTR_FLOAT_ARRAY      (c, "range", 0, t_hoaGain, f_range, 2);
    CLASS_ATTR_ACCESSORS        (c, "range", (method)NULL,(method)hoaGain_setattr_range);
	CLASS_ATTR_ORDER			(c, "range", 0, "2");
	CLASS_ATTR_LABEL			(c, "range", 0, "Range (dB)");
	CLASS_ATTR_DEFAULT			(c, "range", 0, "-70. 18.");
	CLASS_ATTR_SAVE             (c, "range", 1);

	class_register(CLASS_BOX, c);
	s_hoaGain_class = c;
	
	ps_hslider = gensym("hslider");
	ps_slider = gensym("slider");
	ps_preset = gensym("_preset");
    
    class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
    
	return 0;
}

void *hoaGain_new(t_symbol *s, short argc, t_atom *argv)
{
	t_hoaGain* x;
	long flags; 
	t_dictionary *d=NULL;
	
	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_hoaGain *) object_alloc(s_hoaGain_class);
	if (!x)
		return NULL;

	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_NODRAWBOX
			| JBOX_DRAWINLAST			// rbs -- I think we can turn this off
			| JBOX_GROWBOTH
			| JBOX_DRAWBACKGROUND
			| JBOX_MOUSEDRAGDELTA
			;

	x->j_val = 0;
    x->j_defaultValuedB = 0;
    x->j_valdB = x->j_defaultValuedB;
    x->f_interp = 20;
    
    x->f_numberOfChannels = 8;
    
    //dictionary_getlong(d, gensym("channels"), &x->f_numberOfChannels); // make sure we have the number of inputs before set up other args.
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
    
    x->f_amp = new CicmLine(sys_getblksize(), sys_getsr(), x->f_interp);
    
    // inputs
	dsp_setupjbox((t_pxjbox *)x, x->f_numberOfChannels + 1);
    // outputs
    x->f_outlet_infos = outlet_new(x, NULL);
    for (int i=0; i < x->f_numberOfChannels; i++)
        outlet_new(x,"signal");
    
    attr_dictionary_process(x,d); // handle attribute args
    
    hoaGain_set_dB(x, x->j_defaultValuedB);
    
    
    jbox_ready((t_jbox *)x);
    x->j_box.z_misc = Z_NO_INPLACE;
	return x;
}

long hoaGain_oksize(t_hoaGain *x, t_rect *newrect)
{
    int isHoriz = hoaGain_ishorizontal(x, newrect);
    long minWidth, minHeight;
    minWidth = minHeight = 10;
    if (isHoriz) minWidth = 30; // horizontal
    else minHeight = 30; // vertical
    if (newrect->width < minWidth) newrect->width = minWidth;
    if (newrect->height < minHeight) newrect->height = minHeight;
    return 0;
}

void hoaGain_assist(t_hoaGain *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET)
    {
        if (a != x->f_numberOfChannels)
            sprintf(s,"(signal) Audio Signal to be Scaled (ch %ld)", a+1);
        else
        {
            switch (x->f_inputMode) {
                case DECIBELS:
                    sprintf(s,"(Int/Float) Set dB Value (%.2f-%.2f)", x->f_range[0], x->f_range[1]);
                    break;
                case AMPLITUDE:
                    sprintf(s,"(Int/Float) Set Amplitude Value (dB range : %.2f-%.2f)", x->f_range[0], x->f_range[1]);
                    break;
                case MIDI:
                    sprintf(s,"(int) Set Midi Value (dB range : %.2f-%.2f)", x->f_range[0], x->f_range[1]);
                    break;
                    
                default:
                    break;
            }
        }
	} 
	else {
		if (a != x->f_numberOfChannels)
            sprintf(s,"(signal) Scaled Signal (ch %ld)", a+1);
        else
        {
            switch (x->f_inputMode) {
                case DECIBELS:
                    sprintf(s,"(Float) dB Value (%.2f-%.2f)", x->f_range[0], x->f_range[1]);
                    break;
                case AMPLITUDE:
                    sprintf(s,"(Float) Amplitude Value (dB range : %.2f-%.2f)", x->f_range[0], x->f_range[1]);
                    break;
                case MIDI:
                    sprintf(s,"(int) Midi Value (dB range : %.2f-%.2f)", x->f_range[0], x->f_range[1]);
                    break;
                    
                default:
                    break;
            }
        }
	}
}

void hoaGain_preset(t_hoaGain *x)
{
	void *z;
	if (!(z = ps_preset->s_thing))
		return;
    
    binbuf_vinsert(z,(char*)"osslf",x,object_classname(x), gensym("contextvalue"), x->f_inputMode, hoaGain_getInputModeValue(x));
}

void hoaGain_contextValue(t_hoaGain *x, long valueType, double value)
{
    x->f_inputMode = Tools::clip(valueType, long(0), long(2));
    hoaGain_setInputModeValue(x, value, true);
}

void hoaGain_setInputModeValue(t_hoaGain *x, double value, bool outputTheValue)
{
    double dBValue = x->j_valdB;

    switch (x->f_inputMode) {
        case DECIBELS :
            dBValue = value;
            break;
        case AMPLITUDE :
            dBValue = Tools::atodb(value);
            break;
        case MIDI :
            dBValue = Tools::scale(value, 0, 128, -70, 0);
            break;
    }
    
    x->j_val = hoaGain_constrain_real_value(x, dBValue) - x->j_min;
    x->j_valdB = x->j_val + x->j_min;
        
    hoaGain_set_gain(x);
	if (outputTheValue)
		object_notify(x, _sym_modified, NULL);
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("cursor_layer"));
	jbox_redraw((t_jbox *)x);
}

void hoaGain_float_dB(t_hoaGain *x, double dBValue)
{
    
    x->j_val = hoaGain_constrain_real_value(x, dBValue) - x->j_min;
    x->j_valdB = x->j_val + x->j_min;
    hoaGain_set_gain(x);
    object_notify(x, _sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("cursor_layer"));
	jbox_redraw((t_jbox *)x);
    
    hoaGain_bang(x);
}

void hoaGain_set_dB(t_hoaGain *x, double dBValue)
{
    
    x->j_val = hoaGain_constrain_real_value(x, dBValue) - x->j_min;
    x->j_valdB = x->j_val + x->j_min;
    hoaGain_set_gain(x);
    object_notify(x, _sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("cursor_layer"));
	jbox_redraw((t_jbox *)x);    
}

double hoaGain_getInputModeValue(t_hoaGain *x)
{
    switch (x->f_inputMode) {
        case DECIBELS :
            return x->j_valdB;
            break;
        case AMPLITUDE :
            return x->j_valdB > -70 ? Tools::dbtoa(x->j_valdB) : 0;
            break;
        case MIDI :
            return Tools::scale(x->j_valdB, -70, 0, 0, 128);
            break;
        default:
            break;
    }
    return 0;
}

void hoaGain_free(t_hoaGain *x)
{
    dsp_freejbox((t_pxjbox *)x);
	jbox_free((t_jbox *)x);
    delete x->f_amp;
}

/* DSP ------------------------------------- */
void hoaGain_dsp(t_hoaGain *x, t_signal **sp, short *count)
{
    int i;
	int pointer_count;
	t_int **sigvec;
	
	pointer_count = x->f_numberOfChannels*2 + 3;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
    
    x->f_amp->setSampleRate(sp[0]->s_sr);
    x->f_amp->setVectorSize(sp[0]->s_n);
	
	dsp_addv(hoaGain_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}
t_int *hoaGain_perform(t_int *w)
{
    t_hoaGain *x			= (t_hoaGain *)(w[1]);
	t_int	sampleframes= (t_int)(w[2]);
	t_float	**ins		= (t_float **)w+3;
    t_float	**outs		= (t_float **)w+3+x->f_numberOfChannels+1;
    
    int i;
    t_float line[sampleframes];
    
    x->f_amp->process(line);
    
    for(i = 0; i < x->f_numberOfChannels; i++)
        Cicm_Matrix_Vector_Float_Mul(ins[i], line, outs[i], sampleframes);

	return (w + x->f_numberOfChannels*2 + 4);
}
void hoaGain_dsp64(t_hoaGain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_amp->setSampleRate(samplerate);
    x->f_amp->setVectorSize(maxvectorsize);
    object_method(dsp64, gensym("dsp_add64"), x, hoaGain_perform64, 0, NULL);
}
void hoaGain_perform64(t_hoaGain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int i;
    double line[sampleframes];
    
    x->f_amp->process(line);
    
    for(i = 0; i < x->f_numberOfChannels; i++)
        Cicm_Matrix_Vector_Double_Mul(ins[i], line, outs[i], sampleframes);
}

void hoaGain_set_gain(t_hoaGain *x)
{
    x->f_amp->setCoefficient( x->j_valdB > -70.0f ? Tools::dbtoa(x->j_valdB) : 0.0f );
}

/* Paint ------------------------------------- */
void hoaGain_paint(t_hoaGain *x, t_object *view)
{
	t_rect rect;
    char isHoriz;    
	jbox_get_rect_for_view((t_object *)x, view, &rect);
    isHoriz = hoaGain_ishorizontal(x, &rect);
    draw_background(x, view, &rect, isHoriz);
    draw_cursor(x, view, &rect, isHoriz);
}

void hoaGain_drawPopupValue(t_hoaGain *x)
{
    /*
    t_jfont *jf;
    jf = jfont_create(jbox_get_fontname((t_jbox *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_SLANT_NORMAL, 16);
    t_jpopupmenu* popup = jpopupmenu_create();
    //jpopupmenu_setfont(subpopup, x->jfont);
    jpopupmenu_additem(popup, 0, "Menu", NULL, 0, 1, NULL);
    jpopupmenu_addseperator(popup);
    jpopupmenu_additem(popup, 1, "Add source", NULL, 0, 0, NULL);
    jpopupmenu_destroy(popup);
    */
}

void draw_cursor(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz)
{    
	t_jgraphics *g;
	int pos;
    double dBval = x->j_valdB;
    
    g = jbox_start_layer((t_object *)x, view, gensym("cursor_layer"), rect->width, rect->height);
    
	if (g)
	{
        dBval = CLAMP(dBval, x->f_range[0], x->f_range[1]);
        pos = hoaGain_dBvaltopos(x, dBval, rect, isHoriz);
        
        if (isHoriz)
        {
            // draw knob rect
            jgraphics_set_source_jrgba(g, &x->j_knobcolor);
            jgraphics_rectangle_rounded(g, pos-5, knobMargin, 11, rect->height - (knobMargin*2), knobRound, knobRound);
            jgraphics_fill(g);
            
            //draw knob interior line
            jgraphics_set_source_jrgba(g, &x->j_intknobcolor);
            jgraphics_set_line_width(g,1);
            jgraphics_move_to(g, long(pos)+0.5-3, knobMargin+(knobRound*0.5));
            jgraphics_line_to(g, long(pos)+0.5-3, rect->height - (knobMargin+(knobRound*0.5)));
            jgraphics_move_to(g, long(pos)+0.5, (knobMargin+2));
            jgraphics_line_to(g, long(pos)+0.5, rect->height - (knobMargin+2));
            jgraphics_move_to(g, long(pos)+0.5+3, (knobMargin+(knobRound*0.5)));
            jgraphics_line_to(g, long(pos)+0.5+3, rect->height - (knobMargin+(knobRound*0.5)));
            jgraphics_stroke(g);
        }
        else
        {
            // draw knob rect
            jgraphics_set_source_jrgba(g, &x->j_knobcolor);
            jgraphics_rectangle_rounded(g, knobMargin, pos-5, rect->width - (knobMargin*2), 11, knobRound, knobRound);
            jgraphics_fill(g);
            
            //draw knob interior line
            jgraphics_set_source_jrgba(g, &x->j_intknobcolor);
            jgraphics_set_line_width(g,1);
            jgraphics_move_to(g, (knobMargin+(knobRound*0.5)), long(pos)+0.5-3);
            jgraphics_line_to(g, rect->width - (knobMargin+(knobRound*0.5)), long(pos)+0.5-3);
            jgraphics_move_to(g, (knobMargin+2), long(pos)+0.5);
            jgraphics_line_to(g, rect->width - (knobMargin+2), long(pos)+0.5);
            jgraphics_move_to(g, (knobMargin+(knobRound*0.5)), long(pos)+0.5+3);
            jgraphics_line_to(g, rect->width - (knobMargin+(knobRound*0.5)), long(pos)+0.5+3);
            jgraphics_stroke(g);
        }
	}

    jbox_end_layer((t_object*)x, view, gensym("cursor_layer"));
	jbox_paint_layer((t_object *)x, view, gensym("cursor_layer"), 0., 0.);
}

void draw_background(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz)
{
	t_jgraphics *g;
	int zerodBpos;
    t_jrgba black, white;
    black = white = x->j_brgba;
    double contrast = 0.05;
    
    black.red = Tools::clip_min(black.red -= contrast);
    black.green = Tools::clip_min(black.green -= contrast);
    black.blue = Tools::clip_min(black.blue -= contrast);
    
    white.red = Tools::clip_max(white.red += contrast, 1.);
    white.green = Tools::clip_max(white.green += contrast, 1.);
    white.blue = Tools::clip_max(white.blue += contrast, 1.);
    
    zerodBpos = hoaGain_dBvaltopos(x, 0, rect, isHoriz);
    
    g = jbox_start_layer((t_object *)x, view, gensym("bg_layer"), rect->width, rect->height);
    
    if (g) {
        
        if (isHoriz)
        {
            // draw knob rect
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_set_line_width(g,1);
            jgraphics_rectangle_rounded(g, zerodBpos-(knobMargin)-0.5, (knobMargin)-1.5, (knobMargin*2)+1, rect->height - (knobMargin*2)+2, knobRound, knobRound);
            jgraphics_stroke(g);
            
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_set_line_width(g,1);
            jgraphics_rectangle_rounded(g, zerodBpos-(knobMargin)-0.5, (knobMargin)-1.5, (knobMargin*2)+2, rect->height - (knobMargin*2)+3, knobRound, knobRound);
            jgraphics_stroke(g);

            
            // draw middle line :
            jgraphics_set_line_width(g,1);
            jgraphics_set_source_jrgba(g, &white);
            // neg
            jgraphics_move_to(g, 3, long(rect->height*0.5) + 0.5);
            jgraphics_line_to(g, long(zerodBpos) - (knobMargin), long(rect->height*0.5) + 0.5);
            // pos
            jgraphics_move_to(g, long(zerodBpos) + (knobMargin)+1, long(rect->height*0.5) + 0.5);
            jgraphics_line_to(g, rect->width - 4, long(rect->height*0.5) + 0.5);
            jgraphics_stroke(g);
            
            
            jgraphics_set_line_width(g,1);
            jgraphics_set_source_jrgba(g, &black);
            // neg
            jgraphics_move_to(g, 3, long(rect->height*0.5)-1 + 0.5);
            jgraphics_line_to(g, long(zerodBpos) - (knobMargin)-1, long(rect->height*0.5)-1 + 0.5);
            // pos
            jgraphics_move_to(g, long(zerodBpos) + (knobMargin)+1, long(rect->height*0.5)-1 + 0.5);
            jgraphics_line_to(g, rect->width - 4, long(rect->height*0.5)-1 + 0.5);
            jgraphics_stroke(g);
        }
        else
        {
            // draw knob rect
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_set_line_width(g,1);
            jgraphics_rectangle_rounded(g, (knobMargin)-1.5, zerodBpos-(knobMargin)-0.5, rect->width - (knobMargin*2)+2, (knobMargin*2)+1, knobRound, knobRound);
            jgraphics_stroke(g);
            
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_set_line_width(g,1);
            jgraphics_rectangle_rounded(g, (knobMargin)-1.5, zerodBpos-(knobMargin)-0.5, rect->width - (knobMargin*2)+3, (knobMargin*2)+2, knobRound, knobRound);
            jgraphics_stroke(g);
            
            // draw middle line white :
            jgraphics_set_line_width(g,1);
            jgraphics_set_source_jrgba(g, &white);
            // neg
            jgraphics_move_to(g, long(rect->width*0.5) + 0.5, 3);
            jgraphics_line_to(g, long(rect->width*0.5) + 0.5, long(zerodBpos) - (knobMargin));
            // pos
            jgraphics_move_to(g, long(rect->width*0.5) + 0.5, long(zerodBpos) + (knobMargin)+1);
            jgraphics_line_to(g, long(rect->width*0.5) + 0.5, rect->height - 4);
            jgraphics_stroke(g);
            
            // draw middle line white :
            jgraphics_set_line_width(g,1);
            jgraphics_set_source_jrgba(g, &black);
            // neg
            jgraphics_move_to(g, long(rect->width*0.5)-1 + 0.5, 3);
            jgraphics_line_to(g, long(rect->width*0.5)-1 + 0.5, long(zerodBpos) - (knobMargin)-1);
            // pos
            jgraphics_move_to(g, long(rect->width*0.5)-1 + 0.5, long(zerodBpos) + (knobMargin)+1);
            jgraphics_line_to(g, long(rect->width*0.5)-1 + 0.5, rect->height - 4);
            jgraphics_stroke(g);
        }
    }

    jbox_end_layer((t_object*)x, view, gensym("bg_layer"));
	jbox_paint_layer((t_object *)x, view, gensym("bg_layer"), 0., 0.);
}

void hoaGain_bang(t_hoaGain *x)
{
    if (x->f_inputMode == MIDI) {
        outlet_int(x->f_outlet_infos, (long)hoaGain_getInputModeValue(x));
    }
    else
        outlet_float(x->f_outlet_infos, hoaGain_getInputModeValue(x));
}

void hoaGain_int(t_hoaGain *x, long n)
{
    hoaGain_assign(x, double(n), true);
	hoaGain_bang(x);
}

void hoaGain_float(t_hoaGain *x, double f)
{
    hoaGain_assign(x, f, true);
	hoaGain_bang(x);
}

void hoaGain_setminmax(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv)
{
	double a, b;
	
	if (argc > 1) {
		double old_min = x->j_min;
		double old_size = x->j_size;
		a = b = 0;
		
		if (argv[0].a_type == A_LONG)
			a = (double)atom_getlong(&argv[0]);
		else if (argv[0].a_type == A_FLOAT)
			a = (double)atom_getfloat(&argv[0]);

		if (argv[1].a_type == A_LONG)
			b = (double)atom_getlong(&argv[1]);
		else if (argv[1].a_type == A_FLOAT)
			b = (double)atom_getfloat(&argv[1]);
		
		if (a == b) {
			x->j_min = 0.;
			x->j_size = 1.;
		} else  if (a < b) {
			x->j_min = a;
			x->j_size = b - a;
		} else {			
			x->j_min = b;
			x->j_size = a - b;
		}
        
        x->f_range[0] = x->j_min;
        x->f_range[1] = x->j_size + x->j_min;
		
		if (old_min != x->j_min || old_size != x->j_size)
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("bg_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("cursor_layer"));
            jbox_redraw((t_jbox *)x);
        }
	}
}

void hoaGain_set(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv)
{
	if (argc && (argv->a_type == A_FLOAT || argv->a_type == A_LONG))
		hoaGain_assign(x, atom_getfloat(argv), true);
}

t_max_err hoaGain_setattr_interp(t_hoaGain *x, t_object *attr, long ac, t_atom *av)
{
	double d;
	if (ac && av) {
		d = atom_getfloat(av);
        x->f_amp->setRampTimeInMs(d);
        x->f_interp = x->f_amp->getRampTimeInMs();
	}
	return MAX_ERR_NONE;
}

t_max_err hoaGain_setattr_channels(t_hoaGain *x, t_object *attr, long ac, t_atom *av)
{
	long d;
	if (ac && av)
    {
        if (atom_gettype(av) == A_LONG)
        {
            d = atom_getlong(av);
            hoaGain_resize_io(x, d);
            HoaGain_reconnect_outlet(x);
        }
	}
	return MAX_ERR_NONE;
}

void hoaGain_resize_io(t_hoaGain *x, long newNumberOfChannel)
{
    int dspState = sys_getdspobjdspstate((t_object*)x);
    int lastNumberOfChannels = x->f_numberOfChannels;
    newNumberOfChannel = Tools::clip(newNumberOfChannel, long(MIN_IO), long(MAX_IO));
    if (lastNumberOfChannels != newNumberOfChannel) {
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("stop"));
        
        t_object *b = NULL;
        object_obex_lookup(x, _sym_pound_B, (t_object **)&b);
        object_method(b, gensym("dynlet_begin"));
        
        dsp_resize((t_pxobject*)x, newNumberOfChannel+1);
        
        outlet_delete(outlet_nth((t_object*)x, lastNumberOfChannels)); // delete value out outlet
        
        if(lastNumberOfChannels > newNumberOfChannel)
        {
            for(int i = lastNumberOfChannels; i > newNumberOfChannel; i--)
            {
                outlet_delete(outlet_nth((t_object*)x, i-1));
            }
        }
        else if(lastNumberOfChannels < newNumberOfChannel)
        {
            for(int i = lastNumberOfChannels; i < newNumberOfChannel; i++)
            {
                outlet_append((t_object*)x, NULL, gensym("signal"));
            }
        }
        
        x->f_outlet_infos = outlet_append((t_object*)x, NULL, NULL); // restore value out outlet
        
        object_method(b, gensym("dynlet_end"));
        
        if(dspState)
            object_method(gensym("dsp")->s_thing, gensym("start"));
        
        x->f_numberOfChannels = newNumberOfChannel;
    }
}

t_max_err hoaGain_setattr_range(t_hoaGain *x, t_object *attr, long ac, t_atom *av)
{
    hoaGain_setminmax(x, NULL, ac, av);
	return MAX_ERR_NONE;
}

t_max_err hoaGain_setvalueof(t_hoaGain *x, long ac, t_atom *av)
{
    if (ac && av) {
        if (ac >= 2) {
            x->f_inputMode = Tools::clip(long(atom_getlong(av)), long(0), long(2));
            if (atom_gettype(av+1) == A_LONG || atom_gettype(av+1) == A_FLOAT)
                hoaGain_setInputModeValue(x, atom_getfloat(av+1), false);
            
            hoaGain_bang(x);
        }
	}
	return MAX_ERR_NONE;
}

t_max_err hoaGain_getvalueof(t_hoaGain *x, long *ac, t_atom **av)
{
    if (ac && av)
    {
		if (*ac && *av)
        {
            atom_setlong(*av+0, (long)x->f_inputMode);
            if (x->f_inputMode == MIDI)
                atom_setlong(*av+1, (long)hoaGain_getInputModeValue(x));
            else
                atom_setfloat(*av+1, hoaGain_getInputModeValue(x));
		}
        else
        {
            *ac = 2;
			*av = (t_atom *)getbytes(2 * sizeof(t_atom));
        }
        
        atom_setlong(*av+0, (long)x->f_inputMode);
        if (x->f_inputMode == MIDI)
            atom_setlong(*av+1, (long)hoaGain_getInputModeValue(x));
        else
        atom_setfloat(*av+1, hoaGain_getInputModeValue(x));
    }
	return MAX_ERR_NONE;
}

void hoaGain_assign(t_hoaGain *x, double f, long notify)
{
    hoaGain_setInputModeValue(x, f, notify);
}

double hoaGain_constrain_real_value(t_hoaGain *x, double f)
{
    return Tools::clip(f, double(x->j_min), x->j_size + x->j_min);
}

double hoaGain_constrain(t_hoaGain *x, double f)
{
    return Tools::clip(f, double(0), x->j_size);
}

char hoaGain_ishorizontal(t_hoaGain *x, t_rect *r)
{
	if (x->j_orientation == 0) { // automatic mode
		if (r->height > r->width)
			return (0);
		else
			return (1);
	} else
		return (x->j_orientation == 2 ? 0 : 1);	
}

double hoaGain_postoval(t_hoaGain *x, t_pt pt, t_rect *r, char ishoriz)
{
	double pos, range;
	
	if (ishoriz) {
		pos = pt.x;
		range = r->width;
	} else {
		pos = r->height - pt.y;
		range = r->height;
	}
	if (pos <= hoaGain_DISPLAYINSET)
		pos = 0.;
	else {
		pos -= hoaGain_DISPLAYINSET;
		pos = (pos / (range - (hoaGain_DISPLAYINSET*2))) * x->j_size;
	}
	return hoaGain_constrain(x,pos);
}

double hoaGain_valtopos(t_hoaGain *x, double val, t_rect *r, char ishoriz)
{
	double pos, range;
	double size;
	
	if (ishoriz)
		range = r->width;
	else
		range = r->height;
	
    size = x->j_size;
	
	if (size < 0)
		size = 0;
	if (size)
		pos = (val / size) * (range - (hoaGain_DISPLAYINSET*2));
	else
		pos = 0;
	
	pos += hoaGain_DISPLAYINSET;
	if (ishoriz)
		return pos;
	else
		return r->height - pos;
}

double hoaGain_dBvaltopos(t_hoaGain *x, double dBval, t_rect *r, char ishoriz)
{
    double val = Tools:: scale(dBval, x->f_range[0], x->f_range[1], 0, x->j_size);
    return hoaGain_valtopos(x, val, r, ishoriz);
}

double hoaGain_dbtoval(t_hoaGain *x, double dBval)
{
    return Tools::scale(dBval, x->f_range[0], x->f_range[1], 0, x->j_size);
}
double hoaGain_valtodb(t_hoaGain *x, double val)
{
    return Tools::scale(val, 0, x->j_size, x->f_range[0], x->f_range[1]);
}

void hoaGain_mousedoubleclick(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers)
{
    hoaGain_float_dB(x, x->j_defaultValuedB);
}

void hoaGain_mousedown(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	double val;
	char ishoriz;
	
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	s_hoaGain_cum.x = s_hoaGain_cum.y = 0;
	ishoriz = hoaGain_ishorizontal(x, &rect);
	val = hoaGain_postoval(x, pt, &rect, ishoriz);
	if (!x->j_relative)
		hoaGain_float_dB(x, val + x->j_min);	// set value immediately
	s_hoaGain_startval = x->j_val;
}

void hoaGain_mousedragdelta(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	double inc;
	double val, cval;
	double factor;
	
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	
	if (modifiers & eShiftKey || x->j_valdB >= 0) {
		pt.y *= 0.2;
		pt.x *= 0.2;
	}
    
	// need to cancel cum change if it is beyond zero or the max value
	s_hoaGain_cum.x += pt.x;
	s_hoaGain_cum.y -= pt.y;
	if (hoaGain_ishorizontal(x, &rect)) {
		factor = x->j_size / (rect.width - (hoaGain_DISPLAYINSET*2));
		inc = s_hoaGain_cum.x * factor;
		val = s_hoaGain_startval + inc;
		cval = hoaGain_constrain(x,val);
		hoaGain_float_dB(x,cval + x->j_min);
		// in case we were constrained, adjust the cum
		if (cval != val)
			s_hoaGain_cum.x = (cval-s_hoaGain_startval) / factor;
	} else {
		factor = x->j_size / (rect.height - (hoaGain_DISPLAYINSET*2)); 
		inc = s_hoaGain_cum.y * factor;
		val = s_hoaGain_startval + inc;
		cval = hoaGain_constrain(x,val);
		hoaGain_float_dB(x, cval + x->j_min);
		if (cval != val)
			s_hoaGain_cum.y = (cval - s_hoaGain_startval) / factor; 
	}
    
    // force to 0dB :
    if (Tools::isInside(x->j_valdB, -0.05, 0.05) ) {
        hoaGain_float_dB(x, 0);
    }
}

void hoaGain_mouseup(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers)
{
	double pos, vp; 
	t_rect rect; 
	double mx, my;
	char ishoriz;

	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	ishoriz = hoaGain_ishorizontal(x, &rect);
	pos = hoaGain_valtopos(x, x->j_val, &rect, ishoriz);
	vp = pos + 0.5;
	if (ishoriz) {
		mx = vp; 
		my = pt.y;	// have y position be same as where mouse down clicked
	} else {
		mx = pt.x;	// have x position be same as where mouse down clicked
		my = vp; 
	}
	
	if (fabs(pt.x-mx) > 1. || fabs(pt.y-my) > 1.) // this make sure that if you click at the "same" location we don't move the mouse.
		jmouse_setposition_box(patcherview, (t_object*) x, mx, my); 
}

void hoaGain_getdrawparams(t_hoaGain *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = hoaGain_BORDERTHICKNESS;
	params->d_bordercolor = x->j_frgba2;
	params->d_cornersize = hoaGain_CORNERSIZE; 
	params->d_boxfillcolor = x->j_brgba;
}

t_max_err hoaGain_notify(t_hoaGain *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	long argc = 0;
	t_atom *argv = NULL;
	t_symbol *name;
	
	if (msg == _sym_attr_modified) {
		name = (t_symbol *)object_method((t_object *)data,_sym_getname);
		if (name == _sym_color) {
			object_attr_getvalueof(x, _sym_color, &argc, &argv);
			if (argc && argv) {
				object_attr_setvalueof(x, _sym_bgcolor, argc, argv);
				sysmem_freeptr(argv);
			}
		}
        else if (name == gensym("knobcolor") || name == gensym("intknobcolor"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("cursor_layer"));
        }
        else if(name == gensym("bgcolor"))
		{
            jbox_invalidate_layer((t_object *)x, NULL, gensym("bg_layer"));
		}
        jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void hoaGain_tometer(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv)
{
    t_object *patcher;
	t_object *gain;
    t_object *object;
    t_object *line;
	t_max_err err;
    
    if(argc && argv && (s == gensym("loudspeakers") || s == gensym("angles")))
    {
        err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
        if (err != MAX_ERR_NONE)
            return;
       
        err = object_obex_lookup(x, gensym("#B"), (t_object **)&gain);
        if (err != MAX_ERR_NONE)
            return;
        for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line))
        {
            if (jpatchline_get_box1(line) == gain)
            {
                object = jpatchline_get_box2(line);
                if(object_classname(jbox_get_object(object)) == gensym("hoa.meter~"))
                {
                    object_method_typed(jbox_get_object(object), s, argc, argv, NULL);
                }
                else if(object_classname(jbox_get_object(object)) == gensym("hoa.gain~"))
                {
                    object_method_typed(jbox_get_object(object), s, argc, argv, NULL);
                }
            }
        }
	}
}

void HoaGain_reconnect_outlet(t_hoaGain *x)
{
	t_object *patcher;
	t_object *decoder;
    t_object *object;
    t_object *line;
	t_max_err err;
    
	err = object_obex_lookup(x, gensym("#P"), (t_object **)&patcher);
	if (err != MAX_ERR_NONE)
		return;
	
	err = object_obex_lookup(x, gensym("#B"), (t_object **)&decoder);
	if (err != MAX_ERR_NONE)
		return;
	
    for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line))
    {
        if (jpatchline_get_box1(line) == decoder)
        {
            object = jpatchline_get_box2(line);
            
            for(int i = 0; jbox_getinlet((t_jbox *)object, i) != NULL && i < x->f_numberOfChannels; i++)
            {
                t_atom msg[4];
                t_atom rv;
                
                atom_setobj(msg, decoder);
                atom_setlong(msg + 1, i);
                atom_setobj(msg + 2, object);
                atom_setlong(msg + 3, i);
                
                object_method_typed(patcher , gensym("connect"), 4, msg, &rv);
            }
        }
    }
}
