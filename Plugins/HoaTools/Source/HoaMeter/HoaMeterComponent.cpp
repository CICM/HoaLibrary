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
    
    if(m_processor->getNumberOfMeterChannels() != 1)
    {
        for(i = 0; i < m_processor->getNumberOfMeterChannels(); i++)
        {

            angle = m_processor->getChannelAzimuthMapped(i) - m_processor->getChannelWidth(i) * 0.5f;
            
            coso = cosf(angle);
            sino = sinf(angle);
            x1 = m_radius_center * coso;
            y1 = m_radius_center * sino;
            x2 = m_radius * coso;
            y2 = m_radius * sino;
            
            g.setColour(Colours::white);
            if(isInsideRad(angle, HOA_PI4, HOA_PI + HOA_PI4))
            {
                g.drawLine(x1 + m_center - 1., y1 + m_center - 1., x2 + m_center, y2 + m_center);
            }
            else
            {
                g.drawLine(x1 + m_center + 1., y1 + m_center + 1., x2 + m_center, y2 + m_center);
            }
            
            g.setColour(Colours::black);
            g.drawLine(x1 + m_center, y1 + m_center, x2 + m_center, y2 + m_center);
        }
    }
    
    g.setColour(Colours::white);
    g.drawEllipse((int)(m_center - m_radius + 1.), (int)(m_center - m_radius + 1.), m_radius * 2., m_radius * 2., 4.);
    g.drawEllipse((int)(m_center - m_radius_center + 1.), (int)(m_center - m_radius_center + 1.), m_radius_center * 2., m_radius_center * 2., 4.);
    
    g.setColour(Colours::black);
    g.drawEllipse((int)(m_center - m_radius), (int)(m_center - m_radius), m_radius * 2., m_radius * 2., 4.);
    g.drawEllipse((int)(m_center - m_radius_center), (int)(m_center - m_radius_center), m_radius_center * 2., m_radius_center * 2., 4.);
}

void HoaMeterComponent::draw_leds(Graphics& g)
{
    int i;
    float j, dB;
    float angle_start, angle, angle_end, radius, center_x, center_y;
    float led_width = 0.49 * getWidth() / 18.;
    float h = led_width * 17.;
   
	Path p;
    
    for(i = 0; i < m_processor->getNumberOfMeterChannels(); i++)
    {
        angle   = m_processor->getChannelAzimuthMapped(i) + HOA_PI2;
        
        center_x    = Hoa::abscissa(m_radius - h, angle);
        center_y    = -Hoa::ordinate(m_radius - h, angle);
        
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
                
                p.addCentredArc(center_x + getWidth() * 0.5f, center_y + getWidth() * 0.5f, radius, radius, HOA_2PI, angle_start, angle_end, 1);
                g.strokePath(p, PathStrokeType(3, PathStrokeType::mitered, PathStrokeType::rounded));
                p.clear();
            }
            else if(j != -1)
            {
                g.setColour(Colours::grey);
                p.addCentredArc(center_x + m_center, center_y + m_center, radius, radius, HOA_2PI, angle_start, angle_end, 1);
                g.strokePath(p, PathStrokeType(3, PathStrokeType::mitered, PathStrokeType::rounded));
                p.clear();
            }
        }
       /*
        if(x->f_over_leds[i])
        {
            radius    = (4.) * led_width;
            egraphics_set_color_rgba(g, &x->f_color_over_signal);
            egraphics_set_line_width(g, led_width - pd_clip_min(360. / getWidth(), 2.));
            egraphics_arc(g, center_x + getWidth() * 0.5f, center_y + getWidth() * 0.5f, radius, angle_start, angle_end);
            egraphics_stroke(g);
        }
        */
     
    }
};


void HoaMeterComponent::mouseMove(const MouseEvent &event)
{
	;
}

void HoaMeterComponent::mouseDrag(const MouseEvent &event)
{
	;
}



