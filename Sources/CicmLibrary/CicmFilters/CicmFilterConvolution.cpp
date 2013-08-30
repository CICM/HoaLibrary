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

    m_real_vector		= new Cicm_Vector_Float[m_number_of_instances];
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

void FilterConvolution::loadImpulseResponse(Cicm_Vector_Float anImpulseResponse)
{
	Cicm_Vector_Float real;
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