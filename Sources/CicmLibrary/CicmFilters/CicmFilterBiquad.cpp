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
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
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

#include "CicmFilterBiquad.h"

FilterBiquad::FilterBiquad(long aType, long aVectorSize, double aSamplingRate) : Filter(aVectorSize, aSamplingRate)
{
	m_type = Tools::clip(aType, Cicm_Biquad_Lowpass, Cicm_Biquad_Highshelf);
    m_cutoff_frequency = 0.5;
    m_q_value = 0.5;
    m_gain = 1.;
    m_frequency_factor = tan(CICM_PI * m_cutoff_frequency);
    computeCoefficients();
    m_delay_one = 0.;
    m_delay_two = 0.;
}

void FilterBiquad::setSamplingRate(long aSamplingRate)
{
    m_cutoff_frequency *= (double)m_sampling_rate;
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(1));
    m_cutoff_frequency /= (double)m_sampling_rate;
    m_frequency_factor = tan(CICM_PI * m_cutoff_frequency);
    computeCoefficients();
}

void FilterBiquad::setType(long aType)
{
    m_type = Tools::clip(aType, Cicm_Biquad_Lowpass, Cicm_Biquad_Highshelf);
    computeCoefficients();
}

void FilterBiquad::setAll(double aCutoffFrequency, double aQValue, double aGain)
{
    m_cutoff_frequency = Tools::clip(aCutoffFrequency, 1, (double)(m_sampling_rate / 2.));
    m_cutoff_frequency /= (double)m_sampling_rate;
    m_frequency_factor = tan(CICM_PI * m_cutoff_frequency);
    m_q_value = Tools::clip(aQValue, 0.5, 25.);
    m_gain    = aGain;
    computeCoefficients();
}

void FilterBiquad::setCutoffFrequency(double aCutoffFrequency)
{
    m_cutoff_frequency = Tools::clip(aCutoffFrequency, 0., (double)m_sampling_rate / 2.);
    m_cutoff_frequency /= (double)m_sampling_rate;
    m_frequency_factor = tan(CICM_PI * m_cutoff_frequency);
    computeCoefficients();
}

void FilterBiquad::setQValue(double aQValue)
{
    m_q_value = Tools::clip(aQValue, 0.5, 25.);
    computeCoefficients();
}

void FilterBiquad::setGain(double aGain)
{
    m_gain = Tools::clip(aGain, 0.000000001, 10.);
    computeCoefficients();
}

long FilterBiquad::getType()
{
    return m_type;
}
double FilterBiquad::getQValue()
{
    return m_q_value;
}

double  FilterBiquad::getCutoffFrequency()
{
    return m_cutoff_frequency * m_sampling_rate;
}

double  FilterBiquad::getGain()
{
    return m_gain;
}


void FilterBiquad::computeCoefficients()
{
    double norm;
    double gain = m_gain;
   
    if(m_type == Cicm_Biquad_Lowpass)
    {
        norm = 1. / (double)(1. + m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor);
        m_coeff_a0 = m_frequency_factor * m_frequency_factor * norm;
        m_coeff_a1 = 2 * m_coeff_a0;
        m_coeff_a2 = m_coeff_a0;
        m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
        m_coeff_b2 = (1 - m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor) * norm;
    }
    else if(m_type == Cicm_Biquad_Highpass)
    {
        norm = 1. / (double)(1. + m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor);
        m_coeff_a0 = 1 * norm;
        m_coeff_a1 = -2 * m_coeff_a0;
        m_coeff_a2 = m_coeff_a0;
        m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
        m_coeff_b2 = (1 - m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor) * norm;
    }
    else if(m_type == Cicm_Biquad_Bandpass)
    {
        norm = 1. / (double)(1. + m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor);
        m_coeff_a0 = m_frequency_factor / m_q_value * norm;
        m_coeff_a1 = 0.;
        m_coeff_a2 = -(m_frequency_factor / m_q_value * norm);
        m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
        m_coeff_b2 = (1 - m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor) * norm;
    }
    else if(m_type == Cicm_Biquad_Notch)
    {
        norm = 1 / (1 + m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor);
        m_coeff_a0 = (1 + m_frequency_factor * m_frequency_factor) * norm;
        m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
        m_coeff_a2 = m_coeff_a0;
        m_coeff_b1 = m_coeff_a1;
        m_coeff_b2 = (1 - m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor) * norm;
    }
    else if(m_type == Cicm_Biquad_Peak)
    {
        if (m_gain >= 0.)
        {
            norm = 1 / (1 + 1. / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = (1 + gain / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_a2 = (1 - gain / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_b1 = m_coeff_a1;
            m_coeff_b2 = (1 - 1 / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
        }
        else
        {
            norm = 1 / (1 + gain / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = (1 + 1. / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_a2 = (1 - 1. / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_b1 = m_coeff_a1;
            m_coeff_b2 = (1 - gain / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
        }
    }
    else if(m_type == Cicm_Biquad_Lowshelf)
    {
        if (m_gain >= 0.)
        {
            norm = 1 / (1 + sqrt(2) * m_frequency_factor + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = (1 + sqrt(2*gain) * m_frequency_factor + gain * m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_a1 = 2 * (gain * m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_a2 = (1 - sqrt(2*gain) * m_frequency_factor + gain * m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_b2 = (1 - sqrt(2) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
        }
        else
        {
            norm = 1 / (1 + sqrt(2*gain) * m_frequency_factor + gain * m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = (1 + sqrt(2) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_a2 = (1 - sqrt(2) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_b1 = 2 * (gain * m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_b2 = (1 - sqrt(2*gain) * m_frequency_factor + gain * m_frequency_factor * m_frequency_factor) * norm;
        }
    }
    else if(m_type == Cicm_Biquad_Highshelf)
    {
        if (m_gain >= 0.)
        {
            norm = 1 / (1 + sqrt(2) * m_frequency_factor + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = (gain + sqrt(2*gain) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - gain) * norm;
            m_coeff_a2 = (gain - sqrt(2*gain) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_b2 = (1 - sqrt(2) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
        }
        else
        {
            norm = 1 / (gain + sqrt(2*gain) * m_frequency_factor + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = (1 + sqrt(2) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_a2 = (1 - sqrt(2) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - gain) * norm;
            m_coeff_b2 = (gain - sqrt(2*gain) * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
        }
    }
}

FilterBiquad::~FilterBiquad()
{
	;
}

