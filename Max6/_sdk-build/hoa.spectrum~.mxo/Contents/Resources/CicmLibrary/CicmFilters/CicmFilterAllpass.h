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

#ifndef DEF_FILTERALLPASS
#define DEF_FILTERALLPASS

#include "CicmFilter.h"

class FilterAllpass : public Filter
{
private:
	double	m_feedback;

	double*	m_buffer;
	long	m_buffer_size;
    long	m_buffer_size_max;
	long	m_ramp;
public:
    FilterAllpass(long aBufferSize);
    
    void	setBufferSizeMax(long aBufferSize);
    long	getBufferSizeMax();
    void	setBufferSize(long aBufferSize);
    long	getBufferSize();
    void	setFeedback(double val);
    double	getFeedback();
    ~FilterAllpass();
    
    inline double process(double anInput)
    {
        double output = -anInput + m_buffer[m_ramp];
        m_buffer[m_ramp] = anInput + (m_buffer[m_ramp] * m_feedback);
        if(++m_ramp >= m_buffer_size)
            m_ramp = 0;
        
        return output;
    }
    
    inline float process(float anInput)
    {
        float output = -anInput + m_buffer[m_ramp];
        m_buffer[m_ramp] = anInput + (m_buffer[m_ramp] * m_feedback);
        if(++m_ramp >= m_buffer_size)
            m_ramp = 0;
        
        return output;
    }
		
};



#endif