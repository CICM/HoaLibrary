/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "../../Sources/HoaOpenGL/OpenGLTools.h"
#include "../../MaxJuceBox/jucebox_wrapper.h"
#include "../../hoa.max.h"

typedef struct _hoa_scope
{
	t_jucebox	j_box;

    double*         f_signals;
    Hoa3D::Scope*   f_scope;
    int             f_index;
    void*           f_clock;
	int             f_startclock;
    
    t_jrgba         f_bgcolor;
	t_jrgba         f_bdcolor;
	t_jrgba         f_spherecolor;

	double          cam[3];

} t_hoa_scope;

t_class *hoa_scope_class;

void *hoa_scope_new(t_symbol *s, long argc, t_atom *argv);
void hoa_scope_free(t_hoa_scope *x);
void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s);
void hoa_scope_paint(t_hoa_scope *x, double w, double h);
void hoa_scope_tick(t_hoa_scope *x);

void hoa_scope_getdrawparams(t_hoa_scope *x, t_object *patcherview, t_jboxdrawparams *params);
t_max_err hoa_scope_notify(t_hoa_scope *x, t_symbol *s, t_symbol *m, void *sender, void *data);

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void hoa_scope_mousedown(t_hoa_scope *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err hoa_scope_attr_set_cam(t_hoa_scope *x, t_object *attr, long argc, t_atom *argv);

int C74_EXPORT main(void)
{
	t_class *c;
    
	c = class_new("hoa.scope3D~", (method)hoa_scope_new, (method)hoa_scope_free, sizeof(t_hoa_scope), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	
    class_dspinitjbox(c);
    jucebox_initclass(c, (method)hoa_scope_paint,  JBOX_COLOR | JBOX_FIXWIDTH);
    
	class_addmethod(c, (method)hoa_scope_dsp64,				"dsp64",            A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_mousedown,			"mousedown",        A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_assist,			"assist",           A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_getdrawparams,		"getdrawparams",    A_CANT, 0);
	class_addmethod(c, (method)hoa_scope_notify,			"notify",           A_CANT, 0);
	
    CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 200 200");
    CLASS_ATTR_INVISIBLE		(c, "color", 0);
    
    CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_hoa_scope, f_bgcolor);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.9 0.9 0.9 1.");
	
	CLASS_ATTR_RGBA				(c, "bdcolor", 0, t_hoa_scope, f_bdcolor);
	CLASS_ATTR_CATEGORY			(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bdcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bdcolor", 0, "0.1 0.1 0.1 1.");
	
	CLASS_ATTR_RGBA				(c, "spherecolor", 0, t_hoa_scope, f_spherecolor);
	CLASS_ATTR_CATEGORY			(c, "spherecolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "spherecolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "spherecolor", 0, "Sphere Color");
	CLASS_ATTR_ORDER			(c, "spherecolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "spherecolor", 0, "0.9 0.9 0.9 1.");
	
	CLASS_ATTR_DOUBLE_ARRAY     (c, "cam", 0, t_hoa_scope, cam, 3);
	CLASS_ATTR_CATEGORY			(c, "cam", 0, "3D");
	CLASS_ATTR_LABEL			(c, "cam", 0, "Camera XYZ");
	CLASS_ATTR_DEFAULT_SAVE		(c, "cam", 0, "0. 0. 0.");
	CLASS_ATTR_ACCESSORS        (c, "cam", NULL, hoa_scope_attr_set_cam);
    
	class_register(CLASS_BOX, c);
	hoa_scope_class = c;
    
	return 0;
}

void *hoa_scope_new(t_symbol *s, long argc, t_atom *argv)
{
	t_hoa_scope *x    = NULL;
 	t_dictionary *d = NULL;
	long flags;
	int	order = 1;
    
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
    
	x = (t_hoa_scope *)object_alloc(hoa_scope_class);
	flags = 0
    | JBOX_DRAWFIRSTIN
    | JBOX_NODRAWBOX
    | JBOX_DRAWINLAST
    | JBOX_TRANSPARENT
    | JBOX_GROWY
    | JBOX_DRAWBACKGROUND
    ;
    
	jbox_new((t_jbox *)x, flags, argc, argv);
    x->j_box.j_box.z_box.b_firstin = (t_object *)x;
    
    x->f_scope = new Hoa3D::Scope(order, 100, 199);
    x->f_signals    =  new double[x->f_scope->getNumberOfHarmonics() * SYS_MAXBLKSIZE];
    x->f_clock      = clock_new((void *)x, (method)hoa_scope_tick);
    x->f_startclock = 0;
    x->f_index = 0;
    
    dsp_setupjbox((t_pxjbox *)x, x->f_scope->getNumberOfHarmonics());
	jucebox_new((t_jucebox *) x);
    
	attr_dictionary_process(x,d);
	jbox_ready((t_jbox *)x);
	return x;
}

void hoa_scope_dsp64(t_hoa_scope *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_index = 0;
    object_method(dsp64, gensym("dsp_add64"), x, hoa_scope_perform64, 0, NULL);
    x->f_startclock = 1;
}

void hoa_scope_perform64(t_hoa_scope *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	for(int i = 0; i < numins; i++)
    {
        cblas_dcopy(sampleframes, ins[i], 1, x->f_signals+i, numins);
    }
    x->f_index = 0;
    while(--sampleframes)
    {
        x->f_index++;
    }
    if(x->f_startclock)
	{
		x->f_startclock = 0;
		clock_delay(x->f_clock,0);
	}
}

void hoa_scope_tick(t_hoa_scope *x)
{
    x->f_scope->process(x->f_signals + x->f_index * x->f_scope->getNumberOfHarmonics());
    jbox_redraw((t_jbox *)x);
	if (sys_getdspstate())
		clock_fdelay(x->f_clock, 100.);
}

t_max_err hoa_scope_attr_set_cam(t_hoa_scope *x, t_object *attr, long argc, t_atom *argv)
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

void hoa_scope_getdrawparams(t_hoa_scope *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_bordercolor = x->f_bdcolor;
    params->d_boxfillcolor = x->f_bgcolor;
	params->d_borderthickness = 1;
	params->d_cornersize = 4;
}

t_max_err hoa_scope_notify(t_hoa_scope *x, t_symbol *s, t_symbol *m, void *sender, void *data)
{	
    if(m == gensym("attr_modified"))
    {
        t_symbol *name = (t_symbol *)object_method(data, gensym("getname"));
        if(sender == x)
        {
            if(name == gensym("bgcolor") || name == gensym("f_spherecolor"))
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

void hoa_scope_assist(t_hoa_scope *x, void *b, long m, long a, char *s)
{
    sprintf(s,"(Signal) %s", x->f_scope->getHarmonicsName(a).c_str());
}

void hoa_scope_paint(t_hoa_scope *x, double w, double h)
{
    int number_of_rows = x->f_scope->getNumberOfRows();
	int number_of_columns = x->f_scope->getNumberOfColumns();
	//OpenGLHelpers::clear(jrgbaToColour(&x->f_bgcolor) );

	float value;
    float one, two;
	t_jrgb red  = {0.8,0.,0.};
	t_jrgb blue = {0.,0.,0.8};
	
	glEnable(GL_DEPTH_TEST);	// Active le test de profondeur
	glShadeModel(GL_SMOOTH);
    
	
	glPointSize(1.0f);
	glBegin(GL_LINE_LOOP);
	
	for(int i = 0; i < number_of_rows; i++)
    {
        one  =   0;
        two = (double)i / (double)(number_of_rows - 1) * CICM_PI;
        value = x->f_scope->getValue(i, 0);
        if(value < 0)
        {
            glColor3d(blue.red, blue.green, blue.blue);
            value= -value;
        }
        else
		glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
		
        for(int j = 1; j < number_of_columns; j++)
        {
            one  =   (double)j / (double)number_of_columns * CICM_2PI;
            value = x->f_scope->getValue(i, j);
            if(value < 0)
            {
                glColor3d(blue.red, blue.green, blue.blue);
                value= -value;
            }
            else
                glColor3d(red.red, red.green, red.blue);
			
            glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
        }
        
        one  =   0;
        value = x->f_scope->getValue(i, 0);
        if(value < 0)
        {
            glColor3d(blue.red, blue.green, blue.blue);
            value = -value;
        }
        else
           glColor3d(red.red, red.green, red.blue);
        
        glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
    }
	
	for(int j = 0; j < number_of_columns; j++)
    {
        one  =   (double)j / (double)number_of_columns * CICM_2PI;
        two  = 0.;
        value = x->f_scope->getValue(0, j);
        if(value < 0)
        {
            glColor3d(blue.red, blue.green, blue.blue);
            value= -value;
        }
        else
           glColor3d(red.red, red.green, red.blue);
		
		glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
		
        for(int i = 1; i < number_of_rows; i++)
        {
            two = (double)i / (double)(number_of_rows - 1) * CICM_PI;
            value = x->f_scope->getValue(i, j);
            if(value < 0)
            {
                glColor3d(blue.red, blue.green, blue.blue);
                value= -value;
            }
            else
               glColor3d(red.red, red.green, red.blue);
			
            glVertex3d(value * sin(two) * cos(one), value * cos(two), value * sin(two) * sin(one));
        }
    }
	glEnd();
	
	/*
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	// Create light components
	GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { -1.5f, 1.5f, 1.5f, 1.0f };
	
	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
    
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	OpenGLHelpers::setPerspective(60, (double) roundToInt(w) / roundToInt(h), 1, 1000);
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
	OpenGLHelpers::setColour(jrgbaToColour(&x->f_spherecolor));
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 0);
	glEnd();
     */
}

void hoa_scope_mousedown(t_hoa_scope *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ;
}

void hoa_scope_free(t_hoa_scope *x)
{
    clock_free((t_object *)x->f_clock);
    dsp_freejbox((t_pxjbox *)x);
    jucebox_free((t_jucebox*)x);
	delete x->f_scope;
    delete [] x->f_signals;
}

