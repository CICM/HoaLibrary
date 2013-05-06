/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot, Eliott Paris Universite Paris 8
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

#include "CicmProjectHeader.h"
#include "AmbisonicVirtualMicUIManager.h"

typedef struct  _HoaRecomposerUI
{
	t_jbox		j_box;
	t_rect		rect;
    
    // color
	t_jrgba		f_colorBackground;
    t_jrgba		f_colorInnerCircle;
	t_jrgba		f_colorMic;
    t_jrgba		f_colorMicSelected;
	t_jrgba		f_color_selection;
    
    //microphones
    AmbisonicVirtualMicUIManager* f_mics;
    int			f_numberOfMic;
    double		f_MicAngles[MAX_MICS];
    double		f_MicWiders[MAX_MICS];
    int			f_isMicSelected[MAX_MICS];
    int			f_aMicIsSelected;
	
    // options
	int         f_activeMagnet;
    char        f_displayAngle;
	double		f_speakerOffset;
	int			f_numberOfSpeaker;
    
    // mouse
	t_pt		f_last_mouseMove;
    int         f_last_mouseMoveOverMic;
    t_pt		f_last_mouseDown;
    int         f_last_mouseDownOverMic;
    t_pt		f_last_mouseUp;
    int         f_last_mouseUpOverMic;
    t_pt		f_last_mouseDrag;
    double		f_last_mouseDragAngle;
    double      f_last_mouseDragRadius;
    
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

// mouse/key methods
void HoaRecomposerUI_mouseleave(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mouseenter(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mousedown(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mousedown2(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mouseup(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
long HoaRecomposerUI_key(t_HoaRecomposerUI *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void HoaRecomposerUI_mousemove(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);
void HoaRecomposerUI_mousedrag(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers);

// msg-in methods
t_max_err set_MicAngles(t_HoaRecomposerUI *x, void *attr, long ac, t_atom *av);
t_max_err set_numberOfMics(t_HoaRecomposerUI *x, void *attr, long ac, t_atom *av);
void HoaRecomposerUI_bang(t_HoaRecomposerUI *x);
void HoaRecomposerUI_list(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av);
void HoaRecomposerUI_anything(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av);
void HoaRecomposerUI_float(t_HoaRecomposerUI *x, double f);
void HoaRecomposerUI_resetAngles(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av);

void HoaRecomposerUI_nb_hp(t_HoaRecomposerUI *x, int v);

// msg-out methods
void HoaRecomposerUI_output(t_HoaRecomposerUI *x);

// paint methods
void HoaRecomposerUI_paint(t_HoaRecomposerUI *x, t_object *view);
void draw_background(t_HoaRecomposerUI *x, t_object *view, t_rect *rect);
void draw_microphones(t_HoaRecomposerUI *x, t_object *view, t_rect *rect);
void draw_oneMic(t_HoaRecomposerUI *x, t_jgraphics *g, double posX, double posY, double rotDegree, double size);

//calcul methods
int isPointOverAMic(t_HoaRecomposerUI *x, t_pt *pt);

int main()
{
	t_class *c;
	
	c = class_new("hoa.recomposer", (method)HoaRecomposerUI_new, (method)HoaRecomposerUI_free, (short)sizeof(t_HoaRecomposerUI), 0L, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method)HoaRecomposerUI_assist,          "assist",		A_CANT,	0);
	class_addmethod(c, (method)HoaRecomposerUI_paint,           "paint",		A_CANT,	0);
	class_addmethod(c, (method)HoaRecomposerUI_getdrawparams,   "getdrawparams", A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposerUI_notify,          "notify",		A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposerUI_bang,			"bang",			0L,0);
	class_addmethod(c, (method)HoaRecomposerUI_list,			"list",			A_GIMME, 0);
    class_addmethod(c, (method)HoaRecomposerUI_resetAngles,		"resetangles",	A_GIMME, 0);
	class_addmethod(c, (method)HoaRecomposerUI_anything,		"anything",		A_GIMME, 0);
	class_addmethod(c, (method) HoaRecomposerUI_mousedown,	"mousedown",		A_CANT, 0);
	class_addmethod(c, (method)HoaRecomposerUI_mousedrag,	"mousedrag",		A_CANT, 0);
	class_addmethod(c, (method) HoaRecomposerUI_mouseup,			"mouseup",		A_CANT, 0);
	class_addmethod(c, (method) HoaRecomposerUI_mousemove,		"mousemove",	A_CANT, 0);
	class_addmethod(c, (method) HoaRecomposerUI_key,				"key",			A_CANT, 0);
	
	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 300");
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_HoaRecomposerUI, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.65 0.65 0.65 1.");
    
    CLASS_ATTR_RGBA				(c, "circlecolor", 0, t_HoaRecomposerUI, f_colorInnerCircle);
	CLASS_ATTR_CATEGORY			(c, "circlecolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "circlecolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "circlecolor", 0, "Circle Inner Color");
	CLASS_ATTR_ORDER			(c, "circlecolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "circlecolor", 0, "0.3 0.3 0.3 1.");
	
	CLASS_ATTR_RGBA				(c, "miccolor", 0, t_HoaRecomposerUI, f_colorMic);
	CLASS_ATTR_CATEGORY			(c, "miccolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "miccolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "miccolor", 0, "Microphone Color");
	CLASS_ATTR_ORDER			(c, "miccolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "miccolor", 0, "0. 0. 0. 1.");
    
    CLASS_ATTR_RGBA				(c, "selmiccolor", 0, t_HoaRecomposerUI, f_colorMicSelected);
	CLASS_ATTR_CATEGORY			(c, "selmiccolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "selmiccolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "selmiccolor", 0, "Selected Microphone Color");
	CLASS_ATTR_ORDER			(c, "selmiccolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "selmiccolor", 0, "0.5 0.5 0.5 1.");
	
	CLASS_ATTR_LONG				(c, "nmics",0, t_HoaRecomposerUI, f_numberOfMic);
	CLASS_ATTR_FILTER_MIN		(c, "nmics", 1);
    CLASS_ATTR_ACCESSORS		(c, "nmics", NULL, set_numberOfMics);
	CLASS_ATTR_LABEL			(c, "nmics", 0, "Number of Microphones");
	CLASS_ATTR_CATEGORY			(c, "nmics",0,"Custom");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"nmics",0,"8");
    
    CLASS_ATTR_FLOAT_VARSIZE	(c, "mic_angles", 0, t_HoaRecomposerUI, f_MicAngles, f_numberOfMic, MAX_MICS);
	CLASS_ATTR_ACCESSORS		(c, "mic_angles", NULL, set_MicAngles);
	CLASS_ATTR_CATEGORY			(c, "mic_angles", 0, "Custom");
	CLASS_ATTR_ORDER			(c, "mic_angles", 0, "2");
	CLASS_ATTR_LABEL			(c, "mic_angles", 0, "Angles of Microphones");
	CLASS_ATTR_DEFAULT			(c, "mic_angles", 0, "666");
	CLASS_ATTR_SAVE				(c, "mic_angles", 1);
    
    CLASS_ATTR_LONG             (c, "magnetmics", 0, t_HoaRecomposerUI, f_activeMagnet);
	CLASS_ATTR_CATEGORY			(c, "magnetmics", 0, "Custom");
	CLASS_ATTR_ORDER			(c, "magnetmics", 0, "3");
	CLASS_ATTR_LABEL			(c, "magnetmics", 0, "Active Magnetism on Mics");
	CLASS_ATTR_DEFAULT			(c, "magnetmics", 0, "1");
	CLASS_ATTR_SAVE				(c, "magnetmics", 1);
	
	class_register(CLASS_BOX, c);
	HoaRecomposerUI_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *HoaRecomposerUI_new(t_symbol *s, int argc, t_atom *argv)
{
	t_HoaRecomposerUI *x =  NULL; 
	int i;
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_HoaRecomposerUI *)object_alloc(HoaRecomposerUI_class);
	flags = 0 
	| JBOX_DRAWFIRSTIN 
	| JBOX_DRAWINLAST
	| JBOX_TRANSPARENT	
	| JBOX_GROWY
	| JBOX_HILITE
	;
	jbox_new(&x->j_box, flags, argc, argv);
    
    x->f_outlet_infos = listout(x);
    x->f_out = listout(x);
    
    
    x->f_numberOfMic = DEF_MICS;
	x->f_displayAngle = 1;
    x->f_last_mouseMoveOverMic = x->f_last_mouseDownOverMic = x->f_last_mouseUpOverMic = -1;
    
    x->f_mics = new AmbisonicVirtualMicUIManager(x->f_numberOfMic);
    
    x->f_mics->setNumberOfMics(x->f_numberOfMic);
        
	for(i = 0; i < MAX_MICS; i++) {
		x->f_MicAngles[i] = 0;
	}

	x->j_box.b_firstin = (t_object*) x;
	
	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);
	
	return (x);
}

void HoaRecomposerUI_getdrawparams(t_HoaRecomposerUI *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = 1;
	params->d_cornersize = 6;
}

void HoaRecomposerUI_free(t_HoaRecomposerUI *x)
{
	jbox_free(&x->j_box);
    delete x->f_mics;
}

void HoaRecomposerUI_assist(t_HoaRecomposerUI *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		sprintf(s,"(list) Set Microphones Angles");
	} else {
		if (a == 0) {
			sprintf(s,"(list) Microphones Angles");
		}
		else if (a == 1) {
			sprintf(s,"Infos output");
		}
	}
}

/* --------- */

void HoaRecomposerUI_resetAngles(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av)
{    
    if (ac == 0) {
        x->f_mics->resetAngles(-1);
    }
    else
    {
        for(int i = 0; i < ac ; i++)
        {
            if (atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG)
                x->f_mics->resetAngles(atom_getlong(av + i));
        }
    }
    
    HoaRecomposerUI_output(x);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
	jbox_redraw((t_jbox *)x);
}

t_max_err set_MicAngles(t_HoaRecomposerUI *x, void *attr, long ac, t_atom *av)
{
    double listAngles[ac];
    long index;
	
    if (ac && av)
    {
        if (atom_gettype(av) == A_LONG && Tools::isInside(index = atom_getlong(av), long(0), x->f_mics->getNumberOfMics())) // index + angle
        {
            if (!Tools::isInside(index, long(0), x->f_mics->getNumberOfMics())) return MAX_ERR_NONE;
            x->f_mics->setAngleInDegree(index, atom_getfloat(av+1));
            x->f_MicAngles[index] = x->f_mics->getAngleInDegree(index);
        }
        else
        {
            for(int i = 0; i < ac ; i++)
            {
                if (atom_gettype(av+i) == A_FLOAT || atom_gettype(av+i) == A_LONG) {
                    listAngles[i] = atom_getfloat(av + i);
                } else listAngles[i] = 0;
            }
            x->f_mics->setAnglesInDegree(listAngles, ac);
            for (int i=0; i < x->f_mics->getNumberOfMics(); i++) {
                x->f_MicAngles[i] = x->f_mics->getAngleInDegree(i);
            }
        }
    }

    HoaRecomposerUI_output(x);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
	jbox_redraw((t_jbox *)x);
    return MAX_ERR_NONE;
}

t_max_err set_numberOfMics(t_HoaRecomposerUI *x, void *attr, long ac, t_atom *av)
{
	if (ac && av)
    {
        if (atom_gettype(av) == A_LONG || atom_gettype(av) == A_FLOAT) {
            x->f_mics->setNumberOfMics(atom_getlong(av));
            x->f_numberOfMic = x->f_mics->getNumberOfMics();
        }
        jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
        jbox_redraw((t_jbox *)x);
    }
    HoaRecomposerUI_output(x);
    return MAX_ERR_NONE;
}

void HoaRecomposerUI_anything(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av)
{
	;
}

void HoaRecomposerUI_list(t_HoaRecomposerUI *x, t_symbol *s, short ac, t_atom *av)
{
	;
}

//========================= Output Methods :

void HoaRecomposerUI_bang(t_HoaRecomposerUI *x)
{
    HoaRecomposerUI_output(x);
}

void HoaRecomposerUI_output(t_HoaRecomposerUI *x)
{
    int nmics = x->f_mics->getNumberOfMics();
	t_atom	av_angles[nmics];
    t_atom  av_infos[2];
    
    atom_setsym(av_infos, gensym("nmics"));
    atom_setlong(av_infos+1, nmics);
    outlet_list(x->f_outlet_infos, NULL, 2, av_infos);
    
    for (int i=0; i<nmics; i++) {
        atom_setfloat(av_angles+i, (float)x->f_mics->getAngleInRadian(i));
    }
    outlet_list(x->f_out, NULL, nmics, av_angles);
}

//========================= Notify Methods :

t_max_err HoaRecomposerUI_notify(t_HoaRecomposerUI *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	 {
         name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
         if(name == gensym("nmics"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
         }
         else if(name == gensym("miccolor") || name == gensym("selmiccolor"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
         }
         else if(name == gensym("bgcolor") || name == gensym("circlecolor"))
         {
             jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
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
	draw_background(x, view, &rect);
    draw_microphones(x, view, &rect);
}

void draw_microphones(t_HoaRecomposerUI *x, t_object *view, t_rect *rect){
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
            jgraphics_translate(g, 0, w*0.4);
            //-- rotated and translated
            
            // head of the mic :
            jgraphics_arc(g, 0, 0, hpSize, 0, CICM_2PI);
            jgraphics_fill(g);
            
            /*
            //body of the mic :
            jgraphics_new_path(g);
            jgraphics_move_to(g, -hpSize*0.5-1, hpSize*0.5+5);
            jgraphics_line_to(g, hpSize*0.5+1, hpSize*0.5+5);
            jgraphics_line_to(g, 2, hpSize*3);
            jgraphics_line_to(g, -2, hpSize*3);
            jgraphics_close_path(g);
            jgraphics_fill(g);
            */
            
            //-- inverse rotation and translate
            jgraphics_translate(g, 0, -w*0.4);
            jgraphics_rotate(g, -mic_angle);
		}
		jbox_end_layer((t_object*)x, view, gensym("mic_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("mic_layer"), 0., 0.);
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
        jgraphics_translate(context, 0, w*0.4);
        jgraphics_new_path(context);
        jgraphics_arc(context, 0, 0, hpSize, 0, CICM_2PI);
        jgraphics_close_path(context);
        jgraphics_translate(context, 0, -w*0.4);
        jgraphics_rotate(context, -mic_angle);
        if (jgraphics_in_fill(context, ptTranformed.x, ptTranformed.y)) {
            result = i;
            break;
        }
        
        /*
        //-- test body :
        jgraphics_rotate(context, mic_angle);
        jgraphics_translate(context, 0, w*0.4);
        jgraphics_new_path(context);
        jgraphics_move_to(context, -hpSize*0.5-1, hpSize*0.5+5);
        jgraphics_line_to(context, hpSize*0.5+1, hpSize*0.5+5);
        jgraphics_line_to(context, 2, hpSize*3);
        jgraphics_line_to(context, -2, hpSize*3);
        jgraphics_close_path(context);
        jgraphics_translate(context, 0, -w*0.4);
        jgraphics_rotate(context, -mic_angle);
        if (jgraphics_in_fill(context, ptTranformed.x, ptTranformed.y)) {
            result = i;
            break;
        }
        */
    }
    
    jgraphics_destroy(context);
    jgraphics_surface_destroy(surface);
    
    return result;
}

void draw_background(t_HoaRecomposerUI *x,  t_object *view, t_rect *rect)
{
	double w = x->rect.width;
    t_jrgba HpMarkerColor = {0.1,0.1,0.1,1};
    double hpSize;
	hpSize = (w / 20.) * 0.4;
    t_jmatrix transform;
    double mic_angle = CICM_2PI / x->f_mics->getNumberOfMics();
    
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
	
	if (g) {
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_rectangle_rounded(g, 0., 0., w, w, 6, 6);
		jgraphics_fill(g);
		
		jgraphics_set_source_jrgba(g, &x->f_colorInnerCircle);
		jgraphics_arc(g, w*0.5, w*0.5, w*0.4,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
        
        jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
        jgraphics_set_matrix(g, &transform);
        jgraphics_set_source_jrgba(g, &HpMarkerColor);
        jgraphics_set_line_width(g, 1.5);
        
        for (int i=0; i < x->f_mics->getNumberOfMics(); i++) {
            jgraphics_rotate(g, mic_angle*i);
            jgraphics_translate(g, 0, w*0.4);
            jgraphics_arc(g, 0, 0, hpSize*1.4, 0, CICM_2PI);
            jgraphics_set_source_jrgba(g, &x->f_colorInnerCircle);
            jgraphics_fill(g);
            jgraphics_translate(g, 0, -w*0.4);
            jgraphics_rotate(g, -mic_angle*i);
            
            jgraphics_rotate(g, mic_angle*i);
            jgraphics_translate(g, 0, w*0.4);
            jgraphics_move_to(g, 0, -4);
            jgraphics_line_to(g, 0, 4);
            jgraphics_set_source_jrgba(g, &HpMarkerColor);
            jgraphics_stroke(g);
            jgraphics_translate(g, 0, -w*0.4);
            jgraphics_rotate(g, -mic_angle*i);
        }
		
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
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
    // cmd   : on ajoute à la selection courante (toggle)
    // shift : on selectionne entre deux angles
    // 1 mic : 
    // 0 mic : on deselectionne tout
    
    //-- modifiers :
    //post("modifiers : %ld", modifiers);
    // 16 : rien
    // 17 : cmd
    // 18 : shift
    // 148: ctrl
    // 19 : cmd+shift
    
    x->f_last_mouseDown = pt;
    
    int isMouseDownOverAMic = -1;
    isMouseDownOverAMic = isPointOverAMic(x, &pt);
    
    if (isMouseDownOverAMic == -1 )
    {
        if (modifiers == 16) {
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
    jbox_redraw((t_jbox *)x);
}

void HoaRecomposerUI_mousedrag(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double w = x->rect.width;
    t_pt ptTranformed = {pt.x-(w*0.5), (w - pt.y)-(w*0.5)};
    double angleDrag = Tools::angle(ptTranformed.x, ptTranformed.y) - CICM_PI*0.5;
    double radiusDrag = Tools::radius(ptTranformed.x, ptTranformed.y) ;
    
    if (x->f_last_mouseDownOverMic != -1) {
        if (modifiers == 18) // shift => set wider
        {
            double radiusDelta = x->f_last_mouseDragRadius - radiusDrag;
            x->f_mics->setSelectedMicsWiderValueWithRadiusDelta(radiusDelta);
        }
        else
        {
            x->f_mics->rotateSelectedMicsWithRadian(angleDrag, x->f_last_mouseDownOverMic);
        }
    }
    
	x->f_last_mouseDrag = pt;
    x->f_last_mouseDragAngle = angleDrag;
    x->f_last_mouseDragRadius = radiusDrag;
    HoaRecomposerUI_output(x);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
    jbox_redraw((t_jbox *)x);
}

void HoaRecomposerUI_mouseup(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->f_last_mouseUp = pt;
    int isMouseUpOverAMic = -1;
    isMouseUpOverAMic = isPointOverAMic(x, &pt);
    
    x->f_last_mouseUpOverMic = isMouseUpOverAMic;
    jmouse_setcursor(patcherview, (t_object *)x, (x->f_last_mouseMoveOverMic != -1) ? JMOUSE_CURSOR_POINTINGHAND : JMOUSE_CURSOR_ARROW);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
    jbox_redraw((t_jbox *)x);    
}

void HoaRecomposerUI_mousemove(t_HoaRecomposerUI *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->f_last_mouseMoveOverMic = isPointOverAMic(x, &pt);
    x->f_last_mouseMove = pt;
    jmouse_setcursor(patcherview, (t_object *)x, (x->f_last_mouseMoveOverMic != -1) ? JMOUSE_CURSOR_POINTINGHAND : JMOUSE_CURSOR_ARROW);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("mic_layer"));
    jbox_redraw((t_jbox *)x);
}

// key intercept
long HoaRecomposerUI_key(t_HoaRecomposerUI *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{	
	//post("keycode : %ld , modifiers : %ld , textcharacter : %ld ", keycode, modifiers, textcharacter);
	
	//int locked = (int)patcherview_get_locked(patcherview);
	//post("locked : %i", locked);
	
	// cmd+a = keycode : 97 , modifiers : 1 , textcharacter : 0
	// cmd+g = keycode : 103 , modifiers : 1 , textcharacter : 0
	// cmd+shift+g = keycode : 103 , modifiers : 3 , textcharacter : 0
	// cmd+z = keycode : 122 , modifiers : 1 , textcharacter : 0
	// cmd+s = keycode : 115 , modifiers : 1 , textcharacter : 0
	// cmd+e = keycode : 120 , modifiers : 1 , textcharacter : 0
	// cmd+g = keycode : 103 , modifiers : 1 , textcharacter : 0
	
	if (keycode == 97 && modifiers == 1 && textcharacter == 0) { // cmd+a -> select all;
		//post("select all sources");
		//update_source_selection(x, -1, 1);
	}
	
	return 1;	// returns 1 if you want to filter it from the key object (otherwise return 0)
}