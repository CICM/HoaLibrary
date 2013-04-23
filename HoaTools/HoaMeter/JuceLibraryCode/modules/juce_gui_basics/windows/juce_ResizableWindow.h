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

#ifndef __JUCE_RESIZABLEWINDOW_JUCEHEADER__
#define __JUCE_RESIZABLEWINDOW_JUCEHEADER__

#include "juce_TopLevelWindow.h"
#include "../mouse/juce_ComponentDragger.h"
#include "../layout/juce_ResizableBorderComponent.h"
#include "../layout/juce_ResizableCornerComponent.h"


//==============================================================================
/**
    A base class for top-level windows that can be dragged around and resized.

    To add content to the window, use its setContentOwned() or setContentNonOwned() methods
    to give it a component that will remain positioned inside it (leaving a gap around
    the edges for a border).

    It's not advisable to add child components directly to a ResizableWindow: put them
    inside your content component instead. And overriding methods like resized(), moved(), etc
    is also not recommended - instead override these methods for your content component.
    (If for some obscure reason you do need to override these methods, always remember to
    call the super-class's resized() method too, otherwise it'll fail to lay out the window
    decorations correctly).

    By default resizing isn't enabled - use the setResizable() method to enable it and
    to choose the style of resizing to use.

    @see TopLevelWindow
*/
class JUCE_API  ResizableWindow  : public TopLevelWindow
{
public:
    //==============================================================================
    /** Creates a ResizableWindow.

        This constructor doesn't specify a background colour, so the LookAndFeel's default
        background colour will be used.

        @param name                 the name to give the component
        @param addToDesktop         if true, the window will be automatically added to the
                                    desktop; if false, you can use it as a child component
    */
    ResizableWindow (const String& name,
                     bool addToDesktop);

    /** Creates a ResizableWindow.

        @param name                 the name to give the component
        @param backgroundColour     the colour to use for filling the window's background.
        @param addToDesktop         if true, the window will be automatically added to the
                                    desktop; if false, you can use it as a child component
    */
    ResizableWindow (const String& name,
                     const Colour& backgroundColour,
                     bool addToDesktop);

    /** Destructor.
        If a content component has been set with setContentOwned(), it will be deleted.
    */
    ~ResizableWindow();

    //==============================================================================
    /** Returns the colour currently being used for the window's background.

        As a convenience the window will fill itself with this colour, but you
        can override the paint() method if you need more customised behaviour.

        This method is the same as retrieving the colour for ResizableWindow::backgroundColourId.

        @see setBackgroundColour
    */
    Colour getBackgroundColour() const noexcept;

    /** Changes the colour currently being used for the window's background.

        As a convenience the window will fill itself with this colour, but you
        can override the paint() method if you need more customised behaviour.

        Note that the opaque state of this window is altered by this call to reflect
        the opacity of the colour passed-in. On window systems which can't support
        semi-transparent windows this might cause problems, (though it's unlikely you'll
        be using this class as a base for a semi-transparent component anyway).

        You can also use the ResizableWindow::backgroundColourId colour id to set
        this colour.

        @see getBackgroundColour
    */
    void setBackgroundColour (const Colour& newColour);

    //==============================================================================
    /** Make the window resizable or fixed.

        @param shouldBeResizable            whether it's resizable at all
        @param useBottomRightCornerResizer  if true, it'll add a ResizableCornerComponent at the
                                            bottom-right; if false, it'll use a ResizableBorderComponent
                                            around the edge
        @see setResizeLimits, isResizable
    */
    void setResizable (bool shouldBeResizable,
                       bool useBottomRightCornerResizer);

    /** True if resizing is enabled.

        @see setResizable
    */
    bool isResizable() const noexcept;

    /** This sets the maximum and minimum sizes for the window.

        If the window's current size is outside these limits, it will be resized to
        make sure it's within them.

        Calling setBounds() on the component will bypass any size checking - it's only when
        the window is being resized by the user that these values are enforced.

        @see setResizable, setFixedAspectRatio
    */
    void setResizeLimits (int newMinimumWidth,
                          int newMinimumHeight,
                          int newMaximumWidth,
                          int newMaximumHeight) noexcept;

