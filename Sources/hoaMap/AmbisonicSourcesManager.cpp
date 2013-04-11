/*
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

#include "AmbisonicSourcesManager.h"

SourcesManager::SourcesManager(double aMaximumLimitValue)
{
    setMaximumRadius(aMaximumLimitValue);
}

void SourcesManager::setMaximumRadius(double aLimitValue)
{
    m_maximum_radius = aLimitValue;
    for(int i = 0; i < m_groups.size(); i++)
        m_groups[i]->setMaximumRadius(m_maximum_radius);
}

double SourcesManager::getLimitMaximum()
{
    return m_maximum_radius;
}

long SourcesManager::getMaximumIndexOfSource()
{
    return  m_sources.size();
}

long SourcesManager::getNumberOfSources()
{
    long numberOfSources = 0;
    for(int i = 0; i < m_sources.size(); i++)
    {
        if (m_sources[i]->getExistence())
            numberOfSources++;
    }
    return  numberOfSources;
}

long SourcesManager::getMaximumIndexOfGroup()
{
    return  m_groups.size();
}

long SourcesManager::getNumberOfGroups()
{
    long numberOfGroups = 0;
    for(int i = 0; i < m_groups.size(); i++)
    {
        if (m_groups[i]->getNumberOfSources())
            numberOfGroups++;
    }
    return  numberOfGroups;
}

/*******************************************************************************/
/*********************************  SOURCES ************************************/
/*******************************************************************************/

void SourcesManager::sourceRemove(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        int numberOfGroups = m_sources[anIndex]->getNumberOfGroups();
        int indexOfGroup = -1;
        for(int i = 0; i < numberOfGroups; i++)
        {
             indexOfGroup = m_sources[anIndex]->getGroupIndex(i);
            
            if(indexOfGroup >= 0 && indexOfGroup < getNumberOfGroups());
               m_groups[indexOfGroup]->removeSource(anIndex);
        }
        for(int i = 0; i < numberOfGroups; i++)
        {
            indexOfGroup = m_sources[anIndex]->getGroupIndex(i);
            m_sources[anIndex]->removeGroup(indexOfGroup);
        }
        m_sources[anIndex]->setExistence(0);
    }
}

void SourcesManager::sourceSetPolar(long anIndex, coordinatesPolar polarCoordinates)
{
    sourceSetRadius(anIndex, polarCoordinates.radius);
    sourceSetAngle(anIndex, polarCoordinates.angle);
}

void SourcesManager::sourceSetPolar(long anIndex, double aRadius, double anAngle)
{
    sourceSetRadius(anIndex, aRadius);
    sourceSetAngle(anIndex, anAngle);
}

void SourcesManager::sourceSetRadius(long anIndex, double aRadius)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
                m_sources[i]->setMaximumRadius(m_maximum_radius);

        }
        m_sources.push_back(new Source(anIndex, aRadius));
            m_sources[anIndex]->setMaximumRadius(m_maximum_radius);
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setRadius(aRadius);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
    for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
    {
        int groupIndex = m_sources[anIndex]->getGroupIndex(i);
        if(groupIndex >= 0 && groupIndex < m_groups.size())
            m_groups[groupIndex]->sourceHasMoved();
    }
}

void SourcesManager::sourceSetAngle(long anIndex, double anAngle)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
                m_sources[i]->setMaximumRadius(m_maximum_radius);
        }
        m_sources.push_back(new Source(anIndex, 0., anAngle));
            m_sources[anIndex]->setMaximumRadius(m_maximum_radius);
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setAngle(anAngle);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
    for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
    {
        int groupIndex = m_sources[anIndex]->getGroupIndex(i);
        if(groupIndex >= 0 && groupIndex < m_groups.size())
            m_groups[groupIndex]->sourceHasMoved();
    }
}

void SourcesManager::sourceSetCartesian(long anIndex, coordinatesCartesian cartesianCoordinates)
{
    sourceSetAbscissa(anIndex, cartesianCoordinates.x);
    sourceSetOrdinate(anIndex, cartesianCoordinates.y);
}

void SourcesManager::sourceSetCartesian(long anIndex, double anAbscissa, double anOrdinate)
{
    sourceSetAbscissa(anIndex, anAbscissa);
    sourceSetOrdinate(anIndex, anOrdinate);
}

