/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../Hoa2D.max.h"

#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

typedef struct _textfield {
	t_jbox			j_box;
    t_object*       j_patcher;
    t_object*       j_patcherview;
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
    void*           f_clock;
    
	void*		f_out_sources;
    void*		f_out_groups;
    void*		f_out_infos;
    
    t_object*   f_patcher;
    t_object*   f_colorpicker;
    t_object*   f_textfield;
    
	Hoa2D::SourcesManager*     f_source_manager;
    Hoa2D::SourcesPreset*      f_source_preset;
    Hoa2D::SourcesTrajectory*  f_source_trajectory;
    
    t_pt        f_cursor_position;
    long        f_index_of_selected_source;
    long        f_index_of_selected_group;
    long        f_index_of_source_to_remove;
    long        f_index_of_group_to_remove;
    long        f_index_of_source_to_color;
    long        f_index_of_group_to_color;
    
    t_jrgba		f_color_bg;
    t_jrgba     f_color_bd;
    t_jrgba     f_color_selection;
    
    int         f_cartConstrain;
    
    double      f_size_source;
	double		f_zoom_factor;
    
    t_rect		f_rect_selection;
	int			f_rect_selection_exist;
    
    // options :
    t_atom_long f_output_mode;
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

void hoamap_parameters_sources(t_hoamap *x, short ac, t_atom *av);
void hoamap_parameters_groups(t_hoamap *x, short ac, t_atom *av);
void hoamap_parameters_slots(t_hoamap *x, short ac, t_atom *av);
void hoamap_parameters_trajectory(t_hoamap *x, short ac, t_atom *av);
void hoamap_source_save(t_hoamap *x, t_dictionary *d);
void hoamap_group_save(t_hoamap *x, t_dictionary *d);
void hoamap_slot_save(t_hoamap *x, t_dictionary *d);
void hoamap_trajectory_save(t_hoamap *x, t_dictionary *d);
void hoamap_jsave(t_hoamap *x, t_dictionary *d);

void hoamap_doread(t_hoamap *x, t_symbol *s, long argc, t_atom *argv);
void hoamap_dowrite(t_hoamap *x, t_symbol *s, long argc, t_atom *argv);
void hoamap_tick(t_hoamap *x);

void hoamap_source(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_group(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_slot(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_trajectory(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_bang(t_hoamap *x);
void hoamap_infos(t_hoamap *x);
void hoamap_clear_all(t_hoamap *x);

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
long hoamap_key(t_hoamap *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);

t_hoa_err hoa_getinfos(t_hoamap* x, t_hoa_boxinfos* boxinfos);

int C74_EXPORT main()
{
    hoa_textfield_init();
	t_class *c;
    
	c = class_new("hoa.2d.map", (method)hoamap_new, (method)hoamap_free, (short)sizeof(t_hoamap), 0L, A_GIMME, 0);
	class_alias(c, gensym("hoa.map"));
	
	hoa_initclass(c, NULL);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method) hoamap_assist,           "assist",			A_CANT,	0);
	class_addmethod(c, (method) hoamap_paint,            "paint",			A_CANT,	0);
	class_addmethod(c, (method) hoamap_getdrawparams,    "getdrawparams",	A_CANT, 0);
	class_addmethod(c, (method) hoamap_notify,           "notify",			A_CANT, 0);
    
    class_addmethod(c, (method) hoamap_jsave,            "jsave",			A_CANT, 0);
    
    class_addmethod(c, (method) hoamap_bang,             "bang",			A_CANT, 0);
    class_addmethod(c, (method) hoamap_infos,            "getinfo",					0);
    
    class_addmethod(c, (method) hoamap_source,           "source",			A_GIMME,0);
    class_addmethod(c, (method) hoamap_group,            "group",			A_GIMME,0);
    class_addmethod(c, (method) hoamap_slot,             "slot",			A_GIMME,0);
    class_addmethod(c, (method) hoamap_trajectory,       "trajectory",		A_GIMME,0);
    class_addmethod(c, (method) hoamap_clear_all,        "clear",			A_NOTHING ,0);
    
    class_addmethod(c, (method) hoamap_mousedown,        "mousedown",		A_CANT, 0);
    class_addmethod(c, (method) hoamap_mousedrag,        "mousedrag",		A_CANT, 0);
    class_addmethod(c, (method) hoamap_mouseup,          "mouseup",			A_CANT, 0);
    class_addmethod(c, (method) hoamap_mouseenter,       "mouseenter",		A_CANT, 0);
    class_addmethod(c, (method) hoamap_mousemove,        "mousemove",		A_CANT, 0);
    class_addmethod(c, (method) hoamap_mouseleave,       "mouseleave",		A_CANT, 0);
    class_addmethod(c, (method) hoamap_mousewheel,		 "mousewheel",		A_CANT, 0);
    class_addmethod(c, (method) hoamap_key,              "key",				A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 300");
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
    
    /* Colors */
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_hoamap, f_color_bg);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.9 0.9 0.9 1.");
    
    CLASS_ATTR_RGBA				(c, "bdcolor", 0, t_hoamap, f_color_bd);
	CLASS_ATTR_CATEGORY			(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bdcolor", 0, "3");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bdcolor", 0, "0.5 0.5 0.5 1.");
    
    CLASS_ATTR_RGBA				(c, "selcolor", 0, t_hoamap, f_color_selection);
	CLASS_ATTR_CATEGORY			(c, "selcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "selcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "selcolor", 0, "Selection Color");
	CLASS_ATTR_ORDER			(c, "selcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "selcolor", 0, "0.36 0.37 0.7 0.5");
	
    /* Behavior */
	CLASS_ATTR_LONG				(c,"outputmode", 0, t_hoamap, f_output_mode);
	CLASS_ATTR_LABEL			(c,"outputmode", 0, "Output Mode");
	CLASS_ATTR_CATEGORY			(c,"outputmode", 0, "Behavior");
	CLASS_ATTR_ENUMINDEX		(c,"outputmode", 0, "Polar Cartesian");
	CLASS_ATTR_DEFAULT          (c,"outputmode", 0,  "0");
    CLASS_ATTR_SAVE             (c,"outputmode", 1);
    CLASS_ATTR_ORDER			(c,"outputmode", 0, "1");
    
	CLASS_ATTR_DOUBLE			(c,"zoom", 0, t_hoamap, f_zoom_factor);
    CLASS_ATTR_ACCESSORS		(c,"zoom", NULL, hoamap_zoom);
	CLASS_ATTR_LABEL			(c,"zoom", 0,   "Zoom");
	CLASS_ATTR_CATEGORY			(c,"zoom", 0,   "Behavior");
	CLASS_ATTR_DEFAULT          (c,"zoom", 0,   "0.35");
    CLASS_ATTR_ORDER			(c,"zoom", 0,   "2");
    CLASS_ATTR_SAVE             (c,"zoom", 1);

	class_register(CLASS_BOX, c);
	hoamap_class = c;
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
	| JBOX_DRAWBACKGROUND
	| JBOX_GROWY
	| JBOX_HILITE
	;
    
	jbox_new(&x->j_box, flags, argc, argv);
	x->f_source_manager = new Hoa2D::SourcesManager(1./MIN_ZOOM - 5.);
    x->f_source_preset = new Hoa2D::SourcesPreset();
    x->f_source_trajectory = new Hoa2D::SourcesTrajectory();
    
    x->f_rect_selection_exist = 0;
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    x->j_box.b_firstin = (t_object*) x;
        
    x->f_out_infos      = listout(x);
    x->f_out_groups     = listout(x);
	x->f_out_sources    = listout(x);
	
    x->f_clock = clock_new(x,(method)hoamap_tick);
	x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));

    x->f_patcher = NULL;
    x->f_colorpicker = NULL;
    
	attr_dictionary_process(x, d);
    t_atom *av = NULL;
    long ac = 0;
        
    dictionary_copyatoms(d, hoa_sym_trajectory_parameters, &ac, &av);
    hoamap_parameters_trajectory(x, ac, av);
    if (av && ac)
    {
        ac = 0;
        sysmem_freeptr(av);
    }
    dictionary_copyatoms(d, hoa_sym_slots_parameters, &ac, &av);
    hoamap_parameters_slots(x, ac, av);
    if (av && ac)
    {
        ac = 0;
        sysmem_freeptr(av);
    }
    
    dictionary_copyatoms(d, hoa_sym_sources_parameters, &ac, &av);
    hoamap_parameters_sources(x, ac, av);
    if (av && ac)
    {
        ac = 0;
        sysmem_freeptr(av);
    }
    dictionary_copyatoms(d, hoa_sym_groups_parameters, &ac, &av);
    hoamap_parameters_groups(x, ac, av);
    if (av && ac)
    {
        ac = 0;
        sysmem_freeptr(av);
    }
    
	jbox_ready(&x->j_box);
	return (x);
}

t_hoa_err hoa_getinfos(t_hoamap* x, t_hoa_boxinfos* boxinfos)
{
	boxinfos->object_type = HOA_OBJECT_2D;
	boxinfos->autoconnect_inputs = 0;
	boxinfos->autoconnect_outputs = 0;
	boxinfos->autoconnect_inputs_type = HOA_CONNECT_TYPE_STANDARD;
	boxinfos->autoconnect_outputs_type = HOA_CONNECT_TYPE_STANDARD;
	return HOA_ERR_NONE;
}

void hoamap_free(t_hoamap *x)
{
	jbox_free(&x->j_box);
    jfont_destroy(x->jfont);
    freeobject((t_object *)x->f_clock);
    delete x->f_source_manager;
    delete x->f_source_preset;
    delete x->f_source_trajectory;
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
		sprintf(s,"(messages) Behavior and appearance");
	else
    {
        if(a == 0)
            sprintf(s,"(list) Sources coordinates");
        if(a == 1)
            sprintf(s,"(list) Groups coordinates");
        if(a == 2)
            sprintf(s,"(list) Infos");
    }
}

void hoamap_doread(t_hoamap *x, t_symbol *s, long argc, t_atom *argv)
{
	short outvol,error;
	char ps[MAX_PATH_CHARS];
    char ps_dotjson[MAX_PATH_CHARS];
    int forgot_dotjson = 0;
	
    t_fourcc outtype;
    t_fourcc filetypelist = 'pSto';
	t_dictionary *d;
    
	if (s == hoa_sym_nothing)
    {
		if (open_dialog(ps, &outvol, &outtype, &filetypelist, 1))
			return;
	}
    else
    {
        strcpy(ps,s->s_name);
        forgot_dotjson = bool(!strstr(ps, ".json"));
        if (!forgot_dotjson) {
            if (locatefile_extended(ps, &outvol, &outtype, &filetypelist, -1))
            {
                object_error((t_object *)x, "%s: can't find file",ps);
                return;
            }
        }
        else
        {
            sprintf(ps_dotjson, "%s.json", ps);
            if (locatefile_extended(ps_dotjson, &outvol, &outtype, &filetypelist, -1))
            {
                object_error((t_object *)x, "%s: can't find file",ps);
                return;
            }
        }
	}
	error = forgot_dotjson ? dictionary_read(ps_dotjson, outvol, &d) : dictionary_read(ps, outvol, &d);
	if (error)
    {
		object_error((t_object *)x, "%s: error %d opening file",ps, error);
		return;
	}
    else
    {
        t_atom *av = NULL;
        long ac = 0;
        
        dictionary_copyatoms(d, hoa_sym_slots_parameters, &ac, &av);
        hoamap_parameters_slots(x, ac, av);
        if (av && ac)
        {
            ac = 0;
            sysmem_freeptr(av);
        }
        
        dictionary_copyatoms(d, hoa_sym_trajectory_parameters, &ac, &av);
        hoamap_parameters_trajectory(x, ac, av);
        if (av && ac)
        {
            ac = 0;
            sysmem_freeptr(av);
        }
        
        if (d)
        {
            object_free(d);
        }
    }
}

void hoamap_dowrite(t_hoamap *x, t_symbol *sym, long argc, t_atom *argv)
{
	short outvol,error;
	char ps[MAX_PATH_CHARS];

    t_fourcc outtype;
    t_fourcc filetypelist = 'pSto';

    t_filehandle ref;
	t_dictionary *d = dictionary_new();
    
    if(atom_getsym(argv+1) == hoa_sym_slot)
        hoamap_slot_save(x, d);
    else if(atom_getsym(argv+1) == hoa_sym_trajectory)
        hoamap_trajectory_save(x, d);
    else
    {
        hoamap_slot_save(x, d);
        hoamap_trajectory_save(x, d);
    }
    
	if (atom_getsym(argv) == hoa_sym_nothing)
    {
		if (saveasdialog_extended(ps,&outvol, &outtype, &filetypelist, 1))
			return;
	}
    else
    {
		strcpy(ps, atom_getsym(argv)->s_name);
        if(locatefile_extended(ps, &outvol, &outtype, &filetypelist, -1))
           path_createsysfile(ps, outvol, filetypelist, &ref);
	}
    
	error = dictionary_write(d, ps, outvol);
	if (error)
    {
		object_error((t_object *)x, "%s: error %d writing file",ps, error);
		return;
	}
    if (d)
    {
        object_free(d);
    }
}

void hoamap_getdrawparams(t_hoamap *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = HOA_UI_BORDERTHICKNESS;
	params->d_cornersize = HOA_UI_CORNERSIZE;
	
	t_jrgba bgcolor = x->f_color_bg;
	vector_add(3, (double*)&bgcolor, -0.1);
	vector_clip_minmax(3, (double*)&bgcolor, 0., 1.);
	
	params->d_boxfillcolor = bgcolor;
    params->d_bordercolor =  x->f_color_bd;
}

void hoamap_tick(t_hoamap *x)
{
    if(x->f_index_of_selected_source != -1)
        x->f_source_trajectory->recordSourceInTrajectory(x->f_source_manager, x->f_index_of_selected_source);
    else if(x->f_index_of_selected_group != -1)
        x->f_source_trajectory->recordGroupInTrajectory(x->f_source_manager, x->f_index_of_selected_group);
    clock_fdelay(x->f_clock, 100);
}

/**********************************************************/
/*          Intialisation par l'utilisateur               */
/**********************************************************/

void hoamap_clear_all(t_hoamap *x)
{
    x->f_source_manager->clearAll();
    
    object_notify(x, hoa_sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

void hoamap_source(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && atom_gettype(av)==A_LONG && atom_getlong(av)>=0 && atom_gettype(av+1) == A_SYM)
    {
        if(atom_getsym(av+1) == hoa_sym_polar || atom_getsym(av+1) == hoa_sym_pol)
            x->f_source_manager->sourceSetPolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == hoa_sym_radius)
            x->f_source_manager->sourceSetRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_angle)
            x->f_source_manager->sourceSetAngle(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_cartesian || atom_getsym(av+1) == hoa_sym_car)
            x->f_source_manager->sourceSetCartesian(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == hoa_sym_abscissa)
            x->f_source_manager->sourceSetAbscissa(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_ordinate)
            x->f_source_manager->sourceSetOrdinate(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_remove)
        {
            x->f_source_manager->sourceRemove(atom_getlong(av));
            t_atom av[3];
            atom_setlong(av, atom_getlong(av));
            atom_setsym(av+1, hoa_sym_mute);
            atom_setlong(av+2, 1);
            outlet_list(x->f_out_sources, 0L, 3, av);
        }
        else if(atom_getsym(av+1) == hoa_sym_mute)
            x->f_source_manager->sourceSetMute(atom_getlong(av), atom_getlong(av+2));
        else if(atom_getsym(av+1) == hoa_sym_description)
        {
            char description[250];
            char number[250];
            if(atom_gettype(av+1) == A_SYM)
            {
                strcpy(description, atom_getsym(av+2)->s_name);
                strcat(description, " ");
                if(atom_getsym(av+2) == hoa_sym_remove)
                {
                    x->f_source_manager->sourceSetDescription(atom_getlong(av), "");
                    object_notify(x, hoa_sym_modified, NULL);
                    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
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
                    sprintf(number, "%ld ", (long)atom_getlong(av+i));
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
        else if(atom_getsym(av+1) == hoa_sym_color)
        {
            x->f_source_manager->sourceSetColor(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3), atom_getfloat(av+4), atom_getfloat(av+5));
        }
        
    }
    object_notify(x, hoa_sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

void hoamap_group(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av && atom_gettype(av) == A_LONG && atom_getlong(av) >= 0 && atom_gettype(av+1) == A_SYM)
    {
        if(atom_getsym(av+1) == hoa_sym_set)
        {
            x->f_source_manager->groupRemove(atom_getlong(av));
            for(int i = 2; i < ac; i++)
            {
                x->f_source_manager->groupSetSource(atom_getlong(av), atom_getlong(av+i));
            }
        }        
        else if(atom_getsym(av+1) == hoa_sym_polar || atom_getsym(av+1) == hoa_sym_pol)
            x->f_source_manager->groupSetPolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3) + HOA_PI2);
        else if(atom_getsym(av+1) == hoa_sym_radius)
            x->f_source_manager->groupSetRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_angle)
            x->f_source_manager->groupSetAngle(atom_getlong(av), atom_getfloat(av+2) + HOA_PI2);
        else if(atom_getsym(av+1) == hoa_sym_cartesian || atom_getsym(av+1) == hoa_sym_car)
            x->f_source_manager->groupSetCartesian(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == hoa_sym_abscissa)
            x->f_source_manager->groupSetAbscissa(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_ordinate)
            x->f_source_manager->groupSetOrdinate(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_relpolar || atom_getsym(av+1) == hoa_sym_relativepolar)
            x->f_source_manager->groupSetRelativePolar(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3));
        else if(atom_getsym(av+1) == hoa_sym_relradius || atom_getsym(av+1) == hoa_sym_relativeradius)
            x->f_source_manager->groupSetRelativeRadius(atom_getlong(av), atom_getfloat(av+2));
        else if(atom_getsym(av+1) == hoa_sym_relangle || atom_getsym(av+1) == hoa_sym_relativeangle)
            x->f_source_manager->groupSetRelativeAngle(atom_getlong(av), atom_getfloat(av+2) + HOA_PI2);
        else if(atom_getsym(av+1) == hoa_sym_mute)
            x->f_source_manager->groupSetMute(atom_getlong(av), atom_getlong(av+2));
        else if(atom_getsym(av+1) == hoa_sym_remove)
        {
            x->f_source_manager->groupRemove(atom_getlong(av));
            t_atom av[3];
            atom_setlong(av, atom_getlong(av));
            atom_setsym(av+1, hoa_sym_mute);
            atom_setlong(av+2, 1);
            outlet_list(x->f_out_groups, 0L, 3, av);
        }
        else if(atom_getsym(av+1) == hoa_sym_description)
        {
            char description[250];
            char number[250];
            if(atom_gettype(av+1) == A_SYM)
            {
                strcpy(description, atom_getsym(av+2)->s_name);
                strcat(description, " ");
                if(atom_getsym(av+2) == hoa_sym_remove)
                {
                    x->f_source_manager->groupSetDescription(atom_getlong(av), "");
                    object_notify(x, hoa_sym_modified, NULL);
                    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
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
                    sprintf(number, "%ld ", (long)atom_getlong(av+i));
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
        else if(atom_getsym(av+1) == hoa_sym_color)
        {
            x->f_source_manager->groupSetColor(atom_getlong(av), atom_getfloat(av+2), atom_getfloat(av+3), atom_getfloat(av+4), atom_getfloat(av+5));
        }
    }
    
    object_notify(x, hoa_sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);    
}

void hoamap_slot(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av)
    {
        if(atom_gettype(av) == A_SYM)
        {
            t_symbol *sym = atom_getsym(av);
            if(sym == hoa_sym_store)
                x->f_source_preset->storeSouceManagerAtSlot(x->f_source_manager, atom_getlong(av+1));
            else if(sym == hoa_sym_storeagain)
                x->f_source_preset->storeSouceManagerAtLastUsedSlot(x->f_source_manager);
            else if(sym == hoa_sym_storeempty)
                x->f_source_preset->storeSouceManagerAtFirstEmptySlot(x->f_source_manager);
            else if(sym == hoa_sym_storeend)
                x->f_source_preset->storeSouceManagerAtNewEndSlot(x->f_source_manager);
            else if(sym == hoa_sym_storenext)
                x->f_source_preset->storeSouceManagerAtNextSlot(x->f_source_manager);
            else if(sym == hoa_sym_insert)
                x->f_source_preset->insertSlot(x->f_source_manager, atom_getlong(av+1));
            else if(sym == hoa_sym_remove)
                x->f_source_preset->removeSlot(atom_getlong(av+1));
            else if(sym == hoa_sym_delete)
                x->f_source_preset->deleteSlot(atom_getlong(av+1));
            else if(sym == hoa_sym_copy)
                x->f_source_preset->copySlot(atom_getlong(av+1), atom_getlong(av+2));
            else if(sym == hoa_sym_renumber)
                x->f_source_preset->renumber();
            else if(sym == hoa_sym_clear)
                x->f_source_preset->clear();
            else if(sym == hoa_sym_recall)
                x->f_source_preset->recallFractionalSlot(x->f_source_manager, atom_getlong(av+1), atom_getlong(av+2), (double)atom_getfloat(av+3));
            else if(sym == hoa_sym_read)
            {
                t_symbol *sym = ( ac >= 1 && atom_gettype(av+1) == A_SYM) ? atom_getsym(av+1) : hoa_sym_nothing;
                defer( (t_object *)x,(method)hoamap_doread, sym, 0, NULL);
                //defer_low(x,(method)hoamap_doread,atom_getsym(av+1),0,0L);
            }
            else if(sym == hoa_sym_write)
            {
                t_atom parameter[2];
                atom_setsym(parameter, ( ac >= 1 && atom_gettype(av+1) == A_SYM) ? atom_getsym(av+1) : hoa_sym_nothing);
                atom_setsym(parameter+1, hoa_sym_slot);
                defer(x,(method)hoamap_dowrite, hoa_sym_nothing, 2, parameter);
                //defer_low(x,(method)hoamap_dowrite, NULL, 2, parameter);
            }
            else if(sym == hoa_sym_storesource)
                x->f_source_preset->storeSourceAtSlot(x->f_source_manager, atom_getlong(av+1),atom_getlong(av+2));
            else if(sym == hoa_sym_storegroup)
                x->f_source_preset->storeGroupAtSlot(x->f_source_manager, atom_getlong(av+1), atom_getlong(av+2));
        }
        else if(atom_gettype(av) == A_LONG)
            x->f_source_preset->recallSlot(x->f_source_manager, atom_getlong(av));
        else if(atom_gettype(av) == A_FLOAT)
            x->f_source_preset->recallFractionalSlot(x->f_source_manager, (double)atom_getfloat(av));
    }
    
    object_notify(x, hoa_sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

void hoamap_trajectory(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
    if(ac && av)
    {
        if(atom_gettype(av) == A_SYM)
        {
            t_symbol *sym = atom_getsym(av);
            if(sym == hoa_sym_record)
                x->f_source_trajectory->setRecording(atom_getlong(av+1));
            else if(sym == hoa_sym_limit)
                x->f_source_trajectory->setLimited(atom_getlong(av+1));
            else if(sym == hoa_sym_erase)
                x->f_source_trajectory->erase();
            else if(sym == hoa_sym_erasepart)
                x->f_source_trajectory->erase(atom_getfloat(av+1), atom_getfloat(av+2));
            else if(sym == hoa_sym_read)
            {
                t_symbol *sym = ( ac >= 1 && atom_gettype(av+1) == A_SYM) ? atom_getsym(av+1) : hoa_sym_nothing;
                defer( (t_object *)x,(method)hoamap_doread, sym,0, NULL);
                //defer_low(x,(method)hoamap_doread,atom_getsym(av+1),0,0L);
            }
            else if(sym == hoa_sym_write)
            {
                t_atom parameter[2];
                atom_setsym(parameter, ( ac >= 1 && atom_gettype(av+1) == A_SYM) ? atom_getsym(av+1) : hoa_sym_nothing);
                atom_setsym(parameter+1, hoa_sym_trajectory);
                defer(x,(method)hoamap_dowrite, hoa_sym_nothing, 2, parameter);
            }
        }
        else if(atom_gettype(av) == A_FLOAT)
            x->f_source_trajectory->playTrajectory(x->f_source_manager, (double)atom_getfloat(av));
    }
    
    object_notify(x, hoa_sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

/**********************************************************/
/*                  Preset et Pattr                       */
/**********************************************************/

void hoamap_jsave(t_hoamap *x, t_dictionary *d)
{
    x->f_source_manager->groupClean();
    hoamap_source_save(x, d);
    hoamap_group_save(x, d);
    hoamap_slot_save(x, d);
    hoamap_trajectory_save(x, d);
}

void hoamap_source_save(t_hoamap *x, t_dictionary *d)
{
    t_atom *av;
    long ac = x->f_source_manager->getNumberOfSources()*10;
    av = new t_atom[ac];
    if(av && ac)
    {
        for(long i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
				double *color = x->f_source_manager->sourceGetColor(i);
                atom_setsym(av+j, hoa_sym_source);
                atom_setlong(av+j+1, i);
                atom_setfloat(av+j+2, x->f_source_manager->sourceGetAbscissa(i));
                atom_setfloat(av+j+3, x->f_source_manager->sourceGetOrdinate(i));
                atom_setlong(av+j+4, x->f_source_manager->sourceGetMute(i));
                atom_setfloat(av+j+5, color[0]);
                atom_setfloat(av+j+6, color[1]);
                atom_setfloat(av+j+7, color[2]);
                atom_setfloat(av+j+8, color[3]);
                atom_setsym(av+j+9, gensym(x->f_source_manager->sourceGetDescription(i).c_str()));
                j += 10;
            }
        }
        dictionary_appendatoms(d, hoa_sym_sources_parameters, ac, av);
        free(av);
    }
}

void hoamap_group_save(t_hoamap *x, t_dictionary *d)
{
    t_atom *av;
    long ac = 0;
    for(long i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            ac += x->f_source_manager->groupGetNumberOfSources(i) + 9;
        }
    }
    av = new t_atom[ac];
    if(av && ac)
    {
        for(long i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                long numberOfsource = x->f_source_manager->groupGetNumberOfSources(i);
				double *color = x->f_source_manager->groupGetColor(i);
                atom_setsym(av+j, hoa_sym_group);
                atom_setlong(av+j+1, i);
                atom_setlong(av+j+2, numberOfsource);
                for (long k = 0; k < numberOfsource; k++)
                {
                    atom_setlong(av+j+k+3, x->f_source_manager->groupGetSourceIndex(i, k));
                }
                atom_setlong(av+j+numberOfsource+3, x->f_source_manager->groupGetMute(i));
                atom_setfloat(av+j+numberOfsource+4, color[0]);
                atom_setfloat(av+j+numberOfsource+5, color[1]);
                atom_setfloat(av+j+numberOfsource+6, color[2]);
                atom_setfloat(av+j+numberOfsource+7, color[3]);
                atom_setsym(av+j+numberOfsource+8, gensym(x->f_source_manager->groupGetDescription(i).c_str()));
                
                j += x->f_source_manager->groupGetNumberOfSources(i) + 9;
            }
        }
        dictionary_appendatoms(d, hoa_sym_groups_parameters, ac, av);
        free(av);
    }
}

void hoamap_slot_save(t_hoamap *x, t_dictionary *d)
{
    t_atom *av;
    long ac = 0;
	double* color;
    
    SourcesManager* temporySourceManager = NULL;
    temporySourceManager = new SourcesManager();
    if(temporySourceManager)
    {
        ac = 0;
        for(long i = 0; i <= x->f_source_preset->getMaximumIndexOfSlot(); i++)
        {
            if(x->f_source_preset->getSlotExistence(i))
            {
                ac += 2;
                x->f_source_preset->recallSlot(temporySourceManager, i);
                ac += temporySourceManager->getNumberOfSources()*10;
                for(long j = 0; j <= temporySourceManager->getMaximumIndexOfGroup(); j++)
                {
                    if(temporySourceManager->groupGetExistence(j))
                    {
                        ac += temporySourceManager->groupGetNumberOfSources(j) + 9;
                    }
                }
            }
        }
        av = new t_atom[ac];
        if(av && ac)
        {
            for(long j = 0, i = 0; j <= x->f_source_preset->getMaximumIndexOfSlot(); j++)
            {
                if(x->f_source_preset->getSlotExistence(j))
                {
                    atom_setsym(av+i, hoa_sym_slot);
                    atom_setlong(av+i+1, j);
                    x->f_source_preset->recallSlot(temporySourceManager, j);
                    i += 2;
                    for(long k = 0; k <= temporySourceManager->getMaximumIndexOfSource(); k++)
                    {
                        if(temporySourceManager->sourceGetExistence(k))
                        {
							color = temporySourceManager->sourceGetColor(k);
                            atom_setsym(av+i, hoa_sym_source);
                            atom_setlong(av+i+1, k);
                            atom_setfloat(av+i+2, temporySourceManager->sourceGetAbscissa(k));
                            atom_setfloat(av+i+3, temporySourceManager->sourceGetOrdinate(k));
                            atom_setlong(av+i+4, temporySourceManager->groupGetMute(k));
                            atom_setfloat(av+i+5, color[0]);
                            atom_setfloat(av+i+6, color[1]);
                            atom_setfloat(av+i+7, color[2]);
                            atom_setfloat(av+i+8, color[3]);
                            atom_setsym(av+i+9, gensym(temporySourceManager->sourceGetDescription(k).c_str()));
                            
                            i += 10;
                        }
                    }
                    for(long k = 0; k <= temporySourceManager->getMaximumIndexOfGroup(); k++)
                    {
                        if(temporySourceManager->groupGetExistence(k))
                        {
							color = temporySourceManager->groupGetColor(k);
                            long numberOfsource = temporySourceManager->groupGetNumberOfSources(k);
                            atom_setsym(av+i, hoa_sym_group);
                            atom_setlong(av+i+1, k);
                            atom_setlong(av+i+2, numberOfsource);
                            for (long l = 0; l < numberOfsource; l++)
                            {
                                atom_setlong(av+i+l+3, temporySourceManager->groupGetSourceIndex(k, l));
                            }
                            atom_setlong(av+i+numberOfsource+3, temporySourceManager->groupGetMute(k));
                            atom_setfloat(av+i+numberOfsource+4, color[0]);
                            atom_setfloat(av+i+numberOfsource+5, color[1]);
                            atom_setfloat(av+i+numberOfsource+6, color[2]);
                            atom_setfloat(av+i+numberOfsource+7, color[3]);
                            atom_setsym(av+i+numberOfsource+8, gensym(temporySourceManager->groupGetDescription(k).c_str()));
                            
                            i += numberOfsource + 9;
                        }
                    }
                }
            }
            
            dictionary_appendatoms(d, hoa_sym_slots_parameters, ac, av);
            free(av);
        }
        delete temporySourceManager;
    }
}

void hoamap_trajectory_save(t_hoamap *x, t_dictionary *d)
{
    t_atom *av;
    long ac = 0;
	double* color;

    SourcesManager* temporySourceManager = NULL;
    temporySourceManager = new SourcesManager();
    if(temporySourceManager)
    {
        ac = 0;
        for(long i = 0; i <= x->f_source_trajectory->getMaximumIndexOfSlot(); i++)
        {
            if(x->f_source_trajectory->getSlotExistence(i))
            {
                ac += 2;
                x->f_source_trajectory->recallSlot(temporySourceManager, i);
                ac += temporySourceManager->getNumberOfSources()*10;
                for(long j = 0; j <= temporySourceManager->getMaximumIndexOfGroup(); j++)
                {
                    if(temporySourceManager->groupGetExistence(j))
                    {
                        ac += temporySourceManager->groupGetNumberOfSources(j) + 9;
                    }
                }
            }
        }
        av = new t_atom[ac];
        if(av && ac)
        {
            for(long j = 0, i = 0; j <= x->f_source_trajectory->getMaximumIndexOfSlot(); j++)
            {
                if(x->f_source_trajectory->getSlotExistence(j))
                {
                    atom_setsym(av+i, hoa_sym_slot);
                    atom_setlong(av+i+1, j);
                    x->f_source_trajectory->recallSlot(temporySourceManager, j);
                    i += 2;
                    for(long k = 0; k <= temporySourceManager->getMaximumIndexOfSource(); k++)
                    {
                        if(temporySourceManager->sourceGetExistence(k))
                        {
							color = temporySourceManager->sourceGetColor(k);
                            atom_setsym(av+i, hoa_sym_source);
                            atom_setlong(av+i+1, k);
                            atom_setfloat(av+i+2, temporySourceManager->sourceGetAbscissa(k));
                            atom_setfloat(av+i+3, temporySourceManager->sourceGetOrdinate(k));
                            atom_setlong(av+i+4, temporySourceManager->groupGetMute(k));
                            atom_setfloat(av+i+5, color[0]);
                            atom_setfloat(av+i+6, color[1]);
                            atom_setfloat(av+i+7, color[2]);
                            atom_setfloat(av+i+8, color[3]);
                            atom_setsym(av+i+9, gensym(temporySourceManager->sourceGetDescription(k).c_str()));
                            
                            i += 10;
                        }
                    }
                    for(long k = 0; k <= temporySourceManager->getMaximumIndexOfGroup(); k++)
                    {
                        if(temporySourceManager->groupGetExistence(k))
                        {
                            long numberOfsource = temporySourceManager->groupGetNumberOfSources(k);
							color = temporySourceManager->groupGetColor(k);
                            atom_setsym(av+i, hoa_sym_group);
                            atom_setlong(av+i+1, k);
                            atom_setlong(av+i+2, numberOfsource);
                            for (long l = 0; l < numberOfsource; l++)
                            {
                                atom_setlong(av+i+l+3, temporySourceManager->groupGetSourceIndex(k, l));
                            }
                            atom_setlong(av+i+numberOfsource+3, temporySourceManager->groupGetMute(k));
                            atom_setfloat(av+i+numberOfsource+4, color[0]);
                            atom_setfloat(av+i+numberOfsource+5, color[1]);
                            atom_setfloat(av+i+numberOfsource+6, color[2]);
                            atom_setfloat(av+i+numberOfsource+7, color[3]);
                            atom_setsym(av+i+numberOfsource+8, gensym(temporySourceManager->groupGetDescription(k).c_str()));
                            
                            i += numberOfsource + 9;
                        }
                    }
                }
            }
            
            dictionary_appendatoms(d, hoa_sym_trajectory_parameters, ac, av);
            free(av);
        }
        delete temporySourceManager;
    }
}

void hoamap_parameters_sources(t_hoamap *x, short ac, t_atom *av)
{
    if(ac && av)
    {
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == hoa_sym_source) 
            {
                x->f_source_manager->sourceSetCartesian(atom_getlong(av+i+1), atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                x->f_source_manager->sourceSetMute(atom_getlong(av+i+1), atom_getlong(av+i+4));
                x->f_source_manager->sourceSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                x->f_source_manager->sourceSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+9)->s_name);
                i += 8;
            }
        }
    }
}

