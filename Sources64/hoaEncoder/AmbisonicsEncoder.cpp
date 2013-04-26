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
	
    Cicm_Signal_Vector_Float_Malloc(m_ambisonics_coeffs_float, m_number_of_harmonics); 
    Cicm_Signal_Vector_Double_Malloc(m_ambisonics_coeffs_double, m_number_of_harmonics);
    Cicm_Signal_Vector_Double_Malloc(m_cosinus_table, NUMBEROFCIRCLEPOINTS);
    Cicm_Signal_Vector_Double_Malloc(m_sinus_table, NUMBEROFCIRCLEPOINTS);
	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++) 
	{
		m_cosinus_table[i] = cos((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
		m_sinus_table[i] = sin((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
	}
	setAzimtuh(0.);
}

std::string	AmbisonicsEncoder::getMode()
{
	return m_mode;
}

void AmbisonicsEncoder::setAzimtuh(double aTheta)
{
	m_ambisonics_coeffs_double[0] = 1.;
	int  tmpIndex = 2;
	long tmpAngle;
	if (aTheta < 0) 
		aTheta = aTheta + ( -floor(aTheta/CICM_2PI)) * CICM_2PI;

	double angleFactor = aTheta * NUMBEROFCIRCLEPOINTS / (CICM_2PI);
	
	for (int i = 1; i <= m_order; i++) 
	{
		tmpAngle = (long)(i*angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
		m_ambisonics_coeffs_double[tmpIndex-1] = m_sinus_table[tmpAngle];
		m_ambisonics_coeffs_double[tmpIndex]   = m_cosinus_table[tmpAngle];
		tmpIndex += 2;
	}
}

void AmbisonicsEncoder::setAzimtuh(float aTheta)
{
	m_ambisonics_coeffs_float[0] = 1.;
	int  tmpIndex = 2;
	long tmpAngle;
	if (aTheta < 0)
		aTheta = aTheta + ( -floor(aTheta/CICM_2PI)) * CICM_2PI;
    
	double angleFactor = aTheta * NUMBEROFCIRCLEPOINTS / (CICM_2PI);
	
	for (int i = 1; i <= m_order; i++)
	{
		tmpAngle = (long)(i*angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
		m_ambisonics_coeffs_float[tmpIndex-1] = m_sinus_table[tmpAngle];
		m_ambisonics_coeffs_float[tmpIndex]   = m_cosinus_table[tmpAngle];
		tmpIndex += 2;
	}
}

void AmbisonicsEncoder::setAzimtuhBoth(double aTheta)
{
	setAzimtuh(aTheta);
    setAzimtuh((float)aTheta);
}

AmbisonicsEncoder::~AmbisonicsEncoder()
{
	Cicm_Free(m_ambisonics_coeffs_float);
    Cicm_Free(m_ambisonics_coeffs_double);
    Cicm_Free(m_cosinus_table);
    Cicm_Free(m_sinus_table);
}