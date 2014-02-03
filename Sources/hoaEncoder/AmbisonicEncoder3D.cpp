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

#include "AmbisonicEncoder3D.h"

AmbisonicEncoder3D::AmbisonicEncoder3D(long anOrder, long aVectorSize, long aSamlingRate) : Ambisonic3D(anOrder, aVectorSize, aSamlingRate)
{
    m_number_of_inputs = 3;
    
    m_azimuth_matrix = new cicm_vector_double[m_number_of_harmonics];
    m_elevation_matrix = new cicm_vector_double[m_number_of_harmonics];
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        cicm_malloc_vec_d(m_azimuth_matrix[i], NUMBEROFCIRCLEPOINTS);
        cicm_malloc_vec_d(m_elevation_matrix[i], NUMBEROFCIRCLEPOINTS);
    }
    cicm_malloc_vec_f(m_azimuth_float, m_number_of_harmonics);
    cicm_malloc_vec_d(m_azimuth_double, m_number_of_harmonics);
    cicm_malloc_vec_f(m_elevation_float, m_number_of_harmonics);
    cicm_malloc_vec_d(m_elevation_double, m_number_of_harmonics);
    
    
    m_index_vector = new int[m_vector_size];
    cicm_malloc_vec_d(m_vector_double, m_vector_size);
    cicm_malloc_vec_f(m_vector_float, m_vector_size);
    
    computeMatrices();
    setCoordinates(0., 0.);
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
/*
void AmbisonicEncoder3D::computeNormalization()
{
    for(long i = 0; i < m_number_of_harmonics; i++)
    {
        double factor = (2 * getHarmonicOrder(i) + 1) / (CICM_2PI * 2);
        m_normalization_double[i] = factor * Tools::factoriel(getHarmonicOrder(i) - getHarmonicIndex(i)) / Tools::factoriel(getHarmonicOrder(i) + getHarmonicIndex(i));
        if (getHarmonicIndex(i) != 0)
        {
            m_normalization_double[i] *= sqrt(2.);
        }
        m_normalization_float[i] = m_normalization_double[i];
    }
}
*/
void AmbisonicEncoder3D::setCoordinates(double anAzimuth, double anElevation)
{
    setAzimuth(anAzimuth);
    setElevation(anElevation);
}

void AmbisonicEncoder3D::setAzimuth(double anAzimuth)
{
    int index = (int)((Tools::radian_wrap(anAzimuth) / CICM_2PI) * NUMBEROFCIRCLEPOINTS);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_azimuth_float[i] = m_azimuth_double[i] = m_azimuth_matrix[i][index];
    }
}

void AmbisonicEncoder3D::setElevation(double anElevation)
{
	int index = (int)((Tools::radian_wrap(anElevation) / CICM_2PI) * NUMBEROFCIRCLEPOINTS);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_elevation_float[i] = m_elevation_double[i] = m_elevation_matrix[i][index];
    }
}

void AmbisonicEncoder3D::setVectorSize(long aVectorSize)
{
    Ambisonic3D::setVectorSize(aVectorSize);
    
    if(m_index_vector)
        free(m_index_vector);
    if(m_vector_double)
        cicm_free(m_vector_double);
    if(m_vector_float)
        cicm_free(m_vector_float);
    
    m_index_vector = new int[m_vector_size];
    cicm_malloc_vec_d(m_vector_double, m_vector_size);
    cicm_malloc_vec_f(m_vector_float, m_vector_size);
}

std::string AmbisonicEncoder3D::getInputName(long anIndex)
{
    if(anIndex == 0)
        return "Input";
    else if(anIndex == 1)
        return "Azimuth";
    else if(anIndex == 2)
        return "Elevation";
    else
        return "None";
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
    cicm_free(m_azimuth_float);
    cicm_free(m_azimuth_double);
    cicm_free(m_elevation_float);
    cicm_free(m_elevation_double);
    cicm_free(m_vector_float);
    cicm_free(m_vector_double);
}