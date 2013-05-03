#ifdef WIN_VERSION
#define _CRT_SECURE_NO_DEPRECATE
#endif

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "ext_parameter.h"
#include "z_dsp.h"

#ifdef WIN_VERSION
#include <float.h>
#endif
}

#include "../cicmTools.h"
#include "CicmLine.h"

#define MAX_IO 64
#define MIN_IO 1
#define DEF_IO 8

static t_class	*s_hoaGain_class = 0;
static t_symbol *ps_slider, *ps_hslider, *ps_preset;

// mouse tracking stuff

static t_pt s_hoaGain_cum;
static double s_hoaGain_startval;

#define INRANGE(v,lo,hi) ((v)<=(hi)&&(v)>=(lo))

#define	hoaGain_BORDERTHICKNESS			(2.)
#define hoaGain_CORNERSIZE				(6.)

//#define hoaGain_DISPLAYINSET			5		// amount subtracted from rect for value
#define hoaGain_DISPLAYINSET			11		// amount subtracted from rect for value

typedef struct _hoaGain
{
	t_pxjbox	j_box;
	double		j_min;			
	double		j_size;			// number of steps
	double		j_val;
	char		j_relative;		// relative mousing (like orig miller slider, but not like h/uslider)
	char		j_orientation;	// 0 = auto, 1 = horiz, 2 = vertical
	t_jrgba		j_brgba;
	t_jrgba		j_frgba;
	t_jrgba		j_frgba2;
    t_jrgba     j_dbgridcolorneg;
    t_jrgba     j_dbgridcolorpos;
    t_jrgba     j_knobcolor;
    t_jrgba     j_intknobcolor;
    
    // gain
    CicmLine*   f_amp;
    float       f_range[2];
    double      j_valdB;
    
    //inputs/output
    void*       f_inlet_val;
    void*       f_outlet_infos;
    
    // options
    double          f_interp;
    t_atom_long     f_numberOfChannels;
    
} t_hoaGain;

