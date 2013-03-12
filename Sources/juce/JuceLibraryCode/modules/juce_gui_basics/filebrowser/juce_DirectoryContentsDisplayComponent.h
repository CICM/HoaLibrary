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

#ifndef __JUCE_DIRECTORYCONTENTSDISPLAYCOMPONENT_JUCEHEADER__
#define __JUCE_DIRECTORYCONTENTSDISPLAYCOMPONENT_JUCEHEADER__

#include "../components/juce_Component.h"
#include "juce_DirectoryContentsList.h"
#include "juce_FileBrowserListener.h"


//==============================================================================
/**
    A base class for components that display a list of the files in a directory.

    @see DirectoryContentsList
*/
class JUCE_API  DirectoryContentsDisplayComponent
{
public:
    //==============================================================================
    /** Creates a DirectoryContentsDisplayComponent for a given list of files. */
    DirectoryContentsDisplayComponent (DirectoryContentsList& listToShow);

    /** Destructor. */
    virtual ~DirectoryContentsDisplayComponent();

    //==============================================================================
    /** Returns the number of files the user has got selected.
        @see getSelectedFile
    */
    virtual int getNumSelectedFiles() const = 0;

    /** Returns one of the files that the user has currently selected.
        The index should be in the range 0 to (getNumSelectedFiles() - 1).
        @see getNumSelectedFiles
    */
    virtual File getSelectedFile (int index) const = 0;

    /** Deselects any selected files. */
    virtual void deselectAllFiles() = 0;

    /** Scrolls this view to the top. */
    virtual void scrollToTop() = 0;

    /** If the specified file is in the list, it will become the only selected item
        (and if the file isn't in the list, all other items will be deselected). */
    virtual void setSelectedFile (const File&) = 0;

    //==============================================================================
    /** Adds a listener to be told when files are selected or clicked.
        @see removeListener
    */
    void addListener (FileBrowserListener* listener);

    /** Removes a listener.
        @see addListener
    */
    void removeListener (FileBrowserListener* listener);


    //==============================================================================
    /** A set of colour IDs to use to change the colour of various aspects of the list.

        These constants can be used either via the Component::setColour(), or LookAndFeel::setColour()
        methods.

        @see Component::setColour, Component::findColour, LookAndFeel::setColour, LookAndFeel::findColour
    */
    enum ColourIds
    {
        highlightColourId      = 0x1000540, /**< The colour to use to fill a highlighted row of the list. */
        textColourId           = 0x1000541, /**< The colour for the text. */
    };

    //==============================================================================
    /** @internal */
    void sendSelectionChangeMessage();
    /** @internal */
    void sendDoubleClickMessage (const File& file);
    /** @internal */
    void sendMouseClickMessage (const File& file, const MouseEvent& e);

protected:
    //==============================================================================
    DirectoryContentsList& fileList;
    ListenerList <FileBrowserListener> listeners;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DirectoryContentsDisplayComponent)
};


#endif   // __JUCE_DIRECTORYCONTENTSDISPLAYCOMPONENT_JUCEHEADER__
