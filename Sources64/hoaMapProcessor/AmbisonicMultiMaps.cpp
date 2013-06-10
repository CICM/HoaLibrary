/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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


#include "AmbisonicMultiMaps.h"

AmbisonicsMultiMaps::AmbisonicsMultiMaps(long anOrder, long aNumberOfSources,long aRampSample, long aVectorSize, long aSamplingRate) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
    m_number_of_sources     = Tools::clip(aNumberOfSources, (long)1, (long)64);
    if(m_number_of_sources != 1)
        m_number_of_inputs	= m_number_of_sources;
    else
        m_number_of_inputs  = 3;
    
    for(int i = 0; i < m_number_of_sources; i++)
    {
        m_maps.push_back(new AmbisonicsMap(m_order, m_vector_size));
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

