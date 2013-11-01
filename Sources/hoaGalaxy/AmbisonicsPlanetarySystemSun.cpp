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

#include "AmbisonicsPlanetarySystem.h"

/**************************************/
/************ SUN FUNCTION ************/
/**************************************/

void PlanetarySystem::setSunCoordinatesPolar(double aRadius, double anAngle)
{
    m_sun->setCoordinatesPolar(aRadius, anAngle);
}

void PlanetarySystem::setSunRadius(double aRadius)
{
    m_sun->setRadius(aRadius);
}

void PlanetarySystem::setSunAngle(double anAngle)
{
    m_sun->setAngle(anAngle);
}

void PlanetarySystem::setSunCoordinatesCartesian(double anAbscissa, double anOrdinate)
{
    m_sun->setCoordinatesCartesian(anAbscissa, anOrdinate);
}

void PlanetarySystem::setSunAbscissa(double anAbscissa)
{
    m_sun->setAbscissa(anAbscissa);
}

void PlanetarySystem::setSunOrdinate(double anOrdinate)
{
    m_sun->setOrdinate(anOrdinate);
}

void PlanetarySystem::setSunColor(double red, double green, double blue, double alpha)
{
    m_sun->setColor(red, green, blue, alpha);
}

void PlanetarySystem::setSunDescription(std::string aDescription)
{
    m_sun->setDescription(aDescription);
}

void PlanetarySystem::setSunMuted(bool muted)
{
    m_sun->setMuted(muted);
}

double PlanetarySystem::getSunRadius()
{
    return m_sun->getRadius();
}

double PlanetarySystem::getSunAngle()
{
    return m_sun->getAngle();
}

double PlanetarySystem::getSunAbscissa()
{
    return m_sun->getAbscissa();
}

double PlanetarySystem::getSunOrdinate()
{
    return m_sun->getOrdinate();
}

color PlanetarySystem::getSunColor()
{
    return m_sun->getColor();
}

std::string PlanetarySystem::getSunDescription()
{
    return m_sun->getDescription();
}

bool PlanetarySystem::getSunMuted()
{
    return m_sun->getMuted();
}

double PlanetarySystem::getSunGalaxyLimit()
{
    return m_sun->getGalaxyLimit();
}

double PlanetarySystem::getSunDistanceToGalaxyLimit(double anAngle)
{
    return m_sun->getDistanceToGalaxyLimit(anAngle);
}


