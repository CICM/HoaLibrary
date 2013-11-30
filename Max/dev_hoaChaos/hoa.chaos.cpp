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

#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

#define CORNERSIZE 8
#define BORDERTHICK 2

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "ext_path.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "ext_parameter.h"
}

#include "../../Sources/HoaLibrary.h"


typedef struct  _hoachaos
{
	t_jbox      j_box;
	t_rect      rect;
	t_jfont*    jfont;
    void*       f_clock;
    
	void*		f_out_sources;
    void*		f_out_groups;
    void*		f_out_infos;
    
    t_pt        f_cursor_position;
    
    t_jrgba		f_colorBackground;
    t_jrgba		f_colorBackgroundInside;
    t_jrgba     f_colorBorder;
    
    double      f_size_source;
	double		f_zoom_factor;
    
    t_atom_long f_output_mode;
    
} t_hoachaos;

t_class *hoamap_class;

// general methods
void *hoamap_new(t_symbol *s, int argc, t_atom *argv);
void hoamap_free(t_hoachaos *x);
void hoamap_tick(t_hoachaos *x);
void hoamap_getdrawparams(t_hoachaos *x, t_object *patcherview, t_jboxdrawparams *params);
void hoamap_assist(t_hoachaos *x, void *b, long m, long a, char *s);
t_max_err hoamap_notify(t_hoachaos *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err hoamap_zoom(t_hoachaos *x, t_object *attr, long argc, t_atom *argv);

void hoamap_jsave(t_hoachaos *x, t_dictionary *d);

void hoamap_doread(t_hoachaos *x, t_symbol *s, long argc, t_atom *argv);
void hoamap_dowrite(t_hoachaos *x, t_symbol *s, long argc, t_atom *argv);

/* Paint Methods */
void hoamap_paint(t_hoachaos *x, t_object *view);
void draw_background(t_hoachaos *x, t_object *view, t_rect *rect);

void hoamap_mousedown(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousedrag(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseup(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseenter(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousemove(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseleave(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousewheel(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc);
long hoamap_key(t_hoachaos *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);

int C74_EXPORT main()
{
	t_class *c;
    
	c = class_new("hoa.chaos", (method)hoamap_new, (method)hoamap_free, (short)sizeof(t_hoachaos), 0L, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method) hoamap_assist,           "assist",		A_CANT,	0);
	class_addmethod(c, (method) hoamap_paint,            "paint",		A_CANT,	0);
	class_addmethod(c, (method) hoamap_getdrawparams,    "getdrawparams",A_CANT, 0);
	class_addmethod(c, (method) hoamap_notify,           "notify",		A_CANT, 0);
    
    class_addmethod(c, (method) hoamap_jsave,            "jsave",        A_CANT, 0);
    
    class_addmethod(c, (method) hoamap_mousedown,        "mousedown",	A_CANT, 0);
    class_addmethod(c, (method) hoamap_mousedrag,        "mousedrag",	A_CANT, 0);
    class_addmethod(c, (method) hoamap_mouseup,          "mouseup",      A_CANT, 0);
    class_addmethod(c, (method) hoamap_mouseenter,       "mouseenter",   A_CANT, 0);
    class_addmethod(c, (method) hoamap_mousemove,        "mousemove",    A_CANT, 0);
    class_addmethod(c, (method) hoamap_mouseleave,       "mouseleave",   A_CANT, 0);
    class_addmethod(c, (method) hoamap_mousewheel,		 "mousewheel",	A_CANT, 0);
    class_addmethod(c, (method) hoamap_key,              "key",           A_CANT,   0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 300");
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
    
    /* Colors */
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_hoachaos, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Outside Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.9 0.9 0.9 1.");
    
    CLASS_ATTR_RGBA				(c, "bgcolor2", 0, t_hoachaos, f_colorBackgroundInside);
	CLASS_ATTR_CATEGORY			(c, "bgcolor2", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor2", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor2", 0, "Background Inside Color");
	CLASS_ATTR_ORDER			(c, "bgcolor2", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor2", 0, "0.75 0.75 0.75 1.");
    
    CLASS_ATTR_RGBA				(c, "bdcolor", 0, t_hoachaos, f_colorBorder);
	CLASS_ATTR_CATEGORY			(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bdcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bdcolor", 0, "0.5 0.5 0.5 1.");
	
    /* Behavior */
	CLASS_ATTR_LONG				(c,"outputmode", 0, t_hoachaos, f_output_mode);
	CLASS_ATTR_LABEL			(c,"outputmode", 0, "Output Mode");
	CLASS_ATTR_CATEGORY			(c,"outputmode", 0, "Behavior");
	CLASS_ATTR_ENUMINDEX		(c,"outputmode", 0, "Polar Cartesian");
	CLASS_ATTR_DEFAULT          (c,"outputmode", 0,  "0");
    CLASS_ATTR_SAVE             (c,"outputmode", 1);
    CLASS_ATTR_ORDER			(c,"outputmode", 0, "1");
    
	CLASS_ATTR_DOUBLE			(c,"zoom", 0, t_hoachaos, f_zoom_factor);
    CLASS_ATTR_ACCESSORS		(c,"zoom", NULL, hoamap_zoom);
	CLASS_ATTR_LABEL			(c,"zoom", 0,   "Zoom");
	CLASS_ATTR_CATEGORY			(c,"zoom", 0,   "Behavior");
	CLASS_ATTR_DEFAULT          (c,"zoom", 0,   "0.35");
    CLASS_ATTR_ORDER			(c,"zoom", 0,   "2");
    CLASS_ATTR_SAVE             (c,"zoom", 1);

	class_register(CLASS_BOX, c);
	hoamap_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *hoamap_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoachaos *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_hoachaos *)object_alloc(hoamap_class);
	flags = 0 
	| JBOX_DRAWFIRSTIN 
	| JBOX_DRAWINLAST
	| JBOX_TRANSPARENT
	| JBOX_DRAWBACKGROUND
	| JBOX_GROWY
	| JBOX_HILITE
	;
    
	jbox_new(&x->j_box, flags, argc, argv);
    
    x->j_box.b_firstin = (t_object*) x;
        
    x->f_out_infos      = listout(x);
    x->f_out_groups     = listout(x);
	x->f_out_sources    = listout(x);
	
    x->f_clock = clock_new(x,(method)hoamap_tick);
	x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    
	attr_dictionary_process(x, d);
    
	jbox_ready(&x->j_box);
	return (x);
}

void hoamap_free(t_hoachaos *x)
{
	jbox_free(&x->j_box);
    jfont_destroy(x->jfont);
    freeobject((t_object *)x->f_clock);
}

void hoamap_assist(t_hoachaos *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(Anything) Behavior and appearance");
	else
    {
        if(a == 0)
            sprintf(s,"(List) Sources coordinates");
        if(a == 1)
            sprintf(s,"(List) Groups coordinates");
        if(a == 2)
            sprintf(s,"(List) Infos");
    }
}

void hoamap_doread(t_hoachaos *x, t_symbol *s, long argc, t_atom *argv)
{
    ;
}

void hoamap_dowrite(t_hoachaos *x, t_symbol *sym, long argc, t_atom *argv)
{
	;
}

void hoamap_getdrawparams(t_hoachaos *x, t_object *patcherview, t_jboxdrawparams *params)
{
    params->d_boxfillcolor = x->f_colorBackground;
    params->d_bordercolor =  x->f_colorBorder;
	params->d_borderthickness = 1;
	params->d_cornersize = CORNERSIZE;
}

void hoamap_tick(t_hoachaos *x)
{
    clock_fdelay(x->f_clock, 100);
}

/**********************************************************/
/*          Intialisation par l'utilisateur               */
/**********************************************************/

void hoamap_clear_all(t_hoachaos *x)
{
    x->f_source_manager->clearAll();
    
    object_notify(x, gensym("modified"), NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}


t_max_err hoamap_zoom(t_hoachaos *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
            x->f_zoom_factor = Tools::clip(float(atom_getfloat(argv)), float(MIN_ZOOM), float(MAX_ZOOM));
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    return MAX_ERR_NONE;
}

t_max_err hoamap_notify(t_hoachaos *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
    if (msg == gensym("free"))
    {
		if (sender == x->f_patcher)
        {
			x->f_patcher = NULL;
            x->f_textfield = NULL;
            x->f_colorpicker = NULL;
        }
	}
    else if (msg == gensym("endeditbox"))
    {
        if(x->f_textfield)
            object_free(x->f_textfield);
        if(x->f_patcher)
            object_free(x->f_patcher);
    }
    else if(msg == gensym("text"))
    {
        if (sender == x->f_textfield)
        {
            if(x->f_index_of_source_to_color > -1)
            {
                x->f_source_manager->sourceSetDescription(x->f_index_of_source_to_color, (char *)data);
                jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
                object_notify(x, gensym("modified"), NULL);
            }
            else if(x->f_index_of_group_to_color > -1)
            {
                x->f_source_manager->groupSetDescription(x->f_index_of_group_to_color, (char *)data);
                jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
                object_notify(x, gensym("modified"), NULL);
            }
        }
        jbox_redraw((t_jbox *)x);
    }
	if (msg == gensym("attr_modified"))
    {
        if (sender == x->f_colorpicker)
        {
            t_atom *av = NULL;
            long    ac = 0;

            name = (t_symbol *)object_method(data, gensym("getname"));
            if(name == gensym("currentcolor"))
            {
                object_attr_getvalueof(sender, name, &ac, &av);
                if (ac && av)
                {
                    if(x->f_index_of_source_to_color > -1)
                    {
                        x->f_source_manager->sourceSetColor(x->f_index_of_source_to_color, atom_getfloat(av), atom_getfloat(av+1), atom_getfloat(av+2), atom_getfloat(av+3));
                        jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
                        object_notify(x, gensym("modified"), NULL);
                    }
                    else if(x->f_index_of_group_to_color > -1)
                    {
                        x->f_source_manager->groupSetColor(x->f_index_of_group_to_color, atom_getfloat(av), atom_getfloat(av+1), atom_getfloat(av+2), atom_getfloat(av+3));
                        jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
                        object_notify(x, gensym("modified"), NULL);
                    }
                    else if(x->f_index_of_source_to_color == -2)
                    {
                        x->f_colorBackground.red = atom_getfloat(av);
                        x->f_colorBackground.green = atom_getfloat(av+1);
                        x->f_colorBackground.blue = atom_getfloat(av+2);
                        x->f_colorBackground.alpha = atom_getfloat(av+3);
                        jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
                        object_notify(x, gensym("modified"), NULL);
                    }
                    
                }
            }
        }
        else
        {
            name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
            if(name == gensym("bgcolor") || name == gensym("bgcolor2") )
            {
                jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
            }
            else if(name == gensym("fontname") || name == gensym("fontface") || name == gensym("fontsize"))
            {
                jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
                jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
            }
            else if(name == gensym("zoom"))
            {
                jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
                jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
                jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
            }
        }
        jbox_redraw((t_jbox *)x);
    }
        
            
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

/**********************************************************/
/*                          Sortie                        */
/**********************************************************/

void hoamap_bang(t_hoachaos *x)
{
    t_atom av[4];
    atom_setsym(av+1, gensym("mute"));
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(av, i);
            atom_setlong(av+2, x->f_source_manager->sourceGetMute(i));
            outlet_list(x->f_out_sources, 0L, 3, av);
        }
    }
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(av, i);
            atom_setfloat(av+2, x->f_source_manager->groupGetMute(i));
            outlet_list(x->f_out_groups, 0L, 4, av);
        }
    }
    if(x->f_output_mode == 0)
    {
        atom_setsym(av+1, gensym("polar"));
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2, x->f_source_manager->sourceGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->sourceGetAngle(i));
                outlet_list(x->f_out_sources, 0L, 4, av);
            }
        }
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2, x->f_source_manager->groupGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->groupGetAngle(i));
                outlet_list(x->f_out_groups, 0L, 4, av);
            }
        }
        
    }
    else
    {
        atom_setsym(av+1, gensym("cartesian"));
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2,x->f_source_manager->sourceGetAbscissa(i));
                atom_setfloat(av+3,x->f_source_manager->sourceGetOrdinate(i));
                outlet_list(x->f_out_sources, 0L, 4, av);
            }
        }
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2, x->f_source_manager->groupGetAbscissa(i));
                atom_setfloat(av+3, x->f_source_manager->groupGetOrdinate(i));
                outlet_list(x->f_out_groups, 0L, 4, av);
            }
        }
    }
}

