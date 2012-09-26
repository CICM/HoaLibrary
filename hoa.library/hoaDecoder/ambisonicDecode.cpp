/*
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


#include "ambisonicDecode.hpp"

ambisonicDecode::ambisonicDecode(int anOrder,int aNumberOfChannels, int aVectorSize, std::string anOptimMode)
{
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= aNumberOfChannels;
	
	if(m_number_of_outputs < m_number_of_harmonics)
		m_number_of_outputs = m_number_of_harmonics;
	
	m_input_vector		= gsl_vector_alloc (m_number_of_harmonics);
	m_output_vector		= gsl_vector_alloc (m_number_of_outputs);
	m_optimVector		= new double[m_number_of_harmonics];
	
	setVectorSize(aVectorSize);
	computeIndex();
	computeAngles();
	setOptimMode(anOptimMode);
	computePseudoInverse();
}

int	ambisonicDecode::getParameters(std::string aParameter) const
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

void ambisonicDecode::computeIndex()
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

void ambisonicDecode::computeAngles()
{
	m_speakers_angles		= new double[m_number_of_outputs];
	for(int i = 0; i < m_number_of_outputs; i++)
	{
		m_speakers_angles[i] = (2. * PI / (double)m_number_of_outputs) * (double)i;
	}
}

void ambisonicDecode::setOptimMode(std::string anOptim)
{
	if(anOptim != m_optimMode)
	{
		if(anOptim == "inPhase")
			computeInPhaseOptim();
		else if(anOptim == "maxRe")
			computeReOptim();
		else
			computeBasicOptim();
	}
}

void ambisonicDecode::computeBasicOptim()
{
	m_optimMode = "basic"; 
	for (int i = 0; i < m_number_of_harmonics; i++) 
		m_optimVector[i] = 1.;
}

void ambisonicDecode::computeInPhaseOptim()
{
	m_optimMode = "inPhase"; 
	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		if (i == 0) 
			m_optimVector[i] = 1.;
		else 
			m_optimVector[i] = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[i])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[i])));
	}
}

void ambisonicDecode::computeReOptim()
{
	m_optimMode = "maxRe";
	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		if (i == 0) 
			m_optimVector[i] = 1.;
		else 
			m_optimVector[i] = cos(abs(m_index_of_harmonics[i]) * PI / (2*m_order+2));
	}
	
}


void ambisonicDecode::computePseudoInverse()
{
	gsl_matrix* reencod_Mat = gsl_matrix_alloc(m_number_of_harmonics, m_number_of_outputs); 
	
	for (int i = 0; i < m_number_of_outputs; i++)
	{
		for (int j = 0; j < m_number_of_harmonics ; j++) 
		{
			if (m_index_of_harmonics[j] < 0)
				gsl_matrix_set(reencod_Mat,j,i,sin(abs(m_index_of_harmonics[j]) * m_speakers_angles[i]));
			else 
				gsl_matrix_set(reencod_Mat,j,i,cos(abs(m_index_of_harmonics[j]) * m_speakers_angles[i]));
		}
	}
	m_decoder_matrix = GenericSvdPseudoInverse(reencod_Mat);
	gsl_matrix_free(reencod_Mat);
}

void ambisonicDecode::setSpkrsAngles(double* someSpkrsAngles, int size)
{
	if (size > m_number_of_outputs) 
		size = m_number_of_outputs;
	
	memcpy(m_speakers_angles, someSpkrsAngles, sizeof(double)*size);
	computePseudoInverse();
}

void ambisonicDecode::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

ambisonicDecode::~ambisonicDecode()
{
	gsl_matrix_free(m_decoder_matrix);
	delete m_output_vector;
	delete m_index_of_harmonics;
	delete m_speakers_angles;
	delete m_optimVector;
}

