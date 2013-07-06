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

#include "CicmDecorrelation.h"

CicmDecorrelation::CicmDecorrelation(double aMaximumDelay, long aVectorSize, double aSamplingRate)
{
    aMaximumDelay = Tools::clip_min(aMaximumDelay, 1);
    m_sampling_rate = Tools::clip_min(aSamplingRate, long(1));
    m_vector_size = Tools::clip_power_of_two(aVectorSize);
    
	m_delay     = new CicmFilterDelay(aMaximumDelay * m_sampling_rate / 1000., m_vector_size, m_sampling_rate);
    m_line      = new CicmLine(m_vector_size, m_sampling_rate);
    m_envelope  = new CicmEnvelope(m_sampling_rate, Cicm_Envelope_Cosinus);
    
    m_line->setCoefficientDirect(0.);
    m_line->setCoefficient(0.);
    m_line->setRampInMs(20.);
    
    m_current_delay = 0;
    m_delay_time_one = aMaximumDelay;
    m_delay_time_two = aMaximumDelay;
    m_new_delay      = aMaximumDelay;
    m_max_gain = m_envelope->getValueRelative(0.5);
}

long CicmDecorrelation::getVectorSize()
{
	return m_vector_size;
}

long CicmDecorrelation::getSamplingRate()
{
	return m_sampling_rate;
}

long CicmDecorrelation::getDelayTimeInSample()
{
    if(m_current_delay == 0)
        return m_delay_time_one;
    else
        return m_delay_time_two;
}

double CicmDecorrelation::getDelayTimeInMs()
{
    return (double)getDelayTimeInSample() / (double)m_sampling_rate * 1000.;
}

long CicmDecorrelation::getRampInSample()
{
    return m_line->getRampInSample();
}

double CicmDecorrelation::getRampInMs()
{
    return m_line->getRampInMs();
}

void CicmDecorrelation::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_line->setVectorSize(m_vector_size);
    m_delay->setVectorSize(m_vector_size);
}

void CicmDecorrelation::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(1));
    m_line->setSamplingRate(m_sampling_rate);
    m_delay->setSamplingRate(m_sampling_rate);
}

void CicmDecorrelation::setDelayTimeInSample(long aDelayInSample)
{
    m_new_delay = Tools::clip_min(aDelayInSample, 0);
}

void CicmDecorrelation::setDelayTimeInMs(double aDelayInMs)
{
    setDelayTimeInSample(aDelayInMs * (double)m_sampling_rate / 1000.);
}

void CicmDecorrelation::setRampInSample(long aRampInSample)
{
    m_line->setRampInSample(aRampInSample);
}

void CicmDecorrelation::setRampInMs(double aRampInMs)
{
    m_line->setRampInMs(aRampInMs);
}

CicmDecorrelation::~CicmDecorrelation()
{
	delete m_delay;
    delete m_line;
    delete m_envelope;
}

