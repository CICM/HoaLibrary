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

#include "Ambisonic.h"

Ambisonic::Ambisonic(long anOrder, long aVectorSize, long aSamplingRate)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= m_number_of_harmonics;
	
	setVectorSize(aVectorSize);
    setSamplingRate(aSamplingRate);
}

long Ambisonic::getOrder()
{
	return m_order;
}

long Ambisonic::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long Ambisonic::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long Ambisonic::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long Ambisonic::getVectorSize()
{
	return m_vector_size;
}

long Ambisonic::getSamplingRate()
{
	return m_sampling_rate;
}

long Ambisonic::getHarmonicIndex(long anIndex)
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

long Ambisonic::getHarmonicOrder(long anIndex)
{
    return abs(getHarmonicIndex(anIndex));
}

void Ambisonic::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void Ambisonic::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(0));
}

std::string Ambisonic::getHarmonicsName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_harmonics)
        return "Harmonic " + Tools::intToString(getHarmonicIndex(anIndex));
    else
        return "No harmonic";
}

std::string Ambisonic::getInputName(long anIndex)
{
    return getHarmonicsName(anIndex);
}

std::string Ambisonic::getOutputName(long anIndex)
{
    return getHarmonicsName(anIndex);
}


Ambisonic::~Ambisonic()
{
	;
}

