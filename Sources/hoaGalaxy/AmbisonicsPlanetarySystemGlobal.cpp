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
/********** GLOBAL FUNCTION ***********/
/**************************************/

PlanetarySystem::PlanetarySystem(double aSunRadius, double anSunAngle, double aGalaxyLimit)
{
    m_galaxy_limit = aGalaxyLimit;
    m_sun = new Sun(aSunRadius, anSunAngle, aGalaxyLimit);
}

void PlanetarySystem::setColor(double red, double green, double blue, double alpha)
{
    m_color.red =  Tools::clip(red, 0., 1.);
    m_color.green =  Tools::clip(green, 0., 1.);
    m_color.blue =  Tools::clip(blue, 0., 1.);
    m_color.alpha =  Tools::clip(alpha, 0., 1.);
}

void PlanetarySystem::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

void PlanetarySystem::setMuted(bool muted)
{
    m_sun->setMuted(muted);
    for(m_iterator = m_satellites.begin(); m_iterator != m_satellites.end(); m_iterator++)
    {
        m_iterator->second->setMuted(muted);
    }
}

color PlanetarySystem::getColor()
{
    return m_color;
}

std::string PlanetarySystem::getDescription()
{
    return m_description;
}

bool PlanetarySystem::getMuted()
{
    if(!m_sun->getMuted())
        return 0;
    else
    {
        for (m_iterator = m_satellites.begin(); m_iterator != m_satellites.end(); m_iterator++)
        {
            if(m_iterator->second->getMuted() == 0)
                return 0;
        }
    }
    return 1;
}

PlanetarySystem::~PlanetarySystem()
{
    delete m_sun;
    m_satellites.clear();
}