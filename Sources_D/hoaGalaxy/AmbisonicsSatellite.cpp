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

#include "AmbisonicsSatellite.h"

Satellite::Satellite(Star* aCentralStar, double anEllipticAngle, double aRadiusPrincipal, double aRadiusSecondary) : Star(0., 0.)
{
    m_central_star = aCentralStar;
    m_radius_principal = 0.;
    m_radius_secondary = 0.;
    m_elliptic_angle   = 0.;
    m_starting_angle   = 0.;
    m_rotation_time    = 1000.;
    setEllipse(aRadiusPrincipal, aRadiusSecondary, anEllipticAngle);
}

void Satellite::setEllipse(double anEllipticAngle, double aRadiusPrincipal, double aRadiusSecondary)
{
    setEllipticAngle(anEllipticAngle);
    setRadiusPrincipal(aRadiusPrincipal);
    setRadiusSecondary(aRadiusSecondary);
}

void Satellite::setRadiusPrincipal(double aRadius)
{
    if(m_galaxy_limit >= 0)
        m_radius_principal = Tools::clip(aRadius, 0., m_galaxy_limit - m_central_star->getRadius());
    else
        m_radius_principal = Tools::clip_min(aRadius, 0.);
    
    if(m_radius_principal < m_radius_secondary)
    {
        double aRadius = m_radius_principal;
        m_radius_principal = m_radius_secondary;
        setRadiusSecondary(aRadius);
        setEllipticAngle(m_elliptic_angle+CICM_PI2);
        setStartingAngle(m_starting_angle-CICM_PI2);
    }
}

void Satellite::setRadiusSecondary(double aRadius)
{
    
}

void Satellite::setEllipticAngle(double anAngle)
{
    m_elliptic_angle = Tools::radian_wrap(anAngle);
}

void setEllipseCoordinatePolar(double anAbscissa, double anOrdinate)
{
    
}

void setEllipseCoordinateCartesian(double anAbscissa, double anOrdinate)
{
    
}

void Satellite::setStartingAngle(double anAngle)
{
    
}

void Satellite::setRotationTime(double aTimeInMs)
{
    
}

double Satellite::getRadiusPrincipal()
{
    return m_radius_principal;
}

double Satellite::getRadiusSecondary()
{
    return m_radius_secondary;
}

double Satellite::getEllipticAngle()
{
    return m_elliptic_angle;
}

double Satellite::getStartingAngle()
{
    return m_starting_angle;
}

double Satellite::getRotationTime()
{
    return m_rotation_time;
}


Satellite::~Satellite()
{
    ;
}