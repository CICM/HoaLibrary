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

#include "cicmTools.h"
#include "AmbisonicSourcesManager.h"
#include "AmbisonicSourcesTajectory.h"

#define MAX_SOURCES 16
#define MAX_GROUP 16
#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

extern "C"
{
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "commonsyms.h"
#include "ext_parameter.h"
}

typedef struct _textfield {
	t_jbox				j_box;
    t_object*           j_patcher;
    t_object*           j_patcherview;
    t_jfont*        jfont;
} t_textfield;

void hoa_textfield_init(void);
t_textfield* textfield_new(t_symbol *s, short argc, t_atom *argv);
void textfield_free(t_textfield *x);
void textfield_select(t_textfield *x);
void textfield_doselect(t_textfield *x);
void textfield_paint(t_textfield *x, t_object *view);
long textfield_key(t_textfield *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long textfield_keyfilter(t_textfield *x, t_object *patcherview, long *keycode, long *modifiers, long *textcharacter);
void textfield_enter(t_textfield *x);
t_max_err textfield_notify(t_textfield *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

static t_class *s_textfield_class = NULL;


typedef struct  _hoamap
{
	t_jbox          j_box;
	t_rect          rect;
	t_jfont*        jfont;
    long		f_output_mode;
	void*		f_out_sources;
    void*		f_out_groups;
    
    t_object*   f_patcher;
    t_object*   f_colorpicker;
    t_object*   f_textfield;
    
    SourcesManager*     f_source_manager;
    SourcesTrajectory*  f_source_trajectory;
    
    t_pt        f_cursor_position;
    long        f_index_of_selected_source;
    long        f_index_of_selected_group;
    long        f_index_of_source_to_remove;
    long        f_index_of_group_to_remove;
    long        f_index_of_source_to_color;
    long        f_index_of_group_to_color;
    
    t_jrgba		f_source_colorBackground;
    t_jrgba		f_source_colorBackgroundInside;
    double      f_size_source;
	double		f_zoom_factor;
    
    t_rect		f_rect_selection;
	int			f_rect_selection_exist;
    
    long        f_parameters;
} t_hoamap;

t_class *hoamap_class;

// general methods
void *hoamap_new(t_symbol *s, int argc, t_atom *argv);
void hoamap_free(t_hoamap *x);
void hoamap_tick(t_hoamap *x);
void hoamap_getdrawparams(t_hoamap *x, t_object *patcherview, t_jboxdrawparams *params);
void hoamap_assist(t_hoamap *x, void *b, long m, long a, char *s);
t_max_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err hoamap_zoom(t_hoamap *x, t_object *attr, long argc, t_atom *argv);

t_max_err hoamap_setvalueof(t_hoamap *x, long ac, t_atom *av);
t_max_err hoamap_getvalueof(t_hoamap *x, long *ac, t_atom **av);
void hoamap_parameters(t_hoamap *x, short ac, t_atom *av);
void hoamap_jsave(t_hoamap *x, t_dictionary *d);
void hoamap_doread(t_hoamap *x, t_symbol *s);
void hoamap_spool(t_hoamap *x, t_symbol *s);
void hoamap_read(t_hoamap *x, t_symbol *s);

void hoamap_source(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_group(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_slot(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_bang(t_hoamap *x);
void hoamap_color_picker(t_hoamap *x);
void hoamap_text_field(t_hoamap *x);

/* Paint Methods */
void hoamap_paint(t_hoamap *x, t_object *view);
void draw_background(t_hoamap *x, t_object *view, t_rect *rect);
void draw_sources(t_hoamap *x,  t_object *view, t_rect *rect);
void draw_groups(t_hoamap *x,  t_object *view, t_rect *rect);
void draw_rect_selection(t_hoamap *x,  t_object *view, t_rect *rect);

void hoamap_mousedown(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousedrag(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseup(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousewheel(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc);

int main()
{
    common_symbols_init();
    hoa_textfield_init();
	t_class *c;
    
    
	c = class_new("hoa.ease", (method)hoamap_new, (method)hoamap_free, (short)sizeof(t_hoamap), 0L, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method)hoamap_assist,           "assist",		A_CANT,	0);
	class_addmethod(c, (method)hoamap_paint,            "paint",		A_CANT,	0);
	class_addmethod(c, (method)hoamap_getdrawparams,    "getdrawparams",A_CANT, 0);
	class_addmethod(c, (method)hoamap_notify,           "notify",		A_CANT, 0);
    
    class_addmethod(c, (method)hoamap_getvalueof,       "getvalueof",   A_CANT, 0);
	class_addmethod(c, (method)hoamap_setvalueof,       "setvalueof",   A_CANT, 0);
    class_addmethod(c, (method)hoamap_jsave,            "jsave",        A_CANT, 0);
    //class_addmethod(c, (method)hoamap_read,             "read",         A_DEFSYM,0);
    
    class_addmethod(c, (method)hoamap_bang,             "bang",			A_CANT, 0);
    class_addmethod(c, (method)hoamap_source,           "source",       A_GIMME,0);
    class_addmethod(c, (method)hoamap_group,            "group",        A_GIMME,0);
    class_addmethod(c, (method)hoamap_slot,             "slot",         A_GIMME,0);
    
    class_addmethod(c, (method)hoamap_mousedown,        "mousedown",	A_CANT, 0);
    class_addmethod(c, (method)hoamap_mousedrag,        "mousedrag",	A_CANT, 0);
    class_addmethod(c, (method)hoamap_mouseup,          "mouseup",      A_CANT, 0);
    class_addmethod(c, (method)hoamap_mouseenter,       "mouseenter",   A_CANT, 0);
    class_addmethod(c, (method)hoamap_mousemove,        "mousemove",    A_CANT, 0);
    class_addmethod(c, (method)hoamap_mouseleave,       "mouseleave",   A_CANT, 0);
    class_addmethod(c, (method)hoamap_mousewheel,		"mousewheel",	A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 300");
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
    
    /* Colors */
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_hoamap, f_source_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Outside Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0. 0. 0. .2");
    
    CLASS_ATTR_RGBA				(c, "bgcolor2", 0, t_hoamap, f_source_colorBackgroundInside);
	CLASS_ATTR_CATEGORY			(c, "bgcolor2", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor2", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor2", 0, "Background Inside Color");
	CLASS_ATTR_ORDER			(c, "bgcolor2", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor2", 0, "1. 1. 1. 1.");
	
    /* Behavior */
	CLASS_ATTR_LONG				(c,"outputmode", 0, t_hoamap, f_output_mode);
	CLASS_ATTR_LABEL			(c,"outputmode", 0, "Output Mode");
	CLASS_ATTR_CATEGORY			(c,"outputmode", 0, "Behavior");
	CLASS_ATTR_ENUMINDEX		(c,"outputmode", 0, "Polar Cartesian");
	CLASS_ATTR_DEFAULT          (c,"outputmode", 0,  "0");
    CLASS_ATTR_SAVE             (c,"outputmode", 1);
    
	CLASS_ATTR_DOUBLE			(c,"zoom", 0, t_hoamap, f_zoom_factor);
    CLASS_ATTR_ACCESSORS		(c,"zoom", NULL, hoamap_zoom);
	CLASS_ATTR_LABEL			(c,"zoom", 0,   "Zoom");
	CLASS_ATTR_CATEGORY			(c,"zoom", 0,   "Custom");
	CLASS_ATTR_DEFAULT          (c,"zoom", 0,   "0.35");
    CLASS_ATTR_SAVE             (c,"zoom", 1);
	
	class_register(CLASS_BOX, c);
	hoamap_class = c;
	
	class_findbyname(CLASS_BOX, gensym("hoa.encoder~"));
	return 0;
}

void *hoamap_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoamap *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_hoamap *)object_alloc(hoamap_class);
	flags = 0 
	| JBOX_DRAWFIRSTIN 
	| JBOX_DRAWINLAST
	| JBOX_TRANSPARENT	
	| JBOX_GROWY
	| JBOX_HILITE
	;
	jbox_new(&x->j_box, flags, argc, argv);
	x->f_source_manager = new SourcesManager(1./MIN_ZOOM - 5.);
    x->f_source_trajectory = new SourcesTrajectory();
    
    x->f_rect_selection_exist = 0;
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    x->j_box.b_firstin = (t_object*) x;
    x->f_out_groups = listout(x);
	x->f_out_sources   = listout(x);
	
	x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));

    x->f_patcher = NULL;
    x->f_colorpicker = NULL;
    
	attr_dictionary_process(x, d);
    t_atom *av = NULL;
    long ac = 0;
    
    dictionary_copyatoms(d, gensym("sources_parameters"), &ac, &av);
    hoamap_parameters(x, ac, av);
    if (av && ac)
    {
        ac = 0;
        sysmem_freeptr(av);
    }
    dictionary_copyatoms(d, gensym("groups_parameters"), &ac, &av);
    hoamap_parameters(x, ac, av);
    if (av && ac)
    {
        ac = 0;
        sysmem_freeptr(av);
    }
    
	jbox_ready(&x->j_box);
	return (x);
}

void hoamap_tick(t_hoamap *x)
{
    ;
}

void hoamap_getdrawparams(t_hoamap *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = 1;
	params->d_cornersize = 6;
}

void hoamap_free(t_hoamap *x)
{
	jbox_free(&x->j_box);
    jfont_destroy(x->jfont);
    delete x->f_source_manager;
    if(x->f_patcher)
        object_free(x->f_patcher);
    if(x->f_colorpicker )
        object_free(x->f_colorpicker);
    if(x->f_textfield)
         object_free(x->f_textfield);
}

void hoamap_assist(t_hoamap *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(Anything) Behavior and appearance");
	else
    {
        if(a == 0)
            sprintf(s,"(List) Sources coordinates");
        if(a == 1)
            sprintf(s,"(List) Groups coordinates");
    }
}

/**********************************************************/
/*          Intialisation par l'utilisateur               */
/**********************************************************/

void hoamap_source(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && atom_gettype(av)==A_LONG && atom_getlong(av)>=0 && atom_gettype(av+1) == A_SYM)
    {
        if(atom_getsym(av+1) == gensym("polar") || atom_getsym(av+1) == gensym("pol"))
            x->f_source_manager->sourceSetPolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("radius"))
            x->f_source_manager->sourceSetRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("angle"))
            x->f_source_manager->sourceSetAngle(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("cartesian") || atom_getsym(av+1) == gensym("car"))
            x->f_source_manager->sourceSetCartesian(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("abscissa"))
            x->f_source_manager->sourceSetAbscissa(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("ordinate"))
            x->f_source_manager->sourceSetOrdinate(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("remove"))
        {
             x->f_source_manager->sourceRemove(atom_getlong(av));
            t_atom av[3];
            atom_setlong(av, atom_getlong(av));
            atom_setsym(av+1, gensym("mute"));
            atom_setlong(av+2, 1);
            outlet_list(x->f_out_sources, 0L, 3, av);
        }
        else if(atom_getsym(av+1) == gensym("mute"))
            x->f_source_manager->sourceSetMute(atom_getlong(av), atom_getlong(av+2));
        else if(atom_getsym(av+1) == gensym("description"))
        {
            char description[250];
            char number[250];
            if(atom_gettype(av+1) == A_SYM)
            {
                strcpy(description, atom_getsym(av+2)->s_name);
                strcat(description, " ");
                if(atom_getsym(av+2) == gensym("remove"))
                {
                    x->f_source_manager->sourceSetDescription(atom_getlong(av), "");
                    object_notify(x, _sym_modified, NULL);
                    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
                    jbox_redraw((t_jbox *)x);
                    return;
                }
            }
            for(int i = 3; i < ac; i++)
            {
                if(atom_gettype(av+i) == A_SYM)
                {
                    strcat(description, atom_getsym(av+i)->s_name);
                    strcat(description, " ");
                }
                else if(atom_gettype(av+i) == A_LONG)
                {
                    sprintf(number, "%ld ", atom_getlong(av+i));
                    strcat(description, number);
                }
                else if(atom_gettype(av+i) == A_FLOAT)
                {
                    sprintf(number, "%f ", atom_getfloat(av+i));
                    strcat(description, number);
                }
            }
            x->f_source_manager->sourceSetDescription(atom_getlong(av), description);
        }
        else if(atom_getsym(av+1) == gensym("color"))
        {
            x->f_source_manager->sourceSetColor(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3), atom_getfloat(av+4), atom_getfloat(av+5));
        }
        
    }
    object_notify(x, _sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

void hoamap_group(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && atom_gettype(av) == A_LONG && atom_getlong(av) >= 0 && atom_gettype(av+1) == A_SYM)
    {
        if(atom_getsym(av+1) == gensym("set"))
        {
            x->f_source_manager->groupRemove(atom_getlong(av));
            for(int i = 2; i < ac; i++)
            {
                x->f_source_manager->groupSetSource(atom_getlong(av), atom_getlong(av+i));
            }
        }        
        else if(atom_getsym(av+1) == gensym("polar") || atom_getsym(av+1) == gensym("pol"))
            x->f_source_manager->groupSetPolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("radius"))
            x->f_source_manager->groupSetRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("angle"))
            x->f_source_manager->groupSetAngle(atom_getlong(av), atom_getfloat(av+2) + CICM_PI2);
        else if(atom_getsym(av+1) == gensym("cartesian") || atom_getsym(av+1) == gensym("car"))
            x->f_source_manager->groupSetCartesian(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("abscissa"))
            x->f_source_manager->groupSetAbscissa(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("ordinate"))
            x->f_source_manager->groupSetOrdinate(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("relpolar") || atom_getsym(av+1) == gensym("relativepolar"))
            x->f_source_manager->groupSetRelativePolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == gensym("relradius") || atom_getsym(av+1) == gensym("relativeradius"))
            x->f_source_manager->groupSetRelativeRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == gensym("relangle") || atom_getsym(av+1) == gensym("relativeangle"))
            x->f_source_manager->groupSetRelativeAngle(atom_getlong(av), atom_getfloat(av+2) + CICM_PI2);
        else if(atom_getsym(av+1) == gensym("mute"))
            x->f_source_manager->groupSetMute(atom_getlong(av), atom_getlong(av+2));
        else if(atom_getsym(av+1) == gensym("remove"))
        {
            x->f_source_manager->groupRemove(atom_getlong(av));
            t_atom av[3];
            atom_setlong(av, atom_getlong(av));
            atom_setsym(av+1, gensym("mute"));
            atom_setlong(av+2, 1);
            outlet_list(x->f_out_groups, 0L, 3, av);
        }
        else if(atom_getsym(av+1) == gensym("description"))
        {
            char description[250];
            char number[250];
            if(atom_gettype(av+1) == A_SYM)
            {
                strcpy(description, atom_getsym(av+2)->s_name);
                strcat(description, " ");
                if(atom_getsym(av+2) == gensym("remove"))
                {
                    x->f_source_manager->groupSetDescription(atom_getlong(av), "");
                    object_notify(x, _sym_modified, NULL);
                    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
                    jbox_redraw((t_jbox *)x);
                    return;
                }
            }
            for(int i = 3; i < ac; i++)
            {
                if(atom_gettype(av+i) == A_SYM)
                {
                    strcat(description, atom_getsym(av+i)->s_name);
                    strcat(description, " ");
                }
                else if(atom_gettype(av+i) == A_LONG)
                {
                    sprintf(number, "%ld ", atom_getlong(av+i));
                    strcat(description, number);
                }
                else if(atom_gettype(av+i) == A_FLOAT)
                {
                    sprintf(number, "%f ", atom_getfloat(av+i));
                    strcat(description, number);
                }
            }
            x->f_source_manager->groupSetDescription(atom_getlong(av), description);
        }
        else if(atom_getsym(av+1) == gensym("color"))
        {
            x->f_source_manager->groupSetColor(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3), atom_getfloat(av+4), atom_getfloat(av+5));
        }
    }
    
    object_notify(x, _sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);    
}