    /** Returns the bounds constrainer object that this window is using.

        You can access this to change its properties.
    */
    ComponentBoundsConstrainer* getConstrainer() noexcept           { return constrainer; }

    /** Sets the bounds-constrainer object to use for resizing and dragging this window.

        A pointer to the object you pass in will be kept, but it won't be deleted
        by this object, so it's the caller's responsiblity to manage it.

        If you pass 0, then no contraints will be placed on the positioning of the window.
    */
    void setConstrainer (ComponentBoundsConstrainer* newConstrainer);

    /** Calls the window's setBounds method, after first checking these bounds
        with the current constrainer.

        @see setConstrainer
    */
    void setBoundsConstrained (const Rectangle<int>& bounds);


    //==============================================================================
    /** Returns true if the window is currently in full-screen mode.

        @see setFullScreen
    */
    bool isFullScreen() const;

    /** Puts the window into full-screen mode, or restores it to its normal size.

        If true, the window will become full-screen; if false, it will return to the
        last size it was before being made full-screen.

        @see isFullScreen
    */
    void setFullScreen (bool shouldBeFullScreen);

    /** Returns true if the window is currently minimised.

        @see setMinimised
    */
    bool isMinimised() const;

    /** Minimises the window, or restores it to its previous position and size.

        When being un-minimised, it'll return to the last position and size it
        was in before being minimised.

        @see isMinimised
    */
    void setMinimised (bool shouldMinimise);

    /** Adds the window to the desktop using the default flags. */
    void addToDesktop();

    //==============================================================================
    /** Returns a string which encodes the window's current size and position.

        This string will encapsulate the window's size, position, and whether it's
        in full-screen mode. It's intended for letting your application save and
        restore a window's position.

        Use the restoreWindowStateFromString() to restore from a saved state.

        @see restoreWindowStateFromString
    */
    String getWindowStateAsString();

    /** Restores the window to a previously-saved size and position.

        This restores the window's size, positon and full-screen status from an
        string that was previously created with the getWindowStateAsString()
        method.

        @returns false if the string wasn't a valid window state
        @see getWindowStateAsString
    */
    bool restoreWindowStateFromString (const String& previousState);


    //==============================================================================
    /** Returns the current content component.

        This will be the component set by setContentOwned() or setContentNonOwned, or
        nullptr if none has yet been specified.

        @see setContentOwned, setContentNonOwned
    */
    Component* getContentComponent() const noexcept                 { return contentComponent; }

    /** Changes the current content component.

        This sets a component that will be placed in the centre of the ResizableWindow,
        (leaving a space around the edge for the border).

        You should never add components directly to a ResizableWindow (or any of its subclasses)
        with addChildComponent(). Instead, add them to the content component.

        @param newContentComponent  the new component to use - this component will be deleted when it's
                                    no longer needed (i.e. when the window is deleted or a new content
                                    component is set for it). To set a component that this window will not
                                    delete, call setContentNonOwned() instead.
        @param resizeToFitWhenContentChangesSize  if true, then the ResizableWindow will maintain its size
                                    such that it always fits around the size of the content component. If false,
                                    the new content will be resized to fit the current space available.
    */
    void setContentOwned (Component* newContentComponent,
                          bool resizeToFitWhenContentChangesSize);

    /** Changes the current content component.

        This sets a component that will be placed in the centre of the ResizableWindow,
        (leaving a space around the edge for the border).

        You should never add components directly to a ResizableWindow (or any of its subclasses)
        with addChildComponent(). Instead, add them to the content component.

        @param newContentComponent  the new component to use - this component will NOT be deleted by this
                                    component, so it's the caller's responsibility to manage its lifetime (it's
                                    ok to delete it while this window is still using it). To set a content
                                    component that the window will delete, call setContentOwned() instead.
        @param resizeToFitWhenContentChangesSize  if true, then the ResizableWindow will maintain its size
                                    such that it always fits around the size of the content component. If false,
                                    the new content will be resized to fit the current space available.
    */
    void setContentNonOwned (Component* newContentComponent,
                             bool resizeToFitWhenContentChangesSize);

