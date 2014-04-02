/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef _HOA_LOGO_COMPONENT_
#define _HOA_LOGO_COMPONENT_

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class HoaLogoComponent : public Component
{
private:
    
    Image                   m_logo_icon;
    Label*                  m_logo_label;

public:
    HoaLogoComponent();
    ~HoaLogoComponent();
    
    void paint(Graphics&);
};


#endif