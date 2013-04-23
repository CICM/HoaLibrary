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
    m_ambisonics_impulse_responses = new float*[m_number_of_harmonics];
    
    m_early_diffraction = 0.;
    m_tail_diffraction  = 0.;
    
	for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_ambisonics_impulse_responses[i] = new float[1];
		m_convolution.push_back(new ZeroLatencyConvolver());
    }
	
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
}

double	AmbisonicConvolver::getWetValue()
{
    return m_wet;
}

void AmbisonicConvolver::setDryValue(double aGain)
{
    m_dry = Tools::clip(aGain, 0., 1.);
}

double	AmbisonicConvolver::getDryValue()
{
    return m_dry;
}

void AmbisonicConvolver::setEarlyDiffractionValue(double aValue)
{
    m_early_diffraction = Tools::clip(aValue, 0., 1.);
    computeAmbisonicsImpulseResponses();
}

double	AmbisonicConvolver::getEarlyDiffractionValue()
{
    return m_early_diffraction;
}

void AmbisonicConvolver::setTailDiffractionValue(double aValue)
{
    m_tail_diffraction = Tools::clip(aValue, 0., 1.);
    computeAmbisonicsImpulseResponses();
}

double	AmbisonicConvolver::getTailDiffractionValue()
{
    return m_tail_diffraction;
}

void AmbisonicConvolver::setCutOffTime(double aTimeValue)
{
    m_cutoff_time = Tools::clip_min(aTimeValue, 0.);
    computeAmbisonicsImpulseResponses();
}

double AmbisonicConvolver::getCutOffTime()
{
    return m_cutoff_time;
}

void AmbisonicConvolver::computeAmbisonicsImpulseResponses()
{
    ;
}

void AmbisonicConvolver::setImpulseResponse(float* anImpulResponse, long aSize)
{
    if(m_impulse_response_size != aSize)
    {
        free(m_impulse_response);
        m_impulse_response = new float[aSize];
        m_impulse_response_size = aSize;
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            free(m_ambisonics_impulse_responses[i]);
            m_ambisonics_impulse_responses[i] = new float[m_impulse_response_size];
        }
        
    }
    for(int i = 0; i < m_impulse_response_size; i++)
        m_impulse_response[i] = anImpulResponse[i];
    
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_convolution[i]->setImpulseResponse(m_impulse_response, m_impulse_response_size);
    
}
AmbisonicConvolver::~AmbisonicConvolver()
{
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		delete m_convolution[i];
		m_convolution[i] = 0;
        free(m_ambisonics_impulse_responses[i]);
	}
    free(m_impulse_response);
    free(m_ambisonics_impulse_responses);
}


