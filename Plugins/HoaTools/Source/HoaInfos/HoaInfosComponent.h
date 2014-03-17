/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef _HOA_INFOS_COMPONENT_
#define _HOA_INFOS_COMPONENT_

#include <JuceHeader.h>
#include "PluginProcessor.h"

class HoaInfosComponent : public Component
{
private:
    HoaComponentListener*   m_master;
    

public:
    HoaInfosComponent(HoaComponentListener* master);
    ~HoaInfosComponent();
    
    void paint(Graphics&);
    void mouseDown(const MouseEvent &event);

};


#endif