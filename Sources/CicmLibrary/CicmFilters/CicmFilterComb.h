/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
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
