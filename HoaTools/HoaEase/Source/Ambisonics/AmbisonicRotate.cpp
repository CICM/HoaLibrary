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

#include "AmbisonicRotate.h"

AmbisonicRotate::AmbisonicRotate(long anOrder, long aVectorSize)
{
	m_order					= Tools::clip_min(anOrder, (long)1);
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
		m_cosLookUp[i] = cos((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
		m_sinLookUp[i] = sin((double)i * CICM_2PI / (double)NUMBEROFCIRCLEPOINTS);
	}
	setAzimuth(0.);
	setVectorSize(aVectorSize);
}

void AmbisonicRotate::computeIndex()
{
	m_index_of_harmonics	= new long[m_number_of_harmonics];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = floor((float)((i - 1) / 2)) + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

long AmbisonicRotate::getOrder()
{
	return m_order;
}

long AmbisonicRotate::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long AmbisonicRotate::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long AmbisonicRotate::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long AmbisonicRotate::getVectorSize()
{
	return m_vector_size;
}

double AmbisonicRotate::getAzimuth()
{
	return m_azimuth;
}

void AmbisonicRotate::setAzimuth(double aTheta)
{
	long tmpAngle;
	if (aTheta < 0) 
		aTheta = aTheta + ( -floor(aTheta/CICM_2PI)) * CICM_2PI;
	double tmpTheta = aTheta;
	m_azimuth = fmod(aTheta + CICM_2PI, CICM_2PI);
	for(int i = 0; i < m_order; i++)
	{
		double angleFactor = tmpTheta*NUMBEROFCIRCLEPOINTS/(CICM_2PI);
	
		tmpAngle = (long)(angleFactor)%(NUMBEROFCIRCLEPOINTS-1);
		m_harmonicSin[i] = m_sinLookUp[tmpAngle];
		m_harmonicCos[i] = m_cosLookUp[tmpAngle];
		
		tmpTheta += aTheta;
	}
}

void AmbisonicRotate::setAzimuthInDegree(double aDegree)
{
    setAzimuth(aDegree / 360. * CICM_2PI);
}

void AmbisonicRotate::setVectorSize(long aVectorSize)
{
	m_vector_size = Tools::clip_power_of_two(aVectorSize);
}

AmbisonicRotate::~AmbisonicRotate()
{
	delete m_harmonicCos;
	delete m_harmonicSin;
	delete m_sinLookUp;
	delete m_cosLookUp;
	delete m_index_of_harmonics;
}
