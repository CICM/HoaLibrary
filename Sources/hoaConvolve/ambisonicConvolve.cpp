/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & CICM_PIerre Guillot, Universite Paris 8
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

#include "ambisonicConvolve.hpp"

ambisonicConvolve::ambisonicConvolve(long anOrder, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= m_number_of_harmonics;
}

long ambisonicConvolve::getOrder()
{
	return m_order;
}

long ambisonicConvolve::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long ambisonicConvolve::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long ambisonicConvolve::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

void ambisonicConvolve::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_min(aVectorSize, (long)1);
}

long ambisonicConvolve::getVectorSize()
{
	return m_vector_size;
}

ambisonicConvolve::~ambisonicConvolve()
{
	;
}


