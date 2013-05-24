/*
 *
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

#include "AmbisonicsRecomposer.h"

AmbisonicsRecomposer::AmbisonicsRecomposer(long anOrder, long aNumberOfMicrophones, long aVectorSize, long aMode) : Ambisonics(anOrder, aVectorSize)
{
    setMode(aMode);
	m_number_of_microphones = Tools::clip_min(aNumberOfMicrophones, m_number_of_harmonics);
    m_number_of_inputs = m_number_of_microphones;
    m_number_of_outputs = m_number_of_harmonics;
    for(int i = 0; i < m_number_of_microphones; i++)
    {
        m_encoders.push_back(new AmbisonicsEncoder(m_order, "basic", m_vector_size));
        m_widers.push_back(new AmbisonicsWider(m_order, m_vector_size));
        m_lines.push_back(new CicmLine(4410, m_vector_size));
        m_wider_lines.push_back(new CicmLine(4410, m_vector_size));
        
        double angle = ((double)i / (double)(m_number_of_microphones)) * CICM_2PI;
        m_encoders[i]->setAzimtuhBoth(angle);
        m_lines[i]->setCoefficientAngleDirect(angle);
        m_wider_lines[i]->setCoefficientDirect(1.);
    }
    Cicm_Vector_Float_Malloc(m_harmonics_vector_float, m_number_of_harmonics);
    Cicm_Vector_Double_Malloc(m_harmonics_vector_double, m_number_of_harmonics);
    
    Cicm_Vector_Float_Malloc(m_angles_vector_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_angles_vector_double, m_vector_size);
    
    m_harmonics_matrix_float    = new Cicm_Vector_Float[m_number_of_harmonics];
    m_harmonics_matrix_double   = new Cicm_Vector_Double[m_number_of_harmonics];
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        Cicm_Vector_Float_Malloc(m_harmonics_matrix_float[i], m_vector_size);
        Cicm_Vector_Double_Malloc(m_harmonics_matrix_double[i], m_vector_size);
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
    m_fishEyeFactor = 1 - Tools::clip(aFishEyeFactor, 0., 1.);
    double distanceBetwenTwoDefMics = CICM_2PI / m_number_of_microphones;
    for (int i=0; i < m_number_of_microphones; i++)
    {
        setMicrophoneAngle(i, Tools::radianInterp(m_fishEyeFactor, distanceBetwenTwoDefMics*i, 0.));
    }
}

void AmbisonicsRecomposer::setMode(long aMode)
{
    m_mode = Tools::clip(aMode, long(0), long(2));
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

AmbisonicsRecomposer::~AmbisonicsRecomposer()
{
	m_encoders.clear();
    m_lines.clear();
    m_widers.clear();
    m_wider_lines.clear();
    Cicm_Free(m_harmonics_vector_float);
    Cicm_Free(m_harmonics_vector_double);
    Cicm_Free(m_angles_vector_float);
    Cicm_Free(m_angles_vector_double);
    for(int i = 0; i < m_number_of_harmonics; i++)
    {
        Cicm_Free(m_harmonics_matrix_float[i]);
        Cicm_Free(m_harmonics_matrix_double[i]);
    }
    Cicm_Free(m_harmonics_matrix_float);
    Cicm_Free(m_harmonics_matrix_double);
}



