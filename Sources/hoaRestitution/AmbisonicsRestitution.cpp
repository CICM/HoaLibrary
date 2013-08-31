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

#include "AmbisonicsRestitution.h"

AmbisonicsRestitution::AmbisonicsRestitution(long anOrder, long aNumberOfLoudspeakers, long aResitutionMode, long aVectorSize) : Ambisonic(anOrder, aVectorSize)
{
    m_number_of_virtual_loudspeakers = m_number_of_harmonics+1;
    m_decoder = new AmbisonicsDecoder(m_order, m_number_of_virtual_loudspeakers, m_vector_size);
    
    cicm_malloc_vec_f(m_vector_float_input, m_number_of_virtual_loudspeakers);
    cicm_malloc_vec_d(m_vector_double_input, m_number_of_virtual_loudspeakers);
    cicm_malloc_vec_f(m_loudspeakers_vector_float, m_number_of_virtual_loudspeakers);
    cicm_malloc_vec_d(m_loudspeakers_vector_double, m_number_of_virtual_loudspeakers);
    
    m_loudspeakers_gains_vector_float   = NULL;
    m_loudspeakers_gains_vector_double  = NULL;
    m_angles_of_loudspeakers = NULL;
    
    m_restitution_mode = Tools::clip(aResitutionMode, (long)Hoa_Amplitude_Panning, (long)Hoa_Microphone_Simulation);
    setNumberOfLoudspeakers(aNumberOfLoudspeakers);
}

void AmbisonicsRestitution::setRestitutionMode(long aResitutionMode)
{
    m_restitution_mode = Tools::clip(aResitutionMode, (long)Hoa_Amplitude_Panning, (long)Hoa_Microphone_Simulation);
    if(m_restitution_mode == Hoa_Amplitude_Panning)
        computeAmplitudePanning();
    else
        computeMicrophoneSimulation();
}

long AmbisonicsRestitution::getRestitutionMode()
{
    return m_restitution_mode;
}

void AmbisonicsRestitution::setNumberOfLoudspeakers(long aNumberOfLoudspeakers, bool standardOnOff)
{
    /* Initialize the configuration */
    m_number_of_real_loudspeakers    = Tools::clip_min((long)aNumberOfLoudspeakers, (long)1);
    
    /* Free memories */
    if(m_loudspeakers_gains_vector_float && m_loudspeakers_gains_vector_double)
    {
        free(m_loudspeakers_gains_vector_double);
        free(m_loudspeakers_gains_vector_float);
    }
    if(m_angles_of_loudspeakers)
        free(m_angles_of_loudspeakers);
    
    /* Alloc memories */
    m_loudspeakers_gains_vector_float   = new cicm_vector_float[m_number_of_real_loudspeakers];
    m_loudspeakers_gains_vector_double  = new cicm_vector_double[m_number_of_real_loudspeakers];
	cicm_malloc_vec_d(m_angles_of_loudspeakers, m_number_of_real_loudspeakers);
   
    for(int i = 0; i < m_number_of_real_loudspeakers; i++)
    {
        cicm_malloc_vec_f(m_loudspeakers_gains_vector_float[i], m_number_of_virtual_loudspeakers);
        cicm_malloc_vec_d(m_loudspeakers_gains_vector_double[i], m_number_of_virtual_loudspeakers);
    }
    
    /* Define standard configuration */
    m_angles_of_loudspeakers = new double[m_number_of_real_loudspeakers];
    if(standardOnOff)
    {
        if(m_number_of_real_loudspeakers == 1)          // Mono //
        {
            m_angles_of_loudspeakers[0] = 0.;
        }
        else if(m_number_of_real_loudspeakers == 2)     // Stereo //
        {
            m_angles_of_loudspeakers[0] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_real_loudspeakers == 3)     // Dolby Surround //
        {
            m_angles_of_loudspeakers[0] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 180. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_real_loudspeakers == 4)     // Quadriphonic //
        {
            m_angles_of_loudspeakers[0] = 45. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 135. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 225. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 315. / 360. * CICM_2PI;
        }
        else if(m_number_of_real_loudspeakers == 5)     // Surround 5.1 //
        {
            m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[4] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_real_loudspeakers == 6)     // Surround 6.1 //
        {
            m_angles_of_loudspeakers[0] = 0. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[1] = 30. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[2] = 110. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[3] = 180. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[4] = 250. / 360. * CICM_2PI;
            m_angles_of_loudspeakers[5] = 330. / 360. * CICM_2PI;
        }
        else if(m_number_of_real_loudspeakers == 7)     // Surround 7.1 //
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
            for (int i = 0; i < m_number_of_real_loudspeakers; i++)
                m_angles_of_loudspeakers[i] = (double)i / (double)m_number_of_real_loudspeakers * CICM_2PI;
        }
    }
    else                                                // Ambisonics base //
    {
        for (int i = 0; i < m_number_of_real_loudspeakers; i++)
            m_angles_of_loudspeakers[i] = (double)i / (double)m_number_of_real_loudspeakers * CICM_2PI;
    }
    
    if(m_restitution_mode == Hoa_Amplitude_Panning)
        computeAmplitudePanning();
    else
        computeMicrophoneSimulation();
    m_number_of_outputs = m_number_of_real_loudspeakers;
}

