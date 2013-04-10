/*
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


#ifndef DEF_AmbisonicDecode
#define DEF_AmbisonicDecode

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>
#include "gslMatrix.hpp"
#include "../cicmTools.h"

class AmbisonicDecode
{
	
private:
	long m_order;
	long m_number_of_harmonics;
	long m_number_of_inputs;
	long m_number_of_outputs;
	long m_vector_size;
	
	double		*m_speakers_angles;
	long		*m_index_of_harmonics;
	
	gsl_matrix	*m_decoder_matrix;
	gsl_vector	*m_input_vector;
	gsl_vector	*m_output_vector;

	void computeIndex();
	void computeAngles();
	void computePseudoInverse();
	void setSpkrsAngles(double* someSpkrsAngles, int size);

public:
	AmbisonicDecode(long anOrder, long aNumberOfChannels = 0, long aVectorSize = 0);

	long getOrder();
	long getNumberOfHarmonics();
	long getNumberOfInputs();
	long getNumberOfOutputs();
	long getVectorSize();

	void setVectorSize(int aVectorSize);
	~AmbisonicDecode();
	
	/* Perform sample by sample */
	template<typename Type> void process(Type* aInputs, Type* aOutputs)
	{	
		for(int j = 0; j < m_number_of_harmonics; j++)
			gsl_vector_set(m_input_vector, j, aInputs[j]);
		
		gsl_blas_dgemv(CblasNoTrans,1.0, m_decoder_matrix, m_input_vector, 0.0, m_output_vector);
		
		for(int j = 0; j < m_number_of_outputs; j++)
			aOutputs[j] = gsl_vector_get(m_output_vector, j);
	}
	
	/* Perform block sample */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{	
		for(int i = 0; i < m_vector_size; i++)
		{
			for(int j = 0; j < m_number_of_harmonics; j++)
				gsl_vector_set(m_input_vector, j, aInputs[j][i]);
			
			gsl_blas_dgemv(CblasNoTrans,1.0, m_decoder_matrix, m_input_vector, 0.0, m_output_vector);
			
			for(int j = 0; j < m_number_of_outputs; j++)
				aOutputs[j][i] = gsl_vector_get(m_output_vector, j);
		}
	}
};



#endif


