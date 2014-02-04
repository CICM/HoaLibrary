/* 
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
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
