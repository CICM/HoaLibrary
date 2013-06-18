/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
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

#include "AmbisonicsGigaverb.h"

AmbisonicsGigaverb::AmbisonicsGigaverb(long anOrder, long aVectorSize, double aSamplingRate) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_gigaverb.push_back(new Gigaverb(m_vector_size, m_sampling_rate));
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
        m_gigaverb[i]->setVectorSize(m_vector_size);
    }
}

void AmbisonicsGigaverb::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(0));
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setSamplingRate(m_sampling_rate);
    }

}

AmbisonicsGigaverb::~AmbisonicsGigaverb()
{
    m_gigaverb.clear();
}