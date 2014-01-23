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
void jucebox_boxscreenrectchanged(t_jucebox *box, t_object *patcherview);

long jucebox_hittest(t_jucebox *x, t_object *patcherview, t_pt pt);

static t_class *s_jucebox_class;

/* ---------------------------------- EditorComponentHolder class */

class EditorComponentHolder  :	public juce::Component,
public ComponentListener,
public Timer
{
public:
    EditorComponentHolder (juce::Component* const editorComp_, t_jucebox* x)
    :	ref(x)
	{
		addAndMakeVisible (editorComp_);
        setOpaque (false);
        setVisible (true);
        setWantsKeyboardFocus (false);
        
		editorComp = editorComp_;
		editorComp->addComponentListener(this);
        
        editorComp->setBounds(0,0,DEFWIDTH,DEFHEIGHT);
        setBounds(50,50,DEFWIDTH,DEFHEIGHT);
        
		//startTimer(20);
        setInterceptsMouseClicks(false, false);
		setAlwaysOnTop(true);
	}
    
	~EditorComponentHolder()
	{
		editorComp->removeComponentListener(this);
		//stopTimer();
	}
	
	void componentMovedOrResized (Component &component, bool wasMoved, bool wasResized)
	{
        post("movedorresized");
        //post("moved %i", (int)wasMoved);
        //t_size newSize = {(double)editorComp->getWidth(), (double)editorComp->getHeight()};
        //jbox_set_size((t_object*)ref, &newSize);
	}
	
	void timerCallback()
    {
        //char locked = jpatcher_get_locked(jbox_get_patcher((t_object*)ref));
        
        if (ref->isInitialised) {
            int locked = ((patcherview_get_locked(ref->mPatcherview)) != 0);
            int presentation = ((patcherview_get_presentation(ref->mPatcherview)) != 0);
            //int box_presentation = ((jbox_get_presentation((t_object*)ref)) != 0); // dont seems to work ! why ??
            int box_presentation = (ref->j_box.b_presentation != 0);
			post( "box_presentation %i", box_presentation);
            
            //int pv_visible = (patcherview_get_visible(ref->mPatcherview) != 0);
            //post("visible %i", pv_visible);
            
            if( (locked && !presentation) || (box_presentation && presentation && locked)) {
                setVisible(true);
                calcAndSetBounds();
                //getPeer()->toFront(false);
            }
            else {
                setVisible(false);
            }
        }
        //post("islock = %i", locked);
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
	class_addmethod(c, (method)jucebox_boxscreenrectchanged, "boxscreenrectchanged",	A_CANT, 0);
	class_addmethod(c, (method)jucebox_bang,		"bang", 0);
	class_addmethod(c, (method)jucebox_hittest,		"hittest", 0);
			
    CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 200 200");
    CLASS_ATTR_INVISIBLE		(c, "color", 0);
    
    CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_jucebox, bgcolor);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.9 0.9 0.9 1.");
    
    initialiseJuce_GUI();
    
	class_register(CLASS_BOX, c);
	s_jucebox_class = c;
    
	return 0;
}

long jucebox_hittest(t_jucebox *x, t_object *patcherview, t_pt pt)
{
    return 0;
}

void jucebox_boxscreenrectchanged(t_jucebox *box, t_object *patcherview)
{
	//post("boxscreenrectchanged");
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
		
        //zaza = object_class(x->mPatcherview);
		//for(int i =0; i <zaza->c_messcount -1; i++)
		//{
			//post("method % i : %s", i, zaza->c_messlist[i].m_sym->s_name);
		//}
		
		NSView      *cocoa_view = NULL;
		object_method(x->mPatcherview, gensym("nativewindow"), (void**)&cocoa_view);
        //x->juceWindowComp->addToDesktop(0, cocoa_view);
		//x->juceWindowComp->addToDesktop(ComponentPeer::StyleFlags::windowIgnoresMouseClicks, 0);
		x->juceWindowComp->addToDesktop(ComponentPeer::StyleFlags::windowIgnoresMouseClicks, cocoa_view);
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
		sprintf(s, "(signal) Audio Input");
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
	else
    {
        jgraphics_set_source_jrgba(g, &x->bgcolor);
        jgraphics_set_line_width(g, 1.);
        
        jgraphics_rectangle(g, 1., 1., rect.width - 2, rect.height - 2);
        jgraphics_fill(g);
        
        long pad = 5;
        t_jrgba crossColor = x->bgcolor;
        crossColor.red -= 0.1;
        crossColor.green -= 0.1;
        crossColor.blue -= 0.1;
        jgraphics_set_source_jrgba(g, &crossColor);
        jgraphics_set_line_width(g, pad);
        
        jgraphics_move_to(g, pad, pad);
        jgraphics_line_to(g, x->rect.width-pad, x->rect.height-pad);
        jgraphics_stroke(g);
        
        jgraphics_move_to(g, x->rect.width-pad, pad);
        jgraphics_line_to(g, pad, x->rect.height-pad);
        jgraphics_stroke(g);
	}
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
	//object_method(x->mPatcherview, gensym("selectall"), TRUE);

	static char* const flopArguments[ ] =
	{
		"A_NOTHING",
		"A_LONG",
		"A_FLOAT",
		"A_SYM",
		"A_OBJ",
		"A_DEFLONG",
		"A_DEFFLOAT",
		"A_DEFSYM",
		"A_GIMME",
		"A_CANT",
		"A_"
	};
	
	t_object *obj = x->mPatcher;
	
    long i, count = ob_class(obj)->c_messcount;
    t_messlist *p = ob_messlist(obj);
	
    for (i = 1; i < count; i++) {
        if ((p + i)->m_sym) {
            char *a = (p + i)->m_type;
            post("%ld / %s / %s", i, (p + i)->m_sym->s_name, flopArguments[FLOP_CLAMP(a[0], 0, 10)]);
        }
    }
}

void jucebox_int(t_jucebox *x, long n)
{
	jucebox_bang(x);
	jbox_redraw((t_jbox *)x);
}

void jucebox_getdrawparams(t_jucebox *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_bordercolor.alpha = 0;
	params->d_boxfillcolor.alpha = 0;
}


void jucebox_addjucecomponents(t_jucebox* x)
{
    long width, height;
	width   = x->rect.width;
	height  = x->rect.height;
	
	x->juceEditorComp = createMaxBoxComponent(); // new EditorComponent();
	x->juceEditorComp->setBounds(0, 0, width, height);
	
	x->juceEditorComp->setOpaque (false);
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
    | JBOX_GROWBOTH
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
