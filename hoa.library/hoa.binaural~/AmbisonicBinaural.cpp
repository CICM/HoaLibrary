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

#include "AmbisonicBinaural.h"

AmbisonicBinaural::AmbisonicBinaural(int aOrder, int aSamplingRate, int aVectorSize)
{	
	m_vector_size = 0;
	m_sampling_rate = 0;
	m_order = aOrder;
	
	if(m_order < 8)
		m_order = 4;
	else if(m_order < 17 && m_order >= 8)
		m_order = 8;
	else if(m_order < 35 && m_order >= 17)
		m_order = 17;
	else
		m_order = 35;
	
	m_harmonics = 2 * m_order + 1;
	m_response_size = 200;
	
	responseInit();
	matrixInit(aVectorSize);
}

void AmbisonicBinaural::responseInit()
{
	gsl_matrix	*m_impluse_response_matrix = gsl_matrix_calloc(m_response_size * 2, m_harmonics);
}

void AmbisonicBinaural::matrixInit(int aVectorSize)
{
	if(aVectorSize != m_vector_size)
	{		
		m_vector_size = aVectorSize;
		
		gsl_matrix_free(m_input_matrix);
		gsl_matrix_free(m_result_matrix);	
		
		gsl_matrix	*m_input_matrix = gsl_matrix_calloc(m_harmonics, m_vector_size);
		gsl_matrix	*m_result_matrix = gsl_matrix_calloc(m_response_size * 2, m_vector_size);
	}
}

void AmbisonicBinaural::recordInputMatrix(double **aSample)
{
	for (int j = 0; j < m_harmonics; j++)
	{
		for (int i = 0; i < m_vector_size; i++)
		{
			gsl_matrix_set(m_input_matrix, j, i, aSample[j][i]);
		}
	}
}

void AmbisonicBinaural::recordInputMatrix(float **aSample)
{
	for (int j = 0; j < m_harmonics; j++)
	{
		for (int i = 0; i < m_vector_size; i++)
		{
			gsl_matrix_set(m_input_matrix, j, i, (double)aSample[j][i]);
		}
	}
}

double *AmbisonicBinaural::process(float **aSample)
{	
	recordInputMatrix(aSample);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1., m_impluse_response_matrix, m_input_matrix, 1., m_result_matrix);
	
	return m_result;
}

double *AmbisonicBinaural::process(double **aSample)
{	
	recordInputMatrix(aSample);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1., m_impluse_response_matrix, m_input_matrix, 1., m_result_matrix);
	
	return m_result;
}

AmbisonicBinaural::~AmbisonicBinaural()
{
	gsl_matrix_free(m_input_matrix);
	gsl_matrix_free(m_impluse_response_matrix);
	gsl_matrix_free(m_result_matrix);
}