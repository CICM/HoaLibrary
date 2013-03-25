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

#include "AmbisonicGigaverb.h"

AmbisonicGigaverb::AmbisonicGigaverb(long anOrder)
{

    m_order					= Tools::clip_min(anOrder, (long)1);
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= m_number_of_harmonics;
    computeIndex();
    
    ambisonicRecomposer* recomposer  = new ambisonicRecomposer(m_order, m_number_of_harmonics +1, m_number_of_harmonics);
    double* myReverbForm = new double[m_number_of_harmonics +1];
    double* theCoeffresult = new double[m_number_of_harmonics];
    
    for(int i = 0; i < (m_number_of_harmonics + 1) / 2; i++)
    {
        myReverbForm[i] = 0.3 * ((double)i / ((m_number_of_harmonics + 1) / 2)) + 0.7;
        myReverbForm[(m_number_of_harmonics + 1) / 2 - 1 - i] = 0.3 * ((double)(i - 0.25)/ ((m_number_of_harmonics + 1) / 2)) + 0.7;
    }
    recomposer->process(myReverbForm, theCoeffresult);
    double factor = 0;
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        if (fabs(theCoeffresult[i]) > factor)
        {
            factor = fabs(theCoeffresult[i]);
        }
    }

    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb.push_back(new Gigaverb(abs(m_index_of_harmonics[i]), theCoeffresult[i] / factor));
    }
    delete recomposer;
}

long AmbisonicGigaverb::getOrder()
{
	return m_order;
}

long AmbisonicGigaverb::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicGigaverb::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicGigaverb::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

void AmbisonicGigaverb::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

long AmbisonicGigaverb::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicGigaverb::setSamplingRate(long aSamplingRate)
{
    m_sampling_rate = Tools::clip_min(aSamplingRate, (long)44100);
}

long AmbisonicGigaverb::getSamplingRate()
{
	return m_sampling_rate;
}


void AmbisonicGigaverb::setDryValue(double value)
{
    m_dry = Tools::clip(value, 0., 1.);
}

double AmbisonicGigaverb::getDryValue()
{
    return m_dry;
}

void AmbisonicGigaverb::setWetValue(double value)
{
    m_wet = Tools::clip(value, 0., 1.);
}

double AmbisonicGigaverb::getWetValue()
{
    return m_wet;
}
void AmbisonicGigaverb::setRoomSize(double aRoomSize)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setRoomSize(aRoomSize);
    }
}

double AmbisonicGigaverb::getRoomSize()
{
    return m_gigaverb[0]->getRoomSize();
}

void AmbisonicGigaverb::setReverberationTime(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setReverberationTime(aValue);
    }
}

double AmbisonicGigaverb::getReverberationTime()
{
    return m_gigaverb[0]->getReverberationTime();
}

void AmbisonicGigaverb::setDamping(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setDamping(aValue);
    }
}

double AmbisonicGigaverb::getDamping()
{
    return m_gigaverb[0]->getDamping();
}

void AmbisonicGigaverb::setInputBandwidth(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setInputBandwidth(aValue);
    }
}

double AmbisonicGigaverb::getInputBandwidth()
{
    return m_gigaverb[0]->getInputBandwidth();
}

void AmbisonicGigaverb::setEarlyLevel(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setEarlyLevel(aValue);
    }
}

double AmbisonicGigaverb::getEarlyLevel()
{
    return m_gigaverb[0]->getEarlyLevel();
}

void AmbisonicGigaverb::setTailLevel(double aValue)
{
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_gigaverb[i]->setTailLevel(aValue);
    }
}

double AmbisonicGigaverb::getTailLevel()
{
    return m_gigaverb[0]->getTailLevel();
}

void AmbisonicGigaverb::computeIndex()
{
	m_index_of_harmonics	= new long[m_number_of_harmonics];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = (i - 1) / 2 + 1;
		if (i % 2 == 1)
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

AmbisonicGigaverb::~AmbisonicGigaverb()
{
    free(m_index_of_harmonics);
    for(int i = 0; i < m_number_of_harmonics; i++)
	{
		delete m_gigaverb[i];
		m_gigaverb[i] = 0;
	}
}