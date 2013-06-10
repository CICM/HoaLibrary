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

#include "CicmFilterAllpass.h"

FilterAllpass::FilterAllpass(long aBufferSize) : Filter()
{
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
	m_buffer = new double[m_buffer_size_max];
	m_buffer_size = m_buffer_size_max;
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
	m_ramp = 0;
}

void FilterAllpass::setBufferSizeMax(long aBufferSize)
{
	free(m_buffer);
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
	m_buffer = new double[m_buffer_size_max];
	m_buffer_size = m_buffer_size_max;
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
    
    m_ramp = 0;
}

long FilterAllpass::getBufferSizeMax()
{
	return m_buffer_size_max;
}

void FilterAllpass::setBufferSize(long aBufferSize)
{
    m_buffer_size = Tools::clip(aBufferSize, (long)1, m_buffer_size_max);
    if(m_ramp >= m_buffer_size)
        m_ramp -= m_buffer_size;
}

long FilterAllpass::getBufferSize() 
{
	return m_buffer_size;
}

void FilterAllpass::setFeedback(double aFeedbackValue) 
{
	m_feedback = aFeedbackValue;
}

double FilterAllpass::getFeedback() 
{
	return m_feedback;
}

FilterAllpass::~FilterAllpass()
{
    free(m_buffer);
}
