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
        m_microphones_coefficients_step[anIndex] = (m_microphones_coefficients_new[anIndex] - m_microphones_coefficients_old[anIndex]) / (double)RAMP_SAMPLE;
    }
    m_counter = 0;
}

void AmbisonicSpace::setCoefficient(double* aCoefficientVector)
{
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_microphones_coefficients_new[i] = aCoefficientVector[i];
        m_microphones_coefficients_step[i] =(m_microphones_coefficients_new[i] - m_microphones_coefficients_old[i]) / (double)RAMP_SAMPLE;
    }
    m_counter = 0;
}

void AmbisonicSpace::setCoefficient(float* aCoefficientVector)
{
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_microphones_coefficients_new[i] = aCoefficientVector[i];
        m_microphones_coefficients_step[i] = (m_microphones_coefficients_new[i] - m_microphones_coefficients_old[i]) / (double)RAMP_SAMPLE;
    }
    m_counter = 0;
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
