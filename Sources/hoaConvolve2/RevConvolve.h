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
#include "RevFir.h"
#include "RevFftConvolution.h"

class RevConvolution
{
protected:
	long		m_minimum_size;
	long		m_maximum_size;
    long        m_number_of_fft;
	FirFilter*	m_fir;
	vector <FftConvolution*> m_fft;

public:
	RevConvolution(long aMinimumSize = 128, long aMaximumSize = 16384);
	void	setImpulseResponse(Cicm_Signal* anImpulseResponse, long aSize);
	inline  Cicm_Signal process(Cicm_Signal anInput);
    
    long getMinimumSize(){return m_minimum_size;};
    long getMaximumSize(){return m_maximum_size;};
    long getNumberOfFFT(){return m_number_of_fft;};
    
	~RevConvolution();
};

inline Cicm_Signal RevConvolution::process(Cicm_Signal anInput)
{
    Cicm_Signal inputSignal = anInput;
	anInput = m_fir->process(inputSignal);
    
	for(int i = 0; i < m_number_of_fft; i++)
			anInput += m_fft[i]->process(inputSignal);
     
	return  anInput;
}

#endif