void hoamap_parameters_groups(t_hoamap *x, short ac, t_atom *av)
{
    if(ac && av)
    {
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == hoa_sym_group)
            {
                long numberOfsource = atom_getlong(av+i+2);
                for (int j = 0; j < numberOfsource; j++)
                {
                    x->f_source_manager->groupSetSource(atom_getlong(av+i+1), atom_getlong(av+i+3+j));
                }
                x->f_source_manager->groupSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+4+numberOfsource), atom_getfloat(av+i+5+numberOfsource), atom_getfloat(av+i+6+numberOfsource), atom_getfloat(av+i+7+numberOfsource));
                x->f_source_manager->groupSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+8+numberOfsource)->s_name);
                i += numberOfsource + 7;
            }
        }
    }
}

void hoamap_parameters_slots(t_hoamap *x, short ac, t_atom *av)
{
    SourcesManager* temporySourceManager = NULL;
    temporySourceManager = new SourcesManager();
    if(ac && av && temporySourceManager)
    {
        long slotIndex = -1;
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == hoa_sym_slot)
            {
                x->f_source_preset->storeSouceManagerAtSlot(temporySourceManager, slotIndex);
                temporySourceManager->setExistence(0);
                temporySourceManager->setExistence(1);
                slotIndex = atom_getlong(av+i+1);
            }
            else if(atom_getsym(av+i) == hoa_sym_source)
            {
                temporySourceManager->sourceSetCartesian(atom_getlong(av+i+1), atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                temporySourceManager->sourceSetMute(atom_getlong(av+i+1), atom_getlong(av+i+4));
                temporySourceManager->sourceSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                temporySourceManager->sourceSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+9)->s_name);
            }
            if(atom_getsym(av+i) == hoa_sym_group)
            {
                long numberOfsource = atom_getlong(av+i+2);
                for (int j = 0; j < numberOfsource; j++)
                {
                    temporySourceManager->groupSetSource(atom_getlong(av+i+1), atom_getlong(av+i+3+j));
                }
                if(atom_getlong(av+i+3+numberOfsource) == 1)
                    temporySourceManager->groupSetMute(atom_getlong(av+i+1), 1);
                temporySourceManager->groupSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+4+numberOfsource), atom_getfloat(av+i+5+numberOfsource), atom_getfloat(av+i+6+numberOfsource), atom_getfloat(av+i+7+numberOfsource));
                temporySourceManager->groupSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+8+numberOfsource)->s_name);
            }
        }
        x->f_source_preset->storeSouceManagerAtSlot(temporySourceManager, slotIndex);
        delete temporySourceManager;
    }
}

