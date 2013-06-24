/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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
    Cicm_Vector_Float*		m_real_vector;
	Cicm_Vector_Float		m_buffer;
	Cicm_Complex_Packed_Float*		m_input_complexes;
	Cicm_Complex_Packed_Float**		m_impul_complexes;
	Cicm_Complex_Packed_Float*		m_output_complexes;
	
public:
	FilterConvolution(long aWindowSize = 1024, long aNumberOfInstances = 2);
	void loadImpulseResponse(Cicm_Vector_Float anImpulseResponse);
    void clear();
    long getNumberOfInstances(){return m_number_of_instances;};
	
    inline Cicm_Float process(Cicm_Float anInput)
    { 
        Cicm_Float result = m_real_vector[0][m_ramp];
        m_real_vector[0][m_ramp] = anInput;
        
        if(m_ramp % m_hope_size == 0 && m_ramp != 0)
        {
            int index = m_ramp / m_hope_size;
            if(index < m_number_of_instances)
            {
                Cicm_packed_mul(m_input_complexes, m_impul_complexes[index], m_output_complexes, m_array_size);
                m_output_complexes->imagp[0] = m_input_complexes->imagp[0] * m_impul_complexes[index]->imagp[0];
                
                m_fft_instance->inverse(m_output_complexes, m_real_vector[index]);
                
                if(index < m_number_of_instances - 1)
                    Cicm_Vector_Float_Add(m_real_vector[index+1], m_real_vector[index], m_window_size);
            }
        }
        m_ramp++;
        if(m_ramp >= m_array_size)
        {
            Cicm_Vector_Float_Copy(m_real_vector[0]+m_array_size, m_buffer, m_array_size);
            Cicm_Vector_Float_Clear(m_real_vector[0]+m_array_size, m_array_size);
            m_fft_instance->forward(m_real_vector[0], m_input_complexes);
            
            Cicm_packed_mul(m_input_complexes, m_impul_complexes[0], m_output_complexes, m_array_size);
            m_output_complexes->imagp[0] = m_input_complexes->imagp[0] * m_impul_complexes[0]->imagp[0];
            
            m_fft_instance->inverse(m_output_complexes, m_real_vector[0]);
            if(m_number_of_instances > 1)
                Cicm_Vector_Float_Add(m_real_vector[1], m_real_vector[0], m_window_size);
            Cicm_Vector_Float_Add(m_buffer, m_real_vector[0], m_array_size);
            m_ramp = 0;
        }
        
        return result;
    }
    
	~FilterConvolution();
};



#endif
