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

#ifndef DEF_JCALLPASSFILTER
#define DEF_JCALLPASSFILTER

class JcAllPassFilter
{
private:
	double	m_feedback;
	long	m_delay;

	double*	m_buffer;
	long	m_buffer_size;
	long	m_ramp;

	double	m_output;

public:
    JcAllPassFilter(long aBufferSize);
    
    void	setBufferSize(long aBufferSize);
    long	getBufferSize() ;
    void	setFeedback(double aFeedbackValue);
    double	getFeedback();
    void	setDelay(long aDelayValue);
    long	getDelay();
    
	inline  double	process(double anInput);
	~AllpassFilter();
};

inline double JcAllPassFilter::process(double anInput)
{
	m_output = -anInput + m_buffer[m_ramp];
	m_buffer[m_ramp] = anInput + (m_buffer[m_ramp] * m_feedback);
	if(++m_ramp >= m_buffer_size) 
		m_ramp = 0;

	return m_output;
}

#endif