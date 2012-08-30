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

#ifndef define DEF_AMBISONICENTRALIZE
#define DEF_AMBISONICENTRALIZE

#undef	check

#include "math.h"
#include <complex>
#include <stdio.h>
#include <vector>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

#define M_2PI 2*M_PI

class AmbisonicBinaural 
{
	
private:
	int			m_order;
	long		m_harmonics;
	long		m_response_size;
	long		m_vector_size;
	long		m_sampling_rate;
	
	gsl_matrix	*m_input_matrix;
	gsl_matrix	*m_impluse_response_matrix;
	
	gsl_matrix	*m_result_matrix;
	
	gsl_vector_view *m_result_vector_view_left;
	gsl_vector_view *m_result_vector_view_right;
	
	gsl_vector	*m_linear_vector_left;
	gsl_vector	*m_linear_vector_right;
	
	gsl_vector_view *m_linear_vector_view_left;
	gsl_vector_view *m_linear_vector_view_right;
	
	gsl_vector_view m_vectorSize_end_left;
	gsl_vector_view m_responseSize_begin_left;
	gsl_vector_view m_responseSize_end_left;
	
	gsl_vector_view m_vectorSize_end_right;
	gsl_vector_view m_responseSize_begin_right;
	gsl_vector_view m_responseSize_end_right;
	
	double		*m_result[2];
	float		*m_resultFloat[2];
	
public:
	
	AmbisonicBinaural(int aOrder, int aSamplingRate, int aVectorSize);
	void responseInit();
	void matrixInit(int aVectorSize);
	
	void	recordInputMatrix(double **aSample);
	void	recordInputMatrix(float	**aSample);
	double	**process(double **aSample);
	float	**process(float **aSample);
	~AmbisonicBinaural();
	
};

#endif