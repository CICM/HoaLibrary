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

#include "CicmQSGS.h"

CicmQsgs::CicmQsgs(double aMaximumDelay, long aVectorSize, long aSamplingRate)
{
    aMaximumDelay = Tools::clip_min(aMaximumDelay, 1);
    m_sampling_rate = Tools::clip_min(aSamplingRate, 1);
    m_vector_size = Tools::clip_power_of_two(aVectorSize);
    
	m_delay = new CicmFilterDelay((double)(aMaximumDelay), m_vector_size, m_sampling_rate);
    m_line  = new CicmLine(100., m_vector_size, m_sampling_rate);
    m_envelope = new CicmEnvelope(m_sampling_rate, Cicm_Envelope_Hanning);
    m_line->setCoefficientDirect(Tools::getRandd(0., 1));
    m_line->setCoefficient(1.);
    
    m_buffer = 0.;
    setGrainSize(100.);
    setDelayTime(aMaximumDelay);
    setRarefaction(0.2);
    setFeedback(0.8);
    m_delay_rand = Tools::getRandf(0.f, m_delay_time);
    m_bypass = 0.;
    m_feedback_real = m_feedback;
}

long CicmQsgs::getVectorSize()
{
	return m_vector_size;
}

long CicmQsgs::getSamplingRate()
{
	return m_sampling_rate;
}

double CicmQsgs::getGrainSize()
{
    return m_grain_size;
}

double CicmQsgs::getDelayTime()
{
    return m_delay_time;
}

double CicmQsgs::getFeedback()
{
    return m_feedback;
}

double CicmQsgs::getRarefaction()
{
    return m_rarefaction;
}

long CicmQsgs::getWidowFunction()
{
    return m_envelope->getType();
}

double CicmQsgs::getMaximumSizeInMs()
{
    return m_delay->getBufferSizeInMs();
}

long CicmQsgs::getMaximumSizeInSample()
{
    return m_delay->getBufferSizeInSample();
}

void CicmQsgs::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_line->setVectorSize(m_vector_size);
    m_delay->setVectorSize(m_vector_size);
}

void CicmQsgs::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(1));
    m_line->setSamplingRate(m_sampling_rate);
    m_delay->setSamplingRate(m_sampling_rate);
}

void CicmQsgs::setGrainSize(double aGrainSize)
{
    m_grain_size = Tools::clip_min(aGrainSize, 0.);
}

void CicmQsgs::setDelayTime(double aDelayTime)
{
    m_delay_time = Tools::clip(aDelayTime, 0., 5000.);
}

void CicmQsgs::setFeedback(double aFeedback)
{
    m_feedback = Tools::clip(aFeedback, 0., 1.);
}

void CicmQsgs::setRarefaction(double aRarefaction)
{
    m_rarefaction = Tools::clip(aRarefaction, 0., 1.);
}

void CicmQsgs::setWindowFunction(long aEnvelopeType)
{
    m_envelope->setType(aEnvelopeType);
}

void CicmQsgs::writeWidowFunction(double* aBuffer, long aSize)
{
    m_envelope->write(aBuffer, aSize);
}

void CicmQsgs::writeWidowFunction(float* aBuffer, long aSize)
{
    m_envelope->write(aBuffer, aSize);
}

CicmQsgs::~CicmQsgs()
{
	delete m_delay;
    delete m_line;
    delete m_envelope;
}

