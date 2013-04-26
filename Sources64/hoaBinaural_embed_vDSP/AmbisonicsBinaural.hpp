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

#ifndef DEF_AMBISONICSBINAURAL
#define DEF_AMBISONICSBINAURAL

#include "../HoaAmbisonics/Ambisonics.h"
#include "../HoaDecoder/AmbisonicsDecoder.h"
#include "fileLoader.hpp"


class AmbisonicsBinaural : public Ambisonics
{
	
private:
	long		m_response_size;
	long		m_maximumNumberOfVirtualSpeakers;
	long		m_numberOfVirtualSpeakers;
	std::string m_optimMode;
    std::string m_hrtfRootPath;
    std::string m_pinnasize;
    std::string m_hrtfFullPath;
	long		m_number_of_inputs;
	long		m_number_of_outputs;
	bool		m_isHrtfLoaded;
	
	int*		m_harmonicsIndex;
	double*		m_optimVector;
	double*		m_angleListInDegree;
	double**	m_impulsesL;
	double**	m_impulsesR;
	
	AmbisonicsDecoder* m_decoder;

    Cicm_Signal_Vector_Float m_input_matrix_bloc;
    Cicm_Signal_Matrix_Float m_input_matrix;
    
    Cicm_Signal_Vector_Double m_input_matrix_bloc_double;
    Cicm_Signal_Matrix_Double m_input_matrix_double;
	//gsl_matrix	*m_input_matrix;
    
    Cicm_Signal_Vector_Float m_impluse_response_matrix_bloc;
    Cicm_Signal_Matrix_Float m_impluse_response_matrix;
	//gsl_matrix	*m_impluse_response_matrix;
	
    Cicm_Signal_Vector_Float m_result_matrix_bloc;
    Cicm_Signal_Matrix_Float m_result_matrix;
	//gsl_matrix	*m_result_matrix;
	
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
	
	AmbisonicsBinaural(int aOrder, double aSamplingRate, int aVectorSizen, std::string hrtfRootPath = "", std::string pinnaSize = "Small");
	void	computeNbOfVirtualSpeaker();
	int		getParameters(std::string aParameter) const;
	bool	getisHrtfLoaded() {return m_isHrtfLoaded;}
    
    std::string	getHrtfPath() {return m_hrtfFullPath;}
    
	bool	formatHrtfFilePath(std::string hrtfRootPath, int aSamplingRate, std::string pinnaSize);
    
	void	setOptimMode(std::string anOptim);
    void    setPinnaSize(std::string pinnaSize);
    void    setSamplingRate(int aSamplingRate);
	void	computeBasicOptim();
	void	computeInPhaseOptim();
	void	computeReOptim();
	
    void    setVectorSizeAndSamplingRate(int aVectorSize, double aSamplingRate);
	void	loadImpulses();
	void	responseInit();
	void	printBasis(double *basisArray, int size);
	void	matrixResize(int aVectorSize, std::string aMode = "resize");
	std::string intToString(int aValue);
	
	void free();
	~AmbisonicsBinaural();
	
	/* Perform Method */
	inline void process(double** aInputs, double** aOutputs)
	{	
		/* Record Inputs vectors In The Matrix */
		for (int i = 0; i < m_number_of_harmonics; i++)
		{
            Cicm_Signal_Vector_Matrix_Double_Copy(aInputs[i], m_input_matrix_double, i, m_vector_size);
		}
		
		/* Matricial Multiplication */
		//gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1., m_impluse_response_matrix, m_input_matrix, 0., m_result_matrix);
		
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