void hoamap_parameters_trajectory(t_hoamap *x, short ac, t_atom *av)
{
    SourcesManager* temporySourceManager = NULL;
    temporySourceManager = new SourcesManager();
    if(ac && av && temporySourceManager)
    {
        long slotIndex = -1;
        for(long i = 0; i < ac; i++)
        {
            if(atom_getsym(av+i) == hoa_sym_slot)
            {
                x->f_source_trajectory->storeSouceManagerAtSlot(temporySourceManager, slotIndex);
                temporySourceManager->setExistence(0);
                temporySourceManager->setExistence(1);
                slotIndex = atom_getlong(av+i+1);
            }
            else if(atom_getsym(av+i) == hoa_sym_source)
            {
                temporySourceManager->sourceSetCartesian(atom_getlong(av+i+1), atom_getfloat(av+i+2), atom_getfloat(av+i+3));
                temporySourceManager->sourceSetMute(atom_getlong(av+i+1), atom_getlong(av+i+4));
                temporySourceManager->sourceSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+5), atom_getfloat(av+i+6), atom_getfloat(av+i+7), atom_getfloat(av+i+8));
                temporySourceManager->sourceSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+9)->s_name);
            }
            if(atom_getsym(av+i) == hoa_sym_group)
            {
                long numberOfsource = atom_getlong(av+i+2);
                for (int j = 0; j < numberOfsource; j++)
                {
                    temporySourceManager->groupSetSource(atom_getlong(av+i+1), atom_getlong(av+i+3+j));
                }
                if(atom_getlong(av+i+3+numberOfsource) == 1)
                    temporySourceManager->groupSetMute(atom_getlong(av+i+1), 1);
                temporySourceManager->groupSetColor(atom_getlong(av+i+1), atom_getfloat(av+i+4+numberOfsource), atom_getfloat(av+i+5+numberOfsource), atom_getfloat(av+i+6+numberOfsource), atom_getfloat(av+i+7+numberOfsource));
                temporySourceManager->groupSetDescription(atom_getlong(av+i+1), atom_getsym(av+i+8+numberOfsource)->s_name);
            }
        }
        x->f_source_trajectory->storeSouceManagerAtSlot(temporySourceManager, slotIndex);
        delete temporySourceManager;
    }
}

