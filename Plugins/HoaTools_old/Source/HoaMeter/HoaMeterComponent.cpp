/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaMeterComponent.h"

/************************************************************************************/
/***************************** EDITOR ***********************************************/
/************************************************************************************/

HoaMeterComponent::HoaMeterComponent(HoaComponentListener* master, HoaToolsAudioProcessor* processor)
{
	m_master = master;
    m_processor = processor;
    startTimer(20);
}

HoaMeterComponent::~HoaMeterComponent()
{
    ;
}

void HoaMeterComponent::mouseDown(const MouseEvent &event)
{
    if(getWidth() < 125)
    {
        m_master->componentHasBeenClicked(this);
		return;
    }
}

void HoaMeterComponent::timerCallback()
{
    repaint();
}

void HoaMeterComponent::paint(Graphics& g)
{
    m_center = getWidth() * .5;
	m_radius = m_center * 0.95;
	m_radius_center = m_radius / 5.;

	draw_background(g);
    draw_leds(g);
}

void HoaMeterComponent::draw_background(Graphics& g)
{
    int i;
    float coso, sino, angle, x1, y1, x2, y2;
    float thickness  = 3;
    if(getWidth() < PLUG_MENU_WIDTH)
        thickness = 1;
    if(m_processor->getNumberOfChannels() != 1)
    {
        for(i = 0; i < m_processor->getNumberOfChannels(); i++)
        {
            angle = m_processor->getChannelAzimuthMapped(i) - m_processor->getChannelWidth(i) * 0.5f;
            
            coso = cosf(angle - HOA_PI2);
            sino = sinf(angle - HOA_PI2);
            x1 = m_radius_center * coso;
            y1 = m_radius_center * sino;
            x2 = m_radius * coso;
            y2 = m_radius * sino;
            
            g.setColour(Colours::black);
            g.drawLine(x1 + m_center, y1 + m_center, x2 + m_center, y2 + m_center, thickness);
        }
    }
    
    g.setColour(Colours::black);
    g.drawEllipse((int)(m_center - m_radius), (int)(m_center - m_radius), m_radius * 2., m_radius * 2., thickness);
    g.drawEllipse((int)(m_center - m_radius_center), (int)(m_center - m_radius_center), m_radius_center * 2., m_radius_center * 2., thickness);
}

void HoaMeterComponent::draw_leds(Graphics& g)
{
    int i;
    float j, dB;
    float angle_start, angle, angle_end, radius, center_x, center_y;
    float led_width = 0.49 * getWidth() / 18.;
    float h = led_width * 18.;
    float thickness  = led_width - 2;
    if(getWidth() < PLUG_MENU_WIDTH)
        thickness = led_width - 1;
    
	Path p;
    
    for(i = 0; i < m_processor->getNumberOfChannels(); i++)
    {
        angle   = -m_processor->getChannelAzimuthMapped(i) ;
        
        center_x    = Hoa::abscissa(m_radius - h, angle);
        center_y    = Hoa::ordinate(m_radius - h, angle);
        
        angle_start = angle - m_processor->getChannelWidth(i) * 0.5f;
        angle_end   = angle + m_processor->getChannelWidth(i) * 0.5f;
        
        
        for(j = 11, dB = -34.5; j > -1; j--, dB += 3.)
        {
            radius    = (j + 5.) * led_width;
            if(m_processor->getChannelEnergy(i) > dB)
            {
                if(j > 8)
                    g.setColour(Colours::green);
                else if(j > 5)
                    g.setColour(Colours::greenyellow);
                else if(j > 2)
                    g.setColour(Colours::yellow);
                else
                    g.setColour(Colours::orange);
                
                p.addCentredArc(center_x + m_center, center_y + m_center, radius, radius, HOA_2PI, angle_start, angle_end, 1);
                g.strokePath(p, PathStrokeType(thickness, PathStrokeType::beveled, PathStrokeType::butt));
                p.clear();
            }
            else if(j != -1)
            {
                g.setColour(Colours::grey);
                p.addCentredArc(center_x + m_center, center_y + m_center, radius, radius, HOA_2PI, angle_start, angle_end, 1);
                g.strokePath(p, PathStrokeType(thickness, PathStrokeType::beveled, PathStrokeType::butt));
                p.clear();
            }
        }     
    }
};



