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

extern "C"
{
	#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "../hoaHeader.h"
}

#define MAX_SOURCES 100

// output mode
enum {
	CARTESIAN = 0,
	POLAR
};

// configs audio
enum {
	AMBISONIC = 0,
	QUADRIPHONIC,
	OCTOPHONIC
};

// polar coordinates
typedef struct  _pol
{
	double		r; // rayon/distance/amp/alpha de la source par rapport au centre (head) en metres
	double		a; // angle/phase/theta (en radian de -pi à pi) de la source par rapport au centre (head)
} t_pol;

typedef struct  _source
{
	t_pt		pos; // position de la source (x,y)
	t_pt		pix; // à implementer !! attention doit dependre du zoom
	double		angle; // angle (en radian de -pi à pi) de la source par rapport au centre (head)
	double		degree; // angle (en degree de -180 à 180) de la source par rapport au centre (head)
	double		distance; // distance de la source par rapport au centre (head) en metres
	//t_pol		pol;
	t_jrgba		color;
	t_jrgba		selectedColor;
	int			selected;
	int			hasfocus;
	//char		description[20];
	int			hasDescription;
	t_symbol	*description;
} t_source;

typedef struct  _hoamap 
{
	t_jbox		j_box;
	t_rect		rect;
	
	t_jrgba		f_colorBackground;
	t_jrgba		f_colorGrid;
	t_jrgba		f_colorLs;
	t_jrgba		f_colorHead;
	t_jrgba		f_sourceColors[10];
	int			f_nb_sourceColors;
	t_jrgba		f_color_selection;
	
	char		f_displayGrid;
	char		f_displayCartVectors;
	char		f_displayAngle;
	double		f_zoomFactor;
	long		f_audioConfig;
	double		f_speakerOffset;
	int			f_numberOfSpeaker;
	double		f_speakerSpacement;
	double		f_speakerToHeadDistance;
	int			f_arrayType; // "wfs" or "ambisonic"
	int			f_currentGrabedItemIndex;
	int			f_selectedSources[MAX_SOURCES];
	double		f_sourceSize; // taille de la source 
	//int			f_focusedSource;
	
	t_source	f_sources[MAX_SOURCES];
	
	//t_pt		f_mousePointer[MAX_SOURCES];
	t_pt		f_last_mousemove;
	
	int			f_numberOfSources;
	int			f_actualSource;
	int			f_aSourceIsSelected;
	t_rect		f_rect_selection;
	int			f_rect_selection_exist;
	
	long		f_output_mode;
	void*		f_outPolar;
	void*		f_outCarte;
	void*		f_out;
} t_hoamap;

t_class *hoamap_class;

// general methods
void *hoamap_new(t_symbol *s, int argc, t_atom *argv);
void hoamap_free(t_hoamap *x);
void hoamap_getdrawparams(t_hoamap *x, t_object *patcherview, t_jboxdrawparams *params);
void hoamap_assist(t_hoamap *x, void *b, long m, long a, char *s);
t_max_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

