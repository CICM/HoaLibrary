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

#include "RevConvolve.h"

RevConvolution::RevConvolution(long aMinimumSize, long aMaximumSize) 
{
	m_minimum_size = Tools::clip_power_of_two(aMinimumSize);
	m_maximum_size = Tools::clip_power_of_two(aMaximumSize);
    m_number_of_fft= 0;
	m_fir = new FirFilter(m_minimum_size);	 
}

void RevConvolution::setImpulseResponse(Cicm_Signal* anImpulseResponse, long aSize)
{
    long aResponseSize  = Tools::clip_min(Tools::clip_power_of_two(aSize), (long)m_minimum_size);
	Cicm_Signal* datas = new Cicm_Signal[aResponseSize];
	for(int i = 0; i < aResponseSize; i++)
	{
        if(i < aSize)
            datas[i] = anImpulseResponse[i];
        else
           datas[i] = 0.;
	}
    
    m_fir->setImpulseResponse(datas);
    long nFFT = 0;
    for(long i = m_minimum_size; i < aResponseSize / 2;)
    {
        if(nFFT >= m_fft.size())
            m_fft.push_back(new FftConvolution(i));
        m_fft[nFFT++]->loadImpulseResponse(datas + i, i);
        if(i < m_maximum_size)
            i *= 2;
        else
            i += m_maximum_size;
    }
    m_number_of_fft = nFFT;
    free(datas);
}

RevConvolution::~RevConvolution()
{
	delete m_fir;
    m_fft.clear();
}
