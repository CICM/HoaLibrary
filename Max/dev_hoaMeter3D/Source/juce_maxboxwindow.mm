/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2014 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"
#include "jgraphics.h"

#include "../JuceLibraryCode/JuceHeader.h"
#include "MaxBoxComponent.h"

extern juce::Component* createMaxBoxComponent();
class EditorComponentHolder;

typedef struct _meter3d
{
	t_jbox j_box;						// header for UI objects
    int         isInitialised;
    
    t_object    *mPatcher;
    t_object    *mPatcherview;
    t_rect      cachePvRect;
    t_rect      rect;
    t_jrgba     bgcolor;
	t_jrgba		bdcolor;
	t_jrgba		spherecolor;
	t_atom_long		drawVectors;
	double		cam[3];
    
	juce::Component* juceEditorComp;
    EditorComponentHolder* juceWindowComp;
	
	void*       leftOutlet;
} t_meter3d;

/* ---------------------------------- */

EditorComponent* getOGLComponent(t_meter3d *x);

void *jucebox_new(t_symbol *s, long argc, t_atom *argv);
void jucebox_free(t_meter3d *x);
void jucebox_assist(t_meter3d *x, void *b, long m, long a, char *s);
void jucebox_paint(t_meter3d *x, t_object *patcherview);
void jucebox_getdrawparams(t_meter3d *x, t_object *patcherview, t_jboxdrawparams *params);
void jucebox_bang(t_meter3d *x);
void jucebox_int(t_meter3d *x, long n);
void jucebox_assist(t_meter3d *x, void *b, long m, long a, char *s);

void jucebox_addjucecomponents(t_meter3d* x);
void jucebox_deleteui(t_meter3d *x);
void jucebox_mousedown(t_meter3d *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err jucebox_notify          (t_meter3d *x, t_symbol *s, t_symbol *m, void *sender, void *data);
void jucebox_anything        (t_meter3d *x, t_symbol *s, long argc, t_atom *argv);

void jucebox_patcherview_vis(t_meter3d *x, t_object *patcherview);
void jucebox_patcherview_invis(t_meter3d *x, t_object *patcherview);

t_max_err attrset_cam(t_meter3d *x, t_object *attr, long argc, t_atom *argv);

static t_class *s_jucebox_class;

/* ---------------------------------- EditorComponentHolder class */

class EditorComponentHolder  :	public juce::Component,
public ComponentListener
{
public:
    EditorComponentHolder (juce::Component* const editorComp_, t_meter3d* x)
    :	ref(x)
	{
		addAndMakeVisible (editorComp_);
        setOpaque (true);
        setVisible (true);
        setWantsKeyboardFocus (false);
        
		editorComp = editorComp_;
		editorComp->addComponentListener(this);
        
        editorComp->setBounds(0,0, 200, 200);
		setBounds(0,0, 0, 0);
		
        setInterceptsMouseClicks(false, false);
		setAlwaysOnTop(false);
	}
    
	~EditorComponentHolder()
	{
		editorComp->removeComponentListener(this);
	}
	
	void calcAndSetBounds()
	{
		if(ref->isInitialised)
        {
            jbox_get_rect_for_view((t_object *)ref, ref->mPatcherview, &ref->rect);
			Rectangle<int> boxRect(ref->rect.x, ref->rect.y, ref->rect.width, ref->rect.height);
			editorComp->setBounds( 0, 0, boxRect.getWidth(), boxRect.getHeight());
		}
	}
    
    void setBgColour()
	{
        editorComp->setColour(EditorComponent::ColourIds::backgroundColourId, jrgbaToColour(&ref->bgcolor));
	}

	void setPaintColour(EditorComponent::ColourIds colorID, t_jrgba* color)
	{
        editorComp->setColour(colorID, jrgbaToColour(color));
	}
    
	// convert t_jrgba to juce::Colour, ignore alpha ?.
    Colour jrgbaToColour(t_jrgba* jrgbaColor)
	{
		return Colour(uint8(255 * jrgbaColor->red),
					  uint8(255 * jrgbaColor->green),
					  uint8(255 * jrgbaColor->blue),
					  float(jrgbaColor->alpha));
	}
    
private:
	t_meter3d* ref;
	Component* editorComp;
};

int C74_EXPORT main(void)
{
	t_class *c;
    
	c = class_new("hoa.meter3D~", (method)jucebox_new, (method)jucebox_free, sizeof(t_meter3d), 0L, A_GIMME, 0);
    
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR);
    
	class_addmethod(c, (method)jucebox_paint,		"paint",		A_CANT, 0);
	class_addmethod(c, (method)jucebox_mousedown,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)jucebox_assist,		"assist",		A_CANT, 0);
    class_addmethod(c, (method)jucebox_notify,      "notify",       A_CANT, 0);
	class_addmethod(c, (method)jucebox_patcherview_vis, "patcherview_vis",		A_CANT, 0);
    class_addmethod(c, (method)jucebox_patcherview_invis, "patcherview_invis",	A_CANT, 0);
	class_addmethod(c, (method)jucebox_bang,		"bang", 0);
	class_addmethod(c, (method)jucebox_getdrawparams,		"getdrawparams", 0);
	
	
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
	CLASS_ATTR_ACCESSORS (c, "cam", NULL, attrset_cam);
    
    initialiseJuce_GUI();
    
	class_register(CLASS_BOX, c);
	s_jucebox_class = c;
    
	return 0;
}