void *hoaGain_new(t_symbol *s, short argc, t_atom *argv);
void hoaGain_free(t_hoaGain *x);
t_max_err hoaGain_notify(t_hoaGain *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void hoaGain_assist(t_hoaGain *x, void *b, long m, long a, char *s);
void hoaGain_preset(t_hoaGain *x);
void *hoaGain_stdargs(t_dictionary *d, t_symbol *s, long argc, t_atom *argv);
/* DSP ------------------------------------- */
void hoaGain_dsp(t_hoaGain *x, t_signal **sp, short *count);
t_int *hoaGain_perform(t_int *w);
void hoaGain_dsp64(t_hoaGain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoaGain_perform64(t_hoaGain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void hoaGain_tick(t_hoaGain *x);
void hoaGain_output_dB(t_hoaGain *x);
/* Paint ------------------------------------- */
long hoaGain_oksize(t_hoaGain *x, t_rect *newrect);
void hoaGain_paint(t_hoaGain *x, t_object *view);
void draw_cursor(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz);
void draw_dB_grid(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz);
void hoaGain_getdrawparams(t_hoaGain *x, t_object *patcherview, t_jboxdrawparams *params);
/* Input ------------------------------------- */
void hoaGain_bang(t_hoaGain *x);
void hoaGain_int(t_hoaGain *x, long n);
void hoaGain_float(t_hoaGain *x, double f);
void hoaGain_set(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv);
void hoaGain_setminmax(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv);
t_max_err hoaGain_setattr_interp(t_hoaGain *x, t_object *attr, long ac, t_atom *av);
t_max_err hoaGain_setattr_channels(t_hoaGain *x, t_object *attr, long ac, t_atom *av);
t_max_err hoaGain_setattr_range(t_hoaGain *x, t_object *attr, long ac, t_atom *av);
t_max_err hoaGain_setvalueof(t_hoaGain *x, long ac, t_atom *av);
t_max_err hoaGain_getvalueof(t_hoaGain *x, long *ac, t_atom **av);
/* Utility ------------------------------------- */
void hoaGain_assign(t_hoaGain *x, double f, long notify);
double hoaGain_constrain(t_hoaGain *x, double f);
double hoaGain_constrain_real_value(t_hoaGain *x, double f);
char hoaGain_ishorizontal(t_hoaGain *x, t_rect *r);
double hoaGain_postoval(t_hoaGain *x, t_pt pt, t_rect *r, char ishoriz);
double hoaGain_valtopos(t_hoaGain *x, double val, t_rect *r, char ishoriz);
double hoaGain_dBvaltopos(t_hoaGain *x, double dBval, t_rect *r, char ishoriz);
double hoaGain_dbtoval(t_hoaGain *x, double dBval);
double hoaGain_valtodb(t_hoaGain *x, double val);
/* Mouse ------------------------------------- */
void hoaGain_mousedoubleclick(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaGain_mousedown(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaGain_mousedragdelta(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers);
void hoaGain_mouseup(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers);

void hoaGain_set_gain(t_hoaGain *x);

int C74_EXPORT main()
{
	t_class *c; 

	common_symbols_init();

	c = class_new("hoa.gain~", (method)hoaGain_new, (method)hoaGain_free, sizeof(t_hoaGain), (method)NULL, A_GIMME, 0L);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY; // to specify dictionary constructor

    class_dspinitjbox(c);
	jbox_initclass(c, JBOX_FIXWIDTH | JBOX_COLOR | JBOX_FONTATTR);
    
    class_addmethod (c, (method) hoaGain_dsp,                 "dsp",                  A_CANT, 0);
	class_addmethod (c, (method) hoaGain_dsp64,               "dsp64",                A_CANT, 0);
	class_addmethod (c, (method) hoaGain_paint,               "paint",                A_CANT, 0);
	class_addmethod (c, (method) hoaGain_int,                 "int",                  A_LONG, 0);
	class_addmethod (c, (method) hoaGain_float,               "float",                A_FLOAT, 0);
	class_addmethod (c, (method) hoaGain_bang,                "bang",                         0);
	class_addmethod (c, (method) hoaGain_set,                 "set",                  A_GIMME, 0);
	class_addmethod (c, (method) hoaGain_setminmax,           "setminmax",            A_GIMME, 0);
	class_addmethod (c, (method) hoaGain_getdrawparams,       "getdrawparams",        A_CANT, 0);
    class_addmethod (c, (method) hoaGain_mousedoubleclick,    "mousedoubleclick",     A_CANT, 0);
	class_addmethod (c, (method) hoaGain_mousedown,           "mousedown",            A_CANT, 0);
	class_addmethod (c, (method) hoaGain_mousedragdelta,      "mousedragdelta",       A_CANT, 0);
	class_addmethod (c, (method) hoaGain_mouseup,             "mouseup",              A_CANT, 0);
	class_addmethod (c, (method) hoaGain_getvalueof,          "getvalueof",           A_CANT, 0);
	class_addmethod (c, (method) hoaGain_setvalueof,          "setvalueof",           A_CANT, 0);
	class_addmethod (c, (method) hoaGain_assist,              "assist",               A_CANT, 0);
	class_addmethod (c, (method) hoaGain_preset,              "preset",                       0);
	class_addmethod (c, (method) hoaGain_notify,              "notify",               A_CANT, 0); 
	class_addmethod (c, (method) hoaGain_oksize,              "oksize",               A_CANT, 0);
    
	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 20. 140.");
	
	CLASS_STICKY_CATEGORY(c,0,"Value");
    
    CLASS_ATTR_DOUBLE       (c, "interp", 0, t_hoaGain, f_interp);
	CLASS_ATTR_ACCESSORS    (c, "interp",(method)NULL,(method)hoaGain_setattr_interp);
    CLASS_ATTR_LABEL        (c, "interp", 0, "Ramp Time (ms)");
    CLASS_ATTR_FILTER_MIN   (c, "interp", 0);
	
	CLASS_ATTR_CHAR(c,"relative", 0, t_hoaGain, j_relative);
	CLASS_ATTR_LABEL(c,"relative", 0, "Mousing Mode");
	CLASS_ATTR_ENUMINDEX2(c, "relative", 0, "Absolute", "Relative");
	CLASS_ATTR_BASIC(c, "relative", 0);
	CLASS_STICKY_CATEGORY_CLEAR(c);
	
	CLASS_ATTR_CHAR(c,"orientation",0,t_hoaGain,j_orientation);
	CLASS_ATTR_LABEL(c,"orientation",0,"Orientation");
	CLASS_ATTR_ENUMINDEX3(c,"orientation", 0,"Automatic", "Horizontal", "Vertical");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "orientation", 0, "0");
	CLASS_ATTR_CATEGORY(c, "orientation", 0, "Appearance");
	
	CLASS_STICKY_CATEGORY(c, 0, "Color");
	CLASS_ATTR_RGBA_LEGACY(c, "bgcolor", "brgb", 0, t_hoaGain, j_brgba);
	CLASS_ATTR_ALIAS(c,"bgcolor", "brgba");
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c,"bgcolor",0,"1. 1. 1. 1.");
	CLASS_ATTR_STYLE_LABEL(c, "bgcolor", 0, "rgba", "Background Color");
	class_parameter_register_default_color(c, gensym("bgcolor"), ps_control_text_bg);
	CLASS_ATTR_BASIC(c, "bgcolor", 0);
	
	CLASS_ATTR_RGBA_LEGACY(c,"knobcolor","frgb", 0, t_hoaGain, j_frgba);
	CLASS_ATTR_ALIAS(c,"knobcolor", "frgba");
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c,"knobcolor",0,"0.2 0.2 0.2 1.");
	CLASS_ATTR_STYLE_LABEL(c, "knobcolor",0,"rgba","Knob Color");
	class_parameter_register_default_color(c, gensym("knobcolor"), ps_contrast_frame);
	CLASS_ATTR_BASIC(c, "knobcolor", 0);
	
	CLASS_ATTR_RGBA_LEGACY(c,"bordercolor", "rgb2",0, t_hoaGain, j_frgba2);
	CLASS_ATTR_ALIAS(c,"bordercolor", "rgba2");
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c,"bordercolor",0,"0.5 0.5 0.5 1.");
	CLASS_ATTR_STYLE_LABEL(c,"bordercolor",0,"rgba","Border Color");
	class_parameter_register_default_color(c, gensym("bordercolor"), ps_control_bg);
	CLASS_STICKY_CATEGORY_CLEAR(c);
    
    CLASS_ATTR_RGBA				(c, "dbgridcolorneg", 0, t_hoaGain, j_dbgridcolorneg);
	CLASS_ATTR_CATEGORY			(c, "dbgridcolorneg", 0, "Color");
	CLASS_ATTR_STYLE			(c, "dbgridcolorneg", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "dbgridcolorneg", 0, "Negative dB Grid Color");
	CLASS_ATTR_ORDER			(c, "dbgridcolorneg", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "dbgridcolorneg", 0, "0.6 0.1 0.1 1");
    
    CLASS_ATTR_RGBA				(c, "dbgridcolorpos", 0, t_hoaGain, j_dbgridcolorpos);
	CLASS_ATTR_CATEGORY			(c, "dbgridcolorpos", 0, "Color");
	CLASS_ATTR_STYLE			(c, "dbgridcolorpos", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "dbgridcolorpos", 0, "Postive dB Grid Color");
	CLASS_ATTR_ORDER			(c, "dbgridcolorpos", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "dbgridcolorpos", 0, "0.6 0.1 0.1 1");
    
    CLASS_ATTR_RGBA				(c, "knobcolor", 0, t_hoaGain, j_knobcolor);
	CLASS_ATTR_CATEGORY			(c, "knobcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "knobcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "knobcolor", 0, "Knob Color");
	CLASS_ATTR_ORDER			(c, "knobcolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "knobcolor", 0, "0.6 0.6 0.6 1");
    
    CLASS_ATTR_RGBA				(c, "intknobcolor", 0, t_hoaGain, j_intknobcolor);
	CLASS_ATTR_CATEGORY			(c, "intknobcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "intknobcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "intknobcolor", 0, "Knob Color");
	CLASS_ATTR_ORDER			(c, "intknobcolor", 0, "9");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "intknobcolor", 0, "0.6 0.6 0.6 1");

	CLASS_ATTR_INVISIBLE(c, "color", 0);
	CLASS_ATTR_ATTR_PARSE(c, "color","save", USESYM(long), 0, "0");

	CLASS_ATTR_DEFAULT_SAVE(c,"relative",0,"0");
    CLASS_ATTR_DEFAULT_SAVE(c,"interp",0,"20");
	CLASS_ATTR_LABEL(c,"min", 0, "Output Minimum");
	CLASS_ATTR_LABEL(c,"mult", 0, "Output Multiplier");
	CLASS_ATTR_STYLE_LABEL(c,"floatoutput",0,"onoff","Float Output");
	
	CLASS_ATTR_ORDER(c, "relative",		0, "2");
	CLASS_ATTR_ORDER(c, "size",			0, "3");
	CLASS_ATTR_ORDER(c, "min",			0, "4");
	CLASS_ATTR_ORDER(c, "mult",			0, "5");
    
    CLASS_ATTR_CATEGORY			(c, "channels", 0, "Custom");
    CLASS_ATTR_LONG				(c, "channels", 0, t_hoaGain, f_numberOfChannels);
    CLASS_ATTR_ACCESSORS        (c, "channels", (method)NULL,(method)hoaGain_setattr_channels);
	CLASS_ATTR_ORDER			(c, "channels", 0, "1");
	CLASS_ATTR_LABEL			(c, "channels", 0, "Number of Channels");
	CLASS_ATTR_FILTER_CLIP		(c, "channels", 1, MAX_IO);
	CLASS_ATTR_DEFAULT			(c, "channels", 0, "8");
	CLASS_ATTR_SAVE				(c, "channels", 1);
    
    CLASS_ATTR_CATEGORY			(c, "range", 0, "Value");
    CLASS_ATTR_FLOAT_ARRAY      (c, "range", 0, t_hoaGain, f_range, 2);
    CLASS_ATTR_ACCESSORS        (c, "range", (method)NULL,(method)hoaGain_setattr_range);
	CLASS_ATTR_ORDER			(c, "range", 0, "2");
	CLASS_ATTR_LABEL			(c, "range", 0, "Display Range (dB)");
	CLASS_ATTR_DEFAULT			(c, "range", 0, "-70. 6.");
	CLASS_ATTR_SAVE             (c, "range", 1);

	class_register(CLASS_BOX, c);
	s_hoaGain_class = c;
	
	ps_hslider = gensym("hslider");
	ps_slider = gensym("slider");
	ps_preset = gensym("_preset");
    
    class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
    
	return 0;
}

void *hoaGain_new(t_symbol *s, short argc, t_atom *argv)
{
	t_hoaGain* x;
	long flags; 
	t_dictionary *d=NULL;
	
	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;
	
	x = (t_hoaGain *) object_alloc(s_hoaGain_class);
	if (!x)
		return NULL;

	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_NODRAWBOX
			| JBOX_DRAWINLAST			// rbs -- I think we can turn this off
			| JBOX_GROWBOTH
			| JBOX_DRAWBACKGROUND
			| JBOX_MOUSEDRAGDELTA
			;

	x->j_val = 0;
    x->j_valdB = 0;
    x->f_interp = 20;
    
    dictionary_getlong(d, gensym("channels"), &x->f_numberOfChannels); // make sure we have the number of inputs before set up other args.
	jbox_new((t_jbox *)x, flags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
    
    x->f_amp = new CicmLine(sys_getblksize(), sys_getsr(), 100.);
    
    attr_dictionary_process(x,d); // handle attribute args
    
    // inputs
	dsp_setupjbox((t_pxjbox *)x, x->f_numberOfChannels + 1);
    // outputs
    x->f_outlet_infos = outlet_new(x, NULL);
    for (int i=0; i < x->f_numberOfChannels; i++)
        outlet_new(x,"signal");
        //outlet_append((t_object *)x, NULL, gensym("signal"));
    
    jbox_ready((t_jbox *)x);
    x->j_box.z_misc = Z_NO_INPLACE;
	return x;
}

long hoaGain_oksize(t_hoaGain *x, t_rect *newrect)
{
    long min = 14;
    if (newrect->width < min) newrect->width = min;
    if (newrect->height < min) newrect->height = min;
    return 0;
}

void hoaGain_assist(t_hoaGain *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET)
    {
        if (a != x->f_numberOfChannels)
            sprintf(s,"(signal) Audio Signal to be Scaled (ch %ld)", a+1);
        else
			sprintf(s,"(Int/Float) Set Value");
	} 
	else {
		if (a != x->f_numberOfChannels)
            sprintf(s,"(signal) Scaled Signal (ch %ld)", a+1);
        else
			sprintf(s,"(Float) Value in dB (%.2f-%.2f)", x->f_range[0], x->f_range[1]);
	}
}

void hoaGain_preset(t_hoaGain *x)
{
	void *z;
	if (!(z = ps_preset->s_thing))
		return;
    binbuf_vinsert(z,(char*)"ossf",x,object_classname(x), _sym_float, x->j_val + x->j_min);
}

void hoaGain_free(t_hoaGain *x)
{
    dsp_freejbox((t_pxjbox *)x);
	jbox_free((t_jbox *)x);
    delete x->f_amp;
}

/* DSP ------------------------------------- */
void hoaGain_dsp(t_hoaGain *x, t_signal **sp, short *count)
{
    int i;
	int pointer_count;
	t_int **sigvec;
	
	pointer_count = x->f_numberOfChannels*2 + 3;
	
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));
	for(i = 0; i < pointer_count; i++)
		sigvec[i] = (t_int *)calloc(1, sizeof(t_int));
	
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_n;
	for(i = 2; i < pointer_count; i++)
		sigvec[i] = (t_int *)sp[i - 2]->s_vec;
    
    x->f_amp->setSampleRate(sp[0]->s_sr);
    x->f_amp->setVectorSize(sp[0]->s_n);
	
	dsp_addv(hoaGain_perform, pointer_count, (void **)sigvec);
	
	free(sigvec);
}
t_int *hoaGain_perform(t_int *w)
{
    t_hoaGain *x			= (t_hoaGain *)(w[1]);
	t_int	sampleframes= (t_int)(w[2]);
	t_float	**ins		= (t_float **)w+3;
    t_float	**outs		= (t_float **)w+3+x->f_numberOfChannels+1;
	int i, j;
	
	for(i = 0; i < x->f_numberOfChannels; i++)
	{
		for(j = 0; j < sampleframes; j++)
		{
			outs[i][j] = ins[i][j] * x->f_amp->process();
		}
	}
	return (w + x->f_numberOfChannels*2 + 4);
}
void hoaGain_dsp64(t_hoaGain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    x->f_amp->setSampleRate(samplerate);
    x->f_amp->setVectorSize(maxvectorsize);
    post("interp ms = %f", x->f_amp->getRampTimeInMs());
    post("ramp samples = %ld", (long)x->f_amp->getRampTimeInSamps());
    object_method(dsp64, gensym("dsp_add64"), x, hoaGain_perform64, 0, NULL);
}
void hoaGain_perform64(t_hoaGain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int i, j;
    double line[sampleframes];
    
    x->f_amp->process(line);
    
    
        for(i = 0; i < x->f_numberOfChannels; i++)
		{
            Cicm_Matrix_Vector_Mul(ins[i], line, outs[i], sampleframes);
		}
}

