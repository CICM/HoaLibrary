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

SourcesManager::SourcesManager()
{
    ;
}

void SourcesManager::sourceRemove(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        m_sources[anIndex]->setExistence(0);
}

void SourcesManager::sourceSetCoordinatesPolar(long anIndex, coordinatesPolar polarCoordinates)
{
    sourceSetRadius(anIndex, polarCoordinates.radius);
    sourceSetAngle(anIndex, polarCoordinates.angle);
}

void SourcesManager::sourceSetCoordinatesPolar(long anIndex, double aRadius, double anAngle)
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
        }
        m_sources.push_back(new Source(anIndex, aRadius));
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setRadius(aRadius);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
}

void SourcesManager::sourceSetAngle(long anIndex, double anAngle)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
        }
        m_sources.push_back(new Source(anIndex, 0., anAngle));
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setAngle(anAngle);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
}

void SourcesManager::sourceSetCoordinatesCartesian(long anIndex, coordinatesCartesian cartesianCoordinates)
{
    sourceSetAbscissa(anIndex, cartesianCoordinates.x);
    sourceSetOrdinate(anIndex, cartesianCoordinates.y);
}

void SourcesManager::sourceSetCoordinatesCartesian(long anIndex, double anAbscissa, double anOrdinate)
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
        }
        coordinatesCartesian cartesianCoordinates;
        cartesianCoordinates.x = anAbscissa;
        cartesianCoordinates.y = 0.;
        m_sources.push_back(new Source(anIndex, cartesianCoordinates));
    }
    else if(anIndex >= 0)
    {
        m_sources[anIndex]->setAbscissa(anAbscissa);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
}

void SourcesManager::sourceSetOrdinate(long anIndex, double anOrdinate)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
        }
        coordinatesCartesian cartesianCoordinates;
        cartesianCoordinates.x = 0.;
        cartesianCoordinates.y = anOrdinate;
        m_sources.push_back(new Source(anIndex, cartesianCoordinates));
    }
    else if(anIndex >= 0)
    {
         m_sources[anIndex]->setOrdinate(anOrdinate);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
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

void SourcesManager::groupSetSource(long aGroupIndex, long aSourceIndex)
{
    if(aGroupIndex >= m_groups.size())
    {
        for(int i = m_groups.size(); i < aGroupIndex; i++)
        {
            m_groups.push_back(new SourcesGroup());
        }
        m_groups.push_back(new SourcesGroup());
        if(m_sources.size() > aSourceIndex)
            m_groups[aGroupIndex]->addSource(m_sources[aSourceIndex]);
    }
    else if(aGroupIndex >= 0)
    {
        if(m_sources.size() > aSourceIndex)
            m_groups[aGroupIndex]->addSource(m_sources[aSourceIndex]);
    }
}

void SourcesManager::groupRemoveSource(long aGroupIndex, long aSourceIndex)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        if(m_sources.size() > aSourceIndex)
            m_groups[aGroupIndex]->removeSource(m_sources[aSourceIndex]);
    }
}

void SourcesManager::groupShiftPolar(long aGroupIndex, coordinatesPolar polarCoordinates)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->shiftPolar(polarCoordinates);
    }
}

void SourcesManager::groupShiftPolar(long aGroupIndex, double aRadius, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->shiftPolar(aRadius, anAngle);
    }
}

void SourcesManager::groupShiftRadius(long aGroupIndex, double aRadius)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->shiftRadius(aRadius);
    }
}

void SourcesManager::groupShiftAngle(long aGroupIndex, double anAngle)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->shiftAngle(anAngle);
    }
}

void SourcesManager::groupShiftCartesian(long aGroupIndex, coordinatesCartesian cartesianCoordinates)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->shiftCartesian(cartesianCoordinates);
    }
}

void SourcesManager::groupShiftCartesian(long aGroupIndex, double anAbscissa, double anOrdinate)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->shiftCartesian(anAbscissa, anOrdinate);
    }
}

void SourcesManager::groupShiftAbscissa(long aGroupIndex, double anAbscissa)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->shiftAbscissa(anAbscissa);
    }
}

void SourcesManager::groupShiftOrdinate(long aGroupIndex, double anOrdinate)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        m_groups[aGroupIndex]->shiftOrdinate(anOrdinate);
    }
}

void SourcesManager::groupSetColor(long aGroupIndex, color aColor)
{
    if(aGroupIndex < m_groups.size() && aGroupIndex >= 0)
    {
        //m_groups[aGroupIndex]->setColor(aColor);
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
            m_groups[aGroupIndex]->removeSource(m_sources[i]);
    }
}

/******************************************************************************/

coordinatesPolar SourcesManager::getCoordinatesPolar(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getCoordinatesPolar();
    
    return coordinatesPolar_null;
}

double SourcesManager::getRadius(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getRadius();

    return NULL;
}

double SourcesManager::getAngle(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getAngle();
    
    return NULL;
}

coordinatesCartesian SourcesManager::getCoordinatesCartesian(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getCoordinatesCartesian();
    
    return coordinatesCartesian_null;
}

double SourcesManager::getAbscissa(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getAbscissa();
    
    return NULL;
}

double SourcesManager::getOrdinate(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getOrdinate();
    
    return NULL;
}

color SourcesManager::getColor(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getColor();
    
    return color_null;
}

std::string SourcesManager::getDescription(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex]->getDescription();
    
    return NULL;
}

long SourcesManager::getSourceExistence(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        return m_sources[anIndex]->getExistence();
    }
    return 0;
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