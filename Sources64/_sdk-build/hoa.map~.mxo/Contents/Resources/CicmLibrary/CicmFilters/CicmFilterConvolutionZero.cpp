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

#include "CicmFilterConvolutionZero.h"

FilterConvolutionZero::FilterConvolutionZero(long aMinimumSize, long aMaximumSize) 
{
	m_minimum_size = aMinimumSize;
	m_maximum_size = aMaximumSize;
	m_number_of_ffts = 0;

	m_fir = new FilterFir(m_minimum_size);
	
	for(long windowSize = m_minimum_size; windowSize < m_maximum_size * 2; windowSize *= 2)
	{
		m_fft.push_back(new FilterConvolution(windowSize, 1));
	}
    m_number_of_ffts = m_fft.size();
    m_ffts_useds = 0;
}

void FilterConvolutionZero::setImpulseResponse(float* anImpulseResponse, long aSize)
{
    m_ffts_useds = 0;
    
    /* TIME CONVOLUTION *******************************************/
    if(aSize > 0 && aSize <= m_minimum_size)
    {
        Cicm_Float *datas  = new Cicm_Float[m_minimum_size];
        for(int i = 0; i < m_minimum_size; i++)
        {
            if(i < aSize)
                datas[i] = anImpulseResponse[i];
            else
                datas[i] = 0.;
        }
        m_fir->setImpulseResponse(datas);
        free(datas);
    }
    else if(aSize > m_minimum_size)
        m_fir->setImpulseResponse(anImpulseResponse);
    
    /* FFT CONVOLUTION ********************************************/
    int offset      = m_minimum_size;
    int windowSize  = m_minimum_size;
    /* FFTs INTERMEDIAIRES */
    for(int i = 0; i < m_number_of_ffts - 1; i++)
	{
        if (aSize >= windowSize + offset)
        {
            m_fft[i]->loadImpulseResponse(anImpulseResponse + offset);
            m_ffts_useds++;
        }
        else if(aSize > offset &&  aSize < windowSize + offset)
        {
            Cicm_Float *datas  = new Cicm_Float[windowSize];
            for(int j = 0; j < windowSize; j++)
            {
                if(j + offset < aSize)
                    datas[j] = anImpulseResponse[j + offset];
                else
                    datas[j] = 0.;
            }
            m_fft[i]->loadImpulseResponse(datas);
            m_ffts_useds++;
            free(datas);
        }
        offset += windowSize;
        windowSize *= 2;
	}
    /* GRANDES FFTs */
    if(aSize >= offset)
    {
        long numberOfFFT = ((double)(aSize - offset) / (double)m_maximum_size) + 1;
        long dataSize = numberOfFFT * m_maximum_size;
        Cicm_Float *datas  = new Cicm_Float[dataSize];
        if(numberOfFFT != m_fft[m_number_of_ffts-1]->getNumberOfInstances())
        {
            m_fft.pop_back();
            m_fft.push_back(new FilterConvolution(m_maximum_size, numberOfFFT));
        }
        for(int i = 0; i < dataSize; i++)
        {
            if(i + offset < aSize)
                datas[i] = anImpulseResponse[i + offset];
            else
                datas[i] = 0.;
        }
        m_fft[m_number_of_ffts-1]->loadImpulseResponse(datas);
        free(datas);
        m_ffts_useds++;
    }
}

void FilterConvolutionZero::clear()
{
    for(int i = 0; i < m_number_of_ffts; i++)
        m_fft[i]->clear();
}

FilterConvolutionZero::~FilterConvolutionZero()
{
	delete m_fir;
	m_fft.clear();
}
