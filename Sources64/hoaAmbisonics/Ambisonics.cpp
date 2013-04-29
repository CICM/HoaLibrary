/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#include "Ambisonics.h"

Ambisonics::Ambisonics(long anOrder, long aVectorSize, double aSamplingRate)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= m_number_of_harmonics;
	
	setVectorSize(aVectorSize);
    setSamplingRate(aSamplingRate);
}

long Ambisonics::getOrder()
{
	return m_order;
}

long Ambisonics::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long Ambisonics::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long Ambisonics::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long Ambisonics::getVectorSize()
{
	return m_vector_size;
}

long Ambisonics::getSamplingRate()
{
	return m_sampling_rate;
}

long Ambisonics::getHarmonicIndex(long anIndex)
{
    int index;
    if (anIndex == 0)
        return 0;
    else if(anIndex > 0 && anIndex < m_number_of_harmonics)
    {
        index = (anIndex - 1) / 2. + 1.;
        if (anIndex % 2 == 1)
            index = -index;
        return index;
    }
    else
        return 0;
}

long Ambisonics::getHarmonicOrder(long anIndex)
{
    return abs(getHarmonicIndex(anIndex));
}

void Ambisonics::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void Ambisonics::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(0));
}

Ambisonics::~Ambisonics()
{
	;
}