void hoamap_slot(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av)
    {
        if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("store"))
            x->f_source_trajectory->storeSlot(x->f_source_manager, atom_getlong(av+1));
        else if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("insert"))
            x->f_source_trajectory->insertSlot(x->f_source_manager, atom_getlong(av+1));
        else if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("remove"))
            x->f_source_trajectory->removeSlot(atom_getlong(av+1));
        else if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("delete"))
            x->f_source_trajectory->deleteSlot(atom_getlong(av+1));
        else if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("copy"))
            x->f_source_trajectory->copySlot(atom_getlong(av+1), atom_getlong(av+2));
        else if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("renumber"))
            x->f_source_trajectory->renumber();
        else if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("clear"))
            x->f_source_trajectory->clear();
        else if(atom_gettype(av) == A_SYM && atom_getsym(av) == gensym("recall"))
            x->f_source_trajectory->recallSlot(x->f_source_manager, atom_getlong(av+1), atom_getlong(av+2), (double)atom_getfloat(av+3));
        else if(atom_gettype(av) == A_LONG)
            x->f_source_trajectory->recallSlot(x->f_source_manager, atom_getlong(av));
        else if(atom_gettype(av) == A_FLOAT)
            x->f_source_trajectory->recallFractionalSlot(x->f_source_manager, (double)atom_getfloat(av));
    }
    
    for(int i = 0; i < x->f_source_trajectory->getMaximumIndexOfSlot(); i++)
    {
        if(x->f_source_trajectory->getSlotExistence(i))
            post("slot %ld", i);
    }
    object_notify(x, _sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

/**********************************************************/
/*                  Preset et Pattr                       */
/**********************************************************/

void hoamap_jsave(t_hoamap *x, t_dictionary *d)
{
    t_atom *av;
    long ac = x->f_source_manager->getNumberOfSources()*10;
    av = new t_atom[ac];
    for(long i = 0, j = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setsym(av+j, gensym("source"));
            atom_setlong(av+j+1, i);
            atom_setfloat(av+j+2, x->f_source_manager->sourceGetAbscissa(i));
            atom_setfloat(av+j+3, x->f_source_manager->sourceGetOrdinate(i));
            atom_setlong(av+j+4, x->f_source_manager->groupGetMute(i));
            atom_setfloat(av+j+5, x->f_source_manager->sourceGetColor(i).red);
            atom_setfloat(av+j+6, x->f_source_manager->sourceGetColor(i).green);
            atom_setfloat(av+j+7, x->f_source_manager->sourceGetColor(i).blue);
            atom_setfloat(av+j+8, x->f_source_manager->sourceGetColor(i).alpha);
            atom_setsym(av+j+9, gensym(x->f_source_manager->sourceGetDescription(i).c_str()));
            
            j += 10;
        }
    }
    dictionary_appendatoms(d, gensym("sources_parameters"), ac, av);
    
    free(av);
    ac = 0;
    for(long i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            ac += x->f_source_manager->groupGetNumberOfSources(i) + 9;
        }
    }
    av = new t_atom[ac];
    for(long i = 0, j = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            long numberOfsource = x->f_source_manager->groupGetNumberOfSources(i);
            atom_setsym(av+j, gensym("group"));
            atom_setlong(av+j+1, i);
            atom_setlong(av+j+2, numberOfsource);
            for (long k = 0; k < numberOfsource; k++)
            {
                atom_setlong(av+j+k+3, x->f_source_manager->groupGetSourceIndex(i, k));
            }
            atom_setlong(av+j+numberOfsource+3, x->f_source_manager->groupGetMute(i));
            atom_setfloat(av+j+numberOfsource+4, x->f_source_manager->groupGetColor(i).red);
            atom_setfloat(av+j+numberOfsource+5, x->f_source_manager->groupGetColor(i).green);
            atom_setfloat(av+j+numberOfsource+6, x->f_source_manager->groupGetColor(i).blue);
            atom_setfloat(av+j+numberOfsource+7, x->f_source_manager->groupGetColor(i).alpha);
            atom_setsym(av+j+numberOfsource+8, gensym(x->f_source_manager->groupGetDescription(i).c_str()));
            
            j += x->f_source_manager->groupGetNumberOfSources(i) + 9;
        }
    }
    dictionary_appendatoms(d, gensym("groups_parameters"), ac, av);
    free(av);
}

