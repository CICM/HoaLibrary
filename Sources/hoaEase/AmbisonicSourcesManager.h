/*
 * AmbisonicSourcesManager.h
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



#ifndef DEF_AMBISONICSOURCESMANAGER
#define DEF_AMBISONICSOURCESMANAGER

#include "cicmTools.h"
#include "AmbisonicSource.h"
#include "AmbisonicSourcesGroup.h"

class SourcesManager
{
	
private:
    std::vector <Source*>       m_sources;
    std::vector <SourcesGroup*> m_groups;
    
public:
	SourcesManager();
    
    void remove(long anIndex);
    void setCoordinatesPolar(long anIndex, coordinatesPolar polarCoordinates);
	void setCoordinatesPolar(long anIndex, double aRadius, double anAngle);
	void setRadius(long anIndex, double aRadius);
    void setAngle(long anIndex, double anAngle);
    void setCoordinatesCartesian(long anIndex, coordinatesCartesian cartesianCoordinates);
    void setCoordinatesCartesian(long anIndex, double anAbscissa, double anOrdinate);
	void setAbscissa(long anIndex, double anAbscissa);
	void setOrdinate(long anIndex, double anOrdinate);
    void setColor(long anIndex, color aColor);
	void setDescription(long anIndex, std::string aDescription);
	
    long getMaximumIndexOfSource();
    long getNumberOfSources();
    long getSourceExistence(long anIndex);
    coordinatesPolar getCoordinatesPolar(long anIndex);
	double getRadius(long anIndex);
	double getAngle(long anIndex);
    coordinatesCartesian getCoordinatesCartesian(long anIndex);
	double getAbscissa(long anIndex);
	double getOrdinate(long anIndex);
    color getColor(long anIndex);
    std::string getDescription(long anIndex);
	
	~SourcesManager();
};

#endif
