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


