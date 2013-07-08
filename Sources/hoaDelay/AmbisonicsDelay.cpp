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

#include "AmbisonicsDelay.h"

AmbisonicsDelay::AmbisonicsDelay(long anOrder, bool aMode, double aMaximumDelayInMs,long aVectorSize, long aSamplingRate) : AmbisonicsDiffuser( anOrder, aMode, aVectorSize, aSamplingRate)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_delay.push_back(new CicmDecorrelation(aMaximumDelayInMs, aVectorSize, aSamplingRate));
    }
    m_gain = new bool[m_number_of_harmonics];
    
    setDelayTimeInMs(aMaximumDelayInMs);
}

long AmbisonicsDelay::getDelayTimeInSample()
{
    return m_delay_time * (double)m_sampling_rate / 1000.;
}

double AmbisonicsDelay::getDelayTimeInMs()
{
    return m_delay_time;
}

long AmbisonicsDelay::getRampInSample()
{
    return m_delay[0]->getRampInSample();
}

double AmbisonicsDelay::getRampInMs()
{
    return m_delay[0]->getRampInMs();
}

void AmbisonicsDelay::setDiffuseFactor(double aDiffuseValue)
{
    if(m_mode == Hoa_Post_Encoding)
    {
        m_diffuse_factor = Tools::clip(aDiffuseValue, 0., 1.);
        setDelayTimeInMs(m_delay_time);
    }
}

void AmbisonicsDelay::setDelayTimeInSample(long aDelayInSample)
{
    setDelayTimeInMs((double)aDelayInSample / (double)m_sampling_rate * 1000.);
}

void AmbisonicsDelay::setDelayTimeInMs(double aDelayInMs)
{
    double delay;
    m_delay_time = Tools::clip_min(aDelayInMs, 0);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        if(m_diffuse_factor <= (1. - ((double)(i+1) / (double)m_number_of_harmonics)))
        {
            delay = 0.;
            m_gain[i] = 1.;
        }
        else
        {
            delay = m_delay_time * ((double)(i+1) / (double)m_number_of_harmonics);
            m_gain[i] = 0.;
        }
        m_delay[i]->setDelayTimeInMs(delay);
    }
}

void AmbisonicsDelay::setRampInMs(double aRampInMs)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_delay[i]->setRampInMs(aRampInMs);
    }
}

void AmbisonicsDelay::setRampInSample(long aRampInSample)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_delay[i]->setRampInSample(aRampInSample);
    }
}

void AmbisonicsDelay::setVectorSize(long aVectorSize)
{
    AmbisonicsDiffuser::setVectorSize(aVectorSize);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_delay[i]->setVectorSize(m_vector_size);
    }
}

void AmbisonicsDelay::setSamplingRate(long aSamplingRate)
{
    AmbisonicsDiffuser::setSamplingRate(aSamplingRate);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_delay[i]->setSamplingRate(m_sampling_rate);
    }
    setDelayTimeInMs(m_delay_time);
}

AmbisonicsDelay::~AmbisonicsDelay()
{
	m_delay.clear();
    Cicm_Free(m_gain);
}

