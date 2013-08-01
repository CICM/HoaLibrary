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

#include "AmbisonicWider.h"

AmbisonicWider::AmbisonicWider(long anOrder, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics + 1;
	m_number_of_outputs		= m_number_of_harmonics;

	computeVectors();
	setWidenValue(1.);
    setAzimtuh(0.);
    setVectorSize(aVectorSize);
}

long AmbisonicWider::getOrder()
{
	return m_order;
}

long AmbisonicWider::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicWider::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicWider::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicWider::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicWider::computeVectors()
{
	m_index_of_harmonics	= new long[m_number_of_harmonics ];
    m_ambiCoeffs            = new double[m_number_of_harmonics];
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
}

void AmbisonicWider::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void AmbisonicWider::setAzimtuh(double aTheta)
{
	m_ambiCoeffs[0] = 1.;
	int  tmpIndex = 2;
	long tmpAngle;
	if (aTheta < 0)
		aTheta = aTheta + ( -floor(aTheta/CICM_2PI)) * CICM_2PI;
    
	double angleFactor = aTheta*NUMBEROFCIRCLEPOINTS/(CICM_2PI);
	
	for (int i = 1; i <= m_order; i++)
	{
		tmpAngle = (long)(i*angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
		m_ambiCoeffs[tmpIndex-1] = m_sinLookUp[tmpAngle];
		m_ambiCoeffs[tmpIndex]   = m_cosLookUp[tmpAngle];
		
		tmpIndex += 2;
	}
}

void AmbisonicWider::setWidenValue(double aWidenValue)
{
	m_widen_value = Tools::clip(aWidenValue, 0., 1.);
    double weight = ((1. - m_widen_value) * m_order_weight + 1.) * 2.;
    m_widen_vector[0] = weight;
    for(int i = 1; i < m_number_of_harmonics; i+=2)
        m_widen_vector[i] = weight * Tools::clip(((m_widen_value * m_order_weight) - m_minus_vector[i]) * m_dot_vector[i], 0., 1.);
}

AmbisonicWider::~AmbisonicWider()
{
	free(m_index_of_harmonics);
	free(m_minus_vector);
	free(m_dot_vector);
    free(m_widen_vector);
    free(m_ambiCoeffs);
}

