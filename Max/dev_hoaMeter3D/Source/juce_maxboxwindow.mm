/*
 jucebox -- juce component in front of a max UI object
 */

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"
#include "jgraphics.h"

#include "../JuceLibraryCode/JuceHeader.h"
#include "MaxBoxComponent.h"

#import <Cocoa/Cocoa.h>
#include <Carbon/Carbon.h>

#define MAXWIDTH 		1024
#define MINWIDTH 		20			// minimum width and height
#define MINHEIGHT		20			//		...
#define DEFWIDTH 		200			// default width and height
#define DEFHEIGHT		200			//		...


#define FLOP_CLAMP(x, a, b) ((x)<(a)?(a):(x)>(b)?(b):(x))

extern juce::Component* createMaxBoxComponent();
class EditorComponentHolder;

typedef struct _jucebox
{
	t_jbox j_box;						// header for UI objects    
    int         isInitialised;
    
    t_object    *mPatcher;
    t_object    *mPatcherview;
    t_rect      cachePvRect;
    t_rect      rect;
    t_jrgba     bgcolor;
	t_jrgba		bdcolor;
	t_atom_long		drawVectors;
    
	juce::Component* juceEditorComp;
    EditorComponentHolder* juceWindowComp;
	
	float		params[256]; // must be able to do a deep count of child components to set this dynamically
	void*       leftOutlet;
} t_jucebox;

/* ---------------------------------- */

void *jucebox_new(t_symbol *s, long argc, t_atom *argv);
void jucebox_free(t_jucebox *x);
void jucebox_assist(t_jucebox *x, void *b, long m, long a, char *s);
void jucebox_paint(t_jucebox *x, t_object *patcherview);
void jucebox_getdrawparams(t_jucebox *x, t_object *patcherview, t_jboxdrawparams *params);
void jucebox_bang(t_jucebox *x);
void jucebox_int(t_jucebox *x, long n);
void jucebox_assist(t_jucebox *x, void *b, long m, long a, char *s);

void jucebox_addjucecomponents(t_jucebox* x);
void jucebox_deleteui(t_jucebox *x);
void jucebox_mousedown(t_jucebox *x, t_object *patcherview, t_pt pt, long modifiers);

void jucebox_notify          (t_jucebox *x, t_symbol *s, t_symbol *m, void *sender, void *data);
void jucebox_anything        (t_jucebox *x, t_symbol *s, long argc, t_atom *argv);

void jucebox_patcherview_vis(t_jucebox *x, t_object *patcherview);
void jucebox_patcherview_invis(t_jucebox *x, t_object *patcherview);

static t_class *s_jucebox_class;

/* ---------------------------------- EditorComponentHolder class */

class EditorComponentHolder  :	public juce::Component,
public ComponentListener
{
public:
    EditorComponentHolder (juce::Component* const editorComp_, t_jucebox* x)
    :	ref(x)
	{
		addAndMakeVisible (editorComp_);
        setOpaque (true);
        setVisible (true);
        setWantsKeyboardFocus (false);
        
		editorComp = editorComp_;
		editorComp->addComponentListener(this);
        
        editorComp->setBounds(0,0,DEFWIDTH,DEFHEIGHT);
        setBounds(50,50,DEFWIDTH,DEFHEIGHT);
        
        setInterceptsMouseClicks(false, false);
		setAlwaysOnTop(false);
	}
    
	~EditorComponentHolder()
	{
		editorComp->removeComponentListener(this);
	}
	
	void componentMovedOrResized (Component &component, bool wasMoved, bool wasResized)
	{
        post("movedorresized");
	}
	
	void calcAndSetBounds()
	{
		if(ref->isInitialised)
        {
            t_rect pvRect, rpvRect;
            jbox_get_rect_for_view((t_object *)ref, ref->mPatcherview, &ref->rect);
            object_attr_get_rect(ref->mPatcherview, gensym("rect"), &pvRect);
            object_attr_get_rect(ref->mPatcherview, gensym("visiblecanvasrect"), &rpvRect);
						
			//post("pvRect x: %f y: %f, w: %f, h: %f", pvRect.x, pvRect.y, pvRect.width, pvRect.height);
			//post("rpvRect x: %f y: %f, w: %f, h: %f", rpvRect.x, rpvRect.y, rpvRect.width, rpvRect.height);
            
			Rectangle<int> windowRect(pvRect.x, pvRect.y, pvRect.width, pvRect.height);
			Rectangle<int> boxRect(ref->rect.x, ref->rect.y, ref->rect.width, ref->rect.height);
            Rectangle<int> sectRect = windowRect.getIntersection(boxRect);
			
			//int offsetX = ref->rect.x >= 0 ? 0 : ref->rect.x;
			//int offsetY = ref->rect.y >= 0 ? 0 : ref->rect.y;
			
			editorComp->setBounds( 0, 0, boxRect.getWidth(), boxRect.getHeight());
			setBounds(ref->rect.x - rpvRect.x, ref->rect.y - rpvRect.y, boxRect.getWidth(), boxRect.getHeight() );
		}
	}
    
    void setBgColour()
	{
        editorComp->setColour(EditorComponent::ColourIds::backgroundColourId, jrgbaToColour(&ref->bgcolor, false));
	}
    
    Colour jrgbaToColour(t_jrgba* jrgbaColor, bool ignoreAlpha = true)
	{
        // convert t_jrgba to juce::Colour, ignore alpha.
        if (ignoreAlpha)
        {
            return Colour(uint8(255 * jrgbaColor->red),
                          uint8(255 * jrgbaColor->green),
                          uint8(255 * jrgbaColor->blue));
        }
        else
        {
            return Colour(uint8(255 * jrgbaColor->red),
                          uint8(255 * jrgbaColor->green),
                          uint8(255 * jrgbaColor->blue),
                          uint8(255 * jrgbaColor->alpha));
        }
	}
	
	void resized()
	{
        post("resized");
	}
    
    void mouseDown (const MouseEvent &event)
    {
        Point<float> mouse = event.getPosition().toFloat();
        post("mouseDown %f %f", mouse.x, mouse.y);
    }
    
    void mouseDrag (const MouseEvent& event)
    {
		Point<float> mouse = event.getPosition().toFloat();
        post("mouseDrag %f %f", mouse.x, mouse.y);
    }
    
private:
	t_jucebox* ref;
	Component* editorComp;
};


