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

#ifndef DEF_FFT
#define DEF_FFT

#include "../CicmDefine.h"

class Cicm_Fft
{
private:
	long				m_window_size;
	long				m_array_size;
	long				m_order;
	double				m_scale;

#ifdef CICM_VDSP
	Cicm_Fft_Handle		m_fft_handle;
#endif
#ifdef _WINDOWS
	int					m_spec_size;
	int					m_init_size;
	int					m_buff_size;

	Cicm_Fft_Handle*	m_fft_handle;
	Cicm_Fft_Buffer*	m_fft_buff;
	Cicm_Fft_Buffer*	m_fft_init;
	Cicm_Fft_Buffer*	m_fft_spec;
#endif
#ifdef CICM_FFTW_GSL
	Cicm_Fft_Handle		m_handle_forward;
	Cicm_Fft_Handle		m_handle_inverse;
	Cicm_Signal*		m_real_vector;
	Cicm_Packed*		m_complex_vector;
#endif
	
public:
	Cicm_Fft(long aWindowSize = 1024);
	inline void forward(cicm_vector_float aRealVector, Cicm_Complex_Packed_Float* anPackedVector);
	inline void inverse(Cicm_Complex_Packed_Float* anPackedVector, cicm_vector_float aRealVector);
	long	getWindowSize();
	long	getArraySize();
	long	getOrder();
	double	getScale();	
	~Cicm_Fft();
};

inline void Cicm_Fft::forward(cicm_vector_float aRealVector, Cicm_Complex_Packed_Float *anPackedVector)
{
#ifdef CICM_VDSP
	vDSP_ctoz((Cicm_Complex_Float *)aRealVector, 2, anPackedVector, 1, m_array_size); 
	Cicm_fft_forward(m_fft_handle, anPackedVector, m_order);
#endif
#ifdef _WINDOWS
	Cicm_fft_forward(aRealVector, anPackedVector, m_fft_handle, m_fft_buff);
#endif
#ifdef CICM_FFTW_GSL
	Cicm_signal_copy(aRealVector, m_real_vector, m_window_size);
	Cicm_fft_forward(m_handle_forward);
	Cicm_signal_copy(m_complex_vector, anPackedVector, m_window_size);
#endif
}

inline void Cicm_Fft::inverse(Cicm_Complex_Packed_Float *anPackedVector, cicm_vector_float aRealVector)
{
#ifdef CICM_VDSP
	Cicm_fft_inverse(m_fft_handle, anPackedVector, m_order);
	vDSP_ztoc(anPackedVector, 1, (Cicm_Complex_Float *)aRealVector, 2, m_array_size);
#endif
#ifdef CICM_IPPS
	Cicm_fft_inverse(anPackedVector, aRealVector, m_fft_handle, m_fft_buff);
#endif
#ifdef CICM_FFTW_GSL
	Cicm_signal_copy(anPackedVector, m_complex_vector, m_window_size);
	Cicm_fft_inverse(m_handle_inverse);
	Cicm_signal_copy(m_real_vector, aRealVector, m_window_size);
#endif
}
#endif
