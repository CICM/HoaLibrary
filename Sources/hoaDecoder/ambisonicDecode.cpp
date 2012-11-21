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

ambisonicDecode::ambisonicDecode(int anOrder,int aNumberOfChannels, int aVectorSize)
{
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_inputs		= m_number_of_harmonics;
	m_number_of_outputs		= aNumberOfChannels;
	
	if(m_number_of_outputs < m_number_of_harmonics)
		m_number_of_outputs = m_number_of_harmonics;
	
	m_input_vector		= gsl_vector_alloc (m_number_of_harmonics);
	m_output_vector		= gsl_vector_alloc (m_number_of_outputs);
	
	setVectorSize(aVectorSize);
	computeIndex();
	computeAngles();
	computePseudoInverse();
}

long ambisonicDecode::getOrder()
{
	return m_order;
}

long ambisonicDecode::getNumberOfHarmonics()
{
	return m_number_of_harmonics;
}

long ambisonicDecode::getNumberOfInputs()
{
	return m_number_of_inputs;
}

long ambisonicDecode::getNumberOfOutputs()
{
	return m_number_of_outputs;
}

long ambisonicDecode::getVectorSize()
{
	return m_vector_size;
}

void ambisonicDecode::computeIndex()
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

void ambisonicDecode::computeAngles()
{
	m_speakers_angles		= new double[m_number_of_outputs];
	for(int i = 0; i < m_number_of_outputs; i++)
	{
		m_speakers_angles[i] = (2. * M_PI / (double)m_number_of_outputs) * (double)i;
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
}

