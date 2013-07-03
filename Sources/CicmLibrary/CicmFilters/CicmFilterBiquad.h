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

#ifndef DEF_FILTERBIQUAD
#define DEF_FILTERBIQUAD

#include "CicmFilter.h"

enum
{
    Cicm_Biquad_Lowpass = 0,
    Cicm_Biquad_Highpass = 1,
    Cicm_Biquad_Bandpass = 2,
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
    
    inline void processCurOffFrequency(float* inputs, float* outputs, float* aCutoffFrequency)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_type == Cicm_Biquad_Ambisonics)
                inputs[i] *= m_weight;
            setCutoffFrequency(aCutoffFrequency[i]);
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
    
	inline void process(double* inputs, double* outputs)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
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
    
    inline void processCurOffFrequency(double* inputs, double* outputs, double* aCutoffFrequency)
	{
        for(int i = 0; i < m_vector_size; i++)
        {
            if(m_type == Cicm_Biquad_Ambisonics)
                inputs[i] *= m_weight;
            setCutoffFrequency(aCutoffFrequency[i]);
            outputs[i] = inputs[i] * m_coeff_a0 + m_delay_one;
            m_delay_one = inputs[i] * m_coeff_a1 + m_delay_two - m_coeff_b1 * outputs[i];
            m_delay_two = inputs[i] * m_coeff_a2 - m_coeff_b2 * outputs[i];
        }
	}
};



#endif