// mouse/key methods
void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousedown(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousedown2(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mouseup(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_focusgained(t_hoamap *x, t_object *patcherview);
void hoamap_focuslost(t_hoamap *x, t_object *patcherview);
long hoamap_key(t_hoamap *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousedragdelta(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousedrag(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers);
void hoamap_mousewheel(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc);

// msg-in methods
void hoamap_bang(t_hoamap *x);
void hoamap_list(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_anything(t_hoamap *x, t_symbol *s, short ac, t_atom *av);
void hoamap_float(t_hoamap *x, double f);

void hoamap_zoom(t_hoamap *x, double v);
void hoamap_nb_hp(t_hoamap *x, int v);
void hoamap_shape(t_hoamap *x, int v);
void hoamap_delta(t_hoamap *x, double v);
void hoamap_distance(t_hoamap *x, double v);
void hoamap_display_angle(t_hoamap *x, int v);
void hoamap_display_grid(t_hoamap *x, int v);
void hoamap_display_cartvectors(t_hoamap *x, int v);

void hoamap_add(t_hoamap *x, double xpos, double ypos); // ajoute une source en donnant (x,y);
void hoamap_move(t_hoamap *x, t_symbol *s, short ac, t_atom *av); // bouge une source en donnant (index,x,y);
void hoamap_remove(t_hoamap *x); // supprime le dernière source ajoutée;
void hoamap_clear(t_hoamap *x); // fait place nette (plus aucune sources);
void hoamap_add_source_text_description(t_hoamap *x, t_symbol *s, short ac, t_atom *av); // ajoute une description text à la source.

// msg-out methods
void hoamap_outone(t_hoamap *x, int i);

// paint methods
void hoamap_paint(t_hoamap *x, t_object *view);
void draw_background(t_hoamap *x, t_object *view, t_rect *rect);
void draw_head(t_hoamap *x, t_object *view, t_rect *rect);
void draw_cartVectors(t_hoamap *x, t_object *view, t_rect *rect);
void draw_grid(t_hoamap *x, t_object *view, t_rect *rect);
void draw_speakers(t_hoamap *x, t_object *view, t_rect *rect);
void draw_oneLs(t_hoamap *x, t_jgraphics *g, double posX, double posY, double rotDegree, double size);
//void draw_loudspeakers(t_hoamap *x, t_object *view, t_rect *rect);
void draw_sources(t_hoamap *x,  t_object *view, t_rect *rect);
void draw_angle(t_hoamap *x,  t_object *view, t_rect *rect);
void draw_rect_selection(t_hoamap *x, t_object *view, t_rect *rect);

//specific methods
void update_source_pos_in_pixel(t_hoamap *x, int sourceIndex, t_pt pt);
void update_source_pos_in_cart(t_hoamap *x, int sourceIndex, t_pt pt);
void update_source_pos_in_polar(t_hoamap *x, int sourceIndex, double distance, double radian);

void update_source_selection(t_hoamap *x, int sourceIndex, int isSelected);
int which_source_pointed(t_hoamap *x, t_pt pt);

//calcul methods
double nextPow2(double aValue);
double pX(double width, double cartPos);
double pY(double width, double cartPos);
double scale(double value, double aMin, double aMax, double bMin, double bMax);
int is_in_circle(double x, double y, double cx, double cy, double cr);
t_jrgba clr256(int r, int g, int b, float a);
double calcul_angle(double cx, double cy, double px, double py);
double calcul_angle_display(double x1, double y1, double x2, double y2);

t_pt poltocar(double distance, double angle); // return (x,y);
t_pol cartopol(double x, double y);	// return (r = rayon, a = angle en radian);
t_pt pixtocar(t_hoamap *x, t_pt pix);
t_pt cartopix(t_hoamap *x, t_pt pt, int antialiased);
t_pol pixtopol(t_hoamap *x, t_pt pix);
t_pt poltopix(t_hoamap *x, t_pol pol, int antialiased);
double radtodeg(double radian);
double degtorad(double degree);
double wrapi(double deltaPhase);
t_pt point_to_radDist(t_pt pt1, t_pt pt2); // retourne le radian et la distance à partir de deux points
t_pt point_to_degDist(t_pt pt1, t_pt pt2); // retourne le degree et la distance à partir de deux points

int main()
{
	t_class *c;
	
	c = class_new("hoa.map", (method)hoamap_new, (method)hoamap_free, (short)sizeof(t_hoamap), 0L, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method)hoamap_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)hoamap_paint,		"paint",		A_CANT,	0);
	class_addmethod(c, (method)hoamap_getdrawparams, "getdrawparams", A_CANT, 0);
	class_addmethod(c, (method)hoamap_notify,		"notify",		A_CANT, 0);
	class_addmethod(c, (method)hoamap_bang,			"bang",			0L,0);
	class_addmethod(c, (method)hoamap_list,			"list",			A_GIMME, 0);
	class_addmethod(c, (method)hoamap_float,		"float",		A_FLOAT, 0);
	class_addmethod(c, (method)hoamap_anything,		"anything",		A_GIMME, 0);
	//class_addmethod(c, (method)hoamap_zoom,			"zoom",			A_DEFFLOAT, 0);
	//class_addmethod(c, (method)hoamap_nb_hp,		"loudspeaker",	A_DEFLONG, 0);
	//class_addmethod(c, (method)hoamap_shape,		"shape",		A_DEFLONG, 0);
	class_addmethod(c, (method)hoamap_display_angle,"display_angle",A_DEFLONG, 0);
	class_addmethod(c, (method)hoamap_display_grid, "display_grid", A_DEFLONG, 0);
	class_addmethod(c, (method)hoamap_display_cartvectors,"display_cartvectors",A_DEFLONG, 0);
	//class_addmethod(c, (method)hoamap_delta,		"delta",		A_DEFFLOAT, 0);
	class_addmethod(c, (method)hoamap_distance,		"distance",		A_DEFFLOAT, 0);
	
	class_addmethod(c, (method)hoamap_add,			"add",			A_DEFFLOAT, A_DEFFLOAT, 0);
	class_addmethod(c, (method)hoamap_remove,		"remove",		0L, 0);
	class_addmethod(c, (method)hoamap_clear,		"clear",		0L, 0);
	//class_addmethod(c, (method)hoamap_move,			"move",			A_GIMME, 0);
	class_addmethod(c, (method)hoamap_move,			"car",			A_GIMME, 0);
	class_addmethod(c, (method)hoamap_move,			"pol",			A_GIMME, 0);
	class_addmethod(c, (method)hoamap_add_source_text_description,	"text",			A_GIMME, 0);
	
	class_addmethod(c, (method) hoamap_mousedown,	"mousedown",		A_CANT, 0);
	class_addmethod(c, (method)hoamap_mousedrag,	"mousedrag",		A_CANT, 0);
	//class_addmethod(c, (method) hoamap_mousedragdelta,	"mousedragdelta", A_CANT, 0);
	class_addmethod(c, (method) hoamap_mouseup,			"mouseup",		A_CANT, 0);
	class_addmethod(c, (method) hoamap_mousemove,		"mousemove",	A_CANT, 0);
	//class_addmethod(c, (method) hoamap_mouseleave,		"mouseleave",	A_CANT, 0);
	//class_addmethod(c, (method) hoamap_mouseenter,		"mouseenter",	A_CANT, 0);
	//class_addmethod(c, (method) hoamap_focusgained,		"focusgained",	A_CANT, 0);
	//class_addmethod(c, (method) hoamap_focuslost,		"focuslost",	A_CANT, 0);
	class_addmethod(c, (method) hoamap_key,				"key",			A_CANT, 0);
	class_addmethod(c, (method) hoamap_mousewheel,		"mousewheel",	A_CANT, 0);
	
	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 300");
	
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);
	
	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_hoamap, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "1. 1. 1. 1.");
	
	CLASS_ATTR_RGBA				(c, "gridcolor", 0, t_hoamap, f_colorGrid);
	CLASS_ATTR_CATEGORY			(c, "gridcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "gridcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "gridcolor", 0, "Grid Color");
	CLASS_ATTR_ORDER			(c, "gridcolor", 0, "6");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "gridcolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "lscolor", 0, t_hoamap, f_colorLs);
	CLASS_ATTR_CATEGORY			(c, "lscolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "lscolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "lscolor", 0, "LoudSpeaker Color");
	CLASS_ATTR_ORDER			(c, "lscolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "lscolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_RGBA				(c, "headcolor", 0, t_hoamap, f_colorHead);
	CLASS_ATTR_CATEGORY			(c, "headcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "headcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "headcolor", 0, "Head Color");
	CLASS_ATTR_ORDER			(c, "headcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "headcolor", 0, "0. 0. 0. 1.");
	
	/*
	CLASS_ATTR_RGBA				(c, "selectcolor", 0, t_hoamap, f_color_selection);
	CLASS_ATTR_CATEGORY			(c, "selectcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "selectcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "selectcolor", 0, "selection Color");
	CLASS_ATTR_ORDER			(c, "selectcolor", 0, "7");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "selectcolor", 0, "0. 0. 1. 0.05");
	*/

	/*
	CLASS_ATTR_LONG				(c,"output_mode",0, t_hoamap, f_output_mode);
	CLASS_ATTR_LABEL			(c,"output_mode", 0, "Output Mode");
	CLASS_ATTR_CATEGORY			(c,"output_mode",0,"Output");
	CLASS_ATTR_ENUMINDEX		(c,"output_mode", 0, "Cartesian Polar");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"output_mode",0,"0");
	*/
	
	CLASS_ATTR_CHAR				(c,"display_grid",0, t_hoamap, f_displayGrid);
	CLASS_ATTR_STYLE_LABEL		(c,"display_grid",0,"onoff","Display Grid");
	CLASS_ATTR_CATEGORY			(c,"display_grid",0,"Custom");
	CLASS_ATTR_DEFAULT_SAVE		(c,"display_grid",0,"1");
	
	CLASS_ATTR_CHAR				(c,"display_cartvectors",0, t_hoamap, f_displayCartVectors);
	CLASS_ATTR_STYLE_LABEL		(c,"display_cartvectors",0,"onoff","Display Cartesian Vectors");
	CLASS_ATTR_CATEGORY			(c,"display_cartvectors",0,"Custom");
	CLASS_ATTR_DEFAULT_SAVE		(c,"display_cartvectors",0,"1");
	
	CLASS_ATTR_CHAR				(c,"display_angle",0, t_hoamap, f_displayAngle);
	CLASS_ATTR_STYLE_LABEL		(c,"display_angle",0,"onoff","Display Angle");
	CLASS_ATTR_CATEGORY			(c,"display_angle",0,"Custom");
	CLASS_ATTR_DEFAULT_SAVE		(c,"display_angle",0,"1");
	
	/*
	CLASS_ATTR_LONG				(c,"audio_config",0, t_hoamap, f_audioConfig);
	CLASS_ATTR_LABEL			(c,"audio_config", 0, "Audio Configuration");
	CLASS_ATTR_CATEGORY			(c,"audio_config",0,"Custom");
	CLASS_ATTR_ENUMINDEX		(c,"audio_config", 0, "Ambisonic stereo quadriphonic octophonic \" \"5.1 \" \"6.1 \" \"7.1 \" \"9.1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"audio_config",0,"0");
	*/
	
	CLASS_ATTR_DOUBLE			(c,"zoom",0, t_hoamap, f_zoomFactor);
	CLASS_ATTR_FILTER_CLIP		(c,"zoom", 0.1, 1.);
	CLASS_ATTR_LABEL			(c,"zoom", 0, "Zoom");
	CLASS_ATTR_CATEGORY			(c,"zoom",0,"Custom");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"zoom",0,"0.5");
	
	CLASS_ATTR_DOUBLE			(c,"speaker_offset",0, t_hoamap, f_speakerOffset);
	CLASS_ATTR_FILTER_CLIP		(c,"speaker_offset", -180, 180);
	CLASS_ATTR_LABEL			(c,"speaker_offset", 0, "Speaker Offset Degree");
	CLASS_ATTR_CATEGORY			(c,"speaker_offset",0,"Custom");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"speaker_offset",0,"0.");
	
	CLASS_ATTR_DOUBLE			(c,"speaker_distance",0, t_hoamap, f_speakerToHeadDistance);
	CLASS_ATTR_FILTER_MIN		(c,"speaker_distance", 0.1);
	CLASS_ATTR_LABEL			(c,"speaker_distance", 0, "Speaker to Head Distance (meters)");
	CLASS_ATTR_CATEGORY			(c,"speaker_distance",0,"Custom");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"speaker_distance",0,"1.5");
	
	CLASS_ATTR_LONG				(c,"speaker_number",0, t_hoamap, f_numberOfSpeaker);
	CLASS_ATTR_FILTER_MIN		(c,"speaker_number", 1);
	CLASS_ATTR_LABEL			(c,"speaker_number", 0, "Number of LoudSpeakers");
	CLASS_ATTR_CATEGORY			(c,"speaker_number",0,"Custom");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"speaker_number",0,"8");
	
	
	class_register(CLASS_BOX, c);
	hoamap_class = c;
	
	//class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	hoa_init();
	return 0;
}

