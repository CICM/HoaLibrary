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
#ifndef DEF_FEEDBACKCOMBFILTER
#define DEF_FEEDBACKCOMBFILTER

/*******************************************************/
/** y(n) = 1 / ( 1 - a * x(n - delay)                 **/
/*******************************************************/

class FeedbackCombFilter
{
private:
	double	m_feedback;
	long	m_delay;

	double* m_buffer;
	long	m_buffer_size;
	long	m_ramp;

	double	m_output;
public:
		FeedbackCombFilter(long aBufferSize);
    
		void	setBufferSize(long aBufferSize);
		long	getBufferSize() ;
		void	setFeedback(double aFeedbackValue);
		double	getFeedback();
		void	setDelay(long aDelayValue);
		long	getDelay();
	
		inline  double	process(double anInput);
		~FeedbackCombFilter();
};


inline double FeedbackCombFilter::process(double anInput)
{
    temp = allpassDelays_[0].lastOut();
    temp0 = allpassCoefficient_ * temp;
    temp0 += input;
    allpassDelays_[0].tick(temp0);
    temp0 = -(allpassCoefficient_ * temp0) + temp;
    
    int delay = m_ramp + 1;
    if(delay >= m_buffer_size)
        delay -= m_buffer_size;
	m_output = 1. / (1. - m_feedback * m_buffer[delay]);
    m_buffer[m_ramp] = m_output;
    if(++m_ramp >= m_buffer_size) 
		m_ramp = 0;
	
	return m_output;
}
#endif
