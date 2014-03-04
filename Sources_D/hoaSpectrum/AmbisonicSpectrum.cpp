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

#include "AmbisonicSpectrum.h"

AmbisonicSpectrum::AmbisonicSpectrum(long aNumberOfLoudspeakers, long aNumberOfBands, long aVectorSize, long aSamplingRate)
: Planewaves(aNumberOfLoudspeakers, aVectorSize, aSamplingRate)
{
    m_filtered_signal_double = NULL;
    m_filtered_signal_float = NULL;
    m_amplitude = NULL;
    m_frequency = NULL;
    m_abscissa = NULL;
    m_ordinate = NULL;
    m_temp_amplitude_value = NULL;
    m_loudspeakers_values = NULL;
    m_vector = new AmbisonicVector(m_number_of_loudspeakers, m_vector_size);
    setNumberOfBands(aNumberOfBands);
}

void AmbisonicSpectrum::setNumberOfBands(long aNumberOfBands)
{
    aNumberOfBands = Tools::clip_min(aNumberOfBands, (long)1);
    if (m_filter.size() != aNumberOfBands)
    {
        m_filter.clear();
        if(m_filtered_signal_double)
            cicm_free(m_filtered_signal_double);
        if(m_filtered_signal_float)
            cicm_free(m_filtered_signal_float);
        if(m_amplitude)
            cicm_free(m_amplitude);
        if(m_frequency)
            cicm_free(m_frequency);
        if(m_abscissa)
            cicm_free(m_abscissa);
        if(m_ordinate)
            cicm_free(m_ordinate);
        if(m_temp_amplitude_value)
            cicm_free(m_temp_amplitude_value);
        
         for(int i = 0; i < aNumberOfBands; i++)
            m_filter.push_back(vector <FilterBiquad*>());
        
        m_filtered_signal_double = new cicm_vector_double*[m_filter.size()];
        m_filtered_signal_float = new cicm_vector_float*[m_filter.size()];
        
        for(int i = 0; i < m_filter.size(); i++)
        {
            m_filtered_signal_double[i] = NULL;
            m_filtered_signal_float[i]  = NULL;
        }
        cicm_malloc_vec_d(m_amplitude, m_filter.size());
        cicm_malloc_vec_d(m_frequency, m_filter.size());
        cicm_malloc_vec_d(m_abscissa, m_filter.size());
        cicm_malloc_vec_d(m_ordinate, m_filter.size());
        cicm_malloc_vec_d(m_temp_amplitude_value, m_filter.size());
    }
    initializeFrequencyBands();
    setNumberOfLoudspeakers(m_number_of_loudspeakers);
}


void AmbisonicSpectrum::setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff)
{
    Planewaves::setNumberOfLoudspeakers(aNumberOfLoudspeakers, standardOnOff);
    if(m_loudspeakers_values);
        cicm_free(m_loudspeakers_values);
    cicm_malloc_vec_d(m_loudspeakers_values, m_number_of_loudspeakers);
    for(int i = 0; i < m_filter.size(); i++)
    {
        m_filter[i].clear();
        if(m_filtered_signal_double[i])
            cicm_free(m_filtered_signal_double[i]);
        if(m_filtered_signal_float[i])
            cicm_free(m_filtered_signal_float[i]);
        
        m_filtered_signal_double[i] = new cicm_vector_double[m_number_of_loudspeakers];
        m_filtered_signal_float[i]  = new cicm_vector_float[m_number_of_loudspeakers];
        for(int j = 0; j < m_number_of_loudspeakers; j++)
        {
            m_filter[i].push_back(new FilterBiquad(Cicm_Biquad_Bandpass, m_vector_size, m_sampling_rate));
            m_filter[i][j]->setGain(1.);
            m_filter[i][j]->setQValue(1.);
            m_filtered_signal_double[i][j]  = NULL;
            m_filtered_signal_float[i][j]   = NULL;
        }
    }
    /* Iniatialize Filters Type and Q Value*/
    for(int j = 0; j < m_number_of_loudspeakers; j++)
    {
        m_filter[0][j]->setType(Cicm_Biquad_Lowpass);
        m_filter[0][j]->setQValue(1.);
        m_filter[m_filter.size()-1][j]->setType(Cicm_Biquad_Highpass);
        m_filter[m_filter.size()-1][j]->setQValue(1.);
    }
    if(m_filter.size() == 1)
    {
        for(int j = 0; j < m_number_of_loudspeakers; j++)
        {
            m_filter[0][j]->setType(Cicm_Biquad_Highshelf);
            m_filter[0][j]->setQValue(1.);
        }
    }
    m_vector->setNumberOfLoudspeakers(aNumberOfLoudspeakers);
    setVectorSize(m_vector_size);
    setSamplingRate(m_sampling_rate);
}

