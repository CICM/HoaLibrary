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


#ifndef DEF_CONVOLUTION
#define DEF_CONVOLUTION

#include "CicmFilter.h"
#include "../CicmFft/CicmFFt.h"

class FilterConvolution
{
private:
	
	int				m_window_size;
	int				m_array_size;
	int				m_number_of_instances;
	int				m_ramp;
	int				m_hope_size;

	Cicm_Fft*			m_fft_instance;
    Cicm_Fft*			m_fft_response;
    
    cicm_vector_float*		m_real_vector;
	cicm_vector_float		m_buffer;
	Cicm_Complex_Packed_Float*		m_input_complexes;
	Cicm_Complex_Packed_Float**		m_impul_complexes;
	Cicm_Complex_Packed_Float*		m_output_complexes;
	
public:
	FilterConvolution(long aWindowSize = 1024, long aNumberOfInstances = 2);
	void loadImpulseResponse(cicm_vector_float anImpulseResponse);
    void clear();
    long getNumberOfInstances(){return m_number_of_instances;};
	
    inline float process(const float input)
    { 
        float result = m_real_vector[0][m_ramp];
        m_real_vector[0][m_ramp] = input;
        
        if(m_ramp % m_hope_size == 0 && m_ramp != 0)
        {
            int index = m_ramp / m_hope_size;
            if(index < m_number_of_instances)
            {
                Cicm_packed_mul(m_input_complexes, m_impul_complexes[index], m_output_complexes, m_array_size);
                m_output_complexes->imagp[0] = m_input_complexes->imagp[0] * m_impul_complexes[index]->imagp[0];
                
                m_fft_instance->inverse(m_output_complexes, m_real_vector[index]);
                
                if(index < m_number_of_instances - 1)
                    cicm_add_vec_vec_f(m_real_vector[index+1], m_real_vector[index], m_window_size);
            }
        }
        m_ramp++;
        if(m_ramp >= m_array_size)
        {
            cicm_copy_vec_vec_f(m_real_vector[0]+m_array_size, m_buffer, m_array_size);
            cicm_clear_vec_f(m_real_vector[0]+m_array_size, m_array_size);
            m_fft_instance->forward(m_real_vector[0], m_input_complexes);
            
            Cicm_packed_mul(m_input_complexes, m_impul_complexes[0], m_output_complexes, m_array_size);
            m_output_complexes->imagp[0] = m_input_complexes->imagp[0] * m_impul_complexes[0]->imagp[0];
            
            m_fft_instance->inverse(m_output_complexes, m_real_vector[0]);
            if(m_number_of_instances > 1)
                cicm_add_vec_vec_f(m_real_vector[1], m_real_vector[0], m_window_size);
            cicm_add_vec_vec_f(m_buffer, m_real_vector[0], m_array_size);
            m_ramp = 0;
        }
        
        return result;
    }
    
	~FilterConvolution();
};



#endif
