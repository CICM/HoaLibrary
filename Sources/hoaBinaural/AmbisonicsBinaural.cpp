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

#include "AmbisonicsBinaural.h"


AmbisonicsBinaural::AmbisonicsBinaural(long anOrder, std::string aRootPath, long aPinnaeSize, double aSamplingRate, long aVectorSize) : Ambisonic(anOrder, aVectorSize, aSamplingRate)
{
    /* Limit Order Due To HRTFs Discretization */
    if (m_order > 35)
		m_order = 35;
    m_number_of_harmonics = m_order * 2 +1;
    m_number_of_inputs    = m_number_of_harmonics;
    m_number_of_outputs = 2;
    
	m_loudspeakers_configurations[0] = 3;
	m_loudspeakers_configurations[1] = 4;
	m_loudspeakers_configurations[2] = 6;
	m_loudspeakers_configurations[3] = 8;
	m_loudspeakers_configurations[4] = 9;
	m_loudspeakers_configurations[5] = 12;
	m_loudspeakers_configurations[6] = 18;
	m_loudspeakers_configurations[7] = 24;
	m_loudspeakers_configurations[8] = 36;
	m_loudspeakers_configurations[9] = 72;
    /* Check The Best Number Of Virtual Loudspeakers For HRTFs */
	m_number_of_loudspeakers = m_loudspeakers_configurations[0];
	for (int i = 0; i < 10; i++)
	{
		if (m_loudspeakers_configurations[i] >= m_number_of_harmonics)
		{
			m_number_of_loudspeakers = m_loudspeakers_configurations[i];
			break;
		}
	}
	m_decoder = new AmbisonicsDecoder(m_order, m_number_of_loudspeakers);
    
    /* Load HRTFs */
    m_impulse_left      = new double*[m_number_of_loudspeakers];
	m_impulse_right     = new double*[m_number_of_loudspeakers];
    for(int i = 0; i < m_number_of_loudspeakers; i++)
    {
        m_impulse_left[i]   = new double[1];
        m_impulse_right[i]  = new double[1];
    }
    
    m_hrtf_root_path    = aRootPath;
    m_Pinnae_size        = aPinnaeSize;
    
    m_impluse_matrix  = NULL;
    m_result_matrix   = NULL;
    m_input_matrix    = NULL;
    m_linear_vector_left  = NULL;
    m_linear_vector_right = NULL;

    if(loadImpulses())
        m_hrtf_loaded = matrixResize(m_vector_size);
}

long AmbisonicsBinaural::loadImpulses()
{
    m_hrtf_loaded = 0;
    /* Create HRTFs Path */
    m_hrtf_full_path = m_hrtf_root_path;
    
    if (m_sampling_rate == 48000)
        m_impulse_size = 217;
    else if(m_sampling_rate == 88200)
        m_impulse_size = 400;
    else if(m_sampling_rate == 96000)
        m_impulse_size = 435;
    else
    {
        m_impulse_size = 200;
        m_sampling_rate = 44100;
    }
    std::string Pinnae;
    
    if (m_Pinnae_size == Hoa_Large)
        Pinnae = "Large";
    else
        Pinnae = "Small";
    m_hrtf_full_path += Tools::intToString(m_sampling_rate) + "/" + Pinnae + "/";
    
    /* Load HRTFs */
	std::string leftFilePath;
	std::string rightFilePath;
    
	for(int i = 0; i < m_number_of_loudspeakers; i++)
	{
        free(m_impulse_left[i]);
        m_impulse_left[i] = NULL;
        free(m_impulse_right[i]);
        m_impulse_right[i] = NULL;
		int angleOfLoudspeaker = 360 / m_number_of_loudspeakers * i;
        angleOfLoudspeaker += 270;
        angleOfLoudspeaker %= 360;
        leftFilePath  = m_hrtf_full_path + "left"  + Tools::intToString(angleOfLoudspeaker) + ".wav";
		rightFilePath = m_hrtf_full_path + "right" + Tools::intToString(angleOfLoudspeaker) + ".wav";
        
		m_impulse_left[i]   = Tools::Read_Wav(const_cast<char*>(leftFilePath.c_str()));
		m_impulse_right[i]  = Tools::Read_Wav(const_cast<char*>(rightFilePath.c_str()));
        
		if(m_impulse_left[i] == NULL || m_impulse_right[i] == NULL)
        {
            m_impulse_size = 0;
            return 0;
        }
	}
    
    /* Write Hrtfs To The Matrix */
    if(m_impluse_matrix)
    {
        cicm_free(m_impluse_matrix);
        m_impluse_matrix = NULL;
    }
    
    
    cicm_malloc_mat_f(m_impluse_matrix, m_impulse_size * 2, m_number_of_harmonics);
    if(!m_impluse_matrix)
        return 0;
    
    cicm_vector_double HarmonicVector;
    cicm_vector_double LoudspeakersVector;
    cicm_malloc_vec_d(HarmonicVector, m_number_of_harmonics);
    cicm_malloc_vec_d(LoudspeakersVector, m_number_of_loudspeakers);

	cicm_clear_vec_d(HarmonicVector, m_number_of_harmonics);
    cicm_clear_vec_d(LoudspeakersVector, m_number_of_loudspeakers);
	
    HarmonicVector[0]=1;
	for(int harmonicIndex = 0; harmonicIndex < m_number_of_harmonics; harmonicIndex++)
	{
		if(harmonicIndex != 0)
		{
			HarmonicVector[harmonicIndex-1] = 0;
			HarmonicVector[harmonicIndex]= 1;
		}
		m_decoder->process(HarmonicVector, LoudspeakersVector);
		
		for(int sampleIndex = 0; sampleIndex < m_impulse_size; sampleIndex++)
		{
			double tmpValueL = 0;
			double tmpValueR = 0;
			for (int virtualSpeakerIndex = 0; virtualSpeakerIndex < m_number_of_loudspeakers; virtualSpeakerIndex++)
			{
				tmpValueL += LoudspeakersVector[virtualSpeakerIndex] * m_impulse_left[virtualSpeakerIndex][sampleIndex];
				tmpValueR += LoudspeakersVector[virtualSpeakerIndex] * m_impulse_right[virtualSpeakerIndex][sampleIndex];
			}
            m_impluse_matrix[sampleIndex*m_number_of_harmonics+harmonicIndex] = tmpValueL * (1. / 1.125) * (44100. / (double)m_sampling_rate);
            m_impluse_matrix[(sampleIndex+m_impulse_size)*m_number_of_harmonics+harmonicIndex] = tmpValueR * (1. / 1.125) * (44100. / (double)m_sampling_rate);
		}
	}
    
    cicm_free(HarmonicVector);
    cicm_free(LoudspeakersVector);
    return 1;
}