void *hoamap_new(t_symbol *s, int argc, t_atom *argv)
{
	t_hoamap *x =  NULL; 
	int i;
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
//	| JBOX_DRAWBACKGROUND
//	| JBOX_MOUSEDRAGDELTA
	;
	jbox_new(&x->j_box, flags, argc, argv); 
	
	x->f_zoomFactor = 0.5;
	x->f_numberOfSpeaker = 16;
	x->f_speakerSpacement = 0.20;
	x->f_speakerToHeadDistance = 1.5;
	x->f_arrayType = 1;
	x->f_currentGrabedItemIndex = -1;
	
	x->f_displayAngle = 1;
	x->f_displayCartVectors = 1;
	x->f_displayGrid = 1;
	
	//couleurs prédefinies pour les sources :	
	x->f_sourceColors[0] = clr256(41,95,153,255);
	x->f_sourceColors[1] = clr256(255,127,0,255);
	x->f_sourceColors[2] = clr256(255,255,0,255);
	x->f_sourceColors[3] = clr256(127,0,127,255);
	x->f_sourceColors[4] = clr256(0,168,51,255);
	x->f_sourceColors[5] = clr256(255,0,0,255);
	x->f_sourceColors[6] = clr256(153,75,0,255);
	x->f_sourceColors[7] = clr256(20,131,102,255);
	x->f_sourceColors[8] = clr256(84,47,140,255);
	x->f_sourceColors[9] = clr256(255,191,0,255);
	x->f_nb_sourceColors = 10;
	
	x->f_color_selection = clr256(0., 0., 255., 13);
	
	
	x->f_out = outlet_new((t_object *)x, NULL);
	x->f_outPolar		= listout(x);
	x->f_outCarte		= listout(x);
	
	x->f_numberOfSources = 0;
	for(i = 0; i < MAX_SOURCES; i++) {
		x->f_sources[i].pos.x = 0.;
		x->f_sources[i].pos.y = 0.;
		x->f_sources[i].color = x->f_sourceColors[i%(x->f_nb_sourceColors-1)];
	}

	x->j_box.b_firstin = (t_object*) x;
	
	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);
	
	return (x);
}

/* --------- */

t_jrgba clr256(int r, int g, int b, float a)
{
	t_jrgba color;
	color.red = r / 255.0f;
	color.green = g / 255.0f;
	color.blue = b / 255.0f;
	color.alpha = a / 255.0f;
	return color;
}

double scale(double value, double aMin, double aMax, double bMin, double bMax){
	double a = ( (bMax - bMin) / (aMax - aMin) );
	double b = -1 * ( (a * aMin) - bMin );
	return (a * value) + b;
}

int is_in_circle(double x, double y, double cx, double cy, double cr){
	double dist = sqrt(pow(x-cx, 2)+pow(y-cy, 2));
	return dist <= cr;
}

double calcul_angle(double x1, double y1, double x2, double y2){
	//float a = ((float)(atan2 (y2-y1, x2-x1)*180./JGRAPHICS_PI))+90.0f;
	float a = ((float)(atan2 (y2-y1, x2-x1)*180./JGRAPHICS_PI))-90.0f;
	return a;
}

double calcul_angle_display(double x1, double y1, double x2, double y2){
	float a = ((float)(atan2 (y2-y1, x2-x1)*180./JGRAPHICS_PI))-90.0f;
	if (a <= -180) return 360+a;
	else return a;
}

double pX(double width, double cartPos){
	return floor( (cartPos+1)*0.5 * width) + 0.5; //+ antialiasing method
}
double pY(double width, double cartPos){
	return floor( (-cartPos+1)*0.5 * width) + 0.5; //+ antialiasing method
}

t_pt poltocar(double distance, double angle){
	t_pt cart;
	cart.x = distance * sin(angle);
	cart.y = distance * cos(angle);
	return cart;
}
t_pol cartopol(double x, double y){
	t_pol pol;
	double radian = atan2(x,y);
	//double degree = radian * (180 / JGRAPHICS_PI);
	// rayon/distance
	double rayon = sqrt((x * x) + (y * y));
	pol.r = rayon;
	pol.a = radian;
	return pol;
}
t_pt pixtocar(t_hoamap *x, t_pt pix)
{
	t_pt cart = { scale(pix.x, 0, x->rect.width, -1, 1) / x->f_zoomFactor , scale(pix.y, 0, x->rect.height, 1, -1)  / x->f_zoomFactor};
	return cart;
}

t_pt cartopix(t_hoamap *x, t_pt pt, int antialiased)
{
	double w = x->rect.width;
	double zoom = x->f_zoomFactor;
	t_pt pix;
	pix.x = (pt.x*zoom+1)*0.5 * w;
	pix.y = (-pt.y*zoom+1)*0.5 * w;
	if (antialiased) {
		pix.x = floor(pix.x)+0.5;
		pix.y = floor(pix.y)+0.5;
	}
	return pix;
}

t_pol pixtopol(t_hoamap *x, t_pt pix)
{
	t_pt cart = pixtocar(x, pix);
	return cartopol(cart.x, cart.y);
}

t_pt poltopix(t_hoamap *x, t_pol pol, int antialiased)
{
	t_pt cart = poltocar(pol.r, pol.a);
	return cartopix(x, cart, antialiased);
}

double radtodeg(double radian)
{
	return radian * (180 / JGRAPHICS_PI);
}

double degtorad(double degree)
{
	return degree / (180 / JGRAPHICS_PI);
}

// retourne le radian et la distance à partir de deux points
t_pt point_to_radDist(t_pt pt1, t_pt pt2)
{
	//double angleRadian = atan2(pt1.x, pt1.y); //marche aussi puisque pt2 = (0,0)
	double angleRadian = atan2(pt1.x - pt2.x, pt1.y - pt2.y);
	double distance = sqrt((pt1.x * pt1.x) + (pt1.y * pt1.y));
	t_pt radDist = {angleRadian,distance};
	return radDist;
}
// retourne le degree et la distance à partir de deux points
t_pt point_to_degDist(t_pt pt1, t_pt pt2)
{
	double angleRadian = atan2(pt1.x - pt2.x, pt1.y - pt2.y);
	double angleDegree = angleRadian * (180 / JGRAPHICS_PI);
	double distance = sqrt(pt1.x * pt2.x + pt1.y * pt2.y);
	t_pt radDeg = {angleDegree,distance};
	return radDeg;
}

//wraping function :
double wrapi(double deltaPhase)
{
	if (deltaPhase>0)
        deltaPhase = fmod(deltaPhase + CICM_PI, 2.0*CICM_PI)-CICM_PI;
    else
        deltaPhase = fmod(deltaPhase - CICM_PI, 2.0*CICM_PI)+CICM_PI;
	return deltaPhase;
}
/* --------- */

void hoamap_getdrawparams(t_hoamap *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = 1;
	params->d_cornersize = 6; 
}

void hoamap_free(t_hoamap *x)
{
	jbox_free(&x->j_box);
}

void hoamap_assist(t_hoamap *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		sprintf(s,"msg in (add, remove, clear, car, pol ...)");
	} else {
		if (a == 0) {
			sprintf(s,"Cartesian coordinates output : (source, x, y)");
		}
		else if (a == 1) {
			sprintf(s,"Polar coordinates output : (source, distance, radius)");
		}
		else if (a == 2) {
			sprintf(s,"Number of Sources in the scene");
		}
	}
}

void hoamap_float(t_hoamap *x, double f)
{
	;
}
void hoamap_anything(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
	;
}

void hoamap_list(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
	;
}

void hoamap_bang(t_hoamap *x)
{
	int i;
	for(i = 0; i < x->f_numberOfSources; i++)
		hoamap_outone(x, i);
}

void update_source_pos_in_pixel(t_hoamap *x, int sourceIndex, t_pt pt){
	x->f_sources[sourceIndex].pix = pt;
	x->f_sources[sourceIndex].pos = pixtocar(x, pt);
	t_pol pol = cartopol(x->f_sources[sourceIndex].pos.x, x->f_sources[sourceIndex].pos.y);
	x->f_sources[sourceIndex].distance = pol.r;
	x->f_sources[sourceIndex].angle = pol.a;
	hoamap_outone(x, sourceIndex);
}

