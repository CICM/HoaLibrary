/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris UniFilterBiquadersite Paris 8
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

#include "CicmFilterBiquad.h"

FilterBiquad::FilterBiquad(long aType, long aVectorSize, double aSamplingRate) : Filter(aVectorSize, aSamplingRate)
{
	m_type = Tools::clip(aType, (long)Cicm_Biquad_Lowpass, (long)Cicm_Biquad_Highshelf);
    m_cutoff_frequency = 0.5;
    m_q_value = 0.5;
    m_gain = 1.;
    m_frequency_factor = tan(CICM_PI * m_cutoff_frequency);
    computeCoefficients();
    m_delay_one = 0.;
    m_delay_two = 0.;
}

void FilterBiquad::setType(long aType)
{
    m_type = Tools::clip(aType, (long)Cicm_Biquad_Lowpass, (long)Cicm_Biquad_Highshelf);
    computeCoefficients();
}

void FilterBiquad::setAll(double aCutoffFrequency, double aQValue, double aGain)
{
    m_cutoff_frequency = Tools::clip(aCutoffFrequency, 0.00001, (double)(m_sampling_rate / 2.));
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
    m_gain = aGain;
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
    double gain = pow(10, fabs(m_gain) / 20.0);
    switch (m_type)
    {
        case Cicm_Biquad_Lowpass:
            norm = 1 / (1 + m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = m_frequency_factor * m_frequency_factor * norm;
            m_coeff_a1 = 2 * m_coeff_a0;
            m_coeff_a2 = m_coeff_a0;
            m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_b2 = (1 - m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor) * norm;
            break;
            
        case Cicm_Biquad_Highpass:
            norm = 1 / (1 + m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = 1 * norm;
            m_coeff_a1 = -2 * m_coeff_a0;
            m_coeff_a2 = m_coeff_a0;
            m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_b2 = (1 - m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor) * norm;
            break;
            
        case Cicm_Biquad_Bandpass:
            norm = 1 / (1 + m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = m_frequency_factor / m_q_value * norm;
            m_coeff_a1 = 0;
            m_coeff_a2 = -m_coeff_a0;
            m_coeff_b1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_b2 = (1 - m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor) * norm;
            break;
            
        case Cicm_Biquad_Notch:
            norm = 1 / (1 + m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor);
            m_coeff_a0 = (1 + m_frequency_factor * m_frequency_factor) * norm;
            m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
            m_coeff_a2 = m_coeff_a0;
            m_coeff_b1 = m_coeff_a1;
            m_coeff_b2 = (1 - m_frequency_factor / m_q_value + m_frequency_factor * m_frequency_factor) * norm;
            break;
            
        case Cicm_Biquad_Peak:
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
            break;
        case Cicm_Biquad_Lowshelf:
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
            break;
        case Cicm_Biquad_Highshelf:
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
            break;
        case Cicm_Biquad_Ambisonics:
            if (m_gain >= 0.)
            {
                norm = 1 / (1 + 1. / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor);
                m_coeff_a0 = (1 + gain / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
                m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
                m_coeff_a2 = (1 - gain / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
                m_coeff_b1 = m_coeff_a1;
                m_coeff_b2 = (1 - 1 / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
                m_weight = 1. / gain;
            }
            else
            {
                norm = 1 / (1 + gain / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor);
                m_coeff_a0 = (1 + 1. / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
                m_coeff_a1 = 2 * (m_frequency_factor * m_frequency_factor - 1) * norm;
                m_coeff_a2 = (1 - 1. / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
                m_coeff_b1 = m_coeff_a1;
                m_coeff_b2 = (1 - gain / m_q_value * m_frequency_factor + m_frequency_factor * m_frequency_factor) * norm;
                m_weight = 1. / gain;
            }
            break;
    }
}

FilterBiquad::~FilterBiquad()
{
	;
}