t_max_err hoamap_zoom(t_hoamap *x, t_object *attr, long argc, t_atom *argv)
{
    if(argc >= 1 && argv && atom_gettype(argv) == A_FLOAT)
            x->f_zoom_factor = clip_minmax(atom_getfloat(argv), MIN_ZOOM, MAX_ZOOM);
    
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_background_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    return MAX_ERR_NONE;
}

t_max_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
    if (msg == hoa_sym_free)
    {
		if (sender == x->f_patcher)
        {
			x->f_patcher = NULL;
            x->f_textfield = NULL;
            x->f_colorpicker = NULL;
        }
	}
    else if (msg == hoa_sym_endeditbox)
    {
        if(x->f_textfield)
            object_free(x->f_textfield);
        if(x->f_patcher)
            object_free(x->f_patcher);
    }
    else if(msg == hoa_sym_text)
    {
        if (sender == x->f_textfield)
        {
            if(x->f_index_of_source_to_color > -1)
            {
                x->f_source_manager->sourceSetDescription(x->f_index_of_source_to_color, (char *)data);
                jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
                object_notify(x, hoa_sym_modified, NULL);
            }
            else if(x->f_index_of_group_to_color > -1)
            {
                x->f_source_manager->groupSetDescription(x->f_index_of_group_to_color, (char *)data);
                jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
                object_notify(x, hoa_sym_modified, NULL);
            }
        }
        jbox_redraw((t_jbox *)x);
    }
	if (msg == hoa_sym_attr_modified)
    {
        if (sender == x->f_colorpicker)
        {
            t_atom *av = NULL;
            long    ac = 0;

            name = (t_symbol *)object_method(data, hoa_sym_getname);
            if(name == gensym("currentcolor"))
            {
                object_attr_getvalueof(sender, name, &ac, &av);
                if (ac && av)
                {
                    if(x->f_index_of_source_to_color > -1)
                    {
                        x->f_source_manager->sourceSetColor(x->f_index_of_source_to_color, atom_getfloat(av), atom_getfloat(av+1), atom_getfloat(av+2), atom_getfloat(av+3));
                        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
                        object_notify(x, hoa_sym_modified, NULL);
                    }
                    else if(x->f_index_of_group_to_color > -1)
                    {
                        x->f_source_manager->groupSetColor(x->f_index_of_group_to_color, atom_getfloat(av), atom_getfloat(av+1), atom_getfloat(av+2), atom_getfloat(av+3));
                        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
                        object_notify(x, hoa_sym_modified, NULL);
                    }
                    else if(x->f_index_of_source_to_color == -2)
                    {
                        x->f_color_bg.red = atom_getfloat(av);
                        x->f_color_bg.green = atom_getfloat(av+1);
                        x->f_color_bg.blue = atom_getfloat(av+2);
                        x->f_color_bg.alpha = atom_getfloat(av+3);
                        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_background_layer);
                        object_notify(x, hoa_sym_modified, NULL);
                    }
                    
                }
            }
        }
        else
        {
            name = (t_symbol *)object_method((t_object *)data, hoa_sym_getname);
            if(name == hoa_sym_bgcolor)
            {
                jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_background_layer);
            }
            else if(name == gensym("fontname") || name == gensym("fontface") || name == gensym("fontsize"))
            {
                jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
                jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
            }
            else if(name == gensym("zoom"))
            {
                jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_background_layer);
                jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
                jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
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
    atom_setsym(av+1, hoa_sym_mute);
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
        atom_setsym(av+1, hoa_sym_polar);
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
        atom_setsym(av+1, hoa_sym_cartesian);
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

