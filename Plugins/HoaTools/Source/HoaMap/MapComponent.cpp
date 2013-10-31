/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice,
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MapComponent.h"

#define MIN_ZOOM 0.05

/************************************************************************************/
/***************************** EDITOR ***********************************************/
/************************************************************************************/

MapEditor::MapEditor(SourcesManager* aSourceManager, AudioProcessor* aProcessor)
{
    m_sources_manager   = aSourceManager;
    m_processor         = aProcessor;
    
    m_souce_selected    = -1;
    m_group_selected    = -1;
    m_sources_size      = 15.;
    m_selected          = 0;
}


MapEditor::~MapEditor()
{
    ;
}

void MapEditor::mouseMove(const MouseEvent &event)
{
    Point<float> point;
    Point<float> mouse = event.getPosition().toFloat();
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    m_selected          = 0;
    m_souce_selected    = -1;
    m_group_selected    = -1;
    for (int i = 0; i < m_sources_manager->getMaximumIndexOfSource(); i++)
    {
        if(m_sources_manager->sourceGetExistence(i))
        {
            point.setXY(m_sources_manager->sourceGetAbscissa(i) * m_sources_manager->getZoom(), m_sources_manager->sourceGetOrdinate(i) * m_sources_manager->getZoom());
            if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
            {
                m_souce_selected = i;
                setMouseCursor(MouseCursor::PointingHandCursor);
                repaint();
                return;
            }
        }
    }
    for (int i = 0; i < m_sources_manager->getMaximumIndexOfGroup(); i++)
    {
        if(m_sources_manager->groupGetExistence(i))
        {
            point.setXY(m_sources_manager->groupGetAbscissa(i) * m_sources_manager->getZoom(), m_sources_manager->groupGetOrdinate(i) * m_sources_manager->getZoom());
            if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
            {
                m_group_selected = i;
                setMouseCursor(MouseCursor::PointingHandCursor);
                repaint();
                return;
            }
        }
    }
    m_drag_mode = 0;
    repaint();
    setMouseCursor(MouseCursor::NormalCursor);
}

