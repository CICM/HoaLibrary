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

#include "Hoa3DEncoder.h"

namespace Hoa3D
{
    Encoder::Encoder(unsigned int order) : Ambisonic(order)
    {
        m_elevation         = 0;
        m_azimuth           = 0;
        m_number_of_inputs  = 3;
        m_increment         = NUMBEROFCIRCLEPOINTS / CICM_2PI;
        m_azimuth_matrix    = new double[m_number_of_harmonics * NUMBEROFCIRCLEPOINTS];
        m_elevation_matrix  = new double[m_number_of_harmonics * NUMBEROFCIRCLEPOINTS];
    }
    
    void Encoder::setAzimuth(const double azimuth)
    {
        m_azimuth = Tools::radian_wrap(azimuth) * m_increment;
    }
    
    void Encoder::setElevation(const double elevation)
    {
        m_elevation = Tools::radian_wrap(elevation) * m_increment;
    }
    
    void Encoder::process(const float input, float* outputs)
    {
        int i;
        i = m_number_of_harmonics;
        /*
         while(--i)
         outputs[i] = input * m_azimuth_matrix[m_azimuth+i] * m_elevation_matrix[m_elevation+i];
         */
    }
    
    void Encoder::process(const double input, double* outputs)
    {
        int i;
        i = m_number_of_harmonics;
        /*
         while(--i)
         outputs[i] = input * m_azimuth_matrix[m_azimuth+i] * m_elevation_matrix[m_elevation+i];
         */
    }
    
    Encoder::~Encoder()
    {
        delete [] m_azimuth_matrix;
        delete [] m_elevation_matrix;
    }
}

