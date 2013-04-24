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

#include "AmbisonicJcverb.h"

AmbisonicJcverb::AmbisonicJcverb(long anOrder)
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
        m_Jcverb.push_back(new Jcverb(abs(m_index_of_harmonics[i]), m_order * theCoeffresult[i] / factor));
    }
    delete recomposer;
}

long AmbisonicJcverb::getOrder()
{
	return m_order;
}

long AmbisonicJcverb::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicJcverb::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicJcverb::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

void AmbisonicJcverb::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_Jcverb[i]->setVectorSize(m_vector_size);
}

long AmbisonicJcverb::getVectorSize()
{
	return m_vector_size;
}

void AmbisonicJcverb::setSamplingRate(long aSamplingRate)
{
    m_sampling_rate = Tools::clip_min(aSamplingRate, (long)44100);
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_Jcverb[i]->setSamplingRate(m_sampling_rate);
}

long AmbisonicJcverb::getSamplingRate()
{
	return m_sampling_rate;
}

void AmbisonicJcverb::setroomsize(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_Jcverb[i]->setroomsize(value);
	roomsize = (value*scaleroom) + offsetroom;
}

double AmbisonicJcverb::getroomsize()
{
	return (roomsize-offsetroom)/scaleroom;
}

void AmbisonicJcverb::setdamp(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_Jcverb[i]->setdamp(value);
	damp = value*scaledamp;
}

double AmbisonicJcverb::getdamp()
{
	return damp/scaledamp;
}

void AmbisonicJcverb::setmode(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_Jcverb[i]->setmode(value);
	mode = value;
}

double AmbisonicJcverb::getmode()
{
	if (mode >= freezemode)
		return 1;
	else
		return 0;
}

void AmbisonicJcverb::setDryValue(double value)
{
    m_dry = Tools::clip(value, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_Jcverb[i]->setDryValue(m_dry);
    }
}

double AmbisonicJcverb::getDryValue()
{
    return m_dry;
}

void AmbisonicJcverb::setWetValue(double value)
{
    m_wet = Tools::clip(value, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_Jcverb[i]->setWetValue(m_wet);
    }
}

double AmbisonicJcverb::getWetValue()
{
    return m_wet;
}

void AmbisonicJcverb::computeIndex()
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

AmbisonicJcverb::~AmbisonicJcverb()
{
    free(m_index_of_harmonics);
    for(int i = 0; i < m_number_of_harmonics; i++)
	{
		delete m_Jcverb[i];
		m_Jcverb[i] = 0;
	}
}