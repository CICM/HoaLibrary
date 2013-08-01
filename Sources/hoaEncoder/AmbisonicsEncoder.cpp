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

#include "AmbisonicsEncoder.h"

AmbisonicsEncoder::AmbisonicsEncoder(long anOrder, long aMode, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{
    m_mode = Tools::clip(aMode, (long)0, (long)1);
	if(m_mode == Hoa_Split)
		m_number_of_inputs	= m_order + 2;
	else
		m_number_of_inputs	= 2;
    
    Cicm_Vector_Float_Malloc(m_ambisonics_coeffs_float, m_number_of_harmonics); 
    Cicm_Vector_Double_Malloc(m_ambisonics_coeffs_double, m_number_of_harmonics);
	Cicm_Vector_Float_Malloc(m_cos_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_sin_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_angles_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_cos_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_sin_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_angles_double, m_vector_size);
    
	setAzimuthBoth(0.);
}

long AmbisonicsEncoder::getMode()
{
	return m_mode;
}

void AmbisonicsEncoder::setAzimuth(double aTheta)
{
    m_ambisonics_coeffs_float[0] = 1.;
	for (int i = 2, j = 1; i < m_number_of_harmonics; i += 2, j++)
    {
		m_ambisonics_coeffs_double[i-1] = sin(j*aTheta);
		m_ambisonics_coeffs_double[i]   = cos(j*aTheta);
	}
}

void AmbisonicsEncoder::setAzimuth(float aTheta)
{
	m_ambisonics_coeffs_float[0] = 1.;
	for (int i = 2, j = 1; i < m_number_of_harmonics; i += 2, j++)
    {
		m_ambisonics_coeffs_float[i-1] = sin(j*aTheta);
		m_ambisonics_coeffs_float[i]   = cos(j*aTheta);
	}
}

void AmbisonicsEncoder::setAzimuthBoth(double aTheta)
{
	setAzimuth(aTheta);
    setAzimuth((float)aTheta);
}

void AmbisonicsEncoder::setVectorSize(long aVectorSize)
{
	if(m_vector_size != Tools::clip_power_of_two(aVectorSize))
    {
        m_vector_size = Tools::clip_power_of_two(aVectorSize);
        Cicm_Free(m_cos_float);
        Cicm_Free(m_sin_float);
        Cicm_Free(m_angles_float);
        Cicm_Free(m_cos_double);
        Cicm_Free(m_sin_double);
        Cicm_Free(m_angles_double);
        Cicm_Vector_Float_Malloc(m_cos_float, m_vector_size);
        Cicm_Vector_Float_Malloc(m_sin_float, m_vector_size);
        Cicm_Vector_Float_Malloc(m_angles_float, m_vector_size);
        Cicm_Vector_Double_Malloc(m_cos_double, m_vector_size);
        Cicm_Vector_Double_Malloc(m_sin_double, m_vector_size);
        Cicm_Vector_Double_Malloc(m_angles_double, m_vector_size);
    }
}

AmbisonicsEncoder::~AmbisonicsEncoder()
{
	Cicm_Free(m_ambisonics_coeffs_float);
    Cicm_Free(m_ambisonics_coeffs_double);
    Cicm_Free(m_cos_float);
    Cicm_Free(m_sin_float);
    Cicm_Free(m_angles_float);
    Cicm_Free(m_cos_double);
    Cicm_Free(m_sin_double);
    Cicm_Free(m_angles_double);
}