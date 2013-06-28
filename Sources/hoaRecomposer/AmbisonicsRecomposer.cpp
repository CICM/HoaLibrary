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

#include "AmbisonicsRecomposer.h"

AmbisonicsRecomposer::AmbisonicsRecomposer(long anOrder, long aNumberOfMicrophones, long aVectorSize, long aMode) : Ambisonics(anOrder, aVectorSize)
{
	m_number_of_microphones = Tools::clip_min(aNumberOfMicrophones, m_number_of_harmonics);
    m_number_of_outputs = m_number_of_harmonics;
    
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_encoders.push_back(new AmbisonicsEncoder(m_order, Hoa_Basic, m_vector_size));
        m_widers.push_back(new AmbisonicsWider(m_order, m_vector_size));
        m_lines.push_back(new CicmLine(4410, m_vector_size));
        m_wider_lines.push_back(new CicmLine(4410, m_vector_size));
        
        double angle = ((double)i / (double)(m_number_of_microphones)) * CICM_2PI;
        m_encoders[i]->setAzimuthBoth(angle);
        m_lines[i]->setCoefficientAngleDirect(angle);
        m_wider_lines[i]->setCoefficientDirect(1.);
    }
    Cicm_Vector_Float_Malloc(m_harmonics_vector_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_harmonics_vector_double, m_number_of_harmonics);
    Cicm_Vector_Float_Malloc(m_microphones_vector_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_microphones_vector_double, m_number_of_harmonics);
    
    Cicm_Vector_Float_Malloc(m_angles_vector_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_angles_vector_double, m_vector_size);
    
    m_harmonics_matrix_float    = new Cicm_Vector_Float[m_number_of_harmonics];
    m_harmonics_matrix_double   = new Cicm_Vector_Double[m_number_of_harmonics];
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        Cicm_Vector_Float_Malloc(m_harmonics_matrix_float[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_harmonics_matrix_double[i], m_vector_size);
    }
    
    Cicm_Matrix_Float_Malloc(m_recomposer_matrix_float, m_number_of_harmonics, m_number_of_microphones);
    Cicm_Matrix_Double_Malloc(m_recomposer_matrix_double, m_number_of_harmonics, m_number_of_microphones);
    for (int i = 0; i < m_number_of_microphones; i++)
	{
        Cicm_Matrix_Float_Set(m_recomposer_matrix_float, 0, i, m_number_of_microphones, 1.);
        Cicm_Matrix_Double_Set(m_recomposer_matrix_double, 0, i, m_number_of_microphones, 1.);
    }
    setMode(aMode);
}

void AmbisonicsRecomposer::computeMatrix(double aFishEyeFactor)
{
    double angle;
    aFishEyeFactor = Tools::clip(aFishEyeFactor, 0., 1.);
    for (int i = 0; i < m_number_of_microphones; i++)
	{
		angle = CICM_2PI * ((double)i / (double)(m_number_of_microphones));
        if(angle < CICM_PI)
            angle *= aFishEyeFactor;
        else
            angle = CICM_2PI - ((CICM_2PI - angle) * aFishEyeFactor);
		for (int j = 1; j < m_number_of_harmonics; j++)
		{
            int index = getHarmonicIndex(j);
            if(index > 0)
            {
                double value = cos(fabs(index) * angle);
                Cicm_Matrix_Float_Set(m_recomposer_matrix_float, j, i, m_number_of_microphones, value);
                Cicm_Matrix_Double_Set(m_recomposer_matrix_double, j, i, m_number_of_microphones, value);
            }
			else if(index < 0)
            {
                double value = sin(fabs(index) * angle);
                Cicm_Matrix_Float_Set(m_recomposer_matrix_float, j, i, m_number_of_microphones, value);
                Cicm_Matrix_Double_Set(m_recomposer_matrix_double, j, i, m_number_of_microphones, value);
            }
		}
    }
}

