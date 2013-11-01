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

#include "Planewaves.h"

Planewaves::Planewaves(long aNumberOfLoudspeakers, long aVectorSize, double aSamplingRate)
{
    m_angles_of_loudspeakers_double = NULL;
    m_angles_of_loudspeakers_float  = NULL;
    m_abscissa_of_loudspeakers_double = NULL;
    m_abscissa_of_loudspeakers_float  = NULL;
    m_ordinate_of_loudspeakers_double = NULL;
    m_ordinate_of_loudspeakers_float  = NULL;
    
	setVectorSize(aVectorSize);
    setSamplingRate(aSamplingRate);
    setNumberOfLoudspeakers(aNumberOfLoudspeakers, 0);
}

long Planewaves::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long Planewaves::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long Planewaves::getVectorSize()
{
	return m_vector_size;
}

long Planewaves::getSamplingRate()
{
	return m_sampling_rate;
}

long Planewaves::getNumberOfLoudspeakers()
{
    return m_number_of_loudspeakers;
}

double Planewaves::getLoudspeakerAngle(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_angles_of_loudspeakers_double[anIndex] / CICM_2PI * 360.;
    else
        return 0.;
}

double Planewaves::getLoudspeakerAbscissa(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_abscissa_of_loudspeakers_double[anIndex];
    else
        return 0.;
}

double Planewaves::getLoudspeakerOrdinate(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return m_ordinate_of_loudspeakers_double[anIndex];
    else
        return 0.;
}

std::string Planewaves::getLoudspeakerName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return "Channel " + Tools::intToString(anIndex) + " : " + Tools::floatToStringOneDecimal(m_angles_of_loudspeakers_double[anIndex]/ CICM_2PI * 360.) + "°";
    else
        return "No channel";
}

