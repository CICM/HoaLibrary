/*
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#include "AmbisonicsBinaural.h"


AmbisonicsBinaural::AmbisonicsBinaural(long anOrder, std::string aRootPath, std::string aPinnaSize, double aSamplingRate, long aVectorSize) : Ambisonics(anOrder, aVectorSize, aSamplingRate)
{
    /* Limit Order Due To HRTFs Discretization */
    if (m_order > 35)
		m_order = 35;
    m_number_of_harmonics = m_order * 2 +1;
    m_number_of_inputs    = m_number_of_harmonics;
    m_number_of_outputs = 2;
    
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
    m_pinna_size        = aPinnaSize;
    
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
    
    if (m_pinna_size != "Small" && m_pinna_size != "Large")
        m_pinna_size = "Small";
    
    m_hrtf_full_path += Tools::intToString(m_sampling_rate) + "/" + m_pinna_size + "/";
    
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
        //angleOfLoudspeaker += 270;
        //angleOfLoudspeaker %= 360;
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
        Cicm_Free(m_impluse_matrix);
        m_impluse_matrix = NULL;
    }
    
    
    Cicm_Matrix_Float_Malloc(m_impluse_matrix, m_impulse_size * 2, m_number_of_harmonics);
    if(!m_impluse_matrix)
        return 0;
    
    Cicm_Vector_Double HarmonicVector;
    Cicm_Vector_Double LoudspeakersVector;
    Cicm_Vector_Double_Malloc(HarmonicVector, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(LoudspeakersVector, m_number_of_loudspeakers);

	Cicm_Vector_Double_Clear(HarmonicVector, m_number_of_harmonics);
    Cicm_Vector_Double_Clear(LoudspeakersVector, m_number_of_loudspeakers);
	
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
			//Cicm_Matrix_Float_Set(m_impluse_matrix, sampleIndex                 , harmonicIndex, m_number_of_harmonics, tmpValueL);
			//Cicm_Matrix_Float_Set(m_impluse_matrix, sampleIndex+m_impulse_size  , harmonicIndex, m_number_of_harmonics, tmpValueR);
		}
	}
    
    Cicm_Free(HarmonicVector);
    Cicm_Free(LoudspeakersVector);
    return 1;
}

void AmbisonicsBinaural::setPinnaSize(std::string aPinnaSize)
{
    if(aPinnaSize != m_pinna_size)
    {
        m_pinna_size = aPinnaSize;
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
        Cicm_Free(m_input_matrix);
    m_input_matrix = NULL;
    if(m_result_matrix)
        Cicm_Free(m_result_matrix);
    m_result_matrix = NULL;
    if(m_linear_vector_left)
        Cicm_Free(m_linear_vector_left);
    m_linear_vector_left = NULL;
    if(m_linear_vector_right)
        Cicm_Free(m_linear_vector_right);
    m_linear_vector_right = NULL;
    
    Cicm_Matrix_Float_Malloc(m_input_matrix, m_number_of_harmonics, aVectorSize);
    Cicm_Matrix_Float_Malloc(m_result_matrix, m_impulse_size * 2, aVectorSize);
    Cicm_Vector_Float_Malloc(m_linear_vector_left, aVectorSize + m_impulse_size - 1);
    Cicm_Vector_Float_Malloc(m_linear_vector_right, aVectorSize + m_impulse_size - 1);
    
    m_result_matrix_right   = m_result_matrix;
    m_result_matrix_left    = m_result_matrix+aVectorSize*m_impulse_size;
    if(m_input_matrix && m_result_matrix && m_linear_vector_left && m_linear_vector_right)
    {
         m_vector_size = aVectorSize;
        return 1;
    }
    else
        return 0;
}

AmbisonicsBinaural::~AmbisonicsBinaural()
{
    delete m_decoder;
	if(m_input_matrix)
        Cicm_Free(m_input_matrix);
    if(m_result_matrix)
        Cicm_Free(m_result_matrix);
    if(m_impluse_matrix)
        Cicm_Free(m_impluse_matrix);
    if(m_linear_vector_left)
        Cicm_Free(m_linear_vector_left);
    if(m_linear_vector_right)
        Cicm_Free(m_linear_vector_right);
    for(int i = 0; i < m_number_of_loudspeakers; i++)
	{
        free(m_impulse_left[i]);
        free(m_impulse_right[i]);
    }
}


