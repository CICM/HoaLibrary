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

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
}


#define MAX_MICS 64
#define MIN_MICS 3
#define DEF_MICS 8

#include "../../Sources/HoaLibrary.h"

typedef struct  _HoaRecomposerUI
{
	t_jbox		j_box;
	t_rect		rect;
    
    // colors
	t_jrgba		f_colorBackground;
    t_jrgba		f_colorBorder;
    t_jrgba		f_colorInnerCircle;
	t_jrgba		f_colorMic;
    t_jrgba		f_colorMicSelected;
	t_jrgba		f_color_selection;
    t_jrgba		f_colorHarmonics;
    t_jrgba     f_fisheyecolor;
    t_jrgba     f_colorTextMic;
    t_jrgba     f_colorTextMicSelected;
    
    // microphones
    AmbisonicVirtualMicUIManager* f_mics;
    int			f_numberOfMic;
    int         f_showFishEye;
    double      f_fisheyeAngle;
    
    // mouse
    t_pt        f_rectSelectionBegin;
    t_rect      f_rectSelection;
    bool        f_rectSelectionExist;
	t_pt		f_last_mouseMove;
    int         f_last_mouseMoveOverMic;
    t_pt		f_last_mouseDown;
    int         f_last_mouseDownOverMic;
    t_pt		f_last_mouseUp;
    int         f_last_mouseUpOverMic;
    t_pt		f_last_mouseDrag;
    double		f_last_mouseDragAngle;
    double      f_last_mouseDragRadius;
    
    // draw utility
    double      f_micRadius;
    
    // outlets
	void*		f_out;
    void*		f_outlet_infos;

} t_HoaRecomposerUI;

t_class *HoaRecomposerUI_class;