void hoaGain_set_gain(t_hoaGain *x)
{
    x->f_amp->setCoefficient( x->j_valdB >= -70.0f ? Tools::dbtoa(x->j_valdB) : 0.0f );
}

/* Paint ------------------------------------- */
void hoaGain_paint(t_hoaGain *x, t_object *view)
{
	t_rect rect;
    char isHoriz;
	jbox_get_rect_for_view((t_object *)x, view, &rect);
    isHoriz = hoaGain_ishorizontal(x, &rect);
    //draw_dB_grid(x, view, &rect, isHoriz);
    draw_cursor(x, view, &rect, isHoriz);
}

void draw_cursor(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz)
{    
	t_jgraphics *g;
    t_jfont *jf;
	t_jtextlayout *jtl;
    double fontsize = Tools::clip(int(rect->height/4), int(12), int(20));
    char dBCurrentTextValue[10];
	int pos;
    double dBval = x->j_valdB;
    t_rect textPos;
    textPos.width = fontsize*6;
    textPos.height = fontsize*2;
    t_jgraphics_text_justification textjustification = JGRAPHICS_TEXT_JUSTIFICATION_LEFT;
    
    g = jbox_start_layer((t_object *)x, view, gensym("cursor_layer"), rect->width, rect->height);
	jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_BOLD, fontsize);
    jtl = jtextlayout_create();
    
	if (g)
	{
        dBval = CLAMP(dBval, x->f_range[0], x->f_range[1]);
        pos = hoaGain_dBvaltopos(x, dBval, rect, isHoriz);
        
        if (x->j_valdB > -70.0f) {
            sprintf(dBCurrentTextValue,"%.2f dB", x->j_valdB);
        } else sprintf(dBCurrentTextValue,"-inf dB");
                
        if (isHoriz) {
            if (pos <= rect->width*0.5) {
                textPos.x = pos+3;
                textPos.y = 3;
            }
            else
            {
                textPos.x = pos - textPos.width - 3;
                textjustification = JGRAPHICS_TEXT_JUSTIFICATION_RIGHT;
                textPos.y = -fontsize*0.25;
            }
            
            // draw knob rect
            jgraphics_set_source_jrgba(g, &x->j_knobcolor);
            jgraphics_rectangle(g, pos-5, 4, 11, rect->height - 8);
            jgraphics_fill(g);
            
            //draw knob interior line
            jgraphics_set_source_jrgba(g, &x->j_intknobcolor);
            jgraphics_set_line_width(g,1);
            jgraphics_move_to(g, long(pos)+0.5-3, 6);
            jgraphics_line_to(g, long(pos)+0.5-3, rect->height - 6);
            jgraphics_move_to(g, long(pos)+0.5, 6);
            jgraphics_line_to(g, long(pos)+0.5, rect->height - 6);
            jgraphics_move_to(g, long(pos)+0.5+3, 6);
            jgraphics_line_to(g, long(pos)+0.5+3, rect->height - 6);
            jgraphics_stroke(g);
            
        } else {
            
        }
        
        jtextlayout_settextcolor(jtl, &x->j_frgba);
        jtextlayout_set(jtl, dBCurrentTextValue, jf, textPos.x, textPos.y, textPos.width, textPos.height, textjustification, JGRAPHICS_TEXTLAYOUT_USEELLIPSIS);
        //jtextlayout_draw(jtl, g);
	}
    jtextlayout_destroy(jtl);
    jfont_destroy(jf);
    jbox_end_layer((t_object*)x, view, gensym("cursor_layer"));
	jbox_paint_layer((t_object *)x, view, gensym("cursor_layer"), 0., 0.);
}

