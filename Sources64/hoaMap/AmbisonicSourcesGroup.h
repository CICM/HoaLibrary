/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