void AmbisonicSpectrum::initializeFrequencyBands()
{
    if(m_filter.size() == 1)
    {
        m_frequency[0] = 2400.;
    }
    else if(m_filter.size() == 2)
    {
        m_frequency[0] = 2400.;
        m_frequency[1] = 2400.;
    }
    else if(m_filter.size() == 3)
    {
        m_frequency[0] = 200.;
        m_frequency[1] = 2400.;
        m_frequency[2] = 4000.;
    }
    else if(m_filter.size() == 4)
    {
        m_frequency[0] = 200.;
        m_frequency[1] = 600.;
        m_frequency[2] = 2400.;
        m_frequency[3] = 4000.;
    }
    else
    {
        m_frequency[0] = 200.;
        m_frequency[1] = 300.;
        m_frequency[2] = 600.;
        m_frequency[3] = 2400.;
        m_frequency[4] = 4000.;
    }
}


void AmbisonicSpectrum::setLoudspeakerAngle(long anIndex, double anAngle)
{
    Planewaves::setLoudspeakerAngleDegrees(anIndex, anAngle);
    m_vector->setLoudspeakerAngleDegrees(anIndex, anAngle);
}

void AmbisonicSpectrum::setFrequencyBand(long anIndex, double aFrequency)
{
    if (anIndex >= 0 && anIndex < m_filter.size())
    {
        m_frequency[anIndex] = Tools::clip(aFrequency, 20., (double)m_sampling_rate / 2.);
        Tools::sortVector(m_frequency, m_filter.size());
    }
    for(int i = 0; i < m_filter.size(); i++)
    {
        for(int j = 0; j < m_number_of_loudspeakers; j++)
        {
            m_filter[i][j]->setCutoffFrequency(m_frequency[i]);
        }
    }
}

double AmbisonicSpectrum::getFrequencyBand(long anIndex)
{
    if (anIndex >= 0 && anIndex < m_filter.size())
        return m_filter[anIndex][0]->getCutoffFrequency();//m_frequency[anIndex];
    else
        return NULL;
}

void AmbisonicSpectrum::setVectorSize(long aVectorSize)
{
     
    Planewaves::setVectorSize(aVectorSize);
    m_vector->setVectorSize(m_vector_size);
    
    for(int i = 0; i < m_filter.size(); i++)
    {
        for(int j = 0; j < m_number_of_loudspeakers; j++)
        {
            m_filter[i][j]->setVectorSize(m_vector_size);
            if(m_filtered_signal_double[i][j])
                cicm_free(m_filtered_signal_double[i][j]);
            if(m_filtered_signal_float[i][j])
                cicm_free(m_filtered_signal_float[i][j]);
            
            cicm_malloc_vec_d(m_filtered_signal_double[i][j], m_vector_size);
            cicm_malloc_vec_f(m_filtered_signal_float[i][j], m_vector_size);
        }
    }
}