void draw_dB_grid(t_hoaGain *x, t_object *view, t_rect *rect, char isHoriz)
{
	t_jgraphics *g;
    t_jfont *jf;
	t_jtextlayout *jtl;
    char dBCurrentTextValue[100];
    double fontsize = 12;
	int zerodBpos, dBpos;
	//double val = x->j_val;
    double dbStep = 6;
    int nbMark = 30;
    int markerSize = 20;
    int tempMarkerSize;
    int stepSize = (rect->width-6)/nbMark;
    t_jrgba black = {0,0,0,1};
    
    zerodBpos = hoaGain_dBvaltopos(x, 0, rect, isHoriz);
    
    g = jbox_start_layer((t_object *)x, view, gensym("dbGrid_layer"), rect->width, rect->height);
    
    jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize);
    jtl = jtextlayout_create();
    
    if (g) {
        
        if (isHoriz) {
            // draw negative dB grid :
            jgraphics_set_line_width(g,1);
            jgraphics_set_source_jrgba(g, &x->j_dbgridcolorneg);
            jgraphics_move_to(g, 3-0.5, rect->height*0.5+0.5);
            jgraphics_line_to(g, zerodBpos,rect->height*0.5+0.5);
            jgraphics_stroke(g);
            
            jtextlayout_settextcolor(jtl, &x->j_dbgridcolorneg);
            for (int i=0; i < long(x->f_range[0]/dbStep)*-1; i++)
            {
                dBpos = hoaGain_dBvaltopos(x, -dbStep*(i+1), rect, isHoriz);
                jgraphics_move_to(g, long(dBpos)+0.5, rect->height*0.5);
                jgraphics_line_to(g, long(dBpos)+0.5, rect->height*0.5 + markerSize);
                jgraphics_stroke(g);
                // negative text dB value
                sprintf(dBCurrentTextValue,"%ld", long(-dbStep*(i+1)));
                jtextlayout_set(jtl, dBCurrentTextValue, jf, dBpos-20, (rect->height*0.5)+(markerSize)+4, 40, 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_USEELLIPSIS);
                jtextlayout_draw(jtl, g);
            }
            
            // draw positive dB grid :
            jgraphics_set_line_width(g,1);
            jgraphics_set_source_jrgba(g, &x->j_dbgridcolorpos);
            jgraphics_move_to(g, zerodBpos, rect->height*0.5+0.5);
            jgraphics_line_to(g, rect->width - 0.3,rect->height*0.5+0.5);
            jgraphics_stroke(g);
            
            jtextlayout_settextcolor(jtl, &x->j_dbgridcolorpos);
            for (int i=0; i < long(x->f_range[1]/dbStep); i++)
            {
                dBpos = hoaGain_dBvaltopos(x, dbStep*(i+1), rect, isHoriz);
                jgraphics_move_to(g, long(dBpos)+0.5, rect->height*0.5);
                jgraphics_line_to(g, long(dBpos)+0.5, rect->height*0.5 + markerSize);
                jgraphics_stroke(g);
                // negative text dB value
                sprintf(dBCurrentTextValue,"%ld", long(dbStep*(i+1)));
                jtextlayout_set(jtl, dBCurrentTextValue, jf, dBpos-20, (rect->height*0.5)+(markerSize)+4, 40, 20, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_USEELLIPSIS);
                jtextlayout_draw(jtl, g);
            }
            
            // draw zero dB line
            jgraphics_set_line_width(g,1);
            jgraphics_set_source_jrgba(g, &black);
            jgraphics_move_to(g, zerodBpos, rect->height*0.25);
            jgraphics_line_to(g, zerodBpos, rect->height*0.75);
            jgraphics_stroke(g);
        }
    }
    
    jtextlayout_destroy(jtl);
    jfont_destroy(jf);
    
    jbox_end_layer((t_object*)x, view, gensym("dbGrid_layer"));
	jbox_paint_layer((t_object *)x, view, gensym("dbGrid_layer"), 0., 0.);
}

