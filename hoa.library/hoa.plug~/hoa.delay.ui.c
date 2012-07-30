/*
 *  hoa.delay.ui.c
 *  hoa.delay~
 *
 *  Created by Pierre G. on 30/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "hoa.delay.ui.h"

void delay_ui_classinit(void)
{
	t_class *c = class_new("delay_ui", (method)delay_ui_new, (method)delay_ui_free, sizeof(t_delay_ui), 0L, A_GIMME, 0L);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	
	jbox_initclass(c, 0);
	class_addmethod(c, (method)delay_ui_paint,		"paint",		A_CANT, 0);
	class_addmethod(c, (method)delay_ui_mousedown,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)delay_ui_mousedrag,	"mousedrag",	A_CANT, 0);
	class_addmethod(c, (method)jbox_notify,			"notify",	A_CANT, 0);
	
	CLASS_ATTR_RGBA(c, "oncolor", 0, t_delay_ui, u_oncolor);
	CLASS_ATTR_PAINT(c, "oncolor", 0);
	CLASS_ATTR_RGBA(c, "offcolor", 0, t_delay_ui, u_offcolor);
	CLASS_ATTR_PAINT(c, "offcolor", 0);
	
	class_register(CLASS_BOX, c);
	
	s_delay_ui_class = c;
}


void *delay_ui_new(t_symbol *s, long argc, t_atom *argv)
{
	t_delay_ui *x = NULL;
	t_max_err err = MAX_ERR_GENERIC;
	t_dictionary *d;
	long flags;
	
	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_delay_ui *) object_alloc(s_delay_ui_class);
	flags = 0 
	| JBOX_DRAWFIRSTIN 
	//		| JBOX_NODRAWBOX
	| JBOX_DRAWINLAST
	| JBOX_TRANSPARENT	
	//		| JBOX_NOGROW
	//		| JBOX_GROWY
	| JBOX_GROWBOTH
	//		| JBOX_HILITE
	//		| JBOX_BACKGROUND
	//		| JBOX_TEXTFIELD
	| JBOX_DRAWBACKGROUND
	| JBOX_DEFAULTNAMES
	;
	
	err = jbox_new(&x->u_box, flags, argc, argv); 
	
	x->u_box.b_firstin = (t_object*) x;
	
	delay_ui_clear(x);
	attr_dictionary_process(x, d);
	jbox_ready(&x->u_box);
	
	return x;
}

void delay_ui_clear(t_delay_ui *x)
{
	long i;
	
	for (i = 0; i < SCRIPTO_UI_CELLS; i++)
		x->u_state[i] = 0;
}

void delay_ui_paint(t_delay_ui *x, t_object *patcherview)
{
	t_jgraphics *g;
	t_rect r;
	long i, j;
	
	g = (t_jgraphics*) patcherview_get_jgraphics(patcherview); 
	for (i = 0; i < SCRIPTO_UI_ROWS; i++) 
	{
		for (j = 0; j < SCRIPTO_UI_COLS; j++) 
		{
			delay_ui_makerect(x, i, j, &r);
			jgraphics_set_source_jrgba(g, x->u_state[(i * SCRIPTO_UI_COLS) + j]? &x->u_oncolor : &x->u_offcolor);
			jgraphics_rectangle_fill_fast(g, r.x, r.y, r.width, r.height);
		}
	}
}

void delay_ui_makerect(t_delay_ui *x, long row, long col, t_rect *r)
{
	r->y = row * 10;
	r->x = col * 10;
	r->width = 10;
	r->height = 10;
}

void delay_ui_pt2rc(t_delay_ui *x, t_pt pt, long *row, long *col)
{
	*row = CLIP(pt.y / 10, 0, SCRIPTO_UI_ROWS-1);
	*col = CLIP(pt.x / 10, 0, SCRIPTO_UI_COLS-1);
}

void delay_ui_mousedown(t_delay_ui *x, t_object *patcherview, t_pt pt, long modifiers)
{
	long row, col, index;
	t_celldesc desc;
	
	delay_ui_pt2rc(x, pt, &row, &col);
	index = (row * SCRIPTO_UI_COLS) + col;
	x->u_dragstate = !x->u_state[index];
	x->u_state[index] = x->u_dragstate;
	desc.row = row;
	desc.col = col;
	desc.state = x->u_dragstate;
	object_notify((t_object *)x, gensym("cellclicked"), (void *)&desc);
	jbox_redraw((t_jbox *)x);
}

void delay_ui_mousedrag(t_delay_ui *x, t_object *patcherview, t_pt pt, long modifiers)
{
	long row, col, index;
	char state;
	
	delay_ui_pt2rc(x, pt, &row, &col);
	index = (row * SCRIPTO_UI_COLS) + col;
	state = x->u_state[index];
	if (state != x->u_dragstate) {		// optimization: only redraw if state is changing
		x->u_state[index] = x->u_dragstate;
		jbox_redraw((t_jbox *)x);
	}
}

void delay_ui_free(t_delay_ui *x)
{
	jbox_free((t_jbox *)x);
}


