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

SourcesManager::SourcesGroup::SourcesGroup(SourcesManager* aSourceManager, long deadOrAlive, color aColor, std::string aDescription)
{
    m_source_manager = aSourceManager;
    setExistence(deadOrAlive);
    setDescription(aDescription);
    setColor(aColor);
    computeCentroid();
    m_maximum_radius = -1;
}

void SourcesManager::SourcesGroup::setExistence(long deadOrAlive)
{
    m_exist = Tools::clip(deadOrAlive, (long)0, (long)1);
}

void SourcesManager::SourcesGroup::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

void SourcesManager::SourcesGroup::setColor(color aColor)
{
    m_color.red =  Tools::clip(aColor.red, 0., 1.);
    m_color.green =  Tools::clip(aColor.green, 0., 1.);
    m_color.blue =  Tools::clip(aColor.blue, 0., 1.);
    m_color.alpha =  Tools::clip(aColor.alpha, 0., 1.);
}

void SourcesManager::SourcesGroup::setMaximumRadius(double aLimitValue)
{
    m_maximum_radius = aLimitValue;
}

void SourcesManager::SourcesGroup::computeCentroid()
{
    m_centroid.x = 0.;
    m_centroid.y = 0.;
    if(m_sources.size())
    {
        for(int i = 0; i < m_sources.size(); i++)
        {
            if(m_source_manager->sourceGetExistence(m_sources[i]))
            {
                m_centroid.x += m_source_manager->sourceGetAbscissa(m_sources[i]);
                m_centroid.y += m_source_manager->sourceGetOrdinate(m_sources[i]);
            }
        }
        m_centroid.x /= m_sources.size();
        m_centroid.y /= m_sources.size();
    }
}

void SourcesManager::SourcesGroup::addSource(long aSourceIndex)
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        if(m_sources[i] == aSourceIndex)
            return;
    }
    m_sources.push_back(aSourceIndex);
    
    computeCentroid();
}

void SourcesManager::SourcesGroup::sourceHasMoved()
{
    computeCentroid();
}

void SourcesManager::SourcesGroup::removeSource(long aSourceIndex)
{
    if(m_sources.size() > 0)
    {
        int size = m_sources.size();
        
        for(int i = 0; i < size; i++)
        {
            if(m_sources[i] == aSourceIndex)
            {
                for(int j = i; j < size - 1; j++)
                {
                    m_sources[j] = m_sources[j+1];
                }
                m_sources.pop_back();
            }
        }
    }
    computeCentroid();
}

void SourcesManager::SourcesGroup::shiftPolar(coordinatesPolar polarCoordinates)
{
    shiftPolar(polarCoordinates.radius, polarCoordinates.angle);
}

void SourcesManager::SourcesGroup::shiftPolar(double aRadius, double anAngle)
{
    shiftRadius(aRadius);
    shiftAngle(anAngle);
}