/*
void hoaGain_paint(t_hoaGain *x, t_object *view)
{
	t_rect rect;
	t_jgraphics *g;
	int pos;
	char ishoriz;
	double val = x->j_val;
	
	g = (t_jgraphics*) patcherview_get_jgraphics(view);
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	ishoriz = hoaGain_ishorizontal(x, &rect);
	val = CLAMP(val, 0, x->j_size);
	pos = hoaGain_valtopos(x, val, &rect, ishoriz);
	if (ishoriz) {
		jgraphics_move_to(g, pos,3);
		jgraphics_line_to(g, pos,rect.height - 3);
	} else {
		jgraphics_move_to(g, 3, pos);
		jgraphics_line_to(g, rect.width - 3, pos);
	}
	jgraphics_set_line_width(g,3);
	jgraphics_set_source_jrgba(g, &x->j_frgba);
	jgraphics_stroke(g);
}
*/

void hoaGain_bang(t_hoaGain *x)
{
	double value;
	value = CLAMP(x->j_val, 0, x->j_size);
	value += x->j_min;
    outlet_float(x->f_outlet_infos, value);
}

void hoaGain_int(t_hoaGain *x, long n)
{
    hoaGain_assign(x, double(n), true);
	hoaGain_bang(x);
}

void hoaGain_float(t_hoaGain *x, double f)
{
    hoaGain_assign(x, f, true);
	hoaGain_bang(x);
}

