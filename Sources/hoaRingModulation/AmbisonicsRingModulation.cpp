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

#include "AmbisonicsRingModulation.h"

AmbisonicsRingModulation::AmbisonicsRingModulation(long anOrder, bool aMode,long aVectorSize, long aSamplingRate) : AmbisonicsDiffuser( anOrder, aMode, aVectorSize, aSamplingRate)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_ring_mod.push_back(new CicmRingModulation(m_vector_size, m_sampling_rate));
        m_line.push_back(new CicmLine(20., m_vector_size, m_sampling_rate));
        m_line[i]->setCoefficientDirect(1.);
    }
}

double AmbisonicsRingModulation::getFrequency()
{
    return m_frequency;
}

void AmbisonicsRingModulation::setDiffuseFactor(double aDiffuseValue)
{
    if(m_mode == Hoa_Post_Encoding)
    {
        m_diffuse_factor = Tools::clip(aDiffuseValue, 0., 1.);
        setFrequency(m_frequency);
    }
}

void AmbisonicsRingModulation::setFrequency(double aFrequency)
{
    double frequency;
    m_frequency = Tools::clip_min(aFrequency, 0);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        if(m_diffuse_factor <= (1. - ((double)(i+1) / (double)m_number_of_harmonics)))
        {
            frequency = 0.;
            m_line[i]->setCoefficient(1.);
        }
        else
        {
            frequency = m_frequency * ((double)(i+1) / (double)m_number_of_harmonics);
            m_line[i]->setCoefficient(0.);
        }
        m_ring_mod[i]->setFrequency(frequency);
    }
}

void AmbisonicsRingModulation::setVectorSize(long aVectorSize)
{
    AmbisonicsDiffuser::setVectorSize(aVectorSize);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_ring_mod[i]->setVectorSize(m_vector_size);
        m_line[i]->setVectorSize(m_vector_size);
    }
}

void AmbisonicsRingModulation::setSamplingRate(long aSamplingRate)
{
    AmbisonicsDiffuser::setSamplingRate(aSamplingRate);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_ring_mod[i]->setSamplingRate(m_sampling_rate);
        m_line[i]->setSamplingRate(m_sampling_rate);
    }
    setFrequency(m_frequency);
}

AmbisonicsRingModulation::~AmbisonicsRingModulation()
{
	m_ring_mod.clear();
    m_line.clear();
}

