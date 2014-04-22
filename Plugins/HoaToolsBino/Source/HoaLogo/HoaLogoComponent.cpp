/*
// Copyright (c) 2012-2014 Eliott Paris, João Svidzinski & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "HoaLogoComponent.h"

HoaLogoComponent::HoaLogoComponent()
{
    m_logo_icon = ImageCache::getFromMemory(BinaryData::hoa_icon_02_transp_png, BinaryData::hoa_icon_02_transp_pngSize);
}

HoaLogoComponent::~HoaLogoComponent()
{
    ;
}

void HoaLogoComponent::paint(Graphics& g)
{
    g.drawImage(m_logo_icon, 0, 0, PLUG_MENU_WIDTH, PLUG_MENU_WIDTH, 0, 0, m_logo_icon.getWidth(), m_logo_icon.getHeight());
}



