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

#include "revFeedbackCombFilter.h"

FeedbackCombFilter::FeedbackCombFilter(long aBufferSize)
{
    m_buffer = new double[aBufferSize];
	m_buffer_size = aBufferSize;
	for(int i = 0; i < m_buffer_size; i++)
		m_buffer[i] = 0.;
    
	m_ramp = 0;
    setDelay(aBufferSize);
    setFeedback(0.7);
}

void FeedbackCombFilter::setBufferSize(long aBufferSize)
{
	free(m_buffer);
	m_buffer = new double[aBufferSize];
	m_buffer_size = aBufferSize;
	for(int i = 0; i < m_buffer_size; i++)
		m_buffer[i] = 0.;
    
    m_ramp = 0;
}

long FeedbackCombFilter::getBufferSize()
{
	return m_buffer_size;
}


void FeedbackCombFilter::setFeedback(double aFeedbackValue) 
{
	m_feedback = aFeedbackValue;
}

double FeedbackCombFilter::getFeedback() 
{
	return m_feedback;
}

void FeedbackCombFilter::setDelay(long aDelayValue)
{
    m_delay = aDelayValue;
    if(m_delay > m_buffer_size)
        m_delay = m_buffer_size;
    if(m_delay < 0)
        m_delay = 0;
}

long FeedbackCombFilter::getDelay()
{
    return m_delay;
}

FeedbackCombFilter::~FeedbackCombFilter()
{
	free(m_buffer);
}
