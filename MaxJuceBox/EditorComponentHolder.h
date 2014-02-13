/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef DEF_EDITORCOMPONENTHELPER
#define DEF_EDITORCOMPONENTHELPER

#include "jucebox_struct.h"
#include "MaxBoxComponent.h"

/* ---------------------------------- EditorComponentHolder class */

class EditorComponentHolder  :	public juce::Component,
public ComponentListener
{
public:
    EditorComponentHolder (juce::Component* const editorComp_, t_jucebox* x) : jucebox(x)
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
		if(jucebox->isInitialised)
        {
            jbox_get_rect_for_view((t_object *)jucebox, jucebox->mPatcherview, &jucebox->box_rect);
			Rectangle<int> boxRect(jucebox->box_rect.x, jucebox->box_rect.y, jucebox->box_rect.width, jucebox->box_rect.height);
			editorComp->setBounds( 0, 0, boxRect.getWidth(), boxRect.getHeight());
		}
	}
    
private:
	t_jucebox* jucebox;
	Component* editorComp;
};

#endif