/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#ifndef DEF_FILTERBIQUAD
#define DEF_FILTERBIQUAD

#include "CicmFilter.h"

enum
{
    Cicm_Biquad_Lowpass = 0,
    Cicm_Biquad_Highpass,
    Cicm_Biquad_Bandpass,
    Cicm_Biquad_Notch,
    Cicm_Biquad_Peak,
    Cicm_Biquad_Lowshelf,
    Cicm_Biquad_Highshelf,
    Cicm_Biquad_Ambisonics
};

class FilterBiquad : public Filter
{
protected:
    long    m_type;
    double  m_coeff_a0, m_coeff_a1, m_coeff_a2, m_coeff_b1, m_coeff_b2;
    double  m_cutoff_frequency, m_q_value, m_gain;
    double  m_frequency_factor;
    double  m_delay_one, m_delay_two;
    double  m_weight;
    void    computeCoefficients();
public:
	FilterBiquad(long aType, long aVectorSize = 0, double aSamplingRate = 44100.);

    void setType(long aType);
    void setAll(double aCutoffFrequency, double aQValue, double aGain);
    void setCutoffFrequency(double aCutoffFrequency);
    void setQValue(double aQValue);
    void setGain(double aGain);
    
    long    getType();
    double  getQValue();
    double  getCutoffFrequency();
    double  getGain();
    
	~FilterBiquad();
	
	/* Perform sample by sample */
	inline float process(float input)
	{
        if(m_type == Cicm_Biquad_Ambisonics)
            input *= m_weight;
        float output = input * m_coeff_a0 + m_delay_one;
        m_delay_one = input * m_coeff_a1 + m_delay_two - m_coeff_b1 * output;
        m_delay_two = input * m_coeff_a2 - m_coeff_b2 * output;
		return output;
	}
    
	inline double process(double input)
	{
        if(m_type == Cicm_Biquad_Ambisonics)
            input *= m_weight;
		double output = input * m_coeff_a0 + m_delay_one;
        m_delay_one = input * m_coeff_a1 + m_delay_two - m_coeff_b1 * output;
        m_delay_two = input * m_coeff_a2 - m_coeff_b2 * output;
		return output;
	}
	
	/* Perform block sample */
	inline void process(float* inputs, float* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_type == Cicm_Biquad_Ambisonics)
                inputs[i] *= m_weight;
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
    
    inline void process(float* inputs, float* outputs, float* aCutoffFrequency,float* aQValue, float* aGain)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_type == Cicm_Biquad_Ambisonics)
                inputs[i] *= m_weight;
            setAll(aCutoffFrequency[i], aQValue[i], aGain[i]);
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
    
	inline void process(double* inputs, double* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_type == Cicm_Biquad_Ambisonics)
                inputs[i] *= m_weight;
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
    
    inline void process(double* inputs, double* outputs, double* aQValue, double* aGain, double* aCutoffFrequency)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_type == Cicm_Biquad_Ambisonics)
                inputs[i] *= m_weight;
            setAll(aCutoffFrequency[i], aQValue[i], aGain[i]);
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
};



#endif