void hoamap_infos(t_hoamap *x)
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
    atom_setsym(avNumber, hoa_sym_source);
    atom_setsym(avNumber+1, hoa_sym_number);
    atom_setlong(avNumber+2, numberOfSource);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);
    
    avIndex = new t_atom[numberOfSource+2];
    atom_setsym(avIndex, hoa_sym_source);
    atom_setsym(avIndex+1, hoa_sym_index);
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
    
    atom_setsym(avMute, hoa_sym_source);
    atom_setsym(avMute+1, hoa_sym_mute);
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
    atom_setsym(avNumber, hoa_sym_group);
    atom_setsym(avNumber+1, hoa_sym_number);
    atom_setlong(avNumber+2, numberOfGroups);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);
    
    avIndex = new t_atom[numberOfGroups+2];
    atom_setsym(avIndex, hoa_sym_group);
    atom_setsym(avIndex+1, hoa_sym_index);
    for(int i = 0, j = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
    {
        if(x->f_source_manager->groupGetExistence(i))
        {
            atom_setlong(avIndex+j+2, i);
            j++;
            avSource = new t_atom[x->f_source_manager->groupGetNumberOfSources(i)+3];
            atom_setsym(avSource, hoa_sym_group);
            atom_setsym(avSource+1, hoa_sym_source);
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
    
    atom_setsym(avMute, hoa_sym_group);
    atom_setsym(avMute+1, hoa_sym_mute);
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
    atom_setsym(avNumber, hoa_sym_slot);
    atom_setsym(avNumber+1, hoa_sym_number);
    atom_setlong(avNumber+2, numberOfSlots);
    outlet_list(x->f_out_infos, 0L, 3, avNumber);

    avIndex = new t_atom[numberOfSlots+2];
    atom_setsym(avIndex, hoa_sym_slot);
    atom_setsym(avIndex+1, hoa_sym_index);
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

void hoamap_paint(t_hoamap *x, t_object *view)
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

void draw_background(t_hoamap *x,  t_object *view, t_rect *rect)
{
    t_jgraphics *g;
    t_jrgba black, white;
    double w = rect->width;
    double h = rect->height;
    t_pt ctr = {w*0.5, h*0.5};
    double maxctr = max(w, h)*0.5;
    
    double contrastBlack = 0.12;
    double contrastWhite = 0.08;
    black = white = x->f_color_bg;
	
	vector_add(3, (double*)&black, -contrastBlack);
	vector_clip_minmax(3, (double*)&black, 0., 1.);
	
	vector_add(3, (double*)&white, contrastWhite);
	vector_clip_minmax(3, (double*)&white, 0., 1.);
	
	g = jbox_start_layer((t_object *)x, view, hoa_sym_background_layer, w, h);
	
	if (g)
    {
        jgraphics_set_source_jrgba(g, &x->f_color_bg);
        jgraphics_set_line_width(g, 1);
        jgraphics_arc(g, ctr.x, ctr.y, maxctr * (1./MIN_ZOOM * x->f_zoom_factor),  0., HOA_2PI);
        jgraphics_fill(g);
        
        double ecart = x->f_zoom_factor * maxctr;
        if(ecart < 10 && ecart >= 5) ecart *= 4;
        else if(ecart < 5 && ecart > 2.5) ecart *= 8;
        else if(ecart < 2.5) ecart *= 16;
        ecart = int(ecart);
        
		for(double i = 0; i < maxctr; i += ecart)
        {
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_move_to(g, 0., long(ctr.y - i) + 0.5);
            jgraphics_line_to(g, w,  long(ctr.y - i) + 0.5);
            jgraphics_move_to(g, 0., long(ctr.y + i) + 0.5);
            jgraphics_line_to(g, w,  long(ctr.y + i) + 0.5);
            jgraphics_move_to(g, long(ctr.x - i) + 0.5, 0.);
            jgraphics_line_to(g, long(ctr.x - i) + 0.5, w);
            jgraphics_move_to(g, long(ctr.x + i) + 0.5, 0.);
            jgraphics_line_to(g, long(ctr.x + i) + 0.5, w);
            jgraphics_set_line_width(g, 1);
            jgraphics_scale(g, 0.5, 0.5);
            jgraphics_stroke(g);
            jgraphics_scale(g, 2, 2);
            
            jgraphics_set_line_width(g, 1);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_move_to(g, 0. - 0.5, long(ctr.y - i) - 0.5);
            jgraphics_line_to(g, w - 0.5, long(ctr.y - i) - 0.5);
            jgraphics_move_to(g, 0. - 0.5, long(ctr.y + i) - 0.5);
            jgraphics_line_to(g, w - 0.5, long(ctr.y + i) - 0.5);
            jgraphics_move_to(g, long(ctr.x - i) - 0.5, 0. - 0.5);
            jgraphics_line_to(g, long(ctr.x - i) - 0.5, w - 0.5);
            jgraphics_move_to(g, long(ctr.x + i) - 0.5, 0. - 0.5);
            jgraphics_line_to(g, long(ctr.x + i) - 0.5, w - 0.5);
            jgraphics_set_line_width(g, 2);
            jgraphics_scale(g, 0.25, 0.25);
            jgraphics_stroke(g);
            jgraphics_scale(g, 4, 4);
        }
        
        /* Circles */
        double radius = x->f_zoom_factor * (maxctr*2) / 10.;
        for(int i = 5; i > 0; i--)
        {
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &white);
            jgraphics_arc(g, long(ctr.x)+0.5, long(ctr.y)+0.5, (double)i * radius - 1,  0., HOA_2PI);
            jgraphics_scale(g, 0.5, 0.5);
            jgraphics_stroke(g);
            jgraphics_scale(g, 2, 2);
            
            jgraphics_set_line_width(g, 2);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_arc(g, long(ctr.x) - 0.5, long(ctr.y) - 0.5, (double)i * radius - 1,  0., HOA_2PI);
            jgraphics_scale(g, 0.5, 0.5);
            jgraphics_stroke(g);
            jgraphics_scale(g, 2, 2);
        }
        
		jbox_end_layer((t_object*)x, view, hoa_sym_background_layer);
	}
	jbox_paint_layer((t_object *)x, view, hoa_sym_background_layer, 0., 0.);
}

void draw_sources(t_hoamap *x,  t_object *view, t_rect *rect)
{
	int i;
	double fontSize;
	t_jtextlayout *jtl;
	t_jrgba sourceColor;
	char description[250];
	double descriptionPositionX;
    double descriptionPositionY;
	double sourcePositionX;
    double sourcePositionY;
	
	double* color;
    
    double w = rect->width;
    double h = rect->height;
    t_pt ctr = {w*0.5, h*0.5};
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, hoa_sym_sources_layer, rect->width, rect->height);
	
    x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    x->f_size_source = jbox_get_fontsize((t_object *)x) / 2.;
    fontSize = jbox_get_fontsize((t_object *)x);
	
	if (g)
    {
        jtl = jtextlayout_create();
        jgraphics_set_line_width(g, x->f_size_source * 0.2);
		for(i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
        {
            if(x->f_source_manager->sourceGetExistence(i))
            {
                sourcePositionX = (x->f_source_manager->sourceGetAbscissa(i) * x->f_zoom_factor + 1.) * ctr.x;
                sourcePositionY = (-x->f_source_manager->sourceGetOrdinate(i) * x->f_zoom_factor + 1.) * ctr.y;
				
				color = x->f_source_manager->sourceGetColor(i);
				jrgba_set(&sourceColor, color[0], color[1], color[2], color[3]);
                
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
                    jgraphics_set_source_jrgba(g, &x->f_color_selection);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.5,  0., HOA_2PI);
                    jgraphics_fill(g);
                    
                    for(int index = 0; index < x->f_source_manager->sourceGetNumberOfGroups(i); index++)
                    {
                        jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                        int groupIndex = x->f_source_manager->sourceGetGroupIndex(i, index);
                        double groupPositionX = (x->f_source_manager->groupGetAbscissa(groupIndex) * x->f_zoom_factor + 1.) * ctr.x;
                        double groupPositionY = (-x->f_source_manager->groupGetOrdinate(groupIndex) * x->f_zoom_factor + 1.) * ctr.y;
                        jgraphics_line_to(g, groupPositionX, groupPositionY);
                        jgraphics_stroke(g);
                    }
                }
                              
                if(!x->f_source_manager->sourceGetMute(i))
                {
                    jgraphics_set_source_jrgba(g, &sourceColor); 
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 0.6,  0., HOA_2PI);
                    jgraphics_fill(g);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., HOA_2PI);
                    jgraphics_stroke(g);
                }
                if(x->f_source_manager->sourceGetMute(i))
                {
                    jgraphics_set_source_jrgba(g, &sourceColor);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 0.6,  0., HOA_2PI);
                    jgraphics_fill(g);
                    t_jrgba red = {1., 0., 0., 1.};
                    jgraphics_set_source_jrgba(g, &red); 
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., HOA_2PI);
                    jgraphics_stroke(g);
                    jgraphics_move_to(g, sourcePositionX + abscissa(x->f_size_source * 1., HOA_PI2 / 2.), sourcePositionY + ordinate(x->f_size_source * 1., HOA_PI2 / 2.));
                    jgraphics_line_to(g, sourcePositionX + abscissa(x->f_size_source * 1., HOA_PI2 * 5. / 2.), sourcePositionY + ordinate(x->f_size_source * 1., HOA_PI * 5. / 4.));
                    jgraphics_stroke(g);
                }
                
            }
        }
		jtextlayout_destroy(jtl);

		jbox_end_layer((t_object*)x, view, hoa_sym_sources_layer);
    }
	jbox_paint_layer((t_object *)x, view, hoa_sym_sources_layer, 0., 0.);
}