void SourcesManager::SourcesGroup::shiftRadius(double aRadius)
{
    if(m_maximum_radius >= 0)
    {
        if(aRadius < 0.)
        {
            double refRadius = m_maximum_radius;
            for(int i = 0; i < m_sources.size(); i++)
            {
                if(m_source_manager->sourceGetRadius(m_sources[i]) < refRadius)
                {
                    refRadius = m_source_manager->sourceGetRadius(m_sources[i]);
                }
            }
            if(aRadius + refRadius < 0.)
            {
                aRadius = - refRadius;
            }
        }
        else if(aRadius >= 0.)
        {
            double refRadius = -m_maximum_radius;
            for(int i = 0; i < m_sources.size(); i++)
            {
                if(m_source_manager->sourceGetRadius(m_sources[i]) > refRadius)
                {
                    refRadius = m_source_manager->sourceGetRadius(m_sources[i]);
                }
            }
            if(aRadius + refRadius > m_maximum_radius)
            {
                aRadius = m_maximum_radius - refRadius;
            }
        }
    }
    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetRadius(m_sources[i], aRadius + m_source_manager->sourceGetRadius(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftAngle(double anAngle)
{
    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetAngle(m_sources[i], anAngle + m_source_manager->sourceGetAngle(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftCartesian(coordinatesCartesian cartesianCoordinates)
{
    shiftCartesian(cartesianCoordinates.x, cartesianCoordinates.y);
}

void SourcesManager::SourcesGroup::shiftCartesian(double anAbscissa, double anOrdinate)
{
    shiftAbscissa(anAbscissa);
    shiftOrdinate(anOrdinate);
}

void SourcesManager::SourcesGroup::shiftAbscissa(double anAbscissa)
{
    double refRadius = 0.;
    double anOrdinate = 0.;
    if(m_maximum_radius >= 0)
    {
        refRadius = -m_maximum_radius;
        for(int i = 0; i < m_sources.size(); i++)
        {
            if(m_source_manager->sourceGetRadius(m_sources[i]) > refRadius)
            {
                refRadius = m_source_manager->sourceGetRadius(m_sources[i]);
                if(Tools::radius(m_source_manager->sourceGetAbscissa(m_sources[i]) + anAbscissa, m_source_manager->sourceGetOrdinate(m_sources[i])) > m_maximum_radius)
                {
                    return;
                    /*
                    anOrdinate = Tools::ordinate(m_maximum_radius - refRadius, m_source_manager->sourceGetAngle(m_sources[i]) + CICM_PI2) ;
                    anAbscissa = Tools::abscisse(m_maximum_radius - refRadius, m_source_manager->sourceGetAngle(m_sources[i]) + CICM_PI2);
                     */
                }
            }
        }
    }

    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetOrdinate(m_sources[i], anOrdinate + m_source_manager->sourceGetOrdinate(m_sources[i]));
        m_source_manager->sourceSetAbscissa(m_sources[i], anAbscissa + m_source_manager->sourceGetAbscissa(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftOrdinate(double anOrdinate)
{
    double refRadius = 0.;
    double anAbscissa = 0.;
    if(m_maximum_radius >= 0)
    {
        refRadius = -m_maximum_radius;
        for(int i = 0; i < m_sources.size(); i++)
        {
            if(m_source_manager->sourceGetRadius(m_sources[i]) > refRadius)
            {
                refRadius = m_source_manager->sourceGetRadius(m_sources[i]);
                if(Tools::radius(m_source_manager->sourceGetAbscissa(m_sources[i]), m_source_manager->sourceGetOrdinate(m_sources[i]) + anOrdinate) > m_maximum_radius)
                {
                    return;
                    /*
                    anOrdinate = Tools::ordinate(m_maximum_radius - refRadius, m_source_manager->sourceGetAngle(m_sources[i]) + CICM_PI2) ;
                    anAbscissa = Tools::abscisse(m_maximum_radius - refRadius, m_source_manager->sourceGetAngle(m_sources[i]) + CICM_PI2);*/
                }
            }
        }
    }
    
    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetAbscissa(m_sources[i], anAbscissa + m_source_manager->sourceGetAbscissa(m_sources[i]));
        m_source_manager->sourceSetOrdinate(m_sources[i], anOrdinate + m_source_manager->sourceGetOrdinate(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::setCoordinatesPolar(coordinatesPolar polarCoordinates)
{
    setRadius(polarCoordinates.radius);
    setAngle(polarCoordinates.angle);
}

void SourcesManager::SourcesGroup::setCoordinatesPolar(double aRadius, double anAngle)
{
    setRadius(aRadius);
    setAngle(anAngle);
}

void SourcesManager::SourcesGroup::setRadius(double aRadius)
{
    setCoordinatesCartesian(Tools::abscisse(aRadius, getAngle()), Tools::ordinate(aRadius, getAngle() - CICM_PI2));
}

void SourcesManager::SourcesGroup::setAngle(double anAngle)
{
    setCoordinatesCartesian(Tools::abscisse(getRadius(), anAngle), Tools::ordinate(getRadius(), anAngle));
}

void SourcesManager::SourcesGroup::setCoordinatesCartesian(coordinatesCartesian cartesianCoordinates)
{
    setAbscissa(cartesianCoordinates.x);
    setOrdinate(cartesianCoordinates.y);
}

void SourcesManager::SourcesGroup::setCoordinatesCartesian(double anAbscissa, double anOrdinate)
{
    setAbscissa(anAbscissa);
    setOrdinate(anOrdinate);
}

void SourcesManager::SourcesGroup::setAbscissa(double anAbscissa)
{
    double aAbscissaOffset = anAbscissa - getAbscissa();
    shiftAbscissa(aAbscissaOffset);
    computeCentroid();
}

void SourcesManager::SourcesGroup::setOrdinate(double anOrdinate)
{
    double aOrdinateOffset = anOrdinate - getOrdinate();
    shiftOrdinate(aOrdinateOffset);
    computeCentroid();
}

void SourcesManager::SourcesGroup::setRelativeCoordinatesPolar(coordinatesPolar polarCoordinates)
{
    setRelativeRadius(polarCoordinates.radius);
    setRelativeAngle(polarCoordinates.angle);
}

void SourcesManager::SourcesGroup::setRelativeCoordinatesPolar(double aRadius, double anAngle)
{
    setRelativeRadius(aRadius);
    setRelativeAngle(anAngle);
}

void SourcesManager::SourcesGroup::setRelativeRadius(double aRadius)
{
    double aRadiusOffset = Tools::clip_min(aRadius, 0.) - getRadius();
    shiftRadius(aRadiusOffset);
    computeCentroid();
}

void SourcesManager::SourcesGroup::setRelativeAngle(double anAngle)
{
    anAngle +=  CICM_PI2;
    while (anAngle > CICM_2PI)
        anAngle -= CICM_2PI;
    while (anAngle < 0.)
        anAngle += CICM_2PI;
    
    double aAngleOffset = anAngle  - getAngle();
    shiftAngle(aAngleOffset);
    computeCentroid();
}

coordinatesPolar SourcesManager::SourcesGroup::getCoordinatesPolar()
{
    coordinatesPolar polarCentroid;
    polarCentroid.radius = getRadius();
    polarCentroid.angle = getAngle();
    return polarCentroid;
}

double SourcesManager::SourcesGroup::getRadius()
{
    return Tools::radius(m_centroid.x, m_centroid.y);
}

double SourcesManager::SourcesGroup::getAngle()
{
    return Tools::angle(m_centroid.x, m_centroid.y) + CICM_PI2;
}

coordinatesCartesian SourcesManager::SourcesGroup::getCoordinatesCartesian()
{
    return m_centroid;
}

double SourcesManager::SourcesGroup::getAbscissa()
{
    return m_centroid.x;
}

double SourcesManager::SourcesGroup::getOrdinate()
{
    return m_centroid.y;
}

long SourcesManager::SourcesGroup::getNumberOfSources()
{
    return m_sources.size();
}


color SourcesManager::SourcesGroup::getColor()
{
    return m_color;
}

long SourcesManager::SourcesGroup::getExistence()
{
    return m_exist;
}

std::string SourcesManager::SourcesGroup::getDescription()
{
    return m_description;
}

SourcesManager::SourcesGroup::~SourcesGroup()
{
    for(int i = 0; i < m_sources.size(); i++)
        m_sources.pop_back();
}