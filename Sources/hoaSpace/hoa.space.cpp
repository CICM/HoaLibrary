/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#include "AmbisonicRecomposer.h"
#include "AmbisonicProjector.h"
#include "AmbisonicViewer.h"
#include "cicmTools.h"

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

typedef struct  _control 
{
	t_jbox		j_box;
	void*		f_out;
	void*		f_outInfos;

	long		f_mode;
	long		f_order;
	int			f_shadow;
	long		f_optimMode;
	double		f_azimuth;
	double		f_azimuthOffset;
	double		f_wide;
	double		f_wideOffset;

	t_jrgba		f_colorBackground;
	t_jrgba		f_borderboxcolor;
	t_jrgba		f_gradientcolor;
	t_jrgba		f_colorText;
	t_jrgba		f_colorCircle;
	t_jrgba		f_colorCircleInner;
	t_jrgba		f_colorCircleShadow;
	t_jrgba		f_colorNegatif;
	t_jrgba		f_colorPositif;
	t_jrgba		f_colorContrib;

	t_rect		f_center;
	double		f_rayonGlobal;
	double		f_rayonAngle;
	double		f_rayonCircle;
	double		f_fontsize;

	AmbisonicViewer*        f_viewer;
    ambisonicRecomposer*    f_recomposer;
    ambisonicProjector*     f_projector;
	double*                 f_harmonicsValues;
    double*                 f_microphonesValues;

} t_control;

t_class *control_class;

void *control_new(t_symbol *s, int argc, t_atom *argv);
void control_free(t_control *x);
void control_assist(t_control *x, void *b, long m, long a, char *s);