void AmbisonicsBinaural::setPinnaeSize(long aPinnaeSize)
{
    aPinnaeSize = Tools::clip(aPinnaeSize, (long)Hoa_Small, (long)Hoa_Large);
    if(aPinnaeSize != m_Pinnae_size)
    {
        m_Pinnae_size = aPinnaeSize;
        m_hrtf_loaded = loadImpulses();
    }
}

void AmbisonicsBinaural::setSamplingRate(long aSamplingRate)
{
    if (m_sampling_rate != aSamplingRate)
    {
        m_hrtf_loaded = 0;
        m_sampling_rate = aSamplingRate;
        if(loadImpulses())
            m_hrtf_loaded = matrixResize(m_vector_size);
    }
}

void AmbisonicsBinaural::setVectorSize(long aVectorSize)
{
    if(m_vector_size != aVectorSize)
    {
        m_hrtf_loaded = 0;
        m_vector_size = 0;
        m_hrtf_loaded = matrixResize(aVectorSize);
       
    }
}

long AmbisonicsBinaural::matrixResize(long aVectorSize)
{
    m_hrtf_loaded = 0;
    if(m_input_matrix)
        cicm_free(m_input_matrix);
    m_input_matrix = NULL;
    if(m_result_matrix)
        cicm_free(m_result_matrix);
    m_result_matrix = NULL;
    if(m_linear_vector_left)
        cicm_free(m_linear_vector_left);
    m_linear_vector_left = NULL;
    if(m_linear_vector_right)
        cicm_free(m_linear_vector_right);
    m_linear_vector_right = NULL;
    
    cicm_malloc_mat_f(m_input_matrix, m_number_of_harmonics, aVectorSize);
    cicm_malloc_mat_f(m_result_matrix, m_impulse_size * 2, aVectorSize);
    cicm_malloc_vec_f(m_linear_vector_left, aVectorSize + m_impulse_size - 1);
    cicm_malloc_vec_f(m_linear_vector_right, aVectorSize + m_impulse_size - 1);
    
    m_result_matrix_right   = m_result_matrix+aVectorSize*m_impulse_size;
    m_result_matrix_left    = m_result_matrix;
    if(m_input_matrix && m_result_matrix && m_linear_vector_left && m_linear_vector_right)
    {
         m_vector_size = aVectorSize;
        return 1;
    }
    else
        return 0;
}

std::string AmbisonicsBinaural::getLoudspeakerName(long anIndex)
{
    if(anIndex == 0)
        return "Left headphone";
    else
        return "Right headphone";
}

double AmbisonicsBinaural::getLoudspeakerAngle(long anIndex)
{
    if(anIndex == 0)
        return 90.f;
    else
        return 270.f;
}

AmbisonicsBinaural::~AmbisonicsBinaural()
{
    delete m_decoder;
	if(m_input_matrix)
        cicm_free(m_input_matrix);
    if(m_result_matrix)
        cicm_free(m_result_matrix);
    if(m_impluse_matrix)
        cicm_free(m_impluse_matrix);
    if(m_linear_vector_left)
        cicm_free(m_linear_vector_left);
    if(m_linear_vector_right)
        cicm_free(m_linear_vector_right);
	
    for(int i = 0; i < m_number_of_loudspeakers; i++)
	{
		if(m_impulse_left[i])
			free(m_impulse_left[i]);
		if(m_impulse_right[i])
			free(m_impulse_right[i]);
    }
	free(m_impulse_left);
	free(m_impulse_right);
}


