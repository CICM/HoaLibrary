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
    
    setDiffuseSpread(m_diffuse);
    setDirectionalSpread(m_directional_spread);
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
            spreadOne = m_directional_spread * m_directional_spread * m_directional_spread * ((double)getHarmonicOrder(i) / (double)m_order);
        else
            spreadOne = m_directional_spread * m_directional_spread * m_directional_spread * ((double)(getHarmonicOrder(i) - 0.5) / (double)m_order);
        m_freeverb[i]->setDirectionalSpread(spreadOne);
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
        m_freeverb[i]->setDiffuseSpread(spreadTwo);
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