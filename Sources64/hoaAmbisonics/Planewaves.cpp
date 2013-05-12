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

#include "Planewaves.h"

Planewaves::Planewaves(double aConfiguration, long aVectorSize, double aSamplingRate)
{
    m_angles_of_loudspeakers = NULL;
	setVectorSize(aVectorSize);
    setSamplingRate(aSamplingRate);
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

double Planewaves::getConfiguration()
{
    return m_configuration;
}

double Planewaves::getLoudspeakerAngle(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_configuration)
        return m_angles_of_loudspeakers[anIndex] / CICM_2PI * 360.;
    else
        return 0.;
}

std::string Planewaves::getLoudspeakerName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_configuration)
        return "Channel " + Tools::intToString(anIndex) + " : " + Tools::floatToStringOneDecimal(m_angles_of_loudspeakers[anIndex]/ CICM_2PI * 360.) + "°";
    else if(anIndex == (long)m_configuration && m_low_frequency_effect)
        return "Lfe channel";
    else
        return "No channel";
}

void Planewaves::computeConfiguration(bool standardOnOff)
{
    if(standardOnOff)
    {
        if((long)m_configuration == 1)          // Mono //
        {
            m_angles_of_loudspeakers[0] = 0.;
        }
        else if((long)m_configuration == 2)     // Stereo //
        {
            m_angles_of_loudspeakers[0] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 330. / 360. * CICM_2PI;
        }
        else if((long)m_configuration == 3)     // Dolby Surround //
        {
            m_angles_of_loudspeakers[0] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 180. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 330. / 360. * CICM_2PI;
        }
        else if((long)m_configuration == 4)     // Quadriphonic //
        {
            m_angles_of_loudspeakers[0] = 45. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 135. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 225. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 315. / 360. * CICM_2PI;
        }
        else if((long)m_configuration == 5)     // Surround 5.1 //
        {
            m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[4] = 330. / 360. * CICM_2PI;
        }
        else if((long)m_configuration == 6)     // Surround 6.1 //
        {
            m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 180. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[4] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[5] = 330. / 360. * CICM_2PI;
        }
        else if((long)m_configuration == 7)     // Surround 7.1 //
        {
            m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 135 / 360. * CICM_2PI;
            m_angles_of_loudspeakers[4] = 225 / 360. * CICM_2PI;
            m_angles_of_loudspeakers[5] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[6] = 330. / 360. * CICM_2PI;
        }
        else                                            // Ambisonics base //
        {
            for (int i = 0; i < (long)m_configuration; i++)
                m_angles_of_loudspeakers[i] = (double)i / (double)((long)m_configuration) * CICM_2PI;
        }
    }
    else                                                // Ambisonics base //
    {
        for (int i = 0; i < (long)m_configuration; i++)
            m_angles_of_loudspeakers[i] = (double)i / (double)((long)m_configuration) * CICM_2PI;
    }
}

void Planewaves::setConfiguration(double aConfiguration, bool standardOnOff)
{
    m_configuration  = (long)Tools::clip_min(aConfiguration, 0.);
    m_number_of_inputs		= m_configuration;
	m_number_of_outputs		= m_configuration;
    if(aConfiguration - (long)aConfiguration != 0.)
    {
        m_low_frequency_effect = 1;
        m_configuration += 0.1;
        m_number_of_inputs++;
        m_number_of_outputs++;
    }
    else
        m_low_frequency_effect = 0;
    
    if(m_angles_of_loudspeakers)
        free(m_angles_of_loudspeakers);
    
    /* Define standard configuration */
    m_angles_of_loudspeakers = new double[(long)m_configuration];
    computeConfiguration(standardOnOff);
}

void Planewaves::setLoudspeakerAngle(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < (long)m_configuration)
    {
        anAngle = Tools::radianWrap(anAngle / 360. * CICM_2PI);
        m_angles_of_loudspeakers[anIndex] = anAngle;
    }
    Tools::sortVector(m_angles_of_loudspeakers, (long)m_configuration);
}

void Planewaves::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

void Planewaves::setSamplingRate(long aSamplingRate)
{
	m_sampling_rate = Tools::clip_min(aSamplingRate, long(0));
}

Planewaves::~Planewaves()
{
	free(m_angles_of_loudspeakers);
}

