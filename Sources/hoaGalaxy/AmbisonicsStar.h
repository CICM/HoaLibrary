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


#ifndef DEF_AMBISONICSSTAR
#define DEF_AMBISONICSSTAR

#include "../hoaAmbisonics/Ambisonic.h"

class Star
{
protected:
    
    double          m_radius;
    double          m_angle;
	color           m_color;
    std::string     m_description;
    bool            m_muted;
    
    double          m_galaxy_limit;    
public:
    Star(double aRadius = 0., double anAngle = 0., double aGalaxyLimit = -1.);
    
    void setCoordinatesPolar(double aRadius, double anAngle);
    void setRadius(double aRadius);
    void setAngle(double anAngle);
    void setCoordinatesCartesian(double anAbscissa, double anOrdinate);
    void setAbscissa(double anAbscissa);
    void setOrdinate(double anOrdinate);
    
    void setColor(double red, double green, double blue, double alpha);
    void setDescription(std::string aDescription);
    void setMuted(bool muted);
    void setGalaxyLimit(double aGalaxyLimit);
    
    double      getRadius();
    double      getAngle();
    double      getAbscissa();
    double      getOrdinate();
    color       getColor();
    std::string getDescription();
    bool        getMuted();
    double      getGalaxyLimit();
    double      getDistanceToGalaxyLimit(double anAngle);

	
	~Star();
};

#endif


