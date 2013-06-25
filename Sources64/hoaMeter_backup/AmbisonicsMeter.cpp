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

