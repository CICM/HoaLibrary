/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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