/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris Universite Paris 8
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

#ifndef DEF_AMBISONICFIVEDOTONE
#define DEF_AMBISONICFIVEDOTONE

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>
#include "AmbisonicEncode.hpp"
#include "cicmTools.h"

class AmbisonicFiveDotOne
{
	
private:
	long		m_order;
	long		m_number_of_harmonics;
	long		m_number_of_outputs;
	long		m_number_of_inputs;
	long		m_vector_size;
	
	double		m_delta_front;
	double		m_delta_surround;

	double		m_angle_center;
	double		m_angle_left;
	double		m_angle_right;
	double		m_angle_left_surround;
	double		m_angle_right_surround;

	double		m_fractional_order_center;
	double		m_fractional_order_stereo;
	double		m_fractional_order_surround;

	double		m_scale_factor_center;
	double		m_scale_factor_stereo;
	double		m_scale_factor_surround;

	double		m_last_sample;

	int*		m_index_of_harmonics;

	gsl_matrix* m_microphones_matrix_center;
	gsl_matrix* m_microphones_matrix_stereo;
	gsl_matrix* m_microphones_matrix_surround;

	gsl_vector* m_input_vector_center;
	gsl_vector* m_input_vector_stereo;
	gsl_vector* m_input_vector_surround;

	gsl_vector* m_output_vector_center;
	gsl_vector* m_output_vector_stereo;
	gsl_vector* m_output_vector_surround;

	gsl_vector* m_optim_vector_center;
	gsl_vector* m_optim_vector_stereo;
	gsl_vector* m_optim_vector_surround;

	double	computeInPhaseFractionalOrder(double aDelta);
	double	computeScaleFactor(long anIndex, double anAngle);
	void	computeMicrophones();
	void	computeIndex();
	void	computeFiveDotOneOptim();
	
public:
	AmbisonicFiveDotOne(long anOrder,  double aFrontDelta = 30., double aSurroundDelta = 110., long aVectorSize = 0);
	
	long	getOrder();
	long	getNumberOfHarmonics();
	long	getNumberOfInputs();
	long	getNumberOfOutputs();
	long	getVectorSize();
	double	getFractionalOrderCenter();
	double	getFractionalOrderFront();
	double	getFractionalOrderSurround();

	void	setVectorSize(int aVectorSize);
	~AmbisonicFiveDotOne();
	
	/* Perform sample by sample*/
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{	
		for(int j = 0; j < m_number_of_harmonics; j++)
		{
			gsl_vector_set(m_input_vector_center, j, aInputs[j]);
			gsl_vector_set(m_input_vector_stereo, j, aInputs[j]);
			gsl_vector_set(m_input_vector_surround, j, aInputs[j]);
		}

		gsl_vector_mul(m_input_vector_center, m_optim_vector_center);
		gsl_vector_mul(m_input_vector_stereo, m_optim_vector_stereo);
		gsl_vector_mul(m_input_vector_surround, m_optim_vector_surround);

		gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix_center, m_input_vector_center, 0.0, m_output_vector_center);
		gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix_stereo, m_input_vector_stereo, 0.0, m_output_vector_stereo);
		gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix_surround, m_input_vector_surround, 0.0, m_output_vector_surround);

		aOutputs[0] = gsl_vector_get(m_output_vector_center, 0) * m_scale_factor_center;
		aOutputs[1] = gsl_vector_get(m_output_vector_stereo, 0) * m_scale_factor_stereo;
		aOutputs[4] = gsl_vector_get(m_output_vector_stereo, 1) * m_scale_factor_stereo;
		aOutputs[2] = gsl_vector_get(m_output_vector_surround, 0) * m_scale_factor_surround;
		aOutputs[3] = gsl_vector_get(m_output_vector_surround, 1) * m_scale_factor_surround;
		aOutputs[5] = 0.;
		for(int j = 0; j < 5; j++)
			aOutputs[5] += aOutputs[j];
		aOutputs[5] /= 5.;
		aOutputs[5] *= 0.017096;
		aOutputs[5] -= m_last_sample;
		m_last_sample = -0.982904 * aOutputs[5];
	}	
	
	/* Perform block samples */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{	
		for(int i = 0; i < m_vector_size; i++)
		{
			for(int j = 0; j < m_number_of_harmonics; j++)
			{
				gsl_vector_set(m_input_vector_center, j, aInputs[j][i]);
				gsl_vector_set(m_input_vector_stereo, j, aInputs[j][i]);
				gsl_vector_set(m_input_vector_surround, j, aInputs[j][i]);
			}

			gsl_vector_mul(m_input_vector_center, m_optim_vector_center);
			gsl_vector_mul(m_input_vector_stereo, m_optim_vector_stereo);
			gsl_vector_mul(m_input_vector_surround, m_optim_vector_surround);

			gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix_center, m_input_vector_center, 0.0, m_output_vector_center);
			gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix_stereo, m_input_vector_stereo, 0.0, m_output_vector_stereo);
			gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix_surround, m_input_vector_surround, 0.0, m_output_vector_surround);

			aOutputs[0][i] = gsl_vector_get(m_output_vector_center, 0) * m_scale_factor_center;
			aOutputs[1][i] = gsl_vector_get(m_output_vector_stereo, 0) * m_scale_factor_stereo;
			aOutputs[4][i] = gsl_vector_get(m_output_vector_stereo, 1) * m_scale_factor_stereo;
			aOutputs[2][i] = gsl_vector_get(m_output_vector_surround, 0) * m_scale_factor_surround;
			aOutputs[3][i] = gsl_vector_get(m_output_vector_surround, 1) * m_scale_factor_surround;
			aOutputs[5][i] = 0.;
			for(int j = 0; j < 5; j++)
				aOutputs[5][i] += aOutputs[j][i];
			aOutputs[5][i] /= 5.;
			aOutputs[5][i] *= 0.017096;
			aOutputs[5][i] -= m_last_sample;
			m_last_sample = -0.982904 * aOutputs[5][i];
		}	
	}	
};

#endif