void hoamap_parameters(t_hoamap *x, short ac, t_atom *av)
{
    if(ac && av)
    {
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == gensym("source")) 
            {
                x->f_source_manager->sourceSetCartesian(atom_getlong(av+i+1), atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                x->f_source_manager->sourceSetMute(atom_getlong(av+i+1), atom_getlong(av+i+4));
                x->f_source_manager->sourceSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                x->f_source_manager->sourceSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+9)->s_name);
                i += 8;
            }
            else if(atom_getsym(av+i) == gensym("group"))
            {
                long numberOfsource = atom_getlong(av+i+2);
                for (int j = 0; j < numberOfsource; j++)
                {
                    x->f_source_manager->groupSetSource(atom_getlong(av+i+1), atom_getlong(av+i+3+j));
                }
                if(atom_getlong(av+i+3+numberOfsource) == 1)
                    x->f_source_manager->groupSetMute(atom_getlong(av+i+1), 1);
                x->f_source_manager->groupSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+4+numberOfsource), atom_getfloat(av+i+5+numberOfsource), atom_getfloat(av+i+6+numberOfsource), atom_getfloat(av+i+7+numberOfsource));
                x->f_source_manager->groupSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+8+numberOfsource)->s_name);
                i += numberOfsource + 7;
            }
        }
    }
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

t_max_err hoamap_setvalueof(t_hoamap *x, long ac, t_atom *av)
{
    if(ac && av)
    {
        if(atom_getsym(av) == gensym("source"))
        {
            for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
            {
                if(x->f_source_manager->sourceGetExistence(i))
                    x->f_source_manager->sourceRemove(i);
            }
            for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
            {
                if(x->f_source_manager->groupGetExistence(i))
                    x->f_source_manager->groupRemove(i);
            }
        }
        if(atom_getsym(av) == gensym("group"))
        {
            for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
            {
                if(x->f_source_manager->groupGetExistence(i))
                    x->f_source_manager->groupRemove(i);
            }
        }
    }
	hoamap_parameters(x, ac, av);
	return MAX_ERR_NONE;
}

