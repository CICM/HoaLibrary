/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    m_loudspeakers_angles_mapped    = NULL;
    m_loudspeakers_angles_width     = NULL;
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
    if(m_loudspeakers_angles_mapped)
        cicm_free(m_loudspeakers_angles_mapped);
    if(m_loudspeakers_angles_width)
        cicm_free(m_loudspeakers_angles_width);
    
    cicm_malloc_vec_d(m_loudspeakers_amplitudes, m_number_of_loudspeakers);
    cicm_malloc_vec_d(m_loudspeakers_peaks, m_number_of_loudspeakers);
    cicm_malloc_vec_d(m_loudspeakers_energies, m_number_of_loudspeakers);
    cicm_malloc_vec_d(m_loudspeakers_angles_mapped, m_number_of_loudspeakers);
    cicm_malloc_vec_d(m_loudspeakers_angles_width, m_number_of_loudspeakers);
    
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_loudspeakers_amplitudes[i] = 0.;
        m_loudspeakers_peaks[i] = 0.;
        m_loudspeakers_energies[i] = -90;
    }
    
    double curAngle, prevAngle, nextAngle, prevPortion, nextPortion;
	for(int i = 0; i < m_number_of_loudspeakers; i++)
	{
		curAngle = m_angles_of_loudspeakers_double[i];
		if (i != 0)
            prevAngle = m_angles_of_loudspeakers_double[i-1];
		else
            prevAngle = m_angles_of_loudspeakers_double[m_number_of_loudspeakers-1];
		if (i != m_number_of_loudspeakers-1)
            nextAngle = m_angles_of_loudspeakers_double[i+1];
		else
            nextAngle = m_angles_of_loudspeakers_double[0];
		
		prevPortion = (curAngle - prevAngle);
		nextPortion = (nextAngle - curAngle);
		
		if (nextPortion < 0.)
            nextPortion += CICM_2PI;
		if (prevPortion < 0.)
            prevPortion += CICM_2PI;
		
		m_loudspeakers_angles_width[i] = (prevPortion + nextPortion)*0.5;
		m_loudspeakers_angles_mapped[i] = (curAngle - prevPortion*0.5) + m_loudspeakers_angles_width[i]*0.5;
	}
}

std::string AmbisonicsMeter::getChannelName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return "Channel " + Tools::intToString(anIndex+1) + " (" + Tools::floatToString(getLoudspeakerAngle(anIndex), 1) + "°)";
    else
        return "No harmonic";
}

double AmbisonicsMeter::getLoudspeakerAngleMapped(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_loudspeakers_angles_mapped[anIndex] / CICM_2PI * 360.;
    else
        return 0.;
}

double AmbisonicsMeter::getLoudspeakerWidth(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_loudspeakers_angles_width[anIndex] / CICM_2PI * 360.;
    else
        return 0.;
}

double AmbisonicsMeter::getLoudspeakerAngleRadian(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_angles_of_loudspeakers_double[anIndex];
    else
        return 0.;
}

double AmbisonicsMeter::getLoudspeakerAngleMappedRadian(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_loudspeakers_angles_mapped[anIndex];
    else
        return 0.;
}

double AmbisonicsMeter::getLoudspeakerWidthRadian(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_loudspeakers_angles_width[anIndex];
    else
        return 0.;
}

void AmbisonicsMeter::setLoudspeakerAngleDegrees(long anIndex, double anAngle)
{
    Planewaves::setLoudspeakerAngleDegrees(anIndex, anAngle);
    m_vectors->setLoudspeakerAngleDegrees(anIndex, anAngle);
    
    double curAngle, prevAngle, nextAngle, prevPortion, nextPortion;
	for(int i = 0; i < m_number_of_loudspeakers; i++)
	{
		curAngle = m_angles_of_loudspeakers_double[i];
		if (i != 0)
            prevAngle = m_angles_of_loudspeakers_double[i-1];
		else
            prevAngle = m_angles_of_loudspeakers_double[m_number_of_loudspeakers-1];
		if (i != m_number_of_loudspeakers-1)
            nextAngle = m_angles_of_loudspeakers_double[i+1];
		else
            nextAngle = m_angles_of_loudspeakers_double[0];
		
		prevPortion = (curAngle - prevAngle);
		nextPortion = (nextAngle - curAngle);
		
		if (nextPortion < 0.)
            nextPortion += CICM_2PI;
		if (prevPortion < 0.)
            prevPortion += CICM_2PI;
		
		m_loudspeakers_angles_width[i] = (prevPortion + nextPortion)*0.5;
		m_loudspeakers_angles_mapped[i] = (curAngle - prevPortion*0.5) + m_loudspeakers_angles_width[i]*0.5;
	}
}

void AmbisonicsMeter::setLoudspeakerAnglesDegrees(long aSize, double* angles)
{
    Planewaves::setLoudspeakerAnglesDegrees(aSize, angles);
    m_vectors->setLoudspeakerAnglesDegrees(aSize, angles);
    
    double curAngle, prevAngle, nextAngle, prevPortion, nextPortion;
	for(int i = 0; i < m_number_of_loudspeakers; i++)
	{
		curAngle = m_angles_of_loudspeakers_double[i];
		if (i != 0)
            prevAngle = m_angles_of_loudspeakers_double[i-1];
		else
            prevAngle = m_angles_of_loudspeakers_double[m_number_of_loudspeakers-1];
		if (i != m_number_of_loudspeakers-1)
            nextAngle = m_angles_of_loudspeakers_double[i+1];
		else
            nextAngle = m_angles_of_loudspeakers_double[0];
		
		prevPortion = (curAngle - prevAngle);
		nextPortion = (nextAngle - curAngle);
		
		if (nextPortion < 0.)
            nextPortion += CICM_2PI;
		if (prevPortion < 0.)
            prevPortion += CICM_2PI;
		
		m_loudspeakers_angles_width[i] = (prevPortion + nextPortion)*0.5;
		m_loudspeakers_angles_mapped[i] = (curAngle - prevPortion*0.5) + m_loudspeakers_angles_width[i]*0.5;
	}
}

double AmbisonicsMeter::getLoudspeakerPeaks(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_loudspeakers_peaks[anIndex];
    else
        return 0.;
}

double AmbisonicsMeter::getLoudspeakerEnergy(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
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
    if(m_vector_coordinates_double[0] == 0.)
        return 0.;
    return
        Tools::angle(m_vector_coordinates_double[0], m_vector_coordinates_double[1]);
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
    if(m_vector_coordinates_double[2] == 0.)
        return 0.;
    return
    Tools::angle(m_vector_coordinates_double[2], m_vector_coordinates_double[3]);
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
    if(m_loudspeakers_angles_mapped)
        cicm_free(m_loudspeakers_angles_mapped);
    if(m_loudspeakers_angles_width)
        cicm_free(m_loudspeakers_angles_width);
}