double AmbisonicsRestitution::getConfiguration()
{
    return m_number_of_real_loudspeakers;
}

void AmbisonicsRestitution::setLoudspeakerAngle(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < m_number_of_real_loudspeakers)
    {
        anAngle = Tools::radian_wrap(anAngle / 360. * CICM_2PI);
        m_angles_of_loudspeakers[anIndex] = anAngle;
    }
    Tools::sortVector(m_angles_of_loudspeakers, m_number_of_real_loudspeakers);
    if(m_restitution_mode == Hoa_Amplitude_Panning)
        computeAmplitudePanning();
    else
        computeMicrophoneSimulation();
}

double AmbisonicsRestitution::getLoudspeakerAngle(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_real_loudspeakers)
        return m_angles_of_loudspeakers[anIndex] / CICM_2PI * 360.;
    else
        return 0.;
}

std::string AmbisonicsRestitution::getLoudspeakerName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_real_loudspeakers)
        return "Channel " + Tools::intToString(anIndex) + " : " + Tools::floatToStringOneDecimal(m_angles_of_loudspeakers[anIndex]/ CICM_2PI * 360.) + "°";
    else
        return "No channel";
}

void AmbisonicsRestitution::computeAmplitudePanning()
{
    for(int i = 0; i < m_number_of_virtual_loudspeakers; i++)
    {
        double virtualAngle = ((double)i / (double)m_number_of_virtual_loudspeakers) * CICM_2PI;
        
        double ratio1;
        double ratio2;
        
        if(virtualAngle <= m_angles_of_loudspeakers[0])
        {
            // Le virtualHp est < à Hp(0) -> gain entre Hp(0) et Hp(last) //
            int ilast = m_number_of_real_loudspeakers - 1;
            double distance = m_angles_of_loudspeakers[0] + (CICM_2PI - m_angles_of_loudspeakers[ilast]);
            
            ratio1 = (m_angles_of_loudspeakers[0] - virtualAngle) / distance;
            ratio2 = 1. - ratio1;
            m_loudspeakers_gains_vector_double[0][i] = cos(ratio1 * CICM_PI2);
            m_loudspeakers_gains_vector_float[0][i] =  m_loudspeakers_gains_vector_double[0][i];
            
            m_loudspeakers_gains_vector_double[ilast][i] = cos(ratio2 * CICM_PI2);
            m_loudspeakers_gains_vector_float[ilast][i] = m_loudspeakers_gains_vector_double[ilast][i];
            
            // Le gain des autres Hp est nul //
            for(int j = 1; j < m_number_of_real_loudspeakers - 1; j++)
            {
                m_loudspeakers_gains_vector_double[j][i] = 0.;
                m_loudspeakers_gains_vector_float[j][i] = 0.;
            }
        }
        else if(virtualAngle > m_angles_of_loudspeakers[m_number_of_real_loudspeakers - 1])
        {
            // Le virtualHp est  à 0 -> gain entre le 0 et le dernier //
            int ilast = m_number_of_real_loudspeakers - 1;
            double distance = m_angles_of_loudspeakers[0] + (CICM_2PI - m_angles_of_loudspeakers[ilast]);
            
            ratio1 = (m_angles_of_loudspeakers[0] - (virtualAngle - CICM_2PI)) / distance ;
            ratio2 = (virtualAngle - m_angles_of_loudspeakers[ilast]) / distance;
            
            m_loudspeakers_gains_vector_double[0][i] = cos(ratio1 * CICM_PI2);
            m_loudspeakers_gains_vector_float[0][i] =  m_loudspeakers_gains_vector_double[0][i];
            
            m_loudspeakers_gains_vector_double[ilast][i] = cos(ratio2  * CICM_PI2);
            m_loudspeakers_gains_vector_float[ilast][i] = m_loudspeakers_gains_vector_double[ilast][i];
            
            // Le gain des autres Hp est nul //
            for(int j = 1; j < m_number_of_real_loudspeakers - 1; j++)
            {
                m_loudspeakers_gains_vector_double[j][i] = 0.;
                m_loudspeakers_gains_vector_float[j][i] = 0.;
            }
        }
        else
        {
            for(int j = 0; j < m_number_of_real_loudspeakers - 1; j++)
            {
                if(virtualAngle > m_angles_of_loudspeakers[j] && virtualAngle <= m_angles_of_loudspeakers[j+1])
                {
                    double distance = m_angles_of_loudspeakers[j+1] - m_angles_of_loudspeakers[j];
                    
                    ratio1 = (virtualAngle - m_angles_of_loudspeakers[j]) / distance;
                    ratio2 = (m_angles_of_loudspeakers[j+1] - virtualAngle) / distance;
                    
                    m_loudspeakers_gains_vector_double[j][i] = cos(ratio1 * CICM_PI2);
                    m_loudspeakers_gains_vector_float[j][i] =  m_loudspeakers_gains_vector_double[j][i];
                    
                    m_loudspeakers_gains_vector_double[j+1][i] = cos(ratio2 * CICM_PI2);
                    m_loudspeakers_gains_vector_float[j+1][i] =  m_loudspeakers_gains_vector_double[j+1][i];
                    
                    for(int k = 0; k < m_number_of_real_loudspeakers; k++)
                    {
                        if(k != j && k != j+1)
                        {
                            m_loudspeakers_gains_vector_double[k][i] = 0.;
                            m_loudspeakers_gains_vector_float[k][i] = 0.;
                        }
                    }
                }
            }
        }
        
    }
}

