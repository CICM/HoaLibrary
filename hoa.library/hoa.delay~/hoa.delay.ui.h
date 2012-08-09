/*
 *  hoa.delay.ui.h
 *  hoa.delay~
 *
 *  Created by Pierre G. on 30/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"

#define SCRIPTO_UI_ROWS 40
#define SCRIPTO_UI_COLS 30
#define SCRIPTO_UI_CELLS (40 * 30)

typedef struct _celldesc {
	long row;
	long col;
	long state;
} t_celldesc;

typedef struct _delay_ui {
	t_jbox		u_box;
	char		u_state[SCRIPTO_UI_CELLS];
	t_jrgba		u_oncolor;
	t_jrgba		u_offcolor;
	char		u_dragstate;
} t_delay_ui;

static t_class	*s_delay_ui_class;

void delay_ui_classinit(void);
void *delay_ui_new(t_symbol *s, long argc, t_atom *argv);
void delay_ui_makerect(t_delay_ui *x, long row, long col, t_rect *r);
void delay_ui_pt2rc(t_delay_ui *x, t_pt pt, long *row, long *col);
void delay_ui_clear(t_delay_ui *x);
void delay_ui_paint(t_delay_ui *x, t_object *patcherview);
void delay_ui_mousedown(t_delay_ui *x, t_object *patcherview, t_pt pt, long modifiers);
void delay_ui_mousedrag(t_delay_ui *x, t_object *patcherview, t_pt pt, long modifiers);
void delay_ui_free(t_delay_ui *x);