void hoaGain_setminmax(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv)
{
	double a, b;
	
	if (argc > 1) {
		double old_min = x->j_min;
		double old_size = x->j_size;
		a = b = 0;
		
		if (argv[0].a_type == A_LONG)
			a = (double)atom_getlong(&argv[0]);
		else if (argv[0].a_type == A_FLOAT)
			a = (double)atom_getfloat(&argv[0]);

		if (argv[1].a_type == A_LONG)
			b = (double)atom_getlong(&argv[1]);
		else if (argv[1].a_type == A_FLOAT)
			b = (double)atom_getfloat(&argv[1]);
		
		if (a == b) {
			x->j_min = 0.;
			x->j_size = 1.;
		} else  if (a < b) {
			x->j_min = a;
			x->j_size = b - a;
		} else {			
			x->j_min = b;
			x->j_size = a - b;
		}
        
        x->f_range[0] = x->j_min;
        x->f_range[1] = x->j_size + x->j_min;
		
		if (old_min != x->j_min || old_size != x->j_size)
        {
            //hoaGain_assign(x, x->j_val, true);
            jbox_invalidate_layer((t_object *)x, NULL, gensym("dbGrid_layer"));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("cursor_layer"));
            jbox_redraw((t_jbox *)x);
        }
	}
}

