/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "z_dsp.h"

#include "../../MaxJuceBox/jucebox_wrapper.h"

typedef struct _meter3d
{
	t_jucebox	j_box; // custom t_pxjbox
    t_rect      rect;
    t_jrgba     bgcolor;
	t_jrgba		bdcolor;
	t_jrgba		spherecolor;
	t_atom_long	drawVectors;
	double		cam[3];
	void*       leftOutlet;
} t_meter3d;

/* ---------------------------------- */

void *hoaMeter_new(t_symbol *s, long argc, t_atom *argv);
void hoaMeter_free(t_meter3d *x);
void hoaMeter_assist(t_meter3d *x, void *b, long m, long a, char *s);
void hoaMeter_paint(t_meter3d *x);
//void hoaMeter_paint(t_meter3d *x, t_object *patcherview);
void hoaMeter_getdrawparams(t_meter3d *x, t_object *patcherview, t_jboxdrawparams *params);
t_max_err hoaMeter_notify(t_meter3d *x, t_symbol *s, t_symbol *m, void *sender, void *data);

void hoaMeter_bang(t_meter3d *x);
void hoaMeter_int(t_meter3d *x, long n);
void hoaMeter_anything(t_meter3d *x, t_symbol *s, long argc, t_atom *argv);

/* DSP ------------------------------------- */
void hoaMeter_dsp64(t_meter3d *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoaMeter_perform64(t_meter3d *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoaMeter_mousedown(t_meter3d *x, t_object *patcherview, t_pt pt, long modifiers);

/* Attributs setters ------------------------------------- */
t_max_err hoaMeter_setAttr_cam(t_meter3d *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaMeter_number_of_loudspeakers_set(t_meter3d *x, t_object *attr, long argc, t_atom *argv);
t_max_err hoaMeter_angles_of_loudspeakers_set(t_meter3d *x, void *attr, long ac, t_atom *av);

static t_class *s_hoaMeter_class;

int C74_EXPORT main(void)
{
	t_class *c;
    
	c = class_new("hoa.meter3D~", (method)hoaMeter_new, (method)hoaMeter_free, sizeof(t_meter3d), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	class_dspinitjbox(c);
	jbox_initclass(c, JBOX_COLOR);
	
	jucebox_class_new(c, (method)hoaMeter_paint, (method)hoaMeter_notify);

	class_addmethod(c, (method)hoaMeter_dsp64,				"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)hoaMeter_mousedown,			"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)hoaMeter_assist,				"assist",		A_CANT, 0);
	class_addmethod(c, (method)hoaMeter_bang,				"bang", A_CANT, 0);
	class_addmethod(c, (method)hoaMeter_getdrawparams,		"getdrawparams", A_CANT, 0);
	
	
    CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 200 200");
    CLASS_ATTR_INVISIBLE		(c, "color", 0);
    
    CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_meter3d, bgcolor);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.9 0.9 0.9 1.");
	
	CLASS_ATTR_RGBA				(c, "bdcolor", 0, t_meter3d, bdcolor);
	CLASS_ATTR_CATEGORY			(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bdcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bdcolor", 0, "0.1 0.1 0.1 1.");
	
	CLASS_ATTR_RGBA				(c, "spherecolor", 0, t_meter3d, spherecolor);
	CLASS_ATTR_CATEGORY			(c, "spherecolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "spherecolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "spherecolor", 0, "Sphere Color");
	CLASS_ATTR_ORDER			(c, "spherecolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "spherecolor", 0, "0.9 0.9 0.9 1.");
	
	CLASS_ATTR_LONG				(c, "vectors", 0, t_meter3d, drawVectors);
	CLASS_ATTR_CATEGORY			(c, "vectors", 0, "3D");
	CLASS_ATTR_STYLE_LABEL		(c, "vectors", 0, "onoff", "Draw 3D Vectors");
	CLASS_ATTR_DEFAULT_SAVE		(c, "vectors", 0, "1");
	
	CLASS_ATTR_DOUBLE_ARRAY     (c, "cam", 0, t_meter3d, cam, 3);
	CLASS_ATTR_CATEGORY			(c, "cam", 0, "3D");
	CLASS_ATTR_LABEL			(c, "cam", 0, "Camera XYZ");
	CLASS_ATTR_DEFAULT_SAVE		(c, "cam", 0, "0. 0. 0.");
	CLASS_ATTR_ACCESSORS (c, "cam", NULL, hoaMeter_setAttr_cam);
    
    initialiseJuce_GUI();
    
	class_register(CLASS_BOX, c);
	s_hoaMeter_class = c;
    
	return 0;
}

void hoaMeter_dsp64(t_meter3d *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, hoaMeter_perform64, 0, NULL);
}

void hoaMeter_perform64(t_meter3d *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	;
}

t_max_err hoaMeter_setAttr_cam(t_meter3d *x, t_object *attr, long argc, t_atom *argv)
{
	if(argc && argv)
    {
		for (int i=0; i<3; i++)
		{
			x->cam[i] = atom_getfloat(argv+i);
		}
		jbox_redraw((t_jbox*)x);
    }
    return MAX_ERR_NONE;
}

void hoaMeter_getdrawparams(t_meter3d *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_bordercolor = x->bdcolor;
	params->d_borderthickness = 1;
	params->d_cornersize = 4;
}

t_max_err hoaMeter_notify(t_meter3d *x, t_symbol *s, t_symbol *m, void *sender, void *data)
{	
    if (sender && (m == gensym("attr_modified") )) {
        
        t_symbol *name = (t_symbol *)object_method(data, gensym("getname"));

        if (sender == x) {
            if (name == gensym("bgcolor"))
            {
                jbox_redraw((t_jbox*)x);
            }
			if (name == gensym("spherecolor"))
            {
                jbox_redraw((t_jbox*)x);
            }
			else if( name == gensym("vectors") )
			{
				jbox_redraw((t_jbox *)x);
			}
		}
    }
	return jbox_notify((t_jbox *)x, s, m, sender, data);
}

void hoaMeter_assist(t_meter3d *x, void *b, long m, long a, char *s)
{
	if (m == 1)		//inlet
		sprintf(s, "(signal) Audio Inputs");
}

void hoaMeter_paint(t_meter3d *x)
{
	jassert (OpenGLHelpers::isContextActive());
	
	const float desktopScale = 1;
	
	//OpenGLHelpers::clear ( findColour(EditorComponent::backgroundColourId) );
	OpenGLHelpers::clear ( jrgbaToColour(&x->bgcolor) );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	//OpenGLHelpers::setPerspective(60,(double) roundToInt (desktopScale * getWidth()) / roundToInt (desktopScale * getHeight()), 1,1000);
	OpenGLHelpers::setPerspective(60,(double) roundToInt (desktopScale * 200) / roundToInt (desktopScale * 200), 1,1000);
	
	// active z-buffer
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Enable lightings
	glAlphaFunc(GL_LESS, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	
	CicmLookAt(3,3,2,0,0,0,0,0,1);
	
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 0);
	glEnd();
}

void hoaMeter_mousedown(t_meter3d *x, t_object *patcherview, t_pt pt, long modifiers)
{
}

void hoaMeter_bang(t_meter3d *x)
{
}

void hoaMeter_int(t_meter3d *x, long n)
{
}

void hoaMeter_free(t_meter3d *x)
{
	jucebox_free((t_jucebox*)x);
	dsp_freejbox((t_pxjbox *)x);
}

void *hoaMeter_new(t_symbol *s, long argc, t_atom *argv)
{
	t_meter3d *x = NULL;
 	t_dictionary *d = NULL;
	long boxflags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
    
	x = (t_meter3d *)object_alloc(s_hoaMeter_class);
	boxflags = 0
    | JBOX_DRAWFIRSTIN
    | JBOX_NODRAWBOX
    | JBOX_DRAWINLAST
    | JBOX_TRANSPARENT
    | JBOX_GROWY
    | JBOX_DRAWBACKGROUND
    ;
    
	jbox_new((t_jbox *)x, boxflags, argc, argv);
	x->j_box.z_box.b_firstin = (t_object *)x;
    
    jbox_get_patching_rect((t_object *)x, &x->rect);
    
	jucebox_new((t_jucebox*) x);
    //hoaMeter_addjucecomponents(x);
    
    x->leftOutlet = outlet_new((t_object*)x, NULL);
    
	attr_dictionary_process(x,d);
	jbox_ready((t_jbox *)x);
	return x;
}