void hoamap_infos(t_hoachaos *x)
{
    t_atom avNumber[3];
    t_atom* avIndex;
    t_atom* avSource;
    t_atom avMute[4];
    
    /* Sources */
    long numberOfSource = 0;
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        
        if(x->f_source_manager->sourceGetExistence(i))
        {
            numberOfSource++;
        }
    }
    atom_setsym(avNumber, gensym("source"));
    atom_setsym(avNumber+1, gensym("number"));
    atom_setlong(avNumber+2, numberOfSource);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);
    
    avIndex = new t_atom[numberOfSource+2];
    atom_setsym(avIndex, gensym("source"));
    atom_setsym(avIndex+1, gensym("index"));
    for(int i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(avIndex+j+2, i);
            j++;
        }
    }
    outlet_list(x->f_out_infos, 0L, numberOfSource+2, avIndex);
    free(avIndex);
    
    atom_setsym(avMute, gensym("source"));
    atom_setsym(avMute+1, gensym("mute"));
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(avMute+2, i);
            atom_setlong(avMute+3, x->f_source_manager->sourceGetMute(i));
            outlet_list(x->f_out_infos, 0L, 4, avMute);
        }
    }
    
    /* Groups */
    long numberOfGroups = 0;
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            numberOfGroups++;
        }
    }
    atom_setsym(avNumber, gensym("group"));
    atom_setsym(avNumber+1, gensym("number"));
    atom_setlong(avNumber+2, numberOfGroups);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);
    
    avIndex = new t_atom[numberOfGroups+2];
    atom_setsym(avIndex, gensym("group"));
    atom_setsym(avIndex+1, gensym("index"));
    for(int i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(avIndex+j+2, i);
            j++;
            avSource = new t_atom[x->f_source_manager->groupGetNumberOfSources(i)+3];
            atom_setsym(avSource, gensym("group"));
            atom_setsym(avSource+1, gensym("source"));
            atom_setlong(avSource+2, i);
            for(int k = 0; k < x->f_source_manager->groupGetNumberOfSources(i); k++)
            {
                atom_setlong(avSource+3+k,x->f_source_manager->groupGetSourceIndex(i, k));
            }
            outlet_list(x->f_out_infos, 0L, x->f_source_manager->groupGetNumberOfSources(i)+3, avSource);
            free(avSource);
        }
    }
    outlet_list(x->f_out_infos, 0L, numberOfGroups+2, avIndex);
    free(avIndex);
    
    atom_setsym(avMute, gensym("group"));
    atom_setsym(avMute+1, gensym("mute"));
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(avMute+2, i);
            atom_setlong(avMute+3, x->f_source_manager->groupGetMute(i));
            outlet_list(x->f_out_infos, 0L, 4, avMute);
        }
    }

    /* Slots */
    long numberOfSlots = 0;
    for(int i = 0; i <= x->f_source_preset->getMaximumIndexOfSlot(); i++)
    {
        if(x->f_source_preset->getSlotExistence(i))
        {
            numberOfSlots++;
        }
    }
    atom_setsym(avNumber, gensym("slot"));
    atom_setsym(avNumber+1, gensym("number"));
    atom_setlong(avNumber+2, numberOfSlots);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);

    avIndex = new t_atom[numberOfSlots+2];
    atom_setsym(avIndex, gensym("slot"));
    atom_setsym(avIndex+1, gensym("index"));
    for(int i = 0, j = 0; i <= x->f_source_preset->getMaximumIndexOfSlot(); i++)
    {
        if(x->f_source_preset->getSlotExistence(i))
        {
            atom_setlong(avIndex+j+2, i);
            j++;
        }
    }
    outlet_list(x->f_out_infos, 0L, numberOfSlots+2, avIndex);
    free(avIndex);    
}

