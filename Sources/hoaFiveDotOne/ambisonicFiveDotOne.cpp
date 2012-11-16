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

#include "ambisonicFiveDotOne.h"

ambisonicFiveDotOne::ambisonicFiveDotOne(int anOrder, double anAngle1, double anAngle2, int aVectorSize)
{
	m_order					= anOrder;
	m_number_of_harmonics	= m_order * 2 + 1;
	m_number_of_outputs		= 6;
	m_number_of_inputs		= m_number_of_harmonics;

	m_angle2 = anAngle2;
	if(m_angle2 < 0.)
		m_angle2 = 0.;
	else if(m_angle2 > 180.)
		m_angle2 = 0.;

	m_angle1	= anAngle1;
	if(m_angle1 < 0.)
		m_angle1 = 0.;
	else if(m_angle1 > m_angle2)
		m_angle1 = m_angle2;

	m_output_vector_front	= gsl_vector_alloc (3);
	m_output_vector_surround= gsl_vector_alloc (2);

	m_input_vector_front	= gsl_vector_alloc (m_number_of_harmonics);
	m_input_vector_surround	= gsl_vector_alloc (3);
	m_optim_vector	= gsl_vector_alloc (m_number_of_harmonics);
	computeIndex();
	computeMicrophones();
	computeInPhaseOptim();
	
	for(int j = 0; j < m_number_of_harmonics; j++)
	{
		if(j % 2 == 1)
			gsl_vector_set(m_input_vector_front, j, 0.);
		else
			gsl_vector_set(m_input_vector_front, j, 1.);
	}
	
	gsl_vector_mul(m_input_vector_front, m_optim_vector);
	gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix_front, m_input_vector_front, 0.0, m_output_vector_front);
	
	m_scale_factor_front = 1. / gsl_vector_get(m_output_vector_front, 0.);
	
	double optim1 = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[1])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[1])));
	double optim2 = pow(gsl_sf_fact(m_order), 2) / ( gsl_sf_fact(m_order+abs(m_index_of_harmonics[2])) * gsl_sf_fact(m_order-abs(m_index_of_harmonics[2])));
	
	gsl_vector_set(m_input_vector_surround, 0, 1.);
	gsl_vector_set(m_input_vector_surround, 1, sin(m_angle2) * optim1 * 2. / 3.);
	gsl_vector_set(m_input_vector_surround, 2, cos(m_angle2) * optim2 * 2. / 3.);
	gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix_surround, m_input_vector_surround, 0.0, m_output_vector_surround);
	
	m_scale_factor_surround = 1. / gsl_vector_get(m_output_vector_surround, 0.);

	m_last_sample = 0.;
	setVectorSize(aVectorSize);
}

int	ambisonicFiveDotOne::getParameters(std::string aParameter) const
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

void ambisonicFiveDotOne::computeIndex()
{
	m_index_of_harmonics	= new int[m_number_of_harmonics];
	m_index_of_harmonics[0] = 0;
	for(int i = 1; i < m_number_of_harmonics; i++)
	{
		m_index_of_harmonics[i] = (i - 1) / 2 + 1;
		if (i % 2 == 1) 
			m_index_of_harmonics[i] = - m_index_of_harmonics[i];
	}
}

void ambisonicFiveDotOne::computeInPhaseOptim()
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

void ambisonicFiveDotOne::computeMicrophones()
{
	m_microphones_matrix_front = gsl_matrix_alloc(m_number_of_harmonics, 3); 
	m_microphones_matrix_surround = gsl_matrix_alloc(3, 2); 
	double aThetaLeft, aThetaRight, aThetaLeftSurround, aThetaRightSurround;
	int aIndex;
	
	aThetaLeft = (m_angle1 / 360.) * TWOPI;
	aThetaRight = TWOPI - aThetaLeft;
	for (int j = 0; j < m_number_of_harmonics; j++) 
	{
		aIndex = (int)((((double)j - 1.) / 2.) + 1.);
		if (j % 2 == 1)
			aIndex = -aIndex;
			
		if (aIndex < 0)
		{
			gsl_matrix_set(m_microphones_matrix_front, j, 0,sin(0.));
			gsl_matrix_set(m_microphones_matrix_front, j, 1,sin((double)abs(aIndex) * aThetaLeft));
			gsl_matrix_set(m_microphones_matrix_front, j, 2,sin((double)abs(aIndex) * aThetaRight));
		}
		else
		{
			gsl_matrix_set(m_microphones_matrix_front, j, 0,cos(0.));
			gsl_matrix_set(m_microphones_matrix_front, j, 1,cos((double)abs(aIndex) * aThetaLeft));
			gsl_matrix_set(m_microphones_matrix_front, j, 2,cos((double)abs(aIndex) * aThetaRight));
		}
	}
	aThetaLeftSurround = (m_angle2 / 360.) * TWOPI;
	aThetaRightSurround = TWOPI - aThetaLeftSurround;
	for (int j = 0; j < 3; j++) 
	{
		aIndex = (int)((((double)j - 1.) / 2.) + 1.);
		if (j % 2 == 1)
			aIndex = -aIndex;
			
		if (aIndex < 0)
		{
			gsl_matrix_set(m_microphones_matrix_surround, j, 0,sin((double)abs(aIndex) * aThetaLeftSurround));
			gsl_matrix_set(m_microphones_matrix_surround, j, 1,sin((double)abs(aIndex) * aThetaRightSurround));
		}
		else
		{
			gsl_matrix_set(m_microphones_matrix_surround, j, 0,cos((double)abs(aIndex) * aThetaLeftSurround));
			gsl_matrix_set(m_microphones_matrix_surround, j, 1,cos((double)abs(aIndex) * aThetaRightSurround));
		}
	}
}

void ambisonicFiveDotOne::setVectorSize(int aVectorSize)
{
	m_vector_size = aVectorSize;
}

ambisonicFiveDotOne::~ambisonicFiveDotOne()
{
	gsl_matrix_free(m_microphones_matrix_front);
	gsl_matrix_free(m_microphones_matrix_surround);
	gsl_vector_free(m_input_vector_front);
	gsl_vector_free(m_input_vector_surround);
	gsl_vector_free(m_output_vector_front);
	gsl_vector_free(m_output_vector_surround);
	delete m_index_of_harmonics;
}

