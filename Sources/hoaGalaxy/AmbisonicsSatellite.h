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


#ifndef DEF_AMBISONICSSATELLITE
#define DEF_AMBISONICSSATELLITE

#include "AmbisonicsStar.h"

class Satellite : public Star
{
private:    
    double                  m_radius_principal;
    double                  m_radius_secondary;
    double                  m_elliptic_angle;
    double                  m_starting_angle;
    double                  m_rotation_time;
    
    Star*                   m_central_star;
public:
    Satellite(Star* aCentralStar, double anEllipticAngle = 0., double aRadiusPrincipal = 0., double aRadiusSecondary = 0.);

    void setEllipse(double anEllipticAngle, double aRadiusPrincipal, double aRadiusSecondary);
	void setRadiusPrincipal(double aRadius);
    void setRadiusSecondary(double aRadius);
    void setEllipticAngle(double anAngle);
    void setEllipseCoordinatePolar(double anAbscissa, double anOrdinate);
    void setEllipseCoordinateCartesian(double anAbscissa, double anOrdinate);
    
    void setStartingAngle(double anAngle);
    void setRotationTime(double aTimeInMs);
    
    double getRadiusPrincipal();
    double getRadiusSecondary();
    double getEllipticAngle();
    double getStartingAngle();
    double getRotationTime();
    
    void tick()
    {
        
    }
    
	~Satellite();
};

#endif


