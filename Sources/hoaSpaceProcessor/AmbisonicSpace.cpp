/*
 *
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

#include "AmbisonicSpace.h"

AmbisonicSpace::AmbisonicSpace(long aNumberOfMicrophones, long aVectorSize)
{
	m_number_of_microphones = Tools::clip_min(aNumberOfMicrophones, (long)3);
	m_number_of_inputs		= m_number_of_microphones;
	m_number_of_outputs		= m_number_of_microphones;
	
    m_microphones_coefficients_old = new double[m_number_of_microphones];
    m_microphones_coefficients_new = new double[m_number_of_microphones];
    m_microphones_coefficients_step = new double[m_number_of_microphones];
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_microphones_coefficients_old[i] = 1.;
        m_microphones_coefficients_new[i] = 1.;
        m_microphones_coefficients_step[i] = 0.;
    }
    m_counter = 0;
    setVectorSize(aVectorSize);
}

long AmbisonicSpace::getNumberOfMicrophones()
{
	return m_number_of_microphones;
}

long AmbisonicSpace::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicSpace::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicSpace::getVectorSize()
{
	return m_vector_size;
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_microphones_coefficients_step[i] = (m_microphones_coefficients_old[i] - m_microphones_coefficients_new[i]) / (double)m_vector_size;
    }
    
}

double AmbisonicSpace::getCoefficient(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_microphones)
       return m_microphones_coefficients_new[anIndex];
    else
        return NULL;
}

void AmbisonicSpace::setCoefficient(long anIndex, double aCoefficient)
{
    if(anIndex >= 0 && anIndex < m_number_of_microphones)
    {
        m_microphones_coefficients_new[anIndex] = aCoefficient;
        m_microphones_coefficients_step[anIndex] = (m_microphones_coefficients_old[anIndex] - m_microphones_coefficients_new[anIndex]) / (double)4100.;
    }
}

void AmbisonicSpace::setCoefficient(double* aCoefficientVector)
{
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_microphones_coefficients_new[i] = aCoefficientVector[i];
        m_microphones_coefficients_step[i] =(m_microphones_coefficients_old[i] - m_microphones_coefficients_new[i]) / (double)4100.;
    }
}

void AmbisonicSpace::setCoefficient(float* aCoefficientVector)
{
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_microphones_coefficients_new[i] = aCoefficientVector[i];
        m_microphones_coefficients_step[i] = (m_microphones_coefficients_old[i] - m_microphones_coefficients_new[i]) / (double)4100.;
    }
}

void AmbisonicSpace::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

AmbisonicSpace::~AmbisonicSpace()
{
	free(m_microphones_coefficients_old);
    free(m_microphones_coefficients_new);
    free(m_microphones_coefficients_step);
}