t_max_err hoamap_getvalueof(t_hoamap *x, long *ac, t_atom **av)
{
	if (ac && av)
    {
		if (*ac && *av)
        {
            ;
        }
        else
        {
            *ac = x->f_source_manager->getNumberOfSources() * 10;
            for(long i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
            {
                if(x->f_source_manager->groupGetExistence(i))
                {
                    *ac += x->f_source_manager->groupGetNumberOfSources(i) + 9;
                }
            }
			*av = (t_atom *)getbytes(*ac  * sizeof(t_atom));
        }
        long j = 0;
        for(long i = 0; j < *ac  && i  < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setsym(*av+j, gensym("source"));
                atom_setlong(*av+j+1, i);
                atom_setfloat(*av+j+2, x->f_source_manager->sourceGetAbscissa(i));
                atom_setfloat(*av+j+3, x->f_source_manager->sourceGetOrdinate(i));
                atom_setlong(*av+j+4, x->f_source_manager->groupGetMute(i));
                atom_setfloat(*av+j+5, x->f_source_manager->sourceGetColor(i).red);
                atom_setfloat(*av+j+6, x->f_source_manager->sourceGetColor(i).green);
                atom_setfloat(*av+j+7, x->f_source_manager->sourceGetColor(i).blue);
                atom_setfloat(*av+j+8, x->f_source_manager->sourceGetColor(i).alpha);
                atom_setsym(*av+j+9, gensym(x->f_source_manager->sourceGetDescription(i).c_str()));
                
                j += 10;
            }
        }
        for(long i = 0; j < *ac && i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                long numberOfsource = x->f_source_manager->groupGetNumberOfSources(i);
                atom_setsym(*av+j, gensym("group"));
                atom_setlong(*av+j+1, i);
                atom_setlong(*av+j+2, numberOfsource);
                for (long k = 0; k < numberOfsource; k++)
                {
                    atom_setlong(*av+j+k+3, x->f_source_manager->groupGetSourceIndex(i, k));
                }
                atom_setlong(*av+j+numberOfsource+3, x->f_source_manager->groupGetMute(i));
                atom_setfloat(*av+j+numberOfsource+4, x->f_source_manager->groupGetColor(i).red);
                atom_setfloat(*av+j+numberOfsource+5, x->f_source_manager->groupGetColor(i).green);
                atom_setfloat(*av+j+numberOfsource+6, x->f_source_manager->groupGetColor(i).blue);
                atom_setfloat(*av+j+numberOfsource+7, x->f_source_manager->groupGetColor(i).alpha);
                atom_setsym(*av+j+numberOfsource+8, gensym(x->f_source_manager->groupGetDescription(i).c_str()));
                
                j += x->f_source_manager->groupGetNumberOfSources(i) + 9;
            }
        }
        
    }
	return MAX_ERR_NONE;
}

t_max_err hoamap_zoom(t_hoamap *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
            x->f_zoom_factor = Tools::clip(atom_getfloat(argv), (float)MIN_ZOOM, (float)MAX_ZOOM);
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    return MAX_ERR_NONE;
}

t_max_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
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
    else if(msg == gensym("text"))
    {
        if (sender == x->f_textfield)
        {
            if(x->f_index_of_source_to_color > -1)
            {
                x->f_source_manager->sourceSetDescription(x->f_index_of_source_to_color, (char *)data);
                jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
                object_notify(x, _sym_modified, NULL);
            }
            else if(x->f_index_of_group_to_color > -1)
            {
                x->f_source_manager->groupSetDescription(x->f_index_of_group_to_color, (char *)data);
                jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
                object_notify(x, _sym_modified, NULL);
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
                        object_notify(x, _sym_modified, NULL);
                    }
                    else if(x->f_index_of_group_to_color > -1)
                    {
                        x->f_source_manager->groupSetColor(x->f_index_of_group_to_color, atom_getfloat(av), atom_getfloat(av+1), atom_getfloat(av+2), atom_getfloat(av+3));
                        jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
                        object_notify(x, _sym_modified, NULL);
                    }
                    else if(x->f_index_of_source_to_color == -2)
                    {
                        x->f_source_colorBackground.red = atom_getfloat(av);
                        x->f_source_colorBackground.green = atom_getfloat(av+1);
                        x->f_source_colorBackground.blue = atom_getfloat(av+2);
                        x->f_source_colorBackground.alpha = atom_getfloat(av+3);
                        jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
                        object_notify(x, _sym_modified, NULL);
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

void hoamap_bang(t_hoamap *x)
{
    t_atom av[4];
    atom_setsym(av+1, gensym("mute"));
    for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i))
        {
            atom_setlong(av, i);
            atom_setlong(av+2, x->f_source_manager->sourceGetMute(i));
            outlet_list(x->f_out_sources, 0L, 3, av);
        }
    }
    for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
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
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2, x->f_source_manager->sourceGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->sourceGetAngle(i));
                outlet_list(x->f_out_sources, 0L, 4, av);
            }
        }
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
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
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av, i);
                atom_setfloat(av+2,x->f_source_manager->sourceGetAbscissa(i));
                atom_setfloat(av+3,x->f_source_manager->sourceGetOrdinate(i));
                outlet_list(x->f_out_sources, 0L, 4, av);
            }
        }
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
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

/**********************************************************/
/*                          Dessin                        */
/**********************************************************/

void hoamap_paint(t_hoamap *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	x->rect = rect;
    
    /* Pas de groupes avec un nombre de source inférieur à 2 et pas de doublons de groupes */
    for(int i = 0; i < x->f_source_manager->getNumberOfGroups(); i++)
    {
        if (x->f_source_manager->groupGetExistence(i))
        {
            if (x->f_source_manager->groupGetNumberOfSources(i) < 2)
            {
                x->f_source_manager->groupRemove(i);
            }
        }
    }
    for(int i = 0; i < x->f_source_manager->getNumberOfGroups(); i++)
    {
        if (x->f_source_manager->groupGetExistence(i))
        {
            for(int j = 0; j < x->f_source_manager->getNumberOfGroups(); j++)
            {
                if (i != j && x->f_source_manager->groupGetExistence(j))
                {
                    if(x->f_source_manager->groupGetNumberOfSources(i) == x->f_source_manager->groupGetNumberOfSources(j))
                    {
                        int check = 0;
                        for(int k = 0; k < x->f_source_manager->groupGetNumberOfSources(i); k++)
                        {
                            for(int l = 0; l < x->f_source_manager->groupGetNumberOfSources(i); l++)
                            {
                                if(x->f_source_manager->groupGetSourceIndex(i, k) == x->f_source_manager->groupGetSourceIndex(j, l))
                                    check++;
                            }
                        }
                        if(check == x->f_source_manager->groupGetNumberOfSources(j))
                            x->f_source_manager->groupRemove(j);
                    }
                }
            }
        }
    }
    
	draw_background(x, view, &rect);
    draw_sources(x, view, &rect);
    draw_groups(x, view, &rect);
    draw_rect_selection(x, view, &rect);
}

