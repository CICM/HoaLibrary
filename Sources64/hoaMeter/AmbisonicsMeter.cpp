/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

AmbisonicsMeter::AmbisonicsMeter(long aNumberOfChannels, long aVectorSize, double aSamplingRate) : Planewaves()
{

	m_number_of_inputs		= Tools::clip_min(aNumberOfChannels, (long)1);
	m_number_of_outputs		= 0;
    
    Cicm_Vector_Double_Malloc(m_loudspeakers_amplitudes, m_number_of_inputs);
    Cicm_Vector_Double_Malloc(m_loudspeakers_peaks, m_number_of_inputs);
    Cicm_Vector_Double_Malloc(m_loudspeakers_energies, m_number_of_inputs);
    
    m_vectors = new Ambisonicsvector(m_number_of_inputs, Hoa_Cartesian);
    
    for(int i = 0; i < m_number_of_inputs; i++)
    {
        m_loudspeakers_peaks[i] = 0.;
        m_loudspeakers_energies[i] = -999;
    }
    
    for(int i = 0; i < 4; i++)
        m_vector_coordinates_double[i] = m_vector_coordinates_float[i] = 0.;
	
	setVectorSize(aVectorSize);
    setSamplingRate(aSamplingRate);
}

void AmbisonicsMeter::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
    m_vectors->setVectorSize(m_vector_size);
}

void AmbisonicsMeter::setNumberOfChannels(long aNumberofChannels)
{
    setConfiguration(aNumberofChannels);
    //m_number_of_inputs = Tools::clip_min(aNumberofChannels, (long)1);
    m_vectors->setConfiguration(m_number_of_inputs);
    
    Cicm_Free(m_loudspeakers_amplitudes);
    Cicm_Free(m_loudspeakers_peaks);
    Cicm_Free(m_loudspeakers_energies);
    Cicm_Vector_Double_Malloc(m_loudspeakers_amplitudes, m_number_of_inputs);
    Cicm_Vector_Double_Malloc(m_loudspeakers_peaks, m_number_of_inputs);
    Cicm_Vector_Double_Malloc(m_loudspeakers_energies, m_number_of_inputs);
    
    for(int i = 0; i < m_number_of_inputs; i++)
    {
        m_loudspeakers_peaks[i] = 0.;
        m_loudspeakers_energies[i] = -999;
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
    if(anIndex >= 0 && anIndex < (long)m_configuration)
    {
        m_vectors->setLoudspeakerAngle(anIndex, anAngle);
        anAngle = Tools::radianWrap(anAngle / 360. * CICM_2PI);
        m_angles_of_loudspeakers[anIndex] = anAngle;
    }
    Tools::sortVector(m_angles_of_loudspeakers, (long)m_configuration);
}

void AmbisonicsMeter::setLoudspeakerAngles(long len, double* angles)
{
    for (int i=0; i<len && i<m_number_of_inputs; i++) {
        m_angles_of_loudspeakers[i] = Tools::radianWrap(angles[i] / 360. * CICM_2PI);
    }
    m_vectors->setLoudspeakerAngles(len, angles);
    Tools::sortVector(m_angles_of_loudspeakers, (long)m_configuration);
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
	;
}

