/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaLogoComponent.h"

HoaLogoComponent::HoaLogoComponent()
{
    ;
}

HoaLogoComponent::~HoaLogoComponent()
{
    ;
}

void HoaLogoComponent::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawText("HOA", 0, 0, getWidth() * 0.75, getWidth() * 0.75, Justification::centred, 0);
}