void SourcesManager::sourceSetAbscissa(long anIndex, double anAbscissa)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
                m_sources[i]->setMaximumRadius(m_maximum_radius);
        }
        coordinatesCartesian cartesianCoordinates;
        cartesianCoordinates.x = anAbscissa;
        cartesianCoordinates.y = 0.;
        m_sources.push_back(new Source(anIndex, cartesianCoordinates));
        m_sources[anIndex]->setMaximumRadius(m_maximum_radius);
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setAbscissa(anAbscissa);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
    for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
    {
        int groupIndex = m_sources[anIndex]->getGroupIndex(i);
        if(groupIndex >= 0 && groupIndex < m_groups.size())
            m_groups[groupIndex]->sourceHasMoved();
    }
}

void SourcesManager::sourceSetOrdinate(long anIndex, double anOrdinate)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
                m_sources[i]->setMaximumRadius(m_maximum_radius);
        }
        coordinatesCartesian cartesianCoordinates;
        cartesianCoordinates.x = 0.;
        cartesianCoordinates.y = anOrdinate;
        m_sources.push_back(new Source(anIndex, cartesianCoordinates));
            m_sources[anIndex]->setMaximumRadius(m_maximum_radius);
    }
    else if(anIndex >= 0)
    {
         m_sources[anIndex]->setOrdinate(anOrdinate);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
    for(int i = 0; i < m_sources[anIndex]->getNumberOfGroups(); i++)
    {
        int groupIndex = m_sources[anIndex]->getGroupIndex(i);
        if(groupIndex >= 0 && groupIndex < m_groups.size())
            m_groups[groupIndex]->sourceHasMoved();
    }
}

void SourcesManager::sourceSetColor(long anIndex, color aColor)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        m_sources[anIndex]->setColor(aColor);
    }
}

void SourcesManager::sourceSetDescription(long anIndex, std::string aDescription)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        m_sources[anIndex]->setDescription(aDescription);
    }
}

/******************************************************************************/

coordinatesPolar SourcesManager::sourceGetCoordinatesPolar(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getCoordinatesPolar();
    
    return coordinatesPolar_null;
}

double SourcesManager::sourceGetRadius(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getRadius();
    
    return NULL;
}

double SourcesManager::sourceGetAngle(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getAngle();
    
    return NULL;
}

coordinatesCartesian SourcesManager::sourceGetCoordinatesCartesian(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getCoordinatesCartesian();
    
    return coordinatesCartesian_null;
}

double SourcesManager::sourceGetAbscissa(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getAbscissa();
    
    return NULL;
}

double SourcesManager::sourceGetOrdinate(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getOrdinate();
    
    return NULL;
}

color SourcesManager::sourceGetColor(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getColor();
    
    return color_null;
}

std::string SourcesManager::sourceGetDescription(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getDescription();
    
    return NULL;
}

long SourcesManager::sourceGetExistence(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        return m_sources[anIndex]->getExistence();
    }
    return 0;
}

long SourcesManager::sourceGetNumberOfGroups(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        return m_sources[anIndex]->getNumberOfGroups();
    }
    return 0;
}

long SourcesManager::sourceGetGroupIndex(long aSourceIndex, long aGroupIndex)
{
    if(aSourceIndex < m_sources.size() && aSourceIndex >= 0)
    {
        return m_sources[aSourceIndex]->getGroupIndex(aGroupIndex);
    }
    return 0;
}

/*******************************************************************************/
/**********************************  GROUP  ************************************/
/*******************************************************************************/

void SourcesManager::groupSetSource(long aGroupIndex, long aSourceIndex)
{
    if(aGroupIndex >= m_groups.size())
    {
        for(int i = m_groups.size(); i < aGroupIndex; i++)
        {
            m_groups.push_back(new SourcesGroup(this, 0));
                m_groups[i]->setMaximumRadius(m_maximum_radius);
            
        }
        m_groups.push_back(new SourcesGroup(this, 0));
            m_groups[aGroupIndex]->setMaximumRadius(m_maximum_radius);
        if(m_sources.size() > aSourceIndex && m_sources[aSourceIndex]->getExistence())
        {
            m_groups[aGroupIndex]->setExistence(1);
            m_groups[aGroupIndex]->addSource(aSourceIndex);
            m_sources[aSourceIndex]->setGroup(aGroupIndex);
        }
    }
    else if(aGroupIndex >= 0)
    {
        if(m_sources.size() > aSourceIndex && m_sources[aSourceIndex]->getExistence())
        {
            m_groups[aGroupIndex]->addSource(aSourceIndex);
            m_sources[aSourceIndex]->setGroup(aGroupIndex);
            m_groups[aGroupIndex]->setExistence(1);
        }
    }
}

