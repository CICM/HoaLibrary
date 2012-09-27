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

#include "ambisonicRotate.hpp"

ambisonicRotate::ambisonicRotate(int anOrder, int aVectorSize)
{
	m_order					= anOrder;
	m_number_of_harmonics	= 2 * m_order + 1;
	m_number_of_inputs		= m_number_of_harmonics + 1;
	m_number_of_outputs		= m_number_of_harmonics;
	
	m_harmonicCos = new double[m_order];
	m_harmonicSin = new double[m_order];
	computeIndex();
	m_cosLookUp = new double[NUMBEROFCIRCLEPOINTS];
	m_sinLookUp = new double[NUMBEROFCIRCLEPOINTS];
	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++) 
	{
		m_cosLookUp[i] = cos((double)i * M_2PI / (double)NUMBEROFCIRCLEPOINTS);
		m_sinLookUp[i] = sin((double)i * M_2PI / (double)NUMBEROFCIRCLEPOINTS);
	}
	computeTrigo(0.);
	setVectorSize(aVectorSize);
}

void ambisonicRotate::computeIndex()
{
	m_index_of_harmonics	= new int[m_number_of_harmonics ];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = floor((float)((i - 1) / 2)) + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

int	ambisonicRotate::getParameters(std::string aParameter) const
{
	int value = 0;

	if (aParameter == "order")
		value = m_order;
	else if (aParameter == "samplingRate") 
		value =  m_sampling_rate;
	else if (aParameter == "vectorSize") 
		value =  m_vector_size;
	else if (aParameter == "numberOfInputs") 
		value =  m_number_of_inputs;
	else if (aParameter == "numberOfOutputs")
		value =  m_number_of_outputs;
	
	return value;
}

void ambisonicRotate::computeTrigo(double aTheta)
{
	long tmpAngle;
	if (aTheta < 0) 
		aTheta = aTheta + ( -floor(aTheta/M_2PI)) * M_2PI;
	double tmpTheta = aTheta;
	for(int i = 0; i < m_order; i++)
	{
		double angleFactor = tmpTheta*NUMBEROFCIRCLEPOINTS/(M_2PI);
	
		tmpAngle = (long)(angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
		m_harmonicSin[i] = m_sinLookUp[tmpAngle];
		m_harmonicCos[i] = m_cosLookUp[tmpAngle];
		
		tmpTheta += aTheta;
	}
}

void ambisonicRotate::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

ambisonicRotate::~ambisonicRotate()
{
	delete m_harmonicCos;
	delete m_harmonicSin;
	delete m_sinLookUp;
	delete m_cosLookUp;
	delete m_index_of_harmonics;
}
