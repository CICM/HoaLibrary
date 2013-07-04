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

#include "CicmFilterComb.h"

FilterComb::FilterComb(long aBufferSize)
{
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
    m_buffer_size = m_buffer_size_max;
    Cicm_Vector_Double_Malloc(m_buffer, m_buffer_size_max);
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
    
	m_filterstore = 0;
	m_ramp = 0;
}

void FilterComb::setBufferSizeMax(long aBufferSize)
{
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
    Cicm_Free(m_buffer);
    Cicm_Vector_Double_Malloc(m_buffer, m_buffer_size_max);
	m_buffer_size = m_buffer_size_max;
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
    
    m_filterstore = 0;
    m_ramp = 0;
}

long FilterComb::getBufferSizeMax()
{
	return m_buffer_size_max;
}

void FilterComb::setBufferSize(long aBufferSize)
{
	m_buffer_size = Tools::clip(aBufferSize, (long)1, m_buffer_size_max);
    if(m_ramp >= m_buffer_size)
        m_ramp -= m_buffer_size;
}

long FilterComb::getBufferSize()
{
	return m_buffer_size;
}

void FilterComb::setDamp(double aDampValue) 
{
	m_damp1 = aDampValue; 
	m_damp2 = 1. - aDampValue;
}

double FilterComb::getDamp() 
{
	return m_damp1;
}

void FilterComb::setFeedback(double aFeedbackValue) 
{
	m_feedback = aFeedbackValue;
}

double FilterComb::getFeedback() 
{
	return m_feedback;
}

FilterComb::~FilterComb()
{
	free(m_buffer);
}
