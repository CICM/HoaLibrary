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

#include "CicmFilterFir.h"

FilterFir::FilterFir(long anImpulseSize)
{
	m_fir_size		= anImpulseSize;
	m_input_size	= m_fir_size * 2 - 1;

	cicm_malloc_vec_f(m_fir_vector_float, m_fir_size);
	cicm_malloc_vec_f(m_input_vector_float, m_input_size);
    cicm_malloc_vec_d(m_fir_vector_double, m_fir_size);
	cicm_malloc_vec_d(m_input_vector_double, m_input_size);
	m_index = m_fir_size;
}

void FilterFir::setImpulseResponse(cicm_vector_float anImpulseResponse)
{
	cicm_copy_vec_vec_f(anImpulseResponse, m_fir_vector_float, m_fir_size);
    for(int i = 0; i < m_fir_size; i++)
    {
        m_fir_vector_double[i] = m_fir_vector_float[i];
    }
}

void FilterFir::setImpulseResponse(cicm_vector_double anImpulseResponse)
{
	cicm_copy_vec_vec_d(anImpulseResponse, m_fir_vector_double, m_fir_size);
    for(int i = 0; i < m_fir_size; i++)
    {
        m_fir_vector_float[i] = m_fir_vector_double[i];
    }
}

FilterFir::~FilterFir()
{
	cicm_free(m_fir_vector_float);
	cicm_free(m_input_vector_float);
    cicm_free(m_fir_vector_double);
	cicm_free(m_input_vector_double);
}
