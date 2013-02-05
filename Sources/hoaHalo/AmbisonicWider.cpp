/*
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

#include "AmbisonicWider.h"

AmbisonicWider::AmbisonicWider(long anOrder, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics + 1;
	m_number_of_outputs		= m_number_of_harmonics;

	setVectorSize(aVectorSize);

	computeIndex();	
	computeWidenVector();
	setWidenValue(1.);
}

long AmbisonicWider::getOrder()
{
	return m_order;
}

long AmbisonicWider::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicWider::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicWider::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicWider::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicWider::computeIndex()
{
	m_index_of_harmonics	= new long[m_number_of_harmonics ];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = (i - 1) / 2 + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void AmbisonicWider::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}


void AmbisonicWider::computeWidenVector()
{
	m_minus_vector	= new double[m_number_of_harmonics];
	m_dot_vector	= new double[m_number_of_harmonics];

	m_order_weight = log((double)(m_order + 1));
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_minus_vector[i] = Tools::clip_min(log((double)abs(m_index_of_harmonics[i])), 0.);
		m_dot_vector[i]	= Tools::clip_min(log((double)abs(m_index_of_harmonics[i]) + 1.), 0.);
		m_dot_vector[i] -= m_minus_vector[i];
		m_dot_vector[i] = 1. / m_dot_vector[i];
	}
}

void AmbisonicWider::setWidenValue(double aWidenValue)
{
	m_widen_value = Tools::clip(aWidenValue, 0., 1.);
}

AmbisonicWider::~AmbisonicWider()
{
	free(m_index_of_harmonics);
	free(m_minus_vector);
	free(m_dot_vector);
}

