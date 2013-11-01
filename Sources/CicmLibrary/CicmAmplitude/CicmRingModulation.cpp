/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
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






