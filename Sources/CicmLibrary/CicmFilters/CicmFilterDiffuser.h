/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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

#ifndef DEF_FILTERDIFFUSER
#define DEF_FILTERDIFFUSER

#include "CicmFilter.h"

class FilterDiffuser : public Filter
{
private:
    double              m_coefficient;
    
	cicm_vector_double	m_buffer;
	long                m_buffer_size;
    long                m_buffer_size_max;
	long                m_ramp;

public:
	FilterDiffuser(long aBufferSize, double aCoefficient);
    void	setCoefficient(double aCoefficient);
    double  getCoefficient();
    void	setBufferSizeMax(long aBufferSize);
    long	getBufferSizeMax();
    void	setBufferSize(long aBufferSize);
    long	getBufferSize();
    ~FilterDiffuser();
    
	inline double process(double aValue)
    {
        double w = aValue - m_buffer[m_ramp] * m_coefficient;
        double y = m_buffer[m_ramp] + w * m_coefficient;
        m_buffer[m_ramp] = w;
        if (++m_ramp >= m_buffer_size)
            m_ramp = 0;
        
        return y;
    }
    
	
};


#endif