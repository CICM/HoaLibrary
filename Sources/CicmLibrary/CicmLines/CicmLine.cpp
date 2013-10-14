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
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
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

#include "CicmLine.h"

CicmLine::CicmLine(long aTimeInSample, long aVectorSize, long aSamplingRate)
{
    m_value_old = 0.;
    m_value_new = 0.;
    m_value_step = 0.;
    m_counter = 0;
    
    setVectorSize(aVectorSize);
    setSamplingRate(aSamplingRate);
    setRampInSample(aTimeInSample);
}

CicmLine::CicmLine(double aTimeInMs, long aVectorSize, long aSamplingRate)
{
    m_value_old = 0.;
    m_value_new = 0.;
    m_value_step = 0.;
    m_counter = 0;
    
    setVectorSize(aVectorSize);
    setSamplingRate(aSamplingRate);
    setRampInMs(aTimeInMs);
}

long CicmLine::getVectorSize()
{
	return m_vector_size;    
}

long CicmLine::getSamplingRate()
{
    return m_sampling_rate;
}

double CicmLine::getCoefficient()
{
    return m_value_new;
}

long CicmLine::getRampInSample()
{
    return m_ramp;
}

double CicmLine::getRampInMs()
{
    return ((double)m_ramp / (double)m_sampling_rate) * 1000.;
}

void CicmLine::setRampInSample(long aTimeInSample)
{
    m_ramp = Tools::clip_min(aTimeInSample, (long)1);
}

void CicmLine::setRampInMs(double aTimeInMs)
{
    setRampInSample(aTimeInMs * (double)m_sampling_rate / 1000.);
}

void CicmLine::setCoefficientDirect(double aCoefficient)
{
    m_value_old = m_value_new = aCoefficient;
    m_value_step = 0.;
    m_counter = 0;
}

void CicmLine::setCoefficient(double aCoefficient)
{
    m_value_new  = aCoefficient;
    m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
    m_counter = 0;
}

void CicmLine::setCoefficientAngleDirect(double anAngle)
{
    m_value_old = m_value_new = Tools::radian_wrap(anAngle);
    m_value_step = 0.;
    m_counter = 0;
}

void CicmLine::setCoefficientAngle(double anAngle)
{
    m_value_new = Tools::radian_wrap(anAngle);
    m_value_old = Tools::radian_wrap(m_value_old);
    if(Tools::radianDistance(m_value_old, m_value_new) <= CICM_PI)
    {
        m_value_step = (m_value_new - m_value_old) / (double)m_ramp;
    }
    else
    {
        if(m_value_new > Tools::radian_wrap(m_value_old))
        {
            m_value_step = ((m_value_new - CICM_2PI) - m_value_old) / (double)m_ramp;
        }
        else
        {
            m_value_step = ((m_value_new + CICM_2PI) - m_value_old) / (double)m_ramp;
        }
    }
    m_counter = 0;
}

void CicmLine::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void CicmLine::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(1));
}

CicmLine::~CicmLine()
{
    ;
}