void AmbisonicsRestitution::computeMicrophoneSimulation()
{
    for(int i = 0; i < m_number_of_real_loudspeakers; i++)
    {
        double ratio;
        if(i == 0)
        {
            ratio = ((CICM_2PI - m_angles_of_loudspeakers[m_number_of_real_loudspeakers-1]) + m_angles_of_loudspeakers[1]);
        }
        else if(i == m_number_of_real_loudspeakers - 1)
        {
            ratio = (CICM_2PI - m_angles_of_loudspeakers[i-1]) + m_angles_of_loudspeakers[0];
        }
        else
        {
            ratio = (m_angles_of_loudspeakers[i+1] - m_angles_of_loudspeakers[i-1]);
        }
        
        for(int j = 0; j < m_number_of_virtual_loudspeakers; j++)
        {
            double distance;
            double virtualAngle = ((double)j / (double)m_number_of_virtual_loudspeakers) * CICM_2PI;
            distance = fabs(m_angles_of_loudspeakers[i] - virtualAngle);
            if(distance > CICM_PI)
                distance = CICM_2PI - distance;
            distance /= ratio;
            if(distance > 1.)
                distance  = 1.;
            
            m_loudspeakers_gains_vector_double[i][j] = cos(distance*CICM_PI2);
            m_loudspeakers_gains_vector_float[i][j] = m_loudspeakers_gains_vector_double[i][j];
        }
    }
}


AmbisonicsRestitution::~AmbisonicsRestitution()
{
	if(m_vector_float_input)
		cicm_free(m_vector_float_input)
	if(m_vector_double_input)
		cicm_free(m_vector_double_input);
	if(m_loudspeakers_vector_float)
		cicm_free(m_loudspeakers_vector_float);
	if(m_loudspeakers_vector_double)
		cicm_free(m_loudspeakers_vector_double);
	for(int i = 0; i < m_number_of_real_loudspeakers; i++)
    {
        cicm_free(m_loudspeakers_gains_vector_double[i]);
        cicm_free(m_loudspeakers_gains_vector_float[i]);
    }
    free(m_loudspeakers_gains_vector_double);
    free(m_loudspeakers_gains_vector_float);
	if(m_angles_of_loudspeakers)
		free(m_angles_of_loudspeakers);
	delete m_decoder;
}
