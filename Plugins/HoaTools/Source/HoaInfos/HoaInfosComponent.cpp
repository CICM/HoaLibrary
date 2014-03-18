/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaInfosComponent.h"

static char hoa_infos_label[] = "Infos";

static char hoa_infos_text[] = "HOA Library allows musicians and composers to synthesize, transform and render sound fields in a creative and artistic way. This library facilitates the understanding and the appropriation of key concepts of ambisonics. Thanks to original graphical interfaces a lot of new signal processing are allowed like diffuse sound field synthesis, perspective distorsion or spatial filtering";

HoaInfosComponent::HoaInfosComponent(HoaComponentListener* master)
{
    m_master = master;
}

HoaInfosComponent::~HoaInfosComponent()
{
    ;
}

void HoaInfosComponent::mouseDown(const MouseEvent &event)
{
    if(getWidth() < 125)
    {
        m_master->componentHasBeenClicked(this);
		return;
    }
    else
    {
        
    }
}

void HoaInfosComponent::paint(Graphics& g)
{
    g.setColour(Colours::black);
    if(getWidth() < 125)
        g.drawText(hoa_infos_label, 0, 0, getWidth(), getWidth(), Justification::centred, 0);
    else
        g.drawText(hoa_infos_text, 0, 0, getWidth(), getWidth(), Justification::centred, 0);
}