void draw_background(t_hoamap *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
	
	if (g)
    {
		t_jrgba outsideColor = x->f_source_colorBackgroundInside;
		t_jrgba insideColor = x->f_source_colorBackground;

        jgraphics_set_source_jrgba(g, &outsideColor);
        jgraphics_arc(g, rect->width / 2., rect->width / 2., (rect->width / 2.) * (1./MIN_ZOOM * x->f_zoom_factor),  0., JGRAPHICS_2PI);
        jgraphics_fill(g);
        
        jgraphics_set_source_jrgba(g, &insideColor);
        jgraphics_arc(g, rect->width / 2., rect->width / 2., (rect->width / 2.) * (1./MIN_ZOOM * x->f_zoom_factor),  0., JGRAPHICS_2PI);
        jgraphics_fill(g);
    
        /* Circles */
        double radius  = x->f_zoom_factor * rect->width / 10.;
        //radius = (int)radius;
        for(int i = 5; i > 0; i--)
        {
            
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &insideColor);
            jgraphics_arc(g, rect->width / 2 - 0.5, rect->width / 2 - 0.5, (double)i * radius,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
            
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &outsideColor);
            jgraphics_arc(g, rect->width / 2, rect->width / 2, (double)i * radius,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
         
        }
    
        double ecart = x->f_zoom_factor * rect->width / 2.;
        if(ecart < 10 && ecart >= 5)
            ecart *= 2;
        else if(ecart < 5 && ecart > 2.5)
            ecart *= 4;
        else if(ecart < 2.5)
            ecart *= 8;
        
        ecart = (int)ecart;
		for(double i = 0; i < rect->width / 2.; i += ecart)
        {
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &insideColor);
            jgraphics_move_to(g, 0. - 0.5, rect->width / 2. - i - 0.5);
            jgraphics_line_to(g, rect->width - 0.5, rect->width / 2. - i - 0.5);
            jgraphics_move_to(g, 0. - 0.5, rect->width / 2. + i - 0.5);
            jgraphics_line_to(g, rect->width - 0.5, rect->width / 2. + i - 0.5);
            jgraphics_move_to(g, rect->width / 2. - i - 0.5, 0. - 0.5);
            jgraphics_line_to(g, rect->width / 2. - i - 0.5, rect->width - 0.5);
            jgraphics_move_to(g, rect->width / 2. + i - 0.5, 0. - 0.5);
            jgraphics_line_to(g, rect->width / 2. + i - 0.5, rect->width - 0.5);
            jgraphics_set_line_width(g, 2);
            jgraphics_stroke(g);
            
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &outsideColor);
            jgraphics_move_to(g, 0., rect->width / 2. - i);
            jgraphics_line_to(g, rect->width, rect->width / 2. - i);
            jgraphics_move_to(g, 0., rect->width / 2. + i);
            jgraphics_line_to(g, rect->width, rect->width / 2. + i);
            jgraphics_move_to(g, rect->width / 2. - i, 0.);
            jgraphics_line_to(g, rect->width / 2. - i, rect->width);
            jgraphics_move_to(g, rect->width / 2. + i, 0.);
            jgraphics_line_to(g, rect->width / 2. + i, rect->width);
            jgraphics_set_line_width(g, 1);
            jgraphics_stroke(g);
        }
        jgraphics_set_source_jrgba(g, &outsideColor);
        outsideColor.alpha = 0.1;
        jgraphics_set_line_width(g, 2);
        for(int i = 0; (rect->width / 2.) * (100. * x->f_zoom_factor) + 1 + i < 1.5 * rect->width ; i++)
        {
            
            jgraphics_arc(g, rect->width / 2., rect->width / 2., (rect->width / 2.) * (1./MIN_ZOOM * x->f_zoom_factor) + 3 + i,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
        }
        jgraphics_set_source_jrgba(g, &insideColor);
        insideColor.alpha = 0.1;
        jgraphics_set_line_width(g, 1);
        jgraphics_arc(g, rect->width / 2., rect->width / 2., (rect->width / 2.) * (1./MIN_ZOOM * x->f_zoom_factor) + 1.,  0., JGRAPHICS_2PI);
        jgraphics_stroke(g);
        for(int i = 0; (rect->width / 2.) * (100. * x->f_zoom_factor) + 1 + i < 1.5 * rect->width ; i++)
        {
            jgraphics_arc(g, rect->width / 2., rect->width / 2., (rect->width / 2.) * (1./MIN_ZOOM * x->f_zoom_factor) + 2 + i,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
        }
        
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}


void draw_sources(t_hoamap *x,  t_object *view, t_rect *rect)
{
	int i;
	double fontSize;
	t_jtextlayout *jtl;
	t_jrgba sourceColor;
  
    t_jrgba selected_color = {0,0,1,0.2};
	char description[250];
	double descriptionPositionX;
    double descriptionPositionY;
	double sourcePositionX;
    double sourcePositionY;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("sources_layer"), rect->width, rect->height);
	
    x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    x->f_size_source = jbox_get_fontsize((t_object *)x) / 2.;
    fontSize = jbox_get_fontsize((t_object *)x);
	
	if (g)
    {
        jtl = jtextlayout_create();
        jgraphics_set_line_width(g, x->f_size_source * 0.2);
		for(i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                sourcePositionX = (x->f_source_manager->sourceGetAbscissa(i) * x->f_zoom_factor + 1.) * rect->width / 2.;
                sourcePositionY = (-x->f_source_manager->sourceGetOrdinate(i) * x->f_zoom_factor + 1.) * rect->width / 2.;
			
                sourceColor.red = x->f_source_manager->sourceGetColor(i).red;
                sourceColor.green = x->f_source_manager->sourceGetColor(i).green;
                sourceColor.blue = x->f_source_manager->sourceGetColor(i).blue;
                sourceColor.alpha = x->f_source_manager->sourceGetColor(i).alpha;

                
                if(x->f_source_manager->sourceGetDescription(i).c_str()[0])
                    sprintf(description,"%i : %s", i, x->f_source_manager->sourceGetDescription(i).c_str());
                else
                    sprintf(description,"%i", i);
                    
                descriptionPositionX = sourcePositionX - 2. * x->f_size_source;
                descriptionPositionY = sourcePositionY - x->f_size_source - fontSize - 1.;

                jtextlayout_settextcolor(jtl, &sourceColor);
                jtextlayout_set(jtl, description, x->jfont, descriptionPositionX, descriptionPositionY, fontSize * 10., fontSize * 2., JGRAPHICS_TEXT_JUSTIFICATION_LEFT, JGRAPHICS_TEXTLAYOUT_USEELLIPSIS);
                jtextlayout_draw(jtl, g);
			
                if (x->f_index_of_selected_source == i)
                {
                    jgraphics_set_source_jrgba(g, &selected_color);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.5,  0., JGRAPHICS_2PI);
                    jgraphics_fill(g);
                    
                    for(int index = 0; index < x->f_source_manager->sourceGetNumberOfGroups(i); index++)
                    {
                        jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                        int groupIndex = x->f_source_manager->sourceGetGroupIndex(i, index);
                        double groupPositionX = (x->f_source_manager->groupGetAbscissa(groupIndex) * x->f_zoom_factor + 1.) * rect->width / 2.;
                         double groupPositionY = (-x->f_source_manager->groupGetOrdinate(groupIndex) * x->f_zoom_factor + 1.) * rect->width / 2.;
                        jgraphics_line_to(g, groupPositionX, groupPositionY);
                        jgraphics_stroke(g);
                    }
                }
                              
                if(!x->f_source_manager->sourceGetMute(i))
                {
                    jgraphics_set_source_jrgba(g, &sourceColor); 
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 0.6,  0., JGRAPHICS_2PI);
                    jgraphics_fill(g);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., JGRAPHICS_2PI);
                    jgraphics_stroke(g);
                }
                if(x->f_source_manager->sourceGetMute(i))
                {
                    jgraphics_set_source_jrgba(g, &sourceColor);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 0.6,  0., JGRAPHICS_2PI);
                    jgraphics_fill(g);
                    t_jrgba red = {1., 0., 0., 1.};
                    jgraphics_set_source_jrgba(g, &red); 
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., JGRAPHICS_2PI);
                    jgraphics_stroke(g);
                    jgraphics_move_to(g, sourcePositionX + Tools::abscisse(x->f_size_source * 1., CICM_PI2 / 2.), sourcePositionY + Tools::ordinate(x->f_size_source * 1., CICM_PI2 / 2.));
                    jgraphics_line_to(g, sourcePositionX + Tools::abscisse(x->f_size_source * 1., CICM_PI2 * 5. / 2.), sourcePositionY + Tools::ordinate(x->f_size_source * 1., CICM_PI * 5. / 4.));
                    jgraphics_stroke(g);
                }
                
            }
        }
		jtextlayout_destroy(jtl);

		jbox_end_layer((t_object*)x, view, gensym("sources_layer"));
    }
	jbox_paint_layer((t_object *)x, view, gensym("sources_layer"), 0., 0.);
}