// general methods
void *HoaRecomposerUI_new(t_symbol *s, int argc, t_atom *argv);
void HoaRecomposerUI_free(t_HoaRecomposerUI *x);
void HoaRecomposerUI_getdrawparams(t_HoaRecomposerUI *x, t_object *patcherview, t_jboxdrawparams *params);
void HoaRecomposerUI_assist(t_HoaRecomposerUI *x, void *b, long m, long a, char *s);
t_max_err HoaRecomposerUI_notify(t_HoaRecomposerUI *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void HoaRecomposerUI_preset(t_HoaRecomposerUI *x);
t_max_err HoaRecomposerUI_setvalueof(t_HoaRecomposerUI *x, long ac, t_atom *av);
t_max_err HoaRecomposerUI_getvalueof(t_HoaRecomposerUI *x, long *ac, t_atom **av);
void notifyChange(t_HoaRecomposerUI *x);
void HoaRecomposerUI_outputAndNotifyChange(t_HoaRecomposerUI *x);

// mouse/key methods
void HoaRecomposerUI_mouseleave(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mouseenter(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mousedown(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mousedown2(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mouseup(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
long HoaRecomposerUI_key(t_HoaRecomposerUI *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void HoaRecomposerUI_mousemove(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mousedrag(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mousedoubleclick(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);

// msg-in methods
t_max_err set_numberOfMics(t_HoaRecomposerUI *x, void *attr, long ac, t_atom *av);
void HoaRecomposerUI_bang(t_HoaRecomposerUI *x);
void HoaRecomposerUI_list(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av);
void HoaRecomposerUI_anything(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av);
void HoaRecomposerUI_float(t_HoaRecomposerUI *x, double f);
void HoaRecomposerUI_reset(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av);

void HoaRecomposerUI_set(t_HoaRecomposerUI *x, t_symbol *s, long ac, t_atom *av);
void HoaRecomposerUI_angles(t_HoaRecomposerUI *x, t_symbol *s, long ac, t_atom *av);
void HoaRecomposerUI_wide(t_HoaRecomposerUI *x, t_symbol *s, long ac, t_atom *av);
void HoaRecomposerUI_nb_hp(t_HoaRecomposerUI *x, int v);

// msg-out methods
void HoaRecomposerUI_output(t_HoaRecomposerUI *x);

// paint methods
void HoaRecomposerUI_paint(t_HoaRecomposerUI *x, t_object *view);
void draw_background(t_HoaRecomposerUI *x, t_object *view, t_rect *rect);
void draw_microphones(t_HoaRecomposerUI *x, t_object *view, t_rect *rect);
void draw_textMics(t_HoaRecomposerUI *x, t_object *view, t_rect *rect);
void draw_harmonics(t_HoaRecomposerUI *x, t_object *view, t_rect *rect);
void draw_fishEye(t_HoaRecomposerUI *x, t_object *view, t_rect *rect);
void draw_rect_selection(t_HoaRecomposerUI *x, t_object *view, t_rect *rect);

//calcul methods
int isPointOverAMic(t_HoaRecomposerUI *x, t_pt *pt);

void begin_rect_selection(t_HoaRecomposerUI *x, t_pt pt);
void do_rect_selection(t_HoaRecomposerUI *x, t_pt pt);
void end_rect_selection(t_HoaRecomposerUI *x, t_pt pt);
bool isMicInsideRect(t_HoaRecomposerUI *x, int micIndex, t_rect rectSelection);

int C74_EXPORT main()
{
	t_class *c;
	
	c = class_new("hoa.recomposer", (method)HoaRecomposerUI_new, (method)HoaRecomposerUI_free, (short)sizeof(t_HoaRecomposerUI), 0L, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method) HoaRecomposerUI_assist,          "assist",        A_CANT,	0);
    class_addmethod(c, (method) HoaRecomposerUI_preset,          "preset",                  0);
    class_addmethod(c, (method) HoaRecomposerUI_getvalueof,      "getvalueof",    A_CANT,   0);
	class_addmethod(c, (method) HoaRecomposerUI_setvalueof,      "setvalueof",    A_CANT,   0);
	class_addmethod(c, (method) HoaRecomposerUI_paint,           "paint",         A_CANT,	0);
	class_addmethod(c, (method) HoaRecomposerUI_getdrawparams,   "getdrawparams", A_CANT,   0);
	class_addmethod(c, (method) HoaRecomposerUI_notify,          "notify",        A_CANT,   0);
	class_addmethod(c, (method) HoaRecomposerUI_bang,            "bang",                 0L,0);
    class_addmethod(c, (method) HoaRecomposerUI_set,             "set",           A_GIMME,  0);
    class_addmethod(c, (method) HoaRecomposerUI_angles,          "angles",         A_GIMME,  0);
    class_addmethod(c, (method) HoaRecomposerUI_wide,            "directivities",          A_GIMME,  0);
    class_addmethod(c, (method) HoaRecomposerUI_reset,           "reset",         A_GIMME,  0);
	class_addmethod(c, (method) HoaRecomposerUI_anything,        "anything",      A_GIMME,  0);
	class_addmethod(c, (method) HoaRecomposerUI_mousedown,       "mousedown",     A_CANT,   0);
	class_addmethod(c, (method) HoaRecomposerUI_mousedrag,       "mousedrag",     A_CANT,   0);
	class_addmethod(c, (method) HoaRecomposerUI_mouseup,         "mouseup",       A_CANT,   0);
	class_addmethod(c, (method) HoaRecomposerUI_mousemove,       "mousemove",     A_CANT,   0);
    class_addmethod(c, (method) HoaRecomposerUI_mousedoubleclick,"mousedoubleclick", A_CANT,0);
	class_addmethod(c, (method) HoaRecomposerUI_key,             "key",           A_CANT,   0);
    	
	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 300");
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
    CLASS_STICKY_CATEGORY(c, 0, "Color");
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_HoaRecomposerUI, f_colorBackground);
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.35 0.35 0.35 1.");
    
    CLASS_ATTR_RGBA				(c, "bordercolor", 0, t_HoaRecomposerUI, f_colorBorder);
	CLASS_ATTR_STYLE			(c, "bordercolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bordercolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bordercolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bordercolor", 0, "0.2 0.2 0.2 1.");
    
    CLASS_ATTR_RGBA				(c, "circlecolor", 0, t_HoaRecomposerUI, f_colorInnerCircle);
	CLASS_ATTR_STYLE			(c, "circlecolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "circlecolor", 0, "Circle Inner Color");
	CLASS_ATTR_ORDER			(c, "circlecolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "circlecolor", 0, "0.2 0.2 0.2 1.");
	
	CLASS_ATTR_RGBA				(c, "miccolor", 0, t_HoaRecomposerUI, f_colorMic);
	CLASS_ATTR_STYLE			(c, "miccolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "miccolor", 0, "Microphone Color");
	CLASS_ATTR_ORDER			(c, "miccolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "miccolor", 0, "0.5 0.5 0.5 1.");
    
    CLASS_ATTR_RGBA				(c, "selmiccolor", 0, t_HoaRecomposerUI, f_colorMicSelected);
	CLASS_ATTR_STYLE			(c, "selmiccolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "selmiccolor", 0, "Selected Microphone Color");
	CLASS_ATTR_ORDER			(c, "selmiccolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "selmiccolor", 0, "0.86 0.86 0.86 1.");
    
    CLASS_ATTR_RGBA				(c, "harmonicscolor", 0, t_HoaRecomposerUI, f_colorHarmonics);
	CLASS_ATTR_STYLE			(c, "harmonicscolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "harmonicscolor", 0, "Harmonics color");
	CLASS_ATTR_ORDER			(c, "harmonicscolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "harmonicscolor", 0, "0.4 0.4 0.4 0.3");
    
    CLASS_ATTR_RGBA				(c, "fisheyecolor", 0, t_HoaRecomposerUI, f_fisheyecolor);
	CLASS_ATTR_STYLE			(c, "fisheyecolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "fisheyecolor", 0, "FishEye color");
	CLASS_ATTR_ORDER			(c, "fisheyecolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "fisheyecolor", 0, "0.69 0.18 0.18 1.");
    
    CLASS_ATTR_RGBA				(c, "rectselectcolor", 0, t_HoaRecomposerUI, f_color_selection);
	CLASS_ATTR_STYLE			(c, "rectselectcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "rectselectcolor", 0, "Rect Selection color");
	CLASS_ATTR_ORDER			(c, "rectselectcolor", 0, "8");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "rectselectcolor", 0, "0.39 0.52 0.8 1.");
    
    CLASS_ATTR_RGBA				(c, "mictextcolor", 0, t_HoaRecomposerUI, f_colorTextMic);
	CLASS_ATTR_STYLE			(c, "mictextcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "mictextcolor", 0, "Mics text color");
	CLASS_ATTR_ORDER			(c, "mictextcolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "mictextcolor", 0, "0.9 0.9 0.9 1.");
    
    CLASS_ATTR_RGBA				(c, "selmictextcolor", 0, t_HoaRecomposerUI, f_colorTextMicSelected);
	CLASS_ATTR_STYLE			(c, "selmictextcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "selmictextcolor", 0, "Selected Mics text color");
	CLASS_ATTR_ORDER			(c, "selmictextcolor", 0, "10");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "selmictextcolor", 0, "0.4 0.4 0.4 1.");
    CLASS_STICKY_CATEGORY_CLEAR(c);
	
	CLASS_ATTR_LONG				(c, "nmics",0, t_HoaRecomposerUI, f_numberOfMic);
    CLASS_ATTR_CATEGORY			(c, "nmics",0,"Custom");
	CLASS_ATTR_FILTER_CLIP		(c, "nmics", MIN_MICS, MAX_MICS);
    CLASS_ATTR_ACCESSORS		(c, "nmics", NULL, set_numberOfMics);
	CLASS_ATTR_LABEL			(c, "nmics", 0, "Number of Microphones");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"nmics",0,"8");
	
	class_register(CLASS_BOX, c);
	HoaRecomposerUI_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaRecomposerUI_new(t_symbol *s, int argc, t_atom *argv)
{
	t_HoaRecomposerUI *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_HoaRecomposerUI *)object_alloc(HoaRecomposerUI_class);
	flags = 0 
	| JBOX_DRAWFIRSTIN 
	| JBOX_DRAWINLAST
	| JBOX_TRANSPARENT
    | JBOX_DRAWBACKGROUND
	| JBOX_GROWY
	| JBOX_HILITE
	;
	jbox_new(&x->j_box, flags, argc, argv);
    
    x->f_outlet_infos = listout(x);
    x->f_out = outlet_new(x, NULL);
    
    x->f_numberOfMic = DEF_MICS;
    x->f_last_mouseMoveOverMic = x->f_last_mouseDownOverMic = x->f_last_mouseUpOverMic = -1;
    x->f_showFishEye = 0;
    
    x->f_mics = new AmbisonicVirtualMicUIManager(x->f_numberOfMic);
    
    x->f_mics->setNumberOfMics(x->f_numberOfMic);

	x->j_box.b_firstin = (t_object*) x;
	
	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);
    
	return (x);
}

void HoaRecomposerUI_getdrawparams(t_HoaRecomposerUI *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = 1;
	params->d_cornersize = 8;
    params->d_bordercolor = x->f_colorBorder;
    params->d_boxfillcolor = x->f_colorBackground;
}

void HoaRecomposerUI_free(t_HoaRecomposerUI *x)
{
	jbox_free(&x->j_box);
    delete x->f_mics;
}

void HoaRecomposerUI_assist(t_HoaRecomposerUI *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		sprintf(s,"(list) Set Microphones Directivities and Angles Values");
	} else {
		if (a == 0) {
			sprintf(s,"(list) Microphones Directivities and Angles Values");
		}
		else if (a == 1) {
			sprintf(s,"Infos output");
		}
	}
}

void HoaRecomposerUI_preset(t_HoaRecomposerUI *x)
{
    
    void* z;
    if(!(z = gensym("_preset")->s_thing))
        return;
    
    binbuf_vinsert(z, gensym("ossl")->s_name, x, object_classname(x), gensym("nmics"), x->f_numberOfMic);
    
    for(int i = 0; i < x->f_numberOfMic; i++)
    {
        binbuf_vinsert(z, gensym("osslf")->s_name, x, object_classname(x), gensym("angles"), i, (float)x->f_mics->getAngleInRadian(i));
        binbuf_vinsert(z, gensym("osslf")->s_name, x, object_classname(x), gensym("directivities"), i, (float)x->f_mics->getWiderValue(i));
    }
}

t_max_err HoaRecomposerUI_setvalueof(t_HoaRecomposerUI *x, long ac, t_atom *av)
{
    if (ac && av) {
        
        long index, i;
        for (i = index = 0; (index < x->f_numberOfMic) && (i <= ac); index++, i+=3)
        {
            x->f_mics->setAngleCartesianCoordinate(index, atom_getfloat(av+i), atom_getfloat(av+i+1));
            x->f_mics->setWiderValue(index, atom_getfloat(av+i+2));
        }
        
        jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
        jbox_redraw((t_jbox *)x);
        
        HoaRecomposerUI_output(x);
	}
	return MAX_ERR_NONE;
}

// get a list of mic value : (x, y, wider)*numberOfMicrophone
t_max_err HoaRecomposerUI_getvalueof(t_HoaRecomposerUI *x, long *ac, t_atom **av)
{
    if (ac && av)
    {
        if (*ac && *av)
        {
            long index, i;
            for (i = index = 0; index < x->f_numberOfMic; index++, i+=3)
            {
                atom_setfloat(*av+i, x->f_mics->getAbscissa(index) );
                atom_setfloat(*av+i+1, x->f_mics->getOrdinate(index) );
                atom_setfloat(*av+i+2, x->f_mics->getWiderValue(index) );
            }
		}
        else
        {
            *ac = (x->f_numberOfMic*3);
			*av = (t_atom *)getbytes( (x->f_numberOfMic*3) * sizeof(t_atom));
            long index, i;
            for (i = index = 0; index < x->f_numberOfMic; index++, i+=3)
            {
                atom_setfloat(*av+i, x->f_mics->getAbscissa(index) );
                atom_setfloat(*av+i+1, x->f_mics->getOrdinate(index) );
                atom_setfloat(*av+i+2, x->f_mics->getWiderValue(index) );
            }
        }
    }
	return MAX_ERR_NONE;
}

/* --------- */

void HoaRecomposerUI_reset(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av)
{
    // "reset" | "reset angle" | "reset angle 1" | "reset wide" | "reset wide 1"
    if (ac == 0)
    {
        x->f_mics->resetAngles();
        x->f_mics->resetWides();
    }
    else if (ac >= 1 && atom_gettype(av) == A_SYM)
    {
        if (atom_getsym(av) == gensym("angles"))
        {
            if (ac >= 2)
            {
                for(int i = 1; i < ac ; i++)
                {
                    if ( (atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG) && atom_getlong(av + i) != 0 )
                        x->f_mics->resetAngles(atom_getlong(av + i) - 1);
                }
            }
            else
            {
                x->f_mics->resetAngles();
            }
        }
        else if (atom_getsym(av) == gensym("directivities"))
        {
            if (ac >= 2)
            {
                for(int i = 1; i < ac ; i++)
                {
                    if ( (atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG) && atom_getlong(av + i) != 0 )
                        x->f_mics->resetWides(atom_getlong(av + i) - 1);
                }
            }
            else
            {
                x->f_mics->resetWides();
            }
        }
    }
    
    HoaRecomposerUI_outputAndNotifyChange(x);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
	jbox_redraw((t_jbox *)x);
}

void HoaRecomposerUI_set(t_HoaRecomposerUI *x, t_symbol *s, long ac, t_atom *av)
{
    int isSet = (s == gensym("set")) ? 1 : 0;
    t_symbol *name = atom_getsym(av);
    if (!isSet) name = s;
	
    if (ac && av)
    {
        if ( name == gensym("angles") )
        {
            if (atom_gettype(av+isSet) == A_LONG) // index + angle
            {
                long index;
                if (!Tools::isInside(index = atom_getlong(av+isSet), long(0), x->f_mics->getNumberOfMics())) return;
                if ( ac >= 2+isSet )
                    x->f_mics->setAngleInRadian(index, atom_getfloat(av+1+isSet));
            }
            else
            {
                double list[ac];
                for(int i = 0; i < ac - isSet ; i++)
                {
                    if (i > MAX_MICS-1) return;
                    if (atom_gettype(av+i+isSet) == A_FLOAT || atom_gettype(av+i+isSet) == A_LONG) {
                        list[i] = atom_getfloat(av + i + isSet);
                    } else list[i] = 0;
                }
                x->f_mics->setAnglesInRadian(list, ac);
            }
        }
        else if ( name == gensym("directivities") )
        {
            if (atom_gettype(av+isSet) == A_LONG) // index + wide
            {
                long index;
                index = atom_getlong(av+isSet);
                if ( ac >= 2+isSet )
                    x->f_mics->setWiderValue(index, atom_getfloat(av+1+isSet));                
            }
            else
            {
                double list[ac];
                for(int i = 0; i < ac - isSet ; i++)
                {
                    if (i > MAX_MICS-1) return;
                    if (atom_gettype(av+i+isSet) == A_FLOAT || atom_gettype(av+i+isSet) == A_LONG) {
                        list[i] = atom_getfloat(av + i + isSet);
                    } else list[i] = 0;
                }
                x->f_mics->setWiderValues(list, ac);
            }
        }
    }
    
    notifyChange(x);
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
	jbox_redraw((t_jbox *)x);
}

void HoaRecomposerUI_angles(t_HoaRecomposerUI *x, t_symbol *s, long ac, t_atom *av)
{
    HoaRecomposerUI_set(x, s, ac, av); // notifying in set method
    HoaRecomposerUI_output(x);
}

void HoaRecomposerUI_wide(t_HoaRecomposerUI *x, t_symbol *s, long ac, t_atom *av)
{
    HoaRecomposerUI_set(x, s, ac, av); // notifying in set method
    HoaRecomposerUI_output(x);
}

t_max_err set_numberOfMics(t_HoaRecomposerUI *x, void *attr, long ac, t_atom *av)
{
	if (ac && av)
    {
        if (atom_gettype(av) == A_LONG || atom_gettype(av) == A_FLOAT) {
            x->f_mics->setNumberOfMics(atom_getlong(av));
            x->f_numberOfMic = x->f_mics->getNumberOfMics();
        }
        jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
        jbox_redraw((t_jbox *)x);
    }
    
    HoaRecomposerUI_reset(x, gensym("reset"), 0, NULL);
    //object_method(x, gensym("resetangle"));
    return MAX_ERR_NONE;
}

void HoaRecomposerUI_anything(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av)
{
	;
}

//========================= Output Methods :

void HoaRecomposerUI_bang(t_HoaRecomposerUI *x)
{
    HoaRecomposerUI_output(x);
}

void HoaRecomposerUI_outputAndNotifyChange(t_HoaRecomposerUI *x)
{
    notifyChange(x);
    HoaRecomposerUI_output(x);
}

void notifyChange(t_HoaRecomposerUI *x)
{
    // pattrstorage change notification
    object_notify(x, _sym_modified, NULL);
}

void HoaRecomposerUI_output(t_HoaRecomposerUI *x)
{
    int nmics = x->f_mics->getNumberOfMics();
	t_atom	av_left[nmics];
    t_atom  av_right[2];
    
    // number of microphones
    atom_setsym(av_right, gensym("nmics"));
    atom_setlong(av_right+1, nmics);
    outlet_list(x->f_outlet_infos, NULL, 2, av_right);
    
    // angles of microphones
    for (int i=0; i<nmics; i++) {
        atom_setfloat(av_left+i, x->f_mics->getAngleInRadian(i));
    }
    outlet_anything(x->f_out, gensym("angles"), nmics, av_left);
    
    // wider values of microphones
    for (int i=0; i<nmics; i++) {
        atom_setfloat(av_left+i, x->f_mics->getWiderValue(i));
    }
    outlet_anything(x->f_out, gensym("directivities"), nmics, av_left);
}

//========================= Notify Methods :

t_max_err HoaRecomposerUI_notify(t_HoaRecomposerUI *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	//if (msg == gensym("attr_modified"))
    if (msg == _sym_attr_modified)
	 {
         name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
         if(name == gensym("nmics"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
             jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
             jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
         }
         else if(name == gensym("miccolor") || name == gensym("selmiccolor"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
         }
         else if(name == gensym("mictextcolor") || name == gensym("selmictextcolor"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
         }
         else if(name == gensym("bgcolor") || name == gensym("circlecolor"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
         }
         else if(name == gensym("harmonicscolor"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
         }
         else if (name == gensym("fisheyecolor"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("fisheye_layer"));
         }
         jbox_redraw((t_jbox *)x);
	 }
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

//========================= Paint Methods :

void HoaRecomposerUI_paint(t_HoaRecomposerUI *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	x->rect = rect;
    //x->f_micRadius = rect.width * 0.45;
    x->f_micRadius = rect.width * 0.46;
	draw_background(x, view, &rect);
    draw_harmonics(x, view, &rect);
    draw_microphones(x, view, &rect);
    draw_fishEye(x, view, &rect);
    draw_textMics(x, view, &rect);
    draw_rect_selection(x, view, &rect);
}


void draw_microphones(t_HoaRecomposerUI *x, t_object *view, t_rect *rect)
{
    double w = rect->width;
	int numMics = x->f_numberOfMic;
    double mic_angle;
    double hpSize;
	hpSize = (w / 20.) * 0.4;
    
    t_jrgba overMicColor = x->f_colorMicSelected;
    overMicColor.red -= 0.1;
    overMicColor.green -= 0.1;
    overMicColor.blue -= 0.1;
    
    t_jmatrix transform;

	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("mic_layer"), rect->width, rect->height);
	
	if (g) {
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
		jgraphics_set_matrix(g, &transform);
        
		for(int i=numMics-1; i>=0; i--)
		{
            jgraphics_set_source_jrgba(g, x->f_mics->isSelected(i) ? &x->f_colorMicSelected : ( (x->f_last_mouseMoveOverMic == i) ? &overMicColor : &x->f_colorMic) );
            mic_angle = x->f_mics->getAngleInRadian(i);
            
            jgraphics_rotate(g, mic_angle);
            jgraphics_translate(g, 0, x->f_micRadius);
            //-- rotated and translated
            
            // head of the mic :
            jgraphics_arc(g, 0, 0, hpSize, 0, CICM_2PI);
            jgraphics_fill_preserve(g);
            
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, x->f_mics->isSelected(i) ? &x->f_colorMic : ( (x->f_last_mouseMoveOverMic == i) ? &overMicColor : &x->f_colorMicSelected) );
            jgraphics_stroke(g);
            
            //-- inverse rotation and translate
            jgraphics_translate(g, 0, -x->f_micRadius);
            jgraphics_rotate(g, -mic_angle);
		}
            
		jbox_end_layer((t_object*)x, view, gensym("mic_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("mic_layer"), 0., 0.);
}

void draw_textMics(t_HoaRecomposerUI *x, t_object *view, t_rect *rect)
{
    double w = rect->width;
	int numMics = x->f_numberOfMic;
    double mic_angle;

    t_jfont *jf;
	t_jtextlayout *jtl;
    char text[16];
    double fontsize = 10;
    double x1, y1;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("text_layer"), rect->width, rect->height);
    	
	if (g) {
        
        jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_ITALIC, JGRAPHICS_FONT_WEIGHT_BOLD, fontsize);
        jtl = jtextlayout_withbgcolor(g, &x->f_colorMic);
        
        for(int i=numMics-1; i>=0; i--)
        {
            jtextlayout_settextcolor(jtl, (x->f_mics->isSelected(i) || x->f_last_mouseMoveOverMic == i) ? &x->f_colorTextMicSelected : &x->f_colorTextMic);
            mic_angle = CICM_2PI - (x->f_mics->getAngleInRadian(i) + CICM_PI2);
            x1 = long(Tools::abscisse(x->f_micRadius, mic_angle) + (w*0.5))+0.5;
            y1 = long(Tools::ordinate(x->f_micRadius, mic_angle) + (w*0.5))+0.5;
            sprintf(text,"%i", i+1);
			jtextlayout_set(jtl, text, jf, x1 - fontsize * 1.5, y1 - 10, fontsize * 3., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
            jtextlayout_draw(jtl, g);
        }
        
		jbox_end_layer((t_object*)x, view, gensym("text_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("text_layer"), 0., 0.);
}

void draw_harmonics(t_HoaRecomposerUI *x, t_object *view, t_rect *rect)
{
    double w = rect->width;
    t_jrgba harmonicsFillColor = x->f_colorHarmonics;
    
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);
    
    harmonicsFillColor.alpha = Tools::clip_min(x->f_colorHarmonics.alpha - 0.2);
    
	if (g)
	{
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, (w*0.5), (w*0.5));
		jgraphics_set_matrix(g, &transform);
		jgraphics_set_line_width(g, 2);
        jgraphics_set_line_cap(g, JGRAPHICS_LINE_CAP_ROUND);
        jgraphics_set_line_join(g, JGRAPHICS_LINE_JOIN_ROUND);
        
        for (int i = 0; i < x->f_numberOfMic; i++) {
            if(x->f_mics->getBiggestContribution(i) != 0.)
            {
                //double factor = (x->f_micRadius*0.92) / x->f_mics->getBiggestContribution(i);
                double factor = (x->f_micRadius*0.92);
                
                jgraphics_set_source_jrgba(g, &harmonicsFillColor);
                jgraphics_move_to(g, x->f_mics->getBiggestLobe_x(i, 0) * factor, x->f_mics->getBiggestLobe_y(i, 0) * factor);
                for(int j = 1; j < x->f_mics->getBiggestLobeNbPoint(i); j++)
                {
                    jgraphics_line_to(g, x->f_mics->getBiggestLobe_x(i, j) * factor, x->f_mics->getBiggestLobe_y(i, j) * factor );
                }
                jgraphics_line_to(g, x->f_mics->getBiggestLobe_x(i, 0) * factor, x->f_mics->getBiggestLobe_y(i, 0) * factor);
                
                jgraphics_close_path(g);
                jgraphics_fill_preserve(g);
                jgraphics_set_source_jrgba(g, &x->f_colorHarmonics);
                jgraphics_stroke(g);
            }
        }
        
		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
}

int isPointOverAMic(t_HoaRecomposerUI *x, t_pt *pt)
{
    t_jsurface *surface;
    t_jgraphics *context;
    t_jmatrix transform;
    int result = -1;
    double w = x->rect.width;
    double mic_angle;
    double hpSize;
	hpSize = (w / 20.) * 0.4;
    t_pt ptTranformed = {pt->x-(w*0.5), (w - pt->y)-(w*0.5)};
    
    surface = jgraphics_image_surface_create(JGRAPHICS_FORMAT_A8, 1, 1);
    context = jgraphics_create(surface);
    
    jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
    jgraphics_set_matrix(context, &transform);
    
    for(int i=x->f_numberOfMic-1; i>=0; i--)
    {
        mic_angle = x->f_mics->getAngleInRadian(i);        
        
        //-- test head :
        jgraphics_rotate(context, mic_angle);
        jgraphics_translate(context, 0, x->f_micRadius);
        jgraphics_new_path(context);
        jgraphics_arc(context, 0, 0, hpSize, 0, CICM_2PI);
        jgraphics_close_path(context);
        jgraphics_translate(context, 0, -x->f_micRadius);
        jgraphics_rotate(context, -mic_angle);
        if (jgraphics_in_fill(context, ptTranformed.x, ptTranformed.y)) {
            result = i;
            break;
        }
    }
    
    jgraphics_destroy(context);
    jgraphics_surface_destroy(surface);
    
    return result;
}

void draw_background(t_HoaRecomposerUI *x,  t_object *view, t_rect *rect)
{
	double w = x->rect.width;
    t_jrgba HpMarkerColor = {0.2,0.2,0.2,1};
    int colorFactor;
    t_jrgba shadLight, shadDark;
    double hpSize;
	hpSize = (w / 20.) * 0.4;
    t_jmatrix transform;
    double mic_angle = CICM_2PI / x->f_mics->getNumberOfMics();
    
    shadLight = shadDark = x->f_colorInnerCircle;
    shadDark.red = Tools::clip_min(shadDark.red - 0.05);
    shadDark.green = Tools::clip_min(shadDark.green - 0.05);
    shadDark.blue = Tools::clip_min(shadDark.blue - 0.05);
    
    shadLight.red = Tools::clip_max(shadLight.red + 0.05, 1.);
    shadLight.green = Tools::clip_max(shadLight.green + 0.05, 1.);
    shadLight.blue = Tools::clip_max(shadLight.blue + 0.05, 1.);
    
    HpMarkerColor = x->f_colorInnerCircle;
    colorFactor = (x->f_colorInnerCircle.red + x->f_colorInnerCircle.green + x->f_colorInnerCircle.blue > 1.5) ? -1 : 1;
    HpMarkerColor.red = Tools::clip(HpMarkerColor.red + (0.2*colorFactor), 0., 1.);
    HpMarkerColor.green = Tools::clip(HpMarkerColor.green + (0.2*colorFactor), 0., 1.);
    HpMarkerColor.blue = Tools::clip(HpMarkerColor.blue + (0.2*colorFactor), 0., 1.);
    
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
	
	if (g) {
        
        jgraphics_set_line_cap(g, JGRAPHICS_LINE_CAP_ROUND);
		jgraphics_set_source_jrgba(g, &x->f_colorInnerCircle);
		jgraphics_arc(g, w*0.5, w*0.5, x->f_micRadius,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
        
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
        jgraphics_set_matrix(g, &transform);
        jgraphics_set_source_jrgba(g, &HpMarkerColor);
        jgraphics_set_line_width(g, 1.);
        
        for (int i=0; i < x->f_mics->getNumberOfMics(); i++) {
            jgraphics_rotate(g, mic_angle*i);
            jgraphics_translate(g, 0, x->f_micRadius);
            jgraphics_arc(g, 0, 0, hpSize*1.4, 0, CICM_2PI);
            jgraphics_set_source_jrgba(g, &x->f_colorInnerCircle);
            jgraphics_fill(g);
            jgraphics_translate(g, 0, -x->f_micRadius);
            jgraphics_rotate(g, -mic_angle*i);
            
            jgraphics_rotate(g, mic_angle*i);
            jgraphics_translate(g, 0, x->f_micRadius);
            jgraphics_move_to(g, 0, -hpSize*0.8);
            jgraphics_line_to(g, 0, hpSize*0.8);
            jgraphics_set_source_jrgba(g, &HpMarkerColor);
            jgraphics_stroke(g);
            jgraphics_translate(g, 0, -x->f_micRadius);
            jgraphics_rotate(g, -mic_angle*i);
        }
        
        // center crosshair
        for (int i=0; i<2; i++) {
            jgraphics_set_source_jrgba(g, i == 0 ? &shadLight : &shadDark);
            jgraphics_move_to(g, 5.5, 5.5+i);
            jgraphics_line_to(g, -5.5, -5.5+i);
            jgraphics_move_to(g, -5.5, 5.5+i);
            jgraphics_line_to(g, 5.5, -5.5+i);
            jgraphics_stroke(g);
        }
		
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_fishEye(t_HoaRecomposerUI *x, t_object *view, t_rect *rect)
{
    t_pt cartFisheyeDest, cart;
    double micAngle, w;
    w = x->rect.width;
    double dashes[2] = {4, 4};
    
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("fisheye_layer"), rect->width, rect->height);
	
	if (g && x->f_showFishEye) {
        
        jgraphics_set_source_jrgba(g, &x->f_fisheyecolor);
        jgraphics_set_line_width(g, 1);
        jgraphics_set_dash(g, dashes, 2, 0);
        
        cartFisheyeDest.x = Tools::abscisse(x->f_micRadius, x->f_fisheyeAngle);
        cartFisheyeDest.y = Tools::ordinate(x->f_micRadius, x->f_fisheyeAngle);
        cartFisheyeDest.x = (cartFisheyeDest.x + (w*0.5));
        cartFisheyeDest.y = ( (w - cartFisheyeDest.y) - (w*0.5) );
        
        for (int i=0; i < x->f_numberOfMic; i++)
        {
            if (x->f_mics->isSelected(i))
            {
                micAngle = x->f_mics->getAngleInRadian(i);
                cart.x = Tools::abscisse(x->f_micRadius, micAngle + CICM_PI2);
                cart.y = Tools::ordinate(x->f_micRadius, micAngle + CICM_PI2);
                cart.x = (cart.x + (w*0.5));
                cart.y = ( (w - cart.y) - (w*0.5) );
                jgraphics_move_to(g, cartFisheyeDest.x, cartFisheyeDest.y);
                jgraphics_line_to(g, cart.x, cart.y);
                jgraphics_stroke(g);
                jgraphics_arc(g, cart.x, cart.y, 2, 0, CICM_2PI);
                jgraphics_fill(g);
            }
        }
        
        jgraphics_arc(g, cartFisheyeDest.x, cartFisheyeDest.y, 4, 0, CICM_2PI);
        jgraphics_fill(g);
        
		jbox_end_layer((t_object*)x, view, gensym("fisheye_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("fisheye_layer"), 0., 0.);
}

void draw_rect_selection(t_HoaRecomposerUI *x, t_object *view, t_rect *rect)
{
    t_jrgba fillColor = x->f_color_selection;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("rectselection_layer"), rect->width, rect->height);
    fillColor.alpha = Tools::clip_min(fillColor.alpha - 0.2);
	
	if (g && x->f_rectSelectionExist)
    {
        jgraphics_rectangle(g, x->f_rectSelection.x, x->f_rectSelection.y, x->f_rectSelection.width, x->f_rectSelection.height);
        
        jgraphics_set_source_jrgba(g, &fillColor);
        jgraphics_fill_preserve(g);
        jgraphics_set_source_jrgba(g, &x->f_color_selection);
        jgraphics_set_line_width(g, 2);
        jgraphics_stroke(g);
		
		jbox_end_layer((t_object*)x, view, gensym("rectselection_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("rectselection_layer"), 0., 0.);
}
//========================= Mouse Methods :

void HoaRecomposerUI_mouseenter(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
	//post("mouseenter");
}

void HoaRecomposerUI_mouseleave(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
	//post("mouseleave");
}

void HoaRecomposerUI_mousedown(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{    
    //-- modifiers :
    //post("modifiers : %ld", modifiers);
    // 16 : rien
    // 17 : cmd
    // 18 : shift
    // 148: ctrl
    // 19 : cmd+shift
    
    double w = x->rect.width;
    x->f_last_mouseDown = pt;
    
    int isMouseDownOverAMic = -1;
    isMouseDownOverAMic = isPointOverAMic(x, &pt);
    
    
    if (x->f_rectSelectionExist) {
        end_rect_selection(x, pt);
    }
    
    // ctrl => set selected mics fisheyes start angle at the current angle :
    if (modifiers == 148)
    {
        t_pt ptCart = {pt.x-(w*0.5), (w - pt.y)-(w*0.5)};
        x->f_last_mouseDragRadius = Tools::radius(ptCart.x, ptCart.y);
        x->f_mics->setFisheyeStartAngle(-2);
        x->f_mics->setFisheyeDestAngle(x->f_fisheyeAngle - CICM_PI2);
        /*
        for (int i=0; i<x->f_numberOfMic; i++) {
            if (x->f_mics->isSelected(i)) {
                post("startAngle mic %ld = %f", i, x->f_mics->getFisheyeStartAngle(i));
            }
        }
        */
    }
    else if (isMouseDownOverAMic == -1 )
    {
        if (modifiers == 17)
        {
            begin_rect_selection(x, pt);
        }
        else if (modifiers == 16) {
            x->f_mics->setSelected(-1, 0); // tout deselectionné
        }
    }
    else
    {
        if (modifiers == 16) // rien
        {
            if (!x->f_mics->isSelected(isMouseDownOverAMic)) {
                x->f_mics->setSelected(-1, 0); // tout deselectionné
                x->f_mics->setSelected(isMouseDownOverAMic, 1);
            }
        }
        else if (modifiers == 17) // cmd
        {
            x->f_mics->setSelected(isMouseDownOverAMic, -1);
        }
    }
    
    x->f_last_mouseDownOverMic = isMouseDownOverAMic;
    jmouse_setcursor(patcherview, (t_object *)x, (x->f_last_mouseMoveOverMic != -1) ? JMOUSE_CURSOR_POINTINGHAND : JMOUSE_CURSOR_ARROW);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
    jbox_redraw((t_jbox *)x);
}

void HoaRecomposerUI_mousedrag(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double w = x->rect.width;
    t_pt ptCart = {pt.x-(w*0.5), (w - pt.y)-(w*0.5)};
    double angleDrag = Tools::angle(ptCart.x, ptCart.y) - CICM_PI2;
    double radiusDrag = Tools::radius(ptCart.x, ptCart.y);

    if (x->f_rectSelectionExist)
    {
        do_rect_selection(x, pt);
    }
    else if (modifiers == 148 || x->f_showFishEye) // ctrl => do a fisheye
    {
        double fisheyeAngle = x->f_mics->getFisheyeDestAngle();
        double factor = Tools::isInsideRad(angleDrag, fisheyeAngle-CICM_PI2, fisheyeAngle+CICM_PI2) ? 1 : -1;
        double radiusDelta = (x->f_last_mouseDragRadius - radiusDrag) * factor;
        x->f_mics->setSelectedMicsFisheyeStepWithDelta(-2, radiusDelta / x->f_micRadius);
        HoaRecomposerUI_outputAndNotifyChange(x);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("fisheye_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
        jbox_redraw((t_jbox *)x);
    }
    else if (x->f_last_mouseDownOverMic != -1)
    {
        if (modifiers == 18) // shift => set wider
        {
            double micAngle = x->f_mics->getAngleInRadian(x->f_last_mouseDownOverMic);
            double factor = Tools::isInsideRad(angleDrag, micAngle-CICM_PI2, micAngle+CICM_PI2) ? 1 : -1;
            double radiusDelta = (x->f_last_mouseDragRadius - radiusDrag) * factor;
            x->f_mics->setSelectedMicsWiderValueWithRadiusDelta(radiusDelta / x->f_micRadius);
        }
        else // => simply rotate
        {
            int magnet = (modifiers == 17) ? 1 : 0;
            x->f_mics->rotateSelectedMicsWithRadian(angleDrag, x->f_last_mouseDownOverMic, magnet);
        }
        
        HoaRecomposerUI_outputAndNotifyChange(x);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
        jbox_redraw((t_jbox *)x);
    }
    
	x->f_last_mouseDrag = pt;
    x->f_last_mouseDragAngle = angleDrag;
    x->f_last_mouseDragRadius = radiusDrag;
}

void HoaRecomposerUI_mouseup(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->f_last_mouseDragRadius = x->f_micRadius;
    x->f_last_mouseUp = pt;
    int isMouseUpOverAMic = -1;
    isMouseUpOverAMic = isPointOverAMic(x, &pt);
    
    
    if(x->f_showFishEye)
    {
        x->f_showFishEye = 0;
        jbox_invalidate_layer((t_object *)x, NULL, gensym("fisheye_layer"));
    }
    
    if (x->f_rectSelectionExist) {
        end_rect_selection(x, pt);
    }
    
    x->f_last_mouseUpOverMic = isMouseUpOverAMic;
    jmouse_setcursor(patcherview, (t_object *)x, (x->f_last_mouseMoveOverMic != -1) ? JMOUSE_CURSOR_POINTINGHAND : JMOUSE_CURSOR_ARROW);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
    jbox_redraw((t_jbox *)x);    
}

void HoaRecomposerUI_mousemove(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
    //post("modifier %ld", modifiers);
    double w = x->rect.width;
    if ( (x->f_last_mouseMove.x != pt.x) || (x->f_last_mouseMove.y != pt.y) ) {
        x->f_last_mouseMoveOverMic = isPointOverAMic(x, &pt);
        x->f_last_mouseMove = pt;
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
        jbox_redraw((t_jbox *)x);
    }
    
    // fisheye :
    if (modifiers == 132) // ctrl
    {
        x->f_showFishEye = 1;
        t_pt ptCart = {pt.x-(w*0.5), (w - pt.y)-(w*0.5)};
        x->f_fisheyeAngle = Tools::angle(ptCart.x, ptCart.y);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("fisheye_layer"));
        jbox_redraw((t_jbox *)x);
    }
    else if (x->f_showFishEye)
    {
        x->f_showFishEye = 0;
        jbox_invalidate_layer((t_object *)x, NULL, gensym("fisheye_layer"));
        jbox_redraw((t_jbox *)x);
    }
        
    
    if (x->f_last_mouseMoveOverMic == -1 && modifiers == 1) // cmd
    {
        jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_CROSSHAIR);
    }
    else if (modifiers == 132) // ctrl
    {
        jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_DRAGGINGHAND);
    }
    else
    {
        jmouse_setcursor(patcherview, (t_object *)x, (x->f_last_mouseMoveOverMic != -1) ? JMOUSE_CURSOR_POINTINGHAND : JMOUSE_CURSOR_ARROW);
    }
}

void HoaRecomposerUI_mousedoubleclick(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if (x->f_last_mouseDownOverMic != -1) {
        x->f_mics->setAngleToClosestDefMicAngle(x->f_last_mouseDownOverMic);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
        jbox_redraw((t_jbox *)x);
        HoaRecomposerUI_outputAndNotifyChange(x);
    }
}

long HoaRecomposerUI_key(t_HoaRecomposerUI *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{	
	//post("keycode : %ld , modifiers : %ld , textcharacter : %ld ", keycode, modifiers, textcharacter);
    int filter = 0;
	if (keycode == 97 && modifiers == 1 && textcharacter == 0) // cmd+a -> select all;
    {
		x->f_mics->setSelected(-1, 1); // tout selectionné
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
        jbox_redraw((t_jbox *)x);
        filter = 1;
	}
	return filter;	// returns 1 if you want to filter it from the key object (otherwise return 0)
}

void begin_rect_selection(t_HoaRecomposerUI *x, t_pt pt)
{
    x->f_rectSelectionExist = true;
    x->f_rectSelection.width = x->f_rectSelection.height = 0;
    x->f_rectSelection.x = x->f_rectSelectionBegin.x = pt.x;
    x->f_rectSelection.y = x->f_rectSelectionBegin.y = pt.y;
}

void end_rect_selection(t_HoaRecomposerUI *x, t_pt pt)
{
    for (int i=0; i < x->f_numberOfMic; i++) {
        if (isMicInsideRect(x, i, x->f_rectSelection)) {
            x->f_mics->setSelected(i, -1); // toggle selection state
        }
    }
    x->f_rectSelectionExist = false;
    jbox_invalidate_layer((t_object *)x, NULL, gensym("rectselection_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("text_layer"));
    jbox_redraw((t_jbox *)x);
}

void do_rect_selection(t_HoaRecomposerUI *x, t_pt pt)
{
    x->f_rectSelectionExist = true;
    if (pt.x > x->f_rectSelectionBegin.x)
    {
        x->f_rectSelection.width = pt.x - x->f_rectSelectionBegin.x;
        x->f_rectSelection.x = x->f_rectSelectionBegin.x;
    }
    else
    {
        x->f_rectSelection.width = x->f_rectSelectionBegin.x -  pt.x;
        x->f_rectSelection.x = x->f_rectSelectionBegin.x - x->f_rectSelection.width;
    }
    
    if (pt.y > x->f_rectSelectionBegin.y)
    {
        x->f_rectSelection.height = pt.y - x->f_rectSelectionBegin.y;
        x->f_rectSelection.y = x->f_rectSelectionBegin.y;
    }
    else
    {
        x->f_rectSelection.height = x->f_rectSelectionBegin.y -  pt.y;
        x->f_rectSelection.y = x->f_rectSelectionBegin.y - x->f_rectSelection.height;
    }
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("rectselection_layer"));
    jbox_redraw((t_jbox *)x);
}

bool isMicInsideRect(t_HoaRecomposerUI *x, int micIndex, t_rect rectSelection)
{
    double w = x->rect.width;
    t_pt micPoint;
    micPoint.x = Tools::abscisse(x->f_micRadius, x->f_mics->getAngleInRadian(micIndex) + CICM_PI2);
    micPoint.y = Tools::ordinate(x->f_micRadius, x->f_mics->getAngleInRadian(micIndex) + CICM_PI2);
    micPoint.x = (micPoint.x + (w*0.5));
    micPoint.y = ( (w - micPoint.y) - (w*0.5) );
    return jgraphics_ptinrect(micPoint, rectSelection);
}
