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
	int     m_minimum_size;
	int		m_maximum_size;
	int		m_number_of_ffts;
    int		m_ffts_useds;

	FirFilter*	m_fir;
	vector <FftConvolution*> m_fft;

public:
	ZeroLatencyConvolver(long aMinimumSize = 128, long aMaximumSize = 32768);
	void	setImpulseResponse(float* anImpulResponse, long aSize);
	inline Cicm_Signal process(Cicm_Signal anInput);
    long getNumberOfFFTs(){return m_ffts_useds;};
    long getNumberOfInstance(){return m_fft[m_number_of_ffts-1]->getNumberOfInstances();};
	~ZeroLatencyConvolver();
};

inline Cicm_Signal ZeroLatencyConvolver::process(Cicm_Signal anInput)
{
	Cicm_Signal result = m_fir->process(anInput);
    
	for(int i = 0; i < m_ffts_useds; i++)
			result += m_fft[i]->process(anInput);
 
	return  result;
}

#endif