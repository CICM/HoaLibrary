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
    resetAngles(-1);
}
AmbisonicVirtualMicUIManager::~AmbisonicVirtualMicUIManager()
{
    m_mic.clear();
    if(m_defaultAngles) 
		free(m_defaultAngles);
}

void AmbisonicVirtualMicUIManager::setNumberOfMics(long aNumberOfMicrophones)
{
    long order = 0;
    aNumberOfMicrophones = Tools::clip_min(aNumberOfMicrophones, 3);
    
    if (aNumberOfMicrophones % 2 == 0)
        order = aNumberOfMicrophones / 2 - 1;
    else
        order = aNumberOfMicrophones / 2;
    
    if(m_mic.size() > aNumberOfMicrophones)
    {
        while (m_mic.size() != aNumberOfMicrophones)
        {
            m_mic.pop_back();
        }
    }
    else if(m_mic.size() < aNumberOfMicrophones)
    {
        while (m_mic.size() != aNumberOfMicrophones)
        {
            m_mic.push_back(new AmbisonicVirtualMicUI());
        }
    }
    
    for (int i = 0; i < m_mic.size(); i++)
    {
        m_mic[i]->setSelected(0);
        m_mic[i]->setOrder(order);
    }
    
    setDefaultAngles();
}

void AmbisonicVirtualMicUIManager::setDefaultAngles()
{
    if(m_defaultAngles)
        delete m_defaultAngles;
    
    m_defaultAngles = new double[m_mic.size()];
    
    for(int i = 0; i < m_mic.size(); i++)
        m_defaultAngles[i] = CICM_2PI / (double)m_mic.size() * (double)i;
}

void AmbisonicVirtualMicUIManager::resetAngles(const int anIndex)
{    
    if(anIndex == -1)
    {
        for(int i = 0; i < m_mic.size(); i++)
        {
            m_mic[i]->setAngleInRadian(m_defaultAngles[i]);
        }
    }
    else if(Tools::isInside(long(anIndex), long(0), long(m_mic.size())))
    {
        m_mic[anIndex]->setAngleInRadian(m_defaultAngles[anIndex]);
    }
}

void AmbisonicVirtualMicUIManager::resetWides(const int anIndex)
{
    if(anIndex == -1) // tous les angles
    {
        for (int i = 0; i < m_mic.size(); i++)
        {
            m_mic[i]->setWiderValue(1);
        }
    }
    else if(Tools::isInside(long(anIndex), long(0), long(m_mic.size())))
    {
        m_mic[anIndex]->setWiderValue(1);
    }
}

void AmbisonicVirtualMicUIManager::setAnglesInRadian(double* anglesInRadians, long aSize)
{
    for(int i = 0; i < aSize && i < m_mic.size(); i++)
    {
        m_mic[i]->setAngleInRadian(anglesInRadians[i]);
    }
}

void AmbisonicVirtualMicUIManager::setAnglesInDegree(double* anglesInDegrees, long aSize)
{
    for(int i = 0; i < aSize && i < m_mic.size(); i++)
    {
        m_mic[i]->setAngleInDegree(anglesInDegrees[i]);
    }
}

void AmbisonicVirtualMicUIManager::setAngleInRadian(const int anIndex, double anAngleInRadian)
{
    if(anIndex == -1)
    {
        for(int i = 0; i< m_mic.size(); i++)
        {
            m_mic[i]->setAngleInRadian(anAngleInRadian);
        }
    }
    else
    {
        m_mic[(int)Tools::clip(anIndex, 0, m_mic.size())]->setAngleInRadian(anAngleInRadian);
    }
}
void AmbisonicVirtualMicUIManager::setAngleInDegree(const int anIndex, double anAngleInDegree)
{
    if (anIndex == -1)
    {
        for(int i = 0; i<m_mic.size(); i++)
        {
            m_mic[i]->setAngleInDegree(anAngleInDegree);
        }
    }
    else
    {
        m_mic[(int)Tools::clip(anIndex, 0, m_mic.size())]->setAngleInDegree(anAngleInDegree);
    }
}
void AmbisonicVirtualMicUIManager::setDistance(const int anIndex, double _distance)
{
    if(anIndex == -1)
    {
        for(int i = 0; i<m_mic.size(); i++)
        {
            m_mic[i]->setDistance(_distance);
        }
    }
    else
    {
        m_mic[(int)Tools::clip(anIndex, 0, m_mic.size())]->setDistance(_distance);
    }
}

void AmbisonicVirtualMicUIManager::setWiderValues(double* _widerValues, long aSize)
{
    for (int i=0; i < aSize && i < m_mic.size(); i++) {
        m_mic[i]->setWiderValue(_widerValues[i]);
    }
}

void AmbisonicVirtualMicUIManager::setWiderValue(const int anIndex, double _widerValue)
{
    if (anIndex == -1)
    {
        for (int i=0; i < m_mic.size(); i++)
            m_mic[i]->setWiderValue(_widerValue);
    }
    else
    {
        m_mic[(int)Tools::clip(anIndex, 0, m_mic.size())]->setWiderValue(_widerValue);
    }
}

void AmbisonicVirtualMicUIManager::setSelected(const int anIndex, int _selectedState)
{
    if (anIndex == -1)
    {
        for (int i = 0; i < m_mic.size(); i++)
            m_mic[i]->setSelected(_selectedState);
    }
    else
    {
        m_mic[(int)Tools::clip(anIndex, 0, m_mic.size())]->setSelected(_selectedState);
    }
}

