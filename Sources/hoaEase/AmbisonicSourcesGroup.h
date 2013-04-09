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

class SourcesGroup
{
	
private:
    std::vector <Source*>   m_sources;
    std::string             m_description;
    long                    m_exist;
public:
	SourcesGroup(std::string aDescription = "");
    
    void setDescription(std::string aDescription);
    void addSource(Source* aSource);
    void removeSource(Source* aSource);
    void shiftPolar(coordinatesPolar polarCoordinates);
	void shiftPolar(double aRadius, double anAngle);
    void shiftRadius(double aRadius);
    void shiftAngle(double anAngle);
    void shiftCartesian(coordinatesCartesian cartesianCoordinates);
    void shiftCartesian(double anAbscissa, double anOrdinate);
    void shiftAbscissa(double anAbscissa);
    void shiftOrdinate(double anOrdinate);
    
	~SourcesGroup();
};

#endif