void draw_groups(t_hoamap *x,  t_object *view, t_rect *rect)
{
	int i;
	double fontSize;
	t_jtextlayout *jtl;
	t_jrgba sourceColor;    
	char description[250] = {0};
	double descriptionPositionX;
    double descriptionPositionY;
	double sourcePositionX;
    double sourcePositionY;
	
	double* color;
    
    double w = rect->width;
    double h = rect->height;
    t_pt ctr = {w*0.5, h*0.5};
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, hoa_sym_groups_layer, w, h);
	x->jfont = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    x->f_size_source = jbox_get_fontsize((t_object *)x) / 2.;
    fontSize = jbox_get_fontsize((t_object *)x);
	
	if (g)
    {
        jtl = jtextlayout_create();
        jgraphics_set_line_width(g, x->f_size_source * 0.2);
		for(i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i))
            {
                sourcePositionX = (x->f_source_manager->groupGetAbscissa(i) * x->f_zoom_factor + 1.) * ctr.x;
                sourcePositionY = (-x->f_source_manager->groupGetOrdinate(i) * x->f_zoom_factor + 1.) * ctr.y;
                
				color = x->f_source_manager->groupGetColor(i);
				jrgba_set(&sourceColor, color[0], color[1], color[2], color[3]);
                
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
                    //x->f_color_selection
                    jgraphics_set_source_jrgba(g, &x->f_color_selection);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.5,  0., HOA_2PI);
                    jgraphics_fill(g);
                    
                    for(int index = 0; index < x->f_source_manager->groupGetNumberOfSources(i); index++)
                    {
                        jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                        int groupIndex = x->f_source_manager->groupGetSourceIndex(i, index);
                        double groupPositionX = (x->f_source_manager->sourceGetAbscissa(groupIndex) * x->f_zoom_factor + 1.) * ctr.x;
                        double groupPositionY = (-x->f_source_manager->sourceGetOrdinate(groupIndex) * x->f_zoom_factor + 1.) * ctr.y;
                        jgraphics_line_to(g, groupPositionX, groupPositionY);
                        jgraphics_stroke(g);
                    }
                }
                jgraphics_set_source_jrgba(g, &sourceColor);
                for(int j = 1; j < 4; j += 2)
                {
                    jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                    jgraphics_line_to(g, sourcePositionX + abscissa(x->f_size_source * 1., HOA_2PI * j / 4. + HOA_PI2 / 2.), sourcePositionY + ordinate(x->f_size_source * 1., HOA_2PI * j / 4. + HOA_PI2 / 2.));
                }
                jgraphics_stroke(g);
                if(!x->f_source_manager->groupGetMute(i))
                {
                    jgraphics_set_source_jrgba(g, &sourceColor);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source * 1.,  0., HOA_2PI);
                    jgraphics_stroke(g);
                
                    for(int j = 0; j < 2; j++)
                    {
                        jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                        jgraphics_line_to(g, sourcePositionX + abscissa(x->f_size_source * 1., HOA_2PI * j / 2. + HOA_PI2 / 2.), sourcePositionY + ordinate(x->f_size_source * 1., HOA_2PI * j / 2. + HOA_PI2 / 2.));
                    }
                }
                jgraphics_stroke(g);
                if(x->f_source_manager->groupGetMute(i))
                {
                    t_jrgba red = {1., 0., 0., 1.};
                    jgraphics_set_source_jrgba(g, &red);
                    jgraphics_arc(g, sourcePositionX, sourcePositionY, x->f_size_source,  0., HOA_2PI);
                    jgraphics_stroke(g);
                    for(int j = 0; j < 2; j++)
                    {
                        jgraphics_move_to(g, sourcePositionX, sourcePositionY);
                        jgraphics_line_to(g, sourcePositionX + abscissa(x->f_size_source * 1., HOA_2PI * j / 2. + HOA_PI2 / 2.), sourcePositionY + ordinate(x->f_size_source * 1., HOA_2PI * j / 2. + HOA_PI2 / 2.));
                    }
                    jgraphics_stroke(g);
                }
                 
            }
        }
		jtextlayout_destroy(jtl);
        
		jbox_end_layer((t_object*)x, view, hoa_sym_groups_layer);
    }
	jbox_paint_layer((t_object *)x, view, hoa_sym_groups_layer, 0., 0.);
}


