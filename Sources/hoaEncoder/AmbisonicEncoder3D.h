/* 
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DEF_AMBISONIC_ENCODER_3D
#define DEF_AMBISONIC_ENCODER_3D

#include "../HoaAmbisonics/Ambisonic3D.h"

/**
 The ambisonic 3D encoder.
 
 The encoder should be used to encode a signal in the spherical harmonics domain depending of an order of decomposition. It allows to control the azimuth and the elevation of the encoding.
 */
class AmbisonicEncoder3D : public Ambisonic3D
{
	
private:
    float**  m_azimuth_matrix;
    float**  m_elevation_matrix;
    float*   m_azimuth;
    float*   m_elevation;
    void computeMatrices();
    
public:
    /**	The decoder constructor.
     @param     order	The order, must be at least 1.
     */
	AmbisonicEncoder3D(unsigned int order = 1);
    
    /**	The decoder destructor.
     */
    ~AmbisonicEncoder3D();
    
    /**	This method set the angle of azimuth.
     @param     azimuth	The azimuth in radian, you should prefer to use it between 0 and 2 Pi.
     */
	void setAzimuth(const float azimuth);
    
    /**	This method set the angle of elevation.
     @param     azimuth	The elevation in radian, you should prefer to use it between 0 and 2 Pi.
     */
    void setElevation(const float elevation);
    
    /**	This method compute the encoding.
     @param     input	The input sample.
     @param     outputs The output array that contains the spherical harmonics samples.
     */
    void process(const float input, float* outputs);
};

#endif