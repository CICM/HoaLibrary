/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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
    m_defaultAngles = NULL;
    setNumberOfMics(_numberOfMics);
    setDefaultAngles();
    resetAngles(-1);
}
AmbisonicVirtualMicUIManager::~AmbisonicVirtualMicUIManager()
{
    if (m_defaultAngles) delete m_defaultAngles;
}

void AmbisonicVirtualMicUIManager::setNumberOfMics(long _numberOfMicrophones)
{
    m_numberOfMics = Tools::clip(_numberOfMicrophones, long(MIN_MICS), long(MAX_MICS));
    
    long order = 0;
    if (m_numberOfMics%2 == 0)
        order = m_numberOfMics*0.5-1;
    else
        order = m_numberOfMics*0.5;
    
    for (int i = 0; i < m_numberOfMics; i++)
        m_mic[i].setOrder(order);
    
    setDefaultAngles();
}

void AmbisonicVirtualMicUIManager::setDefaultAngles()
{
    if (m_defaultAngles) delete m_defaultAngles;
    m_defaultAngles = new double[m_numberOfMics];
    m_distanceBetweenTwoDefMics = CICM_2PI / m_numberOfMics;
    for (int i = 0; i < m_numberOfMics; i++)
        m_defaultAngles[i] = m_distanceBetweenTwoDefMics*i;
}

void AmbisonicVirtualMicUIManager::resetAngles(const int _index)
{    
    if (_index == -1) // tous les angles
    {
        for (int i = 0; i < m_numberOfMics; i++)
            m_mic[i].setAngleInRadian(m_defaultAngles[i]);
    }
    else if (Tools::isInside(long(_index), long(0), long(m_numberOfMics)))
        m_mic[_index].setAngleInRadian(m_defaultAngles[_index]);
}

void AmbisonicVirtualMicUIManager::resetWides(const int _index)
{
    if (_index == -1) // tous les angles
    {
        for (int i = 0; i < m_numberOfMics; i++)
            m_mic[i].setWiderValue(1);
    }
    else if (Tools::isInside(long(_index), long(0), long(m_numberOfMics)))
        m_mic[_index].setWiderValue(1);
}

void AmbisonicVirtualMicUIManager::setAnglesInRadian(double* _radians, long _len)
{
    for (int i=0; i < _len && i < m_numberOfMics; i++)
        m_mic[i].setAngleInRadian(_radians[i]);
}
void AmbisonicVirtualMicUIManager::setAnglesInDegree(double* _degrees, long _len)
{
    for (int i=0; i < _len && i < m_numberOfMics; i++)
        m_mic[i].setAngleInDegree(_degrees[i]);
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
        m_mic[(int)Tools::clip(_index, 0, MAX_MICS)].setAngleInRadian(_radian);
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
        m_mic[(int)Tools::clip(_index, 0, MAX_MICS)].setAngleInDegree(_degree);
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
        m_mic[(int)Tools::clip(_index, 0, MAX_MICS)].setDistance(_distance);
    }
}

void AmbisonicVirtualMicUIManager::setWiderValues(double* _widerValues, long _len)
{
    for (int i=0; i < _len && i < m_numberOfMics; i++) {
        m_mic[i].setWiderValue(_widerValues[i]);
    }
}

void AmbisonicVirtualMicUIManager::setWiderValue(const int _index, double _widerValue)
{
    if (_index == -1)
    {
        for (int i=0; i<MAX_MICS; i++)
            m_mic[i].setWiderValue(_widerValue);
    }
    else
    {
        m_mic[(int)Tools::clip(_index, 0, MAX_MICS)].setWiderValue(_widerValue);
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
        m_mic[(int)Tools::clip(_index, 0, MAX_MICS)].setSelected(_selectedState);
    }
}

void AmbisonicVirtualMicUIManager::selectMicsBetweenMics(int _micIndex1, int _micIndex2)
{
    double angle1 = getAngleInRadian(_micIndex1);
    double angle2 = getAngleInRadian(_micIndex2);
    
    for (int i=0; i<MAX_MICS; i++) {
        if (Tools::isInsideRad(getAngleInRadian(i), angle1, angle2)) {
            setSelected(i, 1);
        }
    }
}

