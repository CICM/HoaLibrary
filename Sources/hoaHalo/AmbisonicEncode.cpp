/*
 *
 * Copyright (C) 2012 Julien Colafrancesco & Pierre Guillot, Universite Paris 8
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

#include "AmbisonicEncode.h"

AmbisonicEncode::AmbisonicEncode(long anOrder, std::string aMode, long aVectorSize)
{	
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_mode					= aMode;
	m_number_of_outputs		= m_number_of_harmonics;
	m_ambiCoeffs			= new double[m_number_of_harmonics];
	if(aMode == "split")
		m_number_of_inputs	= m_order + 2;
	else
		m_number_of_inputs	= 2;	
	
	computeIndex();
	
	m_cosLookUp = new double[NUMBEROFCIRCLEPOINTS];
	m_sinLookUp = new double[NUMBEROFCIRCLEPOINTS];
	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++) 
	{
		m_cosLookUp[i] = cos((double)i * M_2PI / (double)NUMBEROFCIRCLEPOINTS);
		m_sinLookUp[i] = sin((double)i * M_2PI / (double)NUMBEROFCIRCLEPOINTS);
	}
	setAzimtuh(0.);
	setVectorSize(aVectorSize);
}

long AmbisonicEncode::getOrder()
{
	return m_order;
}

long AmbisonicEncode::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicEncode::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicEncode::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicEncode::getVectorSize()
{
	return m_vector_size;
}

std::string	AmbisonicEncode::getMode()
{
	return m_mode;
}

void AmbisonicEncode::computeIndex()
{
	m_index_of_harmonics	= new long[m_number_of_harmonics ];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = (i - 1) / 2 + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void AmbisonicEncode::setAzimtuh(double aTheta)
{
	m_ambiCoeffs[0] = 1.;
	int  tmpIndex = 2;
	long tmpAngle;
	if (aTheta < 0) 
		aTheta = aTheta + ( -floor(aTheta/M_2PI)) * M_2PI;

	double angleFactor = aTheta*NUMBEROFCIRCLEPOINTS/(M_2PI);
	
	for (int i = 1; i <= m_order; i++) 
	{
		tmpAngle = (long)(i*angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
		m_ambiCoeffs[tmpIndex-1] = m_sinLookUp[tmpAngle];
		m_ambiCoeffs[tmpIndex]   = m_cosLookUp[tmpAngle];
		
		tmpIndex += 2;
	}
	
}

void AmbisonicEncode::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

AmbisonicEncode::~AmbisonicEncode()
{
	delete m_ambiCoeffs;
}