    /** Removes the current content component.
        If the previous content component was added with setContentOwned(), it will also be deleted. If
        it was added with setContentNonOwned(), it will simply be removed from this component.
    */
    void clearContentComponent();

    /** Changes the window so that the content component ends up with the specified size.

        This is basically a setSize call on the window, but which adds on the borders,
        so you can specify the content component's target size.
    */
    void setContentComponentSize (int width, int height);

    /** Returns the width of the frame to use around the window.
        @see getContentComponentBorder
    */
    virtual BorderSize<int> getBorderThickness();

    /** Returns the insets to use when positioning the content component.
        @see getBorderThickness
    */
    virtual BorderSize<int> getContentComponentBorder();

    //==============================================================================
    /** A set of colour IDs to use to change the colour of various aspects of the window.

        These constants can be used either via the Component::setColour(), or LookAndFeel::setColour()
        methods.

        @see Component::setColour, Component::findColour, LookAndFeel::setColour, LookAndFeel::findColour
    */
    enum ColourIds
    {
        backgroundColourId          = 0x1005700,  /**< A colour to use to fill the window's background. */
    };

    //==============================================================================
    /** @deprecated - use setContentOwned() and setContentNonOwned() instead. */
    JUCE_DEPRECATED (void setContentComponent (Component* newContentComponent,
                                               bool deleteOldOne = true,
                                               bool resizeToFit = false));
    using TopLevelWindow::addToDesktop;

protected:
    //==============================================================================
    /** @internal */
    void paint (Graphics& g);
    /** (if overriding this, make sure you call ResizableWindow::moved() in your subclass) */
    void moved();
    /** (if overriding this, make sure you call ResizableWindow::resized() in your subclass) */
    void resized();
    /** @internal */
    void mouseDown (const MouseEvent& e);
    /** @internal */
    void mouseDrag (const MouseEvent& e);
    /** @internal */
    void lookAndFeelChanged();
    /** @internal */
    void childBoundsChanged (Component* child);
    /** @internal */
    void parentSizeChanged();
    /** @internal */
    void visibilityChanged();
    /** @internal */
    void activeWindowStatusChanged();
    /** @internal */
    int getDesktopWindowStyleFlags() const;

   #if JUCE_DEBUG
    /** Overridden to warn people about adding components directly to this component
        instead of using setContentOwned().

        If you know what you're doing and are sure you really want to add a component, specify
        a base-class method call to Component::addAndMakeVisible(), to side-step this warning.
    */
    void addChildComponent (Component* child, int zOrder = -1);
    /** Overridden to warn people about adding components directly to this component
        instead of using setContentOwned().

        If you know what you're doing and are sure you really want to add a component, specify
        a base-class method call to Component::addAndMakeVisible(), to side-step this warning.
    */
    void addAndMakeVisible (Component* child, int zOrder = -1);
   #endif

    ScopedPointer <ResizableCornerComponent> resizableCorner;
    ScopedPointer <ResizableBorderComponent> resizableBorder;

private:
    //==============================================================================
    Component::SafePointer <Component> contentComponent;
    bool ownsContentComponent, resizeToFitContent, fullscreen;
    ComponentDragger dragger;
    Rectangle<int> lastNonFullScreenPos;
    ComponentBoundsConstrainer defaultConstrainer;
    ComponentBoundsConstrainer* constrainer;
    #if JUCE_DEBUG
    bool hasBeenResized;
    #endif

    void initialise (bool addToDesktop);
    void updateLastPos();
    void setContent (Component*, bool takeOwnership, bool resizeToFit);

   #if JUCE_CATCH_DEPRECATED_CODE_MISUSE
    // The parameters for these methods have changed - please update your code!
    JUCE_DEPRECATED (void getBorderThickness (int& left, int& top, int& right, int& bottom));
    JUCE_DEPRECATED (void getContentComponentBorder (int& left, int& top, int& right, int& bottom));
   #endif

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResizableWindow)
};


#endif   // __JUCE_RESIZABLEWINDOW_JUCEHEADER__