void AmbisonicVirtualMicUIManager::rotateSelectedMicsWithRadian(double _newRadian, int _sourceBeingDragged, int magnet)
{
    if (!Tools::isInside(_sourceBeingDragged, int(0), int(m_numberOfMics))) return;
    
    double deltaAngle;
    double oldAngle = m_mic[_sourceBeingDragged].getAngleInRadian();
    deltaAngle = _newRadian - m_mic[_sourceBeingDragged].getAngleInRadian();
    m_mic[_sourceBeingDragged].setAngleInRadian(_newRadian);
    
    if (magnet == 1)
    {
        if ( getClosestDefMicDistance(_sourceBeingDragged) < m_distanceBetweenTwoDefMics*0.1 )
        {
            m_mic[_sourceBeingDragged].setAngleInRadian(getClosestDefMicAngle(_sourceBeingDragged));
            deltaAngle =  m_mic[_sourceBeingDragged].getAngleInRadian() - oldAngle;
        }
    }
    
    for (int i=0; i < m_numberOfMics; i++)
        if (isSelected(i) && i != _sourceBeingDragged)
            m_mic[i].rotateAngleInRadian(deltaAngle);
}

/*
void AmbisonicVirtualMicUIManager::rotateSelectedMicsWithRadian(double _newRadian, int _sourceBeingDragged, int magnet)
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
*/

void AmbisonicVirtualMicUIManager::setSelectedMicsWiderValueWithRadiusDelta(double deltaRadius)
{
    for (int i=0; i < m_numberOfMics; i++) {
        if (isSelected(i)) {
            m_mic[i].setWiderValue( m_mic[i].getWiderValue() + deltaRadius);
        }
    }
}

/* ---- Fisheye ---- */

void AmbisonicVirtualMicUIManager::setFisheyeDestAngle(double _angleInRadian)
{
    m_fisheyeDestAngleInRadian = Tools::radian_wrap(_angleInRadian);
    m_fisheyeStep = 0;
}

void AmbisonicVirtualMicUIManager::setSelectedMicsFisheyeStepWithDelta(const int _micIndex, double _delta)
{
    m_fisheyeStep = Tools::clip(m_fisheyeStep + _delta, double(0), double(1));
    setFisheyeStepDirect(_micIndex, m_fisheyeStep);
}

