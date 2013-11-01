/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    
    inline double process(const double input)
    {
        float inp = input;
        float result = m_fir->process(inp);
        
        for(int i = 0; i < m_ffts_useds; i++)
			result += m_fft[i]->process(inp);
        
        return result;
    }
    
    inline float process(const float input)
    {
        float result = m_fir->process(input);
        
        for(int i = 0; i < m_ffts_useds; i++)
			result += m_fft[i]->process(input);
        
        return result;
    }
    
	~FilterConvolutionZero();
};



#endif