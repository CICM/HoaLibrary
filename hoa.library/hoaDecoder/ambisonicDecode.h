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


#ifndef define DEF_AMBISONICDECODE
#define DEF_AMBISONICDECODE

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "gslMatrix.h"
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>


class ambisonicDecode
{
	
private:
	int m_order;
	int m_number_of_harmonics;
	int m_number_of_inputs;
	int m_number_of_outputs;
	int	m_sampling_rate;
	int	m_vector_size;
	std::string m_optimMode;
	
	double		*m_speakers_angles;
	int			*m_index_of_harmonics;
	
	gsl_matrix	*m_decoder_matrix;
	gsl_vector	*m_input_vector;
	gsl_vector	*m_output_vector;
	double		*m_optimVector;
	
public:
	ambisonicDecode(int anOrder, int aNumberOfChannels = 0, int aVectorSize = 0, std::string anOptimMode = "basic");
	
	int	 getParameters(std::string aParameter) const;
	void computeIndex();
	void computeAngles();
	void setVectorSize(int aVectorSize);
	void setOptimMode(std::string anOptim);
	void computeBasicOptim();
	void computeReOptim();
	void computeInPhaseOptim();
	
	void computePseudoInverse();
	void setSpkrsAngles(double* someSpkrsAngles, int size);

	~ambisonicDecode();
	
	/* Perform */
	template<typename Type> void process(Type** aInputs, Type** aOutputs)
	{	
		for(int i = 0; i < m_vector_size; i++)
		{
			for(int j = 0; j < m_number_of_harmonics; j++)
				gsl_vector_set(m_input_vector, j, aInputs[j][i] * m_optimVector[j]);
			
			gsl_blas_dgemv(CblasNoTrans,1.0, m_decoder_matrix, m_input_vector, 0.0, m_output_vector);
			
			for(int j = 0; j < m_number_of_outputs; j++)
				aOutputs[j][i] = gsl_vector_get(m_output_vector, j);			
		}
	}
};



#endif


