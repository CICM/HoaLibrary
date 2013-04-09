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

#include "AmbisonicSourcesGroup.h"

SourcesGroup::SourcesGroup(std::string aDescription)
{
    m_exist = 1;
    setDescription(aDescription);
}

void SourcesGroup::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

void SourcesGroup::addSource(Source* aSource)
{
    if(m_sources.size() == 0)
        m_sources.push_back(aSource);
    else
    {
        for(int i = 0; i < m_sources.size(); i++)
        {
            if(m_sources[i] == aSource)
                return;
        }
        for(int i = 0; i < m_sources.size(); i++)
        {
            if(m_sources[i] == NULL);
            {
                m_sources.push_back(aSource);
                return;
            }
        }
    }
}

void SourcesGroup::removeSource(Source* aSource)
{
    if(aSource == NULL)
        return;
    for(int i = 0; i < m_sources.size(); i++)
    {
        if(m_sources[i] == aSource)
            m_sources[i] = NULL;
    }
}

void SourcesGroup::shiftPolar(coordinatesPolar polarCoordinates)
{
    shiftPolar(polarCoordinates.radius, polarCoordinates.angle);
}

void SourcesGroup::shiftPolar(double aRadius, double anAngle)
{
    shiftRadius(aRadius);
    shiftAngle(anAngle);
}

void SourcesGroup::shiftRadius(double aRadius)
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        if(m_sources[i] != NULL)
            m_sources[i]->setRadius(aRadius + m_sources[i]->getRadius());
    }
}

void SourcesGroup::shiftAngle(double anAngle)
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        if(m_sources[i] != NULL)
            m_sources[i]->setAngle(anAngle + m_sources[i]->getAngle());
    }
}

void SourcesGroup::shiftCartesian(coordinatesCartesian cartesianCoordinates)
{
    shiftCartesian(cartesianCoordinates.x, cartesianCoordinates.y);
}

void SourcesGroup::shiftCartesian(double anAbscissa, double anOrdinate)
{
    shiftAbscissa(anAbscissa);
    shiftOrdinate(anOrdinate);
}

void SourcesGroup::shiftAbscissa(double anAbscissa)
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        if(m_sources[i] != NULL)
            m_sources[i]->setAbscissa(anAbscissa + m_sources[i]->getAbscissa());
    }
}

void SourcesGroup::shiftOrdinate(double anOrdinate)
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        if(m_sources[i] != NULL)
            m_sources[i]->setOrdinate(anOrdinate + m_sources[i]->getOrdinate());
    }
}

SourcesGroup::~SourcesGroup()
{
    ;
}