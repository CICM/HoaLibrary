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

AmbisonicVirtualMicUIManager::AmbisonicVirtualMicUIManager(long _numberOfMics)
{
    m_numberOfMics = _numberOfMics;
    setAngleInDegree(-1, 0);
}
AmbisonicVirtualMicUIManager::~AmbisonicVirtualMicUIManager()
{
    ;
}

void AmbisonicVirtualMicUIManager::setNumberOfMics(long _numberOfMicrophones)
{
    m_numberOfMics = Tools::clip(_numberOfMicrophones, long(0), long(MAX_MICS));
}

void AmbisonicVirtualMicUIManager::resetAngles(const int _index)
{
    double tempDegAngle = CICM_2PI / m_numberOfMics;
    
    if (_index == -1) // tous les angles
    {
        for (int i = 0; i < m_numberOfMics; i++)
            m_mic[i].setAngleInRadian(tempDegAngle*i);
    }
    else if (Tools::isInside(long(_index), long(0), long(m_numberOfMics)))
    {
        m_mic[_index].setAngleInRadian(tempDegAngle * _index);
    }
}

void AmbisonicVirtualMicUIManager::setAnglesInRadian(double* _radians, long _len)
{
    for (int i=0; i < _len && i < m_numberOfMics; i++) {
        m_mic[i].setAngleInRadian(_radians[i]);
    }
}
void AmbisonicVirtualMicUIManager::setAnglesInDegree(double* _degrees, long _len)
{
    for (int i=0; i < _len && i < m_numberOfMics; i++) {
        m_mic[i].setAngleInDegree(_degrees[i]);
    }
}

void AmbisonicVirtualMicUIManager::setAngleInRadian(const int _index, double _radian)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICS; i++)
            m_mic[i].setAngleInRadian(_radian);
    }
    else
    {
        m_mic[Tools::clip(_index, 0, MAX_MICS)].setAngleInRadian(_radian);
    }
}
void AmbisonicVirtualMicUIManager::setAngleInDegree(const int _index, double _degree)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICS; i++)
            m_mic[i].setAngleInDegree(_degree);
    }
    else
    {
        m_mic[Tools::clip(_index, 0, MAX_MICS)].setAngleInDegree(_degree);
    }
}
void AmbisonicVirtualMicUIManager::setDistance(const int _index, double _distance)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICS; i++)
            m_mic[i].setDistance(_distance);
    }
    else
    {
        m_mic[Tools::clip(_index, 0, MAX_MICS)].setDistance(_distance);
    }
}
void AmbisonicVirtualMicUIManager::setSelected(const int _index, int _selectedState)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICS; i++)
            m_mic[i].setSelected(_selectedState);
    }
    else
    {
        m_mic[Tools::clip(_index, 0, MAX_MICS)].setSelected(_selectedState);
    }
}

void AmbisonicVirtualMicUIManager::selectMicsBetweenMics(int _micIndex1, int _micIndex2)
{
    double angle1 = getAngleInRadian(_micIndex1);
    double angle2 = getAngleInRadian(_micIndex2);
    
    for (int i=0; i<MAX_MICS; i++) {
        if (Tools::isInside(getAngleInRadian(i), angle1, angle2)) {
            setSelected(i, 1);
        }
    }
}

void AmbisonicVirtualMicUIManager::rotateSelectedMicsWithRadian(double _newRadian, int _sourceBeingDragged)
{
    if (!Tools::isInside(_sourceBeingDragged, int(0), int(m_numberOfMics))) return;
    double deltaAngle = _newRadian - m_mic[_sourceBeingDragged].getAngleInRadian();
    m_mic[_sourceBeingDragged].setAngleInRadian(_newRadian);
    for (int i=0; i < m_numberOfMics; i++) {
        if (isSelected(i) && i != _sourceBeingDragged) {
            m_mic[i].rotateAngleInRadian(deltaAngle);
        }
    }
}




