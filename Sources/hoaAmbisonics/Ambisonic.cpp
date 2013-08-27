/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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


Ambisonic::~Ambisonic()
{
	;
}

