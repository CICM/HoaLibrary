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

#include "CicmFilterComb.h"

FilterComb::FilterComb(long aBufferSize)
{
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
    m_buffer_size = m_buffer_size_max;
    cicm_malloc_vec_d(m_buffer, m_buffer_size_max);
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
    
	m_filterstore = 0;
	m_ramp = 0;
}

void FilterComb::setBufferSizeMax(long aBufferSize)
{
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
    cicm_free(m_buffer);
    cicm_malloc_vec_d(m_buffer, m_buffer_size_max);
	m_buffer_size = m_buffer_size_max;
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
    
    m_filterstore = 0;
    m_ramp = 0;
}

long FilterComb::getBufferSizeMax()
{
	return m_buffer_size_max;
}

void FilterComb::setBufferSize(long aBufferSize)
{
	m_buffer_size = Tools::clip(aBufferSize, (long)1, m_buffer_size_max);
    if(m_ramp >= m_buffer_size)
        m_ramp -= m_buffer_size;
}

long FilterComb::getBufferSize()
{
	return m_buffer_size;
}

void FilterComb::setDamp(double aDampValue) 
{
	m_damp1 = aDampValue; 
	m_damp2 = 1. - aDampValue;
}

double FilterComb::getDamp() 
{
	return m_damp1;
}

void FilterComb::setFeedback(double aFeedbackValue) 
{
	m_feedback = aFeedbackValue;
}

double FilterComb::getFeedback() 
{
	return m_feedback;
}

FilterComb::~FilterComb()
{
	free(m_buffer);
}
