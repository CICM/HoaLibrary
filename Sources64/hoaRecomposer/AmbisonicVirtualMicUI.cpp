/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot, Eliott Paris Universite Paris 8
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "AmbisonicVirtualMicUI.h"

AmbisonicVirtualMicUI::AmbisonicVirtualMicUI()
{
    m_angleInRadian = 0;
    m_distance = 1;
    m_isSelected = false;
}
AmbisonicVirtualMicUI::~AmbisonicVirtualMicUI()
{
    ;
}
void AmbisonicVirtualMicUI::setAngleInRadian(double _radian)
{
    m_angleInRadian = Tools::wrap(_radian, 0, CICM_2PI);
}

void AmbisonicVirtualMicUI::rotateAngleInRadian(double _deltaRadian)
{
    m_angleInRadian = Tools::wrap(m_angleInRadian + _deltaRadian, 0, CICM_2PI);
}

void AmbisonicVirtualMicUI::setSelected(int _selectedState)
{
    if (_selectedState == -1) // toggle Mode
        m_isSelected = !m_isSelected;
    else if(_selectedState == 1)
        m_isSelected = true;
    else
        m_isSelected = false;
}