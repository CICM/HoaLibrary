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

