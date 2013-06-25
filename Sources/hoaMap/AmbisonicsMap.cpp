/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "AmbisonicsMap.h"

AmbisonicsMap::AmbisonicsMap(long anOrder, long aRampSample, long aVectorSize, long aSamplingRate) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
	m_number_of_inputs		= 1;

    m_encoder   = new AmbisonicsEncoder(m_order);
    m_wider     = new AmbisonicsWider(m_order);
    m_line_one  = new CicmLine(aRampSample);
    m_line_two  = new CicmLine(aRampSample);
    m_line_thr  = new CicmLine(aRampSample);
    m_line_fou  = new CicmLine(aRampSample);
    m_low_pass_filter    = new FilterOnePole(m_sampling_rate);
    m_low_pass_filter->setCutOffFrequency(m_sampling_rate / 2.);
    
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
    m_low_pass_filter->setVectorSize(m_vector_size);
    
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

void AmbisonicsMap::setSamplingRate(long aSamplingRate)
{
    m_sampling_rate = Tools::clip_min(aSamplingRate, long(0));
    m_low_pass_filter->setSamplingRate(aSamplingRate);
}

void AmbisonicsMap::setCoordinatesPolar(double aRadius, double anAzimuth)
{
    m_radius = Tools::clip_min(aRadius, 0.);
    if(m_radius <= 1.)
    {
        m_gain = 1.;
        m_wide = m_radius;
        m_low_pass_filter->setCutOffFrequency(m_sampling_rate / 2.);
    }
    else
    {
        m_gain = 1. / (m_radius * m_radius);
        m_low_pass_filter->setCutOffFrequency(1000. + (m_sampling_rate / 2.) -  (m_sampling_rate / 2.) * (m_radius * m_radius) / 1225.);
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
    delete m_low_pass_filter;
    
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

