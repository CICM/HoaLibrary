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

#ifndef define DEF_AMBISONICRECOMPOSER
#define DEF_AMBISONICRECOMPOSER

#define M_2PI 2*M_PI
#define NUMBEROFCIRCLEPOINTS 360000
#define round(x) ((fabs(ceil(x) - (x)) < fabs(floor(x) - (x))) ? ceil(x) : floor(x))

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "gslMatrix.hpp"
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>


class ambisonicRecomposer
{
	
private:
	int		m_order;
	int		m_number_of_harmonics;
	int		m_number_of_inputs;
	int		m_number_of_outputs;
	int		m_sampling_rate;
	int		m_vector_size;
	
	double	m_fishEyeFactor;

	double		*m_speakers_angles;
	int			*m_index_of_harmonics;
	
	gsl_matrix*		m_recompMicCoefs;
	gsl_matrix**	m_recompMicCoefsSet;
	gsl_vector*		m_output_vector;
	gsl_vector*		m_input_vector;
public:
	ambisonicRecomposer(int anOrder, int aNumberOfChannels = 0, int aVectorSize = 0);
	int	getParameters(std::string aParameter) const;
	void computeIndex();
	void computeAngles();
	void setVectorSize(int aVectorSize);
	void setFishEyeFactor(double aFishEyeFactor);
	void computeMicMatrix(gsl_matrix* resMatrix, double aFishFactor);
	void computeMicMatrixSet();
	
	~ambisonicRecomposer();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs, Type aFishEyeFactor)
	{
		setFishEyeFactor(aFishEyeFactor);
		process(aInputs, aOutputs);
	}
	
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{
		for(int j = 0; j < m_number_of_inputs; j++)
			gsl_vector_set(m_input_vector, j, aInputs[j]);
		
		gsl_blas_dgemv(CblasTrans,1.0, m_recompMicCoefsSet[(int)round(m_fishEyeFactor * (NUMBEROFCIRCLEPOINTS-1))], m_input_vector, 0.0, m_output_vector);
		
		for(int j = 0; j < m_number_of_outputs; j++)
			aOutputs[j] = gsl_vector_get(m_output_vector, j);
	}
	
	/* Perform sample block */
	template<typename Type> void process(Type** aInputs, Type** aOutputs, Type* aFishEyeFactor)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
			setFishEyeFactor(aFishEyeFactor[i]);

			for(int j = 0; j < m_number_of_inputs; j++)
				gsl_vector_set(m_input_vector, j, aInputs[j][i]);
			
			gsl_blas_dgemv(CblasTrans,1.0, m_recompMicCoefsSet[(int)round((m_fishEyeFactor * (NUMBEROFCIRCLEPOINTS-1)))], m_input_vector, 0.0, m_output_vector);
			
			for(int j = 0; j < m_number_of_outputs; j++)
				aOutputs[j][i] = gsl_vector_get(m_output_vector, j);
		}
	}
	
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{
		for(int i = 0; i < m_vector_size; i++)
		{
			for(int j = 0; j < m_number_of_inputs; j++)
				gsl_vector_set(m_input_vector, j, aInputs[j][i]);
		
			gsl_blas_dgemv(CblasTrans,1.0, m_recompMicCoefsSet[(int)round(m_fishEyeFactor * (NUMBEROFCIRCLEPOINTS-1))], m_input_vector, 0.0, m_output_vector);
		
			for(int j = 0; j < m_number_of_outputs; j++)
				aOutputs[j][i] = gsl_vector_get(m_output_vector, j);
		}
	}
};



#endif


