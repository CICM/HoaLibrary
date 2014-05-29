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

HoaMapComponent::HoaMapComponent(AudioProcessorEditor* master, HoaToolsAudioProcessor* processor)
{
    m_processor         = processor;
    m_sources           = m_processor->getSources();
	m_master			= master;
    m_source_selected   = -1;
    m_sources_size      = 15.;
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
    
    m_source_selected   = -1;
    for (int i = 0; i < m_sources->getNumberOfSources(); i++)
    {
        if(m_sources->sourceGetExistence(i))
        {
            point.setXY(m_sources->sourceGetAbscissa(i) * m_sources->getZoom(), m_sources->sourceGetOrdinate(i) * m_sources->getZoom());
            if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
            {
                m_source_selected = i;
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
    Point<float> point;
    Point<float> mouse = event.getPosition().toFloat();
    Point<float> rect  = mouse;
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    m_source_selected   = -1;
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
    for (int i = 0; i < m_sources->getNumberOfSources(); i++)
    {
        point.setXY(m_sources->sourceGetAbscissa(i) * m_sources->getZoom(), m_sources->sourceGetOrdinate(i) * m_sources->getZoom());
        if(mouse.getDistanceFrom(point) < m_sources_size * 0.002)
        {
            m_source_selected = i;
            setMouseCursor(MouseCursor::PointingHandCursor);
            repaint();
            return;
        }
    }
    
    repaint();
    setMouseCursor(MouseCursor::NormalCursor);
}

void HoaMapComponent::mouseDrag(const MouseEvent &event)
{    
    Point<float> source;
    Point<float> mouse = event.getPosition().toFloat();
    Point<float> rect  = mouse;
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    if(m_source_selected != -1)
    {
        m_processor->beginParameterChangeGesture(m_source_selected*3);
        m_processor->beginParameterChangeGesture(m_source_selected*3+1);
        
        if (m_drag_mode == 1)
        {
            m_sources->sourceSetRadius(m_source_selected, mouse.getDistanceFrom(Point<float>(0., 0.)) / m_sources->getZoom());
        }
        else if(m_drag_mode == 2)
        {
            m_sources->sourceSetAzimuth(m_source_selected, mouse.getAngleToPoint(Point<float>(0., 0.)));
        }
        else if(m_drag_mode == 3)
        {
            m_sources->sourceSetAbscissa(m_source_selected, mouse.getX() / m_sources->getZoom());
        }
        else if(m_drag_mode == 4)
        {
            m_sources->sourceSetOrdinate(m_source_selected, mouse.getY() / m_sources->getZoom());
        }
        else
        {
            m_sources->sourceSetCartesian(m_source_selected, mouse.getX() / m_sources->getZoom(), mouse.getY() / m_sources->getZoom());
        }
        
        m_processor->endParameterChangeGesture(m_source_selected*3);
        m_processor->endParameterChangeGesture(m_source_selected*3+1);
        repaint();
        return;
    }

}

void HoaMapComponent::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    if(event.mods.isShiftDown())
    {
        m_sources->setZoom(m_sources->getZoom() + wheel.deltaY);
        repaint();
    }
}

void HoaMapComponent::paint(Graphics& g)
{
    float center = getWidth() /2.;
    
    Path P;
    P.addCentredArc(center, center, center - 4, center - 4, 0, 0, HOA_2PI, 1);
    g.strokePath(P, PathStrokeType(1));
    P.clear();
    P.addCentredArc(center, center, center - 5, center - 5, 0, 0, HOA_2PI, 1);
    g.reduceClipRegion (P, AffineTransform::identity);
    
    draw_background(g);
    draw_sources(g);
}

void HoaMapComponent::draw_background(Graphics& g)
{
    float center = getWidth() * 0.5;
    
    float ecart = m_sources->getZoom() * center;
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
    
    for(int i = 1; i <= 5; i++)
    {
        float width = center * (i / 5.) * m_sources->getZoom();
        float start = center - width;
        g.setColour(Colours::white);
        g.drawEllipse(start + 4.5, start + 4.5, width * 2. -8, width * 2. - 8, 2.);
        g.setColour(Colours::grey);
        g.drawEllipse(start+4, start+4, width * 2. -8, width * 2. -8, 1.);
    }
}

void HoaMapComponent::draw_sources(Graphics& g)
{
    float source_thickness = 1.;
    float center = getWidth() * 0.5;
    for(int i = 0; i < m_sources->getNumberOfSources(); i++)
    {
        if(!m_sources->sourceGetMute(i))
        {
            g.setColour(Colour(0xff444444));
            float source_x = m_sources->sourceGetAbscissa(i) * m_sources->getZoom() * center + center;
            float source_y = -m_sources->sourceGetOrdinate(i) * m_sources->getZoom() * center + center;
            
            g.fillEllipse(source_x - m_sources_size * 0.35, source_y - m_sources_size * 0.35, m_sources_size * 0.7, m_sources_size * 0.7);
            
            if(i == m_source_selected)
            {
                source_thickness *= 1.5;
                for(int j = 0; j < m_sources->sourceGetNumberOfGroups(i); j++)
                {
                    int group_index = m_sources->sourceGetGroupIndex(i, j);
                    float group_x = m_sources->groupGetAbscissa(group_index) * m_sources->getZoom() * center + center;
                    float group_y = -m_sources->groupGetOrdinate(group_index) * m_sources->getZoom() * center + center;
                    g.drawLine(source_x, source_y, group_x, group_y);
                }
                
                g.setColour(Colour(0xff444444).withAlpha(0.5f));
                g.fillEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size, m_sources_size);
            }
            else
            {
                source_thickness = 1.;
            }
            
            g.drawEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size , m_sources_size, source_thickness);
            
            g.setFont(11);
            g.setColour(Colours::black);
            g.drawText(String(i+1), source_x - m_sources_size * 0.35, source_y - m_sources_size * 1.5,  m_sources_size, m_sources_size, Justification(4), false);
        }
    }
}


