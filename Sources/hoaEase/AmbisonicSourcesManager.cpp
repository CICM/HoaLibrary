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

void SourcesManager::remove(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        m_sources[anIndex]->setExistence(0);
}

void SourcesManager::setCoordinatesPolar(long anIndex, coordinatesPolar polarCoordinates)
{
    setRadius(anIndex, polarCoordinates.radius);
    setAngle(anIndex, polarCoordinates.angle);
}

void SourcesManager::setCoordinatesPolar(long anIndex, double aRadius, double anAngle)
{
    setRadius(anIndex, aRadius);
    setAngle(anIndex, anAngle);
}

void SourcesManager::setRadius(long anIndex, double aRadius)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
        }
        m_sources.push_back(new Source(anIndex, aRadius));
    }
    else
    {
        m_sources[anIndex]->setRadius(aRadius);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
}

void SourcesManager::setAngle(long anIndex, double anAngle)
{
    if(anIndex >= m_sources.size())
    {
        for(int i = m_sources.size(); i < anIndex; i++)
        {
            m_sources.push_back(new Source(0));
        }
        m_sources.push_back(new Source(anIndex, 0., anAngle));
    }
    else
    {
        m_sources[anIndex]->setAngle(anAngle);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
}

void SourcesManager::setCoordinatesCartesian(long anIndex, coordinatesCartesian cartesianCoordinates)
{
    setAbscissa(anIndex, cartesianCoordinates.x);
    setOrdinate(anIndex, cartesianCoordinates.y);
}

void SourcesManager::setCoordinatesCartesian(long anIndex, double anAbscissa, double anOrdinate)
{
    setAbscissa(anIndex, anAbscissa);
    setOrdinate(anIndex, anOrdinate);
}

void SourcesManager::setAbscissa(long anIndex, double anAbscissa)
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
    else
    {
        m_sources[anIndex]->setAbscissa(anAbscissa);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
}

void SourcesManager::setOrdinate(long anIndex, double anOrdinate)
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
    else
    {
         m_sources[anIndex]->setOrdinate(anOrdinate);
        if(!m_sources[anIndex]->getExistence())
            m_sources[anIndex]->setExistence(1);
    }
}

void SourcesManager::setColor(long anIndex, color aColor)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        m_sources[anIndex]->setColor(aColor);
    }
    
}

void SourcesManager::setDescription(long anIndex, std::string aDescription)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
    {
        m_sources[anIndex]->setDescription(aDescription);
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