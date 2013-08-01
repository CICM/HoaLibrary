/*
 * == HoaLibrary ==
 * Copyright (C) 2012-2013, Julien Colafrancesco, Pierre Guillot, Eliott Paris Universite Paris 8
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef __hoaplug__ConfigComponent__
#define __hoaplug__ConfigComponent__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Ambisonics/cicmTools.h"


//==============================================================================
class ConfigComponent    :
    public Component,
    public ChangeBroadcaster,
    public Button::Listener,
    public ComboBox::Listener
{
public:
    ConfigComponent();
    ~ConfigComponent();
    
    void paint (Graphics&);
    void resized();
    
    // action methods :
    void show(bool _animated = true, int millisecondsToTake = 200);
    void hide(bool _animated = true, int millisecondsToTake = 200);
    
    //mouse events :
    /*
    void mouseMove (const MouseEvent &event);
    void mouseDown (const MouseEvent &event);
    void mouseDrag (const MouseEvent &event);
    void mouseUp   (const MouseEvent &event);
    */
    
    // setters :
    void setDirOfRotation(int itemId, const NotificationType notification = sendNotificationAsync);
    void setClosedBounds(Rectangle<int> _closedBounds);
    void setClosedBounds(int _x, int _y, int _width, int _height);
    void setOpenedBounds(Rectangle<int> _openedBounds);
    void setOpenedBounds(int _x, int _y, int _width, int _height);

    // getters :
    inline int   getDirOfRotation() {return m_dir_of_rotation_combobox->getSelectedId();};
    int   getDragState(const int _sourceIndex);
    int   getValueChanged(const int _sourceIndex);
    
    void resetDragState(const int _sourceIndex);
    void resetValueChanged(const int _sourceIndex);
    
    void buttonClicked (Button *button);
    void buttonStateChanged (Button *button);
    
private:
    
    void setComponentSize();
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged);
    
    void triggerChangeMessage (const NotificationType notification);
    
    // inside components
    ToggleButton* m_openCloseTrigger; // show/hide configMenu component
    // text credits
    // combobox rotation
    ComboBox* m_dir_of_rotation_combobox;
    
    Component *parentComp;
    bool m_configPanelState;
    Rectangle<int> m_closedBounds;
    Rectangle<int> m_openedBounds;
    
    int m_btnWidth;
    
    int m_padding;
    inline int getPadWidth() {return getWidth();};
    inline float getCenter() {return getWidth()*0.5;};
    
    int m_sources_dragState[MAX_SOURCES];
    int m_sources_ValueChanged[MAX_SOURCES];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigComponent)
};

#endif /* defined(__hoaplug__ConfigComponent__) */
