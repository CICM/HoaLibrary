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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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