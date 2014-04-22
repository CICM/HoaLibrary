/*
 // Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "HoaMapComponent.h"

#define MIN_ZOOM 0.05

HoaMapComponent::HoaMapComponent(HoaComponentListener* master, HoaProcessor* processor)
{
    m_master    = master;
    m_processor = processor;
}


HoaMapComponent::~HoaMapComponent()
{
    ;
}

void HoaMapComponent::mouseDown(const MouseEvent &event)
{
    if(getWidth() < 125)
    {
        m_master->componentHasBeenClicked(this);
    }
    else
    {
        
    }
}



