/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaMapComponent.h"

#define MIN_ZOOM 0.05

/************************************************************************************/
/***************************** EDITOR ***********************************************/
/************************************************************************************/

HoaMapComponent::HoaMapComponent(HoaComponentListener* master, HoaToolsAudioProcessor* processor)
{
    m_processor         = processor;
	m_master			= master;
    m_souce_selected    = -1;
    m_group_selected    = -1;
    m_sources_size      = 15.;
    m_selected          = 0;
}

HoaMapComponent::~HoaMapComponent()
{
    ;
}

void HoaMapComponent::mouseMove(const MouseEvent &event)
{
    Point<float> point;
    Point<float> mouse = event.getPosition().toFloat();
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    m_selected          = 0;
    m_souce_selected    = -1;
    m_group_selected    = -1;
	
    for (int i = 0; i < m_processor->getMaximumIndexOfSource(); i++)
    {
        if(m_processor->sourceGetExistence(i))
        {
            point.setXY(m_processor->sourceGetAbscissa(i) * m_processor->getZoom(), m_processor->sourceGetOrdinate(i) * m_processor->getZoom());
            if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
            {
                m_souce_selected = i;
                setMouseCursor(MouseCursor::PointingHandCursor);
                repaint();
                return;
            }
        }
    }
    for (int i = 0; i < m_processor->getMaximumIndexOfGroup(); i++)
    {
        if(m_processor->groupGetExistence(i))
        {
            point.setXY(m_processor->groupGetAbscissa(i) * m_processor->getZoom(), m_processor->groupGetOrdinate(i) * m_processor->getZoom());
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


void HoaMapComponent::mouseDown(const MouseEvent &event)
{
	if(getWidth() < 125)
    {
        m_master->componentHasBeenClicked(this);
		return;
    }
	
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
    for (int i = 0; i < m_processor->getNumberOfSources(); i++)
    {
        point.setXY(m_processor->sourceGetAbscissa(i) * m_processor->getZoom(), m_processor->sourceGetOrdinate(i) * m_processor->getZoom());
        if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
        {
            if(event.mods.isRightButtonDown())
            {
                PopupMenu Popup;
                Popup.setLookAndFeel(&LookAndFeel);
                if(m_processor->sourceGetMute(i))
                    Popup.addItem(1, String("Unmute source"));
                else
                    Popup.addItem(1, String("Mute source"));
                
                const int choice = Popup.show();
                if(choice == 1)
                {
                    m_processor->beginParameterChangeGesture(i*3+3);
                    if(m_processor->sourceGetMute(i))
                        m_processor->sourceSetMute(i, 0);
                    else
                        m_processor->sourceSetMute(i, 1);
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
    
    for (int i = 0; i < m_processor->getMaximumIndexOfGroup(); i++)
    {
        if(m_processor->groupGetExistence(i))
        {
            point.setXY(m_processor->groupGetAbscissa(i) * m_processor->getZoom(), m_processor->groupGetOrdinate(i) * m_processor->getZoom());
            if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
            {
                if(event.mods.isRightButtonDown())
                {
                    PopupMenu Popup;
                    Popup.setLookAndFeel(&LookAndFeel);
                    Popup.addItem(1, String("Remove group"));
                    if(m_processor->groupGetMute(i) || m_processor->groupGetIfSourceMuted(i) == 1)
                        Popup.addItem(2, String("Unmute group"));
                    if(!m_processor->groupGetMute(i))
                        Popup.addItem(3, String("Mute group"));
                    
                    const int choice = Popup.show();
                    if(choice == 1)
                    {
                        m_processor->groupRemove(i);
                    }
                    else if(choice == 2)
                    {
                        for(int i = 0; i < m_processor->getNumberOfSources(); i++)
                            m_processor->beginParameterChangeGesture(i*3+3);
                        m_processor->groupSetMute(i, 0);
                        for(int i = 0; i < m_processor->getNumberOfSources(); i++)
                            m_processor->endParameterChangeGesture(i*3+3);
                    }
                    else if(choice == 3)
                    {
                        for(int i = 0; i < m_processor->getNumberOfSources(); i++)
                            m_processor->beginParameterChangeGesture(i*3+3);
                        m_processor->groupSetMute(i, 1);
                        for(int i = 0; i < m_processor->getNumberOfSources(); i++)
                            m_processor->endParameterChangeGesture(i*3+3);
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
    
    m_selected  = 1;
    m_selection.setPosition(rect);
    m_selection.setWidth(0);
    m_selection.setHeight(0);
    
    repaint();
    setMouseCursor(MouseCursor::NormalCursor);
}

void HoaMapComponent::mouseDrag(const MouseEvent &event)
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
            m_processor->sourceSetRadius(m_souce_selected, mouse.getDistanceFrom(Point<float>(0., 0.)) / m_processor->getZoom());
        }
        else if(m_drag_mode == 2)
        {
            m_processor->sourceSetAzimuth(m_souce_selected, mouse.getAngleToPoint(Point<float>(0., 0.)));
        }
        else if(m_drag_mode == 3)
        {
            m_processor->sourceSetAbscissa(m_souce_selected, mouse.getX() / m_processor->getZoom());
        }
        else if(m_drag_mode == 4)
        {
            m_processor->sourceSetOrdinate(m_souce_selected, mouse.getY() / m_processor->getZoom());
        }
        else
        {
            m_processor->sourceSetCartesian(m_souce_selected, mouse.getX() / m_processor->getZoom(), mouse.getY() / m_processor->getZoom());
        }
        m_processor->endParameterChangeGesture(m_souce_selected*3);
        repaint();
        return;
    }
    if(m_group_selected != -1)
    {
        if (m_drag_mode == 1)
        {
            m_processor->groupSetRelativeRadius(m_group_selected, mouse.getDistanceFrom(Point<float>(0., 0.)) / m_processor->getZoom());
        }
        else if(m_drag_mode == 2)
        {
            m_processor->groupSetRelativeAzimuth(m_group_selected, mouse.getAngleToPoint(Point<float>(0., 0.)) + HOA_PI2);
        }
        else if(m_drag_mode == 3)
        {
            m_processor->groupSetAbscissa(m_group_selected, mouse.getX() / m_processor->getZoom());
        }
        else if(m_drag_mode == 4)
        {
            m_processor->groupSetOrdinate(m_group_selected, mouse.getY() / m_processor->getZoom());
        }
        else if(m_drag_mode == 5)
        {
            m_processor->groupSetRelativePolar(m_group_selected, mouse.getDistanceFrom(Point<float>(0., 0.)) / m_processor->getZoom(), mouse.getAngleToPoint(Point<float>(0., 0.)) + HOA_PI2);
        }
        else
        {
            m_processor->groupSetCartesian(m_group_selected, mouse.getX() / m_processor->getZoom(), mouse.getY() / m_processor->getZoom());
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

void HoaMapComponent::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    if(event.mods.isShiftDown())
    {
        m_processor->setZoom(m_processor->getZoom() + wheel.deltaY);
        repaint();
    }
}

void HoaMapComponent::mouseUp(const MouseEvent &event)
{
    if(m_selected)
    {
        float center = getWidth() * 0.5;
        long groupIndex = m_processor->groupGetNextIndex();
        for(int i = 0; i < m_processor->getMaximumIndexOfSource(); i++)
        {
            if(m_processor->sourceGetExistence(i))
            {
                float source_x = m_processor->sourceGetAbscissa(i) * m_processor->getZoom() * center + center;
                float source_y = -m_processor->sourceGetOrdinate(i) * m_processor->getZoom() * center + center;
                if(m_selection.contains(source_x, source_y))
                {
                    m_processor->groupSetSource(groupIndex, i);
                }
            }
        }
        m_processor->groupClean();
    }
    m_selected = 0;
    repaint();
}

void HoaMapComponent::paint(Graphics& g)
{
    float center = getWidth() /2.;
    
    if(center / m_processor->getZoom() > center / MIN_ZOOM * m_processor->getZoom() - 5)
    {
		Path P;
		PathStrokeType pathStrokeType = PathStrokeType(1);
        P.addCentredArc(center, center, center / MIN_ZOOM * m_processor->getZoom() - 4, center / MIN_ZOOM * m_processor->getZoom() - 4, 0, 0, HOA_2PI);
        g.strokePath(P, pathStrokeType);
        P.clear();
        P.addCentredArc(center, center, center / MIN_ZOOM * m_processor->getZoom() - 5, center / MIN_ZOOM * m_processor->getZoom() - 5, 0, 0, HOA_2PI);
        g.reduceClipRegion (P, AffineTransform::identity);
    }
    
    draw_background(g);
    draw_sources(g);
    draw_groups(g);
    draw_selection(g);
}

void HoaMapComponent::draw_background(Graphics& g)
{
    float center = getWidth() * 0.5;
    
    for(int i = 1; i <= 5; i++)
    {
        float width = center * (i / 5.) * m_processor->getZoom();
        float start = center - width;
        g.setColour(Colours::white);
        g.drawEllipse(start + 0.5, start + 0.5, width * 2., width * 2., 2.);
        g.setColour(Colours::grey);
        g.drawEllipse(start, start, width * 2., width * 2., 1.);
    }
    
    float ecart = m_processor->getZoom() * center;
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

void HoaMapComponent::draw_sources(Graphics& g)
{
    float source_thickness = 1.;
    float center = getWidth() * 0.5;
    for(int i = 0; i < m_processor->getNumberOfSources(); i++)
    {
        g.setColour(Colour(0xff444444));
        float source_x = m_processor->sourceGetAbscissa(i) * m_processor->getZoom() * center + center;
        float source_y = -m_processor->sourceGetOrdinate(i) * m_processor->getZoom() * center + center;
        
        g.fillEllipse(source_x - m_sources_size * 0.35, source_y - m_sources_size * 0.35, m_sources_size * 0.7, m_sources_size * 0.7);
        
        if (i == m_souce_selected)
        {
            source_thickness *= 1.5;
            for(int j = 0; j < m_processor->sourceGetNumberOfGroups(i); j++)
            {
                int group_index = m_processor->sourceGetGroupIndex(i, j);
                float group_x = m_processor->groupGetAbscissa(group_index) * m_processor->getZoom() * center + center;
                float group_y = -m_processor->groupGetOrdinate(group_index) * m_processor->getZoom() * center + center;
                g.drawLine(source_x, source_y, group_x, group_y);
            }
            
            g.setColour(Colour(0xff444444).withAlpha(0.5f));
            g.fillEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size, m_sources_size);
        }
        else
        {
            source_thickness = 1.;
        }
        
        if(m_processor->sourceGetMute(i))
        {
            g.setColour(Colours::red);
            g.drawEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size , m_sources_size, source_thickness);
            g.drawLine(source_x + abscissa(m_sources_size * 0.5, HOA_PI2 / 2.), source_y + ordinate(m_sources_size * 0.5, HOA_PI2 / 2.), source_x + abscissa(m_sources_size * 0.5, HOA_PI2 * 5. / 2.), source_y + ordinate(m_sources_size * 0.5, HOA_PI * 5. / 4.));
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

void HoaMapComponent::draw_groups(Graphics& g)
{
    float group_thickness = 1.;
    float center = getWidth() * 0.5;
    for(int i = 0; i < m_processor->getMaximumIndexOfGroup(); i++)
    {
        if(m_processor->groupGetExistence(i))
        {
            g.setColour(Colour(0xff444444));
            float group_x = m_processor->groupGetAbscissa(i) * m_processor->getZoom() * center + center;
            float group_y = -m_processor->groupGetOrdinate(i) * m_processor->getZoom() * center + center;
            
            g.fillEllipse(group_x - m_sources_size * 0.15, group_y - m_sources_size * 0.15, m_sources_size * 0.3, m_sources_size * 0.3);
            if (i == m_group_selected)
            {
                group_thickness *= 1.5;
                for(int j = 0; j < m_processor->groupGetNumberOfSources(i); j++)
                {
                    int source_index = m_processor->groupGetSourceIndex(i, j);
                    float source_x = m_processor->sourceGetAbscissa(source_index) * m_processor->getZoom() * center + center;
                    float source_y = -m_processor->sourceGetOrdinate(source_index) * m_processor->getZoom() * center + center;
                    g.drawLine(group_x, group_y, source_x, source_y);
                }
                
                g.setColour(Colour(0xff444444).withAlpha(0.5f));
                g.fillEllipse(group_x - m_sources_size * 0.5, group_y - m_sources_size * 0.5, m_sources_size, m_sources_size);
            }
            else
            {
                group_thickness = 1.;
            }
            
            if(m_processor->groupGetMute(i))
            {
                g.setColour(Colours::red);
                g.drawEllipse(group_x - m_sources_size * 0.5, group_y - m_sources_size * 0.5, m_sources_size , m_sources_size, group_thickness);
                g.drawLine(group_x + abscissa(m_sources_size * 0.5, HOA_PI2 / 2.), group_y + ordinate(m_sources_size * 0.5, HOA_PI2 / 2.), group_x + abscissa(m_sources_size * 0.5, HOA_PI2 * 5. / 2.), group_y + ordinate(m_sources_size * 0.5, HOA_PI * 5. / 4.));
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

void HoaMapComponent::draw_selection(Graphics& g)
{
    if(m_selected)
    {
        float center = getWidth() * 0.5;
        g.setColour(Colour::fromFloatRGBA(0., 0., 1., 0.5));
        g.fillRect(m_selection);
        
        g.setColour(Colour::fromFloatRGBA(0., 1., 0., 0.5));
        for(int i = 0; i < m_processor->getMaximumIndexOfSource(); i++)
        {
            if(m_processor->sourceGetExistence(i))
            {
                float source_x = m_processor->sourceGetAbscissa(i) * m_processor->getZoom() * center + center;
                float source_y = -m_processor->sourceGetOrdinate(i) * m_processor->getZoom() * center + center;
                if(m_selection.contains(source_x, source_y))
                {                    
                    g.drawEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size , m_sources_size, 1.);
                }
            }
        }

    }
}


