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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicsStar.h"

Star::Star(double aRadius, double anAngle, double aMaximumRadius)
{
    setCoordinatesPolar(aRadius, anAngle);
    setColor(0.2, 0.2, 0.2, 1.);
    setDescription("Star");
    setMute(0);
    setMaximumRadius(aMaximumRadius);
}

void Star::setCoordinatesPolar(double aRadius, double anAngle)
{
    setRadius(aRadius);
    setAngle(anAngle);
}

void Star::setRadius(double aRadius)
{
    if(m_maximum_radius >= 0)
    {
        if(aRadius > m_maximum_radius)
            aRadius = m_maximum_radius;
    }
    m_radius = Tools::clip_min(aRadius, 0.);
}

void Star::setAngle(double anAngle)
{
    m_angle = Tools::radianWrap(anAngle);
}

void Star::setCoordinatesCartesian(double anAbscissa, double anOrdinate)
{
    setRadius(Tools::radius(anAbscissa, anOrdinate));
    setAngle(Tools::angle(anAbscissa, anOrdinate) - CICM_PI2);
}

void Star::setAbscissa(double anAbscissa)
{
    double ordinate = getOrdinate();
    setRadius(Tools::radius(anAbscissa, ordinate));
    setAngle(Tools::angle(anAbscissa, ordinate) - CICM_PI2);
}

void Star::setOrdinate(double anOrdinate)
{
    double abscissa = getAbscissa();
    setRadius(Tools::radius(abscissa, anOrdinate));
    setAngle(Tools::angle(abscissa, anOrdinate) - CICM_PI2);
}

void Star::setMaximumRadius(double aMaximumRadius)
{
    m_maximum_radius = aMaximumRadius;
    setRadius(m_radius);
    setAngle(m_angle);
}

void Star::setColor(double red, double green, double blue, double alpha)
{
    m_color.red =  Tools::clip(red, 0., 1.);
    m_color.green =  Tools::clip(green, 0., 1.);
    m_color.blue =  Tools::clip(blue, 0., 1.);
    m_color.alpha =  Tools::clip(alpha, 0., 1.);
}

void Star::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

void Star::setMute(bool muted)
{
    m_muted = Tools::clip(muted, 0, 1);
}

double Star::getRadius()
{
    return m_radius;
}

double Star::getAngle()
{
    return m_angle;
}

double Star::getAbscissa()
{
    return Tools::abscisse(m_radius, m_angle + CICM_PI2);
}

double Star::getOrdinate()
{
    return Tools::ordinate(m_radius, m_angle + CICM_PI2);
}

color Star::getColor()
{
    return m_color;
}

std::string Star::getDescription()
{
    return m_description;
}

bool Star::getMute()
{
    return m_muted;
}

double Star::getMaximumRadius()
{
    return m_maximum_radius;
}

double Star::getDistanceToBorder(double anAngle)
{
    anAngle = Tools::radianWrap(anAngle);
    if(m_maximum_radius >= 0.)
        return Tools::distance_euclidean(getAbscissa(), getOrdinate(), Tools::abscisse(m_maximum_radius, anAngle+ CICM_PI2), Tools::ordinate(m_maximum_radius, anAngle+ CICM_PI2));
    else
        return -1;
}

Star::~Star()
{
    ;
}

