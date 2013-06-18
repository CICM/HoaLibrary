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

#include "CicmOnePole.h"

AmbisonicOnePole::AmbisonicOnePole(double aSamplingRate, long aVectorSize)
{
    setSamplingRate(aSamplingRate);
    setVectorSize(aVectorSize);
}

void AmbisonicOnePole::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void AmbisonicOnePole::setSamplingRate(double aSamplingRate)
{
	m_samplig_rate = Tools::clip_min(aSamplingRate, 0.);
    setCutOffFrequency(m_cut_off_frequency);
}

void AmbisonicOnePole::setCutOffFrequency(double aFrequency)
{
    m_cut_off_frequency = Tools::clip(aFrequency, 0., m_samplig_rate / 2.);
    m_coeff_a = sin(CICM_2PI * m_cut_off_frequency / m_samplig_rate);
    m_coeff_b = - (1. - m_coeff_a);
}

long AmbisonicOnePole::getVectorSize()
{
	return m_vector_size;    
}

double AmbisonicOnePole::getSamplingRate()
{
	return m_samplig_rate;
}

double  AmbisonicOnePole::getCoeffA()
{
    return m_coeff_a;
}

double  AmbisonicOnePole::getCoeffB()
{
    return m_coeff_b;
}

double  AmbisonicOnePole::getCutOffFrequency()
{
    return m_cut_off_frequency;
}

AmbisonicOnePole::~AmbisonicOnePole()
{
    ;
}
