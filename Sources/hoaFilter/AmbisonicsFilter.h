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

#ifndef DEF_AMBISONICSFILTER
#define DEF_AMBISONICSFILTER

#include "../hoaAmbisonics/Ambisonic.h"
#include "../CicmLibrary/CicmFilters/CicmFilterBiquad.h"

class AmbisonicsFilter : public Ambisonic
{
	
private:
    
    vector <FilterBiquad*>              m_filter;
    cicm_vector_double                  m_frequency;
    cicm_vector_double                  m_gain;
    double                              m_diffuse_factor;
        
    cicm_vector_double                  m_vector_sum_double;
    cicm_vector_float                   m_vector_sum_float;
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
            cicm_product_vec_sca_vec_d(inputs[0], m_gain[i], m_vector_sum_double, m_vector_size);
            cicm_product_vec_sca_vec_d(inputs[i], gain, inputs[i], m_vector_size);
            // ATTENTION //
            cicm_add_vec_vec_d(inputs[i], m_vector_sum_double, m_vector_size);
            
            m_filter[i*2]->process(m_vector_sum_double, m_vector_sum_double);
            m_filter[i*2-1]->process(m_vector_sum_double, outputs[i]);
        }
        gain = 1. - m_gain[m_number_of_harmonics-2];
        cicm_product_vec_sca_vec_d(inputs[0], m_gain[m_number_of_harmonics-2], m_vector_sum_double, m_vector_size);
        cicm_product_vec_sca_vec_d(inputs[m_number_of_harmonics-2], gain, inputs[m_number_of_harmonics-2], m_vector_size);
        // ATTENTION //
        cicm_add_vec_vec_d(inputs[m_number_of_harmonics-2], m_vector_sum_double, m_vector_size);
        m_filter[(m_number_of_harmonics-1)*2-3]->process(inputs[m_number_of_harmonics-2], outputs[m_number_of_harmonics-2]);
        gain = 1. - m_gain[m_number_of_harmonics-1];
        cicm_product_vec_sca_vec_d(inputs[0], m_gain[m_number_of_harmonics-1], m_vector_sum_double, m_vector_size);
        cicm_product_vec_sca_vec_d(inputs[m_number_of_harmonics-1], gain, inputs[m_number_of_harmonics-1], m_vector_size);
        m_filter[(m_number_of_harmonics-1)*2-2]->process(inputs[m_number_of_harmonics-1], outputs[m_number_of_harmonics-1]);

        
    }
};

#endif