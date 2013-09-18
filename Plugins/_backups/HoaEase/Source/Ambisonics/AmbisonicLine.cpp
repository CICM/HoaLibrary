/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#include "AmbisonicLine.h"

AmbisonicLine::AmbisonicLine(long aVectorSize)
{
    m_value_old = 0.;
    m_value_new = 0.;
    m_value_step = 0.;
    m_counter = 0;
    
    setVectorSize(aVectorSize);
}

double AmbisonicLine::getVectorSize()
{
	return m_vector_size;    
}

double AmbisonicLine::getValue()
{
    return m_value_new;
}

void AmbisonicLine::setCoefficientDirect(double aCoefficient)
{
    m_value_old = m_value_new = aCoefficient;
    m_value_step = 0.;
    m_counter = 0;
}

void AmbisonicLine::setCoefficient(double aCoefficient)
{
    m_value_new  = aCoefficient;
    m_value_step = (m_value_new - m_value_old) / (double)RAMP_SAMPLE;
    m_counter = 0;
}

void AmbisonicLine::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_value_step = (m_value_new - m_value_old) / (double)RAMP_SAMPLE;
    m_counter = 0;
}

AmbisonicLine::~AmbisonicLine()
{
    ;
}