void AmbisonicVirtualMicUIManager::setFisheyeStepDirect(const int _micIndex, double _fisheyeStep)
{
    int index = safeIndex(_micIndex);
    m_fisheyeStep = Tools::clip(_fisheyeStep, double(0), double(1));
    if (_micIndex == -2)
    {
        for (int i=0; i < m_numberOfMics; i++)
            if (isSelected(i))
                m_mic[i].setAngleInRadian(radianInterp(m_fisheyeStep, m_mic[i].getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
    }
    else if (_micIndex == -1)
    {
        for (int i=0; i < m_numberOfMics; i++)
            m_mic[i].setAngleInRadian(radianInterp(m_fisheyeStep, m_mic[i].getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
    }
    else
        m_mic[index].setAngleInRadian(radianInterp(m_fisheyeStep, m_mic[index].getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
}

void AmbisonicVirtualMicUIManager::setFisheyeStartAngle(const int _micIndex)
{
    if (_micIndex == -2)
    {
        for (int i=0; i < m_numberOfMics; i++)
            if (isSelected(i))
                m_mic[i].setFisheyeStartAngle();
    }
    else if (_micIndex == -1)
    {
        for (int i=0; i<MAX_MICS; i++)
            m_mic[i].setFisheyeStartAngle();
    }
    else
        m_mic[(int)Tools::clip(_micIndex, 0, MAX_MICS)].setFisheyeStartAngle();
}

void AmbisonicVirtualMicUIManager::setFisheyeStartAngle(const int _micIndex, double _radian)
{
    if (_micIndex == -2) {
        for (int i=0; i < m_numberOfMics; i++)
            if (isSelected(i))
                m_mic[i].setFisheyeStartAngle(_radian);
    }
    else if (_micIndex == -1)
        for (int i=0; i<MAX_MICS; i++)
            m_mic[i].setFisheyeStartAngle(_radian);
    else
        m_mic[(int)Tools::clip(_micIndex, 0, MAX_MICS)].setFisheyeStartAngle(_radian);
}

void AmbisonicVirtualMicUIManager::setAngleCartesianCoordinate(const int _micIndex, double _abscissa, double _ordinate)
{
    if (_micIndex == -1)
        for (int i=0; i<MAX_MICS; i++)
            m_mic[i].setAngleCartesianCoordinate(_abscissa, _ordinate);
    else
        m_mic[(int)Tools::clip(_micIndex, 0, MAX_MICS)].setAngleCartesianCoordinate(_abscissa, _ordinate);
}


/* --- Utility --- */

double AmbisonicVirtualMicUIManager::radianInterp(double _step, double _startRad, double _endRad)
{
    double start = Tools::radian_wrap(_startRad);
    double end   = Tools::radian_wrap(_endRad);
    
    if ( Tools::radian_wrap(end - start) <= CICM_PI ) // anti-clockwise
    {
        if (end - start >= 0)
            return Tools::radian_wrap( start + _step*(end - start) );
        else
            return Tools::radian_wrap( start + _step*( (end+CICM_2PI) - start) );
    }
    else // clockwise
    {
        if (end - start <= 0)
            return Tools::radian_wrap( start + _step*(end - start) );
        else
            return Tools::radian_wrap( start - _step*( (start+CICM_2PI) - end) );
    }
}

double AmbisonicVirtualMicUIManager::getClosestDefMicAngle(const int _micIndex)
{
    return getClosestDefMicAngle(getAngleInRadian(_micIndex));
}

double AmbisonicVirtualMicUIManager::getClosestDefMicAngle(double _angleInRadian)
{
    double angle = Tools::radian_wrap(_angleInRadian);
    double distance = CICM_2PI;
    double tempDistance, closestAngle;
    closestAngle = angle;
    
    for (int i = 0; i < m_numberOfMics; i++)
    {
        tempDistance = Tools::radianClosestDistance(angle, m_defaultAngles[i]);
        if (tempDistance < distance) {
            distance = tempDistance;
            closestAngle = m_defaultAngles[i];
        }
    }

    return closestAngle;
}

double AmbisonicVirtualMicUIManager::getClosestDefMicDistance(const int _micIndex)
{
    return getClosestDefMicDistance(getAngleInRadian(_micIndex));
}

double AmbisonicVirtualMicUIManager::getClosestDefMicDistance(double _angleInRadian)
{
    double angle = Tools::radian_wrap(_angleInRadian);
    double distance = CICM_2PI;
    
    for (int i = 0; i < m_numberOfMics; i++)
        distance = Tools::cicm_min(distance, Tools::radianClosestDistance(angle, m_defaultAngles[i]));
    
    return distance;
}

void AmbisonicVirtualMicUIManager::setAngleToClosestDefMicAngle(const int _micIndex)
{
    if (!Tools::isInside(_micIndex, int(0), int(m_numberOfMics))) return;
    m_mic[_micIndex].setAngleInRadian(getClosestDefMicAngle(_micIndex));
}

// non implemented
int AmbisonicVirtualMicUIManager::getClosestMicIndex(double _angleInRadian)
{
    int closest = 0;
    return closest;
}

// non implemented
int AmbisonicVirtualMicUIManager::getFarthestMicIndex(double _angleInRadian)
{
    int farthest = 0;
    return farthest;
}

long AmbisonicVirtualMicUIManager::getNumberOfSelectedMics()
{
    long numberOfSelectedMics = 0;
    for (int i = 0; i < m_numberOfMics; i++)
        if (m_mic[i].isSelected()) numberOfSelectedMics++;
    return numberOfSelectedMics;
}

