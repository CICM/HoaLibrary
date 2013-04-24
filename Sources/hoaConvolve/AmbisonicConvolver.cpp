/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & CICM_PIerre Guillot, Universite Paris 8
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

#include "AmbisonicConvolver.h"

AmbisonicConvolver::AmbisonicConvolver(long anOrder, long aSamplingFrequency, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= m_number_of_harmonics;
    
	m_impulse_response      = new float[1];
    m_impulse_response_size = 1;

	for(int i = 0; i < m_number_of_harmonics; i++)
    {
		m_convolution.push_back(new ZeroLatencyConvolver());
    }
	m_wet_vector = new double[1];
    m_dry_vector = new double[1];
    m_wet_line = new AmbisonicLine();
    m_dry_line = new AmbisonicLine();
    m_wet_line->setCoefficientDirect(1.);
    m_dry_line->setCoefficientDirect(0.);
	setWetValue(1);
    setDryValue(0.);
}

long AmbisonicConvolver::getOrder()
{
	return m_order;
}

long AmbisonicConvolver::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicConvolver::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicConvolver::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

void AmbisonicConvolver::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_wet_line->setVectorSize(aVectorSize);
    m_dry_line->setVectorSize(aVectorSize);
    free(m_wet_vector);
    m_wet_vector = new double[m_vector_size];
    free(m_dry_vector);
    m_dry_vector = new double[m_vector_size];
}

long AmbisonicConvolver::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicConvolver::setSamplingFrequency(long aSamplingFrequency)
{
    m_sampling_frequency = aSamplingFrequency;
}

long AmbisonicConvolver::getSamplingFrequency()
{
    return m_sampling_frequency;
}

void AmbisonicConvolver::setWetValue(double aGain)
{
    m_wet = Tools::clip(aGain, 0., 1.);
    m_wet_line->setCoefficient(m_wet);
}

double	AmbisonicConvolver::getWetValue()
{
    return m_wet;
}

void AmbisonicConvolver::setDryValue(double aGain)
{
    m_dry = Tools::clip(aGain, 0., 1.);
    m_dry_line->setCoefficient(m_dry);
}

double	AmbisonicConvolver::getDryValue()
{
    return m_dry;
}

void AmbisonicConvolver::clear()
{
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_convolution[i]->clear();
}

void AmbisonicConvolver::setImpulseResponse(float* anImpulResponse, long aSize)
{
    if(m_impulse_response_size != aSize)
    {
        free(m_impulse_response);
        m_impulse_response = new float[aSize];
        m_impulse_response_size = aSize;
    }
    for(int i = 0; i < m_impulse_response_size; i++)
        m_impulse_response[i] = anImpulResponse[i];
    
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_convolution[i]->setImpulseResponse(m_impulse_response, m_impulse_response_size);
    
}
AmbisonicConvolver::~AmbisonicConvolver()
{
    m_convolution.clear();
    delete m_wet_line;
    delete m_dry_line;
    free(m_impulse_response);
    free(m_wet_vector);
    free(m_dry_vector);
}


