/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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
