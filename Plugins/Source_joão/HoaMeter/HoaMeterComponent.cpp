/*
 // Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */


#include "HoaMeterComponent.h"

HoaMeterComponent::HoaMeterComponent(HoaComponentListener* master, AmbisonicsMeter * aMeter)
{
    m_master = master;
    m_meter = aMeter;
    m_loudspeaker_selected = -1;
    m_loudspeaker_overflew = -1;
    startTimer(20);
}

HoaMeterComponent::~HoaMeterComponent()
{
    ;
}

void HoaMeterComponent::timerCallback()
{
    repaint();
}

void HoaMeterComponent::paint(Graphics& g)
{
    char index[256];
    float center  = getWidth() * 0.5;
    float circle_diameter = 20.f;
    g.setColour(Colours::grey);
    g.drawEllipse(0.2 * getWidth(), 0.2 * getWidth(), 0.6 * getWidth(), 0.6 * getWidth(), getWidth() * 0.4);
    
    
    for(int i = 0; i < m_meter->getNumberOfLoudspeakers(); i++)
    {
        float angle  = m_meter->getLoudspeakerAngleRadian(i);
        float x = center - center * cosf(angle - CICM_PI2);
        float y = getWidth() - (center - center * sinf(angle - CICM_PI2));
        
        if(i == m_loudspeaker_selected || i == m_loudspeaker_overflew)
            g.setColour(Colours::blue);
        else
            g.setColour(Colours::green);
        
        g.fillEllipse(x - circle_diameter * 0.5f, y - circle_diameter * 0.5f, circle_diameter, circle_diameter);
        
        g.setColour(Colours::black);
        sprintf(index, "%i", i+1);
        g.drawSingleLineText(index, x, y + circle_diameter * 0.25f, Justification::centred);
        
        sprintf(index, "%f", m_angle);
        g.drawSingleLineText(index, center, center, Justification::centred);
    }
}

void HoaMeterComponent::mouseMove(const MouseEvent &event)
{
    float center  = getWidth() * 0.5;
    float circle_diameter = 20.f;
    Point<float> loudspeaker;
    Point<float> mouse = event.getPosition().toFloat();

    
    m_loudspeaker_selected = -1;
    m_loudspeaker_overflew = -1;
    for(int i = 0; i < m_meter->getNumberOfLoudspeakers(); i++)
    {
        float angle  = m_meter->getLoudspeakerAngleRadian(i);
        loudspeaker.x = center - center * cosf(angle - CICM_PI2);
        loudspeaker.y = getWidth() - (center - center * sinf(angle - CICM_PI2));
    
        float distance = sqrt((loudspeaker.x - mouse.x) * (loudspeaker.x - mouse.x) + (loudspeaker.y - mouse.y) * (loudspeaker.y - mouse.y));
        if(distance <= circle_diameter * 0.5)
        {
            m_loudspeaker_overflew = i;
            setMouseCursor(MouseCursor::PointingHandCursor);
            repaint();
            return;
        }
    }
    setMouseCursor(MouseCursor::NormalCursor);
}

void HoaMeterComponent::mouseDown(const MouseEvent &event)
{
    if(getWidth() < 125)
    {
        m_master->componentHasBeenClicked(this);
    }
    else
    {
        float center  = getWidth() * 0.5;
        float circle_diameter = 20.f;
        Point<float> loudspeaker;
        Point<float> mouse = event.getPosition().toFloat();
        
        m_loudspeaker_selected = -1;
        m_loudspeaker_overflew = -1;
        for(int i = 0; i < m_meter->getNumberOfLoudspeakers(); i++)
        {
            float angle  = m_meter->getLoudspeakerAngleRadian(i);
            loudspeaker.x = center - center * cosf(angle - CICM_PI2);
            loudspeaker.y = getWidth() - (center - center * sinf(angle - CICM_PI2));
            
            float distance = sqrt((loudspeaker.x - mouse.x) * (loudspeaker.x - mouse.x) + (loudspeaker.y - mouse.y) * (loudspeaker.y - mouse.y));
            
            if(distance <= circle_diameter * 0.5)
            {
                m_loudspeaker_selected = i;
                setMouseCursor(MouseCursor::PointingHandCursor);
                repaint();
                return;
            }
        }
        setMouseCursor(MouseCursor::NormalCursor);
    }
}

void HoaMeterComponent::mouseDrag(const MouseEvent &event)
{
    int index;

    Point<float> mouse = event.getPosition().toFloat();
    Point<float> center;
    center.x = getWidth() * 0.5;
    center.y = getWidth() * 0.5;
    float angle_next, angle_new;

    mouse.y = getWidth() - mouse.y;
    angle_new = mouse.getAngleToPoint(center) / CICM_2PI * 360.;
    if(angle_new < 0)
        angle_new += 360.;
    
    
    if(m_loudspeaker_selected > -1)
    {
        index = m_loudspeaker_selected + 1;
        if(index > m_meter->getNumberOfLoudspeakers() - 1)
            index = 0;
        angle_next =  m_meter->getLoudspeakerAngleRadian(index) / CICM_2PI * 360.;
        if(angle_next < m_meter->getLoudspeakerAngleRadian(m_loudspeaker_selected))
            angle_next += CICM_2PI;
        if(angle_next <= angle_new)
        {
            m_loudspeaker_selected = index;
        }
        
        /*
        index = m_loudspeaker_selected - 1;
        if(index < 0)
            index = m_meter->getNumberOfLoudspeakers()- 1;
        angle_next =  m_meter->getLoudspeakerAngleRadian(index) / CICM_2PI * 360.;
        if(angle_next >= angle_new)
        {
            m_loudspeaker_selected = index;
            m_meter->setLoudspeakerAngleDegrees(m_loudspeaker_selected, angle_new);
            repaint();
            return;
        }
        */
        m_meter->setLoudspeakerAngleDegrees(m_loudspeaker_selected, angle_new);
        repaint();
    }
}






