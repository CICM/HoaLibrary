/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "AmbisonicsStar.h"

Star::Star(double aRadius, double anAngle, double aGalaxyLimit)
{
    setCoordinatesPolar(aRadius, anAngle);
    setColor(0.2, 0.2, 0.2, 1.);
    setDescription("Star");
    setMuted(0);
    setGalaxyLimit(aGalaxyLimit);
}

void Star::setCoordinatesPolar(double aRadius, double anAngle)
{
    setRadius(aRadius);
    setAngle(anAngle);
}

void Star::setRadius(double aRadius)
{
    if(m_galaxy_limit >= 0)
    {
        if(aRadius > m_galaxy_limit)
            aRadius = m_galaxy_limit;
    }
    m_radius = Tools::clip_min(aRadius, 0.);
}

void Star::setAngle(double anAngle)
{
    m_angle = Tools::radian_wrap(anAngle);
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

void Star::setGalaxyLimit(double aGalaxyLimit)
{
    m_galaxy_limit = aGalaxyLimit;
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

void Star::setMuted(bool muted)
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
    return Tools::abscissa(m_radius, m_angle + CICM_PI2);
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

bool Star::getMuted()
{
    return m_muted;
}

double Star::getGalaxyLimit()
{
    return m_galaxy_limit;
}

double Star::getDistanceToGalaxyLimit(double anAngle)
{
    anAngle = Tools::radian_wrap(anAngle);
    if(m_galaxy_limit >= 0.)
    {
        return Tools::distance_euclidean(getAbscissa(), getOrdinate(), Tools::abscissa(m_galaxy_limit, anAngle+ CICM_PI2), Tools::ordinate(m_galaxy_limit, anAngle+ CICM_PI2));
    }
    else
        return -1;
}

Star::~Star()
{
    ;
}