void MapEditor::mouseDown(const MouseEvent &event)
{
    Point<float> point;
    Point<float> mouse = event.getPosition().toFloat();
    Point<float> rect  = mouse;
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    m_selected          = 0;
    m_souce_selected    = -1;
    m_drag_mode         = 0;    
    if(event.mods.isAltDown() && event.mods.isShiftDown())
    {
        m_drag_mode = 1;
    }
    else if(event.mods.isAltDown() && !event.mods.isShiftDown())
    {
        m_drag_mode = 2;
    }
    else if(event.mods.isCtrlDown() && event.mods.isShiftDown())
    {
        m_drag_mode = 3;
    }
    else if(event.mods.isCtrlDown() && !event.mods.isShiftDown())
    {
        m_drag_mode = 4;
    }
    else if(event.mods.isShiftDown())
    {
        m_drag_mode = 5;
    }
    for (int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
    {
        point.setXY(m_sources_manager->sourceGetAbscissa(i) * m_sources_manager->getZoom(), m_sources_manager->sourceGetOrdinate(i) * m_sources_manager->getZoom());
        if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
        {
            if(event.mods.isRightButtonDown())
            {
                PopupMenu Popup;
                Popup.setLookAndFeel(&LookAndFeel);
                Popup.addItem(1, String("Source Menu"), false);
                Popup.addSeparator();
                Popup.addItem(2, String("Remove source"));
                if(m_sources_manager->sourceGetMute(i))
                    Popup.addItem(3, String("Unmute source"));
                else
                    Popup.addItem(3, String("Mute source"));
                
                const int choice = Popup.show();
                if(choice == 2)
                {
                    m_sources_manager->sourceRemove(i);
                }
                else if(choice == 3)
                {
                    m_processor->beginParameterChangeGesture(i*3+3);
                    if(m_sources_manager->sourceGetMute(i))
                    {
                        m_sources_manager->sourceSetMute(i, 0);
                    }
                    else
                    {
                        m_sources_manager->sourceSetMute(i, 1);
                    }
                    m_processor->endParameterChangeGesture(i*3+3);
                }
            }
            else
            {
                m_souce_selected = i;
                setMouseCursor(MouseCursor::PointingHandCursor);
            }
            repaint();
            return;
        }
    }
    
    for (int i = 0; i < m_sources_manager->getMaximumIndexOfGroup(); i++)
    {
        if(m_sources_manager->groupGetExistence(i))
        {
            point.setXY(m_sources_manager->groupGetAbscissa(i) * m_sources_manager->getZoom(), m_sources_manager->groupGetOrdinate(i) * m_sources_manager->getZoom());
            if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
            {
                if(event.mods.isRightButtonDown())
                {
                    PopupMenu Popup;
                    Popup.setLookAndFeel(&LookAndFeel);
                    Popup.addItem(1, String("Group Menu"), false);
                    Popup.addSeparator();
                    Popup.addItem(2, String("Remove group"));
                    Popup.addItem(3, String("Remove group and sources"));
                    if(m_sources_manager->groupGetMute(i) || m_sources_manager->groupGetIfSourceMuted(i) == 1)
                        Popup.addItem(4, String("Unmute group"));
                    if(!m_sources_manager->groupGetMute(i))
                        Popup.addItem(5, String("Mute group"));
                    
                    const int choice = Popup.show();
                    if(choice == 2)
                    {
                        m_sources_manager->groupRemove(i);
                    }
                    else if(choice == 3)
                    {
                        m_sources_manager->groupRemoveWithSources(i);
                    }
                    else if(choice == 4)
                    {
                        for(int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
                        {
                            m_processor->beginParameterChangeGesture(i*3+3);
                        }
                        m_sources_manager->groupSetMute(i, 0);
                        for(int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
                        {
                            m_processor->endParameterChangeGesture(i*3+3);
                        }
                    }
                    else if(choice == 5)
                    {
                        for(int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
                        {
                            m_processor->beginParameterChangeGesture(i*3+3);
                        }
                        m_sources_manager->groupSetMute(i, 1);
                        for(int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
                        {
                            m_processor->endParameterChangeGesture(i*3+3);
                        }
                    }
                }
                else
                {
                    m_group_selected = i;
                    setMouseCursor(MouseCursor::PointingHandCursor);
                }
                repaint();
                return;
            }
        }
    }
    if(event.mods.isRightButtonDown())
    {
        PopupMenu Popup;
        Popup.setLookAndFeel(&LookAndFeel);
        Popup.addItem(1, String("Menu"), false);
        Popup.addSeparator();
        Popup.addItem(2, String("Add source"));
        Popup.addItem(3, String("Clear all"));
        
        const int choice = Popup.show();
        if(choice == 2)
        {
            m_sources_manager->sourceNewCartesian(mouse.getX() / m_sources_manager->getZoom(), mouse.getY() / m_sources_manager->getZoom());
        }
        else if(choice == 3)
        {
            m_sources_manager->clearAll();
        }
    }
    m_selected  = 1;
    m_selection.setPosition(rect);
    m_selection.setWidth(0);
    m_selection.setHeight(0);
    
    repaint();
    setMouseCursor(MouseCursor::NormalCursor);
}
void MapEditor::mouseDrag(const MouseEvent &event)
{    
    Point<float> source;
    Point<float> mouse = event.getPosition().toFloat();
    Point<float> rect  = mouse;
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    if(m_souce_selected != -1)
    {
        m_processor->beginParameterChangeGesture(m_souce_selected*3);
        
        if (m_drag_mode == 1)
        {
            m_sources_manager->sourceSetRadius(m_souce_selected, mouse.getDistanceFrom(Point<float>(0., 0.)) / m_sources_manager->getZoom());
        }
        else if(m_drag_mode == 2)
        {
            m_sources_manager->sourceSetAngle(m_souce_selected, mouse.getAngleToPoint(Point<float>(0., 0.)));
        }
        else if(m_drag_mode == 3)
        {
            m_sources_manager->sourceSetAbscissa(m_souce_selected, mouse.getX() / m_sources_manager->getZoom());
        }
        else if(m_drag_mode == 4)
        {
            m_sources_manager->sourceSetOrdinate(m_souce_selected, mouse.getY() / m_sources_manager->getZoom());
        }
        else
        {
            m_sources_manager->sourceSetCartesian(m_souce_selected, mouse.getX() / m_sources_manager->getZoom(), mouse.getY() / m_sources_manager->getZoom());
        }
        m_processor->endParameterChangeGesture(m_souce_selected*3);
        repaint();
        return;
    }
    if(m_group_selected != -1)
    {
        if (m_drag_mode == 1)
        {
            m_sources_manager->groupSetRelativeRadius(m_group_selected, mouse.getDistanceFrom(Point<float>(0., 0.)) / m_sources_manager->getZoom());
        }
        else if(m_drag_mode == 2)
        {
            m_sources_manager->groupSetRelativeAngle(m_group_selected, mouse.getAngleToPoint(Point<float>(0., 0.)) + CICM_PI2);
        }
        else if(m_drag_mode == 3)
        {
            m_sources_manager->groupSetAbscissa(m_group_selected, mouse.getX() / m_sources_manager->getZoom());
        }
        else if(m_drag_mode == 4)
        {
            m_sources_manager->groupSetOrdinate(m_group_selected, mouse.getY() / m_sources_manager->getZoom());
        }
        else if(m_drag_mode == 5)
        {
            m_sources_manager->groupSetRelativePolar(m_group_selected, mouse.getDistanceFrom(Point<float>(0., 0.)) / m_sources_manager->getZoom(), mouse.getAngleToPoint(Point<float>(0., 0.)) + CICM_PI2);
        }
        else
        {
            m_sources_manager->groupSetCartesian(m_group_selected, mouse.getX() / m_sources_manager->getZoom(), mouse.getY() / m_sources_manager->getZoom());
        }
        repaint();
        return;
    }
    if(m_selected)
    {
        m_selection.setWidth(rect.getX() - m_selection.getX());
        m_selection.setHeight(rect.getY() - m_selection.getY());
        repaint();
    }    
}

void MapEditor::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    if(event.mods.isShiftDown())
    {
        m_sources_manager->setZoom(m_sources_manager->getZoom() + wheel.deltaY);
        repaint();
    }
}

void MapEditor::mouseUp(const MouseEvent &event)
{
    if(m_selected)
    {
        float center = getWidth() * 0.5;
        long groupIndex = m_sources_manager->groupGetNextIndex();
        for(int i = 0; i < m_sources_manager->getMaximumIndexOfSource(); i++)
        {
            if(m_sources_manager->sourceGetExistence(i))
            {
                float source_x = m_sources_manager->sourceGetAbscissa(i) * m_sources_manager->getZoom() * center + center;
                float source_y = -m_sources_manager->sourceGetOrdinate(i) * m_sources_manager->getZoom() * center + center;
                if(m_selection.contains(source_x, source_y))
                {
                    m_sources_manager->groupSetSource(groupIndex, i);
                }
            }
        }
        m_sources_manager->groupClean();
    }
    m_selected = 0;
    repaint();
}

void MapEditor::paint(Graphics& g)
{
    float center = getWidth() /2.;
    
    if(center / m_sources_manager->getZoom() > center / MIN_ZOOM * m_sources_manager->getZoom() - 5)
    {
        Path P;
        P.addCentredArc(center, center, center / MIN_ZOOM * m_sources_manager->getZoom() - 4, center / MIN_ZOOM * m_sources_manager->getZoom() - 4, 0, 0, CICM_2PI);
        g.strokePath(P, 1);
        P.clear();
        P.addCentredArc(center, center, center / MIN_ZOOM * m_sources_manager->getZoom() - 5, center / MIN_ZOOM * m_sources_manager->getZoom() - 5, 0, 0, CICM_2PI);
        g.reduceClipRegion (P, AffineTransform::identity);
    }
    
    draw_background(g);
    draw_sources(g);
    draw_groups(g);
    draw_selection(g);
}

void MapEditor::draw_background(Graphics& g)
{
    float center = getWidth() * 0.5;
    
    for(int i = 1; i <= 5; i++)
    {
        float width = center * (i / 5.) * m_sources_manager->getZoom();
        float start = center - width;
        g.setColour(Colours::white);
        g.drawEllipse(start + 0.5, start + 0.5, width * 2., width * 2., 2.);
        g.setColour(Colours::grey);
        g.drawEllipse(start, start, width * 2., width * 2., 1.);
    }
    
    float ecart = m_sources_manager->getZoom() * center;
    if(ecart < 10. && ecart >= 5.)
        ecart *= 2.;
    else if(ecart < 5. && ecart > 2.5)
        ecart *= 4.;
    else if(ecart < 2.5)
        ecart *= 8.;
    ecart = (int)ecart;
    
    for(float i = 0; i < center; i += ecart)
    {
        g.setColour(Colours::white);
        g.drawLine(0.5, center - i + 0.5, getWidth() + 0.5, center - i + 0.5, 2.);
        g.drawLine(0.5, center + i + 0.5, getWidth() + 0.5, center + i + 0.5, 2.);
        g.drawLine(center - i + 0.5, getWidth() - i + 0.5, center - i + 0.5, getWidth() + 0.5, 2.);
        g.drawLine(center + i + 0.5, getWidth() + i + 0.5, center + i + 0.5, getWidth() + 0.5, 2.);

        g.setColour(Colours::grey);
        g.drawLine(0., center - i, getWidth(), center - i, 1.);
        g.drawLine(0.,  center + i, getWidth(), center + i, 1.);
        g.drawLine(center - i,  0., center - i, getWidth(), 1.);
        g.drawLine(center + i,  0., center + i, getWidth(), 1.);
    }
}

void MapEditor::draw_sources(Graphics& g)
{
    float source_thickness = 1.;
    float center = getWidth() * 0.5;
    for(int i = 0; i < m_sources_manager->getMaximumIndexOfSource(); i++)
    {
        if(m_sources_manager->sourceGetExistence(i))
        {
            g.setColour(Colour(0xff444444));
            float source_x = m_sources_manager->sourceGetAbscissa(i) * m_sources_manager->getZoom() * center + center;
            float source_y = -m_sources_manager->sourceGetOrdinate(i) * m_sources_manager->getZoom() * center + center;
            
            g.fillEllipse(source_x - m_sources_size * 0.35, source_y - m_sources_size * 0.35, m_sources_size * 0.7, m_sources_size * 0.7);
            
            if (i == m_souce_selected)
            {
                source_thickness *= 1.5;
                for(int j = 0; j < m_sources_manager->sourceGetNumberOfGroups(i); j++)
                {
                    int group_index = m_sources_manager->sourceGetGroupIndex(i, j);
                    float group_x = m_sources_manager->groupGetAbscissa(group_index) * m_sources_manager->getZoom() * center + center;
                    float group_y = -m_sources_manager->groupGetOrdinate(group_index) * m_sources_manager->getZoom() * center + center;
                    g.drawLine(source_x, source_y, group_x, group_y);
                }
                
                g.setColour(Colour(0xff444444).withAlpha(0.5f));
                g.fillEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size, m_sources_size);
            }
            else
            {
                source_thickness = 1.;
            }            
            
            if(m_sources_manager->sourceGetMute(i))
            {
                g.setColour(Colours::red);
                g.drawEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size , m_sources_size, source_thickness);
                g.drawLine(source_x + Tools::abscissa(m_sources_size * 0.5, CICM_PI2 / 2.), source_y + Tools::ordinate(m_sources_size * 0.5, CICM_PI2 / 2.), source_x + Tools::abscissa(m_sources_size * 0.5, CICM_PI2 * 5. / 2.), source_y + Tools::ordinate(m_sources_size * 0.5, CICM_PI * 5. / 4.));
            }
            else
            {
                g.drawEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size , m_sources_size, source_thickness);
            }
            
            g.setFont(11);
            g.setColour(Colours::black);
            g.drawText(String(i+1), source_x - m_sources_size * 0.35, source_y - m_sources_size * 1.5,  m_sources_size, m_sources_size, Justification(4), FALSE);
        }
    }
}

void MapEditor::draw_groups(Graphics& g)
{
    float group_thickness = 1.;
    float center = getWidth() * 0.5;
    for(int i = 0; i < m_sources_manager->getMaximumIndexOfGroup(); i++)
    {
        if(m_sources_manager->groupGetExistence(i))
        {
            g.setColour(Colour(0xff444444));
            float group_x = m_sources_manager->groupGetAbscissa(i) * m_sources_manager->getZoom() * center + center;
            float group_y = -m_sources_manager->groupGetOrdinate(i) * m_sources_manager->getZoom() * center + center;
            
            g.fillEllipse(group_x - m_sources_size * 0.15, group_y - m_sources_size * 0.15, m_sources_size * 0.3, m_sources_size * 0.3);
            if (i == m_group_selected)
            {
                group_thickness *= 1.5;
                for(int j = 0; j < m_sources_manager->groupGetNumberOfSources(i); j++)
                {
                    int source_index = m_sources_manager->groupGetSourceIndex(i, j);
                    float source_x = m_sources_manager->sourceGetAbscissa(source_index) * m_sources_manager->getZoom() * center + center;
                    float source_y = -m_sources_manager->sourceGetOrdinate(source_index) * m_sources_manager->getZoom() * center + center;
                    g.drawLine(group_x, group_y, source_x, source_y);
                }
                
                g.setColour(Colour(0xff444444).withAlpha(0.5f));
                g.fillEllipse(group_x - m_sources_size * 0.5, group_y - m_sources_size * 0.5, m_sources_size, m_sources_size);
            }
            else
            {
                group_thickness = 1.;
            }
            
            if(m_sources_manager->groupGetMute(i))
            {
                g.setColour(Colours::red);
                g.drawEllipse(group_x - m_sources_size * 0.5, group_y - m_sources_size * 0.5, m_sources_size , m_sources_size, group_thickness);
                g.drawLine(group_x + Tools::abscissa(m_sources_size * 0.5, CICM_PI2 / 2.), group_y + Tools::ordinate(m_sources_size * 0.5, CICM_PI2 / 2.), group_x + Tools::abscissa(m_sources_size * 0.5, CICM_PI2 * 5. / 2.), group_y + Tools::ordinate(m_sources_size * 0.5, CICM_PI * 5. / 4.));
            }
            else
            {
                g.drawEllipse(group_x - m_sources_size * 0.5, group_y - m_sources_size * 0.5, m_sources_size , m_sources_size, group_thickness);
            }
            
            g.setFont(11);
            g.setColour(Colours::black);
            g.drawText(String(i+1), group_x - m_sources_size * 0.35, group_y - m_sources_size * 1.5,  m_sources_size, m_sources_size, Justification(4), FALSE);
        }
    }
}

void MapEditor::draw_selection(Graphics& g)
{
    if(m_selected)
    {
        float center = getWidth() * 0.5;
        g.setColour(Colour::fromFloatRGBA(0., 0., 1., 0.5));
        g.fillRect(m_selection);
        
        g.setColour(Colour::fromFloatRGBA(0., 1., 0., 0.5));
        for(int i = 0; i < m_sources_manager->getMaximumIndexOfSource(); i++)
        {
            if(m_sources_manager->sourceGetExistence(i))
            {
                float source_x = m_sources_manager->sourceGetAbscissa(i) * m_sources_manager->getZoom() * center + center;
                float source_y = -m_sources_manager->sourceGetOrdinate(i) * m_sources_manager->getZoom() * center + center;
                if(m_selection.contains(source_x, source_y))
                {                    
                    g.drawEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size , m_sources_size, 1.);
                }
            }
        }

    }
}


