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

SourcesManager::Source::Source(long deadOrAlive, double aRadius, double anAngle)
{
    m_exist = Tools::clip(deadOrAlive, (long)0, (long)1);
    setRadius(aRadius);
    setAngle(anAngle);
    setColor(0.2, 0.2, 0.2, 1.);
    setDescription("");
    m_maximum_radius = -1;
    m_mute = 0;
}

void SourcesManager::Source::setMaximumRadius(double aLimitValue)
{
    m_maximum_radius = aLimitValue;
}

void SourcesManager::Source::setExistence(long deadOrAlive)
{
    m_exist = Tools::clip(deadOrAlive, (long)0, (long)1);
}

void SourcesManager::Source::setCoordinatesPolar(double aRadius, double anAngle)
{
    setRadius(aRadius);
    setAngle(anAngle);
}

void SourcesManager::Source::setRadius(double aRadius)
{
    if(m_maximum_radius >= 0)
    {
        if(aRadius < -m_maximum_radius || aRadius > m_maximum_radius)
            return;
    }
    m_coordinate_polar.radius = Tools::clip_min(aRadius, 0.);
}

void SourcesManager::Source::setAngle(double anAngle)
{
    while (anAngle > CICM_2PI)
        anAngle -= CICM_2PI;
    while (anAngle < 0.)
        anAngle += CICM_2PI;
    m_coordinate_polar.angle = anAngle;
}

void SourcesManager::Source::setCoordinatesCartesian(double anAbscissa, double anOrdinate)
{
    setRadius(Tools::radius(anAbscissa, anOrdinate));
    setAngle(Tools::angle(anAbscissa, anOrdinate) - CICM_PI2);
}

void SourcesManager::Source::setAbscissa(double anAbscissa)
{
    double ordinate = getOrdinate();
    setRadius(Tools::radius(anAbscissa, ordinate));
    setAngle(Tools::angle(anAbscissa, ordinate) - CICM_PI2);
}

void SourcesManager::Source::setOrdinate(double anOrdinate)
{
    double abscissa = getAbscissa();
    setRadius(Tools::radius(abscissa, anOrdinate));
    setAngle(Tools::angle(abscissa, anOrdinate) - CICM_PI2);
}

void SourcesManager::Source::setColor(double red, double green, double blue, double alpha)
{
    m_color.red =  Tools::clip(red, 0., 1.);
    m_color.green =  Tools::clip(green, 0., 1.);
    m_color.blue =  Tools::clip(blue, 0., 1.);
    m_color.alpha =  Tools::clip(alpha, 0., 1.);
}

void SourcesManager::Source::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

void SourcesManager::Source::setGroup(long aGroupIndex)
{
    for(int i = 0; i < m_groups.size(); i++)
    {
        if(m_groups[i] == aGroupIndex)
            return;
    }
    m_groups.push_back(aGroupIndex);
}

void SourcesManager::Source::setMute(long aValue)
{
    m_mute = Tools::clip(aValue, (long)0, long(1));
}

void SourcesManager::Source::removeGroup(long aGroupIndex)
{
    for(int i = 0; i < m_groups.size(); i++)
    {
        if(m_groups[i] == aGroupIndex)
        {
            for(int j = i; j < m_groups.size() - 1; j++)
            {
                m_groups[j] = m_groups[j+1];
            }
            m_groups.pop_back();
        }
    }
}

double SourcesManager::Source::getRadius()
{
    return m_coordinate_polar.radius;
}

double SourcesManager::Source::getAngle()
{
    return m_coordinate_polar.angle;
}

double SourcesManager::Source::getAbscissa()
{
    return Tools::abscisse(m_coordinate_polar.radius, m_coordinate_polar.angle + CICM_PI2);
}

double SourcesManager::Source::getOrdinate()
{
    return Tools::ordinate(m_coordinate_polar.radius, m_coordinate_polar.angle + CICM_PI2);
}

color SourcesManager::Source::getColor()
{
    return m_color;
}

long SourcesManager::Source::getExistence()
{
    return m_exist;
}

std::string SourcesManager::Source::getDescription()
{
    return m_description;
}

long SourcesManager::Source::getNumberOfGroups()
{
    return m_groups.size();
}

long SourcesManager::Source::getGroupIndex(long anIndex)
{
    if(anIndex < m_groups.size() && anIndex >= 0)
        return m_groups[anIndex];
    else
        return -1;
}

long SourcesManager::Source::getMute()
{
    return m_mute;
}

SourcesManager::Source::~Source()
{
    m_groups.clear();
}