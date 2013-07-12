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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "CicmRingModulation.h"

CicmRingModulation::CicmRingModulation(long aVectorSize, double aSamplingRate)
{
    m_sampling_rate = Tools::clip_min(aSamplingRate, long(1));
    m_vector_size = Tools::clip_power_of_two(aVectorSize);
    
    m_line      = new CicmLine(1000., m_vector_size, m_sampling_rate);
    m_envelope  = new CicmEnvelope(m_sampling_rate, Cicm_Envelope_Sinus);
    
    m_line->setCoefficientDirect(0.25);
    m_line->setCoefficient(1.);
    m_line->setRampInMs(1000.);
}

long CicmRingModulation::getVectorSize()
{
	return m_vector_size;
}

long CicmRingModulation::getSamplingRate()
{
	return m_sampling_rate;
}

double CicmRingModulation::getFrequency()
{
    return m_frequency;
}

void CicmRingModulation::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_line->setVectorSize(m_vector_size);
}

void CicmRingModulation::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(1));
    m_line->setSamplingRate(m_sampling_rate);
}

void CicmRingModulation::setFrequency(double aFrequency)
{
    double frequency = Tools::clip_min(fabs(aFrequency), 0.);
    if(frequency == 0)
    {
        m_line->setCoefficient(0.25);
        m_frequency = 0;
    }
    else if(m_frequency == 0 && frequency!= 0)
    {
        m_line->setCoefficient(1.);
        m_frequency = frequency;
        m_line->setRampInMs(1. / m_frequency * 1000.);
    }
    else
    {
        m_frequency = frequency;
        m_line->setRampInMs(1. / m_frequency * 1000.);
    }
}

CicmRingModulation::~CicmRingModulation()
{
    delete m_line;
    delete m_envelope;
}






