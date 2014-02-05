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
        m_increment         = (double)(NUMBEROFCIRCLEPOINTS * m_number_of_harmonics) / CICM_2PI;
        m_azimuth_matrix    = new double*[NUMBEROFCIRCLEPOINTS];
        m_elevation_matrix  = new double*[NUMBEROFCIRCLEPOINTS];
        
        for(int j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
        {
            m_azimuth_matrix[j]    = new double[m_number_of_harmonics];
            m_elevation_matrix[j]  = new double[m_number_of_harmonics];
        }
        
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            double theta;
            double phi;
            int band     = getHarmonicBand(i);
            int argument = getHarmonicArgument(i);
            if(argument == 0)
            {
                for(int j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
                {
                    theta = (double)j / (double)NUMBEROFCIRCLEPOINTS * CICM_2PI;
                    if(theta > CICM_PI)
                        theta = CICM_2PI - theta;
                   
                    m_azimuth_matrix[j][i] = 1.;
                    m_elevation_matrix[j][i] = legendrePolynomial(band, 0, cos(theta));
                }
            }
            else if(argument > 0 )
            {
                for(int j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
                {
                    phi = (double)j / (double)NUMBEROFCIRCLEPOINTS * CICM_2PI;
                    theta = phi;
                    if(theta > CICM_PI)
                        theta = CICM_2PI - theta;
              
                    m_azimuth_matrix[j][i] = cos((double)argument * phi);
                    m_elevation_matrix[j][i] = legendrePolynomial(band, argument, cos(theta));
                }
            }
            else
            {
                for(int j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
                {
                    phi = (double)j / (double)NUMBEROFCIRCLEPOINTS * CICM_2PI;
                    theta = phi;
                    if(theta > CICM_PI)
                        theta = CICM_2PI - theta;
                  
                    m_azimuth_matrix[j][i] = sin((double)-argument * phi);
                    m_elevation_matrix[j][i] = legendrePolynomial(band, -argument, cos(theta));
                }
            }
        }
    }
    
    void Encoder::setAzimuth(const double azimuth)
    {
        m_azimuth = Tools::radian_wrap(azimuth) / CICM_2PI * (double)NUMBEROFCIRCLEPOINTS;
    }
    
    void Encoder::setElevation(const double elevation)
    {
        m_elevation = Tools::radian_wrap(elevation)  / CICM_2PI * (double)NUMBEROFCIRCLEPOINTS;
    }
    
    void Encoder::process(const float input, float* outputs)
    {
        for(int i = 0; i < m_number_of_harmonics; i++)
            outputs[i] = input * m_azimuth_matrix[m_azimuth][i] * m_elevation_matrix[m_elevation][i];
    }
    
    void Encoder::process(const double input, double* outputs)
    {
        for(int i = 0; i < m_number_of_harmonics; i++)
            outputs[i] = input * m_azimuth_matrix[m_azimuth][i] * m_elevation_matrix[m_elevation][i];
    }
    
    Encoder::~Encoder()
    {
        delete [] m_azimuth_matrix;
        delete [] m_elevation_matrix;
    }
}

