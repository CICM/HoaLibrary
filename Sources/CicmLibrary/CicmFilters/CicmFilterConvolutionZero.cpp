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
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
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
        float *datas  = new float[m_minimum_size];
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
            float *datas  = new float[windowSize];
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
        float *datas  = new float[dataSize];
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