t_max_err control_notify(t_control *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
long control_oksize(t_control *x, t_rect *newrect);
void control_getdrawparams(t_control *x, t_object *patcherview, t_jboxdrawparams *params);
t_max_err order_set(t_control *x, t_object *attr, long argc, t_atom *argv);

/* Interaction ***************************************/
void control_mouse_down(t_control *x, t_object *patcherview, t_pt pt, long modifiers);
void control_mouse_drag(t_control *x, t_object *patcherview, t_pt pt, long modifiers);
void control_compute(t_control *x);

/* Paint *********************************************/
void control_paint(t_control *x, t_object *view);
void draw_background(t_control *x, t_object *view, t_rect *rect);
void draw_angle(t_control *x,  t_object *view, t_rect *rect);
void draw_harmonics(t_control *x,  t_object *view, t_rect *rect);
void draw_biggest_contribution(t_control *x, t_object *view, t_rect *rect);

int main()
{
	t_class *c;

	c = class_new("hoa.space", (method)control_new, (method)control_free, (short)sizeof(t_control), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	//jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH);

	class_addmethod(c, (method)control_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)control_paint,		"paint",		A_CANT,	0);
	class_addmethod(c, (method)control_notify,		"notify",		A_CANT, 0);
	class_addmethod(c, (method)control_getdrawparams, "getdrawparams", A_CANT, 0);
	class_addmethod(c, (method)control_oksize,		"oksize",		A_CANT, 0);
	class_addmethod(c, (method)control_mouse_down,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)control_mouse_down,	"mousedrag",	A_CANT, 0);
	
	CLASS_ATTR_DEFAULT				(c, "patching_rect", 0, "0 0 225 225");
	CLASS_ATTR_INVISIBLE			(c, "color", 0);
	CLASS_ATTR_INVISIBLE			(c, "textcolor", 0);
	
	CLASS_ATTR_LONG					(c, "shadow", 0, t_control, f_shadow);
	CLASS_ATTR_CATEGORY				(c, "shadow", 0, "Appearance");
	CLASS_ATTR_ORDER				(c, "shadow", 0, "1");
	CLASS_ATTR_STYLE_LABEL			(c, "shadow", 0, "onoff", "Draw Shadows");
	CLASS_ATTR_DEFAULT				(c, "shadow", 0, "1");
	CLASS_ATTR_SAVE					(c, "shadow", 1);

	CLASS_ATTR_LONG					(c, "order", 0, t_control, f_order);
	CLASS_ATTR_CATEGORY				(c, "order", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "order", 0, "1");
	CLASS_ATTR_LABEL				(c, "order", 0, "Ambisonic Order");
	CLASS_ATTR_ACCESSORS			(c, "order", NULL, order_set);
	CLASS_ATTR_FILTER_MIN			(c, "order", 1);
	CLASS_ATTR_DEFAULT				(c, "order", 0, "4");
	CLASS_ATTR_SAVE					(c, "order", 1);

	CLASS_ATTR_LONG					(c, "mode", 0, t_control, f_mode);
	CLASS_ATTR_CATEGORY				(c, "mode", 0, "Behavior");
	CLASS_ATTR_ORDER				(c, "mode", 0, "5");
	CLASS_ATTR_ENUMINDEX			(c, "mode", 0, "Absolute \" \"Relative");
	CLASS_ATTR_LABEL				(c, "mode", 0, "Interaction mode");
	CLASS_ATTR_FILTER_CLIP			(c, "mode", 0, 1);
	CLASS_ATTR_DEFAULT				(c, "mode", 0, "0.");
	CLASS_ATTR_SAVE					(c, "mode", 1);

	CLASS_ATTR_RGBA					(c, "bgcolor", 0, t_control, f_colorBackground);
	CLASS_ATTR_CATEGORY				(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "bgcolor", 0, "1. 1. 1. 1.");
	

	CLASS_ATTR_RGBA					(c, "cicolor", 0, t_control, f_colorCircle);
	CLASS_ATTR_CATEGORY				(c, "cicolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "cicolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "cicolor", 0, "Circle Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "cicolor", 0, "0.6 0.6 0.6 1.");
	
	CLASS_ATTR_RGBA					(c, "phcolor", 0, t_control, f_colorPositif);
	CLASS_ATTR_CATEGORY				(c, "phcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "phcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "phcolor", 0, "Positifs Harmonics color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "phcolor", 0, "0. 0. 1. 0.25");
	
	CLASS_ATTR_RGBA					(c, "nhcolor", 0, t_control, f_colorNegatif);
	CLASS_ATTR_CATEGORY				(c, "nhcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "nhcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "nhcolor", 0, "Negatifs Harmonics color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "nhcolor", 0, "1. 0. 0. 0.25");
	
	CLASS_ATTR_RGBA					(c, "cocolor", 0, t_control, f_colorContrib);
	CLASS_ATTR_CATEGORY				(c, "cocolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "cocolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "cocolor", 0, "Biggest contribution color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "cocolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_RGBA					(c, "cishadcolor", 0, t_control, f_colorCircleShadow);
	CLASS_ATTR_CATEGORY				(c, "cishadcolor", 0, "Color");
	CLASS_ATTR_STYLE				(c, "cishadcolor", 0, "rgba");
	CLASS_ATTR_LABEL				(c, "cishadcolor", 0, "Circle Shadow Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT	(c, "cishadcolor", 0, "1. 1. 1. 0.2");
	
	CLASS_ATTR_RGBA					(c, "cicolorin", 0, t_control, f_colorCircleInner);
	CLASS_ATTR_CATEGORY				(c, "cicolorin", 0, "Color");
	CLASS_ATTR_STYLE_LABEL			(c, "cicolorin", 0, "rgba", "Circle Inner Color");
	CLASS_ATTR_DEFAULTNAME_SAVE		(c, "cicolorin", 0, "0.7 0.7 0.7 1.");
	
	
	CLASS_ATTR_RGBA					(c, "borderboxcolor", 0, t_control, f_borderboxcolor);
	CLASS_ATTR_CATEGORY				(c, "borderboxcolor", 0, "Color");
	CLASS_ATTR_STYLE_LABEL			(c, "borderboxcolor", 0, "rgba", "Border Box Color");
	CLASS_ATTR_DEFAULTNAME_SAVE		(c, "borderboxcolor", 0, "0.5 0.5 0.5 1.");
	
	//ordre
	CLASS_ATTR_ORDER				(c, "bgcolor", 0, "1");
	CLASS_ATTR_ORDER				(c, "borderboxcolor", 0, "2");
	CLASS_ATTR_ORDER				(c, "cicolor", 0, "3");
	CLASS_ATTR_ORDER				(c, "cicolorin", 0, "4");
	CLASS_ATTR_ORDER				(c, "cishadcolor", 0, "5");
	CLASS_ATTR_ORDER				(c, "phcolor", 0, "6");
	CLASS_ATTR_ORDER				(c, "nhcolor", 0, "7");
	CLASS_ATTR_ORDER				(c, "cocolor", 0, "8");
	
	
	

	class_register(CLASS_BOX, c);
	control_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void *control_new(t_symbol *s, int argc, t_atom *argv)
{
	t_control *x =  NULL; 
	t_dictionary *d;
	long flags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_control *)object_alloc(control_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWY
			;

	x->f_viewer				= new AmbisonicViewer(x->f_order);
    x->f_recomposer         = new ambisonicRecomposer(x->f_order, x->f_order * 2 + 2);
    x->f_projector          = new ambisonicProjector(x->f_order, x->f_order * 2 + 2);
	x->f_harmonicsValues	= new double[x->f_order * 2 + 1];
    x->f_microphonesValues  = new double[x->f_order * 2 + 2];
    
    for(int i = 0; i < x->f_order * 2 + 2; i++)
        x->f_microphonesValues[i] = 1.;
    
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.b_firstin = (t_object *)x;

	x->f_outInfos	= outlet_new(x, NULL);
    x->f_out        = listout(x);

	attr_dictionary_process(x, d);

	x->f_azimuth= 0.;
	x->f_wide = 1.;
	control_compute(x);
	jbox_ready((t_jbox *)x);
	
	return (x);
}			

void control_free(t_control *x)
{
	jbox_free((t_jbox *)x);
	free(x->f_harmonicsValues);
    free(x->f_microphonesValues);
	delete x->f_viewer;
    delete x->f_recomposer;
    delete x->f_projector;
}

void control_assist(t_control *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"(Anything) Behavior and color messages"); 
	}
	else
	{
		if (a == 0)
			sprintf(s,"(Float) Azimuth value"); 
		else if(a == 1)
			sprintf(s,"(Float) Wide value");
		else
			sprintf(s,"(Messages) Infos");
	}
}

t_max_err control_notify(t_control *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("bgcolor") || name == gensym("borderboxcolor") || name == gensym("cicolor") || name == gensym("cicolorin") || name == gensym("gradientcolor") )
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
		else if(name == gensym("txcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
		}
		else if(name == gensym("nhcolor") || name == gensym("phcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
		}
		else if(name == gensym("cocolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("biggest_contribution_layer"));
		}
		else if(name == gensym("shadow"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
			if (x->f_shadow) object_attr_setdisabled((t_object *)x, gensym("cishadcolor"), 0);
			else object_attr_setdisabled((t_object *)x, gensym("cishadcolor"), 1);
		}
		jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void control_getdrawparams(t_control *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = 0;
	params->d_cornersize = 12; 
}

long control_oksize(t_control *x, t_rect *newrect){
	if (newrect->width < 100){
		newrect->width = newrect->height = 100;
	}
	return 0;
}

void control_paint(t_control *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	
	x->f_center.x = rect.width * .5;
	x->f_center.y = rect.height * .5;
	
	x->f_rayonGlobal = rect.width * .5;
	if(rect.width > rect.height)
		x->f_rayonGlobal = rect.height * .5;
	
	x->f_fontsize = (x->f_rayonGlobal / 14.) - 1.;
	x->f_rayonAngle = 5. / 6. * x->f_rayonGlobal + x->f_fontsize * 1.5;
	x->f_rayonCircle = x->f_rayonGlobal / 6;
	
	draw_background(x, view, &rect);
	draw_harmonics(x, view, &rect);
	draw_biggest_contribution(x, view, &rect);
}

void draw_background(t_control *x,  t_object *view, t_rect *rect)
{
	int i;
	double y1, y2, rotateAngle;
	t_jmatrix transform;

	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
	
	if (g) 
	{
		//background
		jgraphics_rectangle_rounded(g, 0.5, 0.5, rect->width-1.,  rect->height-1., 12, 12);
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_fill_preserve(g);
		jgraphics_set_source_jrgba(g, &x->f_borderboxcolor);
		jgraphics_stroke(g);
		
		jgraphics_arc(g, x->f_center.x, x->f_center.y, 5 * x->f_rayonCircle,  0., JGRAPHICS_2PI);
		jgraphics_set_source_jrgba(g, &x->f_colorCircleInner);
		jgraphics_fill(g);
		
		/* Circles */
		for(i = 5; i > 0; i--)
		{
			if (x->f_shadow) {
				//inner shadow
				jgraphics_set_line_width(g, 2);
				jgraphics_set_source_jrgba(g, &x->f_colorCircleShadow);
				jgraphics_arc(g, x->f_center.x+0.5, x->f_center.y+0.5, (double)i * x->f_rayonCircle,  0., JGRAPHICS_2PI);
				jgraphics_stroke(g);
				// circle color (outer shadow)
				jgraphics_set_line_width(g, 1);
				jgraphics_set_source_jrgba(g, &x->f_colorCircle);
				jgraphics_arc(g, x->f_center.x, x->f_center.y, (double)i * x->f_rayonCircle,  0., JGRAPHICS_2PI);
				jgraphics_stroke(g);
			}
			else {
				jgraphics_set_line_width(g, 1);
				jgraphics_set_source_jrgba(g, &x->f_colorCircle);
				jgraphics_arc(g, x->f_center.x, x->f_center.y, (double)i * x->f_rayonCircle,  0., JGRAPHICS_2PI);
				jgraphics_stroke(g);
			}
		}

        // circle color (outer shadow)
        jgraphics_set_source_jrgba(g, &x->f_colorBackground);
        jgraphics_arc(g, x->f_center.x, x->f_center.y, x->f_rayonCircle,  0., JGRAPHICS_2PI);
        jgraphics_fill(g);
        
		/* Axes */
		jgraphics_set_source_jrgba(g, &x->f_colorCircle);
		
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		for(i = 0; i < x->f_order * 2 + 2; i++)
		{
			rotateAngle = (double)i/ (x->f_order * 2 + 2) * JGRAPHICS_2PI - JGRAPHICS_2PI / ((x->f_order * 2 + 2) * 2.);
			jgraphics_rotate(g, rotateAngle);
			
			y1 = 1. / 6. * x->f_rayonGlobal;
			y2 = 5. / 6. * x->f_rayonGlobal;
			
			if (x->f_shadow) 
			{
				if ( (rotateAngle <= JGRAPHICS_PI && rotateAngle > 0.) ) 
				{
					jgraphics_move_to(g, -0.5, y1-0.5);
					jgraphics_line_to(g, -0.5, y2-0.5);
				}
				else 
				{
					jgraphics_move_to(g, 0.5, y1+0.5);
					jgraphics_line_to(g, 0.5, y2+0.5);
				}
				jgraphics_set_line_width(g, 2);
				jgraphics_set_source_jrgba(g, &x->f_colorCircleShadow);
				jgraphics_stroke(g);
			}
			
			jgraphics_move_to(g, 0, y1);
			jgraphics_line_to(g, 0, y2);
			jgraphics_set_source_jrgba(g, &x->f_colorCircle);
			jgraphics_set_line_width(g, 1);
			jgraphics_stroke(g);
			
			jgraphics_rotate(g, -rotateAngle);
		}
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
	//jgraphics_pattern_destroy(pattern);
}

void draw_angle(t_control *x,  t_object *view, t_rect *rect)
{
	int i;
	double x1, y1;
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("angle_layer"), rect->width, rect->height);
	
	if (g) 
	{
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->f_fontsize);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorText); 
		for(i = 0; i < 12; i++)
		{
			x1 = x->f_rayonAngle * cos((double)-i * JGRAPHICS_2PI / 12. - JGRAPHICS_PI / 2.) + x->f_center.x;
			y1 = x->f_rayonAngle * sin((double)-i * JGRAPHICS_2PI / 12. - JGRAPHICS_PI / 2.) + x->f_center.y;
		
			sprintf(text,"%d°", 30 * i);
			jtextlayout_set(jtl, text, jf, x1 - x->f_fontsize * 1.5, y1 - 10, x->f_fontsize * 3., 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
			jtextlayout_draw(jtl, g);
			
		}	
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("angle_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("angle_layer"), 0., 0.);
}

void draw_harmonics(t_control *x,  t_object *view, t_rect *rect)
{
	int pathLength = 0;
	t_pt beginCoord;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("harmonics_layer"), rect->width, rect->height);

	if (g)
	{
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);
		jgraphics_set_line_width(g, 2);
		if(x->f_viewer->getBiggestContribution() != 0.)
		{
            double max = 0.;
            double normalize = 1;
            for(int i = 0 ; i < x->f_order * 2 + 2; i++)
            {
                if(x->f_microphonesValues[i] > max)
                    max = x->f_microphonesValues[i];
            }
            normalize = max / x->f_viewer->getBiggestContribution();
			double factor = (x->f_rayonGlobal * 5. / 6.) * normalize;
			
			jgraphics_set_source_jrgba(g, &x->f_colorPositif);
			for(int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
			{
				
				if (i == NUMBEROFCIRCLEPOINTS-1) {
					jgraphics_line_to(g, beginCoord.x, beginCoord.y );
				}
				else if(x->f_viewer->getColor(i) == 1)
				{
					if (pathLength == 0) 
					{
						beginCoord.x = x->f_viewer->getAbscisseValue(i) * factor;
						beginCoord.y = x->f_viewer->getOrdinateValue(i) * factor;
						jgraphics_move_to(g, beginCoord.x, beginCoord.y );
						pathLength++;
					} else {
						jgraphics_line_to(g, x->f_viewer->getAbscisseValue(i) * factor, 
										  x->f_viewer->getOrdinateValue(i) * factor);
					}
				}
			}
			if (pathLength) {
				jgraphics_close_path(g);
				jgraphics_fill_preserve(g);
				jgraphics_stroke(g);
			}
			
			pathLength = 0;
			jgraphics_new_path(g);
			jgraphics_set_source_jrgba(g, &x->f_colorNegatif);
			for(int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
			{
				
				if (i == NUMBEROFCIRCLEPOINTS-1) {
					jgraphics_line_to(g, beginCoord.x, beginCoord.y );
				}
				else if(x->f_viewer->getColor(i) == -1)
				{
					if (!pathLength) 
					{
						beginCoord.x = x->f_viewer->getAbscisseValue(i) * factor;
						beginCoord.y = x->f_viewer->getOrdinateValue(i) * factor;
						jgraphics_move_to(g, beginCoord.x, beginCoord.y );
						pathLength++;
					} else {
						jgraphics_line_to(g, x->f_viewer->getAbscisseValue(i) * factor, 
										  x->f_viewer->getOrdinateValue(i) * factor);
					}
				}
			}
			if (pathLength) {
				jgraphics_close_path(g);
				jgraphics_fill_preserve(g);
				jgraphics_stroke(g);
			}
			
		}
		jbox_end_layer((t_object*)x, view, gensym("harmonics_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("harmonics_layer"), 0., 0.);
}

void draw_biggest_contribution(t_control *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("biggest_contribution_layer"), rect->width, rect->height);

	if (g) 
	{
		t_jmatrix transform;
		jgraphics_matrix_init(&transform, 1, 0, 0, -1, x->f_center.x, x->f_center.y);
		jgraphics_set_matrix(g, &transform);

		
		jgraphics_set_source_jrgba(g, &x->f_colorContrib);
        double loudspeaker_angle = CICM_2PI / (x->f_order * 2 + 2);
        double factor = x->f_rayonGlobal * 5. / 6.;
        for(int i = 0; i < x->f_order * 2 + 2; i++)
        {
            jgraphics_set_source_jrgba(g, &x->f_colorContrib);
            double angle = loudspeaker_angle * (double)(i) + CICM_PI2;
            jgraphics_arc(g, Tools::abscisse(x->f_microphonesValues[i] * (5. / 6.) + 1. / 6., angle) * factor, Tools::ordinate(x->f_microphonesValues[i] * (5. / 6.) + 1. / 6., angle) * factor, 3.,  0., JGRAPHICS_2PI);
            jgraphics_fill(g);
        }
		jbox_end_layer((t_object*)x, view, gensym("biggest_contribution_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("biggest_contribution_layer"), 0., 0.);
}

void control_mouse_down(t_control *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double loudspeaker_angle = CICM_2PI / (x->f_order * 2 + 2);
    double loudspeaker_angle_mid = loudspeaker_angle / 2.;
    
    double mapped_x = (pt.x - x->f_center.x) / x->f_center.x;
    double mapped_y = (pt.y - x->f_center.y) / x->f_center.y * -1.;
    double radius   = (Tools::radius(mapped_x, mapped_y) - (1. / 6.)) * (31. / 20.);
    radius = Tools::clip_min(radius, 0.);
    double angle    = Tools::angle(mapped_x, mapped_y) - CICM_PI2;
    if(angle < 0.)
        angle += CICM_2PI;
    
    if(angle > CICM_2PI - loudspeaker_angle_mid || angle < loudspeaker_angle_mid)
    {
        x->f_microphonesValues[0] = radius;
    }
    else
    {
        for(int i = 1; i < x->f_order * 2 + 2; i++)
        {
            if(angle > i * loudspeaker_angle - loudspeaker_angle_mid && angle < i * loudspeaker_angle + loudspeaker_angle_mid)
            {
                x->f_microphonesValues[i] = radius;
                
            }
        }
    }
    control_compute(x);
}

void control_mouse_drag(t_control *x, t_object *patcherview, t_pt pt, long modifiers)
{
    double loudspeaker_angle = CICM_2PI / (x->f_order * 2 + 2);
    double loudspeaker_angle_mid = loudspeaker_angle / 2.;
    double mapped_x = ((pt.x - x->f_center.x) / x->f_center.x * (6. / 5.));
    double mapped_y = ((pt.y - x->f_center.y) / x->f_center.y * (6. / 5.)) * -1.;
    double radius   = Tools::radius(mapped_x, mapped_y);
    double angle    = Tools::angle(mapped_x, mapped_y) - CICM_PI2;
    if(angle < 0.)
        angle += CICM_2PI;
    if(angle > CICM_2PI - loudspeaker_angle_mid || angle < loudspeaker_angle_mid)
    {
        x->f_microphonesValues[0] = radius;
    }
    else
    {
        for(int i = 1; i < x->f_order * 2 + 2; i++)
        {
            if(angle > i * loudspeaker_angle - loudspeaker_angle_mid && angle < i * loudspeaker_angle + loudspeaker_angle_mid)
            {
                x->f_microphonesValues[i] = radius;
                
            }
        }
    }
    control_compute(x);
}

void control_compute(t_control *x)
{
	x->f_recomposer->process(x->f_microphonesValues, x->f_harmonicsValues);
	x->f_viewer->process(x->f_harmonicsValues);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("biggest_contribution_layer"));
    jbox_redraw((t_jbox *)x);
    t_atom* list;
    list =  new t_atom[x->f_order * 2 + 2];
    for(int i = 0; i < x->f_order * 2 + 2; i++)
    {
        atom_setfloat(list+i, x->f_microphonesValues[i]);
    }
    outlet_list(x->f_out, 0L, x->f_order * 2 + 2, list);
}

t_max_err order_set(t_control *x, t_object *attr, long argc, t_atom *argv)
{
	if (atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) != x->f_order && atom_getlong(argv) >= 1)
		{
			delete x->f_viewer;
            delete x->f_recomposer;
            delete x->f_projector;
            free(x->f_harmonicsValues);
            free(x->f_microphonesValues);
			x->f_order = atom_getlong(argv);
			x->f_viewer         = new AmbisonicViewer(x->f_order);
            x->f_recomposer		= new ambisonicRecomposer(x->f_order, x->f_order * 2 + 2);
            x->f_projector		= new ambisonicProjector(x->f_order, x->f_order * 2 + 2);
			x->f_harmonicsValues    = new double[x->f_order * 2 + 1];
            x->f_microphonesValues  = new double[x->f_order * 2 + 2];
            for(int i = 0; i < x->f_order * 2 + 2; i++)
                x->f_microphonesValues[i] = 1.;

			control_compute(x);

			jbox_invalidate_layer((t_object *)x, NULL, gensym("harmonics_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("biggest_contribution_layer"));
			jbox_redraw((t_jbox *)x);
		}
	}
	return 0;
}