EditorComponent* getOGLComponent(t_meter3d *x)
{
	return dynamic_cast <EditorComponent*> (x->juceEditorComp);
}

t_max_err attrset_cam(t_meter3d *x, t_object *attr, long argc, t_atom *argv)
{
	if(argc && argv)
    {
		for (int i=0; i<3; i++)
		{
			x->cam[i] = atom_getfloat(argv+i);
		}
		
		getOGLComponent(x)->setCamera(x->cam);
		jbox_redraw((t_jbox*)x);
    }
    return MAX_ERR_NONE;
}

void jucebox_getdrawparams(t_meter3d *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_bordercolor = x->bdcolor;
	params->d_borderthickness = 1;
	params->d_cornersize = 4;
}

void jucebox_patcherview_vis(t_meter3d *x, t_object *patcherview)
{
    x->mPatcherview = patcherview;
	x->mPatcher = patcherview_get_patcher(x->mPatcherview);
    object_attach_byptr_register(x, x->mPatcherview, CLASS_NOBOX);
	
    if (!x->isInitialised)
    {
		x->juceWindowComp->addToDesktop(0);
        x->isInitialised = 1;
    }
}

void jucebox_patcherview_invis(t_meter3d *x, t_object *patcherview)
{
    object_detach_byptr(x, x->mPatcherview);
    x->mPatcherview = NULL;
}

t_max_err jucebox_notify(t_meter3d *x, t_symbol *s, t_symbol *m, void *sender, void *data)
{
    if (sender && (m == gensym("attr_modified") )) {
        
        t_symbol *name = (t_symbol *)object_method(data, gensym("getname"));
        
        if (sender == x) {
            if (name == gensym("bgcolor"))
            {
                x->juceWindowComp->setBgColour();
                jbox_redraw((t_jbox*)x);
            }
			if (name == gensym("spherecolor"))
            {
                x->juceWindowComp->setPaintColour(EditorComponent::ColourIds::sphereColourId, &x->spherecolor);
                jbox_redraw((t_jbox*)x);
            }
			else if( name == gensym("vectors") )
			{
				getOGLComponent(x)->shouldDrawVectors(x->drawVectors);
				jbox_redraw((t_jbox *)x);
			}
		}
    }
	return jbox_notify((t_jbox *)x, s, m, sender, data);
}

void jucebox_assist(t_meter3d *x, void *b, long m, long a, char *s)
{
	if (m == 1)		//inlet
		sprintf(s, "(signal) Audio Inputs");
}

void jucebox_paint(t_meter3d *x, t_object *patcherview)
{
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(patcherview);
	jbox_get_rect_for_view((t_object *)x, patcherview, &x->rect);
    
    int locked = ((patcherview_get_locked(x->mPatcherview)) != 0);
	
    if( locked )
    {
        if(!x->juceWindowComp) jucebox_addjucecomponents(x);
        x->juceWindowComp->calcAndSetBounds();
	}

	Image openGLSnap = getOGLComponent(x)->makeScreenshot();
	Image::BitmapData* snapBitmap = new Image::BitmapData(openGLSnap, Image::BitmapData::ReadWriteMode::readOnly);
	
	unsigned char* data = snapBitmap->data;
	int width, height, imgStride;
	width = openGLSnap.getWidth();
	height = openGLSnap.getHeight();
	imgStride = snapBitmap->lineStride;
	t_rect srcRect = {0,0, (double)openGLSnap.getWidth(), (double)openGLSnap.getHeight()};
	t_rect destRect = {0,0, x->rect.width, x->rect.height};
	
	t_jsurface* surface = jgraphics_image_surface_create_for_data (data, JGRAPHICS_FORMAT_ARGB32, width, height, imgStride, NULL, NULL);
	jgraphics_image_surface_draw(g, surface, srcRect, destRect);
	jgraphics_surface_destroy (surface);
}

void jucebox_mousedown(t_meter3d *x, t_object *patcherview, t_pt pt, long modifiers)
{
}

