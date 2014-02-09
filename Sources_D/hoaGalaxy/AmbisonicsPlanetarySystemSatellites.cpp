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
/******** SATELLITES FUNCTION *********/
/**************************************/

bool PlanetarySystem::createSatelliteCoordinatesElliptic(long anIndex, long aCentralStarIndex, double anEllipticAngle, double aRadiusPrincipal, double aRadiusSecondary)
{
    if(m_satellites[anIndex])
    {
        m_satellites[anIndex]->setEllipse(anEllipticAngle, aRadiusPrincipal, aRadiusSecondary);
        return TRUE;
    }
    else
    {
        if(aCentralStarIndex == 0)
        {
            m_satellites[anIndex] = new Satellite(m_sun, anEllipticAngle, aRadiusPrincipal, aRadiusSecondary);
            return TRUE;
        }
        else if(aCentralStarIndex >= 1 && m_satellites[aCentralStarIndex])
        {
            if(m_satellites[anIndex])
                m_satellites[anIndex]->setEllipse(anEllipticAngle, aRadiusPrincipal, aRadiusSecondary);
            else
                m_satellites[anIndex] = new Satellite(m_satellites[aCentralStarIndex], anEllipticAngle, aRadiusPrincipal, aRadiusSecondary);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

bool PlanetarySystem::createSatelliteCoordinatesPolar(long anIndex, long aCentralStarIndex, double aRadius, double anAngle)
{
    return FALSE;
}

bool PlanetarySystem::createSatelliteCoordinatesCartesian(long anIndex, long aCentralStarIndex, double anAbscissa, double anOrdinate)
{
    return FALSE;
}

/*
bool PlanetarySystem::setSatelliteCoordinatesElliptic(long anIndex, double anEllipticAngle, double aRadiusPrincipal, double aRadiusSecondary)
{
    if(m_satellites[anIndex])
    {
        m_satellites[anIndex]->setEllipse(anEllipticAngle, aRadiusPrincipal, aRadiusSecondary);
        return TRUE;
    }
    else
    {
        if(aCentralStarIndex == 0)
        {
            m_satellites[anIndex] = new Satellite(m_sun, anEllipticAngle, aRadiusPrincipal, aRadiusSecondary);
            return TRUE;
        }
        else if(aCentralStarIndex >= 1 && m_satellites[aCentralStarIndex])
        {
            if(m_satellites[anIndex])
                m_satellites[anIndex]->setEllipse(anEllipticAngle, aRadiusPrincipal, aRadiusSecondary);
            else
                m_satellites[anIndex] = new Satellite(m_satellites[aCentralStarIndex], anEllipticAngle, aRadiusPrincipal, aRadiusSecondary);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

bool PlanetarySystem::setSatellitesCoordinatesPolar(long anIndex, long aCentralStarIndex, double aRadius, double anAngle)
{
   return FALSE;
}

bool PlanetarySystem::setSatellitesCoordinatesCartesian(long anIndex, long aCentralStarIndex, double anAbscissa, double anOrdinate)
{
    return FALSE;
}

void PlanetarySystem::removeSatellites()
{
    ;
}
*/






