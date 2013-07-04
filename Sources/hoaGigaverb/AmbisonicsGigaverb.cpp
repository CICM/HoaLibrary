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

#include "AmbisonicsGigaverb.h"

AmbisonicsGigaverb::AmbisonicsGigaverb(long anOrder, long aVectorSize, double aSamplingRate) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_gigaverb.push_back(new Gigaverb(m_sampling_rate));
}

void AmbisonicsGigaverb::setDryValue(double value)
{
    m_dry = Tools::clip(value, 0., 1.);
}

double AmbisonicsGigaverb::getDryValue()
{
    return m_dry;
}

void AmbisonicsGigaverb::setWetValue(double value)
{
    m_wet = Tools::clip(value, 0., 1.);
}

double AmbisonicsGigaverb::getWetValue()
{
    return m_wet;
}
void AmbisonicsGigaverb::setRoomSize(double aRoomSize)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setRoomSize(aRoomSize);
    }
}

double AmbisonicsGigaverb::getRoomSize()
{
    return m_gigaverb[0]->getRoomSize();
}

void AmbisonicsGigaverb::setReverberationTime(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setReverberationTime(aValue);
    }
}

double AmbisonicsGigaverb::getReverberationTime()
{
    return m_gigaverb[0]->getReverberationTime();
}

void AmbisonicsGigaverb::setDamping(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setDamping(aValue);
    }
}

double AmbisonicsGigaverb::getDamping()
{
    return m_gigaverb[0]->getDamping();
}

void AmbisonicsGigaverb::setInputBandwidth(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setInputBandwidth(aValue);
    }
}

double AmbisonicsGigaverb::getInputBandwidth()
{
    return m_gigaverb[0]->getInputBandwidth();
}

void AmbisonicsGigaverb::setEarlyLevel(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setEarlyLevel(aValue);
    }
}

double AmbisonicsGigaverb::getEarlyLevel()
{
    return m_gigaverb[0]->getEarlyLevel();
}

void AmbisonicsGigaverb::setTailLevel(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setTailLevel(aValue);
    }
}

double AmbisonicsGigaverb::getTailLevel()
{
    return m_gigaverb[0]->getTailLevel();
}

void AmbisonicsGigaverb::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        //m_gigaverb[i]->setVectorSize(m_vector_size);
    }
}

void AmbisonicsGigaverb::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(0));
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        //m_gigaverb[i]->setSamplingRate(m_sampling_rate);
    }

}

AmbisonicsGigaverb::~AmbisonicsGigaverb()
{
    m_gigaverb.clear();
}