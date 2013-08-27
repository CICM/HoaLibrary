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

#include "AmbisonicConvolver.h"

AmbisonicConvolver::AmbisonicConvolver(long anOrder, long aSamplingFrequency, long aVectorSize) : Ambisonic(anOrder, aVectorSize, aSamplingFrequency)
{    
	m_impulse_response      = new float[1];
    m_impulse_response_size = 1;

	for(int i = 0; i < m_number_of_harmonics; i++)
    {
		m_convolution.push_back(new FilterConvolutionZero());
    }
	m_wet_vector = new double[1];
    m_dry_vector = new double[1];
    m_wet_line = new CicmLine(50.);
    m_dry_line = new CicmLine(50.);
    m_wet_line->setCoefficientDirect(1.);
    m_dry_line->setCoefficientDirect(0.);
	setWetValue(1);
    setDryValue(0.);
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


