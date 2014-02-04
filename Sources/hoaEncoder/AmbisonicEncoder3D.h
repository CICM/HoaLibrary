/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
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

#ifndef DEF_AMBISONICENCODER3D
#define DEF_AMBISONICENCODER3D

#include "../HoaAmbisonics/Ambisonic3D.h"

class AmbisonicEncoder3D : public Ambisonic3D
{
	
private:
    float**  m_azimuth_matrix;
    float**  m_elevation_matrix;
    float*   m_azimuth;
    float*   m_elevation;
    void computeMatrices();
    
public:
	AmbisonicEncoder3D(unsigned int order = 1);
    ~AmbisonicEncoder3D();
    
	inline void	setAzimuth(const float azimuth);
    inline void	setElevation(const float elevation);
    inline void setCoordinates(const float azimuth, const float elevation);
    inline void process(const float input, float* outputs);
};
#endif