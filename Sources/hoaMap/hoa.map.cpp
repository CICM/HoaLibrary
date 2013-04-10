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

#define MAX_SOURCES 64

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

typedef struct  _hoamap
{
	t_jbox          j_box;
	t_rect          rect;
	t_jfont*        jfont;
    long		f_output_mode;
	void*		f_out_sources;
    void*		f_out_groups;
    
    SourcesManager*  f_source_manager;
	
    t_pt        f_cursor_position;
    long        f_index_of_selected_source;
    long        f_index_of_selected_group;
    long        f_index_of_source_to_remove;
    long        f_index_of_group_to_remove;
    
    t_jrgba		f_source_colorBackground;
    t_jrgba		f_source_colorSources;
    double      f_size_source;
	double		f_zoom_factor;
	
    double      f_source_abscissa[MAX_SOURCES];
    double      f_source_ordinate[MAX_SOURCES];
    long        f_source_existence[MAX_SOURCES];
    t_symbol*   f_source_description[MAX_SOURCES];
    double      f_source_color[MAX_SOURCES*4];
    
    t_atom*     f_group[MAX_SOURCES*5];
    long        f_group_existence[MAX_SOURCES];
    double      f_group_color[MAX_SOURCES*4];
    t_symbol*   f_group_description[MAX_SOURCES];
    
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
void hoamap_preset(t_hoamap *x);
t_max_err hoamap_setvalueof(t_hoamap *x, long ac, t_atom *av);
t_max_err hoamap_getvalueof(t_hoamap *x, long *ac, t_atom **av);

void hoamap_bang(t_hoamap *x);

t_max_err hoamap_abscissa_saved(t_hoamap *x, t_object *s, short ac, t_atom *av);
t_max_err hoamap_ordinate_saved(t_hoamap *x, t_object *s, short ac, t_atom *av);
t_max_err hoamap_description_saved(t_hoamap *x, t_object *s, short ac, t_atom *av);
t_max_err hoamap_existence(t_hoamap *x, t_object *s, short ac, t_atom *av);

void hoamap_all_preset(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_source(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_group(t_hoamap *x, t_symbol *s, short ac, t_atom *av);


/* Paint Methods */
void hoamap_paint(t_hoamap *x, t_object *view);
void draw_background(t_hoamap *x, t_object *view, t_rect *rect);
void draw_sources(t_hoamap *x,  t_object *view, t_rect *rect);
void draw_groups(t_hoamap *x,  t_object *view, t_rect *rect);

void hoamap_mousedown(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousedrag(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseup(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);

int main()
{
	t_class *c;
    common_symbols_init();
    
	c = class_new("hoa.ease", (method)hoamap_new, (method)hoamap_free, (short)sizeof(t_hoamap), 0L, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method)hoamap_assist,           "assist",		A_CANT,	0);
	class_addmethod(c, (method)hoamap_paint,            "paint",		A_CANT,	0);
	class_addmethod(c, (method)hoamap_getdrawparams,    "getdrawparams",A_CANT, 0);
	class_addmethod(c, (method)hoamap_notify,           "notify",		A_CANT, 0);
    class_addmethod(c, (method)hoamap_preset,           "preset",               0);
    class_addmethod(c, (method)hoamap_getvalueof,       "getvalueof",   A_CANT, 0);
	class_addmethod(c, (method)hoamap_setvalueof,       "setvalueof",   A_CANT, 0);
    
	class_addmethod(c, (method)hoamap_bang,             "bang",			A_CANT, 0);
    
    class_addmethod(c, (method)hoamap_all_preset,        "all",         A_GIMME,0);
    
    class_addmethod(c, (method)hoamap_source,           "source",       A_GIMME,0);
    class_addmethod(c, (method)hoamap_group,            "group",        A_GIMME,0);
    
    class_addmethod(c, (method)hoamap_mousedown,        "mousedown",	A_CANT, 0);
    class_addmethod(c, (method)hoamap_mousedrag,        "mousedrag",	A_CANT, 0);
    class_addmethod(c, (method)hoamap_mouseup,          "mouseup",      A_CANT, 0);
    class_addmethod(c, (method)hoamap_mouseenter,       "mouseenter",   A_CANT, 0);
    class_addmethod(c, (method)hoamap_mousemove,        "mousemove",    A_CANT, 0);
    class_addmethod(c, (method)hoamap_mouseleave,       "mouseleave",   A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 300");
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
    
    CLASS_ATTR_SYM_ARRAY        (c, "description_saved", ATTR_SET_OPAQUE_USER, t_hoamap, f_source_description, MAX_SOURCES);
    CLASS_ATTR_ACCESSORS		(c, "description_saved", NULL, hoamap_description_saved);
    CLASS_ATTR_INVISIBLE		(c, "description_saved", 0);
    CLASS_ATTR_SAVE             (c, "description_saved", 1);
    
    CLASS_ATTR_DOUBLE_ARRAY     (c, "abscissa_saved", ATTR_SET_OPAQUE_USER, t_hoamap, f_source_abscissa, MAX_SOURCES);
    CLASS_ATTR_ACCESSORS		(c, "abscissa_saved", NULL, hoamap_abscissa_saved);
    CLASS_ATTR_INVISIBLE		(c, "abscissa_saved", 0);
    CLASS_ATTR_SAVE             (c, "abscissa_saved", 1);
    
    CLASS_ATTR_DOUBLE_ARRAY     (c, "ordinate_saved", ATTR_SET_OPAQUE_USER, t_hoamap, f_source_ordinate, MAX_SOURCES);
    CLASS_ATTR_ACCESSORS		(c, "ordinate_saved", NULL, hoamap_ordinate_saved);
    CLASS_ATTR_INVISIBLE		(c, "ordinate_saved", 0);
    CLASS_ATTR_SAVE             (c, "ordinate_saved", 1);
    
    CLASS_ATTR_LONG_ARRAY       (c, "existence", ATTR_SET_OPAQUE_USER, t_hoamap, f_source_existence, MAX_SOURCES);
    CLASS_ATTR_ACCESSORS		(c, "existence", NULL, hoamap_existence);
    CLASS_ATTR_INVISIBLE		(c, "existence", 0);
    CLASS_ATTR_SAVE             (c, "existence", 1);
    
    /* Colors */
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_hoamap, f_source_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0. 0. 0. 1.");
	
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
	//int i;
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
	x->f_source_manager = new SourcesManager();

    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    x->j_box.b_firstin = (t_object*) x;
    x->f_out_groups = listout(x);
	x->f_out_sources   = listout(x);
	
	x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    
	attr_dictionary_process(x, d);

    for (int i = 0; i < MAX_SOURCES; i++)
    {
        if(x->f_source_existence[i] == 0)
            x->f_source_manager->sourceRemove(i);
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
/* Sauvegarde des derniers paramètres pour l'initaliation */
/**********************************************************/

t_max_err hoamap_abscissa_saved(t_hoamap *x, t_object *s, short ac, t_atom *av)
{
    if (ac > MAX_SOURCES)
        ac = MAX_SOURCES;
    for(long i = 0; i < ac; i++)
    {
        if(atom_gettype(av+i) == A_FLOAT)
        {
            x->f_source_manager->sourceSetAbscissa(i, atom_getfloat(av+i));
            x->f_source_abscissa[i] = x->f_source_manager->sourceGetAbscissa(i);
        }
    }
    object_notify(x, _sym_modified, NULL);
    return MAX_ERR_NONE;
}

t_max_err hoamap_ordinate_saved(t_hoamap *x, t_object *s, short ac, t_atom *av)
{
    if (ac > MAX_SOURCES)
        ac = MAX_SOURCES;
    for(long i = 0; i < ac; i++)
    {
        if(atom_gettype(av+i) == A_FLOAT)
        {
            x->f_source_manager->sourceSetOrdinate(i, atom_getfloat(av+i));
            x->f_source_ordinate[i] = x->f_source_manager->sourceGetOrdinate(i);
        }
    }
    object_notify(x, _sym_modified, NULL);
    return MAX_ERR_NONE;
}

t_max_err hoamap_description_saved(t_hoamap *x, t_object *s, short ac, t_atom *av)
{
    if (ac > MAX_SOURCES)
        ac = MAX_SOURCES;
    for(long i = 0; i < ac; i++)
    {
        if(atom_gettype(av+i) == A_SYM)
        {
            x->f_source_description[i] = atom_getsym(av+i);
            x->f_source_manager->sourceSetDescription(i, atom_getsym(av+i)->s_name);
        }
    }
    object_notify(x, _sym_modified, NULL);
    return MAX_ERR_NONE;
}

t_max_err hoamap_existence(t_hoamap *x, t_object *s, short ac, t_atom *av)
{
    if (ac > MAX_SOURCES)
        ac = MAX_SOURCES;
    for(long i = 0; i < ac; i++)
    {
        if(atom_gettype(av+i) == A_LONG && atom_getlong(av+i) == 0)
        {
            x->f_source_existence[i] = 0;
            x->f_source_manager->sourceRemove(i);
        }
        else
            x->f_source_existence[i] = 1;
    }
    object_notify(x, _sym_modified, NULL);
    return MAX_ERR_NONE;
}

void hoamap_all_preset(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if (ac > 5)
        ac = 5;
    int i = 0;
    if(atom_gettype(av) == A_LONG)
        i = atom_getlong(av);
    if(atom_gettype(av+1) == A_FLOAT && atom_gettype(av+2) == A_FLOAT)
    {
        x->f_source_manager->sourceSetCartesian(i, atom_getfloat(av+1), atom_getfloat(av+2));
        x->f_source_abscissa[i] = atom_getfloat(av+1);
        x->f_source_ordinate[i] = atom_getfloat(av+2);
    }
    if(atom_gettype(av+3) == A_SYM)
    {
        x->f_source_manager->sourceSetDescription(i, atom_getsym(av+3)->s_name);
        x->f_source_description[i] = atom_getsym(av+3);
    }
    if(atom_gettype(av+4) == A_LONG && atom_getlong(av+4) < 1)
    {
        x->f_source_manager->sourceRemove(i);
        x->f_source_existence[i] = 0;
    }
    else
        x->f_source_existence[i] = 1;

    object_notify(x, _sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
    
    
}

/**********************************************************/
/*          Intialisation par l'utilisateur               */
/**********************************************************/

void hoamap_source(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && atom_gettype(av)==A_LONG && atom_getlong(av)>=0 && atom_getlong(av) < MAX_SOURCES && atom_gettype(av+1) == A_SYM)
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
            t_atom av[2];
            atom_setsym(av, gensym("remove"));
            atom_setlong(av+1, atom_getlong(av));
            outlet_list(x->f_out_sources, 0L, 2, av);
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
                    x->f_source_manager->sourceSetDescription(atom_getlong(av), "");
                    x->f_source_description[atom_getlong(av)] = NULL;
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
            color sourceColor;
            sourceColor.red = atom_getfloat(av+2);
            sourceColor.green = atom_getfloat(av+3);
            sourceColor.blue = atom_getfloat(av+4);
            sourceColor.alpha = atom_getfloat(av+5);
            x->f_source_manager->sourceSetColor(atom_getlong(av), sourceColor);
        }
        long ngroup = x->f_source_manager->sourceGetNumberOfGroups(atom_getlong(av));
        post("N groups : %ld", ngroup);
        for(int i = 0; i <= ngroup; i++)
        {
            post("groups : %ld", x->f_source_manager->sourceGetGroupIndex(atom_getlong(av), i));
        }
        x->f_source_abscissa[atom_getlong(av)] = x->f_source_manager->sourceGetAbscissa(atom_getlong(av));
        x->f_source_ordinate[atom_getlong(av)] = x->f_source_manager->sourceGetOrdinate(atom_getlong(av));
        x->f_source_existence[atom_getlong(av)] = x->f_source_manager->sourceGetExistence(atom_getlong(av));
        x->f_source_description[atom_getlong(av)] = gensym(x->f_source_manager->sourceGetDescription(atom_getlong(av)).c_str());
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
        else if(atom_getsym(av+1) == gensym("remove"))
            x->f_source_manager->groupRemove(atom_getlong(av));
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
                    x->f_source_description[atom_getlong(av)] = NULL;
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
            color groupColor;
            groupColor.red = atom_getfloat(av+2);
            groupColor.green = atom_getfloat(av+3);
            groupColor.blue = atom_getfloat(av+4);
            groupColor.alpha = atom_getfloat(av+5);
            x->f_source_manager->groupSetColor(atom_getlong(av), groupColor);
        }                
    }
    
    object_notify(x, _sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);    
}

/**********************************************************/
/*                          Sortie                        */
/**********************************************************/

void hoamap_bang(t_hoamap *x)
{
    t_atom av[4];
    if(x->f_output_mode == 0)
    {
        atom_setsym(av, gensym("polar"));
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av+1, i);
                atom_setfloat(av+2, x->f_source_manager->sourceGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->sourceGetAngle(i));
                outlet_list(x->f_out_sources, 0L, 4, av);
            }
        }
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                atom_setlong(av+1, i);
                atom_setfloat(av+2, x->f_source_manager->groupGetRadius(i));
                atom_setfloat(av+3, x->f_source_manager->groupGetAngle(i));
                outlet_list(x->f_out_groups, 0L, 4, av);
            }
        }

    }
    else
    {
        atom_setsym(av, gensym("cartesian"));
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                atom_setlong(av+1, i);
                atom_setfloat(av+2,x->f_source_manager->sourceGetAbscissa(i));
                atom_setfloat(av+3,x->f_source_manager->sourceGetOrdinate(i));
                outlet_list(x->f_out_sources, 0L, 4, av);
            }
        }
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                atom_setlong(av+1, i);
                atom_setfloat(av+2, x->f_source_manager->groupGetAbscissa(i));
                atom_setfloat(av+3, x->f_source_manager->groupGetOrdinate(i));
                outlet_list(x->f_out_groups, 0L, 4, av);
            }
        }
    }
}