/**********************************************************/
/*                          Paint                         */
/**********************************************************/

void hoamap_paint(t_hoachaos *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	x->rect = rect;
    
    /* Pas de groupes avec un nombre de source inférieur à 2 et pas de doublons de groupes */
    
    x->f_source_manager->groupClean();
    
	draw_background(x, view, &rect);
    draw_sources(x, view, &rect);
    draw_groups(x, view, &rect);
    draw_rect_selection(x, view, &rect);
}

void draw_background(t_hoachaos *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g, *g2, *g3;
    t_jsurface *s1, *s2;
    t_jrgba black, white;
    double w = rect->width;
    double h = rect->height;
    t_pt ctr = {w*0.5, h*0.5};
    double maxctr = Tools::cicm_max(w, h)*0.5;
    
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
    black = white = x->f_colorBackgroundInside;
    black.red = Tools::clip_min(black.red -= contrastBlack);
    black.green = Tools::clip_min(black.green -= contrastBlack);
    black.blue = Tools::clip_min(black.blue -= contrastBlack);
    white.red = Tools::clip_max(white.red += contrastWhite, 1.);
    white.green = Tools::clip_max(white.green += contrastWhite, 1.);
    white.blue = Tools::clip_max(white.blue += contrastWhite, 1.);
    
	g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), w, h);
	
	if (g)
    {
        s1 = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, int(w), int(h));
        g2 = jgraphics_create(s1);
        
        s2 = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, int(w), int(h));
        g3 = jgraphics_create(s2);
        
        jgraphics_set_source_jrgba(g3, &x->f_colorBackgroundInside);
        jgraphics_set_line_width(g3, 1);
        jgraphics_arc(g3, ctr.x, ctr.y, maxctr * (1./MIN_ZOOM * x->f_zoom_factor),  0., JGRAPHICS_2PI);
        jgraphics_fill(g3);
        
        double ecart = x->f_zoom_factor * maxctr;
        if(ecart < 10 && ecart >= 5) ecart *= 4;
        else if(ecart < 5 && ecart > 2.5) ecart *= 8;
        else if(ecart < 2.5) ecart *= 16;
        ecart = int(ecart);
        
		for(double i = 0; i < maxctr; i += ecart)
        {
            jgraphics_set_line_width(g3, 1);
            jgraphics_set_source_jrgba(g3, &white);
            jgraphics_move_to(g3, 0., long(ctr.y - i) + 0.5);
            jgraphics_line_to(g3, w,  long(ctr.y - i) + 0.5);
            jgraphics_move_to(g3, 0., long(ctr.y + i) + 0.5);
            jgraphics_line_to(g3, w,  long(ctr.y + i) + 0.5);
            jgraphics_move_to(g3, long(ctr.x - i) + 0.5, 0.);
            jgraphics_line_to(g3, long(ctr.x - i) + 0.5, w);
            jgraphics_move_to(g3, long(ctr.x + i) + 0.5, 0.);
            jgraphics_line_to(g3, long(ctr.x + i) + 0.5, w);
            jgraphics_set_line_width(g3, 1);
            jgraphics_scale(g3, 0.5, 0.5);
            jgraphics_stroke(g3);
            jgraphics_scale(g3, 2, 2);
            
            jgraphics_set_line_width(g3, 1);
            jgraphics_set_source_jrgba(g3, &black);
            jgraphics_move_to(g3, 0. - 0.5, long(ctr.y - i) - 0.5);
            jgraphics_line_to(g3, w - 0.5, long(ctr.y - i) - 0.5);
            jgraphics_move_to(g3, 0. - 0.5, long(ctr.y + i) - 0.5);
            jgraphics_line_to(g3, w - 0.5, long(ctr.y + i) - 0.5);
            jgraphics_move_to(g3, long(ctr.x - i) - 0.5, 0. - 0.5);
            jgraphics_line_to(g3, long(ctr.x - i) - 0.5, w - 0.5);
            jgraphics_move_to(g3, long(ctr.x + i) - 0.5, 0. - 0.5);
            jgraphics_line_to(g3, long(ctr.x + i) - 0.5, w - 0.5);
            jgraphics_set_line_width(g3, 2);
            jgraphics_scale(g3, 0.25, 0.25);
            jgraphics_stroke(g3);
            jgraphics_scale(g3, 4, 4);
        }
        
        /* Circles */
        double radius = x->f_zoom_factor * (maxctr*2) / 10.;
        for(int i = 5; i > 0; i--)
        {
            jgraphics_set_line_width(g3, 2);
            jgraphics_set_source_jrgba(g3, &white);
            jgraphics_arc(g3, long(ctr.x)+0.5, long(ctr.y)+0.5, (double)i * radius - 1,  0., JGRAPHICS_2PI);
            jgraphics_scale(g3, 0.5, 0.5);
            jgraphics_stroke(g3);
            jgraphics_scale(g3, 2, 2);
            
            jgraphics_set_line_width(g3, 2);
            jgraphics_set_source_jrgba(g3, &black);
            jgraphics_arc(g3, long(ctr.x) - 0.5, long(ctr.y) - 0.5, (double)i * radius - 1,  0., JGRAPHICS_2PI);
            jgraphics_scale(g3, 0.5, 0.5);
            jgraphics_stroke(g3);
            jgraphics_scale(g3, 2, 2);
        }
        
        /* clip jgraphics_3 to circle */
        jgraphics_destroy(g3);
        jgraphics_set_source_surface(g2, s2, 0, 0);
        jgraphics_surface_destroy(s2);
        jgraphics_arc(g2, ctr.x, ctr.y, maxctr * (1./MIN_ZOOM * x->f_zoom_factor) - (BORDERTHICK*2),  0., CICM_2PI);
        jgraphics_fill(g2);
        
        /* clip jgraphics_2 to rounded rect */
        jgraphics_destroy(g2);
        jgraphics_set_source_surface(g, s1, 0, 0);
        jgraphics_surface_destroy(s1);
        jgraphics_rectangle_rounded(g, 0, 0, w, h, CORNERSIZE, CORNERSIZE);
        jgraphics_fill(g);
        
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}


