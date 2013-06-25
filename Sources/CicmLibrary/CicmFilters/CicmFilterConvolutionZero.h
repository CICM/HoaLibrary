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

#ifndef DEF_CONVOLUTION_ZERO
#define DEF_CONVOLUTION_ZERO

#include "CicmFilter.h"
#include "CicmFilterConvolution.h"
#include "CicmFilterFir.h"

class FilterConvolutionZero
{
protected:
	int     m_minimum_size;
	int		m_maximum_size;
	int		m_number_of_ffts;
    int		m_ffts_useds;

	FilterFir*	m_fir;
	vector <FilterConvolution*> m_fft;

public:
	FilterConvolutionZero(long aMinimumSize = 128, long aMaximumSize = 32768);
	void	setImpulseResponse(float* anImpulResponse, long aSize);
    void    clear();
	
    long getNumberOfFFTs(){return m_ffts_useds;};
    long getNumberOfInstance(){return m_fft[m_number_of_ffts-1]->getNumberOfInstances();};
    
    inline Cicm_Float process(Cicm_Float anInput)
    {
        Cicm_Float result = m_fir->process(anInput);
        
        for(int i = 0; i < m_ffts_useds; i++)
			result += m_fft[i]->process(anInput);
        
        return  result;
    }
    
	~FilterConvolutionZero();
};



#endif