/**********************************************************/
/*                  Preset et Pattr                       */
/**********************************************************/

void hoamap_preset(t_hoamap *x)
{
    
    void* z;
    if(!(z = gensym("_preset")->s_thing))
        return;
    
    for(long i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        binbuf_vinsert(z, gensym("osslffsl")->s_name, x, object_classname(x), gensym("all"), i, x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), gensym(x->f_source_manager->sourceGetDescription(i).c_str()), x->f_source_manager->sourceGetExistence(i));
    }
}

t_max_err hoamap_setvalueof(t_hoamap *x, long ac, t_atom *av)
{
	if (ac && av)
    {
        if(ac > MAX_SOURCES * 4)
            ac = MAX_SOURCES * 4;
        for (int i = 0; i < ac; i += 4)
        {
            if(atom_gettype(av+i) == A_FLOAT && atom_gettype(av+i+1) == A_FLOAT)
            {
                x->f_source_manager->sourceSetCartesian(i/4, atom_getfloat(av+i), atom_getfloat(av+i+1));
                x->f_source_abscissa[i/4] = atom_getfloat(av+i);
                x->f_source_ordinate[i/4] = atom_getfloat(av+i+1);
            }
            if(atom_gettype(av+i+2) == A_SYM)
            {
                x->f_source_manager->sourceSetDescription(i/4, atom_getsym(av+i+2)->s_name);
                x->f_source_description[i/4] = atom_getsym(av+i+2);
            }
            if(atom_gettype(av+i+3) == A_LONG && atom_getlong(av+i+3) < 1)
            {
                x->f_source_manager->sourceRemove(i/4);
                x->f_source_existence[i/4] = 0;
            }
            else if(atom_gettype(av+i+3) == A_FLOAT && atom_getfloat(av+i+3) < 1.)
            {
                x->f_source_manager->sourceRemove(i/4);
                x->f_source_existence[i/4] = 0;
            }
            else
                x->f_source_existence[i/4] = 1;
        }
        jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
        jbox_redraw((t_jbox *)x);
        hoamap_bang(x);
	}
	return MAX_ERR_NONE;
}

