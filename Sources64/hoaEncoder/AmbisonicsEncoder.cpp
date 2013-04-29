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

#include "AmbisonicsEncoder.h"

AmbisonicsEncoder::AmbisonicsEncoder(long anOrder, std::string aMode, long aVectorSize) : Ambisonics(anOrder, aVectorSize)
{	
	if(aMode == "split")
    {
        m_mode = aMode;
		m_number_of_inputs	= m_order + 2;
    }
	else
    {
        m_mode = "basic";
		m_number_of_inputs	= 2;
    }
    
    Cicm_Vector_Float_Malloc(m_ambisonics_coeffs_float, m_number_of_harmonics); 
    Cicm_Vector_Double_Malloc(m_ambisonics_coeffs_double, m_number_of_harmonics);
	Cicm_Vector_Float_Malloc(m_cos_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_sin_float, m_vector_size);
    Cicm_Vector_Float_Malloc(m_angles_float, m_vector_size);
    Cicm_Vector_Double_Malloc(m_cos_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_sin_double, m_vector_size);
    Cicm_Vector_Double_Malloc(m_angles_double, m_vector_size);
    
	setAzimtuhBoth(0.);
}

std::string	AmbisonicsEncoder::getMode()
{
	return m_mode;
}

void AmbisonicsEncoder::setAzimtuh(double aTheta)
{
    m_ambisonics_coeffs_float[0] = 1.;
	for (int i = 2, j = 1; i < m_number_of_harmonics; i += 2, j++)
    {
		m_ambisonics_coeffs_double[i-1] = sin(j*aTheta);
		m_ambisonics_coeffs_double[i]   = cos(j*aTheta);
	}
}

void AmbisonicsEncoder::setAzimtuh(float aTheta)
{
	m_ambisonics_coeffs_float[0] = 1.;
	for (int i = 2, j = 1; i < m_number_of_harmonics; i += 2, j++)
    {
		m_ambisonics_coeffs_float[i-1] = sin(j*aTheta);
		m_ambisonics_coeffs_float[i]   = cos(j*aTheta);
	}
}

void AmbisonicsEncoder::setAzimtuhBoth(double aTheta)
{
	setAzimtuh(aTheta);
    setAzimtuh((float)aTheta);
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