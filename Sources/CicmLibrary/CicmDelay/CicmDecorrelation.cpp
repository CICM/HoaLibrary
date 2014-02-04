/* 
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "CicmDecorrelation.h"

CicmDecorrelation::CicmDecorrelation(double aMaximumDelay, long aVectorSize, long aSamplingRate)
{
    m_maximum_delay = Tools::clip_min(aMaximumDelay, 1);
    m_sampling_rate = Tools::clip_min(aSamplingRate, 1);
    m_vector_size = Tools::clip_power_of_two(aVectorSize);
    
	m_delay     = new CicmFilterDelay(m_maximum_delay * m_sampling_rate / 1000., m_vector_size, m_sampling_rate);
    m_line      = new CicmLine(100., m_vector_size, m_sampling_rate);
    m_envelope  = new CicmEnvelope(m_sampling_rate, Cicm_Envelope_Halfsinus);
    
    m_line->setCoefficientDirect(0.);
    m_line->setCoefficient(0.);
    m_line->setRampInMs(100.);
    
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
    m_delay->setBufferSizeInMs(m_maximum_delay);
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