void draw_groups(t_hoamap *x,  t_object *view, t_rect *rect)
{
	int i;
	double fontSize;
	t_jtextlayout *jtl;
	t_jrgba sourceColor;
    
    t_jrgba selected_color = {0,0,1,0.2};
	char description[250] = {0};
	double descriptionPositionX;
    double descriptionPositionY;
	double sourcePositionX;
    double sourcePositionY;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("groups_layer"), rect->width, rect->height);
	x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    x->f_size_source = jbox_get_fontsize((t_object *)x) / 2.;
    fontSize = jbox_get_fontsize((t_object *)x);
	
	if (g)
    {
        jtl = jtextlayout_create();
        jgraphics_set_line_width(g, x->f_size_source * 0.2);
		for(i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                sourcePositionX = (x->f_source_manager->groupGetAbscissa(i) * x->f_zoom_factor + 1.) * rect->width / 2.;
                sourcePositionY = (-x->f_source_manager->groupGetOrdinate(i) * x->f_zoom_factor + 1.) * rect->width / 2.;
                
                sourceColor.red = x->f_source_manager->groupGetColor(i).red;
                sourceColor.green = x->f_source_manager->groupGetColor(i).green;
                sourceColor.blue = x->f_source_manager->groupGetColor(i).blue;
                sourceColor.alpha = x->f_source_manager->groupGetColor(i).alpha;
                
                if(x->f_source_manager->groupGetDescription(i).c_str()[0])
                    sprintf(description,"%i : %s", i, x->f_source_manager->groupGetDescription(i).c_str());
                else
                    sprintf(description,"%i", i);
    
                descriptionPositionX = sourcePositionX - 2. * x->f_size_source;
                descriptionPositionY = sourcePositionY - x->f_size_source - fontSize - 1.;
                
                jtextlayout_settextcolor(jtl, &sourceColor);
                jtextlayout_set(jtl, description, x->jfont, descriptionPositionX, descriptionPositionY, fontSize * 10., fontSize * 2., JGRAPHICS_TEXT_JUSTIFICATION_LEFT, JGRAPHICS_TEXTLAYOUT_USEELLIPSIS);
                jtextlayout_draw(jtl, g);
                
                if (x->f_index_of_selected_group == i)
                {
                    jgraphics_set_source_jrgba(g, &selected_color);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.5,  0., JGRAPHICS_2PI);
                    jgraphics_fill(g);
                    
                    for(int index = 0; index < x->f_source_manager->groupGetNumberOfSources(i); index++)
                    {
                        jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                        int groupIndex = x->f_source_manager->groupGetSourceIndex(i, index);
                        double groupPositionX = (x->f_source_manager->sourceGetAbscissa(groupIndex) * x->f_zoom_factor + 1.) * rect->width / 2.;
                        double groupPositionY = (-x->f_source_manager->sourceGetOrdinate(groupIndex) * x->f_zoom_factor + 1.) * rect->width / 2.;
                        jgraphics_line_to(g, groupPositionX, groupPositionY);
                        jgraphics_stroke(g);
                    }
                }
                jgraphics_set_source_jrgba(g, &sourceColor);
                for(int j = 1; j < 4; j += 2)
                {
                    jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                    jgraphics_line_to(g, sourcePositionX + Tools::abscisse(x->f_size_source * 1., CICM_2PI * j / 4. + CICM_PI2 / 2.), sourcePositionY + Tools::ordinate(x->f_size_source * 1., CICM_2PI * j / 4. + CICM_PI2 / 2.));
                }
                jgraphics_stroke(g);
                if(!x->f_source_manager->groupGetMute(i))
                {
                    jgraphics_set_source_jrgba(g, &sourceColor);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.,  0., JGRAPHICS_2PI);
                    jgraphics_stroke(g);
                
                    for(int j = 0; j < 2; j++)
                    {
                        jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                        jgraphics_line_to(g, sourcePositionX + Tools::abscisse(x->f_size_source * 1., CICM_2PI * j / 2. + CICM_PI2 / 2.), sourcePositionY + Tools::ordinate(x->f_size_source * 1., CICM_2PI * j / 2. + CICM_PI2 / 2.));
                    }
                }
                jgraphics_stroke(g);
                if(x->f_source_manager->groupGetMute(i))
                {
                    t_jrgba red = {1., 0., 0., 1.};
                    jgraphics_set_source_jrgba(g, &red);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., JGRAPHICS_2PI);
                    jgraphics_stroke(g);
                    for(int j = 0; j < 2; j++)
                    {
                        jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                        jgraphics_line_to(g, sourcePositionX + Tools::abscisse(x->f_size_source * 1., CICM_2PI * j / 2. + CICM_PI2 / 2.), sourcePositionY + Tools::ordinate(x->f_size_source * 1., CICM_2PI * j / 2. + CICM_PI2 / 2.));
                    }
                    jgraphics_stroke(g);
                }
                 
            }
        }
		jtextlayout_destroy(jtl);
        
		jbox_end_layer((t_object*)x, view, gensym("groups_layer"));
    }
	jbox_paint_layer((t_object *)x, view, gensym("groups_layer"), 0., 0.);
}


void draw_rect_selection(t_hoamap *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("rect_selection_layer"), rect->width, rect->height);
	t_rect sel;
	t_jrgba selected_color = {0,0,1,0.2};
	if (g)
    {
		if (x->f_rect_selection_exist)
        {
			sel.x = floor(x->f_rect_selection.x) + 0.5;
			sel.y = floor(x->f_rect_selection.y) + 0.5;
			sel.width = x->f_rect_selection.width;
			sel.height = x->f_rect_selection.height;
			
			selected_color.alpha = 0.05;
			t_jrgba strokecolor = selected_color;
			strokecolor.alpha = 0.2;
			
			jgraphics_set_source_jrgba(g, &selected_color);
			jgraphics_rectangle(g, sel.x, sel.y, sel.width, sel.height);
			jgraphics_fill(g);
			
			jgraphics_set_source_jrgba(g, &strokecolor);
			jgraphics_set_line_width(g, 1);
			jgraphics_rectangle(g, sel.x, sel.y, sel.width, sel.height);
			jgraphics_stroke(g);
		}
		jbox_end_layer((t_object*)x, view, gensym("rect_selection_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("rect_selection_layer"), 0., 0.);
}

/**********************************************************/
/*                   Souris et clavier                    */
/**********************************************************/

void hoamap_mousedown(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
    double ditanceSelected = (x->f_size_source / x->rect.width * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
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
            jpopupmenu_additem(popup, 0, "Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Remove group", NULL, 0, 0, NULL);
            if(x->f_source_manager->groupGetMute(x->f_index_of_group_to_remove))
            {
                jpopupmenu_additem(popup, 2, "Unmute group", NULL, 0, 0, NULL);
                jpopupmenu_additem(popup, 3, "Set group color", NULL, 0, 0, NULL);
                jpopupmenu_additem(popup, 4, "Set group description", NULL, 0, 0, NULL);
            }
            else
            {
                jpopupmenu_additem(popup, 2, "Mute group", NULL, 0, 0, NULL);
                jpopupmenu_additem(popup, 3, "Unmute group", NULL, 0, 0, NULL);
                jpopupmenu_additem(popup, 4, "Set group color", NULL, 0, 0, NULL);
                jpopupmenu_additem(popup, 5, "Set group description", NULL, 0, 0, NULL);
            }
            
            int choice = jpopupmenu_popup(popup, pos, 0);
            if (choice == 1)
            {
                t_atom av[3];
                atom_setlong(av, x->f_index_of_group_to_remove);
                atom_setsym(av+1, gensym("mute"));
                atom_setlong(av+2, 1);
                outlet_list(x->f_out_groups, 0L, 3, av);
                x->f_source_manager->groupRemove(x->f_index_of_group_to_remove);
            }
            if (choice == 2)
            {
                if(x->f_source_manager->groupGetMute(x->f_index_of_group_to_remove))
                    x->f_source_manager->groupSetMute(x->f_index_of_group_to_remove, 0);
                else
                     x->f_source_manager->groupSetMute(x->f_index_of_group_to_remove, 1);
            }
            if (choice == 3)
            {
                if(x->f_source_manager->groupGetMute(x->f_index_of_group_to_remove))
                    hoamap_color_picker(x);
                else
                    x->f_source_manager->groupSetMute(x->f_index_of_group_to_remove, 0);
            }
            if (choice == 4)
            {
                if(x->f_source_manager->groupGetMute(x->f_index_of_group_to_remove))
                    hoamap_text_field(x);
                else
                    hoamap_color_picker(x);
            }
            if (choice == 5)
                hoamap_color_picker(x);
        }
        else if(x->f_index_of_selected_source != -1)
        {
            x->f_index_of_source_to_color = x->f_index_of_selected_source;
            x->f_index_of_selected_source = -1;
            x->f_index_of_group_to_color = -1;
            jpopupmenu_additem(popup, 0, "Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Remove source", NULL, 0, 0, NULL);
            if(x->f_source_manager->sourceGetMute(x->f_index_of_source_to_remove))
                jpopupmenu_additem(popup, 2, "Unmute source", NULL, 0, 0, NULL);
            else
                jpopupmenu_additem(popup, 2, "Mute source", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 3, "Set source color", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 4, "Set source description", NULL, 0, 0, NULL);
            int choice = jpopupmenu_popup(popup, pos, 0);
            if (choice == 1)
            {
                t_atom av[3];
                atom_setlong(av, x->f_index_of_source_to_remove);
                atom_setsym(av+1, gensym("mute"));
                atom_setlong(av+2, 1);
                outlet_list(x->f_out_sources, 0L, 3, av);
                x->f_source_manager->sourceRemove(x->f_index_of_source_to_remove);
            }
            if (choice == 2)
            {
                if(x->f_source_manager->sourceGetMute(x->f_index_of_source_to_remove))
                    x->f_source_manager->sourceSetMute(x->f_index_of_source_to_remove, 0);
                else
                    x->f_source_manager->sourceSetMute(x->f_index_of_source_to_remove, 1);
            }
            if (choice == 3)
            {
                hoamap_color_picker(x);
            }
            if (choice == 4)
            {
                hoamap_text_field(x);
            }
        }
        else /* Free zone - Add Source */
        {
            t_jpopupmenu* subpopup = jpopupmenu_create();
            jpopupmenu_setfont(subpopup, x->jfont);
            x->f_index_of_group_to_color = -1;
            x->f_index_of_source_to_color = -2;
            jpopupmenu_additem(popup, 0, "Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Add source", NULL, 0, 0, NULL);
            int choice = jpopupmenu_popup(popup, pos, 0);
            int check = 0;
            if (choice == 1)
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
            }
        }
        jpopupmenu_destroy(popup);
    }
    x->f_rect_selection_exist = -1;
    x->f_rect_selection.x = x->f_rect_selection.y = x->f_rect_selection.width =  x->f_rect_selection.height = 0.;
    if(x->f_index_of_selected_source == -1 && x->f_index_of_selected_group == -1)
    {
        x->f_rect_selection.x = pt.x;
        x->f_rect_selection.y = pt.y;
        x->f_rect_selection_exist = 1;
    }
    hoamap_mousedrag(x, patcherview, pt, modifiers);
}


