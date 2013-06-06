/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "AmbisonicsMap.h"

AmbisonicsMap::AmbisonicsMap(long anOrder, long aVectorSize, long aRampSample) : Ambisonics(anOrder, aVectorSize)
{
	m_number_of_inputs		= 1;

    m_encoder   = new AmbisonicsEncoder(m_order);
    m_wider     = new AmbisonicsWider(m_order);
    m_line_one  = new CicmLine(aRampSample);
    m_line_two  = new CicmLine(aRampSample);
    m_line_thr  = new CicmLine(aRampSample);
    m_line_fou  = new CicmLine(aRampSample);
    
    Cicm_Vector_Float_Malloc(m_harmonics_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_harmonics_double, m_number_of_harmonics);
    
    m_harmonics_matrix_float  = new float*[m_number_of_harmonics];
    m_harmonics_matrix_double = new double*[m_number_of_harmonics];
    for (int i = 0; i < m_number_of_harmonics; i++)
    {
        Cicm_Vector_Float_Malloc(m_harmonics_matrix_float[i], 1);
        Cicm_Vector_Double_Malloc(m_harmonics_matrix_double[i], 1);
    }
    
    Cicm_Vector_Float_Malloc(m_gains_float, 1);
    Cicm_Vector_Float_Malloc(m_radius_float, 1);
    Cicm_Vector_Float_Malloc(m_azimuth_float, 1);
    Cicm_Vector_Float_Malloc(m_abscissa_float, 1);
    Cicm_Vector_Float_Malloc(m_ordinate_float, 1);
    
    Cicm_Vector_Double_Malloc(m_gains_double, 1);
    Cicm_Vector_Double_Malloc(m_radius_double, 1);
    Cicm_Vector_Double_Malloc(m_azimuth_double, 1);
    Cicm_Vector_Double_Malloc(m_abscissa_double, 1);
    Cicm_Vector_Double_Malloc(m_ordinate_double, 1);
    
    setVectorSize(aVectorSize);
    
    m_line_one->setCoefficientDirect(1.);
    m_line_two->setCoefficientAngleDirect(0.);
    m_line_thr->setCoefficientDirect(0.);
    m_line_fou->setCoefficientDirect(1.);
    setCoordinatesCartesianLine(0., 1.);
}


