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

#include "revJcverb.h"

Jcverb::Jcverb(long anOrder, double aFactor)
{
	m_factor = aFactor;
    m_order = anOrder;
    
    for(int i = m_order; i < numcombs; i++)
    {
        m_comb_filter.push_back(new FeedbackCombFilter((long)(DelayCombTuning[i] + m_factor * spread)));
        m_comb_filter[i - m_order]->setFeedback(FeedbackCombTuning[i]);
    }
    
    for(int i = 0; i < numallpasses; i++)
    {
        m_allpass_filter.push_back(new AllpassFilter((long)(allpasstuning[i] + m_factor * spread)));
        m_allpass_filter[i]->setFeedback(0.7f);
    }
    m_sampling_rate = 44100;
	setroomsize(initialroom);
	setdamp(initialdamp);
	setmode(initialmode);
    setDryValue(0.);
    setWetValue(1.);
}

void Jcverb::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

long Jcverb::getVectorSize()
{
	return m_vector_size;
}

void Jcverb::setSamplingRate(long aSamplingRate)
{
    m_sampling_rate = aSamplingRate;
    
    for(int i = m_order; i < numcombs; i++)
        m_comb_filter[i - m_order]->setBufferSize((long)((DelayCombTuning[i] + m_factor * spread) * m_sampling_rate / 44100.));
    for(int i = 0; i < numallpasses; i++)
        m_allpass_filter[i]->setBufferSize((long)((allpasstuning[i] + m_factor * spread) * m_sampling_rate / 44100.));
}

long Jcverb::getSamplingRate()
{
	return m_sampling_rate;
}


void Jcverb::update()
{
	if (mode >= freezemode)
	{
		roomsize1 = 1;
		damp1 = 0;
		m_gain = muted;
	}
	else
	{
		roomsize1 = roomsize;
		damp1 = damp;
		m_gain = fixedgain;
	}

}

void Jcverb::setroomsize(double value)
{
	if(value <= 0.)
		value = 0.;
	else if (value >= 1.)
		value = 1;
	roomsize = (value*scaleroom) + offsetroom;
	update();
}

double Jcverb::getroomsize()
{
	return (roomsize-offsetroom)/scaleroom;
}

void Jcverb::setdamp(double value)
{
	if(value <= 0.)
		value = 0.;
	else if (value >= 1.)
		value = 1;
	damp = value*scaledamp;
	update();
}

double Jcverb::getdamp()
{
	return damp/scaledamp;
}

void Jcverb::setmode(double value)
{
	if(value <= 0.)
		value = 0.;
	else if (value >= 1.)
		value = 1;
	mode = value;
	update();
}

double Jcverb::getmode()
{
	if (mode >= freezemode)
		return 1;
	else
		return 0;
}

void Jcverb::setDryValue(double value)
{
    m_dry = Tools::clip(value, 0., 1.);
}

double Jcverb::getDryValue()
{
    return m_dry;
}

void Jcverb::setWetValue(double value)
{
    m_wet = Tools::clip(value, 0., 1.);
}

double Jcverb::getWetValue()
{
    return m_wet;
}

Jcverb::~Jcverb()
{
    for(int i = m_order; i < numcombs; i++)
	{
		delete m_comb_filter[i - m_order];
		m_comb_filter[i - m_order] = 0;
	}
    for(int i = 0; i < numallpasses; i++)
	{
		delete m_allpass_filter[i];
		m_allpass_filter[i] = 0;
	}
    
}
