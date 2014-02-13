/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef DEF_EDITORCOMPONENTHELPER
#define DEF_EDITORCOMPONENTHELPER

#include "MaxBoxComponent.h"

/* ---------------------------------- EditorComponentHolder class */

class EditorComponentHolder  :	public juce::Component,
public ComponentListener
{
public:
    EditorComponentHolder (juce::Component* const editorComp_, t_object* x) : ref(x)
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
    
	// convert t_jrgba to juce::Colour
	
    Colour jrgbaToColour(t_jrgba* jrgbaColor)
	{
		return Colour(uint8(255 * jrgbaColor->red),
					  uint8(255 * jrgbaColor->green),
					  uint8(255 * jrgbaColor->blue),
					  float(jrgbaColor->alpha));
	}
    
private:
	t_object* ref;
	Component* editorComp;
};

EditorComponent* getOGLComponent(t_object *x);
EditorComponent* getOGLComponent(t_object *x)
{
	return dynamic_cast <EditorComponent*> (x->juceEditorComp);
}

#endif