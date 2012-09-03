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

#include "ambisonicWeight.h"

ambisonicWeight::ambisonicWeight(int anOrder, int aSamplingRate, int aVectorSize, std::string anOptimMode)
{
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_outputs		= m_number_of_harmonics;
	m_number_of_inputs		= m_number_of_harmonics;
	m_sampling_rate			= aSamplingRate;
	m_vector_size			= aVectorSize;
	
	m_speakers_angles		= new double[m_order];
	m_index_of_harmonics	= new int[m_number_of_harmonics];
	m_optimVector			=  new double[m_number_of_harmonics];

	m_input_vector				= gsl_vector_alloc(m_number_of_harmonics * m_number_of_harmonics);
	m_input_vector_view			= new gsl_vector_view[m_number_of_harmonics];
	m_output_vector				= gsl_vector_alloc(m_number_of_harmonics * m_number_of_harmonics);
	m_output_vector_view		= new gsl_vector_view[m_number_of_harmonics];
	
	gsl_vector_set_zero(m_input_vector);
	gsl_vector_set_zero(m_output_vector);
	for (int j = 0; j < m_number_of_harmonics; j++)
	{
		m_input_vector_view[j]	= gsl_vector_subvector(m_input_vector, j * m_number_of_harmonics, m_number_of_harmonics);
		m_output_vector_view[j]	= gsl_vector_subvector(m_output_vector, j * m_number_of_harmonics, m_number_of_harmonics);
	}
	computeIndex();
	computeAngles();
	computePseudoInverse();
	setOptimMode(anOptimMode);
	

}

int	ambisonicWeight::getParameters(std::string aParameter) const
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

void ambisonicWeight::computeIndex()
{
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = floor((i - 1) / 2) + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void ambisonicWeight::computeAngles()
{
	for(int i = 0; i < m_number_of_harmonics; i++)
	{
		m_speakers_angles[i] = (2. * PI / (double)m_number_of_harmonics) * (double)i;
	}
}


void ambisonicWeight::setOptimMode(std::string anOptim)
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

void ambisonicWeight::computeBasicOptim()
{
	m_optimMode = "basic"; 
	for (int i = 0; i < m_number_of_harmonics; i++) 
		m_optimVector[i] = 1.;
}

void ambisonicWeight::computeReOptim()
{
	m_optimMode = "maxRe";
	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		if (i == 0) 
			m_optimVector[i] = 1.;
		else 
			m_optimVector[i] = cos(abs(m_index_of_harmonics[i]) * PI / (double)(2 * m_order + 2));
	}
}

void ambisonicWeight::computeInPhaseOptim()
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

void ambisonicWeight::computePseudoInverse()
{
	gsl_matrix* reencod_Mat = gsl_matrix_alloc(m_number_of_harmonics, m_number_of_harmonics); 
	//gsl_matrix* decode_Mat;
	//m_decoder_matrix		= gsl_matrix_alloc(m_number_of_harmonics * m_number_of_harmonics, m_number_of_harmonics);
	
	for (int i = 0; i < m_number_of_harmonics; i++)
	{
		for (int j = 0; j < m_number_of_harmonics; j++) 
		{
			if (m_index_of_harmonics[j] < 0)
				gsl_matrix_set(reencod_Mat,j,i,sin(abs(m_index_of_harmonics[j]) * m_speakers_angles[i]));
			else 
				gsl_matrix_set(reencod_Mat,j,i,cos(abs(m_index_of_harmonics[j]) * m_speakers_angles[i]));
		}
	}
	
	m_decoder_matrix = GenericSvdPseudoInverse(reencod_Mat);
	/*
	for (int i = 0; i < m_number_of_harmonics; i++)
	{
		for (int j = 0; j < m_number_of_harmonics; j++) 
		{
			for (int k = 0; k < m_number_of_harmonics; k++) 
			{
				gsl_matrix_set(m_decoder_matrix, j + i * m_number_of_harmonics, k , gsl_matrix_get(decode_Mat, j, k));
			}
		}
	}
	gsl_matrix_free(decode_Mat);
	 */
	gsl_matrix_free(reencod_Mat);
}

ambisonicWeight::~ambisonicWeight()
{
	gsl_matrix_free(m_decoder_matrix);
	gsl_vector_free(m_input_vector);
	gsl_vector_free(m_output_vector);
	delete m_input_vector_view;
	delete m_output_vector_view;
	delete m_index_of_harmonics;
	delete m_speakers_angles;
	delete m_optimVector;
}


