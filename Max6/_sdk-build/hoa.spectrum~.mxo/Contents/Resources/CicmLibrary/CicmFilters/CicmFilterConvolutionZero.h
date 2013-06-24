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