/**********************************************************/
/*                   Souris et clavier                    */
/**********************************************************/

void hoamap_mousedown(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    double maxwh = Tools::cicm_max(x->rect.width, x->rect.height);
    double ditanceSelected = (x->f_size_source / maxwh * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    x->f_rect_selection_exist = -1;
    x->f_rect_selection.width = x->f_rect_selection.height = 0.;
        
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
                x->f_index_of_selected_group = i;
            }
        }
    }

    if(modifiers == 160)
    {
        int posX, posY;
        t_pt pos;
        jmouse_getposition_global(&posX, &posY);
        pos.x = posX;
        pos.y = posY;
        x->f_index_of_source_to_remove = x->f_index_of_selected_source;
        x->f_index_of_group_to_remove = x->f_index_of_selected_group;
        t_jpopupmenu* popup = jpopupmenu_create();
        jpopupmenu_setfont(popup, x->jfont);
       
        if(x->f_index_of_selected_group != -1) 
        {
            x->f_index_of_group_to_color = x->f_index_of_selected_group;
            x->f_index_of_selected_group = -1;
            x->f_index_of_source_to_color = -1;
            jpopupmenu_additem(popup, 0, "Group Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Remove group", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 2, "Remove group and sources", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 3, "Mute group", NULL, 0, x->f_source_manager->groupGetMute(x->f_index_of_group_to_remove), NULL);
            jpopupmenu_additem(popup, 4, "Unmute group", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 5, "Set group color", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 6, "Set group description", NULL, 0, 0, NULL);
            
            int choice = jpopupmenu_popup(popup, pos, 0);
            switch (choice)
            {
                case 1:
                {
                    t_atom av[3];
                    atom_setlong(av, x->f_index_of_group_to_remove);
                    atom_setsym(av+1, gensym("mute"));
                    atom_setlong(av+2, 1);
                    outlet_list(x->f_out_groups, 0L, 3, av);
                    x->f_source_manager->groupRemove(x->f_index_of_group_to_remove);
                    hoamap_bang(x);
                    break;
                }
                case 2:
                {
                    t_atom av[3];
                    atom_setlong(av, x->f_index_of_group_to_remove);
                    atom_setsym(av+1, gensym("mute"));
                    atom_setlong(av+2, 1);
                    outlet_list(x->f_out_groups, 0L, 3, av);
                    x->f_source_manager->groupRemoveWithSources(x->f_index_of_group_to_remove);
                    hoamap_bang(x);
                    break;
                }
                case 3: // Mute group
                {
                    x->f_source_manager->groupSetMute(x->f_index_of_group_to_remove, 1);
                    break;
                }
                case 4: // Unmute group
                {
                    x->f_source_manager->groupSetMute(x->f_index_of_group_to_remove, 0);
                    break;
                }
                case 5: // Set group color
                {
                    hoamap_color_picker(x);
                    break;
                }
                case 6: // Set group description
                {
                    hoamap_text_field(x);
                    break;
                }
                default:
                    break;
            }
            jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
            jbox_redraw((t_jbox *)x);
            hoamap_bang(x);
        }
        else if(x->f_index_of_selected_source != -1)
        {
            x->f_index_of_source_to_color = x->f_index_of_selected_source;
            x->f_index_of_selected_source = -1;
            x->f_index_of_group_to_color = -1;
            int muted = x->f_source_manager->sourceGetMute(x->f_index_of_source_to_remove);
            jpopupmenu_additem(popup, 0, "Source Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Remove source", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 2, muted ? "Unmute source" : "Mute source", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 3, "Set source color", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 4, "Set source description", NULL, 0, 0, NULL);
            int choice = jpopupmenu_popup(popup, pos, 0);
            switch (choice)
            {
                case 1:
                {
                    t_atom av[3];
                    atom_setlong(av, x->f_index_of_source_to_remove);
                    atom_setsym(av+1, gensym("mute"));
                    atom_setlong(av+2, 1);
                    outlet_list(x->f_out_sources, 0L, 3, av);
                    x->f_source_manager->sourceRemove(x->f_index_of_source_to_remove);
                    break;
                }
                case 2:
                {
                    if(x->f_source_manager->sourceGetMute(x->f_index_of_source_to_remove))
                        x->f_source_manager->sourceSetMute(x->f_index_of_source_to_remove, 0);
                    else
                        x->f_source_manager->sourceSetMute(x->f_index_of_source_to_remove, 1);
                    break;
                }
                case 3:
                {
                    hoamap_color_picker(x);
                    break;
                }
                case 4:
                {
                    hoamap_text_field(x);
                    break;
                }
                default:
                    break;
            }
            jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
            jbox_redraw((t_jbox *)x);
            hoamap_bang(x);
        }
        else
        {
            t_jpopupmenu* subpopup = jpopupmenu_create();
            jpopupmenu_setfont(subpopup, x->jfont);
            x->f_index_of_group_to_color = -1;
            x->f_index_of_source_to_color = -2;
            jpopupmenu_additem(popup, 0, "Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Add source", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 2, "Clear all", NULL, 0, 0, NULL);
            int choice = jpopupmenu_popup(popup, pos, 0);
            int check = 0;
            switch (choice)
            {
                case 1:
                {
                    for(int i = 0; check == 0; i++)
                    {
                        if (x->f_source_manager->sourceGetExistence(i) < 1)
                        {
                            check = 1;
                            x->f_index_of_selected_source = i;
                            hoamap_mousedrag(x, patcherview, pt, modifiers);
                        }
                    }
                    break;
                }
                case 2: // Clear All
                {
                    hoamap_clear_all(x);
                    break;
                }
                default:
                    break;
            }
        }
        jpopupmenu_destroy(popup);
    }
    
    if(x->f_index_of_selected_source == -1 && x->f_index_of_selected_group == -1)
    {
        x->f_rect_selection.x = pt.x;
        x->f_rect_selection.y = pt.y;
        x->f_rect_selection_exist = 1;
    }
    
    if(x->f_source_trajectory->getRecording())
        clock_set(x->f_clock, 20);
}


