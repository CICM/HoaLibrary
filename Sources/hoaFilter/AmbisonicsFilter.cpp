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

#include "AmbisonicsFilter.h"

AmbisonicsFilter::AmbisonicsFilter(long anOrder, long aVectorSize, long aSamplingRate)
: Ambisonic(anOrder, aVectorSize, aSamplingRate)
{
    m_vector_sum_double = NULL;
    m_vector_sum_float  = NULL;
    cicm_malloc_vec_d(m_frequency, m_number_of_harmonics);
    cicm_malloc_vec_d(m_gain, m_number_of_harmonics);
    m_filter.push_back(new FilterBiquad(Cicm_Biquad_Lowshelf, m_vector_size, m_sampling_rate));
    m_filter[0]->setQValue(1.);
    m_filter[0]->setGain(1.);
    
    for(int j = 1; j < m_number_of_harmonics - 2; j++)
    {
        m_filter.push_back(new FilterBiquad(Cicm_Biquad_Lowshelf, m_vector_size, m_sampling_rate));
        m_filter.push_back(new FilterBiquad(Cicm_Biquad_Highshelf, m_vector_size, m_sampling_rate));
        m_filter[j*2]->setQValue(1.);
        m_filter[j*2-1]->setQValue(1.);
        m_filter[j*2]->setGain(1.);
        m_filter[j*2-1]->setGain(1.);
    }
    m_filter.push_back(new FilterBiquad(Cicm_Biquad_Highshelf, m_vector_size, m_sampling_rate));
    m_filter.push_back(new FilterBiquad(Cicm_Biquad_Highshelf, m_vector_size, m_sampling_rate));
    m_filter[(m_number_of_harmonics-1)*2-2]->setQValue(1.);
    m_filter[(m_number_of_harmonics-1)*2-3]->setQValue(1.);
    m_filter[(m_number_of_harmonics-1)*2-2]->setGain(1.);
    m_filter[(m_number_of_harmonics-1)*2-3]->setGain(1.);
    
    m_diffuse_factor = 0.;
    initializeFrequencyBands();
}

void AmbisonicsFilter::initializeFrequencyBands()
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        double factor = (double)(i + 1.) / (double)(m_number_of_harmonics + 1);
        factor *= factor * (double)(m_sampling_rate / 2.);
        m_frequency[i] = factor;
    }
    setSamplingRate(m_sampling_rate);
}

void AmbisonicsFilter::setFrequencyBand(long anIndex, double aFrequency)
{
    if (anIndex >= 0 && anIndex < m_filter.size())
    {
        m_frequency[anIndex] = Tools::clip(aFrequency, 20., (double)m_sampling_rate / 2.);
        Tools::sortVector(m_frequency, 5);
    }
    setSamplingRate(m_sampling_rate);
}

double AmbisonicsFilter::getFrequencyBand(long anIndex)
{
    if (anIndex >= 0 && anIndex < m_filter.size())
        return m_frequency[anIndex];
    else
        return NULL;
}

void AmbisonicsFilter::setDiffusion(double aDiffuseFactor)
{
    m_diffuse_factor = Tools::clip(aDiffuseFactor, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        double factor = m_diffuse_factor;
        factor *= factor * (double)(m_number_of_harmonics - i);
        m_gain[i] = Tools::clip(factor, 0., 1.);
    }
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_filter[0]->setGain(1. - m_gain[0]);
        for(int j = 1; j < m_number_of_harmonics - 2; j++)
        {
            m_filter[j*2]->setGain(Tools::clip_min(1. - m_gain[j], 0.05));
            m_filter[j*2-1]->setGain(Tools::clip_min(1. - m_gain[j], 0.05));
        }
        m_filter[(m_number_of_harmonics-1)*2-3]->setGain(1. - m_gain[m_number_of_harmonics-2]);
        m_filter[(m_number_of_harmonics-1)*2-2]->setGain(1. - m_gain[m_number_of_harmonics-1]);
    }
}

double AmbisonicsFilter::getDiffusion()
{
    return m_diffuse_factor;
}

void AmbisonicsFilter::setVectorSize(long aVectorSize)
{
    if(m_vector_sum_double)
        cicm_free(m_vector_sum_double);
    if(m_vector_sum_float)
        cicm_free(m_vector_sum_float);
    
    Ambisonic::setVectorSize(aVectorSize);
    cicm_malloc_vec_d(m_vector_sum_double, m_vector_size);
    cicm_malloc_vec_f(m_vector_sum_float, m_vector_size);
    for(int i = 0; i < m_filter.size(); i++)
    {
        m_filter[i]->setVectorSize(m_vector_size);
    }
}

void AmbisonicsFilter::setSamplingRate(long aSamplingRate)
{
	Ambisonic::setSamplingRate(aSamplingRate);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_filter[0]->setSamplingRate(m_sampling_rate);
        m_filter[0]->setCutoffFrequency(m_frequency[0]);
        for(int j = 1; j < m_number_of_harmonics - 2; j++)
        {
            m_filter[j*2]->setSamplingRate(m_sampling_rate);
            m_filter[j*2-1]->setSamplingRate(m_sampling_rate);
            m_filter[j*2]->setCutoffFrequency(m_frequency[j]-100.);
            m_filter[j*2-1]->setCutoffFrequency(m_frequency[j]+100.);
        }
        m_filter[(m_number_of_harmonics-1)*2-3]->setSamplingRate(m_sampling_rate);
        m_filter[(m_number_of_harmonics-1)*2-2]->setSamplingRate(m_sampling_rate);
        m_filter[(m_number_of_harmonics-1)*2-3]->setCutoffFrequency(m_frequency[m_number_of_harmonics-2]);
        m_filter[(m_number_of_harmonics-1)*2-2]->setCutoffFrequency(m_frequency[m_number_of_harmonics-1]);
    }
}

AmbisonicsFilter::~AmbisonicsFilter()
{
    m_filter.clear();
    if(m_frequency)
        cicm_free(m_frequency);
    if(m_gain)
        cicm_free(m_gain);
}

