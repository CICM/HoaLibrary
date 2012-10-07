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


#include "ambisonicDigger.hpp"

ambisonicDigger::ambisonicDigger(int aNumberOfMicrophone, std::string anOptimMode, int aVectorSize)
{
	m_number_of_microphones = aNumberOfMicrophone;
	if(m_number_of_microphones % 2 == 0)
		m_order	= (m_number_of_microphones - 2) / 2;
	else
		m_order	= (m_number_of_microphones - 1) / 2;
	
	m_number_of_harmonics	= m_order * 2 + 1;
	m_optimVector		= new double[m_number_of_harmonics];
	
	m_encoder = new AmbisonicEncode(m_order, "split");
	m_encoder = new ambisonicDecode(m_order, m_number_of_microphones, "basic");
	m_weights = gsl_matrix_alloc(m_number_of_microphones, NUMBEROFCIRCLEPOINTS);
	
	setVectorSize(aVectorSize);
	computeIndex();
	setOptimMode(anOptimMode);
}

int	ambisonicDigger::getParameters(std::string aParameter) const
{
	int value = 0;
	
	if (aParameter == "order") 
		value = m_order;
	else if (aParameter == "samplingRate") 
		value =  m_sampling_rate;
	else if (aParameter == "vectorSize") 
		value =  m_vector_size;
	else if (aParameter == "numberOfHarmonics") 
		value =  m_number_of_harmonics;
	else if (aParameter == "numberOfInputs") 
		value =  m_number_of_harmonics;
	else if (aParameter == "numberOfOutputs") 
		value =  m_number_of_harmonics;
	
	return value;
}

void ambisonicDigger::computeIndex()
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

void ambisonicDigger::setOptimMode(std::string anOptim)
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

void ambisonicDigger::computeBasicOptim()
{
	m_optimMode = "basic"; 
	for (int i = 0; i < m_number_of_harmonics; i++) 
		m_optimVector[i] = 1.;
}

void ambisonicDigger::computeInPhaseOptim()
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

void ambisonicDigger::computeReOptim()
{
	m_optimMode = "maxRe";
	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		if (i == 0) 
			m_optimVector[i] = 1.;
		else 
			m_optimVector[i] = cos(abs(m_index_of_harmonics[i]) * M_PI / (2*m_order+2));
	}
	
}

void ambisonicDigger::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

ambisonicDigger::~ambisonicDigger()
{
	free(m_index_of_harmonics);
	free(m_optimVector);
}

