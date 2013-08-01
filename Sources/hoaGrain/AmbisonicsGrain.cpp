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

#include "AmbisonicsGrain.h"

AmbisonicsGrain::AmbisonicsGrain(long anOrder, bool aMode, double aMaximumDelayInMs,long aVectorSize, long aSamplingRate) : AmbisonicsDiffuser( anOrder, aMode, aVectorSize, aSamplingRate)
{
    m_maximum_delay_time = Tools::clip_min(aMaximumDelayInMs, 1);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_grain.push_back(new CicmQsgs(m_maximum_delay_time, m_vector_size, m_sampling_rate));
    }
    setGrainSize(100.);
    setDelayTime(m_maximum_delay_time);
    setFeedback(0.8);
    setRarefaction(0.2);
}

double AmbisonicsGrain::getGrainSize()
{
    return m_grain_size;
}

double AmbisonicsGrain::getDelayTime()
{
    return m_delay_time;
}

double AmbisonicsGrain::getFeedback()
{
    return m_feedback;
}

double AmbisonicsGrain::getRarefaction()
{
    return m_rarefaction;
}

long AmbisonicsGrain::getWidowFunction()
{
    return m_grain[0]->getWidowFunction();
}

double AmbisonicsGrain::getGrainSizeFromIndex(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_harmonics)
        return m_grain[anIndex]->getGrainSize();
    else
        return NULL;
}

double AmbisonicsGrain::getDelayTimeFromIndex(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_harmonics)
        return m_grain[anIndex]->getDelayTime();
    else
        return NULL;
}

double AmbisonicsGrain::getMaximumSizeInMs()
{
    return m_grain[0]->getMaximumSizeInMs();
}

long AmbisonicsGrain::getMaximumSizeInSample()
{
    return m_grain[0]->getMaximumSizeInSample();
}

void AmbisonicsGrain::setGrainSize(double aGrainSize)
{
    m_grain_size = Tools::clip_min(aGrainSize, 0);
    double grain_size;
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        grain_size = m_grain_size * (1. - ((double)(i) / (double)m_number_of_harmonics));
        m_grain[i]->setGrainSize(grain_size);
    }
}

void AmbisonicsGrain::setDelayTime(double aDelayTime)
{
    m_delay_time = Tools::clip(aDelayTime, 0, m_maximum_delay_time);
    double delay_time;
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        delay_time = m_delay_time * ((double)(i+1) / (double)m_number_of_harmonics);
        m_grain[i]->setDelayTime(delay_time);
    }    
}

void AmbisonicsGrain::setFeedback(double aFeedback)
{
    m_feedback = Tools::clip(aFeedback, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_grain[i]->setFeedback(m_feedback);
    }
}

void AmbisonicsGrain::setRarefaction(double aRarefaction)
{
    m_rarefaction = Tools::clip(aRarefaction, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_grain[i]->setRarefaction(m_rarefaction);
    }
}

void AmbisonicsGrain::setWindowFunction(long aEnvelopeType)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_grain[i]->setWindowFunction(aEnvelopeType);
    }
}

void AmbisonicsGrain::writeWidowFunction(double* aBuffer, long aSize)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_grain[i]->writeWidowFunction(aBuffer, aSize);
    }
}

void AmbisonicsGrain::writeWidowFunction(float* aBuffer, long aSize)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_grain[i]->writeWidowFunction(aBuffer, aSize);
    }
}

void AmbisonicsGrain::setVectorSize(long aVectorSize)
{
    AmbisonicsDiffuser::setVectorSize(aVectorSize);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_grain[i]->setVectorSize(m_vector_size);
    }
}

void AmbisonicsGrain::setSamplingRate(long aSamplingRate)
{
    AmbisonicsDiffuser::setSamplingRate(aSamplingRate);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_grain[i]->setSamplingRate(m_sampling_rate);
    }
}

AmbisonicsGrain::~AmbisonicsGrain()
{
	m_grain.clear();
}