void update_source_pos_in_cart(t_hoamap *x, int sourceIndex, t_pt pt){
	x->f_sources[sourceIndex].pos = pt;
	t_pol pol = cartopol(pt.x, pt.y);
	x->f_sources[sourceIndex].distance = pol.r;
	x->f_sources[sourceIndex].angle = pol.a;
	hoamap_outone(x, sourceIndex);
}

void update_source_pos_in_polar(t_hoamap *x, int sourceIndex, double distance, double radian){
	x->f_sources[sourceIndex].distance = distance;
	x->f_sources[sourceIndex].angle = wrapi(radian);
	x->f_sources[sourceIndex].pos = poltocar(distance, radian);
	x->f_sources[sourceIndex].pix = cartopix(x, x->f_sources[sourceIndex].pos, 0);
	hoamap_outone(x, sourceIndex);
}

// update_source_selection (apply to all sources with sourceIndex = -1, toggle state with isSelected = -1)
void update_source_selection(t_hoamap *x, int sourceIndex, int isSelected){
	int i;
	if (sourceIndex != -1) {
		if (sourceIndex >= 0 && sourceIndex < x->f_numberOfSources) {
			if (isSelected != -1) {
				if (isSelected != 0) isSelected = 1;
				x->f_sources[sourceIndex].selected = isSelected;
			} else { // toggle
				x->f_sources[sourceIndex].selected = !x->f_sources[sourceIndex].selected;
			}
		}
	} else {
		// apliqué a toutes les sources
		for(i=0; i<MAX_SOURCES; i++){
			if (i < x->f_numberOfSources) {
				if (isSelected != -1) {
					if (isSelected != 0) isSelected = 1;
					x->f_sources[i].selected = isSelected;
				} else { // toggle
					x->f_sources[i].selected = !x->f_sources[i].selected;
				}
			} else {
				x->f_sources[i].selected = 0;
			}
		}
	}
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
	jbox_redraw((t_jbox *)x);
}

void hoamap_outone(t_hoamap *x, int i)
{
	t_atom	av[3];
	atom_setlong(av, i);
	
	outlet_int(x->f_out, x->f_numberOfSources);
	
	atom_setfloat(av+1, (float)x->f_sources[i].distance);
	atom_setfloat(av+2, (float)x->f_sources[i].angle);
	outlet_list(x->f_outPolar, NULL, 3, av);
	
	atom_setfloat(av+1, (float)x->f_sources[i].pos.x);
	atom_setfloat(av+2, (float)x->f_sources[i].pos.y);
	outlet_list(x->f_outCarte, NULL, 3, av);
	
	
	/*
	if (x->f_output_mode == CARTESIAN) {
		atom_setfloat(av+1, (float)x->f_sources[i].pos.x);
		atom_setfloat(av+2, (float)x->f_sources[i].pos.y);
	}
	else if (x->f_output_mode == POLAR) {
		atom_setfloat(av+1, (float)x->f_sources[i].distance);
		atom_setfloat(av+2, (float)x->f_sources[i].angle);
	}
	outlet_list(x->f_outCarte, NULL, 3, av);
	*/
}

/* ------ MSG EXTERNS ------ */
// ajoute une description text à la source.
void hoamap_add_source_text_description(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
	int source = -1;
	t_symbol *text;
	int textOk = 0;
	
	if (ac>=1) {
		if( atom_gettype(av) == A_LONG ) {
			source = atom_getlong(av);
			if (source<0 || source > MAX_SOURCES-1) source = -1;
		}
		if (ac>1) {
			if(atom_gettype(av+1) == A_SYM) {
				text = atom_getsym(av+1);
				textOk = 1;
			}
		}	
	}
	if (source>=0) {
		if (textOk == 1) {
			x->f_sources[source].hasDescription = 1;
			x->f_sources[source].description = text;
		}
		else {
			x->f_sources[source].hasDescription = 0;
			x->f_sources[source].description = gensym("");
		}
		jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
		jbox_redraw((t_jbox *)x);
	}
	else {
		object_error((t_object*)x, "Bad msg format : [int (source index)] [symbol (description)]");
	}
}

// ajoute une source en donnant (x,y) repère à 0;
void hoamap_add(t_hoamap *x, double xpos, double ypos) {
	t_pt point = {xpos,ypos};	
	if(x->f_numberOfSources < MAX_SOURCES) x->f_numberOfSources++;
	x->f_actualSource = x->f_numberOfSources;
	//x->f_sources[x->f_actualSource-1].pos = point; // repere à 0 : -1 1 
	
	update_source_pos_in_cart(x, x->f_actualSource-1, point);
	hoamap_outone(x, x->f_actualSource-1);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
	jbox_redraw((t_jbox *)x);
}


// bouge une source en donnant (index,x,y);
void hoamap_move(t_hoamap *x, t_symbol *s, short ac, t_atom *av)
{
	int source = -1;
	double coord1, coord2;
	int coordOk = 0;
	t_pt car;
	
	if (ac == 3) 
	{
		if( atom_gettype(av) == A_LONG ) 
		{
			source = atom_getlong(av);
			if (source<0 || source > MAX_SOURCES-1) source = -1;
		}
		if (source >= 0) {
			if( atom_gettype(av+1) == A_LONG ) {
				coord1 = (double)atom_getlong(av+1);
				coordOk = 1;
			}
			else if( atom_gettype(av+1) == A_FLOAT ) {
				coord1 = (double)atom_getfloat(av+1);
				coordOk = 1;
			}
			else coordOk = 0;
			
			if (coordOk) {
				if( atom_gettype(av+2) == A_LONG ) {
					coord2 = (double)atom_getlong(av+2);
					coordOk = 1;
				}
				else if( atom_gettype(av+2) == A_FLOAT ) {
					coord2 = (double)atom_getfloat(av+2);
					coordOk = 1;
				}
				else coordOk = 0;
			}
			
		}	
	}
	
	if (source >= 0 && coordOk) {
		if (s == gensym("car")) {
			car.x = coord1;
			car.y = coord2;
			update_source_pos_in_cart(x, source, car);
			jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
			jbox_redraw((t_jbox *)x);
		}
		else if(s == gensym("pol")){
			if (coord1<0) coord1 *= -1;
			update_source_pos_in_polar(x, source, coord1, coord2);
			jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
			jbox_redraw((t_jbox *)x);
		}
		else {
			object_error((t_object*)x, "bad format message");
		}
	}
	else {
		object_error((t_object*)x, "bad format message");
	}
}

// supprime le dernière source ajoutée;
void hoamap_remove(t_hoamap *x){
	x->f_numberOfSources--;
	if(x->f_numberOfSources <= -1) x->f_numberOfSources = 0;
	update_source_selection(x, x->f_actualSource, 0);
	x->f_actualSource = x->f_numberOfSources;
	outlet_int(x->f_out, x->f_numberOfSources);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
	jbox_redraw((t_jbox *)x);
}

// fait place nette (plus acune sources);
void hoamap_clear(t_hoamap *x){
	int i;
	for(i=0; i<= x->f_numberOfSources; i++){
		x->f_sources[i].pos.x = x->f_sources[i].pos.y = x->f_sources[i].degree = x->f_sources[i].distance = 0;
		x->f_sources[i].selected = x->f_sources[i].hasfocus = 0;
	}
	x->f_numberOfSources = 0;
	x->f_actualSource = 0;
	outlet_int(x->f_out, x->f_numberOfSources);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
	jbox_redraw((t_jbox *)x);
}