void jucebox_bang(t_meter3d *x)
{
	int i,j;
	int n = 0, nstart;
	int iterations = 3;
	//FACET3 *f = NULL;
	double theta[3] = {0.0,35.0,80.0}, phi[3] = {10.0,15.0,80.0}; // corner in polar coordinates
	//XYZ p1, p2, p3;
	//double theta[3] = {0.0,0.35,0.8}, phi[3] = {0.1,0.15,0.8}; // corner in polar coordinates
	
	//Array<t_facet3> f;
	Array<Triangle3D<double>> f;
	Vector3D<double> p1, p2, p3;
	
	// Start with the vertices of the triangle
	f.resize(1);
	p1.x = cos(phi[0]*DTOR) * cos(theta[0]*DTOR);
	p1.y = cos(phi[0]*DTOR) * sin(theta[0]*DTOR);
	p1.z = sin(phi[0]*DTOR);
	p2.x = cos(phi[1]*DTOR) * cos(theta[1]*DTOR);
	p2.y = cos(phi[1]*DTOR) * sin(theta[1]*DTOR);
	p2.z = sin(phi[1]*DTOR);
	p3.x = cos(phi[2]*DTOR) * cos(theta[2]*DTOR);
	p3.y = cos(phi[2]*DTOR) * sin(theta[2]*DTOR);
	p3.z = sin(phi[2]*DTOR);
	post("----- %f %f %f\n",p1.x,p1.y,p1.z);
	f[0].p1 = p1;
	post("vertex %f %f %f\n",f[0].p1.x,f[0].p1.y,f[0].p1.z);
	f[0].p2 = p2;
	f[0].p3 = p3;
	
	n = 1;
	
	post("-------------");
	for (i=0;i<n;i++) {
		post("facet normal 0 0 1\n");
		post("outer loop\n");
		post("vertex %f %f %f\n",f[i].p1.x,f[i].p1.y,f[i].p1.z);
		post("vertex %f %f %f\n",f[i].p2.x,f[i].p2.y,f[i].p2.z);
		post("vertex %f %f %f\n",f[i].p3.x,f[i].p3.y,f[i].p3.z);
		post("endloop\n");
		post("endfacet\n");
	}
	post("-------");
	
	for (i=1;i<iterations;i++) {
		nstart = n;
		
		for (j=0;j<nstart;j++) {
			//f = realloc(f,(n+3)*sizeof(FACET3));
			f.resize(n+3);
			
			// Create initially copies for the new facets
			f[n  ] = f[j];
			f[n+1] = f[j];
			f[n+2] = f[j];
			
			p1 = (f[j].p1 + f[j].p2) * 0.5;
			p1 = p1.normalised();
			p2 = (f[j].p2 + f[j].p3) * 0.5;
			p2 = p2.normalised();
			p3 = (f[j].p3 + f[j].p1) * 0.5;
			p3 = p3.normalised();
			
			// Replace the current facet
			f[j].p2 = p1;
			f[j].p3 = p3;
			
			// Create the changed vertices in the new facets
			f[n  ].p1 = p1;
			f[n  ].p3 = p2;
			f[n+1].p1 = p3;
			f[n+1].p2 = p2;
			f[n+2].p1 = p1;
			f[n+2].p2 = p2;
			f[n+2].p3 = p3;
			n += 3;
		}
	}
	
	post("%d facets generated\n",n);
	
	// Save as STL, for simplicity only
	post("solid\n");
	for (i=0;i<n;i++) {
		post("facet normal 0 0 1\n");
		post("outer loop\n");
		post("vertex %f %f %f\n",f[i].p1.x,f[i].p1.y,f[i].p1.z);
		post("vertex %f %f %f\n",f[i].p2.x,f[i].p2.y,f[i].p2.z);
		post("vertex %f %f %f\n",f[i].p3.x,f[i].p3.y,f[i].p3.z);
		post("endloop\n");
		post("endfacet\n");
	}
	post("endsolid");
}

void jucebox_int(t_meter3d *x, long n)
{
}

void jucebox_addjucecomponents(t_meter3d* x)
{	
	x->juceEditorComp = createMaxBoxComponent();
	x->juceEditorComp->setBounds(0, 0, x->rect.width, x->rect.height);
	
	x->juceEditorComp->setOpaque (true);
	x->juceEditorComp->setVisible (true);
	
	x->juceWindowComp = new EditorComponentHolder(x->juceEditorComp, x);
	x->juceWindowComp->calcAndSetBounds();
}

void jucebox_free(t_meter3d *x)
{
	x->juceWindowComp->removeFromDesktop();
	delete x->juceWindowComp;
	jbox_free((t_jbox *)x);
}

void *jucebox_new(t_symbol *s, long argc, t_atom *argv)
{
	t_meter3d *x = NULL;
 	t_dictionary *d = NULL;
	long boxflags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
    
	x = (t_meter3d *)object_alloc(s_jucebox_class);
	boxflags = 0
    | JBOX_DRAWFIRSTIN
    | JBOX_NODRAWBOX
    | JBOX_DRAWINLAST
    | JBOX_TRANSPARENT
    | JBOX_GROWY
    | JBOX_DRAWBACKGROUND
    ;
    
	jbox_new((t_jbox *)x, boxflags, argc, argv);
	x->j_box.b_firstin = (t_object *)x;
    
    x->isInitialised = 0;
    
    jbox_get_patching_rect((t_object *)x, &x->rect);
    
    x->juceWindowComp = 0L;
    x->juceEditorComp = 0L;
    
    jucebox_addjucecomponents(x);
    
    x->leftOutlet = outlet_new((t_object*)x, NULL);
    
	attr_dictionary_process(x,d);
	jbox_ready((t_jbox *)x);
	return x;
}
