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

AmbisonicsRestitution::AmbisonicsRestitution(long anOrder, long aNumberOfLouspeakers, long aResitutionMode, long aVectorSize) : Ambisonics(anOrder, aVectorSize), Planewaves(aNumberOfLouspeakers, aVectorSize)
{
    m_decoder = new AmbisonicsDecoder(m_order, m_number_of_harmonics+1, Ambisonics::m_vector_size);
    
    m_vector_float_input = NULL;
    m_vector_double_input = NULL;
    m_loudspeakers_vector_float = NULL;
    m_loudspeakers_vector_double = NULL;
    
    m_loudspeakers_gains_vector_float   = NULL;
    m_loudspeakers_gains_vector_double  = NULL;
    
    m_restitution_mode = Tools::clip(aResitutionMode, (long)Hoa_Amplitude_Panning, (long)Hoa_Microphone_Simulation);
    setNumberOfLoudspeakers(aNumberOfLouspeakers);
}

void AmbisonicsRestitution::setRestitutionMode(long aResitutionMode)
{
    /*
    m_restitution_mode = Tools::clip(aResitutionMode, (long)Hoa_Amplitude_Panning, (long)Hoa_Microphone_Simulation);
    if(m_restitution_mode == Hoa_Amplitude_Panning)
        computeAmplitudePanning();
    else
        computeMicrophoneSimulation();
     */
}

long AmbisonicsRestitution::getRestitutionMode()
{
    return m_restitution_mode;
}

void AmbisonicsRestitution::setNumberOfLoudspeakers(long aNumberOfLousperkers, bool standardOnOff)
{
    Planewaves::setNumberOfLoudspeakers(aNumberOfLousperkers, standardOnOff);
    
    if(m_loudspeakers_gains_vector_double)
    {
        for(int i = 0; i < m_number_of_loudspeakers; i++)
            Cicm_Free(m_loudspeakers_gains_vector_double[i]);
        Cicm_Free(m_loudspeakers_gains_vector_double);
    }
    if(m_loudspeakers_gains_vector_float)
    {
        for(int i = 0; i < m_number_of_loudspeakers; i++)
            Cicm_Free(m_loudspeakers_gains_vector_float[i]);
        Cicm_Free(m_loudspeakers_gains_vector_float);
    }
    
    m_loudspeakers_gains_vector_float   = new Cicm_Vector_Float[m_number_of_loudspeakers];
    m_loudspeakers_gains_vector_double  = new Cicm_Vector_Double[m_number_of_loudspeakers];
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        Cicm_Vector_Float_Malloc(m_loudspeakers_gains_vector_float[i], m_decoder->getNumberOfLoudspeakers());
        Cicm_Vector_Double_Malloc(m_loudspeakers_gains_vector_double[i], m_decoder->getNumberOfLoudspeakers());
    }
    
    if(m_restitution_mode == Hoa_Amplitude_Panning)
        computeAmplitudePanning();
    else
        computeMicrophoneSimulation();    
}

void AmbisonicsRestitution::computeDecoder()
{
    int numberOfloudspeakers = m_number_of_harmonics+1;
    
    if(m_restitution_mode == Hoa_Amplitude_Panning)
    {
        double smallestAngle = CICM_2PI;
        for (int i = 0; i < m_number_of_loudspeakers-1; i++)
        {
            if(m_angles_of_loudspeakers[i+1] - m_angles_of_loudspeakers[i] < smallestAngle)
                smallestAngle = m_angles_of_loudspeakers[i+1] - m_angles_of_loudspeakers[i];
        }/*
        if((CICM_2PI - m_angles_of_loudspeakers[m_number_of_loudspeakers-1]) + m_angles_of_loudspeakers[0] < smallestAngle)
            smallestAngle = (CICM_2PI - m_angles_of_loudspeakers[m_number_of_loudspeakers-1]) + m_angles_of_loudspeakers[0];
        */
        while (CICM_2PI / (double)m_decoder->getNumberOfLoudspeakers() > smallestAngle)
        {
            numberOfloudspeakers++;
        }
    }
    
    if(m_vector_float_input)
        Cicm_Free(m_vector_float_input);
    if(m_vector_double_input)
        Cicm_Free(m_vector_double_input);
    if(m_loudspeakers_vector_float)
        Cicm_Free(m_loudspeakers_vector_float);
    if(m_loudspeakers_vector_double)
        Cicm_Free(m_loudspeakers_vector_double);
    
    m_decoder->setNumberOfLoudspeakers(numberOfloudspeakers);
    
    Cicm_Vector_Float_Malloc(m_vector_float_input, m_decoder->getNumberOfLoudspeakers());
    Cicm_Vector_Double_Malloc(m_vector_double_input, m_decoder->getNumberOfLoudspeakers());
    Cicm_Vector_Float_Malloc(m_loudspeakers_vector_float, m_decoder->getNumberOfLoudspeakers());
    Cicm_Vector_Double_Malloc(m_loudspeakers_vector_double, m_decoder->getNumberOfLoudspeakers());
}

