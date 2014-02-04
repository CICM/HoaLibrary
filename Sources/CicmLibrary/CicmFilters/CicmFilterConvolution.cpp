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

#include "CicmFilterConvolution.h"

FilterConvolution::FilterConvolution(long aWindowSize, long aNumberOfInstances)
{
	m_fft_instance	= new Cicm_Fft(aWindowSize*2); // Due to zero padding //
    m_fft_response  = new Cicm_Fft(aWindowSize*2);
	m_window_size	= m_fft_instance->getWindowSize();
	m_array_size	= m_fft_instance->getArraySize();
	m_number_of_instances = Tools::clip_min(aNumberOfInstances, (long)1);
	m_hope_size		= m_array_size / m_number_of_instances;		
	m_ramp = 0;

    m_real_vector		= new cicm_vector_float[m_number_of_instances];
	m_impul_complexes	= new Cicm_Complex_Packed_Float*[m_number_of_instances];
	
	Cicm_Complex_Packed_Float_Malloc(m_input_complexes, m_window_size);
	Cicm_Complex_Packed_Float_Malloc(m_output_complexes, m_window_size);
	cicm_malloc_vec_f(m_buffer, m_array_size);
	
	Cicm_packed_clear(m_input_complexes, m_window_size);
	Cicm_packed_clear(m_output_complexes, m_window_size);;
    
	for(int i = 0; i < m_number_of_instances; i++)
	{
		cicm_malloc_vec_f(m_real_vector[i], m_window_size);
		Cicm_Complex_Packed_Float_Malloc(m_impul_complexes[i], m_window_size);
		Cicm_packed_clear(m_impul_complexes[i], m_window_size);
	}
	
}

void FilterConvolution::loadImpulseResponse(cicm_vector_float anImpulseResponse)
{
	cicm_vector_float real;
	cicm_malloc_vec_f(real, m_window_size);
  
	for(int i = 0; i < m_number_of_instances; i++)
	{
		for(int j = 0; j < m_window_size; j++)
        {
            if(j < m_array_size)
                real[j] = anImpulseResponse[j + m_array_size * i] * m_fft_instance->getScale();
            else
                real[j] = 0.;
        }
		m_fft_response->forward(real, m_impul_complexes[i]);
        
	}
	cicm_free(real);
}

void FilterConvolution::clear()
{
    for(int i = 0; i < m_number_of_instances; i++)
		cicm_clear_vec_f(m_real_vector[i], m_window_size);
}

FilterConvolution::~FilterConvolution()
{
	cicm_free(m_buffer);
	cicm_free(m_input_complexes);
	cicm_free(m_output_complexes);
	for(int i = 0; i < m_number_of_instances; i++)
	{
		cicm_free(m_real_vector[i]);
		cicm_free(m_impul_complexes[i]);
	}
	free(m_real_vector);
	free(m_impul_complexes);
	delete m_fft_instance;
    delete m_fft_response;
}