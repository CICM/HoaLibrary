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

#ifndef DEF_AMBISONICSFILTER
#define DEF_AMBISONICSFILTER

#include "../hoaAmbisonics/Ambisonics.h"
#include "../CicmLibrary/CicmFilters/CicmFilterBiquad.h"

class AmbisonicsFilter : public Ambisonics
{
	
private:
    
    vector <FilterBiquad*>              m_filter;
    Cicm_Vector_Double                  m_frequency;
    Cicm_Vector_Double                  m_gain;
    double                              m_diffuse_factor;
        
    Cicm_Vector_Double                  m_vector_sum_double;
    Cicm_Vector_Float                   m_vector_sum_float;
    void initializeFrequencyBands();
    
public:
	AmbisonicsFilter(long anOrder = 1, long aVectorSize = 0, long aSamplingRate = 44100);
    
    void    setDiffusion(double aDiffuseFactor);
    double  getDiffusion();
    void    setFrequencyBand(long anIndex, double aFrequency);
    double  getFrequencyBand(long anIndex);
    
    void setVectorSize(long aVectorSize);
    void setSamplingRate(long aSamplingRate);
    
	~AmbisonicsFilter();
	
    inline void process(float* inputs, float* outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            outputs[i] = m_filter[i]->process(inputs[i]);
        }
	}
    
	inline void process(double* inputs, double* outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            outputs[i] = m_filter[i]->process(inputs[i]);
        }
    }
	
	inline void process(float** inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
        {
            m_filter[i]->process(inputs[i], outputs[i]);
        }
	}
    
	inline void process(double** inputs, double** outputs)
	{
        double gain = 1.;
        m_filter[0]->process(inputs[0], outputs[0]);
        for(int i = 1; i < m_number_of_harmonics - 2; i++)
        {
            gain = 1. - m_gain[i];
            Cicm_Vector_Scalar_Double_Mul(inputs[0], m_gain[i], m_vector_sum_double, m_vector_size);
            Cicm_Vector_Scalar_Double_Mul(inputs[i], gain, inputs[i], m_vector_size);
            Cicm_Vector_Double_Sum(m_vector_sum_double, inputs[i], m_vector_sum_double, m_vector_size);
            
            m_filter[i*2]->process(m_vector_sum_double, m_vector_sum_double);
            m_filter[i*2-1]->process(m_vector_sum_double, outputs[i]);
        }
        gain = 1. - m_gain[m_number_of_harmonics-2];
        Cicm_Vector_Scalar_Double_Mul(inputs[0], m_gain[m_number_of_harmonics-2], m_vector_sum_double, m_vector_size);
        Cicm_Vector_Scalar_Double_Mul(inputs[m_number_of_harmonics-2], gain, inputs[m_number_of_harmonics-2], m_vector_size);
        Cicm_Vector_Double_Sum(m_vector_sum_double, inputs[m_number_of_harmonics-2], m_vector_sum_double, m_vector_size);
        m_filter[(m_number_of_harmonics-1)*2-3]->process(inputs[m_number_of_harmonics-2], outputs[m_number_of_harmonics-2]);
        gain = 1. - m_gain[m_number_of_harmonics-1];
        Cicm_Vector_Scalar_Double_Mul(inputs[0], m_gain[m_number_of_harmonics-1], m_vector_sum_double, m_vector_size);
        Cicm_Vector_Scalar_Double_Mul(inputs[m_number_of_harmonics-1], gain, inputs[m_number_of_harmonics-1], m_vector_size);
        m_filter[(m_number_of_harmonics-1)*2-2]->process(inputs[m_number_of_harmonics-1], outputs[m_number_of_harmonics-1]);

        
    }
};

#endif