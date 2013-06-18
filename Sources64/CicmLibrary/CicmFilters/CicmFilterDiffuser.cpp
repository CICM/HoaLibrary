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

#include "CicmFilterDiffuser.h"

FilterDiffuser::FilterDiffuser(long aBufferSize, double aCoefficient) : Filter()
{
   
	m_buffer_size_max = Tools::clip_min(aBufferSize, (long)2);
	m_buffer = new double[m_buffer_size_max];
	m_buffer_size = m_buffer_size_max;
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
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
	free(m_buffer);
    m_buffer_size_max = Tools::clip_min(aBufferSize, (long)1);
	m_buffer = new double[m_buffer_size_max];
	m_buffer_size = m_buffer_size_max;
	for(int i = 0; i < m_buffer_size_max; i++)
		m_buffer[i] = 0.;
    
    m_ramp = 0;
}

long FilterDiffuser::getBufferSizeMax()
{
	return m_buffer_size_max;
}

void FilterDiffuser::setBufferSize(long aBufferSize)
{
    m_buffer_size = Tools::clip(aBufferSize, (long)1, m_buffer_size_max);
    if(m_ramp >= m_buffer_size)
        m_ramp -= m_buffer_size;
}

long FilterDiffuser::getBufferSize()
{
	return m_buffer_size;
}

FilterDiffuser::~FilterDiffuser()
{
	free(m_buffer);
}