void AmbisonicVirtualMicUIManager::selectMicsBetweenMics(int anIndexOne, int anIndexTwo)
{
    double angle1 = getAngleInRadian(anIndexOne);
    double angle2 = getAngleInRadian(anIndexTwo);
    
    for (int i=0; i<m_mic.size(); i++) {
        if (Tools::isInsideRad(getAngleInRadian(i), angle1, angle2)) {
            setSelected(i, 1);
        }
    }
}

void AmbisonicVirtualMicUIManager::rotateSelectedMicsWithRadian(double _newRadian, int _sourceBeingDragged, int magnet)
{
    if (!Tools::isInside(_sourceBeingDragged, int(0), int(m_mic.size())))
        return;
    
    double deltaAngle;
    double oldAngle = m_mic[_sourceBeingDragged]->getAngleInRadian();
    deltaAngle = _newRadian - m_mic[_sourceBeingDragged]->getAngleInRadian();
    m_mic[_sourceBeingDragged]->setAngleInRadian(_newRadian);
    
    if (magnet == 1)
    {
        if ( getClosestDefMicDistance(_sourceBeingDragged) < CICM_2PI / (double) m_mic.size() *0.1 )
        {
            m_mic[_sourceBeingDragged]->setAngleInRadian(getClosestDefMicAngle(_sourceBeingDragged));
            deltaAngle =  m_mic[_sourceBeingDragged]->getAngleInRadian() - oldAngle;
        }
    }
    
    for (int i=0; i < m_mic.size(); i++)
    {
        if (isSelected(i) && i != _sourceBeingDragged)
        {
            m_mic[i]->rotateAngleInRadian(deltaAngle);
        }
    }
}

/*
void AmbisonicVirtualMicUIManager::rotateSelectedMicsWithRadian(double _newRadian, int _sourceBeingDragged, int magnet)
{
    if (!Tools::isInside(_sourceBeingDragged, int(0), int(m_mic.size()))) return;
    double deltaAngle = _newRadian - m_mic[_sourceBeingDragged]->getAngleInRadian();
    m_mic[_sourceBeingDragged]->setAngleInRadian(_newRadian);
    for (int i=0; i < m_mic.size(); i++) {
        if (isSelected(i) && i != _sourceBeingDragged) {
            m_mic[i]->rotateAngleInRadian(deltaAngle);
        }
    }
}
*/

void AmbisonicVirtualMicUIManager::setSelectedMicsWiderValueWithRadiusDelta(double deltaRadius)
{
    for (int i=0; i < m_mic.size(); i++) {
        if (isSelected(i)) {
            m_mic[i]->setWiderValue( m_mic[i]->getWiderValue() + deltaRadius);
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
        for (int i=0; i < m_mic.size(); i++)
            if (isSelected(i))
                m_mic[i]->setAngleInRadian(radianInterp(m_fisheyeStep, m_mic[i]->getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
    }
    else if (_micIndex == -1)
    {
        for (int i=0; i < m_mic.size(); i++)
            m_mic[i]->setAngleInRadian(radianInterp(m_fisheyeStep, m_mic[i]->getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
    }
    else
        m_mic[index]->setAngleInRadian(radianInterp(m_fisheyeStep, m_mic[index]->getFisheyeStartAngle(), m_fisheyeDestAngleInRadian));
}

void AmbisonicVirtualMicUIManager::setFisheyeStartAngle(const int _micIndex)
{
    if (_micIndex == -2)
    {
        for (int i=0; i < m_mic.size(); i++)
            if (isSelected(i))
                m_mic[i]->setFisheyeStartAngle();
    }
    else if (_micIndex == -1)
    {
        for (int i=0; i<m_mic.size(); i++)
            m_mic[i]->setFisheyeStartAngle();
    }
    else
        m_mic[(int)Tools::clip(_micIndex, 0, m_mic.size())]->setFisheyeStartAngle();
}

void AmbisonicVirtualMicUIManager::setFisheyeStartAngle(const int _micIndex, double anAngleInRadian)
{
    if (_micIndex == -2) {
        for (int i=0; i < m_mic.size(); i++)
            if (isSelected(i))
                m_mic[i]->setFisheyeStartAngle(anAngleInRadian);
    }
    else if (_micIndex == -1)
        for (int i=0; i<m_mic.size(); i++)
            m_mic[i]->setFisheyeStartAngle(anAngleInRadian);
    else
        m_mic[(int)Tools::clip(_micIndex, 0, m_mic.size())]->setFisheyeStartAngle(anAngleInRadian);
}

void AmbisonicVirtualMicUIManager::setAngleCartesianCoordinate(const int _micIndex, double _abscissa, double _ordinate)
{
    if (_micIndex == -1)
        for (int i=0; i<m_mic.size(); i++)
            m_mic[i]->setAngleCartesianCoordinate(_abscissa, _ordinate);
    else
        m_mic[(int)Tools::clip(_micIndex, 0, m_mic.size())]->setAngleCartesianCoordinate(_abscissa, _ordinate);
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
    
    for (int i = 0; i < m_mic.size(); i++)
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
    
    for (int i = 0; i < m_mic.size(); i++)
        distance = Tools::cicm_min(distance, Tools::radianClosestDistance(angle, m_defaultAngles[i]));
    
    return distance;
}

void AmbisonicVirtualMicUIManager::setAngleToClosestDefMicAngle(const int _micIndex)
{
    if (!Tools::isInside(_micIndex, int(0), int(m_mic.size()))) return;
    m_mic[_micIndex]->setAngleInRadian(getClosestDefMicAngle(_micIndex));
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
    for (int i = 0; i < m_mic.size(); i++)
        if (m_mic[i]->isSelected()) numberOfSelectedMics++;
    return numberOfSelectedMics;
}