void AmbisonicSpectrum::setSamplingRate(long aSamplingRate)
{
	Planewaves::setSamplingRate(aSamplingRate);
    for(int i = 0; i < m_filter.size(); i++)
    {
        for(int j = 0; j < m_number_of_loudspeakers; j++)
        {
            m_filter[i][j]->setSamplingRate(m_sampling_rate);
        }
    }
    for(int i = 0; i < m_filter.size(); i++)
    {
        for(int j = 0; j < m_number_of_loudspeakers; j++)
        {
            m_filter[i][j]->setCutoffFrequency(m_frequency[i]);
        }
    }
}

long AmbisonicSpectrum::getNumberOfBands()
{
    return m_filter.size();
}

double AmbisonicSpectrum::getAmplitude(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    return m_amplitude[aBandIndex];
}

double AmbisonicSpectrum::getAbscissa(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    double radius = Tools::radius(m_abscissa[aBandIndex], m_ordinate[aBandIndex]);
    double angle = Tools::angle(m_abscissa[aBandIndex], m_ordinate[aBandIndex]) + CICM_PI2;
    return Tools::abscissa(radius, angle);
}

double AmbisonicSpectrum::getOrdinate(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    double radius = Tools::radius(m_abscissa[aBandIndex], m_ordinate[aBandIndex]);
    double angle = Tools::angle(m_abscissa[aBandIndex], m_ordinate[aBandIndex]) + CICM_PI2;
    return Tools::ordinate(radius, angle);
}

double AmbisonicSpectrum::getRadius(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    return Tools::radius(m_abscissa[aBandIndex], m_ordinate[aBandIndex]);
}

double AmbisonicSpectrum::getAngle(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    return Tools::angle(m_abscissa[aBandIndex], m_ordinate[aBandIndex]) + CICM_PI2;
}

double AmbisonicSpectrum::getLogAmplitude(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    double amplitude = m_amplitude[aBandIndex] / (m_frequency[aBandIndex] / m_frequency[0]);
    return amplitude;
}

double AmbisonicSpectrum::getLogAbscissa(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    double radius = Tools::radius(m_abscissa[aBandIndex], m_ordinate[aBandIndex]);
    radius *= radius * radius;
    double angle = Tools::angle(m_abscissa[aBandIndex], m_ordinate[aBandIndex]) + CICM_PI2;
    return Tools::abscissa(radius, angle);
}

double AmbisonicSpectrum::getLogOrdinate(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    double radius = Tools::radius(m_abscissa[aBandIndex], m_ordinate[aBandIndex]);
    radius *= radius * radius;
    double angle = Tools::angle(m_abscissa[aBandIndex], m_ordinate[aBandIndex]) + CICM_PI2;
    return Tools::ordinate(radius, angle);
}

double AmbisonicSpectrum::getLogRadius(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    double radius = Tools::radius(m_abscissa[aBandIndex], m_ordinate[aBandIndex]);
    return radius * radius * radius;
}

double AmbisonicSpectrum::getLogAngle(long aBandIndex)
{
    aBandIndex = Tools::clip(aBandIndex, (long)0, (long)m_filter.size());
    return Tools::angle(m_abscissa[aBandIndex], m_ordinate[aBandIndex]) + CICM_PI2;
}


AmbisonicSpectrum::~AmbisonicSpectrum()
{
    delete m_vector;
    m_filter.clear();
    
    if(m_filtered_signal_double)
        cicm_free(m_filtered_signal_double);
    if(m_filtered_signal_float)
        cicm_free(m_filtered_signal_float);
    if(m_amplitude)
        cicm_free(m_amplitude);
    if(m_frequency)
        cicm_free(m_frequency);
    if(m_abscissa)
        cicm_free(m_abscissa);
    if(m_ordinate)
        cicm_free(m_ordinate);
    if(m_loudspeakers_values)
        cicm_free(m_loudspeakers_values);
    if(m_temp_amplitude_value)
        cicm_free(m_temp_amplitude_value);    
}

