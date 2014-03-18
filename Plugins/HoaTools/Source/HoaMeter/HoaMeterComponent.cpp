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
	
    Path P;
    float center  = getWidth() * 0.5;
    float led_width = 0.5 / 16. * getWidth();
    
    //m_processor->processEnergy();
    /*
    g.setColour(Colours::grey);
    g.drawEllipse(0.2 * getWidth(), 0.2 * getWidth(), 0.6 * getWidth(), 0.6 * getWidth(), getWidth() * 0.4);
    g.addTransform(AffineTransform::fromTargetPoints(-center, center, 0, 0, center, center, getWidth(), 0,  center, -center, getWidth(), getWidth()));
    
    for(int i = 0; i < m_processor->getNumberOfChannels(); i++)
    {
        float angle_start = m_processor->getChannelAzimuthMapped(i) - m_processor->getChannelWidth(i) / 2. + 0.025 * getWidth() / 498.;
        float angle_end   = m_processor->getChannelAzimuthMapped(i) + m_processor->getChannelWidth(i) / 2. - 0.025 * getWidth() / 498.;
        
        for(float j = 11, dB = -34.5; j > -2; j--, dB += 3.)
        {
            float center_x  = led_width * (2 - (j / 11.)) * cos(m_processor->getChannelAzimuthMapped(i));
            float center_y  = led_width * (2 - (j / 11.)) * sin(m_processor->getChannelAzimuthMapped(i));
            
            float radius    = (j + 3.33) * led_width;
            if(m_processor->getChannelEnergy(i) > dB)
            {
                if(j > 8)
                    g.setColour(Colours::green);
                else if(j > 5)
                    g.setColour(Colours::yellowgreen);
                else if(j > 2)
                    g.setColour(Colours::yellow);
                else if(j > -1)
                    g.setColour(Colours::orange);
                else
                    g.setColour(Colours::red);
                 P.addCentredArc(center_x, center_y, radius, radius, HOA_PI2, angle_start, angle_end, 1);
                
                g.strokePath(P, PathStrokeType(led_width - getWidth() / 166., PathStrokeType::mitered, PathStrokeType::rounded));
                P.clear();
            }
            else if(j != -1)
            {
                g.setColour(Colours::darkgrey);
                P.addCentredArc(center_x, center_y, radius, radius, HOA_PI2, angle_start, angle_end, 1);
                g.strokePath(P, PathStrokeType(led_width  - getWidth() / 166., PathStrokeType::mitered, PathStrokeType::rounded));
                P.clear();
            }
        }
    }
	*/
}

void HoaMeterComponent::mouseMove(const MouseEvent &event)
{
	;
}

void HoaMeterComponent::mouseDrag(const MouseEvent &event)
{
	;
}

