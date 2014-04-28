/*
 // Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef _HOA_METER_COMPONENT_
#define _HOA_METER_COMPONENT_

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../Sources/HoaLibrary.h"
#include "../HoaComponent.h"

class HoaMeterComponent : public Component, public Timer
{
private:
    HoaComponentListener*   m_master;
    AmbisonicsMeter*    m_meter;
    int                 m_loudspeaker_selected;
    int                 m_loudspeaker_overflew;
    float               m_angle;
public:
    HoaMeterComponent(HoaComponentListener* master, AmbisonicsMeter * aMeter);
    ~HoaMeterComponent();
    
    void paint (Graphics&);
    void mouseMove(const MouseEvent &event);
    void mouseDown(const MouseEvent &event);
    void mouseDrag(const MouseEvent &event);
    void timerCallback();
};


#endif