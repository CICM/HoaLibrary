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

#ifndef DEFFIR
#define DEFFIR

#include "CicmFilter.h"

class FilterFir : public Filter
{
protected:
	
	cicm_vector_float	m_input_vector_float;
	cicm_vector_float	m_fir_vector_float;
    cicm_vector_double	m_input_vector_double;
	cicm_vector_double	m_fir_vector_double;
	long			m_fir_size;
	long			m_input_size;
	int             m_index;;

public:
	FilterFir(long anImpulseSize = 128);
    
	void	setImpulseResponse(cicm_vector_float anImpulseResponse);
    void    setImpulseResponse(cicm_vector_double anImpulseResponse);
    
    inline float process(float input)
    {
        float result;
        m_input_vector_float[--m_index] = input;
        cicm_dot_product_f(m_input_vector_float+m_index, m_fir_vector_float, result, m_fir_size);
        if(m_index <= 0)
        {
            m_index = m_fir_size;
            cicm_copy_vec_vec_f(m_input_vector_float, m_input_vector_float+m_fir_size, m_fir_size);
        }
        return result;
    }
    
    inline double process(double input)
    {
        double result;
        m_input_vector_double[--m_index] = input;
        cicm_dot_product_d(m_input_vector_double+m_index, m_fir_vector_double, result, m_fir_size);
        if(m_index <= 0)
        {
            m_index = m_fir_size;
            cicm_copy_vec_vec_d(m_input_vector_double, m_input_vector_double+m_fir_size, m_fir_size);
        }
        return result;
    }
    
	~FilterFir();
};



#endif