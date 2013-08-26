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

#include "AmbisonicSpace.h"

AmbisonicSpace::AmbisonicSpace(long aNumberOfLoudspeakers, long aVectorSize, long aSamplingRate) : Planewaves(aNumberOfLoudspeakers, aVectorSize, aSamplingRate)
{
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_lines.push_back(new CicmLine(100., m_vector_size, m_sampling_rate));
        m_lines[i]->setCoefficientDirect(1.);
    }
    m_vector_float = NULL;
    m_vector_double = NULL;
}

double AmbisonicSpace::getCoefficient(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
       return m_lines[anIndex]->getCoefficient();
    else
        return NULL;
}

long AmbisonicSpace::getRampInSample()
{
    return m_lines[0]->getRampInSample();
}

double AmbisonicSpace::getRampInMs()
{
    return m_lines[0]->getRampInMs();
}

void AmbisonicSpace::setCoefficient(long anIndex, double aCoefficient)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
    {
        m_lines[anIndex]->setCoefficient(Tools::clip(aCoefficient, 0., 1.));
    }
}

void AmbisonicSpace::setCoefficient(double* aCoefficientVector)
{
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_lines[i]->setCoefficient(Tools::clip(aCoefficientVector[i], 0., 1.));
    }
}

void AmbisonicSpace::setCoefficient(float* aCoefficientVector)
{
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_lines[i]->setCoefficient(Tools::clip(aCoefficientVector[i], 0., 1.));
    }
}

void AmbisonicSpace::setVectorSize(long aVectorSize)
{
    Planewaves::setVectorSize(aVectorSize);
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_lines[i]->setVectorSize(m_vector_size);
    }
    if(m_vector_double)
		Cicm_Free(m_vector_double);
	if(m_vector_float)
		Cicm_Free(m_vector_float);
    Cicm_Vector_Float_Malloc(m_vector_float, m_vector_size);
	Cicm_Vector_Double_Malloc(m_vector_double, m_vector_size);
}

void AmbisonicSpace::setSamplingRate(long aSamplingRate)
{
    Planewaves::setSamplingRate(aSamplingRate);
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_lines[i]->setSamplingRate(m_sampling_rate);
    }
}

void AmbisonicSpace::setRampInSample(long aTimeInSample)
{
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_lines[i]->setRampInSample(aTimeInSample);
    }
}

void AmbisonicSpace::setRampInMs(double aTimeInMs)
{
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_lines[i]->setRampInMs(aTimeInMs);
    }
}

void AmbisonicSpace::setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff)
{
    Planewaves::setNumberOfLoudspeakers(aNumberOfLoudspeakers);
    m_lines.clear();
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_lines.push_back(new CicmLine(100., m_vector_size, m_sampling_rate));
        m_lines[i]->setCoefficientDirect(1.);
    }
}

AmbisonicSpace::~AmbisonicSpace()
{
	m_lines.clear();
    if(m_vector_double)
		Cicm_Free(m_vector_double);
	if(m_vector_float)
		Cicm_Free(m_vector_float);
}
