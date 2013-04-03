/*
 * AmbisonicSource.h
 *
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


#ifndef DEF_AMBISONICSOURCE
#define DEF_AMBISONICSOURCE

#include "cicmTools.h"


class Source
{
	
private:
	coordinatesPolar        m_coordinate_polar;
    coordinatesCartesian    m_coordinate_cartesian;
	color                   m_color;
    std::string             m_description;
    long                    m_exist;
public:
    Source(long deadOrAlive, double aRadius = 0., double anAngle = 0., color aColor = color_black, std::string aDescription = "");
    Source(long deadOrAlive, coordinatesPolar polarCoordinates, color aColor = color_black, std::string aDescription = "");
    Source(long deadOrAlive, coordinatesCartesian cartesianCoordinates, color aColor = color_black, std::string aDescription = "");
    
    void setExistence(long deadOrAlive);
    void setCoordinatesPolar(coordinatesPolar polarCoordinates);
	void setCoordinatesPolar(double aRadius, double anAngle);
	void setRadius(double aRadius);
    void setAngle(double anAngle);
    void setCoordinatesCartesian(coordinatesCartesian cartesianCoordinates);
    void setCoordinatesCartesian(double anAbscissa, double anOrdinate);
	void setAbscissa(double anAbscissa);
	void setOrdinate(double anOrdinate);
    void setColor(color aColor);
	void setDescription(std::string aDescription);
	
    long   getExistence();
    coordinatesPolar        getCoordinatesPolar();
	double getRadius();
	double getAngle();
    coordinatesCartesian    getCoordinatesCartesian();
	double getAbscissa();
	double getOrdinate();
    color  getColor();
    std::string getDescription();
	
	~Source();
};

#endif