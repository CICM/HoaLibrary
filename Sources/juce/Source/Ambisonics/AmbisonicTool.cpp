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


#include "AmbisonicTool.h"

AmbisonicTool::AmbisonicTool(long aNumberOfLoudspeakers, long aNumberOfSources, long aVectorSize)
{
    Tools::clip(aNumberOfLoudspeakers, (long)3, (long)64);
	m_number_of_loudspeakers = aNumberOfLoudspeakers;
    if(m_number_of_loudspeakers%2 == 0)
        m_order = m_number_of_loudspeakers / 2 - 1;
    else
         m_order = m_number_of_loudspeakers / 2 - 0.5;
    
    Tools::clip(aNumberOfSources, (long)1, (long)64);
    m_number_of_sources = aNumberOfSources;
    for(int i = 0; i < m_number_of_sources; i++)
    {
        m_encoders.push_back(new AmbisonicEncoder(m_order));
        m_widers.push_back(new AmbisonicWider(m_order));
    }
    m_decoder = new AmbisonicDecode(m_order, m_number_of_loudspeakers);
    for(int i = 0; i < 63; i++)
    {
        m_harmonics_block_vector[i] = new float[128];
        m_harmonics_block_copy[i] = new float[128];
    }
    
    setVectorSize(aVectorSize);
    
    m_number_of_harmonics = 2 * m_order  +1;
    m_number_of_inputs = m_number_of_sources;
    m_number_of_outputs = m_number_of_loudspeakers;
    
   for(int i = 0; i < m_number_of_sources; i++)
       setPolarCoordinates(i, 1., 0.);
     
}

long AmbisonicTool::getOrder()
{
	return m_order;
}

long AmbisonicTool::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicTool::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicTool::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicTool::getVectorSize()
{
	return m_vector_size;
}

long AmbisonicTool::getNumberOfLoudspeakers()
{
	return m_number_of_loudspeakers;
}

long AmbisonicTool::getNumberOfSources()
{
	return m_number_of_sources;
}

float AmbisonicTool::getRadius(long aSourceIndex)
{
    return m_radius[aSourceIndex];
}

float AmbisonicTool::getAzimuth(long aSourceIndex)
{
    return m_azimuth[aSourceIndex];
}

void AmbisonicTool::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    for(int i = 0; i < 63; i++)
    {
        free(m_harmonics_block_vector[i]);
        free(m_harmonics_block_copy[i]);
        m_harmonics_block_vector[i] = new float[m_vector_size];
        m_harmonics_block_copy[i] = new float[m_vector_size];
    }
    
    for(int i = 0; i < m_number_of_sources; i++)
    {
        m_encoders[i]->setVectorSize(m_vector_size);
        m_widers[i]->setVectorSize(m_vector_size);
    }
    m_decoder->setVectorSize(m_vector_size);
}

void AmbisonicTool::setPolarCoordinates(long aSourceIndex, double aRadius, double anAzimuth)
{
    if(aSourceIndex > 0 && aSourceIndex <= m_number_of_sources)
    {
        aSourceIndex--;
        m_widers[aSourceIndex]->setAzimtuh(anAzimuth);
        m_azimuth[aSourceIndex] = anAzimuth;
        m_radius[aSourceIndex] = aRadius;
        if(aRadius >= 1)
        {
            m_widers[aSourceIndex]->setWidenValue(1.);
            m_weight_values[aSourceIndex] = 1. / (aRadius + 1.);
        }
        else
        {
            m_widers[aSourceIndex]->setWidenValue(aRadius);
            m_weight_values[aSourceIndex] = 0.5;
        }
    }
}

void AmbisonicTool::setCartesianCoordinates(long aSourceIndex, double anAbscissa, double anOrdinate)
{
    setPolarCoordinates(aSourceIndex, Tools::radius(anAbscissa, anOrdinate), Tools::angle(anAbscissa, anOrdinate));
}

void AmbisonicTool::setNumberOfSources(long aNumberOfSources)
{
    Tools::clip(aNumberOfSources, (long)1, (long)64);
    if(aNumberOfSources > m_number_of_sources)
    {
        for(int i = m_number_of_sources; i < aNumberOfSources; i++)
        {
            m_encoders.push_back(new AmbisonicEncoder(m_order));
            m_widers.push_back(new AmbisonicWider(m_order));
            setPolarCoordinates(i, 1, 0);
        }
        m_number_of_sources = aNumberOfSources;
    }
    else if(aNumberOfSources < m_number_of_sources)
    {
        for(int i = m_number_of_sources; i < aNumberOfSources; i++)
        {
            m_encoders.pop_back();
            m_widers.pop_back();
        }
        m_number_of_sources = aNumberOfSources;
    }
    m_number_of_inputs = m_number_of_sources;
}

void AmbisonicTool::setNumberOfLoudspeakers(long aNumberOfLoudspeakers)
{
    Tools::clip(aNumberOfLoudspeakers, (long)3, (long)64);
    if(aNumberOfLoudspeakers !=  m_number_of_loudspeakers)
    {
        if(aNumberOfLoudspeakers < 3)
            aNumberOfLoudspeakers = 3;
        m_number_of_loudspeakers = aNumberOfLoudspeakers;
        if(m_number_of_loudspeakers%2 == 0)
            m_order = m_number_of_loudspeakers / 2 - 1;
        else
            m_order = m_number_of_loudspeakers / 2 - 0.5;
        
        for(int i = 0; i < m_number_of_sources; i++)
        {
            m_encoders.push_back(new AmbisonicEncoder(m_order));
            m_widers.push_back(new AmbisonicWider(m_order));
            setPolarCoordinates(i, 1, 0);
        }
        m_decoder = new AmbisonicDecode(m_order, m_number_of_loudspeakers);
    }
    m_number_of_harmonics = 2 * m_order  +1;
    m_number_of_outputs = m_number_of_loudspeakers;
}

void AmbisonicTool::freeSources()
{
    for(int i = 0; i < m_number_of_sources; i++)
	{
		delete m_encoders[i];
		m_encoders[i] = 0;
        delete m_widers[i];
        m_widers[i] = 0;
	}
}

void AmbisonicTool::freeLoudspeakers()
{
    delete m_decoder;
}

AmbisonicTool::~AmbisonicTool()
{
	freeSources();
    freeLoudspeakers();
    for(int i = 0; i < 63; i++)
    {
        free(m_harmonics_block_vector[i]);
        free(m_harmonics_block_copy[i]);
    }
}

