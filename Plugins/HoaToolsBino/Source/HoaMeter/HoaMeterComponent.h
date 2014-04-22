/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __HOA_DECODER_PLUGIN__
#define __HOA_DECODER_PLUGIN__

#include <JuceHeader.h>
#include "../../../Sources/Hoa2D/Hoa2D.h"
#include "PluginProcessor.h"

class HoaMeterComponent : public Component, public Timer
{
    
private:
	HoaToolsAudioProcessor* m_processor;
	HoaComponentListener*	m_master;

    double                  m_center;
    double                  m_radius;
    double                  m_radius_center;
    
    
    void draw_background(Graphics& g);
    void draw_leds(Graphics& g);
    
public:
    HoaMeterComponent(HoaComponentListener* master, HoaToolsAudioProcessor* processor);
    ~HoaMeterComponent();
    
    void paint (Graphics&);
    void mouseDown(const MouseEvent &event);
    void timerCallback();
};


#endif