void draw_rect_selection(t_hoamap *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g;
    t_jrgba strokecolor = x->f_color_selection;
    strokecolor.alpha = 0.8;
	t_rect sel;
    
    g = jbox_start_layer((t_object *)x, view, hoa_sym_rect_selection_layer, rect->width, rect->height);
    
	if (g)
    {
		if (x->f_rect_selection_exist)
        {
			sel.x = floor(x->f_rect_selection.x) + 0.5;
			sel.y = floor(x->f_rect_selection.y) + 0.5;
			sel.width = x->f_rect_selection.width;
			sel.height = x->f_rect_selection.height;
			
			jgraphics_set_source_jrgba(g, &x->f_color_selection);
			jgraphics_rectangle(g, sel.x, sel.y, sel.width, sel.height);
			jgraphics_fill(g);
			
			jgraphics_set_source_jrgba(g, &strokecolor);
			jgraphics_set_line_width(g, 1);
			jgraphics_rectangle(g, sel.x, sel.y, sel.width, sel.height);
			jgraphics_stroke(g);
		}
		jbox_end_layer((t_object*)x, view, hoa_sym_rect_selection_layer);
	}
	jbox_paint_layer((t_object *)x, view, hoa_sym_rect_selection_layer, 0., 0.);
}

/**********************************************************/
/*                   Souris et clavier                    */
/**********************************************************/

