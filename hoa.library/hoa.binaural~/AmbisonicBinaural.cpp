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

AmbisonicBinaural::AmbisonicBinaural(int aOrder, int aVectorSize)
{	
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
}

void AmbisonicBinaural::responseInit()
{
	gsl_matrix* m_respo_matrix = gsl_matrix_calloc(m_response_size, m_harmonics);
}

void AmbisonicBinaural::matrixInit(int aVectorSize)
{
	if(aVectorSize != m_vector_size)
	{		
		m_vector_size = aVectorSize;
		
		gsl_matrix_free(m_input_matrix);
		gsl_matrix_free(m_outnew_matrix);
		gsl_matrix_free(m_outold_matrix);
	
		
		gsl_matrix* m_input_matrix = gsl_matrix_calloc(m_harmonics, m_vector_size);
		gsl_matrix* m_outnew_matrix = gsl_matrix_calloc(m_response_size, m_vector_size);
		gsl_matrix* m_outold_matrix = gsl_matrix_calloc(m_response_size, m_vector_size);
	}
}

double *AmbisonicBinaural::process(double* aSample)
{	
	double result;
	return &result;
}

AmbisonicBinaural::~AmbisonicBinaural()
{
	gsl_matrix_free(m_input_matrix);
	gsl_matrix_free(m_respo_matrix);
	gsl_matrix_free(m_outnew_matrix);
	gsl_matrix_free(m_outold_matrix);
}