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

#include "ambisonicStereo.h"

ambisonicStereo::ambisonicStereo(int anOrder, double anAngle, int aVectorSize)
{
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_outputs		= 2;
	m_number_of_inputs		= m_number_of_harmonics;
	m_angle					= anAngle;
	if(m_angle < 0.)
		m_angle = 0.;
	else if(m_angle > 360.)
		m_angle = 0.;

	m_output_vector	= gsl_vector_alloc (m_number_of_outputs);
	m_input_vector	= gsl_vector_alloc (m_number_of_harmonics);
	m_optim_vector	= gsl_vector_alloc (m_number_of_harmonics);
	computeIndex();
	computeMicrophones();
	computeInPhaseOptim();

	
	AmbisonicEncode* encoder = new AmbisonicEncode(m_order);
	double* result = new double[m_number_of_harmonics];
	encoder->process(1., result, ((m_angle / 360.) * TWOPI));
	for(int j = 0; j < m_number_of_harmonics; j++)
	{
			gsl_vector_set(m_input_vector, j, result[j]);
	}
	gsl_vector_mul(m_input_vector, m_optim_vector);
	gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix, m_input_vector, 0.0, m_output_vector);
	m_scale_factor = 1. / gsl_vector_get(m_output_vector, 0.);
	free(result);
	delete encoder;
	setVectorSize(aVectorSize);
}

int	ambisonicStereo::getParameters(std::string aParameter) const
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

void ambisonicStereo::computeIndex()
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

void ambisonicStereo::computeInPhaseOptim()
{
	for (int i = 0; i < m_number_of_harmonics; i++) 
	{
		double optim = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[i])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[i])));
		if (i == 0) 
			gsl_vector_set(m_optim_vector, i, 1.);
		else 
			gsl_vector_set(m_optim_vector, i, optim);
	}
}

void ambisonicStereo::computeMicrophones()
{
	m_microphones_matrix = gsl_matrix_alloc(m_number_of_harmonics, m_number_of_outputs); 
	double aThetaLeft, aThetaRight;
	int aIndex;
	
	aThetaLeft = (m_angle / 360.) * TWOPI;
	aThetaRight = TWOPI - aThetaLeft;
	for (int j = 0; j < m_number_of_harmonics; j++) 
	{
		aIndex = (int)((((double)j - 1.) / 2.) + 1.);
		if (j % 2 == 1)
			aIndex = -aIndex;
			
		if (aIndex < 0)
		{
			gsl_matrix_set(m_microphones_matrix, j, 0,sin((double)abs(aIndex) * aThetaLeft));
			gsl_matrix_set(m_microphones_matrix, j, 1,sin((double)abs(aIndex) * aThetaRight));
		}
		else
		{
			gsl_matrix_set(m_microphones_matrix, j, 0,cos((double)abs(aIndex) * aThetaLeft));
			gsl_matrix_set(m_microphones_matrix, j, 1,cos((double)abs(aIndex) * aThetaRight));
		}
	}
}

void ambisonicStereo::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

ambisonicStereo::~ambisonicStereo()
{
	gsl_matrix_free(m_microphones_matrix);
	gsl_vector_free(m_input_vector);
	gsl_vector_free(m_output_vector);
	delete m_index_of_harmonics;
}