t_max_err hoamap_getvalueof(t_hoamap *x, long *ac, t_atom **av)
{
	if (ac && av)
    {
		if (*ac && *av)
        {
            long limit = *ac;
            if (limit > MAX_SOURCES * 4)
                limit = MAX_SOURCES * 4;
            
            for (int i = 0; i < limit; i += 4)
            {
                atom_setfloat(*av+i, x->f_source_manager->sourceGetAbscissa(i / 4));
                atom_setfloat(*av+i+1, x->f_source_manager->sourceGetOrdinate(i / 4));
                atom_setsym(*av+i+2, gensym(x->f_source_manager->sourceGetDescription(i / 4).c_str()));
                atom_setlong(*av+i+3, x->f_source_manager->sourceGetExistence(i / 4));
            }
            return MAX_ERR_NONE;
		}
        else
        {
			*av = (t_atom *)getbytes(MAX_SOURCES * 4 * sizeof(t_atom));
            *ac = MAX_SOURCES * 4 ;
        }
        for (int i = 0; i < *ac; i += 4)
        {
            atom_setfloat(*av+i, x->f_source_manager->sourceGetAbscissa(i / 4));
            atom_setfloat(*av+i+1, x->f_source_manager->sourceGetOrdinate(i / 4));
            atom_setsym(*av+i+2, gensym(x->f_source_manager->sourceGetDescription(i / 4).c_str()));
            atom_setlong(*av+i+3, x->f_source_manager->sourceGetExistence(i / 4));
        }
        
    }
	return MAX_ERR_NONE;
}

