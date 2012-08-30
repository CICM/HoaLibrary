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
	m_impluse_response_matrix = gsl_matrix_calloc(m_response_size * 2, m_harmonics);
}

void AmbisonicBinaural::matrixInit(int aVectorSize)
{
	if(aVectorSize != m_vector_size)
	{		
		m_vector_size = aVectorSize;
		
		gsl_matrix_free(m_input_matrix);
		gsl_matrix_free(m_result_matrix);	
		
		m_input_matrix = gsl_matrix_calloc(m_harmonics, m_vector_size);
		m_result_matrix = gsl_matrix_calloc(m_response_size * 2, m_vector_size);
		
		gsl_vector_free(m_linear_vector_left);
		gsl_vector_free(m_linear_vector_right);
		
		m_linear_vector_left = gsl_vector_calloc(m_vector_size + m_response_size - 1);
		m_linear_vector_right = gsl_vector_calloc(m_vector_size + m_response_size - 1);
		
		delete m_result_vector_view_left;
		delete m_result_vector_view_right;
		delete m_linear_vector_view_left;
		delete m_linear_vector_view_right;
		
		m_result_vector_view_left = new gsl_vector_view[m_vector_size];
		m_result_vector_view_right = new gsl_vector_view[m_vector_size];
		m_linear_vector_view_left = new gsl_vector_view[m_vector_size];
		m_linear_vector_view_right = new gsl_vector_view[m_vector_size];
		
		for (int j = 0; j < m_vector_size; j++)
		{
			m_result_vector_view_left[j]	= gsl_vector_subvector(&(gsl_matrix_column(m_result_matrix, j)).vector, 0, 200);
			m_result_vector_view_right[j]	= gsl_vector_subvector(&(gsl_matrix_column(m_result_matrix, j)).vector, 200, 200);

			m_linear_vector_view_left[j]	= gsl_vector_subvector(m_linear_vector_left, j, 200);
			m_linear_vector_view_right[j]	= gsl_vector_subvector(m_linear_vector_right, j, 200);
		}
		
		m_vectorSize_end_left = gsl_vector_subvector(m_linear_vector_left, m_response_size - 1, m_vector_size);
		m_responseSize_begin_left = gsl_vector_subvector(m_linear_vector_left, 0, m_response_size - 1);
		m_responseSize_end_left = gsl_vector_subvector(m_linear_vector_left, m_vector_size, m_response_size - 1);
		
		m_vectorSize_end_right = gsl_vector_subvector(m_linear_vector_right, m_response_size - 1, m_vector_size);
		m_responseSize_begin_right = gsl_vector_subvector(m_linear_vector_right, 0, m_response_size - 1);
		m_responseSize_end_right = gsl_vector_subvector(m_linear_vector_right, m_vector_size, m_response_size - 1);
		
		delete m_result[0];
		delete m_result[1];
		
		m_result[0] = new double[m_vector_size];
		m_result[1] = new double[m_vector_size];
	}
}

void AmbisonicBinaural::recordInputMatrix(double **aSample)
{
	for (int i = 0; i < m_harmonics; i++)
	{
		for (int j = 0; j < m_vector_size; j++)
		{
			gsl_matrix_set(m_input_matrix, i, j, aSample[i][j]);
		}
	}
}

void AmbisonicBinaural::recordInputMatrix(float **aSample)
{
	for (int i = 0; i < m_harmonics; i++)
	{
		for (int j = 0; j < m_vector_size; j++)
		{
			gsl_matrix_set(m_input_matrix, i, j, (double)aSample[i][j]);
		}
	}
}

double **AmbisonicBinaural::process(float **aSample)
{	
	recordInputMatrix(aSample);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1., m_impluse_response_matrix, m_input_matrix, 1., m_result_matrix);
	
	for (int j = 0; j < m_vector_size; j++)
	{
		gsl_blas_daxpy(1., &m_result_vector_view_left[j].vector, &m_linear_vector_view_left[j].vector);
		gsl_blas_daxpy(1., &m_result_vector_view_right[j].vector, &m_linear_vector_view_right[j].vector);
		m_result[0][j] = gsl_vector_get(m_linear_vector_left, j);
		m_result[1][j] = gsl_vector_get(m_linear_vector_right, j);
	}
	gsl_blas_dcopy(&m_responseSize_end_left.vector, &m_responseSize_begin_left.vector);
	gsl_blas_dcopy(&m_responseSize_end_right.vector, &m_responseSize_begin_right.vector);
	gsl_vector_set_zero(&m_vectorSize_end_left.vector);
	gsl_vector_set_zero(&m_vectorSize_end_right.vector);
	
	return m_result;
}

double **AmbisonicBinaural::process(double **aSample)
{	
	recordInputMatrix(aSample);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1., m_impluse_response_matrix, m_input_matrix, 1., m_result_matrix);
	
	for (int j = 0; j < m_vector_size; j++)
	{
		gsl_blas_daxpy(1., &m_result_vector_view_left[j].vector, &m_linear_vector_view_left[j].vector);
		gsl_blas_daxpy(1., &m_result_vector_view_right[j].vector, &m_linear_vector_view_right[j].vector);
		m_result[0][j] = gsl_vector_get(m_linear_vector_left, j);
		m_result[1][j] = gsl_vector_get(m_linear_vector_right, j);
	}
	gsl_blas_dcopy(&m_responseSize_end_left.vector, &m_responseSize_begin_left.vector);
	gsl_blas_dcopy(&m_responseSize_end_right.vector, &m_responseSize_begin_right.vector);
	gsl_vector_set_zero(&m_vectorSize_end_left.vector);
	gsl_vector_set_zero(&m_vectorSize_end_right.vector);
	
	return m_result;
}

AmbisonicBinaural::~AmbisonicBinaural()
{
	gsl_matrix_free(m_input_matrix);
	gsl_matrix_free(m_impluse_response_matrix);
	gsl_matrix_free(m_result_matrix);
	
	gsl_vector_free(m_linear_vector_left);
	gsl_vector_free(m_linear_vector_right);

	delete m_result_vector_view_left;
	delete m_result_vector_view_right;
	delete m_linear_vector_view_left;
	delete m_linear_vector_view_right;
	
	delete m_result[0];
	delete m_result[1];
}