void hoamap_mousedrag(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
	
    /* Deplacement d'une source */
	if (x->f_index_of_selected_source != -1)
    {
        if(modifiers == 148 || modifiers == 404)
            x->f_source_manager->sourceSetAngle(x->f_index_of_selected_source, Tools::angle(cursor.x, cursor.y) - CICM_PI2);
        else if(modifiers == 18 || modifiers == 274)
            x->f_source_manager->sourceSetRadius(x->f_index_of_selected_source, Tools::radius(cursor.x, cursor.y));
        else
            x->f_source_manager->sourceSetCartesian(x->f_index_of_selected_source, cursor.x, cursor.y);
    }
    /* Deplacement d'un groupe */
    else if (x->f_index_of_selected_group != -1)
    {
        if(modifiers == 148 || modifiers == 404)
            x->f_source_manager->groupSetRelativeAngle(x->f_index_of_selected_group, Tools::angle(cursor.x, cursor.y));
        else if(modifiers == 18 || modifiers == 274)
            x->f_source_manager->groupSetRelativeRadius(x->f_index_of_selected_group, Tools::radius(cursor.x, cursor.y));
        else if(modifiers == 150)
            x->f_source_manager->groupSetRelativePolar(x->f_index_of_selected_group, Tools::radius(cursor.x, cursor.y), Tools::angle(cursor.x, cursor.y));
        else
            x->f_source_manager->groupSetCartesian(x->f_index_of_selected_group, cursor.x, cursor.y);            
    }
    /* Selection de plusieurs source pour la création d'un groupe */
    else
    {
		x->f_rect_selection.width = pt.x - x->f_rect_selection.x;
		x->f_rect_selection.height = pt.y - x->f_rect_selection.y;
		jbox_invalidate_layer((t_object *)x, NULL, gensym("rect_selection_layer"));
		jbox_redraw((t_jbox *)x);
        
    }
    object_notify(x, _sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

void hoamap_mouseup(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    if(x->f_rect_selection_exist)
    {
        int indexOfNewGroup = -1;
        for(int i = 0; i < MAX_SOURCES && indexOfNewGroup == -1; i++)
        {
            if (x->f_source_manager->groupGetExistence(i) == 0)
            {
                indexOfNewGroup = i;
            }
        }
    
        double x1 = ((x->f_rect_selection.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
        double x2 = (((x->f_rect_selection.x + x->f_rect_selection.width) / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
        double y1 = ((-x->f_rect_selection.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
        double y2 = (((-x->f_rect_selection.y - x->f_rect_selection.height) / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
        
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i) && indexOfNewGroup >= 0)
            {
                int abscissaOfSource = x->f_source_manager->sourceGetAbscissa(i);
                int ordinateOfSource = x->f_source_manager->sourceGetOrdinate(i);
                
                if(((abscissaOfSource > x1 && abscissaOfSource < x2) || (abscissaOfSource < x1 && abscissaOfSource > x2)) && ((ordinateOfSource > y1 && ordinateOfSource < y2) || (ordinateOfSource < y1 && ordinateOfSource > y2)))
                {
                    x->f_source_manager->groupSetSource(indexOfNewGroup, i);
                    x->f_index_of_selected_group = indexOfNewGroup;
                }
            }
        }
        x->f_rect_selection_exist = 0;
    }
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("rect_selection_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoamap_mousewheel(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	if (modifiers == eAltKey)
    {
		double newZoom = x->f_zoom_factor + y_inc / 100.;
        x->f_zoom_factor = Tools::clip(newZoom, MIN_ZOOM, MAX_ZOOM);
        object_notify(x, _sym_modified, NULL);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
        jbox_redraw((t_jbox *)x);
	}    
}

void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
    double ditanceSelected = (x->f_size_source / x->rect.width * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
                x->f_index_of_selected_group = i;
            }
        }
    }
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    coordinatesCartesian cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.width * 2.) + 1.) / x->f_zoom_factor;
    double ditanceSelected = (x->f_size_source / x->rect.width * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = Tools::distance_euclidean(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = Tools::distance_euclidean(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
                x->f_index_of_selected_group = i;
            }
        }
    }
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}
    
void hoamap_color_picker(t_hoamap *x)
{
    if(x->f_patcher)
        object_free(x->f_patcher);
    if(x->f_colorpicker )
        object_free(x->f_colorpicker);
    
       x->f_patcher = NULL;
       x->f_colorpicker = NULL;
       
       t_dictionary *dico = dictionary_new();
       char parsebuf[256];
       t_atom a;
       long ac = 0;
       t_atom *av = NULL;
       
       sprintf(parsebuf,"@defrect 0 0 128 32 @openrect 0 0 128 32 @title color @enablehscroll 0 @enablevscroll 0 @presentation 0 @toolbarid \"\"");
       atom_setparse(&ac,&av,parsebuf);
       attr_args_dictionary(dico,ac,av);
       atom_setobj(&a,dico);
       sysmem_freeptr(av);
       x->f_patcher = (t_object *)object_new_typed(CLASS_NOBOX,gensym("jpatcher"),1, &a);
       freeobject((t_object *)dico);
       
       x->f_colorpicker = newobject_sprintf(x->f_patcher, "@maxclass colorpicker @patching_rect 0 0 128 32");
       object_attach_byptr_register(x, x->f_patcher, CLASS_NOBOX);
       object_attach_byptr_register(x, x->f_colorpicker, CLASS_BOX);
    
    object_method(x->f_colorpicker, gensym("bang"));
}


void hoamap_text_field(t_hoamap *x)
{
    if(x->f_textfield)
        object_free(x->f_textfield);
    if(x->f_patcher)
        object_free(x->f_patcher);
    
    x->f_patcher = NULL;
    x->f_textfield = NULL;
    
    t_dictionary *dico = dictionary_new();
    char parsebuf[256];
    t_atom a;
    long ac = 0;
    t_atom *av = NULL;
    
    sprintf(parsebuf,"@defrect 0 0 256 32 @openrect 0 0 256 32 @title Description @enablehscroll 0 @enablevscroll 0 @presentation 0 @toolbarvisible 0 @retain 1\"\"");
    atom_setparse(&ac,&av,parsebuf);
    attr_args_dictionary(dico,ac,av);
    atom_setobj(&a,dico);
    sysmem_freeptr(av);
    x->f_patcher = (t_object *)object_new_typed(CLASS_NOBOX,gensym("jpatcher"),1, &a);
    freeobject((t_object *)dico);
    
    x->f_textfield = newobject_sprintf(x->f_patcher, "@maxclass hoa.textfield @patching_rect 0 0 256 32");
    
    object_attach_byptr_register(x, x->f_patcher, CLASS_NOBOX);
    object_attach_byptr_register(x, x->f_textfield, CLASS_NOBOX);
    
    object_method(x->f_patcher,gensym("noedit"), 1);
    object_method(x->f_patcher,gensym("vis"));
}

/****************************************************************************************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/

void hoa_textfield_init(void)
{
	t_class *c;
	
	jpatcher_syms_init();
	
	c = class_new("hoa.textfield",
				  (method)textfield_new,
				  (method)textfield_free,
				  sizeof(t_textfield),
				  (method)NULL,
				  A_GIMME,
				  0L);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_TEXTFIELD | JBOX_FONTATTR | JBOX_FIXWIDTH);
	
	class_addmethod(c, (method)textfield_paint,         "paint",		A_CANT, 0);
	class_addmethod(c, (method)textfield_key,			"key",			A_CANT, 0);
	class_addmethod(c, (method)textfield_keyfilter,     "keyfilter",	A_CANT, 0);
	class_addmethod(c, (method)textfield_enter,         "enter",		A_CANT, 0);
	class_addmethod(c, (method)textfield_select,		"select",		0);
	class_addmethod(c, (method)textfield_notify,		"notify",		A_CANT, 0);
    
	CLASS_ATTR_DEFAULT(c, "rect", 0, "0. 0. 100. 20.");
	
	class_register(CLASS_BOX, c);
	s_textfield_class = c;
}


t_textfield* textfield_new(t_symbol *name, short argc, t_atom *argv)
{
	t_textfield* x;
	t_dictionary *d = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
 	
	x = (t_textfield*)object_alloc(s_textfield_class);
	if (x) {
		long		flags;
		t_object	*textfield;
		
		flags = 0
        | JBOX_DRAWFIRSTIN
        | JBOX_NODRAWBOX
        | JBOX_DRAWINLAST
        | JBOX_TRANSPARENT
		//		| JBOX_NOGROW
		//		| JBOX_GROWY
        | JBOX_GROWBOTH
		//		| JBOX_IGNORELOCKCLICK
		//		| JBOX_HILITE
		//		| JBOX_BACKGROUND
		//		| JBOX_NOFLOATINSPECTOR
        | JBOX_TEXTFIELD
		;
		
		jbox_new(&x->j_box, flags, argc, argv);
		x->j_box.b_firstin = (t_object*) x;
        x->j_patcher = NULL;
        x->j_patcherview = NULL;
        /*
         x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
         */
		t_jrgba textcolor = {0., 0., 0., 1.};
		textfield = jbox_get_textfield((t_object*) x);
		if (textfield) {
			textfield_set_editonclick(textfield, 1);
			textfield_set_textmargins(textfield, 3, 3, 3, 3);
			textfield_set_textcolor(textfield, &textcolor);
		}
        
		attr_dictionary_process(x, d);
        
		
		jbox_ready(&x->j_box);
	}
	return x;
}

void textfield_free(t_textfield *x)
{
	jbox_free(&x->j_box);
}

void textfield_select(t_textfield *x)
{
	defer(x, (method)textfield_doselect, 0, 0, 0);
}

void textfield_doselect(t_textfield *x)
{
	t_object *p = NULL;
	object_obex_lookup(x,gensym("#P"), &p);
	if (p) {
		t_atom rv;
		long ac = 1;
		t_atom av[1];
		atom_setobj(av, x);
		object_method_typed(p, gensym("selectbox"), ac, av, &rv);
	}
}


long textfield_key(t_textfield *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	char buff[256];
	buff[0] = textcharacter;
	buff[1] = 0;
	object_method(patcherview, gensym("insertboxtext"), x, buff);
    long size	= 0;
	char *text	= NULL;
	t_object *textfield = jbox_get_textfield((t_object *)x);
	object_method(textfield, gensym("gettextptr"), &text, &size);
    object_notify(x, gensym("text"), text);
	jbox_redraw((t_jbox *)x);
	return 1;
}

long textfield_keyfilter(t_textfield *x, t_object *patcherview, long *keycode, long *modifiers, long *textcharacter)
{
	t_atom arv;
	long rv = 1;
	long k = *keycode;
	
	if (k == JKEY_TAB || k == JKEY_ENTER || k == JKEY_RETURN || k == JKEY_ESC) {
		object_method_typed(patcherview, gensym("endeditbox"), 0, NULL, &arv);
		rv = 0;
	}
    long size	= 0;
    char *text	= NULL;
    t_object *textfield = jbox_get_textfield((t_object *)x);
    object_method(textfield, gensym("gettextptr"), &text, &size);
    object_notify(x, gensym("text"), text);
	return rv;
}

void textfield_enter(t_textfield *x)
{
	long size	= 0;
	char *text	= NULL;
	t_object *textfield = jbox_get_textfield((t_object *)x);
	object_method(textfield, gensym("gettextptr"), &text, &size);
    object_notify(x, gensym("text"), text);
}

void textfield_paint(t_textfield *x, t_object *view)
{
	t_rect rect;
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(view);
    jbox_get_rect_for_view((t_object*) x, view, &rect);
    if(x->j_patcher == NULL)
    {
        object_obex_lookup(x,gensym("#P"), &x->j_patcher);
        object_attach_byptr_register(x, x->j_patcher, CLASS_NOBOX);
    }
    if(x->j_patcherview == NULL)
    {
        x->j_patcherview = object_attr_getobj(x->j_patcher, gensym("firstview"));
        object_attach_byptr_register(x, x->j_patcherview, CLASS_NOBOX);
    }
	
    t_jrgba white = {1., 1., 1., 1.};
	jgraphics_rectangle_rounded(g, 0., 0., rect.width, rect.height, 2., 2.);
	jgraphics_set_source_jrgba(g, &white);
	jgraphics_fill(g);
    
    
    t_jrgba grey = {0., 0., 0., 1.};
    jgraphics_rectangle(g, 0., 0., rect.width, rect.height);
	jgraphics_set_source_jrgba(g, &grey);
    jgraphics_set_line_width(g, 1.);
	jgraphics_stroke(g);
	
}

t_max_err textfield_notify(t_textfield *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if (sender == x->j_patcher)
    {
		if (msg == gensym("free"))
        {
			x->j_patcher = NULL;
            x->j_patcherview = NULL;
        }
    }
    if(sender == x->j_patcherview)
    {
        if (msg == gensym("attr_modified"))
        {
            t_symbol* attrname = (t_symbol *)object_method(data, gensym("getname"));
            if (attrname == gensym("rect"))
            {
                t_atom *av = NULL;
                long    ac = 0;
                object_attr_getvalueof(x->j_patcherview, gensym("rect"), &ac, &av);
                if (ac && av)
                {
                    atom_setlong(av, 0);
                    atom_setlong(av+1, 0);
                    object_method(x, gensym("rect"), ac, av);
                    freebytes(av, sizeof(t_atom) * ac);
                }
                jbox_redraw((t_jbox *)x);
            }
        }
        
    }
    return MAX_ERR_NONE;
}