void hoamap_zoom(t_hoamap *x, double v){
    if (v>1) {v = 1;}
    else if (v < 0.1) {v = 0.1; }
    x->f_zoomFactor = v;
	object_attr_setfloat(x, gensym("zoom"), (double)v);
    //if(x->f_zoomFactor == 1 || x->f_zoomFactor == 0.1) {return;};
    //bang();
	jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("cartvectors_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("head_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("grid_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("ls_layer"));
	jbox_redraw((t_jbox *)x);
}

// pas implémentée
/*
void hoamap_shape(t_hoamap *x, int v){
    if (v <= 0) { v = 0; }
    else if (v >= 1) { v = 1; }
    x->f_arrayType = v;
}
*/

// pas implémentée (wfs specific)
/*
void hoamap_delta(t_hoamap *x, double v){
    if (v <= 0) { v = 0; };
    //else if (v >= 1) { v = 1 };
    x->f_speakerSpacement = v;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("ls_layer"));
	jbox_redraw((t_jbox *)x);
}
*/

void hoamap_distance(t_hoamap *x, double v){
    if (v <= 0) { v = 0; };
    x->f_speakerToHeadDistance = v;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("ls_layer"));
	jbox_redraw((t_jbox *)x);
}

void hoamap_display_angle(t_hoamap *x, int v){
	if (v != 0) v = 1;
	object_attr_setchar(x, gensym("display_angle"), (char)v);
}
void hoamap_display_grid(t_hoamap *x, int v){
	if (v != 0) v = 1;
	object_attr_setchar(x, gensym("display_grid"), (char)v);
}
void hoamap_display_cartvectors(t_hoamap *x, int v){
	if (v != 0) v = 1;
	object_attr_setchar(x, gensym("display_cartvectors"), (char)v);
}

t_max_err hoamap_notify(t_hoamap *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	 {
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("bgcolor") || name == gensym("cicolor"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		 }
		else if(name == gensym("headcolor"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("head_layer"));
		 }
		else if(name == gensym("gridcolor"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid_layer"));
		 }
		else if(name == gensym("lscolor"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("ls_layer"));
		 }
		else if(name == gensym("display_grid"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid_layer"));
		 }
		else if(name == gensym("display_angle"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
		 }
		else if(name == gensym("display_cartvectors"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("cartvectors_layer"));
		 }
		else if(name == gensym("speaker_number"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("ls_layer"));
		 }
		else if(name == gensym("speaker_distance"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("ls_layer"));
		 }
		else if(name == gensym("speaker_offset"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("ls_layer"));
		 }
		else if(name == gensym("zoom"))
		 {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("cartvectors_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("head_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("ls_layer"));
		 }
		jbox_redraw((t_jbox *)x);
	 }
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void hoamap_paint(t_hoamap *x, t_object *view)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	x->rect = rect;
	draw_background(x, view, &rect);
	if (x->f_displayGrid) {
		draw_grid(x, view, &rect);
	}
	if (x->f_displayCartVectors) {
		draw_cartVectors(x, view, &rect);
	}
	draw_speakers(x, view, &rect);
	if (x->f_displayAngle) {
		draw_angle(x, view, &rect);
	}
	draw_head(x, view, &rect);
	draw_sources(x, view, &rect);
	draw_rect_selection(x, view, &rect);
}

void draw_sources(t_hoamap *x,  t_object *view, t_rect *rect)
{
	int i;
	double size, fontsize;
	double zoom = x->f_zoomFactor;
	double w = rect->width;
	t_jfont *jf;
	t_jtextlayout *jtl;
	t_jrgba sourceColor;
	int ombreX;
	int ombreY;
	t_jrgba ombre = {0,0,0,0.3};
	char text[55];
	t_pt textplace;
	t_pt sourcePos;
	t_pt sourcePosShadow;
	
	t_jrgba selected_color = x->f_color_selection;
	selected_color.alpha = 0.2;
	
	
	//t_jgraphics_text_justification text_justif = JGRAPHICS_TEXT_JUSTIFICATION_LEFT;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("sources_layer"), rect->width, rect->height);
	size = w / 60.;
	fontsize = (w / 30.) - 1.;
	if (size < 5) size = 5;
	if (fontsize < 10) fontsize = 10;
	x->f_sourceSize = size;
	ombreX = ombreY = floor(size * 0.15) + 0.5;
	
	if (g) 
	 {
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize);
		jtl = jtextlayout_create();
		for(i = 0; i < x->f_numberOfSources; i++)
		 {
			//sourcePos.x = pX(w,x->f_sources[i].pos.x * zoom);
			//sourcePos.y = pY(w,x->f_sources[i].pos.y * zoom);
			sourcePos = cartopix(x, x->f_sources[i].pos, 0);
			sourcePosShadow.x = sourcePos.x + ombreX;
			sourcePosShadow.y = sourcePos.y + ombreY;
			
			sourceColor = x->f_sources[i].color;
			sourceColor.alpha = 0.5;
			
			jgraphics_set_line_width(g, size*0.2);
			if (x->f_sources[i].hasfocus) {
				sourceColor.alpha = 0.8;
				ombre.alpha = 0.8;
			} else {
				sourceColor.alpha = 0.5;
				ombre.alpha = 0.3;
			}
			
			if (x->f_sources[i].hasDescription) {
				sprintf(text,"%i : %s", i, x->f_sources[i].description->s_name);
			} else {
				sprintf(text,"%i", i);
			}
			textplace.x = sourcePos.x + size;
			textplace.y = pY(w,x->f_sources[i].pos.y * zoom) + size;
			if (pX(w,x->f_sources[i].pos.x) < w*0.5) {
				textplace.x = sourcePos.x - size - fontsize*0.5;
			}
			if (pY(w,x->f_sources[i].pos.y) < w*0.5) {
				textplace.y = sourcePos.y - size - fontsize;
			}
			
			if (w>=400) {
				// ombre du text
				/*
				jtextlayout_settextcolor(jtl, &ombre);
				jtextlayout_set(jtl, text, jf, textplace.x+ombreX, textplace.y+ombreY, fontsize * 3, fontsize, JGRAPHICS_TEXT_JUSTIFICATION_LEFT, JGRAPHICS_TEXTLAYOUT_NOWRAP);
				jtextlayout_draw(jtl, g);
				*/
			}
			// nbSourceText
			jtextlayout_settextcolor(jtl, &sourceColor);
			//jtextlayout_set(jtl, text, jf, textplace.x, textplace.y, fontsize * 3, fontsize, JGRAPHICS_TEXT_JUSTIFICATION_LEFT, JGRAPHICS_TEXTLAYOUT_NOWRAP);
			jtextlayout_set(jtl, text, jf, textplace.x, textplace.y, fontsize * 10, fontsize*2., JGRAPHICS_TEXT_JUSTIFICATION_LEFT, JGRAPHICS_TEXTLAYOUT_USEELLIPSIS);
			jtextlayout_draw(jtl, g);
			
			if (w>=400) {
				// ombre portée:
				jgraphics_set_source_jrgba(g, &ombre);
				jgraphics_arc(g, sourcePosShadow.x, sourcePosShadow.y, size*0.2,  0., JGRAPHICS_2PI);
				jgraphics_fill(g);
				jgraphics_arc(g, sourcePosShadow.x, sourcePosShadow.y, size*0.5,  0., JGRAPHICS_2PI);
				jgraphics_stroke(g);
				jgraphics_arc(g, sourcePosShadow.x, sourcePosShadow.y, size*1,  0., JGRAPHICS_2PI);
				jgraphics_stroke(g);
			}
			
			if (x->f_sources[i].selected == 1) {
				jgraphics_set_source_jrgba(g, &selected_color);
				jgraphics_arc(g, sourcePos.x + ombreX*0.5, sourcePos.y + ombreX*0.5, size*1.5,  0., JGRAPHICS_2PI);
				jgraphics_fill(g);
			}
			// source
			jgraphics_set_source_jrgba(g, &sourceColor);
			if (w<=400) {
				jgraphics_arc(g, sourcePos.x, sourcePos.y, size*0.6,  0., JGRAPHICS_2PI);
				jgraphics_fill(g);
			}
			else {
				jgraphics_arc(g, sourcePos.x, sourcePos.y, size*0.2,  0., JGRAPHICS_2PI);
				jgraphics_fill(g);
				jgraphics_arc(g, sourcePos.x, sourcePos.y, size*0.5,  0., JGRAPHICS_2PI);
				jgraphics_stroke(g);
			}
			jgraphics_arc(g, sourcePos.x, sourcePos.y, size*1,  0., JGRAPHICS_2PI);
			jgraphics_stroke(g);
			
		 }
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("sources_layer"));
	 }
	jbox_paint_layer((t_object *)x, view, gensym("sources_layer"), 0., 0.);
}

void draw_angle(t_hoamap *x,  t_object *view, t_rect *rect){
	int i;
	double zoom = x->f_zoomFactor;
	double w = rect->width;
	t_pt sourceOfsset;
	//t_pt headOfsset;
	double dashes[2] = {4,2};
	double radians[2];
	double radius = w*0.15 * zoom;
	if (zoom<0.3) radius = w*0.15 * 0.3;
	t_jfont *jf;
	t_jtextlayout *jtl;
	long fontsize = (w / 30.);
	char text[16];
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("angle_layer"), rect->width, rect->height);
	
	if (g) 
	 {
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize);
		jtl = jtextlayout_create();
		t_jrgba angleFillColor = {0.1,0.1,0.1,0.2};
		t_jrgba angleStrokeColor = {0,0,0,0.4};
		
		for(i = 0; i < x->f_numberOfSources; i++){
			if (x->f_sources[i].hasfocus) {
				
				// angle
				radians[0] = degtorad(-90);
				radians[1] = x->f_sources[i].angle + degtorad(-90);
				
				jgraphics_set_source_jrgba(g, &angleFillColor);
				jgraphics_set_line_width(g, radius);
				if (x->f_sources[i].angle > 0) {
					jgraphics_arc(g, pX(w, 0), pY(w, 0), radius*0.5, radians[0], radians[1]);
				} else {
					jgraphics_arc(g, pX(w, 0), pY(w, 0), radius*0.5, radians[1], radians[0]);
				}
				jgraphics_stroke(g);
				
				// source to head dashed line
				t_pt cart = poltocar(x->f_sources[i].distance + (-0.05 / zoom), x->f_sources[i].angle);
				sourceOfsset = cartopix(x, cart, 1);
				jgraphics_set_line_width(g, 1);
				jgraphics_set_dash(g, dashes, 2, 0);
				jgraphics_set_source_jrgba(g, &angleStrokeColor);
				jgraphics_move_to(g, sourceOfsset.x, sourceOfsset.y);
				jgraphics_line_to(g, pX(w,0),pY(w,0));
				jgraphics_stroke(g);
				
				sprintf(text,"%.2f °", (float)radtodeg(x->f_sources[i].angle));
				jtextlayout_settextcolor(jtl, &angleStrokeColor);
				jtextlayout_set(jtl, text, jf, 0, w*0.5-radius-20, w, 10, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
				jtextlayout_draw(jtl, g);
				
				jgraphics_set_dash(g, NULL, 0, 0);
			}
		}
		jtextlayout_destroy(jtl);
		jfont_destroy(jf);
		jbox_end_layer((t_object*)x, view, gensym("angle_layer"));
	 }
	jbox_paint_layer((t_object *)x, view, gensym("angle_layer"), 0., 0.);
}

void draw_head(t_hoamap *x,  t_object *view, t_rect *rect)
{
	double size;
	//double w = rect->width;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("head_layer"), rect->width, rect->height);
	t_jrgba ombrecolor = {0,0,0,0.3};
	double ombre;
	
	if (g) 
	 {
		size = rect->width*0.5;
		if(rect->width > rect->height)
			size = rect->height*0.5;
		if (x->f_zoomFactor <= 0.3) {size *= 0.3;}
		else { size *= x->f_zoomFactor; }
		
		ombre = floor(size * 0.01) + 0.5;
		
		//tête ombre
		jgraphics_set_source_jrgba(g, &ombrecolor);
		jgraphics_arc(g, rect->width * .5 + ombre, rect->height * .5 + ombre, size*0.1,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		//oreille G ombre
		jgraphics_set_line_width(g, size*(0.015));
		jgraphics_set_line_cap(g, JGRAPHICS_LINE_CAP_ROUND);
		jgraphics_arc(g, rect->width * .5 + ombre, rect->height * .5 + ombre, size*(0.12), JGRAPHICS_2PI*0.47, JGRAPHICS_2PI*0.53);
		jgraphics_stroke(g);
		//oreille D ombre
		jgraphics_arc(g, rect->width * .5 + ombre, rect->height * .5 + ombre, size*(0.12), JGRAPHICS_2PI*0.97, JGRAPHICS_2PI*0.03);
		jgraphics_stroke(g);
		// nez ombre
		jgraphics_ovalarc(g, rect->width * .5 + ombre, rect->height * .5 - size*0.05 + ombre, size*0.015, size*0.07,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		
		x->f_colorHead.alpha = 1;
		
		//tête
		jgraphics_set_source_jrgba(g, &x->f_colorHead);
		jgraphics_arc(g, rect->width * .5, rect->height * .5, size*0.1,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		//oreille G
		jgraphics_set_line_width(g, size*(0.015));
		jgraphics_set_line_cap(g, JGRAPHICS_LINE_CAP_ROUND);
		jgraphics_arc(g, rect->width * .5, rect->height * .5, size*(0.12), JGRAPHICS_2PI*0.47, JGRAPHICS_2PI*0.53);
		jgraphics_stroke(g);
		//oreille D
		jgraphics_arc(g, rect->width * .5, rect->height * .5, size*(0.12), JGRAPHICS_2PI*0.97, JGRAPHICS_2PI*0.03);
		jgraphics_stroke(g);
		// nez
		jgraphics_ovalarc(g, rect->width * .5, rect->height * .5 - size*0.05, size*0.015, size*0.07,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		
		jbox_end_layer((t_object*)x, view, gensym("head_layer"));
	 }
	jbox_paint_layer((t_object *)x, view, gensym("head_layer"), 0., 0.);
}

void draw_cartVectors(t_hoamap *x,  t_object *view, t_rect *rect)
{
	double zoom = x->f_zoomFactor;
	double w = rect->width;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("cartvectors_layer"), rect->width, rect->height);
	
	if (g) 
	 {
		
		t_jrgba red = {0.7,0,0,0.9};
		t_jrgba green = {0,0.7,0,0.9};
		char *xLetter = "x";
		char *yLetter = "y";
		
		int flechePoint = 1;
        jgraphics_set_line_width(g, 1);
		jgraphics_set_font_size(g, 10*zoom);
		
		// X
		jgraphics_set_source_jrgba(g, &red);
        jgraphics_move_to(g, pX(w,0),pY(w,0));
        jgraphics_line_to(g, pX(w,1),pY(w,0));		
		// arrow x
		jgraphics_move_to(g, pX(w,flechePoint*zoom), pY(w,0));
        jgraphics_line_to(g, pX(w,(flechePoint-0.06)*zoom), pY(w,0.03*zoom));
        jgraphics_move_to(g, pX(w,flechePoint*zoom), pY(w,0));
        jgraphics_line_to(g, pX(w,(flechePoint-0.06)*zoom), pY(w,-0.03*zoom));
		// text x
		jgraphics_move_to(g, pX(w,(flechePoint-0.1)*zoom), pY(w,0.05*zoom));
		jgraphics_show_text(g, xLetter);
		jgraphics_stroke(g);
        
		// Y
		jgraphics_set_source_jrgba(g, &green);
        jgraphics_move_to(g, pX(w,0),pY(w,0));
        jgraphics_line_to(g, pX(w,0),pY(w,1));		
		// arrow y
        jgraphics_move_to(g, pX(w,0), pY(w,flechePoint*zoom));
        jgraphics_line_to(g, pX(w,0.03*zoom), pY(w,(flechePoint-0.06)*zoom));
        jgraphics_move_to(g, pX(w,0), pY(w,flechePoint*zoom));
        jgraphics_line_to(g, pX(w,-0.03*zoom), pY(w,(flechePoint-0.06)*zoom));
		// text y
        jgraphics_move_to(g, pX(w,-0.05*zoom), pY(w,(flechePoint-0.1)*zoom));
		jgraphics_show_text(g, yLetter);
		jgraphics_stroke(g);
		
		jbox_end_layer((t_object*)x, view, gensym("cartvectors_layer"));
	 }
	jbox_paint_layer((t_object *)x, view, gensym("cartvectors_layer"), 0., 0.);
}

void draw_grid(t_hoamap *x,  t_object *view, t_rect *rect)
{
	double w = rect->width;	
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	
	long offsetIndex = ceil((1/x->f_zoomFactor));
	double offsetPos = offsetIndex*x->f_zoomFactor;
	double test = nextPow2(offsetIndex);

	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("grid_layer"), rect->width, rect->height);
	
	if (g) {
		
		t_jrgba gridcolor = x->f_colorGrid;
		gridcolor.alpha = 0.1;
		jgraphics_set_source_jrgba(g, &gridcolor);
		
		jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 10);
		jtl = jtextlayout_create();
		jtextlayout_settextcolor(jtl, &x->f_colorGrid);
		
		while(offsetPos > -1)
		 {    
			 offsetPos = offsetIndex * x->f_zoomFactor;
			 if (fmod(offsetIndex, test) == 0)
			  {
				 //offsetPos = floor(offsetPos) + 0.5;
				 jgraphics_move_to(g, pX(w,-1), pY(w,offsetPos));
				 jgraphics_line_to(g, pX(w,1),pY(w,offsetPos));
				 jgraphics_move_to(g, pX(w,offsetPos), pY(w,-1));
				 jgraphics_line_to(g, pX(w,offsetPos),pY(w,1));
				 
				 jgraphics_stroke(g);
				 
				 if (offsetIndex >= 0)
				  {
					 sprintf(text,"%ld m", offsetIndex);
					 jtextlayout_set(jtl, text, jf, pX(w, 1)-25, pY(w, offsetPos)-10, 20, 10, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
					 jtextlayout_draw(jtl, g);
				  }
				  
			  }
			 offsetIndex--;
		 }

		jbox_end_layer((t_object*)x, view, gensym("grid_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("grid_layer"), 0., 0.);
	
}

double nextPow2(double aValue) {
	double pow = 2;
	while( (aValue / pow) >= 1) {
		pow = pow*2;
	}
	return (pow)/4;
}

void draw_speakers(t_hoamap *x, t_object *view, t_rect *rect){
	//t_jrgba hpcolor = {0,0,0,0.8};
	//double w = x->rect.width;
	t_jrgba hpcolor = x->f_colorLs;
	int numHp = x->f_numberOfSpeaker;
	int offset = x->f_speakerOffset;
	double stepAngle = 360.0f/(double)numHp;
	double hpSize;
	hpSize = (rect->width / 20.) * x->f_zoomFactor;
	t_pt pix;
	t_pol pol;
	int i;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("ls_layer"), rect->width, rect->height);
	
	if (g) {
		
		jgraphics_set_source_jrgba(g, &hpcolor);
		
		/*
		jgraphics_matrix_translate(&transform, pX(w,0), pY(w,0));
		jgraphics_matrix_init_rotate(&transform, 45 * JGRAPHICS_PI * (1./180.));
		jgraphics_matrix_translate(&transform, pX(w, 0), pY(w,x->f_speakerToHeadDistance*x->f_zoomFactor));
		jgraphics_set_matrix(g, &transform);
		draw_oneLs(x, g, 0, 0, 0, 10);
		*/
		
		for(i=0; i<numHp; i++)
		{			
			pol.r = x->f_speakerToHeadDistance;
			pol.a = degtorad(i*stepAngle+offset);
			//pol.r = x->f_speakerToHeadDistance*x->f_zoomFactor;
			//pol.a = degtorad(i*stepAngle);
			//pix = poltopix(x, pol, 1);
			
			//cart = poltocar(pol.r, pol.a);
			//draw_oneLs(x, g, pX(w,cart.x), pY(w,cart.y), i*stepAngle+offset, 10);
			
			pix = poltopix(x, pol, 1);
			//draw_oneLs(x, g, pix.x, pix.y, i*stepAngle+offset, 30*x->f_zoomFactor);
			draw_oneLs(x, g, pix.x, pix.y, i*stepAngle+offset, hpSize);
			
			jgraphics_fill(g);
			//draw_oneLs(x, g, pX(w, 0)+i*20, pY(w,x->f_speakerToHeadDistance*x->f_zoomFactor), i*stepAngle, 10);
			//jgraphics_fill(g);
		}
		jbox_end_layer((t_object*)x, view, gensym("ls_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("ls_layer"), 0., 0.);
}

void draw_oneLs(t_hoamap *x, t_jgraphics *g, double posX, double posY, double rotDegree, double size){
	
	double w = x->rect.width;
	t_jmatrix transform;
	size *= 0.5;
	
	//jgraphics_matrix_translate(&transform, pX(w,0), pY(w,0));
	jgraphics_matrix_translate(&transform, w*0.5, w*0.5);
	jgraphics_matrix_init_rotate(&transform, rotDegree * JGRAPHICS_PI * (1./180.));
	jgraphics_matrix_translate(&transform, posX, posY);
	jgraphics_set_matrix(g, &transform);
	
	jgraphics_move_to(g, -size, 0);
	jgraphics_line_to(g, -size, -size);
	jgraphics_line_to(g, +size, -size);
	jgraphics_line_to(g, +size, 0);
	jgraphics_line_to(g, +size*2, +size);
	jgraphics_line_to(g, -size*2, +size);
	jgraphics_close_path(g);
	
	//jgraphics_path_roundcorners(g, size*0.25);
}

void draw_background(t_hoamap *x,  t_object *view, t_rect *rect)
{
	double w = x->rect.width;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);
	
	if (g) {
		t_jrgba outsideColor = {0,0,0,0.1};
		
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		//jgraphics_rectangle_fill_fast(g, 0., 0., rect->width, rect->height);
		jgraphics_rectangle_rounded(g, 0., 0., w, w, 6, 6);
		jgraphics_fill(g);
		jgraphics_set_source_jrgba(g, &outsideColor);
		//jgraphics_rectangle_fill_fast(g, 0., 0., rect->width, rect->height);
		jgraphics_rectangle_rounded(g, 0., 0., w, w, 6, 6);
		jgraphics_fill(g);
		
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_arc(g, pX(w, 0), pY(w, 0), w*0.5*x->f_speakerToHeadDistance*x->f_zoomFactor,  0., JGRAPHICS_2PI);
		jgraphics_fill(g);
		
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);
}

void draw_rect_selection(t_hoamap *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("rect_selection_layer"), rect->width, rect->height);
	t_rect sel;
	
	if (g) {
		if (x->f_rect_selection_exist) {
			sel.x = floor(x->f_rect_selection.x) + 0.5;
			sel.y = floor(x->f_rect_selection.y) + 0.5;
			sel.width = x->f_rect_selection.width;
			sel.height = x->f_rect_selection.height;
			
			//t_jrgba fillcolor = {0,0,1,0.05};
			t_jrgba fillcolor = x->f_color_selection;
			fillcolor.alpha = 0.05;
			t_jrgba strokecolor = fillcolor;
			strokecolor.alpha = 0.2;
			
			jgraphics_set_source_jrgba(g, &fillcolor);
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


////////////////////////////////////////////////////////

// Mouse :

// Quand la souris rentre dans l'objet en up :
void hoamap_mouseenter(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
	//post("mouseenter");
}

////////////////////////////

// Quand la souris quitte l'objet apres y être entree en up :
void hoamap_mouseleave(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
	//post("mouseleave");
}

////////////////////////////

int which_source_pointed(t_hoamap *x, t_pt pt)
{
	int i;
	int sourcePointed = -1;
	for(i = 0; i < x->f_numberOfSources; i++) {
		if (is_in_circle(pt.x, pt.y, pX(x->rect.width,x->f_sources[i].pos.x * x->f_zoomFactor), pY(x->rect.height,x->f_sources[i].pos.y * x->f_zoomFactor), x->f_sourceSize)) {
			sourcePointed = i;
		}
	}
	return sourcePointed;
}

void hoamap_mousedown(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{	
	t_pt cart_pt = pixtocar(x, pt);
	//int i;
	
	// rajoute une source si aucune n'est presente.
	if(x->f_numberOfSources == 0) {
		hoamap_add(x, cart_pt.x , cart_pt.y);
	}
	
	int sourceClicked = which_source_pointed(x, pt);
	if (sourceClicked != -1)
	{
	   // on selectionne plusieurs sources
	   if(modifiers == 17 || modifiers == 273) { // cmd
		   update_source_selection(x, sourceClicked, -1);
	   }else {
		   jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_POINTINGHAND);
		   hoamap_outone(x, sourceClicked);
	   }
	   x->f_aSourceIsSelected = 1;
	   x->f_actualSource = sourceClicked + 1;
	   x->f_sources[sourceClicked].hasfocus = 1;
	}
	else
	{
		// on selectionne plusieurs sources
		/*
		 if(modifiers == 17 || modifiers == 273) { // cmd
		 jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_CROSSHAIR);
		 x->f_rect_selection.x = pt.x;
		 x->f_rect_selection.y = pt.y;
		 x->f_rect_selection_exist = 1;
		 }
		 */
		jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_CROSSHAIR);
		x->f_rect_selection.x = pt.x;
		x->f_rect_selection.y = pt.y;
		x->f_rect_selection_exist = 1;
		
		update_source_selection(x, -1, 0);
		x->f_aSourceIsSelected = 0;
		x->f_actualSource = 0;		
	}
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
	jbox_redraw((t_jbox *)x);
}


void hoamap_mousedrag(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
	int i;
	t_pol polin;
	double diff;
	t_pol polout;
	double factor;
	t_pt pixSource;
	t_pt pixDiff;
	
	if (x->f_aSourceIsSelected) {
		jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_POINTINGHAND);
		x->f_sources[x->f_actualSource-1].hasfocus = 1;
		
		if(modifiers == 148 || modifiers == 404) // ctrl -> angle.
		{
			// on limite le drag à l'angle
			polin = pixtopol(x, pt);
			diff = polin.a - x->f_sources[x->f_actualSource-1].angle;
			for(i=0; i<x->f_numberOfSources; i++)
			{
				if (x->f_sources[i].selected || i == x->f_actualSource-1) 
				{
					update_source_pos_in_polar(x, i, x->f_sources[i].distance, x->f_sources[i].angle + diff);
				}
			}
		}
		else if(modifiers == 18 || modifiers == 274) // shift -> distance (rayon)
		{
			// on limite le drag à la distance
			polin = pixtopol(x, pt);
			
			if (x->f_sources[x->f_actualSource-1].distance != 0.) {
				factor = polin.r / x->f_sources[x->f_actualSource-1].distance;
			} else {
				factor = 0.;
			}
			
			for(i=0; i<x->f_numberOfSources; i++)
			{
				if (x->f_sources[i].selected || i == x->f_actualSource-1) 
				{
					polout.a = x->f_sources[i].angle;
					polout.r = x->f_sources[i].distance * factor;
					if (polout.r == 0.) {
						polout.r = 0.00001;
					}
					update_source_pos_in_polar(x, i, polout.r, polout.a);
				}
			}			
		}
		else 
		{
			pixSource = cartopix(x, x->f_sources[x->f_actualSource-1].pos, 0);
			pixDiff.x = pt.x - pixSource.x;
			pixDiff.y = pt.y - pixSource.y;
			for(i=0; i<x->f_numberOfSources; i++)
			{
				if (x->f_sources[i].selected || i == x->f_actualSource-1)
				{
					pixSource = cartopix(x, x->f_sources[i].pos, 0);
					pixSource.x += pixDiff.x;
					pixSource.y += pixDiff.y;
					update_source_pos_in_pixel(x, i, pixSource);
				}
			}
		}

		jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
		jbox_redraw((t_jbox *)x);
	}
	else {
		
		// on selectionne plusieurs sources
		/*
		if(modifiers == 17 || modifiers == 273) // cmd
		{
			jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_CROSSHAIR);
			x->f_rect_selection.width = pt.x - x->f_rect_selection.x;
			x->f_rect_selection.height = pt.y - x->f_rect_selection.y;
			jbox_invalidate_layer((t_object *)x, NULL, gensym("rect_selection_layer"));
			jbox_redraw((t_jbox *)x);
		}
		*/
		jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_CROSSHAIR);
		x->f_rect_selection.width = pt.x - x->f_rect_selection.x;
		x->f_rect_selection.height = pt.y - x->f_rect_selection.y;
		jbox_invalidate_layer((t_object *)x, NULL, gensym("rect_selection_layer"));
		jbox_redraw((t_jbox *)x);
	}

}

////////////////////////////

void hoamap_mouseup(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect sel = x->f_rect_selection;
	t_pt pix;
	int i;
	
	if (x->f_rect_selection_exist) 
	{
		if (pt.x < sel.x) sel.x = pt.x;
		if (pt.y < sel.y) sel.y = pt.y;
		sel.width = fabs(sel.width);
		sel.height = fabs(sel.height);
		
		for(i=0; i<x->f_numberOfSources; i++)
		{
		   pix = cartopix(x, x->f_sources[i].pos, 0);
		   if ( (pix.x >= sel.x) && (pix.x <= sel.x+sel.width) && (pix.y >= sel.y) && (pix.y <= sel.y+sel.height) ) 
		   {
			   update_source_selection(x, i, 1);
		   }
		   else
		   {
			   update_source_selection(x, i, 0);
		   }
		}
	}
	x->f_rect_selection_exist = x->f_rect_selection.x = x->f_rect_selection.y = x->f_rect_selection.width = x->f_rect_selection.height = 0;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("rect_selection_layer"));
	jbox_redraw((t_jbox *)x);
}

////////////////////////////

// focus sur l'objet :
void hoamap_focusgained(t_hoamap *x, t_object *patcherview)
{
	//post("focusGain");
}

// focus perdu sur l'objet :
void hoamap_focuslost(t_hoamap *x, t_object *patcherview)
{
	//post("You have lost the keyboard focus.");
	//jbox_redraw((t_jbox *)x);
}

////////////////////////////////////////////////////////

// Mouse Move (when mouse up move over the locked view inside the Objet) :

void hoamap_mousemove(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
	int i;
	int sourcePointed = 0;
	if (pt.x != x->f_last_mousemove.x || pt.y != x->f_last_mousemove.y) {
		for(i = 0; i < x->f_numberOfSources; i++) {
			if (is_in_circle(pt.x, pt.y, pX(x->rect.width,x->f_sources[i].pos.x * x->f_zoomFactor), pY(x->rect.height,x->f_sources[i].pos.y * x->f_zoomFactor), x->f_sourceSize)) {
				sourcePointed++;
				x->f_sources[i].hasfocus = 1;
			} else {
				x->f_sources[i].hasfocus = 0;
			}
			//post("x(%f),y(%f) => src %i (%f / %f / %f).", pt.x, pt.y, i, pX(x->rect.width,x->f_sources[i].pos.x * x->f_zoomFactor), pY(x->rect.height,x->f_sources[i].pos.y * x->f_zoomFactor), x->rect.width/60.0f);
		}
		if (sourcePointed) {
			jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_POINTINGHAND);
		}
		else {
			jmouse_setcursor(patcherview, (t_object *)x, JMOUSE_CURSOR_ARROW);
		}
	}
	x->f_last_mousemove = pt;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sources_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("angle_layer"));
	jbox_redraw((t_jbox *)x);
}

// Mouse Delta (calcul la difference entre la position du dernier down et position courante) :

void hoamap_mousedragdelta(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers)
{
	//click'n drag method :
	//post("mousedragdelta");
	//post("mouseX = %f, mouseY = %f", pt.x, pt.y);
}

// key intercept
long hoamap_key(t_hoamap *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
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
		update_source_selection(x, -1, 1);
	}
	else if (keycode == 120 && modifiers == 1 && textcharacter == 0) { // cmd+e -> switch lock/unlock mode;
		//post("switch to edit/play patch mode");
		//jpatcher_set_locked(patcherview, (char)locked);
	}
	
	return 1;	// returns 1 if you want to filter it from the key object (otherwise return 0)
}


void hoamap_mousewheel(t_hoamap *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	// alt (mac) = 8 | 264
	long alt = eAltKey;
	double newZoom;
	
#ifdef WIN_VERSION
#endif
	
	if (modifiers == alt) {
		newZoom = x->f_zoomFactor + y_inc;
		hoamap_zoom(x, newZoom);
	}
}
