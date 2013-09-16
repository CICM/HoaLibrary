/*
 * PdEnhanced - Pure Data Enhanced 
 *
 * An add-on for Pure Data
 *
 * Copyright (C) 2013 Pierre Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
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

#include "AmbisonicsMeter.h"

AmbisonicsMeter::AmbisonicsMeter(long aNumberOfChannels, long aVectorSize, double aSamplingRate) : Planewaves(aNumberOfChannels, aVectorSize, aSamplingRate)
{
	
    m_vectors = new AmbisonicVector(m_number_of_loudspeakers, aVectorSize);
    for(int i = 0; i < 4; i++)
        m_vector_coordinates_double[i] = m_vector_coordinates_float[i] = 0.;
    
    m_loudspeakers_amplitudes   = NULL;
    m_loudspeakers_peaks        = NULL;
    m_loudspeakers_energies     = NULL;    
    
	setNumberOfLoudspeakers(aNumberOfChannels);
	setVectorSize(aVectorSize);
    m_number_of_outputs		= 0;
}

void AmbisonicsMeter::setVectorSize(long aVectorSize)
{
	Planewaves::setVectorSize(aVectorSize);
    m_vectors->setVectorSize(m_vector_size);
}

void AmbisonicsMeter::setNumberOfLoudspeakers(long aNumberOfChannels)
{
    Planewaves::setNumberOfLoudspeakers(aNumberOfChannels);
    m_vectors->setNumberOfLoudspeakers(aNumberOfChannels);
    m_number_of_outputs		= 0;
    
    if(m_loudspeakers_amplitudes)
        cicm_free(m_loudspeakers_amplitudes);
    if(m_loudspeakers_peaks)
        cicm_free(m_loudspeakers_peaks);
    if(m_loudspeakers_energies)
        cicm_free(m_loudspeakers_energies);
    cicm_malloc_vec_d(m_loudspeakers_amplitudes, m_number_of_loudspeakers);
    cicm_malloc_vec_d(m_loudspeakers_peaks, m_number_of_loudspeakers);
    cicm_malloc_vec_d(m_loudspeakers_energies, m_number_of_loudspeakers);
    
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_loudspeakers_amplitudes[i] = 0.;
        m_loudspeakers_peaks[i] = 0.;
        m_loudspeakers_energies[i] = -90;
    }
}

std::string AmbisonicsMeter::getChannelName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_inputs)
        return "Channel " + Tools::intToString(anIndex+1) + " (" + Tools::floatToString(getLoudspeakerAngle(anIndex), 1) + "°)";
    else
        return "No harmonic";
}

void AmbisonicsMeter::setLoudspeakerAngle(long anIndex, double anAngle)
{
    Planewaves::setLoudspeakerAngle(anIndex, anAngle);
    m_vectors->setLoudspeakerAngle(anIndex, anAngle);
}

double AmbisonicsMeter::getLoudspeakerPeaks(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_inputs)
        return m_loudspeakers_peaks[anIndex];
    else
        return 0.;
}

double AmbisonicsMeter::getLoudspeakerEnergy(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_inputs)
        return m_loudspeakers_energies[anIndex];
    else
        return 0.;
}

double AmbisonicsMeter::getEnergyVectorAbscissa()
{
    return m_vector_coordinates_double[0];
}
double AmbisonicsMeter::getEnergyVectorOrdinate()
{
    return m_vector_coordinates_double[1];
}
double AmbisonicsMeter::getEnergyVectorAngle()
{
    if(m_vector_coordinates_double[0] == 0.) return 0.;
    return Tools::angle(m_vector_coordinates_double[0], m_vector_coordinates_double[1]);
}
double AmbisonicsMeter::getVelocityVectorAbscissa()
{
    return m_vector_coordinates_double[2];
}
double AmbisonicsMeter::getVelocityVectorOrdinate()
{
    return m_vector_coordinates_double[3];
}
double AmbisonicsMeter::getVelocityVectorAngle()
{
    if(m_vector_coordinates_double[2] == 0.) return 0.;
    return Tools::angle(m_vector_coordinates_double[2], m_vector_coordinates_double[3]);
}

AmbisonicsMeter::~AmbisonicsMeter()
{
    delete m_vectors;
	if(m_loudspeakers_amplitudes)
        cicm_free(m_loudspeakers_amplitudes);
    if(m_loudspeakers_peaks)
        cicm_free(m_loudspeakers_peaks);
    if(m_loudspeakers_energies)
        cicm_free(m_loudspeakers_energies);
}

