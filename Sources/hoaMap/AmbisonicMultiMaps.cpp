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

#include "AmbisonicMultiMaps.h"

AmbisonicsMultiMaps::AmbisonicsMultiMaps(long anOrder, long aNumberOfSources,long aRampSample, long aVectorSize, long aSamplingRate) : Ambisonic(anOrder, aVectorSize, aSamplingRate)
{
    m_number_of_sources     = Tools::clip(aNumberOfSources, (long)1, (long)64);
    if(m_number_of_sources != 1)
        m_number_of_inputs	= m_number_of_sources;
    else
        m_number_of_inputs  = 3;
    
    for(int i = 0; i < m_number_of_sources; i++)
    {
        m_maps.push_back(new AmbisonicMap(m_order, m_vector_size));
        setCoordinatesPolar(i, 1., 0.);
        m_mute[i] = 0;
    }
    setVectorSize(aVectorSize);
    m_first_source = 0;
    
}

long AmbisonicsMultiMaps::getNumberOfSources()
{
	return m_number_of_sources;
}

double AmbisonicsMultiMaps::getRadius(long aSourceIndex)
{
    return m_radius[aSourceIndex];
}

double AmbisonicsMultiMaps::getAzimuth(long aSourceIndex)
{
    return m_azimuth[aSourceIndex];
}

long AmbisonicsMultiMaps::getMuted(long aSourceIndex)
{
    if(aSourceIndex >= 0 && aSourceIndex < m_number_of_sources)
    {
        return m_mute[aSourceIndex];
    }
    return 1;
}

void AmbisonicsMultiMaps::setRamp(long aNumberOfSample)
{
    for(int i = 0; i < m_number_of_sources; i++)
        m_maps[i]->setRamp(aNumberOfSample);
}

long AmbisonicsMultiMaps::getRamp()
{
    return m_maps[0]->getRamp();
}

void AmbisonicsMultiMaps::setNumberOfSources(long aNumberOfSources)
{
    if(aNumberOfSources > 0)
    {
        if(aNumberOfSources > m_number_of_sources)
        {
            for(int i = m_number_of_sources; i < aNumberOfSources; i++)
            {
                m_maps.push_back(new AmbisonicMap(m_order, m_vector_size));
                setCoordinatesPolar(i, 1., 0.);
                m_mute[i] = 0;
            }
        }
        else
        {
            for(int i = m_number_of_sources; i > aNumberOfSources; i--)
            {
                m_maps.pop_back();
            }
        }
        m_number_of_sources = m_maps.size();
        setMuted(0, getMuted(0));
    }
}

void AmbisonicsMultiMaps::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    for(int i = 0; i < m_number_of_sources; i++)
        m_maps[i]->setVectorSize(m_vector_size);
}

void AmbisonicsMultiMaps::setCoordinatesPolar(long aSourceIndex, double aRadius, double anAzimuth)
{
    if(aSourceIndex >= 0 && aSourceIndex < m_number_of_sources)
        m_maps[aSourceIndex]->setCoordinatesPolarLine(aRadius, anAzimuth);
}

void AmbisonicsMultiMaps::setCoordinatesRadius(long aSourceIndex, double aRadius)
{
    if(aSourceIndex >= 0 && aSourceIndex < m_number_of_sources)
        m_maps[aSourceIndex]->setCoordinatesRadiusLine(aRadius);
}

void AmbisonicsMultiMaps::setCoordinatesAzimuth(long aSourceIndex, double anAzimuth)
{
    if(aSourceIndex >= 0 && aSourceIndex < m_number_of_sources)
        m_maps[aSourceIndex]->setCoordinatesAzimuthLine(anAzimuth);
}

void AmbisonicsMultiMaps::setCoordinatesCartesian(long aSourceIndex, double anAbscissa, double anOrdinate)
{
    if(aSourceIndex >= 0 && aSourceIndex < m_number_of_sources)
        m_maps[aSourceIndex]->setCoordinatesCartesianLine(anAbscissa, anOrdinate);
}

void AmbisonicsMultiMaps::setCoordinatesAbscissa(long aSourceIndex, double anAbscissa)
{
    if(aSourceIndex >= 0 && aSourceIndex < m_number_of_sources)
        m_maps[aSourceIndex]->setCoordinatesAbscissaLine(anAbscissa);
}

void AmbisonicsMultiMaps::setCoordinatesOrdinate(long aSourceIndex, double anOrdinate)
{
    if(aSourceIndex >= 0 && aSourceIndex < m_number_of_sources)
        m_maps[aSourceIndex]->setCoordinatesOrdinateLine(anOrdinate);
}

void AmbisonicsMultiMaps::setMuted(long aSourceIndex, long aValue)
{
    if(aSourceIndex >= 0 && aSourceIndex < m_number_of_sources)
    {
        m_mute[aSourceIndex] = Tools::clip(aValue, (long)0, (long)1);
    }
    
    m_first_source = m_number_of_sources;
    for(int i = m_number_of_sources-1; i >= 0; i--)
    {
        if(m_mute[i] == 0)
            m_first_source = i;
    }
}

std::string AmbisonicsMultiMaps::getSourceName(long anIndex)
{
    if(m_number_of_sources != 1)
    {
        if(anIndex > 0 && anIndex < m_number_of_sources)
            return "Source " + Tools::intToString(anIndex);
        else if(anIndex == 0)
            return "Source 0, sources coordinates";
        else
            return "No source";
    }
    else
    {
        if(anIndex == 0)
            return "Source 0, source coordinates";
        else if(anIndex == 1)
            return "Coordinate Radius or Abscissa";
        else
            return "Coordinate Azimuth or Ordinate";
    }
    return "No source";
}

AmbisonicsMultiMaps::~AmbisonicsMultiMaps()
{
	m_maps.clear();
}

