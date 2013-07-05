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

#include "CicmLine2.h"

CicmLine2::CicmLine2(long aVectorSize, double aSampleRate, double _rampSizeInMs)
{
    m_value_old = 0.;
    m_value_new = 0.;
    m_value_step = 0.;
    m_counter = 0;
    setVectorSize(aVectorSize);
    setSampleRate(aSampleRate);
    setRampTimeInMs(_rampSizeInMs);
    m_mode = 1;
}

void CicmLine2::setCoefficientDirect(double aCoefficient)
{
    m_value_old = m_value_new = aCoefficient;
    m_value_step = 0.;
    m_counter = 0;
}

void CicmLine2::setValueStep()
{
    m_value_step = (m_value_new - m_value_old) / (double)m_ramptime_in_samps;
}

void CicmLine2::setCoefficient(double aCoefficient)
{
    m_value_new  = aCoefficient;
    setValueStep();
    m_counter = 0;
}

void CicmLine2::setSampleRate(double aSampleRate)
{
	m_sampling_rate = aSampleRate;
    setRampTimeInMs(m_ramptime_in_ms);
    setValueStep();
    m_counter = 0;
}

void CicmLine2::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    setValueStep();
    m_counter = 0;
}

void CicmLine2::setRampTimeInMs(double _rampTimeInMs)
{
    m_ramptime_in_ms = Tools::clip_min(_rampTimeInMs, double(0));
    m_ramptime_in_samps = m_ramptime_in_ms * m_sampling_rate / 1000.;//Tools::mstosamps(m_ramptime_in_ms, m_sampling_rate);
}
void CicmLine2::setRampTimeInSamps(long _rampTimeInSamps)
{
    m_ramptime_in_samps = Tools::clip_min(_rampTimeInSamps, long(0));
    m_ramptime_in_ms = Tools::sampstoms(m_ramptime_in_samps, m_sampling_rate);
}

CicmLine2::~CicmLine2()
{
    ;
}
