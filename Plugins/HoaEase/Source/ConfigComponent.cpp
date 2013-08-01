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

#include "ConfigComponent.h"

//==============================================================================
ConfigComponent::ConfigComponent() :
    m_openCloseTrigger(0)
{
    m_configPanelState = true;
    parentComp = getParentComponent();
    m_closedBounds = Rectangle<int>(0, 0, 20, 20);
    m_openedBounds = Rectangle<int>(0, 0, 100, 100);
    setBounds(m_closedBounds);
    
    m_btnWidth = m_closedBounds.getWidth();
    
    // add menu components
    addAndMakeVisible(m_openCloseTrigger = new ToggleButton (String::empty) );
    m_openCloseTrigger->addListener(this);
    
    addAndMakeVisible(m_dir_of_rotation_combobox = new ComboBox (String::empty) );
    m_dir_of_rotation_combobox->addListener(this);
    m_dir_of_rotation_combobox->setTextWhenNothingSelected (String("Direction of the rotation"));
    m_dir_of_rotation_combobox->addItem("Clockwise", 1);
    m_dir_of_rotation_combobox->addItem("Anti-Clockwise", 2);
    m_dir_of_rotation_combobox->setSelectedId(1, true); // don't notify
}

ConfigComponent::~ConfigComponent()
{
    m_openCloseTrigger->removeListener(this);
    m_dir_of_rotation_combobox->removeListener(this);
}

void ConfigComponent::setClosedBounds(Rectangle<int> _closedBounds)
{
    m_closedBounds = _closedBounds;
    m_btnWidth = m_closedBounds.getWidth();
    repaint();
}
void ConfigComponent::setClosedBounds(int _x, int _y, int _width, int _height)
{
    m_closedBounds = Rectangle<int>(_x, _y, _width, _height);
    m_btnWidth = m_closedBounds.getWidth();
    repaint();
}
void ConfigComponent::setOpenedBounds(Rectangle<int> _openedBounds)
{
    m_openedBounds = _openedBounds;
    repaint();
}
void ConfigComponent::setOpenedBounds(int _x, int _y, int _width, int _height)
{
    m_openedBounds = Rectangle<int>(_x, _y, _width, _height);
    repaint();
}

void ConfigComponent::paint (Graphics& g)
{
    g.fillAll( Colour::greyLevel(0.5).withAlpha(float(0.9)) );
    setBounds(m_configPanelState ? m_openedBounds : m_closedBounds);
    if (!m_configPanelState) { // closed
        setBounds(m_closedBounds);
        g.setColour(Colour::greyLevel(0.1));
        g.drawRect(0, 0, getWidth(), getHeight());
        m_openCloseTrigger->setBounds (0, 0, m_btnWidth, m_btnWidth);
    }
    else
    {
        setBounds(m_openedBounds);
        g.setColour(Colour::greyLevel(0.1));
        g.drawRect(0, 0, getWidth(), getHeight());
        m_openCloseTrigger->setBounds (getWidth()-m_btnWidth, 0, m_btnWidth, m_btnWidth);
        m_dir_of_rotation_combobox->setBounds (50, 50, 150, 25);
    }
}
void ConfigComponent::resized()
{
    ;
}

void ConfigComponent::buttonClicked (Button *button)
{
    if (button == m_openCloseTrigger) {
        m_openCloseTrigger->getToggleState() ? show() : hide();
    }
}

void ConfigComponent::buttonStateChanged (Button *button)
{
    ;
}

void ConfigComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == m_dir_of_rotation_combobox) {
        triggerChangeMessage(sendNotificationAsync);
    }
}
void ConfigComponent::setDirOfRotation(int itemId, const NotificationType notification)
{
    m_dir_of_rotation_combobox->setSelectedId(itemId, true); // don't notify
    triggerChangeMessage(notification);
}

void ConfigComponent::show(bool _animated, int millisecondsToTake)
{
    setBounds(m_openedBounds);
    m_configPanelState = true;
    toFront(true);
    //repaint();
}
void ConfigComponent::hide(bool _animated, int millisecondsToTake)
{
    setBounds(m_closedBounds);
    toBack();
    m_configPanelState = false;
    //repaint();
}

void ConfigComponent::triggerChangeMessage (const NotificationType notification)
{
    if (notification != dontSendNotification)
    {
        if (notification == sendNotificationSync)
            sendSynchronousChangeMessage();
        else sendChangeMessage ();
    }
}