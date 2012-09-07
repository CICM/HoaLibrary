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

#include "ambisonicRecomposer.h"

ambisonicRecomposer::ambisonicRecomposer(int anOrder, int aNumberOfChannels, int aVectorSize)
{
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= aNumberOfChannels;
	m_number_of_outputs		= m_number_of_harmonics;
	
	m_fishEyeFactor			= 1.;
	
	m_input_vector			= gsl_vector_alloc(m_number_of_inputs);
	m_output_vector			= gsl_vector_alloc(m_number_of_outputs);
	
	m_recompMicCoefs		= gsl_matrix_alloc(m_number_of_inputs, m_number_of_outputs);
	m_recompMicCoefsSet		= new gsl_matrix*[NUMBEROFCIRCLEPOINTS];
	
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
		m_recompMicCoefsSet[i] = gsl_matrix_alloc(m_number_of_inputs, m_number_of_outputs);
	
	computeIndex();
	computeAngles();
	computeMicMatrixSet();
	setVectorSize(aVectorSize);

}

int	ambisonicRecomposer::getParameters(std::string aParameter) const
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

void ambisonicRecomposer::computeIndex()
{
	m_index_of_harmonics	= new int[m_number_of_harmonics ];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = floor((i - 1) / 2) + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void ambisonicRecomposer::computeAngles()
{
	m_speakers_angles		= new double[m_number_of_outputs];
	for(int i = 0; i < m_number_of_outputs; i++)
	{
		m_speakers_angles[i] = (2. * PI / (double)m_number_of_outputs) * (double)i;
		if(m_speakers_angles[i] > PI)
			m_speakers_angles[i] -= 2. * PI;
	}
}

void ambisonicRecomposer::computeMicMatrix(gsl_matrix* resMatrix, double aFishFactor)
{
	for (int micIndex = 0; micIndex < m_number_of_outputs; micIndex++)
	{
		gsl_matrix_set(resMatrix, micIndex, 0, 1);
		for (int orderIndex = 1; orderIndex <= m_order; orderIndex++) 
		{
			gsl_matrix_set(resMatrix, micIndex, orderIndex * 2 -1, sin(orderIndex * m_speakers_angles[micIndex] * aFishFactor));
			gsl_matrix_set(resMatrix, micIndex, orderIndex * 2   , cos(orderIndex * m_speakers_angles[micIndex] * aFishFactor));
		}
	}
}

void ambisonicRecomposer::computeMicMatrixSet()
{
	double tmpFishEyeFactor;
	for (int matIndex = 0; matIndex < NUMBEROFCIRCLEPOINTS; matIndex++) 
	{
		tmpFishEyeFactor = (float)matIndex/float(NUMBEROFCIRCLEPOINTS-1);
		computeMicMatrix(m_recompMicCoefsSet[matIndex], tmpFishEyeFactor);
	}
}

void ambisonicRecomposer::setVectorSize(int aVectorSize)
{
		m_vector_size	= aVectorSize;	
}

void ambisonicRecomposer::setFishEyeFactor(double aFishEyeFactor)
{
	if (aFishEyeFactor > 1.) 
		aFishEyeFactor = 1.;
	else if (aFishEyeFactor < 0.)
		aFishEyeFactor = 0.;
	m_fishEyeFactor = aFishEyeFactor;	
}

ambisonicRecomposer::~ambisonicRecomposer()
{
	gsl_matrix_free(m_recompMicCoefs);
	for (int i = 0; i < NUMBEROFCIRCLEPOINTS; i++)
		gsl_matrix_free(m_recompMicCoefsSet[i]);
	delete[] m_recompMicCoefsSet;
	
	gsl_vector_free(m_output_vector);
	gsl_vector_free(m_input_vector);
	delete[] m_speakers_angles;
	delete[] m_index_of_harmonics;
}