void AmbisonicsRestitution::setLoudspeakerAngle(long anIndex, double anAngle)
{
    Planewaves::setLoudspeakerAngle(anIndex, anAngle);    
    computeDecoder();
    
    if(m_restitution_mode == Hoa_Amplitude_Panning)
        computeAmplitudePanning();
    else
        computeMicrophoneSimulation();
}

void AmbisonicsRestitution::computeAmplitudePanning()
{
    for(int i = 0; i < m_decoder->getNumberOfLoudspeakers(); i++)
    {
        double virtualAngle = ((double)i / (double)m_decoder->getNumberOfLoudspeakers()) * CICM_2PI;
       
        double ratio1;
        double ratio2;
        
        if(virtualAngle <= m_angles_of_loudspeakers[0])
        {
             // Le virtualHp est < à Hp(0) -> gain entre Hp(0) et Hp(last) //
            int ilast = m_number_of_loudspeakers - 1;
            double distance = m_angles_of_loudspeakers[0] + (CICM_2PI - m_angles_of_loudspeakers[ilast]);
            
            ratio1 = (m_angles_of_loudspeakers[0] - virtualAngle) / distance;
            ratio2 = 1. - ratio1;
            m_loudspeakers_gains_vector_double[0][i] = cos(ratio1 * CICM_PI2);
            m_loudspeakers_gains_vector_float[0][i] =  m_loudspeakers_gains_vector_double[0][i];
            
            m_loudspeakers_gains_vector_double[ilast][i] = cos(ratio2 * CICM_PI2);
            m_loudspeakers_gains_vector_float[ilast][i] = m_loudspeakers_gains_vector_double[ilast][i];
            
            // Le gain des autres Hp est nul //
            for(int j = 1; j < m_number_of_loudspeakers - 1; j++)
            {
                m_loudspeakers_gains_vector_double[j][i] = 0.;
                m_loudspeakers_gains_vector_float[j][i] = 0.;
            }
        }
        else if(virtualAngle > m_angles_of_loudspeakers[m_number_of_loudspeakers - 1])
        {
            // Le virtualHp est  à 0 -> gain entre le 0 et le dernier //
            int ilast = m_number_of_loudspeakers - 1;
            double distance = m_angles_of_loudspeakers[0] + (CICM_2PI - m_angles_of_loudspeakers[ilast]);
            
            ratio1 = (m_angles_of_loudspeakers[0] - (virtualAngle - CICM_2PI)) / distance ;
            ratio2 = (virtualAngle - m_angles_of_loudspeakers[ilast]) / distance;
            
            m_loudspeakers_gains_vector_double[0][i] = cos(ratio1 * CICM_PI2);
            m_loudspeakers_gains_vector_float[0][i] =  m_loudspeakers_gains_vector_double[0][i];
            
            m_loudspeakers_gains_vector_double[ilast][i] = cos(ratio2  * CICM_PI2);
            m_loudspeakers_gains_vector_float[ilast][i] = m_loudspeakers_gains_vector_double[ilast][i];
            
            // Le gain des autres Hp est nul //
            for(int j = 1; j < m_number_of_loudspeakers - 1; j++)
            {
                m_loudspeakers_gains_vector_double[j][i] = 0.;
                m_loudspeakers_gains_vector_float[j][i] = 0.;
            }
        }
        else
        {
            for(int j = 0; j < m_number_of_loudspeakers - 1; j++)
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
                    
                    for(int k = 0; k < m_number_of_loudspeakers; k++)
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
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        double ratio;
        if(i == 0)
        {
            ratio = ((CICM_2PI - m_angles_of_loudspeakers[m_number_of_loudspeakers-1]) + m_angles_of_loudspeakers[1]);
        }
        else if(i == m_number_of_loudspeakers - 1)
        {
            ratio = (CICM_2PI - m_angles_of_loudspeakers[i-1]) + m_angles_of_loudspeakers[0];
        }
        else
        {
            ratio = (m_angles_of_loudspeakers[i+1] - m_angles_of_loudspeakers[i-1]);
        }
        
        for(int j = 0; j < m_decoder->getNumberOfLoudspeakers(); j++)
        {
            double distance;
            double virtualAngle = ((double)j / (double)m_decoder->getNumberOfLoudspeakers()) * CICM_2PI;
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
    Cicm_Free(m_vector_float_input);
    Cicm_Free(m_vector_double_input);
    Cicm_Free(m_loudspeakers_vector_float);
    Cicm_Free(m_loudspeakers_vector_double);
    
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        Cicm_Free(m_loudspeakers_gains_vector_double[i]);
        Cicm_Free(m_loudspeakers_gains_vector_float[i]);
    }
    
    Cicm_Free(m_loudspeakers_gains_vector_double);
    Cicm_Free(m_loudspeakers_gains_vector_float);

	delete m_decoder;
}