void hoamap_mousedown(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    double maxwh = max(x->rect.width, x->rect.height);
    double ditanceSelected = (x->f_size_source / maxwh * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    
    x->f_rect_selection_exist = -1;
    x->f_rect_selection.width = x->f_rect_selection.height = 0.;
        
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && distance(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = distance(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && distance(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = distance(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
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
                    atom_setsym(av+1, hoa_sym_mute);
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
                    atom_setsym(av+1, hoa_sym_mute);
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
            jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
            jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
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
                    atom_setsym(av+1, hoa_sym_mute);
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
            jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
            jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
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


void hoamap_mousedrag(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt cursor;
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
			x->f_source_manager->sourceSetAngle(x->f_index_of_selected_source, azimuth(cursor.x, cursor.y) - HOA_PI2);

		 // Radius
#ifdef _WINDOWS
		else if(modifiers == 18) // Shift
#else
		else if(modifiers == 18 || modifiers == 274)
#endif
            x->f_source_manager->sourceSetRadius(x->f_index_of_selected_source, radius(cursor.x, cursor.y));
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
            x->f_source_manager->groupSetRelativeAngle(x->f_index_of_selected_group, azimuth(cursor.x, cursor.y));
		 // Radius
#ifdef _WINDOWS
		else if(modifiers == 18) // Shift
#else
		else if(modifiers == 18 || modifiers == 274)
#endif
            x->f_source_manager->groupSetRelativeRadius(x->f_index_of_selected_group, radius(cursor.x, cursor.y));
		 // Angle + radius
#ifdef _WINDOWS
		else if(modifiers == 26) // Shift
#else
		else if (modifiers == 17)
#endif
            x->f_source_manager->groupSetRelativePolar(x->f_index_of_selected_group, radius(cursor.x, cursor.y), azimuth(cursor.x, cursor.y));
        else
            x->f_source_manager->groupSetCartesian(x->f_index_of_selected_group, cursor.x, cursor.y);            
    }
    else
    {
		x->f_rect_selection.width = pt.x - x->f_rect_selection.x;
		x->f_rect_selection.height = pt.y - x->f_rect_selection.y;
		jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_rect_selection_layer);
		jbox_redraw((t_jbox *)x);
    }
    
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    object_notify(x, hoa_sym_modified, NULL);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    jbox_redraw((t_jbox *)x);
    hoamap_bang(x);
}

void hoamap_mouseup(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
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
    
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_rect_selection_layer);
    jbox_redraw((t_jbox *)x);
}

void hoamap_mousewheel(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	if (modifiers == eAltKey)
    {
		double newZoom = x->f_zoom_factor + y_inc / 100.;
        x->f_zoom_factor = clip_minmax(newZoom, MIN_ZOOM, MAX_ZOOM);
        object_notify(x, hoa_sym_modified, NULL);
        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_background_layer);
        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
        jbox_redraw((t_jbox *)x);
	}
}

void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_pt cursor;
    cursor.x = ((pt.x / x->rect.width * 2.) - 1.) / x->f_zoom_factor;
    cursor.y = ((-pt.y / x->rect.height * 2.) + 1.) / x->f_zoom_factor;
    double maxwh = max(x->rect.width, x->rect.height);
    double ditanceSelected = (x->f_size_source / maxwh * 2.) / x->f_zoom_factor;
    x->f_cursor_position.x = cursor.x;
    x->f_cursor_position.y = cursor.y;
    
    x->f_index_of_selected_source = -1;
    x->f_index_of_selected_group = -1;
    for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfSource(); i++)
    {
        if(x->f_source_manager->sourceGetExistence(i) && distance(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
        {
            ditanceSelected = distance(x->f_source_manager->sourceGetAbscissa(i), x->f_source_manager->sourceGetOrdinate(i), cursor.x, cursor.y);
            x->f_index_of_selected_source = i;
        }
    }
    if(x->f_index_of_selected_source == -1)
    {
        for(int i = 0; i <= x->f_source_manager->getMaximumIndexOfGroup(); i++)
        {
            if(x->f_source_manager->groupGetExistence(i) && distance(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y) <= ditanceSelected)
            {
                ditanceSelected = distance(x->f_source_manager->groupGetAbscissa(i), x->f_source_manager->groupGetOrdinate(i), cursor.x, cursor.y);
                x->f_index_of_selected_group = i;
            }
        }
    }
    
    if(x->f_index_of_selected_group >= 0 || x->f_index_of_selected_source >= 0)
        jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_POINTINGHAND);
    else jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_ARROW);
    
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
    jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
    jbox_redraw((t_jbox *)x);
}

void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

long hoamap_key(t_hoamap *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
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
        
        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_sources_layer);
        jbox_invalidate_layer((t_object *)x, NULL, hoa_sym_groups_layer);
        jbox_redraw((t_jbox *)x);
        
        filter = 1;
	}
	return filter;
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
    x->f_patcher = (t_object *)object_new_typed(CLASS_NOBOX,hoa_sym_jpatcher,1, &a);
    freeobject((t_object *)dico);
    
    x->f_colorpicker = newobject_sprintf(x->f_patcher, "@maxclass colorpicker @patching_rect 0 0 128 32");
    object_attach_byptr_register(x, x->f_patcher, CLASS_NOBOX);
    object_attach_byptr_register(x, x->f_colorpicker, CLASS_BOX);
    
    object_method(x->f_colorpicker, hoa_sym_bang);
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
    
    int posX, posY;
    jmouse_getposition_global(&posX, &posY);
    
    sprintf(parsebuf,"@defrect %i %i 256 32 @openrect 0 0 256 32 @title Description @enablehscroll 0 @enablevscroll 0 @presentation 0 @toolbarvisible 0 @retain 1\"\"", posX, posY);
    atom_setparse(&ac,&av,parsebuf);
    attr_args_dictionary(dico,ac,av);
    atom_setobj(&a,dico);
    sysmem_freeptr(av);
    x->f_patcher = (t_object *)object_new_typed(CLASS_NOBOX,hoa_sym_jpatcher,1, &a);
    freeobject((t_object *)dico);
    
    x->f_textfield = newobject_sprintf(x->f_patcher, "@maxclass hoa.textfield @patching_rect 0 0 256 32");
    
    object_attach_byptr_register(x, x->f_patcher, CLASS_NOBOX);
    object_attach_byptr_register(x, x->f_textfield, CLASS_NOBOX);
    
    object_method(x->f_patcher,hoa_sym_noedit, 1);
    object_method(x->f_patcher,hoa_sym_vis);
}

/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/

void hoa_textfield_init(void)
{
	t_class *c;	
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
        | JBOX_GROWBOTH
        | JBOX_TEXTFIELD
		;
		
		jbox_new(&x->j_box, flags, argc, argv);
		x->j_box.b_firstin = (t_object*) x;
        x->j_patcher = NULL;
        x->j_patcherview = NULL;
		t_jrgba textcolor = {0., 0., 0., 1.};
		textfield = jbox_get_textfield((t_object*) x);
		if (textfield)
        {
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
	object_obex_lookup(x,hoa_sym_P, &p);
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
	object_method(patcherview, hoa_sym_insertboxtext, x, buff);
    long size	= 0;
	char *text	= NULL;
	t_object *textfield = jbox_get_textfield((t_object *)x);
	object_method(textfield, hoa_sym_gettextptr, &text, &size);
    object_notify(x, hoa_sym_text, text);
	jbox_redraw((t_jbox *)x);
	return 1;
}

long textfield_keyfilter(t_textfield *x, t_object *patcherview, long *keycode, long *modifiers, long *textcharacter)
{
	t_atom arv;
	long rv = 1;
	long k = *keycode;
	
	if (k == JKEY_TAB || k == JKEY_ENTER || k == JKEY_RETURN || k == JKEY_ESC) {
		object_method_typed(patcherview, hoa_sym_endeditbox, 0, NULL, &arv);
		rv = 0;
	}
    long size	= 0;
    char *text	= NULL;
    t_object *textfield = jbox_get_textfield((t_object *)x);
    object_method(textfield, hoa_sym_gettextptr, &text, &size);
    object_notify(x, hoa_sym_text, text);
    if (!rv) object_notify(x, hoa_sym_endeditbox, NULL);
	return rv;
}

void textfield_enter(t_textfield *x)
{
	long size	= 0;
	char *text	= NULL;
	t_object *textfield = jbox_get_textfield((t_object *)x);
	object_method(textfield, hoa_sym_gettextptr, &text, &size);
    object_notify(x, hoa_sym_text, text);
}

void textfield_paint(t_textfield *x, t_object *view)
{
	t_rect rect;
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(view);
    jbox_get_rect_for_view((t_object*) x, view, &rect);
    if(x->j_patcher == NULL)
    {
        object_obex_lookup(x,hoa_sym_P, &x->j_patcher);
        object_attach_byptr_register(x, x->j_patcher, CLASS_NOBOX);
    }
    if(x->j_patcherview == NULL)
    {
        x->j_patcherview = object_attr_getobj(x->j_patcher, hoa_sym_firstview);
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
		if (msg == hoa_sym_free)
        {
			x->j_patcher = NULL;
            x->j_patcherview = NULL;
        }
    }
    if(sender == x->j_patcherview)
    {
        if (msg == hoa_sym_attr_modified)
        {
            t_symbol* attrname = (t_symbol *)object_method(data, hoa_sym_getname);
            if (attrname == hoa_sym_rect)
            {
                t_atom *av = NULL;
                long    ac = 0;
                object_attr_getvalueof(x->j_patcherview, hoa_sym_rect, &ac, &av);
                if (ac && av)
                {
                    atom_setlong(av, 0);
                    atom_setlong(av+1, 0);
                    object_method(x, hoa_sym_rect, ac, av);
                    freebytes(av, sizeof(t_atom) * ac);
                }
                jbox_redraw((t_jbox *)x);
            }
        }
    }
    return MAX_ERR_NONE;
}




