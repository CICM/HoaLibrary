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

#include "CicmFilterComb.h"

FilterComb::FilterComb(long aBufferSize)
{
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
    m_buffer = new double[m_buffer_size_max];
	m_buffer_size = m_buffer_size_max;
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
    
	m_filterstore = 0;
	m_ramp = 0;
}

void FilterComb::setBufferSizeMax(long aBufferSize)
{
	free(m_buffer);
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
	m_buffer = new double[m_buffer_size_max];
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
