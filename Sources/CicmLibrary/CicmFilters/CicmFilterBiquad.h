/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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
    Cicm_Biquad_Highpass = 1,
    Cicm_Biquad_Bandpass = 2,
    Cicm_Biquad_Notch = 3,
    Cicm_Biquad_Peak = 4,
    Cicm_Biquad_Lowshelf = 5,
    Cicm_Biquad_Highshelf = 6,
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

    void setSamplingRate(long aSamplingRate);
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
        float output = input * m_coeff_a0 + m_delay_one;
        m_delay_one = input * m_coeff_a1 + m_delay_two - m_coeff_b1 * output;
        m_delay_two = input * m_coeff_a2 - m_coeff_b2 * output;
		return output;
	}
    
	inline double process(double input)
	{
		double output = input * m_coeff_a0 + m_delay_one;
        m_delay_one = input * m_coeff_a1 + m_delay_two - m_coeff_b1 * output;
        m_delay_two = input * m_coeff_a2 - m_coeff_b2 * output;
		return output;
	}
	
	/* Perform block sample */
	inline void process(float* inputs, float* outputs)
	{
        float input, output;
        for(int i = 0; i < m_vector_size; i++)
        {
            input = inputs[i];
            output = input * m_coeff_a0 + m_delay_one;
            m_delay_one = input * m_coeff_a1 + m_delay_two - m_coeff_b1 * output;
            m_delay_two = input * m_coeff_a2 - m_coeff_b2 * output;
            outputs[i] = output;
        }
	}
    
    inline void process(float* inputs, float* outputs, float* aCutoffFrequency,float* aQValue, float* aGain)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            setAll(aCutoffFrequency[i], aQValue[i], aGain[i]);
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
    
    inline void processCurOffFrequency(float* inputs, float* outputs, float* aCutoffFrequency)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            setCutoffFrequency(aCutoffFrequency[i]);
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
    
    /**************************************************/
    /**************************************************/
    /**************************************************/
    
	inline void process(const double* inputs, double* outputs)
	{
        double input, output;
        for(int i = 0; i < m_vector_size; i++)
        {
            input = inputs[i];
            output = input * m_coeff_a0 + m_delay_one;
            m_delay_one = input * m_coeff_a1 + m_delay_two - m_coeff_b1 * output;
            m_delay_two = input * m_coeff_a2 - m_coeff_b2 * output;
            outputs[i] = output;
        }
	}
    
    inline void process(double* inputs, double* outputs, double* aQValue, double* aGain, double* aCutoffFrequency)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            setAll(aCutoffFrequency[i], aQValue[i], aGain[i]);
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
    
    inline void processCurOffFrequency(double* inputs, double* outputs, double* aCutoffFrequency)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            setCutoffFrequency(aCutoffFrequency[i]);
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
};



#endif


