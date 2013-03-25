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

#include "AmbisonicFreeverb.h"

AmbisonicFreeverb::AmbisonicFreeverb(long anOrder)
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
        m_freeverb.push_back(new Freeverb(abs(m_index_of_harmonics[i]), m_order * theCoeffresult[i] / factor));
    }
    delete recomposer;
}

long AmbisonicFreeverb::getOrder()
{
	return m_order;
}

long AmbisonicFreeverb::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicFreeverb::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicFreeverb::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

void AmbisonicFreeverb::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setVectorSize(m_vector_size);
}

long AmbisonicFreeverb::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicFreeverb::setSamplingRate(long aSamplingRate)
{
    m_sampling_rate = Tools::clip_min(aSamplingRate, (long)44100);
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setSamplingRate(m_sampling_rate);
}

long AmbisonicFreeverb::getSamplingRate()
{
	return m_sampling_rate;
}

void AmbisonicFreeverb::setroomsize(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setroomsize(value);
	roomsize = (value*scaleroom) + offsetroom;
}

double AmbisonicFreeverb::getroomsize()
{
	return (roomsize-offsetroom)/scaleroom;
}

void AmbisonicFreeverb::setdamp(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setdamp(value);
	damp = value*scaledamp;
}

double AmbisonicFreeverb::getdamp()
{
	return damp/scaledamp;
}

void AmbisonicFreeverb::setmode(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setmode(value);
	mode = value;
}

double AmbisonicFreeverb::getmode()
{
	if (mode >= freezemode)
		return 1;
	else
		return 0;
}

void AmbisonicFreeverb::setDryValue(double value)
{
    m_dry = Tools::clip(value, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_freeverb[i]->setDryValue(m_dry);
    }
}

double AmbisonicFreeverb::getDryValue()
{
    return m_dry;
}

void AmbisonicFreeverb::setWetValue(double value)
{
    m_wet = Tools::clip(value, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_freeverb[i]->setWetValue(m_wet);
    }
}

double AmbisonicFreeverb::getWetValue()
{
    return m_wet;
}

void AmbisonicFreeverb::computeIndex()
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

AmbisonicFreeverb::~AmbisonicFreeverb()
{
    free(m_index_of_harmonics);
    for(int i = 0; i < m_number_of_harmonics; i++)
	{
		delete m_freeverb[i];
		m_freeverb[i] = 0;
	}
}