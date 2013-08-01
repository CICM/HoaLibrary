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


#include "CicmFft.h"

Cicm_Fft::Cicm_Fft(long aWindowSize)
{
	m_window_size	= aWindowSize;
	m_array_size	= m_window_size / 2;
	m_order			= Tools::log2(m_window_size);
	m_scale			=  1. / (double)(m_window_size * 8);

#ifdef CICM_VDSP
	m_fft_handle = Cicm_fft_init_handle(m_order);
#endif
#ifdef _WINDOWS
	Cicm_fft_get_size(m_order, &m_spec_size, &m_init_size, &m_buff_size);
	m_fft_buff = Cicm_buffer_malloc(m_buff_size);
	m_fft_init = Cicm_buffer_malloc(m_init_size);
	m_fft_spec = Cicm_buffer_malloc(m_spec_size);
	Cicm_fft_init_handle(&m_fft_handle, m_order, m_fft_spec, m_fft_init);
#endif
#ifdef CICM_FFTW_GSL
	Cicm_signal_malloc(m_real_vector, m_window_size);
	Cicm_packed_malloc(m_complex_vector, m_window_size);
	Cicm_signal_clear(m_real_vector, m_window_size);
	Cicm_signal_clear(m_complex_vector, m_window_size);
	m_handle_forward	= Cicm_fft_init_handle_forward(m_window_size, m_real_vector, m_complex_vector);
	m_handle_inverse	= Cicm_fft_init_handle_inverse(m_window_size, m_complex_vector, m_real_vector);
#endif
		
}

long	Cicm_Fft::getWindowSize()
{
	return m_window_size;
}

long	Cicm_Fft::getArraySize()
{
	return m_array_size;
}
long	Cicm_Fft::getOrder()
{
	return m_order;
}
double	Cicm_Fft::getScale()
{
	return m_scale;
}

Cicm_Fft::~Cicm_Fft()
{
#ifdef CICM_VDSP
	Cicm_fft_free_handle(m_fft_handle);
#endif
#ifdef _WINDOWS
	Cicm_free(m_fft_buff);
	Cicm_free(m_fft_init);
	Cicm_free(m_fft_spec);
	Cicm_fft_free_handle(m_fft_handle);
#endif
#ifdef CICM_FFTW_GSL
	Cicm_fft_free_handle(m_handle_forward);
	Cicm_fft_free_handle(m_handle_inverse);
	Cicm_free(m_real_vector);
	Cicm_free(m_complex_vector);
#endif
}