int C74_EXPORT main(void)
{
	t_class *c;
    
	c = class_new("hoa.meter3D~", (method)jucebox_new, (method)jucebox_free, sizeof(t_jucebox), 0L, A_GIMME, 0);
    
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
    
    CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_jucebox, bgcolor);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.9 0.9 0.9 1.");
	
	CLASS_ATTR_RGBA				(c, "bdcolor", 0, t_jucebox, bdcolor);
	CLASS_ATTR_CATEGORY			(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bdcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bdcolor", 0, "0.1 0.1 0.1 1.");
	
	CLASS_ATTR_LONG				(c, "vectors", 0, t_jucebox, drawVectors);
	CLASS_ATTR_CATEGORY			(c, "vectors", 0, "3D");
	CLASS_ATTR_STYLE_LABEL		(c, "vectors", 0, "onoff", "Draw 3D Vectors");
	CLASS_ATTR_DEFAULT_SAVE		(c, "vectors", 0, "1");
    
    initialiseJuce_GUI();
    
	class_register(CLASS_BOX, c);
	s_jucebox_class = c;
    
	return 0;
}

void jucebox_getdrawparams(t_jucebox *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_bordercolor = x->bdcolor;
	params->d_borderthickness = 1;
	params->d_cornersize = 4;
}

void jucebox_patcherview_vis(t_jucebox *x, t_object *patcherview)
{
    //post("vis");
	//t_class* zaza;
    x->mPatcherview = patcherview;
	x->mPatcher = patcherview_get_patcher(x->mPatcherview);
    object_attach_byptr_register(x, x->mPatcherview, CLASS_NOBOX);
		
    if (!x->isInitialised)
    {
		NSView      *cocoa_view = NULL;
		object_method(x->mPatcherview, gensym("nativewindow"), (void**)&cocoa_view);
        //x->juceWindowComp->addToDesktop(0, cocoa_view);
		x->juceWindowComp->addToDesktop(0);
		//x->juceWindowComp->addToDesktop(ComponentPeer::StyleFlags::windowIgnoresMouseClicks, cocoa_view);
        x->isInitialised = 1;		
    }
}

void jucebox_patcherview_invis(t_jucebox *x, t_object *patcherview)
{
    //post("invis");
    object_detach_byptr(x, x->mPatcherview);
    x->mPatcherview = NULL;
}

void jucebox_notify(t_jucebox *x, t_symbol *s, t_symbol *m, void *sender, void *data)
{
	//post("notify");
    if (sender && (m == gensym("attr_modified") )) {
        
        t_symbol *name = (t_symbol *)object_method(data, gensym("getname"));
        
        if (sender == x) {
            if (name == gensym("bgcolor"))
            {
                x->juceWindowComp->setBgColour();
                jbox_redraw((t_jbox*)x);
            }
            if (name == gensym("patching_rect"))
            {
				x->juceWindowComp->calcAndSetBounds();
            }
        }
        else if (sender == x->mPatcher) {
            //if (name == gensym("name")) { qelem_set(x->mTitle); }
        }
        else if (sender == x->mPatcherview)
        {
            if (name == gensym("visiblecanvasrect"))
            {
                //post("visiblecanvasrect");
                x->juceWindowComp->calcAndSetBounds();
            }
        }
    }
}

