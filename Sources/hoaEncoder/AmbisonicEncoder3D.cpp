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

#include "AmbisonicEncoder3D.h"

AmbisonicEncoder3D::AmbisonicEncoder3D(unsigned int order) : Ambisonic3D(order)
{
    m_number_of_inputs = 3;
    
    m_azimuth_matrix = new float*[m_number_of_harmonics];
    m_elevation_matrix = new float*[m_number_of_harmonics];
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        cicm_malloc_vec_f(m_azimuth_matrix[i], NUMBEROFCIRCLEPOINTS);
        cicm_malloc_vec_f(m_elevation_matrix[i], NUMBEROFCIRCLEPOINTS);
    }
    cicm_malloc_vec_f(m_azimuth, m_number_of_harmonics);
    cicm_malloc_vec_f(m_elevation, m_number_of_harmonics);
    
    computeMatrices();
    setAzimuth(0.);
    setElevation(0.);
}

void AmbisonicEncoder3D::computeMatrices()
{
    // AZIMUTH //
    for(long i = 0; i < m_number_of_harmonics; i++)
    {
        for(long j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
        {
            double azimuth = (double)j * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS;
            if(getHarmonicIndex(i) == 0)
                m_azimuth_matrix[i][j] = 1.;
            else if(getHarmonicIndex(i) < 0)
                m_azimuth_matrix[i][j] =  sin(-getHarmonicIndex(i) * azimuth);
            else
                m_azimuth_matrix[i][j] =  cos(getHarmonicIndex(i) * azimuth);
        }
    }
    // ELEVATION //
    for(long i = 0; i < m_number_of_harmonics; i++)
    {
        for(long j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
        {
            double elevation = (double)j * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS;
            double pmm = 1.0;
            if(abs(getHarmonicIndex(i)) > 0)
            {
                double somx2 = sqrt((1. - cos(elevation)) * (1. + cos(elevation)));
                double fact = 1.;
                for(int i = 1; i <= getHarmonicIndex(i); ++i)
                {
                    pmm*= (-fact)*somx2;
                    fact+= 2.0;
                }
            }
            if(getHarmonicOrder(i) == abs(getHarmonicIndex(i)))
            {
                m_elevation_matrix[i][j] = pmm;
            }
            else
            {
                double pmmpl = cos(elevation) * (2. * abs(getHarmonicIndex(i)) + 1.) * pmm;
                if(getHarmonicOrder(i) == abs(getHarmonicIndex(i))+1)
                {
                    m_elevation_matrix[i][j] = pmmpl;
                }
                else
                {
                    double pll = 0.0;
                    for(int ll = abs(getHarmonicIndex(i))+2; ll <= getHarmonicOrder(i); ++ll)
                    {
                        pll = ((2. * ll - 1.) * cos(elevation) * pmmpl - (ll + getHarmonicIndex(i) - 1.) * pmm) / (ll - abs(getHarmonicIndex(i)));
                        pmm = pmmpl;
                        pmmpl = pll;
                    }
                    m_elevation_matrix[i][j] = pll;
                }
            
            }
        }
	}
    /*
    for(long i = 0; i < m_number_of_harmonics; i++)
    {
        double normalization;
        double factor = (double)(2 * getHarmonicOrder(i) + 1) / (CICM_2PI * 2);
        normalization = factor * Tools::factoriel(getHarmonicOrder(i) - getHarmonicIndex(i)) / Tools::factoriel(getHarmonicOrder(i) + getHarmonicIndex(i));
        if (getHarmonicIndex(i) != 0)
        {
            normalization *= sqrt(2.);
        }
        for(long j = 0; j < NUMBEROFCIRCLEPOINTS; j++)
        {
            m_azimuth_matrix[i][j] *= normalization;
            m_elevation_matrix[i][j] *= normalization;
        }
    }*/
}

void AmbisonicEncoder3D::setAzimuth(const float azimuth)
{
    int index = (int)((Tools::radian_wrap(azimuth) / CICM_2PI) * NUMBEROFCIRCLEPOINTS);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_azimuth[i] = m_azimuth_matrix[i][index];
    }
}

void AmbisonicEncoder3D::setElevation(const float elevation)
{
	int index = (int)((Tools::radian_wrap(elevation) / CICM_2PI) * NUMBEROFCIRCLEPOINTS);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_elevation[i]  = m_elevation_matrix[i][index];
    }
}

void AmbisonicEncoder3D::process(const float input, float* outputs)
{
    ;
}

AmbisonicEncoder3D::~AmbisonicEncoder3D()
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        cicm_free(m_azimuth_matrix[i]);
        cicm_free(m_elevation_matrix[i]);
    }
    cicm_free(m_azimuth_matrix);
    cicm_free(m_elevation_matrix);
    cicm_free(m_azimuth);
    cicm_free(m_elevation);
}