void hoamap_mousedrag(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    
    t_pt mousedelta = {x->f_cursor_position.x - cursor.x, x->f_cursor_position.y - cursor.y};
	
	if (x->f_index_of_selected_source != -1)
    {
		// Angle
#ifdef _WINDOWS
		if(modifiers == 24) // Alt
#else
		if(modifiers == 148 || modifiers == 404)
#endif
			x->f_source_manager->sourceSetAngle(x->f_index_of_selected_source, Tools::angle(cursor.x, cursor.y) - CICM_PI2);

		 // Radius
#ifdef _WINDOWS
		else if(modifiers == 18) // Shift
#else
		else if(modifiers == 18 || modifiers == 274)
#endif
            x->f_source_manager->sourceSetRadius(x->f_index_of_selected_source, Tools::radius(cursor.x, cursor.y));
		 // Angle + radius
#ifdef _WINDOWS
		else if(modifiers == 26) // Shift
#else
		else if (modifiers == 17)
#endif
        {
            if (fabs(mousedelta.x) >= fabs(mousedelta.y))
            {
                x->f_source_manager->sourceSetAbscissa(x->f_index_of_selected_source, cursor.x);
            }
            else
                x->f_source_manager->sourceSetOrdinate(x->f_index_of_selected_source, cursor.y);
          
        }
        else
            x->f_source_manager->sourceSetCartesian(x->f_index_of_selected_source, cursor.x, cursor.y);
    }
    else if (x->f_index_of_selected_group != -1)
    {

		// Angle
#ifdef _WINDOWS
		if(modifiers == 24) // Alt
#else
		if(modifiers == 148 || modifiers == 404)
#endif
            x->f_source_manager->groupSetRelativeAngle(x->f_index_of_selected_group, Tools::angle(cursor.x, cursor.y));
		 // Radius
#ifdef _WINDOWS
		else if(modifiers == 18) // Shift
#else
		else if(modifiers == 18 || modifiers == 274)
#endif
            x->f_source_manager->groupSetRelativeRadius(x->f_index_of_selected_group, Tools::radius(cursor.x, cursor.y));
		 // Angle + radius
#ifdef _WINDOWS
		else if(modifiers == 26) // Shift
#else
		else if (modifiers == 17)
#endif
            x->f_source_manager->groupSetRelativePolar(x->f_index_of_selected_group, Tools::radius(cursor.x, cursor.y), Tools::angle(cursor.x, cursor.y));
        else
            x->f_source_manager->groupSetCartesian(x->f_index_of_selected_group, cursor.x, cursor.y);            
    }
    else
    {
		x->f_rect_selection.width = pt.x - x->f_rect_selection.x;
		x->f_rect_selection.height = pt.y - x->f_rect_selection.y;
		jbox_invalidate_layer((t_object *)x, NULL, gensym("rect_selection_layer"));
		jbox_redraw((t_jbox *)x);
    }
    
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    object_notify(x, gensym("modified"), NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

void hoamap_mouseup(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if(x->f_source_trajectory)
        clock_unset(x->f_clock);
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    if(x->f_rect_selection_exist)
    {
        int indexOfNewGroup = -1;
        for(int i = 0; indexOfNewGroup == -1; i++)
        {
            if (x->f_source_manager->groupGetExistence(i) == 0)
            {
                indexOfNewGroup = i;
            }
        }
    
        double x1 = ((x->f_rect_selection.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
        double x2 = (((x->f_rect_selection.x + x->f_rect_selection.width) / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
        double y1 = ((-x->f_rect_selection.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
        double y2 = (((-x->f_rect_selection.y - x->f_rect_selection.height) / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
        
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i) && indexOfNewGroup >= 0)
            {
                double abscissaOfSource = x->f_source_manager->sourceGetAbscissa(i);
                double ordinateOfSource = x->f_source_manager->sourceGetOrdinate(i);
                                
                if(((abscissaOfSource > x1 && abscissaOfSource < x2) || (abscissaOfSource < x1 && abscissaOfSource > x2)) && ((ordinateOfSource > y1 && ordinateOfSource < y2) || (ordinateOfSource < y1 && ordinateOfSource > y2)))
                {
                    x->f_source_manager->groupSetSource(indexOfNewGroup, i);
                    x->f_index_of_selected_group = indexOfNewGroup;
                }
            }
        }
    }
    
    x->f_rect_selection_exist = x->f_rect_selection.width = x->f_rect_selection.height = 0;
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("rect_selection_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoamap_mousewheel(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	if (modifiers == eAltKey)
    {
		double newZoom = x->f_zoom_factor + y_inc / 100.;
        x->f_zoom_factor = Tools::clip(newZoom, MIN_ZOOM, MAX_ZOOM);
        object_notify(x, gensym("modified"), NULL);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
        jbox_redraw((t_jbox *)x);
	}
}

void hoamap_mouseenter(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void hoamap_mousemove(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    double maxwh = Tools::cicm_max(x->rect.width, x->rect.height);
    double ditanceSelected = (x->f_size_source / maxwh * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
                x->f_index_of_selected_group = i;
            }
        }
    }
    
    if(x->f_index_of_selected_group >= 0 || x->f_index_of_selected_source >= 0)
        jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_POINTINGHAND);
    else jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_ARROW);
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoamap_mouseleave(t_hoachaos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

long hoamap_key(t_hoachaos *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
    int filter = 0;

#ifdef _WINDOWS
	if (keycode == 97 && modifiers == 5 && textcharacter == 1) // Control + a
#else
	if (keycode == 97 && modifiers == 1 && textcharacter == 0) //cmd+a
#endif
    {
		int indexOfNewGroup = -1;
        for(int i = 0; indexOfNewGroup == -1; i++)
        {
            if (x->f_source_manager->groupGetExistence(i) == 0)
            {
                indexOfNewGroup = i;
            }
        }
        
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i) && indexOfNewGroup >= 0)
            {
                x->f_source_manager->groupSetSource(indexOfNewGroup, i);
                x->f_index_of_selected_group = indexOfNewGroup;
            }
        }
        
        jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
        jbox_redraw((t_jbox *)x);
        
        filter = 1;
	}
	return filter;
}



