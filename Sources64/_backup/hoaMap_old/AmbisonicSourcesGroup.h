/*
 * AmbisonicSourcesGroup.h
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



#ifndef DEF_AMBISONICSOURCESGROUP
#define DEF_AMBISONICSOURCESGROUP

#include "cicmTools.h"
#include "AmbisonicSource.h"
/*
class SourcesGroup
{
	
private:
    std::vector <Source*>   m_sources;
    std::string             m_description;
    long                    m_exist;
    color                   m_color;
    coordinatesCartesian    m_centroid;
    
    void computeCentroid();
    void shiftPolar(coordinatesPolar polarCoordinates);
	void shiftPolar(double aRadius, double anAngle);
    void shiftRadius(double aRadius);
    void shiftAngle(double anAngle);
    void shiftCartesian(coordinatesCartesian cartesianCoordinates);
    void shiftCartesian(double anAbscissa, double anOrdinate);
    void shiftAbscissa(double anAbscissa);
    void shiftOrdinate(double anOrdinate);
public:
	SourcesGroup(long deadOrAlive, std::string aDescription = "");
    
    void setExistence(long deadOrAlive);
    void setDescription(std::string aDescription);
    void setColor(color aColor);
    void addSource(Source* aSource);
    void sourceHasMoved(Source* aSource);
    void removeSource(Source* aSource);
    
    void setCoordinatesPolar(coordinatesPolar polarCoordinates);
	void setCoordinatesPolar(double aRadius, double anAngle);
	void setRadius(double aRadius);
    void setAngle(double anAngle);
    void setCoordinatesCartesian(coordinatesCartesian cartesianCoordinates);
    void setCoordinatesCartesian(double anAbscissa, double anOrdinate);
	void setAbscissa(double anAbscissa);
	void setOrdinate(double anOrdinate);
    
    void setRelativeCoordinatesPolar(coordinatesPolar polarCoordinates);
	void setRelativeCoordinatesPolar(double aRadius, double anAngle);
	void setRelativeRadius(double aRadius);
    void setRelativeAngle(double anAngle);

    long   getExistence();
    coordinatesPolar        getCoordinatesPolar();
	double getRadius();
	double getAngle();
    coordinatesCartesian    getCoordinatesCartesian();
	double getAbscissa();
	double getOrdinate();
    long getNumberOfSources();
    std::string getDescription();
    color  getColor();
    
	~SourcesGroup();
};
*/
#endif
