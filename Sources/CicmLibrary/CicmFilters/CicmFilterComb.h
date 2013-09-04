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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#ifndef DEF_FilterComb
#define DEF_FilterComb

/*******************************************************/
/** y(n) = a * x(n) + b * x(n-delay) + c * y(n-delay) **/
/*******************************************************/

#include "CicmFilter.h"

class FilterComb : public Filter
{
private:
	double	m_feedback;
	double	m_filterstore;
	double	m_damp1;
	double	m_damp2;

	double* m_buffer;
	long	m_buffer_size;
    long	m_buffer_size_max;
	long	m_ramp;

public:
		FilterComb(long aBufferSize);
    
		void	setBufferSizeMax(long aBufferSize);
		long	getBufferSizeMax();
        void	setBufferSize(long aBufferSize);
        long	getBufferSize();
    
		void	setDamp(double aDampValue);
		double	getDamp();
		void	setFeedback(double aFeedbackValue);
		double	getFeedback();
		void	setFeedforward(double aFeedforwardValue);
		double	getFeedforward();
		void	setDelay(double aValue);
		double	getDelay();
		~FilterComb();
    
    inline double process(const double anInput)
    {
        double output = m_buffer[m_ramp];
        m_filterstore = (output * m_damp2) + (m_filterstore * m_damp1);
        m_buffer[m_ramp] = anInput + (m_filterstore * m_feedback);
        if(++m_ramp >= m_buffer_size)
            m_ramp = 0;
        
        return output;
    }
    
    inline double process(const float anInput)
    {
        float output = m_buffer[m_ramp];
        m_filterstore = (output * m_damp2) + (m_filterstore * m_damp1);
        m_buffer[m_ramp] = anInput + (m_filterstore * m_feedback);
        if(++m_ramp >= m_buffer_size)
            m_ramp = 0;
        
        return output;
    }
};



#endif
