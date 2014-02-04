/* 
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "CicmFilterDiffuser.h"

FilterDiffuser::FilterDiffuser(long aBufferSize, double aCoefficient) : Filter()
{
   
	m_buffer_size_max = Tools::clip_min(aBufferSize, 2);
    cicm_malloc_vec_d(m_buffer, m_buffer_size_max);
	m_buffer = new double[m_buffer_size_max];
	m_buffer_size = m_buffer_size_max;

	m_ramp = 0;
    setCoefficient(aCoefficient);
}

void FilterDiffuser::setCoefficient(double aCoefficient)
{
    m_coefficient = Tools::clip(aCoefficient, 0., 1.);
}

double FilterDiffuser::getCoefficient()
{
    return m_coefficient;
}

void FilterDiffuser::setBufferSizeMax(long aBufferSize)
{
	cicm_free(m_buffer);
    cicm_malloc_vec_d(m_buffer, m_buffer_size_max);
	m_buffer = new double[m_buffer_size_max];
	m_buffer_size = m_buffer_size_max;
    m_ramp = 0;
}

long FilterDiffuser::getBufferSizeMax()
{
	return m_buffer_size_max;
}

void FilterDiffuser::setBufferSize(long aBufferSize)
{
    m_buffer_size = Tools::clip(aBufferSize, 1, m_buffer_size_max);
    if(m_ramp >= m_buffer_size)
        m_ramp -= m_buffer_size;
}

long FilterDiffuser::getBufferSize()
{
	return m_buffer_size;
}

FilterDiffuser::~FilterDiffuser()
{
	cicm_free(m_buffer);
}