void hoaGain_set(t_hoaGain *x, t_symbol *s, long argc, t_atom *argv)
{
	if (argc && (argv->a_type == A_FLOAT || argv->a_type == A_LONG))
		hoaGain_assign(x, atom_getfloat(argv), true);
}

t_max_err hoaGain_setattr_interp(t_hoaGain *x, t_object *attr, long ac, t_atom *av)
{
	double d;
	if (ac && av) {
		d = atom_getfloat(av);
        x->f_amp->setRampTimeInMs(d);
        x->f_interp = x->f_amp->getRampTimeInMs();
        post("interp ms = %f", x->f_amp->getRampTimeInMs());
        post("ramp samples = %ld", x->f_amp->getRampTimeInSamps());
	}
	return MAX_ERR_NONE;
}

t_max_err hoaGain_setattr_channels(t_hoaGain *x, t_object *attr, long ac, t_atom *av)
{
	long d;
    long old_numberOfChannels = x->f_numberOfChannels;
    //long IO_diff;
    //t_object *b = NULL;
	if (ac && av) {
        if (atom_gettype(av) == A_LONG) {
            d = atom_getlong(av);
            if (old_numberOfChannels != d) {
                x->f_numberOfChannels = Tools::clip(d, long(MIN_IO), long(MAX_IO));
                /*
                IO_diff = x->f_numberOfChannels - old_numberOfChannels;
                object_obex_lookup(x, _sym_pound_B, (t_object **)&b);
                outlet_delete(outlet_nth((t_object*)x, i));
                object_method((t_jbox *)x, gensym("dynlet_begin"));
                dsp_resize((t_pxobject*)x, x->f_numberOfChannels);
                object_method((t_jbox *)x, gensym("dynlet_end"));
                */
            }
        }
	}
	return MAX_ERR_NONE;
}

t_max_err hoaGain_setattr_range(t_hoaGain *x, t_object *attr, long ac, t_atom *av)
{
    hoaGain_setminmax(x, NULL, ac, av);
	return MAX_ERR_NONE;
}

t_max_err hoaGain_setvalueof(t_hoaGain *x, long ac, t_atom *av)
{
	if (ac && av) {
		if (av->a_type == A_FLOAT)
			hoaGain_assign(x, atom_getfloat(av), false);
		else if (av->a_type == A_LONG)
			hoaGain_assign(x, atom_getlong(av), false);
		
		hoaGain_bang(x); 
	}
	return MAX_ERR_NONE;
}

t_max_err hoaGain_getvalueof(t_hoaGain *x, long *ac, t_atom **av)
{
	t_atom a;
	
	if (ac && av) {	
		if (*ac && *av) {
			//memory passed in use it
		} else {
			*av = (t_atom *)getbytes(sizeof(t_atom));
		}
		*ac = 1;
        atom_setfloat(&a,x->j_val + x->j_min);
		**av = a; 
	}
	return MAX_ERR_NONE;
}

void hoaGain_assign(t_hoaGain *x, double f, long notify)
{
	x->j_val = hoaGain_constrain_real_value(x,f) - x->j_min;
    x->j_valdB = x->j_val + x->j_min;
    hoaGain_set_gain(x);
	if (notify)
		object_notify(x, _sym_modified, NULL);
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("cursor_layer"));
	jbox_redraw((t_jbox *)x);
}

double hoaGain_constrain_real_value(t_hoaGain *x, double f)
{
    return Tools::clip(f, double(x->j_min), x->j_size + x->j_min);
}

double hoaGain_constrain(t_hoaGain *x, double f)
{
    return Tools::clip(f, double(0), x->j_size);
}

char hoaGain_ishorizontal(t_hoaGain *x, t_rect *r)
{
	if (x->j_orientation == 0) { // automatic mode
		if (r->height > r->width)
			return (0);
		else
			return (1);
	} else
		return (x->j_orientation == 2 ? 0 : 1);	
}

double hoaGain_postoval(t_hoaGain *x, t_pt pt, t_rect *r, char ishoriz)
{
	double pos, range;
	
	if (ishoriz) {
		pos = pt.x;
		range = r->width;
	} else {
		pos = r->height - pt.y;
		range = r->height;
	}
	if (pos <= hoaGain_DISPLAYINSET)
		pos = 0.;
	else {
		pos -= hoaGain_DISPLAYINSET;
		pos = (pos / (range - (hoaGain_DISPLAYINSET*2))) * x->j_size;
	}
	return hoaGain_constrain(x,pos);
}

double hoaGain_valtopos(t_hoaGain *x, double val, t_rect *r, char ishoriz)
{
	double pos, range;
	double size;
	
	if (ishoriz)
		range = r->width;
	else
		range = r->height;
	
    size = x->j_size;
	
	if (size < 0)
		size = 0;
	if (size)
		pos = (val / size) * (range - (hoaGain_DISPLAYINSET*2));
	else
		pos = 0;
	
	pos += hoaGain_DISPLAYINSET;
	if (ishoriz)
		return pos;
	else
		return r->height - pos;
}

