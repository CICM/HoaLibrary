/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_COMPONENTDRAGGER_JUCEHEADER__
#define __JUCE_COMPONENTDRAGGER_JUCEHEADER__

#include "juce_MouseEvent.h"
#include "../layout/juce_ComponentBoundsConstrainer.h"


//==============================================================================
/**
    An object to take care of the logic for dragging components around with the mouse.

    Very easy to use - in your mouseDown() callback, call startDraggingComponent(),
    then in your mouseDrag() callback, call dragComponent().

    When starting a drag, you can give it a ComponentBoundsConstrainer to use
    to limit the component's position and keep it on-screen.

    e.g. @code
    class MyDraggableComp
    {
        ComponentDragger myDragger;

        void mouseDown (const MouseEvent& e)
        {
            myDragger.startDraggingComponent (this, e);
        }

        void mouseDrag (const MouseEvent& e)
        {
            myDragger.dragComponent (this, e, nullptr);
        }
    };
    @endcode
*/
class JUCE_API  ComponentDragger
{
public:
    //==============================================================================
    /** Creates a ComponentDragger. */
    ComponentDragger();

    /** Destructor. */
    virtual ~ComponentDragger();

    //==============================================================================
    /** Call this from your component's mouseDown() method, to prepare for dragging.

        @param componentToDrag      the component that you want to drag
        @param e                    the mouse event that is triggering the drag
        @see dragComponent
    */
    void startDraggingComponent (Component* componentToDrag,
                                 const MouseEvent& e);

    /** Call this from your mouseDrag() callback to move the component.

        This will move the component, but will first check the validity of the
        component's new position using the checkPosition() method, which you
        can override if you need to enforce special positioning limits on the
        component.

        @param componentToDrag      the component that you want to drag
        @param e                    the current mouse-drag event
        @param constrainer          an optional constrainer object that should be used
                                    to apply limits to the component's position. Pass
                                    null if you don't want to contrain the movement.
        @see startDraggingComponent
    */
    void dragComponent (Component* componentToDrag,
                        const MouseEvent& e,
                        ComponentBoundsConstrainer* constrainer);

private:
    //==============================================================================
    Point<int> mouseDownWithinTarget;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentDragger)
};

#endif   // __JUCE_COMPONENTDRAGGER_JUCEHEADER__