void SourcesManager::groupRemoveSource(long aGroupIndex, long aSourceIndex)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        if(m_sources.size() > aSourceIndex)
        {
            m_groups[aGroupIndex]->removeSource(aSourceIndex);
            m_sources[aSourceIndex]->removeGroup(aGroupIndex);
        }
    }
}

void SourcesManager::groupSetPolar(long aGroupIndex, coordinatesPolar polarCoordinates)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setCoordinatesPolar(polarCoordinates);
    }
}

void SourcesManager::groupSetPolar(long aGroupIndex, double aRadius, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setCoordinatesPolar(aRadius, anAngle);
    }
}

void SourcesManager::groupSetRadius(long aGroupIndex, double aRadius)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRadius(aRadius);
    }
}

void SourcesManager::groupSetAngle(long aGroupIndex, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setAngle(anAngle);
    }
}

void SourcesManager::groupSetCartesian(long aGroupIndex, coordinatesCartesian cartesianCoordinates)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setCoordinatesCartesian(cartesianCoordinates);
    }
}

void SourcesManager::groupSetCartesian(long aGroupIndex, double anAbscissa, double anOrdinate)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setCoordinatesCartesian(anAbscissa, anOrdinate);
    }
}

void SourcesManager::groupSetAbscissa(long aGroupIndex, double anAbscissa)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setAbscissa(anAbscissa);
    }
}

void SourcesManager::groupSetOrdinate(long aGroupIndex, double anOrdinate)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setOrdinate(anOrdinate);
    }
}

void SourcesManager::groupSetRelativePolar(long aGroupIndex, coordinatesPolar polarCoordinates)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRelativeCoordinatesPolar(polarCoordinates);
    }
}

void SourcesManager::groupSetRelativePolar(long aGroupIndex, double aRadius, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRelativeCoordinatesPolar(aRadius, anAngle);
    }
}

void SourcesManager::groupSetRelativeRadius(long aGroupIndex, double aRadius)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRelativeRadius(aRadius);
    }
}

void SourcesManager::groupSetRelativeAngle(long aGroupIndex, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setRelativeAngle(anAngle);
    }
}

void SourcesManager::groupSetColor(long aGroupIndex, color aColor)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setColor(aColor);
    }
}

void SourcesManager::groupSetDescription(long aGroupIndex, std::string aDescription)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->setDescription(aDescription);
    }
}

void SourcesManager::groupRemove(long aGroupIndex)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        for(int i = 0; i < m_sources.size(); i++)
        {
            m_sources[i]->removeGroup(aGroupIndex);
            m_groups[aGroupIndex]->removeSource(i);
        }
        m_groups[aGroupIndex]->setColor(color_mat_black);
        m_groups[aGroupIndex]->setDescription("");
        m_groups[aGroupIndex]->setExistence(0);
    }
}


/******************************************************************************/

coordinatesPolar SourcesManager::groupGetCoordinatesPolar(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getCoordinatesPolar();
    
    return coordinatesPolar_null;
}

double SourcesManager::groupGetRadius(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getRadius();
    
    return NULL;
}

double SourcesManager::groupGetAngle(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getAngle();
    
    return NULL;
}

coordinatesCartesian SourcesManager::groupGetCoordinatesCartesian(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getCoordinatesCartesian();
    
    return coordinatesCartesian_null;
}

double SourcesManager::groupGetAbscissa(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getAbscissa();
    
    return NULL;
}

double SourcesManager::groupGetOrdinate(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getOrdinate();
    
    return NULL;
}

color SourcesManager::groupGetColor(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getColor();
    
    return color_null;
}

std::string SourcesManager::groupGetDescription(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex]->getDescription();
    
    return NULL;
}

long SourcesManager::groupGetExistence(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
    {
        return m_groups[anIndex]->getExistence();
    }
    return 0;
}

/************************************/

SourcesManager::~SourcesManager()
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        delete m_sources[i];
        m_sources[i] = NULL;
    }
    for(int i = 0; i < m_groups.size(); i++)
    {
        delete m_groups[i];
        m_groups[i] = NULL;
    }
}