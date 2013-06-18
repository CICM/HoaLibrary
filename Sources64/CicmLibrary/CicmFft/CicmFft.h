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

#ifndef DEF_FFT
#define DEF_FFT

#include "../CicmDefine.h"
#include "../CicmTools.h"

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
#ifdef CICM_IPPS
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
	inline void forward(Cicm_Vector_Float aRealVector, Cicm_Complex_Packed_Float* anPackedVector);
	inline void inverse(Cicm_Complex_Packed_Float* anPackedVector, Cicm_Vector_Float aRealVector);
	long	getWindowSize();
	long	getArraySize();
	long	getOrder();
	double	getScale();	
	~Cicm_Fft();
};

inline void Cicm_Fft::forward(Cicm_Vector_Float aRealVector, Cicm_Complex_Packed_Float *anPackedVector)
{
#ifdef CICM_VDSP
	vDSP_ctoz((Cicm_Complex_Float *)aRealVector, 2, anPackedVector, 1, m_array_size); 
	Cicm_fft_forward(m_fft_handle, anPackedVector, m_order);
#endif
#ifdef CICM_IPPS
	Cicm_fft_forward(aRealVector, anPackedVector, m_fft_handle, m_fft_buff);
#endif
#ifdef CICM_FFTW_GSL
	Cicm_signal_copy(aRealVector, m_real_vector, m_window_size);
	Cicm_fft_forward(m_handle_forward);
	Cicm_signal_copy(m_complex_vector, anPackedVector, m_window_size);
#endif
}

inline void Cicm_Fft::inverse(Cicm_Complex_Packed_Float *anPackedVector, Cicm_Vector_Float aRealVector)
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