void Planewaves::computeConfiguration(bool standardOnOff)
{
    if(standardOnOff && m_number_of_loudspeakers <= 7)
    {
        if(m_number_of_loudspeakers == 1)          // Mono //
        {
            m_angles_of_loudspeakers_double[0] = 0.;
        }
        else if(m_number_of_loudspeakers == 2)     // Stereo //
        {
            m_angles_of_loudspeakers_double[0] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[1] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 3)     // Dolby Surround //
        {
            m_angles_of_loudspeakers_double[0] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[1] = 180. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[2] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 4)     // Quadriphonic //
        {
            m_angles_of_loudspeakers_double[0] = 45. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[1] = 135. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[2] = 225. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[3] = 315. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 5)     // Surround 5.1 //
        {
            m_angles_of_loudspeakers_double[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[3] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[4] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 6)     // Surround 6.1 //
        {
            m_angles_of_loudspeakers_double[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[3] = 180. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[4] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[5] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 7)     // Surround 7.1 //
        {
            m_angles_of_loudspeakers_double[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[3] = 135 / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[4] = 225 / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[5] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers_double[6] = 330. / 360. * CICM_2PI;
        }
    }
    else                   // Ambisonics base //
    {
        for (int i = 0; i < (long)m_number_of_loudspeakers; i++)
            m_angles_of_loudspeakers_double[i] = (double)i / (double)(m_number_of_loudspeakers) * CICM_2PI;
    }
    for (int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_angles_of_loudspeakers_float[i] = m_angles_of_loudspeakers_double[i];
        m_abscissa_of_loudspeakers_float[i] = m_abscissa_of_loudspeakers_double[i] = Tools::abscissa(1., m_angles_of_loudspeakers_double[i]);
        m_ordinate_of_loudspeakers_float[i] = m_ordinate_of_loudspeakers_double[i] = Tools::ordinate(1., m_angles_of_loudspeakers_double[i]);
    }
}

void Planewaves::setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff)
{
    m_number_of_loudspeakers    = (long)Tools::clip_min(aNumberOfLoudspeakers, (long)1);
    m_number_of_inputs          = m_number_of_loudspeakers;
	m_number_of_outputs         = m_number_of_loudspeakers;
    
    if(m_angles_of_loudspeakers_double)
        cicm_free(m_angles_of_loudspeakers_double);
    if(m_abscissa_of_loudspeakers_double)
        cicm_free(m_abscissa_of_loudspeakers_double);
    if(m_ordinate_of_loudspeakers_double)
        cicm_free(m_ordinate_of_loudspeakers_double);
    if(m_angles_of_loudspeakers_float)
        cicm_free(m_angles_of_loudspeakers_float);
    if(m_abscissa_of_loudspeakers_float)
        cicm_free(m_abscissa_of_loudspeakers_float);
    if(m_ordinate_of_loudspeakers_float)
        cicm_free(m_ordinate_of_loudspeakers_float);
    
    /* Define standard configuration */
    cicm_malloc_vec_d(m_angles_of_loudspeakers_double, m_number_of_loudspeakers);
    cicm_malloc_vec_d(m_abscissa_of_loudspeakers_double, m_number_of_loudspeakers);
    cicm_malloc_vec_d(m_ordinate_of_loudspeakers_double, m_number_of_loudspeakers);
    cicm_malloc_vec_f(m_angles_of_loudspeakers_float, m_number_of_loudspeakers);
    cicm_malloc_vec_f(m_abscissa_of_loudspeakers_float, m_number_of_loudspeakers);
    cicm_malloc_vec_f(m_ordinate_of_loudspeakers_float, m_number_of_loudspeakers);

    computeConfiguration(standardOnOff);
}

void Planewaves::setLoudspeakerAngleDegrees(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
    {
        anAngle = Tools::radian_wrap(anAngle / 360. * CICM_2PI);
        m_angles_of_loudspeakers_double[anIndex] = anAngle;
    }
    
    Tools::sortVector(m_angles_of_loudspeakers_double, m_number_of_loudspeakers);
    
    for (int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_angles_of_loudspeakers_float[i] = m_angles_of_loudspeakers_double[i];
        m_abscissa_of_loudspeakers_float[i] = m_abscissa_of_loudspeakers_double[i] = Tools::abscissa(1., m_angles_of_loudspeakers_double[i]);
        m_ordinate_of_loudspeakers_float[i] = m_ordinate_of_loudspeakers_double[i] = Tools::ordinate(1., m_angles_of_loudspeakers_double[i]);
    }
}

void Planewaves::setLoudspeakerAngleRadians(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
    {
        m_angles_of_loudspeakers_double[anIndex] = Tools::radian_wrap(anAngle);
    }
    
    Tools::sortVector(m_angles_of_loudspeakers_double, m_number_of_loudspeakers);
    
    for (int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_angles_of_loudspeakers_float[i] = m_angles_of_loudspeakers_double[i];
        m_abscissa_of_loudspeakers_float[i] = m_abscissa_of_loudspeakers_double[i] = Tools::abscissa(1., m_angles_of_loudspeakers_double[i]);
        m_ordinate_of_loudspeakers_float[i] = m_ordinate_of_loudspeakers_double[i] = Tools::ordinate(1., m_angles_of_loudspeakers_double[i]);
    }
}

void Planewaves::setLoudspeakerAnglesDegrees(long aSize, double* angles)
{
    for(int i = 0; i < aSize && i < m_number_of_loudspeakers; i++)
        m_angles_of_loudspeakers_double[i] = Tools::radian_wrap(angles[i]  / 360. * CICM_2PI);
    
    Tools::sortVector(m_angles_of_loudspeakers_double, m_number_of_loudspeakers);
    
    for (int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_angles_of_loudspeakers_float[i] = m_angles_of_loudspeakers_double[i];
        m_abscissa_of_loudspeakers_float[i] = m_abscissa_of_loudspeakers_double[i] = Tools::abscissa(1., m_angles_of_loudspeakers_double[i]);
        m_ordinate_of_loudspeakers_float[i] = m_ordinate_of_loudspeakers_double[i] = Tools::ordinate(1., m_angles_of_loudspeakers_double[i]);
    }
        
}

void Planewaves::setLoudspeakerAnglesRadians(long aSize, double* angles)
{
    for(int i = 0; i < aSize || i < m_number_of_loudspeakers; i++)
        m_angles_of_loudspeakers_double[i] = Tools::radian_wrap(angles[i]);
    
    Tools::sortVector(m_angles_of_loudspeakers_double, m_number_of_loudspeakers);
    
    for (int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_angles_of_loudspeakers_float[i] = m_angles_of_loudspeakers_double[i];
        m_abscissa_of_loudspeakers_float[i] = m_abscissa_of_loudspeakers_double[i] = Tools::abscissa(1., m_angles_of_loudspeakers_double[i]);
        m_ordinate_of_loudspeakers_float[i] = m_ordinate_of_loudspeakers_double[i] = Tools::ordinate(1., m_angles_of_loudspeakers_double[i]);
    }
    
}


void Planewaves::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void Planewaves::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, 1);
}

Planewaves::~Planewaves()
{
	if(m_angles_of_loudspeakers_double)
        cicm_free(m_angles_of_loudspeakers_double);
    if(m_abscissa_of_loudspeakers_double)
        cicm_free(m_abscissa_of_loudspeakers_double);
    if(m_ordinate_of_loudspeakers_double)
        cicm_free(m_ordinate_of_loudspeakers_double);
    if(m_angles_of_loudspeakers_float)
        cicm_free(m_angles_of_loudspeakers_float);
    if(m_abscissa_of_loudspeakers_float)
        cicm_free(m_abscissa_of_loudspeakers_float);
    if(m_ordinate_of_loudspeakers_float)
        cicm_free(m_ordinate_of_loudspeakers_float);
}