void AmbisonicsRecomposer::setMicrophoneAngle(long anIndex, double anAngle)
{
    if(anIndex >= 0 && anIndex < m_number_of_microphones)
        m_lines[anIndex]->setCoefficientAngle(anAngle);
}

double AmbisonicsRecomposer::getMicrophoneAngle(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_microphones)
        return m_lines[anIndex]->getCoefficient();
    else
        return 0.;
}

void AmbisonicsRecomposer::setMicrophoneWide(long anIndex, double aWidenValue)
{
    if(anIndex >= 0 && anIndex < m_number_of_microphones)
        m_wider_lines[anIndex]->setCoefficient(aWidenValue);
}

void AmbisonicsRecomposer::setFishEyeFactor(double aFishEyeFactor)
{
    computeMatrix(aFishEyeFactor);
}

void AmbisonicsRecomposer::setMode(long aMode)
{
    m_mode = Tools::clip(aMode, long(0), long(2));
    if(m_mode == Hoa_Fisheye)
    {
        m_number_of_inputs = m_number_of_microphones + 1;
    }
    else if(m_mode == Hoa_Fixe)
    {
        m_number_of_inputs = m_number_of_microphones;
        computeMatrix(1.);
    }
    else
        m_number_of_inputs = m_number_of_microphones;
        
}

double AmbisonicsRecomposer::getMicrophoneWide(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_microphones)
        return m_wider_lines[anIndex]->getCoefficient();
    else
        return 0.;
}

void AmbisonicsRecomposer::setVectorSize(long aVectorSize)
{
    m_vector_size = Tools::clip_power_of_two(aVectorSize);
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_encoders[i]->setVectorSize(m_vector_size);
        m_lines[i]->setVectorSize(m_vector_size);
        m_widers[i]->setVectorSize(m_vector_size);
        m_wider_lines[i]->setVectorSize(m_vector_size);
        
        Cicm_Free(m_angles_vector_float);
        Cicm_Free(m_angles_vector_double);
        Cicm_Vector_Float_Malloc(m_angles_vector_float, m_vector_size);
        Cicm_Vector_Double_Malloc(m_angles_vector_double, m_vector_size);
    }
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        Cicm_Free(m_harmonics_matrix_float[i]);
        Cicm_Free(m_harmonics_matrix_double[i]);
        Cicm_Vector_Float_Malloc(m_harmonics_matrix_float[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_harmonics_matrix_double[i], m_vector_size);
    }
}

void AmbisonicsRecomposer::setRamp(long aNumberOfSample)
{
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_lines[i]->setRamp(aNumberOfSample);
        m_wider_lines[i]->setRamp(aNumberOfSample);
    }
}

std::string AmbisonicsRecomposer::getMicrophonesName(long anIndex)
{
    if(anIndex >= 0 && anIndex < m_number_of_microphones)
        return "Virtual Microphone " + Tools::intToString(anIndex);
    else if(m_number_of_microphones == m_number_of_inputs && m_mode == Hoa_Fisheye)
        return "Fisheye Factor";
    else
        return "No Virtual Microphone";
}

AmbisonicsRecomposer::~AmbisonicsRecomposer()
{
	m_encoders.clear();
    m_lines.clear();
    m_widers.clear();
    m_wider_lines.clear();
    
    Cicm_Free(m_angles_vector_float);
    Cicm_Free(m_angles_vector_double);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        Cicm_Free(m_harmonics_matrix_float[i]);
        Cicm_Free(m_harmonics_matrix_double[i]);
    }
    Cicm_Free(m_harmonics_matrix_float);
    Cicm_Free(m_harmonics_matrix_double);
    
    Cicm_Free(m_harmonics_vector_float);
    Cicm_Free(m_harmonics_vector_double);
    Cicm_Free(m_microphones_vector_float);
    Cicm_Free(m_microphones_vector_double);
    
    Cicm_Free(m_recomposer_matrix_float);
    Cicm_Free(m_recomposer_matrix_double);
}



