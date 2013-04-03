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

#include "AmbisonicSource.h"

Source::Source(long deadOrAlive, double aRadius, double anAngle, color aColor, std::string aDescription)
{
    m_exist = Tools::clip(deadOrAlive, (long)0, (long)1);
    setRadius(aRadius);
    setAngle(anAngle);
    setColor(aColor);
    setDescription(aDescription);
}

Source::Source(long deadOrAlive, coordinatesPolar polarCoordinates, color aColor, std::string aDescription)
{
    m_exist = Tools::clip(deadOrAlive, (long)0, (long)1);
    setCoordinatesPolar(polarCoordinates);
    setColor(aColor);
    setDescription(aDescription);
}

Source::Source(long deadOrAlive, coordinatesCartesian cartesianCoordinates, color aColor, std::string aDescription)
{
    m_exist = Tools::clip(deadOrAlive, (long)0, (long)1);
    setCoordinatesCartesian(cartesianCoordinates);
    setColor(aColor);
    setDescription(aDescription);
}

void Source::setExistence(long deadOrAlive)
{
    m_exist = Tools::clip(deadOrAlive, (long)0, (long)1);
}

void Source::setCoordinatesPolar(coordinatesPolar polarCoordinates)
{
    setRadius(polarCoordinates.radius);
    setAngle(polarCoordinates.angle);
}

void Source::setCoordinatesPolar(double aRadius, double anAngle)
{
    setRadius(aRadius);
    setAngle(anAngle);
}

void Source::setRadius(double aRadius)
{
    m_coordinate_polar.radius = Tools::clip_min(aRadius, 0.);
    m_coordinate_cartesian.x = Tools::abscisse(m_coordinate_polar.radius, m_coordinate_polar.angle + CICM_PI2);
    m_coordinate_cartesian.y = Tools::ordinate(m_coordinate_polar.radius, m_coordinate_polar.angle + CICM_PI2);
}

void Source::setAngle(double anAngle)
{
    while (anAngle > CICM_2PI)
        anAngle -= CICM_2PI;
    while (anAngle < 0.)
        anAngle += CICM_2PI;
    m_coordinate_polar.angle = anAngle;
    m_coordinate_cartesian.x = Tools::abscisse(m_coordinate_polar.radius, m_coordinate_polar.angle + CICM_PI2);
    m_coordinate_cartesian.y = Tools::ordinate(m_coordinate_polar.radius, m_coordinate_polar.angle + CICM_PI2);
}

void Source::setCoordinatesCartesian(coordinatesCartesian cartesianCoordinates)
{
    setRadius(Tools::radius(cartesianCoordinates.x, cartesianCoordinates.y));
    setAngle(-Tools::angle(cartesianCoordinates.x, cartesianCoordinates.y) + CICM_PI2);
}

void Source::setCoordinatesCartesian(double anAbscissa, double anOrdinate)
{
    setRadius(Tools::radius(anAbscissa, anOrdinate));
    setAngle(-Tools::angle(anAbscissa, anOrdinate) + CICM_PI2);
}

void Source::setAbscissa(double anAbscissa)
{
    setRadius(Tools::radius(anAbscissa, m_coordinate_cartesian.y));
    setAngle(-Tools::angle(anAbscissa, m_coordinate_cartesian.y) + CICM_PI2);
}

void Source::setOrdinate(double anOrdinate)
{
    setRadius(Tools::radius(m_coordinate_cartesian.x, anOrdinate));
    setAngle(-Tools::angle(m_coordinate_cartesian.x, anOrdinate) + CICM_PI2);
}

void Source::setColor(color aColor)
{
    m_color.red =  Tools::clip(aColor.red, 0., 1.);
    m_color.green =  Tools::clip(aColor.green, 0., 1.);
    m_color.blue =  Tools::clip(aColor.blue, 0., 1.);
    m_color.alpha =  Tools::clip(aColor.alpha, 0., 1.);
}

void Source::setDescription(std::string aDescription)
{
    m_description = aDescription;
}

coordinatesPolar Source::getCoordinatesPolar()
{
    return m_coordinate_polar;
}

double Source::getRadius()
{
    return m_coordinate_polar.radius;
}

double Source::getAngle()
{
    return m_coordinate_polar.angle;
}

coordinatesCartesian Source::getCoordinatesCartesian()
{
    return m_coordinate_cartesian;
}

double Source::getAbscissa()
{
    return m_coordinate_cartesian.x;
}

double Source::getOrdinate()
{
    return m_coordinate_cartesian.y;
}

color Source::getColor()
{
    return m_color;
}

long Source::getExistence()
{
    return m_exist;
}

std::string Source::getDescription()
{
    return m_description;
}

Source::~Source()
{
	;
}