t_max_err hoamap_zoom(t_hoamap *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv)
    {
        if(atom_gettype(argv) == A_FLOAT)
            x->f_zoom_factor = Tools::clip(atom_getfloat(argv), 0.01f, 1.f);
        else if(atom_gettype(argv) == A_LONG)
            x->f_zoom_factor = Tools::clip((float)atom_getlong(argv), 0.01f, 1.f);
        
    }
    jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    return MAX_ERR_NONE;
}

t_max_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	 {
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
         post("attr %s", name->s_name);
		if(name == gensym("bgcolor") )
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
		jbox_redraw((t_jbox *)x);
	 }
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

/**********************************************************/
/*                          Dessin                        */
/**********************************************************/

void hoamap_paint(t_hoamap *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	x->rect = rect;
	draw_background(x, view, &rect);
    draw_sources(x, view, &rect);
    draw_groups(x, view, &rect);
}

void draw_background(t_hoamap *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
	
	if (g)
    {
		t_jrgba outsideColor = {1,1,1, 1};
		t_jrgba insideColor = x->f_source_colorBackground;
        insideColor.alpha = 0.2;
		jgraphics_set_source_jrgba(g, &outsideColor);
		jgraphics_rectangle_rounded(g, 0., 0., x->rect.width, x->rect.width, 6, 6);
		jgraphics_fill(g);
        
		jgraphics_set_source_jrgba(g, &insideColor);
		jgraphics_rectangle_rounded(g, 0., 0., x->rect.width, x->rect.width, 6, 6);
		jgraphics_fill(g);
		
        /* Circles */
        double radius  = x->f_zoom_factor * rect->width / 10.;
        for(int i = 5; i > 0; i--)
        {
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &insideColor);
            jgraphics_arc(g, rect->width / 2 + 0.5, rect->width / 2 + 0.5, (double)i * radius,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
        
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &outsideColor);
            jgraphics_arc(g, rect->width / 2, rect->width / 2, (double)i * radius,  0., JGRAPHICS_2PI);
            jgraphics_stroke(g);
        }
    
        /* Lines ¨*/
        jgraphics_set_source_jrgba(g, &insideColor);
        jgraphics_move_to(g, 0. - 0.5, rect->width / 2. - 0.5);
        jgraphics_line_to(g, rect->width - 0.5, rect->width / 2. - 0.5);
        jgraphics_move_to(g, rect->width / 2. - 0.5, 0. - 0.5);
        jgraphics_line_to(g, rect->width / 2. - 0.5, rect->width - 0.5);
        jgraphics_set_line_width(g, 2);
        jgraphics_stroke(g);
        jgraphics_set_source_jrgba(g, &outsideColor);
        jgraphics_move_to(g, 0., rect->width / 2.);
        jgraphics_line_to(g, rect->width, rect->width / 2.);
        jgraphics_move_to(g, rect->width / 2., 0.);
        jgraphics_line_to(g, rect->width / 2., rect->width);
        jgraphics_set_line_width(g, 1);
        jgraphics_stroke(g);

        double ecart = x->f_zoom_factor * rect->width / 2.;
        if(ecart < 10 && ecart >= 5)
            ecart *= 2;
        else if(ecart < 5)
            ecart *= 4;
		for(double i = ecart; i < rect->width / 2.; i += ecart)
        {
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
    //t_jrgba selected_color = x->f_source_color_selection;
	int ombreX;
	int ombreY;
	t_jrgba ombre = {0,0,0,0.3};
    t_jrgba selected_color = {0,0,1,0.2};
	char description[250];
	double descriptionPositionX;
    double descriptionPositionY;
	double sourcePositionX;
    double sourcePositionY;
	double sourcePositionShadowX;
	double sourcePositionShadowY;
	
	//selected_color.alpha = 0.2;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("sources_layer"), rect->width, rect->height);
	
    x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    x->f_size_source = jbox_get_fontsize((t_object *)x) / 2.;
    fontSize = jbox_get_fontsize((t_object *)x);

	ombreX = ombreY = floor(x->f_size_source * 0.15) + 0.5;
	
	if (g)
    {
        //jfont_set_font_size(x->jfont, fontSize);
        jtl = jtextlayout_create();
        jgraphics_set_line_width(g, x->f_size_source * 0.2);
		for(i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                sourcePositionX = (x->f_source_manager->sourceGetAbscissa(i) * x->f_zoom_factor + 1.) * rect->width / 2.;
                sourcePositionY = (-x->f_source_manager->sourceGetOrdinate(i) * x->f_zoom_factor + 1.) * rect->width / 2.;
                sourcePositionShadowX = sourcePositionX + ombreX;
                sourcePositionShadowY = sourcePositionY + ombreY;
			
                sourceColor.red = x->f_source_manager->sourceGetColor(i).red;
                sourceColor.green = x->f_source_manager->sourceGetColor(i).green;
                sourceColor.blue = x->f_source_manager->sourceGetColor(i).blue;
                sourceColor.alpha = x->f_source_manager->sourceGetColor(i).alpha;
                ombre.alpha = 0.3;
                
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
                    jgraphics_arc(g, sourcePositionShadowX + ombreX * 0.5, sourcePositionShadowY + ombreX * 0.5, x->f_size_source * 1.5,  0., JGRAPHICS_2PI);
                    jgraphics_fill(g);
                }
                jgraphics_set_source_jrgba(g, &sourceColor);

                jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 0.6,  0., JGRAPHICS_2PI);
                jgraphics_fill(g);
                jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., JGRAPHICS_2PI);
                jgraphics_stroke(g);
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
    
	int ombreX;
	int ombreY;
	t_jrgba ombre = {0,0,0,0.3};
    t_jrgba selected_color = {0,0,1,0.2};
	char description[250] = {0};
	double descriptionPositionX;
    double descriptionPositionY;
	double sourcePositionX;
    double sourcePositionY;
	double sourcePositionShadowX;
	double sourcePositionShadowY;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("groups_layer"), rect->width, rect->height);
	x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    x->f_size_source = jbox_get_fontsize((t_object *)x) / 2.;
    fontSize = jbox_get_fontsize((t_object *)x);
    
	ombreX = ombreY = floor(x->f_size_source * 0.15) + 0.5;
	
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
                sourcePositionShadowX = sourcePositionX + ombreX;
                sourcePositionShadowY = sourcePositionY + ombreY;
                
                sourceColor.red = x->f_source_manager->groupGetColor(i).red;
                sourceColor.green = x->f_source_manager->groupGetColor(i).green;
                sourceColor.blue = x->f_source_manager->groupGetColor(i).blue;
                sourceColor.alpha = x->f_source_manager->groupGetColor(i).alpha;
                ombre.alpha = 0.3;
                
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
                    jgraphics_arc(g, sourcePositionShadowX + ombreX * 0.5, sourcePositionShadowY + ombreX * 0.5, x->f_size_source * 1.5,  0., JGRAPHICS_2PI);
                    jgraphics_fill(g);
                }
                // source
                
                jgraphics_set_source_jrgba(g, &sourceColor);
                jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 0.5,  0., JGRAPHICS_2PI);
                jgraphics_stroke(g);
                /*
                sprintf(description,"%ld", (long)i);
                jtextlayout_settextcolor(jtl, &sourceColor);
                jtextlayout_set(jtl, description, x->jfont, sourcePositionX - x->f_size_source / 2., sourcePositionY - x->f_size_source, x->f_size_source, x->f_size_source / 2., JGRAPHICS_TEXT_JUSTIFICATION_LEFT, JGRAPHICS_TEXTLAYOUT_USEELLIPSIS);
                jtextlayout_draw(jtl, g);
                jgraphics_set_line_width(g, x->f_size_source * 0.4);
                 */
                for(int j = 0; j < 4; j++)
                {
                    jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                    jgraphics_line_to(g, sourcePositionX + Tools::abscisse(x->f_size_source, CICM_2PI * j / 4.), sourcePositionY + Tools::ordinate(x->f_size_source, CICM_2PI * j / 4.));
                }
                 
                jgraphics_stroke(g);
            }
        }
		jtextlayout_destroy(jtl);
        
		jbox_end_layer((t_object*)x, view, gensym("groups_layer"));
    }
	jbox_paint_layer((t_object *)x, view, gensym("groups_layer"), 0., 0.);
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
    post("%ld", modifiers);

    if(modifiers == 160)
    {
        int posX, posY;
        t_pt pos;
        jmouse_getposition_global(&posX, &posY);
        pos.x = posX;
        pos.y = posY;
        x->f_index_of_source_to_remove = x->f_index_of_selected_source;
        t_jpopupmenu* popup = jpopupmenu_create();
        jpopupmenu_setfont(popup, x->jfont);
       
        if(x->f_index_of_selected_group != -1)
        {
            jpopupmenu_additem(popup, 0, "Group Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Remove group", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 2, "Set group color", NULL, 0, 0, NULL);
            int choice = jpopupmenu_popup(popup, pos, 0);
            if (choice == 1)
            {
                x->f_source_manager->groupRemove(x->f_index_of_selected_group);
                x->f_index_of_selected_source = -1;
            }
            else if (choice == 2)
            {
                ;
            }
        }
        else if(x->f_index_of_selected_source != -1)
        {
            jpopupmenu_additem(popup, 0, "Source Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Remove source", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 2, "Set source color", NULL, 0, 0, NULL);
            int choice = jpopupmenu_popup(popup, pos, 0);
            if (choice == 1)
            {
                x->f_source_manager->sourceRemove(x->f_index_of_source_to_remove);
                x->f_index_of_selected_source = -1;
            }
            else if (choice == 2)
            {
                t_dictionary *d = dictionary_new();
                char parsebuf[256];
                t_atom a;
                long ac = 0;
                t_atom *av = NULL;
                
                sprintf(parsebuf,"@defrect 0 0 128 32 @openrect 0 0 128 32 @title color @enablehscroll 0 @enablevscroll 0 @presentation 0 @toolbarid \"\"");
                atom_setparse(&ac,&av,parsebuf);
                attr_args_dictionary(d,ac,av);
                atom_setobj(&a,d);
                sysmem_freeptr(av);
                t_object * patcher = (t_object *)object_new_typed(CLASS_NOBOX,gensym("jpatcher"),1, &a);
                freeobject((t_object *)d);
                
                object_method(patcher,gensym("noedit"), 1);
                t_object* colorpicker = newobject_sprintf(patcher, "@maxclass colorpicker @patching_rect 0 0 128 32");
                object_method(colorpicker, gensym("bang"));
            }
        }
        else
        {
            
            jpopupmenu_additem(popup, 0, "Map Menu", NULL, 0, 1, NULL);
            jpopupmenu_addseperator(popup);
            jpopupmenu_additem(popup, 1, "Add source", NULL, 0, 0, NULL);
            jpopupmenu_additem(popup, 2, "Set zoom", NULL, 0, 0, NULL);
            
            t_jpopupmenu* subpopup = jpopupmenu_create();
            jpopupmenu_setfont(subpopup, x->jfont);
            jpopupmenu_additem(subpopup, 0, "Coordinates Type", NULL, 0, 1, NULL);
            jpopupmenu_additem(subpopup, 1, "Polar", NULL, 0, 0, NULL);
            jpopupmenu_additem(subpopup, 2, "Cartesian", NULL, 0, 0, NULL);

            jpopupmenu_addsubmenu(popup, "Set output", subpopup, 0);
            
            int choice = jpopupmenu_popup(popup, pos, 0);
            int check = 0;
            if (choice == 1)
            {
                for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource() && check == 0; i++)
                {
                    if (x->f_source_manager->sourceGetExistence(i) < 1)
                    {
                        check = 1;
                        x->f_source_manager->sourceSetCartesian(i, cursor.x, cursor.y);
                    }
                }
            }
            else if (choice == 2);
            else if (choice == 3)
            {
                int subchoice = jpopupmenu_popup(subpopup, pos, 0);
                if (subchoice == 1)
                {
                    x->f_output_mode = 0;
                }
                else if (subchoice == 1)
                {
                    x->f_output_mode = 1;
                }
            }
            jpopupmenu_destroy(subpopup);
        }
        jpopupmenu_destroy(popup);
        hoamap_bang(x);
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
        int indexOfNewGroup = -1;
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfGroup() && indexOfNewGroup != -1; i++)
        {
            if (x->f_source_manager->groupGetExistence(i) == 0)
            {
                indexOfNewGroup = i;
            }
        }
        for(int i = 0; i < x->f_source_manager->getMaximumIndexOfSource(); i++)
        {            
            if(x->f_source_manager->groupGetExistence(i))
            {
                int abscissaOfSource = x->f_source_manager->sourceGetAbscissa(i);
                int ordinateOfSource = x->f_source_manager->sourceGetOrdinate(i);
                if(((abscissaOfSource > x->f_cursor_position.x && abscissaOfSource < cursor.x) || (abscissaOfSource < x->f_cursor_position.x && abscissaOfSource > cursor.x)) && ((ordinateOfSource > x->f_cursor_position.y && ordinateOfSource < cursor.y) || (ordinateOfSource < x->f_cursor_position.y && ordinateOfSource > cursor.y)))
                {
                    ;// x->f_source_manager->
                }
            }
        }
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
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("groups_layer"));
    jbox_redraw((t_jbox *)x);
}

void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

