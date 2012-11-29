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

#include "AmbisonicConvolve.h"

AmbisonicConvolve::AmbisonicConvolve(long anOrder, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= m_number_of_harmonics;
	
	for(int i = 0; i < m_number_of_harmonics; i++)
		m_convolution.push_back(new GardnerConvolution());
}

long AmbisonicConvolve::getOrder()
{
	return m_order;
}

long AmbisonicConvolve::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicConvolve::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicConvolve::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

void AmbisonicConvolve::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_min(aVectorSize, (long)1);
}

long AmbisonicConvolve::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicConvolve::setImpulseResponse(long aInstance, double* anImpulResponse, long aSize)
{
	aInstance = Tools::clip(aInstance, (long)0, m_number_of_harmonics);
	m_convolution[aInstance]->setImpulseResponse(anImpulResponse, aSize);
}
AmbisonicConvolve::~AmbisonicConvolve()
{
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		delete m_convolution[i];
		m_convolution[i] = 0;
	}
}

