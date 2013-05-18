/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#include "CicmLine.h"

CicmLine::CicmLine(long aVectorSize, double aSampleRate, double _rampSizeInMs)
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

void CicmLine::setCoefficientDirect(double aCoefficient)
{
    m_value_old = m_value_new = aCoefficient;
    m_value_step = 0.;
    m_counter = 0;
}

void CicmLine::setValueStep()
{
    m_value_step = (m_value_new - m_value_old) / (double)m_ramptime_in_samps;
}

void CicmLine::setCoefficient(double aCoefficient)
{
    m_value_new  = aCoefficient;
    setValueStep();
    m_counter = 0;
}

void CicmLine::setSampleRate(double aSampleRate)
{
	m_sampling_rate = aSampleRate;
    //if (m_mode)
        setRampTimeInMs(m_ramptime_in_ms);
    //else
        //setRampTimeInSamps(m_ramptime_in_samps);
    setValueStep();
    m_counter = 0;
}

void CicmLine::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    setValueStep();
    m_counter = 0;
}

void CicmLine::setRampTimeInMs(double _rampTimeInMs)
{
    m_ramptime_in_ms = Tools::clip_min(_rampTimeInMs, double(0));
    m_ramptime_in_samps = m_ramptime_in_ms * m_sampling_rate / 1000.;//Tools::mstosamps(m_ramptime_in_ms, m_sampling_rate);
}
void CicmLine::setRampTimeInSamps(long _rampTimeInSamps)
{
    m_ramptime_in_samps = Tools::clip_min(_rampTimeInSamps, long(0));
    m_ramptime_in_ms = Tools::sampstoms(m_ramptime_in_samps, m_sampling_rate);
}

CicmLine::~CicmLine()
{
    ;
}