void jucebox_assist(t_jucebox *x, void *b, long m, long a, char *s)
{
	if (m == 1)		//inlet
		sprintf(s, "(signal) Audio Inputs");
}

void jucebox_paint(t_jucebox *x, t_object *patcherview)
{
	t_rect rect;
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(patcherview);		// obtain graphics context
    
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
    
    x->rect = rect;
    
    int locked = ((patcherview_get_locked(x->mPatcherview)) != 0);
	   
    if( locked )
    {
        if(!x->juceWindowComp) jucebox_addjucecomponents(x);
        x->juceWindowComp->calcAndSetBounds();
	}
	
	EditorComponent* comp = dynamic_cast <EditorComponent*> (x->juceEditorComp);
	Image openGLSnap = comp->makeScreenshot();
	Image::BitmapData* snapBitmap = new Image::BitmapData(openGLSnap, Image::BitmapData::ReadWriteMode::readOnly);
	
	unsigned char* data = snapBitmap->data;
	//unsigned char* data = snapBitmap->getPixelPointer(0, 0);
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

// mouse interaction

void jucebox_mousedown(t_jucebox *x, t_object *patcherview, t_pt pt, long modifiers)
{
	post("maxbox mousedown");
	jbox_redraw((t_jbox *)x);
}

void jucebox_bang(t_jucebox *x)
{
    x->juceWindowComp->calcAndSetBounds();
//	EditorComponent* comp = dynamic_cast <EditorComponent*> (x->juceEditorComp);
//	
//	Image openGLSnap = comp->makeScreenshot();
//	Colour imgPxColor = openGLSnap.getPixelAt(50, 50);
//	post("image color = %s", imgPxColor.toString().toStdString().c_str());
//	post("image width = %i", openGLSnap.getWidth());
//	
//	Image::BitmapData* snapBitmap = new Image::BitmapData(openGLSnap, Image::BitmapData::ReadWriteMode::readOnly);
//	
//	unsigned char* data = snapBitmap->data;
//	int width, height, imgStride;
//	width = openGLSnap.getWidth();
//	height = openGLSnap.getHeight();
//	imgStride = snapBitmap->pixelStride;
//	
//	t_jsurface* surface = jgraphics_image_surface_create_for_data (data, JGRAPHICS_FORMAT_ARGB32, width, height, imgStride, NULL, NULL);
//	t_jrgba col;
//	jgraphics_image_surface_get_pixel(surface, 50, 50, &col);
//	post("color : r: %d, g: %d, b: %d, a: %d", col.red, col.green, col.blue, col.alpha);
//	jgraphics_surface_destroy (surface);

}

void jucebox_int(t_jucebox *x, long n)
{
	jucebox_bang(x);
	jbox_redraw((t_jbox *)x);
}

void jucebox_addjucecomponents(t_jucebox* x)
{
    long width, height;
	width   = x->rect.width;
	height  = x->rect.height;
	
	x->juceEditorComp = createMaxBoxComponent(); // new EditorComponent();
	x->juceEditorComp->setBounds(0, 0, width, height);
	
	x->juceEditorComp->setOpaque (true);
	x->juceEditorComp->setVisible (true);
	
	x->juceWindowComp = new EditorComponentHolder(x->juceEditorComp, x);
	x->juceWindowComp->calcAndSetBounds();
}

void jucebox_free(t_jucebox *x)
{
	x->juceWindowComp->removeFromDesktop();
	delete x->juceWindowComp;
	jbox_free((t_jbox *)x);
}

void *jucebox_new(t_symbol *s, long argc, t_atom *argv)
{
	t_jucebox *x = NULL;
 	t_dictionary *d = NULL;
	long boxflags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;
    
	x = (t_jucebox *)object_alloc(s_jucebox_class);
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
    
    // Cache rect for comparisons when the user decides to re-size the object
    jbox_get_patching_rect((t_object *)x, &x->rect);
    
    // need to move this earlier for getting the default size but we crash...
    x->juceWindowComp = 0L;
    x->juceEditorComp = 0L;
    
    jucebox_addjucecomponents(x);
    
    x->leftOutlet = outlet_new((t_object*)x, NULL);
    
	attr_dictionary_process(x,d);
	jbox_ready((t_jbox *)x);
	return x;
}
