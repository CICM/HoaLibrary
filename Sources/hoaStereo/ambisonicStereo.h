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

#ifndef DEF_AMBISONIC_STEREO
#define DEF_AMBISONIC_STEREO

#ifndef PI
#define PI 3.1415926535897932384626433832795
#define TWOPI 3.1415926535897932384626433832795 * 2.
#endif

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>
#include "AmbisonicEncode.hpp"

class ambisonicStereo
{
	
private:
	int			m_order;
	int			m_number_of_harmonics;
	int			m_number_of_outputs;
	int			m_number_of_inputs;
	int			m_vector_size;
	double		m_loudspeakers_angle;
	double		m_axe_angle;
	double		m_scale_factor;

	int*		m_index_of_harmonics;
	gsl_matrix* m_microphones_matrix;
	gsl_vector* m_input_vector;
	gsl_vector* m_output_vector;
	gsl_vector* m_optim_vector;

public:
	ambisonicStereo(int anOrder,double anLoudspeakersAngle = 60., double aAxeAngle = 0., int aVectorSize = 0);
	int		getParameters(std::string aParameter) const;
	void	computeMicrophones();
	void	computeIndex();
	void	computeInPhaseOptim();
	void	setVectorSize(int aVectorSize);
	~ambisonicStereo();
	
	/* Perform sample by sample*/
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{	
		for(int j = 0; j < m_number_of_harmonics; j++)
			gsl_vector_set(m_input_vector, j, aInputs[j]);
		
		gsl_vector_mul(m_input_vector, m_optim_vector);
		gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix, m_input_vector, 0.0, m_output_vector);
			
		for(int j = 0; j < m_number_of_outputs; j++)
			aOutputs[j] = m_scale_factor * gsl_vector_get(m_output_vector, j);			
	}	
	
	/* Perform block samples */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{	
		for(int i = 0; i < m_vector_size; i++)
		{
			for(int j = 0; j < m_number_of_harmonics; j++)
				gsl_vector_set(m_input_vector, j, aInputs[j][i]);
			
			gsl_vector_mul(m_input_vector, m_optim_vector);
			gsl_blas_dgemv(CblasTrans, 1.0, m_microphones_matrix, m_input_vector, 0.0, m_output_vector);
			
			for(int j = 0; j < m_number_of_outputs; j++)
				aOutputs[j][i] = m_scale_factor * gsl_vector_get(m_output_vector, j);			
		}
	}	
};

#endif


