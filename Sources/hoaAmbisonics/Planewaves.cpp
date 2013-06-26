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

#include "Planewaves.h"

Planewaves::Planewaves(long aNumberOfLoudspeakers, long aVectorSize, double aSamplingRate)
{
    m_angles_of_loudspeakers = NULL;
    m_abscissa_of_loudspeakers = NULL;
    m_ordinate_of_loudspeakers = NULL;
    
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
        return m_angles_of_loudspeakers[anIndex] / CICM_2PI * 360.;
    else
        return 0.;
}

std::string Planewaves::getLoudspeakerName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
        return "Channel " + Tools::intToString(anIndex) + " : " + Tools::floatToStringOneDecimal(m_angles_of_loudspeakers[anIndex]/ CICM_2PI * 360.) + "°";
    else
        return "No channel";
}

void Planewaves::computeConfiguration(bool standardOnOff)
{
    if(standardOnOff && m_number_of_loudspeakers <= 7)
    {
        if(m_number_of_loudspeakers == 1)          // Mono //
        {
            m_angles_of_loudspeakers[0] = 0.;
        }
        else if(m_number_of_loudspeakers == 2)     // Stereo //
        {
            m_angles_of_loudspeakers[0] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 3)     // Dolby Surround //
        {
            m_angles_of_loudspeakers[0] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 180. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 4)     // Quadriphonic //
        {
            m_angles_of_loudspeakers[0] = 45. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 135. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 225. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 315. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 5)     // Surround 5.1 //
        {
            m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[4] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 6)     // Surround 6.1 //
        {
            m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 180. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[4] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[5] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_loudspeakers == 7)     // Surround 7.1 //
        {
            m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 135 / 360. * CICM_2PI;
            m_angles_of_loudspeakers[4] = 225 / 360. * CICM_2PI;
            m_angles_of_loudspeakers[5] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[6] = 330. / 360. * CICM_2PI;
        }
    }
    else                   // Ambisonics base //
    {
        for (int i = 0; i < (long)m_number_of_loudspeakers; i++)
            m_angles_of_loudspeakers[i] = (double)i / (double)(m_number_of_loudspeakers) * CICM_2PI;
    }
}

void Planewaves::setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff)
{
    m_number_of_loudspeakers    = (long)Tools::clip_min(aNumberOfLoudspeakers, (long)1);
    m_number_of_inputs          = m_number_of_loudspeakers;
	m_number_of_outputs         = m_number_of_loudspeakers;
    
    if(m_angles_of_loudspeakers)
        free(m_angles_of_loudspeakers);
    if(m_abscissa_of_loudspeakers)
        free(m_abscissa_of_loudspeakers);
    if(m_ordinate_of_loudspeakers)
        free(m_ordinate_of_loudspeakers);
    
    /* Define standard configuration */
    m_angles_of_loudspeakers    = new double[m_number_of_loudspeakers];
    m_abscissa_of_loudspeakers  = new double[m_number_of_loudspeakers];
    m_ordinate_of_loudspeakers  = new double[m_number_of_loudspeakers];
    computeConfiguration(standardOnOff);
    
    for (int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_abscissa_of_loudspeakers[i] = Tools::abscisse(1., m_angles_of_loudspeakers[i]);
        m_ordinate_of_loudspeakers[i] = Tools::ordinate(1., m_angles_of_loudspeakers[i]);
    }
}

void Planewaves::setLoudspeakerAngle(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < m_number_of_loudspeakers)
    {
        anAngle = Tools::radianWrap(anAngle / 360. * CICM_2PI);
        m_angles_of_loudspeakers[anIndex] = anAngle;
    }
    Tools::sortVector(m_angles_of_loudspeakers, m_number_of_loudspeakers);
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
    free(m_abscissa_of_loudspeakers);
    free(m_ordinate_of_loudspeakers);
}