double hoaGain_dBvaltopos(t_hoaGain *x, double dBval, t_rect *r, char ishoriz)
{
    double val = Tools:: scale(dBval, x->f_range[0], x->f_range[1], 0, x->j_size);
    return hoaGain_valtopos(x, val, r, ishoriz);
}

double hoaGain_dbtoval(t_hoaGain *x, double dBval)
{
    return Tools::scale(dBval, x->f_range[0], x->f_range[1], 0, x->j_size);
}
double hoaGain_valtodb(t_hoaGain *x, double val)
{
    return Tools::scale(val, 0, x->j_size, x->f_range[0], x->f_range[1]);
}

void hoaGain_mousedoubleclick(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers)
{
    hoaGain_float(x, 0);
}

void hoaGain_mousedown(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	double val;
	char ishoriz;
	
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	s_hoaGain_cum.x = s_hoaGain_cum.y = 0;
	ishoriz = hoaGain_ishorizontal(x, &rect);
	val = hoaGain_postoval(x, pt, &rect, ishoriz);
	if (!x->j_relative)
		hoaGain_float(x, val + x->j_min);	// set value immediately
	s_hoaGain_startval = x->j_val;
}

void hoaGain_mousedragdelta(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	double inc;
	double val, cval;
	double factor;
	
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	
	if (modifiers & eShiftKey || x->j_valdB >= 0) {
		pt.y *= 0.2;
		pt.x *= 0.2;
	}
    
	// need to cancel cum change if it is beyond zero or the max value
	s_hoaGain_cum.x += pt.x;
	s_hoaGain_cum.y -= pt.y;
	if (hoaGain_ishorizontal(x, &rect)) {
		factor = x->j_size / (rect.width - (hoaGain_DISPLAYINSET*2));
		inc = s_hoaGain_cum.x * factor;
		val = s_hoaGain_startval + inc;
		cval = hoaGain_constrain(x,val);
		hoaGain_float(x,cval + x->j_min);
        if (Tools::isInside(x->j_valdB, -0.02, 0.02) ) {
            hoaGain_float(x, 0);
        }
		// in case we were constrained, adjust the cum
		if (cval != val)
			s_hoaGain_cum.x = (cval-s_hoaGain_startval) / factor;
	} else {
		factor = x->j_size / (rect.height - (hoaGain_DISPLAYINSET*2)); 
		inc = s_hoaGain_cum.y * factor;
		val = s_hoaGain_startval + inc;
		cval = hoaGain_constrain(x,val);
		hoaGain_float(x, cval + x->j_min);
        if (Tools::isInside(x->j_valdB, -0.02, 0.02) ) {
            hoaGain_float(x, 0);
        }
		if (cval != val)
			s_hoaGain_cum.y = (cval - s_hoaGain_startval) / factor; 
	}
}

void hoaGain_mouseup(t_hoaGain *x, t_object *patcherview, t_pt pt, long modifiers)
{
	double pos, vp; 
	t_rect rect; 
	double mx, my;
	char ishoriz;

	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	ishoriz = hoaGain_ishorizontal(x, &rect);
	pos = hoaGain_valtopos(x, x->j_val, &rect, ishoriz);
	vp = pos + 0.5;
	if (ishoriz) {
		mx = vp; 
		my = pt.y;	// have y position be same as where mouse down clicked
	} else {
		mx = pt.x;	// have x position be same as where mouse down clicked
		my = vp; 
	}
	
	if (fabs(pt.x-mx) > 1. || fabs(pt.y-my) > 1.) // this make sure that if you click at the "same" location we don't move the mouse.
		jmouse_setposition_box(patcherview, (t_object*) x, mx, my); 
}

void hoaGain_getdrawparams(t_hoaGain *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_borderthickness = hoaGain_BORDERTHICKNESS;
	params->d_bordercolor = x->j_frgba2;
	params->d_cornersize = hoaGain_CORNERSIZE; 
	params->d_boxfillcolor = x->j_brgba;
}

t_max_err hoaGain_notify(t_hoaGain *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	long argc = 0;
	t_atom *argv = NULL;
	t_symbol *name;
	
	if (msg == _sym_attr_modified) {
		name = (t_symbol *)object_method((t_object *)data,_sym_getname);
		if (name == _sym_color) {
			object_attr_getvalueof(x, _sym_color, &argc, &argv);
			if (argc && argv) {
				object_attr_setvalueof(x, _sym_bgcolor, argc, argv);
				sysmem_freeptr(argv);
			}
		}
        else if (name == gensym("knobcolor") || name == gensym("intknobcolor"))
        {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("cursor_layer"));
        }
        else if(name == gensym("dbgridcolorneg") || name == gensym("dbgridcolorpos"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("dbGrid_layer"));
		}
        jbox_redraw((t_jbox *)x);
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}
