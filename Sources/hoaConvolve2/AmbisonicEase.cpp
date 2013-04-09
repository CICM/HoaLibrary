/*
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#include "AmbisonicEase.h"

AmbisonicEase::AmbisonicEase(long anOrder, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= 1;
	m_number_of_outputs		= m_number_of_harmonics;

	computeVectors();
	setPolarCoordinates(1., 0.);
    setVectorSize(aVectorSize);
}

long AmbisonicEase::getOrder()
{
	return m_order;
}

long AmbisonicEase::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicEase::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicEase::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicEase::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicEase::computeVectors()
{
	m_index_of_harmonics	= new long[m_number_of_harmonics ];
    m_ambiCoeffs            = new double[m_number_of_harmonics];
    m_optimVector           = new double[m_number_of_harmonics];
    m_minus_vector          = new double[m_number_of_harmonics];
	m_dot_vector            = new double[m_number_of_harmonics];
    m_widen_vector          = new double[m_number_of_harmonics];
    
	m_index_of_harmonics[0] = 0;
    m_order_weight = log((double)(m_order + 1));
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = (i - 1) / 2 + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
    for(int i = 1; i < m_number_of_harmonics; i++)
	{
        m_minus_vector[i] = Tools::clip_min(log((double)abs(m_index_of_harmonics[i])), 0.);
		m_dot_vector[i]	= Tools::clip_min(log((double)abs(m_index_of_harmonics[i]) + 1.), 0.);
		m_dot_vector[i] -= m_minus_vector[i];
		m_dot_vector[i] = 1. / m_dot_vector[i];
    }
    for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
	{
		m_cosLookUp[i] = cos((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
		m_sinLookUp[i] = sin((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
	}
    for (int i = 0; i < m_number_of_harmonics; i++)
	{
		if (i == 0)
			m_optimVector[i] = 1.;
		else
			m_optimVector[i] = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[i])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[i])));
	}
}

void AmbisonicEase::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void AmbisonicEase::setAzimtuh(double aTheta)
{
	m_ambiCoeffs[0] = 1. * m_optimVector[0];
	int  tmpIndex = 2;
	long tmpAngle;
	if (aTheta < 0)
		aTheta = aTheta + ( -floor(aTheta/CICM_2PI)) * CICM_2PI;
    
	double angleFactor = aTheta*NUMBEROFCIRCLEPOINTS/(CICM_2PI);
	
	for (int i = 1; i <= m_order; i++)
	{
		tmpAngle = (long)(i*angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
		m_ambiCoeffs[tmpIndex-1] = m_sinLookUp[tmpAngle] * m_optimVector[tmpIndex-1];
		m_ambiCoeffs[tmpIndex]   = m_cosLookUp[tmpAngle] * m_optimVector[tmpIndex];
		
		tmpIndex += 2;
	}
}

void AmbisonicEase::setWidenValue(double aWidenValue)
{
	m_widen_value = Tools::clip(aWidenValue, 0., 1.);
    double weight = (1. - m_widen_value) * m_order_weight + 1.;
    m_widen_vector[0] = weight;
    
    for(int i = 1; i < m_number_of_harmonics; i++)
    {
        m_widen_vector[i] = weight * Tools::clip(((m_widen_value * m_order_weight) - m_minus_vector[i]) * m_dot_vector[i], 0., 1.);
    }
}

void AmbisonicEase::setPolarCoordinates(double aRadius, double anAzimuth)
{
    setAzimtuh(anAzimuth);
    if(aRadius >= 1)
    {
        setWidenValue(1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_widen_vector[i] *= (2. / (aRadius + 1.));
    }
    else
    {
        setWidenValue(aRadius);
    }
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_ambiCoeffs[i] *= m_widen_vector[i];
}

void AmbisonicEase::setCartesianCoordinates(double anAbscissa, double anOrdinate)
{
    setPolarCoordinates(Tools::radius(anAbscissa, anOrdinate), Tools::angle(anAbscissa, anOrdinate) - CICM_PI2);
}

AmbisonicEase::~AmbisonicEase()
{
	free(m_index_of_harmonics);
	free(m_minus_vector);
	free(m_dot_vector);
    free(m_widen_vector);
    free(m_ambiCoeffs);
    free(m_optimVector);
}

