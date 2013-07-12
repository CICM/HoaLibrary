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

