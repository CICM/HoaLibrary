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

//#define gsl_vector gsl_vector_float
//#define gsl_vector_view gsl_vector_float_view
//#define gsl_vector_get gsl_vector_float_get
//#define gsl_vector_subvector gsl_vector_float_subvector
//
//
//#define gsl_matrix gsl_matrix_float
//#define gsl_blas_dgemm gsl_blas_sgemm
//#define gsl_blas_dcopy gsl_blas_scopy
//#define gsl_blas_daxpy gsl_blas_saxpy
//#define gsl_matrix_set gsl_matrix_float_set
//#define gsl_matrix_column gsl_matrix_float_column


#include "math.h"
#include <complex>
#include <stdio.h>
#include <vector>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include "fileLoader.h"
#include <sstream>
#include <ambisonicDecode.h> 
#include <mkl_service.h>



#define M_2PI 2*M_PI

class AmbisonicBinaural 
{
	
private:
	int			m_order;
	long		m_numberOfHarmonics;
	long		m_response_size;
	long		m_vector_size;
	long		m_sampling_rate;
	long		m_maximumNumberOfVirtualSpeakers;
	long		m_numberOfVirtualSpeakers;
	std::string m_optimMode;
	std::string m_preFilePath;
	long		m_number_of_inputs;
	long		m_number_of_outputs;
	bool		m_isHrtfLoaded;
	
	int*		m_harmonicsIndex;
	double*		m_optimVector;
	double*		m_angleListInDegree;
	double**	m_impulsesL;
	double**	m_impulsesR;
	
	ambisonicDecode* m_decoder;

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
	
public:
	
	AmbisonicBinaural(int aOrder, int aSamplingRate, int aVectorSizen, std::string anOptimMode = "basic" , std::string pinnaSize = "small");
	void	computeNbOfVirtualSpeaker();
	int		getParameters(std::string aParameter) const;
	bool	getisHrtfLoaded() {return m_isHrtfLoaded;}
	
	void	setOptimMode(std::string anOptim);
	void	computeBasicOptim();
	void	computeInPhaseOptim();
	void	computeReOptim();
	
	void	loadImpulses();
	void	responseInit();
	void	printBasis(double *basisArray, int size);
	void matrixResize(int aVectorSize, std::string aMode = "resize");
	std::string intToString(int aValue);
	
	void free();
	~AmbisonicBinaural();
	
	/* Perform Method */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{	
		/* Record Inputs vectors In The Matrix */
		for (int i = 0; i < m_numberOfHarmonics; i++)
		{
			for (int j = 0; j < m_vector_size; j++)
			{
				gsl_matrix_set(m_input_matrix, i, j, aInputs[i][j] * m_optimVector[i]);
			}
		}
		
		/* Matricial Multiplication */
		gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1., m_impluse_response_matrix, m_input_matrix, 0., m_result_matrix);
		
		/* Write On The Tempory Vectors And The Outputs Vectors */
		for (int j = 0; j < m_vector_size; j++)
		{
			gsl_blas_daxpy(1., &m_result_vector_view_left[j].vector, &m_linear_vector_view_left[j].vector);
			gsl_blas_daxpy(1., &m_result_vector_view_right[j].vector, &m_linear_vector_view_right[j].vector);
			aOutputs[0][j] = gsl_vector_get(m_linear_vector_left, j);
			aOutputs[1][j] = gsl_vector_get(m_linear_vector_right, j);
		}
	
		/* Reorder The Tempory Vectors */
		gsl_blas_dcopy(&m_responseSize_end_left.vector, &m_responseSize_begin_left.vector);
		gsl_blas_dcopy(&m_responseSize_end_right.vector, &m_responseSize_begin_right.vector);
		gsl_vector_set_zero(&m_vectorSize_end_left.vector);
		gsl_vector_set_zero(&m_vectorSize_end_right.vector);
	}

};

#endif