void AmbisonicsMap::setVectorSize(long aVectorSize)
{
    m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_encoder->setVectorSize(m_vector_size);
    m_wider->setVectorSize(m_vector_size);
    m_line_one->setVectorSize(m_vector_size);
    m_line_two->setVectorSize(m_vector_size);
    m_line_thr->setVectorSize(m_vector_size);
    m_line_fou->setVectorSize(m_vector_size);
    
    Cicm_Free(m_gains_double);
    Cicm_Free(m_gains_float);
    Cicm_Free(m_radius_float);
    Cicm_Free(m_radius_double);
    Cicm_Free(m_azimuth_float);
    Cicm_Free(m_azimuth_double);
    Cicm_Free(m_abscissa_double);
    Cicm_Free(m_abscissa_float);
    Cicm_Free(m_ordinate_float);
    Cicm_Free(m_ordinate_double);
    Cicm_Vector_Float_Malloc(m_gains_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_radius_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_azimuth_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_gains_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_radius_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_azimuth_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_abscissa_double, m_vector_size);
    Cicm_Vector_Float_Malloc(m_abscissa_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_ordinate_double, m_vector_size);
    Cicm_Vector_Float_Malloc(m_ordinate_float, m_vector_size);
    for (int i = 0; i < m_number_of_harmonics; i++)
    {
        Cicm_Free(m_harmonics_matrix_float[i]);
        Cicm_Free(m_harmonics_matrix_double[i]);
        Cicm_Vector_Float_Malloc(m_harmonics_matrix_float[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_harmonics_matrix_double[i], m_vector_size);
    }
}


void AmbisonicsMap::setCoordinatesPolar(double aRadius, double anAzimuth)
{
    m_radius = Tools::clip_min(aRadius, 0.);
    if(m_radius <= 1.)
    {
        m_gain = 1.;
        m_wide = m_radius;
    }
    else
    {
        m_gain = 1. / (m_radius * m_radius);
        m_wide = 1.;
    }
   
    m_azimuth = anAzimuth;
    
}

void AmbisonicsMap::setCoordinatesRadius(double aRadius)
{
    setCoordinatesPolar(m_azimuth, aRadius);
}

void AmbisonicsMap::setCoordinatesAzimuth(double anAzimuth)
{
    setCoordinatesPolar(anAzimuth, m_radius);
}

void AmbisonicsMap::setCoordinatesCartesian(double anAbscissa, double anOrdinate)
{
    m_abscissa = anAbscissa;
    m_ordinate = anOrdinate;
    setCoordinatesPolar(Tools::radius(m_abscissa, m_ordinate), Tools::angle(m_abscissa, m_ordinate) - CICM_PI2);
}

void AmbisonicsMap::setCoordinatesAbscissa(double anAbscissa)
{
    m_abscissa = anAbscissa;
    setCoordinatesPolar(Tools::radius(m_abscissa, m_ordinate), Tools::angle(m_abscissa, m_ordinate) - CICM_PI2);
}

void AmbisonicsMap::setCoordinatesOrdinate(double anOrdinate)
{
    m_ordinate = anOrdinate;
    setCoordinatesPolar(Tools::radius(m_abscissa, m_ordinate), Tools::angle(m_abscissa, m_ordinate) - CICM_PI2);
}

void AmbisonicsMap::setCoordinatesPolarLine(double aRadius, double anAzimuth)
{
    aRadius = Tools::clip_min(aRadius, 0.);
    m_line_one->setCoefficient(aRadius);
    m_line_two->setCoefficientAngle(anAzimuth);
}

void AmbisonicsMap::setCoordinatesRadiusLine(double aRadius)
{
    aRadius = Tools::clip_min(aRadius, 0.);
    m_line_one->setCoefficient(aRadius);
}

void AmbisonicsMap::setCoordinatesAzimuthLine(double anAzimuth)
{
    m_line_two->setCoefficientAngle(anAzimuth);
}

void AmbisonicsMap::setCoordinatesCartesianLine(double anAbscissa, double anOrdinate)
{
    m_line_thr->setCoefficient(anAbscissa);
    m_line_fou->setCoefficient(anOrdinate);
    m_abscissa = anAbscissa;
    m_ordinate = anOrdinate;
    setCoordinatesPolarLine(Tools::radius(m_abscissa, m_ordinate), Tools::angle(m_abscissa, m_ordinate) - CICM_PI2);
}

void AmbisonicsMap::setCoordinatesAbscissaLine(double anAbscissa)
{
    m_line_thr->setCoefficient(anAbscissa);
    m_abscissa = anAbscissa;
    setCoordinatesPolarLine(Tools::radius(m_abscissa, m_ordinate), Tools::angle(m_abscissa, m_ordinate) - CICM_PI2);
}

void AmbisonicsMap::setCoordinatesOrdinateLine(double anOrdinate)
{
    m_line_fou->setCoefficient(anOrdinate);
    m_ordinate = anOrdinate;
    setCoordinatesPolarLine(Tools::radius(m_abscissa, m_ordinate), Tools::angle(m_abscissa, m_ordinate) - CICM_PI2);
}


void AmbisonicsMap::setRamp(long aNumberOfSample)
{
    m_line_one->setRamp(aNumberOfSample);
    m_line_two->setRamp(aNumberOfSample);
}

long AmbisonicsMap::getRamp()
{
    return m_line_one->getRamp();
}

AmbisonicsMap::~AmbisonicsMap()
{
    delete m_encoder;
    delete m_wider;
    delete m_line_one;
    delete m_line_two;
    delete m_line_thr;
    delete m_line_fou;
    
    Cicm_Free(m_abscissa_double);
    Cicm_Free(m_abscissa_float);
    Cicm_Free(m_ordinate_float);
    Cicm_Free(m_ordinate_double);
    Cicm_Free(m_gains_float);
    Cicm_Free(m_gains_double);
    Cicm_Free(m_harmonics_float);
    Cicm_Free(m_harmonics_double);
    Cicm_Free(m_radius_float);
    Cicm_Free(m_radius_double);
    Cicm_Free(m_azimuth_float);
    Cicm_Free(m_azimuth_double);
    for (int i = 0; i < m_number_of_harmonics; i++)
    {
        Cicm_Free(m_harmonics_matrix_float[i]);
        Cicm_Free(m_harmonics_matrix_double[i]);
    }
    Cicm_Free(m_harmonics_matrix_float);
    Cicm_Free(m_harmonics_matrix_double);
}

