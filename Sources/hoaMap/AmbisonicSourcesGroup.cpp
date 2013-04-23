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

SourcesManager::SourcesGroup::SourcesGroup(SourcesManager* aSourceManager, long deadOrAlive)
{
    m_source_manager = aSourceManager;
    setExistence(deadOrAlive);
    setColor(0.2, 0.2, 0.2, 1.);
    setDescription("");
    computeCentroid();
    m_maximum_radius = -1;
    m_mute = 0;
}

void SourcesManager::SourcesGroup::setExistence(long deadOrAlive)
{
    m_exist = Tools::clip(deadOrAlive, (long)0, (long)1);
}

void SourcesManager::SourcesGroup::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

void SourcesManager::SourcesGroup::setColor(double red, double green, double blue, double alpha)
{
    m_color.red =  Tools::clip(red, 0., 1.);
    m_color.green =  Tools::clip(green, 0., 1.);
    m_color.blue =  Tools::clip(blue, 0., 1.);
    m_color.alpha =  Tools::clip(alpha, 0., 1.);
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

void SourcesManager::SourcesGroup::shiftAbscissa(double anAbscissa)
{
    if(m_maximum_radius >= 0)
    {
        if(anAbscissa < 0.)
        {
            double refAbcsissa = -m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleAbscissa = -sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetOrdinate(m_sources[i]) * m_source_manager->sourceGetOrdinate(m_sources[i]));
                if(circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]) > refAbcsissa)
                {
                    refAbcsissa = circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]);
                }
            }
            if(anAbscissa < refAbcsissa)
            {
                anAbscissa = refAbcsissa;
            }
        }
        else if(anAbscissa >= 0.)
        {
            double refAbcsissa = m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleAbscissa = sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetOrdinate(m_sources[i]) * m_source_manager->sourceGetOrdinate(m_sources[i]));
                if(circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]) < refAbcsissa)
                {
                    refAbcsissa = circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]);
                }
            }
            if(anAbscissa > refAbcsissa)
            {
                anAbscissa = refAbcsissa;
            }
        }
    }

    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetAbscissa(m_sources[i], anAbscissa + m_source_manager->sourceGetAbscissa(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftOrdinate(double anOrdinate)
{
    if(m_maximum_radius >= 0)
    {
        if(anOrdinate < 0.)
        {
            double refOrdinate = -m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleOrdinate = -sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetAbscissa(m_sources[i]) * m_source_manager->sourceGetAbscissa(m_sources[i]));
                if(circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]) > refOrdinate)
                {
                    refOrdinate = circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]);
                }
            }
            if(anOrdinate < refOrdinate)
            {
                anOrdinate = refOrdinate;
            }
        }
        else if(anOrdinate >= 0.)
        {
            double refOrdinate = m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleOrdinate = sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetAbscissa(m_sources[i]) * m_source_manager->sourceGetAbscissa(m_sources[i]));
                if(circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]) < refOrdinate)
                {
                    refOrdinate = circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]);
                }
            }
            if(anOrdinate > refOrdinate)
            {
                anOrdinate = refOrdinate;
            }
        }
    }
    
    for(int i = 0; i < m_sources.size(); i++)
    {
       m_source_manager->sourceSetOrdinate(m_sources[i], anOrdinate + m_source_manager->sourceGetOrdinate(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::shiftCartesian(double anAbscissa, double anOrdinate)
{
    if(m_maximum_radius >= 0)
    {
        if(anAbscissa < 0. &&  anOrdinate < 0.)
        {
            double refAbcsissa = -m_maximum_radius * 2.;
            double refOrdinate = -m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleAbscissa = -sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetOrdinate(m_sources[i]) * m_source_manager->sourceGetOrdinate(m_sources[i]));
                double circleOrdinate = -sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetAbscissa(m_sources[i]) * m_source_manager->sourceGetAbscissa(m_sources[i]));
                if(circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]) > refAbcsissa)
                {
                    refAbcsissa = circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]);
                }
                if(circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]) > refOrdinate)
                {
                    refOrdinate = circleOrdinate - m_source_manager->sourceGetOrdinate(m_sources[i]);
                }
            }
            if(anAbscissa < refAbcsissa)
            {
                anAbscissa = refAbcsissa;
            }
            if(anOrdinate < refOrdinate)
            {
                anOrdinate = refOrdinate;
            }
        }
        else if(anAbscissa >= 0.)
        {
            double refAbcsissa = m_maximum_radius * 2.;
            for(int i = 0; i < m_sources.size(); i++)
            {
                double circleAbscissa = sqrt(m_maximum_radius * m_maximum_radius - m_source_manager->sourceGetOrdinate(m_sources[i]) * m_source_manager->sourceGetOrdinate(m_sources[i]));
                if(circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]) < refAbcsissa)
                {
                    refAbcsissa = circleAbscissa - m_source_manager->sourceGetAbscissa(m_sources[i]);
                }
            }
            if(anAbscissa > refAbcsissa)
            {
                anAbscissa = refAbcsissa;
            }
        }
    }
    
    for(int i = 0; i < m_sources.size(); i++)
    {
        m_source_manager->sourceSetAbscissa(m_sources[i], anAbscissa + m_source_manager->sourceGetAbscissa(m_sources[i]));
        m_source_manager->sourceSetOrdinate(m_sources[i], anOrdinate + m_source_manager->sourceGetOrdinate(m_sources[i]));
    }
}

void SourcesManager::SourcesGroup::setCoordinatesPolar(double aRadius, double anAngle)
{
    setCoordinatesCartesian(Tools::abscisse(aRadius, anAngle), Tools::ordinate(aRadius, anAngle));
}

void SourcesManager::SourcesGroup::setRadius(double aRadius)
{
    setCoordinatesCartesian(Tools::abscisse(aRadius, getAngle()), Tools::ordinate(aRadius, getAngle()));
}

void SourcesManager::SourcesGroup::setAngle(double anAngle)
{
    setCoordinatesCartesian(Tools::abscisse(getRadius(), anAngle), Tools::ordinate(getRadius(), anAngle));
}

void SourcesManager::SourcesGroup::setCoordinatesCartesian(double anAbscissa, double anOrdinate)
{
    anAbscissa = anAbscissa - getAbscissa();
    anOrdinate = anOrdinate - getOrdinate();
    shiftAbscissa(anAbscissa);
    shiftOrdinate(anOrdinate);
    computeCentroid();
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

void SourcesManager::SourcesGroup::setMute(long aValue)
{
    m_mute = Tools::clip(aValue, (long)0, (long)1);
}

double SourcesManager::SourcesGroup::getRadius()
{
    return Tools::radius(m_centroid.x, m_centroid.y);
}

double SourcesManager::SourcesGroup::getAngle()
{
    return Tools::angle(m_centroid.x, m_centroid.y) + CICM_PI2;
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


long SourcesManager::SourcesGroup::getSourceIndex(long anIndex)
{
    if(anIndex < m_sources.size() && anIndex >= 0)
        return m_sources[anIndex];
    else
        return -1;
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

long SourcesManager::SourcesGroup::getMute()
{
    return m_mute;
}


SourcesManager::SourcesGroup::~SourcesGroup()
{
    m_sources.clear();
}