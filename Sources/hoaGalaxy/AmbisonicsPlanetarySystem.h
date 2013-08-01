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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef DEF_AMBISONICSPLANETARYSYSTEM
#define DEF_AMBISONICSPLANETARYSYSTEM

#include "AmbisonicsSatellite.h"
#include "AmbisonicsSun.h"

class PlanetarySystem
{
private:
    
    Sun*                                   m_sun;
    std::map<int, Satellite*>              m_satellites;
    std::map<int, Satellite*>::iterator    m_iterator;
    
    color           m_color;
    std::string     m_description;
    double          m_galaxy_limit;
    
public:
    PlanetarySystem(double aSunRadius = 0., double anSunAngle = 0., double aGalaxyLimit = -1.);
    
    /**************************************/
    /********** GLOBAL FUNCTION ***********/
    /**************************************/
    
    void setColor(double red, double green, double blue, double alpha);
    void setDescription(std::string aDescription);
    void setMuted(bool muted);
    void resizeSystem(double aRadius);
    void rotateSystem(double aAngle);
    
    color       getColor();
    std::string getDescription();
    bool        getMuted();
    void        getSize();
    void        getAngle();         
    
    /**************************************/
    /************ SUN FUNCTION ************/
    /**************************************/
    
    void setSunCoordinatesPolar(double aRadius, double anAngle);
    void setSunRadius(double aRadius);
    void setSunAngle(double anAngle);
    void setSunCoordinatesCartesian(double anAbscissa, double anOrdinate);
    void setSunAbscissa(double anAbscissa);
    void setSunOrdinate(double anOrdinate);
    
    void setSunColor(double red, double green, double blue, double alpha);
    void setSunDescription(std::string aDescription);
    void setSunMuted(bool muted);
    void setSunGalaxyLimit(double aGalaxyLimit);
    
    double      getSunRadius();
    double      getSunAngle();
    double      getSunAbscissa();
    double      getSunOrdinate();
    color       getSunColor();
    std::string getSunDescription();
    bool        getSunMuted();
    double      getSunGalaxyLimit();
    double      getSunDistanceToGalaxyLimit(double anAngle);
    
    /**************************************/
    /******** SATELLITES FUNCTION *********/
    /**************************************/
    
    bool createSatelliteCoordinatesElliptic(long anIndex, long anCentralStarIndex = 0, double anEllipticAngle = 0., double aRadiusPrincipal = 0., double aRadiusSecondary = 0.);
    bool createSatelliteCoordinatesPolar(long anIndex, long anCentralStarIndex = 0, double aRadius = 0., double anAngle = 0.);
    bool createSatelliteCoordinatesCartesian(long anIndex, long anCentralStarIndex = 0, double anAbscissa = 0., double anOrdinate = 0.);
    
    void setSatelliteCoordinatesElliptics(long anIndex, double anEllipticAngle, double aRadiusPrincipal, double aRadiusSecondary);
    void setSatelliteEllipticAngle(long anIndex, double anEllipticAngle);
    void setSatelliteRadiusPrincipal(long anIndex, double aRadiusPrincipal);
    void setSatelliteRadiusSecondary(long anIndex, double anEllipticAngle);
    void setSatelliteCoordinatesPolar(long anIndex, double aRadius = 0., double anAngle = 0.);
    void setSatelliteCoordinatesCartesian(long anIndex, double anAbscissa = 0., double anOrdinate = 0.);
    
    bool changeSatelliteCentralStar(long anIndex, long anCentralStarIndex);
    bool duplicateSatelliteToOtherCentralStar(long anIndex, long anCentralStarIndex);
    void removeSatellite(long anIndex);
    
	~PlanetarySystem();
};

#endif


