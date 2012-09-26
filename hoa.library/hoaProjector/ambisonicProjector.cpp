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

#include "ambisonicProjector.h"

ambisonicProjector::ambisonicProjector(int anOrder, int aNumberOfMicrophones, int aVectorSize, std::string anOptimMode)
{
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_outputs		= aNumberOfMicrophones;
	m_number_of_inputs		= m_number_of_harmonics;
	
	m_output_vector	= gsl_vector_alloc (m_number_of_outputs);
	m_input_vector	= gsl_vector_alloc (m_number_of_harmonics);
	m_optimVector   = new double[m_number_of_harmonics];

	computeIndex();
	computeMicrophones();
	setVectorSize(aVectorSize);
	setOptimMode(anOptimMode);
}

int	ambisonicProjector::getParameters(std::string aParameter) const
{
	int value = 0;
	
	if (aParameter == "order") 
		value = m_order;
	else if (aParameter == "numberOfInputs") 
		value =  m_number_of_inputs;
	else if (aParameter == "numberOfOutputs") 
		value =  m_number_of_outputs;
	
	return value;
}

void ambisonicProjector::computeIndex()
{
	m_index_of_harmonics	= new int[m_number_of_harmonics ];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = (i - 1) / 2 + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void ambisonicProjector::computeMicrophones()
{
	m_microphones_matrix = gsl_matrix_alloc(m_number_of_harmonics, m_number_of_outputs); 
	double aTheta;
	int aIndex;
	
	for (int i = 0; i < m_number_of_outputs; i++)
	{
		aTheta = ((double)i / (double)m_number_of_outputs) * PI * 2.;
		for (int j = 0; j < m_number_of_harmonics; j++) 
		{
			aIndex = (int)((((double)j - 1.) / 2.) + 1.);
			if (j % 2 == 1)
				aIndex = -aIndex;
			
			if (aIndex < 0)
				gsl_matrix_set(m_microphones_matrix, j, i,sin((double)abs(aIndex) * aTheta));
			else 
				gsl_matrix_set(m_microphones_matrix, j, i,cos((double)abs(aIndex) * aTheta));
		}
	}
}


void ambisonicProjector::setOptimMode(std::string anOptim)
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

void ambisonicProjector::computeBasicOptim()
{
	m_optimMode = "basic"; 
	for (int i = 0; i < m_number_of_harmonics; i++) 
		m_optimVector[i] = 1.;
	m_optimVector[0] /= 2. * (double)(m_order + 1);
	for(int i = 1; i < m_number_of_harmonics; i++)
		m_optimVector[i] /= (double)(m_order + 1);
}

void ambisonicProjector::computeInPhaseOptim()
{
	m_optimMode = "inPhase"; 
	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		if (i == 0) 
			m_optimVector[i] = 1.;
		else 
			m_optimVector[i] = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[i])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[i])));
	}
	m_optimVector[0] /= 2. * (double)(m_order + 1);
	for(int i = 1; i < m_number_of_harmonics; i++)
		m_optimVector[i] /= (double)(m_order + 1);
}

void ambisonicProjector::computeReOptim()
{
	m_optimMode = "maxRe";
	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		if (i == 0) 
			m_optimVector[i] = 1.;
		else 
			m_optimVector[i] = cos(abs(m_index_of_harmonics[i]) * PI / (2*m_order+2));
	}
	m_optimVector[0] /= 2. * (double)(m_order + 1);
	for(int i = 1; i < m_number_of_harmonics; i++)
		m_optimVector[i] /= (double)(m_order + 1);
	
}

void ambisonicProjector::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

ambisonicProjector::~ambisonicProjector()
{
	gsl_matrix_free(m_microphones_matrix);
	gsl_vector_free(m_input_vector);
	gsl_vector_free(m_output_vector);
	delete m_optimVector;
	delete m_index_of_harmonics;
	delete m_optimVector;
}

