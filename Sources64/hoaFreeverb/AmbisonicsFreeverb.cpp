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

#include "AmbisonicsFreeverb.h"

AmbisonicsFreeverb::AmbisonicsFreeverb(long anOrder, long aVectorSize, double aSamplingRate) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
    m_diffuse = 0;
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb.push_back(new Freeverb());
}

void AmbisonicsFreeverb::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setVectorSize(m_vector_size);
}

void AmbisonicsFreeverb::setSamplingRate(long aSamplingRate)
{
    m_sampling_rate = Tools::clip_min(aSamplingRate, (long)44100);
    for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setSamplingRate(m_sampling_rate);
}


void AmbisonicsFreeverb::setroomsize(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setroomsize(value);
	roomsize = (value*scaleroom) + offsetroom;
}

double AmbisonicsFreeverb::getroomsize()
{
	return (roomsize-offsetroom)/scaleroom;
}

void AmbisonicsFreeverb::setdamp(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setdamp(value);
	damp = value*scaledamp;
}

double AmbisonicsFreeverb::getdamp()
{
	return damp/scaledamp;
}

void AmbisonicsFreeverb::setmode(double value)
{
	for(int i = 0; i < m_number_of_harmonics; i++)
        m_freeverb[i]->setmode(value);
	mode = value;
}

double AmbisonicsFreeverb::getmode()
{
	if (mode >= freezemode)
		return 1;
	else
		return 0;
}

void AmbisonicsFreeverb::setDryValue(double value)
{
    m_dry = Tools::clip(value, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_freeverb[i]->setDryValue(m_dry);
    }
}

double AmbisonicsFreeverb::getDryValue()
{
    return m_dry;
}

void AmbisonicsFreeverb::setWetValue(double value)
{
    m_wet = Tools::clip(value, 0., 1.);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        m_freeverb[i]->setWetValue(m_wet);
    }
}

double AmbisonicsFreeverb::getWetValue()
{
    return m_wet;
}

void AmbisonicsFreeverb::setSpread(double value)
{
    setDiffuseSpread(value);
    setDirectionalSpread(value);
}

void AmbisonicsFreeverb::setDirectionalSpread(double value)
{
    m_directional_spread = Tools::clip(value, 0., 1.);
    double spreadOne;
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        if(getHarmonicIndex(i) >= 0)
            spreadOne = m_diffuse_spread * m_diffuse_spread * m_diffuse_spread * ((double)getHarmonicOrder(i) / (double)m_order);
        else
            spreadOne = m_diffuse_spread * m_diffuse_spread * m_diffuse_spread * ((double)(getHarmonicOrder(i) - 0.5) / (double)m_order);
        m_freeverb[i]->setDiffuseSpread(spreadOne);
    }
}

void AmbisonicsFreeverb::setDiffuseSpread(double value)
{
    m_diffuse_spread = Tools::clip(value, 0., 1.);
    double spreadTwo;
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        if(getHarmonicIndex(i) >= 0)
            spreadTwo = m_diffuse_spread * m_diffuse_spread * m_diffuse_spread * ((double)getHarmonicOrder(i) / (double)m_order);
        else
            spreadTwo = m_diffuse_spread * m_diffuse_spread * m_diffuse_spread * ((double)(getHarmonicOrder(i) - 0.5) / (double)m_order);
        m_freeverb[i]->setDirectionalSpread(spreadTwo);
    }
}

double AmbisonicsFreeverb::getDiffuseSpread()
{
    return m_diffuse_spread;
}

double AmbisonicsFreeverb::getDirectionalSpread()
{
    return m_directional_spread;
}

AmbisonicsFreeverb::~AmbisonicsFreeverb()
{
    m_freeverb.clear();
}