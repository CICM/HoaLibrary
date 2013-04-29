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

#include "AmbisonicVirtualMicUIManager.h"

AmbisonicVirtualMicUIManager::AmbisonicVirtualMicUIManager()
{
    ;
}
AmbisonicVirtualMicUIManager::~AmbisonicVirtualMicUIManager()
{
    ;
}

void AmbisonicVirtualMicUIManager::setAnglesInRadian(double* _radians, long _len)
{
    ;
}
void AmbisonicVirtualMicUIManager::setAnglesInDegree(double* _radians, long _len)
{
    ;
}

void AmbisonicVirtualMicUIManager::setAngleInRadian(const int _index, double _radian)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICROPHONES; i++)
            m_mic[i].setAngleInRadian(_radian);
    }
    else
    {
        m_mic[Tools::clip(_index, 0, MAX_MICROPHONES)].setAngleInRadian(_radian);
    }
}
void AmbisonicVirtualMicUIManager::setAngleInDegree(const int _index, double _degree)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICROPHONES; i++)
            m_mic[i].setAngleInDegree(_degree);
    }
    else
    {
        m_mic[Tools::clip(_index, 0, MAX_MICROPHONES)].setAngleInDegree(_degree);
    }
}
void AmbisonicVirtualMicUIManager::setDistance(const int _index, double _distance)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICROPHONES; i++)
            m_mic[i].setDistance(_distance);
    }
    else
    {
        m_mic[Tools::clip(_index, 0, MAX_MICROPHONES)].setDistance(_distance);
    }
}
void AmbisonicVirtualMicUIManager::setSelected(const int _index, bool _selectedState)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICROPHONES; i++)
            m_mic[i].setSelected(_selectedState);
    }
    else
    {
        m_mic[Tools::clip(_index, 0, MAX_MICROPHONES)].setSelected(_selectedState);
    }
}