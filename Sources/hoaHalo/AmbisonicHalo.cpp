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

#include "AmbisonicHalo.h"

AmbisonicHalo::AmbisonicHalo(long anOrder, long aVectorSize)
{	
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_outputs		= m_number_of_harmonics;
	m_number_of_inputs		= m_number_of_harmonics + 2;

	m_optim					= new AmbisonicOptim(m_order, "inPhase");
	m_encoder				= new AmbisonicEncode(m_order);
	m_wider					= new AmbisonicWider(m_order);

	m_input_vector			= new double[m_number_of_harmonics];
	m_output_vector			= new double[m_number_of_harmonics];
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		m_input_vector[i]	= 0.;
		m_output_vector[i]	= 0.;
	}

	setSpread(1.);
	setVectorSize(aVectorSize);
}

long AmbisonicHalo::getOrder()
{
	return m_order;
}

long AmbisonicHalo::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicHalo::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicHalo::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicHalo::getVectorSize()
{
	return m_vector_size;
}

double AmbisonicHalo::getSpread()
{
	return m_spread;
}

void AmbisonicHalo::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

void AmbisonicHalo::setSpread(double aWidenValue)
{
	m_spread = Tools::clip(aWidenValue, 0., 1.);
	m_spread = sqrt(m_spread);
	m_spread = sqrt(m_spread);
}

AmbisonicHalo::~AmbisonicHalo()
{
	delete m_encoder;
	delete m_optim;
	delete m_input_vector;
	delete m_output_vector;
}