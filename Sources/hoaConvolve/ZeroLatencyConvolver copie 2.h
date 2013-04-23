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

#ifndef DEF_CICM_CONVOLVE
#define DEF_CICM_CONVOLVE

#include "cicmTools.h"
#include "cicmFir.h"
#include "cicmFftConvolution.h"

class ZeroLatencyConvolver
{
protected:
    int		m_number_of_convolutions;

	FirFilter*	m_fir;
    FftConvolution* m_fft_128;
    FftConvolution* m_fft_256;
    FftConvolution* m_fft_512;
    FftConvolution* m_fft_1024;
    FftConvolution* m_fft_2048;
    FftConvolution* m_fft_4096;
    FftConvolution* m_fft_8192;
    FftConvolution* m_fft_16384;

public:
	ZeroLatencyConvolver();
	void	setImpulseResponse(float* anImpulResponse, long aSize);
	inline Cicm_Signal process(Cicm_Signal anInput);
    long getNumberOfFFTs(){return m_number_of_convolutions;};
    long getNumberOfInstance(){return m_fft_16384->getNumberOfInstances();};
	~ZeroLatencyConvolver();
};

inline Cicm_Signal ZeroLatencyConvolver::process(Cicm_Signal anInput)
{
    Cicm_Signal result = 0.f;
    if(m_number_of_convolutions > 0)
        result = m_fir->process(anInput);
	if(m_number_of_convolutions > 1)
        result += m_fft_128->process(anInput);
    if(m_number_of_convolutions > 3)
        result += m_fft_256->process(anInput);
    if(m_number_of_convolutions > 5)
        result += m_fft_512->process(anInput);
    if(m_number_of_convolutions > 7)
        result += m_fft_1024->process(anInput);
    if(m_number_of_convolutions > 5)
        result += m_fft_2048->process(anInput);
    if(m_number_of_convolutions > 7)
        result += m_fft_4096->process(anInput);
    if(m_number_of_convolutions > 9)
        result += m_fft_8192->process(anInput);
    if(m_number_of_convolutions > 11)
        result += m_fft_16384->process(anInput);
    
    //Cicm_Signal result = m_fft[0]->process(anInput);
	return  result;
}

#endif